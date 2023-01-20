/*
 * USNG.java
 *
 * Created on June 7, 2006, 12:55 PM
 */

package geotrans.projections;

/**
 *
 * @author  amyc
 * @version 
 */
public class USNG extends Object {

    private java.lang.String coordinateString;
    
    /** Creates new MGRS */
    public USNG() {
    }

    public USNG(java.lang.String coordString)
    {
        coordinateString = coordString;
    }
    
    public java.lang.String getCoordinateString()
    {
        return coordinateString;
    }
}
