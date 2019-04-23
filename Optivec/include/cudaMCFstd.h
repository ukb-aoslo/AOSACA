/*  cudaMCFstd.h

  matrix management functions:
  manipulations on matrices of data type "fComplex"
  (float-precision complex numbers)

  This file declares the functions with the name variants 
	cudaMCF_func	(working on matrices in device memory, input type fMatrix, scalar parameters reside on host and are passed by value)
	cusdMCF_func	(as cudaMF_func except scalar parameters reside on device and are passed by address)
	cudaMCFfunc		(as cudaMCF_func, but input type cfPMatrix = cfVector = pointer to matrix element[0][0])
	cusdMCFfunc		(as cusdMCF_func, but input type cfPMatrix = cfVector = pointer to matrix element[0][0])
	MCFcu_func		(working on matrices in host memory, input type cfMatrix, scalar parameters on host and passed by value)
	MCFcufunc		(as MCFcu_func, but input type cfPMatrix = cfVector = pointer to matrix element[0][0])
  where func is the respective function.

  Copyright (c) 1996-2017 by OptiCode - Dr. Martin Sander Software Dev.
  All Rights Reserved.
*/

#if !defined( __CUDAMCFSTD_H )
#define __CUDAMCFSTD_H
#if !defined( __CUDAMATLIB_H )
   #include <cudaMatLib.h>
#endif
#if !defined( __CUDAVCFSTD_H )
   #include <cudaVCFstd.h>
#endif
#if !defined( __CUDAVCFMATH_H )
   #include <cudaVCFmath.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif


/**** Generation of matrices on device memory and on pinned host memory *******************/

cfMatrix  __vf cudaMCF_matrix( ui ht, ui len );   /* allocates a vector on device memory */
cfMatrix  __vf cudaMCF_matrix0( ui ht, ui len );
 /* The following functions allocate device-accessible, "pinned" memory on the host.
	This memory is mapped onto the device memory space. The resulting device address is returned.
	The matrix can be accessed either by its host address "hostPtr" e.g., MCF_equ1( hostPtr, ht, len );
	or by its device address , e.g., cudaMCF_equ1( devicePtr, ht, len );                             */
cfMatrix  __vf cudaMCF_pinnedMatrix(  cfMatrix *hostPtr, ui ht, ui len );
cfMatrix  __vf cudaMCF_pinnedMatrix0( cfMatrix *hostPtr, ui ht, ui len );

/*************************************************************************
 * Declarations of the functions written without underbar in the prefix: *
 *	cudaMCFfunc  (input type
				   cfPMatrix = cfVector = pointer to matrix element[0][0])
 *	cusdMCFfunc  (input type
				   cfPMatrix = cfVector = pointer to matrix element[0][0])
 *************************************************************************/


void    __vcuf OVCUAPI  cudaMCFsetElement( cfPMatrix X, ui ht, ui len, ui m, ui n, fComplex C );
void    __vcuf OVCUAPI  cusdMCFsetElement( cfPMatrix X, ui ht, ui len, ui m, ui n, fComplex *d_C );
void    __vcuf OVCUAPI  cudaMCFgetElement( fComplex *h_y, cfPMatrix X, ui ht, ui len, ui m, ui n );
void    __vcuf OVCUAPI  cusdMCFgetElement( fComplex *d_y, cfPMatrix X, ui ht, ui len, ui m, ui n );
fComplex * __vcuf OVCUAPI  cudaMCFPelement( cfPMatrix X, ui ht, ui len, ui m, ui n );
#if defined __cplusplus && defined _CMATH_CLASSDEFS
} // the following function cannot be extern "C", if fComplex is a class
#endif
fComplex   __vcuf OVCUAPI_ifNotClass  cudaMCFelement( cfPMatrix X, ui ht, ui len, ui m, ui n );
#if defined __cplusplus && defined _CMATH_CLASSDEFS
extern "C" {
#endif

#define cudaMCFequ0( MA, ht, len )    cudaVCF_equ0( MA, (ht)*(len) )
overror_t   __vcuf OVCUAPI  cudaMCFequ1( cfPMatrix MA, ui len );  /* identity matrix */
overror_t   __vcuf OVCUAPI  cudaMCFequm1( cfPMatrix MA, ui len );  /* neg. identity matrix */
overror_t   __vcuf OVCUAPI  cudaMCFouterprod( cfPMatrix MA, cfVector X,  cfVector Y, ui ht, ui len );

overror_t   __vcuf OVCUAPI  cudaMCFRow_equ0( cfPMatrix MA, ui ht, ui len, ui iRow );
overror_t   __vcuf OVCUAPI  cudaMCFCol_equ0( cfPMatrix MA, ui ht, ui len, ui iCol );
overror_t   __vcuf OVCUAPI  cudaMCFDia_equ0( cfPMatrix MA, ui len );

#if defined __cplusplus && defined _CMATH_CLASSDEFS && defined __BORLANDC__ && defined _WIN64
} // for C++Builder on Win64, the following functions cannot be extern "C", if fComplex is a class
#endif
overror_t   __vcuf OVCUAPI_ifNotBC64Class  cudaMCFRow_equC( cfPMatrix MA, ui ht, ui len, ui iRow, fComplex C );
overror_t   __vcuf OVCUAPI_ifNotBC64Class  cudaMCFCol_equC( cfPMatrix MA, ui ht, ui len, ui iCol, fComplex C );
overror_t   __vcuf OVCUAPI_ifNotBC64Class  cudaMCFDia_equC( cfPMatrix MA, ui len, fComplex C );
overror_t   __vcuf OVCUAPI_ifNotBC64Class  cusdMCFRow_equC( cfPMatrix MA, ui ht, ui len, ui iRow, fComplex *d_C );
overror_t   __vcuf OVCUAPI_ifNotBC64Class  cusdMCFCol_equC( cfPMatrix MA, ui ht, ui len, ui iCol, fComplex *d_C );
overror_t   __vcuf OVCUAPI_ifNotBC64Class  cusdMCFDia_equC( cfPMatrix MA, ui len, fComplex *d_C );
#if defined __cplusplus && defined _CMATH_CLASSDEFS && defined __BORLANDC__ && defined _WIN64
extern "C" {
#endif

overror_t   __vcuf OVCUAPI  cudaMCFRow_equV( cfPMatrix MA, ui ht, ui len, ui iRow, cfVector X );
overror_t   __vcuf OVCUAPI  cudaMCFCol_equV( cfPMatrix MA, ui ht, ui len, ui iCol, cfVector X );
overror_t   __vcuf OVCUAPI  cudaMCFDia_equV( cfPMatrix MA, ui len, cfVector X );

overror_t   __vcuf OVCUAPI  cudaMCFTrd_equM( cfPMatrix MA, cfPMatrix MTrd, ui len );
overror_t   __vcuf OVCUAPI  cudaMCFTrd_extract( cfPMatrix MTrd, cfPMatrix MA, ui len );

#define cudaMCFequM( MB, MA, ht, len )  cudaVCF_equV( MB, MA, (ht)*(len) )
#define cudaMCFequMhost( d_MB, h_MA, ht, len )  cudaVCF_equVhost( d_MB, h_MA, (ht)*(len) )
#define MCFequMdevice( h_MB, d_MA, ht, len )    VCF_equVdevice( h_MB, d_MA, (ht)*(len) )
#define cudaMCFneg( MB, MA, ht, len )   cudaVCF_neg( MB, MA, (ht)*(len) )
#define cudaMCFconj( MB, MA, ht, len )  cudaVCF_conj( MB, MA, (ht)*(len) )

overror_t   __vcuf OVCUAPI  cudaMCFUequL( cfPMatrix MA, ui len );
overror_t   __vcuf OVCUAPI  cudaMCFLequU( cfPMatrix MA, ui len );

/********  Extracting a submatrix and copying a submatrix back  *********/

overror_t  __vcuf OVCUAPI  cudaMCFsubmatrix( cfPMatrix MSub, ui subHt,  ui subLen,
                          cfPMatrix MSrce, ui srceHt,  ui srceLen,
                          ui firstRowInCol,  ui sampInCol,
                          ui firstColInRow,  ui sampInRow );

overror_t  __vcuf OVCUAPI  cudaMCFsubmatrix_equM( cfPMatrix MDest, ui destHt, ui destLen,
                               ui firstRowInCol,  ui sampInCol,
                               ui firstColInRow,  ui sampInRow,
                               cfPMatrix MSrce, ui srceHt, ui srceLen );

overror_t  __vcuf OVCUAPI  cudaMCFequMblock( cfPMatrix MSub, ui subHt,  ui subLen,
                          cfPMatrix MSrce, ui srceHt,  ui srceLen,
                          ui firstRowInCol,  ui firstColInRow );

overror_t  __vcuf OVCUAPI  cudaMCFblock_equM( cfPMatrix MDest, ui destHt, ui destLen,
                           ui firstRowInCol,  ui firstColInRow,
                           cfPMatrix MSrce, ui srceHt,  ui srceLen );

overror_t  __vcuf OVCUAPI  cudaMCFequMblockT( cfPMatrix MSub,  ui subHt,  ui subLen,
                          cfPMatrix MSrce,  ui srceHt,  ui srceLen,
                          ui firstRowInCol,  ui firstColInRow );

overror_t  __vcuf OVCUAPI  cudaMCFblock_equMT( cfPMatrix MDest,  ui destHt,  ui destLen,
                           ui firstRowInCol,  ui firstColInRow,
                           cfPMatrix MSrce,  ui srceHt,  ui srceLen );


/*****   Extracting a single row or a single column or the diagonal  *****
 *       and storing it into a vector                                    */

overror_t __vcuf OVCUAPI  cudaMCFRow_extract( cfVector Y, cfPMatrix MA, ui ht, ui len, ui iRow );
overror_t __vcuf OVCUAPI  cudaMCFCol_extract( cfVector Y, cfPMatrix MA, ui ht, ui len, ui iCol );
overror_t __vcuf OVCUAPI  cudaMCFDia_extract( cfVector Y, cfPMatrix MA, ui len );

/**********  Deleting or inserting a row or a column *****************/

overror_t __vcuf OVCUAPI  cudaMCFRow_delete( cfPMatrix MB, cfPMatrix MA, ui htA, ui lenA, ui iRow );
overror_t __vcuf OVCUAPI  cudaMCFCol_delete( cfPMatrix MB, cfPMatrix MA, ui htA, ui lenA, ui iCol );
overror_t __vcuf OVCUAPI  cudaMCFRow_insert( cfPMatrix MB, cfPMatrix MA, ui htB, ui lenB, ui iRow, cfVector X );
overror_t __vcuf OVCUAPI  cudaMCFCol_insert( cfPMatrix MB, cfPMatrix MA, ui htB, ui lenB, ui iCol, cfVector X );


/*****************    Basic arithmetic operations ***********************
     performed on one single row,  or one single column of any matrix,
     or on the diagonal of a square matrix                              */

overror_t   __vcuf OVCUAPI  cudaMCFRow_neg( cfPMatrix MX, ui ht, ui len, ui iRow );
overror_t   __vcuf OVCUAPI  cudaMCFCol_neg( cfPMatrix MX, ui ht, ui len, ui iCol );

overror_t   __vcuf OVCUAPI  cudaMCFRow_conj( cfPMatrix MX, ui ht, ui len, ui iRow );
overror_t   __vcuf OVCUAPI  cudaMCFCol_conj( cfPMatrix MX, ui ht, ui len, ui iCol );

#if defined __cplusplus && defined _CMATH_CLASSDEFS && defined __BORLANDC__ && defined _WIN64
} // for C++Builder on Win64, the following functions cannot be extern "C", if fComplex is a class
#endif
overror_t   __vcuf OVCUAPI_ifNotBC64Class  cudaMCFRow_addC( cfPMatrix MA, ui ht, ui len, ui iRow, fComplex C );
overror_t   __vcuf OVCUAPI_ifNotBC64Class  cudaMCFCol_addC( cfPMatrix MA, ui ht, ui len, ui iCol, fComplex C );
overror_t   __vcuf OVCUAPI_ifNotBC64Class  cudaMCFDia_addC( cfPMatrix MA, ui len, fComplex C );

overror_t   __vcuf OVCUAPI_ifNotBC64Class  cudaMCFRow_subC( cfPMatrix MA, ui ht, ui len, ui iRow, fComplex C );
overror_t   __vcuf OVCUAPI_ifNotBC64Class  cudaMCFCol_subC( cfPMatrix MA, ui ht, ui len, ui iCol, fComplex C );
overror_t   __vcuf OVCUAPI_ifNotBC64Class  cudaMCFDia_subC( cfPMatrix MA, ui len, fComplex C );

overror_t   __vcuf OVCUAPI_ifNotBC64Class  cudaMCFRow_subrC( cfPMatrix MA, ui ht, ui len, ui iRow, fComplex C );
overror_t   __vcuf OVCUAPI_ifNotBC64Class  cudaMCFCol_subrC( cfPMatrix MA, ui ht, ui len, ui iCol, fComplex C );
overror_t   __vcuf OVCUAPI_ifNotBC64Class  cudaMCFDia_subrC( cfPMatrix MA, ui len, fComplex C );

overror_t   __vcuf OVCUAPI_ifNotBC64Class  cudaMCFRow_mulC( cfPMatrix MA, ui ht, ui len, ui iRow, fComplex C );
overror_t   __vcuf OVCUAPI_ifNotBC64Class  cudaMCFCol_mulC( cfPMatrix MA, ui ht, ui len, ui iCol, fComplex C );
overror_t   __vcuf OVCUAPI_ifNotBC64Class  cudaMCFDia_mulC( cfPMatrix MA, ui len, fComplex C );

overror_t   __vcuf OVCUAPI_ifNotBC64Class  cudaMCFRow_divC( cfPMatrix MA, ui ht, ui len, ui iRow, fComplex C );
overror_t   __vcuf OVCUAPI_ifNotBC64Class  cudaMCFCol_divC( cfPMatrix MA, ui ht, ui len, ui iCol, fComplex C );
overror_t   __vcuf OVCUAPI_ifNotBC64Class  cudaMCFDia_divC( cfPMatrix MA, ui len, fComplex C );

overror_t   __vcuf OVCUAPI_ifNotBC64Class  cudaMCFRow_divrC( cfPMatrix MA, ui ht, ui len, ui iRow, fComplex C );
overror_t   __vcuf OVCUAPI_ifNotBC64Class  cudaMCFCol_divrC( cfPMatrix MA, ui ht, ui len, ui iCol, fComplex C );
overror_t   __vcuf OVCUAPI_ifNotBC64Class  cudaMCFDia_divrC( cfPMatrix MA, ui len, fComplex C );

#if defined __cplusplus && defined _CMATH_CLASSDEFS && defined __BORLANDC__ && defined _WIN64
extern "C" {
#endif
overror_t   __vcuf OVCUAPI  cudaMCFRow_addV( cfPMatrix MA, ui ht, ui len, ui iRow, cfVector X );
overror_t   __vcuf OVCUAPI  cudaMCFCol_addV( cfPMatrix MA, ui ht, ui len, ui iCol, cfVector X );
overror_t   __vcuf OVCUAPI  cudaMCFDia_addV( cfPMatrix MA, ui len, cfVector X );

overror_t   __vcuf OVCUAPI  cudaMCFRow_subV( cfPMatrix MA, ui ht, ui len, ui iRow, cfVector X );
overror_t   __vcuf OVCUAPI  cudaMCFCol_subV( cfPMatrix MA, ui ht, ui len, ui iCol, cfVector X );
overror_t   __vcuf OVCUAPI  cudaMCFDia_subV( cfPMatrix MA, ui len, cfVector X );

overror_t   __vcuf OVCUAPI  cudaMCFRow_subrV( cfPMatrix MA, ui ht, ui len, ui iRow, cfVector X );
overror_t   __vcuf OVCUAPI  cudaMCFCol_subrV( cfPMatrix MA, ui ht, ui len, ui iCol, cfVector X );
overror_t   __vcuf OVCUAPI  cudaMCFDia_subrV( cfPMatrix MA, ui len, cfVector X );

overror_t   __vcuf OVCUAPI  cudaMCFRow_mulV( cfPMatrix MA, ui ht, ui len, ui iRow, cfVector X );
overror_t   __vcuf OVCUAPI  cudaMCFCol_mulV( cfPMatrix MA, ui ht, ui len, ui iCol, cfVector X );
overror_t   __vcuf OVCUAPI  cudaMCFDia_mulV( cfPMatrix MA, ui len, cfVector X );

overror_t   __vcuf OVCUAPI  cudaMCFRow_divV( cfPMatrix MA, ui ht, ui len, ui iRow, cfVector X );
overror_t   __vcuf OVCUAPI  cudaMCFCol_divV( cfPMatrix MA, ui ht, ui len, ui iCol, cfVector X );
overror_t   __vcuf OVCUAPI  cudaMCFDia_divV( cfPMatrix MA, ui len, cfVector X );

overror_t   __vcuf OVCUAPI  cudaMCFRow_divrV( cfPMatrix MA, ui ht, ui len, ui iRow, cfVector X );
overror_t   __vcuf OVCUAPI  cudaMCFCol_divrV( cfPMatrix MA, ui ht, ui len, ui iCol, cfVector X );
overror_t   __vcuf OVCUAPI  cudaMCFDia_divrV( cfPMatrix MA, ui len, cfVector X );

overror_t   __vcuf OVCUAPI  cusdMCFRow_addC( cfPMatrix MA, ui ht, ui len, ui iRow, fComplex *d_C );
overror_t   __vcuf OVCUAPI  cusdMCFCol_addC( cfPMatrix MA, ui ht, ui len, ui iCol, fComplex *d_C );
overror_t   __vcuf OVCUAPI  cusdMCFDia_addC( cfPMatrix MA, ui len, fComplex *d_C );
overror_t   __vcuf OVCUAPI  cusdMCFRow_subC( cfPMatrix MA, ui ht, ui len, ui iRow, fComplex *d_C );
overror_t   __vcuf OVCUAPI  cusdMCFCol_subC( cfPMatrix MA, ui ht, ui len, ui iCol, fComplex *d_C );
overror_t   __vcuf OVCUAPI  cusdMCFDia_subC( cfPMatrix MA, ui len, fComplex *d_C );
overror_t   __vcuf OVCUAPI  cusdMCFRow_subrC( cfPMatrix MA, ui ht, ui len, ui iRow, fComplex *d_C );
overror_t   __vcuf OVCUAPI  cusdMCFCol_subrC( cfPMatrix MA, ui ht, ui len, ui iCol, fComplex *d_C );
overror_t   __vcuf OVCUAPI  cusdMCFDia_subrC( cfPMatrix MA, ui len, fComplex *d_C );
overror_t   __vcuf OVCUAPI  cusdMCFRow_mulC( cfPMatrix MA, ui ht, ui len, ui iRow, fComplex *d_C );
overror_t   __vcuf OVCUAPI  cusdMCFCol_mulC( cfPMatrix MA, ui ht, ui len, ui iCol, fComplex *d_C );
overror_t   __vcuf OVCUAPI  cusdMCFDia_mulC( cfPMatrix MA, ui len, fComplex *d_C );
overror_t   __vcuf OVCUAPI  cusdMCFRow_divC( cfPMatrix MA, ui ht, ui len, ui iRow, fComplex *d_C );
overror_t   __vcuf OVCUAPI  cusdMCFCol_divC( cfPMatrix MA, ui ht, ui len, ui iCol, fComplex *d_C );
overror_t   __vcuf OVCUAPI  cusdMCFDia_divC( cfPMatrix MA, ui len, fComplex *d_C );
overror_t   __vcuf OVCUAPI  cusdMCFRow_divrC( cfPMatrix MA, ui ht, ui len, ui iRow, fComplex *d_C );
overror_t   __vcuf OVCUAPI  cusdMCFCol_divrC( cfPMatrix MA, ui ht, ui len, ui iCol, fComplex *d_C );
overror_t   __vcuf OVCUAPI  cusdMCFDia_divrC( cfPMatrix MA, ui len, fComplex *d_C );


/******  One-dimensional vector operations **********************
         performed along all rows or all columns simultaneously,
         or along the diagonal of a square matrix                */

overror_t     __vcuf OVCUAPI  cudaMCFRows_absmax( fVector Y, cfPMatrix MA, ui ht, ui len );
overror_t     __vcuf OVCUAPI  cudaMCFCols_absmax( fVector Y, cfPMatrix MA, ui ht, ui len );
overror_t     __vcuf OVCUAPI  cudaMCFRows_absmin( fVector Y, cfPMatrix MA, ui ht, ui len );
overror_t     __vcuf OVCUAPI  cudaMCFCols_absmin( fVector Y, cfPMatrix MA, ui ht, ui len );

overror_t     __vcuf OVCUAPI  cudaMCFRows_maxReIm( cfVector Y, cfPMatrix MA, ui ht, ui len );
overror_t     __vcuf OVCUAPI  cudaMCFCols_maxReIm( cfVector Y, cfPMatrix MA, ui ht, ui len );
overror_t     __vcuf OVCUAPI  cudaMCFRows_minReIm( cfVector Y, cfPMatrix MA, ui ht, ui len );
overror_t     __vcuf OVCUAPI  cudaMCFCols_minReIm( cfVector Y, cfPMatrix MA, ui ht, ui len );

overror_t     __vcuf OVCUAPI  cudaMCFRows_absmaxReIm( cfVector Y, cfPMatrix MA, ui ht, ui len );
overror_t     __vcuf OVCUAPI  cudaMCFCols_absmaxReIm( cfVector Y, cfPMatrix MA, ui ht, ui len );
overror_t     __vcuf OVCUAPI  cudaMCFRows_absminReIm( cfVector Y, cfPMatrix MA, ui ht, ui len );
overror_t     __vcuf OVCUAPI  cudaMCFCols_absminReIm( cfVector Y, cfPMatrix MA, ui ht, ui len );

overror_t     __vcuf OVCUAPI  cudaMCFRows_cabsmax( cfVector Y, cfPMatrix MA, ui ht, ui len );
overror_t     __vcuf OVCUAPI  cudaMCFCols_cabsmax( cfVector Y, cfPMatrix MA, ui ht, ui len );
overror_t     __vcuf OVCUAPI  cudaMCFRows_cabsmin( cfVector Y, cfPMatrix MA, ui ht, ui len );
overror_t     __vcuf OVCUAPI  cudaMCFCols_cabsmin( cfVector Y, cfPMatrix MA, ui ht, ui len );

overror_t     __vcuf OVCUAPI  cudaMCFRows_sabsmax( cfVector Y, cfPMatrix MA, ui ht, ui len );
overror_t     __vcuf OVCUAPI  cudaMCFCols_sabsmax( cfVector Y, cfPMatrix MA, ui ht, ui len );
overror_t     __vcuf OVCUAPI  cudaMCFRows_sabsmin( cfVector Y, cfPMatrix MA, ui ht, ui len );
overror_t     __vcuf OVCUAPI  cudaMCFCols_sabsmin( cfVector Y, cfPMatrix MA, ui ht, ui len );

overror_t     __vcuf OVCUAPI  cudaMCFRows_sum( cfVector Y, cfPMatrix MA, ui ht, ui len );
overror_t     __vcuf OVCUAPI  cudaMCFCols_sum( cfVector Y, cfPMatrix MA, ui ht, ui len );
overror_t     __vcuf OVCUAPI  cudaMCFRows_prod(cfVector Y, cfPMatrix MA, ui ht, ui len );
overror_t     __vcuf OVCUAPI  cudaMCFCols_prod(cfVector Y, cfPMatrix MA, ui ht, ui len );

overror_t     __vcuf OVCUAPI  cudaMCFDia_absmax(  float *h_RetVal, cfPMatrix MA, ui len );
overror_t     __vcuf OVCUAPI  cudaMCFDia_absmin(  float *h_RetVal, cfPMatrix MA, ui len );
overror_t     __vcuf OVCUAPI  cudaMCFDia_maxReIm(  fComplex *h_RetVal, cfPMatrix MA, ui len );
overror_t     __vcuf OVCUAPI  cudaMCFDia_minReIm(  fComplex *h_RetVal, cfPMatrix MA, ui len );
overror_t     __vcuf OVCUAPI  cudaMCFDia_absmaxReIm(  fComplex *h_RetVal, cfPMatrix MA, ui len );
overror_t     __vcuf OVCUAPI  cudaMCFDia_absminReIm(  fComplex *h_RetVal, cfPMatrix MA, ui len );
overror_t     __vcuf OVCUAPI  cudaMCFDia_cabsmax(  fComplex *h_RetVal, cfPMatrix MA, ui len );
overror_t     __vcuf OVCUAPI  cudaMCFDia_cabsmin(  fComplex *h_RetVal, cfPMatrix MA, ui len );
overror_t     __vcuf OVCUAPI  cudaMCFDia_sabsmax(  fComplex *h_RetVal, cfPMatrix MA, ui len );
overror_t     __vcuf OVCUAPI  cudaMCFDia_sabsmin(  fComplex *h_RetVal, cfPMatrix MA, ui len );
overror_t     __vcuf OVCUAPI  cudaMCFDia_sum(  fComplex *h_RetVal, cfPMatrix MA, ui len );
overror_t     __vcuf OVCUAPI  cudaMCFDia_prod( fComplex *h_RetVal, cfPMatrix MA, ui len );

overror_t     __vcuf OVCUAPI  cusdMCFDia_absmax(  float *d_RetVal, cfPMatrix MA, ui len );
overror_t     __vcuf OVCUAPI  cusdMCFDia_absmin(  float *d_RetVal, cfPMatrix MA, ui len );
overror_t     __vcuf OVCUAPI  cusdMCFDia_maxReIm(  fComplex *d_RetVal, cfPMatrix MA, ui len );
overror_t     __vcuf OVCUAPI  cusdMCFDia_minReIm(  fComplex *d_RetVal, cfPMatrix MA, ui len );
overror_t     __vcuf OVCUAPI  cusdMCFDia_absmaxReIm(  fComplex *d_RetVal, cfPMatrix MA, ui len );
overror_t     __vcuf OVCUAPI  cusdMCFDia_absminReIm(  fComplex *d_RetVal, cfPMatrix MA, ui len );
overror_t     __vcuf OVCUAPI  cusdMCFDia_cabsmax(  fComplex *d_RetVal, cfPMatrix MA, ui len );
overror_t     __vcuf OVCUAPI  cusdMCFDia_cabsmin(  fComplex *d_RetVal, cfPMatrix MA, ui len );
overror_t     __vcuf OVCUAPI  cusdMCFDia_sabsmax(  fComplex *d_RetVal, cfPMatrix MA, ui len );
overror_t     __vcuf OVCUAPI  cusdMCFDia_sabsmin(  fComplex *d_RetVal, cfPMatrix MA, ui len );
overror_t     __vcuf OVCUAPI  cusdMCFDia_sum(  fComplex *d_RetVal, cfPMatrix MA, ui len );
overror_t     __vcuf OVCUAPI  cusdMCFDia_prod( fComplex *d_RetVal, cfPMatrix MA, ui len );

overror_t  __vcuf OVCUAPI  cudaMCFRows_runsum( cfPMatrix MA, ui ht, ui len );
overror_t  __vcuf OVCUAPI  cudaMCFCols_runsum( cfPMatrix MA, ui ht, ui len );
overror_t  __vcuf OVCUAPI  cudaMCFRows_runprod( cfPMatrix MA, ui ht, ui len );
overror_t  __vcuf OVCUAPI  cudaMCFCols_runprod( cfPMatrix MA, ui ht, ui len );

overror_t  __vcuf OVCUAPI  cudaMCFRows_rotate( cfPMatrix MA, ui ht, ui len, ssize_t pos );
overror_t  __vcuf OVCUAPI  cudaMCFCols_rotate( cfPMatrix MA, ui ht, ui len, ssize_t pos );
overror_t  __vcuf OVCUAPI  cudaMCFRows_rotate_buf( cfPMatrix MA, ui ht, ui len, ssize_t pos, cfPMatrix MBuf );
overror_t  __vcuf OVCUAPI  cudaMCFCols_rotate_buf( cfPMatrix MA, ui ht, ui len, ssize_t pos, cfPMatrix MBuf );
overror_t  __vcuf OVCUAPI  cudaMCFRows_reflect( cfPMatrix MA, ui ht, ui len );
overror_t  __vcuf OVCUAPI  cudaMCFCols_reflect( cfPMatrix MA, ui ht, ui len );
overror_t  __vcuf OVCUAPI  cudaMCFRows_rev( cfPMatrix MA, ui ht, ui len );
overror_t  __vcuf OVCUAPI  cudaMCFCols_rev( cfPMatrix MA, ui ht, ui len );

/********  Operations involving two rows or two colums of one matrix  *****/

overror_t   __vcuf OVCUAPI  cudaMCFRows_exchange( cfPMatrix MA, ui ht, ui len, ui i1, ui i2 );
overror_t   __vcuf OVCUAPI  cudaMCFCols_exchange( cfPMatrix MA, ui ht, ui len, ui i1, ui i2 );

overror_t   __vcuf OVCUAPI  cudaMCFRows_add( cfPMatrix MA, ui ht, ui len, ui destRow, ui sourceRow );
overror_t   __vcuf OVCUAPI  cudaMCFCols_add( cfPMatrix MA, ui ht, ui len, ui destCol, ui sourceCol );

overror_t   __vcuf OVCUAPI  cudaMCFRows_sub( cfPMatrix MA, ui ht, ui len, ui destRow, ui sourceRow );
overror_t   __vcuf OVCUAPI  cudaMCFCols_sub( cfPMatrix MA, ui ht, ui len, ui destCol, ui sourceCol );

#if defined __cplusplus && defined _CMATH_CLASSDEFS && defined __BORLANDC__ && defined _WIN64
} // for C++Builder on Win64, the following functions cannot be extern "C", if fComplex is a class
#endif
overror_t   __vcuf OVCUAPI_ifNotBC64Class  cudaMCFRows_Cadd( cfPMatrix MA, ui ht, ui len, ui destRow, ui sourceRow, fComplex C );
overror_t   __vcuf OVCUAPI_ifNotBC64Class  cudaMCFCols_Cadd( cfPMatrix MA, ui ht, ui len, ui destCol, ui sourceCol, fComplex C );

