/******************************************************************************
* Filename        : testCoordinateConversionSample.h
*
* Classification  : UNCLASSIFIED
*
* 
*    Copyright 2007 BAE Systems National Security Solutions Inc. 1989-2006
*                            ALL RIGHTS RESERVED
*
* MODIFICATION HISTORY:
*
* DATE        NAME              DR#               DESCRIPTION
* 
* 05/12/10    S Gillis          BAEts26542        MSP TS MSL-HAE conversion 
*                                                 should use CCS         
* 06/11/10    S. Gillis         BAEts26724        Fixed memory error problem
*                                                 when MSPCCS_DATA is not set 
* 
******************************************************************************/

#include <iostream>

#include "CoordinateConversionService.h"
#include "CoordinateSystemParameters.h"
#include "GeodeticParameters.h"
#include "CoordinateTuple.h"
#include "GeodeticCoordinates.h"
#include "CartesianCoordinates.h"
#include "Accuracy.h"
#include "MGRSorUSNGCoordinates.h"
#include "UTMParameters.h"
#include "UTMCoordinates.h"
#include "CoordinateType.h"
#include "HeightType.h"
#include "CoordinateConversionException.h"

using MSP::CCS::Precision;
using MSP::CCS::CoordinateConversionException;

void convertGeodeticToGeocentric(const double lat,const double lon, const double height, 
                                 double& x, double& y, double& z);
void convertGeodeticToGeocentricEgm84ThirtyMinBiLinear(const double lat,const double lon, const double height, 
                                 double& x, double& y, double& z);
void convertGeocentricToGeodetic(const double x, const double y, const double z, 
                                 double& lat,double& lon, double& height);
void convertGeocentricToGeodeticEgm84ThirtyMinBiLinear(const double x, 
                                                       const double y, 
                                                       const double z, 
                                                       double& lat,
                                                       double& lon, 
                                                       double& height);
void convertGeocentricToGeodeticMslEgm84ThirtyMinBiLinear(const double x,const double y,const double z, double& lat,double& lon, double& height); 
void convertGeocentricToGeodeticMslEgm96FifteenMinBilinear(const double x,const double y,const double z, double& lat,double& lon, double& height);
void convertMSLHeightToEllipsoidHeight(const double lat, const double lon,const double mslHeight, double& ellipsoidHeight);
void convertMSLHeightToEllipsoidHeightEGM84ThirtyMinBiLinear(const double lat, const double lon,const double mslHeight,double& ellipsoidHeight);
void convertEllipsoidHeightToMSLHeightEGM84TenDegBilinear(const double lat,const double lon,const double ellipsoidHeight,double& mslHeight);
void convertEllipsoidHeightToMSLHeightEGM84ThirtyMinBiLinear(const double lat,const double lon,const double ellipsoidHeight,double& mslHeight);
void convertEllipsoidHeightToMSLHeight(const double lat,const double lon,const double ellipsoidHeight,double& mslHeight);
void convertGeocentricToUTM(const double x,const double y,const double z, long& zone,char& hemisphere, double& easting,double& northing);
void convertGeocentricToMGRS(const double x,const double y,const double z, char*& mgrsString,Precision::Enum& precision);

