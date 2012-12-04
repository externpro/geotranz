/*
 * Neys.java
 *
 * Created on April 10, 2001, 12:43 PM
 */

package geotrans.projections;

/**
 *
 * @author  amyc
 * @version 
 */
public class Neys extends java.lang.Object {

    // Parameters
    private double origin_latitude;   
    private double central_meridian;  
    private double std_parallel_1;    
    private double false_easting;     
    private double false_northing;    

    // Coordinates
    private double easting;
    private double northing;

    /** Creates new Ney's (Modified Lambert Conformal Conic) */
    public Neys() {
    }

    public Neys(double olat, 
                double cent_merid,
                double std_par_1,
                double feast,
                double fnorth) 
    {
        origin_latitude = olat;
        central_meridian = cent_merid;
        std_parallel_1 = std_par_1;
        false_easting = feast;
        false_northing = fnorth;
    }
    
    public Neys(double east, 
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

    public double getStdParallel1()
    {
        return std_parallel_1;
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
