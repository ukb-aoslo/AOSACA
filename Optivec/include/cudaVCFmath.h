/*  cudaVCFmath.h

  vector management functions:
  math functions performed on each individual element of an
  array or vector of data type "fComplex" (complex float)

  Copyright (c) 1996-2017 by OptiCode - Dr. Martin Sander Software Dev.
  All Rights Reserved.
*/

#ifndef __CUDAVCFMATH_H
#define __CUDAVCFMATH_H

#ifndef __CUDAVCFSTD_H 
#include <cudaVCFstd.h>
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

/************************* Comparisons ****************************/

overror_t  __vcuf OVCUAPI   cudaVCF_cmp_eq0( ui *h_nTrue, cfVector Y, cfVector X, ui size );
overror_t  __vcuf OVCUAPI   cudaVCF_cmp_ne0( ui *h_nTrue, cfVector Y, cfVector X, ui size );
overror_t  __vcuf OVCUAPI   cusdVCF_cmp_eqC( ui *h_nTrue, cfVector Y, cfVector X, ui size, fComplex *d_C );
overror_t  __vcuf OVCUAPI   cusdVCF_cmp_neC( ui *h_nTrue, cfVector Y, cfVector X, ui size, fComplex *d_C );
overror_t  __vcuf OVCUAPI   cudaVCF_cmp_eqV( ui *h_nTrue, cfVector Z, cfVector X, cfVector Y, ui size );
overror_t  __vcuf OVCUAPI   cudaVCF_cmp_neV( ui *h_nTrue, cfVector Z, cfVector X, cfVector Y, ui size );

overror_t  __vcuf OVCUAPI   cudaVCF_cnt_eq0( ui *h_nTrue, cfVector X, ui size );
overror_t  __vcuf OVCUAPI   cudaVCF_cnt_ne0( ui *h_nTrue, cfVector X, ui size );
overror_t  __vcuf OVCUAPI   cusdVCF_cnt_eqC( ui *h_nTrue, cfVector X, ui size, fComplex *d_C );
overror_t  __vcuf OVCUAPI   cusdVCF_cnt_neC( ui *h_nTrue, cfVector X, ui size, fComplex *d_C );
overror_t  __vcuf OVCUAPI   cudaVCF_cnt_eqV( ui *h_nTrue, cfVector X, cfVector Y, ui size );
overror_t  __vcuf OVCUAPI   cudaVCF_cnt_neV( ui *h_nTrue, cfVector X, cfVector Y, ui size );

/*
overror_t  __vcuf OVCUAPI   cudaVCF_cmp_eq0ind( ui *h_nTrue, uiVector Ind, cfVector X, ui size );
overror_t  __vcuf OVCUAPI   cudaVCF_cmp_ne0ind( ui *h_nTrue, uiVector Ind, cfVector X, ui size );
overror_t  __vcuf OVCUAPI   cusdVCF_cmp_eqCind( ui *h_nTrue, uiVector Ind, cfVector X, ui size, fComplex *d_C );
overror_t  __vcuf OVCUAPI   cusdVCF_cmp_neCind( ui *h_nTrue, uiVector Ind, cfVector X, ui size, fComplex *d_C );
overror_t  __vcuf OVCUAPI   cudaVCF_cmp_eqVind( ui *h_nTrue, uiVector Ind, cfVector X, cfVector Y, ui size );
overror_t  __vcuf OVCUAPI   cudaVCF_cmp_neVind( ui *h_nTrue, uiVector Ind, cfVector X, cfVector Y, ui size );
*/

#if defined __cplusplus && defined _CMATH_CLASSDEFS && defined __BORLANDC__ && defined _WIN64
} // cannot be extern "C" for C++Builder on Win64, if fComplex is a class
#endif
overror_t  __vcuf OVCUAPI_ifNotBC64Class   cudaVCF_cmp_eqC( ui *h_nTrue, cfVector Y, cfVector X, ui size, fComplex C );
overror_t  __vcuf OVCUAPI_ifNotBC64Class   cudaVCF_cmp_neC( ui *h_nTrue, cfVector Y, cfVector X, ui size, fComplex C );
overror_t  __vcuf OVCUAPI_ifNotBC64Class   cudaVCF_cnt_eqC( ui *h_nTrue, cfVector X, ui size, fComplex C );
overror_t  __vcuf OVCUAPI_ifNotBC64Class   cudaVCF_cnt_neC( ui *h_nTrue, cfVector X, ui size, fComplex C );
/*
overror_t  __vcuf OVCUAPI   cudaVCF_cmp_eqCind( ui *h_nTrue, uiVector Ind, cfVector X, ui size, fComplex C );
overror_t  __vcuf OVCUAPI   cudaVCF_cmp_neCind( ui *h_nTrue, uiVector Ind, cfVector X, ui size, fComplex C );
*/

/********************  Standard Arithmetics   ***************************/

overror_t  __vcuf OVCUAPI_ifNotBC64Class   cudaVCF_limit(  cfVector Y, cfVector X, ui size, fComplex Min, fComplex Max );
overror_t  __vcuf OVCUAPI_ifNotBC64Class   cudaVCF_flush0( cfVector Y, cfVector X, ui size, fComplex AbsMin );
overror_t  __vcuf OVCUAPI_ifNotBC64Class   cudaVCF_flushInv( cfVector Y, cfVector X, ui size, fComplex AbsMin );
overror_t  __vcuf OVCUAPI_ifNotBC64Class   cudaVCF_replaceNAN( cfVector Y, cfVector X, ui size, fComplex C );

overror_t  __vcuf OVCUAPI_ifNotBC64Class   cudaVCFx_equV( cfVector Y, cfVector X, ui size, fComplex A, fComplex B );
overror_t  __vcuf OVCUAPI_ifNotBC64Class   cudaVCF_addC(  cfVector Y, cfVector X, ui size, fComplex C );
overror_t  __vcuf OVCUAPI_ifNotBC64Class   cudaVCF_subC(  cfVector Y, cfVector X, ui size, fComplex C );
overror_t  __vcuf OVCUAPI_ifNotBC64Class   cudaVCF_subrC( cfVector Y, cfVector X, ui size, fComplex C );
overror_t  __vcuf OVCUAPI_ifNotBC64Class   cudaVCF_mulC(  cfVector Y, cfVector X, ui size, fComplex C );
overror_t  __vcuf OVCUAPI_ifNotBC64Class   cudaVCF_divC(  cfVector Y, cfVector X, ui size, fComplex C );
overror_t  __vcuf OVCUAPI_ifNotBC64Class   cudaVCF_divrC( cfVector Y, cfVector X, ui size, fComplex C );
overror_t  __vcuf OVCUAPI_ifNotBC64Class   cudaVCFx_divrC( cfVector Y, cfVector X, ui size, fComplex A, fComplex B, fComplex C );

