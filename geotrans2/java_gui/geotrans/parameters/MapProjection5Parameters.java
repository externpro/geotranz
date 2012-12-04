/*
 * MapProjection5Parameters.java
 *
 * Created on April 4, 2007, 8:50 AM
 *
 * To change this template, choose Tools | Template Manager
 * and open the template in the editor.
 */

package geotrans.parameters;


/**
 *
 * @author comstam
 */
public class MapProjection5Parameters extends CoordinateSystemParameters
{
  private double centralMeridian;
  private double originLatitude;
  private double scaleFactor;
  private double falseEasting;
  private double falseNorthing;

  
  /** Creates a new instance of MapProjection5Parameters */
  public MapProjection5Parameters(int coordinateType, double _centralMeridian, double _originLatitude, double _scaleFactor, double _falseEasting, double _falseNorthing) 
  {
    super(coordinateType);
    
    centralMeridian = _centralMeridian;
    originLatitude = _originLatitude;
    scaleFactor = _scaleFactor;
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


  public double getScaleFactor()
  {
    return scaleFactor;
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
