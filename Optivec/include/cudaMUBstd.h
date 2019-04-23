/*  cudaMUBstd.h

  matrix management functions:
  manipulations on matrices of data type "unsigned char" 
  (byte-sized unsigned integers)

  This file declares the functions with the name variants 
	cudaMUB_func	(working on matrices in device memory, input type ubMatrix, scalar parameters reside on host and are passed by value)
	cusdMUB_func	(as cudaMUB_func except scalar parameters reside on device and are passed by address)
	cudaMUBfunc		(as cudaMUB_func, but input type ubPMatrix = ubVector = pointer to matrix element[0][0])
	cusdMUBfunc		(as cusdMUB_func, but input type ubPMatrix = ubVector = pointer to matrix element[0][0])
	MUBcu_func		(working on matrices in host memory, input type ubMatrix, scalar parameters on host and passed by value)
	MUBcufunc		(as MUBcu_func, but input type ubPMatrix = ubVector = pointer to matrix element[0][0])
  where func is the respective function.

   Copyright (c) 1996-2017 by OptiCode - Dr. Martin Sander Software Dev.
  All Rights Reserved.

*/

#if !defined( __CUDAMUBSTD_H )
#define __CUDAMUBSTD_H
#if !defined( __CUDAMATLIB_H )
#include <cudaMatLib.h>
#endif
#if !defined( __CUDAVUBSTD_H )
#include <cudaVUBstd.h>
#endif
#if !defined( __CUDAVUBMATH_H )
#include <cudaVUBmath.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif

/**** Generation of matrices on device memory and on pinned host memory *******************/

ubMatrix  __vf cudaMUB_matrix( ui ht, ui len );   /* allocates a vector on device memory */
ubMatrix  __vf cudaMUB_matrix0( ui ht, ui len );
 /* The following functions allocate device-accessible, "pinned" memory on the host.
	This memory is mapped onto the device memory space. The resulting device address is returned.
	The matrix can be accessed either by its host address "hostPtr" e.g., MUB_equ1( hostPtr, ht, len );
	or by its device address , e.g., cudaMUB_equ1( devicePtr, ht, len );                             */
ubMatrix  __vf cudaMUB_pinnedMatrix(  ubMatrix *hostPtr, ui ht, ui len ); 
ubMatrix  __vf cudaMUB_pinnedMatrix0( ubMatrix *hostPtr, ui ht, ui len );

/*************************************************************************
 * Declarations of the functions written without underbar in the prefix: *
 *	cudaMUBfunc  (input type 
                   ubPMatrix = ubVector = pointer to matrix element[0][0])
 *	cusdMUBfunc  (input type 
                   ubPMatrix = ubVector = pointer to matrix element[0][0])
 *************************************************************************/


void  __vcuf OVCUAPI  cudaMUBsetElement( ubPMatrix X, ui ht, ui len, ui m, ui n, unsigned char C );
void  __vcuf OVCUAPI  cusdMUBsetElement( ubPMatrix X, ui ht, ui len, ui m, ui n, unsigned char *d_C );
void  __vcuf OVCUAPI  cudaMUBgetElement( unsigned char *h_y, ubPMatrix X, ui ht, ui len, ui m, ui n );
void  __vcuf OVCUAPI  cusdMUBgetElement( unsigned char *d_y, ubPMatrix X, ui ht, ui len, ui m, ui n );
unsigned char * __vcuf OVCUAPI  cudaMUBPelement( ubPMatrix X, ui ht, ui len, ui m, ui n );
unsigned char   __vcuf OVCUAPI  cudaMUBelement(  ubPMatrix X, ui ht, ui len, ui m, ui n );

#define cudaMUBequ0( MA, ht, len )            cudaVUB_equ0( MA, (ht)*(len) )
overror_t   __vcuf OVCUAPI  cudaMUBequ1( ubPMatrix MA, ui len );  /* identity matrix */
overror_t   __vcuf OVCUAPI  cudaMUBouterprod( ubPMatrix MA, ubVector X,  ubVector Y, ui ht, ui len );

overror_t   __vcuf OVCUAPI  cudaMUBRow_equ0( ubPMatrix MA, ui ht, ui len, ui iRow );
overror_t   __vcuf OVCUAPI  cudaMUBCol_equ0( ubPMatrix MA, ui ht, ui len, ui iCol );
overror_t   __vcuf OVCUAPI  cudaMUBDia_equ0( ubPMatrix MA, ui len );

overror_t   __vcuf OVCUAPI  cudaMUBRow_equC( ubPMatrix MA, ui ht, ui len, ui iRow, unsigned char C );
overror_t   __vcuf OVCUAPI  cudaMUBCol_equC( ubPMatrix MA, ui ht, ui len, ui iCol, unsigned char C );
overror_t   __vcuf OVCUAPI  cudaMUBDia_equC( ubPMatrix MA, ui len, unsigned char C );
overror_t   __vcuf OVCUAPI  cusdMUBRow_equC( ubPMatrix MA, ui ht, ui len, ui iRow, unsigned char *d_C );
overror_t   __vcuf OVCUAPI  cusdMUBCol_equC( ubPMatrix MA, ui ht, ui len, ui iCol, unsigned char *d_C );
overror_t   __vcuf OVCUAPI  cusdMUBDia_equC( ubPMatrix MA, ui len, unsigned char *d_C );

overror_t   __vcuf OVCUAPI  cudaMUBRow_equV( ubPMatrix MA, ui ht, ui len, ui iRow, ubVector X );
overror_t   __vcuf OVCUAPI  cudaMUBCol_equV( ubPMatrix MA, ui ht, ui len, ui iCol, ubVector X );
overror_t   __vcuf OVCUAPI  cudaMUBDia_equV( ubPMatrix MA, ui len, ubVector X );

overror_t   __vcuf OVCUAPI  cudaMUBTrd_equM( ubPMatrix MA, ubPMatrix MTrd, ui len );
overror_t   __vcuf OVCUAPI  cudaMUBTrd_extract( ubPMatrix MTrd, ubPMatrix MA, ui len );

#define cudaMUBequM( MB, MA, ht, len )  cudaVUB_equV( MB, MA, (ht)*(len) )
#define cudaMUBequMhost( MB, MA, ht, len )  cudaVUB_equVhost( MB, MA, (ht)*(len) )
#define MUBequMdevice( MB, MA, ht, len )    VUB_equVdevice( MB, MA, (ht)*(len) )
overror_t   __vcuf OVCUAPI  cudaMUBUequL( ubPMatrix MA, ui len );
overror_t   __vcuf OVCUAPI  cudaMUBLequU( ubPMatrix MA, ui len );

            /* data-type conversions:  */
#define cudaMBItoUB( MUB, MBI, ht, len ) cudaV_BItoUB( (MUB), (MBI), (ht)*(len) )
#define cudaMUBtoBI( MBI, MUB, ht, len ) cudaV_UBtoBI( (MBI), (MUB), (ht)*(len) )
#define cudaMUBtoUS( MUS, MUB, ht, len ) cudaV_UBtoUS( (MUS), (MUB), (ht)*(len) )
#define cudaMUBtoU(  MU,  MUB, ht, len ) cudaV_UBtoU(  (MU),  (MUB), (ht)*(len) )
#define cudaMUBtoUL( MUL, MUB, ht, len ) cudaV_UBtoUL( (MUL), (MUB), (ht)*(len) )
#define cudaMUStoUB( MUB, MUS, ht, len ) cudaV_UStoUB( (MUB), (MUS), (ht)*(len) )
#define cudaMUtoUB(  MUB, MU,  ht, len ) cudaV_UtoUB(  (MUB), (MU),  (ht)*(len) )
#define cudaMULtoUB( MUB, MUL, ht, len ) cudaV_ULtoUB( (MUB), (MUL), (ht)*(len) )
#ifdef _WIN64
	#define cudaMUBtoUQ( MUQ, MUB, ht, len ) cudaV_UBtoUQ( (MUQ), (MUB), (ht)*(len) )
	#define cudaMUQtoUB( MUB, MUQ, ht, len ) cudaV_UQtoUB( (MUB), (MUQ), (ht)*(len) )
#endif
#define cudaMUBtoF(  MF,  MUB, ht, len ) cudaV_UBtoF(  (MF),  (MUB), (ht)*(len) )
#define cudaMUBtoD(  MD,  MUB, ht, len ) cudaV_UBtoD(  (MD),  (MUB), (ht)*(len) )

/********  Extracting a submatrix and copying a submatrix back  *********/

overror_t  __vcuf OVCUAPI  cudaMUBsubmatrix( ubPMatrix MSub,  ui subHt,  ui subLen,
                          ubPMatrix MSrce, ui srceHt,  ui srceLen,
                          ui firstRowInCol,  ui sampInCol,
                          ui firstColInRow,  ui sampInRow );

overror_t  __vcuf OVCUAPI  cudaMUBsubmatrix_equM( ubPMatrix MDest, ui destHt, ui destLen,
                               ui firstRowInCol,  ui sampInCol,
                               ui firstColInRow,  ui sampInRow,
                               ubPMatrix MSrce, ui srceHt, ui srceLen );

overror_t  __vcuf OVCUAPI  cudaMUBequMblock(  ubPMatrix MSub, ui subHt, ui subLen,
                          ubPMatrix MSrce, ui srceHt,  ui srceLen,
                          ui firstRowInCol,  ui firstColInRow );

overror_t  __vcuf OVCUAPI  cudaMUBblock_equM( ubPMatrix MDest, ui destHt, ui destLen,
                          ui firstRowInCol,  ui firstColInRow,
                          ubPMatrix MSrce,  ui srceHt, ui srceLen );

overror_t  __vcuf OVCUAPI  cudaMUBequMblockT( ubPMatrix MSub, ui subHt, ui subLen,
                          ubPMatrix MSrce, ui srceHt, ui srceLen,
                          ui firstRowInCol,  ui firstColInRow );

overror_t  __vcuf OVCUAPI  cudaMUBblock_equMT( ubPMatrix MDest, ui destHt, ui destLen,
                          ui firstRowInCol,  ui firstColInRow,
                          ubPMatrix MSrce, ui srceHt, ui srceLen );


/*****   Extracting a single row or a single column or the diagonal  *****
 *       and storing it into a vector                                    */

