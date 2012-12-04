/*
 * MapProjection3Parameters.java
 *
 * Created on April 4, 2007, 9:16 AM
 *
 * To change this template, choose Tools | Template Manager
 * and open the template in the editor.
 */

package geotrans.parameters;


/**
 *
 * @author comstam
 */
public class MapProjection3Parameters extends CoordinateSystemParameters 
{
  private double centralMeridian;
  private double falseEasting;
  private double falseNorthing;
  
  
  /** Creates a new instance of MapProjection3Parameters */
  public MapProjection3Parameters(int coordinateType, double _centralMeridian, double _falseEasting, double _falseNorthing) 
  {
    super(coordinateType);
    
    centralMeridian = _centralMeridian;
    falseEasting = _falseEasting;
    falseNorthing = _falseNorthing;
  }
  
  
  public double getCentralMeridian()
  {
    return centralMeridian;
  }


  public double getFalseEasting()
  {
    return falseEasting;
  }


  public double getFalseNorthing()
  {
    return falseNorthing;
  }
}