overror_t   __vcuf OVCUAPI_ifNotBC64Class  cudaMCFRows_lincomb( cfPMatrix MA, ui ht, ui len, ui destRow,  fComplex  destC,
                                                                 ui srceRow,  fComplex  srceC );
overror_t   __vcuf OVCUAPI_ifNotBC64Class  cudaMCFCols_lincomb( cfPMatrix MA, ui ht, ui len, ui destCol,  fComplex  destC,
                                                                 ui srceCol,  fComplex  srceC );
#if defined __cplusplus && defined _CMATH_CLASSDEFS && defined __BORLANDC__ && defined _WIN64
extern "C" {
#endif
overror_t   __vcuf OVCUAPI  cusdMCFRows_Cadd( cfPMatrix MA, ui ht, ui len, ui destRow, ui sourceRow, fComplex *d_C );
overror_t   __vcuf OVCUAPI  cusdMCFCols_Cadd( cfPMatrix MA, ui ht, ui len, ui destCol, ui sourceCol, fComplex *d_C );
overror_t   __vcuf OVCUAPI  cusdMCFRows_lincomb( cfPMatrix MA, ui ht, ui len, ui destRow,  fComplex  *d_destC,
                                                                 ui srceRow,  fComplex  *d_srceC );
overror_t   __vcuf OVCUAPI  cusdMCFCols_lincomb( cfPMatrix MA, ui ht, ui len, ui destCol,  fComplex  *d_destC,
                                                                 ui srceCol,  fComplex  *d_srceC );


/**************  Transposing and rotating a matrix **********************/

overror_t  __vcuf OVCUAPI  cudaMCFtranspose( cfPMatrix MTr, cfPMatrix MA, ui htTr, ui lenTr );
overror_t  __vcuf OVCUAPI  cudaMCFhermconj( cfPMatrix MHConj, cfPMatrix MA, ui htTr, ui lenTr );
overror_t  __vcuf OVCUAPI  cudaMCFrotate90(  cfPMatrix MRot, cfPMatrix MA, ui htRot, ui lenRot );
#define     cudaMCFrotate180( MRot, MA, htRot, lenRot ) cudaVCF_rev( MRot, MA, (htRot)*(lenRot) )
overror_t  __vcuf OVCUAPI  cudaMCFrotate270( cfPMatrix MRot, cfPMatrix MA, ui htRot, ui lenRot );
overror_t  __vcuf OVCUAPI  cudaMCFtranspose_buf( cfPMatrix MTr, cfPMatrix MA, ui htTr, ui lenTr, cfPMatrix MBuf );


/************************ Matrix Arithmetics *************************/

#define cudaMCFaddM( MC, MA, MB, htA, lenA )      cudaVCF_addV( MC, MA, MB, (htA)*(lenA) )
overror_t __vcuf OVCUAPI  cudaMCFaddMT( cfPMatrix MC, cfPMatrix MA, cfPMatrix MB, ui htA, ui lenA );
#define cudaMCFsubM( MC, MA, MB, htA, lenA )      cudaVCF_subV( MC, MA, MB, (htA)*(lenA) )
overror_t __vcuf OVCUAPI  cudaMCFsubMT( cfPMatrix MC, cfPMatrix MA, cfPMatrix MB, ui htA, ui lenA );
overror_t __vcuf OVCUAPI  cudaMCFsubrMT( cfPMatrix MC, cfPMatrix MA, cfPMatrix MB, ui htA, ui lenA );

#define cudaMCFmulC( MB, MA, htA, lenA, C )       cudaVCF_mulC( MB, MA, (htA)*(lenA), C )
#define cudaMCFdivC( MB, MA, htA, lenA, C )       cudaVCF_divC( MB, MA, (htA)*(lenA), C )
#define cudaMCFmulReC( MB, MA, htA, lenA, CRe )   cudaVCF_mulReC( MB, MA, (htA)*(lenA), CRe )
#define cudaMCFdivReC( MB, MA, htA, lenA, CRe )   cudaVCF_divReC( MB, MA, (htA)*(lenA), CRe )
#define cudaMCFlincomb( MC, MA, MB, htA, lenA, CA, CB ) cudaVCF_lincomb( MC, MA, MB, (htA)*(lenA), CA, CB )

#define cusdMCFmulC( MB, MA, htA, lenA, d_C )       cusdVCF_mulC( MB, MA, (htA)*(lenA), d_C )
#define cusdMCFdivC( MB, MA, htA, lenA, d_C )       cusdVCF_divC( MB, MA, (htA)*(lenA), d_C )
#define cusdMCFmulReC( MB, MA, htA, lenA, d_CRe )   cusdVCF_mulReC( MB, MA, (htA)*(lenA), d_CRe )
#define cusdMCFdivReC( MB, MA, htA, lenA, d_CRe )   cusdVCF_divReC( MB, MA, (htA)*(lenA), d_CRe )
#define cusdMCFlincomb( MC, MA, MB, htA, lenA, d_CA, d_CB ) cusdVCF_lincomb( MC, MA, MB, (htA)*(lenA), d_CA, d_CB )

overror_t  __vcuf OVCUAPI  cudaMCFmulV( cfVector Y, cfPMatrix MA, cfVector X, ui htA, ui lenA );
overror_t  __vcuf OVCUAPI  cudaMCFTmulV( cfVector Y, cfPMatrix MA, cfVector X, ui htA, ui lenA );
overror_t  __vcuf OVCUAPI  cudaVCFmulM( cfVector Y, cfVector X, cfPMatrix MA, ui htA, ui lenA );
overror_t  __vcuf OVCUAPI  cudaVCFmulMT( cfVector Y, cfVector X, cfPMatrix MA, ui htA, ui lenA );
overror_t  __vcuf OVCUAPI  cudaMCFmulM( cfPMatrix MC, cfPMatrix MA, cfPMatrix MB, ui htA, ui lenA, ui lenB );
overror_t  __vcuf OVCUAPI  cudaMCFmulMT( cfPMatrix MC, cfPMatrix MA, cfPMatrix MB, ui htA, ui lenA, ui htB );
overror_t  __vcuf OVCUAPI  cudaMCFmulMH( cfPMatrix MC, cfPMatrix MA, cfPMatrix MB, ui htA, ui lenA, ui htB );
overror_t  __vcuf OVCUAPI  cudaMCFTmulM( cfPMatrix MC, cfPMatrix MA, cfPMatrix MB, ui htA, ui lenA, ui lenB );
overror_t  __vcuf OVCUAPI  cudaMCFHmulM( cfPMatrix MC, cfPMatrix MA, cfPMatrix MB, ui htA, ui lenA, ui lenB );
overror_t  __vcuf OVCUAPI  cudaMCFTmulMT( cfPMatrix MC, cfPMatrix MA, cfPMatrix MB, ui htA, ui lenA, ui htB );
overror_t  __vcuf OVCUAPI  cudaMCFTmulMH( cfPMatrix MC, cfPMatrix MA, cfPMatrix MB, ui htA, ui lenA, ui htB );
overror_t  __vcuf OVCUAPI  cudaMCFdiamulM( cfPMatrix MC, cfPMatrix MADia, cfPMatrix MB, ui htB, ui lenB );
overror_t  __vcuf OVCUAPI  cudaMCFdiamulMT( cfPMatrix MC, cfPMatrix MADia, cfPMatrix MB, ui htB, ui lenB );
overror_t  __vcuf OVCUAPI  cudaMCFmulMdia( cfPMatrix MC, cfPMatrix MA, cfPMatrix MBDia, ui htA, ui lenA );
overror_t  __vcuf OVCUAPI  cudaMCFTmulMdia( cfPMatrix MC, cfPMatrix MA, cfPMatrix MBDia, ui htA, ui lenA );


/*************  Two-Dimensional Fourier-Transform Methods *****************/

overror_t  __vcuf OVCUAPI  cudaMCFFFT( cfPMatrix MY, cfPMatrix MX, ui ht, ui len, int dir );
overror_t  __vcuf OVCUAPI  cudaMCFfilter( cfPMatrix MY, cfPMatrix MX, cfPMatrix MFlt, ui ht, ui len );
overror_t  __vcuf OVCUAPI  cudaMCFRows_FFT( cfPMatrix MY, cfPMatrix MX, ui ht, ui len, int dir );
overror_t  __vcuf OVCUAPI  cudaMCFCols_FFT( cfPMatrix MY, cfPMatrix MX, ui ht, ui len, int dir );


/**************************  Input and Output  **************************
	The input/output functions involve memory transfers from device
	to host memory or vice versa. The generic cudaMCF_input/output functions
	allocate their own host buffers, whereas the cudaMCF_xxx_buf functions
	take a user-supplied buffer vector h_Wk (size must be >= ht*len )
	and are much more efficient.                                       */

#define cudaMCFprint( MA, ht, len )  cudaMCFfprint( stdout, MA, ht, len, 80 )
overror_t __vf cudaMCFfprint( FILE *stream, cfPMatrix MA, ui ht, ui len, unsigned linewidth );
overror_t __vf cudaMCFcprint( cfPMatrix MA, ui ht, ui len );
#define cudaMCFprint_buf( MA, ht, len, h_Wk )  cudaMCFfprint_buf( stdout, MA, ht, len, 80, h_Wk )
overror_t __vf cudaMCFfprint_buf( FILE *stream, cfPMatrix MA, ui ht, ui len, unsigned linewidth, cfVector h_Wk );
overror_t __vf cudaMCFcprint_buf( cfPMatrix MA, ui ht, ui len, cfVector h_Wk );
overror_t __vf cudaMCFwrite( FILE *stream, cfPMatrix X, ui ht, ui len  );
overror_t __vf cudaMCFwrite_buf( FILE *stream, cfPMatrix X, ui ht, ui len, cfVector h_Wk );
#if !((defined __BORLANDC__) && (__BORLANDC__ < 0x710))
		/* modern compiler versions:  */
	overror_t __vf cudaMCFread( cfPMatrix X, ui ht, ui len, FILE *stream );
	overror_t __vf cudaMCFread_buf( cfPMatrix X, ui ht, ui len, FILE *stream, cfVector h_Wk );
#else /* older Borland compiler versions need separate implementation */
	overror_t __vf cudaMCFread1( cfPMatrix X, ui ht, ui len, FILE *stream );
	overror_t __vf cudaMCFread1_buf( cfPMatrix X, ui ht, ui len, FILE *stream, cfVector h_Wk );
	#define cudaMCFread      cudaMCFread1
	#define cudaMCFread_buf  cudaMCFread1_buf
#endif
#define cudaMCFstore( str, MA, ht, len ) cudaVCF_store( str, MA, (len)*(ht) )
#define cudaMCFrecall( MA, ht, len, str) cudaVCF_recall( MA, (len)*(ht), str)
#define cudaMCFstore_buf( str, MA, ht, len, h_Wk ) cudaVCF_store( str, MA, (len)*(ht), h_Wk )
#define cudaMCFrecall_buf( MA, ht, len, str, h_Wk) cudaVCF_recall( MA, (len)*(ht), str, h_Wk)


/***************************************************************************
    cudaMCF_func (working on matrices in device memory, input type cfMatrix, 
	             scalar parameters reside on host and are passed by value)
    cusdMCF_func (as cudaMCF_func except scalar parameters reside on device 
	             and are passed by address)                                 */



/***************************************************************************
 *  The following definitions are needed to access individual elements,    *
 *  and row pointers. As all addresses point to device memory, the usual   *
 *  mechanism of accessing elements, i.e., writing something like MA[m][n] *
 *  is not possible here!                                                  *
 *  Pro forma, the distinction between the data types cfMatrix and         *
 *  cfPMatrix is kept. However, in the present implementation, both of     *
 *  these types actually contain a pointer to the matrix element [0][0].   *
 *  Pro forma, the distinction between the data types cfMatrix and         *
 *  cfPMatrix is kept. However, in the present implementation, both of     *
 *  these types actually contain a pointer to the matrix element [0][0].   *
 *  For Visual C++, inline functions ensure proper type checking at compile*
*   time, while for C++ Builder and for plain-C a type-cast is performed.  *
 ***************************************************************************/

#if defined __cplusplus && !defined(__BORLANDC__)

/***  Addressing single elements of dynamically allocated matrices: ******/

inline void    cudaMCF_setElement( cfMatrix MA, ui ht, ui len, ui m, ui n, fComplex C )
	{	cudaMCFsetElement( (cfPMatrix)(MA), ht, len, m, n, C );}
inline void    cusdMCF_setElement( cfMatrix MA, ui ht, ui len, ui m, ui n, fComplex *d_C )
	{	cusdMCFsetElement( (cfPMatrix)(MA), ht, len, m, n, d_C );}
inline void    cudaMCF_getElement( fComplex *y, cfMatrix MA, ui ht, ui len, ui m, ui n )
	{	cudaMCFgetElement( y, (cfPMatrix)(MA), ht, len, m, n );}
inline void    cusdMCF_getElement( fComplex *d_y, cfMatrix MA, ui ht, ui len, ui m, ui n )
	{	cusdMCFgetElement( d_y, (cfPMatrix)(MA), ht, len, m, n );}
inline fComplex * cudaMCF_Pelement( cfMatrix MA, ui ht, ui len, ui m, ui n )
	{	return cudaMCFPelement( (cfPMatrix)(MA), ht, len, m, n );}
#if defined _CMATH_CLASSDEFS
} // the following function cannot be extern "C", if fComplex is a class
#endif
inline fComplex   cudaMCF_element( cfMatrix MA, ui ht, ui len, ui m, ui n )
{	return cudaMCFelement( (cfPMatrix)(MA), ht, len, m, n );}
#if defined _CMATH_CLASSDEFS
extern "C" {
#endif

 /****************  Initialization  ****************************************/

inline overror_t  cudaMCF_equ0( cfMatrix MA, ui ht, ui len )
	{	return cudaVCF_equ0( (cfPMatrix)MA, (ht)*(len) ); }
inline overror_t  cudaMCF_equ1( cfMatrix MA, ui len )
	{	return cudaMCFequ1( (cfPMatrix)(MA), len );} /* identity matrix */
inline overror_t  cudaMCF_equm1( cfMatrix MA, ui len )
	{	return cudaMCFequm1( (cfPMatrix)(MA), len );} /* neg. identity matrix */
inline overror_t  cudaMCF_randomLC( cfMatrix MA, ui ht, ui len, long seed, fComplex MinVal, fComplex MaxVal, V_RANDOMLCSTATE *h_state )
	{	return cudaVCF_randomLC( (cfPMatrix)(MA), (ht)*(len), seed, MinVal, MaxVal, h_state );}
inline overror_t  cudaMCF_random( cfMatrix MA, ui ht, ui len, long seed, fComplex MinVal, fComplex MaxVal )
	{	return cudaVCF_random( (cfPMatrix)(MA), (ht)*(len), seed, MinVal, MaxVal );}
inline overror_t  cusdMCF_randomLC( cfMatrix MA, ui ht, ui len, long seed, fComplex *d_MinVal, fComplex *d_MaxVal, V_RANDOMLCSTATE *h_state )
	{	return cusdVCF_randomLC( (cfPMatrix)(MA), (ht)*(len), seed, d_MinVal, d_MaxVal, h_state );}
inline overror_t  cusdMCF_random( cfMatrix MA, ui ht, ui len, long seed, fComplex *d_MinVal, fComplex *d_MaxVal )
	{	return cusdVCF_random( (cfPMatrix)(MA), (ht)*(len), seed, d_MinVal, d_MaxVal );}

inline overror_t  cudaMCF_outerprod( cfMatrix MA, cfVector X,  cfVector Y, ui ht, ui len )
	{	return cudaMCFouterprod( (cfPMatrix)(MA), X, Y, ht, len );}
                       /* sizX=ht, sizY=len */
inline overror_t  cudaMCF_Row_equ0( cfMatrix MA, ui ht, ui len, ui iRow )
	{	return cudaMCFRow_equ0( (cfPMatrix)MA, ht, len, iRow );}
inline overror_t  cudaMCF_Col_equ0( cfMatrix MA, ui ht, ui len, ui iRow )
	{	return cudaMCFCol_equ0( (cfPMatrix)MA, ht, len, iRow );}
inline overror_t  cudaMCF_Dia_equ0( cfMatrix MA, ui len )
	{	return cudaMCFDia_equ0( (cfPMatrix)(MA), len );}

inline overror_t  cudaMCF_Row_equC( cfMatrix MA, ui ht, ui len, ui iRow, fComplex C )
	{	return cudaMCFRow_equC( (cfPMatrix)MA, ht, len, iRow, C );}
inline overror_t  cudaMCF_Col_equC( cfMatrix MA, ui ht, ui len, ui iRow, fComplex C )
	{	return cudaMCFCol_equC( (cfPMatrix)MA, ht, len, iRow, C );}
inline overror_t  cudaMCF_Dia_equC( cfMatrix MA, ui len, fComplex C )
	{	return cudaMCFDia_equC( (cfPMatrix)(MA), len, C );}

inline overror_t  cusdMCF_Row_equC( cfMatrix MA, ui ht, ui len, ui iRow, fComplex *d_C )
	{	return cusdMCFRow_equC( (cfPMatrix)MA, ht, len, iRow, d_C );}
inline overror_t  cusdMCF_Col_equC( cfMatrix MA, ui ht, ui len, ui iRow, fComplex *d_C )
	{	return cusdMCFCol_equC( (cfPMatrix)MA, ht, len, iRow, d_C );}
inline overror_t  cusdMCF_Dia_equC( cfMatrix MA, ui len, fComplex *d_C )
	{	return cusdMCFDia_equC( (cfPMatrix)(MA), len, d_C );}

inline overror_t  cudaMCF_Row_equV( cfMatrix MA, ui ht, ui len, ui iRow, cfVector X )
	{	return cudaMCFRow_equV( (cfPMatrix)MA, ht, len, iRow, X );}
inline overror_t  cudaMCF_Col_equV( cfMatrix MA, ui ht, ui len, ui iRow, cfVector X )
	{	return cudaMCFCol_equV( (cfPMatrix)MA, ht, len, iRow, X );}
inline overror_t  cudaMCF_Dia_equV( cfMatrix MA, ui len, cfVector X )
	{	return cudaMCFDia_equV( (cfPMatrix)(MA), len, X );}

inline overror_t  cudaMCF_Trd_equM( cfMatrix MA, cfMatrix MTrd, ui len )
	{	return cudaMCFTrd_equM( (cfPMatrix)(MA), (cfPMatrix)(MTrd), len );}
inline overror_t  cudaMCF_Trd_extract( cfMatrix MTrd, cfMatrix MA, ui len )
	{	return cudaMCFTrd_extract( (cfPMatrix)(MTrd), (cfPMatrix)(MA), len );}

inline overror_t cudaMCF_equM( cfMatrix MB, cfMatrix MA, ui ht, ui len )
	{	return cudaVCF_equV( (cfPMatrix)MB, (cfPMatrix)MA, (ht)*(len) );}
inline overror_t cudaMCF_equMhost( cfMatrix d_MB, cfMatrix h_MA, ui ht, ui len )
	{	return cudaVCF_equVhost( (cfPMatrix)d_MB, (h_MA)[0], (ht)*(len) );}
inline overror_t MCF_equMdevice( cfMatrix h_MB, cfMatrix d_MA, ui ht, ui len )
	{	return VCF_equVdevice( h_MB[0], (cfPMatrix)d_MA, (ht)*(len) );}
inline overror_t cudaMCF_neg( cfMatrix MB, cfMatrix MA, ui ht, ui len )
	{	return cudaVCF_neg( (cfPMatrix)(MB), (cfPMatrix)(MA), (ht)*(len) );}
inline overror_t  cudaMCF_UequL( cfMatrix MA, ui len )
	{	return cudaMCFUequL( (cfPMatrix)(MA), len );}
inline overror_t  cudaMCF_LequU( cfMatrix MA, ui len )
	{	return cudaMCFLequU( (cfPMatrix)(MA), len );}

            /* data-type conversions:  */
inline overror_t cudaM_CDtoCF( cfMatrix MCF, cdMatrix MCD, ui ht, ui len )
	{	return cudaV_CDtoCF( (cfPMatrix)(MCF), (cdPMatrix)(MCD), (ht)*(len) );}

inline overror_t cudaMF_CtoRe( fMatrix MY, cfMatrix MCX, ui ht, ui len )
	{	return cudaVF_CtoRe( (fPMatrix)(MY),  (cfPMatrix)(MCX), (ht)*(len) );}
inline overror_t cudaMF_CtoIm( fMatrix MY, cfMatrix MCX, ui ht, ui len )
	{	return cudaVF_CtoIm( (fPMatrix)(MY),  (cfPMatrix)(MCX), (ht)*(len) );}
inline overror_t cudaMF_CtoReIm( fMatrix MYRe, fMatrix MYIm, cfMatrix MCX, ui ht, ui len )
	{	return cudaVF_CtoReIm( (fPMatrix)(MYRe), (fPMatrix)(MYIm), (cfPMatrix)(MCX), (ht)*(len) );}
inline overror_t cudaMF_RetoC( cfMatrix MCY, fMatrix MX, ui ht, ui len )
	{	return cudaVF_RetoC( (cfPMatrix)(MCY), (fPMatrix)(MX),  (ht)*(len) );}
inline overror_t cudaMF_ImtoC( cfMatrix MCY, fMatrix MX, ui ht, ui len )
	{	return cudaVF_ImtoC( (cfPMatrix)(MCY), (fPMatrix)(MX),  (ht)*(len) );}
inline overror_t cudaMF_ReImtoC( cfMatrix MCYRe, cfMatrix MCYIm, fMatrix MX, ui ht, ui len )
	{	return cudaVF_ReImtoC( (cfPMatrix)(MCYRe), (fPMatrix)(MCYIm), (fPMatrix)(MX),  (ht)*(len) );}

/********  Extracting a submatrix and copying a submatrix back  *********/

inline overror_t cudaMCF_submatrix( cfMatrix MSub, ui subHt, ui subLen, cfMatrix MSrce, ui srceHt, ui srceLen,
                      ui firstRowInCol, ui sampInCol, ui firstColInRow, ui sampInRow )
	{	return cudaMCFsubmatrix(  (cfPMatrix)(MSub), subHt, subLen,
		                         (cfPMatrix)(MSrce), srceHt, srceLen,
								 firstRowInCol, sampInCol, firstColInRow, sampInRow ); }

inline overror_t cudaMCF_submatrix_equM( cfMatrix MDest, ui destHt, ui destLen,
                           ui firstRowInCol, ui sampInCol, ui firstColInRow, ui sampInRow,
                           cfMatrix MSrce, ui srceHt, ui srceLen )
	{	return cudaMCFsubmatrix_equM(  (cfPMatrix)(MDest), destHt, destLen,
                             firstRowInCol, sampInCol, firstColInRow, sampInRow,
							 (cfPMatrix)(MSrce), srceHt, srceLen );}

inline overror_t cudaMCF_equMblock( cfMatrix MSub, ui subHt, ui subLen, cfMatrix MSrce, ui srceHt, ui srceLen,
                      ui firstRowInCol, ui firstColInRow )
{	return cudaMCFequMblock(  (cfPMatrix)(MSub), subHt, subLen,
						   (cfPMatrix)(MSrce), srceHt, srceLen, firstRowInCol, firstColInRow );}

inline overror_t cudaMCF_block_equM( cfMatrix MDest, ui destHt, ui destLen,
                       ui firstRowInCol, ui firstColInRow,
                       cfMatrix MSrce, ui srceHt, ui srceLen )
	{	return cudaMCFblock_equM( (cfPMatrix)(MDest), destHt, destLen,
                             firstRowInCol, firstColInRow,
							 (cfPMatrix)(MSrce), srceHt, srceLen );}

inline overror_t cudaMCF_equMblockT( cfMatrix MSub, ui subHt, ui subLen, cfMatrix MSrce, ui srceHt, ui srceLen,
                      ui firstRowInCol, ui firstColInRow )
	{	return cudaMCFequMblockT(  (cfPMatrix)(MSub), subHt, subLen,
                             (cfPMatrix)(MSrce), srceHt, srceLen,
							 firstRowInCol, firstColInRow );}

inline overror_t cudaMCF_block_equMT( cfMatrix MDest, ui destHt, ui destLen,
                       ui firstRowInCol, ui firstColInRow,
                       cfMatrix MSrce, ui srceHt, ui srceLen )
	{	return cudaMCFblock_equMT( (cfPMatrix)(MDest), destHt, destLen,
                             firstRowInCol, firstColInRow,
							 (cfPMatrix)(MSrce), srceHt, srceLen );}

/*****   Extracting a single row or a single column or the diagonal  ******
 *       and storing it into a vector                                     */

inline overror_t cudaMCF_Row_extract( cfVector Y, cfMatrix MA, ui ht, ui len, ui iRow ) 
	{	return cudaMCFRow_extract( Y, (cfPMatrix)(MA), ht, len, iRow );}
inline overror_t cudaMCF_Col_extract( cfVector Y, cfMatrix MA, ui ht, ui len, ui iCol ) 
	{	return cudaMCFCol_extract( Y, (cfPMatrix)(MA), ht, len, iCol );}
inline overror_t cudaMCF_Dia_extract( cfVector Y, cfMatrix MA, ui len )
	{	return cudaMCFDia_extract( Y, (cfPMatrix)(MA), len );}


/**************  Deleting or inserting a row or a column   ***************/

inline overror_t cudaMCF_Row_delete( cfMatrix MB, cfMatrix MA, ui htA, ui lenA, ui iRow )
	{	return cudaMCFRow_delete( (cfPMatrix)(MB), (cfPMatrix)(MA), htA, lenA, iRow );}
inline overror_t cudaMCF_Col_delete( cfMatrix MB, cfMatrix MA, ui htA, ui lenA, ui iCol )
	{	return cudaMCFCol_delete( (cfPMatrix)(MB), (cfPMatrix)(MA), htA, lenA, iCol );}
inline overror_t cudaMCF_Row_insert( cfMatrix MB, cfMatrix MA, ui htB, ui lenB, ui iRow, cfVector X )
	{	return cudaMCFRow_insert( (cfPMatrix)(MB), (cfPMatrix)(MA), htB, lenB, iRow, X );}
inline overror_t cudaMCF_Col_insert( cfMatrix MB, cfMatrix MA, ui htB, ui lenB, ui iCol, cfVector X )
	{	return cudaMCFCol_insert( (cfPMatrix)(MB), (cfPMatrix)(MA), htB, lenB, iCol, X );}


/*****************    Basic arithmetic operations *********************
                      performed on one single row,
                      or one single column of any matrix,
                      or on the diagonal of a square matrix

    Note: In contrast to the analogous VectorLib functions, the operations
    are performed in-place, i.e. the input matrix itself is changed  */

inline overror_t cudaMCF_Row_neg( cfMatrix MA, ui ht, ui len, ui iRow )
	{	return cudaMCFRow_neg( (cfPMatrix)(MA), ht, len, iRow );}
inline overror_t cudaMCF_Col_neg( cfMatrix MA, ui ht, ui len, ui iCol )
	{	return cudaMCFCol_neg( (cfPMatrix)(MA), ht, len, iCol );}
inline overror_t cudaMCF_Row_conj( cfMatrix MA, ui ht, ui len, ui iRow )
	{	return cudaMCFRow_conj( (cfPMatrix)(MA), ht, len, iRow );}
inline overror_t cudaMCF_Col_conj( cfMatrix MA, ui ht, ui len, ui iCol )
	{	return cudaMCFCol_conj( (cfPMatrix)(MA), ht, len, iCol );}

inline overror_t cudaMCF_Row_addC( cfMatrix MA, ui ht, ui len, ui iRow, fComplex C )
	{	return cudaMCFRow_addC( (cfPMatrix)(MA), ht, len, iRow, C );}
inline overror_t cudaMCF_Col_addC( cfMatrix MA, ui ht, ui len, ui iCol, fComplex C )
	{	return cudaMCFCol_addC( (cfPMatrix)(MA), ht, len, iCol, C );}
inline overror_t cudaMCF_Dia_addC( cfMatrix MA, ui len, fComplex C )
	{	return cudaMCFDia_addC( (cfPMatrix)(MA), len, C );}
inline overror_t cusdMCF_Row_addC( cfMatrix MA, ui ht, ui len, ui iRow, fComplex *d_C )
	{	return cusdMCFRow_addC( (cfPMatrix)(MA), ht, len, iRow, d_C );}
inline overror_t cusdMCF_Col_addC( cfMatrix MA, ui ht, ui len, ui iCol, fComplex *d_C )
	{	return cusdMCFCol_addC( (cfPMatrix)(MA), ht, len, iCol, d_C );}
inline overror_t cusdMCF_Dia_addC( cfMatrix MA, ui len, fComplex *d_C )
	{	return cusdMCFDia_addC( (cfPMatrix)(MA), len, d_C );}

inline overror_t cudaMCF_Row_addV( cfMatrix MA, ui ht, ui len, ui iRow, cfVector X )
	{	return cudaMCFRow_addV( (cfPMatrix)(MA), ht, len, iRow, X );}
inline overror_t cudaMCF_Col_addV( cfMatrix MA, ui ht, ui len, ui iCol, cfVector X )
	{	return cudaMCFCol_addV( (cfPMatrix)(MA), ht, len, iCol, X );}
inline overror_t cudaMCF_Dia_addV( cfMatrix MA, ui len, cfVector X )
	{	return cudaMCFDia_addV( (cfPMatrix)(MA), len, X );}

inline overror_t cudaMCF_Row_subC( cfMatrix MA, ui ht, ui len, ui iRow, fComplex C )
	{	return cudaMCFRow_subC( (cfPMatrix)(MA), ht, len, iRow, C );}
inline overror_t cudaMCF_Col_subC( cfMatrix MA, ui ht, ui len, ui iCol, fComplex C )
	{	return cudaMCFCol_subC( (cfPMatrix)(MA), ht, len, iCol, C );}
inline overror_t cudaMCF_Dia_subC( cfMatrix MA, ui len, fComplex C )
	{	return cudaMCFDia_subC( (cfPMatrix)(MA), len, C );}
inline overror_t cusdMCF_Row_subC( cfMatrix MA, ui ht, ui len, ui iRow, fComplex *d_C )
	{	return cusdMCFRow_subC( (cfPMatrix)(MA), ht, len, iRow, d_C );}
inline overror_t cusdMCF_Col_subC( cfMatrix MA, ui ht, ui len, ui iCol, fComplex *d_C )
	{	return cusdMCFCol_subC( (cfPMatrix)(MA), ht, len, iCol, d_C );}
inline overror_t cusdMCF_Dia_subC( cfMatrix MA, ui len, fComplex *d_C )
	{	return cusdMCFDia_subC( (cfPMatrix)(MA), len, d_C );}

inline overror_t cudaMCF_Row_subV( cfMatrix MA, ui ht, ui len, ui iRow, cfVector X )
	{	return cudaMCFRow_subV( (cfPMatrix)(MA), ht, len, iRow, X );}
inline overror_t cudaMCF_Col_subV( cfMatrix MA, ui ht, ui len, ui iCol, cfVector X )
	{	return cudaMCFCol_subV( (cfPMatrix)(MA), ht, len, iCol, X );}
inline overror_t cudaMCF_Dia_subV( cfMatrix MA, ui len, cfVector X )
	{	return cudaMCFDia_subV( (cfPMatrix)(MA), len, X );}

inline overror_t cudaMCF_Row_subrC( cfMatrix MA, ui ht, ui len, ui iRow, fComplex C )
	{	return cudaMCFRow_subrC( (cfPMatrix)(MA), ht, len, iRow, C );}
inline overror_t cudaMCF_Col_subrC( cfMatrix MA, ui ht, ui len, ui iCol, fComplex C )
	{	return cudaMCFCol_subrC( (cfPMatrix)(MA), ht, len, iCol, C );}
inline overror_t cudaMCF_Dia_subrC( cfMatrix MA, ui len, fComplex C )
	{	return cudaMCFDia_subrC( (cfPMatrix)(MA), len, C );}
inline overror_t cusdMCF_Row_subrC( cfMatrix MA, ui ht, ui len, ui iRow, fComplex *d_C )
	{	return cusdMCFRow_subrC( (cfPMatrix)(MA), ht, len, iRow, d_C );}
inline overror_t cusdMCF_Col_subrC( cfMatrix MA, ui ht, ui len, ui iCol, fComplex *d_C )
	{	return cusdMCFCol_subrC( (cfPMatrix)(MA), ht, len, iCol, d_C );}
inline overror_t cusdMCF_Dia_subrC( cfMatrix MA, ui len, fComplex *d_C )
	{	return cusdMCFDia_subrC( (cfPMatrix)(MA), len, d_C );}

inline overror_t cudaMCF_Row_subrV( cfMatrix MA, ui ht, ui len, ui iRow, cfVector X )
	{	return cudaMCFRow_subrV( (cfPMatrix)(MA), ht, len, iRow, X );}
inline overror_t cudaMCF_Col_subrV( cfMatrix MA, ui ht, ui len, ui iCol, cfVector X )
	{	return cudaMCFCol_subrV( (cfPMatrix)(MA), ht, len, iCol, X );}
inline overror_t cudaMCF_Dia_subrV( cfMatrix MA, ui len, cfVector X )
	{	return cudaMCFDia_subrV( (cfPMatrix)(MA), len, X );}

inline overror_t cudaMCF_Row_mulC( cfMatrix MA, ui ht, ui len, ui iRow, fComplex C )
	{	return cudaMCFRow_mulC( (cfPMatrix)(MA), ht, len, iRow, C );}
inline overror_t cudaMCF_Col_mulC( cfMatrix MA, ui ht, ui len, ui iCol, fComplex C )
	{	return cudaMCFCol_mulC( (cfPMatrix)(MA), ht, len, iCol, C );}
inline overror_t cudaMCF_Dia_mulC( cfMatrix MA, ui len, fComplex C )
	{	return cudaMCFDia_mulC( (cfPMatrix)(MA), len, C );}
inline overror_t cusdMCF_Row_mulC( cfMatrix MA, ui ht, ui len, ui iRow, fComplex *d_C )
	{	return cusdMCFRow_mulC( (cfPMatrix)(MA), ht, len, iRow, d_C );}
inline overror_t cusdMCF_Col_mulC( cfMatrix MA, ui ht, ui len, ui iCol, fComplex *d_C )
	{	return cusdMCFCol_mulC( (cfPMatrix)(MA), ht, len, iCol, d_C );}
inline overror_t cusdMCF_Dia_mulC( cfMatrix MA, ui len, fComplex *d_C )
	{	return cusdMCFDia_mulC( (cfPMatrix)(MA), len, d_C );}

inline overror_t cudaMCF_Row_mulV( cfMatrix MA, ui ht, ui len, ui iRow, cfVector X )
	{	return cudaMCFRow_mulV( (cfPMatrix)(MA), ht, len, iRow, X );}
inline overror_t cudaMCF_Col_mulV( cfMatrix MA, ui ht, ui len, ui iCol, cfVector X )
	{	return cudaMCFCol_mulV( (cfPMatrix)(MA), ht, len, iCol, X );}
inline overror_t cudaMCF_Dia_mulV( cfMatrix MA, ui len, cfVector X )
	{	return cudaMCFDia_mulV( (cfPMatrix)(MA), len, X );}

inline overror_t cudaMCF_Row_divC( cfMatrix MA, ui ht, ui len, ui iRow, fComplex C )
	{	return cudaMCFRow_divC( (cfPMatrix)(MA), ht, len, iRow, C );}
inline overror_t cudaMCF_Col_divC( cfMatrix MA, ui ht, ui len, ui iCol, fComplex C )
	{	return cudaMCFCol_divC( (cfPMatrix)(MA), ht, len, iCol, C );}
inline overror_t cudaMCF_Dia_divC( cfMatrix MA, ui len, fComplex C )
	{	return cudaMCFDia_divC( (cfPMatrix)(MA), len, C );}
inline overror_t cusdMCF_Row_divC( cfMatrix MA, ui ht, ui len, ui iRow, fComplex *d_C )
	{	return cusdMCFRow_divC( (cfPMatrix)(MA), ht, len, iRow, d_C );}
inline overror_t cusdMCF_Col_divC( cfMatrix MA, ui ht, ui len, ui iCol, fComplex *d_C )
	{	return cusdMCFCol_divC( (cfPMatrix)(MA), ht, len, iCol, d_C );}
inline overror_t cusdMCF_Dia_divC( cfMatrix MA, ui len, fComplex *d_C )
	{	return cusdMCFDia_divC( (cfPMatrix)(MA), len, d_C );}

inline overror_t cudaMCF_Row_divV( cfMatrix MA, ui ht, ui len, ui iRow, cfVector X )
	{	return cudaMCFRow_divV( (cfPMatrix)(MA), ht, len, iRow, X );}
inline overror_t cudaMCF_Col_divV( cfMatrix MA, ui ht, ui len, ui iCol, cfVector X )
	{	return cudaMCFCol_divV( (cfPMatrix)(MA), ht, len, iCol, X );}
inline overror_t cudaMCF_Dia_divV( cfMatrix MA, ui len, cfVector X )
	{	return cudaMCFDia_divV( (cfPMatrix)(MA), len, X );}

inline overror_t cudaMCF_Row_divrC( cfMatrix MA, ui ht, ui len, ui iRow, fComplex C )
	{	return cudaMCFRow_divrC( (cfPMatrix)(MA), ht, len, iRow, C );}
inline overror_t cudaMCF_Col_divrC( cfMatrix MA, ui ht, ui len, ui iCol, fComplex C )
	{	return cudaMCFCol_divrC( (cfPMatrix)(MA), ht, len, iCol, C );}
inline overror_t cudaMCF_Dia_divrC( cfMatrix MA, ui len, fComplex C )
	{	return cudaMCFDia_divrC( (cfPMatrix)(MA), len, C );}
inline overror_t cusdMCF_Row_divrC( cfMatrix MA, ui ht, ui len, ui iRow, fComplex *d_C )
	{	return cusdMCFRow_divrC( (cfPMatrix)(MA), ht, len, iRow, d_C );}
inline overror_t cusdMCF_Col_divrC( cfMatrix MA, ui ht, ui len, ui iCol, fComplex *d_C )
	{	return cusdMCFCol_divrC( (cfPMatrix)(MA), ht, len, iCol, d_C );}
inline overror_t cusdMCF_Dia_divrC( cfMatrix MA, ui len, fComplex *d_C )
	{	return cusdMCFDia_divrC( (cfPMatrix)(MA), len, d_C );}

inline overror_t cudaMCF_Row_divrV( cfMatrix MA, ui ht, ui len, ui iRow, cfVector X )
	{	return cudaMCFRow_divrV( (cfPMatrix)(MA), ht, len, iRow, X );}
inline overror_t cudaMCF_Col_divrV( cfMatrix MA, ui ht, ui len, ui iCol, cfVector X )
	{	return cudaMCFCol_divrV( (cfPMatrix)(MA), ht, len, iCol, X );}
inline overror_t cudaMCF_Dia_divrV( cfMatrix MA, ui len, cfVector X )
	{	return cudaMCFDia_divrV( (cfPMatrix)(MA), len, X );}

/******  One-dimensional vector operations **********************
		 performed along all rows or all columns simultaneously,
         or along the diagonal of a square matrix                */

inline overror_t cudaMCF_Rows_absmax( fVector Y, cfMatrix MA, ui ht, ui len )
	{	return cudaMCFRows_absmax( Y, (cfPMatrix)(MA), ht, len );}
inline overror_t cudaMCF_Cols_absmax( fVector Y, cfMatrix MA, ui ht, ui len )
	{	return cudaMCFCols_absmax( Y, (cfPMatrix)(MA), ht, len );}
inline overror_t cudaMCF_Dia_absmax(  float *h_RetValPtr, cfMatrix MA, ui len )
	{	return cudaMCFDia_absmax(  h_RetValPtr, (cfPMatrix)(MA), len );}
inline overror_t cusdMCF_Dia_absmax(  float *d_RetValPtr, cfMatrix MA, ui len )
	{	return cusdMCFDia_absmax(  d_RetValPtr, (cfPMatrix)(MA), len );}
inline overror_t cudaMCF_Rows_absmin( fVector Y, cfMatrix MA, ui ht, ui len )
	{	return cudaMCFRows_absmin( Y, (cfPMatrix)(MA), ht, len );}
inline overror_t cudaMCF_Cols_absmin( fVector Y, cfMatrix MA, ui ht, ui len )
	{	return cudaMCFCols_absmin( Y, (cfPMatrix)(MA), ht, len );}
inline overror_t cudaMCF_Dia_absmin(  float *h_RetValPtr, cfMatrix MA, ui len )
	{	return cudaMCFDia_absmin(  h_RetValPtr, (cfPMatrix)(MA), len );}
inline overror_t cusdMCF_Dia_absmin(  float *d_RetValPtr, cfMatrix MA, ui len )
	{	return cusdMCFDia_absmin(  d_RetValPtr, (cfPMatrix)(MA), len );}

inline overror_t cudaMCF_Rows_maxReIm( cfVector Y, cfMatrix MA, ui ht, ui len )
	{	return cudaMCFRows_maxReIm( Y, (cfPMatrix)(MA), ht, len );}
inline overror_t cudaMCF_Cols_maxReIm( cfVector Y, cfMatrix MA, ui ht, ui len )
	{	return cudaMCFCols_maxReIm( Y, (cfPMatrix)(MA), ht, len );}
inline overror_t cudaMCF_Dia_maxReIm(  fComplex *h_RetValPtr, cfMatrix MA, ui len )
	{	return cudaMCFDia_maxReIm(  h_RetValPtr, (cfPMatrix)(MA), len );}
inline overror_t cusdMCF_Dia_maxReIm(  fComplex *d_RetValPtr, cfMatrix MA, ui len )
	{	return cusdMCFDia_maxReIm(  d_RetValPtr, (cfPMatrix)(MA), len );}
inline overror_t cudaMCF_Rows_minReIm( cfVector Y, cfMatrix MA, ui ht, ui len )
	{	return cudaMCFRows_minReIm( Y, (cfPMatrix)(MA), ht, len );}
inline overror_t cudaMCF_Cols_minReIm( cfVector Y, cfMatrix MA, ui ht, ui len )
	{	return cudaMCFCols_minReIm( Y, (cfPMatrix)(MA), ht, len );}
inline overror_t cudaMCF_Dia_minReIm(  fComplex *h_RetValPtr, cfMatrix MA, ui len )
	{	return cudaMCFDia_minReIm(  h_RetValPtr, (cfPMatrix)(MA), len );}
inline overror_t cusdMCF_Dia_minReIm(  fComplex *d_RetValPtr, cfMatrix MA, ui len )
	{	return cusdMCFDia_minReIm(  d_RetValPtr, (cfPMatrix)(MA), len );}

inline overror_t cudaMCF_Rows_absmaxReIm( cfVector Y, cfMatrix MA, ui ht, ui len )
	{	return cudaMCFRows_absmaxReIm( Y, (cfPMatrix)(MA), ht, len );}
inline overror_t cudaMCF_Cols_absmaxReIm( cfVector Y, cfMatrix MA, ui ht, ui len )
	{	return cudaMCFCols_absmaxReIm( Y, (cfPMatrix)(MA), ht, len );}
inline overror_t cudaMCF_Dia_absmaxReIm(  fComplex *h_RetValPtr, cfMatrix MA, ui len )
	{	return cudaMCFDia_absmaxReIm(  h_RetValPtr, (cfPMatrix)(MA), len );}
inline overror_t cusdMCF_Dia_absmaxReIm(  fComplex *d_RetValPtr, cfMatrix MA, ui len )
	{	return cusdMCFDia_absmaxReIm(  d_RetValPtr, (cfPMatrix)(MA), len );}
inline overror_t cudaMCF_Rows_absminReIm( cfVector Y, cfMatrix MA, ui ht, ui len )
	{	return cudaMCFRows_absminReIm( Y, (cfPMatrix)(MA), ht, len );}
inline overror_t cudaMCF_Cols_absminReIm( cfVector Y, cfMatrix MA, ui ht, ui len )
	{	return cudaMCFCols_absminReIm( Y, (cfPMatrix)(MA), ht, len );}
inline overror_t cudaMCF_Dia_absminReIm(  fComplex *h_RetValPtr, cfMatrix MA, ui len )
	{	return cudaMCFDia_absminReIm(  h_RetValPtr, (cfPMatrix)(MA), len );}
inline overror_t cusdMCF_Dia_absminReIm(  fComplex *d_RetValPtr, cfMatrix MA, ui len )
	{	return cusdMCFDia_absminReIm(  d_RetValPtr, (cfPMatrix)(MA), len );}

inline overror_t cudaMCF_Rows_cabsmax( cfVector Y, cfMatrix MA, ui ht, ui len )
	{	return cudaMCFRows_cabsmax( Y, (cfPMatrix)(MA), ht, len );}
inline overror_t cudaMCF_Cols_cabsmax( cfVector Y, cfMatrix MA, ui ht, ui len )
	{	return cudaMCFCols_cabsmax( Y, (cfPMatrix)(MA), ht, len );}
inline overror_t cudaMCF_Dia_cabsmax(  fComplex *h_RetValPtr, cfMatrix MA, ui len )
	{	return cudaMCFDia_cabsmax(  h_RetValPtr, (cfPMatrix)(MA), len );}
inline overror_t cusdMCF_Dia_cabsmax(  fComplex *d_RetValPtr, cfMatrix MA, ui len )
	{	return cusdMCFDia_cabsmax(  d_RetValPtr, (cfPMatrix)(MA), len );}
inline overror_t cudaMCF_Rows_cabsmin( cfVector Y, cfMatrix MA, ui ht, ui len )
	{	return cudaMCFRows_cabsmin( Y, (cfPMatrix)(MA), ht, len );}
inline overror_t cudaMCF_Cols_cabsmin( cfVector Y, cfMatrix MA, ui ht, ui len )
	{	return cudaMCFCols_cabsmin( Y, (cfPMatrix)(MA), ht, len );}
inline overror_t cudaMCF_Dia_cabsmin(  fComplex *h_RetValPtr, cfMatrix MA, ui len )
	{	return cudaMCFDia_cabsmin(  h_RetValPtr, (cfPMatrix)(MA), len );}
inline overror_t cusdMCF_Dia_cabsmin(  fComplex *d_RetValPtr, cfMatrix MA, ui len )
	{	return cusdMCFDia_cabsmin(  d_RetValPtr, (cfPMatrix)(MA), len );}

inline overror_t cudaMCF_Rows_sabsmax( cfVector Y, cfMatrix MA, ui ht, ui len )
	{	return cudaMCFRows_sabsmax( Y, (cfPMatrix)(MA), ht, len );}
inline overror_t cudaMCF_Cols_sabsmax( cfVector Y, cfMatrix MA, ui ht, ui len )
	{	return cudaMCFCols_sabsmax( Y, (cfPMatrix)(MA), ht, len );}
inline overror_t cudaMCF_Dia_sabsmax(  fComplex *h_RetValPtr, cfMatrix MA, ui len )
	{	return cudaMCFDia_sabsmax(  h_RetValPtr, (cfPMatrix)(MA), len );}
inline overror_t cusdMCF_Dia_sabsmax(  fComplex *d_RetValPtr, cfMatrix MA, ui len )
	{	return cusdMCFDia_sabsmax(  d_RetValPtr, (cfPMatrix)(MA), len );}
inline overror_t cudaMCF_Rows_sabsmin( cfVector Y, cfMatrix MA, ui ht, ui len )
	{	return cudaMCFRows_sabsmin( Y, (cfPMatrix)(MA), ht, len );}
inline overror_t cudaMCF_Cols_sabsmin( cfVector Y, cfMatrix MA, ui ht, ui len )
	{	return cudaMCFCols_sabsmin( Y, (cfPMatrix)(MA), ht, len );}
inline overror_t cudaMCF_Dia_sabsmin(  fComplex *h_RetValPtr, cfMatrix MA, ui len )
	{	return cudaMCFDia_sabsmin(  h_RetValPtr, (cfPMatrix)(MA), len );}
inline overror_t cusdMCF_Dia_sabsmin(  fComplex *d_RetValPtr, cfMatrix MA, ui len )
	{	return cusdMCFDia_sabsmin(  d_RetValPtr, (cfPMatrix)(MA), len );}

inline overror_t cudaMCF_Rows_sum( cfVector Y, cfMatrix MA, ui ht, ui len )
	{	return cudaMCFRows_sum( Y, (cfPMatrix)(MA), ht, len );}
inline overror_t cudaMCF_Cols_sum( cfVector Y, cfMatrix MA, ui ht, ui len )
	{	return cudaMCFCols_sum( Y, (cfPMatrix)(MA), ht, len );}
inline overror_t cudaMCF_Dia_sum(  fComplex *h_RetValPtr, cfMatrix MA, ui len )
	{	return cudaMCFDia_sum(  h_RetValPtr, (cfPMatrix)(MA), len );}
inline overror_t cusdMCF_Dia_sum(  fComplex *d_RetValPtr, cfMatrix MA, ui len )
	{	return cusdMCFDia_sum(  d_RetValPtr, (cfPMatrix)(MA), len );}
inline overror_t cudaMCF_Rows_prod( cfVector Y, cfMatrix MA, ui ht, ui len )
	{	return cudaMCFRows_prod( Y, (cfPMatrix)(MA), ht, len );}
inline overror_t cudaMCF_Cols_prod( cfVector Y, cfMatrix MA, ui ht, ui len )
	{	return cudaMCFCols_prod( Y, (cfPMatrix)(MA), ht, len );}
inline overror_t cudaMCF_Dia_prod(  fComplex *h_RetValPtr, cfMatrix MA, ui len )
	{	return cudaMCFDia_prod(  h_RetValPtr, (cfPMatrix)(MA), len );}
inline overror_t cusdMCF_Dia_prod(  fComplex *d_RetValPtr, cfMatrix MA, ui len )
	{	return cusdMCFDia_prod(  d_RetValPtr, (cfPMatrix)(MA), len );}

inline overror_t cudaMCF_Rows_runsum( cfMatrix MA, ui ht, ui len )
	{	return cudaMCFRows_runsum( (cfPMatrix)(MA), ht, len );}
inline overror_t cudaMCF_Cols_runsum( cfMatrix MA, ui ht, ui len )
	{	return cudaMCFCols_runsum( (cfPMatrix)(MA), ht, len );}
inline overror_t cudaMCF_Rows_runprod( cfMatrix MA, ui ht, ui len )
	{	return cudaMCFRows_runprod( (cfPMatrix)(MA), ht, len );}
inline overror_t cudaMCF_Cols_runprod( cfMatrix MA, ui ht, ui len )
	{	return cudaMCFCols_runprod( (cfPMatrix)(MA), ht, len );}

inline overror_t cudaMCF_Rows_rotate( cfMatrix MA, ui ht, ui len, ssize_t pos)
	{	return cudaMCFRows_rotate( (cfPMatrix)(MA), ht, len, pos );}
inline overror_t cudaMCF_Cols_rotate( cfMatrix MA, ui ht, ui len, ssize_t pos)
	{	return cudaMCFCols_rotate( (cfPMatrix)(MA), ht, len, pos );}
inline overror_t cudaMCF_Rows_rotate_buf( cfMatrix MA, ui ht, ui len, ssize_t pos, cfMatrix MBuf) 
	{	return cudaMCFRows_rotate_buf( (cfPMatrix)(MA), ht, len, pos, (cfPMatrix)(MBuf) );}
inline overror_t cudaMCF_Cols_rotate_buf( cfMatrix MA, ui ht, ui len, ssize_t pos, cfMatrix MBuf) 
	{	return cudaMCFCols_rotate_buf( (cfPMatrix)(MA), ht, len, pos, (cfPMatrix)(MBuf) );}
inline overror_t cudaMCF_Rows_reflect( cfMatrix MA, ui ht, ui len )
	{	return cudaMCFRows_reflect( (cfPMatrix)(MA), ht, len );}
inline overror_t cudaMCF_Cols_reflect( cfMatrix MA, ui ht, ui len )
	{	return cudaMCFCols_reflect( (cfPMatrix)(MA), ht, len );}
inline overror_t cudaMCF_Rows_rev( cfMatrix MA, ui ht, ui len )
	{	return cudaMCFRows_rev( (cfPMatrix)(MA), ht, len );}
inline overror_t cudaMCF_Cols_rev( cfMatrix MA, ui ht, ui len )
	{	return cudaMCFCols_rev( (cfPMatrix)(MA), ht, len );}


/********  Operations involving two rows or two colums of one matrix  *****/

inline overror_t cudaMCF_Rows_exchange( cfMatrix MA, ui ht, ui len, ui row1, ui row2 )
	{	return cudaMCFRows_exchange( (cfPMatrix)(MA), ht, len, row1, row2 );}
inline overror_t cudaMCF_Cols_exchange( cfMatrix MA, ui ht, ui len, ui col1, ui col2 )
	{	return cudaMCFCols_exchange( (cfPMatrix)(MA), ht, len, col1, col2 );}

inline overror_t cudaMCF_Rows_add( cfMatrix MA, ui ht, ui len, ui destRow, ui srceRow )
	{	return cudaMCFRows_add( (cfPMatrix)(MA), ht, len, destRow, srceRow );}
inline overror_t cudaMCF_Cols_add( cfMatrix MA, ui ht, ui len, ui destCol, ui srceCol )
	{	return cudaMCFCols_add( (cfPMatrix)(MA), ht, len, destCol, srceCol );}
                         /* dest[i] += source[i]  */

inline overror_t cudaMCF_Rows_sub( cfMatrix MA, ui ht, ui len, ui destRow, ui srceRow )
	{	return cudaMCFRows_sub( (cfPMatrix)(MA), ht, len, destRow, srceRow );}
inline overror_t cudaMCF_Cols_sub( cfMatrix MA, ui ht, ui len, ui destCol, ui srceCol )
	{	return cudaMCFCols_sub( (cfPMatrix)(MA), ht, len, destCol, srceCol );}
                         /* dest[i] -= source[i]  */

inline overror_t cudaMCF_Rows_Cadd( cfMatrix MA, ui ht, ui len, ui destRow, ui srceRow, fComplex C )
	{	return cudaMCFRows_Cadd( (cfPMatrix)(MA), ht, len, destRow, srceRow, C );}
inline overror_t cudaMCF_Cols_Cadd( cfMatrix MA, ui ht, ui len, ui destCol, ui srceCol, fComplex C )
	{	return cudaMCFCols_Cadd( (cfPMatrix)(MA), ht, len, destCol, srceCol, C );}
inline overror_t cusdMCF_Rows_Cadd( cfMatrix MA, ui ht, ui len, ui destRow, ui srceRow, fComplex *d_C )
	{	return cusdMCFRows_Cadd( (cfPMatrix)(MA), ht, len, destRow, srceRow, d_C );}
inline overror_t cusdMCF_Cols_Cadd( cfMatrix MA, ui ht, ui len, ui destCol, ui srceCol, fComplex *d_C )
	{	return cusdMCFCols_Cadd( (cfPMatrix)(MA), ht, len, destCol, srceCol, d_C );}
                         /* dest[i] += C * source[i]  */

inline overror_t cudaMCF_Rows_lincomb( cfMatrix MA, ui ht, ui len, ui destRow, fComplex destC, ui srceRow, fComplex srceC )
	{	return cudaMCFRows_lincomb( (cfPMatrix)(MA), ht, len, destRow, destC, srceRow, srceC );}
inline overror_t cudaMCF_Cols_lincomb( cfMatrix MA, ui ht, ui len, ui destCol, fComplex destC, ui srceCol, fComplex srceC )
	{	return cudaMCFCols_lincomb( (cfPMatrix)(MA), ht, len, destCol, destC, srceCol, srceC );}
inline overror_t cusdMCF_Rows_lincomb( cfMatrix MA, ui ht, ui len, ui destRow, fComplex *d_destC, ui srceRow, fComplex *d_srceC )
	{	return cusdMCFRows_lincomb( (cfPMatrix)(MA), ht, len, destRow, d_destC, srceRow, d_srceC );}
inline overror_t cusdMCF_Cols_lincomb( cfMatrix MA, ui ht, ui len, ui destCol, fComplex *d_destC, ui srceCol, fComplex *d_srceC )
	{	return cusdMCFCols_lincomb( (cfPMatrix)(MA), ht, len, destCol, d_destC, srceCol, d_srceC );}
  /*  linear combination: dest[i] = destC * dest[i] + sourceC * source[i] */


/*****************  Transposing and rotating a matrix **********************/

inline overror_t cudaMCF_transpose( cfMatrix MTr, cfMatrix MA, ui htTr, ui lenTr )
	{	return cudaMCFtranspose( (cfPMatrix)(MTr), (cfPMatrix)(MA), htTr, lenTr );}
       /*  dimensions htTr, lenTr are those of the transposed matrix, not of the original!   */
inline overror_t cudaMCF_hermconj( cfMatrix MTr, cfMatrix MA, ui htTr, ui lenTr )
	{	return cudaMCFhermconj( (cfPMatrix)(MTr), (cfPMatrix)(MA), htTr, lenTr );}
inline overror_t cudaMCF_rotate90( cfMatrix MRot, cfMatrix MA, ui htRot, ui lenRot )
	{	return cudaMCFrotate90( (cfPMatrix)(MRot), (cfPMatrix)(MA), htRot, lenRot );}
inline overror_t cudaMCF_rotate180( cfMatrix MRot, cfMatrix MA, ui htRot, ui lenRot )
	{	return cudaVCF_rev( (cfPMatrix)(MRot), (cfPMatrix)(MA), (htRot)*(lenRot) );}
inline overror_t cudaMCF_rotate270( cfMatrix MRot, cfMatrix MA, ui htRot, ui lenRot )
	{	return cudaMCFrotate270( (cfPMatrix)(MRot), (cfPMatrix)(MA), htRot, lenRot );}
inline overror_t cudaMCF_transpose_buf( cfMatrix MTr, cfMatrix MA, ui htTr, ui lenTr, cfMatrix MBuf )
	{	return cudaMCFtranspose_buf( (cfPMatrix)(MTr), (cfPMatrix)(MA), htTr, lenTr, (cfPMatrix)(MBuf) );}


/************************ Matrix Arithmetics *************************/

inline overror_t cudaMCF_addM( cfMatrix MC, cfMatrix MA, cfMatrix MB, ui htA, ui lenA )
	{	return cudaVCF_addV( (cfPMatrix)(MC), (cfPMatrix)(MA), (cfPMatrix)(MB), (htA)*(lenA) );}
inline overror_t cudaMCF_addMT( cfMatrix MC, cfMatrix MA, cfMatrix MB, ui htA, ui lenA )
	{	return cudaMCFaddMT( (cfPMatrix)(MC), (cfPMatrix)(MA), (cfPMatrix)(MB), htA, lenA );}
inline overror_t cudaMCF_subM( cfMatrix MC, cfMatrix MA, cfMatrix MB, ui htA, ui lenA )
	{	return cudaVCF_subV( (cfPMatrix)(MC), (cfPMatrix)(MA), (cfPMatrix)(MB), (htA)*(lenA) );}
inline overror_t cudaMCF_subMT( cfMatrix MC, cfMatrix MA, cfMatrix MB, ui htA, ui lenA )
	{	return cudaMCFsubMT( (cfPMatrix)(MC), (cfPMatrix)(MA), (cfPMatrix)(MB), htA, lenA );}
inline overror_t cudaMCF_subrM( cfMatrix MC, cfMatrix MA, cfMatrix MB, ui htA, ui lenA )
	{	return cudaVCF_subrV( (cfPMatrix)(MC), (cfPMatrix)(MA), (cfPMatrix)(MB), (htA)*(lenA) );}
inline overror_t cudaMCF_subrMT( cfMatrix MC, cfMatrix MA, cfMatrix MB, ui htA, ui lenA )
	{	return cudaMCFsubrMT( (cfPMatrix)(MC), (cfPMatrix)(MA), (cfPMatrix)(MB), htA, lenA );}
inline overror_t cudaMCF_mulC( cfMatrix MB, cfMatrix MA, ui htA, ui lenA, fComplex C )
	{	return cudaVCF_mulC( (cfPMatrix)(MB), (cfPMatrix)(MA), (htA)*(lenA), C );}
inline overror_t cudaMCF_divC( cfMatrix MB, cfMatrix MA, ui htA, ui lenA, fComplex C )
	{	return cudaVCF_divC( (cfPMatrix)(MB), (cfPMatrix)(MA), (htA)*(lenA), C );}
inline overror_t cudaMCF_mulReC( cfMatrix MB, cfMatrix MA, ui htA, ui lenA, float CRe )
	{	return cudaVCF_mulReC( (cfPMatrix)(MB), (cfPMatrix)(MA), (htA)*(lenA), CRe );}
inline overror_t cudaMCF_divReC( cfMatrix MB, cfMatrix MA, ui htA, ui lenA, float CRe )
	{	return cudaVCF_divReC( (cfPMatrix)(MB), (cfPMatrix)(MA), (htA)*(lenA), CRe );}
inline overror_t cusdMCF_mulC( cfMatrix MB, cfMatrix MA, ui htA, ui lenA, fComplex *d_C )
	{	return cusdVCF_mulC( (cfPMatrix)(MB), (cfPMatrix)(MA), (htA)*(lenA), d_C );}
inline overror_t cusdMCF_divC( cfMatrix MB, cfMatrix MA, ui htA, ui lenA, fComplex *d_C )
	{	return cusdVCF_divC( (cfPMatrix)(MB), (cfPMatrix)(MA), (htA)*(lenA), d_C );}
inline overror_t cusdMCF_mulReC( cfMatrix MB, cfMatrix MA, ui htA, ui lenA, float *d_CRe )
	{	return cusdVCF_mulReC( (cfPMatrix)(MB), (cfPMatrix)(MA), (htA)*(lenA), d_CRe );}
inline overror_t cusdMCF_divReC( cfMatrix MB, cfMatrix MA, ui htA, ui lenA, float *d_CRe )
	{	return cusdVCF_divReC( (cfPMatrix)(MB), (cfPMatrix)(MA), (htA)*(lenA), d_CRe );}

inline overror_t cudaMCF_lincomb( cfMatrix MC, cfMatrix MA, cfMatrix MB, ui htA, ui lenA, fComplex CA, fComplex CB )
	{	return cudaVCF_lincomb( (cfPMatrix)(MC), (cfPMatrix)(MA), (cfPMatrix)(MB), (htA)*(lenA), CA, CB );}
inline overror_t cusdMCF_lincomb( cfMatrix MC, cfMatrix MA, cfMatrix MB, ui htA, ui lenA, fComplex *d_CA, fComplex *d_CB )
	{	return cusdVCF_lincomb( (cfPMatrix)(MC), (cfPMatrix)(MA), (cfPMatrix)(MB), (htA)*(lenA), d_CA, d_CB );}

inline overror_t cudaMCF_mulV( cfVector Y, cfMatrix MA, cfVector X, ui htA, ui lenA )
	{	return cudaMCFmulV( Y, (cfPMatrix)(MA), X, htA, lenA );}
             /*  Y = MA * X.  sizX=lenA, sizY=htA;   both X and Y are column-vectors    */
inline overror_t cudaMCF_TmulV( cfVector Y, cfMatrix MA, cfVector X, ui htA, ui lenA )
	{	return cudaMCFTmulV( Y, (cfPMatrix)(MA), X, htA, lenA );}
            /*  Y = MAT * X.  sizX=htA, sizY=lenA;   both X and Y are column-vectors    */
inline overror_t cudaVCF_mulM( cfVector Y, cfVector X, cfMatrix MA, ui htA, ui lenA )
	{	return cudaVCFmulM( Y, X, (cfPMatrix)(MA), htA, lenA );}
            /*  Y = X * MA.  sizX=htA, sizY=lenA;    both X and Y are row-vectors.
							 Mind the prefix: cudaVCF_ (not cudaMCF_)    */
inline overror_t cudaVCF_mulMT( cfVector Y, cfVector X, cfMatrix MA, ui htA, ui lenA )
	{	return cudaVCFmulMT( Y, X, (cfPMatrix)(MA), htA, lenA );}
            /*  Y = X * MAT.  sizX=lenA, sizY=htA;   both X and Y are row-vectors.   */
inline overror_t cudaMCF_mulM( cfMatrix MC, cfMatrix MA, cfMatrix MB, ui htA, ui lenA, ui lenB )
	{	return cudaMCFmulM( (cfPMatrix)(MC), (cfPMatrix)(MA), (cfPMatrix)(MB), htA, lenA, lenB );}
                         /*  MC = MA * MB.  htB=lenA, htC=htA, lenC=lenB */
inline overror_t cudaMCF_mulMT( cfMatrix MC, cfMatrix MA, cfMatrix MB, ui htA, ui lenA, ui htB )
	{	return cudaMCFmulMT( (cfPMatrix)(MC), (cfPMatrix)(MA), (cfPMatrix)(MB), htA, lenA, htB );}
                         /*  MC = MA * MBT.  lenB=lenA, htC=htA, lenC=htB */
inline overror_t cudaMCF_mulMH( cfMatrix MC, cfMatrix MA, cfMatrix MB, ui htA, ui lenA, ui htB )
	{	return cudaMCFmulMH( (cfPMatrix)(MC), (cfPMatrix)(MA), (cfPMatrix)(MB), htA, lenA, htB );}
                         /*  MC = MA * MBH.  lenB=lenA, htC=htA, lenC=htB */
inline overror_t cudaMCF_TmulM( cfMatrix MC, cfMatrix MA, cfMatrix MB, ui htA, ui lenA, ui lenB )
	{	return cudaMCFTmulM( (cfPMatrix)(MC), (cfPMatrix)(MA), (cfPMatrix)(MB), htA, lenA, lenB );}
                         /*  MC = MAT * MB.  htB=htA, htC=lenA, lenC=lenB */
inline overror_t cudaMCF_HmulM( cfMatrix MC, cfMatrix MA, cfMatrix MB, ui htA, ui lenA, ui lenB )
	{	return cudaMCFHmulM( (cfPMatrix)(MC), (cfPMatrix)(MA), (cfPMatrix)(MB), htA, lenA, lenB );}
                         /*  MC = MAH * MB.  htB=htA, htC=lenA, lenC=lenB */
inline overror_t cudaMCF_TmulMT( cfMatrix MC, cfMatrix MA, cfMatrix MB, ui htA, ui lenA, ui htB )
	{	return cudaMCFTmulMT( (cfPMatrix)(MC), (cfPMatrix)(MA), (cfPMatrix)(MB), htA, lenA, htB );}
                         /*  MC = MAT * MBT.  lenB=htA, htC=lenA, lenC=htB */
inline overror_t cudaMCF_TmulMH( cfMatrix MC, cfMatrix MA, cfMatrix MB, ui htA, ui lenA, ui htB )
	{	return cudaMCFTmulMH( (cfPMatrix)(MC), (cfPMatrix)(MA), (cfPMatrix)(MB), htA, lenA, htB );}
                         /*  MC = MAT * MBH.  lenB=htA, htC=lenA, lenC=htB */
inline overror_t cudaMCFdia_mulM(  cfMatrix MC, cfVector MADia, cfMatrix MB, ui htB, ui lenB )
	{	return cudaMCFdiamulM(  (cfPMatrix)(MC), MADia, (cfPMatrix)(MB), htB, lenB );}
inline overror_t cudaMCFdia_mulMT(  cfMatrix MC, cfVector MADia, cfMatrix MB, ui htB, ui lenB )
	{	return cudaMCFdiamulMT(  (cfPMatrix)(MC), MADia, (cfPMatrix)(MB), htB, lenB );}
inline overror_t cudaMCF_mulMdia(  cfMatrix MC, cfMatrix MA, cfVector MBDia, ui htA, ui lenA )
	{	return cudaMCFmulMdia(  (cfPMatrix)(MC), (cfPMatrix)(MA), MBDia, htA, lenA );}
inline overror_t cudaMCF_TmulMdia(  cfMatrix MC, cfMatrix MA, cfVector MBDia, ui htA, ui lenA )
	{	return cudaMCFTmulMdia(  (cfPMatrix)(MC), (cfPMatrix)(MA), MBDia, htA, lenA );}


/***************** Two-Dimensional Fourier-Transform Methods ************/

inline overror_t cudaMCF_FFT( cfMatrix MY, cfMatrix MX, ui ht, ui len, int dir )
	{	return cudaMCFFFT( (cfPMatrix)(MY), (cfPMatrix)(MX), ht, len, dir );}
inline overror_t cudaMCF_Rows_FFT( cfMatrix MY, cfMatrix MX, ui ht, ui len, int dir )
	{	return cudaMCFRows_FFT( (cfPMatrix)(MY), (cfPMatrix)(MX), ht, len, dir );}
inline overror_t cudaMCF_Cols_FFT( cfMatrix MY, cfMatrix MX, ui ht, ui len, int dir )
	{	return cudaMCFCols_FFT( (cfPMatrix)(MY), (cfPMatrix)(MX), ht, len, dir );}
inline overror_t cudaMCF_filter( cfMatrix MY, cfMatrix MX, cfMatrix MCFlt, ui ht, ui len )
	{	return cudaMCFfilter( (cfPMatrix)(MY), (cfPMatrix)(MX), (cfPMatrix)(MCFlt), ht, len );}

/**************************  Input and Output  **************************
	The input/output functions involve memory transfers from device
	to host memory or vice versa. The generic cudaMCF_input/output functions
	allocate their own host buffers, whereas the cudaMCF_xxx_buf functions
	take a user-supplied buffer vector h_Wk (size must be >= ht*len )
	and are much more efficient.                                       */

inline overror_t cudaMCF_fprint( FILE *stream, cfMatrix MA, ui ht, ui len, unsigned linewidth )
	{	return cudaMCFfprint( stream, (cfPMatrix)(MA), ht, len, linewidth ); }
inline overror_t cudaMCF_print( cfMatrix MA, ui ht, ui len )
	{	return cudaMCFfprint( stdout, (cfPMatrix)(MA), ht, len, 80 ); }
inline overror_t cudaMCF_cprint( cfMatrix MA, ui ht, ui len )
	{	return cudaMCFcprint( (cfPMatrix)(MA), ht, len ); }
inline overror_t cudaMCF_fprint_buf( FILE *stream, cfMatrix d_MA, ui ht, ui len, unsigned linewidth, cfVector h_Wk )
	{	return cudaMCFfprint_buf( stream, (cfPMatrix)(d_MA), ht, len, linewidth, h_Wk ); }
inline overror_t cudaMCF_print_buf( cfMatrix d_MA, ui ht, ui len, cfVector h_Wk )
	{	return cudaMCFfprint_buf( stdout, (cfPMatrix)(d_MA), ht, len, 80, h_Wk ); }
inline overror_t cudaMCF_cprint_buf( cfMatrix d_MA, ui ht, ui len, cfVector h_Wk )
	{	return cudaMCFcprint_buf( (cfPMatrix)(d_MA), ht, len, h_Wk ); }
		/*  cudaMCF_print, cudaMCF_cprint usable only for console applications! */
inline overror_t  cudaMCF_write( FILE *stream, cfMatrix MA, ui ht, ui len )
	{	return cudaMCFwrite( stream, (cfPMatrix)(MA), ht, len ); }
inline overror_t cudaMCF_read( cfMatrix MA, ui ht, ui len, FILE *stream )
	{	return cudaMCFread( (cfPMatrix)(MA), ht, len, stream ); }
inline overror_t  cudaMCF_write_buf( FILE *stream, cfMatrix d_MA, ui ht, ui len, cfVector h_Wk )
	{	return cudaMCFwrite_buf( stream, (cfPMatrix)(d_MA), ht, len, h_Wk ); }
inline overror_t cudaMCF_read_buf( cfMatrix d_MA, ui ht, ui len, FILE *stream, cfVector h_Wk )
	{	return cudaMCFread_buf( (cfPMatrix)(d_MA), ht, len, stream, h_Wk ); }
                                   /* write and read in ascii format */
inline overror_t cudaMCF_store( FILE *stream, cfMatrix MA, ui ht, ui len )
{	return cudaVCF_store( stream, (cfPMatrix)(MA), (len)*(ht) ); }
inline overror_t cudaMCF_recall( cfMatrix MA, ui ht, ui len, FILE *stream )
	{	return cudaVCF_recall( (cfPMatrix)(MA), (len)*(ht), stream ); }
inline overror_t cudaMCF_store_buf( FILE *stream, cfMatrix d_MA, ui ht, ui len, cfVector h_Wk )
{	return cudaVCF_store_buf( stream, (cfPMatrix)(d_MA), (len)*(ht), h_Wk ); }
inline overror_t cudaMCF_recall_buf( cfMatrix d_MA, ui ht, ui len, FILE *stream, cfVector h_Wk )
	{	return cudaVCF_recall_buf( (cfPMatrix)(d_MA), (len)*(ht), stream, h_Wk ); }
                                  /* store and recall in binary format */

#else  /* C++ Builder or plain-C: type-cast used to transform cfMatrix into cfPMatrix  */

/***  Addressing single elements of dynamically allocated matrices: ******/

#define cudaMCF_setElement( MA, ht, len, m, n, C ) cudaMCFsetElement( (cfPMatrix)(MA), ht, len, m, n, C )
#define cusdMCF_setElement( MA, ht, len, m, n, C ) cusdMCFsetElement( (cfPMatrix)(MA), ht, len, m, n, C )
#define cudaMCF_getElement( y, MA, ht, len, m, n ) cudaMCFgetElement( y, (cfPMatrix)(MA), ht, len, m, n )
#define cusdMCF_getElement( y, MA, ht, len, m, n ) cusdMCFgetElement( y, (cfPMatrix)(MA), ht, len, m, n )
#define cudaMCF_Pelement( MA, ht, len, m, n )      cudaMCFPelement( (cfPMatrix)(MA), ht, len, m, n )
#define cudaMCF_element( MA, ht, len, m, n )       cudaMCFelement( (cfPMatrix)(MA), ht, len, m, n )

 /****************  Initialization  ****************************************/

#define cudaMCF_equ0( MA, ht, len )            cudaVCF_equ0( (cfPMatrix)(MA), (ht)*(len) )
#define cudaMCF_equ1( MA, len )                cudaMCFequ1( (cfPMatrix)(MA), len )  /* identity matrix */
#define cudaMCF_equm1( MA, len )               cudaMCFequm1( (cfPMatrix)(MA), len )  /* neg. identity matrix */
#define cudaMCF_random( MA, ht, len, seed, Min, Max ) \
                                               cudaVCF_random( (cfPMatrix)(MA), (ht)*(len), seed, Min, Max ) 
#define cudaMCF_outerprod( MA, X, Y, ht, len ) cudaMCFouterprod( (cfPMatrix)(MA), X, Y, ht, len )
                       /* sizX=ht, sizY=len */
#define cudaMCF_Row_equ0( MA, ht, len, iRow ) cudaMCFRow_equ0( (cfPMatrix)(MA), ht, len, iRow )
#define cudaMCF_Col_equ0( MA, ht, len, iCol ) cudaMCFCol_equ0( (cfPMatrix)(MA), ht, len, iCol )
#define cudaMCF_Dia_equ0( MA, len )           cudaMCFDia_equ0( (cfPMatrix)(MA), len )
#define cudaMCF_Row_equC( MA, ht, len, iRow, C ) cudaMCFRow_equC( (cfPMatrix)(MA), ht, len, iRow, C )
#define cudaMCF_Col_equC( MA, ht, len, iCol, C ) cudaMCFCol_equC( (cfPMatrix)(MA), ht, len, iCol, C )
#define cudaMCF_Dia_equC( MA, len, C )           cudaMCFDia_equC( (cfPMatrix)(MA), len, C )
#define cusdMCF_Row_equC( MA, ht, len, iRow, d_CPtr ) cusdMCFRow_equC( (cfPMatrix)(MA), ht, len, iRow, d_CPtr )
#define cusdMCF_Col_equC( MA, ht, len, iCol, d_CPtr ) cusdMCFCol_equC( (cfPMatrix)(MA), ht, len, iCol, d_CPtr )
#define cusdMCF_Dia_equC( MA, len, CPtr )           cusdMCFDia_equC( (cfPMatrix)(MA), len, CPtr )

#define cudaMCF_Row_equV( MA, ht, len, iRow, X ) cudaMCFRow_equV( (cfPMatrix)(MA), ht, len, iRow, X )
#define cudaMCF_Col_equV( MA, ht, len, iCol, X ) cudaMCFCol_equV( (cfPMatrix)(MA), ht, len, iCol, X )
#define cudaMCF_Dia_equV( MA, len, X )           cudaMCFDia_equV( (cfPMatrix)(MA), len, X )

#define cudaMCF_Trd_equM( MA, MTrd, len )    cudaMCFTrd_equM( (cfPMatrix)(MA), (cfPMatrix)(MTrd), len )
#define cudaMCF_Trd_extract( MTrd, MA, len ) cudaMCFTrd_extract( (cfPMatrix)(MTrd), (cfPMatrix)(MA), len )

#define cudaMCF_equM( MB, MA, ht, len )      cudaVCF_equV( (cfPMatrix)(MB), (cfPMatrix)(MA), ((ui)(len))*(ht) )
#define cudaMCF_equMhost( MB, MA, ht, len )  cudaVCF_equVhost( (cfPMatrix)(MB), MA[0], (ht)*(len) )
#define MCF_equMdevice( MB, MA, ht, len )    VCF_equVdevice( MB[0], (cfPMatrix)(MA), (ht)*(len) )
#define cudaMCF_neg( MB, MA, ht, len )       cudaVCF_neg( (cfPMatrix)(MB), (cfPMatrix)(MA), ((ui)(len))*(ht) )
#define cudaMCF_conj( MB, MA, ht, len )      cudaVCF_conj( (cfPMatrix)(MB), (cfPMatrix)(MA), ((ui)(len))*(ht) )

#define cudaMCF_UequL( MA, len ) cudaMCFUequL( (cfPMatrix)(MA), len )
#define cudaMCF_LequU( MA, len ) cudaMCFLequU( (cfPMatrix)(MA), len )
         /* copy lower-diagonal elements into upper-diagonal
           (or vice versa) by index-reflection, so as to
           get a symmetric matrix    */

            /* data-type conversions:  */
#define cudaM_CDtoCF( MCF, MCD, ht, len ) cudaV_CDtoCF( (cfPMatrix)(MCF), (cdPMatrix)(MCD), (ht)*(len) )
#define cudaM_CFtoCD( MCD, MCF, ht, len ) cudaV_CFtoCD( (cdPMatrix)(MCD), (cfPMatrix)(MCF), (ht)*(len) )

#define cudaMF_CtoRe( MY, MCX, ht, len )           cudaVF_CtoRe( (fPMatrix)(MY),  (cfPMatrix)(MCX), (ht)*(len) )
#define cudaMF_CtoIm( MY, MCX, ht, len )           cudaVF_CtoIm( (fPMatrix)(MY),  (cfPMatrix)(MCX), (ht)*(len) )
#define cudaMF_CtoReIm( MYRe, MYIm, MCX, ht, len ) cudaVF_CtoReIm( (fPMatrix)(MYRe), (fPMatrix)(MYIm), (cfPMatrix)(MCX), (ht)*(len) )
#define cudaMF_RetoC( MCY, MX, ht, len )           cudaVF_RetoC( (cfPMatrix)(MCY), (fPMatrix)(MX),  (ht)*(len) )
#define cudaMF_ImtoC( MCY, MX, ht, len )           cudaVF_ImtoC( (cfPMatrix)(MCY), (fPMatrix)(MX),  (ht)*(len) )
#define cudaMF_ReImtoC( MCY, MXRe, MXIm, ht, len ) cudaVF_ReImtoC( (cfPMatrix)(MCY), (fPMatrix)(MXRe), (fPMatrix)(MXIm), (ht)*(len) )

/********  Extracting a submatrix and copying a submatrix back  *********/

#define cudaMCF_submatrix( MSub, subHt, subLen, \
                       MSrce, srceHt, srceLen, \
                       firstRowInCol, sampInCol, firstColInRow, sampInRow ) \
               cudaMCFsubmatrix(  (cfPMatrix)(MSub), subHt, subLen, \
                              (cfPMatrix)(MSrce), srceHt, srceLen, \
                              firstRowInCol, sampInCol, firstColInRow, sampInRow )

