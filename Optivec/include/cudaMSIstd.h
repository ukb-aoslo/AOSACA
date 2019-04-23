/*  cudaMSIstd.h

  matrix management functions:
  manipulations on matrices of data type "short" (16-bit integer)

  This file declares the functions with the name variants 
	cudaMSI_func	(working on matrices in device memory, input type siMatrix, scalar parameters reside on host and are passed by value)
	cusdMSI_func	(as cudaMSI_func except scalar parameters reside on device and are passed by address)
	cudaMSIfunc		(as cudaMSI_func, but input type siPMatrix = siVector = pointer to matrix element[0][0])
	cusdMSIfunc		(as cusdMSI_func, but input type siPMatrix = siVector = pointer to matrix element[0][0])
	MSIcu_func		(working on matrices in host memory, input type siMatrix, scalar parameters on host and passed by value)
	MSIcufunc		(as MSIcu_func, but input type siPMatrix = siVector = pointer to matrix element[0][0])
  where func is the respective function.

   Copyright (c) 1996-2017 by OptiCode - Dr. Martin Sander Software Dev.
  All Rights Reserved.

*/

#if !defined( __CUDAMSISTD_H )
#define __CUDAMSISTD_H
#if !defined( __CUDAMATLIB_H )
#include <cudaMatLib.h>
#endif
#if !defined( __CUDAVSISTD_H )
#include <cudaVSIstd.h>
#endif
#if !defined( __CUDAVSIMATH_H )
#include <cudaVSImath.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif

/**** Generation of matrices on device memory and on pinned host memory *******************/

siMatrix  __vf cudaMSI_matrix( ui ht, ui len );   /* allocates a vector on device memory */
siMatrix  __vf cudaMSI_matrix0( ui ht, ui len );
 /* The following functions allocate device-accessible, "pinned" memory on the host.
	This memory is mapped onto the device memory space. The resulting device address is returned.
	The matrix can be accessed either by its host address "hostPtr" e.g., MSI_equ1( hostPtr, ht, len );
	or by its device address , e.g., cudaMSI_equ1( devicePtr, ht, len );                             */
siMatrix  __vf cudaMSI_pinnedMatrix(  siMatrix *hostPtr, ui ht, ui len ); 
siMatrix  __vf cudaMSI_pinnedMatrix0( siMatrix *hostPtr, ui ht, ui len );

/*************************************************************************
 * Declarations of the functions written without underbar in the prefix: *
 *	cudaMSIfunc  (input type 
                   siPMatrix = siVector = pointer to matrix element[0][0])
 *	cusdMSIfunc  (input type 
                   siPMatrix = siVector = pointer to matrix element[0][0])
 *************************************************************************/

void  __vcuf OVCUAPI  cudaMSIsetElement( siPMatrix X, ui ht, ui len, ui m, ui n, short C );
void  __vcuf OVCUAPI  cusdMSIsetElement( siPMatrix X, ui ht, ui len, ui m, ui n, short *d_C );
void  __vcuf OVCUAPI  cudaMSIgetElement( short *h_y, siPMatrix X, ui ht, ui len, ui m, ui n );
void  __vcuf OVCUAPI  cusdMSIgetElement( short *d_y, siPMatrix X, ui ht, ui len, ui m, ui n );
short  __vcuf OVCUAPI  cudaMSIelement( siPMatrix X, ui ht, ui len, ui m, ui n );
short * __vcuf OVCUAPI cudaMSIPelement( siPMatrix X, ui ht, ui len, ui m, ui n );

#define cudaMSIequ0( MA, ht, len )            cudaVSI_equ0( MA, (ht)*(len) )
overror_t   __vcuf OVCUAPI  cudaMSIequ1( siPMatrix MA, ui len );  /* identity matrix */
overror_t   __vcuf OVCUAPI  cudaMSIequm1( siPMatrix MA, ui len );  /* neg. identity matrix */
overror_t   __vcuf OVCUAPI  cudaMSIouterprod( siPMatrix MA, siVector X,  siVector Y, ui ht, ui len );

overror_t   __vcuf OVCUAPI  cudaMSIRow_equ0( siPMatrix MA, ui ht, ui len, ui iRow );
overror_t   __vcuf OVCUAPI  cudaMSICol_equ0( siPMatrix MA, ui ht, ui len, ui iCol );
overror_t   __vcuf OVCUAPI  cudaMSIDia_equ0( siPMatrix MA, ui len );

overror_t   __vcuf OVCUAPI  cudaMSIRow_equC( siPMatrix MA, ui ht, ui len, ui iRow, short C );
overror_t   __vcuf OVCUAPI  cudaMSICol_equC( siPMatrix MA, ui ht, ui len, ui iCol, short C );
overror_t   __vcuf OVCUAPI  cudaMSIDia_equC( siPMatrix MA, ui len, short C );
overror_t   __vcuf OVCUAPI  cusdMSIRow_equC( siPMatrix MA, ui ht, ui len, ui iRow, short *d_C );
overror_t   __vcuf OVCUAPI  cusdMSICol_equC( siPMatrix MA, ui ht, ui len, ui iCol, short *d_C );
overror_t   __vcuf OVCUAPI  cusdMSIDia_equC( siPMatrix MA, ui len, short *d_C );

overror_t   __vcuf OVCUAPI  cudaMSIRow_equV( siPMatrix MA, ui ht, ui len, ui iRow, siVector X );
overror_t   __vcuf OVCUAPI  cudaMSICol_equV( siPMatrix MA, ui ht, ui len, ui iCol, siVector X );
overror_t   __vcuf OVCUAPI  cudaMSIDia_equV( siPMatrix MA, ui len, siVector X );

overror_t   __vcuf OVCUAPI  cudaMSITrd_equM( siPMatrix MA, siPMatrix MTrd, ui len );
overror_t   __vcuf OVCUAPI  cudaMSITrd_extract( siPMatrix MTrd, siPMatrix MA, ui len );

#define cudaMSIequM( MB, MA, ht, len )         cudaVSI_equV( MB, MA, (ht)*(len) )
#define cudaMSIequMhost( d_MB, h_MA, ht, len ) cudaVSI_equVhost( d_MB, h_MA, (ht)*(len) )
#define MSIequMdevice( h_MB, d_MA, ht, len )   VSI_equVdevice( h_MB, d_MA, (ht)*(len) )
#define cudaMSIneg( MB, MA, ht, len )          cudaVSI_neg( MB, MA, (ht)*(len) )
overror_t   __vcuf OVCUAPI  cudaMSIUequL( siPMatrix MA, ui len );
overror_t   __vcuf OVCUAPI  cudaMSILequU( siPMatrix MA, ui len );

            /* data-type conversions:  */
#define cudaMSItoUS( MUS, MSI, ht, len ) cudaV_SItoUS( (MUS), (MSI), (ht)*(len) )
#define cudaMUStoSI( MSI, MUS, ht, len ) cudaV_UStoSI( (MSI), (MUS), (ht)*(len) )
#define cudaMSItoBI( MBI, MSI, ht, len ) cudaV_SItoBI( (MBI), (MSI), (ht)*(len) )
#define cudaMSItoI(  MI,  MSI, ht, len ) cudaV_SItoI(  (MI),  (MSI), (ht)*(len) )
#define cudaMSItoLI( MLI, MSI, ht, len ) cudaV_SItoLI( (MLI), (MSI), (ht)*(len) )
#define cudaMSItoQI( MQI, MSI, ht, len ) cudaV_SItoQI( (MQI), (MSI), (ht)*(len) )
#define cudaMBItoSI( MSI, MBI, ht, len ) cudaV_BItoSI( (MSI), (MBI), (ht)*(len) )
#define cudaMItoSI(  MSI, MI,  ht, len ) cudaV_ItoSI(  (MSI), (MI),  (ht)*(len) )
#define cudaMLItoSI( MSI, MLI, ht, len ) cudaV_LItoSI( (MSI), (MLI), (ht)*(len) )
#define cudaMQItoSI( MSI, MQI, ht, len ) cudaV_QItoSI( (MSI), (MQI), (ht)*(len) )
#define cudaMSItoF(  MF,  MSI, ht, len ) cudaV_SItoF(  (MF),  (MSI), (ht)*(len) )
#define cudaMSItoD(  MD,  MSI, ht, len ) cudaV_SItoD(  (MD),  (MSI), (ht)*(len) )

/********  Extracting a submatrix and copying a submatrix back  *********/

overror_t  __vcuf OVCUAPI  cudaMSIsubmatrix( siPMatrix MSub, ui subHt,  ui subLen,
                          siPMatrix MSrce, ui srceHt,  ui srceLen,
                          ui firstRowInCol,  ui sampInCol,
                          ui firstColInRow,  ui sampInRow );

overror_t  __vcuf OVCUAPI  cudaMSIsubmatrix_equM( siPMatrix MDest, ui destHt, ui destLen,
                               ui firstRowInCol,  ui sampInCol,
                               ui firstColInRow,  ui sampInRow,
                               siPMatrix MSrce,  ui srceHt, ui srceLen );

overror_t  __vcuf OVCUAPI  cudaMSIequMblock(  siPMatrix MSub,  ui subHt,  ui subLen,
                          siPMatrix MSrce, ui srceHt,  ui srceLen,
                          ui firstRowInCol,  ui firstColInRow );

overror_t  __vcuf OVCUAPI  cudaMSIblock_equM( siPMatrix MDest,  ui destHt,  ui destLen,
                          ui firstRowInCol,  ui firstColInRow,
                          siPMatrix MSrce,  ui srceHt, ui srceLen );

overror_t  __vcuf OVCUAPI  cudaMSIequMblockT( siPMatrix MSub,  ui subHt, ui subLen,
                          siPMatrix MSrce,  ui srceHt,  ui srceLen,
                          ui firstRowInCol,  ui firstColInRow );

overror_t  __vcuf OVCUAPI  cudaMSIblock_equMT( siPMatrix MDest,  ui destHt,  ui destLen,
                          ui firstRowInCol,  ui firstColInRow,
                          siPMatrix MSrce,   ui srceHt,  ui srceLen );


/*****   Extracting a single row or a single column or the diagonal  *****
 *       and storing it into a vector                                    */

overror_t __vcuf OVCUAPI  cudaMSIRow_extract( siVector Y, siPMatrix MA, ui ht, ui len, ui iRow );
overror_t __vcuf OVCUAPI  cudaMSICol_extract( siVector Y, siPMatrix MA, ui ht, ui len, ui iCol );
overror_t __vcuf OVCUAPI  cudaMSIDia_extract( siVector Y, siPMatrix MA, ui len );


