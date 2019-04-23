/*  cudaVPDstd.h

  vector management functions:
  manipulations on whole arrays or vectors of data type dPolar
  (double-precision polar complex numbers)

  Copyright (c) 1996-2017 by OptiCode - Dr. Martin Sander Software Dev.
  All Rights Reserved.
*/

#ifndef __CUDAVPDSTD_H
#define __CUDAVPDSTD_H
#if !defined( __CUDAVECLIB_H )
#include <cudaVecLib.h>
#endif

/******************  cudaVPD_ functions: **********************************
	 act on vectors in CUDA device memory; 
	 scalar parameters and return values on host
******************  cusdVPD_ functions: **********************************
	 also act on vectors in CUDA device memory; 
	 scalar parameters and return values by address on device memory
************************************************************************/

#ifdef __cplusplus
extern "C" {
#endif

/*************************  Generation  **************************/

pdVector  __vf   cudaVPD_vector( ui size );   /* allocates a vector on device memory */
pdVector  __vf   cudaVPD_vector0( ui size );
/* The following functions allocate device-accessible, "pinned" memory on the host.
	This memory is mapped onto the device memory space. The resulting device address is returned.
	The vector can be accessed either by its host address "hostPtr" e.g., VPD_equC( hostPtr, size, C );
	or by its device address , e.g., cudaVPD_equC( devicePtr, size, C );     */
pdVector  __vf   cudaVPD_pinnedVector(  pdVector *hostPtr, ui size ); 
pdVector  __vf   cudaVPD_pinnedVector0( pdVector *hostPtr, ui size );

/***************  Addressing single vector elements ******************/

dPolar * __vcuf OVCUAPI cudaVPD_Pelement( pdVector X, ui n );
#if defined __cplusplus && defined _CMATH_CLASSDEFS
} // the following function cannot be extern "C", if dPolar is a class
#endif
dPolar   __vcuf OVCUAPI cudaVPD_element( pdVector X, ui n );
#if defined __cplusplus && defined _CMATH_CLASSDEFS
extern "C" {
#endif
void  __vcuf OVCUAPI cudaVPD_getElement( dPolar *y, pdVector X, ui n );
void  __vcuf OVCUAPI cusdVPD_getElement( dPolar *d_y, pdVector X, ui n );
void  __vcuf OVCUAPI cudaVPD_setElement( pdVector X, ui n, dPolar C );
void  __vcuf OVCUAPI cusdVPD_setElement( pdVector X, ui n, dPolar *C );

/*******************  Initialization **********************************/

overror_t  __vcuf OVCUAPI   cudaVPD_equ0( pdVector X, ui size );
overror_t  __vcuf OVCUAPI   cudaVPD_equ1( pdVector X, ui size );
overror_t  __vcuf OVCUAPI   cudaVPD_equm1( pdVector X, ui size );
overror_t  __vcuf OVCUAPI   cudaVPD_equC( pdVector X, ui size, dPolar C );
overror_t  __vcuf OVCUAPI   cusdVPD_equC( pdVector X, ui size, dPolar *C );
overror_t  __vcuf OVCUAPI   cudaVPD_equV( pdVector Y, pdVector X, ui size ); /* copies from device to device */
overror_t  __vcuf           cudaVPD_equVhost( pdVector Y, pdVector X, ui size );  /* copies from host to device */
overror_t  __vcuf           VPD_equVdevice( pdVector Y, pdVector X, ui size );  /* copies from device to host */
overror_t  __vcuf OVCUAPI   cudaVPD_principal( pdVector Y, pdVector X, ui size );

overror_t  __vcuf OVCUAPI   cudaVD_PtoMagArg( dVector Mag, dVector Arg, pdVector X, ui size );
overror_t  __vcuf OVCUAPI   cudaVD_MagArgtoP( pdVector Y, dVector Mag, dVector Arg, ui size );
overror_t  __vcuf OVCUAPI   cudaVD_MagArgtoPrincipal( pdVector Y, dVector Mag, dVector Arg, ui size );
overror_t  __vcuf OVCUAPI   cudaVD_PtoMag( dVector Mag, pdVector X, ui size );
overror_t  __vcuf OVCUAPI   cudaVD_MagtoP( pdVector Y, dVector Mag, ui size );
overror_t  __vcuf OVCUAPI   cudaVD_PtoArg( dVector Arg, pdVector X, ui size );
overror_t  __vcuf OVCUAPI   cudaVD_ArgtoP( pdVector Y, dVector Arg, ui size );
overror_t  __vcuf OVCUAPI   cudaVD_CtoP( pdVector YP, cdVector XC, ui size );
overror_t  __vcuf OVCUAPI   cudaVD_PtoC( cdVector YC, pdVector XP, ui size );
overror_t  __vcuf OVCUAPI   cudaVD_PtoNorm( dVector Norm, pdVector X, ui size );
overror_t  __vcuf OVCUAPI   cudaVD_PtoReIm( dVector Re, dVector Im, pdVector X, ui size );
overror_t  __vcuf OVCUAPI   cudaVD_ReImtoP( pdVector Y, dVector Re, dVector Im, ui size );
overror_t  __vcuf OVCUAPI   cudaVD_PtoRe( dVector Re, pdVector X, ui size );
overror_t  __vcuf OVCUAPI   cudaVD_PtoIm( dVector Im, pdVector X, ui size );
overror_t   __vcuf OVCUAPI   cudaVPD_abs(   dVector Y, pdVector X, ui size );
#define     cudaVPD_real( Y, X, sz )         cudaVD_PtoRe( Y, X, sz )
#define     cudaVPD_imag( Y, X, sz )         cudaVD_PtoIm( Y, X, sz )
#define     cudaVPD_arg( Y, X, sz )          cudaVD_PtoArg( Y, X, sz )
#define     cudaVPD_norm( Y, X, sz )         cudaVD_PtoNorm( Y, X, sz )


/****************  Data-type overror_terconversions  ***************************/

overror_t  __vcuf OVCUAPI   cudaV_PFtoPD( pdVector Y, pfVector X, ui size );
overror_t  __vcuf OVCUAPI   cudaV_PDtoPF( pfVector Y, pdVector X, ui size );

/****************  Index-oriented manipulations ***********************/

overror_t  __vcuf OVCUAPI   cudaVPD_delete( pdVector X, ui size, ui pos );
overror_t  __vcuf OVCUAPI   cudaVPD_insert( pdVector X, ui size, ui pos, dPolar C );
overror_t  __vcuf OVCUAPI   cusdVPD_insert( pdVector X, ui size, ui pos, dPolar *C );
overror_t  __vcuf OVCUAPI   cudaVPD_reflect( pdVector X, ui size );
overror_t  __vcuf OVCUAPI   cudaVPD_rev( pdVector Y, pdVector X, ui size );
overror_t  __vcuf OVCUAPI   cudaVPD_rotate( pdVector Y, pdVector X, ui size, ssize_t pos );
overror_t  __vcuf OVCUAPI   cudaVPD_rotate_buf( pdVector Y, pdVector X, ui size, ssize_t pos, pdVector Buf );
overror_t  __vcuf OVCUAPI   cudaVPD_indpick( pdVector Y, uiVector Ind, ui sizey, pdVector X );
overror_t  __vcuf OVCUAPI   cudaVPD_indput(  pdVector Y, pdVector X, uiVector Ind, ui sizex );
overror_t  __vcuf OVCUAPI   cudaVPD_subvector( pdVector Y, ui sizey, pdVector X, ssize_t samp );


/***************** Functions of a sub-set of elements  ********************/

overror_t  __vcuf OVCUAPI   cudaVPD_subvector_equC(  pdVector Y, ui subsiz, ui samp, dPolar C );
overror_t  __vcuf OVCUAPI   cusdVPD_subvector_equC(  pdVector Y, ui subsiz, ui samp, dPolar *C );
overror_t  __vcuf OVCUAPI   cudaVPD_subvector_equV(  pdVector Y, ui subsiz, ui samp, pdVector X );
    /*   for arithmetic functions of subsets, see <cudaVPDmath.h>  */


/**************** One-Dimensional Vector Operations ***********************/

overror_t    __vcuf OVCUAPI   cudaVPD_absmax(  double *h_RetVal, pdVector X, ui size );
overror_t    __vcuf OVCUAPI   cudaVPD_absmin(  double *h_RetVal, pdVector X, ui size );
overror_t    __vcuf OVCUAPI   cudaVPD_absmaxind( double *h_RetVal, ui *pos, pdVector X, ui size );
overror_t    __vcuf OVCUAPI   cudaVPD_absminind( double *h_RetVal, ui *pos, pdVector X, ui size );
overror_t    __vcuf OVCUAPI   cudaVPD_prod( dPolar *h_RetVal, pdVector X, ui size );
overror_t    __vcuf OVCUAPI   cudaVPD_runprod( pdVector Y, pdVector X, ui size );

overror_t    __vcuf OVCUAPI   cusdVPD_absmax(  double *d_RetVal, pdVector X, ui size );
overror_t    __vcuf OVCUAPI   cusdVPD_absmin(  double *d_RetVal, pdVector X, ui size );
overror_t    __vcuf OVCUAPI   cusdVPD_absmaxind( double *d_RetVal, ui *pos, pdVector X, ui size );
overror_t    __vcuf OVCUAPI   cusdVPD_absminind( double *d_RetVal, ui *pos, pdVector X, ui size );
overror_t    __vcuf OVCUAPI   cusdVPD_prod( dPolar *d_RetVal, pdVector X, ui size );
overror_t    __vcuf OVCUAPI   cudaVPD_runprod( pdVector Y, pdVector X, ui size );

int       __vcuf OVCUAPI   cudaVPD_iselementC( pdVector Tab, ui size, dPolar C );
int       __vcuf OVCUAPI   cusdVPD_iselementC( pdVector Tab, ui size, dPolar *C );
overror_t __vcuf OVCUAPI   cudaVPD_iselementV( ui *h_nFound, pdVector Y, pdVector X, ui sizex, pdVector Tab, ui sizetab );

/***************************  Input and Output *****************************
	The input/output functions involve memory transfers from device
	to host memory or vice versa. The generic cudaVPD_input/output functions
	allocate their own host buffers, whereas the cudaVPD_xxx_buf functions
	take a user-supplied buffer h_Wk and are much more efficient.          */

overror_t  __vf    cudaVPD_fprint( FILE *stream, pdVector X, ui size, unsigned nperline, unsigned linewidth );
overror_t  __vf    cudaVPD_cprint( pdVector X, ui size, unsigned nperline );
#define       cudaVPD_print( x, sz, npl )  cudaVPD_fprint( stdout, x, sz, npl, 80 )
overror_t  __vf    cudaVPD_fprint_buf( FILE *stream, pdVector d_X, ui size, unsigned nperline, unsigned linewidth, pdVector h_Wk );
overror_t  __vf    cudaVPD_cprint_buf( pdVector d_X, ui size, unsigned nperline, pdVector h_Wk );
#define       cudaVPD_print_buf( d_x, sz, npl, h_Wk )  cudaVPD_fprint_buf( stdout, d_x, sz, npl, 80, h_Wk )
 /*  cudaVPD_print, cudaVPD_cprint are usable only for console applications!  */
overror_t  __vf    cudaVPD_write( FILE *stream, pdVector X, ui size  );
overror_t  __vf    cudaVPD_write_buf( FILE *stream, pdVector d_X, ui size, pdVector h_Wk );
                     /* cudaVPD_write, cudaVPD_read in ascii format */
overror_t  __vf    cudaVPD_read( pdVector X, ui size, FILE *stream );
overror_t  __vf    cudaVPD_read_buf( pdVector d_X, ui size, FILE *stream, pdVector h_Wk );
overror_t  __vf    cudaVPD_store( FILE *stream, pdVector X, ui size );
overror_t  __vf    cudaVPD_recall( pdVector X, ui size, FILE *stream );
overror_t  __vf    cudaVPD_store_buf( FILE *stream, pdVector d_X, ui size, pdVector h_Wk );
overror_t  __vf    cudaVPD_recall_buf( pdVector d_X, ui size, FILE *stream, pdVector h_Wk );
                     /* cudaVPD_store, cudaVPD_recall in binary format */


#ifdef __cplusplus
}  // end of extern "C"
#endif

