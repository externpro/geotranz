// CLASSIFICATION: UNCLASSIFIED

/***************************************************************************/
/* RSC IDENTIFIER:  Geoid Library
 *
 * ABSTRACT
 *
 *    The purpose of GEOID is to support conversions between WGS84 ellipsoid
 *    heights and WGS84 geoid heights.
 *
 *
 * ERROR HANDLING
 *
 *    This component checks parameters for valid values.  If an invalid value
 *    is found, the error code is combined with the current error code using
 *    the bitwise or.  This combining allows multiple error codes to be
 *    returned. The possible error codes are:
 *
 *  GEOID_NO_ERROR               : No errors occured in function
 *  GEOID_FILE_OPEN_ERROR        : Geoid file opening error
 *  GEOID_INITIALIZE_ERROR       : Geoid seoaration database can not initialize
 *  GEOID_LAT_ERROR              : Latitude out of valid range
 *                                 (-90 to 90 degrees)
 *  GEOID_LON_ERROR              : Longitude out of valid range
 *                                 (-180 to 360 degrees)
 *
 * REUSE NOTES
 *
 *    Geoid is intended for reuse by any application that requires conversion
 *    between WGS84 ellipsoid heights and WGS84 geoid heights.
 *
 * REFERENCES
 *
 *    Further information on Geoid can be found in the Reuse Manual.
 *
 *    Geoid originated from :  U.S. Army Topographic Engineering Center
 *                             Geospatial Information Division
 *                             7701 Telegraph Road
 *                             Alexandria, VA  22310-3864
 *
 * LICENSES
 *
 *    None apply to this component.
 *
 * RESTRICTIONS
 *
 *    Geoid has no restrictions.
 *
 * ENVIRONMENT
 *
 *    Geoid was tested and certified in the following environments
 *
 *    1. Solaris 2.5 with GCC 2.8.1
 *    2. MS Windows XP with MS Visual C++ 6.0
 *
 *
 * MODIFICATIONS
 *
 *    Date              Description
 *    ----              -----------
 *    24-May-99         Original Code
 *    09-Jan-06         Added new geoid height interpolation methods
 *    03-14-07          Original C++ Code
 *    05-12-10          S. Gillis, BAEts26542, MSP TS MSL-HAE conversion 
 *                      should use CCS 
 *    06-11-10          S. Gillis, BAEts26724, Fixed memory error problem
 *                      when MSPCCS_DATA is not set
 *    06-16-10          S. Gillis, BAEts27144, Fixed memory error problem
 *                      when MSPCCS_DATA is not set
 *    07-07-10          K.Lam, BAEts27269, Replace C functions in threads.h
 *                      with C++ methods in classes CCSThreadMutex
 */


/***************************************************************************/
/*
 *                               INCLUDES
 */

#include <string.h>   
#include <stdlib.h>  
#include <stdio.h>
#include "GeoidLibrary.h"
#include "CoordinateConversionException.h"
#include "ErrorMessages.h"
#include "CCSThreadMutex.h"
#include "CCSThreadLock.h"

#include <vector>

/*
 *    string.h   - standard C string handling library
 *    stdio.h    - standard C input/output library
 *    stdlib.h   - standard C general utilities library
 *    GeoidLibrary.h  - prototype error checking and error codes
 *    threads.h  - used for thread safety
 *    CoordinateConversionException.h - Exception handler
 *    ErrorMessages.h  - Contains exception messages
 */


using namespace MSP::CCS;
using MSP::CCSThreadMutex;
using MSP::CCSThreadLock;


/***************************************************************************/
/*                               DEFINES 
 *
 */

const double PI = 3.14159265358979323e0; /* PI */
const double PI_OVER_2 = PI / 2.0;
const double TWO_PI = 2.0 * PI;
const double _180_OVER_PI = (180.0 / PI);
const int EGM96_COLS = 1441;                   /* 360 degrees of longitude at 15 minute spacing */
const int EGM96_ROWS = 721;                    /* 180 degrees of latitude  at 15 minute spacing */
const int EGM84_COLS = 37;                     /* 360 degrees of longitude at 10 degree spacing */
const int EGM84_ROWS = 19;                     /* 180 degrees of latitude  at 10 degree spacing */
const int EGM84_30_MIN_COLS = 721;             /* 360 degrees of longitude at 30 minute spacing */
const int EGM84_30_MIN_ROWS = 361;             /* 180 degrees of latitude  at 30 minute spacing */
const int EGM96_HEADER_ITEMS = 6;              /* min, max lat, min, max long, lat, long spacing*/
const double SCALE_FACTOR_15_MINUTES = .25;    /* 4 grid cells per degree at 15 minute spacing  */
const double SCALE_FACTOR_10_DEGREES = 10;     /* 1 / 10.0 grid cells per degree at 10 degree spacing */
const double SCALE_FACTOR_30_MINUTES = .5;     /* 2 grid cells per degree at 30 minute spacing */
const double SCALE_FACTOR_1_DEGREE = 1;        /* 1 grid cell per degree at 1 degree spacing */
const double SCALE_FACTOR_2_DEGREES = 2;       /* 1 / 2 grid cells per degree at 2 degree spacing */
const int EGM96_ELEVATIONS = EGM96_COLS * EGM96_ROWS;
const int EGM84_ELEVATIONS = EGM84_COLS * EGM84_ROWS;
const int EGM84_30_MIN_ELEVATIONS = EGM84_30_MIN_COLS * EGM84_30_MIN_ROWS; 
const int EGM96_INSET_AREAS = 53;


/* defines the egm96 variable grid */
struct EGM96_Variable_Grid
{
  double min_lat;        /* Min cell latitude */
  double max_lat;        /* Max cell latitude */
  double min_lon;        /* Min cell longitude */
  double max_lon;        /* Max cell latitude */
}; 

