/*
 * Geodetic.java
 *
 * Created on April 10, 2001, 1:08 PM
 */

package geotrans.projections;

/**
 *
 * @author  amyc
 * @version 
 */

public class Geodetic extends Object {

    private int heightType;
    
    // Coordinates
    private double longitude;
    private double latitude;
    private double height;
    
    /** Creates new Geodetic */
    public Geodetic() {
    }
    
    public Geodetic(int htType)
    {
        heightType = htType;
    }
    
    public Geodetic(double lon, 
                    double lat, 
                    double ht)
    {
        longitude = lon;
        latitude = lat;
        height = ht;
    }
    
    public int getHeightType()
    {
        return heightType;
    }
    
    public double getLongitude()
    {
        return longitude;
    }
    
    public double getLatitude()
    {
        return latitude;
    }
    
    public double getHeight()
    {
        return height;
    }
}
