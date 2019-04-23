/*  cudaMCDstd.h

  matrix management functions:
  manipulations on matrices of data type "dComplex"
  (double-precision complex numbers)

  This file declares the functions with the name variants 
	cudaMCD_func	(working on matrices in device memory, input type dMatrix, scalar parameters reside on host and are passed by value)
	cusdMCD_func	(as cudaMD_func except scalar parameters reside on device and are passed by address)
	cudaMCDfunc		(as cudaMCD_func, but input type cdPMatrix = cdVector = pointer to matrix element[0][0])
	cusdMCDfunc		(as cusdMCD_func, but input type cdPMatrix = cdVector = pointer to matrix element[0][0])
	MCDcu_func		(working on matrices in host memory, input type cdMatrix, scalar parameters on host and passed by value)
	MCDcufunc		(as MCDcu_func, but input type cdPMatrix = cdVector = pointer to matrix element[0][0])
  where func is the respective function.

  Copyright (c) 1996-2017 by OptiCode - Dr. Martin Sander Software Dev.
  All Rights Reserved.
*/

#if !defined( __CUDAMCDSTD_H )
#define __CUDAMCDSTD_H
#if !defined( __CUDAMATLIB_H )
   #include <cudaMatLib.h>
#endif
#if !defined( __CUDAVCDSTD_H )
   #include <cudaVCDstd.h>
#endif
#if !defined( __CUDAVCDMATH_H )
   #include <cudaVCDmath.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif


/**** Generation of matrices on device memory and on pinned host memory *******************/

cdMatrix  __vf cudaMCD_matrix( ui ht, ui len );   /* allocates a vector on device memory */
cdMatrix  __vf cudaMCD_matrix0( ui ht, ui len );
 /* The following functions allocate device-accessible, "pinned" memory on the host.
	This memory is mapped onto the device memory space. The resulting device address is returned.
	The matrix can be accessed either by its host address "hostPtr" e.g., MCD_equ1( hostPtr, ht, len );
	or by its device address , e.g., cudaMCD_equ1( devicePtr, ht, len );                             */
cdMatrix  __vf cudaMCD_pinnedMatrix(  cdMatrix *hostPtr, ui ht, ui len ); 
cdMatrix  __vf cudaMCD_pinnedMatrix0( cdMatrix *hostPtr, ui ht, ui len );

/*************************************************************************
 * Declarations of the functions written without underbar in the prefix: *
 *	cudaMCDfunc  (input type 
                   cdPMatrix = cdVector = pointer to matrix element[0][0])
 *	cusdMCDfunc  (input type 
                   cdPMatrix = cdVector = pointer to matrix element[0][0])
 *************************************************************************/


