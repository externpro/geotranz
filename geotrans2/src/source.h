#ifndef SOURCE_H
#define SOURCE_H

/***************************************************************************/
/* RSC IDENTIFIER: Source
 *
 * ABSTRACT
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
 *    Further information on Datum can be found in the Reuse Manual.
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
 */


/***************************************************************************/
/*
 *                              DEFINES
 */

#define SOURCE_NO_ERROR                          0x00000
#define SOURCE_INVALID_INDEX_ERROR               0x00001
#define SOURCE_INVALID_NAME_ERROR                0x00002


/***************************************************************************/
/*
 *                            FUNCTION PROTOTYPES
 */

/* ensure proper linkage to c++ programs */
#ifdef __cplusplus 
extern "C" {
#endif

void Source_Count (long *Count);

/*
 *  The function Source_Count returns the number of accuracy sources 
 *
 *  Count                : number of accuracy sources      (output)
 */


long Source_Index(const char *Name,
                  long *Index );

/*
 *  The function Source_Index returns the index of the accuracy source with the 
 *  specified name.
 *
 *  Name    : The source name being searched for.                   (input)
 *  Index   : The index of the accuracy source with the             (output)
 *              specified code.
 */


long Source_Name (const long Index,
                  char *Name);
/*
 *  The function Source_Name returns the name of the accuracy source referenced by
 *  index.
 *
 *  Index   : The index of a given datum in the datum table.        (input)
 *  Name    : The accuracy source Name referenced by Index.         (output)
 */


long Source_Accuracy (const long Index, 
					            double *CE,
					            double *LE,
					            double *SE);
/*
 *   The function Source_Accuracy returns the accuracy values (CE, LE, SE)
 *   for the source referenced by index.
 *
 *    Index      : The index of a given datum in the datum table   (input)
 *    CE         : Circular error                                  (output)
 *    LE         : Linear error                                    (output)
 *    SE         : Spherical error                                 (output)
 */


#ifdef __cplusplus 
}
#endif

#endif /* SOURCE_H */
