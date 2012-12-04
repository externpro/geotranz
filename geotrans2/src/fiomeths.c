/***************************************************************************/
/* RSC IDENTIFIER: FIOMETHS
 *
 * ABSTRACT
 *
 *    This component provides file processing capability to GEOTRANS.
 *
 *    This component depends on the following modules:  ENGINE,
 *    ERRHAND, COMPHACK, FTOVAL, STRTOVAL.
 *
 * ERROR HANDLING
 *
 *    This component checks for errors in the file input data and if
 *    an error is found it passes an error code back to the calling routine.
 *
 *
 * REUSE NOTES
 *
 *    FIOMETHS is not specifically intended for reuse, as it is designed
 *    to work with files of a very specific format.
 *
 *
 * REFERENCES
 *
 *    Further information on FIOMETHS can be found in the GEOTRANS Programmer's
 *    Guide.
 *
 *    FIOMETHS originated from :  U.S. Army Topographic Engineering Center
 *                             Digital Concepts & Analysis Center
 *                             7701 Telegraph Road
 *                             Alexandria, VA  22310-3864
 *
 * LICENSES
 *
 *    None apply to this component.
 *
 * RESTRICTIONS
 *
 *    FIOMETHS has no restrictions.
 *
 * ENVIRONMENT
 *
 *    FIOMETHS was tested and certified in the following environments:
 *
 *    1. Solaris 2.5 with GCC, version 2.7.2.1
 *    2. MSDOS with MS Visual C++, version 1.52c
 *
 * MODIFICATIONS
 *
 *    Date              Description
 *    ----              -----------
 *    04-22-97          Original Code
 *    06-28-99          Added new DT&CC Modules
 *    09-13-00          Added new DT&CC Modules
 *    03-29-01          Improved file formatting flexibility
 *    08-17-05          Changed Lambert_Conformal_Conic to Lambert_Conformal_Conic_2
 *    01-18-06          Added changes for new height types
 */


/***************************************************************************/

/*                              INCLUDES                                 */
#include <string.h>
#include <stdio.h>
#include <ctype.h>
#include <math.h>
#include "fiomeths.h"
#include "engine.h"
#include "strtoval.h"

#define PI    3.14159265358979323e0  /* PI        */
#define PI_Over_180  PI / 180.0  /* PI        */

/* Local variable definitions */

typedef enum File_Header_Declarations
{
  FHD_End_of_Header = 0,        /* End of header */
  FHD_Comment,                  /* Separator/Comment */
  FHD_Projection,               /* Coordinate System, Grid, or Projection */
  FHD_Datum,                    /* Datum */
  FHD_No_Height,                /* No Height */
  FHD_Ellipsoid_Height,         /* Ellipsoid Height */
  FHD_MSL_EGM96_15M_BL_Height,  /* MSL EGM96 15M BL Height */
  FHD_MSL_EGM96_VG_NS_Height,   /* MSL EGM96 VG NS Height */
  FHD_MSL_EGM84_10D_BL_Height,  /* MSL EGM84 10D BL Height */
  FHD_MSL_EGM84_10D_NS_Height,  /* MSL EGM84 10D NS Height */
  FHD_Central_Meridian,         /* Central Meridian */
  FHD_Origin_Latitude,          /* Origin Latitude */
  FHD_Origin_Longitude,         /* Origin Longitude */
  FHD_Latitude_of_True_Scale,   /* Latitude of True Scale */
  FHD_Longitude_Down_from_Pole, /* Longitude Down from Pole */
  FHD_Latitude_One,             /* Latitude One */
  FHD_Longitude_One,            /* Longitude One */
  FHD_Latitude_Two,             /* Latitude Two */
  FHD_Longitude_Two,            /* Longitude Two */
  FHD_Origin_Height,            /* Origin Height */
  FHD_Orientation,              /* Orientation */
  FHD_Standard_Parallel,        /* Standard Parallel  */
  FHD_Standard_Parallel_One,    /* Standard Parallel One */
  FHD_Standard_Parallel_Two,    /* Standard Parallel Two */
  FHD_Hemisphere,               /* Hemisphere */
  FHD_False_Easting,            /* False Easting */
  FHD_False_Northing,           /* False Northing */
  FHD_Scale_Factor,             /* Scale Factor */
  FHD_Invalid_Header
} FHD_Value;


typedef enum File_to_Value_Conversion_Status
{
  /* Success */
  FVC_Success = 0,
  /* File_to_Longitude errors */
  FVC_Degrees_out_of_Bounds = -11,
  FVC_Minutes_out_of_Bounds = -12,
  FVC_Seconds_out_of_Bounds = -13,
  FVC_Minutes_or_Seconds_Overflow = -14,
  FVC_Inappropriate_Hemisphere = -15,
  FVC_Sign_and_Hemisphere = -16,
  FVC_Misplaced_Hemisphere = -17,
  FVC_File_Read_Longitude = -18,
  FVC_File_Read_Latitude = -19,
  FVC_File_Read_Hemisphere = -20,
  /* <Degrees>_to_File errors */
  FVC_DMS_to_File = -21,
  FVC_DM_to_File = -22,
  FVC_D_to_File = -23,
  FVC_File_Write_Longitude = -24,
  FVC_File_Write_Latitude = -25,
  /* <Parameter>_to_File errors */
  /* Parameter Specific errors */
  FVC_Zone_out_of_Bounds = -71,
  FVC_Scale_Factor_out_of_Bounds = -72,
  /* File errors */
  FVC_Error_Opening_File = -501,
  FVC_Error_Closing_File = -502,
  FVC_Error_Writing_String = -503,
  FVC_Error_Reading_Noise = -504,
  FVC_Error_Parsing_Header = -505,
  FVC_Invalid_Header = -506,
  FVC_Error_Parsing_File = -507,
  FVC_EOF = -508,
  /* General error */
  FVC_Error = -1000
} FVC_Status;

static FILE *input_File = 0;
static FILE *output_File = 0;
static Height_Type input_height_type;
static boole use_NSEW_;
static boole use_Minutes_;
static boole use_Seconds_;

const char* coordinates_Header_String = "COORDINATES";
const char* projection_Header_String = "PROJECTION";
const char* datum_Header_String = "DATUM";
const char* no_Height_Header_String = "NO HEIGHT";
const char* ellipsoid_Height_Header_String = "ELLIPSOID HEIGHT";
const char* geoid_Height_Header_String = "GEOID/MSL HEIGHT";
const char* msl_EGM96_15M_BL_Height_Header_String = "MSL-EGM96-15M-BL HEIGHT";
const char* msl_EGM96_VG_NS_Height_Header_String = "MSL-EGM96-VG-NS HEIGHT";
const char* msl_EGM84_10D_BL_Height_Header_String = "MSL-EGM84-10D-BL HEIGHT";
const char* msl_EGM84_10D_NS_Height_Header_String = "MSL-EGM84-10D-NS HEIGHT";
const char* central_Meridian_Header_String = "CENTRAL MERIDIAN";
const char* origin_Latitude_Header_String = "ORIGIN LATITUDE";
const char* origin_Longitude_Header_String = "ORIGIN LONGITUDE";
const char* latitude_Of_True_Scale_Header_String = "LATITUDE OF TRUE SCALE";
const char* polarst_Longitude_Header_String = "LONGITUDE DOWN FROM POLE";
const char* latitude_One_Header_String = "LATITUDE ONE";
const char* longitude_One_Header_String = "LONGITUDE ONE";
const char* latitude_Two_Header_String = "LATITUDE TWO";
const char* longitude_Two_Header_String = "LONGITUDE TWO";
const char* origin_Height_Header_String = "ORIGIN HEIGHT";
const char* orientation_Header_String = "ORIENTATION";
const char* standard_Parallel_Header_String = "STANDARD PARALLEL";
const char* standard_Parallel_One_Header_String = "STANDARD PARALLEL ONE";
const char* standard_Parallel_Two_Header_String = "STANDARD PARALLEL TWO";
const char* scale_Factor_Header_String = "SCALE FACTOR";
const char* hemisphere_Header_String = "HEMISPHERE";
const char* false_Easting_Header_String = "FALSE EASTING";
const char* false_Northing_Header_String = "FALSE NORTHING";
const char* end_Of_Header_String = "END OF HEADER";
const char* ce90_String = "CE90";
const char* le90_String = "LE90";
const char* se90_String = "SE90";


/* Private functions */

FVC_Status Read_Coord(double *easting, double *northing)
{
  char buf[256];
  FVC_Status error_Code = FVC_Success;

  if (!feof(input_File) && (fscanf(input_File, "%255[^, \t\n]", buf)))
    error_Code = String_to_Double(buf,easting);
  else
    error_Code = FVC_Error;

  if(!error_Code)
  {
    fscanf(input_File, "%[, \t]", buf);
    if (!feof(input_File) && (fscanf(input_File, "%255[^, \t\n]", buf)))
      error_Code = String_to_Double(buf,northing);
    else
      error_Code = FVC_Error;
  }
  return error_Code;
}


void Write_Coord(double easting, double northing)
{
  char meter_str[15];

  Meter_to_String(easting,meter_str);
  fprintf(output_File, "%s", meter_str);
  fprintf(output_File, ", ");
  Meter_to_String(northing,meter_str);
  fprintf(output_File, "%s", meter_str);
}


FVC_Status Open_File(Input_or_Output IOValue, const char *filename, FILE **file)
{ /* Open_File */
  FVC_Status error_Code = FVC_Success;
  char *control_String = "r";
  FILE *local_File = NULL;
  if (IOValue == Input)
    control_String = "r";
  else if (IOValue == Output)
    control_String = "w";
  local_File = fopen(filename, control_String);
  if (local_File)
    *file = local_File;
  else
  {
    error_Code = FVC_Error_Opening_File;
    *file = NULL;
  }
  return error_Code;
} /* Open_File */


FVC_Status Close_File(FILE **file)
{ /* Close_File  */
  FVC_Status error_Code = FVC_Success;
  if (*file != NULL)
  {
    fclose(*file);
    *file = NULL;
  }
  return error_Code;
} /* Close_File */


FVC_Status Eat_Noise(FILE *file)
{ /* Eat_Noise */
  char noise[256] = "";
  if ((fscanf(file, "%255[:, \n\r\t]", noise) == 0) && feof(file))
    return FVC_EOF;
  return FVC_Success;
} /* Eat_Noise */


FVC_Status Next_Header_Line(FILE *file, FHD_Value *header)
{
  FVC_Status error_Code = FVC_Success;
  FHD_Value header_Line = FHD_Comment;
  int next_Character = '\0';
  char garbage_Array[512];
  while (header_Line == FHD_Comment && !error_Code)
  {
    /* eat all whitespace */
    fscanf(file, " ");
    next_Character = fgetc(file);
    if (next_Character == '#')
      fgets(garbage_Array, 511, file);
    else
    {
      if (ungetc(next_Character, file) != next_Character)
        error_Code = FVC_Error_Parsing_Header;
      else
      {
        int i, length;
        char header_Value[32] = "";
        long ftell_Location = ftell(file);
        fscanf(file, "%31[^:\n]", header_Value);
        length = strlen(header_Value);
        for (i = 0; i < length; i++)
          header_Value[i] = (char)toupper(header_Value[i]);

        if (strstr(header_Value, projection_Header_String) ||
            strstr(header_Value, coordinates_Header_String))
          header_Line = FHD_Projection;
        else if (strstr(header_Value, datum_Header_String))
          header_Line = FHD_Datum;
        else if (strstr(header_Value, no_Height_Header_String))
          header_Line = FHD_No_Height;
        else if (strstr(header_Value, ellipsoid_Height_Header_String))
          header_Line = FHD_Ellipsoid_Height;
        else if (strstr(header_Value, geoid_Height_Header_String))
          header_Line = FHD_MSL_EGM96_15M_BL_Height;
        else if (strstr(header_Value, msl_EGM96_15M_BL_Height_Header_String))
          header_Line = FHD_MSL_EGM96_15M_BL_Height;
        else if (strstr(header_Value, msl_EGM96_VG_NS_Height_Header_String))
          header_Line = FHD_MSL_EGM96_VG_NS_Height;
        else if (strstr(header_Value, msl_EGM84_10D_BL_Height_Header_String))
          header_Line = FHD_MSL_EGM84_10D_BL_Height;
        else if (strstr(header_Value, msl_EGM84_10D_NS_Height_Header_String))
          header_Line = FHD_MSL_EGM84_10D_NS_Height;
        else if (strstr(header_Value, central_Meridian_Header_String))
          header_Line = FHD_Central_Meridian;
        else if (strstr(header_Value, latitude_Of_True_Scale_Header_String))
          header_Line = FHD_Latitude_of_True_Scale;
        else if (strstr(header_Value, polarst_Longitude_Header_String))
          header_Line = FHD_Longitude_Down_from_Pole;
        else if (strstr(header_Value, origin_Latitude_Header_String))
          header_Line = FHD_Origin_Latitude;
        else if (strstr(header_Value, origin_Longitude_Header_String))
          header_Line = FHD_Origin_Longitude;
        else if (strstr(header_Value, origin_Height_Header_String))
          header_Line = FHD_Origin_Height;
        else if (strstr(header_Value, orientation_Header_String))
          header_Line = FHD_Orientation;
        else if (strstr(header_Value, latitude_One_Header_String))
          header_Line = FHD_Latitude_One;
        else if (strstr(header_Value, longitude_One_Header_String))
          header_Line = FHD_Longitude_One;
        else if (strstr(header_Value, latitude_Two_Header_String))
          header_Line = FHD_Latitude_Two;
        else if (strstr(header_Value, longitude_Two_Header_String))
          header_Line = FHD_Longitude_Two;
        else if (strstr(header_Value, standard_Parallel_One_Header_String))
          header_Line = FHD_Standard_Parallel_One;
        else if (strstr(header_Value, standard_Parallel_Two_Header_String))
          header_Line = FHD_Standard_Parallel_Two;
        else if (strstr(header_Value, standard_Parallel_Header_String))
          header_Line = FHD_Standard_Parallel;
        else if (strstr(header_Value, scale_Factor_Header_String))
          header_Line = FHD_Scale_Factor;
        else if (strstr(header_Value, hemisphere_Header_String))
          header_Line = FHD_Hemisphere;
        else if (strstr(header_Value, false_Easting_Header_String))
          header_Line = FHD_False_Easting;
        else if (strstr(header_Value, false_Northing_Header_String))
          header_Line = FHD_False_Northing;
        else if (strstr(header_Value, end_Of_Header_String))
          header_Line = FHD_End_of_Header;
        else
        {
          error_Code = FVC_Invalid_Header;
          header_Line = FHD_Invalid_Header;
          fseek(file, ftell_Location, SEEK_SET);
        }
        Eat_Noise(file);
      }
    }
  }
  *header = header_Line;
  return error_Code;
}


