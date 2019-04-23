/*  cudaVBImath.h

  vector management functions for byte-size integers:
  integer arithmetics and mathematics.

  Copyright (c) 1996-2017 by OptiCode - Dr. Martin Sander Software Dev.
  All Rights Reserved.
*/

#ifndef __CUDAVBIMATH_H
#define __CUDAVBIMATH_H

#if !defined( __CUDAVECLIB_H )
   #include <cudaVecLib.h>
#endif

/******************  cudaVBI_ functions: **********************************
	 act on vectors in CUDA device memory; 
	 scalar parameters and return values on host
******************  cusdVBI_ functions: **********************************
	 also act on vectors in CUDA device memory; 
	 scalar parameters and return values by address on device memory
************************************************************************/

#ifdef __cplusplus
   extern "C" {
#endif

/********************  Comparisons ********************************/

overror_t  __vcuf OVCUAPI   cudaVBI_cmp0(    biVector Y, biVector X, ui size );
overror_t  __vcuf OVCUAPI   cudaVBI_cmp_eq0( ui *h_nTrue, biVector Y, biVector X, ui size );
overror_t  __vcuf OVCUAPI   cudaVBI_cmp_ne0( ui *h_nTrue, biVector Y, biVector X, ui size );
overror_t  __vcuf OVCUAPI   cudaVBI_cmp_le0( ui *h_nTrue, biVector Y, biVector X, ui size );
overror_t  __vcuf OVCUAPI   cudaVBI_cmp_lt0( ui *h_nTrue, biVector Y, biVector X, ui size );
overror_t  __vcuf OVCUAPI   cudaVBI_cmp_ge0( ui *h_nTrue, biVector Y, biVector X, ui size );
overror_t  __vcuf OVCUAPI   cudaVBI_cmp_gt0( ui *h_nTrue, biVector Y, biVector X, ui size );

overror_t  __vcuf OVCUAPI   cudaVBI_cmpC(    biVector Y, biVector X, ui size, char C );
overror_t  __vcuf OVCUAPI   cudaVBI_cmp_eqC( ui *h_nTrue, biVector Y, biVector X, ui size, char C );
overror_t  __vcuf OVCUAPI   cudaVBI_cmp_neC( ui *h_nTrue, biVector Y, biVector X, ui size, char C );
overror_t  __vcuf OVCUAPI   cudaVBI_cmp_leC( ui *h_nTrue, biVector Y, biVector X, ui size, char C );
overror_t  __vcuf OVCUAPI   cudaVBI_cmp_ltC( ui *h_nTrue, biVector Y, biVector X, ui size, char C );
overror_t  __vcuf OVCUAPI   cudaVBI_cmp_geC( ui *h_nTrue, biVector Y, biVector X, ui size, char C );
overror_t  __vcuf OVCUAPI   cudaVBI_cmp_gtC( ui *h_nTrue, biVector Y, biVector X, ui size, char C );
overror_t  __vcuf OVCUAPI   cusdVBI_cmpC(    biVector Y, biVector X, ui size, char *d_C );
overror_t  __vcuf OVCUAPI   cusdVBI_cmp_eqC( ui *h_nTrue, biVector Y, biVector X, ui size, char *d_C );
overror_t  __vcuf OVCUAPI   cusdVBI_cmp_neC( ui *h_nTrue, biVector Y, biVector X, ui size, char *d_C );
overror_t  __vcuf OVCUAPI   cusdVBI_cmp_leC( ui *h_nTrue, biVector Y, biVector X, ui size, char *d_C );
overror_t  __vcuf OVCUAPI   cusdVBI_cmp_ltC( ui *h_nTrue, biVector Y, biVector X, ui size, char *d_C );
overror_t  __vcuf OVCUAPI   cusdVBI_cmp_geC( ui *h_nTrue, biVector Y, biVector X, ui size, char *d_C );
overror_t  __vcuf OVCUAPI   cusdVBI_cmp_gtC( ui *h_nTrue, biVector Y, biVector X, ui size, char *d_C );

overror_t  __vcuf OVCUAPI   cudaVBI_cmpV(    biVector Z, biVector X, biVector Y, ui size );
overror_t  __vcuf OVCUAPI   cudaVBI_cmp_eqV( ui *h_nTrue, biVector Z, biVector X, biVector Y, ui size );
overror_t  __vcuf OVCUAPI   cudaVBI_cmp_neV( ui *h_nTrue, biVector Z, biVector X, biVector Y, ui size );
overror_t  __vcuf OVCUAPI   cudaVBI_cmp_leV( ui *h_nTrue, biVector Z, biVector X, biVector Y, ui size );
overror_t  __vcuf OVCUAPI   cudaVBI_cmp_ltV( ui *h_nTrue, biVector Z, biVector X, biVector Y, ui size );
overror_t  __vcuf OVCUAPI   cudaVBI_cmp_geV( ui *h_nTrue, biVector Z, biVector X, biVector Y, ui size );
overror_t  __vcuf OVCUAPI   cudaVBI_cmp_gtV( ui *h_nTrue, biVector Z, biVector X, biVector Y, ui size );

overror_t  __vcuf OVCUAPI   cudaVBI_cmp_inclrange0C( ui *h_nTrue, biVector Y, biVector X, ui size, char C );
overror_t  __vcuf OVCUAPI   cudaVBI_cmp_exclrange0C( ui *h_nTrue, biVector Y, biVector X, ui size, char C );
overror_t  __vcuf OVCUAPI   cudaVBI_cmp_inclrangeCC( ui *h_nTrue, biVector Y, biVector X, ui size, char CLo, char CHi );
overror_t  __vcuf OVCUAPI   cudaVBI_cmp_exclrangeCC( ui *h_nTrue, biVector Y, biVector X, ui size, char CLo, char CHi );
overror_t  __vcuf OVCUAPI   cusdVBI_cmp_inclrange0C( ui *h_nTrue, biVector Y, biVector X, ui size, char *d_C );
overror_t  __vcuf OVCUAPI   cusdVBI_cmp_exclrange0C( ui *h_nTrue, biVector Y, biVector X, ui size, char *d_C );
overror_t  __vcuf OVCUAPI   cusdVBI_cmp_inclrangeCC( ui *h_nTrue, biVector Y, biVector X, ui size, char *d_CLo, char *d_CHi );
overror_t  __vcuf OVCUAPI   cusdVBI_cmp_exclrangeCC( ui *h_nTrue, biVector Y, biVector X, ui size, char *d_CLo, char *d_CHi );

overror_t  __vcuf OVCUAPI   cudaVBI_cnt_eq0( ui *h_nTrue, biVector X, ui size );
overror_t  __vcuf OVCUAPI   cudaVBI_cnt_ne0( ui *h_nTrue, biVector X, ui size );
overror_t  __vcuf OVCUAPI   cudaVBI_cnt_le0( ui *h_nTrue, biVector X, ui size );
overror_t  __vcuf OVCUAPI   cudaVBI_cnt_lt0( ui *h_nTrue, biVector X, ui size );
overror_t  __vcuf OVCUAPI   cudaVBI_cnt_ge0( ui *h_nTrue, biVector X, ui size );
overror_t  __vcuf OVCUAPI   cudaVBI_cnt_gt0( ui *h_nTrue, biVector X, ui size );

overror_t  __vcuf OVCUAPI   cudaVBI_cnt_eqC( ui *h_nTrue, biVector X, ui size, char C );
overror_t  __vcuf OVCUAPI   cudaVBI_cnt_neC( ui *h_nTrue, biVector X, ui size, char C );
overror_t  __vcuf OVCUAPI   cudaVBI_cnt_leC( ui *h_nTrue, biVector X, ui size, char C );
overror_t  __vcuf OVCUAPI   cudaVBI_cnt_ltC( ui *h_nTrue, biVector X, ui size, char C );
overror_t  __vcuf OVCUAPI   cudaVBI_cnt_geC( ui *h_nTrue, biVector X, ui size, char C );
overror_t  __vcuf OVCUAPI   cudaVBI_cnt_gtC( ui *h_nTrue, biVector X, ui size, char C );
overror_t  __vcuf OVCUAPI   cusdVBI_cnt_eqC( ui *h_nTrue, biVector X, ui size, char *d_C );
overror_t  __vcuf OVCUAPI   cusdVBI_cnt_neC( ui *h_nTrue, biVector X, ui size, char *d_C );
overror_t  __vcuf OVCUAPI   cusdVBI_cnt_leC( ui *h_nTrue, biVector X, ui size, char *d_C );
overror_t  __vcuf OVCUAPI   cusdVBI_cnt_ltC( ui *h_nTrue, biVector X, ui size, char *d_C );
overror_t  __vcuf OVCUAPI   cusdVBI_cnt_geC( ui *h_nTrue, biVector X, ui size, char *d_C );
overror_t  __vcuf OVCUAPI   cusdVBI_cnt_gtC( ui *h_nTrue, biVector X, ui size, char *d_C );

overror_t  __vcuf OVCUAPI   cudaVBI_cnt_eqV( ui *h_nTrue, biVector X, biVector Y, ui size );
overror_t  __vcuf OVCUAPI   cudaVBI_cnt_neV( ui *h_nTrue, biVector X, biVector Y, ui size );
overror_t  __vcuf OVCUAPI   cudaVBI_cnt_leV( ui *h_nTrue, biVector X, biVector Y, ui size );
overror_t  __vcuf OVCUAPI   cudaVBI_cnt_ltV( ui *h_nTrue, biVector X, biVector Y, ui size );
overror_t  __vcuf OVCUAPI   cudaVBI_cnt_geV( ui *h_nTrue, biVector X, biVector Y, ui size );
overror_t  __vcuf OVCUAPI   cudaVBI_cnt_gtV( ui *h_nTrue, biVector X, biVector Y, ui size );

overror_t  __vcuf OVCUAPI   cudaVBI_cnt_inclrange0C( ui *h_nTrue, biVector X, ui size, char C );
overror_t  __vcuf OVCUAPI   cudaVBI_cnt_exclrange0C( ui *h_nTrue, biVector X, ui size, char C );
overror_t  __vcuf OVCUAPI   cudaVBI_cnt_inclrangeCC( ui *h_nTrue, biVector X, ui size, char CLo, char CHi );
overror_t  __vcuf OVCUAPI   cudaVBI_cnt_exclrangeCC( ui *h_nTrue, biVector X, ui size, char CLo, char CHi );
overror_t  __vcuf OVCUAPI   cusdVBI_cnt_inclrange0C( ui *h_nTrue, biVector X, ui size, char *d_C );
overror_t  __vcuf OVCUAPI   cusdVBI_cnt_exclrange0C( ui *h_nTrue, biVector X, ui size, char *d_C );
overror_t  __vcuf OVCUAPI   cusdVBI_cnt_inclrangeCC( ui *h_nTrue, biVector X, ui size, char *d_CLo, char *d_CHi );
overror_t  __vcuf OVCUAPI   cusdVBI_cnt_exclrangeCC( ui *h_nTrue, biVector X, ui size, char *d_CLo, char *d_CHi );

/******************   Basic  Arithmetics   *************************/

overror_t  __vcuf OVCUAPI   cudaVBI_neg( biVector Y, biVector X, ui size );
overror_t  __vcuf OVCUAPI   cudaVBI_abs( biVector Y, biVector X, ui size );

overror_t  __vcuf OVCUAPI   cudaVBI_addC(  biVector Y, biVector X, ui size, char C );
overror_t  __vcuf OVCUAPI   cudaVBI_subC(  biVector Y, biVector X, ui size, char C );
overror_t  __vcuf OVCUAPI   cudaVBI_subrC( biVector Y, biVector X, ui size, char C );
overror_t  __vcuf OVCUAPI   cudaVBI_mulC(  biVector Y, biVector X, ui size, char C );
overror_t  __vcuf OVCUAPI   cudaVBI_divC(  biVector Y, biVector X, ui size, char C );
overror_t  __vcuf OVCUAPI   cudaVBI_divrC( biVector Y, biVector X, ui size, char C );
overror_t  __vcuf OVCUAPI   cudaVBI_modC(  biVector Y, biVector X, ui size, char C );
overror_t  __vcuf OVCUAPI   cudaVBI_maxC(  biVector Y, biVector X, ui size, char C );
overror_t  __vcuf OVCUAPI   cudaVBI_minC(  biVector Y, biVector X, ui size, char C );
overror_t  __vcuf OVCUAPI   cudaVBI_limit( biVector Y, biVector X, ui size, char Min, char Max );

overror_t  __vcuf OVCUAPI   cusdVBI_addC(  biVector Y, biVector X, ui size, char *C );
overror_t  __vcuf OVCUAPI   cusdVBI_subC(  biVector Y, biVector X, ui size, char *C );
overror_t  __vcuf OVCUAPI   cusdVBI_subrC( biVector Y, biVector X, ui size, char *C );
overror_t  __vcuf OVCUAPI   cusdVBI_mulC(  biVector Y, biVector X, ui size, char *C );
overror_t  __vcuf OVCUAPI   cusdVBI_divC(  biVector Y, biVector X, ui size, char *C );
overror_t  __vcuf OVCUAPI   cusdVBI_divrC( biVector Y, biVector X, ui size, char *C );
overror_t  __vcuf OVCUAPI   cusdVBI_modC(  biVector Y, biVector X, ui size, char *C );
overror_t  __vcuf OVCUAPI   cusdVBI_maxC(  biVector Y, biVector X, ui size, char *C );
overror_t  __vcuf OVCUAPI   cusdVBI_minC(  biVector Y, biVector X, ui size, char *C );
overror_t  __vcuf OVCUAPI   cusdVBI_limit( biVector Y, biVector X, ui size, char *Min, char *Max );

overror_t  __vcuf OVCUAPI   cudaVBI_addV(  biVector Z, biVector X, biVector Y, ui size );
overror_t  __vcuf OVCUAPI   cudaVBI_subV(  biVector Z, biVector X, biVector Y, ui size );
overror_t  __vcuf OVCUAPI   cudaVBI_subrV( biVector Z, biVector X, biVector Y, ui size );
overror_t  __vcuf OVCUAPI   cudaVBI_mulV(  biVector Z, biVector X, biVector Y, ui size );
overror_t  __vcuf OVCUAPI   cudaVBI_divV(  biVector Z, biVector X, biVector Y, ui size );
overror_t  __vcuf OVCUAPI   cudaVBI_divrV( biVector Z, biVector X, biVector Y, ui size );
overror_t  __vcuf OVCUAPI   cudaVBI_modV(  biVector Z, biVector X, biVector Y, ui size );
overror_t  __vcuf OVCUAPI   cudaVBI_maxV(  biVector Z, biVector X, biVector Y, ui size );
overror_t  __vcuf OVCUAPI   cudaVBI_minV(  biVector Z, biVector X, biVector Y, ui size );

/******************** Accumulation (Y += X) ******************************/

overror_t  __vcuf OVCUAPI  cudaVBI_accV(   biVector Y, biVector  X, ui size );

/*****************   Bit-wise operations  *********************/

overror_t  __vcuf OVCUAPI   cudaVBI_shl( biVector Y, biVector X, ui size, unsigned C );
overror_t  __vcuf OVCUAPI   cudaVBI_shr( biVector Y, biVector X, ui size, unsigned C );

overror_t  __vcuf OVCUAPI   cudaVBI_and( biVector Y, biVector X, ui size, char C );
overror_t  __vcuf OVCUAPI   cudaVBI_or(  biVector Y, biVector X, ui size, char C );
overror_t  __vcuf OVCUAPI   cudaVBI_xor( biVector Y, biVector X, ui size, char C );
overror_t  __vcuf OVCUAPI   cudaVBI_not( biVector Y, biVector X, ui size );

overror_t  __vcuf OVCUAPI   cusdVBI_and( biVector Y, biVector X, ui size, char *C );
overror_t  __vcuf OVCUAPI   cusdVBI_or(  biVector Y, biVector X, ui size, char *C );
overror_t  __vcuf OVCUAPI   cusdVBI_xor( biVector Y, biVector X, ui size, char *C );

#ifdef __cplusplus
} // end of extern "C"
#endif

