/*  VULmath.h

  vector management functions for data type "unsigned long":
  integer arithmetics and mathematics.

  Copyright (c) 1996-2017 by OptiCode - Dr. Martin Sander Software Dev.
  All Rights Reserved.
*/

#ifndef __VULMATH_H
#define __VULMATH_H

#if !defined( __VECLIB_H )
   #include <VecLib.h>
#endif

#ifdef __cplusplus
   extern "C" {
#endif

/********************  Comparisons ********************************/

ui   __vf   VUL_cmp_eq0( ulVector Y, ulVector X, ui size );
ui   __vf   VUL_cmp_ne0( ulVector Y, ulVector X, ui size );
ui   __vf   VUL_cmp_gt0( ulVector Y, ulVector X, ui size );

ui   __vf   VUL_cmp_eq0ind( uiVector Ind, ulVector X, ui size );
ui   __vf   VUL_cmp_ne0ind( uiVector Ind, ulVector X, ui size );
ui   __vf   VUL_cmp_gt0ind( uiVector Ind, ulVector X, ui size );

ui   __vf   VUL_cnt_eq0( ulVector X, ui size );
ui   __vf   VUL_cnt_ne0( ulVector X, ui size );
ui   __vf   VUL_cnt_gt0( ulVector X, ui size );

void __vf   VUL_cmpC(    liVector Y, ulVector X, ui size, unsigned long C );
ui   __vf   VUL_cmp_eqC( ulVector Y, ulVector X, ui size, unsigned long C );
ui   __vf   VUL_cmp_neC( ulVector Y, ulVector X, ui size, unsigned long C );
ui   __vf   VUL_cmp_leC( ulVector Y, ulVector X, ui size, unsigned long C );
ui   __vf   VUL_cmp_ltC( ulVector Y, ulVector X, ui size, unsigned long C );
ui   __vf   VUL_cmp_geC( ulVector Y, ulVector X, ui size, unsigned long C );
ui   __vf   VUL_cmp_gtC( ulVector Y, ulVector X, ui size, unsigned long C );

ui   __vf   VUL_cmp_eqCind( uiVector Ind, ulVector X, ui size, unsigned long C );
ui   __vf   VUL_cmp_neCind( uiVector Ind, ulVector X, ui size, unsigned long C );
ui   __vf   VUL_cmp_leCind( uiVector Ind, ulVector X, ui size, unsigned long C );
ui   __vf   VUL_cmp_ltCind( uiVector Ind, ulVector X, ui size, unsigned long C );
ui   __vf   VUL_cmp_geCind( uiVector Ind, ulVector X, ui size, unsigned long C );
ui   __vf   VUL_cmp_gtCind( uiVector Ind, ulVector X, ui size, unsigned long C );

ui   __vf   VUL_cnt_eqC( ulVector X, ui size, unsigned long C );
ui   __vf   VUL_cnt_neC( ulVector X, ui size, unsigned long C );
ui   __vf   VUL_cnt_leC( ulVector X, ui size, unsigned long C );
ui   __vf   VUL_cnt_ltC( ulVector X, ui size, unsigned long C );
ui   __vf   VUL_cnt_geC( ulVector X, ui size, unsigned long C );
ui   __vf   VUL_cnt_gtC( ulVector X, ui size, unsigned long C );

void __vf   VUL_cmpV(    liVector Z, ulVector X, ulVector Y, ui size );
ui   __vf   VUL_cmp_eqV( ulVector Z, ulVector X, ulVector Y, ui size );
ui   __vf   VUL_cmp_neV( ulVector Z, ulVector X, ulVector Y, ui size );
ui   __vf   VUL_cmp_leV( ulVector Z, ulVector X, ulVector Y, ui size );
ui   __vf   VUL_cmp_ltV( ulVector Z, ulVector X, ulVector Y, ui size );
ui   __vf   VUL_cmp_geV( ulVector Z, ulVector X, ulVector Y, ui size );
ui   __vf   VUL_cmp_gtV( ulVector Z, ulVector X, ulVector Y, ui size );

ui   __vf   VUL_cmp_eqVind( uiVector Ind, ulVector X, ulVector Y, ui size );
ui   __vf   VUL_cmp_neVind( uiVector Ind, ulVector X, ulVector Y, ui size );
ui   __vf   VUL_cmp_leVind( uiVector Ind, ulVector X, ulVector Y, ui size );
ui   __vf   VUL_cmp_ltVind( uiVector Ind, ulVector X, ulVector Y, ui size );
ui   __vf   VUL_cmp_geVind( uiVector Ind, ulVector X, ulVector Y, ui size );
ui   __vf   VUL_cmp_gtVind( uiVector Ind, ulVector X, ulVector Y, ui size );

ui   __vf   VUL_cnt_eqV( ulVector X, ulVector Y, ui size );
ui   __vf   VUL_cnt_neV( ulVector X, ulVector Y, ui size );
ui   __vf   VUL_cnt_leV( ulVector X, ulVector Y, ui size );
ui   __vf   VUL_cnt_ltV( ulVector X, ulVector Y, ui size );
ui   __vf   VUL_cnt_geV( ulVector X, ulVector Y, ui size );
ui   __vf   VUL_cnt_gtV( ulVector X, ulVector Y, ui size );

ui   __vf   VUL_cmp_exclrange0C( ulVector Y, ulVector X, ui size, unsigned long C );
ui   __vf   VUL_cmp_inclrangeCC( ulVector Y, ulVector X, ui size, unsigned long CLo, unsigned long CHi );
ui   __vf   VUL_cmp_exclrangeCC( ulVector Y, ulVector X, ui size, unsigned long CLo, unsigned long CHi );

ui   __vf   VUL_cmp_exclrange0Cind( uiVector Ind, ulVector X, ui size, unsigned long C );
ui   __vf   VUL_cmp_inclrangeCCind( uiVector Ind, ulVector X, ui size, unsigned long CLo, unsigned long CHi );
ui   __vf   VUL_cmp_exclrangeCCind( uiVector Ind, ulVector X, ui size, unsigned long CLo, unsigned long CHi );

ui   __vf   VUL_cnt_exclrange0C( ulVector X, ui size, unsigned long C );
ui   __vf   VUL_cnt_inclrangeCC( ulVector X, ui size, unsigned long CLo, unsigned long CHi );
ui   __vf   VUL_cnt_exclrangeCC( ulVector X, ui size, unsigned long CLo, unsigned long CHi );

/******************   Basic  Arithmetics   *************************/

#if (!defined _WIN64)
	void  __vf  VULo_addC(  ulVector Y, ulVector X, ui size, unsigned long C );
	void  __vf  VULo_subC(  ulVector Y, ulVector X, ui size, unsigned long C );
	void  __vf  VULo_subrC( ulVector Y, ulVector X, ui size, unsigned long C );
	void  __vf  VULo_mulC(  ulVector Y, ulVector X, ui size, unsigned long C );
#endif
#if defined (V_trapIntError) && (!defined _WIN64)
    #define VUL_addC    VULo_addC
    #define VUL_subC    VULo_subC
    #define VUL_subrC   VULo_subrC
    #define VUL_mulC    VULo_mulC
#else
    void  __vf  VUL_addC(  ulVector Y, ulVector X, ui size, unsigned long C );
    void  __vf  VUL_subC(  ulVector Y, ulVector X, ui size, unsigned long C );
    void  __vf  VUL_subrC( ulVector Y, ulVector X, ui size, unsigned long C );
    void  __vf  VUL_mulC(  ulVector Y, ulVector X, ui size, unsigned long C );
#endif

void  __vf  VUL_divC(  ulVector Y, ulVector X, ui size, unsigned long C );
void  __vf  VUL_divrC( ulVector Y, ulVector X, ui size, unsigned long C );
void  __vf  VUL_modC(  ulVector Y, ulVector X, ui size, unsigned long C );
void  __vf  VUL_maxC(  ulVector Y, ulVector X, ui size, unsigned long C );
void  __vf  VUL_minC(  ulVector Y, ulVector X, ui size, unsigned long C );
void  __vf  VUL_limit( ulVector Y, ulVector X, ui size, unsigned long Min, unsigned long Max );

#if (!defined _WIN64)
	void  __vf  VULo_addV(  ulVector Z, ulVector X, ulVector Y, ui size );
	void  __vf  VULo_subV(  ulVector Z, ulVector X, ulVector Y, ui size );
	void  __vf  VULo_subrV( ulVector Z, ulVector X, ulVector Y, ui size );
	void  __vf  VULo_mulV(  ulVector Z, ulVector X, ulVector Y, ui size );
#endif
#if defined (V_trapIntError) && (!defined _WIN64)
    #define VUL_addV    VULo_addV
    #define VUL_subV    VULo_subV
    #define VUL_subrV   VULo_subrV
    #define VUL_mulV    VULo_mulV
#else
    void __vf  VUL_addV(  ulVector Z, ulVector X, ulVector Y, ui size );
    void __vf  VUL_subV(  ulVector Z, ulVector X, ulVector Y, ui size );
    void __vf  VUL_subrV( ulVector Z, ulVector X, ulVector Y, ui size );
    void __vf  VUL_mulV(  ulVector Z, ulVector X, ulVector Y, ui size );
#endif
void    __vf  VUL_divV(  ulVector Z, ulVector X, ulVector Y, ui size );
void    __vf  VUL_divrV( ulVector Z, ulVector X, ulVector Y, ui size );
void    __vf  VUL_modV(  ulVector Z, ulVector X, ulVector Y, ui size );
void    __vf  VUL_maxV(  ulVector Z, ulVector X, ulVector Y, ui size );
void    __vf  VUL_minV(  ulVector Z, ulVector X, ulVector Y, ui size );

/******************** Accumulation (Y += X) ******************************/

void __vf VUL_accV(   ulVector Y, ulVector  X, ui size );
void __vf VUL_accVUB( ulVector Y, ubVector  X, ui size );
void __vf VUL_accVUS( ulVector Y, usVector  X, ui size );
void __vf VUL_accVU(  ulVector Y, uVector   X, ui size );

/*****************   Bit-wise operations  *********************/

void    __vf  VUL_shl( ulVector Y, ulVector X, ui size, unsigned C );
void    __vf  VUL_shr( ulVector Y, ulVector X, ui size, unsigned C );

void    __vf  VUL_and( ulVector Y, ulVector X, ui size, unsigned long C );
void    __vf  VUL_or(  ulVector Y, ulVector X, ui size, unsigned long C );
void    __vf  VUL_xor( ulVector Y, ulVector X, ui size, unsigned long C );
void    __vf  VUL_not( ulVector Y, ulVector X, ui size );

/************  Optical Density Y = log10( X0 / X ) *********************/

int  __vf VUL_ODtoF( fVector OD, ulVector X, ulVector X0, ui size );
int  __vf VUL_ODtoD( dVector OD, ulVector X, ulVector X0, ui size );
int  __vf VUL_ODtoFwDark( fVector OD, ulVector X, ulVector XDark,
                          ulVector X0, ulVector X0Dark, ui size );
int  __vf VUL_ODtoDwDark( dVector OD, ulVector X, ulVector XDark,
                          ulVector X0, ulVector X0Dark, ui size );
void __vf VUL_setODThresh( unsigned long minX, unsigned long minX0 );
#if (defined __BORLANDC__) && !(defined _WIN64)   /* 80-bit reals supported ? */
int  __vf VUL_ODtoE( eVector OD, ulVector X, ulVector X0, ui size );
int  __vf VUL_ODtoEwDark( eVector OD, ulVector X, ulVector XDark,
                          ulVector X0, ulVector X0Dark, ui size );
#else
    #define VUL_ODtoE      VUL_ODtoD
    #define VUL_ODtoEwDark VUL_ODtoDwDark
#endif

#ifdef __cplusplus
}  // end of extern "C"
#endif

#endif   /*  __VULMATH_H    */
