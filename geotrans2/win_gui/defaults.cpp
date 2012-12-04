#include <string.h>
#include <stdlib.h>
#include "defaults.h"
#include "resource.h"
#include "mastervw.h"
#include "mainfrm.h"


Defaults::Defaults( char* _data_dir_path_name ):
  data_dir_path_name( 0 ),
  default_file( 0 )
{
  data_dir_path_name = new char[strlen( _data_dir_path_name ) + 1];
  strcpy( data_dir_path_name, _data_dir_path_name );
}


Defaults::~Defaults()
{
  delete [] data_dir_path_name;
  data_dir_path_name = 0;
}


// Save the current parameters as defaults
void Defaults::saveAsDefault( CMasterView* upper_view, CMasterView* lower_view, CMainFrame* mainFrame )
{
  /*  Open the file for writing */               

  if( ( default_file = fopen( data_dir_path_name, "w+t" ) ) != NULL )
  {
    char* xml_tag = "<?xml version=\"1.0\" encoding=\"ISO-8859-1\"?>\n";
    char* root_open = "<defaults>\n";
    char* root_close = "</defaults>\n";
    char* source_open = "  <source>\n";
    char* source_close = "  </source>\n";
    char* target_open = "  <target>\n";
    char* target_close = "  </target>\n";
    char* datum_open = "    <datum>\n";
    char* datum_close = "    </datum>\n";
    char* projection_open = "    <projection>\n";
    char* projection_close = "    </projection>\n";

    fwrite( xml_tag, sizeof( char ), strlen( xml_tag ), default_file );
    fwrite( root_open, sizeof( char ), strlen( root_open ), default_file );

     // Options
    writeOptions( mainFrame );

    fwrite( source_open, sizeof( char ), strlen( source_open ), default_file );

    // Source datum
    fwrite( datum_open, sizeof( char ), strlen( datum_open ), default_file );
    fprintf( default_file, "%s%d%s\n", "      <index>", upper_view->datum_index - 1, "</index>" );
    char code[10];
    upper_view->getDatumCode( code );
    fprintf( default_file, "%s%s%s\n", "      <code>", code, "</code>" );
    fwrite( datum_close, sizeof( char ), strlen( datum_close ), default_file );

    // Source projection
    fwrite( projection_open, sizeof( char ), strlen( projection_open ), default_file );
    int projectionType = upper_view->type;
    fprintf( default_file, "%s%d%s\n", "      <index>", projectionType, "</index>" );
    code[0] = '\0';
    upper_view->getProjectionCode( code );
    fprintf( default_file, "%s%s%s\n", "      <code>", code, "</code>" );
    fwrite( projection_close, sizeof( char ), strlen( projection_close ), default_file );
   /////////// fprintf( default_file, "%s%d%s\n", "    <projection>", projectionType, "</projection>" );

    writeParameters( upper_view, projectionType );

    fwrite( source_close, sizeof( char ), strlen( source_close ), default_file );
    fwrite( target_open, sizeof( char ), strlen( target_open ), default_file );

    // Target datum
    fwrite( datum_open, sizeof( char ), strlen( datum_open ), default_file );
    fprintf( default_file, "%s%d%s\n", "      <index>", lower_view->datum_index - 1, "</index>" );
    code[0] = '\0';
    lower_view->getDatumCode( code );
    fprintf( default_file, "%s%s%s\n", "      <code>", code, "</code>" );
    fwrite( datum_close, sizeof( char ), strlen( datum_close ), default_file );
///    fprintf( default_file, "%s%d%s\n", "    <datum>", lower_view->datum_index - 1, "</datum>" );


    // Target projection
    fwrite( projection_open, sizeof( char ), strlen( projection_open ), default_file );
    projectionType = lower_view->type;
    fprintf( default_file, "%s%d%s\n", "      <index>", projectionType, "</index>" );
    code[0] = '\0';
    lower_view->getProjectionCode( code );
    fprintf( default_file, "%s%s%s\n", "      <code>", code, "</code>" );
    fwrite( projection_close, sizeof( char ), strlen( projection_close ), default_file );
    /////////fprintf( default_file, "%s%d%s\n", "    <projection>", projectionType, "</projection>" );


    writeParameters( lower_view, projectionType );

    fwrite( target_close, sizeof( char ), strlen( target_close ), default_file );


    fwrite( root_close, sizeof( char ), strlen( root_close ), default_file );

    fclose( default_file );

    AfxMessageBox("Defaults saved!",MB_OK | MB_ICONEXCLAMATION);
  }
  else
    AfxMessageBox("Error saving defaults!",MB_OK | MB_ICONEXCLAMATION);
}