overror_t __vcuf OVCUAPI  cudaMUBRow_extract( ubVector Y, ubPMatrix MA, ui ht, ui len, ui iRow );
overror_t __vcuf OVCUAPI  cudaMUBCol_extract( ubVector Y, ubPMatrix MA, ui ht, ui len, ui iCol );
overror_t __vcuf OVCUAPI  cudaMUBDia_extract( ubVector Y, ubPMatrix MA, ui len );


/**********  Deleting or inserting a row or a column *****************/

overror_t __vcuf OVCUAPI  cudaMUBRow_delete( ubPMatrix MB, ubPMatrix MA, ui htA, ui lenA, ui iRow );
overror_t __vcuf OVCUAPI  cudaMUBCol_delete( ubPMatrix MB, ubPMatrix MA, ui htA, ui lenA, ui iCol );
overror_t __vcuf OVCUAPI  cudaMUBRow_insert( ubPMatrix MB, ubPMatrix MA, ui htB, ui lenB, ui iRow, ubVector X );
overror_t __vcuf OVCUAPI  cudaMUBCol_insert( ubPMatrix MB, ubPMatrix MA, ui htB, ui lenB, ui iCol, ubVector X );


/******  One-dimensional vector operations **********************
         performed along all rows or all columns simultaneously,
         or along the diagonal of a square matrix                */

overror_t  __vcuf OVCUAPI  cudaMUBRows_max( ubVector Y, ubPMatrix MA, ui ht, ui len );
overror_t  __vcuf OVCUAPI  cudaMUBCols_max( ubVector Y, ubPMatrix MA, ui ht, ui len );
overror_t  __vcuf OVCUAPI  cudaMUBDia_max(  unsigned char *h_RetVal, ubPMatrix MA, ui len );
overror_t  __vcuf OVCUAPI  cusdMUBDia_max(  unsigned char *d_RetVal, ubPMatrix MA, ui len );
overror_t  __vcuf OVCUAPI  cudaMUBRows_min( ubVector Y, ubPMatrix MA, ui ht, ui len );
overror_t  __vcuf OVCUAPI  cudaMUBCols_min( ubVector Y, ubPMatrix MA, ui ht, ui len );
overror_t   __vcuf OVCUAPI  cudaMUBDia_min(  unsigned char *h_RetVal, ubPMatrix MA, ui len );
overror_t   __vcuf OVCUAPI  cusdMUBDia_min(  unsigned char *d_RetVal, ubPMatrix MA, ui len );

overror_t  __vcuf OVCUAPI  cudaMUBRows_rotate( ubPMatrix MA, ui ht, ui len, ssize_t pos );
overror_t  __vcuf OVCUAPI  cudaMUBCols_rotate( ubPMatrix MA, ui ht, ui len, ssize_t pos );
overror_t  __vcuf OVCUAPI  cudaMUBRows_rotate_buf( ubPMatrix MA, ui ht, ui len, ssize_t pos, ubPMatrix MBuf );
overror_t  __vcuf OVCUAPI  cudaMUBCols_rotate_buf( ubPMatrix MA, ui ht, ui len, ssize_t pos, ubPMatrix MBuf );
overror_t  __vcuf OVCUAPI  cudaMUBRows_reflect( ubPMatrix MA, ui ht, ui len );
overror_t  __vcuf OVCUAPI  cudaMUBCols_reflect( ubPMatrix MA, ui ht, ui len );
overror_t  __vcuf OVCUAPI  cudaMUBRows_rev( ubPMatrix MA, ui ht, ui len );
overror_t  __vcuf OVCUAPI  cudaMUBCols_rev( ubPMatrix MA, ui ht, ui len );
overror_t  __vcuf OVCUAPI  cudaMUBRows_distribution( uiPMatrix MAbund, ubVector Limits, ui nBins, ubPMatrix MX, ui ht, ui len, int mode );
overror_t  __vcuf OVCUAPI  cudaMUBCols_distribution( uiPMatrix MAbund, ubVector Limits, ui nBins, ubPMatrix MX, ui ht, ui len, int mode );

/********  Operations involving two rows or two colums of one matrix  *****/

overror_t   __vcuf OVCUAPI  cudaMUBRows_exchange( ubPMatrix MA, ui ht, ui len, ui i1, ui i2 );
overror_t   __vcuf OVCUAPI  cudaMUBCols_exchange( ubPMatrix MA, ui ht, ui len, ui i1, ui i2 );

/****************  Transposing and rotating a matrix **********************/

overror_t  __vcuf OVCUAPI  cudaMUBtranspose( ubPMatrix MTr, ubPMatrix MA, ui htTr, ui lenTr );
overror_t  __vcuf OVCUAPI  cudaMUBrotate90(  ubPMatrix MRot, ubPMatrix MA, ui htRot, ui lenRot );
#define       cudaMUBrotate180( MRot, MA, htRot, lenRot ) cudaVUB_rev( MRot, MA, (htRot)*(lenRot) )
overror_t  __vcuf OVCUAPI  cudaMUBrotate270( ubPMatrix MRot, ubPMatrix MA, ui htRot, ui lenRot );
overror_t  __vcuf OVCUAPI  cudaMUBtranspose_buf( ubPMatrix MTr, ubPMatrix MA, ui htTr, ui lenTr, ubPMatrix MBuf );

/**************************  Input and Output  **************************
	The input/output functions involve memory transfers from device
	to host memory or vice versa. The generic cudaMUB_input/output functions
	allocate their own host buffers, whereas the cudaMUB_xxx_buf functions
	take a user-supplied buffer vector h_Wk (size must be >= ht*len )
	and are much more efficient.                                       */

#define cudaMUBprint( MA, ht, len )  cudaMUBfprint( stdout, MA, ht, len, 80 )
overror_t __vf cudaMUBfprint( FILE *stream, ubPMatrix MA, ui ht, ui len, unsigned linewidth );
overror_t __vf cudaMUBcprint( ubPMatrix MA, ui ht, ui len );
#define cudaMUBprint_buf( MA, ht, len, h_Wk )  cudaMUBfprint_buf( stdout, MA, ht, len, 80, h_Wk )
overror_t __vf cudaMUBfprint_buf( FILE *stream, ubPMatrix MA, ui ht, ui len, unsigned linewidth, ubVector h_Wk );
overror_t __vf cudaMUBcprint_buf( ubPMatrix MA, ui ht, ui len, ubVector h_Wk );
overror_t __vf cudaMUBwrite( FILE *stream, ubPMatrix X, ui ht, ui len  );
overror_t __vf cudaMUBread( ubPMatrix X, ui ht, ui len, FILE *stream );
overror_t __vf cudaMUBwrite_buf( FILE *stream, ubPMatrix X, ui ht, ui len, ubVector h_Wk );
overror_t __vf cudaMUBread_buf( ubPMatrix X, ui ht, ui len, FILE *stream, ubVector h_Wk );
#define cudaMUBstore( str, MA, ht, len ) cudaVUB_store( str, MA, (len)*(ht) )
#define cudaMUBrecall( MA, ht, len, str) cudaVUB_recall( MA, (len)*(ht), str)
#define cudaMUBstore_buf( str, MA, ht, len, h_Wk ) cudaVUB_store( str, MA, (len)*(ht), h_Wk )
#define cudaMUBrecall_buf( MA, ht, len, str, h_Wk) cudaVUB_recall( MA, (len)*(ht), str, h_Wk)




/***************************************************************************
    cudaMUB_func	(working on matrices in device memory, input type biMatrix, 
	             scalar parameters reside on host and are passed by value)
    cusdMUB_func	(as cudaMUB_func except scalar parameters reside on device 
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

inline void    cudaMUB_setElement( ubMatrix MA, ui ht, ui len, ui m, ui n, unsigned char C )
	{	cudaMUBsetElement( (ubPMatrix)(MA), ht, len, m, n, C );}
inline void    cusdMUB_setElement( ubMatrix MA, ui ht, ui len, ui m, ui n, unsigned char *d_C )
	{	cusdMUBsetElement( (ubPMatrix)(MA), ht, len, m, n, d_C );}
inline void    cudaMUB_getElement( unsigned char *y, ubMatrix MA, ui ht, ui len, ui m, ui n )
	{	cudaMUBgetElement( y, (ubPMatrix)(MA), ht, len, m, n );}
inline void    cusdMUB_getElement( unsigned char *d_y, ubMatrix MA, ui ht, ui len, ui m, ui n )
	{	cusdMUBgetElement( d_y, (ubPMatrix)(MA), ht, len, m, n );}
inline unsigned char * cudaMUB_Pelement( ubMatrix MA, ui ht, ui len, ui m, ui n )
	{	return cudaMUBPelement( (ubPMatrix)(MA), ht, len, m, n );}
inline unsigned char   cudaMUB_element( ubMatrix MA, ui ht, ui len, ui m, ui n )
{	return cudaMUBelement( (ubPMatrix)(MA), ht, len, m, n );}

inline overror_t  cudaMUB_equ0( ubMatrix MA, ui ht, ui len )
	{	return cudaVUB_equ0( (ubPMatrix)MA, (ht)*(len) ); }
inline overror_t  cudaMUB_equ1( ubMatrix MA, ui len )
	{	return cudaMUBequ1( (ubPMatrix)(MA), len );} /* identity matrix */

inline overror_t  cudaMUB_randomLC( ubMatrix MA, ui ht, ui len, long seed, unsigned char MinVal, unsigned char MaxVal, V_RANDOMLCSTATE *h_state )
	{	return cudaVUB_randomLC( (ubPMatrix)(MA), (ht)*(len), seed, MinVal, MaxVal, h_state );}
inline overror_t  cudaMUB_random( ubMatrix MA, ui ht, ui len, long seed, unsigned char MinVal, unsigned char MaxVal )
	{	return cudaVUB_random( (ubPMatrix)(MA), (ht)*(len), seed, MinVal, MaxVal );}
inline overror_t  cusdMUB_randomLC( ubMatrix MA, ui ht, ui len, long seed, unsigned char *d_MinVal, unsigned char *d_MaxVal, V_RANDOMLCSTATE *h_state )
	{	return cusdVUB_randomLC( (ubPMatrix)(MA), (ht)*(len), seed, d_MinVal, d_MaxVal, h_state );}
inline overror_t  cusdMUB_random( ubMatrix MA, ui ht, ui len, long seed, unsigned char *d_MinVal, unsigned char *d_MaxVal )
	{	return cusdVUB_random( (ubPMatrix)(MA), (ht)*(len), seed, d_MinVal, d_MaxVal );}
