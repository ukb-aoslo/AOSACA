/*  cudaVULmath.h

  vector management functions for data type "unsigned long":
  integer arithmetics and mathematics.

  Copyright (c) 1996-2017 by OptiCode - Dr. Martin Sander Software Dev.
  All Rights Reserved.
*/

#ifndef __CUDAVULMATH_H
#define __CUDAVULMATH_H

#if !defined( __CUDAVECLIB_H )
   #include <cudaVecLib.h>
#endif

/******************  cudaVUL_ functions: **********************************
	 act on vectors in CUDA device memory; 
	 scalar parameters and return values on host
******************  cusdVUL_ functions: **********************************
	 also act on vectors in CUDA device memory; 
	 scalar parameters and return values by address on device memory
************************************************************************/

#ifdef __cplusplus
   extern "C" {
#endif

/********************  Comparisons ********************************/

overror_t  __vcuf OVCUAPI   cudaVUL_cmp_eq0( ui *h_nTrue, ulVector Y, ulVector X, ui size );
overror_t  __vcuf OVCUAPI   cudaVUL_cmp_ne0( ui *h_nTrue, ulVector Y, ulVector X, ui size );
overror_t  __vcuf OVCUAPI   cudaVUL_cmp_gt0( ui *h_nTrue, ulVector Y, ulVector X, ui size );

overror_t  __vcuf OVCUAPI   cudaVUL_cmpC(    liVector Y, ulVector X, ui size, unsigned long C );
overror_t  __vcuf OVCUAPI   cudaVUL_cmp_eqC( ui *h_nTrue, ulVector Y, ulVector X, ui size, unsigned long C );
overror_t  __vcuf OVCUAPI   cudaVUL_cmp_neC( ui *h_nTrue, ulVector Y, ulVector X, ui size, unsigned long C );
overror_t  __vcuf OVCUAPI   cudaVUL_cmp_leC( ui *h_nTrue, ulVector Y, ulVector X, ui size, unsigned long C );
overror_t  __vcuf OVCUAPI   cudaVUL_cmp_ltC( ui *h_nTrue, ulVector Y, ulVector X, ui size, unsigned long C );
overror_t  __vcuf OVCUAPI   cudaVUL_cmp_geC( ui *h_nTrue, ulVector Y, ulVector X, ui size, unsigned long C );
overror_t  __vcuf OVCUAPI   cudaVUL_cmp_gtC( ui *h_nTrue, ulVector Y, ulVector X, ui size, unsigned long C );
overror_t  __vcuf OVCUAPI   cusdVUL_cmpC(    liVector Y, ulVector X, ui size, unsigned long *d_C );
overror_t  __vcuf OVCUAPI   cusdVUL_cmp_eqC( ui *h_nTrue, ulVector Y, ulVector X, ui size, unsigned long *d_C );
overror_t  __vcuf OVCUAPI   cusdVUL_cmp_neC( ui *h_nTrue, ulVector Y, ulVector X, ui size, unsigned long *d_C );
overror_t  __vcuf OVCUAPI   cusdVUL_cmp_leC( ui *h_nTrue, ulVector Y, ulVector X, ui size, unsigned long *d_C );
overror_t  __vcuf OVCUAPI   cusdVUL_cmp_ltC( ui *h_nTrue, ulVector Y, ulVector X, ui size, unsigned long *d_C );
overror_t  __vcuf OVCUAPI   cusdVUL_cmp_geC( ui *h_nTrue, ulVector Y, ulVector X, ui size, unsigned long *d_C );
overror_t  __vcuf OVCUAPI   cusdVUL_cmp_gtC( ui *h_nTrue, ulVector Y, ulVector X, ui size, unsigned long *d_C );

overror_t  __vcuf OVCUAPI   cudaVUL_cmpV(    liVector Z, ulVector X, ulVector Y, ui size );
overror_t  __vcuf OVCUAPI   cudaVUL_cmp_eqV( ui *h_nTrue, ulVector Z, ulVector X, ulVector Y, ui size );
overror_t  __vcuf OVCUAPI   cudaVUL_cmp_neV( ui *h_nTrue, ulVector Z, ulVector X, ulVector Y, ui size );
overror_t  __vcuf OVCUAPI   cudaVUL_cmp_leV( ui *h_nTrue, ulVector Z, ulVector X, ulVector Y, ui size );
overror_t  __vcuf OVCUAPI   cudaVUL_cmp_ltV( ui *h_nTrue, ulVector Z, ulVector X, ulVector Y, ui size );
overror_t  __vcuf OVCUAPI   cudaVUL_cmp_geV( ui *h_nTrue, ulVector Z, ulVector X, ulVector Y, ui size );
overror_t  __vcuf OVCUAPI   cudaVUL_cmp_gtV( ui *h_nTrue, ulVector Z, ulVector X, ulVector Y, ui size );

overror_t  __vcuf OVCUAPI   cudaVUL_cmp_exclrange0C( ui *h_nTrue, ulVector Y, ulVector X, ui size, unsigned long C );
overror_t  __vcuf OVCUAPI   cudaVUL_cmp_inclrangeCC( ui *h_nTrue, ulVector Y, ulVector X, ui size, unsigned long CLo, unsigned long CHi );
overror_t  __vcuf OVCUAPI   cudaVUL_cmp_exclrangeCC( ui *h_nTrue, ulVector Y, ulVector X, ui size, unsigned long CLo, unsigned long CHi );
overror_t  __vcuf OVCUAPI   cusdVUL_cmp_exclrange0C( ui *h_nTrue, ulVector Y, ulVector X, ui size, unsigned long *d_C );
overror_t  __vcuf OVCUAPI   cusdVUL_cmp_inclrangeCC( ui *h_nTrue, ulVector Y, ulVector X, ui size, unsigned long *d_CLo, unsigned long *d_CHi );
overror_t  __vcuf OVCUAPI   cusdVUL_cmp_exclrangeCC( ui *h_nTrue, ulVector Y, ulVector X, ui size, unsigned long *d_CLo, unsigned long *d_CHi );

overror_t  __vcuf OVCUAPI   cudaVUL_cnt_eq0( ui *h_nTrue, ulVector X, ui size );
overror_t  __vcuf OVCUAPI   cudaVUL_cnt_ne0( ui *h_nTrue, ulVector X, ui size );
overror_t  __vcuf OVCUAPI   cudaVUL_cnt_gt0( ui *h_nTrue, ulVector X, ui size );

overror_t  __vcuf OVCUAPI   cudaVUL_cnt_eqC( ui *h_nTrue, ulVector X, ui size, unsigned long C );
overror_t  __vcuf OVCUAPI   cudaVUL_cnt_neC( ui *h_nTrue, ulVector X, ui size, unsigned long C );
overror_t  __vcuf OVCUAPI   cudaVUL_cnt_leC( ui *h_nTrue, ulVector X, ui size, unsigned long C );
overror_t  __vcuf OVCUAPI   cudaVUL_cnt_ltC( ui *h_nTrue, ulVector X, ui size, unsigned long C );
overror_t  __vcuf OVCUAPI   cudaVUL_cnt_geC( ui *h_nTrue, ulVector X, ui size, unsigned long C );
overror_t  __vcuf OVCUAPI   cudaVUL_cnt_gtC( ui *h_nTrue, ulVector X, ui size, unsigned long C );
overror_t  __vcuf OVCUAPI   cusdVUL_cnt_eqC( ui *h_nTrue, ulVector X, ui size, unsigned long *d_C );
overror_t  __vcuf OVCUAPI   cusdVUL_cnt_neC( ui *h_nTrue, ulVector X, ui size, unsigned long *d_C );
overror_t  __vcuf OVCUAPI   cusdVUL_cnt_leC( ui *h_nTrue, ulVector X, ui size, unsigned long *d_C );
overror_t  __vcuf OVCUAPI   cusdVUL_cnt_ltC( ui *h_nTrue, ulVector X, ui size, unsigned long *d_C );
overror_t  __vcuf OVCUAPI   cusdVUL_cnt_geC( ui *h_nTrue, ulVector X, ui size, unsigned long *d_C );
overror_t  __vcuf OVCUAPI   cusdVUL_cnt_gtC( ui *h_nTrue, ulVector X, ui size, unsigned long *d_C );

overror_t  __vcuf OVCUAPI   cudaVUL_cnt_eqV( ui *h_nTrue, ulVector X, ulVector Y, ui size );
overror_t  __vcuf OVCUAPI   cudaVUL_cnt_neV( ui *h_nTrue, ulVector X, ulVector Y, ui size );
overror_t  __vcuf OVCUAPI   cudaVUL_cnt_leV( ui *h_nTrue, ulVector X, ulVector Y, ui size );
overror_t  __vcuf OVCUAPI   cudaVUL_cnt_ltV( ui *h_nTrue, ulVector X, ulVector Y, ui size );
overror_t  __vcuf OVCUAPI   cudaVUL_cnt_geV( ui *h_nTrue, ulVector X, ulVector Y, ui size );
overror_t  __vcuf OVCUAPI   cudaVUL_cnt_gtV( ui *h_nTrue, ulVector X, ulVector Y, ui size );

overror_t  __vcuf OVCUAPI   cudaVUL_cnt_exclrange0C( ui *h_nTrue, ulVector X, ui size, unsigned long C );
overror_t  __vcuf OVCUAPI   cudaVUL_cnt_inclrangeCC( ui *h_nTrue, ulVector X, ui size, unsigned long CLo, unsigned long CHi );
overror_t  __vcuf OVCUAPI   cudaVUL_cnt_exclrangeCC( ui *h_nTrue, ulVector X, ui size, unsigned long CLo, unsigned long CHi );
overror_t  __vcuf OVCUAPI   cusdVUL_cnt_exclrange0C( ui *h_nTrue, ulVector X, ui size, unsigned long *d_C );
overror_t  __vcuf OVCUAPI   cusdVUL_cnt_inclrangeCC( ui *h_nTrue, ulVector X, ui size, unsigned long *d_CLo, unsigned long *d_CHi );
overror_t  __vcuf OVCUAPI   cusdVUL_cnt_exclrangeCC( ui *h_nTrue, ulVector X, ui size, unsigned long *d_CLo, unsigned long *d_CHi );

/******************   Basic  Arithmetics   *************************/

overror_t  __vcuf OVCUAPI   cudaVUL_addC(  ulVector Y, ulVector X, ui size, unsigned long C );
overror_t  __vcuf OVCUAPI   cudaVUL_subC(  ulVector Y, ulVector X, ui size, unsigned long C );
overror_t  __vcuf OVCUAPI   cudaVUL_subrC( ulVector Y, ulVector X, ui size, unsigned long C );
overror_t  __vcuf OVCUAPI   cudaVUL_mulC(  ulVector Y, ulVector X, ui size, unsigned long C );

overror_t  __vcuf OVCUAPI   cudaVUL_divC(  ulVector Y, ulVector X, ui size, unsigned long C );
overror_t  __vcuf OVCUAPI   cudaVUL_divrC( ulVector Y, ulVector X, ui size, unsigned long C );
overror_t  __vcuf OVCUAPI   cudaVUL_modC(  ulVector Y, ulVector X, ui size, unsigned long C );
overror_t  __vcuf OVCUAPI   cudaVUL_maxC(  ulVector Y, ulVector X, ui size, unsigned long C );
overror_t  __vcuf OVCUAPI   cudaVUL_minC(  ulVector Y, ulVector X, ui size, unsigned long C );
overror_t  __vcuf OVCUAPI   cudaVUL_limit( ulVector Y, ulVector X, ui size, unsigned long Min, unsigned long Max );

overror_t  __vcuf OVCUAPI   cusdVUL_addC(  ulVector Y, ulVector X, ui size, unsigned long *C );
overror_t  __vcuf OVCUAPI   cusdVUL_subC(  ulVector Y, ulVector X, ui size, unsigned long *C );
overror_t  __vcuf OVCUAPI   cusdVUL_subrC( ulVector Y, ulVector X, ui size, unsigned long *C );
overror_t  __vcuf OVCUAPI   cusdVUL_mulC(  ulVector Y, ulVector X, ui size, unsigned long *C );

overror_t  __vcuf OVCUAPI   cusdVUL_divC(  ulVector Y, ulVector X, ui size, unsigned long *C );
overror_t  __vcuf OVCUAPI   cusdVUL_divrC( ulVector Y, ulVector X, ui size, unsigned long *C );
overror_t  __vcuf OVCUAPI   cusdVUL_modC(  ulVector Y, ulVector X, ui size, unsigned long *C );
overror_t  __vcuf OVCUAPI   cusdVUL_maxC(  ulVector Y, ulVector X, ui size, unsigned long *C );
overror_t  __vcuf OVCUAPI   cusdVUL_minC(  ulVector Y, ulVector X, ui size, unsigned long *C );
overror_t  __vcuf OVCUAPI   cusdVUL_limit( ulVector Y, ulVector X, ui size, unsigned long *Min, unsigned long *Max );

overror_t  __vcuf OVCUAPI   cudaVUL_addV(  ulVector Z, ulVector X, ulVector Y, ui size );
overror_t  __vcuf OVCUAPI   cudaVUL_subV(  ulVector Z, ulVector X, ulVector Y, ui size );
overror_t  __vcuf OVCUAPI   cudaVUL_subrV( ulVector Z, ulVector X, ulVector Y, ui size );
overror_t  __vcuf OVCUAPI   cudaVUL_mulV(  ulVector Z, ulVector X, ulVector Y, ui size );
overror_t  __vcuf OVCUAPI   cudaVUL_divV(  ulVector Z, ulVector X, ulVector Y, ui size );
overror_t  __vcuf OVCUAPI   cudaVUL_divrV( ulVector Z, ulVector X, ulVector Y, ui size );
overror_t  __vcuf OVCUAPI   cudaVUL_modV(  ulVector Z, ulVector X, ulVector Y, ui size );
overror_t  __vcuf OVCUAPI   cudaVUL_maxV(  ulVector Z, ulVector X, ulVector Y, ui size );
overror_t  __vcuf OVCUAPI   cudaVUL_minV(  ulVector Z, ulVector X, ulVector Y, ui size );

/******************** Accumulation (Y += X) ******************************/

overror_t  __vcuf OVCUAPI  cudaVUL_accV(   ulVector Y, ulVector  X, ui size );
overror_t  __vcuf OVCUAPI  cudaVUL_accVUB( ulVector Y, ubVector  X, ui size );
overror_t  __vcuf OVCUAPI  cudaVUL_accVUS( ulVector Y, usVector  X, ui size );
overror_t  __vcuf OVCUAPI  cudaVUL_accVU(  ulVector Y, uVector   X, ui size );

/*****************   Bit-wise operations  *********************/

overror_t  __vcuf OVCUAPI   cudaVUL_shl( ulVector Y, ulVector X, ui size, unsigned C );
overror_t  __vcuf OVCUAPI   cudaVUL_shr( ulVector Y, ulVector X, ui size, unsigned C );

overror_t  __vcuf OVCUAPI   cudaVUL_and( ulVector Y, ulVector X, ui size, unsigned long C );
overror_t  __vcuf OVCUAPI   cudaVUL_or(  ulVector Y, ulVector X, ui size, unsigned long C );
overror_t  __vcuf OVCUAPI   cudaVUL_xor( ulVector Y, ulVector X, ui size, unsigned long C );
overror_t  __vcuf OVCUAPI   cudaVUL_not( ulVector Y, ulVector X, ui size );

overror_t  __vcuf OVCUAPI   cusdVUL_and( ulVector Y, ulVector X, ui size, unsigned long *C );
overror_t  __vcuf OVCUAPI   cusdVUL_or(  ulVector Y, ulVector X, ui size, unsigned long *C );
overror_t  __vcuf OVCUAPI   cusdVUL_xor( ulVector Y, ulVector X, ui size, unsigned long *C );

/************  Optical Density Y = log10( X0 / X ) *********************/

overror_t  __vcuf OVCUAPI  cudaVUL_ODtoF( fVector OD, ulVector X, ulVector X0, ui size );
overror_t  __vcuf OVCUAPI  cudaVUL_ODtoD( dVector OD, ulVector X, ulVector X0, ui size );
overror_t  __vcuf OVCUAPI  cudaVUL_ODtoFwDark( fVector OD, ulVector X, ulVector XDark,
                          ulVector X0, ulVector X0Dark, ui size );
overror_t  __vcuf OVCUAPI  cudaVUL_ODtoDwDark( dVector OD, ulVector X, ulVector XDark,
                          ulVector X0, ulVector X0Dark, ui size );
void __vcuf OVCUAPI  cudaVUL_setODThresh( unsigned long minX, unsigned long minX0 );

#ifdef __cplusplus
}  // end of extern "C"
#endif


