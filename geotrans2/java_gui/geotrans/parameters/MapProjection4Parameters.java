/*
 * MapProjection4Parameters.java
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
public class MapProjection4Parameters extends CoordinateSystemParameters 
{
  private double centralMeridian;
  private double originLatitude;
  private double falseEasting;
  private double falseNorthing;
  
  
  /** Creates a new instance of MapProjection4Parameters */
  public MapProjection4Parameters(int coordinateType, double _centralMeridian, double _originLatitude, double _falseEasting, double _falseNorthing) 
  {
    super(coordinateType);
    
    centralMeridian = _centralMeridian;
    originLatitude = _originLatitude;
    falseEasting = _falseEasting;
    falseNorthing = _falseNorthing;
  }
  
  
  public double getCentralMeridian()
  {
    return centralMeridian;
  }


  public double getOriginLatitude()
  {
    return originLatitude;
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
