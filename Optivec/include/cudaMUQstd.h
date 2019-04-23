/*  cudaMUQstd.h

  matrix management functions:
  manipulations on matrices of data type "uquad" 
  (64-bit unsigned integers). Win64 only.

  This file declares the functions with the name variants 
	cudaMUQ_func	(working on matrices in device memory, input type uqMatrix, scalar parameters reside on host and are passed by value)
	cusdMUQ_func	(as cudaMUQ_func except scalar parameters reside on device and are passed by address)
	cudaMUQfunc		(as cudaMUQ_func, but input type uqPMatrix = uqVector = pointer to matrix element[0][0])
	cusdMUQfunc		(as cusdMUQ_func, but input type uqPMatrix = uqVector = pointer to matrix element[0][0])
	MUQcu_func		(working on matrices in host memory, input type uqMatrix, scalar parameters on host and passed by value)
	MUQcufunc		(as MUQcu_func, but input type uqPMatrix = uqVector = pointer to matrix element[0][0])
  where func is the respective function.

   Copyright (c) 1996-2017 by OptiCode - Dr. Martin Sander Software Dev.
  All Rights Reserved.

*/

#ifdef _WIN64
#if !defined( __CUDAMUQSTD_H )
#define __CUDAMUQSTD_H
#if !defined( __CUDAMATLIB_H )
#include <cudaMatLib.h>
#endif
#if !defined( __CUDAVUQSTD_H )
#include <cudaVUQstd.h>
#endif
#if !defined( __CUDAVUQMATH_H )
#include <cudaVUQmath.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif

/**** Generation of matrices on device memory and on pinned host memory *******************/

uqMatrix  __vf cudaMUQ_matrix( ui ht, ui len );   /* allocates a vector on device memory */
uqMatrix  __vf cudaMUQ_matrix0( ui ht, ui len );
 /* The following functions allocate device-accessible, "pinned" memory on the host.
	This memory is mapped onto the device memory space. The resulting device address is returned.
	The matrix can be accessed either by its host address "hostPtr" e.g., MUQ_equ1( hostPtr, ht, len );
	or by its device address , e.g., cudaMUQ_equ1( devicePtr, ht, len );                             */
uqMatrix  __vf cudaMUQ_pinnedMatrix(  uqMatrix *hostPtr, ui ht, ui len ); 
uqMatrix  __vf cudaMUQ_pinnedMatrix0( uqMatrix *hostPtr, ui ht, ui len );

/*************************************************************************
 * Declarations of the functions written without underbar in the prefix: *
 *	cudaMUQfunc  (input type 
                   uqPMatrix = uqVector = pointer to matrix element[0][0])
 *	cusdMUQfunc  (input type 
                   uqPMatrix = uqVector = pointer to matrix element[0][0])
 *************************************************************************/


void  __vcuf OVCUAPI  cudaMUQsetElement( uqPMatrix X, ui ht, ui len, ui m, ui n, uquad C );
void  __vcuf OVCUAPI  cusdMUQsetElement( uqPMatrix X, ui ht, ui len, ui m, ui n, uquad *d_C );
void  __vcuf OVCUAPI  cudaMUQgetElement( uquad *h_y, uqPMatrix X, ui ht, ui len, ui m, ui n );
void  __vcuf OVCUAPI  cusdMUQgetElement( uquad *d_y, uqPMatrix X, ui ht, ui len, ui m, ui n );
uquad * __vcuf OVCUAPI  cudaMUQPelement( uqPMatrix X, ui ht, ui len, ui m, ui n );
uquad   __vcuf OVCUAPI  cudaMUQelement(  uqPMatrix X, ui ht, ui len, ui m, ui n );

#define cudaMUQequ0( MA, ht, len )            cudaVUQ_equ0( MA, (ht)*(len) )
overror_t   __vcuf OVCUAPI  cudaMUQequ1( uqPMatrix MA, ui len );  /* identity matrix */
overror_t   __vcuf OVCUAPI  cudaMUQouterprod( uqPMatrix MA, uqVector X,  uqVector Y, ui ht, ui len );

overror_t   __vcuf OVCUAPI  cudaMUQRow_equ0( uqPMatrix MA, ui ht, ui len, ui iRow );
overror_t   __vcuf OVCUAPI  cudaMUQCol_equ0( uqPMatrix MA, ui ht, ui len, ui iCol );
overror_t   __vcuf OVCUAPI  cudaMUQDia_equ0( uqPMatrix MA, ui len );

overror_t   __vcuf OVCUAPI  cudaMUQRow_equC( uqPMatrix MA, ui ht, ui len, ui iRow, uquad C );
overror_t   __vcuf OVCUAPI  cudaMUQCol_equC( uqPMatrix MA, ui ht, ui len, ui iCol, uquad C );
overror_t   __vcuf OVCUAPI  cudaMUQDia_equC( uqPMatrix MA, ui len, uquad C );
overror_t   __vcuf OVCUAPI  cusdMUQRow_equC( uqPMatrix MA, ui ht, ui len, ui iRow, uquad *d_C );
overror_t   __vcuf OVCUAPI  cusdMUQCol_equC( uqPMatrix MA, ui ht, ui len, ui iCol, uquad *d_C );
overror_t   __vcuf OVCUAPI  cusdMUQDia_equC( uqPMatrix MA, ui len, uquad *d_C );

overror_t   __vcuf OVCUAPI  cudaMUQRow_equV( uqPMatrix MA, ui ht, ui len, ui iRow, uqVector X );
overror_t   __vcuf OVCUAPI  cudaMUQCol_equV( uqPMatrix MA, ui ht, ui len, ui iCol, uqVector X );
overror_t   __vcuf OVCUAPI  cudaMUQDia_equV( uqPMatrix MA, ui len, uqVector X );

overror_t   __vcuf OVCUAPI  cudaMUQTrd_equM( uqPMatrix MA, uqPMatrix MTrd, ui len );
overror_t   __vcuf OVCUAPI  cudaMUQTrd_extract( uqPMatrix MTrd, uqPMatrix MA, ui len );

#define cudaMUQequM( MB, MA, ht, len )  cudaVUQ_equV( MB, MA, (ht)*(len) )
#define cudaMUQequMhost( MB, MA, ht, len )  cudaVUQ_equVhost( MB, MA, (ht)*(len) )
#define MUQequMdevice( MB, MA, ht, len )    VUQ_equVdevice( MB, MA, (ht)*(len) )
overror_t   __vcuf OVCUAPI  cudaMUQUequL( uqPMatrix MA, ui len );
overror_t   __vcuf OVCUAPI  cudaMUQLequU( uqPMatrix MA, ui len );

            /* data-type conversions:  */
#define cudaMQItoUQ( MUQ, MQI, ht, len ) cudaV_QItoUQ( (MUQ), (MQI), (ht)*(len) )
#define cudaMUQtoQI( MQI, MUQ, ht, len ) cudaV_UQtoQI( (MQI), (MUQ), (ht)*(len) )
#define cudaMUQtoUB( MUB, MUQ, ht, len ) cudaV_UQtoUB( (MUB), (MUQ), (ht)*(len) )
#define cudaMUQtoUS( MUS, MUQ, ht, len ) cudaV_UQtoUS( (MUS), (MUQ), (ht)*(len) )
#define cudaMUQtoU(  MU,  MUQ, ht, len ) cudaV_UQtoU(  (MU),  (MUQ), (ht)*(len) )
#define cudaMUQtoUL( MUL, MUQ, ht, len ) cudaV_UQtoUL( (MUL), (MUQ), (ht)*(len) )
#define cudaMUBtoUQ( MUQ, MUB, ht, len ) cudaV_UBtoUQ( (MUQ), (MUB), (ht)*(len) )
#define cudaMUStoUQ( MUQ, MUS, ht, len ) cudaV_UStoUQ( (MUQ), (MUS), (ht)*(len) )
#define cudaMUtoUQ(  MUQ, MU,  ht, len ) cudaV_UtoUQ(  (MUQ), (MU),  (ht)*(len) )
#define cudaMULtoUQ( MUQ, MUL, ht, len ) cudaV_ULtoUQ( (MUQ), (MUL), (ht)*(len) )
#define cudaMUQtoF(  MF,  MUQ, ht, len ) cudaV_UQtoF(  (MF),  (MUQ), (ht)*(len) )
#define cudaMUQtoD(  MD,  MUQ, ht, len ) cudaV_UQtoD(  (MD),  (MUQ), (ht)*(len) )

/********  Extracting a submatrix and copying a submatrix back  *********/

overror_t  __vcuf OVCUAPI  cudaMUQsubmatrix( uqPMatrix MSub,  ui subHt,  ui subLen,
                          uqPMatrix MSrce, ui srceHt,  ui srceLen,
                          ui firstRowInCol,  ui sampInCol,
                          ui firstColInRow,  ui sampInRow );

overror_t  __vcuf OVCUAPI  cudaMUQsubmatrix_equM( uqPMatrix MDest, ui destHt, ui destLen,
                               ui firstRowInCol,  ui sampInCol,
                               ui firstColInRow,  ui sampInRow,
                               uqPMatrix MSrce, ui srceHt, ui srceLen );

overror_t  __vcuf OVCUAPI  cudaMUQequMblock(  uqPMatrix MSub, ui subHt, ui subLen,
                          uqPMatrix MSrce, ui srceHt,  ui srceLen,
                          ui firstRowInCol,  ui firstColInRow );

overror_t  __vcuf OVCUAPI  cudaMUQblock_equM( uqPMatrix MDest, ui destHt, ui destLen,
                          ui firstRowInCol,  ui firstColInRow,
                          uqPMatrix MSrce,  ui srceHt, ui srceLen );

overror_t  __vcuf OVCUAPI  cudaMUQequMblockT( uqPMatrix MSub, ui subHt, ui subLen,
                          uqPMatrix MSrce, ui srceHt, ui srceLen,
                          ui firstRowInCol,  ui firstColInRow );

overror_t  __vcuf OVCUAPI  cudaMUQblock_equMT( uqPMatrix MDest, ui destHt, ui destLen,
                          ui firstRowInCol,  ui firstColInRow,
                          uqPMatrix MSrce, ui srceHt, ui srceLen );


/*****   Extracting a single row or a single column or the diagonal  *****
 *       and storing it into a vector                                    */

