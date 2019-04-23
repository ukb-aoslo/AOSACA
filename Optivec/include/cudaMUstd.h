/*  cudaMUstd.h

  matrix management functions:
  manipulations on matrices of data type "unsigned" 
  (generic unsigned integers)

  This file declares the functions with the name variants 
	cudaMU_func	(working on matrices in device memory, input type uMatrix, scalar parameters reside on host and are passed by value)
	cusdMU_func	(as cudaMU_func except scalar parameters reside on device and are passed by address)
	cudaMUfunc		(as cudaMU_func, but input type uPMatrix = uVector = pointer to matrix element[0][0])
	cusdMUfunc		(as cusdMU_func, but input type uPMatrix = uVector = pointer to matrix element[0][0])
	MUcu_func		(working on matrices in host memory, input type uMatrix, scalar parameters on host and passed by value)
	MUcufunc		(as MUcu_func, but input type uPMatrix = uVector = pointer to matrix element[0][0])
  where func is the respective function.

   Copyright (c) 1996-2017 by OptiCode - Dr. Martin Sander Software Dev.
  All Rights Reserved.

*/

#if !defined( __CUDAMUSTD_H )
#define __CUDAMUSTD_H
#if !defined( __CUDAMATLIB_H )
#include <cudaMatLib.h>
#endif
#if !defined( __CUDAVUSTD_H )
#include <cudaVUstd.h>
#endif
#if !defined( __CUDAVUMATH_H )
#include <cudaVUmath.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif

/**** Generation of matrices on device memory and on pinned host memory *******************/

uMatrix  __vf cudaMU_matrix( ui ht, ui len );   /* allocates a vector on device memory */
uMatrix  __vf cudaMU_matrix0( ui ht, ui len );
 /* The following functions allocate device-accessible, "pinned" memory on the host.
	This memory is mapped onto the device memory space. The resulting device address is returned.
	The matrix can be accessed either by its host address "hostPtr" e.g., MU_equ1( hostPtr, ht, len );
	or by its device address , e.g., cudaMU_equ1( devicePtr, ht, len );                             */
uMatrix  __vf cudaMU_pinnedMatrix(  uMatrix *hostPtr, ui ht, ui len ); 
uMatrix  __vf cudaMU_pinnedMatrix0( uMatrix *hostPtr, ui ht, ui len );

/*************************************************************************
 * Declarations of the functions written without underbar in the prefix: *
 *	cudaMUfunc  (input type 
                   uPMatrix = uVector = pointer to matrix element[0][0])
 *	cusdMUfunc  (input type 
                   uPMatrix = uVector = pointer to matrix element[0][0])
 *************************************************************************/


void  __vcuf OVCUAPI  cudaMUsetElement( uPMatrix X, ui ht, ui len, ui m, ui n, unsigned C );
void  __vcuf OVCUAPI  cusdMUsetElement( uPMatrix X, ui ht, ui len, ui m, ui n, unsigned *d_C );
void  __vcuf OVCUAPI  cudaMUgetElement( unsigned *h_y, uPMatrix X, ui ht, ui len, ui m, ui n );
void  __vcuf OVCUAPI  cusdMUgetElement( unsigned *d_y, uPMatrix X, ui ht, ui len, ui m, ui n );
unsigned * __vcuf OVCUAPI  cudaMUPelement( uPMatrix X, ui ht, ui len, ui m, ui n );
unsigned   __vcuf OVCUAPI  cudaMUelement(  uPMatrix X, ui ht, ui len, ui m, ui n );

#define cudaMUequ0( MA, ht, len )            cudaVU_equ0( MA, (ht)*(len) )
overror_t   __vcuf OVCUAPI  cudaMUequ1( uPMatrix MA, ui len );  /* identity matrix */
overror_t   __vcuf OVCUAPI  cudaMUouterprod( uPMatrix MA, uVector X,  uVector Y, ui ht, ui len );

overror_t   __vcuf OVCUAPI  cudaMURow_equ0( uPMatrix MA, ui ht, ui len, ui iRow );
overror_t   __vcuf OVCUAPI  cudaMUCol_equ0( uPMatrix MA, ui ht, ui len, ui iCol );
overror_t   __vcuf OVCUAPI  cudaMUDia_equ0( uPMatrix MA, ui len );

overror_t   __vcuf OVCUAPI  cudaMURow_equC( uPMatrix MA, ui ht, ui len, ui iRow, unsigned C );
overror_t   __vcuf OVCUAPI  cudaMUCol_equC( uPMatrix MA, ui ht, ui len, ui iCol, unsigned C );
overror_t   __vcuf OVCUAPI  cudaMUDia_equC( uPMatrix MA, ui len, unsigned C );
overror_t   __vcuf OVCUAPI  cusdMURow_equC( uPMatrix MA, ui ht, ui len, ui iRow, unsigned *d_C );
overror_t   __vcuf OVCUAPI  cusdMUCol_equC( uPMatrix MA, ui ht, ui len, ui iCol, unsigned *d_C );
overror_t   __vcuf OVCUAPI  cusdMUDia_equC( uPMatrix MA, ui len, unsigned *d_C );

overror_t   __vcuf OVCUAPI  cudaMURow_equV( uPMatrix MA, ui ht, ui len, ui iRow, uVector X );
overror_t   __vcuf OVCUAPI  cudaMUCol_equV( uPMatrix MA, ui ht, ui len, ui iCol, uVector X );
overror_t   __vcuf OVCUAPI  cudaMUDia_equV( uPMatrix MA, ui len, uVector X );

overror_t   __vcuf OVCUAPI  cudaMUTrd_equM( uPMatrix MA, uPMatrix MTrd, ui len );
overror_t   __vcuf OVCUAPI  cudaMUTrd_extract( uPMatrix MTrd, uPMatrix MA, ui len );

#define cudaMUequM( MB, MA, ht, len )  cudaVU_equV( MB, MA, (ht)*(len) )
#define cudaMUequMhost( MB, MA, ht, len )  cudaVU_equVhost( MB, MA, (ht)*(len) )
#define MUequMdevice( MB, MA, ht, len )    VU_equVdevice( MB, MA, (ht)*(len) )
overror_t   __vcuf OVCUAPI  cudaMUUequL( uPMatrix MA, ui len );
overror_t   __vcuf OVCUAPI  cudaMULequU( uPMatrix MA, ui len );

            /* data-type conversions:  */
#define cudaMItoU( MU, MI, ht, len ) cudaV_ItoU( (MU), (MI), (ht)*(len) )
#define cudaMUtoI( MI, MU, ht, len ) cudaV_UtoI( (MI), (MU), (ht)*(len) )
#define cudaMUtoUB( MUB, MU, ht, len ) cudaV_UtoUB( (MUB), (MU), (ht)*(len) )
#define cudaMUtoUS( MUS, MU, ht, len ) cudaV_UtoUS( (MUS), (MU), (ht)*(len) )
#define cudaMUtoUL( MUL, MU, ht, len ) cudaV_UtoUL( (MUL), (MU), (ht)*(len) )
#define cudaMUBtoU( MU, MUB, ht, len ) cudaV_UBtoU( (MU), (MUB), (ht)*(len) )
#define cudaMUStoU( MU, MUS, ht, len ) cudaV_UStoU( (MU), (MUS), (ht)*(len) )
#define cudaMULtoU( MU, MUL, ht, len ) cudaV_ULtoU( (MU), (MUL), (ht)*(len) )
#ifdef _WIN64
	#define cudaMUtoUQ( MUQ, MU, ht, len ) cudaV_UtoUQ( (MUQ), (MU), (ht)*(len) )
	#define cudaMUQtoU( MU, MUQ, ht, len ) cudaV_UQtoU( (MU), (MUQ), (ht)*(len) )
#endif
#define cudaMUtoF(  MF,  MU, ht, len ) cudaV_UtoF(  (MF),  (MU), (ht)*(len) )
#define cudaMUtoD(  MD,  MU, ht, len ) cudaV_UtoD(  (MD),  (MU), (ht)*(len) )

/********  Extracting a submatrix and copying a submatrix back  *********/

overror_t  __vcuf OVCUAPI  cudaMUsubmatrix( uPMatrix MSub,  ui subHt,  ui subLen,
                          uPMatrix MSrce, ui srceHt,  ui srceLen,
                          ui firstRowInCol,  ui sampInCol,
                          ui firstColInRow,  ui sampInRow );

overror_t  __vcuf OVCUAPI  cudaMUsubmatrix_equM( uPMatrix MDest, ui destHt, ui destLen,
                               ui firstRowInCol,  ui sampInCol,
                               ui firstColInRow,  ui sampInRow,
                               uPMatrix MSrce, ui srceHt, ui srceLen );

overror_t  __vcuf OVCUAPI  cudaMUequMblock(  uPMatrix MSub, ui subHt, ui subLen,
                          uPMatrix MSrce, ui srceHt,  ui srceLen,
                          ui firstRowInCol,  ui firstColInRow );

overror_t  __vcuf OVCUAPI  cudaMUblock_equM( uPMatrix MDest, ui destHt, ui destLen,
                          ui firstRowInCol,  ui firstColInRow,
                          uPMatrix MSrce,  ui srceHt, ui srceLen );

overror_t  __vcuf OVCUAPI  cudaMUequMblockT( uPMatrix MSub, ui subHt, ui subLen,
                          uPMatrix MSrce, ui srceHt, ui srceLen,
                          ui firstRowInCol,  ui firstColInRow );

overror_t  __vcuf OVCUAPI  cudaMUblock_equMT( uPMatrix MDest, ui destHt, ui destLen,
                          ui firstRowInCol,  ui firstColInRow,
                          uPMatrix MSrce, ui srceHt, ui srceLen );


/*****   Extracting a single row or a single column or the diagonal  *****
 *       and storing it into a vector                                    */