/******************  VULcu_ functions: **********************************
	act on host memory, using the CUDA device for processing
************************************************************************/


#ifdef __cplusplus
   extern "C" {
#endif

/********************  Comparisons ********************************/

ui   __vf OVCUAPI   VULcu_cmp_eq0( ulVector Y, ulVector X, ui size );
ui   __vf OVCUAPI   VULcu_cmp_ne0( ulVector Y, ulVector X, ui size );
ui   __vf OVCUAPI   VULcu_cmp_gt0( ulVector Y, ulVector X, ui size );

ui   __vf OVCUAPI   VULcu_cnt_eq0( ulVector X, ui size );
ui   __vf OVCUAPI   VULcu_cnt_ne0( ulVector X, ui size );
ui   __vf OVCUAPI   VULcu_cnt_gt0( ulVector X, ui size );

void __vf OVCUAPI   VULcu_cmpC(    liVector Y, ulVector X, ui size, unsigned long C );
ui   __vf OVCUAPI   VULcu_cmp_eqC( ulVector Y, ulVector X, ui size, unsigned long C );
ui   __vf OVCUAPI   VULcu_cmp_neC( ulVector Y, ulVector X, ui size, unsigned long C );
ui   __vf OVCUAPI   VULcu_cmp_leC( ulVector Y, ulVector X, ui size, unsigned long C );
ui   __vf OVCUAPI   VULcu_cmp_ltC( ulVector Y, ulVector X, ui size, unsigned long C );
ui   __vf OVCUAPI   VULcu_cmp_geC( ulVector Y, ulVector X, ui size, unsigned long C );
ui   __vf OVCUAPI   VULcu_cmp_gtC( ulVector Y, ulVector X, ui size, unsigned long C );

ui   __vf OVCUAPI   VULcu_cnt_eqC( ulVector X, ui size, unsigned long C );
ui   __vf OVCUAPI   VULcu_cnt_neC( ulVector X, ui size, unsigned long C );
ui   __vf OVCUAPI   VULcu_cnt_leC( ulVector X, ui size, unsigned long C );
ui   __vf OVCUAPI   VULcu_cnt_ltC( ulVector X, ui size, unsigned long C );
ui   __vf OVCUAPI   VULcu_cnt_geC( ulVector X, ui size, unsigned long C );
ui   __vf OVCUAPI   VULcu_cnt_gtC( ulVector X, ui size, unsigned long C );

void __vf OVCUAPI   VULcu_cmpV(    liVector Z, ulVector X, ulVector Y, ui size );
ui   __vf OVCUAPI   VULcu_cmp_eqV( ulVector Z, ulVector X, ulVector Y, ui size );
ui   __vf OVCUAPI   VULcu_cmp_neV( ulVector Z, ulVector X, ulVector Y, ui size );
ui   __vf OVCUAPI   VULcu_cmp_leV( ulVector Z, ulVector X, ulVector Y, ui size );
ui   __vf OVCUAPI   VULcu_cmp_ltV( ulVector Z, ulVector X, ulVector Y, ui size );
ui   __vf OVCUAPI   VULcu_cmp_geV( ulVector Z, ulVector X, ulVector Y, ui size );
ui   __vf OVCUAPI   VULcu_cmp_gtV( ulVector Z, ulVector X, ulVector Y, ui size );

ui   __vf OVCUAPI   VULcu_cnt_eqV( ulVector X, ulVector Y, ui size );
ui   __vf OVCUAPI   VULcu_cnt_neV( ulVector X, ulVector Y, ui size );
ui   __vf OVCUAPI   VULcu_cnt_leV( ulVector X, ulVector Y, ui size );
ui   __vf OVCUAPI   VULcu_cnt_ltV( ulVector X, ulVector Y, ui size );
ui   __vf OVCUAPI   VULcu_cnt_geV( ulVector X, ulVector Y, ui size );
ui   __vf OVCUAPI   VULcu_cnt_gtV( ulVector X, ulVector Y, ui size );

ui   __vf OVCUAPI   VULcu_cmp_exclrange0C( ulVector Y, ulVector X, ui size, unsigned long C );
ui   __vf OVCUAPI   VULcu_cmp_inclrangeCC( ulVector Y, ulVector X, ui size, unsigned long CLo, unsigned long CHi );
ui   __vf OVCUAPI   VULcu_cmp_exclrangeCC( ulVector Y, ulVector X, ui size, unsigned long CLo, unsigned long CHi );

ui   __vf OVCUAPI   VULcu_cnt_exclrange0C( ulVector X, ui size, unsigned long C );
ui   __vf OVCUAPI   VULcu_cnt_inclrangeCC( ulVector X, ui size, unsigned long CLo, unsigned long CHi );
ui   __vf OVCUAPI   VULcu_cnt_exclrangeCC( ulVector X, ui size, unsigned long CLo, unsigned long CHi );

/******************   Basic  Arithmetics   *************************/

void  __vf OVCUAPI   VULcu_addC(  ulVector Y, ulVector X, ui size, unsigned long C );
void  __vf OVCUAPI   VULcu_subC(  ulVector Y, ulVector X, ui size, unsigned long C );
void  __vf OVCUAPI   VULcu_subrC( ulVector Y, ulVector X, ui size, unsigned long C );
void  __vf OVCUAPI   VULcu_mulC(  ulVector Y, ulVector X, ui size, unsigned long C );

void  __vf OVCUAPI   VULcu_divC(  ulVector Y, ulVector X, ui size, unsigned long C );
void  __vf OVCUAPI   VULcu_divrC( ulVector Y, ulVector X, ui size, unsigned long C );
void  __vf OVCUAPI   VULcu_modC(  ulVector Y, ulVector X, ui size, unsigned long C );
void  __vf OVCUAPI   VULcu_maxC(  ulVector Y, ulVector X, ui size, unsigned long C );
void  __vf OVCUAPI   VULcu_minC(  ulVector Y, ulVector X, ui size, unsigned long C );
void  __vf OVCUAPI   VULcu_limit( ulVector Y, ulVector X, ui size, unsigned long Min, unsigned long Max );

void __vf OVCUAPI   VULcu_addV(  ulVector Z, ulVector X, ulVector Y, ui size );
void __vf OVCUAPI   VULcu_subV(  ulVector Z, ulVector X, ulVector Y, ui size );
void __vf OVCUAPI   VULcu_subrV( ulVector Z, ulVector X, ulVector Y, ui size );
void __vf OVCUAPI   VULcu_mulV(  ulVector Z, ulVector X, ulVector Y, ui size );
void    __vf OVCUAPI   VULcu_divV(  ulVector Z, ulVector X, ulVector Y, ui size );
void    __vf OVCUAPI   VULcu_divrV( ulVector Z, ulVector X, ulVector Y, ui size );
void    __vf OVCUAPI   VULcu_modV(  ulVector Z, ulVector X, ulVector Y, ui size );
void    __vf OVCUAPI   VULcu_maxV(  ulVector Z, ulVector X, ulVector Y, ui size );
void    __vf OVCUAPI   VULcu_minV(  ulVector Z, ulVector X, ulVector Y, ui size );

/******************** Accumulation (Y += X) ******************************/

void __vf OVCUAPI  VULcu_accV(   ulVector Y, ulVector  X, ui size );
void __vf OVCUAPI  VULcu_accVUB( ulVector Y, ubVector  X, ui size );
void __vf OVCUAPI  VULcu_accVUS( ulVector Y, usVector  X, ui size );
void __vf OVCUAPI  VULcu_accVU(  ulVector Y, uVector   X, ui size );

/*****************   Bit-wise operations  *********************/

void    __vf OVCUAPI   VULcu_shl( ulVector Y, ulVector X, ui size, unsigned C );
void    __vf OVCUAPI   VULcu_shr( ulVector Y, ulVector X, ui size, unsigned C );

void    __vf OVCUAPI   VULcu_and( ulVector Y, ulVector X, ui size, unsigned long C );
void    __vf OVCUAPI   VULcu_or(  ulVector Y, ulVector X, ui size, unsigned long C );
void    __vf OVCUAPI   VULcu_xor( ulVector Y, ulVector X, ui size, unsigned long C );
void    __vf OVCUAPI   VULcu_not( ulVector Y, ulVector X, ui size );

/************  Optical Density Y = log10( X0 / X ) *********************/

int  __vf OVCUAPI  VULcu_ODtoF( fVector OD, ulVector X, ulVector X0, ui size );
int  __vf OVCUAPI  VULcu_ODtoD( dVector OD, ulVector X, ulVector X0, ui size );
int  __vf OVCUAPI  VULcu_ODtoFwDark( fVector OD, ulVector X, ulVector XDark,
                          ulVector X0, ulVector X0Dark, ui size );
int  __vf OVCUAPI  VULcu_ODtoDwDark( dVector OD, ulVector X, ulVector XDark,
                          ulVector X0, ulVector X0Dark, ui size );
void __vf OVCUAPI  VULcu_setODThresh( unsigned long minX, unsigned long minX0 );

#ifdef __cplusplus
}  // end of extern "C"
#endif

#endif   /*  __CUDAVULMATH_H    */
