#ifndef THREADS_H
  #define THREADS_H

/****************************************************************************/
/* RSC IDENTIFIER:  Threads
 *
 * ABSTRACT
 *
 *    The purpose of THREADS is to provide support for multithreading. 
 *    In order to lock a thread, a mutex can be created, locked and unlocked. 
 *
 * REUSE NOTES
 *
 *    Threads is intended for reuse by any application that requires multithreading
 *    support.
 *     
 *
 * LICENSES
 *
 *    None apply to this component.
 *
 * RESTRICTIONS
 *
 *    Threads has no restrictions.
 *
 * ENVIRONMENT
 *
 *    Threads was tested and certified in the following environments
 *
 *    1. Solaris 2.7
 *    2. Windows XP 
 *
 * MODIFICATIONS
 *
 *    Date              Description
 *    ----              -----------
 *    12-12-05          Original Code
 *
 */

/***************************************************************************/
/*
 *                               GLOBALS
 */

#define THREADS_NO_ERROR              0x0000
#define THREADS_CREATE_ERROR          0x0001
#define THREADS_LOCK_ERROR            0x0002
#define THREADS_UNLOCK_ERROR          0x0004
#define THREADS_DESTROY_ERROR         0x0008


/***************************************************************************/
/*
 *                          FUNCTION PROTOTYPES
 *                             for threads.c
 */

/* ensure proper linkage to c++ programs */
  #ifdef __cplusplus
extern "C" {
  #endif

#ifdef WIN32
#include <windows.h>

	typedef HANDLE Thread_Mutex;

	/* Create a mutex using the specified name */
	long Threads_Create_Mutex(char* name, Thread_Mutex* thread_mutex);
#else
#include <pthread.h>

	typedef pthread_mutex_t Thread_Mutex;

	/* Create a mutex */
	long Threads_Create_Mutex(Thread_Mutex* _thread_mutex);
#endif


/* Lock the mutex */
long Threads_Lock_Mutex(Thread_Mutex thread_mutex);


/* Unlock the mutex */
long Threads_Unlock_Mutex(Thread_Mutex thread_mutex);


/* Destroy the mutex */
long Threads_Destroy_Mutex(Thread_Mutex thread_mutex);



  #ifdef __cplusplus
}
  #endif

#endif /* THREADS_H */
