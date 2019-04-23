/*  cudaVPFstd.h

  vector management functions:
  manipulations on whole arrays or vectors of data type "fPolar"
  (single-precision polar complex numbers)

  Copyright (c) 1996-2017 by OptiCode - Dr. Martin Sander Software Dev.
  All Rights Reserved.
*/

#ifndef __CUDAVPFSTD_H
#define __CUDAVPFSTD_H
#if !defined( __CUDAVECLIB_H )
#include <cudaVecLib.h>
#endif

/******************  cudaVPF_ functions: **********************************
	 act on vectors in CUDA device memory; 
	 scalar parameters and return values on host
******************  cusdVPF_ functions: **********************************
	 also act on vectors in CUDA device memory; 
	 scalar parameters and return values by address on device memory
************************************************************************/

#ifdef __cplusplus
extern "C" {
#endif

/*************************  Generation  **************************/

pfVector  __vf   cudaVPF_vector( ui size );   /* allocates a vector on device memory */
pfVector  __vf   cudaVPF_vector0( ui size );
/* The following functions allocate device-accessible, "pinned" memory on the host.
	This memory is mapped onto the device memory space. The resulting device address is returned.
	The vector can be accessed either by its host address "hostPtr" e.g., VPF_equC( hostPtr, size, C );
	or by its device address , e.g., cudaVPF_equC( devicePtr, size, C );     */
pfVector  __vf   cudaVPF_pinnedVector(  pfVector *hostPtr, ui size ); 
pfVector  __vf   cudaVPF_pinnedVector0( pfVector *hostPtr, ui size );

/***************  Addressing single vector elements ******************/

fPolar * __vcuf OVCUAPI cudaVPF_Pelement( pfVector X, ui n );
#if defined __cplusplus && defined _CMATH_CLASSDEFS
} // the following function cannot be extern "C", if fPolar is a class
#endif
fPolar   __vcuf OVCUAPI cudaVPF_element( pfVector X, ui n );
#if defined __cplusplus && defined _CMATH_CLASSDEFS
extern "C" {
#endif
#if defined __cplusplus && defined _CMATH_CLASSDEFS && defined __BORLANDC__ && defined _WIN64
} // for C++Builder on Win64, the following functions cannot be extern "C", if fPolar is a class
#endif
void  __vcuf OVCUAPI cudaVPF_setElement( pfVector X, ui n, fPolar C );
#if defined __cplusplus && defined _CMATH_CLASSDEFS && defined __BORLANDC__ && defined _WIN64
extern "C" {
#endif
void  __vcuf OVCUAPI cusdVPF_setElement( pfVector X, ui n, fPolar *d_C );
void  __vcuf OVCUAPI cudaVPF_getElement( fPolar *y, pfVector X, ui n );
void  __vcuf OVCUAPI cusdVPF_getElement( fPolar *d_y, pfVector X, ui n );

/*******************  Initialization **********************************/

overror_t  __vcuf OVCUAPI   cudaVPF_equ0( pfVector X, ui size );
overror_t  __vcuf OVCUAPI   cudaVPF_equ1( pfVector X, ui size );
overror_t  __vcuf OVCUAPI   cudaVPF_equm1( pfVector X, ui size );
#if defined __cplusplus && defined _CMATH_CLASSDEFS && defined __BORLANDC__ && defined _WIN64
} // cannot be extern "C" for C++Builder on Win64, if fPolar is a class
#endif
overror_t  __vcuf OVCUAPI   cudaVPF_equC( pfVector X, ui size, fPolar C );
#if defined __cplusplus && defined _CMATH_CLASSDEFS && defined __BORLANDC__ && defined _WIN64
extern "C" {
#endif
overror_t  __vcuf OVCUAPI   cusdVPF_equC( pfVector X, ui size, fPolar *C );
overror_t  __vcuf OVCUAPI   cudaVPF_equV( pfVector Y, pfVector X, ui size );  /* copies from device to device */
overror_t  __vcuf           cudaVPF_equVhost( pfVector Y, pfVector X, ui size );  /* copies from host to device */
overror_t  __vcuf           VPF_equVdevice( pfVector Y, pfVector X, ui size );  /* copies from device to host */
overror_t  __vcuf OVCUAPI   cudaVPF_principal( pfVector Y, pfVector X, ui size );

overror_t  __vcuf OVCUAPI   cudaVF_PtoMagArg( fVector Mag, fVector Arg, pfVector X, ui size );
overror_t  __vcuf OVCUAPI   cudaVF_MagArgtoP( pfVector Y, fVector Mag, fVector Arg, ui size );
overror_t  __vcuf OVCUAPI   cudaVF_MagArgtoPrincipal( pfVector Y, fVector Mag, fVector Arg, ui size );
overror_t  __vcuf OVCUAPI   cudaVF_PtoMag(  fVector Mag, pfVector X, ui size );
overror_t  __vcuf OVCUAPI   cudaVF_MagtoP(  pfVector Y, fVector Mag, ui size );
overror_t  __vcuf OVCUAPI   cudaVF_PtoArg(  fVector Arg, pfVector X, ui size );
overror_t  __vcuf OVCUAPI   cudaVF_ArgtoP(  pfVector Y, fVector Arg, ui size );
overror_t  __vcuf OVCUAPI   cudaVF_CtoP( pfVector YP, cfVector XC, ui size );
overror_t  __vcuf OVCUAPI   cudaVF_PtoC( cfVector YC, pfVector XP, ui size );
overror_t  __vcuf OVCUAPI   cudaVF_PtoNorm( fVector Norm, pfVector X, ui size );
overror_t  __vcuf OVCUAPI   cudaVF_PtoReIm( fVector Re, fVector Im, pfVector X, ui size );
overror_t  __vcuf OVCUAPI   cudaVF_ReImtoP( pfVector Y, fVector Re, fVector Im, ui size );
overror_t  __vcuf OVCUAPI   cudaVF_PtoRe( fVector Re, pfVector X, ui size );
overror_t  __vcuf OVCUAPI   cudaVF_PtoIm( fVector Im, pfVector X, ui size );
#define     cudaVPF_abs        cudaVF_PtoMag
#define     cudaVPF_real       cudaVF_PtoRe
#define     cudaVPF_imag       cudaVF_PtoIm
#define     cudaVPF_arg        cudaVF_PtoArg
#define     cudaVPF_norm       cudaVF_PtoNorm

/****************  Data-type overror_terconversions  ***************************/

overror_t  __vcuf OVCUAPI   cudaV_PFtoPD( pdVector Y, pfVector X, ui size );
overror_t  __vcuf OVCUAPI   cudaV_PDtoPF( pfVector Y, pdVector X, ui size );


/****************  Index-oriented manipulations ***********************/

overror_t  __vcuf OVCUAPI   cudaVPF_delete( pfVector X, ui size, ui pos );
overror_t  __vcuf OVCUAPI   cusdVPF_insert( pfVector X, ui size, ui pos, fPolar *C );
#if defined __cplusplus && defined _CMATH_CLASSDEFS && defined __BORLANDC__ && defined _WIN64
} // cannot be extern "C" for C++Builder on Win64, if fPolar is a class
#endif
overror_t  __vcuf OVCUAPI   cudaVPF_insert( pfVector X, ui size, ui pos, fPolar C );
#if defined __cplusplus && defined _CMATH_CLASSDEFS && defined __BORLANDC__ && defined _WIN64
extern "C" {
#endif

overror_t  __vcuf OVCUAPI   cudaVPF_reflect( pfVector X, ui size );
overror_t  __vcuf OVCUAPI   cudaVPF_rev( pfVector Y, pfVector X, ui size );
overror_t  __vcuf OVCUAPI   cudaVPF_rotate( pfVector Y, pfVector X, ui size, ssize_t pos );
overror_t  __vcuf OVCUAPI   cudaVPF_rotate_buf( pfVector Y, pfVector X, ui size, ssize_t pos, pfVector Buf );
overror_t  __vcuf OVCUAPI   cudaVPF_indpick( pfVector Y, uiVector Ind, ui sizey, pfVector X );
overror_t  __vcuf OVCUAPI   cudaVPF_indput(  pfVector Y, pfVector X, uiVector Ind, ui sizex );
overror_t  __vcuf OVCUAPI   cudaVPF_subvector( pfVector Y, ui sizey, pfVector X, ssize_t samp );


/*************** Functions of a sub-set of elements  ********************/

#if defined __cplusplus && defined _CMATH_CLASSDEFS && defined __BORLANDC__ && defined _WIN64
} // cannot be extern "C" for C++Builder on Win64, if fPolar is a class
#endif
overror_t  __vcuf OVCUAPI   cudaVPF_subvector_equC(  pfVector Y, ui subsiz, ui samp, fPolar C );
#if defined __cplusplus && defined _CMATH_CLASSDEFS && defined __BORLANDC__ && defined _WIN64
extern "C" {
#endif
overror_t  __vcuf OVCUAPI   cusdVPF_subvector_equC(  pfVector Y, ui subsiz, ui samp, fPolar *C );
overror_t  __vcuf OVCUAPI   cudaVPF_subvector_equV(  pfVector Y, ui subsiz, ui samp, pfVector X );
    /*   for arithmetic functions of subsets, see <VPFmath.h>  */

/**************** One-Dimensional Vector Operations ***********************/

overror_t   __vcuf OVCUAPI   cudaVPF_absmax(  float *h_RetVal, pfVector X, ui size );
overror_t   __vcuf OVCUAPI   cudaVPF_absmin(  float *h_RetVal, pfVector X, ui size );
overror_t   __vcuf OVCUAPI   cudaVPF_absmaxind( float *h_RetVal, ui *pos, pfVector X, ui size );
overror_t   __vcuf OVCUAPI   cudaVPF_absminind( float *h_RetVal, ui *pos, pfVector X, ui size );
overror_t   __vcuf OVCUAPI   cudaVPF_prod( fPolar *h_RetVal, pfVector X, ui size );
overror_t   __vcuf OVCUAPI   cudaVPF_runprod( pfVector Y, pfVector X, ui size );

overror_t   __vcuf OVCUAPI   cusdVPF_absmax(  float *d_RetVal, pfVector X, ui size );
overror_t   __vcuf OVCUAPI   cusdVPF_absmin(  float *d_RetVal, pfVector X, ui size );
overror_t   __vcuf OVCUAPI   cusdVPF_absmaxind( float *d_RetVal, ui *pos, pfVector X, ui size );
overror_t   __vcuf OVCUAPI   cusdVPF_absminind( float *d_RetVal, ui *pos, pfVector X, ui size );
overror_t   __vcuf OVCUAPI   cusdVPF_prod( fPolar *d_RetVal, pfVector X, ui size );

#if defined __cplusplus && defined _CMATH_CLASSDEFS && defined __BORLANDC__ && defined _WIN64
} // cannot be extern "C" for C++Builder on Win64, if fPolar is a class
#endif
int    __vcuf OVCUAPI   cudaVPF_iselementC( pfVector Tab, ui size, fPolar C );
#if defined __cplusplus && defined _CMATH_CLASSDEFS && defined __BORLANDC__ && defined _WIN64
extern "C" {
#endif
int       __vcuf OVCUAPI   cusdVPF_iselementC( pfVector Tab, ui size, fPolar *C );
overror_t __vcuf OVCUAPI   cudaVPF_iselementV( ui *h_nFound, pfVector Y, pfVector X, ui sizex, pfVector Tab, ui sizetab );

/***************************  Input and Output *****************************
	The input/output functions involve memory transfers from device
	to host memory or vice versa. The generic cudaVPF_input/output functions
	allocate their own host buffers, whereas the cudaVPF_xxx_buf functions
	take a user-supplied buffer h_Wk and are much more efficient.          */

overror_t  __vf    cudaVPF_fprint( FILE *stream, pfVector X, ui size, unsigned nperline, unsigned linewidth );
overror_t  __vf    cudaVPF_cprint( pfVector X, ui size, unsigned nperline );
#define       cudaVPF_print( x, sz, npl )  cudaVPF_fprint( stdout, x, sz, npl, 80 )
overror_t  __vf    cudaVPF_fprint_buf( FILE *stream, pfVector d_X, ui size, unsigned nperline, unsigned linewidth, pfVector h_Wk );
overror_t  __vf    cudaVPF_cprint_buf( pfVector d_X, ui size, unsigned nperline, pfVector h_Wk );
#define       cudaVPF_print_buf( d_x, sz, npl, h_Wk )  cudaVPF_fprint_buf( stdout, d_x, sz, npl, 80, h_Wk )
 /*  cudaVPF_print, cudaVPF_cprint are usable only for console applications!  */
overror_t  __vf    cudaVPF_write( FILE *stream, pfVector X, ui size  );
overror_t  __vf    cudaVPF_write_buf( FILE *stream, pfVector d_X, ui size, pfVector h_Wk );
                     /* cudaVPF_write, cudaVPF_read in ascii format */
overror_t  __vf    cudaVPF_read( pfVector X, ui size, FILE *stream );
overror_t  __vf    cudaVPF_read_buf( pfVector d_X, ui size, FILE *stream, pfVector h_Wk );
overror_t  __vf    cudaVPF_store( FILE *stream, pfVector X, ui size );
overror_t  __vf    cudaVPF_recall( pfVector X, ui size, FILE *stream );
overror_t  __vf    cudaVPF_store_buf( FILE *stream, pfVector d_X, ui size, pfVector h_Wk );
overror_t  __vf    cudaVPF_recall_buf( pfVector d_X, ui size, FILE *stream, pfVector h_Wk );
                     /* cudaVPF_store, cudaVPF_recall in binary format */


#ifdef __cplusplus
}  // end of extern "C"
#endif

