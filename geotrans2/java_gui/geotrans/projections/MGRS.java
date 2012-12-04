



/*
 * MGRS.java
 *
 * Created on April 20, 2001, 2:54 PM
 */

package geotrans.projections;

/**
 *
 * @author  amyc
 * @version 
 */
public class MGRS extends Object {

    private java.lang.String coordinateString;
    
    /** Creates new MGRS */
    public MGRS() {
    }

    public MGRS(java.lang.String coordString)
    {
        coordinateString = coordString;
    }
    
    public java.lang.String getCoordinateString()
    {
        return coordinateString;
    }
}
