/*  cudaVSImath.h

  vector management functions for data type "short":
  integer arithmetics and mathematics.

  Copyright (c) 1996-2017 by OptiCode - Dr. Martin Sander Software Dev.
  All Rights Reserved.
*/

#ifndef __CUDAVSIMATH_H
#define __CUDAVSIMATH_H

#if !defined( __CUDAVECLIB_H )
   #include <cudaVecLib.h>
#endif

/******************  cudaVSI_ functions: **********************************
	 act on vectors in CUDA device memory; 
	 scalar parameters and return values on host
******************  cusdVSI_ functions: **********************************
	 also act on vectors in CUDA device memory; 
	 scalar parameters and return values by address on device memory
************************************************************************/

#ifdef __cplusplus
   extern "C" {
#endif

/********************  Comparisons ********************************/

overror_t  __vcuf OVCUAPI   cudaVSI_cmp0(    siVector Y, siVector X, ui size );
overror_t  __vcuf OVCUAPI   cudaVSI_cmp_eq0( ui *h_nTrue, siVector Y, siVector X, ui size );
overror_t  __vcuf OVCUAPI   cudaVSI_cmp_ne0( ui *h_nTrue, siVector Y, siVector X, ui size );
overror_t  __vcuf OVCUAPI   cudaVSI_cmp_le0( ui *h_nTrue, siVector Y, siVector X, ui size );
overror_t  __vcuf OVCUAPI   cudaVSI_cmp_lt0( ui *h_nTrue, siVector Y, siVector X, ui size );
overror_t  __vcuf OVCUAPI   cudaVSI_cmp_ge0( ui *h_nTrue, siVector Y, siVector X, ui size );
overror_t  __vcuf OVCUAPI   cudaVSI_cmp_gt0( ui *h_nTrue, siVector Y, siVector X, ui size );

overror_t  __vcuf OVCUAPI   cudaVSI_cmpC(    siVector Y, siVector X, ui size, short C );
overror_t  __vcuf OVCUAPI   cudaVSI_cmp_eqC( ui *h_nTrue, siVector Y, siVector X, ui size, short C );
overror_t  __vcuf OVCUAPI   cudaVSI_cmp_neC( ui *h_nTrue, siVector Y, siVector X, ui size, short C );
overror_t  __vcuf OVCUAPI   cudaVSI_cmp_leC( ui *h_nTrue, siVector Y, siVector X, ui size, short C );
overror_t  __vcuf OVCUAPI   cudaVSI_cmp_ltC( ui *h_nTrue, siVector Y, siVector X, ui size, short C );
overror_t  __vcuf OVCUAPI   cudaVSI_cmp_geC( ui *h_nTrue, siVector Y, siVector X, ui size, short C );
overror_t  __vcuf OVCUAPI   cudaVSI_cmp_gtC( ui *h_nTrue, siVector Y, siVector X, ui size, short C );
overror_t  __vcuf OVCUAPI   cusdVSI_cmpC(    siVector Y, siVector X, ui size, short *d_C );
overror_t  __vcuf OVCUAPI   cusdVSI_cmp_eqC( ui *h_nTrue, siVector Y, siVector X, ui size, short *d_C );
overror_t  __vcuf OVCUAPI   cusdVSI_cmp_neC( ui *h_nTrue, siVector Y, siVector X, ui size, short *d_C );
overror_t  __vcuf OVCUAPI   cusdVSI_cmp_leC( ui *h_nTrue, siVector Y, siVector X, ui size, short *d_C );
overror_t  __vcuf OVCUAPI   cusdVSI_cmp_ltC( ui *h_nTrue, siVector Y, siVector X, ui size, short *d_C );
overror_t  __vcuf OVCUAPI   cusdVSI_cmp_geC( ui *h_nTrue, siVector Y, siVector X, ui size, short *d_C );
overror_t  __vcuf OVCUAPI   cusdVSI_cmp_gtC( ui *h_nTrue, siVector Y, siVector X, ui size, short *d_C );

overror_t  __vcuf OVCUAPI   cudaVSI_cmpV(    siVector Z, siVector X, siVector Y, ui size );
overror_t  __vcuf OVCUAPI   cudaVSI_cmp_eqV( ui *h_nTrue, siVector Z, siVector X, siVector Y, ui size );
overror_t  __vcuf OVCUAPI   cudaVSI_cmp_neV( ui *h_nTrue, siVector Z, siVector X, siVector Y, ui size );
overror_t  __vcuf OVCUAPI   cudaVSI_cmp_leV( ui *h_nTrue, siVector Z, siVector X, siVector Y, ui size );
overror_t  __vcuf OVCUAPI   cudaVSI_cmp_ltV( ui *h_nTrue, siVector Z, siVector X, siVector Y, ui size );
overror_t  __vcuf OVCUAPI   cudaVSI_cmp_geV( ui *h_nTrue, siVector Z, siVector X, siVector Y, ui size );
overror_t  __vcuf OVCUAPI   cudaVSI_cmp_gtV( ui *h_nTrue, siVector Z, siVector X, siVector Y, ui size );

overror_t  __vcuf OVCUAPI   cudaVSI_cmp_inclrange0C( ui *h_nTrue, siVector Y, siVector X, ui size, short C );
overror_t  __vcuf OVCUAPI   cudaVSI_cmp_exclrange0C( ui *h_nTrue, siVector Y, siVector X, ui size, short C );
overror_t  __vcuf OVCUAPI   cudaVSI_cmp_inclrangeCC( ui *h_nTrue, siVector Y, siVector X, ui size, short CLo, short CHi );
overror_t  __vcuf OVCUAPI   cudaVSI_cmp_exclrangeCC( ui *h_nTrue, siVector Y, siVector X, ui size, short CLo, short CHi );
overror_t  __vcuf OVCUAPI   cusdVSI_cmp_inclrange0C( ui *h_nTrue, siVector Y, siVector X, ui size, short *d_C );
overror_t  __vcuf OVCUAPI   cusdVSI_cmp_exclrange0C( ui *h_nTrue, siVector Y, siVector X, ui size, short *d_C );
overror_t  __vcuf OVCUAPI   cusdVSI_cmp_inclrangeCC( ui *h_nTrue, siVector Y, siVector X, ui size, short *d_CLo, short *d_CHi );
overror_t  __vcuf OVCUAPI   cusdVSI_cmp_exclrangeCC( ui *h_nTrue, siVector Y, siVector X, ui size, short *d_CLo, short *d_CHi );

overror_t  __vcuf OVCUAPI   cudaVSI_cnt_eq0( ui *h_nTrue, siVector X, ui size );
overror_t  __vcuf OVCUAPI   cudaVSI_cnt_ne0( ui *h_nTrue, siVector X, ui size );
overror_t  __vcuf OVCUAPI   cudaVSI_cnt_le0( ui *h_nTrue, siVector X, ui size );
overror_t  __vcuf OVCUAPI   cudaVSI_cnt_lt0( ui *h_nTrue, siVector X, ui size );
overror_t  __vcuf OVCUAPI   cudaVSI_cnt_ge0( ui *h_nTrue, siVector X, ui size );
overror_t  __vcuf OVCUAPI   cudaVSI_cnt_gt0( ui *h_nTrue, siVector X, ui size );

overror_t  __vcuf OVCUAPI   cudaVSI_cnt_eqC( ui *h_nTrue, siVector X, ui size, short C );
overror_t  __vcuf OVCUAPI   cudaVSI_cnt_neC( ui *h_nTrue, siVector X, ui size, short C );
overror_t  __vcuf OVCUAPI   cudaVSI_cnt_leC( ui *h_nTrue, siVector X, ui size, short C );
overror_t  __vcuf OVCUAPI   cudaVSI_cnt_ltC( ui *h_nTrue, siVector X, ui size, short C );
overror_t  __vcuf OVCUAPI   cudaVSI_cnt_geC( ui *h_nTrue, siVector X, ui size, short C );
overror_t  __vcuf OVCUAPI   cudaVSI_cnt_gtC( ui *h_nTrue, siVector X, ui size, short C );
overror_t  __vcuf OVCUAPI   cusdVSI_cnt_eqC( ui *h_nTrue, siVector X, ui size, short *d_C );
overror_t  __vcuf OVCUAPI   cusdVSI_cnt_neC( ui *h_nTrue, siVector X, ui size, short *d_C );
overror_t  __vcuf OVCUAPI   cusdVSI_cnt_leC( ui *h_nTrue, siVector X, ui size, short *d_C );
overror_t  __vcuf OVCUAPI   cusdVSI_cnt_ltC( ui *h_nTrue, siVector X, ui size, short *d_C );
overror_t  __vcuf OVCUAPI   cusdVSI_cnt_geC( ui *h_nTrue, siVector X, ui size, short *d_C );
overror_t  __vcuf OVCUAPI   cusdVSI_cnt_gtC( ui *h_nTrue, siVector X, ui size, short *d_C );

overror_t  __vcuf OVCUAPI   cudaVSI_cnt_eqV( ui *h_nTrue, siVector X, siVector Y, ui size );
overror_t  __vcuf OVCUAPI   cudaVSI_cnt_neV( ui *h_nTrue, siVector X, siVector Y, ui size );
overror_t  __vcuf OVCUAPI   cudaVSI_cnt_leV( ui *h_nTrue, siVector X, siVector Y, ui size );
overror_t  __vcuf OVCUAPI   cudaVSI_cnt_ltV( ui *h_nTrue, siVector X, siVector Y, ui size );
overror_t  __vcuf OVCUAPI   cudaVSI_cnt_geV( ui *h_nTrue, siVector X, siVector Y, ui size );
overror_t  __vcuf OVCUAPI   cudaVSI_cnt_gtV( ui *h_nTrue, siVector X, siVector Y, ui size );

overror_t  __vcuf OVCUAPI   cudaVSI_cnt_inclrange0C( ui *h_nTrue, siVector X, ui size, short C );
overror_t  __vcuf OVCUAPI   cudaVSI_cnt_exclrange0C( ui *h_nTrue, siVector X, ui size, short C );
overror_t  __vcuf OVCUAPI   cudaVSI_cnt_inclrangeCC( ui *h_nTrue, siVector X, ui size, short CLo, short CHi );
overror_t  __vcuf OVCUAPI   cudaVSI_cnt_exclrangeCC( ui *h_nTrue, siVector X, ui size, short CLo, short CHi );
overror_t  __vcuf OVCUAPI   cusdVSI_cnt_inclrange0C( ui *h_nTrue, siVector X, ui size, short *d_C );
overror_t  __vcuf OVCUAPI   cusdVSI_cnt_exclrange0C( ui *h_nTrue, siVector X, ui size, short *d_C );
overror_t  __vcuf OVCUAPI   cusdVSI_cnt_inclrangeCC( ui *h_nTrue, siVector X, ui size, short *d_CLo, short *d_CHi );
overror_t  __vcuf OVCUAPI   cusdVSI_cnt_exclrangeCC( ui *h_nTrue, siVector X, ui size, short *d_CLo, short *d_CHi );

/******************   Basic  Arithmetics   *************************/

overror_t  __vcuf OVCUAPI   cudaVSI_neg( siVector Y, siVector X, ui size );
overror_t  __vcuf OVCUAPI   cudaVSI_abs( siVector Y, siVector X, ui size );

overror_t  __vcuf OVCUAPI   cudaVSI_addC(  siVector Y, siVector X, ui size, short C );
overror_t  __vcuf OVCUAPI   cudaVSI_subC(  siVector Y, siVector X, ui size, short C );
overror_t  __vcuf OVCUAPI   cudaVSI_subrC( siVector Y, siVector X, ui size, short C );
overror_t  __vcuf OVCUAPI   cudaVSI_mulC(  siVector Y, siVector X, ui size, short C );
overror_t  __vcuf OVCUAPI   cudaVSI_divC(  siVector Y, siVector X, ui size, short C );
overror_t  __vcuf OVCUAPI   cudaVSI_divrC( siVector Y, siVector X, ui size, short C );
overror_t  __vcuf OVCUAPI   cudaVSI_modC(  siVector Y, siVector X, ui size, short C );
overror_t  __vcuf OVCUAPI   cudaVSI_maxC(  siVector Y, siVector X, ui size, short C );
overror_t  __vcuf OVCUAPI   cudaVSI_minC(  siVector Y, siVector X, ui size, short C );
overror_t  __vcuf OVCUAPI   cudaVSI_limit( siVector Y, siVector X, ui size, short Min, short Max );

overror_t  __vcuf OVCUAPI   cusdVSI_addC(  siVector Y, siVector X, ui size, short *C );
overror_t  __vcuf OVCUAPI   cusdVSI_subC(  siVector Y, siVector X, ui size, short *C );
overror_t  __vcuf OVCUAPI   cusdVSI_subrC( siVector Y, siVector X, ui size, short *C );
overror_t  __vcuf OVCUAPI   cusdVSI_mulC(  siVector Y, siVector X, ui size, short *C );
overror_t  __vcuf OVCUAPI   cusdVSI_divC(  siVector Y, siVector X, ui size, short *C );
overror_t  __vcuf OVCUAPI   cusdVSI_divrC( siVector Y, siVector X, ui size, short *C );
overror_t  __vcuf OVCUAPI   cusdVSI_modC(  siVector Y, siVector X, ui size, short *C );
overror_t  __vcuf OVCUAPI   cusdVSI_maxC(  siVector Y, siVector X, ui size, short *C );
overror_t  __vcuf OVCUAPI   cusdVSI_minC(  siVector Y, siVector X, ui size, short *C );
overror_t  __vcuf OVCUAPI   cusdVSI_limit( siVector Y, siVector X, ui size, short *Min, short *Max );

overror_t  __vcuf OVCUAPI   cudaVSI_addV(  siVector Z, siVector X, siVector Y, ui size );
overror_t  __vcuf OVCUAPI   cudaVSI_subV(  siVector Z, siVector X, siVector Y, ui size );
overror_t  __vcuf OVCUAPI   cudaVSI_subrV( siVector Z, siVector X, siVector Y, ui size );
overror_t  __vcuf OVCUAPI   cudaVSI_mulV(  siVector Z, siVector X, siVector Y, ui size );
overror_t  __vcuf OVCUAPI   cudaVSI_divV(  siVector Z, siVector X, siVector Y, ui size );
overror_t  __vcuf OVCUAPI   cudaVSI_divrV( siVector Z, siVector X, siVector Y, ui size );
overror_t  __vcuf OVCUAPI   cudaVSI_modV(  siVector Z, siVector X, siVector Y, ui size );
overror_t  __vcuf OVCUAPI   cudaVSI_maxV(  siVector Z, siVector X, siVector Y, ui size );
overror_t  __vcuf OVCUAPI   cudaVSI_minV(  siVector Z, siVector X, siVector Y, ui size );

/******************** Accumulation (Y += X) ******************************/

overror_t  __vcuf OVCUAPI  cudaVSI_accV(   siVector Y, siVector  X, ui size );
overror_t  __vcuf OVCUAPI  cudaVSI_accVBI( siVector Y, biVector  X, ui size );


/*****************   Bit-wise operations  *********************/

overror_t  __vcuf OVCUAPI   cudaVSI_shl( siVector Y, siVector X, ui size, unsigned C );
overror_t  __vcuf OVCUAPI   cudaVSI_shr( siVector Y, siVector X, ui size, unsigned C );

overror_t  __vcuf OVCUAPI   cudaVSI_and( siVector Y, siVector X, ui size, short C );
overror_t  __vcuf OVCUAPI   cudaVSI_or(  siVector Y, siVector X, ui size, short C );
overror_t  __vcuf OVCUAPI   cudaVSI_xor( siVector Y, siVector X, ui size, short C );
overror_t  __vcuf OVCUAPI   cudaVSI_not( siVector Y, siVector X, ui size );

overror_t  __vcuf OVCUAPI   cusdVSI_and( siVector Y, siVector X, ui size, short *C );
overror_t  __vcuf OVCUAPI   cusdVSI_or(  siVector Y, siVector X, ui size, short *C );
overror_t  __vcuf OVCUAPI   cusdVSI_xor( siVector Y, siVector X, ui size, short *C );

#ifdef __cplusplus
}  // end of extern "C"
#endif

