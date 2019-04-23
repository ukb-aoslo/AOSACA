/*  VPDmath.h

  vector management functions:
  arithmetic and math functions performed on each individual element
  of an array or vector of data type "dPolar"  (polar complex double)

  Copyright (c) 1996-2017 by OptiCode - Dr. Martin Sander Software Dev.
  All Rights Reserved.
*/

#ifndef __VPDMATH_H
#define __VPDMATH_H

#ifndef __VPDSTD_H
#include <VPDstd.h>
#endif


#ifdef __cplusplus
extern "C" {
#endif

/********************* Comparisons ****************************/

ui   __vf   VPD_cmp_eq0( pdVector Y, pdVector X, ui size );
ui   __vf   VPD_cmp_ne0( pdVector Y, pdVector X, ui size );
ui   __vf   VPD_cmp_eqC( pdVector Y, pdVector X, ui size, dPolar C );
ui   __vf   VPD_cmp_neC( pdVector Y, pdVector X, ui size, dPolar C );
ui   __vf   VPD_cmp_eqV( pdVector Z, pdVector X, pdVector Y, ui size );
ui   __vf   VPD_cmp_neV( pdVector Z, pdVector X, pdVector Y, ui size );
ui   __vf   VPD_cmp_eq0ind( uiVector Ind, pdVector X, ui size );
ui   __vf   VPD_cmp_ne0ind( uiVector Ind, pdVector X, ui size );
ui   __vf   VPD_cmp_eqCind( uiVector Ind, pdVector X, ui size, dPolar C );
ui   __vf   VPD_cmp_neCind( uiVector Ind, pdVector X, ui size, dPolar C );
ui   __vf   VPD_cmp_eqVind( uiVector Ind, pdVector X, pdVector Y, ui size );
ui   __vf   VPD_cmp_neVind( uiVector Ind, pdVector X, pdVector Y, ui size );
ui   __vf   VPD_cnt_eq0( pdVector X, ui size );
ui   __vf   VPD_cnt_ne0( pdVector X, ui size );
ui   __vf   VPD_cnt_eqC( pdVector X, ui size, dPolar C );
ui   __vf   VPD_cnt_neC( pdVector X, ui size, dPolar C );
ui   __vf   VPD_cnt_eqV( pdVector X, pdVector Y, ui size );
ui   __vf   VPD_cnt_neV( pdVector X, pdVector Y, ui size );


/********************  Standard Arithmetics   ***************************/

void  __vf   VPD_replaceNAN( pdVector Y, pdVector X, ui siz, dPolar C );

void  __vf   VPD_mulC(   pdVector Y, pdVector X, ui size, dPolar C );
void  __vf   VPD_divC(   pdVector Y, pdVector X, ui size, dPolar C );
void  __vf   VPD_divrC(  pdVector Y, pdVector X, ui size, dPolar C );

void  __vf   VPD_mulReC(  pdVector Y, pdVector X, ui size, double CRe );
void  __vf   VPD_divReC(  pdVector Y, pdVector X, ui size, double CRe );
void  __vf   VPD_divrReC( pdVector Y, pdVector X, ui size, double CRe );

void  __vf   VPD_mulV(  pdVector Z, pdVector X, pdVector Y, ui size );
void  __vf   VPD_divV(  pdVector Z, pdVector X, pdVector Y, ui size );
void  __vf   VPD_divrV( pdVector Z, pdVector X, pdVector Y, ui size );

void  __vf   VPD_mulReV(  pdVector Z, pdVector X, dVector Y, ui size );
void  __vf   VPD_divReV(  pdVector Z, pdVector X, dVector Y, ui size );
void  __vf   VPD_divrReV( pdVector Z, pdVector X, dVector Y, ui size );


/*************** Functions of a sub-set of elements  ********************/

void  __vf  VPD_subvector_equC(  pdVector Y, ui subsiz, ui samp,
                                 dPolar C );
void  __vf  VPD_subvector_equV(  pdVector Y, ui subsiz, ui samp,
                                 pdVector X );

void  __vf  VPD_subvector_mulC(  pdVector Y, ui subsiz, ui samp,
                                 dPolar C );
void  __vf  VPD_subvector_divC(  pdVector Y, ui subsiz, ui samp,
                                 dPolar C );
void  __vf  VPD_subvector_divrC( pdVector Y, ui subsiz, ui samp,
                                 dPolar C );

void  __vf  VPD_subvector_mulV(  pdVector Y, ui subsiz, ui samp,
                                 pdVector X );
void  __vf  VPD_subvector_divV(  pdVector Y, ui subsiz, ui samp,
                                 pdVector X );
void  __vf  VPD_subvector_divrV( pdVector Y, ui subsiz, ui samp,
                                 pdVector X );


/*********************  Mathematical Functions *************************/

int   __vf   VPD_neg(  pdVector Y, pdVector X, ui size );
int   __vf   VPD_conj( pdVector Y, pdVector X, ui size );
int   __vf   VPD_abs(   dVector Y, pdVector X, ui size );
int   __vf   VPD_inv(  pdVector Y, pdVector X, ui size );

int  __vf   VPD_square(  pdVector Y, pdVector X, ui size );
int  __vf   VPD_cubic(   pdVector Y, pdVector X, ui size );
int  __vf   VPD_quartic( pdVector Y, pdVector X, ui size );
int  __vf   VPD_ipow(    pdVector Y, pdVector X, ui size, int ipow );

    /* extra fast integer powers: "unprotected", without error handling: */
int  __vf   VPDu_square(   pdVector Y, pdVector X, ui size );
int  __vf   VPDu_cubic(    pdVector Y, pdVector X, ui size );
int  __vf   VPDu_quartic(  pdVector Y, pdVector X, ui size );
int  __vf   VPDu_ipow(     pdVector Y, pdVector X, ui size, int ipow );

int  __vf   VPD_powReExpo(  pdVector Y, pdVector X, ui size, double Expo );
int  __vf   VPD_sqrt(  pdVector Y, pdVector X, ui size );
int  __vf   VPD_logtoC(   cdVector Y, pdVector X, ui size );
int  __vf   VPD_log2toC(  cdVector Y, pdVector X, ui size );
int  __vf   VPD_log10toC( cdVector Y, pdVector X, ui size );
#define     VPD_lntoC   VPD_logtoC

int  __vf   VCD_exptoP(  pdVector Y, cdVector X, ui size );

#ifdef __cplusplus
}  // end of extern "C"
#endif


#endif /* __VPDMATH_H */
