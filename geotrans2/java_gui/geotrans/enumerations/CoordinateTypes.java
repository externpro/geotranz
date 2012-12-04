/*
 * CoordinateTypes.java
 *
 * Created on April 3, 2001, 4:18 PM
 */

package geotrans.enumerations;

/**
 *
 * @author  amyc
 * @version 
 */
public class CoordinateTypes extends Object {

    // Variable declaration for projection list.
    // The list index is based on order. 
    // These variables must be syncronized with any changes in the list in CoordinateConversionService.h.
    public final static String ALBERS_STR = "Albers Equal Area Conic";
    public final static String AZIMUTHAL_STR = "Azimuthal Equidistant (S)";        
    public final static String BONNE_STR = "Bonne";       
    public final static String BNG_STR = "British National Grid";        
    public final static String CASSINI_STR = "Cassini";       
    public final static String CYLEQA_STR = "Cylindrical Equal Area";       
    public final static String ECKERT4_STR = "Eckert IV (S)";       
    public final static String ECKERT6_STR = "Eckert VI (S)";       
    public final static String EQDCYL_STR = "Equidistant Cylindrical (S)";       
    public final static String GEOCENTRIC_STR = "Geocentric";       
    public final static String GEODETIC_STR = "Geodetic";        
    public final static String GEOREF_STR = "GEOREF";        
    public final static String GARS_STR = "Global Area Reference System (GARS)";        
    public final static String GNOMONIC_STR = "Gnomonic (S)";       
    public final static String LAMBERT_1_STR = "Lambert Conformal Conic (1 parallel)";       
    public final static String LAMBERT_2_STR = "Lambert Conformal Conic (2 parallel)";       
    public final static String LOCCART_STR = "Local Cartesian";        
    public final static String MERCATOR_STR = "Mercator";       
    public final static String MGRS_STR = "Military Grid Reference System (MGRS)";        
    public final static String MILLER_STR = "Miller Cylindrical (S)";       
    public final static String MOLLWEIDE_STR = "Mollweide (S)";       
    public final static String NZMG_STR = "New Zealand Map Grid";       
    public final static String NEYS_STR = "Ney's (Modified Lambert Conformal Conic)";       
    public final static String OMERC_STR = "Oblique Mercator";       
    public final static String ORTHOGRAPHIC_STR = "Orthographic (S)";    
    public final static String POLARSTEREO_STR = "Polar Stereographic";     
    public final static String POLYCONIC_STR = "Polyconic";       
    public final static String SINUSOIDAL_STR = "Sinusoidal";      
    public final static String STEREOGRAPHIC_STR = "Stereographic (S)";    
    public final static String TRCYLEQA_STR = "Transverse Cylindrical Equal Area";      
    public final static String TRANMERC_STR = "Transverse Mercator";       
    public final static String UPS_STR = "Universal Polar Stereographic (UPS)";        
    public final static String UTM_STR = "Universal Transverse Mercator (UTM)";        
    public final static String USNG_STR = "United States National Grid (USNG)";        
    public final static String GRINTEN_STR = "Van der Grinten";       
    public final static String F16GRS_STR = "F-16 Grid Reference System"; 
  
