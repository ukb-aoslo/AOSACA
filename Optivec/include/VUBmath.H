/*  VUBmath.h


  vector management functions for unsigned byte-sized integers:
  integer arithmetics and mathematics.

  Copyright (c) 1996-2017 by OptiCode - Dr. Martin Sander Software Dev.
  All Rights Reserved.
*/

#ifndef __VUBMATH_H
#define __VUBMATH_H

#if !defined( __VECLIB_H )
   #include <VecLib.h>
#endif

#ifdef __cplusplus
   extern "C" {
#endif

/********************  Comparisons ********************************/

ui   __vf   VUB_cmp_eq0( ubVector Y, ubVector X, ui size );
ui   __vf   VUB_cmp_ne0( ubVector Y, ubVector X, ui size );
ui   __vf   VUB_cmp_gt0( ubVector Y, ubVector X, ui size );

ui   __vf   VUB_cmp_eq0ind( uiVector Ind, ubVector X, ui size );
ui   __vf   VUB_cmp_ne0ind( uiVector Ind, ubVector X, ui size );
ui   __vf   VUB_cmp_gt0ind( uiVector Ind, ubVector X, ui size );

ui   __vf   VUB_cnt_eq0( ubVector X, ui size );
ui   __vf   VUB_cnt_ne0( ubVector X, ui size );
ui   __vf   VUB_cnt_gt0( ubVector X, ui size );

void __vf   VUB_cmpC(    biVector Y, ubVector X, ui size, unsigned char C );
ui   __vf   VUB_cmp_eqC( ubVector Y, ubVector X, ui size, unsigned char C );
ui   __vf   VUB_cmp_neC( ubVector Y, ubVector X, ui size, unsigned char C );
ui   __vf   VUB_cmp_leC( ubVector Y, ubVector X, ui size, unsigned char C );
ui   __vf   VUB_cmp_ltC( ubVector Y, ubVector X, ui size, unsigned char C );
ui   __vf   VUB_cmp_geC( ubVector Y, ubVector X, ui size, unsigned char C );
ui   __vf   VUB_cmp_gtC( ubVector Y, ubVector X, ui size, unsigned char C );

ui   __vf   VUB_cmp_eqCind( uiVector Ind, ubVector X, ui size, unsigned char C );
ui   __vf   VUB_cmp_neCind( uiVector Ind, ubVector X, ui size, unsigned char C );
ui   __vf   VUB_cmp_leCind( uiVector Ind, ubVector X, ui size, unsigned char C );
ui   __vf   VUB_cmp_ltCind( uiVector Ind, ubVector X, ui size, unsigned char C );
ui   __vf   VUB_cmp_geCind( uiVector Ind, ubVector X, ui size, unsigned char C );
ui   __vf   VUB_cmp_gtCind( uiVector Ind, ubVector X, ui size, unsigned char C );

ui   __vf   VUB_cnt_eqC( ubVector X, ui size, unsigned char C );
ui   __vf   VUB_cnt_neC( ubVector X, ui size, unsigned char C );
ui   __vf   VUB_cnt_leC( ubVector X, ui size, unsigned char C );
ui   __vf   VUB_cnt_ltC( ubVector X, ui size, unsigned char C );
ui   __vf   VUB_cnt_geC( ubVector X, ui size, unsigned char C );
ui   __vf   VUB_cnt_gtC( ubVector X, ui size, unsigned char C );

void __vf   VUB_cmpV(    biVector Z, ubVector X, ubVector Y, ui size );
ui   __vf   VUB_cmp_eqV( ubVector Z, ubVector X, ubVector Y, ui size );
ui   __vf   VUB_cmp_neV( ubVector Z, ubVector X, ubVector Y, ui size );
ui   __vf   VUB_cmp_leV( ubVector Z, ubVector X, ubVector Y, ui size );
ui   __vf   VUB_cmp_ltV( ubVector Z, ubVector X, ubVector Y, ui size );
ui   __vf   VUB_cmp_geV( ubVector Z, ubVector X, ubVector Y, ui size );
ui   __vf   VUB_cmp_gtV( ubVector Z, ubVector X, ubVector Y, ui size );

ui   __vf   VUB_cmp_eqVind( uiVector Ind, ubVector X, ubVector Y, ui size );
ui   __vf   VUB_cmp_neVind( uiVector Ind, ubVector X, ubVector Y, ui size );
ui   __vf   VUB_cmp_leVind( uiVector Ind, ubVector X, ubVector Y, ui size );
ui   __vf   VUB_cmp_ltVind( uiVector Ind, ubVector X, ubVector Y, ui size );
ui   __vf   VUB_cmp_geVind( uiVector Ind, ubVector X, ubVector Y, ui size );
ui   __vf   VUB_cmp_gtVind( uiVector Ind, ubVector X, ubVector Y, ui size );

ui   __vf   VUB_cnt_eqV( ubVector X, ubVector Y, ui size );
ui   __vf   VUB_cnt_neV( ubVector X, ubVector Y, ui size );
ui   __vf   VUB_cnt_leV( ubVector X, ubVector Y, ui size );
ui   __vf   VUB_cnt_ltV( ubVector X, ubVector Y, ui size );
ui   __vf   VUB_cnt_geV( ubVector X, ubVector Y, ui size );
ui   __vf   VUB_cnt_gtV( ubVector X, ubVector Y, ui size );

ui   __vf   VUB_cmp_exclrange0C( ubVector Y, ubVector X, ui size, unsigned char C );
ui   __vf   VUB_cmp_inclrangeCC( ubVector Y, ubVector X, ui size, unsigned char CLo, unsigned char CHi );
ui   __vf   VUB_cmp_exclrangeCC( ubVector Y, ubVector X, ui size, unsigned char CLo, unsigned char CHi );

ui   __vf   VUB_cmp_exclrange0Cind( uiVector Ind, ubVector X, ui size, unsigned char C );
ui   __vf   VUB_cmp_inclrangeCCind( uiVector Ind, ubVector X, ui size, unsigned char CLo, unsigned char CHi );
ui   __vf   VUB_cmp_exclrangeCCind( uiVector Ind, ubVector X, ui size, unsigned char CLo, unsigned char CHi );

ui   __vf   VUB_cnt_exclrange0C( ubVector X, ui size, unsigned char C );
ui   __vf   VUB_cnt_inclrangeCC( ubVector X, ui size, unsigned char CLo, unsigned char CHi );
ui   __vf   VUB_cnt_exclrangeCC( ubVector X, ui size, unsigned char CLo, unsigned char CHi );


/******************   Basic  Arithmetics   *************************/

void  __vf  VUB_addC(  ubVector Y, ubVector X, ui size, unsigned char C );
void  __vf  VUB_subC(  ubVector Y, ubVector X, ui size, unsigned char C );
void  __vf  VUB_subrC( ubVector Y, ubVector X, ui size, unsigned char C );
void  __vf  VUB_mulC(  ubVector Y, ubVector X, ui size, unsigned char C );
void  __vf  VUB_divC(  ubVector Y, ubVector X, ui size, unsigned char C );
void  __vf  VUB_divrC( ubVector Y, ubVector X, ui size, unsigned char C );
void  __vf  VUB_modC(  ubVector Y, ubVector X, ui size, unsigned char C );
void  __vf  VUB_maxC(  ubVector Y, ubVector X, ui size, unsigned char C );
void  __vf  VUB_minC(  ubVector Y, ubVector X, ui size, unsigned char C );
void  __vf  VUB_limit( ubVector Y, ubVector X, ui size, unsigned char Min, unsigned char Max );

void __vf  VUB_addV(  ubVector Z, ubVector X, ubVector Y, ui size );
void __vf  VUB_subV(  ubVector Z, ubVector X, ubVector Y, ui size );
void __vf  VUB_subrV( ubVector Z, ubVector X, ubVector Y, ui size );
void __vf  VUB_mulV(  ubVector Z, ubVector X, ubVector Y, ui size );
void __vf  VUB_divV(  ubVector Z, ubVector X, ubVector Y, ui size );
void __vf  VUB_divrV( ubVector Z, ubVector X, ubVector Y, ui size );
void __vf  VUB_modV(  ubVector Z, ubVector X, ubVector Y, ui size );
void __vf  VUB_maxV(  ubVector Z, ubVector X, ubVector Y, ui size );
void __vf  VUB_minV(  ubVector Z, ubVector X, ubVector Y, ui size );

/******************** Accumulation (Y += X) ******************************/

void __vf VUB_accV(   ubVector Y, ubVector  X, ui size );


/*****************   Bit-wise operations  *********************/

void    __vf  VUB_shl( ubVector Y, ubVector X, ui size, unsigned C );
void    __vf  VUB_shr( ubVector Y, ubVector X, ui size, unsigned C );

void    __vf  VUB_and( ubVector Y, ubVector X, ui size, unsigned char C );
void    __vf  VUB_or(  ubVector Y, ubVector X, ui size, unsigned char C );
void    __vf  VUB_xor( ubVector Y, ubVector X, ui size, unsigned char C );
void    __vf  VUB_not( ubVector Y, ubVector X, ui size );

/************  Optical Density Y = log10( X0 / X ) *********************/

int  __vf VUB_ODtoF( fVector OD, ubVector X, ubVector X0, ui size );
int  __vf VUB_ODtoD( dVector OD, ubVector X, ubVector X0, ui size );
int  __vf VUB_ODtoFwDark( fVector OD, ubVector X, ubVector XDark,
                          ubVector X0, ubVector X0Dark, ui size );
int  __vf VUB_ODtoDwDark( dVector OD, ubVector X, ubVector XDark,
                          ubVector X0, ubVector X0Dark, ui size );
void __vf VUB_setODThresh( unsigned char minX, unsigned char minX0 );
#if (defined __BORLANDC__) && !(defined _WIN64)   /* 80-bit reals supported ? */
int  __vf VUB_ODtoE( eVector OD, ubVector X, ubVector X0, ui size );
int  __vf VUB_ODtoEwDark( eVector OD, ubVector X, ubVector XDark,
                          ubVector X0, ubVector X0Dark, ui size );
#else
    #define VUB_ODtoE      VUB_ODtoD
    #define VUB_ODtoEwDark VUB_ODtoDwDark
#endif

#ifdef __cplusplus
}  // end of extern "C"
#endif

#endif   /*  __VUBMATH_H    */
