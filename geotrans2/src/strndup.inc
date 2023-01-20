#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "strndup.h"

#ifdef __cplusplus
char *allocate_String(long len)
{
  return new char[len];
}
#else
char *allocate_String(long len)
{
  return (char *)malloc((size_t)len * sizeof(char));
}
#endif

char * strndup_(const char *src, long len)
{
  char *dst = "";
  long locallen = 0;
  long src_Length = (src ? strlen(src) : 0);

  if (locallen = ((len && len <= src_Length) ? len : src_Length))
  {
    if (dst = allocate_String(locallen+1))
    {
      strncpy(dst, src, (size_t)locallen);
      dst[locallen] = '\0';
    }
  }

  return dst;
}

char * strdup_(const char *src)
{
  return strndup_(src, 0);
}
