/*
 * VanDerGrinten.java
 *
 * Created on April 10, 2001, 1:03 PM
 */

package geotrans.projections;

/**
 *
 * @author  amyc
 * @version 
 */
public class VanDerGrinten extends Object {

    // Parameters
    private double central_meridian;  
    private double false_easting;     
    private double false_northing; 
    
    // Coordinates
    private double easting;
    private double northing;
    
    /** Creates new VanDerGrinten */
    public VanDerGrinten() {
    }

    public VanDerGrinten(double cent_merid, 
                         double feast,
                         double fnorth) 
    {
        central_meridian = cent_merid;
        false_easting = feast;
        false_northing = fnorth;
    }
    
    public VanDerGrinten(double east, 
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
