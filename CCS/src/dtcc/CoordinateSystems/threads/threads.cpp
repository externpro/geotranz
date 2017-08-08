// CLASSIFICATION: UNCLASSIFIED

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
 *                               INCLUDES
 */

#include "threads.h"


/***************************************************************************/
/*                              FUNCTIONS                                  */


	/* Create a mutex */
long Threads_Create_Mutex( Thread_Mutex* _thread_mutex )
{
#ifdef WIN32

		*_thread_mutex = CreateMutex( NULL, FALSE, NULL );
		if( *_thread_mutex )
			return THREADS_NO_ERROR;
		else
			return THREADS_CREATE_ERROR;

#else

		if( pthread_mutex_init( _thread_mutex, NULL ) )
			return THREADS_CREATE_ERROR;
		else
			return THREADS_NO_ERROR;

#endif
}


/* Lock the mutex */
long Threads_Lock_Mutex( Thread_Mutex thread_mutex )
{
#ifdef WIN32

	if( WaitForSingleObject( thread_mutex, INFINITE ) == WAIT_OBJECT_0 )
		return THREADS_NO_ERROR;
	else
		return THREADS_LOCK_ERROR;

#else
	if( pthread_mutex_lock( &thread_mutex ) )
		return THREADS_LOCK_ERROR;
	else
		return THREADS_NO_ERROR;
#endif
}


/* Unlock the mutex */
long Threads_Unlock_Mutex( Thread_Mutex thread_mutex )
{
#ifdef WIN32
	if( ReleaseMutex( thread_mutex ) )
		return THREADS_NO_ERROR;
	else
		return THREADS_UNLOCK_ERROR;
#else
	if( pthread_mutex_unlock( &thread_mutex ) )
		return THREADS_UNLOCK_ERROR;
	else
		return THREADS_NO_ERROR;
#endif
}


/* Destroy the mutex */
long Threads_Destroy_Mutex( Thread_Mutex thread_mutex )
{
#ifdef WIN32
	if( CloseHandle( thread_mutex ) )
		return THREADS_NO_ERROR;
	else
		return THREADS_DESTROY_ERROR;
#else
	if( pthread_mutex_destroy( &thread_mutex ) )
		return THREADS_DESTROY_ERROR;
	else
		return THREADS_NO_ERROR;
#endif
}


// CLASSIFICATION: UNCLASSIFIED
