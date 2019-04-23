/*  cudaMIstd.h

  matrix management functions:
  manipulations on matrices of data type "int" (generic integer)

  This file declares the functions with the name variants 
	cudaMI_func	(working on matrices in device memory, input type iMatrix, scalar parameters reside on host and are passed by value)
	cusdMI_func	(as cudaMI_func except scalar parameters reside on device and are passed by address)
	cudaMIfunc		(as cudaMI_func, but input type iPMatrix = iVector = pointer to matrix element[0][0])
	cusdMIfunc		(as cusdMI_func, but input type iPMatrix = iVector = pointer to matrix element[0][0])
	MIcu_func		(working on matrices in host memory, input type iMatrix, scalar parameters on host and passed by value)
	MIcufunc		(as MIcu_func, but input type iPMatrix = iVector = pointer to matrix element[0][0])
  where func is the respective function.

   Copyright (c) 1996-2017 by OptiCode - Dr. Martin Sander Software Dev.
  All Rights Reserved.

*/

#if !defined( __CUDAMISTD_H )
#define __CUDAMISTD_H
#if !defined( __CUDAMATLIB_H )
#include <cudaMatLib.h>
#endif
#if !defined( __CUDAVISTD_H )
#include <cudaVIstd.h>
#endif
#if !defined( __CUDAVIMATH_H )
#include <cudaVImath.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif

/**** Generation of matrices on device memory and on pinned host memory *******************/

iMatrix  __vf cudaMI_matrix( ui ht, ui len );   /* allocates a vector on device memory */
iMatrix  __vf cudaMI_matrix0( ui ht, ui len );
 /* The following functions allocate device-accessible, "pinned" memory on the host.
	This memory is mapped onto the device memory space. The resulting device address is returned.
	The matrix can be accessed either by its host address "hostPtr" e.g., MI_equ1( hostPtr, ht, len );
	or by its device address , e.g., cudaMI_equ1( devicePtr, ht, len );                             */
iMatrix  __vf cudaMI_pinnedMatrix(  iMatrix *hostPtr, ui ht, ui len ); 
iMatrix  __vf cudaMI_pinnedMatrix0( iMatrix *hostPtr, ui ht, ui len );

/*************************************************************************
 * Declarations of the functions written without underbar in the prefix: *
 *	cudaMIfunc  (input type 
                   iPMatrix = iVector = pointer to matrix element[0][0])
 *	cusdMIfunc  (input type 
                   iPMatrix = iVector = pointer to matrix element[0][0])
 *************************************************************************/

void  __vcuf OVCUAPI  cudaMIsetElement( iPMatrix X, ui ht, ui len, ui m, ui n, int C );
void  __vcuf OVCUAPI  cusdMIsetElement( iPMatrix X, ui ht, ui len, ui m, ui n, int *d_C );
void  __vcuf OVCUAPI  cudaMIgetElement( int *h_y, iPMatrix X, ui ht, ui len, ui m, ui n );
void  __vcuf OVCUAPI  cusdMIgetElement( int *d_y, iPMatrix X, ui ht, ui len, ui m, ui n );
int  __vcuf OVCUAPI  cudaMIelement( iPMatrix X, ui ht, ui len, ui m, ui n );
int * __vcuf OVCUAPI cudaMIPelement( iPMatrix X, ui ht, ui len, ui m, ui n );

#define cudaMIequ0( MA, ht, len )            cudaVI_equ0( MA, (ht)*(len) )
overror_t   __vcuf OVCUAPI  cudaMIequ1( iPMatrix MA, ui len );  /* identity matrix */
overror_t   __vcuf OVCUAPI  cudaMIequm1( iPMatrix MA, ui len );  /* neg. identity matrix */
overror_t   __vcuf OVCUAPI  cudaMIouterprod( iPMatrix MA, iVector X,  iVector Y, ui ht, ui len );

overror_t   __vcuf OVCUAPI  cudaMIRow_equ0( iPMatrix MA, ui ht, ui len, ui iRow );
overror_t   __vcuf OVCUAPI  cudaMICol_equ0( iPMatrix MA, ui ht, ui len, ui iCol );
overror_t   __vcuf OVCUAPI  cudaMIDia_equ0( iPMatrix MA, ui len );

overror_t   __vcuf OVCUAPI  cudaMIRow_equC( iPMatrix MA, ui ht, ui len, ui iRow, int C );
overror_t   __vcuf OVCUAPI  cudaMICol_equC( iPMatrix MA, ui ht, ui len, ui iCol, int C );
overror_t   __vcuf OVCUAPI  cudaMIDia_equC( iPMatrix MA, ui len, int C );
overror_t   __vcuf OVCUAPI  cusdMIRow_equC( iPMatrix MA, ui ht, ui len, ui iRow, int *d_C );
overror_t   __vcuf OVCUAPI  cusdMICol_equC( iPMatrix MA, ui ht, ui len, ui iCol, int *d_C );
overror_t   __vcuf OVCUAPI  cusdMIDia_equC( iPMatrix MA, ui len, int *d_C );

overror_t   __vcuf OVCUAPI  cudaMIRow_equV( iPMatrix MA, ui ht, ui len, ui iRow, iVector X );
overror_t   __vcuf OVCUAPI  cudaMICol_equV( iPMatrix MA, ui ht, ui len, ui iCol, iVector X );
overror_t   __vcuf OVCUAPI  cudaMIDia_equV( iPMatrix MA, ui len, iVector X );

overror_t   __vcuf OVCUAPI  cudaMITrd_equM( iPMatrix MA, iPMatrix MTrd, ui len );
overror_t   __vcuf OVCUAPI  cudaMITrd_extract( iPMatrix MTrd, iPMatrix MA, ui len );

#define cudaMIequM( MB, MA, ht, len )         cudaVI_equV( MB, MA, (ht)*(len) )
#define cudaMIequMhost( d_MB, h_MA, ht, len ) cudaVI_equVhost( d_MB, h_MA, (ht)*(len) )
#define MIequMdevice( h_MB, d_MA, ht, len )   VI_equVdevice( h_MB, d_MA, (ht)*(len) )
#define cudaMIneg( MB, MA, ht, len )          cudaVI_neg( MB, MA, (ht)*(len) )
overror_t   __vcuf OVCUAPI  cudaMIUequL( iPMatrix MA, ui len );
overror_t   __vcuf OVCUAPI  cudaMILequU( iPMatrix MA, ui len );

            /* data-type conversions:  */
#define cudaMItoU( MU, MI, ht, len ) cudaV_ItoU( (MU), (MI), (ht)*(len) )
#define cudaMUtoI( MI, MU, ht, len ) cudaV_UtoI( (MI), (MU), (ht)*(len) )
#define cudaMItoBI( MBI, MI, ht, len ) cudaV_ItoBI( (MBI), (MI), (ht)*(len) )
#define cudaMItoSI( MSI, MI, ht, len ) cudaV_ItoSI( (MSI), (MI), (ht)*(len) )
#define cudaMItoLI( MLI, MI, ht, len ) cudaV_ItoLI( (MLI), (MI), (ht)*(len) )
#define cudaMItoQI( MQI, MI, ht, len ) cudaV_ItoQI( (MQI), (MI), (ht)*(len) )
#define cudaMBItoI( MI, MBI, ht, len ) cudaV_BItoI( (MI), (MBI), (ht)*(len) )
#define cudaMSItoI( MI, MSI, ht, len ) cudaV_SItoI( (MI), (MSI), (ht)*(len) )
#define cudaMLItoI( MI, MLI, ht, len ) cudaV_LItoI( (MI), (MLI), (ht)*(len) )
#define cudaMQItoI( MI, MQI, ht, len ) cudaV_QItoI( (MI), (MQI), (ht)*(len) )
#define cudaMItoF(  MF,  MI, ht, len ) cudaV_ItoF(  (MF),  (MI), (ht)*(len) )
#define cudaMItoD(  MD,  MI, ht, len ) cudaV_ItoD(  (MD),  (MI), (ht)*(len) )

/********  Extracting a submatrix and copying a submatrix back  *********/

overror_t  __vcuf OVCUAPI  cudaMIsubmatrix( iPMatrix MSub, ui subHt,  ui subLen,
                          iPMatrix MSrce, ui srceHt,  ui srceLen,
                          ui firstRowInCol,  ui sampInCol,
                          ui firstColInRow,  ui sampInRow );

overror_t  __vcuf OVCUAPI  cudaMIsubmatrix_equM( iPMatrix MDest, ui destHt, ui destLen,
                               ui firstRowInCol,  ui sampInCol,
                               ui firstColInRow,  ui sampInRow,
                               iPMatrix MSrce,  ui srceHt, ui srceLen );

overror_t  __vcuf OVCUAPI  cudaMIequMblock(  iPMatrix MSub,  ui subHt,  ui subLen,
                          iPMatrix MSrce, ui srceHt,  ui srceLen,
                          ui firstRowInCol,  ui firstColInRow );

overror_t  __vcuf OVCUAPI  cudaMIblock_equM( iPMatrix MDest,  ui destHt,  ui destLen,
                          ui firstRowInCol,  ui firstColInRow,
                          iPMatrix MSrce,  ui srceHt, ui srceLen );

overror_t  __vcuf OVCUAPI  cudaMIequMblockT( iPMatrix MSub,  ui subHt, ui subLen,
                          iPMatrix MSrce,  ui srceHt,  ui srceLen,
                          ui firstRowInCol,  ui firstColInRow );

overror_t  __vcuf OVCUAPI  cudaMIblock_equMT( iPMatrix MDest,  ui destHt,  ui destLen,
                          ui firstRowInCol,  ui firstColInRow,
                          iPMatrix MSrce,   ui srceHt,  ui srceLen );


/*****   Extracting a single row or a single column or the diagonal  *****
 *       and storing it into a vector                                    */

overror_t __vcuf OVCUAPI  cudaMIRow_extract( iVector Y, iPMatrix MA, ui ht, ui len, ui iRow );
overror_t __vcuf OVCUAPI  cudaMICol_extract( iVector Y, iPMatrix MA, ui ht, ui len, ui iCol );
overror_t __vcuf OVCUAPI  cudaMIDia_extract( iVector Y, iPMatrix MA, ui len );


