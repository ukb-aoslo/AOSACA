/*  cudaMLIstd.h

  matrix management functions:
  manipulations on matrices of data type "long" (32-bit integer)

  This file declares the functions with the name variants 
	cudaMLI_func	(working on matrices in device memory, input type liMatrix, scalar parameters reside on host and are passed by value)
	cusdMLI_func	(as cudaMLI_func except scalar parameters reside on device and are passed by address)
	cudaMLIfunc		(as cudaMLI_func, but input type liPMatrix = liVector = pointer to matrix element[0][0])
	cusdMLIfunc		(as cusdMLI_func, but input type liPMatrix = liVector = pointer to matrix element[0][0])
	MLIcu_func		(working on matrices in host memory, input type liMatrix, scalar parameters on host and passed by value)
	MLIcufunc		(as MLIcu_func, but input type liPMatrix = liVector = pointer to matrix element[0][0])
  where func is the respective function.

   Copyright (c) 1996-2017 by OptiCode - Dr. Martin Sander Software Dev.
  All Rights Reserved.

*/

#if !defined( __CUDAMLISTD_H )
#define __CUDAMLISTD_H
#if !defined( __CUDAMATLIB_H )
#include <cudaMatLib.h>
#endif
#if !defined( __CUDAVLISTD_H )
#include <cudaVLIstd.h>
#endif
#if !defined( __CUDAVLIMATH_H )
#include <cudaVLImath.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif

/**** Generation of matrices on device memory and on pinned host memory *******************/

liMatrix  __vf cudaMLI_matrix( ui ht, ui len );   /* allocates a vector on device memory */
liMatrix  __vf cudaMLI_matrix0( ui ht, ui len );
 /* The following functions allocate device-accessible, "pinned" memory on the host.
	This memory is mapped onto the device memory space. The resulting device address is returned.
	The matrix can be accessed either by its host address "hostPtr" e.g., MLI_equ1( hostPtr, ht, len );
	or by its device address , e.g., cudaMLI_equ1( devicePtr, ht, len );                             */
liMatrix  __vf cudaMLI_pinnedMatrix(  liMatrix *hostPtr, ui ht, ui len ); 
liMatrix  __vf cudaMLI_pinnedMatrix0( liMatrix *hostPtr, ui ht, ui len );

/*************************************************************************
 * Declarations of the functions written without underbar in the prefix: *
 *	cudaMLIfunc  (input type 
                   liPMatrix = liVector = pointer to matrix element[0][0])
 *	cusdMLIfunc  (input type 
                   liPMatrix = liVector = pointer to matrix element[0][0])
 *************************************************************************/

void  __vcuf OVCUAPI  cudaMLIsetElement( liPMatrix X, ui ht, ui len, ui m, ui n, long C );
void  __vcuf OVCUAPI  cusdMLIsetElement( liPMatrix X, ui ht, ui len, ui m, ui n, long *d_C );
void  __vcuf OVCUAPI  cudaMLIgetElement( long *h_y, liPMatrix X, ui ht, ui len, ui m, ui n );
void  __vcuf OVCUAPI  cusdMLIgetElement( long *d_y, liPMatrix X, ui ht, ui len, ui m, ui n );
long  __vcuf OVCUAPI  cudaMLIelement( liPMatrix X, ui ht, ui len, ui m, ui n );
long * __vcuf OVCUAPI cudaMLIPelement( liPMatrix X, ui ht, ui len, ui m, ui n );

#define cudaMLIequ0( MA, ht, len )            cudaVLI_equ0( MA, (ht)*(len) )
overror_t   __vcuf OVCUAPI  cudaMLIequ1( liPMatrix MA, ui len );  /* identity matrix */
overror_t   __vcuf OVCUAPI  cudaMLIequm1( liPMatrix MA, ui len );  /* neg. identity matrix */
overror_t   __vcuf OVCUAPI  cudaMLIouterprod( liPMatrix MA, liVector X,  liVector Y, ui ht, ui len );

overror_t   __vcuf OVCUAPI  cudaMLIRow_equ0( liPMatrix MA, ui ht, ui len, ui iRow );
overror_t   __vcuf OVCUAPI  cudaMLICol_equ0( liPMatrix MA, ui ht, ui len, ui iCol );
overror_t   __vcuf OVCUAPI  cudaMLIDia_equ0( liPMatrix MA, ui len );

overror_t   __vcuf OVCUAPI  cudaMLIRow_equC( liPMatrix MA, ui ht, ui len, ui iRow, long C );
overror_t   __vcuf OVCUAPI  cudaMLICol_equC( liPMatrix MA, ui ht, ui len, ui iCol, long C );
overror_t   __vcuf OVCUAPI  cudaMLIDia_equC( liPMatrix MA, ui len, long C );
overror_t   __vcuf OVCUAPI  cusdMLIRow_equC( liPMatrix MA, ui ht, ui len, ui iRow, long *d_C );
overror_t   __vcuf OVCUAPI  cusdMLICol_equC( liPMatrix MA, ui ht, ui len, ui iCol, long *d_C );
overror_t   __vcuf OVCUAPI  cusdMLIDia_equC( liPMatrix MA, ui len, long *d_C );

overror_t   __vcuf OVCUAPI  cudaMLIRow_equV( liPMatrix MA, ui ht, ui len, ui iRow, liVector X );
overror_t   __vcuf OVCUAPI  cudaMLICol_equV( liPMatrix MA, ui ht, ui len, ui iCol, liVector X );
overror_t   __vcuf OVCUAPI  cudaMLIDia_equV( liPMatrix MA, ui len, liVector X );

overror_t   __vcuf OVCUAPI  cudaMLITrd_equM( liPMatrix MA, liPMatrix MTrd, ui len );
overror_t   __vcuf OVCUAPI  cudaMLITrd_extract( liPMatrix MTrd, liPMatrix MA, ui len );

#define cudaMLIequM( MB, MA, ht, len )         cudaVLI_equV( MB, MA, (ht)*(len) )
#define cudaMLIequMhost( d_MB, h_MA, ht, len ) cudaVLI_equVhost( d_MB, h_MA, (ht)*(len) )
#define MLIequMdevice( h_MB, d_MA, ht, len )   VLI_equVdevice( h_MB, d_MA, (ht)*(len) )
#define cudaMLIneg( MB, MA, ht, len )          cudaVLI_neg( MB, MA, (ht)*(len) )
overror_t   __vcuf OVCUAPI  cudaMLIUequL( liPMatrix MA, ui len );
overror_t   __vcuf OVCUAPI  cudaMLILequU( liPMatrix MA, ui len );

            /* data-type conversions:  */
#define cudaMLItoUL( MUL, MLI, ht, len ) cudaV_LItoUL( (MUL), (MLI), (ht)*(len) )
#define cudaMULtoLI( MLI, MUL, ht, len ) cudaV_ULtoLI( (MLI), (MUL), (ht)*(len) )
#define cudaMLItoBI( MBI, MLI, ht, len ) cudaV_LItoBI( (MBI), (MLI), (ht)*(len) )
#define cudaMLItoSI( MSI, MLI, ht, len ) cudaV_LItoSI( (MSI), (MLI), (ht)*(len) )
#define cudaMLItoI(  MI,  MLI, ht, len ) cudaV_LItoI(  (MI),  (MLI), (ht)*(len) )
#define cudaMLItoQI( MQI, MLI, ht, len ) cudaV_LItoQI( (MQI), (MLI), (ht)*(len) )
#define cudaMBItoLI( MLI, MBI, ht, len ) cudaV_BItoLI( (MLI), (MBI), (ht)*(len) )
#define cudaMSItoLI( MLI, MSI, ht, len ) cudaV_SItoLI( (MLI), (MSI), (ht)*(len) )
#define cudaMItoLI(  MLI, MI,  ht, len ) cudaV_ItoLI(  (MLI), (MI),  (ht)*(len) )
#define cudaMQItoLI( MLI, MQI, ht, len ) cudaV_QItoLI( (MLI), (MQI), (ht)*(len) )
#define cudaMLItoF(  MF,  MLI, ht, len ) cudaV_LItoF(  (MF),  (MLI), (ht)*(len) )
#define cudaMLItoD(  MD,  MLI, ht, len ) cudaV_LItoD(  (MD),  (MLI), (ht)*(len) )

/********  Extracting a submatrix and copying a submatrix back  *********/

overror_t  __vcuf OVCUAPI  cudaMLIsubmatrix( liPMatrix MSub, ui subHt,  ui subLen,
                          liPMatrix MSrce, ui srceHt,  ui srceLen,
                          ui firstRowInCol,  ui sampInCol,
                          ui firstColInRow,  ui sampInRow );

overror_t  __vcuf OVCUAPI  cudaMLIsubmatrix_equM( liPMatrix MDest, ui destHt, ui destLen,
                               ui firstRowInCol,  ui sampInCol,
                               ui firstColInRow,  ui sampInRow,
                               liPMatrix MSrce,  ui srceHt, ui srceLen );

overror_t  __vcuf OVCUAPI  cudaMLIequMblock(  liPMatrix MSub,  ui subHt,  ui subLen,
                          liPMatrix MSrce, ui srceHt,  ui srceLen,
                          ui firstRowInCol,  ui firstColInRow );

overror_t  __vcuf OVCUAPI  cudaMLIblock_equM( liPMatrix MDest,  ui destHt,  ui destLen,
                          ui firstRowInCol,  ui firstColInRow,
                          liPMatrix MSrce,  ui srceHt, ui srceLen );

overror_t  __vcuf OVCUAPI  cudaMLIequMblockT( liPMatrix MSub,  ui subHt, ui subLen,
                          liPMatrix MSrce,  ui srceHt,  ui srceLen,
                          ui firstRowInCol,  ui firstColInRow );

overror_t  __vcuf OVCUAPI  cudaMLIblock_equMT( liPMatrix MDest,  ui destHt,  ui destLen,
                          ui firstRowInCol,  ui firstColInRow,
                          liPMatrix MSrce,   ui srceHt,  ui srceLen );


/*****   Extracting a single row or a single column or the diagonal  *****
 *       and storing it into a vector                                    */

overror_t __vcuf OVCUAPI  cudaMLIRow_extract( liVector Y, liPMatrix MA, ui ht, ui len, ui iRow );
overror_t __vcuf OVCUAPI  cudaMLICol_extract( liVector Y, liPMatrix MA, ui ht, ui len, ui iCol );
overror_t __vcuf OVCUAPI  cudaMLIDia_extract( liVector Y, liPMatrix MA, ui len );


