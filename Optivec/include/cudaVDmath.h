/*  cudaVDmath.h

  vector management functions:
  math functions performed on each individual element of an
  array or vector of the data type "double"

  Copyright (c) 1996-2017 by OptiCode - Dr. Martin Sander Software Dev.
  All Rights Reserved.
*/

#ifndef __CUDAVDMATH_H
#define __CUDAVDMATH_H

#ifndef __CUDAVDSTD_H 
#include <cudaVDstd.h>
#endif

/******************  cudaVD_ functions: **********************************
	 act on vectors in CUDA device memory; 
	 scalar parameters and return values on host
******************  cusdVD_ functions: **********************************
	 also act on vectors in CUDA device memory; 
	 scalar parameters and return values by address on device memory
************************************************************************/

#ifdef __cplusplus
extern "C" {
#endif

/**************************  Rounding **********************************/

overror_t  __vcuf OVCUAPI   cudaVD_round(  dVector  Y, dVector X, ui size );
overror_t  __vcuf OVCUAPI   cudaVD_roundtoBI( biVector Y, dVector X, ui size );
overror_t  __vcuf OVCUAPI   cudaVD_roundtoSI( siVector Y, dVector X, ui size );
overror_t  __vcuf OVCUAPI   cudaVD_roundtoI(  iVector  Y, dVector X, ui size );
overror_t  __vcuf OVCUAPI   cudaVD_roundtoLI( liVector Y, dVector X, ui size );
overror_t  __vcuf OVCUAPI   cudaVD_roundtoQI( qiVector Y, dVector X, ui size );
overror_t  __vcuf OVCUAPI   cudaVD_roundtoUB( ubVector Y, dVector X, ui size );
overror_t  __vcuf OVCUAPI   cudaVD_roundtoUS( usVector Y, dVector X, ui size );
overror_t  __vcuf OVCUAPI   cudaVD_roundtoU(  uVector  Y, dVector X, ui size );
overror_t  __vcuf OVCUAPI   cudaVD_roundtoUL( ulVector Y, dVector X, ui size );
#ifdef _WIN64
    overror_t  __vcuf OVCUAPI   cudaVD_roundtoUQ( uqVector Y, dVector X, ui size );
#endif

overror_t  __vcuf OVCUAPI   cudaVD_floor(  dVector  Y, dVector X, ui size );
overror_t  __vcuf OVCUAPI   cudaVD_floortoBI( biVector Y, dVector X, ui size );
overror_t  __vcuf OVCUAPI   cudaVD_floortoSI( siVector Y, dVector X, ui size );
overror_t  __vcuf OVCUAPI   cudaVD_floortoI(  iVector  Y, dVector X, ui size );
overror_t  __vcuf OVCUAPI   cudaVD_floortoLI( liVector Y, dVector X, ui size );
overror_t  __vcuf OVCUAPI   cudaVD_floortoQI( qiVector Y, dVector X, ui size );
overror_t  __vcuf OVCUAPI   cudaVD_floortoUB( ubVector Y, dVector X, ui size );
overror_t  __vcuf OVCUAPI   cudaVD_floortoUS( usVector Y, dVector X, ui size );
overror_t  __vcuf OVCUAPI   cudaVD_floortoU(  uVector  Y, dVector X, ui size );
overror_t  __vcuf OVCUAPI   cudaVD_floortoUL( ulVector Y, dVector X, ui size );
#ifdef _WIN64
    overror_t  __vcuf OVCUAPI   cudaVD_floortoUQ( uqVector Y, dVector X, ui size );
#endif

overror_t  __vcuf OVCUAPI   cudaVD_ceil(  dVector  Y, dVector X, ui size );
overror_t  __vcuf OVCUAPI   cudaVD_ceiltoBI( biVector Y, dVector X, ui size );
overror_t  __vcuf OVCUAPI   cudaVD_ceiltoSI( siVector Y, dVector X, ui size );
overror_t  __vcuf OVCUAPI   cudaVD_ceiltoI(  iVector  Y, dVector X, ui size );
overror_t  __vcuf OVCUAPI   cudaVD_ceiltoLI( liVector Y, dVector X, ui size );
overror_t  __vcuf OVCUAPI   cudaVD_ceiltoQI( qiVector Y, dVector X, ui size );
overror_t  __vcuf OVCUAPI   cudaVD_ceiltoUB( ubVector Y, dVector X, ui size );
overror_t  __vcuf OVCUAPI   cudaVD_ceiltoUS( usVector Y, dVector X, ui size );
overror_t  __vcuf OVCUAPI   cudaVD_ceiltoU(  uVector  Y, dVector X, ui size );
overror_t  __vcuf OVCUAPI   cudaVD_ceiltoUL( ulVector Y, dVector X, ui size );
#ifdef _WIN64
    overror_t  __vcuf OVCUAPI   cudaVD_ceiltoUQ( uqVector Y, dVector X, ui size );
#endif

overror_t  __vcuf OVCUAPI   cudaVD_chop(  dVector  Y, dVector X, ui size );
overror_t  __vcuf OVCUAPI   cudaVD_choptoBI( biVector Y, dVector X, ui size );
overror_t  __vcuf OVCUAPI   cudaVD_choptoSI( siVector Y, dVector X, ui size );
overror_t  __vcuf OVCUAPI   cudaVD_choptoI(  iVector  Y, dVector X, ui size );
overror_t  __vcuf OVCUAPI   cudaVD_choptoLI( liVector Y, dVector X, ui size );
overror_t  __vcuf OVCUAPI   cudaVD_choptoQI( qiVector Y, dVector X, ui size );
overror_t  __vcuf OVCUAPI   cudaVD_choptoUB( ubVector Y, dVector X, ui size );
overror_t  __vcuf OVCUAPI   cudaVD_choptoUS( usVector Y, dVector X, ui size );
overror_t  __vcuf OVCUAPI   cudaVD_choptoU(  uVector  Y, dVector X, ui size );
overror_t  __vcuf OVCUAPI   cudaVD_choptoUL( ulVector Y, dVector X, ui size );
#ifdef _WIN64
    overror_t  __vcuf OVCUAPI   cudaVD_choptoUQ( uqVector Y, dVector X, ui size );
#endif

#define cudaVD_trunc      cudaVD_chop
#define cudaVD_trunctoBI  cudaVD_choptoBI
#define cudaVD_trunctoSI  cudaVD_choptoSI
#define cudaVD_trunctoI   cudaVD_choptoI
#define cudaVD_trunctoLI  cudaVD_choptoLI
#define cudaVD_trunctoQI  cudaVD_choptoQI
#define cudaVD_trunctoUB  cudaVD_choptoUB
#define cudaVD_trunctoUS  cudaVD_choptoUS
#define cudaVD_trunctoU   cudaVD_choptoU
#define cudaVD_trunctoUL  cudaVD_choptoUL
#define cudaVD_trunctoUQ  cudaVD_choptoUQ

#if defined _WIN64
      #define   cudaVD_roundtoUI    cudaVD_roundtoUQ
      #define   cudaVD_floortoUI    cudaVD_floortoUQ
      #define   cudaVD_ceiltoUI     cudaVD_ceiltoUQ
      #define   cudaVD_choptoUI     cudaVD_choptoUQ
      #define   cudaVD_trunctoUI    cudaVD_trunctoUQ
#else
      #define   cudaVD_roundtoUI    cudaVD_roundtoU
      #define   cudaVD_floortoUI    cudaVD_floortoU
      #define   cudaVD_ceiltoUI     cudaVD_ceiltoU
      #define   cudaVD_choptoUI     cudaVD_choptoU
      #define   cudaVD_trunctoUI    cudaVD_trunctoU
#endif

/********************  Comparisons ********************************/

overror_t  __vcuf OVCUAPI   cudaVD_cmp0(    dVector Y, dVector X, ui size );
overror_t  __vcuf OVCUAPI   cudaVD_cmp_eq0( ui *h_nTrue, dVector Y, dVector X, ui size );
overror_t  __vcuf OVCUAPI   cudaVD_cmp_ne0( ui *h_nTrue, dVector Y, dVector X, ui size );
overror_t  __vcuf OVCUAPI   cudaVD_cmp_le0( ui *h_nTrue, dVector Y, dVector X, ui size );
overror_t  __vcuf OVCUAPI   cudaVD_cmp_lt0( ui *h_nTrue, dVector Y, dVector X, ui size );
overror_t  __vcuf OVCUAPI   cudaVD_cmp_ge0( ui *h_nTrue, dVector Y, dVector X, ui size );
overror_t  __vcuf OVCUAPI   cudaVD_cmp_gt0( ui *h_nTrue, dVector Y, dVector X, ui size );

overror_t  __vcuf OVCUAPI   cudaVD_cmpC(    dVector Y, dVector X, ui size, double C );
overror_t  __vcuf OVCUAPI   cudaVD_cmp_eqC( ui *h_nTrue, dVector Y, dVector X, ui size, double C );
overror_t  __vcuf OVCUAPI   cudaVD_cmp_neC( ui *h_nTrue, dVector Y, dVector X, ui size, double C );
overror_t  __vcuf OVCUAPI   cudaVD_cmp_leC( ui *h_nTrue, dVector Y, dVector X, ui size, double C );
overror_t  __vcuf OVCUAPI   cudaVD_cmp_ltC( ui *h_nTrue, dVector Y, dVector X, ui size, double C );
overror_t  __vcuf OVCUAPI   cudaVD_cmp_geC( ui *h_nTrue, dVector Y, dVector X, ui size, double C );
overror_t  __vcuf OVCUAPI   cudaVD_cmp_gtC( ui *h_nTrue, dVector Y, dVector X, ui size, double C );
overror_t  __vcuf OVCUAPI   cusdVD_cmpC(    dVector Y, dVector X, ui size, double *d_C );
overror_t  __vcuf OVCUAPI   cusdVD_cmp_eqC( ui *h_nTrue, dVector Y, dVector X, ui size, double *d_C );
overror_t  __vcuf OVCUAPI   cusdVD_cmp_neC( ui *h_nTrue, dVector Y, dVector X, ui size, double *d_C );
overror_t  __vcuf OVCUAPI   cusdVD_cmp_leC( ui *h_nTrue, dVector Y, dVector X, ui size, double *d_C );
overror_t  __vcuf OVCUAPI   cusdVD_cmp_ltC( ui *h_nTrue, dVector Y, dVector X, ui size, double *d_C );
overror_t  __vcuf OVCUAPI   cusdVD_cmp_geC( ui *h_nTrue, dVector Y, dVector X, ui size, double *d_C );
overror_t  __vcuf OVCUAPI   cusdVD_cmp_gtC( ui *h_nTrue, dVector Y, dVector X, ui size, double *d_C );

overror_t  __vcuf OVCUAPI   cudaVD_cmpV(    dVector Z, dVector X, dVector Y, ui size );
overror_t  __vcuf OVCUAPI   cudaVD_cmp_eqV( ui *h_nTrue, dVector Z, dVector X, dVector Y, ui size );
overror_t  __vcuf OVCUAPI   cudaVD_cmp_neV( ui *h_nTrue, dVector Z, dVector X, dVector Y, ui size );
overror_t  __vcuf OVCUAPI   cudaVD_cmp_leV( ui *h_nTrue, dVector Z, dVector X, dVector Y, ui size );
overror_t  __vcuf OVCUAPI   cudaVD_cmp_ltV( ui *h_nTrue, dVector Z, dVector X, dVector Y, ui size );
overror_t  __vcuf OVCUAPI   cudaVD_cmp_geV( ui *h_nTrue, dVector Z, dVector X, dVector Y, ui size );
overror_t  __vcuf OVCUAPI   cudaVD_cmp_gtV( ui *h_nTrue, dVector Z, dVector X, dVector Y, ui size );

overror_t  __vcuf OVCUAPI   cudaVD_cmp_inclrange0C( ui *h_nTrue, dVector Y, dVector X, ui size, double C );
overror_t  __vcuf OVCUAPI   cudaVD_cmp_exclrange0C( ui *h_nTrue, dVector Y, dVector X, ui size, double C );
overror_t  __vcuf OVCUAPI   cudaVD_cmp_inclrangeCC( ui *h_nTrue, dVector Y, dVector X, ui size, double CLo, double CHi );
overror_t  __vcuf OVCUAPI   cudaVD_cmp_exclrangeCC( ui *h_nTrue, dVector Y, dVector X, ui size, double CLo, double CHi );
overror_t  __vcuf OVCUAPI   cusdVD_cmp_inclrange0C( ui *h_nTrue, dVector Y, dVector X, ui size, double *d_C );
overror_t  __vcuf OVCUAPI   cusdVD_cmp_exclrange0C( ui *h_nTrue, dVector Y, dVector X, ui size, double *d_C );
overror_t  __vcuf OVCUAPI   cusdVD_cmp_inclrangeCC( ui *h_nTrue, dVector Y, dVector X, ui size, double *d_CLo, double *d_CHi );
overror_t  __vcuf OVCUAPI   cusdVD_cmp_exclrangeCC( ui *h_nTrue, dVector Y, dVector X, ui size, double *d_CLo, double *d_CHi );

overror_t  __vcuf OVCUAPI   cudaVD_cnt_eq0( ui *h_nTrue, dVector X, ui size );
overror_t  __vcuf OVCUAPI   cudaVD_cnt_ne0( ui *h_nTrue, dVector X, ui size );
overror_t  __vcuf OVCUAPI   cudaVD_cnt_le0( ui *h_nTrue, dVector X, ui size );
overror_t  __vcuf OVCUAPI   cudaVD_cnt_lt0( ui *h_nTrue, dVector X, ui size );
overror_t  __vcuf OVCUAPI   cudaVD_cnt_ge0( ui *h_nTrue, dVector X, ui size );
overror_t  __vcuf OVCUAPI   cudaVD_cnt_gt0( ui *h_nTrue, dVector X, ui size );

overror_t  __vcuf OVCUAPI   cudaVD_cnt_eqC( ui *h_nTrue, dVector X, ui size, double C );
overror_t  __vcuf OVCUAPI   cudaVD_cnt_neC( ui *h_nTrue, dVector X, ui size, double C );
overror_t  __vcuf OVCUAPI   cudaVD_cnt_leC( ui *h_nTrue, dVector X, ui size, double C );
overror_t  __vcuf OVCUAPI   cudaVD_cnt_ltC( ui *h_nTrue, dVector X, ui size, double C );
overror_t  __vcuf OVCUAPI   cudaVD_cnt_geC( ui *h_nTrue, dVector X, ui size, double C );
overror_t  __vcuf OVCUAPI   cudaVD_cnt_gtC( ui *h_nTrue, dVector X, ui size, double C );
overror_t  __vcuf OVCUAPI   cusdVD_cnt_eqC( ui *h_nTrue, dVector X, ui size, double *d_C );
overror_t  __vcuf OVCUAPI   cusdVD_cnt_neC( ui *h_nTrue, dVector X, ui size, double *d_C );
overror_t  __vcuf OVCUAPI   cusdVD_cnt_leC( ui *h_nTrue, dVector X, ui size, double *d_C );
overror_t  __vcuf OVCUAPI   cusdVD_cnt_ltC( ui *h_nTrue, dVector X, ui size, double *d_C );
overror_t  __vcuf OVCUAPI   cusdVD_cnt_geC( ui *h_nTrue, dVector X, ui size, double *d_C );
overror_t  __vcuf OVCUAPI   cusdVD_cnt_gtC( ui *h_nTrue, dVector X, ui size, double *d_C );

overror_t  __vcuf OVCUAPI   cudaVD_cnt_eqV( ui *h_nTrue, dVector X, dVector Y, ui size );
overror_t  __vcuf OVCUAPI   cudaVD_cnt_neV( ui *h_nTrue, dVector X, dVector Y, ui size );
overror_t  __vcuf OVCUAPI   cudaVD_cnt_leV( ui *h_nTrue, dVector X, dVector Y, ui size );
overror_t  __vcuf OVCUAPI   cudaVD_cnt_ltV( ui *h_nTrue, dVector X, dVector Y, ui size );
overror_t  __vcuf OVCUAPI   cudaVD_cnt_geV( ui *h_nTrue, dVector X, dVector Y, ui size );
overror_t  __vcuf OVCUAPI   cudaVD_cnt_gtV( ui *h_nTrue, dVector X, dVector Y, ui size );

overror_t  __vcuf OVCUAPI   cudaVD_cnt_inclrange0C( ui *h_nTrue, dVector X, ui size, double C );
overror_t  __vcuf OVCUAPI   cudaVD_cnt_exclrange0C( ui *h_nTrue, dVector X, ui size, double C );
overror_t  __vcuf OVCUAPI   cudaVD_cnt_inclrangeCC( ui *h_nTrue, dVector X, ui size, double CLo, double CHi );
overror_t  __vcuf OVCUAPI   cudaVD_cnt_exclrangeCC( ui *h_nTrue, dVector X, ui size, double CLo, double CHi );
overror_t  __vcuf OVCUAPI   cusdVD_cnt_inclrange0C( ui *h_nTrue, dVector X, ui size, double *d_C );
overror_t  __vcuf OVCUAPI   cusdVD_cnt_exclrange0C( ui *h_nTrue, dVector X, ui size, double *d_C );
overror_t  __vcuf OVCUAPI   cusdVD_cnt_inclrangeCC( ui *h_nTrue, dVector X, ui size, double *d_CLo, double *d_CHi );
overror_t  __vcuf OVCUAPI   cusdVD_cnt_exclrangeCC( ui *h_nTrue, dVector X, ui size, double *d_CLo, double *d_CHi );

/*
overror_t  __vcuf OVCUAPI   cudaVD_cmp_eq0ind( ui *h_nTrue, uiVector Ind, dVector X, ui size );
overror_t  __vcuf OVCUAPI   cudaVD_cmp_ne0ind( ui *h_nTrue, uiVector Ind, dVector X, ui size );
overror_t  __vcuf OVCUAPI   cudaVD_cmp_le0ind( ui *h_nTrue, uiVector Ind, dVector X, ui size );
overror_t  __vcuf OVCUAPI   cudaVD_cmp_lt0ind( ui *h_nTrue, uiVector Ind, dVector X, ui size );
overror_t  __vcuf OVCUAPI   cudaVD_cmp_ge0ind( ui *h_nTrue, uiVector Ind, dVector X, ui size );
overror_t  __vcuf OVCUAPI   cudaVD_cmp_gt0ind( ui *h_nTrue, uiVector Ind, dVector X, ui size );

overror_t  __vcuf OVCUAPI   cudaVD_cmp_eqCind( ui *h_nTrue, uiVector Ind, dVector X, ui size, double C );
overror_t  __vcuf OVCUAPI   cudaVD_cmp_neCind( ui *h_nTrue, uiVector Ind, dVector X, ui size, double C );
overror_t  __vcuf OVCUAPI   cudaVD_cmp_leCind( ui *h_nTrue, uiVector Ind, dVector X, ui size, double C );
overror_t  __vcuf OVCUAPI   cudaVD_cmp_ltCind( ui *h_nTrue, uiVector Ind, dVector X, ui size, double C );
overror_t  __vcuf OVCUAPI   cudaVD_cmp_geCind( ui *h_nTrue, uiVector Ind, dVector X, ui size, double C );
overror_t  __vcuf OVCUAPI   cudaVD_cmp_gtCind( ui *h_nTrue, uiVector Ind, dVector X, ui size, double C );
overror_t  __vcuf OVCUAPI   cusdVD_cmp_eqCind( ui *h_nTrue, uiVector Ind, dVector X, ui size, double *d_C );
overror_t  __vcuf OVCUAPI   cusdVD_cmp_neCind( ui *h_nTrue, uiVector Ind, dVector X, ui size, double *d_C );
overror_t  __vcuf OVCUAPI   cusdVD_cmp_leCind( ui *h_nTrue, uiVector Ind, dVector X, ui size, double *d_C );
overror_t  __vcuf OVCUAPI   cusdVD_cmp_ltCind( ui *h_nTrue, uiVector Ind, dVector X, ui size, double *d_C );
overror_t  __vcuf OVCUAPI   cusdVD_cmp_geCind( ui *h_nTrue, uiVector Ind, dVector X, ui size, double *d_C );
overror_t  __vcuf OVCUAPI   cusdVD_cmp_gtCind( ui *h_nTrue, uiVector Ind, dVector X, ui size, double *d_C );

overror_t  __vcuf OVCUAPI   cudaVD_cmp_eqVind( ui *h_nTrue, uiVector Ind, dVector X, dVector Y, ui size );
overror_t  __vcuf OVCUAPI   cudaVD_cmp_neVind( ui *h_nTrue, uiVector Ind, dVector X, dVector Y, ui size );
overror_t  __vcuf OVCUAPI   cudaVD_cmp_leVind( ui *h_nTrue, uiVector Ind, dVector X, dVector Y, ui size );
overror_t  __vcuf OVCUAPI   cudaVD_cmp_ltVind( ui *h_nTrue, uiVector Ind, dVector X, dVector Y, ui size );
overror_t  __vcuf OVCUAPI   cudaVD_cmp_geVind( ui *h_nTrue, uiVector Ind, dVector X, dVector Y, ui size );
overror_t  __vcuf OVCUAPI   cudaVD_cmp_gtVind( ui *h_nTrue, uiVector Ind, dVector X, dVector Y, ui size );

overror_t  __vcuf OVCUAPI   cudaVD_cmp_inclrange0Cind( ui *h_nTrue, uiVector Ind, dVector X, ui size, double C );
overror_t  __vcuf OVCUAPI   cudaVD_cmp_exclrange0Cind( ui *h_nTrue, uiVector Ind, dVector X, ui size, double C );
overror_t  __vcuf OVCUAPI   cudaVD_cmp_inclrangeCCind( ui *h_nTrue, uiVector Ind, dVector X, ui size, double CLo, double CHi );
overror_t  __vcuf OVCUAPI   cudaVD_cmp_exclrangeCCind( ui *h_nTrue, uiVector Ind, dVector X, ui size, double CLo, double CHi );
overror_t  __vcuf OVCUAPI   cusdVD_cmp_inclrange0Cind( ui *h_nTrue, uiVector Ind, dVector X, ui size, double *d_C );
overror_t  __vcuf OVCUAPI   cusdVD_cmp_exclrange0Cind( ui *h_nTrue, uiVector Ind, dVector X, ui size, double *d_C );
overror_t  __vcuf OVCUAPI   cusdVD_cmp_inclrangeCCind( ui *h_nTrue, uiVector Ind, dVector X, ui size, double *d_CLo, double *d_CHi );
overror_t  __vcuf OVCUAPI   cusdVD_cmp_exclrangeCCind( ui *h_nTrue, uiVector Ind, dVector X, ui size, double *d_CLo, double *d_CHi );
*/


/********************  Standard Arithmetics   ***************************/

overror_t  __vcuf OVCUAPI   cudaVD_equC( dVector X, ui size, double C );
overror_t  __vcuf OVCUAPI   cusdVD_equC( dVector X, ui size, double *d_C );
overror_t  __vcuf OVCUAPI   cudaVD_equV( dVector Y, dVector X, ui size );
overror_t  __vcuf OVCUAPI   cudaVDx_equV( dVector Y, dVector X, ui size, double A, double B );
overror_t  __vcuf OVCUAPI   cusdVDx_equV( dVector Y, dVector X, ui size, double *d_A, double *d_B );

overror_t  __vcuf OVCUAPI   cudaVD_addC(  dVector Y, dVector X, ui size, double C );
overror_t  __vcuf OVCUAPI   cudaVD_subC(  dVector Y, dVector X, ui size, double C );
overror_t  __vcuf OVCUAPI   cudaVD_subrC( dVector Y, dVector X, ui size, double C );
overror_t  __vcuf OVCUAPI   cudaVD_mulC(  dVector Y, dVector X, ui size, double C );
overror_t  __vcuf OVCUAPI   cudaVD_divC(  dVector Y, dVector X, ui size, double C );
overror_t  __vcuf OVCUAPI   cudaVD_divrC( dVector Y, dVector X, ui size, double C );
overror_t  __vcuf OVCUAPI   cudaVDx_divrC( dVector Y, dVector X, ui size, double A, double B, double C );

overror_t  __vcuf OVCUAPI   cusdVD_addC(  dVector Y, dVector X, ui size, double *d_C );
overror_t  __vcuf OVCUAPI   cusdVD_subC(  dVector Y, dVector X, ui size, double *d_C );
overror_t  __vcuf OVCUAPI   cusdVD_subrC( dVector Y, dVector X, ui size, double *d_C );
overror_t  __vcuf OVCUAPI   cusdVD_mulC(  dVector Y, dVector X, ui size, double *d_C );
overror_t  __vcuf OVCUAPI   cusdVD_divC(  dVector Y, dVector X, ui size, double *d_C );
overror_t  __vcuf OVCUAPI   cusdVD_divrC( dVector Y, dVector X, ui size, double *d_C );
overror_t  __vcuf OVCUAPI   cusdVDx_divrC( dVector Y, dVector X, ui size, double *d_A, double *d_B, double *d_C );

overror_t  __vcuf OVCUAPI   cudaVD_addV(  dVector Z, dVector X, dVector Y, ui size );
overror_t  __vcuf OVCUAPI   cudaVD_subV(  dVector Z, dVector X, dVector Y, ui size );
overror_t  __vcuf OVCUAPI   cudaVD_subrV( dVector Z, dVector X, dVector Y, ui size );
overror_t  __vcuf OVCUAPI   cudaVD_mulV(  dVector Z, dVector X, dVector Y, ui size );
overror_t  __vcuf OVCUAPI   cudaVD_divV(  dVector Z, dVector X, dVector Y, ui size );
overror_t  __vcuf OVCUAPI   cudaVD_divrV(  dVector Z, dVector X, dVector Y, ui size );
overror_t  __vcuf OVCUAPI   cudaVD_add2V(  dVector Z, dVector X, dVector Y1, dVector Y2, ui size );
overror_t  __vcuf OVCUAPI   cudaVD_sub2V(  dVector Z, dVector X, dVector Y1, dVector Y2, ui size );

overror_t  __vcuf OVCUAPI   cudaVD_CaddV( dVector Z, dVector X, dVector Y, ui siz, double C );
overror_t  __vcuf OVCUAPI   cusdVD_CaddV( dVector Z, dVector X, dVector Y, ui siz, double *d_C );
                              /* Z = X + C*Y  */

overror_t  __vcuf OVCUAPI   cudaVDx_addV(  dVector Z, dVector X, dVector Y, ui size, double A, double B );
                              /* Z = (A*X+B) + Y  */
overror_t  __vcuf OVCUAPI   cudaVDx_subV(  dVector Z, dVector X, dVector Y, ui size, double A, double B );
overror_t  __vcuf OVCUAPI   cudaVDx_subrV( dVector Z, dVector X, dVector Y, ui size, double A, double B );
overror_t  __vcuf OVCUAPI   cudaVDx_mulV(  dVector Z, dVector X, dVector Y, ui size, double A, double B );
overror_t  __vcuf OVCUAPI   cudaVDx_divV(  dVector Z, dVector X, dVector Y, ui size, double A, double B );
overror_t  __vcuf OVCUAPI   cudaVDx_divrV( dVector Z, dVector X, dVector Y, ui size, double A, double B );

overror_t  __vcuf OVCUAPI   cusdVDx_addV(  dVector Z, dVector X, dVector Y, ui size, double *d_A, double *d_B );
overror_t  __vcuf OVCUAPI   cusdVDx_subV(  dVector Z, dVector X, dVector Y, ui size, double *d_A, double *d_B );
overror_t  __vcuf OVCUAPI   cusdVDx_subrV( dVector Z, dVector X, dVector Y, ui size, double *d_A, double *d_B );
overror_t  __vcuf OVCUAPI   cusdVDx_mulV(  dVector Z, dVector X, dVector Y, ui size, double *d_A, double *d_B );
overror_t  __vcuf OVCUAPI   cusdVDx_divV(  dVector Z, dVector X, dVector Y, ui size, double *d_A, double *d_B );
overror_t  __vcuf OVCUAPI   cusdVDx_divrV( dVector Z, dVector X, dVector Y, ui size, double *d_A, double *d_B );

overror_t  __vcuf OVCUAPI   cudaVDs_addV(  dVector Z, dVector X, dVector Y, ui size, double C ); /* Z=C*(X+Y) */
overror_t  __vcuf OVCUAPI   cudaVDs_subV(  dVector Z, dVector X, dVector Y, ui size, double C );
overror_t  __vcuf OVCUAPI   cudaVDs_subrV( dVector Z, dVector X, dVector Y, ui size, double C );
overror_t  __vcuf OVCUAPI   cudaVDs_mulV(  dVector Z, dVector X, dVector Y, ui size, double C );
overror_t  __vcuf OVCUAPI   cudaVDs_divV(  dVector Z, dVector X, dVector Y, ui size, double C );
overror_t  __vcuf OVCUAPI   cudaVDs_divrV( dVector Z, dVector X, dVector Y, ui size, double C );

overror_t  __vcuf OVCUAPI   cusdVDs_addV(  dVector Z, dVector X, dVector Y, ui size, double *d_C ); /* Z=C*(X+Y) */
overror_t  __vcuf OVCUAPI   cusdVDs_subV(  dVector Z, dVector X, dVector Y, ui size, double *d_C );
overror_t  __vcuf OVCUAPI   cusdVDs_subrV( dVector Z, dVector X, dVector Y, ui size, double *d_C );
overror_t  __vcuf OVCUAPI   cusdVDs_mulV(  dVector Z, dVector X, dVector Y, ui size, double *d_C );
overror_t  __vcuf OVCUAPI   cusdVDs_divV(  dVector Z, dVector X, dVector Y, ui size, double *d_C );
overror_t  __vcuf OVCUAPI   cusdVDs_divrV( dVector Z, dVector X, dVector Y, ui size, double *d_C );

overror_t  __vcuf OVCUAPI   cudaVD_maxC(   dVector Y, dVector X, ui size, double C );
overror_t  __vcuf OVCUAPI   cudaVD_minC(   dVector Y, dVector X, ui size, double C );
overror_t  __vcuf OVCUAPI   cudaVD_limit(  dVector Y, dVector X, ui size, double Min, double Max );
overror_t  __vcuf OVCUAPI   cudaVD_flush0( dVector Y, dVector X, ui size, double AbsMin );
overror_t  __vcuf OVCUAPI   cudaVD_flushInv( dVector Y, dVector X, ui size, double AbsMin );
overror_t  __vcuf OVCUAPI   cudaVD_replaceNAN( dVector Y, dVector X, ui size, double C );
overror_t  __vcuf OVCUAPI   cudaVD_maxV(   dVector Z, dVector X, dVector Y, ui size );
overror_t  __vcuf OVCUAPI   cudaVD_minV(   dVector Z, dVector X, dVector Y, ui size );
overror_t  __vcuf OVCUAPI   cudaVD_modC(   dVector Y, dVector X, ui size, double C );
overror_t  __vcuf OVCUAPI   cudaVD_modV(   dVector Z, dVector X, dVector Y, ui size );
overror_t  __vcuf OVCUAPI   cudaVDx_modV(  dVector Z, dVector X, dVector Y, ui size, double A, double B );
#define     cudaVD_fmodC    cudaVD_modC
#define     cudaVD_fmodV    cudaVD_modV
#define     cudaVDx_fmodV   cudaVDx_modV

overror_t  __vcuf OVCUAPI   cudaVD_redC(  dVector Y, dVector X, ui size, double C );
overror_t  __vcuf OVCUAPI   cudaVD_redV(  dVector Z, dVector X, dVector Y, ui size );
overror_t  __vcuf OVCUAPI   cudaVDx_redV( dVector Z, dVector X, dVector Y, ui size, double A, double B );
overror_t  __vcuf OVCUAPI   cudaVD_visC(  dVector Y, dVector X, ui size, double C );
overror_t  __vcuf OVCUAPI   cudaVD_visV(  dVector Z, dVector X, dVector Y, ui size );
overror_t  __vcuf OVCUAPI   cudaVDx_visV( dVector Z, dVector X, dVector Y, ui size, double A, double B );
overror_t  __vcuf OVCUAPI   cudaVD_hypC(  dVector Y, dVector X, ui size, double C );
overror_t  __vcuf OVCUAPI   cudaVD_hypV(  dVector Z, dVector X, dVector Y, ui size );
overror_t  __vcuf OVCUAPI   cudaVDx_hypV( dVector Z, dVector X, dVector Y, ui size, double A, double B );

overror_t  __vcuf OVCUAPI  cudaVD_lincomb( dVector Z, dVector X, dVector Y, ui size, double CX, double CY );
		/* Z=CX*X+CY*Y */

overror_t  __vcuf OVCUAPI  cudaVD_rotateCoordinates( dVector Xnew, dVector Ynew, dVector Xold, dVector Yold,
                      ui size, double costheta, double sintheta );
#define cudaVD_sgn    cudaVD_cmp0

overror_t  __vcuf OVCUAPI   cusdVD_maxC(   dVector Y, dVector X, ui size, double  *d_C );
overror_t  __vcuf OVCUAPI   cusdVD_minC(   dVector Y, dVector X, ui size, double  *d_C );
overror_t  __vcuf OVCUAPI   cusdVD_limit(  dVector Y, dVector X, ui size, double *d_Min, double *d_Max );
overror_t  __vcuf OVCUAPI   cusdVD_flush0( dVector Y, dVector X, ui size, double *d_AbsMin );
overror_t  __vcuf OVCUAPI   cusdVD_flushInv( dVector Y, dVector X, ui size, double *d_AbsMin );
overror_t  __vcuf OVCUAPI   cusdVD_replaceNAN( dVector Y, dVector X, ui size, double *d_C );
overror_t  __vcuf OVCUAPI   cusdVD_maxV(   dVector Z, dVector X, dVector Y, ui size );
overror_t  __vcuf OVCUAPI   cusdVD_minV(   dVector Z, dVector X, dVector Y, ui size );
overror_t  __vcuf OVCUAPI   cusdVD_modC(   dVector Y, dVector X, ui size, double  *d_C );
overror_t  __vcuf OVCUAPI   cusdVD_modV(   dVector Z, dVector X, dVector Y, ui size );
overror_t  __vcuf OVCUAPI   cusdVDx_modV(  dVector Z, dVector X, dVector Y, ui size, double *d_A, double *d_B );
#define     cusdVD_fmodC    cusdVD_modC
#define     cusdVDx_fmodV   cusdVDx_modV
overror_t  __vcuf OVCUAPI   cusdVD_redC(  dVector Y, dVector X, ui size, double  *d_C );
overror_t  __vcuf OVCUAPI   cusdVDx_redV( dVector Z, dVector X, dVector Y, ui size, double *d_A, double *d_B );
overror_t  __vcuf OVCUAPI   cusdVD_visC(  dVector Y, dVector X, ui size, double  *d_C );
overror_t  __vcuf OVCUAPI   cusdVDx_visV( dVector Z, dVector X, dVector Y, ui size, double *d_A, double *d_B );
overror_t  __vcuf OVCUAPI   cusdVD_hypC(  dVector Y, dVector X, ui size, double  *d_C );
overror_t  __vcuf OVCUAPI   cusdVDx_hypV( dVector Z, dVector X, dVector Y, ui size, double *d_A, double *d_B );
overror_t  __vcuf OVCUAPI  cusdVD_lincomb( dVector Z, dVector X, dVector Y, ui size,  double  *d_CX, double  *d_CY );  /* Z= *d_CX*X+ *d_CY*Y */
overror_t  __vcuf OVCUAPI  cusdVD_rotate_Coordinates( dVector Xnew, dVector Ynew, dVector Xold, dVector Yold,
                      ui size, double *d_costheta, double *d_sintheta );

/******************* Mixed-type arithmetic Functions **********************/

overror_t  __vcuf OVCUAPI   cudaVD_addVBI(  dVector Z, dVector X, biVector Y, ui size );
overror_t  __vcuf OVCUAPI   cudaVD_subVBI(  dVector Z, dVector X, biVector Y, ui size );
overror_t  __vcuf OVCUAPI   cudaVD_subrVBI( dVector Z, dVector X, biVector Y, ui size );
overror_t  __vcuf OVCUAPI   cudaVD_mulVBI(  dVector Z, dVector X, biVector Y, ui size );
overror_t  __vcuf OVCUAPI   cudaVD_divVBI(  dVector Z, dVector X, biVector Y, ui size );
overror_t  __vcuf OVCUAPI   cudaVD_divrVBI( dVector Z, dVector X, biVector Y, ui size );
overror_t  __vcuf OVCUAPI   cudaVD_addVSI(  dVector Z, dVector X, siVector Y, ui size );
overror_t  __vcuf OVCUAPI   cudaVD_subVSI(  dVector Z, dVector X, siVector Y, ui size );
overror_t  __vcuf OVCUAPI   cudaVD_subrVSI( dVector Z, dVector X, siVector Y, ui size );
overror_t  __vcuf OVCUAPI   cudaVD_mulVSI(  dVector Z, dVector X, siVector Y, ui size );
overror_t  __vcuf OVCUAPI   cudaVD_divVSI(  dVector Z, dVector X, siVector Y, ui size );
overror_t  __vcuf OVCUAPI   cudaVD_divrVSI( dVector Z, dVector X, siVector Y, ui size );
overror_t  __vcuf OVCUAPI   cudaVD_addVI(  dVector Z, dVector X, iVector Y, ui size );
overror_t  __vcuf OVCUAPI   cudaVD_subVI(  dVector Z, dVector X, iVector Y, ui size );
overror_t  __vcuf OVCUAPI   cudaVD_subrVI( dVector Z, dVector X, iVector Y, ui size );
overror_t  __vcuf OVCUAPI   cudaVD_mulVI(  dVector Z, dVector X, iVector Y, ui size );
overror_t  __vcuf OVCUAPI   cudaVD_divVI(  dVector Z, dVector X, iVector Y, ui size );
overror_t  __vcuf OVCUAPI   cudaVD_divrVI( dVector Z, dVector X, iVector Y, ui size );
overror_t  __vcuf OVCUAPI   cudaVD_addVLI(  dVector Z, dVector X, liVector Y, ui size );
overror_t  __vcuf OVCUAPI   cudaVD_subVLI(  dVector Z, dVector X, liVector Y, ui size );
overror_t  __vcuf OVCUAPI   cudaVD_subrVLI( dVector Z, dVector X, liVector Y, ui size );
overror_t  __vcuf OVCUAPI   cudaVD_mulVLI(  dVector Z, dVector X, liVector Y, ui size );
overror_t  __vcuf OVCUAPI   cudaVD_divVLI(  dVector Z, dVector X, liVector Y, ui size );
overror_t  __vcuf OVCUAPI   cudaVD_divrVLI( dVector Z, dVector X, liVector Y, ui size );
overror_t  __vcuf OVCUAPI   cudaVD_addVQI(  dVector Z, dVector X, qiVector Y, ui size );
overror_t  __vcuf OVCUAPI   cudaVD_subVQI(  dVector Z, dVector X, qiVector Y, ui size );
overror_t  __vcuf OVCUAPI   cudaVD_subrVQI( dVector Z, dVector X, qiVector Y, ui size );
overror_t  __vcuf OVCUAPI   cudaVD_mulVQI(  dVector Z, dVector X, qiVector Y, ui size );
overror_t  __vcuf OVCUAPI   cudaVD_divVQI(  dVector Z, dVector X, qiVector Y, ui size );
overror_t  __vcuf OVCUAPI   cudaVD_divrVQI( dVector Z, dVector X, qiVector Y, ui size );
overror_t  __vcuf OVCUAPI   cudaVD_addVUB(  dVector Z, dVector X, ubVector Y, ui size );
overror_t  __vcuf OVCUAPI   cudaVD_subVUB(  dVector Z, dVector X, ubVector Y, ui size );
overror_t  __vcuf OVCUAPI   cudaVD_subrVUB( dVector Z, dVector X, ubVector Y, ui size );
overror_t  __vcuf OVCUAPI   cudaVD_mulVUB(  dVector Z, dVector X, ubVector Y, ui size );
overror_t  __vcuf OVCUAPI   cudaVD_divVUB(  dVector Z, dVector X, ubVector Y, ui size );
overror_t  __vcuf OVCUAPI   cudaVD_divrVUB( dVector Z, dVector X, ubVector Y, ui size );
overror_t  __vcuf OVCUAPI   cudaVD_addVUS(  dVector Z, dVector X, usVector Y, ui size );
overror_t  __vcuf OVCUAPI   cudaVD_subVUS(  dVector Z, dVector X, usVector Y, ui size );
overror_t  __vcuf OVCUAPI   cudaVD_subrVUS( dVector Z, dVector X, usVector Y, ui size );
overror_t  __vcuf OVCUAPI   cudaVD_mulVUS(  dVector Z, dVector X, usVector Y, ui size );
overror_t  __vcuf OVCUAPI   cudaVD_divVUS(  dVector Z, dVector X, usVector Y, ui size );
overror_t  __vcuf OVCUAPI   cudaVD_divrVUS( dVector Z, dVector X, usVector Y, ui size );
overror_t  __vcuf OVCUAPI   cudaVD_addVU(   dVector Z, dVector X, uVector Y,  ui size );
overror_t  __vcuf OVCUAPI   cudaVD_subVU(   dVector Z, dVector X, uVector Y,  ui size );
overror_t  __vcuf OVCUAPI   cudaVD_subrVU(  dVector Z, dVector X, uVector Y,  ui size );
overror_t  __vcuf OVCUAPI   cudaVD_mulVU(   dVector Z, dVector X, uVector Y,  ui size );
overror_t  __vcuf OVCUAPI   cudaVD_divVU(   dVector Z, dVector X, uVector Y,  ui size );
overror_t  __vcuf OVCUAPI   cudaVD_divrVU(  dVector Z, dVector X, uVector Y,  ui size );
overror_t  __vcuf OVCUAPI   cudaVD_addVUL(  dVector Z, dVector X, ulVector Y, ui size );
overror_t  __vcuf OVCUAPI   cudaVD_subVUL(  dVector Z, dVector X, ulVector Y, ui size );
overror_t  __vcuf OVCUAPI   cudaVD_subrVUL( dVector Z, dVector X, ulVector Y, ui size );
overror_t  __vcuf OVCUAPI   cudaVD_mulVUL(  dVector Z, dVector X, ulVector Y, ui size );
overror_t  __vcuf OVCUAPI   cudaVD_divVUL(  dVector Z, dVector X, ulVector Y, ui size );
overror_t  __vcuf OVCUAPI   cudaVD_divrVUL( dVector Z, dVector X, ulVector Y, ui size );
#ifdef _WIN64
    overror_t  __vcuf OVCUAPI   cudaVD_addVUQ(  dVector Z, dVector X, uqVector Y, ui size );
    overror_t  __vcuf OVCUAPI   cudaVD_subVUQ(  dVector Z, dVector X, uqVector Y, ui size );
    overror_t  __vcuf OVCUAPI   cudaVD_subrVUQ( dVector Z, dVector X, uqVector Y, ui size );
    overror_t  __vcuf OVCUAPI   cudaVD_mulVUQ(  dVector Z, dVector X, uqVector Y, ui size );
    overror_t  __vcuf OVCUAPI   cudaVD_divVUQ(  dVector Z, dVector X, uqVector Y, ui size );
    overror_t  __vcuf OVCUAPI   cudaVD_divrVUQ( dVector Z, dVector X, uqVector Y, ui size );
    #define cudaVD_addVUI  cudaVD_addVUQ
    #define cudaVD_subVUI  cudaVD_subVUQ
    #define cudaVD_subrVUI cudaVD_subrVUQ
    #define cudaVD_mulVUI  cudaVD_mulVUQ
    #define cudaVD_divVUI  cudaVD_divVUQ
    #define cudaVD_divrVUI cudaVD_divrVUQ
#else
    #define cudaVD_addVUI  cudaVD_addVU
    #define cudaVD_subVUI  cudaVD_subVU
    #define cudaVD_subrVUI cudaVD_subrVU
    #define cudaVD_mulVUI  cudaVD_mulVU
    #define cudaVD_divVUI  cudaVD_divVU
    #define cudaVD_divrVUI cudaVD_divrVU
#endif

/******************** Accumulation (Y += X) ******************************/

overror_t  __vcuf OVCUAPI  cudaVD_accV(   dVector Y, dVector  X, ui size );
overror_t  __vcuf OVCUAPI  cudaVD_accVF(  dVector Y, fVector  X, ui size );
overror_t  __vcuf OVCUAPI  cudaVD_accVBI( dVector Y, biVector X, ui size );
overror_t  __vcuf OVCUAPI  cudaVD_accVSI( dVector Y, siVector X, ui size );
overror_t  __vcuf OVCUAPI  cudaVD_accVI(  dVector Y, iVector  X, ui size );
overror_t  __vcuf OVCUAPI  cudaVD_accVLI( dVector Y, liVector X, ui size );
overror_t  __vcuf OVCUAPI  cudaVD_accVQI( dVector Y, qiVector X, ui size );
overror_t  __vcuf OVCUAPI  cudaVD_accVUB( dVector Y, ubVector X, ui size );
overror_t  __vcuf OVCUAPI  cudaVD_accVUS( dVector Y, usVector X, ui size );
overror_t  __vcuf OVCUAPI  cudaVD_accVU(  dVector Y, uVector  X, ui size );
overror_t  __vcuf OVCUAPI  cudaVD_accVUL( dVector Y, ulVector X, ui size );
overror_t  __vcuf OVCUAPI  cudaVD_acc2V(  dVector Y, dVector  X1, dVector  X2, ui size );
overror_t  __vcuf OVCUAPI  cudaVD_acc2VF( dVector Y, fVector  X1, fVector  X2, ui size );
#if defined _WIN64
    overror_t  __vcuf OVCUAPI  cudaVD_accVUQ( dVector Y, uqVector X, ui size );
    #define cudaVD_accVUI   cudaVD_accVUQ
#else
    #define cudaVD_accVUI   cudaVD_accVU
#endif

/***************** Functions of a sub-set of elements  ********************/

overror_t  __vcuf OVCUAPI   cudaVD_subvector_equC(  dVector Y, ui subsiz, ui samp, double C );
overror_t  __vcuf OVCUAPI   cusdVD_subvector_equC(  dVector Y, ui subsiz, ui samp, double *d_C );
overror_t  __vcuf OVCUAPI   cudaVD_subvector_equV(  dVector Y, ui subsiz, ui samp, dVector X );

overror_t  __vcuf OVCUAPI   cudaVD_subvector_addC(  dVector Y, ui subsiz, ui samp, double C );
overror_t  __vcuf OVCUAPI   cudaVD_subvector_subC(  dVector Y, ui subsiz, ui samp, double C );
overror_t  __vcuf OVCUAPI   cudaVD_subvector_subrC( dVector Y, ui subsiz, ui samp, double C );
overror_t  __vcuf OVCUAPI   cudaVD_subvector_mulC(  dVector Y, ui subsiz, ui samp, double C );
overror_t  __vcuf OVCUAPI   cudaVD_subvector_divC(  dVector Y, ui subsiz, ui samp, double C );
overror_t  __vcuf OVCUAPI   cudaVD_subvector_divrC( dVector Y, ui subsiz, ui samp, double C );

overror_t  __vcuf OVCUAPI   cusdVD_subvector_addC(  dVector Y, ui subsiz, ui samp, double *d_C );
overror_t  __vcuf OVCUAPI   cusdVD_subvector_subC(  dVector Y, ui subsiz, ui samp, double *d_C );
overror_t  __vcuf OVCUAPI   cusdVD_subvector_subrC( dVector Y, ui subsiz, ui samp, double *d_C );
overror_t  __vcuf OVCUAPI   cusdVD_subvector_mulC(  dVector Y, ui subsiz, ui samp, double *d_C );
overror_t  __vcuf OVCUAPI   cusdVD_subvector_divC(  dVector Y, ui subsiz, ui samp, double *d_C );
overror_t  __vcuf OVCUAPI   cusdVD_subvector_divrC( dVector Y, ui subsiz, ui samp, double *d_C );

overror_t  __vcuf OVCUAPI   cudaVD_subvector_addV(  dVector Y, ui subsiz, ui samp, dVector X );
overror_t  __vcuf OVCUAPI   cudaVD_subvector_subV(  dVector Y, ui subsiz, ui samp, dVector X );
overror_t  __vcuf OVCUAPI   cudaVD_subvector_subrV( dVector Y, ui subsiz, ui samp, dVector X );
overror_t  __vcuf OVCUAPI   cudaVD_subvector_mulV(  dVector Y, ui subsiz, ui samp, dVector X );
overror_t  __vcuf OVCUAPI   cudaVD_subvector_divV(  dVector Y, ui subsiz, ui samp, dVector X );
overror_t  __vcuf OVCUAPI   cudaVD_subvector_divrV( dVector Y, ui subsiz, ui samp, dVector X );


/*********************  Mathematical Functions ***********************/

overror_t  __vcuf OVCUAPI   cudaVD_abs( dVector Y, dVector X, ui size );
overror_t  __vcuf OVCUAPI   cudaVD_neg( dVector Y, dVector X, ui size );
overror_t  __vcuf OVCUAPI   cudaVD_inv( dVector Y, dVector X, ui size );
overror_t  __vcuf OVCUAPI   cudaVDx_inv( dVector Y, dVector X, ui size, double A, double B );
overror_t  __vcuf OVCUAPI   cusdVDx_inv( dVector Y, dVector X, ui size, double *d_A, double *d_B );
overror_t  __vcuf OVCUAPI   cudaVD_intfrac( dVector Int, dVector Frac, dVector X, ui size );
#define      cudaVD_modf    cudaVD_intfrac
overror_t  __vcuf OVCUAPI   cudaVD_mantexp( dVector Mant, iVector Exp, dVector X, ui size );
#define      cudaVD_frexp   cudaVD_mantexp

overror_t  __vcuf OVCUAPI   cudaVD_hypotC( dVector Y, dVector X, ui size, double C );
overror_t  __vcuf OVCUAPI   cusdVD_hypotC( dVector Y, dVector X, ui size, double *d_C );
overror_t  __vcuf OVCUAPI   cudaVD_hypotV( dVector Z, dVector X, dVector Y, ui size );
overror_t  __vcuf OVCUAPI   cudaVDx_hypotV( dVector Z, dVector X, dVector Y, ui size, double A, double B );
overror_t  __vcuf OVCUAPI   cusdVDx_hypotV( dVector Z, dVector X, dVector Y, ui size, double *d_A, double *d_B );

overror_t  __vcuf OVCUAPI   cudaVD_scale2( dVector Y, dVector X, ui size, int expo );
overror_t  __vcuf OVCUAPI   cudaVD_scale10( dVector Y, dVector X, ui size, int expo );
#define      cudaVD_ldexp    cudaVD_scale2

overror_t  __vcuf OVCUAPI   cudaVD_square( dVector Y, dVector X, ui size );
overror_t  __vcuf OVCUAPI   cudaVDx_square( dVector Y, dVector X, ui size, double A, double B );
overror_t  __vcuf OVCUAPI   cudaVD_cubic( dVector Y, dVector X, ui size );
overror_t  __vcuf OVCUAPI   cudaVDx_cubic( dVector Y, dVector X, ui size, double A, double B );
overror_t  __vcuf OVCUAPI   cudaVD_quartic( dVector Y, dVector X, ui size );
overror_t  __vcuf OVCUAPI   cudaVDx_quartic( dVector Y, dVector X, ui size, double A, double B );
overror_t  __vcuf OVCUAPI   cudaVD_poly( dVector Y, dVector X, ui size, dVector h_Coeff, unsigned deg );
overror_t  __vcuf OVCUAPI   cudaVDx_poly( dVector Y, dVector X, ui size, dVector h_Coeff, unsigned deg, double A, double B );
overror_t  __vcuf OVCUAPI   cudaVD_ipow( dVector Y, dVector X, ui size, int ipow );
overror_t  __vcuf OVCUAPI   cudaVDx_ipow( dVector Y, dVector X, ui size, int ipow, double A, double B, double C );
                           /*  ipow = integer power of x */
overror_t  __vcuf OVCUAPI   cusdVDx_square( dVector Y, dVector X, ui size, double *d_A, double *d_B );
overror_t  __vcuf OVCUAPI   cusdVDx_cubic( dVector Y, dVector X, ui size, double *d_A, double *d_B );
overror_t  __vcuf OVCUAPI   cusdVDx_quartic( dVector Y, dVector X, ui size, double *d_A, double *d_B );
overror_t  __vcuf OVCUAPI   cusdVD_poly( dVector Y, dVector X, ui size, dVector d_Coeff, unsigned deg );
overror_t  __vcuf OVCUAPI   cusdVDx_poly( dVector Y, dVector X, ui size, dVector d_Coeff, unsigned deg, double *d_A, double *d_B );
overror_t  __vcuf OVCUAPI   cusdVDx_ipow( dVector Y, dVector X, ui size, int ipow, double *d_A, double *d_B, double *d_C );

       /* extra fast integer powers: "unprotected", without error handling: */
overror_t  __vcuf OVCUAPI   cudaVDu_square( dVector Y, dVector X, ui size );
overror_t  __vcuf OVCUAPI   cudaVDux_square( dVector Y, dVector X, ui size, double A, double B );
overror_t  __vcuf OVCUAPI   cudaVDu_cubic( dVector Y, dVector X, ui size );
overror_t  __vcuf OVCUAPI   cudaVDux_cubic( dVector Y, dVector X, ui size, double A, double B );
overror_t  __vcuf OVCUAPI   cudaVDu_quartic( dVector Y, dVector X, ui size );
overror_t  __vcuf OVCUAPI   cudaVDux_quartic( dVector Y, dVector X, ui size, double A, double B );
overror_t  __vcuf OVCUAPI   cudaVDu_poly( dVector Y, dVector X, ui size, dVector h_Coeff, unsigned deg );
overror_t  __vcuf OVCUAPI   cudaVDux_poly( dVector Y, dVector X, ui size, dVector h_Coeff, unsigned deg, double A, double B );
overror_t  __vcuf OVCUAPI   cudaVDu_ipow( dVector Y, dVector X, ui size, int ipow );
overror_t  __vcuf OVCUAPI   cudaVDux_ipow( dVector Y, dVector X, ui size, int ipow, double A, double B, double C );

overror_t  __vcuf OVCUAPI   cusdVDux_square( dVector Y, dVector X, ui size, double *d_A, double *d_B );
overror_t  __vcuf OVCUAPI   cusdVDux_cubic( dVector Y, dVector X, ui size, double *d_A, double *d_B );
overror_t  __vcuf OVCUAPI   cusdVDux_quartic( dVector Y, dVector X, ui size, double *d_A, double *d_B );
overror_t  __vcuf OVCUAPI   cusdVDu_poly( dVector Y, dVector X, ui size, dVector d_Coeff, unsigned deg );
overror_t  __vcuf OVCUAPI   cusdVDux_poly( dVector Y, dVector X, ui size, dVector d_Coeff, unsigned deg, double *d_A, double *d_B );
overror_t  __vcuf OVCUAPI   cusdVDux_ipow( dVector Y, dVector X, ui size, int ipow, double *d_A, double *d_B, double *d_C );

overror_t  __vcuf OVCUAPI   cudaVD_ipow2(  dVector Y, iVector X, ui size );
overror_t  __vcuf OVCUAPI   cudaVD_ipow10( dVector Y, iVector X, ui size );
                          /* ipow2 and ipow10: integer powers of 2 and 10 */

overror_t  __vcuf OVCUAPI   cudaVD_pow(    dVector Y, dVector X, ui size, double expo );
overror_t  __vcuf OVCUAPI   cudaVDx_pow(   dVector Y, dVector X, ui size, double expo, double A, double B, double C );

overror_t  __vcuf OVCUAPI   cudaVD_pow2(   dVector Y, dVector X, ui size );
overror_t  __vcuf OVCUAPI   cudaVDx_pow2(  dVector Y, dVector X, ui size, double A, double B, double C );
overror_t  __vcuf OVCUAPI   cudaVD_pow10(  dVector Y, dVector X, ui size );
overror_t  __vcuf OVCUAPI   cudaVDx_pow10( dVector Y, dVector X, ui size, double A, double B, double C );

overror_t  __vcuf OVCUAPI   cusdVDx_pow(   dVector Y, dVector X, ui size, double expo, double *d_A, double *d_B, double *d_C );
overror_t  __vcuf OVCUAPI   cusdVDx_pow2(  dVector Y, dVector X, ui size, double *d_A, double *d_B, double *d_C );
overror_t  __vcuf OVCUAPI   cusdVDx_pow10( dVector Y, dVector X, ui size, double *d_A, double *d_B, double *d_C );
            /* pow2 and pow10: basis 2 or 10 raised to power x */

overror_t  __vcuf OVCUAPI   cudaVD_sqrt(  dVector Y, dVector X, ui size );
overror_t  __vcuf OVCUAPI   cudaVDx_sqrt( dVector Y, dVector X, ui size, double A, double B, double C );

overror_t  __vcuf OVCUAPI   cudaVD_log(    dVector Y, dVector X, ui size );
overror_t  __vcuf OVCUAPI   cudaVD_log2(   dVector Y, dVector X, ui size );
overror_t  __vcuf OVCUAPI   cudaVD_log10(  dVector Y, dVector X, ui size );
#define     cudaVD_ln      cudaVD_log
overror_t  __vcuf OVCUAPI   cudaVDx_log(   dVector Y, dVector X, ui size, double A, double B, double C );
overror_t  __vcuf OVCUAPI   cudaVDx_log2(  dVector Y, dVector X, ui size, double A, double B, double C );
overror_t  __vcuf OVCUAPI   cudaVDx_log10( dVector Y, dVector X, ui size, double A, double B, double C );
#define     cudaVDx_ln     cudaVDx_log

overror_t  __vcuf OVCUAPI   cudaVD_OD( dVector OD, dVector X, dVector X0, ui size );  /* OD = log10( X0/X ) */
overror_t  __vcuf OVCUAPI   cudaVD_ODwDark( dVector OD, dVector X, dVector XDark,
                        dVector X0, dVector X0Dark, ui size );
void  __vcuf OVCUAPI   cudaVD_setODThresh( double minX, double minX0 );

overror_t  __vcuf OVCUAPI   cudaVD_exp(   dVector Y, dVector X, ui size );
overror_t  __vcuf OVCUAPI   cudaVDx_exp(  dVector Y, dVector X, ui size, double A, double B, double C );
overror_t  __vcuf OVCUAPI   cudaVD_expArbBase(  dVector Y, dVector X, ui size, double Base );
overror_t  __vcuf OVCUAPI   cudaVDx_expArbBase( dVector Y, dVector X, ui size, double Base,
                            double A, double B, double C );
overror_t  __vcuf OVCUAPI   cudaVD_expc(  dVector Y, dVector X, ui size );
overror_t  __vcuf OVCUAPI   cudaVDx_expc( dVector Y, dVector X, ui size, double A, double B, double C );
                /* expc(x) = 1 - exp(x)  */
overror_t  __vcuf OVCUAPI   cudaVD_expmx2(  dVector Y, dVector X, ui size );
overror_t  __vcuf OVCUAPI   cudaVDx_expmx2( dVector Y, dVector X, ui size, double A, double B, double C );
                /* expmx2(x) = exp( -x**2 )  */
#define cudaVD_exp2   cudaVD_pow2
#define cudaVDx_exp2  cudaVDx_pow2
#define cudaVD_exp10   cudaVD_pow10
#define cudaVDx_exp10  cudaVDx_pow10
overror_t  __vcuf OVCUAPI   cudaVD_powexp( dVector Y, dVector X, ui size, double expo );
overror_t  __vcuf OVCUAPI   cudaVDx_powexp( dVector Y, dVector X, ui size, double expo, double A, double B, double C );

overror_t  __vcuf OVCUAPI   cudaVD_erf(     dVector Y, dVector X, ui size );
overror_t  __vcuf OVCUAPI   cudaVDx_erf(    dVector Y, dVector X, ui size, double A, double B, double C );
overror_t  __vcuf OVCUAPI   cudaVD_erfc(    dVector Y, dVector X, ui size );
overror_t  __vcuf OVCUAPI   cudaVDx_erfc(   dVector Y, dVector X, ui size, double A, double B, double C );
overror_t  __vcuf OVCUAPI   cudaVD_Gauss(   dVector Y, dVector X, ui size, double Wid, double Cent, double C );
#define cudaVD_gauss cudaVD_Gauss
overror_t  __vcuf OVCUAPI   cudaVD_Lorentz( dVector Y, dVector X, ui size, double Wid, double Cent, double C );
#define cudaVD_lorentz cudaVD_Lorentz

void __vcuf OVCUAPI   cusdVD_setODThresh( double *d_minX, double *d_minX0 );
overror_t  __vcuf OVCUAPI   cusdVDx_sqrt( dVector Y, dVector X, ui size, double *d_A, double *d_B, double *d_C );
overror_t  __vcuf OVCUAPI   cusdVDx_log(   dVector Y, dVector X, ui size, double *d_A, double *d_B, double *d_C );
overror_t  __vcuf OVCUAPI   cusdVDx_log2(  dVector Y, dVector X, ui size, double *d_A, double *d_B, double *d_C );
overror_t  __vcuf OVCUAPI   cusdVDx_log10( dVector Y, dVector X, ui size, double *d_A, double *d_B, double *d_C );
#define     cusdVDx_ln     cusdVDx_log
overror_t  __vcuf OVCUAPI   cusdVDx_exp(  dVector Y, dVector X, ui size, double *d_A, double *d_B, double *d_C );
overror_t  __vcuf OVCUAPI   cusdVDx_expArbBase( dVector Y, dVector X, ui size, double *d_Base,
                            double *d_A, double *d_B, double *d_C );
overror_t  __vcuf OVCUAPI   cusdVDx_expc( dVector Y, dVector X, ui size, double *d_A, double *d_B, double *d_C );
overror_t  __vcuf OVCUAPI   cusdVDx_expmx2( dVector Y, dVector X, ui size, double *d_A, double *d_B, double *d_C );
#define cusdVDx_exp2  cusdVDx_pow2;
#define cusdVDx_exp10  cusdVDx_pow10;
overror_t  __vcuf OVCUAPI   cusdVDx_powexp( dVector Y, dVector X, ui size, double expo, double *d_A, double *d_B, double *d_C );
overror_t  __vcuf OVCUAPI   cusdVDx_erf(    dVector Y, dVector X, ui size, double *d_A, double *d_B, double *d_C );
overror_t  __vcuf OVCUAPI   cusdVDx_erfc(   dVector Y, dVector X, ui size, double *d_A, double *d_B, double *d_C );
overror_t  __vcuf OVCUAPI   cusdVD_Gauss(   dVector Y, dVector X, ui size, double *d_Wid, double *d_Cent, double *d_C );
#define cusdVD_gauss cusdVD_Gauss
overror_t  __vcuf OVCUAPI   cusdVD_Lorentz( dVector Y, dVector X, ui size, double *d_Wid, double *d_Cent, double *d_C );
#define cusdVD_lorentz cusdVD_Lorentz

overror_t  __vcuf OVCUAPI   cudaVD_sin(     dVector Y, dVector X, ui size );
overror_t  __vcuf OVCUAPI   cudaVDx_sin(    dVector Y, dVector X, ui size, double A, double B, double C );
overror_t  __vcuf OVCUAPI   cudaVD_cos(     dVector Y, dVector X, ui size );
overror_t  __vcuf OVCUAPI   cudaVDx_cos(    dVector Y, dVector X, ui size, double A, double B, double C );
overror_t  __vcuf OVCUAPI   cudaVD_sincos(  dVector Sin, dVector Cos, dVector X, ui size );
overror_t  __vcuf OVCUAPI   cudaVDx_sincos( dVector Sin, dVector Cos, dVector X, ui size, double A, double B, double C );

overror_t  __vcuf OVCUAPI   cudaVD_tan(     dVector Y, dVector X, ui size );
overror_t  __vcuf OVCUAPI   cudaVDx_tan(    dVector Y, dVector X, ui size, double A, double B, double C );
overror_t  __vcuf OVCUAPI   cudaVD_cot(     dVector Y, dVector X, ui size );
overror_t  __vcuf OVCUAPI   cudaVDx_cot(    dVector Y, dVector X, ui size, double A, double B, double C );

overror_t  __vcuf OVCUAPI   cudaVD_sec(     dVector Y, dVector X, ui size );
overror_t  __vcuf OVCUAPI   cudaVDx_sec(    dVector Y, dVector X, ui size, double A, double B, double C );
overror_t  __vcuf OVCUAPI   cudaVD_cosec(   dVector Y, dVector X, ui size );
overror_t  __vcuf OVCUAPI   cudaVDx_cosec(  dVector Y, dVector X, ui size, double A, double B, double C );

overror_t  __vcuf OVCUAPI   cudaVD_sin2(    dVector Y, dVector X, ui size );
overror_t  __vcuf OVCUAPI   cudaVDx_sin2(   dVector Y, dVector X, ui size, double A, double B, double C );
overror_t  __vcuf OVCUAPI   cudaVD_cos2(    dVector Y, dVector X, ui size );
overror_t  __vcuf OVCUAPI   cudaVDx_cos2(   dVector Y, dVector X, ui size, double A, double B, double C );
overror_t  __vcuf OVCUAPI   cudaVD_sincos2( dVector Sin, dVector Cos, dVector X, ui size );
overror_t  __vcuf OVCUAPI   cudaVDx_sincos2( dVector Sin, dVector Cos, dVector X, ui size, double A, double B, double C );

overror_t  __vcuf OVCUAPI   cudaVD_tan2(     dVector Y, dVector X, ui size );
overror_t  __vcuf OVCUAPI   cudaVDx_tan2(    dVector Y, dVector X, ui size, double A, double B, double C );
overror_t  __vcuf OVCUAPI   cudaVD_cot2(     dVector Y, dVector X, ui size );
overror_t  __vcuf OVCUAPI   cudaVDx_cot2(    dVector Y, dVector X, ui size, double A, double B, double C );
overror_t  __vcuf OVCUAPI   cudaVD_sec2(     dVector Y, dVector X, ui size );
overror_t  __vcuf OVCUAPI   cudaVDx_sec2(    dVector Y, dVector X, ui size, double A, double B, double C );
overror_t  __vcuf OVCUAPI   cudaVD_cosec2(   dVector Y, dVector X, ui size );
overror_t  __vcuf OVCUAPI   cudaVDx_cosec2(  dVector Y, dVector X, ui size, double A, double B, double C );

 /*  reduced-range sine and cosine for -2Pi <= x <= +2Pi */
/*
overror_t  __vcuf OVCUAPI   cudaVDr_sin(     dVector Y, dVector X, ui size );
overror_t  __vcuf OVCUAPI   cudaVDrx_sin(    dVector Y, dVector X, ui size, double A, double B, double C );
overror_t  __vcuf OVCUAPI   cudaVDr_cos(     dVector Y, dVector X, ui size );
overror_t  __vcuf OVCUAPI   cudaVDrx_cos(    dVector Y, dVector X, ui size, double A, double B, double C );
overror_t  __vcuf OVCUAPI   cudaVDr_sincos(  dVector YSin, dVector YCos, dVector X, ui size );
overror_t  __vcuf OVCUAPI   cudaVDrx_sincos( dVector YSin, dVector YCos, dVector X, ui size, double A, double B, double C );
overror_t  __vcuf OVCUAPI   cudaVDr_sin2(     dVector Y, dVector X, ui size );
overror_t  __vcuf OVCUAPI   cudaVDrx_sin2(    dVector Y, dVector X, ui size, double A, double B, double C );
overror_t  __vcuf OVCUAPI   cudaVDr_cos2(     dVector Y, dVector X, ui size );
overror_t  __vcuf OVCUAPI   cudaVDrx_cos2(    dVector Y, dVector X, ui size, double A, double B, double C );
overror_t  __vcuf OVCUAPI   cudaVDr_sincos2(  dVector YSin, dVector YCos, dVector X, ui size );
overror_t  __vcuf OVCUAPI   cudaVDrx_sincos2( dVector YSin, dVector YCos, dVector X, ui size, double A, double B, double C );
*/

/* trigonometric functions of rational multiples of Pi: x = p/q * Pi */
overror_t  __vcuf OVCUAPI   cudaVD_sinrpi(   dVector Y, iVector P, ui size, int q );
overror_t  __vcuf OVCUAPI   cudaVD_cosrpi(   dVector Y, iVector P, ui size, int q );
overror_t  __vcuf OVCUAPI   cudaVD_sincosrpi( dVector YSin, dVector YCos, iVector P, ui size, int q );
overror_t  __vcuf OVCUAPI   cudaVD_tanrpi(   dVector Y, iVector P, ui size, int q );
overror_t  __vcuf OVCUAPI   cudaVD_cotrpi(   dVector Y, iVector P, ui size, int q );
overror_t  __vcuf OVCUAPI   cudaVD_secrpi(   dVector Y, iVector P, ui size, int q );
overror_t  __vcuf OVCUAPI   cudaVD_cosecrpi( dVector Y, iVector P, ui size, int q );

overror_t  __vcuf OVCUAPI   cudaVD_sinrpi2(  dVector Y, iVector P, ui size, int q );
overror_t  __vcuf OVCUAPI   cudaVD_cosrpi2(  dVector Y, iVector P, ui size, int q );
overror_t  __vcuf OVCUAPI   cudaVD_sincosrpi2( dVector YSin, dVector YCos, iVector P, ui size, int q );
overror_t  __vcuf OVCUAPI   cudaVD_tanrpi2(  dVector Y, iVector P, ui size, int q );
overror_t  __vcuf OVCUAPI   cudaVD_cotrpi2(  dVector Y, iVector P, ui size, int q );
overror_t  __vcuf OVCUAPI   cudaVD_secrpi2(  dVector Y, iVector P, ui size, int q );
overror_t  __vcuf OVCUAPI   cudaVD_cosecrpi2( dVector Y, iVector P, ui size, int q );

overror_t  __vcuf OVCUAPI   cudaVD_sinrpi3(  dVector Y, iVector P, ui size, int q );
overror_t  __vcuf OVCUAPI   cudaVD_cosrpi3(  dVector Y, iVector P, ui size, int q );
overror_t  __vcuf OVCUAPI   cudaVD_sincosrpi3( dVector YSin, dVector YCos, iVector P, ui size, int q );
overror_t  __vcuf OVCUAPI   cudaVD_tanrpi3(  dVector Y, iVector P, ui size, int q );
overror_t  __vcuf OVCUAPI   cudaVD_cotrpi3(  dVector Y, iVector P, ui size, int q );
overror_t  __vcuf OVCUAPI   cudaVD_secrpi3(  dVector Y, iVector P, ui size, int q );
overror_t  __vcuf OVCUAPI   cudaVD_cosecrpi3( dVector Y, iVector P, ui size, int q );


overror_t  __vcuf OVCUAPI   cudaVD_sinc(     dVector Y, dVector X, ui size );
overror_t  __vcuf OVCUAPI   cudaVDx_sinc(    dVector Y, dVector X, ui size, double A, double B, double C );
overror_t  __vcuf OVCUAPI   cudaVD_Kepler(   dVector Y, dVector X, ui size, double T, double e );
overror_t  __vcuf OVCUAPI   cudaVDx_Kepler(  dVector Y, dVector X, ui size, double T, double e, double A, double B );
#define cudaVD_kepler  cudaVD_Kepler
#define cudaVDx_kepler cudaVDx_Kepler

overror_t  __vcuf OVCUAPI   cudaVD_asin(    dVector Y, dVector X, ui size );
overror_t  __vcuf OVCUAPI   cudaVDx_asin(   dVector Y, dVector X, ui size, double A, double B, double C );
overror_t  __vcuf OVCUAPI   cudaVD_acos(    dVector Y, dVector X, ui size );
overror_t  __vcuf OVCUAPI   cudaVDx_acos(   dVector Y, dVector X, ui size, double A, double B, double C );
overror_t  __vcuf OVCUAPI   cudaVD_atan(    dVector Y, dVector X, ui size );
overror_t  __vcuf OVCUAPI   cudaVDx_atan(   dVector Y, dVector X, ui size, double A, double B, double C );
overror_t  __vcuf OVCUAPI   cudaVD_atan2(   dVector Z, dVector X, dVector Y, ui size );
overror_t  __vcuf OVCUAPI   cudaVDx_atan2(  dVector Z, dVector X, dVector Y, ui size, double A, double B, double C );

overror_t  __vcuf OVCUAPI   cudaVD_sinh(    dVector Y, dVector X, ui size );
overror_t  __vcuf OVCUAPI   cudaVDx_sinh(   dVector Y, dVector X, ui size, double A, double B, double C );
overror_t  __vcuf OVCUAPI   cudaVD_cosh(    dVector Y, dVector X, ui size );
overror_t  __vcuf OVCUAPI   cudaVDx_cosh(   dVector Y, dVector X, ui size, double A, double B, double C );
overror_t  __vcuf OVCUAPI   cudaVD_tanh(    dVector Y, dVector X, ui size );
overror_t  __vcuf OVCUAPI   cudaVDx_tanh(   dVector Y, dVector X, ui size, double A, double B, double C );
overror_t  __vcuf OVCUAPI   cudaVD_coth(    dVector Y, dVector X, ui size );
overror_t  __vcuf OVCUAPI   cudaVDx_coth(   dVector Y, dVector X, ui size, double A, double B, double C );
overror_t  __vcuf OVCUAPI   cudaVD_sech(    dVector Y, dVector X, ui size );
overror_t  __vcuf OVCUAPI   cudaVDx_sech(   dVector Y, dVector X, ui size, double A, double B, double C );
overror_t  __vcuf OVCUAPI   cudaVD_cosech(  dVector Y, dVector X, ui size );
overror_t  __vcuf OVCUAPI   cudaVDx_cosech( dVector Y, dVector X, ui size, double A, double B, double C );
overror_t  __vcuf OVCUAPI   cudaVD_sech2(   dVector Y, dVector X, ui size );
overror_t  __vcuf OVCUAPI   cudaVDx_sech2(  dVector Y, dVector X, ui size, double A, double B, double C );
overror_t  __vcuf OVCUAPI   cudaVD_Langevin( dVector Y, dVector X, ui size ); /* coth(x)-1/x */
overror_t  __vcuf OVCUAPI   cudaVDx_Langevin(dVector Y, dVector X, ui size, double A, double B, double C );
#define cudaVD_langevin  cudaVD_Langevin
#define cudaVDx_langevin cudaVDx_Langevin


overror_t  __vcuf OVCUAPI   cusdVDx_sin(    dVector Y, dVector X, ui size, double *d_A, double *d_B, double *d_C );
overror_t  __vcuf OVCUAPI   cusdVDx_cos(    dVector Y, dVector X, ui size, double *d_A, double *d_B, double *d_C );
overror_t  __vcuf OVCUAPI   cusdVDx_sincos( dVector Sin, dVector *d_Cos, dVector X, ui size, double *d_A, double *d_B, double *d_C );
overror_t  __vcuf OVCUAPI   cusdVDx_tan(    dVector Y, dVector X, ui size, double *d_A, double *d_B, double *d_C );
overror_t  __vcuf OVCUAPI   cusdVDx_cot(    dVector Y, dVector X, ui size, double *d_A, double *d_B, double *d_C );
overror_t  __vcuf OVCUAPI   cusdVDx_sec(    dVector Y, dVector X, ui size, double *d_A, double *d_B, double *d_C );
overror_t  __vcuf OVCUAPI   cusdVDx_cosec(  dVector Y, dVector X, ui size, double *d_A, double *d_B, double *d_C );
overror_t  __vcuf OVCUAPI   cusdVDx_sin2(   dVector Y, dVector X, ui size, double *d_A, double *d_B, double *d_C );
overror_t  __vcuf OVCUAPI   cusdVDx_cos2(   dVector Y, dVector X, ui size, double *d_A, double *d_B, double *d_C );
overror_t  __vcuf OVCUAPI   cusdVDx_sincos2( dVector Sin, dVector *d_Cos, dVector X, ui size, double *d_A, double *d_B, double *d_C );
overror_t  __vcuf OVCUAPI   cusdVDx_tan2(    dVector Y, dVector X, ui size, double *d_A, double *d_B, double *d_C );
overror_t  __vcuf OVCUAPI   cusdVDx_cot2(    dVector Y, dVector X, ui size, double *d_A, double *d_B, double *d_C );
overror_t  __vcuf OVCUAPI   cusdVDx_sec2(    dVector Y, dVector X, ui size, double *d_A, double *d_B, double *d_C );
overror_t  __vcuf OVCUAPI   cusdVDx_cosec2(  dVector Y, dVector X, ui size, double *d_A, double *d_B, double *d_C );
overror_t  __vcuf OVCUAPI   cusdVDx_sinc(    dVector Y, dVector X, ui size, double *d_A, double *d_B, double *d_C );
overror_t  __vcuf OVCUAPI   cusdVD_Kepler(   dVector Y, dVector X, ui size, double *T, double *e );
overror_t  __vcuf OVCUAPI   cusdVDx_Kepler(  dVector Y, dVector X, ui size, double *T, double *e, double *d_A, double *d_B );
#define cusdVD_kepler  cusdVD_Kepler
#define cusdVDx_kepler cusdVDx_Kepler
overror_t  __vcuf OVCUAPI   cusdVDx_asin(   dVector Y, dVector X, ui size, double *d_A, double *d_B, double *d_C );
overror_t  __vcuf OVCUAPI   cusdVDx_acos(   dVector Y, dVector X, ui size, double *d_A, double *d_B, double *d_C );
overror_t  __vcuf OVCUAPI   cusdVDx_atan(   dVector Y, dVector X, ui size, double *d_A, double *d_B, double *d_C );
overror_t  __vcuf OVCUAPI   cusdVDx_atan2(  dVector Z, dVector X, dVector Y, ui size, double *d_A, double *d_B, double *d_C );
overror_t  __vcuf OVCUAPI   cusdVDx_sinh(   dVector Y, dVector X, ui size, double *d_A, double *d_B, double *d_C );
overror_t  __vcuf OVCUAPI   cusdVDx_cosh(   dVector Y, dVector X, ui size, double *d_A, double *d_B, double *d_C );
overror_t  __vcuf OVCUAPI   cusdVDx_tanh(   dVector Y, dVector X, ui size, double *d_A, double *d_B, double *d_C );
overror_t  __vcuf OVCUAPI   cusdVDx_coth(   dVector Y, dVector X, ui size, double *d_A, double *d_B, double *d_C );
overror_t  __vcuf OVCUAPI   cusdVDx_sech(   dVector Y, dVector X, ui size, double *d_A, double *d_B, double *d_C );
overror_t  __vcuf OVCUAPI   cusdVDx_cosech( dVector Y, dVector X, ui size, double *d_A, double *d_B, double *d_C );
overror_t  __vcuf OVCUAPI   cusdVDx_sech2(  dVector Y, dVector X, ui size, double *d_A, double *d_B, double *d_C );
overror_t  __vcuf OVCUAPI   cusdVDx_Langevin(dVector Y, dVector X, ui size, double *d_A, double *d_B, double *d_C );
#define cusdVDx_langevin cusdVDx_Langevin

#ifdef __cplusplus
}  // end of extern "C"
#endif