overror_t __vcuf OVCUAPI  cudaMUQRow_extract( uqVector Y, uqPMatrix MA, ui ht, ui len, ui iRow );
overror_t __vcuf OVCUAPI  cudaMUQCol_extract( uqVector Y, uqPMatrix MA, ui ht, ui len, ui iCol );
overror_t __vcuf OVCUAPI  cudaMUQDia_extract( uqVector Y, uqPMatrix MA, ui len );


/**********  Deleting or inserting a row or a column *****************/

overror_t __vcuf OVCUAPI  cudaMUQRow_delete( uqPMatrix MB, uqPMatrix MA, ui htA, ui lenA, ui iRow );
overror_t __vcuf OVCUAPI  cudaMUQCol_delete( uqPMatrix MB, uqPMatrix MA, ui htA, ui lenA, ui iCol );
overror_t __vcuf OVCUAPI  cudaMUQRow_insert( uqPMatrix MB, uqPMatrix MA, ui htB, ui lenB, ui iRow, uqVector X );
overror_t __vcuf OVCUAPI  cudaMUQCol_insert( uqPMatrix MB, uqPMatrix MA, ui htB, ui lenB, ui iCol, uqVector X );


/******  One-dimensional vector operations **********************
         performed along all rows or all columns simultaneously,
         or along the diagonal of a square matrix                */

overror_t  __vcuf OVCUAPI  cudaMUQRows_max( uqVector Y, uqPMatrix MA, ui ht, ui len );
overror_t  __vcuf OVCUAPI  cudaMUQCols_max( uqVector Y, uqPMatrix MA, ui ht, ui len );
overror_t  __vcuf OVCUAPI  cudaMUQDia_max(  uquad *h_RetVal, uqPMatrix MA, ui len );
overror_t  __vcuf OVCUAPI  cusdMUQDia_max(  uquad *d_RetVal, uqPMatrix MA, ui len );
overror_t  __vcuf OVCUAPI  cudaMUQRows_min( uqVector Y, uqPMatrix MA, ui ht, ui len );
overror_t  __vcuf OVCUAPI  cudaMUQCols_min( uqVector Y, uqPMatrix MA, ui ht, ui len );
overror_t  __vcuf OVCUAPI  cudaMUQDia_min(  uquad *h_RetVal, uqPMatrix MA, ui len );
overror_t  __vcuf OVCUAPI  cusdMUQDia_min(  uquad *d_RetVal, uqPMatrix MA, ui len );

overror_t  __vcuf OVCUAPI  cudaMUQRows_rotate( uqPMatrix MA, ui ht, ui len, ssize_t pos );
overror_t  __vcuf OVCUAPI  cudaMUQCols_rotate( uqPMatrix MA, ui ht, ui len, ssize_t pos );
overror_t  __vcuf OVCUAPI  cudaMUQRows_rotate_buf( uqPMatrix MA, ui ht, ui len, ssize_t pos, uqPMatrix MBuf );
overror_t  __vcuf OVCUAPI  cudaMUQCols_rotate_buf( uqPMatrix MA, ui ht, ui len, ssize_t pos, uqPMatrix MBuf );
overror_t  __vcuf OVCUAPI  cudaMUQRows_reflect( uqPMatrix MA, ui ht, ui len );
overror_t  __vcuf OVCUAPI  cudaMUQCols_reflect( uqPMatrix MA, ui ht, ui len );
overror_t  __vcuf OVCUAPI  cudaMUQRows_rev( uqPMatrix MA, ui ht, ui len );
overror_t  __vcuf OVCUAPI  cudaMUQCols_rev( uqPMatrix MA, ui ht, ui len );
overror_t  __vcuf OVCUAPI  cudaMUQRows_distribution( uiPMatrix MAbund, uqVector Limits, ui nBins, uqPMatrix MX, ui ht, ui len, int mode );
overror_t  __vcuf OVCUAPI  cudaMUQCols_distribution( uiPMatrix MAbund, uqVector Limits, ui nBins, uqPMatrix MX, ui ht, ui len, int mode );

/********  Operations involving two rows or two colums of one matrix  *****/

overror_t   __vcuf OVCUAPI  cudaMUQRows_exchange( uqPMatrix MA, ui ht, ui len, ui i1, ui i2 );
overror_t   __vcuf OVCUAPI  cudaMUQCols_exchange( uqPMatrix MA, ui ht, ui len, ui i1, ui i2 );

/****************  Transposing and rotating a matrix **********************/

overror_t  __vcuf OVCUAPI  cudaMUQtranspose( uqPMatrix MTr, uqPMatrix MA, ui htTr, ui lenTr );
overror_t  __vcuf OVCUAPI  cudaMUQrotate90(  uqPMatrix MRot, uqPMatrix MA, ui htRot, ui lenRot );
#define       cudaMUQrotate180( MRot, MA, htRot, lenRot ) cudaVUQ_rev( MRot, MA, (htRot)*(lenRot) )
overror_t  __vcuf OVCUAPI  cudaMUQrotate270( uqPMatrix MRot, uqPMatrix MA, ui htRot, ui lenRot );
overror_t  __vcuf OVCUAPI  cudaMUQtranspose_buf( uqPMatrix MTr, uqPMatrix MA, ui htTr, ui lenTr, uqPMatrix MBuf );

/**************************  Input and Output  **************************
	The input/output functions involve memory transfers from device
	to host memory or vice versa. The generic cudaMUQ_input/output functions
	allocate their own host buffers, whereas the cudaMUQ_xxx_buf functions
	take a user-supplied buffer vector h_Wk (size must be >= ht*len )
	and are much more efficient.                                       */

#define cudaMUQprint( MA, ht, len )  cudaMUQfprint( stdout, MA, ht, len, 80 )
overror_t __vf cudaMUQfprint( FILE *stream, uqPMatrix MA, ui ht, ui len, unsigned linewidth );
overror_t __vf cudaMUQcprint( uqPMatrix MA, ui ht, ui len );
#define cudaMUQprint_buf( MA, ht, len, h_Wk )  cudaMUQfprint_buf( stdout, MA, ht, len, 80, h_Wk )
overror_t __vf cudaMUQfprint_buf( FILE *stream, uqPMatrix MA, ui ht, ui len, unsigned linewidth, uqVector h_Wk );
overror_t __vf cudaMUQcprint_buf( uqPMatrix MA, ui ht, ui len, uqVector h_Wk );
overror_t __vf cudaMUQwrite( FILE *stream, uqPMatrix X, ui ht, ui len  );
overror_t __vf cudaMUQread( uqPMatrix X, ui ht, ui len, FILE *stream );
overror_t __vf cudaMUQwrite_buf( FILE *stream, uqPMatrix X, ui ht, ui len, uqVector h_Wk );
overror_t __vf cudaMUQread_buf( uqPMatrix X, ui ht, ui len, FILE *stream, uqVector h_Wk );
#define cudaMUQstore( str, MA, ht, len ) cudaVUQ_store( str, MA, (len)*(ht) )
#define cudaMUQrecall( MA, ht, len, str) cudaVUQ_recall( MA, (len)*(ht), str)
#define cudaMUQstore_buf( str, MA, ht, len, h_Wk ) cudaVUQ_store( str, MA, (len)*(ht), h_Wk )
#define cudaMUQrecall_buf( MA, ht, len, str, h_Wk) cudaVUQ_recall( MA, (len)*(ht), str, h_Wk)



/***************************************************************************
    cudaMUQ_func	(working on matrices in device memory, input type qiMatrix, 
	             scalar parameters reside on host and are passed by value)
    cusdMUQ_func	(as cudaMUQ_func except scalar parameters reside on device 
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

inline void    cudaMUQ_setElement( uqMatrix MA, ui ht, ui len, ui m, ui n, uquad C )
	{	cudaMUQsetElement( (uqPMatrix)(MA), ht, len, m, n, C );}
inline void    cusdMUQ_setElement( uqMatrix MA, ui ht, ui len, ui m, ui n, uquad *d_C )
	{	cusdMUQsetElement( (uqPMatrix)(MA), ht, len, m, n, d_C );}
inline void    cudaMUQ_getElement( uquad *y, uqMatrix MA, ui ht, ui len, ui m, ui n )
	{	cudaMUQgetElement( y, (uqPMatrix)(MA), ht, len, m, n );}
inline void    cusdMUQ_getElement( uquad *d_y, uqMatrix MA, ui ht, ui len, ui m, ui n )
	{	cusdMUQgetElement( d_y, (uqPMatrix)(MA), ht, len, m, n );}
inline uquad * cudaMUQ_Pelement( uqMatrix MA, ui ht, ui len, ui m, ui n )
	{	return cudaMUQPelement( (uqPMatrix)(MA), ht, len, m, n );}
inline uquad   cudaMUQ_element( uqMatrix MA, ui ht, ui len, ui m, ui n )
{	return cudaMUQelement( (uqPMatrix)(MA), ht, len, m, n );}

inline overror_t  cudaMUQ_equ0( uqMatrix MA, ui ht, ui len )
	{	return cudaVUQ_equ0( (uqPMatrix)MA, (ht)*(len) ); }
inline overror_t  cudaMUQ_equ1( uqMatrix MA, ui len )
	{	return cudaMUQequ1( (uqPMatrix)(MA), len );} /* identity matrix */

inline overror_t  cudaMUQ_randomLC( uqMatrix MA, ui ht, ui len, long seed, uquad MinVal, uquad MaxVal, V_RANDOMLCSTATE *h_state )
	{	return cudaVUQ_randomLC( (uqPMatrix)(MA), (ht)*(len), seed, MinVal, MaxVal, h_state );}
inline overror_t  cudaMUQ_random( uqMatrix MA, ui ht, ui len, long seed, uquad MinVal, uquad MaxVal )
	{	return cudaVUQ_random( (uqPMatrix)(MA), (ht)*(len), seed, MinVal, MaxVal );}
inline overror_t  cusdMUQ_randomLC( uqMatrix MA, ui ht, ui len, long seed, uquad *d_MinVal, uquad *d_MaxVal, V_RANDOMLCSTATE *h_state )
	{	return cusdVUQ_randomLC( (uqPMatrix)(MA), (ht)*(len), seed, d_MinVal, d_MaxVal, h_state );}
inline overror_t  cusdMUQ_random( uqMatrix MA, ui ht, ui len, long seed, uquad *d_MinVal, uquad *d_MaxVal )
	{	return cusdVUQ_random( (uqPMatrix)(MA), (ht)*(len), seed, d_MinVal, d_MaxVal );}
inline overror_t  cudaMUQ_outerprod( uqMatrix MA, uqVector X,  uqVector Y, ui ht, ui len )
{	return cudaMUQouterprod( (uqPMatrix)(MA), X, Y, ht, len );}

