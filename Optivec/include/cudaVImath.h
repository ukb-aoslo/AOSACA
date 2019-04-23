/*  cudaVImath.h

  vector management functions for data type "int":
  integer arithmetics and mathematics.

  Copyright (c) 1996-200 by OptiCode - Dr. Martin Sander Software Dev.
  All Rights Reserved.
*/

#ifndef __CUDAVIMATH_H
#define __CUDAVIMATH_H

#if !defined( __CUDAVECLIB_H )
   #include <cudaVecLib.h>
#endif

/******************  cudaVI_ functions: **********************************
	 act on vectors in CUDA device memory; 
	 scalar parameters and return values on host
******************  cusdVI_ functions: **********************************
	 also act on vectors in CUDA device memory; 
	 scalar parameters and return values by address on device memory
************************************************************************/

#ifdef __cplusplus
   extern "C" {
#endif

/********************  Comparisons ********************************/

overror_t  __vcuf OVCUAPI   cudaVI_cmp0(    iVector Y, iVector X, ui size );
overror_t  __vcuf OVCUAPI   cudaVI_cmp_eq0( ui *h_nTrue, iVector Y, iVector X, ui size );
overror_t  __vcuf OVCUAPI   cudaVI_cmp_ne0( ui *h_nTrue, iVector Y, iVector X, ui size );
overror_t  __vcuf OVCUAPI   cudaVI_cmp_le0( ui *h_nTrue, iVector Y, iVector X, ui size );
overror_t  __vcuf OVCUAPI   cudaVI_cmp_lt0( ui *h_nTrue, iVector Y, iVector X, ui size );
overror_t  __vcuf OVCUAPI   cudaVI_cmp_ge0( ui *h_nTrue, iVector Y, iVector X, ui size );
overror_t  __vcuf OVCUAPI   cudaVI_cmp_gt0( ui *h_nTrue, iVector Y, iVector X, ui size );

overror_t  __vcuf OVCUAPI   cudaVI_cmpC(    iVector Y, iVector X, ui size, int C );
overror_t  __vcuf OVCUAPI   cudaVI_cmp_eqC( ui *h_nTrue, iVector Y, iVector X, ui size, int C );
overror_t  __vcuf OVCUAPI   cudaVI_cmp_neC( ui *h_nTrue, iVector Y, iVector X, ui size, int C );
overror_t  __vcuf OVCUAPI   cudaVI_cmp_leC( ui *h_nTrue, iVector Y, iVector X, ui size, int C );
overror_t  __vcuf OVCUAPI   cudaVI_cmp_ltC( ui *h_nTrue, iVector Y, iVector X, ui size, int C );
overror_t  __vcuf OVCUAPI   cudaVI_cmp_geC( ui *h_nTrue, iVector Y, iVector X, ui size, int C );
overror_t  __vcuf OVCUAPI   cudaVI_cmp_gtC( ui *h_nTrue, iVector Y, iVector X, ui size, int C );
overror_t  __vcuf OVCUAPI   cusdVI_cmpC(    iVector Y, iVector X, ui size, int *d_C );
overror_t  __vcuf OVCUAPI   cusdVI_cmp_eqC( ui *h_nTrue, iVector Y, iVector X, ui size, int *d_C );
overror_t  __vcuf OVCUAPI   cusdVI_cmp_neC( ui *h_nTrue, iVector Y, iVector X, ui size, int *d_C );
overror_t  __vcuf OVCUAPI   cusdVI_cmp_leC( ui *h_nTrue, iVector Y, iVector X, ui size, int *d_C );
overror_t  __vcuf OVCUAPI   cusdVI_cmp_ltC( ui *h_nTrue, iVector Y, iVector X, ui size, int *d_C );
overror_t  __vcuf OVCUAPI   cusdVI_cmp_geC( ui *h_nTrue, iVector Y, iVector X, ui size, int *d_C );
overror_t  __vcuf OVCUAPI   cusdVI_cmp_gtC( ui *h_nTrue, iVector Y, iVector X, ui size, int *d_C );

overror_t  __vcuf OVCUAPI   cudaVI_cmpV(    iVector Z, iVector X, iVector Y, ui size );
overror_t  __vcuf OVCUAPI   cudaVI_cmp_eqV( ui *h_nTrue, iVector Z, iVector X, iVector Y, ui size );
overror_t  __vcuf OVCUAPI   cudaVI_cmp_neV( ui *h_nTrue, iVector Z, iVector X, iVector Y, ui size );
overror_t  __vcuf OVCUAPI   cudaVI_cmp_leV( ui *h_nTrue, iVector Z, iVector X, iVector Y, ui size );
overror_t  __vcuf OVCUAPI   cudaVI_cmp_ltV( ui *h_nTrue, iVector Z, iVector X, iVector Y, ui size );
overror_t  __vcuf OVCUAPI   cudaVI_cmp_geV( ui *h_nTrue, iVector Z, iVector X, iVector Y, ui size );
overror_t  __vcuf OVCUAPI   cudaVI_cmp_gtV( ui *h_nTrue, iVector Z, iVector X, iVector Y, ui size );

overror_t  __vcuf OVCUAPI   cudaVI_cmp_inclrange0C( ui *h_nTrue, iVector Y, iVector X, ui size, int C );
overror_t  __vcuf OVCUAPI   cudaVI_cmp_exclrange0C( ui *h_nTrue, iVector Y, iVector X, ui size, int C );
overror_t  __vcuf OVCUAPI   cudaVI_cmp_inclrangeCC( ui *h_nTrue, iVector Y, iVector X, ui size, int CLo, int CHi );
overror_t  __vcuf OVCUAPI   cudaVI_cmp_exclrangeCC( ui *h_nTrue, iVector Y, iVector X, ui size, int CLo, int CHi );
overror_t  __vcuf OVCUAPI   cusdVI_cmp_inclrange0C( ui *h_nTrue, iVector Y, iVector X, ui size, int *d_C );
overror_t  __vcuf OVCUAPI   cusdVI_cmp_exclrange0C( ui *h_nTrue, iVector Y, iVector X, ui size, int *d_C );
overror_t  __vcuf OVCUAPI   cusdVI_cmp_inclrangeCC( ui *h_nTrue, iVector Y, iVector X, ui size, int *d_CLo, int *d_CHi );
overror_t  __vcuf OVCUAPI   cusdVI_cmp_exclrangeCC( ui *h_nTrue, iVector Y, iVector X, ui size, int *d_CLo, int *d_CHi );

overror_t  __vcuf OVCUAPI   cudaVI_cnt_eq0( ui *h_nTrue, iVector X, ui size );
overror_t  __vcuf OVCUAPI   cudaVI_cnt_ne0( ui *h_nTrue, iVector X, ui size );
overror_t  __vcuf OVCUAPI   cudaVI_cnt_le0( ui *h_nTrue, iVector X, ui size );
overror_t  __vcuf OVCUAPI   cudaVI_cnt_lt0( ui *h_nTrue, iVector X, ui size );
overror_t  __vcuf OVCUAPI   cudaVI_cnt_ge0( ui *h_nTrue, iVector X, ui size );
overror_t  __vcuf OVCUAPI   cudaVI_cnt_gt0( ui *h_nTrue, iVector X, ui size );

overror_t  __vcuf OVCUAPI   cudaVI_cnt_eqC( ui *h_nTrue, iVector X, ui size, int C );
overror_t  __vcuf OVCUAPI   cudaVI_cnt_neC( ui *h_nTrue, iVector X, ui size, int C );
overror_t  __vcuf OVCUAPI   cudaVI_cnt_leC( ui *h_nTrue, iVector X, ui size, int C );
overror_t  __vcuf OVCUAPI   cudaVI_cnt_ltC( ui *h_nTrue, iVector X, ui size, int C );
overror_t  __vcuf OVCUAPI   cudaVI_cnt_geC( ui *h_nTrue, iVector X, ui size, int C );
overror_t  __vcuf OVCUAPI   cudaVI_cnt_gtC( ui *h_nTrue, iVector X, ui size, int C );
overror_t  __vcuf OVCUAPI   cusdVI_cnt_eqC( ui *h_nTrue, iVector X, ui size, int *d_C );
overror_t  __vcuf OVCUAPI   cusdVI_cnt_neC( ui *h_nTrue, iVector X, ui size, int *d_C );
overror_t  __vcuf OVCUAPI   cusdVI_cnt_leC( ui *h_nTrue, iVector X, ui size, int *d_C );
overror_t  __vcuf OVCUAPI   cusdVI_cnt_ltC( ui *h_nTrue, iVector X, ui size, int *d_C );
overror_t  __vcuf OVCUAPI   cusdVI_cnt_geC( ui *h_nTrue, iVector X, ui size, int *d_C );
overror_t  __vcuf OVCUAPI   cusdVI_cnt_gtC( ui *h_nTrue, iVector X, ui size, int *d_C );

overror_t  __vcuf OVCUAPI   cudaVI_cnt_eqV( ui *h_nTrue, iVector X, iVector Y, ui size );
overror_t  __vcuf OVCUAPI   cudaVI_cnt_neV( ui *h_nTrue, iVector X, iVector Y, ui size );
overror_t  __vcuf OVCUAPI   cudaVI_cnt_leV( ui *h_nTrue, iVector X, iVector Y, ui size );
overror_t  __vcuf OVCUAPI   cudaVI_cnt_ltV( ui *h_nTrue, iVector X, iVector Y, ui size );
overror_t  __vcuf OVCUAPI   cudaVI_cnt_geV( ui *h_nTrue, iVector X, iVector Y, ui size );
overror_t  __vcuf OVCUAPI   cudaVI_cnt_gtV( ui *h_nTrue, iVector X, iVector Y, ui size );

overror_t  __vcuf OVCUAPI   cudaVI_cnt_inclrange0C( ui *h_nTrue, iVector X, ui size, int C );
overror_t  __vcuf OVCUAPI   cudaVI_cnt_exclrange0C( ui *h_nTrue, iVector X, ui size, int C );
overror_t  __vcuf OVCUAPI   cudaVI_cnt_inclrangeCC( ui *h_nTrue, iVector X, ui size, int CLo, int CHi );
overror_t  __vcuf OVCUAPI   cudaVI_cnt_exclrangeCC( ui *h_nTrue, iVector X, ui size, int CLo, int CHi );
overror_t  __vcuf OVCUAPI   cusdVI_cnt_inclrange0C( ui *h_nTrue, iVector X, ui size, int *d_C );
overror_t  __vcuf OVCUAPI   cusdVI_cnt_exclrange0C( ui *h_nTrue, iVector X, ui size, int *d_C );
overror_t  __vcuf OVCUAPI   cusdVI_cnt_inclrangeCC( ui *h_nTrue, iVector X, ui size, int *d_CLo, int *d_CHi );
overror_t  __vcuf OVCUAPI   cusdVI_cnt_exclrangeCC( ui *h_nTrue, iVector X, ui size, int *d_CLo, int *d_CHi );

/******************   Basic  Arithmetics   *************************/

overror_t  __vcuf OVCUAPI   cudaVI_neg( iVector Y, iVector X, ui size );
overror_t  __vcuf OVCUAPI   cudaVI_abs( iVector Y, iVector X, ui size );

overror_t  __vcuf OVCUAPI   cudaVI_addC(  iVector Y, iVector X, ui size, int C );
overror_t  __vcuf OVCUAPI   cudaVI_subC(  iVector Y, iVector X, ui size, int C );
overror_t  __vcuf OVCUAPI   cudaVI_subrC( iVector Y, iVector X, ui size, int C );
overror_t  __vcuf OVCUAPI   cudaVI_mulC(  iVector Y, iVector X, ui size, int C );
overror_t  __vcuf OVCUAPI   cudaVI_divC(  iVector Y, iVector X, ui size, int C );
overror_t  __vcuf OVCUAPI   cudaVI_divrC( iVector Y, iVector X, ui size, int C );
overror_t  __vcuf OVCUAPI   cudaVI_modC(  iVector Y, iVector X, ui size, int C );
overror_t  __vcuf OVCUAPI   cudaVI_maxC(  iVector Y, iVector X, ui size, int C );
overror_t  __vcuf OVCUAPI   cudaVI_minC(  iVector Y, iVector X, ui size, int C );
overror_t  __vcuf OVCUAPI   cudaVI_limit( iVector Y, iVector X, ui size, int Min, int Max );

overror_t  __vcuf OVCUAPI   cusdVI_addC(  iVector Y, iVector X, ui size, int *C );
overror_t  __vcuf OVCUAPI   cusdVI_subC(  iVector Y, iVector X, ui size, int *C );
overror_t  __vcuf OVCUAPI   cusdVI_subrC( iVector Y, iVector X, ui size, int *C );
overror_t  __vcuf OVCUAPI   cusdVI_mulC(  iVector Y, iVector X, ui size, int *C );
overror_t  __vcuf OVCUAPI   cusdVI_divC(  iVector Y, iVector X, ui size, int *C );
overror_t  __vcuf OVCUAPI   cusdVI_divrC( iVector Y, iVector X, ui size, int *C );
overror_t  __vcuf OVCUAPI   cusdVI_modC(  iVector Y, iVector X, ui size, int *C );
overror_t  __vcuf OVCUAPI   cusdVI_maxC(  iVector Y, iVector X, ui size, int *C );
overror_t  __vcuf OVCUAPI   cusdVI_minC(  iVector Y, iVector X, ui size, int *C );
overror_t  __vcuf OVCUAPI   cusdVI_limit( iVector Y, iVector X, ui size, int *Min, int *Max );

overror_t  __vcuf OVCUAPI   cudaVI_addV(  iVector Z, iVector X, iVector Y, ui size );
overror_t  __vcuf OVCUAPI   cudaVI_subV(  iVector Z, iVector X, iVector Y, ui size );
overror_t  __vcuf OVCUAPI   cudaVI_subrV( iVector Z, iVector X, iVector Y, ui size );
overror_t  __vcuf OVCUAPI   cudaVI_mulV(  iVector Z, iVector X, iVector Y, ui size );
overror_t  __vcuf OVCUAPI   cudaVI_divV(  iVector Z, iVector X, iVector Y, ui size );
overror_t  __vcuf OVCUAPI   cudaVI_divrV( iVector Z, iVector X, iVector Y, ui size );
overror_t  __vcuf OVCUAPI   cudaVI_modV(  iVector Z, iVector X, iVector Y, ui size );
overror_t  __vcuf OVCUAPI   cudaVI_maxV(  iVector Z, iVector X, iVector Y, ui size );
overror_t  __vcuf OVCUAPI   cudaVI_minV(  iVector Z, iVector X, iVector Y, ui size );

/******************** Accumulation (Y += X) ******************************/

overror_t  __vcuf OVCUAPI  cudaVI_accV(   iVector Y, iVector   X, ui size );
overror_t  __vcuf OVCUAPI  cudaVI_accVBI( iVector Y, biVector  X, ui size );
overror_t  __vcuf OVCUAPI  cudaVI_accVSI( iVector Y, siVector  X, ui size );

/*****************   Bit-wise operations  *********************/

overror_t  __vcuf OVCUAPI   cudaVI_shl( iVector Y, iVector X, ui size, unsigned C );
overror_t  __vcuf OVCUAPI   cudaVI_shr( iVector Y, iVector X, ui size, unsigned C );

overror_t  __vcuf OVCUAPI   cudaVI_and( iVector Y, iVector X, ui size, int C );
overror_t  __vcuf OVCUAPI   cudaVI_or(  iVector Y, iVector X, ui size, int C );
overror_t  __vcuf OVCUAPI   cudaVI_xor( iVector Y, iVector X, ui size, int C );
overror_t  __vcuf OVCUAPI   cudaVI_not( iVector Y, iVector X, ui size );

overror_t  __vcuf OVCUAPI   cusdVI_and( iVector Y, iVector X, ui size, int *C );
overror_t  __vcuf OVCUAPI   cusdVI_or(  iVector Y, iVector X, ui size, int *C );
overror_t  __vcuf OVCUAPI   cusdVI_xor( iVector Y, iVector X, ui size, int *C );

#ifdef __cplusplus
} // end of extern "C"
#endif