/**********  Deleting or inserting a row or a column *****************/

overror_t __vcuf OVCUAPI  cudaMLIRow_delete( liPMatrix MB, liPMatrix MA, ui htA, ui lenA, ui iRow );
overror_t __vcuf OVCUAPI  cudaMLICol_delete( liPMatrix MB, liPMatrix MA, ui htA, ui lenA, ui iCol );
overror_t __vcuf OVCUAPI  cudaMLIRow_insert( liPMatrix MB, liPMatrix MA, ui htB, ui lenB, ui iRow, liVector X );
overror_t __vcuf OVCUAPI  cudaMLICol_insert( liPMatrix MB, liPMatrix MA, ui htB, ui lenB, ui iCol, liVector X );


/******  One-dimensional vector operations **********************
         performed along all rows or all columns simultaneously,
         or along the diagonal of a square matrix                */

overror_t  __vcuf OVCUAPI  cudaMLIRows_max( liVector Y, liPMatrix MA, ui ht, ui len );
overror_t  __vcuf OVCUAPI  cudaMLICols_max( liVector Y, liPMatrix MA, ui ht, ui len );
overror_t  __vcuf OVCUAPI  cudaMLIDia_max(  long *h_RetVal, liPMatrix MA, ui len );
overror_t  __vcuf OVCUAPI  cusdMLIDia_max(  long *d_RetVal, liPMatrix MA, ui len );
overror_t  __vcuf OVCUAPI  cudaMLIRows_min( liVector Y, liPMatrix MA, ui ht, ui len );
overror_t  __vcuf OVCUAPI  cudaMLICols_min( liVector Y, liPMatrix MA, ui ht, ui len );
overror_t  __vcuf OVCUAPI  cudaMLIDia_min(  long *h_RetVal, liPMatrix MA, ui len );
overror_t  __vcuf OVCUAPI  cusdMLIDia_min(  long *d_RetVal, liPMatrix MA, ui len );

overror_t  __vcuf OVCUAPI  cudaMLIRows_rotate( liPMatrix MA, ui ht, ui len, ssize_t pos );
overror_t  __vcuf OVCUAPI  cudaMLICols_rotate( liPMatrix MA, ui ht, ui len, ssize_t pos );
overror_t  __vcuf OVCUAPI  cudaMLIRows_rotate_buf( liPMatrix MA, ui ht, ui len, ssize_t pos, liPMatrix MBuf );
overror_t  __vcuf OVCUAPI  cudaMLICols_rotate_buf( liPMatrix MA, ui ht, ui len, ssize_t pos, liPMatrix MBuf );
overror_t  __vcuf OVCUAPI  cudaMLIRows_reflect( liPMatrix MA, ui ht, ui len );
overror_t  __vcuf OVCUAPI  cudaMLICols_reflect( liPMatrix MA, ui ht, ui len );
overror_t  __vcuf OVCUAPI  cudaMLIRows_rev( liPMatrix MA, ui ht, ui len );
overror_t  __vcuf OVCUAPI  cudaMLICols_rev( liPMatrix MA, ui ht, ui len );
overror_t  __vcuf OVCUAPI  cudaMLIRows_distribution( uiPMatrix MAbund, liVector Limits, ui nBins, liPMatrix MX, ui ht, ui len, int mode );
overror_t  __vcuf OVCUAPI  cudaMLICols_distribution( uiPMatrix MAbund, liVector Limits, ui nBins, liPMatrix MX, ui ht, ui len, int mode );

/********  Operations involving two rows or two colums of one matrix  *****/

overror_t   __vcuf OVCUAPI  cudaMLIRows_exchange( liPMatrix MA, ui ht, ui len, ui i1, ui i2 );
overror_t   __vcuf OVCUAPI  cudaMLICols_exchange( liPMatrix MA, ui ht, ui len, ui i1, ui i2 );

/*****************  Transposing and rotating a matrix **********************/

overror_t  __vcuf OVCUAPI  cudaMLItranspose( liPMatrix MTr, liPMatrix MA, ui htTr, ui lenTr );
#define     cudaMLIrotate180( MRot, MA, htRot, lenRot )  cudaVLI_rev( MRot, MA, (htRot)*(lenRot) )
overror_t  __vcuf OVCUAPI  cudaMLIrotate90(  liPMatrix MRot, liPMatrix MA, ui htRot, ui lenRot );
overror_t  __vcuf OVCUAPI  cudaMLIrotate270( liPMatrix MRot, liPMatrix MA, ui htRot, ui lenRot );
overror_t  __vcuf OVCUAPI  cudaMLItranspose_buf( liPMatrix MTr, liPMatrix MA, ui htTr, ui lenTr, liPMatrix MBuf );

/**************************  Input and Output  **************************
	The input/output functions involve memory transfers from device
	to host memory or vice versa. The generic cudaMLI_input/output functions
	allocate their own host buffers, whereas the cudaMLI_xxx_buf functions
	take a user-supplied buffer vector h_Wk (size must be >= ht*len )
	and are much more efficient.                                       */

#define cudaMLIprint( MA, ht, len )  cudaMLIfprint( stdout, MA, ht, len, 80 )
overror_t __vf cudaMLIfprint( FILE *stream, liPMatrix MA, ui ht, ui len, unsigned linewidth );
overror_t __vf cudaMLIcprint( liPMatrix MA, ui ht, ui len );
#define cudaMLIprint_buf( MA, ht, len, h_Wk )  cudaMLIfprint_buf( stdout, MA, ht, len, 80, h_Wk )
overror_t __vf cudaMLIfprint_buf( FILE *stream, liPMatrix MA, ui ht, ui len, unsigned linewidth, liVector h_Wk );
overror_t __vf cudaMLIcprint_buf( liPMatrix MA, ui ht, ui len, liVector h_Wk );
overror_t __vf cudaMLIwrite( FILE *stream, liPMatrix X, ui ht, ui len  );
overror_t __vf cudaMLIread( liPMatrix X, ui ht, ui len, FILE *stream );
overror_t __vf cudaMLIwrite_buf( FILE *stream, liPMatrix X, ui ht, ui len, liVector h_Wk );
overror_t __vf cudaMLIread_buf( liPMatrix X, ui ht, ui len, FILE *stream, liVector h_Wk );
#define cudaMLIstore( str, MA, ht, len ) cudaVLI_store( str, MA, (len)*(ht) )
#define cudaMLIrecall( MA, ht, len, str) cudaVLI_recall( MA, (len)*(ht), str)
#define cudaMLIstore_buf( str, MA, ht, len, h_Wk ) cudaVLI_store( str, MA, (len)*(ht), h_Wk )
#define cudaMLIrecall_buf( MA, ht, len, str, h_Wk) cudaVLI_recall( MA, (len)*(ht), str, h_Wk)



/***************************************************************************
    cudaMLI_func	(working on matrices in device memory, input type liMatrix, 
	             scalar parameters reside on host and are passed by value)
    cusdMLI_func	(as cudaMLI_func except scalar parameters reside on device 
	             and are passed by address)                                 */


/***************************************************************************
 *  The following definitions are needed to access individual elements,    *
 *  and row pointers. As all addresses point to device memory, the usual   *
 *  mechanism of accessing elements, i.e., writing something like MA[m][n] *
 *  is not possible here!                                                  *
 *  Pro forma, the distinction between the data types liMatrix and         *
 *  liPMatrix is kept. However, in the present implementation, both of     *
 *  these types actually contain a pointer to the matrix element [0][0].   *
 *  For C++, inline functions ensure proper type checking at compile time, *
 *  while for plain-C, only a less safe type-cast is possible.             *
 ***************************************************************************/

#ifdef __cplusplus

inline void    cudaMLI_setElement( liMatrix MA, ui ht, ui len, ui m, ui n, long C )
	{	cudaMLIsetElement( (liPMatrix)(MA), ht, len, m, n, C );}
inline void    cusdMLI_setElement( liMatrix MA, ui ht, ui len, ui m, ui n, long *d_C )
	{	cusdMLIsetElement( (liPMatrix)(MA), ht, len, m, n, d_C );}
inline void    cudaMLI_getElement( long *y, liMatrix MA, ui ht, ui len, ui m, ui n )
	{	cudaMLIgetElement( y, (liPMatrix)(MA), ht, len, m, n );}
inline void    cusdMLI_getElement( long *d_y, liMatrix MA, ui ht, ui len, ui m, ui n )
	{	cusdMLIgetElement( d_y, (liPMatrix)(MA), ht, len, m, n );}
inline long * cudaMLI_Pelement( liMatrix MA, ui ht, ui len, ui m, ui n )
	{	return cudaMLIPelement( (liPMatrix)(MA), ht, len, m, n );}
inline long   cudaMLI_element( liMatrix MA, ui ht, ui len, ui m, ui n )
{	return cudaMLIelement( (liPMatrix)(MA), ht, len, m, n );}

inline overror_t  cudaMLI_equ0( liMatrix MA, ui ht, ui len )
	{	return cudaVLI_equ0( (liPMatrix)MA, (ht)*(len) ); }
inline overror_t  cudaMLI_equ1( liMatrix MA, ui len )
	{	return cudaMLIequ1( (liPMatrix)(MA), len );} /* identity matrix */
inline overror_t  cudaMLI_equm1( liMatrix MA, ui len )
	{	return cudaMLIequm1( (liPMatrix)(MA), len );} /* neg. identity matrix */

inline overror_t  cudaMLI_randomLC( liMatrix MA, ui ht, ui len, long seed, long MinVal, long MaxVal, V_RANDOMLCSTATE *h_state )
	{	return cudaVLI_randomLC( (liPMatrix)(MA), (ht)*(len), seed, MinVal, MaxVal, h_state );}
inline overror_t  cudaMLI_random( liMatrix MA, ui ht, ui len, long seed, long MinVal, long MaxVal )
	{	return cudaVLI_random( (liPMatrix)(MA), (ht)*(len), seed, MinVal, MaxVal );}
inline overror_t  cusdMLI_randomLC( liMatrix MA, ui ht, ui len, long seed, long *d_MinVal, long *d_MaxVal, V_RANDOMLCSTATE *h_state )
	{	return cusdVLI_randomLC( (liPMatrix)(MA), (ht)*(len), seed, d_MinVal, d_MaxVal, h_state );}
