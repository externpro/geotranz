#ifndef __fiomeths_h__
#define __fiomeths_h__

#include "comphack.h"                             

#ifdef __cplusplus
extern "C" {
#endif

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
 */


/***************************************************************************/
/*
 *                              DEFINES
 */
/* File processing error conditions */

  typedef enum File_Input_and_Output_Conversion_Status
  {
    /* Success */
    FIO_Success = 0,
    FIO_Error_Reading_File = -11,
    FIO_Error_Writing_File = -12,
    FIO_Error_Parsing_Header = -13,
    FIO_Error_Parsing_String = -14,
    FIO_Error_Parsing_File = -15,
    FIO_Error_Writing_Header = -16,
    FIO_EOFile = -17,
    FIO_Error_Latitude_of_True_Scale = -18,
    FIO_Error_Longitude_Down_from_Pole = -19,
    FIO_Error_Projection = -20,
    FIO_Error_Datum = -21,
    FIO_Error_Central_Meridian = -22,
    FIO_Error_Origin_Latitude = -23,
    FIO_Error_Origin_Longitude = -24,
    FIO_Error_Origin_Height = -25,
    FIO_Error_Orientation = -26,
    FIO_Error_Latitude_One = -27,
    FIO_Error_Longitude_One = -28,
    FIO_Error_Latitude_Two = -29,
    FIO_Error_Longitude_Two = -30,
    FIO_Error_Standard_Parallel = -31,
    FIO_Error_Standard_Parallel_One = -32,
    FIO_Error_Standard_Parallel_Two = -33,
    FIO_Error_False_Easting = -34,
    FIO_Error_False_Northing = -35,
    FIO_Error_Scale_Factor = -36,
    FIO_Error_Label = -37,
    FIO_Error_Hemisphere = -38,
    FIO_Error_Setting_Engine = -41,
    FIO_Error_Getting_Engine = -42,
    /* General error */
    FIO_Error = -1000
  } FIO_Status;

  /* Public functions */
  FIO_Status Set_Input_Filename(const char *filename);
  FIO_Status Set_Output_Filename(const char *filename);
  FIO_Status Convert_File(long *Num_Errors, long *Num_Processed, long *Num_Warnings);
  FIO_Status Write_Example_Coord();
  void Get_File_Error_String(FIO_Status error, char *str);
  void Use_NSEW(boole value);
  void Use_Minutes(boole value);
  void Use_Seconds(boole value);
  boole Get_Use_NSEW();
  boole Get_Use_Minutes();
  boole Get_Use_Seconds();
  void Close_Input_File(void);
  void Close_Output_File(void);

#ifdef __cplusplus
}
#endif

#endif