int main(int argc, char **argv)
{

   std::cout << "Coordinate Conversion Service Sample Test Driver" << std::endl;

   ////////Using EGM96FifteenMinBilinear////////////////////////////////////////
   std::cout<<"\nUsing EGM96FifteenMinBilinear:\n"<<std::endl;

   std::cout<<"Starting CCS tests"<<std::endl;

   //Output results
   double lat,lon,height;
   double X = -2422589.08627;
   double Y = -4653263.51338;
   double Z = 3616509.32667;

   try
   {
        convertGeocentricToGeodeticMslEgm96FifteenMinBilinear(X,Y,Z,lat,lon,height);
        std::cout<<"convertGeocentricToGeodeticMslEgm96FifteenMinBilinear: "<<"Lat:"<<lat<<" Lon:"<<lon<<" Height:"<<height<<std::endl;
   }
   catch(CoordinateConversionException e)
   {
        std::cout << e.getMessage();
   }

   long zone;
   char hemi;
   double easting, northing;
   char* mgrsString[21];
   Precision::Enum precision;
   
   try
   {
        convertGeocentricToUTM(X,Y,Z,zone, hemi, easting, northing);
        std::cout<<"zone: "<<zone<<" hemisphere: "<<hemi<<" Easting: "<<easting<<" Northing: "<<northing<<std::endl;
   }
   catch(CoordinateConversionException e)
   {
        std::cout << e.getMessage();
   }

   try
   {
        convertGeocentricToMGRS(X,Y,Z,*mgrsString,precision);
        std::cout<<"mgrs: "<<*mgrsString<<" precision: "<<precision<<std::endl;
   }
   catch(CoordinateConversionException e)
   {
        std::cout << e.getMessage();
   }

   try
   {
       convertGeocentricToGeodetic( X, Y, Z, lat, lon, height);
       std::cout<<"Lat:"<<lat<<" Lon:"<<lon<<" Height:"<<height<<std::endl;
       std::cout<<"X: "<<X<<std::endl;
       std::cout<<"Y: "<<Y<<std::endl;
       std::cout<<"Z: "<<Z<<std::endl;
   }
   catch(CoordinateConversionException e)
   {
        std::cout << e.getMessage();
   }

   double a,b,c;

   try
   {
       convertGeodeticToGeocentric(lat,lon,height,a,b,c);
       std::cout<<"convert back"<<a<<" "<<b<<" "<<c<<" "<<std::endl;
   }
   catch(CoordinateConversionException e)
   {
        std::cout << e.getMessage();
   }

   /////////CCS TESTING/////////////////////////////////////////////////////////
   std::cout<<"/////////////CCS TESTING///////////////"<<std::endl;
   a=0.0; b=0.0; c=0.0;

   try
   {
       convertGeodeticToGeocentric(lat,lon,height,a,b,c);
       std::cout<<"convertGeodeticToGeocentric: "<<a<<"  "<<b<<"  "<<c<<"  "<<std::endl;
   }
   catch(CoordinateConversionException e)
   {
        std::cout << e.getMessage();
   }

   lat=0.0; lon=0.0; height= 0.0;

   try
   {
       convertGeocentricToGeodetic(a,b,c,lat,lon,height);
       std::cout<<"convertGeocentricToGeodetic: "<<lat<<" "<<lon<<" "<<height<<" "<<std::endl;
   }
   catch(CoordinateConversionException e)
   {
        std::cout << e.getMessage();
   }

   double mslHeight;

   try
   {
       convertEllipsoidHeightToMSLHeight(lat,lon,height, mslHeight);
       std::cout<<"convertEllipsoidHeightToMSLHeight -- MSL Height: "<<mslHeight<<std::endl;
   }
   catch(CoordinateConversionException e)
   {
        std::cout << e.getMessage();
   }

   double ellHeight;

   try
   {
       convertMSLHeightToEllipsoidHeight(lat,lon,mslHeight,ellHeight);
       std::cout<<"convertMSLHeightToEllipsoidHeight -- ELLIPSOID Height: "<<ellHeight<<std::endl;
   }
   catch(CoordinateConversionException e)
   {
        std::cout << e.getMessage();
   }

   try
   {
       convertEllipsoidHeightToMSLHeight(lat,lon,height, mslHeight);
       std::cout<<"convertEllipsoidHeightToMSLHeight -- MSL Height: "<<mslHeight<<std::endl;
   }
   catch(CoordinateConversionException e)
   {
        std::cout << e.getMessage();
   }

   ellHeight=0.0;

   try
   {
       convertMSLHeightToEllipsoidHeight(lat,lon,mslHeight,ellHeight);
       std::cout<<"convertMSLHeightToEllipsoidHeight -- ELLIPSOID Height: "<<ellHeight<<std::endl;
   }
   catch(CoordinateConversionException e)
   {
        std::cout << e.getMessage();
   }

   //////Using EGM84ThirtyMinBiLinear///////////////////////////////////////////
   std::cout<<"\nUsing EGM84ThirtyMinBiLinear:\n"<<std::endl;

   std::cout<<"Starting CCS tests"<<std::endl;

   //Output results
   double lat84,lon84,height84;
   double X84 = -2422589.08627;
   double Y84 = -4653263.51338;
   double Z84 = 3616509.32667;

   try
   {
       convertGeocentricToGeodeticMslEgm84ThirtyMinBiLinear(X84,Y84,Z84,lat84,lon84,height84);
       std::cout<<"convertGeocentricToGeodeticMslEgm84ThirtyMinBiLinear: "<<"Lat:"<<lat84<<" Lon:"<<lon84<<" Height:"<<height84<<std::endl;
   }
   catch(CoordinateConversionException e)
   {
        std::cout << e.getMessage();
   }

   long zone84;
   char hemi84;
   double easting84, northing84;
   char* mgrsString84[21];
   Precision::Enum precision84;

   try
   {
       convertGeocentricToUTM(X84,Y84,Z84,zone84, hemi84, easting84, northing84);
       std::cout<<"zone: "<<zone84<<" hemisphere: "<<hemi84<<" Easting: "<<easting84<<" Northing: "<<northing84<<std::endl;
   }
   catch(CoordinateConversionException e)
   {
        std::cout << e.getMessage();
   }

   try
   {
       convertGeocentricToMGRS(X84,Y84,Z84,*mgrsString84,precision84);
       std::cout<<"mgrs: "<<*mgrsString84<<" precision: "<<precision84<<std::endl;
   }
   catch(CoordinateConversionException e)
   {
        std::cout << e.getMessage();
   }

   try
   {
       convertGeocentricToGeodeticEgm84ThirtyMinBiLinear( X84, Y84, Z84, lat84, lon84, height84);
       std::cout<<"Lat:"<<lat84<<" Lon:"<<lon84<<" Height:"<<height84<<std::endl;
       std::cout<<"X: "<<X84<<std::endl;
       std::cout<<"Y: "<<Y84<<std::endl;
       std::cout<<"Z: "<<Z84<<std::endl;
   }
   catch(CoordinateConversionException e)
   {
        std::cout << e.getMessage();
   }

   double a84,b84,c84;

   try
   {
       convertGeodeticToGeocentricEgm84ThirtyMinBiLinear(lat84,lon84,height84,a84,b84,c84);
       std::cout<<"convert back"<<a84<<" "<<b84<<" "<<c84<<" "<<std::endl;
   }
   catch(CoordinateConversionException e)
   {
        std::cout << e.getMessage();
   }

   /////////CCS TESTING/////////////////////////////////////////////////////////////
   std::cout<<"/////////////CCS TESTING///////////////"<<std::endl;

   a84=0.0; b84=0.0; c84=0.0;
   
   try
   {
       convertGeodeticToGeocentricEgm84ThirtyMinBiLinear(lat84,lon84,height84,a84,b84,c84);
       std::cout<<"convertGeodeticToGeocentricEgm84ThirtyMinBiLinear: "<<a84<<"  "<<b84<<"  "<<c84<<"  "<<std::endl;
   }
   catch(CoordinateConversionException e)
   {
        std::cout << e.getMessage();
   }

   lat84=0.0; lon84=0.0; height84= 0.0;

   try
   {
       convertGeocentricToGeodeticEgm84ThirtyMinBiLinear(a84,b84,c84,lat84,lon84,height84);
       std::cout<<"convertGeocentricToGeodeticEgm84ThirtyMinBiLinear: "<<lat84<<" "<<lon84<<" "<<height84<<" "<<std::endl;
   }
   catch(CoordinateConversionException e)
   {
        std::cout << e.getMessage();
   }
   
   double mslHeight84;

   try
   {
       convertEllipsoidHeightToMSLHeightEGM84ThirtyMinBiLinear(lat84,lon84,height84, mslHeight84);
       std::cout<<"convertEllipsoidHeightToMSLHeightEGM84ThirtyMinBiLinear -- MSL Height: "<<mslHeight84<<std::endl;
   }
   catch(CoordinateConversionException e)
   {
        std::cout << e.getMessage();
   }
   
   double ellHeight84;

   try
   {
       convertMSLHeightToEllipsoidHeightEGM84ThirtyMinBiLinear(lat84,lon84,mslHeight84,ellHeight84);
       std::cout<<"convertMSLHeightToEllipsoidHeightEGM84ThirtyMinBiLinear -- ELLIPSOID Height: "<<ellHeight84<<std::endl;
   }
   catch(CoordinateConversionException e)
   {
        std::cout << e.getMessage();
   }

   try
   {
       convertEllipsoidHeightToMSLHeightEGM84ThirtyMinBiLinear(lat84,lon84,height84, mslHeight84);
       std::cout<<"convertEllipsoidHeightToMSLHeightEGM84ThirtyMinBiLinear -- MSL Height: "<<mslHeight84<<std::endl;
   }
   catch(CoordinateConversionException e)
   {
        std::cout << e.getMessage();
   }

   try
   {
       convertMSLHeightToEllipsoidHeightEGM84ThirtyMinBiLinear(lat84,lon84,mslHeight84,ellHeight84);
       std::cout<<"convertMSLHeightToEllipsoidHeightEGM84ThirtyMinBiLinear -- ELLIPSOID Height: "<<ellHeight84<<std::endl;
   }
   catch(CoordinateConversionException e)
   {
        std::cout << e.getMessage();
   }

   //10 degrees lat, 10 degrees lon - result should be about 22.91 meters
   double wantedHeight;

   try
   {
       convertEllipsoidHeightToMSLHeightEGM84ThirtyMinBiLinear(0.174532925, 0.174532925, 0, wantedHeight);
       std::cout<<"convert 10 degrees lat, 10 degrees lon, 0 ellipsoid height to EGM84ThirtyMinBiLinear -- MSL Height: "<<wantedHeight<<std::endl; 
   }
   catch(CoordinateConversionException e)
   {
        std::cout << e.getMessage();
   }

   //10 degrees lat, 10 degrees lon - result should be about 22.91 meters
//   wantedHeight =0.0;
//   try
//   {
//      convertEllipsoidHeightToMSLHeightEGM84TenDegBilinear(0.174532925, 0.174532925, 0, wantedHeight);
//      std::cout<<"convert 10 degrees lat, 10 degrees lon, 0 ellipsoid height to EGM84TenDegBilinear -- MSL Height: "<<wantedHeight<<std::endl; 
//   }
//   catch(CoordinateConversionException e)
//   {
//        std::cout << e.getMessage();
//   }

   //10 degrees lat, 10 degrees lon - result should be about 22.91 meters
//   wantedHeight =0.0;
//   try
//   {
//      convertEllipsoidHeightToMSLHeight(0.174532925, 0.174532925, 0, wantedHeight);
//      std::cout<<"convert 10 degrees lat, 10 degrees lon, 0 ellipsoid height to EGM96FifteenMinBilinear -- MSL Height: "<<wantedHeight<<std::endl; 
//   }
//   catch(CoordinateConversionException e)
//   {
//        std::cout << e.getMessage();
//   }

   //10 degrees, 5 minutes, 3 seconds for lat and lon - result should be about 22.71 meters
   wantedHeight = 0.0;

   try
   {
       convertEllipsoidHeightToMSLHeightEGM84ThirtyMinBiLinear(0.176001911, 0.176001911, 0, wantedHeight);
       std::cout<<"convert 10 degrees, 5 minutes, 3 seconds for lat and lon, with 0 ellipsoid height to EGM84ThirtyMinBiLinear -- MSL Height: "<<wantedHeight<<std::endl; 
   }
   catch(CoordinateConversionException e)
   {
        std::cout << e.getMessage();
   }

   std::cout<<"/////////////END CCS TESTING///////////////"<<std::endl;

   return 0;
}