inline overror_t  cudaMUQ_Row_equ0( uqMatrix MA, ui ht, ui len, ui iRow )
	{	return cudaMUQRow_equ0( (uqPMatrix)MA, ht, len, iRow );}
inline overror_t  cudaMUQ_Col_equ0( uqMatrix MA, ui ht, ui len, ui iRow )
	{	return cudaMUQCol_equ0( (uqPMatrix)MA, ht, len, iRow );}
inline overror_t  cudaMUQ_Dia_equ0( uqMatrix MA, ui len )
	{	return cudaMUQDia_equ0( (uqPMatrix)(MA), len );}

inline overror_t  cudaMUQ_Row_equC( uqMatrix MA, ui ht, ui len, ui iRow, uquad C )
	{	return cudaMUQRow_equC( (uqPMatrix)MA, ht, len, iRow, C );}
inline overror_t  cudaMUQ_Col_equC( uqMatrix MA, ui ht, ui len, ui iRow, uquad C )
	{	return cudaMUQCol_equC( (uqPMatrix)MA, ht, len, iRow, C );}
inline overror_t  cudaMUQ_Dia_equC( uqMatrix MA, ui len, uquad C )
	{	return cudaMUQDia_equC( (uqPMatrix)(MA), len, C );}

inline overror_t  cusdMUQ_Row_equC( uqMatrix MA, ui ht, ui len, ui iRow, uquad *d_C )
	{	return cusdMUQRow_equC( (uqPMatrix)MA, ht, len, iRow, d_C );}
inline overror_t  cusdMUQ_Col_equC( uqMatrix MA, ui ht, ui len, ui iRow, uquad *d_C )
	{	return cusdMUQCol_equC( (uqPMatrix)MA, ht, len, iRow, d_C );}
inline overror_t  cusdMUQ_Dia_equC( uqMatrix MA, ui len, uquad *d_C )
	{	return cusdMUQDia_equC( (uqPMatrix)(MA), len, d_C );}

inline overror_t  cudaMUQ_Row_equV( uqMatrix MA, ui ht, ui len, ui iRow, uqVector X )
	{	return cudaMUQRow_equV( (uqPMatrix)MA, ht, len, iRow, X );}
inline overror_t  cudaMUQ_Col_equV( uqMatrix MA, ui ht, ui len, ui iRow, uqVector X )
	{	return cudaMUQCol_equV( (uqPMatrix)MA, ht, len, iRow, X );}
inline overror_t  cudaMUQ_Dia_equV( uqMatrix MA, ui len, uqVector X )
	{	return cudaMUQDia_equV( (uqPMatrix)(MA), len, X );}

inline overror_t  cudaMUQ_Trd_equM( uqMatrix MA, uqMatrix MTrd, ui len )
	{	return cudaMUQTrd_equM( (uqPMatrix)(MA), (uqPMatrix)(MTrd), len );}
inline overror_t  cudaMUQ_Trd_extract( uqMatrix MTrd, uqMatrix MA, ui len )
	{	return cudaMUQTrd_extract( (uqPMatrix)(MTrd), (uqPMatrix)(MA), len );}

inline overror_t cudaMUQ_equM( uqMatrix MB, uqMatrix MA, ui ht, ui len )
	{	return cudaVUQ_equV( (uqPMatrix)MB, (uqPMatrix)MA, (ht)*(len) );}
inline overror_t cudaMUQ_equMhost( uqMatrix d_MB, uqMatrix h_MA, ui ht, ui len )
	{	return cudaVUQ_equVhost( (uqPMatrix)d_MB, (h_MA)[0], (ht)*(len) );}
inline overror_t MUQ_equMdevice( uqMatrix h_MB, uqMatrix d_MA, ui ht, ui len )
	{	return VUQ_equVdevice( h_MB[0], (uqPMatrix)d_MA, (ht)*(len) );}
inline overror_t  cudaMUQ_UequL( uqMatrix MA, ui len )
	{	return cudaMUQUequL( (uqPMatrix)(MA), len );}
inline overror_t  cudaMUQ_LequU( uqMatrix MA, ui len )
	{	return cudaMUQLequU( (uqPMatrix)(MA), len );}

/************** Data-type interconversions  ****************************/

inline overror_t cudaM_QItoUQ( uqMatrix MUQ, qiMatrix MQI, ui ht, ui len )
	{	return cudaV_QItoUQ( (uqVector)MUQ, (qiVector)MQI, (ht)*(len) );}
inline overror_t cudaM_UBtoUQ( uqMatrix MUQ, ubMatrix MUB, ui ht, ui len )
	{	return cudaV_UBtoUQ( (uqVector)MUQ, (ubVector)MUB, (ht)*(len) );}
inline overror_t cudaM_UStoUQ( uqMatrix MUQ, usMatrix MUS, ui ht, ui len )
	{	return cudaV_UStoUQ( (uqVector)MUQ, (usVector)MUS, (ht)*(len) );}
inline overror_t cudaM_UtoUQ(  uqMatrix MUQ, uMatrix MU,  ui ht, ui len )
	{	return cudaV_UtoUQ(  (uqVector)MUQ, (uVector)MU,   (ht)*(len) );}
inline overror_t cudaM_ULtoUQ( uqMatrix MUQ, ulMatrix MUL, ui ht, ui len )
	{	return cudaV_ULtoUQ( (uqVector)MUQ, (ulVector)MUL, (ht)*(len) );}
inline overror_t cudaM_UQtoF(  fMatrix MF,  uqMatrix MUQ, ui ht, ui len )
	{	return cudaV_UQtoF(  (fVector)MF,   (uqVector)MUQ, (ht)*(len) );}
inline overror_t cudaM_UQtoD(  dMatrix MD,  uqMatrix MUQ, ui ht, ui len )
	{	return cudaV_UQtoD(  (dVector)MD,   (uqVector)MUQ, (ht)*(len) );}

/********  Extracting a submatrix and copying a submatrix back  *********/

inline overror_t cudaMUQ_submatrix( uqMatrix MSub, ui subHt, ui subLen, uqMatrix MSrce, ui srceHt, ui srceLen,
                      ui firstRowInCol, ui sampInCol, ui firstColInRow, ui sampInRow )
	{	return cudaMUQsubmatrix(  (uqPMatrix)(MSub), subHt, subLen,
		                         (uqPMatrix)(MSrce), srceHt, srceLen,
								 firstRowInCol, sampInCol, firstColInRow, sampInRow ); }

inline overror_t cudaMUQ_submatrix_equM( uqMatrix MDest, ui destHt, ui destLen,
                           ui firstRowInCol, ui sampInCol, ui firstColInRow, ui sampInRow,
                           uqMatrix MSrce, ui srceHt, ui srceLen )
	{	return cudaMUQsubmatrix_equM(  (uqPMatrix)(MDest), destHt, destLen,
                             firstRowInCol, sampInCol, firstColInRow, sampInRow,
							 (uqPMatrix)(MSrce), srceHt, srceLen );}

inline overror_t cudaMUQ_equMblock( uqMatrix MSub, ui subHt, ui subLen, uqMatrix MSrce, ui srceHt, ui srceLen,
                      ui firstRowInCol, ui firstColInRow )
{	return cudaMUQequMblock(  (uqPMatrix)(MSub), subHt, subLen,
						   (uqPMatrix)(MSrce), srceHt, srceLen, firstRowInCol, firstColInRow );}

inline overror_t cudaMUQ_block_equM( uqMatrix MDest, ui destHt, ui destLen,
                       ui firstRowInCol, ui firstColInRow,
                       uqMatrix MSrce, ui srceHt, ui srceLen )
	{	return cudaMUQblock_equM( (uqPMatrix)(MDest), destHt, destLen,
                             firstRowInCol, firstColInRow,
							 (uqPMatrix)(MSrce), srceHt, srceLen );}

inline overror_t cudaMUQ_equMblockT( uqMatrix MSub, ui subHt, ui subLen, uqMatrix MSrce, ui srceHt, ui srceLen,
                      ui firstRowInCol, ui firstColInRow )
	{	return cudaMUQequMblockT(  (uqPMatrix)(MSub), subHt, subLen,
                             (uqPMatrix)(MSrce), srceHt, srceLen,
							 firstRowInCol, firstColInRow );}

inline overror_t cudaMUQ_block_equMT( uqMatrix MDest, ui destHt, ui destLen,
                       ui firstRowInCol, ui firstColInRow,
                       uqMatrix MSrce, ui srceHt, ui srceLen )
	{	return cudaMUQblock_equMT( (uqPMatrix)(MDest), destHt, destLen,
                             firstRowInCol, firstColInRow,
							 (uqPMatrix)(MSrce), srceHt, srceLen );}

/*****   Extracting a single row or a single column or the diagonal  ******
 *       and storing it into a vector                                     */

inline overror_t cudaMUQ_Row_extract( uqVector Y, uqMatrix MA, ui ht, ui len, ui iRow ) 
	{	return cudaMUQRow_extract( Y, (uqPMatrix)(MA), ht, len, iRow );}
inline overror_t cudaMUQ_Col_extract( uqVector Y, uqMatrix MA, ui ht, ui len, ui iCol ) 
	{	return cudaMUQCol_extract( Y, (uqPMatrix)(MA), ht, len, iCol );}
inline overror_t cudaMUQ_Dia_extract( uqVector Y, uqMatrix MA, ui len )
	{	return cudaMUQDia_extract( Y, (uqPMatrix)(MA), len );}

/**************  Deleting or inserting a row or a column   ***************/

inline overror_t cudaMUQ_Row_delete( uqMatrix MB, uqMatrix MA, ui htA, ui lenA, ui iRow )
	{	return cudaMUQRow_delete( (uqPMatrix)(MB), (uqPMatrix)(MA), htA, lenA, iRow );}
inline overror_t cudaMUQ_Col_delete( uqMatrix MB, uqMatrix MA, ui htA, ui lenA, ui iCol )
	{	return cudaMUQCol_delete( (uqPMatrix)(MB), (uqPMatrix)(MA), htA, lenA, iCol );}
inline overror_t cudaMUQ_Row_insert( uqMatrix MB, uqMatrix MA, ui htB, ui lenB, ui iRow, uqVector X )
	{	return cudaMUQRow_insert( (uqPMatrix)(MB), (uqPMatrix)(MA), htB, lenB, iRow, X );}