/**********  Deleting or inserting a row or a column *****************/

overror_t __vcuf OVCUAPI  cudaMIRow_delete( iPMatrix MB, iPMatrix MA, ui htA, ui lenA, ui iRow );
overror_t __vcuf OVCUAPI  cudaMICol_delete( iPMatrix MB, iPMatrix MA, ui htA, ui lenA, ui iCol );
overror_t __vcuf OVCUAPI  cudaMIRow_insert( iPMatrix MB, iPMatrix MA, ui htB, ui lenB, ui iRow, iVector X );
overror_t __vcuf OVCUAPI  cudaMICol_insert( iPMatrix MB, iPMatrix MA, ui htB, ui lenB, ui iCol, iVector X );


/******  One-dimensional vector operations **********************
         performed aint all rows or all columns simultaneously,
         or aint the diagonal of a square matrix                */

overror_t  __vcuf OVCUAPI  cudaMIRows_max( iVector Y, iPMatrix MA, ui ht, ui len );
overror_t  __vcuf OVCUAPI  cudaMICols_max( iVector Y, iPMatrix MA, ui ht, ui len );
overror_t  __vcuf OVCUAPI  cudaMIDia_max(  int *h_RetVal, iPMatrix MA, ui len );
overror_t  __vcuf OVCUAPI  cusdMIDia_max(  int *d_RetVal, iPMatrix MA, ui len );
overror_t  __vcuf OVCUAPI  cudaMIRows_min( iVector Y, iPMatrix MA, ui ht, ui len );
overror_t  __vcuf OVCUAPI  cudaMICols_min( iVector Y, iPMatrix MA, ui ht, ui len );
overror_t  __vcuf OVCUAPI  cudaMIDia_min(  int *h_RetVal, iPMatrix MA, ui len );
overror_t  __vcuf OVCUAPI  cusdMIDia_min(  int *d_RetVal, iPMatrix MA, ui len );

overror_t  __vcuf OVCUAPI  cudaMIRows_rotate( iPMatrix MA, ui ht, ui len, ssize_t pos );
overror_t  __vcuf OVCUAPI  cudaMICols_rotate( iPMatrix MA, ui ht, ui len, ssize_t pos );
overror_t  __vcuf OVCUAPI  cudaMIRows_rotate_buf( iPMatrix MA, ui ht, ui len, ssize_t pos, iPMatrix MBuf );
overror_t  __vcuf OVCUAPI  cudaMICols_rotate_buf( iPMatrix MA, ui ht, ui len, ssize_t pos, iPMatrix MBuf );
overror_t  __vcuf OVCUAPI  cudaMIRows_reflect( iPMatrix MA, ui ht, ui len );
overror_t  __vcuf OVCUAPI  cudaMICols_reflect( iPMatrix MA, ui ht, ui len );
overror_t  __vcuf OVCUAPI  cudaMIRows_rev( iPMatrix MA, ui ht, ui len );
overror_t  __vcuf OVCUAPI  cudaMICols_rev( iPMatrix MA, ui ht, ui len );
overror_t  __vcuf OVCUAPI  cudaMIRows_distribution( uiPMatrix MAbund, iVector Limits, ui nBins, iPMatrix MX, ui ht, ui len, int mode );
overror_t  __vcuf OVCUAPI  cudaMICols_distribution( uiPMatrix MAbund, iVector Limits, ui nBins, iPMatrix MX, ui ht, ui len, int mode );

/********  Operations involving two rows or two colums of one matrix  *****/

overror_t   __vcuf OVCUAPI  cudaMIRows_exchange( iPMatrix MA, ui ht, ui len, ui i1, ui i2 );
overror_t   __vcuf OVCUAPI  cudaMICols_exchange( iPMatrix MA, ui ht, ui len, ui i1, ui i2 );

/*****************  Transposing and rotating a matrix **********************/

overror_t  __vcuf OVCUAPI  cudaMItranspose( iPMatrix MTr, iPMatrix MA, ui htTr, ui lenTr );
#define     cudaMIrotate180( MRot, MA, htRot, lenRot )  cudaVI_rev( MRot, MA, (htRot)*(lenRot) )
overror_t  __vcuf OVCUAPI  cudaMIrotate90(  iPMatrix MRot, iPMatrix MA, ui htRot, ui lenRot );
overror_t  __vcuf OVCUAPI  cudaMIrotate270( iPMatrix MRot, iPMatrix MA, ui htRot, ui lenRot );
overror_t  __vcuf OVCUAPI  cudaMItranspose_buf( iPMatrix MTr, iPMatrix MA, ui htTr, ui lenTr, iPMatrix MBuf );

/**************************  Input and Output  **************************
	The input/output functions involve memory transfers from device
	to host memory or vice versa. The generic cudaMI_input/output functions
	allocate their own host buffers, whereas the cudaMI_xxx_buf functions
	take a user-supplied buffer vector h_Wk (size must be >= ht*len )
	and are much more efficient.                                       */

#define cudaMIprint( MA, ht, len )  cudaMIfprint( stdout, MA, ht, len, 80 )
overror_t __vf cudaMIfprint( FILE *stream, iPMatrix MA, ui ht, ui len, unsigned linewidth );
overror_t __vf cudaMIcprint( iPMatrix MA, ui ht, ui len );
#define cudaMIprint_buf( MA, ht, len, h_Wk )  cudaMIfprint_buf( stdout, MA, ht, len, 80, h_Wk )
overror_t __vf cudaMIfprint_buf( FILE *stream, iPMatrix MA, ui ht, ui len, unsigned linewidth, iVector h_Wk );
overror_t __vf cudaMIcprint_buf( iPMatrix MA, ui ht, ui len, iVector h_Wk );
overror_t __vf cudaMIwrite( FILE *stream, iPMatrix X, ui ht, ui len  );
overror_t __vf cudaMIread( iPMatrix X, ui ht, ui len, FILE *stream );
overror_t __vf cudaMIwrite_buf( FILE *stream, iPMatrix X, ui ht, ui len, iVector h_Wk );
overror_t __vf cudaMIread_buf( iPMatrix X, ui ht, ui len, FILE *stream, iVector h_Wk );
#define cudaMIstore( str, MA, ht, len ) cudaVI_store( str, MA, (len)*(ht) )
#define cudaMIrecall( MA, ht, len, str) cudaVI_recall( MA, (len)*(ht), str)
#define cudaMIstore_buf( str, MA, ht, len, h_Wk ) cudaVI_store( str, MA, (len)*(ht), h_Wk )
#define cudaMIrecall_buf( MA, ht, len, str, h_Wk) cudaVI_recall( MA, (len)*(ht), str, h_Wk)



/***************************************************************************
    cudaMI_func	(working on matrices in device memory, input type iMatrix, 
	             scalar parameters reside on host and are passed by value)
    cusdMI_func	(as cudaMI_func except scalar parameters reside on device 
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

inline void    cudaMI_setElement( iMatrix MA, ui ht, ui len, ui m, ui n, int C )
	{	cudaMIsetElement( (iPMatrix)(MA), ht, len, m, n, C );}
inline void    cusdMI_setElement( iMatrix MA, ui ht, ui len, ui m, ui n, int *d_C )
	{	cusdMIsetElement( (iPMatrix)(MA), ht, len, m, n, d_C );}
inline void    cudaMI_getElement( int *y, iMatrix MA, ui ht, ui len, ui m, ui n )
	{	cudaMIgetElement( y, (iPMatrix)(MA), ht, len, m, n );}
inline void    cusdMI_getElement( int *d_y, iMatrix MA, ui ht, ui len, ui m, ui n )
	{	cusdMIgetElement( d_y, (iPMatrix)(MA), ht, len, m, n );}
inline int * cudaMI_Pelement( iMatrix MA, ui ht, ui len, ui m, ui n )
	{	return cudaMIPelement( (iPMatrix)(MA), ht, len, m, n );}
inline int   cudaMI_element( iMatrix MA, ui ht, ui len, ui m, ui n )
{	return cudaMIelement( (iPMatrix)(MA), ht, len, m, n );}

inline overror_t  cudaMI_equ0( iMatrix MA, ui ht, ui len )
	{	return cudaVI_equ0( (iPMatrix)MA, (ht)*(len) ); }
inline overror_t  cudaMI_equ1( iMatrix MA, ui len )
	{	return cudaMIequ1( (iPMatrix)(MA), len );} /* identity matrix */
inline overror_t  cudaMI_equm1( iMatrix MA, ui len )
	{	return cudaMIequm1( (iPMatrix)(MA), len );} /* neg. identity matrix */

inline overror_t  cudaMI_randomLC( iMatrix MA, ui ht, ui len, long seed, int MinVal, int MaxVal, V_RANDOMLCSTATE *h_state )
	{	return cudaVI_randomLC( (iPMatrix)(MA), (ht)*(len), seed, MinVal, MaxVal, h_state );}
inline overror_t  cudaMI_random( iMatrix MA, ui ht, ui len, long seed, int MinVal, int MaxVal )
	{	return cudaVI_random( (iPMatrix)(MA), (ht)*(len), seed, MinVal, MaxVal );}
inline overror_t  cusdMI_randomLC( iMatrix MA, ui ht, ui len, long seed, int *d_MinVal, int *d_MaxVal, V_RANDOMLCSTATE *h_state )
	{	return cusdVI_randomLC( (iPMatrix)(MA), (ht)*(len), seed, d_MinVal, d_MaxVal, h_state );}
inline overror_t  cusdMI_random( iMatrix MA, ui ht, ui len, long seed, int *d_MinVal, int *d_MaxVal )
	{	return cusdVI_random( (iPMatrix)(MA), (ht)*(len), seed, d_MinVal, d_MaxVal );}
inline overror_t  cudaMI_outerprod( iMatrix MA, iVector X,  iVector Y, ui ht, ui len )
{	return cudaMIouterprod( (iPMatrix)(MA), X, Y, ht, len );}

