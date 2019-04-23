/*  cudaMFstd.h

  matrix management functions:
  manipulations on matrices of data type "float"
  (single-precision real numbers)

  This file declares the functions with the name variants 
	cudaMF_func		(working on matrices in device memory, input type fMatrix, scalar parameters reside on host and are passed by value)
	cusdMF_func		(as cudaMF_func except scalar parameters reside on device and are passed by address)
	cudaMFfunc		(as cudaMF_func, but input type fPMatrix = fVector = pointer to matrix element[0][0])
	cusdMFfunc		(as cusdMF_func, but input type fPMatrix = fVector = pointer to matrix element[0][0])
	MFcu_func		(working on matrices in host memory, input type fMatrix, scalar parameters on host and passed by value)
	MFcufunc		(as MFcu_func, but input type fPMatrix = fVector = pointer to matrix element[0][0])
  where func is the respective function.

  Copyright (c) 1996-2017 by OptiCode - Dr. Martin Sander Software Dev.
  All Rights Reserved.
*/

#if !defined( __CUDAMFSTD_H )
#define __CUDAMFSTD_H
#if !defined( __CUDAMATLIB_H )
#include <cudaMatLib.h>
#endif
#if !defined( __CUDAVFSTD_H )
#include <cudaVFstd.h>
#endif
#if !defined( __CUDAVFMATH_H )
#include <cudaVFmath.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif

/**** Generation of matrices on device memory and on pinned host memory *******************/

fMatrix  __vf cudaMF_matrix( ui ht, ui len );   /* allocates a vector on device memory */
fMatrix  __vf cudaMF_matrix0( ui ht, ui len );
 /* The following functions allocate device-accessible, "pinned" memory on the host.
	This memory is mapped onto the device memory space. The resulting device address is returned.
	The matrix can be accessed either by its host address "hostPtr" e.g., MF_equ1( hostPtr, ht, len );
	or by its device address , e.g., cudaMF_equ1( devicePtr, ht, len );                             */
fMatrix  __vf cudaMF_pinnedMatrix(  fMatrix *hostPtr, ui ht, ui len ); 
fMatrix  __vf cudaMF_pinnedMatrix0( fMatrix *hostPtr, ui ht, ui len );

/*************************************************************************
 * Declarations of the functions written without underbar in the prefix: *
 *	cudaMFfunc  (input type 
                   fPMatrix = fVector = pointer to matrix element[0][0])
 *	cusdMFfunc  (input type 
                   fPMatrix = fVector = pointer to matrix element[0][0])
 *************************************************************************/

void    __vcuf OVCUAPI  cudaMFsetElement( fPMatrix X, ui ht, ui len, ui m, ui n, float C );
void    __vcuf OVCUAPI  cusdMFsetElement( fPMatrix X, ui ht, ui len, ui m, ui n, float *d_C );
void    __vcuf OVCUAPI  cudaMFgetElement( float *h_y, fPMatrix X, ui ht, ui len, ui m, ui n );
void    __vcuf OVCUAPI  cusdMFgetElement( float *d_y, fPMatrix X, ui ht, ui len, ui m, ui n );
float * __vcuf OVCUAPI  cudaMFPelement( fPMatrix X, ui ht, ui len, ui m, ui n );
float   __vcuf OVCUAPI  cudaMFelement( fPMatrix X, ui ht, ui len, ui m, ui n );

#define cudaMFequ0( MA, ht, len )       cudaVF_equ0( MA, (ht)*(len) )
overror_t   __vcuf OVCUAPI  cudaMFequ1( fPMatrix MA, ui len );  /* identity matrix */
overror_t   __vcuf OVCUAPI  cudaMFequm1( fPMatrix MA, ui len );  /* neg. identity matrix */
overror_t   __vcuf OVCUAPI  cudaMFouterprod( fPMatrix MA, fVector X,  fVector Y, ui ht, ui len );

overror_t   __vcuf OVCUAPI  cudaMFRow_equ0( fPMatrix MA, ui ht, ui len, ui iRow );
overror_t   __vcuf OVCUAPI  cudaMFCol_equ0( fPMatrix MA, ui ht, ui len, ui iCol );
overror_t   __vcuf OVCUAPI  cudaMFDia_equ0( fPMatrix MA, ui len );

overror_t   __vcuf OVCUAPI  cudaMFRow_equC( fPMatrix MA, ui ht, ui len, ui iRow, float C );
overror_t   __vcuf OVCUAPI  cudaMFCol_equC( fPMatrix MA, ui ht, ui len, ui iCol, float C );
overror_t   __vcuf OVCUAPI  cudaMFDia_equC( fPMatrix MA, ui len, float C );
overror_t   __vcuf OVCUAPI  cusdMFRow_equC( fPMatrix MA, ui ht, ui len, ui iRow, float *d_C);
overror_t   __vcuf OVCUAPI  cusdMFCol_equC( fPMatrix MA, ui ht, ui len, ui iCol, float *d_C);
overror_t   __vcuf OVCUAPI  cusdMFDia_equC( fPMatrix MA, ui len, float *d_C);

overror_t   __vcuf OVCUAPI  cudaMFRow_equV( fPMatrix MA, ui ht, ui len, ui iRow, fVector X );
overror_t   __vcuf OVCUAPI  cudaMFCol_equV( fPMatrix MA, ui ht, ui len, ui iCol, fVector X );
overror_t   __vcuf OVCUAPI  cudaMFDia_equV( fPMatrix MA, ui len, fVector X );

overror_t   __vcuf OVCUAPI  cudaMFTrd_equM( fPMatrix MA, fPMatrix MTrd, ui len );
overror_t   __vcuf OVCUAPI  cudaMFTrd_extract( fPMatrix MTrd, fPMatrix MA, ui len );

#define cudaMFequM( MB, MA, ht, len )      cudaVF_equV( MB, MA, (ht)*(len) )
#define cudaMFequMhost( MB, MA, ht, len )  cudaVF_equVhost( MB, MA, (ht)*(len) )
#define MFequMdevice( MB, MA, ht, len )    VF_equVdevice( MB, MA, (ht)*(len) )
#define cudaMFneg( MB, MA, ht, len )       cudaVF_neg( MB, MA, (ht)*(len) )
overror_t   __vcuf OVCUAPI  cudaMFUequL( fPMatrix MA, ui len );
overror_t   __vcuf OVCUAPI  cudaMFLequU( fPMatrix MA, ui len );

overror_t   __vcuf OVCUAPI  cudaMFHann( fPMatrix MA, ui ht, ui len );
#define cudaMFHanning cudaMFHann
overror_t   __vcuf OVCUAPI  cudaMFParzen(  fPMatrix MA, ui ht, ui len );
overror_t   __vcuf OVCUAPI  cudaMFWelch(   fPMatrix MA, ui ht, ui len );

/********  Extracting a submatrix and copying a submatrix back  *********/

overror_t  __vcuf OVCUAPI  cudaMFsubmatrix( fPMatrix MSub, ui subHt,  ui subLen,
                          fPMatrix MSrce, ui srceHt,  ui srceLen,
                          ui firstRowInCol,  ui sampInCol,
                          ui firstColInRow,  ui sampInRow );

overror_t  __vcuf OVCUAPI  cudaMFsubmatrix_equM( fPMatrix MDest, ui destHt, ui destLen,
                               ui firstRowInCol,  ui sampInCol,
                               ui firstColInRow,  ui sampInRow,
                               fPMatrix MSrce, ui srceHt, ui srceLen );

overror_t  __vcuf OVCUAPI  cudaMFequMblock(  fPMatrix MSub, ui subHt, ui subLen,
                          fPMatrix MSrce, ui srceHt,  ui srceLen,
                          ui firstRowInCol,  ui firstColInRow );

overror_t  __vcuf OVCUAPI  cudaMFblock_equM( fPMatrix MDest, ui destHt, ui destLen,
                          ui firstRowInCol,  ui firstColInRow,
                          fPMatrix MSrce, ui srceHt, ui srceLen );

overror_t  __vcuf OVCUAPI  cudaMFequMblockT( fPMatrix MSub, ui subHt, ui subLen,
                          fPMatrix MSrce, ui srceHt, ui srceLen,
                          ui firstRowInCol,  ui firstColInRow );

overror_t  __vcuf OVCUAPI  cudaMFblock_equMT( fPMatrix MDest, ui destHt, ui destLen,
                          ui firstRowInCol,  ui firstColInRow,
                          fPMatrix MSrce, ui srceHt, ui srceLen );


/*****   Extracting a single row or a single column or the diagonal  *****
 *       and storing it into a vector                                    */

overror_t __vcuf OVCUAPI  cudaMFRow_extract( fVector Y, fPMatrix MA, ui ht, ui len, ui iRow );
overror_t __vcuf OVCUAPI  cudaMFCol_extract( fVector Y, fPMatrix MA, ui ht, ui len, ui iCol );
overror_t __vcuf OVCUAPI  cudaMFDia_extract( fVector Y, fPMatrix MA, ui len );

/**********  Deleting or inserting a row or a column *****************/

overror_t __vcuf OVCUAPI  cudaMFRow_delete( fPMatrix MB, fPMatrix MA, ui htA, ui lenA, ui iRow );
overror_t __vcuf OVCUAPI  cudaMFCol_delete( fPMatrix MB, fPMatrix MA, ui htA, ui lenA, ui iCol );
overror_t __vcuf OVCUAPI  cudaMFRow_insert( fPMatrix MB, fPMatrix MA, ui htB, ui lenB, ui iRow, fVector X );
overror_t __vcuf OVCUAPI  cudaMFCol_insert( fPMatrix MB, fPMatrix MA, ui htB, ui lenB, ui iCol, fVector X );


/*****************    Basic arithmetic operations ***********************
     performed on one single row,  or one single column of any matrix,
     or on the diagonal of a square matrix                              */

overror_t   __vcuf OVCUAPI  cudaMFRow_neg( fPMatrix MX, ui ht, ui len, ui iRow );
overror_t   __vcuf OVCUAPI  cudaMFCol_neg( fPMatrix MX, ui ht, ui len, ui iCol );

overror_t   __vcuf OVCUAPI  cudaMFRow_addC( fPMatrix MA, ui ht, ui len, ui iRow, float C );
overror_t   __vcuf OVCUAPI  cudaMFCol_addC( fPMatrix MA, ui ht, ui len, ui iCol, float C );
overror_t   __vcuf OVCUAPI  cudaMFDia_addC( fPMatrix MA, ui len, float C );
overror_t   __vcuf OVCUAPI  cusdMFRow_addC( fPMatrix MA, ui ht, ui len, ui iRow, float *d_C);
overror_t   __vcuf OVCUAPI  cusdMFCol_addC( fPMatrix MA, ui ht, ui len, ui iCol, float *d_C);
overror_t   __vcuf OVCUAPI  cusdMFDia_addC( fPMatrix MA, ui len, float *d_C);

overror_t   __vcuf OVCUAPI  cudaMFRow_subC( fPMatrix MA, ui ht, ui len, ui iRow, float C );
overror_t   __vcuf OVCUAPI  cudaMFCol_subC( fPMatrix MA, ui ht, ui len, ui iCol, float C );
overror_t   __vcuf OVCUAPI  cudaMFDia_subC( fPMatrix MA, ui len, float C );
overror_t   __vcuf OVCUAPI  cusdMFRow_subC( fPMatrix MA, ui ht, ui len, ui iRow, float *d_C);
overror_t   __vcuf OVCUAPI  cusdMFCol_subC( fPMatrix MA, ui ht, ui len, ui iCol, float *d_C);
overror_t   __vcuf OVCUAPI  cusdMFDia_subC( fPMatrix MA, ui len, float *d_C);

overror_t   __vcuf OVCUAPI  cudaMFRow_addV( fPMatrix MA, ui ht, ui len, ui iRow, fVector X );
overror_t   __vcuf OVCUAPI  cudaMFCol_addV( fPMatrix MA, ui ht, ui len, ui iCol, fVector X );
overror_t   __vcuf OVCUAPI  cudaMFDia_addV( fPMatrix MA, ui len, fVector X );

overror_t   __vcuf OVCUAPI  cudaMFRow_subV( fPMatrix MA, ui ht, ui len, ui iRow, fVector X );
overror_t   __vcuf OVCUAPI  cudaMFCol_subV( fPMatrix MA, ui ht, ui len, ui iCol, fVector X );
overror_t   __vcuf OVCUAPI  cudaMFDia_subV( fPMatrix MA, ui len, fVector X );

overror_t   __vcuf OVCUAPI  cudaMFRow_subrC( fPMatrix MA, ui ht, ui len, ui iRow, float C );
overror_t   __vcuf OVCUAPI  cudaMFCol_subrC( fPMatrix MA, ui ht, ui len, ui iCol, float C );
overror_t   __vcuf OVCUAPI  cudaMFDia_subrC( fPMatrix MA, ui len, float C );
overror_t   __vcuf OVCUAPI  cusdMFRow_subrC( fPMatrix MA, ui ht, ui len, ui iRow, float *d_C);
overror_t   __vcuf OVCUAPI  cusdMFCol_subrC( fPMatrix MA, ui ht, ui len, ui iCol, float *d_C);
overror_t   __vcuf OVCUAPI  cusdMFDia_subrC( fPMatrix MA, ui len, float *d_C);

overror_t   __vcuf OVCUAPI  cudaMFRow_subrV( fPMatrix MA, ui ht, ui len, ui iRow, fVector X );
overror_t   __vcuf OVCUAPI  cudaMFCol_subrV( fPMatrix MA, ui ht, ui len, ui iCol, fVector X );
overror_t   __vcuf OVCUAPI  cudaMFDia_subrV( fPMatrix MA, ui len, fVector X );

overror_t   __vcuf OVCUAPI  cudaMFRow_mulC( fPMatrix MA, ui ht, ui len, ui iRow, float C );
overror_t   __vcuf OVCUAPI  cudaMFCol_mulC( fPMatrix MA, ui ht, ui len, ui iCol, float C );
overror_t   __vcuf OVCUAPI  cudaMFDia_mulC( fPMatrix MA, ui len, float C );
overror_t   __vcuf OVCUAPI  cusdMFRow_mulC( fPMatrix MA, ui ht, ui len, ui iRow, float *d_C);
overror_t   __vcuf OVCUAPI  cusdMFCol_mulC( fPMatrix MA, ui ht, ui len, ui iCol, float *d_C);
overror_t   __vcuf OVCUAPI  cusdMFDia_mulC( fPMatrix MA, ui len, float *d_C);

overror_t   __vcuf OVCUAPI  cudaMFRow_mulV( fPMatrix MA, ui ht, ui len, ui iRow, fVector X );
overror_t   __vcuf OVCUAPI  cudaMFCol_mulV( fPMatrix MA, ui ht, ui len, ui iCol, fVector X );
overror_t   __vcuf OVCUAPI  cudaMFDia_mulV( fPMatrix MA, ui len, fVector X );

overror_t   __vcuf OVCUAPI  cudaMFRow_divC( fPMatrix MA, ui ht, ui len, ui iRow, float C );
overror_t   __vcuf OVCUAPI  cudaMFCol_divC( fPMatrix MA, ui ht, ui len, ui iCol, float C );
overror_t   __vcuf OVCUAPI  cudaMFDia_divC( fPMatrix MA, ui len, float C );
overror_t   __vcuf OVCUAPI  cusdMFRow_divC( fPMatrix MA, ui ht, ui len, ui iRow, float *d_C);
overror_t   __vcuf OVCUAPI  cusdMFCol_divC( fPMatrix MA, ui ht, ui len, ui iCol, float *d_C);
overror_t   __vcuf OVCUAPI  cusdMFDia_divC( fPMatrix MA, ui len, float *d_C);

overror_t   __vcuf OVCUAPI  cudaMFRow_divV( fPMatrix MA, ui ht, ui len, ui iRow, fVector X );
overror_t   __vcuf OVCUAPI  cudaMFCol_divV( fPMatrix MA, ui ht, ui len, ui iCol, fVector X );
overror_t   __vcuf OVCUAPI  cudaMFDia_divV( fPMatrix MA, ui len, fVector X );

overror_t   __vcuf OVCUAPI  cudaMFRow_divrC( fPMatrix MA, ui ht, ui len, ui iRow, float C );
overror_t   __vcuf OVCUAPI  cudaMFCol_divrC( fPMatrix MA, ui ht, ui len, ui iCol, float C );
overror_t   __vcuf OVCUAPI  cudaMFDia_divrC( fPMatrix MA, ui len, float C );
overror_t   __vcuf OVCUAPI  cusdMFRow_divrC( fPMatrix MA, ui ht, ui len, ui iRow, float *d_C);
overror_t   __vcuf OVCUAPI  cusdMFCol_divrC( fPMatrix MA, ui ht, ui len, ui iCol, float *d_C);
overror_t   __vcuf OVCUAPI  cusdMFDia_divrC( fPMatrix MA, ui len, float *d_C);

overror_t   __vcuf OVCUAPI  cudaMFRow_divrV( fPMatrix MA, ui ht, ui len, ui iRow, fVector X );
overror_t   __vcuf OVCUAPI  cudaMFCol_divrV( fPMatrix MA, ui ht, ui len, ui iCol, fVector X );
overror_t   __vcuf OVCUAPI  cudaMFDia_divrV( fPMatrix MA, ui len, fVector X );


/******  One-dimensional vector operations **********************
         performed along all rows or all columns simultaneously,
         or along the diagonal of a square matrix                */

overror_t   __vcuf OVCUAPI  cudaMFRows_max( fVector Y, fPMatrix MA, ui ht, ui len );
overror_t   __vcuf OVCUAPI  cudaMFCols_max( fVector Y, fPMatrix MA, ui ht, ui len );
overror_t   __vcuf OVCUAPI  cudaMFDia_max(  float *h_RetVal, fPMatrix MA, ui len );
overror_t   __vcuf OVCUAPI  cusdMFDia_max(  float *d_RetVal, fPMatrix MA, ui len );
overror_t   __vcuf OVCUAPI  cudaMFRows_min( fVector Y, fPMatrix MA, ui ht, ui len );
overror_t   __vcuf OVCUAPI  cudaMFCols_min( fVector Y, fPMatrix MA, ui ht, ui len );
overror_t   __vcuf OVCUAPI  cudaMFDia_min(  float *h_RetVal, fPMatrix MA, ui len );
overror_t   __vcuf OVCUAPI  cusdMFDia_min(  float *d_RetVal, fPMatrix MA, ui len );

overror_t   __vcuf OVCUAPI  cudaMFRows_absmax( fVector Y, fPMatrix MA, ui ht, ui len );
overror_t   __vcuf OVCUAPI  cudaMFCols_absmax( fVector Y, fPMatrix MA, ui ht, ui len );
overror_t   __vcuf OVCUAPI  cudaMFDia_absmax(  float *h_RetVal, fPMatrix MA, ui len );
overror_t   __vcuf OVCUAPI  cusdMFDia_absmax(  float *d_RetVal, fPMatrix MA, ui len );
overror_t   __vcuf OVCUAPI  cudaMFRows_absmin( fVector Y, fPMatrix MA, ui ht, ui len );
overror_t   __vcuf OVCUAPI  cudaMFCols_absmin( fVector Y, fPMatrix MA, ui ht, ui len );
overror_t   __vcuf OVCUAPI  cudaMFDia_absmin(  float *h_RetVal, fPMatrix MA, ui len );
overror_t   __vcuf OVCUAPI  cusdMFDia_absmin(  float *d_RetVal, fPMatrix MA, ui len );

overror_t   __vcuf OVCUAPI  cudaMFRows_sum( fVector Y, fPMatrix MA, ui ht, ui len );
overror_t   __vcuf OVCUAPI  cudaMFCols_sum( fVector Y, fPMatrix MA, ui ht, ui len );
overror_t   __vcuf OVCUAPI  cudaMFDia_sum(  float *h_RetVal, fPMatrix MA, ui len );
overror_t   __vcuf OVCUAPI  cusdMFDia_sum(  float *d_RetVal, fPMatrix MA, ui len );
overror_t   __vcuf OVCUAPI  cudaMFRows_ssq( fVector Y, fPMatrix MA, ui ht, ui len );
overror_t   __vcuf OVCUAPI  cudaMFCols_ssq( fVector Y, fPMatrix MA, ui ht, ui len );
overror_t   __vcuf OVCUAPI  cudaMFDia_ssq(  float *h_RetVal, fPMatrix MA, ui len );
overror_t   __vcuf OVCUAPI  cusdMFDia_ssq(  float *d_RetVal, fPMatrix MA, ui len );
overror_t   __vcuf OVCUAPI  cudaMFRows_prod(fVector Y, fPMatrix MA, ui ht, ui len );
overror_t   __vcuf OVCUAPI  cudaMFCols_prod(fVector Y, fPMatrix MA, ui ht, ui len );
overror_t   __vcuf OVCUAPI  cudaMFDia_prod( float *h_RetVal, fPMatrix MA, ui len );
overror_t   __vcuf OVCUAPI  cusdMFDia_prod( float *d_RetVal, fPMatrix MA, ui len );

overror_t  __vcuf OVCUAPI  cudaMFRows_runsum( fPMatrix MA, ui ht, ui len );
overror_t  __vcuf OVCUAPI  cudaMFCols_runsum( fPMatrix MA, ui ht, ui len );
overror_t  __vcuf OVCUAPI  cudaMFRows_runprod( fPMatrix MA, ui ht, ui len );
overror_t  __vcuf OVCUAPI  cudaMFCols_runprod( fPMatrix MA, ui ht, ui len );

overror_t  __vcuf OVCUAPI  cudaMFRows_rotate( fPMatrix MA, ui ht, ui len, ssize_t pos );
overror_t  __vcuf OVCUAPI  cudaMFCols_rotate( fPMatrix MA, ui ht, ui len, ssize_t pos );
overror_t  __vcuf OVCUAPI  cudaMFRows_rotate_buf( fPMatrix MA, ui ht, ui len, ssize_t pos, fPMatrix MBuf );
overror_t  __vcuf OVCUAPI  cudaMFCols_rotate_buf( fPMatrix MA, ui ht, ui len, ssize_t pos, fPMatrix MBuf );
overror_t  __vcuf OVCUAPI  cudaMFRows_reflect( fPMatrix MA, ui ht, ui len );
overror_t  __vcuf OVCUAPI  cudaMFCols_reflect( fPMatrix MA, ui ht, ui len );
overror_t  __vcuf OVCUAPI  cudaMFRows_rev( fPMatrix MA, ui ht, ui len );
overror_t  __vcuf OVCUAPI  cudaMFCols_rev( fPMatrix MA, ui ht, ui len );
overror_t  __vcuf OVCUAPI  cudaMFRows_distribution( uiPMatrix MAbund, fVector Limits, ui nBins, fPMatrix MX, ui ht, ui len, int mode );
overror_t  __vcuf OVCUAPI  cudaMFCols_distribution( uiPMatrix MAbund, fVector Limits, ui nBins, fPMatrix MX, ui ht, ui len, int mode );

/********  Operations involving two rows or two colums of one matrix  *****/

overror_t   __vcuf OVCUAPI  cudaMFRows_exchange( fPMatrix MA, ui ht, ui len, ui i1, ui i2 );
overror_t   __vcuf OVCUAPI  cudaMFCols_exchange( fPMatrix MA, ui ht, ui len, ui i1, ui i2 );

overror_t   __vcuf OVCUAPI  cudaMFRows_add( fPMatrix MA, ui ht, ui len, ui destRow, ui sourceRow );
overror_t   __vcuf OVCUAPI  cudaMFCols_add( fPMatrix MA, ui ht, ui len, ui destCol, ui sourceCol );

overror_t   __vcuf OVCUAPI  cudaMFRows_sub( fPMatrix MA, ui ht, ui len, ui destRow, ui sourceRow );
overror_t   __vcuf OVCUAPI  cudaMFCols_sub( fPMatrix MA, ui ht, ui len, ui destCol, ui sourceCol );

overror_t   __vcuf OVCUAPI  cudaMFRows_Cadd( fPMatrix MA, ui ht, ui len, ui destRow, ui sourceRow, float C );
overror_t   __vcuf OVCUAPI  cudaMFCols_Cadd( fPMatrix MA, ui ht, ui len, ui destCol, ui sourceCol, float C );
overror_t   __vcuf OVCUAPI  cusdMFRows_Cadd( fPMatrix MA, ui ht, ui len, ui destRow, ui sourceRow, float *d_C);
overror_t   __vcuf OVCUAPI  cusdMFCols_Cadd( fPMatrix MA, ui ht, ui len, ui destCol, ui sourceCol, float *d_C);