void    __vcuf OVCUAPI  cudaMCDsetElement( cdPMatrix X, ui ht, ui len, ui m, ui n, dComplex C );
void    __vcuf OVCUAPI  cusdMCDsetElement( cdPMatrix X, ui ht, ui len, ui m, ui n, dComplex *d_C );
void    __vcuf OVCUAPI  cudaMCDgetElement( dComplex *h_y, cdPMatrix X, ui ht, ui len, ui m, ui n );
void    __vcuf OVCUAPI  cusdMCDgetElement( dComplex *d_y, cdPMatrix X, ui ht, ui len, ui m, ui n );
dComplex * __vcuf OVCUAPI  cudaMCDPelement( cdPMatrix X, ui ht, ui len, ui m, ui n );
#if defined __cplusplus && defined _CMATH_CLASSDEFS
} // the following function cannot be extern "C", if dComplex is a class
#endif
dComplex   __vcuf OVCUAPI_ifNotClass  cudaMCDelement( cdPMatrix X, ui ht, ui len, ui m, ui n );
#if defined __cplusplus && defined _CMATH_CLASSDEFS
extern "C" {
#endif

#define cudaMCDequ0( MA, ht, len )    cudaVCD_equ0( MA, (ht)*(len) )
overror_t   __vcuf OVCUAPI  cudaMCDequ1( cdPMatrix MA, ui len );  /* identity matrix */
overror_t   __vcuf OVCUAPI  cudaMCDequm1( cdPMatrix MA, ui len );  /* neg. identity matrix */
overror_t   __vcuf OVCUAPI  cudaMCDouterprod( cdPMatrix MA, cdVector X,  cdVector Y, ui ht, ui len );

overror_t   __vcuf OVCUAPI  cudaMCDRow_equ0( cdPMatrix MA, ui ht, ui len, ui iRow );
overror_t   __vcuf OVCUAPI  cudaMCDCol_equ0( cdPMatrix MA, ui ht, ui len, ui iCol );
overror_t   __vcuf OVCUAPI  cudaMCDDia_equ0( cdPMatrix MA, ui len );

overror_t   __vcuf OVCUAPI  cudaMCDRow_equC( cdPMatrix MA, ui ht, ui len, ui iRow, dComplex C );
overror_t   __vcuf OVCUAPI  cudaMCDCol_equC( cdPMatrix MA, ui ht, ui len, ui iCol, dComplex C );
overror_t   __vcuf OVCUAPI  cudaMCDDia_equC( cdPMatrix MA, ui len, dComplex C );
overror_t   __vcuf OVCUAPI  cusdMCDRow_equC( cdPMatrix MA, ui ht, ui len, ui iRow, dComplex *d_C );
overror_t   __vcuf OVCUAPI  cusdMCDCol_equC( cdPMatrix MA, ui ht, ui len, ui iCol, dComplex *d_C );
overror_t   __vcuf OVCUAPI  cusdMCDDia_equC( cdPMatrix MA, ui len, dComplex *d_C );

overror_t   __vcuf OVCUAPI  cudaMCDRow_equV( cdPMatrix MA, ui ht, ui len, ui iRow, cdVector X );
overror_t   __vcuf OVCUAPI  cudaMCDCol_equV( cdPMatrix MA, ui ht, ui len, ui iCol, cdVector X );
overror_t   __vcuf OVCUAPI  cudaMCDDia_equV( cdPMatrix MA, ui len, cdVector X );

overror_t   __vcuf OVCUAPI  cudaMCDTrd_equM( cdPMatrix MA, cdPMatrix MTrd, ui len );
overror_t   __vcuf OVCUAPI  cudaMCDTrd_extract( cdPMatrix MTrd, cdPMatrix MA, ui len );

#define cudaMCDequM( MB, MA, ht, len )  cudaVCD_equV( MB, MA, (ht)*(len) )
#define cudaMCDequMhost( d_MB, h_MA, ht, len )  cudaVCD_equVhost( d_MB, h_MA, (ht)*(len) )
#define MCDequMdevice( h_MB, d_MA, ht, len )    VCD_equVdevice( h_MB, d_MA, (ht)*(len) )
#define cudaMCDneg( MB, MA, ht, len )   cudaVCD_neg( MB, MA, (ht)*(len) )
#define cudaMCDconj( MB, MA, ht, len )  cudaVCD_conj( MB, MA, (ht)*(len) )

overror_t   __vcuf OVCUAPI  cudaMCDUequL( cdPMatrix MA, ui len );
overror_t   __vcuf OVCUAPI  cudaMCDLequU( cdPMatrix MA, ui len );

/********  Extracting a submatrix and copying a submatrix back  *********/

overror_t  __vcuf OVCUAPI  cudaMCDsubmatrix( cdPMatrix MSub, ui subHt,  ui subLen,
                          cdPMatrix MSrce, ui srceHt,  ui srceLen,
                          ui firstRowInCol,  ui sampInCol,
                          ui firstColInRow,  ui sampInRow );

overror_t  __vcuf OVCUAPI  cudaMCDsubmatrix_equM( cdPMatrix MDest, ui destHt, ui destLen,
                               ui firstRowInCol,  ui sampInCol,
                               ui firstColInRow,  ui sampInRow,
                               cdPMatrix MSrce, ui srceHt, ui srceLen );

overror_t  __vcuf OVCUAPI  cudaMCDequMblock( cdPMatrix MSub, ui subHt,  ui subLen,
                          cdPMatrix MSrce, ui srceHt,  ui srceLen,
                          ui firstRowInCol,  ui firstColInRow );

overror_t  __vcuf OVCUAPI  cudaMCDblock_equM( cdPMatrix MDest, ui destHt, ui destLen,
                           ui firstRowInCol,  ui firstColInRow,
                           cdPMatrix MSrce, ui srceHt,  ui srceLen );

overror_t  __vcuf OVCUAPI  cudaMCDequMblockT( cdPMatrix MSub,  ui subHt,  ui subLen,
                          cdPMatrix MSrce,  ui srceHt,  ui srceLen,
                          ui firstRowInCol,  ui firstColInRow );

overror_t  __vcuf OVCUAPI  cudaMCDblock_equMT( cdPMatrix MDest,  ui destHt,  ui destLen,
                           ui firstRowInCol,  ui firstColInRow,
                           cdPMatrix MSrce,  ui srceHt,  ui srceLen );


/*****   Extracting a single row or a single column or the diagonal  *****
 *       and storing it into a vector                                    */

overror_t __vcuf OVCUAPI  cudaMCDRow_extract( cdVector Y, cdPMatrix MA, ui ht, ui len, ui iRow );
overror_t __vcuf OVCUAPI  cudaMCDCol_extract( cdVector Y, cdPMatrix MA, ui ht, ui len, ui iCol );
overror_t __vcuf OVCUAPI  cudaMCDDia_extract( cdVector Y, cdPMatrix MA, ui len );

/**********  Deleting or inserting a row or a column *****************/

overror_t __vcuf OVCUAPI  cudaMCDRow_delete( cdPMatrix MB, cdPMatrix MA, ui htA, ui lenA, ui iRow );
overror_t __vcuf OVCUAPI  cudaMCDCol_delete( cdPMatrix MB, cdPMatrix MA, ui htA, ui lenA, ui iCol );
overror_t __vcuf OVCUAPI  cudaMCDRow_insert( cdPMatrix MB, cdPMatrix MA, ui htB, ui lenB, ui iRow, cdVector X );
overror_t __vcuf OVCUAPI  cudaMCDCol_insert( cdPMatrix MB, cdPMatrix MA, ui htB, ui lenB, ui iCol, cdVector X );


/*****************    Basic arithmetic operations ***********************
     performed on one single row,  or one single column of any matrix,
     or on the diagonal of a square matrix                              */

overror_t   __vcuf OVCUAPI  cudaMCDRow_neg( cdPMatrix MX, ui ht, ui len, ui iRow );
overror_t   __vcuf OVCUAPI  cudaMCDCol_neg( cdPMatrix MX, ui ht, ui len, ui iCol );

overror_t   __vcuf OVCUAPI  cudaMCDRow_conj( cdPMatrix MX, ui ht, ui len, ui iRow );
overror_t   __vcuf OVCUAPI  cudaMCDCol_conj( cdPMatrix MX, ui ht, ui len, ui iCol );

overror_t   __vcuf OVCUAPI  cudaMCDRow_addC( cdPMatrix MA, ui ht, ui len, ui iRow, dComplex C );
overror_t   __vcuf OVCUAPI  cudaMCDCol_addC( cdPMatrix MA, ui ht, ui len, ui iCol, dComplex C );
overror_t   __vcuf OVCUAPI  cudaMCDDia_addC( cdPMatrix MA, ui len, dComplex C );

overror_t   __vcuf OVCUAPI  cudaMCDRow_subC( cdPMatrix MA, ui ht, ui len, ui iRow, dComplex C );
overror_t   __vcuf OVCUAPI  cudaMCDCol_subC( cdPMatrix MA, ui ht, ui len, ui iCol, dComplex C );
overror_t   __vcuf OVCUAPI  cudaMCDDia_subC( cdPMatrix MA, ui len, dComplex C );

overror_t   __vcuf OVCUAPI  cudaMCDRow_addV( cdPMatrix MA, ui ht, ui len, ui iRow, cdVector X );
overror_t   __vcuf OVCUAPI  cudaMCDCol_addV( cdPMatrix MA, ui ht, ui len, ui iCol, cdVector X );
overror_t   __vcuf OVCUAPI  cudaMCDDia_addV( cdPMatrix MA, ui len, cdVector X );

overror_t   __vcuf OVCUAPI  cudaMCDRow_subV( cdPMatrix MA, ui ht, ui len, ui iRow, cdVector X );
overror_t   __vcuf OVCUAPI  cudaMCDCol_subV( cdPMatrix MA, ui ht, ui len, ui iCol, cdVector X );
overror_t   __vcuf OVCUAPI  cudaMCDDia_subV( cdPMatrix MA, ui len, cdVector X );

overror_t   __vcuf OVCUAPI  cudaMCDRow_subrC( cdPMatrix MA, ui ht, ui len, ui iRow, dComplex C );
overror_t   __vcuf OVCUAPI  cudaMCDCol_subrC( cdPMatrix MA, ui ht, ui len, ui iCol, dComplex C );
overror_t   __vcuf OVCUAPI  cudaMCDDia_subrC( cdPMatrix MA, ui len, dComplex C );

overror_t   __vcuf OVCUAPI  cudaMCDRow_subrV( cdPMatrix MA, ui ht, ui len, ui iRow, cdVector X );
overror_t   __vcuf OVCUAPI  cudaMCDCol_subrV( cdPMatrix MA, ui ht, ui len, ui iCol, cdVector X );
overror_t   __vcuf OVCUAPI  cudaMCDDia_subrV( cdPMatrix MA, ui len, cdVector X );

overror_t   __vcuf OVCUAPI  cudaMCDRow_mulC( cdPMatrix MA, ui ht, ui len, ui iRow, dComplex C );
overror_t   __vcuf OVCUAPI  cudaMCDCol_mulC( cdPMatrix MA, ui ht, ui len, ui iCol, dComplex C );
overror_t   __vcuf OVCUAPI  cudaMCDDia_mulC( cdPMatrix MA, ui len, dComplex C );

overror_t   __vcuf OVCUAPI  cudaMCDRow_mulV( cdPMatrix MA, ui ht, ui len, ui iRow, cdVector X );
overror_t   __vcuf OVCUAPI  cudaMCDCol_mulV( cdPMatrix MA, ui ht, ui len, ui iCol, cdVector X );
overror_t   __vcuf OVCUAPI  cudaMCDDia_mulV( cdPMatrix MA, ui len, cdVector X );

overror_t   __vcuf OVCUAPI  cudaMCDRow_divC( cdPMatrix MA, ui ht, ui len, ui iRow, dComplex C );
overror_t   __vcuf OVCUAPI  cudaMCDCol_divC( cdPMatrix MA, ui ht, ui len, ui iCol, dComplex C );
overror_t   __vcuf OVCUAPI  cudaMCDDia_divC( cdPMatrix MA, ui len, dComplex C );

overror_t   __vcuf OVCUAPI  cudaMCDRow_divV( cdPMatrix MA, ui ht, ui len, ui iRow, cdVector X );
overror_t   __vcuf OVCUAPI  cudaMCDCol_divV( cdPMatrix MA, ui ht, ui len, ui iCol, cdVector X );
overror_t   __vcuf OVCUAPI  cudaMCDDia_divV( cdPMatrix MA, ui len, cdVector X );

overror_t   __vcuf OVCUAPI  cudaMCDRow_divrC( cdPMatrix MA, ui ht, ui len, ui iRow, dComplex C );
overror_t   __vcuf OVCUAPI  cudaMCDCol_divrC( cdPMatrix MA, ui ht, ui len, ui iCol, dComplex C );
overror_t   __vcuf OVCUAPI  cudaMCDDia_divrC( cdPMatrix MA, ui len, dComplex C );

overror_t   __vcuf OVCUAPI  cudaMCDRow_divrV( cdPMatrix MA, ui ht, ui len, ui iRow, cdVector X );
overror_t   __vcuf OVCUAPI  cudaMCDCol_divrV( cdPMatrix MA, ui ht, ui len, ui iCol, cdVector X );
overror_t   __vcuf OVCUAPI  cudaMCDDia_divrV( cdPMatrix MA, ui len, cdVector X );

overror_t   __vcuf OVCUAPI  cusdMCDRow_addC( cdPMatrix MA, ui ht, ui len, ui iRow, dComplex *d_C );
overror_t   __vcuf OVCUAPI  cusdMCDCol_addC( cdPMatrix MA, ui ht, ui len, ui iCol, dComplex *d_C );
overror_t   __vcuf OVCUAPI  cusdMCDDia_addC( cdPMatrix MA, ui len, dComplex *d_C );
overror_t   __vcuf OVCUAPI  cusdMCDRow_subC( cdPMatrix MA, ui ht, ui len, ui iRow, dComplex *d_C );
overror_t   __vcuf OVCUAPI  cusdMCDCol_subC( cdPMatrix MA, ui ht, ui len, ui iCol, dComplex *d_C );
overror_t   __vcuf OVCUAPI  cusdMCDDia_subC( cdPMatrix MA, ui len, dComplex *d_C );
overror_t   __vcuf OVCUAPI  cusdMCDRow_subrC( cdPMatrix MA, ui ht, ui len, ui iRow, dComplex *d_C );
overror_t   __vcuf OVCUAPI  cusdMCDCol_subrC( cdPMatrix MA, ui ht, ui len, ui iCol, dComplex *d_C );
overror_t   __vcuf OVCUAPI  cusdMCDDia_subrC( cdPMatrix MA, ui len, dComplex *d_C );
overror_t   __vcuf OVCUAPI  cusdMCDRow_mulC( cdPMatrix MA, ui ht, ui len, ui iRow, dComplex *d_C );
overror_t   __vcuf OVCUAPI  cusdMCDCol_mulC( cdPMatrix MA, ui ht, ui len, ui iCol, dComplex *d_C );
overror_t   __vcuf OVCUAPI  cusdMCDDia_mulC( cdPMatrix MA, ui len, dComplex *d_C );
overror_t   __vcuf OVCUAPI  cusdMCDRow_divC( cdPMatrix MA, ui ht, ui len, ui iRow, dComplex *d_C );
overror_t   __vcuf OVCUAPI  cusdMCDCol_divC( cdPMatrix MA, ui ht, ui len, ui iCol, dComplex *d_C );
overror_t   __vcuf OVCUAPI  cusdMCDDia_divC( cdPMatrix MA, ui len, dComplex *d_C );
overror_t   __vcuf OVCUAPI  cusdMCDRow_divrC( cdPMatrix MA, ui ht, ui len, ui iRow, dComplex *d_C );
overror_t   __vcuf OVCUAPI  cusdMCDCol_divrC( cdPMatrix MA, ui ht, ui len, ui iCol, dComplex *d_C );
overror_t   __vcuf OVCUAPI  cusdMCDDia_divrC( cdPMatrix MA, ui len, dComplex *d_C );


/******  One-dimensional vector operations **********************
         performed along all rows or all columns simultaneously,
         or along the diagonal of a square matrix                */

overror_t     __vcuf OVCUAPI  cudaMCDRows_absmax( dVector Y, cdPMatrix MA, ui ht, ui len );
overror_t     __vcuf OVCUAPI  cudaMCDCols_absmax( dVector Y, cdPMatrix MA, ui ht, ui len );
overror_t     __vcuf OVCUAPI  cudaMCDRows_absmin( dVector Y, cdPMatrix MA, ui ht, ui len );
overror_t     __vcuf OVCUAPI  cudaMCDCols_absmin( dVector Y, cdPMatrix MA, ui ht, ui len );

overror_t     __vcuf OVCUAPI  cudaMCDRows_maxReIm( cdVector Y, cdPMatrix MA, ui ht, ui len );
overror_t     __vcuf OVCUAPI  cudaMCDCols_maxReIm( cdVector Y, cdPMatrix MA, ui ht, ui len );
overror_t     __vcuf OVCUAPI  cudaMCDRows_minReIm( cdVector Y, cdPMatrix MA, ui ht, ui len );
overror_t     __vcuf OVCUAPI  cudaMCDCols_minReIm( cdVector Y, cdPMatrix MA, ui ht, ui len );

overror_t     __vcuf OVCUAPI  cudaMCDRows_absmaxReIm( cdVector Y, cdPMatrix MA, ui ht, ui len );
overror_t     __vcuf OVCUAPI  cudaMCDCols_absmaxReIm( cdVector Y, cdPMatrix MA, ui ht, ui len );
overror_t     __vcuf OVCUAPI  cudaMCDRows_absminReIm( cdVector Y, cdPMatrix MA, ui ht, ui len );
overror_t     __vcuf OVCUAPI  cudaMCDCols_absminReIm( cdVector Y, cdPMatrix MA, ui ht, ui len );

overror_t     __vcuf OVCUAPI  cudaMCDRows_cabsmax( cdVector Y, cdPMatrix MA, ui ht, ui len );
overror_t     __vcuf OVCUAPI  cudaMCDCols_cabsmax( cdVector Y, cdPMatrix MA, ui ht, ui len );
overror_t     __vcuf OVCUAPI  cudaMCDRows_cabsmin( cdVector Y, cdPMatrix MA, ui ht, ui len );
overror_t     __vcuf OVCUAPI  cudaMCDCols_cabsmin( cdVector Y, cdPMatrix MA, ui ht, ui len );

overror_t     __vcuf OVCUAPI  cudaMCDRows_sabsmax( cdVector Y, cdPMatrix MA, ui ht, ui len );
overror_t     __vcuf OVCUAPI  cudaMCDCols_sabsmax( cdVector Y, cdPMatrix MA, ui ht, ui len );
overror_t     __vcuf OVCUAPI  cudaMCDRows_sabsmin( cdVector Y, cdPMatrix MA, ui ht, ui len );
overror_t     __vcuf OVCUAPI  cudaMCDCols_sabsmin( cdVector Y, cdPMatrix MA, ui ht, ui len );

overror_t     __vcuf OVCUAPI  cudaMCDRows_sum( cdVector Y, cdPMatrix MA, ui ht, ui len );
overror_t     __vcuf OVCUAPI  cudaMCDCols_sum( cdVector Y, cdPMatrix MA, ui ht, ui len );
overror_t     __vcuf OVCUAPI  cudaMCDRows_prod(cdVector Y, cdPMatrix MA, ui ht, ui len );
overror_t     __vcuf OVCUAPI  cudaMCDCols_prod(cdVector Y, cdPMatrix MA, ui ht, ui len );

overror_t     __vcuf OVCUAPI  cudaMCDDia_absmax(  double *h_RetVal, cdPMatrix MA, ui len );
overror_t     __vcuf OVCUAPI  cudaMCDDia_absmin(  double *h_RetVal, cdPMatrix MA, ui len );
overror_t     __vcuf OVCUAPI  cudaMCDDia_maxReIm(  dComplex *h_RetVal, cdPMatrix MA, ui len );
overror_t     __vcuf OVCUAPI  cudaMCDDia_minReIm(  dComplex *h_RetVal, cdPMatrix MA, ui len );
overror_t     __vcuf OVCUAPI  cudaMCDDia_absmaxReIm(  dComplex *h_RetVal, cdPMatrix MA, ui len );
overror_t     __vcuf OVCUAPI  cudaMCDDia_absminReIm(  dComplex *h_RetVal, cdPMatrix MA, ui len );
overror_t     __vcuf OVCUAPI  cudaMCDDia_cabsmax(  dComplex *h_RetVal, cdPMatrix MA, ui len );
overror_t     __vcuf OVCUAPI  cudaMCDDia_cabsmin(  dComplex *h_RetVal, cdPMatrix MA, ui len );
overror_t     __vcuf OVCUAPI  cudaMCDDia_sabsmax(  dComplex *h_RetVal, cdPMatrix MA, ui len );
overror_t     __vcuf OVCUAPI  cudaMCDDia_sabsmin(  dComplex *h_RetVal, cdPMatrix MA, ui len );
overror_t     __vcuf OVCUAPI  cudaMCDDia_sum(  dComplex *h_RetVal, cdPMatrix MA, ui len );
overror_t     __vcuf OVCUAPI  cudaMCDDia_prod( dComplex *h_RetVal, cdPMatrix MA, ui len );

overror_t     __vcuf OVCUAPI  cusdMCDDia_absmax(  double *d_RetVal, cdPMatrix MA, ui len );
overror_t     __vcuf OVCUAPI  cusdMCDDia_absmin(  double *d_RetVal, cdPMatrix MA, ui len );
overror_t     __vcuf OVCUAPI  cusdMCDDia_maxReIm(  dComplex *d_RetVal, cdPMatrix MA, ui len );
overror_t     __vcuf OVCUAPI  cusdMCDDia_minReIm(  dComplex *d_RetVal, cdPMatrix MA, ui len );
overror_t     __vcuf OVCUAPI  cusdMCDDia_absmaxReIm(  dComplex *d_RetVal, cdPMatrix MA, ui len );
overror_t     __vcuf OVCUAPI  cusdMCDDia_absminReIm(  dComplex *d_RetVal, cdPMatrix MA, ui len );
overror_t     __vcuf OVCUAPI  cusdMCDDia_cabsmax(  dComplex *d_RetVal, cdPMatrix MA, ui len );
overror_t     __vcuf OVCUAPI  cusdMCDDia_cabsmin(  dComplex *d_RetVal, cdPMatrix MA, ui len );
overror_t     __vcuf OVCUAPI  cusdMCDDia_sabsmax(  dComplex *d_RetVal, cdPMatrix MA, ui len );
overror_t     __vcuf OVCUAPI  cusdMCDDia_sabsmin(  dComplex *d_RetVal, cdPMatrix MA, ui len );
overror_t     __vcuf OVCUAPI  cusdMCDDia_sum(  dComplex *d_RetVal, cdPMatrix MA, ui len );
overror_t     __vcuf OVCUAPI  cusdMCDDia_prod( dComplex *d_RetVal, cdPMatrix MA, ui len );

overror_t  __vcuf OVCUAPI  cudaMCDRows_runsum( cdPMatrix MA, ui ht, ui len );
overror_t  __vcuf OVCUAPI  cudaMCDCols_runsum( cdPMatrix MA, ui ht, ui len );
overror_t  __vcuf OVCUAPI  cudaMCDRows_runprod( cdPMatrix MA, ui ht, ui len );
overror_t  __vcuf OVCUAPI  cudaMCDCols_runprod( cdPMatrix MA, ui ht, ui len );

overror_t  __vcuf OVCUAPI  cudaMCDRows_rotate( cdPMatrix MA, ui ht, ui len, ssize_t pos );
overror_t  __vcuf OVCUAPI  cudaMCDCols_rotate( cdPMatrix MA, ui ht, ui len, ssize_t pos );
overror_t  __vcuf OVCUAPI  cudaMCDRows_rotate_buf( cdPMatrix MA, ui ht, ui len, ssize_t pos, cdPMatrix MBuf );
overror_t  __vcuf OVCUAPI  cudaMCDCols_rotate_buf( cdPMatrix MA, ui ht, ui len, ssize_t pos, cdPMatrix MBuf );
overror_t  __vcuf OVCUAPI  cudaMCDRows_reflect( cdPMatrix MA, ui ht, ui len );
overror_t  __vcuf OVCUAPI  cudaMCDCols_reflect( cdPMatrix MA, ui ht, ui len );
overror_t  __vcuf OVCUAPI  cudaMCDRows_rev( cdPMatrix MA, ui ht, ui len );
overror_t  __vcuf OVCUAPI  cudaMCDCols_rev( cdPMatrix MA, ui ht, ui len );

/********  Operations involving two rows or two colums of one matrix  *****/

overror_t   __vcuf OVCUAPI  cudaMCDRows_exchange( cdPMatrix MA, ui ht, ui len, ui i1, ui i2 );
overror_t   __vcuf OVCUAPI  cudaMCDCols_exchange( cdPMatrix MA, ui ht, ui len, ui i1, ui i2 );

overror_t   __vcuf OVCUAPI  cudaMCDRows_add( cdPMatrix MA, ui ht, ui len, ui destRow, ui sourceRow );
overror_t   __vcuf OVCUAPI  cudaMCDCols_add( cdPMatrix MA, ui ht, ui len, ui destCol, ui sourceCol );

overror_t   __vcuf OVCUAPI  cudaMCDRows_sub( cdPMatrix MA, ui ht, ui len, ui destRow, ui sourceRow );
overror_t   __vcuf OVCUAPI  cudaMCDCols_sub( cdPMatrix MA, ui ht, ui len, ui destCol, ui sourceCol );

overror_t   __vcuf OVCUAPI  cudaMCDRows_Cadd( cdPMatrix MA, ui ht, ui len, ui destRow, ui sourceRow, dComplex C );
overror_t   __vcuf OVCUAPI  cudaMCDCols_Cadd( cdPMatrix MA, ui ht, ui len, ui destCol, ui sourceCol, dComplex C );
overror_t   __vcuf OVCUAPI  cusdMCDRows_Cadd( cdPMatrix MA, ui ht, ui len, ui destRow, ui sourceRow, dComplex *d_C );
overror_t   __vcuf OVCUAPI  cusdMCDCols_Cadd( cdPMatrix MA, ui ht, ui len, ui destCol, ui sourceCol, dComplex *d_C );

overror_t   __vcuf OVCUAPI  cudaMCDRows_lincomb( cdPMatrix MA, ui ht, ui len, ui destRow,  dComplex  destC,
                                                                 ui srceRow,  dComplex  srceC );
overror_t   __vcuf OVCUAPI  cudaMCDCols_lincomb( cdPMatrix MA, ui ht, ui len, ui destCol,  dComplex  destC,
                                                                 ui srceCol,  dComplex  srceC );
overror_t   __vcuf OVCUAPI  cusdMCDRows_lincomb( cdPMatrix MA, ui ht, ui len, ui destRow,  dComplex  *d_destC,
                                                                 ui srceRow,  dComplex  *d_srceC );
overror_t   __vcuf OVCUAPI  cusdMCDCols_lincomb( cdPMatrix MA, ui ht, ui len, ui destCol,  dComplex  *d_destC,
                                                                 ui srceCol,  dComplex  *d_srceC );


/**************  Transposing and rotating a matrix **********************/

overror_t  __vcuf OVCUAPI  cudaMCDtranspose( cdPMatrix MTr, cdPMatrix MA, ui htTr, ui lenTr );
overror_t  __vcuf OVCUAPI  cudaMCDhermconj( cdPMatrix MHConj, cdPMatrix MA, ui htTr, ui lenTr );
overror_t  __vcuf OVCUAPI  cudaMCDrotate90(  cdPMatrix MRot, cdPMatrix MA, ui htRot, ui lenRot );
#define     cudaMCDrotate180( MRot, MA, htRot, lenRot ) cudaVCD_rev( MRot, MA, (htRot)*(lenRot) )
overror_t  __vcuf OVCUAPI  cudaMCDrotate270( cdPMatrix MRot, cdPMatrix MA, ui htRot, ui lenRot );
overror_t  __vcuf OVCUAPI  cudaMCDtranspose_buf( cdPMatrix MTr, cdPMatrix MA, ui htTr, ui lenTr, cdPMatrix MBuf );


/************************ Matrix Arithmetics *************************/

#define cudaMCDaddM( MC, MA, MB, htA, lenA )      cudaVCD_addV( MC, MA, MB, (htA)*(lenA) )
overror_t __vcuf OVCUAPI  cudaMCDaddMT( cdPMatrix MC, cdPMatrix MA, cdPMatrix MB, ui htA, ui lenA );
#define cudaMCDsubM( MC, MA, MB, htA, lenA )      cudaVCD_subV( MC, MA, MB, (htA)*(lenA) )
overror_t __vcuf OVCUAPI  cudaMCDsubMT( cdPMatrix MC, cdPMatrix MA, cdPMatrix MB, ui htA, ui lenA );
overror_t __vcuf OVCUAPI  cudaMCDsubrMT( cdPMatrix MC, cdPMatrix MA, cdPMatrix MB, ui htA, ui lenA );

#define cudaMCDmulC( MB, MA, htA, lenA, C )       cudaVCD_mulC( MB, MA, (htA)*(lenA), C )
#define cudaMCDdivC( MB, MA, htA, lenA, C )       cudaVCD_divC( MB, MA, (htA)*(lenA), C )
#define cudaMCDmulReC( MB, MA, htA, lenA, CRe )   cudaVCD_mulReC( MB, MA, (htA)*(lenA), CRe )
#define cudaMCDdivReC( MB, MA, htA, lenA, CRe )   cudaVCD_divReC( MB, MA, (htA)*(lenA), CRe )
#define cudaMCDlincomb( MC, MA, MB, htA, lenA, CA, CB ) cudaVCD_lincomb( MC, MA, MB, (htA)*(lenA), CA, CB )

#define cusdMCDmulC( MB, MA, htA, lenA, d_C )       cusdVCD_mulC( MB, MA, (htA)*(lenA), d_C )
#define cusdMCDdivC( MB, MA, htA, lenA, d_C )       cusdVCD_divC( MB, MA, (htA)*(lenA), d_C )
#define cusdMCDmulReC( MB, MA, htA, lenA, d_CRe )   cusdVCD_mulReC( MB, MA, (htA)*(lenA), d_CRe )
#define cusdMCDdivReC( MB, MA, htA, lenA, d_CRe )   cusdVCD_divReC( MB, MA, (htA)*(lenA), d_CRe )
#define cusdMCDlincomb( MC, MA, MB, htA, lenA, d_CA, d_CB ) cusdVCD_lincomb( MC, MA, MB, (htA)*(lenA), d_CA, d_CB )

overror_t  __vcuf OVCUAPI  cudaMCDmulV( cdVector Y, cdPMatrix MA, cdVector X, ui htA, ui lenA );
overror_t  __vcuf OVCUAPI  cudaMCDTmulV( cdVector Y, cdPMatrix MA, cdVector X, ui htA, ui lenA );
overror_t  __vcuf OVCUAPI   cudaVCDmulM( cdVector Y, cdVector X, cdPMatrix MA, ui htA, ui lenA );
overror_t  __vcuf OVCUAPI   cudaVCDmulMT( cdVector Y, cdVector X, cdPMatrix MA, ui htA, ui lenA );
overror_t  __vcuf OVCUAPI  cudaMCDmulM( cdPMatrix MC, cdPMatrix MA, cdPMatrix MB, ui htA, ui lenA, ui lenB );
overror_t  __vcuf OVCUAPI  cudaMCDmulMT( cdPMatrix MC, cdPMatrix MA, cdPMatrix MB, ui htA, ui lenA, ui htB );
overror_t  __vcuf OVCUAPI  cudaMCDmulMH( cdPMatrix MC, cdPMatrix MA, cdPMatrix MB, ui htA, ui lenA, ui htB );
overror_t  __vcuf OVCUAPI  cudaMCDTmulM( cdPMatrix MC, cdPMatrix MA, cdPMatrix MB, ui htA, ui lenA, ui lenB );
overror_t  __vcuf OVCUAPI  cudaMCDHmulM( cdPMatrix MC, cdPMatrix MA, cdPMatrix MB, ui htA, ui lenA, ui lenB );
overror_t  __vcuf OVCUAPI  cudaMCDTmulMT( cdPMatrix MC, cdPMatrix MA, cdPMatrix MB, ui htA, ui lenA, ui htB );
overror_t  __vcuf OVCUAPI  cudaMCDTmulMH( cdPMatrix MC, cdPMatrix MA, cdPMatrix MB, ui htA, ui lenA, ui htB );
overror_t  __vcuf OVCUAPI  cudaMCDdiamulM( cdPMatrix MC, cdPMatrix MADia, cdPMatrix MB, ui htB, ui lenB );
overror_t  __vcuf OVCUAPI  cudaMCDdiamulMT( cdPMatrix MC, cdPMatrix MADia, cdPMatrix MB, ui htB, ui lenB );
overror_t  __vcuf OVCUAPI  cudaMCDmulMdia( cdPMatrix MC, cdPMatrix MA, cdPMatrix MBDia, ui htA, ui lenA );
overror_t  __vcuf OVCUAPI  cudaMCDTmulMdia( cdPMatrix MC, cdPMatrix MA, cdPMatrix MBDia, ui htA, ui lenA );


/*************  Two-Dimensional Fourier-Transform Methods *****************/

overror_t  __vcuf OVCUAPI  cudaMCDFFT( cdPMatrix MY, cdPMatrix MX, ui ht, ui len, int dir );
overror_t  __vcuf OVCUAPI  cudaMCDfilter( cdPMatrix MY, cdPMatrix MX, cdPMatrix MFlt, ui ht, ui len );
overror_t  __vcuf OVCUAPI  cudaMCDRows_FFT( cdPMatrix MY, cdPMatrix MX, ui ht, ui len, int dir );
overror_t  __vcuf OVCUAPI  cudaMCDCols_FFT( cdPMatrix MY, cdPMatrix MX, ui ht, ui len, int dir );

/**************************  Input and Output  **************************
	The input/output functions involve memory transfers from device
	to host memory or vice versa. The generic cudaMCD_input/output functions
	allocate their own host buffers, whereas the cudaMCD_xxx_buf functions
	take a user-supplied buffer vector h_Wk (size must be >= ht*len )
	and are much more efficient.                                       */

#define cudaMCDprint( MA, ht, len )  cudaMCDfprint( stdout, MA, ht, len, 80 )
overror_t __vf cudaMCDfprint( FILE *stream, cdPMatrix MA, ui ht, ui len, unsigned linewidth );
overror_t __vf cudaMCDcprint( cdPMatrix MA, ui ht, ui len );
#define cudaMCDprint_buf( MA, ht, len, h_Wk )  cudaMCDfprint_buf( stdout, MA, ht, len, 80, h_Wk )
overror_t __vf cudaMCDfprint_buf( FILE *stream, cdPMatrix MA, ui ht, ui len, unsigned linewidth, cdVector h_Wk );
overror_t __vf cudaMCDcprint_buf( cdPMatrix MA, ui ht, ui len, cdVector h_Wk );
overror_t __vf cudaMCDwrite( FILE *stream, cdPMatrix X, ui ht, ui len  );
overror_t __vf cudaMCDwrite_buf( FILE *stream, cdPMatrix X, ui ht, ui len, cdVector h_Wk );
#if !((defined __BORLANDC__) && (__BORLANDC__ < 0x710))
		/* modern compiler versions:  */
	overror_t __vf cudaMCDread( cdPMatrix X, ui ht, ui len, FILE *stream );
	overror_t __vf cudaMCDread_buf( cdPMatrix X, ui ht, ui len, FILE *stream, cdVector h_Wk );
#else /* older Borland compiler versions need separate implementation */
	overror_t __vf cudaMCDread1( cdPMatrix X, ui ht, ui len, FILE *stream );
	overror_t __vf cudaMCDread1_buf( cdPMatrix X, ui ht, ui len, FILE *stream, cdVector h_Wk );
	#define cudaMCDread      cudaMCDread1
	#define cudaMCDread_buf  cudaMCDread1_buf
#endif
#define cudaMCDstore( str, MA, ht, len ) cudaVCD_store( str, MA, (len)*(ht) )
#define cudaMCDrecall( MA, ht, len, str) cudaVCD_recall( MA, (len)*(ht), str)
#define cudaMCDstore_buf( str, MA, ht, len, h_Wk ) cudaVCD_store( str, MA, (len)*(ht), h_Wk )
#define cudaMCDrecall_buf( MA, ht, len, str, h_Wk) cudaVCD_recall( MA, (len)*(ht), str, h_Wk)



/***************************************************************************
    cudaMCD_func (working on matrices in device memory, input type cdMatrix, 
	             scalar parameters reside on host and are passed by value)
    cusdMCD_func (as cudaMCD_func except scalar parameters reside on device 
	             and are passed by address)                                 */



/***************************************************************************
 *  The following definitions are needed to access individual elements,    *
 *  and row pointers. As all addresses point to device memory, the usual   *
 *  mechanism of accessing elements, i.e., writing something like MA[m][n] *
 *  is not possible here!                                                  *
 *  Pro forma, the distinction between the data types cdMatrix and         *
 *  cdPMatrix is kept. However, in the present implementation, both of     *
 *  these types actually contain a pointer to the matrix element [0][0].   *
 *  Pro forma, the distinction between the data types cdMatrix and         *
 *  cdPMatrix is kept. However, in the present implementation, both of     *
 *  these types actually contain a pointer to the matrix element [0][0].   *
 *  For C++, inline functions ensure proper type checking at compile time, *
 *  while for plain-C, only a less safe type-cast is possible.             *
 ***************************************************************************/

#ifdef __cplusplus

/***  Addressing single elements of dynamically allocated matrices: ******/

inline void    cudaMCD_setElement( cdMatrix MA, ui ht, ui len, ui m, ui n, dComplex C )
	{	cudaMCDsetElement( (cdPMatrix)(MA), ht, len, m, n, C );}
inline void    cusdMCD_setElement( cdMatrix MA, ui ht, ui len, ui m, ui n, dComplex *d_C )
	{	cusdMCDsetElement( (cdPMatrix)(MA), ht, len, m, n, C );}
inline void    cudaMCD_getElement( dComplex *h_y, cdMatrix MA, ui ht, ui len, ui m, ui n )
	{	cudaMCDgetElement( h_y, (cdPMatrix)(MA), ht, len, m, n );}
inline void    cusdMCD_getElement( dComplex *d_y, cdMatrix MA, ui ht, ui len, ui m, ui n )
	{	cusdMCDgetElement( d_y, (cdPMatrix)(MA), ht, len, m, n );}
inline dComplex * cudaMCD_Pelement( cdMatrix MA, ui ht, ui len, ui m, ui n )
	{	return cudaMCDPelement( (cdPMatrix)(MA), ht, len, m, n );}
#if defined _CMATH_CLASSDEFS
} // the following function cannot be extern "C", if fComplex is a class
#endif
inline dComplex   cudaMCD_element( cdMatrix MA, ui ht, ui len, ui m, ui n )
{	return cudaMCDelement( (cdPMatrix)(MA), ht, len, m, n );}
#if defined _CMATH_CLASSDEFS
extern "C" {
#endif

 /****************  Initialization  ****************************************/

inline overror_t  cudaMCD_equ0( cdMatrix MA, ui ht, ui len )
	{	return cudaVCD_equ0( (cdPMatrix)MA, (ht)*(len) ); }
inline overror_t  cudaMCD_equ1( cdMatrix MA, ui len )
	{	return cudaMCDequ1( (cdPMatrix)(MA), len );} /* identity matrix */
inline overror_t  cudaMCD_equm1( cdMatrix MA, ui len )
	{	return cudaMCDequm1( (cdPMatrix)(MA), len );} /* neg. identity matrix */
inline overror_t  cudaMCD_randomLC( cdMatrix MA, ui ht, ui len, long seed, dComplex MinVal, dComplex MaxVal, V_RANDOMLCSTATE *h_state )
	{	return cudaVCD_randomLC( (cdPMatrix)(MA), (ht)*(len), seed, MinVal, MaxVal, h_state );}
inline overror_t  cudaMCD_random( cdMatrix MA, ui ht, ui len, long seed, dComplex MinVal, dComplex MaxVal )
	{	return cudaVCD_random( (cdPMatrix)(MA), (ht)*(len), seed, MinVal, MaxVal );}
inline overror_t  cusdMCD_randomLC( cdMatrix MA, ui ht, ui len, long seed, dComplex *d_MinVal, dComplex *d_MaxVal, V_RANDOMLCSTATE *h_state )
	{	return cusdVCD_randomLC( (cdPMatrix)(MA), (ht)*(len), seed, d_MinVal, d_MaxVal, h_state );}
inline overror_t  cusdMCD_random( cdMatrix MA, ui ht, ui len, long seed, dComplex *d_MinVal, dComplex *d_MaxVal )
	{	return cusdVCD_random( (cdPMatrix)(MA), (ht)*(len), seed, d_MinVal, d_MaxVal );}

inline overror_t  cudaMCD_outerprod( cdMatrix MA, cdVector X,  cdVector Y, ui ht, ui len )
	{	return cudaMCDouterprod( (cdPMatrix)(MA), X, Y, ht, len );}
                       /* sizX=ht, sizY=len */
inline overror_t  cudaMCD_Row_equ0( cdMatrix MA, ui ht, ui len, ui iRow )
	{	return cudaMCDRow_equ0( (cdPMatrix)MA, ht, len, iRow );}
inline overror_t  cudaMCD_Col_equ0( cdMatrix MA, ui ht, ui len, ui iRow )
	{	return cudaMCDCol_equ0( (cdPMatrix)MA, ht, len, iRow );}
inline overror_t  cudaMCD_Dia_equ0( cdMatrix MA, ui len )
	{	return cudaMCDDia_equ0( (cdPMatrix)(MA), len );}

inline overror_t  cudaMCD_Row_equC( cdMatrix MA, ui ht, ui len, ui iRow, dComplex C )
	{	return cudaMCDRow_equC( (cdPMatrix)MA, ht, len, iRow, C );}
inline overror_t  cudaMCD_Col_equC( cdMatrix MA, ui ht, ui len, ui iRow, dComplex C )
	{	return cudaMCDCol_equC( (cdPMatrix)MA, ht, len, iRow, C );}
inline overror_t  cudaMCD_Dia_equC( cdMatrix MA, ui len, dComplex C )
	{	return cudaMCDDia_equC( (cdPMatrix)(MA), len, C );}

inline overror_t  cusdMCD_Row_equC( cdMatrix MA, ui ht, ui len, ui iRow, dComplex *d_C )
	{	return cusdMCDRow_equC( (cdPMatrix)MA, ht, len, iRow, d_C );}
inline overror_t  cusdMCD_Col_equC( cdMatrix MA, ui ht, ui len, ui iRow, dComplex *d_C )
	{	return cusdMCDCol_equC( (cdPMatrix)MA, ht, len, iRow, d_C );}
inline overror_t  cusdMCD_Dia_equC( cdMatrix MA, ui len, dComplex *d_C )
	{	return cusdMCDDia_equC( (cdPMatrix)(MA), len, d_C );}

inline overror_t  cudaMCD_Row_equV( cdMatrix MA, ui ht, ui len, ui iRow, cdVector X )
	{	return cudaMCDRow_equV( (cdPMatrix)MA, ht, len, iRow, X );}
inline overror_t  cudaMCD_Col_equV( cdMatrix MA, ui ht, ui len, ui iRow, cdVector X )
	{	return cudaMCDCol_equV( (cdPMatrix)MA, ht, len, iRow, X );}
inline overror_t  cudaMCD_Dia_equV( cdMatrix MA, ui len, cdVector X )
	{	return cudaMCDDia_equV( (cdPMatrix)(MA), len, X );}

inline overror_t  cudaMCD_Trd_equM( cdMatrix MA, cdMatrix MTrd, ui len )
	{	return cudaMCDTrd_equM( (cdPMatrix)(MA), (cdPMatrix)(MTrd), len );}
inline overror_t  cudaMCD_Trd_extract( cdMatrix MTrd, cdMatrix MA, ui len )
	{	return cudaMCDTrd_extract( (cdPMatrix)(MTrd), (cdPMatrix)(MA), len );}

inline overror_t cudaMCD_equM( cdMatrix MB, cdMatrix MA, ui ht, ui len )
	{	return cudaVCD_equV( (cdPMatrix)MB, (cdPMatrix)MA, (ht)*(len) );}
inline overror_t cudaMCD_equMhost( cdMatrix d_MB, cdMatrix h_MA, ui ht, ui len )
	{	return cudaVCD_equVhost( (cdPMatrix)d_MB, (h_MA)[0], (ht)*(len) );}
inline overror_t MCD_equMdevice( cdMatrix h_MB, cdMatrix d_MA, ui ht, ui len )
	{	return VCD_equVdevice( h_MB[0], (cdPMatrix)d_MA, (ht)*(len) );}
inline overror_t cudaMCD_neg( cdMatrix MB, cdMatrix MA, ui ht, ui len )
	{	return cudaVCD_neg( (cdPMatrix)(MB), (cdPMatrix)(MA), (ht)*(len) );}
inline overror_t  cudaMCD_UequL( cdMatrix MA, ui len )
	{	return cudaMCDUequL( (cdPMatrix)(MA), len );}
inline overror_t  cudaMCD_LequU( cdMatrix MA, ui len )
	{	return cudaMCDLequU( (cdPMatrix)(MA), len );}

            /* data-type conversions:  */
inline overror_t cudaM_CFtoCD( cdMatrix MCD, cfMatrix MCF, ui ht, ui len )
	{	return cudaV_CFtoCD( (cdPMatrix)(MCD), (cfPMatrix)(MCF), (ht)*(len) );}

inline overror_t cudaMD_CtoRe( dMatrix MY, cdMatrix MCX, ui ht, ui len )
	{	return cudaVD_CtoRe( (dPMatrix)(MY),  (cdPMatrix)(MCX), (ht)*(len) );}
inline overror_t cudaMD_CtoIm( dMatrix MY, cdMatrix MCX, ui ht, ui len )
	{	return cudaVD_CtoIm( (dPMatrix)(MY),  (cdPMatrix)(MCX), (ht)*(len) );}
inline overror_t cudaMD_CtoReIm( dMatrix MYRe, dMatrix MYIm, cdMatrix MCX, ui ht, ui len )
	{	return cudaVD_CtoReIm( (dPMatrix)(MYRe), (dPMatrix)(MYIm), (cdPMatrix)(MCX), (ht)*(len) );}
inline overror_t cudaMD_RetoC( cdMatrix MCY, dMatrix MX, ui ht, ui len )
	{	return cudaVD_RetoC( (cdPMatrix)(MCY), (dPMatrix)(MX),  (ht)*(len) );}
inline overror_t cudaMD_ImtoC( cdMatrix MCY, dMatrix MX, ui ht, ui len )
	{	return cudaVD_ImtoC( (cdPMatrix)(MCY), (dPMatrix)(MX),  (ht)*(len) );}
inline overror_t cudaMD_ReImtoC( cdMatrix MCYRe, cdMatrix MCYIm, dMatrix MX, ui ht, ui len )
	{	return cudaVD_ReImtoC( (cdPMatrix)(MCYRe), (dPMatrix)(MCYIm), (dPMatrix)(MX),  (ht)*(len) );}

/********  Extracting a submatrix and copying a submatrix back  *********/

inline overror_t cudaMCD_submatrix( cdMatrix MSub, ui subHt, ui subLen, cdMatrix MSrce, ui srceHt, ui srceLen,
                      ui firstRowInCol, ui sampInCol, ui firstColInRow, ui sampInRow )
	{	return cudaMCDsubmatrix(  (cdPMatrix)(MSub), subHt, subLen,
		                         (cdPMatrix)(MSrce), srceHt, srceLen,
								 firstRowInCol, sampInCol, firstColInRow, sampInRow ); }

inline overror_t cudaMCD_submatrix_equM( cdMatrix MDest, ui destHt, ui destLen,
                           ui firstRowInCol, ui sampInCol, ui firstColInRow, ui sampInRow,
                           cdMatrix MSrce, ui srceHt, ui srceLen )
	{	return cudaMCDsubmatrix_equM(  (cdPMatrix)(MDest), destHt, destLen,
                             firstRowInCol, sampInCol, firstColInRow, sampInRow,
							 (cdPMatrix)(MSrce), srceHt, srceLen );}

inline overror_t cudaMCD_equMblock( cdMatrix MSub, ui subHt, ui subLen, cdMatrix MSrce, ui srceHt, ui srceLen,
                      ui firstRowInCol, ui firstColInRow )
{	return cudaMCDequMblock(  (cdPMatrix)(MSub), subHt, subLen,
						   (cdPMatrix)(MSrce), srceHt, srceLen, firstRowInCol, firstColInRow );}

inline overror_t cudaMCD_block_equM( cdMatrix MDest, ui destHt, ui destLen,
                       ui firstRowInCol, ui firstColInRow,
                       cdMatrix MSrce, ui srceHt, ui srceLen )
	{	return cudaMCDblock_equM( (cdPMatrix)(MDest), destHt, destLen,
                             firstRowInCol, firstColInRow,
							 (cdPMatrix)(MSrce), srceHt, srceLen );}

inline overror_t cudaMCD_equMblockT( cdMatrix MSub, ui subHt, ui subLen, cdMatrix MSrce, ui srceHt, ui srceLen,
                      ui firstRowInCol, ui firstColInRow )
	{	return cudaMCDequMblockT(  (cdPMatrix)(MSub), subHt, subLen,
                             (cdPMatrix)(MSrce), srceHt, srceLen,
							 firstRowInCol, firstColInRow );}

inline overror_t cudaMCD_block_equMT( cdMatrix MDest, ui destHt, ui destLen,
                       ui firstRowInCol, ui firstColInRow,
                       cdMatrix MSrce, ui srceHt, ui srceLen )
	{	return cudaMCDblock_equMT( (cdPMatrix)(MDest), destHt, destLen,
                             firstRowInCol, firstColInRow,
							 (cdPMatrix)(MSrce), srceHt, srceLen );}

/*****   Extracting a single row or a single column or the diagonal  ******
 *       and storing it into a vector                                     */

inline overror_t cudaMCD_Row_extract( cdVector Y, cdMatrix MA, ui ht, ui len, ui iRow ) 
	{	return cudaMCDRow_extract( Y, (cdPMatrix)(MA), ht, len, iRow );}
inline overror_t cudaMCD_Col_extract( cdVector Y, cdMatrix MA, ui ht, ui len, ui iCol ) 
	{	return cudaMCDCol_extract( Y, (cdPMatrix)(MA), ht, len, iCol );}
inline overror_t cudaMCD_Dia_extract( cdVector Y, cdMatrix MA, ui len )
	{	return cudaMCDDia_extract( Y, (cdPMatrix)(MA), len );}


/**************  Deleting or inserting a row or a column   ***************/

inline overror_t cudaMCD_Row_delete( cdMatrix MB, cdMatrix MA, ui htA, ui lenA, ui iRow )
	{	return cudaMCDRow_delete( (cdPMatrix)(MB), (cdPMatrix)(MA), htA, lenA, iRow );}
inline overror_t cudaMCD_Col_delete( cdMatrix MB, cdMatrix MA, ui htA, ui lenA, ui iCol )
	{	return cudaMCDCol_delete( (cdPMatrix)(MB), (cdPMatrix)(MA), htA, lenA, iCol );}
inline overror_t cudaMCD_Row_insert( cdMatrix MB, cdMatrix MA, ui htB, ui lenB, ui iRow, cdVector X )
	{	return cudaMCDRow_insert( (cdPMatrix)(MB), (cdPMatrix)(MA), htB, lenB, iRow, X );}
inline overror_t cudaMCD_Col_insert( cdMatrix MB, cdMatrix MA, ui htB, ui lenB, ui iCol, cdVector X )
	{	return cudaMCDCol_insert( (cdPMatrix)(MB), (cdPMatrix)(MA), htB, lenB, iCol, X );}


/*****************    Basic arithmetic operations *********************
                      performed on one single row,
                      or one single column of any matrix,
                      or on the diagonal of a square matrix

    Note: In contrast to the analogous VectorLib functions, the operations
    are performed in-place, i.e. the input matrix itself is changed  */

inline overror_t cudaMCD_Row_neg( cdMatrix MA, ui ht, ui len, ui iRow )
	{	return cudaMCDRow_neg( (cdPMatrix)(MA), ht, len, iRow );}
inline overror_t cudaMCD_Col_neg( cdMatrix MA, ui ht, ui len, ui iCol )
	{	return cudaMCDCol_neg( (cdPMatrix)(MA), ht, len, iCol );}
inline overror_t cudaMCD_Row_conj( cdMatrix MA, ui ht, ui len, ui iRow )
	{	return cudaMCDRow_conj( (cdPMatrix)(MA), ht, len, iRow );}
inline overror_t cudaMCD_Col_conj( cdMatrix MA, ui ht, ui len, ui iCol )
	{	return cudaMCDCol_conj( (cdPMatrix)(MA), ht, len, iCol );}

inline overror_t cudaMCD_Row_addC( cdMatrix MA, ui ht, ui len, ui iRow, dComplex C )
	{	return cudaMCDRow_addC( (cdPMatrix)(MA), ht, len, iRow, C );}
inline overror_t cudaMCD_Col_addC( cdMatrix MA, ui ht, ui len, ui iCol, dComplex C )
	{	return cudaMCDCol_addC( (cdPMatrix)(MA), ht, len, iCol, C );}
inline overror_t cudaMCD_Dia_addC( cdMatrix MA, ui len, dComplex C )
	{	return cudaMCDDia_addC( (cdPMatrix)(MA), len, C );}
inline overror_t cusdMCD_Row_addC( cdMatrix MA, ui ht, ui len, ui iRow, dComplex *d_C )
	{	return cusdMCDRow_addC( (cdPMatrix)(MA), ht, len, iRow, d_C );}
inline overror_t cusdMCD_Col_addC( cdMatrix MA, ui ht, ui len, ui iCol, dComplex *d_C )
	{	return cusdMCDCol_addC( (cdPMatrix)(MA), ht, len, iCol, d_C );}
inline overror_t cusdMCD_Dia_addC( cdMatrix MA, ui len, dComplex *d_C )
	{	return cusdMCDDia_addC( (cdPMatrix)(MA), len, d_C );}

inline overror_t cudaMCD_Row_addV( cdMatrix MA, ui ht, ui len, ui iRow, cdVector X )
	{	return cudaMCDRow_addV( (cdPMatrix)(MA), ht, len, iRow, X );}
inline overror_t cudaMCD_Col_addV( cdMatrix MA, ui ht, ui len, ui iCol, cdVector X )
	{	return cudaMCDCol_addV( (cdPMatrix)(MA), ht, len, iCol, X );}
inline overror_t cudaMCD_Dia_addV( cdMatrix MA, ui len, cdVector X )
	{	return cudaMCDDia_addV( (cdPMatrix)(MA), len, X );}

inline overror_t cudaMCD_Row_subC( cdMatrix MA, ui ht, ui len, ui iRow, dComplex C )
	{	return cudaMCDRow_subC( (cdPMatrix)(MA), ht, len, iRow, C );}
inline overror_t cudaMCD_Col_subC( cdMatrix MA, ui ht, ui len, ui iCol, dComplex C )
	{	return cudaMCDCol_subC( (cdPMatrix)(MA), ht, len, iCol, C );}
inline overror_t cudaMCD_Dia_subC( cdMatrix MA, ui len, dComplex C )
	{	return cudaMCDDia_subC( (cdPMatrix)(MA), len, C );}
inline overror_t cusdMCD_Row_subC( cdMatrix MA, ui ht, ui len, ui iRow, dComplex *d_C )
	{	return cusdMCDRow_subC( (cdPMatrix)(MA), ht, len, iRow, d_C );}
inline overror_t cusdMCD_Col_subC( cdMatrix MA, ui ht, ui len, ui iCol, dComplex *d_C )
	{	return cusdMCDCol_subC( (cdPMatrix)(MA), ht, len, iCol, d_C );}
inline overror_t cusdMCD_Dia_subC( cdMatrix MA, ui len, dComplex *d_C )
	{	return cusdMCDDia_subC( (cdPMatrix)(MA), len, d_C );}

inline overror_t cudaMCD_Row_subV( cdMatrix MA, ui ht, ui len, ui iRow, cdVector X )
	{	return cudaMCDRow_subV( (cdPMatrix)(MA), ht, len, iRow, X );}
inline overror_t cudaMCD_Col_subV( cdMatrix MA, ui ht, ui len, ui iCol, cdVector X )
	{	return cudaMCDCol_subV( (cdPMatrix)(MA), ht, len, iCol, X );}
inline overror_t cudaMCD_Dia_subV( cdMatrix MA, ui len, cdVector X )
	{	return cudaMCDDia_subV( (cdPMatrix)(MA), len, X );}

inline overror_t cudaMCD_Row_subrC( cdMatrix MA, ui ht, ui len, ui iRow, dComplex C )
	{	return cudaMCDRow_subrC( (cdPMatrix)(MA), ht, len, iRow, C );}
inline overror_t cudaMCD_Col_subrC( cdMatrix MA, ui ht, ui len, ui iCol, dComplex C )
	{	return cudaMCDCol_subrC( (cdPMatrix)(MA), ht, len, iCol, C );}
inline overror_t cudaMCD_Dia_subrC( cdMatrix MA, ui len, dComplex C )
	{	return cudaMCDDia_subrC( (cdPMatrix)(MA), len, C );}
inline overror_t cusdMCD_Row_subrC( cdMatrix MA, ui ht, ui len, ui iRow, dComplex *d_C )
	{	return cusdMCDRow_subrC( (cdPMatrix)(MA), ht, len, iRow, d_C );}
inline overror_t cusdMCD_Col_subrC( cdMatrix MA, ui ht, ui len, ui iCol, dComplex *d_C )
	{	return cusdMCDCol_subrC( (cdPMatrix)(MA), ht, len, iCol, d_C );}
inline overror_t cusdMCD_Dia_subrC( cdMatrix MA, ui len, dComplex *d_C )
	{	return cusdMCDDia_subrC( (cdPMatrix)(MA), len, d_C );}

inline overror_t cudaMCD_Row_subrV( cdMatrix MA, ui ht, ui len, ui iRow, cdVector X )
	{	return cudaMCDRow_subrV( (cdPMatrix)(MA), ht, len, iRow, X );}
inline overror_t cudaMCD_Col_subrV( cdMatrix MA, ui ht, ui len, ui iCol, cdVector X )
	{	return cudaMCDCol_subrV( (cdPMatrix)(MA), ht, len, iCol, X );}
inline overror_t cudaMCD_Dia_subrV( cdMatrix MA, ui len, cdVector X )
	{	return cudaMCDDia_subrV( (cdPMatrix)(MA), len, X );}

inline overror_t cudaMCD_Row_mulC( cdMatrix MA, ui ht, ui len, ui iRow, dComplex C )
	{	return cudaMCDRow_mulC( (cdPMatrix)(MA), ht, len, iRow, C );}
inline overror_t cudaMCD_Col_mulC( cdMatrix MA, ui ht, ui len, ui iCol, dComplex C )
	{	return cudaMCDCol_mulC( (cdPMatrix)(MA), ht, len, iCol, C );}
inline overror_t cudaMCD_Dia_mulC( cdMatrix MA, ui len, dComplex C )
	{	return cudaMCDDia_mulC( (cdPMatrix)(MA), len, C );}
inline overror_t cusdMCD_Row_mulC( cdMatrix MA, ui ht, ui len, ui iRow, dComplex *d_C )
	{	return cusdMCDRow_mulC( (cdPMatrix)(MA), ht, len, iRow, d_C );}
inline overror_t cusdMCD_Col_mulC( cdMatrix MA, ui ht, ui len, ui iCol, dComplex *d_C )
	{	return cusdMCDCol_mulC( (cdPMatrix)(MA), ht, len, iCol, d_C );}
inline overror_t cusdMCD_Dia_mulC( cdMatrix MA, ui len, dComplex *d_C )
	{	return cusdMCDDia_mulC( (cdPMatrix)(MA), len, d_C );}

inline overror_t cudaMCD_Row_mulV( cdMatrix MA, ui ht, ui len, ui iRow, cdVector X )
	{	return cudaMCDRow_mulV( (cdPMatrix)(MA), ht, len, iRow, X );}
inline overror_t cudaMCD_Col_mulV( cdMatrix MA, ui ht, ui len, ui iCol, cdVector X )
	{	return cudaMCDCol_mulV( (cdPMatrix)(MA), ht, len, iCol, X );}
inline overror_t cudaMCD_Dia_mulV( cdMatrix MA, ui len, cdVector X )
	{	return cudaMCDDia_mulV( (cdPMatrix)(MA), len, X );}

inline overror_t cudaMCD_Row_divC( cdMatrix MA, ui ht, ui len, ui iRow, dComplex C )
	{	return cudaMCDRow_divC( (cdPMatrix)(MA), ht, len, iRow, C );}
inline overror_t cudaMCD_Col_divC( cdMatrix MA, ui ht, ui len, ui iCol, dComplex C )
	{	return cudaMCDCol_divC( (cdPMatrix)(MA), ht, len, iCol, C );}
inline overror_t cudaMCD_Dia_divC( cdMatrix MA, ui len, dComplex C )
	{	return cudaMCDDia_divC( (cdPMatrix)(MA), len, C );}
inline overror_t cusdMCD_Row_divC( cdMatrix MA, ui ht, ui len, ui iRow, dComplex *d_C )
	{	return cusdMCDRow_divC( (cdPMatrix)(MA), ht, len, iRow, d_C );}
inline overror_t cusdMCD_Col_divC( cdMatrix MA, ui ht, ui len, ui iCol, dComplex *d_C )
	{	return cusdMCDCol_divC( (cdPMatrix)(MA), ht, len, iCol, d_C );}
inline overror_t cusdMCD_Dia_divC( cdMatrix MA, ui len, dComplex *d_C )
	{	return cusdMCDDia_divC( (cdPMatrix)(MA), len, d_C );}

inline overror_t cudaMCD_Row_divV( cdMatrix MA, ui ht, ui len, ui iRow, cdVector X )
	{	return cudaMCDRow_divV( (cdPMatrix)(MA), ht, len, iRow, X );}
inline overror_t cudaMCD_Col_divV( cdMatrix MA, ui ht, ui len, ui iCol, cdVector X )
	{	return cudaMCDCol_divV( (cdPMatrix)(MA), ht, len, iCol, X );}
inline overror_t cudaMCD_Dia_divV( cdMatrix MA, ui len, cdVector X )
	{	return cudaMCDDia_divV( (cdPMatrix)(MA), len, X );}

inline overror_t cudaMCD_Row_divrC( cdMatrix MA, ui ht, ui len, ui iRow, dComplex C )
	{	return cudaMCDRow_divrC( (cdPMatrix)(MA), ht, len, iRow, C );}
inline overror_t cudaMCD_Col_divrC( cdMatrix MA, ui ht, ui len, ui iCol, dComplex C )
	{	return cudaMCDCol_divrC( (cdPMatrix)(MA), ht, len, iCol, C );}
inline overror_t cudaMCD_Dia_divrC( cdMatrix MA, ui len, dComplex C )
	{	return cudaMCDDia_divrC( (cdPMatrix)(MA), len, C );}
inline overror_t cusdMCD_Row_divrC( cdMatrix MA, ui ht, ui len, ui iRow, dComplex *d_C )
	{	return cusdMCDRow_divrC( (cdPMatrix)(MA), ht, len, iRow, d_C );}
inline overror_t cusdMCD_Col_divrC( cdMatrix MA, ui ht, ui len, ui iCol, dComplex *d_C )
	{	return cusdMCDCol_divrC( (cdPMatrix)(MA), ht, len, iCol, d_C );}
inline overror_t cusdMCD_Dia_divrC( cdMatrix MA, ui len, dComplex *d_C )
	{	return cusdMCDDia_divrC( (cdPMatrix)(MA), len, d_C );}

inline overror_t cudaMCD_Row_divrV( cdMatrix MA, ui ht, ui len, ui iRow, cdVector X )
	{	return cudaMCDRow_divrV( (cdPMatrix)(MA), ht, len, iRow, X );}
inline overror_t cudaMCD_Col_divrV( cdMatrix MA, ui ht, ui len, ui iCol, cdVector X )
	{	return cudaMCDCol_divrV( (cdPMatrix)(MA), ht, len, iCol, X );}
inline overror_t cudaMCD_Dia_divrV( cdMatrix MA, ui len, cdVector X )
	{	return cudaMCDDia_divrV( (cdPMatrix)(MA), len, X );}

/******  One-dimensional vector operations **********************
         performed along all rows or all columns simultaneously,
         or along the diagonal of a square matrix                */

inline overror_t cudaMCD_Rows_absmax( dVector Y, cdMatrix MA, ui ht, ui len )
	{	return cudaMCDRows_absmax( Y, (cdPMatrix)(MA), ht, len );}
inline overror_t cudaMCD_Cols_absmax( dVector Y, cdMatrix MA, ui ht, ui len )
	{	return cudaMCDCols_absmax( Y, (cdPMatrix)(MA), ht, len );}
inline overror_t cudaMCD_Dia_absmax(  double *h_RetValPtr, cdMatrix MA, ui len )
	{	return cudaMCDDia_absmax(  h_RetValPtr, (cdPMatrix)(MA), len );}
inline overror_t cusdMCD_Dia_absmax(  double *d_RetValPtr, cdMatrix MA, ui len )
	{	return cusdMCDDia_absmax(  d_RetValPtr, (cdPMatrix)(MA), len );}
inline overror_t cudaMCD_Rows_absmin( dVector Y, cdMatrix MA, ui ht, ui len )
	{	return cudaMCDRows_absmin( Y, (cdPMatrix)(MA), ht, len );}
inline overror_t cudaMCD_Cols_absmin( dVector Y, cdMatrix MA, ui ht, ui len )
	{	return cudaMCDCols_absmin( Y, (cdPMatrix)(MA), ht, len );}
inline overror_t cudaMCD_Dia_absmin(  double *h_RetValPtr, cdMatrix MA, ui len )
	{	return cudaMCDDia_absmin(  h_RetValPtr, (cdPMatrix)(MA), len );}
inline overror_t cusdMCD_Dia_absmin(  double *d_RetValPtr, cdMatrix MA, ui len )
	{	return cusdMCDDia_absmin(  d_RetValPtr, (cdPMatrix)(MA), len );}

inline overror_t cudaMCD_Rows_maxReIm( cdVector Y, cdMatrix MA, ui ht, ui len )
	{	return cudaMCDRows_maxReIm( Y, (cdPMatrix)(MA), ht, len );}
inline overror_t cudaMCD_Cols_maxReIm( cdVector Y, cdMatrix MA, ui ht, ui len )
	{	return cudaMCDCols_maxReIm( Y, (cdPMatrix)(MA), ht, len );}
inline overror_t cudaMCD_Dia_maxReIm(  dComplex *h_RetValPtr, cdMatrix MA, ui len )
	{	return cudaMCDDia_maxReIm(  h_RetValPtr, (cdPMatrix)(MA), len );}
inline overror_t cusdMCD_Dia_maxReIm(  dComplex *d_RetValPtr, cdMatrix MA, ui len )
	{	return cusdMCDDia_maxReIm(  d_RetValPtr, (cdPMatrix)(MA), len );}
inline overror_t cudaMCD_Rows_minReIm( cdVector Y, cdMatrix MA, ui ht, ui len )
	{	return cudaMCDRows_minReIm( Y, (cdPMatrix)(MA), ht, len );}
inline overror_t cudaMCD_Cols_minReIm( cdVector Y, cdMatrix MA, ui ht, ui len )
	{	return cudaMCDCols_minReIm( Y, (cdPMatrix)(MA), ht, len );}
inline overror_t cudaMCD_Dia_minReIm(  dComplex *h_RetValPtr, cdMatrix MA, ui len )
	{	return cudaMCDDia_minReIm(  h_RetValPtr, (cdPMatrix)(MA), len );}
inline overror_t cusdMCD_Dia_minReIm(  dComplex *d_RetValPtr, cdMatrix MA, ui len )
	{	return cusdMCDDia_minReIm(  d_RetValPtr, (cdPMatrix)(MA), len );}

inline overror_t cudaMCD_Rows_absmaxReIm( cdVector Y, cdMatrix MA, ui ht, ui len )
	{	return cudaMCDRows_absmaxReIm( Y, (cdPMatrix)(MA), ht, len );}
inline overror_t cudaMCD_Cols_absmaxReIm( cdVector Y, cdMatrix MA, ui ht, ui len )
	{	return cudaMCDCols_absmaxReIm( Y, (cdPMatrix)(MA), ht, len );}
inline overror_t cudaMCD_Dia_absmaxReIm(  dComplex *h_RetValPtr, cdMatrix MA, ui len )
	{	return cudaMCDDia_absmaxReIm(  h_RetValPtr, (cdPMatrix)(MA), len );}
inline overror_t cusdMCD_Dia_absmaxReIm(  dComplex *d_RetValPtr, cdMatrix MA, ui len )
	{	return cusdMCDDia_absmaxReIm(  d_RetValPtr, (cdPMatrix)(MA), len );}
inline overror_t cudaMCD_Rows_absminReIm( cdVector Y, cdMatrix MA, ui ht, ui len )
	{	return cudaMCDRows_absminReIm( Y, (cdPMatrix)(MA), ht, len );}
inline overror_t cudaMCD_Cols_absminReIm( cdVector Y, cdMatrix MA, ui ht, ui len )
	{	return cudaMCDCols_absminReIm( Y, (cdPMatrix)(MA), ht, len );}
inline overror_t cudaMCD_Dia_absminReIm(  dComplex *h_RetValPtr, cdMatrix MA, ui len )
	{	return cudaMCDDia_absminReIm(  h_RetValPtr, (cdPMatrix)(MA), len );}
inline overror_t cusdMCD_Dia_absminReIm(  dComplex *d_RetValPtr, cdMatrix MA, ui len )
	{	return cusdMCDDia_absminReIm(  d_RetValPtr, (cdPMatrix)(MA), len );}

inline overror_t cudaMCD_Rows_cabsmax( cdVector Y, cdMatrix MA, ui ht, ui len )
	{	return cudaMCDRows_cabsmax( Y, (cdPMatrix)(MA), ht, len );}
inline overror_t cudaMCD_Cols_cabsmax( cdVector Y, cdMatrix MA, ui ht, ui len )
	{	return cudaMCDCols_cabsmax( Y, (cdPMatrix)(MA), ht, len );}
inline overror_t cudaMCD_Dia_cabsmax(  dComplex *h_RetValPtr, cdMatrix MA, ui len )
	{	return cudaMCDDia_cabsmax(  h_RetValPtr, (cdPMatrix)(MA), len );}
inline overror_t cusdMCD_Dia_cabsmax(  dComplex *d_RetValPtr, cdMatrix MA, ui len )
	{	return cusdMCDDia_cabsmax(  d_RetValPtr, (cdPMatrix)(MA), len );}
inline overror_t cudaMCD_Rows_cabsmin( cdVector Y, cdMatrix MA, ui ht, ui len )
	{	return cudaMCDRows_cabsmin( Y, (cdPMatrix)(MA), ht, len );}
inline overror_t cudaMCD_Cols_cabsmin( cdVector Y, cdMatrix MA, ui ht, ui len )
	{	return cudaMCDCols_cabsmin( Y, (cdPMatrix)(MA), ht, len );}
inline overror_t cudaMCD_Dia_cabsmin(  dComplex *h_RetValPtr, cdMatrix MA, ui len )
	{	return cudaMCDDia_cabsmin(  h_RetValPtr, (cdPMatrix)(MA), len );}
inline overror_t cusdMCD_Dia_cabsmin(  dComplex *d_RetValPtr, cdMatrix MA, ui len )
	{	return cusdMCDDia_cabsmin(  d_RetValPtr, (cdPMatrix)(MA), len );}

inline overror_t cudaMCD_Rows_sabsmax( cdVector Y, cdMatrix MA, ui ht, ui len )
	{	return cudaMCDRows_sabsmax( Y, (cdPMatrix)(MA), ht, len );}
inline overror_t cudaMCD_Cols_sabsmax( cdVector Y, cdMatrix MA, ui ht, ui len )
	{	return cudaMCDCols_sabsmax( Y, (cdPMatrix)(MA), ht, len );}
inline overror_t cudaMCD_Dia_sabsmax(  dComplex *h_RetValPtr, cdMatrix MA, ui len )
	{	return cudaMCDDia_sabsmax(  h_RetValPtr, (cdPMatrix)(MA), len );}
inline overror_t cusdMCD_Dia_sabsmax(  dComplex *d_RetValPtr, cdMatrix MA, ui len )
	{	return cusdMCDDia_sabsmax(  d_RetValPtr, (cdPMatrix)(MA), len );}
inline overror_t cudaMCD_Rows_sabsmin( cdVector Y, cdMatrix MA, ui ht, ui len )
	{	return cudaMCDRows_sabsmin( Y, (cdPMatrix)(MA), ht, len );}
inline overror_t cudaMCD_Cols_sabsmin( cdVector Y, cdMatrix MA, ui ht, ui len )
	{	return cudaMCDCols_sabsmin( Y, (cdPMatrix)(MA), ht, len );}
inline overror_t cudaMCD_Dia_sabsmin(  dComplex *h_RetValPtr, cdMatrix MA, ui len )
	{	return cudaMCDDia_sabsmin(  h_RetValPtr, (cdPMatrix)(MA), len );}
inline overror_t cusdMCD_Dia_sabsmin(  dComplex *d_RetValPtr, cdMatrix MA, ui len )
	{	return cusdMCDDia_sabsmin(  d_RetValPtr, (cdPMatrix)(MA), len );}

inline overror_t cudaMCD_Rows_sum( cdVector Y, cdMatrix MA, ui ht, ui len )
	{	return cudaMCDRows_sum( Y, (cdPMatrix)(MA), ht, len );}
inline overror_t cudaMCD_Cols_sum( cdVector Y, cdMatrix MA, ui ht, ui len )
	{	return cudaMCDCols_sum( Y, (cdPMatrix)(MA), ht, len );}
inline overror_t cudaMCD_Dia_sum(  dComplex *h_RetValPtr, cdMatrix MA, ui len )
	{	return cudaMCDDia_sum(  h_RetValPtr, (cdPMatrix)(MA), len );}
inline overror_t cusdMCD_Dia_sum(  dComplex *d_RetValPtr, cdMatrix MA, ui len )
	{	return cusdMCDDia_sum(  d_RetValPtr, (cdPMatrix)(MA), len );}
inline overror_t cudaMCD_Rows_prod( cdVector Y, cdMatrix MA, ui ht, ui len )
	{	return cudaMCDRows_prod( Y, (cdPMatrix)(MA), ht, len );}
inline overror_t cudaMCD_Cols_prod( cdVector Y, cdMatrix MA, ui ht, ui len )
	{	return cudaMCDCols_prod( Y, (cdPMatrix)(MA), ht, len );}
inline overror_t cudaMCD_Dia_prod(  dComplex *h_RetValPtr, cdMatrix MA, ui len )
	{	return cudaMCDDia_prod(  h_RetValPtr, (cdPMatrix)(MA), len );}
inline overror_t cusdMCD_Dia_prod(  dComplex *d_RetValPtr, cdMatrix MA, ui len )
	{	return cusdMCDDia_prod(  d_RetValPtr, (cdPMatrix)(MA), len );}

inline overror_t cudaMCD_Rows_runsum( cdMatrix MA, ui ht, ui len )
	{	return cudaMCDRows_runsum( (cdPMatrix)(MA), ht, len );}
inline overror_t cudaMCD_Cols_runsum( cdMatrix MA, ui ht, ui len )
	{	return cudaMCDCols_runsum( (cdPMatrix)(MA), ht, len );}
inline overror_t cudaMCD_Rows_runprod( cdMatrix MA, ui ht, ui len )
	{	return cudaMCDRows_runprod( (cdPMatrix)(MA), ht, len );}
inline overror_t cudaMCD_Cols_runprod( cdMatrix MA, ui ht, ui len )
	{	return cudaMCDCols_runprod( (cdPMatrix)(MA), ht, len );}

inline overror_t cudaMCD_Rows_rotate( cdMatrix MA, ui ht, ui len, ssize_t pos)
	{	return cudaMCDRows_rotate( (cdPMatrix)(MA), ht, len, pos );}
inline overror_t cudaMCD_Cols_rotate( cdMatrix MA, ui ht, ui len, ssize_t pos)
	{	return cudaMCDCols_rotate( (cdPMatrix)(MA), ht, len, pos );}
inline overror_t cudaMCD_Rows_rotate_buf( cdMatrix MA, ui ht, ui len, ssize_t pos, cdMatrix MBuf) 
	{	return cudaMCDRows_rotate_buf( (cdPMatrix)(MA), ht, len, pos, (cdPMatrix)(MBuf) );}
inline overror_t cudaMCD_Cols_rotate_buf( cdMatrix MA, ui ht, ui len, ssize_t pos, cdMatrix MBuf) 
	{	return cudaMCDCols_rotate_buf( (cdPMatrix)(MA), ht, len, pos, (cdPMatrix)(MBuf) );}
inline overror_t cudaMCD_Rows_reflect( cdMatrix MA, ui ht, ui len )
	{	return cudaMCDRows_reflect( (cdPMatrix)(MA), ht, len );}
inline overror_t cudaMCD_Cols_reflect( cdMatrix MA, ui ht, ui len )
	{	return cudaMCDCols_reflect( (cdPMatrix)(MA), ht, len );}
inline overror_t cudaMCD_Rows_rev( cdMatrix MA, ui ht, ui len )
	{	return cudaMCDRows_rev( (cdPMatrix)(MA), ht, len );}
inline overror_t cudaMCD_Cols_rev( cdMatrix MA, ui ht, ui len )
	{	return cudaMCDCols_rev( (cdPMatrix)(MA), ht, len );}


/********  Operations involving two rows or two colums of one matrix  *****/

inline overror_t cudaMCD_Rows_exchange( cdMatrix MA, ui ht, ui len, ui row1, ui row2 )
	{	return cudaMCDRows_exchange( (cdPMatrix)(MA), ht, len, row1, row2 );}
inline overror_t cudaMCD_Cols_exchange( cdMatrix MA, ui ht, ui len, ui col1, ui col2 )
	{	return cudaMCDCols_exchange( (cdPMatrix)(MA), ht, len, col1, col2 );}

inline overror_t cudaMCD_Rows_add( cdMatrix MA, ui ht, ui len, ui destRow, ui srceRow )
	{	return cudaMCDRows_add( (cdPMatrix)(MA), ht, len, destRow, srceRow );}
inline overror_t cudaMCD_Cols_add( cdMatrix MA, ui ht, ui len, ui destCol, ui srceCol )
	{	return cudaMCDCols_add( (cdPMatrix)(MA), ht, len, destCol, srceCol );}
                         /* dest[i] += source[i]  */

inline overror_t cudaMCD_Rows_sub( cdMatrix MA, ui ht, ui len, ui destRow, ui srceRow )
	{	return cudaMCDRows_sub( (cdPMatrix)(MA), ht, len, destRow, srceRow );}
inline overror_t cudaMCD_Cols_sub( cdMatrix MA, ui ht, ui len, ui destCol, ui srceCol )
	{	return cudaMCDCols_sub( (cdPMatrix)(MA), ht, len, destCol, srceCol );}
                         /* dest[i] -= source[i]  */

inline overror_t cudaMCD_Rows_Cadd( cdMatrix MA, ui ht, ui len, ui destRow, ui srceRow, dComplex C )
	{	return cudaMCDRows_Cadd( (cdPMatrix)(MA), ht, len, destRow, srceRow, C );}
inline overror_t cudaMCD_Cols_Cadd( cdMatrix MA, ui ht, ui len, ui destCol, ui srceCol, dComplex C )
	{	return cudaMCDCols_Cadd( (cdPMatrix)(MA), ht, len, destCol, srceCol, C );}
inline overror_t cusdMCD_Rows_Cadd( cdMatrix MA, ui ht, ui len, ui destRow, ui srceRow, dComplex *d_C )
	{	return cusdMCDRows_Cadd( (cdPMatrix)(MA), ht, len, destRow, srceRow, d_C );}
inline overror_t cusdMCD_Cols_Cadd( cdMatrix MA, ui ht, ui len, ui destCol, ui srceCol, dComplex *d_C )
	{	return cusdMCDCols_Cadd( (cdPMatrix)(MA), ht, len, destCol, srceCol, d_C );}
                         /* dest[i] += C * source[i]  */

inline overror_t cudaMCD_Rows_lincomb( cdMatrix MA, ui ht, ui len, ui destRow, dComplex destC, ui srceRow, dComplex srceC )
	{	return cudaMCDRows_lincomb( (cdPMatrix)(MA), ht, len, destRow, destC, srceRow, srceC );}
inline overror_t cudaMCD_Cols_lincomb( cdMatrix MA, ui ht, ui len, ui destCol, dComplex destC, ui srceCol, dComplex srceC )
	{	return cudaMCDCols_lincomb( (cdPMatrix)(MA), ht, len, destCol, destC, srceCol, srceC );}
inline overror_t cusdMCD_Rows_lincomb( cdMatrix MA, ui ht, ui len, ui destRow, dComplex *d_destC, ui srceRow, dComplex *d_srceC )
	{	return cusdMCDRows_lincomb( (cdPMatrix)(MA), ht, len, destRow, d_destC, srceRow, d_srceC );}
inline overror_t cusdMCD_Cols_lincomb( cdMatrix MA, ui ht, ui len, ui destCol, dComplex *d_destC, ui srceCol, dComplex *d_srceC )
	{	return cusdMCDCols_lincomb( (cdPMatrix)(MA), ht, len, destCol, d_destC, srceCol, d_srceC );}
  /*  linear combination: dest[i] = destC * dest[i] + sourceC * source[i] */


/*****************  Transposing and rotating a matrix **********************/

inline overror_t cudaMCD_transpose( cdMatrix MTr, cdMatrix MA, ui htTr, ui lenTr )
	{	return cudaMCDtranspose( (cdPMatrix)(MTr), (cdPMatrix)(MA), htTr, lenTr );}
       /*  dimensions htTr, lenTr are those of the transposed matrix, not of the original!   */
inline overror_t cudaMCD_hermconj( cdMatrix MTr, cdMatrix MA, ui htTr, ui lenTr )
	{	return cudaMCDhermconj( (cdPMatrix)(MTr), (cdPMatrix)(MA), htTr, lenTr );}
inline overror_t cudaMCD_rotate90( cdMatrix MRot, cdMatrix MA, ui htRot, ui lenRot )
	{	return cudaMCDrotate90( (cdPMatrix)(MRot), (cdPMatrix)(MA), htRot, lenRot );}
inline overror_t cudaMCD_rotate180( cdMatrix MRot, cdMatrix MA, ui htRot, ui lenRot )
	{	return cudaVCD_rev( (cdPMatrix)(MRot), (cdPMatrix)(MA), (htRot)*(lenRot) );}
inline overror_t cudaMCD_rotate270( cdMatrix MRot, cdMatrix MA, ui htRot, ui lenRot )
	{	return cudaMCDrotate270( (cdPMatrix)(MRot), (cdPMatrix)(MA), htRot, lenRot );}
inline overror_t cudaMCD_transpose_buf( cdMatrix MTr, cdMatrix MA, ui htTr, ui lenTr, cdMatrix MBuf )
	{	return cudaMCDtranspose_buf( (cdPMatrix)(MTr), (cdPMatrix)(MA), htTr, lenTr, (cdPMatrix)(MBuf) );}


/************************ Matrix Arithmetics *************************/

inline overror_t cudaMCD_addM( cdMatrix MC, cdMatrix MA, cdMatrix MB, ui htA, ui lenA )
	{	return cudaVCD_addV( (cdPMatrix)(MC), (cdPMatrix)(MA), (cdPMatrix)(MB), (htA)*(lenA) );}
inline overror_t cudaMCD_addMT( cdMatrix MC, cdMatrix MA, cdMatrix MB, ui htA, ui lenA )
	{	return cudaMCDaddMT( (cdPMatrix)(MC), (cdPMatrix)(MA), (cdPMatrix)(MB), htA, lenA );}
inline overror_t cudaMCD_subM( cdMatrix MC, cdMatrix MA, cdMatrix MB, ui htA, ui lenA )
	{	return cudaVCD_subV( (cdPMatrix)(MC), (cdPMatrix)(MA), (cdPMatrix)(MB), (htA)*(lenA) );}
inline overror_t cudaMCD_subMT( cdMatrix MC, cdMatrix MA, cdMatrix MB, ui htA, ui lenA )
	{	return cudaMCDsubMT( (cdPMatrix)(MC), (cdPMatrix)(MA), (cdPMatrix)(MB), htA, lenA );}
inline overror_t cudaMCD_subrM( cdMatrix MC, cdMatrix MA, cdMatrix MB, ui htA, ui lenA )
	{	return cudaVCD_subrV( (cdPMatrix)(MC), (cdPMatrix)(MA), (cdPMatrix)(MB), (htA)*(lenA) );}
inline overror_t cudaMCD_subrMT( cdMatrix MC, cdMatrix MA, cdMatrix MB, ui htA, ui lenA )
	{	return cudaMCDsubrMT( (cdPMatrix)(MC), (cdPMatrix)(MA), (cdPMatrix)(MB), htA, lenA );}
inline overror_t cudaMCD_mulC( cdMatrix MB, cdMatrix MA, ui htA, ui lenA, dComplex C )
	{	return cudaVCD_mulC( (cdPMatrix)(MB), (cdPMatrix)(MA), (htA)*(lenA), C );}
inline overror_t cudaMCD_divC( cdMatrix MB, cdMatrix MA, ui htA, ui lenA, dComplex C )
	{	return cudaVCD_divC( (cdPMatrix)(MB), (cdPMatrix)(MA), (htA)*(lenA), C );}
inline overror_t cudaMCD_mulReC( cdMatrix MB, cdMatrix MA, ui htA, ui lenA, double CRe )
	{	return cudaVCD_mulReC( (cdPMatrix)(MB), (cdPMatrix)(MA), (htA)*(lenA), CRe );}
inline overror_t cudaMCD_divReC( cdMatrix MB, cdMatrix MA, ui htA, ui lenA, double CRe )
	{	return cudaVCD_divReC( (cdPMatrix)(MB), (cdPMatrix)(MA), (htA)*(lenA), CRe );}
inline overror_t cusdMCD_mulC( cdMatrix MB, cdMatrix MA, ui htA, ui lenA, dComplex *d_C )
	{	return cusdVCD_mulC( (cdPMatrix)(MB), (cdPMatrix)(MA), (htA)*(lenA), d_C );}
inline overror_t cusdMCD_divC( cdMatrix MB, cdMatrix MA, ui htA, ui lenA, dComplex *d_C )
	{	return cusdVCD_divC( (cdPMatrix)(MB), (cdPMatrix)(MA), (htA)*(lenA), d_C );}
inline overror_t cusdMCD_mulReC( cdMatrix MB, cdMatrix MA, ui htA, ui lenA, double *d_CRe )
	{	return cusdVCD_mulReC( (cdPMatrix)(MB), (cdPMatrix)(MA), (htA)*(lenA), d_CRe );}
inline overror_t cusdMCD_divReC( cdMatrix MB, cdMatrix MA, ui htA, ui lenA, double *d_CRe )
	{	return cusdVCD_divReC( (cdPMatrix)(MB), (cdPMatrix)(MA), (htA)*(lenA), d_CRe );}

inline overror_t cudaMCD_lincomb( cdMatrix MC, cdMatrix MA, cdMatrix MB, ui htA, ui lenA, dComplex CA, dComplex CB )
	{	return cudaVCD_lincomb( (cdPMatrix)(MC), (cdPMatrix)(MA), (cdPMatrix)(MB), (htA)*(lenA), CA, CB );}
inline overror_t cusdMCD_lincomb( cdMatrix MC, cdMatrix MA, cdMatrix MB, ui htA, ui lenA, dComplex *d_CA, dComplex *d_CB )
	{	return cusdVCD_lincomb( (cdPMatrix)(MC), (cdPMatrix)(MA), (cdPMatrix)(MB), (htA)*(lenA), d_CA, d_CB );}

inline overror_t cudaMCD_mulV( cdVector Y, cdMatrix MA, cdVector X, ui htA, ui lenA )
	{	return cudaMCDmulV( Y, (cdPMatrix)(MA), X, htA, lenA );}
             /*  Y = MA * X.  sizX=lenA, sizY=htA;   both X and Y are column-vectors    */
inline overror_t cudaMCD_TmulV( cdVector Y, cdMatrix MA, cdVector X, ui htA, ui lenA )
	{	return cudaMCDTmulV( Y, (cdPMatrix)(MA), X, htA, lenA );}
            /*  Y = MAT * X.  sizX=htA, sizY=lenA;   both X and Y are column-vectors    */
inline overror_t cudaVCD_mulM( cdVector Y, cdVector X, cdMatrix MA, ui htA, ui lenA )
	{	return cudaVCDmulM( Y, X, (cdPMatrix)(MA), htA, lenA );}
            /*  Y = X * MA.  sizX=htA, sizY=lenA;    both X and Y are row-vectors.
                             Mind the prefix: cudaVCD_ (not cudaMCD_)    */
inline overror_t cudaVCD_mulMT( cdVector Y, cdVector X, cdMatrix MA, ui htA, ui lenA )
	{	return cudaVCDmulMT( Y, X, (cdPMatrix)(MA), htA, lenA );}
            /*  Y = X * MAT.  sizX=lenA, sizY=htA;   both X and Y are row-vectors.   */
inline overror_t cudaMCD_mulM( cdMatrix MC, cdMatrix MA, cdMatrix MB, ui htA, ui lenA, ui lenB )
	{	return cudaMCDmulM( (cdPMatrix)(MC), (cdPMatrix)(MA), (cdPMatrix)(MB), htA, lenA, lenB );}
                         /*  MC = MA * MB.  htB=lenA, htC=htA, lenC=lenB */
inline overror_t cudaMCD_mulMT( cdMatrix MC, cdMatrix MA, cdMatrix MB, ui htA, ui lenA, ui htB )
	{	return cudaMCDmulMT( (cdPMatrix)(MC), (cdPMatrix)(MA), (cdPMatrix)(MB), htA, lenA, htB );}
                         /*  MC = MA * MBT.  lenB=lenA, htC=htA, lenC=htB */
inline overror_t cudaMCD_mulMH( cdMatrix MC, cdMatrix MA, cdMatrix MB, ui htA, ui lenA, ui htB )
	{	return cudaMCDmulMH( (cdPMatrix)(MC), (cdPMatrix)(MA), (cdPMatrix)(MB), htA, lenA, htB );}
                         /*  MC = MA * MBH.  lenB=lenA, htC=htA, lenC=htB */
inline overror_t cudaMCD_TmulM( cdMatrix MC, cdMatrix MA, cdMatrix MB, ui htA, ui lenA, ui lenB )
	{	return cudaMCDTmulM( (cdPMatrix)(MC), (cdPMatrix)(MA), (cdPMatrix)(MB), htA, lenA, lenB );}
                         /*  MC = MAT * MB.  htB=htA, htC=lenA, lenC=lenB */
inline overror_t cudaMCD_HmulM( cdMatrix MC, cdMatrix MA, cdMatrix MB, ui htA, ui lenA, ui lenB )
	{	return cudaMCDHmulM( (cdPMatrix)(MC), (cdPMatrix)(MA), (cdPMatrix)(MB), htA, lenA, lenB );}
                         /*  MC = MAH * MB.  htB=htA, htC=lenA, lenC=lenB */
inline overror_t cudaMCD_TmulMT( cdMatrix MC, cdMatrix MA, cdMatrix MB, ui htA, ui lenA, ui htB )
	{	return cudaMCDTmulMT( (cdPMatrix)(MC), (cdPMatrix)(MA), (cdPMatrix)(MB), htA, lenA, htB );}
                         /*  MC = MAT * MBT.  lenB=htA, htC=lenA, lenC=htB */
inline overror_t cudaMCD_TmulMH( cdMatrix MC, cdMatrix MA, cdMatrix MB, ui htA, ui lenA, ui htB )
	{	return cudaMCDTmulMH( (cdPMatrix)(MC), (cdPMatrix)(MA), (cdPMatrix)(MB), htA, lenA, htB );}
                         /*  MC = MAT * MBH.  lenB=htA, htC=lenA, lenC=htB */
inline overror_t cudaMCDdia_mulM(  cdMatrix MC, cdVector MADia, cdMatrix MB, ui htB, ui lenB )
	{	return cudaMCDdiamulM(  (cdPMatrix)(MC), MADia, (cdPMatrix)(MB), htB, lenB );}
inline overror_t cudaMCDdia_mulMT(  cdMatrix MC, cdVector MADia, cdMatrix MB, ui htB, ui lenB )
	{	return cudaMCDdiamulMT(  (cdPMatrix)(MC), MADia, (cdPMatrix)(MB), htB, lenB );}
inline overror_t cudaMCD_mulMdia(  cdMatrix MC, cdMatrix MA, cdVector MBDia, ui htA, ui lenA )
	{	return cudaMCDmulMdia(  (cdPMatrix)(MC), (cdPMatrix)(MA), MBDia, htA, lenA );}
inline overror_t cudaMCD_TmulMdia(  cdMatrix MC, cdMatrix MA, cdVector MBDia, ui htA, ui lenA )
	{	return cudaMCDTmulMdia(  (cdPMatrix)(MC), (cdPMatrix)(MA), MBDia, htA, lenA );}


/***************** Two-Dimensional Fourier-Transform Methods ************/

inline overror_t cudaMCD_FFT( cdMatrix MY, cdMatrix MX, ui ht, ui len, int dir )
	{	return cudaMCDFFT( (cdPMatrix)(MY), (cdPMatrix)(MX), ht, len, dir );}
inline overror_t cudaMCD_Rows_FFT( cdMatrix MY, cdMatrix MX, ui ht, ui len, int dir )
	{	return cudaMCDRows_FFT( (cdPMatrix)(MY), (cdPMatrix)(MX), ht, len, dir );}
inline overror_t cudaMCD_Cols_FFT( cdMatrix MY, cdMatrix MX, ui ht, ui len, int dir )
	{	return cudaMCDCols_FFT( (cdPMatrix)(MY), (cdPMatrix)(MX), ht, len, dir );}
inline overror_t cudaMCD_filter( cdMatrix MY, cdMatrix MX, cdMatrix MCDlt, ui ht, ui len )
	{	return cudaMCDfilter( (cdPMatrix)(MY), (cdPMatrix)(MX), (cdPMatrix)(MCDlt), ht, len );}

/**************************  Input and Output  **************************
	The input/output functions involve memory transfers from device
	to host memory or vice versa. The generic cudaMCD_input/output functions
	allocate their own host buffers, whereas the cudaMCD_xxx_buf functions
	take a user-supplied buffer vector h_Wk (size must be >= ht*len )
	and are much more efficient.                                       */

inline overror_t cudaMCD_fprint( FILE *stream, cdMatrix MA, ui ht, ui len, unsigned linewidth )
	{	return cudaMCDfprint( stream, (cdPMatrix)(MA), ht, len, linewidth ); }
inline overror_t cudaMCD_print( cdMatrix MA, ui ht, ui len )
	{	return cudaMCDfprint( stdout, (cdPMatrix)(MA), ht, len, 80 ); }
inline overror_t cudaMCD_cprint( cdMatrix MA, ui ht, ui len )
	{	return cudaMCDcprint( (cdPMatrix)(MA), ht, len ); }
inline overror_t cudaMCD_fprint_buf( FILE *stream, cdMatrix d_MA, ui ht, ui len, unsigned linewidth, cdVector h_Wk )
	{	return cudaMCDfprint_buf( stream, (cdPMatrix)(d_MA), ht, len, linewidth, h_Wk ); }
inline overror_t cudaMCD_print_buf( cdMatrix d_MA, ui ht, ui len, cdVector h_Wk )
	{	return cudaMCDfprint_buf( stdout, (cdPMatrix)(d_MA), ht, len, 80, h_Wk ); }
inline overror_t cudaMCD_cprint_buf( cdMatrix d_MA, ui ht, ui len, cdVector h_Wk )
	{	return cudaMCDcprint_buf( (cdPMatrix)(d_MA), ht, len, h_Wk ); }
		/*  cudaMCD_print, cudaMCD_cprint usable only for console applications! */
inline overror_t  cudaMCD_write( FILE *stream, cdMatrix MA, ui ht, ui len )
	{	return cudaMCDwrite( stream, (cdPMatrix)(MA), ht, len ); }
inline overror_t cudaMCD_read( cdMatrix MA, ui ht, ui len, FILE *stream )
	{	return cudaMCDread( (cdPMatrix)(MA), ht, len, stream ); }
inline overror_t  cudaMCD_write_buf( FILE *stream, cdMatrix d_MA, ui ht, ui len, cdVector h_Wk )
	{	return cudaMCDwrite_buf( stream, (cdPMatrix)(d_MA), ht, len, h_Wk ); }
inline overror_t cudaMCD_read_buf( cdMatrix d_MA, ui ht, ui len, FILE *stream, cdVector h_Wk )
	{	return cudaMCDread_buf( (cdPMatrix)(d_MA), ht, len, stream, h_Wk ); }
                                   /* write and read in ascii format */
inline overror_t cudaMCD_store( FILE *stream, cdMatrix MA, ui ht, ui len )
{	return cudaVCD_store( stream, (cdPMatrix)(MA), (len)*(ht) ); }
inline overror_t cudaMCD_recall( cdMatrix MA, ui ht, ui len, FILE *stream )
	{	return cudaVCD_recall( (cdPMatrix)(MA), (len)*(ht), stream ); }
inline overror_t cudaMCD_store_buf( FILE *stream, cdMatrix d_MA, ui ht, ui len, cdVector h_Wk )
{	return cudaVCD_store_buf( stream, (cdPMatrix)(d_MA), (len)*(ht), h_Wk ); }
inline overror_t cudaMCD_recall_buf( cdMatrix d_MA, ui ht, ui len, FILE *stream, cdVector h_Wk )
	{	return cudaVCD_recall_buf( (cdPMatrix)(d_MA), (len)*(ht), stream, h_Wk ); }
                                  /* store and recall in binary format */

#else  /* plain-C, not C++: type-cast used to transform cdMatrix into cdPMatrix  */

/***  Addressing single elements of dynamically allocated matrices: ******/

#define cudaMCD_setElement( MA, ht, len, m, n, C ) cudaMCDsetElement( (cdPMatrix)(MA), ht, len, m, n, C )
#define cusdMCD_setElement( MA, ht, len, m, n, d_C ) cusdMCDsetElement( (cdPMatrix)(MA), ht, len, m, n, d_C )
#define cudaMCD_getElement( y, MA, ht, len, m, n ) cudaMCDgetElement( y, (cdPMatrix)(MA), ht, len, m, n )
#define cusdMCD_getElement( y, MA, ht, len, m, n ) cusdMCDgetElement( y, (cdPMatrix)(MA), ht, len, m, n )
#define cudaMCD_Pelement( MA, ht, len, m, n )      cudaMCDPelement( (cdPMatrix)(MA), ht, len, m, n )
#define cudaMCD_element( MA, ht, len, m, n )       cudaMCDelement( (cdPMatrix)(MA), ht, len, m, n )

 /****************  Initialization  ****************************************/

#define cudaMCD_equ0( MA, ht, len )            cudaVCD_equ0( (cdPMatrix)(MA), (ht)*(len) )
#define cudaMCD_equ1( MA, len )                cudaMCDequ1( (cdPMatrix)(MA), len )  /* identity matrix */
#define cudaMCD_equm1( MA, len )               cudaMCDequm1( (cdPMatrix)(MA), len )  /* neg. identity matrix */
#define cudaMCD_random( MA, ht, len, seed, Min, Max ) \
                                               cudaVCD_random( (cdPMatrix)(MA), (ht)*(len), seed, Min, Max ) 
#define cudaMCD_outerprod( MA, X, Y, ht, len ) cudaMCDouterprod( (cdPMatrix)(MA), X, Y, ht, len )
                       /* sizX=ht, sizY=len */
#define cudaMCD_Row_equ0( MA, ht, len, iRow ) cudaMCDRow_equ0( (cdPMatrix)(MA), ht, len, iRow )
#define cudaMCD_Col_equ0( MA, ht, len, iCol ) cudaMCDCol_equ0( (cdPMatrix)(MA), ht, len, iCol )
#define cudaMCD_Dia_equ0( MA, len )           cudaMCDDia_equ0( (cdPMatrix)(MA), len )
#define cudaMCD_Row_equC( MA, ht, len, iRow, C ) cudaMCDRow_equC( (cdPMatrix)(MA), ht, len, iRow, C )
#define cudaMCD_Col_equC( MA, ht, len, iCol, C ) cudaMCDCol_equC( (cdPMatrix)(MA), ht, len, iCol, C )
#define cudaMCD_Dia_equC( MA, len, C )           cudaMCDDia_equC( (cdPMatrix)(MA), len, C )
#define cusdMCD_Row_equC( MA, ht, len, iRow, d_CPtr ) cusdMCDRow_equC( (cdPMatrix)(MA), ht, len, iRow, d_CPtr )
#define cusdMCD_Col_equC( MA, ht, len, iCol, d_CPtr ) cusdMCDCol_equC( (cdPMatrix)(MA), ht, len, iCol, d_CPtr )
#define cusdMCD_Dia_equC( MA, len, CPtr )           cusdMCDDia_equC( (cdPMatrix)(MA), len, CPtr )

#define cudaMCD_Row_equV( MA, ht, len, iRow, X ) cudaMCDRow_equV( (cdPMatrix)(MA), ht, len, iRow, X )
#define cudaMCD_Col_equV( MA, ht, len, iCol, X ) cudaMCDCol_equV( (cdPMatrix)(MA), ht, len, iCol, X )
#define cudaMCD_Dia_equV( MA, len, X )           cudaMCDDia_equV( (cdPMatrix)(MA), len, X )

#define cudaMCD_Trd_equM( MA, MTrd, len )    cudaMCDTrd_equM( (cdPMatrix)(MA), (cdPMatrix)(MTrd), len )
#define cudaMCD_Trd_extract( MTrd, MA, len ) cudaMCDTrd_extract( (cdPMatrix)(MTrd), (cdPMatrix)(MA), len )

#define cudaMCD_equM( MB, MA, ht, len )      cudaVCD_equV( (cdPMatrix)(MB), (cdPMatrix)(MA), ((ui)(len))*(ht) )
#define cudaMCD_equMhost( MB, MA, ht, len )  cudaVCD_equVhost( (cdPMatrix)(MB), MA[0], (ht)*(len) )
#define MCD_equMdevice( MB, MA, ht, len )    VCD_equVdevice( MB[0], (cdPMatrix)(MA), (ht)*(len) )
#define cudaMCD_neg( MB, MA, ht, len )       cudaVCD_neg( (cdPMatrix)(MB), (cdPMatrix)(MA), ((ui)(len))*(ht) )
#define cudaMCD_conj( MB, MA, ht, len )      cudaVCD_conj( (cdPMatrix)(MB), (cdPMatrix)(MA), ((ui)(len))*(ht) )

#define cudaMCD_UequL( MA, len ) cudaMCDUequL( (cdPMatrix)(MA), len )
#define cudaMCD_LequU( MA, len ) cudaMCDLequU( (cdPMatrix)(MA), len )
         /* copy lower-diagonal elements into upper-diagonal
           (or vice versa) by index-reflection, so as to
           get a symmetric matrix    */

            /* data-type conversions:  */
#define cudaM_CDtoCF( MCF, MCD, ht, len ) cudaV_CDtoCF( (cfPMatrix)(MCF), (cdPMatrix)(MCD), (ht)*(len) )
#define cudaM_CFtoCD( MCD, MCF, ht, len ) cudaV_CFtoCD( (cdPMatrix)(MCD), (cfPMatrix)(MCF), (ht)*(len) )

#define cudaMD_CtoRe( MY, MCX, ht, len )           cudaVD_CtoRe( (dPMatrix)(MY),  (cdPMatrix)(MCX), (ht)*(len) )
#define cudaMD_CtoIm( MY, MCX, ht, len )           cudaVD_CtoIm( (dPMatrix)(MY),  (cdPMatrix)(MCX), (ht)*(len) )
#define cudaMD_CtoReIm( MYRe, MYIm, MCX, ht, len ) cudaVD_CtoReIm( (dPMatrix)(MYRe), (dPMatrix)(MYIm), (cdPMatrix)(MCX), (ht)*(len) )
#define cudaMD_RetoC( MCY, MX, ht, len )           cudaVD_RetoC( (cdPMatrix)(MCY), (dPMatrix)(MX),  (ht)*(len) )
#define cudaMD_ImtoC( MCY, MX, ht, len )           cudaVD_ImtoC( (cdPMatrix)(MCY), (dPMatrix)(MX),  (ht)*(len) )
#define cudaMD_ReImtoC( MCY, MXRe, MXIm, ht, len ) cudaVD_ReImtoC( (cdPMatrix)(MCY), (dPMatrix)(MXRe), (dPMatrix)(MXIm), (ht)*(len) )

/********  Extracting a submatrix and copying a submatrix back  *********/

#define cudaMCD_submatrix( MSub, subHt, subLen, \
                       MSrce, srceHt, srceLen, \
                       firstRowInCol, sampInCol, firstColInRow, sampInRow ) \
               cudaMCDsubmatrix(  (cdPMatrix)(MSub), subHt, subLen, \
                              (cdPMatrix)(MSrce), srceHt, srceLen, \
                              firstRowInCol, sampInCol, firstColInRow, sampInRow )

