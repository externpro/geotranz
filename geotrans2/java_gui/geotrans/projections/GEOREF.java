/*
 * GEOREF.java
 *
 * Created on April 20, 2001, 2:53 PM
 */

package geotrans.projections;

/**
 *
 * @author  amyc
 * @version 
 */
public class GEOREF extends Object {

    private java.lang.String coordinateString;
    
    /** Creates new GEOREF */
    public GEOREF() {
    }

    public GEOREF(java.lang.String coordString)
    {
        coordinateString = coordString;
    }
    
    public java.lang.String getCoordinateString()
    {
        return coordinateString;
    }
}