FIO_Status Parse_Input_File_Header(FILE *file)
{
  FIO_Status error_Code = FIO_Success;
  SVC_Status error_Code_String = SVC_Success;
  FVC_Status error_Code_File = FVC_Success;
  FHD_Value header_Line = FHD_Comment;
  long error_Code_Engine = 0;
  char buf[256];
  long length;
  Coordinate_Type projection_Type = Geodetic;
  Albers_Equal_Area_Conic_Parameters  albers_params = {0.0};
  Azimuthal_Equidistant_Parameters  azimuthal_equidistant_params = {0.0};
  Bonne_Parameters                  bonne_params = {0.0};
  Cassini_Parameters                cassini_params = {0.0};
  Cylindrical_Equal_Area_Parameters   cylindrical_equal_area_params = {0.0};
  Equidistant_Cylindrical_Parameters  equidistant_cylindrical_params = {0.0};
  Eckert4_Parameters                eckert4_params = {0.0};
  Eckert6_Parameters                eckert6_params = {0.0};
  Gnomonic_Parameters               gnomonic_params = {0.0};
  Lambert_Conformal_Conic_1_Parameters  lambert_1_params = {0.0};
  Lambert_Conformal_Conic_2_Parameters  lambert_2_params = {0.0};
  Local_Cartesian_Parameters        local_cartesian_params = {0.0};
  Mercator_Parameters               mercator_params = {0.0};
  Miller_Cylindrical_Parameters     miller_params = {0.0};
  Mollweide_Parameters              mollweide_params = {0.0};
  Neys_Parameters                   neys_params = {0.0};
  Oblique_Mercator_Parameters       oblique_mercator_params = {0.0};
  Orthographic_Parameters           orthographic_params = {0.0};
  Polar_Stereo_Parameters           polar_stereo_params = {0.0};
  Polyconic_Parameters              polyconic_params = {0.0};
  Sinusoidal_Parameters             sinusoidal_params = {0.0};
  Stereographic_Parameters          stereographic_params = {0.0};
  Transverse_Cylindrical_Equal_Area_Parameters  transverse_cylindrical_equal_area_params = {0.0};
  Transverse_Mercator_Parameters    transverse_mercator_params = {0.0};
  Van_der_Grinten_Parameters        van_der_grinten_params = {0.0};

  /* Process each header line until end-of-header sequence reached */
  error_Code_File = Next_Header_Line(file, &header_Line);
  if (error_Code_File)
    return FIO_Error_Parsing_Header;
  while (header_Line != FHD_End_of_Header)
  {
    switch (header_Line)
    {
    case FHD_Projection:
      {
        char coord_Type[256] = "";
        if (fgets(coord_Type,256,file) == NULL)
          return FIO_Error_Projection;
        else
        {
          int i = 0;
          while(isalpha(coord_Type[i]) || (coord_Type[i] == ' ') || (coord_Type[i] == '\'')
                || (coord_Type[i] == '(') || (coord_Type[i] == ')')
                || (coord_Type[i] == '1') || (coord_Type[i] == '2'))
          {
            if (isalpha(coord_Type[i]))
              coord_Type[i] = (char)toupper(coord_Type[i]);
            i++;
          }
          coord_Type[i] = '\0';
          error_Code_String = String_to_Projection(coord_Type, &projection_Type);
          if (error_Code_String)
            return FIO_Error_Projection;
          else
          {
            error_Code_Engine = Set_Coordinate_System(File, Input, projection_Type);
            if (error_Code_Engine)
              return FIO_Error_Setting_Engine;
            else
              switch (projection_Type)
              {
              case Albers_Equal_Area_Conic:
                {
                  Get_Albers_Equal_Area_Conic_Params(File, Input, &albers_params);
                  break;
                }
              case Azimuthal_Equidistant:
                {
                  Get_Azimuthal_Equidistant_Params(File, Input, &azimuthal_equidistant_params);
                  break;
                }
              case Bonne:
                {
                  Get_Bonne_Params(File, Input, &bonne_params);
                  break;
                }
              case Cassini:
                {
                  Get_Cassini_Params(File, Input, &cassini_params);
                  break;
                }
              case Cylindrical_Equal_Area:
                {
                  Get_Cylindrical_Equal_Area_Params(File, Input, &cylindrical_equal_area_params);
                  break;
                }
              case Eckert4:
                {
                  Get_Eckert4_Params(File, Input, &eckert4_params);
                  break;
                }
              case Eckert6:
                {
                  Get_Eckert6_Params(File, Input, &eckert6_params);
                  break;
                }
              case Equidistant_Cylindrical:
                {
                  Get_Equidistant_Cylindrical_Params(File, Input, &equidistant_cylindrical_params);
                  break;
                }
              case Gnomonic:
                {
                  Get_Gnomonic_Params(File, Input, &gnomonic_params);
                  break;
                }
              case Lambert_Conformal_Conic_1:
                {
                  Get_Lambert_Conformal_Conic_1_Params(File, Input, &lambert_1_params);
                  break;
                }
              case Lambert_Conformal_Conic_2:
                {
                  Get_Lambert_Conformal_Conic_2_Params(File, Input, &lambert_2_params);
                  break;
                }
              case Local_Cartesian:
                {
                  Get_Local_Cartesian_Params(File, Input, &local_cartesian_params);
                  break;
                }
              case Mercator:
                {
                  Get_Mercator_Params(File, Input, &mercator_params);
                  break;
                }
              case Miller_Cylindrical:
                {
                  Get_Miller_Cylindrical_Params(File, Input, &miller_params);
                  break;
                }
              case Mollweide:
                {
                  Get_Mollweide_Params(File, Input, &mollweide_params);
                  break;
                }
              case Neys:
                {
                  Get_Neys_Params(File, Input, &neys_params);
                  break;
                }
              case Oblique_Mercator:
                {
                  Get_Oblique_Mercator_Params(File, Input, &oblique_mercator_params);
                  break;
                }
              case Orthographic:
                {
                  Get_Orthographic_Params(File, Input, &orthographic_params);
                  break;
                }
              case Polar_Stereo:
                {
                  Get_Polar_Stereo_Params(File, Input, &polar_stereo_params);
                  break;
                }
              case Polyconic:
                {
                  Get_Polyconic_Params(File, Input, &polyconic_params);
                  break;
                }
              case Sinusoidal:
                {
                  Get_Sinusoidal_Params(File, Input, &sinusoidal_params);
                  break;
                }
              case Stereographic:
                {
                  Get_Stereographic_Params(File, Input, &stereographic_params);
                  break;
                }
              case Transverse_Cylindrical_Equal_Area:
                {
                  Get_Transverse_Cylindrical_Equal_Area_Params(File, Input, &transverse_cylindrical_equal_area_params);
                  break;
                }
              case Transverse_Mercator:
                {
                  Get_Transverse_Mercator_Params(File, Input, &transverse_mercator_params);
                  break;
                }
              case Van_der_Grinten:
                {
                  Get_Van_der_Grinten_Params(File, Input, &van_der_grinten_params);
                  break;
                }
              }
          }
        }
        break;
      }
    case FHD_Datum:
      {
        char datum_Code[7];
        if (fscanf(file, "%s", datum_Code) <=0)
          return FIO_Error_Datum;
        else
        {
          long datum_Index = 0;
          error_Code_Engine = Get_Datum_Index(datum_Code, &datum_Index);
          if (error_Code_Engine)
            return FIO_Error_Datum;
          else
            error_Code_Engine = Set_Datum(File, Input, datum_Index);
        }
        break;
      }
    case FHD_No_Height:
      {
        Geodetic_Parameters params;
        params.height_type = No_Height;
        Set_Geodetic_Params(File,Input,params);
        break;
      }
    case FHD_Ellipsoid_Height:
      {
        Geodetic_Parameters params;
        params.height_type = Ellipsoid_Height;
        Set_Geodetic_Params(File,Input,params);
        break;
      }
    case FHD_MSL_EGM96_15M_BL_Height:
      {
        Geodetic_Parameters params;
        params.height_type = Geoid_or_MSL_Height;
        Set_Geodetic_Params(File,Input,params);
        break;
      }
    case FHD_MSL_EGM96_VG_NS_Height:
      {
        Geodetic_Parameters params;
        params.height_type = MSL_EGM96_VG_NS_Height;
        Set_Geodetic_Params(File,Input,params);
        break;
      }
    case FHD_MSL_EGM84_10D_BL_Height:
      {
        Geodetic_Parameters params;
        params.height_type = MSL_EGM84_10D_BL_Height;
        Set_Geodetic_Params(File,Input,params);
        break;
      }
    case FHD_MSL_EGM84_10D_NS_Height:
      {
        Geodetic_Parameters params;
        params.height_type = MSL_EGM84_10D_NS_Height;
        Set_Geodetic_Params(File,Input,params);
        break;
      }
    case FHD_Central_Meridian:
      {
        double value = 0.0;
        long error_code = 0;
        Eat_Noise(file);
        error_code = fscanf(file, "%14[ 0123456789NSEW:/+.-]", buf);
        if (error_code)
        {
          error_code = String_to_Longitude(buf,&value);
          if (!error_code)
          {
            value *= PI / 180.0;
            switch (projection_Type)
            {
            case Albers_Equal_Area_Conic:
              {
                albers_params.central_meridian = value;
                break;
              }
            case Azimuthal_Equidistant:
              {
                azimuthal_equidistant_params.central_meridian = value;
                break;
              }
            case Bonne:
              {
                bonne_params.central_meridian = value;
                break;
              }
            case Cassini:
              {
                cassini_params.central_meridian = value;
                break;
              }
            case Cylindrical_Equal_Area:
              {
                cylindrical_equal_area_params.central_meridian = value;
                break;
              }
            case Eckert4:
              {
                eckert4_params.central_meridian = value;
                break;
              }
            case Eckert6:
              {
                eckert6_params.central_meridian = value;
                break;
              }
            case Equidistant_Cylindrical:
              {
                equidistant_cylindrical_params.central_meridian = value;
                break;
              }
            case Gnomonic:
              {
                gnomonic_params.central_meridian = value;
                break;
              }
            case Lambert_Conformal_Conic_1:
              {
                lambert_1_params.central_meridian = value;
                break;
              }
            case Lambert_Conformal_Conic_2:
              {
                lambert_2_params.central_meridian = value;
                break;
              }
            case Mercator:
              {
                mercator_params.central_meridian = value;
                break;
              }
            case Miller_Cylindrical:
              {
                miller_params.central_meridian = value;
                break;
              }
            case Mollweide:
              {
                mollweide_params.central_meridian = value;
                break;
              }
            case Neys:
              {
                neys_params.central_meridian = value;
                break;
              }
            case Orthographic:
              {
                orthographic_params.central_meridian = value;
                break;
              }
            case Polyconic:
              {
                polyconic_params.central_meridian = value;
                break;
              }
            case Sinusoidal:
              {
                sinusoidal_params.central_meridian = value;
                break;
              }
            case Stereographic:
              {
                stereographic_params.central_meridian = value;
                break;
              }
            case Transverse_Cylindrical_Equal_Area:
              {
                transverse_cylindrical_equal_area_params.central_meridian = value;
                break;
              }
            case Transverse_Mercator:
              {
                transverse_mercator_params.central_meridian = value;
                break;
              }
            case Van_der_Grinten:
              {
                van_der_grinten_params.central_meridian = value;
                break;
              }
            default:
              {
                return FIO_Error_Central_Meridian;
              }
            }
          }
          else
            return FIO_Error_Central_Meridian;
        }
        else
          return FIO_Error_Central_Meridian;
        break;
      }
    case FHD_Latitude_of_True_Scale:
      {
        double value = 0.0;
        long error_code = 0;
        Eat_Noise(file);
        error_code = fscanf(file, "%13[ 0123456789NSEW:/.+-]", buf);
        if (error_code)
        {
          error_code = String_to_Latitude(buf,&value);
          if (!error_code)
          {
            value *= PI / 180.0;
            if (projection_Type == Polar_Stereo)
              polar_stereo_params.latitude_of_true_scale = value;
            else if (projection_Type == Mercator)
              mercator_params.latitude_of_true_scale = value;
            else return FIO_Error_Latitude_of_True_Scale;
          }
          else
            return FIO_Error_Latitude_of_True_Scale;
        }
        else
          return FIO_Error_Latitude_of_True_Scale;
        break;
      }
    case FHD_Longitude_Down_from_Pole:
      {
        double value = 0.0;
        long error_code = 0;
        Eat_Noise(file);
        error_code = fscanf(file, "%14[ 0123456789NSEW:/+.-]", buf);
        if (error_code)
        {
          error_code = String_to_Longitude(buf,&value);
          if (!error_code)
          {
            value *= PI / 180.0;
            if (projection_Type == Polar_Stereo)
              polar_stereo_params.longitude_down_from_pole = value;
            else return FIO_Error_Longitude_Down_from_Pole;
          }
          else
            return FIO_Error_Longitude_Down_from_Pole;
        }
        else
          return FIO_Error_Longitude_Down_from_Pole;
        break;
      }
    case FHD_Origin_Latitude:
      {
        double value = 0.0;
        long error_code = 0;
        Eat_Noise(file);
        error_code = fscanf(file, "%13[ 0123456789NSEW:/.+-]", buf);
        if (error_code)
        {
          error_code = String_to_Latitude(buf,&value);
          if (!error_code)
          {
            value *= PI / 180.0;
            switch (projection_Type)
            {
            case Albers_Equal_Area_Conic:
              {
                albers_params.origin_latitude = value;
                break;
              }
            case Azimuthal_Equidistant:
              {
                azimuthal_equidistant_params.origin_latitude = value;
                break;
              }
            case Bonne:
              {
                bonne_params.origin_latitude = value;
                break;
              }
            case Cassini:
              {
                cassini_params.origin_latitude = value;
                break;
              }
            case Cylindrical_Equal_Area:
              {
                cylindrical_equal_area_params.origin_latitude = value;
                break;
              }
            case Gnomonic:
              {
                gnomonic_params.origin_latitude = value;
                break;
              }
            case Lambert_Conformal_Conic_1:
              {
                lambert_1_params.origin_latitude = value;
                break;
              }
            case Lambert_Conformal_Conic_2:
              {
                lambert_2_params.origin_latitude = value;
                break;
              }
            case Local_Cartesian:
              {
                local_cartesian_params.origin_latitude = value;
                break;
              }
            case Neys:
              {
                neys_params.origin_latitude = value;
                break;
              }
            case Oblique_Mercator:
              {
                oblique_mercator_params.origin_latitude = value;
                break;
              }
            case Orthographic:
              {
                orthographic_params.origin_latitude = value;
                break;
              }
            case Polyconic:
              {
                polyconic_params.origin_latitude = value;
                break;
              }
            case Stereographic:
              {
                stereographic_params.origin_latitude = value;
                break;
              }
            case Transverse_Cylindrical_Equal_Area:
              {
                transverse_cylindrical_equal_area_params.origin_latitude = value;
                break;
              }
            case Transverse_Mercator:
              {
                transverse_mercator_params.origin_latitude = value;
                break;
              }
            default:
              {
                return FIO_Error_Origin_Latitude;
              }
            }
          }
          else
            return FIO_Error_Origin_Latitude;
        }
        else
          return FIO_Error_Origin_Latitude;
        break;
      }
    case FHD_Origin_Longitude:
      {
        double value = 0.0;
        long error_code = 0;
        Eat_Noise(file);
        error_code = fscanf(file, "%14[ 0123456789NSEW:/+.-]", buf);
        if (error_code)
        {
          error_code = String_to_Longitude(buf,&value);
          if (!error_code)
          {
            value *= PI / 180.0;
            if (projection_Type == Local_Cartesian)
              local_cartesian_params.origin_longitude = value;
            else return FIO_Error_Origin_Longitude;
          }
          else
            return FIO_Error_Origin_Longitude;
        }
        else
          return FIO_Error_Origin_Longitude;
        break;
      }
    case FHD_Origin_Height:
      {
        double value = 0.0;
        long error_code = fscanf(file, "%s", buf);
        if (error_code)
        {
          length = strlen(buf)-1;
          if (!isdigit(buf[length]))
            buf[length] = 0;
          error_code = String_to_Double(buf,&value);
          if (!error_code)
            if (projection_Type == Local_Cartesian)
              local_cartesian_params.origin_height = value;
            else return FIO_Error_Origin_Height;
          else
            return FIO_Error_Origin_Height;
        }
        else
          return FIO_Error_Origin_Height;
        break;
      }
    case FHD_Orientation:
      {
        double value = 0.0;
        long error_code = 0;
        Eat_Noise(file);
        error_code = fscanf(file, "%14[ 0123456789NSEW:/+.-]", buf);
        if (error_code)
        {
          error_code = String_to_Longitude(buf,&value);
          if (!error_code)
          {
            value *= PI / 180.0;
            if (projection_Type == Local_Cartesian)
              local_cartesian_params.orientation = value;
            else return FIO_Error_Orientation;
          }
          else
            return FIO_Error_Orientation;
        }
        else
          return FIO_Error_Orientation;
        break;
      }
    case FHD_Latitude_One:
      {
        double value = 0.0;
        long error_code = 0;
        Eat_Noise(file);
        error_code = fscanf(file, "%13[ 0123456789NSEW:/.+-]", buf);
        if (error_code)
        {
          error_code = String_to_Latitude(buf,&value);
          if (!error_code)
          {
            value *= PI / 180.0;
            if (projection_Type == Oblique_Mercator)
              oblique_mercator_params.latitude_1 = value;
            else return FIO_Error_Latitude_One;
          }
          else
            return FIO_Error_Latitude_One;
        }
        else
          return FIO_Error_Latitude_One;
        break;
      }
    case FHD_Longitude_One:
      {
        double value = 0.0;
        long error_code = 0;
        Eat_Noise(file);
        error_code = fscanf(file, "%13[ 0123456789NSEW:/.+-]", buf);
        if (error_code)
        {
          error_code = String_to_Longitude(buf,&value);
          if (!error_code)
          {
            value *= PI / 180.0;
            if (projection_Type == Oblique_Mercator)
              oblique_mercator_params.longitude_1 = value;
            else return FIO_Error_Longitude_One;
          }
          else
            return FIO_Error_Longitude_One;
        }
        else
          return FIO_Error_Longitude_One;
        break;
      }
    case FHD_Latitude_Two:
      {
        double value = 0.0;
        long error_code = 0;
        Eat_Noise(file);
        error_code = fscanf(file, "%13[ 0123456789NSEW:/.+-]", buf);
        if (error_code)
        {
          error_code = String_to_Latitude(buf,&value);
          if (!error_code)
          {
            value *= PI / 180.0;
            if (projection_Type == Oblique_Mercator)
              oblique_mercator_params.latitude_2 = value;
            else return FIO_Error_Latitude_Two;
          }
          else
            return FIO_Error_Latitude_Two;
        }
        else
          return FIO_Error_Latitude_Two;
        break;
      }
    case FHD_Longitude_Two:
      {
        double value = 0.0;
        long error_code = 0;
        Eat_Noise(file);
        error_code = fscanf(file, "%13[ 0123456789NSEW:/.+-]", buf);
        if (error_code)
        {
          error_code = String_to_Longitude(buf,&value);
          if (!error_code)
          {
            value *= PI / 180.0;
            if (projection_Type == Oblique_Mercator)
              oblique_mercator_params.longitude_2 = value;
            else return FIO_Error_Longitude_Two;
          }
          else
            return FIO_Error_Longitude_Two;
        }
        else
          return FIO_Error_Longitude_Two;
        break;
      }
    case FHD_Standard_Parallel:
      {
        double value = 0.0;
        long error_code = 0;
        Eat_Noise(file);
        error_code = fscanf(file, "%13[ 0123456789NSEW:/.+-]", buf);
        if (error_code)
        {
          error_code = String_to_Latitude(buf,&value);
          if (!error_code)
          {
            value *= PI / 180.0;
            if (projection_Type == Equidistant_Cylindrical)
              equidistant_cylindrical_params.std_parallel = value;
            else return FIO_Error_Standard_Parallel;
          }
          else
            return FIO_Error_Standard_Parallel;
        }
        else
          return FIO_Error_Standard_Parallel;
        break;
      }
    case FHD_Standard_Parallel_One:
      {
        double value = 0.0;
        long error_code = 0;
        Eat_Noise(file);
        error_code = fscanf(file, "%13[ 0123456789NSEW:/.+-]", buf);
        if (error_code)
        {
          error_code = String_to_Latitude(buf,&value);
          if (!error_code)
          {
            value *= PI / 180.0;
            if (projection_Type == Albers_Equal_Area_Conic)
              albers_params.std_parallel_1 = value;
            else if (projection_Type == Lambert_Conformal_Conic_2)
              lambert_2_params.std_parallel_1 = value;
            else if (projection_Type == Neys)
              neys_params.std_parallel_1 = value;
            else return FIO_Error_Standard_Parallel_One;
          }
          else
            return FIO_Error_Standard_Parallel_One;
        }
        else
          return FIO_Error_Standard_Parallel_One;
        break;
      }
    case FHD_Standard_Parallel_Two:
      {
        double value = 0.0;
        long error_code = 0;
        Eat_Noise(file);
        error_code = fscanf(file, "%13[ 0123456789NSEW:/.+-]", buf);
        if (error_code)
        {
          error_code = String_to_Latitude(buf,&value);
          if (!error_code)
          {
            value *= PI / 180.0;
            if (projection_Type == Albers_Equal_Area_Conic)
              albers_params.std_parallel_2 = value;
            else if (projection_Type == Lambert_Conformal_Conic_2)
              lambert_2_params.std_parallel_2 = value;
            else return FIO_Error_Standard_Parallel_Two;
          }
          else
            return FIO_Error_Standard_Parallel_Two;
        }
        else
          return FIO_Error_Standard_Parallel_Two;
        break;
      }
    case FHD_False_Easting:
      {
        double value = 0.0;
        long error_code = fscanf(file, "%s", buf);
        if (error_code)
        {
          length = strlen(buf)-1;
          if (!isdigit(buf[length]))
            buf[length] = 0;
          error_code = String_to_Double(buf,&value);
          if (!error_code)
            switch (projection_Type)
            {
            case Albers_Equal_Area_Conic:
              {
                albers_params.false_easting = value;
                break;
              }
            case Azimuthal_Equidistant:
              {
                azimuthal_equidistant_params.false_easting = value;
                break;
              }
            case Bonne:
              {
                bonne_params.false_easting = value;
                break;
              }
            case Cassini:
              {
                cassini_params.false_easting = value;
                break;
              }
            case Cylindrical_Equal_Area:
              {
                cylindrical_equal_area_params.false_easting = value;
                break;
              }
            case Eckert4:
              {
                eckert4_params.false_easting = value;
                break;
              }
            case Eckert6:
              {
                eckert6_params.false_easting = value;
                break;
              }
            case Equidistant_Cylindrical:
              {
                equidistant_cylindrical_params.false_easting = value;
                break;
              }
            case Gnomonic:
              {
                gnomonic_params.false_easting = value;
                break;
              }
            case Lambert_Conformal_Conic_1:
              {
                lambert_1_params.false_easting = value;
                break;
              }
            case Lambert_Conformal_Conic_2:
              {
                lambert_2_params.false_easting = value;
                break;
              }
            case Mercator:
              {
                mercator_params.false_easting = value;
                break;
              }
            case Miller_Cylindrical:
              {
                miller_params.false_easting = value;
                break;
              }
            case Mollweide:
              {
                mollweide_params.false_easting = value;
                break;
              }
            case Neys:
              {
                neys_params.false_easting = value;
                break;
              }
            case Oblique_Mercator:
              {
                oblique_mercator_params.false_easting = value;
                break;
              }
            case Orthographic:
              {
                orthographic_params.false_easting = value;
                break;
              }
            case Polar_Stereo:
              {
                polar_stereo_params.false_easting = value;
                break;
              }
            case Polyconic:
              {
                polyconic_params.false_easting = value;
                break;
              }
            case Sinusoidal:
              {
                sinusoidal_params.false_easting = value;
                break;
              }
            case Stereographic:
              {
                stereographic_params.false_easting = value;
                break;
              }
            case Transverse_Cylindrical_Equal_Area:
              {
                transverse_cylindrical_equal_area_params.false_easting = value;
                break;
              }
            case Transverse_Mercator:
              {
                transverse_mercator_params.false_easting = value;
                break;
              }
            case Van_der_Grinten:
              {
                van_der_grinten_params.false_easting = value;
                break;
              }
            default:
              {
                return FIO_Error_Central_Meridian;
              }
            }
          else
            return FIO_Error_False_Easting;
        }
        else
          return FIO_Error_False_Easting;
        break;
      }
    case FHD_False_Northing:
      {
        double value = 0.0;
        long error_code = fscanf(file, "%s", buf);
        if (error_code)
        {
          length = strlen(buf)-1;
          if (!isdigit(buf[length]))
            buf[length] = 0;
          error_code = String_to_Double(buf,&value);
          if (!error_code)
            switch (projection_Type)
            {
            case Albers_Equal_Area_Conic:
              {
                albers_params.false_northing = value;
                break;
              }
            case Azimuthal_Equidistant:
              {
                azimuthal_equidistant_params.false_northing = value;
                break;
              }
            case Bonne:
              {
                bonne_params.false_northing = value;
                break;
              }
            case Cassini:
              {
                cassini_params.false_northing = value;
                break;
              }
            case Cylindrical_Equal_Area:
              {
                cylindrical_equal_area_params.false_northing = value;
                break;
              }
            case Eckert4:
              {
                eckert4_params.false_northing = value;
                break;
              }
            case Eckert6:
              {
                eckert6_params.false_northing = value;
                break;
              }
            case Equidistant_Cylindrical:
              {
                equidistant_cylindrical_params.false_northing = value;
                break;
              }
            case Gnomonic:
              {
                gnomonic_params.false_northing = value;
                break;
              }
            case Lambert_Conformal_Conic_1:
              {
                lambert_1_params.false_northing = value;
                break;
              }
            case Lambert_Conformal_Conic_2:
              {
                lambert_2_params.false_northing = value;
                break;
              }
            case Mercator:
              {
                mercator_params.false_northing = value;
                break;
              }
            case Miller_Cylindrical:
              {
                miller_params.false_northing = value;
                break;
              }
            case Mollweide:
              {
                mollweide_params.false_northing = value;
                break;
              }
            case Neys:
              {
                neys_params.false_northing = value;
                break;
              }
            case Oblique_Mercator:
              {
                oblique_mercator_params.false_northing = value;
                break;
              }
            case Orthographic:
              {
                orthographic_params.false_northing = value;
                break;
              }
            case Polar_Stereo:
              {
                polar_stereo_params.false_northing = value;
                break;
              }
            case Polyconic:
              {
                polyconic_params.false_northing = value;
                break;
              }
            case Sinusoidal:
              {
                sinusoidal_params.false_northing = value;
                break;
              }
            case Stereographic:
              {
                stereographic_params.false_northing = value;
                break;
              }
            case Transverse_Cylindrical_Equal_Area:
              {
                transverse_cylindrical_equal_area_params.false_northing = value;
                break;
              }
            case Transverse_Mercator:
              {
                transverse_mercator_params.false_northing = value;
                break;
              }
            case Van_der_Grinten:
              {
                van_der_grinten_params.false_northing = value;
                break;
              }
            default:
              {
                return FIO_Error_Central_Meridian;
              }
            }
          else
            return FIO_Error_False_Northing;
        }
        else
          return FIO_Error_False_Northing;
        break;
      }
    case FHD_Scale_Factor:
      {
        double value = 0.0;
        long error_code = fscanf(file, "%s", buf);
        if (error_code)
        {
          length = strlen(buf)-1;
          if (!isdigit(buf[length]))
            buf[length] = 0;
          error_code = String_to_Double(buf,&value);
          if (!error_code)
          {
            if ((0.3 <= value) &&(value <= 3.0))
              if (projection_Type == Lambert_Conformal_Conic_1)
                lambert_1_params.scale_factor = value;
              else if (projection_Type == Mercator)
                mercator_params.scale_factor = value;
              else if (projection_Type == Transverse_Cylindrical_Equal_Area)
                transverse_cylindrical_equal_area_params.scale_factor = value;
              else if (projection_Type == Transverse_Mercator)
                transverse_mercator_params.scale_factor = value;
              else if (projection_Type == Oblique_Mercator)
                oblique_mercator_params.scale_factor = value;
              else return FIO_Error_Scale_Factor;
            else
              return FIO_Error_Scale_Factor;
          }
          else
            return FIO_Error_Scale_Factor;
        }
        else
          return FIO_Error_Scale_Factor;
        break;
      }
    case FHD_Invalid_Header:
      {
        error_Code = FIO_Error_Label;
        header_Line = FHD_End_of_Header;
      }
    default:
      break;
    } /* switch */
    error_Code_File = Next_Header_Line(file, &header_Line);
    if (error_Code_File)
      return FIO_Error_Parsing_Header;
  } /* while */
  /* Set parameters */
  switch (projection_Type)
  {
  case Albers_Equal_Area_Conic:
    {
      Set_Albers_Equal_Area_Conic_Params(File, Input, albers_params);
      break;
    }
  case Azimuthal_Equidistant:
    {
      Set_Azimuthal_Equidistant_Params(File, Input, azimuthal_equidistant_params);
      break;
    }
  case Bonne:
    {
      Set_Bonne_Params(File, Input, bonne_params);
      break;
    }
  case Cassini:
    {
      Set_Cassini_Params(File, Input, cassini_params);
      break;
    }
  case Cylindrical_Equal_Area:
    {
      Set_Cylindrical_Equal_Area_Params(File, Input, cylindrical_equal_area_params);
      break;
    }
  case Eckert4:
    {
      Set_Eckert4_Params(File, Input, eckert4_params);
      break;
    }
  case Eckert6:
    {
      Set_Eckert6_Params(File, Input, eckert6_params);
      break;
    }
  case Equidistant_Cylindrical:
    {
      Set_Equidistant_Cylindrical_Params(File, Input, equidistant_cylindrical_params);
      break;
    }
  case Gnomonic:
    {
      Set_Gnomonic_Params(File, Input, gnomonic_params);
      break;
    }
  case Lambert_Conformal_Conic_1:
    {
      Set_Lambert_Conformal_Conic_1_Params(File, Input, lambert_1_params);
      break;
    }
  case Lambert_Conformal_Conic_2:
    {
      Set_Lambert_Conformal_Conic_2_Params(File, Input, lambert_2_params);
      break;
    }
  case Local_Cartesian:
    {
      Set_Local_Cartesian_Params(File, Input, local_cartesian_params);
      break;
    }
  case Mercator:
    {
      Set_Mercator_Params(File, Input, mercator_params);
      break;
    }
  case Miller_Cylindrical:
    {
      Set_Miller_Cylindrical_Params(File, Input, miller_params);
      break;
    }
  case Mollweide:
    {
      Set_Mollweide_Params(File, Input, mollweide_params);
      break;
    }
  case Neys:
    {
      Set_Neys_Params(File, Input, neys_params);
      break;
    }
  case Oblique_Mercator:
    {
      Set_Oblique_Mercator_Params(File, Input, oblique_mercator_params);
      break;
    }
  case Orthographic:
    {
      Set_Orthographic_Params(File, Input, orthographic_params);
      break;
    }
  case Polar_Stereo:
    {
      Set_Polar_Stereo_Params(File, Input, polar_stereo_params);
      break;
    }
  case Polyconic:
    {
      Set_Polyconic_Params(File, Input, polyconic_params);
      break;
    }
  case Sinusoidal:
    {
      Set_Sinusoidal_Params(File, Input, sinusoidal_params);
      break;
    }
  case Stereographic:
    {
      Set_Stereographic_Params(File, Input, stereographic_params);
      break;
    }
  case Transverse_Cylindrical_Equal_Area:
    {
      Set_Transverse_Cylindrical_Equal_Area_Params(File, Input, transverse_cylindrical_equal_area_params);
      break;
    }
  case Transverse_Mercator:
    {
      Set_Transverse_Mercator_Params(File, Input, transverse_mercator_params);
      break;
    }
  case Van_der_Grinten:
    {
      Set_Van_der_Grinten_Params(File, Input, van_der_grinten_params);
      break;
    }
  default:
    {
      break;
    }
  } /* switch */
  return error_Code;
}


