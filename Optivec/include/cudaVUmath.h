/*  cudaVUmath.h

  vector management functions for data type "unsigned":
  integer arithmetics and mathematics.

  Copyright (c) 1996-2017 by OptiCode - Dr. Martin Sander Software Dev.
  All Rights Reserved.
*/

#ifndef __CUDAVUMATH_H
#define __CUDAVUMATH_H

#if !defined( __CUDAVECLIB_H )
   #include <cudaVecLib.h>
#endif

/******************  cudaVU_ functions: **********************************
	 act on vectors in CUDA device memory; 
	 scalar parameters and return values on host
******************  cusdVU_ functions: **********************************
	 also act on vectors in CUDA device memory; 
	 scalar parameters and return values by address on device memory
************************************************************************/

#ifdef __cplusplus
   extern "C" {
#endif

/********************  Comparisons ********************************/

overror_t  __vcuf OVCUAPI   cudaVU_cmp_eq0( ui *h_nTrue, uVector Y, uVector X, ui size );
overror_t  __vcuf OVCUAPI   cudaVU_cmp_ne0( ui *h_nTrue, uVector Y, uVector X, ui size );
overror_t  __vcuf OVCUAPI   cudaVU_cmp_gt0( ui *h_nTrue, uVector Y, uVector X, ui size );

overror_t  __vcuf OVCUAPI   cudaVU_cmpC(    iVector Y, uVector X, ui size, unsigned C );
overror_t  __vcuf OVCUAPI   cudaVU_cmp_eqC( ui *h_nTrue, uVector Y, uVector X, ui size, unsigned C );
overror_t  __vcuf OVCUAPI   cudaVU_cmp_neC( ui *h_nTrue, uVector Y, uVector X, ui size, unsigned C );
overror_t  __vcuf OVCUAPI   cudaVU_cmp_leC( ui *h_nTrue, uVector Y, uVector X, ui size, unsigned C );
overror_t  __vcuf OVCUAPI   cudaVU_cmp_ltC( ui *h_nTrue, uVector Y, uVector X, ui size, unsigned C );
overror_t  __vcuf OVCUAPI   cudaVU_cmp_geC( ui *h_nTrue, uVector Y, uVector X, ui size, unsigned C );
overror_t  __vcuf OVCUAPI   cudaVU_cmp_gtC( ui *h_nTrue, uVector Y, uVector X, ui size, unsigned C );
overror_t  __vcuf OVCUAPI   cusdVU_cmpC(    iVector Y, uVector X, ui size, unsigned *d_C );
overror_t  __vcuf OVCUAPI   cusdVU_cmp_eqC( ui *h_nTrue, uVector Y, uVector X, ui size, unsigned *d_C );
overror_t  __vcuf OVCUAPI   cusdVU_cmp_neC( ui *h_nTrue, uVector Y, uVector X, ui size, unsigned *d_C );
overror_t  __vcuf OVCUAPI   cusdVU_cmp_leC( ui *h_nTrue, uVector Y, uVector X, ui size, unsigned *d_C );
overror_t  __vcuf OVCUAPI   cusdVU_cmp_ltC( ui *h_nTrue, uVector Y, uVector X, ui size, unsigned *d_C );
overror_t  __vcuf OVCUAPI   cusdVU_cmp_geC( ui *h_nTrue, uVector Y, uVector X, ui size, unsigned *d_C );
overror_t  __vcuf OVCUAPI   cusdVU_cmp_gtC( ui *h_nTrue, uVector Y, uVector X, ui size, unsigned *d_C );

overror_t  __vcuf OVCUAPI   cudaVU_cmpV(    iVector Z, uVector X, uVector Y, ui size );
overror_t  __vcuf OVCUAPI   cudaVU_cmp_eqV( ui *h_nTrue, uVector Z, uVector X, uVector Y, ui size );
overror_t  __vcuf OVCUAPI   cudaVU_cmp_neV( ui *h_nTrue, uVector Z, uVector X, uVector Y, ui size );
overror_t  __vcuf OVCUAPI   cudaVU_cmp_leV( ui *h_nTrue, uVector Z, uVector X, uVector Y, ui size );
overror_t  __vcuf OVCUAPI   cudaVU_cmp_ltV( ui *h_nTrue, uVector Z, uVector X, uVector Y, ui size );
overror_t  __vcuf OVCUAPI   cudaVU_cmp_geV( ui *h_nTrue, uVector Z, uVector X, uVector Y, ui size );
overror_t  __vcuf OVCUAPI   cudaVU_cmp_gtV( ui *h_nTrue, uVector Z, uVector X, uVector Y, ui size );

overror_t  __vcuf OVCUAPI   cudaVU_cmp_exclrange0C( ui *h_nTrue, uVector Y, uVector X, ui size, unsigned C );
overror_t  __vcuf OVCUAPI   cudaVU_cmp_inclrangeCC( ui *h_nTrue, uVector Y, uVector X, ui size, unsigned CLo, unsigned CHi );
overror_t  __vcuf OVCUAPI   cudaVU_cmp_exclrangeCC( ui *h_nTrue, uVector Y, uVector X, ui size, unsigned CLo, unsigned CHi );
overror_t  __vcuf OVCUAPI   cusdVU_cmp_exclrange0C( ui *h_nTrue, uVector Y, uVector X, ui size, unsigned *d_C );
overror_t  __vcuf OVCUAPI   cusdVU_cmp_inclrangeCC( ui *h_nTrue, uVector Y, uVector X, ui size, unsigned *d_CLo, unsigned *d_CHi );
overror_t  __vcuf OVCUAPI   cusdVU_cmp_exclrangeCC( ui *h_nTrue, uVector Y, uVector X, ui size, unsigned *d_CLo, unsigned *d_CHi );

overror_t  __vcuf OVCUAPI   cudaVU_cnt_eq0( ui *h_nTrue, uVector X, ui size );
overror_t  __vcuf OVCUAPI   cudaVU_cnt_ne0( ui *h_nTrue, uVector X, ui size );
overror_t  __vcuf OVCUAPI   cudaVU_cnt_gt0( ui *h_nTrue, uVector X, ui size );

overror_t  __vcuf OVCUAPI   cudaVU_cnt_eqC( ui *h_nTrue, uVector X, ui size, unsigned C );
overror_t  __vcuf OVCUAPI   cudaVU_cnt_neC( ui *h_nTrue, uVector X, ui size, unsigned C );
overror_t  __vcuf OVCUAPI   cudaVU_cnt_leC( ui *h_nTrue, uVector X, ui size, unsigned C );
overror_t  __vcuf OVCUAPI   cudaVU_cnt_ltC( ui *h_nTrue, uVector X, ui size, unsigned C );
overror_t  __vcuf OVCUAPI   cudaVU_cnt_geC( ui *h_nTrue, uVector X, ui size, unsigned C );
overror_t  __vcuf OVCUAPI   cudaVU_cnt_gtC( ui *h_nTrue, uVector X, ui size, unsigned C );
overror_t  __vcuf OVCUAPI   cusdVU_cnt_eqC( ui *h_nTrue, uVector X, ui size, unsigned *d_C );
overror_t  __vcuf OVCUAPI   cusdVU_cnt_neC( ui *h_nTrue, uVector X, ui size, unsigned *d_C );
overror_t  __vcuf OVCUAPI   cusdVU_cnt_leC( ui *h_nTrue, uVector X, ui size, unsigned *d_C );
overror_t  __vcuf OVCUAPI   cusdVU_cnt_ltC( ui *h_nTrue, uVector X, ui size, unsigned *d_C );
overror_t  __vcuf OVCUAPI   cusdVU_cnt_geC( ui *h_nTrue, uVector X, ui size, unsigned *d_C );
overror_t  __vcuf OVCUAPI   cusdVU_cnt_gtC( ui *h_nTrue, uVector X, ui size, unsigned *d_C );

overror_t  __vcuf OVCUAPI   cudaVU_cnt_eqV( ui *h_nTrue, uVector X, uVector Y, ui size );
overror_t  __vcuf OVCUAPI   cudaVU_cnt_neV( ui *h_nTrue, uVector X, uVector Y, ui size );
overror_t  __vcuf OVCUAPI   cudaVU_cnt_leV( ui *h_nTrue, uVector X, uVector Y, ui size );
overror_t  __vcuf OVCUAPI   cudaVU_cnt_ltV( ui *h_nTrue, uVector X, uVector Y, ui size );
overror_t  __vcuf OVCUAPI   cudaVU_cnt_geV( ui *h_nTrue, uVector X, uVector Y, ui size );
overror_t  __vcuf OVCUAPI   cudaVU_cnt_gtV( ui *h_nTrue, uVector X, uVector Y, ui size );

overror_t  __vcuf OVCUAPI   cudaVU_cnt_exclrange0C( ui *h_nTrue, uVector X, ui size, unsigned C );
overror_t  __vcuf OVCUAPI   cudaVU_cnt_inclrangeCC( ui *h_nTrue, uVector X, ui size, unsigned CLo, unsigned CHi );
overror_t  __vcuf OVCUAPI   cudaVU_cnt_exclrangeCC( ui *h_nTrue, uVector X, ui size, unsigned CLo, unsigned CHi );
overror_t  __vcuf OVCUAPI   cusdVU_cnt_exclrange0C( ui *h_nTrue, uVector X, ui size, unsigned *d_C );
overror_t  __vcuf OVCUAPI   cusdVU_cnt_inclrangeCC( ui *h_nTrue, uVector X, ui size, unsigned *d_CLo, unsigned *d_CHi );
overror_t  __vcuf OVCUAPI   cusdVU_cnt_exclrangeCC( ui *h_nTrue, uVector X, ui size, unsigned *d_CLo, unsigned *d_CHi );

/******************   Basic  Arithmetics   *************************/

overror_t  __vcuf OVCUAPI   cudaVU_addC(  uVector Y, uVector X, ui size, unsigned C );
overror_t  __vcuf OVCUAPI   cudaVU_subC(  uVector Y, uVector X, ui size, unsigned C );
overror_t  __vcuf OVCUAPI   cudaVU_subrC( uVector Y, uVector X, ui size, unsigned C );
overror_t  __vcuf OVCUAPI   cudaVU_mulC(  uVector Y, uVector X, ui size, unsigned C );

overror_t  __vcuf OVCUAPI   cudaVU_divC(  uVector Y, uVector X, ui size, unsigned C );
overror_t  __vcuf OVCUAPI   cudaVU_divrC( uVector Y, uVector X, ui size, unsigned C );
overror_t  __vcuf OVCUAPI   cudaVU_modC(  uVector Y, uVector X, ui size, unsigned C );
overror_t  __vcuf OVCUAPI   cudaVU_maxC(  uVector Y, uVector X, ui size, unsigned C );
overror_t  __vcuf OVCUAPI   cudaVU_minC(  uVector Y, uVector X, ui size, unsigned C );
overror_t  __vcuf OVCUAPI   cudaVU_limit( uVector Y, uVector X, ui size, unsigned Min, unsigned Max );

overror_t  __vcuf OVCUAPI   cusdVU_addC(  uVector Y, uVector X, ui size, unsigned *C );
overror_t  __vcuf OVCUAPI   cusdVU_subC(  uVector Y, uVector X, ui size, unsigned *C );
overror_t  __vcuf OVCUAPI   cusdVU_subrC( uVector Y, uVector X, ui size, unsigned *C );
overror_t  __vcuf OVCUAPI   cusdVU_mulC(  uVector Y, uVector X, ui size, unsigned *C );

overror_t  __vcuf OVCUAPI   cusdVU_divC(  uVector Y, uVector X, ui size, unsigned *C );
overror_t  __vcuf OVCUAPI   cusdVU_divrC( uVector Y, uVector X, ui size, unsigned *C );
overror_t  __vcuf OVCUAPI   cusdVU_modC(  uVector Y, uVector X, ui size, unsigned *C );
overror_t  __vcuf OVCUAPI   cusdVU_maxC(  uVector Y, uVector X, ui size, unsigned *C );
overror_t  __vcuf OVCUAPI   cusdVU_minC(  uVector Y, uVector X, ui size, unsigned *C );
overror_t  __vcuf OVCUAPI   cusdVU_limit( uVector Y, uVector X, ui size, unsigned *Min, unsigned *Max );

overror_t  __vcuf OVCUAPI   cudaVU_addV(  uVector Z, uVector X, uVector Y, ui size );
overror_t  __vcuf OVCUAPI   cudaVU_subV(  uVector Z, uVector X, uVector Y, ui size );
overror_t  __vcuf OVCUAPI   cudaVU_subrV( uVector Z, uVector X, uVector Y, ui size );
overror_t  __vcuf OVCUAPI   cudaVU_mulV(  uVector Z, uVector X, uVector Y, ui size );
overror_t  __vcuf OVCUAPI   cudaVU_divV(  uVector Z, uVector X, uVector Y, ui size );
overror_t  __vcuf OVCUAPI   cudaVU_divrV( uVector Z, uVector X, uVector Y, ui size );
overror_t  __vcuf OVCUAPI   cudaVU_modV(  uVector Z, uVector X, uVector Y, ui size );
overror_t  __vcuf OVCUAPI   cudaVU_maxV(  uVector Z, uVector X, uVector Y, ui size );
overror_t  __vcuf OVCUAPI   cudaVU_minV(  uVector Z, uVector X, uVector Y, ui size );

/******************** Accumulation (Y += X) ******************************/

overror_t  __vcuf OVCUAPI  cudaVU_accV(   uVector Y, uVector   X, ui size );
overror_t  __vcuf OVCUAPI  cudaVU_accVUB( uVector Y, ubVector  X, ui size );
overror_t  __vcuf OVCUAPI  cudaVU_accVUS( uVector Y, usVector  X, ui size );


/*****************   Bit-wise operations  *********************/

overror_t  __vcuf OVCUAPI   cudaVU_shl( uVector Y, uVector X, ui size, unsigned C );
overror_t  __vcuf OVCUAPI   cudaVU_shr( uVector Y, uVector X, ui size, unsigned C );

overror_t  __vcuf OVCUAPI   cudaVU_and( uVector Y, uVector X, ui size, unsigned C );
overror_t  __vcuf OVCUAPI   cudaVU_or(  uVector Y, uVector X, ui size, unsigned C );
overror_t  __vcuf OVCUAPI   cudaVU_xor( uVector Y, uVector X, ui size, unsigned C );
overror_t  __vcuf OVCUAPI   cudaVU_not( uVector Y, uVector X, ui size );

overror_t  __vcuf OVCUAPI   cusdVU_and( uVector Y, uVector X, ui size, unsigned *C );
overror_t  __vcuf OVCUAPI   cusdVU_or(  uVector Y, uVector X, ui size, unsigned *C );
overror_t  __vcuf OVCUAPI   cusdVU_xor( uVector Y, uVector X, ui size, unsigned *C );

/************  Optical Density Y = log10( X0 / X ) *********************/

overror_t  __vcuf OVCUAPI  cudaVU_ODtoF( fVector OD, uVector X, uVector X0, ui size );
overror_t  __vcuf OVCUAPI  cudaVU_ODtoD( dVector OD, uVector X, uVector X0, ui size );
overror_t  __vcuf OVCUAPI  cudaVU_ODtoFwDark( fVector OD, uVector X, uVector XDark,
                         uVector X0, uVector X0Dark, ui size );
overror_t  __vcuf OVCUAPI  cudaVU_ODtoDwDark( dVector OD, uVector X, uVector XDark,
                         uVector X0, uVector X0Dark, ui size );
void __vcuf OVCUAPI  cudaVU_setODThresh( unsigned minX, unsigned minX0 );

#ifdef __cplusplus
}  // end of extern "C"
#endif