/* Table of EGM96 variable grid 30 minute inset areas */
const EGM96_Variable_Grid EGM96_Variable_Grid_Table[EGM96_INSET_AREAS] =
                   {{74.5, 75.5, 273.5, 280.0},
                    {66.5, 67.5, 293.5, 295.0},
                    {62.5, 64.0, 133.0, 136.5},
                    {60.5, 61.5, 208.5, 210.0},
                    {60.5, 61.0, 219.0, 220.5},
                    {51.0, 53.0, 172.0, 174.5},
                    {52.0, 53.0, 192.5, 194.0},
                    {51.0, 52.0, 188.5, 191.0},
                    {50.0, 52.0, 178.0, 182.5},
                    {43.0, 46.0, 148.0, 153.5},
                    {43.0, 45.0, 84.0, 89.5},
                    {40.0, 41.0, 70.5, 72.0},
                    {36.5, 37.0, 78.5, 79.0},
                    {36.0, 37.0, 348.0, 349.5},
                    {35.0, 36.0, 171.0, 172.5},
                    {34.0, 35.0, 140.5, 142.0},
                    {29.5, 31.0, 78.5, 81.0},
                    {28.5, 30.0, 81.5, 83.0},
                    {26.5, 30.0, 142.0, 143.5},
                    {26.0, 29.0, 91.5, 96.0},
                    {27.5, 29.0, 84.0, 86.5},
                    {28.0, 29.0, 342.5, 344.0},
                    {26.5, 28.0, 88.5, 90.0},
                    {25.0, 26.0, 189.0, 190.5},
                    {23.0, 24.0, 195.0, 196.5},
                    {21.0, 21.5, 204.0, 204.5},
                    {20.0, 21.0, 283.5, 288.0},
                    {18.5, 20.5, 204.0, 205.5},
                    {18.0, 20.0, 291.0, 296.5},
                    {17.0, 18.0, 298.0, 299.5},
                    {15.0, 16.0, 122.0, 123.5},
                    {12.0, 14.0, 144.5, 147.0},
                    {11.0, 12.0, 141.5, 144.0},
                    {9.5, 11.5, 125.0, 127.5},
                    {10.0, 11.0, 286.0, 287.5},
                    {6.0, 9.5, 287.0, 289.5},
                    {5.0, 7.0, 124.0, 128.5},
                    {-1.0, 1.0, 125.0, 128.5},
                    {-3.0, -1.5, 281.0, 282.5},
                    {-7.0, -5.0, 150.5, 155.0},
                    {-8.0, -7.0, 107.0, 108.5},
                    {-9.0, -7.0, 147.0, 149.5},
                    {-11.0, -10.0, 161.5, 163.0},
                    {-14.5, -13.5, 166.0, 167.5},
                    {-18.5, -17.0, 186.5, 188.0},
                    {-20.5, -20.0, 168.0, 169.5},
                    {-23.0, -20.0, 184.5, 187.0},
                    {-27.0, -24.0, 288.0, 290.5},
                    {-53.0, -52.0, 312.0, 313.5},
                    {-56.0, -55.0, 333.0, 334.5},
                    {-61.5, -60.0, 312.5, 317.0},
                    {-61.5, -60.5, 300.5, 303.0},
                    {-73.0, -72.0, 24.5, 26.0}};


/************************************************************************/
/*                         LOCAL FUNCTIONS     
 *
 */

void swapBytes(
   void   *buffer,
   size_t size,
   size_t count)
{
   char *b = (char *) buffer;
   char temp;
   for (size_t c = 0; c < count; c ++)
   {
      for (size_t s = 0; s < size / 2; s ++)
      {
         temp = b[c*size + s];
         b[c*size + s] = b[c*size + size - s - 1];
         b[c*size + size - s - 1] = temp;
      }
   }
}


size_t readBinary(
   void   *buffer,
   size_t  size,
   size_t  count,
   FILE   *stream )
{
   size_t actual_count = fread(buffer, size, count, stream);

   if(ferror(stream) || actual_count < count )
   {
      char message[256] = "";
      strcpy( message, "Error reading binary file." );
      throw CoordinateConversionException( message );
   }

#ifdef LITTLE_ENDIAN
   swapBytes(buffer, size, count);
#endif

   return actual_count;
}

/************************************************************************/
/*                              FUNCTIONS     
 *
 */

/* This class is a safeguard to make sure the singleton gets deleted
 * when the application exits
 */
class MSP::CCS::GeoidLibraryCleaner
{
  public:

  ~GeoidLibraryCleaner()
  {
    CCSThreadLock lock(&GeoidLibrary::mutex);
    GeoidLibrary::deleteInstance();
  }

} geoidLibraryCleanerInstance;


// Make this class a singleton, so the data files are only initialized once
CCSThreadMutex GeoidLibrary::mutex;
GeoidLibrary* GeoidLibrary::instance = 0;
int GeoidLibrary::instanceCount = 0;


GeoidLibrary* GeoidLibrary::getInstance()
{
  CCSThreadLock lock(&mutex);
  if( instance == 0 )
    instance = new GeoidLibrary;

  instanceCount++;

  return instance;
}


void GeoidLibrary::removeInstance()
{
/*
 * The function removeInstance removes this GeoidLibrary instance from the
 * total number of instances. 
 */
  CCSThreadLock lock(&mutex);
  if ( --instanceCount < 1 )
  {
    deleteInstance();
  }
}


void GeoidLibrary::deleteInstance()
{
/*
 * Delete the singleton.
 */

  if( instance != 0 )
  {
    delete instance;
    instance = 0;
  }
}


GeoidLibrary::GeoidLibrary()
{
   loadGeoids();
}


GeoidLibrary::GeoidLibrary( const GeoidLibrary &gl )
{
   *this = gl;
}


GeoidLibrary::~GeoidLibrary()
{
  delete [] egm96GeoidList;
  delete [] egm84GeoidList;
  delete [] egm84ThirtyMinGeoidList;
}


GeoidLibrary& GeoidLibrary::operator=( const GeoidLibrary &gl )
{
  if ( &gl == this )
     return *this;

  egm96GeoidList = new float[EGM96_ELEVATIONS]; 
  egm84GeoidList = new float[EGM84_ELEVATIONS];
  egm84ThirtyMinGeoidList = new double[EGM84_30_MIN_ELEVATIONS];

  for( int i = 0; i < EGM96_ELEVATIONS; i++ )
  {
     egm96GeoidList[i] = gl.egm96GeoidList[i];
  }

  for( int j = 0; j < EGM84_ELEVATIONS; j++ )
  {
     egm84GeoidList[j] = gl.egm84GeoidList[j];
  }

  for( int k = 0; k < EGM84_30_MIN_ELEVATIONS; k++ )
  {
     egm84ThirtyMinGeoidList[k] = gl.egm84ThirtyMinGeoidList[k];
  }

  return *this;
}


