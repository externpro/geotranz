/*
 * SaveAsDefault.java
 *
 * Created on September 20, 2007, 9:05 AM
 *
 * To change this template, choose Tools | Template Manager
 * and open the template in the editor.
 */

package geotrans.gui;


import geotrans.enumerations.CoordinateTypes;


/**
 *
 * @author comstam
 */
public class SaveAsDefault 
{
  private Geotrans parent;
  private java.io.File file;
  private MasterPanel upperMasterPanel;
  private MasterPanel lowerMasterPanel;
  private java.io.FileWriter defaultFile;
  private int projectionType = 0;
  private jOptions joptions;
  
  
  /** Creates a new instance of SaveAsDefault */
  public SaveAsDefault(Geotrans _parent, java.io.File _file, MasterPanel _upperMasterPanel, MasterPanel _lowerMasterPanel, jOptions _joptions) 
  {
    parent = _parent;
    file = _file;
    upperMasterPanel = _upperMasterPanel;
    lowerMasterPanel = _lowerMasterPanel;
    joptions = _joptions;
    
    writeDefaults();
  }
  
  
  private void writeDefaults()
  {
    try
    {
      defaultFile = new java.io.FileWriter(file);

      String contents = "<?xml version=\"1.0\" encoding=\"ISO-8859-1\"?>\r\n";
      contents += "<defaults>\r\n";
      defaultFile.write(contents, 0, contents.length());
      writeOptions();
      contents = "  <source>\r\n";
      contents += "    <datum>\r\n";
      contents += "      <index>" + (upperMasterPanel.getDatumIndex() - 1) + "</index>\r\n";
      contents += "      <code>" + upperMasterPanel.getDatumCode() + "</code>\r\n";
      contents += "    </datum>\r\n";
      contents += "    <projection>\r\n";
      projectionType = upperMasterPanel.getProjectionType();
      contents += "      <index>" + projectionType + "</index>\r\n";
      contents += "      <code>" + upperMasterPanel.getProjectionCode() + "</code>\r\n";
      contents += "    </projection>\r\n";
      defaultFile.write(contents, 0, contents.length());
      writeParameters(upperMasterPanel); 
      contents = "  </source>\r\n";
      contents += "  <target>\r\n";
      contents += "    <datum>\r\n";
      contents += "      <index>" + (lowerMasterPanel.getDatumIndex() - 1) + "</index>\r\n";
      contents += "      <code>" + (lowerMasterPanel.getDatumCode()) + "</code>\r\n";
      contents += "    </datum>\r\n";
      contents += "    <projection>\r\n";
      projectionType = lowerMasterPanel.getProjectionType();
      contents += "      <index>" + projectionType + "</index>\r\n";
      contents += "      <code>" + lowerMasterPanel.getProjectionCode() + "</code>\r\n";
      contents += "    </projection>\r\n";
      defaultFile.write(contents, 0, contents.length());
      writeParameters(lowerMasterPanel); 
      contents = "  </target>\r\n";
      contents += "</defaults>\r\n";
      defaultFile.write(contents, 0, contents.length());
      defaultFile.flush();
      defaultFile.close();
      
      javax.swing.JOptionPane.showMessageDialog(parent, "Defaults saved: " + file, "Save", javax.swing.JOptionPane.INFORMATION_MESSAGE);
    }
    catch(java.io.IOException ioex)
    {
      javax.swing.JOptionPane.showMessageDialog(parent, "Error Saving File: " + file, "Error", javax.swing.JOptionPane.ERROR_MESSAGE);
    }    
  }  
  
  
  private void writeParameters(MasterPanel masterPanel)
  {
   try
    {
      String contents = "    <parameters>\r\n";
      
      switch(projectionType)
      {
        case CoordinateTypes.ECKERT4:
        case CoordinateTypes.ECKERT6:
        case CoordinateTypes.MILLER:
        case CoordinateTypes.MOLLWEIDE:
        case CoordinateTypes.SINUSOIDAL:
        case CoordinateTypes.GRINTEN:
          contents += "      <centralMeridian>" + masterPanel.get3ParamCentralMeridian() + "</centralMeridian>\r\n";
          contents += "      <falseEasting>" + masterPanel.getFalseEasting() + "</falseEasting>\r\n";
          contents += "      <falseNorthing>" + masterPanel.getFalseNorthing() + "</falseNorthing>\r\n";
          break;
        case CoordinateTypes.AZIMUTHAL:
        case CoordinateTypes.BONNE:
        case CoordinateTypes.CASSINI:
        case CoordinateTypes.CYLEQA:
        case CoordinateTypes.GNOMONIC:
        case CoordinateTypes.ORTHOGRAPHIC:
        case CoordinateTypes.POLYCONIC:
        case CoordinateTypes.STEREOGRAPHIC:
          contents += "      <centralMeridian>" + masterPanel.get4ParamCentralMeridian() + "</centralMeridian>\r\n";
          contents += "      <originLatitude>" + masterPanel.get4ParamOriginLatitude() + "</originLatitude>\r\n";
          contents += "      <falseEasting>" + masterPanel.getFalseEasting() + "</falseEasting>\r\n";
          contents += "      <falseNorthing>" + masterPanel.getFalseNorthing() + "</falseNorthing>\r\n";
          break;
        case CoordinateTypes.EQDCYL:
          contents += "      <centralMeridian>" + masterPanel.get4ParamCentralMeridian() + "</centralMeridian>\r\n";
          contents += "      <standardParallel>" + masterPanel.get4ParamOriginLatitude() + "</standardParallel>\r\n";
          contents += "      <falseEasting>" + masterPanel.getFalseEasting() + "</falseEasting>\r\n";
          contents += "      <falseNorthing>" + masterPanel.getFalseNorthing() + "</falseNorthing>\r\n";
          break;
        case CoordinateTypes.LAMBERT_1:
        case CoordinateTypes.TRCYLEQA:
        case CoordinateTypes.TRANMERC:
          contents += "      <centralMeridian>" + masterPanel.get5ParamCentralMeridian() + "</centralMeridian>\r\n";
          contents += "      <originLatitude>" + masterPanel.get5ParamOriginLatitude() + "</originLatitude>\r\n";
          contents += "      <scaleFactor>" + masterPanel.get5ParamScaleFactor() + "</scaleFactor>\r\n";
          contents += "      <falseEasting>" + masterPanel.getFalseEasting() + "</falseEasting>\r\n";
          contents += "      <falseNorthing>" + masterPanel.getFalseNorthing() + "</falseNorthing>\r\n";
          break;
        case CoordinateTypes.MERCATOR:
          contents += "      <centralMeridian>" + masterPanel.get5ParamCentralMeridian() + "</centralMeridian>\r\n";
          contents += "      <latitudeOfTrueScale>" + masterPanel.get5ParamOriginLatitude() + "</latitudeOfTrueScale>\r\n";
          contents += "      <scaleFactor>" + masterPanel.get5ParamScaleFactor() + "</scaleFactor>\r\n";
          contents += "      <falseEasting>" + masterPanel.getFalseEasting() + "</falseEasting>\r\n";
          contents += "      <falseNorthing>" + masterPanel.getFalseNorthing() + "</falseNorthing>\r\n";
          break;
        case CoordinateTypes.ALBERS:
        case CoordinateTypes.LAMBERT_2:
          contents += "      <centralMeridian>" + masterPanel.get6ParamCentralMeridian() + "</centralMeridian>\r\n";
          contents += "      <originLatitude>" + masterPanel.get6ParamOriginLatitude() + "</originLatitude>\r\n";
          contents += "      <standardParallel1>" + masterPanel.get6ParamStandardParallel1() + "</standardParallel1>\r\n";
          contents += "      <standardParallel2>" + masterPanel.get6ParamStandardParallel2() + "</standardParallel2>\r\n";
          contents += "      <falseEasting>" + masterPanel.getFalseEasting() + "</falseEasting>\r\n";
          contents += "      <falseNorthing>" + masterPanel.getFalseNorthing() + "</falseNorthing>\r\n";
          break;
        case CoordinateTypes.GEODETIC:
          contents += "      <heightType>" + masterPanel.getGeodeticHeight() + "</heightType>\r\n";
          break;
        case CoordinateTypes.LOCCART:
          contents += "      <originLongitude>" + masterPanel.getOriginLongitude() + "</originLongitude>\r\n";
          contents += "      <originLatitude>" + masterPanel.getOriginLatitude() + "</originLatitude>\r\n";
          contents += "      <originHeight>" + masterPanel.getOriginHeight() + "</originHeight>\r\n";
          contents += "      <orientation>" + masterPanel.getOrientation() + "</orientation>\r\n";
          break;
        case CoordinateTypes.NEYS:
          contents += "      <centralMeridian>" + masterPanel.getNeysCentralMeridian() + "</centralMeridian>\r\n";
          contents += "      <originLatitude>" + masterPanel.getNeysOriginLatitude() + "</originLatitude>\r\n";
          contents += "      <standardParallel1>" + masterPanel.getNeysStandardParallel1() + "</standardParallel1>\r\n";
          contents += "      <falseEasting>" + masterPanel.getFalseEasting() + "</falseEasting>\r\n";
          contents += "      <falseNorthing>" + masterPanel.getFalseNorthing() + "</falseNorthing>\r\n";
          break;
        case CoordinateTypes.OMERC:
          contents += "      <originLatitude>" + masterPanel.getOmercOriginLatitude() + "</originLatitude>\r\n";
          contents += "      <scaleFactor>" + masterPanel.getOmercScaleFactor() + "</scaleFactor>\r\n";
          contents += "      <longitude1>" + masterPanel.getOmercLongitude1() + "</longitude1>\r\n";
          contents += "      <latitude1>" + masterPanel.getOmercLatitude1() + "</latitude1>\r\n";
          contents += "      <longitude2>" + masterPanel.getOmercLongitude2() + "</longitude2>\r\n";
          contents += "      <latitude2>" + masterPanel.getOmercLatitude2() + "</latitude2>\r\n";
          contents += "      <falseEasting>" + masterPanel.getOmercFalseEasting() + "</falseEasting>\r\n";
          contents += "      <falseNorthing>" + masterPanel.getOmercFalseNorthing() + "</falseNorthing>\r\n";
          break;
        case CoordinateTypes.POLARSTEREO:
          contents += "      <longitudeDownFromPole>" + masterPanel.get4ParamCentralMeridian() + "</longitudeDownFromPole>\r\n";
          contents += "      <latitudeOfTrueScale>" + masterPanel.get4ParamOriginLatitude() + "</latitudeOfTrueScale>\r\n";
          contents += "      <falseEasting>" + masterPanel.getFalseEasting() + "</falseEasting>\r\n";
          contents += "      <falseNorthing>" + masterPanel.getFalseNorthing() + "</falseNorthing>\r\n";
          break;
        case CoordinateTypes.UTM:
          contents += "      <override>" + masterPanel.getOverride() + "</override>\r\n";
          contents += "      <zone>" + masterPanel.getZone() + "</zone>\r\n";
          break;
         
      }
      contents += "    </parameters>\r\n";
      defaultFile.write(contents, 0, contents.length());
    }
    catch(java.io.IOException ioex)
    {
      javax.swing.JOptionPane.showMessageDialog(parent, "Error Saving File: " + file, "Error", javax.swing.JOptionPane.ERROR_MESSAGE);
    }    
  }
  
  
  void writeOptions()
  {
    try
    {
      String contents = "  <options>\r\n";
      
      contents += "    <units>\r\n";
      contents += "      <index>" + joptions.getUnits() + "</index>\r\n";
      contents += "      <value>" + joptions.getUnitsString() + "</value>\r\n";
      contents += "    </units>\r\n";
      
      contents += "    <separator>\r\n";
      contents += "      <index>" + joptions.getSeparatorIndex() + "</index>\r\n";
      contents += "      <value>" + joptions.getSeparator() + "</value>\r\n";
      contents += "    </separator>\r\n";
      
      contents += "    <signHemisphere>\r\n";
    contents += "      <index>" + joptions.getSignHemi() + "</index>\r\n";
      contents += "      <value>" + joptions.getSignHemiString() + "</value>\r\n";
      contents += "    </signHemisphere>\r\n";
      
      contents += "    <longitudeRange>\r\n";
      contents += "      <index>" + joptions.getRange() + "</index>\r\n";
      contents += "      <value>" + joptions.getRangeString() + "</value>\r\n";
      contents += "    </longitudeRange>\r\n";
      
      contents += "    <precision>\r\n";
      contents += "      <index>" + joptions.getPrecision() + "</index>\r\n";
      contents += "      <value>" + joptions.getPrecisionString() + "</value>\r\n";
      contents += "    </precision>\r\n";
      
      contents += "    <leadingZeros>\r\n";
      contents += "      <value>" + joptions.getLeadingZeros() + "</value>\r\n";
      contents += "    </leadingZeros>\r\n";
      
      contents += "  </options>\r\n";   
      defaultFile.write(contents, 0, contents.length());
    }
    catch(java.io.IOException ioex)
    {
      javax.swing.JOptionPane.showMessageDialog(parent, "Error Saving File: " + file, "Error", javax.swing.JOptionPane.ERROR_MESSAGE);
    }    
  }
}