inline overror_t  cudaMI_Row_equ0( iMatrix MA, ui ht, ui len, ui iRow )
	{	return cudaMIRow_equ0( (iPMatrix)MA, ht, len, iRow );}
inline overror_t  cudaMI_Col_equ0( iMatrix MA, ui ht, ui len, ui iRow )
	{	return cudaMICol_equ0( (iPMatrix)MA, ht, len, iRow );}
inline overror_t  cudaMI_Dia_equ0( iMatrix MA, ui len )
	{	return cudaMIDia_equ0( (iPMatrix)(MA), len );}

inline overror_t  cudaMI_Row_equC( iMatrix MA, ui ht, ui len, ui iRow, int C )
	{	return cudaMIRow_equC( (iPMatrix)MA, ht, len, iRow, C );}
inline overror_t  cudaMI_Col_equC( iMatrix MA, ui ht, ui len, ui iRow, int C )
	{	return cudaMICol_equC( (iPMatrix)MA, ht, len, iRow, C );}
inline overror_t  cudaMI_Dia_equC( iMatrix MA, ui len, int C )
	{	return cudaMIDia_equC( (iPMatrix)(MA), len, C );}

inline overror_t  cusdMI_Row_equC( iMatrix MA, ui ht, ui len, ui iRow, int *d_C )
	{	return cusdMIRow_equC( (iPMatrix)MA, ht, len, iRow, d_C );}
inline overror_t  cusdMI_Col_equC( iMatrix MA, ui ht, ui len, ui iRow, int *d_C )
	{	return cusdMICol_equC( (iPMatrix)MA, ht, len, iRow, d_C );}
inline overror_t  cusdMI_Dia_equC( iMatrix MA, ui len, int *d_C )
	{	return cusdMIDia_equC( (iPMatrix)(MA), len, d_C );}

inline overror_t  cudaMI_Row_equV( iMatrix MA, ui ht, ui len, ui iRow, iVector X )
	{	return cudaMIRow_equV( (iPMatrix)MA, ht, len, iRow, X );}
inline overror_t  cudaMI_Col_equV( iMatrix MA, ui ht, ui len, ui iRow, iVector X )
	{	return cudaMICol_equV( (iPMatrix)MA, ht, len, iRow, X );}
inline overror_t  cudaMI_Dia_equV( iMatrix MA, ui len, iVector X )
	{	return cudaMIDia_equV( (iPMatrix)(MA), len, X );}

inline overror_t  cudaMI_Trd_equM( iMatrix MA, iMatrix MTrd, ui len )
	{	return cudaMITrd_equM( (iPMatrix)(MA), (iPMatrix)(MTrd), len );}
inline overror_t  cudaMI_Trd_extract( iMatrix MTrd, iMatrix MA, ui len )
	{	return cudaMITrd_extract( (iPMatrix)(MTrd), (iPMatrix)(MA), len );}

inline overror_t cudaMI_equM( iMatrix MB, iMatrix MA, ui ht, ui len )
	{	return cudaVI_equV( (iPMatrix)MB, (iPMatrix)MA, (ht)*(len) );}
inline overror_t cudaMI_equMhost( iMatrix d_MB, iMatrix h_MA, ui ht, ui len )
	{	return cudaVI_equVhost( (iPMatrix)d_MB, (h_MA)[0], (ht)*(len) );}
inline overror_t MI_equMdevice( iMatrix h_MB, iMatrix d_MA, ui ht, ui len )
	{	return VI_equVdevice( h_MB[0], (iPMatrix)d_MA, (ht)*(len) );}
inline overror_t cudaMI_neg( iMatrix MB, iMatrix MA, ui ht, ui len )
	{	return cudaVI_neg( (iPMatrix)(MB), (iPMatrix)(MA), (ht)*(len) );}
inline overror_t  cudaMI_UequL( iMatrix MA, ui len )
	{	return cudaMIUequL( (iPMatrix)(MA), len );}
inline overror_t  cudaMI_LequU( iMatrix MA, ui len )
	{	return cudaMILequU( (iPMatrix)(MA), len );}

/************** Data-type interconversions  ****************************/

inline overror_t cudaM_UtoI( iMatrix MI, ubMatrix MU, ui ht, ui len )
	{	return cudaV_UtoI( (iVector)MI, (uVector)MU, (ht)*(len) );}
inline overror_t cudaM_BItoI( iMatrix MI, biMatrix MBI, ui ht, ui len )
	{	return cudaV_BItoI( (iVector)MI, (biVector)MBI, (ht)*(len) );}
inline overror_t cudaM_SItoI(  iMatrix MI, siMatrix MSI,  ui ht, ui len )
	{	return cudaV_SItoI(  (iVector)MI, (siVector)MSI,   (ht)*(len) );}
inline overror_t cudaM_LItoI( iMatrix MI, liMatrix MLI, ui ht, ui len )
	{	return cudaV_LItoI( (iVector)MI, (liVector)MLI, (ht)*(len) );}
inline overror_t cudaM_QItoI( iMatrix MI, qiMatrix MQI, ui ht, ui len )
	{	return cudaV_QItoI( (iVector)MI, (qiVector)MQI, (ht)*(len) );}
inline overror_t cudaM_ItoF(  fMatrix MF,  iMatrix MI, ui ht, ui len )
	{	return cudaV_ItoF(  (fVector)MF,   (iVector)MI, (ht)*(len) );}
inline overror_t cudaM_ItoD(  dMatrix MD,  iMatrix MI, ui ht, ui len )
	{	return cudaV_ItoD(  (dVector)MD,   (iVector)MI, (ht)*(len) );}

/********  Extracting a submatrix and copying a submatrix back  *********/

inline overror_t cudaMI_submatrix( iMatrix MSub, ui subHt, ui subLen, iMatrix MSrce, ui srceHt, ui srceLen,
                      ui firstRowInCol, ui sampInCol, ui firstColInRow, ui sampInRow )
	{	return cudaMIsubmatrix(  (iPMatrix)(MSub), subHt, subLen,
		                         (iPMatrix)(MSrce), srceHt, srceLen,
								 firstRowInCol, sampInCol, firstColInRow, sampInRow ); }

inline overror_t cudaMI_submatrix_equM( iMatrix MDest, ui destHt, ui destLen,
                           ui firstRowInCol, ui sampInCol, ui firstColInRow, ui sampInRow,
                           iMatrix MSrce, ui srceHt, ui srceLen )
	{	return cudaMIsubmatrix_equM(  (iPMatrix)(MDest), destHt, destLen,
                             firstRowInCol, sampInCol, firstColInRow, sampInRow,
							 (iPMatrix)(MSrce), srceHt, srceLen );}

inline overror_t cudaMI_equMblock( iMatrix MSub, ui subHt, ui subLen, iMatrix MSrce, ui srceHt, ui srceLen,
                      ui firstRowInCol, ui firstColInRow )
{	return cudaMIequMblock(  (iPMatrix)(MSub), subHt, subLen,
						   (iPMatrix)(MSrce), srceHt, srceLen, firstRowInCol, firstColInRow );}

inline overror_t cudaMI_block_equM( iMatrix MDest, ui destHt, ui destLen,
                       ui firstRowInCol, ui firstColInRow,
                       iMatrix MSrce, ui srceHt, ui srceLen )
	{	return cudaMIblock_equM( (iPMatrix)(MDest), destHt, destLen,
                             firstRowInCol, firstColInRow,
							 (iPMatrix)(MSrce), srceHt, srceLen );}

inline overror_t cudaMI_equMblockT( iMatrix MSub, ui subHt, ui subLen, iMatrix MSrce, ui srceHt, ui srceLen,
                      ui firstRowInCol, ui firstColInRow )
	{	return cudaMIequMblockT(  (iPMatrix)(MSub), subHt, subLen,
                             (iPMatrix)(MSrce), srceHt, srceLen,
							 firstRowInCol, firstColInRow );}

inline overror_t cudaMI_block_equMT( iMatrix MDest, ui destHt, ui destLen,
                       ui firstRowInCol, ui firstColInRow,
                       iMatrix MSrce, ui srceHt, ui srceLen )
	{	return cudaMIblock_equMT( (iPMatrix)(MDest), destHt, destLen,
                             firstRowInCol, firstColInRow,
							 (iPMatrix)(MSrce), srceHt, srceLen );}

/*****   Extracting a single row or a single column or the diagonal  ******
 *       and storing it into a vector                                     */

inline overror_t cudaMI_Row_extract( iVector Y, iMatrix MA, ui ht, ui len, ui iRow ) 
	{	return cudaMIRow_extract( Y, (iPMatrix)(MA), ht, len, iRow );}
inline overror_t cudaMI_Col_extract( iVector Y, iMatrix MA, ui ht, ui len, ui iCol ) 
	{	return cudaMICol_extract( Y, (iPMatrix)(MA), ht, len, iCol );}
inline overror_t cudaMI_Dia_extract( iVector Y, iMatrix MA, ui len )
	{	return cudaMIDia_extract( Y, (iPMatrix)(MA), len );}

/**************  Deleting or inserting a row or a column   ***************/

inline overror_t cudaMI_Row_delete( iMatrix MB, iMatrix MA, ui htA, ui lenA, ui iRow )
	{	return cudaMIRow_delete( (iPMatrix)(MB), (iPMatrix)(MA), htA, lenA, iRow );}
inline overror_t cudaMI_Col_delete( iMatrix MB, iMatrix MA, ui htA, ui lenA, ui iCol )
	{	return cudaMICol_delete( (iPMatrix)(MB), (iPMatrix)(MA), htA, lenA, iCol );}
inline overror_t cudaMI_Row_insert( iMatrix MB, iMatrix MA, ui htB, ui lenB, ui iRow, iVector X )
	{	return cudaMIRow_insert( (iPMatrix)(MB), (iPMatrix)(MA), htB, lenB, iRow, X );}
inline overror_t cudaMI_Col_insert( iMatrix MB, iMatrix MA, ui htB, ui lenB, ui iCol, iVector X )
	{	return cudaMICol_insert( (iPMatrix)(MB), (iPMatrix)(MA), htB, lenB, iCol, X );}


