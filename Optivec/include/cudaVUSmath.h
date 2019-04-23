/*  cudaVUSmath.h

  vector management functions for data type "unsigned short":
  integer arithmetics and mathematics.

  Copyright (c) 1996-2017 by OptiCode - Dr. Martin Sander Software Dev.
  All Rights Reserved.
*/

#ifndef __CUDAVUSMATH_H
#define __CUDAVUSMATH_H

#if !defined( __CUDAVECLIB_H )
   #include <cudaVecLib.h>
#endif

/******************  cudaVUS_ functions: **********************************
	 act on vectors in CUDA device memory; 
	 scalar parameters and return values on host
******************  cusdVUS_ functions: **********************************
	 also act on vectors in CUDA device memory; 
	 scalar parameters and return values by address on device memory
************************************************************************/

#ifdef __cplusplus
   extern "C" {
#endif

/********************  Comparisons ********************************/

overror_t  __vcuf OVCUAPI   cudaVUS_cmp_eq0( ui *h_nTrue, usVector Y, usVector X, ui size );
overror_t  __vcuf OVCUAPI   cudaVUS_cmp_ne0( ui *h_nTrue, usVector Y, usVector X, ui size );
overror_t  __vcuf OVCUAPI   cudaVUS_cmp_gt0( ui *h_nTrue, usVector Y, usVector X, ui size );

overror_t  __vcuf OVCUAPI   cudaVUS_cmpC(    siVector Y, usVector X, ui size, unsigned short C );
overror_t  __vcuf OVCUAPI   cudaVUS_cmp_eqC( ui *h_nTrue, usVector Y, usVector X, ui size, unsigned short C );
overror_t  __vcuf OVCUAPI   cudaVUS_cmp_neC( ui *h_nTrue, usVector Y, usVector X, ui size, unsigned short C );
overror_t  __vcuf OVCUAPI   cudaVUS_cmp_leC( ui *h_nTrue, usVector Y, usVector X, ui size, unsigned short C );
overror_t  __vcuf OVCUAPI   cudaVUS_cmp_ltC( ui *h_nTrue, usVector Y, usVector X, ui size, unsigned short C );
overror_t  __vcuf OVCUAPI   cudaVUS_cmp_geC( ui *h_nTrue, usVector Y, usVector X, ui size, unsigned short C );
overror_t  __vcuf OVCUAPI   cudaVUS_cmp_gtC( ui *h_nTrue, usVector Y, usVector X, ui size, unsigned short C );
overror_t  __vcuf OVCUAPI   cusdVUS_cmpC(    siVector Y, usVector X, ui size, unsigned short *d_C );
overror_t  __vcuf OVCUAPI   cusdVUS_cmp_eqC( ui *h_nTrue, usVector Y, usVector X, ui size, unsigned short *d_C );
overror_t  __vcuf OVCUAPI   cusdVUS_cmp_neC( ui *h_nTrue, usVector Y, usVector X, ui size, unsigned short *d_C );
overror_t  __vcuf OVCUAPI   cusdVUS_cmp_leC( ui *h_nTrue, usVector Y, usVector X, ui size, unsigned short *d_C );
overror_t  __vcuf OVCUAPI   cusdVUS_cmp_ltC( ui *h_nTrue, usVector Y, usVector X, ui size, unsigned short *d_C );
overror_t  __vcuf OVCUAPI   cusdVUS_cmp_geC( ui *h_nTrue, usVector Y, usVector X, ui size, unsigned short *d_C );
overror_t  __vcuf OVCUAPI   cusdVUS_cmp_gtC( ui *h_nTrue, usVector Y, usVector X, ui size, unsigned short *d_C );

overror_t  __vcuf OVCUAPI   cudaVUS_cmpV(    siVector Z, usVector X, usVector Y, ui size );
overror_t  __vcuf OVCUAPI   cudaVUS_cmp_eqV( ui *h_nTrue, usVector Z, usVector X, usVector Y, ui size );
overror_t  __vcuf OVCUAPI   cudaVUS_cmp_neV( ui *h_nTrue, usVector Z, usVector X, usVector Y, ui size );
overror_t  __vcuf OVCUAPI   cudaVUS_cmp_leV( ui *h_nTrue, usVector Z, usVector X, usVector Y, ui size );
overror_t  __vcuf OVCUAPI   cudaVUS_cmp_ltV( ui *h_nTrue, usVector Z, usVector X, usVector Y, ui size );
overror_t  __vcuf OVCUAPI   cudaVUS_cmp_geV( ui *h_nTrue, usVector Z, usVector X, usVector Y, ui size );
overror_t  __vcuf OVCUAPI   cudaVUS_cmp_gtV( ui *h_nTrue, usVector Z, usVector X, usVector Y, ui size );

overror_t  __vcuf OVCUAPI   cudaVUS_cmp_exclrange0C( ui *h_nTrue, usVector Y, usVector X, ui size, unsigned short C );
overror_t  __vcuf OVCUAPI   cudaVUS_cmp_inclrangeCC( ui *h_nTrue, usVector Y, usVector X, ui size, unsigned short CLo, unsigned short CHi );
overror_t  __vcuf OVCUAPI   cudaVUS_cmp_exclrangeCC( ui *h_nTrue, usVector Y, usVector X, ui size, unsigned short CLo, unsigned short CHi );
overror_t  __vcuf OVCUAPI   cusdVUS_cmp_exclrange0C( ui *h_nTrue, usVector Y, usVector X, ui size, unsigned short *d_C );
overror_t  __vcuf OVCUAPI   cusdVUS_cmp_inclrangeCC( ui *h_nTrue, usVector Y, usVector X, ui size, unsigned short *d_CLo, unsigned short *d_CHi );
overror_t  __vcuf OVCUAPI   cusdVUS_cmp_exclrangeCC( ui *h_nTrue, usVector Y, usVector X, ui size, unsigned short *d_CLo, unsigned short *d_CHi );

overror_t  __vcuf OVCUAPI   cudaVUS_cnt_eq0( ui *h_nTrue, usVector X, ui size );
overror_t  __vcuf OVCUAPI   cudaVUS_cnt_ne0( ui *h_nTrue, usVector X, ui size );
overror_t  __vcuf OVCUAPI   cudaVUS_cnt_gt0( ui *h_nTrue, usVector X, ui size );

overror_t  __vcuf OVCUAPI   cudaVUS_cnt_eqC( ui *h_nTrue, usVector X, ui size, unsigned short C );
overror_t  __vcuf OVCUAPI   cudaVUS_cnt_neC( ui *h_nTrue, usVector X, ui size, unsigned short C );
overror_t  __vcuf OVCUAPI   cudaVUS_cnt_leC( ui *h_nTrue, usVector X, ui size, unsigned short C );
overror_t  __vcuf OVCUAPI   cudaVUS_cnt_ltC( ui *h_nTrue, usVector X, ui size, unsigned short C );
overror_t  __vcuf OVCUAPI   cudaVUS_cnt_geC( ui *h_nTrue, usVector X, ui size, unsigned short C );
overror_t  __vcuf OVCUAPI   cudaVUS_cnt_gtC( ui *h_nTrue, usVector X, ui size, unsigned short C );
overror_t  __vcuf OVCUAPI   cusdVUS_cnt_eqC( ui *h_nTrue, usVector X, ui size, unsigned short *d_C );
overror_t  __vcuf OVCUAPI   cusdVUS_cnt_neC( ui *h_nTrue, usVector X, ui size, unsigned short *d_C );
overror_t  __vcuf OVCUAPI   cusdVUS_cnt_leC( ui *h_nTrue, usVector X, ui size, unsigned short *d_C );
overror_t  __vcuf OVCUAPI   cusdVUS_cnt_ltC( ui *h_nTrue, usVector X, ui size, unsigned short *d_C );
overror_t  __vcuf OVCUAPI   cusdVUS_cnt_geC( ui *h_nTrue, usVector X, ui size, unsigned short *d_C );
overror_t  __vcuf OVCUAPI   cusdVUS_cnt_gtC( ui *h_nTrue, usVector X, ui size, unsigned short *d_C );

overror_t  __vcuf OVCUAPI   cudaVUS_cnt_eqV( ui *h_nTrue, usVector X, usVector Y, ui size );
overror_t  __vcuf OVCUAPI   cudaVUS_cnt_neV( ui *h_nTrue, usVector X, usVector Y, ui size );
overror_t  __vcuf OVCUAPI   cudaVUS_cnt_leV( ui *h_nTrue, usVector X, usVector Y, ui size );
overror_t  __vcuf OVCUAPI   cudaVUS_cnt_ltV( ui *h_nTrue, usVector X, usVector Y, ui size );
overror_t  __vcuf OVCUAPI   cudaVUS_cnt_geV( ui *h_nTrue, usVector X, usVector Y, ui size );
overror_t  __vcuf OVCUAPI   cudaVUS_cnt_gtV( ui *h_nTrue, usVector X, usVector Y, ui size );

overror_t  __vcuf OVCUAPI   cudaVUS_cnt_exclrange0C( ui *h_nTrue, usVector X, ui size, unsigned short C );
overror_t  __vcuf OVCUAPI   cudaVUS_cnt_inclrangeCC( ui *h_nTrue, usVector X, ui size, unsigned short CLo, unsigned short CHi );
overror_t  __vcuf OVCUAPI   cudaVUS_cnt_exclrangeCC( ui *h_nTrue, usVector X, ui size, unsigned short CLo, unsigned short CHi );
overror_t  __vcuf OVCUAPI   cusdVUS_cnt_exclrange0C( ui *h_nTrue, usVector X, ui size, unsigned short *d_C );
overror_t  __vcuf OVCUAPI   cusdVUS_cnt_inclrangeCC( ui *h_nTrue, usVector X, ui size, unsigned short *d_CLo, unsigned short *d_CHi );
overror_t  __vcuf OVCUAPI   cusdVUS_cnt_exclrangeCC( ui *h_nTrue, usVector X, ui size, unsigned short *d_CLo, unsigned short *d_CHi );

/******************   Basic  Arithmetics   *************************/

overror_t  __vcuf OVCUAPI   cudaVUS_addC(  usVector Y, usVector X, ui size, unsigned short C );
overror_t  __vcuf OVCUAPI   cudaVUS_subC(  usVector Y, usVector X, ui size, unsigned short C );
overror_t  __vcuf OVCUAPI   cudaVUS_subrC( usVector Y, usVector X, ui size, unsigned short C );
overror_t  __vcuf OVCUAPI   cudaVUS_mulC(  usVector Y, usVector X, ui size, unsigned short C );

overror_t  __vcuf OVCUAPI   cudaVUS_divC(  usVector Y, usVector X, ui size, unsigned short C );
overror_t  __vcuf OVCUAPI   cudaVUS_divrC( usVector Y, usVector X, ui size, unsigned short C );
overror_t  __vcuf OVCUAPI   cudaVUS_modC(  usVector Y, usVector X, ui size, unsigned short C );
overror_t  __vcuf OVCUAPI   cudaVUS_maxC(  usVector Y, usVector X, ui size, unsigned short C );
overror_t  __vcuf OVCUAPI   cudaVUS_minC(  usVector Y, usVector X, ui size, unsigned short C );
overror_t  __vcuf OVCUAPI   cudaVUS_limit( usVector Y, usVector X, ui size, unsigned short Min, unsigned short Max );

overror_t  __vcuf OVCUAPI   cusdVUS_addC(  usVector Y, usVector X, ui size, unsigned short *C );
overror_t  __vcuf OVCUAPI   cusdVUS_subC(  usVector Y, usVector X, ui size, unsigned short *C );
overror_t  __vcuf OVCUAPI   cusdVUS_subrC( usVector Y, usVector X, ui size, unsigned short *C );
overror_t  __vcuf OVCUAPI   cusdVUS_mulC(  usVector Y, usVector X, ui size, unsigned short *C );

overror_t  __vcuf OVCUAPI   cusdVUS_divC(  usVector Y, usVector X, ui size, unsigned short *C );
overror_t  __vcuf OVCUAPI   cusdVUS_divrC( usVector Y, usVector X, ui size, unsigned short *C );
overror_t  __vcuf OVCUAPI   cusdVUS_modC(  usVector Y, usVector X, ui size, unsigned short *C );
overror_t  __vcuf OVCUAPI   cusdVUS_maxC(  usVector Y, usVector X, ui size, unsigned short *C );
overror_t  __vcuf OVCUAPI   cusdVUS_minC(  usVector Y, usVector X, ui size, unsigned short *C );
overror_t  __vcuf OVCUAPI   cusdVUS_limit( usVector Y, usVector X, ui size, unsigned short *Min, unsigned short *Max );

overror_t  __vcuf OVCUAPI   cudaVUS_addV(  usVector Z, usVector X, usVector Y, ui size );
overror_t  __vcuf OVCUAPI   cudaVUS_subV(  usVector Z, usVector X, usVector Y, ui size );
overror_t  __vcuf OVCUAPI   cudaVUS_subrV( usVector Z, usVector X, usVector Y, ui size );
overror_t  __vcuf OVCUAPI   cudaVUS_mulV(  usVector Z, usVector X, usVector Y, ui size );
overror_t  __vcuf OVCUAPI   cudaVUS_divV(  usVector Z, usVector X, usVector Y, ui size );
overror_t  __vcuf OVCUAPI   cudaVUS_divrV( usVector Z, usVector X, usVector Y, ui size );
overror_t  __vcuf OVCUAPI   cudaVUS_modV(  usVector Z, usVector X, usVector Y, ui size );
overror_t  __vcuf OVCUAPI   cudaVUS_maxV(  usVector Z, usVector X, usVector Y, ui size );
overror_t  __vcuf OVCUAPI   cudaVUS_minV(  usVector Z, usVector X, usVector Y, ui size );


/******************** Accumulation (Y += X) ******************************/

overror_t  __vcuf OVCUAPI  cudaVUS_accV(   usVector Y, usVector  X, ui size );
overror_t  __vcuf OVCUAPI  cudaVUS_accVUB( usVector Y, ubVector  X, ui size );


/*****************   Bit-wise operations  *********************/

overror_t  __vcuf OVCUAPI   cudaVUS_shl( usVector Y, usVector X, ui size, unsigned C );
overror_t  __vcuf OVCUAPI   cudaVUS_shr( usVector Y, usVector X, ui size, unsigned C );

overror_t  __vcuf OVCUAPI   cudaVUS_and( usVector Y, usVector X, ui size, unsigned short C );
overror_t  __vcuf OVCUAPI   cudaVUS_or(  usVector Y, usVector X, ui size, unsigned short C );
overror_t  __vcuf OVCUAPI   cudaVUS_xor( usVector Y, usVector X, ui size, unsigned short C );
overror_t  __vcuf OVCUAPI   cudaVUS_not( usVector Y, usVector X, ui size );

overror_t  __vcuf OVCUAPI   cusdVUS_and( usVector Y, usVector X, ui size, unsigned short *C );
overror_t  __vcuf OVCUAPI   cusdVUS_or(  usVector Y, usVector X, ui size, unsigned short *C );
overror_t  __vcuf OVCUAPI   cusdVUS_xor( usVector Y, usVector X, ui size, unsigned short *C );

/************  Optical Density Y = log10( X0 / X ) *********************/

overror_t  __vcuf OVCUAPI  cudaVUS_ODtoF( fVector OD, usVector X, usVector X0, ui size );
overror_t  __vcuf OVCUAPI  cudaVUS_ODtoD( dVector OD, usVector X, usVector X0, ui size );
overror_t  __vcuf OVCUAPI  cudaVUS_ODtoFwDark( fVector OD, usVector X, usVector XDark,
                          usVector X0, usVector X0Dark, ui size );
overror_t  __vcuf OVCUAPI  cudaVUS_ODtoDwDark( dVector OD, usVector X, usVector XDark,
                          usVector X0, usVector X0Dark, ui size );
void __vcuf OVCUAPI  cudaVUS_setODThresh( unsigned short minX, unsigned short minX0 );

#ifdef __cplusplus
}  // end of extern "C"
#endif


