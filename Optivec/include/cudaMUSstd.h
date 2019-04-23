/*  cudaMUSstd.h

  matrix management functions:
  manipulations on matrices of data type "unsigned short" 
  (16-bit unsigned integers)

  This file declares the functions with the name variants 
	cudaMUS_func	(working on matrices in device memory, input type usMatrix, scalar parameters reside on host and are passed by value)
	cusdMUS_func	(as cudaMUS_func except scalar parameters reside on device and are passed by address)
	cudaMUSfunc		(as cudaMUS_func, but input type usPMatrix = usVector = pointer to matrix element[0][0])
	cusdMUSfunc		(as cusdMUS_func, but input type usPMatrix = usVector = pointer to matrix element[0][0])
	MUScu_func		(working on matrices in host memory, input type usMatrix, scalar parameters on host and passed by value)
	MUScufunc		(as MUScu_func, but input type usPMatrix = usVector = pointer to matrix element[0][0])
  where func is the respective function.

   Copyright (c) 1996-2017 by OptiCode - Dr. Martin Sander Software Dev.
  All Rights Reserved.

*/

#if !defined( __CUDAMUSSTD_H )
#define __CUDAMUSSTD_H
#if !defined( __CUDAMATLIB_H )
#include <cudaMatLib.h>
#endif
#if !defined( __CUDAVUSSTD_H )
#include <cudaVUSstd.h>
#endif
#if !defined( __CUDAVUSMATH_H )
#include <cudaVUSmath.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif

/**** Generation of matrices on device memory and on pinned host memory *******************/

usMatrix  __vf cudaMUS_matrix( ui ht, ui len );   /* allocates a vector on device memory */
usMatrix  __vf cudaMUS_matrix0( ui ht, ui len );
 /* The following functions allocate device-accessible, "pinned" memory on the host.
	This memory is mapped onto the device memory space. The resulting device address is returned.
	The matrix can be accessed either by its host address "hostPtr" e.g., MUS_equ1( hostPtr, ht, len );
	or by its device address , e.g., cudaMUS_equ1( devicePtr, ht, len );                             */
usMatrix  __vf cudaMUS_pinnedMatrix(  usMatrix *hostPtr, ui ht, ui len ); 
usMatrix  __vf cudaMUS_pinnedMatrix0( usMatrix *hostPtr, ui ht, ui len );

/*************************************************************************
 * Declarations of the functions written without underbar in the prefix: *
 *	cudaMUSfunc  (input type 
                   usPMatrix = usVector = pointer to matrix element[0][0])
 *	cusdMUSfunc  (input type 
                   usPMatrix = usVector = pointer to matrix element[0][0])
 *************************************************************************/


void  __vcuf OVCUAPI  cudaMUSsetElement( usPMatrix X, ui ht, ui len, ui m, ui n, unsigned short C );
void  __vcuf OVCUAPI  cusdMUSsetElement( usPMatrix X, ui ht, ui len, ui m, ui n, unsigned short *d_C );
void  __vcuf OVCUAPI  cudaMUSgetElement( unsigned short *h_y, usPMatrix X, ui ht, ui len, ui m, ui n );
void  __vcuf OVCUAPI  cusdMUSgetElement( unsigned short *d_y, usPMatrix X, ui ht, ui len, ui m, ui n );
unsigned short * __vcuf OVCUAPI  cudaMUSPelement( usPMatrix X, ui ht, ui len, ui m, ui n );
unsigned short   __vcuf OVCUAPI  cudaMUSelement(  usPMatrix X, ui ht, ui len, ui m, ui n );

#define cudaMUSequ0( MA, ht, len )            cudaVUS_equ0( MA, (ht)*(len) )
overror_t   __vcuf OVCUAPI  cudaMUSequ1( usPMatrix MA, ui len );  /* identity matrix */
overror_t   __vcuf OVCUAPI  cudaMUSouterprod( usPMatrix MA, usVector X,  usVector Y, ui ht, ui len );

overror_t   __vcuf OVCUAPI  cudaMUSRow_equ0( usPMatrix MA, ui ht, ui len, ui iRow );
overror_t   __vcuf OVCUAPI  cudaMUSCol_equ0( usPMatrix MA, ui ht, ui len, ui iCol );
overror_t   __vcuf OVCUAPI  cudaMUSDia_equ0( usPMatrix MA, ui len );

overror_t   __vcuf OVCUAPI  cudaMUSRow_equC( usPMatrix MA, ui ht, ui len, ui iRow, unsigned short C );
overror_t   __vcuf OVCUAPI  cudaMUSCol_equC( usPMatrix MA, ui ht, ui len, ui iCol, unsigned short C );
overror_t   __vcuf OVCUAPI  cudaMUSDia_equC( usPMatrix MA, ui len, unsigned short C );
overror_t   __vcuf OVCUAPI  cusdMUSRow_equC( usPMatrix MA, ui ht, ui len, ui iRow, unsigned short *d_C );
overror_t   __vcuf OVCUAPI  cusdMUSCol_equC( usPMatrix MA, ui ht, ui len, ui iCol, unsigned short *d_C );
overror_t   __vcuf OVCUAPI  cusdMUSDia_equC( usPMatrix MA, ui len, unsigned short *d_C );

overror_t   __vcuf OVCUAPI  cudaMUSRow_equV( usPMatrix MA, ui ht, ui len, ui iRow, usVector X );
overror_t   __vcuf OVCUAPI  cudaMUSCol_equV( usPMatrix MA, ui ht, ui len, ui iCol, usVector X );
overror_t   __vcuf OVCUAPI  cudaMUSDia_equV( usPMatrix MA, ui len, usVector X );

overror_t   __vcuf OVCUAPI  cudaMUSTrd_equM( usPMatrix MA, usPMatrix MTrd, ui len );
overror_t   __vcuf OVCUAPI  cudaMUSTrd_extract( usPMatrix MTrd, usPMatrix MA, ui len );

#define cudaMUSequM( MB, MA, ht, len )  cudaVUS_equV( MB, MA, (ht)*(len) )
#define cudaMUSequMhost( MB, MA, ht, len )  cudaVUS_equVhost( MB, MA, (ht)*(len) )
#define MUSequMdevice( MB, MA, ht, len )    VUS_equVdevice( MB, MA, (ht)*(len) )
overror_t   __vcuf OVCUAPI  cudaMUSUequL( usPMatrix MA, ui len );
overror_t   __vcuf OVCUAPI  cudaMUSLequU( usPMatrix MA, ui len );

            /* data-type conversions:  */
#define cudaMSItoUS( MUS, MSI, ht, len ) cudaV_SItoUS( (MUS), (MSI), (ht)*(len) )
#define cudaMUStoSI( MSI, MUS, ht, len ) cudaV_UStoSI( (MSI), (MUS), (ht)*(len) )
#define cudaMUStoUB( MUB, MUS, ht, len ) cudaV_UStoUB( (MUB), (MUS), (ht)*(len) )
#define cudaMUStoU(  MU,  MUS, ht, len ) cudaV_UStoU(  (MU),  (MUS), (ht)*(len) )
#define cudaMUStoUL( MUL, MUS, ht, len ) cudaV_UStoUL( (MUL), (MUS), (ht)*(len) )
#define cudaMUBtoUS( MUS, MUB, ht, len ) cudaV_UBtoUS( (MUS), (MUB), (ht)*(len) )
#define cudaMUtoUS(  MUS, MU,  ht, len ) cudaV_UtoUS(  (MUS), (MU),  (ht)*(len) )
#define cudaMULtoUS( MUS, MUL, ht, len ) cudaV_ULtoUS( (MUS), (MUL), (ht)*(len) )
#ifdef _WIN64
	#define cudaMUStoUQ( MUQ, MUS, ht, len ) cudaV_UStoUQ( (MUQ), (MUS), (ht)*(len) )
	#define cudaMUQtoUS( MUS, MUQ, ht, len ) cudaV_UQtoUS( (MUS), (MUQ), (ht)*(len) )
#endif
#define cudaMUStoF(  MF,  MUS, ht, len ) cudaV_UStoF(  (MF),  (MUS), (ht)*(len) )
#define cudaMUStoD(  MD,  MUS, ht, len ) cudaV_UStoD(  (MD),  (MUS), (ht)*(len) )

/********  Extracting a submatrix and copying a submatrix back  *********/

overror_t  __vcuf OVCUAPI  cudaMUSsubmatrix( usPMatrix MSub,  ui subHt,  ui subLen,
                          usPMatrix MSrce, ui srceHt,  ui srceLen,
                          ui firstRowInCol,  ui sampInCol,
                          ui firstColInRow,  ui sampInRow );

overror_t  __vcuf OVCUAPI  cudaMUSsubmatrix_equM( usPMatrix MDest, ui destHt, ui destLen,
                               ui firstRowInCol,  ui sampInCol,
                               ui firstColInRow,  ui sampInRow,
                               usPMatrix MSrce, ui srceHt, ui srceLen );

overror_t  __vcuf OVCUAPI  cudaMUSequMblock(  usPMatrix MSub, ui subHt, ui subLen,
                          usPMatrix MSrce, ui srceHt,  ui srceLen,
                          ui firstRowInCol,  ui firstColInRow );

overror_t  __vcuf OVCUAPI  cudaMUSblock_equM( usPMatrix MDest, ui destHt, ui destLen,
                          ui firstRowInCol,  ui firstColInRow,
                          usPMatrix MSrce,  ui srceHt, ui srceLen );

overror_t  __vcuf OVCUAPI  cudaMUSequMblockT( usPMatrix MSub, ui subHt, ui subLen,
                          usPMatrix MSrce, ui srceHt, ui srceLen,
                          ui firstRowInCol,  ui firstColInRow );

overror_t  __vcuf OVCUAPI  cudaMUSblock_equMT( usPMatrix MDest, ui destHt, ui destLen,
                          ui firstRowInCol,  ui firstColInRow,
                          usPMatrix MSrce, ui srceHt, ui srceLen );


/*****   Extracting a single row or a single column or the diagonal  *****
 *       and storing it into a vector                                    */