//CCS CALLER FUNCTIONS BELOW

void convertGeodeticToGeocentric(const double lat,const double lon, const double height, 
                                 double& x, double& y, double& z)
{    
    try
    {
        MSP::CCS::GeodeticParameters geodeticParameters(MSP::CCS::CoordinateType::geodetic, MSP::CCS::HeightType::ellipsoidHeight);
        MSP::CCS::CoordinateSystemParameters geocentricParameters(MSP::CCS::CoordinateType::geocentric);
        MSP::CCS::CoordinateConversionService ccs( "WGE", &geodeticParameters, "WGE", &geocentricParameters );
        MSP::CCS::Accuracy sourceAccuracy;
        MSP::CCS::Accuracy targetAccuracy;
        MSP::CCS::GeodeticCoordinates sourceCoordinates(MSP::CCS::CoordinateType::geodetic, lon, lat, height);
        MSP::CCS::CartesianCoordinates targetCoordinates(MSP::CCS::CoordinateType::geocentric);
        ccs.convertSourceToTarget( &sourceCoordinates, &sourceAccuracy, targetCoordinates, targetAccuracy );
        x = targetCoordinates.x();
        y = targetCoordinates.y();
        z = targetCoordinates.z();
        std::cout<<"BIG TEST"<<std::endl;
        std::cout<<"lat "<<lat<<" lon "<<lon<<" height "<<height<<std::endl;
        std::cout<<"x "<<x<<" y "<<y<<" z "<<z<<std::endl;
    
        targetCoordinates.set(x, y, z);
        sourceCoordinates.set(0.0, 0.0, 0.0);
        ccs.convertTargetToSource( &targetCoordinates, &targetAccuracy, sourceCoordinates, sourceAccuracy);
        std::cout<<"lat "<<sourceCoordinates.latitude()<<" lon "<<sourceCoordinates.longitude()<<" height "<<sourceCoordinates.height()<<std::endl;
    }
    catch(MSP::CCS::CoordinateConversionException e)
    {
        throw e;
    }  
}

