/*
 * Accuracy.java
 *
 * Created on April 24, 2001, 11:54 AM
 */

package geotrans.gui;


/**
 *
 * @author  amyc
 * @version 
 */
public class Accuracy extends Object {

    private double ce90;
    private double le90;
    private double se90;
    
    /** Creates new Accuracy */
    public Accuracy() {
    }
    
    public Accuracy(double ce_90,double le_90,double se_90)
    {
        ce90 = ce_90;
        le90 = le_90;
        se90 = se_90;
    }
    
    public double getCE90()
    {
        return ce90;
    }
    
    public double getLE90()
    {
        return le90;
    }
    
    public double getSE90()
    {
        return se90;
    }
}