/**********  Deleting or inserting a row or a column *****************/

overror_t __vcuf OVCUAPI  cudaMSIRow_delete( siPMatrix MB, siPMatrix MA, ui htA, ui lenA, ui iRow );
overror_t __vcuf OVCUAPI  cudaMSICol_delete( siPMatrix MB, siPMatrix MA, ui htA, ui lenA, ui iCol );
overror_t __vcuf OVCUAPI  cudaMSIRow_insert( siPMatrix MB, siPMatrix MA, ui htB, ui lenB, ui iRow, siVector X );
overror_t __vcuf OVCUAPI  cudaMSICol_insert( siPMatrix MB, siPMatrix MA, ui htB, ui lenB, ui iCol, siVector X );


/******  One-dimensional vector operations **********************
         performed ashort all rows or all columns simultaneously,
         or ashort the diagonal of a square matrix                */

overror_t  __vcuf OVCUAPI  cudaMSIRows_max( siVector Y, siPMatrix MA, ui ht, ui len );
overror_t  __vcuf OVCUAPI  cudaMSICols_max( siVector Y, siPMatrix MA, ui ht, ui len );
overror_t  __vcuf OVCUAPI  cudaMSIDia_max(  short *h_RetVal, siPMatrix MA, ui len );
overror_t  __vcuf OVCUAPI  cusdMSIDia_max(  short *d_RetVal, siPMatrix MA, ui len );
overror_t  __vcuf OVCUAPI  cudaMSIRows_min( siVector Y, siPMatrix MA, ui ht, ui len );
overror_t  __vcuf OVCUAPI  cudaMSICols_min( siVector Y, siPMatrix MA, ui ht, ui len );
overror_t  __vcuf OVCUAPI  cudaMSIDia_min(  short *h_RetVal, siPMatrix MA, ui len );
overror_t  __vcuf OVCUAPI  cusdMSIDia_min(  short *d_RetVal, siPMatrix MA, ui len );

overror_t  __vcuf OVCUAPI  cudaMSIRows_rotate( siPMatrix MA, ui ht, ui len, ssize_t pos );
overror_t  __vcuf OVCUAPI  cudaMSICols_rotate( siPMatrix MA, ui ht, ui len, ssize_t pos );
overror_t  __vcuf OVCUAPI  cudaMSIRows_rotate_buf( siPMatrix MA, ui ht, ui len, ssize_t pos, siPMatrix MBuf );
overror_t  __vcuf OVCUAPI  cudaMSICols_rotate_buf( siPMatrix MA, ui ht, ui len, ssize_t pos, siPMatrix MBuf );
overror_t  __vcuf OVCUAPI  cudaMSIRows_reflect( siPMatrix MA, ui ht, ui len );
overror_t  __vcuf OVCUAPI  cudaMSICols_reflect( siPMatrix MA, ui ht, ui len );
overror_t  __vcuf OVCUAPI  cudaMSIRows_rev( siPMatrix MA, ui ht, ui len );
overror_t  __vcuf OVCUAPI  cudaMSICols_rev( siPMatrix MA, ui ht, ui len );
overror_t  __vcuf OVCUAPI  cudaMSIRows_distribution( uiPMatrix MAbund, siVector Limits, ui nBins, siPMatrix MX, ui ht, ui len, int mode );
overror_t  __vcuf OVCUAPI  cudaMSICols_distribution( uiPMatrix MAbund, siVector Limits, ui nBins, siPMatrix MX, ui ht, ui len, int mode );

/********  Operations involving two rows or two colums of one matrix  *****/

overror_t   __vcuf OVCUAPI  cudaMSIRows_exchange( siPMatrix MA, ui ht, ui len, ui i1, ui i2 );
overror_t   __vcuf OVCUAPI  cudaMSICols_exchange( siPMatrix MA, ui ht, ui len, ui i1, ui i2 );

/*****************  Transposing and rotating a matrix **********************/

overror_t  __vcuf OVCUAPI  cudaMSItranspose( siPMatrix MTr, siPMatrix MA, ui htTr, ui lenTr );
#define     cudaMSIrotate180( MRot, MA, htRot, lenRot )  cudaVSI_rev( MRot, MA, (htRot)*(lenRot) )
overror_t  __vcuf OVCUAPI  cudaMSIrotate90(  siPMatrix MRot, siPMatrix MA, ui htRot, ui lenRot );
overror_t  __vcuf OVCUAPI  cudaMSIrotate270( siPMatrix MRot, siPMatrix MA, ui htRot, ui lenRot );
overror_t  __vcuf OVCUAPI  cudaMSItranspose_buf( siPMatrix MTr, siPMatrix MA, ui htTr, ui lenTr, siPMatrix MBuf );

/**************************  Input and Output  **************************
	The input/output functions involve memory transfers from device
	to host memory or vice versa. The generic cudaMSI_input/output functions
	allocate their own host buffers, whereas the cudaMSI_xxx_buf functions
	take a user-supplied buffer vector h_Wk (size must be >= ht*len )
	and are much more efficient.                                       */

#define cudaMSIprint( MA, ht, len )  cudaMSIfprint( stdout, MA, ht, len, 80 )
overror_t __vf cudaMSIfprint( FILE *stream, siPMatrix MA, ui ht, ui len, unsigned linewidth );
overror_t __vf cudaMSIcprint( siPMatrix MA, ui ht, ui len );
#define cudaMSIprint_buf( MA, ht, len, h_Wk )  cudaMSIfprint_buf( stdout, MA, ht, len, 80, h_Wk )
overror_t __vf cudaMSIfprint_buf( FILE *stream, siPMatrix MA, ui ht, ui len, unsigned linewidth, siVector h_Wk );
overror_t __vf cudaMSIcprint_buf( siPMatrix MA, ui ht, ui len, siVector h_Wk );
overror_t __vf cudaMSIwrite( FILE *stream, siPMatrix X, ui ht, ui len  );
overror_t __vf cudaMSIread( siPMatrix X, ui ht, ui len, FILE *stream );
overror_t __vf cudaMSIwrite_buf( FILE *stream, siPMatrix X, ui ht, ui len, siVector h_Wk );
overror_t __vf cudaMSIread_buf( siPMatrix X, ui ht, ui len, FILE *stream, siVector h_Wk );
#define cudaMSIstore( str, MA, ht, len ) cudaVSI_store( str, MA, (len)*(ht) )
#define cudaMSIrecall( MA, ht, len, str) cudaVSI_recall( MA, (len)*(ht), str)
#define cudaMSIstore_buf( str, MA, ht, len, h_Wk ) cudaVSI_store( str, MA, (len)*(ht), h_Wk )
#define cudaMSIrecall_buf( MA, ht, len, str, h_Wk) cudaVSI_recall( MA, (len)*(ht), str, h_Wk)



/***************************************************************************
    cudaMSI_func	(working on matrices in device memory, input type siMatrix, 
	             scalar parameters reside on host and are passed by value)
    cusdMSI_func	(as cudaMSI_func except scalar parameters reside on device 
	             and are passed by address)                                 */


/***************************************************************************
 *  The following definitions are needed to access individual elements,    *
 *  and row pointers. As all addresses point to device memory, the usual   *
 *  mechanism of accessing elements, i.e., writing something like MA[m][n] *
 *  is not possible here!                                                  *
 *  Pro forma, the distinction between the data types siMatrix and         *
 *  siPMatrix is kept. However, in the present implementation, both of     *
 *  these types actually contain a pointer to the matrix element [0][0].   *
 *  For C++, inline functions ensure proper type checking at compile time, *
 *  while for plain-C, only a less safe type-cast is possible.             *
 ***************************************************************************/

#ifdef __cplusplus

inline void    cudaMSI_setElement( siMatrix MA, ui ht, ui len, ui m, ui n, short C )
	{	cudaMSIsetElement( (siPMatrix)(MA), ht, len, m, n, C );}
inline void    cusdMSI_setElement( siMatrix MA, ui ht, ui len, ui m, ui n, short *d_C )
	{	cusdMSIsetElement( (siPMatrix)(MA), ht, len, m, n, d_C );}
inline void    cudaMSI_getElement( short *y, siMatrix MA, ui ht, ui len, ui m, ui n )
	{	cudaMSIgetElement( y, (siPMatrix)(MA), ht, len, m, n );}
inline void    cusdMSI_getElement( short *d_y, siMatrix MA, ui ht, ui len, ui m, ui n )
	{	cudaMSIgetElement( y, (siPMatrix)(MA), ht, len, m, n );}
inline short * cudaMSI_Pelement( siMatrix MA, ui ht, ui len, ui m, ui n )
	{	return cudaMSIPelement( (siPMatrix)(MA), ht, len, m, n );}
inline short   cudaMSI_element( siMatrix MA, ui ht, ui len, ui m, ui n )
{	return cudaMSIelement( (siPMatrix)(MA), ht, len, m, n );}

inline overror_t  cudaMSI_equ0( siMatrix MA, ui ht, ui len )
	{	return cudaVSI_equ0( (siPMatrix)MA, (ht)*(len) ); }
inline overror_t  cudaMSI_equ1( siMatrix MA, ui len )
	{	return cudaMSIequ1( (siPMatrix)(MA), len );} /* identity matrix */
inline overror_t  cudaMSI_equm1( siMatrix MA, ui len )
	{	return cudaMSIequm1( (siPMatrix)(MA), len );} /* neg. identity matrix */

inline overror_t  cudaMSI_randomLC( siMatrix MA, ui ht, ui len, long seed, short MinVal, short MaxVal, V_RANDOMLCSTATE *h_state )
	{	return cudaVSI_randomLC( (siPMatrix)(MA), (ht)*(len), seed, MinVal, MaxVal, h_state );}
inline overror_t  cudaMSI_random( siMatrix MA, ui ht, ui len, long seed, short MinVal, short MaxVal )
	{	return cudaVSI_random( (siPMatrix)(MA), (ht)*(len), seed, MinVal, MaxVal );}
inline overror_t  cusdMSI_randomLC( siMatrix MA, ui ht, ui len, long seed, short *d_MinVal, short *d_MaxVal, V_RANDOMLCSTATE *h_state )
	{	return cusdVSI_randomLC( (siPMatrix)(MA), (ht)*(len), seed, d_MinVal, d_MaxVal, h_state );}
