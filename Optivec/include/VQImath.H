/*  VQImath.h

  vector management functions for data type "quad":
  integer arithmetics and mathematics.

  Copyright (c) 1996-2017 by OptiCode - Dr. Martin Sander Software Dev.
  All Rights Reserved.
*/

#ifndef __VQIMATH_H
#define __VQIMATH_H

#if !defined( __VECLIB_H )
   #include <VecLib.h>
#endif


#ifdef __cplusplus
   extern "C" {
#endif

/********************  Comparisons ********************************/

void __vf   VQI_cmp0(    qiVector Y, qiVector X, ui size );
ui   __vf   VQI_cmp_eq0( qiVector Y, qiVector X, ui size );
ui   __vf   VQI_cmp_ne0( qiVector Y, qiVector X, ui size );
ui   __vf   VQI_cmp_le0( qiVector Y, qiVector X, ui size );
ui   __vf   VQI_cmp_lt0( qiVector Y, qiVector X, ui size );
ui   __vf   VQI_cmp_ge0( qiVector Y, qiVector X, ui size );
ui   __vf   VQI_cmp_gt0( qiVector Y, qiVector X, ui size );

ui   __vf   VQI_cmp_eq0ind( uiVector Ind, qiVector X, ui size );
ui   __vf   VQI_cmp_ne0ind( uiVector Ind, qiVector X, ui size );
ui   __vf   VQI_cmp_le0ind( uiVector Ind, qiVector X, ui size );
ui   __vf   VQI_cmp_lt0ind( uiVector Ind, qiVector X, ui size );
ui   __vf   VQI_cmp_ge0ind( uiVector Ind, qiVector X, ui size );
ui   __vf   VQI_cmp_gt0ind( uiVector Ind, qiVector X, ui size );

ui   __vf   VQI_cnt_eq0( qiVector X, ui size );
ui   __vf   VQI_cnt_ne0( qiVector X, ui size );
ui   __vf   VQI_cnt_le0( qiVector X, ui size );
ui   __vf   VQI_cnt_lt0( qiVector X, ui size );
ui   __vf   VQI_cnt_ge0( qiVector X, ui size );
ui   __vf   VQI_cnt_gt0( qiVector X, ui size );

void __vf   VQI_cmpC(    qiVector Y, qiVector X, ui size, quad C );
ui   __vf   VQI_cmp_eqC( qiVector Y, qiVector X, ui size, quad C );
ui   __vf   VQI_cmp_neC( qiVector Y, qiVector X, ui size, quad C );
ui   __vf   VQI_cmp_leC( qiVector Y, qiVector X, ui size, quad C );
ui   __vf   VQI_cmp_ltC( qiVector Y, qiVector X, ui size, quad C );
ui   __vf   VQI_cmp_geC( qiVector Y, qiVector X, ui size, quad C );
ui   __vf   VQI_cmp_gtC( qiVector Y, qiVector X, ui size, quad C );

ui   __vf   VQI_cmp_eqCind( uiVector Ind, qiVector X, ui size, quad C );
ui   __vf   VQI_cmp_neCind( uiVector Ind, qiVector X, ui size, quad C );
ui   __vf   VQI_cmp_leCind( uiVector Ind, qiVector X, ui size, quad C );
ui   __vf   VQI_cmp_ltCind( uiVector Ind, qiVector X, ui size, quad C );
ui   __vf   VQI_cmp_geCind( uiVector Ind, qiVector X, ui size, quad C );
ui   __vf   VQI_cmp_gtCind( uiVector Ind, qiVector X, ui size, quad C );

ui   __vf   VQI_cnt_eqC( qiVector X, ui size, quad C );
ui   __vf   VQI_cnt_neC( qiVector X, ui size, quad C );
ui   __vf   VQI_cnt_leC( qiVector X, ui size, quad C );
ui   __vf   VQI_cnt_ltC( qiVector X, ui size, quad C );
ui   __vf   VQI_cnt_geC( qiVector X, ui size, quad C );
ui   __vf   VQI_cnt_gtC( qiVector X, ui size, quad C );

void __vf   VQI_cmpV(    qiVector Z, qiVector X, qiVector Y, ui size );
ui   __vf   VQI_cmp_eqV( qiVector Z, qiVector X, qiVector Y, ui size );
ui   __vf   VQI_cmp_neV( qiVector Z, qiVector X, qiVector Y, ui size );
ui   __vf   VQI_cmp_leV( qiVector Z, qiVector X, qiVector Y, ui size );
ui   __vf   VQI_cmp_ltV( qiVector Z, qiVector X, qiVector Y, ui size );
ui   __vf   VQI_cmp_geV( qiVector Z, qiVector X, qiVector Y, ui size );
ui   __vf   VQI_cmp_gtV( qiVector Z, qiVector X, qiVector Y, ui size );

ui   __vf   VQI_cmp_eqVind( uiVector Ind, qiVector X, qiVector Y, ui size );
ui   __vf   VQI_cmp_neVind( uiVector Ind, qiVector X, qiVector Y, ui size );
ui   __vf   VQI_cmp_leVind( uiVector Ind, qiVector X, qiVector Y, ui size );
ui   __vf   VQI_cmp_ltVind( uiVector Ind, qiVector X, qiVector Y, ui size );
ui   __vf   VQI_cmp_geVind( uiVector Ind, qiVector X, qiVector Y, ui size );
ui   __vf   VQI_cmp_gtVind( uiVector Ind, qiVector X, qiVector Y, ui size );

ui   __vf   VQI_cnt_eqV( qiVector X, qiVector Y, ui size );
ui   __vf   VQI_cnt_neV( qiVector X, qiVector Y, ui size );
ui   __vf   VQI_cnt_leV( qiVector X, qiVector Y, ui size );
ui   __vf   VQI_cnt_ltV( qiVector X, qiVector Y, ui size );
ui   __vf   VQI_cnt_geV( qiVector X, qiVector Y, ui size );
ui   __vf   VQI_cnt_gtV( qiVector X, qiVector Y, ui size );

ui   __vf   VQI_cmp_inclrange0C( qiVector Y, qiVector X, ui size, quad C );
ui   __vf   VQI_cmp_exclrange0C( qiVector Y, qiVector X, ui size, quad C );
ui   __vf   VQI_cmp_inclrangeCC( qiVector Y, qiVector X, ui size, quad CLo, quad CHi );
ui   __vf   VQI_cmp_exclrangeCC( qiVector Y, qiVector X, ui size, quad CLo, quad CHi );

ui   __vf   VQI_cmp_inclrange0Cind( uiVector Ind, qiVector X, ui size, quad C );
ui   __vf   VQI_cmp_exclrange0Cind( uiVector Ind, qiVector X, ui size, quad C );
ui   __vf   VQI_cmp_inclrangeCCind( uiVector Ind, qiVector X, ui size, quad CLo, quad CHi );
ui   __vf   VQI_cmp_exclrangeCCind( uiVector Ind, qiVector X, ui size, quad CLo, quad CHi );

ui   __vf   VQI_cnt_inclrange0C( qiVector X, ui size, quad C );
ui   __vf   VQI_cnt_exclrange0C( qiVector X, ui size, quad C );
ui   __vf   VQI_cnt_inclrangeCC( qiVector X, ui size, quad CLo, quad CHi );
ui   __vf   VQI_cnt_exclrangeCC( qiVector X, ui size, quad CLo, quad CHi );


/******************   Basic  Arithmetics   *************************/

void    __vf  VQI_neg( qiVector Y, qiVector X, ui size );
void    __vf  VQI_abs( qiVector Y, qiVector X, ui size );

void    __vf  VQI_addC(  qiVector Y, qiVector X, ui size, quad C );
void    __vf  VQI_subC(  qiVector Y, qiVector X, ui size, quad C );
void    __vf  VQI_subrC( qiVector Y, qiVector X, ui size, quad C );
void    __vf  VQI_mulC(  qiVector Y, qiVector X, ui size, quad C );
void    __vf  VQI_divC(  qiVector Y, qiVector X, ui size, quad C );
void    __vf  VQI_divrC( qiVector Y, qiVector X, ui size, quad C );
void    __vf  VQI_modC(  qiVector Y, qiVector X, ui size, quad C );
void    __vf  VQI_maxC(  qiVector Y, qiVector X, ui size, quad C );
void    __vf  VQI_minC(  qiVector Y, qiVector X, ui size, quad C );
void    __vf  VQI_limit( qiVector Y, qiVector X, ui size, quad Min, quad Max );

void    __vf  VQI_addV(  qiVector Z, qiVector X, qiVector Y, ui size );
void    __vf  VQI_subV(  qiVector Z, qiVector X, qiVector Y, ui size );
void    __vf  VQI_subrV( qiVector Z, qiVector X, qiVector Y, ui size );
void    __vf  VQI_mulV(  qiVector Z, qiVector X, qiVector Y, ui size );
void    __vf  VQI_divV(  qiVector Z, qiVector X, qiVector Y, ui size );
void    __vf  VQI_divrV( qiVector Z, qiVector X, qiVector Y, ui size );
void    __vf  VQI_modV(  qiVector Z, qiVector X, qiVector Y, ui size );
void    __vf  VQI_maxV(  qiVector Z, qiVector X, qiVector Y, ui size );
void    __vf  VQI_minV(  qiVector Z, qiVector X, qiVector Y, ui size );

/******************** Accumulation (Y += X) ******************************/

void __vf VQI_accV(   qiVector Y, qiVector  X, ui size );
void __vf VQI_accVBI( qiVector Y, biVector  X, ui size );
void __vf VQI_accVSI( qiVector Y, siVector  X, ui size );
void __vf VQI_accVI(  qiVector Y, iVector   X, ui size );
void __vf VQI_accVLI( qiVector Y, liVector  X, ui size );
void __vf VQI_accVUB( qiVector Y, ubVector  X, ui size );
void __vf VQI_accVUS( qiVector Y, usVector  X, ui size );
void __vf VQI_accVU(  qiVector Y, uVector   X, ui size );
void __vf VQI_accVUL( qiVector Y, ulVector  X, ui size );
#if defined (V_HUGE)
    #define VQI_accVUI  VQI_accVUL
#else
    #define VQI_accVUI  VQI_accVU
#endif

/*****************   Bit-wise operations  *********************/

void    __vf  VQI_shl( qiVector Y, qiVector X, ui size, unsigned C );
void    __vf  VQI_shr( qiVector Y, qiVector X, ui size, unsigned C );

void    __vf  VQI_and( qiVector Y, qiVector X, ui size, quad C );
void    __vf  VQI_or(  qiVector Y, qiVector X, ui size, quad C );
void    __vf  VQI_xor( qiVector Y, qiVector X, ui size, quad C );
void    __vf  VQI_not( qiVector Y, qiVector X, ui size );

/************  Optical Density Y = log10( X0 / X ) *********************/

int  __vf VQI_ODtoF( fVector OD, qiVector X, qiVector X0, ui size );
int  __vf VQI_ODtoD( dVector OD, qiVector X, qiVector X0, ui size );
int  __vf VQI_ODtoFwDark( fVector OD, qiVector X, qiVector XDark,
                          qiVector X0, qiVector X0Dark, ui size );
int  __vf VQI_ODtoDwDark( dVector OD, qiVector X, qiVector XDark,
                          qiVector X0, qiVector X0Dark, ui size );
void __vf VQI_setODThresh( quad minX, quad minX0 );
#if (defined __BORLANDC__) && !(defined _WIN64)   /* 80-bit reals supported ? */
int  __vf VQI_ODtoE( eVector OD, qiVector X, qiVector X0, ui size );
int  __vf VQI_ODtoEwDark( eVector OD, qiVector X, qiVector XDark,
                          qiVector X0, qiVector X0Dark, ui size );
#else
    #define VQI_ODtoE      VQI_ODtoD
    #define VQI_ODtoEwDark VQI_ODtoDwDark
#endif

#ifdef __cplusplus
}  // end of extern "C"
#endif

#endif   /*  __VQIMATH_H    */