inline overror_t cudaMUQ_Col_insert( uqMatrix MB, uqMatrix MA, ui htB, ui lenB, ui iCol, uqVector X )
	{	return cudaMUQCol_insert( (uqPMatrix)(MB), (uqPMatrix)(MA), htB, lenB, iCol, X );}


/******  One-dimensional vector operations **********************
         performed along all rows or all columns simultaneously,
         or along the diagonal of a square matrix                */

inline overror_t cudaMUQ_Rows_max( uqVector Y, uqMatrix MA, ui ht, ui len )
	{	return cudaMUQRows_max( Y, (uqPMatrix)(MA), ht, len );}
inline overror_t cudaMUQ_Cols_max( uqVector Y, uqMatrix MA, ui ht, ui len )
	{	return cudaMUQCols_max( Y, (uqPMatrix)(MA), ht, len );}
inline overror_t cudaMUQ_Dia_max(  uquad *h_RetValPtr, uqMatrix MA, ui len )
	{	return cudaMUQDia_max(  h_RetValPtr, (uqPMatrix)(MA), len );}
inline overror_t cusdMUQ_Dia_max(  uquad *d_RetValPtr, uqMatrix MA, ui len )
	{	return cusdMUQDia_max(  d_RetValPtr, (uqPMatrix)(MA), len );}
inline overror_t cudaMUQ_Rows_min( uqVector Y, uqMatrix MA, ui ht, ui len )
	{	return cudaMUQRows_min( Y, (uqPMatrix)(MA), ht, len );}
inline overror_t cudaMUQ_Cols_min( uqVector Y, uqMatrix MA, ui ht, ui len )
	{	return cudaMUQCols_min( Y, (uqPMatrix)(MA), ht, len );}
inline overror_t cudaMUQ_Dia_min(  uquad *h_RetValPtr, uqMatrix MA, ui len )
	{	return cudaMUQDia_min(  h_RetValPtr, (uqPMatrix)(MA), len );}
inline overror_t cusdMUQ_Dia_min(  uquad *d_RetValPtr, uqMatrix MA, ui len )
	{	return cusdMUQDia_min(  d_RetValPtr, (uqPMatrix)(MA), len );}

inline overror_t cudaMUQ_Rows_rotate( uqMatrix MA, ui ht, ui len, ssize_t pos)
	{	return cudaMUQRows_rotate( (uqPMatrix)(MA), ht, len, pos );}
inline overror_t cudaMUQ_Cols_rotate( uqMatrix MA, ui ht, ui len, ssize_t pos)
	{	return cudaMUQCols_rotate( (uqPMatrix)(MA), ht, len, pos );}
inline overror_t cudaMUQ_Rows_rotate_buf( uqMatrix MA, ui ht, ui len, ssize_t pos, uqMatrix MBuf) 
	{	return cudaMUQRows_rotate_buf( (uqPMatrix)(MA), ht, len, pos, (uqPMatrix)(MBuf) );}
inline overror_t cudaMUQ_Cols_rotate_buf( uqMatrix MA, ui ht, ui len, ssize_t pos, uqMatrix MBuf) 
	{	return cudaMUQCols_rotate_buf( (uqPMatrix)(MA), ht, len, pos, (uqPMatrix)(MBuf) );}
inline overror_t cudaMUQ_Rows_reflect( uqMatrix MA, ui ht, ui len )
	{	return cudaMUQRows_reflect( (uqPMatrix)(MA), ht, len );}
inline overror_t cudaMUQ_Cols_reflect( uqMatrix MA, ui ht, ui len )
	{	return cudaMUQCols_reflect( (uqPMatrix)(MA), ht, len );}
inline overror_t cudaMUQ_Rows_rev( uqMatrix MA, ui ht, ui len )
	{	return cudaMUQRows_rev( (uqPMatrix)(MA), ht, len );}
inline overror_t cudaMUQ_Cols_rev( uqMatrix MA, ui ht, ui len )
	{	return cudaMUQCols_rev( (uqPMatrix)(MA), ht, len );}
inline overror_t  cudaMUQ_Rows_distribution( uiMatrix MAbund, uqVector Limits, ui nBins, uqMatrix MX, ui ht, ui len, int mode )
	{	return cudaMUQRows_distribution( (uiPMatrix)MAbund, Limits, nBins, (uqPMatrix)MX, ht, len, mode ); }
inline overror_t  cudaMUQ_Cols_distribution( uiMatrix MAbund, uqVector Limits, ui nBins, uqMatrix MX, ui ht, ui len, int mode )
	{	return cudaMUQCols_distribution( (uiPMatrix)MAbund, Limits, nBins, (uqPMatrix)MX, ht, len, mode ); }

/********  Operations involving two rows or two colums of one matrix  *****/

inline overror_t cudaMUQ_Rows_exchange( uqMatrix MA, ui ht, ui len, ui row1, ui row2 )
	{	return cudaMUQRows_exchange( (uqPMatrix)(MA), ht, len, row1, row2 );}
inline overror_t cudaMUQ_Cols_exchange( uqMatrix MA, ui ht, ui len, ui col1, ui col2 )
	{	return cudaMUQCols_exchange( (uqPMatrix)(MA), ht, len, col1, col2 );}

/*************** Transposing and rotating a matrix **********************/

inline overror_t cudaMUQ_transpose( uqMatrix MTr, uqMatrix MA, ui htTr, ui lenTr )
	{	return cudaMUQtranspose( (uqPMatrix)(MTr), (uqPMatrix)(MA), htTr, lenTr );}
       /*  dimensions htTr, lenTr are those of the transposed matrix, not of the original!   */
inline overror_t cudaMUQ_rotate90( uqMatrix MRot, uqMatrix MA, ui htRot, ui lenRot )
	{	return cudaMUQrotate90( (uqPMatrix)(MRot), (uqPMatrix)(MA), htRot, lenRot );}
inline overror_t cudaMUQ_rotate180( uqMatrix MRot, uqMatrix MA, ui htRot, ui lenRot )
	{	return cudaVUQ_rev( (uqPMatrix)(MRot), (uqPMatrix)(MA), (htRot)*(lenRot) );}
inline overror_t cudaMUQ_rotate270( uqMatrix MRot, uqMatrix MA, ui htRot, ui lenRot )
	{	return cudaMUQrotate270( (uqPMatrix)(MRot), (uqPMatrix)(MA), htRot, lenRot );}
inline overror_t cudaMUQ_transpose_buf( uqMatrix MTr, uqMatrix MA, ui htTr, ui lenTr, uqMatrix MBuf )
	{	return cudaMUQtranspose_buf( (uqPMatrix)(MTr), (uqPMatrix)(MA), htTr, lenTr, (uqPMatrix)(MBuf) );}

/**************************  Input and Output  **************************
	The input/output functions involve memory transfers from device
	to host memory or vice versa. The generic cudaMUQ_input/output functions
	allocate their own host buffers, whereas the cudaMUQ_xxx_buf functions
	take a user-supplied buffer vector h_Wk (size must be >= ht*len )
	and are much more efficient.                                       */

inline overror_t cudaMUQ_fprint( FILE *stream, uqMatrix MA, ui ht, ui len, unsigned linewidth )
	{	return cudaMUQfprint( stream, (uqPMatrix)(MA), ht, len, linewidth ); }
inline overror_t cudaMUQ_print( uqMatrix MA, ui ht, ui len )
	{	return cudaMUQfprint( stdout, (uqPMatrix)(MA), ht, len, 80 ); }
inline overror_t cudaMUQ_cprint( uqMatrix MA, ui ht, ui len )
	{	return cudaMUQcprint( (uqPMatrix)(MA), ht, len ); }
inline overror_t cudaMUQ_fprint_buf( FILE *stream, uqMatrix d_MA, ui ht, ui len, unsigned linewidth, uqVector h_Wk )
	{	return cudaMUQfprint_buf( stream, (uqPMatrix)(d_MA), ht, len, linewidth, h_Wk ); }
inline overror_t cudaMUQ_print_buf( uqMatrix d_MA, ui ht, ui len, uqVector h_Wk )
	{	return cudaMUQfprint_buf( stdout, (uqPMatrix)(d_MA), ht, len, 80, h_Wk ); }
inline overror_t cudaMUQ_cprint_buf( uqMatrix d_MA, ui ht, ui len, uqVector h_Wk )
	{	return cudaMUQcprint_buf( (uqPMatrix)(d_MA), ht, len, h_Wk ); }
		/*  cudaMUQ_print, cudaMUQ_cprint usable only for console applications! */
inline overror_t  cudaMUQ_write( FILE *stream, uqMatrix MA, ui ht, ui len )
	{	return cudaMUQwrite( stream, (uqPMatrix)(MA), ht, len ); }
inline overror_t cudaMUQ_read( uqMatrix MA, ui ht, ui len, FILE *stream )
	{	return cudaMUQread( (uqPMatrix)(MA), ht, len, stream ); }
inline overror_t  cudaMUQ_write_buf( FILE *stream, uqMatrix d_MA, ui ht, ui len, uqVector h_Wk )
	{	return cudaMUQwrite_buf( stream, (uqPMatrix)(d_MA), ht, len, h_Wk ); }
inline overror_t cudaMUQ_read_buf( uqMatrix d_MA, ui ht, ui len, FILE *stream, uqVector h_Wk )
	{	return cudaMUQread_buf( (uqPMatrix)(d_MA), ht, len, stream, h_Wk ); }
                                   /* write and read in ascii format */
inline overror_t cudaMUQ_store( FILE *stream, uqMatrix MA, ui ht, ui len )
{	return cudaVUQ_store( stream, (uqPMatrix)(MA), (len)*(ht) ); }
inline overror_t cudaMUQ_recall( uqMatrix MA, ui ht, ui len, FILE *stream )
	{	return cudaVUQ_recall( (uqPMatrix)(MA), (len)*(ht), stream ); }
inline overror_t cudaMUQ_store_buf( FILE *stream, uqMatrix d_MA, ui ht, ui len, uqVector h_Wk )
{	return cudaVUQ_store_buf( stream, (uqPMatrix)(d_MA), (len)*(ht), h_Wk ); }
inline overror_t cudaMUQ_recall_buf( uqMatrix d_MA, ui ht, ui len, FILE *stream, uqVector h_Wk )
	{	return cudaVUQ_recall_buf( (uqPMatrix)(d_MA), (len)*(ht), stream, h_Wk ); }
                                  /* store and recall in binary format */

#else  /* plain-C, not C++: type-cast used to transform uqMatrix into uqPMatrix */