overror_t   __vcuf OVCUAPI  cudaMFRows_lincomb( fPMatrix MA, ui ht, ui len,
					ui destRow,  float  destC, ui srceRow,  float  srceC );
overror_t   __vcuf OVCUAPI  cudaMFCols_lincomb( fPMatrix MA, ui ht, ui len,
                              ui destCol,  float  destC, ui srceCol,  float  srceC );
overror_t   __vcuf OVCUAPI  cusdMFRows_lincomb( fPMatrix MA, ui ht, ui len,
					ui destRow,  float  *d_destC, ui srceRow,  float  *d_srceC );
overror_t   __vcuf OVCUAPI  cusdMFCols_lincomb( fPMatrix MA, ui ht, ui len,
                              ui destCol,  float  *d_destC, ui srceCol,  float  *d_srceC );


/*********************  Center of gravity *****************************/
overror_t __vcuf OVCUAPI  cudaMFcenterOfGravityInd( fComplex *h_Result, fPMatrix MA, ui ht, ui len );
overror_t __vcuf OVCUAPI  cudaMFcenterOfGravityV( fComplex *h_Result, fVector X, fVector Y, fPMatrix MA, ui ht, ui len );
overror_t __vcuf OVCUAPI  cusdMFcenterOfGravityInd( fComplex *d_Result, fPMatrix MA, ui ht, ui len );
overror_t __vcuf OVCUAPI  cusdMFcenterOfGravityV( fComplex *d_Result, fVector X, fVector Y, fPMatrix MA, ui ht, ui len );

/***************  Transposing and rotating a matrix **********************/

overror_t  __vcuf OVCUAPI  cudaMFtranspose( fPMatrix MTr, fPMatrix MA,  ui htTr, ui lenTr );
overror_t  __vcuf OVCUAPI  cudaMFrotate90(  fPMatrix MRot, fPMatrix MA, ui htRot, ui lenRot );
#define     cudaMFrotate180( MRot, MA, htRot, lenRot )  cudaVF_rev( MRot, MA, (htRot)*(lenRot) )
overror_t  __vcuf OVCUAPI  cudaMFrotate270( fPMatrix MRot, fPMatrix MA, ui htRot, ui lenRot );
overror_t  __vcuf OVCUAPI  cudaMFtranspose_buf( fPMatrix MTr, fPMatrix MA,  ui htTr, ui lenTr, fPMatrix MBuf );


/********************** Interpolation of Matrix elements **************/

overror_t __vcuf OVCUAPI  cudaMFpolyinterpol( fPMatrix MZ, fVector X, fVector Y, ui ht, ui len,
       fVector XTab, fVector YTab, fPMatrix MZTab, ui httab, ui lentab,
       unsigned degX, unsigned degY );
overror_t __vcuf OVCUAPI  cudaMFratinterpol( fPMatrix MZ, fVector X, fVector Y, ui ht, ui len,
       fVector XTab, fVector YTab, fPMatrix MZTab, ui httab, ui lentab,
       unsigned degX, unsigned degY );
overror_t __vcuf OVCUAPI  cudaMFnatCubSplineInterpol( fPMatrix MZ, fVector X, fVector Y, ui ht, ui len,
       fVector XTab, fVector YTab, fPMatrix MZTab, ui httab, ui lentab );


/************************ Matrix Arithmetics *************************/

#define cudaMFaddM( MC, MA, MB, htA, lenA )            cudaVF_addV( MC, MA, MB, (htA)*(lenA) )
overror_t __vcuf OVCUAPI  cudaMFaddMT( fPMatrix MC, fPMatrix MA, fPMatrix MB, ui htA, ui lenA );
#define cudaMFsubM( MC, MA, MB, htA, lenA )            cudaVF_subV( MC, MA, MB, (htA)*(lenA) )
overror_t __vcuf OVCUAPI  cudaMFsubMT( fPMatrix MC, fPMatrix MA, fPMatrix MB, ui htA, ui lenA );
overror_t __vcuf OVCUAPI  cudaMFsubrMT( fPMatrix MC, fPMatrix MA, fPMatrix MB, ui htA, ui lenA );
#define cudaMFmulC( MB, MA, htA, lenA, C )             cudaVF_mulC( MB, MA, (htA)*(lenA), C )
#define cusdMFmulC( MB, MA, htA, lenA, d_CPtr )        cusdVF_mulC( MB, MA, (htA)*(lenA), d_CPtr )
#define cudaMFdivC( MB, MA, htA, lenA, C )             cudaVF_divC( MB, MA, (htA)*(lenA), C )
#define cusdMFdivC( MB, MA, htA, lenA, d_CPtr )        cusdVF_divC( MB, MA, (htA)*(lenA), d_CPtr )
#define cudaMFsaddM( MC, MA, MB, htA, lenA, C )        cudaVFs_addV( MC, MA, MB, (htA)*(lenA), C )
overror_t __vcuf OVCUAPI  cudaMFsaddMT( fPMatrix MC, fPMatrix MA, fPMatrix MB, ui htA, ui lenA, float C );
#define cudaMFssubM( MC, MA, MB, htA, lenA, C )        cudaVFs_subV( MC, MA, MB, (htA)*(lenA), C )
overror_t __vcuf OVCUAPI  cudaMFssubMT( fPMatrix MC, fPMatrix MA, fPMatrix MB, ui htA, ui lenA, float C );
overror_t __vcuf OVCUAPI  cudaMFssubrMT( fPMatrix MC, fPMatrix MA, fPMatrix MB, ui htA, ui lenA, float C );
#define cusdMFsaddM( MC, MA, MB, htA, lenA, d_CPtr )   cusdVFs_addV( MC, MA, MB, (htA)*(lenA), d_CPtr )
overror_t __vcuf OVCUAPI  cusdMFsaddMT( fPMatrix MC, fPMatrix MA, fPMatrix MB, ui htA, ui lenA, float *d_CPtr );
#define cusdMFssubM( MC, MA, MB, htA, lenA, d_CPtr )   cusdVFs_subV( MC, MA, MB, (htA)*(lenA), d_CPtr )
overror_t __vcuf OVCUAPI  cusdMFssubMT( fPMatrix MC, fPMatrix MA, fPMatrix MB, ui htA, ui lenA, float *d_CPtr );
overror_t __vcuf OVCUAPI  cusdMFssubrMT( fPMatrix MC, fPMatrix MA, fPMatrix MB, ui htA, ui lenA, float *d_CPtr );
#define cudaMFlincomb( MC, MA, MB, htA, lenA, CA, CB ) cudaVF_lincomb( MC, MA, MB, (htA)*(lenA), CA, CB )
#define cusdMFlincomb( MC, MA, MB, htA, lenA, d_CAPtr, d_CBPtr ) cusdVF_lincomb( MC, MA, MB, (htA)*(lenA), d_CAPtr, d_CBPtr )
overror_t  __vcuf OVCUAPI  cudaMFmulV( fVector Y, fPMatrix MA, fVector X, ui htA, ui lenA );
overror_t  __vcuf OVCUAPI  cudaMFTmulV( fVector Y, fPMatrix MA, fVector X, ui htA, ui lenA );
overror_t  __vcuf OVCUAPI   cudaVFmulM( fVector Y, fVector X, fPMatrix MA, ui htA, ui lenA );
overror_t  __vcuf OVCUAPI   cudaVFmulMT( fVector Y, fVector X, fPMatrix MA, ui htA, ui lenA );
overror_t  __vcuf OVCUAPI  cudaMFmulM( fPMatrix MC, fPMatrix MA, fPMatrix MB, ui htA, ui lenA, ui lenB );
overror_t  __vcuf OVCUAPI  cudaMFmulMT( fPMatrix MC, fPMatrix MA, fPMatrix MB, ui htA, ui lenA, ui htB );
overror_t  __vcuf OVCUAPI  cudaMFTmulM( fPMatrix MC, fPMatrix MA, fPMatrix MB, ui htA, ui lenA, ui lenB );
overror_t  __vcuf OVCUAPI  cudaMFTmulMT( fPMatrix MC, fPMatrix MA, fPMatrix MB, ui htA, ui lenA, ui htB );
overror_t  __vcuf OVCUAPI  cudaMFdiamulM( fPMatrix MC, fPMatrix MADia, fPMatrix MB, ui htB, ui lenB );
overror_t  __vcuf OVCUAPI  cudaMFdiamulMT( fPMatrix MC, fPMatrix MADia, fPMatrix MB, ui htB, ui lenB );
overror_t  __vcuf OVCUAPI  cudaMFmulMdia( fPMatrix MC, fPMatrix MA, fPMatrix MBDia, ui htA, ui lenA );
overror_t  __vcuf OVCUAPI  cudaMFTmulMdia( fPMatrix MC, fPMatrix MA, fPMatrix MBDia, ui htA, ui lenA );


/*************  Matrix Fourier-Transform Methods *****************/

overror_t  __vcuf OVCUAPI   cudaMFFFT( fPMatrix MY, fPMatrix MX, ui ht, ui len, int dir );
overror_t  __vcuf OVCUAPI   cudaMFFFTtoC( cfPMatrix MY, fPMatrix MX, ui ht, ui len );
overror_t  __vcuf OVCUAPI   cudaMFconvolve( fPMatrix MY, fPMatrix MFlt, fPMatrix MX, fPMatrix MRsp, ui ht, ui len );
overror_t  __vcuf OVCUAPI   cudaMFdeconvolve( fPMatrix MY, fPMatrix MFlt, fPMatrix MX, fPMatrix MRsp, ui ht, ui len );
overror_t  __vcuf OVCUAPI   cudaMFfilter( fPMatrix MY, fPMatrix MX, fPMatrix MFlt, ui ht, ui len );
overror_t  __vcuf OVCUAPI   cudaMFautocorr( fPMatrix MACorr, fPMatrix MX, ui ht, ui len );
overror_t  __vcuf OVCUAPI   cudaMFxcorr( fPMatrix MXCorr, fPMatrix MX, fPMatrix MY, ui ht, ui len );
overror_t  __vcuf OVCUAPI   cudaMFspectrum( fPMatrix MSpec, ui htSpec, ui lenSpec, fPMatrix MX, ui htX, ui lenX, fPMatrix MWin );
overror_t  __vcuf OVCUAPI   cudaMFRows_FFT( fPMatrix MY, fPMatrix MX, ui ht, ui len, int dir );
overror_t  __vcuf OVCUAPI   cudaMFCols_FFT( fPMatrix MY, fPMatrix MX, ui ht, ui len, int dir );
overror_t  __vcuf OVCUAPI   cudaMFRows_FFTtoC( cfPMatrix MY, fPMatrix MX, ui ht, ui len );
overror_t  __vcuf OVCUAPI   cudaMFCols_FFTtoC( cfPMatrix MY, fPMatrix MX, ui ht, ui len );

/**************************  Input and Output  **************************
	The input/output functions involve memory transfers from device
	to host memory or vice versa. The generic cudaMF_input/output functions
	allocate their own host buffers, whereas the cudaMF_xxx_buf functions
	take a user-supplied buffer vector h_Wk (size must be >= ht*len )
	and are much more efficient.                                       */

#define cudaMFprint( MA, ht, len )  cudaMFfprint( stdout, MA, ht, len, 80 )
overror_t __vf cudaMFfprint( FILE *stream, fPMatrix MA, ui ht, ui len, unsigned linewidth );
overror_t __vf cudaMFcprint( fPMatrix MA, ui ht, ui len );
#define cudaMFprint_buf( MA, ht, len, h_Wk )  cudaMFfprint_buf( stdout, MA, ht, len, 80, h_Wk )
overror_t __vf cudaMFfprint_buf( FILE *stream, fPMatrix MA, ui ht, ui len, unsigned linewidth, fVector h_Wk );
overror_t __vf cudaMFcprint_buf( fPMatrix MA, ui ht, ui len, fVector h_Wk );
overror_t __vf cudaMFwrite( FILE *stream, fPMatrix X, ui ht, ui len  );
overror_t __vf cudaMFwrite_buf( FILE *stream, fPMatrix X, ui ht, ui len, fVector h_Wk );
#if !((defined __BORLANDC__) && (__BORLANDC__ < 0x710))
		/* modern compiler versions:  */
	overror_t __vf cudaMFread( fPMatrix X, ui ht, ui len, FILE *stream );
	overror_t __vf cudaMFread_buf( fPMatrix X, ui ht, ui len, FILE *stream, fVector h_Wk );
#else /* older Borland compiler versions need separate implementation */
	overror_t __vf cudaMFread1( fPMatrix X, ui ht, ui len, FILE *stream );
	overror_t __vf cudaMFread1_buf( fPMatrix X, ui ht, ui len, FILE *stream, fVector h_Wk );
	#define cudaMFread      cudaMFread1
	#define cudaMFread_buf  cudaMFread1_buf
#endif
#define cudaMFstore( str, MA, ht, len ) cudaVF_store( str, MA, (len)*(ht) )
#define cudaMFrecall( MA, ht, len, str) cudaVF_recall( MA, (len)*(ht), str)
#define cudaMFstore_buf( str, MA, ht, len, h_Wk ) cudaVF_store( str, MA, (len)*(ht), h_Wk )
#define cudaMFrecall_buf( MA, ht, len, str, h_Wk) cudaVF_recall( MA, (len)*(ht), str, h_Wk)

/***************************************************************************
    cudaMF_func	(working on matrices in device memory, input type fMatrix, 
	             scalar parameters reside on host and are passed by value)
    cusdMF_func	(as cudaMF_func except scalar parameters reside on device 
	             and are passed by address)                                 */


/***************************************************************************
 *  The following definitions are needed to access individual elements,    *
 *  and row pointers. As all addresses point to device memory, the usual   *
 *  mechanism of accessing elements, i.e., writing something like MA[m][n] *
 *  is not possible here!                                                  *
 *  Pro forma, the distinction between the data types fMatrix and          *
 *  fPMatrix is kept. However, in the present implementation, both of      *
 *  these types actually contain a pointer to the matrix element [0][0].   *
 *  For C++, inline functions ensure proper type checking at compile time, *
 *  while for plain-C, only a less safe type-cast is possible.             *
 ***************************************************************************/

#ifdef __cplusplus

/***  Addressing single elements of dynamically allocated matrices: ******/

inline void    cudaMF_setElement( fMatrix MA, ui ht, ui len, ui m, ui n, float C )
	{	cudaMFsetElement( (fPMatrix)(MA), ht, len, m, n, C );}
inline void    cusdMF_setElement( fMatrix MA, ui ht, ui len, ui m, ui n, float *d_C )
	{	cusdMFsetElement( (fPMatrix)(MA), ht, len, m, n, d_C );}
inline void    cudaMF_getElement( float *y, fMatrix MA, ui ht, ui len, ui m, ui n )
	{	cudaMFgetElement( y, (fPMatrix)(MA), ht, len, m, n );}
inline void    cusdMF_getElement( float *d_y, fMatrix MA, ui ht, ui len, ui m, ui n )
	{	cusdMFgetElement( d_y, (fPMatrix)(MA), ht, len, m, n );}
inline float * cudaMF_Pelement( fMatrix MA, ui ht, ui len, ui m, ui n )
	{	return cudaMFPelement( (fPMatrix)(MA), ht, len, m, n );}
inline float   cudaMF_element( fMatrix MA, ui ht, ui len, ui m, ui n )
{	return cudaMFelement( (fPMatrix)(MA), ht, len, m, n );}

 /****************  Initialization  ****************************************/

inline overror_t  cudaMF_equ0( fMatrix MA, ui ht, ui len )
	{	return cudaVF_equ0( (fPMatrix)MA, (ht)*(len) ); }
inline overror_t  cudaMF_equ1( fMatrix MA, ui len )
	{	return cudaMFequ1( (fPMatrix)(MA), len );} /* identity matrix */
inline overror_t  cudaMF_equm1( fMatrix MA, ui len )
	{	return cudaMFequm1( (fPMatrix)(MA), len );} /* neg. identity matrix */

inline overror_t  cudaMF_randomLC( fMatrix MA, ui ht, ui len, long seed, float MinVal, float MaxVal, V_RANDOMLCSTATE *h_state )
	{	return cudaVF_randomLC( (fPMatrix)(MA), (ht)*(len), seed, MinVal, MaxVal, h_state );}
inline overror_t  cudaMF_random( fMatrix MA, ui ht, ui len, long seed, float MinVal, float MaxVal )
	{	return cudaVF_random( (fPMatrix)(MA), (ht)*(len), seed, MinVal, MaxVal );}
inline overror_t  cusdMF_randomLC( fMatrix MA, ui ht, ui len, long seed, float *d_MinVal, float *d_MaxVal, V_RANDOMLCSTATE *h_state )
	{	return cusdVF_randomLC( (fPMatrix)(MA), (ht)*(len), seed, d_MinVal, d_MaxVal, h_state );}
inline overror_t  cusdMF_random( fMatrix MA, ui ht, ui len, long seed, float *d_MinVal, float *d_MaxVal )
	{	return cusdVF_random( (fPMatrix)(MA), (ht)*(len), seed, d_MinVal, d_MaxVal );}
inline overror_t  cudaMF_outerprod( fMatrix MA, fVector X,  fVector Y, ui ht, ui len )
{	return cudaMFouterprod( (fPMatrix)(MA), X, Y, ht, len );}

inline overror_t  cudaMF_Row_equ0( fMatrix MA, ui ht, ui len, ui iRow )
	{	return cudaMFRow_equ0( (fPMatrix)MA, ht, len, iRow );}
inline overror_t  cudaMF_Col_equ0( fMatrix MA, ui ht, ui len, ui iRow )
	{	return cudaMFCol_equ0( (fPMatrix)MA, ht, len, iRow );}
inline overror_t  cudaMF_Dia_equ0( fMatrix MA, ui len )
	{	return cudaMFDia_equ0( (fPMatrix)(MA), len );}

inline overror_t  cudaMF_Row_equC( fMatrix MA, ui ht, ui len, ui iRow, float C )
	{	return cudaMFRow_equC( (fPMatrix)MA, ht, len, iRow, C );}
inline overror_t  cudaMF_Col_equC( fMatrix MA, ui ht, ui len, ui iRow, float C )
	{	return cudaMFCol_equC( (fPMatrix)MA, ht, len, iRow, C );}
inline overror_t  cudaMF_Dia_equC( fMatrix MA, ui len, float C )
	{	return cudaMFDia_equC( (fPMatrix)(MA), len, C );}

inline overror_t  cusdMF_Row_equC( fMatrix MA, ui ht, ui len, ui iRow, float *d_C )
	{	return cusdMFRow_equC( (fPMatrix)MA, ht, len, iRow, d_C );}
inline overror_t  cusdMF_Col_equC( fMatrix MA, ui ht, ui len, ui iRow, float *d_C )
	{	return cusdMFCol_equC( (fPMatrix)MA, ht, len, iRow, d_C );}
inline overror_t  cusdMF_Dia_equC( fMatrix MA, ui len, float *d_C )
	{	return cusdMFDia_equC( (fPMatrix)(MA), len, d_C );}

inline overror_t  cudaMF_Row_equV( fMatrix MA, ui ht, ui len, ui iRow, fVector X )
	{	return cudaMFRow_equV( (fPMatrix)MA, ht, len, iRow, X );}
inline overror_t  cudaMF_Col_equV( fMatrix MA, ui ht, ui len, ui iRow, fVector X )
	{	return cudaMFCol_equV( (fPMatrix)MA, ht, len, iRow, X );}
inline overror_t  cudaMF_Dia_equV( fMatrix MA, ui len, fVector X )
	{	return cudaMFDia_equV( (fPMatrix)(MA), len, X );}

inline overror_t  cudaMF_Trd_equM( fMatrix MA, fMatrix MTrd, ui len )
	{	return cudaMFTrd_equM( (fPMatrix)(MA), (fPMatrix)(MTrd), len );}
inline overror_t  cudaMF_Trd_extract( fMatrix MTrd, fMatrix MA, ui len )
	{	return cudaMFTrd_extract( (fPMatrix)(MTrd), (fPMatrix)(MA), len );}

inline overror_t cudaMF_equM( fMatrix MB, fMatrix MA, ui ht, ui len )
	{	return cudaVF_equV( (fPMatrix)MB, (fPMatrix)MA, (ht)*(len) );}
inline overror_t cudaMF_equMhost( fMatrix d_MB, fMatrix h_MA, ui ht, ui len )
	{	return cudaVF_equVhost( (fPMatrix)d_MB, (h_MA)[0], (ht)*(len) );}
inline overror_t MF_equMdevice( fMatrix h_MB, fMatrix d_MA, ui ht, ui len )
	{	return VF_equVdevice( h_MB[0], (fPMatrix)d_MA, (ht)*(len) );}
inline overror_t cudaMF_neg( fMatrix MB, fMatrix MA, ui ht, ui len )
	{	return cudaVF_neg( (fPMatrix)(MB), (fPMatrix)(MA), (ht)*(len) );}
inline overror_t  cudaMF_UequL( fMatrix MA, ui len )
	{	return cudaMFUequL( (fPMatrix)(MA), len );}
inline overror_t  cudaMF_LequU( fMatrix MA, ui len )
	{	return cudaMFLequU( (fPMatrix)(MA), len );}

            /* data-type conversions:  */
inline overror_t cudaM_DtoF( fMatrix MF, dMatrix MD, ui ht, ui len )
	{	return cudaV_DtoF( (fPMatrix)(MF), (dPMatrix)(MD), (ht)*(len) );}

            /* suitable windows for MF_spectrum: */
inline overror_t cudaMF_Hann( fMatrix MA, ui ht, ui len )
	{	return cudaMFHann( (fPMatrix)(MA), ht, len );}
#define cudaMFHanning cudaMFHann
inline overror_t cudaMF_Parzen( fMatrix MA, ui ht, ui len )
	{	return cudaMFParzen( (fPMatrix)(MA), ht, len );}
inline overror_t cudaMF_Welch( fMatrix MA, ui ht, ui len )
	{	return cudaMFWelch( (fPMatrix)(MA), ht, len );}

/********  Extracting a submatrix and copying a submatrix back  *********/

inline overror_t cudaMF_submatrix( fMatrix MSub, ui subHt, ui subLen, fMatrix MSrce, ui srceHt, ui srceLen,
                      ui firstRowInCol, ui sampInCol, ui firstColInRow, ui sampInRow )
	{	return cudaMFsubmatrix(  (fPMatrix)(MSub), subHt, subLen,
		                         (fPMatrix)(MSrce), srceHt, srceLen,
								 firstRowInCol, sampInCol, firstColInRow, sampInRow ); }

inline overror_t cudaMF_submatrix_equM( fMatrix MDest, ui destHt, ui destLen,
                           ui firstRowInCol, ui sampInCol, ui firstColInRow, ui sampInRow,
                           fMatrix MSrce, ui srceHt, ui srceLen )
	{	return cudaMFsubmatrix_equM(  (fPMatrix)(MDest), destHt, destLen,
                             firstRowInCol, sampInCol, firstColInRow, sampInRow,
							 (fPMatrix)(MSrce), srceHt, srceLen );}

inline overror_t cudaMF_equMblock( fMatrix MSub, ui subHt, ui subLen, fMatrix MSrce, ui srceHt, ui srceLen,
                      ui firstRowInCol, ui firstColInRow )
{	return cudaMFequMblock(  (fPMatrix)(MSub), subHt, subLen,
						   (fPMatrix)(MSrce), srceHt, srceLen, firstRowInCol, firstColInRow );}

inline overror_t cudaMF_block_equM( fMatrix MDest, ui destHt, ui destLen,
                       ui firstRowInCol, ui firstColInRow,
                       fMatrix MSrce, ui srceHt, ui srceLen )
	{	return cudaMFblock_equM( (fPMatrix)(MDest), destHt, destLen,
                             firstRowInCol, firstColInRow,
							 (fPMatrix)(MSrce), srceHt, srceLen );}

inline overror_t cudaMF_equMblockT( fMatrix MSub, ui subHt, ui subLen, fMatrix MSrce, ui srceHt, ui srceLen,
                      ui firstRowInCol, ui firstColInRow )
	{	return cudaMFequMblockT(  (fPMatrix)(MSub), subHt, subLen,
                             (fPMatrix)(MSrce), srceHt, srceLen,
							 firstRowInCol, firstColInRow );}