inline overror_t  cudaMUB_outerprod( ubMatrix MA, ubVector X,  ubVector Y, ui ht, ui len )
{	return cudaMUBouterprod( (ubPMatrix)(MA), X, Y, ht, len );}

inline overror_t  cudaMUB_Row_equ0( ubMatrix MA, ui ht, ui len, ui iRow )
	{	return cudaMUBRow_equ0( (ubPMatrix)MA, ht, len, iRow );}
inline overror_t  cudaMUB_Col_equ0( ubMatrix MA, ui ht, ui len, ui iRow )
	{	return cudaMUBCol_equ0( (ubPMatrix)MA, ht, len, iRow );}
inline overror_t  cudaMUB_Dia_equ0( ubMatrix MA, ui len )
	{	return cudaMUBDia_equ0( (ubPMatrix)(MA), len );}

inline overror_t  cudaMUB_Row_equC( ubMatrix MA, ui ht, ui len, ui iRow, unsigned char C )
	{	return cudaMUBRow_equC( (ubPMatrix)MA, ht, len, iRow, C );}
inline overror_t  cudaMUB_Col_equC( ubMatrix MA, ui ht, ui len, ui iRow, unsigned char C )
	{	return cudaMUBCol_equC( (ubPMatrix)MA, ht, len, iRow, C );}
inline overror_t  cudaMUB_Dia_equC( ubMatrix MA, ui len, unsigned char C )
	{	return cudaMUBDia_equC( (ubPMatrix)(MA), len, C );}

inline overror_t  cusdMUB_Row_equC( ubMatrix MA, ui ht, ui len, ui iRow, unsigned char *d_C )
	{	return cusdMUBRow_equC( (ubPMatrix)MA, ht, len, iRow, d_C );}
inline overror_t  cusdMUB_Col_equC( ubMatrix MA, ui ht, ui len, ui iRow, unsigned char *d_C )
	{	return cusdMUBCol_equC( (ubPMatrix)MA, ht, len, iRow, d_C );}
inline overror_t  cusdMUB_Dia_equC( ubMatrix MA, ui len, unsigned char *d_C )
	{	return cusdMUBDia_equC( (ubPMatrix)(MA), len, d_C );}

inline overror_t  cudaMUB_Row_equV( ubMatrix MA, ui ht, ui len, ui iRow, ubVector X )
	{	return cudaMUBRow_equV( (ubPMatrix)MA, ht, len, iRow, X );}
inline overror_t  cudaMUB_Col_equV( ubMatrix MA, ui ht, ui len, ui iRow, ubVector X )
	{	return cudaMUBCol_equV( (ubPMatrix)MA, ht, len, iRow, X );}
inline overror_t  cudaMUB_Dia_equV( ubMatrix MA, ui len, ubVector X )
	{	return cudaMUBDia_equV( (ubPMatrix)(MA), len, X );}

inline overror_t  cudaMUB_Trd_equM( ubMatrix MA, ubMatrix MTrd, ui len )
	{	return cudaMUBTrd_equM( (ubPMatrix)(MA), (ubPMatrix)(MTrd), len );}
inline overror_t  cudaMUB_Trd_extract( ubMatrix MTrd, ubMatrix MA, ui len )
	{	return cudaMUBTrd_extract( (ubPMatrix)(MTrd), (ubPMatrix)(MA), len );}

inline overror_t cudaMUB_equM( ubMatrix MB, ubMatrix MA, ui ht, ui len )
	{	return cudaVUB_equV( (ubPMatrix)MB, (ubPMatrix)MA, (ht)*(len) );}
inline overror_t cudaMUB_equMhost( ubMatrix d_MB, ubMatrix h_MA, ui ht, ui len )
	{	return cudaVUB_equVhost( (ubPMatrix)d_MB, (h_MA)[0], (ht)*(len) );}
inline overror_t MUB_equMdevice( ubMatrix h_MB, ubMatrix d_MA, ui ht, ui len )
	{	return VUB_equVdevice( h_MB[0], (ubPMatrix)d_MA, (ht)*(len) );}
inline overror_t  cudaMUB_UequL( ubMatrix MA, ui len )
	{	return cudaMUBUequL( (ubPMatrix)(MA), len );}
inline overror_t  cudaMUB_LequU( ubMatrix MA, ui len )
	{	return cudaMUBLequU( (ubPMatrix)(MA), len );}

/************** Data-type interconversions  ****************************/

inline overror_t cudaM_BItoUB( ubMatrix MUB, biMatrix MBI, ui ht, ui len )
	{	return cudaV_BItoUB( (ubVector)MUB, (biVector)MBI, (ht)*(len) );}
inline overror_t cudaM_UStoUB( ubMatrix MUB, usMatrix MUS, ui ht, ui len )
	{	return cudaV_UStoUB( (ubVector)MUB, (usVector)MUS, (ht)*(len) );}
inline overror_t cudaM_UtoUB(  ubMatrix MUB, uMatrix MU,  ui ht, ui len )
	{	return cudaV_UtoUB(  (ubVector)MUB, (uVector)MU,   (ht)*(len) );}
inline overror_t cudaM_ULtoUB( ubMatrix MUB, ulMatrix MUL, ui ht, ui len )
	{	return cudaV_ULtoUB( (ubVector)MUB, (ulVector)MUL, (ht)*(len) );}
#ifdef _WIN64
	inline overror_t cudaM_UQtoUB( ubMatrix MUB, uqMatrix MUQ, ui ht, ui len )
		{	return cudaV_UQtoUB( (ubVector)MUB, (uqVector)MUQ, (ht)*(len) );}
#endif
inline overror_t cudaM_UBtoF(  fMatrix MF,  ubMatrix MUB, ui ht, ui len )
	{	return cudaV_UBtoF(  (fVector)MF,   (ubVector)MUB, (ht)*(len) );}
inline overror_t cudaM_UBtoD(  dMatrix MD,  ubMatrix MUB, ui ht, ui len )
	{	return cudaV_UBtoD(  (dVector)MD,   (ubVector)MUB, (ht)*(len) );}

/********  Extracting a submatrix and copying a submatrix back  *********/

inline overror_t cudaMUB_submatrix( ubMatrix MSub, ui subHt, ui subLen, ubMatrix MSrce, ui srceHt, ui srceLen,
                      ui firstRowInCol, ui sampInCol, ui firstColInRow, ui sampInRow )
	{	return cudaMUBsubmatrix(  (ubPMatrix)(MSub), subHt, subLen,
		                         (ubPMatrix)(MSrce), srceHt, srceLen,
								 firstRowInCol, sampInCol, firstColInRow, sampInRow ); }

inline overror_t cudaMUB_submatrix_equM( ubMatrix MDest, ui destHt, ui destLen,
                           ui firstRowInCol, ui sampInCol, ui firstColInRow, ui sampInRow,
                           ubMatrix MSrce, ui srceHt, ui srceLen )
	{	return cudaMUBsubmatrix_equM(  (ubPMatrix)(MDest), destHt, destLen,
                             firstRowInCol, sampInCol, firstColInRow, sampInRow,
							 (ubPMatrix)(MSrce), srceHt, srceLen );}

inline overror_t cudaMUB_equMblock( ubMatrix MSub, ui subHt, ui subLen, ubMatrix MSrce, ui srceHt, ui srceLen,
                      ui firstRowInCol, ui firstColInRow )
{	return cudaMUBequMblock(  (ubPMatrix)(MSub), subHt, subLen,
						   (ubPMatrix)(MSrce), srceHt, srceLen, firstRowInCol, firstColInRow );}

inline overror_t cudaMUB_block_equM( ubMatrix MDest, ui destHt, ui destLen,
                       ui firstRowInCol, ui firstColInRow,
                       ubMatrix MSrce, ui srceHt, ui srceLen )
	{	return cudaMUBblock_equM( (ubPMatrix)(MDest), destHt, destLen,
                             firstRowInCol, firstColInRow,
							 (ubPMatrix)(MSrce), srceHt, srceLen );}

inline overror_t cudaMUB_equMblockT( ubMatrix MSub, ui subHt, ui subLen, ubMatrix MSrce, ui srceHt, ui srceLen,
                      ui firstRowInCol, ui firstColInRow )
	{	return cudaMUBequMblockT(  (ubPMatrix)(MSub), subHt, subLen,
                             (ubPMatrix)(MSrce), srceHt, srceLen,
							 firstRowInCol, firstColInRow );}

inline overror_t cudaMUB_block_equMT( ubMatrix MDest, ui destHt, ui destLen,
                       ui firstRowInCol, ui firstColInRow,
                       ubMatrix MSrce, ui srceHt, ui srceLen )
	{	return cudaMUBblock_equMT( (ubPMatrix)(MDest), destHt, destLen,
                             firstRowInCol, firstColInRow,
							 (ubPMatrix)(MSrce), srceHt, srceLen );}

/*****   Extracting a single row or a single column or the diagonal  ******
 *       and storing it into a vector                                     */

inline overror_t cudaMUB_Row_extract( ubVector Y, ubMatrix MA, ui ht, ui len, ui iRow ) 
	{	return cudaMUBRow_extract( Y, (ubPMatrix)(MA), ht, len, iRow );}
inline overror_t cudaMUB_Col_extract( ubVector Y, ubMatrix MA, ui ht, ui len, ui iCol ) 
	{	return cudaMUBCol_extract( Y, (ubPMatrix)(MA), ht, len, iCol );}
inline overror_t cudaMUB_Dia_extract( ubVector Y, ubMatrix MA, ui len )
	{	return cudaMUBDia_extract( Y, (ubPMatrix)(MA), len );}

/**************  Deleting or inserting a row or a column   ***************/

inline overror_t cudaMUB_Row_delete( ubMatrix MB, ubMatrix MA, ui htA, ui lenA, ui iRow )
	{	return cudaMUBRow_delete( (ubPMatrix)(MB), (ubPMatrix)(MA), htA, lenA, iRow );}
inline overror_t cudaMUB_Col_delete( ubMatrix MB, ubMatrix MA, ui htA, ui lenA, ui iCol )
	{	return cudaMUBCol_delete( (ubPMatrix)(MB), (ubPMatrix)(MA), htA, lenA, iCol );}
inline overror_t cudaMUB_Row_insert( ubMatrix MB, ubMatrix MA, ui htB, ui lenB, ui iRow, ubVector X )
	{	return cudaMUBRow_insert( (ubPMatrix)(MB), (ubPMatrix)(MA), htB, lenB, iRow, X );}