void GeoidLibrary::loadGeoids()
{
/*
 * The function loadGeoids reads geoid separation data from a file in
 * the current directory and builds the geoid separation table from it.
 * If the separation file can not be found or accessed, an error code of
 * GEOID_FILE_OPEN_ERROR is returned, If the separation file is incomplete
 * or improperly formatted, an error code of GEOID_INITIALIZE_ERROR is returned,
 * otherwise GEOID_NO_ERROR is returned. This function must be called before 
 * any of the other functions in this component.
 */

   initializeEGM96Geoid();
   initializeEGM84Geoid();
   initializeEGM84ThirtyMinGeoid();
}


void GeoidLibrary::convertEllipsoidToEGM96FifteenMinBilinearGeoidHeight(
   double longitude,
   double latitude,
   double ellipsoidHeight,
   double *geoidHeight )
{
/*
 * The function convertEllipsoidToEGM96FifteenMinBilinearGeoidHeight converts the specified WGS84
 * ellipsoid height at the specified geodetic coordinates to the equivalent
 * geoid height, using the EGM96 gravity model and the bilinear interpolation method.
 *
 *    longitude          : Geodetic longitude in radians          (input)
 *    latitude           : Geodetic latitude in radians           (input)
 *    ellipsoidHeight    : Ellipsoid height, in meters            (input)
 *    geoidHeight        : Geoid height, in meters.               (output)
 *
 */

  double  delta_height;

  bilinearInterpolate(
     longitude, latitude,
     SCALE_FACTOR_15_MINUTES, EGM96_COLS, EGM96_ROWS, egm96GeoidList,
     &delta_height );

  *geoidHeight = ellipsoidHeight - delta_height;
}


void GeoidLibrary::convertEllipsoidToEGM96VariableNaturalSplineHeight(
   double longitude,
   double latitude,
   double ellipsoidHeight,
   double *geoidHeight )
{
/*
 * The function convertEllipsoidToEGM96VariableNaturalSplineHeight converts the specified WGS84
 * ellipsoid height at the specified geodetic coordinates to the equivalent
 * geoid height, using the EGM96 gravity model and the natural spline interpolation method..
 *
 *    longitude          : Geodetic longitude in radians          (input)
 *    latitude           : Geodetic latitude in radians           (input)
 *    ellipsoidHeight    : Ellipsoid height, in meters            (input)
 *    geoidHeight        : Geoid height, in meters.               (output)
 *
 */

  int i = 0;
  int num_cols = EGM96_COLS;
  int num_rows = EGM96_ROWS;
  double latitude_degrees = latitude * _180_OVER_PI;
  double longitude_degrees = longitude * _180_OVER_PI;
  double scale_factor = SCALE_FACTOR_15_MINUTES;
  double delta_height;
  long found = 0;

  if( longitude_degrees < 0.0 )
    longitude_degrees += 360.0;

  while( !found && i < EGM96_INSET_AREAS )
  {
    if(( latitude_degrees  >= EGM96_Variable_Grid_Table[i].min_lat ) &&
       ( longitude_degrees >= EGM96_Variable_Grid_Table[i].min_lon ) &&
       ( latitude_degrees   < EGM96_Variable_Grid_Table[i].max_lat ) &&
       ( longitude_degrees  < EGM96_Variable_Grid_Table[i].max_lon ) )
    {
      scale_factor = SCALE_FACTOR_30_MINUTES; // use 30 minute by 30 minute grid
      num_cols = 721;
      num_rows = 361;
      found = 1;
    }

    i++;
  }

  if( !found )
  {
    if( latitude_degrees >= -60.0 && latitude_degrees < 60.0 )
    {
      scale_factor = SCALE_FACTOR_1_DEGREE; // use 1 degree by 1 degree grid
      num_cols = 361;
      num_rows = 181;
    }
    else
    {
      scale_factor = SCALE_FACTOR_2_DEGREES; // use 2 degree by 2 degree grid
      num_cols = 181;
      num_rows = 91;
    }
  }

  naturalSplineInterpolate(
     longitude, latitude,
     scale_factor, num_cols, num_rows, EGM96_ELEVATIONS-1, egm96GeoidList,
     &delta_height );

  *geoidHeight = ellipsoidHeight - delta_height;
}


void GeoidLibrary::convertEllipsoidToEGM84TenDegBilinearHeight(
   double longitude,
   double latitude,
   double ellipsoidHeight,
   double *geoidHeight )
{
/*
 * The function convertEllipsoidToEGM84TenDegBilinearHeight converts the specified WGS84
 * ellipsoid height at the specified geodetic coordinates to the equivalent
 * geoid height, using the EGM84 gravity model and the bilinear interpolation method.
 *
 *    longitude          : Geodetic longitude in radians          (input)
 *    latitude           : Geodetic latitude in radians           (input)
 *    ellipsoidHeight    : Ellipsoid height, in meters            (input)
 *    geoidHeight        : Geoid height, in meters.               (output)
 *
 */

   double delta_height;

   bilinearInterpolate(
      longitude, latitude,
      SCALE_FACTOR_10_DEGREES, EGM84_COLS, EGM84_ROWS, egm84GeoidList,
      &delta_height );

   *geoidHeight = ellipsoidHeight - delta_height;
}


void GeoidLibrary::convertEllipsoidToEGM84TenDegNaturalSplineHeight(
   double longitude,
   double latitude,
   double ellipsoidHeight,
   double *geoidHeight )
{
/*
 * The function convertEllipsoidToEGM84TenDegNaturalSplineHeight converts the specified WGS84
 * ellipsoid height at the specified geodetic coordinates to the equivalent
 * geoid height, using the EGM84 gravity model and the natural spline interpolation method..
 *
 *    longitude           : Geodetic longitude in radians          (input)
 *    latitude            : Geodetic latitude in radians           (input)
 *    ellipsoidHeight     : Ellipsoid height, in meters            (input)
 *    geoidHeight         : Geoid height, in meters.               (output)
 *
 */

  double delta_height;

  naturalSplineInterpolate(
     longitude, latitude,
     SCALE_FACTOR_10_DEGREES, EGM84_COLS, EGM84_ROWS, EGM84_ELEVATIONS-1,
     egm84GeoidList, &delta_height );

  *geoidHeight = ellipsoidHeight - delta_height;
}


