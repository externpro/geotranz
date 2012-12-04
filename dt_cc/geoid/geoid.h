#ifndef GEOID_H
#define GEOID_H

/****************************************************************************/
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
 *  GEOID_NOT_INITIALIZED_ERROR  : Geoid separation database not initialized properly
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
 * MODIFICATIONS
 *
 *    Date              Description
 *    ----              -----------
 *    24-May-99         Original Code
 *    09-Jan-06         Added EGM84, bilinear, natural spline interpolation methods
 *
 */


/***************************************************************************/
/*
 *                               GLOBALS
 */

#define GEOID_NO_ERROR              0x0000
#define GEOID_FILE_OPEN_ERROR       0x0001
#define GEOID_INITIALIZE_ERROR      0x0002
#define GEOID_NOT_INITIALIZED_ERROR 0x0004
#define GEOID_LAT_ERROR             0x0008
#define GEOID_LON_ERROR             0x0010


/***************************************************************************/
/*
 *                          FUNCTION PROTOTYPES
 *                             for geoid.c
 */

/* ensure proper linkage to c++ programs */
#ifdef __cplusplus 
extern "C" {
#endif


long Initialize_Geoid ();
/*
 * The function Initialize_Geiud reads geoid separation data from a file in
 * the current directory and builds the geoid separation table from it.  If an
 * error occurs, the error code is returned, otherwise GEOID_NO_ERROR is 
 * returned.
 */


long Convert_Ellipsoid_To_Geoid_Height (double Latitude,
                                          double Longitude,
                                          double Ellipsoid_Height,
                                          double *Geoid_Height);
/*
 * The function Convert_Ellipsoid_To_Geoid_Height converts the specified WGS84
 * ellipsoid height at the specified geodetic coordinates to the equivalent
 * geoid height, using the EGM96 gravity model.
 *
 *    Latitude            : Geodetic latitude in radians           (input)
 *    Longitude           : Geodetic longitude in radians          (input)
 *    Ellipsoid_Height    : Ellipsoid height, in meters            (input)
 *    Geoid_Height        : Geoid height, in meters.               (output)
 *
 */


long Convert_Ellipsoid_To_MSL_EGM96_VG_NS_Height ( double Latitude,
                                                   double Longitude,
                                                   double Ellipsoid_Height,
                                                   double *Geoid_Height );
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


long Convert_Ellipsoid_To_MSL_EGM84_10D_BL_Height ( double Latitude,
                                                    double Longitude,
                                                    double Ellipsoid_Height,
                                                    double *Geoid_Height );
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


long Convert_Ellipsoid_To_MSL_EGM84_10D_NS_Height ( double Latitude,
                                                    double Longitude,
                                                    double Ellipsoid_Height,
                                                    double *Geoid_Height );
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


long Convert_Geoid_To_Ellipsoid_Height (double Latitude,
                                          double Longitude,
                                          double Geoid_Height,
                                          double *Ellipsoid_Height);
/*
 * The function Convert_Geoid_To_Ellipsoid_Height converts the specified WGS84
 * geoid height at the specified geodetic coordinates to the equivalent
 * ellipsoid height, using the EGM96 gravity model.
 *
 *    Latitude            : Geodetic latitude in radians           (input)
 *    Longitude           : Geodetic longitude in radians          (input)
 *    Geoid_Height        : Geoid height, in meters                (input)
 *    Ellipsoid_Height    : Ellipsoid height, in meters.           (output)
 *
 */

long Convert_MSL_EGM96_VG_NS_To_Ellipsoid_Height ( double Latitude,
                                                   double Longitude,
                                                   double Geoid_Height,
                                                   double *Ellipsoid_Height );
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


long Convert_MSL_EGM84_10D_BL_To_Ellipsoid_Height ( double Latitude,
                                                    double Longitude,
                                                    double Geoid_Height,
                                                    double *Ellipsoid_Height );
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


long Convert_MSL_EGM84_10D_NS_To_Ellipsoid_Height ( double Latitude,
                                                    double Longitude,
                                                    double Geoid_Height,
                                                    double *Ellipsoid_Height );
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


#ifdef __cplusplus 
}
#endif

#endif /* GEOID_H */
