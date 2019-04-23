/*  VPEmath.h

  vector management functions:
  arithmetic and math functions performed on each individual element
  of an array or vector of data type "ePolar"  (polar complex extended)

  Copyright (c) 1996-2017 by OptiCode - Dr. Martin Sander Software Dev.
  All Rights Reserved.
*/

#ifndef __VPEMATH_H
#define __VPEMATH_H

#ifndef __VPESTD_H
#include <VPEstd.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif

#if (defined __BORLANDC__) && !(defined _WIN64)   /* 80-bit IEEE numbers supported.
                         The following  200+ lines apply only to Borland C++ 32-bit */

/********************* Comparisons ****************************/

ui   __vf   VPE_cmp_eq0( peVector Y, peVector X, ui size );
ui   __vf   VPE_cmp_ne0( peVector Y, peVector X, ui size );
ui   __vf   VPE_cmp_eqC( peVector Y, peVector X, ui size, ePolar C );
ui   __vf   VPE_cmp_neC( peVector Y, peVector X, ui size, ePolar C );
ui   __vf   VPE_cmp_eqV( peVector Z, peVector X, peVector Y, ui size );
ui   __vf   VPE_cmp_neV( peVector Z, peVector X, peVector Y, ui size );
ui   __vf   VPE_cmp_eq0ind( uiVector Ind, peVector X, ui size );
ui   __vf   VPE_cmp_ne0ind( uiVector Ind, peVector X, ui size );
ui   __vf   VPE_cmp_eqCind( uiVector Ind, peVector X, ui size, ePolar C );
ui   __vf   VPE_cmp_neCind( uiVector Ind, peVector X, ui size, ePolar C );
ui   __vf   VPE_cmp_eqVind( uiVector Ind, peVector X, peVector Y, ui size );
ui   __vf   VPE_cmp_neVind( uiVector Ind, peVector X, peVector Y, ui size );
ui   __vf   VPE_cnt_eq0( peVector X, ui size );
ui   __vf   VPE_cnt_ne0( peVector X, ui size );
ui   __vf   VPE_cnt_eqC( peVector X, ui size, ePolar C );
ui   __vf   VPE_cnt_neC( peVector X, ui size, ePolar C );
ui   __vf   VPE_cnt_eqV( peVector X, peVector Y, ui size );
ui   __vf   VPE_cnt_neV( peVector X, peVector Y, ui size );


/********************  Standard Arithmetics   ***************************/

void  __vf   VPE_replaceNAN( peVector Y, peVector X, ui siz, ePolar C );

void  __vf   VPE_mulC(   peVector Y, peVector X, ui size, ePolar C );
void  __vf   VPE_divC(   peVector Y, peVector X, ui size, ePolar C );
void  __vf   VPE_divrC(  peVector Y, peVector X, ui size, ePolar C );

void  __vf   VPE_mulReC(  peVector Y, peVector X, ui size, extended CRe );
void  __vf   VPE_divReC(  peVector Y, peVector X, ui size, extended CRe );
void  __vf   VPE_divrReC( peVector Y, peVector X, ui size, extended CRe );

void  __vf   VPE_mulV(  peVector Z, peVector X, peVector Y, ui size );
void  __vf   VPE_divV(  peVector Z, peVector X, peVector Y, ui size );
void  __vf   VPE_divrV( peVector Z, peVector X, peVector Y, ui size );

void  __vf   VPE_mulReV(  peVector Z, peVector X, eVector Y, ui size );
void  __vf   VPE_divReV(  peVector Z, peVector X, eVector Y, ui size );
void  __vf   VPE_divrReV( peVector Z, peVector X, eVector Y, ui size );


/*************** Functions of a sub-set of elements  ********************/

void  __vf  VPE_subvector_equC(  peVector Y, ui subsiz, ui samp,
                                 ePolar C );
void  __vf  VPE_subvector_equV(  peVector Y, ui subsiz, ui samp,
                                 peVector X );

void  __vf  VPE_subvector_mulC(  peVector Y, ui subsiz, ui samp,
                                 ePolar C );
void  __vf  VPE_subvector_divC(  peVector Y, ui subsiz, ui samp,
                                 ePolar C );
void  __vf  VPE_subvector_divrC( peVector Y, ui subsiz, ui samp,
                                 ePolar C );

void  __vf  VPE_subvector_mulV(  peVector Y, ui subsiz, ui samp,
                                 peVector X );
void  __vf  VPE_subvector_divV(  peVector Y, ui subsiz, ui samp,
                                 peVector X );
void  __vf  VPE_subvector_divrV( peVector Y, ui subsiz, ui samp,
                                 peVector X );


/*********************  Mathematical Functions *************************/

int   __vf   VPE_neg(  peVector Y, peVector X, ui size );
int   __vf   VPE_conj( peVector Y, peVector X, ui size );
int   __vf   VPE_abs(   eVector Y, peVector X, ui size );
int   __vf   VPE_inv(  peVector Y, peVector X, ui size );

