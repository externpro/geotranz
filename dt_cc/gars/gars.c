/***************************************************************************/
/* RSC IDENTIFIER: GARS
 *
 * ABSTRACT
 *
 *    This component provides conversions from Geodetic coordinates (latitude
 *    and longitude in radians) to a GARS coordinate string.
 *
 * ERROR HANDLING
 *
 *    This component checks parameters for valid values.  If an invalid value
 *    is found, the error code is combined with the current error code using 
 *    the bitwise or.  This combining allows multiple error codes to be
 *    returned. The possible error codes are:
 *
 *          GARS_NO_ERROR          : No errors occurred in function
 *          GARS_LAT_ERROR         : Latitude outside of valid range 
 *                                      (-90 to 90 degrees)
 *          GARS_LON_ERROR         : Longitude outside of valid range
 *                                      (-180 to 360 degrees)
 *          GARS_STR_ERROR         : A GARS string error: string too long,
 *                                      string too short, invalid numbers/letters
 *          GARS_STR_LAT_ERROR     : The latitude part of the GARS string
 *                                     (fourth and fifth  characters) is invalid.
 *          GARS_STR_LON_ERROR     : The longitude part of the GARS string
 *                                     (first three characters) is invalid.
 *          GARS_STR_15_MIN_ERROR  : The 15 minute part of the GARS
 *                                      string is less than 1 or greater than 4.
 *          GARS_STR_5_MIN_ERROR   : The 5 minute part of the GARS
 *                                      string is less than 1 or greater than 9.
 *          GARS_PRECISION_ERROR   : The precision must be between 0 and 5 
 *                                      inclusive.
 *
 *
 * REUSE NOTES
 *
 *    GARS is intended for reuse by any application that performs a 
 *    conversion between Geodetic and GARS coordinates.
 *    
 * REFERENCES
 *
 *    Further information on GARS can be found in the Reuse Manual.
 *
 *    GARS originated from : 
 *                              
 *                   http://earth-info.nga.mil/GandG/coordsys/grids/gars.html           
 *                              
 *
 * LICENSES
 *
 *    None apply to this component.
 *
 * RESTRICTIONS
 *
 *    GARS has no restrictions.
 *
 * ENVIRONMENT
 *
 *    GARS was tested and certified in the following environments:
 *
 *    1. Solaris 2.5 with GCC version 2.8.1
 *    2. Windows XP with MS Visual C++ version 6
 *
 * MODIFICATIONS
 *
 *    Date              Description
 *    ----              -----------
 *    07-10-06          Original Code
 */


/***************************************************************************/
/*
 *                               INCLUDES
 */

#include <ctype.h>
//#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "gars.h"
/*
 *  ctype.h    - Standard C character handling library
 *  math.h     - Standard C math library
 *  stdio.h    - Standard C input/output library
 *  stdlib.h   - Standard C general utility library
 *  string.h   - Standard C string handling library
 *  gars.h     - for prototype error checking
 */


/***************************************************************************/
/*
 *                              DEFINES
 */

#define MIN_LATITUDE      -90.0  /* Minimum latitude                      */
#define MAX_LATITUDE      90.0   /* Maximum latitude                      */
#define MIN_LONGITUDE    -180.0  /* Minimum longitude                     */
#define MAX_LONGITUDE    360.0   /* Maximum longitude                     */
#define MIN_PER_DEG        60    /* Number of minutes per degree          */
#define GARS_MINIMUM      5      /* Minimum number of chars for GARS      */
#define GARS_MAXIMUM      7      /* Maximum number of chars for GARS      */
#define GARS_LETTERS      4      /* Number of letters in GARS string      */
#define MAX_PRECISION       5    /* Maximum precision of minutes part     */
#define LETTER_A_OFFSET    65    /* Letter A offset in character set      */
#define PI    3.14159265358979323e0     /* PI                             */
#define PI_OVER_180         PI / 180.0
#define RADIAN_TO_DEGREE   180.0e0 / PI

