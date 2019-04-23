/*  VPFmath.h

  vector management functions:
  arithmetic and math functions performed on each individual element
  of an array or vector of data type "fPolar"  (polar complex float)

  Copyright (c) 1996-2017 by OptiCode - Dr. Martin Sander Software Dev.
  All Rights Reserved.
*/

#ifndef __VPFMATH_H
#define __VPFMATH_H

#ifndef __VPFSTD_H
#include <VPFstd.h>
#endif


#ifdef __cplusplus
extern "C" {
#endif

/********************* Comparisons ****************************/

ui   __vf   VPF_cmp_eq0( pfVector Y, pfVector X, ui size );
ui   __vf   VPF_cmp_ne0( pfVector Y, pfVector X, ui size );
ui   __vf   VPF_cmp_eqV( pfVector Z, pfVector X, pfVector Y, ui size );
ui   __vf   VPF_cmp_neV( pfVector Z, pfVector X, pfVector Y, ui size );
ui   __vf   VPF_cmp_eq0ind( uiVector Ind, pfVector X, ui size );
ui   __vf   VPF_cmp_ne0ind( uiVector Ind, pfVector X, ui size );
ui   __vf   VPF_cmp_eqVind( uiVector Ind, pfVector X, pfVector Y, ui size );
ui   __vf   VPF_cmp_neVind( uiVector Ind, pfVector X, pfVector Y, ui size );
ui   __vf   VPF_cnt_eq0( pfVector X, ui size );
ui   __vf   VPF_cnt_ne0( pfVector X, ui size );
ui   __vf   VPF_cnt_eqV( pfVector X, pfVector Y, ui size );
ui   __vf   VPF_cnt_neV( pfVector X, pfVector Y, ui size );

#if defined __cplusplus && defined _CMATH_CLASSDEFS && defined __BORLANDC__ && defined _WIN64
} // cannot be extern "C" for C++Builder on Win64, if fPolar is a class
#endif
ui   __vf   VPF_cmp_eqC( pfVector Y, pfVector X, ui size, fPolar C );
ui   __vf   VPF_cmp_neC( pfVector Y, pfVector X, ui size, fPolar C );
ui   __vf   VPF_cmp_eqCind( uiVector Ind, pfVector X, ui size, fPolar C );
ui   __vf   VPF_cmp_neCind( uiVector Ind, pfVector X, ui size, fPolar C );
ui   __vf   VPF_cnt_eqC( pfVector X, ui size, fPolar C );
ui   __vf   VPF_cnt_neC( pfVector X, ui size, fPolar C );

/********************  Standard Arithmetics   ***************************/

void  __vf   VPF_replaceNAN( pfVector Y, pfVector X, ui siz, fPolar C );

void  __vf   VPF_mulC(   pfVector Y, pfVector X, ui size, fPolar C );
void  __vf   VPF_divC(   pfVector Y, pfVector X, ui size, fPolar C );
void  __vf   VPF_divrC(  pfVector Y, pfVector X, ui size, fPolar C );

#if defined __cplusplus && defined _CMATH_CLASSDEFS && defined __BORLANDC__ && defined _WIN64
extern "C" {
#endif
void  __vf   VPF_mulReC(  pfVector Y, pfVector X, ui size, float CRe );
void  __vf   VPF_divReC(  pfVector Y, pfVector X, ui size, float CRe );
void  __vf   VPF_divrReC( pfVector Y, pfVector X, ui size, float CRe );

void  __vf   VPF_mulV(  pfVector Z, pfVector X, pfVector Y, ui size );
void  __vf   VPF_divV(  pfVector Z, pfVector X, pfVector Y, ui size );
void  __vf   VPF_divrV( pfVector Z, pfVector X, pfVector Y, ui size );

void  __vf   VPF_mulReV(  pfVector Z, pfVector X, fVector Y, ui size );
void  __vf   VPF_divReV(  pfVector Z, pfVector X, fVector Y, ui size );
void  __vf   VPF_divrReV( pfVector Z, pfVector X, fVector Y, ui size );


/*************** Functions of a sub-set of elements  ********************/

#if defined __cplusplus && defined _CMATH_CLASSDEFS && defined __BORLANDC__ && defined _WIN64
} // cannot be extern "C" for C++Builder on Win64, if fPolar is a class
#endif
void  __vf  VPF_subvector_equC(  pfVector Y, ui subsiz, ui samp,
                                 fPolar C );
void  __vf  VPF_subvector_mulC(  pfVector Y, ui subsiz, ui samp,
                                 fPolar C );
void  __vf  VPF_subvector_divC(  pfVector Y, ui subsiz, ui samp,
                                 fPolar C );
void  __vf  VPF_subvector_divrC( pfVector Y, ui subsiz, ui samp,
                                 fPolar C );

#if defined __cplusplus && defined _CMATH_CLASSDEFS && defined __BORLANDC__ && defined _WIN64
extern "C" {
#endif
void  __vf  VPF_subvector_equV(  pfVector Y, ui subsiz, ui samp,
                                 pfVector X );
void  __vf  VPF_subvector_mulV(  pfVector Y, ui subsiz, ui samp,
                                 pfVector X );
void  __vf  VPF_subvector_divV(  pfVector Y, ui subsiz, ui samp,
                                 pfVector X );
void  __vf  VPF_subvector_divrV( pfVector Y, ui subsiz, ui samp,
                                 pfVector X );


/*********************  Mathematical Functions *************************/

int   __vf   VPF_neg(  pfVector Y, pfVector X, ui size );
int   __vf   VPF_conj( pfVector Y, pfVector X, ui size );
int   __vf   VPF_abs(   fVector Y, pfVector X, ui size );
int   __vf   VPF_inv(  pfVector Y, pfVector X, ui size );

int  __vf   VPF_square(  pfVector Y, pfVector X, ui size );
int  __vf   VPF_cubic(   pfVector Y, pfVector X, ui size );
int  __vf   VPF_quartic( pfVector Y, pfVector X, ui size );
int  __vf   VPF_ipow(    pfVector Y, pfVector X, ui size, int ipow );

    /* extra fast integer powers: "unprotected", without error handling: */
int  __vf   VPFu_square(   pfVector Y, pfVector X, ui size );
int  __vf   VPFu_cubic(    pfVector Y, pfVector X, ui size );
int  __vf   VPFu_quartic(  pfVector Y, pfVector X, ui size );
int  __vf   VPFu_ipow(     pfVector Y, pfVector X, ui size, int ipow );

int  __vf   VPF_powReExpo(  pfVector Y, pfVector X, ui size, float Expo );
int  __vf   VPF_sqrt(  pfVector Y, pfVector X, ui size );
int  __vf   VPF_logtoC(   cfVector Y, pfVector X, ui size );
int  __vf   VPF_log2toC(  cfVector Y, pfVector X, ui size );
int  __vf   VPF_log10toC( cfVector Y, pfVector X, ui size );
#define     VPF_lntoC   VPF_logtoC

int  __vf   VCF_exptoP(  pfVector Y, cfVector X, ui size );

#ifdef __cplusplus
}  // end of extern "C"
#endif


#endif /* __VPFMATH_H */
