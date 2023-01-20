/*
 * Center.java
 *
 * Created on May 3, 2001, 9:27 AM
 */

package geotrans.utility;

/**
 *
 * @author  amyc
 * @version 
 */
public class Center extends Object {

    /** Creates new Center */
    public Center(java.awt.Container parent, java.awt.Component comp) 
    {
        int x, y; 
        java.awt.Rectangle boundingRect; 
        java.awt.Dimension compSize = comp.getSize();
        
        // If Container is null then our bounding rectangle is the whole screen 
        if (parent == null)  
        { 
            boundingRect = new java.awt.Rectangle(comp.getToolkit().getScreenSize()); 
            boundingRect.setLocation(0,0); 
        } 
        // Else bounding rectangle is the Container 
        else 
            boundingRect = parent.getBounds(); 
        
        // Place the component so its center is the same 
        // as the center of the bounding rectangle 
        x = boundingRect.x + ((boundingRect.width/2) - (compSize.width/2)); 
        y = boundingRect.y + ((boundingRect.height/2) - (compSize.height/2)); 
        
        comp.setLocation(x, y);
    } 
}
