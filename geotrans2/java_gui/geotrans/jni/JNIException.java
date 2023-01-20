/*
 * JNIException.java
 *
 * Created on April 13, 2001, 4:52 PM
 */

package geotrans.jni;

/**
 *
 * @author  amyc
 * @version 
 */
public class JNIException extends java.lang.Exception {

    /**
 * Creates new <code>JNIException</code> without detail message.
     */
    public JNIException() {
    }


    /**
 * Constructs an <code>JNIException</code> with the specified detail message.
     * @param msg the detail message.
     */
    public JNIException(String msg) {
        super(msg);
    }
}


