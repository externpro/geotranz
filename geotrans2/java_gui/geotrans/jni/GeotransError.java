




/*
 * GeotransException.java
 *
 * Created on April 13, 2001, 1:34 PM
 */

package geotrans.jni;

/**
 *
 * @author  amyc
 * @version 
 */
public class GeotransError extends java.lang.Exception {

    /**
 * Creates new <code>GeotransException</code> without detail message.
     */
    public GeotransError() {
    }


    /**
 * Constructs an <code>GeotransException</code> with the specified detail message.
     * @param msg the detail message.
     */
    public GeotransError(String msg) {
        super(msg);
    }
}