FVC_Status Output_String(FILE *file, const char *sequence)
{/* BEGIN Output_String */
  FVC_Status error_Code = FVC_Success;
  if (fprintf(file, "%s", sequence) <= 0)
    error_Code = FVC_Error_Writing_String;
  return error_Code;
}/* END Output_String */


FVC_Status Output_Separator(FILE *file)
{
  static const char *separator = ", ";
  return Output_String(file, separator);
}


FVC_Status Output_Newline(FILE *file)
{
  static const char *newline_Sequence = "\n";
  return Output_String(file, newline_Sequence);
}


FIO_Status Write_Output_File_Header(FILE *file)
{
  char projection_String[50];
  char datum_Code[6];
  char ellipsoid_Code[3];
  char latitude_str[15];
  char longitude_str[15];
  char meter_str[15];
  Coordinate_Type projection_Type;
  long datum_Index = 0;
  if (Get_Coordinate_System(File, Output, &projection_Type))
    return FIO_Error_Getting_Engine;
  else
  {
    if (Projection_to_String(projection_Type, projection_String))
      return FIO_Error_Writing_Header;
    if ((projection_Type == BNG) ||
        (projection_Type == GARS) ||
        (projection_Type == Geodetic) ||
        (projection_Type == GEOREF) ||
        (projection_Type == Geocentric) ||
        (projection_Type == Local_Cartesian) ||
        (projection_Type == MGRS) ||
        (projection_Type == USNG) ||
        (projection_Type == UTM) ||
        (projection_Type == UPS))
      fprintf(file, "%s: ", coordinates_Header_String);
    else
      fprintf(file, "%s: ", projection_Header_String);
    fprintf(file, "%s\n", projection_String);
    if (Get_Datum(File, Output, &datum_Index))
      return FIO_Error_Getting_Engine;
    if (Get_Datum_Code(datum_Index, datum_Code))
      return FIO_Error_Writing_File;
    fprintf(file, "%s: ", datum_Header_String);
    fprintf(file, "%s\n", datum_Code);
    if (Get_Datum_Ellipsoid_Code(datum_Index, ellipsoid_Code))
      return FIO_Error_Writing_File;
    fprintf(file, "# ELLIPSOID: %s\n", ellipsoid_Code);
    switch (projection_Type)
    {
    case Geodetic:
      {
        Geodetic_Parameters params;
        Get_Geodetic_Params(File,Output,&params);
        if (params.height_type == No_Height)
          fprintf(file, "%s", no_Height_Header_String);
        else if (params.height_type == Ellipsoid_Height)
          fprintf(file, "%s", ellipsoid_Height_Header_String);
        else if (params.height_type == Geoid_or_MSL_Height)
          fprintf(file, "%s", msl_EGM96_15M_BL_Height_Header_String);
        else if (params.height_type == MSL_EGM96_VG_NS_Height)
          fprintf(file, "%s", msl_EGM96_VG_NS_Height_Header_String);
        else if (params.height_type == MSL_EGM84_10D_BL_Height)
          fprintf(file, "%s", msl_EGM84_10D_BL_Height_Header_String);
        else if (params.height_type == MSL_EGM84_10D_NS_Height)
          fprintf(file, "%s", msl_EGM84_10D_NS_Height_Header_String);
        fprintf(file,"\n");
        break;
      }
    case BNG:
    case GARS:
    case GEOREF:
    case Geocentric:
    case MGRS:
    case NZMG:
    case UPS:
    case USNG:
    case UTM:
      break;
    case Local_Cartesian:
      {
        Local_Cartesian_Parameters params;
        Get_Local_Cartesian_Params(File,Output,&params);
        fprintf(file, "%s: ", origin_Latitude_Header_String);
        Latitude_to_String((params.origin_latitude*180)/PI, latitude_str, use_NSEW_, use_Minutes_, use_Seconds_);
        fprintf(file, "%s", latitude_str);
        fprintf(file, "\n%s: ", origin_Longitude_Header_String);
        Longitude_to_String((params.origin_longitude*180)/PI, longitude_str, use_NSEW_, use_Minutes_, use_Seconds_);
        fprintf(file, "%s", longitude_str);
        fprintf(file, "\n%s: ", origin_Height_Header_String);
        Meter_to_String(params.origin_height,meter_str);
        fprintf(file, "%s", meter_str);
        fprintf(file, "\n%s: ", orientation_Header_String);
        Longitude_to_String((params.orientation*180)/PI, longitude_str, use_NSEW_, use_Minutes_, use_Seconds_);
        fprintf(file, "%s", longitude_str);
        fprintf(file, "\n");
        break;
      }
    case Albers_Equal_Area_Conic:
      {
        Albers_Equal_Area_Conic_Parameters params;
        Get_Albers_Equal_Area_Conic_Params(File,Output,&params);
        fprintf(file, "%s: ", central_Meridian_Header_String);
        Longitude_to_String((params.central_meridian*180)/PI, longitude_str, use_NSEW_, use_Minutes_, use_Seconds_);
        fprintf(file, "%s", longitude_str);
        fprintf(file, "\n%s: ", origin_Latitude_Header_String);
        Latitude_to_String((params.origin_latitude*180)/PI, latitude_str, use_NSEW_, use_Minutes_, use_Seconds_);
        fprintf(file, "%s", latitude_str);
        fprintf(file, "\n%s: ", standard_Parallel_One_Header_String);
        Latitude_to_String((params.std_parallel_1*180)/PI, latitude_str, use_NSEW_, use_Minutes_, use_Seconds_);
        fprintf(file, "%s", latitude_str);
        fprintf(file, "\n%s: ", standard_Parallel_Two_Header_String);
        Latitude_to_String((params.std_parallel_2*180)/PI, latitude_str, use_NSEW_, use_Minutes_, use_Seconds_);
        fprintf(file, "%s", latitude_str);
        fprintf(file, "\n%s: ", false_Easting_Header_String);
        Meter_to_String(params.false_easting,meter_str);
        fprintf(file, "%s", meter_str);
        fprintf(file, "\n%s: ", false_Northing_Header_String);
        Meter_to_String(params.false_northing,meter_str);
        fprintf(file, "%s", meter_str);
        fprintf(file, "\n");
        break;
      }
    case Lambert_Conformal_Conic_1:
      {
        Lambert_Conformal_Conic_1_Parameters params;
        Get_Lambert_Conformal_Conic_1_Params(File,Output,&params);
        fprintf(file, "%s: ", central_Meridian_Header_String);
        Longitude_to_String((params.central_meridian*180)/PI, longitude_str, use_NSEW_, use_Minutes_, use_Seconds_);
        fprintf(file, "%s", longitude_str);
        fprintf(file, "\n%s: ", origin_Latitude_Header_String);
        Latitude_to_String((params.origin_latitude*180)/PI, latitude_str, use_NSEW_, use_Minutes_, use_Seconds_);
        fprintf(file, "%s", latitude_str);
        fprintf(file, "\n%s: ", scale_Factor_Header_String);
        fprintf(file, "%.5f", params.scale_factor);
        fprintf(file, "\n%s: ", false_Easting_Header_String);
        Meter_to_String(params.false_easting,meter_str);
        fprintf(file, "%s", meter_str);
        fprintf(file, "\n%s: ", false_Northing_Header_String);
        Meter_to_String(params.false_northing,meter_str);
        fprintf(file, "%s", meter_str);
        fprintf(file, "\n");
        break;
      }
    case Lambert_Conformal_Conic_2:
      {
        Lambert_Conformal_Conic_2_Parameters params;
        Get_Lambert_Conformal_Conic_2_Params(File,Output,&params);
        fprintf(file, "%s: ", central_Meridian_Header_String);
        Longitude_to_String((params.central_meridian*180)/PI, longitude_str, use_NSEW_, use_Minutes_, use_Seconds_);
        fprintf(file, "%s", longitude_str);
        fprintf(file, "\n%s: ", origin_Latitude_Header_String);
        Latitude_to_String((params.origin_latitude*180)/PI, latitude_str, use_NSEW_, use_Minutes_, use_Seconds_);
        fprintf(file, "%s", latitude_str);
        fprintf(file, "\n%s: ", standard_Parallel_One_Header_String);
        Latitude_to_String((params.std_parallel_1*180)/PI, latitude_str, use_NSEW_, use_Minutes_, use_Seconds_);
        fprintf(file, "%s", latitude_str);
        fprintf(file, "\n%s: ", standard_Parallel_Two_Header_String);
        Latitude_to_String((params.std_parallel_2*180)/PI, latitude_str, use_NSEW_, use_Minutes_, use_Seconds_);
        fprintf(file, "%s", latitude_str);
        fprintf(file, "\n%s: ", false_Easting_Header_String);
        Meter_to_String(params.false_easting,meter_str);
        fprintf(file, "%s", meter_str);
        fprintf(file, "\n%s: ", false_Northing_Header_String);
        Meter_to_String(params.false_northing,meter_str);
        fprintf(file, "%s", meter_str);
        fprintf(file, "\n");
        break;
      }
    case Mercator:
      {
        Mercator_Parameters params;
        Convert(File);   /* this is to update mercator scale factor */
        Get_Mercator_Params(File,Output,&params);
        fprintf(file, "%s: ", central_Meridian_Header_String);
        Longitude_to_String((params.central_meridian*180)/PI, longitude_str, use_NSEW_, use_Minutes_, use_Seconds_);
        fprintf(file, "%s", longitude_str);
        fprintf(file, "\n%s: ", latitude_Of_True_Scale_Header_String);
        Latitude_to_String((params.latitude_of_true_scale*180)/PI, latitude_str, use_NSEW_, use_Minutes_, use_Seconds_);
        fprintf(file, "%s", latitude_str);
        fprintf(file, "\n%s: ", scale_Factor_Header_String);
        fprintf(file, "%.5f", params.scale_factor);
        fprintf(file, "\n%s: ", false_Easting_Header_String);
        Meter_to_String(params.false_easting,meter_str);
        fprintf(file, "%s", meter_str);
        fprintf(file, "\n%s: ", false_Northing_Header_String);
        Meter_to_String(params.false_northing,meter_str);
        fprintf(file, "%s", meter_str);
        fprintf(file, "\n");
        break;
      }
    case Transverse_Cylindrical_Equal_Area:
      {
        Transverse_Cylindrical_Equal_Area_Parameters params;
        Get_Transverse_Cylindrical_Equal_Area_Params(File,Output,&params);
        fprintf(file, "%s: ", central_Meridian_Header_String);
        Longitude_to_String((params.central_meridian*180)/PI, longitude_str, use_NSEW_, use_Minutes_, use_Seconds_);
        fprintf(file, "%s", longitude_str);
        fprintf(file, "\n%s: ", origin_Latitude_Header_String);
        Latitude_to_String((params.origin_latitude*180)/PI, latitude_str, use_NSEW_, use_Minutes_, use_Seconds_);
        fprintf(file, "%s", latitude_str);
        fprintf(file, "\n%s: ", scale_Factor_Header_String);
        fprintf(file, "%.5f", params.scale_factor);
        fprintf(file, "\n%s: ", false_Easting_Header_String);
        Meter_to_String(params.false_easting,meter_str);
        fprintf(file, "%s", meter_str);
        fprintf(file, "\n%s: ", false_Northing_Header_String);
        Meter_to_String(params.false_northing,meter_str);
        fprintf(file, "%s", meter_str);
        fprintf(file, "\n");
        break;
      }
    case Transverse_Mercator:
      {
        Transverse_Mercator_Parameters params;
        Get_Transverse_Mercator_Params(File,Output,&params);
        fprintf(file, "%s: ", central_Meridian_Header_String);
        Longitude_to_String((params.central_meridian*180)/PI, longitude_str, use_NSEW_, use_Minutes_, use_Seconds_);
        fprintf(file, "%s", longitude_str);
        fprintf(file, "\n%s: ", origin_Latitude_Header_String);
        Latitude_to_String((params.origin_latitude*180)/PI, latitude_str, use_NSEW_, use_Minutes_, use_Seconds_);
        fprintf(file, "%s", latitude_str);
        fprintf(file, "\n%s: ", scale_Factor_Header_String);
        fprintf(file, "%.5f", params.scale_factor);
        fprintf(file, "\n%s: ", false_Easting_Header_String);
        Meter_to_String(params.false_easting,meter_str);
        fprintf(file, "%s", meter_str);
        fprintf(file, "\n%s: ", false_Northing_Header_String);
        Meter_to_String(params.false_northing,meter_str);
        fprintf(file, "%s", meter_str);
        fprintf(file, "\n");
        break;
      }
    case Polar_Stereo:
      {
        Polar_Stereo_Parameters params;
        Get_Polar_Stereo_Params(File,Output,&params);
        fprintf(file, "%s: ", polarst_Longitude_Header_String);
        Longitude_to_String((params.longitude_down_from_pole*180)/PI, longitude_str, use_NSEW_, use_Minutes_, use_Seconds_);
        fprintf(file, "%s", longitude_str);
        fprintf(file, "\n%s: ", latitude_Of_True_Scale_Header_String);
        Latitude_to_String((params.latitude_of_true_scale*180)/PI, latitude_str, use_NSEW_, use_Minutes_, use_Seconds_);
        fprintf(file, "%s", latitude_str);
        fprintf(file, "\n%s: ", false_Easting_Header_String);
        Meter_to_String(params.false_easting,meter_str);
        fprintf(file, "%s", meter_str);
        fprintf(file, "\n%s: ", false_Northing_Header_String);
        Meter_to_String(params.false_northing,meter_str);
        fprintf(file, "%s", meter_str);
        fprintf(file, "\n");
        break;
      }
    case Azimuthal_Equidistant:
      {
        Azimuthal_Equidistant_Parameters params;
        Get_Azimuthal_Equidistant_Params(File,Output,&params);
        fprintf(file, "%s: ", central_Meridian_Header_String);
        Longitude_to_String((params.central_meridian*180)/PI, longitude_str, use_NSEW_, use_Minutes_, use_Seconds_);
        fprintf(file, "%s", longitude_str);
        fprintf(file, "\n%s: ", origin_Latitude_Header_String);
        Latitude_to_String((params.origin_latitude*180)/PI, latitude_str, use_NSEW_, use_Minutes_, use_Seconds_);
        fprintf(file, "%s", latitude_str);
        fprintf(file, "\n%s: ", false_Easting_Header_String);
        Meter_to_String(params.false_easting,meter_str);
        fprintf(file, "%s", meter_str);
        fprintf(file, "\n%s: ", false_Northing_Header_String);
        Meter_to_String(params.false_northing,meter_str);
        fprintf(file, "%s", meter_str);
        fprintf(file, "\n");
        break;
      }
    case Bonne:
      {
        Bonne_Parameters params;
        Get_Bonne_Params(File,Output,&params);
        fprintf(file, "%s: ", central_Meridian_Header_String);
        Longitude_to_String((params.central_meridian*180)/PI, longitude_str, use_NSEW_, use_Minutes_, use_Seconds_);
        fprintf(file, "%s", longitude_str);
        fprintf(file, "\n%s: ", origin_Latitude_Header_String);
        Latitude_to_String((params.origin_latitude*180)/PI, latitude_str, use_NSEW_, use_Minutes_, use_Seconds_);
        fprintf(file, "%s", latitude_str);
        fprintf(file, "\n%s: ", false_Easting_Header_String);
        Meter_to_String(params.false_easting,meter_str);
        fprintf(file, "%s", meter_str);
        fprintf(file, "\n%s: ", false_Northing_Header_String);
        Meter_to_String(params.false_northing,meter_str);
        fprintf(file, "%s", meter_str);
        fprintf(file, "\n");
        break;
      }
    case Cassini:
      {
        Cassini_Parameters params;
        Get_Cassini_Params(File,Output,&params);
        fprintf(file, "%s: ", central_Meridian_Header_String);
        Longitude_to_String((params.central_meridian*180)/PI, longitude_str, use_NSEW_, use_Minutes_, use_Seconds_);
        fprintf(file, "%s", longitude_str);
        fprintf(file, "\n%s: ", origin_Latitude_Header_String);
        Latitude_to_String((params.origin_latitude*180)/PI, latitude_str, use_NSEW_, use_Minutes_, use_Seconds_);
        fprintf(file, "%s", latitude_str);
        fprintf(file, "\n%s: ", false_Easting_Header_String);
        Meter_to_String(params.false_easting,meter_str);
        fprintf(file, "%s", meter_str);
        fprintf(file, "\n%s: ", false_Northing_Header_String);
        Meter_to_String(params.false_northing,meter_str);
        fprintf(file, "%s", meter_str);
        fprintf(file, "\n");
        break;
      }
    case Cylindrical_Equal_Area:
      {
        Cylindrical_Equal_Area_Parameters params;
        Get_Cylindrical_Equal_Area_Params(File,Output,&params);
        fprintf(file, "%s: ", central_Meridian_Header_String);
        Longitude_to_String((params.central_meridian*180)/PI, longitude_str, use_NSEW_, use_Minutes_, use_Seconds_);
        fprintf(file, "%s", longitude_str);
        fprintf(file, "\n%s: ", origin_Latitude_Header_String);
        Latitude_to_String((params.origin_latitude*180)/PI, latitude_str, use_NSEW_, use_Minutes_, use_Seconds_);
        fprintf(file, "%s", latitude_str);
        fprintf(file, "\n%s: ", false_Easting_Header_String);
        Meter_to_String(params.false_easting,meter_str);
        fprintf(file, "%s", meter_str);
        fprintf(file, "\n%s: ", false_Northing_Header_String);
        Meter_to_String(params.false_northing,meter_str);
        fprintf(file, "%s", meter_str);
        fprintf(file, "\n");
        break;
      }
    case Eckert4:
      {
        Eckert4_Parameters params;
        Get_Eckert4_Params(File,Output,&params);
        fprintf(file, "%s: ", central_Meridian_Header_String);
        Longitude_to_String((params.central_meridian*180)/PI, longitude_str, use_NSEW_, use_Minutes_, use_Seconds_);
        fprintf(file, "%s", longitude_str);
        fprintf(file, "\n%s: ", false_Easting_Header_String);
        Meter_to_String(params.false_easting,meter_str);
        fprintf(file, "%s", meter_str);
        fprintf(file, "\n%s: ", false_Northing_Header_String);
        Meter_to_String(params.false_northing,meter_str);
        fprintf(file, "%s", meter_str);
        fprintf(file, "\n");
        break;
      }
    case Eckert6:
      {
        Eckert6_Parameters params;
        Get_Eckert6_Params(File,Output,&params);
        fprintf(file, "%s: ", central_Meridian_Header_String);
        Longitude_to_String((params.central_meridian*180)/PI, longitude_str, use_NSEW_, use_Minutes_, use_Seconds_);
        fprintf(file, "%s", longitude_str);
        fprintf(file, "\n%s: ", false_Easting_Header_String);
        Meter_to_String(params.false_easting,meter_str);
        fprintf(file, "%s", meter_str);
        fprintf(file, "\n%s: ", false_Northing_Header_String);
        Meter_to_String(params.false_northing,meter_str);
        fprintf(file, "%s", meter_str);
        fprintf(file, "\n");
        break;
      }
    case Equidistant_Cylindrical:
      {
        Equidistant_Cylindrical_Parameters params;
        Get_Equidistant_Cylindrical_Params(File,Output,&params);
        fprintf(file, "%s: ", central_Meridian_Header_String);
        Longitude_to_String((params.central_meridian*180)/PI, longitude_str, use_NSEW_, use_Minutes_, use_Seconds_);
        fprintf(file, "%s", longitude_str);
        fprintf(file, "\n%s: ", standard_Parallel_Header_String);
        Latitude_to_String((params.std_parallel*180)/PI, latitude_str, use_NSEW_, use_Minutes_, use_Seconds_);
        fprintf(file, "%s", latitude_str);
        fprintf(file, "\n%s: ", false_Easting_Header_String);
        Meter_to_String(params.false_easting,meter_str);
        fprintf(file, "%s", meter_str);
        fprintf(file, "\n%s: ", false_Northing_Header_String);
        Meter_to_String(params.false_northing,meter_str);
        fprintf(file, "%s", meter_str);
        fprintf(file, "\n");
        break;
      }
    case Gnomonic:
      {
        Gnomonic_Parameters params;
        Get_Gnomonic_Params(File,Output,&params);
        fprintf(file, "%s: ", central_Meridian_Header_String);
        Longitude_to_String((params.central_meridian*180)/PI, longitude_str, use_NSEW_, use_Minutes_, use_Seconds_);
        fprintf(file, "%s", longitude_str);
        fprintf(file, "\n%s: ", origin_Latitude_Header_String);
        Latitude_to_String((params.origin_latitude*180)/PI, latitude_str, use_NSEW_, use_Minutes_, use_Seconds_);
        fprintf(file, "%s", latitude_str);
        fprintf(file, "\n%s: ", false_Easting_Header_String);
        Meter_to_String(params.false_easting,meter_str);
        fprintf(file, "%s", meter_str);
        fprintf(file, "\n%s: ", false_Northing_Header_String);
        Meter_to_String(params.false_northing,meter_str);
        fprintf(file, "%s", meter_str);
        fprintf(file, "\n");
        break;
      }
    case Miller_Cylindrical:
      {
        Miller_Cylindrical_Parameters params;
        Get_Miller_Cylindrical_Params(File,Output,&params);
        fprintf(file, "%s: ", central_Meridian_Header_String);
        Longitude_to_String((params.central_meridian*180)/PI, longitude_str, use_NSEW_, use_Minutes_, use_Seconds_);
        fprintf(file, "%s", longitude_str);
        fprintf(file, "\n%s: ", false_Easting_Header_String);
        Meter_to_String(params.false_easting,meter_str);
        fprintf(file, "%s", meter_str);
        fprintf(file, "\n%s: ", false_Northing_Header_String);
        Meter_to_String(params.false_northing,meter_str);
        fprintf(file, "%s", meter_str);
        fprintf(file, "\n");
        break;
      }
    case Mollweide:
      {
        Mollweide_Parameters params;
        Get_Mollweide_Params(File,Output,&params);
        fprintf(file, "%s: ", central_Meridian_Header_String);
        Longitude_to_String((params.central_meridian*180)/PI, longitude_str, use_NSEW_, use_Minutes_, use_Seconds_);
        fprintf(file, "%s", longitude_str);
        fprintf(file, "\n%s: ", false_Easting_Header_String);
        Meter_to_String(params.false_easting,meter_str);
        fprintf(file, "%s", meter_str);
        fprintf(file, "\n%s: ", false_Northing_Header_String);
        Meter_to_String(params.false_northing,meter_str);
        fprintf(file, "%s", meter_str);
        fprintf(file, "\n");
        break;
      }
    case Neys:
      {
        Neys_Parameters params;
        Get_Neys_Params(File,Output,&params);
        fprintf(file, "%s: ", central_Meridian_Header_String);
        Longitude_to_String((params.central_meridian*180)/PI, longitude_str, use_NSEW_, use_Minutes_, use_Seconds_);
        fprintf(file, "%s", longitude_str);
        fprintf(file, "\n%s: ", origin_Latitude_Header_String);
        Latitude_to_String((params.origin_latitude*180)/PI, latitude_str, use_NSEW_, use_Minutes_, use_Seconds_);
        fprintf(file, "%s", latitude_str);
        fprintf(file, "\n%s: ", standard_Parallel_One_Header_String);
        Latitude_to_String((params.std_parallel_1*180)/PI, latitude_str, use_NSEW_, use_Minutes_, use_Seconds_);
        fprintf(file, "%s", latitude_str);
        fprintf(file, "\n%s: ", false_Easting_Header_String);
        Meter_to_String(params.false_easting,meter_str);
        fprintf(file, "%s", meter_str);
        fprintf(file, "\n%s: ", false_Northing_Header_String);
        Meter_to_String(params.false_northing,meter_str);
        fprintf(file, "%s", meter_str);
        fprintf(file, "\n");
        break;
      }
    case Oblique_Mercator:
      {
        Oblique_Mercator_Parameters params;
        Get_Oblique_Mercator_Params(File,Output,&params);
        fprintf(file, "%s: ", origin_Latitude_Header_String);
        Latitude_to_String((params.origin_latitude*180)/PI, latitude_str, use_NSEW_, use_Minutes_, use_Seconds_);
        fprintf(file, "%s", latitude_str);
        fprintf(file, "\n%s: ", latitude_One_Header_String);
        Latitude_to_String((params.latitude_1*180)/PI, latitude_str, use_NSEW_, use_Minutes_, use_Seconds_);
        fprintf(file, "%s", latitude_str);
        fprintf(file, "\n%s: ", longitude_One_Header_String);
        Longitude_to_String((params.longitude_1*180)/PI, longitude_str, use_NSEW_, use_Minutes_, use_Seconds_);
        fprintf(file, "%s", longitude_str);
        fprintf(file, "\n%s: ", latitude_Two_Header_String);
        Latitude_to_String((params.latitude_2*180)/PI, latitude_str, use_NSEW_, use_Minutes_, use_Seconds_);
        fprintf(file, "%s", latitude_str);
        fprintf(file, "\n%s: ", longitude_Two_Header_String);
        Longitude_to_String((params.longitude_2*180)/PI, longitude_str, use_NSEW_, use_Minutes_, use_Seconds_);
        fprintf(file, "%s", longitude_str);
        fprintf(file, "\n%s: ", scale_Factor_Header_String);
        fprintf(file, "%.5f", params.scale_factor);
        fprintf(file, "\n%s: ", false_Easting_Header_String);
        Meter_to_String(params.false_easting,meter_str);
        fprintf(file, "%s", meter_str);
        fprintf(file, "\n%s: ", false_Northing_Header_String);
        Meter_to_String(params.false_northing,meter_str);
        fprintf(file, "%s", meter_str);
        fprintf(file, "\n");
        break;
      }
    case Orthographic:
      {
        Orthographic_Parameters params;
        Get_Orthographic_Params(File,Output,&params);
        fprintf(file, "%s: ", central_Meridian_Header_String);
        Longitude_to_String((params.central_meridian*180)/PI, longitude_str, use_NSEW_, use_Minutes_, use_Seconds_);
        fprintf(file, "%s", longitude_str);
        fprintf(file, "\n%s: ", origin_Latitude_Header_String);
        Latitude_to_String((params.origin_latitude*180)/PI, latitude_str, use_NSEW_, use_Minutes_, use_Seconds_);
        fprintf(file, "%s", latitude_str);
        fprintf(file, "\n%s: ", false_Easting_Header_String);
        Meter_to_String(params.false_easting,meter_str);
        fprintf(file, "%s", meter_str);
        fprintf(file, "\n%s: ", false_Northing_Header_String);
        Meter_to_String(params.false_northing,meter_str);
        fprintf(file, "%s", meter_str);
        fprintf(file, "\n");
        break;
      }
    case Polyconic:
      {
        Polyconic_Parameters params;
        Get_Polyconic_Params(File,Output,&params);
        fprintf(file, "%s: ", central_Meridian_Header_String);
        Longitude_to_String((params.central_meridian*180)/PI, longitude_str, use_NSEW_, use_Minutes_, use_Seconds_);
        fprintf(file, "%s", longitude_str);
        fprintf(file, "\n%s: ", origin_Latitude_Header_String);
        Latitude_to_String((params.origin_latitude*180)/PI, latitude_str, use_NSEW_, use_Minutes_, use_Seconds_);
        fprintf(file, "%s", latitude_str);
        fprintf(file, "\n%s: ", false_Easting_Header_String);
        Meter_to_String(params.false_easting,meter_str);
        fprintf(file, "%s", meter_str);
        fprintf(file, "\n%s: ", false_Northing_Header_String);
        Meter_to_String(params.false_northing,meter_str);
        fprintf(file, "%s", meter_str);
        fprintf(file, "\n");
        break;
      }
    case Sinusoidal:
      {
        Sinusoidal_Parameters params;
        Get_Sinusoidal_Params(File,Output,&params);
        fprintf(file, "%s: ", central_Meridian_Header_String);
        Longitude_to_String((params.central_meridian*180)/PI, longitude_str, use_NSEW_, use_Minutes_, use_Seconds_);
        fprintf(file, "%s", longitude_str);
        fprintf(file, "\n%s: ", false_Easting_Header_String);
        Meter_to_String(params.false_easting,meter_str);
        fprintf(file, "%s", meter_str);
        fprintf(file, "\n%s: ", false_Northing_Header_String);
        Meter_to_String(params.false_northing,meter_str);
        fprintf(file, "%s", meter_str);
        fprintf(file, "\n");
        break;
      }
    case Stereographic:
      {
        Stereographic_Parameters params;
        Get_Stereographic_Params(File,Output,&params);
        fprintf(file, "%s: ", central_Meridian_Header_String);
        Longitude_to_String((params.central_meridian*180)/PI, longitude_str, use_NSEW_, use_Minutes_, use_Seconds_);
        fprintf(file, "%s", longitude_str);
        fprintf(file, "\n%s: ", origin_Latitude_Header_String);
        Latitude_to_String((params.origin_latitude*180)/PI, latitude_str, use_NSEW_, use_Minutes_, use_Seconds_);
        fprintf(file, "%s", latitude_str);
        fprintf(file, "\n%s: ", false_Easting_Header_String);
        Meter_to_String(params.false_easting,meter_str);
        fprintf(file, "%s", meter_str);
        fprintf(file, "\n%s: ", false_Northing_Header_String);
        Meter_to_String(params.false_northing,meter_str);
        fprintf(file, "%s", meter_str);
        fprintf(file, "\n");
        break;
      }
    case Van_der_Grinten:
      {
        Van_der_Grinten_Parameters params;
        Get_Van_der_Grinten_Params(File,Output,&params);
        fprintf(file, "%s: ", central_Meridian_Header_String);
        Longitude_to_String((params.central_meridian*180)/PI, longitude_str, use_NSEW_, use_Minutes_, use_Seconds_);
        fprintf(file, "%s", longitude_str);
        fprintf(file, "\n%s: ", false_Easting_Header_String);
        Meter_to_String(params.false_easting,meter_str);
        fprintf(file, "%s", meter_str);
        fprintf(file, "\n%s: ", false_Northing_Header_String);
        Meter_to_String(params.false_northing,meter_str);
        fprintf(file, "%s", meter_str);
        fprintf(file, "\n");
        break;
      }
    }
    fprintf(file, "%s\n\n", end_Of_Header_String);
  }
  return FIO_Success;
}

