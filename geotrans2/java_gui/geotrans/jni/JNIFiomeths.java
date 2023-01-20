/*
 * JNIFiomeths.java
 *
 * Created on April 9, 2001, 4:22 PM
 */

package geotrans.jni;

/**
 *
 * @author  amyc
 * @version 
 */
public class JNIFiomeths extends Object {

    /** Creates new JNIFiomeths */
    public JNIFiomeths() {
    }

    
    public native void JNICloseInputFile();
    public native void JNICloseOutputFile();
    public native void JNIConvertFile() throws GeotransError;
    public native java.lang.String JNIGetFileErrorString(long error) throws JNIException;
    public native long JNIGetNumErrors();
    public native long JNIGetNumProcessed();
    public native long JNIGetNumWarnings();
    public native void JNISetInputFilename(java.lang.String fileName) throws GeotransError, JNIException;    
    public native long JNISetOutputFilename(java.lang.String fileName) throws GeotransError, JNIException;   
    public native void JNIUseNSEW(boolean value);
    public native void JNIUseMinutes(boolean value);
    public native void JNIUseSeconds(boolean value);
    public native void JNIWriteExampleCoord();

}