/******************  VPDcu_ functions: **********************************
	act on host memory, using the CUDA device for processing
************************************************************************/


#ifdef __cplusplus
extern "C" {
#endif

/*******************  Initialization **********************************/

void  __vf OVCUAPI   VPDcu_equ0( pdVector X, ui size );
void  __vf OVCUAPI   VPDcu_equ1( pdVector X, ui size );
void  __vf OVCUAPI   VPDcu_equm1( pdVector X, ui size );
void  __vf OVCUAPI   VPDcu_equC( pdVector X, ui size, dPolar C );
void  __vf OVCUAPI   VPDcu_equV( pdVector Y, pdVector X, ui size ); /* copies from device to device */
void  __vf OVCUAPI   VPDcu_principal( pdVector Y, pdVector X, ui size );

void  __vf OVCUAPI   VDcu_PtoMagArg( dVector Mag, dVector Arg, pdVector X, ui size );
void  __vf OVCUAPI   VDcu_MagArgtoP( pdVector Y, dVector Mag, dVector Arg, ui size );
void  __vf OVCUAPI   VDcu_MagArgtoPrincipal( pdVector Y, dVector Mag, dVector Arg, ui size );
void  __vf OVCUAPI   VDcu_PtoMag( dVector Mag, pdVector X, ui size );
void  __vf OVCUAPI   VDcu_MagtoP( pdVector Y, dVector Mag, ui size );
void  __vf OVCUAPI   VDcu_PtoArg( dVector Arg, pdVector X, ui size );
void  __vf OVCUAPI   VDcu_ArgtoP( pdVector Y, dVector Arg, ui size );
void  __vf OVCUAPI   VDcu_CtoP( pdVector YP, cdVector XC, ui size );
void  __vf OVCUAPI   VDcu_PtoC( cdVector YC, pdVector XP, ui size );
void  __vf OVCUAPI   VDcu_PtoNorm( dVector Norm, pdVector X, ui size );
void  __vf OVCUAPI   VDcu_PtoReIm( dVector Re, dVector Im, pdVector X, ui size );
void  __vf OVCUAPI   VDcu_ReImtoP( pdVector Y, dVector Re, dVector Im, ui size );
void  __vf OVCUAPI   VDcu_PtoRe( dVector Re, pdVector X, ui size );
void  __vf OVCUAPI   VDcu_PtoIm( dVector Im, pdVector X, ui size );
#define     VPDcu_real( Y, X, sz )         VDcu_PtoRe( Y, X, sz )
#define     VPDcu_imag( Y, X, sz )         VDcu_PtoIm( Y, X, sz )
#define     VPDcu_arg( Y, X, sz )          VDcu_PtoArg( Y, X, sz )
#define     VPDcu_norm( Y, X, sz )         VDcu_PtoNorm( Y, X, sz )


/****************  Data-type interconversions  ***************************/

void  __vf OVCUAPI   Vcu_PFtoPD( pdVector Y, pfVector X, ui size );
void  __vf OVCUAPI   Vcu_PDtoPF( pfVector Y, pdVector X, ui size );

/****************  Index-oriented manipulations ***********************/

void  __vf OVCUAPI   VPDcu_delete( pdVector X, ui size, ui pos );
void  __vf OVCUAPI   VPDcu_insert( pdVector X, ui size, ui pos, dPolar C );
void  __vf OVCUAPI   VPDcu_reflect( pdVector X, ui size );
void  __vf OVCUAPI   VPDcu_rev( pdVector Y, pdVector X, ui size );
void  __vf OVCUAPI   VPDcu_rotate( pdVector Y, pdVector X, ui size, ssize_t pos );
void  __vf OVCUAPI   VPDcu_rotate_buf( pdVector Y, pdVector X, ui size, ssize_t pos, pdVector Buf );
  /* no V?cu_indpick, V?cu_indput possible! */
void  __vf OVCUAPI   VPDcu_subvector( pdVector Y, ui sizey, pdVector X, ssize_t samp );


/***************** Functions of a sub-set of elements  ********************/

void  __vf OVCUAPI   VPDcu_subvector_equC(  pdVector Y, ui subsiz, ui samp, dPolar C );
void  __vf OVCUAPI   VPDcu_subvector_equV(  pdVector Y, ui subsiz, ui samp, pdVector X );
    /*   for arithmetic functions of subsets, see <cudaVPDmath.h>  */


/**************** One-Dimensional Vector Operations ***********************/

double    __vf OVCUAPI   VPDcu_absmax(  pdVector X, ui size );
double    __vf OVCUAPI   VPDcu_absmin(  pdVector X, ui size );
double    __vf OVCUAPI   VPDcu_absmaxind( ui *pos, pdVector X, ui size );
double    __vf OVCUAPI   VPDcu_absminind( ui *pos, pdVector X, ui size );
#if defined __cplusplus && defined _CMATH_CLASSDEFS
} // the following function cannot be extern "C", if dPolar is a class
#endif
dPolar    __vf OVCUAPI   VPDcu_prod( pdVector X, ui size );
#if defined __cplusplus && defined _CMATH_CLASSDEFS
extern "C" {
#endif
void    __vf OVCUAPI   VPDcu_runprod( pdVector Y, pdVector X, ui size );

int     __vf OVCUAPI   VPDcu_iselementC( pdVector Tab, ui size, dPolar C );
ui      __vf OVCUAPI   VPDcu_iselementV( pdVector Y, pdVector X, ui sizex, pdVector Tab, ui sizetab );

#ifdef __cplusplus
}  // end of extern "C"
#endif

#endif /*  __CUDAVPDSTD_H */
