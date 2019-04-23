/*  cudaMULstd.h

  matrix management functions:
  manipulations on matrices of data type "unsigned long" 
  (32-bit unsigned integers)

  This file declares the functions with the name variants 
	cudaMUL_func	(working on matrices in device memory, input type ulMatrix, scalar parameters reside on host and are passed by value)
	cusdMUL_func	(as cudaMUL_func except scalar parameters reside on device and are passed by address)
	cudaMULfunc		(as cudaMUL_func, but input type ulPMatrix = ulVector = pointer to matrix element[0][0])
	cusdMULfunc		(as cusdMUL_func, but input type ulPMatrix = ulVector = pointer to matrix element[0][0])
	MULcu_func		(working on matrices in host memory, input type ulMatrix, scalar parameters on host and passed by value)
	MULcufunc		(as MULcu_func, but input type ulPMatrix = ulVector = pointer to matrix element[0][0])
  where func is the respective function.

   Copyright (c) 1996-2017 by OptiCode - Dr. Martin Sander Software Dev.
  All Rights Reserved.

*/

#if !defined( __CUDAMULSTD_H )
#define __CUDAMULSTD_H
#if !defined( __CUDAMATLIB_H )
#include <cudaMatLib.h>
#endif
#if !defined( __CUDAVULSTD_H )
#include <cudaVULstd.h>
#endif
#if !defined( __CUDAVULMATH_H )
#include <cudaVULmath.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif

/**** Generation of matrices on device memory and on pinned host memory *******************/

ulMatrix  __vf cudaMUL_matrix( ui ht, ui len );   /* allocates a vector on device memory */
ulMatrix  __vf cudaMUL_matrix0( ui ht, ui len );
 /* The following functions allocate device-accessible, "pinned" memory on the host.
	This memory is mapped onto the device memory space. The resulting device address is returned.
	The matrix can be accessed either by its host address "hostPtr" e.g., MUL_equ1( hostPtr, ht, len );
	or by its device address , e.g., cudaMUL_equ1( devicePtr, ht, len );                             */
ulMatrix  __vf cudaMUL_pinnedMatrix(  ulMatrix *hostPtr, ui ht, ui len ); 
ulMatrix  __vf cudaMUL_pinnedMatrix0( ulMatrix *hostPtr, ui ht, ui len );

/*************************************************************************
 * Declarations of the functions written without underbar in the prefix: *
 *	cudaMULfunc  (input type 
                   ulPMatrix = ulVector = pointer to matrix element[0][0])
 *	cusdMULfunc  (input type 
                   ulPMatrix = ulVector = pointer to matrix element[0][0])
 *************************************************************************/


void  __vcuf OVCUAPI  cudaMULsetElement( ulPMatrix X, ui ht, ui len, ui m, ui n, unsigned long C );
void  __vcuf OVCUAPI  cusdMULsetElement( ulPMatrix X, ui ht, ui len, ui m, ui n, unsigned long *d_C );
void  __vcuf OVCUAPI  cudaMULgetElement( unsigned long *h_y, ulPMatrix X, ui ht, ui len, ui m, ui n );
void  __vcuf OVCUAPI  cusdMULgetElement( unsigned long *d_y, ulPMatrix X, ui ht, ui len, ui m, ui n );
unsigned long * __vcuf OVCUAPI  cudaMULPelement( ulPMatrix X, ui ht, ui len, ui m, ui n );
unsigned long   __vcuf OVCUAPI  cudaMULelement(  ulPMatrix X, ui ht, ui len, ui m, ui n );

#define cudaMULequ0( MA, ht, len )            cudaVUL_equ0( MA, (ht)*(len) )
overror_t   __vcuf OVCUAPI  cudaMULequ1( ulPMatrix MA, ui len );  /* identity matrix */
overror_t   __vcuf OVCUAPI  cudaMULouterprod( ulPMatrix MA, ulVector X,  ulVector Y, ui ht, ui len );

overror_t   __vcuf OVCUAPI  cudaMULRow_equ0( ulPMatrix MA, ui ht, ui len, ui iRow );
overror_t   __vcuf OVCUAPI  cudaMULCol_equ0( ulPMatrix MA, ui ht, ui len, ui iCol );
overror_t   __vcuf OVCUAPI  cudaMULDia_equ0( ulPMatrix MA, ui len );

overror_t   __vcuf OVCUAPI  cudaMULRow_equC( ulPMatrix MA, ui ht, ui len, ui iRow, unsigned long C );
overror_t   __vcuf OVCUAPI  cudaMULCol_equC( ulPMatrix MA, ui ht, ui len, ui iCol, unsigned long C );
overror_t   __vcuf OVCUAPI  cudaMULDia_equC( ulPMatrix MA, ui len, unsigned long C );
overror_t   __vcuf OVCUAPI  cusdMULRow_equC( ulPMatrix MA, ui ht, ui len, ui iRow, unsigned long *d_C );
overror_t   __vcuf OVCUAPI  cusdMULCol_equC( ulPMatrix MA, ui ht, ui len, ui iCol, unsigned long *d_C );
overror_t   __vcuf OVCUAPI  cusdMULDia_equC( ulPMatrix MA, ui len, unsigned long *d_C );

overror_t   __vcuf OVCUAPI  cudaMULRow_equV( ulPMatrix MA, ui ht, ui len, ui iRow, ulVector X );
overror_t   __vcuf OVCUAPI  cudaMULCol_equV( ulPMatrix MA, ui ht, ui len, ui iCol, ulVector X );
overror_t   __vcuf OVCUAPI  cudaMULDia_equV( ulPMatrix MA, ui len, ulVector X );

overror_t   __vcuf OVCUAPI  cudaMULTrd_equM( ulPMatrix MA, ulPMatrix MTrd, ui len );
overror_t   __vcuf OVCUAPI  cudaMULTrd_extract( ulPMatrix MTrd, ulPMatrix MA, ui len );

#define cudaMULequM( MB, MA, ht, len )  cudaVUL_equV( MB, MA, (ht)*(len) )
#define cudaMULequMhost( MB, MA, ht, len )  cudaVUL_equVhost( MB, MA, (ht)*(len) )
#define MULequMdevice( MB, MA, ht, len )    VUL_equVdevice( MB, MA, (ht)*(len) )
overror_t   __vcuf OVCUAPI  cudaMULUequL( ulPMatrix MA, ui len );
overror_t   __vcuf OVCUAPI  cudaMULLequU( ulPMatrix MA, ui len );

            /* data-type conversions:  */
#define cudaMLItoUL( MUL, MLI, ht, len ) cudaV_LItoUL( (MUL), (MLI), (ht)*(len) )
#define cudaMULtoLI( MLI, MUL, ht, len ) cudaV_ULtoLI( (MLI), (MUL), (ht)*(len) )
#define cudaMULtoUB( MUB, MUL, ht, len ) cudaV_ULtoUB( (MUB), (MUL), (ht)*(len) )
#define cudaMULtoUS( MUS, MUL, ht, len ) cudaV_ULtoUS( (MUS), (MUL), (ht)*(len) )
#define cudaMULtoU(  MU,  MUL, ht, len ) cudaV_ULtoU(  (MU),  (MUL), (ht)*(len) )
#define cudaMUBtoUL( MUL, MUB, ht, len ) cudaV_UBtoUL( (MUL), (MUB), (ht)*(len) )
#define cudaMUStoUL( MUL, MUS, ht, len ) cudaV_UStoUL( (MUL), (MUS), (ht)*(len) )
#define cudaMUtoUL(  MUL, MU,  ht, len ) cudaV_UtoUL(  (MUL), (MU),  (ht)*(len) )
#ifdef _WIN64
	#define cudaMULtoUQ( MUQ, MUL, ht, len ) cudaV_ULtoUQ( (MUQ), (MUL), (ht)*(len) )
	#define cudaMUQtoUL( MUL, MUQ, ht, len ) cudaV_UQtoUL( (MUL), (MUQ), (ht)*(len) )
#endif
#define cudaMULtoF(  MF,  MUL, ht, len ) cudaV_ULtoF(  (MF),  (MUL), (ht)*(len) )
#define cudaMULtoD(  MD,  MUL, ht, len ) cudaV_ULtoD(  (MD),  (MUL), (ht)*(len) )

/********  Extracting a submatrix and copying a submatrix back  *********/

overror_t  __vcuf OVCUAPI  cudaMULsubmatrix( ulPMatrix MSub,  ui subHt,  ui subLen,
                          ulPMatrix MSrce, ui srceHt,  ui srceLen,
                          ui firstRowInCol,  ui sampInCol,
                          ui firstColInRow,  ui sampInRow );

overror_t  __vcuf OVCUAPI  cudaMULsubmatrix_equM( ulPMatrix MDest, ui destHt, ui destLen,
                               ui firstRowInCol,  ui sampInCol,
                               ui firstColInRow,  ui sampInRow,
                               ulPMatrix MSrce, ui srceHt, ui srceLen );

overror_t  __vcuf OVCUAPI  cudaMULequMblock(  ulPMatrix MSub, ui subHt, ui subLen,
                          ulPMatrix MSrce, ui srceHt,  ui srceLen,
                          ui firstRowInCol,  ui firstColInRow );

overror_t  __vcuf OVCUAPI  cudaMULblock_equM( ulPMatrix MDest, ui destHt, ui destLen,
                          ui firstRowInCol,  ui firstColInRow,
                          ulPMatrix MSrce,  ui srceHt, ui srceLen );

overror_t  __vcuf OVCUAPI  cudaMULequMblockT( ulPMatrix MSub, ui subHt, ui subLen,
                          ulPMatrix MSrce, ui srceHt, ui srceLen,
                          ui firstRowInCol,  ui firstColInRow );

overror_t  __vcuf OVCUAPI  cudaMULblock_equMT( ulPMatrix MDest, ui destHt, ui destLen,
                          ui firstRowInCol,  ui firstColInRow,
                          ulPMatrix MSrce, ui srceHt, ui srceLen );


/*****   Extracting a single row or a single column or the diagonal  *****
 *       and storing it into a vector                                    */

overror_t __vcuf OVCUAPI  cudaMULRow_extract( ulVector Y, ulPMatrix MA, ui ht, ui len, ui iRow );
overror_t __vcuf OVCUAPI  cudaMULCol_extract( ulVector Y, ulPMatrix MA, ui ht, ui len, ui iCol );
overror_t __vcuf OVCUAPI  cudaMULDia_extract( ulVector Y, ulPMatrix MA, ui len );


