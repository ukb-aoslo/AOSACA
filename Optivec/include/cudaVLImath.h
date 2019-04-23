/*  cudaVLImath.h

  vector management functions for data type "long":
  integer arithmetics and mathematics.

  Copyright (c) 1996-2017 by OptiCode - Dr. Martin Sander Software Dev.
  All Rights Reserved.
*/

#ifndef __CUDAVLIMATH_H
#define __CUDAVLIMATH_H

#if !defined( __CUDAVECLIB_H )
   #include <cudaVecLib.h>
#endif

/******************  cudaVLI_ functions: **********************************
	 act on vectors in CUDA device memory; 
	 scalar parameters and return values on host
******************  cusdVLI_ functions: **********************************
	 also act on vectors in CUDA device memory; 
	 scalar parameters and return values by address on device memory
************************************************************************/

#ifdef __cplusplus
   extern "C" {
#endif

/********************  Comparisons ********************************/

overror_t  __vcuf OVCUAPI   cudaVLI_cmp0(    liVector Y, liVector X, ui size );
overror_t  __vcuf OVCUAPI   cudaVLI_cmp_eq0( ui *h_nTrue, liVector Y, liVector X, ui size );
overror_t  __vcuf OVCUAPI   cudaVLI_cmp_ne0( ui *h_nTrue, liVector Y, liVector X, ui size );
overror_t  __vcuf OVCUAPI   cudaVLI_cmp_le0( ui *h_nTrue, liVector Y, liVector X, ui size );
overror_t  __vcuf OVCUAPI   cudaVLI_cmp_lt0( ui *h_nTrue, liVector Y, liVector X, ui size );
overror_t  __vcuf OVCUAPI   cudaVLI_cmp_ge0( ui *h_nTrue, liVector Y, liVector X, ui size );
overror_t  __vcuf OVCUAPI   cudaVLI_cmp_gt0( ui *h_nTrue, liVector Y, liVector X, ui size );

overror_t  __vcuf OVCUAPI   cudaVLI_cmpC(    liVector Y, liVector X, ui size, long C );
overror_t  __vcuf OVCUAPI   cudaVLI_cmp_eqC( ui *h_nTrue, liVector Y, liVector X, ui size, long C );
overror_t  __vcuf OVCUAPI   cudaVLI_cmp_neC( ui *h_nTrue, liVector Y, liVector X, ui size, long C );
overror_t  __vcuf OVCUAPI   cudaVLI_cmp_leC( ui *h_nTrue, liVector Y, liVector X, ui size, long C );
overror_t  __vcuf OVCUAPI   cudaVLI_cmp_ltC( ui *h_nTrue, liVector Y, liVector X, ui size, long C );
overror_t  __vcuf OVCUAPI   cudaVLI_cmp_geC( ui *h_nTrue, liVector Y, liVector X, ui size, long C );
overror_t  __vcuf OVCUAPI   cudaVLI_cmp_gtC( ui *h_nTrue, liVector Y, liVector X, ui size, long C );
overror_t  __vcuf OVCUAPI   cusdVLI_cmpC(    liVector Y, liVector X, ui size, long *d_C );
overror_t  __vcuf OVCUAPI   cusdVLI_cmp_eqC( ui *h_nTrue, liVector Y, liVector X, ui size, long *d_C );
overror_t  __vcuf OVCUAPI   cusdVLI_cmp_neC( ui *h_nTrue, liVector Y, liVector X, ui size, long *d_C );
overror_t  __vcuf OVCUAPI   cusdVLI_cmp_leC( ui *h_nTrue, liVector Y, liVector X, ui size, long *d_C );
overror_t  __vcuf OVCUAPI   cusdVLI_cmp_ltC( ui *h_nTrue, liVector Y, liVector X, ui size, long *d_C );
overror_t  __vcuf OVCUAPI   cusdVLI_cmp_geC( ui *h_nTrue, liVector Y, liVector X, ui size, long *d_C );
overror_t  __vcuf OVCUAPI   cusdVLI_cmp_gtC( ui *h_nTrue, liVector Y, liVector X, ui size, long *d_C );

overror_t  __vcuf OVCUAPI   cudaVLI_cmpV(    liVector Z, liVector X, liVector Y, ui size );
overror_t  __vcuf OVCUAPI   cudaVLI_cmp_eqV( ui *h_nTrue, liVector Z, liVector X, liVector Y, ui size );
overror_t  __vcuf OVCUAPI   cudaVLI_cmp_neV( ui *h_nTrue, liVector Z, liVector X, liVector Y, ui size );
overror_t  __vcuf OVCUAPI   cudaVLI_cmp_leV( ui *h_nTrue, liVector Z, liVector X, liVector Y, ui size );
overror_t  __vcuf OVCUAPI   cudaVLI_cmp_ltV( ui *h_nTrue, liVector Z, liVector X, liVector Y, ui size );
overror_t  __vcuf OVCUAPI   cudaVLI_cmp_geV( ui *h_nTrue, liVector Z, liVector X, liVector Y, ui size );
overror_t  __vcuf OVCUAPI   cudaVLI_cmp_gtV( ui *h_nTrue, liVector Z, liVector X, liVector Y, ui size );

overror_t  __vcuf OVCUAPI   cudaVLI_cmp_inclrange0C( ui *h_nTrue, liVector Y, liVector X, ui size, long C );
overror_t  __vcuf OVCUAPI   cudaVLI_cmp_exclrange0C( ui *h_nTrue, liVector Y, liVector X, ui size, long C );
overror_t  __vcuf OVCUAPI   cudaVLI_cmp_inclrangeCC( ui *h_nTrue, liVector Y, liVector X, ui size, long CLo, long CHi );
overror_t  __vcuf OVCUAPI   cudaVLI_cmp_exclrangeCC( ui *h_nTrue, liVector Y, liVector X, ui size, long CLo, long CHi );
overror_t  __vcuf OVCUAPI   cusdVLI_cmp_inclrange0C( ui *h_nTrue, liVector Y, liVector X, ui size, long *d_C );
overror_t  __vcuf OVCUAPI   cusdVLI_cmp_exclrange0C( ui *h_nTrue, liVector Y, liVector X, ui size, long *d_C );
overror_t  __vcuf OVCUAPI   cusdVLI_cmp_inclrangeCC( ui *h_nTrue, liVector Y, liVector X, ui size, long *d_CLo, long *d_CHi );
overror_t  __vcuf OVCUAPI   cusdVLI_cmp_exclrangeCC( ui *h_nTrue, liVector Y, liVector X, ui size, long *d_CLo, long *d_CHi );

overror_t  __vcuf OVCUAPI   cudaVLI_cnt_eq0( ui *h_nTrue, liVector X, ui size );
overror_t  __vcuf OVCUAPI   cudaVLI_cnt_ne0( ui *h_nTrue, liVector X, ui size );
overror_t  __vcuf OVCUAPI   cudaVLI_cnt_le0( ui *h_nTrue, liVector X, ui size );
overror_t  __vcuf OVCUAPI   cudaVLI_cnt_lt0( ui *h_nTrue, liVector X, ui size );
overror_t  __vcuf OVCUAPI   cudaVLI_cnt_ge0( ui *h_nTrue, liVector X, ui size );
overror_t  __vcuf OVCUAPI   cudaVLI_cnt_gt0( ui *h_nTrue, liVector X, ui size );

overror_t  __vcuf OVCUAPI   cudaVLI_cnt_eqC( ui *h_nTrue, liVector X, ui size, long C );
overror_t  __vcuf OVCUAPI   cudaVLI_cnt_neC( ui *h_nTrue, liVector X, ui size, long C );
overror_t  __vcuf OVCUAPI   cudaVLI_cnt_leC( ui *h_nTrue, liVector X, ui size, long C );
overror_t  __vcuf OVCUAPI   cudaVLI_cnt_ltC( ui *h_nTrue, liVector X, ui size, long C );
overror_t  __vcuf OVCUAPI   cudaVLI_cnt_geC( ui *h_nTrue, liVector X, ui size, long C );
overror_t  __vcuf OVCUAPI   cudaVLI_cnt_gtC( ui *h_nTrue, liVector X, ui size, long C );
overror_t  __vcuf OVCUAPI   cusdVLI_cnt_eqC( ui *h_nTrue, liVector X, ui size, long *d_C );
overror_t  __vcuf OVCUAPI   cusdVLI_cnt_neC( ui *h_nTrue, liVector X, ui size, long *d_C );
overror_t  __vcuf OVCUAPI   cusdVLI_cnt_leC( ui *h_nTrue, liVector X, ui size, long *d_C );
overror_t  __vcuf OVCUAPI   cusdVLI_cnt_ltC( ui *h_nTrue, liVector X, ui size, long *d_C );
overror_t  __vcuf OVCUAPI   cusdVLI_cnt_geC( ui *h_nTrue, liVector X, ui size, long *d_C );
overror_t  __vcuf OVCUAPI   cusdVLI_cnt_gtC( ui *h_nTrue, liVector X, ui size, long *d_C );

overror_t  __vcuf OVCUAPI   cudaVLI_cnt_eqV( ui *h_nTrue, liVector X, liVector Y, ui size );
overror_t  __vcuf OVCUAPI   cudaVLI_cnt_neV( ui *h_nTrue, liVector X, liVector Y, ui size );
overror_t  __vcuf OVCUAPI   cudaVLI_cnt_leV( ui *h_nTrue, liVector X, liVector Y, ui size );
overror_t  __vcuf OVCUAPI   cudaVLI_cnt_ltV( ui *h_nTrue, liVector X, liVector Y, ui size );
overror_t  __vcuf OVCUAPI   cudaVLI_cnt_geV( ui *h_nTrue, liVector X, liVector Y, ui size );
overror_t  __vcuf OVCUAPI   cudaVLI_cnt_gtV( ui *h_nTrue, liVector X, liVector Y, ui size );

overror_t  __vcuf OVCUAPI   cudaVLI_cnt_inclrange0C( ui *h_nTrue, liVector X, ui size, long C );
overror_t  __vcuf OVCUAPI   cudaVLI_cnt_exclrange0C( ui *h_nTrue, liVector X, ui size, long C );
overror_t  __vcuf OVCUAPI   cudaVLI_cnt_inclrangeCC( ui *h_nTrue, liVector X, ui size, long CLo, long CHi );
overror_t  __vcuf OVCUAPI   cudaVLI_cnt_exclrangeCC( ui *h_nTrue, liVector X, ui size, long CLo, long CHi );
overror_t  __vcuf OVCUAPI   cusdVLI_cnt_inclrange0C( ui *h_nTrue, liVector X, ui size, long *d_C );
overror_t  __vcuf OVCUAPI   cusdVLI_cnt_exclrange0C( ui *h_nTrue, liVector X, ui size, long *d_C );
overror_t  __vcuf OVCUAPI   cusdVLI_cnt_inclrangeCC( ui *h_nTrue, liVector X, ui size, long *d_CLo, long *d_CHi );
overror_t  __vcuf OVCUAPI   cusdVLI_cnt_exclrangeCC( ui *h_nTrue, liVector X, ui size, long *d_CLo, long *d_CHi );

/******************   Basic  Arithmetics   *************************/

overror_t  __vcuf OVCUAPI   cudaVLI_neg( liVector Y, liVector X, ui size );
overror_t  __vcuf OVCUAPI   cudaVLI_abs( liVector Y, liVector X, ui size );

overror_t  __vcuf OVCUAPI   cudaVLI_addC(  liVector Y, liVector X, ui size, long C );
overror_t  __vcuf OVCUAPI   cudaVLI_subC(  liVector Y, liVector X, ui size, long C );
overror_t  __vcuf OVCUAPI   cudaVLI_subrC( liVector Y, liVector X, ui size, long C );
overror_t  __vcuf OVCUAPI   cudaVLI_mulC(  liVector Y, liVector X, ui size, long C );
overror_t  __vcuf OVCUAPI   cudaVLI_divC(  liVector Y, liVector X, ui size, long C );
overror_t  __vcuf OVCUAPI   cudaVLI_divrC( liVector Y, liVector X, ui size, long C );
overror_t  __vcuf OVCUAPI   cudaVLI_modC(  liVector Y, liVector X, ui size, long C );
overror_t  __vcuf OVCUAPI   cudaVLI_maxC(  liVector Y, liVector X, ui size, long C );
overror_t  __vcuf OVCUAPI   cudaVLI_minC(  liVector Y, liVector X, ui size, long C );
overror_t  __vcuf OVCUAPI   cudaVLI_limit( liVector Y, liVector X, ui size, long Min, long Max );

overror_t  __vcuf OVCUAPI   cusdVLI_addC(  liVector Y, liVector X, ui size, long *C );
overror_t  __vcuf OVCUAPI   cusdVLI_subC(  liVector Y, liVector X, ui size, long *C );
overror_t  __vcuf OVCUAPI   cusdVLI_subrC( liVector Y, liVector X, ui size, long *C );
overror_t  __vcuf OVCUAPI   cusdVLI_mulC(  liVector Y, liVector X, ui size, long *C );
overror_t  __vcuf OVCUAPI   cusdVLI_divC(  liVector Y, liVector X, ui size, long *C );
overror_t  __vcuf OVCUAPI   cusdVLI_divrC( liVector Y, liVector X, ui size, long *C );
overror_t  __vcuf OVCUAPI   cusdVLI_modC(  liVector Y, liVector X, ui size, long *C );
overror_t  __vcuf OVCUAPI   cusdVLI_maxC(  liVector Y, liVector X, ui size, long *C );
overror_t  __vcuf OVCUAPI   cusdVLI_minC(  liVector Y, liVector X, ui size, long *C );
overror_t  __vcuf OVCUAPI   cusdVLI_limit( liVector Y, liVector X, ui size, long *Min, long *Max );

overror_t  __vcuf OVCUAPI   cudaVLI_addV(  liVector Z, liVector X, liVector Y, ui size );
overror_t  __vcuf OVCUAPI   cudaVLI_subV(  liVector Z, liVector X, liVector Y, ui size );
overror_t  __vcuf OVCUAPI   cudaVLI_subrV( liVector Z, liVector X, liVector Y, ui size );
overror_t  __vcuf OVCUAPI   cudaVLI_mulV(  liVector Z, liVector X, liVector Y, ui size );
overror_t  __vcuf OVCUAPI   cudaVLI_divV(  liVector Z, liVector X, liVector Y, ui size );
overror_t  __vcuf OVCUAPI   cudaVLI_divrV( liVector Z, liVector X, liVector Y, ui size );
overror_t  __vcuf OVCUAPI   cudaVLI_modV(  liVector Z, liVector X, liVector Y, ui size );
overror_t  __vcuf OVCUAPI   cudaVLI_maxV(  liVector Z, liVector X, liVector Y, ui size );
overror_t  __vcuf OVCUAPI   cudaVLI_minV(  liVector Z, liVector X, liVector Y, ui size );

/******************** Accumulation (Y += X) ******************************/

overror_t  __vcuf OVCUAPI  cudaVLI_accV(   liVector Y, liVector  X, ui size );
overror_t  __vcuf OVCUAPI  cudaVLI_accVBI( liVector Y, biVector  X, ui size );
overror_t  __vcuf OVCUAPI  cudaVLI_accVSI( liVector Y, siVector  X, ui size );
overror_t  __vcuf OVCUAPI  cudaVLI_accVI(  liVector Y, iVector   X, ui size );

/*****************   Bit-wise operations  *********************/

overror_t  __vcuf OVCUAPI   cudaVLI_shl( liVector Y, liVector X, ui size, unsigned C );
overror_t  __vcuf OVCUAPI   cudaVLI_shr( liVector Y, liVector X, ui size, unsigned C );

overror_t  __vcuf OVCUAPI   cudaVLI_and( liVector Y, liVector X, ui size, long C );
overror_t  __vcuf OVCUAPI   cudaVLI_or(  liVector Y, liVector X, ui size, long C );
overror_t  __vcuf OVCUAPI   cudaVLI_xor( liVector Y, liVector X, ui size, long C );
overror_t  __vcuf OVCUAPI   cudaVLI_not( liVector Y, liVector X, ui size );

overror_t  __vcuf OVCUAPI   cusdVLI_and( liVector Y, liVector X, ui size, long *C );
overror_t  __vcuf OVCUAPI   cusdVLI_or(  liVector Y, liVector X, ui size, long *C );
overror_t  __vcuf OVCUAPI   cusdVLI_xor( liVector Y, liVector X, ui size, long *C );

#ifdef __cplusplus
}  // end of extern "C"
#endif