inline overror_t  cusdMSI_random( siMatrix MA, ui ht, ui len, long seed, short *d_MinVal, short *d_MaxVal )
	{	return cusdVSI_random( (siPMatrix)(MA), (ht)*(len), seed, d_MinVal, d_MaxVal );}
inline overror_t  cudaMSI_outerprod( siMatrix MA, siVector X,  siVector Y, ui ht, ui len )
{	return cudaMSIouterprod( (siPMatrix)(MA), X, Y, ht, len );}

inline overror_t  cudaMSI_Row_equ0( siMatrix MA, ui ht, ui len, ui iRow )
	{	return cudaMSIRow_equ0( (siPMatrix)MA, ht, len, iRow );}
inline overror_t  cudaMSI_Col_equ0( siMatrix MA, ui ht, ui len, ui iRow )
	{	return cudaMSICol_equ0( (siPMatrix)MA, ht, len, iRow );}
inline overror_t  cudaMSI_Dia_equ0( siMatrix MA, ui len )
	{	return cudaMSIDia_equ0( (siPMatrix)(MA), len );}

inline overror_t  cudaMSI_Row_equC( siMatrix MA, ui ht, ui len, ui iRow, short C )
	{	return cudaMSIRow_equC( (siPMatrix)MA, ht, len, iRow, C );}
inline overror_t  cudaMSI_Col_equC( siMatrix MA, ui ht, ui len, ui iRow, short C )
	{	return cudaMSICol_equC( (siPMatrix)MA, ht, len, iRow, C );}
inline overror_t  cudaMSI_Dia_equC( siMatrix MA, ui len, short C )
	{	return cudaMSIDia_equC( (siPMatrix)(MA), len, C );}

inline overror_t  cusdMSI_Row_equC( siMatrix MA, ui ht, ui len, ui iRow, short *d_C )
	{	return cusdMSIRow_equC( (siPMatrix)MA, ht, len, iRow, d_C );}
inline overror_t  cusdMSI_Col_equC( siMatrix MA, ui ht, ui len, ui iRow, short *d_C )
	{	return cusdMSICol_equC( (siPMatrix)MA, ht, len, iRow, d_C );}
inline overror_t  cusdMSI_Dia_equC( siMatrix MA, ui len, short *d_C )
	{	return cusdMSIDia_equC( (siPMatrix)(MA), len, d_C );}

inline overror_t  cudaMSI_Row_equV( siMatrix MA, ui ht, ui len, ui iRow, siVector X )
	{	return cudaMSIRow_equV( (siPMatrix)MA, ht, len, iRow, X );}
inline overror_t  cudaMSI_Col_equV( siMatrix MA, ui ht, ui len, ui iRow, siVector X )
	{	return cudaMSICol_equV( (siPMatrix)MA, ht, len, iRow, X );}
inline overror_t  cudaMSI_Dia_equV( siMatrix MA, ui len, siVector X )
	{	return cudaMSIDia_equV( (siPMatrix)(MA), len, X );}

inline overror_t  cudaMSI_Trd_equM( siMatrix MA, siMatrix MTrd, ui len )
	{	return cudaMSITrd_equM( (siPMatrix)(MA), (siPMatrix)(MTrd), len );}
inline overror_t  cudaMSI_Trd_extract( siMatrix MTrd, siMatrix MA, ui len )
	{	return cudaMSITrd_extract( (siPMatrix)(MTrd), (siPMatrix)(MA), len );}

inline overror_t cudaMSI_equM( siMatrix MB, siMatrix MA, ui ht, ui len )
	{	return cudaVSI_equV( (siPMatrix)MB, (siPMatrix)MA, (ht)*(len) );}
inline overror_t cudaMSI_equMhost( siMatrix d_MB, siMatrix h_MA, ui ht, ui len )
	{	return cudaVSI_equVhost( (siPMatrix)d_MB, (h_MA)[0], (ht)*(len) );}
inline overror_t MSI_equMdevice( siMatrix h_MB, siMatrix d_MA, ui ht, ui len )
	{	return VSI_equVdevice( h_MB[0], (siPMatrix)d_MA, (ht)*(len) );}
inline overror_t cudaMSI_neg( siMatrix MB, siMatrix MA, ui ht, ui len )
	{	return cudaVSI_neg( (siPMatrix)(MB), (siPMatrix)(MA), (ht)*(len) );}
inline overror_t  cudaMSI_UequL( siMatrix MA, ui len )
	{	return cudaMSIUequL( (siPMatrix)(MA), len );}
inline overror_t  cudaMSI_LequU( siMatrix MA, ui len )
	{	return cudaMSILequU( (siPMatrix)(MA), len );}

/************** Data-type interconversions  ****************************/

inline overror_t cudaM_UStoSI( siMatrix MSI, ubMatrix MUS, ui ht, ui len )
	{	return cudaV_UStoSI( (siVector)MSI, (usVector)MUS, (ht)*(len) );}
inline overror_t cudaM_BItoSI( siMatrix MSI, biMatrix MBI, ui ht, ui len )
	{	return cudaV_BItoSI( (siVector)MSI, (biVector)MBI, (ht)*(len) );}
inline overror_t cudaM_ItoSI(  siMatrix MSI, iMatrix MI,  ui ht, ui len )
	{	return cudaV_ItoSI(  (siVector)MSI, (iVector)MI,   (ht)*(len) );}
inline overror_t cudaM_LItoSI( siMatrix MSI, liMatrix MLI, ui ht, ui len )
	{	return cudaV_LItoSI( (siVector)MSI, (liVector)MLI, (ht)*(len) );}
inline overror_t cudaM_QItoSI( siMatrix MSI, qiMatrix MQI, ui ht, ui len )
	{	return cudaV_QItoSI( (siVector)MSI, (qiVector)MQI, (ht)*(len) );}
inline overror_t cudaM_SItoF(  fMatrix MF,  siMatrix MSI, ui ht, ui len )
	{	return cudaV_SItoF(  (fVector)MF,   (siVector)MSI, (ht)*(len) );}
inline overror_t cudaM_SItoD(  dMatrix MD,  siMatrix MSI, ui ht, ui len )
	{	return cudaV_SItoD(  (dVector)MD,   (siVector)MSI, (ht)*(len) );}

/********  Extracting a submatrix and copying a submatrix back  *********/

inline overror_t cudaMSI_submatrix( siMatrix MSub, ui subHt, ui subLen, siMatrix MSrce, ui srceHt, ui srceLen,
                      ui firstRowInCol, ui sampInCol, ui firstColInRow, ui sampInRow )
	{	return cudaMSIsubmatrix(  (siPMatrix)(MSub), subHt, subLen,
		                         (siPMatrix)(MSrce), srceHt, srceLen,
								 firstRowInCol, sampInCol, firstColInRow, sampInRow ); }

inline overror_t cudaMSI_submatrix_equM( siMatrix MDest, ui destHt, ui destLen,
                           ui firstRowInCol, ui sampInCol, ui firstColInRow, ui sampInRow,
                           siMatrix MSrce, ui srceHt, ui srceLen )
	{	return cudaMSIsubmatrix_equM(  (siPMatrix)(MDest), destHt, destLen,
                             firstRowInCol, sampInCol, firstColInRow, sampInRow,
							 (siPMatrix)(MSrce), srceHt, srceLen );}

inline overror_t cudaMSI_equMblock( siMatrix MSub, ui subHt, ui subLen, siMatrix MSrce, ui srceHt, ui srceLen,
                      ui firstRowInCol, ui firstColInRow )
{	return cudaMSIequMblock(  (siPMatrix)(MSub), subHt, subLen,
						   (siPMatrix)(MSrce), srceHt, srceLen, firstRowInCol, firstColInRow );}

inline overror_t cudaMSI_block_equM( siMatrix MDest, ui destHt, ui destLen,
                       ui firstRowInCol, ui firstColInRow,
                       siMatrix MSrce, ui srceHt, ui srceLen )
	{	return cudaMSIblock_equM( (siPMatrix)(MDest), destHt, destLen,
                             firstRowInCol, firstColInRow,
							 (siPMatrix)(MSrce), srceHt, srceLen );}

inline overror_t cudaMSI_equMblockT( siMatrix MSub, ui subHt, ui subLen, siMatrix MSrce, ui srceHt, ui srceLen,
                      ui firstRowInCol, ui firstColInRow )
	{	return cudaMSIequMblockT(  (siPMatrix)(MSub), subHt, subLen,
                             (siPMatrix)(MSrce), srceHt, srceLen,
							 firstRowInCol, firstColInRow );}

inline overror_t cudaMSI_block_equMT( siMatrix MDest, ui destHt, ui destLen,
                       ui firstRowInCol, ui firstColInRow,
                       siMatrix MSrce, ui srceHt, ui srceLen )
	{	return cudaMSIblock_equMT( (siPMatrix)(MDest), destHt, destLen,
                             firstRowInCol, firstColInRow,
							 (siPMatrix)(MSrce), srceHt, srceLen );}

/*****   Extracting a single row or a single column or the diagonal  ******
 *       and storing it into a vector                                     */

inline overror_t cudaMSI_Row_extract( siVector Y, siMatrix MA, ui ht, ui len, ui iRow ) 
	{	return cudaMSIRow_extract( Y, (siPMatrix)(MA), ht, len, iRow );}
inline overror_t cudaMSI_Col_extract( siVector Y, siMatrix MA, ui ht, ui len, ui iCol ) 
	{	return cudaMSICol_extract( Y, (siPMatrix)(MA), ht, len, iCol );}
inline overror_t cudaMSI_Dia_extract( siVector Y, siMatrix MA, ui len )
	{	return cudaMSIDia_extract( Y, (siPMatrix)(MA), len );}

/**************  Deleting or inserting a row or a column   ***************/

inline overror_t cudaMSI_Row_delete( siMatrix MB, siMatrix MA, ui htA, ui lenA, ui iRow )
	{	return cudaMSIRow_delete( (siPMatrix)(MB), (siPMatrix)(MA), htA, lenA, iRow );}
inline overror_t cudaMSI_Col_delete( siMatrix MB, siMatrix MA, ui htA, ui lenA, ui iCol )
	{	return cudaMSICol_delete( (siPMatrix)(MB), (siPMatrix)(MA), htA, lenA, iCol );}