// Write the current projection parameters to the default file
void Defaults::writeParameters( CMasterView* masterView, int projectionType )
{
  fprintf(default_file, "%s\n", "    <parameters>");

  switch( projectionType )
  {
    case Eckert4:
    case Eckert6:
    case Miller_Cylindrical:
    case Mollweide:
    case Sinusoidal:
    case Van_der_Grinten:
      fprintf( default_file, "%s%f%s\n", "    <centralMeridian>", masterView->get3ParamCentralMeridian(), "</centralMeridian>" );
      fprintf( default_file, "%s%f%s\n", "    <falseEasting>", masterView->getFalseEasting(), "</falseEasting>" );
      fprintf( default_file, "%s%f%s\n", "    <falseNorthing>", masterView->getFalseNorthing(), "</falseNorthing>" );
      break;
    case Azimuthal_Equidistant:
    case Bonne:
    case Cassini:
    case Cylindrical_Equal_Area:
    case Gnomonic:
    case Orthographic:
    case Polyconic:
    case Stereographic:
      fprintf( default_file, "%s%f%s\n", "    <centralMeridian>", masterView->get4ParamCentralMeridian(), "</centralMeridian>" );
      fprintf( default_file, "%s%f%s\n", "    <originLatitude>", masterView->get4ParamOriginLatitude(), "</originLatitude>" );
      fprintf( default_file, "%s%f%s\n", "    <falseEasting>", masterView->getFalseEasting(), "</falseEasting>" );
      fprintf( default_file, "%s%f%s\n", "    <falseNorthing>", masterView->getFalseNorthing(), "</falseNorthing>" );
      break;
    case Equidistant_Cylindrical:
      fprintf( default_file, "%s%f%s\n", "    <centralMeridian>", masterView->get4ParamCentralMeridian(), "</centralMeridian>" );
      fprintf( default_file, "%s%f%s\n", "    <standardParallel>", masterView->get4ParamOriginLatitude(), "</standardParallel>" );
      fprintf( default_file, "%s%f%s\n", "    <falseEasting>", masterView->getFalseEasting(), "</falseEasting>" );
      fprintf( default_file, "%s%f%s\n", "    <falseNorthing>", masterView->getFalseNorthing(), "</falseNorthing>" );
      break;
    case Lambert_Conformal_Conic_1:
    case Transverse_Cylindrical_Equal_Area:
    case Transverse_Mercator:
      fprintf( default_file, "%s%f%s\n", "    <centralMeridian>", masterView->get5ParamCentralMeridian(), "</centralMeridian>" );
      fprintf( default_file, "%s%f%s\n", "    <originLatitude>", masterView->get5ParamOriginLatitude(), "</originLatitude>" );
      fprintf( default_file, "%s%f%s\n", "    <scaleFactor>", masterView->get5ParamScaleFactor(), "</scaleFactor>" );
      fprintf( default_file, "%s%f%s\n", "    <falseEasting>", masterView->getFalseEasting(), "</falseEasting>" );
      fprintf( default_file, "%s%f%s\n", "    <falseNorthing>", masterView->getFalseNorthing(), "</falseNorthing>" );
      break;
    case Mercator:
      fprintf( default_file, "%s%f%s\n", "    <centralMeridian>", masterView->get5ParamCentralMeridian(), "</centralMeridian>" );
      fprintf( default_file, "%s%f%s\n", "    <latitudeOfTrueScale>", masterView->get5ParamOriginLatitude(), "</latitudeOfTrueScale>" );
      fprintf( default_file, "%s%f%s\n", "    <scaleFactor>", masterView->get5ParamScaleFactor(), "</scaleFactor>" );
      fprintf( default_file, "%s%f%s\n", "    <falseEasting>", masterView->getFalseEasting(), "</falseEasting>" );
      fprintf( default_file, "%s%f%s\n", "    <falseNorthing>", masterView->getFalseNorthing(), "</falseNorthing>" );
      break;
    case Albers_Equal_Area_Conic:
    case Lambert_Conformal_Conic_2:
      fprintf( default_file, "%s%f%s\n", "    <centralMeridian>", masterView->get6ParamCentralMeridian(), "</centralMeridian>" );
      fprintf( default_file, "%s%f%s\n", "    <originLatitude>", masterView->get6ParamOriginLatitude(), "</originLatitude>" );
      fprintf( default_file, "%s%f%s\n", "    <standardParallel1>", masterView->get6ParamStandardParallel1(), "</standardParallel1>" );
      fprintf( default_file, "%s%f%s\n", "    <standardParallel2>", masterView->get6ParamStandardParallel2(), "</standardParallel2>" );
      fprintf( default_file, "%s%f%s\n", "    <falseEasting>", masterView->getFalseEasting(), "</falseEasting>" );
      fprintf( default_file, "%s%f%s\n", "    <falseNorthing>", masterView->getFalseNorthing(), "</falseNorthing>" );
      break;
    case Geodetic:
      fprintf( default_file, "%s%d%s\n", "    <heightType>", masterView->getGeodeticHeight(), "</heightType>" );
      break;
    case Local_Cartesian:
      fprintf( default_file, "%s%f%s\n", "    <originLongitude>", masterView->getOriginLongitude(), "</originLongitude>" );
      fprintf( default_file, "%s%f%s\n", "    <originLatitude>", masterView->getOriginLatitude(), "</originLatitude>" );
      fprintf( default_file, "%s%f%s\n", "    <originHeight>", masterView->getOriginHeight(), "</originHeight>" );
      fprintf( default_file, "%s%f%s\n", "    <orientation>", masterView->getOrientation(), "</orientation>" );
      break;
    case Neys:
      fprintf( default_file, "%s%f%s\n", "    <centralMeridian>", masterView->get6ParamCentralMeridian(), "</centralMeridian>" );
      fprintf( default_file, "%s%f%s\n", "    <originLatitude>", masterView->get6ParamOriginLatitude(), "</originLatitude>" );
      fprintf( default_file, "%s%f%s\n", "    <standardParallel1>", masterView->getNeysStandardParallel1(), "</standardParallel1>" );
      fprintf( default_file, "%s%f%s\n", "    <falseEasting>", masterView->getFalseEasting(), "</falseEasting>" );
      fprintf( default_file, "%s%f%s\n", "    <falseNorthing>", masterView->getFalseNorthing(), "</falseNorthing>" );
      break;
    case Oblique_Mercator:
      fprintf( default_file, "%s%f%s\n", "    <originLatitude>", masterView->getOmercOriginLatitude(), "</originLatitude>" );
      fprintf( default_file, "%s%f%s\n", "    <scaleFactor>", masterView->getOmercScaleFactor(), "</scaleFactor>" );
      fprintf( default_file, "%s%f%s\n", "    <longitude1>", masterView->getOmercLongitude1(), "</longitude1>" );
      fprintf( default_file, "%s%f%s\n", "    <latitude1>", masterView->getOmercLatitude1(), "</latitude1>" );
      fprintf( default_file, "%s%f%s\n", "    <longitude2>", masterView->getOmercLongitude2(), "</longitude2>" );
      fprintf( default_file, "%s%f%s\n", "    <latitude2>", masterView->getOmercLatitude2(), "</latitude2>" );
      fprintf( default_file, "%s%f%s\n", "    <falseEasting>", masterView->getOmercFalseEasting(), "</falseEasting>" );
      fprintf( default_file, "%s%f%s\n", "    <falseNorthing>", masterView->getOmercFalseNorthing(), "</falseNorthing>" );
      break;
    case Polar_Stereo:
      fprintf( default_file, "%s%f%s\n", "    <longitudeDownFromPole>", masterView->get4ParamCentralMeridian(), "</longitudeDownFromPole>" );
      fprintf( default_file, "%s%f%s\n", "    <latitudeOfTrueScale>", masterView->get4ParamOriginLatitude(), "</latitudeOfTrueScale>" );
      fprintf( default_file, "%s%f%s\n", "    <falseEasting>", masterView->getFalseEasting(), "</falseEasting>" );
      fprintf( default_file, "%s%f%s\n", "    <falseNorthing>", masterView->getFalseNorthing(), "</falseNorthing>" );
      break;
    case UTM:
      fprintf( default_file, "%s%d%s\n", "    <override>", masterView->getOverride(), "</override>" );
      fprintf( default_file, "%s%d%s\n", "    <zone>", masterView->getZone(), "</zone>" );
      break;
  }

  fprintf(default_file, "%s\n", "    </parameters>");
}