inline overror_t cudaMUB_Col_insert( ubMatrix MB, ubMatrix MA, ui htB, ui lenB, ui iCol, ubVector X )
	{	return cudaMUBCol_insert( (ubPMatrix)(MB), (ubPMatrix)(MA), htB, lenB, iCol, X );}


/******  One-dimensional vector operations **********************
         performed along all rows or all columns simultaneously,
         or along the diagonal of a square matrix                */

inline overror_t cudaMUB_Rows_max( ubVector Y, ubMatrix MA, ui ht, ui len )
	{	return cudaMUBRows_max( Y, (ubPMatrix)(MA), ht, len );}
inline overror_t cudaMUB_Cols_max( ubVector Y, ubMatrix MA, ui ht, ui len )
	{	return cudaMUBCols_max( Y, (ubPMatrix)(MA), ht, len );}
inline overror_t cudaMUB_Dia_max(  unsigned char *h_RetValPtr, ubMatrix MA, ui len )
	{	return cudaMUBDia_max(  h_RetValPtr, (ubPMatrix)(MA), len );}
inline overror_t cusdMUB_Dia_max(  unsigned char *d_RetValPtr, ubMatrix MA, ui len )
	{	return cusdMUBDia_max(  d_RetValPtr, (ubPMatrix)(MA), len );}
inline overror_t cudaMUB_Rows_min( ubVector Y, ubMatrix MA, ui ht, ui len )
	{	return cudaMUBRows_min( Y, (ubPMatrix)(MA), ht, len );}
inline overror_t cudaMUB_Cols_min( ubVector Y, ubMatrix MA, ui ht, ui len )
	{	return cudaMUBCols_min( Y, (ubPMatrix)(MA), ht, len );}
inline overror_t cudaMUB_Dia_min(  unsigned char *h_RetValPtr, ubMatrix MA, ui len )
	{	return cudaMUBDia_min(  h_RetValPtr, (ubPMatrix)(MA), len );}
inline overror_t cusdMUB_Dia_min(  unsigned char *d_RetValPtr, ubMatrix MA, ui len )
	{	return cusdMUBDia_min(  d_RetValPtr, (ubPMatrix)(MA), len );}

inline overror_t cudaMUB_Rows_rotate( ubMatrix MA, ui ht, ui len, ssize_t pos)
	{	return cudaMUBRows_rotate( (ubPMatrix)(MA), ht, len, pos );}
inline overror_t cudaMUB_Cols_rotate( ubMatrix MA, ui ht, ui len, ssize_t pos)
	{	return cudaMUBCols_rotate( (ubPMatrix)(MA), ht, len, pos );}
inline overror_t cudaMUB_Rows_rotate_buf( ubMatrix MA, ui ht, ui len, ssize_t pos, ubMatrix MBuf) 
	{	return cudaMUBRows_rotate_buf( (ubPMatrix)(MA), ht, len, pos, (ubPMatrix)(MBuf) );}
inline overror_t cudaMUB_Cols_rotate_buf( ubMatrix MA, ui ht, ui len, ssize_t pos, ubMatrix MBuf) 
	{	return cudaMUBCols_rotate_buf( (ubPMatrix)(MA), ht, len, pos, (ubPMatrix)(MBuf) );}
inline overror_t cudaMUB_Rows_reflect( ubMatrix MA, ui ht, ui len )
	{	return cudaMUBRows_reflect( (ubPMatrix)(MA), ht, len );}
inline overror_t cudaMUB_Cols_reflect( ubMatrix MA, ui ht, ui len )
	{	return cudaMUBCols_reflect( (ubPMatrix)(MA), ht, len );}
inline overror_t cudaMUB_Rows_rev( ubMatrix MA, ui ht, ui len )
	{	return cudaMUBRows_rev( (ubPMatrix)(MA), ht, len );}
inline overror_t cudaMUB_Cols_rev( ubMatrix MA, ui ht, ui len )
	{	return cudaMUBCols_rev( (ubPMatrix)(MA), ht, len );}
inline overror_t  cudaMUB_Rows_distribution( uiMatrix MAbund, ubVector Limits, ui nBins, ubMatrix MX, ui ht, ui len, int mode )
	{	return cudaMUBRows_distribution( (uiPMatrix)MAbund, Limits, nBins, (ubPMatrix)MX, ht, len, mode ); }
inline overror_t  cudaMUB_Cols_distribution( uiMatrix MAbund, ubVector Limits, ui nBins, ubMatrix MX, ui ht, ui len, int mode )
	{	return cudaMUBCols_distribution( (uiPMatrix)MAbund, Limits, nBins, (ubPMatrix)MX, ht, len, mode ); }

/********  Operations involving two rows or two colums of one matrix  *****/

inline overror_t cudaMUB_Rows_exchange( ubMatrix MA, ui ht, ui len, ui row1, ui row2 )
	{	return cudaMUBRows_exchange( (ubPMatrix)(MA), ht, len, row1, row2 );}
inline overror_t cudaMUB_Cols_exchange( ubMatrix MA, ui ht, ui len, ui col1, ui col2 )
	{	return cudaMUBCols_exchange( (ubPMatrix)(MA), ht, len, col1, col2 );}

/*************** Transposing and rotating a matrix **********************/

inline overror_t cudaMUB_transpose( ubMatrix MTr, ubMatrix MA, ui htTr, ui lenTr )
	{	return cudaMUBtranspose( (ubPMatrix)(MTr), (ubPMatrix)(MA), htTr, lenTr );}
       /*  dimensions htTr, lenTr are those of the transposed matrix, not of the original!   */
inline overror_t cudaMUB_rotate90( ubMatrix MRot, ubMatrix MA, ui htRot, ui lenRot )
	{	return cudaMUBrotate90( (ubPMatrix)(MRot), (ubPMatrix)(MA), htRot, lenRot );}
inline overror_t cudaMUB_rotate180( ubMatrix MRot, ubMatrix MA, ui htRot, ui lenRot )
	{	return cudaVUB_rev( (ubPMatrix)(MRot), (ubPMatrix)(MA), (htRot)*(lenRot) );}
inline overror_t cudaMUB_rotate270( ubMatrix MRot, ubMatrix MA, ui htRot, ui lenRot )
	{	return cudaMUBrotate270( (ubPMatrix)(MRot), (ubPMatrix)(MA), htRot, lenRot );}
inline overror_t cudaMUB_transpose_buf( ubMatrix MTr, ubMatrix MA, ui htTr, ui lenTr, ubMatrix MBuf )
	{	return cudaMUBtranspose_buf( (ubPMatrix)(MTr), (ubPMatrix)(MA), htTr, lenTr, (ubPMatrix)(MBuf) );}

/**************************  Input and Output  **************************
	The input/output functions involve memory transfers from device
	to host memory or vice versa. The generic cudaMUB_input/output functions
	allocate their own host buffers, whereas the cudaMUB_xxx_buf functions
	take a user-supplied buffer vector h_Wk (size must be >= ht*len )
	and are much more efficient.                                       */

inline overror_t cudaMUB_fprint( FILE *stream, ubMatrix MA, ui ht, ui len, unsigned linewidth )
	{	return cudaMUBfprint( stream, (ubPMatrix)(MA), ht, len, linewidth ); }
inline overror_t cudaMUB_print( ubMatrix MA, ui ht, ui len )
	{	return cudaMUBfprint( stdout, (ubPMatrix)(MA), ht, len, 80 ); }
inline overror_t cudaMUB_cprint( ubMatrix MA, ui ht, ui len )
	{	return cudaMUBcprint( (ubPMatrix)(MA), ht, len ); }
inline overror_t cudaMUB_fprint_buf( FILE *stream, ubMatrix d_MA, ui ht, ui len, unsigned linewidth, ubVector h_Wk )
	{	return cudaMUBfprint_buf( stream, (ubPMatrix)(d_MA), ht, len, linewidth, h_Wk ); }
inline overror_t cudaMUB_print_buf( ubMatrix d_MA, ui ht, ui len, ubVector h_Wk )
	{	return cudaMUBfprint_buf( stdout, (ubPMatrix)(d_MA), ht, len, 80, h_Wk ); }
inline overror_t cudaMUB_cprint_buf( ubMatrix d_MA, ui ht, ui len, ubVector h_Wk )
	{	return cudaMUBcprint_buf( (ubPMatrix)(d_MA), ht, len, h_Wk ); }
		/*  cudaMUB_print, cudaMUB_cprint usable only for console applications! */
inline overror_t  cudaMUB_write( FILE *stream, ubMatrix MA, ui ht, ui len )
	{	return cudaMUBwrite( stream, (ubPMatrix)(MA), ht, len ); }
inline overror_t cudaMUB_read( ubMatrix MA, ui ht, ui len, FILE *stream )
	{	return cudaMUBread( (ubPMatrix)(MA), ht, len, stream ); }
inline overror_t  cudaMUB_write_buf( FILE *stream, ubMatrix d_MA, ui ht, ui len, ubVector h_Wk )
	{	return cudaMUBwrite_buf( stream, (ubPMatrix)(d_MA), ht, len, h_Wk ); }
inline overror_t cudaMUB_read_buf( ubMatrix d_MA, ui ht, ui len, FILE *stream, ubVector h_Wk )
	{	return cudaMUBread_buf( (ubPMatrix)(d_MA), ht, len, stream, h_Wk ); }
                                   /* write and read in ascii format */
inline overror_t cudaMUB_store( FILE *stream, ubMatrix MA, ui ht, ui len )
{	return cudaVUB_store( stream, (ubPMatrix)(MA), (len)*(ht) ); }
inline overror_t cudaMUB_recall( ubMatrix MA, ui ht, ui len, FILE *stream )
	{	return cudaVUB_recall( (ubPMatrix)(MA), (len)*(ht), stream ); }
inline overror_t cudaMUB_store_buf( FILE *stream, ubMatrix d_MA, ui ht, ui len, ubVector h_Wk )
{	return cudaVUB_store_buf( stream, (ubPMatrix)(d_MA), (len)*(ht), h_Wk ); }
inline overror_t cudaMUB_recall_buf( ubMatrix d_MA, ui ht, ui len, FILE *stream, ubVector h_Wk )
	{	return cudaVUB_recall_buf( (ubPMatrix)(d_MA), (len)*(ht), stream, h_Wk ); }
                                  /* store and recall in binary format */