#if defined __cplusplus && defined _CMATH_CLASSDEFS && defined __BORLANDC__ && defined _WIN64
extern "C" {
#endif

overror_t  __vcuf OVCUAPI   cusdVCF_limit(  cfVector Y, cfVector X, ui size, fComplex *d_Min, fComplex *d_Max );
overror_t  __vcuf OVCUAPI   cusdVCF_flush0( cfVector Y, cfVector X, ui size, fComplex *d_AbsMin );
overror_t  __vcuf OVCUAPI   cusdVCF_flushInv( cfVector Y, cfVector X, ui size, fComplex *d_AbsMin );
overror_t  __vcuf OVCUAPI   cusdVCF_replaceNAN( cfVector Y, cfVector X, ui size, fComplex *d_C );

overror_t  __vcuf OVCUAPI   cusdVCFx_equV( cfVector Y, cfVector X, ui size, fComplex *d_A, fComplex *d_B );
overror_t  __vcuf OVCUAPI   cusdVCF_addC(  cfVector Y, cfVector X, ui size, fComplex *d_C );
overror_t  __vcuf OVCUAPI   cusdVCF_subC(  cfVector Y, cfVector X, ui size, fComplex *d_C );
overror_t  __vcuf OVCUAPI   cusdVCF_subrC( cfVector Y, cfVector X, ui size, fComplex *d_C );
overror_t  __vcuf OVCUAPI   cusdVCF_mulC(  cfVector Y, cfVector X, ui size, fComplex *d_C );
overror_t  __vcuf OVCUAPI   cusdVCF_divC(  cfVector Y, cfVector X, ui size, fComplex *d_C );
overror_t  __vcuf OVCUAPI   cusdVCF_divrC( cfVector Y, cfVector X, ui size, fComplex *d_C );
overror_t  __vcuf OVCUAPI   cusdVCFx_divrC( cfVector Y, cfVector X, ui size, fComplex *d_A, fComplex *d_B, fComplex *d_C );

overror_t  __vcuf OVCUAPI   cudaVCF_addReC(  cfVector Y, cfVector X, ui size, float CRe );
overror_t  __vcuf OVCUAPI   cudaVCF_subReC(  cfVector Y, cfVector X, ui size, float CRe );
overror_t  __vcuf OVCUAPI   cudaVCF_subrReC( cfVector Y, cfVector X, ui size, float CRe );
overror_t  __vcuf OVCUAPI   cudaVCF_mulReC(  cfVector Y, cfVector X, ui size, float CRe );
overror_t  __vcuf OVCUAPI   cudaVCF_divReC(  cfVector Y, cfVector X, ui size, float CRe );
overror_t  __vcuf OVCUAPI   cudaVCF_divrReC( cfVector Y, cfVector X, ui size, float CRe );

overror_t  __vcuf OVCUAPI   cusdVCF_addReC(  cfVector Y, cfVector X, ui size, float *d_CRe );
overror_t  __vcuf OVCUAPI   cusdVCF_subReC(  cfVector Y, cfVector X, ui size, float *d_CRe );
overror_t  __vcuf OVCUAPI   cusdVCF_subrReC( cfVector Y, cfVector X, ui size, float *d_CRe );
overror_t  __vcuf OVCUAPI   cusdVCF_mulReC(  cfVector Y, cfVector X, ui size, float *d_CRe );
overror_t  __vcuf OVCUAPI   cusdVCF_divReC(  cfVector Y, cfVector X, ui size, float *d_CRe );
overror_t  __vcuf OVCUAPI   cusdVCF_divrReC( cfVector Y, cfVector X, ui size, float *d_CRe );

overror_t  __vcuf OVCUAPI   cudaVCF_addV(  cfVector Z, cfVector X, cfVector Y, ui size );
overror_t  __vcuf OVCUAPI   cudaVCF_subV(  cfVector Z, cfVector X, cfVector Y, ui size );
overror_t  __vcuf OVCUAPI   cudaVCF_subrV( cfVector Z, cfVector X, cfVector Y, ui size );
overror_t  __vcuf OVCUAPI   cudaVCF_mulV(  cfVector Z, cfVector X, cfVector Y, ui size );
overror_t  __vcuf OVCUAPI   cudaVCF_divV(  cfVector Z, cfVector X, cfVector Y, ui size );
overror_t  __vcuf OVCUAPI   cudaVCF_divrV( cfVector Z, cfVector X, cfVector Y, ui size );
overror_t  __vcuf OVCUAPI   cudaVCF_mulVconj(  cfVector Z, cfVector X, cfVector Y, ui size );

overror_t  __vcuf OVCUAPI   cudaVCF_addReV(  cfVector Z, cfVector X, fVector Y, ui size );
overror_t  __vcuf OVCUAPI   cudaVCF_subReV(  cfVector Z, cfVector X, fVector Y, ui size );
overror_t  __vcuf OVCUAPI   cudaVCF_subrReV( cfVector Z, cfVector X, fVector Y, ui size );
overror_t  __vcuf OVCUAPI   cudaVCF_mulReV(  cfVector Z, cfVector X, fVector Y, ui size );
overror_t  __vcuf OVCUAPI   cudaVCF_divReV(  cfVector Z, cfVector X, fVector Y, ui size );
overror_t  __vcuf OVCUAPI   cudaVCF_divrReV( cfVector Z, cfVector X, fVector Y, ui size );

overror_t  __vcuf OVCUAPI   cudaVCF_CaddV( cfVector Z, cfVector X, cfVector Y, ui siz, fComplex C );
overror_t  __vcuf OVCUAPI   cusdVCF_CaddV( cfVector Z, cfVector X, cfVector Y, ui siz, fComplex *d_C );

#if defined __cplusplus && defined _CMATH_CLASSDEFS && defined __BORLANDC__ && defined _WIN64
} // cannot be extern "C" for C++Builder on Win64, if fComplex is a class
#endif
overror_t  __vcuf OVCUAPI_ifNotBC64Class   cudaVCFx_addV(  cfVector Z, cfVector X, cfVector Y, ui size, fComplex A, fComplex B );
overror_t  __vcuf OVCUAPI_ifNotBC64Class   cudaVCFx_subV(  cfVector Z, cfVector X, cfVector Y, ui size, fComplex A, fComplex B );
overror_t  __vcuf OVCUAPI_ifNotBC64Class   cudaVCFx_subrV( cfVector Z, cfVector X, cfVector Y, ui size, fComplex A, fComplex B );
overror_t  __vcuf OVCUAPI_ifNotBC64Class   cudaVCFx_mulV(  cfVector Z, cfVector X, cfVector Y, ui size, fComplex A, fComplex B );
overror_t  __vcuf OVCUAPI_ifNotBC64Class   cudaVCFx_divV(  cfVector Z, cfVector X, cfVector Y, ui size, fComplex A, fComplex B );
overror_t  __vcuf OVCUAPI_ifNotBC64Class   cudaVCFx_divrV( cfVector Z, cfVector X, cfVector Y, ui size, fComplex A, fComplex B );
overror_t  __vcuf OVCUAPI_ifNotBC64Class   cudaVCFx_mulVconj( cfVector Z, cfVector X, cfVector Y, ui size, fComplex A, fComplex B );