/******************  VBIcu_ functions: **********************************
	act on host memory, using the CUDA device for processing
************************************************************************/


#ifdef __cplusplus
   extern "C" {
#endif

/********************  Comparisons ********************************/

void __vf OVCUAPI   VBIcu_cmp0(    biVector Y, biVector X, ui size );
ui   __vf OVCUAPI   VBIcu_cmp_eq0( biVector Y, biVector X, ui size );
ui   __vf OVCUAPI   VBIcu_cmp_ne0( biVector Y, biVector X, ui size );
ui   __vf OVCUAPI   VBIcu_cmp_le0( biVector Y, biVector X, ui size );
ui   __vf OVCUAPI   VBIcu_cmp_lt0( biVector Y, biVector X, ui size );
ui   __vf OVCUAPI   VBIcu_cmp_ge0( biVector Y, biVector X, ui size );
ui   __vf OVCUAPI   VBIcu_cmp_gt0( biVector Y, biVector X, ui size );

ui   __vf OVCUAPI   VBIcu_cnt_eq0( biVector X, ui size );
ui   __vf OVCUAPI   VBIcu_cnt_ne0( biVector X, ui size );
ui   __vf OVCUAPI   VBIcu_cnt_le0( biVector X, ui size );
ui   __vf OVCUAPI   VBIcu_cnt_lt0( biVector X, ui size );
ui   __vf OVCUAPI   VBIcu_cnt_ge0( biVector X, ui size );
ui   __vf OVCUAPI   VBIcu_cnt_gt0( biVector X, ui size );

void __vf OVCUAPI   VBIcu_cmpC(    biVector Y, biVector X, ui size, char C );
ui   __vf OVCUAPI   VBIcu_cmp_eqC( biVector Y, biVector X, ui size, char C );
ui   __vf OVCUAPI   VBIcu_cmp_neC( biVector Y, biVector X, ui size, char C );
ui   __vf OVCUAPI   VBIcu_cmp_leC( biVector Y, biVector X, ui size, char C );
ui   __vf OVCUAPI   VBIcu_cmp_ltC( biVector Y, biVector X, ui size, char C );
ui   __vf OVCUAPI   VBIcu_cmp_geC( biVector Y, biVector X, ui size, char C );
ui   __vf OVCUAPI   VBIcu_cmp_gtC( biVector Y, biVector X, ui size, char C );

ui   __vf OVCUAPI   VBIcu_cnt_eqC( biVector X, ui size, char C );
ui   __vf OVCUAPI   VBIcu_cnt_neC( biVector X, ui size, char C );
ui   __vf OVCUAPI   VBIcu_cnt_leC( biVector X, ui size, char C );
ui   __vf OVCUAPI   VBIcu_cnt_ltC( biVector X, ui size, char C );
ui   __vf OVCUAPI   VBIcu_cnt_geC( biVector X, ui size, char C );
ui   __vf OVCUAPI   VBIcu_cnt_gtC( biVector X, ui size, char C );

void __vf OVCUAPI   VBIcu_cmpV(    biVector Z, biVector X, biVector Y, ui size );
ui   __vf OVCUAPI   VBIcu_cmp_eqV( biVector Z, biVector X, biVector Y, ui size );
ui   __vf OVCUAPI   VBIcu_cmp_neV( biVector Z, biVector X, biVector Y, ui size );
ui   __vf OVCUAPI   VBIcu_cmp_leV( biVector Z, biVector X, biVector Y, ui size );
ui   __vf OVCUAPI   VBIcu_cmp_ltV( biVector Z, biVector X, biVector Y, ui size );
ui   __vf OVCUAPI   VBIcu_cmp_geV( biVector Z, biVector X, biVector Y, ui size );
ui   __vf OVCUAPI   VBIcu_cmp_gtV( biVector Z, biVector X, biVector Y, ui size );

ui   __vf OVCUAPI   VBIcu_cnt_eqV( biVector X, biVector Y, ui size );
ui   __vf OVCUAPI   VBIcu_cnt_neV( biVector X, biVector Y, ui size );
ui   __vf OVCUAPI   VBIcu_cnt_leV( biVector X, biVector Y, ui size );
ui   __vf OVCUAPI   VBIcu_cnt_ltV( biVector X, biVector Y, ui size );
ui   __vf OVCUAPI   VBIcu_cnt_geV( biVector X, biVector Y, ui size );
ui   __vf OVCUAPI   VBIcu_cnt_gtV( biVector X, biVector Y, ui size );

ui   __vf OVCUAPI   VBIcu_cmp_inclrange0C( biVector Y, biVector X, ui size, char C );
ui   __vf OVCUAPI   VBIcu_cmp_exclrange0C( biVector Y, biVector X, ui size, char C );
ui   __vf OVCUAPI   VBIcu_cmp_inclrangeCC( biVector Y, biVector X, ui size, char CLo, char CHi );
ui   __vf OVCUAPI   VBIcu_cmp_exclrangeCC( biVector Y, biVector X, ui size, char CLo, char CHi );

ui   __vf OVCUAPI   VBIcu_cnt_inclrange0C( biVector X, ui size, char C );
ui   __vf OVCUAPI   VBIcu_cnt_exclrange0C( biVector X, ui size, char C );
ui   __vf OVCUAPI   VBIcu_cnt_inclrangeCC( biVector X, ui size, char CLo, char CHi );
ui   __vf OVCUAPI   VBIcu_cnt_exclrangeCC( biVector X, ui size, char CLo, char CHi );

/******************   Basic  Arithmetics   *************************/

void  __vf OVCUAPI   VBIcu_neg( biVector Y, biVector X, ui size );
void  __vf OVCUAPI   VBIcu_abs( biVector Y, biVector X, ui size );

void  __vf OVCUAPI   VBIcu_addC(  biVector Y, biVector X, ui size, char C );
void  __vf OVCUAPI   VBIcu_subC(  biVector Y, biVector X, ui size, char C );
void  __vf OVCUAPI   VBIcu_subrC( biVector Y, biVector X, ui size, char C );
void  __vf OVCUAPI   VBIcu_mulC(  biVector Y, biVector X, ui size, char C );
void  __vf OVCUAPI   VBIcu_divC(  biVector Y, biVector X, ui size, char C );
void  __vf OVCUAPI   VBIcu_divrC( biVector Y, biVector X, ui size, char C );
void  __vf OVCUAPI   VBIcu_modC(  biVector Y, biVector X, ui size, char C );
void  __vf OVCUAPI   VBIcu_maxC(  biVector Y, biVector X, ui size, char C );
void  __vf OVCUAPI   VBIcu_minC(  biVector Y, biVector X, ui size, char C );
void  __vf OVCUAPI   VBIcu_limit( biVector Y, biVector X, ui size, char Min, char Max );

void  __vf OVCUAPI   VBIcu_addV(  biVector Z, biVector X, biVector Y, ui size );
void  __vf OVCUAPI   VBIcu_subV(  biVector Z, biVector X, biVector Y, ui size );
void  __vf OVCUAPI   VBIcu_subrV( biVector Z, biVector X, biVector Y, ui size );
void  __vf OVCUAPI   VBIcu_mulV(  biVector Z, biVector X, biVector Y, ui size );
void  __vf OVCUAPI   VBIcu_divV(  biVector Z, biVector X, biVector Y, ui size );
void  __vf OVCUAPI   VBIcu_divrV( biVector Z, biVector X, biVector Y, ui size );
void  __vf OVCUAPI   VBIcu_modV(  biVector Z, biVector X, biVector Y, ui size );
void  __vf OVCUAPI   VBIcu_maxV(  biVector Z, biVector X, biVector Y, ui size );
void  __vf OVCUAPI   VBIcu_minV(  biVector Z, biVector X, biVector Y, ui size );

/******************** Accumulation (Y += X) ******************************/

void __vf OVCUAPI  VBIcu_accV(   biVector Y, biVector  X, ui size );

/*****************   Bit-wise operations  *********************/

void    __vf OVCUAPI   VBIcu_shl( biVector Y, biVector X, ui size, unsigned C );
void    __vf OVCUAPI   VBIcu_shr( biVector Y, biVector X, ui size, unsigned C );

void    __vf OVCUAPI   VBIcu_and( biVector Y, biVector X, ui size, char C );
void    __vf OVCUAPI   VBIcu_or(  biVector Y, biVector X, ui size, char C );
void    __vf OVCUAPI   VBIcu_xor( biVector Y, biVector X, ui size, char C );
void    __vf OVCUAPI   VBIcu_not( biVector Y, biVector X, ui size );

#ifdef __cplusplus
} // end of extern "C"
#endif

#endif   /*  __CUDAVBIMATH_H    */
