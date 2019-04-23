/*  cudaMQIstd.h

  matrix management functions:
  manipulations on matrices of data type "quad" (64-bit integer)

  This file declares the functions with the name variants 
	cudaMQI_func	(working on matrices in device memory, input type qiMatrix, scalar parameters reside on host and are passed by value)
	cusdMQI_func	(as cudaMQI_func except scalar parameters reside on device and are passed by address)
	cudaMQIfunc		(as cudaMQI_func, but input type qiPMatrix = qiVector = pointer to matrix element[0][0])
	cusdMQIfunc		(as cusdMQI_func, but input type qiPMatrix = qiVector = pointer to matrix element[0][0])
	MQIcu_func		(working on matrices in host memory, input type qiMatrix, scalar parameters on host and passed by value)
	MQIcufunc		(as MQIcu_func, but input type qiPMatrix = qiVector = pointer to matrix element[0][0])
  where func is the respective function.

   Copyright (c) 1996-2017 by OptiCode - Dr. Martin Sander Software Dev.
  All Rights Reserved.

*/

#if !defined( __CUDAMQISTD_H )
#define __CUDAMQISTD_H
#if !defined( __CUDAMATLIB_H )
#include <cudaMatLib.h>
#endif
#if !defined( __CUDAVQISTD_H )
#include <cudaVQIstd.h>
#endif
#if !defined( __CUDAVQIMATH_H )
#include <cudaVQImath.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif

/**** Generation of matrices on device memory and on pinned host memory *******************/

qiMatrix  __vf cudaMQI_matrix( ui ht, ui len );   /* allocates a vector on device memory */
qiMatrix  __vf cudaMQI_matrix0( ui ht, ui len );
 /* The following functions allocate device-accessible, "pinned" memory on the host.
	This memory is mapped onto the device memory space. The resulting device address is returned.
	The matrix can be accessed either by its host address "hostPtr" e.g., MQI_equ1( hostPtr, ht, len );
	or by its device address , e.g., cudaMQI_equ1( devicePtr, ht, len );                             */
qiMatrix  __vf cudaMQI_pinnedMatrix(  qiMatrix *hostPtr, ui ht, ui len ); 
qiMatrix  __vf cudaMQI_pinnedMatrix0( qiMatrix *hostPtr, ui ht, ui len );

/*************************************************************************
 * Declarations of the functions written without underbar in the prefix: *
 *	cudaMQIfunc  (input type 
                   qiPMatrix = qiVector = pointer to matrix element[0][0])
 *	cusdMQIfunc  (input type 
                   qiPMatrix = qiVector = pointer to matrix element[0][0])
 *************************************************************************/

void  __vcuf OVCUAPI  cudaMQIsetElement( qiPMatrix X, ui ht, ui len, ui m, ui n, quad C );
void  __vcuf OVCUAPI  cusdMQIsetElement( qiPMatrix X, ui ht, ui len, ui m, ui n, quad *d_C );
void  __vcuf OVCUAPI  cudaMQIgetElement( quad *h_y, qiPMatrix X, ui ht, ui len, ui m, ui n );
void  __vcuf OVCUAPI  cusdMQIgetElement( quad *d_y, qiPMatrix X, ui ht, ui len, ui m, ui n );
quad  __vcuf OVCUAPI  cudaMQIelement( qiPMatrix X, ui ht, ui len, ui m, ui n );
quad * __vcuf OVCUAPI cudaMQIPelement( qiPMatrix X, ui ht, ui len, ui m, ui n );

#define cudaMQIequ0( MA, ht, len )            cudaVQI_equ0( MA, (ht)*(len) )
overror_t   __vcuf OVCUAPI  cudaMQIequ1( qiPMatrix MA, ui len );  /* identity matrix */
overror_t   __vcuf OVCUAPI  cudaMQIequm1( qiPMatrix MA, ui len );  /* neg. identity matrix */
overror_t   __vcuf OVCUAPI  cudaMQIouterprod( qiPMatrix MA, qiVector X,  qiVector Y, ui ht, ui len );

overror_t   __vcuf OVCUAPI  cudaMQIRow_equ0( qiPMatrix MA, ui ht, ui len, ui iRow );
overror_t   __vcuf OVCUAPI  cudaMQICol_equ0( qiPMatrix MA, ui ht, ui len, ui iCol );
overror_t   __vcuf OVCUAPI  cudaMQIDia_equ0( qiPMatrix MA, ui len );

overror_t   __vcuf OVCUAPI  cudaMQIRow_equC( qiPMatrix MA, ui ht, ui len, ui iRow, quad C );
overror_t   __vcuf OVCUAPI  cudaMQICol_equC( qiPMatrix MA, ui ht, ui len, ui iCol, quad C );
overror_t   __vcuf OVCUAPI  cudaMQIDia_equC( qiPMatrix MA, ui len, quad C );
overror_t   __vcuf OVCUAPI  cusdMQIRow_equC( qiPMatrix MA, ui ht, ui len, ui iRow, quad *d_C );
overror_t   __vcuf OVCUAPI  cusdMQICol_equC( qiPMatrix MA, ui ht, ui len, ui iCol, quad *d_C );
overror_t   __vcuf OVCUAPI  cusdMQIDia_equC( qiPMatrix MA, ui len, quad *d_C );

overror_t   __vcuf OVCUAPI  cudaMQIRow_equV( qiPMatrix MA, ui ht, ui len, ui iRow, qiVector X );
overror_t   __vcuf OVCUAPI  cudaMQICol_equV( qiPMatrix MA, ui ht, ui len, ui iCol, qiVector X );
overror_t   __vcuf OVCUAPI  cudaMQIDia_equV( qiPMatrix MA, ui len, qiVector X );

overror_t   __vcuf OVCUAPI  cudaMQITrd_equM( qiPMatrix MA, qiPMatrix MTrd, ui len );
overror_t   __vcuf OVCUAPI  cudaMQITrd_extract( qiPMatrix MTrd, qiPMatrix MA, ui len );

#define cudaMQIequM( MB, MA, ht, len )         cudaVQI_equV( MB, MA, (ht)*(len) )
#define cudaMQIequMhost( d_MB, h_MA, ht, len ) cudaVQI_equVhost( d_MB, h_MA, (ht)*(len) )
#define MQIequMdevice( h_MB, d_MA, ht, len )   VQI_equVdevice( h_MB, d_MA, (ht)*(len) )
#define cudaMQIneg( MB, MA, ht, len )          cudaVQI_neg( MB, MA, (ht)*(len) )
overror_t   __vcuf OVCUAPI  cudaMQIUequL( qiPMatrix MA, ui len );
overror_t   __vcuf OVCUAPI  cudaMQILequU( qiPMatrix MA, ui len );

            /* data-type conversions:  */
#ifdef _WIN64
	#define cudaMQItoUQ( MUQ, MQI, ht, len ) cudaV_QItoUQ( (MUQ), (MQI), (ht)*(len) )
	#define cudaMUQtoQI( MQI, MUQ, ht, len ) cudaV_UQtoQI( (MQI), (MUQ), (ht)*(len) )
#endif
#define cudaMQItoBI( MBI, MQI, ht, len ) cudaV_QItoBI( (MBI), (MQI), (ht)*(len) )
#define cudaMQItoSI( MSI, MQI, ht, len ) cudaV_QItoSI( (MSI), (MQI), (ht)*(len) )
#define cudaMQItoI(  MI,  MQI, ht, len ) cudaV_QItoI(  (MI),  (MQI), (ht)*(len) )
#define cudaMQItoLI( MLI, MQI, ht, len ) cudaV_QItoLI( (MLI), (MQI), (ht)*(len) )
#define cudaMBItoQI( MQI, MBI, ht, len ) cudaV_BItoQI( (MQI), (MBI), (ht)*(len) )
#define cudaMSItoQI( MQI, MSI, ht, len ) cudaV_SItoQI( (MQI), (MSI), (ht)*(len) )
#define cudaMItoQI(  MQI, MI,  ht, len ) cudaV_ItoQI(  (MQI), (MI),  (ht)*(len) )
#define cudaMLItoQI( MQI, MLI, ht, len ) cudaV_LItoQI( (MQI), (MLI), (ht)*(len) )
#define cudaMQItoF(  MF,  MQI, ht, len ) cudaV_QItoF(  (MF),  (MQI), (ht)*(len) )
#define cudaMQItoD(  MD,  MQI, ht, len ) cudaV_QItoD(  (MD),  (MQI), (ht)*(len) )

/********  Extracting a submatrix and copying a submatrix back  *********/

overror_t  __vcuf OVCUAPI  cudaMQIsubmatrix( qiPMatrix MSub, ui subHt,  ui subLen,
                          qiPMatrix MSrce, ui srceHt,  ui srceLen,
                          ui firstRowInCol,  ui sampInCol,
                          ui firstColInRow,  ui sampInRow );

overror_t  __vcuf OVCUAPI  cudaMQIsubmatrix_equM( qiPMatrix MDest, ui destHt, ui destLen,
                               ui firstRowInCol,  ui sampInCol,
                               ui firstColInRow,  ui sampInRow,
                               qiPMatrix MSrce,  ui srceHt, ui srceLen );

overror_t  __vcuf OVCUAPI  cudaMQIequMblock(  qiPMatrix MSub,  ui subHt,  ui subLen,
                          qiPMatrix MSrce, ui srceHt,  ui srceLen,
                          ui firstRowInCol,  ui firstColInRow );

overror_t  __vcuf OVCUAPI  cudaMQIblock_equM( qiPMatrix MDest,  ui destHt,  ui destLen,
                          ui firstRowInCol,  ui firstColInRow,
                          qiPMatrix MSrce,  ui srceHt, ui srceLen );

overror_t  __vcuf OVCUAPI  cudaMQIequMblockT( qiPMatrix MSub,  ui subHt, ui subLen,
                          qiPMatrix MSrce,  ui srceHt,  ui srceLen,
                          ui firstRowInCol,  ui firstColInRow );

overror_t  __vcuf OVCUAPI  cudaMQIblock_equMT( qiPMatrix MDest,  ui destHt,  ui destLen,
                          ui firstRowInCol,  ui firstColInRow,
                          qiPMatrix MSrce,   ui srceHt,  ui srceLen );


/*****   Extracting a single row or a single column or the diagonal  *****
 *       and storing it into a vector                                    */

overror_t __vcuf OVCUAPI  cudaMQIRow_extract( qiVector Y, qiPMatrix MA, ui ht, ui len, ui iRow );
overror_t __vcuf OVCUAPI  cudaMQICol_extract( qiVector Y, qiPMatrix MA, ui ht, ui len, ui iCol );
overror_t __vcuf OVCUAPI  cudaMQIDia_extract( qiVector Y, qiPMatrix MA, ui len );


/**********  Deleting or inserting a row or a column *****************/

