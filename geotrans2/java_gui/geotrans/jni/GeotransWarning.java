/*
 * GeotransWarning.java
 *
 * Created on April 24, 2001, 1:31 PM
 */

package geotrans.jni;

/**
 *
 * @author  amyc
 * @version 
 */
public class GeotransWarning extends java.lang.Exception {

    /**
 * Creates new <code>GeotransWarning</code> without detail message.
     */
    public GeotransWarning() {
    }


    /**
 * Constructs an <code>GeotransWarning</code> with the specified detail message.
     * @param msg the detail message.
     */
    public GeotransWarning(String msg) {
        super(msg);
    }
}


