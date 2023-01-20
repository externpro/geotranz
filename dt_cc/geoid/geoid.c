/* RSC IDENTIFIER:  Geoid
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
 *
 */


/***************************************************************************/
/*
 *                               INCLUDES
 */
#include <stdio.h>   /* standard C input/output library */
#include <stdlib.h>  /* standard C library */
#include "geoid.h"
#include "threads.h"


/***************************************************************************/
/*
 *                               DEFINES
 */

#define PI         3.14159265358979323e0 /* PI */
#define PI_OVER_2  PI / 2.0
#define TWO_PI     2.0 * PI
#define _180_OVER_PI  (180.0 / PI)
#define EGM96_COLS  1441                 /* 360 degrees of longitude at 15 minute spacing */
#define EGM96_ROWS   721                 /* 180 degrees of latitude  at 15 minute spacing */
#define EGM84_COLS    37                 /* 360 degrees of longitude at 10 degree spacing */
#define EGM84_ROWS    19                 /* 180 degrees of latitude  at 10 degree spacing */
#define EGM96_HEADER_ITEMS 6             /* min, max lat, min, max long, lat, long spacing*/
#define SCALE_FACTOR_15_MINUTES .25      /* 4 grid cells per degree at 15 minute spacing  */
#define SCALE_FACTOR_10_DEGREES  10      /* 1 / 10.0 grid cells per degree at 10 degree spacing */
#define SCALE_FACTOR_30_MINUTES  .5      /* 2 grid cells per degree at 30 minute spacing */
#define SCALE_FACTOR_1_DEGREE     1      /* 1 grid cell per degree at 1 degree spacing */
#define SCALE_FACTOR_2_DEGREES    2      /* 1 / 2 grid cells per degree at 2 degree spacing */
#define EGM96_ELEVATIONS   EGM96_COLS * EGM96_ROWS
#define EGM84_ELEVATIONS   EGM84_COLS * EGM84_ROWS
#define EGM96_INSET_AREAS 53


/***************************************************************************/
/*
 *                               GLOBALS
 */

FILE*  geoid_height_file;

/* Array of EGM96 elevations */
float egm96_height_grid[EGM96_ELEVATIONS];
/* Array of EGM84 elevations */
float egm84_height_grid[EGM84_ELEVATIONS];

/* indicates successful initialization */
static long geoid_initialized = 0;

Thread_Mutex geoid_96_mutex;
Thread_Mutex geoid_84_mutex;

typedef struct EGM96_Variable_Grid_Values
{
  double min_lat;        /* Min cell latitude */
  double max_lat;        /* Max cell latitude */
  double min_lon;        /* Min cell longitude */
  double max_lon;        /* Max cell latitude */
} EGM96_Variable_Grid; /* defines the egm96 variable grid */


/* Table of EGM96 variable grid 30 minute inset areas */
static const EGM96_Variable_Grid EGM96_Variable_Grid_Table[EGM96_INSET_AREAS] =
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


/***************************************************************************/
/*
 *                              FUNCTIONS
 */

float read_float( int *num_read )
/*
 * The private function read_float returns the geoid height
 * read from the geoid file. 4 bytes are read from the file and,
 * if necessary, the bytes are swapped.
 *
 *    NumRead             : Number of heights read from file         (output)
 *
 */
{
  float result;
  char* swap = ( char* )&result;
  char temp;

  *num_read = fread( swap, 4, 1, geoid_height_file );
#ifdef LITTLE_ENDIAN
  temp = swap[0];
  swap[0] = swap[3];
  swap[3] = temp;
  temp = swap[1];
  swap[1] = swap[2];
  swap[2] = temp;
#endif
  return result;
}