overror_t __vcuf OVCUAPI  cudaMUSRow_extract( usVector Y, usPMatrix MA, ui ht, ui len, ui iRow );
overror_t __vcuf OVCUAPI  cudaMUSCol_extract( usVector Y, usPMatrix MA, ui ht, ui len, ui iCol );
overror_t __vcuf OVCUAPI  cudaMUSDia_extract( usVector Y, usPMatrix MA, ui len );


/**********  Deleting or inserting a row or a column *****************/

overror_t __vcuf OVCUAPI  cudaMUSRow_delete( usPMatrix MB, usPMatrix MA, ui htA, ui lenA, ui iRow );
overror_t __vcuf OVCUAPI  cudaMUSCol_delete( usPMatrix MB, usPMatrix MA, ui htA, ui lenA, ui iCol );
overror_t __vcuf OVCUAPI  cudaMUSRow_insert( usPMatrix MB, usPMatrix MA, ui htB, ui lenB, ui iRow, usVector X );
overror_t __vcuf OVCUAPI  cudaMUSCol_insert( usPMatrix MB, usPMatrix MA, ui htB, ui lenB, ui iCol, usVector X );


/******  One-dimensional vector operations **********************
         performed along all rows or all columns simultaneously,
         or along the diagonal of a square matrix                */

overror_t  __vcuf OVCUAPI  cudaMUSRows_max( usVector Y, usPMatrix MA, ui ht, ui len );
overror_t  __vcuf OVCUAPI  cudaMUSCols_max( usVector Y, usPMatrix MA, ui ht, ui len );
overror_t  __vcuf OVCUAPI  cudaMUSDia_max(  unsigned short *h_RetVal, usPMatrix MA, ui len );
overror_t  __vcuf OVCUAPI  cusdMUSDia_max(  unsigned short *d_RetVal, usPMatrix MA, ui len );
overror_t  __vcuf OVCUAPI  cudaMUSRows_min( usVector Y, usPMatrix MA, ui ht, ui len );
overror_t  __vcuf OVCUAPI  cudaMUSCols_min( usVector Y, usPMatrix MA, ui ht, ui len );
overror_t  __vcuf OVCUAPI  cudaMUSDia_min(  unsigned short *h_RetVal, usPMatrix MA, ui len );
overror_t  __vcuf OVCUAPI  cusdMUSDia_min(  unsigned short *d_RetVal, usPMatrix MA, ui len );

overror_t  __vcuf OVCUAPI  cudaMUSRows_rotate( usPMatrix MA, ui ht, ui len, ssize_t pos );
overror_t  __vcuf OVCUAPI  cudaMUSCols_rotate( usPMatrix MA, ui ht, ui len, ssize_t pos );
overror_t  __vcuf OVCUAPI  cudaMUSRows_rotate_buf( usPMatrix MA, ui ht, ui len, ssize_t pos, usPMatrix MBuf );
overror_t  __vcuf OVCUAPI  cudaMUSCols_rotate_buf( usPMatrix MA, ui ht, ui len, ssize_t pos, usPMatrix MBuf );
overror_t  __vcuf OVCUAPI  cudaMUSRows_reflect( usPMatrix MA, ui ht, ui len );
overror_t  __vcuf OVCUAPI  cudaMUSCols_reflect( usPMatrix MA, ui ht, ui len );
overror_t  __vcuf OVCUAPI  cudaMUSRows_rev( usPMatrix MA, ui ht, ui len );
overror_t  __vcuf OVCUAPI  cudaMUSCols_rev( usPMatrix MA, ui ht, ui len );
overror_t  __vcuf OVCUAPI  cudaMUSRows_distribution( uiPMatrix MAbund, usVector Limits, ui nBins, usPMatrix MX, ui ht, ui len, int mode );
overror_t  __vcuf OVCUAPI  cudaMUSCols_distribution( uiPMatrix MAbund, usVector Limits, ui nBins, usPMatrix MX, ui ht, ui len, int mode );

/********  Operations involving two rows or two colums of one matrix  *****/

overror_t   __vcuf OVCUAPI  cudaMUSRows_exchange( usPMatrix MA, ui ht, ui len, ui i1, ui i2 );
overror_t   __vcuf OVCUAPI  cudaMUSCols_exchange( usPMatrix MA, ui ht, ui len, ui i1, ui i2 );

/****************  Transposing and rotating a matrix **********************/

overror_t  __vcuf OVCUAPI  cudaMUStranspose( usPMatrix MTr, usPMatrix MA, ui htTr, ui lenTr );
overror_t  __vcuf OVCUAPI  cudaMUSrotate90(  usPMatrix MRot, usPMatrix MA, ui htRot, ui lenRot );
#define       cudaMUSrotate180( MRot, MA, htRot, lenRot ) cudaVUS_rev( MRot, MA, (htRot)*(lenRot) )
overror_t  __vcuf OVCUAPI  cudaMUSrotate270( usPMatrix MRot, usPMatrix MA, ui htRot, ui lenRot );
overror_t  __vcuf OVCUAPI  cudaMUStranspose_buf( usPMatrix MTr, usPMatrix MA, ui htTr, ui lenTr, usPMatrix MBuf );

/**************************  Input and Output  **************************
	The input/output functions involve memory transfers from device
	to host memory or vice versa. The generic cudaMUS_input/output functions
	allocate their own host buffers, whereas the cudaMUS_xxx_buf functions
	take a user-supplied buffer vector h_Wk (size must be >= ht*len )
	and are much more efficient.                                       */

#define cudaMUSprint( MA, ht, len )  cudaMUSfprint( stdout, MA, ht, len, 80 )
overror_t __vf cudaMUSfprint( FILE *stream, usPMatrix MA, ui ht, ui len, unsigned linewidth );
overror_t __vf cudaMUScprint( usPMatrix MA, ui ht, ui len );
#define cudaMUSprint_buf( MA, ht, len, h_Wk )  cudaMUSfprint_buf( stdout, MA, ht, len, 80, h_Wk )
overror_t __vf cudaMUSfprint_buf( FILE *stream, usPMatrix MA, ui ht, ui len, unsigned linewidth, usVector h_Wk );
overror_t __vf cudaMUScprint_buf( usPMatrix MA, ui ht, ui len, usVector h_Wk );
overror_t __vf cudaMUSwrite( FILE *stream, usPMatrix X, ui ht, ui len  );
overror_t __vf cudaMUSread( usPMatrix X, ui ht, ui len, FILE *stream );
overror_t __vf cudaMUSwrite_buf( FILE *stream, usPMatrix X, ui ht, ui len, usVector h_Wk );
overror_t __vf cudaMUSread_buf( usPMatrix X, ui ht, ui len, FILE *stream, usVector h_Wk );
#define cudaMUSstore( str, MA, ht, len ) cudaVUS_store( str, MA, (len)*(ht) )
#define cudaMUSrecall( MA, ht, len, str) cudaVUS_recall( MA, (len)*(ht), str)
#define cudaMUSstore_buf( str, MA, ht, len, h_Wk ) cudaVUS_store( str, MA, (len)*(ht), h_Wk )
#define cudaMUSrecall_buf( MA, ht, len, str, h_Wk) cudaVUS_recall( MA, (len)*(ht), str, h_Wk)




/***************************************************************************
    cudaMUS_func	(working on matrices in device memory, input type siMatrix, 
	             scalar parameters reside on host and are passed by value)
    cusdMUS_func	(as cudaMUS_func except scalar parameters reside on device 
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

inline void    cudaMUS_setElement( usMatrix MA, ui ht, ui len, ui m, ui n, unsigned short C )
	{	cudaMUSsetElement( (usPMatrix)(MA), ht, len, m, n, C );}
inline void    cusdMUS_setElement( usMatrix MA, ui ht, ui len, ui m, ui n, unsigned short *d_C )
	{	cusdMUSsetElement( (usPMatrix)(MA), ht, len, m, n, d_C );}
inline void    cudaMUS_getElement( unsigned short *y, usMatrix MA, ui ht, ui len, ui m, ui n )
	{	cudaMUSgetElement( y, (usPMatrix)(MA), ht, len, m, n );}
inline void    cusdMUS_getElement( unsigned short *d_y, usMatrix MA, ui ht, ui len, ui m, ui n )
	{	cusdMUSgetElement( d_y, (usPMatrix)(MA), ht, len, m, n );}
inline unsigned short * cudaMUS_Pelement( usMatrix MA, ui ht, ui len, ui m, ui n )
	{	return cudaMUSPelement( (usPMatrix)(MA), ht, len, m, n );}
inline unsigned short   cudaMUS_element( usMatrix MA, ui ht, ui len, ui m, ui n )
{	return cudaMUSelement( (usPMatrix)(MA), ht, len, m, n );}

inline overror_t  cudaMUS_equ0( usMatrix MA, ui ht, ui len )
	{	return cudaVUS_equ0( (usPMatrix)MA, (ht)*(len) ); }
inline overror_t  cudaMUS_equ1( usMatrix MA, ui len )
	{	return cudaMUSequ1( (usPMatrix)(MA), len );} /* identity matrix */

inline overror_t  cudaMUS_randomLC( usMatrix MA, ui ht, ui len, long seed, unsigned short MinVal, unsigned short MaxVal, V_RANDOMLCSTATE *h_state )
	{	return cudaVUS_randomLC( (usPMatrix)(MA), (ht)*(len), seed, MinVal, MaxVal, h_state );}
inline overror_t  cudaMUS_random( usMatrix MA, ui ht, ui len, long seed, unsigned short MinVal, unsigned short MaxVal )
	{	return cudaVUS_random( (usPMatrix)(MA), (ht)*(len), seed, MinVal, MaxVal );}
inline overror_t  cusdMUS_randomLC( usMatrix MA, ui ht, ui len, long seed, unsigned short *d_MinVal, unsigned short *d_MaxVal, V_RANDOMLCSTATE *h_state )
	{	return cusdVUS_randomLC( (usPMatrix)(MA), (ht)*(len), seed, d_MinVal, d_MaxVal, h_state );}