#else  /* plain-C, not C++: type-cast used to transform ubMatrix into ubPMatrix */


/***  Addressing single elements of dynamically allocated matrices: ******/

#define cudaMUB_setElement( MA, ht, len, m, n, C ) cudaMUBsetElement( (ubPMatrix)(MA), ht, len, m, n, C )
#define cusdMUB_setElement( MA, ht, len, m, n, C ) cusdMUBsetElement( (ubPMatrix)(MA), ht, len, m, n, C )
#define cudaMUB_getElement( y, MA, ht, len, m, n ) cudaMUBgetElement( y, (ubPMatrix)(MA), ht, len, m, n )
#define cusdMUB_getElement( y, MA, ht, len, m, n ) cusdMUBgetElement( y, (ubPMatrix)(MA), ht, len, m, n )
#define cudaMUB_Pelement( MA, ht, len, m, n )      cudaMUBPelement( (ubPMatrix)(MA), ht, len, m, n )
#define cudaMUB_element(  MA, ht, len, m, n )      cudaMUBelement( (ubPMatrix)(MA), ht, len, m, n )

 /****************  Initialization  ***************************************

    To initialize all elements of a matrix with the same value,
    or to perform arithmetic operations on all elements simultaneously,
    refer to the functions of VectorLib.
    In order to use the VectorLib functions, utilize the feature that
    the whole matrix occupies one contiguous area in memory: pass the
    address of the first row to the desired vector function, the size
    of the "vector" being ht * len.
    For example, initialize all elements of the matrix MA with 1
    (this is *NOT* the identity matrix)  by calling
        cudaVUB_equ1( (ubVector)MA, ht * len );
*/

#define cudaMUB_equ0( MA, ht, len )            cudaVUB_equ0( (ubPMatrix)(MA), (ht)*(len) )
#define cudaMUB_equ1( MA, len )                cudaMUBequ1( (ubPMatrix)(MA), len ) /* identity matrix */
#define cudaMUB_randomLC( MA, ht, len, seed, Min, Max, h_state )      cudaVUB_randomLC( MA, (ht)*(len), seed, Min, Max, h_state )
#define cudaMUB_random( MA, ht, len, seed, Min, Max )                 cudaVUB_random( MA, (ht)*(len), seed, Min, Max )
#define cusdMUB_randomLC( MA, ht, len, seed, d_Min, d_Max, h_state )  cudaVUB_randomLC( MA, (ht)*(len), seed, d_Min, d_Max, h_state )
#define cusdMUB_random( MA, ht, len, seed, d_Min, d_Max )             cudaVUB_random( MA, (ht)*(len), seed, d_Min, d_Max )
#define cudaMUB_outerprod( MA, X, Y, ht, len ) cudaMUBouterprod( (ubPMatrix)(MA), X, Y, ht, len )
                       /* sizX=ht, sizY=len */
#define cudaMUB_Row_equ0( MA, ht, len, iRow )    cudaMUBRow_equ0( (ubPMatrix)(MA), ht, len, iRow )
#define cudaMUB_Col_equ0( MA, ht, len, iCol )    cudaMUBCol_equ0( (ubPMatrix)(MA), ht, len, iCol )
#define cudaMUB_Dia_equ0( MA, len )              cudaMUBDia_equ0( (ubPMatrix)(MA), len )
#define cudaMUB_Row_equC( MA, ht, len, iRow, C ) cudaMUBRow_equC( (ubPMatrix)(MA), ht, len, iRow, C )
#define cudaMUB_Col_equC( MA, ht, len, iCol, C ) cudaMUBCol_equC( (ubPMatrix)(MA), ht, len, iCol, C )
#define cudaMUB_Dia_equC( MA, len, C )           cudaMUBDia_equC( (ubPMatrix)(MA), len, C )
#define cusdMUB_Row_equC( MA, ht, len, iRow, d_C ) cusdMUBRow_equC( (ubPMatrix)(MA), ht, len, iRow, d_C )
#define cusdMUB_Col_equC( MA, ht, len, iCol, d_C ) cusdMUBCol_equC( (ubPMatrix)(MA), ht, len, iCol, d_C )
#define cusdMUB_Dia_equC( MA, len, d_C )           cusdMUBDia_equC( (ubPMatrix)(MA), len, d_C )

#define cudaMUB_Row_equV( MA, ht, len, iRow, X ) cudaMUBRow_equV( (ubPMatrix)(MA), ht, len, iRow, X )
#define cudaMUB_Col_equV( MA, ht, len, iCol, X ) cudaMUBCol_equV( (ubPMatrix)(MA), ht, len, iCol, X )
#define cudaMUB_Dia_equV( MA, len, X )           cudaMUBDia_equV( (ubPMatrix)(MA), len, X )

#define cudaMUB_Trd_equM( MA, MTrd, len )    cudaMUBTrd_equM( (ubPMatrix)(MA), (ubPMatrix)(MTr)d, len )
#define cudaMUB_Trd_extract( MTrd, MA, len ) cudaMUBTrd_extract( (ubPMatrix)(MTr)d, (ubPMatrix)(MA), len )

#define cudaMUB_equM( MB, MA, ht, len )      cudaVUB_equV( (ubPMatrix)(MB), (ubPMatrix)(MA), (ht)*(len) )
#define cudaMUB_equMhost( MB, MA, ht, len )  cudaVUB_equVhost( (ubPMatrix)(MB), MA[0], (ht)*(len) )
#define MUB_equMdevice( MB, MA, ht, len )    VUB_equVdevice( MB[0], (ubPMatrix)(MA), (ht)*(len) )

#define cudaMUB_UequL( MA, len ) cudaMUBUequL( (ubPMatrix)(MA), len )
#define cudaMUB_LequU( MA, len ) cudaMUBLequU( (ubPMatrix)(MA), len )

/************** Data-type interconversions  ****************************/

#define cudaM_BItoUB( MUB, MBI, ht, len ) cudaV_BItoUB( (ubVector)(MUB), (biVector)(MBI), (ht)*(len) )
#define cudaM_UBtoBI( MBI, MUB, ht, len ) cudaV_UBtoBI( (biVector)(MBI), (ubVector)(MUB), (ht)*(len) )
#define cudaM_UBtoU(  MU,  MUB, ht, len ) cudaV_UBtoU(  (uVector)(MU),   (ubVector)(MUB), (ht)*(len) )
#define cudaM_UBtoUS( MUS, MUB, ht, len ) cudaV_UBtoUS( (usVector)(MUS), (ubVector)(MUB), (ht)*(len) )
#define cudaM_UBtoUL( MUL, MUB, ht, len ) cudaV_UBtoUL( (ulVector)(MUL), (ubVector)(MUB), (ht)*(len) )
#define cudaM_UStoUB( MUB, MUS, ht, len ) cudaV_UStoUB( (ubVector)(MUB), (usVector)(MUS), (ht)*(len) )
#define cudaM_UtoUB(  MUB, MU,  ht, len ) cudaV_UtoUB(  (ubVector)(MUB), (uVector)(MU),  (ht)*(len) )
#define cudaM_ULtoUB( MUB, MUL, ht, len ) cudaV_ULtoUB( (ubVector)(MUB), (ulVector)(MUL), (ht)*(len) )
#ifdef _WIN64
	#define cudaM_UBtoUQ( MUQ, MUB, ht, len ) cudaV_UBtoUQ( (uqVector)(MUQ), (ubVector)(MUB), (ht)*(len) )
	#define cudaM_UQtoUB( MUB, MUQ, ht, len ) cudaV_UQtoUB( (ubVector)(MUB), (uqVector)(MUQ), (ht)*(len) )
#endif
#define cudaM_UBtoF(  MF,  MUB, ht, len ) cudaV_UBtoF(  (fVector)(MF),   (ubVector)(MUB), (ht)*(len) )
#define cudaM_UBtoD(  MD,  MUB, ht, len ) cudaV_UBtoD(  (dVector)(MD),   (ubVector)(MUB), (ht)*(len) )


/********  Extracting a submatrix and copying a submatrix back  *********/

#define cudaMUB_submatrix( MSub, subHt, subLen, MSrce, srceHt, srceLen, \
                      firstRowInCol, sampInCol, firstColInRow, sampInRow ) \
               cudaMUBsubmatrix(  (ubPMatrix)(MSub), subHt, subLen, \
                             (ubPMatrix)(MSrce), srceHt, srceLen, \
                             firstRowInCol, sampInCol, firstColInRow, sampInRow )

#define cudaMUB_submatrix_equM( MDest, destHt, destLen, \
                           firstRowInCol, sampInCol, firstColInRow, sampInRow, \
                           MSrce, srceHt, srceLen ) \
               cudaMUBsubmatrix_equM(  (ubPMatrix)(MDest), destHt, destLen, \
                             firstRowInCol, sampInCol, firstColInRow, sampInRow, \
                             (ubPMatrix)(MSrce), srceHt, srceLen )

#define cudaMUB_equMblock( MSub, subHt, subLen, MSrce, srceHt, srceLen, \
                      firstRowInCol, firstColInRow ) \
               cudaMUBequMblock(  (ubPMatrix)(MSub), subHt, subLen, \
                             (ubPMatrix)(MSrce), srceHt, srceLen, \
                             firstRowInCol, firstColInRow )

#define cudaMUB_block_equM( MDest, destHt, destLen, \
                       firstRowInCol, firstColInRow, \
                       MSrce, srceHt, srceLen ) \
               cudaMUBblock_equM( (ubPMatrix)(MDest), destHt, destLen, \
                             firstRowInCol, firstColInRow, \
                             (ubPMatrix)(MSrce), srceHt, srceLen )

#define cudaMUB_equMblockT( MSub, subHt, subLen, \
                      MSrce, srceHt, srceLen, \
                      firstRowInCol, firstColInRow ) \
               cudaMUBequMblockT(  (ubPMatrix)(MSub), subHt, subLen, \
                             (ubPMatrix)(MSrce), srceHt, srceLen, \
                             firstRowInCol, firstColInRow )

#define cudaMUB_block_equMT( MDest, destHt, destLen, \
                       firstRowInCol, firstColInRow, \
                       MSrce, srceHt, srceLen ) \
               cudaMUBblock_equMT( (ubPMatrix)(MDest), destHt, destLen, \
                             firstRowInCol, firstColInRow, \
                             (ubPMatrix)(MSrce), srceHt, srceLen )

