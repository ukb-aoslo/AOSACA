/*  cudaMDstd.h

  matrix management functions:
  manipulations on matrices of data type "double"
  (single-precision real numbers)

  This file declares the functions with the name variants 
	cudaMD_func		(working on matrices in device memory, input type dMatrix, scalar parameters reside on host and are passed by value)
	cusdMD_func		(as cudaMD_func except scalar parameters reside on device and are passed by address)
	cudaMDfunc		(as cudaMD_func, but input type dPMatrix = dVector = pointer to matrix element[0][0])
	cusdMDfunc		(as cusdMD_func, but input type dPMatrix = dVector = pointer to matrix element[0][0])
	MDcu_func		(working on matrices in host memory, input type dMatrix, scalar parameters on host and passed by value)
	MDcufunc		(as MDcu_func, but input type dPMatrix = dVector = pointer to matrix element[0][0])
  where func is the respective function.

  Copyright (c) 1996-2017 by OptiCode - Dr. Martin Sander Software Dev.
  All Rights Reserved.
*/

#if !defined( __CUDAMDSTD_H )
#define __CUDAMDSTD_H
#if !defined( __CUDAMATLIB_H )
#include <cudaMatLib.h>
#endif
#if !defined( __CUDAVDSTD_H )
#include <cudaVDstd.h>
#endif
#if !defined( __CUDAVDMATH_H )
#include <cudaVDmath.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif

/**** Generation of matrices on device memory and on pinned host memory *******************/

dMatrix  __vf cudaMD_matrix( ui ht, ui len );   /* allocates a vector on device memory */
dMatrix  __vf cudaMD_matrix0( ui ht, ui len );
 /* The following functions allocate device-accessible, "pinned" memory on the host.
	This memory is mapped onto the device memory space. The resulting device address is returned.
	The matrix can be accessed either by its host address "hostPtr" e.g., MD_equ1( hostPtr, ht, len );
	or by its device address , e.g., cudaMD_equ1( devicePtr, ht, len );                             */
dMatrix  __vf cudaMD_pinnedMatrix(  dMatrix *hostPtr, ui ht, ui len ); 
dMatrix  __vf cudaMD_pinnedMatrix0( dMatrix *hostPtr, ui ht, ui len );

/*************************************************************************
 * Declarations of the functions written without underbar in the prefix: *
 *	cudaMDfunc  (input type 
                   dPMatrix = dVector = pointer to matrix element[0][0])
 *	cusdMDfunc  (but input type 
                   dPMatrix = dVector = pointer to matrix element[0][0])
 *************************************************************************/

void    __vcuf OVCUAPI  cudaMDsetElement( dPMatrix X, ui ht, ui len, ui m, ui n, double C );
void    __vcuf OVCUAPI  cusdMDsetElement( dPMatrix X, ui ht, ui len, ui m, ui n, double *d_C );
void    __vcuf OVCUAPI  cudaMDgetElement( double *h_y, dPMatrix X, ui ht, ui len, ui m, ui n );
void    __vcuf OVCUAPI  cusdMDgetElement( double *d_y, dPMatrix X, ui ht, ui len, ui m, ui n );
double * __vcuf OVCUAPI  cudaMDPelement( dPMatrix X, ui ht, ui len, ui m, ui n );
double   __vcuf OVCUAPI  cudaMDelement( dPMatrix X, ui ht, ui len, ui m, ui n );

#define cudaMDequ0( MA, ht, len )       cudaVD_equ0( MA, (ht)*(len) )
overror_t   __vcuf OVCUAPI  cudaMDequ1( dPMatrix MA, ui len );  /* identity matrix */
overror_t   __vcuf OVCUAPI  cudaMDequm1( dPMatrix MA, ui len );  /* neg. identity matrix */
overror_t   __vcuf OVCUAPI  cudaMDouterprod( dPMatrix MA, dVector X,  dVector Y, ui ht, ui len );

overror_t   __vcuf OVCUAPI  cudaMDRow_equ0( dPMatrix MA, ui ht, ui len, ui iRow );
overror_t   __vcuf OVCUAPI  cudaMDCol_equ0( dPMatrix MA, ui ht, ui len, ui iCol );
overror_t   __vcuf OVCUAPI  cudaMDDia_equ0( dPMatrix MA, ui len );

overror_t   __vcuf OVCUAPI  cudaMDRow_equC( dPMatrix MA, ui ht, ui len, ui iRow, double C );
overror_t   __vcuf OVCUAPI  cudaMDCol_equC( dPMatrix MA, ui ht, ui len, ui iCol, double C );
overror_t   __vcuf OVCUAPI  cudaMDDia_equC( dPMatrix MA, ui len, double C );
overror_t   __vcuf OVCUAPI  cusdMDRow_equC( dPMatrix MA, ui ht, ui len, ui iRow, double *d_C);
overror_t   __vcuf OVCUAPI  cusdMDCol_equC( dPMatrix MA, ui ht, ui len, ui iCol, double *d_C);
overror_t   __vcuf OVCUAPI  cusdMDDia_equC( dPMatrix MA, ui len, double *d_C);

overror_t   __vcuf OVCUAPI  cudaMDRow_equV( dPMatrix MA, ui ht, ui len, ui iRow, dVector X );
overror_t   __vcuf OVCUAPI  cudaMDCol_equV( dPMatrix MA, ui ht, ui len, ui iCol, dVector X );
overror_t   __vcuf OVCUAPI  cudaMDDia_equV( dPMatrix MA, ui len, dVector X );

overror_t   __vcuf OVCUAPI  cudaMDTrd_equM( dPMatrix MA, dPMatrix MTrd, ui len );
overror_t   __vcuf OVCUAPI  cudaMDTrd_extract( dPMatrix MTrd, dPMatrix MA, ui len );

#define cudaMDequM( MB, MA, ht, len )      cudaVD_equV( MB, MA, (ht)*(len) )
#define cudaMDequMhost( MB, MA, ht, len )  cudaVD_equVhost( MB, MA, (ht)*(len) )
#define MDequMdevice( MB, MA, ht, len )    VD_equVdevice( MB, MA, (ht)*(len) )
#define cudaMDneg( MB, MA, ht, len )       cudaVD_neg( MB, MA, (ht)*(len) )
overror_t   __vcuf OVCUAPI  cudaMDUequL( dPMatrix MA, ui len );
overror_t   __vcuf OVCUAPI  cudaMDLequU( dPMatrix MA, ui len );

overror_t   __vcuf OVCUAPI  cudaMDHann( dPMatrix MA, ui ht, ui len );
#define cudaMDHanning cudaMDHann
overror_t   __vcuf OVCUAPI  cudaMDParzen(  dPMatrix MA, ui ht, ui len );
overror_t   __vcuf OVCUAPI  cudaMDWelch(   dPMatrix MA, ui ht, ui len );

/********  Extracting a submatrix and copying a submatrix back  *********/

overror_t  __vcuf OVCUAPI  cudaMDsubmatrix( dPMatrix MSub, ui subHt,  ui subLen,
                          dPMatrix MSrce, ui srceHt,  ui srceLen,
                          ui firstRowInCol,  ui sampInCol,
                          ui firstColInRow,  ui sampInRow );

overror_t  __vcuf OVCUAPI  cudaMDsubmatrix_equM( dPMatrix MDest, ui destHt, ui destLen,
                               ui firstRowInCol,  ui sampInCol,
                               ui firstColInRow,  ui sampInRow,
                               dPMatrix MSrce, ui srceHt, ui srceLen );

overror_t  __vcuf OVCUAPI  cudaMDequMblock(  dPMatrix MSub, ui subHt, ui subLen,
                          dPMatrix MSrce, ui srceHt,  ui srceLen,
                          ui firstRowInCol,  ui firstColInRow );

overror_t  __vcuf OVCUAPI  cudaMDblock_equM( dPMatrix MDest, ui destHt, ui destLen,
                          ui firstRowInCol,  ui firstColInRow,
                          dPMatrix MSrce, ui srceHt, ui srceLen );

overror_t  __vcuf OVCUAPI  cudaMDequMblockT( dPMatrix MSub, ui subHt, ui subLen,
                          dPMatrix MSrce, ui srceHt, ui srceLen,
                          ui firstRowInCol,  ui firstColInRow );

overror_t  __vcuf OVCUAPI  cudaMDblock_equMT( dPMatrix MDest, ui destHt, ui destLen,
                          ui firstRowInCol,  ui firstColInRow,
                          dPMatrix MSrce, ui srceHt, ui srceLen );


/*****   Extracting a single row or a single column or the diagonal  *****
 *       and storing it into a vector                                    */

overror_t __vcuf OVCUAPI  cudaMDRow_extract( dVector Y, dPMatrix MA, ui ht, ui len, ui iRow );
overror_t __vcuf OVCUAPI  cudaMDCol_extract( dVector Y, dPMatrix MA, ui ht, ui len, ui iCol );
overror_t __vcuf OVCUAPI  cudaMDDia_extract( dVector Y, dPMatrix MA, ui len );

/**********  Deleting or inserting a row or a column *****************/

overror_t __vcuf OVCUAPI  cudaMDRow_delete( dPMatrix MB, dPMatrix MA, ui htA, ui lenA, ui iRow );
overror_t __vcuf OVCUAPI  cudaMDCol_delete( dPMatrix MB, dPMatrix MA, ui htA, ui lenA, ui iCol );
overror_t __vcuf OVCUAPI  cudaMDRow_insert( dPMatrix MB, dPMatrix MA, ui htB, ui lenB, ui iRow, dVector X );
overror_t __vcuf OVCUAPI  cudaMDCol_insert( dPMatrix MB, dPMatrix MA, ui htB, ui lenB, ui iCol, dVector X );


/*****************    Basic arithmetic operations ***********************
     performed on one single row,  or one single column of any matrix,
     or on the diagonal of a square matrix                              */

overror_t   __vcuf OVCUAPI  cudaMDRow_neg( dPMatrix MX, ui ht, ui len, ui iRow );
overror_t   __vcuf OVCUAPI  cudaMDCol_neg( dPMatrix MX, ui ht, ui len, ui iCol );

overror_t   __vcuf OVCUAPI  cudaMDRow_addC( dPMatrix MA, ui ht, ui len, ui iRow, double C );
overror_t   __vcuf OVCUAPI  cudaMDCol_addC( dPMatrix MA, ui ht, ui len, ui iCol, double C );
overror_t   __vcuf OVCUAPI  cudaMDDia_addC( dPMatrix MA, ui len, double C );
overror_t   __vcuf OVCUAPI  cusdMDRow_addC( dPMatrix MA, ui ht, ui len, ui iRow, double *d_C);
overror_t   __vcuf OVCUAPI  cusdMDCol_addC( dPMatrix MA, ui ht, ui len, ui iCol, double *d_C);
overror_t   __vcuf OVCUAPI  cusdMDDia_addC( dPMatrix MA, ui len, double *d_C);

overror_t   __vcuf OVCUAPI  cudaMDRow_subC( dPMatrix MA, ui ht, ui len, ui iRow, double C );
overror_t   __vcuf OVCUAPI  cudaMDCol_subC( dPMatrix MA, ui ht, ui len, ui iCol, double C );
overror_t   __vcuf OVCUAPI  cudaMDDia_subC( dPMatrix MA, ui len, double C );
overror_t   __vcuf OVCUAPI  cusdMDRow_subC( dPMatrix MA, ui ht, ui len, ui iRow, double *d_C);
overror_t   __vcuf OVCUAPI  cusdMDCol_subC( dPMatrix MA, ui ht, ui len, ui iCol, double *d_C);
overror_t   __vcuf OVCUAPI  cusdMDDia_subC( dPMatrix MA, ui len, double *d_C);

overror_t   __vcuf OVCUAPI  cudaMDRow_addV( dPMatrix MA, ui ht, ui len, ui iRow, dVector X );
overror_t   __vcuf OVCUAPI  cudaMDCol_addV( dPMatrix MA, ui ht, ui len, ui iCol, dVector X );
overror_t   __vcuf OVCUAPI  cudaMDDia_addV( dPMatrix MA, ui len, dVector X );

overror_t   __vcuf OVCUAPI  cudaMDRow_subV( dPMatrix MA, ui ht, ui len, ui iRow, dVector X );
overror_t   __vcuf OVCUAPI  cudaMDCol_subV( dPMatrix MA, ui ht, ui len, ui iCol, dVector X );
overror_t   __vcuf OVCUAPI  cudaMDDia_subV( dPMatrix MA, ui len, dVector X );

overror_t   __vcuf OVCUAPI  cudaMDRow_subrC( dPMatrix MA, ui ht, ui len, ui iRow, double C );
overror_t   __vcuf OVCUAPI  cudaMDCol_subrC( dPMatrix MA, ui ht, ui len, ui iCol, double C );
overror_t   __vcuf OVCUAPI  cudaMDDia_subrC( dPMatrix MA, ui len, double C );
overror_t   __vcuf OVCUAPI  cusdMDRow_subrC( dPMatrix MA, ui ht, ui len, ui iRow, double *d_C);
overror_t   __vcuf OVCUAPI  cusdMDCol_subrC( dPMatrix MA, ui ht, ui len, ui iCol, double *d_C);
overror_t   __vcuf OVCUAPI  cusdMDDia_subrC( dPMatrix MA, ui len, double *d_C);

overror_t   __vcuf OVCUAPI  cudaMDRow_subrV( dPMatrix MA, ui ht, ui len, ui iRow, dVector X );
overror_t   __vcuf OVCUAPI  cudaMDCol_subrV( dPMatrix MA, ui ht, ui len, ui iCol, dVector X );
overror_t   __vcuf OVCUAPI  cudaMDDia_subrV( dPMatrix MA, ui len, dVector X );

overror_t   __vcuf OVCUAPI  cudaMDRow_mulC( dPMatrix MA, ui ht, ui len, ui iRow, double C );
overror_t   __vcuf OVCUAPI  cudaMDCol_mulC( dPMatrix MA, ui ht, ui len, ui iCol, double C );
overror_t   __vcuf OVCUAPI  cudaMDDia_mulC( dPMatrix MA, ui len, double C );
overror_t   __vcuf OVCUAPI  cusdMDRow_mulC( dPMatrix MA, ui ht, ui len, ui iRow, double *d_C);
overror_t   __vcuf OVCUAPI  cusdMDCol_mulC( dPMatrix MA, ui ht, ui len, ui iCol, double *d_C);
overror_t   __vcuf OVCUAPI  cusdMDDia_mulC( dPMatrix MA, ui len, double *d_C);

overror_t   __vcuf OVCUAPI  cudaMDRow_mulV( dPMatrix MA, ui ht, ui len, ui iRow, dVector X );
overror_t   __vcuf OVCUAPI  cudaMDCol_mulV( dPMatrix MA, ui ht, ui len, ui iCol, dVector X );
overror_t   __vcuf OVCUAPI  cudaMDDia_mulV( dPMatrix MA, ui len, dVector X );

overror_t   __vcuf OVCUAPI  cudaMDRow_divC( dPMatrix MA, ui ht, ui len, ui iRow, double C );
overror_t   __vcuf OVCUAPI  cudaMDCol_divC( dPMatrix MA, ui ht, ui len, ui iCol, double C );
overror_t   __vcuf OVCUAPI  cudaMDDia_divC( dPMatrix MA, ui len, double C );
overror_t   __vcuf OVCUAPI  cusdMDRow_divC( dPMatrix MA, ui ht, ui len, ui iRow, double *d_C);
overror_t   __vcuf OVCUAPI  cusdMDCol_divC( dPMatrix MA, ui ht, ui len, ui iCol, double *d_C);
overror_t   __vcuf OVCUAPI  cusdMDDia_divC( dPMatrix MA, ui len, double *d_C);

overror_t   __vcuf OVCUAPI  cudaMDRow_divV( dPMatrix MA, ui ht, ui len, ui iRow, dVector X );
overror_t   __vcuf OVCUAPI  cudaMDCol_divV( dPMatrix MA, ui ht, ui len, ui iCol, dVector X );
overror_t   __vcuf OVCUAPI  cudaMDDia_divV( dPMatrix MA, ui len, dVector X );

overror_t   __vcuf OVCUAPI  cudaMDRow_divrC( dPMatrix MA, ui ht, ui len, ui iRow, double C );
overror_t   __vcuf OVCUAPI  cudaMDCol_divrC( dPMatrix MA, ui ht, ui len, ui iCol, double C );
overror_t   __vcuf OVCUAPI  cudaMDDia_divrC( dPMatrix MA, ui len, double C );
overror_t   __vcuf OVCUAPI  cusdMDRow_divrC( dPMatrix MA, ui ht, ui len, ui iRow, double *d_C);
overror_t   __vcuf OVCUAPI  cusdMDCol_divrC( dPMatrix MA, ui ht, ui len, ui iCol, double *d_C);
overror_t   __vcuf OVCUAPI  cusdMDDia_divrC( dPMatrix MA, ui len, double *d_C);

overror_t   __vcuf OVCUAPI  cudaMDRow_divrV( dPMatrix MA, ui ht, ui len, ui iRow, dVector X );
overror_t   __vcuf OVCUAPI  cudaMDCol_divrV( dPMatrix MA, ui ht, ui len, ui iCol, dVector X );
overror_t   __vcuf OVCUAPI  cudaMDDia_divrV( dPMatrix MA, ui len, dVector X );


/******  One-dimensional vector operations **********************
         performed along all rows or all columns simultaneously,
         or along the diagonal of a square matrix                */

overror_t   __vcuf OVCUAPI  cudaMDRows_max( dVector Y, dPMatrix MA, ui ht, ui len );
overror_t   __vcuf OVCUAPI  cudaMDCols_max( dVector Y, dPMatrix MA, ui ht, ui len );
overror_t   __vcuf OVCUAPI  cudaMDDia_max(  double *h_RetVal, dPMatrix MA, ui len );
overror_t   __vcuf OVCUAPI  cusdMDDia_max(  double *d_RetVal, dPMatrix MA, ui len );
overror_t   __vcuf OVCUAPI  cudaMDRows_min( dVector Y, dPMatrix MA, ui ht, ui len );
overror_t   __vcuf OVCUAPI  cudaMDCols_min( dVector Y, dPMatrix MA, ui ht, ui len );
overror_t   __vcuf OVCUAPI  cudaMDDia_min(  double *h_RetVal, dPMatrix MA, ui len );
overror_t   __vcuf OVCUAPI  cusdMDDia_min(  double *d_RetVal, dPMatrix MA, ui len );

overror_t   __vcuf OVCUAPI  cudaMDRows_absmax( dVector Y, dPMatrix MA, ui ht, ui len );
overror_t   __vcuf OVCUAPI  cudaMDCols_absmax( dVector Y, dPMatrix MA, ui ht, ui len );
overror_t   __vcuf OVCUAPI  cudaMDDia_absmax(  double *h_RetVal, dPMatrix MA, ui len );
overror_t   __vcuf OVCUAPI  cusdMDDia_absmax(  double *d_RetVal, dPMatrix MA, ui len );
overror_t   __vcuf OVCUAPI  cudaMDRows_absmin( dVector Y, dPMatrix MA, ui ht, ui len );
overror_t   __vcuf OVCUAPI  cudaMDCols_absmin( dVector Y, dPMatrix MA, ui ht, ui len );
overror_t   __vcuf OVCUAPI  cudaMDDia_absmin(  double *h_RetVal, dPMatrix MA, ui len );
overror_t   __vcuf OVCUAPI  cusdMDDia_absmin(  double *d_RetVal, dPMatrix MA, ui len );

overror_t   __vcuf OVCUAPI  cudaMDRows_sum( dVector Y, dPMatrix MA, ui ht, ui len );
overror_t   __vcuf OVCUAPI  cudaMDCols_sum( dVector Y, dPMatrix MA, ui ht, ui len );
overror_t   __vcuf OVCUAPI  cudaMDDia_sum(  double *h_RetVal, dPMatrix MA, ui len );
overror_t   __vcuf OVCUAPI  cusdMDDia_sum(  double *d_RetVal, dPMatrix MA, ui len );
overror_t   __vcuf OVCUAPI  cudaMDRows_ssq( dVector Y, dPMatrix MA, ui ht, ui len );
overror_t   __vcuf OVCUAPI  cudaMDCols_ssq( dVector Y, dPMatrix MA, ui ht, ui len );
overror_t   __vcuf OVCUAPI  cudaMDDia_ssq(  double *h_RetVal, dPMatrix MA, ui len );
overror_t   __vcuf OVCUAPI  cusdMDDia_ssq(  double *d_RetVal, dPMatrix MA, ui len );
overror_t   __vcuf OVCUAPI  cudaMDRows_prod(dVector Y, dPMatrix MA, ui ht, ui len );
overror_t   __vcuf OVCUAPI  cudaMDCols_prod(dVector Y, dPMatrix MA, ui ht, ui len );
overror_t   __vcuf OVCUAPI  cudaMDDia_prod( double *h_RetVal, dPMatrix MA, ui len );
overror_t   __vcuf OVCUAPI  cusdMDDia_prod( double *d_RetVal, dPMatrix MA, ui len );

overror_t  __vcuf OVCUAPI  cudaMDRows_runsum( dPMatrix MA, ui ht, ui len );
overror_t  __vcuf OVCUAPI  cudaMDCols_runsum( dPMatrix MA, ui ht, ui len );
overror_t  __vcuf OVCUAPI  cudaMDRows_runprod( dPMatrix MA, ui ht, ui len );
overror_t  __vcuf OVCUAPI  cudaMDCols_runprod( dPMatrix MA, ui ht, ui len );

overror_t  __vcuf OVCUAPI  cudaMDRows_rotate( dPMatrix MA, ui ht, ui len, ssize_t pos );
overror_t  __vcuf OVCUAPI  cudaMDCols_rotate( dPMatrix MA, ui ht, ui len, ssize_t pos );
overror_t  __vcuf OVCUAPI  cudaMDRows_rotate_buf( dPMatrix MA, ui ht, ui len, ssize_t pos, dPMatrix MBuf );
overror_t  __vcuf OVCUAPI  cudaMDCols_rotate_buf( dPMatrix MA, ui ht, ui len, ssize_t pos, dPMatrix MBuf );
overror_t  __vcuf OVCUAPI  cudaMDRows_reflect( dPMatrix MA, ui ht, ui len );
overror_t  __vcuf OVCUAPI  cudaMDCols_reflect( dPMatrix MA, ui ht, ui len );
overror_t  __vcuf OVCUAPI  cudaMDRows_rev( dPMatrix MA, ui ht, ui len );
overror_t  __vcuf OVCUAPI  cudaMDCols_rev( dPMatrix MA, ui ht, ui len );
overror_t  __vcuf OVCUAPI  cudaMDRows_distribution( uiPMatrix MAbund, dVector Limits, ui nBins, dPMatrix MX, ui ht, ui len, int mode );
overror_t  __vcuf OVCUAPI  cudaMDCols_distribution( uiPMatrix MAbund, dVector Limits, ui nBins, dPMatrix MX, ui ht, ui len, int mode );

/********  Operations involving two rows or two colums of one matrix  *****/

overror_t   __vcuf OVCUAPI  cudaMDRows_exchange( dPMatrix MA, ui ht, ui len, ui i1, ui i2 );
overror_t   __vcuf OVCUAPI  cudaMDCols_exchange( dPMatrix MA, ui ht, ui len, ui i1, ui i2 );

overror_t   __vcuf OVCUAPI  cudaMDRows_add( dPMatrix MA, ui ht, ui len, ui destRow, ui sourceRow );
overror_t   __vcuf OVCUAPI  cudaMDCols_add( dPMatrix MA, ui ht, ui len, ui destCol, ui sourceCol );

overror_t   __vcuf OVCUAPI  cudaMDRows_sub( dPMatrix MA, ui ht, ui len, ui destRow, ui sourceRow );
overror_t   __vcuf OVCUAPI  cudaMDCols_sub( dPMatrix MA, ui ht, ui len, ui destCol, ui sourceCol );

