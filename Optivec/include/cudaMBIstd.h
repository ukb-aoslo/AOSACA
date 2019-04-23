/*  cudaMBIstd.h

  matrix management functions:
  manipulations on matrices of data type "char" (byte-sized integer)

  This file declares the functions with the name variants 
	cudaMBI_func	(working on matrices in device memory, input type biMatrix, scalar parameters reside on host and are passed by value)
	cusdMBI_func	(as cudaMBI_func except scalar parameters reside on device and are passed by address)
	cudaMBIfunc		(as cudaMBI_func, but input type biPMatrix = biVector = pointer to matrix element[0][0])
	cusdMBIfunc		(as cusdMBI_func, but input type biPMatrix = biVector = pointer to matrix element[0][0])
	MBIcu_func		(working on matrices in host memory, input type biMatrix, scalar parameters on host and passed by value)
	MBIcufunc		(as MBIcu_func, but input type biPMatrix = biVector = pointer to matrix element[0][0])
  where func is the respective function.

   Copyright (c) 1996-2017 by OptiCode - Dr. Martin Sander Software Dev.
  All Rights Reserved.

*/

#if !defined( __CUDAMBISTD_H )
#define __CUDAMBISTD_H
#if !defined( __CUDAMATLIB_H )
#include <cudaMatLib.h>
#endif
#if !defined( __CUDAVBISTD_H )
#include <cudaVBIstd.h>
#endif
#if !defined( __CUDAVBIMATH_H )
#include <cudaVBImath.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif

/**** Generation of matrices on device memory and on pinned host memory *******************/

biMatrix  __vf cudaMBI_matrix( ui ht, ui len );   /* allocates a vector on device memory */
biMatrix  __vf cudaMBI_matrix0( ui ht, ui len );
 /* The following functions allocate device-accessible, "pinned" memory on the host.
	This memory is mapped onto the device memory space. The resulting device address is returned.
	The matrix can be accessed either by its host address "hostPtr" e.g., MBI_equ1( hostPtr, ht, len );
	or by its device address , e.g., cudaMBI_equ1( devicePtr, ht, len );                             */
biMatrix  __vf cudaMBI_pinnedMatrix(  biMatrix *hostPtr, ui ht, ui len ); 
biMatrix  __vf cudaMBI_pinnedMatrix0( biMatrix *hostPtr, ui ht, ui len );


/*************************************************************************
 * Declarations of the functions written without underbar in the prefix: *
 *	cudaMBIfunc  (input type 
                   biPMatrix = biVector = pointer to matrix element[0][0])
 *	cusdMBIfunc  (input type 
                   biPMatrix = biVector = pointer to matrix element[0][0])
 *************************************************************************/

void  __vcuf OVCUAPI  cudaMBIsetElement( biPMatrix X, ui ht, ui len, ui m, ui n, char C );
void  __vcuf OVCUAPI  cusdMBIsetElement( biPMatrix X, ui ht, ui len, ui m, ui n, char *d_C );
void  __vcuf OVCUAPI  cudaMBIgetElement( char *h_y, biPMatrix X, ui ht, ui len, ui m, ui n );
void  __vcuf OVCUAPI  cusdMBIgetElement( char *d_y, biPMatrix X, ui ht, ui len, ui m, ui n );
char  __vcuf OVCUAPI  cudaMBIelement( biPMatrix X, ui ht, ui len, ui m, ui n );
char * __vcuf OVCUAPI cudaMBIPelement( biPMatrix X, ui ht, ui len, ui m, ui n );

#define cudaMBIequ0( MA, ht, len )            cudaVBI_equ0( MA, (ht)*(len) )
overror_t   __vcuf OVCUAPI  cudaMBIequ1( biPMatrix MA, ui len );  /* identity matrix */
overror_t   __vcuf OVCUAPI  cudaMBIequm1( biPMatrix MA, ui len );  /* neg. identity matrix */
overror_t   __vcuf OVCUAPI  cudaMBIouterprod( biPMatrix MA, biVector X,  biVector Y, ui ht, ui len );

overror_t   __vcuf OVCUAPI  cudaMBIRow_equ0( biPMatrix MA, ui ht, ui len, ui iRow );
overror_t   __vcuf OVCUAPI  cudaMBICol_equ0( biPMatrix MA, ui ht, ui len, ui iCol );
overror_t   __vcuf OVCUAPI  cudaMBIDia_equ0( biPMatrix MA, ui len );

overror_t   __vcuf OVCUAPI  cudaMBIRow_equC( biPMatrix MA, ui ht, ui len, ui iRow, char C );
overror_t   __vcuf OVCUAPI  cudaMBICol_equC( biPMatrix MA, ui ht, ui len, ui iCol, char C );
overror_t   __vcuf OVCUAPI  cudaMBIDia_equC( biPMatrix MA, ui len, char C );
overror_t   __vcuf OVCUAPI  cusdMBIRow_equC( biPMatrix MA, ui ht, ui len, ui iRow, char *d_C );
overror_t   __vcuf OVCUAPI  cusdMBICol_equC( biPMatrix MA, ui ht, ui len, ui iCol, char *d_C );
overror_t   __vcuf OVCUAPI  cusdMBIDia_equC( biPMatrix MA, ui len, char *d_C );

overror_t   __vcuf OVCUAPI  cudaMBIRow_equV( biPMatrix MA, ui ht, ui len, ui iRow, biVector X );
overror_t   __vcuf OVCUAPI  cudaMBICol_equV( biPMatrix MA, ui ht, ui len, ui iCol, biVector X );
overror_t   __vcuf OVCUAPI  cudaMBIDia_equV( biPMatrix MA, ui len, biVector X );

overror_t   __vcuf OVCUAPI  cudaMBITrd_equM( biPMatrix MA, biPMatrix MTrd, ui len );
overror_t   __vcuf OVCUAPI  cudaMBITrd_extract( biPMatrix MTrd, biPMatrix MA, ui len );

#define cudaMBIequM( MB, MA, ht, len )         cudaVBI_equV( MB, MA, (ht)*(len) )
#define cudaMBIequMhost( d_MB, h_MA, ht, len ) cudaVBI_equVhost( d_MB, h_MA, (ht)*(len) )
#define MBIequMdevice( h_MB, d_MA, ht, len )   VBI_equVdevice( h_MB, d_MA, (ht)*(len) )
#define cudaMBIneg( MB, MA, ht, len )          cudaVBI_neg( MB, MA, (ht)*(len) )
overror_t   __vcuf OVCUAPI  cudaMBIUequL( biPMatrix MA, ui len );
overror_t   __vcuf OVCUAPI  cudaMBILequU( biPMatrix MA, ui len );

            /* data-type conversions:  */
#define cudaMBItoUB( MUB, MBI, ht, len ) cudaV_BItoUB( (MUB), (MBI), (ht)*(len) )
#define cudaMUBtoBI( MBI, MUB, ht, len ) cudaV_UBtoBI( (MBI), (MUB), (ht)*(len) )
#define cudaMBItoSI( MSI, MBI, ht, len ) cudaV_BItoSI( (MSI), (MBI), (ht)*(len) )
#define cudaMBItoI(  MI,  MBI, ht, len ) cudaV_BItoI(  (MI),  (MBI), (ht)*(len) )
#define cudaMBItoLI( MLI, MBI, ht, len ) cudaV_BItoLI( (MLI), (MBI), (ht)*(len) )
#define cudaMBItoQI( MQI, MBI, ht, len ) cudaV_BItoQI( (MQI), (MBI), (ht)*(len) )
#define cudaMSItoBI( MBI, MSI, ht, len ) cudaV_SItoBI( (MBI), (MSI), (ht)*(len) )
#define cudaMItoBI(  MBI, MI,  ht, len ) cudaV_ItoBI(  (MBI), (MI),  (ht)*(len) )
#define cudaMLItoBI( MBI, MLI, ht, len ) cudaV_LItoBI( (MBI), (MLI), (ht)*(len) )
#define cudaMQItoBI( MBI, MQI, ht, len ) cudaV_QItoBI( (MBI), (MQI), (ht)*(len) )
#define cudaMBItoF(  MF,  MBI, ht, len ) cudaV_BItoF(  (MF),  (MBI), (ht)*(len) )
#define cudaMBItoD(  MD,  MBI, ht, len ) cudaV_BItoD(  (MD),  (MBI), (ht)*(len) )

/********  Extracting a submatrix and copying a submatrix back  *********/

overror_t  __vcuf OVCUAPI  cudaMBIsubmatrix( biPMatrix MSub, ui subHt,  ui subLen,
                          biPMatrix MSrce, ui srceHt,  ui srceLen,
                          ui firstRowInCol,  ui sampInCol,
                          ui firstColInRow,  ui sampInRow );

overror_t  __vcuf OVCUAPI  cudaMBIsubmatrix_equM( biPMatrix MDest, ui destHt, ui destLen,
                               ui firstRowInCol,  ui sampInCol,
                               ui firstColInRow,  ui sampInRow,
                               biPMatrix MSrce,  ui srceHt, ui srceLen );

overror_t  __vcuf OVCUAPI  cudaMBIequMblock(  biPMatrix MSub,  ui subHt,  ui subLen,
                          biPMatrix MSrce, ui srceHt,  ui srceLen,
                          ui firstRowInCol,  ui firstColInRow );

overror_t  __vcuf OVCUAPI  cudaMBIblock_equM( biPMatrix MDest,  ui destHt,  ui destLen,
                          ui firstRowInCol,  ui firstColInRow,
                          biPMatrix MSrce,  ui srceHt, ui srceLen );

overror_t  __vcuf OVCUAPI  cudaMBIequMblockT( biPMatrix MSub,  ui subHt, ui subLen,
                          biPMatrix MSrce,  ui srceHt,  ui srceLen,
                          ui firstRowInCol,  ui firstColInRow );

overror_t  __vcuf OVCUAPI  cudaMBIblock_equMT( biPMatrix MDest,  ui destHt,  ui destLen,
                          ui firstRowInCol,  ui firstColInRow,
                          biPMatrix MSrce,   ui srceHt,  ui srceLen );


/*****   Extracting a single row or a single column or the diagonal  *****
 *       and storing it into a vector                                    */

overror_t __vcuf OVCUAPI  cudaMBIRow_extract( biVector Y, biPMatrix MA, ui ht, ui len, ui iRow );
overror_t __vcuf OVCUAPI  cudaMBICol_extract( biVector Y, biPMatrix MA, ui ht, ui len, ui iCol );
overror_t __vcuf OVCUAPI  cudaMBIDia_extract( biVector Y, biPMatrix MA, ui len );