overror_t __vcuf OVCUAPI  cudaMQIRow_delete( qiPMatrix MB, qiPMatrix MA, ui htA, ui lenA, ui iRow );
overror_t __vcuf OVCUAPI  cudaMQICol_delete( qiPMatrix MB, qiPMatrix MA, ui htA, ui lenA, ui iCol );
overror_t __vcuf OVCUAPI  cudaMQIRow_insert( qiPMatrix MB, qiPMatrix MA, ui htB, ui lenB, ui iRow, qiVector X );
overror_t __vcuf OVCUAPI  cudaMQICol_insert( qiPMatrix MB, qiPMatrix MA, ui htB, ui lenB, ui iCol, qiVector X );


/******  One-dimensional vector operations **********************
         performed along all rows or all columns simultaneously,
         or along the diagonal of a square matrix                */

overror_t  __vcuf OVCUAPI  cudaMQIRows_max( qiVector Y, qiPMatrix MA, ui ht, ui len );
overror_t  __vcuf OVCUAPI  cudaMQICols_max( qiVector Y, qiPMatrix MA, ui ht, ui len );
overror_t  __vcuf OVCUAPI  cudaMQIDia_max(  quad *h_RetVal, qiPMatrix MA, ui len );
overror_t  __vcuf OVCUAPI  cusdMQIDia_max(  quad *d_RetVal, qiPMatrix MA, ui len );
overror_t  __vcuf OVCUAPI  cudaMQIRows_min( qiVector Y, qiPMatrix MA, ui ht, ui len );
overror_t  __vcuf OVCUAPI  cudaMQICols_min( qiVector Y, qiPMatrix MA, ui ht, ui len );
overror_t  __vcuf OVCUAPI  cudaMQIDia_min(  quad *h_RetVal, qiPMatrix MA, ui len );
overror_t  __vcuf OVCUAPI  cusdMQIDia_min(  quad *d_RetVal, qiPMatrix MA, ui len );

overror_t  __vcuf OVCUAPI  cudaMQIRows_rotate( qiPMatrix MA, ui ht, ui len, ssize_t pos );
overror_t  __vcuf OVCUAPI  cudaMQICols_rotate( qiPMatrix MA, ui ht, ui len, ssize_t pos );
overror_t  __vcuf OVCUAPI  cudaMQIRows_rotate_buf( qiPMatrix MA, ui ht, ui len, ssize_t pos, qiPMatrix MBuf );
overror_t  __vcuf OVCUAPI  cudaMQICols_rotate_buf( qiPMatrix MA, ui ht, ui len, ssize_t pos, qiPMatrix MBuf );
overror_t  __vcuf OVCUAPI  cudaMQIRows_reflect( qiPMatrix MA, ui ht, ui len );
overror_t  __vcuf OVCUAPI  cudaMQICols_reflect( qiPMatrix MA, ui ht, ui len );
overror_t  __vcuf OVCUAPI  cudaMQIRows_rev( qiPMatrix MA, ui ht, ui len );
overror_t  __vcuf OVCUAPI  cudaMQICols_rev( qiPMatrix MA, ui ht, ui len );
overror_t  __vcuf OVCUAPI  cudaMQIRows_distribution( uiPMatrix MAbund, qiVector Limits, ui nBins, qiPMatrix MX, ui ht, ui len, int mode );
overror_t  __vcuf OVCUAPI  cudaMQICols_distribution( uiPMatrix MAbund, qiVector Limits, ui nBins, qiPMatrix MX, ui ht, ui len, int mode );

/********  Operations involving two rows or two colums of one matrix  *****/

overror_t   __vcuf OVCUAPI  cudaMQIRows_exchange( qiPMatrix MA, ui ht, ui len, ui i1, ui i2 );
overror_t   __vcuf OVCUAPI  cudaMQICols_exchange( qiPMatrix MA, ui ht, ui len, ui i1, ui i2 );

/*****************  Transposing and rotating a matrix **********************/

overror_t  __vcuf OVCUAPI  cudaMQItranspose( qiPMatrix MTr, qiPMatrix MA, ui htTr, ui lenTr );
#define     cudaMQIrotate180( MRot, MA, htRot, lenRot )  cudaVQI_rev( MRot, MA, (htRot)*(lenRot) )
overror_t  __vcuf OVCUAPI  cudaMQIrotate90(  qiPMatrix MRot, qiPMatrix MA, ui htRot, ui lenRot );
overror_t  __vcuf OVCUAPI  cudaMQIrotate270( qiPMatrix MRot, qiPMatrix MA, ui htRot, ui lenRot );
overror_t  __vcuf OVCUAPI  cudaMQItranspose_buf( qiPMatrix MTr, qiPMatrix MA, ui htTr, ui lenTr, qiPMatrix MBuf );

/**************************  Input and Output  **************************
	The input/output functions involve memory transfers from device
	to host memory or vice versa. The generic cudaMQI_input/output functions
	allocate their own host buffers, whereas the cudaMQI_xxx_buf functions
	take a user-supplied buffer vector h_Wk (size must be >= ht*len )
	and are much more efficient.                                       */

#if !(((defined __BORLANDC__) && (__BORLANDC__ < 0x570)) || ((defined _MSC_VER) && (_MSC_VER < 1400)))
		/* modern compiler versions:  */
	overror_t __vf cudaMQIfprint( FILE *stream, qiPMatrix MA, ui ht, ui len, unsigned linewidth );
	overror_t __vf cudaMQIcprint( qiPMatrix MA, ui ht, ui len );
	#define cudaMQIprint( MA, ht, len )  cudaMQIfprint( stdout, MA, ht, len, 80 )
	overror_t __vf cudaMQIfprint_buf( FILE *stream, qiPMatrix MA, ui ht, ui len, unsigned linewidth, qiVector h_Wk );
	overror_t __vf cudaMQIcprint_buf( qiPMatrix MA, ui ht, ui len, qiVector h_Wk );
	#define cudaMQIprint_buf( MA, ht, len, h_Wk )  cudaMQIfprint_buf( stdout, MA, ht, len, 80, h_Wk )
	overror_t __vf cudaMQIwrite( FILE *stream, qiPMatrix X, ui ht, ui len  );
	overror_t __vf cudaMQIwrite_buf( FILE *stream, qiPMatrix X, ui ht, ui len, qiVector h_Wk );
#else /* older compiler versions need separate implementation */
	overror_t __vf cudaMQIfprint1( FILE *stream, qiPMatrix MA, ui ht, ui len, unsigned linewidth );
	overror_t __vf cudaMQIcprint1( qiPMatrix MA, ui ht, ui len );
	#define cudaMQIprint( MA, ht, len )  cudaMQIfprint1( stdout, MA, ht, len, 80 )
	overror_t __vf cudaMQIfprint1_buf( FILE *stream, qiPMatrix MA, ui ht, ui len, unsigned linewidth, qiVector h_Wk );
	overror_t __vf cudaMQIcprint1_buf( qiPMatrix MA, ui ht, ui len, qiVector h_Wk );
	#define cudaMQIprint_buf( MA, ht, len, h_Wk )  cudaMQIfprint1_buf( stdout, MA, ht, len, 80, h_Wk )
	overror_t __vf cudaMQIwrite1( FILE *stream, qiPMatrix X, ui ht, ui len  );
	overror_t __vf cudaMQIwrite1_buf( FILE *stream, qiPMatrix X, ui ht, ui len, qiVector h_Wk );
	#define cudaMQIfprint cudaMQIfprint1
	#define cudaMQIcprint cudaMQIcprint1
	#define cudaMQIfprint_buf cudaMQIfprint1_buf
	#define cudaMQIcprint_buf cudaMQIcprint1_buf
	#define cudaMQIwrite cudaMQIwrite1
	#define cudaMQIwrite_buf cudaMQIwrite1_buf
#endif
#if !(((defined __BORLANDC__) && (__BORLANDC__ < 0x600)))
	overror_t __vf cudaMQIread( qiPMatrix X, ui ht, ui len, FILE *stream );
	overror_t __vf cudaMQIread_buf( qiPMatrix X, ui ht, ui len, FILE *stream, qiVector h_Wk );
#else
	overror_t __vf cudaMQIread1( qiPMatrix X, ui ht, ui len, FILE *stream );
	overror_t __vf cudaMQIread1_buf( qiPMatrix X, ui ht, ui len, FILE *stream, qiVector h_Wk );
	#define cudaMQIread     cudaMQIread1
	#define cudaMQIread_buf cudaMQIread1_buf
#endif

#define cudaMQIstore( str, MA, ht, len ) cudaVQI_store( str, MA, (len)*(ht) )
#define cudaMQIrecall( MA, ht, len, str) cudaVQI_recall( MA, (len)*(ht), str)
#define cudaMQIstore_buf( str, MA, ht, len, h_Wk ) cudaVQI_store( str, MA, (len)*(ht), h_Wk )
#define cudaMQIrecall_buf( MA, ht, len, str, h_Wk) cudaVQI_recall( MA, (len)*(ht), str, h_Wk)



/***************************************************************************
    cudaMQI_func	(working on matrices in device memory, input type qiMatrix, 
	             scalar parameters reside on host and are passed by value)
    cusdMQI_func	(as cudaMQI_func except scalar parameters reside on device 
	             and are passed by address)                                 */


/***************************************************************************
 *  The following definitions are needed to access individual elements,    *
 *  and row pointers. As all addresses point to device memory, the usual   *
 *  mechanism of accessing elements, i.e., writing something like MA[m][n] *
 *  is not possible here!                                                  *
 *  Pro forma, the distinction between the data types qiMatrix and         *
 *  qiPMatrix is kept. However, in the present implementation, both of     *
 *  these types actually contain a pointer to the matrix element [0][0].   *
 *  For C++, inline functions ensure proper type checking at compile time, *
 *  while for plain-C, only a less safe type-cast is possible.             *
 ***************************************************************************/

#ifdef __cplusplus

inline void    cudaMQI_setElement( qiMatrix MA, ui ht, ui len, ui m, ui n, quad C )
	{	cudaMQIsetElement( (qiPMatrix)(MA), ht, len, m, n, C );}
inline void    cusdMQI_setElement( qiMatrix MA, ui ht, ui len, ui m, ui n, quad *d_C )
	{	cusdMQIsetElement( (qiPMatrix)(MA), ht, len, m, n, d_C );}
inline void    cudaMQI_getElement( quad *y, qiMatrix MA, ui ht, ui len, ui m, ui n )
	{	cudaMQIgetElement( y, (qiPMatrix)(MA), ht, len, m, n );}
inline void    cusdMQI_getElement( quad *d_y, qiMatrix MA, ui ht, ui len, ui m, ui n )
	{	cusdMQIgetElement( d_y, (qiPMatrix)(MA), ht, len, m, n );}
inline quad * cudaMQI_Pelement( qiMatrix MA, ui ht, ui len, ui m, ui n )
	{	return cudaMQIPelement( (qiPMatrix)(MA), ht, len, m, n );}
