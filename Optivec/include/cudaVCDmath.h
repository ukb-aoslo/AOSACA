/*  cudaVCDmath.h

  vector management functions:
  math functions performed on each individual element of an
  array or vector of data type "dComplex" (complex double)

  Copyright (c) 1996-2017 by OptiCode - Dr. Martin Sander Software Dev.
  All Rights Reserved.
*/

#ifndef __CUDAVCDMATH_H
#define __CUDAVCDMATH_H

#ifndef __CUDAVCDSTD_H 
#include <cudaVCDstd.h>
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

/************************* Comparisons ****************************/

overror_t  __vcuf OVCUAPI   cudaVCD_cmp_eq0( ui *h_nTrue, cdVector Y, cdVector X, ui size );
overror_t  __vcuf OVCUAPI   cudaVCD_cmp_ne0( ui *h_nTrue, cdVector Y, cdVector X, ui size );
overror_t  __vcuf OVCUAPI   cudaVCD_cmp_eqC( ui *h_nTrue, cdVector Y, cdVector X, ui size, dComplex C );
overror_t  __vcuf OVCUAPI   cudaVCD_cmp_neC( ui *h_nTrue, cdVector Y, cdVector X, ui size, dComplex C );
overror_t  __vcuf OVCUAPI   cusdVCD_cmp_eqC( ui *h_nTrue, cdVector Y, cdVector X, ui size, dComplex *d_C );
overror_t  __vcuf OVCUAPI   cusdVCD_cmp_neC( ui *h_nTrue, cdVector Y, cdVector X, ui size, dComplex *d_C );
overror_t  __vcuf OVCUAPI   cudaVCD_cmp_eqV( ui *h_nTrue, cdVector Z, cdVector X, cdVector Y, ui size );
overror_t  __vcuf OVCUAPI   cudaVCD_cmp_neV( ui *h_nTrue, cdVector Z, cdVector X, cdVector Y, ui size );

overror_t  __vcuf OVCUAPI   cudaVCD_cnt_eq0( ui *h_nTrue, cdVector X, ui size );
overror_t  __vcuf OVCUAPI   cudaVCD_cnt_ne0( ui *h_nTrue, cdVector X, ui size );
overror_t  __vcuf OVCUAPI   cudaVCD_cnt_eqC( ui *h_nTrue, cdVector X, ui size, dComplex C );
overror_t  __vcuf OVCUAPI   cudaVCD_cnt_neC( ui *h_nTrue, cdVector X, ui size, dComplex C );
overror_t  __vcuf OVCUAPI   cusdVCD_cnt_eqC( ui *h_nTrue, cdVector X, ui size, dComplex *d_C );
overror_t  __vcuf OVCUAPI   cusdVCD_cnt_neC( ui *h_nTrue, cdVector X, ui size, dComplex *d_C );
overror_t  __vcuf OVCUAPI   cudaVCD_cnt_eqV( ui *h_nTrue, cdVector X, cdVector Y, ui size );
overror_t  __vcuf OVCUAPI   cudaVCD_cnt_neV( ui *h_nTrue, cdVector X, cdVector Y, ui size );
/*
overror_t  __vcuf OVCUAPI   cudaVCD_cmp_eq0ind( ui *h_nTrue, uiVector Ind, cdVector X, ui size );
overror_t  __vcuf OVCUAPI   cudaVCD_cmp_ne0ind( ui *h_nTrue, uiVector Ind, cdVector X, ui size );
overror_t  __vcuf OVCUAPI   cudaVCD_cmp_eqCind( ui *h_nTrue, uiVector Ind, cdVector X, ui size, dComplex C );
overror_t  __vcuf OVCUAPI   cudaVCD_cmp_neCind( ui *h_nTrue, uiVector Ind, cdVector X, ui size, dComplex C );
overror_t  __vcuf OVCUAPI   cusdVCD_cmp_eqCind( ui *h_nTrue, uiVector Ind, cdVector X, ui size, dComplex *d_C );
overror_t  __vcuf OVCUAPI   cusdVCD_cmp_neCind( ui *h_nTrue, uiVector Ind, cdVector X, ui size, dComplex *d_C );
overror_t  __vcuf OVCUAPI   cudaVCD_cmp_eqVind( ui *h_nTrue, uiVector Ind, cdVector X, cdVector Y, ui size );
overror_t  __vcuf OVCUAPI   cudaVCD_cmp_neVind( ui *h_nTrue, uiVector Ind, cdVector X, cdVector Y, ui size );
*/

/********************  Standard Arithmetics   ***************************/

overror_t  __vcuf OVCUAPI   cudaVCD_limit(  cdVector Y, cdVector X, ui size, dComplex Min, dComplex Max );
overror_t  __vcuf OVCUAPI   cudaVCD_flush0( cdVector Y, cdVector X, ui size, dComplex AbsMin );
overror_t  __vcuf OVCUAPI   cudaVCD_flushInv( cdVector Y, cdVector X, ui size, dComplex AbsMin );
overror_t  __vcuf OVCUAPI   cudaVCD_replaceNAN( cdVector Y, cdVector X, ui size, dComplex C );

overror_t  __vcuf OVCUAPI   cusdVCD_limit(  cdVector Y, cdVector X, ui size, dComplex *d_Min, dComplex *d_Max );
overror_t  __vcuf OVCUAPI   cusdVCD_flush0( cdVector Y, cdVector X, ui size, dComplex *d_AbsMin );
overror_t  __vcuf OVCUAPI   cusdVCD_flushInv( cdVector Y, cdVector X, ui size, dComplex *d_AbsMin );
overror_t  __vcuf OVCUAPI   cusdVCD_replaceNAN( cdVector Y, cdVector X, ui size, dComplex *d_C );

overror_t  __vcuf OVCUAPI   cudaVCDx_equV( cdVector Y, cdVector X, ui size, dComplex A, dComplex B );
overror_t  __vcuf OVCUAPI   cudaVCD_addC(  cdVector Y, cdVector X, ui size, dComplex C );
overror_t  __vcuf OVCUAPI   cudaVCD_subC(  cdVector Y, cdVector X, ui size, dComplex C );
overror_t  __vcuf OVCUAPI   cudaVCD_subrC( cdVector Y, cdVector X, ui size, dComplex C );
overror_t  __vcuf OVCUAPI   cudaVCD_mulC(  cdVector Y, cdVector X, ui size, dComplex C );
overror_t  __vcuf OVCUAPI   cudaVCD_divC(  cdVector Y, cdVector X, ui size, dComplex C );
overror_t  __vcuf OVCUAPI   cudaVCD_divrC( cdVector Y, cdVector X, ui size, dComplex C );
overror_t  __vcuf OVCUAPI   cudaVCDx_divrC( cdVector Y, cdVector X, ui size, dComplex A, dComplex B, dComplex C );

