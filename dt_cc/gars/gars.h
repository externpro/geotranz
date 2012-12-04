#ifndef GARS_H
#define GARS_H

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
 *                  http://earth-info.nga.mil/GandG/coordsys/grids/gars.html            
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
 *                               DEFINES
 */
#define GARS_NO_ERROR             0x0000
#define GARS_LAT_ERROR            0x0001
#define GARS_LON_ERROR            0x0002
#define GARS_STR_ERROR            0x0004
#define GARS_STR_LAT_ERROR        0x0008
#define GARS_STR_LON_ERROR        0x0010
#define GARS_STR_15_MIN_ERROR     0x0020
#define GARS_STR_5_MIN_ERROR      0x0040
#define GARS_PRECISION_ERROR      0x0080


/***************************************************************************/
/*
 *                             FUNCTION PROTOTYPES
 *                                for gars.c
 */

/* ensure proper linkage to c++ programs */
#ifdef __cplusplus
extern "C" {
#endif


  long Convert_Geodetic_To_GARS ( double Latitude,
                                  double Longitude,
                                  long Precision,
                                  char *Gars );
/*   
 *  This function converts Geodetic (latitude and longitude in radians)
 *  coordinates to a GARS coordinate string.  Precision specifies the
 *  number of digits in the GARS string for latitude and longitude:
 *                                  0: 30 minutes (5 characters)
 *                                  1: 15 minutes (6 characters)
 *                                  2: 5 minutes (7 characters)
 *
 *    Latitude  : Latitude in radians                       (input)
 *    Longitude : Longitude in radians                      (input)
 *    Precision : level of precision specified by the user  (input)
 *    Gars      : GARS coordinate string                    (output)
 */


  long Convert_GARS_To_Geodetic ( char *Gars,
                                  double *Latitude, 
                                  double *Longitude );
/*
 *  This function converts a GARS coordinate string to Geodetic (latitude
 *  and longitude in radians) coordinates.
 *
 *    Gars    : GARS coordinate string     (input)
 *    Latitude  : Latitude in radians        (output)
 *    Longitude : Longitude in radians       (output)
*/


#ifdef __cplusplus
}
#endif

#endif /* GARS_H */