#define cudaMCD_submatrix_equM( MDest, destHt, destLen, \
                            firstRowInCol, sampInCol, firstColInRow, sampInRow, \
                            MSrce, srceHt, srceLen ) \
               cudaMCDsubmatrix_equM(  (cdPMatrix)(MDest), destHt, destLen, \
                             firstRowInCol, sampInCol, firstColInRow, sampInRow, \
                             (cdPMatrix)(MSrce), srceHt, srceLen )

#define cudaMCD_equMblock( MSub, subHt, subLen, \
                      MSrce, srceHt, srceLen, \
                      firstRowInCol, firstColInRow ) \
              cudaMCDequMblock(  (cdPMatrix)(MSub), subHt, subLen, \
                             (cdPMatrix)(MSrce), srceHt, srceLen, \
                             firstRowInCol, firstColInRow )

#define cudaMCD_block_equM( MDest, destHt, destLen, \
                       firstRowInCol, firstColInRow, \
                       MSrce, srceHt, srceLen ) \
              cudaMCDblock_equM( (cdPMatrix)(MDest), destHt, destLen, \
                             firstRowInCol, firstColInRow, \
                             (cdPMatrix)(MSrce), srceHt, srceLen )

#define cudaMCD_equMblockT( MSub, subHt, subLen, \
                      MSrce, srceHt, srceLen, \
                      firstRowInCol, firstColInRow ) \
              cudaMCDequMblockT( (cdPMatrix)(MSub), subHt, subLen, \
                             (cdPMatrix)(MSrce), srceHt, srceLen, \
                             firstRowInCol, firstColInRow )