overror_t   __vcuf OVCUAPI  cudaMDRows_Cadd( dPMatrix MA, ui ht, ui len, ui destRow, ui sourceRow, double C );
overror_t   __vcuf OVCUAPI  cudaMDCols_Cadd( dPMatrix MA, ui ht, ui len, ui destCol, ui sourceCol, double C );
overror_t   __vcuf OVCUAPI  cusdMDRows_Cadd( dPMatrix MA, ui ht, ui len, ui destRow, ui sourceRow, double *d_C);
overror_t   __vcuf OVCUAPI  cusdMDCols_Cadd( dPMatrix MA, ui ht, ui len, ui destCol, ui sourceCol, double *d_C);

overror_t   __vcuf OVCUAPI  cudaMDRows_lincomb( dPMatrix MA, ui ht, ui len,
					ui destRow,  double  destC, ui srceRow,  double  srceC );
overror_t   __vcuf OVCUAPI  cudaMDCols_lincomb( dPMatrix MA, ui ht, ui len,
                              ui destCol,  double  destC, ui srceCol,  double  srceC );
overror_t   __vcuf OVCUAPI  cusdMDRows_lincomb( dPMatrix MA, ui ht, ui len,
					ui destRow,  double  *d_destC, ui srceRow,  double  *d_srceC );
overror_t   __vcuf OVCUAPI  cusdMDCols_lincomb( dPMatrix MA, ui ht, ui len,
                              ui destCol,  double  *d_destC, ui srceCol,  double  *d_srceC );


/*********************  Center of gravity *****************************/
overror_t __vcuf OVCUAPI  cudaMDcenterOfGravityInd( dComplex *h_Result, dPMatrix MA, ui ht, ui len );
overror_t __vcuf OVCUAPI  cudaMDcenterOfGravityV( dComplex *h_Result, dVector X, dVector Y, dPMatrix MA, ui ht, ui len );
overror_t __vcuf OVCUAPI  cusdMDcenterOfGravityInd( dComplex *d_Result, dPMatrix MA, ui ht, ui len );
overror_t __vcuf OVCUAPI  cusdMDcenterOfGravityV( dComplex *d_Result, dVector X, dVector Y, dPMatrix MA, ui ht, ui len );

/***************  Transposing and rotating a matrix **********************/

overror_t  __vcuf OVCUAPI  cudaMDtranspose( dPMatrix MTr, dPMatrix MA,  ui htTr, ui lenTr );
overror_t  __vcuf OVCUAPI  cudaMDrotate90(  dPMatrix MRot, dPMatrix MA, ui htRot, ui lenRot );
#define     cudaMDrotate180( MRot, MA, htRot, lenRot )  cudaVD_rev( MRot, MA, (htRot)*(lenRot) )
overror_t  __vcuf OVCUAPI  cudaMDrotate270( dPMatrix MRot, dPMatrix MA, ui htRot, ui lenRot );
overror_t  __vcuf OVCUAPI  cudaMDtranspose_buf( dPMatrix MTr, dPMatrix MA,  ui htTr, ui lenTr, dPMatrix MBuf );


/********************** Interpolation of Matrix elements **************/

overror_t __vcuf OVCUAPI  cudaMDpolyinterpol( dPMatrix MZ, dVector X, dVector Y, ui ht, ui len,
       dVector XTab, dVector YTab, dPMatrix MZTab, ui httab, ui lentab,
       unsigned degX, unsigned degY );
overror_t __vcuf OVCUAPI  cudaMDratinterpol( dPMatrix MZ, dVector X, dVector Y, ui ht, ui len,
       dVector XTab, dVector YTab, dPMatrix MZTab, ui httab, ui lentab,
       unsigned degX, unsigned degY );
overror_t __vcuf OVCUAPI  cudaMDnatCubSplineInterpol( dPMatrix MZ, dVector X, dVector Y, ui ht, ui len,
       dVector XTab, dVector YTab, dPMatrix MZTab, ui httab, ui lentab );


/************************ Matrix Arithmetics *************************/

#define cudaMDaddM( MC, MA, MB, htA, lenA )            cudaVD_addV( MC, MA, MB, (htA)*(lenA) )
overror_t __vcuf OVCUAPI  cudaMDaddMT( dPMatrix MC, dPMatrix MA, dPMatrix MB, ui htA, ui lenA );
#define cudaMDsubM( MC, MA, MB, htA, lenA )            cudaVD_subV( MC, MA, MB, (htA)*(lenA) )
overror_t __vcuf OVCUAPI  cudaMDsubMT( dPMatrix MC, dPMatrix MA, dPMatrix MB, ui htA, ui lenA );
overror_t __vcuf OVCUAPI  cudaMDsubrMT( dPMatrix MC, dPMatrix MA, dPMatrix MB, ui htA, ui lenA );
#define cudaMDmulC( MB, MA, htA, lenA, C )             cudaVD_mulC( MB, MA, (htA)*(lenA), C )
#define cusdMDmulC( MB, MA, htA, lenA, d_CPtr )        cusdVD_mulC( MB, MA, (htA)*(lenA), d_CPtr )
#define cudaMDdivC( MB, MA, htA, lenA, C )             cudaVD_divC( MB, MA, (htA)*(lenA), C )
#define cusdMDdivC( MB, MA, htA, lenA, d_CPtr )        cusdVD_divC( MB, MA, (htA)*(lenA), d_CPtr )
#define cudaMDsaddM( MC, MA, MB, htA, lenA, C )        cudaVDs_addV( MC, MA, MB, (htA)*(lenA), C )
overror_t __vcuf OVCUAPI  cudaMDsaddMT( dPMatrix MC, dPMatrix MA, dPMatrix MB, ui htA, ui lenA, double C );
#define cudaMDssubM( MC, MA, MB, htA, lenA, C )        cudaVDs_subV( MC, MA, MB, (htA)*(lenA), C )
overror_t __vcuf OVCUAPI  cudaMDssubMT( dPMatrix MC, dPMatrix MA, dPMatrix MB, ui htA, ui lenA, double C );
overror_t __vcuf OVCUAPI  cudaMDssubrMT( dPMatrix MC, dPMatrix MA, dPMatrix MB, ui htA, ui lenA, double C );
#define cusdMDsaddM( MC, MA, MB, htA, lenA, d_CPtr )   cusdVDs_addV( MC, MA, MB, (htA)*(lenA), d_CPtr )
overror_t __vcuf OVCUAPI  cusdMDsaddMT( dPMatrix MC, dPMatrix MA, dPMatrix MB, ui htA, ui lenA, double *d_CPtr );
#define cusdMDssubM( MC, MA, MB, htA, lenA, d_CPtr )   cusdVDs_subV( MC, MA, MB, (htA)*(lenA), d_CPtr )
overror_t __vcuf OVCUAPI  cusdMDssubMT( dPMatrix MC, dPMatrix MA, dPMatrix MB, ui htA, ui lenA, double *d_CPtr );
overror_t __vcuf OVCUAPI  cusdMDssubrMT( dPMatrix MC, dPMatrix MA, dPMatrix MB, ui htA, ui lenA, double *d_CPtr );
#define cudaMDlincomb( MC, MA, MB, htA, lenA, CA, CB ) cudaVD_lincomb( MC, MA, MB, (htA)*(lenA), CA, CB )
#define cusdMDlincomb( MC, MA, MB, htA, lenA, d_CAPtr, d_CBPtr ) cusdVD_lincomb( MC, MA, MB, (htA)*(lenA), d_CAPtr, d_CBPtr )
overror_t  __vcuf OVCUAPI  cudaMDmulV( dVector Y, dPMatrix MA, dVector X, ui htA, ui lenA );
overror_t  __vcuf OVCUAPI  cudaMDTmulV( dVector Y, dPMatrix MA, dVector X, ui htA, ui lenA );
overror_t  __vcuf OVCUAPI   cudaVDmulM( dVector Y, dVector X, dPMatrix MA, ui htA, ui lenA );
overror_t  __vcuf OVCUAPI   cudaVDmulMT( dVector Y, dVector X, dPMatrix MA, ui htA, ui lenA );
overror_t  __vcuf OVCUAPI  cudaMDmulM( dPMatrix MC, dPMatrix MA, dPMatrix MB, ui htA, ui lenA, ui lenB );
overror_t  __vcuf OVCUAPI  cudaMDmulMT( dPMatrix MC, dPMatrix MA, dPMatrix MB, ui htA, ui lenA, ui htB );
overror_t  __vcuf OVCUAPI  cudaMDTmulM( dPMatrix MC, dPMatrix MA, dPMatrix MB, ui htA, ui lenA, ui lenB );
overror_t  __vcuf OVCUAPI  cudaMDTmulMT( dPMatrix MC, dPMatrix MA, dPMatrix MB, ui htA, ui lenA, ui htB );
overror_t  __vcuf OVCUAPI  cudaMDdiamulM( dPMatrix MC, dPMatrix MADia, dPMatrix MB, ui htB, ui lenB );
overror_t  __vcuf OVCUAPI  cudaMDdiamulMT( dPMatrix MC, dPMatrix MADia, dPMatrix MB, ui htB, ui lenB );
overror_t  __vcuf OVCUAPI  cudaMDmulMdia( dPMatrix MC, dPMatrix MA, dPMatrix MBDia, ui htA, ui lenA );
overror_t  __vcuf OVCUAPI  cudaMDTmulMdia( dPMatrix MC, dPMatrix MA, dPMatrix MBDia, ui htA, ui lenA );


/*************  Matrix Fourier-Transform Methods *****************/

overror_t  __vcuf OVCUAPI   cudaMDFFT( dPMatrix MY, dPMatrix MX, ui ht, ui len, int dir );
overror_t  __vcuf OVCUAPI   cudaMDFFTtoC( cdPMatrix MY, dPMatrix MX, ui ht, ui len );
overror_t  __vcuf OVCUAPI   cudaMDconvolve( dPMatrix MY, dPMatrix MFlt, dPMatrix MX, dPMatrix MRsp, ui ht, ui len );
overror_t  __vcuf OVCUAPI   cudaMDdeconvolve( dPMatrix MY, dPMatrix MFlt, dPMatrix MX, dPMatrix MRsp, ui ht, ui len );
overror_t  __vcuf OVCUAPI   cudaMDfilter( dPMatrix MY, dPMatrix MX, dPMatrix MFlt, ui ht, ui len );
overror_t  __vcuf OVCUAPI   cudaMDautocorr( dPMatrix MACorr, dPMatrix MX, ui ht, ui len );
overror_t  __vcuf OVCUAPI   cudaMDxcorr( dPMatrix MXCorr, dPMatrix MX, dPMatrix MY, ui ht, ui len );
overror_t  __vcuf OVCUAPI   cudaMDspectrum( dPMatrix MSpec, ui htSpec, ui lenSpec, dPMatrix MX, ui htX, ui lenX, dPMatrix MWin );
overror_t  __vcuf OVCUAPI   cudaMDRows_FFT( dPMatrix MY, dPMatrix MX, ui ht, ui len, int dir );
overror_t  __vcuf OVCUAPI   cudaMDCols_FFT( dPMatrix MY, dPMatrix MX, ui ht, ui len, int dir );
overror_t  __vcuf OVCUAPI   cudaMDRows_FFTtoC( cdPMatrix MY, dPMatrix MX, ui ht, ui len );
overror_t  __vcuf OVCUAPI   cudaMDCols_FFTtoC( cdPMatrix MY, dPMatrix MX, ui ht, ui len );

/**************************  Input and Output  **************************
	The input/output functions involve memory transfers from device
	to host memory or vice versa. The generic cudaMD_input/output functions
	allocate their own host buffers, whereas the cudaMD_xxx_buf functions
	take a user-supplied buffer vector h_Wk (size must be >= ht*len )
	and are much more efficient.                                       */

#define cudaMDprint( MA, ht, len )  cudaMDfprint( stdout, MA, ht, len, 80 )
overror_t __vf cudaMDfprint( FILE *stream, dPMatrix MA, ui ht, ui len, unsigned linewidth );
overror_t __vf cudaMDcprint( dPMatrix MA, ui ht, ui len );
#define cudaMDprint_buf( MA, ht, len, h_Wk )  cudaMDfprint_buf( stdout, MA, ht, len, 80, h_Wk )
overror_t __vf cudaMDfprint_buf( FILE *stream, dPMatrix MA, ui ht, ui len, unsigned linewidth, dVector h_Wk );
overror_t __vf cudaMDcprint_buf( dPMatrix MA, ui ht, ui len, dVector h_Wk );
overror_t __vf cudaMDwrite( FILE *stream, dPMatrix X, ui ht, ui len  );
overror_t __vf cudaMDwrite_buf( FILE *stream, dPMatrix X, ui ht, ui len, dVector h_Wk );
#if !((defined __BORLANDC__) && (__BORLANDC__ < 0x710))
		/* modern compiler versions:  */
	overror_t __vf cudaMDread( dPMatrix X, ui ht, ui len, FILE *stream );
	overror_t __vf cudaMDread_buf( dPMatrix X, ui ht, ui len, FILE *stream, dVector h_Wk );
#else /* older Borland compiler versions need separate implementation */
	overror_t __vf cudaMDread1( dPMatrix X, ui ht, ui len, FILE *stream );
	overror_t __vf cudaMDread1_buf( dPMatrix X, ui ht, ui len, FILE *stream, dVector h_Wk );
	#define cudaMDread      cudaMDread1
	#define cudaMDread_buf  cudaMDread1_buf
#endif
#define cudaMDstore( str, MA, ht, len ) cudaVD_store( str, MA, (len)*(ht) )
#define cudaMDrecall( MA, ht, len, str) cudaVD_recall( MA, (len)*(ht), str)
#define cudaMDstore_buf( str, MA, ht, len, h_Wk ) cudaVD_store( str, MA, (len)*(ht), h_Wk )
#define cudaMDrecall_buf( MA, ht, len, str, h_Wk) cudaVD_recall( MA, (len)*(ht), str, h_Wk)


/***************************************************************************
    cudaMD_func	(working on matrices in device memory, input type dMatrix, 
	             scalar parameters reside on host and are passed by value)
    cusdMD_func	(as cudaMD_func except scalar parameters reside on device 
	             and are passed by address)                                 */


/***************************************************************************
 *  The following definitions are needed to access individual elements,    *
 *  and row pointers. As all addresses point to device memory, the usual   *
 *  mechanism of accessing elements, i.e., writing something like MA[m][n] *
 *  is not possible here!                                                  *
 *  Pro forma, the distinction between the data types dMatrix and          *
 *  dPMatrix is kept. However, in the present implementation, both of      *
 *  these types actually contain a pointer to the matrix element [0][0].   *
 *  For C++, inline functions ensure proper type checking at compile time, *
 *  while for plain-C, only a less safe type-cast is possible.             *
 ***************************************************************************/

#ifdef __cplusplus

/***  Addressing single elements of dynamically allocated matrices: ******/

inline void    cudaMD_setElement( dMatrix MA, ui ht, ui len, ui m, ui n, double C )
	{	cudaMDsetElement( (dPMatrix)(MA), ht, len, m, n, C );}
inline void    cusdMD_setElement( dMatrix MA, ui ht, ui len, ui m, ui n, double *d_C )
	{	cusdMDsetElement( (dPMatrix)(MA), ht, len, m, n, C );}
inline void    cudaMD_getElement( double *y, dMatrix MA, ui ht, ui len, ui m, ui n )
	{	cudaMDgetElement( y, (dPMatrix)(MA), ht, len, m, n );}
inline void    cusdMD_getElement( double *y, dMatrix MA, ui ht, ui len, ui m, ui n )
	{	cusdMDgetElement( y, (dPMatrix)(MA), ht, len, m, n );}
inline double * cudaMD_Pelement( dMatrix MA, ui ht, ui len, ui m, ui n )
	{	return cudaMDPelement( (dPMatrix)(MA), ht, len, m, n );}
inline double   cudaMD_element( dMatrix MA, ui ht, ui len, ui m, ui n )
{	return cudaMDelement( (dPMatrix)(MA), ht, len, m, n );}

 /****************  Initialization  ****************************************/

inline overror_t  cudaMD_equ0( dMatrix MA, ui ht, ui len )
	{	return cudaVD_equ0( (dPMatrix)MA, (ht)*(len) ); }
inline overror_t  cudaMD_equ1( dMatrix MA, ui len )
	{	return cudaMDequ1( (dPMatrix)(MA), len );} /* identity matrix */
inline overror_t  cudaMD_equm1( dMatrix MA, ui len )
	{	return cudaMDequm1( (dPMatrix)(MA), len );} /* neg. identity matrix */

inline overror_t  cudaMD_randomLC( dMatrix MA, ui ht, ui len, long seed, double MinVal, double MaxVal, V_RANDOMLCSTATE *h_state )
	{	return cudaVD_randomLC( (dPMatrix)(MA), (ht)*(len), seed, MinVal, MaxVal, h_state );}
inline overror_t  cudaMD_random( dMatrix MA, ui ht, ui len, long seed, double MinVal, double MaxVal )
	{	return cudaVD_random( (dPMatrix)(MA), (ht)*(len), seed, MinVal, MaxVal );}
inline overror_t  cusdMD_randomLC( dMatrix MA, ui ht, ui len, long seed, double *d_MinVal, double *d_MaxVal, V_RANDOMLCSTATE *h_state )
	{	return cusdVD_randomLC( (dPMatrix)(MA), (ht)*(len), seed, d_MinVal, d_MaxVal, h_state );}
inline overror_t  cusdMD_random( dMatrix MA, ui ht, ui len, long seed, double *d_MinVal, double *d_MaxVal )
	{	return cusdVD_random( (dPMatrix)(MA), (ht)*(len), seed, d_MinVal, d_MaxVal );}
inline overror_t  cudaMD_outerprod( dMatrix MA, dVector X,  dVector Y, ui ht, ui len )
{	return cudaMDouterprod( (dPMatrix)(MA), X, Y, ht, len );}

inline overror_t  cudaMD_Row_equ0( dMatrix MA, ui ht, ui len, ui iRow )
	{	return cudaMDRow_equ0( (dPMatrix)MA, ht, len, iRow );}
inline overror_t  cudaMD_Col_equ0( dMatrix MA, ui ht, ui len, ui iRow )
	{	return cudaMDCol_equ0( (dPMatrix)MA, ht, len, iRow );}
inline overror_t  cudaMD_Dia_equ0( dMatrix MA, ui len )
	{	return cudaMDDia_equ0( (dPMatrix)(MA), len );}

inline overror_t  cudaMD_Row_equC( dMatrix MA, ui ht, ui len, ui iRow, double C )
	{	return cudaMDRow_equC( (dPMatrix)MA, ht, len, iRow, C );}
inline overror_t  cudaMD_Col_equC( dMatrix MA, ui ht, ui len, ui iRow, double C )
	{	return cudaMDCol_equC( (dPMatrix)MA, ht, len, iRow, C );}
inline overror_t  cudaMD_Dia_equC( dMatrix MA, ui len, double C )
	{	return cudaMDDia_equC( (dPMatrix)(MA), len, C );}

inline overror_t  cusdMD_Row_equC( dMatrix MA, ui ht, ui len, ui iRow, double *d_C )
	{	return cusdMDRow_equC( (dPMatrix)MA, ht, len, iRow, d_C );}
inline overror_t  cusdMD_Col_equC( dMatrix MA, ui ht, ui len, ui iRow, double *d_C )
	{	return cusdMDCol_equC( (dPMatrix)MA, ht, len, iRow, d_C );}
inline overror_t  cusdMD_Dia_equC( dMatrix MA, ui len, double *d_C )
	{	return cusdMDDia_equC( (dPMatrix)(MA), len, d_C );}

inline overror_t  cudaMD_Row_equV( dMatrix MA, ui ht, ui len, ui iRow, dVector X )
	{	return cudaMDRow_equV( (dPMatrix)MA, ht, len, iRow, X );}
inline overror_t  cudaMD_Col_equV( dMatrix MA, ui ht, ui len, ui iRow, dVector X )
	{	return cudaMDCol_equV( (dPMatrix)MA, ht, len, iRow, X );}
inline overror_t  cudaMD_Dia_equV( dMatrix MA, ui len, dVector X )
	{	return cudaMDDia_equV( (dPMatrix)(MA), len, X );}

inline overror_t  cudaMD_Trd_equM( dMatrix MA, dMatrix MTrd, ui len )
	{	return cudaMDTrd_equM( (dPMatrix)(MA), (dPMatrix)(MTrd), len );}
inline overror_t  cudaMD_Trd_extract( dMatrix MTrd, dMatrix MA, ui len )
	{	return cudaMDTrd_extract( (dPMatrix)(MTrd), (dPMatrix)(MA), len );}

inline overror_t cudaMD_equM( dMatrix MB, dMatrix MA, ui ht, ui len )
	{	return cudaVD_equV( (dPMatrix)MB, (dPMatrix)MA, (ht)*(len) );}
inline overror_t cudaMD_equMhost( dMatrix d_MB, dMatrix h_MA, ui ht, ui len )
	{	return cudaVD_equVhost( (dPMatrix)d_MB, (h_MA)[0], (ht)*(len) );}
inline overror_t MD_equMdevice( dMatrix h_MB, dMatrix d_MA, ui ht, ui len )
	{	return VD_equVdevice( h_MB[0], (dPMatrix)d_MA, (ht)*(len) );}
inline overror_t cudaMD_neg( dMatrix MB, dMatrix MA, ui ht, ui len )
	{	return cudaVD_neg( (dPMatrix)(MB), (dPMatrix)(MA), (ht)*(len) );}
inline overror_t  cudaMD_UequL( dMatrix MA, ui len )
	{	return cudaMDUequL( (dPMatrix)(MA), len );}
inline overror_t  cudaMD_LequU( dMatrix MA, ui len )
	{	return cudaMDLequU( (dPMatrix)(MA), len );}

            /* data-type conversions:  */
inline overror_t cudaM_FtoD( dMatrix MD, fMatrix MF, ui ht, ui len )
	{	return cudaV_FtoD( (dPMatrix)(MD), (fPMatrix)(MF), (ht)*(len) );}

            /* suitable windows for MD_spectrum: */
inline overror_t cudaMD_Hann( dMatrix MA, ui ht, ui len )
	{	return cudaMDHann( (dPMatrix)(MA), ht, len );}
#define cudaMDHanning cudaMDHann
inline overror_t cudaMD_Parzen( dMatrix MA, ui ht, ui len )
	{	return cudaMDParzen( (dPMatrix)(MA), ht, len );}
inline overror_t cudaMD_Welch( dMatrix MA, ui ht, ui len )
	{	return cudaMDWelch( (dPMatrix)(MA), ht, len );}

/********  Extracting a submatrix and copying a submatrix back  *********/

inline overror_t cudaMD_submatrix( dMatrix MSub, ui subHt, ui subLen, dMatrix MSrce, ui srceHt, ui srceLen,
                      ui firstRowInCol, ui sampInCol, ui firstColInRow, ui sampInRow )
	{	return cudaMDsubmatrix(  (dPMatrix)(MSub), subHt, subLen,
		                         (dPMatrix)(MSrce), srceHt, srceLen,
								 firstRowInCol, sampInCol, firstColInRow, sampInRow ); }

inline overror_t cudaMD_submatrix_equM( dMatrix MDest, ui destHt, ui destLen,
                           ui firstRowInCol, ui sampInCol, ui firstColInRow, ui sampInRow,
                           dMatrix MSrce, ui srceHt, ui srceLen )
	{	return cudaMDsubmatrix_equM(  (dPMatrix)(MDest), destHt, destLen,
                             firstRowInCol, sampInCol, firstColInRow, sampInRow,
							 (dPMatrix)(MSrce), srceHt, srceLen );}

inline overror_t cudaMD_equMblock( dMatrix MSub, ui subHt, ui subLen, dMatrix MSrce, ui srceHt, ui srceLen,
                      ui firstRowInCol, ui firstColInRow )
{	return cudaMDequMblock(  (dPMatrix)(MSub), subHt, subLen,
						   (dPMatrix)(MSrce), srceHt, srceLen, firstRowInCol, firstColInRow );}

inline overror_t cudaMD_block_equM( dMatrix MDest, ui destHt, ui destLen,
                       ui firstRowInCol, ui firstColInRow,
                       dMatrix MSrce, ui srceHt, ui srceLen )
	{	return cudaMDblock_equM( (dPMatrix)(MDest), destHt, destLen,
                             firstRowInCol, firstColInRow,
							 (dPMatrix)(MSrce), srceHt, srceLen );}

