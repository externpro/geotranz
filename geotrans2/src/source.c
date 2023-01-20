/***************************************************************************/
/* RSC IDENTIFIER: Source
 *
 * ABSTRACT
 *
 *
 * ERROR HANDLING
 *
 *    This component checks for input file errors and input parameter errors.
 *    If an invalid value is found, the error code is combined with the current
 *    error code using the bitwise or.  This combining allows multiple error
 *    codes to be returned. The possible error codes are:
 *
 *  SOURCE_NO_ERROR                  : No errors occurred in function
 *  SOURCE_INVALID_INDEX_ERROR       : Index out of valid range (less than one
 *                                      or more than Source_Count)
 *  SOURCE_INVALID_NAME_ERROR        : Source name not found
 *
 *
 * REUSE NOTES
 *
 *    Source is intended for reuse by any application that needs access to 
 *    accuracy sources.
 *
 *    
 * REFERENCES
 *
 *    Further information on Source can be found in the Reuse Manual.
 *
 *    Source originated from :  U.S. Army Topographic Engineering Center (USATEC)
 *                              Geospatial Information Division (GID)
 *                              7701 Telegraph Road
 *                              Alexandria, VA  22310-3864
 *
 * LICENSES
 *
 *    None apply to this component.
 *
 * RESTRICTIONS
 *
 *    Source has no restrictions.
 *
 * ENVIRONMENT
 *
 *    Source was tested and certified in the following environments:
 *
 *    1. Solaris 2.5 with GCC 2.8.1
 *    2. MS Windows 95 with MS Visual C++ 6
 *
 * MODIFICATIONS
 *
 *    Date              Description
 *    ----              -----------
 *    01/07/2008        Changed SE90 values,
 *                      Ned A. Ferris
 *                      (see extended explanation below)
 *
 * The modifications discussed below were made by Ned A. Ferris
 * on 7 January 2008.
 *
 * During Final Acceptance Testing (FAT) of the Coordinate
 * Conversion Service and Application (CCS and CCA),
 * 15 to 17 July 2007, Dr. Duane Brown (Navy) filed a 
 * discrepancy reported against the 90% Spherical Error values
 * for DTED Levels 1 and 2. This DR was GEOTRANS-0013 which cross 
 * references with the BAE discrepancy report BAEts21981.
 * 
 * Discussions with Dr. Brown and Dan Mullaney (NGA) regarding SE90 
 * values culminated at the MSP FAT DR TEM on 20 December 2007. 
 * At this technical exchange meeting, it was decided to replace 
 * the existing SE90 values with those calculated by an equation 
 * developed by Dr. Brown (see below). The formulas given below
 * were extracted from a PowerPoint Presentation sent to NGMS by
 * Dr. Brown; the actual derivations of the formulas were not documented.
 * 
 * Given CE90 and LE90 and the following definitions:
 * 
 * sqrt(x):  the square root of x.
 * 
 * sigma_xy: the standard deviation of the circular/ground components.
 * 
 * ratio:    the ratio of sigma_Z over sigma_xy
 * 
 * Let sigma_xy = sqrt(CE90^2/chi-square_distribution(0.1,2))
 *              = sqrt(CE90^2/4.60517612509304)
 * 
 * Let ratio    = (sqrt(LE90^2/chi-square_distribution(0.1,1)))/sigma_xy
 *              = (sqrt(LE90^2/2.70554058545338))/sigma_xy
 * 
 * If ratio < 5, then:
 * 
 * SE90 = 
 * (2.129292146             - 
 * (0.115864822 * ratio)    +
 * (0.6391671   * ratio^2)  -
 * (0.277130883 * ratio^3)  +
 * (0.148193487 * ratio^4)  -  
 * (0.037837525 * ratio^5)  +
 * (0.003262523 * ratio^6)) * sigma_xy
 * 
 * If ratio >= 5, then:
 * 
 * SE90 = 
 * (0.010469959           + 
 * (1.636566894*ratio)    +
 * (3.58376E-10*ratio^2)  -
 * (1.3613E-14*ratio^3)   +
 * (2.4342E-19*ratio^4)   -  
 * (2.04984E-24*ratio^5)  +
 * (6.55643E-30*ratio^6)) * sigma_xy
 * 
 * The 90% Spherical Error values in the Accuracy_Sources Source_Table
 * were recalculated using the above formula (except for CIB and DFAD,
 * see below). They were all rounded up to the nearest integer value.
 * The ratio values were all less than 5, so only the first of the above 
 * two formulas was used.
 * 
 * In addition, based on communications with Dan Mullaney on 
 * 27 December 2007, it was determined that:
 * 
 * 1. CIB has no vertical accuracy standard.
 * 
 * 2. DFAD is planimetric and doesn't have a vertical component.
 *    
 * SE90 is therefore not applicable for either CIB or DFAS. The SE90
 * values for all CIB and DFAD products were set to -1.
 *
 */


/***************************************************************************/
/*
 *                               INCLUDES
 */

#include <string.h>
#include "source.h"

/***************************************************************************/
/*
 *                               DEFINES
 */
#define SOURCE_NAME_LENGTH          50
#define NUMBER_SOURCES              19

/***************************************************************************/
/*
 *                          GLOBAL DECLARATIONS
 */

