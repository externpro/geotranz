/*
 * MillerCylindrical.java
 *
 * Created on April 10, 2001, 12:41 PM
 */

package geotrans.projections;

/**
 *
 * @author  amyc
 * @version 
 */
public class MillerCylindrical extends Object {

    // Parameters
    private double central_meridian;  
    private double false_easting;     
    private double false_northing; 
    
    // Coordinates
    private double easting;
    private double northing;

    /** Creates new MillerCylindrical */
    public MillerCylindrical() {
    }

    public MillerCylindrical(double cent_merid, 
                             double feast,
                             double fnorth) 
    {
        central_meridian = cent_merid;
        false_easting = feast;
        false_northing = fnorth;
    }
    
    public MillerCylindrical(double east, 
                             double north) 
    {
        easting = east;
        northing = north;
    }

    public double getCentralMeridian()
    {
        return central_meridian;
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