/* A = 0, B = 1, C = 2, D = 3, E = 4, F = 5, G = 6, H = 7                 */
#define LETTER_I               8   /* ARRAY INDEX FOR LETTER I            */
/* J = 9, K = 10, L = 11, M = 12, N = 13                                  */
#define LETTER_O              14   /* ARRAY INDEX FOR LETTER O            */
/* P = 15, Q = 16, R = 17, S = 18, T = 19, U = 20, V = 21,                */
/* W = 22, X = 23, Y = 24, Z = 25                                         */

#define _1                '1'
#define _2                '2'
#define _3                '3'
#define _4                '4'
#define _5                '5'
#define _6                '6'
#define _7                '7'
#define _8                '8'
#define _9                '9'

/***************************************************************************/
/*
 *                              FUNCTIONS     
 */

long Convert_GARS_To_Geodetic( char *gars,
                               double *latitude, 
                               double *longitude )
{ /* BEGIN Convert_GARS_To_Geodetic */
/*
 *  This function converts a GARS coordinate string to Geodetic (latitude
 *  and longitude in radians) coordinates.
 *
 *    gars      : GARS coordinate string.     (input)
 *    latitude  : Latitude in radians.        (output)
 *    longitude : Longitude in radians.       (output)
 *
 */

  long gars_length;          /* length of GARS string                      */
  int index = 0;
  char ew_str[4];
  int ew_value = 0;
  char letter = ' ';
  int ns_str[3];
  char _15_minute_value = 0;
  char _5_minute_value = 0;
  double lat_minutes = 0;
  double lon_minutes = 0;
  long error_code = GARS_NO_ERROR;

  gars_length = strlen( gars );
  if ( ( gars_length < GARS_MINIMUM ) || ( gars_length > GARS_MAXIMUM ) )
    error_code |= GARS_STR_ERROR;

  if ( !error_code )
  {
    while( isdigit( gars[index] ) )
    {
      ew_str[index] = gars[index];
      index++;
    }
    if( index != 3 )
      error_code |= GARS_STR_ERROR;
    else
    {
      /* Get 30 minute east/west value, 1-720 */
      ew_value = atoi( ew_str );

      letter = gars[index];
      if( !isalpha( letter ) )
        error_code |= GARS_STR_LON_ERROR;
      else
      {
        /* Get first 30 minute north/south letter, A-Q */
        ns_str[0] = toupper( letter ) - LETTER_A_OFFSET;
        letter = gars[++index];
        if( !isalpha( letter ) )
          error_code |= GARS_STR_LAT_ERROR;
        else
        {
        /* Get second 30 minute north/south letter, A-Z */
          ns_str[1] = toupper( letter ) - LETTER_A_OFFSET;
    
          if( index + 1 < gars_length )
          {
            /* Get 15 minute quadrant value, 1-4 */
            _15_minute_value = gars[++index];
            if( !isdigit( _15_minute_value ) || _15_minute_value < _1 || _15_minute_value > _4 )
              error_code |= GARS_STR_15_MIN_ERROR;
            else
            {
              if( index + 1 < gars_length )
              {
                /* Get 5 minute quadrant value, 1-9 */
                _5_minute_value = gars[++index];
                if( !isdigit( _5_minute_value ) || _5_minute_value < _1 || _5_minute_value > _9 )
                  error_code |= GARS_STR_5_MIN_ERROR;
              }
            }
          }

          if( !error_code )
          {
            *longitude = ( ( ( ew_value - 1.0 ) / 2.0 ) - 180.0 );

            /* Letter I and O are invalid */
            if( ns_str[0] >= LETTER_O )
              ns_str[0] --;
            if( ns_str[0] >= LETTER_I ) 
              ns_str[0] --;

            if( ns_str[1] >= LETTER_O )
              ns_str[1] --;
            if( ns_str[1] >= LETTER_I )
              ns_str[1] --;

            *latitude = ( ( -90.0 + ( ns_str[0] * 12.0 ) ) + ( ns_str[1] / 2.0 ) );

            switch( _15_minute_value )
            {
              case _1:
                lat_minutes = 15.0;
                break;
              case _4:
                lon_minutes = 15.0;
                break;
              case _2:
                lat_minutes = 15.0;
                lon_minutes = 15.0;
                break;
              case _3:
              default:
                break;
            }

            switch( _5_minute_value )
            {
              case _4:
                lat_minutes += 5.0;
                break;
              case _1:
                lat_minutes += 10.0;
                break;
              case _8:
                lon_minutes += 5.0;
                break;
              case _5:
                lon_minutes += 5.0;
                lat_minutes += 5.0;
                break;
              case _2:
                lon_minutes += 5.0;
                lat_minutes += 10.0;
                break;
              case _9:
                lon_minutes += 10.0;
                break;
              case _6:
                lon_minutes += 10.0;
                lat_minutes += 5.0;
                break;
              case _3:
                lon_minutes += 10.0;
                lat_minutes += 10.0;
                break;
              case _7:
              default:
                break;
            }

            /* Add these values to force the reference point to be the center of the box */
            if( _5_minute_value )
            {
              lat_minutes += 2.5;
              lon_minutes += 2.5;
            }
            else if( _15_minute_value )
            {
              lat_minutes += 7.5;
              lon_minutes += 7.5;
            }
            else
            {
              lat_minutes += 15.0;
              lon_minutes += 15.0;
            }

            *latitude += lat_minutes / MIN_PER_DEG;
            *longitude += lon_minutes / MIN_PER_DEG;
            *longitude *= PI_OVER_180;
            *latitude *= PI_OVER_180;
          }
        }
      }
    }
  }
  return ( error_code );
} /* END OF Convert_GARS_To_Geodetic */


