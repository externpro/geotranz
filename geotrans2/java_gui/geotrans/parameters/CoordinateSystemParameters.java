/*
 * CoordinateSystemParameters.java
 *
 * Created on April 3, 2007, 1:27 PM
 *
 * To change this template, choose Tools | Template Manager
 * and open the template in the editor.
 */

package geotrans.parameters;


import geotrans.enumerations.CoordinateTypes;


/**
 *
 * @author comstam
 */
public class CoordinateSystemParameters 
{
  protected int coordinateType = CoordinateTypes.GEODETIC;
  
  
  /** Creates a new instance of CoordinateSystemParameters */
  public CoordinateSystemParameters() 
  {
  }
  
  
  public CoordinateSystemParameters(int _coordinateType) 
  {
    coordinateType = _coordinateType;
  }
  
  
  public int getCoordinateType()
  {
    return coordinateType;
  }  
}