#define cudaMCD_block_equMT( MDest, destHt, destLen, \
                       firstRowInCol, firstColInRow, \
                       MSrce, srceHt, srceLen ) \
              cudaMCDblock_equMT( (cdPMatrix)(MDest), destHt, destLen, \
                             firstRowInCol, firstColInRow, \
                             (cdPMatrix)(MSrce), srceHt, srceLen )

/*****   Extracting a single row or a single column or the diagonal  ******
 *       and storing it into a vector                                     */

#define cudaMCD_Row_extract( Y, MA, ht, len, iRow ) cudaMCDRow_extract( Y, (cdPMatrix)(MA), ht, len, iRow )
#define cudaMCD_Col_extract( Y, MA, ht, len, iCol ) cudaMCDCol_extract( Y, (cdPMatrix)(MA), ht, len, iCol )
#define cudaMCD_Dia_extract( Y, MA, len )           cudaMCDDia_extract( Y, (cdPMatrix)(MA), len )


/**************  Deleting or inserting a row or a column   ***************/

#define cudaMCD_Row_delete( MB, MA, htA, lenA, iRow )    cudaMCDRow_delete( (cdPMatrix)(MB), (cdPMatrix)(MA), htA, lenA, iRow )
#define cudaMCD_Col_delete( MB, MA, htA, lenA, iCol )    cudaMCDCol_delete( (cdPMatrix)(MB), (cdPMatrix)(MA), htA, lenA, iCol )
#define cudaMCD_Row_insert( MB, MA, htB, lenB, iRow, X ) cudaMCDRow_insert( (cdPMatrix)(MB), (cdPMatrix)(MA), htB, lenB, iRow, X )
#define cudaMCD_Col_insert( MB, MA, htB, lenB, iCol, X ) cudaMCDCol_insert( (cdPMatrix)(MB), (cdPMatrix)(MA), htB, lenB, iCol, X )


