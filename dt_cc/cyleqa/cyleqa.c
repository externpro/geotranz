/***************************************************************************/
/* RSC IDENTIFIER: CYLINDRICAL EQUAL AREA
 *
 * ABSTRACT
 *
 *    This component provides conversions between Geodetic coordinates
 *    (latitude and longitude in radians) and Cylindrical Equal Area projection
 *    coordinates (easting and northing in meters).
 *
 * ERROR HANDLING
 *
 *    This component checks parameters for valid values.  If an invalid value
 *    is found, the error code is combined with the current error code using
 *    the bitwise or.  This combining allows multiple error codes to be
 *    returned. The possible error codes are:
 *
 *          CYEQ_NO_ERROR           : No errors occurred in function
 *          CYEQ_LAT_ERROR          : Latitude outside of valid range
 *                                      (-90 to 90 degrees)
 *          CYEQ_LON_ERROR          : Longitude outside of valid range
 *                                      (-180 to 360 degrees)
 *          CYEQ_EASTING_ERROR      : Easting outside of valid range
 *                                      (False_Easting +/- ~20,000,000 m,
 *                                       depending on ellipsoid parameters
 *                                       and Origin_Latitude)
 *          CYEQ_NORTHING_ERROR     : Northing outside of valid range
 *                                      (False_Northing +/- ~6,000,000 m,
 *                                       depending on ellipsoid parameters
 *                                       and Origin_Latitude)
 *          CYEQ_ORIGIN_LAT_ERROR   : Origin latitude outside of valid range
 *                                      (-90 to 90 degrees)
 *          CYEQ_CENT_MER_ERROR     : Central meridian outside of valid range
 *                                      (-180 to 360 degrees)
 *          CYEQ_A_ERROR            : Semi-major axis less than or equal to zero
 *          CYEQ_INV_F_ERROR        : Inverse flattening outside of valid range
 *                                      (250 to 350)
 *
 * REUSE NOTES
 *
 *    CYLINDRICAL EQUAL AREA is intended for reuse by any application that performs a
 *    Cylindrical Equal Area projection or its inverse.
 *
 * REFERENCES
 *
 *    Further information on CYLINDRICAL EQUAL AREA can be found in the Reuse Manual.
 *
 *    CYLINDRICAL EQUAL AREA originated from :
 *                                U.S. Army Topographic Engineering Center
 *                                Geospatial Information Division
 *                                7701 Telegraph Road
 *                                Alexandria, VA  22310-3864
 *
 * LICENSES
 *
 *    None apply to this component.
 *
 * RESTRICTIONS
 *
 *    CYLINDRICAL EQUAL AREA has no restrictions.
 *
 * ENVIRONMENT
 *
 *    CYLINDRICAL EQUAL AREA was tested and certified in the following environments:
 *
 *    1. Solaris 2.5 with GCC 2.8.1
 *    2. MS Windows 95 with MS Visual C++ 6
 *
 * MODIFICATIONS
 *
 *    Date              Description
 *    ----              -----------
 *    4/16/99          Original Code
 *
 */


/***************************************************************************/
/*
 *                               INCLUDES
 */

#include <math.h>
#include "cyleqa.h"

/*
 *    math.h   - Standard C math library
 *    cyleqa.h - Is for prototype error checking
 */


/***************************************************************************/
/*
 *                               DEFINES
 */

#define PI         3.14159265358979323e0  /* PI                            */
#define PI_OVER_2  ( PI / 2.0)
#define TWO_PI     (2.0 * PI)
#define CYLEQAR_Q(slat, x)                (1.0-es2)*(slat/(1.0-x*x)-(1.0/(2.0*es))*      \
                            log((1.0-x)/(1.0+x)))
#define CYEQ_COEFF_TIMES_SIN(coeff, c, Beta)      (coeff * sin(c * Beta))
#define ONE        (1.0 * PI / 180)       /* 1 degree in radians           */

/***************************************************************************/
/*
 *                               GLOBALS
 */