overror_t  __vcuf OVCUAPI   cusdVCDx_equV( cdVector Y, cdVector X, ui size, dComplex *d_A, dComplex *d_B );
overror_t  __vcuf OVCUAPI   cusdVCD_addC(  cdVector Y, cdVector X, ui size, dComplex *d_C );
overror_t  __vcuf OVCUAPI   cusdVCD_subC(  cdVector Y, cdVector X, ui size, dComplex *d_C );
overror_t  __vcuf OVCUAPI   cusdVCD_subrC( cdVector Y, cdVector X, ui size, dComplex *d_C );
overror_t  __vcuf OVCUAPI   cusdVCD_mulC(  cdVector Y, cdVector X, ui size, dComplex *d_C );
overror_t  __vcuf OVCUAPI   cusdVCD_divC(  cdVector Y, cdVector X, ui size, dComplex *d_C );
overror_t  __vcuf OVCUAPI   cusdVCD_divrC( cdVector Y, cdVector X, ui size, dComplex *d_C );
overror_t  __vcuf OVCUAPI   cusdVCDx_divrC( cdVector Y, cdVector X, ui size, dComplex *d_A, dComplex *d_B, dComplex *d_C );

overror_t  __vcuf OVCUAPI   cudaVCD_addReC(  cdVector Y, cdVector X, ui size, double CRe );
overror_t  __vcuf OVCUAPI   cudaVCD_subReC(  cdVector Y, cdVector X, ui size, double CRe );
overror_t  __vcuf OVCUAPI   cudaVCD_subrReC( cdVector Y, cdVector X, ui size, double CRe );
overror_t  __vcuf OVCUAPI   cudaVCD_mulReC(  cdVector Y, cdVector X, ui size, double CRe );
overror_t  __vcuf OVCUAPI   cudaVCD_divReC(  cdVector Y, cdVector X, ui size, double CRe );
overror_t  __vcuf OVCUAPI   cudaVCD_divrReC( cdVector Y, cdVector X, ui size, double CRe );

overror_t  __vcuf OVCUAPI   cusdVCD_addReC(  cdVector Y, cdVector X, ui size, double *d_CRe );
overror_t  __vcuf OVCUAPI   cusdVCD_subReC(  cdVector Y, cdVector X, ui size, double *d_CRe );
overror_t  __vcuf OVCUAPI   cusdVCD_subrReC( cdVector Y, cdVector X, ui size, double *d_CRe );
overror_t  __vcuf OVCUAPI   cusdVCD_mulReC(  cdVector Y, cdVector X, ui size, double *d_CRe );
overror_t  __vcuf OVCUAPI   cusdVCD_divReC(  cdVector Y, cdVector X, ui size, double *d_CRe );
overror_t  __vcuf OVCUAPI   cusdVCD_divrReC( cdVector Y, cdVector X, ui size, double *d_CRe );

overror_t  __vcuf OVCUAPI   cudaVCD_addV(  cdVector Z, cdVector X, cdVector Y, ui size );
overror_t  __vcuf OVCUAPI   cudaVCD_subV(  cdVector Z, cdVector X, cdVector Y, ui size );
overror_t  __vcuf OVCUAPI   cudaVCD_subrV( cdVector Z, cdVector X, cdVector Y, ui size );
overror_t  __vcuf OVCUAPI   cudaVCD_mulV(  cdVector Z, cdVector X, cdVector Y, ui size );
overror_t  __vcuf OVCUAPI   cudaVCD_divV(  cdVector Z, cdVector X, cdVector Y, ui size );
overror_t  __vcuf OVCUAPI   cudaVCD_divrV( cdVector Z, cdVector X, cdVector Y, ui size );
overror_t  __vcuf OVCUAPI   cudaVCD_mulVconj(  cdVector Z, cdVector X, cdVector Y, ui size );

overror_t  __vcuf OVCUAPI   cudaVCD_addReV(  cdVector Z, cdVector X, dVector Y, ui size );
overror_t  __vcuf OVCUAPI   cudaVCD_subReV(  cdVector Z, cdVector X, dVector Y, ui size );
overror_t  __vcuf OVCUAPI   cudaVCD_subrReV( cdVector Z, cdVector X, dVector Y, ui size );
overror_t  __vcuf OVCUAPI   cudaVCD_mulReV(  cdVector Z, cdVector X, dVector Y, ui size );
overror_t  __vcuf OVCUAPI   cudaVCD_divReV(  cdVector Z, cdVector X, dVector Y, ui size );
overror_t  __vcuf OVCUAPI   cudaVCD_divrReV( cdVector Z, cdVector X, dVector Y, ui size );

overror_t  __vcuf OVCUAPI   cudaVCD_CaddV( cdVector Z, cdVector X, cdVector Y, ui siz, dComplex C );
overror_t  __vcuf OVCUAPI   cusdVCD_CaddV( cdVector Z, cdVector X, cdVector Y, ui siz, dComplex *d_C );

overror_t  __vcuf OVCUAPI   cudaVCDx_addV(  cdVector Z, cdVector X, cdVector Y, ui size, dComplex A, dComplex B );
overror_t  __vcuf OVCUAPI   cudaVCDx_subV(  cdVector Z, cdVector X, cdVector Y, ui size, dComplex A, dComplex B );
overror_t  __vcuf OVCUAPI   cudaVCDx_subrV( cdVector Z, cdVector X, cdVector Y, ui size, dComplex A, dComplex B );
overror_t  __vcuf OVCUAPI   cudaVCDx_mulV(  cdVector Z, cdVector X, cdVector Y, ui size, dComplex A, dComplex B );
overror_t  __vcuf OVCUAPI   cudaVCDx_divV(  cdVector Z, cdVector X, cdVector Y, ui size, dComplex A, dComplex B );
overror_t  __vcuf OVCUAPI   cudaVCDx_divrV( cdVector Z, cdVector X, cdVector Y, ui size, dComplex A, dComplex B );
overror_t  __vcuf OVCUAPI   cudaVCDx_mulVconj( cdVector Z, cdVector X, cdVector Y, ui size, dComplex A, dComplex B );

