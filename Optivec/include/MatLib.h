/*  MatLib.h

  two-dimensional-matrix management functions.

  All matrices follow the C/C++ convention of row-wise storage.

  Copyright (c) 1996-2017 by OptiCode - Dr. Martin Sander Software Dev.
  All Rights Reserved.
*/

#ifndef __MATLIB_H
#define __MATLIB_H

#ifndef __VECLIB_H
    #include <VecLib.h>
#endif
#if defined( V_HUGE )
     #define   V_DATAPTR  huge
#else
     #define   V_DATAPTR
#endif

/**********************************************************************
 *   The following definitions ensure compatibility between           *
 *   dynamically allocated matrices (e.g., by MF_matrix) and          *
 *   static ones (declared, e.g., by float MA[20][20];                *
 *   for details see MFstd.h                                          */

typedef   char   V_DATAPTR  *           biPMatrix;
typedef   short  V_DATAPTR  *           siPMatrix;
typedef   int    V_DATAPTR  *           iPMatrix;
typedef   long   V_DATAPTR  *           liPMatrix;
typedef   quad   V_DATAPTR  *           qiPMatrix;
typedef   unsigned char  V_DATAPTR *    ubPMatrix;
typedef   unsigned short V_DATAPTR *    usPMatrix;
typedef   unsigned int   V_DATAPTR *    uPMatrix;
typedef   unsigned long  V_DATAPTR *    ulPMatrix;
#ifdef _WIN64
    typedef   uquad      V_DATAPTR *    uqPMatrix; 
#endif
typedef   ui        V_DATAPTR   *       uiPMatrix;   
typedef   float     V_DATAPTR   *       fPMatrix;
typedef   double    V_DATAPTR   *       dPMatrix;
typedef   extended  V_DATAPTR   *       ePMatrix;
typedef   fComplex  V_DATAPTR   *       cfPMatrix;
typedef   dComplex  V_DATAPTR   *       cdPMatrix;
typedef   eComplex  V_DATAPTR   *       cePMatrix;
typedef   fPolar    V_DATAPTR   *       pfPMatrix;
typedef   dPolar    V_DATAPTR   *       pdPMatrix;
typedef   ePolar    V_DATAPTR   *       pePMatrix;

typedef   biPMatrix  *        biMatrix;
typedef   ubPMatrix  *        ubMatrix;
typedef   siPMatrix  *        siMatrix;
typedef   usPMatrix  *        usMatrix;
typedef   iPMatrix   *        iMatrix;
typedef   uPMatrix   *        uMatrix;
typedef   liPMatrix  *        liMatrix;
typedef   ulPMatrix  *        ulMatrix;
typedef   qiPMatrix  *        qiMatrix;
#ifdef _WIN64
    typedef   uqPMatrix *     uqMatrix; 
#endif
typedef   uiPMatrix  *        uiMatrix;
typedef   fPMatrix   *        fMatrix;
typedef   dPMatrix   *        dMatrix;
typedef   ePMatrix   *        eMatrix;
typedef   cfPMatrix  *        cfMatrix;
typedef   cdPMatrix  *        cdMatrix;
typedef   cePMatrix  *        ceMatrix;
typedef   pfPMatrix  *        pfMatrix;
typedef   pdPMatrix  *        pdMatrix;
typedef   pePMatrix  *        peMatrix;

#ifdef __cplusplus
extern "C" {
#endif

/*************   Dynamic Generation of Matrices   ************************
          The allocation functions are defined in the individual
          include files,  <MFstd.h> etc.                                 */

 /* the following functions allocate pointer vectors and pointer matrices: */
#if defined __COMPACT__ || defined __LARGE__ || defined __HUGE__
    #define VUP_vector  VUL_vector  /* pointer to vector */
    #define MUP_matrix  MUL_matrix  /* pointer to matrix */
#elif defined  (_WIN64)
    #define VUP_vector  VUQ_vector
    #define MUP_matrix  MUQ_matrix
    #define VUP_vector_dbg  VUQ_vector_dbg
    #define MUP_matrix_dbg  MUQ_matrix_dbg
#else  /* WIN32 and non-segmented Win16 models */
    #define VUP_vector  VU_vector
    #define MUP_matrix  MU_matrix
    #define VUP_vector_dbg  VU_vector_dbg
    #define MUP_matrix_dbg  MU_matrix_dbg
#endif

/*   de-allocation of matrices (common to all data types): */

void    __vf  Mfree( void **M );
#define M_free(M)  Mfree( (void **)(M) )
void    __vf  M_nfree( unsigned n, ... );
#if defined (_MSC_VER) && defined (_DEBUG)
    void    __vf  Mfree_dbg( void **M );
    void    __vf  M_nfree_dbg( unsigned n, ... );
	#define M_free_dbg(M)  Mfree_dbg( (void **)(M) )
    #if defined (_INC_CRTDBG) && defined (_CRTDBG_MAP_ALLOC)
	    /* Automatic mapping for memory-leak detection by CRT debugging switched on? */
        #define Mfree  Mfree_dbg
        #define M_nfree M_nfree_dbg
    #endif
#else
    #define Mfree_dbg  Mfree
    #define M_nfree_dbg M_nfree
#endif

#ifdef __cplusplus
}  // end of extern "C"
#endif

#undef V_DATAPTR
#endif   /* __MATLIB_H  */