inline overror_t cudaMSI_Row_insert( siMatrix MB, siMatrix MA, ui htB, ui lenB, ui iRow, siVector X )
	{	return cudaMSIRow_insert( (siPMatrix)(MB), (siPMatrix)(MA), htB, lenB, iRow, X );}
inline overror_t cudaMSI_Col_insert( siMatrix MB, siMatrix MA, ui htB, ui lenB, ui iCol, siVector X )
	{	return cudaMSICol_insert( (siPMatrix)(MB), (siPMatrix)(MA), htB, lenB, iCol, X );}


/******  One-dimensional vector operations **********************
         performed along all rows or all columns simultaneously,
         or along the diagonal of a square matrix                */

inline overror_t cudaMSI_Rows_max( siVector Y, siMatrix MA, ui ht, ui len )
	{	return cudaMSIRows_max( Y, (siPMatrix)(MA), ht, len );}
inline overror_t cudaMSI_Cols_max( siVector Y, siMatrix MA, ui ht, ui len )
	{	return cudaMSICols_max( Y, (siPMatrix)(MA), ht, len );}
inline overror_t cudaMSI_Dia_max(  short *h_RetValPtr, siMatrix MA, ui len )
	{	return cudaMSIDia_max(  h_RetValPtr, (siPMatrix)(MA), len );}
inline overror_t cusdMSI_Dia_max(  short *d_RetValPtr, siMatrix MA, ui len )
	{	return cusdMSIDia_max(  d_RetValPtr, (siPMatrix)(MA), len );}
inline overror_t cudaMSI_Rows_min( siVector Y, siMatrix MA, ui ht, ui len )
	{	return cudaMSIRows_min( Y, (siPMatrix)(MA), ht, len );}
inline overror_t cudaMSI_Cols_min( siVector Y, siMatrix MA, ui ht, ui len )
	{	return cudaMSICols_min( Y, (siPMatrix)(MA), ht, len );}
inline overror_t cudaMSI_Dia_min(  short *h_RetValPtr, siMatrix MA, ui len )
	{	return cudaMSIDia_min(  h_RetValPtr, (siPMatrix)(MA), len );}
inline overror_t cusdMSI_Dia_min(  short *d_RetValPtr, siMatrix MA, ui len )
	{	return cusdMSIDia_min(  d_RetValPtr, (siPMatrix)(MA), len );}

inline overror_t cudaMSI_Rows_rotate( siMatrix MA, ui ht, ui len, ssize_t pos)
	{	return cudaMSIRows_rotate( (siPMatrix)(MA), ht, len, pos );}
inline overror_t cudaMSI_Cols_rotate( siMatrix MA, ui ht, ui len, ssize_t pos)
	{	return cudaMSICols_rotate( (siPMatrix)(MA), ht, len, pos );}
inline overror_t cudaMSI_Rows_rotate_buf( siMatrix MA, ui ht, ui len, ssize_t pos, siMatrix MBuf) 
	{	return cudaMSIRows_rotate_buf( (siPMatrix)(MA), ht, len, pos, (siPMatrix)(MBuf) );}
inline overror_t cudaMSI_Cols_rotate_buf( siMatrix MA, ui ht, ui len, ssize_t pos, siMatrix MBuf) 
	{	return cudaMSICols_rotate_buf( (siPMatrix)(MA), ht, len, pos, (siPMatrix)(MBuf) );}
inline overror_t cudaMSI_Rows_reflect( siMatrix MA, ui ht, ui len )
	{	return cudaMSIRows_reflect( (siPMatrix)(MA), ht, len );}
inline overror_t cudaMSI_Cols_reflect( siMatrix MA, ui ht, ui len )
	{	return cudaMSICols_reflect( (siPMatrix)(MA), ht, len );}
inline overror_t cudaMSI_Rows_rev( siMatrix MA, ui ht, ui len )
	{	return cudaMSIRows_rev( (siPMatrix)(MA), ht, len );}
inline overror_t cudaMSI_Cols_rev( siMatrix MA, ui ht, ui len )
	{	return cudaMSICols_rev( (siPMatrix)(MA), ht, len );}
inline overror_t  cudaMSI_Rows_distribution( uiMatrix MAbund, siVector Limits, ui nBins, siMatrix MX, ui ht, ui len, int mode )
	{	return cudaMSIRows_distribution( (uiPMatrix)MAbund, Limits, nBins, (siPMatrix)MX, ht, len, mode ); }
inline overror_t  cudaMSI_Cols_distribution( uiMatrix MAbund, siVector Limits, ui nBins, siMatrix MX, ui ht, ui len, int mode )
	{	return cudaMSICols_distribution( (uiPMatrix)MAbund, Limits, nBins, (siPMatrix)MX, ht, len, mode ); }

/********  Operations involving two rows or two colums of one matrix  *****/

inline overror_t cudaMSI_Rows_exchange( siMatrix MA, ui ht, ui len, ui row1, ui row2 )
	{	return cudaMSIRows_exchange( (siPMatrix)(MA), ht, len, row1, row2 );}
inline overror_t cudaMSI_Cols_exchange( siMatrix MA, ui ht, ui len, ui col1, ui col2 )
	{	return cudaMSICols_exchange( (siPMatrix)(MA), ht, len, col1, col2 );}

/*************** Transposing and rotating a matrix **********************/

inline overror_t cudaMSI_transpose( siMatrix MTr, siMatrix MA, ui htTr, ui lenTr )
	{	return cudaMSItranspose( (siPMatrix)(MTr), (siPMatrix)(MA), htTr, lenTr );}
       /*  dimensions htTr, lenTr are those of the transposed matrix, not of the original!   */
inline overror_t cudaMSI_rotate90( siMatrix MRot, siMatrix MA, ui htRot, ui lenRot )
	{	return cudaMSIrotate90( (siPMatrix)(MRot), (siPMatrix)(MA), htRot, lenRot );}
inline overror_t cudaMSI_rotate180( siMatrix MRot, siMatrix MA, ui htRot, ui lenRot )
	{	return cudaVSI_rev( (siPMatrix)(MRot), (siPMatrix)(MA), (htRot)*(lenRot) );}
inline overror_t cudaMSI_rotate270( siMatrix MRot, siMatrix MA, ui htRot, ui lenRot )
	{	return cudaMSIrotate270( (siPMatrix)(MRot), (siPMatrix)(MA), htRot, lenRot );}
inline overror_t cudaMSI_transpose_buf( siMatrix MTr, siMatrix MA, ui htTr, ui lenTr, siMatrix MBuf )
	{	return cudaMSItranspose_buf( (siPMatrix)(MTr), (siPMatrix)(MA), htTr, lenTr, (siPMatrix)(MBuf) );}

/**************************  Input and Output  **************************
	The input/output functions involve memory transfers from device
	to host memory or vice versa. The generic cudaMSI_input/output functions
	allocate their own host buffers, whereas the cudaMSI_xxx_buf functions
	take a user-supplied buffer vector h_Wk (size must be >= ht*len )
	and are much more efficient.                                       */

inline overror_t cudaMSI_fprint( FILE *stream, siMatrix MA, ui ht, ui len, unsigned linewidth )
	{	return cudaMSIfprint( stream, (siPMatrix)(MA), ht, len, linewidth ); }
inline overror_t cudaMSI_print( siMatrix MA, ui ht, ui len )
	{	return cudaMSIfprint( stdout, (siPMatrix)(MA), ht, len, 80 ); }
inline overror_t cudaMSI_cprint( siMatrix MA, ui ht, ui len )
	{	return cudaMSIcprint( (siPMatrix)(MA), ht, len ); }
inline overror_t cudaMSI_fprint_buf( FILE *stream, siMatrix d_MA, ui ht, ui len, unsigned linewidth, siVector h_Wk )
	{	return cudaMSIfprint_buf( stream, (siPMatrix)(d_MA), ht, len, linewidth, h_Wk ); }
inline overror_t cudaMSI_print_buf( siMatrix d_MA, ui ht, ui len, siVector h_Wk )
	{	return cudaMSIfprint_buf( stdout, (siPMatrix)(d_MA), ht, len, 80, h_Wk ); }
inline overror_t cudaMSI_cprint_buf( siMatrix d_MA, ui ht, ui len, siVector h_Wk )
	{	return cudaMSIcprint_buf( (siPMatrix)(d_MA), ht, len, h_Wk ); }
		/*  cudaMSI_print, cudaMSI_cprint usable only for console applications! */
inline overror_t  cudaMSI_write( FILE *stream, siMatrix MA, ui ht, ui len )
	{	return cudaMSIwrite( stream, (siPMatrix)(MA), ht, len ); }
inline overror_t cudaMSI_read( siMatrix MA, ui ht, ui len, FILE *stream )
	{	return cudaMSIread( (siPMatrix)(MA), ht, len, stream ); }
inline overror_t  cudaMSI_write_buf( FILE *stream, siMatrix d_MA, ui ht, ui len, siVector h_Wk )
	{	return cudaMSIwrite_buf( stream, (siPMatrix)(d_MA), ht, len, h_Wk ); }
inline overror_t cudaMSI_read_buf( siMatrix d_MA, ui ht, ui len, FILE *stream, siVector h_Wk )
	{	return cudaMSIread_buf( (siPMatrix)(d_MA), ht, len, stream, h_Wk ); }
                                   /* write and read in ascii format */
inline overror_t cudaMSI_store( FILE *stream, siMatrix MA, ui ht, ui len )
{	return cudaVSI_store( stream, (siPMatrix)(MA), (len)*(ht) ); }
inline overror_t cudaMSI_recall( siMatrix MA, ui ht, ui len, FILE *stream )
	{	return cudaVSI_recall( (siPMatrix)(MA), (len)*(ht), stream ); }
inline overror_t cudaMSI_store_buf( FILE *stream, siMatrix d_MA, ui ht, ui len, siVector h_Wk )
{	return cudaVSI_store_buf( stream, (siPMatrix)(d_MA), (len)*(ht), h_Wk ); }
inline overror_t cudaMSI_recall_buf( siMatrix d_MA, ui ht, ui len, FILE *stream, siVector h_Wk )
	{	return cudaVSI_recall_buf( (siPMatrix)(d_MA), (len)*(ht), stream, h_Wk ); }
                                  /* store and recall in binary format */

#else  /* plain-C, not C++: type-cast used to transform siMatrix into siPMatrix */

/***  Addressing single elements of dynamically allocated matrices: ******/

