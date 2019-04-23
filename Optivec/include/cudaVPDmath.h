/*  cudaVPDmath.h

  vector management functions:
  arithmetic and math functions performed on each individual element
  of an array or vector of data type "dPolar"  (polar complex double)

  Copyright (c) 1996-2017 by OptiCode - Dr. Martin Sander Software Dev.
  All Rights Reserved.
*/

#ifndef __CUDAVPDMATH_H
#define __CUDAVPDMATH_H

#ifndef __CUDAVPDSTD_H
#include <cudaVPDstd.h>
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

/********************* Comparisons ****************************/

overror_t  __vcuf OVCUAPI   cudaVPD_cmp_eq0( ui *h_nTrue, pdVector Y, pdVector X, ui size );
overror_t  __vcuf OVCUAPI   cudaVPD_cmp_ne0( ui *h_nTrue, pdVector Y, pdVector X, ui size );
overror_t  __vcuf OVCUAPI   cudaVPD_cmp_eqC( ui *h_nTrue, pdVector Y, pdVector X, ui size, dPolar C );
overror_t  __vcuf OVCUAPI   cudaVPD_cmp_neC( ui *h_nTrue, pdVector Y, pdVector X, ui size, dPolar C );
overror_t  __vcuf OVCUAPI   cusdVPD_cmp_eqC( ui *h_nTrue, pdVector Y, pdVector X, ui size, dPolar *d_C );
overror_t  __vcuf OVCUAPI   cusdVPD_cmp_neC( ui *h_nTrue, pdVector Y, pdVector X, ui size, dPolar *d_C );
overror_t  __vcuf OVCUAPI   cudaVPD_cmp_eqV( ui *h_nTrue, pdVector Z, pdVector X, pdVector Y, ui size );
overror_t  __vcuf OVCUAPI   cudaVPD_cmp_neV( ui *h_nTrue, pdVector Z, pdVector X, pdVector Y, ui size );
overror_t  __vcuf OVCUAPI   cudaVPD_cmp_eq0ind( ui *h_nTrue, uiVector Ind, pdVector X, ui size );
overror_t  __vcuf OVCUAPI   cudaVPD_cmp_ne0ind( ui *h_nTrue, uiVector Ind, pdVector X, ui size );

overror_t  __vcuf OVCUAPI   cudaVPD_cnt_eq0( ui *h_nTrue, pdVector X, ui size );
overror_t  __vcuf OVCUAPI   cudaVPD_cnt_ne0( ui *h_nTrue, pdVector X, ui size );
overror_t  __vcuf OVCUAPI   cudaVPD_cnt_eqC( ui *h_nTrue, pdVector X, ui size, dPolar C );
overror_t  __vcuf OVCUAPI   cudaVPD_cnt_neC( ui *h_nTrue, pdVector X, ui size, dPolar C );
overror_t  __vcuf OVCUAPI   cusdVPD_cnt_eqC( ui *h_nTrue, pdVector X, ui size, dPolar *d_C );
overror_t  __vcuf OVCUAPI   cusdVPD_cnt_neC( ui *h_nTrue, pdVector X, ui size, dPolar *d_C );
overror_t  __vcuf OVCUAPI   cudaVPD_cnt_eqV( ui *h_nTrue, pdVector X, pdVector Y, ui size );
overror_t  __vcuf OVCUAPI   cudaVPD_cnt_neV( ui *h_nTrue, pdVector X, pdVector Y, ui size );
overror_t  __vcuf OVCUAPI   cudaVPD_cnt_eq0ind( ui *h_nTrue, uiVector Ind, pdVector X, ui size );
overror_t  __vcuf OVCUAPI   cudaVPD_cnt_ne0ind( ui *h_nTrue, uiVector Ind, pdVector X, ui size );
/*
overror_t  __vcuf OVCUAPI   cudaVPD_cmp_eqCind( ui *h_nTrue, uiVector Ind, pdVector X, ui size, dPolar C );
overror_t  __vcuf OVCUAPI   cudaVPD_cmp_neCind( ui *h_nTrue, uiVector Ind, pdVector X, ui size, dPolar C );
overror_t  __vcuf OVCUAPI   cusdVPD_cmp_eqCind( ui *h_nTrue, uiVector Ind, pdVector X, ui size, dPolar *d_C );
overror_t  __vcuf OVCUAPI   cusdVPD_cmp_neCind( ui *h_nTrue, uiVector Ind, pdVector X, ui size, dPolar *d_C );
overror_t  __vcuf OVCUAPI   cudaVPD_cmp_eqVind( ui *h_nTrue, uiVector Ind, pdVector X, pdVector Y, ui size );
overror_t  __vcuf OVCUAPI   cudaVPD_cmp_neVind( ui *h_nTrue, uiVector Ind, pdVector X, pdVector Y, ui size );
*/