/**********  Deleting or inserting a row or a column *****************/

overror_t __vcuf OVCUAPI  cudaMULRow_delete( ulPMatrix MB, ulPMatrix MA, ui htA, ui lenA, ui iRow );
overror_t __vcuf OVCUAPI  cudaMULCol_delete( ulPMatrix MB, ulPMatrix MA, ui htA, ui lenA, ui iCol );
overror_t __vcuf OVCUAPI  cudaMULRow_insert( ulPMatrix MB, ulPMatrix MA, ui htB, ui lenB, ui iRow, ulVector X );
overror_t __vcuf OVCUAPI  cudaMULCol_insert( ulPMatrix MB, ulPMatrix MA, ui htB, ui lenB, ui iCol, ulVector X );


/******  One-dimensional vector operations **********************
         performed along all rows or all columns simultaneously,
         or along the diagonal of a square matrix                */

overror_t  __vcuf OVCUAPI  cudaMULRows_max( ulVector Y, ulPMatrix MA, ui ht, ui len );
overror_t  __vcuf OVCUAPI  cudaMULCols_max( ulVector Y, ulPMatrix MA, ui ht, ui len );
overror_t  __vcuf OVCUAPI  cudaMULDia_max(  unsigned long *h_RetVal, ulPMatrix MA, ui len );
overror_t  __vcuf OVCUAPI  cusdMULDia_max(  unsigned long *d_RetVal, ulPMatrix MA, ui len );
overror_t  __vcuf OVCUAPI  cudaMULRows_min( ulVector Y, ulPMatrix MA, ui ht, ui len );
overror_t  __vcuf OVCUAPI  cudaMULCols_min( ulVector Y, ulPMatrix MA, ui ht, ui len );
overror_t  __vcuf OVCUAPI  cudaMULDia_min(  unsigned long *h_RetVal, ulPMatrix MA, ui len );
overror_t  __vcuf OVCUAPI  cusdMULDia_min(  unsigned long *d_RetVal, ulPMatrix MA, ui len );

overror_t  __vcuf OVCUAPI  cudaMULRows_rotate( ulPMatrix MA, ui ht, ui len, ssize_t pos );
overror_t  __vcuf OVCUAPI  cudaMULCols_rotate( ulPMatrix MA, ui ht, ui len, ssize_t pos );
overror_t  __vcuf OVCUAPI  cudaMULRows_rotate_buf( ulPMatrix MA, ui ht, ui len, ssize_t pos, ulPMatrix MBuf );
overror_t  __vcuf OVCUAPI  cudaMULCols_rotate_buf( ulPMatrix MA, ui ht, ui len, ssize_t pos, ulPMatrix MBuf );
overror_t  __vcuf OVCUAPI  cudaMULRows_reflect( ulPMatrix MA, ui ht, ui len );
overror_t  __vcuf OVCUAPI  cudaMULCols_reflect( ulPMatrix MA, ui ht, ui len );
overror_t  __vcuf OVCUAPI  cudaMULRows_rev( ulPMatrix MA, ui ht, ui len );
overror_t  __vcuf OVCUAPI  cudaMULCols_rev( ulPMatrix MA, ui ht, ui len );
overror_t  __vcuf OVCUAPI  cudaMULRows_distribution( uiPMatrix MAbund, ulVector Limits, ui nBins, ulPMatrix MX, ui ht, ui len, int mode );
overror_t  __vcuf OVCUAPI  cudaMULCols_distribution( uiPMatrix MAbund, ulVector Limits, ui nBins, ulPMatrix MX, ui ht, ui len, int mode );

/********  Operations involving two rows or two colums of one matrix  *****/

overror_t   __vcuf OVCUAPI  cudaMULRows_exchange( ulPMatrix MA, ui ht, ui len, ui i1, ui i2 );
overror_t   __vcuf OVCUAPI  cudaMULCols_exchange( ulPMatrix MA, ui ht, ui len, ui i1, ui i2 );

/****************  Transposing and rotating a matrix **********************/

overror_t  __vcuf OVCUAPI  cudaMULtranspose( ulPMatrix MTr, ulPMatrix MA, ui htTr, ui lenTr );
overror_t  __vcuf OVCUAPI  cudaMULrotate90(  ulPMatrix MRot, ulPMatrix MA, ui htRot, ui lenRot );
#define       cudaMULrotate180( MRot, MA, htRot, lenRot ) cudaVUL_rev( MRot, MA, (htRot)*(lenRot) )
overror_t  __vcuf OVCUAPI  cudaMULrotate270( ulPMatrix MRot, ulPMatrix MA, ui htRot, ui lenRot );
overror_t  __vcuf OVCUAPI  cudaMULtranspose_buf( ulPMatrix MTr, ulPMatrix MA, ui htTr, ui lenTr, ulPMatrix MBuf );

/**************************  Input and Output  **************************
	The input/output functions involve memory transfers from device
	to host memory or vice versa. The generic cudaMUL_input/output functions
	allocate their own host buffers, whereas the cudaMUL_xxx_buf functions
	take a user-supplied buffer vector h_Wk (size must be >= ht*len )
	and are much more efficient.                                       */

#define cudaMULprint( MA, ht, len )  cudaMULfprint( stdout, MA, ht, len, 80 )
overror_t __vf cudaMULfprint( FILE *stream, ulPMatrix MA, ui ht, ui len, unsigned linewidth );
overror_t __vf cudaMULcprint( ulPMatrix MA, ui ht, ui len );
#define cudaMULprint_buf( MA, ht, len, h_Wk )  cudaMULfprint_buf( stdout, MA, ht, len, 80, h_Wk )
overror_t __vf cudaMULfprint_buf( FILE *stream, ulPMatrix MA, ui ht, ui len, unsigned linewidth, ulVector h_Wk );
overror_t __vf cudaMULcprint_buf( ulPMatrix MA, ui ht, ui len, ulVector h_Wk );
overror_t __vf cudaMULwrite( FILE *stream, ulPMatrix X, ui ht, ui len  );
overror_t __vf cudaMULread( ulPMatrix X, ui ht, ui len, FILE *stream );
overror_t __vf cudaMULwrite_buf( FILE *stream, ulPMatrix X, ui ht, ui len, ulVector h_Wk );
overror_t __vf cudaMULread_buf( ulPMatrix X, ui ht, ui len, FILE *stream, ulVector h_Wk );
#define cudaMULstore( str, MA, ht, len ) cudaVUL_store( str, MA, (len)*(ht) )
#define cudaMULrecall( MA, ht, len, str) cudaVUL_recall( MA, (len)*(ht), str)
#define cudaMULstore_buf( str, MA, ht, len, h_Wk ) cudaVUL_store( str, MA, (len)*(ht), h_Wk )
#define cudaMULrecall_buf( MA, ht, len, str, h_Wk) cudaVUL_recall( MA, (len)*(ht), str, h_Wk)



/***************************************************************************
    cudaMUL_func	(working on matrices in device memory, input type liMatrix, 
	             scalar parameters reside on host and are passed by value)
    cusdMUL_func	(as cudaMUL_func except scalar parameters reside on device 
	             and are passed by address)                                 */



/***************************************************************************
 *  The following definitions are needed to access individual elements,    *
 *  and row pointers. As all addresses point to device memory, the usual   *
 *  mechanism of accessing elements, i.e., writing something like MA[m][n] *
 *  is not possible here!                                                  *
 *  Pro forma, the distinction between the data types iMatrix and         *
 *  iPMatrix is kept. However, in the present implementation, both of     *
 *  these types actually contain a pointer to the matrix element [0][0].   *
  *  For C++, inline functions ensure proper type checking at compile time, *
 *  while for plain-C, only a less safe type-cast is possible.             *
 ***************************************************************************/

#ifdef __cplusplus

inline void    cudaMUL_setElement( ulMatrix MA, ui ht, ui len, ui m, ui n, unsigned long C )
	{	cudaMULsetElement( (ulPMatrix)(MA), ht, len, m, n, C );}
inline void    cusdMUL_setElement( ulMatrix MA, ui ht, ui len, ui m, ui n, unsigned long *d_C )
	{	cusdMULsetElement( (ulPMatrix)(MA), ht, len, m, n, d_C );}
inline void    cudaMUL_getElement( unsigned long *y, ulMatrix MA, ui ht, ui len, ui m, ui n )
	{	cudaMULgetElement( y, (ulPMatrix)(MA), ht, len, m, n );}
inline void    cusdMUL_getElement( unsigned long *d_y, ulMatrix MA, ui ht, ui len, ui m, ui n )
	{	cusdMULgetElement( d_y, (ulPMatrix)(MA), ht, len, m, n );}
inline unsigned long * cudaMUL_Pelement( ulMatrix MA, ui ht, ui len, ui m, ui n )
	{	return cudaMULPelement( (ulPMatrix)(MA), ht, len, m, n );}
inline unsigned long   cudaMUL_element( ulMatrix MA, ui ht, ui len, ui m, ui n )
{	return cudaMULelement( (ulPMatrix)(MA), ht, len, m, n );}

inline overror_t  cudaMUL_equ0( ulMatrix MA, ui ht, ui len )
	{	return cudaVUL_equ0( (ulPMatrix)MA, (ht)*(len) ); }
inline overror_t  cudaMUL_equ1( ulMatrix MA, ui len )
	{	return cudaMULequ1( (ulPMatrix)(MA), len );} /* identity matrix */

inline overror_t  cudaMUL_randomLC( ulMatrix MA, ui ht, ui len, long seed, unsigned long MinVal, unsigned long MaxVal, V_RANDOMLCSTATE *h_state )
	{	return cudaVUL_randomLC( (ulPMatrix)(MA), (ht)*(len), seed, MinVal, MaxVal, h_state );}
inline overror_t  cudaMUL_random( ulMatrix MA, ui ht, ui len, long seed, unsigned long MinVal, unsigned long MaxVal )
	{	return cudaVUL_random( (ulPMatrix)(MA), (ht)*(len), seed, MinVal, MaxVal );}
