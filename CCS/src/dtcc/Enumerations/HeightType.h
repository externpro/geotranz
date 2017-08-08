// CLASSIFICATION: UNCLASSIFIED

/****************************************************************************
* FILE:           HeightType.h
*  
*           (C) Copyright 2010, BAE SYSTEMS
*                  ALL RIGHTS RESERVED
*           THIS NOTICE DOES NOT IMPLY PUBLICATION
*
*
* DESCRIPTION:  This file contains an enum with height types.
*
* LIMITATIONS/ASSUMPTIONS:
*
* MODIFICATION HISTORY:
*
* PROGRAMMER: 
*
* DATE        NAME              DR#               DESCRIPTION
* 
* 04/19/10    S Gillis          BAEts26542        Added EGM84ThirtyMinBiLinear          
* 
*****************************************************************************/

#ifndef HeightType_H
#define HeightType_H


namespace MSP
{
  namespace CCS
  {
    class HeightType
    {
    public:

      enum Enum
      {
        noHeight,
        ellipsoidHeight,
        EGM96FifteenMinBilinear,
        EGM96VariableNaturalSpline,
        EGM84TenDegBilinear,
        EGM84TenDegNaturalSpline,
        EGM84ThirtyMinBiLinear
      };
    };
  }
}
	
#endif 


// CLASSIFICATION: UNCLASSIFIED
