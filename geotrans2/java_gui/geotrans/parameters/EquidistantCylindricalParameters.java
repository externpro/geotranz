/*
 * EquidistantCylindricalParameters.java
 *
 * Created on April 6, 2007, 3:05 PM
 *
 * To change this template, choose Tools | Template Manager
 * and open the template in the editor.
 */

package geotrans.parameters;

/**
 *
 * @author comstam
 */
public class EquidistantCylindricalParameters extends CoordinateSystemParameters 
{
  private double centralMeridian;
  private double standardParallel;
  private double falseEasting;
  private double falseNorthing;
  
  
  /** Creates a new instance of EquidistantCylindricalParameters */
  public EquidistantCylindricalParameters(int coordinateType, double _centralMeridian, double _standardParallel, double _falseEasting, double _falseNorthing) 
  {
    super(coordinateType);
    
    centralMeridian = _centralMeridian;
    standardParallel = _standardParallel;
    falseEasting = _falseEasting;
    falseNorthing = _falseNorthing;
  }
  
  
  public double getCentralMeridian()
  {
    return centralMeridian;
  }


  public double getStandardParallel()
  {
    return standardParallel;
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
