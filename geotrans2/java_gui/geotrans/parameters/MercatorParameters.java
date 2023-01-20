/*
 * MercatorParameters.java
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
public class MercatorParameters extends CoordinateSystemParameters
{
  private double centralMeridian;
  private double latitudeOfTrueScale;
  private double scaleFactor;
  private double falseEasting;
  private double falseNorthing;

  
  /** Creates a new instance of MercatorParameters */
  public MercatorParameters(int coordinateType, double _centralMeridian, double _latitudeOfTrueScale, double _scaleFactor, double _falseEasting, double _falseNorthing) 
  {
    super(coordinateType);
    
    centralMeridian = _centralMeridian;
    latitudeOfTrueScale = _latitudeOfTrueScale;
    scaleFactor = _scaleFactor;
    falseEasting = _falseEasting;
    falseNorthing = _falseNorthing;
  }
  
  
  public double getCentralMeridian()
  {
    return centralMeridian;
  }


  public double getLatitudeOfTrueScale()
  {
    return latitudeOfTrueScale;
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
