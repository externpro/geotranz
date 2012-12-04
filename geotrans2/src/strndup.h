#ifndef __strndup_h__
#define __strndup_h__

#ifdef __cplusplus

char *strndup_(const char *src, long len);
char *strdup_(const char *src);

/* defined C++ symbols, C symbols to follow */

#else

char *strndup_(const char *src, long len);
char *strdup_(const char *src);

#endif
      
#endif