/*****   Extracting a single row or a single column or the diagonal  ******
 *       and storing it into a vector                                     */

#define cudaMUB_Row_extract( Y, MA, ht, len, iRow ) cudaMUBRow_extract( Y, (ubPMatrix)(MA), ht, len, iRow )
#define cudaMUB_Col_extract( Y, MA, ht, len, iCol ) cudaMUBCol_extract( Y, (ubPMatrix)(MA), ht, len, iCol )
#define cudaMUB_Dia_extract( Y, MA, len )           cudaMUBDia_extract( Y, (ubPMatrix)(MA), len )


/**************  Deleting or inserting a row or a column   ***************/

#define cudaMUB_Row_delete( MB, MA, htA, lenA, iRow ) cudaMUBRow_delete( (ubPMatrix)(MB), (ubPMatrix)(MA), htA, lenA, iRow )
#define cudaMUB_Col_delete( MB, MA, htA, lenA, iCol ) cudaMUBCol_delete( (ubPMatrix)(MB), (ubPMatrix)(MA), htA, lenA, iCol )
#define cudaMUB_Row_insert( MB, MA, htB, lenB, iRow, X ) cudaMUBRow_insert( (ubPMatrix)(MB), (ubPMatrix)(MA), htB, lenB, iRow, X )
#define cudaMUB_Col_insert( MB, MA, htB, lenB, iCol, X ) cudaMUBCol_insert( (ubPMatrix)(MB), (ubPMatrix)(MA), htB, lenB, iCol, X )

/******  One-dimensional vector operations **********************
         performed along all rows or all columns simultaneously,
         or along the diagonal of a square matrix                */

#define cudaMUB_Rows_max( Y, MA, ht, len )     cudaMUBRows_max( Y, (ubPMatrix)(MA), ht, len )
#define cudaMUB_Cols_max( Y, MA, ht, len )     cudaMUBCols_max( Y, (ubPMatrix)(MA), ht, len )
#define cudaMUB_Dia_max(  h_RetPtr, MA, len )  cudaMUBDia_max( h_RetPtr, (ubPMatrix)(MA), len )
#define cusdMUB_Dia_max(  d_RetPtr, MA, len )  cusdMUBDia_max( d_RetPtr, (ubPMatrix)(MA), len )
#define cudaMUB_Rows_min( Y, MA, ht, len )     cudaMUBRows_min( Y, (ubPMatrix)(MA), ht, len )
#define cudaMUB_Cols_min( Y, MA, ht, len )     cudaMUBCols_min( Y, (ubPMatrix)(MA), ht, len )
#define cudaMUB_Dia_min(  h_RetPtr, MA, len )  cudaMUBDia_min( h_RetPtr, (ubPMatrix)(MA), len )
#define cusdMUB_Dia_min(  d_RetPtr, MA, len )  cusdMUBDia_min( d_RetPtr, (ubPMatrix)(MA), len )

#define cudaMUB_Rows_rotate( MA, ht, len, pos) cudaMUBRows_rotate( (ubPMatrix)(MA), ht, len, pos )
#define cudaMUB_Cols_rotate( MA, ht, len, pos) cudaMUBCols_rotate( (ubPMatrix)(MA), ht, len, pos )
#define cudaMUB_Rows_rotate_buf( MA, ht, len, pos, MBuf) cudaMUBRows_rotate_buf( (ubPMatrix)(MA), ht, len, pos, (ubPMatrix)(MBuf) )
#define cudaMUB_Cols_rotate_buf( MA, ht, len, pos, MBuf) cudaMUBCols_rotate_buf( (ubPMatrix)(MA), ht, len, pos, (ubPMatrix)(MBuf) )
#define cudaMUB_Rows_reflect( MA, ht, len)     cudaMUBRows_reflect( (ubPMatrix)(MA), ht, len )
#define cudaMUB_Cols_reflect( MA, ht, len)     cudaMUBCols_reflect( (ubPMatrix)(MA), ht, len )
#define cudaMUB_Rows_rev( MA, ht, len)         cudaMUBRows_rev( (ubPMatrix)(MA), ht, len )
#define cudaMUB_Cols_rev( MA, ht, len)         cudaMUBCols_rev( (ubPMatrix)(MA), ht, len )
#define cudaMUB_Rows_distribution( MAbund, Limits, nBins, MX, ht, len, mode ) cudaMUBRows_distribution( (uiPMatrix)MAbund, Limits, nBins, (ubPMatrix)MX, ht, len, mode )
#define cudaMUB_Cols_distribution( MAbund, Limits, nBins, MX, ht, len, mode ) cudaMUBCols_distribution( (uiPMatrix)MAbund, Limits, nBins, (ubPMatrix)MX, ht, len, mode )

/********  Operations involving two rows or two colums of one matrix  *****/

#define cudaMUB_Rows_exchange( MA, ht, len, row1, row2 ) cudaMUBRows_exchange( (ubPMatrix)(MA), ht, len, row1, row2 )
#define cudaMUB_Cols_exchange( MA, ht, len, col1, col2 ) cudaMUBCols_exchange( (ubPMatrix)(MA), ht, len, col1, col2 )

/****************  Transposing and rotating a matrix **********************/

#define cudaMUB_transpose( MTr, MA, htTr, lenTr ) cudaMUBtranspose( (ubPMatrix)(MTr), (ubPMatrix)(MA), htTr, lenTr )
       /*  dimensions htTr, lenTr are those of the transposed matrix,
           not of the original!                */
#define cudaMUB_rotate90( MRot, MA, htRot, lenRot )  cudaMUBrotate90( (ubPMatrix)(MRot), (ubPMatrix)(MA), htRot, lenRot )
#define cudaMUB_rotate180( MRot, MA, htRot, lenRot ) cudaVUB_rev( (ubPMatrix)(MRot), (ubPMatrix)(MA), (htRot)*(lenRot) )
#define cudaMUB_rotate270( MRot, MA, htRot, lenRot ) cudaMUBrotate270( (ubPMatrix)(MRot), (ubPMatrix)(MA), htRot, lenRot )


/**************************  Input and Output  **************************
	The input/output functions involve memory transfers from device
	to host memory or vice versa. The generic cudaMUB_input/output functions
	allocate their own host buffers, whereas the cudaMUB_xxx_buf functions
	take a user-supplied buffer vector h_Wk (size must be >= ht*len )
	and are much more efficient.                                       */

#define cudaMUB_fprint( stream, MA, ht, len, linewidth ) \
                    cudaMUBfprint( stream, (ubPMatrix)(MA), ht, len, linewidth )
#define cudaMUB_print( MA, ht, len )  cudaMUBfprint( stdout, (ubPMatrix)(MA), ht, len, 80 )
#define cudaMUB_cprint( MA, ht, len ) cudaMUBcprint( (ubPMatrix)(MA), ht, len )
#define cudaMUB_fprint_buf( stream, MA, ht, len, linewidth, h_Wk ) \
                    cudaMUBfprint_buf( stream, (ubPMatrix)(MA), ht, len, linewidth, h_Wk )
#define cudaMUB_print_buf( MA, ht, len )  cudaMUBfprint_buf( stdout, (ubPMatrix)(MA), ht, len, 80, h_Wk )
#define cudaMUB_cprint_buf( MA, ht, len ) cudaMUBcprint_buf( (ubPMatrix)(MA), ht, len, h_Wk )
  /*  cudaMUB_print, cudaMUB_cprint usable only for console applications! */
#define cudaMUB_write( str, MA, ht, len )   cudaMUBwrite( str, (ubPMatrix)(MA), ht, len )
#define cudaMUB_read( MA, ht, len, str )    cudaMUBread( (ubPMatrix)(MA), ht, len, str )
#define cudaMUB_write_buf( str, MA, ht, len, h_Wk )   cudaMUBwrite_buf( str, (ubPMatrix)(MA), ht, len, h_Wk )
#define cudaMUB_read_buf( MA, ht, len, str, h_Wk )    cudaMUBread_buf( (ubPMatrix)(MA), ht, len, str, h_Wk )
                                   /* write and read in ascii format */
#define cudaMUB_store( str, MA, ht, len )   cudaVUB_store( str, (ubPMatrix)(MA), (len)*(ht) )
#define cudaMUB_recall( MA, ht, len, str)   cudaVUB_recall( (ubPMatrix)(MA), (len)*(ht), str)
#define cudaMUB_store_buf( str, MA, ht, len, h_Wk )   cudaVUB_store_buf( str, (ubPMatrix)(MA), (len)*(ht), h_Wk )
#define cudaMUB_recall_buf( MA, ht, len, str, h_Wk)   cudaVUB_recall_buf( (ubPMatrix)(MA), (len)*(ht), str, h_Wk )
                                  /* store and recall in binary format */

#endif /* plain-C or C++ for functions working on device memory */


/*******************  Functions working on host memory: **********************
 *                                                                           *
 *	MBIcu_func		(working on matrices in host memory, input type biMatrix,*
 *	scalar parameters on host and passed by value)                           *
 *****************************************************************************/ 

/****************  Initialization  ****************************************/

#define MUBcu_equ0( MA, ht, len )                   VUBcu_equ0( (MA)[0], (ht)*(len) )
#define MUBcu_equ1( MA, len )                       MUBcuequ1( (MA)[0], len ) /* identity matrix */
#define MUBcu_randomLC( MA, ht, len, seed, Min, Max, state ) VUBcu_randomLC( (MA)[0], (ht)*(len), seed, Min, Max, state )
#define MUBcu_random( MA, ht, len, seed, Min, Max )          VUBcu_random( (MA)[0], (ht)*(len), seed, Min, Max )
#define MUBcu_outerprod( MA, X, Y, ht, len )        MUBcuouterprod( (MA)[0], X, Y, ht, len )
                       /* sizX=ht, sizY=len */
#define MUBcu_Row_equ0( MA, ht, len, iRow )    MUBcuRow_equ0( (MA)[0], ht, len, iRow )
#define MUBcu_Col_equ0( MA, ht, len, iCol )    MUBcuCol_equ0( (MA)[0], ht, len, iCol )
#define MUBcu_Dia_equ0( MA, len )              MUBcuDia_equ0( (MA)[0], len )
#define MUBcu_Row_equC( MA, ht, len, iRow, C ) MUBcuRow_equC( (MA)[0], ht, len, iRow, C )
#define MUBcu_Col_equC( MA, ht, len, iCol, C ) MUBcuCol_equC( (MA)[0], ht, len, iCol, C )
#define MUBcu_Dia_equC( MA, len, C )           MUBcuDia_equC( (MA)[0], len, C )

