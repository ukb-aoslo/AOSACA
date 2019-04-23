/*  VUQmath.h

  vector management functions for data type "uquad":
  integer arithmetics and mathematics.

  Copyright (c) 1996-2017 by OptiCode - Dr. Martin Sander Software Dev.
  All Rights Reserved.
*/

#if defined _WIN64

#ifndef __VUQMATH_H
#define __VUQMATH_H

#if !defined( __VECLIB_H )
   #include <VecLib.h>
#endif

#ifdef __cplusplus
   extern "C" {
#endif

/********************  Comparisons ********************************/

ui   __vf   VUQ_cmp_eq0( uqVector Y, uqVector X, ui size );
ui   __vf   VUQ_cmp_ne0( uqVector Y, uqVector X, ui size );
ui   __vf   VUQ_cmp_gt0( uqVector Y, uqVector X, ui size );

ui   __vf   VUQ_cmp_eq0ind( uiVector Ind, uqVector X, ui size );
ui   __vf   VUQ_cmp_ne0ind( uiVector Ind, uqVector X, ui size );
ui   __vf   VUQ_cmp_gt0ind( uiVector Ind, uqVector X, ui size );

ui   __vf   VUQ_cnt_eq0( uqVector X, ui size );
ui   __vf   VUQ_cnt_ne0( uqVector X, ui size );
ui   __vf   VUQ_cnt_gt0( uqVector X, ui size );

void __vf   VUQ_cmpC(    qiVector Y, uqVector X, ui size, uquad C );
ui   __vf   VUQ_cmp_eqC( uqVector Y, uqVector X, ui size, uquad C );
ui   __vf   VUQ_cmp_neC( uqVector Y, uqVector X, ui size, uquad C );
ui   __vf   VUQ_cmp_leC( uqVector Y, uqVector X, ui size, uquad C );
ui   __vf   VUQ_cmp_ltC( uqVector Y, uqVector X, ui size, uquad C );
ui   __vf   VUQ_cmp_geC( uqVector Y, uqVector X, ui size, uquad C );
ui   __vf   VUQ_cmp_gtC( uqVector Y, uqVector X, ui size, uquad C );

ui   __vf   VUQ_cmp_eqCind( uiVector Ind, uqVector X, ui size, uquad C );
ui   __vf   VUQ_cmp_neCind( uiVector Ind, uqVector X, ui size, uquad C );
ui   __vf   VUQ_cmp_leCind( uiVector Ind, uqVector X, ui size, uquad C );
ui   __vf   VUQ_cmp_ltCind( uiVector Ind, uqVector X, ui size, uquad C );
ui   __vf   VUQ_cmp_geCind( uiVector Ind, uqVector X, ui size, uquad C );
ui   __vf   VUQ_cmp_gtCind( uiVector Ind, uqVector X, ui size, uquad C );

ui   __vf   VUQ_cnt_eqC( uqVector X, ui size, uquad C );
ui   __vf   VUQ_cnt_neC( uqVector X, ui size, uquad C );
ui   __vf   VUQ_cnt_leC( uqVector X, ui size, uquad C );
ui   __vf   VUQ_cnt_ltC( uqVector X, ui size, uquad C );
ui   __vf   VUQ_cnt_geC( uqVector X, ui size, uquad C );
ui   __vf   VUQ_cnt_gtC( uqVector X, ui size, uquad C );

void __vf   VUQ_cmpV(    qiVector Z, uqVector X, uqVector Y, ui size );
ui   __vf   VUQ_cmp_eqV( uqVector Z, uqVector X, uqVector Y, ui size );
ui   __vf   VUQ_cmp_neV( uqVector Z, uqVector X, uqVector Y, ui size );
ui   __vf   VUQ_cmp_leV( uqVector Z, uqVector X, uqVector Y, ui size );
ui   __vf   VUQ_cmp_ltV( uqVector Z, uqVector X, uqVector Y, ui size );
ui   __vf   VUQ_cmp_geV( uqVector Z, uqVector X, uqVector Y, ui size );
ui   __vf   VUQ_cmp_gtV( uqVector Z, uqVector X, uqVector Y, ui size );

ui   __vf   VUQ_cmp_eqVind( uiVector Ind, uqVector X, uqVector Y, ui size );
ui   __vf   VUQ_cmp_neVind( uiVector Ind, uqVector X, uqVector Y, ui size );
ui   __vf   VUQ_cmp_leVind( uiVector Ind, uqVector X, uqVector Y, ui size );
ui   __vf   VUQ_cmp_ltVind( uiVector Ind, uqVector X, uqVector Y, ui size );
ui   __vf   VUQ_cmp_geVind( uiVector Ind, uqVector X, uqVector Y, ui size );
ui   __vf   VUQ_cmp_gtVind( uiVector Ind, uqVector X, uqVector Y, ui size );

ui   __vf   VUQ_cnt_eqV( uqVector X, uqVector Y, ui size );
ui   __vf   VUQ_cnt_neV( uqVector X, uqVector Y, ui size );
ui   __vf   VUQ_cnt_leV( uqVector X, uqVector Y, ui size );
ui   __vf   VUQ_cnt_ltV( uqVector X, uqVector Y, ui size );
ui   __vf   VUQ_cnt_geV( uqVector X, uqVector Y, ui size );
ui   __vf   VUQ_cnt_gtV( uqVector X, uqVector Y, ui size );

ui   __vf   VUQ_cmp_exclrange0C( uqVector Y, uqVector X, ui size, uquad C );
ui   __vf   VUQ_cmp_inclrangeCC( uqVector Y, uqVector X, ui size, uquad CLo, uquad CHi );
ui   __vf   VUQ_cmp_exclrangeCC( uqVector Y, uqVector X, ui size, uquad CLo, uquad CHi );

ui   __vf   VUQ_cmp_exclrange0Cind( uiVector Ind, uqVector X, ui size, uquad C );
ui   __vf   VUQ_cmp_inclrangeCCind( uiVector Ind, uqVector X, ui size, uquad CLo, uquad CHi );
ui   __vf   VUQ_cmp_exclrangeCCind( uiVector Ind, uqVector X, ui size, uquad CLo, uquad CHi );

ui   __vf   VUQ_cnt_exclrange0C( uqVector X, ui size, uquad C );
ui   __vf   VUQ_cnt_inclrangeCC( uqVector X, ui size, uquad CLo, uquad CHi );
ui   __vf   VUQ_cnt_exclrangeCC( uqVector X, ui size, uquad CLo, uquad CHi );

/******************   Basic  Arithmetics   *************************/

void  __vf  VUQ_addC(  uqVector Y, uqVector X, ui size, uquad C );
void  __vf  VUQ_subC(  uqVector Y, uqVector X, ui size, uquad C );
void  __vf  VUQ_subrC( uqVector Y, uqVector X, ui size, uquad C );
void  __vf  VUQ_mulC(  uqVector Y, uqVector X, ui size, uquad C );

void  __vf  VUQ_divC(  uqVector Y, uqVector X, ui size, uquad C );
void  __vf  VUQ_divrC( uqVector Y, uqVector X, ui size, uquad C );
void  __vf  VUQ_modC(  uqVector Y, uqVector X, ui size, uquad C );
void  __vf  VUQ_maxC(  uqVector Y, uqVector X, ui size, uquad C );
void  __vf  VUQ_minC(  uqVector Y, uqVector X, ui size, uquad C );
void  __vf  VUQ_limit( uqVector Y, uqVector X, ui size, uquad Min, uquad Max );

void __vf  VUQ_addV(  uqVector Z, uqVector X, uqVector Y, ui size );
void __vf  VUQ_subV(  uqVector Z, uqVector X, uqVector Y, ui size );
void __vf  VUQ_subrV( uqVector Z, uqVector X, uqVector Y, ui size );
void __vf  VUQ_mulV(  uqVector Z, uqVector X, uqVector Y, ui size );

void    __vf  VUQ_divV(  uqVector Z, uqVector X, uqVector Y, ui size );
void    __vf  VUQ_divrV( uqVector Z, uqVector X, uqVector Y, ui size );
void    __vf  VUQ_modV(  uqVector Z, uqVector X, uqVector Y, ui size );
void    __vf  VUQ_maxV(  uqVector Z, uqVector X, uqVector Y, ui size );
void    __vf  VUQ_minV(  uqVector Z, uqVector X, uqVector Y, ui size );

/******************** Accumulation (Y += X) ******************************/

void __vf VUQ_accV(   uqVector Y, uqVector  X, ui size );
void __vf VUQ_accVUB( uqVector Y, ubVector  X, ui size );
void __vf VUQ_accVUS( uqVector Y, usVector  X, ui size );
void __vf VUQ_accVU(  uqVector Y, uVector   X, ui size );
void __vf VUQ_accVUL( uqVector Y, ulVector  X, ui size );

/*****************   Bit-wise operations  *********************/

void    __vf  VUQ_shl( uqVector Y, uqVector X, ui size, unsigned C );
void    __vf  VUQ_shr( uqVector Y, uqVector X, ui size, unsigned C );

void    __vf  VUQ_and( uqVector Y, uqVector X, ui size, uquad C );
void    __vf  VUQ_or(  uqVector Y, uqVector X, ui size, uquad C );
void    __vf  VUQ_xor( uqVector Y, uqVector X, ui size, uquad C );
void    __vf  VUQ_not( uqVector Y, uqVector X, ui size );

/************  Optical Density Y = log10( X0 / X ) *********************/

int  __vf VUQ_ODtoF( fVector OD, uqVector X, uqVector X0, ui size );
int  __vf VUQ_ODtoD( dVector OD, uqVector X, uqVector X0, ui size );
int  __vf VUQ_ODtoFwDark( fVector OD, uqVector X, uqVector XDark,
                          uqVector X0, uqVector X0Dark, ui size );
int  __vf VUQ_ODtoDwDark( dVector OD, uqVector X, uqVector XDark,
                          uqVector X0, uqVector X0Dark, ui size );
void __vf VUQ_setODThresh( uquad minX, uquad minX0 );
#if (defined __BORLANDC__) && !(defined _WIN64)  /* 80-bit reals supported ? */
int  __vf VUQ_ODtoE( eVector OD, uqVector X, uqVector X0, ui size );
int  __vf VUQ_ODtoEwDark( eVector OD, uqVector X, uqVector XDark,
                          uqVector X0, uqVector X0Dark, ui size );
#else
    #define VUQ_ODtoE      VUQ_ODtoD
    #define VUQ_ODtoEwDark VUQ_ODtoDwDark
#endif

#ifdef __cplusplus
}  // end of extern "C"
#endif

#endif   /*  __VUQMATH_H    */
#endif   /*  _WIN64  */