inline overror_t cudaMF_block_equMT( fMatrix MDest, ui destHt, ui destLen,
                       ui firstRowInCol, ui firstColInRow,
                       fMatrix MSrce, ui srceHt, ui srceLen )
	{	return cudaMFblock_equMT( (fPMatrix)(MDest), destHt, destLen,
                             firstRowInCol, firstColInRow,
							 (fPMatrix)(MSrce), srceHt, srceLen );}

/*****   Extracting a single row or a single column or the diagonal  ******
 *       and storing it into a vector                                     */

inline overror_t cudaMF_Row_extract( fVector Y, fMatrix MA, ui ht, ui len, ui iRow ) 
	{	return cudaMFRow_extract( Y, (fPMatrix)(MA), ht, len, iRow );}
inline overror_t cudaMF_Col_extract( fVector Y, fMatrix MA, ui ht, ui len, ui iCol ) 
	{	return cudaMFCol_extract( Y, (fPMatrix)(MA), ht, len, iCol );}
inline overror_t cudaMF_Dia_extract( fVector Y, fMatrix MA, ui len )
	{	return cudaMFDia_extract( Y, (fPMatrix)(MA), len );}

/**************  Deleting or inserting a row or a column   ***************/

inline overror_t cudaMF_Row_delete( fMatrix MB, fMatrix MA, ui htA, ui lenA, ui iRow )
	{	return cudaMFRow_delete( (fPMatrix)(MB), (fPMatrix)(MA), htA, lenA, iRow );}
inline overror_t cudaMF_Col_delete( fMatrix MB, fMatrix MA, ui htA, ui lenA, ui iCol )
	{	return cudaMFCol_delete( (fPMatrix)(MB), (fPMatrix)(MA), htA, lenA, iCol );}
inline overror_t cudaMF_Row_insert( fMatrix MB, fMatrix MA, ui htB, ui lenB, ui iRow, fVector X )
	{	return cudaMFRow_insert( (fPMatrix)(MB), (fPMatrix)(MA), htB, lenB, iRow, X );}
inline overror_t cudaMF_Col_insert( fMatrix MB, fMatrix MA, ui htB, ui lenB, ui iCol, fVector X )
	{	return cudaMFCol_insert( (fPMatrix)(MB), (fPMatrix)(MA), htB, lenB, iCol, X );}

/*****************    Basic arithmetic operations *********************
                      performed on one single row,
                      or one single column of any matrix,
                      or on the diagonal of a square matrix

    Note: In contrast to the analogous VectorLib functions, the operations
    are performed in-place, i.e. the input matrix itself is changed  */

inline overror_t cudaMF_Row_neg( fMatrix MA, ui ht, ui len, ui iRow )
	{	return cudaMFRow_neg( (fPMatrix)(MA), ht, len, iRow );}
inline overror_t cudaMF_Col_neg( fMatrix MA, ui ht, ui len, ui iCol )
	{	return cudaMFCol_neg( (fPMatrix)(MA), ht, len, iCol );}

inline overror_t cudaMF_Row_addC( fMatrix MA, ui ht, ui len, ui iRow, float C )
	{	return cudaMFRow_addC( (fPMatrix)(MA), ht, len, iRow, C );}
inline overror_t cudaMF_Col_addC( fMatrix MA, ui ht, ui len, ui iCol, float C )
	{	return cudaMFCol_addC( (fPMatrix)(MA), ht, len, iCol, C );}
inline overror_t cudaMF_Dia_addC( fMatrix MA, ui len, float C )
	{	return cudaMFDia_addC( (fPMatrix)(MA), len, C );}
inline overror_t cusdMF_Row_addC( fMatrix MA, ui ht, ui len, ui iRow, float *d_C )
	{	return cusdMFRow_addC( (fPMatrix)(MA), ht, len, iRow, d_C );}
inline overror_t cusdMF_Col_addC( fMatrix MA, ui ht, ui len, ui iCol, float *d_C )
	{	return cusdMFCol_addC( (fPMatrix)(MA), ht, len, iCol, d_C );}
inline overror_t cusdMF_Dia_addC( fMatrix MA, ui len, float *d_C )
	{	return cusdMFDia_addC( (fPMatrix)(MA), len, d_C );}

inline overror_t cudaMF_Row_addV( fMatrix MA, ui ht, ui len, ui iRow, fVector X )
	{	return cudaMFRow_addV( (fPMatrix)(MA), ht, len, iRow, X );}
inline overror_t cudaMF_Col_addV( fMatrix MA, ui ht, ui len, ui iCol, fVector X )
	{	return cudaMFCol_addV( (fPMatrix)(MA), ht, len, iCol, X );}
inline overror_t cudaMF_Dia_addV( fMatrix MA, ui len, fVector X )
	{	return cudaMFDia_addV( (fPMatrix)(MA), len, X );}

inline overror_t cudaMF_Row_subC( fMatrix MA, ui ht, ui len, ui iRow, float C )
	{	return cudaMFRow_subC( (fPMatrix)(MA), ht, len, iRow, C );}
inline overror_t cudaMF_Col_subC( fMatrix MA, ui ht, ui len, ui iCol, float C )
	{	return cudaMFCol_subC( (fPMatrix)(MA), ht, len, iCol, C );}
inline overror_t cudaMF_Dia_subC( fMatrix MA, ui len, float C )
	{	return cudaMFDia_subC( (fPMatrix)(MA), len, C );}
inline overror_t cusdMF_Row_subC( fMatrix MA, ui ht, ui len, ui iRow, float *d_C )
	{	return cusdMFRow_subC( (fPMatrix)(MA), ht, len, iRow, d_C );}
inline overror_t cusdMF_Col_subC( fMatrix MA, ui ht, ui len, ui iCol, float *d_C )
	{	return cusdMFCol_subC( (fPMatrix)(MA), ht, len, iCol, d_C );}
inline overror_t cusdMF_Dia_subC( fMatrix MA, ui len, float *d_C )
	{	return cusdMFDia_subC( (fPMatrix)(MA), len, d_C );}

inline overror_t cudaMF_Row_subV( fMatrix MA, ui ht, ui len, ui iRow, fVector X )
	{	return cudaMFRow_subV( (fPMatrix)(MA), ht, len, iRow, X );}
inline overror_t cudaMF_Col_subV( fMatrix MA, ui ht, ui len, ui iCol, fVector X )
	{	return cudaMFCol_subV( (fPMatrix)(MA), ht, len, iCol, X );}
inline overror_t cudaMF_Dia_subV( fMatrix MA, ui len, fVector X )
	{	return cudaMFDia_subV( (fPMatrix)(MA), len, X );}

inline overror_t cudaMF_Row_subrC( fMatrix MA, ui ht, ui len, ui iRow, float C )
	{	return cudaMFRow_subrC( (fPMatrix)(MA), ht, len, iRow, C );}
inline overror_t cudaMF_Col_subrC( fMatrix MA, ui ht, ui len, ui iCol, float C )
	{	return cudaMFCol_subrC( (fPMatrix)(MA), ht, len, iCol, C );}
inline overror_t cudaMF_Dia_subrC( fMatrix MA, ui len, float C )
	{	return cudaMFDia_subrC( (fPMatrix)(MA), len, C );}
inline overror_t cusdMF_Row_subrC( fMatrix MA, ui ht, ui len, ui iRow, float *d_C )
	{	return cusdMFRow_subrC( (fPMatrix)(MA), ht, len, iRow, d_C );}
inline overror_t cusdMF_Col_subrC( fMatrix MA, ui ht, ui len, ui iCol, float *d_C )
	{	return cusdMFCol_subrC( (fPMatrix)(MA), ht, len, iCol, d_C );}
inline overror_t cusdMF_Dia_subrC( fMatrix MA, ui len, float *d_C )
	{	return cusdMFDia_subrC( (fPMatrix)(MA), len, d_C );}

inline overror_t cudaMF_Row_subrV( fMatrix MA, ui ht, ui len, ui iRow, fVector X )
	{	return cudaMFRow_subrV( (fPMatrix)(MA), ht, len, iRow, X );}
inline overror_t cudaMF_Col_subrV( fMatrix MA, ui ht, ui len, ui iCol, fVector X )
	{	return cudaMFCol_subrV( (fPMatrix)(MA), ht, len, iCol, X );}
inline overror_t cudaMF_Dia_subrV( fMatrix MA, ui len, fVector X )
	{	return cudaMFDia_subrV( (fPMatrix)(MA), len, X );}

inline overror_t cudaMF_Row_mulC( fMatrix MA, ui ht, ui len, ui iRow, float C )
	{	return cudaMFRow_mulC( (fPMatrix)(MA), ht, len, iRow, C );}
inline overror_t cudaMF_Col_mulC( fMatrix MA, ui ht, ui len, ui iCol, float C )
	{	return cudaMFCol_mulC( (fPMatrix)(MA), ht, len, iCol, C );}
inline overror_t cudaMF_Dia_mulC( fMatrix MA, ui len, float C )
	{	return cudaMFDia_mulC( (fPMatrix)(MA), len, C );}
inline overror_t cusdMF_Row_mulC( fMatrix MA, ui ht, ui len, ui iRow, float *d_C )
	{	return cusdMFRow_mulC( (fPMatrix)(MA), ht, len, iRow, d_C );}
inline overror_t cusdMF_Col_mulC( fMatrix MA, ui ht, ui len, ui iCol, float *d_C )
	{	return cusdMFCol_mulC( (fPMatrix)(MA), ht, len, iCol, d_C );}
inline overror_t cusdMF_Dia_mulC( fMatrix MA, ui len, float *d_C )
	{	return cusdMFDia_mulC( (fPMatrix)(MA), len, d_C );}

inline overror_t cudaMF_Row_mulV( fMatrix MA, ui ht, ui len, ui iRow, fVector X )
	{	return cudaMFRow_mulV( (fPMatrix)(MA), ht, len, iRow, X );}
inline overror_t cudaMF_Col_mulV( fMatrix MA, ui ht, ui len, ui iCol, fVector X )
	{	return cudaMFCol_mulV( (fPMatrix)(MA), ht, len, iCol, X );}
inline overror_t cudaMF_Dia_mulV( fMatrix MA, ui len, fVector X )
	{	return cudaMFDia_mulV( (fPMatrix)(MA), len, X );}

inline overror_t cudaMF_Row_divC( fMatrix MA, ui ht, ui len, ui iRow, float C )
	{	return cudaMFRow_divC( (fPMatrix)(MA), ht, len, iRow, C );}
inline overror_t cudaMF_Col_divC( fMatrix MA, ui ht, ui len, ui iCol, float C )
	{	return cudaMFCol_divC( (fPMatrix)(MA), ht, len, iCol, C );}
inline overror_t cudaMF_Dia_divC( fMatrix MA, ui len, float C )
	{	return cudaMFDia_divC( (fPMatrix)(MA), len, C );}
inline overror_t cusdMF_Row_divC( fMatrix MA, ui ht, ui len, ui iRow, float *d_C )
	{	return cusdMFRow_divC( (fPMatrix)(MA), ht, len, iRow, d_C );}
inline overror_t cusdMF_Col_divC( fMatrix MA, ui ht, ui len, ui iCol, float *d_C )
	{	return cusdMFCol_divC( (fPMatrix)(MA), ht, len, iCol, d_C );}
inline overror_t cusdMF_Dia_divC( fMatrix MA, ui len, float *d_C )
	{	return cusdMFDia_divC( (fPMatrix)(MA), len, d_C );}

inline overror_t cudaMF_Row_divV( fMatrix MA, ui ht, ui len, ui iRow, fVector X )
	{	return cudaMFRow_divV( (fPMatrix)(MA), ht, len, iRow, X );}
inline overror_t cudaMF_Col_divV( fMatrix MA, ui ht, ui len, ui iCol, fVector X )
	{	return cudaMFCol_divV( (fPMatrix)(MA), ht, len, iCol, X );}
inline overror_t cudaMF_Dia_divV( fMatrix MA, ui len, fVector X )
	{	return cudaMFDia_divV( (fPMatrix)(MA), len, X );}

inline overror_t cudaMF_Row_divrC( fMatrix MA, ui ht, ui len, ui iRow, float C )
	{	return cudaMFRow_divrC( (fPMatrix)(MA), ht, len, iRow, C );}
inline overror_t cudaMF_Col_divrC( fMatrix MA, ui ht, ui len, ui iCol, float C )
	{	return cudaMFCol_divrC( (fPMatrix)(MA), ht, len, iCol, C );}
inline overror_t cudaMF_Dia_divrC( fMatrix MA, ui len, float C )
	{	return cudaMFDia_divrC( (fPMatrix)(MA), len, C );}
inline overror_t cusdMF_Row_divrC( fMatrix MA, ui ht, ui len, ui iRow, float *d_C )
	{	return cusdMFRow_divrC( (fPMatrix)(MA), ht, len, iRow, d_C );}
inline overror_t cusdMF_Col_divrC( fMatrix MA, ui ht, ui len, ui iCol, float *d_C )
	{	return cusdMFCol_divrC( (fPMatrix)(MA), ht, len, iCol, d_C );}
inline overror_t cusdMF_Dia_divrC( fMatrix MA, ui len, float *d_C )
	{	return cusdMFDia_divrC( (fPMatrix)(MA), len, d_C );}

inline overror_t cudaMF_Row_divrV( fMatrix MA, ui ht, ui len, ui iRow, fVector X )
	{	return cudaMFRow_divrV( (fPMatrix)(MA), ht, len, iRow, X );}
inline overror_t cudaMF_Col_divrV( fMatrix MA, ui ht, ui len, ui iCol, fVector X )
	{	return cudaMFCol_divrV( (fPMatrix)(MA), ht, len, iCol, X );}
inline overror_t cudaMF_Dia_divrV( fMatrix MA, ui len, fVector X )
	{	return cudaMFDia_divrV( (fPMatrix)(MA), len, X );}


/******  One-dimensional vector operations **********************
         performed along all rows or all columns simultaneously,
         or along the diagonal of a square matrix                */

inline overror_t cudaMF_Rows_max( fVector Y, fMatrix MA, ui ht, ui len )
	{	return cudaMFRows_max( Y, (fPMatrix)(MA), ht, len );}
inline overror_t cudaMF_Cols_max( fVector Y, fMatrix MA, ui ht, ui len )
	{	return cudaMFCols_max( Y, (fPMatrix)(MA), ht, len );}
inline overror_t cudaMF_Dia_max(  float *h_RetValPtr, fMatrix MA, ui len )
	{	return cudaMFDia_max(  h_RetValPtr, (fPMatrix)(MA), len );}
inline overror_t cusdMF_Dia_max(  float *d_RetValPtr, fMatrix MA, ui len )
	{	return cusdMFDia_max(  d_RetValPtr, (fPMatrix)(MA), len );}
inline overror_t cudaMF_Rows_min( fVector Y, fMatrix MA, ui ht, ui len )
	{	return cudaMFRows_min( Y, (fPMatrix)(MA), ht, len );}
inline overror_t cudaMF_Cols_min( fVector Y, fMatrix MA, ui ht, ui len )
	{	return cudaMFCols_min( Y, (fPMatrix)(MA), ht, len );}
inline overror_t cudaMF_Dia_min(  float *h_RetValPtr, fMatrix MA, ui len )
	{	return cudaMFDia_min(  h_RetValPtr, (fPMatrix)(MA), len );}
inline overror_t cusdMF_Dia_min(  float *d_RetValPtr, fMatrix MA, ui len )
	{	return cusdMFDia_min(  d_RetValPtr, (fPMatrix)(MA), len );}

inline overror_t cudaMF_Rows_absmax( fVector Y, fMatrix MA, ui ht, ui len )
	{	return cudaMFRows_absmax( Y, (fPMatrix)(MA), ht, len );}
inline overror_t cudaMF_Cols_absmax( fVector Y, fMatrix MA, ui ht, ui len )
	{	return cudaMFCols_absmax( Y, (fPMatrix)(MA), ht, len );}
inline overror_t cudaMF_Dia_absmax(  float *h_RetValPtr, fMatrix MA, ui len )
	{	return cudaMFDia_absmax(  h_RetValPtr, (fPMatrix)(MA), len );}
inline overror_t cusdMF_Dia_absmax(  float *d_RetValPtr, fMatrix MA, ui len )
	{	return cusdMFDia_absmax(  d_RetValPtr, (fPMatrix)(MA), len );}
inline overror_t cudaMF_Rows_absmin( fVector Y, fMatrix MA, ui ht, ui len )
	{	return cudaMFRows_absmin( Y, (fPMatrix)(MA), ht, len );}
inline overror_t cudaMF_Cols_absmin( fVector Y, fMatrix MA, ui ht, ui len )
	{	return cudaMFCols_absmin( Y, (fPMatrix)(MA), ht, len );}
inline overror_t cudaMF_Dia_absmin(  float *h_RetValPtr, fMatrix MA, ui len )
	{	return cudaMFDia_absmin(  h_RetValPtr, (fPMatrix)(MA), len );}
inline overror_t cusdMF_Dia_absmin(  float *d_RetValPtr, fMatrix MA, ui len )
	{	return cusdMFDia_absmin(  d_RetValPtr, (fPMatrix)(MA), len );}

inline overror_t cudaMF_Rows_sum( fVector Y, fMatrix MA, ui ht, ui len )
	{	return cudaMFRows_sum( Y, (fPMatrix)(MA), ht, len );}
inline overror_t cudaMF_Cols_sum( fVector Y, fMatrix MA, ui ht, ui len )
	{	return cudaMFCols_sum( Y, (fPMatrix)(MA), ht, len );}
inline overror_t cudaMF_Dia_sum(  float *h_RetValPtr, fMatrix MA, ui len )
	{	return cudaMFDia_sum(  h_RetValPtr, (fPMatrix)(MA), len );}
inline overror_t cusdMF_Dia_sum(  float *d_RetValPtr, fMatrix MA, ui len )
	{	return cusdMFDia_sum(  d_RetValPtr, (fPMatrix)(MA), len );}
inline overror_t cudaMF_Rows_ssq( fVector Y, fMatrix MA, ui ht, ui len )
	{	return cudaMFRows_ssq( Y, (fPMatrix)(MA), ht, len );}
inline overror_t cudaMF_Cols_ssq( fVector Y, fMatrix MA, ui ht, ui len )
	{	return cudaMFCols_ssq( Y, (fPMatrix)(MA), ht, len );}
inline overror_t cudaMF_Dia_ssq(  float *h_RetValPtr, fMatrix MA, ui len )
	{	return cudaMFDia_ssq(  h_RetValPtr, (fPMatrix)(MA), len );}
inline overror_t cusdMF_Dia_ssq(  float *d_RetValPtr, fMatrix MA, ui len )
	{	return cusdMFDia_ssq(  d_RetValPtr, (fPMatrix)(MA), len );}
inline overror_t cudaMF_Rows_prod( fVector Y, fMatrix MA, ui ht, ui len )
	{	return cudaMFRows_prod( Y, (fPMatrix)(MA), ht, len );}
inline overror_t cudaMF_Cols_prod( fVector Y, fMatrix MA, ui ht, ui len )
	{	return cudaMFCols_prod( Y, (fPMatrix)(MA), ht, len );}
inline overror_t cudaMF_Dia_prod(  float *h_RetValPtr, fMatrix MA, ui len )
	{	return cudaMFDia_prod(  h_RetValPtr, (fPMatrix)(MA), len );}
inline overror_t cusdMF_Dia_prod(  float *d_RetValPtr, fMatrix MA, ui len )
	{	return cusdMFDia_prod(  d_RetValPtr, (fPMatrix)(MA), len );}

inline overror_t cudaMF_Rows_runsum( fMatrix MA, ui ht, ui len )
	{	return cudaMFRows_runsum( (fPMatrix)(MA), ht, len );}
inline overror_t cudaMF_Cols_runsum( fMatrix MA, ui ht, ui len )
	{	return cudaMFCols_runsum( (fPMatrix)(MA), ht, len );}
inline overror_t cudaMF_Rows_runprod( fMatrix MA, ui ht, ui len )
	{	return cudaMFRows_runprod( (fPMatrix)(MA), ht, len );}
inline overror_t cudaMF_Cols_runprod( fMatrix MA, ui ht, ui len )
	{	return cudaMFCols_runprod( (fPMatrix)(MA), ht, len );}

inline overror_t cudaMF_Rows_rotate( fMatrix MA, ui ht, ui len, ssize_t pos)
	{	return cudaMFRows_rotate( (fPMatrix)(MA), ht, len, pos );}
inline overror_t cudaMF_Cols_rotate( fMatrix MA, ui ht, ui len, ssize_t pos)
	{	return cudaMFCols_rotate( (fPMatrix)(MA), ht, len, pos );}
inline overror_t cudaMF_Rows_rotate_buf( fMatrix MA, ui ht, ui len, ssize_t pos, fMatrix MBuf) 
	{	return cudaMFRows_rotate_buf( (fPMatrix)(MA), ht, len, pos, (fPMatrix)(MBuf) );}
inline overror_t cudaMF_Cols_rotate_buf( fMatrix MA, ui ht, ui len, ssize_t pos, fMatrix MBuf) 
	{	return cudaMFCols_rotate_buf( (fPMatrix)(MA), ht, len, pos, (fPMatrix)(MBuf) );}
inline overror_t cudaMF_Rows_reflect( fMatrix MA, ui ht, ui len )
	{	return cudaMFRows_reflect( (fPMatrix)(MA), ht, len );}
inline overror_t cudaMF_Cols_reflect( fMatrix MA, ui ht, ui len )
	{	return cudaMFCols_reflect( (fPMatrix)(MA), ht, len );}
inline overror_t cudaMF_Rows_rev( fMatrix MA, ui ht, ui len )
	{	return cudaMFRows_rev( (fPMatrix)(MA), ht, len );}
inline overror_t cudaMF_Cols_rev( fMatrix MA, ui ht, ui len )
	{	return cudaMFCols_rev( (fPMatrix)(MA), ht, len );}
inline overror_t  cudaMF_Rows_distribution( uiMatrix MAbund, fVector Limits, ui nBins, fMatrix MX, ui ht, ui len, int mode )
	{	return cudaMFRows_distribution( (uiPMatrix)MAbund, Limits, nBins, (fPMatrix)MX, ht, len, mode ); }
inline overror_t  cudaMF_Cols_distribution( uiMatrix MAbund, fVector Limits, ui nBins, fMatrix MX, ui ht, ui len, int mode )
	{	return cudaMFCols_distribution( (uiPMatrix)MAbund, Limits, nBins, (fPMatrix)MX, ht, len, mode ); }

/********  Operations involving two rows or two colums of one matrix  *****/

inline overror_t cudaMF_Rows_exchange( fMatrix MA, ui ht, ui len, ui row1, ui row2 )
	{	return cudaMFRows_exchange( (fPMatrix)(MA), ht, len, row1, row2 );}
inline overror_t cudaMF_Cols_exchange( fMatrix MA, ui ht, ui len, ui col1, ui col2 )
	{	return cudaMFCols_exchange( (fPMatrix)(MA), ht, len, col1, col2 );}

inline overror_t cudaMF_Rows_add( fMatrix MA, ui ht, ui len, ui destRow, ui srceRow )
	{	return cudaMFRows_add( (fPMatrix)(MA), ht, len, destRow, srceRow );}
inline overror_t cudaMF_Cols_add( fMatrix MA, ui ht, ui len, ui destCol, ui srceCol )
	{	return cudaMFCols_add( (fPMatrix)(MA), ht, len, destCol, srceCol );}
                         /* dest[i] += source[i]  */

inline overror_t cudaMF_Rows_sub( fMatrix MA, ui ht, ui len, ui destRow, ui srceRow )
	{	return cudaMFRows_sub( (fPMatrix)(MA), ht, len, destRow, srceRow );}
inline overror_t cudaMF_Cols_sub( fMatrix MA, ui ht, ui len, ui destCol, ui srceCol )
	{	return cudaMFCols_sub( (fPMatrix)(MA), ht, len, destCol, srceCol );}
                         /* dest[i] -= source[i]  */