overror_t __vcuf OVCUAPI  cudaMURow_extract( uVector Y, uPMatrix MA, ui ht, ui len, ui iRow );
overror_t __vcuf OVCUAPI  cudaMUCol_extract( uVector Y, uPMatrix MA, ui ht, ui len, ui iCol );
overror_t __vcuf OVCUAPI  cudaMUDia_extract( uVector Y, uPMatrix MA, ui len );


/**********  Deleting or inserting a row or a column *****************/

overror_t __vcuf OVCUAPI  cudaMURow_delete( uPMatrix MB, uPMatrix MA, ui htA, ui lenA, ui iRow );
overror_t __vcuf OVCUAPI  cudaMUCol_delete( uPMatrix MB, uPMatrix MA, ui htA, ui lenA, ui iCol );
overror_t __vcuf OVCUAPI  cudaMURow_insert( uPMatrix MB, uPMatrix MA, ui htB, ui lenB, ui iRow, uVector X );
overror_t __vcuf OVCUAPI  cudaMUCol_insert( uPMatrix MB, uPMatrix MA, ui htB, ui lenB, ui iCol, uVector X );


/******  One-dimensional vector operations **********************
         performed along all rows or all columns simultaneously,
         or along the diagonal of a square matrix                */

overror_t  __vcuf OVCUAPI  cudaMURows_max( uVector Y, uPMatrix MA, ui ht, ui len );
overror_t  __vcuf OVCUAPI  cudaMUCols_max( uVector Y, uPMatrix MA, ui ht, ui len );
overror_t  __vcuf OVCUAPI  cudaMUDia_max(  unsigned *h_RetVal, uPMatrix MA, ui len );
overror_t  __vcuf OVCUAPI  cusdMUDia_max(  unsigned *d_RetVal, uPMatrix MA, ui len );
overror_t  __vcuf OVCUAPI  cudaMURows_min( uVector Y, uPMatrix MA, ui ht, ui len );
overror_t  __vcuf OVCUAPI  cudaMUCols_min( uVector Y, uPMatrix MA, ui ht, ui len );
overror_t  __vcuf OVCUAPI  cudaMUDia_min(  unsigned *h_RetVal, uPMatrix MA, ui len );
overror_t  __vcuf OVCUAPI  cusdMUDia_min(  unsigned *d_RetVal, uPMatrix MA, ui len );

overror_t  __vcuf OVCUAPI  cudaMURows_rotate( uPMatrix MA, ui ht, ui len, ssize_t pos );
overror_t  __vcuf OVCUAPI  cudaMUCols_rotate( uPMatrix MA, ui ht, ui len, ssize_t pos );
overror_t  __vcuf OVCUAPI  cudaMURows_rotate_buf( uPMatrix MA, ui ht, ui len, ssize_t pos, uPMatrix MBuf );
overror_t  __vcuf OVCUAPI  cudaMUCols_rotate_buf( uPMatrix MA, ui ht, ui len, ssize_t pos, uPMatrix MBuf );
overror_t  __vcuf OVCUAPI  cudaMURows_reflect( uPMatrix MA, ui ht, ui len );
overror_t  __vcuf OVCUAPI  cudaMUCols_reflect( uPMatrix MA, ui ht, ui len );
overror_t  __vcuf OVCUAPI  cudaMURows_rev( uPMatrix MA, ui ht, ui len );
overror_t  __vcuf OVCUAPI  cudaMUCols_rev( uPMatrix MA, ui ht, ui len );
overror_t  __vcuf OVCUAPI  cudaMURows_distribution( uiPMatrix MAbund, uVector Limits, ui nBins, uPMatrix MX, ui ht, ui len, int mode );
overror_t  __vcuf OVCUAPI  cudaMUCols_distribution( uiPMatrix MAbund, uVector Limits, ui nBins, uPMatrix MX, ui ht, ui len, int mode );

/********  Operations involving two rows or two colums of one matrix  *****/

overror_t   __vcuf OVCUAPI  cudaMURows_exchange( uPMatrix MA, ui ht, ui len, ui i1, ui i2 );
overror_t   __vcuf OVCUAPI  cudaMUCols_exchange( uPMatrix MA, ui ht, ui len, ui i1, ui i2 );

/****************  Transposing and rotating a matrix **********************/

overror_t  __vcuf OVCUAPI  cudaMUtranspose( uPMatrix MTr, uPMatrix MA, ui htTr, ui lenTr );
overror_t  __vcuf OVCUAPI  cudaMUrotate90(  uPMatrix MRot, uPMatrix MA, ui htRot, ui lenRot );
#define       cudaMUrotate180( MRot, MA, htRot, lenRot ) cudaVU_rev( MRot, MA, (htRot)*(lenRot) )
overror_t  __vcuf OVCUAPI  cudaMUrotate270( uPMatrix MRot, uPMatrix MA, ui htRot, ui lenRot );
overror_t  __vcuf OVCUAPI  cudaMUtranspose_buf( uPMatrix MTr, uPMatrix MA, ui htTr, ui lenTr, uPMatrix MBuf );

/**************************  Input and Output  **************************
	The input/output functions involve memory transfers from device
	to host memory or vice versa. The generic cudaMF_input/output functions
	allocate their own host buffers, whereas the cudaMF_xxx_buf functions
	take a user-supplied buffer vector h_Wk (size must be >= ht*len )
	and are much more efficient.                                       */

#define cudaMUprint( MA, ht, len )  cudaMUfprint( stdout, MA, ht, len, 80 )
overror_t __vf cudaMUfprint( FILE *stream, uPMatrix MA, ui ht, ui len, unsigned linewidth );
overror_t __vf cudaMUcprint( uPMatrix MA, ui ht, ui len );
#define cudaMUprint_buf( MA, ht, len, h_Wk )  cudaMUfprint_buf( stdout, MA, ht, len, 80, h_Wk )
overror_t __vf cudaMUfprint_buf( FILE *stream, uPMatrix MA, ui ht, ui len, unsigned linewidth, uVector h_Wk );
overror_t __vf cudaMUcprint_buf( uPMatrix MA, ui ht, ui len, uVector h_Wk );
overror_t __vf cudaMUwrite( FILE *stream, uPMatrix X, ui ht, ui len  );
overror_t __vf cudaMUread( uPMatrix X, ui ht, ui len, FILE *stream );
overror_t __vf cudaMUwrite_buf( FILE *stream, uPMatrix X, ui ht, ui len, uVector h_Wk );
overror_t __vf cudaMUread_buf( uPMatrix X, ui ht, ui len, FILE *stream, uVector h_Wk );
#define cudaMUstore( str, MA, ht, len ) cudaVU_store( str, MA, (len)*(ht) )
#define cudaMUrecall( MA, ht, len, str) cudaVU_recall( MA, (len)*(ht), str)
#define cudaMUstore_buf( str, MA, ht, len, h_Wk ) cudaVU_store( str, MA, (len)*(ht), h_Wk )
#define cudaMUrecall_buf( MA, ht, len, str, h_Wk) cudaVU_recall( MA, (len)*(ht), str, h_Wk)




/***************************************************************************
    cudaMU_func	(working on matrices in device memory, input type iMatrix, 
	             scalar parameters reside on host and are passed by value)
    cusdMU_func	(as cudaMU_func except scalar parameters reside on device 
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

inline void    cudaMU_setElement( uMatrix MA, ui ht, ui len, ui m, ui n, unsigned C )
	{	cudaMUsetElement( (uPMatrix)(MA), ht, len, m, n, C );}
inline void    cusdMU_setElement( uMatrix MA, ui ht, ui len, ui m, ui n, unsigned *d_C )
	{	cusdMUsetElement( (uPMatrix)(MA), ht, len, m, n, d_C );}
inline void    cudaMU_getElement( unsigned *y, uMatrix MA, ui ht, ui len, ui m, ui n )
	{	cudaMUgetElement( y, (uPMatrix)(MA), ht, len, m, n );}
inline void    cusdMU_getElement( unsigned *d_y, uMatrix MA, ui ht, ui len, ui m, ui n )
	{	cusdMUgetElement( d_y, (uPMatrix)(MA), ht, len, m, n );}
inline unsigned * cudaMU_Pelement( uMatrix MA, ui ht, ui len, ui m, ui n )
	{	return cudaMUPelement( (uPMatrix)(MA), ht, len, m, n );}
inline unsigned   cudaMU_element( uMatrix MA, ui ht, ui len, ui m, ui n )
{	return cudaMUelement( (uPMatrix)(MA), ht, len, m, n );}

inline overror_t  cudaMU_equ0( uMatrix MA, ui ht, ui len )
	{	return cudaVU_equ0( (uPMatrix)MA, (ht)*(len) ); }
inline overror_t  cudaMU_equ1( uMatrix MA, ui len )
	{	return cudaMUequ1( (uPMatrix)(MA), len );} /* identity matrix */

inline overror_t  cudaMU_randomLC( uMatrix MA, ui ht, ui len, long seed, unsigned MinVal, unsigned MaxVal, V_RANDOMLCSTATE *h_state )
	{	return cudaVU_randomLC( (uPMatrix)(MA), (ht)*(len), seed, MinVal, MaxVal, h_state );}
inline overror_t  cudaMU_random( uMatrix MA, ui ht, ui len, long seed, unsigned MinVal, unsigned MaxVal )
	{	return cudaVU_random( (uPMatrix)(MA), (ht)*(len), seed, MinVal, MaxVal );}
inline overror_t  cusdMU_randomLC( uMatrix MA, ui ht, ui len, long seed, unsigned *d_MinVal, unsigned *d_MaxVal, V_RANDOMLCSTATE *h_state )
	{	return cusdVU_randomLC( (uPMatrix)(MA), (ht)*(len), seed, d_MinVal, d_MaxVal, h_state );}
inline overror_t  cusdMU_random( uMatrix MA, ui ht, ui len, long seed, unsigned *d_MinVal, unsigned *d_MaxVal )
	{	return cusdVU_random( (uPMatrix)(MA), (ht)*(len), seed, d_MinVal, d_MaxVal );}