/**********  Deleting or inserting a row or a column *****************/

overror_t __vcuf OVCUAPI  cudaMBIRow_delete( biPMatrix MB, biPMatrix MA, ui htA, ui lenA, ui iRow );
overror_t __vcuf OVCUAPI  cudaMBICol_delete( biPMatrix MB, biPMatrix MA, ui htA, ui lenA, ui iCol );
overror_t __vcuf OVCUAPI  cudaMBIRow_insert( biPMatrix MB, biPMatrix MA, ui htB, ui lenB, ui iRow, biVector X );
overror_t __vcuf OVCUAPI  cudaMBICol_insert( biPMatrix MB, biPMatrix MA, ui htB, ui lenB, ui iCol, biVector X );


/******  One-dimensional vector operations **********************
         performed achar all rows or all columns simultaneously,
         or achar the diagonal of a square matrix                */

overror_t  __vcuf OVCUAPI  cudaMBIRows_max( biVector Y, biPMatrix MA, ui ht, ui len );
overror_t  __vcuf OVCUAPI  cudaMBICols_max( biVector Y, biPMatrix MA, ui ht, ui len );
overror_t  __vcuf OVCUAPI  cudaMBIDia_max(  char *h_RetVal, biPMatrix MA, ui len );
overror_t  __vcuf OVCUAPI  cusdMBIDia_max(  char *d_RetVal, biPMatrix MA, ui len );
overror_t  __vcuf OVCUAPI  cudaMBIRows_min( biVector Y, biPMatrix MA, ui ht, ui len );
overror_t  __vcuf OVCUAPI  cudaMBICols_min( biVector Y, biPMatrix MA, ui ht, ui len );
overror_t  __vcuf OVCUAPI  cudaMBIDia_min(  char *h_RetVal, biPMatrix MA, ui len );
overror_t  __vcuf OVCUAPI  cusdMBIDia_min(  char *d_RetVal, biPMatrix MA, ui len );

overror_t  __vcuf OVCUAPI  cudaMBIRows_rotate( biPMatrix MA, ui ht, ui len, ssize_t pos );
overror_t  __vcuf OVCUAPI  cudaMBICols_rotate( biPMatrix MA, ui ht, ui len, ssize_t pos );
overror_t  __vcuf OVCUAPI  cudaMBIRows_rotate_buf( biPMatrix MA, ui ht, ui len, ssize_t pos, biPMatrix MBuf );
overror_t  __vcuf OVCUAPI  cudaMBICols_rotate_buf( biPMatrix MA, ui ht, ui len, ssize_t pos, biPMatrix MBuf );
overror_t  __vcuf OVCUAPI  cudaMBIRows_reflect( biPMatrix MA, ui ht, ui len );
overror_t  __vcuf OVCUAPI  cudaMBICols_reflect( biPMatrix MA, ui ht, ui len );
overror_t  __vcuf OVCUAPI  cudaMBIRows_rev( biPMatrix MA, ui ht, ui len );
overror_t  __vcuf OVCUAPI  cudaMBICols_rev( biPMatrix MA, ui ht, ui len );
overror_t  __vcuf OVCUAPI  cudaMBIRows_distribution( uiPMatrix MAbund, biVector Limits, ui nBins, biPMatrix MX, ui ht, ui len, int mode );
overror_t  __vcuf OVCUAPI  cudaMBICols_distribution( uiPMatrix MAbund, biVector Limits, ui nBins, biPMatrix MX, ui ht, ui len, int mode );

/********  Operations involving two rows or two colums of one matrix  *****/

overror_t   __vcuf OVCUAPI  cudaMBIRows_exchange( biPMatrix MA, ui ht, ui len, ui i1, ui i2 );
overror_t   __vcuf OVCUAPI  cudaMBICols_exchange( biPMatrix MA, ui ht, ui len, ui i1, ui i2 );

/*****************  Transposing and rotating a matrix **********************/

overror_t  __vcuf OVCUAPI  cudaMBItranspose( biPMatrix MTr, biPMatrix MA, ui htTr, ui lenTr );
#define     cudaMBIrotate180( MRot, MA, htRot, lenRot )  cudaVBI_rev( MRot, MA, (htRot)*(lenRot) )
overror_t  __vcuf OVCUAPI  cudaMBIrotate90(  biPMatrix MRot, biPMatrix MA, ui htRot, ui lenRot );
overror_t  __vcuf OVCUAPI  cudaMBIrotate270( biPMatrix MRot, biPMatrix MA, ui htRot, ui lenRot );
overror_t  __vcuf OVCUAPI  cudaMBItranspose_buf( biPMatrix MTr, biPMatrix MA, ui htTr, ui lenTr, biPMatrix MBuf );

/**************************  Input and Output  **************************
	The input/output functions involve memory transfers from device
	to host memory or vice versa. The generic cudaMBI_input/output functions
	allocate their own host buffers, whereas the cudaMBI_xxx_buf functions
	take a user-supplied buffer vector h_Wk (size must be >= ht*len )
	and are much more efficient.                                       */

#define cudaMBIprint( MA, ht, len )  cudaMBIfprint( stdout, MA, ht, len, 80 )
overror_t __vf cudaMBIfprint( FILE *stream, biPMatrix MA, ui ht, ui len, unsigned linewidth );
overror_t __vf cudaMBIcprint( biPMatrix MA, ui ht, ui len );
#define cudaMBIprint_buf( MA, ht, len, h_Wk )  cudaMBIfprint_buf( stdout, MA, ht, len, 80, h_Wk )
overror_t __vf cudaMBIfprint_buf( FILE *stream, biPMatrix MA, ui ht, ui len, unsigned linewidth, biVector h_Wk );
overror_t __vf cudaMBIcprint_buf( biPMatrix MA, ui ht, ui len, biVector h_Wk );
overror_t __vf cudaMBIwrite( FILE *stream, biPMatrix X, ui ht, ui len  );
overror_t __vf cudaMBIread( biPMatrix X, ui ht, ui len, FILE *stream );
overror_t __vf cudaMBIwrite_buf( FILE *stream, biPMatrix X, ui ht, ui len, biVector h_Wk );
overror_t __vf cudaMBIread_buf( biPMatrix X, ui ht, ui len, FILE *stream, biVector h_Wk );
#define cudaMBIstore( str, MA, ht, len ) cudaVBI_store( str, MA, (len)*(ht) )
#define cudaMBIrecall( MA, ht, len, str) cudaVBI_recall( MA, (len)*(ht), str)
#define cudaMBIstore_buf( str, MA, ht, len, h_Wk ) cudaVBI_store_buf( str, MA, (len)*(ht), h_Wk )
#define cudaMBIrecall_buf( MA, ht, len, str, h_Wk) cudaVBI_recall_buf( MA, (len)*(ht), str, h_Wk)



/***************************************************************************
    cudaMBI_func	(working on matrices in device memory, input type biMatrix, 
	             scalar parameters reside on host and are passed by value)
    cusdMBI_func	(as cudaMBI_func except scalar parameters reside on device 
	             and are passed by address)                                 */


/***************************************************************************
 *  The following definitions are needed to access individual elements,    *
 *  and row pointers. As all addresses point to device memory, the usual   *
 *  mechanism of accessing elements, i.e., writing something like MA[m][n] *
 *  is not possible here!                                                  *
 *  Pro forma, the distinction between the data types biMatrix and         *
 *  biPMatrix is kept. However, in the present implementation, both of     *
 *  these types actually contain a pointer to the matrix element [0][0].   *
 *  For C++, inline functions ensure proper type checking at compile time, *
 *  while for plain-C, only a less safe type-cast is possible.             *
 ***************************************************************************/

#ifdef __cplusplus

inline void    cudaMBI_setElement( biMatrix MA, ui ht, ui len, ui m, ui n, char C )
	{	cudaMBIsetElement( (biPMatrix)(MA), ht, len, m, n, C );}
inline void    cusdMBI_setElement( biMatrix MA, ui ht, ui len, ui m, ui n, char *d_C )
	{	cusdMBIsetElement( (biPMatrix)(MA), ht, len, m, n, d_C );}
inline void    cudaMBI_getElement( char *y, biMatrix MA, ui ht, ui len, ui m, ui n )
	{	cudaMBIgetElement( y, (biPMatrix)(MA), ht, len, m, n );}
inline void    cusdMBI_getElement( char *d_y, biMatrix MA, ui ht, ui len, ui m, ui n )
	{	cusdMBIgetElement( d_y, (biPMatrix)(MA), ht, len, m, n );}
inline char * cudaMBI_Pelement( biMatrix MA, ui ht, ui len, ui m, ui n )
	{	return cudaMBIPelement( (biPMatrix)(MA), ht, len, m, n );}
inline char   cudaMBI_element( biMatrix MA, ui ht, ui len, ui m, ui n )
{	return cudaMBIelement( (biPMatrix)(MA), ht, len, m, n );}

inline overror_t  cudaMBI_equ0( biMatrix MA, ui ht, ui len )
	{	return cudaVBI_equ0( (biPMatrix)MA, (ht)*(len) ); }
inline overror_t  cudaMBI_equ1( biMatrix MA, ui len )
	{	return cudaMBIequ1( (biPMatrix)(MA), len );} /* identity matrix */
inline overror_t  cudaMBI_equm1( biMatrix MA, ui len )
	{	return cudaMBIequm1( (biPMatrix)(MA), len );} /* neg. identity matrix */

inline overror_t  cudaMBI_randomLC( biMatrix MA, ui ht, ui len, long seed, char MinVal, char MaxVal, V_RANDOMLCSTATE *h_state )
	{	return cudaVBI_randomLC( (biPMatrix)(MA), (ht)*(len), seed, MinVal, MaxVal, h_state );}
inline overror_t  cudaMBI_random( biMatrix MA, ui ht, ui len, long seed, char MinVal, char MaxVal )
	{	return cudaVBI_random( (biPMatrix)(MA), (ht)*(len), seed, MinVal, MaxVal );}
inline overror_t  cusdMBI_randomLC( biMatrix MA, ui ht, ui len, long seed, char *d_MinVal, char *d_MaxVal, V_RANDOMLCSTATE *h_state )
	{	return cusdVBI_randomLC( (biPMatrix)(MA), (ht)*(len), seed, d_MinVal, d_MaxVal, h_state );}