void convertGeodeticToGeocentricEgm84ThirtyMinBiLinear(const double lat,const double lon, const double height, 
                                 double& x, double& y, double& z)
{
    try
    {
        MSP::CCS::GeodeticParameters geodeticParameters(MSP::CCS::CoordinateType::geodetic, MSP::CCS::HeightType::EGM84ThirtyMinBiLinear);
        MSP::CCS::CoordinateSystemParameters geocentricParameters(MSP::CCS::CoordinateType::geocentric);
        MSP::CCS::CoordinateConversionService ccs( "WGE", &geodeticParameters, "WGE", &geocentricParameters );
        MSP::CCS::Accuracy sourceAccuracy;
        MSP::CCS::Accuracy targetAccuracy;
        MSP::CCS::GeodeticCoordinates sourceCoordinates(MSP::CCS::CoordinateType::geodetic, lon, lat, height);
        MSP::CCS::CartesianCoordinates targetCoordinates(MSP::CCS::CoordinateType::geocentric);
        ccs.convertSourceToTarget( &sourceCoordinates, &sourceAccuracy, targetCoordinates, targetAccuracy );
        x = targetCoordinates.x();
        y = targetCoordinates.y();
        z = targetCoordinates.z();
        std::cout<<"BIG TEST"<<std::endl;
        std::cout<<"lat "<<lat<<" lon "<<lon<<" height "<<height<<std::endl;
        std::cout<<"x "<<x<<" y "<<y<<" z "<<z<<std::endl;
    
        targetCoordinates.set(x, y, z);
        sourceCoordinates.set(0.0, 0.0, 0.0);
        ccs.convertTargetToSource( &targetCoordinates, &targetAccuracy, sourceCoordinates, sourceAccuracy);
        std::cout<<"lat "<<sourceCoordinates.latitude()<<" lon "<<sourceCoordinates.longitude()<<" height "<<sourceCoordinates.height()<<std::endl;
    }
    catch(MSP::CCS::CoordinateConversionException e)
    {
        throw e;
    } 
}

