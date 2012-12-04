/*
 * NZMG.java
 *
 * Created on April 20, 2001, 2:54 PM
 */

package geotrans.projections;

/**
 *
 * @author  amyc
 * @version 
 */
public class NZMG extends Object {

    // Coordinates
    private double easting;
    private double northing;

    /** Creates new NZMG */
    public NZMG() {
    }

    public NZMG(double east, 
                double north) 
    {
        easting = east;
        northing = north;
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