long Read_Conversion_Errors(char* errors)
{
  char buf[256] = "";
  double ce90 = 1.0;
  double le90 = 1.0;
  double se90 = 1.0;
  int index = 0;

  sscanf(errors, "%[^:\t]", buf);
  if(strstr(errors, ce90_String))
  {
    index = strlen(buf);
    buf[0] = 0;
    sscanf(errors + index, "%[: ]", buf);
    index += strlen(buf);
    buf[0] = 0;
    sscanf(errors + index, "%[^,]", buf);
    if(strcmp(buf, "Unk") == 0)
      ce90 = -1.0;
    else
      ce90 = atof(buf);
    index += strlen(buf);
    buf[0] = 0;

    sscanf(errors + index, "%[, ]", buf);
    index += strlen(buf);
    buf[0] = 0;
    sscanf(errors + index, "%[^:\t]", buf);
    if(strstr(errors, le90_String))
    {
      index += strlen(buf);
      buf[0] = 0;
      sscanf(errors + index, "%[: ]", buf);
      index += strlen(buf);
      buf[0] = 0;
      sscanf(errors + index, "%[^,]", buf);
      if(strcmp(buf, "Unk") == 0)
        le90 = -1.0;
      else
        le90 = atof(buf);
      index += strlen(buf);
      buf[0] = 0;

      sscanf(errors + index, "%[, ]", buf);
      index += strlen(buf);
      buf[0] = 0;
      sscanf(errors + index, "%[^:\t]", buf);
      if(strstr(errors, se90_String))
      {
        index += strlen(buf);
        buf[0] = 0;
        sscanf(errors + index, "%[: ]", buf);
        index += strlen(buf);
        buf[0] = 0;
        sscanf(errors + index, "%[^,\n]", buf);
        if(strcmp(buf, "Unk") == 0)
          se90 = -1.0;
        else
          se90 = atof(buf);

        Set_Conversion_Errors(File, ce90, le90, se90);
        return 1;
      }
      else
        return 0;
    }
    else
      return 0;
  }
  else
    return 0;
}