inline overror_t  cudaMU_outerprod( uMatrix MA, uVector X,  uVector Y, ui ht, ui len )
{	return cudaMUouterprod( (uPMatrix)(MA), X, Y, ht, len );}

inline overror_t  cudaMU_Row_equ0( uMatrix MA, ui ht, ui len, ui iRow )
	{	return cudaMURow_equ0( (uPMatrix)MA, ht, len, iRow );}
inline overror_t  cudaMU_Col_equ0( uMatrix MA, ui ht, ui len, ui iRow )
	{	return cudaMUCol_equ0( (uPMatrix)MA, ht, len, iRow );}
inline overror_t  cudaMU_Dia_equ0( uMatrix MA, ui len )
	{	return cudaMUDia_equ0( (uPMatrix)(MA), len );}

inline overror_t  cudaMU_Row_equC( uMatrix MA, ui ht, ui len, ui iRow, unsigned C )
	{	return cudaMURow_equC( (uPMatrix)MA, ht, len, iRow, C );}
inline overror_t  cudaMU_Col_equC( uMatrix MA, ui ht, ui len, ui iRow, unsigned C )
	{	return cudaMUCol_equC( (uPMatrix)MA, ht, len, iRow, C );}
inline overror_t  cudaMU_Dia_equC( uMatrix MA, ui len, unsigned C )
	{	return cudaMUDia_equC( (uPMatrix)(MA), len, C );}

inline overror_t  cusdMU_Row_equC( uMatrix MA, ui ht, ui len, ui iRow, unsigned *d_C )
	{	return cusdMURow_equC( (uPMatrix)MA, ht, len, iRow, d_C );}
inline overror_t  cusdMU_Col_equC( uMatrix MA, ui ht, ui len, ui iRow, unsigned *d_C )
	{	return cusdMUCol_equC( (uPMatrix)MA, ht, len, iRow, d_C );}
inline overror_t  cusdMU_Dia_equC( uMatrix MA, ui len, unsigned *d_C )
	{	return cusdMUDia_equC( (uPMatrix)(MA), len, d_C );}

inline overror_t  cudaMU_Row_equV( uMatrix MA, ui ht, ui len, ui iRow, uVector X )
	{	return cudaMURow_equV( (uPMatrix)MA, ht, len, iRow, X );}
inline overror_t  cudaMU_Col_equV( uMatrix MA, ui ht, ui len, ui iRow, uVector X )
	{	return cudaMUCol_equV( (uPMatrix)MA, ht, len, iRow, X );}
inline overror_t  cudaMU_Dia_equV( uMatrix MA, ui len, uVector X )
	{	return cudaMUDia_equV( (uPMatrix)(MA), len, X );}

inline overror_t  cudaMU_Trd_equM( uMatrix MA, uMatrix MTrd, ui len )
	{	return cudaMUTrd_equM( (uPMatrix)(MA), (uPMatrix)(MTrd), len );}
inline overror_t  cudaMU_Trd_extract( uMatrix MTrd, uMatrix MA, ui len )
	{	return cudaMUTrd_extract( (uPMatrix)(MTrd), (uPMatrix)(MA), len );}

inline overror_t cudaMU_equM( uMatrix MB, uMatrix MA, ui ht, ui len )
	{	return cudaVU_equV( (uPMatrix)MB, (uPMatrix)MA, (ht)*(len) );}
inline overror_t cudaMU_equMhost( uMatrix d_MB, uMatrix h_MA, ui ht, ui len )
	{	return cudaVU_equVhost( (uPMatrix)d_MB, (h_MA)[0], (ht)*(len) );}
inline overror_t MU_equMdevice( uMatrix h_MB, uMatrix d_MA, ui ht, ui len )
	{	return VU_equVdevice( h_MB[0], (uPMatrix)d_MA, (ht)*(len) );}
inline overror_t  cudaMU_UequL( uMatrix MA, ui len )
	{	return cudaMUUequL( (uPMatrix)(MA), len );}
inline overror_t  cudaMU_LequU( uMatrix MA, ui len )
	{	return cudaMULequU( (uPMatrix)(MA), len );}

/************** Data-type interconversions  ****************************/

inline overror_t cudaM_ItoU( uMatrix MU, iMatrix MI, ui ht, ui len )
	{	return cudaV_ItoU( (uVector)MU, (iVector)MI, (ht)*(len) );}
inline overror_t cudaM_UBtoU( uMatrix MU, ubMatrix MUB, ui ht, ui len )
	{	return cudaV_UBtoU( (uVector)MU, (ubVector)MUB, (ht)*(len) );}
inline overror_t cudaM_UStoU(  uMatrix MU, usMatrix MUS,  ui ht, ui len )
	{	return cudaV_UStoU(  (uVector)MU, (usVector)MUS,   (ht)*(len) );}
inline overror_t cudaM_ULtoU( uMatrix MU, ulMatrix MUL, ui ht, ui len )
	{	return cudaV_ULtoU( (uVector)MU, (ulVector)MUL, (ht)*(len) );}
#ifdef _WIN64
	inline overror_t cudaM_UQtoU( uMatrix MU, uqMatrix MUQ, ui ht, ui len )
		{	return cudaV_UQtoU( (uVector)MU, (uqVector)MUQ, (ht)*(len) );}
#endif
inline overror_t cudaM_UtoF(  fMatrix MF,  uMatrix MU, ui ht, ui len )
	{	return cudaV_UtoF(  (fVector)MF,   (uVector)MU, (ht)*(len) );}
inline overror_t cudaM_UtoD(  dMatrix MD,  uMatrix MU, ui ht, ui len )
	{	return cudaV_UtoD(  (dVector)MD,   (uVector)MU, (ht)*(len) );}

/********  Extracting a submatrix and copying a submatrix back  *********/

inline overror_t cudaMU_submatrix( uMatrix MSub, ui subHt, ui subLen, uMatrix MSrce, ui srceHt, ui srceLen,
                      ui firstRowInCol, ui sampInCol, ui firstColInRow, ui sampInRow )
	{	return cudaMUsubmatrix(  (uPMatrix)(MSub), subHt, subLen,
		                         (uPMatrix)(MSrce), srceHt, srceLen,
								 firstRowInCol, sampInCol, firstColInRow, sampInRow ); }

inline overror_t cudaMU_submatrix_equM( uMatrix MDest, ui destHt, ui destLen,
                           ui firstRowInCol, ui sampInCol, ui firstColInRow, ui sampInRow,
                           uMatrix MSrce, ui srceHt, ui srceLen )
	{	return cudaMUsubmatrix_equM(  (uPMatrix)(MDest), destHt, destLen,
                             firstRowInCol, sampInCol, firstColInRow, sampInRow,
							 (uPMatrix)(MSrce), srceHt, srceLen );}

inline overror_t cudaMU_equMblock( uMatrix MSub, ui subHt, ui subLen, uMatrix MSrce, ui srceHt, ui srceLen,
                      ui firstRowInCol, ui firstColInRow )
{	return cudaMUequMblock(  (uPMatrix)(MSub), subHt, subLen,
						   (uPMatrix)(MSrce), srceHt, srceLen, firstRowInCol, firstColInRow );}

inline overror_t cudaMU_block_equM( uMatrix MDest, ui destHt, ui destLen,
                       ui firstRowInCol, ui firstColInRow,
                       uMatrix MSrce, ui srceHt, ui srceLen )
	{	return cudaMUblock_equM( (uPMatrix)(MDest), destHt, destLen,
                             firstRowInCol, firstColInRow,
							 (uPMatrix)(MSrce), srceHt, srceLen );}

inline overror_t cudaMU_equMblockT( uMatrix MSub, ui subHt, ui subLen, uMatrix MSrce, ui srceHt, ui srceLen,
                      ui firstRowInCol, ui firstColInRow )
	{	return cudaMUequMblockT(  (uPMatrix)(MSub), subHt, subLen,
                             (uPMatrix)(MSrce), srceHt, srceLen,
							 firstRowInCol, firstColInRow );}

inline overror_t cudaMU_block_equMT( uMatrix MDest, ui destHt, ui destLen,
                       ui firstRowInCol, ui firstColInRow,
                       uMatrix MSrce, ui srceHt, ui srceLen )
	{	return cudaMUblock_equMT( (uPMatrix)(MDest), destHt, destLen,
                             firstRowInCol, firstColInRow,
							 (uPMatrix)(MSrce), srceHt, srceLen );}

/*****   Extracting a single row or a single column or the diagonal  ******
 *       and storing it into a vector                                     */

inline overror_t cudaMU_Row_extract( uVector Y, uMatrix MA, ui ht, ui len, ui iRow ) 
	{	return cudaMURow_extract( Y, (uPMatrix)(MA), ht, len, iRow );}
inline overror_t cudaMU_Col_extract( uVector Y, uMatrix MA, ui ht, ui len, ui iCol ) 
	{	return cudaMUCol_extract( Y, (uPMatrix)(MA), ht, len, iCol );}
inline overror_t cudaMU_Dia_extract( uVector Y, uMatrix MA, ui len )
	{	return cudaMUDia_extract( Y, (uPMatrix)(MA), len );}

/**************  Deleting or inserting a row or a column   ***************/

inline overror_t cudaMU_Row_delete( uMatrix MB, uMatrix MA, ui htA, ui lenA, ui iRow )
	{	return cudaMURow_delete( (uPMatrix)(MB), (uPMatrix)(MA), htA, lenA, iRow );}
inline overror_t cudaMU_Col_delete( uMatrix MB, uMatrix MA, ui htA, ui lenA, ui iCol )
	{	return cudaMUCol_delete( (uPMatrix)(MB), (uPMatrix)(MA), htA, lenA, iCol );}
inline overror_t cudaMU_Row_insert( uMatrix MB, uMatrix MA, ui htB, ui lenB, ui iRow, uVector X )
	{	return cudaMURow_insert( (uPMatrix)(MB), (uPMatrix)(MA), htB, lenB, iRow, X );}
