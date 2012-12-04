/*
 * BNG.java
 *
 * Created on April 20, 2001, 2:50 PM
 */

package geotrans.projections;

/**
 *
 * @author  amyc
 * @version 
 */
public class BNG extends Object {

    private java.lang.String coordinateString;
    
    /** Creates new BNG */
    public BNG() {
    }
    
    public BNG(java.lang.String coordString)
    {
        coordinateString = coordString;
    }
    
    public java.lang.String getCoordinateString()
    {
        return coordinateString;
    }
}