#define MUBcu_Row_equV( MA, ht, len, iRow, X ) MUBcuRow_equV( (MA)[0], ht, len, iRow, X )
#define MUBcu_Col_equV( MA, ht, len, iCol, X ) MUBcuCol_equV( (MA)[0], ht, len, iCol, X )
#define MUBcu_Dia_equV( MA, len, X )           MUBcuDia_equV( (MA)[0], len, X )

#define MUBcu_Trd_equM( MA, MTrd, len )        MUBcuTrd_equM( (MA)[0], (MTrd)[0], len )
#define MUBcu_Trd_extract( MTrd, MA, len )     MUBcuTrd_extract( (MTrd)[0], (MA)[0], len )

#define MUBcu_equM( MB, MA, ht, len )          VUBcu_equV( (MB)[0], (MA)[0], (ht)*(len) )
#define MUBcu_equMhost( MB, MA, ht, len )      VUBcu_equVhost( (MB)[0], MA[0], (ht)*(len) )

#define MUBcu_UequL( MA, len ) MUBcuUequL( (MA)[0], len )
#define MUBcu_LequU( MA, len ) MUBcuLequU( (MA)[0], len )
     /* copy lower-diagonal elements into upper-diagonal
       (or vice versa) by index-reflection, so as to get a symmetric matrix    */

            /* data-type conversions:  */
#define Mcu_BItoUB( MUB, MBI, ht, len ) Vcu_BItoUB( (MUB)[0], (MBI)[0], (ht)*(len) )
#define Mcu_UBtoBI( MBI, MUB, ht, len ) Vcu_UBtoBI( (MBI)[0], (MUB)[0], (ht)*(len) )
#define Mcu_UBtoUS( MUS, MUB, ht, len ) Vcu_UBtoUS( (MUS)[0], (MUB)[0], (ht)*(len) )
#define Mcu_UBtoU(  MU,  MUB, ht, len ) Vcu_UBtoU(  (MU)[0],  (MUB)[0], (ht)*(len) )
#define Mcu_UBtoUL( MUL, MUB, ht, len ) Vcu_UBtoUL( (MUL)[0], (MUB)[0], (ht)*(len) )
#define Mcu_UStoUB( MUB, MUS, ht, len ) Vcu_UStoUB( (MUB)[0], (MUS)[0], (ht)*(len) )
#define Mcu_UtoUB(  MUB, MU,  ht, len ) Vcu_UtoUB(  (MUB)[0], (MU)[0],  (ht)*(len) )
#define Mcu_ULtoUB( MUB, MUL, ht, len ) Vcu_ULtoUB( (MUB)[0], (MUL)[0], (ht)*(len) )
#ifdef _WIN64
	#define Mcu_UBtoUQ( MUQ, MUB, ht, len ) Vcu_UBtoUQ( (MUQ)[0], (MUB)[0], (ht)*(len) )
	#define Mcu_UQtoUB( MUB, MUQ, ht, len ) Vcu_UQtoUB( (MUB)[0], (MUQ)[0], (ht)*(len) )
#endif
#define Mcu_UBtoF(  MF,  MUB, ht, len ) Vcu_UBtoF(  (MF)[0],  (MUB)[0], (ht)*(len) )
#define Mcu_UBtoD(  MD,  MUB, ht, len ) Vcu_UBtoD(  (MD)[0],  (MUB)[0], (ht)*(len) )


/********  Extracting a submatrix and copying a submatrix back  *********/

#define MUBcu_submatrix( MSub, subHt, subLen, MSrce, srceHt, srceLen, \
                      firstRowInCol, sampInCol, firstColInRow, sampInRow ) \
               MUBcusubmatrix(  (MSub)[0], subHt, subLen, \
                             (MSrce)[0], srceHt, srceLen, \
                             firstRowInCol, sampInCol, firstColInRow, sampInRow )

#define MUBcu_submatrix_equM( MDest, destHt, destLen, \
                           firstRowInCol, sampInCol, firstColInRow, sampInRow, \
                           MSrce, srceHt, srceLen ) \
               MUBcusubmatrix_equM(  (MDest)[0], destHt, destLen, \
                             firstRowInCol, sampInCol, firstColInRow, sampInRow, \
                             (MSrce)[0], srceHt, srceLen )

#define MUBcu_equMblock( MSub, subHt, subLen, MSrce, srceHt, srceLen, \
                      firstRowInCol, firstColInRow ) \
               MUBcuequMblock(  (MSub)[0], subHt, subLen, \
                             (MSrce)[0], srceHt, srceLen, \
                             firstRowInCol, firstColInRow )

#define MUBcu_block_equM( MDest, destHt, destLen, \
                       firstRowInCol, firstColInRow, \
                       MSrce, srceHt, srceLen ) \
               MUBcublock_equM( (MDest)[0], destHt, destLen, \
                             firstRowInCol, firstColInRow, \
                             (MSrce)[0], srceHt, srceLen )

#define MUBcu_equMblockT( MSub, subHt, subLen, MSrce, srceHt, srceLen, \
                      firstRowInCol, firstColInRow ) \
               MUBcuequMblockT(  (MSub)[0], subHt, subLen, \
                             (MSrce)[0], srceHt, srceLen, \
                             firstRowInCol, firstColInRow )

#define MUBcu_block_equMT( MDest, destHt, destLen, \
                       firstRowInCol, firstColInRow, \
                       MSrce, srceHt, srceLen ) \
               MUBcublock_equMT( (MDest)[0], destHt, destLen, \
                             firstRowInCol, firstColInRow, \
                             (MSrce)[0], srceHt, srceLen )

/*****   Extracting a single row or a single column or the diagonal  ******
 *       and storing it into a vector                                     */

#define MUBcu_Row_extract( Y, MA, ht, len, iRow ) MUBcuRow_extract( Y, (MA)[0], ht, len, iRow )
#define MUBcu_Col_extract( Y, MA, ht, len, iCol ) MUBcuCol_extract( Y, (MA)[0], ht, len, iCol )
#define MUBcu_Dia_extract( Y, MA, len )           MUBcuDia_extract( Y, (MA)[0], len )

/**************  Deleting or inserting a row or a column   ***************/

#define MUBcu_Row_delete( MB, MA, htA, lenA, iRow )    MUBcuRow_delete( (MB)[0], (MA)[0], htA, lenA, iRow )
#define MUBcu_Col_delete( MB, MA, htA, lenA, iCol )    MUBcuCol_delete( (MB)[0], (MA)[0], htA, lenA, iCol )
#define MUBcu_Row_insert( MB, MA, htB, lenB, iRow, X ) MUBcuRow_insert( (MB)[0], (MA)[0], htB, lenB, iRow, X )
#define MUBcu_Col_insert( MB, MA, htB, lenB, iCol, X ) MUBcuCol_insert( (MB)[0], (MA)[0], htB, lenB, iCol, X )


/******  One-dimensional vector operations **********************
         performed along all rows or all columns simultaneously,
         or along the diagonal of a square matrix                */

#define MUBcu_Rows_max( Y, MA, ht, len )        MUBcuRows_max( Y, (MA)[0], ht, len )
#define MUBcu_Cols_max( Y, MA, ht, len )        MUBcuCols_max( Y, (MA)[0], ht, len )
#define MUBcu_Dia_max(  MA, len )               MUBcuDia_max(  (MA)[0], len )
#define MUBcu_Rows_min( Y, MA, ht, len )        MUBcuRows_min( Y, (MA)[0], ht, len )
#define MUBcu_Cols_min( Y, MA, ht, len )        MUBcuCols_min( Y, (MA)[0], ht, len )
#define MUBcu_Dia_min(  MA, len )               MUBcuDia_min(  (MA)[0], len )

#define MUBcu_Rows_rotate( MA, ht, len, pos)           MUBcuRows_rotate( (MA)[0], ht, len, pos )
#define MUBcu_Cols_rotate( MA, ht, len, pos)           MUBcuCols_rotate( (MA)[0], ht, len, pos )
#define MUBcu_Rows_rotate_buf( MA, ht, len, pos, MBuf) MUBcuRows_rotate_buf( (MA)[0], ht, len, pos, (MBuf)[0] )
#define MUBcu_Cols_rotate_buf( MA, ht, len, pos, MBuf) MUBcuCols_rotate_buf( (MA)[0], ht, len, pos, (MBuf)[0] )
#define MUBcu_Rows_reflect( MA, ht, len )              MUBcuRows_reflect( (MA)[0], ht, len )
#define MUBcu_Cols_reflect( MA, ht, len )              MUBcuCols_reflect( (MA)[0], ht, len )
#define MUBcu_Rows_rev( MA, ht, len)                   MUBcuRows_rev( (MA)[0], ht, len )
#define MUBcu_Cols_rev( MA, ht, len)                   MUBcuCols_rev( (MA)[0], ht, len )
#define MUBcu_Rows_distribution( MAbund, Limits, nBins, MX, ht, len, mode ) MUBcuRows_distribution( MAbund[0], Limits, nBins, MX[0], ht, len, mode )
#define MUBcu_Cols_distribution( MAbund, Limits, nBins, MX, ht, len, mode ) MUBcuCols_distribution( MAbund[0], Limits, nBins, MX[0], ht, len, mode )

/********  Operations involving two rows or two colums of one matrix  *****/

#define MUBcu_Rows_exchange( MA, ht, len, row1, row2 ) \
                             MUBcuRows_exchange( (MA)[0], ht, len, row1, row2 )
#define MUBcu_Cols_exchange( MA, ht, len, col1, col2 ) \
                             MUBcuCols_exchange( (MA)[0], ht, len, col1, col2 )

/*************** Transposing and rotating a matrix **********************/

#define MUBcu_transpose( MTr, MA, htTr, lenTr )    MUBcutranspose( (MTr)[0], (MA)[0], htTr, lenTr )
       /*  dimensions htTr, lenTr are those of the transposed matrix, not of the original!   */
#define MUBcu_rotate90( MRot, MA, htRot, lenRot )  MUBcurotate90( (MRot)[0], (MA)[0], htRot, lenRot )
#define MUBcu_rotate180( MRot, MA, htRot, lenRot ) VUBcu_rev( (MRot)[0], (MA)[0], (htRot)*(lenRot) )
#define MUBcu_rotate270( MRot, MA, htRot, lenRot ) MUBcurotate270( (MRot)[0], (MA)[0], htRot, lenRot )