/******************  VIcu_ functions: **********************************
	act on host memory, using the CUDA device for processing
************************************************************************/


#ifdef __cplusplus
   extern "C" {
#endif

/********************  Comparisons ********************************/

void __vf OVCUAPI   VIcu_cmp0(    iVector Y, iVector X, ui size );
ui   __vf OVCUAPI   VIcu_cmp_eq0( iVector Y, iVector X, ui size );
ui   __vf OVCUAPI   VIcu_cmp_ne0( iVector Y, iVector X, ui size );
ui   __vf OVCUAPI   VIcu_cmp_le0( iVector Y, iVector X, ui size );
ui   __vf OVCUAPI   VIcu_cmp_lt0( iVector Y, iVector X, ui size );
ui   __vf OVCUAPI   VIcu_cmp_ge0( iVector Y, iVector X, ui size );
ui   __vf OVCUAPI   VIcu_cmp_gt0( iVector Y, iVector X, ui size );

ui   __vf OVCUAPI   VIcu_cnt_eq0( iVector X, ui size );
ui   __vf OVCUAPI   VIcu_cnt_ne0( iVector X, ui size );
ui   __vf OVCUAPI   VIcu_cnt_le0( iVector X, ui size );
ui   __vf OVCUAPI   VIcu_cnt_lt0( iVector X, ui size );
ui   __vf OVCUAPI   VIcu_cnt_ge0( iVector X, ui size );
ui   __vf OVCUAPI   VIcu_cnt_gt0( iVector X, ui size );

void __vf OVCUAPI   VIcu_cmpC(    iVector Y, iVector X, ui size, int C );
ui   __vf OVCUAPI   VIcu_cmp_eqC( iVector Y, iVector X, ui size, int C );
ui   __vf OVCUAPI   VIcu_cmp_neC( iVector Y, iVector X, ui size, int C );
ui   __vf OVCUAPI   VIcu_cmp_leC( iVector Y, iVector X, ui size, int C );
ui   __vf OVCUAPI   VIcu_cmp_ltC( iVector Y, iVector X, ui size, int C );
ui   __vf OVCUAPI   VIcu_cmp_geC( iVector Y, iVector X, ui size, int C );
ui   __vf OVCUAPI   VIcu_cmp_gtC( iVector Y, iVector X, ui size, int C );

ui   __vf OVCUAPI   VIcu_cnt_eqC( iVector X, ui size, int C );
ui   __vf OVCUAPI   VIcu_cnt_neC( iVector X, ui size, int C );
ui   __vf OVCUAPI   VIcu_cnt_leC( iVector X, ui size, int C );
ui   __vf OVCUAPI   VIcu_cnt_ltC( iVector X, ui size, int C );
ui   __vf OVCUAPI   VIcu_cnt_geC( iVector X, ui size, int C );
ui   __vf OVCUAPI   VIcu_cnt_gtC( iVector X, ui size, int C );

void __vf OVCUAPI   VIcu_cmpV(    iVector Z, iVector X, iVector Y, ui size );
ui   __vf OVCUAPI   VIcu_cmp_eqV( iVector Z, iVector X, iVector Y, ui size );
ui   __vf OVCUAPI   VIcu_cmp_neV( iVector Z, iVector X, iVector Y, ui size );
ui   __vf OVCUAPI   VIcu_cmp_leV( iVector Z, iVector X, iVector Y, ui size );
ui   __vf OVCUAPI   VIcu_cmp_ltV( iVector Z, iVector X, iVector Y, ui size );
ui   __vf OVCUAPI   VIcu_cmp_geV( iVector Z, iVector X, iVector Y, ui size );
ui   __vf OVCUAPI   VIcu_cmp_gtV( iVector Z, iVector X, iVector Y, ui size );

ui   __vf OVCUAPI   VIcu_cnt_eqV( iVector X, iVector Y, ui size );
ui   __vf OVCUAPI   VIcu_cnt_neV( iVector X, iVector Y, ui size );
ui   __vf OVCUAPI   VIcu_cnt_leV( iVector X, iVector Y, ui size );
ui   __vf OVCUAPI   VIcu_cnt_ltV( iVector X, iVector Y, ui size );
ui   __vf OVCUAPI   VIcu_cnt_geV( iVector X, iVector Y, ui size );
ui   __vf OVCUAPI   VIcu_cnt_gtV( iVector X, iVector Y, ui size );

ui   __vf OVCUAPI   VIcu_cmp_inclrange0C( iVector Y, iVector X, ui size, int C );
ui   __vf OVCUAPI   VIcu_cmp_exclrange0C( iVector Y, iVector X, ui size, int C );
ui   __vf OVCUAPI   VIcu_cmp_inclrangeCC( iVector Y, iVector X, ui size, int CLo, int CHi );
ui   __vf OVCUAPI   VIcu_cmp_exclrangeCC( iVector Y, iVector X, ui size, int CLo, int CHi );

ui   __vf OVCUAPI   VIcu_cnt_inclrange0C( iVector X, ui size, int C );
ui   __vf OVCUAPI   VIcu_cnt_exclrange0C( iVector X, ui size, int C );
ui   __vf OVCUAPI   VIcu_cnt_inclrangeCC( iVector X, ui size, int CLo, int CHi );
ui   __vf OVCUAPI   VIcu_cnt_exclrangeCC( iVector X, ui size, int CLo, int CHi );

/******************   Basic  Arithmetics   *************************/

void  __vf OVCUAPI   VIcu_neg( iVector Y, iVector X, ui size );
void  __vf OVCUAPI   VIcu_abs( iVector Y, iVector X, ui size );

void  __vf OVCUAPI   VIcu_addC(  iVector Y, iVector X, ui size, int C );
void  __vf OVCUAPI   VIcu_subC(  iVector Y, iVector X, ui size, int C );
void  __vf OVCUAPI   VIcu_subrC( iVector Y, iVector X, ui size, int C );
void  __vf OVCUAPI   VIcu_mulC(  iVector Y, iVector X, ui size, int C );
void  __vf OVCUAPI   VIcu_divC(  iVector Y, iVector X, ui size, int C );
void  __vf OVCUAPI   VIcu_divrC( iVector Y, iVector X, ui size, int C );
void  __vf OVCUAPI   VIcu_modC(  iVector Y, iVector X, ui size, int C );
void  __vf OVCUAPI   VIcu_maxC(  iVector Y, iVector X, ui size, int C );
void  __vf OVCUAPI   VIcu_minC(  iVector Y, iVector X, ui size, int C );
void  __vf OVCUAPI   VIcu_limit( iVector Y, iVector X, ui size, int Min, int Max );

void  __vf OVCUAPI   VIcu_addV(  iVector Z, iVector X, iVector Y, ui size );
void  __vf OVCUAPI   VIcu_subV(  iVector Z, iVector X, iVector Y, ui size );
void  __vf OVCUAPI   VIcu_subrV( iVector Z, iVector X, iVector Y, ui size );
void  __vf OVCUAPI   VIcu_mulV(  iVector Z, iVector X, iVector Y, ui size );
void  __vf OVCUAPI   VIcu_divV(  iVector Z, iVector X, iVector Y, ui size );
void  __vf OVCUAPI   VIcu_divrV( iVector Z, iVector X, iVector Y, ui size );
void  __vf OVCUAPI   VIcu_modV(  iVector Z, iVector X, iVector Y, ui size );
void  __vf OVCUAPI   VIcu_maxV(  iVector Z, iVector X, iVector Y, ui size );
void  __vf OVCUAPI   VIcu_minV(  iVector Z, iVector X, iVector Y, ui size );

/******************** Accumulation (Y += X) ******************************/

void __vf OVCUAPI  VIcu_accV(   iVector Y, iVector   X, ui size );
void __vf OVCUAPI  VIcu_accVBI( iVector Y, biVector  X, ui size );
void __vf OVCUAPI  VIcu_accVSI( iVector Y, siVector  X, ui size );

/*****************   Bit-wise operations  *********************/

void    __vf OVCUAPI   VIcu_shl( iVector Y, iVector X, ui size, unsigned C );
void    __vf OVCUAPI   VIcu_shr( iVector Y, iVector X, ui size, unsigned C );

void    __vf OVCUAPI   VIcu_and( iVector Y, iVector X, ui size, int C );
void    __vf OVCUAPI   VIcu_or(  iVector Y, iVector X, ui size, int C );
void    __vf OVCUAPI   VIcu_xor( iVector Y, iVector X, ui size, int C );
void    __vf OVCUAPI   VIcu_not( iVector Y, iVector X, ui size );

#ifdef __cplusplus
} // end of extern "C"
#endif

#endif   /*  __CUDAVIMATH_H    */