inline overror_t  cusdMUS_random( usMatrix MA, ui ht, ui len, long seed, unsigned short *d_MinVal, unsigned short *d_MaxVal )
	{	return cusdVUS_random( (usPMatrix)(MA), (ht)*(len), seed, d_MinVal, d_MaxVal );}
inline overror_t  cudaMUS_outerprod( usMatrix MA, usVector X,  usVector Y, ui ht, ui len )
{	return cudaMUSouterprod( (usPMatrix)(MA), X, Y, ht, len );}

inline overror_t  cudaMUS_Row_equ0( usMatrix MA, ui ht, ui len, ui iRow )
	{	return cudaMUSRow_equ0( (usPMatrix)MA, ht, len, iRow );}
inline overror_t  cudaMUS_Col_equ0( usMatrix MA, ui ht, ui len, ui iRow )
	{	return cudaMUSCol_equ0( (usPMatrix)MA, ht, len, iRow );}
inline overror_t  cudaMUS_Dia_equ0( usMatrix MA, ui len )
	{	return cudaMUSDia_equ0( (usPMatrix)(MA), len );}

inline overror_t  cudaMUS_Row_equC( usMatrix MA, ui ht, ui len, ui iRow, unsigned short C )
	{	return cudaMUSRow_equC( (usPMatrix)MA, ht, len, iRow, C );}
inline overror_t  cudaMUS_Col_equC( usMatrix MA, ui ht, ui len, ui iRow, unsigned short C )
	{	return cudaMUSCol_equC( (usPMatrix)MA, ht, len, iRow, C );}
inline overror_t  cudaMUS_Dia_equC( usMatrix MA, ui len, unsigned short C )
	{	return cudaMUSDia_equC( (usPMatrix)(MA), len, C );}

inline overror_t  cusdMUS_Row_equC( usMatrix MA, ui ht, ui len, ui iRow, unsigned short *d_C )
	{	return cusdMUSRow_equC( (usPMatrix)MA, ht, len, iRow, d_C );}
inline overror_t  cusdMUS_Col_equC( usMatrix MA, ui ht, ui len, ui iRow, unsigned short *d_C )
	{	return cusdMUSCol_equC( (usPMatrix)MA, ht, len, iRow, d_C );}
inline overror_t  cusdMUS_Dia_equC( usMatrix MA, ui len, unsigned short *d_C )
	{	return cusdMUSDia_equC( (usPMatrix)(MA), len, d_C );}

inline overror_t  cudaMUS_Row_equV( usMatrix MA, ui ht, ui len, ui iRow, usVector X )
	{	return cudaMUSRow_equV( (usPMatrix)MA, ht, len, iRow, X );}
inline overror_t  cudaMUS_Col_equV( usMatrix MA, ui ht, ui len, ui iRow, usVector X )
	{	return cudaMUSCol_equV( (usPMatrix)MA, ht, len, iRow, X );}
inline overror_t  cudaMUS_Dia_equV( usMatrix MA, ui len, usVector X )
	{	return cudaMUSDia_equV( (usPMatrix)(MA), len, X );}

inline overror_t  cudaMUS_Trd_equM( usMatrix MA, usMatrix MTrd, ui len )
	{	return cudaMUSTrd_equM( (usPMatrix)(MA), (usPMatrix)(MTrd), len );}
inline overror_t  cudaMUS_Trd_extract( usMatrix MTrd, usMatrix MA, ui len )
	{	return cudaMUSTrd_extract( (usPMatrix)(MTrd), (usPMatrix)(MA), len );}

inline overror_t cudaMUS_equM( usMatrix MB, usMatrix MA, ui ht, ui len )
	{	return cudaVUS_equV( (usPMatrix)MB, (usPMatrix)MA, (ht)*(len) );}
inline overror_t cudaMUS_equMhost( usMatrix d_MB, usMatrix h_MA, ui ht, ui len )
	{	return cudaVUS_equVhost( (usPMatrix)d_MB, (h_MA)[0], (ht)*(len) );}
inline overror_t MUS_equMdevice( usMatrix h_MB, usMatrix d_MA, ui ht, ui len )
	{	return VUS_equVdevice( h_MB[0], (usPMatrix)d_MA, (ht)*(len) );}
inline overror_t  cudaMUS_UequL( usMatrix MA, ui len )
	{	return cudaMUSUequL( (usPMatrix)(MA), len );}
inline overror_t  cudaMUS_LequU( usMatrix MA, ui len )
	{	return cudaMUSLequU( (usPMatrix)(MA), len );}

/************** Data-type interconversions  ****************************/

inline overror_t cudaM_SItoUS( usMatrix MUS, siMatrix MSI, ui ht, ui len )
	{	return cudaV_SItoUS( (usVector)MUS, (siVector)MSI, (ht)*(len) );}
inline overror_t cudaM_UBtoUS( usMatrix MUS, ubMatrix MUB, ui ht, ui len )
	{	return cudaV_UBtoUS( (usVector)MUS, (ubVector)MUB, (ht)*(len) );}
inline overror_t cudaM_UtoUS(  usMatrix MUS, uMatrix MU,  ui ht, ui len )
	{	return cudaV_UtoUS(  (usVector)MUS, (uVector)MU,   (ht)*(len) );}
inline overror_t cudaM_ULtoUS( usMatrix MUS, ulMatrix MUL, ui ht, ui len )
	{	return cudaV_ULtoUS( (usVector)MUS, (ulVector)MUL, (ht)*(len) );}
#ifdef _WIN64
	inline overror_t cudaM_UQtoUS( usMatrix MUS, uqMatrix MUQ, ui ht, ui len )
		{	return cudaV_UQtoUS( (usVector)MUS, (uqVector)MUQ, (ht)*(len) );}
#endif
inline overror_t cudaM_UStoF(  fMatrix MF,  usMatrix MUS, ui ht, ui len )
	{	return cudaV_UStoF(  (fVector)MF,   (usVector)MUS, (ht)*(len) );}
inline overror_t cudaM_UStoD(  dMatrix MD,  usMatrix MUS, ui ht, ui len )
	{	return cudaV_UStoD(  (dVector)MD,   (usVector)MUS, (ht)*(len) );}

/********  Extracting a submatrix and copying a submatrix back  *********/

inline overror_t cudaMUS_submatrix( usMatrix MSub, ui subHt, ui subLen, usMatrix MSrce, ui srceHt, ui srceLen,
                      ui firstRowInCol, ui sampInCol, ui firstColInRow, ui sampInRow )
	{	return cudaMUSsubmatrix(  (usPMatrix)(MSub), subHt, subLen,
		                         (usPMatrix)(MSrce), srceHt, srceLen,
								 firstRowInCol, sampInCol, firstColInRow, sampInRow ); }

inline overror_t cudaMUS_submatrix_equM( usMatrix MDest, ui destHt, ui destLen,
                           ui firstRowInCol, ui sampInCol, ui firstColInRow, ui sampInRow,
                           usMatrix MSrce, ui srceHt, ui srceLen )
	{	return cudaMUSsubmatrix_equM(  (usPMatrix)(MDest), destHt, destLen,
                             firstRowInCol, sampInCol, firstColInRow, sampInRow,
							 (usPMatrix)(MSrce), srceHt, srceLen );}

inline overror_t cudaMUS_equMblock( usMatrix MSub, ui subHt, ui subLen, usMatrix MSrce, ui srceHt, ui srceLen,
                      ui firstRowInCol, ui firstColInRow )
{	return cudaMUSequMblock(  (usPMatrix)(MSub), subHt, subLen,
						   (usPMatrix)(MSrce), srceHt, srceLen, firstRowInCol, firstColInRow );}

inline overror_t cudaMUS_block_equM( usMatrix MDest, ui destHt, ui destLen,
                       ui firstRowInCol, ui firstColInRow,
                       usMatrix MSrce, ui srceHt, ui srceLen )
	{	return cudaMUSblock_equM( (usPMatrix)(MDest), destHt, destLen,
                             firstRowInCol, firstColInRow,
							 (usPMatrix)(MSrce), srceHt, srceLen );}

inline overror_t cudaMUS_equMblockT( usMatrix MSub, ui subHt, ui subLen, usMatrix MSrce, ui srceHt, ui srceLen,
                      ui firstRowInCol, ui firstColInRow )
	{	return cudaMUSequMblockT(  (usPMatrix)(MSub), subHt, subLen,
                             (usPMatrix)(MSrce), srceHt, srceLen,
							 firstRowInCol, firstColInRow );}

inline overror_t cudaMUS_block_equMT( usMatrix MDest, ui destHt, ui destLen,
                       ui firstRowInCol, ui firstColInRow,
                       usMatrix MSrce, ui srceHt, ui srceLen )
	{	return cudaMUSblock_equMT( (usPMatrix)(MDest), destHt, destLen,
                             firstRowInCol, firstColInRow,
							 (usPMatrix)(MSrce), srceHt, srceLen );}

/*****   Extracting a single row or a single column or the diagonal  ******
 *       and storing it into a vector                                     */

inline overror_t cudaMUS_Row_extract( usVector Y, usMatrix MA, ui ht, ui len, ui iRow ) 
	{	return cudaMUSRow_extract( Y, (usPMatrix)(MA), ht, len, iRow );}
inline overror_t cudaMUS_Col_extract( usVector Y, usMatrix MA, ui ht, ui len, ui iCol ) 
	{	return cudaMUSCol_extract( Y, (usPMatrix)(MA), ht, len, iCol );}
inline overror_t cudaMUS_Dia_extract( usVector Y, usMatrix MA, ui len )
	{	return cudaMUSDia_extract( Y, (usPMatrix)(MA), len );}

/**************  Deleting or inserting a row or a column   ***************/

inline overror_t cudaMUS_Row_delete( usMatrix MB, usMatrix MA, ui htA, ui lenA, ui iRow )
	{	return cudaMUSRow_delete( (usPMatrix)(MB), (usPMatrix)(MA), htA, lenA, iRow );}
inline overror_t cudaMUS_Col_delete( usMatrix MB, usMatrix MA, ui htA, ui lenA, ui iCol )
	{	return cudaMUSCol_delete( (usPMatrix)(MB), (usPMatrix)(MA), htA, lenA, iCol );}
