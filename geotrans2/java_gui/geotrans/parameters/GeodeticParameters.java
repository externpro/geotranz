/*
 * GeodeticParameters.java
 *
 * Created on April 3, 2007, 2:35 PM
 *
 * To change this template, choose Tools | Template Manager
 * and open the template in the editor.
 */

package geotrans.parameters;


/**
 *
 * @author comstam
 */
public class GeodeticParameters extends CoordinateSystemParameters
{
  private int heightType;
  
  
  /** Creates a new instance of GeodeticParameters */
  public GeodeticParameters(int coordinateType, int _heightType) 
  {
    super(coordinateType);
    
    heightType = _heightType;
  }
  
  
  public int getHeightType()
  {
    return heightType;
  }
}