/***  Addressing single elements of dynamically allocated matrices: ******/

#define cudaMUQ_setElement( MA, ht, len, m, n, C ) cudaMUQsetElement( (uqPMatrix)(MA), ht, len, m, n, C )
#define cusdMUQ_setElement( MA, ht, len, m, n, C ) cusdMUQsetElement( (uqPMatrix)(MA), ht, len, m, n, C )
#define cudaMUQ_getElement( y, MA, ht, len, m, n ) cudaMUQgetElement( y, (uqPMatrix)(MA), ht, len, m, n )
#define cusdMUQ_getElement( y, MA, ht, len, m, n ) cusdMUQgetElement( y, (uqPMatrix)(MA), ht, len, m, n )
#define cudaMUQ_Pelement( MA, ht, len, m, n )      cudaMUQPelement( (uqPMatrix)(MA), ht, len, m, n )
#define cudaMUQ_element(  MA, ht, len, m, n )      cudaMUQelement( (uqPMatrix)(MA), ht, len, m, n )

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
        cudaVUQ_equ1( (uqVector)MA, ht * len );
*/

#define cudaMUQ_equ0( MA, ht, len )            cudaVUQ_equ0( (uqPMatrix)(MA), (ht)*(len) )
#define cudaMUQ_equ1( MA, len )                cudaMUQequ1( (uqPMatrix)(MA), len ) /* identity matrix */
#define cudaMUQ_randomLC( MA, ht, len, seed, Min, Max, h_state )      cudaVUQ_randomLC( MA, (ht)*(len), seed, Min, Max, h_state )
#define cudaMUQ_random( MA, ht, len, seed, Min, Max )                 cudaVUQ_random( MA, (ht)*(len), seed, Min, Max )
#define cusdMUQ_randomLC( MA, ht, len, seed, d_Min, d_Max, h_state )  cudaVUQ_randomLC( MA, (ht)*(len), seed, d_Min, d_Max, h_state )
#define cusdMUQ_random( MA, ht, len, seed, d_Min, d_Max )             cudaVUQ_random( MA, (ht)*(len), seed, d_Min, d_Max )
#define cudaMUQ_outerprod( MA, X, Y, ht, len ) cudaMUQouterprod( (uqPMatrix)(MA), X, Y, ht, len )
                       /* sizX=ht, sizY=len */
#define cudaMUQ_Row_equ0( MA, ht, len, iRow )    cudaMUQRow_equ0( (uqPMatrix)(MA), ht, len, iRow )
#define cudaMUQ_Col_equ0( MA, ht, len, iCol )    cudaMUQCol_equ0( (uqPMatrix)(MA), ht, len, iCol )
#define cudaMUQ_Dia_equ0( MA, len )              cudaMUQDia_equ0( (uqPMatrix)(MA), len )
#define cudaMUQ_Row_equC( MA, ht, len, iRow, C ) cudaMUQRow_equC( (uqPMatrix)(MA), ht, len, iRow, C )
#define cudaMUQ_Col_equC( MA, ht, len, iCol, C ) cudaMUQCol_equC( (uqPMatrix)(MA), ht, len, iCol, C )
#define cudaMUQ_Dia_equC( MA, len, C )           cudaMUQDia_equC( (uqPMatrix)(MA), len, C )
#define cusdMUQ_Row_equC( MA, ht, len, iRow, d_C ) cusdMUQRow_equC( (uqPMatrix)(MA), ht, len, iRow, d_C )
#define cusdMUQ_Col_equC( MA, ht, len, iCol, d_C ) cusdMUQCol_equC( (uqPMatrix)(MA), ht, len, iCol, d_C )
#define cusdMUQ_Dia_equC( MA, len, d_C )           cusdMUQDia_equC( (uqPMatrix)(MA), len, d_C )

#define cudaMUQ_Row_equV( MA, ht, len, iRow, X ) cudaMUQRow_equV( (uqPMatrix)(MA), ht, len, iRow, X )
#define cudaMUQ_Col_equV( MA, ht, len, iCol, X ) cudaMUQCol_equV( (uqPMatrix)(MA), ht, len, iCol, X )
#define cudaMUQ_Dia_equV( MA, len, X )           cudaMUQDia_equV( (uqPMatrix)(MA), len, X )

#define cudaMUQ_Trd_equM( MA, MTrd, len )    cudaMUQTrd_equM( (uqPMatrix)(MA), (uqPMatrix)(MTr)d, len )
#define cudaMUQ_Trd_extract( MTrd, MA, len ) cudaMUQTrd_extract( (uqPMatrix)(MTr)d, (uqPMatrix)(MA), len )

#define cudaMUQ_equM( MB, MA, ht, len )      cudaVUQ_equV( (uqPMatrix)(MB), (uqPMatrix)(MA), (ht)*(len) )
#define cudaMUQ_equMhost( MB, MA, ht, len )  cudaVUQ_equVhost( (uqPMatrix)(MB), MA[0], (ht)*(len) )
#define MUQ_equMdevice( MB, MA, ht, len )    VUQ_equVdevice( MB[0], (uqPMatrix)(MA), (ht)*(len) )

#define cudaMUQ_UequL( MA, len ) cudaMUQUequL( (uqPMatrix)(MA), len )
#define cudaMUQ_LequU( MA, len ) cudaMUQLequU( (uqPMatrix)(MA), len )

/************** Data-type interconversions  ****************************/

#define cudaM_QItoUQ( MUQ, MQI, ht, len ) cudaV_QItoUQ( (uqVector)(MUQ), (qiVector)(MQI), (ht)*(len) )
#define cudaM_UQtoQI( MQI, MUQ, ht, len ) cudaV_UQtoQI( (qiVector)(MQI), (uqVector)(MUQ), (ht)*(len) )
#define cudaM_UQtoUB( MUB, MUQ, ht, len ) cudaV_UQtoUB( (ubVector)(MUB), (uqVector)(MUQ), (ht)*(len) )
#define cudaM_UQtoUS( MUS, MUQ, ht, len ) cudaV_UQtoUS( (usVector)(MUS), (uqVector)(MUQ), (ht)*(len) )
#define cudaM_UQtoU(  MU,  MUQ, ht, len ) cudaV_UQtoU(  (uVector)(MU),   (uqVector)(MUQ), (ht)*(len) )
#define cudaM_UQtoUL( MUL, MUQ, ht, len ) cudaV_UQtoUL( (ulVector)(MUL), (uqVector)(MUQ), (ht)*(len) )
#define cudaM_UQtoQI( MQI, MUQ, ht, len ) cudaV_UQtoQI( (qiVector)(MQI), (uqVector)(MUQ), (ht)*(len) )
#define cudaM_UBtoUQ( MUQ, MUB, ht, len ) cudaV_UBtoUQ( (uqVector)(MUQ), (ubVector)(MUB), (ht)*(len) )
#define cudaM_UStoUQ( MUQ, MUS, ht, len ) cudaV_UStoUQ( (uqVector)(MUQ), (usVector)(MUS), (ht)*(len) )
#define cudaM_UtoUQ(  MUQ, MU,  ht, len ) cudaV_UtoUQ(  (uqVector)(MUQ), (uVector)(MU),   (ht)*(len) )
#define cudaM_ULtoUQ( MUQ, MUL, ht, len ) cudaV_ULtoUQ( (uqVector)(MUQ), (ulVector)(MUL), (ht)*(len) )
#define cudaM_QItoUQ( MUQ, MQI, ht, len ) cudaV_QItoUQ( (uqVector)(MUQ), (qiVector)(MQI), (ht)*(len) )
#define cudaM_UQtoF(  MF,  MUQ, ht, len ) cudaV_UQtoF(  (fVector)(MF),   (uqVector)(MUQ), (ht)*(len) )
#define cudaM_UQtoD(  MD,  MUQ, ht, len ) cudaV_UQtoD(  (dVector)(MD),   (uqVector)(MUQ), (ht)*(len) )


/********  Extracting a submatrix and copying a submatrix back  *********/

#define cudaMUQ_submatrix( MSub, subHt, subLen, MSrce, srceHt, srceLen, \
                      firstRowInCol, sampInCol, firstColInRow, sampInRow ) \
               cudaMUQsubmatrix(  (uqPMatrix)(MSub), subHt, subLen, \
                             (uqPMatrix)(MSrce), srceHt, srceLen, \
                             firstRowInCol, sampInCol, firstColInRow, sampInRow )

#define cudaMUQ_submatrix_equM( MDest, destHt, destLen, \
                           firstRowInCol, sampInCol, firstColInRow, sampInRow, \
                           MSrce, srceHt, srceLen ) \
               cudaMUQsubmatrix_equM(  (uqPMatrix)(MDest), destHt, destLen, \
                             firstRowInCol, sampInCol, firstColInRow, sampInRow, \
                             (uqPMatrix)(MSrce), srceHt, srceLen )

#define cudaMUQ_equMblock( MSub, subHt, subLen, MSrce, srceHt, srceLen, \
                      firstRowInCol, firstColInRow ) \
               cudaMUQequMblock(  (uqPMatrix)(MSub), subHt, subLen, \
                             (uqPMatrix)(MSrce), srceHt, srceLen, \
                             firstRowInCol, firstColInRow )

#define cudaMUQ_block_equM( MDest, destHt, destLen, \
                       firstRowInCol, firstColInRow, \
                       MSrce, srceHt, srceLen ) \
               cudaMUQblock_equM( (uqPMatrix)(MDest), destHt, destLen, \
                             firstRowInCol, firstColInRow, \
                             (uqPMatrix)(MSrce), srceHt, srceLen )

#define cudaMUQ_equMblockT( MSub, subHt, subLen, \
                      MSrce, srceHt, srceLen, \
                      firstRowInCol, firstColInRow ) \
               cudaMUQequMblockT(  (uqPMatrix)(MSub), subHt, subLen, \
                             (uqPMatrix)(MSrce), srceHt, srceLen, \
                             firstRowInCol, firstColInRow )

#define cudaMUQ_block_equMT( MDest, destHt, destLen, \
                       firstRowInCol, firstColInRow, \
                       MSrce, srceHt, srceLen ) \
               cudaMUQblock_equMT( (uqPMatrix)(MDest), destHt, destLen, \
                             firstRowInCol, firstColInRow, \
                             (uqPMatrix)(MSrce), srceHt, srceLen )

/*****   Extracting a single row or a single column or the diagonal  ******
 *       and storing it into a vector                                     */