// Write the current formatting options to the default file
void Defaults::writeOptions( CMainFrame* mainFrame )
{
  fprintf(default_file, "%s\n", "    <options>");
  fprintf(default_file, "%s\n", "      <units>");
  fprintf( default_file, "%s%d%s\n", "        <index>", mainFrame->getUnits(), "</index>" );
  fprintf( default_file, "%s%s%s\n", "        <value>", mainFrame->getUnitsString(), "</value>" );
  fprintf(default_file, "%s\n", "      </units>");

  fprintf(default_file, "%s\n", "      <separator>");
  fprintf( default_file, "%s%d%s\n", "        <index>", mainFrame->getSeparatorIndex(), "</index>" );
  fprintf( default_file, "%s%c%s\n", "        <value>", mainFrame->getSeparator(), "</value>" );
  fprintf(default_file, "%s\n", "      </separator>");

  fprintf(default_file, "%s\n", "      <signHemisphere>");
  fprintf( default_file, "%s%d%s\n", "        <index>", mainFrame->getSignHemi(), "</index>" );
  fprintf( default_file, "%s%s%s\n", "        <value>", mainFrame->getSignHemiString(), "</value>" );
  fprintf(default_file, "%s\n", "      </signHemisphere>");

  fprintf(default_file, "%s\n", "      <longitudeRange>");
  fprintf( default_file, "%s%d%s\n", "        <index>", mainFrame->getRange(), "</index>" );
  fprintf( default_file, "%s%s%s\n", "        <value>", mainFrame->getRangeString(), "</value>" );
  fprintf(default_file, "%s\n", "      </longitudeRange>");

  fprintf(default_file, "%s\n", "      <precision>");
  fprintf( default_file, "%s%d%s\n", "        <index>", mainFrame->getPrecision(), "</index>" );
  fprintf( default_file, "%s%s%s\n", "        <value>", mainFrame->getPrecisionString(), "</value>" );
  fprintf(default_file, "%s\n", "      </precision>");

  fprintf(default_file, "%s\n", "      <leadingZeros>");
  fprintf( default_file, "%s%s%s\n", "        <value>", mainFrame->getLeadingZeros(), "</value>" );
  fprintf(default_file, "%s\n", "      </leadingZeros>");

  fprintf(default_file, "%s\n", "    </options>");
}