#define cudaMCF_submatrix_equM( MDest, destHt, destLen, \
                            firstRowInCol, sampInCol, firstColInRow, sampInRow, \
                            MSrce, srceHt, srceLen ) \
               cudaMCFsubmatrix_equM(  (cfPMatrix)(MDest), destHt, destLen, \
                             firstRowInCol, sampInCol, firstColInRow, sampInRow, \
                             (cfPMatrix)(MSrce), srceHt, srceLen )

#define cudaMCF_equMblock( MSub, subHt, subLen, \
                      MSrce, srceHt, srceLen, \
                      firstRowInCol, firstColInRow ) \
              cudaMCFequMblock(  (cfPMatrix)(MSub), subHt, subLen, \
                             (cfPMatrix)(MSrce), srceHt, srceLen, \
                             firstRowInCol, firstColInRow )

#define cudaMCF_block_equM( MDest, destHt, destLen, \
                       firstRowInCol, firstColInRow, \
                       MSrce, srceHt, srceLen ) \
              cudaMCFblock_equM( (cfPMatrix)(MDest), destHt, destLen, \
                             firstRowInCol, firstColInRow, \
                             (cfPMatrix)(MSrce), srceHt, srceLen )

#define cudaMCF_equMblockT( MSub, subHt, subLen, \
                      MSrce, srceHt, srceLen, \
                      firstRowInCol, firstColInRow ) \
              cudaMCFequMblockT( (cfPMatrix)(MSub), subHt, subLen, \
                             (cfPMatrix)(MSrce), srceHt, srceLen, \
                             firstRowInCol, firstColInRow )

