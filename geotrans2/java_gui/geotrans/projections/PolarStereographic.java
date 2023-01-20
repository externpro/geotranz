/*
 * PolarStereographic.java
 *
 * Created on April 10, 2001, 12:55 PM
 */

package geotrans.projections;

/**
 *
 * @author  amyc
 * @version 
 */
public class PolarStereographic extends Object {

    // Parameters
    double  latitude_of_true_scale;   
    double  longitude_down_from_pole; 
    private double false_easting;     
    private double false_northing;    
    
    // Coordinates
    private double easting;
    private double northing;

    /** Creates new PolarStereographic */
    public PolarStereographic() {
    }

    public PolarStereographic(double lat_of_true_scale, 
                              double lon_down_from_pole,
                              double feast,
                              double fnorth) 
    {
        latitude_of_true_scale = lat_of_true_scale;
        longitude_down_from_pole = lon_down_from_pole;
        false_easting = feast;
        false_northing = fnorth;
    }
    
    public PolarStereographic(double east, 
                              double north) 
    {
        easting = east;
        northing = north;
    }
    
    public double getLatitudeOfTrueScale()
    {
        return latitude_of_true_scale;
    }
    
    public double getLongitudeDownFromPole()
    {
        return longitude_down_from_pole;
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