/******************  VLIcu_ functions: **********************************
	act on host memory, using the CUDA device for processing
************************************************************************/


#ifdef __cplusplus
   extern "C" {
#endif

/********************  Comparisons ********************************/

void __vf OVCUAPI   VLIcu_cmp0(    liVector Y, liVector X, ui size );
ui   __vf OVCUAPI   VLIcu_cmp_eq0( liVector Y, liVector X, ui size );
ui   __vf OVCUAPI   VLIcu_cmp_ne0( liVector Y, liVector X, ui size );
ui   __vf OVCUAPI   VLIcu_cmp_le0( liVector Y, liVector X, ui size );
ui   __vf OVCUAPI   VLIcu_cmp_lt0( liVector Y, liVector X, ui size );
ui   __vf OVCUAPI   VLIcu_cmp_ge0( liVector Y, liVector X, ui size );
ui   __vf OVCUAPI   VLIcu_cmp_gt0( liVector Y, liVector X, ui size );

ui   __vf OVCUAPI   VLIcu_cnt_eq0( liVector X, ui size );
ui   __vf OVCUAPI   VLIcu_cnt_ne0( liVector X, ui size );
ui   __vf OVCUAPI   VLIcu_cnt_le0( liVector X, ui size );
ui   __vf OVCUAPI   VLIcu_cnt_lt0( liVector X, ui size );
ui   __vf OVCUAPI   VLIcu_cnt_ge0( liVector X, ui size );
ui   __vf OVCUAPI   VLIcu_cnt_gt0( liVector X, ui size );

void __vf OVCUAPI   VLIcu_cmpC(    liVector Y, liVector X, ui size, long C );
ui   __vf OVCUAPI   VLIcu_cmp_eqC( liVector Y, liVector X, ui size, long C );
ui   __vf OVCUAPI   VLIcu_cmp_neC( liVector Y, liVector X, ui size, long C );
ui   __vf OVCUAPI   VLIcu_cmp_leC( liVector Y, liVector X, ui size, long C );
ui   __vf OVCUAPI   VLIcu_cmp_ltC( liVector Y, liVector X, ui size, long C );
ui   __vf OVCUAPI   VLIcu_cmp_geC( liVector Y, liVector X, ui size, long C );
ui   __vf OVCUAPI   VLIcu_cmp_gtC( liVector Y, liVector X, ui size, long C );

ui   __vf OVCUAPI   VLIcu_cnt_eqC( liVector X, ui size, long C );
ui   __vf OVCUAPI   VLIcu_cnt_neC( liVector X, ui size, long C );
ui   __vf OVCUAPI   VLIcu_cnt_leC( liVector X, ui size, long C );
ui   __vf OVCUAPI   VLIcu_cnt_ltC( liVector X, ui size, long C );
ui   __vf OVCUAPI   VLIcu_cnt_geC( liVector X, ui size, long C );
ui   __vf OVCUAPI   VLIcu_cnt_gtC( liVector X, ui size, long C );

void __vf OVCUAPI   VLIcu_cmpV(    liVector Z, liVector X, liVector Y, ui size );
ui   __vf OVCUAPI   VLIcu_cmp_eqV( liVector Z, liVector X, liVector Y, ui size );
ui   __vf OVCUAPI   VLIcu_cmp_neV( liVector Z, liVector X, liVector Y, ui size );
ui   __vf OVCUAPI   VLIcu_cmp_leV( liVector Z, liVector X, liVector Y, ui size );
ui   __vf OVCUAPI   VLIcu_cmp_ltV( liVector Z, liVector X, liVector Y, ui size );
ui   __vf OVCUAPI   VLIcu_cmp_geV( liVector Z, liVector X, liVector Y, ui size );
ui   __vf OVCUAPI   VLIcu_cmp_gtV( liVector Z, liVector X, liVector Y, ui size );

ui   __vf OVCUAPI   VLIcu_cnt_eqV( liVector X, liVector Y, ui size );
ui   __vf OVCUAPI   VLIcu_cnt_neV( liVector X, liVector Y, ui size );
ui   __vf OVCUAPI   VLIcu_cnt_leV( liVector X, liVector Y, ui size );
ui   __vf OVCUAPI   VLIcu_cnt_ltV( liVector X, liVector Y, ui size );
ui   __vf OVCUAPI   VLIcu_cnt_geV( liVector X, liVector Y, ui size );
ui   __vf OVCUAPI   VLIcu_cnt_gtV( liVector X, liVector Y, ui size );

ui   __vf OVCUAPI   VLIcu_cmp_inclrange0C( liVector Y, liVector X, ui size, long C );
ui   __vf OVCUAPI   VLIcu_cmp_exclrange0C( liVector Y, liVector X, ui size, long C );
ui   __vf OVCUAPI   VLIcu_cmp_inclrangeCC( liVector Y, liVector X, ui size, long CLo, long CHi );
ui   __vf OVCUAPI   VLIcu_cmp_exclrangeCC( liVector Y, liVector X, ui size, long CLo, long CHi );

ui   __vf OVCUAPI   VLIcu_cnt_inclrange0C( liVector X, ui size, long C );
ui   __vf OVCUAPI   VLIcu_cnt_exclrange0C( liVector X, ui size, long C );
ui   __vf OVCUAPI   VLIcu_cnt_inclrangeCC( liVector X, ui size, long CLo, long CHi );
ui   __vf OVCUAPI   VLIcu_cnt_exclrangeCC( liVector X, ui size, long CLo, long CHi );

/******************   Basic  Arithmetics   *************************/

void  __vf OVCUAPI   VLIcu_neg( liVector Y, liVector X, ui size );
void  __vf OVCUAPI   VLIcu_abs( liVector Y, liVector X, ui size );

void  __vf OVCUAPI   VLIcu_addC(  liVector Y, liVector X, ui size, long C );
void  __vf OVCUAPI   VLIcu_subC(  liVector Y, liVector X, ui size, long C );
void  __vf OVCUAPI   VLIcu_subrC( liVector Y, liVector X, ui size, long C );
void  __vf OVCUAPI   VLIcu_mulC(  liVector Y, liVector X, ui size, long C );
void  __vf OVCUAPI   VLIcu_divC(  liVector Y, liVector X, ui size, long C );
void  __vf OVCUAPI   VLIcu_divrC( liVector Y, liVector X, ui size, long C );
void  __vf OVCUAPI   VLIcu_modC(  liVector Y, liVector X, ui size, long C );
void  __vf OVCUAPI   VLIcu_maxC(  liVector Y, liVector X, ui size, long C );
void  __vf OVCUAPI   VLIcu_minC(  liVector Y, liVector X, ui size, long C );
void  __vf OVCUAPI   VLIcu_limit( liVector Y, liVector X, ui size, long Min, long Max );

void  __vf OVCUAPI   VLIcu_addV(  liVector Z, liVector X, liVector Y, ui size );
void  __vf OVCUAPI   VLIcu_subV(  liVector Z, liVector X, liVector Y, ui size );
void  __vf OVCUAPI   VLIcu_subrV( liVector Z, liVector X, liVector Y, ui size );
void  __vf OVCUAPI   VLIcu_mulV(  liVector Z, liVector X, liVector Y, ui size );
void  __vf OVCUAPI   VLIcu_divV(  liVector Z, liVector X, liVector Y, ui size );
void  __vf OVCUAPI   VLIcu_divrV( liVector Z, liVector X, liVector Y, ui size );
void  __vf OVCUAPI   VLIcu_modV(  liVector Z, liVector X, liVector Y, ui size );
void  __vf OVCUAPI   VLIcu_maxV(  liVector Z, liVector X, liVector Y, ui size );
void  __vf OVCUAPI   VLIcu_minV(  liVector Z, liVector X, liVector Y, ui size );

/******************** Accumulation (Y += X) ******************************/

void __vf OVCUAPI  VLIcu_accV(   liVector Y, liVector  X, ui size );
void __vf OVCUAPI  VLIcu_accVBI( liVector Y, biVector  X, ui size );
void __vf OVCUAPI  VLIcu_accVSI( liVector Y, siVector  X, ui size );
void __vf OVCUAPI  VLIcu_accVI(  liVector Y, iVector   X, ui size );

/*****************   Bit-wise operations  *********************/

void    __vf OVCUAPI   VLIcu_shl( liVector Y, liVector X, ui size, unsigned C );
void    __vf OVCUAPI   VLIcu_shr( liVector Y, liVector X, ui size, unsigned C );

void    __vf OVCUAPI   VLIcu_and( liVector Y, liVector X, ui size, long C );
void    __vf OVCUAPI   VLIcu_or(  liVector Y, liVector X, ui size, long C );
void    __vf OVCUAPI   VLIcu_xor( liVector Y, liVector X, ui size, long C );
void    __vf OVCUAPI   VLIcu_not( liVector Y, liVector X, ui size );

#ifdef __cplusplus
}  // end of extern "C"
#endif

#endif   /*  __CUDAVLIMATH_H    */