inline overror_t cudaMUS_Row_insert( usMatrix MB, usMatrix MA, ui htB, ui lenB, ui iRow, usVector X )
	{	return cudaMUSRow_insert( (usPMatrix)(MB), (usPMatrix)(MA), htB, lenB, iRow, X );}
inline overror_t cudaMUS_Col_insert( usMatrix MB, usMatrix MA, ui htB, ui lenB, ui iCol, usVector X )
	{	return cudaMUSCol_insert( (usPMatrix)(MB), (usPMatrix)(MA), htB, lenB, iCol, X );}


/******  One-dimensional vector operations **********************
         performed along all rows or all columns simultaneously,
         or along the diagonal of a square matrix                */

inline overror_t cudaMUS_Rows_max( usVector Y, usMatrix MA, ui ht, ui len )
	{	return cudaMUSRows_max( Y, (usPMatrix)(MA), ht, len );}
inline overror_t cudaMUS_Cols_max( usVector Y, usMatrix MA, ui ht, ui len )
	{	return cudaMUSCols_max( Y, (usPMatrix)(MA), ht, len );}
inline overror_t cudaMUS_Dia_max(  unsigned short *h_RetValPtr, usMatrix MA, ui len )
	{	return cudaMUSDia_max(  h_RetValPtr, (usPMatrix)(MA), len );}
inline overror_t cusdMUS_Dia_max(  unsigned short *d_RetValPtr, usMatrix MA, ui len )
	{	return cusdMUSDia_max(  d_RetValPtr, (usPMatrix)(MA), len );}
inline overror_t cudaMUS_Rows_min( usVector Y, usMatrix MA, ui ht, ui len )
	{	return cudaMUSRows_min( Y, (usPMatrix)(MA), ht, len );}
inline overror_t cudaMUS_Cols_min( usVector Y, usMatrix MA, ui ht, ui len )
	{	return cudaMUSCols_min( Y, (usPMatrix)(MA), ht, len );}
inline overror_t cudaMUS_Dia_min(  unsigned short *h_RetValPtr, usMatrix MA, ui len )
	{	return cudaMUSDia_min(  h_RetValPtr, (usPMatrix)(MA), len );}
inline overror_t cusdMUS_Dia_min(  unsigned short *d_RetValPtr, usMatrix MA, ui len )
	{	return cusdMUSDia_min(  d_RetValPtr, (usPMatrix)(MA), len );}

inline overror_t cudaMUS_Rows_rotate( usMatrix MA, ui ht, ui len, ssize_t pos)
	{	return cudaMUSRows_rotate( (usPMatrix)(MA), ht, len, pos );}
inline overror_t cudaMUS_Cols_rotate( usMatrix MA, ui ht, ui len, ssize_t pos)
	{	return cudaMUSCols_rotate( (usPMatrix)(MA), ht, len, pos );}
inline overror_t cudaMUS_Rows_rotate_buf( usMatrix MA, ui ht, ui len, ssize_t pos, usMatrix MBuf) 
	{	return cudaMUSRows_rotate_buf( (usPMatrix)(MA), ht, len, pos, (usPMatrix)(MBuf) );}
inline overror_t cudaMUS_Cols_rotate_buf( usMatrix MA, ui ht, ui len, ssize_t pos, usMatrix MBuf) 
	{	return cudaMUSCols_rotate_buf( (usPMatrix)(MA), ht, len, pos, (usPMatrix)(MBuf) );}
inline overror_t cudaMUS_Rows_reflect( usMatrix MA, ui ht, ui len )
	{	return cudaMUSRows_reflect( (usPMatrix)(MA), ht, len );}
inline overror_t cudaMUS_Cols_reflect( usMatrix MA, ui ht, ui len )
	{	return cudaMUSCols_reflect( (usPMatrix)(MA), ht, len );}
inline overror_t cudaMUS_Rows_rev( usMatrix MA, ui ht, ui len )
	{	return cudaMUSRows_rev( (usPMatrix)(MA), ht, len );}
inline overror_t cudaMUS_Cols_rev( usMatrix MA, ui ht, ui len )
	{	return cudaMUSCols_rev( (usPMatrix)(MA), ht, len );}
inline overror_t  cudaMUS_Rows_distribution( uiMatrix MAbund, usVector Limits, ui nBins, usMatrix MX, ui ht, ui len, int mode )
	{	return cudaMUSRows_distribution( (uiPMatrix)MAbund, Limits, nBins, (usPMatrix)MX, ht, len, mode ); }
inline overror_t  cudaMUS_Cols_distribution( uiMatrix MAbund, usVector Limits, ui nBins, usMatrix MX, ui ht, ui len, int mode )
	{	return cudaMUSCols_distribution( (uiPMatrix)MAbund, Limits, nBins, (usPMatrix)MX, ht, len, mode ); }

/********  Operations involving two rows or two colums of one matrix  *****/

inline overror_t cudaMUS_Rows_exchange( usMatrix MA, ui ht, ui len, ui row1, ui row2 )
	{	return cudaMUSRows_exchange( (usPMatrix)(MA), ht, len, row1, row2 );}
inline overror_t cudaMUS_Cols_exchange( usMatrix MA, ui ht, ui len, ui col1, ui col2 )
	{	return cudaMUSCols_exchange( (usPMatrix)(MA), ht, len, col1, col2 );}

/*************** Transposing and rotating a matrix **********************/

inline overror_t cudaMUS_transpose( usMatrix MTr, usMatrix MA, ui htTr, ui lenTr )
	{	return cudaMUStranspose( (usPMatrix)(MTr), (usPMatrix)(MA), htTr, lenTr );}
       /*  dimensions htTr, lenTr are those of the transposed matrix, not of the original!   */
inline overror_t cudaMUS_rotate90( usMatrix MRot, usMatrix MA, ui htRot, ui lenRot )
	{	return cudaMUSrotate90( (usPMatrix)(MRot), (usPMatrix)(MA), htRot, lenRot );}
inline overror_t cudaMUS_rotate180( usMatrix MRot, usMatrix MA, ui htRot, ui lenRot )
	{	return cudaVUS_rev( (usPMatrix)(MRot), (usPMatrix)(MA), (htRot)*(lenRot) );}
inline overror_t cudaMUS_rotate270( usMatrix MRot, usMatrix MA, ui htRot, ui lenRot )
	{	return cudaMUSrotate270( (usPMatrix)(MRot), (usPMatrix)(MA), htRot, lenRot );}
inline overror_t cudaMUS_transpose_buf( usMatrix MTr, usMatrix MA, ui htTr, ui lenTr, usMatrix MBuf )
	{	return cudaMUStranspose_buf( (usPMatrix)(MTr), (usPMatrix)(MA), htTr, lenTr, (usPMatrix)(MBuf) );}

/**************************  Input and Output  **************************
	The input/output functions involve memory transfers from device
	to host memory or vice versa. The generic cudaMUS_input/output functions
	allocate their own host buffers, whereas the cudaMUS_xxx_buf functions
	take a user-supplied buffer vector h_Wk (size must be >= ht*len )
	and are much more efficient.                                       */

inline overror_t cudaMUS_fprint( FILE *stream, usMatrix MA, ui ht, ui len, unsigned linewidth )
	{	return cudaMUSfprint( stream, (usPMatrix)(MA), ht, len, linewidth ); }
inline overror_t cudaMUS_print( usMatrix MA, ui ht, ui len )
	{	return cudaMUSfprint( stdout, (usPMatrix)(MA), ht, len, 80 ); }
inline overror_t cudaMUS_cprint( usMatrix MA, ui ht, ui len )
	{	return cudaMUScprint( (usPMatrix)(MA), ht, len ); }
inline overror_t cudaMUS_fprint_buf( FILE *stream, usMatrix d_MA, ui ht, ui len, unsigned linewidth, usVector h_Wk )
	{	return cudaMUSfprint_buf( stream, (usPMatrix)(d_MA), ht, len, linewidth, h_Wk ); }
inline overror_t cudaMUS_print_buf( usMatrix d_MA, ui ht, ui len, usVector h_Wk )
	{	return cudaMUSfprint_buf( stdout, (usPMatrix)(d_MA), ht, len, 80, h_Wk ); }
inline overror_t cudaMUS_cprint_buf( usMatrix d_MA, ui ht, ui len, usVector h_Wk )
	{	return cudaMUScprint_buf( (usPMatrix)(d_MA), ht, len, h_Wk ); }
		/*  cudaMUS_print, cudaMUS_cprint usable only for console applications! */
inline overror_t  cudaMUS_write( FILE *stream, usMatrix MA, ui ht, ui len )
	{	return cudaMUSwrite( stream, (usPMatrix)(MA), ht, len ); }
inline overror_t cudaMUS_read( usMatrix MA, ui ht, ui len, FILE *stream )
	{	return cudaMUSread( (usPMatrix)(MA), ht, len, stream ); }
inline overror_t  cudaMUS_write_buf( FILE *stream, usMatrix d_MA, ui ht, ui len, usVector h_Wk )
	{	return cudaMUSwrite_buf( stream, (usPMatrix)(d_MA), ht, len, h_Wk ); }
inline overror_t cudaMUS_read_buf( usMatrix d_MA, ui ht, ui len, FILE *stream, usVector h_Wk )
	{	return cudaMUSread_buf( (usPMatrix)(d_MA), ht, len, stream, h_Wk ); }
                                   /* write and read in ascii format */
inline overror_t cudaMUS_store( FILE *stream, usMatrix MA, ui ht, ui len )
{	return cudaVUS_store( stream, (usPMatrix)(MA), (len)*(ht) ); }
inline overror_t cudaMUS_recall( usMatrix MA, ui ht, ui len, FILE *stream )
	{	return cudaVUS_recall( (usPMatrix)(MA), (len)*(ht), stream ); }
inline overror_t cudaMUS_store_buf( FILE *stream, usMatrix d_MA, ui ht, ui len, usVector h_Wk )
{	return cudaVUS_store_buf( stream, (usPMatrix)(d_MA), (len)*(ht), h_Wk ); }
inline overror_t cudaMUS_recall_buf( usMatrix d_MA, ui ht, ui len, FILE *stream, usVector h_Wk )
	{	return cudaVUS_recall_buf( (usPMatrix)(d_MA), (len)*(ht), stream, h_Wk ); }
                                  /* store and recall in binary format */