inline overror_t cudaMD_equMblockT( dMatrix MSub, ui subHt, ui subLen, dMatrix MSrce, ui srceHt, ui srceLen,
                      ui firstRowInCol, ui firstColInRow )
	{	return cudaMDequMblockT(  (dPMatrix)(MSub), subHt, subLen,
                             (dPMatrix)(MSrce), srceHt, srceLen,
							 firstRowInCol, firstColInRow );}

inline overror_t cudaMD_block_equMT( dMatrix MDest, ui destHt, ui destLen,
                       ui firstRowInCol, ui firstColInRow,
                       dMatrix MSrce, ui srceHt, ui srceLen )
	{	return cudaMDblock_equMT( (dPMatrix)(MDest), destHt, destLen,
                             firstRowInCol, firstColInRow,
							 (dPMatrix)(MSrce), srceHt, srceLen );}

/*****   Extracting a single row or a single column or the diagonal  ******
 *       and storing it into a vector                                     */

inline overror_t cudaMD_Row_extract( dVector Y, dMatrix MA, ui ht, ui len, ui iRow ) 
	{	return cudaMDRow_extract( Y, (dPMatrix)(MA), ht, len, iRow );}
inline overror_t cudaMD_Col_extract( dVector Y, dMatrix MA, ui ht, ui len, ui iCol ) 
	{	return cudaMDCol_extract( Y, (dPMatrix)(MA), ht, len, iCol );}
inline overror_t cudaMD_Dia_extract( dVector Y, dMatrix MA, ui len )
	{	return cudaMDDia_extract( Y, (dPMatrix)(MA), len );}

/**************  Deleting or inserting a row or a column   ***************/

inline overror_t cudaMD_Row_delete( dMatrix MB, dMatrix MA, ui htA, ui lenA, ui iRow )
	{	return cudaMDRow_delete( (dPMatrix)(MB), (dPMatrix)(MA), htA, lenA, iRow );}
inline overror_t cudaMD_Col_delete( dMatrix MB, dMatrix MA, ui htA, ui lenA, ui iCol )
	{	return cudaMDCol_delete( (dPMatrix)(MB), (dPMatrix)(MA), htA, lenA, iCol );}
inline overror_t cudaMD_Row_insert( dMatrix MB, dMatrix MA, ui htB, ui lenB, ui iRow, dVector X )
	{	return cudaMDRow_insert( (dPMatrix)(MB), (dPMatrix)(MA), htB, lenB, iRow, X );}
inline overror_t cudaMD_Col_insert( dMatrix MB, dMatrix MA, ui htB, ui lenB, ui iCol, dVector X )
	{	return cudaMDCol_insert( (dPMatrix)(MB), (dPMatrix)(MA), htB, lenB, iCol, X );}

/*****************    Basic arithmetic operations *********************
                      performed on one single row,
                      or one single column of any matrix,
                      or on the diagonal of a square matrix

    Note: In contrast to the analogous VectorLib functions, the operations
    are performed in-place, i.e. the input matrix itself is changed  */

inline overror_t cudaMD_Row_neg( dMatrix MA, ui ht, ui len, ui iRow )
	{	return cudaMDRow_neg( (dPMatrix)(MA), ht, len, iRow );}
inline overror_t cudaMD_Col_neg( dMatrix MA, ui ht, ui len, ui iCol )
	{	return cudaMDCol_neg( (dPMatrix)(MA), ht, len, iCol );}

inline overror_t cudaMD_Row_addC( dMatrix MA, ui ht, ui len, ui iRow, double C )
	{	return cudaMDRow_addC( (dPMatrix)(MA), ht, len, iRow, C );}
inline overror_t cudaMD_Col_addC( dMatrix MA, ui ht, ui len, ui iCol, double C )
	{	return cudaMDCol_addC( (dPMatrix)(MA), ht, len, iCol, C );}
inline overror_t cudaMD_Dia_addC( dMatrix MA, ui len, double C )
	{	return cudaMDDia_addC( (dPMatrix)(MA), len, C );}
inline overror_t cusdMD_Row_addC( dMatrix MA, ui ht, ui len, ui iRow, double *d_C )
	{	return cusdMDRow_addC( (dPMatrix)(MA), ht, len, iRow, d_C );}
inline overror_t cusdMD_Col_addC( dMatrix MA, ui ht, ui len, ui iCol, double *d_C )
	{	return cusdMDCol_addC( (dPMatrix)(MA), ht, len, iCol, d_C );}
inline overror_t cusdMD_Dia_addC( dMatrix MA, ui len, double *d_C )
	{	return cusdMDDia_addC( (dPMatrix)(MA), len, d_C );}

inline overror_t cudaMD_Row_addV( dMatrix MA, ui ht, ui len, ui iRow, dVector X )
	{	return cudaMDRow_addV( (dPMatrix)(MA), ht, len, iRow, X );}
inline overror_t cudaMD_Col_addV( dMatrix MA, ui ht, ui len, ui iCol, dVector X )
	{	return cudaMDCol_addV( (dPMatrix)(MA), ht, len, iCol, X );}
inline overror_t cudaMD_Dia_addV( dMatrix MA, ui len, dVector X )
	{	return cudaMDDia_addV( (dPMatrix)(MA), len, X );}

inline overror_t cudaMD_Row_subC( dMatrix MA, ui ht, ui len, ui iRow, double C )
	{	return cudaMDRow_subC( (dPMatrix)(MA), ht, len, iRow, C );}
inline overror_t cudaMD_Col_subC( dMatrix MA, ui ht, ui len, ui iCol, double C )
	{	return cudaMDCol_subC( (dPMatrix)(MA), ht, len, iCol, C );}
inline overror_t cudaMD_Dia_subC( dMatrix MA, ui len, double C )
	{	return cudaMDDia_subC( (dPMatrix)(MA), len, C );}
inline overror_t cusdMD_Row_subC( dMatrix MA, ui ht, ui len, ui iRow, double *d_C )
	{	return cusdMDRow_subC( (dPMatrix)(MA), ht, len, iRow, d_C );}
inline overror_t cusdMD_Col_subC( dMatrix MA, ui ht, ui len, ui iCol, double *d_C )
	{	return cusdMDCol_subC( (dPMatrix)(MA), ht, len, iCol, d_C );}
inline overror_t cusdMD_Dia_subC( dMatrix MA, ui len, double *d_C )
	{	return cusdMDDia_subC( (dPMatrix)(MA), len, d_C );}

inline overror_t cudaMD_Row_subV( dMatrix MA, ui ht, ui len, ui iRow, dVector X )
	{	return cudaMDRow_subV( (dPMatrix)(MA), ht, len, iRow, X );}
inline overror_t cudaMD_Col_subV( dMatrix MA, ui ht, ui len, ui iCol, dVector X )
	{	return cudaMDCol_subV( (dPMatrix)(MA), ht, len, iCol, X );}
inline overror_t cudaMD_Dia_subV( dMatrix MA, ui len, dVector X )
	{	return cudaMDDia_subV( (dPMatrix)(MA), len, X );}

inline overror_t cudaMD_Row_subrC( dMatrix MA, ui ht, ui len, ui iRow, double C )
	{	return cudaMDRow_subrC( (dPMatrix)(MA), ht, len, iRow, C );}
inline overror_t cudaMD_Col_subrC( dMatrix MA, ui ht, ui len, ui iCol, double C )
	{	return cudaMDCol_subrC( (dPMatrix)(MA), ht, len, iCol, C );}
inline overror_t cudaMD_Dia_subrC( dMatrix MA, ui len, double C )
	{	return cudaMDDia_subrC( (dPMatrix)(MA), len, C );}
inline overror_t cusdMD_Row_subrC( dMatrix MA, ui ht, ui len, ui iRow, double *d_C )
	{	return cusdMDRow_subrC( (dPMatrix)(MA), ht, len, iRow, d_C );}
inline overror_t cusdMD_Col_subrC( dMatrix MA, ui ht, ui len, ui iCol, double *d_C )
	{	return cusdMDCol_subrC( (dPMatrix)(MA), ht, len, iCol, d_C );}
inline overror_t cusdMD_Dia_subrC( dMatrix MA, ui len, double *d_C )
	{	return cusdMDDia_subrC( (dPMatrix)(MA), len, d_C );}

inline overror_t cudaMD_Row_subrV( dMatrix MA, ui ht, ui len, ui iRow, dVector X )
	{	return cudaMDRow_subrV( (dPMatrix)(MA), ht, len, iRow, X );}
inline overror_t cudaMD_Col_subrV( dMatrix MA, ui ht, ui len, ui iCol, dVector X )
	{	return cudaMDCol_subrV( (dPMatrix)(MA), ht, len, iCol, X );}
inline overror_t cudaMD_Dia_subrV( dMatrix MA, ui len, dVector X )
	{	return cudaMDDia_subrV( (dPMatrix)(MA), len, X );}

inline overror_t cudaMD_Row_mulC( dMatrix MA, ui ht, ui len, ui iRow, double C )
	{	return cudaMDRow_mulC( (dPMatrix)(MA), ht, len, iRow, C );}
inline overror_t cudaMD_Col_mulC( dMatrix MA, ui ht, ui len, ui iCol, double C )
	{	return cudaMDCol_mulC( (dPMatrix)(MA), ht, len, iCol, C );}
inline overror_t cudaMD_Dia_mulC( dMatrix MA, ui len, double C )
	{	return cudaMDDia_mulC( (dPMatrix)(MA), len, C );}
inline overror_t cusdMD_Row_mulC( dMatrix MA, ui ht, ui len, ui iRow, double *d_C )
	{	return cusdMDRow_mulC( (dPMatrix)(MA), ht, len, iRow, d_C );}
inline overror_t cusdMD_Col_mulC( dMatrix MA, ui ht, ui len, ui iCol, double *d_C )
	{	return cusdMDCol_mulC( (dPMatrix)(MA), ht, len, iCol, d_C );}
inline overror_t cusdMD_Dia_mulC( dMatrix MA, ui len, double *d_C )
	{	return cusdMDDia_mulC( (dPMatrix)(MA), len, d_C );}

inline overror_t cudaMD_Row_mulV( dMatrix MA, ui ht, ui len, ui iRow, dVector X )
	{	return cudaMDRow_mulV( (dPMatrix)(MA), ht, len, iRow, X );}
inline overror_t cudaMD_Col_mulV( dMatrix MA, ui ht, ui len, ui iCol, dVector X )
	{	return cudaMDCol_mulV( (dPMatrix)(MA), ht, len, iCol, X );}
inline overror_t cudaMD_Dia_mulV( dMatrix MA, ui len, dVector X )
	{	return cudaMDDia_mulV( (dPMatrix)(MA), len, X );}

inline overror_t cudaMD_Row_divC( dMatrix MA, ui ht, ui len, ui iRow, double C )
	{	return cudaMDRow_divC( (dPMatrix)(MA), ht, len, iRow, C );}
inline overror_t cudaMD_Col_divC( dMatrix MA, ui ht, ui len, ui iCol, double C )
	{	return cudaMDCol_divC( (dPMatrix)(MA), ht, len, iCol, C );}
inline overror_t cudaMD_Dia_divC( dMatrix MA, ui len, double C )
	{	return cudaMDDia_divC( (dPMatrix)(MA), len, C );}
inline overror_t cusdMD_Row_divC( dMatrix MA, ui ht, ui len, ui iRow, double *d_C )
	{	return cusdMDRow_divC( (dPMatrix)(MA), ht, len, iRow, d_C );}
inline overror_t cusdMD_Col_divC( dMatrix MA, ui ht, ui len, ui iCol, double *d_C )
	{	return cusdMDCol_divC( (dPMatrix)(MA), ht, len, iCol, d_C );}
inline overror_t cusdMD_Dia_divC( dMatrix MA, ui len, double *d_C )
	{	return cusdMDDia_divC( (dPMatrix)(MA), len, d_C );}

inline overror_t cudaMD_Row_divV( dMatrix MA, ui ht, ui len, ui iRow, dVector X )
	{	return cudaMDRow_divV( (dPMatrix)(MA), ht, len, iRow, X );}
inline overror_t cudaMD_Col_divV( dMatrix MA, ui ht, ui len, ui iCol, dVector X )
	{	return cudaMDCol_divV( (dPMatrix)(MA), ht, len, iCol, X );}
inline overror_t cudaMD_Dia_divV( dMatrix MA, ui len, dVector X )
	{	return cudaMDDia_divV( (dPMatrix)(MA), len, X );}

inline overror_t cudaMD_Row_divrC( dMatrix MA, ui ht, ui len, ui iRow, double C )
	{	return cudaMDRow_divrC( (dPMatrix)(MA), ht, len, iRow, C );}
inline overror_t cudaMD_Col_divrC( dMatrix MA, ui ht, ui len, ui iCol, double C )
	{	return cudaMDCol_divrC( (dPMatrix)(MA), ht, len, iCol, C );}
inline overror_t cudaMD_Dia_divrC( dMatrix MA, ui len, double C )
	{	return cudaMDDia_divrC( (dPMatrix)(MA), len, C );}
inline overror_t cusdMD_Row_divrC( dMatrix MA, ui ht, ui len, ui iRow, double *d_C )
	{	return cusdMDRow_divrC( (dPMatrix)(MA), ht, len, iRow, d_C );}
inline overror_t cusdMD_Col_divrC( dMatrix MA, ui ht, ui len, ui iCol, double *d_C )
	{	return cusdMDCol_divrC( (dPMatrix)(MA), ht, len, iCol, d_C );}
inline overror_t cusdMD_Dia_divrC( dMatrix MA, ui len, double *d_C )
	{	return cusdMDDia_divrC( (dPMatrix)(MA), len, d_C );}

inline overror_t cudaMD_Row_divrV( dMatrix MA, ui ht, ui len, ui iRow, dVector X )
	{	return cudaMDRow_divrV( (dPMatrix)(MA), ht, len, iRow, X );}
inline overror_t cudaMD_Col_divrV( dMatrix MA, ui ht, ui len, ui iCol, dVector X )
	{	return cudaMDCol_divrV( (dPMatrix)(MA), ht, len, iCol, X );}
inline overror_t cudaMD_Dia_divrV( dMatrix MA, ui len, dVector X )
	{	return cudaMDDia_divrV( (dPMatrix)(MA), len, X );}


/******  One-dimensional vector operations **********************
         performed along all rows or all columns simultaneously,
         or along the diagonal of a square matrix                */

inline overror_t cudaMD_Rows_max( dVector Y, dMatrix MA, ui ht, ui len )
	{	return cudaMDRows_max( Y, (dPMatrix)(MA), ht, len );}
inline overror_t cudaMD_Cols_max( dVector Y, dMatrix MA, ui ht, ui len )
	{	return cudaMDCols_max( Y, (dPMatrix)(MA), ht, len );}
inline overror_t cudaMD_Dia_max(  double *h_RetValPtr, dMatrix MA, ui len )
	{	return cudaMDDia_max(  h_RetValPtr, (dPMatrix)(MA), len );}
inline overror_t cusdMD_Dia_max(  double *d_RetValPtr, dMatrix MA, ui len )
	{	return cusdMDDia_max(  d_RetValPtr, (dPMatrix)(MA), len );}
inline overror_t cudaMD_Rows_min( dVector Y, dMatrix MA, ui ht, ui len )
	{	return cudaMDRows_min( Y, (dPMatrix)(MA), ht, len );}
inline overror_t cudaMD_Cols_min( dVector Y, dMatrix MA, ui ht, ui len )
	{	return cudaMDCols_min( Y, (dPMatrix)(MA), ht, len );}
inline overror_t cudaMD_Dia_min(  double *h_RetValPtr, dMatrix MA, ui len )
	{	return cudaMDDia_min(  h_RetValPtr, (dPMatrix)(MA), len );}
inline overror_t cusdMD_Dia_min(  double *d_RetValPtr, dMatrix MA, ui len )
	{	return cusdMDDia_min(  d_RetValPtr, (dPMatrix)(MA), len );}

inline overror_t cudaMD_Rows_absmax( dVector Y, dMatrix MA, ui ht, ui len )
	{	return cudaMDRows_absmax( Y, (dPMatrix)(MA), ht, len );}
inline overror_t cudaMD_Cols_absmax( dVector Y, dMatrix MA, ui ht, ui len )
	{	return cudaMDCols_absmax( Y, (dPMatrix)(MA), ht, len );}
inline overror_t cudaMD_Dia_absmax(  double *h_RetValPtr, dMatrix MA, ui len )
	{	return cudaMDDia_absmax(  h_RetValPtr, (dPMatrix)(MA), len );}
inline overror_t cusdMD_Dia_absmax(  double *d_RetValPtr, dMatrix MA, ui len )
	{	return cusdMDDia_absmax(  d_RetValPtr, (dPMatrix)(MA), len );}
inline overror_t cudaMD_Rows_absmin( dVector Y, dMatrix MA, ui ht, ui len )
	{	return cudaMDRows_absmin( Y, (dPMatrix)(MA), ht, len );}
inline overror_t cudaMD_Cols_absmin( dVector Y, dMatrix MA, ui ht, ui len )
	{	return cudaMDCols_absmin( Y, (dPMatrix)(MA), ht, len );}
inline overror_t cudaMD_Dia_absmin(  double *h_RetValPtr, dMatrix MA, ui len )
	{	return cudaMDDia_absmin(  h_RetValPtr, (dPMatrix)(MA), len );}
inline overror_t cusdMD_Dia_absmin(  double *d_RetValPtr, dMatrix MA, ui len )
	{	return cusdMDDia_absmin(  d_RetValPtr, (dPMatrix)(MA), len );}

inline overror_t cudaMD_Rows_sum( dVector Y, dMatrix MA, ui ht, ui len )
	{	return cudaMDRows_sum( Y, (dPMatrix)(MA), ht, len );}
inline overror_t cudaMD_Cols_sum( dVector Y, dMatrix MA, ui ht, ui len )
	{	return cudaMDCols_sum( Y, (dPMatrix)(MA), ht, len );}
inline overror_t cudaMD_Dia_sum(  double *h_RetValPtr, dMatrix MA, ui len )
	{	return cudaMDDia_sum(  h_RetValPtr, (dPMatrix)(MA), len );}
inline overror_t cusdMD_Dia_sum(  double *d_RetValPtr, dMatrix MA, ui len )
	{	return cusdMDDia_sum(  d_RetValPtr, (dPMatrix)(MA), len );}
inline overror_t cudaMD_Rows_ssq( dVector Y, dMatrix MA, ui ht, ui len )
	{	return cudaMDRows_ssq( Y, (dPMatrix)(MA), ht, len );}
inline overror_t cudaMD_Cols_ssq( dVector Y, dMatrix MA, ui ht, ui len )
	{	return cudaMDCols_ssq( Y, (dPMatrix)(MA), ht, len );}
inline overror_t cudaMD_Dia_ssq(  double *h_RetValPtr, dMatrix MA, ui len )
	{	return cudaMDDia_ssq(  h_RetValPtr, (dPMatrix)(MA), len );}
inline overror_t cusdMD_Dia_ssq(  double *d_RetValPtr, dMatrix MA, ui len )
	{	return cusdMDDia_ssq(  d_RetValPtr, (dPMatrix)(MA), len );}
inline overror_t cudaMD_Rows_prod( dVector Y, dMatrix MA, ui ht, ui len )
	{	return cudaMDRows_prod( Y, (dPMatrix)(MA), ht, len );}
inline overror_t cudaMD_Cols_prod( dVector Y, dMatrix MA, ui ht, ui len )
	{	return cudaMDCols_prod( Y, (dPMatrix)(MA), ht, len );}
inline overror_t cudaMD_Dia_prod(  double *h_RetValPtr, dMatrix MA, ui len )
	{	return cudaMDDia_prod(  h_RetValPtr, (dPMatrix)(MA), len );}
inline overror_t cusdMD_Dia_prod(  double *d_RetValPtr, dMatrix MA, ui len )
	{	return cusdMDDia_prod(  d_RetValPtr, (dPMatrix)(MA), len );}

inline overror_t cudaMD_Rows_runsum( dMatrix MA, ui ht, ui len )
	{	return cudaMDRows_runsum( (dPMatrix)(MA), ht, len );}
inline overror_t cudaMD_Cols_runsum( dMatrix MA, ui ht, ui len )
	{	return cudaMDCols_runsum( (dPMatrix)(MA), ht, len );}
inline overror_t cudaMD_Rows_runprod( dMatrix MA, ui ht, ui len )
	{	return cudaMDRows_runprod( (dPMatrix)(MA), ht, len );}
inline overror_t cudaMD_Cols_runprod( dMatrix MA, ui ht, ui len )
	{	return cudaMDCols_runprod( (dPMatrix)(MA), ht, len );}

inline overror_t cudaMD_Rows_rotate( dMatrix MA, ui ht, ui len, ssize_t pos)
	{	return cudaMDRows_rotate( (dPMatrix)(MA), ht, len, pos );}
inline overror_t cudaMD_Cols_rotate( dMatrix MA, ui ht, ui len, ssize_t pos)
	{	return cudaMDCols_rotate( (dPMatrix)(MA), ht, len, pos );}
inline overror_t cudaMD_Rows_rotate_buf( dMatrix MA, ui ht, ui len, ssize_t pos, dMatrix MBuf) 
	{	return cudaMDRows_rotate_buf( (dPMatrix)(MA), ht, len, pos, (dPMatrix)(MBuf) );}
inline overror_t cudaMD_Cols_rotate_buf( dMatrix MA, ui ht, ui len, ssize_t pos, dMatrix MBuf) 
	{	return cudaMDCols_rotate_buf( (dPMatrix)(MA), ht, len, pos, (dPMatrix)(MBuf) );}
inline overror_t cudaMD_Rows_reflect( dMatrix MA, ui ht, ui len )
	{	return cudaMDRows_reflect( (dPMatrix)(MA), ht, len );}
inline overror_t cudaMD_Cols_reflect( dMatrix MA, ui ht, ui len )
	{	return cudaMDCols_reflect( (dPMatrix)(MA), ht, len );}
inline overror_t cudaMD_Rows_rev( dMatrix MA, ui ht, ui len )
	{	return cudaMDRows_rev( (dPMatrix)(MA), ht, len );}
inline overror_t cudaMD_Cols_rev( dMatrix MA, ui ht, ui len )
	{	return cudaMDCols_rev( (dPMatrix)(MA), ht, len );}
inline overror_t  cudaMD_Rows_distribution( uiMatrix MAbund, dVector Limits, ui nBins, dMatrix MX, ui ht, ui len, int mode )
	{	return cudaMDRows_distribution( (uiPMatrix)MAbund, Limits, nBins, (dPMatrix)MX, ht, len, mode ); }
inline overror_t  cudaMD_Cols_distribution( uiMatrix MAbund, dVector Limits, ui nBins, dMatrix MX, ui ht, ui len, int mode )
	{	return cudaMDCols_distribution( (uiPMatrix)MAbund, Limits, nBins, (dPMatrix)MX, ht, len, mode ); }

/********  Operations involving two rows or two colums of one matrix  *****/

inline overror_t cudaMD_Rows_exchange( dMatrix MA, ui ht, ui len, ui row1, ui row2 )
	{	return cudaMDRows_exchange( (dPMatrix)(MA), ht, len, row1, row2 );}
inline overror_t cudaMD_Cols_exchange( dMatrix MA, ui ht, ui len, ui col1, ui col2 )
	{	return cudaMDCols_exchange( (dPMatrix)(MA), ht, len, col1, col2 );}

inline overror_t cudaMD_Rows_add( dMatrix MA, ui ht, ui len, ui destRow, ui srceRow )
	{	return cudaMDRows_add( (dPMatrix)(MA), ht, len, destRow, srceRow );}
inline overror_t cudaMD_Cols_add( dMatrix MA, ui ht, ui len, ui destCol, ui srceCol )
	{	return cudaMDCols_add( (dPMatrix)(MA), ht, len, destCol, srceCol );}
                         /* dest[i] += source[i]  */

inline overror_t cudaMD_Rows_sub( dMatrix MA, ui ht, ui len, ui destRow, ui srceRow )
	{	return cudaMDRows_sub( (dPMatrix)(MA), ht, len, destRow, srceRow );}
inline overror_t cudaMD_Cols_sub( dMatrix MA, ui ht, ui len, ui destCol, ui srceCol )
	{	return cudaMDCols_sub( (dPMatrix)(MA), ht, len, destCol, srceCol );}
                         /* dest[i] -= source[i]  */