#define cudaMSI_setElement( MA, ht, len, m, n, C ) cudaMSIsetElement( (siPMatrix)(MA), ht, len, m, n, C )
#define cusdMSI_setElement( MA, ht, len, m, n, C ) cusdMSIsetElement( (siPMatrix)(MA), ht, len, m, n, C )
#define cudaMSI_getElement( y, MA, ht, len, m, n ) cudaMSIgetElement( y, (siPMatrix)(MA), ht, len, m, n )
#define cusdMSI_getElement( y, MA, ht, len, m, n ) cusdMSIgetElement( y, (siPMatrix)(MA), ht, len, m, n )
#define cudaMSI_Pelement( MA, ht, len, m, n )      cudaMSIPelement( (siPMatrix)(MA), ht, len, m, n )
                     /* returns a pointer to MA[m][n]. */
#define cudaMSI_element( MA, ht, len, m, n )       cudaMSIelement( (siPMatrix)(MA), ht, len, m, n )

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
        VSI_equ1( (siVector)MA, ht * len );
*/

#define cudaMSI_equ0( MA, ht, len )            cudaVSI_equ0( (siPMatrix)(MA), (ht)*(len) )
#define cudaMSI_equ1( MA, len )                cudaMSIequ1( (siPMatrix)(MA), len ) /* identity matrix */
#define cudaMSI_equm1( MA, len )               cudaMSIequm1( (siPMatrix)(MA), len ) /* neg. identity matrix */
#define cudaMSI_randomLC( MA, ht, len, seed, Min, Max, h_state )      cudaVSI_randomLC( MA, (ht)*(len), seed, Min, Max, h_state )
#define cudaMSI_random( MA, ht, len, seed, Min, Max )                 cudaVSI_random( MA, (ht)*(len), seed, Min, Max )
#define cusdMSI_randomLC( MA, ht, len, seed, d_Min, d_Max, h_state )  cudaVSI_randomLC( MA, (ht)*(len), seed, d_Min, d_Max, h_state )
#define cusdMSI_random( MA, ht, len, seed, d_Min, d_Max )             cudaVSI_random( MA, (ht)*(len), seed, d_Min, d_Max )
#define cudaMSI_outerprod( MA, X, Y, ht, len ) cudaMSIouterprod( (siPMatrix)(MA), X, Y, ht, len )
                       /* sizX=ht, sizY=len */
#define cudaMSI_Row_equ0( MA, ht, len, iRow )  cudaMSIRow_equ0( (siPMatrix)(MA), ht, len, iRow )
#define cudaMSI_Col_equ0( MA, ht, len, iCol )  cudaMSICol_equ0( (siPMatrix)(MA), ht, len, iCol )
#define cudaMSI_Dia_equ0( MA, len )            cudaMSIDia_equ0( (siPMatrix)(MA), len )
#define cudaMSI_Row_equC( MA, ht, len, iRow, C ) cudaMSIRow_equC( (siPMatrix)(MA), ht, len, iRow, C )
#define cudaMSI_Col_equC( MA, ht, len, iCol, C ) cudaMSICol_equC( (siPMatrix)(MA), ht, len, iCol, C )
#define cudaMSI_Dia_equC( MA, len, C )           cudaMSIDia_equC( (siPMatrix)(MA), len, C )
#define cusdMSI_Row_equC( MA, ht, len, iRow, d_C ) cusdMSIRow_equC( (siPMatrix)(MA), ht, len, iRow, d_C )
#define cusdMSI_Col_equC( MA, ht, len, iCol, d_C ) cusdMSICol_equC( (siPMatrix)(MA), ht, len, iCol, d_C )
#define cusdMSI_Dia_equC( MA, len, d_C )           cusdMSIDia_equC( (siPMatrix)(MA), len, d_C )

#define cudaMSI_Row_equV( MA, ht, len, iRow, X ) cudaMSIRow_equV( (siPMatrix)(MA), ht, len, iRow, X )
#define cudaMSI_Col_equV( MA, ht, len, iCol, X ) cudaMSICol_equV( (siPMatrix)(MA), ht, len, iCol, X )
#define cudaMSI_Dia_equV( MA, len, X )           cudaMSIDia_equV( (siPMatrix)(MA), len, X )

#define cudaMSI_Trd_equM( MA, MTrd, len )    cudaMSITrd_equM( (siPMatrix)(MA), (siPMatrix)(MTr)d, len )
#define cudaMSI_Trd_extract( MTrd, MA, len ) cudaMSITrd_extract( (siPMatrix)(MTr)d, (siPMatrix)(MA), len )

#define cudaMSI_equM( MB, MA, ht, len )      cudaVSI_equV( (siPMatrix)(MB), (siPMatrix)(MA), (ht)*(len) )
#define cudaMSI_equMhost( MB, MA, ht, len )  cudaVSI_equVhost( (siPMatrix)(MB), MA[0], (ht)*(len) )
#define MSI_equMdevice( MB, MA, ht, len )    VSI_equVdevice( MB[0], (siPMatrix)(MA), (ht)*(len) )
#define cudaMSI_neg( MB, MA, ht, len )       cudaVSI_neg( (siPMatrix)(MB), (siPMatrix)(MA), (ht)*(len) )

#define cudaMSI_UequL( MA, len ) cudaMSIUequL( (siPMatrix)(MA), len )
#define cudaMSI_LequU( MA, len ) cudaMSILequU( (siPMatrix)(MA), len )


/************** Data-type interconversions  ****************************/

#define cudaM_SItoUS( MUS, MSI, ht, len ) cudaV_SItoUS( (ubVector)(MUS), (siVector)(MSI), (ht)*(len) )
#define cudaM_UStoSI( MSI, MUS, ht, len ) cudaV_UStoSI( (siVector)(MSI), (usVector)(MUS), (ht)*(len) )
#define cudaM_SItoBI( MBI, MSI, ht, len ) cudaV_SItoBI( (biVector)(MBI), (siVector)(MSI), (ht)*(len) )
#define cudaM_SItoI(  MI,  MSI, ht, len ) cudaV_SItoI(  (iVector)(MI),   (siVector)(MSI), (ht)*(len) )
#define cudaM_SItoLI( MLI, MSI, ht, len ) cudaV_SItoLI( (liVector)(MLI), (siVector)(MSI), (ht)*(len) )
#define cudaM_SItoQI( MQI, MSI, ht, len ) cudaV_SItoQI( (qiVector)(MQI), (siVector)(MSI), (ht)*(len) )
#define cudaM_BItoSI( MSI, MBI, ht, len ) cudaV_BItoSI( (siVector)(MSI), (biVector)(MBI), (ht)*(len) )
#define cudaM_ItoSI(  MSI, MI,  ht, len ) cudaV_ItoSI(  (siVector)(MSI), (iVector)(MI),   (ht)*(len) )
#define cudaM_LItoSI( MSI, MLI, ht, len ) cudaV_LItoSI( (siVector)(MSI), (liVector)(MLI), (ht)*(len) )
#define cudaM_QItoSI( MSI, MQI, ht, len ) cudaV_QItoSI( (siVector)(MSI), (qiVector)(MQI), (ht)*(len) )
#define cudaM_SItoF(  MF,  MSI, ht, len ) cudaV_SItoF(  (fVector)(MF),   (siVector)(MSI), (ht)*(len) )
#define cudaM_SItoD(  MD,  MSI, ht, len ) cudaV_SItoD(  (dVector)(MD),   (siVector)(MSI), (ht)*(len) )

/********  Extracting a submatrix and copying a submatrix back  *********/

#define cudaMSI_submatrix( MSub, subHt, subLen, MSrce, srceHt, srceLen, \
                      firstRowInCol, sampInCol, firstColInRow, sampInRow ) \
               cudaMSIsubmatrix(  (siPMatrix)(MSub), subHt, subLen, \
                             (siPMatrix)(MSrce), srceHt, srceLen, \
                             firstRowInCol, sampInCol, firstColInRow, sampInRow )

#define cudaMSI_submatrix_equM( MDest, destHt, destLen, \
                           firstRowInCol, sampInCol, firstColInRow, sampInRow, \
                           MSrce, srceHt, srceLen ) \
               cudaMSIsubmatrix_equM(  (siPMatrix)(MDest), destHt, destLen, \
                             firstRowInCol, sampInCol, firstColInRow, sampInRow, \
                             (siPMatrix)(MSrce), srceHt, srceLen )

#define cudaMSI_equMblock( MSub, subHt, subLen, \
                      MSrce, srceHt, srceLen, \
                      firstRowInCol, firstColInRow ) \
               cudaMSIequMblock(  (siPMatrix)(MSub), subHt, subLen, \
                             (siPMatrix)(MSrce), srceHt, srceLen, \
                             firstRowInCol, firstColInRow )

#define cudaMSI_block_equM( MDest, destHt, destLen, \
                       firstRowInCol, firstColInRow, \
                       MSrce, srceHt, srceLen ) \
               cudaMSIblock_equM( (siPMatrix)(MDest), destHt, destLen, \
                             firstRowInCol, firstColInRow, \
                             (siPMatrix)(MSrce), srceHt, srceLen )

#define cudaMSI_equMblockT( MSub, subHt, subLen, \
                      MSrce, srceHt, srceLen, \
                      firstRowInCol, firstColInRow ) \
               cudaMSIequMblockT(  (siPMatrix)(MSub), subHt, subLen, \
                             (siPMatrix)(MSrce), srceHt, srceLen, \
                             firstRowInCol, firstColInRow )

#define cudaMSI_block_equMT( MDest, destHt, destLen, \
                       firstRowInCol, firstColInRow, \
                       MSrce, srceHt, srceLen ) \
               cudaMSIblock_equMT( (siPMatrix)(MDest), destHt, destLen, \
                             firstRowInCol, firstColInRow, \
                             (siPMatrix)(MSrce), srceHt, srceLen )

/*****   Extracting a single row or a single column or the diagonal  ******
 *       and storing it into a vector                                     */

#define cudaMSI_Row_extract( Y, MA, ht, len, iRow ) \
                                     cudaMSIRow_extract( Y, (siPMatrix)(MA), ht, len, iRow )
#define cudaMSI_Col_extract( Y, MA, ht, len, iCol ) \
                                     cudaMSICol_extract( Y, (siPMatrix)(MA), ht, len, iCol )
#define cudaMSI_Dia_extract( Y, MA, len ) cudaMSIDia_extract( Y, (siPMatrix)(MA), len )


/**************  Deleting or inserting a row or a column   ***************/