/*****************    Basic arithmetic operations *********************
                      performed on one single row,
                      or one single column of any matrix,
                      or on the diagonal of a square matrix

    Note: In contrast to the analogous VectorLib functions, the operations
    are performed in-place, i.e. the input matrix itself is changed  */

#define cudaMCD_Row_neg( MA, ht, len, iRow ) cudaMCDRow_neg( (cdPMatrix)(MA), ht, len, iRow )
#define cudaMCD_Col_neg( MA, ht, len, iCol ) cudaMCDCol_neg( (cdPMatrix)(MA), ht, len, iCol )

#define cudaMCD_Row_conj( MA, ht, len, iRow ) cudaMCDRow_conj( (cdPMatrix)(MA), ht, len, iRow )
#define cudaMCD_Col_conj( MA, ht, len, iCol ) cudaMCDCol_conj( (cdPMatrix)(MA), ht, len, iCol )

#define cudaMCD_Row_addC( MA, ht, len, iRow, C ) cudaMCDRow_addC( (cdPMatrix)(MA), ht, len, iRow, C )
#define cudaMCD_Col_addC( MA, ht, len, iCol, C ) cudaMCDCol_addC( (cdPMatrix)(MA), ht, len, iCol, C )
#define cudaMCD_Dia_addC( MA, len, C )           cudaMCDDia_addC( (cdPMatrix)(MA), len, C )

#define cudaMCD_Row_addV( MA, ht, len, iRow, X ) cudaMCDRow_addV( (cdPMatrix)(MA), ht, len, iRow, X )
#define cudaMCD_Col_addV( MA, ht, len, iCol, X ) cudaMCDCol_addV( (cdPMatrix)(MA), ht, len, iCol, X )
#define cudaMCD_Dia_addV( MA, len, X )           cudaMCDDia_addV( (cdPMatrix)(MA), len, X )

#define cudaMCD_Row_subC( MA, ht, len, iRow, C ) cudaMCDRow_subC( (cdPMatrix)(MA), ht, len, iRow, C )
#define cudaMCD_Col_subC( MA, ht, len, iCol, C ) cudaMCDCol_subC( (cdPMatrix)(MA), ht, len, iCol, C )
#define cudaMCD_Dia_subC( MA, len, C )           cudaMCDDia_subC( (cdPMatrix)(MA), len, C )

#define cudaMCD_Row_subV( MA, ht, len, iRow, X ) cudaMCDRow_subV( (cdPMatrix)(MA), ht, len, iRow, X )
#define cudaMCD_Col_subV( MA, ht, len, iCol, X ) cudaMCDCol_subV( (cdPMatrix)(MA), ht, len, iCol, X )
#define cudaMCD_Dia_subV( MA, len, X )           cudaMCDDia_subV( (cdPMatrix)(MA), len, X )

#define cudaMCD_Row_subrC( MA, ht, len, iRow, C ) cudaMCDRow_subrC( (cdPMatrix)(MA), ht, len, iRow, C )
#define cudaMCD_Col_subrC( MA, ht, len, iCol, C ) cudaMCDCol_subrC( (cdPMatrix)(MA), ht, len, iCol, C )
#define cudaMCD_Dia_subrC( MA, len, C )           cudaMCDDia_subrC( (cdPMatrix)(MA), len, C )

#define cudaMCD_Row_subrV( MA, ht, len, iRow, X ) cudaMCDRow_subrV( (cdPMatrix)(MA), ht, len, iRow, X )
#define cudaMCD_Col_subrV( MA, ht, len, iCol, X ) cudaMCDCol_subrV( (cdPMatrix)(MA), ht, len, iCol, X )
#define cudaMCD_Dia_subrV( MA, len, X )           cudaMCDDia_subrV( (cdPMatrix)(MA), len, X )

#define cudaMCD_Row_mulC( MA, ht, len, iRow, C ) cudaMCDRow_mulC( (cdPMatrix)(MA), ht, len, iRow, C )
#define cudaMCD_Col_mulC( MA, ht, len, iCol, C ) cudaMCDCol_mulC( (cdPMatrix)(MA), ht, len, iCol, C )
#define cudaMCD_Dia_mulC( MA, len, C )           cudaMCDDia_mulC( (cdPMatrix)(MA), len, C )

#define cudaMCD_Row_mulV( MA, ht, len, iRow, X ) cudaMCDRow_mulV( (cdPMatrix)(MA), ht, len, iRow, X )
#define cudaMCD_Col_mulV( MA, ht, len, iCol, X ) cudaMCDCol_mulV( (cdPMatrix)(MA), ht, len, iCol, X )
#define cudaMCD_Dia_mulV( MA, len, X )           cudaMCDDia_mulV( (cdPMatrix)(MA), len, X )

#define cudaMCD_Row_divC( MA, ht, len, iRow, C ) cudaMCDRow_divC( (cdPMatrix)(MA), ht, len, iRow, C )
#define cudaMCD_Col_divC( MA, ht, len, iCol, C ) cudaMCDCol_divC( (cdPMatrix)(MA), ht, len, iCol, C )
#define cudaMCD_Dia_divC( MA, len, C )           cudaMCDDia_divC( (cdPMatrix)(MA), len, C )

#define cudaMCD_Row_divV( MA, ht, len, iRow, X ) cudaMCDRow_divV( (cdPMatrix)(MA), ht, len, iRow, X )
#define cudaMCD_Col_divV( MA, ht, len, iCol, X ) cudaMCDCol_divV( (cdPMatrix)(MA), ht, len, iCol, X )
#define cudaMCD_Dia_divV( MA, len, X )           cudaMCDDia_divV( (cdPMatrix)(MA), len, X )

#define cudaMCD_Row_divrC( MA, ht, len, iRow, C ) cudaMCDRow_divrC( (cdPMatrix)(MA), ht, len, iRow, C )
#define cudaMCD_Col_divrC( MA, ht, len, iCol, C ) cudaMCDCol_divrC( (cdPMatrix)(MA), ht, len, iCol, C )
#define cudaMCD_Dia_divrC( MA, len, C )           cudaMCDDia_divrC( (cdPMatrix)(MA), len, C )

#define cudaMCD_Row_divrV( MA, ht, len, iRow, X ) cudaMCDRow_divrV( (cdPMatrix)(MA), ht, len, iRow, X )
#define cudaMCD_Col_divrV( MA, ht, len, iCol, X ) cudaMCDCol_divrV( (cdPMatrix)(MA), ht, len, iCol, X )
#define cudaMCD_Dia_divrV( MA, len, X )           cudaMCDDia_divrV( (cdPMatrix)(MA), len, X )

#define cusdMCD_Row_addC( MA, ht, len, iRow, d_CPtr ) cusdMCDRow_addC( (cdPMatrix)(MA), ht, len, iRow, d_CPtr )
#define cusdMCD_Col_addC( MA, ht, len, iCol, d_CPtr ) cusdMCDCol_addC( (cdPMatrix)(MA), ht, len, iCol, d_CPtr )
#define cusdMCD_Dia_addC( MA, len, d_CPtr )           cusdMCDDia_addC( (cdPMatrix)(MA), len, d_CPtr )
#define cusdMCD_Row_subC( MA, ht, len, iRow, d_CPtr ) cusdMCDRow_subC( (cdPMatrix)(MA), ht, len, iRow, d_CPtr )
#define cusdMCD_Col_subC( MA, ht, len, iCol, d_CPtr ) cusdMCDCol_subC( (cdPMatrix)(MA), ht, len, iCol, d_CPtr )
#define cusdMCD_Dia_subC( MA, len, d_CPtr )           cusdMCDDia_subC( (cdPMatrix)(MA), len, d_CPtr )
#define cusdMCD_Row_subrC( MA, ht, len, iRow, d_CPtr ) cusdMCDRow_subrC( (cdPMatrix)(MA), ht, len, iRow, d_CPtr )
#define cusdMCD_Col_subrC( MA, ht, len, iCol, d_CPtr ) cusdMCDCol_subrC( (cdPMatrix)(MA), ht, len, iCol, d_CPtr )
#define cusdMCD_Dia_subrC( MA, len, d_CPtr )           cusdMCDDia_subrC( (cdPMatrix)(MA), len, d_CPtr )
#define cusdMCD_Row_mulC( MA, ht, len, iRow, d_CPtr ) cusdMCDRow_mulC( (cdPMatrix)(MA), ht, len, iRow, d_CPtr )
#define cusdMCD_Col_mulC( MA, ht, len, iCol, d_CPtr ) cusdMCDCol_mulC( (cdPMatrix)(MA), ht, len, iCol, d_CPtr )
#define cusdMCD_Dia_mulC( MA, len, d_CPtr )           cusdMCDDia_mulC( (cdPMatrix)(MA), len, d_CPtr )
#define cusdMCD_Row_divC( MA, ht, len, iRow, d_CPtr ) cusdMCDRow_divC( (cdPMatrix)(MA), ht, len, iRow, d_CPtr )
#define cusdMCD_Col_divC( MA, ht, len, iCol, d_CPtr ) cusdMCDCol_divC( (cdPMatrix)(MA), ht, len, iCol, d_CPtr )
#define cusdMCD_Dia_divC( MA, len, d_CPtr )           cusdMCDDia_divC( (cdPMatrix)(MA), len, d_CPtr )
#define cusdMCD_Row_divrC( MA, ht, len, iRow, d_CPtr ) cusdMCDRow_divrC( (cdPMatrix)(MA), ht, len, iRow, d_CPtr )
#define cusdMCD_Col_divrC( MA, ht, len, iCol, d_CPtr ) cusdMCDCol_divrC( (cdPMatrix)(MA), ht, len, iCol, d_CPtr )
#define cusdMCD_Dia_divrC( MA, len, d_CPtr )           cusdMCDDia_divrC( (cdPMatrix)(MA), len, d_CPtr )

/******  One-dimensional vector operations **********************
         performed along all rows or all columns simultaneously,
         or along the diagonal of a square matrix                */

#define cudaMCD_Rows_absmax( Y, MA, ht, len )   cudaMCDRows_absmax( Y, (cdPMatrix)(MA), ht, len )
#define cudaMCD_Cols_absmax( Y, MA, ht, len )   cudaMCDCols_absmax( Y, (cdPMatrix)(MA), ht, len )
#define cudaMCD_Dia_absmax( h_RetPtr, MA, len ) cudaMCDDia_absmax( h_RetPtr, (cdPMatrix)(MA), len )
#define cudaMCD_Rows_absmin( Y, MA, ht, len )   cudaMCDRows_absmin( Y, (cdPMatrix)(MA), ht, len )
#define cudaMCD_Cols_absmin( Y, MA, ht, len )   cudaMCDCols_absmin( Y, (cdPMatrix)(MA), ht, len )
#define cudaMCD_Dia_absmin( h_RetPtr, MA, len ) cudaMCDDia_absmin( h_RetPtr, (cdPMatrix)(MA), len )

#define cudaMCD_Rows_maxReIm( Y, MA, ht, len )   cudaMCDRows_maxReIm( Y, (cdPMatrix)(MA), ht, len )
#define cudaMCD_Cols_maxReIm( Y, MA, ht, len )   cudaMCDCols_maxReIm( Y, (cdPMatrix)(MA), ht, len )
#define cudaMCD_Dia_maxReIm( h_RetPtr, MA, len ) cudaMCDDia_maxReIm( h_RetPtr, (cdPMatrix)(MA), len )
#define cudaMCD_Rows_minReIm( Y, MA, ht, len )   cudaMCDRows_minReIm( Y, (cdPMatrix)(MA), ht, len )
#define cudaMCD_Cols_minReIm( Y, MA, ht, len )   cudaMCDCols_minReIm( Y, (cdPMatrix)(MA), ht, len )
#define cudaMCD_Dia_minReIm( h_RetPtr, MA, len ) cudaMCDDia_minReIm( h_RetPtr, (cdPMatrix)(MA), len )

#define cudaMCD_Rows_absmaxReIm( Y, MA, ht, len )   cudaMCDRows_absmaxReIm( Y, (cdPMatrix)(MA), ht, len )
#define cudaMCD_Cols_absmaxReIm( Y, MA, ht, len )   cudaMCDCols_absmaxReIm( Y, (cdPMatrix)(MA), ht, len )
#define cudaMCD_Dia_absmaxReIm( h_RetPtr, MA, len ) cudaMCDDia_absmaxReIm( h_RetPtr, (cdPMatrix)(MA), len )
#define cudaMCD_Rows_absminReIm( Y, MA, ht, len )   cudaMCDRows_absminReIm( Y, (cdPMatrix)(MA), ht, len )
#define cudaMCD_Cols_absminReIm( Y, MA, ht, len )   cudaMCDCols_absminReIm( Y, (cdPMatrix)(MA), ht, len )
#define cudaMCD_Dia_absminReIm( h_RetPtr, MA, len ) cudaMCDDia_absminReIm( h_RetPtr, (cdPMatrix)(MA), len )

#define cudaMCD_Rows_cabsmax( Y, MA, ht, len )   cudaMCDRows_cabsmax( Y, (cdPMatrix)(MA), ht, len )
#define cudaMCD_Cols_cabsmax( Y, MA, ht, len )   cudaMCDCols_cabsmax( Y, (cdPMatrix)(MA), ht, len )
#define cudaMCD_Dia_cabsmax( h_RetPtr, MA, len ) cudaMCDDia_cabsmax( h_RetPtr, (cdPMatrix)(MA), len )
#define cudaMCD_Rows_cabsmin( Y, MA, ht, len )   cudaMCDRows_cabsmin( Y, (cdPMatrix)(MA), ht, len )
#define cudaMCD_Cols_cabsmin( Y, MA, ht, len )   cudaMCDCols_cabsmin( Y, (cdPMatrix)(MA), ht, len )
#define cudaMCD_Dia_cabsmin( h_RetPtr, MA, len ) cudaMCDDia_cabsmin( h_RetPtr, (cdPMatrix)(MA), len )

