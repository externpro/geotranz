#ifndef __compiler_hacks_h__
#define __compiler_hacks_h__

/* Hack to define a type bool */

#ifdef __cplusplus
extern "C" {
#endif

#if (!defined(__cplusplus) && !defined(BOOL_DEFINED))

  #include <stdbool.h>
  typedef bool boole;
  #define BOOL_DEFINED

#elif (defined (COMPILER_HAS_NO_BOOLEAN) && !defined (BOOL_DEFINED))

  typedef char boole;
  #define BOOL_DEFINED

#else
  #define boole bool

#endif

#ifdef __cplusplus
}
#endif


#ifdef __cplusplus

// Hack to define the new casts

#if defined (COMPILER_HAS_NO_CASTS) && !defined (CASTS_DEFINED)
template<class Target>
struct dynamic_cast
{
  Target subject;

  dynamic_cast(void *sub)
  : subject ((Target) sub) {}

  operator Target () {return subject;}
};

#define CASTS_DEFINED
#endif

#endif 


#endif