inline quad   cudaMQI_element( qiMatrix MA, ui ht, ui len, ui m, ui n )
{	return cudaMQIelement( (qiPMatrix)(MA), ht, len, m, n );}

inline overror_t  cudaMQI_equ0( qiMatrix MA, ui ht, ui len )
	{	return cudaVQI_equ0( (qiPMatrix)MA, (ht)*(len) ); }
inline overror_t  cudaMQI_equ1( qiMatrix MA, ui len )
	{	return cudaMQIequ1( (qiPMatrix)(MA), len );} /* identity matrix */
inline overror_t  cudaMQI_equm1( qiMatrix MA, ui len )
	{	return cudaMQIequm1( (qiPMatrix)(MA), len );} /* neg. identity matrix */

inline overror_t  cudaMQI_randomLC( qiMatrix MA, ui ht, ui len, long seed, quad MinVal, quad MaxVal, V_RANDOMLCSTATE *h_state )
	{	return cudaVQI_randomLC( (qiPMatrix)(MA), (ht)*(len), seed, MinVal, MaxVal, h_state );}
inline overror_t  cudaMQI_random( qiMatrix MA, ui ht, ui len, long seed, quad MinVal, quad MaxVal )
	{	return cudaVQI_random( (qiPMatrix)(MA), (ht)*(len), seed, MinVal, MaxVal );}
inline overror_t  cusdMQI_randomLC( qiMatrix MA, ui ht, ui len, long seed, quad *d_MinVal, quad *d_MaxVal, V_RANDOMLCSTATE *h_state )
	{	return cusdVQI_randomLC( (qiPMatrix)(MA), (ht)*(len), seed, d_MinVal, d_MaxVal, h_state );}
inline overror_t  cusdMQI_random( qiMatrix MA, ui ht, ui len, long seed, quad *d_MinVal, quad *d_MaxVal )
	{	return cusdVQI_random( (qiPMatrix)(MA), (ht)*(len), seed, d_MinVal, d_MaxVal );}
inline overror_t  cudaMQI_outerprod( qiMatrix MA, qiVector X,  qiVector Y, ui ht, ui len )
{	return cudaMQIouterprod( (qiPMatrix)(MA), X, Y, ht, len );}

inline overror_t  cudaMQI_Row_equ0( qiMatrix MA, ui ht, ui len, ui iRow )
	{	return cudaMQIRow_equ0( (qiPMatrix)MA, ht, len, iRow );}
inline overror_t  cudaMQI_Col_equ0( qiMatrix MA, ui ht, ui len, ui iRow )
	{	return cudaMQICol_equ0( (qiPMatrix)MA, ht, len, iRow );}
inline overror_t  cudaMQI_Dia_equ0( qiMatrix MA, ui len )
	{	return cudaMQIDia_equ0( (qiPMatrix)(MA), len );}

inline overror_t  cudaMQI_Row_equC( qiMatrix MA, ui ht, ui len, ui iRow, quad C )
	{	return cudaMQIRow_equC( (qiPMatrix)MA, ht, len, iRow, C );}
inline overror_t  cudaMQI_Col_equC( qiMatrix MA, ui ht, ui len, ui iRow, quad C )
	{	return cudaMQICol_equC( (qiPMatrix)MA, ht, len, iRow, C );}
inline overror_t  cudaMQI_Dia_equC( qiMatrix MA, ui len, quad C )
	{	return cudaMQIDia_equC( (qiPMatrix)(MA), len, C );}

inline overror_t  cusdMQI_Row_equC( qiMatrix MA, ui ht, ui len, ui iRow, quad *d_C )
	{	return cusdMQIRow_equC( (qiPMatrix)MA, ht, len, iRow, d_C );}
inline overror_t  cusdMQI_Col_equC( qiMatrix MA, ui ht, ui len, ui iRow, quad *d_C )
	{	return cusdMQICol_equC( (qiPMatrix)MA, ht, len, iRow, d_C );}
inline overror_t  cusdMQI_Dia_equC( qiMatrix MA, ui len, quad *d_C )
	{	return cusdMQIDia_equC( (qiPMatrix)(MA), len, d_C );}

inline overror_t  cudaMQI_Row_equV( qiMatrix MA, ui ht, ui len, ui iRow, qiVector X )
	{	return cudaMQIRow_equV( (qiPMatrix)MA, ht, len, iRow, X );}
inline overror_t  cudaMQI_Col_equV( qiMatrix MA, ui ht, ui len, ui iRow, qiVector X )
	{	return cudaMQICol_equV( (qiPMatrix)MA, ht, len, iRow, X );}
inline overror_t  cudaMQI_Dia_equV( qiMatrix MA, ui len, qiVector X )
	{	return cudaMQIDia_equV( (qiPMatrix)(MA), len, X );}

inline overror_t  cudaMQI_Trd_equM( qiMatrix MA, qiMatrix MTrd, ui len )
	{	return cudaMQITrd_equM( (qiPMatrix)(MA), (qiPMatrix)(MTrd), len );}
inline overror_t  cudaMQI_Trd_extract( qiMatrix MTrd, qiMatrix MA, ui len )
	{	return cudaMQITrd_extract( (qiPMatrix)(MTrd), (qiPMatrix)(MA), len );}

inline overror_t cudaMQI_equM( qiMatrix MB, qiMatrix MA, ui ht, ui len )
	{	return cudaVQI_equV( (qiPMatrix)MB, (qiPMatrix)MA, (ht)*(len) );}
inline overror_t cudaMQI_equMhost( qiMatrix d_MB, qiMatrix h_MA, ui ht, ui len )
	{	return cudaVQI_equVhost( (qiPMatrix)d_MB, (h_MA)[0], (ht)*(len) );}
inline overror_t MQI_equMdevice( qiMatrix h_MB, qiMatrix d_MA, ui ht, ui len )
	{	return VQI_equVdevice( h_MB[0], (qiPMatrix)d_MA, (ht)*(len) );}
inline overror_t cudaMQI_neg( qiMatrix MB, qiMatrix MA, ui ht, ui len )
	{	return cudaVQI_neg( (qiPMatrix)(MB), (qiPMatrix)(MA), (ht)*(len) );}
inline overror_t  cudaMQI_UequL( qiMatrix MA, ui len )
	{	return cudaMQIUequL( (qiPMatrix)(MA), len );}
inline overror_t  cudaMQI_LequU( qiMatrix MA, ui len )
	{	return cudaMQILequU( (qiPMatrix)(MA), len );}

/************** Data-type interconversions  ****************************/

#ifdef _WIN64
	inline overror_t cudaM_UQtoQI( qiMatrix MQI, ubMatrix MUQ, ui ht, ui len )
		{	return cudaV_UQtoQI( (qiVector)MQI, (uqVector)MUQ, (ht)*(len) );}
#endif
inline overror_t cudaM_BItoQI( qiMatrix MQI, biMatrix MBI, ui ht, ui len )
	{	return cudaV_BItoQI( (qiVector)MQI, (biVector)MBI, (ht)*(len) );}
inline overror_t cudaM_SItoQI( qiMatrix MQI, siMatrix MSI, ui ht, ui len )
	{	return cudaV_SItoQI( (qiVector)MQI, (siVector)MSI, (ht)*(len) );}
inline overror_t cudaM_ItoQI(  qiMatrix MQI, iMatrix MI,  ui ht, ui len )
	{	return cudaV_ItoQI(  (qiVector)MQI, (iVector)MI,   (ht)*(len) );}
inline overror_t cudaM_LItoQI( qiMatrix MQI, liMatrix MLI, ui ht, ui len )
	{	return cudaV_LItoQI( (qiVector)MQI, (liVector)MLI, (ht)*(len) );}
inline overror_t cudaM_QItoF(  fMatrix MF,  qiMatrix MQI, ui ht, ui len )
	{	return cudaV_QItoF(  (fVector)MF,   (qiVector)MQI, (ht)*(len) );}
inline overror_t cudaM_QItoD(  dMatrix MD,  qiMatrix MQI, ui ht, ui len )
	{	return cudaV_QItoD(  (dVector)MD,   (qiVector)MQI, (ht)*(len) );}

/********  Extracting a submatrix and copying a submatrix back  *********/

inline overror_t cudaMQI_submatrix( qiMatrix MSub, ui subHt, ui subLen, qiMatrix MSrce, ui srceHt, ui srceLen,
                      ui firstRowInCol, ui sampInCol, ui firstColInRow, ui sampInRow )
	{	return cudaMQIsubmatrix(  (qiPMatrix)(MSub), subHt, subLen,
		                         (qiPMatrix)(MSrce), srceHt, srceLen,
								 firstRowInCol, sampInCol, firstColInRow, sampInRow ); }

inline overror_t cudaMQI_submatrix_equM( qiMatrix MDest, ui destHt, ui destLen,
                           ui firstRowInCol, ui sampInCol, ui firstColInRow, ui sampInRow,
                           qiMatrix MSrce, ui srceHt, ui srceLen )
	{	return cudaMQIsubmatrix_equM(  (qiPMatrix)(MDest), destHt, destLen,
                             firstRowInCol, sampInCol, firstColInRow, sampInRow,
							 (qiPMatrix)(MSrce), srceHt, srceLen );}

inline overror_t cudaMQI_equMblock( qiMatrix MSub, ui subHt, ui subLen, qiMatrix MSrce, ui srceHt, ui srceLen,
                      ui firstRowInCol, ui firstColInRow )
{	return cudaMQIequMblock(  (qiPMatrix)(MSub), subHt, subLen,
						   (qiPMatrix)(MSrce), srceHt, srceLen, firstRowInCol, firstColInRow );}

inline overror_t cudaMQI_block_equM( qiMatrix MDest, ui destHt, ui destLen,
                       ui firstRowInCol, ui firstColInRow,
                       qiMatrix MSrce, ui srceHt, ui srceLen )
	{	return cudaMQIblock_equM( (qiPMatrix)(MDest), destHt, destLen,
                             firstRowInCol, firstColInRow,
							 (qiPMatrix)(MSrce), srceHt, srceLen );}

inline overror_t cudaMQI_equMblockT( qiMatrix MSub, ui subHt, ui subLen, qiMatrix MSrce, ui srceHt, ui srceLen,
                      ui firstRowInCol, ui firstColInRow )
	{	return cudaMQIequMblockT(  (qiPMatrix)(MSub), subHt, subLen,
                             (qiPMatrix)(MSrce), srceHt, srceLen,
							 firstRowInCol, firstColInRow );}

inline overror_t cudaMQI_block_equMT( qiMatrix MDest, ui destHt, ui destLen,
                       ui firstRowInCol, ui firstColInRow,
                       qiMatrix MSrce, ui srceHt, ui srceLen )
	{	return cudaMQIblock_equMT( (qiPMatrix)(MDest), destHt, destLen,
                             firstRowInCol, firstColInRow,
							 (qiPMatrix)(MSrce), srceHt, srceLen );}