long Initialize_EGM96_Geoid()
/*
 * The function Initialize_EGM96_Geoid reads geoid separation data from the egm96.grd
 *  file in the current directory and builds a geoid separation table from it.
 * If the separation file can not be found or accessed, an error code of
 * GEOID_FILE_OPEN_ERROR is returned, If the separation file is incomplete
 * or improperly formatted, an error code of GEOID_INITIALIZE_ERROR is returned,
 * otherwise GEOID_NO_ERROR is returned.
 */
{
  int items_read = 0;
  char* file_name = 0;
  char* path_name = getenv( "GEOTRANS_DATA" );
  long elevations_read = 0;
  long items_discarded = 0;
  long num = 0;
  long mutex_error = THREADS_NO_ERROR;

#ifdef WIN32
  mutex_error = Threads_Create_Mutex( "Geoid_Mutex", &geoid_96_mutex );
#else
  mutex_error = Threads_Create_Mutex( &geoid_96_mutex );
#endif

  if( !mutex_error )
    mutex_error = Threads_Lock_Mutex( geoid_96_mutex );

/*  Check the environment for a user provided path, else current directory;   */
/*  Build a File Name, including specified or default path:                   */

  if (path_name != NULL)
  {
    file_name = calloc( strlen( path_name ) + 11, sizeof( char ) );
    strcpy( file_name, path_name );
    strcat( file_name, "/" );
  }
  else
  {
    file_name = calloc( 18, sizeof( char ) );
    strcpy( file_name, "../data/" );
  }
  strcat( file_name, "egm96.grd" );

/*  Open the File READONLY, or Return Error Condition:                        */

  if ( ( geoid_height_file = fopen( file_name, "rb" ) ) == NULL )
  {
    free( file_name );
    file_name = 0;

    return ( GEOID_FILE_OPEN_ERROR );
  }

/*  Skip the Header Line:                                                     */

  while ( num < EGM96_HEADER_ITEMS )
  {
    if ( feof( geoid_height_file ) ) break;
    if ( ferror( geoid_height_file ) ) break;
    egm96_height_grid[num] = read_float( &items_read );
    items_discarded += items_read;
    num++;
  }

/*  Determine if header read properly, or NOT:                                */

  if (egm96_height_grid[0] !=  -90.0 ||
      egm96_height_grid[1] !=   90.0 ||
      egm96_height_grid[2] !=    0.0 ||
      egm96_height_grid[3] !=  360.0 ||
      egm96_height_grid[4] !=  SCALE_FACTOR_15_MINUTES ||
      egm96_height_grid[5] !=  SCALE_FACTOR_15_MINUTES ||
      items_discarded != EGM96_HEADER_ITEMS)
  {
    fclose( geoid_height_file );
    free( file_name );
    file_name = 0;
    return ( GEOID_INITIALIZE_ERROR );
  }

/*  Extract elements from the file:                                           */

  num = 0;
  while ( num < EGM96_ELEVATIONS )
  {
    if ( feof( geoid_height_file ) ) break;
    if ( ferror( geoid_height_file ) ) break;
    egm96_height_grid[num] = read_float ( &items_read );
    elevations_read += items_read;
    num++;
  }

/*  Determine if all elevations of file read properly, or NOT:                */

  if ( elevations_read != EGM96_ELEVATIONS )
  {
    fclose(geoid_height_file);
    free( file_name );
    file_name = 0;
    return ( GEOID_INITIALIZE_ERROR );
  }

  fclose( geoid_height_file );
  geoid_height_file = 0;

  if( !mutex_error )
    mutex_error = Threads_Unlock_Mutex( geoid_96_mutex );

  if( !mutex_error )
    Threads_Destroy_Mutex( geoid_96_mutex );

  free( file_name );
  file_name = 0;

  return ( GEOID_NO_ERROR );
}