    public final static int GEODETIC  = 0;        
    public final static int GEOREF    = 1;        
    public final static int GARS      = 2;        
    public final static int GEOCENTRIC = 3;       
    public final static int LOCCART   = 4;        
    public final static int MGRS      = 5;        
    public final static int USNG      = 6;        
    public final static int UTM       = 7;        
    public final static int UPS       = 8;        
    public final static int ALBERS    = 9;        
    public final static int AZIMUTHAL = 10;        
    public final static int BNG       = 11;        
    public final static int BONNE     = 12;       
    public final static int CASSINI   = 13;       
    public final static int CYLEQA    = 14;       
    public final static int ECKERT4   = 15;       
    public final static int ECKERT6   = 16;       
    public final static int EQDCYL    = 17;       
    public final static int GNOMONIC  = 18;       
    public final static int LAMBERT_1 = 19;       
    public final static int LAMBERT_2 = 20;       
    public final static int MERCATOR  = 21;       
    public final static int MILLER    = 22;       
    public final static int MOLLWEIDE = 23;       
    public final static int NEYS      = 24;       
    public final static int NZMG      = 25;       
    public final static int OMERC     = 26;       
    public final static int ORTHOGRAPHIC = 27;    
    public final static int POLARSTEREO = 28;     
    public final static int POLYCONIC = 29;       
    public final static int SINUSOIDAL = 30;      
    public final static int STEREOGRAPHIC = 31;    
    public final static int TRCYLEQA  = 32;      
    public final static int TRANMERC  = 33;       
    public final static int GRINTEN   = 34;       
    public final static int F16GRS   = 35;       
      
    
    public static int index(java.lang.String name)
    {
      if(name.startsWith(GEODETIC_STR))
        return GEODETIC;
      else if(name.startsWith(GEOREF_STR))
        return GEOREF;
      else if(name.startsWith(GARS_STR))
        return GARS;
      else if(name.startsWith(GEOCENTRIC_STR))
        return GEOCENTRIC;
      else if(name.startsWith(LOCCART_STR))
        return LOCCART;
      else if(name.startsWith(MGRS_STR))
        return MGRS;
      else if(name.startsWith(USNG_STR))
        return USNG;
      else if(name.startsWith(UTM_STR))
        return UTM;
      else if(name.startsWith(UPS_STR))
        return UPS;
      else if(name.startsWith(ALBERS_STR))
        return ALBERS;
      else if(name.startsWith(AZIMUTHAL_STR))
        return AZIMUTHAL;
      else if(name.startsWith(BNG_STR))
        return BNG;
      else if(name.startsWith(BONNE_STR))
        return BONNE;
      else if(name.startsWith(CASSINI_STR))
        return CASSINI;
      else if(name.startsWith(CYLEQA_STR))
        return CYLEQA;
      else if(name.startsWith(ECKERT4_STR))
        return ECKERT4;
      else if(name.startsWith(ECKERT6_STR))
        return ECKERT6;
      else if(name.startsWith(EQDCYL_STR))
        return EQDCYL;
      else if(name.startsWith(GNOMONIC_STR))
        return GNOMONIC;
      else if(name.startsWith(LAMBERT_1_STR))
        return LAMBERT_1;
      else if(name.startsWith(LAMBERT_2_STR))
        return LAMBERT_2;
      else if(name.startsWith(MERCATOR_STR))
        return MERCATOR;
      else if(name.startsWith(MILLER_STR))
        return MILLER;
      else if(name.startsWith(MOLLWEIDE_STR))
        return MOLLWEIDE;
      else if(name.startsWith(NEYS_STR))
        return NEYS;
      else if(name.startsWith(NZMG_STR))
        return NZMG;
      else if(name.startsWith(OMERC_STR))
        return OMERC;
      else if(name.startsWith(ORTHOGRAPHIC_STR))
        return ORTHOGRAPHIC;
      else if(name.startsWith(POLARSTEREO_STR))
        return POLARSTEREO;
      else if(name.startsWith(POLYCONIC_STR))
        return POLYCONIC;
      else if(name.startsWith(SINUSOIDAL_STR))
        return SINUSOIDAL;
      else if(name.startsWith(STEREOGRAPHIC_STR))
        return STEREOGRAPHIC;
      else if(name.startsWith(TRCYLEQA_STR))
        return TRCYLEQA;
      else if(name.startsWith(TRANMERC_STR))
        return TRANMERC;
      else if(name.startsWith(GRINTEN_STR))     
        return GRINTEN;
      else if(name.startsWith(F16GRS_STR))
        return F16GRS;
      else
        return GEODETIC;
    }
    
    
    public static java.lang.String name(int index)
    {
      switch(index)
      {
        case ALBERS:  
          return ALBERS_STR;
        case AZIMUTHAL:        
          return AZIMUTHAL_STR;
        case BONNE:       
          return BONNE_STR;
        case BNG:       
          return BNG_STR;
        case CASSINI:     
          return CASSINI_STR;
        case CYLEQA:     
          return CYLEQA_STR;
        case ECKERT4:     
          return ECKERT4_STR;
        case ECKERT6:     
          return ECKERT6_STR;
        case EQDCYL:  
          return EQDCYL_STR;
        case GEOCENTRIC:      
           return GEOCENTRIC_STR;
        case GEODETIC:        
          return GEODETIC_STR;
        case GEOREF:       
           return GEOREF_STR;
        case GARS:       
          return GARS_STR;
        case GNOMONIC:     
          return GNOMONIC_STR;
        case LAMBERT_1:       
          return LAMBERT_1_STR;
        case LAMBERT_2:    
          return LAMBERT_2_STR;
        case LOCCART:       
          return LOCCART_STR;
        case MERCATOR:       
          return MERCATOR_STR;
        case MGRS:      
          return MGRS_STR;
        case MILLER:     
          return MILLER_STR;
        case MOLLWEIDE:      
          return MOLLWEIDE_STR;
        case NZMG:      
          return NZMG_STR;
        case NEYS:    
          return NEYS_STR;
        case OMERC:       
          return OMERC_STR;
        case ORTHOGRAPHIC:    
          return ORTHOGRAPHIC_STR;
        case POLARSTEREO:    
          return POLARSTEREO_STR;
        case POLYCONIC:      
          return POLYCONIC_STR;
        case SINUSOIDAL:    
          return SINUSOIDAL_STR;
        case STEREOGRAPHIC:  
          return STEREOGRAPHIC_STR;
        case TRCYLEQA:   
          return TRCYLEQA_STR;
        case TRANMERC:      
          return TRANMERC_STR;
        case UPS:       
          return UPS_STR;
        case UTM:        
          return UTM_STR;
        case USNG:    
          return USNG_STR;
        case GRINTEN:       
          return GRINTEN_STR;
        case F16GRS:
          return F16GRS_STR;
        default:
          return GEODETIC_STR;
      }
    }
}