/******************  VDcu_ functions: **********************************
	act on host memory, using the CUDA device for processing
************************************************************************/

#ifdef __cplusplus
extern "C" {
#endif

/**************************  Rounding **********************************/

int  __vf OVCUAPI   VDcu_round(  dVector  Y, dVector X, ui size );
int  __vf OVCUAPI   VDcu_roundtoBI( biVector Y, dVector X, ui size );
int  __vf OVCUAPI   VDcu_roundtoSI( siVector Y, dVector X, ui size );
int  __vf OVCUAPI   VDcu_roundtoI(  iVector  Y, dVector X, ui size );
int  __vf OVCUAPI   VDcu_roundtoLI( liVector Y, dVector X, ui size );
int  __vf OVCUAPI   VDcu_roundtoQI( qiVector Y, dVector X, ui size );
int  __vf OVCUAPI   VDcu_roundtoUB( ubVector Y, dVector X, ui size );
int  __vf OVCUAPI   VDcu_roundtoUS( usVector Y, dVector X, ui size );
int  __vf OVCUAPI   VDcu_roundtoU(  uVector  Y, dVector X, ui size );
int  __vf OVCUAPI   VDcu_roundtoUL( ulVector Y, dVector X, ui size );
#ifdef _WIN64
    int  __vf OVCUAPI   VDcu_roundtoUQ( uqVector Y, dVector X, ui size );
#endif

int  __vf OVCUAPI   VDcu_floor(  dVector  Y, dVector X, ui size );
int  __vf OVCUAPI   VDcu_floortoBI( biVector Y, dVector X, ui size );
int  __vf OVCUAPI   VDcu_floortoSI( siVector Y, dVector X, ui size );
int  __vf OVCUAPI   VDcu_floortoI(  iVector  Y, dVector X, ui size );
int  __vf OVCUAPI   VDcu_floortoLI( liVector Y, dVector X, ui size );
int  __vf OVCUAPI   VDcu_floortoQI( qiVector Y, dVector X, ui size );
int  __vf OVCUAPI   VDcu_floortoUB( ubVector Y, dVector X, ui size );
int  __vf OVCUAPI   VDcu_floortoUS( usVector Y, dVector X, ui size );
int  __vf OVCUAPI   VDcu_floortoU(  uVector  Y, dVector X, ui size );
int  __vf OVCUAPI   VDcu_floortoUL( ulVector Y, dVector X, ui size );
#ifdef _WIN64
    int  __vf OVCUAPI   VDcu_floortoUQ( uqVector Y, dVector X, ui size );
#endif

int  __vf OVCUAPI   VDcu_ceil(  dVector  Y, dVector X, ui size );
int  __vf OVCUAPI   VDcu_ceiltoBI( biVector Y, dVector X, ui size );
int  __vf OVCUAPI   VDcu_ceiltoSI( siVector Y, dVector X, ui size );
int  __vf OVCUAPI   VDcu_ceiltoI(  iVector  Y, dVector X, ui size );
int  __vf OVCUAPI   VDcu_ceiltoLI( liVector Y, dVector X, ui size );
int  __vf OVCUAPI   VDcu_ceiltoQI( qiVector Y, dVector X, ui size );
int  __vf OVCUAPI   VDcu_ceiltoUB( ubVector Y, dVector X, ui size );
int  __vf OVCUAPI   VDcu_ceiltoUS( usVector Y, dVector X, ui size );
int  __vf OVCUAPI   VDcu_ceiltoU(  uVector  Y, dVector X, ui size );
int  __vf OVCUAPI   VDcu_ceiltoUL( ulVector Y, dVector X, ui size );
#ifdef _WIN64
    int  __vf OVCUAPI   VDcu_ceiltoUQ( uqVector Y, dVector X, ui size );
#endif

int  __vf OVCUAPI   VDcu_chop(  dVector  Y, dVector X, ui size );
int  __vf OVCUAPI   VDcu_choptoBI( biVector Y, dVector X, ui size );
int  __vf OVCUAPI   VDcu_choptoSI( siVector Y, dVector X, ui size );
int  __vf OVCUAPI   VDcu_choptoI(  iVector  Y, dVector X, ui size );
int  __vf OVCUAPI   VDcu_choptoLI( liVector Y, dVector X, ui size );
int  __vf OVCUAPI   VDcu_choptoQI( qiVector Y, dVector X, ui size );
int  __vf OVCUAPI   VDcu_choptoUB( ubVector Y, dVector X, ui size );
int  __vf OVCUAPI   VDcu_choptoUS( usVector Y, dVector X, ui size );
int  __vf OVCUAPI   VDcu_choptoU(  uVector  Y, dVector X, ui size );
int  __vf OVCUAPI   VDcu_choptoUL( ulVector Y, dVector X, ui size );
#ifdef _WIN64
    int  __vf OVCUAPI   VDcu_choptoUQ( uqVector Y, dVector X, ui size );
#endif

#define VDcu_trunc      VDcu_chop
#define VDcu_trunctoBI  VDcu_choptoBI
#define VDcu_trunctoSI  VDcu_choptoSI
#define VDcu_trunctoI   VDcu_choptoI
#define VDcu_trunctoLI  VDcu_choptoLI
#define VDcu_trunctoQI  VDcu_choptoQI
#define VDcu_trunctoUB  VDcu_choptoUB
#define VDcu_trunctoUS  VDcu_choptoUS
#define VDcu_trunctoU   VDcu_choptoU
#define VDcu_trunctoUL  VDcu_choptoUL
#define VDcu_trunctoUQ  VDcu_choptoUQ

#if defined _WIN64
      #define   VDcu_roundtoUI    VDcu_roundtoUQ
      #define   VDcu_floortoUI    VDcu_floortoUQ
      #define   VDcu_ceiltoUI     VDcu_ceiltoUQ
      #define   VDcu_choptoUI     VDcu_choptoUQ
      #define   VDcu_trunctoUI    VDcu_trunctoUQ
#else
      #define   VDcu_roundtoUI    VDcu_roundtoU
      #define   VDcu_floortoUI    VDcu_floortoU
      #define   VDcu_ceiltoUI     VDcu_ceiltoU
      #define   VDcu_choptoUI     VDcu_choptoU
      #define   VDcu_trunctoUI    VDcu_trunctoU
#endif

/********************  Comparisons ********************************/

void __vf OVCUAPI   VDcu_cmp0(    dVector Y, dVector X, ui size );
ui   __vf OVCUAPI   VDcu_cmp_eq0( dVector Y, dVector X, ui size );
ui   __vf OVCUAPI   VDcu_cmp_ne0( dVector Y, dVector X, ui size );
ui   __vf OVCUAPI   VDcu_cmp_le0( dVector Y, dVector X, ui size );
ui   __vf OVCUAPI   VDcu_cmp_lt0( dVector Y, dVector X, ui size );
ui   __vf OVCUAPI   VDcu_cmp_ge0( dVector Y, dVector X, ui size );
ui   __vf OVCUAPI   VDcu_cmp_gt0( dVector Y, dVector X, ui size );

ui   __vf OVCUAPI   VDcu_cnt_eq0( dVector X, ui size );
ui   __vf OVCUAPI   VDcu_cnt_ne0( dVector X, ui size );
ui   __vf OVCUAPI   VDcu_cnt_le0( dVector X, ui size );
ui   __vf OVCUAPI   VDcu_cnt_lt0( dVector X, ui size );
ui   __vf OVCUAPI   VDcu_cnt_ge0( dVector X, ui size );
ui   __vf OVCUAPI   VDcu_cnt_gt0( dVector X, ui size );

/*
ui   __vf OVCUAPI   VDcu_cmp_eq0ind( uiVector Ind, dVector X, ui size );
ui   __vf OVCUAPI   VDcu_cmp_ne0ind( uiVector Ind, dVector X, ui size );
ui   __vf OVCUAPI   VDcu_cmp_le0ind( uiVector Ind, dVector X, ui size );
ui   __vf OVCUAPI   VDcu_cmp_lt0ind( uiVector Ind, dVector X, ui size );
ui   __vf OVCUAPI   VDcu_cmp_ge0ind( uiVector Ind, dVector X, ui size );
ui   __vf OVCUAPI   VDcu_cmp_gt0ind( uiVector Ind, dVector X, ui size );
*/

void __vf OVCUAPI   VDcu_cmpC(    dVector Y, dVector X, ui size, double C );
ui   __vf OVCUAPI   VDcu_cmp_eqC( dVector Y, dVector X, ui size, double C );
ui   __vf OVCUAPI   VDcu_cmp_neC( dVector Y, dVector X, ui size, double C );
ui   __vf OVCUAPI   VDcu_cmp_leC( dVector Y, dVector X, ui size, double C );
ui   __vf OVCUAPI   VDcu_cmp_ltC( dVector Y, dVector X, ui size, double C );
ui   __vf OVCUAPI   VDcu_cmp_geC( dVector Y, dVector X, ui size, double C );
ui   __vf OVCUAPI   VDcu_cmp_gtC( dVector Y, dVector X, ui size, double C );

ui   __vf OVCUAPI   VDcu_cnt_eqC( dVector X, ui size, double C );
ui   __vf OVCUAPI   VDcu_cnt_neC( dVector X, ui size, double C );
ui   __vf OVCUAPI   VDcu_cnt_leC( dVector X, ui size, double C );
ui   __vf OVCUAPI   VDcu_cnt_ltC( dVector X, ui size, double C );
ui   __vf OVCUAPI   VDcu_cnt_geC( dVector X, ui size, double C );
ui   __vf OVCUAPI   VDcu_cnt_gtC( dVector X, ui size, double C );

/*
ui   __vf OVCUAPI   VDcu_cmp_eqCind( uiVector Ind, dVector X, ui size, double C );
ui   __vf OVCUAPI   VDcu_cmp_neCind( uiVector Ind, dVector X, ui size, double C );
ui   __vf OVCUAPI   VDcu_cmp_leCind( uiVector Ind, dVector X, ui size, double C );
ui   __vf OVCUAPI   VDcu_cmp_ltCind( uiVector Ind, dVector X, ui size, double C );
ui   __vf OVCUAPI   VDcu_cmp_geCind( uiVector Ind, dVector X, ui size, double C );
ui   __vf OVCUAPI   VDcu_cmp_gtCind( uiVector Ind, dVector X, ui size, double C );
*/
void __vf OVCUAPI   VDcu_cmpV(    dVector Z, dVector X, dVector Y, ui size );
ui   __vf OVCUAPI   VDcu_cmp_eqV( dVector Z, dVector X, dVector Y, ui size );
ui   __vf OVCUAPI   VDcu_cmp_neV( dVector Z, dVector X, dVector Y, ui size );
ui   __vf OVCUAPI   VDcu_cmp_leV( dVector Z, dVector X, dVector Y, ui size );
ui   __vf OVCUAPI   VDcu_cmp_ltV( dVector Z, dVector X, dVector Y, ui size );
ui   __vf OVCUAPI   VDcu_cmp_geV( dVector Z, dVector X, dVector Y, ui size );
ui   __vf OVCUAPI   VDcu_cmp_gtV( dVector Z, dVector X, dVector Y, ui size );

ui   __vf OVCUAPI   VDcu_cnt_eqV( dVector X, dVector Y, ui size );
ui   __vf OVCUAPI   VDcu_cnt_neV( dVector X, dVector Y, ui size );
ui   __vf OVCUAPI   VDcu_cnt_leV( dVector X, dVector Y, ui size );
ui   __vf OVCUAPI   VDcu_cnt_ltV( dVector X, dVector Y, ui size );
ui   __vf OVCUAPI   VDcu_cnt_geV( dVector X, dVector Y, ui size );
ui   __vf OVCUAPI   VDcu_cnt_gtV( dVector X, dVector Y, ui size );

/*
ui   __vf OVCUAPI   VDcu_cmp_eqVind( uiVector Ind, dVector X, dVector Y, ui size );
ui   __vf OVCUAPI   VDcu_cmp_neVind( uiVector Ind, dVector X, dVector Y, ui size );
ui   __vf OVCUAPI   VDcu_cmp_leVind( uiVector Ind, dVector X, dVector Y, ui size );
ui   __vf OVCUAPI   VDcu_cmp_ltVind( uiVector Ind, dVector X, dVector Y, ui size );
ui   __vf OVCUAPI   VDcu_cmp_geVind( uiVector Ind, dVector X, dVector Y, ui size );
ui   __vf OVCUAPI   VDcu_cmp_gtVind( uiVector Ind, dVector X, dVector Y, ui size );
*/
ui   __vf OVCUAPI   VDcu_cmp_inclrange0C( dVector Y, dVector X, ui size, double C );
ui   __vf OVCUAPI   VDcu_cmp_exclrange0C( dVector Y, dVector X, ui size, double C );
ui   __vf OVCUAPI   VDcu_cmp_inclrangeCC( dVector Y, dVector X, ui size, double CLo, double CHi );
ui   __vf OVCUAPI   VDcu_cmp_exclrangeCC( dVector Y, dVector X, ui size, double CLo, double CHi );

ui   __vf OVCUAPI   VDcu_cnt_inclrange0C( dVector X, ui size, double C );
ui   __vf OVCUAPI   VDcu_cnt_exclrange0C( dVector X, ui size, double C );
ui   __vf OVCUAPI   VDcu_cnt_inclrangeCC( dVector X, ui size, double CLo, double CHi );
ui   __vf OVCUAPI   VDcu_cnt_exclrangeCC( dVector X, ui size, double CLo, double CHi );

/*
ui   __vf OVCUAPI   VDcu_cmp_inclrange0Cind( uiVector Ind, dVector X, ui size, double C );
ui   __vf OVCUAPI   VDcu_cmp_exclrange0Cind( uiVector Ind, dVector X, ui size, double C );
ui   __vf OVCUAPI   VDcu_cmp_inclrangeCCind( uiVector Ind, dVector X, ui size, double CLo, double CHi );
ui   __vf OVCUAPI   VDcu_cmp_exclrangeCCind( uiVector Ind, dVector X, ui size, double CLo, double CHi );
*/

/********************  Standard Arithmetics   ***************************/

void  __vf OVCUAPI   VDcu_equC( dVector X, ui size, double C );
void  __vf OVCUAPI   VDcu_equV( dVector Y, dVector X, ui size );
void  __vf OVCUAPI   VDxcu_equV( dVector Y, dVector X, ui size, double A, double B );

void  __vf OVCUAPI   VDcu_addC(  dVector Y, dVector X, ui size, double C );
void  __vf OVCUAPI   VDcu_subC(  dVector Y, dVector X, ui size, double C );
void  __vf OVCUAPI   VDcu_subrC( dVector Y, dVector X, ui size, double C );
void  __vf OVCUAPI   VDcu_mulC(  dVector Y, dVector X, ui size, double C );
void  __vf OVCUAPI   VDcu_divC(  dVector Y, dVector X, ui size, double C );
void  __vf OVCUAPI   VDcu_divrC( dVector Y, dVector X, ui size, double C );
void  __vf OVCUAPI   VDxcu_divrC( dVector Y, dVector X, ui size, double A, double B, double C );

void  __vf OVCUAPI   VDcu_addV(  dVector Z, dVector X, dVector Y, ui size );
void  __vf OVCUAPI   VDcu_subV(  dVector Z, dVector X, dVector Y, ui size );
void  __vf OVCUAPI   VDcu_subrV( dVector Z, dVector X, dVector Y, ui size );
void  __vf OVCUAPI   VDcu_mulV(  dVector Z, dVector X, dVector Y, ui size );
void  __vf OVCUAPI   VDcu_divV(  dVector Z, dVector X, dVector Y, ui size );
void  __vf OVCUAPI   VDcu_divrV(  dVector Z, dVector X, dVector Y, ui size );
void  __vf OVCUAPI   VDcu_add2V(  dVector Z, dVector X, dVector Y1, dVector Y2, ui size );
void  __vf OVCUAPI   VDcu_sub2V(  dVector Z, dVector X, dVector Y1, dVector Y2, ui size );

void  __vf OVCUAPI   VDcu_CaddV( dVector Z, dVector X, dVector Y, ui siz, double C );
                              /* Z = X + C*Y  */

void  __vf OVCUAPI   VDxcu_addV(  dVector Z, dVector X, dVector Y, ui size, double A, double B );
                              /* Z = (A*X+B) + Y  */
void  __vf OVCUAPI   VDxcu_subV(  dVector Z, dVector X, dVector Y, ui size, double A, double B );
void  __vf OVCUAPI   VDxcu_subrV( dVector Z, dVector X, dVector Y, ui size, double A, double B );
void  __vf OVCUAPI   VDxcu_mulV(  dVector Z, dVector X, dVector Y, ui size, double A, double B );
void  __vf OVCUAPI   VDxcu_divV(  dVector Z, dVector X, dVector Y, ui size, double A, double B );
void  __vf OVCUAPI   VDxcu_divrV( dVector Z, dVector X, dVector Y, ui size, double A, double B );

void  __vf OVCUAPI   VDscu_addV(  dVector Z, dVector X, dVector Y, ui size, double C ); /* Z=C*(X+Y) */
void  __vf OVCUAPI   VDscu_subV(  dVector Z, dVector X, dVector Y, ui size, double C );
void  __vf OVCUAPI   VDscu_subrV( dVector Z, dVector X, dVector Y, ui size, double C );
void  __vf OVCUAPI   VDscu_mulV(  dVector Z, dVector X, dVector Y, ui size, double C );
void  __vf OVCUAPI   VDscu_divV(  dVector Z, dVector X, dVector Y, ui size, double C );
void  __vf OVCUAPI   VDscu_divrV( dVector Z, dVector X, dVector Y, ui size, double C );

void  __vf OVCUAPI   VDcu_maxC(   dVector Y, dVector X, ui size, double C );
void  __vf OVCUAPI   VDcu_minC(   dVector Y, dVector X, ui size, double C );
void  __vf OVCUAPI   VDcu_limit(  dVector Y, dVector X, ui size, double Min, double Max );
void  __vf OVCUAPI   VDcu_flush0( dVector Y, dVector X, ui size, double AbsMin );
void  __vf OVCUAPI   VDcu_flushInv( dVector Y, dVector X, ui size, double AbsMin );
void  __vf OVCUAPI   VDcu_replaceNAN( dVector Y, dVector X, ui size, double C );
void  __vf OVCUAPI   VDcu_maxV(   dVector Z, dVector X, dVector Y, ui size );
void  __vf OVCUAPI   VDcu_minV(   dVector Z, dVector X, dVector Y, ui size );
void  __vf OVCUAPI   VDcu_modC(   dVector Y, dVector X, ui size, double C );
void  __vf OVCUAPI   VDcu_modV(   dVector Z, dVector X, dVector Y, ui size );
void  __vf OVCUAPI   VDxcu_modV(  dVector Z, dVector X, dVector Y, ui size, double A, double B );
#define     VDcu_fmodC    VDcu_modC
#define     VDcu_fmodV    VDcu_modV
#define     VDxcu_fmodV   VDxcu_modV

void __vf OVCUAPI   VDcu_redC(  dVector Y, dVector X, ui size, double C );
void __vf OVCUAPI   VDcu_redV(  dVector Z, dVector X, dVector Y, ui size );
void __vf OVCUAPI   VDxcu_redV( dVector Z, dVector X, dVector Y, ui size, double A, double B );
void __vf OVCUAPI   VDcu_visC(  dVector Y, dVector X, ui size, double C );
void __vf OVCUAPI   VDcu_visV(  dVector Z, dVector X, dVector Y, ui size );
void __vf OVCUAPI   VDxcu_visV( dVector Z, dVector X, dVector Y, ui size, double A, double B );
void __vf OVCUAPI   VDcu_hypC(  dVector Y, dVector X, ui size, double C );
void __vf OVCUAPI   VDcu_hypV(  dVector Z, dVector X, dVector Y, ui size );
void __vf OVCUAPI   VDxcu_hypV( dVector Z, dVector X, dVector Y, ui size, double A, double B );

void __vf OVCUAPI  VDcu_lincomb( dVector Z, dVector X, dVector Y, ui size, double CX, double CY );
		/* Z=CX*X+CY*Y */

void __vf OVCUAPI  VDcu_rotateCoordinates( dVector Xnew, dVector Ynew, dVector Xold, dVector Yold,
                      ui size, double costheta, double sintheta );
#define VDcu_sgn    VDcu_cmp0

/******************* Mixed-type arithmetic Functions **********************/

void  __vf OVCUAPI   VDcu_addVBI(  dVector Z, dVector X, biVector Y, ui size );
void  __vf OVCUAPI   VDcu_subVBI(  dVector Z, dVector X, biVector Y, ui size );
void  __vf OVCUAPI   VDcu_subrVBI( dVector Z, dVector X, biVector Y, ui size );
void  __vf OVCUAPI   VDcu_mulVBI(  dVector Z, dVector X, biVector Y, ui size );
void  __vf OVCUAPI   VDcu_divVBI(  dVector Z, dVector X, biVector Y, ui size );
void  __vf OVCUAPI   VDcu_divrVBI( dVector Z, dVector X, biVector Y, ui size );
void  __vf OVCUAPI   VDcu_addVSI(  dVector Z, dVector X, siVector Y, ui size );
void  __vf OVCUAPI   VDcu_subVSI(  dVector Z, dVector X, siVector Y, ui size );
void  __vf OVCUAPI   VDcu_subrVSI( dVector Z, dVector X, siVector Y, ui size );
void  __vf OVCUAPI   VDcu_mulVSI(  dVector Z, dVector X, siVector Y, ui size );
void  __vf OVCUAPI   VDcu_divVSI(  dVector Z, dVector X, siVector Y, ui size );
void  __vf OVCUAPI   VDcu_divrVSI( dVector Z, dVector X, siVector Y, ui size );
void  __vf OVCUAPI   VDcu_addVI(  dVector Z, dVector X, iVector Y, ui size );
void  __vf OVCUAPI   VDcu_subVI(  dVector Z, dVector X, iVector Y, ui size );
void  __vf OVCUAPI   VDcu_subrVI( dVector Z, dVector X, iVector Y, ui size );
void  __vf OVCUAPI   VDcu_mulVI(  dVector Z, dVector X, iVector Y, ui size );
void  __vf OVCUAPI   VDcu_divVI(  dVector Z, dVector X, iVector Y, ui size );
void  __vf OVCUAPI   VDcu_divrVI( dVector Z, dVector X, iVector Y, ui size );
void  __vf OVCUAPI   VDcu_addVLI(  dVector Z, dVector X, liVector Y, ui size );
void  __vf OVCUAPI   VDcu_subVLI(  dVector Z, dVector X, liVector Y, ui size );
void  __vf OVCUAPI   VDcu_subrVLI( dVector Z, dVector X, liVector Y, ui size );
void  __vf OVCUAPI   VDcu_mulVLI(  dVector Z, dVector X, liVector Y, ui size );
void  __vf OVCUAPI   VDcu_divVLI(  dVector Z, dVector X, liVector Y, ui size );
void  __vf OVCUAPI   VDcu_divrVLI( dVector Z, dVector X, liVector Y, ui size );
void  __vf OVCUAPI   VDcu_addVQI(  dVector Z, dVector X, qiVector Y, ui size );
void  __vf OVCUAPI   VDcu_subVQI(  dVector Z, dVector X, qiVector Y, ui size );
void  __vf OVCUAPI   VDcu_subrVQI( dVector Z, dVector X, qiVector Y, ui size );
void  __vf OVCUAPI   VDcu_mulVQI(  dVector Z, dVector X, qiVector Y, ui size );
void  __vf OVCUAPI   VDcu_divVQI(  dVector Z, dVector X, qiVector Y, ui size );
void  __vf OVCUAPI   VDcu_divrVQI( dVector Z, dVector X, qiVector Y, ui size );
void  __vf OVCUAPI   VDcu_addVUB(  dVector Z, dVector X, ubVector Y, ui size );
void  __vf OVCUAPI   VDcu_subVUB(  dVector Z, dVector X, ubVector Y, ui size );
void  __vf OVCUAPI   VDcu_subrVUB( dVector Z, dVector X, ubVector Y, ui size );
void  __vf OVCUAPI   VDcu_mulVUB(  dVector Z, dVector X, ubVector Y, ui size );
void  __vf OVCUAPI   VDcu_divVUB(  dVector Z, dVector X, ubVector Y, ui size );
void  __vf OVCUAPI   VDcu_divrVUB( dVector Z, dVector X, ubVector Y, ui size );
void  __vf OVCUAPI   VDcu_addVUS(  dVector Z, dVector X, usVector Y, ui size );
void  __vf OVCUAPI   VDcu_subVUS(  dVector Z, dVector X, usVector Y, ui size );
void  __vf OVCUAPI   VDcu_subrVUS( dVector Z, dVector X, usVector Y, ui size );
void  __vf OVCUAPI   VDcu_mulVUS(  dVector Z, dVector X, usVector Y, ui size );
void  __vf OVCUAPI   VDcu_divVUS(  dVector Z, dVector X, usVector Y, ui size );
void  __vf OVCUAPI   VDcu_divrVUS( dVector Z, dVector X, usVector Y, ui size );
void  __vf OVCUAPI   VDcu_addVU(   dVector Z, dVector X, uVector Y,  ui size );
void  __vf OVCUAPI   VDcu_subVU(   dVector Z, dVector X, uVector Y,  ui size );
void  __vf OVCUAPI   VDcu_subrVU(  dVector Z, dVector X, uVector Y,  ui size );
void  __vf OVCUAPI   VDcu_mulVU(   dVector Z, dVector X, uVector Y,  ui size );
void  __vf OVCUAPI   VDcu_divVU(   dVector Z, dVector X, uVector Y,  ui size );
void  __vf OVCUAPI   VDcu_divrVU(  dVector Z, dVector X, uVector Y,  ui size );
void  __vf OVCUAPI   VDcu_addVUL(  dVector Z, dVector X, ulVector Y, ui size );
void  __vf OVCUAPI   VDcu_subVUL(  dVector Z, dVector X, ulVector Y, ui size );
void  __vf OVCUAPI   VDcu_subrVUL( dVector Z, dVector X, ulVector Y, ui size );
void  __vf OVCUAPI   VDcu_mulVUL(  dVector Z, dVector X, ulVector Y, ui size );
void  __vf OVCUAPI   VDcu_divVUL(  dVector Z, dVector X, ulVector Y, ui size );
void  __vf OVCUAPI   VDcu_divrVUL( dVector Z, dVector X, ulVector Y, ui size );
#ifdef _WIN64
    void  __vf OVCUAPI   VDcu_addVUQ(  dVector Z, dVector X, uqVector Y, ui size );
    void  __vf OVCUAPI   VDcu_subVUQ(  dVector Z, dVector X, uqVector Y, ui size );
    void  __vf OVCUAPI   VDcu_subrVUQ( dVector Z, dVector X, uqVector Y, ui size );
    void  __vf OVCUAPI   VDcu_mulVUQ(  dVector Z, dVector X, uqVector Y, ui size );
    void  __vf OVCUAPI   VDcu_divVUQ(  dVector Z, dVector X, uqVector Y, ui size );
    void  __vf OVCUAPI   VDcu_divrVUQ( dVector Z, dVector X, uqVector Y, ui size );
    #define VDcu_addVUI  VDcu_addVUQ
    #define VDcu_subVUI  VDcu_subVUQ
    #define VDcu_subrVUI VDcu_subrVUQ
    #define VDcu_mulVUI  VDcu_mulVUQ
    #define VDcu_divVUI  VDcu_divVUQ
    #define VDcu_divrVUI VDcu_divrVUQ
#else
    #define VDcu_addVUI  VDcu_addVU
    #define VDcu_subVUI  VDcu_subVU
    #define VDcu_subrVUI VDcu_subrVU
    #define VDcu_mulVUI  VDcu_mulVU
    #define VDcu_divVUI  VDcu_divVU
    #define VDcu_divrVUI VDcu_divrVU
#endif

/******************** Accumulation (Y += X) ******************************/

void __vf OVCUAPI  VDcu_accV(   dVector Y, dVector  X, ui size );
void __vf OVCUAPI  VDcu_accVF(  dVector Y, fVector  X, ui size );
void __vf OVCUAPI  VDcu_accVBI( dVector Y, biVector X, ui size );
void __vf OVCUAPI  VDcu_accVSI( dVector Y, siVector X, ui size );
void __vf OVCUAPI  VDcu_accVI(  dVector Y, iVector  X, ui size );
void __vf OVCUAPI  VDcu_accVLI( dVector Y, liVector X, ui size );
void __vf OVCUAPI  VDcu_accVQI( dVector Y, qiVector X, ui size );
void __vf OVCUAPI  VDcu_accVUB( dVector Y, ubVector X, ui size );
void __vf OVCUAPI  VDcu_accVUS( dVector Y, usVector X, ui size );
void __vf OVCUAPI  VDcu_accVU(  dVector Y, uVector  X, ui size );
void __vf OVCUAPI  VDcu_accVUL( dVector Y, ulVector X, ui size );
void __vf OVCUAPI  VDcu_acc2V(  dVector Y, dVector  X1, dVector  X2, ui size );
void __vf OVCUAPI  VDcu_acc2VF( dVector Y, fVector  X1, fVector  X2, ui size );
#if defined _WIN64
    void __vf OVCUAPI  VDcu_accVUQ( dVector Y, uqVector X, ui size );
    #define VDcu_accVUI   VDcu_accVUQ
#else
    #define VDcu_accVUI   VDcu_accVU
#endif

/***************** Functions of a sub-set of elements  ********************/

void  __vf OVCUAPI   VDcu_subvector_equC(  dVector Y, ui subsiz, ui samp, double C );
void  __vf OVCUAPI   VDcu_subvector_equV(  dVector Y, ui subsiz, ui samp, dVector X );

void  __vf OVCUAPI   VDcu_subvector_addC(  dVector Y, ui subsiz, ui samp, double C );
void  __vf OVCUAPI   VDcu_subvector_subC(  dVector Y, ui subsiz, ui samp, double C );
void  __vf OVCUAPI   VDcu_subvector_subrC( dVector Y, ui subsiz, ui samp, double C );
void  __vf OVCUAPI   VDcu_subvector_mulC(  dVector Y, ui subsiz, ui samp, double C );
void  __vf OVCUAPI   VDcu_subvector_divC(  dVector Y, ui subsiz, ui samp, double C );
void  __vf OVCUAPI   VDcu_subvector_divrC( dVector Y, ui subsiz, ui samp, double C );

void  __vf OVCUAPI   VDcu_subvector_addV(  dVector Y, ui subsiz, ui samp, dVector X );
void  __vf OVCUAPI   VDcu_subvector_subV(  dVector Y, ui subsiz, ui samp, dVector X );
void  __vf OVCUAPI   VDcu_subvector_subrV( dVector Y, ui subsiz, ui samp, dVector X );
void  __vf OVCUAPI   VDcu_subvector_mulV(  dVector Y, ui subsiz, ui samp, dVector X );
void  __vf OVCUAPI   VDcu_subvector_divV(  dVector Y, ui subsiz, ui samp, dVector X );
void  __vf OVCUAPI   VDcu_subvector_divrV( dVector Y, ui subsiz, ui samp, dVector X );

/*********************  Mathematical Functions ***********************/

int   __vf OVCUAPI   VDcu_abs( dVector Y, dVector X, ui size );
int   __vf OVCUAPI   VDcu_neg( dVector Y, dVector X, ui size );
int   __vf OVCUAPI   VDcu_inv( dVector Y, dVector X, ui size );
int   __vf OVCUAPI   VDxcu_inv( dVector Y, dVector X, ui size, double A, double B );
int   __vf OVCUAPI   VDcu_intfrac( dVector Int, dVector Frac, dVector X, ui size );
#define      VDcu_modf    VDcu_intfrac
int   __vf OVCUAPI   VDcu_mantexp( dVector Mant, iVector Exp, dVector X, ui size );
#define      VDcu_frexp   VDcu_mantexp

int  __vf OVCUAPI   VDcu_hypotC( dVector Y, dVector X, ui size, double C );
int  __vf OVCUAPI   VDcu_hypotV( dVector Z, dVector X, dVector Y, ui size );
int  __vf OVCUAPI   VDxcu_hypotV( dVector Z, dVector X, dVector Y, ui size, double A, double B );

int  __vf OVCUAPI   VDcu_scale2( dVector Y, dVector X, ui size, int expo );
int  __vf OVCUAPI   VDcu_scale10( dVector Y, dVector X, ui size, int expo );
#define      VDcu_ldexp    VDcu_scale2

int  __vf OVCUAPI   VDcu_square( dVector Y, dVector X, ui size );
int  __vf OVCUAPI   VDxcu_square( dVector Y, dVector X, ui size, double A, double B );
int  __vf OVCUAPI   VDcu_cubic( dVector Y, dVector X, ui size );
int  __vf OVCUAPI   VDxcu_cubic( dVector Y, dVector X, ui size, double A, double B );
int  __vf OVCUAPI   VDcu_quartic( dVector Y, dVector X, ui size );
int  __vf OVCUAPI   VDxcu_quartic( dVector Y, dVector X, ui size, double A, double B );
int  __vf OVCUAPI   VDcu_poly( dVector Y, dVector X, ui size, dVector d_Coeff, unsigned deg );
int  __vf OVCUAPI   VDxcu_poly( dVector Y, dVector X, ui size, dVector d_Coeff, unsigned deg, double A, double B );
int  __vf OVCUAPI   VDcu_ipow( dVector Y, dVector X, ui size, int ipow );
int  __vf OVCUAPI   VDxcu_ipow( dVector Y, dVector X, ui size, int ipow, double A, double B, double C );
                           /*  ipow = integer power of x */
       /* unprotected integer powers:  */
int  __vf OVCUAPI   VDucu_square( dVector Y, dVector X, ui size );
int  __vf OVCUAPI   VDuxcu_square( dVector Y, dVector X, ui size, double A, double B );
int  __vf OVCUAPI   VDucu_cubic( dVector Y, dVector X, ui size );
int  __vf OVCUAPI   VDuxcu_cubic( dVector Y, dVector X, ui size, double A, double B );
int  __vf OVCUAPI   VDucu_quartic( dVector Y, dVector X, ui size );
int  __vf OVCUAPI   VDuxcu_quartic( dVector Y, dVector X, ui size, double A, double B );
int  __vf OVCUAPI   VDucu_poly( dVector Y, dVector X, ui size, dVector Coeff, unsigned deg );
int  __vf OVCUAPI   VDuxcu_poly( dVector Y, dVector X, ui size, dVector Coeff, unsigned deg, double A, double B );
int  __vf OVCUAPI   VDucu_ipow( dVector Y, dVector X, ui size, int ipow );
int  __vf OVCUAPI   VDuxcu_ipow( dVector Y, dVector X, ui size, int ipow, double A, double B, double C );

int  __vf OVCUAPI   VDcu_ipow2(  dVector Y, iVector X, ui size );
int  __vf OVCUAPI   VDcu_ipow10( dVector Y, iVector X, ui size );
                          /* ipow2 and ipow10: integer powers of 2 and 10 */

int  __vf OVCUAPI   VDcu_pow(    dVector Y, dVector X, ui size, double expo );
int  __vf OVCUAPI   VDxcu_pow(   dVector Y, dVector X, ui size, double expo, double A, double B, double C );

int  __vf OVCUAPI   VDcu_pow2(   dVector Y, dVector X, ui size );
int  __vf OVCUAPI   VDxcu_pow2(  dVector Y, dVector X, ui size, double A, double B, double C );
int  __vf OVCUAPI   VDcu_pow10(  dVector Y, dVector X, ui size );
int  __vf OVCUAPI   VDxcu_pow10( dVector Y, dVector X, ui size, double A, double B, double C );
            /* pow2 and pow10: basis 2 or 10 raised to power x */

int  __vf OVCUAPI   VDcu_sqrt(  dVector Y, dVector X, ui size );
int  __vf OVCUAPI   VDxcu_sqrt( dVector Y, dVector X, ui size, double A, double B, double C );

int  __vf OVCUAPI   VDcu_log(    dVector Y, dVector X, ui size );
int  __vf OVCUAPI   VDcu_log2(   dVector Y, dVector X, ui size );
int  __vf OVCUAPI   VDcu_log10(  dVector Y, dVector X, ui size );
#define     VDcu_ln      VDcu_log
int  __vf OVCUAPI   VDxcu_log(   dVector Y, dVector X, ui size, double A, double B, double C );
int  __vf OVCUAPI   VDxcu_log2(  dVector Y, dVector X, ui size, double A, double B, double C );
int  __vf OVCUAPI   VDxcu_log10( dVector Y, dVector X, ui size, double A, double B, double C );
#define     VDxcu_ln     VDxcu_log

int  __vf OVCUAPI   VDcu_OD( dVector OD, dVector X, dVector X0, ui size );  /* OD = log10( X0/X ) */
int  __vf OVCUAPI   VDcu_ODwDark( dVector OD, dVector X, dVector XDark,
                        dVector X0, dVector X0Dark, ui size );
void __vf OVCUAPI   VDcu_setODThresh( double minX, double minX0 );

int  __vf OVCUAPI   VDcu_exp(   dVector Y, dVector X, ui size );
int  __vf OVCUAPI   VDxcu_exp(  dVector Y, dVector X, ui size, double A, double B, double C );
int  __vf OVCUAPI   VDcu_expArbBase(  dVector Y, dVector X, ui size, double Base );
int  __vf OVCUAPI   VDxcu_expArbBase( dVector Y, dVector X, ui size, double Base,
                            double A, double B, double C );
int  __vf OVCUAPI   VDcu_expc(  dVector Y, dVector X, ui size );
int  __vf OVCUAPI   VDxcu_expc( dVector Y, dVector X, ui size, double A, double B, double C );
                /* expc(x) = 1 - exp(x)  */
int  __vf OVCUAPI   VDcu_expmx2(  dVector Y, dVector X, ui size );
int  __vf OVCUAPI   VDxcu_expmx2( dVector Y, dVector X, ui size, double A, double B, double C );
                /* expmx2(x) = exp( -x**2 )  */
#define VDcu_exp2   VDcu_pow2
#define VDxcu_exp2  VDxcu_pow2
#define VDcu_exp10   VDcu_pow10
#define VDxcu_exp10  VDxcu_pow10
int  __vf OVCUAPI   VDcu_powexp( dVector Y, dVector X, ui size, double expo );
int  __vf OVCUAPI   VDxcu_powexp( dVector Y, dVector X, ui size, double expo, double A, double B, double C );

int  __vf OVCUAPI   VDcu_erf(     dVector Y, dVector X, ui size );
int  __vf OVCUAPI   VDxcu_erf(    dVector Y, dVector X, ui size, double A, double B, double C );
int  __vf OVCUAPI   VDcu_erfc(    dVector Y, dVector X, ui size );
int  __vf OVCUAPI   VDxcu_erfc(   dVector Y, dVector X, ui size, double A, double B, double C );
int  __vf OVCUAPI   VDcu_Gauss(   dVector Y, dVector X, ui size, double Wid, double Cent, double C );
#define VDcu_gauss VDcu_Gauss
int  __vf OVCUAPI   VDcu_Lorentz( dVector Y, dVector X, ui size, double Wid, double Cent, double C );
#define VDcu_lorentz VDcu_Lorentz

int  __vf OVCUAPI   VDcu_sin(     dVector Y, dVector X, ui size );
int  __vf OVCUAPI   VDxcu_sin(    dVector Y, dVector X, ui size, double A, double B, double C );
int  __vf OVCUAPI   VDcu_cos(     dVector Y, dVector X, ui size );
int  __vf OVCUAPI   VDxcu_cos(    dVector Y, dVector X, ui size, double A, double B, double C );
int  __vf OVCUAPI   VDcu_sincos(  dVector Sin, dVector Cos, dVector X, ui size );
int  __vf OVCUAPI   VDxcu_sincos( dVector Sin, dVector Cos, dVector X, ui size, double A, double B, double C );

int  __vf OVCUAPI   VDcu_tan(     dVector Y, dVector X, ui size );
int  __vf OVCUAPI   VDxcu_tan(    dVector Y, dVector X, ui size, double A, double B, double C );
int  __vf OVCUAPI   VDcu_cot(     dVector Y, dVector X, ui size );
int  __vf OVCUAPI   VDxcu_cot(    dVector Y, dVector X, ui size, double A, double B, double C );

int  __vf OVCUAPI   VDcu_sec(     dVector Y, dVector X, ui size );
int  __vf OVCUAPI   VDxcu_sec(    dVector Y, dVector X, ui size, double A, double B, double C );
int  __vf OVCUAPI   VDcu_cosec(   dVector Y, dVector X, ui size );
int  __vf OVCUAPI   VDxcu_cosec(  dVector Y, dVector X, ui size, double A, double B, double C );

int  __vf OVCUAPI   VDcu_sin2(    dVector Y, dVector X, ui size );
int  __vf OVCUAPI   VDxcu_sin2(   dVector Y, dVector X, ui size, double A, double B, double C );
int  __vf OVCUAPI   VDcu_cos2(    dVector Y, dVector X, ui size );
int  __vf OVCUAPI   VDxcu_cos2(   dVector Y, dVector X, ui size, double A, double B, double C );
int  __vf OVCUAPI   VDcu_sincos2( dVector Sin, dVector Cos, dVector X, ui size );
int  __vf OVCUAPI   VDxcu_sincos2( dVector Sin, dVector Cos, dVector X, ui size, double A, double B, double C );

int  __vf OVCUAPI   VDcu_tan2(     dVector Y, dVector X, ui size );
int  __vf OVCUAPI   VDxcu_tan2(    dVector Y, dVector X, ui size, double A, double B, double C );
int  __vf OVCUAPI   VDcu_cot2(     dVector Y, dVector X, ui size );
int  __vf OVCUAPI   VDxcu_cot2(    dVector Y, dVector X, ui size, double A, double B, double C );
int  __vf OVCUAPI   VDcu_sec2(     dVector Y, dVector X, ui size );
int  __vf OVCUAPI   VDxcu_sec2(    dVector Y, dVector X, ui size, double A, double B, double C );
int  __vf OVCUAPI   VDcu_cosec2(   dVector Y, dVector X, ui size );
int  __vf OVCUAPI   VDxcu_cosec2(  dVector Y, dVector X, ui size, double A, double B, double C );

 /*  reduced-range sine and cosine for -2Pi <= x <= +2Pi */
/*
int  __vf OVCUAPI   VDrcu_sin(     dVector Y, dVector X, ui size );
int  __vf OVCUAPI   cudaVDrx_sin(    dVector Y, dVector X, ui size, double A, double B, double C );
int  __vf OVCUAPI   VDrcu_cos(     dVector Y, dVector X, ui size );
int  __vf OVCUAPI   cudaVDrx_cos(    dVector Y, dVector X, ui size, double A, double B, double C );
int  __vf OVCUAPI   VDrcu_sincos(  dVector YSin, dVector YCos, dVector X, ui size );
int  __vf OVCUAPI   cudaVDrx_sincos( dVector YSin, dVector YCos, dVector X, ui size, double A, double B, double C );
int  __vf OVCUAPI   VDrcu_sin2(     dVector Y, dVector X, ui size );
int  __vf OVCUAPI   cudaVDrx_sin2(    dVector Y, dVector X, ui size, double A, double B, double C );
int  __vf OVCUAPI   VDrcu_cos2(     dVector Y, dVector X, ui size );
int  __vf OVCUAPI   cudaVDrx_cos2(    dVector Y, dVector X, ui size, double A, double B, double C );
int  __vf OVCUAPI   VDrcu_sincos2(  dVector YSin, dVector YCos, dVector X, ui size );
int  __vf OVCUAPI   cudaVDrx_sincos2( dVector YSin, dVector YCos, dVector X, ui size, double A, double B, double C );
*/

/* trigonometric functions of rational multiples of Pi: x = p/q * Pi */
int  __vf OVCUAPI   VDcu_sinrpi(   dVector Y, iVector P, ui size, int q );
int  __vf OVCUAPI   VDcu_cosrpi(   dVector Y, iVector P, ui size, int q );
int  __vf OVCUAPI   VDcu_sincosrpi( dVector YSin, dVector YCos, iVector P, ui size, int q );
int  __vf OVCUAPI   VDcu_tanrpi(   dVector Y, iVector P, ui size, int q );
int  __vf OVCUAPI   VDcu_cotrpi(   dVector Y, iVector P, ui size, int q );
int  __vf OVCUAPI   VDcu_secrpi(   dVector Y, iVector P, ui size, int q );
int  __vf OVCUAPI   VDcu_cosecrpi( dVector Y, iVector P, ui size, int q );

int  __vf OVCUAPI   VDcu_sinrpi2(  dVector Y, iVector P, ui size, int q );
int  __vf OVCUAPI   VDcu_cosrpi2(  dVector Y, iVector P, ui size, int q );
int  __vf OVCUAPI   VDcu_sincosrpi2( dVector YSin, dVector YCos, iVector P, ui size, int q );
int  __vf OVCUAPI   VDcu_tanrpi2(  dVector Y, iVector P, ui size, int q );
int  __vf OVCUAPI   VDcu_cotrpi2(  dVector Y, iVector P, ui size, int q );
int  __vf OVCUAPI   VDcu_secrpi2(  dVector Y, iVector P, ui size, int q );
int  __vf OVCUAPI   VDcu_cosecrpi2( dVector Y, iVector P, ui size, int q );

int  __vf OVCUAPI   VDcu_sinrpi3(  dVector Y, iVector P, ui size, int q );
int  __vf OVCUAPI   VDcu_cosrpi3(  dVector Y, iVector P, ui size, int q );
int  __vf OVCUAPI   VDcu_sincosrpi3( dVector YSin, dVector YCos, iVector P, ui size, int q );
int  __vf OVCUAPI   VDcu_tanrpi3(  dVector Y, iVector P, ui size, int q );
int  __vf OVCUAPI   VDcu_cotrpi3(  dVector Y, iVector P, ui size, int q );
int  __vf OVCUAPI   VDcu_secrpi3(  dVector Y, iVector P, ui size, int q );
int  __vf OVCUAPI   VDcu_cosecrpi3( dVector Y, iVector P, ui size, int q );


int  __vf OVCUAPI   VDcu_sinc(     dVector Y, dVector X, ui size );
int  __vf OVCUAPI   VDxcu_sinc(    dVector Y, dVector X, ui size, double A, double B, double C );
int  __vf OVCUAPI   VDcu_Kepler(   dVector Y, dVector X, ui size, double T, double e );
int  __vf OVCUAPI   VDxcu_Kepler(  dVector Y, dVector X, ui size, double T, double e, double A, double B );
#define VDcu_kepler  VDcu_Kepler
#define VDxcu_kepler VDxcu_Kepler

int  __vf OVCUAPI   VDcu_asin(    dVector Y, dVector X, ui size );
int  __vf OVCUAPI   VDxcu_asin(   dVector Y, dVector X, ui size, double A, double B, double C );
int  __vf OVCUAPI   VDcu_acos(    dVector Y, dVector X, ui size );
int  __vf OVCUAPI   VDxcu_acos(   dVector Y, dVector X, ui size, double A, double B, double C );
int  __vf OVCUAPI   VDcu_atan(    dVector Y, dVector X, ui size );
int  __vf OVCUAPI   VDxcu_atan(   dVector Y, dVector X, ui size, double A, double B, double C );
int  __vf OVCUAPI   VDcu_atan2(   dVector Z, dVector X, dVector Y, ui size );
int  __vf OVCUAPI   VDxcu_atan2(  dVector Z, dVector X, dVector Y, ui size, double A, double B, double C );

int  __vf OVCUAPI   VDcu_sinh(    dVector Y, dVector X, ui size );
int  __vf OVCUAPI   VDxcu_sinh(   dVector Y, dVector X, ui size, double A, double B, double C );
int  __vf OVCUAPI   VDcu_cosh(    dVector Y, dVector X, ui size );
int  __vf OVCUAPI   VDxcu_cosh(   dVector Y, dVector X, ui size, double A, double B, double C );
int  __vf OVCUAPI   VDcu_tanh(    dVector Y, dVector X, ui size );
int  __vf OVCUAPI   VDxcu_tanh(   dVector Y, dVector X, ui size, double A, double B, double C );
int  __vf OVCUAPI   VDcu_coth(    dVector Y, dVector X, ui size );
int  __vf OVCUAPI   VDxcu_coth(   dVector Y, dVector X, ui size, double A, double B, double C );
int  __vf OVCUAPI   VDcu_sech(    dVector Y, dVector X, ui size );
int  __vf OVCUAPI   VDxcu_sech(   dVector Y, dVector X, ui size, double A, double B, double C );
int  __vf OVCUAPI   VDcu_cosech(  dVector Y, dVector X, ui size );
int  __vf OVCUAPI   VDxcu_cosech( dVector Y, dVector X, ui size, double A, double B, double C );
int  __vf OVCUAPI   VDcu_sech2(   dVector Y, dVector X, ui size );
int  __vf OVCUAPI   VDxcu_sech2(  dVector Y, dVector X, ui size, double A, double B, double C );
int  __vf OVCUAPI   VDcu_Langevin( dVector Y, dVector X, ui size ); /* coth(x)-1/x */
int  __vf OVCUAPI   VDxcu_Langevin(dVector Y, dVector X, ui size, double A, double B, double C );
#define VDcu_langevin  VDcu_Langevin
#define VDxcu_langevin VDxcu_Langevin

#ifdef __cplusplus
}  // end of extern "C"
#endif


#endif /* __cudaVDMATH_H */