inline overror_t cudaMD_Rows_Cadd( dMatrix MA, ui ht, ui len, ui destRow, ui srceRow, double C )
	{	return cudaMDRows_Cadd( (dPMatrix)(MA), ht, len, destRow, srceRow, C );}
inline overror_t cudaMD_Cols_Cadd( dMatrix MA, ui ht, ui len, ui destCol, ui srceCol, double C )
	{	return cudaMDCols_Cadd( (dPMatrix)(MA), ht, len, destCol, srceCol, C );}
inline overror_t cusdMD_Rows_Cadd( dMatrix MA, ui ht, ui len, ui destRow, ui srceRow, double *d_C )
	{	return cusdMDRows_Cadd( (dPMatrix)(MA), ht, len, destRow, srceRow, d_C );}
inline overror_t cusdMD_Cols_Cadd( dMatrix MA, ui ht, ui len, ui destCol, ui srceCol, double *d_C )
	{	return cusdMDCols_Cadd( (dPMatrix)(MA), ht, len, destCol, srceCol, d_C );}
                         /* dest[i] += C * source[i]  */

inline overror_t cudaMD_Rows_lincomb( dMatrix MA, ui ht, ui len, ui destRow, double destC, ui srceRow, double srceC )
	{	return cudaMDRows_lincomb( (dPMatrix)(MA), ht, len, destRow, destC, srceRow, srceC );}
inline overror_t cudaMD_Cols_lincomb( dMatrix MA, ui ht, ui len, ui destCol, double destC, ui srceCol, double srceC )
	{	return cudaMDCols_lincomb( (dPMatrix)(MA), ht, len, destCol, destC, srceCol, srceC );}
inline overror_t cusdMD_Rows_lincomb( dMatrix MA, ui ht, ui len, ui destRow, double *d_destC, ui srceRow, double *d_srceC )
	{	return cusdMDRows_lincomb( (dPMatrix)(MA), ht, len, destRow, d_destC, srceRow, d_srceC );}
inline overror_t cusdMD_Cols_lincomb( dMatrix MA, ui ht, ui len, ui destCol, double *d_destC, ui srceCol, double *d_srceC )
	{	return cusdMDCols_lincomb( (dPMatrix)(MA), ht, len, destCol, d_destC, srceCol, d_srceC );}
  /*  linear combination: dest[i] = destC * dest[i] + sourceC * source[i] */


/*********************  Center of gravity *****************************/
inline overror_t cudaMD_centerOfGravityInd( dComplex *h_RetValPtr, dMatrix MA, ui ht, ui len )
	{	return cudaMDcenterOfGravityInd( h_RetValPtr, (dPMatrix)(MA), ht, len );}
inline overror_t cudaMD_centerOfGravityV( dComplex *h_RetValPtr, dVector X, dVector Y, dMatrix MA, ui ht, ui len )
	{	return cudaMDcenterOfGravityV( h_RetValPtr, X, Y, (dPMatrix)(MA), ht, len );}
inline overror_t cusdMD_centerOfGravityInd( dComplex *d_RetValPtr, dMatrix MA, ui ht, ui len )
	{	return cusdMDcenterOfGravityInd( d_RetValPtr, (dPMatrix)(MA), ht, len );}
inline overror_t cusdMD_centerOfGravityV( dComplex *d_RetValPtr, dVector X, dVector Y, dMatrix MA, ui ht, ui len )
	{	return cusdMDcenterOfGravityV( d_RetValPtr, X, Y, (dPMatrix)(MA), ht, len );}

/*************** Transposing and rotating a matrix **********************/

inline overror_t cudaMD_transpose( dMatrix MTr, dMatrix MA, ui htTr, ui lenTr )
	{	return cudaMDtranspose( (dPMatrix)(MTr), (dPMatrix)(MA), htTr, lenTr );}
       /*  dimensions htTr, lenTr are those of the transposed matrix, not of the original!   */
inline overror_t cudaMD_rotate90( dMatrix MRot, dMatrix MA, ui htRot, ui lenRot )
	{	return cudaMDrotate90( (dPMatrix)(MRot), (dPMatrix)(MA), htRot, lenRot );}
inline overror_t cudaMD_rotate180( dMatrix MRot, dMatrix MA, ui htRot, ui lenRot )
	{	return cudaVD_rev( (dPMatrix)(MRot), (dPMatrix)(MA), (htRot)*(lenRot) );}
inline overror_t cudaMD_rotate270( dMatrix MRot, dMatrix MA, ui htRot, ui lenRot )
	{	return cudaMDrotate270( (dPMatrix)(MRot), (dPMatrix)(MA), htRot, lenRot );}
inline overror_t cudaMD_transpose_buf( dMatrix MTr, dMatrix MA, ui htTr, ui lenTr, dMatrix MBuf )
	{	return cudaMDtranspose_buf( (dPMatrix)(MTr), (dPMatrix)(MA), htTr, lenTr, (dPMatrix)(MBuf) );}

 /********************** Interpolation of Matrix elements **************/

inline overror_t cudaMD_polyinterpol( dMatrix MZ, dVector X, dVector Y, ui ht, ui len, 
									dVector XTab, dVector YTab, dMatrix MZTab, ui httab, ui lentab, unsigned degX, unsigned degY )
	{	return cudaMDpolyinterpol( (dPMatrix)(MZ), X, Y, ht, len, XTab, YTab, (dPMatrix)(MZTab), httab, lentab, degX, degY );}
inline overror_t cudaMD_ratinterpol( dMatrix MZ, dVector X, dVector Y, ui ht, ui len, 
									dVector XTab, dVector YTab, dMatrix MZTab, ui httab, ui lentab, unsigned degX, unsigned degY )
	{	return cudaMDratinterpol( (dPMatrix)(MZ), X, Y, ht, len, XTab, YTab, (dPMatrix)(MZTab), httab, lentab, degX, degY );}
inline overror_t cudaMD_natCubSplineInterpol( dMatrix MZ, dVector X, dVector Y, ui ht, ui len, 
									dVector XTab, dVector YTab, dMatrix MZTab, ui httab, ui lentab )
	{	return cudaMDnatCubSplineInterpol( (dPMatrix)(MZ), X, Y, ht, len, XTab, YTab, (dPMatrix)(MZTab), httab, lentab );}

/************************ Matrix Arithmetics *************************/

inline overror_t cudaMD_addM( dMatrix MC, dMatrix MA, dMatrix MB, ui htA, ui lenA )
	{	return cudaVD_addV( (dPMatrix)(MC), (dPMatrix)(MA), (dPMatrix)(MB), (htA)*(lenA) );}
inline overror_t cudaMD_addMT( dMatrix MC, dMatrix MA, dMatrix MB, ui htA, ui lenA )
	{	return cudaMDaddMT( (dPMatrix)(MC), (dPMatrix)(MA), (dPMatrix)(MB), htA, lenA );}
inline overror_t cudaMD_subM( dMatrix MC, dMatrix MA, dMatrix MB, ui htA, ui lenA )
	{	return cudaVD_subV( (dPMatrix)(MC), (dPMatrix)(MA), (dPMatrix)(MB), (htA)*(lenA) );}
inline overror_t cudaMD_subMT( dMatrix MC, dMatrix MA, dMatrix MB, ui htA, ui lenA )
	{	return cudaMDsubMT( (dPMatrix)(MC), (dPMatrix)(MA), (dPMatrix)(MB), htA, lenA );}
inline overror_t cudaMD_subrM( dMatrix MC, dMatrix MA, dMatrix MB, ui htA, ui lenA )
	{	return cudaVD_subrV( (dPMatrix)(MC), (dPMatrix)(MA), (dPMatrix)(MB), (htA)*(lenA) );}
inline overror_t cudaMD_subrMT( dMatrix MC, dMatrix MA, dMatrix MB, ui htA, ui lenA )
	{	return cudaMDsubrMT( (dPMatrix)(MC), (dPMatrix)(MA), (dPMatrix)(MB), htA, lenA );}
inline overror_t cudaMD_mulC( dMatrix MB, dMatrix MA, ui htA, ui lenA, double C )
	{	return cudaVD_mulC( (dPMatrix)(MB), (dPMatrix)(MA), (htA)*(lenA), C );}
inline overror_t cudaMD_divC( dMatrix MB, dMatrix MA, ui htA, ui lenA, double C )
	{	return cudaVD_divC( (dPMatrix)(MB), (dPMatrix)(MA), (htA)*(lenA), C );}
inline overror_t cusdMD_mulC( dMatrix MB, dMatrix MA, ui htA, ui lenA, double *d_C )
	{	return cusdVD_mulC( (dPMatrix)(MB), (dPMatrix)(MA), (htA)*(lenA), d_C );}
inline overror_t cusdMD_divC( dMatrix MB, dMatrix MA, ui htA, ui lenA, double *d_C )
	{	return cusdVD_divC( (dPMatrix)(MB), (dPMatrix)(MA), (htA)*(lenA), d_C );}

inline overror_t cudaMDs_addM( dMatrix MC, dMatrix MA, dMatrix MB, ui htA, ui lenA, double C )
	{	return cudaVDs_addV( (dPMatrix)(MC), (dPMatrix)(MA), (dPMatrix)(MB), (htA)*(lenA), C );}
inline overror_t cudaMDs_addMT( dMatrix MC, dMatrix MA, dMatrix MB, ui htA, ui lenA, double C )
	{	return cudaMDsaddMT( (dPMatrix)(MC), (dPMatrix)(MA), (dPMatrix)(MB), htA, lenA, C );}
inline overror_t cudaMDs_subM( dMatrix MC, dMatrix MA, dMatrix MB, ui htA, ui lenA, double C )
	{	return cudaVDs_subV( (dPMatrix)(MC), (dPMatrix)(MA), (dPMatrix)(MB), (htA)*(lenA), C );}
inline overror_t cudaMDs_subMT( dMatrix MC, dMatrix MA, dMatrix MB, ui htA, ui lenA, double C )
	{	return cudaMDssubMT( (dPMatrix)(MC), (dPMatrix)(MA), (dPMatrix)(MB), htA, lenA, C );}
inline overror_t cudaMDs_subrM( dMatrix MC, dMatrix MA, dMatrix MB, ui htA, ui lenA, double C )
	{	return cudaVDs_subrV( (dPMatrix)(MC), (dPMatrix)(MA), (dPMatrix)(MB), (htA)*(lenA), C );}
inline overror_t cudaMDs_subrMT( dMatrix MC, dMatrix MA, dMatrix MB, ui htA, ui lenA, double C )
	{	return cudaMDssubrMT( (dPMatrix)(MC), (dPMatrix)(MA), (dPMatrix)(MB), htA, lenA, C );}
inline overror_t cusdMDs_addM( dMatrix MC, dMatrix MA, dMatrix MB, ui htA, ui lenA, double *d_C )
	{	return cusdVDs_addV( (dPMatrix)(MC), (dPMatrix)(MA), (dPMatrix)(MB), (htA)*(lenA), d_C );}
inline overror_t cusdMDs_addMT( dMatrix MC, dMatrix MA, dMatrix MB, ui htA, ui lenA, double *d_C )
	{	return cusdMDsaddMT( (dPMatrix)(MC), (dPMatrix)(MA), (dPMatrix)(MB), htA, lenA, d_C );}
inline overror_t cusdMDs_subM( dMatrix MC, dMatrix MA, dMatrix MB, ui htA, ui lenA, double *d_C )
	{	return cusdVDs_subV( (dPMatrix)(MC), (dPMatrix)(MA), (dPMatrix)(MB), (htA)*(lenA), d_C );}
inline overror_t cusdMDs_subMT( dMatrix MC, dMatrix MA, dMatrix MB, ui htA, ui lenA, double *d_C )
	{	return cusdMDssubMT( (dPMatrix)(MC), (dPMatrix)(MA), (dPMatrix)(MB), htA, lenA, d_C );}
inline overror_t cusdMDs_subrM( dMatrix MC, dMatrix MA, dMatrix MB, ui htA, ui lenA, double *d_C )
	{	return cusdVDs_subrV( (dPMatrix)(MC), (dPMatrix)(MA), (dPMatrix)(MB), (htA)*(lenA), d_C );}
inline overror_t cusdMDs_subrMT( dMatrix MC, dMatrix MA, dMatrix MB, ui htA, ui lenA, double *d_C )
	{	return cusdMDssubrMT( (dPMatrix)(MC), (dPMatrix)(MA), (dPMatrix)(MB), htA, lenA, d_C );}

inline overror_t cudaMD_lincomb( dMatrix MC, dMatrix MA, dMatrix MB, ui htA, ui lenA, double CA, double CB )
	{	return cudaVD_lincomb( (dPMatrix)(MC), (dPMatrix)(MA), (dPMatrix)(MB), (htA)*(lenA), CA, CB );}
inline overror_t cusdMD_lincomb( dMatrix MC, dMatrix MA, dMatrix MB, ui htA, ui lenA, double *d_CA, double *d_CB )
	{	return cusdVD_lincomb( (dPMatrix)(MC), (dPMatrix)(MA), (dPMatrix)(MB), (htA)*(lenA), d_CA, d_CB );}

inline overror_t cudaMD_mulV( dVector Y, dMatrix MA, dVector X, ui htA, ui lenA )
	{	return cudaMDmulV( Y, (dPMatrix)(MA), X, htA, lenA );}
             /*  Y = MA * X.  sizX=lenA, sizY=htA;   both X and Y are column-vectors    */
inline overror_t cudaMD_TmulV( dVector Y, dMatrix MA, dVector X, ui htA, ui lenA )
	{	return cudaMDTmulV( Y, (dPMatrix)(MA), X, htA, lenA );}
            /*  Y = MAT * X.  sizX=htA, sizY=lenA;   both X and Y are column-vectors    */
inline overror_t cudaVD_mulM( dVector Y, dVector X, dMatrix MA, ui htA, ui lenA )
	{	return cudaVDmulM( Y, X, (dPMatrix)(MA), htA, lenA );}
            /*  Y = X * MA.  sizX=htA, sizY=lenA;    both X and Y are row-vectors.
                             Mind the prefix: cudaVD_ (not cudaMD_)    */
inline overror_t cudaVD_mulMT( dVector Y, dVector X, dMatrix MA, ui htA, ui lenA )
	{	return cudaVDmulMT( Y, X, (dPMatrix)(MA), htA, lenA );}
            /*  Y = X * MAT.  sizX=lenA, sizY=htA;   both X and Y are row-vectors.   */
inline overror_t cudaMD_mulM( dMatrix MC, dMatrix MA, dMatrix MB, ui htA, ui lenA, ui lenB )
	{	return cudaMDmulM( (dPMatrix)(MC), (dPMatrix)(MA), (dPMatrix)(MB), htA, lenA, lenB );}
                         /*  MC = MA * MB.  htB=lenA, htC=htA, lenC=lenB */
inline overror_t cudaMD_mulMT( dMatrix MC, dMatrix MA, dMatrix MB, ui htA, ui lenA, ui htB )
	{	return cudaMDmulMT( (dPMatrix)(MC), (dPMatrix)(MA), (dPMatrix)(MB), htA, lenA, htB );}
                         /*  MC = MA * MBT.  lenB=lenA, htC=htA, lenC=htB */
inline overror_t cudaMD_TmulM( dMatrix MC, dMatrix MA, dMatrix MB, ui htA, ui lenA, ui lenB )
	{	return cudaMDTmulM( (dPMatrix)(MC), (dPMatrix)(MA), (dPMatrix)(MB), htA, lenA, lenB );}
                         /*  MC = MAT * MB.  htB=htA, htC=lenA, lenC=lenB */
inline overror_t cudaMD_TmulMT( dMatrix MC, dMatrix MA, dMatrix MB, ui htA, ui lenA, ui htB )
	{	return cudaMDTmulMT( (dPMatrix)(MC), (dPMatrix)(MA), (dPMatrix)(MB), htA, lenA, htB );}
                         /*  MC = MAT * MBT.  lenB=htA, htC=lenA, lenC=htB */
inline overror_t cudaMDdia_mulM(  dMatrix MC, dVector MADia, dMatrix MB, ui htB, ui lenB )
	{	return cudaMDdiamulM(  (dPMatrix)(MC), MADia, (dPMatrix)(MB), htB, lenB );}
inline overror_t cudaMDdia_mulMT(  dMatrix MC, dVector MADia, dMatrix MB, ui htB, ui lenB )
	{	return cudaMDdiamulMT(  (dPMatrix)(MC), MADia, (dPMatrix)(MB), htB, lenB );}
inline overror_t cudaMD_mulMdia(  dMatrix MC, dMatrix MA, dVector MBDia, ui htA, ui lenA )
	{	return cudaMDmulMdia(  (dPMatrix)(MC), (dPMatrix)(MA), MBDia, htA, lenA );}
inline overror_t cudaMD_TmulMdia(  dMatrix MC, dMatrix MA, dVector MBDia, ui htA, ui lenA )
	{	return cudaMDTmulMdia(  (dPMatrix)(MC), (dPMatrix)(MA), MBDia, htA, lenA );}

/***************** Two-Dimensional Fourier-Transform Methods ************/

inline overror_t cudaMD_FFT( dMatrix MY, dMatrix MX, ui ht, ui len, int dir )
	{	return cudaMDFFT( (dPMatrix)(MY), (dPMatrix)(MX), ht, len, dir );}
inline overror_t cudaMD_Rows_FFT( dMatrix MY, dMatrix MX, ui ht, ui len, int dir )
	{	return cudaMDRows_FFT( (dPMatrix)(MY), (dPMatrix)(MX), ht, len, dir );}
inline overror_t cudaMD_Cols_FFT( dMatrix MY, dMatrix MX, ui ht, ui len, int dir )
	{	return cudaMDCols_FFT( (dPMatrix)(MY), (dPMatrix)(MX), ht, len, dir );}
inline overror_t cudaMD_FFTtoC( cdMatrix MY, dMatrix MX, ui ht, ui len )
	{	return cudaMDFFTtoC( (cdPMatrix)(MY), (dPMatrix)(MX), ht, len );}
inline overror_t cudaMD_Rows_FFTtoC( cdMatrix MY, dMatrix MX, ui ht, ui len )
	{	return cudaMDRows_FFTtoC( (cdPMatrix)(MY), (dPMatrix)(MX), ht, len );}
inline overror_t cudaMD_Cols_FFTtoC( cdMatrix MY, dMatrix MX, ui ht, ui len )
	{	return cudaMDCols_FFTtoC( (cdPMatrix)(MY), (dPMatrix)(MX), ht, len );}
inline overror_t cudaMD_convolve( dMatrix MY, dMatrix MFlt, dMatrix MX, dMatrix MRsp, ui ht, ui len )
	{	return cudaMDconvolve( (dPMatrix)(MY), (dPMatrix)(MFlt), (dPMatrix)(MX), (dPMatrix)(MRsp), ht, len );}
inline overror_t cudaMD_deconvolve( dMatrix MY, dMatrix MFlt, dMatrix MX, dMatrix MRsp, ui ht, ui len )
	{	return cudaMDdeconvolve( (dPMatrix)(MY), (dPMatrix)(MFlt), (dPMatrix)(MX), (dPMatrix)(MRsp), ht, len );}
inline overror_t cudaMD_filter( dMatrix MY, dMatrix MX, dMatrix MFlt, ui ht, ui len )
	{	return cudaMDfilter( (dPMatrix)(MY), (dPMatrix)(MX), (dPMatrix)(MFlt), ht, len );}
inline overror_t cudaMD_autocorr( dMatrix MACorr, dMatrix MX, ui ht, ui len )
	{	return cudaMDautocorr( (dPMatrix)(MACorr), (dPMatrix)(MX), ht, len );}
inline overror_t cudaMD_xcorr( dMatrix MXCorr, dMatrix MX, dMatrix MY, ui ht, ui len)
	{	return cudaMDxcorr( (dPMatrix)(MXCorr), (dPMatrix)(MX), (dPMatrix)(MY), ht, len );}
inline overror_t cudaMD_spectrum( dMatrix MSpec, ui htSpec, ui lenSpec, dMatrix MX, ui htX, ui lenX, dMatrix MWin )
	{	return cudaMDspectrum( (dPMatrix)(MSpec), htSpec, lenSpec, (dPMatrix)(MX), htX, lenX, (dPMatrix)(MWin) );}
              /*   htSpec, lenSpec must be 2**n,
                   MSpec must be a (htSpec+1)*(lenSpec+1) matrix!!
                   htX >= n*htSpec,  lenX >= n*lenSpec,
                   htWin = 2*htSpec, lenWin = 2*lenSpec */

/**************************  Input and Output  **************************
	The input/output functions involve memory transfers from device
	to host memory or vice versa. The generic cudaMD_input/output functions
	allocate their own host buffers, whereas the cudaMD_xxx_buf functions
	take a user-supplied buffer vector h_Wk (size must be >= ht*len )
	and are much more efficient.                                       */

inline overror_t cudaMD_fprint( FILE *stream, dMatrix MA, ui ht, ui len, unsigned linewidth )
	{	return cudaMDfprint( stream, (dPMatrix)(MA), ht, len, linewidth ); }
inline overror_t cudaMD_print( dMatrix MA, ui ht, ui len )
	{	return cudaMDfprint( stdout, (dPMatrix)(MA), ht, len, 80 ); }
inline overror_t cudaMD_cprint( dMatrix MA, ui ht, ui len )
	{	return cudaMDcprint( (dPMatrix)(MA), ht, len ); }
inline overror_t cudaMD_fprint_buf( FILE *stream, dMatrix d_MA, ui ht, ui len, unsigned linewidth, dVector h_Wk )
	{	return cudaMDfprint_buf( stream, (dPMatrix)(d_MA), ht, len, linewidth, h_Wk ); }
inline overror_t cudaMD_print_buf( dMatrix d_MA, ui ht, ui len, dVector h_Wk )
	{	return cudaMDfprint_buf( stdout, (dPMatrix)(d_MA), ht, len, 80, h_Wk ); }
inline overror_t cudaMD_cprint_buf( dMatrix d_MA, ui ht, ui len, dVector h_Wk )
	{	return cudaMDcprint_buf( (dPMatrix)(d_MA), ht, len, h_Wk ); }
		/*  cudaMD_print, cudaMD_cprint usable only for console applications! */
inline overror_t  cudaMD_write( FILE *stream, dMatrix MA, ui ht, ui len )
	{	return cudaMDwrite( stream, (dPMatrix)(MA), ht, len ); }
inline overror_t cudaMD_read( dMatrix MA, ui ht, ui len, FILE *stream )
	{	return cudaMDread( (dPMatrix)(MA), ht, len, stream ); }
inline overror_t  cudaMD_write_buf( FILE *stream, dMatrix d_MA, ui ht, ui len, dVector h_Wk )
	{	return cudaMDwrite_buf( stream, (dPMatrix)(d_MA), ht, len, h_Wk ); }
inline overror_t cudaMD_read_buf( dMatrix d_MA, ui ht, ui len, FILE *stream, dVector h_Wk )
	{	return cudaMDread_buf( (dPMatrix)(d_MA), ht, len, stream, h_Wk ); }
                                   /* write and read in ascii format */
inline overror_t cudaMD_store( FILE *stream, dMatrix MA, ui ht, ui len )
{	return cudaVD_store( stream, (dPMatrix)(MA), (len)*(ht) ); }
inline overror_t cudaMD_recall( dMatrix MA, ui ht, ui len, FILE *stream )
	{	return cudaVD_recall( (dPMatrix)(MA), (len)*(ht), stream ); }
inline overror_t cudaMD_store_buf( FILE *stream, dMatrix d_MA, ui ht, ui len, dVector h_Wk )
{	return cudaVD_store_buf( stream, (dPMatrix)(d_MA), (len)*(ht), h_Wk ); }
inline overror_t cudaMD_recall_buf( dMatrix d_MA, ui ht, ui len, FILE *stream, dVector h_Wk )
	{	return cudaVD_recall_buf( (dPMatrix)(d_MA), (len)*(ht), stream, h_Wk ); }
                                  /* store and recall in binary format */

#else  /* plain-C, not C++: type-cast used to transform dMatrix into dPMatrix  */

/***  Addressing single elements of dynamically allocated matrices: ******/