overror_t  __vcuf OVCUAPI   cudaVCDx_addReV(  cdVector Z, cdVector X, dVector Y, ui size, dComplex A, dComplex B );
overror_t  __vcuf OVCUAPI   cudaVCDx_subReV(  cdVector Z, cdVector X, dVector Y, ui size, dComplex A, dComplex B );
overror_t  __vcuf OVCUAPI   cudaVCDx_subrReV( cdVector Z, cdVector X, dVector Y, ui size, dComplex A, dComplex B );
overror_t  __vcuf OVCUAPI   cudaVCDx_mulReV(  cdVector Z, cdVector X, dVector Y, ui size, dComplex A, dComplex B );
overror_t  __vcuf OVCUAPI   cudaVCDx_divReV(  cdVector Z, cdVector X, dVector Y, ui size, dComplex A, dComplex B );
overror_t  __vcuf OVCUAPI   cudaVCDx_divrReV( cdVector Z, cdVector X, dVector Y, ui size, dComplex A, dComplex B );

overror_t  __vcuf OVCUAPI  cudaVCD_lincomb( cdVector Z, cdVector X, cdVector Y, ui size, dComplex CX, dComplex CY ); 
overror_t  __vcuf OVCUAPI  cudaVCD_rotateCoordinates( cdVector XYnew, cdVector XYold,
                       ui size, double costheta, double sintheta );

overror_t  __vcuf OVCUAPI   cusdVCDx_addV(  cdVector Z, cdVector X, cdVector Y, ui size, dComplex *d_A, dComplex *d_B );
overror_t  __vcuf OVCUAPI   cusdVCDx_subV(  cdVector Z, cdVector X, cdVector Y, ui size, dComplex *d_A, dComplex *d_B );
overror_t  __vcuf OVCUAPI   cusdVCDx_subrV( cdVector Z, cdVector X, cdVector Y, ui size, dComplex *d_A, dComplex *d_B );
overror_t  __vcuf OVCUAPI   cusdVCDx_mulV(  cdVector Z, cdVector X, cdVector Y, ui size, dComplex *d_A, dComplex *d_B );
overror_t  __vcuf OVCUAPI   cusdVCDx_divV(  cdVector Z, cdVector X, cdVector Y, ui size, dComplex *d_A, dComplex *d_B );
overror_t  __vcuf OVCUAPI   cusdVCDx_divrV( cdVector Z, cdVector X, cdVector Y, ui size, dComplex *d_A, dComplex *d_B );
overror_t  __vcuf OVCUAPI   cusdVCDx_mulVconj( cdVector Z, cdVector X, cdVector Y, ui size, dComplex *d_A, dComplex *d_B );

overror_t  __vcuf OVCUAPI   cusdVCDx_addReV(  cdVector Z, cdVector X, dVector Y, ui size, dComplex *d_A, dComplex *d_B );
overror_t  __vcuf OVCUAPI   cusdVCDx_subReV(  cdVector Z, cdVector X, dVector Y, ui size, dComplex *d_A, dComplex *d_B );
overror_t  __vcuf OVCUAPI   cusdVCDx_subrReV( cdVector Z, cdVector X, dVector Y, ui size, dComplex *d_A, dComplex *d_B );
overror_t  __vcuf OVCUAPI   cusdVCDx_mulReV(  cdVector Z, cdVector X, dVector Y, ui size, dComplex *d_A, dComplex *d_B );
overror_t  __vcuf OVCUAPI   cusdVCDx_divReV(  cdVector Z, cdVector X, dVector Y, ui size, dComplex *d_A, dComplex *d_B );
overror_t  __vcuf OVCUAPI   cusdVCDx_divrReV( cdVector Z, cdVector X, dVector Y, ui size, dComplex *d_A, dComplex *d_B );

overror_t  __vcuf OVCUAPI  cusdVCD_lincomb( cdVector Z, cdVector X, cdVector Y, ui size, dComplex *d_CX, dComplex *d_CY ); 
overror_t  __vcuf OVCUAPI  cusdVCD_rotateCoordinates( cdVector XYnew, cdVector XYold,
                       ui size, double *d_costheta, double *d_sintheta );

/******************** Accumulation (Y += X) ******************************/

overror_t  __vcuf OVCUAPI  cudaVCD_accV(   cdVector Y, cdVector  X, ui size );
overror_t  __vcuf OVCUAPI  cudaVCD_accVCF( cdVector Y, cfVector  X, ui size );


/***************** Functions of a sub-set of elements  ********************/

overror_t  __vcuf OVCUAPI   cudaVCD_subvector_equC(  cdVector Y, ui subsiz, ui samp, dComplex C );
overror_t  __vcuf OVCUAPI   cusdVCD_subvector_equC(  cdVector Y, ui subsiz, ui samp, dComplex *d_C );
overror_t  __vcuf OVCUAPI   cudaVCD_subvector_equV(  cdVector Y, ui subsiz, ui samp, cdVector X );

overror_t  __vcuf OVCUAPI   cudaVCD_subvector_addC(  cdVector Y, ui subsiz, ui samp, dComplex C );
overror_t  __vcuf OVCUAPI   cudaVCD_subvector_subC(  cdVector Y, ui subsiz, ui samp, dComplex C );
overror_t  __vcuf OVCUAPI   cudaVCD_subvector_subrC( cdVector Y, ui subsiz, ui samp, dComplex C );
overror_t  __vcuf OVCUAPI   cudaVCD_subvector_mulC(  cdVector Y, ui subsiz, ui samp, dComplex C );
overror_t  __vcuf OVCUAPI   cudaVCD_subvector_divC(  cdVector Y, ui subsiz, ui samp, dComplex C );
overror_t  __vcuf OVCUAPI   cudaVCD_subvector_divrC( cdVector Y, ui subsiz, ui samp, dComplex C );

overror_t  __vcuf OVCUAPI   cusdVCD_subvector_addC(  cdVector Y, ui subsiz, ui samp, dComplex *d_C );
overror_t  __vcuf OVCUAPI   cusdVCD_subvector_subC(  cdVector Y, ui subsiz, ui samp, dComplex *d_C );
overror_t  __vcuf OVCUAPI   cusdVCD_subvector_subrC( cdVector Y, ui subsiz, ui samp, dComplex *d_C );
overror_t  __vcuf OVCUAPI   cusdVCD_subvector_mulC(  cdVector Y, ui subsiz, ui samp, dComplex *d_C );
overror_t  __vcuf OVCUAPI   cusdVCD_subvector_divC(  cdVector Y, ui subsiz, ui samp, dComplex *d_C );
overror_t  __vcuf OVCUAPI   cusdVCD_subvector_divrC( cdVector Y, ui subsiz, ui samp, dComplex *d_C );