/******  One-dimensional vector operations **********************
         performed along all rows or all columns simultaneously,
         or along the diagonal of a square matrix                */

inline overror_t cudaMI_Rows_max( iVector Y, iMatrix MA, ui ht, ui len )
	{	return cudaMIRows_max( Y, (iPMatrix)(MA), ht, len );}
inline overror_t cudaMI_Cols_max( iVector Y, iMatrix MA, ui ht, ui len )
	{	return cudaMICols_max( Y, (iPMatrix)(MA), ht, len );}
inline overror_t cudaMI_Dia_max(  int *h_RetValPtr, iMatrix MA, ui len )
	{	return cudaMIDia_max(  h_RetValPtr, (iPMatrix)(MA), len );}
inline overror_t cusdMI_Dia_max(  int *d_RetValPtr, iMatrix MA, ui len )
	{	return cusdMIDia_max(  d_RetValPtr, (iPMatrix)(MA), len );}
inline overror_t cudaMI_Rows_min( iVector Y, iMatrix MA, ui ht, ui len )
	{	return cudaMIRows_min( Y, (iPMatrix)(MA), ht, len );}
inline overror_t cudaMI_Cols_min( iVector Y, iMatrix MA, ui ht, ui len )
	{	return cudaMICols_min( Y, (iPMatrix)(MA), ht, len );}
inline overror_t cudaMI_Dia_min(  int *h_RetValPtr, iMatrix MA, ui len )
	{	return cudaMIDia_min(  h_RetValPtr, (iPMatrix)(MA), len );}
inline overror_t cusdMI_Dia_min(  int *d_RetValPtr, iMatrix MA, ui len )
	{	return cusdMIDia_min(  d_RetValPtr, (iPMatrix)(MA), len );}

inline overror_t cudaMI_Rows_rotate( iMatrix MA, ui ht, ui len, ssize_t pos)
	{	return cudaMIRows_rotate( (iPMatrix)(MA), ht, len, pos );}
inline overror_t cudaMI_Cols_rotate( iMatrix MA, ui ht, ui len, ssize_t pos)
	{	return cudaMICols_rotate( (iPMatrix)(MA), ht, len, pos );}
inline overror_t cudaMI_Rows_rotate_buf( iMatrix MA, ui ht, ui len, ssize_t pos, iMatrix MBuf) 
	{	return cudaMIRows_rotate_buf( (iPMatrix)(MA), ht, len, pos, (iPMatrix)(MBuf) );}
inline overror_t cudaMI_Cols_rotate_buf( iMatrix MA, ui ht, ui len, ssize_t pos, iMatrix MBuf) 
	{	return cudaMICols_rotate_buf( (iPMatrix)(MA), ht, len, pos, (iPMatrix)(MBuf) );}
inline overror_t cudaMI_Rows_reflect( iMatrix MA, ui ht, ui len )
	{	return cudaMIRows_reflect( (iPMatrix)(MA), ht, len );}
inline overror_t cudaMI_Cols_reflect( iMatrix MA, ui ht, ui len )
	{	return cudaMICols_reflect( (iPMatrix)(MA), ht, len );}
inline overror_t cudaMI_Rows_rev( iMatrix MA, ui ht, ui len )
	{	return cudaMIRows_rev( (iPMatrix)(MA), ht, len );}
inline overror_t cudaMI_Cols_rev( iMatrix MA, ui ht, ui len )
	{	return cudaMICols_rev( (iPMatrix)(MA), ht, len );}
inline overror_t  cudaMI_Rows_distribution( uiMatrix MAbund, iVector Limits, ui nBins, iMatrix MX, ui ht, ui len, int mode )
	{	return cudaMIRows_distribution( (uiPMatrix)MAbund, Limits, nBins, (iPMatrix)MX, ht, len, mode ); }
inline overror_t  cudaMI_Cols_distribution( uiMatrix MAbund, iVector Limits, ui nBins, iMatrix MX, ui ht, ui len, int mode )
	{	return cudaMICols_distribution( (uiPMatrix)MAbund, Limits, nBins, (iPMatrix)MX, ht, len, mode ); }

/********  Operations involving two rows or two colums of one matrix  *****/

inline overror_t cudaMI_Rows_exchange( iMatrix MA, ui ht, ui len, ui row1, ui row2 )
	{	return cudaMIRows_exchange( (iPMatrix)(MA), ht, len, row1, row2 );}
inline overror_t cudaMI_Cols_exchange( iMatrix MA, ui ht, ui len, ui col1, ui col2 )
	{	return cudaMICols_exchange( (iPMatrix)(MA), ht, len, col1, col2 );}

/*************** Transposing and rotating a matrix **********************/

inline overror_t cudaMI_transpose( iMatrix MTr, iMatrix MA, ui htTr, ui lenTr )
	{	return cudaMItranspose( (iPMatrix)(MTr), (iPMatrix)(MA), htTr, lenTr );}
       /*  dimensions htTr, lenTr are those of the transposed matrix, not of the original!   */
inline overror_t cudaMI_rotate90( iMatrix MRot, iMatrix MA, ui htRot, ui lenRot )
	{	return cudaMIrotate90( (iPMatrix)(MRot), (iPMatrix)(MA), htRot, lenRot );}
inline overror_t cudaMI_rotate180( iMatrix MRot, iMatrix MA, ui htRot, ui lenRot )
	{	return cudaVI_rev( (iPMatrix)(MRot), (iPMatrix)(MA), (htRot)*(lenRot) );}
inline overror_t cudaMI_rotate270( iMatrix MRot, iMatrix MA, ui htRot, ui lenRot )
	{	return cudaMIrotate270( (iPMatrix)(MRot), (iPMatrix)(MA), htRot, lenRot );}
inline overror_t cudaMI_transpose_buf( iMatrix MTr, iMatrix MA, ui htTr, ui lenTr, iMatrix MBuf )
	{	return cudaMItranspose_buf( (iPMatrix)(MTr), (iPMatrix)(MA), htTr, lenTr, (iPMatrix)(MBuf) );}

/**************************  Input and Output  **************************
	The input/output functions involve memory transfers from device
	to host memory or vice versa. The generic cudaMI_input/output functions
	allocate their own host buffers, whereas the cudaMI_xxx_buf functions
	take a user-supplied buffer vector h_Wk (size must be >= ht*len )
	and are much more efficient.                                       */

inline overror_t cudaMI_fprint( FILE *stream, iMatrix MA, ui ht, ui len, unsigned linewidth )
	{	return cudaMIfprint( stream, (iPMatrix)(MA), ht, len, linewidth ); }
inline overror_t cudaMI_print( iMatrix MA, ui ht, ui len )
	{	return cudaMIfprint( stdout, (iPMatrix)(MA), ht, len, 80 ); }
inline overror_t cudaMI_cprint( iMatrix MA, ui ht, ui len )
	{	return cudaMIcprint( (iPMatrix)(MA), ht, len ); }
inline overror_t cudaMI_fprint_buf( FILE *stream, iMatrix d_MA, ui ht, ui len, unsigned linewidth, iVector h_Wk )
	{	return cudaMIfprint_buf( stream, (iPMatrix)(d_MA), ht, len, linewidth, h_Wk ); }
inline overror_t cudaMI_print_buf( iMatrix d_MA, ui ht, ui len, iVector h_Wk )
	{	return cudaMIfprint_buf( stdout, (iPMatrix)(d_MA), ht, len, 80, h_Wk ); }
inline overror_t cudaMI_cprint_buf( iMatrix d_MA, ui ht, ui len, iVector h_Wk )
	{	return cudaMIcprint_buf( (iPMatrix)(d_MA), ht, len, h_Wk ); }
		/*  cudaMI_print, cudaMI_cprint usable only for console applications! */
inline overror_t  cudaMI_write( FILE *stream, iMatrix MA, ui ht, ui len )
	{	return cudaMIwrite( stream, (iPMatrix)(MA), ht, len ); }
inline overror_t cudaMI_read( iMatrix MA, ui ht, ui len, FILE *stream )
	{	return cudaMIread( (iPMatrix)(MA), ht, len, stream ); }
inline overror_t  cudaMI_write_buf( FILE *stream, iMatrix d_MA, ui ht, ui len, iVector h_Wk )
	{	return cudaMIwrite_buf( stream, (iPMatrix)(d_MA), ht, len, h_Wk ); }
inline overror_t cudaMI_read_buf( iMatrix d_MA, ui ht, ui len, FILE *stream, iVector h_Wk )
	{	return cudaMIread_buf( (iPMatrix)(d_MA), ht, len, stream, h_Wk ); }
                                   /* write and read in ascii format */
inline overror_t cudaMI_store( FILE *stream, iMatrix MA, ui ht, ui len )
{	return cudaVI_store( stream, (iPMatrix)(MA), (len)*(ht) ); }
inline overror_t cudaMI_recall( iMatrix MA, ui ht, ui len, FILE *stream )
	{	return cudaVI_recall( (iPMatrix)(MA), (len)*(ht), stream ); }
inline overror_t cudaMI_store_buf( FILE *stream, iMatrix d_MA, ui ht, ui len, iVector h_Wk )
{	return cudaVI_store_buf( stream, (iPMatrix)(d_MA), (len)*(ht), h_Wk ); }
inline overror_t cudaMI_recall_buf( iMatrix d_MA, ui ht, ui len, FILE *stream, iVector h_Wk )
	{	return cudaVI_recall_buf( (iPMatrix)(d_MA), (len)*(ht), stream, h_Wk ); }
                                  /* store and recall in binary format */

#else  /* plain-C, not C++: type-cast used to transform iMatrix into iPMatrix  */

/***  Addressing single elements of dynamically allocated matrices: ******/