inline overror_t  cusdMBI_random( biMatrix MA, ui ht, ui len, long seed, char *d_MinVal, char *d_MaxVal )
	{	return cusdVBI_random( (biPMatrix)(MA), (ht)*(len), seed, d_MinVal, d_MaxVal );}
inline overror_t  cudaMBI_outerprod( biMatrix MA, biVector X,  biVector Y, ui ht, ui len )
{	return cudaMBIouterprod( (biPMatrix)(MA), X, Y, ht, len );}

inline overror_t  cudaMBI_Row_equ0( biMatrix MA, ui ht, ui len, ui iRow )
	{	return cudaMBIRow_equ0( (biPMatrix)MA, ht, len, iRow );}
inline overror_t  cudaMBI_Col_equ0( biMatrix MA, ui ht, ui len, ui iRow )
	{	return cudaMBICol_equ0( (biPMatrix)MA, ht, len, iRow );}
inline overror_t  cudaMBI_Dia_equ0( biMatrix MA, ui len )
	{	return cudaMBIDia_equ0( (biPMatrix)(MA), len );}

inline overror_t  cudaMBI_Row_equC( biMatrix MA, ui ht, ui len, ui iRow, char C )
	{	return cudaMBIRow_equC( (biPMatrix)MA, ht, len, iRow, C );}
inline overror_t  cudaMBI_Col_equC( biMatrix MA, ui ht, ui len, ui iRow, char C )
	{	return cudaMBICol_equC( (biPMatrix)MA, ht, len, iRow, C );}
inline overror_t  cudaMBI_Dia_equC( biMatrix MA, ui len, char C )
	{	return cudaMBIDia_equC( (biPMatrix)(MA), len, C );}

inline overror_t  cusdMBI_Row_equC( biMatrix MA, ui ht, ui len, ui iRow, char *d_C )
	{	return cusdMBIRow_equC( (biPMatrix)MA, ht, len, iRow, d_C );}
inline overror_t  cusdMBI_Col_equC( biMatrix MA, ui ht, ui len, ui iRow, char *d_C )
	{	return cusdMBICol_equC( (biPMatrix)MA, ht, len, iRow, d_C );}
inline overror_t  cusdMBI_Dia_equC( biMatrix MA, ui len, char *d_C )
	{	return cusdMBIDia_equC( (biPMatrix)(MA), len, d_C );}

inline overror_t  cudaMBI_Row_equV( biMatrix MA, ui ht, ui len, ui iRow, biVector X )
	{	return cudaMBIRow_equV( (biPMatrix)MA, ht, len, iRow, X );}
inline overror_t  cudaMBI_Col_equV( biMatrix MA, ui ht, ui len, ui iRow, biVector X )
	{	return cudaMBICol_equV( (biPMatrix)MA, ht, len, iRow, X );}
inline overror_t  cudaMBI_Dia_equV( biMatrix MA, ui len, biVector X )
	{	return cudaMBIDia_equV( (biPMatrix)(MA), len, X );}

inline overror_t  cudaMBI_Trd_equM( biMatrix MA, biMatrix MTrd, ui len )
	{	return cudaMBITrd_equM( (biPMatrix)(MA), (biPMatrix)(MTrd), len );}
inline overror_t  cudaMBI_Trd_extract( biMatrix MTrd, biMatrix MA, ui len )
	{	return cudaMBITrd_extract( (biPMatrix)(MTrd), (biPMatrix)(MA), len );}

inline overror_t cudaMBI_equM( biMatrix MB, biMatrix MA, ui ht, ui len )
	{	return cudaVBI_equV( (biPMatrix)MB, (biPMatrix)MA, (ht)*(len) );}
inline overror_t cudaMBI_equMhost( biMatrix d_MB, biMatrix h_MA, ui ht, ui len )
	{	return cudaVBI_equVhost( (biPMatrix)d_MB, (h_MA)[0], (ht)*(len) );}
inline overror_t MBI_equMdevice( biMatrix h_MB, biMatrix d_MA, ui ht, ui len )
	{	return VBI_equVdevice( h_MB[0], (biPMatrix)d_MA, (ht)*(len) );}
inline overror_t cudaMBI_neg( biMatrix MB, biMatrix MA, ui ht, ui len )
	{	return cudaVBI_neg( (biPMatrix)(MB), (biPMatrix)(MA), (ht)*(len) );}
inline overror_t  cudaMBI_UequL( biMatrix MA, ui len )
	{	return cudaMBIUequL( (biPMatrix)(MA), len );}
inline overror_t  cudaMBI_LequU( biMatrix MA, ui len )
	{	return cudaMBILequU( (biPMatrix)(MA), len );}

/************** Data-type interconversions  ****************************/

inline overror_t cudaM_UBtoBI( biMatrix MBI, ubMatrix MUB, ui ht, ui len )
	{	return cudaV_UBtoBI( (biVector)MBI, (ubVector)MUB, (ht)*(len) );}
inline overror_t cudaM_SItoBI( biMatrix MBI, siMatrix MSI, ui ht, ui len )
	{	return cudaV_SItoBI( (biVector)MBI, (siVector)MSI, (ht)*(len) );}
inline overror_t cudaM_ItoBI(  biMatrix MBI, iMatrix MI,  ui ht, ui len )
	{	return cudaV_ItoBI(  (biVector)MBI, (iVector)MI,   (ht)*(len) );}
inline overror_t cudaM_LItoBI( biMatrix MBI, liMatrix MLI, ui ht, ui len )
	{	return cudaV_LItoBI( (biVector)MBI, (liVector)MLI, (ht)*(len) );}
inline overror_t cudaM_QItoBI( biMatrix MBI, qiMatrix MQI, ui ht, ui len )
	{	return cudaV_QItoBI( (biVector)MBI, (qiVector)MQI, (ht)*(len) );}
inline overror_t cudaM_BItoF(  fMatrix MF,  biMatrix MBI, ui ht, ui len )
	{	return cudaV_BItoF(  (fVector)MF,   (biVector)MBI, (ht)*(len) );}
inline overror_t cudaM_BItoD(  dMatrix MD,  biMatrix MBI, ui ht, ui len )
	{	return cudaV_BItoD(  (dVector)MD,   (biVector)MBI, (ht)*(len) );}

/********  Extracting a submatrix and copying a submatrix back  *********/

inline overror_t cudaMBI_submatrix( biMatrix MSub, ui subHt, ui subLen, biMatrix MSrce, ui srceHt, ui srceLen,
                      ui firstRowInCol, ui sampInCol, ui firstColInRow, ui sampInRow )
	{	return cudaMBIsubmatrix(  (biPMatrix)(MSub), subHt, subLen,
		                         (biPMatrix)(MSrce), srceHt, srceLen,
								 firstRowInCol, sampInCol, firstColInRow, sampInRow ); }

inline overror_t cudaMBI_submatrix_equM( biMatrix MDest, ui destHt, ui destLen,
                           ui firstRowInCol, ui sampInCol, ui firstColInRow, ui sampInRow,
                           biMatrix MSrce, ui srceHt, ui srceLen )
	{	return cudaMBIsubmatrix_equM(  (biPMatrix)(MDest), destHt, destLen,
                             firstRowInCol, sampInCol, firstColInRow, sampInRow,
							 (biPMatrix)(MSrce), srceHt, srceLen );}

inline overror_t cudaMBI_equMblock( biMatrix MSub, ui subHt, ui subLen, biMatrix MSrce, ui srceHt, ui srceLen,
                      ui firstRowInCol, ui firstColInRow )
{	return cudaMBIequMblock(  (biPMatrix)(MSub), subHt, subLen,
						   (biPMatrix)(MSrce), srceHt, srceLen, firstRowInCol, firstColInRow );}

inline overror_t cudaMBI_block_equM( biMatrix MDest, ui destHt, ui destLen,
                       ui firstRowInCol, ui firstColInRow,
                       biMatrix MSrce, ui srceHt, ui srceLen )
	{	return cudaMBIblock_equM( (biPMatrix)(MDest), destHt, destLen,
                             firstRowInCol, firstColInRow,
							 (biPMatrix)(MSrce), srceHt, srceLen );}

inline overror_t cudaMBI_equMblockT( biMatrix MSub, ui subHt, ui subLen, biMatrix MSrce, ui srceHt, ui srceLen,
                      ui firstRowInCol, ui firstColInRow )
	{	return cudaMBIequMblockT(  (biPMatrix)(MSub), subHt, subLen,
                             (biPMatrix)(MSrce), srceHt, srceLen,
							 firstRowInCol, firstColInRow );}

inline overror_t cudaMBI_block_equMT( biMatrix MDest, ui destHt, ui destLen,
                       ui firstRowInCol, ui firstColInRow,
                       biMatrix MSrce, ui srceHt, ui srceLen )
	{	return cudaMBIblock_equMT( (biPMatrix)(MDest), destHt, destLen,
                             firstRowInCol, firstColInRow,
							 (biPMatrix)(MSrce), srceHt, srceLen );}

/*****   Extracting a single row or a single column or the diagonal  ******
 *       and storing it into a vector                                     */

inline overror_t cudaMBI_Row_extract( biVector Y, biMatrix MA, ui ht, ui len, ui iRow ) 
	{	return cudaMBIRow_extract( Y, (biPMatrix)(MA), ht, len, iRow );}
inline overror_t cudaMBI_Col_extract( biVector Y, biMatrix MA, ui ht, ui len, ui iCol ) 
	{	return cudaMBICol_extract( Y, (biPMatrix)(MA), ht, len, iCol );}
inline overror_t cudaMBI_Dia_extract( biVector Y, biMatrix MA, ui len )
	{	return cudaMBIDia_extract( Y, (biPMatrix)(MA), len );}

/**************  Deleting or inserting a row or a column   ***************/

inline overror_t cudaMBI_Row_delete( biMatrix MB, biMatrix MA, ui htA, ui lenA, ui iRow )
	{	return cudaMBIRow_delete( (biPMatrix)(MB), (biPMatrix)(MA), htA, lenA, iRow );}
inline overror_t cudaMBI_Col_delete( biMatrix MB, biMatrix MA, ui htA, ui lenA, ui iCol )
	{	return cudaMBICol_delete( (biPMatrix)(MB), (biPMatrix)(MA), htA, lenA, iCol );}
inline overror_t cudaMBI_Row_insert( biMatrix MB, biMatrix MA, ui htB, ui lenB, ui iRow, biVector X )
	{	return cudaMBIRow_insert( (biPMatrix)(MB), (biPMatrix)(MA), htB, lenB, iRow, X );}
