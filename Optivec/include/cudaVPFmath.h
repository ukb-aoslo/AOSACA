/*  cudaVPFmath.h

  vector management functions:
  arithmetic and math functions performed on each individual element
  of an array or vector of data type "fPolar"  (polar complex float)

  Copyright (c) 1996-2017 by OptiCode - Dr. Martin Sander Software Dev.
  All Rights Reserved.
*/

#ifndef __CUDAVPFMATH_H
#define __CUDAVPFMATH_H

#ifndef __CUDAVPFSTD_H
#include <cudaVPFstd.h>
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

/********************* Comparisons ****************************/

overror_t  __vcuf OVCUAPI   cudaVPF_cmp_eq0( ui *h_nTrue, pfVector Y, pfVector X, ui size );
overror_t  __vcuf OVCUAPI   cudaVPF_cmp_ne0( ui *h_nTrue, pfVector Y, pfVector X, ui size );
overror_t  __vcuf OVCUAPI   cusdVPF_cmp_eqC( ui *h_nTrue, pfVector Y, pfVector X, ui size, fPolar *d_C );
overror_t  __vcuf OVCUAPI   cusdVPF_cmp_neC( ui *h_nTrue, pfVector Y, pfVector X, ui size, fPolar *d_C );
overror_t  __vcuf OVCUAPI   cudaVPF_cmp_eqV( ui *h_nTrue, pfVector Z, pfVector X, pfVector Y, ui size );
overror_t  __vcuf OVCUAPI   cudaVPF_cmp_neV( ui *h_nTrue, pfVector Z, pfVector X, pfVector Y, ui size );

overror_t  __vcuf OVCUAPI   cudaVPF_cnt_eq0( ui *h_nTrue, pfVector X, ui size );
overror_t  __vcuf OVCUAPI   cudaVPF_cnt_ne0( ui *h_nTrue, pfVector X, ui size );
overror_t  __vcuf OVCUAPI   cusdVPF_cnt_eqC( ui *h_nTrue, pfVector X, ui size, fPolar *d_C );
overror_t  __vcuf OVCUAPI   cusdVPF_cnt_neC( ui *h_nTrue, pfVector X, ui size, fPolar *d_C );
overror_t  __vcuf OVCUAPI   cudaVPF_cnt_eqV( ui *h_nTrue, pfVector X, pfVector Y, ui size );
overror_t  __vcuf OVCUAPI   cudaVPF_cnt_neV( ui *h_nTrue, pfVector X, pfVector Y, ui size );
/*
overror_t  __vcuf OVCUAPI   cudaVPF_cmp_eq0ind( ui *h_nTrue, uiVector Ind, pfVector X, ui size );
overror_t  __vcuf OVCUAPI   cudaVPF_cmp_ne0ind( ui *h_nTrue, uiVector Ind, pfVector X, ui size );
overror_t  __vcuf OVCUAPI   cudaVPF_cmp_eqVind( ui *h_nTrue, uiVector Ind, pfVector X, pfVector Y, ui size );
overror_t  __vcuf OVCUAPI   cudaVPF_cmp_neVind( ui *h_nTrue, uiVector Ind, pfVector X, pfVector Y, ui size );
*/
#if defined __cplusplus && defined _CMATH_CLASSDEFS && defined __BORLANDC__ && defined _WIN64
} // cannot be extern "C" for C++Builder on Win64, if fPolar is a class
#endif
overror_t  __vcuf OVCUAPI   cudaVPF_cmp_eqC( ui *h_nTrue, pfVector Y, pfVector X, ui size, fPolar C );
overror_t  __vcuf OVCUAPI   cudaVPF_cmp_neC( ui *h_nTrue, pfVector Y, pfVector X, ui size, fPolar C );
overror_t  __vcuf OVCUAPI   cudaVPF_cnt_eqC( ui *h_nTrue, pfVector X, ui size, fPolar C );
overror_t  __vcuf OVCUAPI   cudaVPF_cnt_neC( ui *h_nTrue, pfVector X, ui size, fPolar C );
/*
overror_t  __vcuf OVCUAPI   cudaVPF_cmp_eqCind( ui *h_nTrue, uiVector Ind, pfVector X, ui size, fPolar C );
overror_t  __vcuf OVCUAPI   cudaVPF_cmp_neCind( ui *h_nTrue, uiVector Ind, pfVector X, ui size, fPolar C );
*/

