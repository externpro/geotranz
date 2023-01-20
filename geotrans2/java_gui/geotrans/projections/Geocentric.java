/*
 * Geocentric.java
 *
 * Created on April 20, 2001, 2:55 PM
 */

package geotrans.projections;

/**
 *
 * @author  amyc
 * @version 
 */
public class Geocentric extends Object {

    // Coordinates
    double x;
    double y;
    double z;

    /** Creates new Geocentric */
    public Geocentric() {
    }

    public Geocentric(double _x, 
                      double _y,
                      double _z)
    {
        x = _x;
        y = _y;
        z = _z;
    }
    
    public double getX()
    {
        return x;
    }
    
    public double getY()
    {
        return y;
    }
    
    public double getZ()
    {
        return z;
    }
}
