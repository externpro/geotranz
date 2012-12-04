/*
 * UTMParameters.java
 *
 * Created on April 3, 2007, 3:54 PM
 *
 * To change this template, choose Tools | Template Manager
 * and open the template in the editor.
 */

package geotrans.parameters;


/**
 *
 * @author comstam
 */
public class UTMParameters extends CoordinateSystemParameters
{
  private long zone;
  private long override;
  
  
  /** Creates a new instance of UTMParameters */
  public UTMParameters(int coordinateType, long _zone, long _override) 
  {
    super(coordinateType); 
    
    zone = _zone;
    override = _override;
  }
  
  
  public long getZone()
  {
    return zone;
  }
  
  
  public long getOverride()
  {
    return override;
  }
}