#define cudaMSI_Row_delete( MB, MA, htA, lenA, iRow ) \
                           cudaMSIRow_delete( (siPMatrix)(MB), (siPMatrix)(MA), htA, lenA, iRow )
#define cudaMSI_Col_delete( MB, MA, htA, lenA, iCol ) \
                           cudaMSICol_delete( (siPMatrix)(MB), (siPMatrix)(MA), htA, lenA, iCol )
#define cudaMSI_Row_insert( MB, MA, htB, lenB, iRow, X ) \
                           cudaMSIRow_insert( (siPMatrix)(MB), (siPMatrix)(MA), htB, lenB, iRow, X )
#define cudaMSI_Col_insert( MB, MA, htB, lenB, iCol, X ) \
                           cudaMSICol_insert( (siPMatrix)(MB), (siPMatrix)(MA), htB, lenB, iCol, X )

/******  One-dimensional vector operations **********************
         performed ashort all rows or all columns simultaneously,
         or ashort the diagonal of a square matrix                */

#define cudaMSI_Rows_max( Y, MA, ht, len )     cudaMSIRows_max( Y, (siPMatrix)(MA), ht, len )
#define cudaMSI_Cols_max( Y, MA, ht, len )     cudaMSICols_max( Y, (siPMatrix)(MA), ht, len )
#define cudaMSI_Dia_max(  h_RetPtr, MA, len )  cudaMSIDia_max( h_RetPtr, (siPMatrix)(MA), len )
#define cusdMSI_Dia_max(  d_RetPtr, MA, len )  cusdMSIDia_max( d_RetPtr, (siPMatrix)(MA), len )
#define cudaMSI_Rows_min( Y, MA, ht, len )     cudaMSIRows_min( Y, (siPMatrix)(MA), ht, len )
#define cudaMSI_Cols_min( Y, MA, ht, len )     cudaMSICols_min( Y, (siPMatrix)(MA), ht, len )
#define cudaMSI_Dia_min(  h_RetPtr, MA, len )  cudaMSIDia_min( h_RetPtr, (siPMatrix)(MA), len )
#define cusdMSI_Dia_min(  d_RetPtr, MA, len )  cusdMSIDia_min( d_RetPtr, (siPMatrix)(MA), len )

#define cudaMSI_Rows_rotate( MA, ht, len, pos) cudaMSIRows_rotate( (siPMatrix)(MA), ht, len, pos )
#define cudaMSI_Cols_rotate( MA, ht, len, pos) cudaMSICols_rotate( (siPMatrix)(MA), ht, len, pos )
#define cudaMSI_Rows_rotate_buf( MA, ht, len, pos, MBuf) cudaMSIRows_rotate_buf( (siPMatrix)(MA), ht, len, pos, (siPMatrix)(MBuf) )
#define cudaMSI_Cols_rotate_buf( MA, ht, len, pos, MBuf) cudaMSICols_rotate_buf( (siPMatrix)(MA), ht, len, pos, (siPMatrix)(MBuf) )
#define cudaMSI_Rows_reflect( MA, ht, len)     cudaMSIRows_reflect( (siPMatrix)(MA), ht, len )
#define cudaMSI_Cols_reflect( MA, ht, len)     cudaMSICols_reflect( (siPMatrix)(MA), ht, len )
#define cudaMSI_Rows_rev( MA, ht, len)         cudaMSIRows_rev( (siPMatrix)(MA), ht, len )
#define cudaMSI_Cols_rev( MA, ht, len)         cudaMSICols_rev( (siPMatrix)(MA), ht, len )
#define cudaMSI_Rows_distribution( MAbund, Limits, nBins, MX, ht, len, mode ) cudaMSIRows_distribution( (uiPMatrix)MAbund, Limits, nBins, (siPMatrix)MX, ht, len, mode )
#define cudaMSI_Cols_distribution( MAbund, Limits, nBins, MX, ht, len, mode ) cudaMSICols_distribution( (uiPMatrix)MAbund, Limits, nBins, (siPMatrix)MX, ht, len, mode )

/********  Operations involving two rows or two colums of one matrix  *****/

#define cudaMSI_Rows_exchange( MA, ht, len, row1, row2 ) \
                             cudaMSIRows_exchange( (siPMatrix)(MA), ht, len, row1, row2 )
#define cudaMSI_Cols_exchange( MA, ht, len, col1, col2 ) \
                             cudaMSICols_exchange( (siPMatrix)(MA), ht, len, col1, col2 )

/************  Transposing and rotating a matrix **********************/

#define cudaMSI_transpose( MTr, MA, htTr, lenTr ) \
             cudaMSItranspose( (siPMatrix)(MTr), (siPMatrix)(MA), htTr, lenTr )
       /*  dimensions htTr, lenTr are those of the transposed matrix,
           not of the original!                */
#define cudaMSI_rotate90( MRot, MA, htRot, lenRot ) \
             cudaMSIrotate90( (siPMatrix)(MRot), (siPMatrix)(MA), htRot, lenRot )
#define cudaMSI_rotate180( MRot, MA, htRot, lenRot ) \
             cudaVSI_rev( (siPMatrix)(MRot), (siPMatrix)(MA), (htRot)*(lenRot) )
#define cudaMSI_rotate270( MRot, MA, htRot, lenRot ) \
             cudaMSIrotate270( (siPMatrix)(MRot), (siPMatrix)(MA), htRot, lenRot )
#define cudaMSI_transpose_buf( MTr, MA, htTr, lenTr, MBuf ) \
             cudaMSItranspose_buf( (siPMatrix)(MTr), (siPMatrix)(MA), htTr, lenTr, (siPMatrix)(MBuf) )

/**************************  Input and Output  **************************
	The input/output functions involve memory transfers from device
	to host memory or vice versa. The generic cudaMSI_input/output functions
	allocate their own host buffers, whereas the cudaMSI_xxx_buf functions
	take a user-supplied buffer vector h_Wk (size must be >= ht*len )
	and are much more efficient.                                       */

#define cudaMSI_fprint( stream, MA, ht, len, linewidth ) \
                    cudaMSIfprint( stream, (siPMatrix)(MA), ht, len, linewidth )
#define cudaMSI_print( MA, ht, len )  cudaMSIfprint( stdout, (siPMatrix)(MA), ht, len, 80 )
#define cudaMSI_cprint( MA, ht, len ) cudaMSIcprint( (siPMatrix)(MA), ht, len )
#define cudaMSI_fprint_buf( stream, MA, ht, len, linewidth, h_Wk ) \
                    cudaMSIfprint_buf( stream, (siPMatrix)(MA), ht, len, linewidth, h_Wk )
#define cudaMSI_print_buf( MA, ht, len )  cudaMSIfprint_buf( stdout, (siPMatrix)(MA), ht, len, 80, h_Wk )
#define cudaMSI_cprint_buf( MA, ht, len ) cudaMSIcprint_buf( (siPMatrix)(MA), ht, len, h_Wk )
  /*  cudaMSI_print, cudaMSI_cprint usable only for console applications! */
#define cudaMSI_write( str, MA, ht, len )   cudaMSIwrite( str, (siPMatrix)(MA), ht, len )
#define cudaMSI_read( MA, ht, len, str )    cudaMSIread( (siPMatrix)(MA), ht, len, str )
#define cudaMSI_write_buf( str, MA, ht, len, h_Wk )   cudaMSIwrite_buf( str, (siPMatrix)(MA), ht, len, h_Wk )
#define cudaMSI_read_buf( MA, ht, len, str, h_Wk )    cudaMSIread_buf( (siPMatrix)(MA), ht, len, str, h_Wk )
                                   /* write and read in ascii format */
#define cudaMSI_store( str, MA, ht, len )   cudaVSI_store( str, (siPMatrix)(MA), (len)*(ht) )
#define cudaMSI_recall( MA, ht, len, str)   cudaVSI_recall( (siPMatrix)(MA), (len)*(ht), str)
#define cudaMSI_store_buf( str, MA, ht, len, h_Wk )   cudaVSI_store_buf( str, (siPMatrix)(MA), (len)*(ht), h_Wk )
#define cudaMSI_recall_buf( MA, ht, len, str, h_Wk)   cudaVSI_recall_buf( (siPMatrix)(MA), (len)*(ht), str, h_Wk )
                                  /* store and recall in binary format */

#endif /* plain-C or C++ for functions working on device memory  */


/*******************  Functions working on host memory: **********************
 *                                                                           *
 *	MSIcu_func		(working on matrices in host memory, input type siMatrix,*
 *	scalar parameters on host and passed by value)                           *
 *****************************************************************************/ 

/****************  Initialization  ****************************************/

#define MSIcu_equ0( MA, ht, len )                   VSIcu_equ0( (MA)[0], (ht)*(len) )
#define MSIcu_equ1( MA, len )                       MSIcuequ1( (MA)[0], len ) /* identity matrix */
#define MSIcu_equm1( MA, len )                      MSIcuequm1( (MA)[0], len ) /* neg. identity matrix */
#define MSIcu_randomLC( MA, ht, len, seed, Min, Max, state ) VSIcu_randomLC( (MA)[0], (ht)*(len), seed, Min, Max, state )
#define MSIcu_random( MA, ht, len, seed, Min, Max )          VSIcu_random( (MA)[0], (ht)*(len), seed, Min, Max )
#define MSIcu_outerprod( MA, X, Y, ht, len )        MSIcuouterprod( (MA)[0], X, Y, ht, len )
                       /* sizX=ht, sizY=len */
#define MSIcu_Row_equ0( MA, ht, len, iRow )    MSIcuRow_equ0( (MA)[0], ht, len, iRow )
#define MSIcu_Col_equ0( MA, ht, len, iCol )    MSIcuCol_equ0( (MA)[0], ht, len, iCol )
#define MSIcu_Dia_equ0( MA, len )              MSIcuDia_equ0( (MA)[0], len )
#define MSIcu_Row_equC( MA, ht, len, iRow, C ) MSIcuRow_equC( (MA)[0], ht, len, iRow, C )
#define MSIcu_Col_equC( MA, ht, len, iCol, C ) MSIcuCol_equC( (MA)[0], ht, len, iCol, C )
#define MSIcu_Dia_equC( MA, len, C )           MSIcuDia_equC( (MA)[0], len, C )

