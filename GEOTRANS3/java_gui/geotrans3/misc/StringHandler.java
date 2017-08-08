// CLASSIFICATION: UNCLASSIFIED

/*
 * StringHandler.java
 *
 * Created on April 9, 2001, 4:22 PM
 *
 * MODIFICATION HISTORY:
 *
 * DATE      NAME        DR#               DESCRIPTION
 *
 * 08/13/10  S Gillis    BAEts27457        Update to GeoTrans 3.1
 */

package geotrans3.misc;


import geotrans3.misc.StringToVal;
import geotrans3.exception.CoordinateConversionException;
import geotrans3.enumerations.CoordinateType;
import geotrans3.enumerations.SourceOrTarget;
import geotrans3.utility.Constants;


/**
 *
 * @author  amyc
 * @version 
 */
public class StringHandler extends Object 
{
  private final java.lang.String title = "MSP GEOTRANS 3.1";
  
  private java.lang.String errorMsg[];
  private boolean ccsError = false;
  private int numErrors = 0;
  private StringToVal stringToVal;
  private final int maxErrors = 20;

  
  /** Creates new StringHandler */
  public StringHandler() 
  {
    errorMsg = new java.lang.String[maxErrors];
    stringToVal = new StringToVal();
    initialize();
  }
    
    
  public StringHandler(StringToVal _stringToVal) 
  {
    errorMsg = new java.lang.String[maxErrors];
    stringToVal = _stringToVal;
    initialize();
  }


  public void setPrecision(int _precision)
  {
    stringToVal.setPrecision(_precision);
  }
  
    
  public String longitudeToString(final double longitude, boolean use_NSEW, boolean use_Minutes, boolean use_Seconds) throws CoordinateConversionException
  {
    return stringToVal.longitudeToString(longitude, use_NSEW, use_Minutes, use_Seconds);
  }


  public String latitudeToString(final double latitude, boolean use_NSEW, boolean use_Minutes, boolean use_Seconds) throws CoordinateConversionException
  {
    return stringToVal.latitudeToString(latitude, use_NSEW, use_Minutes, use_Seconds);
  }


  public String meterToString(final double meters)
  {
    return stringToVal.meterToString(meters);
  }


  public double stringToLatitude(java.lang.String str, java.lang.String msg)
  {
    double lat = 0;

    try
    {
      if (str.equals(""))
        throw new CoordinateConversionException(msg);
      
      lat = stringToVal.stringToLatitude(str) * Constants.PI_OVER_180;
    }   
    catch(CoordinateConversionException e)
    {
      errorMsg[numErrors] = msg + e.getMessage();
      numErrors++;
      ccsError = true;
    }
    
    return lat;
  }
    
  
  public double stringToLongitude(java.lang.String str, java.lang.String msg)
  {
    double lon = 0;

    try
    {
      if (str.equals(""))
        throw new CoordinateConversionException(msg);
      
      lon = stringToVal.stringToLongitude(str) * Constants.PI_OVER_180;
    }   
    catch(CoordinateConversionException e)
    {
      errorMsg[numErrors] = msg + e.getMessage();
      numErrors++;
      ccsError = true;
    }
    
    return lon;
  }
  
  
  public double stringToDouble(java.lang.String str, java.lang.String msg)
  {
    double num = 0;

    try
    {
      if (str.equals(""))
        throw new CoordinateConversionException(msg);
      
      num = stringToVal.stringToDouble(str);
    }   
    catch(CoordinateConversionException e)
    {
      errorMsg[numErrors] = msg + e.getMessage();
      numErrors++;            
      ccsError = true;
    }
    
    return num;
  }

  
  public int stringToInt(java.lang.String str, java.lang.String msg)
  {
    int num = 0;

    try
    {
      if (str.equals(""))
        throw new CoordinateConversionException(msg);
      
      num = stringToVal.stringToInt(str);
    }   
    catch(CoordinateConversionException e)
    {
      errorMsg[numErrors] = msg + e.getMessage();
      numErrors++;            
      ccsError = true;
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
    errorMsg[0] = "Error: \n" + SourceOrTarget.name(dir) + " " + CoordinateType.name(projType) + ": ";
    errorMsg[1] = " ";
    javax.swing.JOptionPane.showMessageDialog(parent, errorMsg, title, javax.swing.JOptionPane.ERROR_MESSAGE);
    initialize();
  }  

  
  public void displayWarningMsg(java.awt.Component parent, java.lang.String msg)
  {
    javax.swing.JOptionPane.showMessageDialog(parent, "Warning: \n" + msg, title, javax.swing.JOptionPane.WARNING_MESSAGE);
  }  

  
  public void displayPlainMsg(java.awt.Component parent, java.lang.String msg)
  {
    javax.swing.JOptionPane.showMessageDialog(parent, msg, title, javax.swing.JOptionPane.PLAIN_MESSAGE);
  }  

  
  public boolean getError()
  {
    return ccsError;
  }
  
  
  public void setErrorMessage(boolean error, java.lang.String msg)
  {
    ccsError = error;
    errorMsg[numErrors] = msg;
    numErrors++;
  }
    
  
  private void initialize()
  {
    ccsError = false;
    numErrors = 2;
    for (int i = 0; i < maxErrors; i++)
        errorMsg[i] = "";
  }

  
  public void setNumberFormat(javax.swing.JTextField textField, double num, int digits)
  {
    java.text.NumberFormat nf = java.text.NumberFormat.getNumberInstance();
    nf.setMaximumFractionDigits(digits);
    nf.setMinimumFractionDigits(digits);
    textField.setText(nf.format(num));
  }
  
  
  public String getTitle()
  {
    return title;
  }
}

// CLASSIFICATION: UNCLASSIFIED