inline overror_t  cusdMUL_randomLC( ulMatrix MA, ui ht, ui len, long seed, unsigned long *d_MinVal, unsigned long *d_MaxVal, V_RANDOMLCSTATE *h_state )
	{	return cusdVUL_randomLC( (ulPMatrix)(MA), (ht)*(len), seed, d_MinVal, d_MaxVal, h_state );}
inline overror_t  cusdMUL_random( ulMatrix MA, ui ht, ui len, long seed, unsigned long *d_MinVal, unsigned long *d_MaxVal )
	{	return cusdVUL_random( (ulPMatrix)(MA), (ht)*(len), seed, d_MinVal, d_MaxVal );}
inline overror_t  cudaMUL_outerprod( ulMatrix MA, ulVector X,  ulVector Y, ui ht, ui len )
{	return cudaMULouterprod( (ulPMatrix)(MA), X, Y, ht, len );}

inline overror_t  cudaMUL_Row_equ0( ulMatrix MA, ui ht, ui len, ui iRow )
	{	return cudaMULRow_equ0( (ulPMatrix)MA, ht, len, iRow );}
inline overror_t  cudaMUL_Col_equ0( ulMatrix MA, ui ht, ui len, ui iRow )
	{	return cudaMULCol_equ0( (ulPMatrix)MA, ht, len, iRow );}
inline overror_t  cudaMUL_Dia_equ0( ulMatrix MA, ui len )
	{	return cudaMULDia_equ0( (ulPMatrix)(MA), len );}

inline overror_t  cudaMUL_Row_equC( ulMatrix MA, ui ht, ui len, ui iRow, unsigned long C )
	{	return cudaMULRow_equC( (ulPMatrix)MA, ht, len, iRow, C );}
inline overror_t  cudaMUL_Col_equC( ulMatrix MA, ui ht, ui len, ui iRow, unsigned long C )
	{	return cudaMULCol_equC( (ulPMatrix)MA, ht, len, iRow, C );}
inline overror_t  cudaMUL_Dia_equC( ulMatrix MA, ui len, unsigned long C )
	{	return cudaMULDia_equC( (ulPMatrix)(MA), len, C );}

inline overror_t  cusdMUL_Row_equC( ulMatrix MA, ui ht, ui len, ui iRow, unsigned long *d_C )
	{	return cusdMULRow_equC( (ulPMatrix)MA, ht, len, iRow, d_C );}
inline overror_t  cusdMUL_Col_equC( ulMatrix MA, ui ht, ui len, ui iRow, unsigned long *d_C )
	{	return cusdMULCol_equC( (ulPMatrix)MA, ht, len, iRow, d_C );}
inline overror_t  cusdMUL_Dia_equC( ulMatrix MA, ui len, unsigned long *d_C )
	{	return cusdMULDia_equC( (ulPMatrix)(MA), len, d_C );}

inline overror_t  cudaMUL_Row_equV( ulMatrix MA, ui ht, ui len, ui iRow, ulVector X )
	{	return cudaMULRow_equV( (ulPMatrix)MA, ht, len, iRow, X );}
inline overror_t  cudaMUL_Col_equV( ulMatrix MA, ui ht, ui len, ui iRow, ulVector X )
	{	return cudaMULCol_equV( (ulPMatrix)MA, ht, len, iRow, X );}
inline overror_t  cudaMUL_Dia_equV( ulMatrix MA, ui len, ulVector X )
	{	return cudaMULDia_equV( (ulPMatrix)(MA), len, X );}

inline overror_t  cudaMUL_Trd_equM( ulMatrix MA, ulMatrix MTrd, ui len )
	{	return cudaMULTrd_equM( (ulPMatrix)(MA), (ulPMatrix)(MTrd), len );}
inline overror_t  cudaMUL_Trd_extract( ulMatrix MTrd, ulMatrix MA, ui len )
	{	return cudaMULTrd_extract( (ulPMatrix)(MTrd), (ulPMatrix)(MA), len );}

inline overror_t cudaMUL_equM( ulMatrix MB, ulMatrix MA, ui ht, ui len )
	{	return cudaVUL_equV( (ulPMatrix)MB, (ulPMatrix)MA, (ht)*(len) );}
inline overror_t cudaMUL_equMhost( ulMatrix d_MB, ulMatrix h_MA, ui ht, ui len )
	{	return cudaVUL_equVhost( (ulPMatrix)d_MB, (h_MA)[0], (ht)*(len) );}
inline overror_t MUL_equMdevice( ulMatrix h_MB, ulMatrix d_MA, ui ht, ui len )
	{	return VUL_equVdevice( h_MB[0], (ulPMatrix)d_MA, (ht)*(len) );}
inline overror_t  cudaMUL_UequL( ulMatrix MA, ui len )
	{	return cudaMULUequL( (ulPMatrix)(MA), len );}
inline overror_t  cudaMUL_LequU( ulMatrix MA, ui len )
	{	return cudaMULLequU( (ulPMatrix)(MA), len );}

/************** Data-type interconversions  ****************************/

inline overror_t cudaM_LItoUL( ulMatrix MUL, liMatrix MLI, ui ht, ui len )
	{	return cudaV_LItoUL( (ulVector)MUL, (liVector)MLI, (ht)*(len) );}
inline overror_t cudaM_UBtoUL( ulMatrix MUL, ubMatrix MUB, ui ht, ui len )
	{	return cudaV_UBtoUL( (ulVector)MUL, (ubVector)MUB, (ht)*(len) );}
inline overror_t cudaM_UStoUL( ulMatrix MUL, usMatrix MUS, ui ht, ui len )
	{	return cudaV_UStoUL( (ulVector)MUL, (usVector)MUS, (ht)*(len) );}
inline overror_t cudaM_UtoUL(  ulMatrix MUL, uMatrix MU,  ui ht, ui len )
	{	return cudaV_UtoUL(  (ulVector)MUL, (uVector)MU,   (ht)*(len) );}
#ifdef _WIN64
	inline overror_t cudaM_UQtoUL( ulMatrix MUL, uqMatrix MUQ, ui ht, ui len )
		{	return cudaV_UQtoUL( (ulVector)MUL, (uqVector)MUQ, (ht)*(len) );}
#endif
inline overror_t cudaM_ULtoF(  fMatrix MF,  ulMatrix MUL, ui ht, ui len )
	{	return cudaV_ULtoF(  (fVector)MF,   (ulVector)MUL, (ht)*(len) );}
inline overror_t cudaM_ULtoD(  dMatrix MD,  ulMatrix MUL, ui ht, ui len )
	{	return cudaV_ULtoD(  (dVector)MD,   (ulVector)MUL, (ht)*(len) );}

/********  Extracting a submatrix and copying a submatrix back  *********/

inline overror_t cudaMUL_submatrix( ulMatrix MSub, ui subHt, ui subLen, ulMatrix MSrce, ui srceHt, ui srceLen,
                      ui firstRowInCol, ui sampInCol, ui firstColInRow, ui sampInRow )
	{	return cudaMULsubmatrix(  (ulPMatrix)(MSub), subHt, subLen,
		                         (ulPMatrix)(MSrce), srceHt, srceLen,
								 firstRowInCol, sampInCol, firstColInRow, sampInRow ); }

inline overror_t cudaMUL_submatrix_equM( ulMatrix MDest, ui destHt, ui destLen,
                           ui firstRowInCol, ui sampInCol, ui firstColInRow, ui sampInRow,
                           ulMatrix MSrce, ui srceHt, ui srceLen )
	{	return cudaMULsubmatrix_equM(  (ulPMatrix)(MDest), destHt, destLen,
                             firstRowInCol, sampInCol, firstColInRow, sampInRow,
							 (ulPMatrix)(MSrce), srceHt, srceLen );}

inline overror_t cudaMUL_equMblock( ulMatrix MSub, ui subHt, ui subLen, ulMatrix MSrce, ui srceHt, ui srceLen,
                      ui firstRowInCol, ui firstColInRow )
{	return cudaMULequMblock(  (ulPMatrix)(MSub), subHt, subLen,
						   (ulPMatrix)(MSrce), srceHt, srceLen, firstRowInCol, firstColInRow );}

inline overror_t cudaMUL_block_equM( ulMatrix MDest, ui destHt, ui destLen,
                       ui firstRowInCol, ui firstColInRow,
                       ulMatrix MSrce, ui srceHt, ui srceLen )
	{	return cudaMULblock_equM( (ulPMatrix)(MDest), destHt, destLen,
                             firstRowInCol, firstColInRow,
							 (ulPMatrix)(MSrce), srceHt, srceLen );}

inline overror_t cudaMUL_equMblockT( ulMatrix MSub, ui subHt, ui subLen, ulMatrix MSrce, ui srceHt, ui srceLen,
                      ui firstRowInCol, ui firstColInRow )
	{	return cudaMULequMblockT(  (ulPMatrix)(MSub), subHt, subLen,
                             (ulPMatrix)(MSrce), srceHt, srceLen,
							 firstRowInCol, firstColInRow );}

inline overror_t cudaMUL_block_equMT( ulMatrix MDest, ui destHt, ui destLen,
                       ui firstRowInCol, ui firstColInRow,
                       ulMatrix MSrce, ui srceHt, ui srceLen )
	{	return cudaMULblock_equMT( (ulPMatrix)(MDest), destHt, destLen,
                             firstRowInCol, firstColInRow,
							 (ulPMatrix)(MSrce), srceHt, srceLen );}

/*****   Extracting a single row or a single column or the diagonal  ******
 *       and storing it into a vector                                     */

inline overror_t cudaMUL_Row_extract( ulVector Y, ulMatrix MA, ui ht, ui len, ui iRow ) 
	{	return cudaMULRow_extract( Y, (ulPMatrix)(MA), ht, len, iRow );}
inline overror_t cudaMUL_Col_extract( ulVector Y, ulMatrix MA, ui ht, ui len, ui iCol ) 
	{	return cudaMULCol_extract( Y, (ulPMatrix)(MA), ht, len, iCol );}
inline overror_t cudaMUL_Dia_extract( ulVector Y, ulMatrix MA, ui len )
	{	return cudaMULDia_extract( Y, (ulPMatrix)(MA), len );}

/**************  Deleting or inserting a row or a column   ***************/

inline overror_t cudaMUL_Row_delete( ulMatrix MB, ulMatrix MA, ui htA, ui lenA, ui iRow )
	{	return cudaMULRow_delete( (ulPMatrix)(MB), (ulPMatrix)(MA), htA, lenA, iRow );}