// Initialize the gui with the parameter values in the default file
void Defaults::restoreDefault( CMasterView* upper_view, CMasterView* lower_view, CMainFrame* mainFrame )
{
  /*  Open the File READONLY */   
  
  if( ( default_file = fopen( data_dir_path_name, "r+t" ) ) != NULL )
  {
    char xml_tag[100];
    fscanf( default_file, "%99[^\n]", xml_tag );
    fgetc( default_file );

    char root_open[25];
    fscanf( default_file, "%24[^\n]", root_open );
    fgetc( default_file );

    // Format options info
    readOptions( mainFrame );

    char source_open[25];
    fscanf( default_file, "%24[^\n]", source_open );
    fgetc( default_file );


    // Source datum info
    char source_datum_open[25];
    fscanf( default_file, "%24[^\n]", source_datum_open );
    fgetc( default_file );

    char source_datum[25];
    getNodeValue( source_datum );

    char source_datum_code[25];
    getNodeValue( source_datum_code );

    char source_datum_close[25];
    fscanf( default_file, "%24[^\n]", source_datum_close );
    fgetc( default_file );


    // Source projection info
    char source_projection_open[25];
    fscanf( default_file, "%24[^\n]", source_projection_open );
    fgetc( default_file );

    char source_projection[25];
    getNodeValue( source_projection );

    char source_projection_code[25];
    getNodeValue( source_projection_code );

    char source_projection_close[25];
    fscanf( default_file, "%24[^\n]", source_projection_close );
    fgetc( default_file );

    upper_view->setDatum( atoi( source_datum ) );
    upper_view->setProjection( atoi( source_projection ) );
    readParameters( upper_view, atoi( source_projection ) );

    char source_close[25];
    fscanf( default_file, "%24[^\n]", source_close );
    fgetc( default_file );

    char target_open[25];
    fscanf( default_file, "%24[^\n]", target_open );
    fgetc( default_file );


    // Target datum info
    char target_datum_open[25];
    fscanf( default_file, "%24[^\n]", target_datum_open );
    fgetc( default_file );

    char target_datum[25];
    getNodeValue( target_datum );

    char target_datum_code[25];
    getNodeValue( target_datum_code );

    char target_datum_close[25];
    fscanf( default_file, "%24[^\n]", target_datum_close );
    fgetc( default_file );


    // Target projection info
    char target_projection_open[25];
    fscanf( default_file, "%24[^\n]", target_projection_open );
    fgetc( default_file );

    char target_projection[25];
    getNodeValue( target_projection );

    char target_projection_code[25];
    getNodeValue( target_projection_code );

    char target_projection_close[25];
    fscanf( default_file, "%24[^\n]", target_projection_close );
    fgetc( default_file );

    lower_view->setDatum( atoi( target_datum ) );
    lower_view->setProjection( atoi( target_projection ) );
    readParameters( lower_view, atoi( target_projection ) );

    char target_close[25];
    fscanf( default_file, "%24[^\n]", target_close );
    fgetc( default_file );

 ////   mainFrame->OnOptionsPrecision100000m();
    fclose( default_file );

  }
  else
    AfxMessageBox("Error restoring defaults!",MB_OK | MB_ICONEXCLAMATION);
}


