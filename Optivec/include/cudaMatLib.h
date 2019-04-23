/*  cudaMatLib.h

  two-dimensional-matrix management functions.

  All matrices follow the C/C++ convention of row-wise storage.

  Copyright (c) 1996-2017 by OptiCode - Dr. Martin Sander Software Dev.
  All Rights Reserved.
*/

#ifndef __CUDAMATLIB_H
#define __CUDAMATLIB_H

#ifndef __CUDAVECLIB_H
    #include <cudaVecLib.h>
#endif
#ifndef __MATLIB_H
    #include <MatLib.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif

/*************   Dynamic Generation of Matrices   ************************
          The allocation functions are defined in the individual
          include files,  <cudaMFstd.h> etc.                              */

 /* the following functions allocate pointer vectors and pointer matrices: */
#if defined  (_WIN64)
    #define cudaVUP_vector  cudaVUQ_vector
    #define cudaMUP_matrix  cudaMUQ_matrix
#else  /* WIN32  */
    #define cudaVUP_vector  cudaVU_vector
    #define cudaMUP_matrix  cudaMU_matrix
#endif

/*   de-allocation of matrices (common to all data types): */

overror_t   __vcuf OVCUAPI  cudaM_nfree( unsigned n, ... );
#define cudaM_free( M ) cudaV_free( (M) )
#define cudaMfree( M )  cudaV_free( (M) )

overror_t   __vcuf OVCUAPI  cudaM_pinnedNfree( unsigned n, ... );
overror_t   __vcuf OVCUAPI  cudaMpinnedFree( void **M );
#define cudaM_pinnedFree(M) cudaMpinnedFree( (void **)(M) )

#ifdef __cplusplus
}  // end of extern "C"
#endif

#endif   /* __CUDAMATLIB_H  */