inline overror_t cudaMF_Rows_Cadd( fMatrix MA, ui ht, ui len, ui destRow, ui srceRow, float C )
	{	return cudaMFRows_Cadd( (fPMatrix)(MA), ht, len, destRow, srceRow, C );}
inline overror_t cudaMF_Cols_Cadd( fMatrix MA, ui ht, ui len, ui destCol, ui srceCol, float C )
	{	return cudaMFCols_Cadd( (fPMatrix)(MA), ht, len, destCol, srceCol, C );}
inline overror_t cusdMF_Rows_Cadd( fMatrix MA, ui ht, ui len, ui destRow, ui srceRow, float *d_C )
	{	return cusdMFRows_Cadd( (fPMatrix)(MA), ht, len, destRow, srceRow, d_C );}
inline overror_t cusdMF_Cols_Cadd( fMatrix MA, ui ht, ui len, ui destCol, ui srceCol, float *d_C )
	{	return cusdMFCols_Cadd( (fPMatrix)(MA), ht, len, destCol, srceCol, d_C );}
                         /* dest[i] += C * source[i]  */

inline overror_t cudaMF_Rows_lincomb( fMatrix MA, ui ht, ui len, ui destRow, float destC, ui srceRow, float srceC )
	{	return cudaMFRows_lincomb( (fPMatrix)(MA), ht, len, destRow, destC, srceRow, srceC );}
inline overror_t cudaMF_Cols_lincomb( fMatrix MA, ui ht, ui len, ui destCol, float destC, ui srceCol, float srceC )
	{	return cudaMFCols_lincomb( (fPMatrix)(MA), ht, len, destCol, destC, srceCol, srceC );}
inline overror_t cusdMF_Rows_lincomb( fMatrix MA, ui ht, ui len, ui destRow, float *d_destC, ui srceRow, float *d_srceC )
	{	return cusdMFRows_lincomb( (fPMatrix)(MA), ht, len, destRow, d_destC, srceRow, d_srceC );}
inline overror_t cusdMF_Cols_lincomb( fMatrix MA, ui ht, ui len, ui destCol, float *d_destC, ui srceCol, float *d_srceC )
	{	return cusdMFCols_lincomb( (fPMatrix)(MA), ht, len, destCol, d_destC, srceCol, d_srceC );}
  /*  linear combination: dest[i] = destC * dest[i] + sourceC * source[i] */


/*********************  Center of gravity *****************************/
inline overror_t cudaMF_centerOfGravityInd( fComplex *h_RetValPtr, fMatrix MA, ui ht, ui len )
	{	return cudaMFcenterOfGravityInd( h_RetValPtr, (fPMatrix)(MA), ht, len );}
inline overror_t cudaMF_centerOfGravityV( fComplex *h_RetValPtr, fVector X, fVector Y, fMatrix MA, ui ht, ui len )
	{	return cudaMFcenterOfGravityV( h_RetValPtr, X, Y, (fPMatrix)(MA), ht, len );}
inline overror_t cusdMF_centerOfGravityInd( fComplex *d_RetValPtr, fMatrix MA, ui ht, ui len )
	{	return cusdMFcenterOfGravityInd( d_RetValPtr, (fPMatrix)(MA), ht, len );}
inline overror_t cusdMF_centerOfGravityV( fComplex *d_RetValPtr, fVector X, fVector Y, fMatrix MA, ui ht, ui len )
	{	return cusdMFcenterOfGravityV( d_RetValPtr, X, Y, (fPMatrix)(MA), ht, len );}

/*************** Transposing and rotating a matrix **********************/

inline overror_t cudaMF_transpose( fMatrix MTr, fMatrix MA, ui htTr, ui lenTr )
	{	return cudaMFtranspose( (fPMatrix)(MTr), (fPMatrix)(MA), htTr, lenTr );}
       /*  dimensions htTr, lenTr are those of the transposed matrix, not of the original!   */
inline overror_t cudaMF_rotate90( fMatrix MRot, fMatrix MA, ui htRot, ui lenRot )
	{	return cudaMFrotate90( (fPMatrix)(MRot), (fPMatrix)(MA), htRot, lenRot );}
inline overror_t cudaMF_rotate180( fMatrix MRot, fMatrix MA, ui htRot, ui lenRot )
	{	return cudaVF_rev( (fPMatrix)(MRot), (fPMatrix)(MA), (htRot)*(lenRot) );}
inline overror_t cudaMF_rotate270( fMatrix MRot, fMatrix MA, ui htRot, ui lenRot )
	{	return cudaMFrotate270( (fPMatrix)(MRot), (fPMatrix)(MA), htRot, lenRot );}
inline overror_t cudaMF_transpose_buf( fMatrix MTr, fMatrix MA, ui htTr, ui lenTr, fMatrix MBuf )
	{	return cudaMFtranspose_buf( (fPMatrix)(MTr), (fPMatrix)(MA), htTr, lenTr, (fPMatrix)(MBuf) );}

 /********************** Interpolation of Matrix elements **************/

inline overror_t cudaMF_polyinterpol( fMatrix MZ, fVector X, fVector Y, ui ht, ui len, 
									fVector XTab, fVector YTab, fMatrix MZTab, ui httab, ui lentab, unsigned degX, unsigned degY )
	{	return cudaMFpolyinterpol( (fPMatrix)(MZ), X, Y, ht, len, XTab, YTab, (fPMatrix)(MZTab), httab, lentab, degX, degY );}
inline overror_t cudaMF_ratinterpol( fMatrix MZ, fVector X, fVector Y, ui ht, ui len, 
									fVector XTab, fVector YTab, fMatrix MZTab, ui httab, ui lentab, unsigned degX, unsigned degY )
	{	return cudaMFratinterpol( (fPMatrix)(MZ), X, Y, ht, len, XTab, YTab, (fPMatrix)(MZTab), httab, lentab, degX, degY );}
inline overror_t cudaMF_natCubSplineInterpol( fMatrix MZ, fVector X, fVector Y, ui ht, ui len, 
									fVector XTab, fVector YTab, fMatrix MZTab, ui httab, ui lentab )
	{	return cudaMFnatCubSplineInterpol( (fPMatrix)(MZ), X, Y, ht, len, XTab, YTab, (fPMatrix)(MZTab), httab, lentab );}

/************************ Matrix Arithmetics *************************/

inline overror_t cudaMF_addM( fMatrix MC, fMatrix MA, fMatrix MB, ui htA, ui lenA )
	{	return cudaVF_addV( (fPMatrix)(MC), (fPMatrix)(MA), (fPMatrix)(MB), (htA)*(lenA) );}
inline overror_t cudaMF_addMT( fMatrix MC, fMatrix MA, fMatrix MB, ui htA, ui lenA )
	{	return cudaMFaddMT( (fPMatrix)(MC), (fPMatrix)(MA), (fPMatrix)(MB), htA, lenA );}
inline overror_t cudaMF_subM( fMatrix MC, fMatrix MA, fMatrix MB, ui htA, ui lenA )
	{	return cudaVF_subV( (fPMatrix)(MC), (fPMatrix)(MA), (fPMatrix)(MB), (htA)*(lenA) );}
inline overror_t cudaMF_subMT( fMatrix MC, fMatrix MA, fMatrix MB, ui htA, ui lenA )
	{	return cudaMFsubMT( (fPMatrix)(MC), (fPMatrix)(MA), (fPMatrix)(MB), htA, lenA );}
inline overror_t cudaMF_subrM( fMatrix MC, fMatrix MA, fMatrix MB, ui htA, ui lenA )
	{	return cudaVF_subrV( (fPMatrix)(MC), (fPMatrix)(MA), (fPMatrix)(MB), (htA)*(lenA) );}
inline overror_t cudaMF_subrMT( fMatrix MC, fMatrix MA, fMatrix MB, ui htA, ui lenA )
	{	return cudaMFsubrMT( (fPMatrix)(MC), (fPMatrix)(MA), (fPMatrix)(MB), htA, lenA );}
inline overror_t cudaMF_mulC( fMatrix MB, fMatrix MA, ui htA, ui lenA, float C )
	{	return cudaVF_mulC( (fPMatrix)(MB), (fPMatrix)(MA), (htA)*(lenA), C );}
inline overror_t cudaMF_divC( fMatrix MB, fMatrix MA, ui htA, ui lenA, float C )
	{	return cudaVF_divC( (fPMatrix)(MB), (fPMatrix)(MA), (htA)*(lenA), C );}
inline overror_t cusdMF_mulC( fMatrix MB, fMatrix MA, ui htA, ui lenA, float *d_C )
	{	return cusdVF_mulC( (fPMatrix)(MB), (fPMatrix)(MA), (htA)*(lenA), d_C );}
inline overror_t cusdMF_divC( fMatrix MB, fMatrix MA, ui htA, ui lenA, float *d_C )
	{	return cusdVF_divC( (fPMatrix)(MB), (fPMatrix)(MA), (htA)*(lenA), d_C );}

inline overror_t cudaMFs_addM( fMatrix MC, fMatrix MA, fMatrix MB, ui htA, ui lenA, float C )
	{	return cudaVFs_addV( (fPMatrix)(MC), (fPMatrix)(MA), (fPMatrix)(MB), (htA)*(lenA), C );}
inline overror_t cudaMFs_addMT( fMatrix MC, fMatrix MA, fMatrix MB, ui htA, ui lenA, float C )
	{	return cudaMFsaddMT( (fPMatrix)(MC), (fPMatrix)(MA), (fPMatrix)(MB), htA, lenA, C );}
inline overror_t cudaMFs_subM( fMatrix MC, fMatrix MA, fMatrix MB, ui htA, ui lenA, float C )
	{	return cudaVFs_subV( (fPMatrix)(MC), (fPMatrix)(MA), (fPMatrix)(MB), (htA)*(lenA), C );}
inline overror_t cudaMFs_subMT( fMatrix MC, fMatrix MA, fMatrix MB, ui htA, ui lenA, float C )
	{	return cudaMFssubMT( (fPMatrix)(MC), (fPMatrix)(MA), (fPMatrix)(MB), htA, lenA, C );}
inline overror_t cudaMFs_subrM( fMatrix MC, fMatrix MA, fMatrix MB, ui htA, ui lenA, float C )
	{	return cudaVFs_subrV( (fPMatrix)(MC), (fPMatrix)(MA), (fPMatrix)(MB), (htA)*(lenA), C );}
inline overror_t cudaMFs_subrMT( fMatrix MC, fMatrix MA, fMatrix MB, ui htA, ui lenA, float C )
	{	return cudaMFssubrMT( (fPMatrix)(MC), (fPMatrix)(MA), (fPMatrix)(MB), htA, lenA, C );}
inline overror_t cusdMFs_addM( fMatrix MC, fMatrix MA, fMatrix MB, ui htA, ui lenA, float *d_C )
	{	return cusdVFs_addV( (fPMatrix)(MC), (fPMatrix)(MA), (fPMatrix)(MB), (htA)*(lenA), d_C );}
inline overror_t cusdMFs_addMT( fMatrix MC, fMatrix MA, fMatrix MB, ui htA, ui lenA, float *d_C )
	{	return cusdMFsaddMT( (fPMatrix)(MC), (fPMatrix)(MA), (fPMatrix)(MB), htA, lenA, d_C );}
inline overror_t cusdMFs_subM( fMatrix MC, fMatrix MA, fMatrix MB, ui htA, ui lenA, float *d_C )
	{	return cusdVFs_subV( (fPMatrix)(MC), (fPMatrix)(MA), (fPMatrix)(MB), (htA)*(lenA), d_C );}
inline overror_t cusdMFs_subMT( fMatrix MC, fMatrix MA, fMatrix MB, ui htA, ui lenA, float *d_C )
	{	return cusdMFssubMT( (fPMatrix)(MC), (fPMatrix)(MA), (fPMatrix)(MB), htA, lenA, d_C );}
inline overror_t cusdMFs_subrM( fMatrix MC, fMatrix MA, fMatrix MB, ui htA, ui lenA, float *d_C )
	{	return cusdVFs_subrV( (fPMatrix)(MC), (fPMatrix)(MA), (fPMatrix)(MB), (htA)*(lenA), d_C );}
inline overror_t cusdMFs_subrMT( fMatrix MC, fMatrix MA, fMatrix MB, ui htA, ui lenA, float *d_C )
	{	return cusdMFssubrMT( (fPMatrix)(MC), (fPMatrix)(MA), (fPMatrix)(MB), htA, lenA, d_C );}

inline overror_t cudaMF_lincomb( fMatrix MC, fMatrix MA, fMatrix MB, ui htA, ui lenA, float CA, float CB )
	{	return cudaVF_lincomb( (fPMatrix)(MC), (fPMatrix)(MA), (fPMatrix)(MB), (htA)*(lenA), CA, CB );}
inline overror_t cusdMF_lincomb( fMatrix MC, fMatrix MA, fMatrix MB, ui htA, ui lenA, float *d_CA, float *d_CB )
	{	return cusdVF_lincomb( (fPMatrix)(MC), (fPMatrix)(MA), (fPMatrix)(MB), (htA)*(lenA), d_CA, d_CB );}

inline overror_t cudaMF_mulV( fVector Y, fMatrix MA, fVector X, ui htA, ui lenA )
	{	return cudaMFmulV( Y, (fPMatrix)(MA), X, htA, lenA );}
             /*  Y = MA * X.  sizX=lenA, sizY=htA;   both X and Y are column-vectors    */
inline overror_t cudaMF_TmulV( fVector Y, fMatrix MA, fVector X, ui htA, ui lenA )
	{	return cudaMFTmulV( Y, (fPMatrix)(MA), X, htA, lenA );}
            /*  Y = MAT * X.  sizX=htA, sizY=lenA;   both X and Y are column-vectors    */
inline overror_t cudaVF_mulM( fVector Y, fVector X, fMatrix MA, ui htA, ui lenA )
	{	return cudaVFmulM( Y, X, (fPMatrix)(MA), htA, lenA );}
            /*  Y = X * MA.  sizX=htA, sizY=lenA;    both X and Y are row-vectors.
                             Mind the prefix: cudaVF_ (not cudaMF_)    */
inline overror_t cudaVF_mulMT( fVector Y, fVector X, fMatrix MA, ui htA, ui lenA )
	{	return cudaVFmulMT( Y, X, (fPMatrix)(MA), htA, lenA );}
            /*  Y = X * MAT.  sizX=lenA, sizY=htA;   both X and Y are row-vectors.   */
inline overror_t cudaMF_mulM( fMatrix MC, fMatrix MA, fMatrix MB, ui htA, ui lenA, ui lenB )
	{	return cudaMFmulM( (fPMatrix)(MC), (fPMatrix)(MA), (fPMatrix)(MB), htA, lenA, lenB );}
                         /*  MC = MA * MB.  htB=lenA, htC=htA, lenC=lenB */
inline overror_t cudaMF_mulMT( fMatrix MC, fMatrix MA, fMatrix MB, ui htA, ui lenA, ui htB )
	{	return cudaMFmulMT( (fPMatrix)(MC), (fPMatrix)(MA), (fPMatrix)(MB), htA, lenA, htB );}
                         /*  MC = MA * MBT.  lenB=lenA, htC=htA, lenC=htB */
inline overror_t cudaMF_TmulM( fMatrix MC, fMatrix MA, fMatrix MB, ui htA, ui lenA, ui lenB )
	{	return cudaMFTmulM( (fPMatrix)(MC), (fPMatrix)(MA), (fPMatrix)(MB), htA, lenA, lenB );}
                         /*  MC = MAT * MB.  htB=htA, htC=lenA, lenC=lenB */
inline overror_t cudaMF_TmulMT( fMatrix MC, fMatrix MA, fMatrix MB, ui htA, ui lenA, ui htB )
	{	return cudaMFTmulMT( (fPMatrix)(MC), (fPMatrix)(MA), (fPMatrix)(MB), htA, lenA, htB );}
                         /*  MC = MAT * MBT.  lenB=htA, htC=lenA, lenC=htB */
inline overror_t cudaMFdia_mulM(  fMatrix MC, fVector MADia, fMatrix MB, ui htB, ui lenB )
	{	return cudaMFdiamulM(  (fPMatrix)(MC), MADia, (fPMatrix)(MB), htB, lenB );}
inline overror_t cudaMFdia_mulMT(  fMatrix MC, fVector MADia, fMatrix MB, ui htB, ui lenB )
	{	return cudaMFdiamulMT(  (fPMatrix)(MC), MADia, (fPMatrix)(MB), htB, lenB );}
inline overror_t cudaMF_mulMdia(  fMatrix MC, fMatrix MA, fVector MBDia, ui htA, ui lenA )
	{	return cudaMFmulMdia(  (fPMatrix)(MC), (fPMatrix)(MA), MBDia, htA, lenA );}
inline overror_t cudaMF_TmulMdia(  fMatrix MC, fMatrix MA, fVector MBDia, ui htA, ui lenA )
	{	return cudaMFTmulMdia(  (fPMatrix)(MC), (fPMatrix)(MA), MBDia, htA, lenA );}

/***************** Two-Dimensional Fourier-Transform Methods ************/

inline overror_t cudaMF_FFT( fMatrix MY, fMatrix MX, ui ht, ui len, int dir )
	{	return cudaMFFFT( (fPMatrix)(MY), (fPMatrix)(MX), ht, len, dir );}
inline overror_t cudaMF_Rows_FFT( fMatrix MY, fMatrix MX, ui ht, ui len, int dir )
	{	return cudaMFRows_FFT( (fPMatrix)(MY), (fPMatrix)(MX), ht, len, dir );}
inline overror_t cudaMF_Cols_FFT( fMatrix MY, fMatrix MX, ui ht, ui len, int dir )
	{	return cudaMFCols_FFT( (fPMatrix)(MY), (fPMatrix)(MX), ht, len, dir );}
inline overror_t cudaMF_FFTtoC( cfMatrix MY, fMatrix MX, ui ht, ui len )
	{	return cudaMFFFTtoC( (cfPMatrix)(MY), (fPMatrix)(MX), ht, len );}
inline overror_t cudaMF_Rows_FFTtoC( cfMatrix MY, fMatrix MX, ui ht, ui len )
	{	return cudaMFRows_FFTtoC( (cfPMatrix)(MY), (fPMatrix)(MX), ht, len );}
inline overror_t cudaMF_Cols_FFTtoC( cfMatrix MY, fMatrix MX, ui ht, ui len )
	{	return cudaMFCols_FFTtoC( (cfPMatrix)(MY), (fPMatrix)(MX), ht, len );}
inline overror_t cudaMF_convolve( fMatrix MY, fMatrix MFlt, fMatrix MX, fMatrix MRsp, ui ht, ui len )
	{	return cudaMFconvolve( (fPMatrix)(MY), (fPMatrix)(MFlt), (fPMatrix)(MX), (fPMatrix)(MRsp), ht, len );}
inline overror_t cudaMF_deconvolve( fMatrix MY, fMatrix MFlt, fMatrix MX, fMatrix MRsp, ui ht, ui len )
	{	return cudaMFdeconvolve( (fPMatrix)(MY), (fPMatrix)(MFlt), (fPMatrix)(MX), (fPMatrix)(MRsp), ht, len );}
inline overror_t cudaMF_filter( fMatrix MY, fMatrix MX, fMatrix MFlt, ui ht, ui len )
	{	return cudaMFfilter( (fPMatrix)(MY), (fPMatrix)(MX), (fPMatrix)(MFlt), ht, len );}
inline overror_t cudaMF_autocorr( fMatrix MACorr, fMatrix MX, ui ht, ui len )
	{	return cudaMFautocorr( (fPMatrix)(MACorr), (fPMatrix)(MX), ht, len );}
inline overror_t cudaMF_xcorr( fMatrix MXCorr, fMatrix MX, fMatrix MY, ui ht, ui len)
	{	return cudaMFxcorr( (fPMatrix)(MXCorr), (fPMatrix)(MX), (fPMatrix)(MY), ht, len );}
inline overror_t cudaMF_spectrum( fMatrix MSpec, ui htSpec, ui lenSpec, fMatrix MX, ui htX, ui lenX, fMatrix MWin )
	{	return cudaMFspectrum( (fPMatrix)(MSpec), htSpec, lenSpec, (fPMatrix)(MX), htX, lenX, (fPMatrix)(MWin) );}
              /*   htSpec, lenSpec must be 2**n,
                   MSpec must be a (htSpec+1)*(lenSpec+1) matrix!!
                   htX >= n*htSpec,  lenX >= n*lenSpec,
                   htWin = 2*htSpec, lenWin = 2*lenSpec */

/**************************  Input and Output  **************************
	The input/output functions involve memory transfers from device
	to host memory or vice versa. The generic cudaMF_input/output functions
	allocate their own host buffers, whereas the cudaMF_xxx_buf functions
	take a user-supplied buffer vector h_Wk (size must be >= ht*len )
	and are much more efficient.                                       */

inline overror_t cudaMF_fprint( FILE *stream, fMatrix MA, ui ht, ui len, unsigned linewidth )
	{	return cudaMFfprint( stream, (fPMatrix)(MA), ht, len, linewidth ); }
inline overror_t cudaMF_print( fMatrix MA, ui ht, ui len )
	{	return cudaMFfprint( stdout, (fPMatrix)(MA), ht, len, 80 ); }
inline overror_t cudaMF_cprint( fMatrix MA, ui ht, ui len )
	{	return cudaMFcprint( (fPMatrix)(MA), ht, len ); }
inline overror_t cudaMF_fprint_buf( FILE *stream, fMatrix d_MA, ui ht, ui len, unsigned linewidth, fVector h_Wk )
	{	return cudaMFfprint_buf( stream, (fPMatrix)(d_MA), ht, len, linewidth, h_Wk ); }
inline overror_t cudaMF_print_buf( fMatrix d_MA, ui ht, ui len, fVector h_Wk )
	{	return cudaMFfprint_buf( stdout, (fPMatrix)(d_MA), ht, len, 80, h_Wk ); }
inline overror_t cudaMF_cprint_buf( fMatrix d_MA, ui ht, ui len, fVector h_Wk )
	{	return cudaMFcprint_buf( (fPMatrix)(d_MA), ht, len, h_Wk ); }
		/*  cudaMF_print, cudaMF_cprint usable only for console applications! */
inline overror_t  cudaMF_write( FILE *stream, fMatrix MA, ui ht, ui len )
	{	return cudaMFwrite( stream, (fPMatrix)(MA), ht, len ); }
inline overror_t cudaMF_read( fMatrix MA, ui ht, ui len, FILE *stream )
	{	return cudaMFread( (fPMatrix)(MA), ht, len, stream ); }
inline overror_t  cudaMF_write_buf( FILE *stream, fMatrix d_MA, ui ht, ui len, fVector h_Wk )
	{	return cudaMFwrite_buf( stream, (fPMatrix)(d_MA), ht, len, h_Wk ); }
inline overror_t cudaMF_read_buf( fMatrix d_MA, ui ht, ui len, FILE *stream, fVector h_Wk )
	{	return cudaMFread_buf( (fPMatrix)(d_MA), ht, len, stream, h_Wk ); }
                                   /* write and read in ascii format */
inline overror_t cudaMF_store( FILE *stream, fMatrix MA, ui ht, ui len )
{	return cudaVF_store( stream, (fPMatrix)(MA), (len)*(ht) ); }
inline overror_t cudaMF_recall( fMatrix MA, ui ht, ui len, FILE *stream )
	{	return cudaVF_recall( (fPMatrix)(MA), (len)*(ht), stream ); }
inline overror_t cudaMF_store_buf( FILE *stream, fMatrix d_MA, ui ht, ui len, fVector h_Wk )
{	return cudaVF_store_buf( stream, (fPMatrix)(d_MA), (len)*(ht), h_Wk ); }
inline overror_t cudaMF_recall_buf( fMatrix d_MA, ui ht, ui len, FILE *stream, fVector h_Wk )
	{	return cudaVF_recall_buf( (fPMatrix)(d_MA), (len)*(ht), stream, h_Wk ); }
                                  /* store and recall in binary format */

#else  /* plain-C, not C++: type-cast used to transform fMatrix into fPMatrix */

/***  Addressing single elements of dynamically allocated matrices: ******/

