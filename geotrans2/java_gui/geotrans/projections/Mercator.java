/*
 * Mercator.java
 *
 * Created on April 10, 2001, 12:37 PM
 */

package geotrans.projections;

/**
 *
 * @author  amyc
 * @version 
 */
public class Mercator extends Object {

    // Parameters
    private double latitude_of_true_scale;   
    private double central_meridian;
    private double scale_factor;
    private double false_easting;     
    private double false_northing;    
    
    // Coordinates
    private double easting;
    private double northing;

    /** Creates new Mercator */
    public Mercator() {
    }

    public Mercator(double lat_of_true_scale, 
                    double cent_merid,
                    double scale_fact,
                    double feast,
                    double fnorth) 
    {
        latitude_of_true_scale = lat_of_true_scale;
        central_meridian = cent_merid;
        scale_factor = scale_fact;
        false_easting = feast;
        false_northing = fnorth;
    }
    
    public Mercator(double east, 
                    double north) 
    {
        easting = east;
        northing = north;
    }
    
    public double getLatitudeOfTrueScale()
    {
        return latitude_of_true_scale;
    }
    
    public double getCentralMeridian()
    {
        return central_meridian;
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
