/*  cudaVecLib.h

  vector management functions.

  Contains the basic definitions for cudaVectorLib.

  Copyright (c) 1996-2017 by OptiCode - Dr. Martin Sander Software Dev.
  All Rights Reserved.
*/

#ifndef __CUDAVECLIB_H
#define __CUDAVECLIB_H
#include <VecLib.h>

#define __vcuf __cdecl  /* CUDA API works with __stdcall; here this would lead to problems with complex data types */
#if ((defined _MSC_VER) && (defined _OVCUDLL)) || (defined __BORLANDC__) // use OVCUDA DLL
	#define OVCUAPI __declspec(dllimport)
#else // use the static OVCUDA library in MSVC
	#define OVCUAPI
#endif
#if defined __cplusplus && defined _CMATH_CLASSDEFS && defined __BORLANDC__ && defined _WIN64
		// 64-bit C++ Builder functions with class complex<float> arguments
		// will be called via alias functions rather than imported from the DLL:
	#define OVCUAPI_ifNotBC64Class
#else
	#define OVCUAPI_ifNotBC64Class OVCUAPI
#endif
#if defined __cplusplus && defined _CMATH_CLASSDEFS
		// functions with class complex<float> or class complex<double> return values 
		// will be called via alias functions rather than imported from the DLL:
	#define OVCUAPI_ifNotClass
#else
	#define OVCUAPI_ifNotClass OVCUAPI
#endif


#ifdef __cplusplus
extern "C" {
#endif


void __vf V_setAutoCudaUse( int UseCuda );  /* UseCuda=0: no automatic CUDA use by OptiVec. Any other value for UseCuda: try to use CUDA where it seems reasonable. */ 

/*	Building upon nVidia's concept of CUDA streams, OptiVec manages execution concurrency 
	through workspaces of type V_CUDAWORKSPACE, incorporating a CUDA stream and associated
	buffers                                                                                  */

typedef struct V_CUDAWORKSPACE
{
	void      *cudaStream;  /* will be typecast into cudaStream_t where needed */
	biVector  deviceBuffer, pinnedBuffer_h, pinnedBuffer_d, deviceScalBuffer, pinnedScalBuffer_h, pinnedScalBuffer_d, V_intern;
}  V_CUDAWORKSPACE;

V_CUDAWORKSPACE __vf OVCUAPI V_createCudaWorkspace( void );
overror_t       __vf OVCUAPI V_destroyCudaWorkspace( V_CUDAWORKSPACE *wsp );
V_CUDAWORKSPACE __vf OVCUAPI V_getCudaWorkspace( void );
overror_t       __vf OVCUAPI V_setCudaWorkspace( V_CUDAWORKSPACE wsp );

overror_t __vf OVCUAPI V_initCuda( void );   /* must be called for each additional host thread (i.e., except the main thread) */
overror_t __vf OVCUAPI V_closeCuda( void );  /* must be called before closure of additional host threads */

/*	The following function synchronizes all CUDA threads within one stream
	and should be called before transfers between device and host memory: */
void __vcuf OVCUAPI cudaV_synchronize( void );

/* Retrieve last error occurred on the CUDA device: */
overror_t __vcuf OVCUAPI cudaV_getLastError( void );  /* returns error code */
void      __vcuf OVCUAPI cudaV_printLastErrorMsg( void );  /* prints message belonging to last occurred error; if no error: "Success" */

/** Allocation of memory is specific for the respective data type and
    is consequently included in cudaVFstd.h etc.                    */
/*    Freeing memory is the same for all data types: */

overror_t  __vcuf OVCUAPI   cudaV_free( void *X );     /* frees memory allocated by cudaV?_vector */
overror_t  __vcuf OVCUAPI   cudaV_pinnedFree( void *host_X ); /* frees pinned host memory allocated by cudaV?_pinnedVector. needs the host address(!) as parameter */
overror_t  __vcuf OVCUAPI   cudaV_freeAll( void );     /* frees all memory allocated by cudaV?_vector and by cudaV?_pinnedVector */
overror_t  __vcuf OVCUAPI   cudaV_pinnedFreeAll( void ); /* frees all pinned host memory allocated by cudaV?_pinnedVector */
overror_t  __vcuf OVCUAPI   cudaV_nfree( unsigned numfree,...); /* e.g., cudaV_nfree( 2, d_X, d_Y ); */
overror_t  __vcuf OVCUAPI   cudaV_pinnedNfree( unsigned numfree,...); /* frees several pinned host memory vectors, 
														  e.g., cudaV_pinnedNfree( 2, h_X, h_Y ); 
														  needs the host addresses(!) h_X and h_Y as parameters */

/********  user-accessible error handling functions ***************/

/*
#ifdef _WIN64
	void  __vcuf OVCUAPI   cudaV_checkBoundaries( void *X, ui size, int FlagRW, char *funcname, char *parname );
#else
	void  __vcuf OVCUAPI   cudaV_checkBoundaries( void *X, ui size, int FlagRW, char *funcname );
#endif
    X: vector of any type;  size: size in bytes;  FlagRW: 0=read, 1=write; 
	funcname: name of calling function;  parname (WIN64 only): name of offending vector */

/*	void  __vcuf OVCUAPI   cudaV_setBoundaryCheckWarn( int WarnLevel );
 WarnLevel=0: tolerate static and other non-OptiVec vectors; 1: don't tolerate, but warn */ 

#if defined __cplusplus
}   // end of "extern C",
#endif

#endif  /*  __CUDAVECLIB_H  */