inline overror_t  cusdMLI_random( liMatrix MA, ui ht, ui len, long seed, long *d_MinVal, long *d_MaxVal )
	{	return cusdVLI_random( (liPMatrix)(MA), (ht)*(len), seed, d_MinVal, d_MaxVal );}
inline overror_t  cudaMLI_outerprod( liMatrix MA, liVector X,  liVector Y, ui ht, ui len )
{	return cudaMLIouterprod( (liPMatrix)(MA), X, Y, ht, len );}

inline overror_t  cudaMLI_Row_equ0( liMatrix MA, ui ht, ui len, ui iRow )
	{	return cudaMLIRow_equ0( (liPMatrix)MA, ht, len, iRow );}
inline overror_t  cudaMLI_Col_equ0( liMatrix MA, ui ht, ui len, ui iRow )
	{	return cudaMLICol_equ0( (liPMatrix)MA, ht, len, iRow );}
inline overror_t  cudaMLI_Dia_equ0( liMatrix MA, ui len )
	{	return cudaMLIDia_equ0( (liPMatrix)(MA), len );}

inline overror_t  cudaMLI_Row_equC( liMatrix MA, ui ht, ui len, ui iRow, long C )
	{	return cudaMLIRow_equC( (liPMatrix)MA, ht, len, iRow, C );}
inline overror_t  cudaMLI_Col_equC( liMatrix MA, ui ht, ui len, ui iRow, long C )
	{	return cudaMLICol_equC( (liPMatrix)MA, ht, len, iRow, C );}
inline overror_t  cudaMLI_Dia_equC( liMatrix MA, ui len, long C )
	{	return cudaMLIDia_equC( (liPMatrix)(MA), len, C );}

inline overror_t  cusdMLI_Row_equC( liMatrix MA, ui ht, ui len, ui iRow, long *d_C )
	{	return cusdMLIRow_equC( (liPMatrix)MA, ht, len, iRow, d_C );}
inline overror_t  cusdMLI_Col_equC( liMatrix MA, ui ht, ui len, ui iRow, long *d_C )
	{	return cusdMLICol_equC( (liPMatrix)MA, ht, len, iRow, d_C );}
inline overror_t  cusdMLI_Dia_equC( liMatrix MA, ui len, long *d_C )
	{	return cusdMLIDia_equC( (liPMatrix)(MA), len, d_C );}

inline overror_t  cudaMLI_Row_equV( liMatrix MA, ui ht, ui len, ui iRow, liVector X )
	{	return cudaMLIRow_equV( (liPMatrix)MA, ht, len, iRow, X );}
inline overror_t  cudaMLI_Col_equV( liMatrix MA, ui ht, ui len, ui iRow, liVector X )
	{	return cudaMLICol_equV( (liPMatrix)MA, ht, len, iRow, X );}
inline overror_t  cudaMLI_Dia_equV( liMatrix MA, ui len, liVector X )
	{	return cudaMLIDia_equV( (liPMatrix)(MA), len, X );}

inline overror_t  cudaMLI_Trd_equM( liMatrix MA, liMatrix MTrd, ui len )
	{	return cudaMLITrd_equM( (liPMatrix)(MA), (liPMatrix)(MTrd), len );}
inline overror_t  cudaMLI_Trd_extract( liMatrix MTrd, liMatrix MA, ui len )
	{	return cudaMLITrd_extract( (liPMatrix)(MTrd), (liPMatrix)(MA), len );}

inline overror_t cudaMLI_equM( liMatrix MB, liMatrix MA, ui ht, ui len )
	{	return cudaVLI_equV( (liPMatrix)MB, (liPMatrix)MA, (ht)*(len) );}
inline overror_t cudaMLI_equMhost( liMatrix d_MB, liMatrix h_MA, ui ht, ui len )
	{	return cudaVLI_equVhost( (liPMatrix)d_MB, (h_MA)[0], (ht)*(len) );}
inline overror_t MLI_equMdevice( liMatrix h_MB, liMatrix d_MA, ui ht, ui len )
	{	return VLI_equVdevice( h_MB[0], (liPMatrix)d_MA, (ht)*(len) );}
inline overror_t cudaMLI_neg( liMatrix MB, liMatrix MA, ui ht, ui len )
	{	return cudaVLI_neg( (liPMatrix)(MB), (liPMatrix)(MA), (ht)*(len) );}
inline overror_t  cudaMLI_UequL( liMatrix MA, ui len )
	{	return cudaMLIUequL( (liPMatrix)(MA), len );}
inline overror_t  cudaMLI_LequU( liMatrix MA, ui len )
	{	return cudaMLILequU( (liPMatrix)(MA), len );}

/************** Data-type interconversions  ****************************/

inline overror_t cudaM_ULtoLI( liMatrix MLI, ulMatrix MUL, ui ht, ui len )
	{	return cudaV_ULtoLI( (liVector)MLI, (ulVector)MUL, (ht)*(len) );}
inline overror_t cudaM_BItoLI( liMatrix MLI, biMatrix MBI, ui ht, ui len )
	{	return cudaV_BItoLI( (liVector)MLI, (biVector)MBI, (ht)*(len) );}
inline overror_t cudaM_SItoLI( liMatrix MLI, siMatrix MSI, ui ht, ui len )
	{	return cudaV_SItoLI( (liVector)MLI, (siVector)MSI, (ht)*(len) );}
inline overror_t cudaM_ItoLI(  liMatrix MLI, iMatrix MI,  ui ht, ui len )
	{	return cudaV_ItoLI(  (liVector)MLI, (iVector)MI,   (ht)*(len) );}
inline overror_t cudaM_QItoLI( liMatrix MLI, qiMatrix MQI, ui ht, ui len )
	{	return cudaV_QItoLI( (liVector)MLI, (qiVector)MQI, (ht)*(len) );}
inline overror_t cudaM_LItoF(  fMatrix MF,  liMatrix MLI, ui ht, ui len )
	{	return cudaV_LItoF(  (fVector)MF,   (liVector)MLI, (ht)*(len) );}
inline overror_t cudaM_LItoD(  dMatrix MD,  liMatrix MLI, ui ht, ui len )
	{	return cudaV_LItoD(  (dVector)MD,   (liVector)MLI, (ht)*(len) );}

/********  Extracting a submatrix and copying a submatrix back  *********/

inline overror_t cudaMLI_submatrix( liMatrix MSub, ui subHt, ui subLen, liMatrix MSrce, ui srceHt, ui srceLen,
                      ui firstRowInCol, ui sampInCol, ui firstColInRow, ui sampInRow )
	{	return cudaMLIsubmatrix(  (liPMatrix)(MSub), subHt, subLen,
		                         (liPMatrix)(MSrce), srceHt, srceLen,
								 firstRowInCol, sampInCol, firstColInRow, sampInRow ); }

inline overror_t cudaMLI_submatrix_equM( liMatrix MDest, ui destHt, ui destLen,
                           ui firstRowInCol, ui sampInCol, ui firstColInRow, ui sampInRow,
                           liMatrix MSrce, ui srceHt, ui srceLen )
	{	return cudaMLIsubmatrix_equM(  (liPMatrix)(MDest), destHt, destLen,
                             firstRowInCol, sampInCol, firstColInRow, sampInRow,
							 (liPMatrix)(MSrce), srceHt, srceLen );}

inline overror_t cudaMLI_equMblock( liMatrix MSub, ui subHt, ui subLen, liMatrix MSrce, ui srceHt, ui srceLen,
                      ui firstRowInCol, ui firstColInRow )
{	return cudaMLIequMblock(  (liPMatrix)(MSub), subHt, subLen,
						   (liPMatrix)(MSrce), srceHt, srceLen, firstRowInCol, firstColInRow );}

inline overror_t cudaMLI_block_equM( liMatrix MDest, ui destHt, ui destLen,
                       ui firstRowInCol, ui firstColInRow,
                       liMatrix MSrce, ui srceHt, ui srceLen )
	{	return cudaMLIblock_equM( (liPMatrix)(MDest), destHt, destLen,
                             firstRowInCol, firstColInRow,
							 (liPMatrix)(MSrce), srceHt, srceLen );}

inline overror_t cudaMLI_equMblockT( liMatrix MSub, ui subHt, ui subLen, liMatrix MSrce, ui srceHt, ui srceLen,
                      ui firstRowInCol, ui firstColInRow )
	{	return cudaMLIequMblockT(  (liPMatrix)(MSub), subHt, subLen,
                             (liPMatrix)(MSrce), srceHt, srceLen,
							 firstRowInCol, firstColInRow );}

inline overror_t cudaMLI_block_equMT( liMatrix MDest, ui destHt, ui destLen,
                       ui firstRowInCol, ui firstColInRow,
                       liMatrix MSrce, ui srceHt, ui srceLen )
	{	return cudaMLIblock_equMT( (liPMatrix)(MDest), destHt, destLen,
                             firstRowInCol, firstColInRow,
							 (liPMatrix)(MSrce), srceHt, srceLen );}

/*****   Extracting a single row or a single column or the diagonal  ******
 *       and storing it into a vector                                     */

inline overror_t cudaMLI_Row_extract( liVector Y, liMatrix MA, ui ht, ui len, ui iRow ) 
	{	return cudaMLIRow_extract( Y, (liPMatrix)(MA), ht, len, iRow );}
inline overror_t cudaMLI_Col_extract( liVector Y, liMatrix MA, ui ht, ui len, ui iCol ) 
	{	return cudaMLICol_extract( Y, (liPMatrix)(MA), ht, len, iCol );}
inline overror_t cudaMLI_Dia_extract( liVector Y, liMatrix MA, ui len )
	{	return cudaMLIDia_extract( Y, (liPMatrix)(MA), len );}

/**************  Deleting or inserting a row or a column   ***************/

inline overror_t cudaMLI_Row_delete( liMatrix MB, liMatrix MA, ui htA, ui lenA, ui iRow )
	{	return cudaMLIRow_delete( (liPMatrix)(MB), (liPMatrix)(MA), htA, lenA, iRow );}
inline overror_t cudaMLI_Col_delete( liMatrix MB, liMatrix MA, ui htA, ui lenA, ui iCol )
	{	return cudaMLICol_delete( (liPMatrix)(MB), (liPMatrix)(MA), htA, lenA, iCol );}
inline overror_t cudaMLI_Row_insert( liMatrix MB, liMatrix MA, ui htB, ui lenB, ui iRow, liVector X )
	{	return cudaMLIRow_insert( (liPMatrix)(MB), (liPMatrix)(MA), htB, lenB, iRow, X );}
