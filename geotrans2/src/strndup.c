#include <stdlib.h>
#include <string.h>


#ifdef __cplusplus

char *allocate_String(long len)
{
   return new char[len];
}
      
#else

char *allocate_String(long len)
{
   return (char *)malloc(len * sizeof(char));
}

#endif                             
                             
char * strndup_(const char *src, long len)
{
   char *dst = "";

   long src_Length = (src ? strlen(src) : 0);
   long locallen = ((len && len <= src_Length) ? len : src_Length);

   if (locallen)
   {
      dst = allocate_String(locallen+1);
      if (dst)
      {
         strncpy(dst, src, locallen);
         dst[locallen] = '\0';
      }
   }

   return dst;
}

char * strdup_(const char *src)
{
  return strndup_(src, 0);
}