overror_t  __vcuf OVCUAPI_ifNotBC64Class   cudaVCFx_addReV(  cfVector Z, cfVector X, fVector Y, ui size, fComplex A, fComplex B );
overror_t  __vcuf OVCUAPI_ifNotBC64Class   cudaVCFx_subReV(  cfVector Z, cfVector X, fVector Y, ui size, fComplex A, fComplex B );
overror_t  __vcuf OVCUAPI_ifNotBC64Class   cudaVCFx_subrReV( cfVector Z, cfVector X, fVector Y, ui size, fComplex A, fComplex B );
overror_t  __vcuf OVCUAPI_ifNotBC64Class   cudaVCFx_mulReV(  cfVector Z, cfVector X, fVector Y, ui size, fComplex A, fComplex B );
overror_t  __vcuf OVCUAPI_ifNotBC64Class   cudaVCFx_divReV(  cfVector Z, cfVector X, fVector Y, ui size, fComplex A, fComplex B );
overror_t  __vcuf OVCUAPI_ifNotBC64Class   cudaVCFx_divrReV( cfVector Z, cfVector X, fVector Y, ui size, fComplex A, fComplex B );

overror_t  __vcuf OVCUAPI_ifNotBC64Class  cudaVCF_lincomb( cfVector Z, cfVector X, cfVector Y, ui size, fComplex CX, fComplex CY ); 

#if defined __cplusplus && defined _CMATH_CLASSDEFS && defined __BORLANDC__ && defined _WIN64
extern "C" {
#endif
overror_t  __vcuf OVCUAPI  cudaVCF_rotateCoordinates( cfVector XYnew, cfVector XYold,
                       ui size, float costheta, float sintheta );

overror_t  __vcuf OVCUAPI   cusdVCFx_addV(  cfVector Z, cfVector X, cfVector Y, ui size, fComplex *d_A, fComplex *d_B );
overror_t  __vcuf OVCUAPI   cusdVCFx_subV(  cfVector Z, cfVector X, cfVector Y, ui size, fComplex *d_A, fComplex *d_B );
overror_t  __vcuf OVCUAPI   cusdVCFx_subrV( cfVector Z, cfVector X, cfVector Y, ui size, fComplex *d_A, fComplex *d_B );
overror_t  __vcuf OVCUAPI   cusdVCFx_mulV(  cfVector Z, cfVector X, cfVector Y, ui size, fComplex *d_A, fComplex *d_B );
overror_t  __vcuf OVCUAPI   cusdVCFx_divV(  cfVector Z, cfVector X, cfVector Y, ui size, fComplex *d_A, fComplex *d_B );
overror_t  __vcuf OVCUAPI   cusdVCFx_divrV( cfVector Z, cfVector X, cfVector Y, ui size, fComplex *d_A, fComplex *d_B );
overror_t  __vcuf OVCUAPI   cusdVCFx_mulVconj( cfVector Z, cfVector X, cfVector Y, ui size, fComplex *d_A, fComplex *d_B );

overror_t  __vcuf OVCUAPI   cusdVCFx_addReV(  cfVector Z, cfVector X, fVector Y, ui size, fComplex *d_A, fComplex *d_B );
overror_t  __vcuf OVCUAPI   cusdVCFx_subReV(  cfVector Z, cfVector X, fVector Y, ui size, fComplex *d_A, fComplex *d_B );
overror_t  __vcuf OVCUAPI   cusdVCFx_subrReV( cfVector Z, cfVector X, fVector Y, ui size, fComplex *d_A, fComplex *d_B );
overror_t  __vcuf OVCUAPI   cusdVCFx_mulReV(  cfVector Z, cfVector X, fVector Y, ui size, fComplex *d_A, fComplex *d_B );
overror_t  __vcuf OVCUAPI   cusdVCFx_divReV(  cfVector Z, cfVector X, fVector Y, ui size, fComplex *d_A, fComplex *d_B );
overror_t  __vcuf OVCUAPI   cusdVCFx_divrReV( cfVector Z, cfVector X, fVector Y, ui size, fComplex *d_A, fComplex *d_B );

overror_t  __vcuf OVCUAPI  cusdVCF_lincomb( cfVector Z, cfVector X, cfVector Y, ui size, fComplex *d_CX, fComplex *d_CY ); 
overror_t  __vcuf OVCUAPI  cusdVCF_rotateCoordinates( cfVector XYnew, cfVector XYold,
                       ui size, float *d_costheta, float *d_sintheta );

/******************** Accumulation (Y += X) ******************************/

overror_t  __vcuf OVCUAPI  cudaVCF_accV(   cfVector Y, cfVector  X, ui size );


/***************** Functions of a sub-set of elements  ********************/

#if defined __cplusplus && defined _CMATH_CLASSDEFS && defined __BORLANDC__ && defined _WIN64
} // cannot be extern "C" for C++Builder on Win64, if fComplex is a class
#endif
overror_t  __vcuf OVCUAPI_ifNotBC64Class   cudaVCF_subvector_equC(  cfVector Y, ui subsiz, ui samp, fComplex C );
overror_t  __vcuf OVCUAPI_ifNotBC64Class   cusdVCF_subvector_equC(  cfVector Y, ui subsiz, ui samp, fComplex *d_C );

overror_t  __vcuf OVCUAPI_ifNotBC64Class   cudaVCF_subvector_addC(  cfVector Y, ui subsiz, ui samp, fComplex C );
overror_t  __vcuf OVCUAPI_ifNotBC64Class   cudaVCF_subvector_subC(  cfVector Y, ui subsiz, ui samp, fComplex C );
overror_t  __vcuf OVCUAPI_ifNotBC64Class   cudaVCF_subvector_subrC( cfVector Y, ui subsiz, ui samp, fComplex C );
overror_t  __vcuf OVCUAPI_ifNotBC64Class   cudaVCF_subvector_mulC(  cfVector Y, ui subsiz, ui samp, fComplex C );
overror_t  __vcuf OVCUAPI_ifNotBC64Class   cudaVCF_subvector_divC(  cfVector Y, ui subsiz, ui samp, fComplex C );
overror_t  __vcuf OVCUAPI_ifNotBC64Class   cudaVCF_subvector_divrC( cfVector Y, ui subsiz, ui samp, fComplex C );

overror_t  __vcuf OVCUAPI_ifNotBC64Class   cusdVCF_subvector_addC(  cfVector Y, ui subsiz, ui samp, fComplex *d_C );
overror_t  __vcuf OVCUAPI_ifNotBC64Class   cusdVCF_subvector_subC(  cfVector Y, ui subsiz, ui samp, fComplex *d_C );
overror_t  __vcuf OVCUAPI_ifNotBC64Class   cusdVCF_subvector_subrC( cfVector Y, ui subsiz, ui samp, fComplex *d_C );
overror_t  __vcuf OVCUAPI_ifNotBC64Class   cusdVCF_subvector_mulC(  cfVector Y, ui subsiz, ui samp, fComplex *d_C );
overror_t  __vcuf OVCUAPI_ifNotBC64Class   cusdVCF_subvector_divC(  cfVector Y, ui subsiz, ui samp, fComplex *d_C );
overror_t  __vcuf OVCUAPI_ifNotBC64Class   cusdVCF_subvector_divrC( cfVector Y, ui subsiz, ui samp, fComplex *d_C );