/******************  VSIcu_ functions: **********************************
	act on host memory, using the CUDA device for processing
************************************************************************/


#ifdef __cplusplus
   extern "C" {
#endif

/********************  Comparisons ********************************/

void __vf OVCUAPI   VSIcu_cmp0(    siVector Y, siVector X, ui size );
ui   __vf OVCUAPI   VSIcu_cmp_eq0( siVector Y, siVector X, ui size );
ui   __vf OVCUAPI   VSIcu_cmp_ne0( siVector Y, siVector X, ui size );
ui   __vf OVCUAPI   VSIcu_cmp_le0( siVector Y, siVector X, ui size );
ui   __vf OVCUAPI   VSIcu_cmp_lt0( siVector Y, siVector X, ui size );
ui   __vf OVCUAPI   VSIcu_cmp_ge0( siVector Y, siVector X, ui size );
ui   __vf OVCUAPI   VSIcu_cmp_gt0( siVector Y, siVector X, ui size );

ui   __vf OVCUAPI   VSIcu_cnt_eq0( siVector X, ui size );
ui   __vf OVCUAPI   VSIcu_cnt_ne0( siVector X, ui size );
ui   __vf OVCUAPI   VSIcu_cnt_le0( siVector X, ui size );
ui   __vf OVCUAPI   VSIcu_cnt_lt0( siVector X, ui size );
ui   __vf OVCUAPI   VSIcu_cnt_ge0( siVector X, ui size );
ui   __vf OVCUAPI   VSIcu_cnt_gt0( siVector X, ui size );

void __vf OVCUAPI   VSIcu_cmpC(    siVector Y, siVector X, ui size, short C );
ui   __vf OVCUAPI   VSIcu_cmp_eqC( siVector Y, siVector X, ui size, short C );
ui   __vf OVCUAPI   VSIcu_cmp_neC( siVector Y, siVector X, ui size, short C );
ui   __vf OVCUAPI   VSIcu_cmp_leC( siVector Y, siVector X, ui size, short C );
ui   __vf OVCUAPI   VSIcu_cmp_ltC( siVector Y, siVector X, ui size, short C );
ui   __vf OVCUAPI   VSIcu_cmp_geC( siVector Y, siVector X, ui size, short C );
ui   __vf OVCUAPI   VSIcu_cmp_gtC( siVector Y, siVector X, ui size, short C );

ui   __vf OVCUAPI   VSIcu_cnt_eqC( siVector X, ui size, short C );
ui   __vf OVCUAPI   VSIcu_cnt_neC( siVector X, ui size, short C );
ui   __vf OVCUAPI   VSIcu_cnt_leC( siVector X, ui size, short C );
ui   __vf OVCUAPI   VSIcu_cnt_ltC( siVector X, ui size, short C );
ui   __vf OVCUAPI   VSIcu_cnt_geC( siVector X, ui size, short C );
ui   __vf OVCUAPI   VSIcu_cnt_gtC( siVector X, ui size, short C );

void __vf OVCUAPI   VSIcu_cmpV(    siVector Z, siVector X, siVector Y, ui size );
ui   __vf OVCUAPI   VSIcu_cmp_eqV( siVector Z, siVector X, siVector Y, ui size );
ui   __vf OVCUAPI   VSIcu_cmp_neV( siVector Z, siVector X, siVector Y, ui size );
ui   __vf OVCUAPI   VSIcu_cmp_leV( siVector Z, siVector X, siVector Y, ui size );
ui   __vf OVCUAPI   VSIcu_cmp_ltV( siVector Z, siVector X, siVector Y, ui size );
ui   __vf OVCUAPI   VSIcu_cmp_geV( siVector Z, siVector X, siVector Y, ui size );
ui   __vf OVCUAPI   VSIcu_cmp_gtV( siVector Z, siVector X, siVector Y, ui size );

ui   __vf OVCUAPI   VSIcu_cnt_eqV( siVector X, siVector Y, ui size );
ui   __vf OVCUAPI   VSIcu_cnt_neV( siVector X, siVector Y, ui size );
ui   __vf OVCUAPI   VSIcu_cnt_leV( siVector X, siVector Y, ui size );
ui   __vf OVCUAPI   VSIcu_cnt_ltV( siVector X, siVector Y, ui size );
ui   __vf OVCUAPI   VSIcu_cnt_geV( siVector X, siVector Y, ui size );
ui   __vf OVCUAPI   VSIcu_cnt_gtV( siVector X, siVector Y, ui size );

ui   __vf OVCUAPI   VSIcu_cmp_inclrange0C( siVector Y, siVector X, ui size, short C );
ui   __vf OVCUAPI   VSIcu_cmp_exclrange0C( siVector Y, siVector X, ui size, short C );
ui   __vf OVCUAPI   VSIcu_cmp_inclrangeCC( siVector Y, siVector X, ui size, short CLo, short CHi );
ui   __vf OVCUAPI   VSIcu_cmp_exclrangeCC( siVector Y, siVector X, ui size, short CLo, short CHi );

ui   __vf OVCUAPI   VSIcu_cnt_inclrange0C( siVector X, ui size, short C );
ui   __vf OVCUAPI   VSIcu_cnt_exclrange0C( siVector X, ui size, short C );
ui   __vf OVCUAPI   VSIcu_cnt_inclrangeCC( siVector X, ui size, short CLo, short CHi );
ui   __vf OVCUAPI   VSIcu_cnt_exclrangeCC( siVector X, ui size, short CLo, short CHi );

/******************   Basic  Arithmetics   *************************/

void  __vf OVCUAPI   VSIcu_neg( siVector Y, siVector X, ui size );
void  __vf OVCUAPI   VSIcu_abs( siVector Y, siVector X, ui size );

void  __vf OVCUAPI   VSIcu_addC(  siVector Y, siVector X, ui size, short C );
void  __vf OVCUAPI   VSIcu_subC(  siVector Y, siVector X, ui size, short C );
void  __vf OVCUAPI   VSIcu_subrC( siVector Y, siVector X, ui size, short C );
void  __vf OVCUAPI   VSIcu_mulC(  siVector Y, siVector X, ui size, short C );
void  __vf OVCUAPI   VSIcu_divC(  siVector Y, siVector X, ui size, short C );
void  __vf OVCUAPI   VSIcu_divrC( siVector Y, siVector X, ui size, short C );
void  __vf OVCUAPI   VSIcu_modC(  siVector Y, siVector X, ui size, short C );
void  __vf OVCUAPI   VSIcu_maxC(  siVector Y, siVector X, ui size, short C );
void  __vf OVCUAPI   VSIcu_minC(  siVector Y, siVector X, ui size, short C );
void  __vf OVCUAPI   VSIcu_limit( siVector Y, siVector X, ui size, short Min, short Max );

void    __vf OVCUAPI   VSIcu_addV(  siVector Z, siVector X, siVector Y, ui size );
void    __vf OVCUAPI   VSIcu_subV(  siVector Z, siVector X, siVector Y, ui size );
void    __vf OVCUAPI   VSIcu_subrV( siVector Z, siVector X, siVector Y, ui size );
void    __vf OVCUAPI   VSIcu_mulV(  siVector Z, siVector X, siVector Y, ui size );
void    __vf OVCUAPI   VSIcu_divV(  siVector Z, siVector X, siVector Y, ui size );
void    __vf OVCUAPI   VSIcu_divrV( siVector Z, siVector X, siVector Y, ui size );
void    __vf OVCUAPI   VSIcu_modV(  siVector Z, siVector X, siVector Y, ui size );
void    __vf OVCUAPI   VSIcu_maxV(  siVector Z, siVector X, siVector Y, ui size );
void    __vf OVCUAPI   VSIcu_minV(  siVector Z, siVector X, siVector Y, ui size );

/******************** Accumulation (Y += X) ******************************/

void __vf OVCUAPI  VSIcu_accV(   siVector Y, siVector  X, ui size );
void __vf OVCUAPI  VSIcu_accVBI( siVector Y, biVector  X, ui size );


/*****************   Bit-wise operations  *********************/

void    __vf OVCUAPI   VSIcu_shl( siVector Y, siVector X, ui size, unsigned C );
void    __vf OVCUAPI   VSIcu_shr( siVector Y, siVector X, ui size, unsigned C );

void    __vf OVCUAPI   VSIcu_and( siVector Y, siVector X, ui size, short C );
void    __vf OVCUAPI   VSIcu_or(  siVector Y, siVector X, ui size, short C );
void    __vf OVCUAPI   VSIcu_xor( siVector Y, siVector X, ui size, short C );
void    __vf OVCUAPI   VSIcu_not( siVector Y, siVector X, ui size );

#ifdef __cplusplus
}  // end of extern "C"
#endif

#endif   /*  __CUDAVSIMATH_H    */