#define MSIcu_Row_equV( MA, ht, len, iRow, X ) MSIcuRow_equV( (MA)[0], ht, len, iRow, X )
#define MSIcu_Col_equV( MA, ht, len, iCol, X ) MSIcuCol_equV( (MA)[0], ht, len, iCol, X )
#define MSIcu_Dia_equV( MA, len, X )           MSIcuDia_equV( (MA)[0], len, X )

#define MSIcu_Trd_equM( MA, MTrd, len )        MSIcuTrd_equM( (MA)[0], (MTrd)[0], len )
#define MSIcu_Trd_extract( MTrd, MA, len )     MSIcuTrd_extract( (MTrd)[0], (MA)[0], len )

#define MSIcu_equM( MB, MA, ht, len )          VSIcu_equV( (MB)[0], (MA)[0], (ht)*(len) )
#define MSIcu_equMhost( MB, MA, ht, len )      VSIcu_equVhost( (MB)[0], MA[0], (ht)*(len) )
#define MSIcu_neg( MB, MA, ht, len )           VSIcu_neg( (MB)[0], (MA)[0], (ht)*(len) )

#define MSIcu_UequL( MA, len ) MSIcuUequL( (MA)[0], len )
#define MSIcu_LequU( MA, len ) MSIcuLequU( (MA)[0], len )
     /* copy lower-diagonal elements into upper-diagonal
       (or vice versa) by index-reflection, so as to get a symmetric matrix    */

            /* data-type conversions:  */
#define Mcu_SItoUS( MUS, MSI, ht, len ) Vcu_SItoUS( (MUS)[0], (MSI)[0], (ht)*(len) )
#define Mcu_UStoSI( MSI, MUS, ht, len ) Vcu_UStoSI( (MSI)[0], (MUS)[0], (ht)*(len) )
#define Mcu_SItoBI( MBI, MSI, ht, len ) Vcu_SItoBI( (MBI)[0], (MSI)[0], (ht)*(len) )
#define Mcu_SItoI(  MI,  MSI, ht, len ) Vcu_SItoI(  (MI)[0],  (MSI)[0], (ht)*(len) )
#define Mcu_SItoLI( MLI, MSI, ht, len ) Vcu_SItoLI( (MLI)[0], (MSI)[0], (ht)*(len) )
#define Mcu_SItoQI( MQI, MSI, ht, len ) Vcu_SItoQI( (MQI)[0], (MSI)[0], (ht)*(len) )
#define Mcu_BItoSI( MSI, MBI, ht, len ) Vcu_BItoSI( (MSI)[0], (MBI)[0], (ht)*(len) )
#define Mcu_ItoSI(  MSI, MI,  ht, len ) Vcu_ItoSI(  (MSI)[0], (MI)[0],  (ht)*(len) )
#define Mcu_LItoSI( MSI, MLI, ht, len ) Vcu_LItoSI( (MSI)[0], (MLI)[0], (ht)*(len) )
#define Mcu_QItoSI( MSI, MQI, ht, len ) Vcu_QItoSI( (MSI)[0], (MQI)[0], (ht)*(len) )
#define Mcu_SItoF(  MF,  MSI, ht, len ) Vcu_SItoF(  (MF)[0],  (MSI)[0], (ht)*(len) )
#define Mcu_SItoD(  MD,  MSI, ht, len ) Vcu_SItoD(  (MD)[0],  (MSI)[0], (ht)*(len) )


/********  Extracting a submatrix and copying a submatrix back  *********/

#define MSIcu_submatrix( MSub, subHt, subLen, MSrce, srceHt, srceLen, \
                      firstRowInCol, sampInCol, firstColInRow, sampInRow ) \
               MSIcusubmatrix(  (MSub)[0], subHt, subLen, \
                             (MSrce)[0], srceHt, srceLen, \
                             firstRowInCol, sampInCol, firstColInRow, sampInRow )

#define MSIcu_submatrix_equM( MDest, destHt, destLen, \
                           firstRowInCol, sampInCol, firstColInRow, sampInRow, \
                           MSrce, srceHt, srceLen ) \
               MSIcusubmatrix_equM(  (MDest)[0], destHt, destLen, \
                             firstRowInCol, sampInCol, firstColInRow, sampInRow, \
                             (MSrce)[0], srceHt, srceLen )

#define MSIcu_equMblock( MSub, subHt, subLen, MSrce, srceHt, srceLen, \
                      firstRowInCol, firstColInRow ) \
               MSIcuequMblock(  (MSub)[0], subHt, subLen, \
                             (MSrce)[0], srceHt, srceLen, \
                             firstRowInCol, firstColInRow )

#define MSIcu_block_equM( MDest, destHt, destLen, \
                       firstRowInCol, firstColInRow, \
                       MSrce, srceHt, srceLen ) \
               MSIcublock_equM( (MDest)[0], destHt, destLen, \
                             firstRowInCol, firstColInRow, \
                             (MSrce)[0], srceHt, srceLen )

#define MSIcu_equMblockT( MSub, subHt, subLen, MSrce, srceHt, srceLen, \
                      firstRowInCol, firstColInRow ) \
               MSIcuequMblockT(  (MSub)[0], subHt, subLen, \
                             (MSrce)[0], srceHt, srceLen, \
                             firstRowInCol, firstColInRow )

#define MSIcu_block_equMT( MDest, destHt, destLen, \
                       firstRowInCol, firstColInRow, \
                       MSrce, srceHt, srceLen ) \
               MSIcublock_equMT( (MDest)[0], destHt, destLen, \
                             firstRowInCol, firstColInRow, \
                             (MSrce)[0], srceHt, srceLen )

/*****   Extracting a single row or a single column or the diagonal  ******
 *       and storing it into a vector                                     */

#define MSIcu_Row_extract( Y, MA, ht, len, iRow ) MSIcuRow_extract( Y, (MA)[0], ht, len, iRow )
#define MSIcu_Col_extract( Y, MA, ht, len, iCol ) MSIcuCol_extract( Y, (MA)[0], ht, len, iCol )
#define MSIcu_Dia_extract( Y, MA, len )           MSIcuDia_extract( Y, (MA)[0], len )

/**************  Deleting or inserting a row or a column   ***************/

#define MSIcu_Row_delete( MB, MA, htA, lenA, iRow )    MSIcuRow_delete( (MB)[0], (MA)[0], htA, lenA, iRow )
#define MSIcu_Col_delete( MB, MA, htA, lenA, iCol )    MSIcuCol_delete( (MB)[0], (MA)[0], htA, lenA, iCol )
#define MSIcu_Row_insert( MB, MA, htB, lenB, iRow, X ) MSIcuRow_insert( (MB)[0], (MA)[0], htB, lenB, iRow, X )
#define MSIcu_Col_insert( MB, MA, htB, lenB, iCol, X ) MSIcuCol_insert( (MB)[0], (MA)[0], htB, lenB, iCol, X )


/*****************    Basic arithmetic operations *********************
                      performed on one single row,
                      or one single column of any matrix,
                      or on the diagonal of a square matrix

    Note: In contrast to the analogous VectorLib functions, the operations
    are performed in-place, i.e. the input matrix itself is changed  */

#define MSIcu_Row_neg( MA, ht, len, iRow ) MSIcuRow_neg( (MA)[0], ht, len, iRow )
#define MSIcu_Col_neg( MA, ht, len, iCol ) MSIcuCol_neg( (MA)[0], ht, len, iCol )

/******  One-dimensional vector operations **********************
         performed along all rows or all columns simultaneously,
         or along the diagonal of a square matrix                */

#define MSIcu_Rows_max( Y, MA, ht, len )        MSIcuRows_max( Y, (MA)[0], ht, len )
#define MSIcu_Cols_max( Y, MA, ht, len )        MSIcuCols_max( Y, (MA)[0], ht, len )
#define MSIcu_Dia_max(  MA, len )               MSIcuDia_max(  (MA)[0], len )
#define MSIcu_Rows_min( Y, MA, ht, len )        MSIcuRows_min( Y, (MA)[0], ht, len )
#define MSIcu_Cols_min( Y, MA, ht, len )        MSIcuCols_min( Y, (MA)[0], ht, len )
#define MSIcu_Dia_min(  MA, len )               MSIcuDia_min(  (MA)[0], len )

#define MSIcu_Rows_rotate( MA, ht, len, pos)           MSIcuRows_rotate( (MA)[0], ht, len, pos )
#define MSIcu_Cols_rotate( MA, ht, len, pos)           MSIcuCols_rotate( (MA)[0], ht, len, pos )
#define MSIcu_Rows_rotate_buf( MA, ht, len, pos, MBuf) MSIcuRows_rotate_buf( (MA)[0], ht, len, pos, (MBuf)[0] )
#define MSIcu_Cols_rotate_buf( MA, ht, len, pos, MBuf) MSIcuCols_rotate_buf( (MA)[0], ht, len, pos, (MBuf)[0] )
#define MSIcu_Rows_reflect( MA, ht, len )              MSIcuRows_reflect( (MA)[0], ht, len )
#define MSIcu_Cols_reflect( MA, ht, len )              MSIcuCols_reflect( (MA)[0], ht, len )
#define MSIcu_Rows_rev( MA, ht, len)                   MSIcuRows_rev( (MA)[0], ht, len )
#define MSIcu_Cols_rev( MA, ht, len)                   MSIcuCols_rev( (MA)[0], ht, len )
#define MSIcu_Rows_distribution( MAbund, Limits, nBins, MX, ht, len, mode ) MSIcuRows_distribution( MAbund[0], Limits, nBins, MX[0], ht, len, mode )
#define MSIcu_Cols_distribution( MAbund, Limits, nBins, MX, ht, len, mode ) MSIcuCols_distribution( MAbund[0], Limits, nBins, MX[0], ht, len, mode )

/********  Operations involving two rows or two colums of one matrix  *****/

#define MSIcu_Rows_exchange( MA, ht, len, row1, row2 ) \
                             MSIcuRows_exchange( (MA)[0], ht, len, row1, row2 )
#define MSIcu_Cols_exchange( MA, ht, len, col1, col2 ) \
                             MSIcuCols_exchange( (MA)[0], ht, len, col1, col2 )

/*************** Transposing and rotating a matrix **********************/

#define MSIcu_transpose( MTr, MA, htTr, lenTr )    MSIcutranspose( (MTr)[0], (MA)[0], htTr, lenTr )
       /*  dimensions htTr, lenTr are those of the transposed matrix, not of the original!   */