#if defined __cplusplus && defined _CMATH_CLASSDEFS && defined __BORLANDC__ && defined _WIN64
extern "C" {
#endif
overror_t  __vcuf OVCUAPI   cudaVCF_subvector_equV(  cfVector Y, ui subsiz, ui samp, cfVector X );

overror_t  __vcuf OVCUAPI   cudaVCF_subvector_addV(  cfVector Y, ui subsiz, ui samp, cfVector X );
overror_t  __vcuf OVCUAPI   cudaVCF_subvector_subV(  cfVector Y, ui subsiz, ui samp, cfVector X );
overror_t  __vcuf OVCUAPI   cudaVCF_subvector_subrV( cfVector Y, ui subsiz, ui samp, cfVector X );
overror_t  __vcuf OVCUAPI   cudaVCF_subvector_mulV(  cfVector Y, ui subsiz, ui samp, cfVector X );
overror_t  __vcuf OVCUAPI   cudaVCF_subvector_divV(  cfVector Y, ui subsiz, ui samp, cfVector X );
overror_t  __vcuf OVCUAPI   cudaVCF_subvector_divrV( cfVector Y, ui subsiz, ui samp, cfVector X );

/********************  Mathematical Functions ***************************/

overror_t  __vcuf OVCUAPI  cudaVCF_neg(  cfVector Y, cfVector X, ui size );
overror_t  __vcuf OVCUAPI  cudaVCF_conj( cfVector Y, cfVector X, ui size );
#define      cudaVCF_abs    cudaVF_CtoAbs
overror_t  __vcuf OVCUAPI   cudaVCF_inv(  cfVector Y, cfVector X, ui size );

overror_t  __vcuf OVCUAPI   cudaVCF_square(  cfVector Y, cfVector X, ui size );
overror_t  __vcuf OVCUAPI   cudaVCF_cubic(   cfVector Y, cfVector X, ui size );
overror_t  __vcuf OVCUAPI   cudaVCF_quartic( cfVector Y, cfVector X, ui size );
overror_t  __vcuf OVCUAPI   cudaVCF_ipow(    cfVector Y, cfVector X, ui size, int ipow );

       /* extra fast integer powers: "unprotected", without error handling: */
overror_t  __vcuf OVCUAPI   cudaVCFu_square(  cfVector Y, cfVector X, ui size );
overror_t  __vcuf OVCUAPI   cudaVCFu_cubic(   cfVector Y, cfVector X, ui size );
overror_t  __vcuf OVCUAPI   cudaVCFu_quartic( cfVector Y, cfVector X, ui size );
overror_t  __vcuf OVCUAPI   cudaVCFu_ipow(    cfVector Y, cfVector X, ui size, int ipow );

overror_t  __vcuf OVCUAPI   cudaVCF_powReExpo(  cfVector Y, cfVector X, ui size, float Expo );
overror_t  __vcuf OVCUAPI   cudaVCF_sqrt(  cfVector Y, cfVector X, ui size );
overror_t  __vcuf OVCUAPI   cudaVCF_log(   cfVector Y, cfVector X, ui size );
overror_t  __vcuf OVCUAPI   cudaVCF_log2(  cfVector Y, cfVector X, ui size );
overror_t  __vcuf OVCUAPI   cudaVCF_log10( cfVector Y, cfVector X, ui size );
#define     cudaVCF_ln   cudaVCF_log

overror_t  __vcuf OVCUAPI   cudaVCF_exp(  cfVector Y, cfVector X, ui size );

overror_t  __vcuf OVCUAPI   cudaVCF_sin(  cfVector Y, cfVector X, ui size );
overror_t  __vcuf OVCUAPI   cudaVCF_cos(  cfVector Y, cfVector X, ui size );
overror_t  __vcuf OVCUAPI   cudaVCF_tan(  cfVector Y, cfVector X, ui size );

overror_t  __vcuf OVCUAPI   cudaVCF_asin(  cfVector Y, cfVector X, ui size );
overror_t  __vcuf OVCUAPI   cudaVCF_acos(  cfVector Y, cfVector X, ui size );
overror_t  __vcuf OVCUAPI   cudaVCF_atan(  cfVector Y, cfVector X, ui size );

overror_t  __vcuf OVCUAPI   cudaVCF_sinh(  cfVector Y, cfVector X, ui size );
overror_t  __vcuf OVCUAPI   cudaVCF_cosh(  cfVector Y, cfVector X, ui size );
overror_t  __vcuf OVCUAPI   cudaVCF_tanh(  cfVector Y, cfVector X, ui size );

#if defined __cplusplus && defined _CMATH_CLASSDEFS && defined __BORLANDC__ && defined _WIN64
} // cannot be extern "C" for C++Builder on Win64, if fComplex is a class
#endif
overror_t  __vcuf OVCUAPI_ifNotBC64Class   cudaVCF_pow(     cfVector Y, cfVector X, ui size, fComplex Expo );
overror_t  __vcuf OVCUAPI_ifNotBC64Class   cudaVCF_expArbBase(  cfVector Y, cfVector X, ui size, fComplex Base );

	/*  cudaVCFx_ variant (extended syntax): scalar values passed by value from host memory: */
overror_t  __vcuf OVCUAPI_ifNotBC64Class   cudaVCFx_inv( cfVector Y, cfVector X, ui size, fComplex A, fComplex B );
overror_t  __vcuf OVCUAPI_ifNotBC64Class   cudaVCFx_square( cfVector Y, cfVector X, ui size, fComplex A, fComplex B );
overror_t  __vcuf OVCUAPI_ifNotBC64Class   cudaVCFx_cubic(  cfVector Y, cfVector X, ui size, fComplex A, fComplex B );
overror_t  __vcuf OVCUAPI_ifNotBC64Class   cudaVCFx_quartic( cfVector Y, cfVector X, ui size, fComplex A, fComplex B );
overror_t  __vcuf OVCUAPI_ifNotBC64Class   cudaVCFx_ipow(   cfVector Y, cfVector X, ui size, int ipow,
                                                            fComplex A, fComplex B, fComplex C );
overror_t  __vcuf OVCUAPI_ifNotBC64Class   cudaVCFux_square( cfVector Y, cfVector X, ui size, fComplex A, fComplex B );
overror_t  __vcuf OVCUAPI_ifNotBC64Class   cudaVCFux_cubic(  cfVector Y, cfVector X, ui size, fComplex A, fComplex B );
overror_t  __vcuf OVCUAPI_ifNotBC64Class   cudaVCFux_quartic( cfVector Y, cfVector X, ui size, fComplex A, fComplex B );
overror_t  __vcuf OVCUAPI_ifNotBC64Class   cudaVCFux_ipow(   cfVector Y, cfVector X, ui size, int ipow,
                                                             fComplex A, fComplex B, fComplex C );
overror_t  __vcuf OVCUAPI_ifNotBC64Class   cudaVCFx_pow(    cfVector Y, cfVector X, ui size,  fComplex Expo,
                                                            fComplex A, fComplex B, fComplex C );
overror_t  __vcuf OVCUAPI_ifNotBC64Class   cudaVCFx_powReExpo( cfVector Y, cfVector X, ui size, float Expo,
                                                               fComplex A, fComplex B, fComplex C );
