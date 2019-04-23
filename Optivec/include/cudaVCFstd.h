/*  cudaVCFstd.h

  vector management functions:
  manipulations on whole arrays or vectors of data type fComplex
  (float-precision complex numbers)

  Copyright (c) 1996-2017 by OptiCode - Dr. Martin Sander Software Dev.
  All Rights Reserved.
*/

#ifndef __CUDAVCFSTD_H
#define __CUDAVCFSTD_H
#if !defined( __CUDAVECLIB_H )
#include <cudaVecLib.h>
#endif

/******************  cudaVCF_ functions: **********************************
	 act on vectors in CUDA device memory; 
	 scalar parameters and return values on host
******************  cusdVCF_ functions: **********************************
	 also act on vectors in CUDA device memory; 
	 scalar parameters and return values by address on device memory
************************************************************************/

#ifdef __cplusplus
extern "C" {
#endif

/*************************  Generation  **************************/

cfVector  __vf  cudaVCF_vector( ui size );   /* allocates a vector on device memory */
cfVector  __vf  cudaVCF_vector0( ui size );
/* The following functions allocate device-accessible, "pinned" memory on the host.
	This memory is mapped onto the device memory space. The resulting device address is returned.
	The vector can be accessed either by its host address "hostPtr" e.g., VF_equC( hostPtr, size, C );
	or by its device address , e.g., cudaVCF_equC( devicePtr, size, C );     */
cfVector  __vf  cudaVCF_pinnedVector(  cfVector *hostPtr, ui size ); 
cfVector  __vf  cudaVCF_pinnedVector0( cfVector *hostPtr, ui size );

/***************  Addressing single vector elements ******************
*  Please note that you cannot use the X[n] syntax on device memory! */

fComplex * __vcuf OVCUAPI cudaVCF_Pelement( cfVector X, ui n );
#if defined __cplusplus && defined _CMATH_CLASSDEFS && defined __BORLANDC__ && defined _WIN64
} // for C++Builder on Win64, the following functions cannot be extern "C", if fComplex is a class
#endif
void  __vcuf OVCUAPI_ifNotBC64Class cudaVCF_setElement( cfVector X, ui n, fComplex C );
#if defined __cplusplus && defined _CMATH_CLASSDEFS && defined __BORLANDC__ && defined _WIN64
extern "C" {
#endif
void  __vcuf OVCUAPI cusdVCF_setElement( cfVector X, ui n, fComplex *d_C );
#if defined __cplusplus && defined _CMATH_CLASSDEFS
} // the following function cannot be extern "C", if fComplex is a class
#endif
fComplex   __vcuf OVCUAPI_ifNotClass cudaVCF_element( cfVector X, ui n );
#if defined __cplusplus && defined _CMATH_CLASSDEFS
extern "C" {
#endif
void  __vcuf OVCUAPI cudaVCF_getElement( fComplex *y, cfVector X, ui n );
void  __vcuf OVCUAPI cusdVCF_getElement( fComplex *d_y, cfVector X, ui n );

/*******************  Initialization **********************************/

overror_t  __vcuf OVCUAPI   cudaVCF_equ0( cfVector X, ui size );
overror_t  __vcuf OVCUAPI   cudaVCF_equ1( cfVector X, ui size );
overror_t  __vcuf OVCUAPI   cudaVCF_equm1( cfVector X, ui size );
overror_t  __vcuf OVCUAPI   cudaVCF_equV( cfVector Y, cfVector X, ui size );  /* copies from device to device */
overror_t  __vcuf OVCUAPI   cudaVCF_equVhost( cfVector Y, cfVector X, ui size );  /* copies from host to device */
overror_t  __vcuf OVCUAPI   VCF_equVdevice( cfVector Y, cfVector X, ui size );  /* copies from device to host */
#if defined __cplusplus && defined _CMATH_CLASSDEFS && defined __BORLANDC__ && defined _WIN64
} // for C++Builder on Win64, the following functions cannot be extern "C", if fComplex is a class
#endif
overror_t  __vcuf OVCUAPI   cudaVCF_equC( cfVector X, ui size, fComplex C );
overror_t  __vcuf OVCUAPI   cusdVCF_equC( cfVector X, ui size, fComplex *C );
overror_t  __vcuf OVCUAPI   cudaVCFx_equV( cfVector Y, cfVector X, ui size, fComplex A, fComplex B );
overror_t  __vcuf OVCUAPI   cudaVCF_ramp( cfVector X, ui size, fComplex Start, fComplex Rise );
#if defined __cplusplus && defined _CMATH_CLASSDEFS && defined __BORLANDC__ && defined _WIN64
extern "C" {
#endif
overror_t  __vcuf OVCUAPI   cusdVCFx_equV( cfVector Y, cfVector X, ui size, fComplex *A, fComplex *B );
overror_t  __vcuf OVCUAPI   cusdVCF_ramp( cfVector X, ui size, fComplex *Start, fComplex *Rise );

/******  Linear Congruential random generator with Bays-Durham shuffle:  ***********
  Random series is generated on the CPU.
  state must be stored in host memory!
  seed!=0 --> initialization of state. seed==0 --> continue series from previous call with the same state. */
#if defined __cplusplus && defined _CMATH_CLASSDEFS && defined __BORLANDC__ && defined _WIN64
} // for C++Builder on Win64, the following functions cannot be extern "C", if fComplex is a class
#endif
overror_t  __vcuf OVCUAPI  cudaVCF_randomLC( cfVector X, ui size, long seed, fComplex MinVal, fComplex MaxVal, V_RANDOMLCSTATE *state );
/**  simplified version: Series cannot be made continuous across calls: */
overror_t  __vcuf OVCUAPI  cudaVCF_random( cfVector X, ui size, long seed, fComplex MinVal, fComplex MaxVal );
#if defined __cplusplus && defined _CMATH_CLASSDEFS && defined __BORLANDC__ && defined _WIN64
extern "C" {
#endif
overror_t  __vcuf OVCUAPI  cusdVCF_randomLC( cfVector X, ui size, long seed, fComplex *MinVal, fComplex *MaxVal, V_RANDOMLCSTATE *state );
overror_t  __vcuf OVCUAPI  cusdVCF_random( cfVector X, ui size, long seed, fComplex *MinVal, fComplex *MaxVal );

overror_t  __vcuf OVCUAPI   cudaVF_CtoReIm( fVector Re, fVector Im, cfVector X, ui size );
overror_t  __vcuf OVCUAPI   cudaVF_ReImtoC( cfVector Y, fVector Re, fVector Im, ui size );
overror_t  __vcuf OVCUAPI   cudaVF_CtoRe( fVector Re, cfVector X, ui size );
overror_t  __vcuf OVCUAPI   cudaVF_RetoC( cfVector Y, fVector Re, ui size );
overror_t  __vcuf OVCUAPI   cudaVF_CtoIm( fVector Im, cfVector X, ui size );
overror_t  __vcuf OVCUAPI   cudaVF_ImtoC( cfVector Y, fVector Im, ui size );
overror_t  __vcuf OVCUAPI   cudaVF_CtoPolar( fVector Mag, fVector Arg, cfVector X, ui size );
overror_t  __vcuf OVCUAPI   cudaVF_PolartoC( cfVector Y, fVector Mag, fVector Arg, ui size );
overror_t  __vcuf OVCUAPI   cudaVF_CtoNorm( fVector Norm, cfVector X, ui size );
overror_t  __vcuf OVCUAPI   cudaVF_CtoAbs( fVector Abs, cfVector X, ui size );
overror_t  __vcuf OVCUAPI   cudaVF_CtoArg( fVector Arg, cfVector X, ui size );
overror_t  __vcuf OVCUAPI   cudaVCF_normtoC( cfVector Norm, cfVector X, ui size );
#define     cudaVCF_abs          cudaVF_CtoAbs
#define     cudaVCF_real         cudaVF_CtoRe
#define     cudaVCF_imag         cudaVF_CtoIm
#define     cudaVCF_arg          cudaVF_CtoArg
#define     cudaVCF_norm         cudaVF_CtoNorm
#define     cudaVCF_polar        cudaVF_PolartoC
#define     cudaVCF_complex      cudaVF_ReImtoC


/****************  Data-type overror_terconversions  ***************************/

overror_t  __vcuf OVCUAPI   cudaV_CFtoCD( cdVector Y, cfVector X, ui size );
overror_t  __vcuf OVCUAPI   cudaV_CDtoCF( cfVector Y, cdVector X, ui size );


/****************  Index-oriented manipulations ***********************/

overror_t  __vcuf OVCUAPI   cudaVCF_delete( cfVector X, ui size, ui pos );
overror_t  __vcuf OVCUAPI   cusdVCF_insert( cfVector X, ui size, ui pos, fComplex *C );
#if defined __cplusplus && defined _CMATH_CLASSDEFS && defined __BORLANDC__ && defined _WIN64
} // for C++Builder on Win64, the following functions cannot be extern "C", if fComplex is a class
#endif
overror_t  __vcuf OVCUAPI_ifNotBC64Class   cudaVCF_insert( cfVector X, ui size, ui pos, fComplex C );
#if defined __cplusplus && defined _CMATH_CLASSDEFS && defined __BORLANDC__ && defined _WIN64
extern "C" {
#endif

overror_t  __vcuf OVCUAPI   cudaVCF_reflect( cfVector X, ui size );
overror_t  __vcuf OVCUAPI   cudaVCF_rev( cfVector Y, cfVector X, ui size );
overror_t  __vcuf OVCUAPI   cudaVCF_rotate( cfVector Y, cfVector X, ui size, ssize_t pos );
overror_t  __vcuf OVCUAPI   cudaVCF_rotate_buf( cfVector Y, cfVector X, ui size, ssize_t pos, cfVector Buf );
overror_t  __vcuf OVCUAPI   cudaVCF_indpick( cfVector Y, uiVector Ind, ui sizey, cfVector X );
overror_t  __vcuf OVCUAPI   cudaVCF_indput(  cfVector Y, cfVector X, uiVector Ind, ui sizex );
overror_t  __vcuf OVCUAPI   cudaVCF_subvector( cfVector Y, ui sizey, cfVector X, ssize_t samp );


/***************** Functions of a sub-set of elements  ********************/

#if defined __cplusplus && defined _CMATH_CLASSDEFS && defined __BORLANDC__ && defined _WIN64
} // for C++Builder on Win64, the following functions cannot be extern "C", if fComplex is a class
#endif
overror_t  __vcuf OVCUAPI_ifNotBC64Class   cudaVCF_subvector_equC(  cfVector Y, ui subsiz, ui samp, fComplex C );
#if defined __cplusplus && defined _CMATH_CLASSDEFS && defined __BORLANDC__ && defined _WIN64
extern "C" {
#endif
overror_t  __vcuf OVCUAPI   cusdVCF_subvector_equC(  cfVector Y, ui subsiz, ui samp, fComplex *C );
overror_t  __vcuf OVCUAPI   cudaVCF_subvector_equV(  cfVector Y, ui subsiz, ui samp, cfVector X );


/**************** One-Dimensional Vector Operations ***********************/

overror_t    __vcuf OVCUAPI   cudaVCF_absmax(  float *h_RetVal, cfVector X, ui size );
overror_t    __vcuf OVCUAPI   cudaVCF_absmin(  float *h_RetVal, cfVector X, ui size );
overror_t    __vcuf OVCUAPI   cudaVCF_absmaxind( float *h_RetVal, ui *pos, cfVector X, ui size );
overror_t    __vcuf OVCUAPI   cudaVCF_absminind( float *h_RetVal, ui *pos, cfVector X, ui size );

overror_t  __vcuf OVCUAPI   cudaVCF_maxReIm(     fComplex  *h_RetVal, cfVector X, ui size );
overror_t  __vcuf OVCUAPI   cudaVCF_minReIm(     fComplex  *h_RetVal, cfVector X, ui size );
overror_t  __vcuf OVCUAPI   cudaVCF_absmaxReIm(  fComplex  *h_RetVal, cfVector X, ui size );
overror_t  __vcuf OVCUAPI   cudaVCF_absminReIm(  fComplex  *h_RetVal, cfVector X, ui size );
overror_t  __vcuf OVCUAPI   cudaVCF_cabsmax(  fComplex  *h_RetVal, cfVector X, ui size );
overror_t  __vcuf OVCUAPI   cudaVCF_cabsmin(  fComplex  *h_RetVal, cfVector X, ui size );
overror_t  __vcuf OVCUAPI   cudaVCF_sabsmax(  fComplex  *h_RetVal, cfVector X, ui size );
overror_t  __vcuf OVCUAPI   cudaVCF_sabsmin(  fComplex  *h_RetVal, cfVector X, ui size );
overror_t  __vcuf OVCUAPI   cudaVCF_sum(     fComplex  *h_RetVal, cfVector X, ui size );
overror_t  __vcuf OVCUAPI   cudaVCF_prod(    fComplex  *h_RetVal, cfVector X, ui size );
overror_t  __vcuf OVCUAPI   cudaVCF_mean(   fComplex  *h_RetVal, cfVector X, ui size );
overror_t  __vcuf OVCUAPI   cudaVCF_meanwW( fComplex  *h_RetVal, cfVector X, fVector Wt, ui size );
overror_t  __vcuf OVCUAPI   cudaVCF_scalprod( fComplex  *h_RetVal, cfVector X, cfVector Y, ui size );

overror_t __vcuf OVCUAPI   cusdVCF_absmax(  float *d_RetVal, cfVector X, ui size );
overror_t __vcuf OVCUAPI   cusdVCF_absmin(  float *d_RetVal, cfVector X, ui size );
overror_t __vcuf OVCUAPI   cusdVCF_absmaxind( float *d_RetVal, ui *pos, cfVector X, ui size );
overror_t __vcuf OVCUAPI   cusdVCF_absminind( float *d_RetVal, ui *pos, cfVector X, ui size );
overror_t __vcuf OVCUAPI   cusdVCF_maxReIm(  fComplex *d_RetVal, cfVector X, ui size );
overror_t __vcuf OVCUAPI   cusdVCF_minReIm(  fComplex *d_RetVal, cfVector X, ui size );
overror_t __vcuf OVCUAPI   cusdVCF_absmaxReIm( fComplex *d_RetVal, cfVector X, ui size );
overror_t __vcuf OVCUAPI   cusdVCF_absminReIm( fComplex *d_RetVal, cfVector X, ui size );
overror_t __vcuf OVCUAPI   cusdVCF_cabsmax(  fComplex *d_RetVal, cfVector X, ui size );
overror_t __vcuf OVCUAPI   cusdVCF_cabsmin(  fComplex *d_RetVal, cfVector X, ui size );
overror_t __vcuf OVCUAPI   cusdVCF_sabsmax(  fComplex *d_RetVal, cfVector X, ui size );
overror_t __vcuf OVCUAPI   cusdVCF_sabsmin(  fComplex *d_RetVal, cfVector X, ui size );
overror_t __vcuf OVCUAPI   cusdVCF_sum(     fComplex *d_RetVal, cfVector X, ui size );
overror_t __vcuf OVCUAPI   cusdVCF_prod(    fComplex *d_RetVal, cfVector X, ui size );
overror_t __vcuf OVCUAPI   cusdVCF_mean(   fComplex *d_RetVal, cfVector X, ui size );
overror_t __vcuf OVCUAPI   cusdVCF_meanwW( fComplex *d_RetVal, cfVector X, fVector Wt, ui size );
overror_t __vcuf OVCUAPI   cusdVCF_scalprod( fComplex *d_RetVal, cfVector X, cfVector Y, ui size );

overror_t __vcuf OVCUAPI  cudaVCF_runsum(  cfVector Y, cfVector X, ui size );
overror_t __vcuf OVCUAPI  cudaVCF_runprod( cfVector Y, cfVector X, ui size );

#if defined __cplusplus && defined _CMATH_CLASSDEFS && defined __BORLANDC__ && defined _WIN64
} // for C++Builder on Win64, the following functions cannot be extern "C", if fComplex is a class
#endif
int    __vcuf OVCUAPI_ifNotBC64Class   cudaVCF_iselementC( cfVector Tab, ui size, fComplex C );
#if defined __cplusplus && defined _CMATH_CLASSDEFS && defined __BORLANDC__ && defined _WIN64
extern "C" {
#endif
int       __vcuf OVCUAPI cusdVCF_iselementC( cfVector Tab, ui size, fComplex *C );
overror_t __vcuf OVCUAPI cudaVCF_iselementV( ui *h_nFound, cfVector Y, cfVector X, ui sizex, cfVector Tab, ui sizetab );


/*********  Fourier Transforms, Convolutions, Filtering  ****************/

overror_t  __vcuf OVCUAPI   cudaVCF_FFT( cfVector Y, cfVector X, ui size, int dir );
overror_t  __vcuf OVCUAPI   cudaVCF_2FFT( cfVector Y1, cfVector Y2, cfVector X1, cfVector X2, ui size, int dir );
overror_t  __vcuf OVCUAPI   cudaVCF_filter( cfVector Y, cfVector X, cfVector Flt, ui size );

/***************************  Input and Output *****************************
	The input/output functions involve memory transfers from device
	to host memory or vice versa. The generic cudaVCF_input/output functions
	allocate their own host buffers, whereas the cudaVCF_xxx_buf functions
	take a user-supplied buffer h_Wk and are much more efficient.          */

overror_t  __vf    cudaVCF_fprint( FILE *stream, cfVector X, ui size, unsigned nperline, unsigned linewidth );
overror_t  __vf    cudaVCF_cprint( cfVector X, ui size, unsigned nperline );
#define       cudaVCF_print( x, sz, npl )  cudaVCF_fprint( stdout, x, sz, npl, 80 )
overror_t  __vf    cudaVCF_fprint_buf( FILE *stream, cfVector d_X, ui size, unsigned nperline, unsigned linewidth, cfVector h_Wk );
overror_t  __vf    cudaVCF_cprint_buf( cfVector d_X, ui size, unsigned nperline, cfVector h_Wk );
#define       cudaVCF_print_buf( d_x, sz, npl, h_Wk )  cudaVCF_fprint_buf( stdout, d_x, sz, npl, 80, h_Wk )
 /*  cudaVCF_print, cudaVCF_cprint are usable only for console applications!  */
overror_t  __vf    cudaVCF_write( FILE *stream, cfVector X, ui size  );
overror_t  __vf    cudaVCF_write_buf( FILE *stream, cfVector d_X, ui size, cfVector h_Wk );
                     /* cudaVCF_write, cudaVCF_read in ascii format */
#if !((defined __BORLANDC__) && (__BORLANDC__ < 0x710))
		/* modern compiler versions:  */
	overror_t  __vf    cudaVCF_read( cfVector X, ui size, FILE *stream );
	overror_t  __vf    cudaVCF_read_buf( cfVector d_X, ui size, FILE *stream, cfVector h_Wk );
#else /* older Borland compiler versions need separate implementation */
	overror_t  __vf    cudaVCF_read1( cfVector X, ui size, FILE *stream );
	overror_t  __vf    cudaVCF_read1_buf( cfVector d_X, ui size, FILE *stream, cfVector h_Wk );
	#define cudaVCF_read     cudaVCF_read1
	#define cudaVCF_read_buf cudaVCF_read1_buf
#endif
overror_t  __vf    cudaVCF_store( FILE *stream, cfVector X, ui size );
overror_t  __vf    cudaVCF_recall( cfVector X, ui size, FILE *stream );
overror_t  __vf    cudaVCF_store_buf( FILE *stream, cfVector d_X, ui size, cfVector h_Wk );
overror_t  __vf    cudaVCF_recall_buf( cfVector d_X, ui size, FILE *stream, cfVector h_Wk );
                     /* cudaVCF_store, cudaVCF_recall in binary format */


#ifdef __cplusplus
}  // end of extern "C"
#endif