inline overror_t cudaMBI_Col_insert( biMatrix MB, biMatrix MA, ui htB, ui lenB, ui iCol, biVector X )
	{	return cudaMBICol_insert( (biPMatrix)(MB), (biPMatrix)(MA), htB, lenB, iCol, X );}


/******  One-dimensional vector operations **********************
         performed along all rows or all columns simultaneously,
         or along the diagonal of a square matrix                */

inline overror_t cudaMBI_Rows_max( biVector Y, biMatrix MA, ui ht, ui len )
	{	return cudaMBIRows_max( Y, (biPMatrix)(MA), ht, len );}
inline overror_t cudaMBI_Cols_max( biVector Y, biMatrix MA, ui ht, ui len )
	{	return cudaMBICols_max( Y, (biPMatrix)(MA), ht, len );}
inline overror_t cudaMBI_Dia_max(  char *h_RetValPtr, biMatrix MA, ui len )
	{	return cudaMBIDia_max(  h_RetValPtr, (biPMatrix)(MA), len );}
inline overror_t cusdMBI_Dia_max(  char *d_RetValPtr, biMatrix MA, ui len )
	{	return cusdMBIDia_max(  d_RetValPtr, (biPMatrix)(MA), len );}
inline overror_t cudaMBI_Rows_min( biVector Y, biMatrix MA, ui ht, ui len )
	{	return cudaMBIRows_min( Y, (biPMatrix)(MA), ht, len );}
inline overror_t cudaMBI_Cols_min( biVector Y, biMatrix MA, ui ht, ui len )
	{	return cudaMBICols_min( Y, (biPMatrix)(MA), ht, len );}
inline overror_t cudaMBI_Dia_min(  char *h_RetValPtr, biMatrix MA, ui len )
	{	return cudaMBIDia_min(  h_RetValPtr, (biPMatrix)(MA), len );}
inline overror_t cusdMBI_Dia_min(  char *d_RetValPtr, biMatrix MA, ui len )
	{	return cusdMBIDia_min(  d_RetValPtr, (biPMatrix)(MA), len );}

inline overror_t cudaMBI_Rows_rotate( biMatrix MA, ui ht, ui len, ssize_t pos)
	{	return cudaMBIRows_rotate( (biPMatrix)(MA), ht, len, pos );}
inline overror_t cudaMBI_Cols_rotate( biMatrix MA, ui ht, ui len, ssize_t pos)
	{	return cudaMBICols_rotate( (biPMatrix)(MA), ht, len, pos );}
inline overror_t cudaMBI_Rows_rotate_buf( biMatrix MA, ui ht, ui len, ssize_t pos, biMatrix MBuf) 
	{	return cudaMBIRows_rotate_buf( (biPMatrix)(MA), ht, len, pos, (biPMatrix)(MBuf) );}
inline overror_t cudaMBI_Cols_rotate_buf( biMatrix MA, ui ht, ui len, ssize_t pos, biMatrix MBuf) 
	{	return cudaMBICols_rotate_buf( (biPMatrix)(MA), ht, len, pos, (biPMatrix)(MBuf) );}
inline overror_t cudaMBI_Rows_reflect( biMatrix MA, ui ht, ui len )
	{	return cudaMBIRows_reflect( (biPMatrix)(MA), ht, len );}
inline overror_t cudaMBI_Cols_reflect( biMatrix MA, ui ht, ui len )
	{	return cudaMBICols_reflect( (biPMatrix)(MA), ht, len );}
inline overror_t cudaMBI_Rows_rev( biMatrix MA, ui ht, ui len )
	{	return cudaMBIRows_rev( (biPMatrix)(MA), ht, len );}
inline overror_t cudaMBI_Cols_rev( biMatrix MA, ui ht, ui len )
	{	return cudaMBICols_rev( (biPMatrix)(MA), ht, len );}
inline overror_t  cudaMBI_Rows_distribution( uiMatrix MAbund, biVector Limits, ui nBins, biMatrix MX, ui ht, ui len, int mode )
	{	return cudaMBIRows_distribution( (uiPMatrix)MAbund, Limits, nBins, (biPMatrix)MX, ht, len, mode ); }
inline overror_t  cudaMBI_Cols_distribution( uiMatrix MAbund, biVector Limits, ui nBins, biMatrix MX, ui ht, ui len, int mode )
	{	return cudaMBICols_distribution( (uiPMatrix)MAbund, Limits, nBins, (biPMatrix)MX, ht, len, mode ); }

/********  Operations involving two rows or two colums of one matrix  *****/

inline overror_t cudaMBI_Rows_exchange( biMatrix MA, ui ht, ui len, ui row1, ui row2 )
	{	return cudaMBIRows_exchange( (biPMatrix)(MA), ht, len, row1, row2 );}
inline overror_t cudaMBI_Cols_exchange( biMatrix MA, ui ht, ui len, ui col1, ui col2 )
	{	return cudaMBICols_exchange( (biPMatrix)(MA), ht, len, col1, col2 );}

/*************** Transposing and rotating a matrix **********************/

inline overror_t cudaMBI_transpose( biMatrix MTr, biMatrix MA, ui htTr, ui lenTr )
	{	return cudaMBItranspose( (biPMatrix)(MTr), (biPMatrix)(MA), htTr, lenTr );}
       /*  dimensions htTr, lenTr are those of the transposed matrix, not of the original!   */
inline overror_t cudaMBI_rotate90( biMatrix MRot, biMatrix MA, ui htRot, ui lenRot )
	{	return cudaMBIrotate90( (biPMatrix)(MRot), (biPMatrix)(MA), htRot, lenRot );}
inline overror_t cudaMBI_rotate180( biMatrix MRot, biMatrix MA, ui htRot, ui lenRot )
	{	return cudaVBI_rev( (biPMatrix)(MRot), (biPMatrix)(MA), (htRot)*(lenRot) );}
inline overror_t cudaMBI_rotate270( biMatrix MRot, biMatrix MA, ui htRot, ui lenRot )
	{	return cudaMBIrotate270( (biPMatrix)(MRot), (biPMatrix)(MA), htRot, lenRot );}
inline overror_t cudaMBI_transpose_buf( biMatrix MTr, biMatrix MA, ui htTr, ui lenTr, biMatrix MBuf )
	{	return cudaMBItranspose_buf( (biPMatrix)(MTr), (biPMatrix)(MA), htTr, lenTr, (biPMatrix)(MBuf) );}

/**************************  Input and Output  **************************
	The input/output functions involve memory transfers from device
	to host memory or vice versa. The generic cudaMBI_input/output functions
	allocate their own host buffers, whereas the cudaMBI_xxx_buf functions
	take a user-supplied buffer vector h_Wk (size must be >= ht*len )
	and are much more efficient.                                       */

inline overror_t cudaMBI_fprint( FILE *stream, biMatrix MA, ui ht, ui len, unsigned linewidth )
	{	return cudaMBIfprint( stream, (biPMatrix)(MA), ht, len, linewidth ); }
inline overror_t cudaMBI_print( biMatrix MA, ui ht, ui len )
	{	return cudaMBIfprint( stdout, (biPMatrix)(MA), ht, len, 80 ); }
inline overror_t cudaMBI_cprint( biMatrix MA, ui ht, ui len )
	{	return cudaMBIcprint( (biPMatrix)(MA), ht, len ); }
inline overror_t cudaMBI_fprint_buf( FILE *stream, biMatrix d_MA, ui ht, ui len, unsigned linewidth, biVector h_Wk )
	{	return cudaMBIfprint_buf( stream, (biPMatrix)(d_MA), ht, len, linewidth, h_Wk ); }
inline overror_t cudaMBI_print_buf( biMatrix d_MA, ui ht, ui len, biVector h_Wk )
	{	return cudaMBIfprint_buf( stdout, (biPMatrix)(d_MA), ht, len, 80, h_Wk ); }
inline overror_t cudaMBI_cprint_buf( biMatrix d_MA, ui ht, ui len, biVector h_Wk )
	{	return cudaMBIcprint_buf( (biPMatrix)(d_MA), ht, len, h_Wk ); }
		/*  cudaMBI_print, cudaMBI_cprint usable only for console applications! */
inline overror_t  cudaMBI_write( FILE *stream, biMatrix MA, ui ht, ui len )
	{	return cudaMBIwrite( stream, (biPMatrix)(MA), ht, len ); }
inline overror_t cudaMBI_read( biMatrix MA, ui ht, ui len, FILE *stream )
	{	return cudaMBIread( (biPMatrix)(MA), ht, len, stream ); }
inline overror_t  cudaMBI_write_buf( FILE *stream, biMatrix d_MA, ui ht, ui len, biVector h_Wk )
	{	return cudaMBIwrite_buf( stream, (biPMatrix)(d_MA), ht, len, h_Wk ); }
inline overror_t cudaMBI_read_buf( biMatrix d_MA, ui ht, ui len, FILE *stream, biVector h_Wk )
	{	return cudaMBIread_buf( (biPMatrix)(d_MA), ht, len, stream, h_Wk ); }
                                   /* write and read in ascii format */
inline overror_t cudaMBI_store( FILE *stream, biMatrix MA, ui ht, ui len )
{	return cudaVBI_store( stream, (biPMatrix)(MA), (len)*(ht) ); }
inline overror_t cudaMBI_recall( biMatrix MA, ui ht, ui len, FILE *stream )
	{	return cudaVBI_recall( (biPMatrix)(MA), (len)*(ht), stream ); }
inline overror_t cudaMBI_store_buf( FILE *stream, biMatrix d_MA, ui ht, ui len, biVector h_Wk )
{	return cudaVBI_store_buf( stream, (biPMatrix)(d_MA), (len)*(ht), h_Wk ); }
inline overror_t cudaMBI_recall_buf( biMatrix d_MA, ui ht, ui len, FILE *stream, biVector h_Wk )
	{	return cudaVBI_recall_buf( (biPMatrix)(d_MA), (len)*(ht), stream, h_Wk ); }
                                  /* store and recall in binary format */

#else  /* plain-C, not C++: type-cast used to transform biMatrix into biPMatrix   */

/***  Addressing single elements of dynamically allocated matrices: ******/