overror_t  __vcuf OVCUAPI   cudaVCD_subvector_addV(  cdVector Y, ui subsiz, ui samp, cdVector X );
overror_t  __vcuf OVCUAPI   cudaVCD_subvector_subV(  cdVector Y, ui subsiz, ui samp, cdVector X );
overror_t  __vcuf OVCUAPI   cudaVCD_subvector_subrV( cdVector Y, ui subsiz, ui samp, cdVector X );
overror_t  __vcuf OVCUAPI   cudaVCD_subvector_mulV(  cdVector Y, ui subsiz, ui samp, cdVector X );
overror_t  __vcuf OVCUAPI   cudaVCD_subvector_divV(  cdVector Y, ui subsiz, ui samp, cdVector X );
overror_t  __vcuf OVCUAPI   cudaVCD_subvector_divrV( cdVector Y, ui subsiz, ui samp, cdVector X );

/********************  Mathematical Functions ***************************/

overror_t  __vcuf OVCUAPI  cudaVCD_neg(  cdVector Y, cdVector X, ui size );
overror_t  __vcuf OVCUAPI  cudaVCD_conj( cdVector Y, cdVector X, ui size );
#define      cudaVCD_abs  cudaVD_CtoAbs
overror_t  __vcuf OVCUAPI   cudaVCD_inv(  cdVector Y, cdVector X, ui size );
overror_t  __vcuf OVCUAPI   cudaVCDx_inv( cdVector Y, cdVector X, ui size, dComplex A, dComplex B );

overror_t  __vcuf OVCUAPI   cudaVCD_square(  cdVector Y, cdVector X, ui size );
overror_t  __vcuf OVCUAPI   cudaVCDx_square( cdVector Y, cdVector X, ui size, dComplex A, dComplex B );
overror_t  __vcuf OVCUAPI   cudaVCD_cubic(   cdVector Y, cdVector X, ui size );
overror_t  __vcuf OVCUAPI   cudaVCDx_cubic(  cdVector Y, cdVector X, ui size, dComplex A, dComplex B );
overror_t  __vcuf OVCUAPI   cudaVCD_quartic( cdVector Y, cdVector X, ui size );
overror_t  __vcuf OVCUAPI   cudaVCDx_quartic( cdVector Y, cdVector X, ui size, dComplex A, dComplex B );
overror_t  __vcuf OVCUAPI   cudaVCD_ipow(    cdVector Y, cdVector X, ui size, int ipow );
overror_t  __vcuf OVCUAPI   cudaVCDx_ipow(   cdVector Y, cdVector X, ui size, int ipow,
                         dComplex A, dComplex B, dComplex C );

       /* extra fast integer powers: "unprotected", without error handling: */
overror_t  __vcuf OVCUAPI   cudaVCDu_square(  cdVector Y, cdVector X, ui size );
overror_t  __vcuf OVCUAPI   cudaVCDux_square( cdVector Y, cdVector X, ui size, dComplex A, dComplex B );
overror_t  __vcuf OVCUAPI   cudaVCDu_cubic(   cdVector Y, cdVector X, ui size );
overror_t  __vcuf OVCUAPI   cudaVCDux_cubic(  cdVector Y, cdVector X, ui size, dComplex A, dComplex B );
overror_t  __vcuf OVCUAPI   cudaVCDu_quartic( cdVector Y, cdVector X, ui size );
overror_t  __vcuf OVCUAPI   cudaVCDux_quartic( cdVector Y, cdVector X, ui size, dComplex A, dComplex B );
overror_t  __vcuf OVCUAPI   cudaVCDu_ipow(    cdVector Y, cdVector X, ui size, int ipow );
overror_t  __vcuf OVCUAPI   cudaVCDux_ipow(   cdVector Y, cdVector X, ui size, int ipow,
                          dComplex A, dComplex B, dComplex C );

overror_t  __vcuf OVCUAPI   cudaVCD_pow(     cdVector Y, cdVector X, ui size, dComplex Expo );
overror_t  __vcuf OVCUAPI   cudaVCDx_pow(    cdVector Y, cdVector X, ui size,  dComplex Expo,
                         dComplex A, dComplex B, dComplex C );
overror_t  __vcuf OVCUAPI   cudaVCD_powReExpo(  cdVector Y, cdVector X, ui size, double Expo );
overror_t  __vcuf OVCUAPI   cudaVCDx_powReExpo( cdVector Y, cdVector X, ui size, double Expo,
                            dComplex A, dComplex B, dComplex C );

overror_t  __vcuf OVCUAPI   cudaVCD_sqrt(  cdVector Y, cdVector X, ui size );
overror_t  __vcuf OVCUAPI   cudaVCDx_sqrt( cdVector Y, cdVector X, ui size, dComplex A, dComplex B, dComplex C );

overror_t  __vcuf OVCUAPI   cudaVCD_log(   cdVector Y, cdVector X, ui size );
overror_t  __vcuf OVCUAPI   cudaVCD_log2(  cdVector Y, cdVector X, ui size );
overror_t  __vcuf OVCUAPI   cudaVCD_log10( cdVector Y, cdVector X, ui size );
#define     cudaVCD_ln   cudaVCD_log
overror_t  __vcuf OVCUAPI   cudaVCDx_log(  cdVector Y, cdVector X, ui size, dComplex A, dComplex B, dComplex C );
overror_t  __vcuf OVCUAPI   cudaVCDx_log2( cdVector Y, cdVector X, ui size, dComplex A, dComplex B, dComplex C );
overror_t  __vcuf OVCUAPI   cudaVCDx_log10( cdVector Y, cdVector X, ui size, dComplex A, dComplex B, dComplex C );
#define     cudaVCDx_ln    cudaVCDx_log

overror_t  __vcuf OVCUAPI   cudaVCD_exp(  cdVector Y, cdVector X, ui size );
overror_t  __vcuf OVCUAPI   cudaVCDx_exp( cdVector Y, cdVector X, ui size, dComplex A, dComplex B, dComplex C );
overror_t  __vcuf OVCUAPI   cudaVCD_expArbBase(  cdVector Y, cdVector X, ui size, dComplex Base );
overror_t  __vcuf OVCUAPI   cudaVCDx_expArbBase( cdVector Y, cdVector X, ui size, dComplex Base,
                             dComplex A, dComplex B, dComplex C );