#define cudaMI_setElement( MA, ht, len, m, n, C ) cudaMIsetElement( (iPMatrix)(MA), ht, len, m, n, C )
#define cusdMI_setElement( MA, ht, len, m, n, C ) cusdMIsetElement( (iPMatrix)(MA), ht, len, m, n, C )
#define cudaMI_getElement( y, MA, ht, len, m, n ) cudaMIgetElement( y, (iPMatrix)(MA), ht, len, m, n )
#define cusdMI_getElement( y, MA, ht, len, m, n ) cusdMIgetElement( y, (iPMatrix)(MA), ht, len, m, n )
#define cudaMI_Pelement( MA, ht, len, m, n )      cudaMIPelement( (iPMatrix)(MA), ht, len, m, n )
                     /* returns a pointer to MA[m][n]. */
#define cudaMI_element( MA, ht, len, m, n )       cudaMIelement( (iPMatrix)(MA), ht, len, m, n )

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
        VI_equ1( (iVector)MA, ht * len );
*/

#define cudaMI_equ0( MA, ht, len )            cudaVI_equ0( (iPMatrix)(MA), (ht)*(len) )
#define cudaMI_equ1( MA, len )                cudaMIequ1( (iPMatrix)(MA), len ) /* identity matrix */
#define cudaMI_equm1( MA, len )               cudaMIequm1( (iPMatrix)(MA), len ) /* neg. identity matrix */
#define cudaMI_randomLC( MA, ht, len, seed, Min, Max, h_state )      cudaVI_randomLC( MA, (ht)*(len), seed, Min, Max, h_state )
#define cudaMI_random( MA, ht, len, seed, Min, Max )                 cudaVI_random( MA, (ht)*(len), seed, Min, Max )
#define cusdMI_randomLC( MA, ht, len, seed, d_Min, d_Max, h_state )  cudaVI_randomLC( MA, (ht)*(len), seed, d_Min, d_Max, h_state )
#define cusdMI_random( MA, ht, len, seed, d_Min, d_Max )             cudaVI_random( MA, (ht)*(len), seed, d_Min, d_Max )
#define cudaMI_outerprod( MA, X, Y, ht, len ) cudaMIouterprod( (iPMatrix)(MA), X, Y, ht, len )
                       /* sizX=ht, sizY=len */
#define cudaMI_Row_equ0( MA, ht, len, iRow )  cudaMIRow_equ0( (iPMatrix)(MA), ht, len, iRow )
#define cudaMI_Col_equ0( MA, ht, len, iCol )  cudaMICol_equ0( (iPMatrix)(MA), ht, len, iCol )
#define cudaMI_Dia_equ0( MA, len )            cudaMIDia_equ0( (iPMatrix)(MA), len )
#define cudaMI_Row_equC( MA, ht, len, iRow, C ) cudaMIRow_equC( (iPMatrix)(MA), ht, len, iRow, C )
#define cudaMI_Col_equC( MA, ht, len, iCol, C ) cudaMICol_equC( (iPMatrix)(MA), ht, len, iCol, C )
#define cudaMI_Dia_equC( MA, len, C )           cudaMIDia_equC( (iPMatrix)(MA), len, C )
#define cusdMI_Row_equC( MA, ht, len, iRow, d_C ) cusdMIRow_equC( (iPMatrix)(MA), ht, len, iRow, d_C )
#define cusdMI_Col_equC( MA, ht, len, iCol, d_C ) cusdMICol_equC( (iPMatrix)(MA), ht, len, iCol, d_C )
#define cusdMI_Dia_equC( MA, len, d_C )           cusdMIDia_equC( (iPMatrix)(MA), len, d_C )

#define cudaMI_Row_equV( MA, ht, len, iRow, X ) cudaMIRow_equV( (iPMatrix)(MA), ht, len, iRow, X )
#define cudaMI_Col_equV( MA, ht, len, iCol, X ) cudaMICol_equV( (iPMatrix)(MA), ht, len, iCol, X )
#define cudaMI_Dia_equV( MA, len, X )           cudaMIDia_equV( (iPMatrix)(MA), len, X )

#define cudaMI_Trd_equM( MA, MTrd, len )    cudaMITrd_equM( (iPMatrix)(MA), (iPMatrix)(MTr)d, len )
#define cudaMI_Trd_extract( MTrd, MA, len ) cudaMITrd_extract( (iPMatrix)(MTr)d, (iPMatrix)(MA), len )

#define cudaMI_equM( MB, MA, ht, len )      cudaVI_equV( (iPMatrix)(MB), (iPMatrix)(MA), (ht)*(len) )
#define cudaMI_equMhost( MB, MA, ht, len )  cudaVI_equVhost( (iPMatrix)(MB), MA[0], (ht)*(len) )
#define MI_equMdevice( MB, MA, ht, len )    VI_equVdevice( MB[0], (iPMatrix)(MA), (ht)*(len) )
#define cudaMI_neg( MB, MA, ht, len )       cudaVI_neg( (iPMatrix)(MB), (iPMatrix)(MA), (ht)*(len) )

#define cudaMI_UequL( MA, len ) cudaMIUequL( (iPMatrix)(MA), len )
#define cudaMI_LequU( MA, len ) cudaMILequU( (iPMatrix)(MA), len )


/************** Data-type interconversions  ****************************/

#define cudaM_ItoU( MU, MI, ht, len ) cudaV_ItoU( (uVector)(MU), (iVector)(MI), (ht)*(len) )
#define cudaM_UtoI( MI, MU, ht, len ) cudaV_UtoI( (iVector)(MI), (uVector)(MU), (ht)*(len) )
#define cudaM_ItoBI( MBI, MI, ht, len ) cudaV_ItoBI( (biVector)(MBI), (iVector)(MI), (ht)*(len) )
#define cudaM_ItoSI( MSI, MI, ht, len ) cudaV_ItoSI( (siVector)(MSI), (iVector)(MI), (ht)*(len) )
#define cudaM_ItoLI( MLI, MI, ht, len ) cudaV_ItoLI( (liVector)(MLI), (iVector)(MI), (ht)*(len) )
#define cudaM_ItoQI( MQI, MI, ht, len ) cudaV_ItoQI( (qiVector)(MQI), (iVector)(MI), (ht)*(len) )
#define cudaM_BItoI( MI, MBI, ht, len ) cudaV_BItoI( (iVector)(MI), (biVector)(MBI), (ht)*(len) )
#define cudaM_SItoI( MI, MSI, ht, len ) cudaV_SItoI( (iVector)(MI), (siVector)(MSI), (ht)*(len) )
#define cudaM_LItoI( MI, MLI, ht, len ) cudaV_LItoI( (iVector)(MI), (liVector)(MLI), (ht)*(len) )
#define cudaM_QItoI( MI, MQI, ht, len ) cudaV_QItoI( (iVector)(MI), (qiVector)(MQI), (ht)*(len) )
#define cudaM_ItoF(  MF,  MI, ht, len ) cudaV_ItoF(  (fVector)(MF),   (iVector)(MI), (ht)*(len) )
#define cudaM_ItoD(  MD,  MI, ht, len ) cudaV_ItoD(  (dVector)(MD),   (iVector)(MI), (ht)*(len) )

/********  Extracting a submatrix and copying a submatrix back  *********/

#define cudaMI_submatrix( MSub, subHt, subLen, MSrce, srceHt, srceLen, \
                      firstRowInCol, sampInCol, firstColInRow, sampInRow ) \
               cudaMIsubmatrix(  (iPMatrix)(MSub), subHt, subLen, \
                             (iPMatrix)(MSrce), srceHt, srceLen, \
                             firstRowInCol, sampInCol, firstColInRow, sampInRow )

#define cudaMI_submatrix_equM( MDest, destHt, destLen, \
                           firstRowInCol, sampInCol, firstColInRow, sampInRow, \
                           MSrce, srceHt, srceLen ) \
               cudaMIsubmatrix_equM(  (iPMatrix)(MDest), destHt, destLen, \
                             firstRowInCol, sampInCol, firstColInRow, sampInRow, \
                             (iPMatrix)(MSrce), srceHt, srceLen )

#define cudaMI_equMblock( MSub, subHt, subLen, \
                      MSrce, srceHt, srceLen, \
                      firstRowInCol, firstColInRow ) \
               cudaMIequMblock(  (iPMatrix)(MSub), subHt, subLen, \
                             (iPMatrix)(MSrce), srceHt, srceLen, \
                             firstRowInCol, firstColInRow )

#define cudaMI_block_equM( MDest, destHt, destLen, \
                       firstRowInCol, firstColInRow, \
                       MSrce, srceHt, srceLen ) \
               cudaMIblock_equM( (iPMatrix)(MDest), destHt, destLen, \
                             firstRowInCol, firstColInRow, \
                             (iPMatrix)(MSrce), srceHt, srceLen )

#define cudaMI_equMblockT( MSub, subHt, subLen, \
                      MSrce, srceHt, srceLen, \
                      firstRowInCol, firstColInRow ) \
               cudaMIequMblockT(  (iPMatrix)(MSub), subHt, subLen, \
                             (iPMatrix)(MSrce), srceHt, srceLen, \
                             firstRowInCol, firstColInRow )

#define cudaMI_block_equMT( MDest, destHt, destLen, \
                       firstRowInCol, firstColInRow, \
                       MSrce, srceHt, srceLen ) \
               cudaMIblock_equMT( (iPMatrix)(MDest), destHt, destLen, \
                             firstRowInCol, firstColInRow, \
                             (iPMatrix)(MSrce), srceHt, srceLen )

/*****   Extracting a single row or a single column or the diagonal  ******
 *       and storing it into a vector                                     */

#define cudaMI_Row_extract( Y, MA, ht, len, iRow ) \
                                     cudaMIRow_extract( Y, (iPMatrix)(MA), ht, len, iRow )
#define cudaMI_Col_extract( Y, MA, ht, len, iCol ) \
                                     cudaMICol_extract( Y, (iPMatrix)(MA), ht, len, iCol )
#define cudaMI_Dia_extract( Y, MA, len ) cudaMIDia_extract( Y, (iPMatrix)(MA), len )


/**************  Deleting or inserting a row or a column   ***************/

#define cudaMI_Row_delete( MB, MA, htA, lenA, iRow ) \
                           cudaMIRow_delete( (iPMatrix)(MB), (iPMatrix)(MA), htA, lenA, iRow )