long Initialize_EGM84_Geoid()
/*
 * The function Initialize_EGM84_Geoid reads geoid separation data from a file in
 * the current directory and builds the geoid separation table from it.
 * If the separation file can not be found or accessed, an error code of
 * GEOID_FILE_OPEN_ERROR is returned, If the separation file is incomplete
 * or improperly formatted, an error code of GEOID_INITIALIZE_ERROR is returned,
 * otherwise GEOID_NO_ERROR is returned.
 */
{
  int items_read = 0;
  char* file_name = 0;
  char* path_name = getenv( "GEOTRANS_DATA" );
  long elevations_read = 0;
  long num = 0;
  long mutex_error = THREADS_NO_ERROR;

#ifdef WIN32
  mutex_error = Threads_Create_Mutex( "Geoid84_Mutex", &geoid_84_mutex );
#else
  mutex_error = Threads_Create_Mutex( &geoid_84_mutex );
#endif

  if( !mutex_error )
    mutex_error = Threads_Lock_Mutex( geoid_84_mutex );

  /*  Check the environment for a user provided path, else current directory;   */
  /*  Build a File Name, including specified or default path:                   */

  if (path_name != NULL)
  {
    file_name = calloc( strlen( path_name ) + 11, sizeof( char ) );
    strcpy( file_name, path_name );
    strcat( file_name, "/" );
  }
  else
  {
    file_name = calloc( 18, sizeof( char ) );
    strcpy( file_name, "../data/" );
  }
  strcat( file_name, "egm84.grd" );

  /*  Open the File READONLY, or Return Error Condition:                        */

  if( ( geoid_height_file = fopen( file_name, "rb" ) ) == NULL )
  {
    free( file_name );
    file_name = 0;

    return ( GEOID_FILE_OPEN_ERROR );
  }


  /*  Extract elements from the file:                                           */

  num = 0;
  while( num < EGM84_ELEVATIONS )
  {
    if ( feof( geoid_height_file ) ) break;
    if ( ferror( geoid_height_file ) ) break;
    egm84_height_grid[num] = read_float( &items_read );

    elevations_read += items_read;
    num++;
  }


  /*  Determine if all elevations of file read properly, or NOT:                */

  if( ( elevations_read ) != EGM84_ELEVATIONS )
  {
    fclose( geoid_height_file );
    free( file_name );
    file_name = 0;
    return ( GEOID_INITIALIZE_ERROR );
  }

  fclose( geoid_height_file );

  if( !mutex_error )
    mutex_error = Threads_Unlock_Mutex( geoid_84_mutex );

  if( !mutex_error )
    Threads_Destroy_Mutex( geoid_84_mutex );

  free( file_name );
  file_name = 0;

  return ( GEOID_NO_ERROR );
}


long Initialize_Geoid()
/*
 * The function Initialize_Geoid reads geoid separation data from a file in
 * the current directory and builds the geoid separation table from it.
 * If the separation file can not be found or accessed, an error code of
 * GEOID_FILE_OPEN_ERROR is returned, If the separation file is incomplete
 * or improperly formatted, an error code of GEOID_INITIALIZE_ERROR is returned,
 * otherwise GEOID_NO_ERROR is returned.
 */
{
  long error_code = 0;


  if (geoid_initialized)
  {
    return GEOID_NO_ERROR;
  }

  error_code = Initialize_EGM96_Geoid();

  if( !error_code )
    error_code = Initialize_EGM84_Geoid();

  if( !error_code )
    geoid_initialized = 1;

  return error_code;
}


long BL_Interpolate( double latitude,
                     double longitude,
                     double scale_factor,
                     int num_cols,
                     int num_rows,
                     float height_buffer[],
                     double *delta_height )
/*
 * The private function BL_Interpolate returns the height of the
 * WGS84 geoid above or below the WGS84 ellipsoid, at the
 * specified geodetic coordinates, using a grid of height adjustments
 * and the bilinear interpolation method.
 *
 *    latitude            : Geodetic latitude in radians           (input)
 *    longitude           : Geodetic longitude in radians          (input)
 *    scale_factor        : Grid scale factor                      (input)
 *    num_cols            : Number of columns in grid              (input)
 *    num_rows            : Number of rows in grid                 (input)
 *    height_buffer       : Grid of height adjustments             (input)
 *    delta_height        : Height Adjustment, in meters.          (output)
 *
 */
{
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
  long error_code = 0;

  if( !geoid_initialized )
  {
    return ( GEOID_NOT_INITIALIZED_ERROR );
  }
  if( ( latitude < -PI_OVER_2 ) || ( latitude > PI_OVER_2 ) )
  { /* Latitude out of range */
    error_code |= GEOID_LAT_ERROR;
  }
  if( ( longitude < -PI ) || ( longitude > TWO_PI ) )
  { /* Longitude out of range */
    error_code |= GEOID_LON_ERROR;
  }

  if( !error_code )
  { /* no errors */
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

    /*  Perform Bi-Linear Interpolation to compute Height above Ellipsoid:        */

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

    *delta_height = height_sw * w_sw + height_se * w_se + height_ne * w_ne + height_nw * w_nw;
  }

  return error_code;
}


long NS_Interpolate( double latitude,
                     double longitude,
                     double scale_factor,
                     int num_cols,
                     int num_rows,
                     int max_index,
                     float height_buffer[],
                     double *delta_height )