inline overror_t cudaMU_Col_insert( uMatrix MB, uMatrix MA, ui htB, ui lenB, ui iCol, uVector X )
	{	return cudaMUCol_insert( (uPMatrix)(MB), (uPMatrix)(MA), htB, lenB, iCol, X );}


/******  One-dimensional vector operations **********************
         performed along all rows or all columns simultaneously,
         or along the diagonal of a square matrix                */

inline overror_t cudaMU_Rows_max( uVector Y, uMatrix MA, ui ht, ui len )
	{	return cudaMURows_max( Y, (uPMatrix)(MA), ht, len );}
inline overror_t cudaMU_Cols_max( uVector Y, uMatrix MA, ui ht, ui len )
	{	return cudaMUCols_max( Y, (uPMatrix)(MA), ht, len );}
inline overror_t cudaMU_Dia_max(  unsigned *h_RetValPtr, uMatrix MA, ui len )
	{	return cudaMUDia_max(  h_RetValPtr, (uPMatrix)(MA), len );}
inline overror_t cusdMU_Dia_max(  unsigned *d_RetValPtr, uMatrix MA, ui len )
	{	return cusdMUDia_max(  d_RetValPtr, (uPMatrix)(MA), len );}
inline overror_t cudaMU_Rows_min( uVector Y, uMatrix MA, ui ht, ui len )
	{	return cudaMURows_min( Y, (uPMatrix)(MA), ht, len );}
inline overror_t cudaMU_Cols_min( uVector Y, uMatrix MA, ui ht, ui len )
	{	return cudaMUCols_min( Y, (uPMatrix)(MA), ht, len );}
inline overror_t cudaMU_Dia_min(  unsigned *h_RetValPtr, uMatrix MA, ui len )
	{	return cudaMUDia_min(  h_RetValPtr, (uPMatrix)(MA), len );}
inline overror_t cusdMU_Dia_min(  unsigned *d_RetValPtr, uMatrix MA, ui len )
	{	return cusdMUDia_min(  d_RetValPtr, (uPMatrix)(MA), len );}

inline overror_t cudaMU_Rows_rotate( uMatrix MA, ui ht, ui len, ssize_t pos)
	{	return cudaMURows_rotate( (uPMatrix)(MA), ht, len, pos );}
inline overror_t cudaMU_Cols_rotate( uMatrix MA, ui ht, ui len, ssize_t pos)
	{	return cudaMUCols_rotate( (uPMatrix)(MA), ht, len, pos );}
inline overror_t cudaMU_Rows_rotate_buf( uMatrix MA, ui ht, ui len, ssize_t pos, uMatrix MBuf) 
	{	return cudaMURows_rotate_buf( (uPMatrix)(MA), ht, len, pos, (uPMatrix)(MBuf) );}
inline overror_t cudaMU_Cols_rotate_buf( uMatrix MA, ui ht, ui len, ssize_t pos, uMatrix MBuf) 
	{	return cudaMUCols_rotate_buf( (uPMatrix)(MA), ht, len, pos, (uPMatrix)(MBuf) );}
inline overror_t cudaMU_Rows_reflect( uMatrix MA, ui ht, ui len )
	{	return cudaMURows_reflect( (uPMatrix)(MA), ht, len );}
inline overror_t cudaMU_Cols_reflect( uMatrix MA, ui ht, ui len )
	{	return cudaMUCols_reflect( (uPMatrix)(MA), ht, len );}
inline overror_t cudaMU_Rows_rev( uMatrix MA, ui ht, ui len )
	{	return cudaMURows_rev( (uPMatrix)(MA), ht, len );}
inline overror_t cudaMU_Cols_rev( uMatrix MA, ui ht, ui len )
	{	return cudaMUCols_rev( (uPMatrix)(MA), ht, len );}
inline overror_t  cudaMU_Rows_distribution( uiMatrix MAbund, uVector Limits, ui nBins, uMatrix MX, ui ht, ui len, int mode )
	{	return cudaMURows_distribution( (uiPMatrix)MAbund, Limits, nBins, (uPMatrix)MX, ht, len, mode ); }
inline overror_t  cudaMU_Cols_distribution( uiMatrix MAbund, uVector Limits, ui nBins, uMatrix MX, ui ht, ui len, int mode )
	{	return cudaMUCols_distribution( (uiPMatrix)MAbund, Limits, nBins, (uPMatrix)MX, ht, len, mode ); }

/********  Operations involving two rows or two colums of one matrix  *****/

inline overror_t cudaMU_Rows_exchange( uMatrix MA, ui ht, ui len, ui row1, ui row2 )
	{	return cudaMURows_exchange( (uPMatrix)(MA), ht, len, row1, row2 );}
inline overror_t cudaMU_Cols_exchange( uMatrix MA, ui ht, ui len, ui col1, ui col2 )
	{	return cudaMUCols_exchange( (uPMatrix)(MA), ht, len, col1, col2 );}

/*************** Transposing and rotating a matrix **********************/

inline overror_t cudaMU_transpose( uMatrix MTr, uMatrix MA, ui htTr, ui lenTr )
	{	return cudaMUtranspose( (uPMatrix)(MTr), (uPMatrix)(MA), htTr, lenTr );}
       /*  dimensions htTr, lenTr are those of the transposed matrix, not of the original!   */
inline overror_t cudaMU_rotate90( uMatrix MRot, uMatrix MA, ui htRot, ui lenRot )
	{	return cudaMUrotate90( (uPMatrix)(MRot), (uPMatrix)(MA), htRot, lenRot );}
inline overror_t cudaMU_rotate180( uMatrix MRot, uMatrix MA, ui htRot, ui lenRot )
	{	return cudaVU_rev( (uPMatrix)(MRot), (uPMatrix)(MA), (htRot)*(lenRot) );}
inline overror_t cudaMU_rotate270( uMatrix MRot, uMatrix MA, ui htRot, ui lenRot )
	{	return cudaMUrotate270( (uPMatrix)(MRot), (uPMatrix)(MA), htRot, lenRot );}
inline overror_t cudaMU_transpose_buf( uMatrix MTr, uMatrix MA, ui htTr, ui lenTr, uMatrix MBuf )
	{	return cudaMUtranspose_buf( (uPMatrix)(MTr), (uPMatrix)(MA), htTr, lenTr, (uPMatrix)(MBuf) );}

/**************************  Input and Output  **************************
	The input/output functions involve memory transfers from device
	to host memory or vice versa. The generic cudaMU_input/output functions
	allocate their own host buffers, whereas the cudaMU_xxx_buf functions
	take a user-supplied buffer vector h_Wk (size must be >= ht*len )
	and are much more efficient.                                       */

inline overror_t cudaMU_fprint( FILE *stream, uMatrix MA, ui ht, ui len, unsigned linewidth )
	{	return cudaMUfprint( stream, (uPMatrix)(MA), ht, len, linewidth ); }
inline overror_t cudaMU_print( uMatrix MA, ui ht, ui len )
	{	return cudaMUfprint( stdout, (uPMatrix)(MA), ht, len, 80 ); }
inline overror_t cudaMU_cprint( uMatrix MA, ui ht, ui len )
	{	return cudaMUcprint( (uPMatrix)(MA), ht, len ); }
inline overror_t cudaMU_fprint_buf( FILE *stream, uMatrix d_MA, ui ht, ui len, unsigned linewidth, uVector h_Wk )
	{	return cudaMUfprint_buf( stream, (uPMatrix)(d_MA), ht, len, linewidth, h_Wk ); }
inline overror_t cudaMU_print_buf( uMatrix d_MA, ui ht, ui len, uVector h_Wk )
	{	return cudaMUfprint_buf( stdout, (uPMatrix)(d_MA), ht, len, 80, h_Wk ); }
inline overror_t cudaMU_cprint_buf( uMatrix d_MA, ui ht, ui len, uVector h_Wk )
	{	return cudaMUcprint_buf( (uPMatrix)(d_MA), ht, len, h_Wk ); }
		/*  cudaMU_print, cudaMU_cprint usable only for console applications! */
inline overror_t  cudaMU_write( FILE *stream, uMatrix MA, ui ht, ui len )
	{	return cudaMUwrite( stream, (uPMatrix)(MA), ht, len ); }
inline overror_t cudaMU_read( uMatrix MA, ui ht, ui len, FILE *stream )
	{	return cudaMUread( (uPMatrix)(MA), ht, len, stream ); }
inline overror_t  cudaMU_write_buf( FILE *stream, uMatrix d_MA, ui ht, ui len, uVector h_Wk )
	{	return cudaMUwrite_buf( stream, (uPMatrix)(d_MA), ht, len, h_Wk ); }
inline overror_t cudaMU_read_buf( uMatrix d_MA, ui ht, ui len, FILE *stream, uVector h_Wk )
	{	return cudaMUread_buf( (uPMatrix)(d_MA), ht, len, stream, h_Wk ); }
                                   /* write and read in ascii format */
inline overror_t cudaMU_store( FILE *stream, uMatrix MA, ui ht, ui len )
{	return cudaVU_store( stream, (uPMatrix)(MA), (len)*(ht) ); }
inline overror_t cudaMU_recall( uMatrix MA, ui ht, ui len, FILE *stream )
	{	return cudaVU_recall( (uPMatrix)(MA), (len)*(ht), stream ); }
inline overror_t cudaMU_store_buf( FILE *stream, uMatrix d_MA, ui ht, ui len, uVector h_Wk )
{	return cudaVU_store_buf( stream, (uPMatrix)(d_MA), (len)*(ht), h_Wk ); }
inline overror_t cudaMU_recall_buf( uMatrix d_MA, ui ht, ui len, FILE *stream, uVector h_Wk )
	{	return cudaVU_recall_buf( (uPMatrix)(d_MA), (len)*(ht), stream, h_Wk ); }
                                  /* store and recall in binary format */