void convertGeocentricToGeodetic(const double x, const double y, const double z, 
                                 double& lat,double& lon, double& height)
{
    try
    {
        MSP::CCS::CoordinateSystemParameters geocentricParameters(MSP::CCS::CoordinateType::geocentric);
        MSP::CCS::GeodeticParameters geodeticParameters(MSP::CCS::CoordinateType::geodetic, MSP::CCS::HeightType::ellipsoidHeight);
        MSP::CCS::CoordinateConversionService ccs( "WGE", &geocentricParameters, "WGE", &geodeticParameters );
        MSP::CCS::Accuracy sourceAccuracy;
        MSP::CCS::Accuracy targetAccuracy;
        MSP::CCS::CartesianCoordinates sourceCoordinates(MSP::CCS::CoordinateType::geocentric, x, y, z);
        MSP::CCS::GeodeticCoordinates targetCoordinates;
        ccs.convertSourceToTarget( &sourceCoordinates, &sourceAccuracy, targetCoordinates, targetAccuracy );
        lat = targetCoordinates.latitude();
        lon = targetCoordinates.longitude();
        height = targetCoordinates.height();
    }
    catch(MSP::CCS::CoordinateConversionException e)
    {
        throw e;
    } 

}

void convertGeocentricToGeodeticEgm84ThirtyMinBiLinear(const double x, 
                                                       const double y, 
                                                       const double z, 
                                                       double& lat,
                                                       double& lon, 
                                                       double& height)
{
    try
    {
        MSP::CCS::CoordinateSystemParameters geocentricParameters(MSP::CCS::CoordinateType::geocentric);
        MSP::CCS::GeodeticParameters geodeticParameters(MSP::CCS::CoordinateType::geodetic, MSP::CCS::HeightType::EGM84ThirtyMinBiLinear);
        MSP::CCS::CoordinateConversionService ccs( "WGE", &geocentricParameters, "WGE", &geodeticParameters );
        MSP::CCS::Accuracy sourceAccuracy;
        MSP::CCS::Accuracy targetAccuracy;
        MSP::CCS::CartesianCoordinates sourceCoordinates(MSP::CCS::CoordinateType::geocentric, x, y, z);
        MSP::CCS::GeodeticCoordinates targetCoordinates;
        ccs.convertSourceToTarget( &sourceCoordinates, &sourceAccuracy, targetCoordinates, targetAccuracy );
        lat = targetCoordinates.latitude();
        lon = targetCoordinates.longitude();
        height = targetCoordinates.height();
    }
    catch(MSP::CCS::CoordinateConversionException e)
    {
        throw e;
    } 

}

