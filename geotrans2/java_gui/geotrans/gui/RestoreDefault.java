/*
 * RestoreDefault.java
 *
 * Created on September 25, 2007, 11:04 AM
 *
 * To change this template, choose Tools | Template Manager
 * and open the template in the editor.
 */

package geotrans.gui;


import geotrans.parameters.*;
import geotrans.enumerations.CoordinateTypes;
import java.io.File;
import org.w3c.dom.Document;
import org.w3c.dom.*;
import javax.xml.parsers.DocumentBuilderFactory;
import javax.xml.parsers.DocumentBuilder;
import org.xml.sax.SAXException;
import org.xml.sax.SAXParseException; 


/**
 *
 * @author comstam
 */
public class RestoreDefault 
{
  private Geotrans parent;
  private java.io.File file;
  private MasterPanel upperMasterPanel;
  private MasterPanel lowerMasterPanel;
  private jOptions joptions;

  
  /** Creates a new instance of RestoreDefault */
  public RestoreDefault(Geotrans _parent, java.io.File _file, MasterPanel _upperMasterPanel, MasterPanel _lowerMasterPanel, jOptions _joptions) 
  {
    parent = _parent;
    file = _file;
    upperMasterPanel = _upperMasterPanel;
    lowerMasterPanel = _lowerMasterPanel;
    joptions = _joptions;
    
    readDefaults();
  }
  
  
  private void readDefaults()
  {
    try 
    {
      int defaultSourceDatum = 0;
      int defaultSourceProjection = 0;
      CoordinateSystemParameters defaultSourceParameters = new CoordinateSystemParameters();
      int defaultTargetDatum = 0;
      int defaultTargetProjection = 0;
      CoordinateSystemParameters defaultTargetParameters = new CoordinateSystemParameters();
      
      DocumentBuilderFactory docBuilderFactory = DocumentBuilderFactory.newInstance();
      DocumentBuilder docBuilder = docBuilderFactory.newDocumentBuilder();
      Document doc = docBuilder.parse(file);
      
      doc.getDocumentElement().normalize ();
      
      // Read format options
      readOptions(doc);      
      
      // Read source datum, projection and parameter information
      NodeList sourceDefaults = doc.getElementsByTagName("source");

      Node sourceNode = sourceDefaults.item(0);
      if(sourceNode.getNodeType() == Node.ELEMENT_NODE)
      {
          Element sourceElement = (Element)sourceNode;

          NodeList datumList = sourceElement.getElementsByTagName("datum");
          Element datumElement = (Element)datumList.item(0);
          
          NodeList datumIndexList = datumElement.getElementsByTagName("index");
          Node datumIndexTextNode = datumIndexList.item(0).getLastChild();
          defaultSourceDatum = Integer.parseInt(datumIndexTextNode.getNodeValue().trim());
          
          NodeList datumCodeList = datumElement.getElementsByTagName("code");
          Node datumCodeTextNode = datumCodeList.item(0).getLastChild();
          String defaultSourceDatumCode = datumCodeTextNode.getNodeValue().trim();

          NodeList projectionList = sourceElement.getElementsByTagName("projection");
          Element projectionElement = (Element)projectionList.item(0);
          
          NodeList projectionIndexList = projectionElement.getElementsByTagName("index");
          Node projectionIndexTextNode = projectionIndexList.item(0).getLastChild();
          defaultSourceProjection = Integer.parseInt(projectionIndexTextNode.getNodeValue().trim());
          
          NodeList projectionCodeList = projectionElement.getElementsByTagName("code");
          Node projectionCodeTextNode = projectionCodeList.item(0).getLastChild();
          String defaultSourceProjectionCode = projectionCodeTextNode.getNodeValue().trim();
          
          NodeList parametersList = sourceElement.getElementsByTagName("parameters");
          Element parametersElement = (Element)parametersList.item(0);
          
          defaultSourceParameters = readParameters(defaultSourceProjection, parametersElement);
      }
      
      upperMasterPanel.setDefaults(defaultSourceDatum, defaultSourceProjection, defaultSourceParameters);

      // Read target datum, projection and parameter information
      NodeList targetDefaults = doc.getElementsByTagName("target");

      Node targetNode = targetDefaults.item(0);
      if(targetNode.getNodeType() == Node.ELEMENT_NODE)
      {
          Element targetElement = (Element)targetNode;

          NodeList datumList = targetElement.getElementsByTagName("datum");
          Element datumElement = (Element)datumList.item(0);
          
          NodeList datumIndexList = datumElement.getElementsByTagName("index");
          Node datumIndexTextNode = datumIndexList.item(0).getLastChild();
          defaultTargetDatum = Integer.parseInt(datumIndexTextNode.getNodeValue().trim());
          
          NodeList datumCodeList = datumElement.getElementsByTagName("code");
          Node datumCodeTextNode = datumCodeList.item(0).getLastChild();
          String defaultTargetDatumCode = datumCodeTextNode.getNodeValue().trim();
          
          NodeList projectionList = targetElement.getElementsByTagName("projection");
          Element projectionElement = (Element)projectionList.item(0);
          
          NodeList projectionIndexList = projectionElement.getElementsByTagName("index");
          Node projectionIndexTextNode = projectionIndexList.item(0).getLastChild();
          defaultTargetProjection = Integer.parseInt(projectionIndexTextNode.getNodeValue().trim());
          
          NodeList projectionCodeList = projectionElement.getElementsByTagName("code");
          Node projectionCodeTextNode = projectionCodeList.item(0).getLastChild();
          String defaultTargetProjectionCode = projectionCodeTextNode.getNodeValue().trim();
          
          NodeList parametersList = targetElement.getElementsByTagName("parameters");
          Element parametersElement = (Element)parametersList.item(0);
          
          defaultTargetParameters = readParameters(defaultTargetProjection, parametersElement);
      }
      
      lowerMasterPanel.setDefaults(defaultTargetDatum, defaultTargetProjection, defaultTargetParameters);
    }
    catch (SAXParseException err) 
    {
        System.out.println ("** Parsing error" + ", line " 
             + err.getLineNumber () + ", uri " + err.getSystemId ());
        System.out.println(" " + err.getMessage ());

    }
    catch (SAXException e) 
    {
        Exception x = e.getException ();
        ((x == null) ? e : x).printStackTrace ();

    }
    catch (Throwable t)
    {
        t.printStackTrace ();
    }
  }
  
  
  private void readOptions(Document doc)
  {
    NodeList optionsDefaults = doc.getElementsByTagName("options");

    Node optionsNode = optionsDefaults.item(0);
    if(optionsNode.getNodeType() == Node.ELEMENT_NODE)
    {
        Element optionsElement = (Element)optionsNode;

        // Units
        NodeList unitsList = optionsElement.getElementsByTagName("units");
        Element unitsElement = (Element)unitsList.item(0);

        NodeList unitsIndexList = unitsElement.getElementsByTagName("index");
        Node unitsIndexTextNode = unitsIndexList.item(0).getLastChild();
        int defaultUnits = Integer.parseInt(unitsIndexTextNode.getNodeValue().trim());

        NodeList unitsValueList = unitsElement.getElementsByTagName("value");
        Node unitsValueTextNode = unitsValueList.item(0).getLastChild();
        String defaultUnitsValue = unitsValueTextNode.getNodeValue().trim();

        joptions.setUnits(defaultUnits);

        // Separator
        NodeList separatorList = optionsElement.getElementsByTagName("separator");
        Element separatorElement = (Element)separatorList.item(0);

        NodeList separatorIndexList = separatorElement.getElementsByTagName("index");
        Node separatorIndexTextNode = separatorIndexList.item(0).getLastChild();
        int defaultSeparator = Integer.parseInt(separatorIndexTextNode.getNodeValue().trim());

        NodeList separatorValueList = separatorElement.getElementsByTagName("value");
        Node separatorValueTextNode = separatorValueList.item(0).getLastChild();
        String defaultSeparatorValue = separatorValueTextNode.getNodeValue().trim();

        joptions.setSeparator(defaultSeparator);

        // Sign/hemisphere
        NodeList signHemisphereList = optionsElement.getElementsByTagName("signHemisphere");
        Element signHemisphereElement = (Element)signHemisphereList.item(0);

        NodeList signHemisphereIndexList = signHemisphereElement.getElementsByTagName("index");
        Node signHemisphereIndexTextNode = signHemisphereIndexList.item(0).getLastChild();
        int defaultSignHemisphere = Integer.parseInt(signHemisphereIndexTextNode.getNodeValue().trim());

        NodeList signHemisphereValueList = signHemisphereElement.getElementsByTagName("value");
        Node signHemisphereValueTextNode = signHemisphereValueList.item(0).getLastChild();
        String defaultSignHemisphereValue = signHemisphereValueTextNode.getNodeValue().trim();

        joptions.setSignHemi(defaultSignHemisphere);

        // Longitude range
        NodeList longitudeRangeList = optionsElement.getElementsByTagName("longitudeRange");
        Element longitudeRangeElement = (Element)longitudeRangeList.item(0);

        NodeList longitudeRangeIndexList = longitudeRangeElement.getElementsByTagName("index");
        Node longitudeRangeIndexTextNode = longitudeRangeIndexList.item(0).getLastChild();
        int defaultLongitudeRange = Integer.parseInt(longitudeRangeIndexTextNode.getNodeValue().trim());

        NodeList longitudeRangeValueList = longitudeRangeElement.getElementsByTagName("value");
        Node longitudeRangeValueTextNode = longitudeRangeValueList.item(0).getLastChild();
        String defaultLongitudeRangeValue = longitudeRangeValueTextNode.getNodeValue().trim();

        joptions.setRange(defaultLongitudeRange);

        // Precision
        NodeList precisionList = optionsElement.getElementsByTagName("precision");
        Element precisionElement = (Element)precisionList.item(0);

        NodeList precisionIndexList = precisionElement.getElementsByTagName("index");
        Node precisionIndexTextNode = precisionIndexList.item(0).getLastChild();
        int defaultPrecision = Integer.parseInt(precisionIndexTextNode.getNodeValue().trim());

        NodeList precisionValueList = precisionElement.getElementsByTagName("value");
        Node precisionValueTextNode = precisionValueList.item(0).getLastChild();
        String defaultPrecisionValue = precisionValueTextNode.getNodeValue().trim();

        joptions.setPrecision(defaultPrecision);

        // Leading zeros
        NodeList leadingZerosList = optionsElement.getElementsByTagName("leadingZeros");
        Element leadingZerosElement = (Element)leadingZerosList.item(0);

        NodeList leadingZerosValueList = leadingZerosElement.getElementsByTagName("value");
        Node leadingZerosValueTextNode = leadingZerosValueList.item(0).getLastChild();
        boolean defaultLeadingZerosValue = Boolean.valueOf(leadingZerosValueTextNode.getNodeValue().trim()).booleanValue();

        joptions.setLeadingZeros(defaultLeadingZerosValue);
    }
  }
  