/******************  VCFcu_ functions: **********************************
	act on host memory, using the CUDA device for processing
************************************************************************/

#ifdef __cplusplus
extern "C" {
#endif

/*******************  Initialization **********************************/

void  __vcuf OVCUAPI   VCFcu_equ0( cfVector X, ui size );
void  __vcuf OVCUAPI   VCFcu_equ1( cfVector X, ui size );
void  __vcuf OVCUAPI   VCFcu_equm1( cfVector X, ui size );
void  __vcuf OVCUAPI   VCFcu_equV( cfVector Y, cfVector X, ui size );  /* copies from device to device */
#if defined __cplusplus && defined _CMATH_CLASSDEFS && defined __BORLANDC__ && defined _WIN64
} // for C++Builder on Win64, the following functions cannot be extern "C", if fComplex is a class
#endif
void  __vcuf OVCUAPI_ifNotBC64Class   VCFcu_equC( cfVector X, ui size, fComplex C );
void  __vcuf OVCUAPI_ifNotBC64Class   VCFxcu_equV( cfVector Y, cfVector X, ui size, fComplex A, fComplex B );
void  __vcuf OVCUAPI_ifNotBC64Class   VCFcu_ramp( cfVector X, ui size, fComplex Start, fComplex Rise );
/* no Vcu_random functions: random generation runs on CPU anyway */