void convertGeocentricToGeodeticMslEgm84ThirtyMinBiLinear(
			const double x,
			const double y,
			const double z, 
			double& lat,
			double& lon, 
			double& height)
{
    try
    {
        MSP::CCS::CoordinateSystemParameters geocentricParameters(MSP::CCS::CoordinateType::geocentric);
        MSP::CCS::GeodeticParameters mslParameters(MSP::CCS::CoordinateType::geodetic, MSP::CCS::HeightType::EGM84ThirtyMinBiLinear);
        MSP::CCS::CoordinateConversionService ccs( "WGE", &geocentricParameters, "WGE", &mslParameters );
        MSP::CCS::Accuracy sourceAccuracy;
        MSP::CCS::Accuracy targetAccuracy;
        MSP::CCS::CartesianCoordinates sourceCoordinates(MSP::CCS::CoordinateType::geocentric, x, y, z);
        MSP::CCS::GeodeticCoordinates targetCoordinates(MSP::CCS::CoordinateType::geodetic, lon, lat, height);
        ccs.convertSourceToTarget( &sourceCoordinates, &sourceAccuracy, targetCoordinates, targetAccuracy );
        lat = targetCoordinates.latitude();
        lon = targetCoordinates.longitude();
        height = targetCoordinates.height();
    }
    catch(MSP::CCS::CoordinateConversionException e)
    {
        throw e;
    } 
}

void convertGeocentricToGeodeticMslEgm96FifteenMinBilinear(
			const double x,
			const double y,
			const double z, 
			double& lat,
			double& lon, 
			double& height)
{
    try
    {
        MSP::CCS::CoordinateSystemParameters geocentricParameters(MSP::CCS::CoordinateType::geocentric);
        MSP::CCS::GeodeticParameters mslParameters(MSP::CCS::CoordinateType::geodetic, MSP::CCS::HeightType::EGM96FifteenMinBilinear);
        MSP::CCS::CoordinateConversionService ccs( "WGE", &geocentricParameters, "WGE", &mslParameters );
        MSP::CCS::Accuracy sourceAccuracy;
        MSP::CCS::Accuracy targetAccuracy;
        MSP::CCS::CartesianCoordinates sourceCoordinates(MSP::CCS::CoordinateType::geocentric, x, y, z);
        MSP::CCS::GeodeticCoordinates targetCoordinates(MSP::CCS::CoordinateType::geodetic, lon, lat, height);
        ccs.convertSourceToTarget( &sourceCoordinates, &sourceAccuracy, targetCoordinates, targetAccuracy );
        lat = targetCoordinates.latitude();
        lon = targetCoordinates.longitude();
        height = targetCoordinates.height();
    }
    catch(MSP::CCS::CoordinateConversionException e)
    {
        throw e;
    } 
}