/*************************************************************************
 * MUBcu functions (without underbar in the prefix): 	
    (working on matrices in host memory, input type 
	ubPMatrix = ubVector = pointer to matrix element[0][0], 
	scalar parameters on host and passed by value)
*
 *************************************************************************/

#define MUBcuequ0( MA, ht, len )       VUBcu_equ0( MA, (ht)*(len) )
void   __vf OVCUAPI  MUBcuequ1( ubPMatrix MA, ui len );  /* identity matrix */
void   __vf OVCUAPI  MUBcuouterprod( ubPMatrix MA, ubVector X,  ubVector Y, ui ht, ui len );

void   __vf OVCUAPI  MUBcuRow_equ0( ubPMatrix MA, ui ht, ui len, ui iRow );
void   __vf OVCUAPI  MUBcuCol_equ0( ubPMatrix MA, ui ht, ui len, ui iCol );
void   __vf OVCUAPI  MUBcuDia_equ0( ubPMatrix MA, ui len );

void   __vf OVCUAPI  MUBcuRow_equC( ubPMatrix MA, ui ht, ui len, ui iRow, unsigned char C );
void   __vf OVCUAPI  MUBcuCol_equC( ubPMatrix MA, ui ht, ui len, ui iCol, unsigned char C );
void   __vf OVCUAPI  MUBcuDia_equC( ubPMatrix MA, ui len, unsigned char C );

void   __vf OVCUAPI  MUBcuRow_equV( ubPMatrix MA, ui ht, ui len, ui iRow, ubVector X );
void   __vf OVCUAPI  MUBcuCol_equV( ubPMatrix MA, ui ht, ui len, ui iCol, ubVector X );
void   __vf OVCUAPI  MUBcuDia_equV( ubPMatrix MA, ui len, ubVector X );

void   __vf OVCUAPI  MUBcuTrd_equM( ubPMatrix MA, ubPMatrix MTrd, ui len );
void   __vf OVCUAPI  MUBcuTrd_extract( ubPMatrix MTrd, ubPMatrix MA, ui len );

#define MUBcuequM( MB, MA, ht, len )      VUBcu_equV( MB, MA, (ht)*(len) )
void   __vf OVCUAPI  MUBcuUequL( ubPMatrix MA, ui len );
void   __vf OVCUAPI  MUBcuLequU( ubPMatrix MA, ui len );

            /* data-type conversions:  */
#define McuBItoUB( MUB, MBI, ht, len ) Vcu_BItoUB( MUB, MBI, (ht)*(len) )
#define McuUBtoBI( MBI, MUB, ht, len ) Vcu_UBtoBI( MBI, MUB, (ht)*(len) )
#define McuUBtoUS( MUS, MUB, ht, len ) Vcu_UBtoUS( MUS, MUB, (ht)*(len) )
#define McuUBtoU(  MU,  MUB, ht, len ) Vcu_UBtoU(  MU,  MUB, (ht)*(len) )
#define McuUBtoUL( MUL, MUB, ht, len ) Vcu_UBtoUL( MUL, MUB, (ht)*(len) )
#define McuUStoUB( MUB, MUS, ht, len ) Vcu_UStoUB( MUB, MUS, (ht)*(len) )
#define McuUtoUB(  MUB, MU,  ht, len ) Vcu_UtoUB(  MUB, MU,   (ht)*(len) )
#define McuULtoUB( MUB, MUL, ht, len ) Vcu_ULtoUB( MUB, MUL, (ht)*(len) )
#ifdef _WIN64
	#define McuUBtoUQ( MUQ, MUB, ht, len ) Vcu_UBtoUQ( MUQ, MUB, (ht)*(len) )
	#define McuUQtoUB( MUB, MUQ, ht, len ) Vcu_UQtoUB( MUB, MUQ, (ht)*(len) )
#endif
#define McuUBtoF(  MF,  MUB, ht, len ) Vcu_UBtoF(  MF,  MUB, (ht)*(len) )
#define McuUBtoD(  MD,  MUB, ht, len ) Vcu_UBtoD(  MD,  MUB, (ht)*(len) )

/********  Extracting a submatrix and copying a submatrix back  *********/

void  __vf OVCUAPI  MUBcusubmatrix( ubPMatrix MSub, ui subHt,  ui subLen,
                          ubPMatrix MSrce, ui srceHt,  ui srceLen,
                          ui firstRowInCol,  ui sampInCol,
                          ui firstColInRow,  ui sampInRow );

void  __vf OVCUAPI  MUBcusubmatrix_equM( ubPMatrix MDest, ui destHt, ui destLen,
                               ui firstRowInCol,  ui sampInCol,
                               ui firstColInRow,  ui sampInRow,
                               ubPMatrix MSrce, ui srceHt, ui srceLen );

void  __vf OVCUAPI  MUBcuequMblock(  ubPMatrix MSub, ui subHt, ui subLen,
                          ubPMatrix MSrce, ui srceHt,  ui srceLen,
                          ui firstRowInCol,  ui firstColInRow );

void  __vf OVCUAPI  MUBcublock_equM( ubPMatrix MDest, ui destHt, ui destLen,
                          ui firstRowInCol,  ui firstColInRow,
                          ubPMatrix MSrce, ui srceHt, ui srceLen );

void  __vf OVCUAPI  MUBcuequMblockT( ubPMatrix MSub, ui subHt, ui subLen,
                          ubPMatrix MSrce, ui srceHt, ui srceLen,
                          ui firstRowInCol,  ui firstColInRow );

void  __vf OVCUAPI  MUBcublock_equMT( ubPMatrix MDest, ui destHt, ui destLen,
                          ui firstRowInCol,  ui firstColInRow,
                          ubPMatrix MSrce, ui srceHt, ui srceLen );


/*****   Extracting a single row or a single column or the diagonal  *****
 *       and storing it into a vector                                    */

void __vf OVCUAPI  MUBcuRow_extract( ubVector Y, ubPMatrix MA, ui ht, ui len, ui iRow );
void __vf OVCUAPI  MUBcuCol_extract( ubVector Y, ubPMatrix MA, ui ht, ui len, ui iCol );
void __vf OVCUAPI  MUBcuDia_extract( ubVector Y, ubPMatrix MA, ui len );

/**********  Deleting or inserting a row or a column *****************/

void __vf OVCUAPI  MUBcuRow_delete( ubPMatrix MB, ubPMatrix MA, ui htA, ui lenA, ui iRow );
void __vf OVCUAPI  MUBcuCol_delete( ubPMatrix MB, ubPMatrix MA, ui htA, ui lenA, ui iCol );
void __vf OVCUAPI  MUBcuRow_insert( ubPMatrix MB, ubPMatrix MA, ui htB, ui lenB, ui iRow, ubVector X );
void __vf OVCUAPI  MUBcuCol_insert( ubPMatrix MB, ubPMatrix MA, ui htB, ui lenB, ui iCol, ubVector X );


/******  One-dimensional vector operations **********************
         performed along all rows or all columns simultaneously,
         or along the diagonal of a square matrix                */

void   __vf OVCUAPI  MUBcuRows_max( ubVector Y, ubPMatrix MA, ui ht, ui len );
void   __vf OVCUAPI  MUBcuCols_max( ubVector Y, ubPMatrix MA, ui ht, ui len );
unsigned char  __vf OVCUAPI  MUBcuDia_max(  ubPMatrix MA, ui len );
void   __vf OVCUAPI  MUBcuRows_min( ubVector Y, ubPMatrix MA, ui ht, ui len );
void   __vf OVCUAPI  MUBcuCols_min( ubVector Y, ubPMatrix MA, ui ht, ui len );
unsigned char  __vf OVCUAPI  MUBcuDia_min(  ubPMatrix MA, ui len );

void  __vf OVCUAPI  MUBcuRows_rotate( ubPMatrix MA, ui ht, ui len, ssize_t pos );
void  __vf OVCUAPI  MUBcuCols_rotate( ubPMatrix MA, ui ht, ui len, ssize_t pos );
void  __vf OVCUAPI  MUBcuRows_rotate_buf( ubPMatrix MA, ui ht, ui len, ssize_t pos, ubPMatrix MBuf );
void  __vf OVCUAPI  MUBcuCols_rotate_buf( ubPMatrix MA, ui ht, ui len, ssize_t pos, ubPMatrix MBuf );
void  __vf OVCUAPI  MUBcuRows_reflect( ubPMatrix MA, ui ht, ui len );
void  __vf OVCUAPI  MUBcuCols_reflect( ubPMatrix MA, ui ht, ui len );
void  __vf OVCUAPI  MUBcuRows_rev( ubPMatrix MA, ui ht, ui len );
void  __vf OVCUAPI  MUBcuCols_rev( ubPMatrix MA, ui ht, ui len );
void  __vf OVCUAPI  MUBcuRows_distribution( uiPMatrix MAbund, ubVector Limits, ui nBins, ubPMatrix MX, ui ht, ui len, int mode );
void  __vf OVCUAPI  MUBcuCols_distribution( uiPMatrix MAbund, ubVector Limits, ui nBins, ubPMatrix MX, ui ht, ui len, int mode );

/********  Operations involving two rows or two colums of one matrix  *****/

void   __vf OVCUAPI  MUBcuRows_exchange( ubPMatrix MA, ui ht, ui len, ui i1, ui i2 );
void   __vf OVCUAPI  MUBcuCols_exchange( ubPMatrix MA, ui ht, ui len, ui i1, ui i2 );


/***************  Transposing and rotating a matrix **********************/

void  __vf OVCUAPI  MUBcutranspose( ubPMatrix MTr, ubPMatrix MA,  ui htTr, ui lenTr );
void  __vf OVCUAPI  MUBcurotate90(  ubPMatrix MRot, ubPMatrix MA, ui htRot, ui lenRot );
#define     MUBcurotate180( MRot, MA, htRot, lenRot )  VUBcu_rev( MRot, MA, (htRot)*(lenRot) )
void  __vf OVCUAPI  MUBcurotate270( ubPMatrix MRot, ubPMatrix MA, ui htRot, ui lenRot );



#ifdef __cplusplus
} // end of extern "C"
#endif
#endif  /*  __MUBSTD_H  */
