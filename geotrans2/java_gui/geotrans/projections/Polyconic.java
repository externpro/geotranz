/*
 * Polyconic.java
 *
 * Created on April 10, 2001, 12:54 PM
 */

package geotrans.projections;

/**
 *
 * @author  amyc
 * @version 
 */
public class Polyconic extends Object {

    // Parameters
    private double origin_latitude;   
    private double central_meridian;  
    private double false_easting;     
    private double false_northing;    

    // Coordinates
    private double easting;
    private double northing;

    /** Creates new Polyconic */
    public Polyconic() {
    }

    public Polyconic(double olat, 
                     double cent_merid,
                     double feast,
                     double fnorth) 
    {
        origin_latitude = olat;
        central_meridian = cent_merid;
        false_easting = feast;
        false_northing = fnorth;
    }
    
    public Polyconic(double east, 
                     double north) 
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
