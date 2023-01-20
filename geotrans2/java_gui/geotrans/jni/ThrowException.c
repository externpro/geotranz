#include <jni.h>
#include "ThrowException.h"



void throwException(JNIEnv* env, const char *name, const char *msg)
{
    jclass cls = NULL;
    
   (*env)->ExceptionClear(env);
    cls = (*env)->FindClass(env, name);
    if (cls != NULL)
        (*env)->ThrowNew (env, cls, msg);
    (*env)->DeleteLocalRef(env, cls);
}