#define cudaMD_setElement( MA, ht, len, m, n, C ) cudaMDsetElement( (dPMatrix)(MA), ht, len, m, n, C )
#define cusdMD_setElement( MA, ht, len, m, n, C ) cusdMDsetElement( (dPMatrix)(MA), ht, len, m, n, C )
#define cudaMD_getElement( y, MA, ht, len, m, n ) cudaMDgetElement( y, (dPMatrix)(MA), ht, len, m, n )
#define cusdMD_getElement( y, MA, ht, len, m, n ) cusdMDgetElement( y, (dPMatrix)(MA), ht, len, m, n )
#define cudaMD_Pelement( MA, ht, len, m, n )      cudaMDPelement( (dPMatrix)(MA), ht, len, m, n )
#define cudaMD_element( MA, ht, len, m, n )       cudaMDelement( (dPMatrix)(MA), ht, len, m, n )

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
        cudaVD_equ1( (dPMatrix)(MA), ht * len );
*/

#define cudaMD_equ0( MA, ht, len )                   cudaVD_equ0( (dPMatrix)(MA), (ht)*(len) )
#define cudaMD_equ1( MA, len )                       cudaMDequ1( (dPMatrix)(MA), len ) /* identity matrix */
#define cudaMD_equm1( MA, len )                      cudaMDequm1( (dPMatrix)(MA), len ) /* neg. identity matrix */
#define cudaMD_randomLC( MA, ht, len, seed, Min, Max, state ) cudaVD_randomLC( (dPMatrix)(MA), (ht)*(len), seed, Min, Max, state )
#define cudaMD_random( MA, ht, len, seed, Min, Max )          cudaVD_random( (dPMatrix)(MA), (ht)*(len), seed, Min, Max )
#define cusdMD_randomLC( MA, ht, len, seed, d_MinPtr, d_MaxPtr, state ) cusdVD_randomLC( (dPMatrix)(MA), (ht)*(len), seed, d_MinPtr, d_MaxPtr, state )
#define cusdMD_random( MA, ht, len, seed, d_MinPtr, d_MaxPtr )          cusdVD_random( (dPMatrix)(MA), (ht)*(len), seed, d_MinPtr, d_MaxPtr )
#define cudaMD_outerprod( MA, X, Y, ht, len )        cudaMDouterprod( (dPMatrix)(MA), X, Y, ht, len )
                       /* sizX=ht, sizY=len */
#define cudaMD_Row_equ0( MA, ht, len, iRow )    cudaMDRow_equ0( (dPMatrix)(MA), ht, len, iRow )
#define cudaMD_Col_equ0( MA, ht, len, iCol )    cudaMDCol_equ0( (dPMatrix)(MA), ht, len, iCol )
#define cudaMD_Dia_equ0( MA, len )              cudaMDDia_equ0( (dPMatrix)(MA), len )
#define cudaMD_Row_equC( MA, ht, len, iRow, C ) cudaMDRow_equC( (dPMatrix)(MA), ht, len, iRow, C )
#define cudaMD_Col_equC( MA, ht, len, iCol, C ) cudaMDCol_equC( (dPMatrix)(MA), ht, len, iCol, C )
#define cudaMD_Dia_equC( MA, len, C )           cudaMDDia_equC( (dPMatrix)(MA), len, C )
#define cusdMD_Row_equC( MA, ht, len, iRow, d_CPtr ) cusdMDRow_equC( (dPMatrix)(MA), ht, len, iRow, d_CPtr )
#define cusdMD_Col_equC( MA, ht, len, iCol, d_CPtr ) cusdMDCol_equC( (dPMatrix)(MA), ht, len, iCol, d_CPtr )
#define cusdMD_Dia_equC( MA, len, CPtr )           cusdMDDia_equC( (dPMatrix)(MA), len, CPtr )

#define cudaMD_Row_equV( MA, ht, len, iRow, X ) cudaMDRow_equV( (dPMatrix)(MA), ht, len, iRow, X )
#define cudaMD_Col_equV( MA, ht, len, iCol, X ) cudaMDCol_equV( (dPMatrix)(MA), ht, len, iCol, X )
#define cudaMD_Dia_equV( MA, len, X )           cudaMDDia_equV( (dPMatrix)(MA), len, X )

#define cudaMD_Trd_equM( MA, MTrd, len )        cudaMDTrd_equM( (dPMatrix)(MA), (dPMatrix)(MTrd), len )
#define cudaMD_Trd_extract( MTrd, MA, len )     cudaMDTrd_extract( (dPMatrix)(MTrd), (dPMatrix)(MA), len )

#define cudaMD_equM( MB, MA, ht, len )          cudaVD_equV( (dPMatrix)(MB), (dPMatrix)(MA), (ht)*(len) )
#define cudaMD_equMhost( MB, MA, ht, len )      cudaVD_equVhost( (dPMatrix)(MB), MA[0], (ht)*(len) )
#define MD_equMdevice( MB, MA, ht, len )        VD_equVdevice( MB[0], (dPMatrix)(MA), (ht)*(len) )
#define cudaMD_neg( MB, MA, ht, len )           cudaVD_neg( (dPMatrix)(MB), (dPMatrix)(MA), (ht)*(len) )

#define cudaMD_UequL( MA, len ) cudaMDUequL( (dPMatrix)(MA), len )
#define cudaMD_LequU( MA, len ) cudaMDLequU( (dPMatrix)(MA), len )
     /* copy lower-diagonal elements into upper-diagonal
       (or vice versa) by index-reflection, so as to get a symmetric matrix    */

            /* data-type conversions:  */
#define cudaM_DtoF( MF, MD, ht, len ) cudaV_DtoF( (fPMatrix)(MF), (dPMatrix)(MD), (ht)*(len) )
#define cudaM_FtoD( MD, MF, ht, len ) cudaV_FtoD( (dPMatrix)(MD), (fPMatrix)(MF), (ht)*(len) )

            /* suitable windows for MD_spectrum: */
#define cudaMD_Hann( MA, ht, len )     cudaMDHann( (dPMatrix)(MA), ht, len )
#define cudaMD_Hanning( MA, ht, len )  cudaMDHann( (dPMatrix)(MA), ht, len )  /* erroneous name for Hann */
#define cudaMD_Parzen( MA, ht, len )   cudaMDParzen( (dPMatrix)(MA), ht, len )
#define cudaMD_Welch( MA, ht, len )    cudaMDWelch( (dPMatrix)(MA), ht, len )

/********  Extracting a submatrix and copying a submatrix back  *********/

#define cudaMD_submatrix( MSub, subHt, subLen, MSrce, srceHt, srceLen, \
                      firstRowInCol, sampInCol, firstColInRow, sampInRow ) \
               cudaMDsubmatrix(  (dPMatrix)(MSub), subHt, subLen, \
                             (dPMatrix)(MSrce), srceHt, srceLen, \
                             firstRowInCol, sampInCol, firstColInRow, sampInRow )

#define cudaMD_submatrix_equM( MDest, destHt, destLen, \
                           firstRowInCol, sampInCol, firstColInRow, sampInRow, \
                           MSrce, srceHt, srceLen ) \
               cudaMDsubmatrix_equM(  (dPMatrix)(MDest), destHt, destLen, \
                             firstRowInCol, sampInCol, firstColInRow, sampInRow, \
                             (dPMatrix)(MSrce), srceHt, srceLen )

#define cudaMD_equMblock( MSub, subHt, subLen, MSrce, srceHt, srceLen, \
                      firstRowInCol, firstColInRow ) \
               cudaMDequMblock(  (dPMatrix)(MSub), subHt, subLen, \
                             (dPMatrix)(MSrce), srceHt, srceLen, \
                             firstRowInCol, firstColInRow )

#define cudaMD_block_equM( MDest, destHt, destLen, \
                       firstRowInCol, firstColInRow, \
                       MSrce, srceHt, srceLen ) \
               cudaMDblock_equM( (dPMatrix)(MDest), destHt, destLen, \
                             firstRowInCol, firstColInRow, \
                             (dPMatrix)(MSrce), srceHt, srceLen )

#define cudaMD_equMblockT( MSub, subHt, subLen, MSrce, srceHt, srceLen, \
                      firstRowInCol, firstColInRow ) \
               cudaMDequMblockT(  (dPMatrix)(MSub), subHt, subLen, \
                             (dPMatrix)(MSrce), srceHt, srceLen, \
                             firstRowInCol, firstColInRow )

#define cudaMD_block_equMT( MDest, destHt, destLen, \
                       firstRowInCol, firstColInRow, \
                       MSrce, srceHt, srceLen ) \
               cudaMDblock_equMT( (dPMatrix)(MDest), destHt, destLen, \
                             firstRowInCol, firstColInRow, \
                             (dPMatrix)(MSrce), srceHt, srceLen )

/*****   Extracting a single row or a single column or the diagonal  ******
 *       and storing it into a vector                                     */

#define cudaMD_Row_extract( Y, MA, ht, len, iRow ) cudaMDRow_extract( Y, (dPMatrix)(MA), ht, len, iRow )
#define cudaMD_Col_extract( Y, MA, ht, len, iCol ) cudaMDCol_extract( Y, (dPMatrix)(MA), ht, len, iCol )
#define cudaMD_Dia_extract( Y, MA, len )           cudaMDDia_extract( Y, (dPMatrix)(MA), len )

/**************  Deleting or inserting a row or a column   ***************/

#define cudaMD_Row_delete( MB, MA, htA, lenA, iRow )    cudaMDRow_delete( (dPMatrix)(MB), (dPMatrix)(MA), htA, lenA, iRow )
#define cudaMD_Col_delete( MB, MA, htA, lenA, iCol )    cudaMDCol_delete( (dPMatrix)(MB), (dPMatrix)(MA), htA, lenA, iCol )
#define cudaMD_Row_insert( MB, MA, htB, lenB, iRow, X ) cudaMDRow_insert( (dPMatrix)(MB), (dPMatrix)(MA), htB, lenB, iRow, X )
#define cudaMD_Col_insert( MB, MA, htB, lenB, iCol, X ) cudaMDCol_insert( (dPMatrix)(MB), (dPMatrix)(MA), htB, lenB, iCol, X )


/*****************    Basic arithmetic operations *********************
                      performed on one single row,
                      or one single column of any matrix,
                      or on the diagonal of a square matrix

    Note: In contrast to the analogous VectorLib functions, the operations
    are performed in-place, i.e. the input matrix itself is changed  */

#define cudaMD_Row_neg( MA, ht, len, iRow ) cudaMDRow_neg( (dPMatrix)(MA), ht, len, iRow )
#define cudaMD_Col_neg( MA, ht, len, iCol ) cudaMDCol_neg( (dPMatrix)(MA), ht, len, iCol )

#define cudaMD_Row_addC( MA, ht, len, iRow, C )      cudaMDRow_addC( (dPMatrix)(MA), ht, len, iRow, C )
#define cudaMD_Col_addC( MA, ht, len, iCol, C )      cudaMDCol_addC( (dPMatrix)(MA), ht, len, iCol, C )
#define cudaMD_Dia_addC( MA, len, C )                cudaMDDia_addC( (dPMatrix)(MA), len, C )
#define cusdMD_Row_addC( MA, ht, len, iRow, d_CPtr ) cusdMDRow_addC( (dPMatrix)(MA), ht, len, iRow, d_CPtr )
#define cusdMD_Col_addC( MA, ht, len, iCol, d_CPtr ) cusdMDCol_addC( (dPMatrix)(MA), ht, len, iCol, d_CPtr )
#define cusdMD_Dia_addC( MA, len, d_CPtr )           cusdMDDia_addC( (dPMatrix)(MA), len, d_CPtr )

#define cudaMD_Row_addV( MA, ht, len, iRow, X )      cudaMDRow_addV( (dPMatrix)(MA), ht, len, iRow, X )
#define cudaMD_Col_addV( MA, ht, len, iCol, X )      cudaMDCol_addV( (dPMatrix)(MA), ht, len, iCol, X )
#define cudaMD_Dia_addV( MA, len, X )                cudaMDDia_addV( (dPMatrix)(MA), len, X )

#define cudaMD_Row_subC( MA, ht, len, iRow, C )      cudaMDRow_subC( (dPMatrix)(MA), ht, len, iRow, C )
#define cudaMD_Col_subC( MA, ht, len, iCol, C )      cudaMDCol_subC( (dPMatrix)(MA), ht, len, iCol, C )
#define cudaMD_Dia_subC( MA, len, C )                cudaMDDia_subC( (dPMatrix)(MA), len, C )
#define cusdMD_Row_subC( MA, ht, len, iRow, d_CPtr ) cusdMDRow_subC( (dPMatrix)(MA), ht, len, iRow, d_CPtr )
#define cusdMD_Col_subC( MA, ht, len, iCol, d_CPtr ) cusdMDCol_subC( (dPMatrix)(MA), ht, len, iCol, d_CPtr )
#define cusdMD_Dia_subC( MA, len, d_CPtr )           cusdMDDia_subC( (dPMatrix)(MA), len, d_CPtr )

#define cudaMD_Row_subV( MA, ht, len, iRow, X )      cudaMDRow_subV( (dPMatrix)(MA), ht, len, iRow, X )
#define cudaMD_Col_subV( MA, ht, len, iCol, X )      cudaMDCol_subV( (dPMatrix)(MA), ht, len, iCol, X )
#define cudaMD_Dia_subV( MA, len, X )                cudaMDDia_subV( (dPMatrix)(MA), len, X )

#define cudaMD_Row_subrC( MA, ht, len, iRow, C )      cudaMDRow_subrC( (dPMatrix)(MA), ht, len, iRow, C )
#define cudaMD_Col_subrC( MA, ht, len, iCol, C )      cudaMDCol_subrC( (dPMatrix)(MA), ht, len, iCol, C )
#define cudaMD_Dia_subrC( MA, len, C )                cudaMDDia_subrC( (dPMatrix)(MA), len, C )
#define cusdMD_Row_subrC( MA, ht, len, iRow, d_CPtr ) cusdMDRow_subrC( (dPMatrix)(MA), ht, len, iRow, d_CPtr )
#define cusdMD_Col_subrC( MA, ht, len, iCol, d_CPtr ) cusdMDCol_subrC( (dPMatrix)(MA), ht, len, iCol, d_CPtr )
#define cusdMD_Dia_subrC( MA, len, d_CPtr )           cusdMDDia_subrC( (dPMatrix)(MA), len, d_CPtr )

#define cudaMD_Row_subrV( MA, ht, len, iRow, X )      cudaMDRow_subrV( (dPMatrix)(MA), ht, len, iRow, X )
#define cudaMD_Col_subrV( MA, ht, len, iCol, X )      cudaMDCol_subrV( (dPMatrix)(MA), ht, len, iCol, X )
#define cudaMD_Dia_subrV( MA, len, X )                cudaMDDia_subrV( (dPMatrix)(MA), len, X )

#define cudaMD_Row_mulC( MA, ht, len, iRow, C )      cudaMDRow_mulC( (dPMatrix)(MA), ht, len, iRow, C )
#define cudaMD_Col_mulC( MA, ht, len, iCol, C )      cudaMDCol_mulC( (dPMatrix)(MA), ht, len, iCol, C )
#define cudaMD_Dia_mulC( MA, len, C )                cudaMDDia_mulC( (dPMatrix)(MA), len, C )
#define cusdMD_Row_mulC( MA, ht, len, iRow, d_CPtr ) cusdMDRow_mulC( (dPMatrix)(MA), ht, len, iRow, d_CPtr )
#define cusdMD_Col_mulC( MA, ht, len, iCol, d_CPtr ) cusdMDCol_mulC( (dPMatrix)(MA), ht, len, iCol, d_CPtr )
#define cusdMD_Dia_mulC( MA, len, d_CPtr )           cusdMDDia_mulC( (dPMatrix)(MA), len, d_CPtr )

#define cudaMD_Row_mulV( MA, ht, len, iRow, X )      cudaMDRow_mulV( (dPMatrix)(MA), ht, len, iRow, X )
#define cudaMD_Col_mulV( MA, ht, len, iCol, X )      cudaMDCol_mulV( (dPMatrix)(MA), ht, len, iCol, X )
#define cudaMD_Dia_mulV( MA, len, X )                cudaMDDia_mulV( (dPMatrix)(MA), len, X )

#define cudaMD_Row_divC( MA, ht, len, iRow, C )      cudaMDRow_divC( (dPMatrix)(MA), ht, len, iRow, C )
#define cudaMD_Col_divC( MA, ht, len, iCol, C )      cudaMDCol_divC( (dPMatrix)(MA), ht, len, iCol, C )
#define cudaMD_Dia_divC( MA, len, C )                cudaMDDia_divC( (dPMatrix)(MA), len, C )
#define cusdMD_Row_divC( MA, ht, len, iRow, d_CPtr ) cusdMDRow_divC( (dPMatrix)(MA), ht, len, iRow, d_CPtr )
#define cusdMD_Col_divC( MA, ht, len, iCol, d_CPtr ) cusdMDCol_divC( (dPMatrix)(MA), ht, len, iCol, d_CPtr )
#define cusdMD_Dia_divC( MA, len, d_CPtr )           cusdMDDia_divC( (dPMatrix)(MA), len, d_CPtr )

#define cudaMD_Row_divV( MA, ht, len, iRow, X )      cudaMDRow_divV( (dPMatrix)(MA), ht, len, iRow, X )
#define cudaMD_Col_divV( MA, ht, len, iCol, X )      cudaMDCol_divV( (dPMatrix)(MA), ht, len, iCol, X )
#define cudaMD_Dia_divV( MA, len, X )                cudaMDDia_divV( (dPMatrix)(MA), len, X )

#define cudaMD_Row_divrC( MA, ht, len, iRow, C )      cudaMDRow_divrC( (dPMatrix)(MA), ht, len, iRow, C )
#define cudaMD_Col_divrC( MA, ht, len, iCol, C )      cudaMDCol_divrC( (dPMatrix)(MA), ht, len, iCol, C )
#define cudaMD_Dia_divrC( MA, len, C )                cudaMDDia_divrC( (dPMatrix)(MA), len, C )
#define cusdMD_Row_divrC( MA, ht, len, iRow, d_CPtr ) cusdMDRow_divrC( (dPMatrix)(MA), ht, len, iRow, d_CPtr )
#define cusdMD_Col_divrC( MA, ht, len, iCol, d_CPtr ) cusdMDCol_divrC( (dPMatrix)(MA), ht, len, iCol, d_CPtr )
#define cusdMD_Dia_divrC( MA, len, d_CPtr )           cusdMDDia_divrC( (dPMatrix)(MA), len, d_CPtr )

#define cudaMD_Row_divrV( MA, ht, len, iRow, X )      cudaMDRow_divrV( (dPMatrix)(MA), ht, len, iRow, X )
#define cudaMD_Col_divrV( MA, ht, len, iCol, X )      cudaMDCol_divrV( (dPMatrix)(MA), ht, len, iCol, X )
#define cudaMD_Dia_divrV( MA, len, X )                cudaMDDia_divrV( (dPMatrix)(MA), len, X )


/******  One-dimensional vector operations **********************
         performed along all rows or all columns simultaneously,
         or along the diagonal of a square matrix                */

#define cudaMD_Rows_max( Y, MA, ht, len )        cudaMDRows_max( Y, (dPMatrix)(MA), ht, len )
#define cudaMD_Cols_max( Y, MA, ht, len )        cudaMDCols_max( Y, (dPMatrix)(MA), ht, len )
#define cudaMD_Dia_max(  h_RetValPtr, MA, len )  cudaMDDia_max(  h_RetValPtr, (dPMatrix)(MA), len )
#define cusdMD_Dia_max(  d_RetValPtr, MA, len )  cusdMDDia_max(  d_RetValPtr, (dPMatrix)(MA), len )
#define cudaMD_Rows_min( Y, MA, ht, len )        cudaMDRows_min( Y, (dPMatrix)(MA), ht, len )
#define cudaMD_Cols_min( Y, MA, ht, len )        cudaMDCols_min( Y, (dPMatrix)(MA), ht, len )
#define cudaMD_Dia_min(  h_RetValPtr, MA, len )  cudaMDDia_min(  h_RetValPtr, (dPMatrix)(MA), len )
#define cusdMD_Dia_min(  d_RetValPtr, MA, len )  cusdMDDia_min(  d_RetValPtr, (dPMatrix)(MA), len )

#define cudaMD_Rows_absmax( Y, MA, ht, len )       cudaMDRows_absmax( Y, (dPMatrix)(MA), ht, len )
#define cudaMD_Cols_absmax( Y, MA, ht, len )       cudaMDCols_absmax( Y, (dPMatrix)(MA), ht, len )
#define cudaMD_Dia_absmax(  h_RetValPtr, MA, len ) cudaMDDia_absmax(  h_RetValPtr, (dPMatrix)(MA), len )
#define cusdMD_Dia_absmax(  d_RetValPtr, MA, len ) cusdMDDia_absmax(  d_RetValPtr, (dPMatrix)(MA), len )
#define cudaMD_Rows_absmin( Y, MA, ht, len )       cudaMDRows_absmin( Y, (dPMatrix)(MA), ht, len )
#define cudaMD_Cols_absmin( Y, MA, ht, len )       cudaMDCols_absmin( Y, (dPMatrix)(MA), ht, len )
#define cudaMD_Dia_absmin(  h_RetValPtr, MA, len ) cudaMDDia_absmin(  h_RetValPtr, (dPMatrix)(MA), len )
#define cusdMD_Dia_absmin(  d_RetValPtr, MA, len ) cusdMDDia_absmin(  d_RetValPtr, (dPMatrix)(MA), len )

#define cudaMD_Rows_sum( Y, MA, ht, len )          cudaMDRows_sum( Y, (dPMatrix)(MA), ht, len )
#define cudaMD_Cols_sum( Y, MA, ht, len )          cudaMDCols_sum( Y, (dPMatrix)(MA), ht, len )
#define cudaMD_Dia_sum(  h_RetValPtr, MA, len )    cudaMDDia_sum(  h_RetValPtr, (dPMatrix)(MA), len )
#define cusdMD_Dia_sum(  d_RetValPtr, MA, len )    cusdMDDia_sum(  d_RetValPtr, (dPMatrix)(MA), len )
#define cudaMD_Rows_ssq( Y, MA, ht, len )          cudaMDRows_ssq( Y, (dPMatrix)(MA), ht, len )
#define cudaMD_Cols_ssq( Y, MA, ht, len )          cudaMDCols_ssq( Y, (dPMatrix)(MA), ht, len )
#define cudaMD_Dia_ssq(  h_RetValPtr, MA, len )    cudaMDDia_ssq(  h_RetValPtr, (dPMatrix)(MA), len )
#define cusdMD_Dia_ssq(  d_RetValPtr, MA, len )    cusdMDDia_ssq(  d_RetValPtr, (dPMatrix)(MA), len )
#define cudaMD_Rows_prod( Y, MA, ht, len )         cudaMDRows_prod( Y, (dPMatrix)(MA), ht, len )
#define cudaMD_Cols_prod( Y, MA, ht, len )         cudaMDCols_prod( Y, (dPMatrix)(MA), ht, len )
#define cudaMD_Dia_prod(  h_RetValPtr, MA, len )   cudaMDDia_prod(  h_RetValPtr, (dPMatrix)(MA), len )
#define cusdMD_Dia_prod(  d_RetValPtr, MA, len )   cusdMDDia_prod(  d_RetValPtr, (dPMatrix)(MA), len )

#define cudaMD_Rows_runsum( MA, ht, len )     cudaMDRows_runsum( (dPMatrix)(MA), ht, len )
#define cudaMD_Cols_runsum( MA, ht, len )     cudaMDCols_runsum( (dPMatrix)(MA), ht, len )
#define cudaMD_Rows_runprod( MA, ht, len )    cudaMDRows_runprod( (dPMatrix)(MA), ht, len )
#define cudaMD_Cols_runprod( MA, ht, len )    cudaMDCols_runprod( (dPMatrix)(MA), ht, len )

