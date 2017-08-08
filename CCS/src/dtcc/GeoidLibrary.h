// CLASSIFICATION: UNCLASSIFIED

#ifndef GeoidLibrary_H
#define GeoidLibrary_H

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
 *
 */

#include <vector>
#include "DtccApi.h"

namespace MSP
{
  namespace CCS
  {
    /***************************************************************************/
    /*
     *                              DEFINES
     */

    class MSP_DTCC_API GeoidLibrary
    {
    friend class GeoidLibraryCleaner;

    public:

      /* The function getInstance returns an instance of the GeoidLibrary
       */

      static GeoidLibrary* getInstance();


      /*
       * The function removeInstance removes this GeoidLibrary instance from the
       * total number of instances. 
       */

      static void removeInstance();


	    ~GeoidLibrary( void );


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

      void convertEllipsoidToEGM96FifteenMinBilinearGeoidHeight( double longitude, double latitude,  double ellipsoidHeight, double *geoidHeight );


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

      void convertEllipsoidToEGM96VariableNaturalSplineHeight( double longitude, double latitude, double ellipsoidHeight, double *geoidHeight );


      /*
       * The function convertEllipsoidToEGM84TenDegBilinearHeight converts the specified WGS84
       * ellipsoid height at the specified geodetic coordinates to the equivalent
       * geoid height, using the EGM84 gravity model and the bilinear interpolation method..
       *
       *    longitude          : Geodetic longitude in radians          (input)
       *    latitude           : Geodetic latitude in radians           (input)
       *    ellipsoidHeight    : Ellipsoid height, in meters            (input)
       *    geoidHeight        : Geoid height, in meters.               (output)
       *
       */

      void convertEllipsoidToEGM84TenDegBilinearHeight( double longitude, double latitude, double ellipsoidHeight, double *geoidHeight );


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

      void convertEllipsoidToEGM84TenDegNaturalSplineHeight( double longitude, double latitude, double ellipsoidHeight, double *geoidHeight );


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

      void convertEGM96FifteenMinBilinearGeoidToEllipsoidHeight( double longitude, double latitude, double geoidHeight,  double *ellipsoidHeight );


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

      void convertEGM96VariableNaturalSplineToEllipsoidHeight( double longitude, double latitude, double geoidHeight, double *ellipsoidHeight );


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

      void convertEGM84TenDegBilinearToEllipsoidHeight( double longitude, double latitude, double geoidHeight, double *ellipsoidHeight );


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

      void convertEGM84TenDegNaturalSplineToEllipsoidHeight( double longitude, double latitude, double geoidHeight, double *ellipsoidHeight );

    protected:

      /*
       * The constructor creates an empty list which is used to store the geoid separation data
       * contained in the data files egm84.grd and egm96.grd
       */

	    GeoidLibrary();


      GeoidLibrary( const GeoidLibrary &gl );


      GeoidLibrary& operator=( const GeoidLibrary &gl );


    private:

      static GeoidLibrary* instance;
      static int instanceCount;

      /* List of EGM96 elevations */
      std::vector<float> egm96GeoidList;

      /* List of EGM84 elevations */
      std::vector<float> egm84GeoidList;

    
      /*
       * The function loadGeoids reads geoid separation data from a file in
       * the current directory and builds the geoid separation table from it.
       * If the separation file can not be found or accessed, an error code of
       * GEOID_FILE_OPEN_ERROR is returned, If the separation file is incomplete
       * or improperly formatted, an error code of GEOID_INITIALIZE_ERROR is returned,
       * otherwise GEOID_NO_ERROR is returned. This function must be called before 
       * any of the other functions in this component.
       */

      void loadGeoids();


      /*
       * The function initializeEGM96Geoid reads geoid separation data from the egm96.grd
       *  file in the current directory and builds a geoid separation table from it.
       * If the separation file can not be found or accessed, an error code of
       * GEOID_FILE_OPEN_ERROR is returned, If the separation file is incomplete
       * or improperly formatted, an error code of GEOID_INITIALIZE_ERROR is returned,
       * otherwise GEOID_NO_ERROR is returned.
       */

      void initializeEGM96Geoid();


      /*
       * The function initializeEGM84Geoid reads geoid separation data from a file in
       * the current directory and builds the geoid separation table from it.
       * If the separation file can not be found or accessed, an error code of
       * GEOID_FILE_OPEN_ERROR is returned, If the separation file is incomplete
       * or improperly formatted, an error code of GEOID_INITIALIZE_ERROR is returned,
       * otherwise GEOID_NO_ERROR is returned.
       */

      void initializeEGM84Geoid();


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
       *    height_buffer       : Grid of height adjustments             (input)
       *    delta_height        : Height Adjustment, in meters.          (output)
       *
       */

      void bilinearInterpolate( double longitude, double latitude, double scale_factor, int num_cols, int num_rows,
                                std::vector<float>& height_buffer,  double *delta_height );


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

      void naturalSplineInterpolate( double longitude, double latitude, double scale_factor, int num_cols, int num_rows,
                                     int max_index, std::vector<float>& height_buffer, double *delta_height );

      
      /*
       * Delete the singleton.
       */

      static void deleteInstance();
    };
  }
}

#endif 


// CLASSIFICATION: UNCLASSIFIED