inline overror_t cudaMLI_Col_insert( liMatrix MB, liMatrix MA, ui htB, ui lenB, ui iCol, liVector X )
	{	return cudaMLICol_insert( (liPMatrix)(MB), (liPMatrix)(MA), htB, lenB, iCol, X );}


/******  One-dimensional vector operations **********************
         performed along all rows or all columns simultaneously,
         or along the diagonal of a square matrix                */

inline overror_t cudaMLI_Rows_max( liVector Y, liMatrix MA, ui ht, ui len )
	{	return cudaMLIRows_max( Y, (liPMatrix)(MA), ht, len );}
inline overror_t cudaMLI_Cols_max( liVector Y, liMatrix MA, ui ht, ui len )
	{	return cudaMLICols_max( Y, (liPMatrix)(MA), ht, len );}
inline overror_t cudaMLI_Dia_max(  long *h_RetValPtr, liMatrix MA, ui len )
	{	return cudaMLIDia_max(  h_RetValPtr, (liPMatrix)(MA), len );}
inline overror_t cusdMLI_Dia_max(  long *d_RetValPtr, liMatrix MA, ui len )
	{	return cusdMLIDia_max(  d_RetValPtr, (liPMatrix)(MA), len );}
inline overror_t cudaMLI_Rows_min( liVector Y, liMatrix MA, ui ht, ui len )
	{	return cudaMLIRows_min( Y, (liPMatrix)(MA), ht, len );}
inline overror_t cudaMLI_Cols_min( liVector Y, liMatrix MA, ui ht, ui len )
	{	return cudaMLICols_min( Y, (liPMatrix)(MA), ht, len );}
inline overror_t cudaMLI_Dia_min(  long *h_RetValPtr, liMatrix MA, ui len )
	{	return cudaMLIDia_min(  h_RetValPtr, (liPMatrix)(MA), len );}
inline overror_t cusdMLI_Dia_min(  long *d_RetValPtr, liMatrix MA, ui len )
	{	return cusdMLIDia_min(  d_RetValPtr, (liPMatrix)(MA), len );}

inline overror_t cudaMLI_Rows_rotate( liMatrix MA, ui ht, ui len, ssize_t pos)
	{	return cudaMLIRows_rotate( (liPMatrix)(MA), ht, len, pos );}
inline overror_t cudaMLI_Cols_rotate( liMatrix MA, ui ht, ui len, ssize_t pos)
	{	return cudaMLICols_rotate( (liPMatrix)(MA), ht, len, pos );}
inline overror_t cudaMLI_Rows_rotate_buf( liMatrix MA, ui ht, ui len, ssize_t pos, liMatrix MBuf) 
	{	return cudaMLIRows_rotate_buf( (liPMatrix)(MA), ht, len, pos, (liPMatrix)(MBuf) );}
inline overror_t cudaMLI_Cols_rotate_buf( liMatrix MA, ui ht, ui len, ssize_t pos, liMatrix MBuf) 
	{	return cudaMLICols_rotate_buf( (liPMatrix)(MA), ht, len, pos, (liPMatrix)(MBuf) );}
inline overror_t cudaMLI_Rows_reflect( liMatrix MA, ui ht, ui len )
	{	return cudaMLIRows_reflect( (liPMatrix)(MA), ht, len );}
inline overror_t cudaMLI_Cols_reflect( liMatrix MA, ui ht, ui len )
	{	return cudaMLICols_reflect( (liPMatrix)(MA), ht, len );}
inline overror_t cudaMLI_Rows_rev( liMatrix MA, ui ht, ui len )
	{	return cudaMLIRows_rev( (liPMatrix)(MA), ht, len );}
inline overror_t cudaMLI_Cols_rev( liMatrix MA, ui ht, ui len )
	{	return cudaMLICols_rev( (liPMatrix)(MA), ht, len );}
inline overror_t  cudaMLI_Rows_distribution( uiMatrix MAbund, liVector Limits, ui nBins, liMatrix MX, ui ht, ui len, int mode )
	{	return cudaMLIRows_distribution( (uiPMatrix)MAbund, Limits, nBins, (liPMatrix)MX, ht, len, mode ); }
inline overror_t  cudaMLI_Cols_distribution( uiMatrix MAbund, liVector Limits, ui nBins, liMatrix MX, ui ht, ui len, int mode )
	{	return cudaMLICols_distribution( (uiPMatrix)MAbund, Limits, nBins, (liPMatrix)MX, ht, len, mode ); }

/********  Operations involving two rows or two colums of one matrix  *****/

inline overror_t cudaMLI_Rows_exchange( liMatrix MA, ui ht, ui len, ui row1, ui row2 )
	{	return cudaMLIRows_exchange( (liPMatrix)(MA), ht, len, row1, row2 );}
inline overror_t cudaMLI_Cols_exchange( liMatrix MA, ui ht, ui len, ui col1, ui col2 )
	{	return cudaMLICols_exchange( (liPMatrix)(MA), ht, len, col1, col2 );}

/*************** Transposing and rotating a matrix **********************/

inline overror_t cudaMLI_transpose( liMatrix MTr, liMatrix MA, ui htTr, ui lenTr )
	{	return cudaMLItranspose( (liPMatrix)(MTr), (liPMatrix)(MA), htTr, lenTr );}
       /*  dimensions htTr, lenTr are those of the transposed matrix, not of the original!   */
inline overror_t cudaMLI_rotate90( liMatrix MRot, liMatrix MA, ui htRot, ui lenRot )
	{	return cudaMLIrotate90( (liPMatrix)(MRot), (liPMatrix)(MA), htRot, lenRot );}
inline overror_t cudaMLI_rotate180( liMatrix MRot, liMatrix MA, ui htRot, ui lenRot )
	{	return cudaVLI_rev( (liPMatrix)(MRot), (liPMatrix)(MA), (htRot)*(lenRot) );}
inline overror_t cudaMLI_rotate270( liMatrix MRot, liMatrix MA, ui htRot, ui lenRot )
	{	return cudaMLIrotate270( (liPMatrix)(MRot), (liPMatrix)(MA), htRot, lenRot );}
inline overror_t cudaMLI_transpose_buf( liMatrix MTr, liMatrix MA, ui htTr, ui lenTr, liMatrix MBuf )
	{	return cudaMLItranspose_buf( (liPMatrix)(MTr), (liPMatrix)(MA), htTr, lenTr, (liPMatrix)(MBuf) );}

/**************************  Input and Output  **************************
	The input/output functions involve memory transfers from device
	to host memory or vice versa. The generic cudaMLI_input/output functions
	allocate their own host buffers, whereas the cudaMLI_xxx_buf functions
	take a user-supplied buffer vector h_Wk (size must be >= ht*len )
	and are much more efficient.                                       */

inline overror_t cudaMLI_fprint( FILE *stream, liMatrix MA, ui ht, ui len, unsigned linewidth )
	{	return cudaMLIfprint( stream, (liPMatrix)(MA), ht, len, linewidth ); }
inline overror_t cudaMLI_print( liMatrix MA, ui ht, ui len )
	{	return cudaMLIfprint( stdout, (liPMatrix)(MA), ht, len, 80 ); }
inline overror_t cudaMLI_cprint( liMatrix MA, ui ht, ui len )
	{	return cudaMLIcprint( (liPMatrix)(MA), ht, len ); }
inline overror_t cudaMLI_fprint_buf( FILE *stream, liMatrix d_MA, ui ht, ui len, unsigned linewidth, liVector h_Wk )
	{	return cudaMLIfprint_buf( stream, (liPMatrix)(d_MA), ht, len, linewidth, h_Wk ); }
inline overror_t cudaMLI_print_buf( liMatrix d_MA, ui ht, ui len, liVector h_Wk )
	{	return cudaMLIfprint_buf( stdout, (liPMatrix)(d_MA), ht, len, 80, h_Wk ); }
inline overror_t cudaMLI_cprint_buf( liMatrix d_MA, ui ht, ui len, liVector h_Wk )
	{	return cudaMLIcprint_buf( (liPMatrix)(d_MA), ht, len, h_Wk ); }
		/*  cudaMLI_print, cudaMLI_cprint usable only for console applications! */
inline overror_t  cudaMLI_write( FILE *stream, liMatrix MA, ui ht, ui len )
	{	return cudaMLIwrite( stream, (liPMatrix)(MA), ht, len ); }
inline overror_t cudaMLI_read( liMatrix MA, ui ht, ui len, FILE *stream )
	{	return cudaMLIread( (liPMatrix)(MA), ht, len, stream ); }
inline overror_t  cudaMLI_write_buf( FILE *stream, liMatrix d_MA, ui ht, ui len, liVector h_Wk )
	{	return cudaMLIwrite_buf( stream, (liPMatrix)(d_MA), ht, len, h_Wk ); }
inline overror_t cudaMLI_read_buf( liMatrix d_MA, ui ht, ui len, FILE *stream, liVector h_Wk )
	{	return cudaMLIread_buf( (liPMatrix)(d_MA), ht, len, stream, h_Wk ); }
                                   /* write and read in ascii format */
inline overror_t cudaMLI_store( FILE *stream, liMatrix MA, ui ht, ui len )
{	return cudaVLI_store( stream, (liPMatrix)(MA), (len)*(ht) ); }
inline overror_t cudaMLI_recall( liMatrix MA, ui ht, ui len, FILE *stream )
	{	return cudaVLI_recall( (liPMatrix)(MA), (len)*(ht), stream ); }
inline overror_t cudaMLI_store_buf( FILE *stream, liMatrix d_MA, ui ht, ui len, liVector h_Wk )
{	return cudaVLI_store_buf( stream, (liPMatrix)(d_MA), (len)*(ht), h_Wk ); }
inline overror_t cudaMLI_recall_buf( liMatrix d_MA, ui ht, ui len, FILE *stream, liVector h_Wk )
	{	return cudaVLI_recall_buf( (liPMatrix)(d_MA), (len)*(ht), stream, h_Wk ); }
                                  /* store and recall in binary format */

#else  /* plain-C, not C++: type-cast used to transform liMatrix into liPMatrix  */

/***  Addressing single elements of dynamically allocated matrices: ******/