#define cudaMBI_setElement( MA, ht, len, m, n, C ) cudaMBIsetElement( (biPMatrix)(MA), ht, len, m, n, C )
#define cusdMBI_setElement( MA, ht, len, m, n, C ) cusdMBIsetElement( (biPMatrix)(MA), ht, len, m, n, C )
#define cudaMBI_getElement( y, MA, ht, len, m, n ) cudaMBIgetElement( y, (biPMatrix)(MA), ht, len, m, n )
#define cusdMBI_getElement( y, MA, ht, len, m, n ) cusdMBIgetElement( y, (biPMatrix)(MA), ht, len, m, n )
#define cudaMBI_Pelement( MA, ht, len, m, n )      cudaMBIPelement( (biPMatrix)(MA), ht, len, m, n )
                     /* returns a pointer to MA[m][n]. */
#define cudaMBI_element( MA, ht, len, m, n )       cudaMBIelement( (biPMatrix)(MA), ht, len, m, n )

 /****************  Initialization  ***************************************

    To initialize all elements of a matrix with the same value,
    or to perform arithmetic operations on all elements simultaneously,
    refer to the functions of VectorLib.
    In order to use the VectorLib functions, utilize the feature that
    the whole matrix occupies one contiguous area in memory: pass the
    address of the first element to the desired vector function, the size
    of the "vector" being ht * len.
    For example, initialize all elements of the matrix MA with 1.0
    (this is *NOT* the identity matrix)  by calling
        VBI_equ1( (biVector)MA, ht * len );
*/

#define cudaMBI_equ0( MA, ht, len )            cudaVBI_equ0( (biPMatrix)(MA), (ht)*(len) )
#define cudaMBI_equ1( MA, len )                cudaMBIequ1( (biPMatrix)(MA), len ) /* identity matrix */
#define cudaMBI_equm1( MA, len )               cudaMBIequm1( (biPMatrix)(MA), len ) /* neg. identity matrix */
#define cudaMBI_randomLC( MA, ht, len, seed, Min, Max, h_state )      cudaVBI_randomLC( MA, (ht)*(len), seed, Min, Max, h_state )
#define cudaMBI_random( MA, ht, len, seed, Min, Max )                 cudaVBI_random( MA, (ht)*(len), seed, Min, Max )
#define cusdMBI_randomLC( MA, ht, len, seed, d_Min, d_Max, h_state )  cudaVBI_randomLC( MA, (ht)*(len), seed, d_Min, d_Max, h_state )
#define cusdMBI_random( MA, ht, len, seed, d_Min, d_Max )             cudaVBI_random( MA, (ht)*(len), seed, d_Min, d_Max )
#define cudaMBI_outerprod( MA, X, Y, ht, len ) cudaMBIouterprod( (biPMatrix)(MA), X, Y, ht, len )
                       /* sizX=ht, sizY=len */
#define cudaMBI_Row_equ0( MA, ht, len, iRow )  cudaMBIRow_equ0( (biPMatrix)(MA), ht, len, iRow )
#define cudaMBI_Col_equ0( MA, ht, len, iCol )  cudaMBICol_equ0( (biPMatrix)(MA), ht, len, iCol )
#define cudaMBI_Dia_equ0( MA, len )            cudaMBIDia_equ0( (biPMatrix)(MA), len )
#define cudaMBI_Row_equC( MA, ht, len, iRow, C ) cudaMBIRow_equC( (biPMatrix)(MA), ht, len, iRow, C )
#define cudaMBI_Col_equC( MA, ht, len, iCol, C ) cudaMBICol_equC( (biPMatrix)(MA), ht, len, iCol, C )
#define cudaMBI_Dia_equC( MA, len, C )           cudaMBIDia_equC( (biPMatrix)(MA), len, C )
#define cusdMBI_Row_equC( MA, ht, len, iRow, d_C ) cusdMBIRow_equC( (biPMatrix)(MA), ht, len, iRow, d_C )
#define cusdMBI_Col_equC( MA, ht, len, iCol, d_C ) cusdMBICol_equC( (biPMatrix)(MA), ht, len, iCol, d_C )
#define cusdMBI_Dia_equC( MA, len, d_C )           cusdMBIDia_equC( (biPMatrix)(MA), len, d_C )

#define cudaMBI_Row_equV( MA, ht, len, iRow, X ) cudaMBIRow_equV( (biPMatrix)(MA), ht, len, iRow, X )
#define cudaMBI_Col_equV( MA, ht, len, iCol, X ) cudaMBICol_equV( (biPMatrix)(MA), ht, len, iCol, X )
#define cudaMBI_Dia_equV( MA, len, X )           cudaMBIDia_equV( (biPMatrix)(MA), len, X )

#define cudaMBI_Trd_equM( MA, MTrd, len )    cudaMBITrd_equM( (biPMatrix)(MA), (biPMatrix)(MTr)d, len )
#define cudaMBI_Trd_extract( MTrd, MA, len ) cudaMBITrd_extract( (biPMatrix)(MTr)d, (biPMatrix)(MA), len )

#define cudaMBI_equM( MB, MA, ht, len )      cudaVBI_equV( (biPMatrix)(MB), (biPMatrix)(MA), (ht)*(len) )
#define cudaMBI_equMhost( MB, MA, ht, len )  cudaVBI_equVhost( (biPMatrix)(MB), MA[0], (ht)*(len) )
#define MBI_equMdevice( MB, MA, ht, len )    VBI_equVdevice( MB[0], (biPMatrix)(MA), (ht)*(len) )
#define cudaMBI_neg( MB, MA, ht, len )       cudaVBI_neg( (biPMatrix)(MB), (biPMatrix)(MA), (ht)*(len) )

#define cudaMBI_UequL( MA, len ) cudaMBIUequL( (biPMatrix)(MA), len )
#define cudaMBI_LequU( MA, len ) cudaMBILequU( (biPMatrix)(MA), len )


/************** Data-type interconversions  ****************************/

#define cudaM_BItoUB( MUB, MBI, ht, len ) cudaV_BItoUB( (ubVector)(MUB), (biVector)(MBI), (ht)*(len) )
#define cudaM_UBtoBI( MBI, MUB, ht, len ) cudaV_UBtoBI( (biVector)(MBI), (ubVector)(MUB), (ht)*(len) )
#define cudaM_BItoSI( MSI, MBI, ht, len ) cudaV_BItoSI( (siVector)(MSI), (biVector)(MBI), (ht)*(len) )
#define cudaM_BItoI(  MI,  MBI, ht, len ) cudaV_BItoI(  (iVector)(MI),   (biVector)(MBI), (ht)*(len) )
#define cudaM_BItoLI( MLI, MBI, ht, len ) cudaV_BItoLI( (liVector)(MLI), (biVector)(MBI), (ht)*(len) )
#define cudaM_BItoQI( MQI, MBI, ht, len ) cudaV_BItoQI( (qiVector)(MQI), (biVector)(MBI), (ht)*(len) )
#define cudaM_SItoBI( MBI, MSI, ht, len ) cudaV_SItoBI( (biVector)(MBI), (siVector)(MSI), (ht)*(len) )
#define cudaM_ItoBI(  MBI, MI,  ht, len ) cudaV_ItoBI(  (biVector)(MBI), (iVector)(MI),   (ht)*(len) )
#define cudaM_LItoBI( MBI, MLI, ht, len ) cudaV_LItoBI( (biVector)(MBI), (liVector)(MLI), (ht)*(len) )
#define cudaM_QItoBI( MBI, MQI, ht, len ) cudaV_QItoBI( (biVector)(MBI), (qiVector)(MQI), (ht)*(len) )
#define cudaM_BItoF(  MF,  MBI, ht, len ) cudaV_BItoF(  (fVector)(MF),   (biVector)(MBI), (ht)*(len) )
#define cudaM_BItoD(  MD,  MBI, ht, len ) cudaV_BItoD(  (dVector)(MD),   (biVector)(MBI), (ht)*(len) )

/********  Extracting a submatrix and copying a submatrix back  *********/

#define cudaMBI_submatrix( MSub, subHt, subLen, MSrce, srceHt, srceLen, \
                      firstRowInCol, sampInCol, firstColInRow, sampInRow ) \
               cudaMBIsubmatrix(  (biPMatrix)(MSub), subHt, subLen, \
                             (biPMatrix)(MSrce), srceHt, srceLen, \
                             firstRowInCol, sampInCol, firstColInRow, sampInRow )

#define cudaMBI_submatrix_equM( MDest, destHt, destLen, \
                           firstRowInCol, sampInCol, firstColInRow, sampInRow, \
                           MSrce, srceHt, srceLen ) \
               cudaMBIsubmatrix_equM(  (biPMatrix)(MDest), destHt, destLen, \
                             firstRowInCol, sampInCol, firstColInRow, sampInRow, \
                             (biPMatrix)(MSrce), srceHt, srceLen )

#define cudaMBI_equMblock( MSub, subHt, subLen, \
                      MSrce, srceHt, srceLen, \
                      firstRowInCol, firstColInRow ) \
               cudaMBIequMblock(  (biPMatrix)(MSub), subHt, subLen, \
                             (biPMatrix)(MSrce), srceHt, srceLen, \
                             firstRowInCol, firstColInRow )

#define cudaMBI_block_equM( MDest, destHt, destLen, \
                       firstRowInCol, firstColInRow, \
                       MSrce, srceHt, srceLen ) \
               cudaMBIblock_equM( (biPMatrix)(MDest), destHt, destLen, \
                             firstRowInCol, firstColInRow, \
                             (biPMatrix)(MSrce), srceHt, srceLen )

#define cudaMBI_equMblockT( MSub, subHt, subLen, \
                      MSrce, srceHt, srceLen, \
                      firstRowInCol, firstColInRow ) \
               cudaMBIequMblockT(  (biPMatrix)(MSub), subHt, subLen, \
                             (biPMatrix)(MSrce), srceHt, srceLen, \
                             firstRowInCol, firstColInRow )

#define cudaMBI_block_equMT( MDest, destHt, destLen, \
                       firstRowInCol, firstColInRow, \
                       MSrce, srceHt, srceLen ) \
               cudaMBIblock_equMT( (biPMatrix)(MDest), destHt, destLen, \
                             firstRowInCol, firstColInRow, \
                             (biPMatrix)(MSrce), srceHt, srceLen )

/*****   Extracting a single row or a single column or the diagonal  ******
 *       and storing it into a vector                                     */

#define cudaMBI_Row_extract( Y, MA, ht, len, iRow ) \
                                     cudaMBIRow_extract( Y, (biPMatrix)(MA), ht, len, iRow )
#define cudaMBI_Col_extract( Y, MA, ht, len, iCol ) \
                                     cudaMBICol_extract( Y, (biPMatrix)(MA), ht, len, iCol )