#define cudaMUQ_Row_extract( Y, MA, ht, len, iRow ) cudaMUQRow_extract( Y, (uqPMatrix)(MA), ht, len, iRow )
#define cudaMUQ_Col_extract( Y, MA, ht, len, iCol ) cudaMUQCol_extract( Y, (uqPMatrix)(MA), ht, len, iCol )
#define cudaMUQ_Dia_extract( Y, MA, len )           cudaMUQDia_extract( Y, (uqPMatrix)(MA), len )


/**************  Deleting or inserting a row or a column   ***************/

#define cudaMUQ_Row_delete( MB, MA, htA, lenA, iRow ) cudaMUQRow_delete( (uqPMatrix)(MB), (uqPMatrix)(MA), htA, lenA, iRow )
#define cudaMUQ_Col_delete( MB, MA, htA, lenA, iCol ) cudaMUQCol_delete( (uqPMatrix)(MB), (uqPMatrix)(MA), htA, lenA, iCol )
#define cudaMUQ_Row_insert( MB, MA, htB, lenB, iRow, X ) cudaMUQRow_insert( (uqPMatrix)(MB), (uqPMatrix)(MA), htB, lenB, iRow, X )
#define cudaMUQ_Col_insert( MB, MA, htB, lenB, iCol, X ) cudaMUQCol_insert( (uqPMatrix)(MB), (uqPMatrix)(MA), htB, lenB, iCol, X )

/******  One-dimensional vector operations **********************
         performed along all rows or all columns simultaneously,
         or along the diagonal of a square matrix                */

#define cudaMUQ_Rows_max( Y, MA, ht, len )     cudaMUQRows_max( Y, (uqPMatrix)(MA), ht, len )
#define cudaMUQ_Cols_max( Y, MA, ht, len )     cudaMUQCols_max( Y, (uqPMatrix)(MA), ht, len )
#define cudaMUQ_Dia_max(  h_RetPtr, MA, len )  cudaMUQDia_max( h_RetPtr, (uqPMatrix)(MA), len )
#define cusdMUQ_Dia_max(  d_RetPtr, MA, len )  cusdMUQDia_max( d_RetPtr, (uqPMatrix)(MA), len )
#define cudaMUQ_Rows_min( Y, MA, ht, len )     cudaMUQRows_min( Y, (uqPMatrix)(MA), ht, len )
#define cudaMUQ_Cols_min( Y, MA, ht, len )     cudaMUQCols_min( Y, (uqPMatrix)(MA), ht, len )
#define cudaMUQ_Dia_min(  h_RetPtr, MA, len )  cudaMUQDia_min( h_RetPtr, (uqPMatrix)(MA), len )
#define cusdMUQ_Dia_min(  d_RetPtr, MA, len )  cusdMUQDia_min( d_RetPtr, (uqPMatrix)(MA), len )

#define cudaMUQ_Rows_rotate( MA, ht, len, pos) cudaMUQRows_rotate( (uqPMatrix)(MA), ht, len, pos )
#define cudaMUQ_Cols_rotate( MA, ht, len, pos) cudaMUQCols_rotate( (uqPMatrix)(MA), ht, len, pos )
#define cudaMUQ_Rows_rotate_buf( MA, ht, len, pos, MBuf) cudaMUQRows_rotate_buf( (uqPMatrix)(MA), ht, len, pos, (uqPMatrix)(MBuf) )
#define cudaMUQ_Cols_rotate_buf( MA, ht, len, pos, MBuf) cudaMUQCols_rotate_buf( (uqPMatrix)(MA), ht, len, pos, (uqPMatrix)(MBuf) )
#define cudaMUQ_Rows_reflect( MA, ht, len)     cudaMUQRows_reflect( (uqPMatrix)(MA), ht, len )
#define cudaMUQ_Cols_reflect( MA, ht, len)     cudaMUQCols_reflect( (uqPMatrix)(MA), ht, len )
#define cudaMUQ_Rows_rev( MA, ht, len)         cudaMUQRows_rev( (uqPMatrix)(MA), ht, len )
#define cudaMUQ_Cols_rev( MA, ht, len)         cudaMUQCols_rev( (uqPMatrix)(MA), ht, len )
#define cudaMUQ_Rows_distribution( MAbund, Limits, nBins, MX, ht, len, mode ) cudaMUQRows_distribution( (uiPMatrix)MAbund, Limits, nBins, (uqPMatrix)MX, ht, len, mode )
#define cudaMUQ_Cols_distribution( MAbund, Limits, nBins, MX, ht, len, mode ) cudaMUQCols_distribution( (uiPMatrix)MAbund, Limits, nBins, (uqPMatrix)MX, ht, len, mode )

/********  Operations involving two rows or two colums of one matrix  *****/

#define cudaMUQ_Rows_exchange( MA, ht, len, row1, row2 ) cudaMUQRows_exchange( (uqPMatrix)(MA), ht, len, row1, row2 )
#define cudaMUQ_Cols_exchange( MA, ht, len, col1, col2 ) cudaMUQCols_exchange( (uqPMatrix)(MA), ht, len, col1, col2 )

/****************  Transposing and rotating a matrix **********************/

#define cudaMUQ_transpose( MTr, MA, htTr, lenTr ) cudaMUQtranspose( (uqPMatrix)(MTr), (uqPMatrix)(MA), htTr, lenTr )
       /*  dimensions htTr, lenTr are those of the transposed matrix,
           not of the original!                */
#define cudaMUQ_rotate90( MRot, MA, htRot, lenRot )  cudaMUQrotate90( (uqPMatrix)(MRot), (uqPMatrix)(MA), htRot, lenRot )
#define cudaMUQ_rotate180( MRot, MA, htRot, lenRot ) cudaVUQ_rev( (uqPMatrix)(MRot), (uqPMatrix)(MA), (htRot)*(lenRot) )
#define cudaMUQ_rotate270( MRot, MA, htRot, lenRot ) cudaMUQrotate270( (uqPMatrix)(MRot), (uqPMatrix)(MA), htRot, lenRot )
#define cudaMUQ_transpose_buf( MTr, MA, htTr, lenTr, MBuf ) cudaMUQtranspose_buf( (uqPMatrix)(MTr), (uqPMatrix)(MA), htTr, lenTr, (uqPMatrix)(MBuf) )


/**************************  Input and Output  **************************
	The input/output functions involve memory transfers from device
	to host memory or vice versa. The generic cudaMUQ_input/output functions
	allocate their own host buffers, whereas the cudaMUQ_xxx_buf functions
	take a user-supplied buffer vector h_Wk (size must be >= ht*len )
	and are much more efficient.                                       */

#define cudaMUQ_fprint( stream, MA, ht, len, linewidth ) \
                    cudaMUQfprint( stream, (uqPMatrix)(MA), ht, len, linewidth )
#define cudaMUQ_print( MA, ht, len )  cudaMUQfprint( stdout, (uqPMatrix)(MA), ht, len, 80 )
#define cudaMUQ_cprint( MA, ht, len ) cudaMUQcprint( (uqPMatrix)(MA), ht, len )
#define cudaMUQ_fprint_buf( stream, MA, ht, len, linewidth, h_Wk ) \
                    cudaMUQfprint_buf( stream, (uqPMatrix)(MA), ht, len, linewidth, h_Wk )
#define cudaMUQ_print_buf( MA, ht, len )  cudaMUQfprint_buf( stdout, (uqPMatrix)(MA), ht, len, 80, h_Wk )
#define cudaMUQ_cprint_buf( MA, ht, len ) cudaMUQcprint_buf( (uqPMatrix)(MA), ht, len, h_Wk )
  /*  cudaMUQ_print, cudaMUQ_cprint usable only for console applications! */
#define cudaMUQ_write( str, MA, ht, len )   cudaMUQwrite( str, (uqPMatrix)(MA), ht, len )
#define cudaMUQ_read( MA, ht, len, str )    cudaMUQread( (uqPMatrix)(MA), ht, len, str )
#define cudaMUQ_write_buf( str, MA, ht, len, h_Wk )   cudaMUQwrite_buf( str, (uqPMatrix)(MA), ht, len, h_Wk )
#define cudaMUQ_read_buf( MA, ht, len, str, h_Wk )    cudaMUQread_buf( (uqPMatrix)(MA), ht, len, str, h_Wk )
                                   /* write and read in ascii format */
#define cudaMUQ_store( str, MA, ht, len )   cudaVUQ_store( str, (uqPMatrix)(MA), (len)*(ht) )
#define cudaMUQ_recall( MA, ht, len, str)   cudaVUQ_recall( (uqPMatrix)(MA), (len)*(ht), str)
#define cudaMUQ_store_buf( str, MA, ht, len, h_Wk )   cudaVUQ_store_buf( str, (uqPMatrix)(MA), (len)*(ht), h_Wk )
#define cudaMUQ_recall_buf( MA, ht, len, str, h_Wk)   cudaVUQ_recall_buf( (uqPMatrix)(MA), (len)*(ht), str, h_Wk )
                                  /* store and recall in binary format */

#endif /* plain-C or C++ for functions working on device memory */


/*******************  Functions working on host memory: **********************
 *                                                                           *
 *	MQIcu_func		(working on matrices in host memory, input type qiMatrix,*
 *	scalar parameters on host and passed by value)                           *
 *****************************************************************************/ 

/****************  Initialization  ****************************************/

#define MUQcu_equ0( MA, ht, len )                   VUQcu_equ0( (MA)[0], (ht)*(len) )
#define MUQcu_equ1( MA, len )                       MUQcuequ1( (MA)[0], len ) /* identity matrix */
#define MUQcu_randomLC( MA, ht, len, seed, Min, Max, state ) VUQcu_randomLC( (MA)[0], (ht)*(len), seed, Min, Max, state )
#define MUQcu_random( MA, ht, len, seed, Min, Max )          VUQcu_random( (MA)[0], (ht)*(len), seed, Min, Max )
#define MUQcu_outerprod( MA, X, Y, ht, len )        MUQcuouterprod( (MA)[0], X, Y, ht, len )
                       /* sizX=ht, sizY=len */
#define MUQcu_Row_equ0( MA, ht, len, iRow )    MUQcuRow_equ0( (MA)[0], ht, len, iRow )
#define MUQcu_Col_equ0( MA, ht, len, iCol )    MUQcuCol_equ0( (MA)[0], ht, len, iCol )
#define MUQcu_Dia_equ0( MA, len )              MUQcuDia_equ0( (MA)[0], len )
#define MUQcu_Row_equC( MA, ht, len, iRow, C ) MUQcuRow_equC( (MA)[0], ht, len, iRow, C )
#define MUQcu_Col_equC( MA, ht, len, iCol, C ) MUQcuCol_equC( (MA)[0], ht, len, iCol, C )
#define MUQcu_Dia_equC( MA, len, C )           MUQcuDia_equC( (MA)[0], len, C )