void Write_Conversion_Errors(FILE *file,
                             double ce90,
                             double le90,
                             double se90)
{
  fprintf(file, " # CE90: ");
  if (ce90 == -1.0)
    fprintf(file,"Unk");
  else
    fprintf(file,"%1.0f",ce90);
  fprintf(file, ", LE90: ");
  if (le90 == -1.0)
    fprintf(file,"Unk");
  else
    fprintf(file,"%1.0f",le90);
  fprintf(file, ", SE90: ");
  if (se90 == -1.0)
    fprintf(file,"Unk");
  else
    fprintf(file,"%1.0f",se90);
}

/* Public functions */

FIO_Status Set_Input_Filename(const char *filename)
{
  FIO_Status error_Code = FIO_Success;
  FVC_Status error_Code_File = FVC_Success;
  error_Code_File = Open_File(Input, filename, &input_File);
  if (error_Code_File)
    error_Code = FIO_Error_Reading_File;
  else
    error_Code = Parse_Input_File_Header(input_File);
  Eat_Noise(input_File);
  return error_Code;
}


void Close_Input_File(void)
{
  if (input_File != NULL)
    Close_File(&input_File);
}


void Close_Output_File(void)
{
  if (output_File != NULL)
    Close_File(&output_File);
}


FIO_Status Set_Output_Filename(const char *filename)
{
  FIO_Status error_Code = FIO_Success;
  FVC_Status error_Code_File = FVC_Success;
  if (output_File != NULL)
    Close_Output_File();
  error_Code_File = Open_File(Output, filename, &output_File);
  if (!error_Code_File)
    Write_Output_File_Header(output_File);
  return error_Code;
}