#define cudaMBI_Dia_extract( Y, MA, len ) cudaMBIDia_extract( Y, (biPMatrix)(MA), len )


/**************  Deleting or inserting a row or a column   ***************/

#define cudaMBI_Row_delete( MB, MA, htA, lenA, iRow ) \
                           cudaMBIRow_delete( (biPMatrix)(MB), (biPMatrix)(MA), htA, lenA, iRow )
#define cudaMBI_Col_delete( MB, MA, htA, lenA, iCol ) \
                           cudaMBICol_delete( (biPMatrix)(MB), (biPMatrix)(MA), htA, lenA, iCol )
#define cudaMBI_Row_insert( MB, MA, htB, lenB, iRow, X ) \
                           cudaMBIRow_insert( (biPMatrix)(MB), (biPMatrix)(MA), htB, lenB, iRow, X )
#define cudaMBI_Col_insert( MB, MA, htB, lenB, iCol, X ) \
                           cudaMBICol_insert( (biPMatrix)(MB), (biPMatrix)(MA), htB, lenB, iCol, X )

/******  One-dimensional vector operations **********************
         performed achar all rows or all columns simultaneously,
         or achar the diagonal of a square matrix                */

#define cudaMBI_Rows_max( Y, MA, ht, len )     cudaMBIRows_max( Y, (biPMatrix)(MA), ht, len )
#define cudaMBI_Cols_max( Y, MA, ht, len )     cudaMBICols_max( Y, (biPMatrix)(MA), ht, len )
#define cudaMBI_Dia_max(  h_RetPtr, MA, len )  cudaMBIDia_max( h_RetPtr, (biPMatrix)(MA), len )
#define cusdMBI_Dia_max(  d_RetPtr, MA, len )  cusdMBIDia_max( d_RetPtr, (biPMatrix)(MA), len )
#define cudaMBI_Rows_min( Y, MA, ht, len )     cudaMBIRows_min( Y, (biPMatrix)(MA), ht, len )
#define cudaMBI_Cols_min( Y, MA, ht, len )     cudaMBICols_min( Y, (biPMatrix)(MA), ht, len )
#define cudaMBI_Dia_min(  h_RetPtr, MA, len )  cudaMBIDia_min( h_RetPtr, (biPMatrix)(MA), len )
#define cusdMBI_Dia_min(  d_RetPtr, MA, len )  cusdMBIDia_min( d_RetPtr, (biPMatrix)(MA), len )

#define cudaMBI_Rows_rotate( MA, ht, len, pos) cudaMBIRows_rotate( (biPMatrix)(MA), ht, len, pos )
#define cudaMBI_Cols_rotate( MA, ht, len, pos) cudaMBICols_rotate( (biPMatrix)(MA), ht, len, pos )
#define cudaMBI_Rows_rotate_buf( MA, ht, len, pos, MBuf) cudaMBIRows_rotate_buf( (biPMatrix)(MA), ht, len, pos, (biPMatrix)(MBuf) )
#define cudaMBI_Cols_rotate_buf( MA, ht, len, pos, MBuf) cudaMBICols_rotate_buf( (biPMatrix)(MA), ht, len, pos, (biPMatrix)(MBuf) )
#define cudaMBI_Rows_reflect( MA, ht, len)     cudaMBIRows_reflect( (biPMatrix)(MA), ht, len )
#define cudaMBI_Cols_reflect( MA, ht, len)     cudaMBICols_reflect( (biPMatrix)(MA), ht, len )
#define cudaMBI_Rows_rev( MA, ht, len)         cudaMBIRows_rev( (biPMatrix)(MA), ht, len )
#define cudaMBI_Cols_rev( MA, ht, len)         cudaMBICols_rev( (biPMatrix)(MA), ht, len )
#define cudaMBI_Rows_distribution( MAbund, Limits, nBins, MX, ht, len, mode ) cudaMBIRows_distribution( (uiPMatrix)MAbund, Limits, nBins, (biPMatrix)MX, ht, len, mode )
#define cudaMBI_Cols_distribution( MAbund, Limits, nBins, MX, ht, len, mode ) cudaMBICols_distribution( (uiPMatrix)MAbund, Limits, nBins, (biPMatrix)MX, ht, len, mode )

/********  Operations involving two rows or two colums of one matrix  *****/

#define cudaMBI_Rows_exchange( MA, ht, len, row1, row2 ) \
                             cudaMBIRows_exchange( (biPMatrix)(MA), ht, len, row1, row2 )
#define cudaMBI_Cols_exchange( MA, ht, len, col1, col2 ) \
                             cudaMBICols_exchange( (biPMatrix)(MA), ht, len, col1, col2 )

/************  Transposing and rotating a matrix **********************/

#define cudaMBI_transpose( MTr, MA, htTr, lenTr ) \
             cudaMBItranspose( (biPMatrix)(MTr), (biPMatrix)(MA), htTr, lenTr )
       /*  dimensions htTr, lenTr are those of the transposed matrix,
           not of the original!                */
#define cudaMBI_rotate90( MRot, MA, htRot, lenRot ) \
             cudaMBIrotate90( (biPMatrix)(MRot), (biPMatrix)(MA), htRot, lenRot )
#define cudaMBI_rotate180( MRot, MA, htRot, lenRot ) \
             cudaVBI_rev( (biPMatrix)(MRot), (biPMatrix)(MA), (htRot)*(lenRot) )
#define cudaMBI_rotate270( MRot, MA, htRot, lenRot ) \
             cudaMBIrotate270( (biPMatrix)(MRot), (biPMatrix)(MA), htRot, lenRot )
#define cudaMBI_transpose_buf( MTr, MA, htTr, lenTr, MBuf ) \
             cudaMBItranspose( (biPMatrix)(MTr), (biPMatrix)(MA), htTr, lenTr, (biPMatrix)(MBuf) )

/**************************  Input and Output  **************************
	The input/output functions involve memory transfers from device
	to host memory or vice versa. The generic cudaMBI_input/output functions
	allocate their own host buffers, whereas the cudaMBI_xxx_buf functions
	take a user-supplied buffer vector h_Wk (size must be >= ht*len )
	and are much more efficient.                                       */

#define cudaMBI_fprint( stream, MA, ht, len, linewidth ) \
                    cudaMBIfprint( stream, (biPMatrix)(MA), ht, len, linewidth )
#define cudaMBI_print( MA, ht, len )  cudaMBIfprint( stdout, (biPMatrix)(MA), ht, len, 80 )
#define cudaMBI_cprint( MA, ht, len ) cudaMBIcprint( (biPMatrix)(MA), ht, len )
#define cudaMBI_fprint_buf( stream, MA, ht, len, linewidth, h_Wk ) \
                    cudaMBIfprint_buf( stream, (biPMatrix)(MA), ht, len, linewidth, h_Wk )
#define cudaMBI_print_buf( MA, ht, len )  cudaMBIfprint_buf( stdout, (biPMatrix)(MA), ht, len, 80, h_Wk )
#define cudaMBI_cprint_buf( MA, ht, len ) cudaMBIcprint_buf( (biPMatrix)(MA), ht, len, h_Wk )
  /*  cudaMBI_print, cudaMBI_cprint usable only for console applications! */
#define cudaMBI_write( str, MA, ht, len )   cudaMBIwrite( str, (biPMatrix)(MA), ht, len )
#define cudaMBI_read( MA, ht, len, str )    cudaMBIread( (biPMatrix)(MA), ht, len, str )
#define cudaMBI_write_buf( str, MA, ht, len, h_Wk )   cudaMBIwrite_buf( str, (biPMatrix)(MA), ht, len, h_Wk )
#define cudaMBI_read_buf( MA, ht, len, str, h_Wk )    cudaMBIread_buf( (biPMatrix)(MA), ht, len, str, h_Wk )
                                   /* write and read in ascii format */
#define cudaMBI_store( str, MA, ht, len )   cudaVBI_store( str, (biPMatrix)(MA), (len)*(ht) )
#define cudaMBI_recall( MA, ht, len, str)   cudaVBI_recall( (biPMatrix)(MA), (len)*(ht), str)
#define cudaMBI_store_buf( str, MA, ht, len, h_Wk )   cudaVBI_store_buf( str, (biPMatrix)(MA), (len)*(ht), h_Wk )
#define cudaMBI_recall_buf( MA, ht, len, str, h_Wk)   cudaVBI_recall_buf( (biPMatrix)(MA), (len)*(ht), str, h_Wk )
                                  /* store and recall in binary format */

#endif /* plain-C or C++ for functions working on device memory  */


/*******************  Functions working on host memory: **********************
 *                                                                           *
 *	MBIcu_func		(working on matrices in host memory, input type biMatrix,*
 *	scalar parameters on host and passed by value)                           *
 *****************************************************************************/ 

/****************  Initialization  ****************************************/

#define MBIcu_equ0( MA, ht, len )                   VBIcu_equ0( (MA)[0], (ht)*(len) )
#define MBIcu_equ1( MA, len )                       MBIcuequ1( (MA)[0], len ) /* identity matrix */
#define MBIcu_equm1( MA, len )                      MBIcuequm1( (MA)[0], len ) /* neg. identity matrix */
#define MBIcu_randomLC( MA, ht, len, seed, Min, Max, state ) VBIcu_randomLC( (MA)[0], (ht)*(len), seed, Min, Max, state )
#define MBIcu_random( MA, ht, len, seed, Min, Max )          VBIcu_random( (MA)[0], (ht)*(len), seed, Min, Max )
#define MBIcu_outerprod( MA, X, Y, ht, len )        MBIcuouterprod( (MA)[0], X, Y, ht, len )
                       /* sizX=ht, sizY=len */
#define MBIcu_Row_equ0( MA, ht, len, iRow )    MBIcuRow_equ0( (MA)[0], ht, len, iRow )
#define MBIcu_Col_equ0( MA, ht, len, iCol )    MBIcuCol_equ0( (MA)[0], ht, len, iCol )
#define MBIcu_Dia_equ0( MA, len )              MBIcuDia_equ0( (MA)[0], len )
#define MBIcu_Row_equC( MA, ht, len, iRow, C ) MBIcuRow_equC( (MA)[0], ht, len, iRow, C )
#define MBIcu_Col_equC( MA, ht, len, iCol, C ) MBIcuCol_equC( (MA)[0], ht, len, iCol, C )
#define MBIcu_Dia_equC( MA, len, C )           MBIcuDia_equC( (MA)[0], len, C )