#else  /* plain-C, not C++: type-cast used to transform uMatrix into uPMatrix */


/***  Addressing single elements of dynamically allocated matrices: ******/

#define cudaMU_setElement( MA, ht, len, m, n, C ) cudaMUsetElement( (uPMatrix)(MA), ht, len, m, n, C )
#define cusdMU_setElement( MA, ht, len, m, n, C ) cusdMUsetElement( (uPMatrix)(MA), ht, len, m, n, C )
#define cudaMU_getElement( y, MA, ht, len, m, n ) cudaMUgetElement( y, (uPMatrix)(MA), ht, len, m, n )
#define cusdMU_getElement( y, MA, ht, len, m, n ) cusdMUgetElement( y, (uPMatrix)(MA), ht, len, m, n )
#define cudaMU_Pelement( MA, ht, len, m, n )      cudaMUPelement( (uPMatrix)(MA), ht, len, m, n )
#define cudaMU_element(  MA, ht, len, m, n )      cudaMUelement( (uPMatrix)(MA), ht, len, m, n )

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
        cudaVU_equ1( (uVector)MA, ht * len );
*/

#define cudaMU_equ0( MA, ht, len )            cudaVU_equ0( (uPMatrix)(MA), (ht)*(len) )
#define cudaMU_equ1( MA, len )                cudaMUequ1( (uPMatrix)(MA), len ) /* identity matrix */
#define cudaMU_randomLC( MA, ht, len, seed, Min, Max, h_state )      cudaVU_randomLC( MA, (ht)*(len), seed, Min, Max, h_state )
#define cudaMU_random( MA, ht, len, seed, Min, Max )                 cudaVU_random( MA, (ht)*(len), seed, Min, Max )
#define cusdMU_randomLC( MA, ht, len, seed, d_Min, d_Max, h_state )  cudaVU_randomLC( MA, (ht)*(len), seed, d_Min, d_Max, h_state )
#define cusdMU_random( MA, ht, len, seed, d_Min, d_Max )             cudaVU_random( MA, (ht)*(len), seed, d_Min, d_Max )
#define cudaMU_outerprod( MA, X, Y, ht, len ) cudaMUouterprod( (uPMatrix)(MA), X, Y, ht, len )
                       /* sizX=ht, sizY=len */
#define cudaMU_Row_equ0( MA, ht, len, iRow )    cudaMURow_equ0( (uPMatrix)(MA), ht, len, iRow )
#define cudaMU_Col_equ0( MA, ht, len, iCol )    cudaMUCol_equ0( (uPMatrix)(MA), ht, len, iCol )
#define cudaMU_Dia_equ0( MA, len )              cudaMUDia_equ0( (uPMatrix)(MA), len )
#define cudaMU_Row_equC( MA, ht, len, iRow, C ) cudaMURow_equC( (uPMatrix)(MA), ht, len, iRow, C )
#define cudaMU_Col_equC( MA, ht, len, iCol, C ) cudaMUCol_equC( (uPMatrix)(MA), ht, len, iCol, C )
#define cudaMU_Dia_equC( MA, len, C )           cudaMUDia_equC( (uPMatrix)(MA), len, C )
#define cusdMU_Row_equC( MA, ht, len, iRow, d_C ) cusdMURow_equC( (uPMatrix)(MA), ht, len, iRow, d_C )
#define cusdMU_Col_equC( MA, ht, len, iCol, d_C ) cusdMUCol_equC( (uPMatrix)(MA), ht, len, iCol, d_C )
#define cusdMU_Dia_equC( MA, len, d_C )           cusdMUDia_equC( (uPMatrix)(MA), len, d_C )

#define cudaMU_Row_equV( MA, ht, len, iRow, X ) cudaMURow_equV( (uPMatrix)(MA), ht, len, iRow, X )
#define cudaMU_Col_equV( MA, ht, len, iCol, X ) cudaMUCol_equV( (uPMatrix)(MA), ht, len, iCol, X )
#define cudaMU_Dia_equV( MA, len, X )           cudaMUDia_equV( (uPMatrix)(MA), len, X )

#define cudaMU_Trd_equM( MA, MTrd, len )    cudaMUTrd_equM( (uPMatrix)(MA), (uPMatrix)(MTr)d, len )
#define cudaMU_Trd_extract( MTrd, MA, len ) cudaMUTrd_extract( (uPMatrix)(MTr)d, (uPMatrix)(MA), len )

#define cudaMU_equM( MB, MA, ht, len )      cudaVU_equV( (uPMatrix)(MB), (uPMatrix)(MA), (ht)*(len) )
#define cudaMU_equMhost( MB, MA, ht, len )  cudaVU_equVhost( (uPMatrix)(MB), MA[0], (ht)*(len) )
#define MU_equMdevice( MB, MA, ht, len )    VU_equVdevice( MB[0], (uPMatrix)(MA), (ht)*(len) )

#define cudaMU_UequL( MA, len ) cudaMUUequL( (uPMatrix)(MA), len )
#define cudaMU_LequU( MA, len ) cudaMULequU( (uPMatrix)(MA), len )

/************** Data-type interconversions  ****************************/

#define cudaM_ItoU( MU, MI, ht, len ) cudaV_ItoU( (uVector)(MU), (iVector)(MI), (ht)*(len) )
#define cudaM_UtoI( MI, MU, ht, len ) cudaV_UtoI( (iVector)(MI), (uVector)(MU), (ht)*(len) )
#define cudaM_UtoUB( MUB, MU, ht, len ) cudaV_UtoUB( (ubVector)(MUB), (uVector)(MU), (ht)*(len) )
#define cudaM_UtoUS( MUS, MU, ht, len ) cudaV_UtoUS( (usVector)(MUS), (uVector)(MU), (ht)*(len) )
#define cudaM_UtoUL( MUL, MU, ht, len ) cudaV_UtoUL( (ulVector)(MUL), (uVector)(MU), (ht)*(len) )
#define cudaM_UBtoU( MU, MUB, ht, len ) cudaV_UBtoU( (uVector)(MU), (ubVector)(MUB), (ht)*(len) )
#define cudaM_UStoU( MU, MUS, ht, len ) cudaV_UStoU( (uVector)(MU), (usVector)(MUS), (ht)*(len) )
#define cudaM_ULtoU( MU, MUL, ht, len ) cudaV_ULtoU( (uVector)(MU), (ulVector)(MUL), (ht)*(len) )
#ifdef _WIN64
	#define cudaM_UtoUQ( MUQ, MU, ht, len ) cudaV_UtoUQ( (uqVector)(MUQ), (uVector)(MU), (ht)*(len) )
	#define cudaM_UQtoU( MU, MUQ, ht, len ) cudaV_UQtoU( (uVector)(MU), (uqVector)(MUQ), (ht)*(len) )
#endif
#define cudaM_UtoF(  MF,  MU, ht, len ) cudaV_UtoF(  (fVector)(MF),   (uVector)(MU), (ht)*(len) )
#define cudaM_UtoD(  MD,  MU, ht, len ) cudaV_UtoD(  (dVector)(MD),   (uVector)(MU), (ht)*(len) )


/********  Extracting a submatrix and copying a submatrix back  *********/

#define cudaMU_submatrix( MSub, subHt, subLen, MSrce, srceHt, srceLen, \
                      firstRowInCol, sampInCol, firstColInRow, sampInRow ) \
               cudaMUsubmatrix(  (uPMatrix)(MSub), subHt, subLen, \
                             (uPMatrix)(MSrce), srceHt, srceLen, \
                             firstRowInCol, sampInCol, firstColInRow, sampInRow )

#define cudaMU_submatrix_equM( MDest, destHt, destLen, \
                           firstRowInCol, sampInCol, firstColInRow, sampInRow, \
                           MSrce, srceHt, srceLen ) \
               cudaMUsubmatrix_equM(  (uPMatrix)(MDest), destHt, destLen, \
                             firstRowInCol, sampInCol, firstColInRow, sampInRow, \
                             (uPMatrix)(MSrce), srceHt, srceLen )

#define cudaMU_equMblock( MSub, subHt, subLen, MSrce, srceHt, srceLen, \
                      firstRowInCol, firstColInRow ) \
               cudaMUequMblock(  (uPMatrix)(MSub), subHt, subLen, \
                             (uPMatrix)(MSrce), srceHt, srceLen, \
                             firstRowInCol, firstColInRow )

#define cudaMU_block_equM( MDest, destHt, destLen, \
                       firstRowInCol, firstColInRow, \
                       MSrce, srceHt, srceLen ) \
               cudaMUblock_equM( (uPMatrix)(MDest), destHt, destLen, \
                             firstRowInCol, firstColInRow, \
                             (uPMatrix)(MSrce), srceHt, srceLen )

#define cudaMU_equMblockT( MSub, subHt, subLen, \
                      MSrce, srceHt, srceLen, \
                      firstRowInCol, firstColInRow ) \
               cudaMUequMblockT(  (uPMatrix)(MSub), subHt, subLen, \
                             (uPMatrix)(MSrce), srceHt, srceLen, \
                             firstRowInCol, firstColInRow )

#define cudaMU_block_equMT( MDest, destHt, destLen, \
                       firstRowInCol, firstColInRow, \
                       MSrce, srceHt, srceLen ) \
               cudaMUblock_equMT( (uPMatrix)(MDest), destHt, destLen, \
                             firstRowInCol, firstColInRow, \
                             (uPMatrix)(MSrce), srceHt, srceLen )

/*****   Extracting a single row or a single column or the diagonal  ******
 *       and storing it into a vector                                     */

#define cudaMU_Row_extract( Y, MA, ht, len, iRow ) cudaMURow_extract( Y, (uPMatrix)(MA), ht, len, iRow )
#define cudaMU_Col_extract( Y, MA, ht, len, iCol ) cudaMUCol_extract( Y, (uPMatrix)(MA), ht, len, iCol )
#define cudaMU_Dia_extract( Y, MA, len )           cudaMUDia_extract( Y, (uPMatrix)(MA), len )