/******************  VPFcu_ functions: **********************************
	act on host memory, using the CUDA device for processing
************************************************************************/

#ifdef __cplusplus
extern "C" {
#endif

/*******************  Initialization **********************************/

void  __vcuf OVCUAPI   VPFcu_equ0( pfVector X, ui size );
void  __vcuf OVCUAPI   VPFcu_equ1( pfVector X, ui size );
void  __vcuf OVCUAPI   VPFcu_equm1( pfVector X, ui size );
#if defined __cplusplus && defined _CMATH_CLASSDEFS && defined __BORLANDC__ && defined _WIN64
} // cannot be extern "C" for C++Builder on Win64, if fPolar is a class
#endif
void  __vcuf OVCUAPI   VPFcu_equC( pfVector X, ui size, fPolar C );
#if defined __cplusplus && defined _CMATH_CLASSDEFS && defined __BORLANDC__ && defined _WIN64
extern "C" {
#endif
void  __vcuf OVCUAPI   VPFcu_equV( pfVector Y, pfVector X, ui size );  /* copies from device to device */
void  __vcuf OVCUAPI   VPFcu_principal( pfVector Y, pfVector X, ui size );

void  __vcuf OVCUAPI   VFcu_PtoMagArg( fVector Mag, fVector Arg, pfVector X, ui size );
void  __vcuf OVCUAPI   VFcu_MagArgtoP( pfVector Y, fVector Mag, fVector Arg, ui size );
void  __vcuf OVCUAPI   VFcu_MagArgtoPrincipal( pfVector Y, fVector Mag, fVector Arg, ui size );
void  __vcuf OVCUAPI   VFcu_PtoMag(  fVector Mag, pfVector X, ui size );
void  __vcuf OVCUAPI   VFcu_MagtoP(  pfVector Y, fVector Mag, ui size );
void  __vcuf OVCUAPI   VFcu_PtoArg(  fVector Arg, pfVector X, ui size );
void  __vcuf OVCUAPI   VFcu_ArgtoP(  pfVector Y, fVector Arg, ui size );
void  __vcuf OVCUAPI   VFcu_CtoP( pfVector YP, cfVector XC, ui size );
void  __vcuf OVCUAPI   VFcu_PtoC( cfVector YC, pfVector XP, ui size );
void  __vcuf OVCUAPI   VFcu_PtoNorm( fVector Norm, pfVector X, ui size );
void  __vcuf OVCUAPI   VFcu_PtoReIm( fVector Re, fVector Im, pfVector X, ui size );
void  __vcuf OVCUAPI   VFcu_ReImtoP( pfVector Y, fVector Re, fVector Im, ui size );
void  __vcuf OVCUAPI   VFcu_PtoRe( fVector Re, pfVector X, ui size );
void  __vcuf OVCUAPI   VFcu_PtoIm( fVector Im, pfVector X, ui size );
#define     VPFcu_real       VFcu_PtoRe
#define     VPFcu_imag       VFcu_PtoIm
#define     VPFcu_arg        VFcu_PtoArg
#define     VPFcu_norm       VFcu_PtoNorm

/****************  Data-type interconversions  ***************************/

void  __vcuf OVCUAPI   Vcu_PFtoPD( pdVector Y, pfVector X, ui size );
void  __vcuf OVCUAPI   Vcu_PDtoPF( pfVector Y, pdVector X, ui size );


/****************  Index-oriented manipulations ***********************/

void  __vcuf OVCUAPI   VPFcu_delete( pfVector X, ui size, ui pos );
#if defined __cplusplus && defined _CMATH_CLASSDEFS && defined __BORLANDC__ && defined _WIN64
} // cannot be extern "C" for C++Builder on Win64, if fPolar is a class
#endif
void  __vcuf OVCUAPI   VPFcu_insert( pfVector X, ui size, ui pos, fPolar C );
#if defined __cplusplus && defined _CMATH_CLASSDEFS && defined __BORLANDC__ && defined _WIN64
extern "C" {
#endif

void  __vcuf OVCUAPI   VPFcu_reflect( pfVector X, ui size );
void  __vcuf OVCUAPI   VPFcu_rev( pfVector Y, pfVector X, ui size );
void  __vcuf OVCUAPI   VPFcu_rotate( pfVector Y, pfVector X, ui size, ssize_t pos );
void  __vcuf OVCUAPI   VPFcu_rotate_buf( pfVector Y, pfVector X, ui size, ssize_t pos, pfVector Buf );
  /* no V?cu_indpick, V?cu_indput possible! */
void  __vcuf OVCUAPI   VPFcu_subvector( pfVector Y, ui sizey, pfVector X, ssize_t samp );


/*************** Functions of a sub-set of elements  ********************/

#if defined __cplusplus && defined _CMATH_CLASSDEFS && defined __BORLANDC__ && defined _WIN64
} // cannot be extern "C" for C++Builder on Win64, if fPolar is a class
#endif
void  __vcuf OVCUAPI   VPFcu_subvector_equC(  pfVector Y, ui subsiz, ui samp, fPolar C );
#if defined __cplusplus && defined _CMATH_CLASSDEFS && defined __BORLANDC__ && defined _WIN64
extern "C" {
#endif
void  __vcuf OVCUAPI   VPFcu_subvector_equV(  pfVector Y, ui subsiz, ui samp, pfVector X );
    /*   for arithmetic functions of subsets, see <VPFmath.h>  */

/**************** One-Dimensional Vector Operations ***********************/

float     __vcuf OVCUAPI   VPFcu_absmax(  pfVector X, ui size );
float     __vcuf OVCUAPI   VPFcu_absmin(  pfVector X, ui size );
float     __vcuf OVCUAPI   VPFcu_absmaxind( ui *pos, pfVector X, ui size );
float     __vcuf OVCUAPI   VPFcu_absminind( ui *pos, pfVector X, ui size );
#if defined __cplusplus && defined _CMATH_CLASSDEFS
} // the following functions cannot be extern "C", if fPolar is a class
#endif
fPolar  __vcuf OVCUAPI   VPFcu_prod(    pfVector X, ui size );
#if defined __cplusplus && defined _CMATH_CLASSDEFS
extern "C" {
#endif
void      __vcuf OVCUAPI  VPFcu_runprod( pfVector Y, pfVector X, ui size );

#if defined __cplusplus && defined _CMATH_CLASSDEFS && defined __BORLANDC__ && defined _WIN64
} // cannot be extern "C" for C++Builder on Win64, if fPolar is a class
#endif
int    __vcuf OVCUAPI   VPFcu_iselementC( pfVector Tab, ui size, fPolar C );
#if defined __cplusplus && defined _CMATH_CLASSDEFS && defined __BORLANDC__ && defined _WIN64
extern "C" {
#endif
ui     __vcuf OVCUAPI   VPFcu_iselementV( pfVector Y, pfVector X, ui sizex, pfVector Tab, ui sizetab );


#ifdef __cplusplus
}  // end of extern "C"
#endif

#endif /*  __CUDAVPFSTD_H */