/*****   Extracting a single row or a single column or the diagonal  ******
 *       and storing it into a vector                                     */

inline overror_t cudaMQI_Row_extract( qiVector Y, qiMatrix MA, ui ht, ui len, ui iRow ) 
	{	return cudaMQIRow_extract( Y, (qiPMatrix)(MA), ht, len, iRow );}
inline overror_t cudaMQI_Col_extract( qiVector Y, qiMatrix MA, ui ht, ui len, ui iCol ) 
	{	return cudaMQICol_extract( Y, (qiPMatrix)(MA), ht, len, iCol );}
inline overror_t cudaMQI_Dia_extract( qiVector Y, qiMatrix MA, ui len )
	{	return cudaMQIDia_extract( Y, (qiPMatrix)(MA), len );}

/**************  Deleting or inserting a row or a column   ***************/

inline overror_t cudaMQI_Row_delete( qiMatrix MB, qiMatrix MA, ui htA, ui lenA, ui iRow )
	{	return cudaMQIRow_delete( (qiPMatrix)(MB), (qiPMatrix)(MA), htA, lenA, iRow );}
inline overror_t cudaMQI_Col_delete( qiMatrix MB, qiMatrix MA, ui htA, ui lenA, ui iCol )
	{	return cudaMQICol_delete( (qiPMatrix)(MB), (qiPMatrix)(MA), htA, lenA, iCol );}
inline overror_t cudaMQI_Row_insert( qiMatrix MB, qiMatrix MA, ui htB, ui lenB, ui iRow, qiVector X )
	{	return cudaMQIRow_insert( (qiPMatrix)(MB), (qiPMatrix)(MA), htB, lenB, iRow, X );}
inline overror_t cudaMQI_Col_insert( qiMatrix MB, qiMatrix MA, ui htB, ui lenB, ui iCol, qiVector X )
	{	return cudaMQICol_insert( (qiPMatrix)(MB), (qiPMatrix)(MA), htB, lenB, iCol, X );}


/******  One-dimensional vector operations **********************
         performed along all rows or all columns simultaneously,
         or along the diagonal of a square matrix                */

inline overror_t cudaMQI_Rows_max( qiVector Y, qiMatrix MA, ui ht, ui len )
	{	return cudaMQIRows_max( Y, (qiPMatrix)(MA), ht, len );}
inline overror_t cudaMQI_Cols_max( qiVector Y, qiMatrix MA, ui ht, ui len )
	{	return cudaMQICols_max( Y, (qiPMatrix)(MA), ht, len );}
inline overror_t cudaMQI_Dia_max(  quad *h_RetValPtr, qiMatrix MA, ui len )
	{	return cudaMQIDia_max(  h_RetValPtr, (qiPMatrix)(MA), len );}
inline overror_t cusdMQI_Dia_max(  quad *d_RetValPtr, qiMatrix MA, ui len )
	{	return cusdMQIDia_max(  d_RetValPtr, (qiPMatrix)(MA), len );}
inline overror_t cudaMQI_Rows_min( qiVector Y, qiMatrix MA, ui ht, ui len )
	{	return cudaMQIRows_min( Y, (qiPMatrix)(MA), ht, len );}
inline overror_t cudaMQI_Cols_min( qiVector Y, qiMatrix MA, ui ht, ui len )
	{	return cudaMQICols_min( Y, (qiPMatrix)(MA), ht, len );}
inline overror_t cudaMQI_Dia_min(  quad *h_RetValPtr, qiMatrix MA, ui len )
	{	return cudaMQIDia_min(  h_RetValPtr, (qiPMatrix)(MA), len );}
inline overror_t cusdMQI_Dia_min(  quad *d_RetValPtr, qiMatrix MA, ui len )
	{	return cusdMQIDia_min(  d_RetValPtr, (qiPMatrix)(MA), len );}

inline overror_t cudaMQI_Rows_rotate( qiMatrix MA, ui ht, ui len, ssize_t pos)
	{	return cudaMQIRows_rotate( (qiPMatrix)(MA), ht, len, pos );}
inline overror_t cudaMQI_Cols_rotate( qiMatrix MA, ui ht, ui len, ssize_t pos)
	{	return cudaMQICols_rotate( (qiPMatrix)(MA), ht, len, pos );}
inline overror_t cudaMQI_Rows_rotate_buf( qiMatrix MA, ui ht, ui len, ssize_t pos, qiMatrix MBuf) 
	{	return cudaMQIRows_rotate_buf( (qiPMatrix)(MA), ht, len, pos, (qiPMatrix)(MBuf) );}
inline overror_t cudaMQI_Cols_rotate_buf( qiMatrix MA, ui ht, ui len, ssize_t pos, qiMatrix MBuf) 
	{	return cudaMQICols_rotate_buf( (qiPMatrix)(MA), ht, len, pos, (qiPMatrix)(MBuf) );}
inline overror_t cudaMQI_Rows_reflect( qiMatrix MA, ui ht, ui len )
	{	return cudaMQIRows_reflect( (qiPMatrix)(MA), ht, len );}
inline overror_t cudaMQI_Cols_reflect( qiMatrix MA, ui ht, ui len )
	{	return cudaMQICols_reflect( (qiPMatrix)(MA), ht, len );}
inline overror_t cudaMQI_Rows_rev( qiMatrix MA, ui ht, ui len )
	{	return cudaMQIRows_rev( (qiPMatrix)(MA), ht, len );}
inline overror_t cudaMQI_Cols_rev( qiMatrix MA, ui ht, ui len )
	{	return cudaMQICols_rev( (qiPMatrix)(MA), ht, len );}
inline overror_t  cudaMQI_Rows_distribution( uiMatrix MAbund, qiVector Limits, ui nBins, qiMatrix MX, ui ht, ui len, int mode )
	{	return cudaMQIRows_distribution( (uiPMatrix)MAbund, Limits, nBins, (qiPMatrix)MX, ht, len, mode ); }
inline overror_t  cudaMQI_Cols_distribution( uiMatrix MAbund, qiVector Limits, ui nBins, qiMatrix MX, ui ht, ui len, int mode )
	{	return cudaMQICols_distribution( (uiPMatrix)MAbund, Limits, nBins, (qiPMatrix)MX, ht, len, mode ); }

/********  Operations involving two rows or two colums of one matrix  *****/

inline overror_t cudaMQI_Rows_exchange( qiMatrix MA, ui ht, ui len, ui row1, ui row2 )
	{	return cudaMQIRows_exchange( (qiPMatrix)(MA), ht, len, row1, row2 );}
inline overror_t cudaMQI_Cols_exchange( qiMatrix MA, ui ht, ui len, ui col1, ui col2 )
	{	return cudaMQICols_exchange( (qiPMatrix)(MA), ht, len, col1, col2 );}

/*************** Transposing and rotating a matrix **********************/

inline overror_t cudaMQI_transpose( qiMatrix MTr, qiMatrix MA, ui htTr, ui lenTr )
	{	return cudaMQItranspose( (qiPMatrix)(MTr), (qiPMatrix)(MA), htTr, lenTr );}
       /*  dimensions htTr, lenTr are those of the transposed matrix, not of the original!   */
inline overror_t cudaMQI_rotate90( qiMatrix MRot, qiMatrix MA, ui htRot, ui lenRot )
	{	return cudaMQIrotate90( (qiPMatrix)(MRot), (qiPMatrix)(MA), htRot, lenRot );}
inline overror_t cudaMQI_rotate180( qiMatrix MRot, qiMatrix MA, ui htRot, ui lenRot )
	{	return cudaVQI_rev( (qiPMatrix)(MRot), (qiPMatrix)(MA), (htRot)*(lenRot) );}
inline overror_t cudaMQI_rotate270( qiMatrix MRot, qiMatrix MA, ui htRot, ui lenRot )
	{	return cudaMQIrotate270( (qiPMatrix)(MRot), (qiPMatrix)(MA), htRot, lenRot );}
inline overror_t cudaMQI_transpose_buf( qiMatrix MTr, qiMatrix MA, ui htTr, ui lenTr, qiMatrix MBuf )
	{	return cudaMQItranspose_buf( (qiPMatrix)(MTr), (qiPMatrix)(MA), htTr, lenTr, (qiPMatrix)(MBuf) );}

/**************************  Input and Output  **************************
	The input/output functions involve memory transfers from device
	to host memory or vice versa. The generic cudaMQI_input/output functions
	allocate their own host buffers, whereas the cudaMQI_xxx_buf functions
	take a user-supplied buffer vector h_Wk (size must be >= ht*len )
	and are much more efficient.                                       */

inline overror_t cudaMQI_fprint( FILE *stream, qiMatrix MA, ui ht, ui len, unsigned linewidth )
	{	return cudaMQIfprint( stream, (qiPMatrix)(MA), ht, len, linewidth ); }
inline overror_t cudaMQI_print( qiMatrix MA, ui ht, ui len )
	{	return cudaMQIfprint( stdout, (qiPMatrix)(MA), ht, len, 80 ); }
inline overror_t cudaMQI_cprint( qiMatrix MA, ui ht, ui len )
	{	return cudaMQIcprint( (qiPMatrix)(MA), ht, len ); }
inline overror_t cudaMQI_fprint_buf( FILE *stream, qiMatrix d_MA, ui ht, ui len, unsigned linewidth, qiVector h_Wk )
	{	return cudaMQIfprint_buf( stream, (qiPMatrix)(d_MA), ht, len, linewidth, h_Wk ); }
inline overror_t cudaMQI_print_buf( qiMatrix d_MA, ui ht, ui len, qiVector h_Wk )
	{	return cudaMQIfprint_buf( stdout, (qiPMatrix)(d_MA), ht, len, 80, h_Wk ); }
inline overror_t cudaMQI_cprint_buf( qiMatrix d_MA, ui ht, ui len, qiVector h_Wk )
	{	return cudaMQIcprint_buf( (qiPMatrix)(d_MA), ht, len, h_Wk ); }
		/*  cudaMQI_print, cudaMQI_cprint usable only for console applications! */
inline overror_t  cudaMQI_write( FILE *stream, qiMatrix MA, ui ht, ui len )
	{	return cudaMQIwrite( stream, (qiPMatrix)(MA), ht, len ); }
inline overror_t cudaMQI_read( qiMatrix MA, ui ht, ui len, FILE *stream )
	{	return cudaMQIread( (qiPMatrix)(MA), ht, len, stream ); }
inline overror_t  cudaMQI_write_buf( FILE *stream, qiMatrix d_MA, ui ht, ui len, qiVector h_Wk )
	{	return cudaMQIwrite_buf( stream, (qiPMatrix)(d_MA), ht, len, h_Wk ); }