/* Ellipsoid Parameters, default to WGS 84 */
static double Cyeq_a = 6378137.0;                     /* Semi-major axis of ellipsoid in meters */
static double Cyeq_f = 1 / 298.257223563;             /* Flattening of ellipsoid */
static double es2 = 0.0066943799901413800;            /* Eccentricity (0.08181919084262188000) squared  */
static double es = .081819190842622;                  /* Sqrt(es2) */
static double es4 = 4.4814723452405e-005;             /* es2 * es2 */
static double es6 = 3.0000678794350e-007;             /* es4 * es2 */
static double k0 = 1.0;
static double Cyeq_a_k0 = 6378137.0;                  /* Cyeq_a * k0 */
static double two_k0 = 2.0;                           /* 2.0 * k0 */
static double c0 = .0022392088624809;                 /* es2 / 3.0 + 31.0 * es4 / 180.0 + 517.0 * es6 / 5040.0 */
static double c1 = 2.8830839728915e-006;              /* 23.0 es4 / 360.0 + 251.0 * es6 / 3780.0 */
static double c2 = 5.0331826636906e-009;              /* 761.0 * es6 / 45360.0 */

/* Cylindrical Equal Area projection Parameters */
static double Cyeq_Origin_Lat = 0.0;                  /* Latitude of origin in radians     */
static double Cyeq_Origin_Long = 0.0;                 /* Longitude of origin in radians    */
static double Cyeq_False_Northing = 0.0;              /* False northing in meters          */
static double Cyeq_False_Easting = 0.0;               /* False easting in meters           */

/* Maximum variance for easting and northing values for WGS 84.
 */
static double Cyeq_Max_Easting = 20037509.0;
static double Cyeq_Min_Easting = -20037509.0;
static double Cyeq_Delta_Northing = 6363886.0;
/*
 * These state variables are for optimization purposes.  The only function
 * that should modify them is Set_Cyl_Eq_Area_Parameters.
 */


/***************************************************************************/
/*
 *                              FUNCTIONS
 */


long Set_Cyl_Eq_Area_Parameters(double a,
                                double f,
                                double Origin_Latitude,
                                double Central_Meridian,
                                double False_Easting,
                                double False_Northing)
{ /* Begin Set_Cyl_Eq_Area_Parameters */
/*
 * The function Set_Cyl_Eq_Area_Parameters receives the ellipsoid parameters and
 * Cylindrical Equal Area projcetion parameters as inputs, and sets the corresponding
 * state variables.  If any errors occur, the error code(s) are returned by the
 * function, otherwise CYEQ_NO_ERROR is returned.
 *
 *    a                 : Semi-major axis of ellipsoid, in meters   (input)
 *    f                 : Flattening of ellipsoid                   (input)
 *    Origin_Latitude   : Latitude in radians at which the          (input)
 *                          point scale factor is 1.0
 *    Central_Meridian  : Longitude in radians at the center of     (input)
 *                          the projection
 *    False_Easting     : A coordinate value in meters assigned to the
 *                          central meridian of the projection.     (input)
 *    False_Northing    : A coordinate value in meters assigned to the
 *                          origin latitude of the projection       (input)
 */

  double Sin_Cyeq_Origin_Lat;
  double temp;
  double inv_f = 1 / f;
  long Error_Code = CYEQ_NO_ERROR;

  if (a <= 0.0)
  { /* Semi-major axis must be greater than zero */
    Error_Code |= CYEQ_A_ERROR;
  }
  if ((inv_f < 250) || (inv_f > 350))
  { /* Inverse flattening must be between 250 and 350 */
    Error_Code |= CYEQ_INV_F_ERROR;
  }
  if ((Origin_Latitude < -PI_OVER_2) || (Origin_Latitude > PI_OVER_2))
  { /* origin latitude out of range */
    Error_Code |= CYEQ_ORIGIN_LAT_ERROR;
  }
  if ((Central_Meridian < -PI) || (Central_Meridian > TWO_PI))
  { /* origin longitude out of range */
    Error_Code |= CYEQ_CENT_MER_ERROR;
  }
  if (!Error_Code)
  { /* no errors */
    Cyeq_a = a;
    Cyeq_f = f;
    Cyeq_Origin_Lat = Origin_Latitude;
    if (Central_Meridian > PI)
      Central_Meridian -= TWO_PI;
    Cyeq_Origin_Long = Central_Meridian;
    Cyeq_False_Northing = False_Northing;
    Cyeq_False_Easting = False_Easting;
    es2 = 2 * Cyeq_f - Cyeq_f * Cyeq_f;
    es4 = es2 * es2;
    es6 = es4 * es2;
    es = sqrt(es2);
    c0 = es2 / 3.0 + 31.0 * es4 / 180.0 + 517.0 * es6 / 5040.0;
    c1 = 23.0 * es4 / 360.0 + 251.0 * es6 / 3780.0;
    c2 = 761.0 * es6 / 45360.0;
    Sin_Cyeq_Origin_Lat = sin(Cyeq_Origin_Lat);
    k0 = cos(Cyeq_Origin_Lat) / sqrt(1.0 - es2 * Sin_Cyeq_Origin_Lat * Sin_Cyeq_Origin_Lat);
    Cyeq_a_k0 = Cyeq_a * k0;
    two_k0 = 2.0 * k0;

    if (Cyeq_Origin_Long > 0)
    {
      Convert_Geodetic_To_Cyl_Eq_Area(PI_OVER_2, Cyeq_Origin_Long - PI - ONE, &Cyeq_Max_Easting, &temp);
      Convert_Geodetic_To_Cyl_Eq_Area(PI_OVER_2, Cyeq_Origin_Long - PI, &Cyeq_Min_Easting, &temp);
      Convert_Geodetic_To_Cyl_Eq_Area(PI_OVER_2, PI, &temp, &Cyeq_Delta_Northing);
    }
    else if (Cyeq_Origin_Long < 0)
    {
      Convert_Geodetic_To_Cyl_Eq_Area(PI_OVER_2, Cyeq_Origin_Long + PI, &Cyeq_Max_Easting, &temp);
      Convert_Geodetic_To_Cyl_Eq_Area(PI_OVER_2, Cyeq_Origin_Long + PI + ONE, &Cyeq_Min_Easting, &temp);
      Convert_Geodetic_To_Cyl_Eq_Area(PI_OVER_2, PI, &temp, &Cyeq_Delta_Northing);
    }
    else
    {
      Convert_Geodetic_To_Cyl_Eq_Area(PI_OVER_2, PI, &Cyeq_Max_Easting, &Cyeq_Delta_Northing);
      Cyeq_Min_Easting = -Cyeq_Max_Easting;
    }

    if(Cyeq_False_Northing)
      Cyeq_Delta_Northing -= Cyeq_False_Northing;
    if (Cyeq_Delta_Northing < 0)
      Cyeq_Delta_Northing = -Cyeq_Delta_Northing;

    if(Cyeq_False_Easting)
    {
      Cyeq_Min_Easting -= Cyeq_False_Easting;
      Cyeq_Max_Easting -= Cyeq_False_Easting;
    }

  } /* End if(!Error_Code) */
  return (Error_Code);
} /* End Set_Cyl_Eq_Area_Parameters */