FIO_Status Convert_File(long *Num_Errors, long *Num_Processed, long *Num_Warnings)
{
  FIO_Status error_Code = FIO_Success;
  long engine_error_Code;
  char next_Character;
  char Comment[256];
  Coordinate_Type input_Projection_Type, output_Projection_Type;
  char latitude_str[15];
  char longitude_str[15];
  char meter_str[15];

  char next_Letters[7];
  long position;
  long coordinate = 1;
  long conversion_errors = 0;

  *Num_Errors = 0;
  *Num_Processed = 0;
  *Num_Warnings = 0;
  Get_Coordinate_System(File, Input, &input_Projection_Type);
  Get_Coordinate_System(File, Output, &output_Projection_Type);

  while (!feof(input_File))
  {
    next_Character = (char)fgetc(input_File);
    ungetc(next_Character, input_File);
    if (next_Character == '#')
    {
      fgets(Comment, 255, input_File);
      Output_String(output_File,Comment);
      coordinate = 0;
    }
    else if (next_Character == '\n')
    {
      fgetc(input_File);
      Output_Newline(output_File);
      coordinate = 0;
    }
    else if (next_Character == '\r')
    {
      fgetc(input_File);
      coordinate = 0;
    }
    else if (next_Character == 'H')
    {
      position = ftell(input_File);
      fgets(next_Letters, 7, input_File);
      if (strcmp(next_Letters, "HEADER") == 0)
      {
        fgets(Comment, 255, input_File);
        fprintf(output_File,"%s\n", "# HEADER");
        Parse_Input_File_Header(input_File);
        Get_Coordinate_System(File, Input, &input_Projection_Type);
        coordinate = 0;
      }
      else
      {
        fseek(input_File, position, 0);
        fputs(next_Letters, input_File);
        coordinate = 1;
      }
    }
    else if (feof(input_File))
      coordinate = 0;
    else
      coordinate = 1;

    if (coordinate)
    {
      switch (input_Projection_Type)
      {
      case Geodetic:
        {
          Geodetic_Parameters params;
          Geodetic_Tuple coord;
          char buf[256] = "";
          long length;
          double temp_val = 0;

          Eat_Noise(input_File);
          if (!feof(input_File) && (fscanf(input_File, "%255[^,\t\n]", buf)))
          {
            error_Code = String_to_Latitude(buf, &temp_val);
            if(!error_Code)
            {
              coord.latitude =(temp_val*PI)/180;
              fscanf(input_File, "%[, \t]", buf);
              if (!feof(input_File) && (fscanf(input_File, "%255[^,\t\n#]", buf)))
              {
                length = strlen(buf)-1;
                if (!isdigit(buf[length]) && !isalpha(buf[length]))
                  buf[length] = 0;
                error_Code = String_to_Longitude(buf, &temp_val);
                if(!error_Code)
                {
                  coord.longitude =(temp_val*PI)/180;

                  /*only read height if not No Height*/
                  error_Code = Get_Geodetic_Params(File,Input,&params);
                  if(!error_Code)
                  {
                    if (params.height_type != No_Height)
                    {
                      fscanf(input_File, "%[, \t]", buf);
                      if (!feof(input_File) && (fscanf(input_File, "%[^, \t\n#]", buf)))
                      {
                        length = strlen(buf)-1;
                        if (!isdigit(buf[length]))
                          buf[length] = 0;
                        error_Code = String_to_Double(buf,&coord.height);
                      }
                      else
                        coord.height = 0.0;
                    }
                    else
                      coord.height = 0.0;

                    if(!error_Code)
                      error_Code = Set_Geodetic_Coordinates(File,Input,coord);
                  }
                }
              }
              else
                error_Code = FIO_Error;
            }
          }
          else
            error_Code = FIO_Error;
          break;
        }
      case GEOREF:
        {
          GEOREF_Tuple coord;
          char return_Parameter[32];
          int i = 0;

          Eat_Noise(input_File);
          if (!feof(input_File) && (fscanf(input_File, "%255[1234567890abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ]", return_Parameter)))
          {
            for (i = 0;(unsigned int)i < strlen(return_Parameter); i++)
              return_Parameter[i] = (char)toupper(return_Parameter[i]);
            strcpy(coord.string, return_Parameter);
            error_Code = Set_GEOREF_Coordinates(File,Input,coord);
          }
          else
            error_Code = FIO_Error;

          break;
        }
      case Geocentric:
        {
          char buf[256];
          Geocentric_Tuple coord;

          Eat_Noise(input_File);
          error_Code = Read_Coord(&coord.x, &coord.y);
          if(!error_Code)
          {
            fscanf(input_File, "%[, \t]", buf);
            if (!feof(input_File) && (fscanf(input_File, "%255[^, \t\n]", buf)))
            {
              error_Code = String_to_Double(buf,&coord.z);
              if(!error_Code)
                error_Code = Set_Geocentric_Coordinates(File,Input,coord);
            }
            else
              error_Code = FIO_Error;
          }
          break;
        }
      case Local_Cartesian:
        {
          char buf[256];
          Local_Cartesian_Tuple coord;

          Eat_Noise(input_File);
          error_Code = Read_Coord(&coord.x, &coord.y);
          if(!error_Code)
          {
            fscanf(input_File, "%[, \t]", buf);
            if (!feof(input_File) && (fscanf(input_File, "%255[^, \t\n]", buf)))
            {
              error_Code = String_to_Double(buf,&coord.z);
              if(!error_Code)
                error_Code = Set_Local_Cartesian_Coordinates(File,Input,coord);
            }
            else
              error_Code = FIO_Error;
          }
          break;
        }
      case MGRS:
        {
          MGRS_Tuple coord;
          char return_Parameter[32];
          int i = 0;

          Eat_Noise(input_File);
          if (!feof(input_File) && (fscanf(input_File, "%255[1234567890abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ]", return_Parameter)))
          {
            for (i = 0;(unsigned int)i < strlen(return_Parameter); i++)
              return_Parameter[i] = (char)toupper(return_Parameter[i]);
            strcpy(coord.string, return_Parameter);
            error_Code = Set_MGRS_Coordinates(File,Input,coord);
          }
          else
            error_Code = FIO_Error;

          break;
        }
      case UTM:
        {
          char buf[256];
          UTM_Tuple coord;
          double temp = 0;

          Eat_Noise(input_File);
          if (!feof(input_File) && (fscanf(input_File, "%255[^, \t\n]", buf)))
          {
            error_Code = String_to_Double(buf,&temp);
            if(!error_Code)
            {
              coord.zone = (long)temp;
              fscanf(input_File, "%[, \t]", buf);
              if (!feof(input_File) && (fscanf(input_File, "%255[^, \t\n]", &coord.hemisphere)))
              {
                coord.hemisphere = (char)toupper(coord.hemisphere);
                if ((coord.hemisphere != 'N') && (coord.hemisphere != 'S'))
                  error_Code = FIO_Error;
                else
                {
                  fscanf(input_File, "%[, \t]", buf);
                  error_Code = Read_Coord(&coord.easting, &coord.northing);
                  if(!error_Code)
                    error_Code = Set_UTM_Coordinates(File,Input,coord);
                }
              }
              else
                error_Code = FIO_Error;
            }
          }
          else
            error_Code = FIO_Error;
          break;
        }
      case UPS:
        {
          char buf[256];
          UPS_Tuple coord;

          Eat_Noise(input_File);
          if (!feof(input_File) && (fscanf(input_File, "%255[^, \t\n]", &coord.hemisphere)))
          {
            coord.hemisphere = (char)toupper(coord.hemisphere);
            if ((coord.hemisphere != 'N') && (coord.hemisphere != 'S'))
              error_Code = FIO_Error;
            else
            {
              fscanf(input_File, "%[, \t]", buf);
              error_Code = Read_Coord(&coord.easting, &coord.northing);
              if(!error_Code)
                error_Code = Set_UPS_Coordinates(File,Input,coord);
            }
          }
          else
            error_Code = FIO_Error;
          break;
        }
      case Albers_Equal_Area_Conic:
        {
          Albers_Equal_Area_Conic_Tuple coord;

          Eat_Noise(input_File);
          error_Code = Read_Coord(&coord.easting, &coord.northing);
          if(!error_Code)
            error_Code = Set_Albers_Equal_Area_Conic_Coordinates(File,Input,coord);
          break;
        }
      case Azimuthal_Equidistant:
        {
          Azimuthal_Equidistant_Tuple coord;

          Eat_Noise(input_File);
          error_Code = Read_Coord(&coord.easting, &coord.northing);
          if(!error_Code)
            error_Code = Set_Azimuthal_Equidistant_Coordinates(File,Input,coord);
          break;
        }
      case BNG:
        {
          BNG_Tuple coord;
          char return_Parameter[32];
          int i = 0;

          Eat_Noise(input_File);
          if (!feof(input_File) && (fscanf(input_File, "%255[ 1234567890abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ]", return_Parameter)))
          {
            for (i = 0;(unsigned int)i < strlen(return_Parameter); i++)
              return_Parameter[i] = (char)toupper(return_Parameter[i]);
            strcpy(coord.string, return_Parameter);
            error_Code = Set_BNG_Coordinates(File,Input,coord);
          }
          else
            error_Code = FIO_Error;

          break;
        }
      case Bonne:
        {
          Bonne_Tuple coord;

          Eat_Noise(input_File);
          error_Code = Read_Coord(&coord.easting, &coord.northing);
          if(!error_Code)
            error_Code = Set_Bonne_Coordinates(File,Input,coord);
          break;
        }
      case Cassini:
        {
          Cassini_Tuple coord;

          Eat_Noise(input_File);
          error_Code = Read_Coord(&coord.easting, &coord.northing);
          if(!error_Code)
            error_Code = Set_Cassini_Coordinates(File,Input,coord);
          break;
        }
      case Cylindrical_Equal_Area:
        {
          Cylindrical_Equal_Area_Tuple coord;

          Eat_Noise(input_File);
          error_Code = Read_Coord(&coord.easting, &coord.northing);
          if(!error_Code)
            error_Code = Set_Cylindrical_Equal_Area_Coordinates(File,Input,coord);
          break;
        }
      case Eckert4:
        {
          Eckert4_Tuple coord;

          Eat_Noise(input_File);
          error_Code = Read_Coord(&coord.easting, &coord.northing);
          if(!error_Code)
            error_Code = Set_Eckert4_Coordinates(File,Input,coord);
          break;
        }
      case Eckert6:
        {
          Eckert6_Tuple coord;

          Eat_Noise(input_File);
          error_Code = Read_Coord(&coord.easting, &coord.northing);
          if(!error_Code)
            error_Code = Set_Eckert6_Coordinates(File,Input,coord);
          break;
        }
      case Equidistant_Cylindrical:
        {
          Equidistant_Cylindrical_Tuple coord;

          Eat_Noise(input_File);
          error_Code = Read_Coord(&coord.easting, &coord.northing);
          if(!error_Code)
            error_Code = Set_Equidistant_Cylindrical_Coordinates(File,Input,coord);
          break;
        }
      case GARS:
        {
          GARS_Tuple coord;
          char return_Parameter[32];
          int i = 0;

          Eat_Noise(input_File);
          if (!feof(input_File) && (fscanf(input_File, "%255[1234567890abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ]", return_Parameter)))
          {
            for (i = 0;(unsigned int)i < strlen(return_Parameter); i++)
              return_Parameter[i] = (char)toupper(return_Parameter[i]);
            strcpy(coord.string, return_Parameter);
            error_Code = Set_GARS_Coordinates(File,Input,coord);
          }
          else
            error_Code = FIO_Error;

          break;
        }
      case Gnomonic:
        {
          Gnomonic_Tuple coord;

          Eat_Noise(input_File);
          error_Code = Read_Coord(&coord.easting, &coord.northing);
          if(!error_Code)
            error_Code = Set_Gnomonic_Coordinates(File,Input,coord);
          break;
        }
      case Lambert_Conformal_Conic_1:
        {
          Lambert_Conformal_Conic_1_Tuple coord;

          Eat_Noise(input_File);
          error_Code = Read_Coord(&coord.easting, &coord.northing);
          if(!error_Code)
            error_Code = Set_Lambert_Conformal_Conic_1_Coordinates(File,Input,coord);
          break;
        }
      case Lambert_Conformal_Conic_2:
        {
          Lambert_Conformal_Conic_2_Tuple coord;

          Eat_Noise(input_File);
          error_Code = Read_Coord(&coord.easting, &coord.northing);
          if(!error_Code)
            error_Code = Set_Lambert_Conformal_Conic_2_Coordinates(File,Input,coord);
          break;
        }
      case Mercator:
        {
          Mercator_Tuple coord;

          Eat_Noise(input_File);
          error_Code = Read_Coord(&coord.easting, &coord.northing);
          if(!error_Code)
            error_Code = Set_Mercator_Coordinates(File,Input,coord);
          break;
        }
      case Miller_Cylindrical:
        {
          Miller_Cylindrical_Tuple coord;

          Eat_Noise(input_File);
          error_Code = Read_Coord(&coord.easting, &coord.northing);
          if(!error_Code)
            error_Code = Set_Miller_Cylindrical_Coordinates(File,Input,coord);
          break;
        }
      case Mollweide:
        {
          Mollweide_Tuple coord;

          Eat_Noise(input_File);
          error_Code = Read_Coord(&coord.easting, &coord.northing);
          if(!error_Code)
            error_Code = Set_Mollweide_Coordinates(File,Input,coord);
          break;
        }
      case Neys:
        {
          Neys_Tuple coord;

          Eat_Noise(input_File);
          error_Code = Read_Coord(&coord.easting, &coord.northing);
          if(!error_Code)
            error_Code = Set_Neys_Coordinates(File,Input,coord);
          break;
        }
      case NZMG:
        {
          NZMG_Tuple coord;

          Eat_Noise(input_File);
          error_Code = Read_Coord(&coord.easting, &coord.northing);
          if(!error_Code)
            error_Code = Set_NZMG_Coordinates(File,Input,coord);
          break;
        }
      case Oblique_Mercator:
        {
          Oblique_Mercator_Tuple coord;

          Eat_Noise(input_File);
          error_Code = Read_Coord(&coord.easting, &coord.northing);
          if(!error_Code)
            error_Code = Set_Oblique_Mercator_Coordinates(File,Input,coord);
          break;
        }
      case Orthographic:
        {
          Orthographic_Tuple coord;

          Eat_Noise(input_File);
          error_Code = Read_Coord(&coord.easting, &coord.northing);
          if(!error_Code)
            error_Code = Set_Orthographic_Coordinates(File,Input,coord);
          break;
        }
      case Polar_Stereo:
        {
          Polar_Stereo_Tuple coord;

          Eat_Noise(input_File);
          error_Code = Read_Coord(&coord.easting, &coord.northing);
          if(!error_Code)
            error_Code = Set_Polar_Stereo_Coordinates(File,Input,coord);
          break;
        }
      case Polyconic:
        {
          Polyconic_Tuple coord;

          Eat_Noise(input_File);
          error_Code = Read_Coord(&coord.easting, &coord.northing);
          if(!error_Code)
            error_Code = Set_Polyconic_Coordinates(File,Input,coord);
          break;
        }
      case Sinusoidal:
        {
          Sinusoidal_Tuple coord;

          Eat_Noise(input_File);
          error_Code = Read_Coord(&coord.easting, &coord.northing);
          if(!error_Code)
            error_Code = Set_Sinusoidal_Coordinates(File,Input,coord);
          break;
        }
      case Stereographic:
        {
          Stereographic_Tuple coord;

          Eat_Noise(input_File);
          error_Code = Read_Coord(&coord.easting, &coord.northing);
          if(!error_Code)
            error_Code = Set_Stereographic_Coordinates(File,Input,coord);
          break;
        }
      case Transverse_Cylindrical_Equal_Area:
        {
          Transverse_Cylindrical_Equal_Area_Tuple coord;

          Eat_Noise(input_File);
          error_Code = Read_Coord(&coord.easting, &coord.northing);
          if(!error_Code)
            error_Code = Set_Transverse_Cylindrical_Equal_Area_Coordinates(File,Input,coord);
          break;
        }
      case Transverse_Mercator:
        {
          Transverse_Mercator_Tuple coord;

          Eat_Noise(input_File);
          error_Code = Read_Coord(&coord.easting, &coord.northing);
          if(!error_Code)
            error_Code = Set_Transverse_Mercator_Coordinates(File,Input,coord);
          break;
        }
      case USNG:
        {
          USNG_Tuple coord;
          char return_Parameter[32];
          int i = 0;

          Eat_Noise(input_File);
          if (!feof(input_File) && (fscanf(input_File, "%255[1234567890abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ]", return_Parameter)))
          {
            for (i = 0;(unsigned int)i < strlen(return_Parameter); i++)
              return_Parameter[i] = (char)toupper(return_Parameter[i]);
            strcpy(coord.string, return_Parameter);
            error_Code = Set_USNG_Coordinates(File,Input,coord);
          }
          else
            error_Code = FIO_Error;

          break;
        }
      case Van_der_Grinten:
        {
          Van_der_Grinten_Tuple coord;

          Eat_Noise(input_File);
          error_Code = Read_Coord(&coord.easting, &coord.northing);
          if(!error_Code)
            error_Code = Set_Van_der_Grinten_Coordinates(File,Input,coord);
          break;
        }
      } /*End of Switch? */

      *Num_Processed = *Num_Processed + 1;
      if (error_Code)
      {
        error_Code = FIO_Success;
        fgets(Comment, 255, input_File);
        Output_String(output_File,"# Error reading coordinates from input file");
        *Num_Errors = *Num_Errors + 1;
      }
      else
      {
        fgets(Comment, 255, input_File);
        if(strstr(Comment, ce90_String) && strstr(Comment, le90_String) && strstr(Comment, se90_String))
        {
          if(Read_Conversion_Errors(Comment))
            conversion_errors = 1;
        }
        engine_error_Code = Convert(File);
        if (engine_error_Code & ENGINE_INPUT_ERROR)
        {
          Get_Conversion_Status_String(File,Input," ",Comment);
          Output_String(output_File,"# Error: ");
          Output_String(output_File,Comment);
        }
        else if (engine_error_Code & ENGINE_INPUT_WARNING)
        {
          Get_Conversion_Status_String(File,Input," ",Comment);
          Output_String(output_File,"# Warning: ");
          Output_String(output_File,Comment);
          Output_Newline(output_File);
          *Num_Warnings = *Num_Warnings + 1;
        }
        if (engine_error_Code & ENGINE_OUTPUT_ERROR)
        {
          Get_Conversion_Status_String(File,Output," ",Comment);
          Output_String(output_File,"# Error: ");
          Output_String(output_File,Comment);
        }
        else if (engine_error_Code & ENGINE_OUTPUT_WARNING)
        {
          Get_Conversion_Status_String(File,Output," ",Comment);
          Output_String(output_File,"# Warning: ");
          Output_String(output_File,Comment);
          Output_Newline(output_File);
          *Num_Warnings = *Num_Warnings + 1;
        }
        if ((engine_error_Code & ENGINE_INPUT_ERROR) ||
            (engine_error_Code & ENGINE_OUTPUT_ERROR))
          *Num_Errors = *Num_Errors + 1;
        else
        {
          double ce90, le90, se90;
          switch (output_Projection_Type)
          {
          case Geodetic:
            {
              Geodetic_Parameters params;
              Geodetic_Tuple coord;
              Get_Geodetic_Coordinates(File,Output,&coord);
              Latitude_to_String((coord.latitude*180)/PI, latitude_str, use_NSEW_, use_Minutes_, use_Seconds_);
              fprintf(output_File, "%s", latitude_str);
              fprintf(output_File, ", ");
              Longitude_to_String((coord.longitude*180)/PI, longitude_str, use_NSEW_, use_Minutes_, use_Seconds_);
              fprintf(output_File, "%s", longitude_str);
              /*only output height if not No_Height*/
              Get_Geodetic_Params(File,Output,&params);
              if (params.height_type != No_Height)
              {
                fprintf(output_File, ", ");
                Meter_to_String(coord.height,meter_str);
                fprintf(output_File, "%s", meter_str);
              }
              break;
            }
          case GEOREF: {
              GEOREF_Tuple coord;
              Get_GEOREF_Coordinates(File,Output,&coord);
              if (fprintf(output_File, "%s", coord.string) <= 0)
                return FIO_Error_Writing_File;
              break;
            }
          case Geocentric: {
              Geocentric_Tuple coord;
              Get_Geocentric_Coordinates(File,Output,&coord);
              Write_Coord(coord.x, coord.y);
              fprintf(output_File, ", ");
              Meter_to_String(coord.z,meter_str);
              fprintf(output_File, "%s", meter_str);
              break;
            }
          case Local_Cartesian:  {
              Local_Cartesian_Tuple coord;
              Get_Local_Cartesian_Coordinates(File,Output,&coord);
              Write_Coord(coord.x, coord.y);
              fprintf(output_File, ", ");
              Meter_to_String(coord.z,meter_str);
              fprintf(output_File, "%s", meter_str);
              break;
            }
          case MGRS:  {
              MGRS_Tuple coord;
              Get_MGRS_Coordinates(File,Output,&coord );
              if (fprintf(output_File, "%s", coord.string) <= 0)
                return FIO_Error_Writing_File;
              break;
            }
          case UTM:  {
              UTM_Tuple coord;
              Get_UTM_Coordinates(File,Output,&coord);
              fprintf(output_File, "%d", coord.zone);
              fprintf(output_File, ", ");
              fprintf(output_File, "%c", coord.hemisphere);
              fprintf(output_File, ", ");
              Write_Coord(coord.easting, coord.northing);
              break;
            }
          case UPS:  {
              UPS_Tuple coord;
              Get_UPS_Coordinates(File,Output,&coord);
              fprintf(output_File, "%c", coord.hemisphere);
              fprintf(output_File, ", ");
              Write_Coord(coord.easting, coord.northing);
              break;
            }
          case Albers_Equal_Area_Conic: {
              Albers_Equal_Area_Conic_Tuple coord;
              Get_Albers_Equal_Area_Conic_Coordinates(File,Output,&coord);
              Write_Coord(coord.easting, coord.northing);
              break;
            }
          case Azimuthal_Equidistant: {
              Azimuthal_Equidistant_Tuple coord;
              Get_Azimuthal_Equidistant_Coordinates(File,Output,&coord);
              Write_Coord(coord.easting, coord.northing);
              break;
            }
          case BNG:  {
              BNG_Tuple coord;
              Get_BNG_Coordinates(File,Output,&coord );
              if (fprintf(output_File, "%s", coord.string) <= 0)
                return FIO_Error_Writing_File;
              break;
            }
          case Bonne: {
              Bonne_Tuple coord;
              Get_Bonne_Coordinates(File,Output,&coord);
              Write_Coord(coord.easting, coord.northing);
              break;
            }
          case Cassini:  {
              Cassini_Tuple coord;
              Get_Cassini_Coordinates(File,Output,&coord);
              Write_Coord(coord.easting, coord.northing);
              break;
            }
          case Cylindrical_Equal_Area:  {
              Cylindrical_Equal_Area_Tuple coord;
              Get_Cylindrical_Equal_Area_Coordinates(File,Output,&coord);
              Write_Coord(coord.easting, coord.northing);
              break;
            }
          case Eckert4:  {
              Eckert4_Tuple coord;
              Get_Eckert4_Coordinates(File,Output,&coord);
              Write_Coord(coord.easting, coord.northing);
              break;
            }
          case Eckert6:  {
              Eckert6_Tuple coord;
              Get_Eckert6_Coordinates(File,Output,&coord);
              Write_Coord(coord.easting, coord.northing);
              break;
            }
          case Equidistant_Cylindrical:  {
              Equidistant_Cylindrical_Tuple coord;
              Get_Equidistant_Cylindrical_Coordinates(File,Output,&coord);
              Write_Coord(coord.easting, coord.northing);
              break;
            }
          case GARS: {
              GARS_Tuple coord;
              Get_GARS_Coordinates(File,Output,&coord);
              if (fprintf(output_File, "%s", coord.string) <= 0)
                return FIO_Error_Writing_File;
              break;
            }
          case Gnomonic: {
              Gnomonic_Tuple coord;
              Get_Gnomonic_Coordinates(File,Output,&coord);
              Write_Coord(coord.easting, coord.northing);
              break;
            }
          case Lambert_Conformal_Conic_1:  {
              Lambert_Conformal_Conic_1_Tuple coord;
              Get_Lambert_Conformal_Conic_1_Coordinates(File,Output,&coord);
              Write_Coord(coord.easting, coord.northing);
              break;
            }
          case Lambert_Conformal_Conic_2:  {
              Lambert_Conformal_Conic_2_Tuple coord;
              Get_Lambert_Conformal_Conic_2_Coordinates(File,Output,&coord);
              Write_Coord(coord.easting, coord.northing);
              break;
            }
          case Mercator: {
              Mercator_Tuple coord;
              Get_Mercator_Coordinates(File,Output,&coord);
              Write_Coord(coord.easting, coord.northing);
              break;
            }
          case Miller_Cylindrical:  {
              Miller_Cylindrical_Tuple coord;
              Get_Miller_Cylindrical_Coordinates(File,Output,&coord);
              Write_Coord(coord.easting, coord.northing);
              break;
            }
          case Mollweide:  {
              Mollweide_Tuple coord;
              Get_Mollweide_Coordinates(File,Output,&coord);
              Write_Coord(coord.easting, coord.northing);
              break;
            }
          case Neys:  {
              Neys_Tuple coord;
              Get_Neys_Coordinates(File,Output,&coord);
              Meter_to_String(coord.easting,meter_str);
              Write_Coord(coord.easting, coord.northing);
              break;
            }
          case NZMG:  {
              NZMG_Tuple coord;
              Get_NZMG_Coordinates(File,Output,&coord);
              Write_Coord(coord.easting, coord.northing);
              break;
            }
          case Oblique_Mercator: {
              Oblique_Mercator_Tuple coord;
              Get_Oblique_Mercator_Coordinates(File,Output,&coord);
              Write_Coord(coord.easting, coord.northing);
              break;
            }
          case Orthographic:  {
              Orthographic_Tuple coord;
              Get_Orthographic_Coordinates(File,Output,&coord);
              Write_Coord(coord.easting, coord.northing);
              break;
            }
          case Polar_Stereo: {
              Polar_Stereo_Tuple coord;
              Get_Polar_Stereo_Coordinates(File,Output,&coord);
              Write_Coord(coord.easting, coord.northing);
              break;
            }
          case Polyconic: {
              Polyconic_Tuple coord;
              Get_Polyconic_Coordinates(File,Output,&coord);
              Write_Coord(coord.easting, coord.northing);
              break;
            }
          case Sinusoidal:  {
              Sinusoidal_Tuple coord;
              Get_Sinusoidal_Coordinates(File,Output,&coord);
              Write_Coord(coord.easting, coord.northing);
              break;
            }
          case Stereographic:  {
              Stereographic_Tuple coord;
              Get_Stereographic_Coordinates(File,Output,&coord);
              Write_Coord(coord.easting, coord.northing);
              break;
            }
          case Transverse_Cylindrical_Equal_Area:  {
              Transverse_Cylindrical_Equal_Area_Tuple coord;
              Get_Transverse_Cylindrical_Equal_Area_Coordinates(File,Output,&coord);
              Write_Coord(coord.easting, coord.northing);
              break;
            }
          case Transverse_Mercator:  {
              Transverse_Mercator_Tuple coord;
              Get_Transverse_Mercator_Coordinates(File,Output,&coord);
              Write_Coord(coord.easting, coord.northing);
              break;
            }
          case USNG:  {
              USNG_Tuple coord;
              Get_USNG_Coordinates(File,Output,&coord );
              if (fprintf(output_File, "%s", coord.string) <= 0)
                return FIO_Error_Writing_File;
              break;
            }
          case Van_der_Grinten:{
              Van_der_Grinten_Tuple coord;
              Get_Van_der_Grinten_Coordinates(File,Output,&coord);
              Write_Coord(coord.easting, coord.northing);
              break;
            }
          }/* End of Switches */
          if(conversion_errors)
          {
            Get_Conversion_Errors(File, &ce90, &le90, &se90);
            Write_Conversion_Errors(output_File, ce90, le90, se90);
            conversion_errors = 0;
          }
        }
      }
      Output_Newline(output_File);
    }
  }
  Close_Input_File();
  Close_Output_File();
  return FIO_Success;
}


