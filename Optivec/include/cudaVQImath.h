/*  cudaVQImath.h

  vector management functions for data type "quad":
  integer arithmetics and mathematics.

  Copyright (c) 1996-2017 by OptiCode - Dr. Martin Sander Software Dev.
  All Rights Reserved.
*/

#ifndef __CUDAVQIMATH_H
#define __CUDAVQIMATH_H

#if !defined( __CUDAVECLIB_H )
   #include <cudaVecLib.h>
#endif

/******************  cudaVQI_ functions: **********************************
	 act on vectors in CUDA device memory; 
	 scalar parameters and return values on host
******************  cusdVQI_ functions: **********************************
	 also act on vectors in CUDA device memory; 
	 scalar parameters and return values by address on device memory
************************************************************************/

#ifdef __cplusplus
   extern "C" {
#endif

/********************  Comparisons ********************************/

overror_t  __vcuf OVCUAPI   cudaVQI_cmp0(    qiVector Y, qiVector X, ui size );
overror_t  __vcuf OVCUAPI   cudaVQI_cmp_eq0( ui *h_nTrue, qiVector Y, qiVector X, ui size );
overror_t  __vcuf OVCUAPI   cudaVQI_cmp_ne0( ui *h_nTrue, qiVector Y, qiVector X, ui size );
overror_t  __vcuf OVCUAPI   cudaVQI_cmp_le0( ui *h_nTrue, qiVector Y, qiVector X, ui size );
overror_t  __vcuf OVCUAPI   cudaVQI_cmp_lt0( ui *h_nTrue, qiVector Y, qiVector X, ui size );
overror_t  __vcuf OVCUAPI   cudaVQI_cmp_ge0( ui *h_nTrue, qiVector Y, qiVector X, ui size );
overror_t  __vcuf OVCUAPI   cudaVQI_cmp_gt0( ui *h_nTrue, qiVector Y, qiVector X, ui size );

overror_t  __vcuf OVCUAPI   cudaVQI_cmpC(    qiVector Y, qiVector X, ui size, quad C );
overror_t  __vcuf OVCUAPI   cudaVQI_cmp_eqC( ui *h_nTrue, qiVector Y, qiVector X, ui size, quad C );
overror_t  __vcuf OVCUAPI   cudaVQI_cmp_neC( ui *h_nTrue, qiVector Y, qiVector X, ui size, quad C );
overror_t  __vcuf OVCUAPI   cudaVQI_cmp_leC( ui *h_nTrue, qiVector Y, qiVector X, ui size, quad C );
overror_t  __vcuf OVCUAPI   cudaVQI_cmp_ltC( ui *h_nTrue, qiVector Y, qiVector X, ui size, quad C );
overror_t  __vcuf OVCUAPI   cudaVQI_cmp_geC( ui *h_nTrue, qiVector Y, qiVector X, ui size, quad C );
overror_t  __vcuf OVCUAPI   cudaVQI_cmp_gtC( ui *h_nTrue, qiVector Y, qiVector X, ui size, quad C );
overror_t  __vcuf OVCUAPI   cusdVQI_cmpC(    qiVector Y, qiVector X, ui size, quad *d_C );
overror_t  __vcuf OVCUAPI   cusdVQI_cmp_eqC( ui *h_nTrue, qiVector Y, qiVector X, ui size, quad *d_C );
overror_t  __vcuf OVCUAPI   cusdVQI_cmp_neC( ui *h_nTrue, qiVector Y, qiVector X, ui size, quad *d_C );
overror_t  __vcuf OVCUAPI   cusdVQI_cmp_leC( ui *h_nTrue, qiVector Y, qiVector X, ui size, quad *d_C );
overror_t  __vcuf OVCUAPI   cusdVQI_cmp_ltC( ui *h_nTrue, qiVector Y, qiVector X, ui size, quad *d_C );
overror_t  __vcuf OVCUAPI   cusdVQI_cmp_geC( ui *h_nTrue, qiVector Y, qiVector X, ui size, quad *d_C );
overror_t  __vcuf OVCUAPI   cusdVQI_cmp_gtC( ui *h_nTrue, qiVector Y, qiVector X, ui size, quad *d_C );

overror_t  __vcuf OVCUAPI   cudaVQI_cmpV(    qiVector Z, qiVector X, qiVector Y, ui size );
overror_t  __vcuf OVCUAPI   cudaVQI_cmp_eqV( ui *h_nTrue, qiVector Z, qiVector X, qiVector Y, ui size );
overror_t  __vcuf OVCUAPI   cudaVQI_cmp_neV( ui *h_nTrue, qiVector Z, qiVector X, qiVector Y, ui size );
overror_t  __vcuf OVCUAPI   cudaVQI_cmp_leV( ui *h_nTrue, qiVector Z, qiVector X, qiVector Y, ui size );
overror_t  __vcuf OVCUAPI   cudaVQI_cmp_ltV( ui *h_nTrue, qiVector Z, qiVector X, qiVector Y, ui size );
overror_t  __vcuf OVCUAPI   cudaVQI_cmp_geV( ui *h_nTrue, qiVector Z, qiVector X, qiVector Y, ui size );
overror_t  __vcuf OVCUAPI   cudaVQI_cmp_gtV( ui *h_nTrue, qiVector Z, qiVector X, qiVector Y, ui size );

overror_t  __vcuf OVCUAPI   cudaVQI_cmp_inclrange0C( ui *h_nTrue, qiVector Y, qiVector X, ui size, quad C );
overror_t  __vcuf OVCUAPI   cudaVQI_cmp_exclrange0C( ui *h_nTrue, qiVector Y, qiVector X, ui size, quad C );
overror_t  __vcuf OVCUAPI   cudaVQI_cmp_inclrangeCC( ui *h_nTrue, qiVector Y, qiVector X, ui size, quad CLo, quad CHi );
overror_t  __vcuf OVCUAPI   cudaVQI_cmp_exclrangeCC( ui *h_nTrue, qiVector Y, qiVector X, ui size, quad CLo, quad CHi );
overror_t  __vcuf OVCUAPI   cusdVQI_cmp_inclrange0C( ui *h_nTrue, qiVector Y, qiVector X, ui size, quad *d_C );
overror_t  __vcuf OVCUAPI   cusdVQI_cmp_exclrange0C( ui *h_nTrue, qiVector Y, qiVector X, ui size, quad *d_C );
overror_t  __vcuf OVCUAPI   cusdVQI_cmp_inclrangeCC( ui *h_nTrue, qiVector Y, qiVector X, ui size, quad *d_CLo, quad *d_CHi );
overror_t  __vcuf OVCUAPI   cusdVQI_cmp_exclrangeCC( ui *h_nTrue, qiVector Y, qiVector X, ui size, quad *d_CLo, quad *d_CHi );

overror_t  __vcuf OVCUAPI   cudaVQI_cnt_eq0( ui *h_nTrue, qiVector X, ui size );
overror_t  __vcuf OVCUAPI   cudaVQI_cnt_ne0( ui *h_nTrue, qiVector X, ui size );
overror_t  __vcuf OVCUAPI   cudaVQI_cnt_le0( ui *h_nTrue, qiVector X, ui size );
overror_t  __vcuf OVCUAPI   cudaVQI_cnt_lt0( ui *h_nTrue, qiVector X, ui size );
overror_t  __vcuf OVCUAPI   cudaVQI_cnt_ge0( ui *h_nTrue, qiVector X, ui size );
overror_t  __vcuf OVCUAPI   cudaVQI_cnt_gt0( ui *h_nTrue, qiVector X, ui size );

overror_t  __vcuf OVCUAPI   cudaVQI_cnt_eqC( ui *h_nTrue, qiVector X, ui size, quad C );
overror_t  __vcuf OVCUAPI   cudaVQI_cnt_neC( ui *h_nTrue, qiVector X, ui size, quad C );
overror_t  __vcuf OVCUAPI   cudaVQI_cnt_leC( ui *h_nTrue, qiVector X, ui size, quad C );
overror_t  __vcuf OVCUAPI   cudaVQI_cnt_ltC( ui *h_nTrue, qiVector X, ui size, quad C );
overror_t  __vcuf OVCUAPI   cudaVQI_cnt_geC( ui *h_nTrue, qiVector X, ui size, quad C );
overror_t  __vcuf OVCUAPI   cudaVQI_cnt_gtC( ui *h_nTrue, qiVector X, ui size, quad C );
overror_t  __vcuf OVCUAPI   cusdVQI_cnt_eqC( ui *h_nTrue, qiVector X, ui size, quad *d_C );
overror_t  __vcuf OVCUAPI   cusdVQI_cnt_neC( ui *h_nTrue, qiVector X, ui size, quad *d_C );
overror_t  __vcuf OVCUAPI   cusdVQI_cnt_leC( ui *h_nTrue, qiVector X, ui size, quad *d_C );
overror_t  __vcuf OVCUAPI   cusdVQI_cnt_ltC( ui *h_nTrue, qiVector X, ui size, quad *d_C );
overror_t  __vcuf OVCUAPI   cusdVQI_cnt_geC( ui *h_nTrue, qiVector X, ui size, quad *d_C );
overror_t  __vcuf OVCUAPI   cusdVQI_cnt_gtC( ui *h_nTrue, qiVector X, ui size, quad *d_C );

overror_t  __vcuf OVCUAPI   cudaVQI_cnt_eqV( ui *h_nTrue, qiVector X, qiVector Y, ui size );
overror_t  __vcuf OVCUAPI   cudaVQI_cnt_neV( ui *h_nTrue, qiVector X, qiVector Y, ui size );
overror_t  __vcuf OVCUAPI   cudaVQI_cnt_leV( ui *h_nTrue, qiVector X, qiVector Y, ui size );
overror_t  __vcuf OVCUAPI   cudaVQI_cnt_ltV( ui *h_nTrue, qiVector X, qiVector Y, ui size );
overror_t  __vcuf OVCUAPI   cudaVQI_cnt_geV( ui *h_nTrue, qiVector X, qiVector Y, ui size );
overror_t  __vcuf OVCUAPI   cudaVQI_cnt_gtV( ui *h_nTrue, qiVector X, qiVector Y, ui size );

overror_t  __vcuf OVCUAPI   cudaVQI_cnt_inclrange0C( ui *h_nTrue, qiVector X, ui size, quad C );
overror_t  __vcuf OVCUAPI   cudaVQI_cnt_exclrange0C( ui *h_nTrue, qiVector X, ui size, quad C );
overror_t  __vcuf OVCUAPI   cudaVQI_cnt_inclrangeCC( ui *h_nTrue, qiVector X, ui size, quad CLo, quad CHi );
overror_t  __vcuf OVCUAPI   cudaVQI_cnt_exclrangeCC( ui *h_nTrue, qiVector X, ui size, quad CLo, quad CHi );
overror_t  __vcuf OVCUAPI   cusdVQI_cnt_inclrange0C( ui *h_nTrue, qiVector X, ui size, quad *d_C );
overror_t  __vcuf OVCUAPI   cusdVQI_cnt_exclrange0C( ui *h_nTrue, qiVector X, ui size, quad *d_C );
overror_t  __vcuf OVCUAPI   cusdVQI_cnt_inclrangeCC( ui *h_nTrue, qiVector X, ui size, quad *d_CLo, quad *d_CHi );
overror_t  __vcuf OVCUAPI   cusdVQI_cnt_exclrangeCC( ui *h_nTrue, qiVector X, ui size, quad *d_CLo, quad *d_CHi );

/******************   Basic  Arithmetics   *************************/

overror_t  __vcuf OVCUAPI   cudaVQI_neg( qiVector Y, qiVector X, ui size );
overror_t  __vcuf OVCUAPI   cudaVQI_abs( qiVector Y, qiVector X, ui size );

overror_t  __vcuf OVCUAPI   cudaVQI_addC(  qiVector Y, qiVector X, ui size, quad C );
overror_t  __vcuf OVCUAPI   cudaVQI_subC(  qiVector Y, qiVector X, ui size, quad C );
overror_t  __vcuf OVCUAPI   cudaVQI_subrC( qiVector Y, qiVector X, ui size, quad C );
overror_t  __vcuf OVCUAPI   cudaVQI_mulC(  qiVector Y, qiVector X, ui size, quad C );
overror_t  __vcuf OVCUAPI   cudaVQI_divC(  qiVector Y, qiVector X, ui size, quad C );
overror_t  __vcuf OVCUAPI   cudaVQI_divrC( qiVector Y, qiVector X, ui size, quad C );
overror_t  __vcuf OVCUAPI   cudaVQI_modC(  qiVector Y, qiVector X, ui size, quad C );
overror_t  __vcuf OVCUAPI   cudaVQI_maxC(  qiVector Y, qiVector X, ui size, quad C );
overror_t  __vcuf OVCUAPI   cudaVQI_minC(  qiVector Y, qiVector X, ui size, quad C );
overror_t  __vcuf OVCUAPI   cudaVQI_limit( qiVector Y, qiVector X, ui size, quad Min, quad Max );

overror_t  __vcuf OVCUAPI   cusdVQI_addC(  qiVector Y, qiVector X, ui size, quad *C );
overror_t  __vcuf OVCUAPI   cusdVQI_subC(  qiVector Y, qiVector X, ui size, quad *C );
overror_t  __vcuf OVCUAPI   cusdVQI_subrC( qiVector Y, qiVector X, ui size, quad *C );
overror_t  __vcuf OVCUAPI   cusdVQI_mulC(  qiVector Y, qiVector X, ui size, quad *C );
overror_t  __vcuf OVCUAPI   cusdVQI_divC(  qiVector Y, qiVector X, ui size, quad *C );
overror_t  __vcuf OVCUAPI   cusdVQI_divrC( qiVector Y, qiVector X, ui size, quad *C );
overror_t  __vcuf OVCUAPI   cusdVQI_modC(  qiVector Y, qiVector X, ui size, quad *C );
overror_t  __vcuf OVCUAPI   cusdVQI_maxC(  qiVector Y, qiVector X, ui size, quad *C );
overror_t  __vcuf OVCUAPI   cusdVQI_minC(  qiVector Y, qiVector X, ui size, quad *C );
overror_t  __vcuf OVCUAPI   cusdVQI_limit( qiVector Y, qiVector X, ui size, quad *Min, quad *Max );

overror_t  __vcuf OVCUAPI   cudaVQI_addV(  qiVector Z, qiVector X, qiVector Y, ui size );
overror_t  __vcuf OVCUAPI   cudaVQI_subV(  qiVector Z, qiVector X, qiVector Y, ui size );
overror_t  __vcuf OVCUAPI   cudaVQI_subrV( qiVector Z, qiVector X, qiVector Y, ui size );
overror_t  __vcuf OVCUAPI   cudaVQI_mulV(  qiVector Z, qiVector X, qiVector Y, ui size );
overror_t  __vcuf OVCUAPI   cudaVQI_divV(  qiVector Z, qiVector X, qiVector Y, ui size );
overror_t  __vcuf OVCUAPI   cudaVQI_divrV( qiVector Z, qiVector X, qiVector Y, ui size );
overror_t  __vcuf OVCUAPI   cudaVQI_modV(  qiVector Z, qiVector X, qiVector Y, ui size );
overror_t  __vcuf OVCUAPI   cudaVQI_maxV(  qiVector Z, qiVector X, qiVector Y, ui size );
overror_t  __vcuf OVCUAPI   cudaVQI_minV(  qiVector Z, qiVector X, qiVector Y, ui size );

/******************** Accumulation (Y += X) ******************************/

overror_t  __vcuf OVCUAPI  cudaVQI_accV(   qiVector Y, qiVector  X, ui size );
overror_t  __vcuf OVCUAPI  cudaVQI_accVBI( qiVector Y, biVector  X, ui size );
overror_t  __vcuf OVCUAPI  cudaVQI_accVSI( qiVector Y, siVector  X, ui size );
overror_t  __vcuf OVCUAPI  cudaVQI_accVI(  qiVector Y, iVector   X, ui size );
overror_t  __vcuf OVCUAPI  cudaVQI_accVLI( qiVector Y, liVector  X, ui size );
overror_t  __vcuf OVCUAPI  cudaVQI_accVUB( qiVector Y, ubVector  X, ui size );
overror_t  __vcuf OVCUAPI  cudaVQI_accVUS( qiVector Y, usVector  X, ui size );
overror_t  __vcuf OVCUAPI  cudaVQI_accVU(  qiVector Y, uVector   X, ui size );
overror_t  __vcuf OVCUAPI  cudaVQI_accVUL( qiVector Y, ulVector  X, ui size );

/*****************   Bit-wise operations  *********************/

overror_t  __vcuf OVCUAPI   cudaVQI_shl( qiVector Y, qiVector X, ui size, unsigned C );
overror_t  __vcuf OVCUAPI   cudaVQI_shr( qiVector Y, qiVector X, ui size, unsigned C );

overror_t  __vcuf OVCUAPI   cudaVQI_and( qiVector Y, qiVector X, ui size, quad C );
overror_t  __vcuf OVCUAPI   cudaVQI_or(  qiVector Y, qiVector X, ui size, quad C );
overror_t  __vcuf OVCUAPI   cudaVQI_xor( qiVector Y, qiVector X, ui size, quad C );
overror_t  __vcuf OVCUAPI   cudaVQI_not( qiVector Y, qiVector X, ui size );

overror_t  __vcuf OVCUAPI   cusdVQI_and( qiVector Y, qiVector X, ui size, quad *C );
overror_t  __vcuf OVCUAPI   cusdVQI_or(  qiVector Y, qiVector X, ui size, quad *C );
overror_t  __vcuf OVCUAPI   cusdVQI_xor( qiVector Y, qiVector X, ui size, quad *C );

/************  Optical Density Y = log10( X0 / X ) *********************/

overror_t  __vcuf OVCUAPI  cudaVQI_ODtoF( fVector OD, qiVector X, qiVector X0, ui size );
overror_t  __vcuf OVCUAPI  cudaVQI_ODtoD( dVector OD, qiVector X, qiVector X0, ui size );
overror_t  __vcuf OVCUAPI  cudaVQI_ODtoFwDark( fVector OD, qiVector X, qiVector XDark,
                          qiVector X0, qiVector X0Dark, ui size );
overror_t  __vcuf OVCUAPI  cudaVQI_ODtoDwDark( dVector OD, qiVector X, qiVector XDark,
                          qiVector X0, qiVector X0Dark, ui size );
void __vcuf OVCUAPI  cudaVQI_setODThresh( quad minX, quad minX0 );

#ifdef __cplusplus
}  // end of extern "C"
#endif