overror_t  __vcuf OVCUAPI   cudaVCD_sin(  cdVector Y, cdVector X, ui size );
overror_t  __vcuf OVCUAPI   cudaVCDx_sin( cdVector Y, cdVector X, ui size, dComplex A, dComplex B, dComplex C );
overror_t  __vcuf OVCUAPI   cudaVCD_cos(  cdVector Y, cdVector X, ui size );
overror_t  __vcuf OVCUAPI   cudaVCDx_cos( cdVector Y, cdVector X, ui size, dComplex A, dComplex B, dComplex C );
overror_t  __vcuf OVCUAPI   cudaVCD_tan(  cdVector Y, cdVector X, ui size );
overror_t  __vcuf OVCUAPI   cudaVCDx_tan( cdVector Y, cdVector X, ui size, dComplex A, dComplex B, dComplex C );

overror_t  __vcuf OVCUAPI   cudaVCD_asin(  cdVector Y, cdVector X, ui size );
overror_t  __vcuf OVCUAPI   cudaVCDx_asin( cdVector Y, cdVector X, ui size, dComplex A, dComplex B, dComplex C );
overror_t  __vcuf OVCUAPI   cudaVCD_acos(  cdVector Y, cdVector X, ui size );
overror_t  __vcuf OVCUAPI   cudaVCDx_acos( cdVector Y, cdVector X, ui size, dComplex A, dComplex B, dComplex C );
overror_t  __vcuf OVCUAPI   cudaVCD_atan(  cdVector Y, cdVector X, ui size );
overror_t  __vcuf OVCUAPI   cudaVCDx_atan( cdVector Y, cdVector X, ui size, dComplex A, dComplex B, dComplex C );

overror_t  __vcuf OVCUAPI   cudaVCD_sinh(  cdVector Y, cdVector X, ui size );
overror_t  __vcuf OVCUAPI   cudaVCDx_sinh( cdVector Y, cdVector X, ui size, dComplex A, dComplex B, dComplex C );
overror_t  __vcuf OVCUAPI   cudaVCD_cosh(  cdVector Y, cdVector X, ui size );
overror_t  __vcuf OVCUAPI   cudaVCDx_cosh( cdVector Y, cdVector X, ui size, dComplex A, dComplex B, dComplex C );
overror_t  __vcuf OVCUAPI   cudaVCD_tanh(  cdVector Y, cdVector X, ui size );
overror_t  __vcuf OVCUAPI   cudaVCDx_tanh( cdVector Y, cdVector X, ui size, dComplex A, dComplex B, dComplex C );

	/*  cusdVCF_ variant: scalar values passed by address on device memory: */
overror_t  __vcuf OVCUAPI   cusdVCDx_inv( cdVector Y, cdVector X, ui size, dComplex *d_A, dComplex *d_B );
overror_t  __vcuf OVCUAPI   cusdVCDx_square( cdVector Y, cdVector X, ui size, dComplex *d_A, dComplex *d_B );
overror_t  __vcuf OVCUAPI   cusdVCDx_cubic(  cdVector Y, cdVector X, ui size, dComplex *d_A, dComplex *d_B );
overror_t  __vcuf OVCUAPI   cusdVCDx_quartic( cdVector Y, cdVector X, ui size, dComplex *d_A, dComplex *d_B );
overror_t  __vcuf OVCUAPI   cusdVCDx_ipow(   cdVector Y, cdVector X, ui size, int ipow, dComplex *d_A, dComplex *d_B, dComplex *d_C );
overror_t  __vcuf OVCUAPI   cusdVCDux_square( cdVector Y, cdVector X, ui size, dComplex *d_A, dComplex *d_B );
overror_t  __vcuf OVCUAPI   cusdVCDux_cubic(  cdVector Y, cdVector X, ui size, dComplex *d_A, dComplex *d_B );
overror_t  __vcuf OVCUAPI   cusdVCDux_quartic( cdVector Y, cdVector X, ui size, dComplex *d_A, dComplex *d_B );
overror_t  __vcuf OVCUAPI   cusdVCDux_ipow(   cdVector Y, cdVector X, ui size, int ipow, dComplex *d_A, dComplex *d_B, dComplex *d_C );
overror_t  __vcuf OVCUAPI   cusdVCDx_pow(    cdVector Y, cdVector X, ui size,  dComplex Expo, dComplex *d_A, dComplex *d_B, dComplex *d_C );
overror_t  __vcuf OVCUAPI   cusdVCDx_powReExpo( cdVector Y, cdVector X, ui size, double Expo, dComplex *d_A, dComplex *d_B, dComplex *d_C );
overror_t  __vcuf OVCUAPI   cusdVCDx_sqrt( cdVector Y, cdVector X, ui size, dComplex *d_A, dComplex *d_B, dComplex *d_C );
overror_t  __vcuf OVCUAPI   cusdVCDx_log(  cdVector Y, cdVector X, ui size, dComplex *d_A, dComplex *d_B, dComplex *d_C );
overror_t  __vcuf OVCUAPI   cusdVCDx_log2( cdVector Y, cdVector X, ui size, dComplex *d_A, dComplex *d_B, dComplex *d_C );
overror_t  __vcuf OVCUAPI   cusdVCDx_log10( cdVector Y, cdVector X, ui size, dComplex *d_A, dComplex *d_B, dComplex *d_C );
#define     cusdVCDx_ln    cusdVCDx_log
overror_t  __vcuf OVCUAPI   cusdVCDx_exp( cdVector Y, cdVector X, ui size, dComplex *d_A, dComplex *d_B, dComplex *d_C );
overror_t  __vcuf OVCUAPI   cusdVCDx_expArbBase( cdVector Y, cdVector X, ui size, dComplex Base, dComplex *d_A, dComplex *d_B, dComplex *d_C );
overror_t  __vcuf OVCUAPI   cusdVCDx_sin( cdVector Y, cdVector X, ui size, dComplex *d_A, dComplex *d_B, dComplex *d_C );
overror_t  __vcuf OVCUAPI   cusdVCDx_cos( cdVector Y, cdVector X, ui size, dComplex *d_A, dComplex *d_B, dComplex *d_C );
overror_t  __vcuf OVCUAPI   cusdVCDx_tan( cdVector Y, cdVector X, ui size, dComplex *d_A, dComplex *d_B, dComplex *d_C );
overror_t  __vcuf OVCUAPI   cusdVCDx_asin( cdVector Y, cdVector X, ui size, dComplex *d_A, dComplex *d_B, dComplex *d_C );
overror_t  __vcuf OVCUAPI   cusdVCDx_acos( cdVector Y, cdVector X, ui size, dComplex *d_A, dComplex *d_B, dComplex *d_C );
overror_t  __vcuf OVCUAPI   cusdVCDx_atan( cdVector Y, cdVector X, ui size, dComplex *d_A, dComplex *d_B, dComplex *d_C );
overror_t  __vcuf OVCUAPI   cusdVCDx_sinh( cdVector Y, cdVector X, ui size, dComplex *d_A, dComplex *d_B, dComplex *d_C );
overror_t  __vcuf OVCUAPI   cusdVCDx_cosh( cdVector Y, cdVector X, ui size, dComplex *d_A, dComplex *d_B, dComplex *d_C );
overror_t  __vcuf OVCUAPI   cusdVCDx_tanh( cdVector Y, cdVector X, ui size, dComplex *d_A, dComplex *d_B, dComplex *d_C );