inline overror_t cudaMUL_Col_delete( ulMatrix MB, ulMatrix MA, ui htA, ui lenA, ui iCol )
	{	return cudaMULCol_delete( (ulPMatrix)(MB), (ulPMatrix)(MA), htA, lenA, iCol );}
inline overror_t cudaMUL_Row_insert( ulMatrix MB, ulMatrix MA, ui htB, ui lenB, ui iRow, ulVector X )
	{	return cudaMULRow_insert( (ulPMatrix)(MB), (ulPMatrix)(MA), htB, lenB, iRow, X );}
inline overror_t cudaMUL_Col_insert( ulMatrix MB, ulMatrix MA, ui htB, ui lenB, ui iCol, ulVector X )
	{	return cudaMULCol_insert( (ulPMatrix)(MB), (ulPMatrix)(MA), htB, lenB, iCol, X );}


/******  One-dimensional vector operations **********************
         performed along all rows or all columns simultaneously,
         or along the diagonal of a square matrix                */

inline overror_t cudaMUL_Rows_max( ulVector Y, ulMatrix MA, ui ht, ui len )
	{	return cudaMULRows_max( Y, (ulPMatrix)(MA), ht, len );}
inline overror_t cudaMUL_Cols_max( ulVector Y, ulMatrix MA, ui ht, ui len )
	{	return cudaMULCols_max( Y, (ulPMatrix)(MA), ht, len );}
inline overror_t cudaMUL_Dia_max(  unsigned long *h_RetValPtr, ulMatrix MA, ui len )
	{	return cudaMULDia_max(  h_RetValPtr, (ulPMatrix)(MA), len );}
inline overror_t cusdMUL_Dia_max(  unsigned long *d_RetValPtr, ulMatrix MA, ui len )
	{	return cusdMULDia_max(  d_RetValPtr, (ulPMatrix)(MA), len );}
inline overror_t cudaMUL_Rows_min( ulVector Y, ulMatrix MA, ui ht, ui len )
	{	return cudaMULRows_min( Y, (ulPMatrix)(MA), ht, len );}
inline overror_t cudaMUL_Cols_min( ulVector Y, ulMatrix MA, ui ht, ui len )
	{	return cudaMULCols_min( Y, (ulPMatrix)(MA), ht, len );}
inline overror_t cudaMUL_Dia_min(  unsigned long *h_RetValPtr, ulMatrix MA, ui len )
	{	return cudaMULDia_min(  h_RetValPtr, (ulPMatrix)(MA), len );}
inline overror_t cusdMUL_Dia_min(  unsigned long *d_RetValPtr, ulMatrix MA, ui len )
	{	return cusdMULDia_min(  d_RetValPtr, (ulPMatrix)(MA), len );}

inline overror_t cudaMUL_Rows_rotate( ulMatrix MA, ui ht, ui len, ssize_t pos)
	{	return cudaMULRows_rotate( (ulPMatrix)(MA), ht, len, pos );}
inline overror_t cudaMUL_Cols_rotate( ulMatrix MA, ui ht, ui len, ssize_t pos)
	{	return cudaMULCols_rotate( (ulPMatrix)(MA), ht, len, pos );}
inline overror_t cudaMUL_Rows_rotate_buf( ulMatrix MA, ui ht, ui len, ssize_t pos, ulMatrix MBuf) 
	{	return cudaMULRows_rotate_buf( (ulPMatrix)(MA), ht, len, pos, (ulPMatrix)(MBuf) );}
inline overror_t cudaMUL_Cols_rotate_buf( ulMatrix MA, ui ht, ui len, ssize_t pos, ulMatrix MBuf) 
	{	return cudaMULCols_rotate_buf( (ulPMatrix)(MA), ht, len, pos, (ulPMatrix)(MBuf) );}
inline overror_t cudaMUL_Rows_reflect( ulMatrix MA, ui ht, ui len )
	{	return cudaMULRows_reflect( (ulPMatrix)(MA), ht, len );}
inline overror_t cudaMUL_Cols_reflect( ulMatrix MA, ui ht, ui len )
	{	return cudaMULCols_reflect( (ulPMatrix)(MA), ht, len );}
inline overror_t cudaMUL_Rows_rev( ulMatrix MA, ui ht, ui len )
	{	return cudaMULRows_rev( (ulPMatrix)(MA), ht, len );}
inline overror_t cudaMUL_Cols_rev( ulMatrix MA, ui ht, ui len )
	{	return cudaMULCols_rev( (ulPMatrix)(MA), ht, len );}
inline overror_t  cudaMUL_Rows_distribution( uiMatrix MAbund, ulVector Limits, ui nBins, ulMatrix MX, ui ht, ui len, int mode )
	{	return cudaMULRows_distribution( (uiPMatrix)MAbund, Limits, nBins, (ulPMatrix)MX, ht, len, mode ); }
inline overror_t  cudaMUL_Cols_distribution( uiMatrix MAbund, ulVector Limits, ui nBins, ulMatrix MX, ui ht, ui len, int mode )
	{	return cudaMULCols_distribution( (uiPMatrix)MAbund, Limits, nBins, (ulPMatrix)MX, ht, len, mode ); }

/********  Operations involving two rows or two colums of one matrix  *****/

inline overror_t cudaMUL_Rows_exchange( ulMatrix MA, ui ht, ui len, ui row1, ui row2 )
	{	return cudaMULRows_exchange( (ulPMatrix)(MA), ht, len, row1, row2 );}
inline overror_t cudaMUL_Cols_exchange( ulMatrix MA, ui ht, ui len, ui col1, ui col2 )
	{	return cudaMULCols_exchange( (ulPMatrix)(MA), ht, len, col1, col2 );}

/*************** Transposing and rotating a matrix **********************/

inline overror_t cudaMUL_transpose( ulMatrix MTr, ulMatrix MA, ui htTr, ui lenTr )
	{	return cudaMULtranspose( (ulPMatrix)(MTr), (ulPMatrix)(MA), htTr, lenTr );}
       /*  dimensions htTr, lenTr are those of the transposed matrix, not of the original!   */
inline overror_t cudaMUL_rotate90( ulMatrix MRot, ulMatrix MA, ui htRot, ui lenRot )
	{	return cudaMULrotate90( (ulPMatrix)(MRot), (ulPMatrix)(MA), htRot, lenRot );}
inline overror_t cudaMUL_rotate180( ulMatrix MRot, ulMatrix MA, ui htRot, ui lenRot )
	{	return cudaVUL_rev( (ulPMatrix)(MRot), (ulPMatrix)(MA), (htRot)*(lenRot) );}
inline overror_t cudaMUL_rotate270( ulMatrix MRot, ulMatrix MA, ui htRot, ui lenRot )
	{	return cudaMULrotate270( (ulPMatrix)(MRot), (ulPMatrix)(MA), htRot, lenRot );}
inline overror_t cudaMUL_transpose_buf( ulMatrix MTr, ulMatrix MA, ui htTr, ui lenTr, ulMatrix MBuf )
	{	return cudaMULtranspose_buf( (ulPMatrix)(MTr), (ulPMatrix)(MA), htTr, lenTr, (ulPMatrix)(MBuf) );}

/**************************  Input and Output  **************************
	The input/output functions involve memory transfers from device
	to host memory or vice versa. The generic cudaMUL_input/output functions
	allocate their own host buffers, whereas the cudaMUL_xxx_buf functions
	take a user-supplied buffer vector h_Wk (size must be >= ht*len )
	and are much more efficient.                                       */

inline overror_t cudaMUL_fprint( FILE *stream, ulMatrix MA, ui ht, ui len, unsigned linewidth )
	{	return cudaMULfprint( stream, (ulPMatrix)(MA), ht, len, linewidth ); }
inline overror_t cudaMUL_print( ulMatrix MA, ui ht, ui len )
	{	return cudaMULfprint( stdout, (ulPMatrix)(MA), ht, len, 80 ); }
inline overror_t cudaMUL_cprint( ulMatrix MA, ui ht, ui len )
	{	return cudaMULcprint( (ulPMatrix)(MA), ht, len ); }
inline overror_t cudaMUL_fprint_buf( FILE *stream, ulMatrix d_MA, ui ht, ui len, unsigned linewidth, ulVector h_Wk )
	{	return cudaMULfprint_buf( stream, (ulPMatrix)(d_MA), ht, len, linewidth, h_Wk ); }
inline overror_t cudaMUL_print_buf( ulMatrix d_MA, ui ht, ui len, ulVector h_Wk )
	{	return cudaMULfprint_buf( stdout, (ulPMatrix)(d_MA), ht, len, 80, h_Wk ); }
inline overror_t cudaMUL_cprint_buf( ulMatrix d_MA, ui ht, ui len, ulVector h_Wk )
	{	return cudaMULcprint_buf( (ulPMatrix)(d_MA), ht, len, h_Wk ); }
		/*  cudaMUL_print, cudaMUL_cprint usable only for console applications! */
inline overror_t  cudaMUL_write( FILE *stream, ulMatrix MA, ui ht, ui len )
	{	return cudaMULwrite( stream, (ulPMatrix)(MA), ht, len ); }
inline overror_t cudaMUL_read( ulMatrix MA, ui ht, ui len, FILE *stream )
	{	return cudaMULread( (ulPMatrix)(MA), ht, len, stream ); }
inline overror_t  cudaMUL_write_buf( FILE *stream, ulMatrix d_MA, ui ht, ui len, ulVector h_Wk )
	{	return cudaMULwrite_buf( stream, (ulPMatrix)(d_MA), ht, len, h_Wk ); }
inline overror_t cudaMUL_read_buf( ulMatrix d_MA, ui ht, ui len, FILE *stream, ulVector h_Wk )
	{	return cudaMULread_buf( (ulPMatrix)(d_MA), ht, len, stream, h_Wk ); }
                                   /* write and read in ascii format */
inline overror_t cudaMUL_store( FILE *stream, ulMatrix MA, ui ht, ui len )
{	return cudaVUL_store( stream, (ulPMatrix)(MA), (len)*(ht) ); }
inline overror_t cudaMUL_recall( ulMatrix MA, ui ht, ui len, FILE *stream )
	{	return cudaVUL_recall( (ulPMatrix)(MA), (len)*(ht), stream ); }