#define cudaMLI_setElement( MA, ht, len, m, n, C ) cudaMLIsetElement( (liPMatrix)(MA), ht, len, m, n, C )
#define cusdMLI_setElement( MA, ht, len, m, n, C ) cusdMLIsetElement( (liPMatrix)(MA), ht, len, m, n, C )
#define cudaMLI_getElement( y, MA, ht, len, m, n ) cudaMLIgetElement( y, (liPMatrix)(MA), ht, len, m, n )
#define cusdMLI_getElement( y, MA, ht, len, m, n ) cusdMLIgetElement( y, (liPMatrix)(MA), ht, len, m, n )
#define cudaMLI_Pelement( MA, ht, len, m, n )      cudaMLIPelement( (liPMatrix)(MA), ht, len, m, n )
                     /* returns a pointer to MA[m][n]. */
#define cudaMLI_element( MA, ht, len, m, n )       cudaMLIelement( (liPMatrix)(MA), ht, len, m, n )

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
        VLI_equ1( (liVector)MA, ht * len );
*/

#define cudaMLI_equ0( MA, ht, len )            cudaVLI_equ0( (liPMatrix)(MA), (ht)*(len) )
#define cudaMLI_equ1( MA, len )                cudaMLIequ1( (liPMatrix)(MA), len ) /* identity matrix */
#define cudaMLI_equm1( MA, len )               cudaMLIequm1( (liPMatrix)(MA), len ) /* neg. identity matrix */
#define cudaMLI_randomLC( MA, ht, len, seed, Min, Max, h_state )      cudaVLI_randomLC( MA, (ht)*(len), seed, Min, Max, h_state )
#define cudaMLI_random( MA, ht, len, seed, Min, Max )                 cudaVLI_random( MA, (ht)*(len), seed, Min, Max )
#define cusdMLI_randomLC( MA, ht, len, seed, d_Min, d_Max, h_state )  cudaVLI_randomLC( MA, (ht)*(len), seed, d_Min, d_Max, h_state )
#define cusdMLI_random( MA, ht, len, seed, d_Min, d_Max )             cudaVLI_random( MA, (ht)*(len), seed, d_Min, d_Max )
#define cudaMLI_outerprod( MA, X, Y, ht, len ) cudaMLIouterprod( (liPMatrix)(MA), X, Y, ht, len )
                       /* sizX=ht, sizY=len */
#define cudaMLI_Row_equ0( MA, ht, len, iRow )  cudaMLIRow_equ0( (liPMatrix)(MA), ht, len, iRow )
#define cudaMLI_Col_equ0( MA, ht, len, iCol )  cudaMLICol_equ0( (liPMatrix)(MA), ht, len, iCol )
#define cudaMLI_Dia_equ0( MA, len )            cudaMLIDia_equ0( (liPMatrix)(MA), len )
#define cudaMLI_Row_equC( MA, ht, len, iRow, C ) cudaMLIRow_equC( (liPMatrix)(MA), ht, len, iRow, C )
#define cudaMLI_Col_equC( MA, ht, len, iCol, C ) cudaMLICol_equC( (liPMatrix)(MA), ht, len, iCol, C )
#define cudaMLI_Dia_equC( MA, len, C )           cudaMLIDia_equC( (liPMatrix)(MA), len, C )
#define cusdMLI_Row_equC( MA, ht, len, iRow, d_C ) cusdMLIRow_equC( (liPMatrix)(MA), ht, len, iRow, d_C )
#define cusdMLI_Col_equC( MA, ht, len, iCol, d_C ) cusdMLICol_equC( (liPMatrix)(MA), ht, len, iCol, d_C )
#define cusdMLI_Dia_equC( MA, len, d_C )           cusdMLIDia_equC( (liPMatrix)(MA), len, d_C )

#define cudaMLI_Row_equV( MA, ht, len, iRow, X ) cudaMLIRow_equV( (liPMatrix)(MA), ht, len, iRow, X )
#define cudaMLI_Col_equV( MA, ht, len, iCol, X ) cudaMLICol_equV( (liPMatrix)(MA), ht, len, iCol, X )
#define cudaMLI_Dia_equV( MA, len, X )           cudaMLIDia_equV( (liPMatrix)(MA), len, X )

#define cudaMLI_Trd_equM( MA, MTrd, len )    cudaMLITrd_equM( (liPMatrix)(MA), (liPMatrix)(MTr)d, len )
#define cudaMLI_Trd_extract( MTrd, MA, len ) cudaMLITrd_extract( (liPMatrix)(MTr)d, (liPMatrix)(MA), len )

#define cudaMLI_equM( MB, MA, ht, len )      cudaVLI_equV( (liPMatrix)(MB), (liPMatrix)(MA), (ht)*(len) )
#define cudaMLI_equMhost( MB, MA, ht, len )  cudaVLI_equVhost( (liPMatrix)(MB), MA[0], (ht)*(len) )
#define MLI_equMdevice( MB, MA, ht, len )    VLI_equVdevice( MB[0], (liPMatrix)(MA), (ht)*(len) )
#define cudaMLI_neg( MB, MA, ht, len )       cudaVLI_neg( (liPMatrix)(MB), (liPMatrix)(MA), (ht)*(len) )

#define cudaMLI_UequL( MA, len ) cudaMLIUequL( (liPMatrix)(MA), len )
#define cudaMLI_LequU( MA, len ) cudaMLILequU( (liPMatrix)(MA), len )


/************** Data-type interconversions  ****************************/

#define cudaM_LItoUL( MUL, MLI, ht, len ) cudaV_LItoUL( (ulVector)(MUL), (liVector)(MLI), (ht)*(len) )
#define cudaM_ULtoLI( MLI, MUL, ht, len ) cudaV_ULtoLI( (liVector)(MLI), (ulVector)(MUL), (ht)*(len) )
#define cudaM_LItoBI( MBI, MLI, ht, len ) cudaV_LItoBI( (biVector)(MBI), (liVector)(MLI), (ht)*(len) )
#define cudaM_LItoSI( MSI, MLI, ht, len ) cudaV_LItoSI( (siVector)(MSI), (liVector)(MLI), (ht)*(len) )
#define cudaM_LItoI(  MI,  MLI, ht, len ) cudaV_LItoI(  (iVector)(MI),   (liVector)(MLI), (ht)*(len) )
#define cudaM_LItoQI( MQI, MLI, ht, len ) cudaV_LItoQI( (qiVector)(MQI), (liVector)(MLI), (ht)*(len) )
#define cudaM_BItoLI( MLI, MBI, ht, len ) cudaV_BItoLI( (liVector)(MLI), (biVector)(MBI), (ht)*(len) )
#define cudaM_SItoLI( MLI, MSI, ht, len ) cudaV_SItoLI( (liVector)(MLI), (siVector)(MSI), (ht)*(len) )
#define cudaM_ItoLI(  MLI, MI,  ht, len ) cudaV_ItoLI(  (liVector)(MLI), (iVector)(MI),   (ht)*(len) )
#define cudaM_QItoLI( MLI, MQI, ht, len ) cudaV_QItoLI( (liVector)(MLI), (qiVector)(MQI), (ht)*(len) )
#define cudaM_LItoF(  MF,  MLI, ht, len ) cudaV_LItoF(  (fVector)(MF),   (liVector)(MLI), (ht)*(len) )
#define cudaM_LItoD(  MD,  MLI, ht, len ) cudaV_LItoD(  (dVector)(MD),   (liVector)(MLI), (ht)*(len) )

/********  Extracting a submatrix and copying a submatrix back  *********/

#define cudaMLI_submatrix( MSub, subHt, subLen, MSrce, srceHt, srceLen, \
                      firstRowInCol, sampInCol, firstColInRow, sampInRow ) \
               cudaMLIsubmatrix(  (liPMatrix)(MSub), subHt, subLen, \
                             (liPMatrix)(MSrce), srceHt, srceLen, \
                             firstRowInCol, sampInCol, firstColInRow, sampInRow )

#define cudaMLI_submatrix_equM( MDest, destHt, destLen, \
                           firstRowInCol, sampInCol, firstColInRow, sampInRow, \
                           MSrce, srceHt, srceLen ) \
               cudaMLIsubmatrix_equM(  (liPMatrix)(MDest), destHt, destLen, \
                             firstRowInCol, sampInCol, firstColInRow, sampInRow, \
                             (liPMatrix)(MSrce), srceHt, srceLen )

#define cudaMLI_equMblock( MSub, subHt, subLen, \
                      MSrce, srceHt, srceLen, \
                      firstRowInCol, firstColInRow ) \
               cudaMLIequMblock(  (liPMatrix)(MSub), subHt, subLen, \
                             (liPMatrix)(MSrce), srceHt, srceLen, \
                             firstRowInCol, firstColInRow )

#define cudaMLI_block_equM( MDest, destHt, destLen, \
                       firstRowInCol, firstColInRow, \
                       MSrce, srceHt, srceLen ) \
               cudaMLIblock_equM( (liPMatrix)(MDest), destHt, destLen, \
                             firstRowInCol, firstColInRow, \
                             (liPMatrix)(MSrce), srceHt, srceLen )

#define cudaMLI_equMblockT( MSub, subHt, subLen, \
                      MSrce, srceHt, srceLen, \
                      firstRowInCol, firstColInRow ) \
               cudaMLIequMblockT(  (liPMatrix)(MSub), subHt, subLen, \
                             (liPMatrix)(MSrce), srceHt, srceLen, \
                             firstRowInCol, firstColInRow )

#define cudaMLI_block_equMT( MDest, destHt, destLen, \
                       firstRowInCol, firstColInRow, \
                       MSrce, srceHt, srceLen ) \
               cudaMLIblock_equMT( (liPMatrix)(MDest), destHt, destLen, \
                             firstRowInCol, firstColInRow, \
                             (liPMatrix)(MSrce), srceHt, srceLen )

/*****   Extracting a single row or a single column or the diagonal  ******
 *       and storing it into a vector                                     */

#define cudaMLI_Row_extract( Y, MA, ht, len, iRow ) \
                                     cudaMLIRow_extract( Y, (liPMatrix)(MA), ht, len, iRow )
#define cudaMLI_Col_extract( Y, MA, ht, len, iCol ) \
                                     cudaMLICol_extract( Y, (liPMatrix)(MA), ht, len, iCol )
#define cudaMLI_Dia_extract( Y, MA, len ) cudaMLIDia_extract( Y, (liPMatrix)(MA), len )


/**************  Deleting or inserting a row or a column   ***************/