#define cudaMD_Rows_rotate( MA, ht, len, pos)           cudaMDRows_rotate( (dPMatrix)(MA), ht, len, pos )
#define cudaMD_Cols_rotate( MA, ht, len, pos)           cudaMDCols_rotate( (dPMatrix)(MA), ht, len, pos )
#define cudaMD_Rows_rotate_buf( MA, ht, len, pos, MBuf) cudaMDRows_rotate_buf( (dPMatrix)(MA), ht, len, pos, (dPMatrix)(MBuf) )
#define cudaMD_Cols_rotate_buf( MA, ht, len, pos, MBuf) cudaMDCols_rotate_buf( (dPMatrix)(MA), ht, len, pos, (dPMatrix)(MBuf) )
#define cudaMD_Rows_reflect( MA, ht, len )              cudaMDRows_reflect( (dPMatrix)(MA), ht, len )
#define cudaMD_Cols_reflect( MA, ht, len )              cudaMDCols_reflect( (dPMatrix)(MA), ht, len )
#define cudaMD_Rows_rev( MA, ht, len)                   cudaMDRows_rev( (dPMatrix)(MA), ht, len )
#define cudaMD_Cols_rev( MA, ht, len)                   cudaMDCols_rev( (dPMatrix)(MA), ht, len )
#define cudaMD_Rows_distribution( MAbund, Limits, nBins, MX, ht, len, mode ) cudaMDRows_distribution( (uiPMatrix)MAbund, Limits, nBins, (dPMatrix)MX, ht, len, mode )
#define cudaMD_Cols_distribution( MAbund, Limits, nBins, MX, ht, len, mode ) cudaMDCols_distribution( (uiPMatrix)MAbund, Limits, nBins, (dPMatrix)MX, ht, len, mode )

/********  Operations involving two rows or two colums of one matrix  *****/

#define cudaMD_Rows_exchange( MA, ht, len, row1, row2 ) \
                             cudaMDRows_exchange( (dPMatrix)(MA), ht, len, row1, row2 )
#define cudaMD_Cols_exchange( MA, ht, len, col1, col2 ) \
                             cudaMDCols_exchange( (dPMatrix)(MA), ht, len, col1, col2 )

#define cudaMD_Rows_add( MA, ht, len, destRow, srceRow ) \
                             cudaMDRows_add( (dPMatrix)(MA), ht, len, destRow, srceRow )
#define cudaMD_Cols_add( MA, ht, len, destCol, srceCol ) \
                             cudaMDCols_add( (dPMatrix)(MA), ht, len, destCol, srceCol )
                         /* dest[i] += source[i]  */

#define cudaMD_Rows_sub( MA, ht, len, destRow, srceRow ) \
                             cudaMDRows_sub( (dPMatrix)(MA), ht, len, destRow, srceRow )
#define cudaMD_Cols_sub( MA, ht, len, destCol, srceCol ) \
                             cudaMDCols_sub( (dPMatrix)(MA), ht, len, destCol, srceCol )
                         /* dest[i] -= source[i]  */

#define cudaMD_Rows_Cadd( MA, ht, len, destRow, srceRow, C ) \
                          cudaMDRows_Cadd( (dPMatrix)(MA), ht, len, destRow, srceRow, C )
#define cudaMD_Cols_Cadd( MA, ht, len, destCol, srceCol, C ) \
                          cudaMDCols_Cadd( (dPMatrix)(MA), ht, len, destCol, srceCol, C )
#define cusdMD_Rows_Cadd( MA, ht, len, destRow, srceRow, d_CPtr ) \
                          cusdMDRows_Cadd( (dPMatrix)(MA), ht, len, destRow, srceRow, d_CPtr )
#define cusdMD_Cols_Cadd( MA, ht, len, destCol, srceCol, d_CPtr ) \
                          cusdMDCols_Cadd( (dPMatrix)(MA), ht, len, destCol, srceCol, d_CPtr )
                         /* dest[i] += C * source[i]  */

#define cudaMD_Rows_lincomb( MA, ht, len, destRow, destC, srceRow, srceC ) \
            cudaMDRows_lincomb( (dPMatrix)(MA), ht, len, destRow, destC, srceRow, srceC )
#define cudaMD_Cols_lincomb( MA, ht, len, destCol, destC, srceCol, srceC ) \
            cudaMDCols_lincomb( (dPMatrix)(MA), ht, len, destCol, destC, srceCol, srceC )
#define cusdMD_Rows_lincomb( MA, ht, len, destRow, d_destCPtr, srceRow, d_srceCPtr ) \
            cusdMDRows_lincomb( (dPMatrix)(MA), ht, len, destRow, d_destCPtr, srceRow, d_srceCPtr )
#define cusdMD_Cols_lincomb( MA, ht, len, destCol, d_destCPtr, srceCol, d_srceCPtr ) \
            cusdMDCols_lincomb( (dPMatrix)(MA), ht, len, destCol, d_destCPtr, srceCol, d_srceCPtr )
  /*  linear combination: dest[i] = destC * dest[i] + sourceC * source[i] */


/*********************  Center of gravity *****************************/
#define cudaMD_centerOfGravityInd( h_RetValPtr, MA, ht, len ) \
            cudaMDcenterOfGravityInd( h_RetValPtr, (dPMatrix)(MA), ht, len )
#define cudaMD_centerOfGravityV( h_RetValPtr, X, Y, MA, ht, len ) \
            cudaMDcenterOfGravityV( h_RetValPtr, X, Y, (dPMatrix)(MA), ht, len )
#define cusdMD_centerOfGravityInd( d_RetValPtr, MA, ht, len ) \
            cusdMDcenterOfGravityInd( d_RetValPtr, (dPMatrix)(MA), ht, len )
#define cusdMD_centerOfGravityV( d_RetValPtr, X, Y, MA, ht, len ) \
            cusdMDcenterOfGravityV( d_RetValPtr, X, Y, (dPMatrix)(MA), ht, len )

/*************** Transposing and rotating a matrix **********************/

#define cudaMD_transpose( MTr, MA, htTr, lenTr )    cudaMDtranspose( (dPMatrix)(MTr), (dPMatrix)(MA), htTr, lenTr )
       /*  dimensions htTr, lenTr are those of the transposed matrix, not of the original!   */
#define cudaMD_rotate90( MRot, MA, htRot, lenRot )  cudaMDrotate90( (dPMatrix)(MRot), (dPMatrix)(MA), htRot, lenRot )
#define cudaMD_rotate180( MRot, MA, htRot, lenRot ) cudaVD_rev( (dPMatrix)(MRot), (dPMatrix)(MA), (htRot)*(lenRot) )
#define cudaMD_rotate270( MRot, MA, htRot, lenRot ) cudaMDrotate270( (dPMatrix)(MRot), (dPMatrix)(MA), htRot, lenRot )
#define cudaMD_transpose_buf( MTr, MA, htTr, lenTr, MBuf ) cudaMDtranspose_buf( (dPMatrix)(MTr), (dPMatrix)(MA), htTr, lenTr, (dPMatrix)(MBuf) )

/********************** Interpolation of Matrix elements **************/

#define cudaMD_polyinterpol( MZ, X, Y, ht, len, XTab, YTab, MZTab, httab, lentab, degX, degY ) \
             cudaMDpolyinterpol( (dPMatrix)(MZ), X, Y, ht, len, XTab, YTab, (dPMatrix)(MZTab), httab, lentab, degX, degY )
#define cudaMD_ratinterpol( MZ, X, Y, ht, len, XTab, YTab, MZTab, httab, lentab, degX, degY ) \
             cudaMDratinterpol( (dPMatrix)(MZ), X, Y, ht, len, XTab, YTab, (dPMatrix)(MZTab), httab, lentab, degX, degY )
#define cudaMD_natCubSplineInterpol( MZ, X, Y, ht, len, XTab, YTab, MZTab, httab, lentab ) \
             cudaMDnatCubSplineInterpol( (dPMatrix)(MZ), X, Y, ht, len, XTab, YTab, (dPMatrix)(MZTab), httab, lentab )


/************************ Matrix Arithmetics *************************/

#define cudaMD_addM( MC, MA, MB, htA, lenA )   cudaVD_addV( (dPMatrix)(MC), (dPMatrix)(MA), (dPMatrix)(MB), (htA)*(lenA) )
#define cudaMD_addMT( MC, MA, MB, htA, lenA )  cudaMDaddMT( (dPMatrix)(MC), (dPMatrix)(MA), (dPMatrix)(MB), htA, lenA )
#define cudaMD_subM( MC, MA, MB, htA, lenA )   cudaVD_subV( (dPMatrix)(MC), (dPMatrix)(MA), (dPMatrix)(MB), (htA)*(lenA) )
#define cudaMD_subMT( MC, MA, MB, htA, lenA )  cudaMDsubMT( (dPMatrix)(MC), (dPMatrix)(MA), (dPMatrix)(MB), htA, lenA )
#define cudaMD_subrMT( MC, MA, MB, htA, lenA ) cudaMDsubrMT( (dPMatrix)(MC), (dPMatrix)(MA), (dPMatrix)(MB), htA, lenA )
#define cudaMD_mulC( MB, MA, htA, lenA, C )    cudaVD_mulC( (dPMatrix)(MB), (dPMatrix)(MA), (htA)*(lenA), C )
#define cudaMD_divC( MB, MA, htA, lenA, C )    cudaVD_divC( (dPMatrix)(MB), (dPMatrix)(MA), (htA)*(lenA), C )
#define cusdMD_mulC( MB, MA, htA, lenA, CPtr ) cusdVD_mulC( (dPMatrix)(MB), (dPMatrix)(MA), (htA)*(lenA), CPtr )
#define cusdMD_divC( MB, MA, htA, lenA, CPtr ) cusdVD_divC( (dPMatrix)(MB), (dPMatrix)(MA), (htA)*(lenA), CPtr )

#define cudaMDs_addM( MC, MA, MB, htA, lenA, C )      cudaVDs_addV( (dPMatrix)(MC), (dPMatrix)(MA), (dPMatrix)(MB), (htA)*(lenA), C )
#define cudaMDs_addMT( MC, MA, MB, htA, lenA, C )     cudaMDsaddMT( (dPMatrix)(MC), (dPMatrix)(MA), (dPMatrix)(MB), htA, lenA, C )
#define cusdMDs_addM( MC, MA, MB, htA, lenA, CPtr )   cusdVDs_addV( (dPMatrix)(MC), (dPMatrix)(MA), (dPMatrix)(MB), (htA)*(lenA), CPtr )
#define cusdMDs_addMT( MC, MA, MB, htA, lenA, CPtr )  cusdMDsaddMT( (dPMatrix)(MC), (dPMatrix)(MA), (dPMatrix)(MB), htA, lenA, CPtr )
#define cudaMDs_subM( MC, MA, MB, htA, lenA, C )      cudaVDs_subV( (dPMatrix)(MC), (dPMatrix)(MA), (dPMatrix)(MB), (htA)*(lenA), C )
#define cudaMDs_subMT( MC, MA, MB, htA, lenA, C )     cudaMDssubMT( (dPMatrix)(MC), (dPMatrix)(MA), (dPMatrix)(MB), htA, lenA, C )
#define cusdMDs_subM( MC, MA, MB, htA, lenA, CPtr )   cusdVDs_subV( (dPMatrix)(MC), (dPMatrix)(MA), (dPMatrix)(MB), (htA)*(lenA), CPtr )
#define cusdMDs_subMT( MC, MA, MB, htA, lenA, CPtr )  cusdMDssubMT( (dPMatrix)(MC), (dPMatrix)(MA), (dPMatrix)(MB), htA, lenA, CPtr )
#define cudaMDs_subrMT( MC, MA, MB, htA, lenA, C )    cudaMDssubrMT( (dPMatrix)(MC), (dPMatrix)(MA), (dPMatrix)(MB), htA, lenA, C )
#define cusdMDs_subrMT( MC, MA, MB, htA, lenA, CPtr ) cusdMDssubrMT( (dPMatrix)(MC), (dPMatrix)(MA), (dPMatrix)(MB), htA, lenA, CPtr )
#define cudaMD_lincomb( MC, MA, MB, htA, lenA, CA, CB )       cudaVD_lincomb( (dPMatrix)(MC), (dPMatrix)(MA), (dPMatrix)(MB), (htA)*(lenA), CA,    CB )
#define cusdMD_lincomb( MC, MA, MB, htA, lenA, CAPtr, CBPtr ) cusdVD_lincomb( (dPMatrix)(MC), (dPMatrix)(MA), (dPMatrix)(MB), (htA)*(lenA), CAPtr, CBPtr )

#define cudaMD_mulV( Y, MA, X, htA, lenA )    cudaMDmulV( Y, (dPMatrix)(MA), X, htA, lenA )
             /*  Y = MA * X.  sizX=lenA, sizY=htA;   both X and Y are column-vectors    */
#define cudaMD_TmulV( Y, MA, X, htA, lenA )   cudaMDTmulV( Y, (dPMatrix)(MA), X, htA, lenA )
            /*  Y = MAT * X.  sizX=htA, sizY=lenA;   both X and Y are column-vectors    */
#define cudaVD_mulM( Y, X, MA, htA, lenA )    cudaVDmulM( Y, X, (dPMatrix)(MA), htA, lenA )
            /*  Y = X * MA.  sizX=htA, sizY=lenA;    both X and Y are row-vectors.
                             Mind the prefix: cudaVD_ (not cudaMD_)    */
#define cudaVD_mulMT( Y, X, MA, htA, lenA )    cudaVDmulMT( Y, X, (dPMatrix)(MA), htA, lenA )
            /*  Y = X * MAT.  sizX=lenA, sizY=htA;   both X and Y are row-vectors.   */
#define cudaMD_mulM( MC, MA, MB, htA, lenA, lenB )  cudaMDmulM( (dPMatrix)(MC), (dPMatrix)(MA), (dPMatrix)(MB), htA, lenA, lenB )
                         /*  MC = MA * MB.  htB=lenA, htC=htA, lenC=lenB */
#define cudaMD_mulMT( MC, MA, MB, htA, lenA, htB )  cudaMDmulMT( (dPMatrix)(MC), (dPMatrix)(MA), (dPMatrix)(MB), htA, lenA, htB )
                         /*  MC = MA * MBT.  lenB=lenA, htC=htA, lenC=htB */
#define cudaMD_TmulM( MC, MA, MB, htA, lenA, lenB ) cudaMDTmulM( (dPMatrix)(MC), (dPMatrix)(MA), (dPMatrix)(MB), htA, lenA, lenB )
                         /*  MC = MAT * MB.  htB=htA, htC=lenA, lenC=lenB */
#define cudaMD_TmulMT( MC, MA, MB, htA, lenA, htB ) cudaMDTmulMT( (dPMatrix)(MC), (dPMatrix)(MA), (dPMatrix)(MB), htA, lenA, htB )
                         /*  MC = MAT * MBT.  lenB=htA, htC=lenA, lenC=htB */
#define cudaMDdia_mulM(  MC, MADia, MB, htB, lenB )  cudaMDdiamulM(  (dPMatrix)(MC), MADia, (dPMatrix)(MB), htB, lenB )
#define cudaMDdia_mulMT( MC, MADia, MB, htB, lenB )  cudaMDdiamulMT( (dPMatrix)(MC), MADia, (dPMatrix)(MB), htB, lenB )
#define cudaMD_mulMdia(  MC, MA, MBDia, htA, lenA )  cudaMDmulMdia(  (dPMatrix)(MC), (dPMatrix)(MA), MBDia, htA, lenA )
#define cudaMD_TmulMdia( MC, MA, MBDia, htA, lenA )  cudaMDTmulMdia( (dPMatrix)(MC), (dPMatrix)(MA), MBDia, htA, lenA )

/***************** Two-Dimensional Fourier-Transform Methods ************/

#define cudaMD_FFT( MY, MX, ht, len, dir )     cudaMDFFT( (dPMatrix)(MY), (dPMatrix)(MX), ht, len, dir )
#define cudaMD_Rows_FFT( MY, MX, ht, len, dir) cudaMDRows_FFT( (dPMatrix)(MY), (dPMatrix)(MX), ht, len, dir )
#define cudaMD_Cols_FFT( MY, MX, ht, len, dir) cudaMDCols_FFT( (dPMatrix)(MY), (dPMatrix)(MX), ht, len, dir )
#define cudaMD_FFTtoC( MY, MX, ht, len )       cudaMDFFTtoC( (cdPMatrix)(MY), (dPMatrix)(MX), ht, len )
#define cudaMD_Rows_FFTtoC( MY, MX, ht, len )  cudaMDRows_FFTtoC( (cdPMatrix)(MY), (dPMatrix)(MX), ht, len )
#define cudaMD_Cols_FFTtoC( MY, MX, ht, len )  cudaMDCols_FFTtoC( (cdPMatrix)(MY), (dPMatrix)(MX), ht, len )
#define cudaMD_convolve( MY, MFlt, MX, MRsp, ht, len ) \
                  cudaMDconvolve( (dPMatrix)(MY), (dPMatrix)(MFlt), (dPMatrix)(MX), (dPMatrix)(MRsp), ht, len )
#define cudaMD_deconvolve( MY, MFlt, MX, MRsp, ht, len ) \
                  cudaMDdeconvolve( (dPMatrix)(MY), (dPMatrix)(MFlt), (dPMatrix)(MX), (dPMatrix)(MRsp), ht, len )
#define cudaMD_filter( MY, MX, MFlt, ht, len ) cudaMDfilter( (dPMatrix)(MY), (dPMatrix)(MX), (dPMatrix)(MFlt), ht, len )
#define cudaMD_autocorr( MACorr, MX, ht, len ) cudaMDautocorr( (dPMatrix)(MACorr), (dPMatrix)(MX), ht, len )
#define cudaMD_xcorr( MXCorr, MX, MY, ht, len) cudaMDxcorr( (dPMatrix)(MXCorr), (dPMatrix)(MX), (dPMatrix)(MY), ht, len )
#define cudaMD_spectrum( MSpec, htSpec, lenSpec, MX, htX, lenX, MWin ) \
              cudaMDspectrum( (dPMatrix)(MSpec), htSpec, lenSpec, (dPMatrix)(MX), htX, lenX, (dPMatrix)(MWin) )
              /*   htSpec, lenSpec must be 2**n,
                   MSpec must be a (htSpec+1)*(lenSpec+1) matrix!!
                   htX >= n*htSpec,  lenX >= n*lenSpec,
                   htWin = 2*htSpec, lenWin = 2*lenSpec */

/**************************  Input and Output  **************************
	The input/output functions involve memory transfers from device
	to host memory or vice versa. The generic cudaMD_input/output functions
	allocate their own host buffers, whereas the cudaMD_xxx_buf functions
	take a user-supplied buffer vector h_Wk (size must be >= ht*len )
	and are much more efficient.                                       */

#define cudaMD_fprint( stream, MA, ht, len, linewidth ) \
                    cudaMDfprint( stream, (dPMatrix)(MA), ht, len, linewidth )
#define cudaMD_print( MA, ht, len )  cudaMDfprint( stdout, (dPMatrix)(MA), ht, len, 80 )
#define cudaMD_cprint( MA, ht, len ) cudaMDcprint( (dPMatrix)(MA), ht, len )
#define cudaMD_fprint_buf( stream, MA, ht, len, linewidth, h_Wk ) \
                    cudaMDfprint_buf( stream, (dPMatrix)(MA), ht, len, linewidth, h_Wk )
#define cudaMD_print_buf( MA, ht, len )  cudaMDfprint_buf( stdout, (dPMatrix)(MA), ht, len, 80, h_Wk )
#define cudaMD_cprint_buf( MA, ht, len ) cudaMDcprint_buf( (dPMatrix)(MA), ht, len, h_Wk )
  /*  cudaMD_print, cudaMD_cprint usable only for console applications! */
#define cudaMD_write( str, MA, ht, len )   cudaMDwrite( str, (dPMatrix)(MA), ht, len )
#define cudaMD_read( MA, ht, len, str )    cudaMDread( (dPMatrix)(MA), ht, len, str )
#define cudaMD_write_buf( str, MA, ht, len, h_Wk )   cudaMDwrite_buf( str, (dPMatrix)(MA), ht, len, h_Wk )
#define cudaMD_read_buf( MA, ht, len, str, h_Wk )    cudaMDread_buf( (dPMatrix)(MA), ht, len, str, h_Wk )
                                   /* write and read in ascii format */
#define cudaMD_store( str, MA, ht, len )   cudaVD_store( str, (dPMatrix)(MA), (len)*(ht) )
#define cudaMD_recall( MA, ht, len, str)   cudaVD_recall( (dPMatrix)(MA), (len)*(ht), str)
#define cudaMD_store_buf( str, MA, ht, len, h_Wk )   cudaVD_store_buf( str, (dPMatrix)(MA), (len)*(ht), h_Wk )
#define cudaMD_recall_buf( MA, ht, len, str, h_Wk)   cudaVD_recall_buf( (dPMatrix)(MA), (len)*(ht), str, h_Wk )
                                  /* store and recall in binary format */

#endif /* plain-C or C++ for functions working on device memory   */


/*******************  Functions working on host memory: **********************
 *                                                                           *
 *	MDcu_func		(working on matrices in host memory, input type dMatrix, *
 *	scalar parameters on host and passed by value)                           *
 *****************************************************************************/ 

 /****************  Initialization  ****************************************/

#define MDcu_equ0( MA, ht, len )                   VDcu_equ0( (MA)[0], (ht)*(len) )
#define MDcu_equ1( MA, len )                       MDcuequ1( (MA)[0], len ) /* identity matrix */
#define MDcu_equm1( MA, len )                      MDcuequm1( (MA)[0], len ) /* neg. identity matrix */
#define MDcu_randomLC( MA, ht, len, seed, Min, Max, state ) VDcu_randomLC( (MA)[0], (ht)*(len), seed, Min, Max, state )
#define MDcu_random( MA, ht, len, seed, Min, Max )          VDcu_random( (MA)[0], (ht)*(len), seed, Min, Max )
#define MDcu_outerprod( MA, X, Y, ht, len )        MDcuouterprod( (MA)[0], X, Y, ht, len )
                       /* sizX=ht, sizY=len */
#define MDcu_Row_equ0( MA, ht, len, iRow )    MDcuRow_equ0( (MA)[0], ht, len, iRow )
#define MDcu_Col_equ0( MA, ht, len, iCol )    MDcuCol_equ0( (MA)[0], ht, len, iCol )
#define MDcu_Dia_equ0( MA, len )              MDcuDia_equ0( (MA)[0], len )
#define MDcu_Row_equC( MA, ht, len, iRow, C ) MDcuRow_equC( (MA)[0], ht, len, iRow, C )
#define MDcu_Col_equC( MA, ht, len, iCol, C ) MDcuCol_equC( (MA)[0], ht, len, iCol, C )
#define MDcu_Dia_equC( MA, len, C )           MDcuDia_equC( (MA)[0], len, C )

#define MDcu_Row_equV( MA, ht, len, iRow, X ) MDcuRow_equV( (MA)[0], ht, len, iRow, X )
#define MDcu_Col_equV( MA, ht, len, iCol, X ) MDcuCol_equV( (MA)[0], ht, len, iCol, X )
#define MDcu_Dia_equV( MA, len, X )           MDcuDia_equV( (MA)[0], len, X )

#define MDcu_Trd_equM( MA, MTrd, len )        MDcuTrd_equM( (MA)[0], (MTrd)[0], len )
#define MDcu_Trd_extract( MTrd, MA, len )     MDcuTrd_extract( (MTrd)[0], (MA)[0], len )

#define MDcu_equM( MB, MA, ht, len )          VDcu_equV( (MB)[0], (MA)[0], (ht)*(len) )
#define MDcu_equMhost( MB, MA, ht, len )      VDcu_equVhost( (MB)[0], MA[0], (ht)*(len) )
#define MDcu_neg( MB, MA, ht, len )           VDcu_neg( (MB)[0], (MA)[0], (ht)*(len) )

#define MDcu_UequL( MA, len ) MDcuUequL( (MA)[0], len )
#define MDcu_LequU( MA, len ) MDcuLequU( (MA)[0], len )
     /* copy lower-diagonal elements into upper-diagonal
       (or vice versa) by index-reflection, so as to get a symmetric matrix    */

            /* data-type conversions:  */
#define Mcu_DtoF( MF, MD, ht, len ) Vcu_DtoF( (MF)[0], (MD)[0], (ht)*(len) )
#define Mcu_FtoD( MD, MF, ht, len ) Vcu_FtoD( (MD)[0], (MF)[0], (ht)*(len) )

            /* suitable windows for MD_spectrum: */