inline overror_t cudaMUL_store_buf( FILE *stream, ulMatrix d_MA, ui ht, ui len, ulVector h_Wk )
{	return cudaVUL_store_buf( stream, (ulPMatrix)(d_MA), (len)*(ht), h_Wk ); }
inline overror_t cudaMUL_recall_buf( ulMatrix d_MA, ui ht, ui len, FILE *stream, ulVector h_Wk )
	{	return cudaVUL_recall_buf( (ulPMatrix)(d_MA), (len)*(ht), stream, h_Wk ); }
                                  /* store and recall in binary format */

#else  /* plain-C, not C++: type-cast used to transform ulMatrix into ulPMatrix */


/***  Addressing single elements of dynamically allocated matrices: ******/

#define cudaMUL_setElement( MA, ht, len, m, n, C ) cudaMULsetElement( (ulPMatrix)(MA), ht, len, m, n, C )
#define cusdMUL_setElement( MA, ht, len, m, n, C ) cusdMULsetElement( (ulPMatrix)(MA), ht, len, m, n, C )
#define cudaMUL_getElement( y, MA, ht, len, m, n ) cudaMULgetElement( y, (ulPMatrix)(MA), ht, len, m, n )
#define cusdMUL_getElement( y, MA, ht, len, m, n ) cusdMULgetElement( y, (ulPMatrix)(MA), ht, len, m, n )
#define cudaMUL_Pelement( MA, ht, len, m, n )      cudaMULPelement( (ulPMatrix)(MA), ht, len, m, n )
#define cudaMUL_element(  MA, ht, len, m, n )      cudaMULelement( (ulPMatrix)(MA), ht, len, m, n )

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
        cudaVUL_equ1( (ulVector)MA, ht * len );
*/

#define cudaMUL_equ0( MA, ht, len )            cudaVUL_equ0( (ulPMatrix)(MA), (ht)*(len) )
#define cudaMUL_equ1( MA, len )                cudaMULequ1( (ulPMatrix)(MA), len ) /* identity matrix */
#define cudaMUL_randomLC( MA, ht, len, seed, Min, Max, h_state )      cudaVUL_randomLC( MA, (ht)*(len), seed, Min, Max, h_state )
#define cudaMUL_random( MA, ht, len, seed, Min, Max )                 cudaVUL_random( MA, (ht)*(len), seed, Min, Max )
#define cusdMUL_randomLC( MA, ht, len, seed, d_Min, d_Max, h_state )  cudaVUL_randomLC( MA, (ht)*(len), seed, d_Min, d_Max, h_state )
#define cusdMUL_random( MA, ht, len, seed, d_Min, d_Max )             cudaVUL_random( MA, (ht)*(len), seed, d_Min, d_Max )
#define cudaMUL_outerprod( MA, X, Y, ht, len ) cudaMULouterprod( (ulPMatrix)(MA), X, Y, ht, len )
                       /* sizX=ht, sizY=len */
#define cudaMUL_Row_equ0( MA, ht, len, iRow )    cudaMULRow_equ0( (ulPMatrix)(MA), ht, len, iRow )
#define cudaMUL_Col_equ0( MA, ht, len, iCol )    cudaMULCol_equ0( (ulPMatrix)(MA), ht, len, iCol )
#define cudaMUL_Dia_equ0( MA, len )              cudaMULDia_equ0( (ulPMatrix)(MA), len )
#define cudaMUL_Row_equC( MA, ht, len, iRow, C ) cudaMULRow_equC( (ulPMatrix)(MA), ht, len, iRow, C )
#define cudaMUL_Col_equC( MA, ht, len, iCol, C ) cudaMULCol_equC( (ulPMatrix)(MA), ht, len, iCol, C )
#define cudaMUL_Dia_equC( MA, len, C )           cudaMULDia_equC( (ulPMatrix)(MA), len, C )
#define cusdMUL_Row_equC( MA, ht, len, iRow, d_C ) cusdMULRow_equC( (ulPMatrix)(MA), ht, len, iRow, d_C )
#define cusdMUL_Col_equC( MA, ht, len, iCol, d_C ) cusdMULCol_equC( (ulPMatrix)(MA), ht, len, iCol, d_C )
#define cusdMUL_Dia_equC( MA, len, d_C )           cusdMULDia_equC( (ulPMatrix)(MA), len, d_C )

#define cudaMUL_Row_equV( MA, ht, len, iRow, X ) cudaMULRow_equV( (ulPMatrix)(MA), ht, len, iRow, X )
#define cudaMUL_Col_equV( MA, ht, len, iCol, X ) cudaMULCol_equV( (ulPMatrix)(MA), ht, len, iCol, X )
#define cudaMUL_Dia_equV( MA, len, X )           cudaMULDia_equV( (ulPMatrix)(MA), len, X )

#define cudaMUL_Trd_equM( MA, MTrd, len )    cudaMULTrd_equM( (ulPMatrix)(MA), (ulPMatrix)(MTr)d, len )
#define cudaMUL_Trd_extract( MTrd, MA, len ) cudaMULTrd_extract( (ulPMatrix)(MTr)d, (ulPMatrix)(MA), len )

#define cudaMUL_equM( MB, MA, ht, len )      cudaVUL_equV( (ulPMatrix)(MB), (ulPMatrix)(MA), (ht)*(len) )
#define cudaMUL_equMhost( MB, MA, ht, len )  cudaVUL_equVhost( (ulPMatrix)(MB), MA[0], (ht)*(len) )
#define MUL_equMdevice( MB, MA, ht, len )    VUL_equVdevice( MB[0], (ulPMatrix)(MA), (ht)*(len) )

#define cudaMUL_UequL( MA, len ) cudaMULUequL( (ulPMatrix)(MA), len )
#define cudaMUL_LequU( MA, len ) cudaMULLequU( (ulPMatrix)(MA), len )

/************** Data-type interconversions  ****************************/

#define cudaM_LItoUL( MUL, MLI, ht, len ) cudaV_LItoUL( (ulVector)(MUL), (liVector)(MLI), (ht)*(len) )
#define cudaM_ULtoLI( MLI, MUL, ht, len ) cudaV_ULtoLI( (liVector)(MLI), (ulVector)(MUL), (ht)*(len) )
#define cudaM_ULtoUB( MUB, MUL, ht, len ) cudaV_ULtoUB( (ubVector)(MUB), (ulVector)(MUL), (ht)*(len) )
#define cudaM_ULtoUS( MUS, MUL, ht, len ) cudaV_ULtoUS( (usVector)(MUS), (ulVector)(MUL), (ht)*(len) )
#define cudaM_ULtoU(  MU,  MUL, ht, len ) cudaV_ULtoU(  (uVector)(MU),   (ulVector)(MUL), (ht)*(len) )
#define cudaM_UBtoUL( MUL, MUB, ht, len ) cudaV_UBtoUL( (ulVector)(MUL), (ubVector)(MUB), (ht)*(len) )
#define cudaM_UStoUL( MUL, MUS, ht, len ) cudaV_UStoUL( (ulVector)(MUL), (usVector)(MUS), (ht)*(len) )
#define cudaM_UtoUL(  MUL, MU,  ht, len ) cudaV_UtoUL(  (ulVector)(MUL), (uVector)(MU),   (ht)*(len) )
#ifdef _WIN64
	#define cudaM_ULtoUQ( MUQ, MUL, ht, len ) cudaV_ULtoUQ( (uqVector)(MUQ), (ulVector)(MUL), (ht)*(len) )
	#define cudaM_UQtoUL( MUL, MUQ, ht, len ) cudaV_UQtoUL( (ulVector)(MUL), (uqVector)(MUQ), (ht)*(len) )
#endif
#define cudaM_ULtoF(  MF,  MUL, ht, len ) cudaV_ULtoF(  (fVector)(MF),   (ulVector)(MUL), (ht)*(len) )
#define cudaM_ULtoD(  MD,  MUL, ht, len ) cudaV_ULtoD(  (dVector)(MD),   (ulVector)(MUL), (ht)*(len) )


/********  Extracting a submatrix and copying a submatrix back  *********/

#define cudaMUL_submatrix( MSub, subHt, subLen, MSrce, srceHt, srceLen, \
                      firstRowInCol, sampInCol, firstColInRow, sampInRow ) \
               cudaMULsubmatrix(  (ulPMatrix)(MSub), subHt, subLen, \
                             (ulPMatrix)(MSrce), srceHt, srceLen, \
                             firstRowInCol, sampInCol, firstColInRow, sampInRow )

#define cudaMUL_submatrix_equM( MDest, destHt, destLen, \
                           firstRowInCol, sampInCol, firstColInRow, sampInRow, \
                           MSrce, srceHt, srceLen ) \
               cudaMULsubmatrix_equM(  (ulPMatrix)(MDest), destHt, destLen, \
                             firstRowInCol, sampInCol, firstColInRow, sampInRow, \
                             (ulPMatrix)(MSrce), srceHt, srceLen )

#define cudaMUL_equMblock( MSub, subHt, subLen, MSrce, srceHt, srceLen, \
                      firstRowInCol, firstColInRow ) \
               cudaMULequMblock(  (ulPMatrix)(MSub), subHt, subLen, \
                             (ulPMatrix)(MSrce), srceHt, srceLen, \
                             firstRowInCol, firstColInRow )

#define cudaMUL_block_equM( MDest, destHt, destLen, \
                       firstRowInCol, firstColInRow, \
                       MSrce, srceHt, srceLen ) \
               cudaMULblock_equM( (ulPMatrix)(MDest), destHt, destLen, \
                             firstRowInCol, firstColInRow, \
                             (ulPMatrix)(MSrce), srceHt, srceLen )

#define cudaMUL_equMblockT( MSub, subHt, subLen, \
                      MSrce, srceHt, srceLen, \
                      firstRowInCol, firstColInRow ) \
               cudaMULequMblockT(  (ulPMatrix)(MSub), subHt, subLen, \
                             (ulPMatrix)(MSrce), srceHt, srceLen, \
                             firstRowInCol, firstColInRow )

#define cudaMUL_block_equMT( MDest, destHt, destLen, \
                       firstRowInCol, firstColInRow, \
                       MSrce, srceHt, srceLen ) \
               cudaMULblock_equMT( (ulPMatrix)(MDest), destHt, destLen, \
                             firstRowInCol, firstColInRow, \
                             (ulPMatrix)(MSrce), srceHt, srceLen )