void Get_File_Error_String(FIO_Status error, char *str)
{
  switch (error)
  {
  case FIO_Error_Reading_File:
    {
      strcpy(str,"Input file error opening file\n");
      break;
    }
  case FIO_Error_Projection:
    {
      strcpy(str,"Input file error in coordinate type\n");
      break;
    }
  case FIO_Error_Datum:
    {
      strcpy(str,"Input file error in datum\n");
      break;
    }
  case FIO_Error_Central_Meridian:
    {
      strcpy(str,"Input file error in Central Meridian\n");
      break;
    }
  case FIO_Error_Origin_Latitude:
    {
      strcpy(str,"Input file error in Origin Latitude\n");
      break;
    }
  case FIO_Error_Origin_Longitude:
    {
      strcpy(str,"Input file error in Origin Longitude\n");
      break;
    }
  case FIO_Error_Origin_Height:
    {
      strcpy(str,"Input file error in Origin Height\n");
      break;
    }
  case FIO_Error_Orientation:
    {
      strcpy(str,"Input file error in Orientation\n");
      break;
    }
  case FIO_Error_Latitude_One:
    {
      strcpy(str,"Input file error in Latitude 1\n");
      break;
    }
  case FIO_Error_Longitude_One:
    {
      strcpy(str,"Input file error in Longitude 1\n");
      break;
    }
  case FIO_Error_Latitude_Two:
    {
      strcpy(str,"Input file error in Latitude 2\n");
      break;
    }
  case FIO_Error_Longitude_Two:
    {
      strcpy(str,"Input file error in Longitude 2\n");
      break;
    }
  case FIO_Error_Standard_Parallel:
    {
      strcpy(str,"Input file error in Standard Parallel ");
      break;
    }
  case FIO_Error_Standard_Parallel_One:
    {
      strcpy(str,"Input file error in Standard Parallel 1\n");
      break;
    }
  case FIO_Error_Standard_Parallel_Two:
    {
      strcpy(str,"Input file error in Standard Parallel 2\n");
      break;
    }
  case FIO_Error_False_Easting:
    {
      strcpy(str,"Input file error in False Easting\n");
      break;
    }
  case FIO_Error_False_Northing:
    {
      strcpy(str,"Input file error in False Northing\n");
      break;
    }
  case FIO_Error_Scale_Factor:
    {
      strcpy(str,"Input file error in Scale Factor\n");
      break;
    }
  case FIO_Error_Hemisphere:
    {
      strcpy(str,"Input file error in Hemisphere\n");
      break;
    }
  case FIO_Error_Parsing_Header:
    {
      strcpy(str,"Input file header contains unknown keyword\n");
      break;
    }
  default:
    {
      strcpy(str,"Input file unknown error\n");
      break;
    }
  }
}