void GeoidLibrary::convertEllipsoidToEGM84ThirtyMinBiLinearHeight( 
    double longitude, double latitude, double ellipsoidHeight, 
    double *geoidHeight )
{
/*
 * The function convertEllipsoidToEGM84ThirtyMinBiLinearHeight converts the 
 * specified WGS84 ellipsoid height at the specified geodetic coordinates to the
 * equivalent geoid height, using the EGM84 gravity model and the bilinear 
 * interpolation method..
 *
 *    longitude           : Geodetic longitude in radians          (input)
 *    latitude            : Geodetic latitude in radians           (input)
 *    ellipsoidHeight     : Ellipsoid height, in meters            (input)
 *    geoidHeight         : Geoid height, in meters.               (output)
 *
 */

  double delta_height;

  bilinearInterpolateDoubleHeights(
     longitude, latitude,
     SCALE_FACTOR_30_MINUTES, EGM84_30_MIN_COLS, EGM84_30_MIN_ROWS,
     egm84ThirtyMinGeoidList, &delta_height );

  *geoidHeight = ellipsoidHeight - delta_height;
}


void GeoidLibrary::convertEGM96FifteenMinBilinearGeoidToEllipsoidHeight( double longitude, double latitude, double geoidHeight,  double *ellipsoidHeight )
{
/*
 * The function convertEGM96FifteenMinBilinearGeoidToEllipsoidHeight converts the specified WGS84
 * geoid height at the specified geodetic coordinates to the equivalent
 * ellipsoid height, using the EGM96 gravity model and the bilinear interpolation method.
 *
 *    longitude           : Geodetic longitude in radians          (input)
 *    latitude            : Geodetic latitude in radians           (input)
 *    geoidHeight         : Geoid height, in meters.               (input)
 *    ellipsoidHeight     : Ellipsoid height, in meters            (output)
 *
 */

  double  delta_height;

  bilinearInterpolate(
     longitude, latitude,
     SCALE_FACTOR_15_MINUTES, EGM96_COLS, EGM96_ROWS, egm96GeoidList,
     &delta_height );

  *ellipsoidHeight = geoidHeight + delta_height;
}


void GeoidLibrary::convertEGM96VariableNaturalSplineToEllipsoidHeight(
   double longitude,
   double latitude,
   double geoidHeight,
   double *ellipsoidHeight )
{
/*
 * The function convertEGM96VariableNaturalSplineToEllipsoidHeight converts the specified WGS84
 * geoid height at the specified geodetic coordinates to the equivalent
 * ellipsoid height, using the EGM96 gravity model and the natural spline interpolation method.
 *
 *    longitude           : Geodetic longitude in radians          (input)
 *    latitude            : Geodetic latitude in radians           (input)
 *    geoidHeight         : Geoid height, in meters.               (input)
 *    ellipsoidHeight     : Ellipsoid height, in meters            (output)
 *
 */

  int i = 0;
  int num_cols = EGM96_COLS;
  int num_rows = EGM96_ROWS;
  double latitude_degrees = latitude * _180_OVER_PI;
  double longitude_degrees = longitude * _180_OVER_PI;
  double scale_factor = SCALE_FACTOR_15_MINUTES;
  double delta_height;
  long found = 0;

  if( longitude_degrees < 0.0 )
    longitude_degrees += 360.0;

  while( !found && i < EGM96_INSET_AREAS )
  {
    if(( latitude_degrees  >= EGM96_Variable_Grid_Table[i].min_lat ) &&
       ( longitude_degrees >= EGM96_Variable_Grid_Table[i].min_lon ) &&
       ( latitude_degrees   < EGM96_Variable_Grid_Table[i].max_lat ) &&
       ( longitude_degrees  < EGM96_Variable_Grid_Table[i].max_lon ) )
    {
      scale_factor = SCALE_FACTOR_30_MINUTES; // use 30 minute by 30 minute grid
      num_cols = 721;
      num_rows = 361;
      found = 1;
    }

    i++;
  }

  if( !found )
  {
    if( latitude_degrees >= -60.0 && latitude_degrees < 60.0 )
    {
      scale_factor = SCALE_FACTOR_1_DEGREE; // use 1 degree by 1 degree grid
      num_cols = 361;
      num_rows = 181;
    }
    else
    {
      scale_factor = SCALE_FACTOR_2_DEGREES; // use 2 degree by 2 degree grid
      num_cols = 181;
      num_rows = 91;
    }
  }

  naturalSplineInterpolate(
     longitude, latitude,
     scale_factor, num_cols, num_rows, EGM96_ELEVATIONS-1, egm96GeoidList,
     &delta_height );

  *ellipsoidHeight = geoidHeight + delta_height;
}


void GeoidLibrary::convertEGM84TenDegBilinearToEllipsoidHeight( double longitude, double latitude, double geoidHeight, double *ellipsoidHeight )
{
/*
 * The function convertEGM84TenDegBilinearToEllipsoidHeight converts the specified WGS84
 * geoid height at the specified geodetic coordinates to the equivalent
 * ellipsoid height, using the EGM84 gravity model and the bilinear interpolation method.
 *
 *    longitude           : Geodetic longitude in radians          (input)
 *    latitude            : Geodetic latitude in radians           (input)
 *    geoidHeight         : Geoid height, in meters.               (input)
 *    ellipsoidHeight     : Ellipsoid height, in meters            (output)
 *
 */

  double  delta_height;

  bilinearInterpolate(
     longitude, latitude,
     SCALE_FACTOR_10_DEGREES, EGM84_COLS, EGM84_ROWS, egm84GeoidList,
     &delta_height );

  *ellipsoidHeight = geoidHeight + delta_height;
}


void GeoidLibrary::convertEGM84TenDegNaturalSplineToEllipsoidHeight(
   double longitude,
   double latitude,
   double geoidHeight,
   double *ellipsoidHeight )
{
/*
 * The function convertEGM84TenDegNaturalSplineToEllipsoidHeight converts the specified WGS84
 * geoid height at the specified geodetic coordinates to the equivalent
 * ellipsoid height, using the EGM84 gravity model and the natural spline interpolation method.
 *
 *    longitude           : Geodetic longitude in radians          (input)
 *    latitude            : Geodetic latitude in radians           (input)
 *    geoidHeight         : Geoid height, in meters.               (input)
 *    ellipsoidHeight     : Ellipsoid height, in meters            (output)
 *
 */

  double  delta_height;

  naturalSplineInterpolate(
     longitude, latitude, SCALE_FACTOR_10_DEGREES,
     EGM84_COLS, EGM84_ROWS, EGM84_ELEVATIONS-1,
     egm84GeoidList, &delta_height );

  *ellipsoidHeight = geoidHeight + delta_height;
}