#else  /* plain-C, not C++: type-cast used to transform usMatrix into usPMatrix */


/***  Addressing single elements of dynamically allocated matrices: ******/

#define cudaMUS_setElement( MA, ht, len, m, n, C ) cudaMUSsetElement( (usPMatrix)(MA), ht, len, m, n, C )
#define cusdMUS_setElement( MA, ht, len, m, n, C ) cusdMUSsetElement( (usPMatrix)(MA), ht, len, m, n, C )
#define cudaMUS_getElement( y, MA, ht, len, m, n ) cudaMUSgetElement( y, (usPMatrix)(MA), ht, len, m, n )
#define cusdMUS_getElement( y, MA, ht, len, m, n ) cusdMUSgetElement( y, (usPMatrix)(MA), ht, len, m, n )
#define cudaMUS_Pelement( MA, ht, len, m, n )      cudaMUSPelement( (usPMatrix)(MA), ht, len, m, n )
#define cudaMUS_element(  MA, ht, len, m, n )      cudaMUSelement( (usPMatrix)(MA), ht, len, m, n )

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
        cudaVUS_equ1( (usVector)MA, ht * len );
*/

#define cudaMUS_equ0( MA, ht, len )            cudaVUS_equ0( (usPMatrix)(MA), (ht)*(len) )
#define cudaMUS_equ1( MA, len )                cudaMUSequ1( (usPMatrix)(MA), len ) /* identity matrix */
#define cudaMUS_randomLC( MA, ht, len, seed, Min, Max, h_state )      cudaVUS_randomLC( MA, (ht)*(len), seed, Min, Max, h_state )
#define cudaMUS_random( MA, ht, len, seed, Min, Max )                 cudaVUS_random( MA, (ht)*(len), seed, Min, Max )
#define cusdMUS_randomLC( MA, ht, len, seed, d_Min, d_Max, h_state )  cudaVUS_randomLC( MA, (ht)*(len), seed, d_Min, d_Max, h_state )
#define cusdMUS_random( MA, ht, len, seed, d_Min, d_Max )             cudaVUS_random( MA, (ht)*(len), seed, d_Min, d_Max )
#define cudaMUS_outerprod( MA, X, Y, ht, len ) cudaMUSouterprod( (usPMatrix)(MA), X, Y, ht, len )
                       /* sizX=ht, sizY=len */
#define cudaMUS_Row_equ0( MA, ht, len, iRow )    cudaMUSRow_equ0( (usPMatrix)(MA), ht, len, iRow )
#define cudaMUS_Col_equ0( MA, ht, len, iCol )    cudaMUSCol_equ0( (usPMatrix)(MA), ht, len, iCol )
#define cudaMUS_Dia_equ0( MA, len )              cudaMUSDia_equ0( (usPMatrix)(MA), len )
#define cudaMUS_Row_equC( MA, ht, len, iRow, C ) cudaMUSRow_equC( (usPMatrix)(MA), ht, len, iRow, C )
#define cudaMUS_Col_equC( MA, ht, len, iCol, C ) cudaMUSCol_equC( (usPMatrix)(MA), ht, len, iCol, C )
#define cudaMUS_Dia_equC( MA, len, C )           cudaMUSDia_equC( (usPMatrix)(MA), len, C )
#define cusdMUS_Row_equC( MA, ht, len, iRow, d_C ) cusdMUSRow_equC( (usPMatrix)(MA), ht, len, iRow, d_C )
#define cusdMUS_Col_equC( MA, ht, len, iCol, d_C ) cusdMUSCol_equC( (usPMatrix)(MA), ht, len, iCol, d_C )
#define cusdMUS_Dia_equC( MA, len, d_C )           cusdMUSDia_equC( (usPMatrix)(MA), len, d_C )

#define cudaMUS_Row_equV( MA, ht, len, iRow, X ) cudaMUSRow_equV( (usPMatrix)(MA), ht, len, iRow, X )
#define cudaMUS_Col_equV( MA, ht, len, iCol, X ) cudaMUSCol_equV( (usPMatrix)(MA), ht, len, iCol, X )
#define cudaMUS_Dia_equV( MA, len, X )           cudaMUSDia_equV( (usPMatrix)(MA), len, X )

#define cudaMUS_Trd_equM( MA, MTrd, len )    cudaMUSTrd_equM( (usPMatrix)(MA), (usPMatrix)(MTr)d, len )
#define cudaMUS_Trd_extract( MTrd, MA, len ) cudaMUSTrd_extract( (usPMatrix)(MTr)d, (usPMatrix)(MA), len )

#define cudaMUS_equM( MB, MA, ht, len )      cudaVUS_equV( (usPMatrix)(MB), (usPMatrix)(MA), (ht)*(len) )
#define cudaMUS_equMhost( MB, MA, ht, len )  cudaVUS_equVhost( (usPMatrix)(MB), MA[0], (ht)*(len) )
#define MUS_equMdevice( MB, MA, ht, len )    VUS_equVdevice( MB[0], (usPMatrix)(MA), (ht)*(len) )

#define cudaMUS_UequL( MA, len ) cudaMUSUequL( (usPMatrix)(MA), len )
#define cudaMUS_LequU( MA, len ) cudaMUSLequU( (usPMatrix)(MA), len )

/************** Data-type interconversions  ****************************/

#define cudaM_UStoSI( MSI, MUS, ht, len ) cudaV_UStoSI( (siVector)(MSI), (usVector)(MUS), (ht)*(len) )
#define cudaM_SItoUS( MUS, MSI, ht, len ) cudaV_SItoUS( (ubVector)(MUS), (siVector)(MSI), (ht)*(len) )
#define cudaM_UStoUB( MUB, MUS, ht, len ) cudaV_UStoUB( (ubVector)(MUB), (usVector)(MUS), (ht)*(len) )
#define cudaM_UStoU(  MU,  MUS, ht, len ) cudaV_UStoU(  (uVector)(MU),   (usVector)(MUS), (ht)*(len) )
#define cudaM_UStoUL( MUL, MUS, ht, len ) cudaV_UStoUL( (ulVector)(MUL), (usVector)(MUS), (ht)*(len) )
#define cudaM_UBtoUS( MUS, MUB, ht, len ) cudaV_UBtoUS( (usVector)(MUS), (ubVector)(MUB), (ht)*(len) )
#define cudaM_UtoUS(  MUS, MU,  ht, len ) cudaV_UtoUS(  (usVector)(MUS), (uVector)(MU),   (ht)*(len) )
#define cudaM_ULtoUS( MUS, MUL, ht, len ) cudaV_ULtoUS( (usVector)(MUS), (ulVector)(MUL), (ht)*(len) )
#ifdef _WIN64
	#define cudaM_UStoUQ( MUQ, MUS, ht, len ) cudaV_UStoUQ( (uqVector)(MUQ), (usVector)(MUS), (ht)*(len) )
	#define cudaM_UQtoUS( MUS, MUQ, ht, len ) cudaV_UQtoUS( (usVector)(MUS), (uqVector)(MUQ), (ht)*(len) )
#endif
#define cudaM_UStoF(  MF,  MUS, ht, len ) cudaV_UStoF(  (fVector)(MF),   (usVector)(MUS), (ht)*(len) )
#define cudaM_UStoD(  MD,  MUS, ht, len ) cudaV_UStoD(  (dVector)(MD),   (usVector)(MUS), (ht)*(len) )


/********  Extracting a submatrix and copying a submatrix back  *********/

#define cudaMUS_submatrix( MSub, subHt, subLen, MSrce, srceHt, srceLen, \
                      firstRowInCol, sampInCol, firstColInRow, sampInRow ) \
               cudaMUSsubmatrix(  (usPMatrix)(MSub), subHt, subLen, \
                             (usPMatrix)(MSrce), srceHt, srceLen, \
                             firstRowInCol, sampInCol, firstColInRow, sampInRow )

#define cudaMUS_submatrix_equM( MDest, destHt, destLen, \
                           firstRowInCol, sampInCol, firstColInRow, sampInRow, \
                           MSrce, srceHt, srceLen ) \
               cudaMUSsubmatrix_equM(  (usPMatrix)(MDest), destHt, destLen, \
                             firstRowInCol, sampInCol, firstColInRow, sampInRow, \
                             (usPMatrix)(MSrce), srceHt, srceLen )

#define cudaMUS_equMblock( MSub, subHt, subLen, MSrce, srceHt, srceLen, \
                      firstRowInCol, firstColInRow ) \
               cudaMUSequMblock(  (usPMatrix)(MSub), subHt, subLen, \
                             (usPMatrix)(MSrce), srceHt, srceLen, \
                             firstRowInCol, firstColInRow )

#define cudaMUS_block_equM( MDest, destHt, destLen, \
                       firstRowInCol, firstColInRow, \
                       MSrce, srceHt, srceLen ) \
               cudaMUSblock_equM( (usPMatrix)(MDest), destHt, destLen, \
                             firstRowInCol, firstColInRow, \
                             (usPMatrix)(MSrce), srceHt, srceLen )

#define cudaMUS_equMblockT( MSub, subHt, subLen, \
                      MSrce, srceHt, srceLen, \
                      firstRowInCol, firstColInRow ) \
               cudaMUSequMblockT(  (usPMatrix)(MSub), subHt, subLen, \
                             (usPMatrix)(MSrce), srceHt, srceLen, \
                             firstRowInCol, firstColInRow )

#define cudaMUS_block_equMT( MDest, destHt, destLen, \
                       firstRowInCol, firstColInRow, \
                       MSrce, srceHt, srceLen ) \
               cudaMUSblock_equMT( (usPMatrix)(MDest), destHt, destLen, \
                             firstRowInCol, firstColInRow, \
                             (usPMatrix)(MSrce), srceHt, srceLen )

/*****   Extracting a single row or a single column or the diagonal  ******
 *       and storing it into a vector                                     */