inline overror_t cudaMQI_read_buf( qiMatrix d_MA, ui ht, ui len, FILE *stream, qiVector h_Wk )
	{	return cudaMQIread_buf( (qiPMatrix)(d_MA), ht, len, stream, h_Wk ); }
                                   /* write and read in ascii format */
inline overror_t cudaMQI_store( FILE *stream, qiMatrix MA, ui ht, ui len )
{	return cudaVQI_store( stream, (qiPMatrix)(MA), (len)*(ht) ); }
inline overror_t cudaMQI_recall( qiMatrix MA, ui ht, ui len, FILE *stream )
	{	return cudaVQI_recall( (qiPMatrix)(MA), (len)*(ht), stream ); }
inline overror_t cudaMQI_store_buf( FILE *stream, qiMatrix d_MA, ui ht, ui len, qiVector h_Wk )
{	return cudaVQI_store_buf( stream, (qiPMatrix)(d_MA), (len)*(ht), h_Wk ); }
inline overror_t cudaMQI_recall_buf( qiMatrix d_MA, ui ht, ui len, FILE *stream, qiVector h_Wk )
	{	return cudaVQI_recall_buf( (qiPMatrix)(d_MA), (len)*(ht), stream, h_Wk ); }
                                  /* store and recall in binary format */

#else  /* plain-C, not C++: type-cast used to transform qiMatrix into qiPMatrix  */

/***  Addressing single elements of dynamically allocated matrices: ******/

#define cudaMQI_setElement( MA, ht, len, m, n, C ) cudaMQIsetElement( (qiPMatrix)(MA), ht, len, m, n, C )
#define cusdMQI_setElement( MA, ht, len, m, n, C ) cusdMQIsetElement( (qiPMatrix)(MA), ht, len, m, n, C )
#define cudaMQI_getElement( y, MA, ht, len, m, n ) cudaMQIgetElement( y, (qiPMatrix)(MA), ht, len, m, n )
#define cusdMQI_getElement( y, MA, ht, len, m, n ) cusdMQIgetElement( y, (qiPMatrix)(MA), ht, len, m, n )
#define cudaMQI_Pelement( MA, ht, len, m, n )      cudaMQIPelement( (qiPMatrix)(MA), ht, len, m, n )
                     /* returns a pointer to MA[m][n]. */
#define cudaMQI_element( MA, ht, len, m, n )       cudaMQIelement( (qiPMatrix)(MA), ht, len, m, n )

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
        VQI_equ1( (qiVector)MA, ht * len );
*/

#define cudaMQI_equ0( MA, ht, len )            cudaVQI_equ0( (qiPMatrix)(MA), (ht)*(len) )
#define cudaMQI_equ1( MA, len )                cudaMQIequ1( (qiPMatrix)(MA), len ) /* identity matrix */
#define cudaMQI_equm1( MA, len )               cudaMQIequm1( (qiPMatrix)(MA), len ) /* neg. identity matrix */
#define cudaMQI_randomLC( MA, ht, len, seed, Min, Max, h_state )      cudaVQI_randomLC( MA, (ht)*(len), seed, Min, Max, h_state )
#define cudaMQI_random( MA, ht, len, seed, Min, Max )                 cudaVQI_random( MA, (ht)*(len), seed, Min, Max )
#define cusdMQI_randomLC( MA, ht, len, seed, d_Min, d_Max, h_state )  cudaVQI_randomLC( MA, (ht)*(len), seed, d_Min, d_Max, h_state )
#define cusdMQI_random( MA, ht, len, seed, d_Min, d_Max )             cudaVQI_random( MA, (ht)*(len), seed, d_Min, d_Max )
#define cudaMQI_outerprod( MA, X, Y, ht, len ) cudaMQIouterprod( (qiPMatrix)(MA), X, Y, ht, len )
                       /* sizX=ht, sizY=len */
#define cudaMQI_Row_equ0( MA, ht, len, iRow )  cudaMQIRow_equ0( (qiPMatrix)(MA), ht, len, iRow )
#define cudaMQI_Col_equ0( MA, ht, len, iCol )  cudaMQICol_equ0( (qiPMatrix)(MA), ht, len, iCol )
#define cudaMQI_Dia_equ0( MA, len )            cudaMQIDia_equ0( (qiPMatrix)(MA), len )
#define cudaMQI_Row_equC( MA, ht, len, iRow, C ) cudaMQIRow_equC( (qiPMatrix)(MA), ht, len, iRow, C )
#define cudaMQI_Col_equC( MA, ht, len, iCol, C ) cudaMQICol_equC( (qiPMatrix)(MA), ht, len, iCol, C )
#define cudaMQI_Dia_equC( MA, len, C )           cudaMQIDia_equC( (qiPMatrix)(MA), len, C )
#define cusdMQI_Row_equC( MA, ht, len, iRow, d_C ) cusdMQIRow_equC( (qiPMatrix)(MA), ht, len, iRow, d_C )
#define cusdMQI_Col_equC( MA, ht, len, iCol, d_C ) cusdMQICol_equC( (qiPMatrix)(MA), ht, len, iCol, d_C )
#define cusdMQI_Dia_equC( MA, len, d_C )           cusdMQIDia_equC( (qiPMatrix)(MA), len, d_C )

#define cudaMQI_Row_equV( MA, ht, len, iRow, X ) cudaMQIRow_equV( (qiPMatrix)(MA), ht, len, iRow, X )
#define cudaMQI_Col_equV( MA, ht, len, iCol, X ) cudaMQICol_equV( (qiPMatrix)(MA), ht, len, iCol, X )
#define cudaMQI_Dia_equV( MA, len, X )           cudaMQIDia_equV( (qiPMatrix)(MA), len, X )

#define cudaMQI_Trd_equM( MA, MTrd, len )    cudaMQITrd_equM( (qiPMatrix)(MA), (qiPMatrix)(MTr)d, len )
#define cudaMQI_Trd_extract( MTrd, MA, len ) cudaMQITrd_extract( (qiPMatrix)(MTr)d, (qiPMatrix)(MA), len )

#define cudaMQI_equM( MB, MA, ht, len )      cudaVQI_equV( (qiPMatrix)(MB), (qiPMatrix)(MA), (ht)*(len) )
#define cudaMQI_equMhost( MB, MA, ht, len )  cudaVQI_equVhost( (qiPMatrix)(MB), MA[0], (ht)*(len) )
#define MQI_equMdevice( MB, MA, ht, len )    VQI_equVdevice( MB[0], (qiPMatrix)(MA), (ht)*(len) )
#define cudaMQI_neg( MB, MA, ht, len )       cudaVQI_neg( (qiPMatrix)(MB), (qiPMatrix)(MA), (ht)*(len) )

#define cudaMQI_UequL( MA, len ) cudaMQIUequL( (qiPMatrix)(MA), len )
#define cudaMQI_LequU( MA, len ) cudaMQILequU( (qiPMatrix)(MA), len )


/************** Data-type interconversions  ****************************/

#ifdef _WIN64
	#define cudaM_QItoUQ( MUQ, MQI, ht, len ) cudaV_QItoUQ( (uqVector)(MUQ), (qiVector)(MQI), (ht)*(len) )
	#define cudaM_UQtoQI( MQI, MUQ, ht, len ) cudaV_UQtoQI( (qiVector)(MQI), (uqVector)(MUQ), (ht)*(len) )
#endif
#define cudaM_QItoBI( MBI, MQI, ht, len ) cudaV_QItoBI( (biVector)(MBI), (qiVector)(MQI), (ht)*(len) )
#define cudaM_QItoSI( MSI, MQI, ht, len ) cudaV_QItoSI( (siVector)(MSI), (qiVector)(MQI), (ht)*(len) )
#define cudaM_QItoI(  MI,  MQI, ht, len ) cudaV_QItoI(  (iVector)(MI),   (qiVector)(MQI), (ht)*(len) )
#define cudaM_QItoLI( MLI, MQI, ht, len ) cudaV_QItoLI( (liVector)(MLI), (qiVector)(MQI), (ht)*(len) )
#define cudaM_BItoQI( MQI, MBI, ht, len ) cudaV_BItoQI( (qiVector)(MQI), (biVector)(MBI), (ht)*(len) )
#define cudaM_SItoQI( MQI, MSI, ht, len ) cudaV_SItoQI( (qiVector)(MQI), (siVector)(MSI), (ht)*(len) )
#define cudaM_ItoQI(  MQI, MI,  ht, len ) cudaV_ItoQI(  (qiVector)(MQI), (iVector)(MI),   (ht)*(len) )
#define cudaM_LItoQI( MQI, MLI, ht, len ) cudaV_LItoQI( (qiVector)(MQI), (liVector)(MLI), (ht)*(len) )
#define cudaM_QItoF(  MF,  MQI, ht, len ) cudaV_QItoF(  (fVector)(MF),   (qiVector)(MQI), (ht)*(len) )
#define cudaM_QItoD(  MD,  MQI, ht, len ) cudaV_QItoD(  (dVector)(MD),   (qiVector)(MQI), (ht)*(len) )

/********  Extracting a submatrix and copying a submatrix back  *********/

#define cudaMQI_submatrix( MSub, subHt, subLen, MSrce, srceHt, srceLen, \
                      firstRowInCol, sampInCol, firstColInRow, sampInRow ) \
               cudaMQIsubmatrix(  (qiPMatrix)(MSub), subHt, subLen, \
                             (qiPMatrix)(MSrce), srceHt, srceLen, \
                             firstRowInCol, sampInCol, firstColInRow, sampInRow )

#define cudaMQI_submatrix_equM( MDest, destHt, destLen, \
                           firstRowInCol, sampInCol, firstColInRow, sampInRow, \
                           MSrce, srceHt, srceLen ) \
               cudaMQIsubmatrix_equM(  (qiPMatrix)(MDest), destHt, destLen, \
                             firstRowInCol, sampInCol, firstColInRow, sampInRow, \
                             (qiPMatrix)(MSrce), srceHt, srceLen )

#define cudaMQI_equMblock( MSub, subHt, subLen, \
                      MSrce, srceHt, srceLen, \
                      firstRowInCol, firstColInRow ) \
               cudaMQIequMblock(  (qiPMatrix)(MSub), subHt, subLen, \
                             (qiPMatrix)(MSrce), srceHt, srceLen, \
                             firstRowInCol, firstColInRow )

#define cudaMQI_block_equM( MDest, destHt, destLen, \
                       firstRowInCol, firstColInRow, \
                       MSrce, srceHt, srceLen ) \
               cudaMQIblock_equM( (qiPMatrix)(MDest), destHt, destLen, \
                             firstRowInCol, firstColInRow, \
                             (qiPMatrix)(MSrce), srceHt, srceLen )

#define cudaMQI_equMblockT( MSub, subHt, subLen, \
                      MSrce, srceHt, srceLen, \
                      firstRowInCol, firstColInRow ) \
               cudaMQIequMblockT(  (qiPMatrix)(MSub), subHt, subLen, \
                             (qiPMatrix)(MSrce), srceHt, srceLen, \
                             firstRowInCol, firstColInRow )

