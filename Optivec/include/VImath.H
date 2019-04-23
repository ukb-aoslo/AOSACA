/*  VImath.h

  vector management functions for data type "int":
  integer arithmetics and mathematics.

  Copyright (c) 1996-200 by OptiCode - Dr. Martin Sander Software Dev.
  All Rights Reserved.
*/

#ifndef __VIMATH_H
#define __VIMATH_H

#if !defined( __VECLIB_H )
   #include <VecLib.h>
#endif

#ifdef __cplusplus
   extern "C" {
#endif

/********************  Comparisons ********************************/

void __vf   VI_cmp0(    iVector Y, iVector X, ui size );
ui   __vf   VI_cmp_eq0( iVector Y, iVector X, ui size );
ui   __vf   VI_cmp_ne0( iVector Y, iVector X, ui size );
ui   __vf   VI_cmp_le0( iVector Y, iVector X, ui size );
ui   __vf   VI_cmp_lt0( iVector Y, iVector X, ui size );
ui   __vf   VI_cmp_ge0( iVector Y, iVector X, ui size );
ui   __vf   VI_cmp_gt0( iVector Y, iVector X, ui size );

ui   __vf   VI_cmp_eq0ind( uiVector Ind, iVector X, ui size );
ui   __vf   VI_cmp_ne0ind( uiVector Ind, iVector X, ui size );
ui   __vf   VI_cmp_le0ind( uiVector Ind, iVector X, ui size );
ui   __vf   VI_cmp_lt0ind( uiVector Ind, iVector X, ui size );
ui   __vf   VI_cmp_ge0ind( uiVector Ind, iVector X, ui size );
ui   __vf   VI_cmp_gt0ind( uiVector Ind, iVector X, ui size );

ui   __vf   VI_cnt_eq0( iVector X, ui size );
ui   __vf   VI_cnt_ne0( iVector X, ui size );
ui   __vf   VI_cnt_le0( iVector X, ui size );
ui   __vf   VI_cnt_lt0( iVector X, ui size );
ui   __vf   VI_cnt_ge0( iVector X, ui size );
ui   __vf   VI_cnt_gt0( iVector X, ui size );

void __vf   VI_cmpC(    iVector Y, iVector X, ui size, int C );
ui   __vf   VI_cmp_eqC( iVector Y, iVector X, ui size, int C );
ui   __vf   VI_cmp_neC( iVector Y, iVector X, ui size, int C );
ui   __vf   VI_cmp_leC( iVector Y, iVector X, ui size, int C );
ui   __vf   VI_cmp_ltC( iVector Y, iVector X, ui size, int C );
ui   __vf   VI_cmp_geC( iVector Y, iVector X, ui size, int C );
ui   __vf   VI_cmp_gtC( iVector Y, iVector X, ui size, int C );

ui   __vf   VI_cmp_eqCind( uiVector Ind, iVector X, ui size, int C );
ui   __vf   VI_cmp_neCind( uiVector Ind, iVector X, ui size, int C );
ui   __vf   VI_cmp_leCind( uiVector Ind, iVector X, ui size, int C );
ui   __vf   VI_cmp_ltCind( uiVector Ind, iVector X, ui size, int C );
ui   __vf   VI_cmp_geCind( uiVector Ind, iVector X, ui size, int C );
ui   __vf   VI_cmp_gtCind( uiVector Ind, iVector X, ui size, int C );

ui   __vf   VI_cnt_eqC( iVector X, ui size, int C );
ui   __vf   VI_cnt_neC( iVector X, ui size, int C );
ui   __vf   VI_cnt_leC( iVector X, ui size, int C );
ui   __vf   VI_cnt_ltC( iVector X, ui size, int C );
ui   __vf   VI_cnt_geC( iVector X, ui size, int C );
ui   __vf   VI_cnt_gtC( iVector X, ui size, int C );

void __vf   VI_cmpV(    iVector Z, iVector X, iVector Y, ui size );
ui   __vf   VI_cmp_eqV( iVector Z, iVector X, iVector Y, ui size );
ui   __vf   VI_cmp_neV( iVector Z, iVector X, iVector Y, ui size );
ui   __vf   VI_cmp_leV( iVector Z, iVector X, iVector Y, ui size );
ui   __vf   VI_cmp_ltV( iVector Z, iVector X, iVector Y, ui size );
ui   __vf   VI_cmp_geV( iVector Z, iVector X, iVector Y, ui size );
ui   __vf   VI_cmp_gtV( iVector Z, iVector X, iVector Y, ui size );

ui   __vf   VI_cmp_eqVind( uiVector Ind, iVector X, iVector Y, ui size );
ui   __vf   VI_cmp_neVind( uiVector Ind, iVector X, iVector Y, ui size );
ui   __vf   VI_cmp_leVind( uiVector Ind, iVector X, iVector Y, ui size );
ui   __vf   VI_cmp_ltVind( uiVector Ind, iVector X, iVector Y, ui size );
ui   __vf   VI_cmp_geVind( uiVector Ind, iVector X, iVector Y, ui size );
ui   __vf   VI_cmp_gtVind( uiVector Ind, iVector X, iVector Y, ui size );

ui   __vf   VI_cnt_eqV( iVector X, iVector Y, ui size );
ui   __vf   VI_cnt_neV( iVector X, iVector Y, ui size );
ui   __vf   VI_cnt_leV( iVector X, iVector Y, ui size );
ui   __vf   VI_cnt_ltV( iVector X, iVector Y, ui size );
ui   __vf   VI_cnt_geV( iVector X, iVector Y, ui size );
ui   __vf   VI_cnt_gtV( iVector X, iVector Y, ui size );

ui   __vf   VI_cmp_inclrange0C( iVector Y, iVector X, ui size, int C );
ui   __vf   VI_cmp_exclrange0C( iVector Y, iVector X, ui size, int C );
ui   __vf   VI_cmp_inclrangeCC( iVector Y, iVector X, ui size, int CLo, int CHi );
ui   __vf   VI_cmp_exclrangeCC( iVector Y, iVector X, ui size, int CLo, int CHi );

ui   __vf   VI_cmp_inclrange0Cind( uiVector Ind, iVector X, ui size, int C );
ui   __vf   VI_cmp_exclrange0Cind( uiVector Ind, iVector X, ui size, int C );
ui   __vf   VI_cmp_inclrangeCCind( uiVector Ind, iVector X, ui size, int CLo, int CHi );
ui   __vf   VI_cmp_exclrangeCCind( uiVector Ind, iVector X, ui size, int CLo, int CHi );

ui   __vf   VI_cnt_inclrange0C( iVector X, ui size, int C );
ui   __vf   VI_cnt_exclrange0C( iVector X, ui size, int C );
ui   __vf   VI_cnt_inclrangeCC( iVector X, ui size, int CLo, int CHi );
ui   __vf   VI_cnt_exclrangeCC( iVector X, ui size, int CLo, int CHi );


/******************   Basic  Arithmetics   *************************/

void  __vf  VI_neg( iVector Y, iVector X, ui size );
void  __vf  VI_abs( iVector Y, iVector X, ui size );

void  __vf  VIo_addC(  iVector Y, iVector X, ui size, int C );
void  __vf  VIo_subC(  iVector Y, iVector X, ui size, int C );
void  __vf  VIo_subrC( iVector Y, iVector X, ui size, int C );
void  __vf  VIo_mulC(  iVector Y, iVector X, ui size, int C );
#ifdef V_trapIntError
    #define VI_addC     VIo_addC
    #define VI_subC     VIo_subC
    #define VI_subrC    VIo_subrC
    #define VI_mulC     VIo_mulC
#else
    void  __vf  VI_addC(  iVector Y, iVector X, ui size, int C );
    void  __vf  VI_subC(  iVector Y, iVector X, ui size, int C );
    void  __vf  VI_subrC( iVector Y, iVector X, ui size, int C );
    void  __vf  VI_mulC(  iVector Y, iVector X, ui size, int C );
#endif
void  __vf  VI_divC(  iVector Y, iVector X, ui size, int C );
void  __vf  VI_divrC( iVector Y, iVector X, ui size, int C );
void  __vf  VI_modC(  iVector Y, iVector X, ui size, int C );
void  __vf  VI_maxC(  iVector Y, iVector X, ui size, int C );
void  __vf  VI_minC(  iVector Y, iVector X, ui size, int C );
void  __vf  VI_limit( iVector Y, iVector X, ui size, int Min, int Max );

void  __vf  VIo_addV(  iVector Z, iVector X, iVector Y, ui size );
void  __vf  VIo_subV(  iVector Z, iVector X, iVector Y, ui size );
void  __vf  VIo_subrV( iVector Z, iVector X, iVector Y, ui size );
void  __vf  VIo_mulV(  iVector Z, iVector X, iVector Y, ui size );
#ifdef V_trapIntError
    #define VI_addV    VIo_addV
    #define VI_subV    VIo_subV
    #define VI_subrV   VIo_subrV
    #define VI_mulV    VIo_mulV
#else
    void  __vf  VI_addV(  iVector Z, iVector X, iVector Y, ui size );
    void  __vf  VI_subV(  iVector Z, iVector X, iVector Y, ui size );
    void  __vf  VI_subrV( iVector Z, iVector X, iVector Y, ui size );
    void  __vf  VI_mulV(  iVector Z, iVector X, iVector Y, ui size );
#endif
void  __vf  VI_divV(  iVector Z, iVector X, iVector Y, ui size );
void  __vf  VI_divrV( iVector Z, iVector X, iVector Y, ui size );
void  __vf  VI_modV(  iVector Z, iVector X, iVector Y, ui size );
void  __vf  VI_maxV(  iVector Z, iVector X, iVector Y, ui size );
void  __vf  VI_minV(  iVector Z, iVector X, iVector Y, ui size );

/******************** Accumulation (Y += X) ******************************/

void __vf VI_accV(   iVector Y, iVector   X, ui size );
void __vf VI_accVBI( iVector Y, biVector  X, ui size );
void __vf VI_accVSI( iVector Y, siVector  X, ui size );

/*****************   Bit-wise operations  *********************/

void    __vf  VI_shl( iVector Y, iVector X, ui size, unsigned C );
void    __vf  VI_shr( iVector Y, iVector X, ui size, unsigned C );

void    __vf  VI_and( iVector Y, iVector X, ui size, int C );
void    __vf  VI_or(  iVector Y, iVector X, ui size, int C );
void    __vf  VI_xor( iVector Y, iVector X, ui size, int C );
void    __vf  VI_not( iVector Y, iVector X, ui size );

#ifdef __cplusplus
} // end of extern "C"
#endif

#endif   /*  __VIMATH_H    */