#define cudaMF_setElement( MA, ht, len, m, n, C ) cudaMFsetElement( (fPMatrix)(MA), ht, len, m, n, C )
#define cusdMF_setElement( MA, ht, len, m, n, C ) cusdMFsetElement( (fPMatrix)(MA), ht, len, m, n, C )
#define cudaMF_getElement( y, MA, ht, len, m, n ) cudaMFgetElement( y, (fPMatrix)(MA), ht, len, m, n )
#define cusdMF_getElement( y, MA, ht, len, m, n ) cusdMFgetElement( y, (fPMatrix)(MA), ht, len, m, n )
#define cudaMF_Pelement( MA, ht, len, m, n )      cudaMFPelement( (fPMatrix)(MA), ht, len, m, n )
#define cudaMF_element( MA, ht, len, m, n )       cudaMFelement( (fPMatrix)(MA), ht, len, m, n )

 /****************  Initialization  ***************************************

    To initialize all elements of a matrix with the same value,
    or to perform arithmetic operations on all elements simultaneously,
    refer to the functions of VectorLib.
    In order to use the VectorLib functions, utilize the feature that
    the whole matrix occupies one contiguous area in memory: pass the
    address of the first row to the desired vector function, the size
    of the "vector" being ht * len.
    For example, initialize all elements of the matrix MA with 1.0
    (this is *NOT* the identity matrix)  by calling
        cudaVF_equ1( (fPMatrix)(MA), ht * len );
*/

#define cudaMF_equ0( MA, ht, len )                   cudaVF_equ0( (fPMatrix)(MA), (ht)*(len) )
#define cudaMF_equ1( MA, len )                       cudaMFequ1( (fPMatrix)(MA), len ) /* identity matrix */
#define cudaMF_equm1( MA, len )                      cudaMFequm1( (fPMatrix)(MA), len ) /* neg. identity matrix */
#define cudaMF_randomLC( MA, ht, len, seed, Min, Max, state ) cudaVF_randomLC( (fPMatrix)(MA), (ht)*(len), seed, Min, Max, state )
#define cudaMF_random( MA, ht, len, seed, Min, Max )          cudaVF_random( (fPMatrix)(MA), (ht)*(len), seed, Min, Max )
#define cusdMF_randomLC( MA, ht, len, seed, d_MinPtr, d_MaxPtr, state ) cusdVF_randomLC( (fPMatrix)(MA), (ht)*(len), seed, d_MinPtr, d_MaxPtr, state )
#define cusdMF_random( MA, ht, len, seed, d_MinPtr, d_MaxPtr )          cusdVF_random( (fPMatrix)(MA), (ht)*(len), seed, d_MinPtr, d_MaxPtr )
#define cudaMF_outerprod( MA, X, Y, ht, len )        cudaMFouterprod( (fPMatrix)(MA), X, Y, ht, len )
                       /* sizX=ht, sizY=len */
#define cudaMF_Row_equ0( MA, ht, len, iRow )    cudaMFRow_equ0( (fPMatrix)(MA), ht, len, iRow )
#define cudaMF_Col_equ0( MA, ht, len, iCol )    cudaMFCol_equ0( (fPMatrix)(MA), ht, len, iCol )
#define cudaMF_Dia_equ0( MA, len )              cudaMFDia_equ0( (fPMatrix)(MA), len )
#define cudaMF_Row_equC( MA, ht, len, iRow, C ) cudaMFRow_equC( (fPMatrix)(MA), ht, len, iRow, C )
#define cudaMF_Col_equC( MA, ht, len, iCol, C ) cudaMFCol_equC( (fPMatrix)(MA), ht, len, iCol, C )
#define cudaMF_Dia_equC( MA, len, C )           cudaMFDia_equC( (fPMatrix)(MA), len, C )
#define cusdMF_Row_equC( MA, ht, len, iRow, d_CPtr ) cusdMFRow_equC( (fPMatrix)(MA), ht, len, iRow, d_CPtr )
#define cusdMF_Col_equC( MA, ht, len, iCol, d_CPtr ) cusdMFCol_equC( (fPMatrix)(MA), ht, len, iCol, d_CPtr )
#define cusdMF_Dia_equC( MA, len, CPtr )           cusdMFDia_equC( (fPMatrix)(MA), len, CPtr )

#define cudaMF_Row_equV( MA, ht, len, iRow, X ) cudaMFRow_equV( (fPMatrix)(MA), ht, len, iRow, X )
#define cudaMF_Col_equV( MA, ht, len, iCol, X ) cudaMFCol_equV( (fPMatrix)(MA), ht, len, iCol, X )
#define cudaMF_Dia_equV( MA, len, X )           cudaMFDia_equV( (fPMatrix)(MA), len, X )

#define cudaMF_Trd_equM( MA, MTrd, len )        cudaMFTrd_equM( (fPMatrix)(MA), (fPMatrix)(MTrd), len )
#define cudaMF_Trd_extract( MTrd, MA, len )     cudaMFTrd_extract( (fPMatrix)(MTrd), (fPMatrix)(MA), len )

#define cudaMF_equM( MB, MA, ht, len )          cudaVF_equV( (fPMatrix)(MB), (fPMatrix)(MA), (ht)*(len) )
#define cudaMF_equMhost( MB, MA, ht, len )      cudaVF_equVhost( (fPMatrix)(MB), MA[0], (ht)*(len) )
#define MF_equMdevice( MB, MA, ht, len )        VF_equVdevice( MB[0], (fPMatrix)(MA), (ht)*(len) )
#define cudaMF_neg( MB, MA, ht, len )           cudaVF_neg( (fPMatrix)(MB), (fPMatrix)(MA), (ht)*(len) )

#define cudaMF_UequL( MA, len ) cudaMFUequL( (fPMatrix)(MA), len )
#define cudaMF_LequU( MA, len ) cudaMFLequU( (fPMatrix)(MA), len )
     /* copy lower-diagonal elements into upper-diagonal
       (or vice versa) by index-reflection, so as to get a symmetric matrix    */

            /* data-type conversions:  */
#define cudaM_DtoF( MF, MD, ht, len ) cudaV_DtoF( (fPMatrix)(MF), (dPMatrix)(MD), (ht)*(len) )
#define cudaM_FtoD( MD, MF, ht, len ) cudaV_FtoD( (dPMatrix)(MD), (fPMatrix)(MF), (ht)*(len) )

            /* suitable windows for MF_spectrum: */
#define cudaMF_Hann( MA, ht, len )     cudaMFHann( (fPMatrix)(MA), ht, len )
#define cudaMF_Hanning( MA, ht, len )  cudaMFHann( (fPMatrix)(MA), ht, len )  /* erroneous name for Hann */
#define cudaMF_Parzen( MA, ht, len )   cudaMFParzen( (fPMatrix)(MA), ht, len )
#define cudaMF_Welch( MA, ht, len )    cudaMFWelch( (fPMatrix)(MA), ht, len )

/********  Extracting a submatrix and copying a submatrix back  *********/

#define cudaMF_submatrix( MSub, subHt, subLen, MSrce, srceHt, srceLen, \
                      firstRowInCol, sampInCol, firstColInRow, sampInRow ) \
               cudaMFsubmatrix(  (fPMatrix)(MSub), subHt, subLen, \
                             (fPMatrix)(MSrce), srceHt, srceLen, \
                             firstRowInCol, sampInCol, firstColInRow, sampInRow )

#define cudaMF_submatrix_equM( MDest, destHt, destLen, \
                           firstRowInCol, sampInCol, firstColInRow, sampInRow, \
                           MSrce, srceHt, srceLen ) \
               cudaMFsubmatrix_equM(  (fPMatrix)(MDest), destHt, destLen, \
                             firstRowInCol, sampInCol, firstColInRow, sampInRow, \
                             (fPMatrix)(MSrce), srceHt, srceLen )

#define cudaMF_equMblock( MSub, subHt, subLen, MSrce, srceHt, srceLen, \
                      firstRowInCol, firstColInRow ) \
               cudaMFequMblock(  (fPMatrix)(MSub), subHt, subLen, \
                             (fPMatrix)(MSrce), srceHt, srceLen, \
                             firstRowInCol, firstColInRow )

#define cudaMF_block_equM( MDest, destHt, destLen, \
                       firstRowInCol, firstColInRow, \
                       MSrce, srceHt, srceLen ) \
               cudaMFblock_equM( (fPMatrix)(MDest), destHt, destLen, \
                             firstRowInCol, firstColInRow, \
                             (fPMatrix)(MSrce), srceHt, srceLen )

#define cudaMF_equMblockT( MSub, subHt, subLen, MSrce, srceHt, srceLen, \
                      firstRowInCol, firstColInRow ) \
               cudaMFequMblockT(  (fPMatrix)(MSub), subHt, subLen, \
                             (fPMatrix)(MSrce), srceHt, srceLen, \
                             firstRowInCol, firstColInRow )

#define cudaMF_block_equMT( MDest, destHt, destLen, \
                       firstRowInCol, firstColInRow, \
                       MSrce, srceHt, srceLen ) \
               cudaMFblock_equMT( (fPMatrix)(MDest), destHt, destLen, \
                             firstRowInCol, firstColInRow, \
                             (fPMatrix)(MSrce), srceHt, srceLen )

/*****   Extracting a single row or a single column or the diagonal  ******
 *       and storing it into a vector                                     */

#define cudaMF_Row_extract( Y, MA, ht, len, iRow ) cudaMFRow_extract( Y, (fPMatrix)(MA), ht, len, iRow )
#define cudaMF_Col_extract( Y, MA, ht, len, iCol ) cudaMFCol_extract( Y, (fPMatrix)(MA), ht, len, iCol )
#define cudaMF_Dia_extract( Y, MA, len )           cudaMFDia_extract( Y, (fPMatrix)(MA), len )

/**************  Deleting or inserting a row or a column   ***************/

#define cudaMF_Row_delete( MB, MA, htA, lenA, iRow )    cudaMFRow_delete( (fPMatrix)(MB), (fPMatrix)(MA), htA, lenA, iRow )
#define cudaMF_Col_delete( MB, MA, htA, lenA, iCol )    cudaMFCol_delete( (fPMatrix)(MB), (fPMatrix)(MA), htA, lenA, iCol )
#define cudaMF_Row_insert( MB, MA, htB, lenB, iRow, X ) cudaMFRow_insert( (fPMatrix)(MB), (fPMatrix)(MA), htB, lenB, iRow, X )
#define cudaMF_Col_insert( MB, MA, htB, lenB, iCol, X ) cudaMFCol_insert( (fPMatrix)(MB), (fPMatrix)(MA), htB, lenB, iCol, X )


/*****************    Basic arithmetic operations *********************
                      performed on one single row,
                      or one single column of any matrix,
                      or on the diagonal of a square matrix

    Note: In contrast to the analogous VectorLib functions, the operations
    are performed in-place, i.e. the input matrix itself is changed  */

#define cudaMF_Row_neg( MA, ht, len, iRow ) cudaMFRow_neg( (fPMatrix)(MA), ht, len, iRow )
#define cudaMF_Col_neg( MA, ht, len, iCol ) cudaMFCol_neg( (fPMatrix)(MA), ht, len, iCol )

#define cudaMF_Row_addC( MA, ht, len, iRow, C )      cudaMFRow_addC( (fPMatrix)(MA), ht, len, iRow, C )
#define cudaMF_Col_addC( MA, ht, len, iCol, C )      cudaMFCol_addC( (fPMatrix)(MA), ht, len, iCol, C )
#define cudaMF_Dia_addC( MA, len, C )                cudaMFDia_addC( (fPMatrix)(MA), len, C )
#define cusdMF_Row_addC( MA, ht, len, iRow, d_CPtr ) cusdMFRow_addC( (fPMatrix)(MA), ht, len, iRow, d_CPtr )
#define cusdMF_Col_addC( MA, ht, len, iCol, d_CPtr ) cusdMFCol_addC( (fPMatrix)(MA), ht, len, iCol, d_CPtr )
#define cusdMF_Dia_addC( MA, len, d_CPtr )           cusdMFDia_addC( (fPMatrix)(MA), len, d_CPtr )

#define cudaMF_Row_addV( MA, ht, len, iRow, X )      cudaMFRow_addV( (fPMatrix)(MA), ht, len, iRow, X )
#define cudaMF_Col_addV( MA, ht, len, iCol, X )      cudaMFCol_addV( (fPMatrix)(MA), ht, len, iCol, X )
#define cudaMF_Dia_addV( MA, len, X )                cudaMFDia_addV( (fPMatrix)(MA), len, X )

#define cudaMF_Row_subC( MA, ht, len, iRow, C )      cudaMFRow_subC( (fPMatrix)(MA), ht, len, iRow, C )
#define cudaMF_Col_subC( MA, ht, len, iCol, C )      cudaMFCol_subC( (fPMatrix)(MA), ht, len, iCol, C )
#define cudaMF_Dia_subC( MA, len, C )                cudaMFDia_subC( (fPMatrix)(MA), len, C )
#define cusdMF_Row_subC( MA, ht, len, iRow, d_CPtr ) cusdMFRow_subC( (fPMatrix)(MA), ht, len, iRow, d_CPtr )
#define cusdMF_Col_subC( MA, ht, len, iCol, d_CPtr ) cusdMFCol_subC( (fPMatrix)(MA), ht, len, iCol, d_CPtr )
#define cusdMF_Dia_subC( MA, len, d_CPtr )           cusdMFDia_subC( (fPMatrix)(MA), len, d_CPtr )

#define cudaMF_Row_subV( MA, ht, len, iRow, X )      cudaMFRow_subV( (fPMatrix)(MA), ht, len, iRow, X )
#define cudaMF_Col_subV( MA, ht, len, iCol, X )      cudaMFCol_subV( (fPMatrix)(MA), ht, len, iCol, X )
#define cudaMF_Dia_subV( MA, len, X )                cudaMFDia_subV( (fPMatrix)(MA), len, X )

#define cudaMF_Row_subrC( MA, ht, len, iRow, C )      cudaMFRow_subrC( (fPMatrix)(MA), ht, len, iRow, C )
#define cudaMF_Col_subrC( MA, ht, len, iCol, C )      cudaMFCol_subrC( (fPMatrix)(MA), ht, len, iCol, C )
#define cudaMF_Dia_subrC( MA, len, C )                cudaMFDia_subrC( (fPMatrix)(MA), len, C )
#define cusdMF_Row_subrC( MA, ht, len, iRow, d_CPtr ) cusdMFRow_subrC( (fPMatrix)(MA), ht, len, iRow, d_CPtr )
#define cusdMF_Col_subrC( MA, ht, len, iCol, d_CPtr ) cusdMFCol_subrC( (fPMatrix)(MA), ht, len, iCol, d_CPtr )
#define cusdMF_Dia_subrC( MA, len, d_CPtr )           cusdMFDia_subrC( (fPMatrix)(MA), len, d_CPtr )

#define cudaMF_Row_subrV( MA, ht, len, iRow, X )      cudaMFRow_subrV( (fPMatrix)(MA), ht, len, iRow, X )
#define cudaMF_Col_subrV( MA, ht, len, iCol, X )      cudaMFCol_subrV( (fPMatrix)(MA), ht, len, iCol, X )
#define cudaMF_Dia_subrV( MA, len, X )                cudaMFDia_subrV( (fPMatrix)(MA), len, X )

#define cudaMF_Row_mulC( MA, ht, len, iRow, C )      cudaMFRow_mulC( (fPMatrix)(MA), ht, len, iRow, C )
#define cudaMF_Col_mulC( MA, ht, len, iCol, C )      cudaMFCol_mulC( (fPMatrix)(MA), ht, len, iCol, C )
#define cudaMF_Dia_mulC( MA, len, C )                cudaMFDia_mulC( (fPMatrix)(MA), len, C )
#define cusdMF_Row_mulC( MA, ht, len, iRow, d_CPtr ) cusdMFRow_mulC( (fPMatrix)(MA), ht, len, iRow, d_CPtr )
#define cusdMF_Col_mulC( MA, ht, len, iCol, d_CPtr ) cusdMFCol_mulC( (fPMatrix)(MA), ht, len, iCol, d_CPtr )
#define cusdMF_Dia_mulC( MA, len, d_CPtr )           cusdMFDia_mulC( (fPMatrix)(MA), len, d_CPtr )

#define cudaMF_Row_mulV( MA, ht, len, iRow, X )      cudaMFRow_mulV( (fPMatrix)(MA), ht, len, iRow, X )
#define cudaMF_Col_mulV( MA, ht, len, iCol, X )      cudaMFCol_mulV( (fPMatrix)(MA), ht, len, iCol, X )
#define cudaMF_Dia_mulV( MA, len, X )                cudaMFDia_mulV( (fPMatrix)(MA), len, X )

#define cudaMF_Row_divC( MA, ht, len, iRow, C )      cudaMFRow_divC( (fPMatrix)(MA), ht, len, iRow, C )
#define cudaMF_Col_divC( MA, ht, len, iCol, C )      cudaMFCol_divC( (fPMatrix)(MA), ht, len, iCol, C )
#define cudaMF_Dia_divC( MA, len, C )                cudaMFDia_divC( (fPMatrix)(MA), len, C )
#define cusdMF_Row_divC( MA, ht, len, iRow, d_CPtr ) cusdMFRow_divC( (fPMatrix)(MA), ht, len, iRow, d_CPtr )
#define cusdMF_Col_divC( MA, ht, len, iCol, d_CPtr ) cusdMFCol_divC( (fPMatrix)(MA), ht, len, iCol, d_CPtr )
#define cusdMF_Dia_divC( MA, len, d_CPtr )           cusdMFDia_divC( (fPMatrix)(MA), len, d_CPtr )

#define cudaMF_Row_divV( MA, ht, len, iRow, X )      cudaMFRow_divV( (fPMatrix)(MA), ht, len, iRow, X )
#define cudaMF_Col_divV( MA, ht, len, iCol, X )      cudaMFCol_divV( (fPMatrix)(MA), ht, len, iCol, X )
#define cudaMF_Dia_divV( MA, len, X )                cudaMFDia_divV( (fPMatrix)(MA), len, X )

#define cudaMF_Row_divrC( MA, ht, len, iRow, C )      cudaMFRow_divrC( (fPMatrix)(MA), ht, len, iRow, C )
#define cudaMF_Col_divrC( MA, ht, len, iCol, C )      cudaMFCol_divrC( (fPMatrix)(MA), ht, len, iCol, C )
#define cudaMF_Dia_divrC( MA, len, C )                cudaMFDia_divrC( (fPMatrix)(MA), len, C )
#define cusdMF_Row_divrC( MA, ht, len, iRow, d_CPtr ) cusdMFRow_divrC( (fPMatrix)(MA), ht, len, iRow, d_CPtr )
#define cusdMF_Col_divrC( MA, ht, len, iCol, d_CPtr ) cusdMFCol_divrC( (fPMatrix)(MA), ht, len, iCol, d_CPtr )
#define cusdMF_Dia_divrC( MA, len, d_CPtr )           cusdMFDia_divrC( (fPMatrix)(MA), len, d_CPtr )

#define cudaMF_Row_divrV( MA, ht, len, iRow, X )      cudaMFRow_divrV( (fPMatrix)(MA), ht, len, iRow, X )
#define cudaMF_Col_divrV( MA, ht, len, iCol, X )      cudaMFCol_divrV( (fPMatrix)(MA), ht, len, iCol, X )
#define cudaMF_Dia_divrV( MA, len, X )                cudaMFDia_divrV( (fPMatrix)(MA), len, X )


/******  One-dimensional vector operations **********************
         performed along all rows or all columns simultaneously,
         or along the diagonal of a square matrix                */

#define cudaMF_Rows_max( Y, MA, ht, len )        cudaMFRows_max( Y, (fPMatrix)(MA), ht, len )
#define cudaMF_Cols_max( Y, MA, ht, len )        cudaMFCols_max( Y, (fPMatrix)(MA), ht, len )
#define cudaMF_Dia_max(  h_RetValPtr, MA, len )  cudaMFDia_max(  h_RetValPtr, (fPMatrix)(MA), len )
#define cusdMF_Dia_max(  d_RetValPtr, MA, len )  cusdMFDia_max(  d_RetValPtr, (fPMatrix)(MA), len )
#define cudaMF_Rows_min( Y, MA, ht, len )        cudaMFRows_min( Y, (fPMatrix)(MA), ht, len )
#define cudaMF_Cols_min( Y, MA, ht, len )        cudaMFCols_min( Y, (fPMatrix)(MA), ht, len )
#define cudaMF_Dia_min(  h_RetValPtr, MA, len )  cudaMFDia_min(  h_RetValPtr, (fPMatrix)(MA), len )
#define cusdMF_Dia_min(  d_RetValPtr, MA, len )  cusdMFDia_min(  d_RetValPtr, (fPMatrix)(MA), len )

#define cudaMF_Rows_absmax( Y, MA, ht, len )       cudaMFRows_absmax( Y, (fPMatrix)(MA), ht, len )
#define cudaMF_Cols_absmax( Y, MA, ht, len )       cudaMFCols_absmax( Y, (fPMatrix)(MA), ht, len )
#define cudaMF_Dia_absmax(  h_RetValPtr, MA, len ) cudaMFDia_absmax(  h_RetValPtr, (fPMatrix)(MA), len )
#define cusdMF_Dia_absmax(  d_RetValPtr, MA, len ) cusdMFDia_absmax(  d_RetValPtr, (fPMatrix)(MA), len )
#define cudaMF_Rows_absmin( Y, MA, ht, len )       cudaMFRows_absmin( Y, (fPMatrix)(MA), ht, len )
#define cudaMF_Cols_absmin( Y, MA, ht, len )       cudaMFCols_absmin( Y, (fPMatrix)(MA), ht, len )
#define cudaMF_Dia_absmin(  h_RetValPtr, MA, len ) cudaMFDia_absmin(  h_RetValPtr, (fPMatrix)(MA), len )
#define cusdMF_Dia_absmin(  d_RetValPtr, MA, len ) cusdMFDia_absmin(  d_RetValPtr, (fPMatrix)(MA), len )

#define cudaMF_Rows_sum( Y, MA, ht, len )          cudaMFRows_sum( Y, (fPMatrix)(MA), ht, len )
#define cudaMF_Cols_sum( Y, MA, ht, len )          cudaMFCols_sum( Y, (fPMatrix)(MA), ht, len )
#define cudaMF_Dia_sum(  h_RetValPtr, MA, len )    cudaMFDia_sum(  h_RetValPtr, (fPMatrix)(MA), len )
#define cusdMF_Dia_sum(  d_RetValPtr, MA, len )    cusdMFDia_sum(  d_RetValPtr, (fPMatrix)(MA), len )
#define cudaMF_Rows_ssq( Y, MA, ht, len )          cudaMFRows_ssq( Y, (fPMatrix)(MA), ht, len )
#define cudaMF_Cols_ssq( Y, MA, ht, len )          cudaMFCols_ssq( Y, (fPMatrix)(MA), ht, len )
#define cudaMF_Dia_ssq(  h_RetValPtr, MA, len )    cudaMFDia_ssq(  h_RetValPtr, (fPMatrix)(MA), len )
#define cusdMF_Dia_ssq(  d_RetValPtr, MA, len )    cusdMFDia_ssq(  d_RetValPtr, (fPMatrix)(MA), len )
#define cudaMF_Rows_prod( Y, MA, ht, len )         cudaMFRows_prod( Y, (fPMatrix)(MA), ht, len )
#define cudaMF_Cols_prod( Y, MA, ht, len )         cudaMFCols_prod( Y, (fPMatrix)(MA), ht, len )
#define cudaMF_Dia_prod(  h_RetValPtr, MA, len )   cudaMFDia_prod(  h_RetValPtr, (fPMatrix)(MA), len )
#define cusdMF_Dia_prod(  d_RetValPtr, MA, len )   cusdMFDia_prod(  d_RetValPtr, (fPMatrix)(MA), len )

#define cudaMF_Rows_runsum( MA, ht, len )     cudaMFRows_runsum( (fPMatrix)(MA), ht, len )
#define cudaMF_Cols_runsum( MA, ht, len )     cudaMFCols_runsum( (fPMatrix)(MA), ht, len )
#define cudaMF_Rows_runprod( MA, ht, len )    cudaMFRows_runprod( (fPMatrix)(MA), ht, len )
#define cudaMF_Cols_runprod( MA, ht, len )    cudaMFCols_runprod( (fPMatrix)(MA), ht, len )

