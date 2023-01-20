/*
 * LocalCartesianParameters.java
 *
 * Created on April 6, 2007, 3:10 PM
 *
 * To change this template, choose Tools | Template Manager
 * and open the template in the editor.
 */

package geotrans.parameters;

/**
 *
 * @author comstam
 */
public class LocalCartesianParameters extends CoordinateSystemParameters 
{
  private double longitude;
  private double latitude;
  private double height;
  private double orientation;

      
  /** Creates a new instance of LocalCartesianParameters */
  public LocalCartesianParameters(int coordinateType, double _longitude, double _latitude, double _height, double _orientation) 
  {
     super(coordinateType);
    
    longitude = _longitude;
    latitude = _latitude;
    height = _height;
    orientation = _orientation;
 }
  
  
  public double getLongitude()
  {
    return longitude;
  }


  public double getLatitude()
  {
    return latitude;
  }


  public double getHeight()
  {
    return height;
  }


  public double getOrientation()
  {
    return orientation;
  }  
}