#define cudaMQI_block_equMT( MDest, destHt, destLen, \
                       firstRowInCol, firstColInRow, \
                       MSrce, srceHt, srceLen ) \
               cudaMQIblock_equMT( (qiPMatrix)(MDest), destHt, destLen, \
                             firstRowInCol, firstColInRow, \
                             (qiPMatrix)(MSrce), srceHt, srceLen )

/*****   Extracting a single row or a single column or the diagonal  ******
 *       and storing it into a vector                                     */

#define cudaMQI_Row_extract( Y, MA, ht, len, iRow ) \
                                     cudaMQIRow_extract( Y, (qiPMatrix)(MA), ht, len, iRow )
#define cudaMQI_Col_extract( Y, MA, ht, len, iCol ) \
                                     cudaMQICol_extract( Y, (qiPMatrix)(MA), ht, len, iCol )
#define cudaMQI_Dia_extract( Y, MA, len ) cudaMQIDia_extract( Y, (qiPMatrix)(MA), len )


/**************  Deleting or inserting a row or a column   ***************/

#define cudaMQI_Row_delete( MB, MA, htA, lenA, iRow ) \
                           cudaMQIRow_delete( (qiPMatrix)(MB), (qiPMatrix)(MA), htA, lenA, iRow )
#define cudaMQI_Col_delete( MB, MA, htA, lenA, iCol ) \
                           cudaMQICol_delete( (qiPMatrix)(MB), (qiPMatrix)(MA), htA, lenA, iCol )
#define cudaMQI_Row_insert( MB, MA, htB, lenB, iRow, X ) \
                           cudaMQIRow_insert( (qiPMatrix)(MB), (qiPMatrix)(MA), htB, lenB, iRow, X )
#define cudaMQI_Col_insert( MB, MA, htB, lenB, iCol, X ) \
                           cudaMQICol_insert( (qiPMatrix)(MB), (qiPMatrix)(MA), htB, lenB, iCol, X )

/******  One-dimensional vector operations **********************
         performed along all rows or all columns simultaneously,
         or along the diagonal of a square matrix                */

#define cudaMQI_Rows_max( Y, MA, ht, len )     cudaMQIRows_max( Y, (qiPMatrix)(MA), ht, len )
#define cudaMQI_Cols_max( Y, MA, ht, len )     cudaMQICols_max( Y, (qiPMatrix)(MA), ht, len )
#define cudaMQI_Dia_max(  h_RetPtr, MA, len )  cudaMQIDia_max( h_RetPtr, (qiPMatrix)(MA), len )
#define cusdMQI_Dia_max(  d_RetPtr, MA, len )  cusdMQIDia_max( d_RetPtr, (qiPMatrix)(MA), len )
#define cudaMQI_Rows_min( Y, MA, ht, len )     cudaMQIRows_min( Y, (qiPMatrix)(MA), ht, len )
#define cudaMQI_Cols_min( Y, MA, ht, len )     cudaMQICols_min( Y, (qiPMatrix)(MA), ht, len )
#define cudaMQI_Dia_min(  h_RetPtr, MA, len )  cudaMQIDia_min( h_RetPtr, (qiPMatrix)(MA), len )
#define cusdMQI_Dia_min(  d_RetPtr, MA, len )  cusdMQIDia_min( d_RetPtr, (qiPMatrix)(MA), len )

#define cudaMQI_Rows_rotate( MA, ht, len, pos) cudaMQIRows_rotate( (qiPMatrix)(MA), ht, len, pos )
#define cudaMQI_Cols_rotate( MA, ht, len, pos) cudaMQICols_rotate( (qiPMatrix)(MA), ht, len, pos )
#define cudaMQI_Rows_rotate_buf( MA, ht, len, pos, MBuf) cudaMQIRows_rotate_buf( (qiPMatrix)(MA), ht, len, pos, (qiPMatrix)(MBuf) )
#define cudaMQI_Cols_rotate_buf( MA, ht, len, pos, MBuf) cudaMQICols_rotate_buf( (qiPMatrix)(MA), ht, len, pos, (qiPMatrix)(MBuf) )
#define cudaMQI_Rows_reflect( MA, ht, len)     cudaMQIRows_reflect( (qiPMatrix)(MA), ht, len )
#define cudaMQI_Cols_reflect( MA, ht, len)     cudaMQICols_reflect( (qiPMatrix)(MA), ht, len )
#define cudaMQI_Rows_rev( MA, ht, len)         cudaMQIRows_rev( (qiPMatrix)(MA), ht, len )
#define cudaMQI_Cols_rev( MA, ht, len)         cudaMQICols_rev( (qiPMatrix)(MA), ht, len )
#define cudaMQI_Rows_distribution( MAbund, Limits, nBins, MX, ht, len, mode ) cudaMQIRows_distribution( (uiPMatrix)MAbund, Limits, nBins, (qiPMatrix)MX, ht, len, mode )
#define cudaMQI_Cols_distribution( MAbund, Limits, nBins, MX, ht, len, mode ) cudaMQICols_distribution( (uiPMatrix)MAbund, Limits, nBins, (qiPMatrix)MX, ht, len, mode )

/********  Operations involving two rows or two colums of one matrix  *****/

#define cudaMQI_Rows_exchange( MA, ht, len, row1, row2 ) \
                             cudaMQIRows_exchange( (qiPMatrix)(MA), ht, len, row1, row2 )
#define cudaMQI_Cols_exchange( MA, ht, len, col1, col2 ) \
                             cudaMQICols_exchange( (qiPMatrix)(MA), ht, len, col1, col2 )

/************  Transposing and rotating a matrix **********************/

#define cudaMQI_transpose( MTr, MA, htTr, lenTr ) \
             cudaMQItranspose( (qiPMatrix)(MTr), (qiPMatrix)(MA), htTr, lenTr )
       /*  dimensions htTr, lenTr are those of the transposed matrix,
           not of the original!                */
#define cudaMQI_rotate90( MRot, MA, htRot, lenRot ) \
             cudaMQIrotate90( (qiPMatrix)(MRot), (qiPMatrix)(MA), htRot, lenRot )
#define cudaMQI_rotate180( MRot, MA, htRot, lenRot ) \
             cudaVQI_rev( (qiPMatrix)(MRot), (qiPMatrix)(MA), (htRot)*(lenRot) )
#define cudaMQI_rotate270( MRot, MA, htRot, lenRot ) \
             cudaMQIrotate270( (qiPMatrix)(MRot), (qiPMatrix)(MA), htRot, lenRot )

/**************************  Input and Output  **************************
	The input/output functions involve memory transfers from device
	to host memory or vice versa. The generic cudaMQI_input/output functions
	allocate their own host buffers, whereas the cudaMQI_xxx_buf functions
	take a user-supplied buffer vector h_Wk (size must be >= ht*len )
	and are much more efficient.                                       */

#define cudaMQI_fprint( stream, MA, ht, len, linewidth ) \
                    cudaMQIfprint( stream, (qiPMatrix)(MA), ht, len, linewidth )
#define cudaMQI_print( MA, ht, len )  cudaMQIfprint( stdout, (qiPMatrix)(MA), ht, len, 80 )
#define cudaMQI_cprint( MA, ht, len ) cudaMQIcprint( (qiPMatrix)(MA), ht, len )
#define cudaMQI_fprint_buf( stream, MA, ht, len, linewidth, h_Wk ) \
                    cudaMQIfprint_buf( stream, (qiPMatrix)(MA), ht, len, linewidth, h_Wk )
#define cudaMQI_print_buf( MA, ht, len )  cudaMQIfprint_buf( stdout, (qiPMatrix)(MA), ht, len, 80, h_Wk )
#define cudaMQI_cprint_buf( MA, ht, len ) cudaMQIcprint_buf( (qiPMatrix)(MA), ht, len, h_Wk )
  /*  cudaMQI_print, cudaMQI_cprint usable only for console applications! */
#define cudaMQI_write( str, MA, ht, len )   cudaMQIwrite( str, (qiPMatrix)(MA), ht, len )
#define cudaMQI_read( MA, ht, len, str )    cudaMQIread( (qiPMatrix)(MA), ht, len, str )
#define cudaMQI_write_buf( str, MA, ht, len, h_Wk )   cudaMQIwrite_buf( str, (qiPMatrix)(MA), ht, len, h_Wk )
#define cudaMQI_read_buf( MA, ht, len, str, h_Wk )    cudaMQIread_buf( (qiPMatrix)(MA), ht, len, str, h_Wk )
                                   /* write and read in ascii format */
#define cudaMQI_store( str, MA, ht, len )   cudaVQI_store( str, (qiPMatrix)(MA), (len)*(ht) )
#define cudaMQI_recall( MA, ht, len, str)   cudaVQI_recall( (qiPMatrix)(MA), (len)*(ht), str)
#define cudaMQI_store_buf( str, MA, ht, len, h_Wk )   cudaVQI_store_buf( str, (qiPMatrix)(MA), (len)*(ht), h_Wk )
#define cudaMQI_recall_buf( MA, ht, len, str, h_Wk)   cudaVQI_recall_buf( (qiPMatrix)(MA), (len)*(ht), str, h_Wk )
                                  /* store and recall in binary format */

#endif /* plain-C or C++ for functions working on device memory */


/*******************  Functions working on host memory: **********************
 *                                                                           *
 *	MQIcu_func		(working on matrices in host memory, input type qiMatrix,*
 *	scalar parameters on host and passed by value)                           *
 *****************************************************************************/ 

/****************  Initialization  ****************************************/

#define MQIcu_equ0( MA, ht, len )                   VQIcu_equ0( (MA)[0], (ht)*(len) )
#define MQIcu_equ1( MA, len )                       MQIcuequ1( (MA)[0], len ) /* identity matrix */
#define MQIcu_equm1( MA, len )                      MQIcuequm1( (MA)[0], len ) /* neg. identity matrix */
#define MQIcu_randomLC( MA, ht, len, seed, Min, Max, state ) VQIcu_randomLC( (MA)[0], (ht)*(len), seed, Min, Max, state )
#define MQIcu_random( MA, ht, len, seed, Min, Max )          VQIcu_random( (MA)[0], (ht)*(len), seed, Min, Max )
#define MQIcu_outerprod( MA, X, Y, ht, len )        MQIcuouterprod( (MA)[0], X, Y, ht, len )
                       /* sizX=ht, sizY=len */