void convertEllipsoidHeightToMSLHeightEGM84TenDegBilinear(const double lat,const double lon,const double ellipsoidHeight,double& mslHeight)
{
    try
    {
        MSP::CCS::GeodeticParameters ellParameters(MSP::CCS::CoordinateType::geodetic, MSP::CCS::HeightType::ellipsoidHeight);
        MSP::CCS::GeodeticParameters mslParameters(MSP::CCS::CoordinateType::geodetic, MSP::CCS::HeightType::EGM84TenDegBilinear);
        MSP::CCS::CoordinateConversionService ccs( "WGE", &ellParameters, "WGE", &mslParameters );
        MSP::CCS::Accuracy sourceAccuracy;
        MSP::CCS::Accuracy targetAccuracy;
        MSP::CCS::GeodeticCoordinates sourceCoordinates(MSP::CCS::CoordinateType::geodetic, lon, lat, ellipsoidHeight);
        MSP::CCS::GeodeticCoordinates targetCoordinates;
        ccs.convertSourceToTarget( &sourceCoordinates, &sourceAccuracy, targetCoordinates, targetAccuracy );
        mslHeight = targetCoordinates.height();
    }
    catch(MSP::CCS::CoordinateConversionException e)
    {
        throw e;
    } 
}

void convertEllipsoidHeightToMSLHeightEGM84ThirtyMinBiLinear(const double lat,const double lon,const double ellipsoidHeight,double& mslHeight)
{
    try
    {
        MSP::CCS::GeodeticParameters ellParameters(MSP::CCS::CoordinateType::geodetic, MSP::CCS::HeightType::ellipsoidHeight);
        MSP::CCS::GeodeticParameters mslParameters(MSP::CCS::CoordinateType::geodetic, MSP::CCS::HeightType::EGM84ThirtyMinBiLinear);
        MSP::CCS::CoordinateConversionService ccs( "WGE", &ellParameters, "WGE", &mslParameters );
        MSP::CCS::Accuracy sourceAccuracy;
        MSP::CCS::Accuracy targetAccuracy;
        MSP::CCS::GeodeticCoordinates sourceCoordinates(MSP::CCS::CoordinateType::geodetic, lon, lat, ellipsoidHeight);
        MSP::CCS::GeodeticCoordinates targetCoordinates;
        ccs.convertSourceToTarget( &sourceCoordinates, &sourceAccuracy, targetCoordinates, targetAccuracy );
        mslHeight = targetCoordinates.height();
    }
    catch(MSP::CCS::CoordinateConversionException e)
    {
        throw e;
    } 
}

void convertEllipsoidHeightToMSLHeight(const double lat,const double lon,const double ellipsoidHeight,double& mslHeight)
{
    try
    {
        MSP::CCS::GeodeticParameters ellParameters(MSP::CCS::CoordinateType::geodetic, MSP::CCS::HeightType::ellipsoidHeight);
        MSP::CCS::GeodeticParameters mslParameters(MSP::CCS::CoordinateType::geodetic, MSP::CCS::HeightType::EGM96FifteenMinBilinear);
        MSP::CCS::CoordinateConversionService ccs( "WGE", &ellParameters, "WGE", &mslParameters );
        MSP::CCS::Accuracy sourceAccuracy;
        MSP::CCS::Accuracy targetAccuracy;
        MSP::CCS::GeodeticCoordinates sourceCoordinates(MSP::CCS::CoordinateType::geodetic, lon, lat, ellipsoidHeight);
        MSP::CCS::GeodeticCoordinates targetCoordinates;
        ccs.convertSourceToTarget( &sourceCoordinates, &sourceAccuracy, targetCoordinates, targetAccuracy );
        mslHeight = targetCoordinates.height();
    }
    catch(MSP::CCS::CoordinateConversionException e)
    {
        throw e;
    } 
}

void convertMSLHeightToEllipsoidHeightEGM84ThirtyMinBiLinear(const double lat, const double lon,const double mslHeight,double& ellipsoidHeight)
{
    try
    {
        MSP::CCS::GeodeticParameters mslParameters(MSP::CCS::CoordinateType::geodetic, MSP::CCS::HeightType::EGM84ThirtyMinBiLinear);
        MSP::CCS::GeodeticParameters ellParameters(MSP::CCS::CoordinateType::geodetic, MSP::CCS::HeightType::ellipsoidHeight);
        MSP::CCS::CoordinateConversionService ccs( "WGE", &mslParameters, "WGE", &ellParameters );
        MSP::CCS::Accuracy sourceAccuracy;
        MSP::CCS::Accuracy targetAccuracy;
        MSP::CCS::GeodeticCoordinates sourceCoordinates(MSP::CCS::CoordinateType::geodetic, lon, lat, mslHeight);
        MSP::CCS::GeodeticCoordinates targetCoordinates;
        ccs.convertSourceToTarget( &sourceCoordinates, &sourceAccuracy, targetCoordinates, targetAccuracy );
        ellipsoidHeight = targetCoordinates.height();
    }
    catch(MSP::CCS::CoordinateConversionException e)
    {
        throw e;
    } 
}