#define cudaMCD_Rows_sabsmax( Y, MA, ht, len )   cudaMCDRows_sabsmax( Y, (cdPMatrix)(MA), ht, len )
#define cudaMCD_Cols_sabsmax( Y, MA, ht, len )   cudaMCDCols_sabsmax( Y, (cdPMatrix)(MA), ht, len )
#define cudaMCD_Dia_sabsmax( h_RetPtr, MA, len ) cudaMCDDia_sabsmax( h_RetPtr, (cdPMatrix)(MA), len )
#define cudaMCD_Rows_sabsmin( Y, MA, ht, len )   cudaMCDRows_sabsmin( Y, (cdPMatrix)(MA), ht, len )
#define cudaMCD_Cols_sabsmin( Y, MA, ht, len )   cudaMCDCols_sabsmin( Y, (cdPMatrix)(MA), ht, len )
#define cudaMCD_Dia_sabsmin( h_RetPtr, MA, len ) cudaMCDDia_sabsmin( h_RetPtr, (cdPMatrix)(MA), len )

#define cudaMCD_Rows_sum( Y, MA, ht, len )     cudaMCDRows_sum( Y, (cdPMatrix)(MA), ht, len )
#define cudaMCD_Cols_sum( Y, MA, ht, len )     cudaMCDCols_sum( Y, (cdPMatrix)(MA), ht, len )
#define cudaMCD_Dia_sum(  h_RetPtr, MA, len )  cudaMCDDia_sum( h_RetPtr, (cdPMatrix)(MA), len )
#define cudaMCD_Rows_prod( Y, MA, ht, len )    cudaMCDRows_prod( Y, (cdPMatrix)(MA), ht, len )
#define cudaMCD_Cols_prod( Y, MA, ht, len )    cudaMCDCols_prod( Y, (cdPMatrix)(MA), ht, len )
#define cudaMCD_Dia_prod(  h_RetPtr, MA, len ) cudaMCDDia_prod( h_RetPtr, (cdPMatrix)(MA), len )

#define cusdMCD_Dia_absmax( d_RetPtr, MA, len ) cusdMCDDia_absmax( d_RetPtr, (cdPMatrix)(MA), len )
#define cusdMCD_Dia_absmin( d_RetPtr, MA, len ) cusdMCDDia_absmin( d_RetPtr, (cdPMatrix)(MA), len )
#define cusdMCD_Dia_maxReIm( d_RetPtr, MA, len ) cusdMCDDia_maxReIm( d_RetPtr, (cdPMatrix)(MA), len )
#define cusdMCD_Dia_minReIm( d_RetPtr, MA, len ) cusdMCDDia_minReIm( d_RetPtr, (cdPMatrix)(MA), len )
#define cusdMCD_Dia_absmaxReIm( d_RetPtr, MA, len ) cusdMCDDia_absmaxReIm( d_RetPtr, (cdPMatrix)(MA), len )
#define cusdMCD_Dia_absminReIm( d_RetPtr, MA, len ) cusdMCDDia_absminReIm( d_RetPtr, (cdPMatrix)(MA), len )
#define cusdMCD_Dia_cabsmax( d_RetPtr, MA, len ) cusdMCDDia_cabsmax( d_RetPtr, (cdPMatrix)(MA), len )
#define cusdMCD_Dia_cabsmin( d_RetPtr, MA, len ) cusdMCDDia_cabsmin( d_RetPtr, (cdPMatrix)(MA), len )
#define cusdMCD_Dia_sabsmax( d_RetPtr, MA, len ) cusdMCDDia_sabsmax( d_RetPtr, (cdPMatrix)(MA), len )
#define cusdMCD_Dia_sabsmin( d_RetPtr, MA, len ) cusdMCDDia_sabsmin( d_RetPtr, (cdPMatrix)(MA), len )
#define cusdMCD_Dia_sum(  d_RetPtr, MA, len )  cusdMCDDia_sum( d_RetPtr, (cdPMatrix)(MA), len )
#define cusdMCD_Dia_prod(  d_RetPtr, MA, len ) cusdMCDDia_prod( d_RetPtr, (cdPMatrix)(MA), len )

#define cudaMCD_Rows_runsum( MA, ht, len )     cudaMCDRows_runsum( (cdPMatrix)(MA), ht, len )
#define cudaMCD_Cols_runsum( MA, ht, len )     cudaMCDCols_runsum( (cdPMatrix)(MA), ht, len )
#define cudaMCD_Rows_runprod( MA, ht, len )    cudaMCDRows_runprod( (cdPMatrix)(MA), ht, len )
#define cudaMCD_Cols_runprod( MA, ht, len )    cudaMCDCols_runprod( (cdPMatrix)(MA), ht, len )

#define cudaMCD_Rows_rotate( MA, ht, len, pos) cudaMCDRows_rotate( (cdPMatrix)(MA), ht, len, pos )
#define cudaMCD_Cols_rotate( MA, ht, len, pos) cudaMCDCols_rotate( (cdPMatrix)(MA), ht, len, pos )
#define cudaMCD_Rows_rotate_buf( MA, ht, len, pos, MBuf) cudaMCDRows_rotate_buf( (cdPMatrix)(MA), ht, len, pos, (cdPMatrix)(MBuf) )
#define cudaMCD_Cols_rotate_buf( MA, ht, len, pos, MBuf) cudaMCDCols_rotate_buf( (cdPMatrix)(MA), ht, len, pos, (cdPMatrix)(MBuf) )
#define cudaMCD_Rows_reflect( MA, ht, len)     cudaMCDRows_reflect( (cdPMatrix)(MA), ht, len )
#define cudaMCD_Cols_reflect( MA, ht, len)     cudaMCDCols_reflect( (cdPMatrix)(MA), ht, len )
#define cudaMCD_Rows_rev( MA, ht, len)         cudaMCDRows_rev( (cdPMatrix)(MA), ht, len )
#define cudaMCD_Cols_rev( MA, ht, len)         cudaMCDCols_rev( (cdPMatrix)(MA), ht, len )


/********  Operations involving two rows or two colums of one matrix  *****/

#define cudaMCD_Rows_exchange( MA, ht, len, row1, row2 )  cudaMCDRows_exchange( (cdPMatrix)(MA), ht, len, row1, row2 )
#define cudaMCD_Cols_exchange( MA, ht, len, col1, col2 )  cudaMCDCols_exchange( (cdPMatrix)(MA), ht, len, col1, col2 )

#define cudaMCD_Rows_add( MA, ht, len, destRow, srceRow ) cudaMCDRows_add( (cdPMatrix)(MA), ht, len, destRow, srceRow )
#define cudaMCD_Cols_add( MA, ht, len, destCol, srceCol ) cudaMCDCols_add( (cdPMatrix)(MA), ht, len, destCol, srceCol )
                         /* dest[i] += source[i]  */

#define cudaMCD_Rows_sub( MA, ht, len, destRow, srceRow ) cudaMCDRows_sub( (cdPMatrix)(MA), ht, len, destRow, srceRow )
#define cudaMCD_Cols_sub( MA, ht, len, destCol, srceCol ) cudaMCDCols_sub( (cdPMatrix)(MA), ht, len, destCol, srceCol )
                         /* dest[i] -= source[i]  */

#define cudaMCD_Rows_Cadd( MA, ht, len, destRow, srceRow, C ) cudaMCDRows_Cadd( (cdPMatrix)(MA), ht, len, destRow, srceRow, C )
#define cudaMCD_Cols_Cadd( MA, ht, len, destCol, srceCol, C ) cudaMCDCols_Cadd( (cdPMatrix)(MA), ht, len, destCol, srceCol, C )
#define cusdMCD_Rows_Cadd( MA, ht, len, destRow, srceRow, d_CPtr ) cusdMCDRows_Cadd( (cdPMatrix)(MA), ht, len, destRow, srceRow, d_CPtr )
#define cusdMCD_Cols_Cadd( MA, ht, len, destCol, srceCol, d_CPtr ) cusdMCDCols_Cadd( (cdPMatrix)(MA), ht, len, destCol, srceCol, d_CPtr )
                         /* dest[i] += C * source[i]  */

#define cudaMCD_Rows_lincomb( MA, ht, len, destRow, destC, srceRow, srceC ) \
            cudaMCDRows_lincomb( (cdPMatrix)(MA), ht, len, destRow, destC, srceRow, srceC )
#define cudaMCD_Cols_lincomb( MA, ht, len, destCol, destC, srceCol, srceC ) \
            cudaMCDCols_lincomb( (cdPMatrix)(MA), ht, len, destCol, destC, srceCol, srceC )
#define cusdMCD_Rows_lincomb( MA, ht, len, destRow, d_DestCPtr, srceRow, d_SrceCPtr ) \
            cusdMCDRows_lincomb( (cdPMatrix)(MA), ht, len, destRow, d_DestCPtr, srceRow, d_SrceCPtr )
#define cusdMCD_Cols_lincomb( MA, ht, len, d_DestCPtrol, d_DestCPtr, d_SrceCPtrol, d_SrceCPtr ) \
            cusdMCDCols_lincomb( (cdPMatrix)(MA), ht, len, d_DestCPtrol, d_DestCPtr, d_SrceCPtrol, d_SrceCPtr )
  /*  linear combination: dest[i] = destC * dest[i] + sourceC * source[i] */


/*****************  Transposing and rotating a matrix **********************/

#define cudaMCD_transpose( MTr, MA, htTr, lenTr )    cudaMCDtranspose( (cdPMatrix)(MTr), (cdPMatrix)(MA), htTr, lenTr )
       /*  the dimensions htTr, lenTr are those of the transposed matrix,
           not of the original!                */
#define cudaMCD_hermconj( MHConj, MA, htTr, lenTr )  cudaMCDhermconj( (cdPMatrix)(MHConj), (cdPMatrix)(MA), htTr, lenTr )
#define cudaMCD_rotate90( MRot, MA, htRot, lenRot )  cudaMCDrotate90( (cdPMatrix)(MRot), (cdPMatrix)(MA), htRot, lenRot )
#define cudaMCD_rotate180( MRot, MA, htRot, lenRot ) cudaVCD_rev( (cdPMatrix)(MRot), (cdPMatrix)(MA), (htRot)*(lenRot) )
#define cudaMCD_rotate270( MRot, MA, htRot, lenRot ) cudaMCDrotate270( (cdPMatrix)(MRot), (cdPMatrix)(MA), htRot, lenRot )
#define cudaMCD_transpose_buf( MTr, MA, htTr, lenTr, MBuf )    cudaMCDtranspose_buf( (cdPMatrix)(MTr), (cdPMatrix)(MA), htTr, lenTr, (cdPMatrix)(MBuf) )


/************************ Matrix Arithmetics *************************/

#define cudaMCD_addM( MC, MA, MB, htA, lenA )    cudaVCD_addV( (cdPMatrix)(MC), (cdPMatrix)(MA), (cdPMatrix)(MB), (htA)*(lenA) )
#define cudaMCD_addMT( MC, MA, MB, htA, lenA )   cudaMCDaddMT( (cdPMatrix)(MC), (cdPMatrix)(MA), (cdPMatrix)(MB), htA, lenA )
#define cudaMCD_subM( MC, MA, MB, htA, lenA )    cudaVCD_subV( (cdPMatrix)(MC), (cdPMatrix)(MA), (cdPMatrix)(MB), (htA)*(lenA) )
#define cudaMCD_subMT( MC, MA, MB, htA, lenA )   cudaMCDsubMT( (cdPMatrix)(MC), (cdPMatrix)(MA), (cdPMatrix)(MB), htA, lenA )
#define cudaMCD_subrMT( MC, MA, MB, htA, lenA )  cudaMCDsubrMT( (cdPMatrix)(MC), (cdPMatrix)(MA), (cdPMatrix)(MB), htA, lenA )
#define cudaMCD_mulC( MB, MA, htA, lenA, C )     cudaVCD_mulC( (cdPMatrix)(MB), (cdPMatrix)(MA), (htA)*(lenA), C )
#define cudaMCD_divC( MB, MA, htA, lenA, C )     cudaVCD_divC( (cdPMatrix)(MB), (cdPMatrix)(MA), (htA)*(lenA), C )
#define cudaMCD_mulReC( MB, MA, htA, lenA, CRe ) cudaVCD_mulReC( (cdPMatrix)(MB), (cdPMatrix)(MA), (htA)*(lenA), CRe )
#define cudaMCD_divReC( MB, MA, htA, lenA, CRe ) cudaVCD_divReC( (cdPMatrix)(MB), (cdPMatrix)(MA), (htA)*(lenA), CRe )
#define cudaMCD_lincomb( MC, MA, MB, htA, lenA, CA, CB ) \
                 cudaVCD_lincomb( (cdPMatrix)(MC), (cdPMatrix)(MA), (cdPMatrix)(MB), (htA)*(lenA), CA, CB )

#define cusdMCD_mulC( MB, MA, htA, lenA, d_CPtr )     cusdVCD_mulC( (cdPMatrix)(MB), (cdPMatrix)(MA), (htA)*(lenA), d_CPtr )
#define cusdMCD_divC( MB, MA, htA, lenA, d_CPtr )     cusdVCD_divC( (cdPMatrix)(MB), (cdPMatrix)(MA), (htA)*(lenA), d_CPtr )
#define cusdMCD_mulReC( MB, MA, htA, lenA, d_CRePtr ) cusdVCD_mulReC( (cdPMatrix)(MB), (cdPMatrix)(MA), (htA)*(lenA), d_CRePtr )
#define cusdMCD_divReC( MB, MA, htA, lenA, d_CRePtr ) cusdVCD_divReC( (cdPMatrix)(MB), (cdPMatrix)(MA), (htA)*(lenA), d_CRePtr )
#define cusdMCD_lincomb( MC, MA, MB, htA, lenA, d_CAPtr, d_CBPtr ) \
                 cusdVCD_lincomb( (cdPMatrix)(MC), (cdPMatrix)(MA), (cdPMatrix)(MB), (htA)*(lenA), d_CAPtr, d_CBPtr )

#define cudaMCD_mulV( Y, MA, X, htA, lenA )      cudaMCDmulV( Y, (cdPMatrix)(MA), X, htA, lenA )
                  /*  Y = MA * X.  sizX=lenA, sizY=htA;  both X and Y are column-vectors    */
#define cudaMCD_TmulV( Y, MA, X, htA, lenA )      cudaMCDTmulV( Y, (cdPMatrix)(MA), X, htA, lenA )
                  /*  Y = MAT * X.  sizX=htA, sizY=lenA; both X and Y are column-vectors    */
#define cudaVCD_mulM( Y, X, MA, htA, lenA )       cudaVCDmulM( Y, X, (cdPMatrix)(MA), htA, lenA )
                  /*  Y = X * MA.  sizX=htA, sizY=lenA;  both X and Y are row-vectors.
                             Mind the prefix: cudaVCD_ (not cudaMCD_)    */
#define cudaVCD_mulMT( Y, X, MA, htA, lenA )      cudaVCDmulMT( Y, X, (cdPMatrix)(MA), htA, lenA )
                 /*  Y = X * MAT.  sizX=lenA, sizY=htA;  both X and Y are row-vectors.   */
#define cudaMCD_mulM( MC, MA, MB, htA, lenA, lenB ) cudaMCDmulM( (cdPMatrix)(MC), (cdPMatrix)(MA), (cdPMatrix)(MB), htA, lenA, lenB )
                         /*  MC = MA * MB.  htB=lenA, htC=htA, lenC=lenB */
#define cudaMCD_mulMT( MC, MA, MB, htA, lenA, htB ) cudaMCDmulMT( (cdPMatrix)(MC), (cdPMatrix)(MA), (cdPMatrix)(MB), htA, lenA, htB )
                         /*  MC = MA * MBT.  lenB=lenA, htC=htA, lenC=htB */
#define cudaMCD_mulMH( MC, MA, MB, htA, lenA, htB ) cudaMCDmulMH( (cdPMatrix)(MC), (cdPMatrix)(MA), (cdPMatrix)(MB), htA, lenA, htB )
                         /*  MC = MA * MBH.  lenB=lenA, htC=htA, lenC=htB */
#define cudaMCD_TmulM( MC, MA, MB, htA, lenA, lenB ) cudaMCDTmulM( (cdPMatrix)(MC), (cdPMatrix)(MA), (cdPMatrix)(MB), htA, lenA, lenB )
                         /*  MC = MAT * MB.  htB=htA, htC=lenA, lenC=lenB */
#define cudaMCD_HmulM( MC, MA, MB, htA, lenA, lenB ) cudaMCDHmulM( (cdPMatrix)(MC), (cdPMatrix)(MA), (cdPMatrix)(MB), htA, lenA, lenB )
                         /*  MC = MAH * MB.  htB=htA, htC=lenA, lenC=lenB */
#define cudaMCD_TmulMT( MC, MA, MB, htA, lenA, htB ) cudaMCDTmulMT( (cdPMatrix)(MC), (cdPMatrix)(MA), (cdPMatrix)(MB), htA, lenA, htB )
                         /*  MC = MAT * MBT.  lenB=htA, htC=lenA, lenC=htB */
#define cudaMCD_TmulMH( MC, MA, MB, htA, lenA, htB )  cudaMCDTmulMH( (cdPMatrix)(MC), (cdPMatrix)(MA), (cdPMatrix)(MB), htA, lenA, htB )
                         /*  MC = MAT * MBH.  lenB=htA, htC=lenA, lenC=htB */
#define cudaMCDdia_mulM(  MC, MADia, MB, htB, lenB )  cudaMCDdiamulM(  (cdPMatrix)(MC), MADia, (cdPMatrix)(MB), htB, lenB )
#define cudaMCDdia_mulMT( MC, MADia, MB, htB, lenB )  cudaMCDdiamulMT( (cdPMatrix)(MC), MADia, (cdPMatrix)(MB), htB, lenB )
#define cudaMCD_mulMdia(  MC, MA, MBDia, htA, lenA )  cudaMCDmulMdia(  (cdPMatrix)(MC), (cdPMatrix)(MA), MBDia, htA, lenA )
#define cudaMCD_TmulMdia( MC, MA, MBDia, htA, lenA )  cudaMCDTmulMdia( (cdPMatrix)(MC), (cdPMatrix)(MA), MBDia, htA, lenA )


/***************** Two-Dimensional Fourier-Transform Methods ************/

#define cudaMCD_FFT( MY, MX, ht, len, dir )     cudaMCDFFT( (cdPMatrix)(MY), (cdPMatrix)(MX), ht, len, dir )
#define cudaMCD_Rows_FFT( MY, MX, ht, len, dir) cudaMCDRows_FFT( (cdPMatrix)(MY), (cdPMatrix)(MX), ht, len, dir )
#define cudaMCD_Cols_FFT( MY, MX, ht, len, dir) cudaMCDCols_FFT( (cdPMatrix)(MY), (cdPMatrix)(MX), ht, len, dir )
#define cudaMCD_filter( MY, MX, MFlt, ht, len ) cudaMCDfilter( (cdPMatrix)(MY), (cdPMatrix)(MX), (cdPMatrix)(MD)lt, ht, len )

/**************************  Input and Output  **************************
	The input/output functions involve memory transfers from device
	to host memory or vice versa. The generic cudaMCD_input/output functions
	allocate their own host buffers, whereas the cudaMCD_xxx_buf functions
	take a user-supplied buffer vector h_Wk (size must be >= ht*len )
	and are much more efficient.                                       */

#define cudaMCD_fprint( stream, MA, ht, len, linewidth ) \
                    cudaMCDfprint( stream, (cdPMatrix)(MA), ht, len, linewidth )
#define cudaMCD_print( MA, ht, len )  cudaMCDfprint( stdout, (cdPMatrix)(MA), ht, len, 80 )
#define cudaMCD_cprint( MA, ht, len ) cudaMCDcprint( (cdPMatrix)(MA), ht, len )
#define cudaMCD_fprint_buf( stream, MA, ht, len, linewidth, h_Wk ) \
                    cudaMCDfprint_buf( stream, (cdPMatrix)(MA), ht, len, linewidth, h_Wk )
#define cudaMCD_print_buf( MA, ht, len )  cudaMCDfprint_buf( stdout, (cdPMatrix)(MA), ht, len, 80, h_Wk )
#define cudaMCD_cprint_buf( MA, ht, len ) cudaMCDcprint_buf( (cdPMatrix)(MA), ht, len, h_Wk )
  /*  cudaMCD_print, cudaMCD_cprint usable only for console applications! */
#define cudaMCD_write( str, MA, ht, len )   cudaMCDwrite( str, (cdPMatrix)(MA), ht, len )
#define cudaMCD_read( MA, ht, len, str )    cudaMCDread( (cdPMatrix)(MA), ht, len, str )
#define cudaMCD_write_buf( str, MA, ht, len, h_Wk )   cudaMCDwrite_buf( str, (cdPMatrix)(MA), ht, len, h_Wk )
#define cudaMCD_read_buf( MA, ht, len, str, h_Wk )    cudaMCDread_buf( (cdPMatrix)(MA), ht, len, str, h_Wk )
                                   /* write and read in ascii format */
#define cudaMCD_store( str, MA, ht, len )   cudaVCD_store( str, (cdPMatrix)(MA), (len)*(ht) )
#define cudaMCD_recall( MA, ht, len, str)   cudaVCD_recall( (cdPMatrix)(MA), (len)*(ht), str)
#define cudaMCD_store_buf( str, MA, ht, len, h_Wk )   cudaVCD_store_buf( str, (cdPMatrix)(MA), (len)*(ht), h_Wk )
#define cudaMCD_recall_buf( MA, ht, len, str, h_Wk)   cudaVCD_recall_buf( (cdPMatrix)(MA), (len)*(ht), str, h_Wk )
                                  /* store and recall in binary format */

#endif /* C++ or plain-C declarations of functions working on device memory */


/*******************  Functions working on host memory: **********************
 *                                                                           *
 *	MDcu_func		(working on matrices in host memory, input type dMatrix, *
 *	scalar parameters on host and passed by value)                           *
 *****************************************************************************/ 

 /****************  Initialization  ****************************************/

#define MCDcu_equ0( MA, ht, len )            VCDcu_equ0( (MA)[0], (ht)*(len) )
#define MCDcu_equ1( MA, len )                MCDcuequ1( (MA)[0], len )  /* identity matrix */
#define MCDcu_equm1( MA, len )               MCDcuequm1( (MA)[0], len )  /* neg. identity matrix */
#define MCDcu_random( MA, ht, len, seed, Min, Max ) \
                                               VCDcu_random( (MA)[0], (ht)*(len), seed, Min, Max ) 
#define MCDcu_outerprod( MA, X, Y, ht, len ) MCDcuouterprod( (MA)[0], X, Y, ht, len )
                       /* sizX=ht, sizY=len */
#define MCDcu_Row_equ0( MA, ht, len, iRow ) MCDcuRow_equ0( (MA)[0], ht, len, iRow )
#define MCDcu_Col_equ0( MA, ht, len, iCol ) MCDcuCol_equ0( (MA)[0], ht, len, iCol )
#define MCDcu_Dia_equ0( MA, len )           MCDcuDia_equ0( (MA)[0], len )
#define MCDcu_Row_equC( MA, ht, len, iRow, C ) MCDcuRow_equC( (MA)[0], ht, len, iRow, C )
#define MCDcu_Col_equC( MA, ht, len, iCol, C ) MCDcuCol_equC( (MA)[0], ht, len, iCol, C )
#define MCDcu_Dia_equC( MA, len, C )           MCDcuDia_equC( (MA)[0], len, C )

#define MCDcu_Row_equV( MA, ht, len, iRow, X ) MCDcuRow_equV( (MA)[0], ht, len, iRow, X )
#define MCDcu_Col_equV( MA, ht, len, iCol, X ) MCDcuCol_equV( (MA)[0], ht, len, iCol, X )
#define MCDcu_Dia_equV( MA, len, X )           MCDcuDia_equV( (MA)[0], len, X )

#define MCDcu_Trd_equM( MA, MTrd, len )    MCDcuTrd_equM( (MA)[0], (MTrd)[0], len )
#define MCDcu_Trd_extract( MTrd, MA, len ) MCDcuTrd_extract( (MTrd)[0], (MA)[0], len )

#define MCDcu_equM( MB, MA, ht, len )      VCDcu_equV( (MB)[0], (MA)[0], ((ui)(len))*(ht) )
#define MCDcu_neg( MB, MA, ht, len )       VCDcu_neg( (MB)[0], (MA)[0], ((ui)(len))*(ht) )
#define MCDcu_conj( MB, MA, ht, len )      VCDcu_conj( (MB)[0], (MA)[0], ((ui)(len))*(ht) )

#define MCDcu_UequL( MA, len ) MCDcuUequL( (MA)[0], len )
#define MCDcu_LequU( MA, len ) MCDcuLequU( (MA)[0], len )
         /* copy lower-diagonal elements into upper-diagonal
           (or vice versa) by index-reflection, so as to
           get a symmetric matrix    */

            /* data-type conversions:  */
#define Mcu_CDtoCF( MCF, MCD, ht, len ) Vcu_CDtoCF( (MCF)[0], (MCD)[0], (ht)*(len) )
#define Mcu_CFtoCD( MCD, MCF, ht, len ) Vcu_CFtoCD( (MCD)[0], (MCF)[0], (ht)*(len) )