/******************  VQIcu_ functions: **********************************
	act on host memory, using the CUDA device for processing
************************************************************************/


#ifdef __cplusplus
   extern "C" {
#endif

/********************  Comparisons ********************************/

void __vf OVCUAPI   VQIcu_cmp0(    qiVector Y, qiVector X, ui size );
ui   __vf OVCUAPI   VQIcu_cmp_eq0( qiVector Y, qiVector X, ui size );
ui   __vf OVCUAPI   VQIcu_cmp_ne0( qiVector Y, qiVector X, ui size );
ui   __vf OVCUAPI   VQIcu_cmp_le0( qiVector Y, qiVector X, ui size );
ui   __vf OVCUAPI   VQIcu_cmp_lt0( qiVector Y, qiVector X, ui size );
ui   __vf OVCUAPI   VQIcu_cmp_ge0( qiVector Y, qiVector X, ui size );
ui   __vf OVCUAPI   VQIcu_cmp_gt0( qiVector Y, qiVector X, ui size );

ui   __vf OVCUAPI   VQIcu_cnt_eq0( qiVector X, ui size );
ui   __vf OVCUAPI   VQIcu_cnt_ne0( qiVector X, ui size );
ui   __vf OVCUAPI   VQIcu_cnt_le0( qiVector X, ui size );
ui   __vf OVCUAPI   VQIcu_cnt_lt0( qiVector X, ui size );
ui   __vf OVCUAPI   VQIcu_cnt_ge0( qiVector X, ui size );
ui   __vf OVCUAPI   VQIcu_cnt_gt0( qiVector X, ui size );

void __vf OVCUAPI   VQIcu_cmpC(    qiVector Y, qiVector X, ui size, quad C );
ui   __vf OVCUAPI   VQIcu_cmp_eqC( qiVector Y, qiVector X, ui size, quad C );
ui   __vf OVCUAPI   VQIcu_cmp_neC( qiVector Y, qiVector X, ui size, quad C );
ui   __vf OVCUAPI   VQIcu_cmp_leC( qiVector Y, qiVector X, ui size, quad C );
ui   __vf OVCUAPI   VQIcu_cmp_ltC( qiVector Y, qiVector X, ui size, quad C );
ui   __vf OVCUAPI   VQIcu_cmp_geC( qiVector Y, qiVector X, ui size, quad C );
ui   __vf OVCUAPI   VQIcu_cmp_gtC( qiVector Y, qiVector X, ui size, quad C );

ui   __vf OVCUAPI   VQIcu_cnt_eqC( qiVector X, ui size, quad C );
ui   __vf OVCUAPI   VQIcu_cnt_neC( qiVector X, ui size, quad C );
ui   __vf OVCUAPI   VQIcu_cnt_leC( qiVector X, ui size, quad C );
ui   __vf OVCUAPI   VQIcu_cnt_ltC( qiVector X, ui size, quad C );
ui   __vf OVCUAPI   VQIcu_cnt_geC( qiVector X, ui size, quad C );
ui   __vf OVCUAPI   VQIcu_cnt_gtC( qiVector X, ui size, quad C );

void __vf OVCUAPI   VQIcu_cmpV(    qiVector Z, qiVector X, qiVector Y, ui size );
ui   __vf OVCUAPI   VQIcu_cmp_eqV( qiVector Z, qiVector X, qiVector Y, ui size );
ui   __vf OVCUAPI   VQIcu_cmp_neV( qiVector Z, qiVector X, qiVector Y, ui size );
ui   __vf OVCUAPI   VQIcu_cmp_leV( qiVector Z, qiVector X, qiVector Y, ui size );
ui   __vf OVCUAPI   VQIcu_cmp_ltV( qiVector Z, qiVector X, qiVector Y, ui size );
ui   __vf OVCUAPI   VQIcu_cmp_geV( qiVector Z, qiVector X, qiVector Y, ui size );
ui   __vf OVCUAPI   VQIcu_cmp_gtV( qiVector Z, qiVector X, qiVector Y, ui size );

ui   __vf OVCUAPI   VQIcu_cnt_eqV( qiVector X, qiVector Y, ui size );
ui   __vf OVCUAPI   VQIcu_cnt_neV( qiVector X, qiVector Y, ui size );
ui   __vf OVCUAPI   VQIcu_cnt_leV( qiVector X, qiVector Y, ui size );
ui   __vf OVCUAPI   VQIcu_cnt_ltV( qiVector X, qiVector Y, ui size );
ui   __vf OVCUAPI   VQIcu_cnt_geV( qiVector X, qiVector Y, ui size );
ui   __vf OVCUAPI   VQIcu_cnt_gtV( qiVector X, qiVector Y, ui size );

ui   __vf OVCUAPI   VQIcu_cmp_inclrange0C( qiVector Y, qiVector X, ui size, quad C );
ui   __vf OVCUAPI   VQIcu_cmp_exclrange0C( qiVector Y, qiVector X, ui size, quad C );
ui   __vf OVCUAPI   VQIcu_cmp_inclrangeCC( qiVector Y, qiVector X, ui size, quad CLo, quad CHi );
ui   __vf OVCUAPI   VQIcu_cmp_exclrangeCC( qiVector Y, qiVector X, ui size, quad CLo, quad CHi );

ui   __vf OVCUAPI   VQIcu_cnt_inclrange0C( qiVector X, ui size, quad C );
ui   __vf OVCUAPI   VQIcu_cnt_exclrange0C( qiVector X, ui size, quad C );
ui   __vf OVCUAPI   VQIcu_cnt_inclrangeCC( qiVector X, ui size, quad CLo, quad CHi );
ui   __vf OVCUAPI   VQIcu_cnt_exclrangeCC( qiVector X, ui size, quad CLo, quad CHi );

/******************   Basic  Arithmetics   *************************/

void    __vf OVCUAPI   VQIcu_neg( qiVector Y, qiVector X, ui size );
void    __vf OVCUAPI   VQIcu_abs( qiVector Y, qiVector X, ui size );

void    __vf OVCUAPI   VQIcu_addC(  qiVector Y, qiVector X, ui size, quad C );
void    __vf OVCUAPI   VQIcu_subC(  qiVector Y, qiVector X, ui size, quad C );
void    __vf OVCUAPI   VQIcu_subrC( qiVector Y, qiVector X, ui size, quad C );
void    __vf OVCUAPI   VQIcu_mulC(  qiVector Y, qiVector X, ui size, quad C );
void    __vf OVCUAPI   VQIcu_divC(  qiVector Y, qiVector X, ui size, quad C );
void    __vf OVCUAPI   VQIcu_divrC( qiVector Y, qiVector X, ui size, quad C );
void    __vf OVCUAPI   VQIcu_modC(  qiVector Y, qiVector X, ui size, quad C );
void    __vf OVCUAPI   VQIcu_maxC(  qiVector Y, qiVector X, ui size, quad C );
void    __vf OVCUAPI   VQIcu_minC(  qiVector Y, qiVector X, ui size, quad C );
void    __vf OVCUAPI   VQIcu_limit( qiVector Y, qiVector X, ui size, quad Min, quad Max );

void    __vf OVCUAPI   VQIcu_addV(  qiVector Z, qiVector X, qiVector Y, ui size );
void    __vf OVCUAPI   VQIcu_subV(  qiVector Z, qiVector X, qiVector Y, ui size );
void    __vf OVCUAPI   VQIcu_subrV( qiVector Z, qiVector X, qiVector Y, ui size );
void    __vf OVCUAPI   VQIcu_mulV(  qiVector Z, qiVector X, qiVector Y, ui size );
void    __vf OVCUAPI   VQIcu_divV(  qiVector Z, qiVector X, qiVector Y, ui size );
void    __vf OVCUAPI   VQIcu_divrV( qiVector Z, qiVector X, qiVector Y, ui size );
void    __vf OVCUAPI   VQIcu_modV(  qiVector Z, qiVector X, qiVector Y, ui size );
void    __vf OVCUAPI   VQIcu_maxV(  qiVector Z, qiVector X, qiVector Y, ui size );
void    __vf OVCUAPI   VQIcu_minV(  qiVector Z, qiVector X, qiVector Y, ui size );

/******************** Accumulation (Y += X) ******************************/

void __vf OVCUAPI  VQIcu_accV(   qiVector Y, qiVector  X, ui size );
void __vf OVCUAPI  VQIcu_accVBI( qiVector Y, biVector  X, ui size );
void __vf OVCUAPI  VQIcu_accVSI( qiVector Y, siVector  X, ui size );
void __vf OVCUAPI  VQIcu_accVI(  qiVector Y, iVector   X, ui size );
void __vf OVCUAPI  VQIcu_accVLI( qiVector Y, liVector  X, ui size );
void __vf OVCUAPI  VQIcu_accVUB( qiVector Y, ubVector  X, ui size );
void __vf OVCUAPI  VQIcu_accVUS( qiVector Y, usVector  X, ui size );
void __vf OVCUAPI  VQIcu_accVU(  qiVector Y, uVector   X, ui size );
void __vf OVCUAPI  VQIcu_accVUL( qiVector Y, ulVector  X, ui size );

/*****************   Bit-wise operations  *********************/

void    __vf OVCUAPI   VQIcu_shl( qiVector Y, qiVector X, ui size, unsigned C );
void    __vf OVCUAPI   VQIcu_shr( qiVector Y, qiVector X, ui size, unsigned C );

void    __vf OVCUAPI   VQIcu_and( qiVector Y, qiVector X, ui size, quad C );
void    __vf OVCUAPI   VQIcu_or(  qiVector Y, qiVector X, ui size, quad C );
void    __vf OVCUAPI   VQIcu_xor( qiVector Y, qiVector X, ui size, quad C );
void    __vf OVCUAPI   VQIcu_not( qiVector Y, qiVector X, ui size );

/************  Optical Density Y = log10( X0 / X ) *********************/

int  __vf OVCUAPI  VQIcu_ODtoF( fVector OD, qiVector X, qiVector X0, ui size );
int  __vf OVCUAPI  VQIcu_ODtoD( dVector OD, qiVector X, qiVector X0, ui size );
int  __vf OVCUAPI  VQIcu_ODtoFwDark( fVector OD, qiVector X, qiVector XDark,
                          qiVector X0, qiVector X0Dark, ui size );
int  __vf OVCUAPI  VQIcu_ODtoDwDark( dVector OD, qiVector X, qiVector XDark,
                          qiVector X0, qiVector X0Dark, ui size );
void __vf OVCUAPI  VQIcu_setODThresh( quad minX, quad minX0 );

#ifdef __cplusplus
}  // end of extern "C"
#endif

#endif   /*  __CUDAVQIMATH_H    */