/**************  Deleting or inserting a row or a column   ***************/

#define cudaMU_Row_delete( MB, MA, htA, lenA, iRow ) cudaMURow_delete( (uPMatrix)(MB), (uPMatrix)(MA), htA, lenA, iRow )
#define cudaMU_Col_delete( MB, MA, htA, lenA, iCol ) cudaMUCol_delete( (uPMatrix)(MB), (uPMatrix)(MA), htA, lenA, iCol )
#define cudaMU_Row_insert( MB, MA, htB, lenB, iRow, X ) cudaMURow_insert( (uPMatrix)(MB), (uPMatrix)(MA), htB, lenB, iRow, X )
#define cudaMU_Col_insert( MB, MA, htB, lenB, iCol, X ) cudaMUCol_insert( (uPMatrix)(MB), (uPMatrix)(MA), htB, lenB, iCol, X )

/******  One-dimensional vector operations **********************
         performed along all rows or all columns simultaneously,
         or along the diagonal of a square matrix                */

#define cudaMU_Rows_max( Y, MA, ht, len )     cudaMURows_max( Y, (uPMatrix)(MA), ht, len )
#define cudaMU_Cols_max( Y, MA, ht, len )     cudaMUCols_max( Y, (uPMatrix)(MA), ht, len )
#define cudaMU_Dia_max(  h_RetPtr, MA, len )  cudaMUDia_max( h_RetPtr, (uPMatrix)(MA), len )
#define cusdMU_Dia_max(  d_RetPtr, MA, len )  cusdMUDia_max( d_RetPtr, (uPMatrix)(MA), len )
#define cudaMU_Rows_min( Y, MA, ht, len )     cudaMURows_min( Y, (uPMatrix)(MA), ht, len )
#define cudaMU_Cols_min( Y, MA, ht, len )     cudaMUCols_min( Y, (uPMatrix)(MA), ht, len )
#define cudaMU_Dia_min(  h_RetPtr, MA, len )  cudaMUDia_min( h_RetPtr, (uPMatrix)(MA), len )
#define cusdMU_Dia_min(  d_RetPtr, MA, len )  cusdMUDia_min( d_RetPtr, (uPMatrix)(MA), len )

#define cudaMU_Rows_rotate( MA, ht, len, pos) cudaMURows_rotate( (uPMatrix)(MA), ht, len, pos )
#define cudaMU_Cols_rotate( MA, ht, len, pos) cudaMUCols_rotate( (uPMatrix)(MA), ht, len, pos )
#define cudaMU_Rows_rotate_buf( MA, ht, len, pos, MBuf) cudaMURows_rotate_buf( (uPMatrix)(MA), ht, len, pos, (uPMatrix)(MBuf) )
#define cudaMU_Cols_rotate_buf( MA, ht, len, pos, MBuf) cudaMUCols_rotate_buf( (uPMatrix)(MA), ht, len, pos, (uPMatrix)(MBuf) )
#define cudaMU_Rows_reflect( MA, ht, len)     cudaMURows_reflect( (uPMatrix)(MA), ht, len )
#define cudaMU_Cols_reflect( MA, ht, len)     cudaMUCols_reflect( (uPMatrix)(MA), ht, len )
#define cudaMU_Rows_rev( MA, ht, len)         cudaMURows_rev( (uPMatrix)(MA), ht, len )
#define cudaMU_Cols_rev( MA, ht, len)         cudaMUCols_rev( (uPMatrix)(MA), ht, len )
#define cudaMU_Rows_distribution( MAbund, Limits, nBins, MX, ht, len, mode ) cudaMURows_distribution( (uiPMatrix)MAbund, Limits, nBins, (uPMatrix)MX, ht, len, mode )
#define cudaMU_Cols_distribution( MAbund, Limits, nBins, MX, ht, len, mode ) cudaMUCols_distribution( (uiPMatrix)MAbund, Limits, nBins, (uPMatrix)MX, ht, len, mode )

/********  Operations involving two rows or two colums of one matrix  *****/

#define cudaMU_Rows_exchange( MA, ht, len, row1, row2 ) cudaMURows_exchange( (uPMatrix)(MA), ht, len, row1, row2 )
#define cudaMU_Cols_exchange( MA, ht, len, col1, col2 ) cudaMUCols_exchange( (uPMatrix)(MA), ht, len, col1, col2 )

/****************  Transposing and rotating a matrix **********************/

#define cudaMU_transpose( MTr, MA, htTr, lenTr ) cudaMUtranspose( (uPMatrix)(MTr), (uPMatrix)(MA), htTr, lenTr )
       /*  dimensions htTr, lenTr are those of the transposed matrix,
           not of the original!                */
#define cudaMU_rotate90( MRot, MA, htRot, lenRot )  cudaMUrotate90( (uPMatrix)(MRot), (uPMatrix)(MA), htRot, lenRot )
#define cudaMU_rotate180( MRot, MA, htRot, lenRot ) cudaVU_rev( (uPMatrix)(MRot), (uPMatrix)(MA), (htRot)*(lenRot) )
#define cudaMU_rotate270( MRot, MA, htRot, lenRot ) cudaMUrotate270( (uPMatrix)(MRot), (uPMatrix)(MA), htRot, lenRot )
#define cudaMU_transpose_buf( MTr, MA, htTr, lenTr, MBuf ) cudaMUtranspose_buf( (uPMatrix)(MTr), (uPMatrix)(MA), htTr, lenTr, (uPMatrix)(MBuf) )


/**************************  Input and Output  **************************
	The input/output functions involve memory transfers from device
	to host memory or vice versa. The generic cudaMU_input/output functions
	allocate their own host buffers, whereas the cudaMU_xxx_buf functions
	take a user-supplied buffer vector h_Wk (size must be >= ht*len )
	and are much more efficient.                                       */

#define cudaMU_fprint( stream, MA, ht, len, linewidth ) \
                    cudaMUfprint( stream, (uPMatrix)(MA), ht, len, linewidth )
#define cudaMU_print( MA, ht, len )  cudaMUfprint( stdout, (uPMatrix)(MA), ht, len, 80 )
#define cudaMU_cprint( MA, ht, len ) cudaMUcprint( (uPMatrix)(MA), ht, len )
#define cudaMU_fprint_buf( stream, MA, ht, len, linewidth, h_Wk ) \
                    cudaMUfprint_buf( stream, (uPMatrix)(MA), ht, len, linewidth, h_Wk )
#define cudaMU_print_buf( MA, ht, len )  cudaMUfprint_buf( stdout, (uPMatrix)(MA), ht, len, 80, h_Wk )
#define cudaMU_cprint_buf( MA, ht, len ) cudaMUcprint_buf( (uPMatrix)(MA), ht, len, h_Wk )
  /*  cudaMU_print, cudaMU_cprint usable only for console applications! */
#define cudaMU_write( str, MA, ht, len )   cudaMUwrite( str, (uPMatrix)(MA), ht, len )
#define cudaMU_read( MA, ht, len, str )    cudaMUread( (uPMatrix)(MA), ht, len, str )
#define cudaMU_write_buf( str, MA, ht, len, h_Wk )   cudaMUwrite_buf( str, (uPMatrix)(MA), ht, len, h_Wk )
#define cudaMU_read_buf( MA, ht, len, str, h_Wk )    cudaMUread_buf( (uPMatrix)(MA), ht, len, str, h_Wk )
                                   /* write and read in ascii format */
#define cudaMU_store( str, MA, ht, len )   cudaVU_store( str, (uPMatrix)(MA), (len)*(ht) )
#define cudaMU_recall( MA, ht, len, str)   cudaVU_recall( (uPMatrix)(MA), (len)*(ht), str)
#define cudaMU_store_buf( str, MA, ht, len, h_Wk )   cudaVU_store_buf( str, (uPMatrix)(MA), (len)*(ht), h_Wk )
#define cudaMU_recall_buf( MA, ht, len, str, h_Wk)   cudaVU_recall_buf( (uPMatrix)(MA), (len)*(ht), str, h_Wk )
                                  /* store and recall in binary format */

#endif /* plain-C or C++ for functions working on device memory */


/*******************  Functions working on host memory: **********************
 *                                                                           *
 *	MIcu_func		(working on matrices in host memory, input type iMatrix,*
 *	scalar parameters on host and passed by value)                           *
 *****************************************************************************/ 

/****************  Initialization  ****************************************/

#define MUcu_equ0( MA, ht, len )                   VUcu_equ0( (MA)[0], (ht)*(len) )
#define MUcu_equ1( MA, len )                       MUcuequ1( (MA)[0], len ) /* identity matrix */
#define MUcu_randomLC( MA, ht, len, seed, Min, Max, state ) VUcu_randomLC( (MA)[0], (ht)*(len), seed, Min, Max, state )
#define MUcu_random( MA, ht, len, seed, Min, Max )          VUcu_random( (MA)[0], (ht)*(len), seed, Min, Max )
#define MUcu_outerprod( MA, X, Y, ht, len )        MUcuouterprod( (MA)[0], X, Y, ht, len )
                       /* sizX=ht, sizY=len */
#define MUcu_Row_equ0( MA, ht, len, iRow )    MUcuRow_equ0( (MA)[0], ht, len, iRow )
#define MUcu_Col_equ0( MA, ht, len, iCol )    MUcuCol_equ0( (MA)[0], ht, len, iCol )
#define MUcu_Dia_equ0( MA, len )              MUcuDia_equ0( (MA)[0], len )
#define MUcu_Row_equC( MA, ht, len, iRow, C ) MUcuRow_equC( (MA)[0], ht, len, iRow, C )
#define MUcu_Col_equC( MA, ht, len, iCol, C ) MUcuCol_equC( (MA)[0], ht, len, iCol, C )
#define MUcu_Dia_equC( MA, len, C )           MUcuDia_equC( (MA)[0], len, C )