#define cudaMCF_block_equMT( MDest, destHt, destLen, \
                       firstRowInCol, firstColInRow, \
                       MSrce, srceHt, srceLen ) \
              cudaMCFblock_equMT( (cfPMatrix)(MDest), destHt, destLen, \
                             firstRowInCol, firstColInRow, \
                             (cfPMatrix)(MSrce), srceHt, srceLen )

/*****   Extracting a single row or a single column or the diagonal  ******
 *       and storing it into a vector                                     */

#define cudaMCF_Row_extract( Y, MA, ht, len, iRow ) cudaMCFRow_extract( Y, (cfPMatrix)(MA), ht, len, iRow )
#define cudaMCF_Col_extract( Y, MA, ht, len, iCol ) cudaMCFCol_extract( Y, (cfPMatrix)(MA), ht, len, iCol )
#define cudaMCF_Dia_extract( Y, MA, len )           cudaMCFDia_extract( Y, (cfPMatrix)(MA), len )


/**************  Deleting or inserting a row or a column   ***************/

#define cudaMCF_Row_delete( MB, MA, htA, lenA, iRow )    cudaMCFRow_delete( (cfPMatrix)(MB), (cfPMatrix)(MA), htA, lenA, iRow )
#define cudaMCF_Col_delete( MB, MA, htA, lenA, iCol )    cudaMCFCol_delete( (cfPMatrix)(MB), (cfPMatrix)(MA), htA, lenA, iCol )
#define cudaMCF_Row_insert( MB, MA, htB, lenB, iRow, X ) cudaMCFRow_insert( (cfPMatrix)(MB), (cfPMatrix)(MA), htB, lenB, iRow, X )
#define cudaMCF_Col_insert( MB, MA, htB, lenB, iCol, X ) cudaMCFCol_insert( (cfPMatrix)(MB), (cfPMatrix)(MA), htB, lenB, iCol, X )