#define cudaMI_Col_delete( MB, MA, htA, lenA, iCol ) \
                           cudaMICol_delete( (iPMatrix)(MB), (iPMatrix)(MA), htA, lenA, iCol )
#define cudaMI_Row_insert( MB, MA, htB, lenB, iRow, X ) \
                           cudaMIRow_insert( (iPMatrix)(MB), (iPMatrix)(MA), htB, lenB, iRow, X )
#define cudaMI_Col_insert( MB, MA, htB, lenB, iCol, X ) \
                           cudaMICol_insert( (iPMatrix)(MB), (iPMatrix)(MA), htB, lenB, iCol, X )

/******  One-dimensional vector operations **********************
         performed aint all rows or all columns simultaneously,
         or aint the diagonal of a square matrix                */

#define cudaMI_Rows_max( Y, MA, ht, len )     cudaMIRows_max( Y, (iPMatrix)(MA), ht, len )
#define cudaMI_Cols_max( Y, MA, ht, len )     cudaMICols_max( Y, (iPMatrix)(MA), ht, len )
#define cudaMI_Dia_max(  h_RetPtr, MA, len )  cudaMIDia_max( h_RetPtr, (iPMatrix)(MA), len )
#define cusdMI_Dia_max(  d_RetPtr, MA, len )  cusdMIDia_max( d_RetPtr, (iPMatrix)(MA), len )
#define cudaMI_Rows_min( Y, MA, ht, len )     cudaMIRows_min( Y, (iPMatrix)(MA), ht, len )
#define cudaMI_Cols_min( Y, MA, ht, len )     cudaMICols_min( Y, (iPMatrix)(MA), ht, len )
#define cudaMI_Dia_min(  h_RetPtr, MA, len )  cudaMIDia_min( h_RetPtr, (iPMatrix)(MA), len )
#define cusdMI_Dia_min(  d_RetPtr, MA, len )  cusdMIDia_min( d_RetPtr, (iPMatrix)(MA), len )

#define cudaMI_Rows_rotate( MA, ht, len, pos) cudaMIRows_rotate( (iPMatrix)(MA), ht, len, pos )
#define cudaMI_Cols_rotate( MA, ht, len, pos) cudaMICols_rotate( (iPMatrix)(MA), ht, len, pos )
#define cudaMI_Rows_rotate_buf( MA, ht, len, pos, MBuf) cudaMIRows_rotate_buf( (iPMatrix)(MA), ht, len, pos, (iPMatrix)(MBuf) )
#define cudaMI_Cols_rotate_buf( MA, ht, len, pos, MBuf) cudaMICols_rotate_buf( (iPMatrix)(MA), ht, len, pos, (iPMatrix)(MBuf) )
#define cudaMI_Rows_reflect( MA, ht, len)     cudaMIRows_reflect( (iPMatrix)(MA), ht, len )
#define cudaMI_Cols_reflect( MA, ht, len)     cudaMICols_reflect( (iPMatrix)(MA), ht, len )
#define cudaMI_Rows_rev( MA, ht, len)         cudaMIRows_rev( (iPMatrix)(MA), ht, len )
#define cudaMI_Cols_rev( MA, ht, len)         cudaMICols_rev( (iPMatrix)(MA), ht, len )
#define cudaMI_Rows_distribution( MAbund, Limits, nBins, MX, ht, len, mode ) cudaMIRows_distribution( (uiPMatrix)MAbund, Limits, nBins, (iPMatrix)MX, ht, len, mode )
#define cudaMI_Cols_distribution( MAbund, Limits, nBins, MX, ht, len, mode ) cudaMICols_distribution( (uiPMatrix)MAbund, Limits, nBins, (iPMatrix)MX, ht, len, mode )

/********  Operations involving two rows or two colums of one matrix  *****/

#define cudaMI_Rows_exchange( MA, ht, len, row1, row2 ) \
                             cudaMIRows_exchange( (iPMatrix)(MA), ht, len, row1, row2 )
#define cudaMI_Cols_exchange( MA, ht, len, col1, col2 ) \
                             cudaMICols_exchange( (iPMatrix)(MA), ht, len, col1, col2 )

/************  Transposing and rotating a matrix **********************/

#define cudaMI_transpose( MTr, MA, htTr, lenTr ) \
             cudaMItranspose( (iPMatrix)(MTr), (iPMatrix)(MA), htTr, lenTr )
       /*  dimensions htTr, lenTr are those of the transposed matrix,
           not of the original!                */
#define cudaMI_rotate90( MRot, MA, htRot, lenRot ) \
             cudaMIrotate90( (iPMatrix)(MRot), (iPMatrix)(MA), htRot, lenRot )
#define cudaMI_rotate180( MRot, MA, htRot, lenRot ) \
             cudaVI_rev( (iPMatrix)(MRot), (iPMatrix)(MA), (htRot)*(lenRot) )
#define cudaMI_rotate270( MRot, MA, htRot, lenRot ) \
             cudaMIrotate270( (iPMatrix)(MRot), (iPMatrix)(MA), htRot, lenRot )
#define cudaMI_transpose_buf( MTr, MA, htTr, lenTr, MBuf ) \
             cudaMItranspose_buf( (iPMatrix)(MTr), (iPMatrix)(MA), htTr, lenTr, (iPMatrix)(MBuf) )

/**************************  Input and Output  **************************
	The input/output functions involve memory transfers from device
	to host memory or vice versa. The generic cudaMI_input/output functions
	allocate their own host buffers, whereas the cudaMI_xxx_buf functions
	take a user-supplied buffer vector h_Wk (size must be >= ht*len )
	and are much more efficient.                                       */

#define cudaMI_fprint( stream, MA, ht, len, linewidth ) \
                    cudaMIfprint( stream, (iPMatrix)(MA), ht, len, linewidth )
#define cudaMI_print( MA, ht, len )  cudaMIfprint( stdout, (iPMatrix)(MA), ht, len, 80 )
#define cudaMI_cprint( MA, ht, len ) cudaMIcprint( (iPMatrix)(MA), ht, len )
#define cudaMI_fprint_buf( stream, MA, ht, len, linewidth, h_Wk ) \
                    cudaMIfprint_buf( stream, (iPMatrix)(MA), ht, len, linewidth, h_Wk )
#define cudaMI_print_buf( MA, ht, len )  cudaMIfprint_buf( stdout, (iPMatrix)(MA), ht, len, 80, h_Wk )
#define cudaMI_cprint_buf( MA, ht, len ) cudaMIcprint_buf( (iPMatrix)(MA), ht, len, h_Wk )
  /*  cudaMI_print, cudaMI_cprint usable only for console applications! */
#define cudaMI_write( str, MA, ht, len )   cudaMIwrite( str, (iPMatrix)(MA), ht, len )
#define cudaMI_read( MA, ht, len, str )    cudaMIread( (iPMatrix)(MA), ht, len, str )
#define cudaMI_write_buf( str, MA, ht, len, h_Wk )   cudaMIwrite_buf( str, (iPMatrix)(MA), ht, len, h_Wk )
#define cudaMI_read_buf( MA, ht, len, str, h_Wk )    cudaMIread_buf( (iPMatrix)(MA), ht, len, str, h_Wk )
                                   /* write and read in ascii format */
#define cudaMI_store( str, MA, ht, len )   cudaVI_store( str, (iPMatrix)(MA), (len)*(ht) )
#define cudaMI_recall( MA, ht, len, str)   cudaVI_recall( (iPMatrix)(MA), (len)*(ht), str)
#define cudaMI_store_buf( str, MA, ht, len, h_Wk )   cudaVI_store_buf( str, (iPMatrix)(MA), (len)*(ht), h_Wk )
#define cudaMI_recall_buf( MA, ht, len, str, h_Wk)   cudaVI_recall_buf( (iPMatrix)(MA), (len)*(ht), str, h_Wk )
                                  /* store and recall in binary format */

#endif /* plain-C or C++ for functions working on device memory  */


/*******************  Functions working on host memory: **********************
 *                                                                           *
 *	MIcu_func		(working on matrices in host memory, input type iMatrix,*
 *	scalar parameters on host and passed by value)                           *
 *****************************************************************************/ 

/****************  Initialization  ****************************************/

#define MIcu_equ0( MA, ht, len )                   VIcu_equ0( (MA)[0], (ht)*(len) )
#define MIcu_equ1( MA, len )                       MIcuequ1( (MA)[0], len ) /* identity matrix */
#define MIcu_equm1( MA, len )                      MIcuequm1( (MA)[0], len ) /* neg. identity matrix */
#define MIcu_randomLC( MA, ht, len, seed, Min, Max, state ) VIcu_randomLC( (MA)[0], (ht)*(len), seed, Min, Max, state )
#define MIcu_random( MA, ht, len, seed, Min, Max )          VIcu_random( (MA)[0], (ht)*(len), seed, Min, Max )
#define MIcu_outerprod( MA, X, Y, ht, len )        MIcuouterprod( (MA)[0], X, Y, ht, len )
                       /* sizX=ht, sizY=len */
#define MIcu_Row_equ0( MA, ht, len, iRow )    MIcuRow_equ0( (MA)[0], ht, len, iRow )
#define MIcu_Col_equ0( MA, ht, len, iCol )    MIcuCol_equ0( (MA)[0], ht, len, iCol )
#define MIcu_Dia_equ0( MA, len )              MIcuDia_equ0( (MA)[0], len )
#define MIcu_Row_equC( MA, ht, len, iRow, C ) MIcuRow_equC( (MA)[0], ht, len, iRow, C )
#define MIcu_Col_equC( MA, ht, len, iCol, C ) MIcuCol_equC( (MA)[0], ht, len, iCol, C )
#define MIcu_Dia_equC( MA, len, C )           MIcuDia_equC( (MA)[0], len, C )

#define MIcu_Row_equV( MA, ht, len, iRow, X ) MIcuRow_equV( (MA)[0], ht, len, iRow, X )
#define MIcu_Col_equV( MA, ht, len, iCol, X ) MIcuCol_equV( (MA)[0], ht, len, iCol, X )
#define MIcu_Dia_equV( MA, len, X )           MIcuDia_equV( (MA)[0], len, X )

