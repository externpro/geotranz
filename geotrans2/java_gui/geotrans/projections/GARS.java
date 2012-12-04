/*
 * GARS.java
 *
 * Created on April 20, 2001, 2:53 PM
 */

package geotrans.projections;

/**
 *
 * @author  amyc
 * @version 
 */
public class GARS extends Object {

    private java.lang.String coordinateString;
    
    /** Creates new GARS */
    public GARS() {
    }

    public GARS(java.lang.String coordString)
    {
        coordinateString = coordString;
    }
    
    public java.lang.String getCoordinateString()
    {
        return coordinateString;
    }
}