#define MQIcu_Row_equ0( MA, ht, len, iRow )    MQIcuRow_equ0( (MA)[0], ht, len, iRow )
#define MQIcu_Col_equ0( MA, ht, len, iCol )    MQIcuCol_equ0( (MA)[0], ht, len, iCol )
#define MQIcu_Dia_equ0( MA, len )              MQIcuDia_equ0( (MA)[0], len )
#define MQIcu_Row_equC( MA, ht, len, iRow, C ) MQIcuRow_equC( (MA)[0], ht, len, iRow, C )
#define MQIcu_Col_equC( MA, ht, len, iCol, C ) MQIcuCol_equC( (MA)[0], ht, len, iCol, C )
#define MQIcu_Dia_equC( MA, len, C )           MQIcuDia_equC( (MA)[0], len, C )

#define MQIcu_Row_equV( MA, ht, len, iRow, X ) MQIcuRow_equV( (MA)[0], ht, len, iRow, X )
#define MQIcu_Col_equV( MA, ht, len, iCol, X ) MQIcuCol_equV( (MA)[0], ht, len, iCol, X )
#define MQIcu_Dia_equV( MA, len, X )           MQIcuDia_equV( (MA)[0], len, X )

#define MQIcu_Trd_equM( MA, MTrd, len )        MQIcuTrd_equM( (MA)[0], (MTrd)[0], len )
#define MQIcu_Trd_extract( MTrd, MA, len )     MQIcuTrd_extract( (MTrd)[0], (MA)[0], len )

#define MQIcu_equM( MB, MA, ht, len )          VQIcu_equV( (MB)[0], (MA)[0], (ht)*(len) )
#define MQIcu_equMhost( MB, MA, ht, len )      VQIcu_equVhost( (MB)[0], MA[0], (ht)*(len) )
#define MQIcu_neg( MB, MA, ht, len )           VQIcu_neg( (MB)[0], (MA)[0], (ht)*(len) )

#define MQIcu_UequL( MA, len ) MQIcuUequL( (MA)[0], len )
#define MQIcu_LequU( MA, len ) MQIcuLequU( (MA)[0], len )
     /* copy lower-diagonal elements into upper-diagonal
       (or vice versa) by index-reflection, so as to get a symmetric matrix    */

            /* data-type conversions:  */
#ifdef _WIN64
	#define Mcu_QItoUQ( MUQ, MQI, ht, len ) Vcu_QItoUQ( (MUQ)[0], (MQI)[0], (ht)*(len) )
	#define Mcu_UQtoQI( MQI, MUQ, ht, len ) Vcu_UQtoQI( (MQI)[0], (MUQ)[0], (ht)*(len) )
#endif
#define Mcu_QItoBI( MBI, MQI, ht, len ) Vcu_QItoBI( (MBI)[0], (MQI)[0], (ht)*(len) )
#define Mcu_QItoSI( MSI, MQI, ht, len ) Vcu_QItoSI( (MSI)[0], (MQI)[0], (ht)*(len) )
#define Mcu_QItoI(  MI,  MQI, ht, len ) Vcu_QItoI(  (MI)[0],  (MQI)[0], (ht)*(len) )
#define Mcu_QItoLI( MLI, MQI, ht, len ) Vcu_QItoLI( (MLI)[0], (MQI)[0], (ht)*(len) )
#define Mcu_BItoQI( MQI, MBI, ht, len ) Vcu_BItoQI( (MQI)[0], (MBI)[0], (ht)*(len) )
#define Mcu_SItoQI( MQI, MSI, ht, len ) Vcu_SItoQI( (MQI)[0], (MSI)[0], (ht)*(len) )
#define Mcu_ItoQI(  MQI, MI,  ht, len ) Vcu_ItoQI(  (MQI)[0], (MI)[0],  (ht)*(len) )
#define Mcu_LItoQI( MQI, MLI, ht, len ) Vcu_LItoQI( (MQI)[0], (MLI)[0], (ht)*(len) )
#define Mcu_QItoF(  MF,  MQI, ht, len ) Vcu_QItoF(  (MF)[0],  (MQI)[0], (ht)*(len) )
#define Mcu_QItoD(  MD,  MQI, ht, len ) Vcu_QItoD(  (MD)[0],  (MQI)[0], (ht)*(len) )


/********  Extracting a submatrix and copying a submatrix back  *********/

#define MQIcu_submatrix( MSub, subHt, subLen, MSrce, srceHt, srceLen, \
                      firstRowInCol, sampInCol, firstColInRow, sampInRow ) \
               MQIcusubmatrix(  (MSub)[0], subHt, subLen, \
                             (MSrce)[0], srceHt, srceLen, \
                             firstRowInCol, sampInCol, firstColInRow, sampInRow )

#define MQIcu_submatrix_equM( MDest, destHt, destLen, \
                           firstRowInCol, sampInCol, firstColInRow, sampInRow, \
                           MSrce, srceHt, srceLen ) \
               MQIcusubmatrix_equM(  (MDest)[0], destHt, destLen, \
                             firstRowInCol, sampInCol, firstColInRow, sampInRow, \
                             (MSrce)[0], srceHt, srceLen )

#define MQIcu_equMblock( MSub, subHt, subLen, MSrce, srceHt, srceLen, \
                      firstRowInCol, firstColInRow ) \
               MQIcuequMblock(  (MSub)[0], subHt, subLen, \
                             (MSrce)[0], srceHt, srceLen, \
                             firstRowInCol, firstColInRow )

#define MQIcu_block_equM( MDest, destHt, destLen, \
                       firstRowInCol, firstColInRow, \
                       MSrce, srceHt, srceLen ) \
               MQIcublock_equM( (MDest)[0], destHt, destLen, \
                             firstRowInCol, firstColInRow, \
                             (MSrce)[0], srceHt, srceLen )

#define MQIcu_equMblockT( MSub, subHt, subLen, MSrce, srceHt, srceLen, \
                      firstRowInCol, firstColInRow ) \
               MQIcuequMblockT(  (MSub)[0], subHt, subLen, \
                             (MSrce)[0], srceHt, srceLen, \
                             firstRowInCol, firstColInRow )

#define MQIcu_block_equMT( MDest, destHt, destLen, \
                       firstRowInCol, firstColInRow, \
                       MSrce, srceHt, srceLen ) \
               MQIcublock_equMT( (MDest)[0], destHt, destLen, \
                             firstRowInCol, firstColInRow, \
                             (MSrce)[0], srceHt, srceLen )

/*****   Extracting a single row or a single column or the diagonal  ******
 *       and storing it into a vector                                     */

#define MQIcu_Row_extract( Y, MA, ht, len, iRow ) MQIcuRow_extract( Y, (MA)[0], ht, len, iRow )
#define MQIcu_Col_extract( Y, MA, ht, len, iCol ) MQIcuCol_extract( Y, (MA)[0], ht, len, iCol )
#define MQIcu_Dia_extract( Y, MA, len )           MQIcuDia_extract( Y, (MA)[0], len )

/**************  Deleting or inserting a row or a column   ***************/

#define MQIcu_Row_delete( MB, MA, htA, lenA, iRow )    MQIcuRow_delete( (MB)[0], (MA)[0], htA, lenA, iRow )
#define MQIcu_Col_delete( MB, MA, htA, lenA, iCol )    MQIcuCol_delete( (MB)[0], (MA)[0], htA, lenA, iCol )
#define MQIcu_Row_insert( MB, MA, htB, lenB, iRow, X ) MQIcuRow_insert( (MB)[0], (MA)[0], htB, lenB, iRow, X )
#define MQIcu_Col_insert( MB, MA, htB, lenB, iCol, X ) MQIcuCol_insert( (MB)[0], (MA)[0], htB, lenB, iCol, X )


/*****************    Basic arithmetic operations *********************
                      performed on one single row,
                      or one single column of any matrix,
                      or on the diagonal of a square matrix

    Note: In contrast to the analogous VectorLib functions, the operations
    are performed in-place, i.e. the input matrix itself is changed  */

#define MQIcu_Row_neg( MA, ht, len, iRow ) MQIcuRow_neg( (MA)[0], ht, len, iRow )
#define MQIcu_Col_neg( MA, ht, len, iCol ) MQIcuCol_neg( (MA)[0], ht, len, iCol )

/******  One-dimensional vector operations **********************
         performed along all rows or all columns simultaneously,
         or along the diagonal of a square matrix                */

#define MQIcu_Rows_max( Y, MA, ht, len )        MQIcuRows_max( Y, (MA)[0], ht, len )
#define MQIcu_Cols_max( Y, MA, ht, len )        MQIcuCols_max( Y, (MA)[0], ht, len )
#define MQIcu_Dia_max(  MA, len )               MQIcuDia_max(  (MA)[0], len )
#define MQIcu_Rows_min( Y, MA, ht, len )        MQIcuRows_min( Y, (MA)[0], ht, len )
#define MQIcu_Cols_min( Y, MA, ht, len )        MQIcuCols_min( Y, (MA)[0], ht, len )
#define MQIcu_Dia_min(  MA, len )               MQIcuDia_min(  (MA)[0], len )

#define MQIcu_Rows_rotate( MA, ht, len, pos)           MQIcuRows_rotate( (MA)[0], ht, len, pos )
#define MQIcu_Cols_rotate( MA, ht, len, pos)           MQIcuCols_rotate( (MA)[0], ht, len, pos )
#define MQIcu_Rows_rotate_buf( MA, ht, len, pos, MBuf) MQIcuRows_rotate_buf( (MA)[0], ht, len, pos, (MBuf)[0] )
#define MQIcu_Cols_rotate_buf( MA, ht, len, pos, MBuf) MQIcuCols_rotate_buf( (MA)[0], ht, len, pos, (MBuf)[0] )
#define MQIcu_Rows_reflect( MA, ht, len )              MQIcuRows_reflect( (MA)[0], ht, len )
#define MQIcu_Cols_reflect( MA, ht, len )              MQIcuCols_reflect( (MA)[0], ht, len )
#define MQIcu_Rows_rev( MA, ht, len)                   MQIcuRows_rev( (MA)[0], ht, len )
#define MQIcu_Cols_rev( MA, ht, len)                   MQIcuCols_rev( (MA)[0], ht, len )
#define MQIcu_Rows_distribution( MAbund, Limits, nBins, MX, ht, len, mode ) MQIcuRows_distribution( MAbund[0], Limits, nBins, MX[0], ht, len, mode )
#define MQIcu_Cols_distribution( MAbund, Limits, nBins, MX, ht, len, mode ) MQIcuCols_distribution( MAbund[0], Limits, nBins, MX[0], ht, len, mode )

/********  Operations involving two rows or two colums of one matrix  *****/

#define MQIcu_Rows_exchange( MA, ht, len, row1, row2 ) \
                             MQIcuRows_exchange( (MA)[0], ht, len, row1, row2 )
#define MQIcu_Cols_exchange( MA, ht, len, col1, col2 ) \
                             MQIcuCols_exchange( (MA)[0], ht, len, col1, col2 )

/*************** Transposing and rotating a matrix **********************/

#define MQIcu_transpose( MTr, MA, htTr, lenTr )    MQIcutranspose( (MTr)[0], (MA)[0], htTr, lenTr )
       /*  dimensions htTr, lenTr are those of the transposed matrix, not of the original!   */