#define cudaMF_Rows_rotate( MA, ht, len, pos)           cudaMFRows_rotate( (fPMatrix)(MA), ht, len, pos )
#define cudaMF_Cols_rotate( MA, ht, len, pos)           cudaMFCols_rotate( (fPMatrix)(MA), ht, len, pos )
#define cudaMF_Rows_rotate_buf( MA, ht, len, pos, MBuf) cudaMFRows_rotate_buf( (fPMatrix)(MA), ht, len, pos, (fPMatrix)(MBuf) )
#define cudaMF_Cols_rotate_buf( MA, ht, len, pos, MBuf) cudaMFCols_rotate_buf( (fPMatrix)(MA), ht, len, pos, (fPMatrix)(MBuf) )
#define cudaMF_Rows_reflect( MA, ht, len )              cudaMFRows_reflect( (fPMatrix)(MA), ht, len )
#define cudaMF_Cols_reflect( MA, ht, len )              cudaMFCols_reflect( (fPMatrix)(MA), ht, len )
#define cudaMF_Rows_rev( MA, ht, len)                   cudaMFRows_rev( (fPMatrix)(MA), ht, len )
#define cudaMF_Cols_rev( MA, ht, len)                   cudaMFCols_rev( (fPMatrix)(MA), ht, len )
#define cudaMF_Rows_distribution( MAbund, Limits, nBins, MX, ht, len, mode ) cudaMFRows_distribution( (uiPMatrix)MAbund, Limits, nBins, (fPMatrix)MX, ht, len, mode )
#define cudaMF_Cols_distribution( MAbund, Limits, nBins, MX, ht, len, mode ) cudaMFCols_distribution( (uiPMatrix)MAbund, Limits, nBins, (fPMatrix)MX, ht, len, mode )

/********  Operations involving two rows or two colums of one matrix  *****/

#define cudaMF_Rows_exchange( MA, ht, len, row1, row2 ) \
                             cudaMFRows_exchange( (fPMatrix)(MA), ht, len, row1, row2 )
#define cudaMF_Cols_exchange( MA, ht, len, col1, col2 ) \
                             cudaMFCols_exchange( (fPMatrix)(MA), ht, len, col1, col2 )

#define cudaMF_Rows_add( MA, ht, len, destRow, srceRow ) \
                             cudaMFRows_add( (fPMatrix)(MA), ht, len, destRow, srceRow )
#define cudaMF_Cols_add( MA, ht, len, destCol, srceCol ) \
                             cudaMFCols_add( (fPMatrix)(MA), ht, len, destCol, srceCol )
                         /* dest[i] += source[i]  */

#define cudaMF_Rows_sub( MA, ht, len, destRow, srceRow ) \
                             cudaMFRows_sub( (fPMatrix)(MA), ht, len, destRow, srceRow )
#define cudaMF_Cols_sub( MA, ht, len, destCol, srceCol ) \
                             cudaMFCols_sub( (fPMatrix)(MA), ht, len, destCol, srceCol )
                         /* dest[i] -= source[i]  */

#define cudaMF_Rows_Cadd( MA, ht, len, destRow, srceRow, C ) \
                          cudaMFRows_Cadd( (fPMatrix)(MA), ht, len, destRow, srceRow, C )
#define cudaMF_Cols_Cadd( MA, ht, len, destCol, srceCol, C ) \
                          cudaMFCols_Cadd( (fPMatrix)(MA), ht, len, destCol, srceCol, C )
#define cusdMF_Rows_Cadd( MA, ht, len, destRow, srceRow, d_CPtr ) \
                          cusdMFRows_Cadd( (fPMatrix)(MA), ht, len, destRow, srceRow, d_CPtr )
#define cusdMF_Cols_Cadd( MA, ht, len, destCol, srceCol, d_CPtr ) \
                          cusdMFCols_Cadd( (fPMatrix)(MA), ht, len, destCol, srceCol, d_CPtr )
                         /* dest[i] += C * source[i]  */

#define cudaMF_Rows_lincomb( MA, ht, len, destRow, destC, srceRow, srceC ) \
            cudaMFRows_lincomb( (fPMatrix)(MA), ht, len, destRow, destC, srceRow, srceC )
#define cudaMF_Cols_lincomb( MA, ht, len, destCol, destC, srceCol, srceC ) \
            cudaMFCols_lincomb( (fPMatrix)(MA), ht, len, destCol, destC, srceCol, srceC )
#define cusdMF_Rows_lincomb( MA, ht, len, destRow, d_destCPtr, srceRow, d_srceCPtr ) \
            cusdMFRows_lincomb( (fPMatrix)(MA), ht, len, destRow, d_destCPtr, srceRow, d_srceCPtr )
#define cusdMF_Cols_lincomb( MA, ht, len, destCol, d_destCPtr, srceCol, d_srceCPtr ) \
            cusdMFCols_lincomb( (fPMatrix)(MA), ht, len, destCol, d_destCPtr, srceCol, d_srceCPtr )
  /*  linear combination: dest[i] = destC * dest[i] + sourceC * source[i] */


/*********************  Center of gravity *****************************/
#define cudaMF_centerOfGravityInd( h_RetValPtr, MA, ht, len ) \
            cudaMFcenterOfGravityInd( h_RetValPtr, (fPMatrix)(MA), ht, len )
#define cudaMF_centerOfGravityV( h_RetValPtr, X, Y, MA, ht, len ) \
            cudaMFcenterOfGravityV( h_RetValPtr, X, Y, (fPMatrix)(MA), ht, len )
#define cusdMF_centerOfGravityInd( d_RetValPtr, MA, ht, len ) \
            cusdMFcenterOfGravityInd( d_RetValPtr, (fPMatrix)(MA), ht, len )
#define cusdMF_centerOfGravityV( d_RetValPtr, X, Y, MA, ht, len ) \
            cusdMFcenterOfGravityV( d_RetValPtr, X, Y, (fPMatrix)(MA), ht, len )

/*************** Transposing and rotating a matrix **********************/

#define cudaMF_transpose( MTr, MA, htTr, lenTr )    cudaMFtranspose( (fPMatrix)(MTr), (fPMatrix)(MA), htTr, lenTr )
       /*  dimensions htTr, lenTr are those of the transposed matrix, not of the original!   */
#define cudaMF_rotate90( MRot, MA, htRot, lenRot )  cudaMFrotate90( (fPMatrix)(MRot), (fPMatrix)(MA), htRot, lenRot )
#define cudaMF_rotate180( MRot, MA, htRot, lenRot ) cudaVF_rev( (fPMatrix)(MRot), (fPMatrix)(MA), (htRot)*(lenRot) )
#define cudaMF_rotate270( MRot, MA, htRot, lenRot ) cudaMFrotate270( (fPMatrix)(MRot), (fPMatrix)(MA), htRot, lenRot )
#define cudaMF_transpose_buf( MTr, MA, htTr, lenTr, MBuf )  cudaMFtranspose_buf( (fPMatrix)(MTr), (fPMatrix)(MA), htTr, lenTr, (fPMatrix)(MBuf) )

/********************** Interpolation of Matrix elements **************/

#define cudaMF_polyinterpol( MZ, X, Y, ht, len, XTab, YTab, MZTab, httab, lentab, degX, degY ) \
             cudaMFpolyinterpol( (fPMatrix)(MZ), X, Y, ht, len, XTab, YTab, (fPMatrix)(MZTab), httab, lentab, degX, degY )
#define cudaMF_ratinterpol( MZ, X, Y, ht, len, XTab, YTab, MZTab, httab, lentab, degX, degY ) \
             cudaMFratinterpol( (fPMatrix)(MZ), X, Y, ht, len, XTab, YTab, (fPMatrix)(MZTab), httab, lentab, degX, degY )
#define cudaMF_natCubSplineInterpol( MZ, X, Y, ht, len, XTab, YTab, MZTab, httab, lentab ) \
             cudaMFnatCubSplineInterpol( (fPMatrix)(MZ), X, Y, ht, len, XTab, YTab, (fPMatrix)(MZTab), httab, lentab )


/************************ Matrix Arithmetics *************************/

#define cudaMF_addM( MC, MA, MB, htA, lenA )   cudaVF_addV( (fPMatrix)(MC), (fPMatrix)(MA), (fPMatrix)(MB), (htA)*(lenA) )
#define cudaMF_addMT( MC, MA, MB, htA, lenA )  cudaMFaddMT( (fPMatrix)(MC), (fPMatrix)(MA), (fPMatrix)(MB), htA, lenA )
#define cudaMF_subM( MC, MA, MB, htA, lenA )   cudaVF_subV( (fPMatrix)(MC), (fPMatrix)(MA), (fPMatrix)(MB), (htA)*(lenA) )
#define cudaMF_subMT( MC, MA, MB, htA, lenA )  cudaMFsubMT( (fPMatrix)(MC), (fPMatrix)(MA), (fPMatrix)(MB), htA, lenA )
#define cudaMF_subrMT( MC, MA, MB, htA, lenA ) cudaMFsubrMT( (fPMatrix)(MC), (fPMatrix)(MA), (fPMatrix)(MB), htA, lenA )
#define cudaMF_mulC( MB, MA, htA, lenA, C )    cudaVF_mulC( (fPMatrix)(MB), (fPMatrix)(MA), (htA)*(lenA), C )
#define cudaMF_divC( MB, MA, htA, lenA, C )    cudaVF_divC( (fPMatrix)(MB), (fPMatrix)(MA), (htA)*(lenA), C )
#define cusdMF_mulC( MB, MA, htA, lenA, CPtr ) cusdVF_mulC( (fPMatrix)(MB), (fPMatrix)(MA), (htA)*(lenA), CPtr )
#define cusdMF_divC( MB, MA, htA, lenA, CPtr ) cusdVF_divC( (fPMatrix)(MB), (fPMatrix)(MA), (htA)*(lenA), CPtr )

#define cudaMFs_addM( MC, MA, MB, htA, lenA, C )      cudaVFs_addV( (fPMatrix)(MC), (fPMatrix)(MA), (fPMatrix)(MB), (htA)*(lenA), C )
#define cudaMFs_addMT( MC, MA, MB, htA, lenA, C )     cudaMFsaddMT( (fPMatrix)(MC), (fPMatrix)(MA), (fPMatrix)(MB), htA, lenA, C )
#define cusdMFs_addM( MC, MA, MB, htA, lenA, CPtr )   cusdVFs_addV( (fPMatrix)(MC), (fPMatrix)(MA), (fPMatrix)(MB), (htA)*(lenA), CPtr )
#define cusdMFs_addMT( MC, MA, MB, htA, lenA, CPtr )  cusdMFsaddMT( (fPMatrix)(MC), (fPMatrix)(MA), (fPMatrix)(MB), htA, lenA, CPtr )
#define cudaMFs_subM( MC, MA, MB, htA, lenA, C )      cudaVFs_subV( (fPMatrix)(MC), (fPMatrix)(MA), (fPMatrix)(MB), (htA)*(lenA), C )
#define cudaMFs_subMT( MC, MA, MB, htA, lenA, C )     cudaMFssubMT( (fPMatrix)(MC), (fPMatrix)(MA), (fPMatrix)(MB), htA, lenA, C )
#define cusdMFs_subM( MC, MA, MB, htA, lenA, CPtr )   cusdVFs_subV( (fPMatrix)(MC), (fPMatrix)(MA), (fPMatrix)(MB), (htA)*(lenA), CPtr )
#define cusdMFs_subMT( MC, MA, MB, htA, lenA, CPtr )  cusdMFssubMT( (fPMatrix)(MC), (fPMatrix)(MA), (fPMatrix)(MB), htA, lenA, CPtr )
#define cudaMFs_subrMT( MC, MA, MB, htA, lenA, C )    cudaMFssubrMT( (fPMatrix)(MC), (fPMatrix)(MA), (fPMatrix)(MB), htA, lenA, C )
#define cusdMFs_subrMT( MC, MA, MB, htA, lenA, CPtr ) cusdMFssubrMT( (fPMatrix)(MC), (fPMatrix)(MA), (fPMatrix)(MB), htA, lenA, CPtr )
#define cudaMF_lincomb( MC, MA, MB, htA, lenA, CA, CB )       cudaVF_lincomb( (fPMatrix)(MC), (fPMatrix)(MA), (fPMatrix)(MB), (htA)*(lenA), CA,    CB )
#define cusdMF_lincomb( MC, MA, MB, htA, lenA, CAPtr, CBPtr ) cusdVF_lincomb( (fPMatrix)(MC), (fPMatrix)(MA), (fPMatrix)(MB), (htA)*(lenA), CAPtr, CBPtr )

#define cudaMF_mulV( Y, MA, X, htA, lenA )    cudaMFmulV( Y, (fPMatrix)(MA), X, htA, lenA )
             /*  Y = MA * X.  sizX=lenA, sizY=htA;   both X and Y are column-vectors    */
#define cudaMF_TmulV( Y, MA, X, htA, lenA )   cudaMFTmulV( Y, (fPMatrix)(MA), X, htA, lenA )
            /*  Y = MAT * X.  sizX=htA, sizY=lenA;   both X and Y are column-vectors    */
#define cudaVF_mulM( Y, X, MA, htA, lenA )    cudaVFmulM( Y, X, (fPMatrix)(MA), htA, lenA )
            /*  Y = X * MA.  sizX=htA, sizY=lenA;    both X and Y are row-vectors.
                             Mind the prefix: cudaVF_ (not cudaMF_)    */
#define cudaVF_mulMT( Y, X, MA, htA, lenA )    cudaVFmulMT( Y, X, (fPMatrix)(MA), htA, lenA )
            /*  Y = X * MAT.  sizX=lenA, sizY=htA;   both X and Y are row-vectors.   */
#define cudaMF_mulM( MC, MA, MB, htA, lenA, lenB )  cudaMFmulM( (fPMatrix)(MC), (fPMatrix)(MA), (fPMatrix)(MB), htA, lenA, lenB )
                         /*  MC = MA * MB.  htB=lenA, htC=htA, lenC=lenB */
#define cudaMF_mulMT( MC, MA, MB, htA, lenA, htB )  cudaMFmulMT( (fPMatrix)(MC), (fPMatrix)(MA), (fPMatrix)(MB), htA, lenA, htB )
                         /*  MC = MA * MBT.  lenB=lenA, htC=htA, lenC=htB */
#define cudaMF_TmulM( MC, MA, MB, htA, lenA, lenB ) cudaMFTmulM( (fPMatrix)(MC), (fPMatrix)(MA), (fPMatrix)(MB), htA, lenA, lenB )
                         /*  MC = MAT * MB.  htB=htA, htC=lenA, lenC=lenB */
#define cudaMF_TmulMT( MC, MA, MB, htA, lenA, htB ) cudaMFTmulMT( (fPMatrix)(MC), (fPMatrix)(MA), (fPMatrix)(MB), htA, lenA, htB )
                         /*  MC = MAT * MBT.  lenB=htA, htC=lenA, lenC=htB */
#define cudaMFdia_mulM(  MC, MADia, MB, htB, lenB )  cudaMFdiamulM(  (fPMatrix)(MC), MADia, (fPMatrix)(MB), htB, lenB )
#define cudaMFdia_mulMT( MC, MADia, MB, htB, lenB )  cudaMFdiamulMT( (fPMatrix)(MC), MADia, (fPMatrix)(MB), htB, lenB )
#define cudaMF_mulMdia(  MC, MA, MBDia, htA, lenA )  cudaMFmulMdia(  (fPMatrix)(MC), (fPMatrix)(MA), MBDia, htA, lenA )
#define cudaMF_TmulMdia( MC, MA, MBDia, htA, lenA )  cudaMFTmulMdia( (fPMatrix)(MC), (fPMatrix)(MA), MBDia, htA, lenA )

/***************** Two-Dimensional Fourier-Transform Methods ************/

#define cudaMF_FFT( MY, MX, ht, len, dir )     cudaMFFFT( (fPMatrix)(MY), (fPMatrix)(MX), ht, len, dir )
#define cudaMF_Rows_FFT( MY, MX, ht, len, dir) cudaMFRows_FFT( (fPMatrix)(MY), (fPMatrix)(MX), ht, len, dir )
#define cudaMF_Cols_FFT( MY, MX, ht, len, dir) cudaMFCols_FFT( (fPMatrix)(MY), (fPMatrix)(MX), ht, len, dir )
#define cudaMF_FFTtoC( MY, MX, ht, len )       cudaMFFFTtoC( (cfPMatrix)(MY), (fPMatrix)(MX), ht, len )
#define cudaMF_Rows_FFTtoC( MY, MX, ht, len )  cudaMFRows_FFTtoC( (cfPMatrix)(MY), (fPMatrix)(MX), ht, len )
#define cudaMF_Cols_FFTtoC( MY, MX, ht, len )  cudaMFCols_FFTtoC( (cfPMatrix)(MY), (fPMatrix)(MX), ht, len )
#define cudaMF_convolve( MY, MFlt, MX, MRsp, ht, len ) \
                  cudaMFconvolve( (fPMatrix)(MY), (fPMatrix)(MFlt), (fPMatrix)(MX), (fPMatrix)(MRsp), ht, len )
#define cudaMF_deconvolve( MY, MFlt, MX, MRsp, ht, len ) \
                  cudaMFdeconvolve( (fPMatrix)(MY), (fPMatrix)(MFlt), (fPMatrix)(MX), (fPMatrix)(MRsp), ht, len )
#define cudaMF_filter( MY, MX, MFlt, ht, len ) cudaMFfilter( (fPMatrix)(MY), (fPMatrix)(MX), (fPMatrix)(MFlt), ht, len )
#define cudaMF_autocorr( MACorr, MX, ht, len ) cudaMFautocorr( (fPMatrix)(MACorr), (fPMatrix)(MX), ht, len )
#define cudaMF_xcorr( MXCorr, MX, MY, ht, len) cudaMFxcorr( (fPMatrix)(MXCorr), (fPMatrix)(MX), (fPMatrix)(MY), ht, len )
#define cudaMF_spectrum( MSpec, htSpec, lenSpec, MX, htX, lenX, MWin ) \
              cudaMFspectrum( (fPMatrix)(MSpec), htSpec, lenSpec, (fPMatrix)(MX), htX, lenX, (fPMatrix)(MWin) )
              /*   htSpec, lenSpec must be 2**n,
                   MSpec must be a (htSpec+1)*(lenSpec+1) matrix!!
                   htX >= n*htSpec,  lenX >= n*lenSpec,
                   htWin = 2*htSpec, lenWin = 2*lenSpec */

/**************************  Input and Output  **************************
	The input/output functions involve memory transfers from device
	to host memory or vice versa. The generic cudaMF_input/output functions
	allocate their own host buffers, whereas the cudaMF_xxx_buf functions
	take a user-supplied buffer vector h_Wk (size must be >= ht*len )
	and are much more efficient.                                       */

#define cudaMF_fprint( stream, MA, ht, len, linewidth ) \
                    cudaMFfprint( stream, (fPMatrix)(MA), ht, len, linewidth )
#define cudaMF_print( MA, ht, len )  cudaMFfprint( stdout, (fPMatrix)(MA), ht, len, 80 )
#define cudaMF_cprint( MA, ht, len ) cudaMFcprint( (fPMatrix)(MA), ht, len )
#define cudaMF_fprint_buf( stream, MA, ht, len, linewidth, h_Wk ) \
                    cudaMFfprint_buf( stream, (fPMatrix)(MA), ht, len, linewidth, h_Wk )
#define cudaMF_print_buf( MA, ht, len )  cudaMFfprint_buf( stdout, (fPMatrix)(MA), ht, len, 80, h_Wk )
#define cudaMF_cprint_buf( MA, ht, len ) cudaMFcprint_buf( (fPMatrix)(MA), ht, len, h_Wk )
  /*  cudaMF_print, cudaMF_cprint usable only for console applications! */
#define cudaMF_write( str, MA, ht, len )   cudaMFwrite( str, (fPMatrix)(MA), ht, len )
#define cudaMF_read( MA, ht, len, str )    cudaMFread( (fPMatrix)(MA), ht, len, str )
#define cudaMF_write_buf( str, MA, ht, len, h_Wk )   cudaMFwrite_buf( str, (fPMatrix)(MA), ht, len, h_Wk )
#define cudaMF_read_buf( MA, ht, len, str, h_Wk )    cudaMFread_buf( (fPMatrix)(MA), ht, len, str, h_Wk )
                                   /* write and read in ascii format */
#define cudaMF_store( str, MA, ht, len )   cudaVF_store( str, (fPMatrix)(MA), (len)*(ht) )
#define cudaMF_recall( MA, ht, len, str)   cudaVF_recall( (fPMatrix)(MA), (len)*(ht), str)
#define cudaMF_store_buf( str, MA, ht, len, h_Wk )   cudaVF_store_buf( str, (fPMatrix)(MA), (len)*(ht), h_Wk )
#define cudaMF_recall_buf( MA, ht, len, str, h_Wk)   cudaVF_recall_buf( (fPMatrix)(MA), (len)*(ht), str, h_Wk )
                                  /* store and recall in binary format */

#endif /* plain-C or C++ for functions working on device memory  */


/*******************  Functions working on host memory: **********************
 *                                                                           *
 *	MFcu_func		(working on matrices in host memory, input type fMatrix, *
 *	scalar parameters on host and passed by value)                           *
 *****************************************************************************/ 

 /****************  Initialization  ****************************************/

#define MFcu_equ0( MA, ht, len )                   VFcu_equ0( (MA)[0], (ht)*(len) )
#define MFcu_equ1( MA, len )                       MFcuequ1( (MA)[0], len ) /* identity matrix */
#define MFcu_equm1( MA, len )                      MFcuequm1( (MA)[0], len ) /* neg. identity matrix */
#define MFcu_randomLC( MA, ht, len, seed, Min, Max, state ) VFcu_randomLC( (MA)[0], (ht)*(len), seed, Min, Max, state )
#define MFcu_random( MA, ht, len, seed, Min, Max )          VFcu_random( (MA)[0], (ht)*(len), seed, Min, Max )
#define MFcu_outerprod( MA, X, Y, ht, len )        MFcuouterprod( (MA)[0], X, Y, ht, len )
                       /* sizX=ht, sizY=len */
#define MFcu_Row_equ0( MA, ht, len, iRow )    MFcuRow_equ0( (MA)[0], ht, len, iRow )
#define MFcu_Col_equ0( MA, ht, len, iCol )    MFcuCol_equ0( (MA)[0], ht, len, iCol )
#define MFcu_Dia_equ0( MA, len )              MFcuDia_equ0( (MA)[0], len )
#define MFcu_Row_equC( MA, ht, len, iRow, C ) MFcuRow_equC( (MA)[0], ht, len, iRow, C )
#define MFcu_Col_equC( MA, ht, len, iCol, C ) MFcuCol_equC( (MA)[0], ht, len, iCol, C )
#define MFcu_Dia_equC( MA, len, C )           MFcuDia_equC( (MA)[0], len, C )

#define MFcu_Row_equV( MA, ht, len, iRow, X ) MFcuRow_equV( (MA)[0], ht, len, iRow, X )
#define MFcu_Col_equV( MA, ht, len, iCol, X ) MFcuCol_equV( (MA)[0], ht, len, iCol, X )
#define MFcu_Dia_equV( MA, len, X )           MFcuDia_equV( (MA)[0], len, X )

#define MFcu_Trd_equM( MA, MTrd, len )        MFcuTrd_equM( (MA)[0], (MTrd)[0], len )
#define MFcu_Trd_extract( MTrd, MA, len )     MFcuTrd_extract( (MTrd)[0], (MA)[0], len )

#define MFcu_equM( MB, MA, ht, len )          VFcu_equV( (MB)[0], (MA)[0], (ht)*(len) )
#define MFcu_equMhost( MB, MA, ht, len )      VFcu_equVhost( (MB)[0], MA[0], (ht)*(len) )
#define MFcu_neg( MB, MA, ht, len )           VFcu_neg( (MB)[0], (MA)[0], (ht)*(len) )

#define MFcu_UequL( MA, len ) MFcuUequL( (MA)[0], len )
#define MFcu_LequU( MA, len ) MFcuLequU( (MA)[0], len )
     /* copy lower-diagonal elements into upper-diagonal
       (or vice versa) by index-reflection, so as to get a symmetric matrix    */

            /* data-type conversions:  */
#define Mcu_DtoF( MF, MD, ht, len ) Vcu_DtoF( (MF)[0], (MD)[0], (ht)*(len) )
#define Mcu_FtoD( MD, MF, ht, len ) Vcu_FtoD( (MD)[0], (MF)[0], (ht)*(len) )

            /* suitable windows for MF_spectrum: */