/********************  Standard Arithmetics   ***************************/

overror_t  __vcuf OVCUAPI   cudaVPD_mulC(   pdVector Y, pdVector X, ui size, dPolar C );
overror_t  __vcuf OVCUAPI   cudaVPD_divC(   pdVector Y, pdVector X, ui size, dPolar C );
overror_t  __vcuf OVCUAPI   cudaVPD_divrC(  pdVector Y, pdVector X, ui size, dPolar C );

overror_t  __vcuf OVCUAPI   cusdVPD_mulC(   pdVector Y, pdVector X, ui size, dPolar *d_C );
overror_t  __vcuf OVCUAPI   cusdVPD_divC(   pdVector Y, pdVector X, ui size, dPolar *d_C );
overror_t  __vcuf OVCUAPI   cusdVPD_divrC(  pdVector Y, pdVector X, ui size, dPolar *d_C );

overror_t  __vcuf OVCUAPI   cudaVPD_mulReC(  pdVector Y, pdVector X, ui size, double CRe );
overror_t  __vcuf OVCUAPI   cudaVPD_divReC(  pdVector Y, pdVector X, ui size, double CRe );
overror_t  __vcuf OVCUAPI   cudaVPD_divrReC( pdVector Y, pdVector X, ui size, double CRe );

overror_t  __vcuf OVCUAPI   cusdVPD_mulReC(  pdVector Y, pdVector X, ui size, double *d_CRe );
overror_t  __vcuf OVCUAPI   cusdVPD_divReC(  pdVector Y, pdVector X, ui size, double *d_CRe );
overror_t  __vcuf OVCUAPI   cusdVPD_divrReC( pdVector Y, pdVector X, ui size, double *d_CRe );

overror_t  __vcuf OVCUAPI   cudaVPD_mulV(  pdVector Z, pdVector X, pdVector Y, ui size );
overror_t  __vcuf OVCUAPI   cudaVPD_divV(  pdVector Z, pdVector X, pdVector Y, ui size );
overror_t  __vcuf OVCUAPI   cudaVPD_divrV( pdVector Z, pdVector X, pdVector Y, ui size );

overror_t  __vcuf OVCUAPI   cudaVPD_mulReV(  pdVector Z, pdVector X, dVector Y, ui size );
overror_t  __vcuf OVCUAPI   cudaVPD_divReV(  pdVector Z, pdVector X, dVector Y, ui size );
overror_t  __vcuf OVCUAPI   cudaVPD_divrReV( pdVector Z, pdVector X, dVector Y, ui size );


/*************** Functions of a sub-set of elements  ********************/

overror_t  __vcuf OVCUAPI   cudaVPD_subvector_equC(  pdVector Y, ui subsiz, ui samp, dPolar C );
overror_t  __vcuf OVCUAPI   cusdVPD_subvector_equC(  pdVector Y, ui subsiz, ui samp, dPolar *d_C );
overror_t  __vcuf OVCUAPI   cudaVPD_subvector_equV(  pdVector Y, ui subsiz, ui samp, pdVector X );

overror_t  __vcuf OVCUAPI   cudaVPD_subvector_mulC(  pdVector Y, ui subsiz, ui samp, dPolar C );
overror_t  __vcuf OVCUAPI   cudaVPD_subvector_divC(  pdVector Y, ui subsiz, ui samp, dPolar C );
overror_t  __vcuf OVCUAPI   cudaVPD_subvector_divrC( pdVector Y, ui subsiz, ui samp, dPolar C );

overror_t  __vcuf OVCUAPI   cusdVPD_subvector_mulC(  pdVector Y, ui subsiz, ui samp, dPolar *d_C );
overror_t  __vcuf OVCUAPI   cusdVPD_subvector_divC(  pdVector Y, ui subsiz, ui samp, dPolar *d_C );
overror_t  __vcuf OVCUAPI   cusdVPD_subvector_divrC( pdVector Y, ui subsiz, ui samp, dPolar *d_C );

overror_t  __vcuf OVCUAPI   cudaVPD_subvector_mulV(  pdVector Y, ui subsiz, ui samp, pdVector X );
overror_t  __vcuf OVCUAPI   cudaVPD_subvector_divV(  pdVector Y, ui subsiz, ui samp, pdVector X );
overror_t  __vcuf OVCUAPI   cudaVPD_subvector_divrV( pdVector Y, ui subsiz, ui samp, pdVector X );


/*********************  Mathematical Functions *************************/