typedef struct Accuracy_Source_Value
{
  char Name[SOURCE_NAME_LENGTH];
  double CE;        /* circular error */
  double LE;        /* linear error */
  double SE;        /* spherical error */
} Accuracy_Sources; /* defines an accuracy source */



static const Accuracy_Sources Source_Table[NUMBER_SOURCES] = {{"Unknown", -1, -1, -1},
                                                              {"User defined (1 meter)", 1, 1, 2},
                                                              {"GPS PPS", 20, 20, 26},
                                                              {"GPS SPS", 20, 20, 26},
                                                              {"1:25,000 City Map", 50, 20, 52},
                                                              {"1:50,000 Topographic Line Map (TLM)", 50, 20, 52},
                                                              {"1:50,000 Combat Chart", 50, 20, 52},
                                                              {"1:100,000 Topographic Line Map (TLM)", 100, 20, 100},
                                                              {"1:250,000 Joint Operations Graphic (JOG)", 250, 100, 258},
                                                              {"1:500,000 Tactical Pilotage Chart (TPC)", 1000, 150, 993},
                                                              {"1:1,000,000 Operational Navigation Chart (ONC)", 2000, 650, 2031},
                                                              {"Digital Terrain Elevation Data (DTED) Level 1", 50, 30, 55},
                                                              {"Digital Terrain Elevation Data (DTED) Level 2", 23, 18, 27},
                                                              {"Digital Feature Analysis Data (DFAD) Level 1", 130, -1, -1},
                                                              {"Digital Feature Analysis Data (DFAD) Level 2", 130, -1, -1},
                                                              {"Controlled Image Base (CIB) [>10m GSD]", 25, -1, -1},
                                                              {"Vector Smart Map (VMAP) Level 1", 250, 100, 258},
                                                              {"Vector Smart Map (VMAP) Level 2 (1:100,000)", 100, 20, 100},
                                                              {"Vector Smart Map (VMAP) Level 2 (1:50,000)", 50, 20, 52}};



/***************************************************************************/
/*
 *                              FUNCTIONS     
 */
void Source_Count (long *Count)

{ /* Begin Source_Count */
  /*
   *  The function Source_Count returns the number of source accuracies 
   *
   *  Count                : number of accuracy sources      (output)
   */

    *Count = NUMBER_SOURCES;

} /* End of Source_Count */


long Source_Index( const char *Name,
                   long *Index )

{ /* Begin Source_Index */
  /*
   *  The function Source_Index returns the index of the source accuracy with the 
   *  specified name.
   *
   *  Name    : The source name being searched for.                   (input)
   *  Index   : The index of the accuracy source with the             (output)
   *              specified code.
   */
  char temp_name[SOURCE_NAME_LENGTH];
  long error_code = SOURCE_NO_ERROR;
  long length;
  long i = 0;

  *Index = 0;
  length = strlen(Name);
  if (length > (SOURCE_NAME_LENGTH-1))
    error_code |= SOURCE_INVALID_NAME_ERROR;
  else
  {
    strcpy(temp_name,Name);

    /* Convert to upper case */
/*    for (i=0;i<length;i++)
      temp_name[i] = (char)toupper(temp_name[i]);*/

    /* Strip blank spaces */
/*      while (pos < length)
    {
      if (isspace(temp_name[pos]))
      {
        for (i=pos;i<=length;i++)
          temp_name[i] = temp_name[i+1];
        length -= 1;
      }
      else
        pos += 1;
    }*/
    /* Search for code */
   /// i = 0;
    while (i < NUMBER_SOURCES && strcmp(temp_name, Source_Table[i].Name))
    {
      i++;
    }
    if (i == NUMBER_SOURCES || strcmp(temp_name, Source_Table[i].Name))
      error_code |= SOURCE_INVALID_NAME_ERROR;
    else
      *Index = i+1;
  }
  return (error_code);
} /* End Source_Index */


long Source_Name (const long Index,
                  char *Name)
{ /* Begin Source_Name */
  /*
   *  The function Source_Name returns the name of the source accuracy referenced by
   *  index.
   *
   *  Index   : The index of a given datum in the datum table.        (input)
   *  Name    : The accuracy source Name referenced by Index.         (output)
   */

  long error_code = SOURCE_NO_ERROR;

  if ((Index > 0) && (Index <= NUMBER_SOURCES))
    strcpy(Name, Source_Table[Index-1].Name);
  else
    error_code |= SOURCE_INVALID_INDEX_ERROR;
  return (error_code);
} /* End Source_Name */


long Source_Accuracy (const long Index, 
					            double *CE,
					            double *LE,
					            double *SE)
{ /* Begin Source_Accuracy */
/*
 *   The function Source_Accuracy returns the accuracy values (CE, LE, SE)
 *   for the source referenced by index.
 *
 *    Index      : The index of a given datum in the datum table   (input)
 *    CE         : Circular error                                  (output)
 *    LE         : Linear error                                    (output)
 *    SE         : Spherical error                                 (output)
 */

  long error_code = SOURCE_NO_ERROR;

  if (Index > 0 && Index <= NUMBER_SOURCES)
  {
    *CE = Source_Table[Index-1].CE;
    *LE = Source_Table[Index-1].LE;
    *SE = Source_Table[Index-1].SE;
  }
  else
  {
    error_code |= SOURCE_INVALID_INDEX_ERROR;
  }
  return (error_code);
} /* End Source_Accuracy */