#define MDcu_Hann( MA, ht, len )     MDcuHann( (MA)[0], ht, len )
#define MDcu_Hanning( MA, ht, len )  MDcuHann( (MA)[0], ht, len )  /* erroneous name for Hann */
#define MDcu_Parzen( MA, ht, len )   MDcuParzen( (MA)[0], ht, len )
#define MDcu_Welch( MA, ht, len )    MDcuWelch( (MA)[0], ht, len )

/********  Extracting a submatrix and copying a submatrix back  *********/

#define MDcu_submatrix( MSub, subHt, subLen, MSrce, srceHt, srceLen, \
                      firstRowInCol, sampInCol, firstColInRow, sampInRow ) \
               MDcusubmatrix(  (MSub)[0], subHt, subLen, \
                             (MSrce)[0], srceHt, srceLen, \
                             firstRowInCol, sampInCol, firstColInRow, sampInRow )

#define MDcu_submatrix_equM( MDest, destHt, destLen, \
                           firstRowInCol, sampInCol, firstColInRow, sampInRow, \
                           MSrce, srceHt, srceLen ) \
               MDcusubmatrix_equM(  (MDest)[0], destHt, destLen, \
                             firstRowInCol, sampInCol, firstColInRow, sampInRow, \
                             (MSrce)[0], srceHt, srceLen )

#define MDcu_equMblock( MSub, subHt, subLen, MSrce, srceHt, srceLen, \
                      firstRowInCol, firstColInRow ) \
               MDcuequMblock(  (MSub)[0], subHt, subLen, \
                             (MSrce)[0], srceHt, srceLen, \
                             firstRowInCol, firstColInRow )

#define MDcu_block_equM( MDest, destHt, destLen, \
                       firstRowInCol, firstColInRow, \
                       MSrce, srceHt, srceLen ) \
               MDcublock_equM( (MDest)[0], destHt, destLen, \
                             firstRowInCol, firstColInRow, \
                             (MSrce)[0], srceHt, srceLen )

#define MDcu_equMblockT( MSub, subHt, subLen, MSrce, srceHt, srceLen, \
                      firstRowInCol, firstColInRow ) \
               MDcuequMblockT(  (MSub)[0], subHt, subLen, \
                             (MSrce)[0], srceHt, srceLen, \
                             firstRowInCol, firstColInRow )

#define MDcu_block_equMT( MDest, destHt, destLen, \
                       firstRowInCol, firstColInRow, \
                       MSrce, srceHt, srceLen ) \
               MDcublock_equMT( (MDest)[0], destHt, destLen, \
                             firstRowInCol, firstColInRow, \
                             (MSrce)[0], srceHt, srceLen )

/*****   Extracting a single row or a single column or the diagonal  ******
 *       and storing it into a vector                                     */

#define MDcu_Row_extract( Y, MA, ht, len, iRow ) MDcuRow_extract( Y, (MA)[0], ht, len, iRow )
#define MDcu_Col_extract( Y, MA, ht, len, iCol ) MDcuCol_extract( Y, (MA)[0], ht, len, iCol )
#define MDcu_Dia_extract( Y, MA, len )           MDcuDia_extract( Y, (MA)[0], len )

/**************  Deleting or inserting a row or a column   ***************/

#define MDcu_Row_delete( MB, MA, htA, lenA, iRow )    MDcuRow_delete( (MB)[0], (MA)[0], htA, lenA, iRow )
#define MDcu_Col_delete( MB, MA, htA, lenA, iCol )    MDcuCol_delete( (MB)[0], (MA)[0], htA, lenA, iCol )
#define MDcu_Row_insert( MB, MA, htB, lenB, iRow, X ) MDcuRow_insert( (MB)[0], (MA)[0], htB, lenB, iRow, X )
#define MDcu_Col_insert( MB, MA, htB, lenB, iCol, X ) MDcuCol_insert( (MB)[0], (MA)[0], htB, lenB, iCol, X )


/*****************    Basic arithmetic operations *********************
                      performed on one single row,
                      or one single column of any matrix,
                      or on the diagonal of a square matrix

    Note: In contrast to the analogous VectorLib functions, the operations
    are performed in-place, i.e. the input matrix itself is changed  */

#define MDcu_Row_neg( MA, ht, len, iRow ) MDcuRow_neg( (MA)[0], ht, len, iRow )
#define MDcu_Col_neg( MA, ht, len, iCol ) MDcuCol_neg( (MA)[0], ht, len, iCol )

#define MDcu_Row_addC( MA, ht, len, iRow, C )      MDcuRow_addC( (MA)[0], ht, len, iRow, C )
#define MDcu_Col_addC( MA, ht, len, iCol, C )      MDcuCol_addC( (MA)[0], ht, len, iCol, C )
#define MDcu_Dia_addC( MA, len, C )                MDcuDia_addC( (MA)[0], len, C )

#define MDcu_Row_addV( MA, ht, len, iRow, X )      MDcuRow_addV( (MA)[0], ht, len, iRow, X )
#define MDcu_Col_addV( MA, ht, len, iCol, X )      MDcuCol_addV( (MA)[0], ht, len, iCol, X )
#define MDcu_Dia_addV( MA, len, X )                MDcuDia_addV( (MA)[0], len, X )

#define MDcu_Row_subC( MA, ht, len, iRow, C )      MDcuRow_subC( (MA)[0], ht, len, iRow, C )
#define MDcu_Col_subC( MA, ht, len, iCol, C )      MDcuCol_subC( (MA)[0], ht, len, iCol, C )
#define MDcu_Dia_subC( MA, len, C )                MDcuDia_subC( (MA)[0], len, C )

#define MDcu_Row_subV( MA, ht, len, iRow, X )      MDcuRow_subV( (MA)[0], ht, len, iRow, X )
#define MDcu_Col_subV( MA, ht, len, iCol, X )      MDcuCol_subV( (MA)[0], ht, len, iCol, X )
#define MDcu_Dia_subV( MA, len, X )                MDcuDia_subV( (MA)[0], len, X )

#define MDcu_Row_subrC( MA, ht, len, iRow, C )      MDcuRow_subrC( (MA)[0], ht, len, iRow, C )
#define MDcu_Col_subrC( MA, ht, len, iCol, C )      MDcuCol_subrC( (MA)[0], ht, len, iCol, C )
#define MDcu_Dia_subrC( MA, len, C )                MDcuDia_subrC( (MA)[0], len, C )

#define MDcu_Row_subrV( MA, ht, len, iRow, X )      MDcuRow_subrV( (MA)[0], ht, len, iRow, X )
#define MDcu_Col_subrV( MA, ht, len, iCol, X )      MDcuCol_subrV( (MA)[0], ht, len, iCol, X )
#define MDcu_Dia_subrV( MA, len, X )                MDcuDia_subrV( (MA)[0], len, X )

#define MDcu_Row_mulC( MA, ht, len, iRow, C )      MDcuRow_mulC( (MA)[0], ht, len, iRow, C )
#define MDcu_Col_mulC( MA, ht, len, iCol, C )      MDcuCol_mulC( (MA)[0], ht, len, iCol, C )
#define MDcu_Dia_mulC( MA, len, C )                MDcuDia_mulC( (MA)[0], len, C )

#define MDcu_Row_mulV( MA, ht, len, iRow, X )      MDcuRow_mulV( (MA)[0], ht, len, iRow, X )
#define MDcu_Col_mulV( MA, ht, len, iCol, X )      MDcuCol_mulV( (MA)[0], ht, len, iCol, X )
#define MDcu_Dia_mulV( MA, len, X )                MDcuDia_mulV( (MA)[0], len, X )

#define MDcu_Row_divC( MA, ht, len, iRow, C )      MDcuRow_divC( (MA)[0], ht, len, iRow, C )
#define MDcu_Col_divC( MA, ht, len, iCol, C )      MDcuCol_divC( (MA)[0], ht, len, iCol, C )
#define MDcu_Dia_divC( MA, len, C )                MDcuDia_divC( (MA)[0], len, C )

#define MDcu_Row_divV( MA, ht, len, iRow, X )      MDcuRow_divV( (MA)[0], ht, len, iRow, X )
#define MDcu_Col_divV( MA, ht, len, iCol, X )      MDcuCol_divV( (MA)[0], ht, len, iCol, X )
#define MDcu_Dia_divV( MA, len, X )                MDcuDia_divV( (MA)[0], len, X )

#define MDcu_Row_divrC( MA, ht, len, iRow, C )      MDcuRow_divrC( (MA)[0], ht, len, iRow, C )
#define MDcu_Col_divrC( MA, ht, len, iCol, C )      MDcuCol_divrC( (MA)[0], ht, len, iCol, C )
#define MDcu_Dia_divrC( MA, len, C )                MDcuDia_divrC( (MA)[0], len, C )

#define MDcu_Row_divrV( MA, ht, len, iRow, X )      MDcuRow_divrV( (MA)[0], ht, len, iRow, X )
#define MDcu_Col_divrV( MA, ht, len, iCol, X )      MDcuCol_divrV( (MA)[0], ht, len, iCol, X )
#define MDcu_Dia_divrV( MA, len, X )                MDcuDia_divrV( (MA)[0], len, X )


/******  One-dimensional vector operations **********************
         performed along all rows or all columns simultaneously,
         or along the diagonal of a square matrix                */

#define MDcu_Rows_max( Y, MA, ht, len )        MDcuRows_max( Y, (MA)[0], ht, len )
#define MDcu_Cols_max( Y, MA, ht, len )        MDcuCols_max( Y, (MA)[0], ht, len )
#define MDcu_Dia_max(  MA, len )               MDcuDia_max(  (MA)[0], len )
#define MDcu_Rows_min( Y, MA, ht, len )        MDcuRows_min( Y, (MA)[0], ht, len )
#define MDcu_Cols_min( Y, MA, ht, len )        MDcuCols_min( Y, (MA)[0], ht, len )
#define MDcu_Dia_min(  MA, len )               MDcuDia_min(  (MA)[0], len )

#define MDcu_Rows_absmax( Y, MA, ht, len )       MDcuRows_absmax( Y, (MA)[0], ht, len )
#define MDcu_Cols_absmax( Y, MA, ht, len )       MDcuCols_absmax( Y, (MA)[0], ht, len )
#define MDcu_Dia_absmax(  MA, len )              MDcuDia_absmax(  (MA)[0], len )
#define MDcu_Rows_absmin( Y, MA, ht, len )       MDcuRows_absmin( Y, (MA)[0], ht, len )
#define MDcu_Cols_absmin( Y, MA, ht, len )       MDcuCols_absmin( Y, (MA)[0], ht, len )
#define MDcu_Dia_absmin(  MA, len )              MDcuDia_absmin(  (MA)[0], len )

#define MDcu_Rows_sum( Y, MA, ht, len )          MDcuRows_sum( Y, (MA)[0], ht, len )
#define MDcu_Cols_sum( Y, MA, ht, len )          MDcuCols_sum( Y, (MA)[0], ht, len )
#define MDcu_Dia_sum(  MA, len )                 MDcuDia_sum(  (MA)[0], len )
#define MDcu_Rows_ssq( Y, MA, ht, len )          MDcuRows_ssq( Y, (MA)[0], ht, len )
#define MDcu_Cols_ssq( Y, MA, ht, len )          MDcuCols_ssq( Y, (MA)[0], ht, len )
#define MDcu_Dia_ssq(  MA, len )                 MDcuDia_ssq(  (MA)[0], len )
#define MDcu_Rows_prod( Y, MA, ht, len )         MDcuRows_prod( Y, (MA)[0], ht, len )
#define MDcu_Cols_prod( Y, MA, ht, len )         MDcuCols_prod( Y, (MA)[0], ht, len )
#define MDcu_Dia_prod(  MA, len )                MDcuDia_prod(  (MA)[0], len )

#define MDcu_Rows_runsum( MA, ht, len )     MDcuRows_runsum( (MA)[0], ht, len )
#define MDcu_Cols_runsum( MA, ht, len )     MDcuCols_runsum( (MA)[0], ht, len )
#define MDcu_Rows_runprod( MA, ht, len )    MDcuRows_runprod( (MA)[0], ht, len )
#define MDcu_Cols_runprod( MA, ht, len )    MDcuCols_runprod( (MA)[0], ht, len )

#define MDcu_Rows_rotate( MA, ht, len, pos)           MDcuRows_rotate( (MA)[0], ht, len, pos )
#define MDcu_Cols_rotate( MA, ht, len, pos)           MDcuCols_rotate( (MA)[0], ht, len, pos )
#define MDcu_Rows_rotate_buf( MA, ht, len, pos, MBuf) MDcuRows_rotate_buf( (MA)[0], ht, len, pos, (MBuf)[0] )
#define MDcu_Cols_rotate_buf( MA, ht, len, pos, MBuf) MDcuCols_rotate_buf( (MA)[0], ht, len, pos, (MBuf)[0] )
#define MDcu_Rows_reflect( MA, ht, len )              MDcuRows_reflect( (MA)[0], ht, len )
#define MDcu_Cols_reflect( MA, ht, len )              MDcuCols_reflect( (MA)[0], ht, len )
#define MDcu_Rows_rev( MA, ht, len)                   MDcuRows_rev( (MA)[0], ht, len )
#define MDcu_Cols_rev( MA, ht, len)                   MDcuCols_rev( (MA)[0], ht, len )
#define MDcu_Rows_distribution( MAbund, Limits, nBins, MX, ht, len, mode ) MDcuRows_distribution( MAbund[0], Limits, nBins, MX[0], ht, len, mode )
#define MDcu_Cols_distribution( MAbund, Limits, nBins, MX, ht, len, mode ) MDcuCols_distribution( MAbund[0], Limits, nBins, MX[0], ht, len, mode )

/********  Operations involving two rows or two colums of one matrix  *****/

#define MDcu_Rows_exchange( MA, ht, len, row1, row2 ) \
                             MDcuRows_exchange( (MA)[0], ht, len, row1, row2 )
#define MDcu_Cols_exchange( MA, ht, len, col1, col2 ) \
                             MDcuCols_exchange( (MA)[0], ht, len, col1, col2 )

#define MDcu_Rows_add( MA, ht, len, destRow, srceRow ) \
                             MDcuRows_add( (MA)[0], ht, len, destRow, srceRow )
#define MDcu_Cols_add( MA, ht, len, destCol, srceCol ) \
                             MDcuCols_add( (MA)[0], ht, len, destCol, srceCol )
                         /* dest[i] += source[i]  */

#define MDcu_Rows_sub( MA, ht, len, destRow, srceRow ) \
                             MDcuRows_sub( (MA)[0], ht, len, destRow, srceRow )
#define MDcu_Cols_sub( MA, ht, len, destCol, srceCol ) \
                             MDcuCols_sub( (MA)[0], ht, len, destCol, srceCol )
                         /* dest[i] -= source[i]  */

#define MDcu_Rows_Cadd( MA, ht, len, destRow, srceRow, C ) \
                          MDcuRows_Cadd( (MA)[0], ht, len, destRow, srceRow, C )
#define MDcu_Cols_Cadd( MA, ht, len, destCol, srceCol, C ) \
                          MDcuCols_Cadd( (MA)[0], ht, len, destCol, srceCol, C )
                         /* dest[i] += C * source[i]  */

#define MDcu_Rows_lincomb( MA, ht, len, destRow, destC, srceRow, srceC ) \
            MDcuRows_lincomb( (MA)[0], ht, len, destRow, destC, srceRow, srceC )
#define MDcu_Cols_lincomb( MA, ht, len, destCol, destC, srceCol, srceC ) \
            MDcuCols_lincomb( (MA)[0], ht, len, destCol, destC, srceCol, srceC )
  /*  linear combination: dest[i] = destC * dest[i] + sourceC * source[i] */


/*********************  Center of gravity *****************************/
#define MDcu_centerOfGravityInd( MA, ht, len ) \
            MDcucenterOfGravityInd( (MA)[0], ht, len )
#define MDcu_centerOfGravityV( X, Y, MA, ht, len ) \
            MDcucenterOfGravityV( X, Y, (MA)[0], ht, len )

/*************** Transposing and rotating a matrix **********************/

#define MDcu_transpose( MTr, MA, htTr, lenTr )    MDcutranspose( (MTr)[0], (MA)[0], htTr, lenTr )
       /*  dimensions htTr, lenTr are those of the transposed matrix, not of the original!   */
#define MDcu_rotate90( MRot, MA, htRot, lenRot )  MDcurotate90( (MRot)[0], (MA)[0], htRot, lenRot )
#define MDcu_rotate180( MRot, MA, htRot, lenRot ) VDcu_rev( (MRot)[0], (MA)[0], (htRot)*(lenRot) )
#define MDcu_rotate270( MRot, MA, htRot, lenRot ) MDcurotate270( (MRot)[0], (MA)[0], htRot, lenRot )

/********************** Interpolation of Matrix elements **************/

#define MDcu_polyinterpol( MZ, X, Y, ht, len, XTab, YTab, MZTab, httab, lentab, degX, degY ) \
             MDcupolyinterpol( (MZ)[0], X, Y, ht, len, XTab, YTab, (MZTab)[0], httab, lentab, degX, degY )
#define MDcu_ratinterpol( MZ, X, Y, ht, len, XTab, YTab, MZTab, httab, lentab, degX, degY ) \
             MDcuratinterpol( (MZ)[0], X, Y, ht, len, XTab, YTab, (MZTab)[0], httab, lentab, degX, degY )
#define MDcu_natCubSplineInterpol( MZ, X, Y, ht, len, XTab, YTab, MZTab, httab, lentab ) \
             MDcunatCubSplineInterpol( (MZ)[0], X, Y, ht, len, XTab, YTab, (MZTab)[0], httab, lentab )


/************************ Matrix Arithmetics *************************/

#define MDcu_addM( MC, MA, MB, htA, lenA )   VDcu_addV( (MC)[0], (MA)[0], (MB)[0], (htA)*(lenA) )
#define MDcu_addMT( MC, MA, MB, htA, lenA )  MDcuaddMT( (MC)[0], (MA)[0], (MB)[0], htA, lenA )
#define MDcu_subM( MC, MA, MB, htA, lenA )   VDcu_subV( (MC)[0], (MA)[0], (MB)[0], (htA)*(lenA) )
#define MDcu_subMT( MC, MA, MB, htA, lenA )  MDcusubMT( (MC)[0], (MA)[0], (MB)[0], htA, lenA )
#define MDcu_subrMT( MC, MA, MB, htA, lenA ) MDcusubrMT( (MC)[0], (MA)[0], (MB)[0], htA, lenA )
#define MDcu_mulC( MB, MA, htA, lenA, C )    VDcu_mulC( (MB)[0], (MA)[0], (htA)*(lenA), C )
#define MDcu_divC( MB, MA, htA, lenA, C )    VDcu_divC( (MB)[0], (MA)[0], (htA)*(lenA), C )

#define MDscu_addM( MC, MA, MB, htA, lenA, C )      VDscu_addV( (MC)[0], (MA)[0], (MB)[0], (htA)*(lenA), C )
#define MDscu_addMT( MC, MA, MB, htA, lenA, C )     MDscuaddMT( (MC)[0], (MA)[0], (MB)[0], htA, lenA, C )
#define MDscu_subM( MC, MA, MB, htA, lenA, C )      VDscu_subV( (MC)[0], (MA)[0], (MB)[0], (htA)*(lenA), C )
#define MDscu_subMT( MC, MA, MB, htA, lenA, C )     MDscusubMT( (MC)[0], (MA)[0], (MB)[0], htA, lenA, C )
#define MDscu_subrMT( MC, MA, MB, htA, lenA, C )    MDscusubrMT( (MC)[0], (MA)[0], (MB)[0], htA, lenA, C )
#define MDcu_lincomb( MC, MA, MB, htA, lenA, CA, CB )       VDcu_lincomb( (MC)[0], (MA)[0], (MB)[0], (htA)*(lenA), CA,    CB )

#define MDcu_mulV( Y, MA, X, htA, lenA )    MDcumulV( Y, (MA)[0], X, htA, lenA )
             /*  Y = MA * X.  sizX=lenA, sizY=htA;   both X and Y are column-vectors    */
#define MDcu_TmulV( Y, MA, X, htA, lenA )   MDcuTmulV( Y, (MA)[0], X, htA, lenA )
            /*  Y = MAT * X.  sizX=htA, sizY=lenA;   both X and Y are column-vectors    */
#define VDcu_mulM( Y, X, MA, htA, lenA )    VDcumulM( Y, X, (MA)[0], htA, lenA )
            /*  Y = X * MA.  sizX=htA, sizY=lenA;    both X and Y are row-vectors.
                             Mind the prefix: VDcu_ (not MDcu_)    */
#define VDcu_mulMT( Y, X, MA, htA, lenA )    VDcumulMT( Y, X, (MA)[0], htA, lenA )
            /*  Y = X * MAT.  sizX=lenA, sizY=htA;   both X and Y are row-vectors.   */
#define MDcu_mulM( MC, MA, MB, htA, lenA, lenB )  MDcumulM( (MC)[0], (MA)[0], (MB)[0], htA, lenA, lenB )
                         /*  MC = MA * MB.  htB=lenA, htC=htA, lenC=lenB */
#define MDcu_mulMT( MC, MA, MB, htA, lenA, htB )  MDcumulMT( (MC)[0], (MA)[0], (MB)[0], htA, lenA, htB )
                         /*  MC = MA * MBT.  lenB=lenA, htC=htA, lenC=htB */
#define MDcu_TmulM( MC, MA, MB, htA, lenA, lenB ) MDcuTmulM( (MC)[0], (MA)[0], (MB)[0], htA, lenA, lenB )
                         /*  MC = MAT * MB.  htB=htA, htC=lenA, lenC=lenB */
#define MDcu_TmulMT( MC, MA, MB, htA, lenA, htB ) MDcuTmulMT( (MC)[0], (MA)[0], (MB)[0], htA, lenA, htB )
                         /*  MC = MAT * MBT.  lenB=htA, htC=lenA, lenC=htB */
#define MDdiacu_mulM(  MC, MADia, MB, htB, lenB )  MDdiacumulM(  (MC)[0], MADia, (MB)[0], htB, lenB )
#define MDdiacu_mulMT( MC, MADia, MB, htB, lenB )  MDdiacumulMT( (MC)[0], MADia, (MB)[0], htB, lenB )
#define MDcu_mulMdia(  MC, MA, MBDia, htA, lenA )  MDcumulMdia(  (MC)[0], (MA)[0], MBDia, htA, lenA )
#define MDcu_TmulMdia( MC, MA, MBDia, htA, lenA )  MDcuTmulMdia( (MC)[0], (MA)[0], MBDia, htA, lenA )

/***************** Two-Dimensional Fourier-Transform Methods ************/

#define MDcu_FFT( MY, MX, ht, len, dir )     MDcuFFT( (MY)[0], (MX)[0], ht, len, dir )
#define MDcu_Rows_FFT( MY, MX, ht, len, dir) MDcuRows_FFT( (MY)[0], (MX)[0], ht, len, dir )
#define MDcu_Cols_FFT( MY, MX, ht, len, dir) MDcuCols_FFT( (MY)[0], (MX)[0], ht, len, dir )
#define MDcu_FFTtoC( MY, MX, ht, len )       MDcuFFTtoC( (MY)[0], (MX)[0], ht, len )
#define MDcu_Rows_FFTtoC( MY, MX, ht, len )  MDcuRows_FFTtoC( (MY)[0], (MX)[0], ht, len )
#define MDcu_Cols_FFTtoC( MY, MX, ht, len )  MDcuCols_FFTtoC( (MY)[0], (MX)[0], ht, len )
#define MDcu_convolve( MY, MFlt, MX, MRsp, ht, len ) \
                  MDcuconvolve( (MY)[0], (MFlt)[0], (MX)[0], (MRsp)[0], ht, len )
#define MDcu_deconvolve( MY, MFlt, MX, MRsp, ht, len ) \
                  MDcudeconvolve( (MY)[0], (MFlt)[0], (MX)[0], (MRsp)[0], ht, len )