#define cudaMUS_Row_extract( Y, MA, ht, len, iRow ) cudaMUSRow_extract( Y, (usPMatrix)(MA), ht, len, iRow )
#define cudaMUS_Col_extract( Y, MA, ht, len, iCol ) cudaMUSCol_extract( Y, (usPMatrix)(MA), ht, len, iCol )
#define cudaMUS_Dia_extract( Y, MA, len )           cudaMUSDia_extract( Y, (usPMatrix)(MA), len )


/**************  Deleting or inserting a row or a column   ***************/

#define cudaMUS_Row_delete( MB, MA, htA, lenA, iRow ) cudaMUSRow_delete( (usPMatrix)(MB), (usPMatrix)(MA), htA, lenA, iRow )
#define cudaMUS_Col_delete( MB, MA, htA, lenA, iCol ) cudaMUSCol_delete( (usPMatrix)(MB), (usPMatrix)(MA), htA, lenA, iCol )
#define cudaMUS_Row_insert( MB, MA, htB, lenB, iRow, X ) cudaMUSRow_insert( (usPMatrix)(MB), (usPMatrix)(MA), htB, lenB, iRow, X )
#define cudaMUS_Col_insert( MB, MA, htB, lenB, iCol, X ) cudaMUSCol_insert( (usPMatrix)(MB), (usPMatrix)(MA), htB, lenB, iCol, X )

/******  One-dimensional vector operations **********************
         performed along all rows or all columns simultaneously,
         or along the diagonal of a square matrix                */

#define cudaMUS_Rows_max( Y, MA, ht, len )     cudaMUSRows_max( Y, (usPMatrix)(MA), ht, len )
#define cudaMUS_Cols_max( Y, MA, ht, len )     cudaMUSCols_max( Y, (usPMatrix)(MA), ht, len )
#define cudaMUS_Dia_max(  h_RetPtr, MA, len )  cudaMUSDia_max( h_RetPtr, (usPMatrix)(MA), len )
#define cusdMUS_Dia_max(  d_RetPtr, MA, len )  cusdMUSDia_max( d_RetPtr, (usPMatrix)(MA), len )
#define cudaMUS_Rows_min( Y, MA, ht, len )     cudaMUSRows_min( Y, (usPMatrix)(MA), ht, len )
#define cudaMUS_Cols_min( Y, MA, ht, len )     cudaMUSCols_min( Y, (usPMatrix)(MA), ht, len )
#define cudaMUS_Dia_min(  h_RetPtr, MA, len )  cudaMUSDia_min( h_RetPtr, (usPMatrix)(MA), len )
#define cusdMUS_Dia_min(  d_RetPtr, MA, len )  cusdMUSDia_min( d_RetPtr, (usPMatrix)(MA), len )

#define cudaMUS_Rows_rotate( MA, ht, len, pos) cudaMUSRows_rotate( (usPMatrix)(MA), ht, len, pos )
#define cudaMUS_Cols_rotate( MA, ht, len, pos) cudaMUSCols_rotate( (usPMatrix)(MA), ht, len, pos )
#define cudaMUS_Rows_rotate_buf( MA, ht, len, pos, MBuf) cudaMUSRows_rotate_buf( (usPMatrix)(MA), ht, len, pos, (usPMatrix)(MBuf) )
#define cudaMUS_Cols_rotate_buf( MA, ht, len, pos, MBuf) cudaMUSCols_rotate_buf( (usPMatrix)(MA), ht, len, pos, (usPMatrix)(MBuf) )
#define cudaMUS_Rows_reflect( MA, ht, len)     cudaMUSRows_reflect( (usPMatrix)(MA), ht, len )
#define cudaMUS_Cols_reflect( MA, ht, len)     cudaMUSCols_reflect( (usPMatrix)(MA), ht, len )
#define cudaMUS_Rows_rev( MA, ht, len)         cudaMUSRows_rev( (usPMatrix)(MA), ht, len )
#define cudaMUS_Cols_rev( MA, ht, len)         cudaMUSCols_rev( (usPMatrix)(MA), ht, len )
#define cudaMUS_Rows_distribution( MAbund, Limits, nBins, MX, ht, len, mode ) cudaMUSRows_distribution( (uiPMatrix)MAbund, Limits, nBins, (usPMatrix)MX, ht, len, mode )
#define cudaMUS_Cols_distribution( MAbund, Limits, nBins, MX, ht, len, mode ) cudaMUSCols_distribution( (uiPMatrix)MAbund, Limits, nBins, (usPMatrix)MX, ht, len, mode )

/********  Operations involving two rows or two colums of one matrix  *****/

#define cudaMUS_Rows_exchange( MA, ht, len, row1, row2 ) cudaMUSRows_exchange( (usPMatrix)(MA), ht, len, row1, row2 )
#define cudaMUS_Cols_exchange( MA, ht, len, col1, col2 ) cudaMUSCols_exchange( (usPMatrix)(MA), ht, len, col1, col2 )

/****************  Transposing and rotating a matrix **********************/

#define cudaMUS_transpose( MTr, MA, htTr, lenTr ) cudaMUStranspose( (usPMatrix)(MTr), (usPMatrix)(MA), htTr, lenTr )
       /*  dimensions htTr, lenTr are those of the transposed matrix,
           not of the original!                */
#define cudaMUS_rotate90( MRot, MA, htRot, lenRot )  cudaMUSrotate90( (usPMatrix)(MRot), (usPMatrix)(MA), htRot, lenRot )
#define cudaMUS_rotate180( MRot, MA, htRot, lenRot ) cudaVUS_rev( (usPMatrix)(MRot), (usPMatrix)(MA), (htRot)*(lenRot) )
#define cudaMUS_rotate270( MRot, MA, htRot, lenRot ) cudaMUSrotate270( (usPMatrix)(MRot), (usPMatrix)(MA), htRot, lenRot )
#define cudaMUS_transpose_buf( MTr, MA, htTr, lenTr, MBuf ) cudaMUStranspose_buf( (usPMatrix)(MTr), (usPMatrix)(MA), htTr, lenTr, (usPMatrix)(MBuf) )

/**************************  Input and Output  **************************
	The input/output functions involve memory transfers from device
	to host memory or vice versa. The generic cudaMUS_input/output functions
	allocate their own host buffers, whereas the cudaMUS_xxx_buf functions
	take a user-supplied buffer vector h_Wk (size must be >= ht*len )
	and are much more efficient.                                       */

#define cudaMUS_fprint( stream, MA, ht, len, linewidth ) \
                    cudaMUSfprint( stream, (usPMatrix)(MA), ht, len, linewidth )
#define cudaMUS_print( MA, ht, len )  cudaMUSfprint( stdout, (usPMatrix)(MA), ht, len, 80 )
#define cudaMUS_cprint( MA, ht, len ) cudaMUScprint( (usPMatrix)(MA), ht, len )
#define cudaMUS_fprint_buf( stream, MA, ht, len, linewidth, h_Wk ) \
                    cudaMUSfprint_buf( stream, (usPMatrix)(MA), ht, len, linewidth, h_Wk )
#define cudaMUS_print_buf( MA, ht, len )  cudaMUSfprint_buf( stdout, (usPMatrix)(MA), ht, len, 80, h_Wk )
#define cudaMUS_cprint_buf( MA, ht, len ) cudaMUScprint_buf( (usPMatrix)(MA), ht, len, h_Wk )
  /*  cudaMUS_print, cudaMUS_cprint usable only for console applications! */
#define cudaMUS_write( str, MA, ht, len )   cudaMUSwrite( str, (usPMatrix)(MA), ht, len )
#define cudaMUS_read( MA, ht, len, str )    cudaMUSread( (usPMatrix)(MA), ht, len, str )
#define cudaMUS_write_buf( str, MA, ht, len, h_Wk )   cudaMUSwrite_buf( str, (usPMatrix)(MA), ht, len, h_Wk )
#define cudaMUS_read_buf( MA, ht, len, str, h_Wk )    cudaMUSread_buf( (usPMatrix)(MA), ht, len, str, h_Wk )
                                   /* write and read in ascii format */
#define cudaMUS_store( str, MA, ht, len )   cudaVUS_store( str, (usPMatrix)(MA), (len)*(ht) )
#define cudaMUS_recall( MA, ht, len, str)   cudaVUS_recall( (usPMatrix)(MA), (len)*(ht), str)
#define cudaMUS_store_buf( str, MA, ht, len, h_Wk )   cudaVUS_store_buf( str, (usPMatrix)(MA), (len)*(ht), h_Wk )
#define cudaMUS_recall_buf( MA, ht, len, str, h_Wk)   cudaVUS_recall_buf( (usPMatrix)(MA), (len)*(ht), str, h_Wk )
                                  /* store and recall in binary format */

#endif /* plain-C or C++ for functions working on device memory */


/*******************  Functions working on host memory: **********************
 *                                                                           *
 *	MSIcu_func		(working on matrices in host memory, input type siMatrix,*
 *	scalar parameters on host and passed by value)                           *
 *****************************************************************************/ 

/****************  Initialization  ****************************************/

#define MUScu_equ0( MA, ht, len )                   VUScu_equ0( (MA)[0], (ht)*(len) )
#define MUScu_equ1( MA, len )                       MUScuequ1( (MA)[0], len ) /* identity matrix */
#define MUScu_randomLC( MA, ht, len, seed, Min, Max, state ) VUScu_randomLC( (MA)[0], (ht)*(len), seed, Min, Max, state )
#define MUScu_random( MA, ht, len, seed, Min, Max )          VUScu_random( (MA)[0], (ht)*(len), seed, Min, Max )
#define MUScu_outerprod( MA, X, Y, ht, len )        MUScuouterprod( (MA)[0], X, Y, ht, len )
                       /* sizX=ht, sizY=len */
#define MUScu_Row_equ0( MA, ht, len, iRow )    MUScuRow_equ0( (MA)[0], ht, len, iRow )
#define MUScu_Col_equ0( MA, ht, len, iCol )    MUScuCol_equ0( (MA)[0], ht, len, iCol )
#define MUScu_Dia_equ0( MA, len )              MUScuDia_equ0( (MA)[0], len )
#define MUScu_Row_equC( MA, ht, len, iRow, C ) MUScuRow_equC( (MA)[0], ht, len, iRow, C )
#define MUScu_Col_equC( MA, ht, len, iCol, C ) MUScuCol_equC( (MA)[0], ht, len, iCol, C )
#define MUScu_Dia_equC( MA, len, C )           MUScuDia_equC( (MA)[0], len, C )