/*
 * The private function NS_Interpolate returns the height of the
 * WGS84 geoid above or below the WGS84 ellipsoid, at the
 * specified geodetic coordinates, using a grid of height adjustments
 * and the natural spline interpolation method.
 *
 *    latitude            : Geodetic latitude in radians           (input)
 *    longitude           : Geodetic longitude in radians          (input)
 *    scale_factor        : Grid scale factor                      (input)
 *    num_cols            : Number of columns in grid              (input)
 *    num_rows            : Number of rows in grid                 (input)
 *    height_buffer       : Grid of height adjustments             (input)
 *    DeltaHeight         : Height Adjustment, in meters.          (output)
 *
 */
{
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
 // double num_columns = num_cols;
  long error_code = 0;

  if( !geoid_initialized )
  {
    return ( GEOID_NOT_INITIALIZED_ERROR );
  }
  if( ( latitude < -PI_OVER_2 ) || ( latitude > PI_OVER_2 ) )
  { /* latitude out of range */
    error_code |= GEOID_LAT_ERROR;
  }
  if( ( longitude < -PI ) || ( longitude > TWO_PI ) )
  { /* longitude out of range */
    error_code |= GEOID_LON_ERROR;
  }

  if( !error_code )
  { /* no errors */
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
    offset_y = ( 90.0 - latitude_dd ) / scale_factor;

    /*  Find Four Nearest Geoid Height Cells for specified latitude, longitude;   */
    /*  Assumes that (0,0) of Geoid Height Array is at Northwest corner:          */

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

    /*  Perform Non-Linear Interpolation to compute Height above Ellipsoid:        */

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

    w_sw = _1_minus_delta_x2 * _1_minus_delta_y2 * ( _3_minus_2_times_1_minus_delta_x * _3_minus_2_times_1_minus_delta_y );
    w_se = delta_x2 * _1_minus_delta_y2 * ( _3_minus_2_times_delta_x * _3_minus_2_times_1_minus_delta_y );
    w_ne = delta_x2 * delta_y2 * ( _3_minus_2_times_delta_x * _3_minus_2_times_delta_y );
    w_nw = _1_minus_delta_x2 * delta_y2 * (  _3_minus_2_times_1_minus_delta_x * _3_minus_2_times_delta_y );

    *delta_height = height_sw * w_sw + height_se * w_se + height_ne * w_ne + height_nw * w_nw;
  }

  return error_code;
}


long Convert_Ellipsoid_To_Geoid_Height( double Latitude,
                                        double Longitude,
                                        double Ellipsoid_Height,
                                        double *Geoid_Height )
/*
 * The function Convert_Ellipsoid_To_Geoid_Height converts the specified WGS84
 * ellipsoid height at the specified geodetic coordinates to the equivalent
 * geoid height, using the EGM96 gravity model and the bilinear interpolation method.
 *
 *    Latitude            : Geodetic latitude in radians           (input)
 *    Longitude           : Geodetic longitude in radians          (input)
 *    Ellipsoid_Height    : Ellipsoid height, in meters            (input)
 *    Geoid_Height        : Geoid height, in meters.               (output)
 *
 */
{
  double  delta_height;
  long error_code;

  error_code = BL_Interpolate( Latitude, Longitude, SCALE_FACTOR_15_MINUTES, EGM96_COLS, EGM96_ROWS, egm96_height_grid, &delta_height );
  *Geoid_Height = Ellipsoid_Height - delta_height;

  return error_code;
}


long Convert_Ellipsoid_To_MSL_EGM96_VG_NS_Height( double Latitude,
                                                  double Longitude,
                                                  double Ellipsoid_Height,
                                                  double *Geoid_Height )