/********************  Standard Arithmetics   ***************************/

overror_t  __vcuf OVCUAPI   cudaVPF_mulC(   pfVector Y, pfVector X, ui size, fPolar C );
overror_t  __vcuf OVCUAPI   cudaVPF_divC(   pfVector Y, pfVector X, ui size, fPolar C );
overror_t  __vcuf OVCUAPI   cudaVPF_divrC(  pfVector Y, pfVector X, ui size, fPolar C );

#if defined __cplusplus && defined _CMATH_CLASSDEFS && defined __BORLANDC__ && defined _WIN64
extern "C" {
#endif
overror_t  __vcuf OVCUAPI   cusdVPF_mulC(   pfVector Y, pfVector X, ui size, fPolar *d_C );
overror_t  __vcuf OVCUAPI   cusdVPF_divC(   pfVector Y, pfVector X, ui size, fPolar *d_C );
overror_t  __vcuf OVCUAPI   cusdVPF_divrC(  pfVector Y, pfVector X, ui size, fPolar *d_C );

overror_t  __vcuf OVCUAPI   cudaVPF_mulReC(  pfVector Y, pfVector X, ui size, float CRe );
overror_t  __vcuf OVCUAPI   cudaVPF_divReC(  pfVector Y, pfVector X, ui size, float CRe );
overror_t  __vcuf OVCUAPI   cudaVPF_divrReC( pfVector Y, pfVector X, ui size, float CRe );

overror_t  __vcuf OVCUAPI   cusdVPF_mulReC(  pfVector Y, pfVector X, ui size, float *d_CRe );
overror_t  __vcuf OVCUAPI   cusdVPF_divReC(  pfVector Y, pfVector X, ui size, float *d_CRe );
overror_t  __vcuf OVCUAPI   cusdVPF_divrReC( pfVector Y, pfVector X, ui size, float *d_CRe );

overror_t  __vcuf OVCUAPI   cudaVPF_mulV(  pfVector Z, pfVector X, pfVector Y, ui size );
overror_t  __vcuf OVCUAPI   cudaVPF_divV(  pfVector Z, pfVector X, pfVector Y, ui size );
overror_t  __vcuf OVCUAPI   cudaVPF_divrV( pfVector Z, pfVector X, pfVector Y, ui size );

overror_t  __vcuf OVCUAPI   cudaVPF_mulReV(  pfVector Z, pfVector X, fVector Y, ui size );
overror_t  __vcuf OVCUAPI   cudaVPF_divReV(  pfVector Z, pfVector X, fVector Y, ui size );
overror_t  __vcuf OVCUAPI   cudaVPF_divrReV( pfVector Z, pfVector X, fVector Y, ui size );


/*************** Functions of a sub-set of elements  ********************/

#if defined __cplusplus && defined _CMATH_CLASSDEFS && defined __BORLANDC__ && defined _WIN64
} // cannot be extern "C" for C++Builder on Win64, if fPolar is a class
#endif
overror_t  __vcuf OVCUAPI   cudaVPF_subvector_equC(  pfVector Y, ui subsiz, ui samp, fPolar C );
overror_t  __vcuf OVCUAPI   cudaVPF_subvector_mulC(  pfVector Y, ui subsiz, ui samp, fPolar C );
overror_t  __vcuf OVCUAPI   cudaVPF_subvector_divC(  pfVector Y, ui subsiz, ui samp, fPolar C );
overror_t  __vcuf OVCUAPI   cudaVPF_subvector_divrC( pfVector Y, ui subsiz, ui samp, fPolar C );

