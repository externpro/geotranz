/*
 * JNISource.java
 *
 * Created on May 24, 2001, 4:44 PM
 */

package geotrans.jni;


import geotrans.gui.Accuracy;


/**
 *
 * @author  amyc
 * @version 
 */
public class JNISource extends Object {

    /** Creates new JNISource */
    public JNISource() {
    }
    
    public native long JNISourceCount();
    public native long JNISourceIndex(java.lang.String name) throws GeotransError, JNIException;
    public native java.lang.String JNISourceName(long index) throws GeotransError, JNIException;
    public native Accuracy JNISourceAccuracy(long index) throws GeotransError, JNIException;

}