void GeoidLibrary::convertEGM84ThirtyMinBiLinearToEllipsoidHeight( 
    double longitude, double latitude, double geoidHeight, 
    double *ellipsoidHeight )
{
/*
 * The function convertEGM84ThirtyMinBiLinearToEllipsoidHeight converts the 
 * specified WGS84 geoid height at the specified geodetic coordinates to the 
 * equivalent ellipsoid height, using the EGM84 gravity model and the bilinear 
 * interpolation method.
 *
 *    longitude           : Geodetic longitude in radians          (input)
 *    latitude            : Geodetic latitude in radians           (input)
 *    geoidHeight         : Geoid height, in meters.               (input)
 *    ellipsoidHeight     : Ellipsoid height, in meters            (output)
 *
 */

  double  delta_height;

  bilinearInterpolateDoubleHeights( longitude, latitude, SCALE_FACTOR_30_MINUTES, 
      EGM84_30_MIN_COLS, EGM84_30_MIN_ROWS, egm84ThirtyMinGeoidList, 
      &delta_height );
  *ellipsoidHeight = geoidHeight + delta_height;
}


/************************************************************************/
/*                              PRIVATE FUNCTIONS     
 *
 */

void GeoidLibrary::initializeEGM96Geoid()
{
/*
 * The function initializeEGM96Geoid reads geoid separation data from the egm96.grd
 *  file in the current directory and builds a geoid separation table from it.
 * If the separation file can not be found or accessed, an error code of
 * GEOID_FILE_OPEN_ERROR is returned, If the separation file is incomplete
 * or improperly formatted, an error code of GEOID_INITIALIZE_ERROR is returned,
 * otherwise GEOID_NO_ERROR is returned.
 */

  int items_read = 0;
  char* file_name = 0;
  char* path_name = getenv( "MSPCCS_DATA" );
  long elevations_read = 0;
  long items_discarded = 0;
  long num = 0;
  FILE*  geoid_height_file;

  CCSThreadLock lock(&mutex);

/*  Check the environment for a user provided path, else current directory;   */
/*  Build a File Name, including specified or default path:                   */

  if (path_name != NULL)
  {
    file_name = new char[ strlen( path_name ) + 11 ];
    strcpy( file_name, path_name );
    strcat( file_name, "/" );
  }
  else
  {
    file_name = new char[ 21 ];
    strcpy( file_name, "../../data/" );
  }
  strcat( file_name, "egm96.grd" );

/*  Open the File READONLY, or Return Error Condition:                        */

  if ( ( geoid_height_file = fopen( file_name, "rb" ) ) == NULL )
  {
    delete [] file_name;
    file_name = 0;

    char message[256] = "";
    strcpy( message, ErrorMessages::geoidFileOpenError );
    strcat( message, ": egm96.grd\n" );
    throw CoordinateConversionException( message );
  }

/*  Skip the Header Line:                                                     */

  float egm96GeoidHeaderList[EGM96_HEADER_ITEMS];
  items_discarded = readBinary(
     egm96GeoidHeaderList, 4, EGM96_HEADER_ITEMS, geoid_height_file );
  
/*  Determine if header read properly, or NOT:                                */

  if( egm96GeoidHeaderList[0] !=  -90.0 ||
      egm96GeoidHeaderList[1] !=   90.0 ||
      egm96GeoidHeaderList[2] !=    0.0 ||
      egm96GeoidHeaderList[3] !=  360.0 ||
      egm96GeoidHeaderList[4] !=  SCALE_FACTOR_15_MINUTES ||
      egm96GeoidHeaderList[5] !=  SCALE_FACTOR_15_MINUTES ||
      items_discarded != EGM96_HEADER_ITEMS )
  {
    fclose( geoid_height_file );
    delete [] file_name;
    file_name = 0;

    char message[256] = "";
    strcpy( message, ErrorMessages::geoidFileParseError );
    strcat( message, ": egm96.grd\n" );
    throw CoordinateConversionException( message );
  }

/*  Extract elements from the file:                                           */
  egm96GeoidList = new float[EGM96_ELEVATIONS];
  elevations_read = readBinary(
     egm96GeoidList, 4, EGM96_ELEVATIONS, geoid_height_file );

  fclose( geoid_height_file );
  geoid_height_file = 0;

  delete [] file_name;
  file_name = 0;
}


void GeoidLibrary::initializeEGM84Geoid()
{
/*
 * The function initializeEGM84Geoid reads geoid separation data from a file in
 * the current directory and builds the geoid separation table from it.
 * If the separation file can not be found or accessed, an error code of
 * GEOID_FILE_OPEN_ERROR is returned, If the separation file is incomplete
 * or improperly formatted, an error code of GEOID_INITIALIZE_ERROR is returned,
 * otherwise GEOID_NO_ERROR is returned.
 */

  int items_read = 0;
  char* file_name = 0;
  char* path_name = getenv( "MSPCCS_DATA" );
  long elevations_read = 0;
  long num = 0;
  FILE*  geoid_height_file;

  CCSThreadLock lock(&mutex);

/*  Check the environment for a user provided path, else current directory;   */
/*  Build a File Name, including specified or default path:                   */

  if (path_name != NULL)
  {
    file_name = new char[ strlen( path_name ) + 11 ];
    strcpy( file_name, path_name );
    strcat( file_name, "/" );
  }
  else
  {
    file_name =new char[ 21 ];
    strcpy( file_name, "../../data/" );
  }
  strcat( file_name, "egm84.grd" );

/*  Open the File READONLY, or Return Error Condition:                        */

  if( ( geoid_height_file = fopen( file_name, "rb" ) ) == NULL )
  {
    delete [] file_name;
    file_name = 0;

    char message[256] = "";
    strcpy( message, ErrorMessages::geoidFileOpenError );
    strcat( message, ": egm84.grd\n" );
    throw CoordinateConversionException( message );
  }


  /*  Extract elements from the file:                     */
  egm84GeoidList = new float[EGM84_ELEVATIONS];
  elevations_read = readBinary(
     egm84GeoidList, 4, EGM84_ELEVATIONS, geoid_height_file );

  fclose( geoid_height_file );

  delete [] file_name;
  file_name = 0;
}