#define MUScu_Row_equV( MA, ht, len, iRow, X ) MUScuRow_equV( (MA)[0], ht, len, iRow, X )
#define MUScu_Col_equV( MA, ht, len, iCol, X ) MUScuCol_equV( (MA)[0], ht, len, iCol, X )
#define MUScu_Dia_equV( MA, len, X )           MUScuDia_equV( (MA)[0], len, X )

#define MUScu_Trd_equM( MA, MTrd, len )        MUScuTrd_equM( (MA)[0], (MTrd)[0], len )
#define MUScu_Trd_extract( MTrd, MA, len )     MUScuTrd_extract( (MTrd)[0], (MA)[0], len )

#define MUScu_equM( MB, MA, ht, len )          VUScu_equV( (MB)[0], (MA)[0], (ht)*(len) )
#define MUScu_equMhost( MB, MA, ht, len )      VUScu_equVhost( (MB)[0], MA[0], (ht)*(len) )

#define MUScu_UequL( MA, len ) MUScuUequL( (MA)[0], len )
#define MUScu_LequU( MA, len ) MUScuLequU( (MA)[0], len )
     /* copy lower-diagonal elements into upper-diagonal
       (or vice versa) by index-reflection, so as to get a symmetric matrix    */

            /* data-type conversions:  */
#define Mcu_SItoUS( MUS, MSI, ht, len ) Vcu_SItoUS( (MUS)[0], (MSI)[0], (ht)*(len) )
#define Mcu_UStoSI( MSI, MUS, ht, len ) Vcu_UStoSI( (MSI)[0], (MUS)[0], (ht)*(len) )
#define Mcu_UStoUB( MUB, MUS, ht, len ) Vcu_UStoUB( (MUB)[0], (MUS)[0], (ht)*(len) )
#define Mcu_UStoU(  MU,  MUS, ht, len ) Vcu_UStoU(  (MU)[0],  (MUS)[0], (ht)*(len) )
#define Mcu_UStoUL( MUL, MUS, ht, len ) Vcu_UStoUL( (MUL)[0], (MUS)[0], (ht)*(len) )
#define Mcu_UBtoUS( MUS, MUB, ht, len ) Vcu_UBtoUS( (MUS)[0], (MUB)[0], (ht)*(len) )
#define Mcu_UtoUS(  MUS, MU,  ht, len ) Vcu_UtoUS(  (MUS)[0], (MU)[0],  (ht)*(len) )
#define Mcu_ULtoUS( MUS, MUL, ht, len ) Vcu_ULtoUS( (MUS)[0], (MUL)[0], (ht)*(len) )
#ifdef _WIN64
	#define Mcu_UStoUQ( MUQ, MUS, ht, len ) Vcu_UStoUQ( (MUQ)[0], (MUS)[0], (ht)*(len) )
	#define Mcu_UQtoUS( MUS, MUQ, ht, len ) Vcu_UQtoUS( (MUS)[0], (MUQ)[0], (ht)*(len) )
#endif
#define Mcu_UStoF(  MF,  MUS, ht, len ) Vcu_UStoF(  (MF)[0],  (MUS)[0], (ht)*(len) )
#define Mcu_UStoD(  MD,  MUS, ht, len ) Vcu_UStoD(  (MD)[0],  (MUS)[0], (ht)*(len) )


/********  Extracting a submatrix and copying a submatrix back  *********/

#define MUScu_submatrix( MSub, subHt, subLen, MSrce, srceHt, srceLen, \
                      firstRowInCol, sampInCol, firstColInRow, sampInRow ) \
               MUScusubmatrix(  (MSub)[0], subHt, subLen, \
                             (MSrce)[0], srceHt, srceLen, \
                             firstRowInCol, sampInCol, firstColInRow, sampInRow )

#define MUScu_submatrix_equM( MDest, destHt, destLen, \
                           firstRowInCol, sampInCol, firstColInRow, sampInRow, \
                           MSrce, srceHt, srceLen ) \
               MUScusubmatrix_equM(  (MDest)[0], destHt, destLen, \
                             firstRowInCol, sampInCol, firstColInRow, sampInRow, \
                             (MSrce)[0], srceHt, srceLen )

#define MUScu_equMblock( MSub, subHt, subLen, MSrce, srceHt, srceLen, \
                      firstRowInCol, firstColInRow ) \
               MUScuequMblock(  (MSub)[0], subHt, subLen, \
                             (MSrce)[0], srceHt, srceLen, \
                             firstRowInCol, firstColInRow )

#define MUScu_block_equM( MDest, destHt, destLen, \
                       firstRowInCol, firstColInRow, \
                       MSrce, srceHt, srceLen ) \
               MUScublock_equM( (MDest)[0], destHt, destLen, \
                             firstRowInCol, firstColInRow, \
                             (MSrce)[0], srceHt, srceLen )

#define MUScu_equMblockT( MSub, subHt, subLen, MSrce, srceHt, srceLen, \
                      firstRowInCol, firstColInRow ) \
               MUScuequMblockT(  (MSub)[0], subHt, subLen, \
                             (MSrce)[0], srceHt, srceLen, \
                             firstRowInCol, firstColInRow )

#define MUScu_block_equMT( MDest, destHt, destLen, \
                       firstRowInCol, firstColInRow, \
                       MSrce, srceHt, srceLen ) \
               MUScublock_equMT( (MDest)[0], destHt, destLen, \
                             firstRowInCol, firstColInRow, \
                             (MSrce)[0], srceHt, srceLen )

/*****   Extracting a single row or a single column or the diagonal  ******
 *       and storing it into a vector                                     */

#define MUScu_Row_extract( Y, MA, ht, len, iRow ) MUScuRow_extract( Y, (MA)[0], ht, len, iRow )
#define MUScu_Col_extract( Y, MA, ht, len, iCol ) MUScuCol_extract( Y, (MA)[0], ht, len, iCol )
#define MUScu_Dia_extract( Y, MA, len )           MUScuDia_extract( Y, (MA)[0], len )

/**************  Deleting or inserting a row or a column   ***************/

#define MUScu_Row_delete( MB, MA, htA, lenA, iRow )    MUScuRow_delete( (MB)[0], (MA)[0], htA, lenA, iRow )
#define MUScu_Col_delete( MB, MA, htA, lenA, iCol )    MUScuCol_delete( (MB)[0], (MA)[0], htA, lenA, iCol )
#define MUScu_Row_insert( MB, MA, htB, lenB, iRow, X ) MUScuRow_insert( (MB)[0], (MA)[0], htB, lenB, iRow, X )
#define MUScu_Col_insert( MB, MA, htB, lenB, iCol, X ) MUScuCol_insert( (MB)[0], (MA)[0], htB, lenB, iCol, X )


/******  One-dimensional vector operations **********************
         performed along all rows or all columns simultaneously,
         or along the diagonal of a square matrix                */

#define MUScu_Rows_max( Y, MA, ht, len )        MUScuRows_max( Y, (MA)[0], ht, len )
#define MUScu_Cols_max( Y, MA, ht, len )        MUScuCols_max( Y, (MA)[0], ht, len )
#define MUScu_Dia_max(  MA, len )               MUScuDia_max(  (MA)[0], len )
#define MUScu_Rows_min( Y, MA, ht, len )        MUScuRows_min( Y, (MA)[0], ht, len )
#define MUScu_Cols_min( Y, MA, ht, len )        MUScuCols_min( Y, (MA)[0], ht, len )
#define MUScu_Dia_min(  MA, len )               MUScuDia_min(  (MA)[0], len )

#define MUScu_Rows_rotate( MA, ht, len, pos)           MUScuRows_rotate( (MA)[0], ht, len, pos )
#define MUScu_Cols_rotate( MA, ht, len, pos)           MUScuCols_rotate( (MA)[0], ht, len, pos )
#define MUScu_Rows_rotate_buf( MA, ht, len, pos, MBuf) MUScuRows_rotate_buf( (MA)[0], ht, len, pos, (MBuf)[0] )
#define MUScu_Cols_rotate_buf( MA, ht, len, pos, MBuf) MUScuCols_rotate_buf( (MA)[0], ht, len, pos, (MBuf)[0] )
#define MUScu_Rows_reflect( MA, ht, len )              MUScuRows_reflect( (MA)[0], ht, len )
#define MUScu_Cols_reflect( MA, ht, len )              MUScuCols_reflect( (MA)[0], ht, len )
#define MUScu_Rows_rev( MA, ht, len)                   MUScuRows_rev( (MA)[0], ht, len )
#define MUScu_Cols_rev( MA, ht, len)                   MUScuCols_rev( (MA)[0], ht, len )
#define MUScu_Rows_distribution( MAbund, Limits, nBins, MX, ht, len, mode ) MUScuRows_distribution( MAbund[0], Limits, nBins, MX[0], ht, len, mode )
#define MUScu_Cols_distribution( MAbund, Limits, nBins, MX, ht, len, mode ) MUScuCols_distribution( MAbund[0], Limits, nBins, MX[0], ht, len, mode )

/********  Operations involving two rows or two colums of one matrix  *****/

#define MUScu_Rows_exchange( MA, ht, len, row1, row2 ) \
                             MUScuRows_exchange( (MA)[0], ht, len, row1, row2 )
#define MUScu_Cols_exchange( MA, ht, len, col1, col2 ) \
                             MUScuCols_exchange( (MA)[0], ht, len, col1, col2 )

/*************** Transposing and rotating a matrix **********************/

#define MUScu_transpose( MTr, MA, htTr, lenTr )    MUScutranspose( (MTr)[0], (MA)[0], htTr, lenTr )
       /*  dimensions htTr, lenTr are those of the transposed matrix, not of the original!   */
