/*
 * UPS.java
 *
 * Created on April 20, 2001, 1:40 PM
 */

package geotrans.projections;

/**
 *
 * @author  amyc
 * @version 
 */
public class UPS extends Object {

    // Coordinates
    private double easting;
    private double northing;
    private char hemisphere;

    /** Creates new UPS */
    public UPS() {
    }

    public UPS(double east, 
               double north, 
               char hemi)
    {
        easting = east;
        northing = north;
        hemisphere = hemi;
    }
    
    public double getEasting()
    {
        return easting;
    }
    
    public double getNorthing()
    {
        return northing;
    }
    
    public char getHemisphere()
    {
        return hemisphere;
    }
}