#define MFcu_Hann( MA, ht, len )     MFcuHann( (MA)[0], ht, len )
#define MFcu_Hanning( MA, ht, len )  MFcuHann( (MA)[0], ht, len )  /* erroneous name for Hann */
#define MFcu_Parzen( MA, ht, len )   MFcuParzen( (MA)[0], ht, len )
#define MFcu_Welch( MA, ht, len )    MFcuWelch( (MA)[0], ht, len )

/********  Extracting a submatrix and copying a submatrix back  *********/

#define MFcu_submatrix( MSub, subHt, subLen, MSrce, srceHt, srceLen, \
                      firstRowInCol, sampInCol, firstColInRow, sampInRow ) \
               MFcusubmatrix(  (MSub)[0], subHt, subLen, \
                             (MSrce)[0], srceHt, srceLen, \
                             firstRowInCol, sampInCol, firstColInRow, sampInRow )

#define MFcu_submatrix_equM( MDest, destHt, destLen, \
                           firstRowInCol, sampInCol, firstColInRow, sampInRow, \
                           MSrce, srceHt, srceLen ) \
               MFcusubmatrix_equM(  (MDest)[0], destHt, destLen, \
                             firstRowInCol, sampInCol, firstColInRow, sampInRow, \
                             (MSrce)[0], srceHt, srceLen )

#define MFcu_equMblock( MSub, subHt, subLen, MSrce, srceHt, srceLen, \
                      firstRowInCol, firstColInRow ) \
               MFcuequMblock(  (MSub)[0], subHt, subLen, \
                             (MSrce)[0], srceHt, srceLen, \
                             firstRowInCol, firstColInRow )

#define MFcu_block_equM( MDest, destHt, destLen, \
                       firstRowInCol, firstColInRow, \
                       MSrce, srceHt, srceLen ) \
               MFcublock_equM( (MDest)[0], destHt, destLen, \
                             firstRowInCol, firstColInRow, \
                             (MSrce)[0], srceHt, srceLen )

#define MFcu_equMblockT( MSub, subHt, subLen, MSrce, srceHt, srceLen, \
                      firstRowInCol, firstColInRow ) \
               MFcuequMblockT(  (MSub)[0], subHt, subLen, \
                             (MSrce)[0], srceHt, srceLen, \
                             firstRowInCol, firstColInRow )

#define MFcu_block_equMT( MDest, destHt, destLen, \
                       firstRowInCol, firstColInRow, \
                       MSrce, srceHt, srceLen ) \
               MFcublock_equMT( (MDest)[0], destHt, destLen, \
                             firstRowInCol, firstColInRow, \
                             (MSrce)[0], srceHt, srceLen )

/*****   Extracting a single row or a single column or the diagonal  ******
 *       and storing it into a vector                                     */

#define MFcu_Row_extract( Y, MA, ht, len, iRow ) MFcuRow_extract( Y, (MA)[0], ht, len, iRow )
#define MFcu_Col_extract( Y, MA, ht, len, iCol ) MFcuCol_extract( Y, (MA)[0], ht, len, iCol )
#define MFcu_Dia_extract( Y, MA, len )           MFcuDia_extract( Y, (MA)[0], len )

/**************  Deleting or inserting a row or a column   ***************/

#define MFcu_Row_delete( MB, MA, htA, lenA, iRow )    MFcuRow_delete( (MB)[0], (MA)[0], htA, lenA, iRow )
#define MFcu_Col_delete( MB, MA, htA, lenA, iCol )    MFcuCol_delete( (MB)[0], (MA)[0], htA, lenA, iCol )
#define MFcu_Row_insert( MB, MA, htB, lenB, iRow, X ) MFcuRow_insert( (MB)[0], (MA)[0], htB, lenB, iRow, X )
#define MFcu_Col_insert( MB, MA, htB, lenB, iCol, X ) MFcuCol_insert( (MB)[0], (MA)[0], htB, lenB, iCol, X )


/*****************    Basic arithmetic operations *********************
                      performed on one single row,
                      or one single column of any matrix,
                      or on the diagonal of a square matrix

    Note: In contrast to the analogous VectorLib functions, the operations
    are performed in-place, i.e. the input matrix itself is changed  */

#define MFcu_Row_neg( MA, ht, len, iRow ) MFcuRow_neg( (MA)[0], ht, len, iRow )
#define MFcu_Col_neg( MA, ht, len, iCol ) MFcuCol_neg( (MA)[0], ht, len, iCol )

#define MFcu_Row_addC( MA, ht, len, iRow, C )      MFcuRow_addC( (MA)[0], ht, len, iRow, C )
#define MFcu_Col_addC( MA, ht, len, iCol, C )      MFcuCol_addC( (MA)[0], ht, len, iCol, C )
#define MFcu_Dia_addC( MA, len, C )                MFcuDia_addC( (MA)[0], len, C )

#define MFcu_Row_addV( MA, ht, len, iRow, X )      MFcuRow_addV( (MA)[0], ht, len, iRow, X )
#define MFcu_Col_addV( MA, ht, len, iCol, X )      MFcuCol_addV( (MA)[0], ht, len, iCol, X )
#define MFcu_Dia_addV( MA, len, X )                MFcuDia_addV( (MA)[0], len, X )

#define MFcu_Row_subC( MA, ht, len, iRow, C )      MFcuRow_subC( (MA)[0], ht, len, iRow, C )
#define MFcu_Col_subC( MA, ht, len, iCol, C )      MFcuCol_subC( (MA)[0], ht, len, iCol, C )
#define MFcu_Dia_subC( MA, len, C )                MFcuDia_subC( (MA)[0], len, C )

#define MFcu_Row_subV( MA, ht, len, iRow, X )      MFcuRow_subV( (MA)[0], ht, len, iRow, X )
#define MFcu_Col_subV( MA, ht, len, iCol, X )      MFcuCol_subV( (MA)[0], ht, len, iCol, X )
#define MFcu_Dia_subV( MA, len, X )                MFcuDia_subV( (MA)[0], len, X )

#define MFcu_Row_subrC( MA, ht, len, iRow, C )      MFcuRow_subrC( (MA)[0], ht, len, iRow, C )
#define MFcu_Col_subrC( MA, ht, len, iCol, C )      MFcuCol_subrC( (MA)[0], ht, len, iCol, C )
#define MFcu_Dia_subrC( MA, len, C )                MFcuDia_subrC( (MA)[0], len, C )

#define MFcu_Row_subrV( MA, ht, len, iRow, X )      MFcuRow_subrV( (MA)[0], ht, len, iRow, X )
#define MFcu_Col_subrV( MA, ht, len, iCol, X )      MFcuCol_subrV( (MA)[0], ht, len, iCol, X )
#define MFcu_Dia_subrV( MA, len, X )                MFcuDia_subrV( (MA)[0], len, X )

#define MFcu_Row_mulC( MA, ht, len, iRow, C )      MFcuRow_mulC( (MA)[0], ht, len, iRow, C )
#define MFcu_Col_mulC( MA, ht, len, iCol, C )      MFcuCol_mulC( (MA)[0], ht, len, iCol, C )
#define MFcu_Dia_mulC( MA, len, C )                MFcuDia_mulC( (MA)[0], len, C )

#define MFcu_Row_mulV( MA, ht, len, iRow, X )      MFcuRow_mulV( (MA)[0], ht, len, iRow, X )
#define MFcu_Col_mulV( MA, ht, len, iCol, X )      MFcuCol_mulV( (MA)[0], ht, len, iCol, X )
#define MFcu_Dia_mulV( MA, len, X )                MFcuDia_mulV( (MA)[0], len, X )

#define MFcu_Row_divC( MA, ht, len, iRow, C )      MFcuRow_divC( (MA)[0], ht, len, iRow, C )
#define MFcu_Col_divC( MA, ht, len, iCol, C )      MFcuCol_divC( (MA)[0], ht, len, iCol, C )
#define MFcu_Dia_divC( MA, len, C )                MFcuDia_divC( (MA)[0], len, C )

#define MFcu_Row_divV( MA, ht, len, iRow, X )      MFcuRow_divV( (MA)[0], ht, len, iRow, X )
#define MFcu_Col_divV( MA, ht, len, iCol, X )      MFcuCol_divV( (MA)[0], ht, len, iCol, X )
#define MFcu_Dia_divV( MA, len, X )                MFcuDia_divV( (MA)[0], len, X )

#define MFcu_Row_divrC( MA, ht, len, iRow, C )      MFcuRow_divrC( (MA)[0], ht, len, iRow, C )
#define MFcu_Col_divrC( MA, ht, len, iCol, C )      MFcuCol_divrC( (MA)[0], ht, len, iCol, C )
#define MFcu_Dia_divrC( MA, len, C )                MFcuDia_divrC( (MA)[0], len, C )

#define MFcu_Row_divrV( MA, ht, len, iRow, X )      MFcuRow_divrV( (MA)[0], ht, len, iRow, X )
#define MFcu_Col_divrV( MA, ht, len, iCol, X )      MFcuCol_divrV( (MA)[0], ht, len, iCol, X )
#define MFcu_Dia_divrV( MA, len, X )                MFcuDia_divrV( (MA)[0], len, X )


/******  One-dimensional vector operations **********************
         performed along all rows or all columns simultaneously,
         or along the diagonal of a square matrix                */

#define MFcu_Rows_max( Y, MA, ht, len )        MFcuRows_max( Y, (MA)[0], ht, len )
#define MFcu_Cols_max( Y, MA, ht, len )        MFcuCols_max( Y, (MA)[0], ht, len )
#define MFcu_Dia_max(  MA, len )               MFcuDia_max(  (MA)[0], len )
#define MFcu_Rows_min( Y, MA, ht, len )        MFcuRows_min( Y, (MA)[0], ht, len )
#define MFcu_Cols_min( Y, MA, ht, len )        MFcuCols_min( Y, (MA)[0], ht, len )
#define MFcu_Dia_min(  MA, len )               MFcuDia_min(  (MA)[0], len )

#define MFcu_Rows_absmax( Y, MA, ht, len )       MFcuRows_absmax( Y, (MA)[0], ht, len )
#define MFcu_Cols_absmax( Y, MA, ht, len )       MFcuCols_absmax( Y, (MA)[0], ht, len )
#define MFcu_Dia_absmax(  MA, len )              MFcuDia_absmax(  (MA)[0], len )
#define MFcu_Rows_absmin( Y, MA, ht, len )       MFcuRows_absmin( Y, (MA)[0], ht, len )
#define MFcu_Cols_absmin( Y, MA, ht, len )       MFcuCols_absmin( Y, (MA)[0], ht, len )
#define MFcu_Dia_absmin(  MA, len )              MFcuDia_absmin(  (MA)[0], len )

#define MFcu_Rows_sum( Y, MA, ht, len )          MFcuRows_sum( Y, (MA)[0], ht, len )
#define MFcu_Cols_sum( Y, MA, ht, len )          MFcuCols_sum( Y, (MA)[0], ht, len )
#define MFcu_Dia_sum(  MA, len )                 MFcuDia_sum(  (MA)[0], len )
#define MFcu_Rows_ssq( Y, MA, ht, len )          MFcuRows_ssq( Y, (MA)[0], ht, len )
#define MFcu_Cols_ssq( Y, MA, ht, len )          MFcuCols_ssq( Y, (MA)[0], ht, len )
#define MFcu_Dia_ssq(  MA, len )                 MFcuDia_ssq(  (MA)[0], len )
#define MFcu_Rows_prod( Y, MA, ht, len )         MFcuRows_prod( Y, (MA)[0], ht, len )
#define MFcu_Cols_prod( Y, MA, ht, len )         MFcuCols_prod( Y, (MA)[0], ht, len )
#define MFcu_Dia_prod(  MA, len )                MFcuDia_prod(  (MA)[0], len )

#define MFcu_Rows_runsum( MA, ht, len )     MFcuRows_runsum( (MA)[0], ht, len )
#define MFcu_Cols_runsum( MA, ht, len )     MFcuCols_runsum( (MA)[0], ht, len )
#define MFcu_Rows_runprod( MA, ht, len )    MFcuRows_runprod( (MA)[0], ht, len )
#define MFcu_Cols_runprod( MA, ht, len )    MFcuCols_runprod( (MA)[0], ht, len )

#define MFcu_Rows_rotate( MA, ht, len, pos)           MFcuRows_rotate( (MA)[0], ht, len, pos )
#define MFcu_Cols_rotate( MA, ht, len, pos)           MFcuCols_rotate( (MA)[0], ht, len, pos )
#define MFcu_Rows_rotate_buf( MA, ht, len, pos, MBuf) MFcuRows_rotate_buf( (MA)[0], ht, len, pos, (MBuf)[0] )
#define MFcu_Cols_rotate_buf( MA, ht, len, pos, MBuf) MFcuCols_rotate_buf( (MA)[0], ht, len, pos, (MBuf)[0] )
#define MFcu_Rows_reflect( MA, ht, len )              MFcuRows_reflect( (MA)[0], ht, len )
#define MFcu_Cols_reflect( MA, ht, len )              MFcuCols_reflect( (MA)[0], ht, len )
#define MFcu_Rows_rev( MA, ht, len)                   MFcuRows_rev( (MA)[0], ht, len )
#define MFcu_Cols_rev( MA, ht, len)                   MFcuCols_rev( (MA)[0], ht, len )
#define MFcu_Rows_distribution( MAbund, Limits, nBins, MX, ht, len, mode ) MFcuRows_distribution( MAbund[0], Limits, nBins, MX[0], ht, len, mode )
#define MFcu_Cols_distribution( MAbund, Limits, nBins, MX, ht, len, mode ) MFcuCols_distribution( MAbund[0], Limits, nBins, MX[0], ht, len, mode )

/********  Operations involving two rows or two colums of one matrix  *****/

#define MFcu_Rows_exchange( MA, ht, len, row1, row2 ) \
                             MFcuRows_exchange( (MA)[0], ht, len, row1, row2 )
#define MFcu_Cols_exchange( MA, ht, len, col1, col2 ) \
                             MFcuCols_exchange( (MA)[0], ht, len, col1, col2 )

#define MFcu_Rows_add( MA, ht, len, destRow, srceRow ) \
                             MFcuRows_add( (MA)[0], ht, len, destRow, srceRow )
#define MFcu_Cols_add( MA, ht, len, destCol, srceCol ) \
                             MFcuCols_add( (MA)[0], ht, len, destCol, srceCol )
                         /* dest[i] += source[i]  */

#define MFcu_Rows_sub( MA, ht, len, destRow, srceRow ) \
                             MFcuRows_sub( (MA)[0], ht, len, destRow, srceRow )
#define MFcu_Cols_sub( MA, ht, len, destCol, srceCol ) \
                             MFcuCols_sub( (MA)[0], ht, len, destCol, srceCol )
                         /* dest[i] -= source[i]  */

#define MFcu_Rows_Cadd( MA, ht, len, destRow, srceRow, C ) \
                          MFcuRows_Cadd( (MA)[0], ht, len, destRow, srceRow, C )
#define MFcu_Cols_Cadd( MA, ht, len, destCol, srceCol, C ) \
                          MFcuCols_Cadd( (MA)[0], ht, len, destCol, srceCol, C )
                         /* dest[i] += C * source[i]  */

#define MFcu_Rows_lincomb( MA, ht, len, destRow, destC, srceRow, srceC ) \
            MFcuRows_lincomb( (MA)[0], ht, len, destRow, destC, srceRow, srceC )
#define MFcu_Cols_lincomb( MA, ht, len, destCol, destC, srceCol, srceC ) \
            MFcuCols_lincomb( (MA)[0], ht, len, destCol, destC, srceCol, srceC )
  /*  linear combination: dest[i] = destC * dest[i] + sourceC * source[i] */


/*********************  Center of gravity *****************************/
#define MFcu_centerOfGravityInd( MA, ht, len ) \
            MFcucenterOfGravityInd( (MA)[0], ht, len )
#define MFcu_centerOfGravityV( X, Y, MA, ht, len ) \
            MFcucenterOfGravityV( X, Y, (MA)[0], ht, len )

/*************** Transposing and rotating a matrix **********************/

#define MFcu_transpose( MTr, MA, htTr, lenTr )    MFcutranspose( (MTr)[0], (MA)[0], htTr, lenTr )
       /*  dimensions htTr, lenTr are those of the transposed matrix, not of the original!   */
#define MFcu_rotate90( MRot, MA, htRot, lenRot )  MFcurotate90( (MRot)[0], (MA)[0], htRot, lenRot )
#define MFcu_rotate180( MRot, MA, htRot, lenRot ) VFcu_rev( (MRot)[0], (MA)[0], (htRot)*(lenRot) )
#define MFcu_rotate270( MRot, MA, htRot, lenRot ) MFcurotate270( (MRot)[0], (MA)[0], htRot, lenRot )

/********************** Interpolation of Matrix elements **************/

#define MFcu_polyinterpol( MZ, X, Y, ht, len, XTab, YTab, MZTab, httab, lentab, degX, degY ) \
             MFcupolyinterpol( (MZ)[0], X, Y, ht, len, XTab, YTab, (MZTab)[0], httab, lentab, degX, degY )
#define MFcu_ratinterpol( MZ, X, Y, ht, len, XTab, YTab, MZTab, httab, lentab, degX, degY ) \
             MFcuratinterpol( (MZ)[0], X, Y, ht, len, XTab, YTab, (MZTab)[0], httab, lentab, degX, degY )
#define MFcu_natCubSplineInterpol( MZ, X, Y, ht, len, XTab, YTab, MZTab, httab, lentab ) \
             MFcunatCubSplineInterpol( (MZ)[0], X, Y, ht, len, XTab, YTab, (MZTab)[0], httab, lentab )


/************************ Matrix Arithmetics *************************/

#define MFcu_addM( MC, MA, MB, htA, lenA )   VFcu_addV( (MC)[0], (MA)[0], (MB)[0], (htA)*(lenA) )
#define MFcu_addMT( MC, MA, MB, htA, lenA )  MFcuaddMT( (MC)[0], (MA)[0], (MB)[0], htA, lenA )
#define MFcu_subM( MC, MA, MB, htA, lenA )   VFcu_subV( (MC)[0], (MA)[0], (MB)[0], (htA)*(lenA) )
#define MFcu_subMT( MC, MA, MB, htA, lenA )  MFcusubMT( (MC)[0], (MA)[0], (MB)[0], htA, lenA )
#define MFcu_subrMT( MC, MA, MB, htA, lenA ) MFcusubrMT( (MC)[0], (MA)[0], (MB)[0], htA, lenA )
#define MFcu_mulC( MB, MA, htA, lenA, C )    VFcu_mulC( (MB)[0], (MA)[0], (htA)*(lenA), C )
#define MFcu_divC( MB, MA, htA, lenA, C )    VFcu_divC( (MB)[0], (MA)[0], (htA)*(lenA), C )

#define MFscu_addM( MC, MA, MB, htA, lenA, C )      VFscu_addV( (MC)[0], (MA)[0], (MB)[0], (htA)*(lenA), C )
#define MFscu_addMT( MC, MA, MB, htA, lenA, C )     MFscuaddMT( (MC)[0], (MA)[0], (MB)[0], htA, lenA, C )
#define MFscu_subM( MC, MA, MB, htA, lenA, C )      VFscu_subV( (MC)[0], (MA)[0], (MB)[0], (htA)*(lenA), C )
#define MFscu_subMT( MC, MA, MB, htA, lenA, C )     MFscusubMT( (MC)[0], (MA)[0], (MB)[0], htA, lenA, C )
#define MFscu_subrMT( MC, MA, MB, htA, lenA, C )    MFscusubrMT( (MC)[0], (MA)[0], (MB)[0], htA, lenA, C )
#define MFcu_lincomb( MC, MA, MB, htA, lenA, CA, CB )       VFcu_lincomb( (MC)[0], (MA)[0], (MB)[0], (htA)*(lenA), CA,    CB )

#define MFcu_mulV( Y, MA, X, htA, lenA )    MFcumulV( Y, (MA)[0], X, htA, lenA )
             /*  Y = MA * X.  sizX=lenA, sizY=htA;   both X and Y are column-vectors    */
#define MFcu_TmulV( Y, MA, X, htA, lenA )   MFcuTmulV( Y, (MA)[0], X, htA, lenA )
            /*  Y = MAT * X.  sizX=htA, sizY=lenA;   both X and Y are column-vectors    */
#define VFcu_mulM( Y, X, MA, htA, lenA )    VFcumulM( Y, X, (MA)[0], htA, lenA )
            /*  Y = X * MA.  sizX=htA, sizY=lenA;    both X and Y are row-vectors.
                             Mind the prefix: VFcu_ (not MFcu_)    */
#define VFcu_mulMT( Y, X, MA, htA, lenA )    VFcumulMT( Y, X, (MA)[0], htA, lenA )
            /*  Y = X * MAT.  sizX=lenA, sizY=htA;   both X and Y are row-vectors.   */
#define MFcu_mulM( MC, MA, MB, htA, lenA, lenB )  MFcumulM( (MC)[0], (MA)[0], (MB)[0], htA, lenA, lenB )
                         /*  MC = MA * MB.  htB=lenA, htC=htA, lenC=lenB */
#define MFcu_mulMT( MC, MA, MB, htA, lenA, htB )  MFcumulMT( (MC)[0], (MA)[0], (MB)[0], htA, lenA, htB )
                         /*  MC = MA * MBT.  lenB=lenA, htC=htA, lenC=htB */
#define MFcu_TmulM( MC, MA, MB, htA, lenA, lenB ) MFcuTmulM( (MC)[0], (MA)[0], (MB)[0], htA, lenA, lenB )
                         /*  MC = MAT * MB.  htB=htA, htC=lenA, lenC=lenB */
#define MFcu_TmulMT( MC, MA, MB, htA, lenA, htB ) MFcuTmulMT( (MC)[0], (MA)[0], (MB)[0], htA, lenA, htB )
                         /*  MC = MAT * MBT.  lenB=htA, htC=lenA, lenC=htB */
#define MFdiacu_mulM(  MC, MADia, MB, htB, lenB )  MFdiacumulM(  (MC)[0], MADia, (MB)[0], htB, lenB )
#define MFdiacu_mulMT( MC, MADia, MB, htB, lenB )  MFdiacumulMT( (MC)[0], MADia, (MB)[0], htB, lenB )
#define MFcu_mulMdia(  MC, MA, MBDia, htA, lenA )  MFcumulMdia(  (MC)[0], (MA)[0], MBDia, htA, lenA )
#define MFcu_TmulMdia( MC, MA, MBDia, htA, lenA )  MFcuTmulMdia( (MC)[0], (MA)[0], MBDia, htA, lenA )

/***************** Two-Dimensional Fourier-Transform Methods ************/

#define MFcu_FFT( MY, MX, ht, len, dir )     MFcuFFT( (MY)[0], (MX)[0], ht, len, dir )
#define MFcu_Rows_FFT( MY, MX, ht, len, dir) MFcuRows_FFT( (MY)[0], (MX)[0], ht, len, dir )
#define MFcu_Cols_FFT( MY, MX, ht, len, dir) MFcuCols_FFT( (MY)[0], (MX)[0], ht, len, dir )
#define MFcu_FFTtoC( MY, MX, ht, len )       MFcuFFTtoC( (MY)[0], (MX)[0], ht, len )
#define MFcu_Rows_FFTtoC( MY, MX, ht, len )  MFcuRows_FFTtoC( (MY)[0], (MX)[0], ht, len )
#define MFcu_Cols_FFTtoC( MY, MX, ht, len )  MFcuCols_FFTtoC( (MY)[0], (MX)[0], ht, len )
#define MFcu_convolve( MY, MFlt, MX, MRsp, ht, len ) \
                  MFcuconvolve( (MY)[0], (MFlt)[0], (MX)[0], (MRsp)[0], ht, len )
#define MFcu_deconvolve( MY, MFlt, MX, MRsp, ht, len ) \
                  MFcudeconvolve( (MY)[0], (MFlt)[0], (MX)[0], (MRsp)[0], ht, len )
