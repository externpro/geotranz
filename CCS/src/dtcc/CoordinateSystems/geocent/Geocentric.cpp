// CLASSIFICATION: UNCLASSIFIED

/***************************************************************************/
/* RSC IDENTIFIER:  GEOCENTRIC
 *
 * ABSTRACT
 *
 *    This component provides conversions between Geodetic coordinates (latitude,
 *    longitude in radians and height in meters) and Geocentric coordinates
 *    (X, Y, Z) in meters.
 *
 * ERROR HANDLING
 *
 *    This component checks parameters for valid values.  If an invalid value
 *    is found, the error code is combined with the current error code using 
 *    the bitwise or.  This combining allows multiple error codes to be
 *    returned. The possible error codes are:
 *
 *      GEOCENT_NO_ERROR        : No errors occurred in function
 *      GEOCENT_LAT_ERROR       : Latitude out of valid range
 *                                 (-90 to 90 degrees)
 *      GEOCENT_LON_ERROR       : Longitude out of valid range
 *                                 (-180 to 360 degrees)
 *      GEOCENT_A_ERROR         : Semi-major axis less than or equal to zero
 *      GEOCENT_INV_F_ERROR     : Inverse flattening outside of valid range
 *								                 (250 to 350)
 *
 *
 * REUSE NOTES
 *
 *    GEOCENTRIC is intended for reuse by any application that performs
 *    coordinate conversions between geodetic coordinates and geocentric
 *    coordinates.
 *    
 *
 * REFERENCES
 *    
 *    An Improved Algorithm for Geocentric to Geodetic Coordinate Conversion,
 *    Ralph Toms, February 1996  UCRL-JC-123138.
 *    
 *    Further information on GEOCENTRIC can be found in the Reuse Manual.
 *
 *    GEOCENTRIC originated from : U.S. Army Topographic Engineering Center
 *                                 Geospatial Information Division
 *                                 7701 Telegraph Road
 *                                 Alexandria, VA  22310-3864
 *
 * LICENSES
 *
 *    None apply to this component.
 *
 * RESTRICTIONS
 *
 *    GEOCENTRIC has no restrictions.
 *
 * ENVIRONMENT
 *
 *    GEOCENTRIC was tested and certified in the following environments:
 *
 *    1. Solaris 2.5 with GCC version 2.8.1
 *    2. Windows 95 with MS Visual C++ version 6
 *
 * MODIFICATIONS
 *
 *    Date              Description
 *    ----              -----------
 *    25-02-97          Original Code
 *    3-02-07           Original C++ Code
 *
 */


/***************************************************************************/
/*
 *                               INCLUDES
 */

#include <math.h>
#include "Geocentric.h"
#include "CartesianCoordinates.h"
#include "GeodeticCoordinates.h"
#include "CoordinateConversionException.h"
#include "ErrorMessages.h"

/*
 *    math.h     - is needed for calls to sin, cos, tan and sqrt.
 *    Geocentric.h  - is needed for Error codes and prototype error checking.
 *    CartesianCoordinates.h   - defines cartesian coordinates
 *    GeodeticCoordinates.h   - defines geodetic coordinates
 *    CoordinateConversionException.h - Exception handler
 *    ErrorMessages.h  - Contains exception messages
 */


using namespace MSP::CCS;


/***************************************************************************/
/*                               DEFINES 
 *
 */

const double PI = 3.14159265358979323e0;
const double PI_OVER_2 = (PI / 2.0e0);
const int FALSE = 0;
const int TRUE = 1;
const double COS_67P5 = 0.38268343236508977;  /* cosine of 67.5 degrees */
const double AD_C = 1.0026000;            /* Toms region 1 constant */


/************************************************************************/
/*                              FUNCTIONS     
 *
 */

