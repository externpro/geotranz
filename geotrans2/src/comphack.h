#ifndef __compiler_hacks_h__
#define __compiler_hacks_h__

/* Hack to define a type bool */

#ifdef __cplusplus
extern "C" {
#endif

#if ((defined (COMPILER_HAS_NO_BOOLEAN) || !defined __cplusplus) && !defined (BOOL_DEFINED))

  typedef char boole;

  static const boole true = 1;
  static const boole false = 0;

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
