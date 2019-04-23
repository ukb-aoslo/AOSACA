/*  cudaVCDstd.h

  vector management functions:
  manipulations on whole arrays or vectors of data type dComplex
  (double-precision complex numbers)

  Copyright (c) 1996-2017 by OptiCode - Dr. Martin Sander Software Dev.
  All Rights Reserved.
*/

#ifndef __CUDAVCDSTD_H
#define __CUDAVCDSTD_H
#if !defined( __CUDAVECLIB_H )
#include <cudaVecLib.h>
#endif

/******************  cudaVCD_ functions: **********************************
	 act on vectors in CUDA device memory; 
	 scalar parameters and return values on host
******************  cusdVCD_ functions: **********************************
	 also act on vectors in CUDA device memory; 
	 scalar parameters and return values by address on device memory
************************************************************************/

#ifdef __cplusplus
extern "C" {
#endif

/*************************  Generation  **************************/

cdVector  __vf  cudaVCD_vector( ui size );   /* allocates a vector on device memory */
cdVector  __vf  cudaVCD_vector0( ui size );
/* The following functions allocate device-accessible, "pinned" memory on the host.
	This memory is mapped onto the device memory space. The resulting device address is returned.
	The vector can be accessed either by its host address "hostPtr" e.g., VCD_equC( hostPtr, size, C );
	or by its device address , e.g., cudaVCD_equC( devicePtr, size, C );     */
cdVector  __vf  cudaVCD_pinnedVector(  cdVector *hostPtr, ui size ); 
cdVector  __vf  cudaVCD_pinnedVector0( cdVector *hostPtr, ui size );

/***************  Addressing single vector elements ******************
*  Please note that you cannot use the X[n] syntax on device memory! */

dComplex * __vcuf OVCUAPI cudaVCD_Pelement( cdVector X, ui n );
void       __vcuf OVCUAPI cudaVCD_getElement( dComplex *y, cdVector X, ui n );
void       __vcuf OVCUAPI cusdVCD_getElement( dComplex *d_y, cdVector X, ui n );
void       __vcuf OVCUAPI cudaVCD_setElement( cdVector X, ui n, dComplex C );
void       __vcuf OVCUAPI cusdVCD_setElement( cdVector X, ui n, dComplex *d_C );
#if defined __cplusplus && defined _CMATH_CLASSDEFS
} // the following function cannot be extern "C", if dComplex is a class
#endif
dComplex   __vcuf OVCUAPI_ifNotClass cudaVCD_element( cdVector X, ui n );
#if defined __cplusplus && defined _CMATH_CLASSDEFS
extern "C" {
#endif

/*******************  Initialization **********************************/

overror_t  __vcuf OVCUAPI   cudaVCD_equ0( cdVector X, ui size );
overror_t  __vcuf OVCUAPI   cudaVCD_equ1( cdVector X, ui size );
overror_t  __vcuf OVCUAPI   cudaVCD_equm1( cdVector X, ui size );
overror_t  __vcuf OVCUAPI   cudaVCD_equC( cdVector X, ui size, dComplex C );
overror_t  __vcuf OVCUAPI   cusdVCD_equC( cdVector X, ui size, dComplex *C );
overror_t  __vcuf OVCUAPI   cudaVCD_equV( cdVector Y, cdVector X, ui size );  /* copies from device to device */
overror_t  __vcuf OVCUAPI   cudaVCD_equVhost( cdVector Y, cdVector X, ui size );  /* copies from host to device */
overror_t  __vcuf OVCUAPI   VCD_equVdevice( cdVector Y, cdVector X, ui size );  /* copies from device to host */
overror_t  __vcuf OVCUAPI   cudaVCDx_equV( cdVector Y, cdVector X, ui size, dComplex A, dComplex B );
overror_t  __vcuf OVCUAPI   cusdVCDx_equV( cdVector Y, cdVector X, ui size, dComplex *A, dComplex *B );
overror_t  __vcuf OVCUAPI   cudaVCD_ramp( cdVector X, ui size, dComplex Start, dComplex Rise );
overror_t  __vcuf OVCUAPI   cusdVCD_ramp( cdVector X, ui size, dComplex *Start, dComplex *Rise );

/******  Linear Congruential random generator with Bays-Durham shuffle:  ***********
  Random series is generated on the CPU.
  state must be stored in host memory!
  seed!=0 --> initialization of state. seed==0 --> continue series from previous call with the same state. */
overror_t  __vcuf OVCUAPI  cudaVCD_randomLC( cdVector X, ui size, long seed, dComplex MinVal, dComplex MaxVal, V_RANDOMLCSTATE *state );
overror_t  __vcuf OVCUAPI  cusdVCD_randomLC( cdVector X, ui size, long seed, dComplex *MinVal, dComplex *MaxVal, V_RANDOMLCSTATE *state );
/**  simplified version: Series cannot be made continuous across calls: */
overror_t  __vcuf OVCUAPI  cudaVCD_random( cdVector X, ui size, long seed, dComplex MinVal, dComplex MaxVal );
overror_t  __vcuf OVCUAPI  cusdVCD_random( cdVector X, ui size, long seed, dComplex *MinVal, dComplex *MaxVal );

overror_t  __vcuf OVCUAPI   cudaVD_CtoReIm( dVector Re, dVector Im, cdVector X, ui size );
overror_t  __vcuf OVCUAPI   cudaVD_ReImtoC( cdVector Y, dVector Re, dVector Im, ui size );
overror_t  __vcuf OVCUAPI   cudaVD_CtoRe( dVector Re, cdVector X, ui size );
overror_t  __vcuf OVCUAPI   cudaVD_RetoC( cdVector Y, dVector Re, ui size );
overror_t  __vcuf OVCUAPI   cudaVD_CtoIm( dVector Im, cdVector X, ui size );
overror_t  __vcuf OVCUAPI   cudaVD_ImtoC( cdVector Y, dVector Im, ui size );
overror_t  __vcuf OVCUAPI   cudaVD_CtoPolar( dVector Mag, dVector Arg, cdVector X, ui size );
overror_t  __vcuf OVCUAPI   cudaVD_PolartoC( cdVector Y, dVector Mag, dVector Arg, ui size );
overror_t  __vcuf OVCUAPI   cudaVD_CtoNorm( dVector Norm, cdVector X, ui size );
overror_t  __vcuf OVCUAPI   cudaVD_CtoAbs( dVector Abs, cdVector X, ui size );
overror_t  __vcuf OVCUAPI   cudaVD_CtoArg( dVector Arg, cdVector X, ui size );
overror_t  __vcuf OVCUAPI   cudaVCD_normtoC( cdVector Norm, cdVector X, ui size );
#define     cudaVCD_abs          cudaVD_CtoAbs
#define     cudaVCD_real         cudaVD_CtoRe
#define     cudaVCD_imag         cudaVD_CtoIm
#define     cudaVCD_arg          cudaVD_CtoArg
#define     cudaVCD_norm         cudaVD_CtoNorm
#define     cudaVCD_polar        cudaVD_PolartoC
#define     cudaVCD_complex      cudaVD_ReImtoC


/****************  Data-type overror_terconversions  ***************************/

overror_t  __vcuf OVCUAPI   cudaV_CFtoCD( cdVector Y, cfVector X, ui size );
overror_t  __vcuf OVCUAPI   cudaV_CDtoCF( cfVector Y, cdVector X, ui size );


/****************  Index-oriented manipulations ***********************/

overror_t  __vcuf OVCUAPI   cudaVCD_delete( cdVector X, ui size, ui pos );
overror_t  __vcuf OVCUAPI   cudaVCD_insert( cdVector X, ui size, ui pos, dComplex C );
overror_t  __vcuf OVCUAPI   cusdVCD_insert( cdVector X, ui size, ui pos, dComplex *C );

overror_t  __vcuf OVCUAPI   cudaVCD_reflect( cdVector X, ui size );
overror_t  __vcuf OVCUAPI   cudaVCD_rev( cdVector Y, cdVector X, ui size );
overror_t  __vcuf OVCUAPI   cudaVCD_rotate( cdVector Y, cdVector X, ui size, ssize_t pos );
overror_t  __vcuf OVCUAPI   cudaVCD_rotate_buf( cdVector Y, cdVector X, ui size, ssize_t pos, cdVector Buf );
overror_t  __vcuf OVCUAPI   cudaVCD_indpick( cdVector Y, uiVector Ind, ui sizey, cdVector X );
overror_t  __vcuf OVCUAPI   cudaVCD_indput(  cdVector Y, cdVector X, uiVector Ind, ui sizex );
overror_t  __vcuf OVCUAPI   cudaVCD_subvector( cdVector Y, ui sizey, cdVector X, ssize_t samp );


/***************** Functions of a sub-set of elements  ********************/

overror_t  __vcuf OVCUAPI   cudaVCD_subvector_equC(  cdVector Y, ui subsiz, ui samp, dComplex C );
overror_t  __vcuf OVCUAPI   cusdVCD_subvector_equC(  cdVector Y, ui subsiz, ui samp, dComplex *C );
overror_t  __vcuf OVCUAPI   cudaVCD_subvector_equV(  cdVector Y, ui subsiz, ui samp, cdVector X );


/**************** One-Dimensional Vector Operations ***********************/

overror_t    __vcuf OVCUAPI   cudaVCD_absmax(  double *h_RetVal, cdVector X, ui size );
overror_t    __vcuf OVCUAPI   cudaVCD_absmin(  double *h_RetVal, cdVector X, ui size );
overror_t    __vcuf OVCUAPI   cudaVCD_absmaxind( double *h_RetVal, ui *pos, cdVector X, ui size );
overror_t    __vcuf OVCUAPI   cudaVCD_absminind( double *h_RetVal, ui *pos, cdVector X, ui size );

overror_t  __vcuf OVCUAPI   cudaVCD_maxReIm(     dComplex  *h_RetVal, cdVector X, ui size );
overror_t  __vcuf OVCUAPI   cudaVCD_minReIm(     dComplex  *h_RetVal, cdVector X, ui size );
overror_t  __vcuf OVCUAPI   cudaVCD_absmaxReIm(  dComplex  *h_RetVal, cdVector X, ui size );
overror_t  __vcuf OVCUAPI   cudaVCD_absminReIm(  dComplex  *h_RetVal, cdVector X, ui size );
overror_t  __vcuf OVCUAPI   cudaVCD_cabsmax(  dComplex  *h_RetVal, cdVector X, ui size );
overror_t  __vcuf OVCUAPI   cudaVCD_cabsmin(  dComplex  *h_RetVal, cdVector X, ui size );
overror_t  __vcuf OVCUAPI   cudaVCD_sabsmax(  dComplex  *h_RetVal, cdVector X, ui size );
overror_t  __vcuf OVCUAPI   cudaVCD_sabsmin(  dComplex  *h_RetVal, cdVector X, ui size );
overror_t  __vcuf OVCUAPI   cudaVCD_sum(     dComplex  *h_RetVal, cdVector X, ui size );
overror_t  __vcuf OVCUAPI   cudaVCD_prod(    dComplex  *h_RetVal, cdVector X, ui size );
overror_t  __vcuf OVCUAPI   cudaVCD_mean(   dComplex  *h_RetVal, cdVector X, ui size );
overror_t  __vcuf OVCUAPI   cudaVCD_meanwW( dComplex  *h_RetVal, cdVector X, dVector Wt, ui size );
overror_t  __vcuf OVCUAPI   cudaVCD_scalprod( dComplex  *h_RetVal, cdVector X, cdVector Y, ui size );

overror_t __vcuf OVCUAPI   cusdVCD_absmax(  double *d_RetVal, cdVector X, ui size );
overror_t __vcuf OVCUAPI   cusdVCD_absmin(  double *d_RetVal, cdVector X, ui size );
overror_t __vcuf OVCUAPI   cusdVCD_absmaxind( double *d_RetVal, ui *pos, cdVector X, ui size );
overror_t __vcuf OVCUAPI   cusdVCD_absminind( double *d_RetVal, ui *pos, cdVector X, ui size );
overror_t __vcuf OVCUAPI   cusdVCD_maxReIm(  dComplex *d_RetVal, cdVector X, ui size );
overror_t __vcuf OVCUAPI   cusdVCD_minReIm(  dComplex *d_RetVal, cdVector X, ui size );
overror_t __vcuf OVCUAPI   cusdVCD_absmaxReIm( dComplex *d_RetVal, cdVector X, ui size );
overror_t __vcuf OVCUAPI   cusdVCD_absminReIm( dComplex *d_RetVal, cdVector X, ui size );
overror_t __vcuf OVCUAPI   cusdVCD_cabsmax(  dComplex *d_RetVal, cdVector X, ui size );
overror_t __vcuf OVCUAPI   cusdVCD_cabsmin(  dComplex *d_RetVal, cdVector X, ui size );
overror_t __vcuf OVCUAPI   cusdVCD_sabsmax(  dComplex *d_RetVal, cdVector X, ui size );
overror_t __vcuf OVCUAPI   cusdVCD_sabsmin(  dComplex *d_RetVal, cdVector X, ui size );
overror_t __vcuf OVCUAPI   cusdVCD_sum(     dComplex *d_RetVal, cdVector X, ui size );
overror_t __vcuf OVCUAPI   cusdVCD_prod(    dComplex *d_RetVal, cdVector X, ui size );
overror_t __vcuf OVCUAPI   cusdVCD_mean(   dComplex *d_RetVal, cdVector X, ui size );
overror_t __vcuf OVCUAPI   cusdVCD_meanwW( dComplex *d_RetVal, cdVector X, dVector Wt, ui size );
overror_t __vcuf OVCUAPI   cusdVCD_scalprod( dComplex *d_RetVal, cdVector X, cdVector Y, ui size );

overror_t __vcuf OVCUAPI  cudaVCD_runsum(  cdVector Y, cdVector X, ui size );
overror_t __vcuf OVCUAPI  cudaVCD_runprod( cdVector Y, cdVector X, ui size );

int     __vcuf OVCUAPI   cudaVCD_iselementC( cdVector Tab, ui size, dComplex C );
int     __vcuf OVCUAPI   cusdVCD_iselementC( cdVector Tab, ui size, dComplex *C );
overror_t __vcuf OVCUAPI cudaVCD_iselementV( ui *h_nFound, cdVector Y, cdVector X, ui sizex, cdVector Tab, ui sizetab );

/*********  Fourier Transforms, Convolutions, Filtering  ****************/

overror_t  __vcuf OVCUAPI   cudaVCD_FFT( cdVector Y, cdVector X, ui size, int dir );
overror_t  __vcuf OVCUAPI   cudaVCD_2FFT( cdVector Y1, cdVector Y2, cdVector X1, cdVector X2, ui size, int dir );
overror_t  __vcuf OVCUAPI   cudaVCD_filter( cdVector Y, cdVector X, cdVector Flt, ui size );

/***************************  Input and Output *****************************
	The input/output functions involve memory transfers from device
	to host memory or vice versa. The generic cudaVCD_input/output functions
	allocate their own host buffers, whereas the cudaVCD_xxx_buf functions
	take a user-supplied buffer h_Wk and are much more efficient.          */

overror_t  __vf    cudaVCD_fprint( FILE *stream, cdVector X, ui size, unsigned nperline, unsigned linewidth );
overror_t  __vf    cudaVCD_cprint( cdVector X, ui size, unsigned nperline );
#define       cudaVCD_print( x, sz, npl )  cudaVCD_fprint( stdout, x, sz, npl, 80 )
overror_t  __vf    cudaVCD_fprint_buf( FILE *stream, cdVector d_X, ui size, unsigned nperline, unsigned linewidth, cdVector h_Wk );
overror_t  __vf    cudaVCD_cprint_buf( cdVector d_X, ui size, unsigned nperline, cdVector h_Wk );
#define       cudaVCD_print_buf( d_x, sz, npl, h_Wk )  cudaVCD_fprint_buf( stdout, d_x, sz, npl, 80, h_Wk )
 /*  cudaVCD_print, cudaVCD_cprint are usable only for console applications!  */
overror_t  __vf    cudaVCD_write( FILE *stream, cdVector X, ui size  );
overror_t  __vf    cudaVCD_write_buf( FILE *stream, cdVector d_X, ui size, cdVector h_Wk );
                     /* cudaVCD_write, cudaVCD_read in ascii format */
#if !((defined __BORLANDC__) && (__BORLANDC__ < 0x710))
		/* modern compiler versions:  */
	overror_t  __vf    cudaVCD_read( cdVector X, ui size, FILE *stream );
	overror_t  __vf    cudaVCD_read_buf( cdVector d_X, ui size, FILE *stream, cdVector h_Wk );
#else /* older Borland compiler versions need separate implementation */
	overror_t  __vf    cudaVCD_read1( cdVector X, ui size, FILE *stream );
	overror_t  __vf    cudaVCD_read1_buf( cdVector d_X, ui size, FILE *stream, cdVector h_Wk );
	#define cudaVCD_read     cudaVCD_read1
	#define cudaVCD_read_buf cudaVCD_read1_buf
#endif
overror_t  __vf    cudaVCD_store( FILE *stream, cdVector X, ui size );
overror_t  __vf    cudaVCD_recall( cdVector X, ui size, FILE *stream );
overror_t  __vf    cudaVCD_store_buf( FILE *stream, cdVector d_X, ui size, cdVector h_Wk );
overror_t  __vf    cudaVCD_recall_buf( cdVector d_X, ui size, FILE *stream, cdVector h_Wk );
                     /* cudaVCD_store, cudaVCD_recall in binary format */


#ifdef __cplusplus
}  // end of extern "C"
#endif