// Read format options in the default file
void Defaults::readOptions( CMainFrame* mainFrame )
{
  char node_value[25];

  char options_open[25];
  fscanf( default_file, "%24[^\n]", options_open );
  fgetc( default_file );


  // Units
  char units_open[25];
  fscanf( default_file, "%24[^\n]", units_open );
  fgetc( default_file );

  getNodeValue( node_value );
  mainFrame->setUnits( atoi( node_value ) );
  getNodeValue( node_value );

  char units_close[25];
  fscanf( default_file, "%24[^\n]", units_close );
  fgetc( default_file );


  // Separator
  char separator_open[25];
  fscanf( default_file, "%24[^\n]", separator_open );
  fgetc( default_file );

  getNodeValue( node_value );
  mainFrame->setSeparator( atoi( node_value ) );
  getNodeValue( node_value );

  char separator_close[25];
  fscanf( default_file, "%24[^\n]", separator_close );
  fgetc( default_file );


  // Sign/hemisphere
  char sign_hemisphere_open[25];
  fscanf( default_file, "%24[^\n]", sign_hemisphere_open );
  fgetc( default_file );

  getNodeValue( node_value );
  mainFrame->setSignHemi( atoi( node_value ) );
  getNodeValue( node_value );

  char sign_hemisphere_close[25];
  fscanf( default_file, "%24[^\n]", sign_hemisphere_close );
  fgetc( default_file );


  // Longitude range
  char longitude_range_open[25];
  fscanf( default_file, "%24[^\n]", longitude_range_open );
  fgetc( default_file );

  getNodeValue( node_value );
  mainFrame->setLongitudeRange( atoi( node_value ) );
  getNodeValue( node_value );

  char longitude_range_close[25];
  fscanf( default_file, "%24[^\n]", longitude_range_close );
  fgetc( default_file );


  // Precision
  char precision_open[25];
  fscanf( default_file, "%24[^\n]", precision_open );
  fgetc( default_file );

  getNodeValue( node_value );
  mainFrame->setPrecision( atoi( node_value ) );
  getNodeValue( node_value );

  char precision_close[25];
  fscanf( default_file, "%24[^\n]", precision_close );
  fgetc( default_file );


  // Leading zeros
  char leading_zeros_open[25];
  fscanf( default_file, "%24[^\n]", leading_zeros_open );
  fgetc( default_file );

  getNodeValue( node_value );
  mainFrame->setLeadingZeros( node_value );

  char leading_zeros_close[25];
  fscanf( default_file, "%24[^\n]", leading_zeros_close );
  fgetc( default_file );
}