int  __vf   VPE_square(  peVector Y, peVector X, ui size );
int  __vf   VPE_cubic(   peVector Y, peVector X, ui size );
int  __vf   VPE_quartic( peVector Y, peVector X, ui size );
int  __vf   VPE_ipow(    peVector Y, peVector X, ui size, int ipow );

    /* extra fast integer powers: "unprotected", without error handling: */
int  __vf   VPEu_square(   peVector Y, peVector X, ui size );
int  __vf   VPEu_cubic(    peVector Y, peVector X, ui size );
int  __vf   VPEu_quartic(  peVector Y, peVector X, ui size );
int  __vf   VPEu_ipow(     peVector Y, peVector X, ui size, int ipow );

int  __vf   VPE_powReExpo(  peVector Y, peVector X, ui size, extended Expo );
int  __vf   VPE_sqrt(  peVector Y, peVector X, ui size );
int  __vf   VPE_logtoC(   ceVector Y, peVector X, ui size );
int  __vf   VPE_log2toC(  ceVector Y, peVector X, ui size );
int  __vf   VPE_log10toC( ceVector Y, peVector X, ui size );
#define     VPE_lntoC   VPE_logtoC

int  __vf   VCE_exptoP(  peVector Y, ceVector X, ui size );

#else   /* no 80-bit IEEE number support with Visual C++:
           the following 120 lines apply only to Visual C++  */
#include <VPDmath.h>
#define VPE_cmp_eq0     VPD_cmp_eq0
#define VPE_cmp_ne0     VPD_cmp_ne0
#define VPE_cmp_eqC     VPD_cmp_eqC
#define VPE_cmp_neC     VPD_cmp_neC
#define VPE_cmp_eqV     VPD_cmp_eqV
#define VPE_cmp_neV     VPD_cmp_neV
#define VPE_cnt_eq0     VPD_cnt_eq0
#define VPE_cnt_ne0     VPD_cnt_ne0
#define VPE_cnt_eqC     VPD_cnt_eqC
#define VPE_cnt_neC     VPD_cnt_neC
#define VPE_cnt_eqV     VPD_cnt_eqV
#define VPE_cnt_neV     VPD_cnt_neV
#define VPE_cmp_eq0ind  VPD_cmp_eq0ind
#define VPE_cmp_ne0ind  VPD_cmp_ne0ind
#define VPE_cmp_eqCind  VPD_cmp_eqCind
#define VPE_cmp_neCind  VPD_cmp_neCind
#define VPE_cmp_eqVind  VPD_cmp_eqVind
#define VPE_cmp_neVind  VPD_cmp_neVind
#define VPE_cnt_eq0     VPD_cnt_eq0
#define VPE_cnt_ne0     VPD_cnt_ne0
#define VPE_cnt_eqC     VPD_cnt_eqC
#define VPE_cnt_neC     VPD_cnt_neC
#define VPE_cnt_eqV     VPD_cnt_eqV
#define VPE_cnt_neV     VPD_cnt_neV

#define VPE_replaceNAN  VPD_replaceNAN
#define VPE_mulC        VPD_mulC
#define VPE_divC        VPD_divC
#define VPE_divrC       VPD_divrC
#define VPE_mulReC      VPD_mulReC
#define VPE_divReC      VPD_divReC
#define VPE_divrReC     VPD_divrReC
#define VPE_mulV        VPD_mulV
#define VPE_divV        VPD_divV
#define VPE_divrV       VPD_divrV
#define VPE_mulReV      VPD_mulReV
#define VPE_divReV      VPD_divReV
#define VPE_divrReV     VPD_divrReV
#define VPE_subvector_equC  VPD_subvector_equC
#define VPE_subvector_mulC  VPD_subvector_mulC
#define VPE_subvector_divC  VPD_subvector_divC
#define VPE_subvector_divrC VPD_subvector_divrC
#define VPE_subvector_mulV  VPD_subvector_mulV
#define VPE_subvector_divV  VPD_subvector_divV
#define VPE_subvector_divrV VPD_subvector_divrV

/*******************  Mathematical Functions *************************/

#define VPE_neg        VPD_neg
#define VPE_conj       VPD_conj
#define VPE_abs        VPD_abs
#define VPE_inv        VPD_inv
#define VPE_square     VPD_square
#define VPE_cubic      VPD_cubic
#define VPE_quartic    VPD_quartic
#define VPE_ipow       VPD_ipow
#define VPEu_square    VPDu_square
#define VPEu_cubic     VPDu_cubic
#define VPEu_quartic   VPDu_quartic
#define VPEu_ipow      VPDu_ipow
#define VPE_powReExpo  VPD_powReExpo
#define VPE_sqrt       VPD_sqrt
#define VPE_logtoC     VPD_logtoC
#define VPE_log2toC    VPD_log2toC
#define VPE_log10toC   VPD_log10toC
#define VPE_lntoC      VPE_logtoC
#define VCE_exptoP     VCD_exptoP

#endif  /* Borland or Microsoft */

#ifdef __cplusplus
}  // end of extern "C"
#endif

#endif /* __VPEMATH_H */