#define MUcu_Row_equV( MA, ht, len, iRow, X ) MUcuRow_equV( (MA)[0], ht, len, iRow, X )
#define MUcu_Col_equV( MA, ht, len, iCol, X ) MUcuCol_equV( (MA)[0], ht, len, iCol, X )
#define MUcu_Dia_equV( MA, len, X )           MUcuDia_equV( (MA)[0], len, X )

#define MUcu_Trd_equM( MA, MTrd, len )        MUcuTrd_equM( (MA)[0], (MTrd)[0], len )
#define MUcu_Trd_extract( MTrd, MA, len )     MUcuTrd_extract( (MTrd)[0], (MA)[0], len )

#define MUcu_equM( MB, MA, ht, len )          VUcu_equV( (MB)[0], (MA)[0], (ht)*(len) )
#define MUcu_equMhost( MB, MA, ht, len )      VUcu_equVhost( (MB)[0], MA[0], (ht)*(len) )

#define MUcu_UequL( MA, len ) MUcuUequL( (MA)[0], len )
#define MUcu_LequU( MA, len ) MUcuLequU( (MA)[0], len )
     /* copy lower-diagonal elements into upper-diagonal
       (or vice versa) by index-reflection, so as to get a symmetric matrix    */

            /* data-type conversions:  */
#define Mcu_ItoU( MU, MI, ht, len ) Vcu_ItoU( (MU)[0], (MI)[0], (ht)*(len) )
#define Mcu_UtoI( MI, MU, ht, len ) Vcu_UtoI( (MI)[0], (MU)[0], (ht)*(len) )
#define Mcu_UtoUB( MUB, MU, ht, len ) Vcu_UtoUB( (MUB)[0], (MU)[0], (ht)*(len) )
#define Mcu_UtoUS( MUS, MU, ht, len ) Vcu_UtoUS( (MUS)[0], (MU)[0], (ht)*(len) )
#define Mcu_UtoUL( MUL, MU, ht, len ) Vcu_UtoUL( (MUL)[0], (MU)[0], (ht)*(len) )
#define Mcu_UBtoU( MU, MUB, ht, len ) Vcu_UBtoU( (MU)[0], (MUB)[0], (ht)*(len) )
#define Mcu_UStoU( MU, MUS, ht, len ) Vcu_UStoU( (MU)[0], (MUS)[0], (ht)*(len) )
#define Mcu_ULtoU( MU, MUL, ht, len ) Vcu_ULtoU( (MU)[0], (MUL)[0], (ht)*(len) )
#ifdef _WIN64
	#define Mcu_UtoUQ( MUQ, MU, ht, len ) Vcu_UtoUQ( (MUQ)[0], (MU)[0], (ht)*(len) )
	#define Mcu_UQtoU( MU, MUQ, ht, len ) Vcu_UQtoU( (MU)[0], (MUQ)[0], (ht)*(len) )
#endif
#define Mcu_UtoF(  MF,  MU, ht, len ) Vcu_UtoF(  (MF)[0],  (MU)[0], (ht)*(len) )
#define Mcu_UtoD(  MD,  MU, ht, len ) Vcu_UtoD(  (MD)[0],  (MU)[0], (ht)*(len) )


/********  Extracting a submatrix and copying a submatrix back  *********/

#define MUcu_submatrix( MSub, subHt, subLen, MSrce, srceHt, srceLen, \
                      firstRowInCol, sampInCol, firstColInRow, sampInRow ) \
               MUcusubmatrix(  (MSub)[0], subHt, subLen, \
                             (MSrce)[0], srceHt, srceLen, \
                             firstRowInCol, sampInCol, firstColInRow, sampInRow )

#define MUcu_submatrix_equM( MDest, destHt, destLen, \
                           firstRowInCol, sampInCol, firstColInRow, sampInRow, \
                           MSrce, srceHt, srceLen ) \
               MUcusubmatrix_equM(  (MDest)[0], destHt, destLen, \
                             firstRowInCol, sampInCol, firstColInRow, sampInRow, \
                             (MSrce)[0], srceHt, srceLen )

#define MUcu_equMblock( MSub, subHt, subLen, MSrce, srceHt, srceLen, \
                      firstRowInCol, firstColInRow ) \
               MUcuequMblock(  (MSub)[0], subHt, subLen, \
                             (MSrce)[0], srceHt, srceLen, \
                             firstRowInCol, firstColInRow )

#define MUcu_block_equM( MDest, destHt, destLen, \
                       firstRowInCol, firstColInRow, \
                       MSrce, srceHt, srceLen ) \
               MUcublock_equM( (MDest)[0], destHt, destLen, \
                             firstRowInCol, firstColInRow, \
                             (MSrce)[0], srceHt, srceLen )

#define MUcu_equMblockT( MSub, subHt, subLen, MSrce, srceHt, srceLen, \
                      firstRowInCol, firstColInRow ) \
               MUcuequMblockT(  (MSub)[0], subHt, subLen, \
                             (MSrce)[0], srceHt, srceLen, \
                             firstRowInCol, firstColInRow )

#define MUcu_block_equMT( MDest, destHt, destLen, \
                       firstRowInCol, firstColInRow, \
                       MSrce, srceHt, srceLen ) \
               MUcublock_equMT( (MDest)[0], destHt, destLen, \
                             firstRowInCol, firstColInRow, \
                             (MSrce)[0], srceHt, srceLen )

/*****   Extracting a single row or a single column or the diagonal  ******
 *       and storing it into a vector                                     */

#define MUcu_Row_extract( Y, MA, ht, len, iRow ) MUcuRow_extract( Y, (MA)[0], ht, len, iRow )
#define MUcu_Col_extract( Y, MA, ht, len, iCol ) MUcuCol_extract( Y, (MA)[0], ht, len, iCol )
#define MUcu_Dia_extract( Y, MA, len )           MUcuDia_extract( Y, (MA)[0], len )

/**************  Deleting or inserting a row or a column   ***************/

#define MUcu_Row_delete( MB, MA, htA, lenA, iRow )    MUcuRow_delete( (MB)[0], (MA)[0], htA, lenA, iRow )
#define MUcu_Col_delete( MB, MA, htA, lenA, iCol )    MUcuCol_delete( (MB)[0], (MA)[0], htA, lenA, iCol )
#define MUcu_Row_insert( MB, MA, htB, lenB, iRow, X ) MUcuRow_insert( (MB)[0], (MA)[0], htB, lenB, iRow, X )
#define MUcu_Col_insert( MB, MA, htB, lenB, iCol, X ) MUcuCol_insert( (MB)[0], (MA)[0], htB, lenB, iCol, X )


/******  One-dimensional vector operations **********************
         performed along all rows or all columns simultaneously,
         or along the diagonal of a square matrix                */

#define MUcu_Rows_max( Y, MA, ht, len )        MUcuRows_max( Y, (MA)[0], ht, len )
#define MUcu_Cols_max( Y, MA, ht, len )        MUcuCols_max( Y, (MA)[0], ht, len )
#define MUcu_Dia_max(  MA, len )               MUcuDia_max(  (MA)[0], len )
#define MUcu_Rows_min( Y, MA, ht, len )        MUcuRows_min( Y, (MA)[0], ht, len )
#define MUcu_Cols_min( Y, MA, ht, len )        MUcuCols_min( Y, (MA)[0], ht, len )
#define MUcu_Dia_min(  MA, len )               MUcuDia_min(  (MA)[0], len )

#define MUcu_Rows_rotate( MA, ht, len, pos)           MUcuRows_rotate( (MA)[0], ht, len, pos )
#define MUcu_Cols_rotate( MA, ht, len, pos)           MUcuCols_rotate( (MA)[0], ht, len, pos )
#define MUcu_Rows_rotate_buf( MA, ht, len, pos, MBuf) MUcuRows_rotate_buf( (MA)[0], ht, len, pos, (MBuf)[0] )
#define MUcu_Cols_rotate_buf( MA, ht, len, pos, MBuf) MUcuCols_rotate_buf( (MA)[0], ht, len, pos, (MBuf)[0] )
#define MUcu_Rows_reflect( MA, ht, len )              MUcuRows_reflect( (MA)[0], ht, len )
#define MUcu_Cols_reflect( MA, ht, len )              MUcuCols_reflect( (MA)[0], ht, len )
#define MUcu_Rows_rev( MA, ht, len)                   MUcuRows_rev( (MA)[0], ht, len )
#define MUcu_Cols_rev( MA, ht, len)                   MUcuCols_rev( (MA)[0], ht, len )
#define MUcu_Rows_distribution( MAbund, Limits, nBins, MX, ht, len, mode ) MUcuRows_distribution( MAbund[0], Limits, nBins, MX[0], ht, len, mode )
#define MUcu_Cols_distribution( MAbund, Limits, nBins, MX, ht, len, mode ) MUcuCols_distribution( MAbund[0], Limits, nBins, MX[0], ht, len, mode )

/********  Operations involving two rows or two colums of one matrix  *****/

#define MUcu_Rows_exchange( MA, ht, len, row1, row2 ) \
                             MUcuRows_exchange( (MA)[0], ht, len, row1, row2 )
#define MUcu_Cols_exchange( MA, ht, len, col1, col2 ) \
                             MUcuCols_exchange( (MA)[0], ht, len, col1, col2 )

/*************** Transposing and rotating a matrix **********************/

#define MUcu_transpose( MTr, MA, htTr, lenTr )    MUcutranspose( (MTr)[0], (MA)[0], htTr, lenTr )
       /*  dimensions htTr, lenTr are those of the transposed matrix, not of the original!   */
#define MUcu_rotate90( MRot, MA, htRot, lenRot )  MUcurotate90( (MRot)[0], (MA)[0], htRot, lenRot )
#define MUcu_rotate180( MRot, MA, htRot, lenRot ) VUcu_rev( (MRot)[0], (MA)[0], (htRot)*(lenRot) )
#define MUcu_rotate270( MRot, MA, htRot, lenRot ) MUcurotate270( (MRot)[0], (MA)[0], htRot, lenRot )