/*****************    Basic arithmetic operations *********************
                      performed on one single row,
                      or one single column of any matrix,
                      or on the diagonal of a square matrix

    Note: In contrast to the analogous VectorLib functions, the operations
    are performed in-place, i.e. the input matrix itself is changed  */

#define cudaMCF_Row_neg( MA, ht, len, iRow ) cudaMCFRow_neg( (cfPMatrix)(MA), ht, len, iRow )
#define cudaMCF_Col_neg( MA, ht, len, iCol ) cudaMCFCol_neg( (cfPMatrix)(MA), ht, len, iCol )

#define cudaMCF_Row_conj( MA, ht, len, iRow ) cudaMCFRow_conj( (cfPMatrix)(MA), ht, len, iRow )
#define cudaMCF_Col_conj( MA, ht, len, iCol ) cudaMCFCol_conj( (cfPMatrix)(MA), ht, len, iCol )

#define cudaMCF_Row_addC( MA, ht, len, iRow, C ) cudaMCFRow_addC( (cfPMatrix)(MA), ht, len, iRow, C )
#define cudaMCF_Col_addC( MA, ht, len, iCol, C ) cudaMCFCol_addC( (cfPMatrix)(MA), ht, len, iCol, C )
#define cudaMCF_Dia_addC( MA, len, C )           cudaMCFDia_addC( (cfPMatrix)(MA), len, C )

#define cudaMCF_Row_addV( MA, ht, len, iRow, X ) cudaMCFRow_addV( (cfPMatrix)(MA), ht, len, iRow, X )
#define cudaMCF_Col_addV( MA, ht, len, iCol, X ) cudaMCFCol_addV( (cfPMatrix)(MA), ht, len, iCol, X )
#define cudaMCF_Dia_addV( MA, len, X )           cudaMCFDia_addV( (cfPMatrix)(MA), len, X )

#define cudaMCF_Row_subC( MA, ht, len, iRow, C ) cudaMCFRow_subC( (cfPMatrix)(MA), ht, len, iRow, C )
#define cudaMCF_Col_subC( MA, ht, len, iCol, C ) cudaMCFCol_subC( (cfPMatrix)(MA), ht, len, iCol, C )
#define cudaMCF_Dia_subC( MA, len, C )           cudaMCFDia_subC( (cfPMatrix)(MA), len, C )

#define cudaMCF_Row_subV( MA, ht, len, iRow, X ) cudaMCFRow_subV( (cfPMatrix)(MA), ht, len, iRow, X )
#define cudaMCF_Col_subV( MA, ht, len, iCol, X ) cudaMCFCol_subV( (cfPMatrix)(MA), ht, len, iCol, X )
#define cudaMCF_Dia_subV( MA, len, X )           cudaMCFDia_subV( (cfPMatrix)(MA), len, X )

#define cudaMCF_Row_subrC( MA, ht, len, iRow, C ) cudaMCFRow_subrC( (cfPMatrix)(MA), ht, len, iRow, C )
#define cudaMCF_Col_subrC( MA, ht, len, iCol, C ) cudaMCFCol_subrC( (cfPMatrix)(MA), ht, len, iCol, C )
#define cudaMCF_Dia_subrC( MA, len, C )           cudaMCFDia_subrC( (cfPMatrix)(MA), len, C )

#define cudaMCF_Row_subrV( MA, ht, len, iRow, X ) cudaMCFRow_subrV( (cfPMatrix)(MA), ht, len, iRow, X )
#define cudaMCF_Col_subrV( MA, ht, len, iCol, X ) cudaMCFCol_subrV( (cfPMatrix)(MA), ht, len, iCol, X )
#define cudaMCF_Dia_subrV( MA, len, X )           cudaMCFDia_subrV( (cfPMatrix)(MA), len, X )

#define cudaMCF_Row_mulC( MA, ht, len, iRow, C ) cudaMCFRow_mulC( (cfPMatrix)(MA), ht, len, iRow, C )
#define cudaMCF_Col_mulC( MA, ht, len, iCol, C ) cudaMCFCol_mulC( (cfPMatrix)(MA), ht, len, iCol, C )
#define cudaMCF_Dia_mulC( MA, len, C )           cudaMCFDia_mulC( (cfPMatrix)(MA), len, C )

#define cudaMCF_Row_mulV( MA, ht, len, iRow, X ) cudaMCFRow_mulV( (cfPMatrix)(MA), ht, len, iRow, X )
#define cudaMCF_Col_mulV( MA, ht, len, iCol, X ) cudaMCFCol_mulV( (cfPMatrix)(MA), ht, len, iCol, X )
#define cudaMCF_Dia_mulV( MA, len, X )           cudaMCFDia_mulV( (cfPMatrix)(MA), len, X )

#define cudaMCF_Row_divC( MA, ht, len, iRow, C ) cudaMCFRow_divC( (cfPMatrix)(MA), ht, len, iRow, C )
#define cudaMCF_Col_divC( MA, ht, len, iCol, C ) cudaMCFCol_divC( (cfPMatrix)(MA), ht, len, iCol, C )
#define cudaMCF_Dia_divC( MA, len, C )           cudaMCFDia_divC( (cfPMatrix)(MA), len, C )

#define cudaMCF_Row_divV( MA, ht, len, iRow, X ) cudaMCFRow_divV( (cfPMatrix)(MA), ht, len, iRow, X )
#define cudaMCF_Col_divV( MA, ht, len, iCol, X ) cudaMCFCol_divV( (cfPMatrix)(MA), ht, len, iCol, X )
#define cudaMCF_Dia_divV( MA, len, X )           cudaMCFDia_divV( (cfPMatrix)(MA), len, X )

#define cudaMCF_Row_divrC( MA, ht, len, iRow, C ) cudaMCFRow_divrC( (cfPMatrix)(MA), ht, len, iRow, C )
#define cudaMCF_Col_divrC( MA, ht, len, iCol, C ) cudaMCFCol_divrC( (cfPMatrix)(MA), ht, len, iCol, C )
#define cudaMCF_Dia_divrC( MA, len, C )           cudaMCFDia_divrC( (cfPMatrix)(MA), len, C )

#define cudaMCF_Row_divrV( MA, ht, len, iRow, X ) cudaMCFRow_divrV( (cfPMatrix)(MA), ht, len, iRow, X )
#define cudaMCF_Col_divrV( MA, ht, len, iCol, X ) cudaMCFCol_divrV( (cfPMatrix)(MA), ht, len, iCol, X )
#define cudaMCF_Dia_divrV( MA, len, X )           cudaMCFDia_divrV( (cfPMatrix)(MA), len, X )

#define cusdMCF_Row_addC( MA, ht, len, iRow, d_CPtr ) cusdMCFRow_addC( (cfPMatrix)(MA), ht, len, iRow, d_CPtr )
#define cusdMCF_Col_addC( MA, ht, len, iCol, d_CPtr ) cusdMCFCol_addC( (cfPMatrix)(MA), ht, len, iCol, d_CPtr )
#define cusdMCF_Dia_addC( MA, len, d_CPtr )           cusdMCFDia_addC( (cfPMatrix)(MA), len, d_CPtr )
#define cusdMCF_Row_subC( MA, ht, len, iRow, d_CPtr ) cusdMCFRow_subC( (cfPMatrix)(MA), ht, len, iRow, d_CPtr )
#define cusdMCF_Col_subC( MA, ht, len, iCol, d_CPtr ) cusdMCFCol_subC( (cfPMatrix)(MA), ht, len, iCol, d_CPtr )
#define cusdMCF_Dia_subC( MA, len, d_CPtr )           cusdMCFDia_subC( (cfPMatrix)(MA), len, d_CPtr )
#define cusdMCF_Row_subrC( MA, ht, len, iRow, d_CPtr ) cusdMCFRow_subrC( (cfPMatrix)(MA), ht, len, iRow, d_CPtr )
#define cusdMCF_Col_subrC( MA, ht, len, iCol, d_CPtr ) cusdMCFCol_subrC( (cfPMatrix)(MA), ht, len, iCol, d_CPtr )
#define cusdMCF_Dia_subrC( MA, len, d_CPtr )           cusdMCFDia_subrC( (cfPMatrix)(MA), len, d_CPtr )
#define cusdMCF_Row_mulC( MA, ht, len, iRow, d_CPtr ) cusdMCFRow_mulC( (cfPMatrix)(MA), ht, len, iRow, d_CPtr )
#define cusdMCF_Col_mulC( MA, ht, len, iCol, d_CPtr ) cusdMCFCol_mulC( (cfPMatrix)(MA), ht, len, iCol, d_CPtr )
#define cusdMCF_Dia_mulC( MA, len, d_CPtr )           cusdMCFDia_mulC( (cfPMatrix)(MA), len, d_CPtr )
#define cusdMCF_Row_divC( MA, ht, len, iRow, d_CPtr ) cusdMCFRow_divC( (cfPMatrix)(MA), ht, len, iRow, d_CPtr )
#define cusdMCF_Col_divC( MA, ht, len, iCol, d_CPtr ) cusdMCFCol_divC( (cfPMatrix)(MA), ht, len, iCol, d_CPtr )
#define cusdMCF_Dia_divC( MA, len, d_CPtr )           cusdMCFDia_divC( (cfPMatrix)(MA), len, d_CPtr )
#define cusdMCF_Row_divrC( MA, ht, len, iRow, d_CPtr ) cusdMCFRow_divrC( (cfPMatrix)(MA), ht, len, iRow, d_CPtr )
#define cusdMCF_Col_divrC( MA, ht, len, iCol, d_CPtr ) cusdMCFCol_divrC( (cfPMatrix)(MA), ht, len, iCol, d_CPtr )
#define cusdMCF_Dia_divrC( MA, len, d_CPtr )           cusdMCFDia_divrC( (cfPMatrix)(MA), len, d_CPtr )

/******  One-dimensional vector operations **********************
         performed along all rows or all columns simultaneously,
         or along the diagonal of a square matrix                */

#define cudaMCF_Rows_absmax( Y, MA, ht, len )   cudaMCFRows_absmax( Y, (cfPMatrix)(MA), ht, len )
#define cudaMCF_Cols_absmax( Y, MA, ht, len )   cudaMCFCols_absmax( Y, (cfPMatrix)(MA), ht, len )
#define cudaMCF_Dia_absmax( h_RetPtr, MA, len ) cudaMCFDia_absmax( h_RetPtr, (cfPMatrix)(MA), len )
#define cudaMCF_Rows_absmin( Y, MA, ht, len )   cudaMCFRows_absmin( Y, (cfPMatrix)(MA), ht, len )
#define cudaMCF_Cols_absmin( Y, MA, ht, len )   cudaMCFCols_absmin( Y, (cfPMatrix)(MA), ht, len )
#define cudaMCF_Dia_absmin( h_RetPtr, MA, len ) cudaMCFDia_absmin( h_RetPtr, (cfPMatrix)(MA), len )

#define cudaMCF_Rows_maxReIm( Y, MA, ht, len )   cudaMCFRows_maxReIm( Y, (cfPMatrix)(MA), ht, len )
#define cudaMCF_Cols_maxReIm( Y, MA, ht, len )   cudaMCFCols_maxReIm( Y, (cfPMatrix)(MA), ht, len )
#define cudaMCF_Dia_maxReIm( h_RetPtr, MA, len ) cudaMCFDia_maxReIm( h_RetPtr, (cfPMatrix)(MA), len )
#define cudaMCF_Rows_minReIm( Y, MA, ht, len )   cudaMCFRows_minReIm( Y, (cfPMatrix)(MA), ht, len )
#define cudaMCF_Cols_minReIm( Y, MA, ht, len )   cudaMCFCols_minReIm( Y, (cfPMatrix)(MA), ht, len )
#define cudaMCF_Dia_minReIm( h_RetPtr, MA, len ) cudaMCFDia_minReIm( h_RetPtr, (cfPMatrix)(MA), len )

#define cudaMCF_Rows_absmaxReIm( Y, MA, ht, len )   cudaMCFRows_absmaxReIm( Y, (cfPMatrix)(MA), ht, len )
#define cudaMCF_Cols_absmaxReIm( Y, MA, ht, len )   cudaMCFCols_absmaxReIm( Y, (cfPMatrix)(MA), ht, len )
#define cudaMCF_Dia_absmaxReIm( h_RetPtr, MA, len ) cudaMCFDia_absmaxReIm( h_RetPtr, (cfPMatrix)(MA), len )
#define cudaMCF_Rows_absminReIm( Y, MA, ht, len )   cudaMCFRows_absminReIm( Y, (cfPMatrix)(MA), ht, len )
#define cudaMCF_Cols_absminReIm( Y, MA, ht, len )   cudaMCFCols_absminReIm( Y, (cfPMatrix)(MA), ht, len )
#define cudaMCF_Dia_absminReIm( h_RetPtr, MA, len ) cudaMCFDia_absminReIm( h_RetPtr, (cfPMatrix)(MA), len )

#define cudaMCF_Rows_cabsmax( Y, MA, ht, len )   cudaMCFRows_cabsmax( Y, (cfPMatrix)(MA), ht, len )
#define cudaMCF_Cols_cabsmax( Y, MA, ht, len )   cudaMCFCols_cabsmax( Y, (cfPMatrix)(MA), ht, len )
#define cudaMCF_Dia_cabsmax( h_RetPtr, MA, len ) cudaMCFDia_cabsmax( h_RetPtr, (cfPMatrix)(MA), len )
#define cudaMCF_Rows_cabsmin( Y, MA, ht, len )   cudaMCFRows_cabsmin( Y, (cfPMatrix)(MA), ht, len )
#define cudaMCF_Cols_cabsmin( Y, MA, ht, len )   cudaMCFCols_cabsmin( Y, (cfPMatrix)(MA), ht, len )
#define cudaMCF_Dia_cabsmin( h_RetPtr, MA, len ) cudaMCFDia_cabsmin( h_RetPtr, (cfPMatrix)(MA), len )

#define cudaMCF_Rows_sabsmax( Y, MA, ht, len )   cudaMCFRows_sabsmax( Y, (cfPMatrix)(MA), ht, len )
#define cudaMCF_Cols_sabsmax( Y, MA, ht, len )   cudaMCFCols_sabsmax( Y, (cfPMatrix)(MA), ht, len )
#define cudaMCF_Dia_sabsmax( h_RetPtr, MA, len ) cudaMCFDia_sabsmax( h_RetPtr, (cfPMatrix)(MA), len )
#define cudaMCF_Rows_sabsmin( Y, MA, ht, len )   cudaMCFRows_sabsmin( Y, (cfPMatrix)(MA), ht, len )
#define cudaMCF_Cols_sabsmin( Y, MA, ht, len )   cudaMCFCols_sabsmin( Y, (cfPMatrix)(MA), ht, len )
#define cudaMCF_Dia_sabsmin( h_RetPtr, MA, len ) cudaMCFDia_sabsmin( h_RetPtr, (cfPMatrix)(MA), len )