overror_t  __vcuf OVCUAPI_ifNotBC64Class   cudaVCFx_sqrt( cfVector Y, cfVector X, ui size, fComplex A, fComplex B, fComplex C );
overror_t  __vcuf OVCUAPI_ifNotBC64Class   cudaVCFx_log(  cfVector Y, cfVector X, ui size, fComplex A, fComplex B, fComplex C );
overror_t  __vcuf OVCUAPI_ifNotBC64Class   cudaVCFx_log2( cfVector Y, cfVector X, ui size, fComplex A, fComplex B, fComplex C );
overror_t  __vcuf OVCUAPI_ifNotBC64Class   cudaVCFx_log10( cfVector Y, cfVector X, ui size, fComplex A, fComplex B, fComplex C );
#define     cudaVCFx_ln    cudaVCFx_log
overror_t  __vcuf OVCUAPI_ifNotBC64Class   cudaVCFx_exp( cfVector Y, cfVector X, ui size, fComplex A, fComplex B, fComplex C );
overror_t  __vcuf OVCUAPI_ifNotBC64Class   cudaVCFx_expArbBase( cfVector Y, cfVector X, ui size, fComplex Base,
                                                                fComplex A, fComplex B, fComplex C );
overror_t  __vcuf OVCUAPI_ifNotBC64Class   cudaVCFx_sin( cfVector Y, cfVector X, ui size, fComplex A, fComplex B, fComplex C );
overror_t  __vcuf OVCUAPI_ifNotBC64Class   cudaVCFx_cos( cfVector Y, cfVector X, ui size, fComplex A, fComplex B, fComplex C );
overror_t  __vcuf OVCUAPI_ifNotBC64Class   cudaVCFx_tan( cfVector Y, cfVector X, ui size, fComplex A, fComplex B, fComplex C );
overror_t  __vcuf OVCUAPI_ifNotBC64Class   cudaVCFx_asin( cfVector Y, cfVector X, ui size, fComplex A, fComplex B, fComplex C );
overror_t  __vcuf OVCUAPI_ifNotBC64Class   cudaVCFx_acos( cfVector Y, cfVector X, ui size, fComplex A, fComplex B, fComplex C );
overror_t  __vcuf OVCUAPI_ifNotBC64Class   cudaVCFx_atan( cfVector Y, cfVector X, ui size, fComplex A, fComplex B, fComplex C );
overror_t  __vcuf OVCUAPI_ifNotBC64Class   cudaVCFx_sinh( cfVector Y, cfVector X, ui size, fComplex A, fComplex B, fComplex C );
overror_t  __vcuf OVCUAPI_ifNotBC64Class   cudaVCFx_cosh( cfVector Y, cfVector X, ui size, fComplex A, fComplex B, fComplex C );
overror_t  __vcuf OVCUAPI_ifNotBC64Class   cudaVCFx_tanh( cfVector Y, cfVector X, ui size, fComplex A, fComplex B, fComplex C );

#if defined __cplusplus && defined _CMATH_CLASSDEFS && defined __BORLANDC__ && defined _WIN64
extern "C" {
#endif

	/*  cusdVCFx_ variant: scalar values passed by address on device memory: */
overror_t  __vcuf OVCUAPI   cusdVCFx_inv( cfVector Y, cfVector X, ui size, fComplex *d_A, fComplex *d_B );
overror_t  __vcuf OVCUAPI   cusdVCFx_square( cfVector Y, cfVector X, ui size, fComplex *d_A, fComplex *d_B );
overror_t  __vcuf OVCUAPI   cusdVCFx_cubic(  cfVector Y, cfVector X, ui size, fComplex *d_A, fComplex *d_B );
overror_t  __vcuf OVCUAPI   cusdVCFx_quartic( cfVector Y, cfVector X, ui size, fComplex *d_A, fComplex *d_B );
overror_t  __vcuf OVCUAPI   cusdVCFx_ipow(   cfVector Y, cfVector X, ui size, int ipow, fComplex *d_A, fComplex *d_B, fComplex *d_C );
overror_t  __vcuf OVCUAPI   cusdVCFux_square( cfVector Y, cfVector X, ui size, fComplex *d_A, fComplex *d_B );
overror_t  __vcuf OVCUAPI   cusdVCFux_cubic(  cfVector Y, cfVector X, ui size, fComplex *d_A, fComplex *d_B );
overror_t  __vcuf OVCUAPI   cusdVCFux_quartic( cfVector Y, cfVector X, ui size, fComplex *d_A, fComplex *d_B );
overror_t  __vcuf OVCUAPI   cusdVCFux_ipow(   cfVector Y, cfVector X, ui size, int ipow, fComplex *d_A, fComplex *d_B, fComplex *d_C );
overror_t  __vcuf OVCUAPI   cusdVCFx_pow(    cfVector Y, cfVector X, ui size,  fComplex Expo, fComplex *d_A, fComplex *d_B, fComplex *d_C );
overror_t  __vcuf OVCUAPI   cusdVCFx_powReExpo( cfVector Y, cfVector X, ui size, float Expo, fComplex *d_A, fComplex *d_B, fComplex *d_C );
overror_t  __vcuf OVCUAPI   cusdVCFx_sqrt( cfVector Y, cfVector X, ui size, fComplex *d_A, fComplex *d_B, fComplex *d_C );
overror_t  __vcuf OVCUAPI   cusdVCFx_log(  cfVector Y, cfVector X, ui size, fComplex *d_A, fComplex *d_B, fComplex *d_C );
overror_t  __vcuf OVCUAPI   cusdVCFx_log2( cfVector Y, cfVector X, ui size, fComplex *d_A, fComplex *d_B, fComplex *d_C );
overror_t  __vcuf OVCUAPI   cusdVCFx_log10( cfVector Y, cfVector X, ui size, fComplex *d_A, fComplex *d_B, fComplex *d_C );
#define     cusdVCFx_ln    cusdVCFx_log
overror_t  __vcuf OVCUAPI   cusdVCFx_exp( cfVector Y, cfVector X, ui size, fComplex *d_A, fComplex *d_B, fComplex *d_C );
overror_t  __vcuf OVCUAPI   cusdVCFx_expArbBase( cfVector Y, cfVector X, ui size, fComplex Base,
                             fComplex *d_A, fComplex *d_B, fComplex *d_C );
overror_t  __vcuf OVCUAPI   cusdVCFx_sin( cfVector Y, cfVector X, ui size, fComplex *d_A, fComplex *d_B, fComplex *d_C );
overror_t  __vcuf OVCUAPI   cusdVCFx_cos( cfVector Y, cfVector X, ui size, fComplex *d_A, fComplex *d_B, fComplex *d_C );
overror_t  __vcuf OVCUAPI   cusdVCFx_tan( cfVector Y, cfVector X, ui size, fComplex *d_A, fComplex *d_B, fComplex *d_C );
overror_t  __vcuf OVCUAPI   cusdVCFx_asin( cfVector Y, cfVector X, ui size, fComplex *d_A, fComplex *d_B, fComplex *d_C );
overror_t  __vcuf OVCUAPI   cusdVCFx_acos( cfVector Y, cfVector X, ui size, fComplex *d_A, fComplex *d_B, fComplex *d_C );
overror_t  __vcuf OVCUAPI   cusdVCFx_atan( cfVector Y, cfVector X, ui size, fComplex *d_A, fComplex *d_B, fComplex *d_C );
overror_t  __vcuf OVCUAPI   cusdVCFx_sinh( cfVector Y, cfVector X, ui size, fComplex *d_A, fComplex *d_B, fComplex *d_C );
overror_t  __vcuf OVCUAPI   cusdVCFx_cosh( cfVector Y, cfVector X, ui size, fComplex *d_A, fComplex *d_B, fComplex *d_C );
overror_t  __vcuf OVCUAPI   cusdVCFx_tanh( cfVector Y, cfVector X, ui size, fComplex *d_A, fComplex *d_B, fComplex *d_C );

#ifdef __cplusplus
} // end of extern "C"
#endif

