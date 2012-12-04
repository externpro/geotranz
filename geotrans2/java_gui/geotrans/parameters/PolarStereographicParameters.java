/*
 * PolarStereographicParameters.java
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
public class PolarStereographicParameters extends CoordinateSystemParameters 
{
  private double longitudeDownFromPole;
  private double latitudeOfTrueScale;
  private double falseEasting;
  private double falseNorthing;
  
  
  /** Creates a new instance of PolarStereographicParameters */
  public PolarStereographicParameters(int coordinateType, double _longitudeDownFromPole, double _latitudeOfTrueScale, double _falseEasting, double _falseNorthing) 
  {
    super(coordinateType);
    
    longitudeDownFromPole = _longitudeDownFromPole;
    latitudeOfTrueScale = _latitudeOfTrueScale;
    falseEasting = _falseEasting;
    falseNorthing = _falseNorthing;
  }
  
  
  public double getLongitudeDownFromPole()
  {
    return longitudeDownFromPole;
  }


  public double getLatitudeOfTrueScale()
  {
    return latitudeOfTrueScale;
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
