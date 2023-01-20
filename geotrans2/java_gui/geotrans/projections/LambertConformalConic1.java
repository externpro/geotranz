/*
 * LambertConformalConic1.java
 *
 * Created on March 18, 2005, 12:06 PM
 */

package geotrans.projections;

/**
 *
 * @author  amyc
 * @version 
 */
public class LambertConformalConic1 extends Object {

    // Parameters
    private double origin_latitude;   
    private double central_meridian;
    private double scale_factor;
    private double false_easting;     
    private double false_northing;    
    
    // Coordinates
    private double easting;
    private double northing;
    
    /** Creates new LambertConformalConic1 */
    public LambertConformalConic1() {
    }

    public LambertConformalConic1(double olat, double cent_merid, double scale_fact, double feast, double fnorth) 
    {
        origin_latitude = olat;
        central_meridian = cent_merid;
        scale_factor = scale_fact;
        false_easting = feast;
        false_northing = fnorth;
    }
    
    public LambertConformalConic1(double east, double north) 
    {
        easting = east;
        northing = north;
    }
    
    public double getOriginLatitude()
    {
        return origin_latitude;
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