#ifdef __cplusplus
} // end of extern "C"
#endif

/******************  VCDcu_ functions: **********************************
	act on host memory, using the CUDA device for processing
************************************************************************/



#ifdef __cplusplus
extern "C" {
#endif

/************************* Comparisons ****************************/

ui   __vf OVCUAPI   VCDcu_cmp_eq0( cdVector Y, cdVector X, ui size );
ui   __vf OVCUAPI   VCDcu_cmp_ne0( cdVector Y, cdVector X, ui size );
ui   __vf OVCUAPI   VCDcu_cmp_eqC( cdVector Y, cdVector X, ui size, dComplex C );
ui   __vf OVCUAPI   VCDcu_cmp_neC( cdVector Y, cdVector X, ui size, dComplex C );
ui   __vf OVCUAPI   VCDcu_cmp_eqV( cdVector Z, cdVector X, cdVector Y, ui size );
ui   __vf OVCUAPI   VCDcu_cmp_neV( cdVector Z, cdVector X, cdVector Y, ui size );
ui   __vf OVCUAPI   VCDcu_cnt_eq0( cdVector X, ui size );
ui   __vf OVCUAPI   VCDcu_cnt_ne0( cdVector X, ui size );
ui   __vf OVCUAPI   VCDcu_cnt_eqC( cdVector X, ui size, dComplex C );
ui   __vf OVCUAPI   VCDcu_cnt_neC( cdVector X, ui size, dComplex C );
ui   __vf OVCUAPI   VCDcu_cnt_eqV( cdVector X, cdVector Y, ui size );
ui   __vf OVCUAPI   VCDcu_cnt_neV( cdVector X, cdVector Y, ui size );
/*
ui   __vf OVCUAPI   VCDcu_cmp_eq0ind( uiVector Ind, cdVector X, ui size );
ui   __vf OVCUAPI   VCDcu_cmp_ne0ind( uiVector Ind, cdVector X, ui size );
ui   __vf OVCUAPI   VCDcu_cmp_eqCind( uiVector Ind, cdVector X, ui size, dComplex C );
ui   __vf OVCUAPI   VCDcu_cmp_neCind( uiVector Ind, cdVector X, ui size, dComplex C );
ui   __vf OVCUAPI   VCDcu_cmp_eqVind( uiVector Ind, cdVector X, cdVector Y, ui size );
ui   __vf OVCUAPI   VCDcu_cmp_neVind( uiVector Ind, cdVector X, cdVector Y, ui size );
*/

/********************  Standard Arithmetics   ***************************/

void  __vf OVCUAPI   VCDcu_limit(  cdVector Y, cdVector X, ui size, dComplex Min, dComplex Max );
void  __vf OVCUAPI   VCDcu_flush0( cdVector Y, cdVector X, ui size, dComplex AbsMin );
void  __vf OVCUAPI   VCDcu_flushInv( cdVector Y, cdVector X, ui size, dComplex AbsMin );
void  __vf OVCUAPI   VCDcu_replaceNAN( cdVector Y, cdVector X, ui size, dComplex C );

void  __vf OVCUAPI   VCDxcu_equV( cdVector Y, cdVector X, ui size, dComplex A, dComplex B );
void  __vf OVCUAPI   VCDcu_addC(  cdVector Y, cdVector X, ui size, dComplex C );
void  __vf OVCUAPI   VCDcu_subC(  cdVector Y, cdVector X, ui size, dComplex C );
void  __vf OVCUAPI   VCDcu_subrC( cdVector Y, cdVector X, ui size, dComplex C );
void  __vf OVCUAPI   VCDcu_mulC(  cdVector Y, cdVector X, ui size, dComplex C );
void  __vf OVCUAPI   VCDcu_divC(  cdVector Y, cdVector X, ui size, dComplex C );
void  __vf OVCUAPI   VCDcu_divrC( cdVector Y, cdVector X, ui size, dComplex C );
void  __vf OVCUAPI   VCDxcu_divrC( cdVector Y, cdVector X, ui size, dComplex A, dComplex B, dComplex C );

void  __vf OVCUAPI   VCDcu_addReC(  cdVector Y, cdVector X, ui size, double CRe );
void  __vf OVCUAPI   VCDcu_subReC(  cdVector Y, cdVector X, ui size, double CRe );
void  __vf OVCUAPI   VCDcu_subrReC( cdVector Y, cdVector X, ui size, double CRe );
void  __vf OVCUAPI   VCDcu_mulReC(  cdVector Y, cdVector X, ui size, double CRe );
void  __vf OVCUAPI   VCDcu_divReC(  cdVector Y, cdVector X, ui size, double CRe );
void  __vf OVCUAPI   VCDcu_divrReC( cdVector Y, cdVector X, ui size, double CRe );

void  __vf OVCUAPI   VCDcu_addV(  cdVector Z, cdVector X, cdVector Y, ui size );
void  __vf OVCUAPI   VCDcu_subV(  cdVector Z, cdVector X, cdVector Y, ui size );
void  __vf OVCUAPI   VCDcu_subrV( cdVector Z, cdVector X, cdVector Y, ui size );
void  __vf OVCUAPI   VCDcu_mulV(  cdVector Z, cdVector X, cdVector Y, ui size );
void  __vf OVCUAPI   VCDcu_divV(  cdVector Z, cdVector X, cdVector Y, ui size );
void  __vf OVCUAPI   VCDcu_divrV( cdVector Z, cdVector X, cdVector Y, ui size );
void  __vf OVCUAPI   VCDcu_mulVconj(  cdVector Z, cdVector X, cdVector Y, ui size );

void  __vf OVCUAPI   VCDcu_addReV(  cdVector Z, cdVector X, dVector Y, ui size );
void  __vf OVCUAPI   VCDcu_subReV(  cdVector Z, cdVector X, dVector Y, ui size );
void  __vf OVCUAPI   VCDcu_subrReV( cdVector Z, cdVector X, dVector Y, ui size );
void  __vf OVCUAPI   VCDcu_mulReV(  cdVector Z, cdVector X, dVector Y, ui size );
void  __vf OVCUAPI   VCDcu_divReV(  cdVector Z, cdVector X, dVector Y, ui size );
void  __vf OVCUAPI   VCDcu_divrReV( cdVector Z, cdVector X, dVector Y, ui size );

void  __vf OVCUAPI   VCDcu_CaddV( cdVector Z, cdVector X, cdVector Y, ui siz, dComplex C );

void  __vf OVCUAPI   VCDxcu_addV(  cdVector Z, cdVector X, cdVector Y, ui size, dComplex A, dComplex B );
void  __vf OVCUAPI   VCDxcu_subV(  cdVector Z, cdVector X, cdVector Y, ui size, dComplex A, dComplex B );
void  __vf OVCUAPI   VCDxcu_subrV( cdVector Z, cdVector X, cdVector Y, ui size, dComplex A, dComplex B );
void  __vf OVCUAPI   VCDxcu_mulV(  cdVector Z, cdVector X, cdVector Y, ui size, dComplex A, dComplex B );
void  __vf OVCUAPI   VCDxcu_divV(  cdVector Z, cdVector X, cdVector Y, ui size, dComplex A, dComplex B );
void  __vf OVCUAPI   VCDxcu_divrV( cdVector Z, cdVector X, cdVector Y, ui size, dComplex A, dComplex B );
void  __vf OVCUAPI   VCDxcu_mulVconj( cdVector Z, cdVector X, cdVector Y, ui size, dComplex A, dComplex B );

void  __vf OVCUAPI   VCDxcu_addReV(  cdVector Z, cdVector X, dVector Y, ui size, dComplex A, dComplex B );
void  __vf OVCUAPI   VCDxcu_subReV(  cdVector Z, cdVector X, dVector Y, ui size, dComplex A, dComplex B );
void  __vf OVCUAPI   VCDxcu_subrReV( cdVector Z, cdVector X, dVector Y, ui size, dComplex A, dComplex B );
void  __vf OVCUAPI   VCDxcu_mulReV(  cdVector Z, cdVector X, dVector Y, ui size, dComplex A, dComplex B );
void  __vf OVCUAPI   VCDxcu_divReV(  cdVector Z, cdVector X, dVector Y, ui size, dComplex A, dComplex B );
void  __vf OVCUAPI   VCDxcu_divrReV( cdVector Z, cdVector X, dVector Y, ui size, dComplex A, dComplex B );

void __vf OVCUAPI  VCDcu_lincomb( cdVector Z, cdVector X, cdVector Y, ui size, dComplex CX, dComplex CY ); 
void __vf OVCUAPI  VCDcu_rotateCoordinates( cdVector XYnew, cdVector XYold,
                       ui size, double costheta, double sintheta );


/******************** Accumulation (Y += X) ******************************/

void __vf OVCUAPI  VCDcu_accV(   cdVector Y, cdVector  X, ui size );
void __vf OVCUAPI  VCDcu_accVCF( cdVector Y, cfVector  X, ui size );


/***************** Functions of a sub-set of elements  ********************/

void  __vf OVCUAPI   VCDcu_subvector_equC(  cdVector Y, ui subsiz, ui samp, dComplex C );
void  __vf OVCUAPI   VCDcu_subvector_equV(  cdVector Y, ui subsiz, ui samp, cdVector X );

void  __vf OVCUAPI   VCDcu_subvector_addC(  cdVector Y, ui subsiz, ui samp, dComplex C );
void  __vf OVCUAPI   VCDcu_subvector_subC(  cdVector Y, ui subsiz, ui samp, dComplex C );
void  __vf OVCUAPI   VCDcu_subvector_subrC( cdVector Y, ui subsiz, ui samp, dComplex C );
void  __vf OVCUAPI   VCDcu_subvector_mulC(  cdVector Y, ui subsiz, ui samp, dComplex C );
void  __vf OVCUAPI   VCDcu_subvector_divC(  cdVector Y, ui subsiz, ui samp, dComplex C );
void  __vf OVCUAPI   VCDcu_subvector_divrC( cdVector Y, ui subsiz, ui samp, dComplex C );

void  __vf OVCUAPI   VCDcu_subvector_addV(  cdVector Y, ui subsiz, ui samp, cdVector X );
void  __vf OVCUAPI   VCDcu_subvector_subV(  cdVector Y, ui subsiz, ui samp, cdVector X );
void  __vf OVCUAPI   VCDcu_subvector_subrV( cdVector Y, ui subsiz, ui samp, cdVector X );
void  __vf OVCUAPI   VCDcu_subvector_mulV(  cdVector Y, ui subsiz, ui samp, cdVector X );
void  __vf OVCUAPI   VCDcu_subvector_divV(  cdVector Y, ui subsiz, ui samp, cdVector X );
void  __vf OVCUAPI   VCDcu_subvector_divrV( cdVector Y, ui subsiz, ui samp, cdVector X );

/********************  Mathematical Functions ***************************/

int  __vf OVCUAPI  VCDcu_abs(  dVector Y, cdVector X, ui size );
int  __vf OVCUAPI  VCDcu_neg(  cdVector Y, cdVector X, ui size );
int  __vf OVCUAPI  VCDcu_conj( cdVector Y, cdVector X, ui size );
int  __vf OVCUAPI  VCDcu_inv(  cdVector Y, cdVector X, ui size );
int  __vf OVCUAPI  VCDxcu_inv( cdVector Y, cdVector X, ui size, dComplex A, dComplex B );

int  __vf OVCUAPI   VCDcu_square(  cdVector Y, cdVector X, ui size );
int  __vf OVCUAPI   VCDxcu_square( cdVector Y, cdVector X, ui size, dComplex A, dComplex B );
int  __vf OVCUAPI   VCDcu_cubic(   cdVector Y, cdVector X, ui size );
int  __vf OVCUAPI   VCDxcu_cubic(  cdVector Y, cdVector X, ui size, dComplex A, dComplex B );
int  __vf OVCUAPI   VCDcu_quartic( cdVector Y, cdVector X, ui size );
int  __vf OVCUAPI   VCDxcu_quartic( cdVector Y, cdVector X, ui size, dComplex A, dComplex B );
int  __vf OVCUAPI   VCDcu_ipow(    cdVector Y, cdVector X, ui size, int ipow );
int  __vf OVCUAPI   VCDxcu_ipow(   cdVector Y, cdVector X, ui size, int ipow,
                         dComplex A, dComplex B, dComplex C );

       /* unprotected integer powers: */
int  __vf OVCUAPI   VCDucu_square(  cdVector Y, cdVector X, ui size );
int  __vf OVCUAPI   VCDuxcu_square( cdVector Y, cdVector X, ui size, dComplex A, dComplex B );
int  __vf OVCUAPI   VCDucu_cubic(   cdVector Y, cdVector X, ui size );
int  __vf OVCUAPI   VCDuxcu_cubic(  cdVector Y, cdVector X, ui size, dComplex A, dComplex B );
int  __vf OVCUAPI   VCDucu_quartic( cdVector Y, cdVector X, ui size );
int  __vf OVCUAPI   VCDuxcu_quartic( cdVector Y, cdVector X, ui size, dComplex A, dComplex B );
int  __vf OVCUAPI   VCDucu_ipow(    cdVector Y, cdVector X, ui size, int ipow );
int  __vf OVCUAPI   VCDuxcu_ipow(   cdVector Y, cdVector X, ui size, int ipow,
                          dComplex A, dComplex B, dComplex C );

int  __vf OVCUAPI   VCDcu_pow(     cdVector Y, cdVector X, ui size, dComplex Expo );
int  __vf OVCUAPI   VCDxcu_pow(    cdVector Y, cdVector X, ui size,  dComplex Expo,
                         dComplex A, dComplex B, dComplex C );
int  __vf OVCUAPI   VCDcu_powReExpo(  cdVector Y, cdVector X, ui size, double Expo );
int  __vf OVCUAPI   VCDxcu_powReExpo( cdVector Y, cdVector X, ui size, double Expo,
                            dComplex A, dComplex B, dComplex C );

int  __vf OVCUAPI   VCDcu_sqrt(  cdVector Y, cdVector X, ui size );
int  __vf OVCUAPI   VCDxcu_sqrt( cdVector Y, cdVector X, ui size, dComplex A, dComplex B, dComplex C );

int  __vf OVCUAPI   VCDcu_log(   cdVector Y, cdVector X, ui size );
int  __vf OVCUAPI   VCDcu_log2(  cdVector Y, cdVector X, ui size );
int  __vf OVCUAPI   VCDcu_log10( cdVector Y, cdVector X, ui size );
#define     VCDcu_ln   VCDcu_log
int  __vf OVCUAPI   VCDxcu_log(  cdVector Y, cdVector X, ui size, dComplex A, dComplex B, dComplex C );
int  __vf OVCUAPI   VCDxcu_log2( cdVector Y, cdVector X, ui size, dComplex A, dComplex B, dComplex C );
int  __vf OVCUAPI   VCDxcu_log10( cdVector Y, cdVector X, ui size, dComplex A, dComplex B, dComplex C );
#define     VCDxcu_ln    VCDxcu_log

int  __vf OVCUAPI   VCDcu_exp(  cdVector Y, cdVector X, ui size );
int  __vf OVCUAPI   VCDxcu_exp( cdVector Y, cdVector X, ui size, dComplex A, dComplex B, dComplex C );
int  __vf OVCUAPI   VCDcu_expArbBase(  cdVector Y, cdVector X, ui size, dComplex Base );
int  __vf OVCUAPI   VCDxcu_expArbBase( cdVector Y, cdVector X, ui size, dComplex Base,
                             dComplex A, dComplex B, dComplex C );

int  __vf OVCUAPI   VCDcu_sin(  cdVector Y, cdVector X, ui size );
int  __vf OVCUAPI   VCDxcu_sin( cdVector Y, cdVector X, ui size, dComplex A, dComplex B, dComplex C );
int  __vf OVCUAPI   VCDcu_cos(  cdVector Y, cdVector X, ui size );
int  __vf OVCUAPI   VCDxcu_cos( cdVector Y, cdVector X, ui size, dComplex A, dComplex B, dComplex C );
int  __vf OVCUAPI   VCDcu_tan(  cdVector Y, cdVector X, ui size );
int  __vf OVCUAPI   VCDxcu_tan( cdVector Y, cdVector X, ui size, dComplex A, dComplex B, dComplex C );

int  __vf OVCUAPI   VCDcu_asin(  cdVector Y, cdVector X, ui size );
int  __vf OVCUAPI   VCDxcu_asin( cdVector Y, cdVector X, ui size, dComplex A, dComplex B, dComplex C );
int  __vf OVCUAPI   VCDcu_acos(  cdVector Y, cdVector X, ui size );
int  __vf OVCUAPI   VCDxcu_acos( cdVector Y, cdVector X, ui size, dComplex A, dComplex B, dComplex C );
int  __vf OVCUAPI   VCDcu_atan(  cdVector Y, cdVector X, ui size );
int  __vf OVCUAPI   VCDxcu_atan( cdVector Y, cdVector X, ui size, dComplex A, dComplex B, dComplex C );

int  __vf OVCUAPI   VCDcu_sinh(  cdVector Y, cdVector X, ui size );
int  __vf OVCUAPI   VCDxcu_sinh( cdVector Y, cdVector X, ui size, dComplex A, dComplex B, dComplex C );
int  __vf OVCUAPI   VCDcu_cosh(  cdVector Y, cdVector X, ui size );
int  __vf OVCUAPI   VCDxcu_cosh( cdVector Y, cdVector X, ui size, dComplex A, dComplex B, dComplex C );
int  __vf OVCUAPI   VCDcu_tanh(  cdVector Y, cdVector X, ui size );
int  __vf OVCUAPI   VCDxcu_tanh( cdVector Y, cdVector X, ui size, dComplex A, dComplex B, dComplex C );

#ifdef __cplusplus
} // end of extern "C"
#endif


#endif /* __cudaVCDMATH_H */