/******************  VCFcu_ functions: **********************************
	act on host memory, using the CUDA device for processing
************************************************************************/


#ifdef __cplusplus
extern "C" {
#endif

/************************* Comparisons ****************************/

ui   __vf OVCUAPI   VCFcu_cmp_eq0( cfVector Y, cfVector X, ui size );
ui   __vf OVCUAPI   VCFcu_cmp_ne0( cfVector Y, cfVector X, ui size );
ui   __vf OVCUAPI   VCFcu_cmp_eqV( cfVector Z, cfVector X, cfVector Y, ui size );
ui   __vf OVCUAPI   VCFcu_cmp_neV( cfVector Z, cfVector X, cfVector Y, ui size );
ui   __vf OVCUAPI   VCFcu_cnt_eq0( cfVector X, ui size );
ui   __vf OVCUAPI   VCFcu_cnt_ne0( cfVector X, ui size );
ui   __vf OVCUAPI   VCFcu_cnt_eqV( cfVector X, cfVector Y, ui size );
ui   __vf OVCUAPI   VCFcu_cnt_neV( cfVector X, cfVector Y, ui size );
/*
ui   __vf OVCUAPI   VCFcu_cmp_eq0ind( uiVector Ind, cfVector X, ui size );
ui   __vf OVCUAPI   VCFcu_cmp_ne0ind( uiVector Ind, cfVector X, ui size );
ui   __vf OVCUAPI   VCFcu_cmp_eqVind( uiVector Ind, cfVector X, cfVector Y, ui size );
ui   __vf OVCUAPI   VCFcu_cmp_neVind( uiVector Ind, cfVector X, cfVector Y, ui size );
*/
#if defined __cplusplus && defined _CMATH_CLASSDEFS && defined __BORLANDC__ && defined _WIN64
} // cannot be extern "C" for C++Builder on Win64, if fComplex is a class
#endif
ui   __vf OVCUAPI_ifNotBC64Class   VCFcu_cmp_eqC( cfVector Y, cfVector X, ui size, fComplex C );
ui   __vf OVCUAPI_ifNotBC64Class   VCFcu_cmp_neC( cfVector Y, cfVector X, ui size, fComplex C );
ui   __vf OVCUAPI_ifNotBC64Class   VCFcu_cnt_eqC( cfVector X, ui size, fComplex C );
ui   __vf OVCUAPI_ifNotBC64Class   VCFcu_cnt_neC( cfVector X, ui size, fComplex C );
/*
ui   __vf OVCUAPI_ifNotBC64Class   VCFcu_cmp_eqCind( uiVector Ind, cfVector X, ui size, fComplex C );
ui   __vf OVCUAPI_ifNotBC64Class   VCFcu_cmp_neCind( uiVector Ind, cfVector X, ui size, fComplex C );
*/

/********************  Standard Arithmetics   ***************************/

void  __vf OVCUAPI_ifNotBC64Class   VCFcu_limit(  cfVector Y, cfVector X, ui size, fComplex Min, fComplex Max );
void  __vf OVCUAPI_ifNotBC64Class   VCFcu_flush0( cfVector Y, cfVector X, ui size, fComplex AbsMin );
void  __vf OVCUAPI_ifNotBC64Class   VCFcu_flushInv( cfVector Y, cfVector X, ui size, fComplex AbsMin );
void  __vf OVCUAPI_ifNotBC64Class   VCFcu_replaceNAN( cfVector Y, cfVector X, ui size, fComplex C );

void  __vf OVCUAPI_ifNotBC64Class   VCFxcu_equV( cfVector Y, cfVector X, ui size, fComplex A, fComplex B );
void  __vf OVCUAPI_ifNotBC64Class   VCFcu_addC(  cfVector Y, cfVector X, ui size, fComplex C );
void  __vf OVCUAPI_ifNotBC64Class   VCFcu_subC(  cfVector Y, cfVector X, ui size, fComplex C );
void  __vf OVCUAPI_ifNotBC64Class   VCFcu_subrC( cfVector Y, cfVector X, ui size, fComplex C );
void  __vf OVCUAPI_ifNotBC64Class   VCFcu_mulC(  cfVector Y, cfVector X, ui size, fComplex C );
void  __vf OVCUAPI_ifNotBC64Class   VCFcu_divC(  cfVector Y, cfVector X, ui size, fComplex C );
void  __vf OVCUAPI_ifNotBC64Class   VCFcu_divrC( cfVector Y, cfVector X, ui size, fComplex C );
void  __vf OVCUAPI_ifNotBC64Class   VCFxcu_divrC( cfVector Y, cfVector X, ui size, fComplex A, fComplex B, fComplex C );

#if defined __cplusplus && defined _CMATH_CLASSDEFS && defined __BORLANDC__ && defined _WIN64
extern "C" {
#endif

void  __vf OVCUAPI   VCFcu_addReC(  cfVector Y, cfVector X, ui size, float CRe );
void  __vf OVCUAPI   VCFcu_subReC(  cfVector Y, cfVector X, ui size, float CRe );
void  __vf OVCUAPI   VCFcu_subrReC( cfVector Y, cfVector X, ui size, float CRe );
void  __vf OVCUAPI   VCFcu_mulReC(  cfVector Y, cfVector X, ui size, float CRe );
void  __vf OVCUAPI   VCFcu_divReC(  cfVector Y, cfVector X, ui size, float CRe );
void  __vf OVCUAPI   VCFcu_divrReC( cfVector Y, cfVector X, ui size, float CRe );

void  __vf OVCUAPI   VCFcu_addV(  cfVector Z, cfVector X, cfVector Y, ui size );
void  __vf OVCUAPI   VCFcu_subV(  cfVector Z, cfVector X, cfVector Y, ui size );
void  __vf OVCUAPI   VCFcu_subrV( cfVector Z, cfVector X, cfVector Y, ui size );
void  __vf OVCUAPI   VCFcu_mulV(  cfVector Z, cfVector X, cfVector Y, ui size );
void  __vf OVCUAPI   VCFcu_divV(  cfVector Z, cfVector X, cfVector Y, ui size );
void  __vf OVCUAPI   VCFcu_divrV( cfVector Z, cfVector X, cfVector Y, ui size );
void  __vf OVCUAPI   VCFcu_mulVconj(  cfVector Z, cfVector X, cfVector Y, ui size );

void  __vf OVCUAPI   VCFcu_addReV(  cfVector Z, cfVector X, fVector Y, ui size );
void  __vf OVCUAPI   VCFcu_subReV(  cfVector Z, cfVector X, fVector Y, ui size );
void  __vf OVCUAPI   VCFcu_subrReV( cfVector Z, cfVector X, fVector Y, ui size );
void  __vf OVCUAPI   VCFcu_mulReV(  cfVector Z, cfVector X, fVector Y, ui size );
void  __vf OVCUAPI   VCFcu_divReV(  cfVector Z, cfVector X, fVector Y, ui size );
void  __vf OVCUAPI   VCFcu_divrReV( cfVector Z, cfVector X, fVector Y, ui size );

#if defined __cplusplus && defined _CMATH_CLASSDEFS && defined __BORLANDC__ && defined _WIN64
} // cannot be extern "C" for C++Builder on Win64, if fComplex is a class
#endif
void  __vf OVCUAPI_ifNotBC64Class   VCFcu_CaddV( cfVector Z, cfVector X, cfVector Y, ui siz, fComplex C );