#define MDcu_filter( MY, MX, MFlt, ht, len ) MDcufilter( (MY)[0], (MX)[0], (MFlt)[0], ht, len )
#define MDcu_autocorr( MACorr, MX, ht, len ) MDcuautocorr( (MACorr)[0], (MX)[0], ht, len )
#define MDcu_xcorr( MXCorr, MX, MY, ht, len) MDcuxcorr( (MXCorr)[0], (MX)[0], (MY)[0], ht, len )
#define MDcu_spectrum( MSpec, htSpec, lenSpec, MX, htX, lenX, MWin ) \
              MDcuspectrum( (MSpec)[0], htSpec, lenSpec, (MX)[0], htX, lenX, (MWin)[0] )
              /*   htSpec, lenSpec must be 2**n,
                   MSpec must be a (htSpec+1)*(lenSpec+1) matrix!!
                   htX >= n*htSpec,  lenX >= n*lenSpec,
                   htWin = 2*htSpec, lenWin = 2*lenSpec */


/*************************************************************************
 * MDcu functions (without underbar in the prefix): 	
    (working on matrices in host memory, input type 
	dPMatrix = dVector = pointer to matrix element[0][0], 
	scalar parameters on host and passed by value)
*
 *************************************************************************/

#define MDcuequ0( MA, ht, len )       VDcu_equ0( MA, (ht)*(len) )
void   __vf OVCUAPI  MDcuequ1( dPMatrix MA, ui len );  /* identity matrix */
void   __vf OVCUAPI  MDcuequm1( dPMatrix MA, ui len );  /* neg. identity matrix */
void   __vf OVCUAPI  MDcuouterprod( dPMatrix MA, dVector X,  dVector Y, ui ht, ui len );

void   __vf OVCUAPI  MDcuRow_equ0( dPMatrix MA, ui ht, ui len, ui iRow );
void   __vf OVCUAPI  MDcuCol_equ0( dPMatrix MA, ui ht, ui len, ui iCol );
void   __vf OVCUAPI  MDcuDia_equ0( dPMatrix MA, ui len );

void   __vf OVCUAPI  MDcuRow_equC( dPMatrix MA, ui ht, ui len, ui iRow, double C );
void   __vf OVCUAPI  MDcuCol_equC( dPMatrix MA, ui ht, ui len, ui iCol, double C );
void   __vf OVCUAPI  MDcuDia_equC( dPMatrix MA, ui len, double C );

void   __vf OVCUAPI  MDcuRow_equV( dPMatrix MA, ui ht, ui len, ui iRow, dVector X );
void   __vf OVCUAPI  MDcuCol_equV( dPMatrix MA, ui ht, ui len, ui iCol, dVector X );
void   __vf OVCUAPI  MDcuDia_equV( dPMatrix MA, ui len, dVector X );

void   __vf OVCUAPI  MDcuTrd_equM( dPMatrix MA, dPMatrix MTrd, ui len );
void   __vf OVCUAPI  MDcuTrd_extract( dPMatrix MTrd, dPMatrix MA, ui len );

#define MDcuequM( MB, MA, ht, len )      VDcu_equV( MB, MA, (ht)*(len) )
#define MDcuneg( MB, MA, ht, len )       VDcu_neg( MB, MA, (ht)*(len) )
void   __vf OVCUAPI  MDcuUequL( dPMatrix MA, ui len );
void   __vf OVCUAPI  MDcuLequU( dPMatrix MA, ui len );

void   __vf OVCUAPI  MDcuHann( dPMatrix MA, ui ht, ui len );
#define MDcuHanning MDcuHann
void   __vf OVCUAPI  MDcuParzen(  dPMatrix MA, ui ht, ui len );
void   __vf OVCUAPI  MDcuWelch(   dPMatrix MA, ui ht, ui len );

            /* data-type conversions:  */
#define McuDtoF( MF, MD, ht, len ) Vcu_DtoF( (MF), (MD), (ht)*(len) )
#define McuFtoD( MD, MF, ht, len ) Vcu_FtoD( (MD), (MF), (ht)*(len) )

/********  Extracting a submatrix and copying a submatrix back  *********/

void  __vf OVCUAPI  MDcusubmatrix( dPMatrix MSub, ui subHt,  ui subLen,
                          dPMatrix MSrce, ui srceHt,  ui srceLen,
                          ui firstRowInCol,  ui sampInCol,
                          ui firstColInRow,  ui sampInRow );

void  __vf OVCUAPI  MDcusubmatrix_equM( dPMatrix MDest, ui destHt, ui destLen,
                               ui firstRowInCol,  ui sampInCol,
                               ui firstColInRow,  ui sampInRow,
                               dPMatrix MSrce, ui srceHt, ui srceLen );

void  __vf OVCUAPI  MDcuequMblock(  dPMatrix MSub, ui subHt, ui subLen,
                          dPMatrix MSrce, ui srceHt,  ui srceLen,
                          ui firstRowInCol,  ui firstColInRow );

void  __vf OVCUAPI  MDcublock_equM( dPMatrix MDest, ui destHt, ui destLen,
                          ui firstRowInCol,  ui firstColInRow,
                          dPMatrix MSrce, ui srceHt, ui srceLen );

void  __vf OVCUAPI  MDcuequMblockT( dPMatrix MSub, ui subHt, ui subLen,
                          dPMatrix MSrce, ui srceHt, ui srceLen,
                          ui firstRowInCol,  ui firstColInRow );

void  __vf OVCUAPI  MDcublock_equMT( dPMatrix MDest, ui destHt, ui destLen,
                          ui firstRowInCol,  ui firstColInRow,
                          dPMatrix MSrce, ui srceHt, ui srceLen );


/*****   Extracting a single row or a single column or the diagonal  *****
 *       and storing it into a vector                                    */

void __vf OVCUAPI  MDcuRow_extract( dVector Y, dPMatrix MA, ui ht, ui len, ui iRow );
void __vf OVCUAPI  MDcuCol_extract( dVector Y, dPMatrix MA, ui ht, ui len, ui iCol );
void __vf OVCUAPI  MDcuDia_extract( dVector Y, dPMatrix MA, ui len );

/**********  Deleting or inserting a row or a column *****************/

void __vf OVCUAPI  MDcuRow_delete( dPMatrix MB, dPMatrix MA, ui htA, ui lenA, ui iRow );
void __vf OVCUAPI  MDcuCol_delete( dPMatrix MB, dPMatrix MA, ui htA, ui lenA, ui iCol );
void __vf OVCUAPI  MDcuRow_insert( dPMatrix MB, dPMatrix MA, ui htB, ui lenB, ui iRow, dVector X );
void __vf OVCUAPI  MDcuCol_insert( dPMatrix MB, dPMatrix MA, ui htB, ui lenB, ui iCol, dVector X );


/*****************    Basic arithmetic operations ***********************
     performed on one single row,  or one single column of any matrix,
     or on the diagonal of a square matrix                              */

void   __vf OVCUAPI  MDcuRow_neg( dPMatrix MX, ui ht, ui len, ui iRow );
void   __vf OVCUAPI  MDcuCol_neg( dPMatrix MX, ui ht, ui len, ui iCol );

void   __vf OVCUAPI  MDcuRow_addC( dPMatrix MA, ui ht, ui len, ui iRow, double C );
void   __vf OVCUAPI  MDcuCol_addC( dPMatrix MA, ui ht, ui len, ui iCol, double C );
void   __vf OVCUAPI  MDcuDia_addC( dPMatrix MA, ui len, double C );

void   __vf OVCUAPI  MDcuRow_subC( dPMatrix MA, ui ht, ui len, ui iRow, double C );
void   __vf OVCUAPI  MDcuCol_subC( dPMatrix MA, ui ht, ui len, ui iCol, double C );
void   __vf OVCUAPI  MDcuDia_subC( dPMatrix MA, ui len, double C );

void   __vf OVCUAPI  MDcuRow_addV( dPMatrix MA, ui ht, ui len, ui iRow, dVector X );
void   __vf OVCUAPI  MDcuCol_addV( dPMatrix MA, ui ht, ui len, ui iCol, dVector X );
void   __vf OVCUAPI  MDcuDia_addV( dPMatrix MA, ui len, dVector X );

void   __vf OVCUAPI  MDcuRow_subV( dPMatrix MA, ui ht, ui len, ui iRow, dVector X );
void   __vf OVCUAPI  MDcuCol_subV( dPMatrix MA, ui ht, ui len, ui iCol, dVector X );
void   __vf OVCUAPI  MDcuDia_subV( dPMatrix MA, ui len, dVector X );

void   __vf OVCUAPI  MDcuRow_subrC( dPMatrix MA, ui ht, ui len, ui iRow, double C );
void   __vf OVCUAPI  MDcuCol_subrC( dPMatrix MA, ui ht, ui len, ui iCol, double C );
void   __vf OVCUAPI  MDcuDia_subrC( dPMatrix MA, ui len, double C );

void   __vf OVCUAPI  MDcuRow_subrV( dPMatrix MA, ui ht, ui len, ui iRow, dVector X );
void   __vf OVCUAPI  MDcuCol_subrV( dPMatrix MA, ui ht, ui len, ui iCol, dVector X );
void   __vf OVCUAPI  MDcuDia_subrV( dPMatrix MA, ui len, dVector X );

void   __vf OVCUAPI  MDcuRow_mulC( dPMatrix MA, ui ht, ui len, ui iRow, double C );
void   __vf OVCUAPI  MDcuCol_mulC( dPMatrix MA, ui ht, ui len, ui iCol, double C );
void   __vf OVCUAPI  MDcuDia_mulC( dPMatrix MA, ui len, double C );

void   __vf OVCUAPI  MDcuRow_mulV( dPMatrix MA, ui ht, ui len, ui iRow, dVector X );
void   __vf OVCUAPI  MDcuCol_mulV( dPMatrix MA, ui ht, ui len, ui iCol, dVector X );
void   __vf OVCUAPI  MDcuDia_mulV( dPMatrix MA, ui len, dVector X );

void   __vf OVCUAPI  MDcuRow_divC( dPMatrix MA, ui ht, ui len, ui iRow, double C );
void   __vf OVCUAPI  MDcuCol_divC( dPMatrix MA, ui ht, ui len, ui iCol, double C );
void   __vf OVCUAPI  MDcuDia_divC( dPMatrix MA, ui len, double C );

void   __vf OVCUAPI  MDcuRow_divV( dPMatrix MA, ui ht, ui len, ui iRow, dVector X );
void   __vf OVCUAPI  MDcuCol_divV( dPMatrix MA, ui ht, ui len, ui iCol, dVector X );
void   __vf OVCUAPI  MDcuDia_divV( dPMatrix MA, ui len, dVector X );

void   __vf OVCUAPI  MDcuRow_divrC( dPMatrix MA, ui ht, ui len, ui iRow, double C );
void   __vf OVCUAPI  MDcuCol_divrC( dPMatrix MA, ui ht, ui len, ui iCol, double C );
void   __vf OVCUAPI  MDcuDia_divrC( dPMatrix MA, ui len, double C );

void   __vf OVCUAPI  MDcuRow_divrV( dPMatrix MA, ui ht, ui len, ui iRow, dVector X );
void   __vf OVCUAPI  MDcuCol_divrV( dPMatrix MA, ui ht, ui len, ui iCol, dVector X );
void   __vf OVCUAPI  MDcuDia_divrV( dPMatrix MA, ui len, dVector X );


/******  One-dimensional vector operations **********************
         performed along all rows or all columns simultaneously,
         or along the diagonal of a square matrix                */

void   __vf OVCUAPI  MDcuRows_max( dVector Y, dPMatrix MA, ui ht, ui len );
void   __vf OVCUAPI  MDcuCols_max( dVector Y, dPMatrix MA, ui ht, ui len );
double  __vf OVCUAPI  MDcuDia_max(  dPMatrix MA, ui len );
void   __vf OVCUAPI  MDcuRows_min( dVector Y, dPMatrix MA, ui ht, ui len );
void   __vf OVCUAPI  MDcuCols_min( dVector Y, dPMatrix MA, ui ht, ui len );
double  __vf OVCUAPI  MDcuDia_min(  dPMatrix MA, ui len );

void   __vf OVCUAPI  MDcuRows_absmax( dVector Y, dPMatrix MA, ui ht, ui len );
void   __vf OVCUAPI  MDcuCols_absmax( dVector Y, dPMatrix MA, ui ht, ui len );
double  __vf OVCUAPI  MDcuDia_absmax(  dPMatrix MA, ui len );
void   __vf OVCUAPI  MDcuRows_absmin( dVector Y, dPMatrix MA, ui ht, ui len );
void   __vf OVCUAPI  MDcuCols_absmin( dVector Y, dPMatrix MA, ui ht, ui len );
double  __vf OVCUAPI  MDcuDia_absmin(  dPMatrix MA, ui len );

void   __vf OVCUAPI  MDcuRows_sum( dVector Y, dPMatrix MA, ui ht, ui len );
void   __vf OVCUAPI  MDcuCols_sum( dVector Y, dPMatrix MA, ui ht, ui len );
double  __vf OVCUAPI  MDcuDia_sum(  dPMatrix MA, ui len );
void   __vf OVCUAPI  MDcuRows_ssq( dVector Y, dPMatrix MA, ui ht, ui len );
void   __vf OVCUAPI  MDcuCols_ssq( dVector Y, dPMatrix MA, ui ht, ui len );
double  __vf OVCUAPI  MDcuDia_ssq(  dPMatrix MA, ui len );
void   __vf OVCUAPI  MDcuRows_prod(dVector Y, dPMatrix MA, ui ht, ui len );
void   __vf OVCUAPI  MDcuCols_prod(dVector Y, dPMatrix MA, ui ht, ui len );
double  __vf OVCUAPI  MDcuDia_prod( dPMatrix MA, ui len );

void  __vf OVCUAPI  MDcuRows_runsum( dPMatrix MA, ui ht, ui len );
void  __vf OVCUAPI  MDcuCols_runsum( dPMatrix MA, ui ht, ui len );
void  __vf OVCUAPI  MDcuRows_runprod( dPMatrix MA, ui ht, ui len );
void  __vf OVCUAPI  MDcuCols_runprod( dPMatrix MA, ui ht, ui len );

void  __vf OVCUAPI  MDcuRows_rotate( dPMatrix MA, ui ht, ui len, ssize_t pos );
void  __vf OVCUAPI  MDcuCols_rotate( dPMatrix MA, ui ht, ui len, ssize_t pos );
void  __vf OVCUAPI  MDcuRows_rotate_buf( dPMatrix MA, ui ht, ui len, ssize_t pos, dPMatrix MBuf );
void  __vf OVCUAPI  MDcuCols_rotate_buf( dPMatrix MA, ui ht, ui len, ssize_t pos, dPMatrix MBuf );
void  __vf OVCUAPI  MDcuRows_reflect( dPMatrix MA, ui ht, ui len );
void  __vf OVCUAPI  MDcuCols_reflect( dPMatrix MA, ui ht, ui len );
void  __vf OVCUAPI  MDcuRows_rev( dPMatrix MA, ui ht, ui len );
void  __vf OVCUAPI  MDcuCols_rev( dPMatrix MA, ui ht, ui len );
void  __vf OVCUAPI  MDcuRows_distribution( uiPMatrix MAbund, dVector Limits, ui nBins, dPMatrix MX, ui ht, ui len, int mode );
void  __vf OVCUAPI  MDcuCols_distribution( uiPMatrix MAbund, dVector Limits, ui nBins, dPMatrix MX, ui ht, ui len, int mode );

/********  Operations involving two rows or two colums of one matrix  *****/

void   __vf OVCUAPI  MDcuRows_exchange( dPMatrix MA, ui ht, ui len, ui i1, ui i2 );
void   __vf OVCUAPI  MDcuCols_exchange( dPMatrix MA, ui ht, ui len, ui i1, ui i2 );

void   __vf OVCUAPI  MDcuRows_add( dPMatrix MA, ui ht, ui len, ui destRow, ui sourceRow );
void   __vf OVCUAPI  MDcuCols_add( dPMatrix MA, ui ht, ui len, ui destCol, ui sourceCol );

void   __vf OVCUAPI  MDcuRows_sub( dPMatrix MA, ui ht, ui len, ui destRow, ui sourceRow );
void   __vf OVCUAPI  MDcuCols_sub( dPMatrix MA, ui ht, ui len, ui destCol, ui sourceCol );

void   __vf OVCUAPI  MDcuRows_Cadd( dPMatrix MA, ui ht, ui len, ui destRow, ui sourceRow, double C );
void   __vf OVCUAPI  MDcuCols_Cadd( dPMatrix MA, ui ht, ui len, ui destCol, ui sourceCol, double C );

void   __vf OVCUAPI  MDcuRows_lincomb( dPMatrix MA, ui ht, ui len,
					ui destRow,  double  destC, ui srceRow,  double  srceC );
void   __vf OVCUAPI  MDcuCols_lincomb( dPMatrix MA, ui ht, ui len,
                              ui destCol,  double  destC, ui srceCol,  double  srceC );


/*********************  Center of gravity *****************************/
#if defined __cplusplus && defined _CMATH_CLASSDEFS
} // the following functions cannot be extern "C", if dComplex is a class
#endif
dComplex __vf OVCUAPI  MDcucenterOfGravityInd( dPMatrix MA, ui ht, ui len );
dComplex __vf OVCUAPI  MDcucenterOfGravityV( dVector X, dVector Y, dPMatrix MA, ui ht, ui len );
#if defined __cplusplus && defined _CMATH_CLASSDEFS
extern "C" {
#endif

/***************  Transposing and rotating a matrix **********************/

void  __vf OVCUAPI  MDcutranspose( dPMatrix MTr, dPMatrix MA,  ui htTr, ui lenTr );
void  __vf OVCUAPI  MDcurotate90(  dPMatrix MRot, dPMatrix MA, ui htRot, ui lenRot );
#define     MDcurotate180( MRot, MA, htRot, lenRot )  VDcu_rev( MRot, MA, (htRot)*(lenRot) )
void  __vf OVCUAPI  MDcurotate270( dPMatrix MRot, dPMatrix MA, ui htRot, ui lenRot );


/********************** Interpolation of Matrix elements **************/

void __vf OVCUAPI  MDcupolyinterpol( dPMatrix MZ, dVector X, dVector Y, ui ht, ui len,
       dVector XTab, dVector YTab, dPMatrix MZTab, ui httab, ui lentab,
       unsigned degX, unsigned degY );
void __vf OVCUAPI  MDcuratinterpol( dPMatrix MZ, dVector X, dVector Y, ui ht, ui len,
       dVector XTab, dVector YTab, dPMatrix MZTab, ui httab, ui lentab,
       unsigned degX, unsigned degY );
void __vf OVCUAPI  MDcunatCubSplineInterpol( dPMatrix MZ, dVector X, dVector Y, ui ht, ui len,
       dVector XTab, dVector YTab, dPMatrix MZTab, ui httab, ui lentab );


/************************ Matrix Arithmetics *************************/

#define MDcuaddM( MC, MA, MB, htA, lenA )            VDcu_addV( MC, MA, MB, (htA)*(lenA) )
void __vf OVCUAPI  MDcuaddMT( dPMatrix MC, dPMatrix MA, dPMatrix MB, ui htA, ui lenA );
#define MDcusubM( MC, MA, MB, htA, lenA )            VDcu_subV( MC, MA, MB, (htA)*(lenA) )
void __vf OVCUAPI  MDcusubMT( dPMatrix MC, dPMatrix MA, dPMatrix MB, ui htA, ui lenA );
void __vf OVCUAPI  MDcusubrMT( dPMatrix MC, dPMatrix MA, dPMatrix MB, ui htA, ui lenA );
#define MDcumulC( MB, MA, htA, lenA, C )             VDcu_mulC( MB, MA, (htA)*(lenA), C )
#define MDcudivC( MB, MA, htA, lenA, C )             VDcu_divC( MB, MA, (htA)*(lenA), C )
#define MDscuaddM( MC, MA, MB, htA, lenA, C )        VDscu_addV( MC, MA, MB, (htA)*(lenA), C )
void __vf OVCUAPI  MDscuaddMT( dPMatrix MC, dPMatrix MA, dPMatrix MB, ui htA, ui lenA, double C );
#define MDscusubM( MC, MA, MB, htA, lenA, C )        VDscu_subV( MC, MA, MB, (htA)*(lenA), C )
void __vf OVCUAPI  MDscusubMT( dPMatrix MC, dPMatrix MA, dPMatrix MB, ui htA, ui lenA, double C );
void __vf OVCUAPI  MDscusubrMT( dPMatrix MC, dPMatrix MA, dPMatrix MB, ui htA, ui lenA, double C );
#define MDculincomb( MC, MA, MB, htA, lenA, CA, CB ) VDcu_lincomb( MC, MA, MB, (htA)*(lenA), CA, CB )
void  __vf OVCUAPI  MDcumulV( dVector Y, dPMatrix MA, dVector X, ui htA, ui lenA );
void  __vf OVCUAPI  MDcuTmulV( dVector Y, dPMatrix MA, dVector X, ui htA, ui lenA );
void  __vf OVCUAPI  VDcumulM( dVector Y, dVector X, dPMatrix MA, ui htA, ui lenA );
void  __vf OVCUAPI  VDcumulMT( dVector Y, dVector X, dPMatrix MA, ui htA, ui lenA );
void  __vf OVCUAPI  MDcumulM( dPMatrix MC, dPMatrix MA, dPMatrix MB, ui htA, ui lenA, ui lenB );
void  __vf OVCUAPI  MDcumulMT( dPMatrix MC, dPMatrix MA, dPMatrix MB, ui htA, ui lenA, ui htB );
void  __vf OVCUAPI  MDcuTmulM( dPMatrix MC, dPMatrix MA, dPMatrix MB, ui htA, ui lenA, ui lenB );
void  __vf OVCUAPI  MDcuTmulMT( dPMatrix MC, dPMatrix MA, dPMatrix MB, ui htA, ui lenA, ui htB );
void  __vf OVCUAPI  MDcudiamulM( dPMatrix MC, dPMatrix MADia, dPMatrix MB, ui htB, ui lenB );
void  __vf OVCUAPI  MDcudiamulMT( dPMatrix MC, dPMatrix MADia, dPMatrix MB, ui htB, ui lenB );
void  __vf OVCUAPI  MDcumulMdia( dPMatrix MC, dPMatrix MA, dPMatrix MBDia, ui htA, ui lenA );
void  __vf OVCUAPI  MDcuTmulMdia( dPMatrix MC, dPMatrix MA, dPMatrix MBDia, ui htA, ui lenA );


/*************  Matrix Fourier-Transform Methods *****************/

void  __vf OVCUAPI   MDcuFFT( dPMatrix MY, dPMatrix MX, ui ht, ui len, int dir );
void  __vf OVCUAPI   MDcuFFTtoC( cdPMatrix MY, dPMatrix MX, ui ht, ui len );
void  __vf OVCUAPI   MDcuconvolve( dPMatrix MY, dPMatrix MFlt, dPMatrix MX, dPMatrix MRsp, ui ht, ui len );
void  __vf OVCUAPI   MDcudeconvolve( dPMatrix MY, dPMatrix MFlt, dPMatrix MX, dPMatrix MRsp, ui ht, ui len );
void  __vf OVCUAPI   MDcufilter( dPMatrix MY, dPMatrix MX, dPMatrix MFlt, ui ht, ui len );
void  __vf OVCUAPI   MDcuautocorr( dPMatrix MACorr, dPMatrix MX, ui ht, ui len );
void  __vf OVCUAPI   MDcuxcorr( dPMatrix MXCorr, dPMatrix MX, dPMatrix MY, ui ht, ui len );
void  __vf OVCUAPI   MDcuspectrum( dPMatrix MSpec, ui htSpec, ui lenSpec, dPMatrix MX, ui htX, ui lenX, dPMatrix MWin );
void  __vf OVCUAPI   MDcuRows_FFT( dPMatrix MY, dPMatrix MX, ui ht, ui len, int dir );
void  __vf OVCUAPI   MDcuCols_FFT( dPMatrix MY, dPMatrix MX, ui ht, ui len, int dir );
void  __vf OVCUAPI   MDcuRows_FFTtoC( cdPMatrix MY, dPMatrix MX, ui ht, ui len );
void  __vf OVCUAPI   MDcuCols_FFTtoC( cdPMatrix MY, dPMatrix MX, ui ht, ui len );


#ifdef __cplusplus
}  // end of extern "C"
#endif // __cplusplus
#endif /* __CUDAMDSTD_H */