Geocentric::Geocentric( double ellipsoidSemiMajorAxis, double ellipsoidFlattening ) :
  CoordinateSystem(),
  Geocent_e2( 0.0066943799901413800 ),
  Geocent_ep2( 0.00673949675658690300 )
{
/*
 * The constructor receives the ellipsoid parameters
 * as inputs and sets the corresponding state variables.
 *
 *    ellipsoidSemiMajorAxis  : Semi-major axis of ellipsoid, in meters.       (input)
 *    ellipsoidFlattening     : Flattening of ellipsoid.						           (input)
 */

  double inv_f = 1 / ellipsoidFlattening;
  char errorStatus[500] = "";

  if (ellipsoidSemiMajorAxis <= 0.0)
    strcat( errorStatus, MSP::CCS::ErrorMessages::semiMajorAxis );
  if ((inv_f < 250) || (inv_f > 350))
  { /* Inverse flattening must be between 250 and 350 */
    strcat( errorStatus, MSP::CCS::ErrorMessages::ellipsoidFlattening );
  }

  if( strlen( errorStatus ) > 0)
    throw CoordinateConversionException( errorStatus );

  semiMajorAxis = ellipsoidSemiMajorAxis;
  flattening = ellipsoidFlattening;

  Geocent_e2 = 2 * flattening - flattening * flattening;
  Geocent_ep2 = (1 / (1 - Geocent_e2)) - 1;
}


Geocentric::Geocentric( const Geocentric &g )
{
  semiMajorAxis = g.semiMajorAxis;
  flattening = g.flattening;
  Geocent_e2 = g.Geocent_e2;
  Geocent_ep2 = g.Geocent_ep2;
}


Geocentric::~Geocentric()
{
}


Geocentric& Geocentric::operator=( const Geocentric &g )
{
  if( this != &g )
  {
    semiMajorAxis = g.semiMajorAxis;
    flattening = g.flattening;
    Geocent_e2 = g.Geocent_e2;
    Geocent_ep2 = g.Geocent_ep2;
  }

  return *this;
}


MSP::CCS::CartesianCoordinates* Geocentric::convertFromGeodetic( const MSP::CCS::GeodeticCoordinates* geodeticCoordinates )
{
/*
 * The function convertFromGeodetic converts geodetic coordinates
 * (latitude, longitude, and height) to geocentric coordinates (X, Y, Z),
 * according to the current ellipsoid parameters.
 *
 *    longitude : Geodetic longitude in radians                    (input)
 *    latitude  : Geodetic latitude in radians                     (input)
 *    height    : Geodetic height, in meters                       (input)
 *    X         : Calculated Geocentric X coordinate, in meters    (output)
 *    Y         : Calculated Geocentric Y coordinate, in meters    (output)
 *    Z         : Calculated Geocentric Z coordinate, in meters    (output)
 *
 */

  double Rn;            /*  Earth radius at location  */
  double Sin_Lat;       /*  sin(Latitude)  */
  double Sin2_Lat;      /*  Square of sin(Latitude)  */
  double Cos_Lat;       /*  cos(Latitude)  */
  char errorStatus[50] = "";

  double longitude = geodeticCoordinates->longitude();
  double latitude = geodeticCoordinates->latitude();
  double height = geodeticCoordinates->height();

  if ((latitude < -PI_OVER_2) || (latitude > PI_OVER_2))
  { /* Latitude out of range */
    strcat( errorStatus, MSP::CCS::ErrorMessages::latitude );
  }
  if ((longitude < -PI) || (longitude > (2*PI)))
  { /* Longitude out of range */
    strcat( errorStatus, MSP::CCS::ErrorMessages::longitude );
  }

  if( strlen( errorStatus ) > 0)
    throw CoordinateConversionException( errorStatus );

  if (longitude > PI)
    longitude -= (2*PI);
  Sin_Lat = sin(latitude);
  Cos_Lat = cos(latitude);
  Sin2_Lat = Sin_Lat * Sin_Lat;
  Rn = semiMajorAxis / (sqrt(1.0e0 - Geocent_e2 * Sin2_Lat));
  double X = (Rn + height) * Cos_Lat * cos(longitude);
  double Y = (Rn + height) * Cos_Lat * sin(longitude);
  double Z = ((Rn * (1 - Geocent_e2)) + height) * Sin_Lat;

  return new CartesianCoordinates( CoordinateType::geocentric, X, Y, Z );
}