#define MBIcu_Row_equV( MA, ht, len, iRow, X ) MBIcuRow_equV( (MA)[0], ht, len, iRow, X )
#define MBIcu_Col_equV( MA, ht, len, iCol, X ) MBIcuCol_equV( (MA)[0], ht, len, iCol, X )
#define MBIcu_Dia_equV( MA, len, X )           MBIcuDia_equV( (MA)[0], len, X )

#define MBIcu_Trd_equM( MA, MTrd, len )        MBIcuTrd_equM( (MA)[0], (MTrd)[0], len )
#define MBIcu_Trd_extract( MTrd, MA, len )     MBIcuTrd_extract( (MTrd)[0], (MA)[0], len )

#define MBIcu_equM( MB, MA, ht, len )          VBIcu_equV( (MB)[0], (MA)[0], (ht)*(len) )
#define MBIcu_equMhost( MB, MA, ht, len )      VBIcu_equVhost( (MB)[0], MA[0], (ht)*(len) )
#define MBIcu_neg( MB, MA, ht, len )           VBIcu_neg( (MB)[0], (MA)[0], (ht)*(len) )

#define MBIcu_UequL( MA, len ) MBIcuUequL( (MA)[0], len )
#define MBIcu_LequU( MA, len ) MBIcuLequU( (MA)[0], len )
     /* copy lower-diagonal elements into upper-diagonal
       (or vice versa) by index-reflection, so as to get a symmetric matrix    */

            /* data-type conversions:  */
#define Mcu_BItoUB( MUB, MBI, ht, len ) Vcu_BItoUB( (MUB)[0], (MBI)[0], (ht)*(len) )
#define Mcu_UBtoBI( MBI, MUB, ht, len ) Vcu_UBtoBI( (MBI)[0], (MUB)[0], (ht)*(len) )
#define Mcu_BItoSI( MSI, MBI, ht, len ) Vcu_BItoSI( (MSI)[0], (MBI)[0], (ht)*(len) )
#define Mcu_BItoI(  MI,  MBI, ht, len ) Vcu_BItoI(  (MI)[0],  (MBI)[0], (ht)*(len) )
#define Mcu_BItoLI( MLI, MBI, ht, len ) Vcu_BItoLI( (MLI)[0], (MBI)[0], (ht)*(len) )
#define Mcu_BItoQI( MQI, MBI, ht, len ) Vcu_BItoQI( (MQI)[0], (MBI)[0], (ht)*(len) )
#define Mcu_SItoBI( MBI, MSI, ht, len ) Vcu_SItoBI( (MBI)[0], (MSI)[0], (ht)*(len) )
#define Mcu_ItoBI(  MBI, MI,  ht, len ) Vcu_ItoBI(  (MBI)[0], (MI)[0],  (ht)*(len) )
#define Mcu_LItoBI( MBI, MLI, ht, len ) Vcu_LItoBI( (MBI)[0], (MLI)[0], (ht)*(len) )
#define Mcu_QItoBI( MBI, MQI, ht, len ) Vcu_QItoBI( (MBI)[0], (MQI)[0], (ht)*(len) )
#define Mcu_BItoF(  MF,  MBI, ht, len ) Vcu_BItoF(  (MF)[0],  (MBI)[0], (ht)*(len) )
#define Mcu_BItoD(  MD,  MBI, ht, len ) Vcu_BItoD(  (MD)[0],  (MBI)[0], (ht)*(len) )


/********  Extracting a submatrix and copying a submatrix back  *********/

#define MBIcu_submatrix( MSub, subHt, subLen, MSrce, srceHt, srceLen, \
                      firstRowInCol, sampInCol, firstColInRow, sampInRow ) \
               MBIcusubmatrix(  (MSub)[0], subHt, subLen, \
                             (MSrce)[0], srceHt, srceLen, \
                             firstRowInCol, sampInCol, firstColInRow, sampInRow )

#define MBIcu_submatrix_equM( MDest, destHt, destLen, \
                           firstRowInCol, sampInCol, firstColInRow, sampInRow, \
                           MSrce, srceHt, srceLen ) \
               MBIcusubmatrix_equM(  (MDest)[0], destHt, destLen, \
                             firstRowInCol, sampInCol, firstColInRow, sampInRow, \
                             (MSrce)[0], srceHt, srceLen )

#define MBIcu_equMblock( MSub, subHt, subLen, MSrce, srceHt, srceLen, \
                      firstRowInCol, firstColInRow ) \
               MBIcuequMblock(  (MSub)[0], subHt, subLen, \
                             (MSrce)[0], srceHt, srceLen, \
                             firstRowInCol, firstColInRow )

#define MBIcu_block_equM( MDest, destHt, destLen, \
                       firstRowInCol, firstColInRow, \
                       MSrce, srceHt, srceLen ) \
               MBIcublock_equM( (MDest)[0], destHt, destLen, \
                             firstRowInCol, firstColInRow, \
                             (MSrce)[0], srceHt, srceLen )

#define MBIcu_equMblockT( MSub, subHt, subLen, MSrce, srceHt, srceLen, \
                      firstRowInCol, firstColInRow ) \
               MBIcuequMblockT(  (MSub)[0], subHt, subLen, \
                             (MSrce)[0], srceHt, srceLen, \
                             firstRowInCol, firstColInRow )

#define MBIcu_block_equMT( MDest, destHt, destLen, \
                       firstRowInCol, firstColInRow, \
                       MSrce, srceHt, srceLen ) \
               MBIcublock_equMT( (MDest)[0], destHt, destLen, \
                             firstRowInCol, firstColInRow, \
                             (MSrce)[0], srceHt, srceLen )

/*****   Extracting a single row or a single column or the diagonal  ******
 *       and storing it into a vector                                     */

#define MBIcu_Row_extract( Y, MA, ht, len, iRow ) MBIcuRow_extract( Y, (MA)[0], ht, len, iRow )
#define MBIcu_Col_extract( Y, MA, ht, len, iCol ) MBIcuCol_extract( Y, (MA)[0], ht, len, iCol )
#define MBIcu_Dia_extract( Y, MA, len )           MBIcuDia_extract( Y, (MA)[0], len )

/**************  Deleting or inserting a row or a column   ***************/

#define MBIcu_Row_delete( MB, MA, htA, lenA, iRow )    MBIcuRow_delete( (MB)[0], (MA)[0], htA, lenA, iRow )
#define MBIcu_Col_delete( MB, MA, htA, lenA, iCol )    MBIcuCol_delete( (MB)[0], (MA)[0], htA, lenA, iCol )
#define MBIcu_Row_insert( MB, MA, htB, lenB, iRow, X ) MBIcuRow_insert( (MB)[0], (MA)[0], htB, lenB, iRow, X )
#define MBIcu_Col_insert( MB, MA, htB, lenB, iCol, X ) MBIcuCol_insert( (MB)[0], (MA)[0], htB, lenB, iCol, X )


/*****************    Basic arithmetic operations *********************
                      performed on one single row,
                      or one single column of any matrix,
                      or on the diagonal of a square matrix

    Note: In contrast to the analogous VectorLib functions, the operations
    are performed in-place, i.e. the input matrix itself is changed  */

#define MBIcu_Row_neg( MA, ht, len, iRow ) MBIcuRow_neg( (MA)[0], ht, len, iRow )
#define MBIcu_Col_neg( MA, ht, len, iCol ) MBIcuCol_neg( (MA)[0], ht, len, iCol )

/******  One-dimensional vector operations **********************
         performed along all rows or all columns simultaneously,
         or along the diagonal of a square matrix                */

#define MBIcu_Rows_max( Y, MA, ht, len )        MBIcuRows_max( Y, (MA)[0], ht, len )
#define MBIcu_Cols_max( Y, MA, ht, len )        MBIcuCols_max( Y, (MA)[0], ht, len )
#define MBIcu_Dia_max(  MA, len )               MBIcuDia_max(  (MA)[0], len )
#define MBIcu_Rows_min( Y, MA, ht, len )        MBIcuRows_min( Y, (MA)[0], ht, len )
#define MBIcu_Cols_min( Y, MA, ht, len )        MBIcuCols_min( Y, (MA)[0], ht, len )
#define MBIcu_Dia_min(  MA, len )               MBIcuDia_min(  (MA)[0], len )

#define MBIcu_Rows_rotate( MA, ht, len, pos)           MBIcuRows_rotate( (MA)[0], ht, len, pos )
#define MBIcu_Cols_rotate( MA, ht, len, pos)           MBIcuCols_rotate( (MA)[0], ht, len, pos )
#define MBIcu_Rows_rotate_buf( MA, ht, len, pos, MBuf) MBIcuRows_rotate_buf( (MA)[0], ht, len, pos, (MBuf)[0] )
#define MBIcu_Cols_rotate_buf( MA, ht, len, pos, MBuf) MBIcuCols_rotate_buf( (MA)[0], ht, len, pos, (MBuf)[0] )
#define MBIcu_Rows_reflect( MA, ht, len )              MBIcuRows_reflect( (MA)[0], ht, len )
#define MBIcu_Cols_reflect( MA, ht, len )              MBIcuCols_reflect( (MA)[0], ht, len )
#define MBIcu_Rows_rev( MA, ht, len)                   MBIcuRows_rev( (MA)[0], ht, len )
#define MBIcu_Cols_rev( MA, ht, len)                   MBIcuCols_rev( (MA)[0], ht, len )
#define MBIcu_Rows_distribution( MAbund, Limits, nBins, MX, ht, len, mode ) MBIcuRows_distribution( MAbund[0], Limits, nBins, MX[0], ht, len, mode )
#define MBIcu_Cols_distribution( MAbund, Limits, nBins, MX, ht, len, mode ) MBIcuCols_distribution( MAbund[0], Limits, nBins, MX[0], ht, len, mode )

/********  Operations involving two rows or two colums of one matrix  *****/

#define MBIcu_Rows_exchange( MA, ht, len, row1, row2 ) \
                             MBIcuRows_exchange( (MA)[0], ht, len, row1, row2 )
#define MBIcu_Cols_exchange( MA, ht, len, col1, col2 ) \
                             MBIcuCols_exchange( (MA)[0], ht, len, col1, col2 )

/*************** Transposing and rotating a matrix **********************/

#define MBIcu_transpose( MTr, MA, htTr, lenTr )    MBIcutranspose( (MTr)[0], (MA)[0], htTr, lenTr )
       /*  dimensions htTr, lenTr are those of the transposed matrix, not of the original!   */