#define cudaMCF_Rows_sum( Y, MA, ht, len )     cudaMCFRows_sum( Y, (cfPMatrix)(MA), ht, len )
#define cudaMCF_Cols_sum( Y, MA, ht, len )     cudaMCFCols_sum( Y, (cfPMatrix)(MA), ht, len )
#define cudaMCF_Dia_sum(  h_RetPtr, MA, len )  cudaMCFDia_sum( h_RetPtr, (cfPMatrix)(MA), len )
#define cudaMCF_Rows_prod( Y, MA, ht, len )    cudaMCFRows_prod( Y, (cfPMatrix)(MA), ht, len )
#define cudaMCF_Cols_prod( Y, MA, ht, len )    cudaMCFCols_prod( Y, (cfPMatrix)(MA), ht, len )
#define cudaMCF_Dia_prod(  h_RetPtr, MA, len ) cudaMCFDia_prod( h_RetPtr, (cfPMatrix)(MA), len )

#define cusdMCF_Dia_absmax( d_RetPtr, MA, len ) cusdMCFDia_absmax( d_RetPtr, (cfPMatrix)(MA), len )
#define cusdMCF_Dia_absmin( d_RetPtr, MA, len ) cusdMCFDia_absmin( d_RetPtr, (cfPMatrix)(MA), len )
#define cusdMCF_Dia_maxReIm( d_RetPtr, MA, len ) cusdMCFDia_maxReIm( d_RetPtr, (cfPMatrix)(MA), len )
#define cusdMCF_Dia_minReIm( d_RetPtr, MA, len ) cusdMCFDia_minReIm( d_RetPtr, (cfPMatrix)(MA), len )
#define cusdMCF_Dia_absmaxReIm( d_RetPtr, MA, len ) cusdMCFDia_absmaxReIm( d_RetPtr, (cfPMatrix)(MA), len )
#define cusdMCF_Dia_absminReIm( d_RetPtr, MA, len ) cusdMCFDia_absminReIm( d_RetPtr, (cfPMatrix)(MA), len )
#define cusdMCF_Dia_cabsmax( d_RetPtr, MA, len ) cusdMCFDia_cabsmax( d_RetPtr, (cfPMatrix)(MA), len )
#define cusdMCF_Dia_cabsmin( d_RetPtr, MA, len ) cusdMCFDia_cabsmin( d_RetPtr, (cfPMatrix)(MA), len )
#define cusdMCF_Dia_sabsmax( d_RetPtr, MA, len ) cusdMCFDia_sabsmax( d_RetPtr, (cfPMatrix)(MA), len )
#define cusdMCF_Dia_sabsmin( d_RetPtr, MA, len ) cusdMCFDia_sabsmin( d_RetPtr, (cfPMatrix)(MA), len )
#define cusdMCF_Dia_sum(  d_RetPtr, MA, len )  cusdMCFDia_sum( d_RetPtr, (cfPMatrix)(MA), len )
#define cusdMCF_Dia_prod(  d_RetPtr, MA, len ) cusdMCFDia_prod( d_RetPtr, (cfPMatrix)(MA), len )

#define cudaMCF_Rows_runsum( MA, ht, len )     cudaMCFRows_runsum( (cfPMatrix)(MA), ht, len )
#define cudaMCF_Cols_runsum( MA, ht, len )     cudaMCFCols_runsum( (cfPMatrix)(MA), ht, len )
#define cudaMCF_Rows_runprod( MA, ht, len )    cudaMCFRows_runprod( (cfPMatrix)(MA), ht, len )
#define cudaMCF_Cols_runprod( MA, ht, len )    cudaMCFCols_runprod( (cfPMatrix)(MA), ht, len )

#define cudaMCF_Rows_rotate( MA, ht, len, pos) cudaMCFRows_rotate( (cfPMatrix)(MA), ht, len, pos )
#define cudaMCF_Cols_rotate( MA, ht, len, pos) cudaMCFCols_rotate( (cfPMatrix)(MA), ht, len, pos )
#define cudaMCF_Rows_rotate_buf( MA, ht, len, pos, MBuf) cudaMCFRows_rotate_buf( (cfPMatrix)(MA), ht, len, pos, (cfPMatrix)(MBuf) )
#define cudaMCF_Cols_rotate_buf( MA, ht, len, pos, MBuf) cudaMCFCols_rotate_buf( (cfPMatrix)(MA), ht, len, pos, (cfPMatrix)(MBuf) )
#define cudaMCF_Rows_reflect( MA, ht, len)     cudaMCFRows_reflect( (cfPMatrix)(MA), ht, len )
#define cudaMCF_Cols_reflect( MA, ht, len)     cudaMCFCols_reflect( (cfPMatrix)(MA), ht, len )
#define cudaMCF_Rows_rev( MA, ht, len)         cudaMCFRows_rev( (cfPMatrix)(MA), ht, len )
#define cudaMCF_Cols_rev( MA, ht, len)         cudaMCFCols_rev( (cfPMatrix)(MA), ht, len )


/********  Operations involving two rows or two colums of one matrix  *****/

#define cudaMCF_Rows_exchange( MA, ht, len, row1, row2 )  cudaMCFRows_exchange( (cfPMatrix)(MA), ht, len, row1, row2 )
#define cudaMCF_Cols_exchange( MA, ht, len, col1, col2 )  cudaMCFCols_exchange( (cfPMatrix)(MA), ht, len, col1, col2 )

#define cudaMCF_Rows_add( MA, ht, len, destRow, srceRow ) cudaMCFRows_add( (cfPMatrix)(MA), ht, len, destRow, srceRow )
#define cudaMCF_Cols_add( MA, ht, len, destCol, srceCol ) cudaMCFCols_add( (cfPMatrix)(MA), ht, len, destCol, srceCol )
                         /* dest[i] += source[i]  */

#define cudaMCF_Rows_sub( MA, ht, len, destRow, srceRow ) cudaMCFRows_sub( (cfPMatrix)(MA), ht, len, destRow, srceRow )
#define cudaMCF_Cols_sub( MA, ht, len, destCol, srceCol ) cudaMCFCols_sub( (cfPMatrix)(MA), ht, len, destCol, srceCol )
                         /* dest[i] -= source[i]  */

#define cudaMCF_Rows_Cadd( MA, ht, len, destRow, srceRow, C ) cudaMCFRows_Cadd( (cfPMatrix)(MA), ht, len, destRow, srceRow, C )
#define cudaMCF_Cols_Cadd( MA, ht, len, destCol, srceCol, C ) cudaMCFCols_Cadd( (cfPMatrix)(MA), ht, len, destCol, srceCol, C )
#define cusdMCF_Rows_Cadd( MA, ht, len, destRow, srceRow, d_CPtr ) cusdMCFRows_Cadd( (cfPMatrix)(MA), ht, len, destRow, srceRow, d_CPtr )
#define cusdMCF_Cols_Cadd( MA, ht, len, destCol, srceCol, d_CPtr ) cusdMCFCols_Cadd( (cfPMatrix)(MA), ht, len, destCol, srceCol, d_CPtr )
                         /* dest[i] += C * source[i]  */

#define cudaMCF_Rows_lincomb( MA, ht, len, destRow, destC, srceRow, srceC ) \
            cudaMCFRows_lincomb( (cfPMatrix)(MA), ht, len, destRow, destC, srceRow, srceC )
#define cudaMCF_Cols_lincomb( MA, ht, len, destCol, destC, srceCol, srceC ) \
            cudaMCFCols_lincomb( (cfPMatrix)(MA), ht, len, destCol, destC, srceCol, srceC )
#define cusdMCF_Rows_lincomb( MA, ht, len, destRow, d_DestCPtr, srceRow, d_SrceCPtr ) \
            cusdMCFRows_lincomb( (cfPMatrix)(MA), ht, len, destRow, d_DestCPtr, srceRow, d_SrceCPtr )
#define cusdMCF_Cols_lincomb( MA, ht, len, d_DestCPtrol, d_DestCPtr, d_SrceCPtrol, d_SrceCPtr ) \
            cusdMCFCols_lincomb( (cfPMatrix)(MA), ht, len, d_DestCPtrol, d_DestCPtr, d_SrceCPtrol, d_SrceCPtr )
  /*  linear combination: dest[i] = destC * dest[i] + sourceC * source[i] */


/*****************  Transposing and rotating a matrix **********************/

#define cudaMCF_transpose( MTr, MA, htTr, lenTr )    cudaMCFtranspose( (cfPMatrix)(MTr), (cfPMatrix)(MA), htTr, lenTr )
       /*  the dimensions htTr, lenTr are those of the transposed matrix,
           not of the original!                */
#define cudaMCF_hermconj( MHConj, MA, htTr, lenTr )  cudaMCFhermconj( (cfPMatrix)(MHConj), (cfPMatrix)(MA), htTr, lenTr )
#define cudaMCF_rotate90( MRot, MA, htRot, lenRot )  cudaMCFrotate90( (cfPMatrix)(MRot), (cfPMatrix)(MA), htRot, lenRot )
#define cudaMCF_rotate180( MRot, MA, htRot, lenRot ) cudaVCF_rev( (cfPMatrix)(MRot), (cfPMatrix)(MA), (htRot)*(lenRot) )
#define cudaMCF_rotate270( MRot, MA, htRot, lenRot ) cudaMCFrotate270( (cfPMatrix)(MRot), (cfPMatrix)(MA), htRot, lenRot )
#define cudaMCF_transpose_buf( MTr, MA, htTr, lenTr, MBuf )    cudaMCFtranspose_buf( (cfPMatrix)(MTr), (cfPMatrix)(MA), htTr, lenTr, (cfPMatrix)(MBuf) )

/************************ Matrix Arithmetics *************************/

#define cudaMCF_addM( MC, MA, MB, htA, lenA )    cudaVCF_addV( (cfPMatrix)(MC), (cfPMatrix)(MA), (cfPMatrix)(MB), (htA)*(lenA) )
#define cudaMCF_addMT( MC, MA, MB, htA, lenA )   cudaMCFaddMT( (cfPMatrix)(MC), (cfPMatrix)(MA), (cfPMatrix)(MB), htA, lenA )
#define cudaMCF_subM( MC, MA, MB, htA, lenA )    cudaVCF_subV( (cfPMatrix)(MC), (cfPMatrix)(MA), (cfPMatrix)(MB), (htA)*(lenA) )
#define cudaMCF_subMT( MC, MA, MB, htA, lenA )   cudaMCFsubMT( (cfPMatrix)(MC), (cfPMatrix)(MA), (cfPMatrix)(MB), htA, lenA )
#define cudaMCF_subrMT( MC, MA, MB, htA, lenA )  cudaMCFsubrMT( (cfPMatrix)(MC), (cfPMatrix)(MA), (cfPMatrix)(MB), htA, lenA )
#define cudaMCF_mulC( MB, MA, htA, lenA, C )     cudaVCF_mulC( (cfPMatrix)(MB), (cfPMatrix)(MA), (htA)*(lenA), C )
#define cudaMCF_divC( MB, MA, htA, lenA, C )     cudaVCF_divC( (cfPMatrix)(MB), (cfPMatrix)(MA), (htA)*(lenA), C )
#define cudaMCF_mulReC( MB, MA, htA, lenA, CRe ) cudaVCF_mulReC( (cfPMatrix)(MB), (cfPMatrix)(MA), (htA)*(lenA), CRe )
#define cudaMCF_divReC( MB, MA, htA, lenA, CRe ) cudaVCF_divReC( (cfPMatrix)(MB), (cfPMatrix)(MA), (htA)*(lenA), CRe )
#define cudaMCF_lincomb( MC, MA, MB, htA, lenA, CA, CB ) \
                 cudaVCF_lincomb( (cfPMatrix)(MC), (cfPMatrix)(MA), (cfPMatrix)(MB), (htA)*(lenA), CA, CB )

#define cusdMCF_mulC( MB, MA, htA, lenA, d_CPtr )     cusdVCF_mulC( (cfPMatrix)(MB), (cfPMatrix)(MA), (htA)*(lenA), d_CPtr )
#define cusdMCF_divC( MB, MA, htA, lenA, d_CPtr )     cusdVCF_divC( (cfPMatrix)(MB), (cfPMatrix)(MA), (htA)*(lenA), d_CPtr )
#define cusdMCF_mulReC( MB, MA, htA, lenA, d_CRePtr ) cusdVCF_mulReC( (cfPMatrix)(MB), (cfPMatrix)(MA), (htA)*(lenA), d_CRePtr )
#define cusdMCF_divReC( MB, MA, htA, lenA, d_CRePtr ) cusdVCF_divReC( (cfPMatrix)(MB), (cfPMatrix)(MA), (htA)*(lenA), d_CRePtr )
#define cusdMCF_lincomb( MC, MA, MB, htA, lenA, d_CAPtr, d_CBPtr ) \
                 cusdVCF_lincomb( (cfPMatrix)(MC), (cfPMatrix)(MA), (cfPMatrix)(MB), (htA)*(lenA), d_CAPtr, d_CBPtr )

#define cudaMCF_mulV( Y, MA, X, htA, lenA )      cudaMCFmulV( Y, (cfPMatrix)(MA), X, htA, lenA )
                  /*  Y = MA * X.  sizX=lenA, sizY=htA;  both X and Y are column-vectors    */
#define cudaMCF_TmulV( Y, MA, X, htA, lenA )      cudaMCFTmulV( Y, (cfPMatrix)(MA), X, htA, lenA )
                  /*  Y = MAT * X.  sizX=htA, sizY=lenA; both X and Y are column-vectors    */
#define cudaVCF_mulM( Y, X, MA, htA, lenA )       cudaVCFmulM( Y, X, (cfPMatrix)(MA), htA, lenA )
                  /*  Y = X * MA.  sizX=htA, sizY=lenA;  both X and Y are row-vectors.
                             Mind the prefix: cudaVCF_ (not cudaMCF_)    */
#define cudaVCF_mulMT( Y, X, MA, htA, lenA )      cudaVCFmulMT( Y, X, (cfPMatrix)(MA), htA, lenA )
                 /*  Y = X * MAT.  sizX=lenA, sizY=htA;  both X and Y are row-vectors.   */
#define cudaMCF_mulM( MC, MA, MB, htA, lenA, lenB ) cudaMCFmulM( (cfPMatrix)(MC), (cfPMatrix)(MA), (cfPMatrix)(MB), htA, lenA, lenB )
                         /*  MC = MA * MB.  htB=lenA, htC=htA, lenC=lenB */
#define cudaMCF_mulMT( MC, MA, MB, htA, lenA, htB ) cudaMCFmulMT( (cfPMatrix)(MC), (cfPMatrix)(MA), (cfPMatrix)(MB), htA, lenA, htB )
                         /*  MC = MA * MBT.  lenB=lenA, htC=htA, lenC=htB */
#define cudaMCF_mulMH( MC, MA, MB, htA, lenA, htB ) cudaMCFmulMH( (cfPMatrix)(MC), (cfPMatrix)(MA), (cfPMatrix)(MB), htA, lenA, htB )
                         /*  MC = MA * MBH.  lenB=lenA, htC=htA, lenC=htB */
#define cudaMCF_TmulM( MC, MA, MB, htA, lenA, lenB ) cudaMCFTmulM( (cfPMatrix)(MC), (cfPMatrix)(MA), (cfPMatrix)(MB), htA, lenA, lenB )
                         /*  MC = MAT * MB.  htB=htA, htC=lenA, lenC=lenB */
#define cudaMCF_HmulM( MC, MA, MB, htA, lenA, lenB ) cudaMCFHmulM( (cfPMatrix)(MC), (cfPMatrix)(MA), (cfPMatrix)(MB), htA, lenA, lenB )
                         /*  MC = MAH * MB.  htB=htA, htC=lenA, lenC=lenB */
#define cudaMCF_TmulMT( MC, MA, MB, htA, lenA, htB ) cudaMCFTmulMT( (cfPMatrix)(MC), (cfPMatrix)(MA), (cfPMatrix)(MB), htA, lenA, htB )
                         /*  MC = MAT * MBT.  lenB=htA, htC=lenA, lenC=htB */
#define cudaMCF_TmulMH( MC, MA, MB, htA, lenA, htB )  cudaMCFTmulMH( (cfPMatrix)(MC), (cfPMatrix)(MA), (cfPMatrix)(MB), htA, lenA, htB )
                         /*  MC = MAT * MBH.  lenB=htA, htC=lenA, lenC=htB */
#define cudaMCFdia_mulM(  MC, MADia, MB, htB, lenB )  cudaMCFdiamulM(  (cfPMatrix)(MC), MADia, (cfPMatrix)(MB), htB, lenB )
#define cudaMCFdia_mulMT( MC, MADia, MB, htB, lenB )  cudaMCFdiamulMT( (cfPMatrix)(MC), MADia, (cfPMatrix)(MB), htB, lenB )
#define cudaMCF_mulMdia(  MC, MA, MBDia, htA, lenA )  cudaMCFmulMdia(  (cfPMatrix)(MC), (cfPMatrix)(MA), MBDia, htA, lenA )
#define cudaMCF_TmulMdia( MC, MA, MBDia, htA, lenA )  cudaMCFTmulMdia( (cfPMatrix)(MC), (cfPMatrix)(MA), MBDia, htA, lenA )


/***************** Two-Dimensional Fourier-Transform Methods ************/

#define cudaMCF_FFT( MY, MX, ht, len, dir )     cudaMCFFFT( (cfPMatrix)(MY), (cfPMatrix)(MX), ht, len, dir )
#define cudaMCF_Rows_FFT( MY, MX, ht, len, dir) cudaMCFRows_FFT( (cfPMatrix)(MY), (cfPMatrix)(MX), ht, len, dir )
#define cudaMCF_Cols_FFT( MY, MX, ht, len, dir) cudaMCFCols_FFT( (cfPMatrix)(MY), (cfPMatrix)(MX), ht, len, dir )
#define cudaMCF_filter( MY, MX, MFlt, ht, len ) cudaMCFfilter( (cfPMatrix)(MY), (cfPMatrix)(MX), (cfPMatrix)(MFlt), ht, len )

/**************************  Input and Output  **************************
	The input/output functions involve memory transfers from device
	to host memory or vice versa. The generic cudaMCF_input/output functions
	allocate their own host buffers, whereas the cudaMCF_xxx_buf functions
	take a user-supplied buffer vector h_Wk (size must be >= ht*len )
	and are much more efficient.                                       */

#define cudaMCF_fprint( stream, MA, ht, len, linewidth ) \
                    cudaMCFfprint( stream, (cfPMatrix)(MA), ht, len, linewidth )
#define cudaMCF_print( MA, ht, len )  cudaMCFfprint( stdout, (cfPMatrix)(MA), ht, len, 80 )
#define cudaMCF_cprint( MA, ht, len ) cudaMCFcprint( (cfPMatrix)(MA), ht, len )
#define cudaMCF_fprint_buf( stream, MA, ht, len, linewidth, h_Wk ) \
                    cudaMCFfprint_buf( stream, (cfPMatrix)(MA), ht, len, linewidth, h_Wk )
#define cudaMCF_print_buf( MA, ht, len )  cudaMCFfprint_buf( stdout, (cfPMatrix)(MA), ht, len, 80, h_Wk )
#define cudaMCF_cprint_buf( MA, ht, len ) cudaMCFcprint_buf( (cfPMatrix)(MA), ht, len, h_Wk )
  /*  cudaMCF_print, cudaMCF_cprint usable only for console applications! */
#define cudaMCF_write( str, MA, ht, len )   cudaMCFwrite( str, (cfPMatrix)(MA), ht, len )
#define cudaMCF_read( MA, ht, len, str )    cudaMCFread( (cfPMatrix)(MA), ht, len, str )
#define cudaMCF_write_buf( str, MA, ht, len, h_Wk )   cudaMCFwrite_buf( str, (cfPMatrix)(MA), ht, len, h_Wk )
#define cudaMCF_read_buf( MA, ht, len, str, h_Wk )    cudaMCFread_buf( (cfPMatrix)(MA), ht, len, str, h_Wk )
                                   /* write and read in ascii format */
#define cudaMCF_store( str, MA, ht, len )   cudaVCF_store( str, (cfPMatrix)(MA), (len)*(ht) )
#define cudaMCF_recall( MA, ht, len, str)   cudaVCF_recall( (cfPMatrix)(MA), (len)*(ht), str)
#define cudaMCF_store_buf( str, MA, ht, len, h_Wk )   cudaVCF_store_buf( str, (cfPMatrix)(MA), (len)*(ht), h_Wk )
#define cudaMCF_recall_buf( MA, ht, len, str, h_Wk)   cudaVCF_recall_buf( (cfPMatrix)(MA), (len)*(ht), str, h_Wk )
                                  /* store and recall in binary format */

#endif /* C++ or plain-C declarations of functions working on device memory */


/*******************  Functions working on host memory: **********************
 *                                                                           *
 *	MFcu_func		(working on matrices in host memory, input type fMatrix, *
 *	scalar parameters on host and passed by value)                           *
 *****************************************************************************/ 

 /****************  Initialization  ****************************************/

#define MCFcu_equ0( MA, ht, len )            VCFcu_equ0( (MA)[0], (ht)*(len) )
#define MCFcu_equ1( MA, len )                MCFcuequ1( (MA)[0], len )  /* identity matrix */
#define MCFcu_equm1( MA, len )               MCFcuequm1( (MA)[0], len )  /* neg. identity matrix */
#define MCFcu_random( MA, ht, len, seed, Min, Max ) \
                                               VCFcu_random( (MA)[0], (ht)*(len), seed, Min, Max ) 
#define MCFcu_outerprod( MA, X, Y, ht, len ) MCFcuouterprod( (MA)[0], X, Y, ht, len )
                       /* sizX=ht, sizY=len */
#define MCFcu_Row_equ0( MA, ht, len, iRow ) MCFcuRow_equ0( (MA)[0], ht, len, iRow )
#define MCFcu_Col_equ0( MA, ht, len, iCol ) MCFcuCol_equ0( (MA)[0], ht, len, iCol )
#define MCFcu_Dia_equ0( MA, len )           MCFcuDia_equ0( (MA)[0], len )
#define MCFcu_Row_equC( MA, ht, len, iRow, C ) MCFcuRow_equC( (MA)[0], ht, len, iRow, C )
#define MCFcu_Col_equC( MA, ht, len, iCol, C ) MCFcuCol_equC( (MA)[0], ht, len, iCol, C )
#define MCFcu_Dia_equC( MA, len, C )           MCFcuDia_equC( (MA)[0], len, C )

#define MCFcu_Row_equV( MA, ht, len, iRow, X ) MCFcuRow_equV( (MA)[0], ht, len, iRow, X )
#define MCFcu_Col_equV( MA, ht, len, iCol, X ) MCFcuCol_equV( (MA)[0], ht, len, iCol, X )
#define MCFcu_Dia_equV( MA, len, X )           MCFcuDia_equV( (MA)[0], len, X )

#define MCFcu_Trd_equM( MA, MTrd, len )    MCFcuTrd_equM( (MA)[0], (MTrd)[0], len )
#define MCFcu_Trd_extract( MTrd, MA, len ) MCFcuTrd_extract( (MTrd)[0], (MA)[0], len )

#define MCFcu_equM( MB, MA, ht, len )      VCFcu_equV( (MB)[0], (MA)[0], ((ui)(len))*(ht) )
#define MCFcu_neg( MB, MA, ht, len )       VCFcu_neg( (MB)[0], (MA)[0], ((ui)(len))*(ht) )
#define MCFcu_conj( MB, MA, ht, len )      VCFcu_conj( (MB)[0], (MA)[0], ((ui)(len))*(ht) )

#define MCFcu_UequL( MA, len ) MCFcuUequL( (MA)[0], len )
#define MCFcu_LequU( MA, len ) MCFcuLequU( (MA)[0], len )
         /* copy lower-diagonal elements into upper-diagonal
           (or vice versa) by index-reflection, so as to
           get a symmetric matrix    */

            /* data-type conversions:  */
#define Mcu_CDtoCF( MCF, MCD, ht, len ) Vcu_CDtoCF( (MCF)[0], (MCD)[0], (ht)*(len) )
#define Mcu_CFtoCD( MCD, MCF, ht, len ) Vcu_CFtoCD( (MCD)[0], (MCF)[0], (ht)*(len) )

#define MFcu_CtoRe( MY, MCX, ht, len )           VFcu_CtoRe( (MY)[0],  (MCX)[0], (ht)*(len) )
#define MFcu_CtoIm( MY, MCX, ht, len )           VFcu_CtoIm( (MY)[0],  (MCX)[0], (ht)*(len) )
#define MFcu_CtoReIm( MYRe, MYIm, MCX, ht, len ) VFcu_CtoReIm( (MYRe)[0], (MYIm)[0], (MCX)[0], (ht)*(len) )
#define MFcu_RetoC( MCY, MX, ht, len )           VFcu_RetoC( (MCY)[0], (MX)[0],  (ht)*(len) )
#define MFcu_ImtoC( MCY, MX, ht, len )           VFcu_ImtoC( (MCY)[0], (MX)[0],  (ht)*(len) )
#define MFcu_ReImtoC( MCY, MXRe, MXIm, ht, len ) VFcu_ReImtoC( (MCY)[0], (MXRe)[0], (MXIm)[0], (ht)*(len) )

/********  Extracting a submatrix and copying a submatrix back  *********/