void  __vf OVCUAPI_ifNotBC64Class   VCFxcu_addV(  cfVector Z, cfVector X, cfVector Y, ui size, fComplex A, fComplex B );
void  __vf OVCUAPI_ifNotBC64Class   VCFxcu_subV(  cfVector Z, cfVector X, cfVector Y, ui size, fComplex A, fComplex B );
void  __vf OVCUAPI_ifNotBC64Class   VCFxcu_subrV( cfVector Z, cfVector X, cfVector Y, ui size, fComplex A, fComplex B );
void  __vf OVCUAPI_ifNotBC64Class   VCFxcu_mulV(  cfVector Z, cfVector X, cfVector Y, ui size, fComplex A, fComplex B );
void  __vf OVCUAPI_ifNotBC64Class   VCFxcu_divV(  cfVector Z, cfVector X, cfVector Y, ui size, fComplex A, fComplex B );
void  __vf OVCUAPI_ifNotBC64Class   VCFxcu_divrV( cfVector Z, cfVector X, cfVector Y, ui size, fComplex A, fComplex B );
void  __vf OVCUAPI_ifNotBC64Class   VCFxcu_mulVconj( cfVector Z, cfVector X, cfVector Y, ui size, fComplex A, fComplex B );

void  __vf OVCUAPI_ifNotBC64Class   VCFxcu_addReV(  cfVector Z, cfVector X, fVector Y, ui size, fComplex A, fComplex B );
void  __vf OVCUAPI_ifNotBC64Class   VCFxcu_subReV(  cfVector Z, cfVector X, fVector Y, ui size, fComplex A, fComplex B );
void  __vf OVCUAPI_ifNotBC64Class   VCFxcu_subrReV( cfVector Z, cfVector X, fVector Y, ui size, fComplex A, fComplex B );
void  __vf OVCUAPI_ifNotBC64Class   VCFxcu_mulReV(  cfVector Z, cfVector X, fVector Y, ui size, fComplex A, fComplex B );
void  __vf OVCUAPI_ifNotBC64Class   VCFxcu_divReV(  cfVector Z, cfVector X, fVector Y, ui size, fComplex A, fComplex B );
void  __vf OVCUAPI_ifNotBC64Class   VCFxcu_divrReV( cfVector Z, cfVector X, fVector Y, ui size, fComplex A, fComplex B );

void __vf OVCUAPI_ifNotBC64Class  VCFcu_lincomb( cfVector Z, cfVector X, cfVector Y, ui size, fComplex CX, fComplex CY ); 

#if defined __cplusplus && defined _CMATH_CLASSDEFS && defined __BORLANDC__ && defined _WIN64
extern "C" {
#endif
void __vf OVCUAPI  VCFcu_rotateCoordinates( cfVector XYnew, cfVector XYold,
                       ui size, float costheta, float sintheta );

/******************** Accumulation (Y += X) ******************************/

void __vf OVCUAPI  VCFcu_accV(   cfVector Y, cfVector  X, ui size );

/***************** Functions of a sub-set of elements  ********************/

#if defined __cplusplus && defined _CMATH_CLASSDEFS && defined __BORLANDC__ && defined _WIN64
} // cannot be extern "C" for C++Builder on Win64, if fComplex is a class
#endif
void  __vf OVCUAPI_ifNotBC64Class   VCFcu_subvector_equC(  cfVector Y, ui subsiz, ui samp, fComplex C );
void  __vf OVCUAPI_ifNotBC64Class   VCFcu_subvector_addC(  cfVector Y, ui subsiz, ui samp, fComplex C );
void  __vf OVCUAPI_ifNotBC64Class   VCFcu_subvector_subC(  cfVector Y, ui subsiz, ui samp, fComplex C );
void  __vf OVCUAPI_ifNotBC64Class   VCFcu_subvector_subrC( cfVector Y, ui subsiz, ui samp, fComplex C );
void  __vf OVCUAPI_ifNotBC64Class   VCFcu_subvector_mulC(  cfVector Y, ui subsiz, ui samp, fComplex C );
void  __vf OVCUAPI_ifNotBC64Class   VCFcu_subvector_divC(  cfVector Y, ui subsiz, ui samp, fComplex C );
void  __vf OVCUAPI_ifNotBC64Class   VCFcu_subvector_divrC( cfVector Y, ui subsiz, ui samp, fComplex C );

#if defined __cplusplus && defined _CMATH_CLASSDEFS && defined __BORLANDC__ && defined _WIN64
extern "C" {
#endif

void  __vf OVCUAPI   VCFcu_subvector_equV(  cfVector Y, ui subsiz, ui samp, cfVector X );
void  __vf OVCUAPI   VCFcu_subvector_addV(  cfVector Y, ui subsiz, ui samp, cfVector X );
void  __vf OVCUAPI   VCFcu_subvector_subV(  cfVector Y, ui subsiz, ui samp, cfVector X );
void  __vf OVCUAPI   VCFcu_subvector_subrV( cfVector Y, ui subsiz, ui samp, cfVector X );
void  __vf OVCUAPI   VCFcu_subvector_mulV(  cfVector Y, ui subsiz, ui samp, cfVector X );
void  __vf OVCUAPI   VCFcu_subvector_divV(  cfVector Y, ui subsiz, ui samp, cfVector X );
void  __vf OVCUAPI   VCFcu_subvector_divrV( cfVector Y, ui subsiz, ui samp, cfVector X );

/********************  Mathematical Functions ***************************/

int  __vf OVCUAPI  VCFcu_abs(   fVector Y, cfVector X, ui size );
int  __vf OVCUAPI  VCFcu_neg(  cfVector Y, cfVector X, ui size );
int  __vf OVCUAPI  VCFcu_conj( cfVector Y, cfVector X, ui size );
int  __vf OVCUAPI  VCFcu_inv(  cfVector Y, cfVector X, ui size );

int  __vf OVCUAPI   VCFcu_square(  cfVector Y, cfVector X, ui size );
int  __vf OVCUAPI   VCFcu_cubic(   cfVector Y, cfVector X, ui size );
int  __vf OVCUAPI   VCFcu_quartic( cfVector Y, cfVector X, ui size );
int  __vf OVCUAPI   VCFcu_ipow(    cfVector Y, cfVector X, ui size, int ipow );
int  __vf OVCUAPI   VCFcu_powReExpo(  cfVector Y, cfVector X, ui size, float Expo );

#if defined __cplusplus && defined _CMATH_CLASSDEFS && defined __BORLANDC__ && defined _WIN64
} // cannot be extern "C" for C++Builder on Win64, if fComplex is a class
#endif
int  __vf OVCUAPI_ifNotBC64Class   VCFxcu_inv( cfVector Y, cfVector X, ui size, fComplex A, fComplex B );
int  __vf OVCUAPI_ifNotBC64Class   VCFxcu_square( cfVector Y, cfVector X, ui size, fComplex A, fComplex B );
int  __vf OVCUAPI_ifNotBC64Class   VCFxcu_cubic(  cfVector Y, cfVector X, ui size, fComplex A, fComplex B );
int  __vf OVCUAPI_ifNotBC64Class   VCFxcu_quartic( cfVector Y, cfVector X, ui size, fComplex A, fComplex B );
int  __vf OVCUAPI_ifNotBC64Class   VCFxcu_ipow(   cfVector Y, cfVector X, ui size, int ipow,
                         fComplex A, fComplex B, fComplex C );
