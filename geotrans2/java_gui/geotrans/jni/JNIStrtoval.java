/*
 * JNIStrtoval.java
 *
 * Created on April 9, 2001, 4:22 PM
 */

package geotrans.jni;

/**
 *
 * @author  amyc
 * @version 
 */
public class JNIStrtoval extends Object {

    private java.lang.String title = "Geographic Translator V2.4.2";
    public final static double PI = 3.14159265358979323e0;  
    private java.lang.String errorMsg[] = new java.lang.String[22];
    private boolean engineError = false;
    private boolean jniError = false;
    private int numErrors = 0;
    
    /** Creates new JNIStrtoval */
    public JNIStrtoval() {
        initialize();
}
    
public native java.lang.String JNIErrorPrefix ( int direction,  int system);
public native java.lang.String JNILatitudeToString(final double latitude, boolean use_NSEW, 
                        boolean use_Minutes, boolean use_Seconds) throws GeotransError, JNIException;
public native java.lang.String JNILongitudeToString(final double longitude, boolean use_NSEW,  
                         boolean use_Minutes, boolean use_Seconds) throws GeotransError, JNIException;
public native java.lang.String JNIMeterToString(final double meters) throws GeotransError, JNIException;
public native void JNISetSeparator(char sep);
public native void JNISetLongRange(int range);
public native void JNISetLatLongPrecision(long precis);
public native void JNIShowLeadingZeros(boolean lz);
public native double JNIStringToDouble(java.lang.String str) throws GeotransError, JNIException;
public native double JNIStringToLatitude(java.lang.String str) throws GeotransError, JNIException;
public native long JNIStringToLong(java.lang.String str) throws GeotransError, JNIException;
public native double JNIStringToLongitude(java.lang.String str) throws GeotransError, JNIException;

    
    public double stringToLatitude(java.lang.String str, java.lang.String msg)
    {
        double lat = 0;
        
        try
        {
            if (str.equals(""))
                throw new GeotransError(msg);
            lat = JNIStringToLatitude(str)*PI/180;
        }   
        catch(GeotransError e)
        {
            errorMsg[numErrors] = msg;
            numErrors++;
            engineError = true;
        }
        catch(JNIException e)
        {
            errorMsg[numErrors] = e.getMessage();
            numErrors++;
            jniError = true;
        }
        return lat;
    }
    
    public double stringToLongitude(java.lang.String str, java.lang.String msg)
    {
        double lon = 0;
        
        try
        {
            if (str.equals(""))
                throw new GeotransError(msg);
            lon = JNIStringToLongitude(str)*PI/180;
        }   
        catch(GeotransError e)
        {
            errorMsg[numErrors] = msg;
            numErrors++;
            engineError = true;
        }
        catch(JNIException e)
        {
            errorMsg[numErrors] = e.getMessage();
            numErrors++;
            jniError = true;
        }
        return lon;
    }
  
    public double stringToDouble(java.lang.String str, java.lang.String msg)
    {
        double num = 0;
        
        try
        {
            if (str.equals(""))
                throw new GeotransError(msg);
            num = JNIStringToDouble(str);
        }   
        catch(GeotransError e)
        {
            errorMsg[numErrors] = msg;
            numErrors++;            
            engineError = true;
        }
        catch(JNIException e)
        {
            errorMsg[numErrors] = e.getMessage();
            numErrors++;
            jniError = true;
        }
        return num;
    }

    public long stringToLong(java.lang.String str, java.lang.String msg)
    {
        long num = 0;
        
        try
        {
            if (str.equals(""))
                throw new GeotransError(msg);
            num = JNIStringToLong(str);
        }   
        catch(GeotransError e)
        {
            errorMsg[numErrors] = msg;
            numErrors++;            
            engineError = true;
        }
        catch(JNIException e)
        {
            errorMsg[numErrors] = e.getMessage();
            numErrors++;
            jniError = true;
        }
        return num;
    }
    
    public void displayErrorMsg(java.awt.Component parent)
    {
        javax.swing.JOptionPane.showMessageDialog(parent, errorMsg, title, javax.swing.JOptionPane.ERROR_MESSAGE);
        initialize();
    }  
    
    public void displayErrorMsg(java.awt.Component parent, java.lang.String msg)
    {
        javax.swing.JOptionPane.showMessageDialog(parent, "Error: \n" + msg, title, javax.swing.JOptionPane.ERROR_MESSAGE);
    }  
    
    public void displayErrorMsg(java.awt.Component parent, int dir, int projType)
    {
        errorMsg[0] = "Error: \n" + JNIErrorPrefix(dir, projType);
        errorMsg[1] = " ";
        javax.swing.JOptionPane.showMessageDialog(parent, errorMsg, title, javax.swing.JOptionPane.ERROR_MESSAGE);
        initialize();
    }  
    
    public void displayWarningMsg(java.awt.Component parent, java.lang.String msg)
    {
        javax.swing.JOptionPane.showMessageDialog(parent, "Warning: \n" + msg, title, javax.swing.JOptionPane.WARNING_MESSAGE);
    }  
    
    public boolean getEngineError()
    {
        return engineError;
    }
    
    public void setEngineError(boolean error, java.lang.String msg)
    {
        engineError = error;
        errorMsg[numErrors] = msg;
        numErrors++;
    }
    
    public boolean getJNIError()
    {
        return jniError;
    }
  
    public java.lang.String getTitle()
    {
        return title;
    }
    
    public void setJNIError(boolean error, java.lang.String msg)
    {
        jniError = error;
        errorMsg[numErrors] = msg;
        numErrors++;
    }
    
    private void initialize()
    {
        engineError = false;
        jniError = false;
        numErrors = 2;
        for (int i = 0; i < 10; i++)
            errorMsg[i] = "";
    }
    
    public void setNumberFormat(javax.swing.JTextField textField, double num, int digits)
    {
        java.text.NumberFormat nf = java.text.NumberFormat.getNumberInstance();
        nf.setMaximumFractionDigits(digits);
        nf.setMinimumFractionDigits(digits);
        textField.setText(nf.format(num));
    }
}
