/*  VLImath.h

  vector management functions for data type "long":
  integer arithmetics and mathematics.

  Copyright (c) 1996-2017 by OptiCode - Dr. Martin Sander Software Dev.
  All Rights Reserved.
*/

#ifndef __VLIMATH_H
#define __VLIMATH_H

#if !defined( __VECLIB_H )
   #include <VecLib.h>
#endif

#ifdef __cplusplus
   extern "C" {
#endif

/********************  Comparisons ********************************/

void __vf   VLI_cmp0(    liVector Y, liVector X, ui size );
ui   __vf   VLI_cmp_eq0( liVector Y, liVector X, ui size );
ui   __vf   VLI_cmp_ne0( liVector Y, liVector X, ui size );
ui   __vf   VLI_cmp_le0( liVector Y, liVector X, ui size );
ui   __vf   VLI_cmp_lt0( liVector Y, liVector X, ui size );
ui   __vf   VLI_cmp_ge0( liVector Y, liVector X, ui size );
ui   __vf   VLI_cmp_gt0( liVector Y, liVector X, ui size );

ui   __vf   VLI_cmp_eq0ind( uiVector Ind, liVector X, ui size );
ui   __vf   VLI_cmp_ne0ind( uiVector Ind, liVector X, ui size );
ui   __vf   VLI_cmp_le0ind( uiVector Ind, liVector X, ui size );
ui   __vf   VLI_cmp_lt0ind( uiVector Ind, liVector X, ui size );
ui   __vf   VLI_cmp_ge0ind( uiVector Ind, liVector X, ui size );
ui   __vf   VLI_cmp_gt0ind( uiVector Ind, liVector X, ui size );

ui   __vf   VLI_cnt_eq0( liVector X, ui size );
ui   __vf   VLI_cnt_ne0( liVector X, ui size );
ui   __vf   VLI_cnt_le0( liVector X, ui size );
ui   __vf   VLI_cnt_lt0( liVector X, ui size );
ui   __vf   VLI_cnt_ge0( liVector X, ui size );
ui   __vf   VLI_cnt_gt0( liVector X, ui size );

void __vf   VLI_cmpC(    liVector Y, liVector X, ui size, long C );
ui   __vf   VLI_cmp_eqC( liVector Y, liVector X, ui size, long C );
ui   __vf   VLI_cmp_neC( liVector Y, liVector X, ui size, long C );
ui   __vf   VLI_cmp_leC( liVector Y, liVector X, ui size, long C );
ui   __vf   VLI_cmp_ltC( liVector Y, liVector X, ui size, long C );
ui   __vf   VLI_cmp_geC( liVector Y, liVector X, ui size, long C );
ui   __vf   VLI_cmp_gtC( liVector Y, liVector X, ui size, long C );

ui   __vf   VLI_cmp_eqCind( uiVector Ind, liVector X, ui size, long C );
ui   __vf   VLI_cmp_neCind( uiVector Ind, liVector X, ui size, long C );
ui   __vf   VLI_cmp_leCind( uiVector Ind, liVector X, ui size, long C );
ui   __vf   VLI_cmp_ltCind( uiVector Ind, liVector X, ui size, long C );
ui   __vf   VLI_cmp_geCind( uiVector Ind, liVector X, ui size, long C );
ui   __vf   VLI_cmp_gtCind( uiVector Ind, liVector X, ui size, long C );

ui   __vf   VLI_cnt_eqC( liVector X, ui size, long C );
ui   __vf   VLI_cnt_neC( liVector X, ui size, long C );
ui   __vf   VLI_cnt_leC( liVector X, ui size, long C );
ui   __vf   VLI_cnt_ltC( liVector X, ui size, long C );
ui   __vf   VLI_cnt_geC( liVector X, ui size, long C );
ui   __vf   VLI_cnt_gtC( liVector X, ui size, long C );

void __vf   VLI_cmpV(    liVector Z, liVector X, liVector Y, ui size );
ui   __vf   VLI_cmp_eqV( liVector Z, liVector X, liVector Y, ui size );
ui   __vf   VLI_cmp_neV( liVector Z, liVector X, liVector Y, ui size );
ui   __vf   VLI_cmp_leV( liVector Z, liVector X, liVector Y, ui size );
ui   __vf   VLI_cmp_ltV( liVector Z, liVector X, liVector Y, ui size );
ui   __vf   VLI_cmp_geV( liVector Z, liVector X, liVector Y, ui size );
ui   __vf   VLI_cmp_gtV( liVector Z, liVector X, liVector Y, ui size );

ui   __vf   VLI_cmp_eqVind( uiVector Ind, liVector X, liVector Y, ui size );
ui   __vf   VLI_cmp_neVind( uiVector Ind, liVector X, liVector Y, ui size );
ui   __vf   VLI_cmp_leVind( uiVector Ind, liVector X, liVector Y, ui size );
ui   __vf   VLI_cmp_ltVind( uiVector Ind, liVector X, liVector Y, ui size );
ui   __vf   VLI_cmp_geVind( uiVector Ind, liVector X, liVector Y, ui size );
ui   __vf   VLI_cmp_gtVind( uiVector Ind, liVector X, liVector Y, ui size );

ui   __vf   VLI_cnt_eqV( liVector X, liVector Y, ui size );
ui   __vf   VLI_cnt_neV( liVector X, liVector Y, ui size );
ui   __vf   VLI_cnt_leV( liVector X, liVector Y, ui size );
ui   __vf   VLI_cnt_ltV( liVector X, liVector Y, ui size );
ui   __vf   VLI_cnt_geV( liVector X, liVector Y, ui size );
ui   __vf   VLI_cnt_gtV( liVector X, liVector Y, ui size );

ui   __vf   VLI_cmp_inclrange0C( liVector Y, liVector X, ui size, long C );
ui   __vf   VLI_cmp_exclrange0C( liVector Y, liVector X, ui size, long C );
ui   __vf   VLI_cmp_inclrangeCC( liVector Y, liVector X, ui size, long CLo, long CHi );
ui   __vf   VLI_cmp_exclrangeCC( liVector Y, liVector X, ui size, long CLo, long CHi );

ui   __vf   VLI_cmp_inclrange0Cind( uiVector Ind, liVector X, ui size, long C );
ui   __vf   VLI_cmp_exclrange0Cind( uiVector Ind, liVector X, ui size, long C );
ui   __vf   VLI_cmp_inclrangeCCind( uiVector Ind, liVector X, ui size, long CLo, long CHi );
ui   __vf   VLI_cmp_exclrangeCCind( uiVector Ind, liVector X, ui size, long CLo, long CHi );

ui   __vf   VLI_cnt_inclrange0C( liVector X, ui size, long C );
ui   __vf   VLI_cnt_exclrange0C( liVector X, ui size, long C );
ui   __vf   VLI_cnt_inclrangeCC( liVector X, ui size, long CLo, long CHi );
ui   __vf   VLI_cnt_exclrangeCC( liVector X, ui size, long CLo, long CHi );


/******************   Basic  Arithmetics   *************************/

void  __vf  VLI_neg( liVector Y, liVector X, ui size );
void  __vf  VLI_abs( liVector Y, liVector X, ui size );

#if (!defined _WIN64)
	void  __vf  VLIo_addC(  liVector Y, liVector X, ui size, long C );
	void  __vf  VLIo_subC(  liVector Y, liVector X, ui size, long C );
	void  __vf  VLIo_subrC( liVector Y, liVector X, ui size, long C );
	void  __vf  VLIo_mulC(  liVector Y, liVector X, ui size, long C );
#endif
#if defined (V_trapIntError) && (!defined _WIN64)
    #define VLI_addC    VLIo_addC
    #define VLI_subC    VLIo_subC
    #define VLI_subrC   VLIo_subrC
    #define VLI_mulC    VLIo_mulC
#else
    void  __vf  VLI_addC(  liVector Y, liVector X, ui size, long C );
    void  __vf  VLI_subC(  liVector Y, liVector X, ui size, long C );
    void  __vf  VLI_subrC( liVector Y, liVector X, ui size, long C );
    void  __vf  VLI_mulC(  liVector Y, liVector X, ui size, long C );
#endif
void  __vf  VLI_divC(  liVector Y, liVector X, ui size, long C );
void  __vf  VLI_divrC( liVector Y, liVector X, ui size, long C );
void  __vf  VLI_modC(  liVector Y, liVector X, ui size, long C );
void  __vf  VLI_maxC(  liVector Y, liVector X, ui size, long C );
void  __vf  VLI_minC(  liVector Y, liVector X, ui size, long C );
void  __vf  VLI_limit( liVector Y, liVector X, ui size, long Min, long Max );

#if (!defined _WIN64)
	void  __vf  VLIo_addV(  liVector Z, liVector X, liVector Y, ui size );
	void  __vf  VLIo_subV(  liVector Z, liVector X, liVector Y, ui size );
	void  __vf  VLIo_subrV( liVector Z, liVector X, liVector Y, ui size );
	void  __vf  VLIo_mulV(  liVector Z, liVector X, liVector Y, ui size );
#endif
#if defined (V_trapIntError) && (!defined _WIN64)
    #define VLI_addV    VLIo_addV
    #define VLI_subV    VLIo_subV
    #define VLI_subrV   VLIo_subrV
    #define VLI_mulV    VLIo_mulV
#else
    void  __vf  VLI_addV(  liVector Z, liVector X, liVector Y, ui size );
    void  __vf  VLI_subV(  liVector Z, liVector X, liVector Y, ui size );
    void  __vf  VLI_subrV( liVector Z, liVector X, liVector Y, ui size );
    void  __vf  VLI_mulV(  liVector Z, liVector X, liVector Y, ui size );
#endif
void  __vf  VLI_divV(  liVector Z, liVector X, liVector Y, ui size );
void  __vf  VLI_divrV( liVector Z, liVector X, liVector Y, ui size );
void  __vf  VLI_modV(  liVector Z, liVector X, liVector Y, ui size );
void  __vf  VLI_maxV(  liVector Z, liVector X, liVector Y, ui size );
void  __vf  VLI_minV(  liVector Z, liVector X, liVector Y, ui size );

/******************** Accumulation (Y += X) ******************************/

void __vf VLI_accV(   liVector Y, liVector  X, ui size );
void __vf VLI_accVBI( liVector Y, biVector  X, ui size );
void __vf VLI_accVSI( liVector Y, siVector  X, ui size );
void __vf VLI_accVI(  liVector Y, iVector   X, ui size );

/*****************   Bit-wise operations  *********************/

void    __vf  VLI_shl( liVector Y, liVector X, ui size, unsigned C );
void    __vf  VLI_shr( liVector Y, liVector X, ui size, unsigned C );

void    __vf  VLI_and( liVector Y, liVector X, ui size, long C );
void    __vf  VLI_or(  liVector Y, liVector X, ui size, long C );
void    __vf  VLI_xor( liVector Y, liVector X, ui size, long C );
void    __vf  VLI_not( liVector Y, liVector X, ui size );

#ifdef __cplusplus
}  // end of extern "C"
#endif

#endif   /*  __VLIMATH_H    */