#define MUQcu_Row_equV( MA, ht, len, iRow, X ) MUQcuRow_equV( (MA)[0], ht, len, iRow, X )
#define MUQcu_Col_equV( MA, ht, len, iCol, X ) MUQcuCol_equV( (MA)[0], ht, len, iCol, X )
#define MUQcu_Dia_equV( MA, len, X )           MUQcuDia_equV( (MA)[0], len, X )

#define MUQcu_Trd_equM( MA, MTrd, len )        MUQcuTrd_equM( (MA)[0], (MTrd)[0], len )
#define MUQcu_Trd_extract( MTrd, MA, len )     MUQcuTrd_extract( (MTrd)[0], (MA)[0], len )

#define MUQcu_equM( MB, MA, ht, len )          VUQcu_equV( (MB)[0], (MA)[0], (ht)*(len) )
#define MUQcu_equMhost( MB, MA, ht, len )      VUQcu_equVhost( (MB)[0], MA[0], (ht)*(len) )

#define MUQcu_UequL( MA, len ) MUQcuUequL( (MA)[0], len )
#define MUQcu_LequU( MA, len ) MUQcuLequU( (MA)[0], len )
     /* copy lower-diagonal elements into upper-diagonal
       (or vice versa) by index-reflection, so as to get a symmetric matrix    */

            /* data-type conversions:  */
#define Mcu_QItoUQ( MUQ, MQI, ht, len ) Vcu_QItoUQ( (MUQ)[0], (MQI)[0], (ht)*(len) )
#define Mcu_UQtoQI( MQI, MUQ, ht, len ) Vcu_UQtoQI( (MQI)[0], (MUQ)[0], (ht)*(len) )
#define Mcu_UQtoUB( MUB, MUQ, ht, len ) Vcu_UQtoUB( (MUB)[0], (MUQ)[0], (ht)*(len) )
#define Mcu_UQtoUS( MUS, MUQ, ht, len ) Vcu_UQtoUS( (MUS)[0], (MUQ)[0], (ht)*(len) )
#define Mcu_UQtoU(  MU,  MUQ, ht, len ) Vcu_UQtoU(  (MU)[0],  (MUQ)[0], (ht)*(len) )
#define Mcu_UQtoUL( MUL, MUQ, ht, len ) Vcu_UQtoUL( (MUL)[0], (MUQ)[0], (ht)*(len) )
#define Mcu_UBtoUQ( MUQ, MUB, ht, len ) Vcu_UBtoUQ( (MUQ)[0], (MUB)[0], (ht)*(len) )
#define Mcu_UStoUQ( MUQ, MUS, ht, len ) Vcu_UStoUQ( (MUQ)[0], (MUS)[0], (ht)*(len) )
#define Mcu_UtoUQ(  MUQ, MU,  ht, len ) Vcu_UtoUQ(  (MUQ)[0], (MU)[0],  (ht)*(len) )
#define Mcu_ULtoUQ( MUQ, MUL, ht, len ) Vcu_ULtoUQ( (MUQ)[0], (MUL)[0], (ht)*(len) )
#define Mcu_UQtoF(  MF,  MUQ, ht, len ) Vcu_UQtoF(  (MF)[0],  (MUQ)[0], (ht)*(len) )
#define Mcu_UQtoD(  MD,  MUQ, ht, len ) Vcu_UQtoD(  (MD)[0],  (MUQ)[0], (ht)*(len) )


/********  Extracting a submatrix and copying a submatrix back  *********/

#define MUQcu_submatrix( MSub, subHt, subLen, MSrce, srceHt, srceLen, \
                      firstRowInCol, sampInCol, firstColInRow, sampInRow ) \
               MUQcusubmatrix(  (MSub)[0], subHt, subLen, \
                             (MSrce)[0], srceHt, srceLen, \
                             firstRowInCol, sampInCol, firstColInRow, sampInRow )

#define MUQcu_submatrix_equM( MDest, destHt, destLen, \
                           firstRowInCol, sampInCol, firstColInRow, sampInRow, \
                           MSrce, srceHt, srceLen ) \
               MUQcusubmatrix_equM(  (MDest)[0], destHt, destLen, \
                             firstRowInCol, sampInCol, firstColInRow, sampInRow, \
                             (MSrce)[0], srceHt, srceLen )

#define MUQcu_equMblock( MSub, subHt, subLen, MSrce, srceHt, srceLen, \
                      firstRowInCol, firstColInRow ) \
               MUQcuequMblock(  (MSub)[0], subHt, subLen, \
                             (MSrce)[0], srceHt, srceLen, \
                             firstRowInCol, firstColInRow )

#define MUQcu_block_equM( MDest, destHt, destLen, \
                       firstRowInCol, firstColInRow, \
                       MSrce, srceHt, srceLen ) \
               MUQcublock_equM( (MDest)[0], destHt, destLen, \
                             firstRowInCol, firstColInRow, \
                             (MSrce)[0], srceHt, srceLen )

#define MUQcu_equMblockT( MSub, subHt, subLen, MSrce, srceHt, srceLen, \
                      firstRowInCol, firstColInRow ) \
               MUQcuequMblockT(  (MSub)[0], subHt, subLen, \
                             (MSrce)[0], srceHt, srceLen, \
                             firstRowInCol, firstColInRow )

#define MUQcu_block_equMT( MDest, destHt, destLen, \
                       firstRowInCol, firstColInRow, \
                       MSrce, srceHt, srceLen ) \
               MUQcublock_equMT( (MDest)[0], destHt, destLen, \
                             firstRowInCol, firstColInRow, \
                             (MSrce)[0], srceHt, srceLen )

/*****   Extracting a single row or a single column or the diagonal  ******
 *       and storing it into a vector                                     */

#define MUQcu_Row_extract( Y, MA, ht, len, iRow ) MUQcuRow_extract( Y, (MA)[0], ht, len, iRow )
#define MUQcu_Col_extract( Y, MA, ht, len, iCol ) MUQcuCol_extract( Y, (MA)[0], ht, len, iCol )
#define MUQcu_Dia_extract( Y, MA, len )           MUQcuDia_extract( Y, (MA)[0], len )

/**************  Deleting or inserting a row or a column   ***************/

#define MUQcu_Row_delete( MB, MA, htA, lenA, iRow )    MUQcuRow_delete( (MB)[0], (MA)[0], htA, lenA, iRow )
#define MUQcu_Col_delete( MB, MA, htA, lenA, iCol )    MUQcuCol_delete( (MB)[0], (MA)[0], htA, lenA, iCol )
#define MUQcu_Row_insert( MB, MA, htB, lenB, iRow, X ) MUQcuRow_insert( (MB)[0], (MA)[0], htB, lenB, iRow, X )
#define MUQcu_Col_insert( MB, MA, htB, lenB, iCol, X ) MUQcuCol_insert( (MB)[0], (MA)[0], htB, lenB, iCol, X )


/******  One-dimensional vector operations **********************
         performed along all rows or all columns simultaneously,
         or along the diagonal of a square matrix                */

#define MUQcu_Rows_max( Y, MA, ht, len )        MUQcuRows_max( Y, (MA)[0], ht, len )
#define MUQcu_Cols_max( Y, MA, ht, len )        MUQcuCols_max( Y, (MA)[0], ht, len )
#define MUQcu_Dia_max(  MA, len )               MUQcuDia_max(  (MA)[0], len )
#define MUQcu_Rows_min( Y, MA, ht, len )        MUQcuRows_min( Y, (MA)[0], ht, len )
#define MUQcu_Cols_min( Y, MA, ht, len )        MUQcuCols_min( Y, (MA)[0], ht, len )
#define MUQcu_Dia_min(  MA, len )               MUQcuDia_min(  (MA)[0], len )

#define MUQcu_Rows_rotate( MA, ht, len, pos)           MUQcuRows_rotate( (MA)[0], ht, len, pos )
#define MUQcu_Cols_rotate( MA, ht, len, pos)           MUQcuCols_rotate( (MA)[0], ht, len, pos )
#define MUQcu_Rows_rotate_buf( MA, ht, len, pos, MBuf) MUQcuRows_rotate_buf( (MA)[0], ht, len, pos, (MBuf)[0] )
#define MUQcu_Cols_rotate_buf( MA, ht, len, pos, MBuf) MUQcuCols_rotate_buf( (MA)[0], ht, len, pos, (MBuf)[0] )
#define MUQcu_Rows_reflect( MA, ht, len )              MUQcuRows_reflect( (MA)[0], ht, len )
#define MUQcu_Cols_reflect( MA, ht, len )              MUQcuCols_reflect( (MA)[0], ht, len )
#define MUQcu_Rows_rev( MA, ht, len)                   MUQcuRows_rev( (MA)[0], ht, len )
#define MUQcu_Cols_rev( MA, ht, len)                   MUQcuCols_rev( (MA)[0], ht, len )
#define MUQcu_Rows_distribution( MAbund, Limits, nBins, MX, ht, len, mode ) MUQcuRows_distribution( MAbund[0], Limits, nBins, MX[0], ht, len, mode )
#define MUQcu_Cols_distribution( MAbund, Limits, nBins, MX, ht, len, mode ) MUQcuCols_distribution( MAbund[0], Limits, nBins, MX[0], ht, len, mode )

/********  Operations involving two rows or two colums of one matrix  *****/

#define MUQcu_Rows_exchange( MA, ht, len, row1, row2 ) \
                             MUQcuRows_exchange( (MA)[0], ht, len, row1, row2 )
#define MUQcu_Cols_exchange( MA, ht, len, col1, col2 ) \
                             MUQcuCols_exchange( (MA)[0], ht, len, col1, col2 )

/*************** Transposing and rotating a matrix **********************/

#define MUQcu_transpose( MTr, MA, htTr, lenTr )    MUQcutranspose( (MTr)[0], (MA)[0], htTr, lenTr )
       /*  dimensions htTr, lenTr are those of the transposed matrix, not of the original!   */