#define cudaMLI_Row_delete( MB, MA, htA, lenA, iRow ) \
                           cudaMLIRow_delete( (liPMatrix)(MB), (liPMatrix)(MA), htA, lenA, iRow )
#define cudaMLI_Col_delete( MB, MA, htA, lenA, iCol ) \
                           cudaMLICol_delete( (liPMatrix)(MB), (liPMatrix)(MA), htA, lenA, iCol )
#define cudaMLI_Row_insert( MB, MA, htB, lenB, iRow, X ) \
                           cudaMLIRow_insert( (liPMatrix)(MB), (liPMatrix)(MA), htB, lenB, iRow, X )
#define cudaMLI_Col_insert( MB, MA, htB, lenB, iCol, X ) \
                           cudaMLICol_insert( (liPMatrix)(MB), (liPMatrix)(MA), htB, lenB, iCol, X )

/******  One-dimensional vector operations **********************
         performed along all rows or all columns simultaneously,
         or along the diagonal of a square matrix                */

#define cudaMLI_Rows_max( Y, MA, ht, len )     cudaMLIRows_max( Y, (liPMatrix)(MA), ht, len )
#define cudaMLI_Cols_max( Y, MA, ht, len )     cudaMLICols_max( Y, (liPMatrix)(MA), ht, len )
#define cudaMLI_Dia_max(  h_RetPtr, MA, len )  cudaMLIDia_max( h_RetPtr, (liPMatrix)(MA), len )
#define cusdMLI_Dia_max(  d_RetPtr, MA, len )  cusdMLIDia_max( d_RetPtr, (liPMatrix)(MA), len )
#define cudaMLI_Rows_min( Y, MA, ht, len )     cudaMLIRows_min( Y, (liPMatrix)(MA), ht, len )
#define cudaMLI_Cols_min( Y, MA, ht, len )     cudaMLICols_min( Y, (liPMatrix)(MA), ht, len )
#define cudaMLI_Dia_min(  h_RetPtr, MA, len )  cudaMLIDia_min( h_RetPtr, (liPMatrix)(MA), len )
#define cusdMLI_Dia_min(  d_RetPtr, MA, len )  cusdMLIDia_min( d_RetPtr, (liPMatrix)(MA), len )

#define cudaMLI_Rows_rotate( MA, ht, len, pos) cudaMLIRows_rotate( (liPMatrix)(MA), ht, len, pos )
#define cudaMLI_Cols_rotate( MA, ht, len, pos) cudaMLICols_rotate( (liPMatrix)(MA), ht, len, pos )
#define cudaMLI_Rows_rotate_buf( MA, ht, len, pos, MBuf) cudaMLIRows_rotate_buf( (liPMatrix)(MA), ht, len, pos, (liPMatrix)(MBuf) )
#define cudaMLI_Cols_rotate_buf( MA, ht, len, pos, MBuf) cudaMLICols_rotate_buf( (liPMatrix)(MA), ht, len, pos, (liPMatrix)(MBuf) )
#define cudaMLI_Rows_reflect( MA, ht, len)     cudaMLIRows_reflect( (liPMatrix)(MA), ht, len )
#define cudaMLI_Cols_reflect( MA, ht, len)     cudaMLICols_reflect( (liPMatrix)(MA), ht, len )
#define cudaMLI_Rows_rev( MA, ht, len)         cudaMLIRows_rev( (liPMatrix)(MA), ht, len )
#define cudaMLI_Cols_rev( MA, ht, len)         cudaMLICols_rev( (liPMatrix)(MA), ht, len )
#define cudaMLI_Rows_distribution( MAbund, Limits, nBins, MX, ht, len, mode ) cudaMLIRows_distribution( (uiPMatrix)MAbund, Limits, nBins, (liPMatrix)MX, ht, len, mode )
#define cudaMLI_Cols_distribution( MAbund, Limits, nBins, MX, ht, len, mode ) cudaMLICols_distribution( (uiPMatrix)MAbund, Limits, nBins, (liPMatrix)MX, ht, len, mode )

/********  Operations involving two rows or two colums of one matrix  *****/

#define cudaMLI_Rows_exchange( MA, ht, len, row1, row2 ) \
                             cudaMLIRows_exchange( (liPMatrix)(MA), ht, len, row1, row2 )
#define cudaMLI_Cols_exchange( MA, ht, len, col1, col2 ) \
                             cudaMLICols_exchange( (liPMatrix)(MA), ht, len, col1, col2 )

/************  Transposing and rotating a matrix **********************/

#define cudaMLI_transpose( MTr, MA, htTr, lenTr ) \
             cudaMLItranspose( (liPMatrix)(MTr), (liPMatrix)(MA), htTr, lenTr )
       /*  dimensions htTr, lenTr are those of the transposed matrix,
           not of the original!                */
#define cudaMLI_rotate90( MRot, MA, htRot, lenRot ) \
             cudaMLIrotate90( (liPMatrix)(MRot), (liPMatrix)(MA), htRot, lenRot )
#define cudaMLI_rotate180( MRot, MA, htRot, lenRot ) \
             cudaVLI_rev( (liPMatrix)(MRot), (liPMatrix)(MA), (htRot)*(lenRot) )
#define cudaMLI_rotate270( MRot, MA, htRot, lenRot ) \
             cudaMLIrotate270( (liPMatrix)(MRot), (liPMatrix)(MA), htRot, lenRot )
#define cudaMLI_transpose_buf( MTr, MA, htTr, lenTr, MBuf ) \
             cudaMLItranspose_buf( (liPMatrix)(MTr), (liPMatrix)(MA), htTr, lenTr, (liPMatrix)(MBuf) )

/**************************  Input and Output  **************************
	The input/output functions involve memory transfers from device
	to host memory or vice versa. The generic cudaMLI_input/output functions
	allocate their own host buffers, whereas the cudaMLI_xxx_buf functions
	take a user-supplied buffer vector h_Wk (size must be >= ht*len )
	and are much more efficient.                                       */

#define cudaMLI_fprint( stream, MA, ht, len, linewidth ) \
                    cudaMLIfprint( stream, (liPMatrix)(MA), ht, len, linewidth )
#define cudaMLI_print( MA, ht, len )  cudaMLIfprint( stdout, (liPMatrix)(MA), ht, len, 80 )
#define cudaMLI_cprint( MA, ht, len ) cudaMLIcprint( (liPMatrix)(MA), ht, len )
#define cudaMLI_fprint_buf( stream, MA, ht, len, linewidth, h_Wk ) \
                    cudaMLIfprint_buf( stream, (liPMatrix)(MA), ht, len, linewidth, h_Wk )
#define cudaMLI_print_buf( MA, ht, len )  cudaMLIfprint_buf( stdout, (liPMatrix)(MA), ht, len, 80, h_Wk )
#define cudaMLI_cprint_buf( MA, ht, len ) cudaMLIcprint_buf( (liPMatrix)(MA), ht, len, h_Wk )
  /*  cudaMLI_print, cudaMLI_cprint usable only for console applications! */
#define cudaMLI_write( str, MA, ht, len )   cudaMLIwrite( str, (liPMatrix)(MA), ht, len )
#define cudaMLI_read( MA, ht, len, str )    cudaMLIread( (liPMatrix)(MA), ht, len, str )
#define cudaMLI_write_buf( str, MA, ht, len, h_Wk )   cudaMLIwrite_buf( str, (liPMatrix)(MA), ht, len, h_Wk )
#define cudaMLI_read_buf( MA, ht, len, str, h_Wk )    cudaMLIread_buf( (liPMatrix)(MA), ht, len, str, h_Wk )
                                   /* write and read in ascii format */
#define cudaMLI_store( str, MA, ht, len )   cudaVLI_store( str, (liPMatrix)(MA), (len)*(ht) )
#define cudaMLI_recall( MA, ht, len, str)   cudaVLI_recall( (liPMatrix)(MA), (len)*(ht), str)
#define cudaMLI_store_buf( str, MA, ht, len, h_Wk )   cudaVLI_store_buf( str, (liPMatrix)(MA), (len)*(ht), h_Wk )
#define cudaMLI_recall_buf( MA, ht, len, str, h_Wk)   cudaVLI_recall_buf( (liPMatrix)(MA), (len)*(ht), str, h_Wk )
                                  /* store and recall in binary format */

#endif /* plain-C or C++ for functions working on device memory */


/*******************  Functions working on host memory: **********************
 *                                                                           *
 *	MLIcu_func		(working on matrices in host memory, input type liMatrix,*
 *	scalar parameters on host and passed by value)                           *
 *****************************************************************************/ 

/****************  Initialization  ****************************************/

#define MLIcu_equ0( MA, ht, len )                   VLIcu_equ0( (MA)[0], (ht)*(len) )
#define MLIcu_equ1( MA, len )                       MLIcuequ1( (MA)[0], len ) /* identity matrix */
#define MLIcu_equm1( MA, len )                      MLIcuequm1( (MA)[0], len ) /* neg. identity matrix */
#define MLIcu_randomLC( MA, ht, len, seed, Min, Max, state ) VLIcu_randomLC( (MA)[0], (ht)*(len), seed, Min, Max, state )
#define MLIcu_random( MA, ht, len, seed, Min, Max )          VLIcu_random( (MA)[0], (ht)*(len), seed, Min, Max )
#define MLIcu_outerprod( MA, X, Y, ht, len )        MLIcuouterprod( (MA)[0], X, Y, ht, len )
                       /* sizX=ht, sizY=len */
#define MLIcu_Row_equ0( MA, ht, len, iRow )    MLIcuRow_equ0( (MA)[0], ht, len, iRow )
#define MLIcu_Col_equ0( MA, ht, len, iCol )    MLIcuCol_equ0( (MA)[0], ht, len, iCol )
#define MLIcu_Dia_equ0( MA, len )              MLIcuDia_equ0( (MA)[0], len )
#define MLIcu_Row_equC( MA, ht, len, iRow, C ) MLIcuRow_equC( (MA)[0], ht, len, iRow, C )
#define MLIcu_Col_equC( MA, ht, len, iCol, C ) MLIcuCol_equC( (MA)[0], ht, len, iCol, C )
#define MLIcu_Dia_equC( MA, len, C )           MLIcuDia_equC( (MA)[0], len, C )