#define MFcu_filter( MY, MX, MFlt, ht, len ) MFcufilter( (MY)[0], (MX)[0], (MFlt)[0], ht, len )
#define MFcu_autocorr( MACorr, MX, ht, len ) MFcuautocorr( (MACorr)[0], (MX)[0], ht, len )
#define MFcu_xcorr( MXCorr, MX, MY, ht, len) MFcuxcorr( (MXCorr)[0], (MX)[0], (MY)[0], ht, len )
#define MFcu_spectrum( MSpec, htSpec, lenSpec, MX, htX, lenX, MWin ) \
              MFcuspectrum( (MSpec)[0], htSpec, lenSpec, (MX)[0], htX, lenX, (MWin)[0] )
              /*   htSpec, lenSpec must be 2**n,
                   MSpec must be a (htSpec+1)*(lenSpec+1) matrix!!
                   htX >= n*htSpec,  lenX >= n*lenSpec,
                   htWin = 2*htSpec, lenWin = 2*lenSpec */


/*************************************************************************
 * MFcu functions (without underbar in the prefix): 	
    (working on matrices in host memory, input type 
	fPMatrix = fVector = pointer to matrix element[0][0], 
	scalar parameters on host and passed by value)
*
 *************************************************************************/

#define MFcuequ0( MA, ht, len )       VFcu_equ0( MA, (ht)*(len) )
void   __vf OVCUAPI  MFcuequ1( fPMatrix MA, ui len );  /* identity matrix */
void   __vf OVCUAPI  MFcuequm1( fPMatrix MA, ui len );  /* neg. identity matrix */
void   __vf OVCUAPI  MFcuouterprod( fPMatrix MA, fVector X,  fVector Y, ui ht, ui len );

void   __vf OVCUAPI  MFcuRow_equ0( fPMatrix MA, ui ht, ui len, ui iRow );
void   __vf OVCUAPI  MFcuCol_equ0( fPMatrix MA, ui ht, ui len, ui iCol );
void   __vf OVCUAPI  MFcuDia_equ0( fPMatrix MA, ui len );

void   __vf OVCUAPI  MFcuRow_equC( fPMatrix MA, ui ht, ui len, ui iRow, float C );
void   __vf OVCUAPI  MFcuCol_equC( fPMatrix MA, ui ht, ui len, ui iCol, float C );
void   __vf OVCUAPI  MFcuDia_equC( fPMatrix MA, ui len, float C );

void   __vf OVCUAPI  MFcuRow_equV( fPMatrix MA, ui ht, ui len, ui iRow, fVector X );
void   __vf OVCUAPI  MFcuCol_equV( fPMatrix MA, ui ht, ui len, ui iCol, fVector X );
void   __vf OVCUAPI  MFcuDia_equV( fPMatrix MA, ui len, fVector X );

void   __vf OVCUAPI  MFcuTrd_equM( fPMatrix MA, fPMatrix MTrd, ui len );
void   __vf OVCUAPI  MFcuTrd_extract( fPMatrix MTrd, fPMatrix MA, ui len );

#define MFcuequM( MB, MA, ht, len )      VFcu_equV( MB, MA, (ht)*(len) )
#define MFcuneg( MB, MA, ht, len )       VFcu_neg( MB, MA, (ht)*(len) )
void   __vf OVCUAPI  MFcuUequL( fPMatrix MA, ui len );
void   __vf OVCUAPI  MFcuLequU( fPMatrix MA, ui len );

void   __vf OVCUAPI  MFcuHann( fPMatrix MA, ui ht, ui len );
#define MFcuHanning MFcuHann
void   __vf OVCUAPI  MFcuParzen(  fPMatrix MA, ui ht, ui len );
void   __vf OVCUAPI  MFcuWelch(   fPMatrix MA, ui ht, ui len );

            /* data-type conversions:  */
#define McuDtoF( MF, MD, ht, len ) Vcu_DtoF( (MF), (MD), (ht)*(len) )
#define McuFtoD( MD, MF, ht, len ) Vcu_FtoD( (MD), (MF), (ht)*(len) )

/********  Extracting a submatrix and copying a submatrix back  *********/

void  __vf OVCUAPI  MFcusubmatrix( fPMatrix MSub, ui subHt,  ui subLen,
                          fPMatrix MSrce, ui srceHt,  ui srceLen,
                          ui firstRowInCol,  ui sampInCol,
                          ui firstColInRow,  ui sampInRow );

void  __vf OVCUAPI  MFcusubmatrix_equM( fPMatrix MDest, ui destHt, ui destLen,
                               ui firstRowInCol,  ui sampInCol,
                               ui firstColInRow,  ui sampInRow,
                               fPMatrix MSrce, ui srceHt, ui srceLen );

void  __vf OVCUAPI  MFcuequMblock(  fPMatrix MSub, ui subHt, ui subLen,
                          fPMatrix MSrce, ui srceHt,  ui srceLen,
                          ui firstRowInCol,  ui firstColInRow );

void  __vf OVCUAPI  MFcublock_equM( fPMatrix MDest, ui destHt, ui destLen,
                          ui firstRowInCol,  ui firstColInRow,
                          fPMatrix MSrce, ui srceHt, ui srceLen );

void  __vf OVCUAPI  MFcuequMblockT( fPMatrix MSub, ui subHt, ui subLen,
                          fPMatrix MSrce, ui srceHt, ui srceLen,
                          ui firstRowInCol,  ui firstColInRow );

void  __vf OVCUAPI  MFcublock_equMT( fPMatrix MDest, ui destHt, ui destLen,
                          ui firstRowInCol,  ui firstColInRow,
                          fPMatrix MSrce, ui srceHt, ui srceLen );


/*****   Extracting a single row or a single column or the diagonal  *****
 *       and storing it into a vector                                    */

void __vf OVCUAPI  MFcuRow_extract( fVector Y, fPMatrix MA, ui ht, ui len, ui iRow );
void __vf OVCUAPI  MFcuCol_extract( fVector Y, fPMatrix MA, ui ht, ui len, ui iCol );
void __vf OVCUAPI  MFcuDia_extract( fVector Y, fPMatrix MA, ui len );

/**********  Deleting or inserting a row or a column *****************/

void __vf OVCUAPI  MFcuRow_delete( fPMatrix MB, fPMatrix MA, ui htA, ui lenA, ui iRow );
void __vf OVCUAPI  MFcuCol_delete( fPMatrix MB, fPMatrix MA, ui htA, ui lenA, ui iCol );
void __vf OVCUAPI  MFcuRow_insert( fPMatrix MB, fPMatrix MA, ui htB, ui lenB, ui iRow, fVector X );
void __vf OVCUAPI  MFcuCol_insert( fPMatrix MB, fPMatrix MA, ui htB, ui lenB, ui iCol, fVector X );


/*****************    Basic arithmetic operations ***********************
     performed on one single row,  or one single column of any matrix,
     or on the diagonal of a square matrix                              */

void   __vf OVCUAPI  MFcuRow_neg( fPMatrix MX, ui ht, ui len, ui iRow );
void   __vf OVCUAPI  MFcuCol_neg( fPMatrix MX, ui ht, ui len, ui iCol );

void   __vf OVCUAPI  MFcuRow_addC( fPMatrix MA, ui ht, ui len, ui iRow, float C );
void   __vf OVCUAPI  MFcuCol_addC( fPMatrix MA, ui ht, ui len, ui iCol, float C );
void   __vf OVCUAPI  MFcuDia_addC( fPMatrix MA, ui len, float C );

void   __vf OVCUAPI  MFcuRow_subC( fPMatrix MA, ui ht, ui len, ui iRow, float C );
void   __vf OVCUAPI  MFcuCol_subC( fPMatrix MA, ui ht, ui len, ui iCol, float C );
void   __vf OVCUAPI  MFcuDia_subC( fPMatrix MA, ui len, float C );

void   __vf OVCUAPI  MFcuRow_addV( fPMatrix MA, ui ht, ui len, ui iRow, fVector X );
void   __vf OVCUAPI  MFcuCol_addV( fPMatrix MA, ui ht, ui len, ui iCol, fVector X );
void   __vf OVCUAPI  MFcuDia_addV( fPMatrix MA, ui len, fVector X );

void   __vf OVCUAPI  MFcuRow_subV( fPMatrix MA, ui ht, ui len, ui iRow, fVector X );
void   __vf OVCUAPI  MFcuCol_subV( fPMatrix MA, ui ht, ui len, ui iCol, fVector X );
void   __vf OVCUAPI  MFcuDia_subV( fPMatrix MA, ui len, fVector X );

void   __vf OVCUAPI  MFcuRow_subrC( fPMatrix MA, ui ht, ui len, ui iRow, float C );
void   __vf OVCUAPI  MFcuCol_subrC( fPMatrix MA, ui ht, ui len, ui iCol, float C );
void   __vf OVCUAPI  MFcuDia_subrC( fPMatrix MA, ui len, float C );

void   __vf OVCUAPI  MFcuRow_subrV( fPMatrix MA, ui ht, ui len, ui iRow, fVector X );
void   __vf OVCUAPI  MFcuCol_subrV( fPMatrix MA, ui ht, ui len, ui iCol, fVector X );
void   __vf OVCUAPI  MFcuDia_subrV( fPMatrix MA, ui len, fVector X );

void   __vf OVCUAPI  MFcuRow_mulC( fPMatrix MA, ui ht, ui len, ui iRow, float C );
void   __vf OVCUAPI  MFcuCol_mulC( fPMatrix MA, ui ht, ui len, ui iCol, float C );
void   __vf OVCUAPI  MFcuDia_mulC( fPMatrix MA, ui len, float C );

void   __vf OVCUAPI  MFcuRow_mulV( fPMatrix MA, ui ht, ui len, ui iRow, fVector X );
void   __vf OVCUAPI  MFcuCol_mulV( fPMatrix MA, ui ht, ui len, ui iCol, fVector X );
void   __vf OVCUAPI  MFcuDia_mulV( fPMatrix MA, ui len, fVector X );

void   __vf OVCUAPI  MFcuRow_divC( fPMatrix MA, ui ht, ui len, ui iRow, float C );
void   __vf OVCUAPI  MFcuCol_divC( fPMatrix MA, ui ht, ui len, ui iCol, float C );
void   __vf OVCUAPI  MFcuDia_divC( fPMatrix MA, ui len, float C );

void   __vf OVCUAPI  MFcuRow_divV( fPMatrix MA, ui ht, ui len, ui iRow, fVector X );
void   __vf OVCUAPI  MFcuCol_divV( fPMatrix MA, ui ht, ui len, ui iCol, fVector X );
void   __vf OVCUAPI  MFcuDia_divV( fPMatrix MA, ui len, fVector X );

void   __vf OVCUAPI  MFcuRow_divrC( fPMatrix MA, ui ht, ui len, ui iRow, float C );
void   __vf OVCUAPI  MFcuCol_divrC( fPMatrix MA, ui ht, ui len, ui iCol, float C );
void   __vf OVCUAPI  MFcuDia_divrC( fPMatrix MA, ui len, float C );

void   __vf OVCUAPI  MFcuRow_divrV( fPMatrix MA, ui ht, ui len, ui iRow, fVector X );
void   __vf OVCUAPI  MFcuCol_divrV( fPMatrix MA, ui ht, ui len, ui iCol, fVector X );
void   __vf OVCUAPI  MFcuDia_divrV( fPMatrix MA, ui len, fVector X );


/******  One-dimensional vector operations **********************
         performed along all rows or all columns simultaneously,
         or along the diagonal of a square matrix                */

void   __vf OVCUAPI  MFcuRows_max( fVector Y, fPMatrix MA, ui ht, ui len );
void   __vf OVCUAPI  MFcuCols_max( fVector Y, fPMatrix MA, ui ht, ui len );
float  __vf OVCUAPI  MFcuDia_max(  fPMatrix MA, ui len );
void   __vf OVCUAPI  MFcuRows_min( fVector Y, fPMatrix MA, ui ht, ui len );
void   __vf OVCUAPI  MFcuCols_min( fVector Y, fPMatrix MA, ui ht, ui len );
float  __vf OVCUAPI  MFcuDia_min(  fPMatrix MA, ui len );

void   __vf OVCUAPI  MFcuRows_absmax( fVector Y, fPMatrix MA, ui ht, ui len );
void   __vf OVCUAPI  MFcuCols_absmax( fVector Y, fPMatrix MA, ui ht, ui len );
float  __vf OVCUAPI  MFcuDia_absmax(  fPMatrix MA, ui len );
void   __vf OVCUAPI  MFcuRows_absmin( fVector Y, fPMatrix MA, ui ht, ui len );
void   __vf OVCUAPI  MFcuCols_absmin( fVector Y, fPMatrix MA, ui ht, ui len );
float  __vf OVCUAPI  MFcuDia_absmin(  fPMatrix MA, ui len );

void   __vf OVCUAPI  MFcuRows_sum( fVector Y, fPMatrix MA, ui ht, ui len );
void   __vf OVCUAPI  MFcuCols_sum( fVector Y, fPMatrix MA, ui ht, ui len );
float  __vf OVCUAPI  MFcuDia_sum(  fPMatrix MA, ui len );
void   __vf OVCUAPI  MFcuRows_ssq( fVector Y, fPMatrix MA, ui ht, ui len );
void   __vf OVCUAPI  MFcuCols_ssq( fVector Y, fPMatrix MA, ui ht, ui len );
float  __vf OVCUAPI  MFcuDia_ssq(  fPMatrix MA, ui len );
void   __vf OVCUAPI  MFcuRows_prod(fVector Y, fPMatrix MA, ui ht, ui len );
void   __vf OVCUAPI  MFcuCols_prod(fVector Y, fPMatrix MA, ui ht, ui len );
float  __vf OVCUAPI  MFcuDia_prod( fPMatrix MA, ui len );

void  __vf OVCUAPI  MFcuRows_runsum( fPMatrix MA, ui ht, ui len );
void  __vf OVCUAPI  MFcuCols_runsum( fPMatrix MA, ui ht, ui len );
void  __vf OVCUAPI  MFcuRows_runprod( fPMatrix MA, ui ht, ui len );
void  __vf OVCUAPI  MFcuCols_runprod( fPMatrix MA, ui ht, ui len );

void  __vf OVCUAPI  MFcuRows_rotate( fPMatrix MA, ui ht, ui len, ssize_t pos );
void  __vf OVCUAPI  MFcuCols_rotate( fPMatrix MA, ui ht, ui len, ssize_t pos );
void  __vf OVCUAPI  MFcuRows_rotate_buf( fPMatrix MA, ui ht, ui len, ssize_t pos, fPMatrix MBuf );
void  __vf OVCUAPI  MFcuCols_rotate_buf( fPMatrix MA, ui ht, ui len, ssize_t pos, fPMatrix MBuf );
void  __vf OVCUAPI  MFcuRows_reflect( fPMatrix MA, ui ht, ui len );
void  __vf OVCUAPI  MFcuCols_reflect( fPMatrix MA, ui ht, ui len );
void  __vf OVCUAPI  MFcuRows_rev( fPMatrix MA, ui ht, ui len );
void  __vf OVCUAPI  MFcuCols_rev( fPMatrix MA, ui ht, ui len );
void  __vf OVCUAPI  MFcuRows_distribution( uiPMatrix MAbund, fVector Limits, ui nBins, fPMatrix MX, ui ht, ui len, int mode );
void  __vf OVCUAPI  MFcuCols_distribution( uiPMatrix MAbund, fVector Limits, ui nBins, fPMatrix MX, ui ht, ui len, int mode );

/********  Operations involving two rows or two colums of one matrix  *****/

void   __vf OVCUAPI  MFcuRows_exchange( fPMatrix MA, ui ht, ui len, ui i1, ui i2 );
void   __vf OVCUAPI  MFcuCols_exchange( fPMatrix MA, ui ht, ui len, ui i1, ui i2 );

void   __vf OVCUAPI  MFcuRows_add( fPMatrix MA, ui ht, ui len, ui destRow, ui sourceRow );
void   __vf OVCUAPI  MFcuCols_add( fPMatrix MA, ui ht, ui len, ui destCol, ui sourceCol );

void   __vf OVCUAPI  MFcuRows_sub( fPMatrix MA, ui ht, ui len, ui destRow, ui sourceRow );
void   __vf OVCUAPI  MFcuCols_sub( fPMatrix MA, ui ht, ui len, ui destCol, ui sourceCol );

void   __vf OVCUAPI  MFcuRows_Cadd( fPMatrix MA, ui ht, ui len, ui destRow, ui sourceRow, float C );
void   __vf OVCUAPI  MFcuCols_Cadd( fPMatrix MA, ui ht, ui len, ui destCol, ui sourceCol, float C );

void   __vf OVCUAPI  MFcuRows_lincomb( fPMatrix MA, ui ht, ui len,
					ui destRow,  float  destC, ui srceRow,  float  srceC );
void   __vf OVCUAPI  MFcuCols_lincomb( fPMatrix MA, ui ht, ui len,
                              ui destCol,  float  destC, ui srceCol,  float  srceC );


/*********************  Center of gravity *****************************/
#if defined __cplusplus && defined _CMATH_CLASSDEFS
} // the following functions cannot be extern "C", if fComplex is a class
#endif
fComplex __vf OVCUAPI  MFcucenterOfGravityInd( fPMatrix MA, ui ht, ui len );
fComplex __vf OVCUAPI  MFcucenterOfGravityV( fVector X, fVector Y, fPMatrix MA, ui ht, ui len );
#if defined __cplusplus && defined _CMATH_CLASSDEFS
extern "C" {
#endif

/***************  Transposing and rotating a matrix **********************/

void  __vf OVCUAPI  MFcutranspose( fPMatrix MTr, fPMatrix MA,  ui htTr, ui lenTr );
void  __vf OVCUAPI  MFcurotate90(  fPMatrix MRot, fPMatrix MA, ui htRot, ui lenRot );
#define     MFcurotate180( MRot, MA, htRot, lenRot )  VFcu_rev( MRot, MA, (htRot)*(lenRot) )
void  __vf OVCUAPI  MFcurotate270( fPMatrix MRot, fPMatrix MA, ui htRot, ui lenRot );


/********************** Interpolation of Matrix elements **************/

void __vf OVCUAPI  MFcupolyinterpol( fPMatrix MZ, fVector X, fVector Y, ui ht, ui len,
       fVector XTab, fVector YTab, fPMatrix MZTab, ui httab, ui lentab,
       unsigned degX, unsigned degY );
void __vf OVCUAPI  MFcuratinterpol( fPMatrix MZ, fVector X, fVector Y, ui ht, ui len,
       fVector XTab, fVector YTab, fPMatrix MZTab, ui httab, ui lentab,
       unsigned degX, unsigned degY );
void __vf OVCUAPI  MFcunatCubSplineInterpol( fPMatrix MZ, fVector X, fVector Y, ui ht, ui len,
       fVector XTab, fVector YTab, fPMatrix MZTab, ui httab, ui lentab );


/************************ Matrix Arithmetics *************************/

#define MFcuaddM( MC, MA, MB, htA, lenA )            VFcu_addV( MC, MA, MB, (htA)*(lenA) )
void __vf OVCUAPI  MFcuaddMT( fPMatrix MC, fPMatrix MA, fPMatrix MB, ui htA, ui lenA );
#define MFcusubM( MC, MA, MB, htA, lenA )            VFcu_subV( MC, MA, MB, (htA)*(lenA) )
void __vf OVCUAPI  MFcusubMT( fPMatrix MC, fPMatrix MA, fPMatrix MB, ui htA, ui lenA );
void __vf OVCUAPI  MFcusubrMT( fPMatrix MC, fPMatrix MA, fPMatrix MB, ui htA, ui lenA );
#define MFcumulC( MB, MA, htA, lenA, C )             VFcu_mulC( MB, MA, (htA)*(lenA), C )
#define MFcudivC( MB, MA, htA, lenA, C )             VFcu_divC( MB, MA, (htA)*(lenA), C )
#define MFscuaddM( MC, MA, MB, htA, lenA, C )        VFscu_addV( MC, MA, MB, (htA)*(lenA), C )
void __vf OVCUAPI  MFscuaddMT( fPMatrix MC, fPMatrix MA, fPMatrix MB, ui htA, ui lenA, float C );
#define MFscusubM( MC, MA, MB, htA, lenA, C )        VFscu_subV( MC, MA, MB, (htA)*(lenA), C )
void __vf OVCUAPI  MFscusubMT( fPMatrix MC, fPMatrix MA, fPMatrix MB, ui htA, ui lenA, float C );
void __vf OVCUAPI  MFscusubrMT( fPMatrix MC, fPMatrix MA, fPMatrix MB, ui htA, ui lenA, float C );
#define MFculincomb( MC, MA, MB, htA, lenA, CA, CB ) VFcu_lincomb( MC, MA, MB, (htA)*(lenA), CA, CB )
void  __vf OVCUAPI  MFcumulV( fVector Y, fPMatrix MA, fVector X, ui htA, ui lenA );
void  __vf OVCUAPI  MFcuTmulV( fVector Y, fPMatrix MA, fVector X, ui htA, ui lenA );
void  __vf OVCUAPI  VFcumulM( fVector Y, fVector X, fPMatrix MA, ui htA, ui lenA );
void  __vf OVCUAPI  VFcumulMT( fVector Y, fVector X, fPMatrix MA, ui htA, ui lenA );
void  __vf OVCUAPI  MFcumulM( fPMatrix MC, fPMatrix MA, fPMatrix MB, ui htA, ui lenA, ui lenB );
void  __vf OVCUAPI  MFcumulMT( fPMatrix MC, fPMatrix MA, fPMatrix MB, ui htA, ui lenA, ui htB );
void  __vf OVCUAPI  MFcuTmulM( fPMatrix MC, fPMatrix MA, fPMatrix MB, ui htA, ui lenA, ui lenB );
void  __vf OVCUAPI  MFcuTmulMT( fPMatrix MC, fPMatrix MA, fPMatrix MB, ui htA, ui lenA, ui htB );
void  __vf OVCUAPI  MFcudiamulM( fPMatrix MC, fPMatrix MADia, fPMatrix MB, ui htB, ui lenB );
void  __vf OVCUAPI  MFcudiamulMT( fPMatrix MC, fPMatrix MADia, fPMatrix MB, ui htB, ui lenB );
void  __vf OVCUAPI  MFcumulMdia( fPMatrix MC, fPMatrix MA, fPMatrix MBDia, ui htA, ui lenA );
void  __vf OVCUAPI  MFcuTmulMdia( fPMatrix MC, fPMatrix MA, fPMatrix MBDia, ui htA, ui lenA );


/*************  Matrix Fourier-Transform Methods *****************/

void  __vf OVCUAPI   MFcuFFT( fPMatrix MY, fPMatrix MX, ui ht, ui len, int dir );
void  __vf OVCUAPI   MFcuFFTtoC( cfPMatrix MY, fPMatrix MX, ui ht, ui len );
void  __vf OVCUAPI   MFcuconvolve( fPMatrix MY, fPMatrix MFlt, fPMatrix MX, fPMatrix MRsp, ui ht, ui len );
void  __vf OVCUAPI   MFcudeconvolve( fPMatrix MY, fPMatrix MFlt, fPMatrix MX, fPMatrix MRsp, ui ht, ui len );
void  __vf OVCUAPI   MFcufilter( fPMatrix MY, fPMatrix MX, fPMatrix MFlt, ui ht, ui len );
void  __vf OVCUAPI   MFcuautocorr( fPMatrix MACorr, fPMatrix MX, ui ht, ui len );
void  __vf OVCUAPI   MFcuxcorr( fPMatrix MXCorr, fPMatrix MX, fPMatrix MY, ui ht, ui len );
void  __vf OVCUAPI   MFcuspectrum( fPMatrix MSpec, ui htSpec, ui lenSpec, fPMatrix MX, ui htX, ui lenX, fPMatrix MWin );
void  __vf OVCUAPI   MFcuRows_FFT( fPMatrix MY, fPMatrix MX, ui ht, ui len, int dir );
void  __vf OVCUAPI   MFcuCols_FFT( fPMatrix MY, fPMatrix MX, ui ht, ui len, int dir );
void  __vf OVCUAPI   MFcuRows_FFTtoC( cfPMatrix MY, fPMatrix MX, ui ht, ui len );
void  __vf OVCUAPI   MFcuCols_FFTtoC( cfPMatrix MY, fPMatrix MX, ui ht, ui len );


#ifdef __cplusplus
}  // end of extern "C"
#endif // __cplusplus
#endif /* __CUDAMFSTD_H */