void GeoidLibrary::initializeEGM84ThirtyMinGeoid()
{
/*
 * The function initializeEGM84ThirtyMinGeoid reads geoid separation data from 
 * a file in the current directory and builds the geoid separation table from it.
 * If the separation file can not be found or accessed, an error code of
 * GEOID_FILE_OPEN_ERROR is returned, If the separation file is incomplete
 * or improperly formatted, an error code of GEOID_INITIALIZE_ERROR is returned,
 * otherwise GEOID_NO_ERROR is returned.
 */

  int items_read = 0;
  char* file_name = 0;
  char* path_name = getenv( "MSPCCS_DATA" );
  long elevations_read = 0;
  long num = 0;
  FILE*  geoid_height_file;

  CCSThreadLock lock(&mutex);

/*  Check the environment for a user provided path, else current directory;   */
/*  Build a File Name, including specified or default path:                   */

  if (path_name != NULL)
  {
    file_name = new char[ strlen( path_name ) + 12 ]; 
    strcpy( file_name, path_name );
    strcat( file_name, "/" );
  }
  else
  {
    file_name =new char[ 22 ]; 
    strcpy( file_name, "../../data/" );
  }
  strcat( file_name, "wwgrid.bin" );

/*  Open the File READONLY, or Return Error Condition:                        */

  if( ( geoid_height_file = fopen( file_name, "rb" ) ) == NULL )
  {
    delete [] file_name;
    file_name = 0;

    char message[256] = "";
    strcpy( message, ErrorMessages::geoidFileOpenError );
    strcat( message, ": wwgrid.bin\n" );
    throw CoordinateConversionException( message );
  }


/*  Extract elements from the file:                                           */

  egm84ThirtyMinGeoidList = new double[EGM84_30_MIN_ELEVATIONS];
  elevations_read = readBinary(
     egm84ThirtyMinGeoidList, 8, EGM84_30_MIN_ELEVATIONS, geoid_height_file );

  fclose( geoid_height_file );

  delete [] file_name;
  file_name = 0;
}

void GeoidLibrary::bilinearInterpolateDoubleHeights(
   double longitude,
   double latitude,
   double scale_factor,
   int num_cols,
   int num_rows,
   double *height_buffer,
   double *delta_height )
{
/*
 * The private function bilinearInterpolateDoubleHeights returns the height of the
 * WGS84 geoid above or below the WGS84 ellipsoid, at the
 * specified geodetic coordinates, using a grid of height adjustments
 * and the bilinear interpolation method.
 *
 *    longitude           : Geodetic longitude in radians          (input)
 *    latitude            : Geodetic latitude in radians           (input)
 *    scale_factor        : Grid scale factor                      (input)
 *    num_cols            : Number of columns in grid              (input)
 *    num_rows            : Number of rows in grid                 (input)
 *    height_buffer       : Grid of height adjustments, doubles    (input)
 *    delta_height        : Height Adjustment, in meters.          (output)
 *
 */

  int index;
  int post_x, post_y;
  double offset_x, offset_y;
  double delta_x, delta_y;
  double _1_minus_delta_x, _1_minus_delta_y;
  double latitude_dd, longitude_dd;
  double height_se, height_sw, height_ne, height_nw;
  double w_sw, w_se, w_ne, w_nw;
  double south_lat, west_lon;
  int end_index = 0;
  int max_index = num_rows * num_cols - 1;
  char errorStatus[50] = "";

  if( ( latitude < -PI_OVER_2 ) || ( latitude > PI_OVER_2 ) )
  { /* Latitude out of range */
    strcat( errorStatus, ErrorMessages::latitude );
  }
  if( ( longitude < -PI ) || ( longitude > TWO_PI ) )
  { /* Longitude out of range */
    strcat( errorStatus, ErrorMessages::longitude );
  }

  if( strlen( errorStatus ) > 0)
    throw CoordinateConversionException( errorStatus );

  latitude_dd  = latitude  * _180_OVER_PI;
  longitude_dd = longitude * _180_OVER_PI;

  /*  Compute X and Y Offsets into Geoid Height Array:                          */

  if( longitude_dd < 0.0 )
  {
    offset_x = ( longitude_dd + 360.0 ) / scale_factor;
  }
  else
  {
    offset_x = longitude_dd / scale_factor;
  }
  offset_y = ( 90 - latitude_dd ) / scale_factor;

  /*  Find Four Nearest Geoid Height Cells for specified latitude, longitude;   */
  /*  Assumes that (0,0) of Geoid Height Array is at Northwest corner:          */

  post_x = ( int )( offset_x );
  if( ( post_x + 1 ) == num_cols )
    post_x--;
  post_y = ( int )( offset_y + 1.0e-11 );
  if( ( post_y + 1 ) == num_rows )
   post_y--;

  // NW Height
  index = post_y * num_cols + post_x;
  if( index < 0 )
    height_nw = height_buffer[ 0 ];
  else if( index > max_index )
    height_nw = height_buffer[ max_index ];
  else
    height_nw = height_buffer[ index ];
  // NE Height
  end_index = index + 1;
  if( end_index > max_index )
    height_ne  = height_buffer[ max_index ];
  else
    height_ne  = height_buffer[ end_index ];

  // SW Height
  index = ( post_y + 1 ) * num_cols + post_x;  
  if( index < 0 )
    height_sw = height_buffer[ 0 ];
  else if( index > max_index )
    height_sw = height_buffer[ max_index ];
  else
    height_sw = height_buffer[ index ];

  // SE Height
  end_index = index + 1;
  if( end_index > max_index )
    height_se  = height_buffer[ max_index ];
  else
    height_se  = height_buffer[ end_index ];

  west_lon = post_x * scale_factor;

  // North latitude - scale_factor
  south_lat = ( 90 - ( post_y * scale_factor ) ) - scale_factor;

  /*  Perform Bi-Linear Interpolation to compute Height above Ellipsoid:     */

  if( longitude_dd < 0.0 )
    delta_x = ( longitude_dd + 360.0 - west_lon ) / scale_factor;
  else
    delta_x = ( longitude_dd - west_lon ) / scale_factor;
  delta_y = ( latitude_dd - south_lat ) / scale_factor;

  _1_minus_delta_x = 1 - delta_x;
  _1_minus_delta_y = 1 - delta_y;

  w_sw = _1_minus_delta_x * _1_minus_delta_y;
  w_se = delta_x * _1_minus_delta_y;
  w_ne = delta_x * delta_y;
  w_nw = _1_minus_delta_x * delta_y;

  *delta_height =
     height_sw * w_sw + height_se * w_se + height_ne * w_ne + height_nw * w_nw;
}