#define MUQcu_rotate90( MRot, MA, htRot, lenRot )  MUQcurotate90( (MRot)[0], (MA)[0], htRot, lenRot )
#define MUQcu_rotate180( MRot, MA, htRot, lenRot ) VUQcu_rev( (MRot)[0], (MA)[0], (htRot)*(lenRot) )
#define MUQcu_rotate270( MRot, MA, htRot, lenRot ) MUQcurotate270( (MRot)[0], (MA)[0], htRot, lenRot )


/*************************************************************************
 * MUQcu functions (without underbar in the prefix): 	
    (working on matrices in host memory, input type 
	uqPMatrix = uqVector = pointer to matrix element[0][0], 
	scalar parameters on host and passed by value)
*
 *************************************************************************/

#define MUQcuequ0( MA, ht, len )       VUQcu_equ0( MA, (ht)*(len) )
void   __vf OVCUAPI  MUQcuequ1( uqPMatrix MA, ui len );  /* identity matrix */
void   __vf OVCUAPI  MUQcuouterprod( uqPMatrix MA, uqVector X,  uqVector Y, ui ht, ui len );

void   __vf OVCUAPI  MUQcuRow_equ0( uqPMatrix MA, ui ht, ui len, ui iRow );
void   __vf OVCUAPI  MUQcuCol_equ0( uqPMatrix MA, ui ht, ui len, ui iCol );
void   __vf OVCUAPI  MUQcuDia_equ0( uqPMatrix MA, ui len );

void   __vf OVCUAPI  MUQcuRow_equC( uqPMatrix MA, ui ht, ui len, ui iRow, uquad C );
void   __vf OVCUAPI  MUQcuCol_equC( uqPMatrix MA, ui ht, ui len, ui iCol, uquad C );
void   __vf OVCUAPI  MUQcuDia_equC( uqPMatrix MA, ui len, uquad C );

void   __vf OVCUAPI  MUQcuRow_equV( uqPMatrix MA, ui ht, ui len, ui iRow, uqVector X );
void   __vf OVCUAPI  MUQcuCol_equV( uqPMatrix MA, ui ht, ui len, ui iCol, uqVector X );
void   __vf OVCUAPI  MUQcuDia_equV( uqPMatrix MA, ui len, uqVector X );

void   __vf OVCUAPI  MUQcuTrd_equM( uqPMatrix MA, uqPMatrix MTrd, ui len );
void   __vf OVCUAPI  MUQcuTrd_extract( uqPMatrix MTrd, uqPMatrix MA, ui len );

#define MUQcuequM( MB, MA, ht, len )      VUQcu_equV( MB, MA, (ht)*(len) )
void   __vf OVCUAPI  MUQcuUequL( uqPMatrix MA, ui len );
void   __vf OVCUAPI  MUQcuLequU( uqPMatrix MA, ui len );

            /* data-type conversions:  */
#define McuQItoUQ( MUQ, MQI, ht, len ) Vcu_QItoUQ( MUQ, MQI, (ht)*(len) )
#define McuUQtoQI( MQI, MUQ, ht, len ) Vcu_UQtoQI( MQI, MUQ, (ht)*(len) )
#define McuUQtoUB( MUB, MUQ, ht, len ) Vcu_UQtoUB( MUB, MUQ, (ht)*(len) )
#define McuUQtoUS( MUS, MUQ, ht, len ) Vcu_UQtoUS( MUS, MUQ, (ht)*(len) )
#define McuUQtoU(  MU,  MUQ, ht, len ) Vcu_UQtoU(  MU,  MUQ, (ht)*(len) )
#define McuUQtoUL( MUL, MUQ, ht, len ) Vcu_UQtoUL( MUL, MUQ, (ht)*(len) )
#define McuUBtoUQ( MUQ, MUB, ht, len ) Vcu_UBtoUQ( MUQ, MUB, (ht)*(len) )
#define McuUStoUQ( MUQ, MUS, ht, len ) Vcu_UStoUQ( MUQ, MUS, (ht)*(len) )
#define McuUtoUQ(  MUQ, MU,  ht, len ) Vcu_UtoUQ(  MUQ, MU,   (ht)*(len) )
#define McuULtoUQ( MUQ, MUL, ht, len ) Vcu_ULtoUQ( MUQ, MUL, (ht)*(len) )
#define McuUQtoF(  MF,  MUQ, ht, len ) Vcu_UQtoF(  MF,  MUQ, (ht)*(len) )
#define McuUQtoD(  MD,  MUQ, ht, len ) Vcu_UQtoD(  MD,  MUQ, (ht)*(len) )

/********  Extracting a submatrix and copying a submatrix back  *********/

void  __vf OVCUAPI  MUQcusubmatrix( uqPMatrix MSub, ui subHt,  ui subLen,
                          uqPMatrix MSrce, ui srceHt,  ui srceLen,
                          ui firstRowInCol,  ui sampInCol,
                          ui firstColInRow,  ui sampInRow );

void  __vf OVCUAPI  MUQcusubmatrix_equM( uqPMatrix MDest, ui destHt, ui destLen,
                               ui firstRowInCol,  ui sampInCol,
                               ui firstColInRow,  ui sampInRow,
                               uqPMatrix MSrce, ui srceHt, ui srceLen );

void  __vf OVCUAPI  MUQcuequMblock(  uqPMatrix MSub, ui subHt, ui subLen,
                          uqPMatrix MSrce, ui srceHt,  ui srceLen,
                          ui firstRowInCol,  ui firstColInRow );

void  __vf OVCUAPI  MUQcublock_equM( uqPMatrix MDest, ui destHt, ui destLen,
                          ui firstRowInCol,  ui firstColInRow,
                          uqPMatrix MSrce, ui srceHt, ui srceLen );

void  __vf OVCUAPI  MUQcuequMblockT( uqPMatrix MSub, ui subHt, ui subLen,
                          uqPMatrix MSrce, ui srceHt, ui srceLen,
                          ui firstRowInCol,  ui firstColInRow );

void  __vf OVCUAPI  MUQcublock_equMT( uqPMatrix MDest, ui destHt, ui destLen,
                          ui firstRowInCol,  ui firstColInRow,
                          uqPMatrix MSrce, ui srceHt, ui srceLen );


/*****   Extracting a single row or a single column or the diagonal  *****
 *       and storing it into a vector                                    */

void __vf OVCUAPI  MUQcuRow_extract( uqVector Y, uqPMatrix MA, ui ht, ui len, ui iRow );
void __vf OVCUAPI  MUQcuCol_extract( uqVector Y, uqPMatrix MA, ui ht, ui len, ui iCol );
void __vf OVCUAPI  MUQcuDia_extract( uqVector Y, uqPMatrix MA, ui len );

/**********  Deleting or inserting a row or a column *****************/

void __vf OVCUAPI  MUQcuRow_delete( uqPMatrix MB, uqPMatrix MA, ui htA, ui lenA, ui iRow );
void __vf OVCUAPI  MUQcuCol_delete( uqPMatrix MB, uqPMatrix MA, ui htA, ui lenA, ui iCol );
void __vf OVCUAPI  MUQcuRow_insert( uqPMatrix MB, uqPMatrix MA, ui htB, ui lenB, ui iRow, uqVector X );
void __vf OVCUAPI  MUQcuCol_insert( uqPMatrix MB, uqPMatrix MA, ui htB, ui lenB, ui iCol, uqVector X );


/******  One-dimensional vector operations **********************
         performed along all rows or all columns simultaneously,
         or along the diagonal of a square matrix                */

void   __vf OVCUAPI  MUQcuRows_max( uqVector Y, uqPMatrix MA, ui ht, ui len );
void   __vf OVCUAPI  MUQcuCols_max( uqVector Y, uqPMatrix MA, ui ht, ui len );
uquad  __vf OVCUAPI  MUQcuDia_max(  uqPMatrix MA, ui len );
void   __vf OVCUAPI  MUQcuRows_min( uqVector Y, uqPMatrix MA, ui ht, ui len );
void   __vf OVCUAPI  MUQcuCols_min( uqVector Y, uqPMatrix MA, ui ht, ui len );
uquad  __vf OVCUAPI  MUQcuDia_min(  uqPMatrix MA, ui len );

void  __vf OVCUAPI  MUQcuRows_rotate( uqPMatrix MA, ui ht, ui len, ssize_t pos );
void  __vf OVCUAPI  MUQcuCols_rotate( uqPMatrix MA, ui ht, ui len, ssize_t pos );
void  __vf OVCUAPI  MUQcuRows_rotate_buf( uqPMatrix MA, ui ht, ui len, ssize_t pos, uqPMatrix MBuf );
void  __vf OVCUAPI  MUQcuCols_rotate_buf( uqPMatrix MA, ui ht, ui len, ssize_t pos, uqPMatrix MBuf );
void  __vf OVCUAPI  MUQcuRows_reflect( uqPMatrix MA, ui ht, ui len );
void  __vf OVCUAPI  MUQcuCols_reflect( uqPMatrix MA, ui ht, ui len );
void  __vf OVCUAPI  MUQcuRows_rev( uqPMatrix MA, ui ht, ui len );
void  __vf OVCUAPI  MUQcuCols_rev( uqPMatrix MA, ui ht, ui len );
void  __vf OVCUAPI  MUQcuRows_distribution( uiPMatrix MAbund, uqVector Limits, ui nBins, uqPMatrix MX, ui ht, ui len, int mode );
void  __vf OVCUAPI  MUQcuCols_distribution( uiPMatrix MAbund, uqVector Limits, ui nBins, uqPMatrix MX, ui ht, ui len, int mode );

/********  Operations involving two rows or two colums of one matrix  *****/

void   __vf OVCUAPI  MUQcuRows_exchange( uqPMatrix MA, ui ht, ui len, ui i1, ui i2 );
void   __vf OVCUAPI  MUQcuCols_exchange( uqPMatrix MA, ui ht, ui len, ui i1, ui i2 );


/***************  Transposing and rotating a matrix **********************/

void  __vf OVCUAPI  MUQcutranspose( uqPMatrix MTr, uqPMatrix MA,  ui htTr, ui lenTr );
void  __vf OVCUAPI  MUQcurotate90(  uqPMatrix MRot, uqPMatrix MA, ui htRot, ui lenRot );
#define     MUQcurotate180( MRot, MA, htRot, lenRot )  VUQcu_rev( MRot, MA, (htRot)*(lenRot) )
void  __vf OVCUAPI  MUQcurotate270( uqPMatrix MRot, uqPMatrix MA, ui htRot, ui lenRot );



#ifdef __cplusplus
} // end of extern "C"
#endif
#endif  /*  __MUQSTD_H  */
#endif  /* _WIN64 */