/******************  VUcu_ functions: **********************************
	act on host memory, using the CUDA device for processing
************************************************************************/

#ifdef __cplusplus
   extern "C" {
#endif

/********************  Comparisons ********************************/

ui   __vf OVCUAPI   VUcu_cmp_eq0( uVector Y, uVector X, ui size );
ui   __vf OVCUAPI   VUcu_cmp_ne0( uVector Y, uVector X, ui size );
ui   __vf OVCUAPI   VUcu_cmp_gt0( uVector Y, uVector X, ui size );

ui   __vf OVCUAPI   VUcu_cnt_eq0( uVector X, ui size );
ui   __vf OVCUAPI   VUcu_cnt_ne0( uVector X, ui size );
ui   __vf OVCUAPI   VUcu_cnt_gt0( uVector X, ui size );

void __vf OVCUAPI   VUcu_cmpC(    iVector Y, uVector X, ui size, unsigned int C );
ui   __vf OVCUAPI   VUcu_cmp_eqC( uVector Y, uVector X, ui size, unsigned int C );
ui   __vf OVCUAPI   VUcu_cmp_neC( uVector Y, uVector X, ui size, unsigned int C );
ui   __vf OVCUAPI   VUcu_cmp_leC( uVector Y, uVector X, ui size, unsigned int C );
ui   __vf OVCUAPI   VUcu_cmp_ltC( uVector Y, uVector X, ui size, unsigned int C );
ui   __vf OVCUAPI   VUcu_cmp_geC( uVector Y, uVector X, ui size, unsigned int C );
ui   __vf OVCUAPI   VUcu_cmp_gtC( uVector Y, uVector X, ui size, unsigned int C );

ui   __vf OVCUAPI   VUcu_cnt_eqC( uVector X, ui size, unsigned int C );
ui   __vf OVCUAPI   VUcu_cnt_neC( uVector X, ui size, unsigned int C );
ui   __vf OVCUAPI   VUcu_cnt_leC( uVector X, ui size, unsigned int C );
ui   __vf OVCUAPI   VUcu_cnt_ltC( uVector X, ui size, unsigned int C );
ui   __vf OVCUAPI   VUcu_cnt_geC( uVector X, ui size, unsigned int C );
ui   __vf OVCUAPI   VUcu_cnt_gtC( uVector X, ui size, unsigned int C );

void __vf OVCUAPI   VUcu_cmpV(    iVector Z, uVector X, uVector Y, ui size );
ui   __vf OVCUAPI   VUcu_cmp_eqV( uVector Z, uVector X, uVector Y, ui size );
ui   __vf OVCUAPI   VUcu_cmp_neV( uVector Z, uVector X, uVector Y, ui size );
ui   __vf OVCUAPI   VUcu_cmp_leV( uVector Z, uVector X, uVector Y, ui size );
ui   __vf OVCUAPI   VUcu_cmp_ltV( uVector Z, uVector X, uVector Y, ui size );
ui   __vf OVCUAPI   VUcu_cmp_geV( uVector Z, uVector X, uVector Y, ui size );
ui   __vf OVCUAPI   VUcu_cmp_gtV( uVector Z, uVector X, uVector Y, ui size );

ui   __vf OVCUAPI   VUcu_cnt_eqV( uVector X, uVector Y, ui size );
ui   __vf OVCUAPI   VUcu_cnt_neV( uVector X, uVector Y, ui size );
ui   __vf OVCUAPI   VUcu_cnt_leV( uVector X, uVector Y, ui size );
ui   __vf OVCUAPI   VUcu_cnt_ltV( uVector X, uVector Y, ui size );
ui   __vf OVCUAPI   VUcu_cnt_geV( uVector X, uVector Y, ui size );
ui   __vf OVCUAPI   VUcu_cnt_gtV( uVector X, uVector Y, ui size );

ui   __vf OVCUAPI   VUcu_cmp_exclrange0C( uVector Y, uVector X, ui size, unsigned int C );
ui   __vf OVCUAPI   VUcu_cmp_inclrangeCC( uVector Y, uVector X, ui size, unsigned int CLo, unsigned int CHi );
ui   __vf OVCUAPI   VUcu_cmp_exclrangeCC( uVector Y, uVector X, ui size, unsigned int CLo, unsigned int CHi );

ui   __vf OVCUAPI   VUcu_cnt_exclrange0C( uVector X, ui size, unsigned int C );
ui   __vf OVCUAPI   VUcu_cnt_inclrangeCC( uVector X, ui size, unsigned int CLo, unsigned int CHi );
ui   __vf OVCUAPI   VUcu_cnt_exclrangeCC( uVector X, ui size, unsigned int CLo, unsigned int CHi );

/******************   Basic  Arithmetics   *************************/

void  __vf OVCUAPI   VUcu_addC(  uVector Y, uVector X, ui size, unsigned C );
void  __vf OVCUAPI   VUcu_subC(  uVector Y, uVector X, ui size, unsigned C );
void  __vf OVCUAPI   VUcu_subrC( uVector Y, uVector X, ui size, unsigned C );
void  __vf OVCUAPI   VUcu_mulC(  uVector Y, uVector X, ui size, unsigned C );

void  __vf OVCUAPI   VUcu_divC(  uVector Y, uVector X, ui size, unsigned C );
void  __vf OVCUAPI   VUcu_divrC( uVector Y, uVector X, ui size, unsigned C );
void  __vf OVCUAPI   VUcu_modC(  uVector Y, uVector X, ui size, unsigned C );
void  __vf OVCUAPI   VUcu_maxC(  uVector Y, uVector X, ui size, unsigned C );
void  __vf OVCUAPI   VUcu_minC(  uVector Y, uVector X, ui size, unsigned C );
void  __vf OVCUAPI   VUcu_limit( uVector Y, uVector X, ui size, unsigned Min, unsigned Max );

void __vf OVCUAPI   VUcu_addV(  uVector Z, uVector X, uVector Y, ui size );
void __vf OVCUAPI   VUcu_subV(  uVector Z, uVector X, uVector Y, ui size );
void __vf OVCUAPI   VUcu_subrV( uVector Z, uVector X, uVector Y, ui size );
void __vf OVCUAPI   VUcu_mulV(  uVector Z, uVector X, uVector Y, ui size );
void __vf OVCUAPI   VUcu_divV(  uVector Z, uVector X, uVector Y, ui size );
void __vf OVCUAPI   VUcu_divrV( uVector Z, uVector X, uVector Y, ui size );
void __vf OVCUAPI   VUcu_modV(  uVector Z, uVector X, uVector Y, ui size );
void __vf OVCUAPI   VUcu_maxV(  uVector Z, uVector X, uVector Y, ui size );
void __vf OVCUAPI   VUcu_minV(  uVector Z, uVector X, uVector Y, ui size );

/******************** Accumulation (Y += X) ******************************/

void __vf OVCUAPI  VUcu_accV(   uVector Y, uVector   X, ui size );
void __vf OVCUAPI  VUcu_accVUB( uVector Y, ubVector  X, ui size );
void __vf OVCUAPI  VUcu_accVUS( uVector Y, usVector  X, ui size );


/*****************   Bit-wise operations  *********************/

void    __vf OVCUAPI   VUcu_shl( uVector Y, uVector X, ui size, unsigned C );
void    __vf OVCUAPI   VUcu_shr( uVector Y, uVector X, ui size, unsigned C );

void    __vf OVCUAPI   VUcu_and( uVector Y, uVector X, ui size, unsigned C );
void    __vf OVCUAPI   VUcu_or(  uVector Y, uVector X, ui size, unsigned C );
void    __vf OVCUAPI   VUcu_xor( uVector Y, uVector X, ui size, unsigned C );
void    __vf OVCUAPI   VUcu_not( uVector Y, uVector X, ui size );

/************  Optical Density Y = log10( X0 / X ) *********************/

int  __vf OVCUAPI  VUcu_ODtoF( fVector OD, uVector X, uVector X0, ui size );
int  __vf OVCUAPI  VUcu_ODtoD( dVector OD, uVector X, uVector X0, ui size );
int  __vf OVCUAPI  VUcu_ODtoFwDark( fVector OD, uVector X, uVector XDark,
                         uVector X0, uVector X0Dark, ui size );
int  __vf OVCUAPI  VUcu_ODtoDwDark( dVector OD, uVector X, uVector XDark,
                         uVector X0, uVector X0Dark, ui size );
void __vf OVCUAPI  VUcu_setODThresh( unsigned minX, unsigned minX0 );

#ifdef __cplusplus
}  // end of extern "C"
#endif


#endif   /*  __CUDAVUMATH_H    */