  private CoordinateSystemParameters readParameters(int projectionType, Element parametersElement)
  {
    switch(projectionType)
    {
      case CoordinateTypes.ECKERT4:
      case CoordinateTypes.ECKERT6:
      case CoordinateTypes.MILLER:
      case CoordinateTypes.MOLLWEIDE:
      case CoordinateTypes.SINUSOIDAL:
      case CoordinateTypes.GRINTEN:
      {
        NodeList centralMeridianList = parametersElement.getElementsByTagName("centralMeridian");
        Node centralMeridianTextNode = centralMeridianList.item(0).getLastChild();
        double centralMeridian = Double.parseDouble(centralMeridianTextNode.getNodeValue().trim());
        
        NodeList falseEastingList = parametersElement.getElementsByTagName("falseEasting");
        Node falseEastingTextNode = falseEastingList.item(0).getLastChild();
        double falseEasting = Double.parseDouble(falseEastingTextNode.getNodeValue().trim());
        
        NodeList falseNorthingList = parametersElement.getElementsByTagName("falseNorthing");
        Node falseNorthingTextNode = falseNorthingList.item(0).getLastChild();
        double falseNorthing = Double.parseDouble(falseNorthingTextNode.getNodeValue().trim());
        
        return new MapProjection3Parameters(projectionType, centralMeridian, falseEasting, falseNorthing);
      }
      case CoordinateTypes.AZIMUTHAL:
      case CoordinateTypes.BONNE:
      case CoordinateTypes.CASSINI:
      case CoordinateTypes.CYLEQA:
      case CoordinateTypes.GNOMONIC:
      case CoordinateTypes.ORTHOGRAPHIC:
      case CoordinateTypes.POLYCONIC:
      case CoordinateTypes.STEREOGRAPHIC:
      {
        NodeList centralMeridianList = parametersElement.getElementsByTagName("centralMeridian");
        Node centralMeridianTextNode = centralMeridianList.item(0).getLastChild();
        double centralMeridian = Double.parseDouble(centralMeridianTextNode.getNodeValue().trim());
        
        NodeList originLatitudeList = parametersElement.getElementsByTagName("originLatitude");
        Node originLatitudeTextNode = originLatitudeList.item(0).getLastChild();
        double originLatitude = Double.parseDouble(originLatitudeTextNode.getNodeValue().trim());
        
        NodeList falseEastingList = parametersElement.getElementsByTagName("falseEasting");
        Node falseEastingTextNode = falseEastingList.item(0).getLastChild();
        double falseEasting = Double.parseDouble(falseEastingTextNode.getNodeValue().trim());
        
        NodeList falseNorthingList = parametersElement.getElementsByTagName("falseNorthing");
        Node falseNorthingTextNode = falseNorthingList.item(0).getLastChild();
        double falseNorthing = Double.parseDouble(falseNorthingTextNode.getNodeValue().trim());

        return new MapProjection4Parameters(projectionType, centralMeridian, originLatitude, falseEasting, falseNorthing);
      }
      case CoordinateTypes.EQDCYL:
      {
        NodeList centralMeridianList = parametersElement.getElementsByTagName("centralMeridian");
        Node centralMeridianTextNode = centralMeridianList.item(0).getLastChild();
        double centralMeridian = Double.parseDouble(centralMeridianTextNode.getNodeValue().trim());
        
        NodeList standardParallelList = parametersElement.getElementsByTagName("standardParallel");
        Node standardParallelTextNode = standardParallelList.item(0).getLastChild();
        double standardParallel = Double.parseDouble(standardParallelTextNode.getNodeValue().trim());
        
        NodeList falseEastingList = parametersElement.getElementsByTagName("falseEasting");
        Node falseEastingTextNode = falseEastingList.item(0).getLastChild();
        double falseEasting = Double.parseDouble(falseEastingTextNode.getNodeValue().trim());
        
        NodeList falseNorthingList = parametersElement.getElementsByTagName("falseNorthing");
        Node falseNorthingTextNode = falseNorthingList.item(0).getLastChild();
        double falseNorthing = Double.parseDouble(falseNorthingTextNode.getNodeValue().trim());

        return new EquidistantCylindricalParameters(projectionType, centralMeridian, standardParallel, falseEasting, falseNorthing);
      }
      case CoordinateTypes.LAMBERT_1:
      case CoordinateTypes.TRCYLEQA:
      case CoordinateTypes.TRANMERC:
      {
        NodeList centralMeridianList = parametersElement.getElementsByTagName("centralMeridian");
        Node centralMeridianTextNode = centralMeridianList.item(0).getLastChild();
        double centralMeridian = Double.parseDouble(centralMeridianTextNode.getNodeValue().trim());
        
        NodeList originLatitudeList = parametersElement.getElementsByTagName("originLatitude");
        Node originLatitudeTextNode = originLatitudeList.item(0).getLastChild();
        double originLatitude = Double.parseDouble(originLatitudeTextNode.getNodeValue().trim());
        
        NodeList scaleFactorList = parametersElement.getElementsByTagName("scaleFactor");
        Node scaleFactorTextNode = scaleFactorList.item(0).getLastChild();
        double scaleFactor = Double.parseDouble(scaleFactorTextNode.getNodeValue().trim());
        
        NodeList falseEastingList = parametersElement.getElementsByTagName("falseEasting");
        Node falseEastingTextNode = falseEastingList.item(0).getLastChild();
        double falseEasting = Double.parseDouble(falseEastingTextNode.getNodeValue().trim());
        
        NodeList falseNorthingList = parametersElement.getElementsByTagName("falseNorthing");
        Node falseNorthingTextNode = falseNorthingList.item(0).getLastChild();
        double falseNorthing = Double.parseDouble(falseNorthingTextNode.getNodeValue().trim());

        return new MapProjection5Parameters(projectionType, centralMeridian, originLatitude, scaleFactor, falseEasting, falseNorthing);
      }
      case CoordinateTypes.MERCATOR:
      {
        NodeList centralMeridianList = parametersElement.getElementsByTagName("centralMeridian");
        Node centralMeridianTextNode = centralMeridianList.item(0).getLastChild();
        double centralMeridian = Double.parseDouble(centralMeridianTextNode.getNodeValue().trim());
        
        NodeList latitudeOfTrueScaleList = parametersElement.getElementsByTagName("latitudeOfTrueScale");
        Node latitudeOfTrueScaleTextNode = latitudeOfTrueScaleList.item(0).getLastChild();
        double latitudeOfTrueScale = Double.parseDouble(latitudeOfTrueScaleTextNode.getNodeValue().trim());
        
        NodeList scaleFactorList = parametersElement.getElementsByTagName("scaleFactor");
        Node scaleFactorTextNode = scaleFactorList.item(0).getLastChild();
        double scaleFactor = Double.parseDouble(scaleFactorTextNode.getNodeValue().trim());
        
        NodeList falseEastingList = parametersElement.getElementsByTagName("falseEasting");
        Node falseEastingTextNode = falseEastingList.item(0).getLastChild();
        double falseEasting = Double.parseDouble(falseEastingTextNode.getNodeValue().trim());
        
        NodeList falseNorthingList = parametersElement.getElementsByTagName("falseNorthing");
        Node falseNorthingTextNode = falseNorthingList.item(0).getLastChild();
        double falseNorthing = Double.parseDouble(falseNorthingTextNode.getNodeValue().trim());

        return new MercatorParameters(projectionType, centralMeridian, latitudeOfTrueScale, scaleFactor, falseEasting, falseNorthing);        
      }
      case CoordinateTypes.ALBERS:
      case CoordinateTypes.LAMBERT_2:
      {
        NodeList centralMeridianList = parametersElement.getElementsByTagName("centralMeridian");
        Node centralMeridianTextNode = centralMeridianList.item(0).getLastChild();
        double centralMeridian = Double.parseDouble(centralMeridianTextNode.getNodeValue().trim());
        
        NodeList originLatitudeList = parametersElement.getElementsByTagName("originLatitude");
        Node originLatitudeTextNode = originLatitudeList.item(0).getLastChild();
        double originLatitude = Double.parseDouble(originLatitudeTextNode.getNodeValue().trim());
        
        NodeList standardParallel1List = parametersElement.getElementsByTagName("standardParallel1");
        Node standardParallel1TextNode = standardParallel1List.item(0).getLastChild();
        double standardParallel1 = Double.parseDouble(standardParallel1TextNode.getNodeValue().trim());
        
        NodeList standardParallel2List = parametersElement.getElementsByTagName("standardParallel2");
        Node standardParallel2TextNode = standardParallel2List.item(0).getLastChild();
        double standardParallel2 = Double.parseDouble(standardParallel2TextNode.getNodeValue().trim());
        
        NodeList falseEastingList = parametersElement.getElementsByTagName("falseEasting");
        Node falseEastingTextNode = falseEastingList.item(0).getLastChild();
        double falseEasting = Double.parseDouble(falseEastingTextNode.getNodeValue().trim());
        
        NodeList falseNorthingList = parametersElement.getElementsByTagName("falseNorthing");
        Node falseNorthingTextNode = falseNorthingList.item(0).getLastChild();
        double falseNorthing = Double.parseDouble(falseNorthingTextNode.getNodeValue().trim());

        return new MapProjection6Parameters(projectionType, centralMeridian, originLatitude, standardParallel1, standardParallel2, falseEasting, falseNorthing);
      }
      case CoordinateTypes.LOCCART:
      {
        NodeList originLongitudeList = parametersElement.getElementsByTagName("originLongitude");
        Node originLongitudeTextNode = originLongitudeList.item(0).getLastChild();
        double originLongitude = Double.parseDouble(originLongitudeTextNode.getNodeValue().trim());
        
        NodeList originLatitudeList = parametersElement.getElementsByTagName("originLatitude");
        Node originLatitudeTextNode = originLatitudeList.item(0).getLastChild();
        double originLatitude = Double.parseDouble(originLatitudeTextNode.getNodeValue().trim());
        
        NodeList originHeightList = parametersElement.getElementsByTagName("originHeight");
        Node originHeightTextNode = originHeightList.item(0).getLastChild();
        double originHeight = Double.parseDouble(originHeightTextNode.getNodeValue().trim());        
        
        NodeList orientationList = parametersElement.getElementsByTagName("orientation");
        Node orientationTextNode = orientationList.item(0).getLastChild();
        double orientation = Double.parseDouble(orientationTextNode.getNodeValue().trim());

        return new LocalCartesianParameters(projectionType, originLongitude, originLatitude, originHeight, orientation);
      }
      case CoordinateTypes.NEYS:
      {
        NodeList centralMeridianList = parametersElement.getElementsByTagName("centralMeridian");
        Node centralMeridianTextNode = centralMeridianList.item(0).getLastChild();
        double centralMeridian = Double.parseDouble(centralMeridianTextNode.getNodeValue().trim());
        
        NodeList originLatitudeList = parametersElement.getElementsByTagName("originLatitude");
        Node originLatitudeTextNode = originLatitudeList.item(0).getLastChild();
        double originLatitude = Double.parseDouble(originLatitudeTextNode.getNodeValue().trim());
        
        NodeList standardParallel1List = parametersElement.getElementsByTagName("standardParallel1");
        Node standardParallel1TextNode = standardParallel1List.item(0).getLastChild();
        double standardParallel1 = Double.parseDouble(standardParallel1TextNode.getNodeValue().trim());
        
        NodeList falseEastingList = parametersElement.getElementsByTagName("falseEasting");
        Node falseEastingTextNode = falseEastingList.item(0).getLastChild();
        double falseEasting = Double.parseDouble(falseEastingTextNode.getNodeValue().trim());
        
        NodeList falseNorthingList = parametersElement.getElementsByTagName("falseNorthing");
        Node falseNorthingTextNode = falseNorthingList.item(0).getLastChild();
        double falseNorthing = Double.parseDouble(falseNorthingTextNode.getNodeValue().trim());

        return new NeysParameters(projectionType, centralMeridian, originLatitude, standardParallel1, falseEasting, falseNorthing);        
      }
      case CoordinateTypes.OMERC:
      {
        NodeList originLatitudeList = parametersElement.getElementsByTagName("originLatitude");
        Node originLatitudeTextNode = originLatitudeList.item(0).getLastChild();
        double originLatitude = Double.parseDouble(originLatitudeTextNode.getNodeValue().trim());
        
        NodeList scaleFactorList = parametersElement.getElementsByTagName("scaleFactor");
        Node scaleFactorTextNode = scaleFactorList.item(0).getLastChild();
        double scaleFactor = Double.parseDouble(scaleFactorTextNode.getNodeValue().trim());
        
        NodeList longitude1List = parametersElement.getElementsByTagName("longitude1");
        Node longitude1TextNode = longitude1List.item(0).getLastChild();
        double longitude1 = Double.parseDouble(longitude1TextNode.getNodeValue().trim());
        
        NodeList latitude1List = parametersElement.getElementsByTagName("latitude1");
        Node latitude1TextNode = latitude1List.item(0).getLastChild();
        double latitude1 = Double.parseDouble(latitude1TextNode.getNodeValue().trim());
        
        NodeList longitude2List = parametersElement.getElementsByTagName("longitude2");
        Node longitude2TextNode = longitude2List.item(0).getLastChild();
        double longitude2 = Double.parseDouble(longitude2TextNode.getNodeValue().trim());
        
        NodeList latitude2List = parametersElement.getElementsByTagName("latitude2");
        Node latitude2TextNode = latitude2List.item(0).getLastChild();
        double latitude2 = Double.parseDouble(latitude2TextNode.getNodeValue().trim());
        
        NodeList falseEastingList = parametersElement.getElementsByTagName("falseEasting");
        Node falseEastingTextNode = falseEastingList.item(0).getLastChild();
        double falseEasting = Double.parseDouble(falseEastingTextNode.getNodeValue().trim());
        
        NodeList falseNorthingList = parametersElement.getElementsByTagName("falseNorthing");
        Node falseNorthingTextNode = falseNorthingList.item(0).getLastChild();
        double falseNorthing = Double.parseDouble(falseNorthingTextNode.getNodeValue().trim());

        return new ObliqueMercatorParameters(projectionType, originLatitude, longitude1, latitude1, longitude2, latitude2, falseEasting, falseNorthing, scaleFactor);        
      }
      case CoordinateTypes.POLARSTEREO:
      {
        NodeList longitudeDownFromPoleList = parametersElement.getElementsByTagName("longitudeDownFromPole");
        Node longitudeDownFromPoleTextNode = longitudeDownFromPoleList.item(0).getLastChild();
        double longitudeDownFromPole = Double.parseDouble(longitudeDownFromPoleTextNode.getNodeValue().trim());
        
        NodeList latitudeOfTrueScaleList = parametersElement.getElementsByTagName("latitudeOfTrueScale");
        Node latitudeOfTrueScaleTextNode = latitudeOfTrueScaleList.item(0).getLastChild();
        double latitudeOfTrueScale = Double.parseDouble(latitudeOfTrueScaleTextNode.getNodeValue().trim());
        
        NodeList falseEastingList = parametersElement.getElementsByTagName("falseEasting");
        Node falseEastingTextNode = falseEastingList.item(0).getLastChild();
        double falseEasting = Double.parseDouble(falseEastingTextNode.getNodeValue().trim());
        
        NodeList falseNorthingList = parametersElement.getElementsByTagName("falseNorthing");
        Node falseNorthingTextNode = falseNorthingList.item(0).getLastChild();
        double falseNorthing = Double.parseDouble(falseNorthingTextNode.getNodeValue().trim());

        return new PolarStereographicParameters(projectionType, longitudeDownFromPole, latitudeOfTrueScale, falseEasting, falseNorthing);        
      }
      case CoordinateTypes.GEODETIC:
      {
        NodeList heightTypeList = parametersElement.getElementsByTagName("heightType");
        Node heightTypeTextNode = heightTypeList.item(0).getLastChild();
        int heightType = Integer.parseInt(heightTypeTextNode.getNodeValue().trim());

        return new GeodeticParameters(projectionType, heightType);
      }
      case CoordinateTypes.UTM:
      {
        NodeList overrideList = parametersElement.getElementsByTagName("override");
        Node overrideTextNode = overrideList.item(0).getLastChild();
        int override = Integer.parseInt(overrideTextNode.getNodeValue().trim());

        NodeList zoneList = parametersElement.getElementsByTagName("zone");
        Node zoneTextNode = zoneList.item(0).getLastChild();
        int zone = Integer.parseInt(zoneTextNode.getNodeValue().trim());

        return new UTMParameters(projectionType, zone, override);
      }
      case CoordinateTypes.BNG:
      case CoordinateTypes.F16GRS:
      case CoordinateTypes.GARS:
      case CoordinateTypes.GEOCENTRIC:
      case CoordinateTypes.GEOREF:
      case CoordinateTypes.MGRS:
      case CoordinateTypes.USNG:
      case CoordinateTypes.NZMG:
      case CoordinateTypes.UPS:
        return new CoordinateSystemParameters(projectionType);
    }
    
    return null;
  }
}
