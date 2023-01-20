/*
 * JNIEngine.java
 *
 * Created on April 5, 2001, 4:40 PM
 */

package geotrans.jni;


import geotrans.gui.Accuracy;
import geotrans.projections.*;


/**
 *
 * @author  amyc
 * @version 
 */
public class JNIEngine extends Object {

    /** Creates new JNIEngine */
    public JNIEngine() {
    }
    
    public native int JNICheckValidConversion(int inputSystem, int outputSystem, int inputDatum, int outputDatum);
    public native void JNIConvert(int state) throws GeotransError, GeotransWarning, JNIException;
    public native void JNIDefine3ParamDatum(java.lang.String datumCode, java.lang.String datumName,
                                            java.lang.String ellipsoidCode,
                                            double deltaX, double deltaY, double deltaZ,
                                            double sigmaX, double sigmaY, double sigmaZ,
                                            double southLat, double northLat,
                                            double westLon, double eastLon)throws GeotransError, JNIException;
    public native void JNIDefine7ParamDatum(java.lang.String datumCode, java.lang.String datumName,
                                            java.lang.String ellipsoidCode,
                                            double deltaX, double deltaY, double deltaZ,
                                            double rotationX, double rotationY, double rotationZ,
                                            double scale)throws GeotransError, JNIException;
    public native void JNIDefineEllipsoid(java.lang.String ellipsoidCode, java.lang.String ellipsoidName,
                                          double a, double f)throws GeotransError, JNIException;
    public native void JNIRemoveDatum(java.lang.String datumCode)throws GeotransError, JNIException;
    public native void JNIRemoveEllipsoid(java.lang.String ellipsoidCode)throws GeotransError, JNIException;    
    public native void JNIInitializeEngine() throws GeotransError;
    public native Accuracy JNIGetConversionErrors(int state);
    public native void JNISetConversionErrors(int state, double ce90, double le90, double se90) throws GeotransError;
    public native String JNIGetCoordinateSystemCode(int index) throws GeotransError;
    public native int JNIGetCoordinateSystem(int state, int direction) throws GeotransError;
    public native void JNISetCoordinateSystem(int state, int direction, int projectionType) throws GeotransError;
    public native long JNIGetDatum(int state, int direction) throws GeotransError;
    public native void JNISetDatum(int state, int direction, long index) throws GeotransError;
    public native java.lang.String JNIGetDatumCode(long i) throws GeotransError, JNIException; 
    public native long JNIGetDatumCount() throws GeotransError;
    public native long JNIGetDatumIndex(java.lang.String code) throws GeotransError, JNIException;
    public native java.lang.String JNIGetDatumName(long i) throws GeotransError, JNIException; 
    public native java.lang.String JNIGetDatumEllipsoidCode(long i) throws GeotransError, JNIException; 
    public native java.lang.String JNIGetEllipsoidCode(long i) throws GeotransError, JNIException; 
    public native long JNIGetEllipsoidCount() throws GeotransError;
    public native long JNIGetEllipsoidIndex(java.lang.String code) throws GeotransError, JNIException;
    public native java.lang.String JNIGetEllipsoidName(long i) throws GeotransError, JNIException; 
    public native void JNISetPrecision(int precision);
    public native int JNIGetPrecision();
    
    public native AlbersEqualAreaConic JNIGetAlbersEqualAreaConicParams(int state, int direction) throws GeotransError, JNIException;
    public native void JNISetAlbersEqualAreaConicParams(int state, int direction, AlbersEqualAreaConic params) throws GeotransError, JNIException;
    public native AlbersEqualAreaConic JNIGetAlbersEqualAreaConicCoordinates(int state, int direction) throws GeotransError, JNIException;
    public native void JNISetAlbersEqualAreaConicCoordinates(int state, int direction, AlbersEqualAreaConic coords) throws GeotransError, JNIException;
    
    public native AzimuthalEquidistant JNIGetAzimuthalEquidistantParams(int state, int direction) throws GeotransError, JNIException;
    public native void JNISetAzimuthalEquidistantParams(int state, int direction, AzimuthalEquidistant params) throws GeotransError, JNIException;
    public native AzimuthalEquidistant JNIGetAzimuthalEquidistantCoordinates(int state, int direction) throws GeotransError, JNIException;
    public native void JNISetAzimuthalEquidistantCoordinates(int state, int direction, AzimuthalEquidistant coords) throws GeotransError, JNIException;
    
    public native BNG JNIGetBNGCoordinates(int state, int direction) throws GeotransError, JNIException;
    public native void JNISetBNGCoordinates(int state, int direction, BNG coords) throws GeotransError, JNIException;
    