#define MCFcu_submatrix( MSub, subHt, subLen, \
                       MSrce, srceHt, srceLen, \
                       firstRowInCol, sampInCol, firstColInRow, sampInRow ) \
               MCFcusubmatrix(  (MSub)[0], subHt, subLen, \
                              (MSrce)[0], srceHt, srceLen, \
                              firstRowInCol, sampInCol, firstColInRow, sampInRow )

#define MCFcu_submatrix_equM( MDest, destHt, destLen, \
                            firstRowInCol, sampInCol, firstColInRow, sampInRow, \
                            MSrce, srceHt, srceLen ) \
               MCFcusubmatrix_equM(  (MDest)[0], destHt, destLen, \
                             firstRowInCol, sampInCol, firstColInRow, sampInRow, \
                             (MSrce)[0], srceHt, srceLen )

#define MCFcu_equMblock( MSub, subHt, subLen, \
                      MSrce, srceHt, srceLen, \
                      firstRowInCol, firstColInRow ) \
              MCFcuequMblock(  (MSub)[0], subHt, subLen, \
                             (MSrce)[0], srceHt, srceLen, \
                             firstRowInCol, firstColInRow )

#define MCFcu_block_equM( MDest, destHt, destLen, \
                       firstRowInCol, firstColInRow, \
                       MSrce, srceHt, srceLen ) \
              MCFcublock_equM( (MDest)[0], destHt, destLen, \
                             firstRowInCol, firstColInRow, \
                             (MSrce)[0], srceHt, srceLen )

#define MCFcu_equMblockT( MSub, subHt, subLen, \
                      MSrce, srceHt, srceLen, \
                      firstRowInCol, firstColInRow ) \
              MCFcuequMblockT( (MSub)[0], subHt, subLen, \
                             (MSrce)[0], srceHt, srceLen, \
                             firstRowInCol, firstColInRow )

#define MCFcu_block_equMT( MDest, destHt, destLen, \
                       firstRowInCol, firstColInRow, \
                       MSrce, srceHt, srceLen ) \
              MCFcublock_equMT( (MDest)[0], destHt, destLen, \
                             firstRowInCol, firstColInRow, \
                             (MSrce)[0], srceHt, srceLen )

/*****   Extracting a single row or a single column or the diagonal  ******
 *       and storing it into a vector                                     */

#define MCFcu_Row_extract( Y, MA, ht, len, iRow ) MCFcuRow_extract( Y, (MA)[0], ht, len, iRow )
#define MCFcu_Col_extract( Y, MA, ht, len, iCol ) MCFcuCol_extract( Y, (MA)[0], ht, len, iCol )
#define MCFcu_Dia_extract( Y, MA, len )           MCFcuDia_extract( Y, (MA)[0], len )


/**************  Deleting or inserting a row or a column   ***************/

#define MCFcu_Row_delete( MB, MA, htA, lenA, iRow )    MCFcuRow_delete( (MB)[0], (MA)[0], htA, lenA, iRow )
#define MCFcu_Col_delete( MB, MA, htA, lenA, iCol )    MCFcuCol_delete( (MB)[0], (MA)[0], htA, lenA, iCol )
#define MCFcu_Row_insert( MB, MA, htB, lenB, iRow, X ) MCFcuRow_insert( (MB)[0], (MA)[0], htB, lenB, iRow, X )
#define MCFcu_Col_insert( MB, MA, htB, lenB, iCol, X ) MCFcuCol_insert( (MB)[0], (MA)[0], htB, lenB, iCol, X )


/*****************    Basic arithmetic operations *********************
                      performed on one single row,
                      or one single column of any matrix,
                      or on the diagonal of a square matrix

    Note: In contrast to the analogous VectorLib functions, the operations
    are performed in-place, i.e. the input matrix itself is changed  */

#define MCFcu_Row_neg( MA, ht, len, iRow ) MCFcuRow_neg( (MA)[0], ht, len, iRow )
#define MCFcu_Col_neg( MA, ht, len, iCol ) MCFcuCol_neg( (MA)[0], ht, len, iCol )

#define MCFcu_Row_conj( MA, ht, len, iRow ) MCFcuRow_conj( (MA)[0], ht, len, iRow )
#define MCFcu_Col_conj( MA, ht, len, iCol ) MCFcuCol_conj( (MA)[0], ht, len, iCol )

#define MCFcu_Row_addC( MA, ht, len, iRow, C ) MCFcuRow_addC( (MA)[0], ht, len, iRow, C )
#define MCFcu_Col_addC( MA, ht, len, iCol, C ) MCFcuCol_addC( (MA)[0], ht, len, iCol, C )
#define MCFcu_Dia_addC( MA, len, C )           MCFcuDia_addC( (MA)[0], len, C )

#define MCFcu_Row_addV( MA, ht, len, iRow, X ) MCFcuRow_addV( (MA)[0], ht, len, iRow, X )
#define MCFcu_Col_addV( MA, ht, len, iCol, X ) MCFcuCol_addV( (MA)[0], ht, len, iCol, X )
#define MCFcu_Dia_addV( MA, len, X )           MCFcuDia_addV( (MA)[0], len, X )

#define MCFcu_Row_subC( MA, ht, len, iRow, C ) MCFcuRow_subC( (MA)[0], ht, len, iRow, C )
#define MCFcu_Col_subC( MA, ht, len, iCol, C ) MCFcuCol_subC( (MA)[0], ht, len, iCol, C )
#define MCFcu_Dia_subC( MA, len, C )           MCFcuDia_subC( (MA)[0], len, C )

#define MCFcu_Row_subV( MA, ht, len, iRow, X ) MCFcuRow_subV( (MA)[0], ht, len, iRow, X )
#define MCFcu_Col_subV( MA, ht, len, iCol, X ) MCFcuCol_subV( (MA)[0], ht, len, iCol, X )
#define MCFcu_Dia_subV( MA, len, X )           MCFcuDia_subV( (MA)[0], len, X )

#define MCFcu_Row_subrC( MA, ht, len, iRow, C ) MCFcuRow_subrC( (MA)[0], ht, len, iRow, C )
#define MCFcu_Col_subrC( MA, ht, len, iCol, C ) MCFcuCol_subrC( (MA)[0], ht, len, iCol, C )
#define MCFcu_Dia_subrC( MA, len, C )           MCFcuDia_subrC( (MA)[0], len, C )

#define MCFcu_Row_subrV( MA, ht, len, iRow, X ) MCFcuRow_subrV( (MA)[0], ht, len, iRow, X )
#define MCFcu_Col_subrV( MA, ht, len, iCol, X ) MCFcuCol_subrV( (MA)[0], ht, len, iCol, X )
#define MCFcu_Dia_subrV( MA, len, X )           MCFcuDia_subrV( (MA)[0], len, X )

#define MCFcu_Row_mulC( MA, ht, len, iRow, C ) MCFcuRow_mulC( (MA)[0], ht, len, iRow, C )
#define MCFcu_Col_mulC( MA, ht, len, iCol, C ) MCFcuCol_mulC( (MA)[0], ht, len, iCol, C )
#define MCFcu_Dia_mulC( MA, len, C )           MCFcuDia_mulC( (MA)[0], len, C )

#define MCFcu_Row_mulV( MA, ht, len, iRow, X ) MCFcuRow_mulV( (MA)[0], ht, len, iRow, X )
#define MCFcu_Col_mulV( MA, ht, len, iCol, X ) MCFcuCol_mulV( (MA)[0], ht, len, iCol, X )
#define MCFcu_Dia_mulV( MA, len, X )           MCFcuDia_mulV( (MA)[0], len, X )

#define MCFcu_Row_divC( MA, ht, len, iRow, C ) MCFcuRow_divC( (MA)[0], ht, len, iRow, C )
#define MCFcu_Col_divC( MA, ht, len, iCol, C ) MCFcuCol_divC( (MA)[0], ht, len, iCol, C )
#define MCFcu_Dia_divC( MA, len, C )           MCFcuDia_divC( (MA)[0], len, C )

#define MCFcu_Row_divV( MA, ht, len, iRow, X ) MCFcuRow_divV( (MA)[0], ht, len, iRow, X )
#define MCFcu_Col_divV( MA, ht, len, iCol, X ) MCFcuCol_divV( (MA)[0], ht, len, iCol, X )
#define MCFcu_Dia_divV( MA, len, X )           MCFcuDia_divV( (MA)[0], len, X )

#define MCFcu_Row_divrC( MA, ht, len, iRow, C ) MCFcuRow_divrC( (MA)[0], ht, len, iRow, C )
#define MCFcu_Col_divrC( MA, ht, len, iCol, C ) MCFcuCol_divrC( (MA)[0], ht, len, iCol, C )
#define MCFcu_Dia_divrC( MA, len, C )           MCFcuDia_divrC( (MA)[0], len, C )

#define MCFcu_Row_divrV( MA, ht, len, iRow, X ) MCFcuRow_divrV( (MA)[0], ht, len, iRow, X )
#define MCFcu_Col_divrV( MA, ht, len, iCol, X ) MCFcuCol_divrV( (MA)[0], ht, len, iCol, X )
#define MCFcu_Dia_divrV( MA, len, X )           MCFcuDia_divrV( (MA)[0], len, X )


/******  One-dimensional vector operations **********************
         performed along all rows or all columns simultaneously,
         or along the diagonal of a square matrix                */

#define MCFcu_Rows_absmax( Y, MA, ht, len )  MCFcuRows_absmax( Y, (MA)[0], ht, len )
#define MCFcu_Cols_absmax( Y, MA, ht, len )  MCFcuCols_absmax( Y, (MA)[0], ht, len )
#define MCFcu_Dia_absmax( MA, len )          MCFcuDia_absmax( (MA)[0], len )
#define MCFcu_Rows_absmin( Y, MA, ht, len )  MCFcuRows_absmin( Y, (MA)[0], ht, len )
#define MCFcu_Cols_absmin( Y, MA, ht, len )  MCFcuCols_absmin( Y, (MA)[0], ht, len )
#define MCFcu_Dia_absmin( MA, len )          MCFcuDia_absmin( (MA)[0], len )

#define MCFcu_Rows_maxReIm( Y, MA, ht, len ) MCFcuRows_maxReIm( Y, (MA)[0], ht, len )
#define MCFcu_Cols_maxReIm( Y, MA, ht, len ) MCFcuCols_maxReIm( Y, (MA)[0], ht, len )
#define MCFcu_Dia_maxReIm( MA, len )         MCFcuDia_maxReIm( (MA)[0], len )
#define MCFcu_Rows_minReIm( Y, MA, ht, len ) MCFcuRows_minReIm( Y, (MA)[0], ht, len )
#define MCFcu_Cols_minReIm( Y, MA, ht, len ) MCFcuCols_minReIm( Y, (MA)[0], ht, len )
#define MCFcu_Dia_minReIm( MA, len )         MCFcuDia_minReIm( (MA)[0], len )

#define MCFcu_Rows_absmaxReIm( Y, MA, ht, len ) MCFcuRows_absmaxReIm( Y, (MA)[0], ht, len )
#define MCFcu_Cols_absmaxReIm( Y, MA, ht, len ) MCFcuCols_absmaxReIm( Y, (MA)[0], ht, len )
#define MCFcu_Dia_absmaxReIm( MA, len )         MCFcuDia_absmaxReIm( (MA)[0], len )
#define MCFcu_Rows_absminReIm( Y, MA, ht, len ) MCFcuRows_absminReIm( Y, (MA)[0], ht, len )
#define MCFcu_Cols_absminReIm( Y, MA, ht, len ) MCFcuCols_absminReIm( Y, (MA)[0], ht, len )
#define MCFcu_Dia_absminReIm( MA, len )         MCFcuDia_absminReIm( (MA)[0], len )

#define MCFcu_Rows_cabsmax( Y, MA, ht, len ) MCFcuRows_cabsmax( Y, (MA)[0], ht, len )
#define MCFcu_Cols_cabsmax( Y, MA, ht, len ) MCFcuCols_cabsmax( Y, (MA)[0], ht, len )
#define MCFcu_Dia_cabsmax( MA, len )         MCFcuDia_cabsmax( (MA)[0], len )
#define MCFcu_Rows_cabsmin( Y, MA, ht, len ) MCFcuRows_cabsmin( Y, (MA)[0], ht, len )
#define MCFcu_Cols_cabsmin( Y, MA, ht, len ) MCFcuCols_cabsmin( Y, (MA)[0], ht, len )
#define MCFcu_Dia_cabsmin( MA, len )         MCFcuDia_cabsmin( (MA)[0], len )

#define MCFcu_Rows_sabsmax( Y, MA, ht, len ) MCFcuRows_sabsmax( Y, (MA)[0], ht, len )
#define MCFcu_Cols_sabsmax( Y, MA, ht, len ) MCFcuCols_sabsmax( Y, (MA)[0], ht, len )
#define MCFcu_Dia_sabsmax( MA, len )         MCFcuDia_sabsmax( (MA)[0], len )
#define MCFcu_Rows_sabsmin( Y, MA, ht, len ) MCFcuRows_sabsmin( Y, (MA)[0], ht, len )
#define MCFcu_Cols_sabsmin( Y, MA, ht, len ) MCFcuCols_sabsmin( Y, (MA)[0], ht, len )
#define MCFcu_Dia_sabsmin( MA, len )         MCFcuDia_sabsmin( (MA)[0], len )

#define MCFcu_Rows_sum( Y, MA, ht, len )     MCFcuRows_sum( Y, (MA)[0], ht, len )
#define MCFcu_Cols_sum( Y, MA, ht, len )     MCFcuCols_sum( Y, (MA)[0], ht, len )
#define MCFcu_Dia_sum(  MA, len )            MCFcuDia_sum( (MA)[0], len )
#define MCFcu_Rows_prod( Y, MA, ht, len )    MCFcuRows_prod( Y, (MA)[0], ht, len )
#define MCFcu_Cols_prod( Y, MA, ht, len )    MCFcuCols_prod( Y, (MA)[0], ht, len )
#define MCFcu_Dia_prod(  MA, len )           MCFcuDia_prod( (MA)[0], len )

#define MCFcu_Rows_runsum( MA, ht, len )     MCFcuRows_runsum( (MA)[0], ht, len )
#define MCFcu_Cols_runsum( MA, ht, len )     MCFcuCols_runsum( (MA)[0], ht, len )
#define MCFcu_Rows_runprod( MA, ht, len )    MCFcuRows_runprod( (MA)[0], ht, len )
#define MCFcu_Cols_runprod( MA, ht, len )    MCFcuCols_runprod( (MA)[0], ht, len )

#define MCFcu_Rows_rotate( MA, ht, len, pos) MCFcuRows_rotate( (MA)[0], ht, len, pos )
#define MCFcu_Cols_rotate( MA, ht, len, pos) MCFcuCols_rotate( (MA)[0], ht, len, pos )
#define MCFcu_Rows_rotate_buf( MA, ht, len, pos, MBuf) MCFcuRows_rotate_buf( (MA)[0], ht, len, pos, (MBuf)[0] )
#define MCFcu_Cols_rotate_buf( MA, ht, len, pos, MBuf) MCFcuCols_rotate_buf( (MA)[0], ht, len, pos, (MBuf)[0] )
#define MCFcu_Rows_reflect( MA, ht, len)     MCFcuRows_reflect( (MA)[0], ht, len )
#define MCFcu_Cols_reflect( MA, ht, len)     MCFcuCols_reflect( (MA)[0], ht, len )
#define MCFcu_Rows_rev( MA, ht, len)         MCFcuRows_rev( (MA)[0], ht, len )
#define MCFcu_Cols_rev( MA, ht, len)         MCFcuCols_rev( (MA)[0], ht, len )


/********  Operations involving two rows or two colums of one matrix  *****/

#define MCFcu_Rows_exchange( MA, ht, len, row1, row2 )  MCFcuRows_exchange( (MA)[0], ht, len, row1, row2 )
#define MCFcu_Cols_exchange( MA, ht, len, col1, col2 )  MCFcuCols_exchange( (MA)[0], ht, len, col1, col2 )

#define MCFcu_Rows_add( MA, ht, len, destRow, srceRow ) MCFcuRows_add( (MA)[0], ht, len, destRow, srceRow )
#define MCFcu_Cols_add( MA, ht, len, destCol, srceCol ) MCFcuCols_add( (MA)[0], ht, len, destCol, srceCol )
                         /* dest[i] += source[i]  */

#define MCFcu_Rows_sub( MA, ht, len, destRow, srceRow ) MCFcuRows_sub( (MA)[0], ht, len, destRow, srceRow )
#define MCFcu_Cols_sub( MA, ht, len, destCol, srceCol ) MCFcuCols_sub( (MA)[0], ht, len, destCol, srceCol )
                         /* dest[i] -= source[i]  */

#define MCFcu_Rows_Cadd( MA, ht, len, destRow, srceRow, C ) MCFcuRows_Cadd( (MA)[0], ht, len, destRow, srceRow, C )
#define MCFcu_Cols_Cadd( MA, ht, len, destCol, srceCol, C ) MCFcuCols_Cadd( (MA)[0], ht, len, destCol, srceCol, C )
                         /* dest[i] += C * source[i]  */

#define MCFcu_Rows_lincomb( MA, ht, len, destRow, destC, srceRow, srceC ) \
            MCFcuRows_lincomb( (MA)[0], ht, len, destRow, destC, srceRow, srceC )
#define MCFcu_Cols_lincomb( MA, ht, len, destCol, destC, srceCol, srceC ) \
            MCFcuCols_lincomb( (MA)[0], ht, len, destCol, destC, srceCol, srceC )
  /*  linear combination: dest[i] = destC * dest[i] + sourceC * source[i] */


/*****************  Transposing and rotating a matrix **********************/

#define MCFcu_transpose( MTr, MA, htTr, lenTr )    MCFcutranspose( (MTr)[0], (MA)[0], htTr, lenTr )
       /*  the dimensions htTr, lenTr are those of the transposed matrix,
           not of the original!                */
#define MCFcu_hermconj( MHConj, MA, htTr, lenTr )  MCFcuhermconj( (MHConj)[0], (MA)[0], htTr, lenTr )
#define MCFcu_rotate90( MRot, MA, htRot, lenRot )  MCFcurotate90( (MRot)[0], (MA)[0], htRot, lenRot )
#define MCFcu_rotate180( MRot, MA, htRot, lenRot ) VCFcu_rev( (MRot)[0], (MA)[0], (htRot)*(lenRot) )
#define MCFcu_rotate270( MRot, MA, htRot, lenRot ) MCFcurotate270( (MRot)[0], (MA)[0], htRot, lenRot )


/************************ Matrix Arithmetics *************************/

#define MCFcu_addM( MC, MA, MB, htA, lenA )    VCFcu_addV( (MC)[0], (MA)[0], (MB)[0], (htA)*(lenA) )
#define MCFcu_addMT( MC, MA, MB, htA, lenA )   MCFcuaddMT( (MC)[0], (MA)[0], (MB)[0], htA, lenA )
#define MCFcu_subM( MC, MA, MB, htA, lenA )    VCFcu_subV( (MC)[0], (MA)[0], (MB)[0], (htA)*(lenA) )
#define MCFcu_subMT( MC, MA, MB, htA, lenA )   MCFcusubMT( (MC)[0], (MA)[0], (MB)[0], htA, lenA )
#define MCFcu_subrMT( MC, MA, MB, htA, lenA )  MCFcusubrMT( (MC)[0], (MA)[0], (MB)[0], htA, lenA )
#define MCFcu_mulC( MB, MA, htA, lenA, C )     VCFcu_mulC( (MB)[0], (MA)[0], (htA)*(lenA), C )
#define MCFcu_divC( MB, MA, htA, lenA, C )     VCFcu_divC( (MB)[0], (MA)[0], (htA)*(lenA), C )
#define MCFcu_mulReC( MB, MA, htA, lenA, CRe ) VCFcu_mulReC( (MB)[0], (MA)[0], (htA)*(lenA), CRe )
#define MCFcu_divReC( MB, MA, htA, lenA, CRe ) VCFcu_divReC( (MB)[0], (MA)[0], (htA)*(lenA), CRe )
#define MCFcu_lincomb( MC, MA, MB, htA, lenA, CA, CB ) \
                 VCFcu_lincomb( (MC)[0], (MA)[0], (MB)[0], (htA)*(lenA), CA, CB )

#define MCFcu_mulV( Y, MA, X, htA, lenA )      MCFcumulV( Y, (MA)[0], X, htA, lenA )
                  /*  Y = MA * X.  sizX=lenA, sizY=htA;  both X and Y are column-vectors    */
#define MCFcu_TmulV( Y, MA, X, htA, lenA )      MCFcuTmulV( Y, (MA)[0], X, htA, lenA )
                  /*  Y = MAT * X.  sizX=htA, sizY=lenA; both X and Y are column-vectors    */
#define VCFcu_mulM( Y, X, MA, htA, lenA )       VCFcumulM( Y, X, (MA)[0], htA, lenA )
                  /*  Y = X * MA.  sizX=htA, sizY=lenA;  both X and Y are row-vectors.
                             Mind the prefix: VCFcu_ (not MCFcu_)    */
#define VCFcu_mulMT( Y, X, MA, htA, lenA )      VCFcumulMT( Y, X, (MA)[0], htA, lenA )
                 /*  Y = X * MAT.  sizX=lenA, sizY=htA;  both X and Y are row-vectors.   */
#define MCFcu_mulM( MC, MA, MB, htA, lenA, lenB ) MCFcumulM( (MC)[0], (MA)[0], (MB)[0], htA, lenA, lenB )
                         /*  MC = MA * MB.  htB=lenA, htC=htA, lenC=lenB */
#define MCFcu_mulMT( MC, MA, MB, htA, lenA, htB ) MCFcumulMT( (MC)[0], (MA)[0], (MB)[0], htA, lenA, htB )
                         /*  MC = MA * MBT.  lenB=lenA, htC=htA, lenC=htB */
#define MCFcu_mulMH( MC, MA, MB, htA, lenA, htB ) MCFcumulMH( (MC)[0], (MA)[0], (MB)[0], htA, lenA, htB )
                         /*  MC = MA * MBH.  lenB=lenA, htC=htA, lenC=htB */
#define MCFcu_TmulM( MC, MA, MB, htA, lenA, lenB ) MCFcuTmulM( (MC)[0], (MA)[0], (MB)[0], htA, lenA, lenB )
                         /*  MC = MAT * MB.  htB=htA, htC=lenA, lenC=lenB */
#define MCFcu_HmulM( MC, MA, MB, htA, lenA, lenB ) MCFcuHmulM( (MC)[0], (MA)[0], (MB)[0], htA, lenA, lenB )
                         /*  MC = MAH * MB.  htB=htA, htC=lenA, lenC=lenB */
#define MCFcu_TmulMT( MC, MA, MB, htA, lenA, htB ) MCFcuTmulMT( (MC)[0], (MA)[0], (MB)[0], htA, lenA, htB )
                         /*  MC = MAT * MBT.  lenB=htA, htC=lenA, lenC=htB */
#define MCFcu_TmulMH( MC, MA, MB, htA, lenA, htB )  MCFcuTmulMH( (MC)[0], (MA)[0], (MB)[0], htA, lenA, htB )
                         /*  MC = MAT * MBH.  lenB=htA, htC=lenA, lenC=htB */
#define MCFdiacu_mulM(  MC, MADia, MB, htB, lenB )  MCFdiacumulM(  (MC)[0], MADia, (MB)[0], htB, lenB )
#define MCFdiacu_mulMT( MC, MADia, MB, htB, lenB )  MCFdiacumulMT( (MC)[0], MADia, (MB)[0], htB, lenB )
#define MCFcu_mulMdia(  MC, MA, MBDia, htA, lenA )  MCFcumulMdia(  (MC)[0], (MA)[0], MBDia, htA, lenA )
#define MCFcu_TmulMdia( MC, MA, MBDia, htA, lenA )  MCFcuTmulMdia( (MC)[0], (MA)[0], MBDia, htA, lenA )


/***************** Two-Dimensional Fourier-Transform Methods ************/

#define MCFcu_FFT( MY, MX, ht, len, dir )     MCFcuFFT( (MY)[0], (MX)[0], ht, len, dir )
#define MCFcu_Rows_FFT( MY, MX, ht, len, dir) MCFcuRows_FFT( (MY)[0], (MX)[0], ht, len, dir )
#define MCFcu_Cols_FFT( MY, MX, ht, len, dir) MCFcuCols_FFT( (MY)[0], (MX)[0], ht, len, dir )
#define MCFcu_filter( MY, MX, MFlt, ht, len ) MCFcufilter( (MY)[0], (MX)[0], (MFlt)[0], ht, len )


/*************************************************************************
 * Declarations of the functions written without underbar in the prefix: *
 *	MCFcufunc		(as MCFcu_func, but input type 
                       cfPMatrix = cfVector = pointer to matrix element[0][0])
 *	cusdMCFfunc		(as cusdMCF_func, but input type 
                       cfPMatrix = cfVector = pointer to matrix element[0][0])
 *************************************************************************/


#define MCFcuequ0( MA, ht, len )    VCFcu_equ0( MA, (ht)*(len) )
void   __vf OVCUAPI  MCFcuequ1( cfPMatrix MA, ui len );  /* identity matrix */
void   __vf OVCUAPI  MCFcuequm1( cfPMatrix MA, ui len );  /* neg. identity matrix */
void   __vf OVCUAPI  MCFcuouterprod( cfPMatrix MA, cfVector X,  cfVector Y, ui ht, ui len );

void   __vf OVCUAPI  MCFcuRow_equ0( cfPMatrix MA, ui ht, ui len, ui iRow );
void   __vf OVCUAPI  MCFcuCol_equ0( cfPMatrix MA, ui ht, ui len, ui iCol );
void   __vf OVCUAPI  MCFcuDia_equ0( cfPMatrix MA, ui len );