void GeoidLibrary::bilinearInterpolate(
   double longitude,
   double latitude,
   double scale_factor,
   int num_cols,
   int num_rows,
   float  *height_buffer,
   double *delta_height )
{
/*
 * The private function bilinearInterpolate returns the height of the
 * WGS84 geoid above or below the WGS84 ellipsoid, at the
 * specified geodetic coordinates, using a grid of height adjustments
 * and the bilinear interpolation method.
 *
 *    longitude           : Geodetic longitude in radians          (input)
 *    latitude            : Geodetic latitude in radians           (input)
 *    scale_factor        : Grid scale factor                      (input)
 *    num_cols            : Number of columns in grid              (input)
 *    num_rows            : Number of rows in grid                 (input)
 *    height_buffer       : Grid of height adjustments, floats     (input)
 *    delta_height        : Height Adjustment, in meters.          (output)
 *
 */

  int index;
  int post_x, post_y;
  double offset_x, offset_y;
  double delta_x, delta_y;
  double _1_minus_delta_x, _1_minus_delta_y;
  double latitude_dd, longitude_dd;
  double height_se, height_sw, height_ne, height_nw;
  double w_sw, w_se, w_ne, w_nw;
  double south_lat, west_lon;
  int end_index = 0;
  int max_index = num_rows * num_cols - 1;
  char errorStatus[50] = "";

  if( ( latitude < -PI_OVER_2 ) || ( latitude > PI_OVER_2 ) )
  { /* Latitude out of range */
    strcat( errorStatus, ErrorMessages::latitude );
  }
  if( ( longitude < -PI ) || ( longitude > TWO_PI ) )
  { /* Longitude out of range */
    strcat( errorStatus, ErrorMessages::longitude );
  }

  if( strlen( errorStatus ) > 0)
    throw CoordinateConversionException( errorStatus );

  latitude_dd  = latitude  * _180_OVER_PI;
  longitude_dd = longitude * _180_OVER_PI;

  /*  Compute X and Y Offsets into Geoid Height Array:                        */

  if( longitude_dd < 0.0 )
  {
    offset_x = ( longitude_dd + 360.0 ) / scale_factor;
  }
  else
  {
    offset_x = longitude_dd / scale_factor;
  }
  offset_y = ( 90 - latitude_dd ) / scale_factor;

  /*  Find Four Nearest Geoid Height Cells for specified latitude, longitude; */
  /*  Assumes that (0,0) of Geoid Height Array is at Northwest corner:        */

  post_x = ( int )( offset_x );
  if( ( post_x + 1 ) == num_cols )
    post_x--;
  post_y = ( int )( offset_y + 1.0e-11 );
  if( ( post_y + 1 ) == num_rows )
   post_y--;

  // NW Height
  index = post_y * num_cols + post_x;
  if( index < 0 )
    height_nw = height_buffer[ 0 ];
  else if( index > max_index )
    height_nw = height_buffer[ max_index ];
  else
    height_nw = height_buffer[ index ];
  // NE Height
  end_index = index + 1;
  if( end_index > max_index )
    height_ne  = height_buffer[ max_index ];
  else
    height_ne  = height_buffer[ end_index ];

  // SW Height
  index = ( post_y + 1 ) * num_cols + post_x;  
  if( index < 0 )
    height_sw = height_buffer[ 0 ];
  else if( index > max_index )
    height_sw = height_buffer[ max_index ];
  else
    height_sw = height_buffer[ index ];

  // SE Height
  end_index = index + 1;
  if( end_index > max_index )
    height_se  = height_buffer[ max_index ];
  else
    height_se  = height_buffer[ end_index ];

  west_lon = post_x * scale_factor;

  // North latitude - scale_factor
  south_lat = ( 90 - ( post_y * scale_factor ) ) - scale_factor;

  /*  Perform Bi-Linear Interpolation to compute Height above Ellipsoid:    */

  if( longitude_dd < 0.0 )
    delta_x = ( longitude_dd + 360.0 - west_lon ) / scale_factor;
  else
    delta_x = ( longitude_dd - west_lon ) / scale_factor;
  delta_y = ( latitude_dd - south_lat ) / scale_factor;

  _1_minus_delta_x = 1 - delta_x;
  _1_minus_delta_y = 1 - delta_y;

  w_sw = _1_minus_delta_x * _1_minus_delta_y;
  w_se = delta_x * _1_minus_delta_y;
  w_ne = delta_x * delta_y;
  w_nw = _1_minus_delta_x * delta_y;

  *delta_height =
     height_sw * w_sw + height_se * w_se + height_ne * w_ne + height_nw * w_nw;
}