#define MIcu_Trd_equM( MA, MTrd, len )        MIcuTrd_equM( (MA)[0], (MTrd)[0], len )
#define MIcu_Trd_extract( MTrd, MA, len )     MIcuTrd_extract( (MTrd)[0], (MA)[0], len )

#define MIcu_equM( MB, MA, ht, len )          VIcu_equV( (MB)[0], (MA)[0], (ht)*(len) )
#define MIcu_equMhost( MB, MA, ht, len )      VIcu_equVhost( (MB)[0], MA[0], (ht)*(len) )
#define MIcu_neg( MB, MA, ht, len )           VIcu_neg( (MB)[0], (MA)[0], (ht)*(len) )

#define MIcu_UequL( MA, len ) MIcuUequL( (MA)[0], len )
#define MIcu_LequU( MA, len ) MIcuLequU( (MA)[0], len )
     /* copy lower-diagonal elements into upper-diagonal
       (or vice versa) by index-reflection, so as to get a symmetric matrix    */

            /* data-type conversions:  */
#define Mcu_ItoU( MU, MI, ht, len ) Vcu_ItoU( (MU)[0], (MI)[0], (ht)*(len) )
#define Mcu_UtoI( MI, MU, ht, len ) Vcu_UtoI( (MI)[0], (MU)[0], (ht)*(len) )
#define Mcu_ItoBI( MBI, MI, ht, len ) Vcu_ItoBI( (MBI)[0], (MI)[0], (ht)*(len) )
#define Mcu_ItoSI( MSI, MI, ht, len ) Vcu_ItoSI( (MSI)[0], (MI)[0], (ht)*(len) )
#define Mcu_ItoLI( MLI, MI, ht, len ) Vcu_ItoLI( (MLI)[0], (MI)[0], (ht)*(len) )
#define Mcu_ItoQI( MQI, MI, ht, len ) Vcu_ItoQI( (MQI)[0], (MI)[0], (ht)*(len) )
#define Mcu_BItoI( MI, MBI, ht, len ) Vcu_BItoI( (MI)[0], (MBI)[0], (ht)*(len) )
#define Mcu_SItoI( MI, MSI, ht, len ) Vcu_SItoI( (MI)[0], (MSI)[0], (ht)*(len) )
#define Mcu_LItoI( MI, MLI, ht, len ) Vcu_LItoI( (MI)[0], (MLI)[0], (ht)*(len) )
#define Mcu_QItoI( MI, MQI, ht, len ) Vcu_QItoI( (MI)[0], (MQI)[0], (ht)*(len) )
#define Mcu_ItoF(  MF,  MI, ht, len ) Vcu_ItoF(  (MF)[0],  (MI)[0], (ht)*(len) )
#define Mcu_ItoD(  MD,  MI, ht, len ) Vcu_ItoD(  (MD)[0],  (MI)[0], (ht)*(len) )


/********  Extracting a submatrix and copying a submatrix back  *********/

#define MIcu_submatrix( MSub, subHt, subLen, MSrce, srceHt, srceLen, \
                      firstRowInCol, sampInCol, firstColInRow, sampInRow ) \
               MIcusubmatrix(  (MSub)[0], subHt, subLen, \
                             (MSrce)[0], srceHt, srceLen, \
                             firstRowInCol, sampInCol, firstColInRow, sampInRow )

#define MIcu_submatrix_equM( MDest, destHt, destLen, \
                           firstRowInCol, sampInCol, firstColInRow, sampInRow, \
                           MSrce, srceHt, srceLen ) \
               MIcusubmatrix_equM(  (MDest)[0], destHt, destLen, \
                             firstRowInCol, sampInCol, firstColInRow, sampInRow, \
                             (MSrce)[0], srceHt, srceLen )

#define MIcu_equMblock( MSub, subHt, subLen, MSrce, srceHt, srceLen, \
                      firstRowInCol, firstColInRow ) \
               MIcuequMblock(  (MSub)[0], subHt, subLen, \
                             (MSrce)[0], srceHt, srceLen, \
                             firstRowInCol, firstColInRow )

#define MIcu_block_equM( MDest, destHt, destLen, \
                       firstRowInCol, firstColInRow, \
                       MSrce, srceHt, srceLen ) \
               MIcublock_equM( (MDest)[0], destHt, destLen, \
                             firstRowInCol, firstColInRow, \
                             (MSrce)[0], srceHt, srceLen )

#define MIcu_equMblockT( MSub, subHt, subLen, MSrce, srceHt, srceLen, \
                      firstRowInCol, firstColInRow ) \
               MIcuequMblockT(  (MSub)[0], subHt, subLen, \
                             (MSrce)[0], srceHt, srceLen, \
                             firstRowInCol, firstColInRow )

#define MIcu_block_equMT( MDest, destHt, destLen, \
                       firstRowInCol, firstColInRow, \
                       MSrce, srceHt, srceLen ) \
               MIcublock_equMT( (MDest)[0], destHt, destLen, \
                             firstRowInCol, firstColInRow, \
                             (MSrce)[0], srceHt, srceLen )

/*****   Extracting a single row or a single column or the diagonal  ******
 *       and storing it into a vector                                     */

#define MIcu_Row_extract( Y, MA, ht, len, iRow ) MIcuRow_extract( Y, (MA)[0], ht, len, iRow )
#define MIcu_Col_extract( Y, MA, ht, len, iCol ) MIcuCol_extract( Y, (MA)[0], ht, len, iCol )
#define MIcu_Dia_extract( Y, MA, len )           MIcuDia_extract( Y, (MA)[0], len )

/**************  Deleting or inserting a row or a column   ***************/

#define MIcu_Row_delete( MB, MA, htA, lenA, iRow )    MIcuRow_delete( (MB)[0], (MA)[0], htA, lenA, iRow )
#define MIcu_Col_delete( MB, MA, htA, lenA, iCol )    MIcuCol_delete( (MB)[0], (MA)[0], htA, lenA, iCol )
#define MIcu_Row_insert( MB, MA, htB, lenB, iRow, X ) MIcuRow_insert( (MB)[0], (MA)[0], htB, lenB, iRow, X )
#define MIcu_Col_insert( MB, MA, htB, lenB, iCol, X ) MIcuCol_insert( (MB)[0], (MA)[0], htB, lenB, iCol, X )


/*****************    Basic arithmetic operations *********************
                      performed on one single row,
                      or one single column of any matrix,
                      or on the diagonal of a square matrix

    Note: In contrast to the analogous VectorLib functions, the operations
    are performed in-place, i.e. the input matrix itself is changed  */

#define MIcu_Row_neg( MA, ht, len, iRow ) MIcuRow_neg( (MA)[0], ht, len, iRow )
#define MIcu_Col_neg( MA, ht, len, iCol ) MIcuCol_neg( (MA)[0], ht, len, iCol )

/******  One-dimensional vector operations **********************
         performed along all rows or all columns simultaneously,
         or along the diagonal of a square matrix                */

#define MIcu_Rows_max( Y, MA, ht, len )        MIcuRows_max( Y, (MA)[0], ht, len )
#define MIcu_Cols_max( Y, MA, ht, len )        MIcuCols_max( Y, (MA)[0], ht, len )
#define MIcu_Dia_max(  MA, len )               MIcuDia_max(  (MA)[0], len )
#define MIcu_Rows_min( Y, MA, ht, len )        MIcuRows_min( Y, (MA)[0], ht, len )
#define MIcu_Cols_min( Y, MA, ht, len )        MIcuCols_min( Y, (MA)[0], ht, len )
#define MIcu_Dia_min(  MA, len )               MIcuDia_min(  (MA)[0], len )

#define MIcu_Rows_rotate( MA, ht, len, pos)           MIcuRows_rotate( (MA)[0], ht, len, pos )
#define MIcu_Cols_rotate( MA, ht, len, pos)           MIcuCols_rotate( (MA)[0], ht, len, pos )
#define MIcu_Rows_rotate_buf( MA, ht, len, pos, MBuf) MIcuRows_rotate_buf( (MA)[0], ht, len, pos, (MBuf)[0] )
#define MIcu_Cols_rotate_buf( MA, ht, len, pos, MBuf) MIcuCols_rotate_buf( (MA)[0], ht, len, pos, (MBuf)[0] )
#define MIcu_Rows_reflect( MA, ht, len )              MIcuRows_reflect( (MA)[0], ht, len )
#define MIcu_Cols_reflect( MA, ht, len )              MIcuCols_reflect( (MA)[0], ht, len )
#define MIcu_Rows_rev( MA, ht, len)                   MIcuRows_rev( (MA)[0], ht, len )
#define MIcu_Cols_rev( MA, ht, len)                   MIcuCols_rev( (MA)[0], ht, len )
#define MIcu_Rows_distribution( MAbund, Limits, nBins, MX, ht, len, mode ) MIcuRows_distribution( MAbund[0], Limits, nBins, MX[0], ht, len, mode )
#define MIcu_Cols_distribution( MAbund, Limits, nBins, MX, ht, len, mode ) MIcuCols_distribution( MAbund[0], Limits, nBins, MX[0], ht, len, mode )

/********  Operations involving two rows or two colums of one matrix  *****/

#define MIcu_Rows_exchange( MA, ht, len, row1, row2 ) \
                             MIcuRows_exchange( (MA)[0], ht, len, row1, row2 )
#define MIcu_Cols_exchange( MA, ht, len, col1, col2 ) \
                             MIcuCols_exchange( (MA)[0], ht, len, col1, col2 )

/*************** Transposing and rotating a matrix **********************/

#define MIcu_transpose( MTr, MA, htTr, lenTr )    MIcutranspose( (MTr)[0], (MA)[0], htTr, lenTr )
       /*  dimensions htTr, lenTr are those of the transposed matrix, not of the original!   */