    public native Bonne JNIGetBonneParams(int state, int direction) throws GeotransError, JNIException;
    public native void JNISetBonneParams(int state, int direction, Bonne params) throws GeotransError, JNIException;
    public native Bonne JNIGetBonneCoordinates(int state, int direction) throws GeotransError, JNIException;
    public native void JNISetBonneCoordinates(int state, int direction, Bonne coords) throws GeotransError, JNIException;
    
    public native Cassini JNIGetCassiniParams(int state, int direction) throws GeotransError, JNIException;
    public native void JNISetCassiniParams(int state, int direction, Cassini params) throws GeotransError, JNIException;
    public native Cassini JNIGetCassiniCoordinates(int state, int direction) throws GeotransError, JNIException;
    public native void JNISetCassiniCoordinates(int state, int direction, Cassini coords) throws GeotransError, JNIException;
   
    public native CylindricalEqualArea JNIGetCylindricalEqualAreaParams(int state, int direction) throws GeotransError, JNIException;
    public native void JNISetCylindricalEqualAreaParams(int state, int direction, CylindricalEqualArea params) throws GeotransError, JNIException;
    public native CylindricalEqualArea JNIGetCylindricalEqualAreaCoordinates(int state, int direction) throws GeotransError, JNIException;
    public native void JNISetCylindricalEqualAreaCoordinates(int state, int direction, CylindricalEqualArea coords) throws GeotransError, JNIException;
    
    public native Eckert4 JNIGetEckert4Params(int state, int direction) throws GeotransError, JNIException;
    public native void JNISetEckert4Params(int state, int direction, Eckert4 params) throws GeotransError, JNIException;
    public native Eckert4 JNIGetEckert4Coordinates(int state, int direction) throws GeotransError, JNIException;
    public native void JNISetEckert4Coordinates(int state, int direction, Eckert4 coords) throws GeotransError, JNIException;
   
    public native Eckert6 JNIGetEckert6Params(int state, int direction) throws GeotransError, JNIException;
    public native void JNISetEckert6Params(int state, int direction, Eckert6 params) throws GeotransError, JNIException;
    public native Eckert6 JNIGetEckert6Coordinates(int state, int direction) throws GeotransError, JNIException;
    public native void JNISetEckert6Coordinates(int state, int direction, Eckert6 coords) throws GeotransError, JNIException;
    
    public native EquidistantCylindrical JNIGetEquidistantCylindricalParams(int state, int direction) throws GeotransError, JNIException;
    public native void JNISetEquidistantCylindricalParams(int state, int direction, EquidistantCylindrical params) throws GeotransError, JNIException;
    public native EquidistantCylindrical JNIGetEquidistantCylindricalCoordinates(int state, int direction) throws GeotransError, JNIException;
    public native void JNISetEquidistantCylindricalCoordinates(int state, int direction, EquidistantCylindrical coords) throws GeotransError, JNIException;
    
    public native GARS JNIGetGARSCoordinates(int state, int direction) throws GeotransError, JNIException;
    public native void JNISetGARSCoordinates(int state, int direction, GARS coords) throws GeotransError, JNIException;
    
    public native Geocentric JNIGetGeocentricCoordinates(int state, int direction) throws GeotransError, JNIException;
    public native void JNISetGeocentricCoordinates(int state, int direction, Geocentric coords) throws GeotransError, JNIException;
    
    public native Geodetic JNIGetGeodeticParams(int state, int direction) throws GeotransError, JNIException;
    public native void JNISetGeodeticParams(int state, int direction, Geodetic params) throws GeotransError, JNIException;
    public native Geodetic JNIGetGeodeticCoordinates(int state, int direction) throws GeotransError, JNIException;
    public native void JNISetGeodeticCoordinates(int state, int direction, Geodetic coords) throws GeotransError, JNIException;
    
    public native GEOREF JNIGetGEOREFCoordinates(int state, int direction) throws GeotransError, JNIException;
    public native void JNISetGEOREFCoordinates(int state, int direction, GEOREF coords) throws GeotransError, JNIException;
   
    public native Gnomonic JNIGetGnomonicParams(int state, int direction) throws GeotransError, JNIException;
    public native void JNISetGnomonicParams(int state, int direction, Gnomonic params) throws GeotransError, JNIException;
    public native Gnomonic JNIGetGnomonicCoordinates(int state, int direction) throws GeotransError, JNIException;
    public native void JNISetGnomonicCoordinates(int state, int direction, Gnomonic coords) throws GeotransError, JNIException;
    
