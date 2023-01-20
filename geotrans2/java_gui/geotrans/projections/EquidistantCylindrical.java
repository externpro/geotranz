/*
 * EquidistantCylindrical.java
 *
 * Created on April 10, 2001, 12:33 PM
 */

package geotrans.projections;

/**
 *
 * @author  amyc
 * @version 
 */
public class EquidistantCylindrical extends Object {

    // Parameters
    private double std_parallel;   
    private double central_meridian;  
    private double false_easting;     
    private double false_northing;    
    
    // Coordinates
    private double easting;
    private double northing;

    /** Creates new EquidistantCylindrical */
    public EquidistantCylindrical() {
    }

    public EquidistantCylindrical(double std_par, 
                                  double cent_merid,
                                  double feast,
                                  double fnorth) 
    {
        std_parallel = std_par;
        central_meridian = cent_merid;
        false_easting = feast;
        false_northing = fnorth;
    }
    
    public EquidistantCylindrical(double east, 
                                  double north) 
    {
        easting = east;
        northing = north;
    }

    public double getStdParallel()
    {
        return std_parallel;
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