void Get_Cyl_Eq_Area_Parameters(double *a,
                                double *f,
                                double *Origin_Latitude,
                                double *Central_Meridian,
                                double *False_Easting,
                                double *False_Northing)
{ /* Begin Get_Cyl_Eq_Area_Parameters */
/*
 * The function Get_Cyl_Eq_Area_Parameters returns the current ellipsoid
 * parameters, and Cylindrical Equal Area projection parameters.
 *
 *    a                 : Semi-major axis of ellipsoid, in meters   (output)
 *    f                 : Flattening of ellipsoid                   (output)
 *    Origin_Latitude   : Latitude in radians at which the          (output)
 *                          point scale factor is 1.0
 *    Central_Meridian  : Longitude in radians at the center of     (output)
 *                          the projection
 *    False_Easting     : A coordinate value in meters assigned to the
 *                          central meridian of the projection.     (output)
 *    False_Northing    : A coordinate value in meters assigned to the
 *                          origin latitude of the projection       (output)
 */

  *a = Cyeq_a;
  *f = Cyeq_f;
  *Origin_Latitude = Cyeq_Origin_Lat;
  *Central_Meridian = Cyeq_Origin_Long;
  *False_Easting = Cyeq_False_Easting;
  *False_Northing = Cyeq_False_Northing;
  return;
} /* End Get_Cyl_Eq_Area_Parameters */