#define MLIcu_Row_equV( MA, ht, len, iRow, X ) MLIcuRow_equV( (MA)[0], ht, len, iRow, X )
#define MLIcu_Col_equV( MA, ht, len, iCol, X ) MLIcuCol_equV( (MA)[0], ht, len, iCol, X )
#define MLIcu_Dia_equV( MA, len, X )           MLIcuDia_equV( (MA)[0], len, X )

#define MLIcu_Trd_equM( MA, MTrd, len )        MLIcuTrd_equM( (MA)[0], (MTrd)[0], len )
#define MLIcu_Trd_extract( MTrd, MA, len )     MLIcuTrd_extract( (MTrd)[0], (MA)[0], len )

#define MLIcu_equM( MB, MA, ht, len )          VLIcu_equV( (MB)[0], (MA)[0], (ht)*(len) )
#define MLIcu_equMhost( MB, MA, ht, len )      VLIcu_equVhost( (MB)[0], MA[0], (ht)*(len) )
#define MLIcu_neg( MB, MA, ht, len )           VLIcu_neg( (MB)[0], (MA)[0], (ht)*(len) )

#define MLIcu_UequL( MA, len ) MLIcuUequL( (MA)[0], len )
#define MLIcu_LequU( MA, len ) MLIcuLequU( (MA)[0], len )
     /* copy lower-diagonal elements into upper-diagonal
       (or vice versa) by index-reflection, so as to get a symmetric matrix    */

            /* data-type conversions:  */
#define Mcu_LItoUL( MUL, MLI, ht, len ) Vcu_LItoUL( (MUL)[0], (MLI)[0], (ht)*(len) )
#define Mcu_ULtoLI( MLI, MUL, ht, len ) Vcu_ULtoLI( (MLI)[0], (MUL)[0], (ht)*(len) )
#define Mcu_LItoBI( MBI, MLI, ht, len ) Vcu_LItoBI( (MBI)[0], (MLI)[0], (ht)*(len) )
#define Mcu_LItoSI( MSI, MLI, ht, len ) Vcu_LItoSI( (MSI)[0], (MLI)[0], (ht)*(len) )
#define Mcu_LItoI(  MI,  MLI, ht, len ) Vcu_LItoI(  (MI)[0],  (MLI)[0], (ht)*(len) )
#define Mcu_LItoQI( MQI, MLI, ht, len ) Vcu_LItoQI( (MQI)[0], (MLI)[0], (ht)*(len) )
#define Mcu_BItoLI( MLI, MBI, ht, len ) Vcu_BItoLI( (MLI)[0], (MBI)[0], (ht)*(len) )
#define Mcu_SItoLI( MLI, MSI, ht, len ) Vcu_SItoLI( (MLI)[0], (MSI)[0], (ht)*(len) )
#define Mcu_ItoLI(  MLI, MI,  ht, len ) Vcu_ItoLI(  (MLI)[0], (MI)[0],  (ht)*(len) )
#define Mcu_QItoLI( MLI, MQI, ht, len ) Vcu_QItoLI( (MLI)[0], (MQI)[0], (ht)*(len) )
#define Mcu_LItoF(  MF,  MLI, ht, len ) Vcu_LItoF(  (MF)[0],  (MLI)[0], (ht)*(len) )
#define Mcu_LItoD(  MD,  MLI, ht, len ) Vcu_LItoD(  (MD)[0],  (MLI)[0], (ht)*(len) )


/********  Extracting a submatrix and copying a submatrix back  *********/

#define MLIcu_submatrix( MSub, subHt, subLen, MSrce, srceHt, srceLen, \
                      firstRowInCol, sampInCol, firstColInRow, sampInRow ) \
               MLIcusubmatrix(  (MSub)[0], subHt, subLen, \
                             (MSrce)[0], srceHt, srceLen, \
                             firstRowInCol, sampInCol, firstColInRow, sampInRow )

#define MLIcu_submatrix_equM( MDest, destHt, destLen, \
                           firstRowInCol, sampInCol, firstColInRow, sampInRow, \
                           MSrce, srceHt, srceLen ) \
               MLIcusubmatrix_equM(  (MDest)[0], destHt, destLen, \
                             firstRowInCol, sampInCol, firstColInRow, sampInRow, \
                             (MSrce)[0], srceHt, srceLen )

#define MLIcu_equMblock( MSub, subHt, subLen, MSrce, srceHt, srceLen, \
                      firstRowInCol, firstColInRow ) \
               MLIcuequMblock(  (MSub)[0], subHt, subLen, \
                             (MSrce)[0], srceHt, srceLen, \
                             firstRowInCol, firstColInRow )

#define MLIcu_block_equM( MDest, destHt, destLen, \
                       firstRowInCol, firstColInRow, \
                       MSrce, srceHt, srceLen ) \
               MLIcublock_equM( (MDest)[0], destHt, destLen, \
                             firstRowInCol, firstColInRow, \
                             (MSrce)[0], srceHt, srceLen )

#define MLIcu_equMblockT( MSub, subHt, subLen, MSrce, srceHt, srceLen, \
                      firstRowInCol, firstColInRow ) \
               MLIcuequMblockT(  (MSub)[0], subHt, subLen, \
                             (MSrce)[0], srceHt, srceLen, \
                             firstRowInCol, firstColInRow )

#define MLIcu_block_equMT( MDest, destHt, destLen, \
                       firstRowInCol, firstColInRow, \
                       MSrce, srceHt, srceLen ) \
               MLIcublock_equMT( (MDest)[0], destHt, destLen, \
                             firstRowInCol, firstColInRow, \
                             (MSrce)[0], srceHt, srceLen )

/*****   Extracting a single row or a single column or the diagonal  ******
 *       and storing it into a vector                                     */

#define MLIcu_Row_extract( Y, MA, ht, len, iRow ) MLIcuRow_extract( Y, (MA)[0], ht, len, iRow )
#define MLIcu_Col_extract( Y, MA, ht, len, iCol ) MLIcuCol_extract( Y, (MA)[0], ht, len, iCol )
#define MLIcu_Dia_extract( Y, MA, len )           MLIcuDia_extract( Y, (MA)[0], len )

/**************  Deleting or inserting a row or a column   ***************/

#define MLIcu_Row_delete( MB, MA, htA, lenA, iRow )    MLIcuRow_delete( (MB)[0], (MA)[0], htA, lenA, iRow )
#define MLIcu_Col_delete( MB, MA, htA, lenA, iCol )    MLIcuCol_delete( (MB)[0], (MA)[0], htA, lenA, iCol )
#define MLIcu_Row_insert( MB, MA, htB, lenB, iRow, X ) MLIcuRow_insert( (MB)[0], (MA)[0], htB, lenB, iRow, X )
#define MLIcu_Col_insert( MB, MA, htB, lenB, iCol, X ) MLIcuCol_insert( (MB)[0], (MA)[0], htB, lenB, iCol, X )


/*****************    Basic arithmetic operations *********************
                      performed on one single row,
                      or one single column of any matrix,
                      or on the diagonal of a square matrix

    Note: In contrast to the analogous VectorLib functions, the operations
    are performed in-place, i.e. the input matrix itself is changed  */

#define MLIcu_Row_neg( MA, ht, len, iRow ) MLIcuRow_neg( (MA)[0], ht, len, iRow )
#define MLIcu_Col_neg( MA, ht, len, iCol ) MLIcuCol_neg( (MA)[0], ht, len, iCol )

/******  One-dimensional vector operations **********************
         performed along all rows or all columns simultaneously,
         or along the diagonal of a square matrix                */

#define MLIcu_Rows_max( Y, MA, ht, len )        MLIcuRows_max( Y, (MA)[0], ht, len )
#define MLIcu_Cols_max( Y, MA, ht, len )        MLIcuCols_max( Y, (MA)[0], ht, len )
#define MLIcu_Dia_max(  MA, len )               MLIcuDia_max(  (MA)[0], len )
#define MLIcu_Rows_min( Y, MA, ht, len )        MLIcuRows_min( Y, (MA)[0], ht, len )
#define MLIcu_Cols_min( Y, MA, ht, len )        MLIcuCols_min( Y, (MA)[0], ht, len )
#define MLIcu_Dia_min(  MA, len )               MLIcuDia_min(  (MA)[0], len )

#define MLIcu_Rows_rotate( MA, ht, len, pos)           MLIcuRows_rotate( (MA)[0], ht, len, pos )
#define MLIcu_Cols_rotate( MA, ht, len, pos)           MLIcuCols_rotate( (MA)[0], ht, len, pos )
#define MLIcu_Rows_rotate_buf( MA, ht, len, pos, MBuf) MLIcuRows_rotate_buf( (MA)[0], ht, len, pos, (MBuf)[0] )
#define MLIcu_Cols_rotate_buf( MA, ht, len, pos, MBuf) MLIcuCols_rotate_buf( (MA)[0], ht, len, pos, (MBuf)[0] )
#define MLIcu_Rows_reflect( MA, ht, len )              MLIcuRows_reflect( (MA)[0], ht, len )
#define MLIcu_Cols_reflect( MA, ht, len )              MLIcuCols_reflect( (MA)[0], ht, len )
#define MLIcu_Rows_rev( MA, ht, len)                   MLIcuRows_rev( (MA)[0], ht, len )
#define MLIcu_Cols_rev( MA, ht, len)                   MLIcuCols_rev( (MA)[0], ht, len )
#define MLIcu_Rows_distribution( MAbund, Limits, nBins, MX, ht, len, mode ) MLIcuRows_distribution( MAbund[0], Limits, nBins, MX[0], ht, len, mode )
#define MLIcu_Cols_distribution( MAbund, Limits, nBins, MX, ht, len, mode ) MLIcuCols_distribution( MAbund[0], Limits, nBins, MX[0], ht, len, mode )

/********  Operations involving two rows or two colums of one matrix  *****/

#define MLIcu_Rows_exchange( MA, ht, len, row1, row2 ) \
                             MLIcuRows_exchange( (MA)[0], ht, len, row1, row2 )
#define MLIcu_Cols_exchange( MA, ht, len, col1, col2 ) \
                             MLIcuCols_exchange( (MA)[0], ht, len, col1, col2 )

/*************** Transposing and rotating a matrix **********************/

#define MLIcu_transpose( MTr, MA, htTr, lenTr )    MLIcutranspose( (MTr)[0], (MA)[0], htTr, lenTr )
       /*  dimensions htTr, lenTr are those of the transposed matrix, not of the original!   */