#define MBIcu_rotate90( MRot, MA, htRot, lenRot )  MBIcurotate90( (MRot)[0], (MA)[0], htRot, lenRot )
#define MBIcu_rotate180( MRot, MA, htRot, lenRot ) VBIcu_rev( (MRot)[0], (MA)[0], (htRot)*(lenRot) )
#define MBIcu_rotate270( MRot, MA, htRot, lenRot ) MBIcurotate270( (MRot)[0], (MA)[0], htRot, lenRot )


/*************************************************************************
 * MBIcu functions (without underbar in the prefix): 	
    (working on matrices in host memory, input type 
	biPMatrix = biVector = pointer to matrix element[0][0], 
	scalar parameters on host and passed by value)
*
 *************************************************************************/

#define MBIcuequ0( MA, ht, len )       VBIcu_equ0( MA, (ht)*(len) )
void   __vf OVCUAPI  MBIcuequ1( biPMatrix MA, ui len );  /* identity matrix */
void   __vf OVCUAPI  MBIcuequm1( biPMatrix MA, ui len );  /* neg. identity matrix */
void   __vf OVCUAPI  MBIcuouterprod( biPMatrix MA, biVector X,  biVector Y, ui ht, ui len );

void   __vf OVCUAPI  MBIcuRow_equ0( biPMatrix MA, ui ht, ui len, ui iRow );
void   __vf OVCUAPI  MBIcuCol_equ0( biPMatrix MA, ui ht, ui len, ui iCol );
void   __vf OVCUAPI  MBIcuDia_equ0( biPMatrix MA, ui len );

void   __vf OVCUAPI  MBIcuRow_equC( biPMatrix MA, ui ht, ui len, ui iRow, char C );
void   __vf OVCUAPI  MBIcuCol_equC( biPMatrix MA, ui ht, ui len, ui iCol, char C );
void   __vf OVCUAPI  MBIcuDia_equC( biPMatrix MA, ui len, char C );

void   __vf OVCUAPI  MBIcuRow_equV( biPMatrix MA, ui ht, ui len, ui iRow, biVector X );
void   __vf OVCUAPI  MBIcuCol_equV( biPMatrix MA, ui ht, ui len, ui iCol, biVector X );
void   __vf OVCUAPI  MBIcuDia_equV( biPMatrix MA, ui len, biVector X );

void   __vf OVCUAPI  MBIcuTrd_equM( biPMatrix MA, biPMatrix MTrd, ui len );
void   __vf OVCUAPI  MBIcuTrd_extract( biPMatrix MTrd, biPMatrix MA, ui len );

#define MBIcuequM( MB, MA, ht, len )      VBIcu_equV( MB, MA, (ht)*(len) )
#define MBIcuneg( MB, MA, ht, len )       VBIcu_neg( MB, MA, (ht)*(len) )
void   __vf OVCUAPI  MBIcuUequL( biPMatrix MA, ui len );
void   __vf OVCUAPI  MBIcuLequU( biPMatrix MA, ui len );

            /* data-type conversions:  */
#define McuBItoUB( MUB, MBI, ht, len ) Vcu_BItoUB( MUB, MBI, (ht)*(len) )
#define McuUBtoBI( MBI, MUB, ht, len ) Vcu_UBtoBI( MBI, MUB, (ht)*(len) )
#define McuBItoSI( MSI, MBI, ht, len ) Vcu_BItoSI( MSI, MBI, (ht)*(len) )
#define McuBItoI(  MI,  MBI, ht, len ) Vcu_BItoI(  MI,  MBI, (ht)*(len) )
#define McuBItoLI( MLI, MBI, ht, len ) Vcu_BItoLI( MLI, MBI, (ht)*(len) )
#define McuBItoQI( MQI, MBI, ht, len ) Vcu_BItoQI( MQI, MBI, (ht)*(len) )
#define McuSItoBI( MBI, MSI, ht, len ) Vcu_SItoBI( MBI, MSI, (ht)*(len) )
#define McuItoBI(  MBI, MI,  ht, len ) Vcu_ItoBI(  MBI, MI,  (ht)*(len) )
#define McuLItoBI( MBI, MLI, ht, len ) Vcu_LItoBI( MBI, MLI, (ht)*(len) )
#define McuQItoBI( MBI, MQI, ht, len ) Vcu_QItoBI( MBI, MQI, (ht)*(len) )
#define McuBItoF(  MF,  MBI, ht, len ) Vcu_BItoF(  MF,  MBI, (ht)*(len) )
#define McuBItoD(  MD,  MBI, ht, len ) Vcu_BItoD(  MD,  MBI, (ht)*(len) )

/********  Extracting a submatrix and copying a submatrix back  *********/

void  __vf OVCUAPI  MBIcusubmatrix( biPMatrix MSub, ui subHt,  ui subLen,
                          biPMatrix MSrce, ui srceHt,  ui srceLen,
                          ui firstRowInCol,  ui sampInCol,
                          ui firstColInRow,  ui sampInRow );

void  __vf OVCUAPI  MBIcusubmatrix_equM( biPMatrix MDest, ui destHt, ui destLen,
                               ui firstRowInCol,  ui sampInCol,
                               ui firstColInRow,  ui sampInRow,
                               biPMatrix MSrce, ui srceHt, ui srceLen );

void  __vf OVCUAPI  MBIcuequMblock(  biPMatrix MSub, ui subHt, ui subLen,
                          biPMatrix MSrce, ui srceHt,  ui srceLen,
                          ui firstRowInCol,  ui firstColInRow );

void  __vf OVCUAPI  MBIcublock_equM( biPMatrix MDest, ui destHt, ui destLen,
                          ui firstRowInCol,  ui firstColInRow,
                          biPMatrix MSrce, ui srceHt, ui srceLen );

void  __vf OVCUAPI  MBIcuequMblockT( biPMatrix MSub, ui subHt, ui subLen,
                          biPMatrix MSrce, ui srceHt, ui srceLen,
                          ui firstRowInCol,  ui firstColInRow );

void  __vf OVCUAPI  MBIcublock_equMT( biPMatrix MDest, ui destHt, ui destLen,
                          ui firstRowInCol,  ui firstColInRow,
                          biPMatrix MSrce, ui srceHt, ui srceLen );


/*****   Extracting a single row or a single column or the diagonal  *****
 *       and storing it into a vector                                    */

void __vf OVCUAPI  MBIcuRow_extract( biVector Y, biPMatrix MA, ui ht, ui len, ui iRow );
void __vf OVCUAPI  MBIcuCol_extract( biVector Y, biPMatrix MA, ui ht, ui len, ui iCol );
void __vf OVCUAPI  MBIcuDia_extract( biVector Y, biPMatrix MA, ui len );

/**********  Deleting or inserting a row or a column *****************/

void __vf OVCUAPI  MBIcuRow_delete( biPMatrix MB, biPMatrix MA, ui htA, ui lenA, ui iRow );
void __vf OVCUAPI  MBIcuCol_delete( biPMatrix MB, biPMatrix MA, ui htA, ui lenA, ui iCol );
void __vf OVCUAPI  MBIcuRow_insert( biPMatrix MB, biPMatrix MA, ui htB, ui lenB, ui iRow, biVector X );
void __vf OVCUAPI  MBIcuCol_insert( biPMatrix MB, biPMatrix MA, ui htB, ui lenB, ui iCol, biVector X );


/******  One-dimensional vector operations **********************
         performed along all rows or all columns simultaneously,
         or along the diagonal of a square matrix                */

void   __vf OVCUAPI  MBIcuRows_max( biVector Y, biPMatrix MA, ui ht, ui len );
void   __vf OVCUAPI  MBIcuCols_max( biVector Y, biPMatrix MA, ui ht, ui len );
char  __vf OVCUAPI  MBIcuDia_max(  biPMatrix MA, ui len );
void   __vf OVCUAPI  MBIcuRows_min( biVector Y, biPMatrix MA, ui ht, ui len );
void   __vf OVCUAPI  MBIcuCols_min( biVector Y, biPMatrix MA, ui ht, ui len );
char  __vf OVCUAPI  MBIcuDia_min(  biPMatrix MA, ui len );

void  __vf OVCUAPI  MBIcuRows_rotate( biPMatrix MA, ui ht, ui len, ssize_t pos );
void  __vf OVCUAPI  MBIcuCols_rotate( biPMatrix MA, ui ht, ui len, ssize_t pos );
void  __vf OVCUAPI  MBIcuRows_rotate_buf( biPMatrix MA, ui ht, ui len, ssize_t pos, biPMatrix MBuf );
void  __vf OVCUAPI  MBIcuCols_rotate_buf( biPMatrix MA, ui ht, ui len, ssize_t pos, biPMatrix MBuf );
void  __vf OVCUAPI  MBIcuRows_reflect( biPMatrix MA, ui ht, ui len );
void  __vf OVCUAPI  MBIcuCols_reflect( biPMatrix MA, ui ht, ui len );
void  __vf OVCUAPI  MBIcuRows_rev( biPMatrix MA, ui ht, ui len );
void  __vf OVCUAPI  MBIcuCols_rev( biPMatrix MA, ui ht, ui len );
void  __vf OVCUAPI  MBIcuRows_distribution( uiPMatrix MAbund, biVector Limits, ui nBins, biPMatrix MX, ui ht, ui len, int mode );
void  __vf OVCUAPI  MBIcuCols_distribution( uiPMatrix MAbund, biVector Limits, ui nBins, biPMatrix MX, ui ht, ui len, int mode );

/********  Operations involving two rows or two colums of one matrix  *****/

void   __vf OVCUAPI  MBIcuRows_exchange( biPMatrix MA, ui ht, ui len, ui i1, ui i2 );
void   __vf OVCUAPI  MBIcuCols_exchange( biPMatrix MA, ui ht, ui len, ui i1, ui i2 );


/***************  Transposing and rotating a matrix **********************/

void  __vf OVCUAPI  MBIcutranspose( biPMatrix MTr, biPMatrix MA,  ui htTr, ui lenTr );
void  __vf OVCUAPI  MBIcurotate90(  biPMatrix MRot, biPMatrix MA, ui htRot, ui lenRot );
#define     MBIcurotate180( MRot, MA, htRot, lenRot )  VBIcu_rev( MRot, MA, (htRot)*(lenRot) )
void  __vf OVCUAPI  MBIcurotate270( biPMatrix MRot, biPMatrix MA, ui htRot, ui lenRot );

#ifdef __cplusplus
} // end of extern "C"
#endif
#endif  /*  __MBISTD_H  */