/******************  VCDcu_ functions: **********************************
	act on host memory, using the CUDA device for processing
************************************************************************/

#ifdef __cplusplus
extern "C" {
#endif

/*******************  Initialization **********************************/

void  __vcuf OVCUAPI   VCDcu_equ0( cdVector X, ui size );
void  __vcuf OVCUAPI   VCDcu_equ1( cdVector X, ui size );
void  __vcuf OVCUAPI   VCDcu_equm1( cdVector X, ui size );
void  __vcuf OVCUAPI   VCDcu_equC( cdVector X, ui size, dComplex C );
void  __vcuf OVCUAPI   VCDcu_equV( cdVector Y, cdVector X, ui size );  /* copies from device to device */
void  __vcuf OVCUAPI   VCDxcu_equV( cdVector Y, cdVector X, ui size, dComplex A, dComplex B );
void  __vcuf OVCUAPI   VCDcu_ramp( cdVector X, ui size, dComplex Start, dComplex Rise );
/* no Vcu_random functions: random generation runs on CPU anyway */

void  __vcuf OVCUAPI   VDcu_CtoReIm( dVector Re, dVector Im, cdVector X, ui size );
void  __vcuf OVCUAPI   VDcu_ReImtoC( cdVector Y, dVector Re, dVector Im, ui size );
void  __vcuf OVCUAPI   VDcu_CtoRe( dVector Re, cdVector X, ui size );
void  __vcuf OVCUAPI   VDcu_RetoC( cdVector Y, dVector Re, ui size );
void  __vcuf OVCUAPI   VDcu_CtoIm( dVector Im, cdVector X, ui size );
void  __vcuf OVCUAPI   VDcu_ImtoC( cdVector Y, dVector Im, ui size );
void  __vcuf OVCUAPI   VDcu_CtoPolar( dVector Mag, dVector Arg, cdVector X, ui size );
void  __vcuf OVCUAPI   VDcu_PolartoC( cdVector Y, dVector Mag, dVector Arg, ui size );
void  __vcuf OVCUAPI   VDcu_CtoNorm( dVector Norm, cdVector X, ui size );
void  __vcuf OVCUAPI   VDcu_CtoAbs( dVector Abs, cdVector X, ui size );
void  __vcuf OVCUAPI   VDcu_CtoArg( dVector Arg, cdVector X, ui size );
void  __vcuf OVCUAPI   VCDcu_normtoC( cdVector Norm, cdVector X, ui size );
#define     VCDcu_real         VDcu_CtoRe
#define     VCDcu_imag         VDcu_CtoIm
#define     VCDcu_arg          VDcu_CtoArg
#define     VCDcu_norm         VDcu_CtoNorm
#define     VCDcu_polar        VDcu_PolartoC
#define     VCDcu_complex      VDcu_ReImtoC


/****************  Data-type interconversions  ***************************/

void  __vcuf OVCUAPI   Vcu_CFtoCD( cdVector Y, cfVector X, ui size );
void  __vcuf OVCUAPI   Vcu_CDtoCF( cfVector Y, cdVector X, ui size );


/****************  Index-oriented manipulations ***********************/

void  __vcuf OVCUAPI   VCDcu_delete( cdVector X, ui size, ui pos );
void  __vcuf OVCUAPI   VCDcu_insert( cdVector X, ui size, ui pos, dComplex C );
void  __vcuf OVCUAPI   VCDcu_reflect( cdVector X, ui size );
void  __vcuf OVCUAPI   VCDcu_rev( cdVector Y, cdVector X, ui size );
void  __vcuf OVCUAPI   VCDcu_rotate( cdVector Y, cdVector X, ui size, ssize_t pos );
void  __vcuf OVCUAPI   VCDcu_rotate_buf( cdVector Y, cdVector X, ui size, ssize_t pos, cdVector Buf );
  /* no V?cu_indpick, V?cu_indput possible! */
void  __vcuf OVCUAPI   VCDcu_subvector( cdVector Y, ui sizey, cdVector X, ssize_t samp );


/***************** Functions of a sub-set of elements  ********************/

void  __vcuf OVCUAPI   VCDcu_subvector_equC(  cdVector Y, ui subsiz, ui samp, dComplex C );
void  __vcuf OVCUAPI   VCDcu_subvector_equV(  cdVector Y, ui subsiz, ui samp, cdVector X );


/**************** One-Dimensional Vector Operations ***********************/

double    __vcuf OVCUAPI   VCDcu_absmax(  cdVector X, ui size );
double    __vcuf OVCUAPI   VCDcu_absmin(  cdVector X, ui size );
double    __vcuf OVCUAPI   VCDcu_absmaxind( ui *pos, cdVector X, ui size );
double    __vcuf OVCUAPI   VCDcu_absminind( ui *pos, cdVector X, ui size );
#if defined __cplusplus && defined _CMATH_CLASSDEFS
} // the following functions cannot be extern "C", if dComplex is a class
#endif
dComplex  __vcuf OVCUAPI_ifNotClass   VCDcu_maxReIm(     cdVector X, ui size );
dComplex  __vcuf OVCUAPI_ifNotClass   VCDcu_minReIm(     cdVector X, ui size );
dComplex  __vcuf OVCUAPI_ifNotClass   VCDcu_absmaxReIm(  cdVector X, ui size );
dComplex  __vcuf OVCUAPI_ifNotClass   VCDcu_absminReIm(  cdVector X, ui size );
dComplex  __vcuf OVCUAPI_ifNotClass   VCDcu_cabsmax(  cdVector X, ui size );
dComplex  __vcuf OVCUAPI_ifNotClass   VCDcu_cabsmin(  cdVector X, ui size );
dComplex  __vcuf OVCUAPI_ifNotClass   VCDcu_sabsmax(  cdVector X, ui size );
dComplex  __vcuf OVCUAPI_ifNotClass   VCDcu_sabsmin(  cdVector X, ui size );
dComplex  __vcuf OVCUAPI_ifNotClass   VCDcu_sum(     cdVector X, ui size );
dComplex  __vcuf OVCUAPI_ifNotClass   VCDcu_prod(    cdVector X, ui size );
dComplex  __vcuf OVCUAPI_ifNotClass   VCDcu_mean(   cdVector X, ui size );
dComplex  __vcuf OVCUAPI_ifNotClass   VCDcu_meanwW( cdVector X, dVector Wt, ui size );
dComplex  __vcuf OVCUAPI_ifNotClass   VCDcu_scalprod( cdVector X, cdVector Y, ui size );
#if defined __cplusplus && defined _CMATH_CLASSDEFS
extern "C" {
#endif

void      __vcuf OVCUAPI   VCDcu_runsum(  cdVector Y, cdVector X, ui size );
void      __vcuf OVCUAPI   VCDcu_runprod( cdVector Y, cdVector X, ui size );
int       __vcuf OVCUAPI   VCDcu_iselementC( cdVector Tab, ui size, dComplex C );
ui        __vcuf OVCUAPI   VCDcu_iselementV( cdVector Y, cdVector X, ui sizex, cdVector Tab, ui sizetab );

/*********  Fourier Transforms, Convolutions, Filtering  ****************/

void  __vcuf OVCUAPI   VCDcu_FFT( cdVector Y, cdVector X, ui size, int dir );
void  __vcuf OVCUAPI   VCDcu_2FFT( cdVector Y1, cdVector Y2, cdVector X1, cdVector X2, ui size, int dir );
void  __vcuf OVCUAPI   VCDcu_filter( cdVector Y, cdVector X, cdVector Flt, ui size );

#ifdef __cplusplus
}  // end of extern "C"
#endif

#endif /*  __CUDAVCDSTD_H */