    public native LambertConformalConic1 JNIGetLambertConformalConic1Params(int state, int direction) throws GeotransError, JNIException;
    public native void JNISetLambertConformalConic1Params(int state, int direction, LambertConformalConic1 params) throws GeotransError, JNIException;
    public native LambertConformalConic1 JNIGetLambertConformalConic1Coordinates(int state, int direction) throws GeotransError, JNIException;
    public native void JNISetLambertConformalConic1Coordinates(int state, int direction, LambertConformalConic1 coords) throws GeotransError, JNIException;
    
    public native LambertConformalConic2 JNIGetLambertConformalConic2Params(int state, int direction) throws GeotransError, JNIException;
    public native void JNISetLambertConformalConic2Params(int state, int direction, LambertConformalConic2 params) throws GeotransError, JNIException;
    public native LambertConformalConic2 JNIGetLambertConformalConic2Coordinates(int state, int direction) throws GeotransError, JNIException;
    public native void JNISetLambertConformalConic2Coordinates(int state, int direction, LambertConformalConic2 coords) throws GeotransError, JNIException;
    
    public native LocalCartesian JNIGetLocalCartesianParams(int state, int direction) throws GeotransError, JNIException;
    public native void JNISetLocalCartesianParams(int state, int direction, LocalCartesian params) throws GeotransError, JNIException;
    public native LocalCartesian JNIGetLocalCartesianCoordinates(int state, int direction) throws GeotransError, JNIException;
    public native void JNISetLocalCartesianCoordinates(int state, int direction, LocalCartesian coords) throws GeotransError, JNIException;
   
    public native Mercator JNIGetMercatorParams(int state, int direction) throws GeotransError, JNIException;
    public native void JNISetMercatorParams(int state, int direction, Mercator params) throws GeotransError, JNIException;
    public native Mercator JNIGetMercatorCoordinates(int state, int direction) throws GeotransError, JNIException;
    public native void JNISetMercatorCoordinates(int state, int direction, Mercator coords) throws GeotransError, JNIException;
    
    public native MGRS JNIGetMGRSCoordinates(int state, int direction) throws GeotransError, JNIException;
    public native void JNISetMGRSCoordinates(int state, int direction, MGRS coords) throws GeotransError, JNIException;
    
    public native MillerCylindrical JNIGetMillerCylindricalParams(int state, int direction) throws GeotransError, JNIException;
    public native void JNISetMillerCylindricalParams(int state, int direction, MillerCylindrical params) throws GeotransError, JNIException;
    public native MillerCylindrical JNIGetMillerCylindricalCoordinates(int state, int direction) throws GeotransError, JNIException;
    public native void JNISetMillerCylindricalCoordinates(int state, int direction, MillerCylindrical coords) throws GeotransError, JNIException;
   
    public native Mollweide JNIGetMollweideParams(int state, int direction) throws GeotransError, JNIException;
    public native void JNISetMollweideParams(int state, int direction, Mollweide params) throws GeotransError, JNIException;
    public native Mollweide JNIGetMollweideCoordinates(int state, int direction) throws GeotransError, JNIException;
    public native void JNISetMollweideCoordinates(int state, int direction, Mollweide coords) throws GeotransError, JNIException;
    
    public native Neys JNIGetNeysParams(int state, int direction) throws GeotransError, JNIException;
    public native void JNISetNeysParams(int state, int direction, Neys params) throws GeotransError, JNIException;
    public native Neys JNIGetNeysCoordinates(int state, int direction) throws GeotransError, JNIException;
    public native void JNISetNeysCoordinates(int state, int direction, Neys coords) throws GeotransError, JNIException;
   
    public native NZMG JNIGetNZMGCoordinates(int state, int direction) throws GeotransError, JNIException;
    public native void JNISetNZMGCoordinates(int state, int direction, NZMG coords) throws GeotransError, JNIException;
   
    public native ObliqueMercator JNIGetObliqueMercatorParams(int state, int direction) throws GeotransError, JNIException;
    public native void JNISetObliqueMercatorParams(int state, int direction, ObliqueMercator params) throws GeotransError, JNIException;
    public native ObliqueMercator JNIGetObliqueMercatorCoordinates(int state, int direction) throws GeotransError, JNIException;
    public native void JNISetObliqueMercatorCoordinates(int state, int direction, ObliqueMercator coords) throws GeotransError, JNIException;
    