MSP::CCS::GeodeticCoordinates* Geocentric::convertToGeodetic( MSP::CCS::CartesianCoordinates* cartesianCoordinates )
{
/*
 * The function convertToGeodetic converts geocentric
 * coordinates (X, Y, Z) to geodetic coordinates (latitude, longitude, 
 * and height), according to the current ellipsoid parameters.
 *
 *    X         : Geocentric X coordinate, in meters.         (input)
 *    Y         : Geocentric Y coordinate, in meters.         (input)
 *    Z         : Geocentric Z coordinate, in meters.         (input)
 *    longitude : Calculated longitude value in radians.      (output)
 *    latitude  : Calculated latitude value in radians.       (output)
 *    height    : Calculated height value, in meters.         (output)
 *
 * The method used here is derived from 'An Improved Algorithm for
 * Geocentric to Geodetic Coordinate Conversion', by Ralph Toms, Feb 1996
 */

/* Note: Variable names follow the notation used in Toms, Feb 1996 */

  double W;        /* distance from Z axis */
  double W2;       /* square of distance from Z axis */
  double T0;       /* initial estimate of vertical component */
  double T1;       /* corrected estimate of vertical component */
  double S0;       /* initial estimate of horizontal component */
  double S1;       /* corrected estimate of horizontal component */
  double Sin_B0;   /* sin(B0), B0 is estimate of Bowring aux variable */
  double Sin3_B0;  /* cube of sin(B0) */
  double Cos_B0;   /* cos(B0) */
  double Sin_p1;   /* sin(phi1), phi1 is estimated latitude */
  double Cos_p1;   /* cos(phi1) */
  double Rn;       /* Earth radius at location */
  double Sum;      /* numerator of cos(phi1) */
  int At_Pole;     /* indicates location is in polar region */
  double longitude, latitude, height;
  double Geocent_b = semiMajorAxis * (1 - flattening); /* Semi-minor axis of ellipsoid, in meters */

  double X = cartesianCoordinates->x();
  double Y = cartesianCoordinates->y();
  double Z = cartesianCoordinates->z();

  At_Pole = FALSE;
  if (X != 0.0)
  {
    longitude = atan2(Y,X);
  }
  else
  {
    if (Y > 0)
    {
      longitude = PI_OVER_2;
    }
    else if (Y < 0)
    {
      longitude = -PI_OVER_2;
    }
    else
    {
      At_Pole = TRUE;
      longitude = 0.0;
      if (Z > 0.0)
      {  /* north pole */
        latitude = PI_OVER_2;
      }
      else if (Z < 0.0)
      {  /* south pole */
        latitude = -PI_OVER_2;
      }
      else
      {  /* center of earth */
        latitude = PI_OVER_2;
        height = -Geocent_b;
        return new GeodeticCoordinates( CoordinateType::geodetic, longitude, latitude, height );
      } 
    }
  }
  W2 = X*X + Y*Y;
  W = sqrt(W2);
  T0 = Z * AD_C;
  S0 = sqrt(T0 * T0 + W2);
  Sin_B0 = T0 / S0;
  Cos_B0 = W / S0;
  Sin3_B0 = Sin_B0 * Sin_B0 * Sin_B0;
  T1 = Z + Geocent_b * Geocent_ep2 * Sin3_B0;
  Sum = W - semiMajorAxis * Geocent_e2 * Cos_B0 * Cos_B0 * Cos_B0;
  S1 = sqrt(T1*T1 + Sum * Sum);
  Sin_p1 = T1 / S1;
  Cos_p1 = Sum / S1;
  Rn = semiMajorAxis / sqrt(1.0 - Geocent_e2 * Sin_p1 * Sin_p1);
  if (Cos_p1 >= COS_67P5)
  {
    height = W / Cos_p1 - Rn;
  }
  else if (Cos_p1 <= -COS_67P5)
  {
    height = W / -Cos_p1 - Rn;
  }
  else
  {
    height = Z / Sin_p1 + Rn * (Geocent_e2 - 1.0);
  }
  if (At_Pole == FALSE)
  {
    latitude = atan(Sin_p1 / Cos_p1);
  }

  return new GeodeticCoordinates( CoordinateType::geodetic, longitude, latitude, height );
}



// CLASSIFICATION: UNCLASSIFIED
