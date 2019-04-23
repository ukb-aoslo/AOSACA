/*  VBImath.h

  vector management functions for byte-size integers:
  integer arithmetics and mathematics.

  Copyright (c) 1996-2017 by OptiCode - Dr. Martin Sander Software Dev.
  All Rights Reserved.
*/

#ifndef __VBIMATH_H
#define __VBIMATH_H

#if !defined( __VECLIB_H )
   #include <VecLib.h>
#endif

#ifdef __cplusplus
   extern "C" {
#endif

/********************  Comparisons ********************************/

void __vf   VBI_cmp0(    biVector Y, biVector X, ui size );
ui   __vf   VBI_cmp_eq0( biVector Y, biVector X, ui size );
ui   __vf   VBI_cmp_ne0( biVector Y, biVector X, ui size );
ui   __vf   VBI_cmp_le0( biVector Y, biVector X, ui size );
ui   __vf   VBI_cmp_lt0( biVector Y, biVector X, ui size );
ui   __vf   VBI_cmp_ge0( biVector Y, biVector X, ui size );
ui   __vf   VBI_cmp_gt0( biVector Y, biVector X, ui size );

ui   __vf   VBI_cmp_eq0ind( uiVector Ind, biVector X, ui size );
ui   __vf   VBI_cmp_ne0ind( uiVector Ind, biVector X, ui size );
ui   __vf   VBI_cmp_le0ind( uiVector Ind, biVector X, ui size );
ui   __vf   VBI_cmp_lt0ind( uiVector Ind, biVector X, ui size );
ui   __vf   VBI_cmp_ge0ind( uiVector Ind, biVector X, ui size );
ui   __vf   VBI_cmp_gt0ind( uiVector Ind, biVector X, ui size );

ui   __vf   VBI_cnt_eq0( biVector X, ui size );
ui   __vf   VBI_cnt_ne0( biVector X, ui size );
ui   __vf   VBI_cnt_le0( biVector X, ui size );
ui   __vf   VBI_cnt_lt0( biVector X, ui size );
ui   __vf   VBI_cnt_ge0( biVector X, ui size );
ui   __vf   VBI_cnt_gt0( biVector X, ui size );

void __vf   VBI_cmpC(    biVector Y, biVector X, ui size, char C );
ui   __vf   VBI_cmp_eqC( biVector Y, biVector X, ui size, char C );
ui   __vf   VBI_cmp_neC( biVector Y, biVector X, ui size, char C );
ui   __vf   VBI_cmp_leC( biVector Y, biVector X, ui size, char C );
ui   __vf   VBI_cmp_ltC( biVector Y, biVector X, ui size, char C );
ui   __vf   VBI_cmp_geC( biVector Y, biVector X, ui size, char C );
ui   __vf   VBI_cmp_gtC( biVector Y, biVector X, ui size, char C );

ui   __vf   VBI_cmp_eqCind( uiVector Ind, biVector X, ui size, char C );
ui   __vf   VBI_cmp_neCind( uiVector Ind, biVector X, ui size, char C );
ui   __vf   VBI_cmp_leCind( uiVector Ind, biVector X, ui size, char C );
ui   __vf   VBI_cmp_ltCind( uiVector Ind, biVector X, ui size, char C );
ui   __vf   VBI_cmp_geCind( uiVector Ind, biVector X, ui size, char C );
ui   __vf   VBI_cmp_gtCind( uiVector Ind, biVector X, ui size, char C );

ui   __vf   VBI_cnt_eqC( biVector X, ui size, char C );
ui   __vf   VBI_cnt_neC( biVector X, ui size, char C );
ui   __vf   VBI_cnt_leC( biVector X, ui size, char C );
ui   __vf   VBI_cnt_ltC( biVector X, ui size, char C );
ui   __vf   VBI_cnt_geC( biVector X, ui size, char C );
ui   __vf   VBI_cnt_gtC( biVector X, ui size, char C );

void __vf   VBI_cmpV(    biVector Z, biVector X, biVector Y, ui size );
ui   __vf   VBI_cmp_eqV( biVector Z, biVector X, biVector Y, ui size );
ui   __vf   VBI_cmp_neV( biVector Z, biVector X, biVector Y, ui size );
ui   __vf   VBI_cmp_leV( biVector Z, biVector X, biVector Y, ui size );
ui   __vf   VBI_cmp_ltV( biVector Z, biVector X, biVector Y, ui size );
ui   __vf   VBI_cmp_geV( biVector Z, biVector X, biVector Y, ui size );
ui   __vf   VBI_cmp_gtV( biVector Z, biVector X, biVector Y, ui size );

ui   __vf   VBI_cmp_eqVind( uiVector Ind, biVector X, biVector Y, ui size );
ui   __vf   VBI_cmp_neVind( uiVector Ind, biVector X, biVector Y, ui size );
ui   __vf   VBI_cmp_leVind( uiVector Ind, biVector X, biVector Y, ui size );
ui   __vf   VBI_cmp_ltVind( uiVector Ind, biVector X, biVector Y, ui size );
ui   __vf   VBI_cmp_geVind( uiVector Ind, biVector X, biVector Y, ui size );
ui   __vf   VBI_cmp_gtVind( uiVector Ind, biVector X, biVector Y, ui size );

ui   __vf   VBI_cnt_eqV( biVector X, biVector Y, ui size );
ui   __vf   VBI_cnt_neV( biVector X, biVector Y, ui size );
ui   __vf   VBI_cnt_leV( biVector X, biVector Y, ui size );
ui   __vf   VBI_cnt_ltV( biVector X, biVector Y, ui size );
ui   __vf   VBI_cnt_geV( biVector X, biVector Y, ui size );
ui   __vf   VBI_cnt_gtV( biVector X, biVector Y, ui size );

ui   __vf   VBI_cmp_inclrange0C( biVector Y, biVector X, ui size, char C );
ui   __vf   VBI_cmp_exclrange0C( biVector Y, biVector X, ui size, char C );
ui   __vf   VBI_cmp_inclrangeCC( biVector Y, biVector X, ui size, char CLo, char CHi );
ui   __vf   VBI_cmp_exclrangeCC( biVector Y, biVector X, ui size, char CLo, char CHi );

ui   __vf   VBI_cmp_inclrange0Cind( uiVector Ind, biVector X, ui size, char C );
ui   __vf   VBI_cmp_exclrange0Cind( uiVector Ind, biVector X, ui size, char C );
ui   __vf   VBI_cmp_inclrangeCCind( uiVector Ind, biVector X, ui size, char CLo, char CHi );
ui   __vf   VBI_cmp_exclrangeCCind( uiVector Ind, biVector X, ui size, char CLo, char CHi );

ui   __vf   VBI_cnt_inclrange0C( biVector X, ui size, char C );
ui   __vf   VBI_cnt_exclrange0C( biVector X, ui size, char C );
ui   __vf   VBI_cnt_inclrangeCC( biVector X, ui size, char CLo, char CHi );
ui   __vf   VBI_cnt_exclrangeCC( biVector X, ui size, char CLo, char CHi );


/******************   Basic  Arithmetics   *************************/

void  __vf  VBI_neg( biVector Y, biVector X, ui size );
void  __vf  VBI_abs( biVector Y, biVector X, ui size );

void  __vf  VBI_addC(  biVector Y, biVector X, ui size, char C );
void  __vf  VBI_subC(  biVector Y, biVector X, ui size, char C );
void  __vf  VBI_subrC( biVector Y, biVector X, ui size, char C );
void  __vf  VBI_mulC(  biVector Y, biVector X, ui size, char C );
void  __vf  VBI_divC(  biVector Y, biVector X, ui size, char C );
void  __vf  VBI_divrC( biVector Y, biVector X, ui size, char C );
void  __vf  VBI_modC(  biVector Y, biVector X, ui size, char C );
void  __vf  VBI_maxC(  biVector Y, biVector X, ui size, char C );
void  __vf  VBI_minC(  biVector Y, biVector X, ui size, char C );
void  __vf  VBI_limit( biVector Y, biVector X, ui size, char Min, char Max );

void  __vf  VBI_addV(  biVector Z, biVector X, biVector Y, ui size );
void  __vf  VBI_subV(  biVector Z, biVector X, biVector Y, ui size );
void  __vf  VBI_subrV( biVector Z, biVector X, biVector Y, ui size );
void  __vf  VBI_mulV(  biVector Z, biVector X, biVector Y, ui size );
void  __vf  VBI_divV(  biVector Z, biVector X, biVector Y, ui size );
void  __vf  VBI_divrV( biVector Z, biVector X, biVector Y, ui size );
void  __vf  VBI_modV(  biVector Z, biVector X, biVector Y, ui size );
void  __vf  VBI_maxV(  biVector Z, biVector X, biVector Y, ui size );
void  __vf  VBI_minV(  biVector Z, biVector X, biVector Y, ui size );

/******************** Accumulation (Y += X) ******************************/

void __vf VBI_accV(   biVector Y, biVector  X, ui size );

/*****************   Bit-wise operations  *********************/

void    __vf  VBI_shl( biVector Y, biVector X, ui size, unsigned C );
void    __vf  VBI_shr( biVector Y, biVector X, ui size, unsigned C );

void    __vf  VBI_and( biVector Y, biVector X, ui size, char C );
void    __vf  VBI_or(  biVector Y, biVector X, ui size, char C );
void    __vf  VBI_xor( biVector Y, biVector X, ui size, char C );
void    __vf  VBI_not( biVector Y, biVector X, ui size );

#ifdef __cplusplus
} // end of extern "C"
#endif

#endif   /*  __VBIMATH_H    */