overror_t  __vcuf OVCUAPI   cudaVPD_neg(  pdVector Y, pdVector X, ui size );
overror_t  __vcuf OVCUAPI   cudaVPD_conj( pdVector Y, pdVector X, ui size );
#define        cudaVPD_abs        cudaVD_PtoMag
overror_t  __vcuf OVCUAPI   cudaVPD_inv(  pdVector Y, pdVector X, ui size );

overror_t  __vcuf OVCUAPI   cudaVPD_square(  pdVector Y, pdVector X, ui size );
overror_t  __vcuf OVCUAPI   cudaVPD_cubic(   pdVector Y, pdVector X, ui size );
overror_t  __vcuf OVCUAPI   cudaVPD_quartic( pdVector Y, pdVector X, ui size );
overror_t  __vcuf OVCUAPI   cudaVPD_ipow(    pdVector Y, pdVector X, ui size, int ipow );

    /* extra fast integer powers: "unprotected", without error handling: */
overror_t  __vcuf OVCUAPI   cudaVPDu_square(   pdVector Y, pdVector X, ui size );
overror_t  __vcuf OVCUAPI   cudaVPDu_cubic(    pdVector Y, pdVector X, ui size );
overror_t  __vcuf OVCUAPI   cudaVPDu_quartic(  pdVector Y, pdVector X, ui size );
overror_t  __vcuf OVCUAPI   cudaVPDu_ipow(     pdVector Y, pdVector X, ui size, int ipow );

overror_t  __vcuf OVCUAPI   cudaVPD_powReExpo(  pdVector Y, pdVector X, ui size, double Expo );
overror_t  __vcuf OVCUAPI   cudaVPD_sqrt(  pdVector Y, pdVector X, ui size );
overror_t  __vcuf OVCUAPI   cudaVPD_logtoC(   cdVector Y, pdVector X, ui size );
overror_t  __vcuf OVCUAPI   cudaVPD_log2toC(  cdVector Y, pdVector X, ui size );
overror_t  __vcuf OVCUAPI   cudaVPD_log10toC( cdVector Y, pdVector X, ui size );
#define     cudaVPD_lntoC   cudaVPD_logtoC

overror_t  __vcuf OVCUAPI   cudaVCD_exptoP(  pdVector Y, cdVector X, ui size );

#ifdef __cplusplus
}  // end of extern "C"
#endif


/******************  VPDcu_ functions: **********************************
	act on host memory, using the CUDA device for processing
************************************************************************/