#define MQIcu_rotate90( MRot, MA, htRot, lenRot )  MQIcurotate90( (MRot)[0], (MA)[0], htRot, lenRot )
#define MQIcu_rotate180( MRot, MA, htRot, lenRot ) VQIcu_rev( (MRot)[0], (MA)[0], (htRot)*(lenRot) )
#define MQIcu_rotate270( MRot, MA, htRot, lenRot ) MQIcurotate270( (MRot)[0], (MA)[0], htRot, lenRot )


/*************************************************************************
 * MQIcu functions (without underbar in the prefix): 	
    (working on matrices in host memory, input type 
	qiPMatrix = qiVector = pointer to matrix element[0][0], 
	scalar parameters on host and passed by value)
*
 *************************************************************************/

#define MQIcuequ0( MA, ht, len )       VQIcu_equ0( MA, (ht)*(len) )
void   __vf OVCUAPI  MQIcuequ1( qiPMatrix MA, ui len );  /* identity matrix */
void   __vf OVCUAPI  MQIcuequm1( qiPMatrix MA, ui len );  /* neg. identity matrix */
void   __vf OVCUAPI  MQIcuouterprod( qiPMatrix MA, qiVector X,  qiVector Y, ui ht, ui len );

void   __vf OVCUAPI  MQIcuRow_equ0( qiPMatrix MA, ui ht, ui len, ui iRow );
void   __vf OVCUAPI  MQIcuCol_equ0( qiPMatrix MA, ui ht, ui len, ui iCol );
void   __vf OVCUAPI  MQIcuDia_equ0( qiPMatrix MA, ui len );

void   __vf OVCUAPI  MQIcuRow_equC( qiPMatrix MA, ui ht, ui len, ui iRow, quad C );
void   __vf OVCUAPI  MQIcuCol_equC( qiPMatrix MA, ui ht, ui len, ui iCol, quad C );
void   __vf OVCUAPI  MQIcuDia_equC( qiPMatrix MA, ui len, quad C );

void   __vf OVCUAPI  MQIcuRow_equV( qiPMatrix MA, ui ht, ui len, ui iRow, qiVector X );
void   __vf OVCUAPI  MQIcuCol_equV( qiPMatrix MA, ui ht, ui len, ui iCol, qiVector X );
void   __vf OVCUAPI  MQIcuDia_equV( qiPMatrix MA, ui len, qiVector X );

void   __vf OVCUAPI  MQIcuTrd_equM( qiPMatrix MA, qiPMatrix MTrd, ui len );
void   __vf OVCUAPI  MQIcuTrd_extract( qiPMatrix MTrd, qiPMatrix MA, ui len );

#define MQIcuequM( MB, MA, ht, len )      VQIcu_equV( MB, MA, (ht)*(len) )
#define MQIcuneg( MB, MA, ht, len )       VQIcu_neg( MB, MA, (ht)*(len) )
void   __vf OVCUAPI  MQIcuUequL( qiPMatrix MA, ui len );
void   __vf OVCUAPI  MQIcuLequU( qiPMatrix MA, ui len );

            /* data-type conversions:  */
#ifdef _WIN64
	#define McuQItoUQ( MUQ, MQI, ht, len ) Vcu_QItoUQ( MUQ, MQI, (ht)*(len) )
	#define McuUQtoQI( MQI, MUQ, ht, len ) Vcu_UQtoQI( MQI, MUQ, (ht)*(len) )
#endif
#define McuQItoBI( MBI, MQI, ht, len ) Vcu_QItoBI( MBI, MQI, (ht)*(len) )
#define McuQItoSI( MSI, MQI, ht, len ) Vcu_QItoSI( MSI, MQI, (ht)*(len) )
#define McuQItoI(  MI,  MQI, ht, len ) Vcu_QItoI(  MI,  MQI, (ht)*(len) )
#define McuQItoLI( MLI, MQI, ht, len ) Vcu_QItoLI( MLI, MQI, (ht)*(len) )
#define McuBItoQI( MQI, MBI, ht, len ) Vcu_BItoQI( MQI, MBI, (ht)*(len) )
#define McuSItoQI( MQI, MSI, ht, len ) Vcu_SItoQI( MQI, MSI, (ht)*(len) )
#define McuItoQI(  MQI, MI,  ht, len ) Vcu_ItoQI(  MQI, MI,  (ht)*(len) )
#define McuLItoQI( MQI, MLI, ht, len ) Vcu_LItoQI( MQI, MLI, (ht)*(len) )
#define McuQItoF(  MF,  MQI, ht, len ) Vcu_QItoF(  MF,  MQI, (ht)*(len) )
#define McuQItoD(  MD,  MQI, ht, len ) Vcu_QItoD(  MD,  MQI, (ht)*(len) )

/********  Extracting a submatrix and copying a submatrix back  *********/

void  __vf OVCUAPI  MQIcusubmatrix( qiPMatrix MSub, ui subHt,  ui subLen,
                          qiPMatrix MSrce, ui srceHt,  ui srceLen,
                          ui firstRowInCol,  ui sampInCol,
                          ui firstColInRow,  ui sampInRow );

void  __vf OVCUAPI  MQIcusubmatrix_equM( qiPMatrix MDest, ui destHt, ui destLen,
                               ui firstRowInCol,  ui sampInCol,
                               ui firstColInRow,  ui sampInRow,
                               qiPMatrix MSrce, ui srceHt, ui srceLen );

void  __vf OVCUAPI  MQIcuequMblock(  qiPMatrix MSub, ui subHt, ui subLen,
                          qiPMatrix MSrce, ui srceHt,  ui srceLen,
                          ui firstRowInCol,  ui firstColInRow );

void  __vf OVCUAPI  MQIcublock_equM( qiPMatrix MDest, ui destHt, ui destLen,
                          ui firstRowInCol,  ui firstColInRow,
                          qiPMatrix MSrce, ui srceHt, ui srceLen );

void  __vf OVCUAPI  MQIcuequMblockT( qiPMatrix MSub, ui subHt, ui subLen,
                          qiPMatrix MSrce, ui srceHt, ui srceLen,
                          ui firstRowInCol,  ui firstColInRow );

void  __vf OVCUAPI  MQIcublock_equMT( qiPMatrix MDest, ui destHt, ui destLen,
                          ui firstRowInCol,  ui firstColInRow,
                          qiPMatrix MSrce, ui srceHt, ui srceLen );


/*****   Extracting a single row or a single column or the diagonal  *****
 *       and storing it into a vector                                    */

void __vf OVCUAPI  MQIcuRow_extract( qiVector Y, qiPMatrix MA, ui ht, ui len, ui iRow );
void __vf OVCUAPI  MQIcuCol_extract( qiVector Y, qiPMatrix MA, ui ht, ui len, ui iCol );
void __vf OVCUAPI  MQIcuDia_extract( qiVector Y, qiPMatrix MA, ui len );

/**********  Deleting or inserting a row or a column *****************/

void __vf OVCUAPI  MQIcuRow_delete( qiPMatrix MB, qiPMatrix MA, ui htA, ui lenA, ui iRow );
void __vf OVCUAPI  MQIcuCol_delete( qiPMatrix MB, qiPMatrix MA, ui htA, ui lenA, ui iCol );
void __vf OVCUAPI  MQIcuRow_insert( qiPMatrix MB, qiPMatrix MA, ui htB, ui lenB, ui iRow, qiVector X );
void __vf OVCUAPI  MQIcuCol_insert( qiPMatrix MB, qiPMatrix MA, ui htB, ui lenB, ui iCol, qiVector X );


/******  One-dimensional vector operations **********************
         performed along all rows or all columns simultaneously,
         or along the diagonal of a square matrix                */

void   __vf OVCUAPI  MQIcuRows_max( qiVector Y, qiPMatrix MA, ui ht, ui len );
void   __vf OVCUAPI  MQIcuCols_max( qiVector Y, qiPMatrix MA, ui ht, ui len );
quad   __vf OVCUAPI  MQIcuDia_max(  qiPMatrix MA, ui len );
void   __vf OVCUAPI  MQIcuRows_min( qiVector Y, qiPMatrix MA, ui ht, ui len );
void   __vf OVCUAPI  MQIcuCols_min( qiVector Y, qiPMatrix MA, ui ht, ui len );
quad   __vf OVCUAPI  MQIcuDia_min(  qiPMatrix MA, ui len );

void  __vf OVCUAPI  MQIcuRows_rotate( qiPMatrix MA, ui ht, ui len, ssize_t pos );
void  __vf OVCUAPI  MQIcuCols_rotate( qiPMatrix MA, ui ht, ui len, ssize_t pos );
void  __vf OVCUAPI  MQIcuRows_rotate_buf( qiPMatrix MA, ui ht, ui len, ssize_t pos, qiPMatrix MBuf );
void  __vf OVCUAPI  MQIcuCols_rotate_buf( qiPMatrix MA, ui ht, ui len, ssize_t pos, qiPMatrix MBuf );
void  __vf OVCUAPI  MQIcuRows_reflect( qiPMatrix MA, ui ht, ui len );
void  __vf OVCUAPI  MQIcuCols_reflect( qiPMatrix MA, ui ht, ui len );
void  __vf OVCUAPI  MQIcuRows_rev( qiPMatrix MA, ui ht, ui len );
void  __vf OVCUAPI  MQIcuCols_rev( qiPMatrix MA, ui ht, ui len );
void  __vf OVCUAPI  MQIcuRows_distribution( uiPMatrix MAbund, qiVector Limits, ui nBins, qiPMatrix MX, ui ht, ui len, int mode );
void  __vf OVCUAPI  MQIcuCols_distribution( uiPMatrix MAbund, qiVector Limits, ui nBins, qiPMatrix MX, ui ht, ui len, int mode );

/********  Operations involving two rows or two colums of one matrix  *****/

void   __vf OVCUAPI  MQIcuRows_exchange( qiPMatrix MA, ui ht, ui len, ui i1, ui i2 );
void   __vf OVCUAPI  MQIcuCols_exchange( qiPMatrix MA, ui ht, ui len, ui i1, ui i2 );


/***************  Transposing and rotating a matrix **********************/

void  __vf OVCUAPI  MQIcutranspose( qiPMatrix MTr, qiPMatrix MA,  ui htTr, ui lenTr );
void  __vf OVCUAPI  MQIcurotate90(  qiPMatrix MRot, qiPMatrix MA, ui htRot, ui lenRot );
#define     MQIcurotate180( MRot, MA, htRot, lenRot )  VQIcu_rev( MRot, MA, (htRot)*(lenRot) )
void  __vf OVCUAPI  MQIcurotate270( qiPMatrix MRot, qiPMatrix MA, ui htRot, ui lenRot );

#ifdef __cplusplus
} // end of extern "C"
#endif
#endif  /*  __MQISTD_H  */
