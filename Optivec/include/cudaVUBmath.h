/*  cudaVUBmath.h


  vector management functions for unsigned byte-sized integers:
  integer arithmetics and mathematics.

  Copyright (c) 1996-2017 by OptiCode - Dr. Martin Sander Software Dev.
  All Rights Reserved.
*/

#ifndef __CUDAVUBMATH_H
#define __CUDAVUBMATH_H

#if !defined( __CUDAVECLIB_H )
   #include <cudaVecLib.h>
#endif

/******************  cudaVUB_ functions: **********************************
	 act on vectors in CUDA device memory; 
	 scalar parameters and return values on host
******************  cusdVUB_ functions: **********************************
	 also act on vectors in CUDA device memory; 
	 scalar parameters and return values by address on device memory
************************************************************************/

#ifdef __cplusplus
   extern "C" {
#endif

/********************  Comparisons ********************************/

overror_t  __vcuf OVCUAPI   cudaVUB_cmp_eq0( ui *h_nTrue, ubVector Y, ubVector X, ui size );
overror_t  __vcuf OVCUAPI   cudaVUB_cmp_ne0( ui *h_nTrue, ubVector Y, ubVector X, ui size );
overror_t  __vcuf OVCUAPI   cudaVUB_cmp_gt0( ui *h_nTrue, ubVector Y, ubVector X, ui size );

overror_t  __vcuf OVCUAPI   cudaVUB_cmpC(    biVector Y, ubVector X, ui size, unsigned char C );
overror_t  __vcuf OVCUAPI   cudaVUB_cmp_eqC( ui *h_nTrue, ubVector Y, ubVector X, ui size, unsigned char C );
overror_t  __vcuf OVCUAPI   cudaVUB_cmp_neC( ui *h_nTrue, ubVector Y, ubVector X, ui size, unsigned char C );
overror_t  __vcuf OVCUAPI   cudaVUB_cmp_leC( ui *h_nTrue, ubVector Y, ubVector X, ui size, unsigned char C );
overror_t  __vcuf OVCUAPI   cudaVUB_cmp_ltC( ui *h_nTrue, ubVector Y, ubVector X, ui size, unsigned char C );
overror_t  __vcuf OVCUAPI   cudaVUB_cmp_geC( ui *h_nTrue, ubVector Y, ubVector X, ui size, unsigned char C );
overror_t  __vcuf OVCUAPI   cudaVUB_cmp_gtC( ui *h_nTrue, ubVector Y, ubVector X, ui size, unsigned char C );
overror_t  __vcuf OVCUAPI   cusdVUB_cmpC(    biVector Y, ubVector X, ui size, unsigned char *d_C );
overror_t  __vcuf OVCUAPI   cusdVUB_cmp_eqC( ui *h_nTrue, ubVector Y, ubVector X, ui size, unsigned char *d_C );
overror_t  __vcuf OVCUAPI   cusdVUB_cmp_neC( ui *h_nTrue, ubVector Y, ubVector X, ui size, unsigned char *d_C );
overror_t  __vcuf OVCUAPI   cusdVUB_cmp_leC( ui *h_nTrue, ubVector Y, ubVector X, ui size, unsigned char *d_C );
overror_t  __vcuf OVCUAPI   cusdVUB_cmp_ltC( ui *h_nTrue, ubVector Y, ubVector X, ui size, unsigned char *d_C );
overror_t  __vcuf OVCUAPI   cusdVUB_cmp_geC( ui *h_nTrue, ubVector Y, ubVector X, ui size, unsigned char *d_C );
overror_t  __vcuf OVCUAPI   cusdVUB_cmp_gtC( ui *h_nTrue, ubVector Y, ubVector X, ui size, unsigned char *d_C );

overror_t  __vcuf OVCUAPI   cudaVUB_cmpV(    biVector Z, ubVector X, ubVector Y, ui size );
overror_t  __vcuf OVCUAPI   cudaVUB_cmp_eqV( ui *h_nTrue, ubVector Z, ubVector X, ubVector Y, ui size );
overror_t  __vcuf OVCUAPI   cudaVUB_cmp_neV( ui *h_nTrue, ubVector Z, ubVector X, ubVector Y, ui size );
overror_t  __vcuf OVCUAPI   cudaVUB_cmp_leV( ui *h_nTrue, ubVector Z, ubVector X, ubVector Y, ui size );
overror_t  __vcuf OVCUAPI   cudaVUB_cmp_ltV( ui *h_nTrue, ubVector Z, ubVector X, ubVector Y, ui size );
overror_t  __vcuf OVCUAPI   cudaVUB_cmp_geV( ui *h_nTrue, ubVector Z, ubVector X, ubVector Y, ui size );
overror_t  __vcuf OVCUAPI   cudaVUB_cmp_gtV( ui *h_nTrue, ubVector Z, ubVector X, ubVector Y, ui size );

overror_t  __vcuf OVCUAPI   cudaVUB_cmp_exclrange0C( ui *h_nTrue, ubVector Y, ubVector X, ui size, unsigned char C );
overror_t  __vcuf OVCUAPI   cudaVUB_cmp_inclrangeCC( ui *h_nTrue, ubVector Y, ubVector X, ui size, unsigned char CLo, unsigned char CHi );
overror_t  __vcuf OVCUAPI   cudaVUB_cmp_exclrangeCC( ui *h_nTrue, ubVector Y, ubVector X, ui size, unsigned char CLo, unsigned char CHi );
overror_t  __vcuf OVCUAPI   cusdVUB_cmp_exclrange0C( ui *h_nTrue, ubVector Y, ubVector X, ui size, unsigned char *d_C );
overror_t  __vcuf OVCUAPI   cusdVUB_cmp_inclrangeCC( ui *h_nTrue, ubVector Y, ubVector X, ui size, unsigned char *d_CLo, unsigned char *d_CHi );
overror_t  __vcuf OVCUAPI   cusdVUB_cmp_exclrangeCC( ui *h_nTrue, ubVector Y, ubVector X, ui size, unsigned char *d_CLo, unsigned char *d_CHi );

overror_t  __vcuf OVCUAPI   cudaVUB_cnt_eq0( ui *h_nTrue, ubVector X, ui size );
overror_t  __vcuf OVCUAPI   cudaVUB_cnt_ne0( ui *h_nTrue, ubVector X, ui size );
overror_t  __vcuf OVCUAPI   cudaVUB_cnt_gt0( ui *h_nTrue, ubVector X, ui size );

overror_t  __vcuf OVCUAPI   cudaVUB_cnt_eqC( ui *h_nTrue, ubVector X, ui size, unsigned char C );
overror_t  __vcuf OVCUAPI   cudaVUB_cnt_neC( ui *h_nTrue, ubVector X, ui size, unsigned char C );
overror_t  __vcuf OVCUAPI   cudaVUB_cnt_leC( ui *h_nTrue, ubVector X, ui size, unsigned char C );
overror_t  __vcuf OVCUAPI   cudaVUB_cnt_ltC( ui *h_nTrue, ubVector X, ui size, unsigned char C );
overror_t  __vcuf OVCUAPI   cudaVUB_cnt_geC( ui *h_nTrue, ubVector X, ui size, unsigned char C );
overror_t  __vcuf OVCUAPI   cudaVUB_cnt_gtC( ui *h_nTrue, ubVector X, ui size, unsigned char C );
overror_t  __vcuf OVCUAPI   cusdVUB_cnt_eqC( ui *h_nTrue, ubVector X, ui size, unsigned char *d_C );
overror_t  __vcuf OVCUAPI   cusdVUB_cnt_neC( ui *h_nTrue, ubVector X, ui size, unsigned char *d_C );
overror_t  __vcuf OVCUAPI   cusdVUB_cnt_leC( ui *h_nTrue, ubVector X, ui size, unsigned char *d_C );
overror_t  __vcuf OVCUAPI   cusdVUB_cnt_ltC( ui *h_nTrue, ubVector X, ui size, unsigned char *d_C );
overror_t  __vcuf OVCUAPI   cusdVUB_cnt_geC( ui *h_nTrue, ubVector X, ui size, unsigned char *d_C );
overror_t  __vcuf OVCUAPI   cusdVUB_cnt_gtC( ui *h_nTrue, ubVector X, ui size, unsigned char *d_C );

overror_t  __vcuf OVCUAPI   cudaVUB_cnt_eqV( ui *h_nTrue, ubVector X, ubVector Y, ui size );
overror_t  __vcuf OVCUAPI   cudaVUB_cnt_neV( ui *h_nTrue, ubVector X, ubVector Y, ui size );
overror_t  __vcuf OVCUAPI   cudaVUB_cnt_leV( ui *h_nTrue, ubVector X, ubVector Y, ui size );
overror_t  __vcuf OVCUAPI   cudaVUB_cnt_ltV( ui *h_nTrue, ubVector X, ubVector Y, ui size );
overror_t  __vcuf OVCUAPI   cudaVUB_cnt_geV( ui *h_nTrue, ubVector X, ubVector Y, ui size );
overror_t  __vcuf OVCUAPI   cudaVUB_cnt_gtV( ui *h_nTrue, ubVector X, ubVector Y, ui size );

overror_t  __vcuf OVCUAPI   cudaVUB_cnt_exclrange0C( ui *h_nTrue, ubVector X, ui size, unsigned char C );
overror_t  __vcuf OVCUAPI   cudaVUB_cnt_inclrangeCC( ui *h_nTrue, ubVector X, ui size, unsigned char CLo, unsigned char CHi );
overror_t  __vcuf OVCUAPI   cudaVUB_cnt_exclrangeCC( ui *h_nTrue, ubVector X, ui size, unsigned char CLo, unsigned char CHi );
overror_t  __vcuf OVCUAPI   cusdVUB_cnt_exclrange0C( ui *h_nTrue, ubVector X, ui size, unsigned char *d_C );
overror_t  __vcuf OVCUAPI   cusdVUB_cnt_inclrangeCC( ui *h_nTrue, ubVector X, ui size, unsigned char *d_CLo, unsigned char *d_CHi );
overror_t  __vcuf OVCUAPI   cusdVUB_cnt_exclrangeCC( ui *h_nTrue, ubVector X, ui size, unsigned char *d_CLo, unsigned char *d_CHi );

/******************   Basic  Arithmetics   *************************/

overror_t  __vcuf OVCUAPI   cudaVUB_addC(  ubVector Y, ubVector X, ui size, unsigned char C );
overror_t  __vcuf OVCUAPI   cudaVUB_subC(  ubVector Y, ubVector X, ui size, unsigned char C );
overror_t  __vcuf OVCUAPI   cudaVUB_subrC( ubVector Y, ubVector X, ui size, unsigned char C );
overror_t  __vcuf OVCUAPI   cudaVUB_mulC(  ubVector Y, ubVector X, ui size, unsigned char C );
overror_t  __vcuf OVCUAPI   cudaVUB_divC(  ubVector Y, ubVector X, ui size, unsigned char C );
overror_t  __vcuf OVCUAPI   cudaVUB_divrC( ubVector Y, ubVector X, ui size, unsigned char C );
overror_t  __vcuf OVCUAPI   cudaVUB_modC(  ubVector Y, ubVector X, ui size, unsigned char C );
overror_t  __vcuf OVCUAPI   cudaVUB_maxC(  ubVector Y, ubVector X, ui size, unsigned char C );
overror_t  __vcuf OVCUAPI   cudaVUB_minC(  ubVector Y, ubVector X, ui size, unsigned char C );
overror_t  __vcuf OVCUAPI   cudaVUB_limit( ubVector Y, ubVector X, ui size, unsigned char Min, unsigned char Max );

overror_t  __vcuf OVCUAPI   cusdVUB_addC(  ubVector Y, ubVector X, ui size, unsigned char *C );
overror_t  __vcuf OVCUAPI   cusdVUB_subC(  ubVector Y, ubVector X, ui size, unsigned char *C );
overror_t  __vcuf OVCUAPI   cusdVUB_subrC( ubVector Y, ubVector X, ui size, unsigned char *C );
overror_t  __vcuf OVCUAPI   cusdVUB_mulC(  ubVector Y, ubVector X, ui size, unsigned char *C );
overror_t  __vcuf OVCUAPI   cusdVUB_divC(  ubVector Y, ubVector X, ui size, unsigned char *C );
overror_t  __vcuf OVCUAPI   cusdVUB_divrC( ubVector Y, ubVector X, ui size, unsigned char *C );
overror_t  __vcuf OVCUAPI   cusdVUB_modC(  ubVector Y, ubVector X, ui size, unsigned char *C );
overror_t  __vcuf OVCUAPI   cusdVUB_maxC(  ubVector Y, ubVector X, ui size, unsigned char *C );
overror_t  __vcuf OVCUAPI   cusdVUB_minC(  ubVector Y, ubVector X, ui size, unsigned char *C );
overror_t  __vcuf OVCUAPI   cusdVUB_limit( ubVector Y, ubVector X, ui size, unsigned char *Min, unsigned char *Max );

overror_t  __vcuf OVCUAPI   cudaVUB_addV(  ubVector Z, ubVector X, ubVector Y, ui size );
overror_t  __vcuf OVCUAPI   cudaVUB_subV(  ubVector Z, ubVector X, ubVector Y, ui size );
overror_t  __vcuf OVCUAPI   cudaVUB_subrV( ubVector Z, ubVector X, ubVector Y, ui size );
overror_t  __vcuf OVCUAPI   cudaVUB_mulV(  ubVector Z, ubVector X, ubVector Y, ui size );
overror_t  __vcuf OVCUAPI   cudaVUB_divV(  ubVector Z, ubVector X, ubVector Y, ui size );
overror_t  __vcuf OVCUAPI   cudaVUB_divrV( ubVector Z, ubVector X, ubVector Y, ui size );
overror_t  __vcuf OVCUAPI   cudaVUB_modV(  ubVector Z, ubVector X, ubVector Y, ui size );
overror_t  __vcuf OVCUAPI   cudaVUB_maxV(  ubVector Z, ubVector X, ubVector Y, ui size );
overror_t  __vcuf OVCUAPI   cudaVUB_minV(  ubVector Z, ubVector X, ubVector Y, ui size );

/******************** Accumulation (Y += X) ******************************/

overror_t  __vcuf OVCUAPI  cudaVUB_accV(   ubVector Y, ubVector  X, ui size );


/*****************   Bit-wise operations  *********************/

overror_t  __vcuf OVCUAPI   cudaVUB_shl( ubVector Y, ubVector X, ui size, unsigned C );
overror_t  __vcuf OVCUAPI   cudaVUB_shr( ubVector Y, ubVector X, ui size, unsigned C );

overror_t  __vcuf OVCUAPI   cudaVUB_and( ubVector Y, ubVector X, ui size, unsigned char C );
overror_t  __vcuf OVCUAPI   cudaVUB_or(  ubVector Y, ubVector X, ui size, unsigned char C );
overror_t  __vcuf OVCUAPI   cudaVUB_xor( ubVector Y, ubVector X, ui size, unsigned char C );
overror_t  __vcuf OVCUAPI   cudaVUB_not( ubVector Y, ubVector X, ui size );

overror_t  __vcuf OVCUAPI   cusdVUB_and( ubVector Y, ubVector X, ui size, unsigned char *C );
overror_t  __vcuf OVCUAPI   cusdVUB_or(  ubVector Y, ubVector X, ui size, unsigned char *C );
overror_t  __vcuf OVCUAPI   cusdVUB_xor( ubVector Y, ubVector X, ui size, unsigned char *C );

/************  Optical Density Y = log10( X0 / X ) *********************/

overror_t  __vcuf OVCUAPI  cudaVUB_ODtoF( fVector OD, ubVector X, ubVector X0, ui size );
overror_t  __vcuf OVCUAPI  cudaVUB_ODtoD( dVector OD, ubVector X, ubVector X0, ui size );
overror_t  __vcuf OVCUAPI  cudaVUB_ODtoFwDark( fVector OD, ubVector X, ubVector XDark,
                          ubVector X0, ubVector X0Dark, ui size );
overror_t  __vcuf OVCUAPI  cudaVUB_ODtoDwDark( dVector OD, ubVector X, ubVector XDark,
                          ubVector X0, ubVector X0Dark, ui size );
void  __vcuf OVCUAPI  cudaVUB_setODThresh( unsigned char minX, unsigned char minX0 );

#ifdef __cplusplus
}  // end of extern "C"
#endif