/*
 * The function Convert_Ellipsoid_To_MSL_EGM96_VG_NS_Height converts the specified WGS84
 * ellipsoid height at the specified geodetic coordinates to the equivalent
 * geoid height, using the EGM96 gravity model and the natural spline interpolation method..
 *
 *    Latitude            : Geodetic latitude in radians           (input)
 *    Longitude           : Geodetic longitude in radians          (input)
 *    Ellipsoid_Height    : Ellipsoid height, in meters            (input)
 *    Geoid_Height        : Geoid height, in meters.               (output)
 *
 */
{
  int i = 0;
  int num_cols = EGM96_COLS;
  int num_rows = EGM96_ROWS;
  double latitude_degrees = Latitude * _180_OVER_PI;
  double longitude_degrees = Longitude * _180_OVER_PI;
  double scale_factor = SCALE_FACTOR_15_MINUTES;
  double delta_height;
  long found = 0;
  long error_code;

  if( longitude_degrees < 0.0 )
    longitude_degrees += 360.0;

  while( !found && i < EGM96_INSET_AREAS )
  {
    if( ( latitude_degrees >= EGM96_Variable_Grid_Table[i].min_lat ) && ( longitude_degrees >= EGM96_Variable_Grid_Table[i].min_lon ) &&
        ( latitude_degrees < EGM96_Variable_Grid_Table[i].max_lat ) && ( longitude_degrees < EGM96_Variable_Grid_Table[i].max_lon ) )
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

  error_code = NS_Interpolate( Latitude, Longitude, scale_factor, num_cols, num_rows, EGM96_ELEVATIONS-1, egm96_height_grid, &delta_height );
  *Geoid_Height = Ellipsoid_Height - delta_height;

  return error_code;
}


long Convert_Ellipsoid_To_MSL_EGM84_10D_BL_Height( double Latitude,
                                                   double Longitude,
                                                   double Ellipsoid_Height,
                                                   double *Geoid_Height )
/*
 * The function Convert_Ellipsoid_To_MSL_EGM84_10D_BL_Height converts the specified WGS84
 * ellipsoid height at the specified geodetic coordinates to the equivalent
 * geoid height, using the EGM84 gravity model and the bilinear interpolation method..
 *
 *    Latitude            : Geodetic latitude in radians           (input)
 *    Longitude           : Geodetic longitude in radians          (input)
 *    Ellipsoid_Height    : Ellipsoid height, in meters            (input)
 *    Geoid_Height        : Geoid height, in meters.               (output)
 *
 */
{
  double delta_height;
  long error_code;

  error_code = BL_Interpolate( Latitude, Longitude, SCALE_FACTOR_10_DEGREES, EGM84_COLS, EGM84_ROWS, egm84_height_grid, &delta_height );
  *Geoid_Height = Ellipsoid_Height - delta_height;

  return error_code;
}


long Convert_Ellipsoid_To_MSL_EGM84_10D_NS_Height( double Latitude,
                                                   double Longitude,
                                                   double Ellipsoid_Height,
                                                   double *Geoid_Height )
/*
 * The function Convert_Ellipsoid_To_MSL_EGM84_10D_NS_Height converts the specified WGS84
 * ellipsoid height at the specified geodetic coordinates to the equivalent
 * geoid height, using the EGM84 gravity model and the natural spline interpolation method..
 *
 *    Latitude            : Geodetic latitude in radians           (input)
 *    Longitude           : Geodetic longitude in radians          (input)
 *    Ellipsoid_Height    : Ellipsoid height, in meters            (input)
 *    Geoid_Height        : Geoid height, in meters.               (output)
 *
 */
{
  double delta_height;
  long error_code;

  error_code = NS_Interpolate( Latitude, Longitude, SCALE_FACTOR_10_DEGREES, EGM84_COLS, EGM84_ROWS, EGM84_ELEVATIONS-1, egm84_height_grid, &delta_height );
  *Geoid_Height = Ellipsoid_Height - delta_height;

  return error_code;
}


long Convert_Geoid_To_Ellipsoid_Height( double Latitude,
                                        double Longitude,
                                        double Geoid_Height,
                                        double *Ellipsoid_Height )
/*
 * The function Convert_Geoid_To_Ellipsoid_Height converts the specified WGS84
 * geoid height at the specified geodetic coordinates to the equivalent
 * ellipsoid height, using the EGM96 gravity model and the bilinear interpolation method.
 *
 *    Latitude            : Geodetic latitude in radians           (input)
 *    Longitude           : Geodetic longitude in radians          (input)
 *    Geoid_Height        : Geoid height, in meters.               (input)
 *    Ellipsoid_Height    : Ellipsoid height, in meters            (output)
 *
 */
{
  double  delta_height;
  long error_code;

  error_code = BL_Interpolate( Latitude, Longitude, SCALE_FACTOR_15_MINUTES, EGM96_COLS, EGM96_ROWS, egm96_height_grid, &delta_height );
  *Ellipsoid_Height = Geoid_Height + delta_height;

  return error_code;
}


long Convert_MSL_EGM96_VG_NS_To_Ellipsoid_Height( double Latitude,
                                                  double Longitude,
                                                  double Geoid_Height,
                                                  double *Ellipsoid_Height )
/*
 * The function Convert_MSL_EGM96_VG_NS_To_Ellipsoid_Height converts the specified WGS84
 * geoid height at the specified geodetic coordinates to the equivalent
 * ellipsoid height, using the EGM96 gravity model and the natural spline interpolation method.
 *
 *    Latitude            : Geodetic latitude in radians           (input)
 *    Longitude           : Geodetic longitude in radians          (input)
 *    Ellipsoid_Height    : Ellipsoid height, in meters            (input)
 *    Geoid_Height        : Geoid height, in meters.               (output)
 *
 */
{
  int i = 0;
  int num_cols = EGM96_COLS;
  int num_rows = EGM96_ROWS;
  double latitude_degrees = Latitude * _180_OVER_PI;
  double longitude_degrees = Longitude * _180_OVER_PI;
  double scale_factor = SCALE_FACTOR_15_MINUTES;
  double delta_height;
  long found = 0;
  long error_code;

  if( longitude_degrees < 0.0 )
    longitude_degrees += 360.0;

  while( !found && i < EGM96_INSET_AREAS )
  {
    if( ( latitude_degrees >= EGM96_Variable_Grid_Table[i].min_lat ) && ( longitude_degrees >= EGM96_Variable_Grid_Table[i].min_lon ) &&
        ( latitude_degrees < EGM96_Variable_Grid_Table[i].max_lat ) && ( longitude_degrees < EGM96_Variable_Grid_Table[i].max_lon ) )
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

  error_code = NS_Interpolate( Latitude, Longitude, scale_factor, num_cols, num_rows, EGM96_ELEVATIONS-1, egm96_height_grid, &delta_height );
  *Ellipsoid_Height = Geoid_Height + delta_height;

  return error_code;
}


long Convert_MSL_EGM84_10D_BL_To_Ellipsoid_Height( double Latitude,
                                                   double Longitude,
                                                   double Geoid_Height,
                                                   double *Ellipsoid_Height )
/*
 * The function Convert_MSL_EGM84_10D_BL_To_Ellipsoid_Height converts the specified WGS84
 * geoid height at the specified geodetic coordinates to the equivalent
 * ellipsoid height, using the EGM84 gravity model and the bilinear interpolation method.
 *
 *    Latitude            : Geodetic latitude in radians           (input)
 *    Longitude           : Geodetic longitude in radians          (input)
 *    Ellipsoid_Height    : Ellipsoid height, in meters            (input)
 *    Geoid_Height        : Geoid height, in meters.               (output)
 *
 */
{
  double  delta_height;
  long error_code;

  error_code = BL_Interpolate( Latitude, Longitude, SCALE_FACTOR_10_DEGREES, EGM84_COLS, EGM84_ROWS, egm84_height_grid, &delta_height );
  *Ellipsoid_Height = Geoid_Height + delta_height;

  return error_code;
}


long Convert_MSL_EGM84_10D_NS_To_Ellipsoid_Height( double Latitude,
                                                   double Longitude,
                                                   double Geoid_Height,
                                                   double *Ellipsoid_Height )
/*
 * The function Convert_MSL_EGM84_10D_NS_To_Ellipsoid_Height converts the specified WGS84
 * geoid height at the specified geodetic coordinates to the equivalent
 * ellipsoid height, using the EGM84 gravity model and the natural spline interpolation method.
 *
 *    Latitude            : Geodetic latitude in radians           (input)
 *    Longitude           : Geodetic longitude in radians          (input)
 *    Ellipsoid_Height    : Ellipsoid height, in meters            (input)
 *    Geoid_Height        : Geoid height, in meters.               (output)
 *
 */
{
  double  delta_height;
  long error_code;

  error_code = NS_Interpolate( Latitude, Longitude, SCALE_FACTOR_10_DEGREES, EGM84_COLS, EGM84_ROWS, EGM84_ELEVATIONS-1, egm84_height_grid, &delta_height );
  *Ellipsoid_Height = Geoid_Height + delta_height;

  return error_code;
}