#define MIcu_rotate90( MRot, MA, htRot, lenRot )  MIcurotate90( (MRot)[0], (MA)[0], htRot, lenRot )
#define MIcu_rotate180( MRot, MA, htRot, lenRot ) VIcu_rev( (MRot)[0], (MA)[0], (htRot)*(lenRot) )
#define MIcu_rotate270( MRot, MA, htRot, lenRot ) MIcurotate270( (MRot)[0], (MA)[0], htRot, lenRot )


/*************************************************************************
 * MIcu functions (without underbar in the prefix): 	
    (working on matrices in host memory, input type 
	iPMatrix = iVector = pointer to matrix element[0][0], 
	scalar parameters on host and passed by value)
*
 *************************************************************************/

#define MIcuequ0( MA, ht, len )       VIcu_equ0( MA, (ht)*(len) )
void   __vf OVCUAPI  MIcuequ1( iPMatrix MA, ui len );  /* identity matrix */
void   __vf OVCUAPI  MIcuequm1( iPMatrix MA, ui len );  /* neg. identity matrix */
void   __vf OVCUAPI  MIcuouterprod( iPMatrix MA, iVector X,  iVector Y, ui ht, ui len );

void   __vf OVCUAPI  MIcuRow_equ0( iPMatrix MA, ui ht, ui len, ui iRow );
void   __vf OVCUAPI  MIcuCol_equ0( iPMatrix MA, ui ht, ui len, ui iCol );
void   __vf OVCUAPI  MIcuDia_equ0( iPMatrix MA, ui len );

void   __vf OVCUAPI  MIcuRow_equC( iPMatrix MA, ui ht, ui len, ui iRow, int C );
void   __vf OVCUAPI  MIcuCol_equC( iPMatrix MA, ui ht, ui len, ui iCol, int C );
void   __vf OVCUAPI  MIcuDia_equC( iPMatrix MA, ui len, int C );

void   __vf OVCUAPI  MIcuRow_equV( iPMatrix MA, ui ht, ui len, ui iRow, iVector X );
void   __vf OVCUAPI  MIcuCol_equV( iPMatrix MA, ui ht, ui len, ui iCol, iVector X );
void   __vf OVCUAPI  MIcuDia_equV( iPMatrix MA, ui len, iVector X );

void   __vf OVCUAPI  MIcuTrd_equM( iPMatrix MA, iPMatrix MTrd, ui len );
void   __vf OVCUAPI  MIcuTrd_extract( iPMatrix MTrd, iPMatrix MA, ui len );

#define MIcuequM( MB, MA, ht, len )      VIcu_equV( MB, MA, (ht)*(len) )
#define MIcuneg( MB, MA, ht, len )       VIcu_neg( MB, MA, (ht)*(len) )
void   __vf OVCUAPI  MIcuUequL( iPMatrix MA, ui len );
void   __vf OVCUAPI  MIcuLequU( iPMatrix MA, ui len );

            /* data-type conversions:  */
#define McuItoU( MU, MI, ht, len ) Vcu_ItoU( MU, MI, (ht)*(len) )
#define McuUtoI( MI, MU, ht, len ) Vcu_UtoI( MI, MU, (ht)*(len) )
#define McuItoBI( MBI, MI, ht, len ) Vcu_ItoBI( MBI, MI, (ht)*(len) )
#define McuItoSI( MSI, MI, ht, len ) Vcu_ItoSI( MSI, MI, (ht)*(len) )
#define McuItoLI( MLI, MI, ht, len ) Vcu_ItoLI( MLI, MI, (ht)*(len) )
#define McuItoQI( MQI, MI, ht, len ) Vcu_ItoQI( MQI, MI, (ht)*(len) )
#define McuBItoI( MI, MBI, ht, len ) Vcu_BItoI( MI,  MBI, (ht)*(len) )
#define McuSItoI( MI, MSI, ht, len ) Vcu_SItoI( MI,  MSI, (ht)*(len) )
#define McuLItoI( MI, MLI, ht, len ) Vcu_LItoI( MI,  MLI, (ht)*(len) )
#define McuQItoI( MI, MQI, ht, len ) Vcu_QItoI( MI,  MQI, (ht)*(len) )
#define McuItoF(  MF,  MI, ht, len ) Vcu_ItoF(  MF,  MI, (ht)*(len) )
#define McuItoD(  MD,  MI, ht, len ) Vcu_ItoD(  MD,  MI, (ht)*(len) )

/********  Extracting a submatrix and copying a submatrix back  *********/

void  __vf OVCUAPI  MIcusubmatrix( iPMatrix MSub, ui subHt,  ui subLen,
                          iPMatrix MSrce, ui srceHt,  ui srceLen,
                          ui firstRowInCol,  ui sampInCol,
                          ui firstColInRow,  ui sampInRow );

void  __vf OVCUAPI  MIcusubmatrix_equM( iPMatrix MDest, ui destHt, ui destLen,
                               ui firstRowInCol,  ui sampInCol,
                               ui firstColInRow,  ui sampInRow,
                               iPMatrix MSrce, ui srceHt, ui srceLen );

void  __vf OVCUAPI  MIcuequMblock(  iPMatrix MSub, ui subHt, ui subLen,
                          iPMatrix MSrce, ui srceHt,  ui srceLen,
                          ui firstRowInCol,  ui firstColInRow );

void  __vf OVCUAPI  MIcublock_equM( iPMatrix MDest, ui destHt, ui destLen,
                          ui firstRowInCol,  ui firstColInRow,
                          iPMatrix MSrce, ui srceHt, ui srceLen );

void  __vf OVCUAPI  MIcuequMblockT( iPMatrix MSub, ui subHt, ui subLen,
                          iPMatrix MSrce, ui srceHt, ui srceLen,
                          ui firstRowInCol,  ui firstColInRow );

void  __vf OVCUAPI  MIcublock_equMT( iPMatrix MDest, ui destHt, ui destLen,
                          ui firstRowInCol,  ui firstColInRow,
                          iPMatrix MSrce, ui srceHt, ui srceLen );


/*****   Extracting a single row or a single column or the diagonal  *****
 *       and storing it into a vector                                    */

void __vf OVCUAPI  MIcuRow_extract( iVector Y, iPMatrix MA, ui ht, ui len, ui iRow );
void __vf OVCUAPI  MIcuCol_extract( iVector Y, iPMatrix MA, ui ht, ui len, ui iCol );
void __vf OVCUAPI  MIcuDia_extract( iVector Y, iPMatrix MA, ui len );

/**********  Deleting or inserting a row or a column *****************/

void __vf OVCUAPI  MIcuRow_delete( iPMatrix MB, iPMatrix MA, ui htA, ui lenA, ui iRow );
void __vf OVCUAPI  MIcuCol_delete( iPMatrix MB, iPMatrix MA, ui htA, ui lenA, ui iCol );
void __vf OVCUAPI  MIcuRow_insert( iPMatrix MB, iPMatrix MA, ui htB, ui lenB, ui iRow, iVector X );
void __vf OVCUAPI  MIcuCol_insert( iPMatrix MB, iPMatrix MA, ui htB, ui lenB, ui iCol, iVector X );


/******  One-dimensional vector operations **********************
         performed along all rows or all columns simultaneously,
         or along the diagonal of a square matrix                */

void   __vf OVCUAPI  MIcuRows_max( iVector Y, iPMatrix MA, ui ht, ui len );
void   __vf OVCUAPI  MIcuCols_max( iVector Y, iPMatrix MA, ui ht, ui len );
int  __vf OVCUAPI  MIcuDia_max(  iPMatrix MA, ui len );
void   __vf OVCUAPI  MIcuRows_min( iVector Y, iPMatrix MA, ui ht, ui len );
void   __vf OVCUAPI  MIcuCols_min( iVector Y, iPMatrix MA, ui ht, ui len );
int  __vf OVCUAPI  MIcuDia_min(  iPMatrix MA, ui len );

void  __vf OVCUAPI  MIcuRows_rotate( iPMatrix MA, ui ht, ui len, ssize_t pos );
void  __vf OVCUAPI  MIcuCols_rotate( iPMatrix MA, ui ht, ui len, ssize_t pos );
void  __vf OVCUAPI  MIcuRows_rotate_buf( iPMatrix MA, ui ht, ui len, ssize_t pos, iPMatrix MBuf );
void  __vf OVCUAPI  MIcuCols_rotate_buf( iPMatrix MA, ui ht, ui len, ssize_t pos, iPMatrix MBuf );
void  __vf OVCUAPI  MIcuRows_reflect( iPMatrix MA, ui ht, ui len );
void  __vf OVCUAPI  MIcuCols_reflect( iPMatrix MA, ui ht, ui len );
void  __vf OVCUAPI  MIcuRows_rev( iPMatrix MA, ui ht, ui len );
void  __vf OVCUAPI  MIcuCols_rev( iPMatrix MA, ui ht, ui len );
void  __vf OVCUAPI  MIcuRows_distribution( uiPMatrix MAbund, iVector Limits, ui nBins, iPMatrix MX, ui ht, ui len, int mode );
void  __vf OVCUAPI  MIcuCols_distribution( uiPMatrix MAbund, iVector Limits, ui nBins, iPMatrix MX, ui ht, ui len, int mode );

/********  Operations involving two rows or two colums of one matrix  *****/

void   __vf OVCUAPI  MIcuRows_exchange( iPMatrix MA, ui ht, ui len, ui i1, ui i2 );
void   __vf OVCUAPI  MIcuCols_exchange( iPMatrix MA, ui ht, ui len, ui i1, ui i2 );


/***************  Transposing and rotating a matrix **********************/

void  __vf OVCUAPI  MIcutranspose( iPMatrix MTr, iPMatrix MA,  ui htTr, ui lenTr );
void  __vf OVCUAPI  MIcurotate90(  iPMatrix MRot, iPMatrix MA, ui htRot, ui lenRot );
#define     MIcurotate180( MRot, MA, htRot, lenRot )  VIcu_rev( MRot, MA, (htRot)*(lenRot) )
void  __vf OVCUAPI  MIcurotate270( iPMatrix MRot, iPMatrix MA, ui htRot, ui lenRot );

#ifdef __cplusplus
} // end of extern "C"
#endif
#endif  /*  __MISTD_H  */