#define MDcu_CtoRe( MY, MCX, ht, len )           VDcu_CtoRe( (MY)[0],  (MCX)[0], (ht)*(len) )
#define MDcu_CtoIm( MY, MCX, ht, len )           VDcu_CtoIm( (MY)[0],  (MCX)[0], (ht)*(len) )
#define MDcu_CtoReIm( MYRe, MYIm, MCX, ht, len ) VDcu_CtoReIm( (MYRe)[0], (MYIm)[0], (MCX)[0], (ht)*(len) )
#define MDcu_RetoC( MCY, MX, ht, len )           VDcu_RetoC( (MCY)[0], (MX)[0],  (ht)*(len) )
#define MDcu_ImtoC( MCY, MX, ht, len )           VDcu_ImtoC( (MCY)[0], (MX)[0],  (ht)*(len) )
#define MDcu_ReImtoC( MCY, MXRe, MXIm, ht, len ) VDcu_ReImtoC( (MCY)[0], (MXRe)[0], (MXIm)[0], (ht)*(len) )

/********  Extracting a submatrix and copying a submatrix back  *********/

#define MCDcu_submatrix( MSub, subHt, subLen, \
                       MSrce, srceHt, srceLen, \
                       firstRowInCol, sampInCol, firstColInRow, sampInRow ) \
               MCDcusubmatrix(  (MSub)[0], subHt, subLen, \
                              (MSrce)[0], srceHt, srceLen, \
                              firstRowInCol, sampInCol, firstColInRow, sampInRow )

#define MCDcu_submatrix_equM( MDest, destHt, destLen, \
                            firstRowInCol, sampInCol, firstColInRow, sampInRow, \
                            MSrce, srceHt, srceLen ) \
               MCDcusubmatrix_equM(  (MDest)[0], destHt, destLen, \
                             firstRowInCol, sampInCol, firstColInRow, sampInRow, \
                             (MSrce)[0], srceHt, srceLen )

#define MCDcu_equMblock( MSub, subHt, subLen, \
                      MSrce, srceHt, srceLen, \
                      firstRowInCol, firstColInRow ) \
              MCDcuequMblock(  (MSub)[0], subHt, subLen, \
                             (MSrce)[0], srceHt, srceLen, \
                             firstRowInCol, firstColInRow )

#define MCDcu_block_equM( MDest, destHt, destLen, \
                       firstRowInCol, firstColInRow, \
                       MSrce, srceHt, srceLen ) \
              MCDcublock_equM( (MDest)[0], destHt, destLen, \
                             firstRowInCol, firstColInRow, \
                             (MSrce)[0], srceHt, srceLen )

#define MCDcu_equMblockT( MSub, subHt, subLen, \
                      MSrce, srceHt, srceLen, \
                      firstRowInCol, firstColInRow ) \
              MCDcuequMblockT( (MSub)[0], subHt, subLen, \
                             (MSrce)[0], srceHt, srceLen, \
                             firstRowInCol, firstColInRow )

#define MCDcu_block_equMT( MDest, destHt, destLen, \
                       firstRowInCol, firstColInRow, \
                       MSrce, srceHt, srceLen ) \
              MCDcublock_equMT( (MDest)[0], destHt, destLen, \
                             firstRowInCol, firstColInRow, \
                             (MSrce)[0], srceHt, srceLen )

/*****   Extracting a single row or a single column or the diagonal  ******
 *       and storing it into a vector                                     */

#define MCDcu_Row_extract( Y, MA, ht, len, iRow ) MCDcuRow_extract( Y, (MA)[0], ht, len, iRow )
#define MCDcu_Col_extract( Y, MA, ht, len, iCol ) MCDcuCol_extract( Y, (MA)[0], ht, len, iCol )
#define MCDcu_Dia_extract( Y, MA, len )           MCDcuDia_extract( Y, (MA)[0], len )


/**************  Deleting or inserting a row or a column   ***************/

#define MCDcu_Row_delete( MB, MA, htA, lenA, iRow )    MCDcuRow_delete( (MB)[0], (MA)[0], htA, lenA, iRow )
#define MCDcu_Col_delete( MB, MA, htA, lenA, iCol )    MCDcuCol_delete( (MB)[0], (MA)[0], htA, lenA, iCol )
#define MCDcu_Row_insert( MB, MA, htB, lenB, iRow, X ) MCDcuRow_insert( (MB)[0], (MA)[0], htB, lenB, iRow, X )
#define MCDcu_Col_insert( MB, MA, htB, lenB, iCol, X ) MCDcuCol_insert( (MB)[0], (MA)[0], htB, lenB, iCol, X )


/*****************    Basic arithmetic operations *********************
                      performed on one single row,
                      or one single column of any matrix,
                      or on the diagonal of a square matrix

    Note: In contrast to the analogous VectorLib functions, the operations
    are performed in-place, i.e. the input matrix itself is changed  */

#define MCDcu_Row_neg( MA, ht, len, iRow ) MCDcuRow_neg( (MA)[0], ht, len, iRow )
#define MCDcu_Col_neg( MA, ht, len, iCol ) MCDcuCol_neg( (MA)[0], ht, len, iCol )

#define MCDcu_Row_conj( MA, ht, len, iRow ) MCDcuRow_conj( (MA)[0], ht, len, iRow )
#define MCDcu_Col_conj( MA, ht, len, iCol ) MCDcuCol_conj( (MA)[0], ht, len, iCol )

#define MCDcu_Row_addC( MA, ht, len, iRow, C ) MCDcuRow_addC( (MA)[0], ht, len, iRow, C )
#define MCDcu_Col_addC( MA, ht, len, iCol, C ) MCDcuCol_addC( (MA)[0], ht, len, iCol, C )
#define MCDcu_Dia_addC( MA, len, C )           MCDcuDia_addC( (MA)[0], len, C )

#define MCDcu_Row_addV( MA, ht, len, iRow, X ) MCDcuRow_addV( (MA)[0], ht, len, iRow, X )
#define MCDcu_Col_addV( MA, ht, len, iCol, X ) MCDcuCol_addV( (MA)[0], ht, len, iCol, X )
#define MCDcu_Dia_addV( MA, len, X )           MCDcuDia_addV( (MA)[0], len, X )

#define MCDcu_Row_subC( MA, ht, len, iRow, C ) MCDcuRow_subC( (MA)[0], ht, len, iRow, C )
#define MCDcu_Col_subC( MA, ht, len, iCol, C ) MCDcuCol_subC( (MA)[0], ht, len, iCol, C )
#define MCDcu_Dia_subC( MA, len, C )           MCDcuDia_subC( (MA)[0], len, C )

#define MCDcu_Row_subV( MA, ht, len, iRow, X ) MCDcuRow_subV( (MA)[0], ht, len, iRow, X )
#define MCDcu_Col_subV( MA, ht, len, iCol, X ) MCDcuCol_subV( (MA)[0], ht, len, iCol, X )
#define MCDcu_Dia_subV( MA, len, X )           MCDcuDia_subV( (MA)[0], len, X )

#define MCDcu_Row_subrC( MA, ht, len, iRow, C ) MCDcuRow_subrC( (MA)[0], ht, len, iRow, C )
#define MCDcu_Col_subrC( MA, ht, len, iCol, C ) MCDcuCol_subrC( (MA)[0], ht, len, iCol, C )
#define MCDcu_Dia_subrC( MA, len, C )           MCDcuDia_subrC( (MA)[0], len, C )

#define MCDcu_Row_subrV( MA, ht, len, iRow, X ) MCDcuRow_subrV( (MA)[0], ht, len, iRow, X )
#define MCDcu_Col_subrV( MA, ht, len, iCol, X ) MCDcuCol_subrV( (MA)[0], ht, len, iCol, X )
#define MCDcu_Dia_subrV( MA, len, X )           MCDcuDia_subrV( (MA)[0], len, X )

#define MCDcu_Row_mulC( MA, ht, len, iRow, C ) MCDcuRow_mulC( (MA)[0], ht, len, iRow, C )
#define MCDcu_Col_mulC( MA, ht, len, iCol, C ) MCDcuCol_mulC( (MA)[0], ht, len, iCol, C )
#define MCDcu_Dia_mulC( MA, len, C )           MCDcuDia_mulC( (MA)[0], len, C )

#define MCDcu_Row_mulV( MA, ht, len, iRow, X ) MCDcuRow_mulV( (MA)[0], ht, len, iRow, X )
#define MCDcu_Col_mulV( MA, ht, len, iCol, X ) MCDcuCol_mulV( (MA)[0], ht, len, iCol, X )
#define MCDcu_Dia_mulV( MA, len, X )           MCDcuDia_mulV( (MA)[0], len, X )

#define MCDcu_Row_divC( MA, ht, len, iRow, C ) MCDcuRow_divC( (MA)[0], ht, len, iRow, C )
#define MCDcu_Col_divC( MA, ht, len, iCol, C ) MCDcuCol_divC( (MA)[0], ht, len, iCol, C )
#define MCDcu_Dia_divC( MA, len, C )           MCDcuDia_divC( (MA)[0], len, C )

#define MCDcu_Row_divV( MA, ht, len, iRow, X ) MCDcuRow_divV( (MA)[0], ht, len, iRow, X )
#define MCDcu_Col_divV( MA, ht, len, iCol, X ) MCDcuCol_divV( (MA)[0], ht, len, iCol, X )
#define MCDcu_Dia_divV( MA, len, X )           MCDcuDia_divV( (MA)[0], len, X )

#define MCDcu_Row_divrC( MA, ht, len, iRow, C ) MCDcuRow_divrC( (MA)[0], ht, len, iRow, C )
#define MCDcu_Col_divrC( MA, ht, len, iCol, C ) MCDcuCol_divrC( (MA)[0], ht, len, iCol, C )
#define MCDcu_Dia_divrC( MA, len, C )           MCDcuDia_divrC( (MA)[0], len, C )

#define MCDcu_Row_divrV( MA, ht, len, iRow, X ) MCDcuRow_divrV( (MA)[0], ht, len, iRow, X )
#define MCDcu_Col_divrV( MA, ht, len, iCol, X ) MCDcuCol_divrV( (MA)[0], ht, len, iCol, X )
#define MCDcu_Dia_divrV( MA, len, X )           MCDcuDia_divrV( (MA)[0], len, X )


/******  One-dimensional vector operations **********************
         performed along all rows or all columns simultaneously,
         or along the diagonal of a square matrix                */

#define MCDcu_Rows_absmax( Y, MA, ht, len )  MCDcuRows_absmax( Y, (MA)[0], ht, len )
#define MCDcu_Cols_absmax( Y, MA, ht, len )  MCDcuCols_absmax( Y, (MA)[0], ht, len )
#define MCDcu_Dia_absmax( MA, len )          MCDcuDia_absmax( (MA)[0], len )
#define MCDcu_Rows_absmin( Y, MA, ht, len )  MCDcuRows_absmin( Y, (MA)[0], ht, len )
#define MCDcu_Cols_absmin( Y, MA, ht, len )  MCDcuCols_absmin( Y, (MA)[0], ht, len )
#define MCDcu_Dia_absmin( MA, len )          MCDcuDia_absmin( (MA)[0], len )

#define MCDcu_Rows_maxReIm( Y, MA, ht, len ) MCDcuRows_maxReIm( Y, (MA)[0], ht, len )
#define MCDcu_Cols_maxReIm( Y, MA, ht, len ) MCDcuCols_maxReIm( Y, (MA)[0], ht, len )
#define MCDcu_Dia_maxReIm( MA, len )         MCDcuDia_maxReIm( (MA)[0], len )
#define MCDcu_Rows_minReIm( Y, MA, ht, len ) MCDcuRows_minReIm( Y, (MA)[0], ht, len )
#define MCDcu_Cols_minReIm( Y, MA, ht, len ) MCDcuCols_minReIm( Y, (MA)[0], ht, len )
#define MCDcu_Dia_minReIm( MA, len )         MCDcuDia_minReIm( (MA)[0], len )

#define MCDcu_Rows_absmaxReIm( Y, MA, ht, len ) MCDcuRows_absmaxReIm( Y, (MA)[0], ht, len )
#define MCDcu_Cols_absmaxReIm( Y, MA, ht, len ) MCDcuCols_absmaxReIm( Y, (MA)[0], ht, len )
#define MCDcu_Dia_absmaxReIm( MA, len )         MCDcuDia_absmaxReIm( (MA)[0], len )
#define MCDcu_Rows_absminReIm( Y, MA, ht, len ) MCDcuRows_absminReIm( Y, (MA)[0], ht, len )
#define MCDcu_Cols_absminReIm( Y, MA, ht, len ) MCDcuCols_absminReIm( Y, (MA)[0], ht, len )
#define MCDcu_Dia_absminReIm( MA, len )         MCDcuDia_absminReIm( (MA)[0], len )

#define MCDcu_Rows_cabsmax( Y, MA, ht, len ) MCDcuRows_cabsmax( Y, (MA)[0], ht, len )
#define MCDcu_Cols_cabsmax( Y, MA, ht, len ) MCDcuCols_cabsmax( Y, (MA)[0], ht, len )
#define MCDcu_Dia_cabsmax( MA, len )         MCDcuDia_cabsmax( (MA)[0], len )
#define MCDcu_Rows_cabsmin( Y, MA, ht, len ) MCDcuRows_cabsmin( Y, (MA)[0], ht, len )
#define MCDcu_Cols_cabsmin( Y, MA, ht, len ) MCDcuCols_cabsmin( Y, (MA)[0], ht, len )
#define MCDcu_Dia_cabsmin( MA, len )         MCDcuDia_cabsmin( (MA)[0], len )

#define MCDcu_Rows_sabsmax( Y, MA, ht, len ) MCDcuRows_sabsmax( Y, (MA)[0], ht, len )
#define MCDcu_Cols_sabsmax( Y, MA, ht, len ) MCDcuCols_sabsmax( Y, (MA)[0], ht, len )
#define MCDcu_Dia_sabsmax( MA, len )         MCDcuDia_sabsmax( (MA)[0], len )
#define MCDcu_Rows_sabsmin( Y, MA, ht, len ) MCDcuRows_sabsmin( Y, (MA)[0], ht, len )
#define MCDcu_Cols_sabsmin( Y, MA, ht, len ) MCDcuCols_sabsmin( Y, (MA)[0], ht, len )
#define MCDcu_Dia_sabsmin( MA, len )         MCDcuDia_sabsmin( (MA)[0], len )

#define MCDcu_Rows_sum( Y, MA, ht, len )     MCDcuRows_sum( Y, (MA)[0], ht, len )
#define MCDcu_Cols_sum( Y, MA, ht, len )     MCDcuCols_sum( Y, (MA)[0], ht, len )
#define MCDcu_Dia_sum(  MA, len )            MCDcuDia_sum( (MA)[0], len )
#define MCDcu_Rows_prod( Y, MA, ht, len )    MCDcuRows_prod( Y, (MA)[0], ht, len )
#define MCDcu_Cols_prod( Y, MA, ht, len )    MCDcuCols_prod( Y, (MA)[0], ht, len )
#define MCDcu_Dia_prod(  MA, len )           MCDcuDia_prod( (MA)[0], len )

#define MCDcu_Rows_runsum( MA, ht, len )     MCDcuRows_runsum( (MA)[0], ht, len )
#define MCDcu_Cols_runsum( MA, ht, len )     MCDcuCols_runsum( (MA)[0], ht, len )
#define MCDcu_Rows_runprod( MA, ht, len )    MCDcuRows_runprod( (MA)[0], ht, len )
#define MCDcu_Cols_runprod( MA, ht, len )    MCDcuCols_runprod( (MA)[0], ht, len )

#define MCDcu_Rows_rotate( MA, ht, len, pos) MCDcuRows_rotate( (MA)[0], ht, len, pos )
#define MCDcu_Cols_rotate( MA, ht, len, pos) MCDcuCols_rotate( (MA)[0], ht, len, pos )
#define MCDcu_Rows_rotate_buf( MA, ht, len, pos, MBuf) MCDcuRows_rotate_buf( (MA)[0], ht, len, pos, (MBuf)[0] )
#define MCDcu_Cols_rotate_buf( MA, ht, len, pos, MBuf) MCDcuCols_rotate_buf( (MA)[0], ht, len, pos, (MBuf)[0] )
#define MCDcu_Rows_reflect( MA, ht, len)     MCDcuRows_reflect( (MA)[0], ht, len )
#define MCDcu_Cols_reflect( MA, ht, len)     MCDcuCols_reflect( (MA)[0], ht, len )
#define MCDcu_Rows_rev( MA, ht, len)         MCDcuRows_rev( (MA)[0], ht, len )
#define MCDcu_Cols_rev( MA, ht, len)         MCDcuCols_rev( (MA)[0], ht, len )


/********  Operations involving two rows or two colums of one matrix  *****/

#define MCDcu_Rows_exchange( MA, ht, len, row1, row2 )  MCDcuRows_exchange( (MA)[0], ht, len, row1, row2 )
#define MCDcu_Cols_exchange( MA, ht, len, col1, col2 )  MCDcuCols_exchange( (MA)[0], ht, len, col1, col2 )

#define MCDcu_Rows_add( MA, ht, len, destRow, srceRow ) MCDcuRows_add( (MA)[0], ht, len, destRow, srceRow )
#define MCDcu_Cols_add( MA, ht, len, destCol, srceCol ) MCDcuCols_add( (MA)[0], ht, len, destCol, srceCol )
                         /* dest[i] += source[i]  */

#define MCDcu_Rows_sub( MA, ht, len, destRow, srceRow ) MCDcuRows_sub( (MA)[0], ht, len, destRow, srceRow )
#define MCDcu_Cols_sub( MA, ht, len, destCol, srceCol ) MCDcuCols_sub( (MA)[0], ht, len, destCol, srceCol )
                         /* dest[i] -= source[i]  */

#define MCDcu_Rows_Cadd( MA, ht, len, destRow, srceRow, C ) MCDcuRows_Cadd( (MA)[0], ht, len, destRow, srceRow, C )
#define MCDcu_Cols_Cadd( MA, ht, len, destCol, srceCol, C ) MCDcuCols_Cadd( (MA)[0], ht, len, destCol, srceCol, C )
                         /* dest[i] += C * source[i]  */

#define MCDcu_Rows_lincomb( MA, ht, len, destRow, destC, srceRow, srceC ) \
            MCDcuRows_lincomb( (MA)[0], ht, len, destRow, destC, srceRow, srceC )
#define MCDcu_Cols_lincomb( MA, ht, len, destCol, destC, srceCol, srceC ) \
            MCDcuCols_lincomb( (MA)[0], ht, len, destCol, destC, srceCol, srceC )
  /*  linear combination: dest[i] = destC * dest[i] + sourceC * source[i] */


/*****************  Transposing and rotating a matrix **********************/

#define MCDcu_transpose( MTr, MA, htTr, lenTr )    MCDcutranspose( (MTr)[0], (MA)[0], htTr, lenTr )
       /*  the dimensions htTr, lenTr are those of the transposed matrix,
           not of the original!                */
#define MCDcu_hermconj( MHConj, MA, htTr, lenTr )  MCDcuhermconj( (MHConj)[0], (MA)[0], htTr, lenTr )
#define MCDcu_rotate90( MRot, MA, htRot, lenRot )  MCDcurotate90( (MRot)[0], (MA)[0], htRot, lenRot )
#define MCDcu_rotate180( MRot, MA, htRot, lenRot ) VCDcu_rev( (MRot)[0], (MA)[0], (htRot)*(lenRot) )
#define MCDcu_rotate270( MRot, MA, htRot, lenRot ) MCDcurotate270( (MRot)[0], (MA)[0], htRot, lenRot )


/************************ Matrix Arithmetics *************************/

#define MCDcu_addM( MC, MA, MB, htA, lenA )    VCDcu_addV( (MC)[0], (MA)[0], (MB)[0], (htA)*(lenA) )
#define MCDcu_addMT( MC, MA, MB, htA, lenA )   MCDcuaddMT( (MC)[0], (MA)[0], (MB)[0], htA, lenA )
#define MCDcu_subM( MC, MA, MB, htA, lenA )    VCDcu_subV( (MC)[0], (MA)[0], (MB)[0], (htA)*(lenA) )
#define MCDcu_subMT( MC, MA, MB, htA, lenA )   MCDcusubMT( (MC)[0], (MA)[0], (MB)[0], htA, lenA )
#define MCDcu_subrMT( MC, MA, MB, htA, lenA )  MCDcusubrMT( (MC)[0], (MA)[0], (MB)[0], htA, lenA )
#define MCDcu_mulC( MB, MA, htA, lenA, C )     VCDcu_mulC( (MB)[0], (MA)[0], (htA)*(lenA), C )
#define MCDcu_divC( MB, MA, htA, lenA, C )     VCDcu_divC( (MB)[0], (MA)[0], (htA)*(lenA), C )
#define MCDcu_mulReC( MB, MA, htA, lenA, CRe ) VCDcu_mulReC( (MB)[0], (MA)[0], (htA)*(lenA), CRe )
#define MCDcu_divReC( MB, MA, htA, lenA, CRe ) VCDcu_divReC( (MB)[0], (MA)[0], (htA)*(lenA), CRe )
#define MCDcu_lincomb( MC, MA, MB, htA, lenA, CA, CB ) \
                 VCDcu_lincomb( (MC)[0], (MA)[0], (MB)[0], (htA)*(lenA), CA, CB )

#define MCDcu_mulV( Y, MA, X, htA, lenA )      MCDcumulV( Y, (MA)[0], X, htA, lenA )
                  /*  Y = MA * X.  sizX=lenA, sizY=htA;  both X and Y are column-vectors    */
#define MCDcu_TmulV( Y, MA, X, htA, lenA )      MCDcuTmulV( Y, (MA)[0], X, htA, lenA )
                  /*  Y = MAT * X.  sizX=htA, sizY=lenA; both X and Y are column-vectors    */
#define VCDcu_mulM( Y, X, MA, htA, lenA )       VCDcumulM( Y, X, (MA)[0], htA, lenA )
                  /*  Y = X * MA.  sizX=htA, sizY=lenA;  both X and Y are row-vectors.
                             Mind the prefix: VCDcu_ (not MCDcu_)    */
#define VCDcu_mulMT( Y, X, MA, htA, lenA )      VCDcumulMT( Y, X, (MA)[0], htA, lenA )
                 /*  Y = X * MAT.  sizX=lenA, sizY=htA;  both X and Y are row-vectors.   */
#define MCDcu_mulM( MC, MA, MB, htA, lenA, lenB ) MCDcumulM( (MC)[0], (MA)[0], (MB)[0], htA, lenA, lenB )
                         /*  MC = MA * MB.  htB=lenA, htC=htA, lenC=lenB */
#define MCDcu_mulMT( MC, MA, MB, htA, lenA, htB ) MCDcumulMT( (MC)[0], (MA)[0], (MB)[0], htA, lenA, htB )
                         /*  MC = MA * MBT.  lenB=lenA, htC=htA, lenC=htB */
#define MCDcu_mulMH( MC, MA, MB, htA, lenA, htB ) MCDcumulMH( (MC)[0], (MA)[0], (MB)[0], htA, lenA, htB )
                         /*  MC = MA * MBH.  lenB=lenA, htC=htA, lenC=htB */
#define MCDcu_TmulM( MC, MA, MB, htA, lenA, lenB ) MCDcuTmulM( (MC)[0], (MA)[0], (MB)[0], htA, lenA, lenB )
                         /*  MC = MAT * MB.  htB=htA, htC=lenA, lenC=lenB */
#define MCDcu_HmulM( MC, MA, MB, htA, lenA, lenB ) MCDcuHmulM( (MC)[0], (MA)[0], (MB)[0], htA, lenA, lenB )
                         /*  MC = MAH * MB.  htB=htA, htC=lenA, lenC=lenB */
#define MCDcu_TmulMT( MC, MA, MB, htA, lenA, htB ) MCDcuTmulMT( (MC)[0], (MA)[0], (MB)[0], htA, lenA, htB )
                         /*  MC = MAT * MBT.  lenB=htA, htC=lenA, lenC=htB */
#define MCDcu_TmulMH( MC, MA, MB, htA, lenA, htB )  MCDcuTmulMH( (MC)[0], (MA)[0], (MB)[0], htA, lenA, htB )
                         /*  MC = MAT * MBH.  lenB=htA, htC=lenA, lenC=htB */
#define MCDdiacu_mulM(  MC, MADia, MB, htB, lenB )  MCDdiacumulM(  (MC)[0], MADia, (MB)[0], htB, lenB )
#define MCDdiacu_mulMT( MC, MADia, MB, htB, lenB )  MCDdiacumulMT( (MC)[0], MADia, (MB)[0], htB, lenB )
#define MCDcu_mulMdia(  MC, MA, MBDia, htA, lenA )  MCDcumulMdia(  (MC)[0], (MA)[0], MBDia, htA, lenA )
#define MCDcu_TmulMdia( MC, MA, MBDia, htA, lenA )  MCDcuTmulMdia( (MC)[0], (MA)[0], MBDia, htA, lenA )


/***************** Two-Dimensional Fourier-Transform Methods ************/

#define MCDcu_FFT( MY, MX, ht, len, dir )     MCDcuFFT( (MY)[0], (MX)[0], ht, len, dir )
#define MCDcu_Rows_FFT( MY, MX, ht, len, dir) MCDcuRows_FFT( (MY)[0], (MX)[0], ht, len, dir )
#define MCDcu_Cols_FFT( MY, MX, ht, len, dir) MCDcuCols_FFT( (MY)[0], (MX)[0], ht, len, dir )
#define MCDcu_filter( MY, MX, MFlt, ht, len ) MCDcufilter( (MY)[0], (MX)[0], (MFlt)[0], ht, len )