#if defined __cplusplus && defined _CMATH_CLASSDEFS && defined __BORLANDC__ && defined _WIN64
} // for C++Builder on Win64, the following functions cannot be extern "C", if fComplex is a class
#endif
void   __vf OVCUAPI_ifNotBC64Class  MCFcuRow_equC( cfPMatrix MA, ui ht, ui len, ui iRow, fComplex C );
void   __vf OVCUAPI_ifNotBC64Class  MCFcuCol_equC( cfPMatrix MA, ui ht, ui len, ui iCol, fComplex C );
void   __vf OVCUAPI_ifNotBC64Class  MCFcuDia_equC( cfPMatrix MA, ui len, fComplex C );
#if defined __cplusplus && defined _CMATH_CLASSDEFS && defined __BORLANDC__ && defined _WIN64
extern "C" {
#endif

void   __vf OVCUAPI  MCFcuRow_equV( cfPMatrix MA, ui ht, ui len, ui iRow, cfVector X );
void   __vf OVCUAPI  MCFcuCol_equV( cfPMatrix MA, ui ht, ui len, ui iCol, cfVector X );
void   __vf OVCUAPI  MCFcuDia_equV( cfPMatrix MA, ui len, cfVector X );

void   __vf OVCUAPI  MCFcuTrd_equM( cfPMatrix MA, cfPMatrix MTrd, ui len );
void   __vf OVCUAPI  MCFcuTrd_extract( cfPMatrix MTrd, cfPMatrix MA, ui len );

#define MCFcuequM( MB, MA, ht, len )  VCFcu_equV( MB, MA, (ht)*(len) )
#define MCFcuneg( MB, MA, ht, len )   VCFcu_neg( MB, MA, (ht)*(len) )
#define MCFcuconj( MB, MA, ht, len )  VCFcu_conj( MB, MA, (ht)*(len) )

void   __vf OVCUAPI  MCFcuUequL( cfPMatrix MA, ui len );
void   __vf OVCUAPI  MCFcuLequU( cfPMatrix MA, ui len );

            /* data-type conversions:  */
#define McuCDtoCF( MCF, MCD, ht, len ) Vcu_CDtoCF( (MCF), (MCD), (ht)*(len) )
#define McuCFtoCD( MCD, MCF, ht, len ) Vcu_CFtoCD( (MCD), (MCF), (ht)*(len) )

#define MFcuCtoRe( MY, MCX, ht, len )           VFcu_CtoRe( MY,  MCX, (ht)*(len) )
#define MFcuCtoIm( MY, MCX, ht, len )           VFcu_CtoIm( MY,  MCX, (ht)*(len) )
#define MFcuCtoReIm( MYRe, MYIm, MCX, ht, len ) VFcu_CtoReIm( (MYRe), (MYIm), (MCX), (ht)*(len) )
#define MFcuRetoC( MCY, MX, ht, len )           VFcu_RetoC( (MCY), (MX),  (ht)*(len) )
#define MFcuImtoC( MCY, MX, ht, len )           VFcu_ImtoC( (MCY), (MX),  (ht)*(len) )
#define MFcuReImtoC( MCY, MXRe, MXIm, ht, len ) VFcu_ReImtoC( (MCY), (MXRe), (MXIm), (ht)*(len) )

/********  Extracting a submatrix and copying a submatrix back  *********/

void  __vf OVCUAPI  MCFcusubmatrix( cfPMatrix MSub, ui subHt,  ui subLen,
                          cfPMatrix MSrce, ui srceHt,  ui srceLen,
                          ui firstRowInCol,  ui sampInCol,
                          ui firstColInRow,  ui sampInRow );

void  __vf OVCUAPI  MCFcusubmatrix_equM( cfPMatrix MDest, ui destHt, ui destLen,
                               ui firstRowInCol,  ui sampInCol,
                               ui firstColInRow,  ui sampInRow,
                               cfPMatrix MSrce, ui srceHt, ui srceLen );

void  __vf OVCUAPI  MCFcuequMblock( cfPMatrix MSub, ui subHt,  ui subLen,
                          cfPMatrix MSrce, ui srceHt,  ui srceLen,
                          ui firstRowInCol,  ui firstColInRow );

void  __vf OVCUAPI  MCFcublock_equM( cfPMatrix MDest, ui destHt, ui destLen,
                           ui firstRowInCol,  ui firstColInRow,
                           cfPMatrix MSrce, ui srceHt,  ui srceLen );

void  __vf OVCUAPI  MCFcuequMblockT( cfPMatrix MSub,  ui subHt,  ui subLen,
                          cfPMatrix MSrce,  ui srceHt,  ui srceLen,
						  ui firstRowInCol,  ui firstColInRow );

void  __vf OVCUAPI  MCFcublock_equMT( cfPMatrix MDest,  ui destHt,  ui destLen,
                           ui firstRowInCol,  ui firstColInRow,
                           cfPMatrix MSrce,  ui srceHt,  ui srceLen );


/*****   Extracting a single row or a single column or the diagonal  *****
 *       and storing it into a vector                                    */

void __vf OVCUAPI  MCFcuRow_extract( cfVector Y, cfPMatrix MA, ui ht, ui len, ui iRow );
void __vf OVCUAPI  MCFcuCol_extract( cfVector Y, cfPMatrix MA, ui ht, ui len, ui iCol );
void __vf OVCUAPI  MCFcuDia_extract( cfVector Y, cfPMatrix MA, ui len );

/**********  Deleting or inserting a row or a column *****************/

void __vf OVCUAPI  MCFcuRow_delete( cfPMatrix MB, cfPMatrix MA, ui htA, ui lenA, ui iRow );
void __vf OVCUAPI  MCFcuCol_delete( cfPMatrix MB, cfPMatrix MA, ui htA, ui lenA, ui iCol );
void __vf OVCUAPI  MCFcuRow_insert( cfPMatrix MB, cfPMatrix MA, ui htB, ui lenB, ui iRow, cfVector X );
void __vf OVCUAPI  MCFcuCol_insert( cfPMatrix MB, cfPMatrix MA, ui htB, ui lenB, ui iCol, cfVector X );


/*****************    Basic arithmetic operations ***********************
     performed on one single row,  or one single column of any matrix,
     or on the diagonal of a square matrix                              */

void   __vf OVCUAPI  MCFcuRow_neg( cfPMatrix MX, ui ht, ui len, ui iRow );
void   __vf OVCUAPI  MCFcuCol_neg( cfPMatrix MX, ui ht, ui len, ui iCol );

void   __vf OVCUAPI  MCFcuRow_conj( cfPMatrix MX, ui ht, ui len, ui iRow );
void   __vf OVCUAPI  MCFcuCol_conj( cfPMatrix MX, ui ht, ui len, ui iCol );

#if defined __cplusplus && defined _CMATH_CLASSDEFS && defined __BORLANDC__ && defined _WIN64
} // for C++Builder on Win64, the following functions cannot be extern "C", if fComplex is a class
#endif
void   __vf OVCUAPI_ifNotBC64Class  MCFcuRow_addC( cfPMatrix MA, ui ht, ui len, ui iRow, fComplex C );
void   __vf OVCUAPI_ifNotBC64Class  MCFcuCol_addC( cfPMatrix MA, ui ht, ui len, ui iCol, fComplex C );
void   __vf OVCUAPI_ifNotBC64Class  MCFcuDia_addC( cfPMatrix MA, ui len, fComplex C );

void   __vf OVCUAPI_ifNotBC64Class  MCFcuRow_subC( cfPMatrix MA, ui ht, ui len, ui iRow, fComplex C );
void   __vf OVCUAPI_ifNotBC64Class  MCFcuCol_subC( cfPMatrix MA, ui ht, ui len, ui iCol, fComplex C );
void   __vf OVCUAPI_ifNotBC64Class  MCFcuDia_subC( cfPMatrix MA, ui len, fComplex C );

void   __vf OVCUAPI_ifNotBC64Class  MCFcuRow_subrC( cfPMatrix MA, ui ht, ui len, ui iRow, fComplex C );
void   __vf OVCUAPI_ifNotBC64Class  MCFcuCol_subrC( cfPMatrix MA, ui ht, ui len, ui iCol, fComplex C );
void   __vf OVCUAPI_ifNotBC64Class  MCFcuDia_subrC( cfPMatrix MA, ui len, fComplex C );

void   __vf OVCUAPI_ifNotBC64Class  MCFcuRow_mulC( cfPMatrix MA, ui ht, ui len, ui iRow, fComplex C );
void   __vf OVCUAPI_ifNotBC64Class  MCFcuCol_mulC( cfPMatrix MA, ui ht, ui len, ui iCol, fComplex C );
void   __vf OVCUAPI_ifNotBC64Class  MCFcuDia_mulC( cfPMatrix MA, ui len, fComplex C );

void   __vf OVCUAPI_ifNotBC64Class  MCFcuRow_divC( cfPMatrix MA, ui ht, ui len, ui iRow, fComplex C );
void   __vf OVCUAPI_ifNotBC64Class  MCFcuCol_divC( cfPMatrix MA, ui ht, ui len, ui iCol, fComplex C );
void   __vf OVCUAPI_ifNotBC64Class  MCFcuDia_divC( cfPMatrix MA, ui len, fComplex C );

void   __vf OVCUAPI_ifNotBC64Class  MCFcuRow_divrC( cfPMatrix MA, ui ht, ui len, ui iRow, fComplex C );
void   __vf OVCUAPI_ifNotBC64Class  MCFcuCol_divrC( cfPMatrix MA, ui ht, ui len, ui iCol, fComplex C );
void   __vf OVCUAPI_ifNotBC64Class  MCFcuDia_divrC( cfPMatrix MA, ui len, fComplex C );

#if defined __cplusplus && defined _CMATH_CLASSDEFS && defined __BORLANDC__ && defined _WIN64
extern "C" {
#endif
void   __vf OVCUAPI  MCFcuRow_addV( cfPMatrix MA, ui ht, ui len, ui iRow, cfVector X );
void   __vf OVCUAPI  MCFcuCol_addV( cfPMatrix MA, ui ht, ui len, ui iCol, cfVector X );
void   __vf OVCUAPI  MCFcuDia_addV( cfPMatrix MA, ui len, cfVector X );

void   __vf OVCUAPI  MCFcuRow_subV( cfPMatrix MA, ui ht, ui len, ui iRow, cfVector X );
void   __vf OVCUAPI  MCFcuCol_subV( cfPMatrix MA, ui ht, ui len, ui iCol, cfVector X );
void   __vf OVCUAPI  MCFcuDia_subV( cfPMatrix MA, ui len, cfVector X );

void   __vf OVCUAPI  MCFcuRow_subrV( cfPMatrix MA, ui ht, ui len, ui iRow, cfVector X );
void   __vf OVCUAPI  MCFcuCol_subrV( cfPMatrix MA, ui ht, ui len, ui iCol, cfVector X );
void   __vf OVCUAPI  MCFcuDia_subrV( cfPMatrix MA, ui len, cfVector X );

void   __vf OVCUAPI  MCFcuRow_mulV( cfPMatrix MA, ui ht, ui len, ui iRow, cfVector X );
void   __vf OVCUAPI  MCFcuCol_mulV( cfPMatrix MA, ui ht, ui len, ui iCol, cfVector X );
void   __vf OVCUAPI  MCFcuDia_mulV( cfPMatrix MA, ui len, cfVector X );

void   __vf OVCUAPI  MCFcuRow_divV( cfPMatrix MA, ui ht, ui len, ui iRow, cfVector X );
void   __vf OVCUAPI  MCFcuCol_divV( cfPMatrix MA, ui ht, ui len, ui iCol, cfVector X );
void   __vf OVCUAPI  MCFcuDia_divV( cfPMatrix MA, ui len, cfVector X );

void   __vf OVCUAPI  MCFcuRow_divrV( cfPMatrix MA, ui ht, ui len, ui iRow, cfVector X );
void   __vf OVCUAPI  MCFcuCol_divrV( cfPMatrix MA, ui ht, ui len, ui iCol, cfVector X );
void   __vf OVCUAPI  MCFcuDia_divrV( cfPMatrix MA, ui len, cfVector X );


/******  One-dimensional vector operations **********************
         performed along all rows or all columns simultaneously,
         or along the diagonal of a square matrix                */

void     __vf OVCUAPI  MCFcuRows_absmax( fVector Y, cfPMatrix MA, ui ht, ui len );
void     __vf OVCUAPI  MCFcuCols_absmax( fVector Y, cfPMatrix MA, ui ht, ui len );
float    __vf OVCUAPI  MCFcuDia_absmax(  cfPMatrix MA, ui len );
void     __vf OVCUAPI  MCFcuRows_absmin( fVector Y, cfPMatrix MA, ui ht, ui len );
void     __vf OVCUAPI  MCFcuCols_absmin( fVector Y, cfPMatrix MA, ui ht, ui len );
float    __vf OVCUAPI  MCFcuDia_absmin(  cfPMatrix MA, ui len );

void     __vf OVCUAPI  MCFcuRows_maxReIm( cfVector Y, cfPMatrix MA, ui ht, ui len );
void     __vf OVCUAPI  MCFcuCols_maxReIm( cfVector Y, cfPMatrix MA, ui ht, ui len );
void     __vf OVCUAPI  MCFcuRows_minReIm( cfVector Y, cfPMatrix MA, ui ht, ui len );
void     __vf OVCUAPI  MCFcuCols_minReIm( cfVector Y, cfPMatrix MA, ui ht, ui len );

void     __vf OVCUAPI  MCFcuRows_absmaxReIm( cfVector Y, cfPMatrix MA, ui ht, ui len );
void     __vf OVCUAPI  MCFcuCols_absmaxReIm( cfVector Y, cfPMatrix MA, ui ht, ui len );
void     __vf OVCUAPI  MCFcuRows_absminReIm( cfVector Y, cfPMatrix MA, ui ht, ui len );
void     __vf OVCUAPI  MCFcuCols_absminReIm( cfVector Y, cfPMatrix MA, ui ht, ui len );

void     __vf OVCUAPI  MCFcuRows_cabsmax( cfVector Y, cfPMatrix MA, ui ht, ui len );
void     __vf OVCUAPI  MCFcuCols_cabsmax( cfVector Y, cfPMatrix MA, ui ht, ui len );
void     __vf OVCUAPI  MCFcuRows_cabsmin( cfVector Y, cfPMatrix MA, ui ht, ui len );
void     __vf OVCUAPI  MCFcuCols_cabsmin( cfVector Y, cfPMatrix MA, ui ht, ui len );

void     __vf OVCUAPI  MCFcuRows_sabsmax( cfVector Y, cfPMatrix MA, ui ht, ui len );
void     __vf OVCUAPI  MCFcuCols_sabsmax( cfVector Y, cfPMatrix MA, ui ht, ui len );
void     __vf OVCUAPI  MCFcuRows_sabsmin( cfVector Y, cfPMatrix MA, ui ht, ui len );
void     __vf OVCUAPI  MCFcuCols_sabsmin( cfVector Y, cfPMatrix MA, ui ht, ui len );

void     __vf OVCUAPI  MCFcuRows_sum( cfVector Y, cfPMatrix MA, ui ht, ui len );
void     __vf OVCUAPI  MCFcuCols_sum( cfVector Y, cfPMatrix MA, ui ht, ui len );
void     __vf OVCUAPI  MCFcuRows_prod(cfVector Y, cfPMatrix MA, ui ht, ui len );
void     __vf OVCUAPI  MCFcuCols_prod(cfVector Y, cfPMatrix MA, ui ht, ui len );

#if defined __cplusplus && defined _CMATH_CLASSDEFS
}   /* following functions cannot be extern "C", if fComplex is a class */
#endif
fComplex     __vf OVCUAPI_ifNotClass  MCFcuDia_maxReIm(  cfPMatrix MA, ui len );
fComplex     __vf OVCUAPI_ifNotClass  MCFcuDia_minReIm(  cfPMatrix MA, ui len );
fComplex     __vf OVCUAPI_ifNotClass  MCFcuDia_absmaxReIm(  cfPMatrix MA, ui len );
fComplex     __vf OVCUAPI_ifNotClass  MCFcuDia_absminReIm(  cfPMatrix MA, ui len );
fComplex     __vf OVCUAPI_ifNotClass  MCFcuDia_cabsmax(  cfPMatrix MA, ui len );
fComplex     __vf OVCUAPI_ifNotClass  MCFcuDia_cabsmin(  cfPMatrix MA, ui len );
fComplex     __vf OVCUAPI_ifNotClass  MCFcuDia_sabsmax(  cfPMatrix MA, ui len );
fComplex     __vf OVCUAPI_ifNotClass  MCFcuDia_sabsmin(  cfPMatrix MA, ui len );
fComplex     __vf OVCUAPI_ifNotClass  MCFcuDia_sum(  cfPMatrix MA, ui len );
fComplex     __vf OVCUAPI_ifNotClass  MCFcuDia_prod( cfPMatrix MA, ui len );
#if defined __cplusplus && defined _CMATH_CLASSDEFS
extern "C" {
#endif

void  __vf OVCUAPI  MCFcuRows_runsum( cfPMatrix MA, ui ht, ui len );
void  __vf OVCUAPI  MCFcuCols_runsum( cfPMatrix MA, ui ht, ui len );
void  __vf OVCUAPI  MCFcuRows_runprod( cfPMatrix MA, ui ht, ui len );
void  __vf OVCUAPI  MCFcuCols_runprod( cfPMatrix MA, ui ht, ui len );

void  __vf OVCUAPI  MCFcuRows_rotate( cfPMatrix MA, ui ht, ui len, ssize_t pos );
void  __vf OVCUAPI  MCFcuCols_rotate( cfPMatrix MA, ui ht, ui len, ssize_t pos );
void  __vf OVCUAPI  MCFcuRows_rotate_buf( cfPMatrix MA, ui ht, ui len, ssize_t pos, cfPMatrix MBuf );
void  __vf OVCUAPI  MCFcuCols_rotate_buf( cfPMatrix MA, ui ht, ui len, ssize_t pos, cfPMatrix MBuf );
void  __vf OVCUAPI  MCFcuRows_reflect( cfPMatrix MA, ui ht, ui len );
void  __vf OVCUAPI  MCFcuCols_reflect( cfPMatrix MA, ui ht, ui len );
void  __vf OVCUAPI  MCFcuRows_rev( cfPMatrix MA, ui ht, ui len );
void  __vf OVCUAPI  MCFcuCols_rev( cfPMatrix MA, ui ht, ui len );

/********  Operations involving two rows or two colums of one matrix  *****/

void   __vf OVCUAPI  MCFcuRows_exchange( cfPMatrix MA, ui ht, ui len, ui i1, ui i2 );
void   __vf OVCUAPI  MCFcuCols_exchange( cfPMatrix MA, ui ht, ui len, ui i1, ui i2 );

void   __vf OVCUAPI  MCFcuRows_add( cfPMatrix MA, ui ht, ui len, ui destRow, ui sourceRow );
void   __vf OVCUAPI  MCFcuCols_add( cfPMatrix MA, ui ht, ui len, ui destCol, ui sourceCol );

void   __vf OVCUAPI  MCFcuRows_sub( cfPMatrix MA, ui ht, ui len, ui destRow, ui sourceRow );
void   __vf OVCUAPI  MCFcuCols_sub( cfPMatrix MA, ui ht, ui len, ui destCol, ui sourceCol );

#if defined __cplusplus && defined _CMATH_CLASSDEFS && defined __BORLANDC__ && defined _WIN64
} // for C++Builder on Win64, the following functions cannot be extern "C", if fComplex is a class
#endif
void   __vf OVCUAPI_ifNotBC64Class  MCFcuRows_Cadd( cfPMatrix MA, ui ht, ui len, ui destRow, ui sourceRow, fComplex C );
void   __vf OVCUAPI_ifNotBC64Class  MCFcuCols_Cadd( cfPMatrix MA, ui ht, ui len, ui destCol, ui sourceCol, fComplex C );

void   __vf OVCUAPI_ifNotBC64Class  MCFcuRows_lincomb( cfPMatrix MA, ui ht, ui len, ui destRow,  fComplex  destC,
                                                                 ui srceRow,  fComplex  srceC );
void   __vf OVCUAPI_ifNotBC64Class  MCFcuCols_lincomb( cfPMatrix MA, ui ht, ui len, ui destCol,  fComplex  destC,
                                                                 ui srceCol,  fComplex  srceC );
#if defined __cplusplus && defined _CMATH_CLASSDEFS && defined __BORLANDC__ && defined _WIN64
extern "C" {
#endif


/**************  Transposing and rotating a matrix **********************/

void  __vf OVCUAPI  MCFcutranspose( cfPMatrix MTr, cfPMatrix MA, ui htTr, ui lenTr );
void  __vf OVCUAPI  MCFcuhermconj( cfPMatrix MHConj, cfPMatrix MA, ui htTr, ui lenTr );
void  __vf OVCUAPI  MCFcurotate90(  cfPMatrix MRot, cfPMatrix MA, ui htRot, ui lenRot );
#define     MCFcurotate180( MRot, MA, htRot, lenRot ) VCFcu_rev( MRot, MA, (htRot)*(lenRot) )
void  __vf OVCUAPI  MCFcurotate270( cfPMatrix MRot, cfPMatrix MA, ui htRot, ui lenRot );


/************************ Matrix Arithmetics *************************/

#define MCFcuaddM( MC, MA, MB, htA, lenA )      VCFcu_addV( MC, MA, MB, (htA)*(lenA) )
void __vf OVCUAPI  MCFcuaddMT( cfPMatrix MC, cfPMatrix MA, cfPMatrix MB, ui htA, ui lenA );
#define MCFcusubM( MC, MA, MB, htA, lenA )      VCFcu_subV( MC, MA, MB, (htA)*(lenA) )
void __vf OVCUAPI  MCFcusubMT( cfPMatrix MC, cfPMatrix MA, cfPMatrix MB, ui htA, ui lenA );
void __vf OVCUAPI  MCFcusubrMT( cfPMatrix MC, cfPMatrix MA, cfPMatrix MB, ui htA, ui lenA );
#define MCFcumulC( MB, MA, htA, lenA, C )       VCFcu_mulC( MB, MA, (htA)*(lenA), C )
#define MCFcudivC( MB, MA, htA, lenA, C )       VCFcu_divC( MB, MA, (htA)*(lenA), C )
#define MCFcumulReC( MB, MA, htA, lenA, CRe )   VCFcu_mulReC( MB, MA, (htA)*(lenA), CRe )
#define MCFcudivReC( MB, MA, htA, lenA, CRe )   VCFcu_divReC( MB, MA, (htA)*(lenA), CRe )
#define MCFculincomb( MC, MA, MB, htA, lenA, CA, CB ) VCFcu_lincomb( MC, MA, MB, (htA)*(lenA), CA, CB )
void  __vf OVCUAPI  MCFcumulV( cfVector Y, cfPMatrix MA, cfVector X, ui htA, ui lenA );
void  __vf OVCUAPI  MCFcuTmulV( cfVector Y, cfPMatrix MA, cfVector X, ui htA, ui lenA );
void  __vf OVCUAPI  VCFcumulM( cfVector Y, cfVector X, cfPMatrix MA, ui htA, ui lenA );
void  __vf OVCUAPI  VCFcumulMT( cfVector Y, cfVector X, cfPMatrix MA, ui htA, ui lenA );
void  __vf OVCUAPI  MCFcumulM( cfPMatrix MC, cfPMatrix MA, cfPMatrix MB, ui htA, ui lenA, ui lenB );
void  __vf OVCUAPI  MCFcumulMT( cfPMatrix MC, cfPMatrix MA, cfPMatrix MB, ui htA, ui lenA, ui htB );
void  __vf OVCUAPI  MCFcumulMH( cfPMatrix MC, cfPMatrix MA, cfPMatrix MB, ui htA, ui lenA, ui htB );
void  __vf OVCUAPI  MCFcuTmulM( cfPMatrix MC, cfPMatrix MA, cfPMatrix MB, ui htA, ui lenA, ui lenB );
void  __vf OVCUAPI  MCFcuHmulM( cfPMatrix MC, cfPMatrix MA, cfPMatrix MB, ui htA, ui lenA, ui lenB );
void  __vf OVCUAPI  MCFcuTmulMT( cfPMatrix MC, cfPMatrix MA, cfPMatrix MB, ui htA, ui lenA, ui htB );
void  __vf OVCUAPI  MCFcuTmulMH( cfPMatrix MC, cfPMatrix MA, cfPMatrix MB, ui htA, ui lenA, ui htB );
void  __vf OVCUAPI  MCFdiacumulM( cfPMatrix MC, cfPMatrix MADia, cfPMatrix MB, ui htB, ui lenB );
void  __vf OVCUAPI  MCFdiacumulMT( cfPMatrix MC, cfPMatrix MADia, cfPMatrix MB, ui htB, ui lenB );
void  __vf OVCUAPI  MCFcumulMdia( cfPMatrix MC, cfPMatrix MA, cfPMatrix MBDia, ui htA, ui lenA );
void  __vf OVCUAPI  MCFcuTmulMdia( cfPMatrix MC, cfPMatrix MA, cfPMatrix MBDia, ui htA, ui lenA );


/*************  Two-Dimensional Fourier-Transform Methods *****************/

void  __vf OVCUAPI  MCFcuFFT( cfPMatrix MY, cfPMatrix MX, ui ht, ui len, int dir );
void  __vf OVCUAPI  MCFcufilter( cfPMatrix MY, cfPMatrix MX, cfPMatrix MFlt, ui ht, ui len );
void  __vf OVCUAPI  MCFcuRows_FFT( cfPMatrix MY, cfPMatrix MX, ui ht, ui len, int dir );
void  __vf OVCUAPI  MCFcuCols_FFT( cfPMatrix MY, cfPMatrix MX, ui ht, ui len, int dir );

#ifdef __cplusplus
}  // end of extern "C"
#endif
#endif /* __CUDAMCFSTD_H */