#if defined __cplusplus && defined _CMATH_CLASSDEFS && defined __BORLANDC__ && defined _WIN64
extern "C" {
#endif
overror_t  __vcuf OVCUAPI   cusdVPF_subvector_equC(  pfVector Y, ui subsiz, ui samp, fPolar *d_C );
overror_t  __vcuf OVCUAPI   cusdVPF_subvector_mulC(  pfVector Y, ui subsiz, ui samp, fPolar *d_C );
overror_t  __vcuf OVCUAPI   cusdVPF_subvector_divC(  pfVector Y, ui subsiz, ui samp, fPolar *d_C );
overror_t  __vcuf OVCUAPI   cusdVPF_subvector_divrC( pfVector Y, ui subsiz, ui samp, fPolar *d_C );

overror_t  __vcuf OVCUAPI   cudaVPF_subvector_equV(  pfVector Y, ui subsiz, ui samp, pfVector X );
overror_t  __vcuf OVCUAPI   cudaVPF_subvector_mulV(  pfVector Y, ui subsiz, ui samp, pfVector X );
overror_t  __vcuf OVCUAPI   cudaVPF_subvector_divV(  pfVector Y, ui subsiz, ui samp, pfVector X );
overror_t  __vcuf OVCUAPI   cudaVPF_subvector_divrV( pfVector Y, ui subsiz, ui samp, pfVector X );


/*********************  Mathematical Functions *************************/

overror_t  __vcuf OVCUAPI   cudaVPF_neg(  pfVector Y, pfVector X, ui size );
overror_t  __vcuf OVCUAPI   cudaVPF_conj( pfVector Y, pfVector X, ui size );
#define        cudaVPF_abs        cudaVF_PtoMag
overror_t  __vcuf OVCUAPI   cudaVPF_inv(  pfVector Y, pfVector X, ui size );

overror_t  __vcuf OVCUAPI   cudaVPF_square(  pfVector Y, pfVector X, ui size );
overror_t  __vcuf OVCUAPI   cudaVPF_cubic(   pfVector Y, pfVector X, ui size );
overror_t  __vcuf OVCUAPI   cudaVPF_quartic( pfVector Y, pfVector X, ui size );
overror_t  __vcuf OVCUAPI   cudaVPF_ipow(    pfVector Y, pfVector X, ui size, int ipow );

    /* extra fast integer powers: "unprotected", without error handling: */
overror_t  __vcuf OVCUAPI   cudaVPFu_square(   pfVector Y, pfVector X, ui size );
overror_t  __vcuf OVCUAPI   cudaVPFu_cubic(    pfVector Y, pfVector X, ui size );
overror_t  __vcuf OVCUAPI   cudaVPFu_quartic(  pfVector Y, pfVector X, ui size );
overror_t  __vcuf OVCUAPI   cudaVPFu_ipow(     pfVector Y, pfVector X, ui size, int ipow );

overror_t  __vcuf OVCUAPI   cudaVPF_powReExpo(  pfVector Y, pfVector X, ui size, float Expo );
overror_t  __vcuf OVCUAPI   cudaVPF_sqrt(  pfVector Y, pfVector X, ui size );
overror_t  __vcuf OVCUAPI   cudaVPF_logtoC(   cfVector Y, pfVector X, ui size );
overror_t  __vcuf OVCUAPI   cudaVPF_log2toC(  cfVector Y, pfVector X, ui size );
overror_t  __vcuf OVCUAPI   cudaVPF_log10toC( cfVector Y, pfVector X, ui size );
#define     cudaVPF_lntoC   cudaVPF_logtoC

overror_t  __vcuf OVCUAPI   cudaVCF_exptoP(  pfVector Y, cfVector X, ui size );

#ifdef __cplusplus
}  // end of extern "C"
#endif


/******************  VPFcu_ functions: **********************************
	act on host memory, using the CUDA device for processing
************************************************************************/