/*****   Extracting a single row or a single column or the diagonal  ******
 *       and storing it into a vector                                     */

#define cudaMUL_Row_extract( Y, MA, ht, len, iRow ) cudaMULRow_extract( Y, (ulPMatrix)(MA), ht, len, iRow )
#define cudaMUL_Col_extract( Y, MA, ht, len, iCol ) cudaMULCol_extract( Y, (ulPMatrix)(MA), ht, len, iCol )
#define cudaMUL_Dia_extract( Y, MA, len )           cudaMULDia_extract( Y, (ulPMatrix)(MA), len )


/**************  Deleting or inserting a row or a column   ***************/

#define cudaMUL_Row_delete( MB, MA, htA, lenA, iRow ) cudaMULRow_delete( (ulPMatrix)(MB), (ulPMatrix)(MA), htA, lenA, iRow )
#define cudaMUL_Col_delete( MB, MA, htA, lenA, iCol ) cudaMULCol_delete( (ulPMatrix)(MB), (ulPMatrix)(MA), htA, lenA, iCol )
#define cudaMUL_Row_insert( MB, MA, htB, lenB, iRow, X ) cudaMULRow_insert( (ulPMatrix)(MB), (ulPMatrix)(MA), htB, lenB, iRow, X )
#define cudaMUL_Col_insert( MB, MA, htB, lenB, iCol, X ) cudaMULCol_insert( (ulPMatrix)(MB), (ulPMatrix)(MA), htB, lenB, iCol, X )

/******  One-dimensional vector operations **********************
         performed along all rows or all columns simultaneously,
         or along the diagonal of a square matrix                */

#define cudaMUL_Rows_max( Y, MA, ht, len )     cudaMULRows_max( Y, (ulPMatrix)(MA), ht, len )
#define cudaMUL_Cols_max( Y, MA, ht, len )     cudaMULCols_max( Y, (ulPMatrix)(MA), ht, len )
#define cudaMUL_Dia_max(  h_RetPtr, MA, len )  cudaMULDia_max( h_RetPtr, (ulPMatrix)(MA), len )
#define cusdMUL_Dia_max(  d_RetPtr, MA, len )  cusdMULDia_max( d_RetPtr, (ulPMatrix)(MA), len )
#define cudaMUL_Rows_min( Y, MA, ht, len )     cudaMULRows_min( Y, (ulPMatrix)(MA), ht, len )
#define cudaMUL_Cols_min( Y, MA, ht, len )     cudaMULCols_min( Y, (ulPMatrix)(MA), ht, len )
#define cudaMUL_Dia_min(  h_RetPtr, MA, len )  cudaMULDia_min( h_RetPtr, (ulPMatrix)(MA), len )
#define cusdMUL_Dia_min(  d_RetPtr, MA, len )  cusdMULDia_min( d_RetPtr, (ulPMatrix)(MA), len )

#define cudaMUL_Rows_rotate( MA, ht, len, pos) cudaMULRows_rotate( (ulPMatrix)(MA), ht, len, pos )
#define cudaMUL_Cols_rotate( MA, ht, len, pos) cudaMULCols_rotate( (ulPMatrix)(MA), ht, len, pos )
#define cudaMUL_Rows_rotate_buf( MA, ht, len, pos, MBuf) cudaMULRows_rotate_buf( (ulPMatrix)(MA), ht, len, pos, (ulPMatrix)(MBuf) )
#define cudaMUL_Cols_rotate_buf( MA, ht, len, pos, MBuf) cudaMULCols_rotate_buf( (ulPMatrix)(MA), ht, len, pos, (ulPMatrix)(MBuf) )
#define cudaMUL_Rows_reflect( MA, ht, len)     cudaMULRows_reflect( (ulPMatrix)(MA), ht, len )
#define cudaMUL_Cols_reflect( MA, ht, len)     cudaMULCols_reflect( (ulPMatrix)(MA), ht, len )
#define cudaMUL_Rows_rev( MA, ht, len)         cudaMULRows_rev( (ulPMatrix)(MA), ht, len )
#define cudaMUL_Cols_rev( MA, ht, len)         cudaMULCols_rev( (ulPMatrix)(MA), ht, len )
#define cudaMUL_Rows_distribution( MAbund, Limits, nBins, MX, ht, len, mode ) cudaMULRows_distribution( (uiPMatrix)MAbund, Limits, nBins, (ulPMatrix)MX, ht, len, mode )
#define cudaMUL_Cols_distribution( MAbund, Limits, nBins, MX, ht, len, mode ) cudaMULCols_distribution( (uiPMatrix)MAbund, Limits, nBins, (ulPMatrix)MX, ht, len, mode )

/********  Operations involving two rows or two colums of one matrix  *****/

#define cudaMUL_Rows_exchange( MA, ht, len, row1, row2 ) cudaMULRows_exchange( (ulPMatrix)(MA), ht, len, row1, row2 )
#define cudaMUL_Cols_exchange( MA, ht, len, col1, col2 ) cudaMULCols_exchange( (ulPMatrix)(MA), ht, len, col1, col2 )

/****************  Transposing and rotating a matrix **********************/

#define cudaMUL_transpose( MTr, MA, htTr, lenTr ) cudaMULtranspose( (ulPMatrix)(MTr), (ulPMatrix)(MA), htTr, lenTr )
       /*  dimensions htTr, lenTr are those of the transposed matrix,
           not of the original!                */
#define cudaMUL_rotate90( MRot, MA, htRot, lenRot )  cudaMULrotate90( (ulPMatrix)(MRot), (ulPMatrix)(MA), htRot, lenRot )
#define cudaMUL_rotate180( MRot, MA, htRot, lenRot ) cudaVUL_rev( (ulPMatrix)(MRot), (ulPMatrix)(MA), (htRot)*(lenRot) )
#define cudaMUL_rotate270( MRot, MA, htRot, lenRot ) cudaMULrotate270( (ulPMatrix)(MRot), (ulPMatrix)(MA), htRot, lenRot )
#define cudaMUL_transpose_buf( MTr, MA, htTr, lenTr, MBuf ) cudaMULtranspose_buf( (ulPMatrix)(MTr), (ulPMatrix)(MA), htTr, lenTr, (ulPMatrix)(MBuf) )

/**************************  Input and Output  **************************
	The input/output functions involve memory transfers from device
	to host memory or vice versa. The generic cudaMUL_input/output functions
	allocate their own host buffers, whereas the cudaMUL_xxx_buf functions
	take a user-supplied buffer vector h_Wk (size must be >= ht*len )
	and are much more efficient.                                       */

#define cudaMUL_fprint( stream, MA, ht, len, linewidth ) \
                    cudaMULfprint( stream, (ulPMatrix)(MA), ht, len, linewidth )
#define cudaMUL_print( MA, ht, len )  cudaMULfprint( stdout, (ulPMatrix)(MA), ht, len, 80 )
#define cudaMUL_cprint( MA, ht, len ) cudaMULcprint( (ulPMatrix)(MA), ht, len )
#define cudaMUL_fprint_buf( stream, MA, ht, len, linewidth, h_Wk ) \
                    cudaMULfprint_buf( stream, (ulPMatrix)(MA), ht, len, linewidth, h_Wk )
#define cudaMUL_print_buf( MA, ht, len )  cudaMULfprint_buf( stdout, (ulPMatrix)(MA), ht, len, 80, h_Wk )
#define cudaMUL_cprint_buf( MA, ht, len ) cudaMULcprint_buf( (ulPMatrix)(MA), ht, len, h_Wk )
  /*  cudaMUL_print, cudaMUL_cprint usable only for console applications! */
#define cudaMUL_write( str, MA, ht, len )   cudaMULwrite( str, (ulPMatrix)(MA), ht, len )
#define cudaMUL_read( MA, ht, len, str )    cudaMULread( (ulPMatrix)(MA), ht, len, str )
#define cudaMUL_write_buf( str, MA, ht, len, h_Wk )   cudaMULwrite_buf( str, (ulPMatrix)(MA), ht, len, h_Wk )
#define cudaMUL_read_buf( MA, ht, len, str, h_Wk )    cudaMULread_buf( (ulPMatrix)(MA), ht, len, str, h_Wk )
                                   /* write and read in ascii format */
#define cudaMUL_store( str, MA, ht, len )   cudaVUL_store( str, (ulPMatrix)(MA), (len)*(ht) )
#define cudaMUL_recall( MA, ht, len, str)   cudaVUL_recall( (ulPMatrix)(MA), (len)*(ht), str)
#define cudaMUL_store_buf( str, MA, ht, len, h_Wk )   cudaVUL_store_buf( str, (ulPMatrix)(MA), (len)*(ht), h_Wk )
#define cudaMUL_recall_buf( MA, ht, len, str, h_Wk)   cudaVUL_recall_buf( (ulPMatrix)(MA), (len)*(ht), str, h_Wk )
                                  /* store and recall in binary format */

#endif /* plain-C or C++ for functions working on device memory */


/*******************  Functions working on host memory: **********************
 *                                                                           *
 *	MLIcu_func		(working on matrices in host memory, input type liMatrix,*
 *	scalar parameters on host and passed by value)                           *
 *****************************************************************************/ 

/****************  Initialization  ****************************************/

#define MULcu_equ0( MA, ht, len )                   VULcu_equ0( (MA)[0], (ht)*(len) )
#define MULcu_equ1( MA, len )                       MULcuequ1( (MA)[0], len ) /* identity matrix */
#define MULcu_randomLC( MA, ht, len, seed, Min, Max, state ) VULcu_randomLC( (MA)[0], (ht)*(len), seed, Min, Max, state )
#define MULcu_random( MA, ht, len, seed, Min, Max )          VULcu_random( (MA)[0], (ht)*(len), seed, Min, Max )
#define MULcu_outerprod( MA, X, Y, ht, len )        MULcuouterprod( (MA)[0], X, Y, ht, len )
                       /* sizX=ht, sizY=len */