/******************  VUScu_ functions: **********************************
	act on host memory, using the CUDA device for processing
************************************************************************/


#ifdef __cplusplus
   extern "C" {
#endif

/********************  Comparisons ********************************/

ui   __vf OVCUAPI   VUScu_cmp_eq0( usVector Y, usVector X, ui size );
ui   __vf OVCUAPI   VUScu_cmp_ne0( usVector Y, usVector X, ui size );
ui   __vf OVCUAPI   VUScu_cmp_gt0( usVector Y, usVector X, ui size );

ui   __vf OVCUAPI   VUScu_cnt_eq0( usVector X, ui size );
ui   __vf OVCUAPI   VUScu_cnt_ne0( usVector X, ui size );
ui   __vf OVCUAPI   VUScu_cnt_gt0( usVector X, ui size );

void __vf OVCUAPI   VUScu_cmpC(    siVector Y, usVector X, ui size, unsigned short C );
ui   __vf OVCUAPI   VUScu_cmp_eqC( usVector Y, usVector X, ui size, unsigned short C );
ui   __vf OVCUAPI   VUScu_cmp_neC( usVector Y, usVector X, ui size, unsigned short C );
ui   __vf OVCUAPI   VUScu_cmp_leC( usVector Y, usVector X, ui size, unsigned short C );
ui   __vf OVCUAPI   VUScu_cmp_ltC( usVector Y, usVector X, ui size, unsigned short C );
ui   __vf OVCUAPI   VUScu_cmp_geC( usVector Y, usVector X, ui size, unsigned short C );
ui   __vf OVCUAPI   VUScu_cmp_gtC( usVector Y, usVector X, ui size, unsigned short C );

ui   __vf OVCUAPI   VUScu_cnt_eqC( usVector X, ui size, unsigned short C );
ui   __vf OVCUAPI   VUScu_cnt_neC( usVector X, ui size, unsigned short C );
ui   __vf OVCUAPI   VUScu_cnt_leC( usVector X, ui size, unsigned short C );
ui   __vf OVCUAPI   VUScu_cnt_ltC( usVector X, ui size, unsigned short C );
ui   __vf OVCUAPI   VUScu_cnt_geC( usVector X, ui size, unsigned short C );
ui   __vf OVCUAPI   VUScu_cnt_gtC( usVector X, ui size, unsigned short C );

void __vf OVCUAPI   VUScu_cmpV(    siVector Z, usVector X, usVector Y, ui size );
ui   __vf OVCUAPI   VUScu_cmp_eqV( usVector Z, usVector X, usVector Y, ui size );
ui   __vf OVCUAPI   VUScu_cmp_neV( usVector Z, usVector X, usVector Y, ui size );
ui   __vf OVCUAPI   VUScu_cmp_leV( usVector Z, usVector X, usVector Y, ui size );
ui   __vf OVCUAPI   VUScu_cmp_ltV( usVector Z, usVector X, usVector Y, ui size );
ui   __vf OVCUAPI   VUScu_cmp_geV( usVector Z, usVector X, usVector Y, ui size );
ui   __vf OVCUAPI   VUScu_cmp_gtV( usVector Z, usVector X, usVector Y, ui size );

ui   __vf OVCUAPI   VUScu_cnt_eqV( usVector X, usVector Y, ui size );
ui   __vf OVCUAPI   VUScu_cnt_neV( usVector X, usVector Y, ui size );
ui   __vf OVCUAPI   VUScu_cnt_leV( usVector X, usVector Y, ui size );
ui   __vf OVCUAPI   VUScu_cnt_ltV( usVector X, usVector Y, ui size );
ui   __vf OVCUAPI   VUScu_cnt_geV( usVector X, usVector Y, ui size );
ui   __vf OVCUAPI   VUScu_cnt_gtV( usVector X, usVector Y, ui size );

ui   __vf OVCUAPI   VUScu_cmp_exclrange0C( usVector Y, usVector X, ui size, unsigned short C );
ui   __vf OVCUAPI   VUScu_cmp_inclrangeCC( usVector Y, usVector X, ui size, unsigned short CLo, unsigned short CHi );
ui   __vf OVCUAPI   VUScu_cmp_exclrangeCC( usVector Y, usVector X, ui size, unsigned short CLo, unsigned short CHi );

ui   __vf OVCUAPI   VUScu_cnt_exclrange0C( usVector X, ui size, unsigned short C );
ui   __vf OVCUAPI   VUScu_cnt_inclrangeCC( usVector X, ui size, unsigned short CLo, unsigned short CHi );
ui   __vf OVCUAPI   VUScu_cnt_exclrangeCC( usVector X, ui size, unsigned short CLo, unsigned short CHi );

/******************   Basic  Arithmetics   *************************/

void  __vf OVCUAPI   VUScu_addC(  usVector Y, usVector X, ui size, unsigned short C );
void  __vf OVCUAPI   VUScu_subC(  usVector Y, usVector X, ui size, unsigned short C );
void  __vf OVCUAPI   VUScu_subrC( usVector Y, usVector X, ui size, unsigned short C );
void  __vf OVCUAPI   VUScu_mulC(  usVector Y, usVector X, ui size, unsigned short C );

void  __vf OVCUAPI   VUScu_divC(  usVector Y, usVector X, ui size, unsigned short C );
void  __vf OVCUAPI   VUScu_divrC( usVector Y, usVector X, ui size, unsigned short C );
void  __vf OVCUAPI   VUScu_modC(  usVector Y, usVector X, ui size, unsigned short C );
void  __vf OVCUAPI   VUScu_maxC(  usVector Y, usVector X, ui size, unsigned short C );
void  __vf OVCUAPI   VUScu_minC(  usVector Y, usVector X, ui size, unsigned short C );
void  __vf OVCUAPI   VUScu_limit( usVector Y, usVector X, ui size, unsigned short Min, unsigned short Max );

void __vf OVCUAPI   VUScu_addV(  usVector Z, usVector X, usVector Y, ui size );
void __vf OVCUAPI   VUScu_subV(  usVector Z, usVector X, usVector Y, ui size );
void __vf OVCUAPI   VUScu_subrV( usVector Z, usVector X, usVector Y, ui size );
void __vf OVCUAPI   VUScu_mulV(  usVector Z, usVector X, usVector Y, ui size );
void  __vf OVCUAPI   VUScu_divV(  usVector Z, usVector X, usVector Y, ui size );
void  __vf OVCUAPI   VUScu_divrV( usVector Z, usVector X, usVector Y, ui size );
void  __vf OVCUAPI   VUScu_modV(  usVector Z, usVector X, usVector Y, ui size );
void  __vf OVCUAPI   VUScu_maxV(  usVector Z, usVector X, usVector Y, ui size );
void  __vf OVCUAPI   VUScu_minV(  usVector Z, usVector X, usVector Y, ui size );


/******************** Accumulation (Y += X) ******************************/

void __vf OVCUAPI  VUScu_accV(   usVector Y, usVector  X, ui size );
void __vf OVCUAPI  VUScu_accVUB( usVector Y, ubVector  X, ui size );


/*****************   Bit-wise operations  *********************/

void    __vf OVCUAPI   VUScu_shl( usVector Y, usVector X, ui size, unsigned C );
void    __vf OVCUAPI   VUScu_shr( usVector Y, usVector X, ui size, unsigned C );

void    __vf OVCUAPI   VUScu_and( usVector Y, usVector X, ui size, unsigned short C );
void    __vf OVCUAPI   VUScu_or(  usVector Y, usVector X, ui size, unsigned short C );
void    __vf OVCUAPI   VUScu_xor( usVector Y, usVector X, ui size, unsigned short C );
void    __vf OVCUAPI   VUScu_not( usVector Y, usVector X, ui size );

/************  Optical Density Y = log10( X0 / X ) *********************/

int  __vf OVCUAPI  VUScu_ODtoF( fVector OD, usVector X, usVector X0, ui size );
int  __vf OVCUAPI  VUScu_ODtoD( dVector OD, usVector X, usVector X0, ui size );
int  __vf OVCUAPI  VUScu_ODtoFwDark( fVector OD, usVector X, usVector XDark,
                          usVector X0, usVector X0Dark, ui size );
int  __vf OVCUAPI  VUScu_ODtoDwDark( dVector OD, usVector X, usVector XDark,
                          usVector X0, usVector X0Dark, ui size );
void __vf OVCUAPI  VUScu_setODThresh( unsigned short minX, unsigned short minX0 );

#ifdef __cplusplus
}  // end of extern "C"
#endif

#endif   /*  __VUSMATH_H    */