long Convert_Geodetic_To_GARS( double latitude,
                               double longitude,
                               long precision,
                               char *gars )
{ /* BEGIN Convert_Geodetic_To_GARS */
/*   
 *  This function converts Geodetic (latitude and longitude in radians)
 *  coordinates to a GARS coordinate string.  Precision specifies the
 *  number of digits in the GARS string for latitude and longitude:
 *                                  0: 30 minutes (5 characters)
 *                                  1: 15 minutes (6 characters)
 *                                  2: 5 minutes (7 characters)
 *
 *    latitude  : Latitude in radians.                   (input)
 *    longitude : Longitude in radians.                  (input)
 *    precision : Precision specified by the user.       (input)
 *    gars      : GARS coordinate string.                (output)
 *
 */

  long ew_value;
  long letter_index[GARS_LETTERS + 1];    /* GARS letters                 */
  char _15_minute_value_str[2] = "";
  char _5_minute_value_str[2] = "";
  double round_error = 5.0e-11;
  char* _15_minute_array[2][2] = {{"3", "1"}, {"4", "2"}};
  char* _5_minute_array[3][3] = {{"7", "4", "1"}, {"8", "5", "2"}, {"9", "6", "3"}};
  double long_minutes, lat_minutes; 
  double long_remainder, lat_remainder; 
  long horiz_index_30, vert_index_30; 
  long horiz_index_15, vert_index_15; 
  long horiz_index_5, vert_index_5; 
  long error_code = GARS_NO_ERROR;

  latitude = latitude * RADIAN_TO_DEGREE;
  longitude = longitude *  RADIAN_TO_DEGREE;

  if ( ( latitude < MIN_LATITUDE ) || ( latitude > MAX_LATITUDE ) )
    error_code |= GARS_LAT_ERROR;
  if ( ( longitude < MIN_LONGITUDE ) || ( longitude > MAX_LONGITUDE ) )
    error_code |= GARS_LON_ERROR;
  if ( ( precision < 0 ) || ( precision > MAX_PRECISION ) )
    error_code |= GARS_PRECISION_ERROR;
  if ( !error_code )
  {
    /* North pole is an exception, read over and down */
    if( latitude == MAX_LATITUDE )
      latitude = 89.99999999999;

    if( longitude >= 180.0 )
      longitude -= 360.0;

    /* Convert longitude and latitude from degrees to minutes */ 
    /* longitude assumed in -180 <= long < +180 range */ 
    long_minutes = ( longitude - MIN_LONGITUDE ) * 60.0 + round_error; 
    lat_minutes = ( latitude - MIN_LATITUDE ) * 60.0 + round_error; 
    /* now we have a positive number of minutes */ 

    /* Find 30-min cell indices 0-719 and 0-359 */ 
    horiz_index_30 = ( long )( long_minutes / 30.0 ); 
    vert_index_30 = ( long )( lat_minutes / 30.0 );

    /* Compute remainders 0 <= x < 30.0 */ 
    long_remainder = long_minutes - ( horiz_index_30 ) * 30.0; 
    lat_remainder = lat_minutes - ( vert_index_30 ) * 30.0; 

    /* Find 15-min cell indices 0 or 1 */ 
    horiz_index_15 = ( long )( long_remainder / 15.0 ); 
    vert_index_15 = ( long )( lat_remainder / 15.0 ); 

    /* Compute remainders 0 <= x < 15.0 */ 
    long_remainder = long_remainder - ( horiz_index_15 ) * 15.0; 
    lat_remainder = lat_remainder - ( vert_index_15 ) * 15.0; 

    /* Find 5-min cell indices 0, 1, or 2 */ 
    horiz_index_5 = ( long )( long_remainder / 5.0 ); 
    vert_index_5 = ( long )( lat_remainder / 5.0 );

    /* Calculate 30 minute east/west value, 1-720 */
    ew_value = horiz_index_30 + 1;

    /* Calculate 30 minute north/south first letter, A-Q */
    letter_index[0] = ( long )( vert_index_30 / 24.0 );

    /* Calculate 30 minute north/south second letter, A-Z */
    letter_index[1] = ( long )( vert_index_30 - letter_index[0] * 24.0 );

    /* Letters I and O are invalid, so skip them */
    if( letter_index[0] >= LETTER_I )
      letter_index[0]++;
    if( letter_index[0] >= LETTER_O )
      letter_index[0] ++;

    if( letter_index[1] >= LETTER_I )
      letter_index[1]++;
    if( letter_index[1] >= LETTER_O )
      letter_index[1] ++;

    /* Get 15 minute quadrant value, 1-4 */
    strcpy( _15_minute_value_str, _15_minute_array[horiz_index_15][vert_index_15] );

    /* Get 5 minute keypad value, 1-9 */
    strcpy( _5_minute_value_str, _5_minute_array[horiz_index_5][vert_index_5] );

    /* Form the gars string */
    if( ew_value < 10 )
      sprintf ( gars, "00%d%c%c", ew_value, ( char )( letter_index[0] + LETTER_A_OFFSET ), ( char )( letter_index[1] + LETTER_A_OFFSET ) );
    else if( ew_value < 100 )
      sprintf ( gars, "0%d%c%c", ew_value, ( char )( letter_index[0] + LETTER_A_OFFSET ), ( char )( letter_index[1] + LETTER_A_OFFSET ) );
    else
      sprintf ( gars, "%d%c%c", ew_value, ( char )( letter_index[0] + LETTER_A_OFFSET ), ( char )( letter_index[1] + LETTER_A_OFFSET ) );

    if( precision > 0 )
    {
      strcat( gars, _15_minute_value_str);

      if( precision > 1 )
        strcat( gars, _5_minute_value_str);
    }

    gars[7] = '\0';
  }

  return ( error_code );
} /* END OF Convert_Geodetic_To_GARS */