#if defined __cplusplus && defined _CMATH_CLASSDEFS && defined __BORLANDC__ && defined _WIN64
extern "C" {
#endif

       /* extra fast integer powers: "unprotected", without error handling: */
int  __vf OVCUAPI   VCFucu_square(  cfVector Y, cfVector X, ui size );
int  __vf OVCUAPI   VCFucu_cubic(   cfVector Y, cfVector X, ui size );
int  __vf OVCUAPI   VCFucu_quartic( cfVector Y, cfVector X, ui size );
int  __vf OVCUAPI   VCFucu_ipow(    cfVector Y, cfVector X, ui size, int ipow );

int  __vf OVCUAPI   VCFcu_sqrt(  cfVector Y, cfVector X, ui size );

int  __vf OVCUAPI   VCFcu_log(   cfVector Y, cfVector X, ui size );
int  __vf OVCUAPI   VCFcu_log2(  cfVector Y, cfVector X, ui size );
int  __vf OVCUAPI   VCFcu_log10( cfVector Y, cfVector X, ui size );
#define     VCFcu_ln   VCFcu_log

int  __vf OVCUAPI   VCFcu_exp(  cfVector Y, cfVector X, ui size );

int  __vf OVCUAPI   VCFcu_sin(  cfVector Y, cfVector X, ui size );
int  __vf OVCUAPI   VCFcu_cos(  cfVector Y, cfVector X, ui size );
int  __vf OVCUAPI   VCFcu_tan(  cfVector Y, cfVector X, ui size );

int  __vf OVCUAPI   VCFcu_asin(  cfVector Y, cfVector X, ui size );
int  __vf OVCUAPI   VCFcu_acos(  cfVector Y, cfVector X, ui size );
int  __vf OVCUAPI   VCFcu_atan(  cfVector Y, cfVector X, ui size );

int  __vf OVCUAPI   VCFcu_sinh(  cfVector Y, cfVector X, ui size );
int  __vf OVCUAPI   VCFcu_cosh(  cfVector Y, cfVector X, ui size );
int  __vf OVCUAPI   VCFcu_tanh(  cfVector Y, cfVector X, ui size );

#if defined __cplusplus && defined _CMATH_CLASSDEFS && defined __BORLANDC__ && defined _WIN64
} // functions with scalar fComplex argument cannot be extern "C" for C++Builder on Win64, if fComplex is a class
#endif

int  __vf OVCUAPI_ifNotBC64Class   VCFuxcu_square( cfVector Y, cfVector X, ui size, fComplex A, fComplex B );
int  __vf OVCUAPI_ifNotBC64Class   VCFuxcu_cubic(  cfVector Y, cfVector X, ui size, fComplex A, fComplex B );
int  __vf OVCUAPI_ifNotBC64Class   VCFuxcu_quartic( cfVector Y, cfVector X, ui size, fComplex A, fComplex B );

int  __vf OVCUAPI_ifNotBC64Class   VCFuxcu_ipow(   cfVector Y, cfVector X, ui size, int ipow,
                          fComplex A, fComplex B, fComplex C );

int  __vf OVCUAPI_ifNotBC64Class   VCFcu_pow(     cfVector Y, cfVector X, ui size, fComplex Expo );
int  __vf OVCUAPI_ifNotBC64Class   VCFxcu_pow(    cfVector Y, cfVector X, ui size,  fComplex Expo,
                         fComplex A, fComplex B, fComplex C );
int  __vf OVCUAPI_ifNotBC64Class   VCFxcu_powReExpo( cfVector Y, cfVector X, ui size, float Expo,
                            fComplex A, fComplex B, fComplex C );
int  __vf OVCUAPI_ifNotBC64Class   VCFxcu_sqrt( cfVector Y, cfVector X, ui size, fComplex A, fComplex B, fComplex C );
int  __vf OVCUAPI_ifNotBC64Class   VCFxcu_log(  cfVector Y, cfVector X, ui size, fComplex A, fComplex B, fComplex C );
int  __vf OVCUAPI_ifNotBC64Class   VCFxcu_log2( cfVector Y, cfVector X, ui size, fComplex A, fComplex B, fComplex C );
int  __vf OVCUAPI_ifNotBC64Class   VCFxcu_log10( cfVector Y, cfVector X, ui size, fComplex A, fComplex B, fComplex C );
#define     VCFxcu_ln    VCFxcu_log

int  __vf OVCUAPI_ifNotBC64Class   VCFxcu_exp( cfVector Y, cfVector X, ui size, fComplex A, fComplex B, fComplex C );
int  __vf OVCUAPI_ifNotBC64Class   VCFcu_expArbBase(  cfVector Y, cfVector X, ui size, fComplex Base );
int  __vf OVCUAPI_ifNotBC64Class   VCFxcu_expArbBase( cfVector Y, cfVector X, ui size, fComplex Base,
                             fComplex A, fComplex B, fComplex C );
int  __vf OVCUAPI_ifNotBC64Class   VCFxcu_sin( cfVector Y, cfVector X, ui size, fComplex A, fComplex B, fComplex C );
int  __vf OVCUAPI_ifNotBC64Class   VCFxcu_cos( cfVector Y, cfVector X, ui size, fComplex A, fComplex B, fComplex C );
int  __vf OVCUAPI_ifNotBC64Class   VCFxcu_tan( cfVector Y, cfVector X, ui size, fComplex A, fComplex B, fComplex C );
int  __vf OVCUAPI_ifNotBC64Class   VCFxcu_asin( cfVector Y, cfVector X, ui size, fComplex A, fComplex B, fComplex C );
int  __vf OVCUAPI_ifNotBC64Class   VCFxcu_acos( cfVector Y, cfVector X, ui size, fComplex A, fComplex B, fComplex C );
int  __vf OVCUAPI_ifNotBC64Class   VCFxcu_atan( cfVector Y, cfVector X, ui size, fComplex A, fComplex B, fComplex C );
int  __vf OVCUAPI_ifNotBC64Class   VCFxcu_sinh( cfVector Y, cfVector X, ui size, fComplex A, fComplex B, fComplex C );
int  __vf OVCUAPI_ifNotBC64Class   VCFxcu_cosh( cfVector Y, cfVector X, ui size, fComplex A, fComplex B, fComplex C );
int  __vf OVCUAPI_ifNotBC64Class   VCFxcu_tanh( cfVector Y, cfVector X, ui size, fComplex A, fComplex B, fComplex C );

#if defined __cplusplus && !(defined _CMATH_CLASSDEFS && defined __BORLANDC__ && defined _WIN64)
} // end of extern "C"
#endif

#endif /* __cudaVCFMATH_H */
