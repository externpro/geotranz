// CLASSIFICATION: UNCLASSIFIED

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
        EGM84TenDegNaturalSpline
      };
    };
  }
}
	
#endif 


// CLASSIFICATION: UNCLASSIFIED