#ifdef __cplusplus
extern "C" {
#endif

/********************* Comparisons ****************************/

ui   __vf OVCUAPI   VPFcu_cmp_eq0( pfVector Y, pfVector X, ui size );
ui   __vf OVCUAPI   VPFcu_cmp_ne0( pfVector Y, pfVector X, ui size );
ui   __vf OVCUAPI   VPFcu_cmp_eqV( pfVector Z, pfVector X, pfVector Y, ui size );
ui   __vf OVCUAPI   VPFcu_cmp_neV( pfVector Z, pfVector X, pfVector Y, ui size );
ui   __vf OVCUAPI   VPFcu_cnt_eq0( pfVector X, ui size );
ui   __vf OVCUAPI   VPFcu_cnt_ne0( pfVector X, ui size );
ui   __vf OVCUAPI   VPFcu_cnt_eqV( pfVector X, pfVector Y, ui size );
ui   __vf OVCUAPI   VPFcu_cnt_neV( pfVector X, pfVector Y, ui size );
/*
ui   __vf OVCUAPI   VPFcu_cmp_eq0ind( uiVector Ind, pfVector X, ui size );
ui   __vf OVCUAPI   VPFcu_cmp_ne0ind( uiVector Ind, pfVector X, ui size );
ui   __vf OVCUAPI   VPFcu_cmp_eqVind( uiVector Ind, pfVector X, pfVector Y, ui size );
ui   __vf OVCUAPI   VPFcu_cmp_neVind( uiVector Ind, pfVector X, pfVector Y, ui size );
*/
#if defined __cplusplus && defined _CMATH_CLASSDEFS && defined __BORLANDC__ && defined _WIN64
} // cannot be extern "C" for C++Builder on Win64, if fPolar is a class
#endif
ui   __vf OVCUAPI   VPFcu_cmp_eqC( pfVector Y, pfVector X, ui size, fPolar C );
ui   __vf OVCUAPI   VPFcu_cmp_neC( pfVector Y, pfVector X, ui size, fPolar C );
ui   __vf OVCUAPI   VPFcu_cnt_eqC( pfVector X, ui size, fPolar C );
ui   __vf OVCUAPI   VPFcu_cnt_neC( pfVector X, ui size, fPolar C );
/*
ui   __vf OVCUAPI   VPFcu_cmp_eqCind( uiVector Ind, pfVector X, ui size, fPolar C );
ui   __vf OVCUAPI   VPFcu_cmp_neCind( uiVector Ind, pfVector X, ui size, fPolar C );
*/

/********************  Standard Arithmetics   ***************************/

void  __vf OVCUAPI   VPFcu_mulC(   pfVector Y, pfVector X, ui size, fPolar C );
void  __vf OVCUAPI   VPFcu_divC(   pfVector Y, pfVector X, ui size, fPolar C );
void  __vf OVCUAPI   VPFcu_divrC(  pfVector Y, pfVector X, ui size, fPolar C );

