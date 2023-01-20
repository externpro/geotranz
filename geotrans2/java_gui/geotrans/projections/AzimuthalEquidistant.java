/*
 * AzimuthalEquidistant.java
 *
 * Created on April 10, 2001, 10:24 AM
 */

package geotrans.projections;

/**
 *
 * @author  amyc
 * @version 
 */
public class AzimuthalEquidistant extends Object {

    // Parameters
    private double origin_latitude;   
    private double central_meridian;  
    private double false_easting;     
    private double false_northing;    

    // Coordinates
    private double easting;
    private double northing;

    /** Creates new AzimuthalEquidistant */
    public AzimuthalEquidistant() {
    }
    
    public AzimuthalEquidistant(double olat, 
                                double cent_merid,
                                double feast,
                                double fnorth) 
    {
        origin_latitude = olat;
        central_meridian = cent_merid;
        false_easting = feast;
        false_northing = fnorth;
    }
    
    public AzimuthalEquidistant(double east, 
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
