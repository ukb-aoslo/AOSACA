/*  VSImath.h

  vector management functions for data type "short":
  integer arithmetics and mathematics.

  Copyright (c) 1996-2017 by OptiCode - Dr. Martin Sander Software Dev.
  All Rights Reserved.
*/

#ifndef __VSIMATH_H
#define __VSIMATH_H

#if !defined( __VECLIB_H )
   #include <VecLib.h>
#endif

#ifdef __cplusplus
   extern "C" {
#endif

/********************  Comparisons ********************************/

void __vf   VSI_cmp0(    siVector Y, siVector X, ui size );
ui   __vf   VSI_cmp_eq0( siVector Y, siVector X, ui size );
ui   __vf   VSI_cmp_ne0( siVector Y, siVector X, ui size );
ui   __vf   VSI_cmp_le0( siVector Y, siVector X, ui size );
ui   __vf   VSI_cmp_lt0( siVector Y, siVector X, ui size );
ui   __vf   VSI_cmp_ge0( siVector Y, siVector X, ui size );
ui   __vf   VSI_cmp_gt0( siVector Y, siVector X, ui size );

ui   __vf   VSI_cmp_eq0ind( uiVector Ind, siVector X, ui size );
ui   __vf   VSI_cmp_ne0ind( uiVector Ind, siVector X, ui size );
ui   __vf   VSI_cmp_le0ind( uiVector Ind, siVector X, ui size );
ui   __vf   VSI_cmp_lt0ind( uiVector Ind, siVector X, ui size );
ui   __vf   VSI_cmp_ge0ind( uiVector Ind, siVector X, ui size );
ui   __vf   VSI_cmp_gt0ind( uiVector Ind, siVector X, ui size );

ui   __vf   VSI_cnt_eq0( siVector X, ui size );
ui   __vf   VSI_cnt_ne0( siVector X, ui size );
ui   __vf   VSI_cnt_le0( siVector X, ui size );
ui   __vf   VSI_cnt_lt0( siVector X, ui size );
ui   __vf   VSI_cnt_ge0( siVector X, ui size );
ui   __vf   VSI_cnt_gt0( siVector X, ui size );

void __vf   VSI_cmpC(    siVector Y, siVector X, ui size, short C );
ui   __vf   VSI_cmp_eqC( siVector Y, siVector X, ui size, short C );
ui   __vf   VSI_cmp_neC( siVector Y, siVector X, ui size, short C );
ui   __vf   VSI_cmp_leC( siVector Y, siVector X, ui size, short C );
ui   __vf   VSI_cmp_ltC( siVector Y, siVector X, ui size, short C );
ui   __vf   VSI_cmp_geC( siVector Y, siVector X, ui size, short C );
ui   __vf   VSI_cmp_gtC( siVector Y, siVector X, ui size, short C );

ui   __vf   VSI_cmp_eqCind( uiVector Ind, siVector X, ui size, short C );
ui   __vf   VSI_cmp_neCind( uiVector Ind, siVector X, ui size, short C );
ui   __vf   VSI_cmp_leCind( uiVector Ind, siVector X, ui size, short C );
ui   __vf   VSI_cmp_ltCind( uiVector Ind, siVector X, ui size, short C );
ui   __vf   VSI_cmp_geCind( uiVector Ind, siVector X, ui size, short C );
ui   __vf   VSI_cmp_gtCind( uiVector Ind, siVector X, ui size, short C );

ui   __vf   VSI_cnt_eqC( siVector X, ui size, short C );
ui   __vf   VSI_cnt_neC( siVector X, ui size, short C );
ui   __vf   VSI_cnt_leC( siVector X, ui size, short C );
ui   __vf   VSI_cnt_ltC( siVector X, ui size, short C );
ui   __vf   VSI_cnt_geC( siVector X, ui size, short C );
ui   __vf   VSI_cnt_gtC( siVector X, ui size, short C );

void __vf   VSI_cmpV(    siVector Z, siVector X, siVector Y, ui size );
ui   __vf   VSI_cmp_eqV( siVector Z, siVector X, siVector Y, ui size );
ui   __vf   VSI_cmp_neV( siVector Z, siVector X, siVector Y, ui size );
ui   __vf   VSI_cmp_leV( siVector Z, siVector X, siVector Y, ui size );
ui   __vf   VSI_cmp_ltV( siVector Z, siVector X, siVector Y, ui size );
ui   __vf   VSI_cmp_geV( siVector Z, siVector X, siVector Y, ui size );
ui   __vf   VSI_cmp_gtV( siVector Z, siVector X, siVector Y, ui size );

ui   __vf   VSI_cmp_eqVind( uiVector Ind, siVector X, siVector Y, ui size );
ui   __vf   VSI_cmp_neVind( uiVector Ind, siVector X, siVector Y, ui size );
ui   __vf   VSI_cmp_leVind( uiVector Ind, siVector X, siVector Y, ui size );
ui   __vf   VSI_cmp_ltVind( uiVector Ind, siVector X, siVector Y, ui size );
ui   __vf   VSI_cmp_geVind( uiVector Ind, siVector X, siVector Y, ui size );
ui   __vf   VSI_cmp_gtVind( uiVector Ind, siVector X, siVector Y, ui size );

ui   __vf   VSI_cnt_eqV( siVector X, siVector Y, ui size );
ui   __vf   VSI_cnt_neV( siVector X, siVector Y, ui size );
ui   __vf   VSI_cnt_leV( siVector X, siVector Y, ui size );
ui   __vf   VSI_cnt_ltV( siVector X, siVector Y, ui size );
ui   __vf   VSI_cnt_geV( siVector X, siVector Y, ui size );
ui   __vf   VSI_cnt_gtV( siVector X, siVector Y, ui size );

ui   __vf   VSI_cmp_inclrange0C( siVector Y, siVector X, ui size, short C );
ui   __vf   VSI_cmp_exclrange0C( siVector Y, siVector X, ui size, short C );
ui   __vf   VSI_cmp_inclrangeCC( siVector Y, siVector X, ui size, short CLo, short CHi );
ui   __vf   VSI_cmp_exclrangeCC( siVector Y, siVector X, ui size, short CLo, short CHi );

ui   __vf   VSI_cmp_inclrange0Cind( uiVector Ind, siVector X, ui size, short C );
ui   __vf   VSI_cmp_exclrange0Cind( uiVector Ind, siVector X, ui size, short C );
ui   __vf   VSI_cmp_inclrangeCCind( uiVector Ind, siVector X, ui size, short CLo, short CHi );
ui   __vf   VSI_cmp_exclrangeCCind( uiVector Ind, siVector X, ui size, short CLo, short CHi );

ui   __vf   VSI_cnt_inclrange0C( siVector X, ui size, short C );
ui   __vf   VSI_cnt_exclrange0C( siVector X, ui size, short C );
ui   __vf   VSI_cnt_inclrangeCC( siVector X, ui size, short CLo, short CHi );
ui   __vf   VSI_cnt_exclrangeCC( siVector X, ui size, short CLo, short CHi );


/******************   Basic  Arithmetics   *************************/

void  __vf  VSI_neg( siVector Y, siVector X, ui size );
void  __vf  VSI_abs( siVector Y, siVector X, ui size );

#if (!defined _WIN64)
	void  __vf  VSIo_addC(  siVector Y, siVector X, ui size, short C );
	void  __vf  VSIo_subC(  siVector Y, siVector X, ui size, short C );
	void  __vf  VSIo_subrC( siVector Y, siVector X, ui size, short C );
	void  __vf  VSIo_mulC(  siVector Y, siVector X, ui size, short C );
#endif
#if defined (V_trapIntError) && (!defined _WIN64)
    #define VSI_addC    VSIo_addC
    #define VSI_subC    VSIo_subC
    #define VSI_subrC   VSIo_subrC
    #define VSI_mulC    VSIo_mulC
#else
    void  __vf  VSI_addC(  siVector Y, siVector X, ui size, short C );
    void  __vf  VSI_subC(  siVector Y, siVector X, ui size, short C );
    void  __vf  VSI_subrC( siVector Y, siVector X, ui size, short C );
    void  __vf  VSI_mulC(  siVector Y, siVector X, ui size, short C );
#endif
void  __vf  VSI_divC(  siVector Y, siVector X, ui size, short C );
void  __vf  VSI_divrC( siVector Y, siVector X, ui size, short C );
void  __vf  VSI_modC(  siVector Y, siVector X, ui size, short C );
void  __vf  VSI_maxC(  siVector Y, siVector X, ui size, short C );
void  __vf  VSI_minC(  siVector Y, siVector X, ui size, short C );
void  __vf  VSI_limit( siVector Y, siVector X, ui size, short Min, short Max );

#if (!defined _WIN64)
	void  __vf  VSIo_addV(  siVector Z, siVector X, siVector Y, ui size );
	void  __vf  VSIo_subV(  siVector Z, siVector X, siVector Y, ui size );
	void  __vf  VSIo_subrV( siVector Z, siVector X, siVector Y, ui size );
	void  __vf  VSIo_mulV(  siVector Z, siVector X, siVector Y, ui size );
#endif
#if defined (V_trapIntError) && (!defined _WIN64)
    #define VSI_addV     VSIo_addV
    #define VSI_subV     VSIo_subV
    #define VSI_subrV    VSIo_subrV
    #define VSI_mulV     VSIo_mulV
#else
    void    __vf  VSI_addV(  siVector Z, siVector X, siVector Y, ui size );
    void    __vf  VSI_subV(  siVector Z, siVector X, siVector Y, ui size );
    void    __vf  VSI_subrV( siVector Z, siVector X, siVector Y, ui size );
    void    __vf  VSI_mulV(  siVector Z, siVector X, siVector Y, ui size );
#endif
void    __vf  VSI_divV(  siVector Z, siVector X, siVector Y, ui size );
void    __vf  VSI_divrV( siVector Z, siVector X, siVector Y, ui size );
void    __vf  VSI_modV(  siVector Z, siVector X, siVector Y, ui size );
void    __vf  VSI_maxV(  siVector Z, siVector X, siVector Y, ui size );
void    __vf  VSI_minV(  siVector Z, siVector X, siVector Y, ui size );

/******************** Accumulation (Y += X) ******************************/

void __vf VSI_accV(   siVector Y, siVector  X, ui size );
void __vf VSI_accVBI( siVector Y, biVector  X, ui size );


/*****************   Bit-wise operations  *********************/

void    __vf  VSI_shl( siVector Y, siVector X, ui size, unsigned C );
void    __vf  VSI_shr( siVector Y, siVector X, ui size, unsigned C );

void    __vf  VSI_and( siVector Y, siVector X, ui size, short C );
void    __vf  VSI_or(  siVector Y, siVector X, ui size, short C );
void    __vf  VSI_xor( siVector Y, siVector X, ui size, short C );
void    __vf  VSI_not( siVector Y, siVector X, ui size );

#ifdef __cplusplus
}  // end of extern "C"
#endif

#endif   /*  __VSIMATH_H    */