    public native Orthographic JNIGetOrthographicParams(int state, int direction) throws GeotransError, JNIException;
    public native void JNISetOrthographicParams(int state, int direction, Orthographic params) throws GeotransError, JNIException;
    public native Orthographic JNIGetOrthographicCoordinates(int state, int direction) throws GeotransError, JNIException;
    public native void JNISetOrthographicCoordinates(int state, int direction, Orthographic coords) throws GeotransError, JNIException;
   
    public native PolarStereographic JNIGetPolarStereographicParams(int state, int direction) throws GeotransError, JNIException;
    public native void JNISetPolarStereographicParams(int state, int direction, PolarStereographic params) throws GeotransError, JNIException;
    public native PolarStereographic JNIGetPolarStereographicCoordinates(int state, int direction) throws GeotransError, JNIException;
    public native void JNISetPolarStereographicCoordinates(int state, int direction, PolarStereographic coords) throws GeotransError, JNIException;
    
    public native Polyconic JNIGetPolyconicParams(int state, int direction) throws GeotransError, JNIException;
    public native void JNISetPolyconicParams(int state, int direction, Polyconic params) throws GeotransError, JNIException;
    public native Polyconic JNIGetPolyconicCoordinates(int state, int direction) throws GeotransError, JNIException;
    public native void JNISetPolyconicCoordinates(int state, int direction, Polyconic coords) throws GeotransError, JNIException;
    
    public native Sinusoidal JNIGetSinusoidalParams(int state, int direction) throws GeotransError, JNIException;
    public native void JNISetSinusoidalParams(int state, int direction, Sinusoidal params) throws GeotransError, JNIException;
    public native Sinusoidal JNIGetSinusoidalCoordinates(int state, int direction) throws GeotransError, JNIException;
    public native void JNISetSinusoidalCoordinates(int state, int direction, Sinusoidal coords) throws GeotransError, JNIException;
   
    public native Stereographic JNIGetStereographicParams(int state, int direction) throws GeotransError, JNIException;
    public native void JNISetStereographicParams(int state, int direction, Stereographic params) throws GeotransError, JNIException;
    public native Stereographic JNIGetStereographicCoordinates(int state, int direction) throws GeotransError, JNIException;
    public native void JNISetStereographicCoordinates(int state, int direction, Stereographic coords) throws GeotransError, JNIException;
    
    public native TransverseCylindricalEqualArea JNIGetTransverseCylindricalEqualAreaParams(int state, int direction) throws GeotransError, JNIException;
    public native void JNISetTransverseCylindricalEqualAreaParams(int state, int direction, TransverseCylindricalEqualArea params) throws GeotransError, JNIException;
    public native TransverseCylindricalEqualArea JNIGetTransverseCylindricalEqualAreaCoordinates(int state, int direction) throws GeotransError, JNIException;
    public native void JNISetTransverseCylindricalEqualAreaCoordinates(int state, int direction, TransverseCylindricalEqualArea coords) throws GeotransError, JNIException;
   
    public native TransverseMercator JNIGetTransverseMercatorParams(int state, int direction) throws GeotransError, JNIException;
    public native void JNISetTransverseMercatorParams(int state, int direction, TransverseMercator params) throws GeotransError, JNIException;
    public native TransverseMercator JNIGetTransverseMercatorCoordinates(int state, int direction) throws GeotransError, JNIException;
    public native void JNISetTransverseMercatorCoordinates(int state, int direction, TransverseMercator coords) throws GeotransError, JNIException;
    
    public native UPS JNIGetUPSCoordinates(int state, int direction) throws GeotransError, JNIException;
    public native void JNISetUPSCoordinates(int state, int direction, UPS coords) throws GeotransError, JNIException;
    
    public native USNG JNIGetUSNGCoordinates(int state, int direction) throws GeotransError, JNIException;
    public native void JNISetUSNGCoordinates(int state, int direction, USNG coords) throws GeotransError, JNIException;
    
    public native void JNISetUTMParams(int state, int direction, UTM params) throws GeotransError, JNIException;
    public native UTM JNIGetUTMCoordinates(int state, int direction) throws GeotransError, JNIException;
    public native void JNISetUTMCoordinates(int state, int direction, UTM coords) throws GeotransError, JNIException;
    
    public native VanDerGrinten JNIGetVanDerGrintenParams(int state, int direction) throws GeotransError, JNIException;
    public native void JNISetVanDerGrintenParams(int state, int direction, VanDerGrinten params) throws GeotransError, JNIException;
    public native VanDerGrinten JNIGetVanDerGrintenCoordinates(int state, int direction) throws GeotransError, JNIException;
    public native void JNISetVanDerGrintenCoordinates(int state, int direction, VanDerGrinten coords) throws GeotransError, JNIException;
    
    
}