#ifdef __cplusplus
extern "C" {
#endif

/********************* Comparisons ****************************/

ui   __vf OVCUAPI   VPDcu_cmp_eq0( pdVector Y, pdVector X, ui size );
ui   __vf OVCUAPI   VPDcu_cmp_ne0( pdVector Y, pdVector X, ui size );
ui   __vf OVCUAPI   VPDcu_cmp_eqC( pdVector Y, pdVector X, ui size, dPolar C );
ui   __vf OVCUAPI   VPDcu_cmp_neC( pdVector Y, pdVector X, ui size, dPolar C );
ui   __vf OVCUAPI   VPDcu_cmp_eqV( pdVector Z, pdVector X, pdVector Y, ui size );
ui   __vf OVCUAPI   VPDcu_cmp_neV( pdVector Z, pdVector X, pdVector Y, ui size );
ui   __vf OVCUAPI   VPDcu_cmp_eq0ind( uiVector Ind, pdVector X, ui size );
ui   __vf OVCUAPI   VPDcu_cmp_ne0ind( uiVector Ind, pdVector X, ui size );
ui   __vf OVCUAPI   VPDcu_cnt_eq0( pdVector X, ui size );
ui   __vf OVCUAPI   VPDcu_cnt_ne0( pdVector X, ui size );
ui   __vf OVCUAPI   VPDcu_cnt_eqC( pdVector X, ui size, dPolar C );
ui   __vf OVCUAPI   VPDcu_cnt_neC( pdVector X, ui size, dPolar C );
ui   __vf OVCUAPI   VPDcu_cnt_eqV( pdVector X, pdVector Y, ui size );
ui   __vf OVCUAPI   VPDcu_cnt_neV( pdVector X, pdVector Y, ui size );
/*
ui   __vf OVCUAPI   VPDcu_cmp_eqCind( uiVector Ind, pdVector X, ui size, dPolar C );
ui   __vf OVCUAPI   VPDcu_cmp_neCind( uiVector Ind, pdVector X, ui size, dPolar C );
ui   __vf OVCUAPI   VPDcu_cmp_eqVind( uiVector Ind, pdVector X, pdVector Y, ui size );
ui   __vf OVCUAPI   VPDcu_cmp_neVind( uiVector Ind, pdVector X, pdVector Y, ui size );
*/

/********************  Standard Arithmetics   ***************************/

void  __vf OVCUAPI   VPDcu_mulC(   pdVector Y, pdVector X, ui size, dPolar C );
void  __vf OVCUAPI   VPDcu_divC(   pdVector Y, pdVector X, ui size, dPolar C );
void  __vf OVCUAPI   VPDcu_divrC(  pdVector Y, pdVector X, ui size, dPolar C );

void  __vf OVCUAPI   VPDcu_mulReC(  pdVector Y, pdVector X, ui size, double CRe );
void  __vf OVCUAPI   VPDcu_divReC(  pdVector Y, pdVector X, ui size, double CRe );
void  __vf OVCUAPI   VPDcu_divrReC( pdVector Y, pdVector X, ui size, double CRe );

void  __vf OVCUAPI   VPDcu_mulV(  pdVector Z, pdVector X, pdVector Y, ui size );
void  __vf OVCUAPI   VPDcu_divV(  pdVector Z, pdVector X, pdVector Y, ui size );
void  __vf OVCUAPI   VPDcu_divrV( pdVector Z, pdVector X, pdVector Y, ui size );

void  __vf OVCUAPI   VPDcu_mulReV(  pdVector Z, pdVector X, dVector Y, ui size );
void  __vf OVCUAPI   VPDcu_divReV(  pdVector Z, pdVector X, dVector Y, ui size );
void  __vf OVCUAPI   VPDcu_divrReV( pdVector Z, pdVector X, dVector Y, ui size );


/*************** Functions of a sub-set of elements  ********************/

void  __vf OVCUAPI   VPDcu_subvector_equC(  pdVector Y, ui subsiz, ui samp, dPolar C );
void  __vf OVCUAPI   VPDcu_subvector_equV(  pdVector Y, ui subsiz, ui samp, pdVector X );

void  __vf OVCUAPI   VPDcu_subvector_mulC(  pdVector Y, ui subsiz, ui samp, dPolar C );
void  __vf OVCUAPI   VPDcu_subvector_divC(  pdVector Y, ui subsiz, ui samp, dPolar C );
void  __vf OVCUAPI   VPDcu_subvector_divrC( pdVector Y, ui subsiz, ui samp, dPolar C );

void  __vf OVCUAPI   VPDcu_subvector_mulV(  pdVector Y, ui subsiz, ui samp, pdVector X );
void  __vf OVCUAPI   VPDcu_subvector_divV(  pdVector Y, ui subsiz, ui samp, pdVector X );
void  __vf OVCUAPI   VPDcu_subvector_divrV( pdVector Y, ui subsiz, ui samp, pdVector X );


/*********************  Mathematical Functions *************************/

int   __vf OVCUAPI   VPDcu_abs(   dVector Y, pdVector X, ui size );
int   __vf OVCUAPI   VPDcu_neg(  pdVector Y, pdVector X, ui size );
int   __vf OVCUAPI   VPDcu_conj( pdVector Y, pdVector X, ui size );
int   __vf OVCUAPI   VPDcu_inv(  pdVector Y, pdVector X, ui size );

int  __vf OVCUAPI   VPDcu_square(  pdVector Y, pdVector X, ui size );
int  __vf OVCUAPI   VPDcu_cubic(   pdVector Y, pdVector X, ui size );
int  __vf OVCUAPI   VPDcu_quartic( pdVector Y, pdVector X, ui size );
int  __vf OVCUAPI   VPDcu_ipow(    pdVector Y, pdVector X, ui size, int ipow );

    /* extra fast integer powers: "unprotected", without error handling: */
int  __vf OVCUAPI   VPDucu_square(   pdVector Y, pdVector X, ui size );
int  __vf OVCUAPI   VPDucu_cubic(    pdVector Y, pdVector X, ui size );
int  __vf OVCUAPI   VPDucu_quartic(  pdVector Y, pdVector X, ui size );
int  __vf OVCUAPI   VPDucu_ipow(     pdVector Y, pdVector X, ui size, int ipow );

int  __vf OVCUAPI   VPDcu_powReExpo(  pdVector Y, pdVector X, ui size, double Expo );
int  __vf OVCUAPI   VPDcu_sqrt(  pdVector Y, pdVector X, ui size );
int  __vf OVCUAPI   VPDcu_logtoC(   cdVector Y, pdVector X, ui size );
int  __vf OVCUAPI   VPDcu_log2toC(  cdVector Y, pdVector X, ui size );
int  __vf OVCUAPI   VPDcu_log10toC( cdVector Y, pdVector X, ui size );
#define     VPDcu_lntoC   VPDcu_logtoC

int  __vf OVCUAPI   VCDcu_exptoP(  pdVector Y, cdVector X, ui size );

#ifdef __cplusplus
}  // end of extern "C"
#endif


#endif /* __cudaVPDMATH_H */