#define MUScu_rotate90( MRot, MA, htRot, lenRot )  MUScurotate90( (MRot)[0], (MA)[0], htRot, lenRot )
#define MUScu_rotate180( MRot, MA, htRot, lenRot ) VUScu_rev( (MRot)[0], (MA)[0], (htRot)*(lenRot) )
#define MUScu_rotate270( MRot, MA, htRot, lenRot ) MUScurotate270( (MRot)[0], (MA)[0], htRot, lenRot )


/*************************************************************************
 * MUScu functions (without underbar in the prefix): 	
    (working on matrices in host memory, input type 
	usPMatrix = usVector = pointer to matrix element[0][0], 
	scalar parameters on host and passed by value)
*
 *************************************************************************/

#define MUScuequ0( MA, ht, len )       VUScu_equ0( MA, (ht)*(len) )
void   __vf OVCUAPI  MUScuequ1( usPMatrix MA, ui len );  /* identity matrix */
void   __vf OVCUAPI  MUScuouterprod( usPMatrix MA, usVector X,  usVector Y, ui ht, ui len );

void   __vf OVCUAPI  MUScuRow_equ0( usPMatrix MA, ui ht, ui len, ui iRow );
void   __vf OVCUAPI  MUScuCol_equ0( usPMatrix MA, ui ht, ui len, ui iCol );
void   __vf OVCUAPI  MUScuDia_equ0( usPMatrix MA, ui len );

void   __vf OVCUAPI  MUScuRow_equC( usPMatrix MA, ui ht, ui len, ui iRow, unsigned short C );
void   __vf OVCUAPI  MUScuCol_equC( usPMatrix MA, ui ht, ui len, ui iCol, unsigned short C );
void   __vf OVCUAPI  MUScuDia_equC( usPMatrix MA, ui len, unsigned short C );

void   __vf OVCUAPI  MUScuRow_equV( usPMatrix MA, ui ht, ui len, ui iRow, usVector X );
void   __vf OVCUAPI  MUScuCol_equV( usPMatrix MA, ui ht, ui len, ui iCol, usVector X );
void   __vf OVCUAPI  MUScuDia_equV( usPMatrix MA, ui len, usVector X );

void   __vf OVCUAPI  MUScuTrd_equM( usPMatrix MA, usPMatrix MTrd, ui len );
void   __vf OVCUAPI  MUScuTrd_extract( usPMatrix MTrd, usPMatrix MA, ui len );

#define MUScuequM( MB, MA, ht, len )      VUScu_equV( MB, MA, (ht)*(len) )
void   __vf OVCUAPI  MUScuUequL( usPMatrix MA, ui len );
void   __vf OVCUAPI  MUScuLequU( usPMatrix MA, ui len );

            /* data-type conversions:  */
#define McuSItoUS( MUS, MSI, ht, len ) Vcu_SItoUS( MUS, MSI, (ht)*(len) )
#define McuUStoSI( MSI, MUS, ht, len ) Vcu_UStoSI( MSI, MUS, (ht)*(len) )
#define McuUStoUB( MUB, MUS, ht, len ) Vcu_UStoUB( MUB, MUS, (ht)*(len) )
#define McuUStoU(  MU,  MUS, ht, len ) Vcu_UStoU(  MU,  MUS, (ht)*(len) )
#define McuUStoUL( MUL, MUS, ht, len ) Vcu_UStoUL( MUL, MUS, (ht)*(len) )
#define McuUBtoUS( MUS, MUB, ht, len ) Vcu_UBtoUS( MUS, MUB, (ht)*(len) )
#define McuUtoUS(  MUS, MU,  ht, len ) Vcu_UtoUS(  MUS, MU,   (ht)*(len) )
#define McuULtoUS( MUS, MUL, ht, len ) Vcu_ULtoUS( MUS, MUL, (ht)*(len) )
#ifdef _WIN64
	#define McuUStoUQ( MUQ, MUS, ht, len ) Vcu_UStoUQ( MUQ, MUS, (ht)*(len) )
	#define McuUQtoUS( MUS, MUQ, ht, len ) Vcu_UQtoUS( MUS, MUQ, (ht)*(len) )
#endif
#define McuUStoF(  MF,  MUS, ht, len ) Vcu_UStoF(  MF, MUS, (ht)*(len) )
#define McuUStoD(  MD,  MUS, ht, len ) Vcu_UStoD(  MD, MUS, (ht)*(len) )

/********  Extracting a submatrix and copying a submatrix back  *********/

void  __vf OVCUAPI  MUScusubmatrix( usPMatrix MSub, ui subHt,  ui subLen,
                          usPMatrix MSrce, ui srceHt,  ui srceLen,
                          ui firstRowInCol,  ui sampInCol,
                          ui firstColInRow,  ui sampInRow );

void  __vf OVCUAPI  MUScusubmatrix_equM( usPMatrix MDest, ui destHt, ui destLen,
                               ui firstRowInCol,  ui sampInCol,
                               ui firstColInRow,  ui sampInRow,
                               usPMatrix MSrce, ui srceHt, ui srceLen );

void  __vf OVCUAPI  MUScuequMblock(  usPMatrix MSub, ui subHt, ui subLen,
                          usPMatrix MSrce, ui srceHt,  ui srceLen,
                          ui firstRowInCol,  ui firstColInRow );

void  __vf OVCUAPI  MUScublock_equM( usPMatrix MDest, ui destHt, ui destLen,
                          ui firstRowInCol,  ui firstColInRow,
                          usPMatrix MSrce, ui srceHt, ui srceLen );

void  __vf OVCUAPI  MUScuequMblockT( usPMatrix MSub, ui subHt, ui subLen,
                          usPMatrix MSrce, ui srceHt, ui srceLen,
                          ui firstRowInCol,  ui firstColInRow );

void  __vf OVCUAPI  MUScublock_equMT( usPMatrix MDest, ui destHt, ui destLen,
                          ui firstRowInCol,  ui firstColInRow,
                          usPMatrix MSrce, ui srceHt, ui srceLen );


/*****   Extracting a single row or a single column or the diagonal  *****
 *       and storing it into a vector                                    */

void __vf OVCUAPI  MUScuRow_extract( usVector Y, usPMatrix MA, ui ht, ui len, ui iRow );
void __vf OVCUAPI  MUScuCol_extract( usVector Y, usPMatrix MA, ui ht, ui len, ui iCol );
void __vf OVCUAPI  MUScuDia_extract( usVector Y, usPMatrix MA, ui len );

/**********  Deleting or inserting a row or a column *****************/

void __vf OVCUAPI  MUScuRow_delete( usPMatrix MB, usPMatrix MA, ui htA, ui lenA, ui iRow );
void __vf OVCUAPI  MUScuCol_delete( usPMatrix MB, usPMatrix MA, ui htA, ui lenA, ui iCol );
void __vf OVCUAPI  MUScuRow_insert( usPMatrix MB, usPMatrix MA, ui htB, ui lenB, ui iRow, usVector X );
void __vf OVCUAPI  MUScuCol_insert( usPMatrix MB, usPMatrix MA, ui htB, ui lenB, ui iCol, usVector X );


/******  One-dimensional vector operations **********************
         performed along all rows or all columns simultaneously,
         or along the diagonal of a square matrix                */

void   __vf OVCUAPI  MUScuRows_max( usVector Y, usPMatrix MA, ui ht, ui len );
void   __vf OVCUAPI  MUScuCols_max( usVector Y, usPMatrix MA, ui ht, ui len );
unsigned short  __vf OVCUAPI  MUScuDia_max(  usPMatrix MA, ui len );
void   __vf OVCUAPI  MUScuRows_min( usVector Y, usPMatrix MA, ui ht, ui len );
void   __vf OVCUAPI  MUScuCols_min( usVector Y, usPMatrix MA, ui ht, ui len );
unsigned short  __vf OVCUAPI  MUScuDia_min(  usPMatrix MA, ui len );

void  __vf OVCUAPI  MUScuRows_rotate( usPMatrix MA, ui ht, ui len, ssize_t pos );
void  __vf OVCUAPI  MUScuCols_rotate( usPMatrix MA, ui ht, ui len, ssize_t pos );
void  __vf OVCUAPI  MUScuRows_rotate_buf( usPMatrix MA, ui ht, ui len, ssize_t pos, usPMatrix MBuf );
void  __vf OVCUAPI  MUScuCols_rotate_buf( usPMatrix MA, ui ht, ui len, ssize_t pos, usPMatrix MBuf );
void  __vf OVCUAPI  MUScuRows_reflect( usPMatrix MA, ui ht, ui len );
void  __vf OVCUAPI  MUScuCols_reflect( usPMatrix MA, ui ht, ui len );
void  __vf OVCUAPI  MUScuRows_rev( usPMatrix MA, ui ht, ui len );
void  __vf OVCUAPI  MUScuCols_rev( usPMatrix MA, ui ht, ui len );
void  __vf OVCUAPI  MUScuRows_distribution( uiPMatrix MAbund, usVector Limits, ui nBins, usPMatrix MX, ui ht, ui len, int mode );
void  __vf OVCUAPI  MUScuCols_distribution( uiPMatrix MAbund, usVector Limits, ui nBins, usPMatrix MX, ui ht, ui len, int mode );

/********  Operations involving two rows or two colums of one matrix  *****/

void   __vf OVCUAPI  MUScuRows_exchange( usPMatrix MA, ui ht, ui len, ui i1, ui i2 );
void   __vf OVCUAPI  MUScuCols_exchange( usPMatrix MA, ui ht, ui len, ui i1, ui i2 );


/***************  Transposing and rotating a matrix **********************/

void  __vf OVCUAPI  MUScutranspose( usPMatrix MTr, usPMatrix MA,  ui htTr, ui lenTr );
void  __vf OVCUAPI  MUScurotate90(  usPMatrix MRot, usPMatrix MA, ui htRot, ui lenRot );
#define     MUScurotate180( MRot, MA, htRot, lenRot )  VUScu_rev( MRot, MA, (htRot)*(lenRot) )
void  __vf OVCUAPI  MUScurotate270( usPMatrix MRot, usPMatrix MA, ui htRot, ui lenRot );



#ifdef __cplusplus
} // end of extern "C"
#endif
#endif  /*  __MUSSTD_H  */