// Read the projection parameters in the default file
void Defaults::readParameters( CMasterView* masterView, int projectionType )
{
  char parameters_open[25];
  fscanf( default_file, "%24[^\n]", parameters_open );
  fgetc( default_file );

  char node_value[25];

  switch(projectionType)
  {
    case Eckert4:
    case Eckert6:
    case Miller_Cylindrical:
    case Mollweide:
    case Sinusoidal:
    case Van_der_Grinten:
    {
      getNodeValue( node_value );
      double central_meridian = atof( node_value );
      masterView->set3ParamCentralMeridian( central_meridian );

      getNodeValue( node_value );
      double false_easting = atof( node_value );
      masterView->setFalseEasting( false_easting );

      getNodeValue( node_value );
      double false_northing = atof( node_value );
      masterView->setFalseNorthing( false_northing );
      break;
    }
    case Azimuthal_Equidistant:
    case Bonne:
    case Cassini:
    case Cylindrical_Equal_Area:
    case Gnomonic:
    case Orthographic:
    case Polyconic:
    case Stereographic:
    case Equidistant_Cylindrical:
    case Polar_Stereo:
    {
      getNodeValue( node_value );
      double central_meridian = atof( node_value );
      masterView->set4ParamCentralMeridian( central_meridian );

      getNodeValue( node_value );
      double origin_latitude = atof( node_value );
      masterView->set4ParamOriginLatitude( origin_latitude );

      getNodeValue( node_value );
      double false_easting = atof( node_value );
      masterView->setFalseEasting( false_easting );

      getNodeValue( node_value );
      double false_northing = atof( node_value );
      masterView->setFalseNorthing( false_northing );
      break;
    }
    case Lambert_Conformal_Conic_1:
    case Transverse_Cylindrical_Equal_Area:
    case Transverse_Mercator:
    case Mercator:
    {
      getNodeValue( node_value );
      double central_meridian = atof( node_value );
      masterView->set5ParamCentralMeridian( central_meridian );

      getNodeValue( node_value );
      double origin_latitude = atof( node_value );
      masterView->set5ParamOriginLatitude( origin_latitude );

      getNodeValue( node_value );
      double scale_factor = atof( node_value );
      masterView->set5ParamScaleFactor( scale_factor );

      getNodeValue( node_value );
      double false_easting = atof( node_value );
      masterView->setFalseEasting( false_easting );

      getNodeValue( node_value );
      double false_northing = atof( node_value );
      masterView->setFalseNorthing( false_northing );
      break;
    }
    case Albers_Equal_Area_Conic:
    case Lambert_Conformal_Conic_2:
    {
      getNodeValue( node_value );
      double central_meridian = atof( node_value );
      masterView->set6ParamCentralMeridian( central_meridian );

      getNodeValue( node_value );
      double origin_latitude = atof( node_value );
      masterView->set6ParamOriginLatitude( origin_latitude );

      getNodeValue( node_value );
      double standard_parallel_1 = atof( node_value );
      masterView->set6ParamStandardParallel1( standard_parallel_1 );

      getNodeValue( node_value );
      double standard_parallel_2 = atof( node_value );
      masterView->set6ParamStandardParallel2( standard_parallel_2 );

      getNodeValue( node_value );
      double false_easting = atof( node_value );
      masterView->setFalseEasting( false_easting );

      getNodeValue( node_value );
      double false_northing = atof( node_value );
      masterView->setFalseNorthing( false_northing );
      break;
    }
    case Geodetic:
    {
      getNodeValue( node_value );
      int height_type = atoi( node_value );
      masterView->setGeodeticHeight( height_type );
      break;
    }
    case Local_Cartesian:
    {
      getNodeValue( node_value );
      double origin_longitude = atof( node_value );
      masterView->setOriginLongitude( origin_longitude );

      getNodeValue( node_value );
      double origin_latitude = atof( node_value );
      masterView->setOriginLatitude( origin_latitude );

      getNodeValue( node_value );
      double origin_height = atof( node_value );
      masterView->setOriginHeight( origin_height );

      getNodeValue( node_value );
      double orientation = atof( node_value );
      masterView->setOrientation( orientation );
      break;
    }
    case Neys:
    {
      getNodeValue( node_value );
      double central_meridian = atof( node_value );
      masterView->set6ParamCentralMeridian( central_meridian );

      getNodeValue( node_value );
      double origin_latitude = atof( node_value );
      masterView->set6ParamOriginLatitude( origin_latitude );

      getNodeValue( node_value );
      double standard_parallel_1 = atof( node_value );
      masterView->setNeysStandardParallel1( standard_parallel_1 );

      getNodeValue( node_value );
      double false_easting = atof( node_value );
      masterView->setFalseEasting( false_easting );

      getNodeValue( node_value );
      double false_northing = atof( node_value );
      masterView->setFalseNorthing( false_northing );
      break;
    }
    case Oblique_Mercator:
    {
      getNodeValue( node_value );
      double origin_latitude = atof( node_value );
      masterView->setOmercOriginLatitude( origin_latitude );

      getNodeValue( node_value );
      double scale_factor = atof( node_value );
      masterView->setOmercScaleFactor( scale_factor );

      getNodeValue( node_value );
      double longitude1 = atof( node_value );
      masterView->setOmercLongitude1( longitude1 );

      getNodeValue( node_value );
      double latitude1 = atof( node_value );
      masterView->setOmercLatitude1( latitude1 );

      getNodeValue( node_value );
      double longitude2 = atof( node_value );
      masterView->setOmercLongitude2( longitude2 );

      getNodeValue( node_value );
      double latitude2 = atof( node_value );
      masterView->setOmercLatitude2( latitude2 );

      getNodeValue( node_value );
      double false_easting = atof( node_value );
      masterView->setOmercFalseEasting( false_easting );

      getNodeValue( node_value );
      double false_northing = atof( node_value );
      masterView->setOmercFalseNorthing( false_northing );
      break;
    }
    case UTM:
    {
      getNodeValue( node_value );
      int override = atoi( node_value );
      masterView->setOverride( override );

      getNodeValue( node_value );
      long zone = atoi( node_value );
      masterView->setZone( zone );
      break;
    }
  }

  char parameters_close[25];
  fscanf( default_file, "%24[^\n]", parameters_close );
  fgetc( default_file );
}


// Read a node value
void Defaults::getNodeValue( char node_value[25] )
{
  char tag_open[35];
  fscanf( default_file, "%34[^>]", tag_open );
  fgetc( default_file );

  node_value[0] = '\0';
  fscanf( default_file, "%34[^<]", node_value);
  fgetc( default_file );

  char tag_close[35];
  fscanf( default_file, "%34[^\n]", tag_close );
  fgetc( default_file );
}