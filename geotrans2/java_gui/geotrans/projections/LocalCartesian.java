/*
 * LocalCartesian.java
 *
 * Created on April 10, 2001, 1:04 PM
 */

package geotrans.projections;

/**
 *
 * @author  amyc
 * @version 
 */
public class LocalCartesian extends Object {

    // Parameters
    double  origin_latitude;  
    double  origin_longitude; 
    double  origin_height;    
    double  orientation;     
    
    // Coordinates
    double x;
    double y;
    double z;
    
    /** Creates new LocalCartesian */
    public LocalCartesian() {
    }

    public LocalCartesian(double olat, 
                          double olon,
                          double oheight,
                          double orientat) 
    {
        origin_latitude = olat;
        origin_longitude = olon;
        origin_height = oheight;
        orientation = orientat;
    }
    
    public LocalCartesian(double _x, 
                          double _y,
                          double _z)
    {
        x = _x;
        y = _y;
        z = _z;
    }
    
    public double getOriginLatitude()
    {
        return origin_latitude;
    }
    
    public double getOriginLongitude()
    {
        return origin_longitude;
    }

    public double getOriginHeight()
    {
        return origin_height;
    }
    
    public double getOrientation()
    {
        return orientation;
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