void Use_NSEW(boole value)
{
  use_NSEW_ = value;
}


boole Get_Use_NSEW()
{
  return (use_NSEW_);
}

void Use_Minutes(boole value)
{
  use_Minutes_ = value;
}


boole Get_Use_Minutes()
{
  return (use_Minutes_);
}


void Use_Seconds(boole value)
{
  use_Seconds_ = value;
}


boole Get_Use_Seconds()
{
  return (use_Seconds_);
}


FIO_Status Write_Example_Coord()
{
  Coordinate_Type output_Projection_Type;
  char latitude_str[15];
  char longitude_str[15];
  char meter_str[15];

  if (Get_Coordinate_System(File, Output, &output_Projection_Type))
     return FIO_Error_Getting_Engine;
  else
  {
    switch(output_Projection_Type)
    {
      case GARS:
        {
          fprintf(output_File, "361HN37");
          break;
        }
      case Geodetic:
        {
          Geodetic_Parameters params;
          Latitude_to_String(0, latitude_str, use_NSEW_, use_Minutes_, use_Seconds_);
          fprintf(output_File, "%s", latitude_str);
          fprintf(output_File, ", ");
          Longitude_to_String(0, longitude_str, use_NSEW_, use_Minutes_, use_Seconds_);
          fprintf(output_File, "%s", longitude_str);
          /*only output height if not No_Height*/
          Get_Geodetic_Params(File,Output,&params);
          if (params.height_type != No_Height)
          {
            fprintf(output_File, ", ");
            Meter_to_String(0,meter_str);
            fprintf(output_File, "%s", meter_str);
          }
          break;
        }
      case GEOREF:
        {
          fprintf(output_File, "NGAA0000000000");
          break;
        }
      case Geocentric:
        {
          Write_Coord(0, 0);
          fprintf(output_File, ", ");
          Meter_to_String(0,meter_str);
          fprintf(output_File, "%s", meter_str);
          break;
        }
      case Local_Cartesian:
        {
          Write_Coord(0, 0);
          fprintf(output_File, ", ");
          Meter_to_String(0,meter_str);
          fprintf(output_File, "%s", meter_str);
          break;
        }
      case MGRS:
        {
          fprintf(output_File, "31NEA0000000000");
          break;
        }
      case USNG:
        {
          fprintf(output_File, "31NEA0000000000");
          break;
        }
      case UTM:
        {
          UTM_Parameters params;
          Get_UTM_Params(File,Output,&params);
          if (params.override)
            fprintf(output_File, "%d", params.zone);
          else
            fprintf(output_File, "%d", 0);
          fprintf(output_File, ", ");
          fprintf(output_File, "N");
          fprintf(output_File, ", ");
          Write_Coord(500000, 0);
          break;
        }
      case UPS:
        {
          fprintf(output_File, "N");
          fprintf(output_File, ", ");
          Write_Coord(2000000, 2000000);
          break;
        }
      case BNG:
        {
          fprintf(output_File, "SV 0000000000");
          break;
        }
      case Albers_Equal_Area_Conic:
      case Azimuthal_Equidistant:
      case Bonne:
      case Cassini:
      case Cylindrical_Equal_Area:
      case Eckert4:
      case Eckert6:
      case Equidistant_Cylindrical:
      case Gnomonic:
      case Lambert_Conformal_Conic_1:
      case Lambert_Conformal_Conic_2:
      case Mercator:
      case Miller_Cylindrical:
      case Mollweide:
      case Neys:
      case Oblique_Mercator:
      case Orthographic:
      case Polar_Stereo:
      case Polyconic:
      case Sinusoidal:
      case Stereographic:
      case Transverse_Cylindrical_Equal_Area:
      case Transverse_Mercator:
      case Van_der_Grinten:
        {
          Write_Coord(0, 0);
          break;
      }
      case NZMG:
        {
          Write_Coord(2510000, 6023150);
          break;
        }
    }/* End of Switches */
  }

  return FIO_Success;

}
