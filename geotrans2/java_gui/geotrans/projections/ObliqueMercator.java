/*
 * ObliqueMercator.java
 *
 * Created on April 10, 2001, 12:47 PM
 */

package geotrans.projections;

/**
 *
 * @author  amyc
 * @version 
 */
public class ObliqueMercator extends Object {

    // Parameters
    double  origin_latitude;   
    double  latitude_1;        
    double  longitude_1;       
    double  latitude_2;        
    double  longitude_2;       
    double  scale_factor;      
    double  false_easting;     
    double  false_northing;    
    
    // Coordinates
    private double easting;
    private double northing;

    /** Creates new ObliqueMercator */
    public ObliqueMercator() {
    }
    
    public ObliqueMercator(double olat, 
                           double lat_1,
                           double lon_1,
                           double lat_2,
                           double lon_2,
                           double scale_fact,
                           double feast,
                           double fnorth) 
    {
        origin_latitude = olat;
        latitude_1 = lat_1;
        longitude_1 = lon_1;
        latitude_2 = lat_2;
        longitude_2 = lon_2;
        scale_factor = scale_fact;
        false_easting = feast;
        false_northing = fnorth;
    }
        
    public ObliqueMercator(double east, 
                           double north) 
    {
        easting = east;
        northing = north;
    }

    public double getOriginLatitude()
    {
        return origin_latitude;
    }
    
    public double getLatitude1()
    {
        return latitude_1;
    }

    public double getLongitude1()
    {
        return longitude_1;
    }

    public double getLatitude2()
    {
        return latitude_2;
    }
    
    public double getLongitude2()
    {
        return longitude_2;
    }

    public double getScaleFactor()
    {
        return scale_factor;
    }

    public double getFalseEasting()
    {
        return false_easting;
    }
    
    public double getFalseNorthing()
    {
        return false_northing;
    }
       
    public double getEasting()
    {
        return easting;
    }
    
    public double getNorthing()
    {
        return northing;
    }
}