#define MSIcu_rotate90( MRot, MA, htRot, lenRot )  MSIcurotate90( (MRot)[0], (MA)[0], htRot, lenRot )
#define MSIcu_rotate180( MRot, MA, htRot, lenRot ) VSIcu_rev( (MRot)[0], (MA)[0], (htRot)*(lenRot) )
#define MSIcu_rotate270( MRot, MA, htRot, lenRot ) MSIcurotate270( (MRot)[0], (MA)[0], htRot, lenRot )


/*************************************************************************
 * MSIcu functions (without underbar in the prefix): 	
    (working on matrices in host memory, input type 
	siPMatrix = siVector = pointer to matrix element[0][0], 
	scalar parameters on host and passed by value)
*
 *************************************************************************/

#define MSIcuequ0( MA, ht, len )       VSIcu_equ0( MA, (ht)*(len) )
void   __vf OVCUAPI  MSIcuequ1( siPMatrix MA, ui len );  /* identity matrix */
void   __vf OVCUAPI  MSIcuequm1( siPMatrix MA, ui len );  /* neg. identity matrix */
void   __vf OVCUAPI  MSIcuouterprod( siPMatrix MA, siVector X,  siVector Y, ui ht, ui len );

void   __vf OVCUAPI  MSIcuRow_equ0( siPMatrix MA, ui ht, ui len, ui iRow );
void   __vf OVCUAPI  MSIcuCol_equ0( siPMatrix MA, ui ht, ui len, ui iCol );
void   __vf OVCUAPI  MSIcuDia_equ0( siPMatrix MA, ui len );

void   __vf OVCUAPI  MSIcuRow_equC( siPMatrix MA, ui ht, ui len, ui iRow, short C );
void   __vf OVCUAPI  MSIcuCol_equC( siPMatrix MA, ui ht, ui len, ui iCol, short C );
void   __vf OVCUAPI  MSIcuDia_equC( siPMatrix MA, ui len, short C );

void   __vf OVCUAPI  MSIcuRow_equV( siPMatrix MA, ui ht, ui len, ui iRow, siVector X );
void   __vf OVCUAPI  MSIcuCol_equV( siPMatrix MA, ui ht, ui len, ui iCol, siVector X );
void   __vf OVCUAPI  MSIcuDia_equV( siPMatrix MA, ui len, siVector X );

void   __vf OVCUAPI  MSIcuTrd_equM( siPMatrix MA, siPMatrix MTrd, ui len );
void   __vf OVCUAPI  MSIcuTrd_extract( siPMatrix MTrd, siPMatrix MA, ui len );

#define MSIcuequM( MB, MA, ht, len )      VSIcu_equV( MB, MA, (ht)*(len) )
#define MSIcuneg( MB, MA, ht, len )       VSIcu_neg( MB, MA, (ht)*(len) )
void   __vf OVCUAPI  MSIcuUequL( siPMatrix MA, ui len );
void   __vf OVCUAPI  MSIcuLequU( siPMatrix MA, ui len );

            /* data-type conversions:  */
#define McuSItoUS( MUS, MSI, ht, len ) Vcu_SItoUS( MUS, MSI, (ht)*(len) )
#define McuUStoSI( MSI, MUS, ht, len ) Vcu_UStoSI( MSI, MUS, (ht)*(len) )
#define McuSItoBI( MBI, MSI, ht, len ) Vcu_SItoBI( MBI, MSI, (ht)*(len) )
#define McuSItoI(  MI,  MSI, ht, len ) Vcu_SItoI(  MI,  MSI, (ht)*(len) )
#define McuSItoLI( MLI, MSI, ht, len ) Vcu_SItoLI( MLI, MSI, (ht)*(len) )
#define McuSItoQI( MQI, MSI, ht, len ) Vcu_SItoQI( MQI, MSI, (ht)*(len) )
#define McuBItoSI( MSI, MBI, ht, len ) Vcu_BItoSI( MSI, MBI, (ht)*(len) )
#define McuItoSI(  MSI, MI,  ht, len ) Vcu_ItoSI(  MSI, MI,   (ht)*(len) )
#define McuLItoSI( MSI, MLI, ht, len ) Vcu_LItoSI( MSI, MLI, (ht)*(len) )
#define McuQItoSI( MSI, MQI, ht, len ) Vcu_QItoSI( MSI, MQI, (ht)*(len) )
#define McuSItoF(  MF,  MSI, ht, len ) Vcu_SItoF(  MF,  MSI, (ht)*(len) )
#define McuSItoD(  MD,  MSI, ht, len ) Vcu_SItoD(  MD,  MSI, (ht)*(len) )

/********  Extracting a submatrix and copying a submatrix back  *********/

void  __vf OVCUAPI  MSIcusubmatrix( siPMatrix MSub, ui subHt,  ui subLen,
                          siPMatrix MSrce, ui srceHt,  ui srceLen,
                          ui firstRowInCol,  ui sampInCol,
                          ui firstColInRow,  ui sampInRow );

void  __vf OVCUAPI  MSIcusubmatrix_equM( siPMatrix MDest, ui destHt, ui destLen,
                               ui firstRowInCol,  ui sampInCol,
                               ui firstColInRow,  ui sampInRow,
                               siPMatrix MSrce, ui srceHt, ui srceLen );

void  __vf OVCUAPI  MSIcuequMblock(  siPMatrix MSub, ui subHt, ui subLen,
                          siPMatrix MSrce, ui srceHt,  ui srceLen,
                          ui firstRowInCol,  ui firstColInRow );

void  __vf OVCUAPI  MSIcublock_equM( siPMatrix MDest, ui destHt, ui destLen,
                          ui firstRowInCol,  ui firstColInRow,
                          siPMatrix MSrce, ui srceHt, ui srceLen );

void  __vf OVCUAPI  MSIcuequMblockT( siPMatrix MSub, ui subHt, ui subLen,
                          siPMatrix MSrce, ui srceHt, ui srceLen,
                          ui firstRowInCol,  ui firstColInRow );

void  __vf OVCUAPI  MSIcublock_equMT( siPMatrix MDest, ui destHt, ui destLen,
                          ui firstRowInCol,  ui firstColInRow,
                          siPMatrix MSrce, ui srceHt, ui srceLen );


/*****   Extracting a single row or a single column or the diagonal  *****
 *       and storing it into a vector                                    */

void __vf OVCUAPI  MSIcuRow_extract( siVector Y, siPMatrix MA, ui ht, ui len, ui iRow );
void __vf OVCUAPI  MSIcuCol_extract( siVector Y, siPMatrix MA, ui ht, ui len, ui iCol );
void __vf OVCUAPI  MSIcuDia_extract( siVector Y, siPMatrix MA, ui len );

/**********  Deleting or inserting a row or a column *****************/

void __vf OVCUAPI  MSIcuRow_delete( siPMatrix MB, siPMatrix MA, ui htA, ui lenA, ui iRow );
void __vf OVCUAPI  MSIcuCol_delete( siPMatrix MB, siPMatrix MA, ui htA, ui lenA, ui iCol );
void __vf OVCUAPI  MSIcuRow_insert( siPMatrix MB, siPMatrix MA, ui htB, ui lenB, ui iRow, siVector X );
void __vf OVCUAPI  MSIcuCol_insert( siPMatrix MB, siPMatrix MA, ui htB, ui lenB, ui iCol, siVector X );


/******  One-dimensional vector operations **********************
         performed along all rows or all columns simultaneously,
         or along the diagonal of a square matrix                */

void   __vf OVCUAPI  MSIcuRows_max( siVector Y, siPMatrix MA, ui ht, ui len );
void   __vf OVCUAPI  MSIcuCols_max( siVector Y, siPMatrix MA, ui ht, ui len );
short  __vf OVCUAPI  MSIcuDia_max(  siPMatrix MA, ui len );
void   __vf OVCUAPI  MSIcuRows_min( siVector Y, siPMatrix MA, ui ht, ui len );
void   __vf OVCUAPI  MSIcuCols_min( siVector Y, siPMatrix MA, ui ht, ui len );
short  __vf OVCUAPI  MSIcuDia_min(  siPMatrix MA, ui len );

void  __vf OVCUAPI  MSIcuRows_rotate( siPMatrix MA, ui ht, ui len, ssize_t pos );
void  __vf OVCUAPI  MSIcuCols_rotate( siPMatrix MA, ui ht, ui len, ssize_t pos );
void  __vf OVCUAPI  MSIcuRows_rotate_buf( siPMatrix MA, ui ht, ui len, ssize_t pos, siPMatrix MBuf );
void  __vf OVCUAPI  MSIcuCols_rotate_buf( siPMatrix MA, ui ht, ui len, ssize_t pos, siPMatrix MBuf );
void  __vf OVCUAPI  MSIcuRows_reflect( siPMatrix MA, ui ht, ui len );
void  __vf OVCUAPI  MSIcuCols_reflect( siPMatrix MA, ui ht, ui len );
void  __vf OVCUAPI  MSIcuRows_rev( siPMatrix MA, ui ht, ui len );
void  __vf OVCUAPI  MSIcuCols_rev( siPMatrix MA, ui ht, ui len );
void  __vf OVCUAPI  MSIcuRows_distribution( uiPMatrix MAbund, siVector Limits, ui nBins, siPMatrix MX, ui ht, ui len, int mode );
void  __vf OVCUAPI  MSIcuCols_distribution( uiPMatrix MAbund, siVector Limits, ui nBins, siPMatrix MX, ui ht, ui len, int mode );

/********  Operations involving two rows or two colums of one matrix  *****/

void   __vf OVCUAPI  MSIcuRows_exchange( siPMatrix MA, ui ht, ui len, ui i1, ui i2 );
void   __vf OVCUAPI  MSIcuCols_exchange( siPMatrix MA, ui ht, ui len, ui i1, ui i2 );


/***************  Transposing and rotating a matrix **********************/

void  __vf OVCUAPI  MSIcutranspose( siPMatrix MTr, siPMatrix MA,  ui htTr, ui lenTr );
void  __vf OVCUAPI  MSIcurotate90(  siPMatrix MRot, siPMatrix MA, ui htRot, ui lenRot );
#define     MSIcurotate180( MRot, MA, htRot, lenRot )  VSIcu_rev( MRot, MA, (htRot)*(lenRot) )
void  __vf OVCUAPI  MSIcurotate270( siPMatrix MRot, siPMatrix MA, ui htRot, ui lenRot );

#ifdef __cplusplus
} // end of extern "C"
#endif
#endif  /*  __MSISTD_H  */