/******************  VUBcu_ functions: **********************************
	act on host memory, using the CUDA device for processing
************************************************************************/


#ifdef __cplusplus
   extern "C" {
#endif

/********************  Comparisons ********************************/

ui   __vf OVCUAPI   VUBcu_cmp_eq0( ubVector Y, ubVector X, ui size );
ui   __vf OVCUAPI   VUBcu_cmp_ne0( ubVector Y, ubVector X, ui size );
ui   __vf OVCUAPI   VUBcu_cmp_gt0( ubVector Y, ubVector X, ui size );

ui   __vf OVCUAPI   VUBcu_cnt_eq0( ubVector X, ui size );
ui   __vf OVCUAPI   VUBcu_cnt_ne0( ubVector X, ui size );
ui   __vf OVCUAPI   VUBcu_cnt_gt0( ubVector X, ui size );

void __vf OVCUAPI   VUBcu_cmpC(    biVector Y, ubVector X, ui size, unsigned char C );
ui   __vf OVCUAPI   VUBcu_cmp_eqC( ubVector Y, ubVector X, ui size, unsigned char C );
ui   __vf OVCUAPI   VUBcu_cmp_neC( ubVector Y, ubVector X, ui size, unsigned char C );
ui   __vf OVCUAPI   VUBcu_cmp_leC( ubVector Y, ubVector X, ui size, unsigned char C );
ui   __vf OVCUAPI   VUBcu_cmp_ltC( ubVector Y, ubVector X, ui size, unsigned char C );
ui   __vf OVCUAPI   VUBcu_cmp_geC( ubVector Y, ubVector X, ui size, unsigned char C );
ui   __vf OVCUAPI   VUBcu_cmp_gtC( ubVector Y, ubVector X, ui size, unsigned char C );

ui   __vf OVCUAPI   VUBcu_cnt_eqC( ubVector X, ui size, unsigned char C );
ui   __vf OVCUAPI   VUBcu_cnt_neC( ubVector X, ui size, unsigned char C );
ui   __vf OVCUAPI   VUBcu_cnt_leC( ubVector X, ui size, unsigned char C );
ui   __vf OVCUAPI   VUBcu_cnt_ltC( ubVector X, ui size, unsigned char C );
ui   __vf OVCUAPI   VUBcu_cnt_geC( ubVector X, ui size, unsigned char C );
ui   __vf OVCUAPI   VUBcu_cnt_gtC( ubVector X, ui size, unsigned char C );

void __vf OVCUAPI   VUBcu_cmpV(    biVector Z, ubVector X, ubVector Y, ui size );
ui   __vf OVCUAPI   VUBcu_cmp_eqV( ubVector Z, ubVector X, ubVector Y, ui size );
ui   __vf OVCUAPI   VUBcu_cmp_neV( ubVector Z, ubVector X, ubVector Y, ui size );
ui   __vf OVCUAPI   VUBcu_cmp_leV( ubVector Z, ubVector X, ubVector Y, ui size );
ui   __vf OVCUAPI   VUBcu_cmp_ltV( ubVector Z, ubVector X, ubVector Y, ui size );
ui   __vf OVCUAPI   VUBcu_cmp_geV( ubVector Z, ubVector X, ubVector Y, ui size );
ui   __vf OVCUAPI   VUBcu_cmp_gtV( ubVector Z, ubVector X, ubVector Y, ui size );

ui   __vf OVCUAPI   VUBcu_cnt_eqV( ubVector X, ubVector Y, ui size );
ui   __vf OVCUAPI   VUBcu_cnt_neV( ubVector X, ubVector Y, ui size );
ui   __vf OVCUAPI   VUBcu_cnt_leV( ubVector X, ubVector Y, ui size );
ui   __vf OVCUAPI   VUBcu_cnt_ltV( ubVector X, ubVector Y, ui size );
ui   __vf OVCUAPI   VUBcu_cnt_geV( ubVector X, ubVector Y, ui size );
ui   __vf OVCUAPI   VUBcu_cnt_gtV( ubVector X, ubVector Y, ui size );

ui   __vf OVCUAPI   VUBcu_cmp_exclrange0C( ubVector Y, ubVector X, ui size, unsigned char C );
ui   __vf OVCUAPI   VUBcu_cmp_inclrangeCC( ubVector Y, ubVector X, ui size, unsigned char CLo, unsigned char CHi );
ui   __vf OVCUAPI   VUBcu_cmp_exclrangeCC( ubVector Y, ubVector X, ui size, unsigned char CLo, unsigned char CHi );

ui   __vf OVCUAPI   VUBcu_cnt_exclrange0C( ubVector X, ui size, unsigned char C );
ui   __vf OVCUAPI   VUBcu_cnt_inclrangeCC( ubVector X, ui size, unsigned char CLo, unsigned char CHi );
ui   __vf OVCUAPI   VUBcu_cnt_exclrangeCC( ubVector X, ui size, unsigned char CLo, unsigned char CHi );

/******************   Basic  Arithmetics   *************************/

void  __vf OVCUAPI   VUBcu_addC(  ubVector Y, ubVector X, ui size, unsigned char C );
void  __vf OVCUAPI   VUBcu_subC(  ubVector Y, ubVector X, ui size, unsigned char C );
void  __vf OVCUAPI   VUBcu_subrC( ubVector Y, ubVector X, ui size, unsigned char C );
void  __vf OVCUAPI   VUBcu_mulC(  ubVector Y, ubVector X, ui size, unsigned char C );
void  __vf OVCUAPI   VUBcu_divC(  ubVector Y, ubVector X, ui size, unsigned char C );
void  __vf OVCUAPI   VUBcu_divrC( ubVector Y, ubVector X, ui size, unsigned char C );
void  __vf OVCUAPI   VUBcu_modC(  ubVector Y, ubVector X, ui size, unsigned char C );
void  __vf OVCUAPI   VUBcu_maxC(  ubVector Y, ubVector X, ui size, unsigned char C );
void  __vf OVCUAPI   VUBcu_minC(  ubVector Y, ubVector X, ui size, unsigned char C );
void  __vf OVCUAPI   VUBcu_limit( ubVector Y, ubVector X, ui size, unsigned char Min, unsigned char Max );

void __vf OVCUAPI   VUBcu_addV(  ubVector Z, ubVector X, ubVector Y, ui size );
void __vf OVCUAPI   VUBcu_subV(  ubVector Z, ubVector X, ubVector Y, ui size );
void __vf OVCUAPI   VUBcu_subrV( ubVector Z, ubVector X, ubVector Y, ui size );
void __vf OVCUAPI   VUBcu_mulV(  ubVector Z, ubVector X, ubVector Y, ui size );
void __vf OVCUAPI   VUBcu_divV(  ubVector Z, ubVector X, ubVector Y, ui size );
void __vf OVCUAPI   VUBcu_divrV( ubVector Z, ubVector X, ubVector Y, ui size );
void __vf OVCUAPI   VUBcu_modV(  ubVector Z, ubVector X, ubVector Y, ui size );
void __vf OVCUAPI   VUBcu_maxV(  ubVector Z, ubVector X, ubVector Y, ui size );
void __vf OVCUAPI   VUBcu_minV(  ubVector Z, ubVector X, ubVector Y, ui size );

/******************** Accumulation (Y += X) ******************************/

void __vf OVCUAPI  VUBcu_accV(   ubVector Y, ubVector  X, ui size );


/*****************   Bit-wise operations  *********************/

void    __vf OVCUAPI   VUBcu_shl( ubVector Y, ubVector X, ui size, unsigned C );
void    __vf OVCUAPI   VUBcu_shr( ubVector Y, ubVector X, ui size, unsigned C );

void    __vf OVCUAPI   VUBcu_and( ubVector Y, ubVector X, ui size, unsigned char C );
void    __vf OVCUAPI   VUBcu_or(  ubVector Y, ubVector X, ui size, unsigned char C );
void    __vf OVCUAPI   VUBcu_xor( ubVector Y, ubVector X, ui size, unsigned char C );
void    __vf OVCUAPI   VUBcu_not( ubVector Y, ubVector X, ui size );

/************  Optical Density Y = log10( X0 / X ) *********************/

int  __vf OVCUAPI  VUBcu_ODtoF( fVector OD, ubVector X, ubVector X0, ui size );
int  __vf OVCUAPI  VUBcu_ODtoD( dVector OD, ubVector X, ubVector X0, ui size );
int  __vf OVCUAPI  VUBcu_ODtoFwDark( fVector OD, ubVector X, ubVector XDark,
                          ubVector X0, ubVector X0Dark, ui size );
int  __vf OVCUAPI  VUBcu_ODtoDwDark( dVector OD, ubVector X, ubVector XDark,
                          ubVector X0, ubVector X0Dark, ui size );
void __vf OVCUAPI  VUBcu_setODThresh( unsigned char minX, unsigned char minX0 );

#ifdef __cplusplus
}  // end of extern "C"
#endif

#endif   /*  __VUBMATH_H    */