/*************************************************************************
 * MUcu functions (without underbar in the prefix): 	
    (working on matrices in host memory, input type 
	uPMatrix = uVector = pointer to matrix element[0][0], 
	scalar parameters on host and passed by value)
*
 *************************************************************************/

#define MUcuequ0( MA, ht, len )       VUcu_equ0( MA, (ht)*(len) )
void   __vf OVCUAPI  MUcuequ1( uPMatrix MA, ui len );  /* identity matrix */
void   __vf OVCUAPI  MUcuouterprod( uPMatrix MA, uVector X,  uVector Y, ui ht, ui len );

void   __vf OVCUAPI  MUcuRow_equ0( uPMatrix MA, ui ht, ui len, ui iRow );
void   __vf OVCUAPI  MUcuCol_equ0( uPMatrix MA, ui ht, ui len, ui iCol );
void   __vf OVCUAPI  MUcuDia_equ0( uPMatrix MA, ui len );

void   __vf OVCUAPI  MUcuRow_equC( uPMatrix MA, ui ht, ui len, ui iRow, unsigned C );
void   __vf OVCUAPI  MUcuCol_equC( uPMatrix MA, ui ht, ui len, ui iCol, unsigned C );
void   __vf OVCUAPI  MUcuDia_equC( uPMatrix MA, ui len, unsigned C );

void   __vf OVCUAPI  MUcuRow_equV( uPMatrix MA, ui ht, ui len, ui iRow, uVector X );
void   __vf OVCUAPI  MUcuCol_equV( uPMatrix MA, ui ht, ui len, ui iCol, uVector X );
void   __vf OVCUAPI  MUcuDia_equV( uPMatrix MA, ui len, uVector X );

void   __vf OVCUAPI  MUcuTrd_equM( uPMatrix MA, uPMatrix MTrd, ui len );
void   __vf OVCUAPI  MUcuTrd_extract( uPMatrix MTrd, uPMatrix MA, ui len );

#define MUcuequM( MB, MA, ht, len )      VUcu_equV( MB, MA, (ht)*(len) )
void   __vf OVCUAPI  MUcuUequL( uPMatrix MA, ui len );
void   __vf OVCUAPI  MUcuLequU( uPMatrix MA, ui len );

            /* data-type conversions:  */
#define McuItoU( MU, MI, ht, len ) Vcu_ItoU( MU, MI, (ht)*(len) )
#define McuUtoI( MI, MU, ht, len ) Vcu_UtoI( MI, MU, (ht)*(len) )
#define McuUtoUB( MUB, MU, ht, len ) Vcu_UtoUB( MUB, MU, (ht)*(len) )
#define McuUtoUS( MUS, MU, ht, len ) Vcu_UtoUS( MUS, MU, (ht)*(len) )
#define McuUtoUL( MUL, MU, ht, len ) Vcu_UtoUL( MUL, MU, (ht)*(len) )
#define McuUBtoU( MU, MUB, ht, len ) Vcu_UBtoU( MU,  MUB, (ht)*(len) )
#define McuUStoU( MU, MUS, ht, len ) Vcu_UStoU( MU,  MUS, (ht)*(len) )
#define McuULtoU( MU, MUL, ht, len ) Vcu_ULtoU( MU,  MUL, (ht)*(len) )
#ifdef _WIN64
	#define McuUtoUQ( MUQ, MU, ht, len ) Vcu_UtoUQ( MUQ, MU, (ht)*(len) )
	#define McuUQtoU( MU, MUQ, ht, len ) Vcu_UQtoU( MU, MUQ, (ht)*(len) )
#endif
#define McuUtoF(  MF,  MU, ht, len ) Vcu_UtoF(  MF, MU, (ht)*(len) )
#define McuUtoD(  MD,  MU, ht, len ) Vcu_UtoD(  MD, MU, (ht)*(len) )

/********  Extracting a submatrix and copying a submatrix back  *********/

void  __vf OVCUAPI  MUcusubmatrix( uPMatrix MSub, ui subHt,  ui subLen,
                          uPMatrix MSrce, ui srceHt,  ui srceLen,
                          ui firstRowInCol,  ui sampInCol,
                          ui firstColInRow,  ui sampInRow );

void  __vf OVCUAPI  MUcusubmatrix_equM( uPMatrix MDest, ui destHt, ui destLen,
                               ui firstRowInCol,  ui sampInCol,
                               ui firstColInRow,  ui sampInRow,
                               uPMatrix MSrce, ui srceHt, ui srceLen );

void  __vf OVCUAPI  MUcuequMblock(  uPMatrix MSub, ui subHt, ui subLen,
                          uPMatrix MSrce, ui srceHt,  ui srceLen,
                          ui firstRowInCol,  ui firstColInRow );

void  __vf OVCUAPI  MUcublock_equM( uPMatrix MDest, ui destHt, ui destLen,
                          ui firstRowInCol,  ui firstColInRow,
                          uPMatrix MSrce, ui srceHt, ui srceLen );

void  __vf OVCUAPI  MUcuequMblockT( uPMatrix MSub, ui subHt, ui subLen,
                          uPMatrix MSrce, ui srceHt, ui srceLen,
                          ui firstRowInCol,  ui firstColInRow );

void  __vf OVCUAPI  MUcublock_equMT( uPMatrix MDest, ui destHt, ui destLen,
                          ui firstRowInCol,  ui firstColInRow,
                          uPMatrix MSrce, ui srceHt, ui srceLen );


/*****   Extracting a single row or a single column or the diagonal  *****
 *       and storing it into a vector                                    */

void __vf OVCUAPI  MUcuRow_extract( uVector Y, uPMatrix MA, ui ht, ui len, ui iRow );
void __vf OVCUAPI  MUcuCol_extract( uVector Y, uPMatrix MA, ui ht, ui len, ui iCol );
void __vf OVCUAPI  MUcuDia_extract( uVector Y, uPMatrix MA, ui len );

/**********  Deleting or inserting a row or a column *****************/

void __vf OVCUAPI  MUcuRow_delete( uPMatrix MB, uPMatrix MA, ui htA, ui lenA, ui iRow );
void __vf OVCUAPI  MUcuCol_delete( uPMatrix MB, uPMatrix MA, ui htA, ui lenA, ui iCol );
void __vf OVCUAPI  MUcuRow_insert( uPMatrix MB, uPMatrix MA, ui htB, ui lenB, ui iRow, uVector X );
void __vf OVCUAPI  MUcuCol_insert( uPMatrix MB, uPMatrix MA, ui htB, ui lenB, ui iCol, uVector X );


/******  One-dimensional vector operations **********************
         performed along all rows or all columns simultaneously,
         or along the diagonal of a square matrix                */

void   __vf OVCUAPI  MUcuRows_max( uVector Y, uPMatrix MA, ui ht, ui len );
void   __vf OVCUAPI  MUcuCols_max( uVector Y, uPMatrix MA, ui ht, ui len );
unsigned  __vf OVCUAPI  MUcuDia_max(  uPMatrix MA, ui len );
void   __vf OVCUAPI  MUcuRows_min( uVector Y, uPMatrix MA, ui ht, ui len );
void   __vf OVCUAPI  MUcuCols_min( uVector Y, uPMatrix MA, ui ht, ui len );
unsigned  __vf OVCUAPI  MUcuDia_min(  uPMatrix MA, ui len );

void  __vf OVCUAPI  MUcuRows_rotate( uPMatrix MA, ui ht, ui len, ssize_t pos );
void  __vf OVCUAPI  MUcuCols_rotate( uPMatrix MA, ui ht, ui len, ssize_t pos );
void  __vf OVCUAPI  MUcuRows_rotate_buf( uPMatrix MA, ui ht, ui len, ssize_t pos, uPMatrix MBuf );
void  __vf OVCUAPI  MUcuCols_rotate_buf( uPMatrix MA, ui ht, ui len, ssize_t pos, uPMatrix MBuf );
void  __vf OVCUAPI  MUcuRows_reflect( uPMatrix MA, ui ht, ui len );
void  __vf OVCUAPI  MUcuCols_reflect( uPMatrix MA, ui ht, ui len );
void  __vf OVCUAPI  MUcuRows_rev( uPMatrix MA, ui ht, ui len );
void  __vf OVCUAPI  MUcuCols_rev( uPMatrix MA, ui ht, ui len );
void  __vf OVCUAPI  MUcuRows_distribution( uiPMatrix MAbund, uVector Limits, ui nBins, uPMatrix MX, ui ht, ui len, int mode );
void  __vf OVCUAPI  MUcuCols_distribution( uiPMatrix MAbund, uVector Limits, ui nBins, uPMatrix MX, ui ht, ui len, int mode );

/********  Operations involving two rows or two colums of one matrix  *****/

void   __vf OVCUAPI  MUcuRows_exchange( uPMatrix MA, ui ht, ui len, ui i1, ui i2 );
void   __vf OVCUAPI  MUcuCols_exchange( uPMatrix MA, ui ht, ui len, ui i1, ui i2 );


/***************  Transposing and rotating a matrix **********************/

void  __vf OVCUAPI  MUcutranspose( uPMatrix MTr, uPMatrix MA,  ui htTr, ui lenTr );
void  __vf OVCUAPI  MUcurotate90(  uPMatrix MRot, uPMatrix MA, ui htRot, ui lenRot );
#define     MUcurotate180( MRot, MA, htRot, lenRot )  VUcu_rev( MRot, MA, (htRot)*(lenRot) )
void  __vf OVCUAPI  MUcurotate270( uPMatrix MRot, uPMatrix MA, ui htRot, ui lenRot );



#ifdef __cplusplus
} // end of extern "C"
#endif
#endif  /*  __MUSTD_H  */