void convertMSLHeightToEllipsoidHeight(const double lat, const double lon,const double mslHeight,double& ellipsoidHeight)
{
    try
    {
        MSP::CCS::GeodeticParameters mslParameters(MSP::CCS::CoordinateType::geodetic, MSP::CCS::HeightType::EGM96FifteenMinBilinear);
        MSP::CCS::GeodeticParameters ellParameters(MSP::CCS::CoordinateType::geodetic, MSP::CCS::HeightType::ellipsoidHeight);
        MSP::CCS::CoordinateConversionService ccs( "WGE", &mslParameters, "WGE", &ellParameters );
        MSP::CCS::Accuracy sourceAccuracy;
        MSP::CCS::Accuracy targetAccuracy;
        MSP::CCS::GeodeticCoordinates sourceCoordinates(MSP::CCS::CoordinateType::geodetic, lon, lat, mslHeight);
        MSP::CCS::GeodeticCoordinates targetCoordinates;
        ccs.convertSourceToTarget( &sourceCoordinates, &sourceAccuracy, targetCoordinates, targetAccuracy );
        ellipsoidHeight = targetCoordinates.height();
    }
    catch(MSP::CCS::CoordinateConversionException e)
    {
        throw e;
    } 
}

void convertGeocentricToUTM(
			const double x,
			const double y,
			const double z, 
			long& zone,
			char& hemisphere, 
			double& easting,
            double& northing)
{
    try
    {
        MSP::CCS::CoordinateSystemParameters geocentricParameters(MSP::CCS::CoordinateType::geocentric);
        MSP::CCS::UTMParameters utmParameters(MSP::CCS::CoordinateType::universalTransverseMercator, 1, 0);
        MSP::CCS::CoordinateConversionService ccs( "WGE", &geocentricParameters, "WGE", &utmParameters );
        MSP::CCS::Accuracy sourceAccuracy;
        MSP::CCS::Accuracy targetAccuracy;
        MSP::CCS::CartesianCoordinates sourceCoordinates(MSP::CCS::CoordinateType::geocentric, x, y, z);
        MSP::CCS::UTMCoordinates targetCoordinates;
        ccs.convertSourceToTarget( &sourceCoordinates, &sourceAccuracy, targetCoordinates, targetAccuracy );
        zone = targetCoordinates.zone();
        hemisphere = targetCoordinates.hemisphere();
        easting = targetCoordinates.easting();
        northing = targetCoordinates.northing();
    }
    catch(MSP::CCS::CoordinateConversionException e)
    {
        throw e;
    } 
}

void convertGeocentricToMGRS(
			const double x,
			const double y,
			const double z, 
			char*& mgrsString,
            Precision::Enum& precision)
{
    try
    {
        MSP::CCS::CoordinateSystemParameters geocentricParameters(MSP::CCS::CoordinateType::geocentric);
        MSP::CCS::CoordinateSystemParameters mgrsParameters(MSP::CCS::CoordinateType::militaryGridReferenceSystem);
        MSP::CCS::CoordinateConversionService ccs( "WGE", &geocentricParameters, "WGE", &mgrsParameters );
        MSP::CCS::Accuracy sourceAccuracy;
        MSP::CCS::Accuracy targetAccuracy;
        MSP::CCS::CartesianCoordinates sourceCoordinates(MSP::CCS::CoordinateType::geocentric, x, y, z);
        MSP::CCS::MGRSorUSNGCoordinates targetCoordinates;
        ccs.convertSourceToTarget( &sourceCoordinates, &sourceAccuracy, targetCoordinates, targetAccuracy );
        mgrsString = targetCoordinates.MGRSString();
        precision = targetCoordinates.precision();
    }
    catch(MSP::CCS::CoordinateConversionException e)
    {
        throw e;
    } 
}
