/*  cudaVUQmath.h

  vector management functions for data type "uquad":
  integer arithmetics and mathematics.

  Copyright (c) 1996-2017 by OptiCode - Dr. Martin Sander Software Dev.
  All Rights Reserved.
*/

#if defined _WIN64

#ifndef __CUDAVUQMATH_H
#define __CUDAVUQMATH_H

#if !defined( __CUDAVECLIB_H )
   #include <cudaVecLib.h>
#endif

/******************  cudaVUQ_ functions: **********************************
	 act on vectors in CUDA device memory; 
	 scalar parameters and return values on host
******************  cusdVUQ_ functions: **********************************
	 also act on vectors in CUDA device memory; 
	 scalar parameters and return values by address on device memory
************************************************************************/

#ifdef __cplusplus
   extern "C" {
#endif

/********************  Comparisons ********************************/

overror_t  __vcuf OVCUAPI   cudaVUQ_cmp_eq0( ui *h_nTrue, uqVector Y, uqVector X, ui size );
overror_t  __vcuf OVCUAPI   cudaVUQ_cmp_ne0( ui *h_nTrue, uqVector Y, uqVector X, ui size );
overror_t  __vcuf OVCUAPI   cudaVUQ_cmp_gt0( ui *h_nTrue, uqVector Y, uqVector X, ui size );

overror_t  __vcuf OVCUAPI   cudaVUQ_cmpC(    qiVector Y, uqVector X, ui size, uquad C );
overror_t  __vcuf OVCUAPI   cudaVUQ_cmp_eqC( ui *h_nTrue, uqVector Y, uqVector X, ui size, uquad C );
overror_t  __vcuf OVCUAPI   cudaVUQ_cmp_neC( ui *h_nTrue, uqVector Y, uqVector X, ui size, uquad C );
overror_t  __vcuf OVCUAPI   cudaVUQ_cmp_leC( ui *h_nTrue, uqVector Y, uqVector X, ui size, uquad C );
overror_t  __vcuf OVCUAPI   cudaVUQ_cmp_ltC( ui *h_nTrue, uqVector Y, uqVector X, ui size, uquad C );
overror_t  __vcuf OVCUAPI   cudaVUQ_cmp_geC( ui *h_nTrue, uqVector Y, uqVector X, ui size, uquad C );
overror_t  __vcuf OVCUAPI   cudaVUQ_cmp_gtC( ui *h_nTrue, uqVector Y, uqVector X, ui size, uquad C );
overror_t  __vcuf OVCUAPI   cusdVUQ_cmpC(    qiVector Y, uqVector X, ui size, uquad *d_C );
overror_t  __vcuf OVCUAPI   cusdVUQ_cmp_eqC( ui *h_nTrue, uqVector Y, uqVector X, ui size, uquad *d_C );
overror_t  __vcuf OVCUAPI   cusdVUQ_cmp_neC( ui *h_nTrue, uqVector Y, uqVector X, ui size, uquad *d_C );
overror_t  __vcuf OVCUAPI   cusdVUQ_cmp_leC( ui *h_nTrue, uqVector Y, uqVector X, ui size, uquad *d_C );
overror_t  __vcuf OVCUAPI   cusdVUQ_cmp_ltC( ui *h_nTrue, uqVector Y, uqVector X, ui size, uquad *d_C );
overror_t  __vcuf OVCUAPI   cusdVUQ_cmp_geC( ui *h_nTrue, uqVector Y, uqVector X, ui size, uquad *d_C );
overror_t  __vcuf OVCUAPI   cusdVUQ_cmp_gtC( ui *h_nTrue, uqVector Y, uqVector X, ui size, uquad *d_C );

overror_t  __vcuf OVCUAPI   cudaVUQ_cmpV(    qiVector Z, uqVector X, uqVector Y, ui size );
overror_t  __vcuf OVCUAPI   cudaVUQ_cmp_eqV( ui *h_nTrue, uqVector Z, uqVector X, uqVector Y, ui size );
overror_t  __vcuf OVCUAPI   cudaVUQ_cmp_neV( ui *h_nTrue, uqVector Z, uqVector X, uqVector Y, ui size );
overror_t  __vcuf OVCUAPI   cudaVUQ_cmp_leV( ui *h_nTrue, uqVector Z, uqVector X, uqVector Y, ui size );
overror_t  __vcuf OVCUAPI   cudaVUQ_cmp_ltV( ui *h_nTrue, uqVector Z, uqVector X, uqVector Y, ui size );
overror_t  __vcuf OVCUAPI   cudaVUQ_cmp_geV( ui *h_nTrue, uqVector Z, uqVector X, uqVector Y, ui size );
overror_t  __vcuf OVCUAPI   cudaVUQ_cmp_gtV( ui *h_nTrue, uqVector Z, uqVector X, uqVector Y, ui size );

overror_t  __vcuf OVCUAPI   cudaVUQ_cmp_exclrange0C( ui *h_nTrue, uqVector Y, uqVector X, ui size, uquad C );
overror_t  __vcuf OVCUAPI   cudaVUQ_cmp_inclrangeCC( ui *h_nTrue, uqVector Y, uqVector X, ui size, uquad CLo, uquad CHi );
overror_t  __vcuf OVCUAPI   cudaVUQ_cmp_exclrangeCC( ui *h_nTrue, uqVector Y, uqVector X, ui size, uquad CLo, uquad CHi );
overror_t  __vcuf OVCUAPI   cusdVUQ_cmp_exclrange0C( ui *h_nTrue, uqVector Y, uqVector X, ui size, uquad *d_C );
overror_t  __vcuf OVCUAPI   cusdVUQ_cmp_inclrangeCC( ui *h_nTrue, uqVector Y, uqVector X, ui size, uquad *d_CLo, uquad *d_CHi );
overror_t  __vcuf OVCUAPI   cusdVUQ_cmp_exclrangeCC( ui *h_nTrue, uqVector Y, uqVector X, ui size, uquad *d_CLo, uquad *d_CHi );

overror_t  __vcuf OVCUAPI   cudaVUQ_cnt_eq0( ui *h_nTrue, uqVector X, ui size );
overror_t  __vcuf OVCUAPI   cudaVUQ_cnt_ne0( ui *h_nTrue, uqVector X, ui size );
overror_t  __vcuf OVCUAPI   cudaVUQ_cnt_gt0( ui *h_nTrue, uqVector X, ui size );

overror_t  __vcuf OVCUAPI   cudaVUQ_cnt_eqC( ui *h_nTrue, uqVector X, ui size, uquad C );
overror_t  __vcuf OVCUAPI   cudaVUQ_cnt_neC( ui *h_nTrue, uqVector X, ui size, uquad C );
overror_t  __vcuf OVCUAPI   cudaVUQ_cnt_leC( ui *h_nTrue, uqVector X, ui size, uquad C );
overror_t  __vcuf OVCUAPI   cudaVUQ_cnt_ltC( ui *h_nTrue, uqVector X, ui size, uquad C );
overror_t  __vcuf OVCUAPI   cudaVUQ_cnt_geC( ui *h_nTrue, uqVector X, ui size, uquad C );
overror_t  __vcuf OVCUAPI   cudaVUQ_cnt_gtC( ui *h_nTrue, uqVector X, ui size, uquad C );
overror_t  __vcuf OVCUAPI   cusdVUQ_cnt_eqC( ui *h_nTrue, uqVector X, ui size, uquad *d_C );
overror_t  __vcuf OVCUAPI   cusdVUQ_cnt_neC( ui *h_nTrue, uqVector X, ui size, uquad *d_C );
overror_t  __vcuf OVCUAPI   cusdVUQ_cnt_leC( ui *h_nTrue, uqVector X, ui size, uquad *d_C );
overror_t  __vcuf OVCUAPI   cusdVUQ_cnt_ltC( ui *h_nTrue, uqVector X, ui size, uquad *d_C );
overror_t  __vcuf OVCUAPI   cusdVUQ_cnt_geC( ui *h_nTrue, uqVector X, ui size, uquad *d_C );
overror_t  __vcuf OVCUAPI   cusdVUQ_cnt_gtC( ui *h_nTrue, uqVector X, ui size, uquad *d_C );

overror_t  __vcuf OVCUAPI   cudaVUQ_cnt_eqV( ui *h_nTrue, uqVector X, uqVector Y, ui size );
overror_t  __vcuf OVCUAPI   cudaVUQ_cnt_neV( ui *h_nTrue, uqVector X, uqVector Y, ui size );
overror_t  __vcuf OVCUAPI   cudaVUQ_cnt_leV( ui *h_nTrue, uqVector X, uqVector Y, ui size );
overror_t  __vcuf OVCUAPI   cudaVUQ_cnt_ltV( ui *h_nTrue, uqVector X, uqVector Y, ui size );
overror_t  __vcuf OVCUAPI   cudaVUQ_cnt_geV( ui *h_nTrue, uqVector X, uqVector Y, ui size );
overror_t  __vcuf OVCUAPI   cudaVUQ_cnt_gtV( ui *h_nTrue, uqVector X, uqVector Y, ui size );

overror_t  __vcuf OVCUAPI   cudaVUQ_cnt_exclrange0C( ui *h_nTrue, uqVector X, ui size, uquad C );
overror_t  __vcuf OVCUAPI   cudaVUQ_cnt_inclrangeCC( ui *h_nTrue, uqVector X, ui size, uquad CLo, uquad CHi );
overror_t  __vcuf OVCUAPI   cudaVUQ_cnt_exclrangeCC( ui *h_nTrue, uqVector X, ui size, uquad CLo, uquad CHi );
overror_t  __vcuf OVCUAPI   cusdVUQ_cnt_exclrange0C( ui *h_nTrue, uqVector X, ui size, uquad *d_C );
overror_t  __vcuf OVCUAPI   cusdVUQ_cnt_inclrangeCC( ui *h_nTrue, uqVector X, ui size, uquad *d_CLo, uquad *d_CHi );
overror_t  __vcuf OVCUAPI   cusdVUQ_cnt_exclrangeCC( ui *h_nTrue, uqVector X, ui size, uquad *d_CLo, uquad *d_CHi );

/******************   Basic  Arithmetics   *************************/

overror_t  __vcuf OVCUAPI   cudaVUQ_addC(  uqVector Y, uqVector X, ui size, uquad C );
overror_t  __vcuf OVCUAPI   cudaVUQ_subC(  uqVector Y, uqVector X, ui size, uquad C );
overror_t  __vcuf OVCUAPI   cudaVUQ_subrC( uqVector Y, uqVector X, ui size, uquad C );
overror_t  __vcuf OVCUAPI   cudaVUQ_mulC(  uqVector Y, uqVector X, ui size, uquad C );

overror_t  __vcuf OVCUAPI   cudaVUQ_divC(  uqVector Y, uqVector X, ui size, uquad C );
overror_t  __vcuf OVCUAPI   cudaVUQ_divrC( uqVector Y, uqVector X, ui size, uquad C );
overror_t  __vcuf OVCUAPI   cudaVUQ_modC(  uqVector Y, uqVector X, ui size, uquad C );
overror_t  __vcuf OVCUAPI   cudaVUQ_maxC(  uqVector Y, uqVector X, ui size, uquad C );
overror_t  __vcuf OVCUAPI   cudaVUQ_minC(  uqVector Y, uqVector X, ui size, uquad C );
overror_t  __vcuf OVCUAPI   cudaVUQ_limit( uqVector Y, uqVector X, ui size, uquad Min, uquad Max );

overror_t  __vcuf OVCUAPI   cusdVUQ_addC(  uqVector Y, uqVector X, ui size, uquad *C );
overror_t  __vcuf OVCUAPI   cusdVUQ_subC(  uqVector Y, uqVector X, ui size, uquad *C );
overror_t  __vcuf OVCUAPI   cusdVUQ_subrC( uqVector Y, uqVector X, ui size, uquad *C );
overror_t  __vcuf OVCUAPI   cusdVUQ_mulC(  uqVector Y, uqVector X, ui size, uquad *C );

overror_t  __vcuf OVCUAPI   cusdVUQ_divC(  uqVector Y, uqVector X, ui size, uquad *C );
overror_t  __vcuf OVCUAPI   cusdVUQ_divrC( uqVector Y, uqVector X, ui size, uquad *C );
overror_t  __vcuf OVCUAPI   cusdVUQ_modC(  uqVector Y, uqVector X, ui size, uquad *C );
overror_t  __vcuf OVCUAPI   cusdVUQ_maxC(  uqVector Y, uqVector X, ui size, uquad *C );
overror_t  __vcuf OVCUAPI   cusdVUQ_minC(  uqVector Y, uqVector X, ui size, uquad *C );
overror_t  __vcuf OVCUAPI   cusdVUQ_limit( uqVector Y, uqVector X, ui size, uquad *Min, uquad *Max );

overror_t  __vcuf OVCUAPI   cudaVUQ_addV(  uqVector Z, uqVector X, uqVector Y, ui size );
overror_t  __vcuf OVCUAPI   cudaVUQ_subV(  uqVector Z, uqVector X, uqVector Y, ui size );
overror_t  __vcuf OVCUAPI   cudaVUQ_subrV( uqVector Z, uqVector X, uqVector Y, ui size );
overror_t  __vcuf OVCUAPI   cudaVUQ_mulV(  uqVector Z, uqVector X, uqVector Y, ui size );

overror_t  __vcuf OVCUAPI   cudaVUQ_divV(  uqVector Z, uqVector X, uqVector Y, ui size );
overror_t  __vcuf OVCUAPI   cudaVUQ_divrV( uqVector Z, uqVector X, uqVector Y, ui size );
overror_t  __vcuf OVCUAPI   cudaVUQ_modV(  uqVector Z, uqVector X, uqVector Y, ui size );
overror_t  __vcuf OVCUAPI   cudaVUQ_maxV(  uqVector Z, uqVector X, uqVector Y, ui size );
overror_t  __vcuf OVCUAPI   cudaVUQ_minV(  uqVector Z, uqVector X, uqVector Y, ui size );

/******************** Accumulation (Y += X) ******************************/

overror_t  __vcuf OVCUAPI  cudaVUQ_accV(   uqVector Y, uqVector  X, ui size );
overror_t  __vcuf OVCUAPI  cudaVUQ_accVUB( uqVector Y, ubVector  X, ui size );
overror_t  __vcuf OVCUAPI  cudaVUQ_accVUS( uqVector Y, usVector  X, ui size );
overror_t  __vcuf OVCUAPI  cudaVUQ_accVU(  uqVector Y, uVector   X, ui size );
overror_t  __vcuf OVCUAPI  cudaVUQ_accVUL( uqVector Y, ulVector  X, ui size );

/*****************   Bit-wise operations  *********************/

overror_t  __vcuf OVCUAPI   cudaVUQ_shl( uqVector Y, uqVector X, ui size, unsigned C );
overror_t  __vcuf OVCUAPI   cudaVUQ_shr( uqVector Y, uqVector X, ui size, unsigned C );

overror_t  __vcuf OVCUAPI   cudaVUQ_and( uqVector Y, uqVector X, ui size, uquad C );
overror_t  __vcuf OVCUAPI   cudaVUQ_or(  uqVector Y, uqVector X, ui size, uquad C );
overror_t  __vcuf OVCUAPI   cudaVUQ_xor( uqVector Y, uqVector X, ui size, uquad C );
overror_t  __vcuf OVCUAPI   cudaVUQ_not( uqVector Y, uqVector X, ui size );

overror_t  __vcuf OVCUAPI   cusdVUQ_and( uqVector Y, uqVector X, ui size, uquad *C );
overror_t  __vcuf OVCUAPI   cusdVUQ_or(  uqVector Y, uqVector X, ui size, uquad *C );
overror_t  __vcuf OVCUAPI   cusdVUQ_xor( uqVector Y, uqVector X, ui size, uquad *C );

/************  Optical Density Y = log10( X0 / X ) *********************/

overror_t  __vcuf OVCUAPI  cudaVUQ_ODtoF( fVector OD, uqVector X, uqVector X0, ui size );
overror_t  __vcuf OVCUAPI  cudaVUQ_ODtoD( dVector OD, uqVector X, uqVector X0, ui size );
overror_t  __vcuf OVCUAPI  cudaVUQ_ODtoFwDark( fVector OD, uqVector X, uqVector XDark,
                          uqVector X0, uqVector X0Dark, ui size );
overror_t  __vcuf OVCUAPI  cudaVUQ_ODtoDwDark( dVector OD, uqVector X, uqVector XDark,
                          uqVector X0, uqVector X0Dark, ui size );
void __vcuf OVCUAPI  cudaVUQ_setODThresh( uquad minX, uquad minX0 );

#ifdef __cplusplus
}  // end of extern "C"
#endif