#if defined __cplusplus && defined _CMATH_CLASSDEFS && defined __BORLANDC__ && defined _WIN64
extern "C" {
#endif

void  __vcuf OVCUAPI   VFcu_CtoReIm( fVector Re, fVector Im, cfVector X, ui size );
void  __vcuf OVCUAPI   VFcu_ReImtoC( cfVector Y, fVector Re, fVector Im, ui size );
void  __vcuf OVCUAPI   VFcu_CtoRe( fVector Re, cfVector X, ui size );
void  __vcuf OVCUAPI   VFcu_RetoC( cfVector Y, fVector Re, ui size );
void  __vcuf OVCUAPI   VFcu_CtoIm( fVector Im, cfVector X, ui size );
void  __vcuf OVCUAPI   VFcu_ImtoC( cfVector Y, fVector Im, ui size );
void  __vcuf OVCUAPI   VFcu_CtoPolar( fVector Mag, fVector Arg, cfVector X, ui size );
void  __vcuf OVCUAPI   VFcu_PolartoC( cfVector Y, fVector Mag, fVector Arg, ui size );
void  __vcuf OVCUAPI   VFcu_CtoNorm( fVector Norm, cfVector X, ui size );
void  __vcuf OVCUAPI   VFcu_CtoAbs( fVector Abs, cfVector X, ui size );
void  __vcuf OVCUAPI   VFcu_CtoArg( fVector Arg, cfVector X, ui size );
void  __vcuf OVCUAPI   VCFcu_normtoC( cfVector Norm, cfVector X, ui size );
#define     VCFcu_real         VFcu_CtoRe
#define     VCFcu_imag         VFcu_CtoIm
#define     VCFcu_arg          VFcu_CtoArg
#define     VCFcu_norm         VFcu_CtoNorm
#define     VCFcu_polar        VFcu_PolartoC
#define     VCFcu_complex      VFcu_ReImtoC


/****************  Data-type interconversions  ***************************/

void  __vcuf OVCUAPI   Vcu_CFtoCD( cdVector Y, cfVector X, ui size );
void  __vcuf OVCUAPI   Vcu_CDtoCF( cfVector Y, cdVector X, ui size );


/****************  Index-oriented manipulations ***********************/

void  __vcuf OVCUAPI   VCFcu_delete( cfVector X, ui size, ui pos );
#if defined __cplusplus && defined _CMATH_CLASSDEFS && defined __BORLANDC__ && defined _WIN64
} // for C++Builder on Win64, the following functions cannot be extern "C", if fComplex is a class
#endif
void  __vcuf OVCUAPI_ifNotBC64Class   VCFcu_insert( cfVector X, ui size, ui pos, fComplex C );
#if defined __cplusplus && defined _CMATH_CLASSDEFS && defined __BORLANDC__ && defined _WIN64
extern "C" {
#endif

void  __vcuf OVCUAPI   VCFcu_reflect( cfVector X, ui size );
void  __vcuf OVCUAPI   VCFcu_rev( cfVector Y, cfVector X, ui size );
void  __vcuf OVCUAPI   VCFcu_rotate( cfVector Y, cfVector X, ui size, ssize_t pos );
void  __vcuf OVCUAPI   VCFcu_rotate_buf( cfVector Y, cfVector X, ui size, ssize_t pos, cfVector Buf );
  /* no V?cu_indpick, V?cu_indput possible! */
void  __vcuf OVCUAPI   VCFcu_subvector( cfVector Y, ui sizey, cfVector X, ssize_t samp );


/***************** Functions of a sub-set of elements  ********************/

#if defined __cplusplus && defined _CMATH_CLASSDEFS && defined __BORLANDC__ && defined _WIN64
} // for C++Builder on Win64, the following functions cannot be extern "C", if fComplex is a class
#endif
void  __vcuf OVCUAPI_ifNotBC64Class   VCFcu_subvector_equC(  cfVector Y, ui subsiz, ui samp, fComplex C );
#if defined __cplusplus && defined _CMATH_CLASSDEFS && defined __BORLANDC__ && defined _WIN64
extern "C" {
#endif
void  __vcuf OVCUAPI   VCFcu_subvector_equV(  cfVector Y, ui subsiz, ui samp, cfVector X );


/**************** One-Dimensional Vector Operations ***********************/

float    __vcuf OVCUAPI   VCFcu_absmax(  cfVector X, ui size );
float    __vcuf OVCUAPI   VCFcu_absmin(  cfVector X, ui size );
float    __vcuf OVCUAPI   VCFcu_absmaxind( ui *pos, cfVector X, ui size );
float    __vcuf OVCUAPI   VCFcu_absminind( ui *pos, cfVector X, ui size );
#if defined __cplusplus && defined _CMATH_CLASSDEFS
} // the following functions cannot be extern "C", if fComplex is a class
#endif
fComplex  __vcuf OVCUAPI_ifNotClass   VCFcu_maxReIm(     cfVector X, ui size );
fComplex  __vcuf OVCUAPI_ifNotClass   VCFcu_minReIm(     cfVector X, ui size );
fComplex  __vcuf OVCUAPI_ifNotClass   VCFcu_absmaxReIm(  cfVector X, ui size );
fComplex  __vcuf OVCUAPI_ifNotClass   VCFcu_absminReIm(  cfVector X, ui size );
fComplex  __vcuf OVCUAPI_ifNotClass   VCFcu_cabsmax(  cfVector X, ui size );
fComplex  __vcuf OVCUAPI_ifNotClass   VCFcu_cabsmin(  cfVector X, ui size );
fComplex  __vcuf OVCUAPI_ifNotClass   VCFcu_sabsmax(  cfVector X, ui size );
fComplex  __vcuf OVCUAPI_ifNotClass   VCFcu_sabsmin(  cfVector X, ui size );
fComplex  __vcuf OVCUAPI_ifNotClass   VCFcu_sum(     cfVector X, ui size );
fComplex  __vcuf OVCUAPI_ifNotClass   VCFcu_prod(    cfVector X, ui size );
fComplex  __vcuf OVCUAPI_ifNotClass   VCFcu_mean(   cfVector X, ui size );
fComplex  __vcuf OVCUAPI_ifNotClass   VCFcu_meanwW( cfVector X, fVector Wt, ui size );
fComplex  __vcuf OVCUAPI_ifNotClass   VCFcu_scalprod( cfVector X, cfVector Y, ui size );
#if defined __cplusplus && defined _CMATH_CLASSDEFS
extern "C" {
#endif
void    __vf OVCUAPI  VCFcu_runsum(  cfVector Y, cfVector X, ui size );
void    __vf OVCUAPI  VCFcu_runprod( cfVector Y, cfVector X, ui size );
#if defined __cplusplus && defined _CMATH_CLASSDEFS && defined __BORLANDC__ && defined _WIN64
} // for C++Builder on Win64, the following functions cannot be extern "C", if fComplex is a class
#endif
int      __vcuf OVCUAPI_ifNotBC64Class   VCFcu_iselementC( cfVector Tab, ui size, fComplex C );
#if defined __cplusplus && defined _CMATH_CLASSDEFS && defined __BORLANDC__ && defined _WIN64
extern "C" {
#endif
ui      __vcuf OVCUAPI   VCFcu_iselementV( cfVector Y, cfVector X, ui sizex, cfVector Tab, ui sizetab );


/*********  Fourier Transforms, Convolutions, Filtering  ****************/

void  __vcuf OVCUAPI   VCFcu_FFT( cfVector Y, cfVector X, ui size, int dir );
void  __vcuf OVCUAPI   VCFcu_2FFT( cfVector Y1, cfVector Y2, cfVector X1, cfVector X2, ui size, int dir );
void  __vcuf OVCUAPI   VCFcu_filter( cfVector Y, cfVector X, cfVector Flt, ui size );

#ifdef __cplusplus
}  // end of extern "C"
#endif

#endif /*  __CUDAVCFSTD_H */