#if defined __cplusplus && defined _CMATH_CLASSDEFS && defined __BORLANDC__ && defined _WIN64
extern "C" {
#endif

void  __vf OVCUAPI   VPFcu_mulReC(  pfVector Y, pfVector X, ui size, float CRe );
void  __vf OVCUAPI   VPFcu_divReC(  pfVector Y, pfVector X, ui size, float CRe );
void  __vf OVCUAPI   VPFcu_divrReC( pfVector Y, pfVector X, ui size, float CRe );

void  __vf OVCUAPI   VPFcu_mulV(  pfVector Z, pfVector X, pfVector Y, ui size );
void  __vf OVCUAPI   VPFcu_divV(  pfVector Z, pfVector X, pfVector Y, ui size );
void  __vf OVCUAPI   VPFcu_divrV( pfVector Z, pfVector X, pfVector Y, ui size );

void  __vf OVCUAPI   VPFcu_mulReV(  pfVector Z, pfVector X, fVector Y, ui size );
void  __vf OVCUAPI   VPFcu_divReV(  pfVector Z, pfVector X, fVector Y, ui size );
void  __vf OVCUAPI   VPFcu_divrReV( pfVector Z, pfVector X, fVector Y, ui size );


/*************** Functions of a sub-set of elements  ********************/

#if defined __cplusplus && defined _CMATH_CLASSDEFS && defined __BORLANDC__ && defined _WIN64
} // cannot be extern "C" for C++Builder on Win64, if fPolar is a class
#endif
void  __vf OVCUAPI   VPFcu_subvector_equC(  pfVector Y, ui subsiz, ui samp, fPolar C );
void  __vf OVCUAPI   VPFcu_subvector_mulC(  pfVector Y, ui subsiz, ui samp, fPolar C );
void  __vf OVCUAPI   VPFcu_subvector_divC(  pfVector Y, ui subsiz, ui samp, fPolar C );
void  __vf OVCUAPI   VPFcu_subvector_divrC( pfVector Y, ui subsiz, ui samp, fPolar C );

#if defined __cplusplus && defined _CMATH_CLASSDEFS && defined __BORLANDC__ && defined _WIN64
extern "C" {
#endif

void  __vf OVCUAPI   VPFcu_subvector_equV(  pfVector Y, ui subsiz, ui samp, pfVector X );
void  __vf OVCUAPI   VPFcu_subvector_mulV(  pfVector Y, ui subsiz, ui samp, pfVector X );
void  __vf OVCUAPI   VPFcu_subvector_divV(  pfVector Y, ui subsiz, ui samp, pfVector X );
void  __vf OVCUAPI   VPFcu_subvector_divrV( pfVector Y, ui subsiz, ui samp, pfVector X );


/*********************  Mathematical Functions *************************/

int   __vf OVCUAPI   VPFcu_abs(  fVector Y, pfVector X, ui size );
int   __vf OVCUAPI   VPFcu_neg(  pfVector Y, pfVector X, ui size );
int   __vf OVCUAPI   VPFcu_conj( pfVector Y, pfVector X, ui size );
int   __vf OVCUAPI   VPFcu_inv(  pfVector Y, pfVector X, ui size );

int  __vf OVCUAPI   VPFcu_square(  pfVector Y, pfVector X, ui size );
int  __vf OVCUAPI   VPFcu_cubic(   pfVector Y, pfVector X, ui size );
int  __vf OVCUAPI   VPFcu_quartic( pfVector Y, pfVector X, ui size );
int  __vf OVCUAPI   VPFcu_ipow(    pfVector Y, pfVector X, ui size, int ipow );

    /* extra fast integer powers: "unprotected", without error handling: */
int  __vf OVCUAPI   VPFucu_square(   pfVector Y, pfVector X, ui size );
int  __vf OVCUAPI   VPFucu_cubic(    pfVector Y, pfVector X, ui size );
int  __vf OVCUAPI   VPFucu_quartic(  pfVector Y, pfVector X, ui size );
int  __vf OVCUAPI   VPFucu_ipow(     pfVector Y, pfVector X, ui size, int ipow );

int  __vf OVCUAPI   VPFcu_powReExpo(  pfVector Y, pfVector X, ui size, float Expo );
int  __vf OVCUAPI   VPFcu_sqrt(  pfVector Y, pfVector X, ui size );
int  __vf OVCUAPI   VPFcu_logtoC(   cfVector Y, pfVector X, ui size );
int  __vf OVCUAPI   VPFcu_log2toC(  cfVector Y, pfVector X, ui size );
int  __vf OVCUAPI   VPFcu_log10toC( cfVector Y, pfVector X, ui size );
#define     VPFcu_lntoC   VPFcu_logtoC

int  __vf OVCUAPI   VCFcu_exptoP(  pfVector Y, cfVector X, ui size );

#ifdef __cplusplus
}  // end of extern "C"
#endif


#endif /* __cudaVPFMATH_H */
