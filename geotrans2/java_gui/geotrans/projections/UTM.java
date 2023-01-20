/*
 * UTM.java
 *
 * Created on April 11, 2001, 3:33 PM
 */

package geotrans.projections;

/**
 *
 * @author  amyc
 * @version 
 */
public class UTM extends Object {

    // Parameters
    private long zone;
    private long override;
    
    // Coordinates
    private double easting;
    private double northing;
    private int zoneCoord;
    private char hemisphere;

    
    /** Creates new UTM */
    public UTM() {
    }
    
    public UTM(long z,
               long o)
    {
        zone = z;
        override = o;
    }
    
    public UTM(double east, 
               double north, 
               int z,
               char hemi)
    {
        easting = east;
        northing = north;
        
        zoneCoord = z;
        hemisphere = hemi;
    }
    
    public long getZone()
    {
        return zone;
    }
    
    public int getZoneCoord()
    {
        return zoneCoord;
    }
    
    public long getOverride()
    {
        return override;
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