/******************  VUQcu_ functions: **********************************
	act on host memory, using the CUDA device for processing
************************************************************************/


#ifdef __cplusplus
   extern "C" {
#endif

/********************  Comparisons ********************************/

ui   __vf OVCUAPI   VUQcu_cmp_eq0( uqVector Y, uqVector X, ui size );
ui   __vf OVCUAPI   VUQcu_cmp_ne0( uqVector Y, uqVector X, ui size );
ui   __vf OVCUAPI   VUQcu_cmp_gt0( uqVector Y, uqVector X, ui size );

ui   __vf OVCUAPI   VUQcu_cnt_eq0( uqVector X, ui size );
ui   __vf OVCUAPI   VUQcu_cnt_ne0( uqVector X, ui size );
ui   __vf OVCUAPI   VUQcu_cnt_gt0( uqVector X, ui size );

void __vf OVCUAPI   VUQcu_cmpC(    qiVector Y, uqVector X, ui size, uquad C );
ui   __vf OVCUAPI   VUQcu_cmp_eqC( uqVector Y, uqVector X, ui size, uquad C );
ui   __vf OVCUAPI   VUQcu_cmp_neC( uqVector Y, uqVector X, ui size, uquad C );
ui   __vf OVCUAPI   VUQcu_cmp_leC( uqVector Y, uqVector X, ui size, uquad C );
ui   __vf OVCUAPI   VUQcu_cmp_ltC( uqVector Y, uqVector X, ui size, uquad C );
ui   __vf OVCUAPI   VUQcu_cmp_geC( uqVector Y, uqVector X, ui size, uquad C );
ui   __vf OVCUAPI   VUQcu_cmp_gtC( uqVector Y, uqVector X, ui size, uquad C );

ui   __vf OVCUAPI   VUQcu_cnt_eqC( uqVector X, ui size, uquad C );
ui   __vf OVCUAPI   VUQcu_cnt_neC( uqVector X, ui size, uquad C );
ui   __vf OVCUAPI   VUQcu_cnt_leC( uqVector X, ui size, uquad C );
ui   __vf OVCUAPI   VUQcu_cnt_ltC( uqVector X, ui size, uquad C );
ui   __vf OVCUAPI   VUQcu_cnt_geC( uqVector X, ui size, uquad C );
ui   __vf OVCUAPI   VUQcu_cnt_gtC( uqVector X, ui size, uquad C );

void __vf OVCUAPI   VUQcu_cmpV(    qiVector Z, uqVector X, uqVector Y, ui size );
ui   __vf OVCUAPI   VUQcu_cmp_eqV( uqVector Z, uqVector X, uqVector Y, ui size );
ui   __vf OVCUAPI   VUQcu_cmp_neV( uqVector Z, uqVector X, uqVector Y, ui size );
ui   __vf OVCUAPI   VUQcu_cmp_leV( uqVector Z, uqVector X, uqVector Y, ui size );
ui   __vf OVCUAPI   VUQcu_cmp_ltV( uqVector Z, uqVector X, uqVector Y, ui size );
ui   __vf OVCUAPI   VUQcu_cmp_geV( uqVector Z, uqVector X, uqVector Y, ui size );
ui   __vf OVCUAPI   VUQcu_cmp_gtV( uqVector Z, uqVector X, uqVector Y, ui size );

ui   __vf OVCUAPI   VUQcu_cnt_eqV( uqVector X, uqVector Y, ui size );
ui   __vf OVCUAPI   VUQcu_cnt_neV( uqVector X, uqVector Y, ui size );
ui   __vf OVCUAPI   VUQcu_cnt_leV( uqVector X, uqVector Y, ui size );
ui   __vf OVCUAPI   VUQcu_cnt_ltV( uqVector X, uqVector Y, ui size );
ui   __vf OVCUAPI   VUQcu_cnt_geV( uqVector X, uqVector Y, ui size );
ui   __vf OVCUAPI   VUQcu_cnt_gtV( uqVector X, uqVector Y, ui size );

ui   __vf OVCUAPI   VUQcu_cmp_exclrange0C( uqVector Y, uqVector X, ui size, uquad C );
ui   __vf OVCUAPI   VUQcu_cmp_inclrangeCC( uqVector Y, uqVector X, ui size, uquad CLo, uquad CHi );
ui   __vf OVCUAPI   VUQcu_cmp_exclrangeCC( uqVector Y, uqVector X, ui size, uquad CLo, uquad CHi );

ui   __vf OVCUAPI   VUQcu_cnt_exclrange0C( uqVector X, ui size, uquad C );
ui   __vf OVCUAPI   VUQcu_cnt_inclrangeCC( uqVector X, ui size, uquad CLo, uquad CHi );
ui   __vf OVCUAPI   VUQcu_cnt_exclrangeCC( uqVector X, ui size, uquad CLo, uquad CHi );

/******************   Basic  Arithmetics   *************************/

void  __vf OVCUAPI   VUQcu_addC(  uqVector Y, uqVector X, ui size, uquad C );
void  __vf OVCUAPI   VUQcu_subC(  uqVector Y, uqVector X, ui size, uquad C );
void  __vf OVCUAPI   VUQcu_subrC( uqVector Y, uqVector X, ui size, uquad C );
void  __vf OVCUAPI   VUQcu_mulC(  uqVector Y, uqVector X, ui size, uquad C );

void  __vf OVCUAPI   VUQcu_divC(  uqVector Y, uqVector X, ui size, uquad C );
void  __vf OVCUAPI   VUQcu_divrC( uqVector Y, uqVector X, ui size, uquad C );
void  __vf OVCUAPI   VUQcu_modC(  uqVector Y, uqVector X, ui size, uquad C );
void  __vf OVCUAPI   VUQcu_maxC(  uqVector Y, uqVector X, ui size, uquad C );
void  __vf OVCUAPI   VUQcu_minC(  uqVector Y, uqVector X, ui size, uquad C );
void  __vf OVCUAPI   VUQcu_limit( uqVector Y, uqVector X, ui size, uquad Min, uquad Max );

void __vf OVCUAPI   VUQcu_addV(  uqVector Z, uqVector X, uqVector Y, ui size );
void __vf OVCUAPI   VUQcu_subV(  uqVector Z, uqVector X, uqVector Y, ui size );
void __vf OVCUAPI   VUQcu_subrV( uqVector Z, uqVector X, uqVector Y, ui size );
void __vf OVCUAPI   VUQcu_mulV(  uqVector Z, uqVector X, uqVector Y, ui size );

void    __vf OVCUAPI   VUQcu_divV(  uqVector Z, uqVector X, uqVector Y, ui size );
void    __vf OVCUAPI   VUQcu_divrV( uqVector Z, uqVector X, uqVector Y, ui size );
void    __vf OVCUAPI   VUQcu_modV(  uqVector Z, uqVector X, uqVector Y, ui size );
void    __vf OVCUAPI   VUQcu_maxV(  uqVector Z, uqVector X, uqVector Y, ui size );
void    __vf OVCUAPI   VUQcu_minV(  uqVector Z, uqVector X, uqVector Y, ui size );

/******************** Accumulation (Y += X) ******************************/

void __vf OVCUAPI  VUQcu_accV(   uqVector Y, uqVector  X, ui size );
void __vf OVCUAPI  VUQcu_accVUB( uqVector Y, ubVector  X, ui size );
void __vf OVCUAPI  VUQcu_accVUS( uqVector Y, usVector  X, ui size );
void __vf OVCUAPI  VUQcu_accVU(  uqVector Y, uVector   X, ui size );
void __vf OVCUAPI  VUQcu_accVUL( uqVector Y, ulVector  X, ui size );

/*****************   Bit-wise operations  *********************/

void    __vf OVCUAPI   VUQcu_shl( uqVector Y, uqVector X, ui size, unsigned C );
void    __vf OVCUAPI   VUQcu_shr( uqVector Y, uqVector X, ui size, unsigned C );

void    __vf OVCUAPI   VUQcu_and( uqVector Y, uqVector X, ui size, uquad C );
void    __vf OVCUAPI   VUQcu_or(  uqVector Y, uqVector X, ui size, uquad C );
void    __vf OVCUAPI   VUQcu_xor( uqVector Y, uqVector X, ui size, uquad C );
void    __vf OVCUAPI   VUQcu_not( uqVector Y, uqVector X, ui size );

/************  Optical Density Y = log10( X0 / X ) *********************/

int  __vf OVCUAPI  VUQcu_ODtoF( fVector OD, uqVector X, uqVector X0, ui size );
int  __vf OVCUAPI  VUQcu_ODtoD( dVector OD, uqVector X, uqVector X0, ui size );
int  __vf OVCUAPI  VUQcu_ODtoFwDark( fVector OD, uqVector X, uqVector XDark,
                          uqVector X0, uqVector X0Dark, ui size );
int  __vf OVCUAPI  VUQcu_ODtoDwDark( dVector OD, uqVector X, uqVector XDark,
                          uqVector X0, uqVector X0Dark, ui size );
void __vf OVCUAPI  VUQcu_setODThresh( uquad minX, uquad minX0 );

#ifdef __cplusplus
}  // end of extern "C"
#endif

#endif   /*  __CUDAVUQMATH_H    */
#endif   /*  _WIN64  */