long Convert_Geodetic_To_Cyl_Eq_Area (double Latitude,
                                      double Longitude,
                                      double *Easting,
                                      double *Northing)
{ /* Begin Convert_Geodetic_To_Cyl_Eq_Area */
/*
 * The function Convert_Geodetic_To_Cyl_Eq_Area converts geodetic (latitude and
 * longitude) coordinates to Cylindrical Equal Area projection (easting and northing)
 * coordinates, according to the current ellipsoid and Cylindrical Equal Area projection
 * parameters.  If any errors occur, the error code(s) are returned by the
 * function, otherwise CYEQ_NO_ERROR is returned.
 *
 *    Latitude          : Latitude (phi) in radians           (input)
 *    Longitude         : Longitude (lambda) in radians       (input)
 *    Easting           : Easting (X) in meters               (output)
 *    Northing          : Northing (Y) in meters              (output)
 */

  double dlam;                      /* Longitude - Central Meridan */
  double qq;
  double x;
  double sin_lat = sin(Latitude);
  long Error_Code = CYEQ_NO_ERROR;

  if ((Latitude < -PI_OVER_2) || (Latitude > PI_OVER_2))
  { /* Latitude out of range */
    Error_Code |= CYEQ_LAT_ERROR;
  }
  if ((Longitude < -PI) || (Longitude > TWO_PI))
  { /* Longitude out of range */
    Error_Code |= CYEQ_LON_ERROR;
  }
  if (!Error_Code)
  { /* no errors */
    dlam = Longitude - Cyeq_Origin_Long;
    if (dlam > PI)
    {
      dlam -= TWO_PI;
    }
    if (dlam < -PI)
    {
      dlam += TWO_PI;
    }
    x = es * sin_lat;
    qq = CYLEQAR_Q(sin_lat,x);
    *Easting = Cyeq_a_k0 * dlam + Cyeq_False_Easting;
    *Northing = Cyeq_a * qq / two_k0 + Cyeq_False_Northing;
  }
  return (Error_Code);
} /* End Convert_Geodetic_To_Cyl_Eq_Area */


long Convert_Cyl_Eq_Area_To_Geodetic(double Easting,
                                     double Northing,
                                     double *Latitude,
                                     double *Longitude)
{ /* Begin Convert_Cyl_Eq_Area_To_Geodetic */
/*
 * The function Convert_Cyl_Eq_Area_To_Geodetic converts
 * Cylindrical Equal Area projection (easting and northing) coordinates
 * to geodetic (latitude and longitude) coordinates, according to the
 * current ellipsoid and Cylindrical Equal Area projection
 * coordinates.  If any errors occur, the error code(s) are returned by the
 * function, otherwise CYEQ_NO_ERROR is returned.
 *
 *    Easting           : Easting (X) in meters                  (input)
 *    Northing          : Northing (Y) in meters                 (input)
 *    Latitude          : Latitude (phi) in radians              (output)
 *    Longitude         : Longitude (lambda) in radians          (output)
 */

  double sin2beta, sin4beta, sin6beta;
  double dx;     /* Delta easting - Difference in easting (easting-FE)      */
  double dy;     /* Delta northing - Difference in northing (northing-FN)   */
  double qp;
  double beta;
  double sin_lat = sin(PI_OVER_2);
  double i;
  double x;
  long Error_Code = CYEQ_NO_ERROR;

  if ((Easting < (Cyeq_False_Easting + Cyeq_Min_Easting))
      || (Easting > (Cyeq_False_Easting + Cyeq_Max_Easting)))
  { /* Easting out of range */
    Error_Code |= CYEQ_EASTING_ERROR;
  }
  if ((Northing < (Cyeq_False_Northing - fabs(Cyeq_Delta_Northing)))
      || (Northing > (Cyeq_False_Northing + fabs(Cyeq_Delta_Northing))))
  { /* Northing out of range */
    Error_Code |= CYEQ_NORTHING_ERROR;
  }
  if (!Error_Code)
  { /* no errors */
    dy = Northing - Cyeq_False_Northing;
    dx = Easting - Cyeq_False_Easting;
    x = es * sin_lat;
    qp = CYLEQAR_Q(sin_lat,x);
    i = two_k0 * dy / (Cyeq_a * qp);
    if (i > 1.0)
      i = 1.0;
    else if (i < -1.0)
      i = -1.0;
    beta = asin(i);
    sin2beta = CYEQ_COEFF_TIMES_SIN(c0, 2.0, beta);
    sin4beta = CYEQ_COEFF_TIMES_SIN(c1, 4.0, beta);
    sin6beta = CYEQ_COEFF_TIMES_SIN(c2, 6.0, beta);
    *Latitude = beta + sin2beta + sin4beta + sin6beta;
    *Longitude = Cyeq_Origin_Long + dx / Cyeq_a_k0;

    if (*Latitude > PI_OVER_2)  /* force distorted values to 90, -90 degrees */
      *Latitude = PI_OVER_2;
    else if (*Latitude < -PI_OVER_2)
      *Latitude = -PI_OVER_2;

    if (*Longitude > PI)
      *Longitude -= TWO_PI;
    if (*Longitude < -PI)
      *Longitude += TWO_PI;

    if (*Longitude > PI) /* force distorted values to 180, -180 degrees */
      *Longitude = PI;
    else if (*Longitude < -PI)
      *Longitude = -PI;


  }
  return (Error_Code);
} /* End Convert_Cyl_Eq_Area_To_Geodetic */
