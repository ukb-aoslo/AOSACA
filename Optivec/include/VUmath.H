/*  VUmath.h

  vector management functions for data type "unsigned":
  integer arithmetics and mathematics.

  Copyright (c) 1996-2017 by OptiCode - Dr. Martin Sander Software Dev.
  All Rights Reserved.
*/

#ifndef __VUMATH_H
#define __VUMATH_H

#if !defined( __VECLIB_H )
   #include <VecLib.h>
#endif

#ifdef __cplusplus
   extern "C" {
#endif

/********************  Comparisons ********************************/

ui   __vf   VU_cmp_eq0( uVector Y, uVector X, ui size );
ui   __vf   VU_cmp_ne0( uVector Y, uVector X, ui size );
ui   __vf   VU_cmp_gt0( uVector Y, uVector X, ui size );

ui   __vf   VU_cmp_eq0ind( uiVector Ind, uVector X, ui size );
ui   __vf   VU_cmp_ne0ind( uiVector Ind, uVector X, ui size );
ui   __vf   VU_cmp_gt0ind( uiVector Ind, uVector X, ui size );

ui   __vf   VU_cnt_eq0( uVector X, ui size );
ui   __vf   VU_cnt_ne0( uVector X, ui size );
ui   __vf   VU_cnt_gt0( uVector X, ui size );

void __vf   VU_cmpC(    iVector Y, uVector X, ui size, unsigned int C );
ui   __vf   VU_cmp_eqC( uVector Y, uVector X, ui size, unsigned int C );
ui   __vf   VU_cmp_neC( uVector Y, uVector X, ui size, unsigned int C );
ui   __vf   VU_cmp_leC( uVector Y, uVector X, ui size, unsigned int C );
ui   __vf   VU_cmp_ltC( uVector Y, uVector X, ui size, unsigned int C );
ui   __vf   VU_cmp_geC( uVector Y, uVector X, ui size, unsigned int C );
ui   __vf   VU_cmp_gtC( uVector Y, uVector X, ui size, unsigned int C );

ui   __vf   VU_cmp_eqCind( uiVector Ind, uVector X, ui size, unsigned int C );
ui   __vf   VU_cmp_neCind( uiVector Ind, uVector X, ui size, unsigned int C );
ui   __vf   VU_cmp_leCind( uiVector Ind, uVector X, ui size, unsigned int C );
ui   __vf   VU_cmp_ltCind( uiVector Ind, uVector X, ui size, unsigned int C );
ui   __vf   VU_cmp_geCind( uiVector Ind, uVector X, ui size, unsigned int C );
ui   __vf   VU_cmp_gtCind( uiVector Ind, uVector X, ui size, unsigned int C );

ui   __vf   VU_cnt_eqC( uVector X, ui size, unsigned int C );
ui   __vf   VU_cnt_neC( uVector X, ui size, unsigned int C );
ui   __vf   VU_cnt_leC( uVector X, ui size, unsigned int C );
ui   __vf   VU_cnt_ltC( uVector X, ui size, unsigned int C );
ui   __vf   VU_cnt_geC( uVector X, ui size, unsigned int C );
ui   __vf   VU_cnt_gtC( uVector X, ui size, unsigned int C );

void __vf   VU_cmpV(    iVector Z, uVector X, uVector Y, ui size );
ui   __vf   VU_cmp_eqV( uVector Z, uVector X, uVector Y, ui size );
ui   __vf   VU_cmp_neV( uVector Z, uVector X, uVector Y, ui size );
ui   __vf   VU_cmp_leV( uVector Z, uVector X, uVector Y, ui size );
ui   __vf   VU_cmp_ltV( uVector Z, uVector X, uVector Y, ui size );
ui   __vf   VU_cmp_geV( uVector Z, uVector X, uVector Y, ui size );
ui   __vf   VU_cmp_gtV( uVector Z, uVector X, uVector Y, ui size );

ui   __vf   VU_cmp_eqVind( uiVector Ind, uVector X, uVector Y, ui size );
ui   __vf   VU_cmp_neVind( uiVector Ind, uVector X, uVector Y, ui size );
ui   __vf   VU_cmp_leVind( uiVector Ind, uVector X, uVector Y, ui size );
ui   __vf   VU_cmp_ltVind( uiVector Ind, uVector X, uVector Y, ui size );
ui   __vf   VU_cmp_geVind( uiVector Ind, uVector X, uVector Y, ui size );
ui   __vf   VU_cmp_gtVind( uiVector Ind, uVector X, uVector Y, ui size );

ui   __vf   VU_cnt_eqV( uVector X, uVector Y, ui size );
ui   __vf   VU_cnt_neV( uVector X, uVector Y, ui size );
ui   __vf   VU_cnt_leV( uVector X, uVector Y, ui size );
ui   __vf   VU_cnt_ltV( uVector X, uVector Y, ui size );
ui   __vf   VU_cnt_geV( uVector X, uVector Y, ui size );
ui   __vf   VU_cnt_gtV( uVector X, uVector Y, ui size );

ui   __vf   VU_cmp_exclrange0C( uVector Y, uVector X, ui size, unsigned int C );
ui   __vf   VU_cmp_inclrangeCC( uVector Y, uVector X, ui size, unsigned int CLo, unsigned int CHi );
ui   __vf   VU_cmp_exclrangeCC( uVector Y, uVector X, ui size, unsigned int CLo, unsigned int CHi );

ui   __vf   VU_cmp_exclrange0Cind( uiVector Ind, uVector X, ui size, unsigned int C );
ui   __vf   VU_cmp_inclrangeCCind( uiVector Ind, uVector X, ui size, unsigned int CLo, unsigned int CHi );
ui   __vf   VU_cmp_exclrangeCCind( uiVector Ind, uVector X, ui size, unsigned int CLo, unsigned int CHi );

ui   __vf   VU_cnt_exclrange0C( uVector X, ui size, unsigned int C );
ui   __vf   VU_cnt_inclrangeCC( uVector X, ui size, unsigned int CLo, unsigned int CHi );
ui   __vf   VU_cnt_exclrangeCC( uVector X, ui size, unsigned int CLo, unsigned int CHi );

/******************   Basic  Arithmetics   *************************/

#if (!defined _WIN64)
	void  __vf  VUo_addC(  uVector Y, uVector X, ui size, unsigned C );
	void  __vf  VUo_subC(  uVector Y, uVector X, ui size, unsigned C );
	void  __vf  VUo_subrC( uVector Y, uVector X, ui size, unsigned C );
	void  __vf  VUo_mulC(  uVector Y, uVector X, ui size, unsigned C );
#endif
#if defined (V_trapIntError) && (!defined _WIN64)
    #define VU_addC    VUo_addC
    #define VU_subC    VUo_subC
    #define VU_subrC   VUo_subrC
    #define VU_mulC    VUo_mulC
#else
    void  __vf  VU_addC(  uVector Y, uVector X, ui size, unsigned C );
    void  __vf  VU_subC(  uVector Y, uVector X, ui size, unsigned C );
    void  __vf  VU_subrC( uVector Y, uVector X, ui size, unsigned C );
    void  __vf  VU_mulC(  uVector Y, uVector X, ui size, unsigned C );
#endif

void  __vf  VU_divC(  uVector Y, uVector X, ui size, unsigned C );
void  __vf  VU_divrC( uVector Y, uVector X, ui size, unsigned C );
void  __vf  VU_modC(  uVector Y, uVector X, ui size, unsigned C );
void  __vf  VU_maxC(  uVector Y, uVector X, ui size, unsigned C );
void  __vf  VU_minC(  uVector Y, uVector X, ui size, unsigned C );
void  __vf  VU_limit( uVector Y, uVector X, ui size, unsigned Min, unsigned Max );

#if (!defined _WIN64)
	void  __vf  VUo_addV(  uVector Z, uVector X, uVector Y, ui size );
	void  __vf  VUo_subV(  uVector Z, uVector X, uVector Y, ui size );
	void  __vf  VUo_subrV( uVector Z, uVector X, uVector Y, ui size );
	void  __vf  VUo_mulV(  uVector Z, uVector X, uVector Y, ui size );
#endif
#if defined (V_trapIntError) && (!defined _WIN64)
    #define VU_addV    VUo_addV
    #define VU_subV    VUo_subV
    #define VU_subrV   VUo_subrV
    #define VU_mulV    VUo_mulV
#else
    void __vf  VU_addV(  uVector Z, uVector X, uVector Y, ui size );
    void __vf  VU_subV(  uVector Z, uVector X, uVector Y, ui size );
    void __vf  VU_subrV( uVector Z, uVector X, uVector Y, ui size );
    void __vf  VU_mulV(  uVector Z, uVector X, uVector Y, ui size );
#endif
void    __vf  VU_divV(  uVector Z, uVector X, uVector Y, ui size );
void    __vf  VU_divrV( uVector Z, uVector X, uVector Y, ui size );
void    __vf  VU_modV(  uVector Z, uVector X, uVector Y, ui size );
void    __vf  VU_maxV(  uVector Z, uVector X, uVector Y, ui size );
void    __vf  VU_minV(  uVector Z, uVector X, uVector Y, ui size );

/******************** Accumulation (Y += X) ******************************/

void __vf VU_accV(   uVector Y, uVector   X, ui size );
void __vf VU_accVUB( uVector Y, ubVector  X, ui size );
void __vf VU_accVUS( uVector Y, usVector  X, ui size );


/*****************   Bit-wise operations  *********************/

void    __vf  VU_shl( uVector Y, uVector X, ui size, unsigned C );
void    __vf  VU_shr( uVector Y, uVector X, ui size, unsigned C );

void    __vf  VU_and( uVector Y, uVector X, ui size, unsigned C );
void    __vf  VU_or(  uVector Y, uVector X, ui size, unsigned C );
void    __vf  VU_xor( uVector Y, uVector X, ui size, unsigned C );
void    __vf  VU_not( uVector Y, uVector X, ui size );

/************  Optical Density Y = log10( X0 / X ) *********************/

int  __vf VU_ODtoF( fVector OD, uVector X, uVector X0, ui size );
int  __vf VU_ODtoD( dVector OD, uVector X, uVector X0, ui size );
int  __vf VU_ODtoFwDark( fVector OD, uVector X, uVector XDark,
                         uVector X0, uVector X0Dark, ui size );
int  __vf VU_ODtoDwDark( dVector OD, uVector X, uVector XDark,
                         uVector X0, uVector X0Dark, ui size );
void __vf VU_setODThresh( unsigned minX, unsigned minX0 );
#if (defined __BORLANDC__) && !(defined _WIN64)   /* 80-bit reals supported ? */
int  __vf VU_ODtoE( eVector OD, uVector X, uVector X0, ui size );
int  __vf VU_ODtoEwDark( eVector OD, uVector X, uVector XDark,
                         uVector X0, uVector X0Dark, ui size );
#else
    #define VU_ODtoE      VU_ODtoD
    #define VU_ODtoEwDark VU_ODtoDwDark
#endif

#ifdef __cplusplus
}  // end of extern "C"
#endif

#endif   /*  __VUMATH_H    */