/*************************************************************************
 * Declarations of the functions written without underbar in the prefix: *
 *	MCDcufunc		(as MCDcu_func, but input type 
                       cdPMatrix = cdVector = pointer to matrix element[0][0])
 *	cusdMCDfunc		(as cusdMCD_func, but input type 
                       cdPMatrix = cdVector = pointer to matrix element[0][0])
 *************************************************************************/


#define MCDcuequ0( MA, ht, len )    VCDcu_equ0( MA, (ht)*(len) )
void   __vf OVCUAPI  MCDcuequ1( cdPMatrix MA, ui len );  /* identity matrix */
void   __vf OVCUAPI  MCDcuequm1( cdPMatrix MA, ui len );  /* neg. identity matrix */
void   __vf OVCUAPI  MCDcuouterprod( cdPMatrix MA, cdVector X,  cdVector Y, ui ht, ui len );

void   __vf OVCUAPI  MCDcuRow_equ0( cdPMatrix MA, ui ht, ui len, ui iRow );
void   __vf OVCUAPI  MCDcuCol_equ0( cdPMatrix MA, ui ht, ui len, ui iCol );
void   __vf OVCUAPI  MCDcuDia_equ0( cdPMatrix MA, ui len );

void   __vf OVCUAPI  MCDcuRow_equC( cdPMatrix MA, ui ht, ui len, ui iRow, dComplex C );
void   __vf OVCUAPI  MCDcuCol_equC( cdPMatrix MA, ui ht, ui len, ui iCol, dComplex C );
void   __vf OVCUAPI  MCDcuDia_equC( cdPMatrix MA, ui len, dComplex C );

void   __vf OVCUAPI  MCDcuRow_equV( cdPMatrix MA, ui ht, ui len, ui iRow, cdVector X );
void   __vf OVCUAPI  MCDcuCol_equV( cdPMatrix MA, ui ht, ui len, ui iCol, cdVector X );
void   __vf OVCUAPI  MCDcuDia_equV( cdPMatrix MA, ui len, cdVector X );

void   __vf OVCUAPI  MCDcuTrd_equM( cdPMatrix MA, cdPMatrix MTrd, ui len );
void   __vf OVCUAPI  MCDcuTrd_extract( cdPMatrix MTrd, cdPMatrix MA, ui len );

#define MCDcuequM( MB, MA, ht, len )  VCDcu_equV( MB, MA, (ht)*(len) )
#define MCDcuneg( MB, MA, ht, len )   VCDcu_neg( MB, MA, (ht)*(len) )
#define MCDcuconj( MB, MA, ht, len )  VCDcu_conj( MB, MA, (ht)*(len) )

void   __vf OVCUAPI  MCDcuUequL( cdPMatrix MA, ui len );
void   __vf OVCUAPI  MCDcuLequU( cdPMatrix MA, ui len );

            /* data-type conversions:  */
#define McuCDtoCF( MCF, MCD, ht, len ) Vcu_CDtoCF( (MCF), (MCD), (ht)*(len) )
#define McuCFtoCD( MCD, MCF, ht, len ) Vcu_CFtoCD( (MCD), (MCF), (ht)*(len) )

#define MDcuCtoRe( MY, MCX, ht, len )           VDcu_CtoRe( (MY),  (MCX), (ht)*(len) )
#define MDcuCtoIm( MY, MCX, ht, len )           VDcu_CtoIm( (MY),  (MCX), (ht)*(len) )
#define MDcuCtoReIm( MYRe, MYIm, MCX, ht, len ) VDcu_CtoReIm( (MYRe), (MYIm), (MCX), (ht)*(len) )
#define MDcuRetoC( MCY, MX, ht, len )           VDcu_RetoC( (MCY), (MX),  (ht)*(len) )
#define MDcuImtoC( MCY, MX, ht, len )           VDcu_ImtoC( (MCY), (MX),  (ht)*(len) )
#define MDcuReImtoC( MCY, MXRe, MXIm, ht, len ) VDcu_ReImtoC( (MCY), (MXRe), (MXIm), (ht)*(len) )

/********  Extracting a submatrix and copying a submatrix back  *********/

void  __vf OVCUAPI  MCDcusubmatrix( cdPMatrix MSub, ui subHt,  ui subLen,
                          cdPMatrix MSrce, ui srceHt,  ui srceLen,
                          ui firstRowInCol,  ui sampInCol,
                          ui firstColInRow,  ui sampInRow );

void  __vf OVCUAPI  MCDcusubmatrix_equM( cdPMatrix MDest, ui destHt, ui destLen,
                               ui firstRowInCol,  ui sampInCol,
                               ui firstColInRow,  ui sampInRow,
                               cdPMatrix MSrce, ui srceHt, ui srceLen );

void  __vf OVCUAPI  MCDcuequMblock( cdPMatrix MSub, ui subHt,  ui subLen,
                          cdPMatrix MSrce, ui srceHt,  ui srceLen,
                          ui firstRowInCol,  ui firstColInRow );

void  __vf OVCUAPI  MCDcublock_equM( cdPMatrix MDest, ui destHt, ui destLen,
                           ui firstRowInCol,  ui firstColInRow,
                           cdPMatrix MSrce, ui srceHt,  ui srceLen );

void  __vf OVCUAPI  MCDcuequMblockT( cdPMatrix MSub,  ui subHt,  ui subLen,
                          cdPMatrix MSrce,  ui srceHt,  ui srceLen,
                          ui firstRowInCol,  ui firstColInRow );

void  __vf OVCUAPI  MCDcublock_equMT( cdPMatrix MDest,  ui destHt,  ui destLen,
                           ui firstRowInCol,  ui firstColInRow,
                           cdPMatrix MSrce,  ui srceHt,  ui srceLen );


/*****   Extracting a single row or a single column or the diagonal  *****
 *       and storing it into a vector                                    */

void __vf OVCUAPI  MCDcuRow_extract( cdVector Y, cdPMatrix MA, ui ht, ui len, ui iRow );
void __vf OVCUAPI  MCDcuCol_extract( cdVector Y, cdPMatrix MA, ui ht, ui len, ui iCol );
void __vf OVCUAPI  MCDcuDia_extract( cdVector Y, cdPMatrix MA, ui len );

/**********  Deleting or inserting a row or a column *****************/

void __vf OVCUAPI  MCDcuRow_delete( cdPMatrix MB, cdPMatrix MA, ui htA, ui lenA, ui iRow );
void __vf OVCUAPI  MCDcuCol_delete( cdPMatrix MB, cdPMatrix MA, ui htA, ui lenA, ui iCol );
void __vf OVCUAPI  MCDcuRow_insert( cdPMatrix MB, cdPMatrix MA, ui htB, ui lenB, ui iRow, cdVector X );
void __vf OVCUAPI  MCDcuCol_insert( cdPMatrix MB, cdPMatrix MA, ui htB, ui lenB, ui iCol, cdVector X );


/*****************    Basic arithmetic operations ***********************
     performed on one single row,  or one single column of any matrix,
     or on the diagonal of a square matrix                              */

void   __vf OVCUAPI  MCDcuRow_neg( cdPMatrix MX, ui ht, ui len, ui iRow );
void   __vf OVCUAPI  MCDcuCol_neg( cdPMatrix MX, ui ht, ui len, ui iCol );

void   __vf OVCUAPI  MCDcuRow_conj( cdPMatrix MX, ui ht, ui len, ui iRow );
void   __vf OVCUAPI  MCDcuCol_conj( cdPMatrix MX, ui ht, ui len, ui iCol );

void   __vf OVCUAPI  MCDcuRow_addC( cdPMatrix MA, ui ht, ui len, ui iRow, dComplex C );
void   __vf OVCUAPI  MCDcuCol_addC( cdPMatrix MA, ui ht, ui len, ui iCol, dComplex C );
void   __vf OVCUAPI  MCDcuDia_addC( cdPMatrix MA, ui len, dComplex C );

void   __vf OVCUAPI  MCDcuRow_subC( cdPMatrix MA, ui ht, ui len, ui iRow, dComplex C );
void   __vf OVCUAPI  MCDcuCol_subC( cdPMatrix MA, ui ht, ui len, ui iCol, dComplex C );
void   __vf OVCUAPI  MCDcuDia_subC( cdPMatrix MA, ui len, dComplex C );

void   __vf OVCUAPI  MCDcuRow_addV( cdPMatrix MA, ui ht, ui len, ui iRow, cdVector X );
void   __vf OVCUAPI  MCDcuCol_addV( cdPMatrix MA, ui ht, ui len, ui iCol, cdVector X );
void   __vf OVCUAPI  MCDcuDia_addV( cdPMatrix MA, ui len, cdVector X );

void   __vf OVCUAPI  MCDcuRow_subV( cdPMatrix MA, ui ht, ui len, ui iRow, cdVector X );
void   __vf OVCUAPI  MCDcuCol_subV( cdPMatrix MA, ui ht, ui len, ui iCol, cdVector X );
void   __vf OVCUAPI  MCDcuDia_subV( cdPMatrix MA, ui len, cdVector X );

void   __vf OVCUAPI  MCDcuRow_subrC( cdPMatrix MA, ui ht, ui len, ui iRow, dComplex C );
void   __vf OVCUAPI  MCDcuCol_subrC( cdPMatrix MA, ui ht, ui len, ui iCol, dComplex C );
void   __vf OVCUAPI  MCDcuDia_subrC( cdPMatrix MA, ui len, dComplex C );

void   __vf OVCUAPI  MCDcuRow_subrV( cdPMatrix MA, ui ht, ui len, ui iRow, cdVector X );
void   __vf OVCUAPI  MCDcuCol_subrV( cdPMatrix MA, ui ht, ui len, ui iCol, cdVector X );
void   __vf OVCUAPI  MCDcuDia_subrV( cdPMatrix MA, ui len, cdVector X );

void   __vf OVCUAPI  MCDcuRow_mulC( cdPMatrix MA, ui ht, ui len, ui iRow, dComplex C );
void   __vf OVCUAPI  MCDcuCol_mulC( cdPMatrix MA, ui ht, ui len, ui iCol, dComplex C );
void   __vf OVCUAPI  MCDcuDia_mulC( cdPMatrix MA, ui len, dComplex C );

void   __vf OVCUAPI  MCDcuRow_mulV( cdPMatrix MA, ui ht, ui len, ui iRow, cdVector X );
void   __vf OVCUAPI  MCDcuCol_mulV( cdPMatrix MA, ui ht, ui len, ui iCol, cdVector X );
void   __vf OVCUAPI  MCDcuDia_mulV( cdPMatrix MA, ui len, cdVector X );

void   __vf OVCUAPI  MCDcuRow_divC( cdPMatrix MA, ui ht, ui len, ui iRow, dComplex C );
void   __vf OVCUAPI  MCDcuCol_divC( cdPMatrix MA, ui ht, ui len, ui iCol, dComplex C );
void   __vf OVCUAPI  MCDcuDia_divC( cdPMatrix MA, ui len, dComplex C );

void   __vf OVCUAPI  MCDcuRow_divV( cdPMatrix MA, ui ht, ui len, ui iRow, cdVector X );
void   __vf OVCUAPI  MCDcuCol_divV( cdPMatrix MA, ui ht, ui len, ui iCol, cdVector X );
void   __vf OVCUAPI  MCDcuDia_divV( cdPMatrix MA, ui len, cdVector X );

void   __vf OVCUAPI  MCDcuRow_divrC( cdPMatrix MA, ui ht, ui len, ui iRow, dComplex C );
void   __vf OVCUAPI  MCDcuCol_divrC( cdPMatrix MA, ui ht, ui len, ui iCol, dComplex C );
void   __vf OVCUAPI  MCDcuDia_divrC( cdPMatrix MA, ui len, dComplex C );

void   __vf OVCUAPI  MCDcuRow_divrV( cdPMatrix MA, ui ht, ui len, ui iRow, cdVector X );
void   __vf OVCUAPI  MCDcuCol_divrV( cdPMatrix MA, ui ht, ui len, ui iCol, cdVector X );
void   __vf OVCUAPI  MCDcuDia_divrV( cdPMatrix MA, ui len, cdVector X );


/******  One-dimensional vector operations **********************
         performed along all rows or all columns simultaneously,
         or along the diagonal of a square matrix                */

void     __vf OVCUAPI  MCDcuRows_absmax( dVector Y, cdPMatrix MA, ui ht, ui len );
void     __vf OVCUAPI  MCDcuCols_absmax( dVector Y, cdPMatrix MA, ui ht, ui len );
double    __vf OVCUAPI  MCDcuDia_absmax(  cdPMatrix MA, ui len );
void     __vf OVCUAPI  MCDcuRows_absmin( dVector Y, cdPMatrix MA, ui ht, ui len );
void     __vf OVCUAPI  MCDcuCols_absmin( dVector Y, cdPMatrix MA, ui ht, ui len );
double    __vf OVCUAPI  MCDcuDia_absmin(  cdPMatrix MA, ui len );

void     __vf OVCUAPI  MCDcuRows_maxReIm( cdVector Y, cdPMatrix MA, ui ht, ui len );
void     __vf OVCUAPI  MCDcuCols_maxReIm( cdVector Y, cdPMatrix MA, ui ht, ui len );
void     __vf OVCUAPI  MCDcuRows_minReIm( cdVector Y, cdPMatrix MA, ui ht, ui len );
void     __vf OVCUAPI  MCDcuCols_minReIm( cdVector Y, cdPMatrix MA, ui ht, ui len );

void     __vf OVCUAPI  MCDcuRows_absmaxReIm( cdVector Y, cdPMatrix MA, ui ht, ui len );
void     __vf OVCUAPI  MCDcuCols_absmaxReIm( cdVector Y, cdPMatrix MA, ui ht, ui len );
void     __vf OVCUAPI  MCDcuRows_absminReIm( cdVector Y, cdPMatrix MA, ui ht, ui len );
void     __vf OVCUAPI  MCDcuCols_absminReIm( cdVector Y, cdPMatrix MA, ui ht, ui len );

void     __vf OVCUAPI  MCDcuRows_cabsmax( cdVector Y, cdPMatrix MA, ui ht, ui len );
void     __vf OVCUAPI  MCDcuCols_cabsmax( cdVector Y, cdPMatrix MA, ui ht, ui len );
void     __vf OVCUAPI  MCDcuRows_cabsmin( cdVector Y, cdPMatrix MA, ui ht, ui len );
void     __vf OVCUAPI  MCDcuCols_cabsmin( cdVector Y, cdPMatrix MA, ui ht, ui len );

void     __vf OVCUAPI  MCDcuRows_sabsmax( cdVector Y, cdPMatrix MA, ui ht, ui len );
void     __vf OVCUAPI  MCDcuCols_sabsmax( cdVector Y, cdPMatrix MA, ui ht, ui len );
void     __vf OVCUAPI  MCDcuRows_sabsmin( cdVector Y, cdPMatrix MA, ui ht, ui len );
void     __vf OVCUAPI  MCDcuCols_sabsmin( cdVector Y, cdPMatrix MA, ui ht, ui len );

void     __vf OVCUAPI  MCDcuRows_sum( cdVector Y, cdPMatrix MA, ui ht, ui len );
void     __vf OVCUAPI  MCDcuCols_sum( cdVector Y, cdPMatrix MA, ui ht, ui len );
void     __vf OVCUAPI  MCDcuRows_prod(cdVector Y, cdPMatrix MA, ui ht, ui len );
void     __vf OVCUAPI  MCDcuCols_prod(cdVector Y, cdPMatrix MA, ui ht, ui len );

#if defined __cplusplus && defined _CMATH_CLASSDEFS
}   /* following functions cannot be extern "C", if fComplex is a class */
#endif
dComplex     __vf OVCUAPI_ifNotClass  MCDcuDia_maxReIm(  cdPMatrix MA, ui len );
dComplex     __vf OVCUAPI_ifNotClass  MCDcuDia_minReIm(  cdPMatrix MA, ui len );
dComplex     __vf OVCUAPI_ifNotClass  MCDcuDia_absmaxReIm(  cdPMatrix MA, ui len );
dComplex     __vf OVCUAPI_ifNotClass  MCDcuDia_absminReIm(  cdPMatrix MA, ui len );
dComplex     __vf OVCUAPI_ifNotClass  MCDcuDia_cabsmax(  cdPMatrix MA, ui len );
dComplex     __vf OVCUAPI_ifNotClass  MCDcuDia_cabsmin(  cdPMatrix MA, ui len );
dComplex     __vf OVCUAPI_ifNotClass  MCDcuDia_sabsmax(  cdPMatrix MA, ui len );
dComplex     __vf OVCUAPI_ifNotClass  MCDcuDia_sabsmin(  cdPMatrix MA, ui len );
dComplex     __vf OVCUAPI_ifNotClass  MCDcuDia_sum(  cdPMatrix MA, ui len );
dComplex     __vf OVCUAPI_ifNotClass  MCDcuDia_prod( cdPMatrix MA, ui len );
#if defined __cplusplus && defined _CMATH_CLASSDEFS
extern "C" {
#endif

void  __vf OVCUAPI  MCDcuRows_runsum( cdPMatrix MA, ui ht, ui len );
void  __vf OVCUAPI  MCDcuCols_runsum( cdPMatrix MA, ui ht, ui len );
void  __vf OVCUAPI  MCDcuRows_runprod( cdPMatrix MA, ui ht, ui len );
void  __vf OVCUAPI  MCDcuCols_runprod( cdPMatrix MA, ui ht, ui len );

void  __vf OVCUAPI  MCDcuRows_rotate( cdPMatrix MA, ui ht, ui len, ssize_t pos );
void  __vf OVCUAPI  MCDcuCols_rotate( cdPMatrix MA, ui ht, ui len, ssize_t pos );
void  __vf OVCUAPI  MCDcuRows_rotate_buf( cdPMatrix MA, ui ht, ui len, ssize_t pos, cdPMatrix MBuf );
void  __vf OVCUAPI  MCDcuCols_rotate_buf( cdPMatrix MA, ui ht, ui len, ssize_t pos, cdPMatrix MBuf );
void  __vf OVCUAPI  MCDcuRows_reflect( cdPMatrix MA, ui ht, ui len );
void  __vf OVCUAPI  MCDcuCols_reflect( cdPMatrix MA, ui ht, ui len );
void  __vf OVCUAPI  MCDcuRows_rev( cdPMatrix MA, ui ht, ui len );
void  __vf OVCUAPI  MCDcuCols_rev( cdPMatrix MA, ui ht, ui len );

/********  Operations involving two rows or two colums of one matrix  *****/

void   __vf OVCUAPI  MCDcuRows_exchange( cdPMatrix MA, ui ht, ui len, ui i1, ui i2 );
void   __vf OVCUAPI  MCDcuCols_exchange( cdPMatrix MA, ui ht, ui len, ui i1, ui i2 );

void   __vf OVCUAPI  MCDcuRows_add( cdPMatrix MA, ui ht, ui len, ui destRow, ui sourceRow );
void   __vf OVCUAPI  MCDcuCols_add( cdPMatrix MA, ui ht, ui len, ui destCol, ui sourceCol );

void   __vf OVCUAPI  MCDcuRows_sub( cdPMatrix MA, ui ht, ui len, ui destRow, ui sourceRow );
void   __vf OVCUAPI  MCDcuCols_sub( cdPMatrix MA, ui ht, ui len, ui destCol, ui sourceCol );

void   __vf OVCUAPI  MCDcuRows_Cadd( cdPMatrix MA, ui ht, ui len, ui destRow, ui sourceRow, dComplex C );
void   __vf OVCUAPI  MCDcuCols_Cadd( cdPMatrix MA, ui ht, ui len, ui destCol, ui sourceCol, dComplex C );

void   __vf OVCUAPI  MCDcuRows_lincomb( cdPMatrix MA, ui ht, ui len, ui destRow,  dComplex  destC,
                                                                 ui srceRow,  dComplex  srceC );
void   __vf OVCUAPI  MCDcuCols_lincomb( cdPMatrix MA, ui ht, ui len, ui destCol,  dComplex  destC,
                                                                 ui srceCol,  dComplex  srceC );


/**************  Transposing and rotating a matrix **********************/

void  __vf OVCUAPI  MCDcutranspose( cdPMatrix MTr, cdPMatrix MA, ui htTr, ui lenTr );
void  __vf OVCUAPI  MCDcuhermconj( cdPMatrix MHConj, cdPMatrix MA, ui htTr, ui lenTr );
void  __vf OVCUAPI  MCDcurotate90(  cdPMatrix MRot, cdPMatrix MA, ui htRot, ui lenRot );
#define     MCDcurotate180( MRot, MA, htRot, lenRot ) VCDcu_rev( MRot, MA, (htRot)*(lenRot) )
void  __vf OVCUAPI  MCDcurotate270( cdPMatrix MRot, cdPMatrix MA, ui htRot, ui lenRot );


/************************ Matrix Arithmetics *************************/

#define MCDcuaddM( MC, MA, MB, htA, lenA )      VCDcu_addV( MC, MA, MB, (htA)*(lenA) )
void __vf OVCUAPI  MCDcuaddMT( cdPMatrix MC, cdPMatrix MA, cdPMatrix MB, ui htA, ui lenA );
#define MCDcusubM( MC, MA, MB, htA, lenA )      VCDcu_subV( MC, MA, MB, (htA)*(lenA) )
void __vf OVCUAPI  MCDcusubMT( cdPMatrix MC, cdPMatrix MA, cdPMatrix MB, ui htA, ui lenA );
void __vf OVCUAPI  MCDcusubrMT( cdPMatrix MC, cdPMatrix MA, cdPMatrix MB, ui htA, ui lenA );
#define MCDcumulC( MB, MA, htA, lenA, C )       VCDcu_mulC( MB, MA, (htA)*(lenA), C )
#define MCDcudivC( MB, MA, htA, lenA, C )       VCDcu_divC( MB, MA, (htA)*(lenA), C )
#define MCDcumulReC( MB, MA, htA, lenA, CRe )   VCDcu_mulReC( MB, MA, (htA)*(lenA), CRe )
#define MCDcudivReC( MB, MA, htA, lenA, CRe )   VCDcu_divReC( MB, MA, (htA)*(lenA), CRe )
#define MCDculincomb( MC, MA, MB, htA, lenA, CA, CB ) VCDcu_lincomb( MC, MA, MB, (htA)*(lenA), CA, CB )
void  __vf OVCUAPI  MCDcumulV( cdVector Y, cdPMatrix MA, cdVector X, ui htA, ui lenA );
void  __vf OVCUAPI  MCDcuTmulV( cdVector Y, cdPMatrix MA, cdVector X, ui htA, ui lenA );
void  __vf OVCUAPI  VCDcumulM( cdVector Y, cdVector X, cdPMatrix MA, ui htA, ui lenA );
void  __vf OVCUAPI  VCDcumulMT( cdVector Y, cdVector X, cdPMatrix MA, ui htA, ui lenA );
void  __vf OVCUAPI  MCDcumulM( cdPMatrix MC, cdPMatrix MA, cdPMatrix MB, ui htA, ui lenA, ui lenB );
void  __vf OVCUAPI  MCDcumulMT( cdPMatrix MC, cdPMatrix MA, cdPMatrix MB, ui htA, ui lenA, ui htB );
void  __vf OVCUAPI  MCDcumulMH( cdPMatrix MC, cdPMatrix MA, cdPMatrix MB, ui htA, ui lenA, ui htB );
void  __vf OVCUAPI  MCDcuTmulM( cdPMatrix MC, cdPMatrix MA, cdPMatrix MB, ui htA, ui lenA, ui lenB );
void  __vf OVCUAPI  MCDcuHmulM( cdPMatrix MC, cdPMatrix MA, cdPMatrix MB, ui htA, ui lenA, ui lenB );
void  __vf OVCUAPI  MCDcuTmulMT( cdPMatrix MC, cdPMatrix MA, cdPMatrix MB, ui htA, ui lenA, ui htB );
void  __vf OVCUAPI  MCDcuTmulMH( cdPMatrix MC, cdPMatrix MA, cdPMatrix MB, ui htA, ui lenA, ui htB );
void  __vf OVCUAPI  MCDdiacumulM( cdPMatrix MC, cdPMatrix MADia, cdPMatrix MB, ui htB, ui lenB );
void  __vf OVCUAPI  MCDdiacumulMT( cdPMatrix MC, cdPMatrix MADia, cdPMatrix MB, ui htB, ui lenB );
void  __vf OVCUAPI  MCDcumulMdia( cdPMatrix MC, cdPMatrix MA, cdPMatrix MBDia, ui htA, ui lenA );
void  __vf OVCUAPI  MCDcuTmulMdia( cdPMatrix MC, cdPMatrix MA, cdPMatrix MBDia, ui htA, ui lenA );


/*************  Two-Dimensional Fourier-Transform Methods *****************/

void  __vf OVCUAPI  MCDcuFFT( cdPMatrix MY, cdPMatrix MX, ui ht, ui len, int dir );
void  __vf OVCUAPI  MCDcufilter( cdPMatrix MY, cdPMatrix MX, cdPMatrix MFlt, ui ht, ui len );
void  __vf OVCUAPI  MCDcuRows_FFT( cdPMatrix MY, cdPMatrix MX, ui ht, ui len, int dir );
void  __vf OVCUAPI  MCDcuCols_FFT( cdPMatrix MY, cdPMatrix MX, ui ht, ui len, int dir );

#ifdef __cplusplus
}  // end of extern "C"
#endif
#endif /* __CUDAMCDSTD_H */