#define MULcu_Row_equ0( MA, ht, len, iRow )    MULcuRow_equ0( (MA)[0], ht, len, iRow )
#define MULcu_Col_equ0( MA, ht, len, iCol )    MULcuCol_equ0( (MA)[0], ht, len, iCol )
#define MULcu_Dia_equ0( MA, len )              MULcuDia_equ0( (MA)[0], len )
#define MULcu_Row_equC( MA, ht, len, iRow, C ) MULcuRow_equC( (MA)[0], ht, len, iRow, C )
#define MULcu_Col_equC( MA, ht, len, iCol, C ) MULcuCol_equC( (MA)[0], ht, len, iCol, C )
#define MULcu_Dia_equC( MA, len, C )           MULcuDia_equC( (MA)[0], len, C )

#define MULcu_Row_equV( MA, ht, len, iRow, X ) MULcuRow_equV( (MA)[0], ht, len, iRow, X )
#define MULcu_Col_equV( MA, ht, len, iCol, X ) MULcuCol_equV( (MA)[0], ht, len, iCol, X )
#define MULcu_Dia_equV( MA, len, X )           MULcuDia_equV( (MA)[0], len, X )

#define MULcu_Trd_equM( MA, MTrd, len )        MULcuTrd_equM( (MA)[0], (MTrd)[0], len )
#define MULcu_Trd_extract( MTrd, MA, len )     MULcuTrd_extract( (MTrd)[0], (MA)[0], len )

#define MULcu_equM( MB, MA, ht, len )          VULcu_equV( (MB)[0], (MA)[0], (ht)*(len) )
#define MULcu_equMhost( MB, MA, ht, len )      VULcu_equVhost( (MB)[0], MA[0], (ht)*(len) )

#define MULcu_UequL( MA, len ) MULcuUequL( (MA)[0], len )
#define MULcu_LequU( MA, len ) MULcuLequU( (MA)[0], len )
     /* copy lower-diagonal elements into upper-diagonal
       (or vice versa) by index-reflection, so as to get a symmetric matrix    */

            /* data-type conversions:  */
#define Mcu_LItoUL( MUL, MLI, ht, len ) Vcu_LItoUL( (MUL)[0], (MLI)[0], (ht)*(len) )
#define Mcu_ULtoLI( MLI, MUL, ht, len ) Vcu_ULtoLI( (MLI)[0], (MUL)[0], (ht)*(len) )
#define Mcu_ULtoUB( MUB, MUL, ht, len ) Vcu_ULtoUB( (MUB)[0], (MUL)[0], (ht)*(len) )
#define Mcu_ULtoUS( MUS, MUL, ht, len ) Vcu_ULtoUS( (MUS)[0], (MUL)[0], (ht)*(len) )
#define Mcu_ULtoU(  MU,  MUL, ht, len ) Vcu_ULtoU(  (MU)[0],  (MUL)[0], (ht)*(len) )
#define Mcu_UBtoUL( MUL, MUB, ht, len ) Vcu_UBtoUL( (MUL)[0], (MUB)[0], (ht)*(len) )
#define Mcu_UtoUL(  MUL, MU,  ht, len ) Vcu_UtoUL(  (MUL)[0], (MU)[0],  (ht)*(len) )
#define Mcu_UStoUL( MUL, MUS, ht, len ) Vcu_UStoUL( (MUL)[0], (MUS)[0], (ht)*(len) )
#ifdef _WIN64
	#define Mcu_ULtoUQ( MUQ, MUL, ht, len ) Vcu_ULtoUQ( (MUQ)[0], (MUL)[0], (ht)*(len) )
	#define Mcu_UQtoUL( MUL, MUQ, ht, len ) Vcu_UQtoUL( (MUL)[0], (MUQ)[0], (ht)*(len) )
#endif
#define Mcu_ULtoF(  MF,  MUL, ht, len ) Vcu_ULtoF(  (MF)[0],  (MUL)[0], (ht)*(len) )
#define Mcu_ULtoD(  MD,  MUL, ht, len ) Vcu_ULtoD(  (MD)[0],  (MUL)[0], (ht)*(len) )


/********  Extracting a submatrix and copying a submatrix back  *********/

#define MULcu_submatrix( MSub, subHt, subLen, MSrce, srceHt, srceLen, \
                      firstRowInCol, sampInCol, firstColInRow, sampInRow ) \
               MULcusubmatrix(  (MSub)[0], subHt, subLen, \
                             (MSrce)[0], srceHt, srceLen, \
                             firstRowInCol, sampInCol, firstColInRow, sampInRow )

#define MULcu_submatrix_equM( MDest, destHt, destLen, \
                           firstRowInCol, sampInCol, firstColInRow, sampInRow, \
                           MSrce, srceHt, srceLen ) \
               MULcusubmatrix_equM(  (MDest)[0], destHt, destLen, \
                             firstRowInCol, sampInCol, firstColInRow, sampInRow, \
                             (MSrce)[0], srceHt, srceLen )

#define MULcu_equMblock( MSub, subHt, subLen, MSrce, srceHt, srceLen, \
                      firstRowInCol, firstColInRow ) \
               MULcuequMblock(  (MSub)[0], subHt, subLen, \
                             (MSrce)[0], srceHt, srceLen, \
                             firstRowInCol, firstColInRow )

#define MULcu_block_equM( MDest, destHt, destLen, \
                       firstRowInCol, firstColInRow, \
                       MSrce, srceHt, srceLen ) \
               MULcublock_equM( (MDest)[0], destHt, destLen, \
                             firstRowInCol, firstColInRow, \
                             (MSrce)[0], srceHt, srceLen )

#define MULcu_equMblockT( MSub, subHt, subLen, MSrce, srceHt, srceLen, \
                      firstRowInCol, firstColInRow ) \
               MULcuequMblockT(  (MSub)[0], subHt, subLen, \
                             (MSrce)[0], srceHt, srceLen, \
                             firstRowInCol, firstColInRow )

#define MULcu_block_equMT( MDest, destHt, destLen, \
                       firstRowInCol, firstColInRow, \
                       MSrce, srceHt, srceLen ) \
               MULcublock_equMT( (MDest)[0], destHt, destLen, \
                             firstRowInCol, firstColInRow, \
                             (MSrce)[0], srceHt, srceLen )

/*****   Extracting a single row or a single column or the diagonal  ******
 *       and storing it into a vector                                     */

#define MULcu_Row_extract( Y, MA, ht, len, iRow ) MULcuRow_extract( Y, (MA)[0], ht, len, iRow )
#define MULcu_Col_extract( Y, MA, ht, len, iCol ) MULcuCol_extract( Y, (MA)[0], ht, len, iCol )
#define MULcu_Dia_extract( Y, MA, len )           MULcuDia_extract( Y, (MA)[0], len )

/**************  Deleting or inserting a row or a column   ***************/

#define MULcu_Row_delete( MB, MA, htA, lenA, iRow )    MULcuRow_delete( (MB)[0], (MA)[0], htA, lenA, iRow )
#define MULcu_Col_delete( MB, MA, htA, lenA, iCol )    MULcuCol_delete( (MB)[0], (MA)[0], htA, lenA, iCol )
#define MULcu_Row_insert( MB, MA, htB, lenB, iRow, X ) MULcuRow_insert( (MB)[0], (MA)[0], htB, lenB, iRow, X )
#define MULcu_Col_insert( MB, MA, htB, lenB, iCol, X ) MULcuCol_insert( (MB)[0], (MA)[0], htB, lenB, iCol, X )


/******  One-dimensional vector operations **********************
         performed along all rows or all columns simultaneously,
         or along the diagonal of a square matrix                */

#define MULcu_Rows_max( Y, MA, ht, len )        MULcuRows_max( Y, (MA)[0], ht, len )
#define MULcu_Cols_max( Y, MA, ht, len )        MULcuCols_max( Y, (MA)[0], ht, len )
#define MULcu_Dia_max(  MA, len )               MULcuDia_max(  (MA)[0], len )
#define MULcu_Rows_min( Y, MA, ht, len )        MULcuRows_min( Y, (MA)[0], ht, len )
#define MULcu_Cols_min( Y, MA, ht, len )        MULcuCols_min( Y, (MA)[0], ht, len )
#define MULcu_Dia_min(  MA, len )               MULcuDia_min(  (MA)[0], len )

#define MULcu_Rows_rotate( MA, ht, len, pos)           MULcuRows_rotate( (MA)[0], ht, len, pos )
#define MULcu_Cols_rotate( MA, ht, len, pos)           MULcuCols_rotate( (MA)[0], ht, len, pos )
#define MULcu_Rows_rotate_buf( MA, ht, len, pos, MBuf) MULcuRows_rotate_buf( (MA)[0], ht, len, pos, (MBuf)[0] )
#define MULcu_Cols_rotate_buf( MA, ht, len, pos, MBuf) MULcuCols_rotate_buf( (MA)[0], ht, len, pos, (MBuf)[0] )
#define MULcu_Rows_reflect( MA, ht, len )              MULcuRows_reflect( (MA)[0], ht, len )
#define MULcu_Cols_reflect( MA, ht, len )              MULcuCols_reflect( (MA)[0], ht, len )
#define MULcu_Rows_rev( MA, ht, len)                   MULcuRows_rev( (MA)[0], ht, len )
#define MULcu_Cols_rev( MA, ht, len)                   MULcuCols_rev( (MA)[0], ht, len )
#define MULcu_Rows_distribution( MAbund, Limits, nBins, MX, ht, len, mode ) MULcuRows_distribution( MAbund[0], Limits, nBins, MX[0], ht, len, mode )
#define MULcu_Cols_distribution( MAbund, Limits, nBins, MX, ht, len, mode ) MULcuCols_distribution( MAbund[0], Limits, nBins, MX[0], ht, len, mode )

/********  Operations involving two rows or two colums of one matrix  *****/

#define MULcu_Rows_exchange( MA, ht, len, row1, row2 ) \
                             MULcuRows_exchange( (MA)[0], ht, len, row1, row2 )
#define MULcu_Cols_exchange( MA, ht, len, col1, col2 ) \
                             MULcuCols_exchange( (MA)[0], ht, len, col1, col2 )

/*************** Transposing and rotating a matrix **********************/

#define MULcu_transpose( MTr, MA, htTr, lenTr )    MULcutranspose( (MTr)[0], (MA)[0], htTr, lenTr )
       /*  dimensions htTr, lenTr are those of the transposed matrix, not of the original!   */