void GeoidLibrary::naturalSplineInterpolate(
   double longitude,
   double latitude,
   double scale_factor,
   int num_cols,
   int num_rows,
   int max_index,
   float  *height_buffer,
   double *delta_height )
{
/*
 * The private function naturalSplineInterpolate returns the height of the
 * WGS84 geoid above or below the WGS84 ellipsoid, at the
 * specified geodetic coordinates, using a grid of height adjustments
 * and the natural spline interpolation method.
 *
 *    longitude           : Geodetic longitude in radians          (input)
 *    latitude            : Geodetic latitude in radians           (input)
 *    scale_factor        : Grid scale factor                      (input)
 *    num_cols            : Number of columns in grid              (input)
 *    num_rows            : Number of rows in grid                 (input)
 *    height_buffer       : Grid of height adjustments             (input)
 *    DeltaHeight         : Height Adjustment, in meters.          (output)
 *
 */

  int index;
  int post_x, post_y;
  int temp_offset_x, temp_offset_y;
  double offset_x, offset_y;
  double delta_x, delta_y;
  double delta_x2, delta_y2;
  double _1_minus_delta_x, _1_minus_delta_y;
  double _1_minus_delta_x2, _1_minus_delta_y2;
  double  _3_minus_2_times_1_minus_delta_x, _3_minus_2_times_1_minus_delta_y;
  double _3_minus_2_times_delta_x, _3_minus_2_times_delta_y;
  double latitude_dd, longitude_dd;
  double height_se, height_sw, height_ne, height_nw;
  double w_sw, w_se, w_ne, w_nw;
  double south_lat, west_lon;
  int end_index = 0;
  double skip_factor = 1.0;
  char errorStatus[50] = "";

  if( ( latitude < -PI_OVER_2 ) || ( latitude > PI_OVER_2 ) )
  { /* latitude out of range */
    strcat( errorStatus, ErrorMessages::latitude );
  }
  if( ( longitude < -PI ) || ( longitude > TWO_PI ) )
  { /* longitude out of range */
    strcat( errorStatus, ErrorMessages::longitude );
  }

  if( strlen( errorStatus ) > 0)
    throw CoordinateConversionException( errorStatus );

  latitude_dd  = latitude  * _180_OVER_PI;
  longitude_dd = longitude * _180_OVER_PI;

  /*  Compute X and Y Offsets into Geoid Height Array:                        */

  if( longitude_dd < 0.0 )
  {
    offset_x = ( longitude_dd + 360.0 ) / scale_factor;
  }
  else
  {
    offset_x = longitude_dd / scale_factor;
  }
  offset_y = ( 90.0 - latitude_dd ) / scale_factor;

  /*  Find Four Nearest Geoid Height Cells for specified latitude, longitude; */
  /*  Assumes that (0,0) of Geoid Height Array is at Northwest corner:        */

  post_x = ( int ) offset_x;
  if ( ( post_x + 1 ) == num_cols)
    post_x--;
  post_y = ( int )( offset_y + 1.0e-11 );
  if ( ( post_y + 1 ) == num_rows)
    post_y--;

  if( scale_factor == SCALE_FACTOR_30_MINUTES )
  {
    skip_factor = 2.0;
    num_rows = EGM96_ROWS;
    num_cols = EGM96_COLS;
  }
  else if( scale_factor == SCALE_FACTOR_1_DEGREE )
  {
    skip_factor = 4.0;
    num_rows = EGM96_ROWS;
    num_cols = EGM96_COLS;
  }
  else if( scale_factor == SCALE_FACTOR_2_DEGREES )
  {
    skip_factor = 8.0;
    num_rows = EGM96_ROWS;
    num_cols = EGM96_COLS;
  }

  temp_offset_x = ( int )( post_x * skip_factor );
  temp_offset_y = ( int )( post_y * skip_factor + 1.0e-11 );
  if ( ( temp_offset_x + 1 ) == num_cols )
    temp_offset_x--;
  if ( ( temp_offset_y + 1 ) == num_rows )
    temp_offset_y--;

  // NW Height
  index = ( int )( temp_offset_y * num_cols + temp_offset_x );
  if( index < 0 )
    height_nw = height_buffer[ 0 ];
  else if( index > max_index )
    height_nw = height_buffer[ max_index ];
  else
    height_nw = height_buffer[ index ];
  // NE Height
  end_index = index + (int)skip_factor;
  if( end_index < 0 )
    height_ne = height_buffer[ 0 ];
  else if( end_index > max_index )
    height_ne = height_buffer[ max_index ];
  else
    height_ne = height_buffer[ end_index ];

  // SW Height
  index = ( int )( ( temp_offset_y + skip_factor ) * num_cols + temp_offset_x );
  if( index < 0 )
    height_sw = height_buffer[ 0 ];
  else if( index > max_index )
    height_sw = height_buffer[ max_index ];
  else
    height_sw = height_buffer[ index ];
  // SE Height
  end_index = index + (int)skip_factor;
  if( end_index < 0 )
    height_se = height_buffer[ 0 ];
  else if( end_index > max_index )
    height_se = height_buffer[ max_index ];
  else
    height_se = height_buffer[ end_index ];

  west_lon = post_x * scale_factor;
  
  // North latitude - scale_factor
  south_lat = ( 90 - ( post_y * scale_factor ) ) - scale_factor;   

  /*  Perform Non-Linear Interpolation to compute Height above Ellipsoid:     */

  if( longitude_dd < 0.0 )
    delta_x = ( longitude_dd + 360.0 - west_lon ) / scale_factor;
  else
    delta_x = ( longitude_dd - west_lon ) / scale_factor;
  delta_y = ( latitude_dd - south_lat ) / scale_factor;

  delta_x2 = delta_x * delta_x;
  delta_y2 = delta_y * delta_y;

  _1_minus_delta_x = 1 - delta_x;
  _1_minus_delta_y = 1 - delta_y;

  _1_minus_delta_x2 = _1_minus_delta_x * _1_minus_delta_x;
  _1_minus_delta_y2 = _1_minus_delta_y * _1_minus_delta_y;

  _3_minus_2_times_1_minus_delta_x = 3 - 2 * _1_minus_delta_x;
  _3_minus_2_times_1_minus_delta_y = 3 - 2 * _1_minus_delta_y;

  _3_minus_2_times_delta_x = 3 - 2 * delta_x;
  _3_minus_2_times_delta_y = 3 - 2 * delta_y;

  w_sw = _1_minus_delta_x2 * _1_minus_delta_y2 * 
     ( _3_minus_2_times_1_minus_delta_x * _3_minus_2_times_1_minus_delta_y );

  w_se = delta_x2 * _1_minus_delta_y2 * 
     ( _3_minus_2_times_delta_x * _3_minus_2_times_1_minus_delta_y );

  w_ne = delta_x2 * delta_y2 * 
     ( _3_minus_2_times_delta_x * _3_minus_2_times_delta_y );

  w_nw = _1_minus_delta_x2 * delta_y2 * 
     (  _3_minus_2_times_1_minus_delta_x * _3_minus_2_times_delta_y );

  *delta_height = 
     height_sw * w_sw + height_se * w_se + height_ne * w_ne + height_nw * w_nw;
}

// CLASSIFICATION: UNCLASSIFIED