#define MLIcu_rotate90( MRot, MA, htRot, lenRot )  MLIcurotate90( (MRot)[0], (MA)[0], htRot, lenRot )
#define MLIcu_rotate180( MRot, MA, htRot, lenRot ) VLIcu_rev( (MRot)[0], (MA)[0], (htRot)*(lenRot) )
#define MLIcu_rotate270( MRot, MA, htRot, lenRot ) MLIcurotate270( (MRot)[0], (MA)[0], htRot, lenRot )


/*************************************************************************
 * MLIcu functions (without underbar in the prefix): 	
    (working on matrices in host memory, input type 
	liPMatrix = liVector = pointer to matrix element[0][0], 
	scalar parameters on host and passed by value)
*
 *************************************************************************/

#define MLIcuequ0( MA, ht, len )       VLIcu_equ0( MA, (ht)*(len) )
void   __vf OVCUAPI  MLIcuequ1( liPMatrix MA, ui len );  /* identity matrix */
void   __vf OVCUAPI  MLIcuequm1( liPMatrix MA, ui len );  /* neg. identity matrix */
void   __vf OVCUAPI  MLIcuouterprod( liPMatrix MA, liVector X,  liVector Y, ui ht, ui len );

void   __vf OVCUAPI  MLIcuRow_equ0( liPMatrix MA, ui ht, ui len, ui iRow );
void   __vf OVCUAPI  MLIcuCol_equ0( liPMatrix MA, ui ht, ui len, ui iCol );
void   __vf OVCUAPI  MLIcuDia_equ0( liPMatrix MA, ui len );

void   __vf OVCUAPI  MLIcuRow_equC( liPMatrix MA, ui ht, ui len, ui iRow, long C );
void   __vf OVCUAPI  MLIcuCol_equC( liPMatrix MA, ui ht, ui len, ui iCol, long C );
void   __vf OVCUAPI  MLIcuDia_equC( liPMatrix MA, ui len, long C );

void   __vf OVCUAPI  MLIcuRow_equV( liPMatrix MA, ui ht, ui len, ui iRow, liVector X );
void   __vf OVCUAPI  MLIcuCol_equV( liPMatrix MA, ui ht, ui len, ui iCol, liVector X );
void   __vf OVCUAPI  MLIcuDia_equV( liPMatrix MA, ui len, liVector X );

void   __vf OVCUAPI  MLIcuTrd_equM( liPMatrix MA, liPMatrix MTrd, ui len );
void   __vf OVCUAPI  MLIcuTrd_extract( liPMatrix MTrd, liPMatrix MA, ui len );

#define MLIcuequM( MB, MA, ht, len )      VLIcu_equV( MB, MA, (ht)*(len) )
#define MLIcuneg( MB, MA, ht, len )       VLIcu_neg( MB, MA, (ht)*(len) )
void   __vf OVCUAPI  MLIcuUequL( liPMatrix MA, ui len );
void   __vf OVCUAPI  MLIcuLequU( liPMatrix MA, ui len );

            /* data-type conversions:  */
#define McuLItoUL( MUL, MLI, ht, len ) Vcu_LItoUL( MUL, MLI, (ht)*(len) )
#define McuULtoLI( MLI, MUL, ht, len ) Vcu_ULtoLI( MLI, MUL, (ht)*(len) )
#define McuLItoBI( MBI, MLI, ht, len ) Vcu_LItoBI( MBI, MLI, (ht)*(len) )
#define McuLItoSI( MSI, MLI, ht, len ) Vcu_LItoSI( MSI, MLI, (ht)*(len) )
#define McuLItoI(  MI,  MLI, ht, len ) Vcu_LItoI(  MI,  MLI, (ht)*(len) )
#define McuLItoQI( MQI, MLI, ht, len ) Vcu_LItoQI( MQI, MLI, (ht)*(len) )
#define McuBItoLI( MLI, MBI, ht, len ) Vcu_BItoLI( MLI, MBI, (ht)*(len) )
#define McuSItoLI( MLI, MSI, ht, len ) Vcu_SItoLI( MLI, MSI, (ht)*(len) )
#define McuItoLI(  MLI, MI,  ht, len ) Vcu_ItoLI(  MLI, MI,   (ht)*(len) )
#define McuQItoLI( MLI, MQI, ht, len ) Vcu_QItoLI( MLI, MQI, (ht)*(len) )
#define McuLItoF(  MF,  MLI, ht, len ) Vcu_LItoF(  MF,  MLI, (ht)*(len) )
#define McuLItoD(  MD,  MLI, ht, len ) Vcu_LItoD(  MD,  MLI, (ht)*(len) )

/********  Extracting a submatrix and copying a submatrix back  *********/

void  __vf OVCUAPI  MLIcusubmatrix( liPMatrix MSub, ui subHt,  ui subLen,
                          liPMatrix MSrce, ui srceHt,  ui srceLen,
                          ui firstRowInCol,  ui sampInCol,
                          ui firstColInRow,  ui sampInRow );

void  __vf OVCUAPI  MLIcusubmatrix_equM( liPMatrix MDest, ui destHt, ui destLen,
                               ui firstRowInCol,  ui sampInCol,
                               ui firstColInRow,  ui sampInRow,
                               liPMatrix MSrce, ui srceHt, ui srceLen );

void  __vf OVCUAPI  MLIcuequMblock(  liPMatrix MSub, ui subHt, ui subLen,
                          liPMatrix MSrce, ui srceHt,  ui srceLen,
                          ui firstRowInCol,  ui firstColInRow );

void  __vf OVCUAPI  MLIcublock_equM( liPMatrix MDest, ui destHt, ui destLen,
                          ui firstRowInCol,  ui firstColInRow,
                          liPMatrix MSrce, ui srceHt, ui srceLen );

void  __vf OVCUAPI  MLIcuequMblockT( liPMatrix MSub, ui subHt, ui subLen,
                          liPMatrix MSrce, ui srceHt, ui srceLen,
                          ui firstRowInCol,  ui firstColInRow );

void  __vf OVCUAPI  MLIcublock_equMT( liPMatrix MDest, ui destHt, ui destLen,
                          ui firstRowInCol,  ui firstColInRow,
                          liPMatrix MSrce, ui srceHt, ui srceLen );


/*****   Extracting a single row or a single column or the diagonal  *****
 *       and storing it into a vector                                    */

void __vf OVCUAPI  MLIcuRow_extract( liVector Y, liPMatrix MA, ui ht, ui len, ui iRow );
void __vf OVCUAPI  MLIcuCol_extract( liVector Y, liPMatrix MA, ui ht, ui len, ui iCol );
void __vf OVCUAPI  MLIcuDia_extract( liVector Y, liPMatrix MA, ui len );

/**********  Deleting or inserting a row or a column *****************/

void __vf OVCUAPI  MLIcuRow_delete( liPMatrix MB, liPMatrix MA, ui htA, ui lenA, ui iRow );
void __vf OVCUAPI  MLIcuCol_delete( liPMatrix MB, liPMatrix MA, ui htA, ui lenA, ui iCol );
void __vf OVCUAPI  MLIcuRow_insert( liPMatrix MB, liPMatrix MA, ui htB, ui lenB, ui iRow, liVector X );
void __vf OVCUAPI  MLIcuCol_insert( liPMatrix MB, liPMatrix MA, ui htB, ui lenB, ui iCol, liVector X );


/******  One-dimensional vector operations **********************
         performed along all rows or all columns simultaneously,
         or along the diagonal of a square matrix                */

void   __vf OVCUAPI  MLIcuRows_max( liVector Y, liPMatrix MA, ui ht, ui len );
void   __vf OVCUAPI  MLIcuCols_max( liVector Y, liPMatrix MA, ui ht, ui len );
long  __vf OVCUAPI  MLIcuDia_max(  liPMatrix MA, ui len );
void   __vf OVCUAPI  MLIcuRows_min( liVector Y, liPMatrix MA, ui ht, ui len );
void   __vf OVCUAPI  MLIcuCols_min( liVector Y, liPMatrix MA, ui ht, ui len );
long  __vf OVCUAPI  MLIcuDia_min(  liPMatrix MA, ui len );

void  __vf OVCUAPI  MLIcuRows_rotate( liPMatrix MA, ui ht, ui len, ssize_t pos );
void  __vf OVCUAPI  MLIcuCols_rotate( liPMatrix MA, ui ht, ui len, ssize_t pos );
void  __vf OVCUAPI  MLIcuRows_rotate_buf( liPMatrix MA, ui ht, ui len, ssize_t pos, liPMatrix MBuf );
void  __vf OVCUAPI  MLIcuCols_rotate_buf( liPMatrix MA, ui ht, ui len, ssize_t pos, liPMatrix MBuf );
void  __vf OVCUAPI  MLIcuRows_reflect( liPMatrix MA, ui ht, ui len );
void  __vf OVCUAPI  MLIcuCols_reflect( liPMatrix MA, ui ht, ui len );
void  __vf OVCUAPI  MLIcuRows_rev( liPMatrix MA, ui ht, ui len );
void  __vf OVCUAPI  MLIcuCols_rev( liPMatrix MA, ui ht, ui len );
void  __vf OVCUAPI  MLIcuRows_distribution( uiPMatrix MAbund, liVector Limits, ui nBins, liPMatrix MX, ui ht, ui len, int mode );
void  __vf OVCUAPI  MLIcuCols_distribution( uiPMatrix MAbund, liVector Limits, ui nBins, liPMatrix MX, ui ht, ui len, int mode );

/********  Operations involving two rows or two colums of one matrix  *****/

void   __vf OVCUAPI  MLIcuRows_exchange( liPMatrix MA, ui ht, ui len, ui i1, ui i2 );
void   __vf OVCUAPI  MLIcuCols_exchange( liPMatrix MA, ui ht, ui len, ui i1, ui i2 );


/***************  Transposing and rotating a matrix **********************/

void  __vf OVCUAPI  MLIcutranspose( liPMatrix MTr, liPMatrix MA,  ui htTr, ui lenTr );
void  __vf OVCUAPI  MLIcurotate90(  liPMatrix MRot, liPMatrix MA, ui htRot, ui lenRot );
#define     MLIcurotate180( MRot, MA, htRot, lenRot )  VLIcu_rev( MRot, MA, (htRot)*(lenRot) )
void  __vf OVCUAPI  MLIcurotate270( liPMatrix MRot, liPMatrix MA, ui htRot, ui lenRot );

#ifdef __cplusplus
} // end of extern "C"
#endif
#endif  /*  __MLISTD_H  */