#define MULcu_rotate90( MRot, MA, htRot, lenRot )  MULcurotate90( (MRot)[0], (MA)[0], htRot, lenRot )
#define MULcu_rotate180( MRot, MA, htRot, lenRot ) VULcu_rev( (MRot)[0], (MA)[0], (htRot)*(lenRot) )
#define MULcu_rotate270( MRot, MA, htRot, lenRot ) MULcurotate270( (MRot)[0], (MA)[0], htRot, lenRot )

/*************************************************************************
 * MULcu functions (without underbar in the prefix): 	
    (working on matrices in host memory, input type 
	ulPMatrix = ulVector = pointer to matrix element[0][0], 
	scalar parameters on host and passed by value)
*
 *************************************************************************/

#define MULcuequ0( MA, ht, len )       VULcu_equ0( MA, (ht)*(len) )
void   __vf OVCUAPI  MULcuequ1( ulPMatrix MA, ui len );  /* identity matrix */
void   __vf OVCUAPI  MULcuouterprod( ulPMatrix MA, ulVector X,  ulVector Y, ui ht, ui len );

void   __vf OVCUAPI  MULcuRow_equ0( ulPMatrix MA, ui ht, ui len, ui iRow );
void   __vf OVCUAPI  MULcuCol_equ0( ulPMatrix MA, ui ht, ui len, ui iCol );
void   __vf OVCUAPI  MULcuDia_equ0( ulPMatrix MA, ui len );

void   __vf OVCUAPI  MULcuRow_equC( ulPMatrix MA, ui ht, ui len, ui iRow, unsigned long C );
void   __vf OVCUAPI  MULcuCol_equC( ulPMatrix MA, ui ht, ui len, ui iCol, unsigned long C );
void   __vf OVCUAPI  MULcuDia_equC( ulPMatrix MA, ui len, unsigned long C );

void   __vf OVCUAPI  MULcuRow_equV( ulPMatrix MA, ui ht, ui len, ui iRow, ulVector X );
void   __vf OVCUAPI  MULcuCol_equV( ulPMatrix MA, ui ht, ui len, ui iCol, ulVector X );
void   __vf OVCUAPI  MULcuDia_equV( ulPMatrix MA, ui len, ulVector X );

void   __vf OVCUAPI  MULcuTrd_equM( ulPMatrix MA, ulPMatrix MTrd, ui len );
void   __vf OVCUAPI  MULcuTrd_extract( ulPMatrix MTrd, ulPMatrix MA, ui len );

#define MULcuequM( MB, MA, ht, len )      VULcu_equV( MB, MA, (ht)*(len) )
void   __vf OVCUAPI  MULcuUequL( ulPMatrix MA, ui len );
void   __vf OVCUAPI  MULcuLequU( ulPMatrix MA, ui len );

            /* data-type conversions:  */
#define McuLItoUL( MUL, MLI, ht, len ) Vcu_LItoUL( MUL, MLI, (ht)*(len) )
#define McuULtoLI( MLI, MUL, ht, len ) Vcu_ULtoLI( MLI, MUL, (ht)*(len) )
#define McuULtoUB( MUB, MUL, ht, len ) Vcu_ULtoUB( MUB, MUL, (ht)*(len) )
#define McuULtoUS( MUS, MUL, ht, len ) Vcu_ULtoUS( MUS, MUL, (ht)*(len) )
#define McuULtoU(  MU,  MUL, ht, len ) Vcu_ULtoU(  MU,  MUL, (ht)*(len) )
#define McuUBtoUL( MUL, MUB, ht, len ) Vcu_UBtoUL( MUL, MUB, (ht)*(len) )
#define McuUStoUL( MUL, MUS, ht, len ) Vcu_UStoUL( MUL, MUS, (ht)*(len) )
#define McuUtoUL(  MUL, MU,  ht, len ) Vcu_UtoUL(  MUL, MU,   (ht)*(len) )
#ifdef _WIN64
	#define McuULtoUQ( MUQ, MUL, ht, len ) Vcu_ULtoUQ( MUQ, MUL, (ht)*(len) )
	#define McuUQtoUL( MUL, MUQ, ht, len ) Vcu_UQtoUL( MUL, MUQ, (ht)*(len) )
#endif
#define McuULtoF(  MF,  MUL, ht, len ) Vcu_ULtoF(  MF, MUL, (ht)*(len) )
#define McuULtoD(  MD,  MUL, ht, len ) Vcu_ULtoD(  MD, MUL, (ht)*(len) )

/********  Extracting a submatrix and copying a submatrix back  *********/

void  __vf OVCUAPI  MULcusubmatrix( ulPMatrix MSub, ui subHt,  ui subLen,
                          ulPMatrix MSrce, ui srceHt,  ui srceLen,
                          ui firstRowInCol,  ui sampInCol,
                          ui firstColInRow,  ui sampInRow );

void  __vf OVCUAPI  MULcusubmatrix_equM( ulPMatrix MDest, ui destHt, ui destLen,
                               ui firstRowInCol,  ui sampInCol,
                               ui firstColInRow,  ui sampInRow,
                               ulPMatrix MSrce, ui srceHt, ui srceLen );

void  __vf OVCUAPI  MULcuequMblock(  ulPMatrix MSub, ui subHt, ui subLen,
                          ulPMatrix MSrce, ui srceHt,  ui srceLen,
                          ui firstRowInCol,  ui firstColInRow );

void  __vf OVCUAPI  MULcublock_equM( ulPMatrix MDest, ui destHt, ui destLen,
                          ui firstRowInCol,  ui firstColInRow,
                          ulPMatrix MSrce, ui srceHt, ui srceLen );

void  __vf OVCUAPI  MULcuequMblockT( ulPMatrix MSub, ui subHt, ui subLen,
                          ulPMatrix MSrce, ui srceHt, ui srceLen,
                          ui firstRowInCol,  ui firstColInRow );

void  __vf OVCUAPI  MULcublock_equMT( ulPMatrix MDest, ui destHt, ui destLen,
                          ui firstRowInCol,  ui firstColInRow,
                          ulPMatrix MSrce, ui srceHt, ui srceLen );


/*****   Extracting a single row or a single column or the diagonal  *****
 *       and storing it into a vector                                    */

void __vf OVCUAPI  MULcuRow_extract( ulVector Y, ulPMatrix MA, ui ht, ui len, ui iRow );
void __vf OVCUAPI  MULcuCol_extract( ulVector Y, ulPMatrix MA, ui ht, ui len, ui iCol );
void __vf OVCUAPI  MULcuDia_extract( ulVector Y, ulPMatrix MA, ui len );

/**********  Deleting or inserting a row or a column *****************/

void __vf OVCUAPI  MULcuRow_delete( ulPMatrix MB, ulPMatrix MA, ui htA, ui lenA, ui iRow );
void __vf OVCUAPI  MULcuCol_delete( ulPMatrix MB, ulPMatrix MA, ui htA, ui lenA, ui iCol );
void __vf OVCUAPI  MULcuRow_insert( ulPMatrix MB, ulPMatrix MA, ui htB, ui lenB, ui iRow, ulVector X );
void __vf OVCUAPI  MULcuCol_insert( ulPMatrix MB, ulPMatrix MA, ui htB, ui lenB, ui iCol, ulVector X );


/******  One-dimensional vector operations **********************
         performed along all rows or all columns simultaneously,
         or along the diagonal of a square matrix                */

void   __vf OVCUAPI  MULcuRows_max( ulVector Y, ulPMatrix MA, ui ht, ui len );
void   __vf OVCUAPI  MULcuCols_max( ulVector Y, ulPMatrix MA, ui ht, ui len );
unsigned long  __vf OVCUAPI  MULcuDia_max(  ulPMatrix MA, ui len );
void   __vf OVCUAPI  MULcuRows_min( ulVector Y, ulPMatrix MA, ui ht, ui len );
void   __vf OVCUAPI  MULcuCols_min( ulVector Y, ulPMatrix MA, ui ht, ui len );
unsigned long  __vf OVCUAPI  MULcuDia_min(  ulPMatrix MA, ui len );

void  __vf OVCUAPI  MULcuRows_rotate( ulPMatrix MA, ui ht, ui len, ssize_t pos );
void  __vf OVCUAPI  MULcuCols_rotate( ulPMatrix MA, ui ht, ui len, ssize_t pos );
void  __vf OVCUAPI  MULcuRows_rotate_buf( ulPMatrix MA, ui ht, ui len, ssize_t pos, ulPMatrix MBuf );
void  __vf OVCUAPI  MULcuCols_rotate_buf( ulPMatrix MA, ui ht, ui len, ssize_t pos, ulPMatrix MBuf );
void  __vf OVCUAPI  MULcuRows_reflect( ulPMatrix MA, ui ht, ui len );
void  __vf OVCUAPI  MULcuCols_reflect( ulPMatrix MA, ui ht, ui len );
void  __vf OVCUAPI  MULcuRows_rev( ulPMatrix MA, ui ht, ui len );
void  __vf OVCUAPI  MULcuCols_rev( ulPMatrix MA, ui ht, ui len );
void  __vf OVCUAPI  MULcuRows_distribution( uiPMatrix MAbund, ulVector Limits, ui nBins, ulPMatrix MX, ui ht, ui len, int mode );
void  __vf OVCUAPI  MULcuCols_distribution( uiPMatrix MAbund, ulVector Limits, ui nBins, ulPMatrix MX, ui ht, ui len, int mode );

/********  Operations involving two rows or two colums of one matrix  *****/

void   __vf OVCUAPI  MULcuRows_exchange( ulPMatrix MA, ui ht, ui len, ui i1, ui i2 );
void   __vf OVCUAPI  MULcuCols_exchange( ulPMatrix MA, ui ht, ui len, ui i1, ui i2 );


/***************  Transposing and rotating a matrix **********************/

void  __vf OVCUAPI  MULcutranspose( ulPMatrix MTr, ulPMatrix MA,  ui htTr, ui lenTr );
void  __vf OVCUAPI  MULcurotate90(  ulPMatrix MRot, ulPMatrix MA, ui htRot, ui lenRot );
#define     MULcurotate180( MRot, MA, htRot, lenRot )  VULcu_rev( MRot, MA, (htRot)*(lenRot) )
void  __vf OVCUAPI  MULcurotate270( ulPMatrix MRot, ulPMatrix MA, ui htRot, ui lenRot );



#ifdef __cplusplus
} // end of extern "C"
#endif
#endif  /*  __MULSTD_H  */
