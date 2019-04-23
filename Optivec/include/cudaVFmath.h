/*  cudaVFmath.h

  vector management functions:
  math functions performed on each individual element of an
  array or vector of the data type "float"

  Copyright (c) 1996-2017 by OptiCode - Dr. Martin Sander Software Dev.
  All Rights Reserved.
*/

#ifndef __CUDAVFMATH_H
#define __CUDAVFMATH_H

#ifndef __CUDAVFSTD_H 
#include <cudaVFstd.h>
#endif

/******************  cudaVF_ functions: **********************************
	 act on vectors in CUDA device memory; 
	 scalar parameters and return values on host
******************  cusdVF_ functions: **********************************
	 also act on vectors in CUDA device memory; 
	 scalar parameters and return values by address on device memory
************************************************************************/

#ifdef __cplusplus
extern "C" {
#endif

/**************************  Rounding **********************************/

overror_t  __vcuf OVCUAPI   cudaVF_round(  fVector  Y, fVector X, ui size );
overror_t  __vcuf OVCUAPI   cudaVF_roundtoBI( biVector Y, fVector X, ui size );
overror_t  __vcuf OVCUAPI   cudaVF_roundtoSI( siVector Y, fVector X, ui size );
overror_t  __vcuf OVCUAPI   cudaVF_roundtoI(  iVector  Y, fVector X, ui size );
overror_t  __vcuf OVCUAPI   cudaVF_roundtoLI( liVector Y, fVector X, ui size );
overror_t  __vcuf OVCUAPI   cudaVF_roundtoQI( qiVector Y, fVector X, ui size );
overror_t  __vcuf OVCUAPI   cudaVF_roundtoUB( ubVector Y, fVector X, ui size );
overror_t  __vcuf OVCUAPI   cudaVF_roundtoUS( usVector Y, fVector X, ui size );
overror_t  __vcuf OVCUAPI   cudaVF_roundtoU(  uVector  Y, fVector X, ui size );
overror_t  __vcuf OVCUAPI   cudaVF_roundtoUL( ulVector Y, fVector X, ui size );
#ifdef _WIN64
    overror_t  __vcuf OVCUAPI   cudaVF_roundtoUQ( uqVector Y, fVector X, ui size );
#endif

overror_t  __vcuf OVCUAPI   cudaVF_floor(  fVector  Y, fVector X, ui size );
overror_t  __vcuf OVCUAPI   cudaVF_floortoBI( biVector Y, fVector X, ui size );
overror_t  __vcuf OVCUAPI   cudaVF_floortoSI( siVector Y, fVector X, ui size );
overror_t  __vcuf OVCUAPI   cudaVF_floortoI(  iVector  Y, fVector X, ui size );
overror_t  __vcuf OVCUAPI   cudaVF_floortoLI( liVector Y, fVector X, ui size );
overror_t  __vcuf OVCUAPI   cudaVF_floortoQI( qiVector Y, fVector X, ui size );
overror_t  __vcuf OVCUAPI   cudaVF_floortoUB( ubVector Y, fVector X, ui size );
overror_t  __vcuf OVCUAPI   cudaVF_floortoUS( usVector Y, fVector X, ui size );
overror_t  __vcuf OVCUAPI   cudaVF_floortoU(  uVector  Y, fVector X, ui size );
overror_t  __vcuf OVCUAPI   cudaVF_floortoUL( ulVector Y, fVector X, ui size );
#ifdef _WIN64
    overror_t  __vcuf OVCUAPI   cudaVF_floortoUQ( uqVector Y, fVector X, ui size );
#endif

overror_t  __vcuf OVCUAPI   cudaVF_ceil(  fVector  Y, fVector X, ui size );
overror_t  __vcuf OVCUAPI   cudaVF_ceiltoBI( biVector Y, fVector X, ui size );
overror_t  __vcuf OVCUAPI   cudaVF_ceiltoSI( siVector Y, fVector X, ui size );
overror_t  __vcuf OVCUAPI   cudaVF_ceiltoI(  iVector  Y, fVector X, ui size );
overror_t  __vcuf OVCUAPI   cudaVF_ceiltoLI( liVector Y, fVector X, ui size );
overror_t  __vcuf OVCUAPI   cudaVF_ceiltoQI( qiVector Y, fVector X, ui size );
overror_t  __vcuf OVCUAPI   cudaVF_ceiltoUB( ubVector Y, fVector X, ui size );
overror_t  __vcuf OVCUAPI   cudaVF_ceiltoUS( usVector Y, fVector X, ui size );
overror_t  __vcuf OVCUAPI   cudaVF_ceiltoU(  uVector  Y, fVector X, ui size );
overror_t  __vcuf OVCUAPI   cudaVF_ceiltoUL( ulVector Y, fVector X, ui size );
#ifdef _WIN64
    overror_t  __vcuf OVCUAPI   cudaVF_ceiltoUQ( uqVector Y, fVector X, ui size );
#endif

overror_t  __vcuf OVCUAPI   cudaVF_chop(  fVector  Y, fVector X, ui size );
overror_t  __vcuf OVCUAPI   cudaVF_choptoBI( biVector Y, fVector X, ui size );
overror_t  __vcuf OVCUAPI   cudaVF_choptoSI( siVector Y, fVector X, ui size );
overror_t  __vcuf OVCUAPI   cudaVF_choptoI(  iVector  Y, fVector X, ui size );
overror_t  __vcuf OVCUAPI   cudaVF_choptoLI( liVector Y, fVector X, ui size );
overror_t  __vcuf OVCUAPI   cudaVF_choptoQI( qiVector Y, fVector X, ui size );
overror_t  __vcuf OVCUAPI   cudaVF_choptoUB( ubVector Y, fVector X, ui size );
overror_t  __vcuf OVCUAPI   cudaVF_choptoUS( usVector Y, fVector X, ui size );
overror_t  __vcuf OVCUAPI   cudaVF_choptoU(  uVector  Y, fVector X, ui size );
overror_t  __vcuf OVCUAPI   cudaVF_choptoUL( ulVector Y, fVector X, ui size );
#ifdef _WIN64
    overror_t  __vcuf OVCUAPI   cudaVF_choptoUQ( uqVector Y, fVector X, ui size );
#endif

#define cudaVF_trunc      cudaVF_chop
#define cudaVF_trunctoBI  cudaVF_choptoBI
#define cudaVF_trunctoSI  cudaVF_choptoSI
#define cudaVF_trunctoI   cudaVF_choptoI
#define cudaVF_trunctoLI  cudaVF_choptoLI
#define cudaVF_trunctoQI  cudaVF_choptoQI
#define cudaVF_trunctoUB  cudaVF_choptoUB
#define cudaVF_trunctoUS  cudaVF_choptoUS
#define cudaVF_trunctoU   cudaVF_choptoU
#define cudaVF_trunctoUL  cudaVF_choptoUL
#define cudaVF_trunctoUQ  cudaVF_choptoUQ

#if defined _WIN64
      #define   cudaVF_roundtoUI    cudaVF_roundtoUQ
      #define   cudaVF_floortoUI    cudaVF_floortoUQ
      #define   cudaVF_ceiltoUI     cudaVF_ceiltoUQ
      #define   cudaVF_choptoUI     cudaVF_choptoUQ
      #define   cudaVF_trunctoUI    cudaVF_trunctoUQ
#else
      #define   cudaVF_roundtoUI    cudaVF_roundtoU
      #define   cudaVF_floortoUI    cudaVF_floortoU
      #define   cudaVF_ceiltoUI     cudaVF_ceiltoU
      #define   cudaVF_choptoUI     cudaVF_choptoU
      #define   cudaVF_trunctoUI    cudaVF_trunctoU
#endif

/********************  Comparisons ********************************/

overror_t  __vcuf OVCUAPI   cudaVF_cmp0(    fVector Y, fVector X, ui size );
overror_t  __vcuf OVCUAPI   cudaVF_cmp_eq0( ui *h_nTrue, fVector Y, fVector X, ui size );
overror_t  __vcuf OVCUAPI   cudaVF_cmp_ne0( ui *h_nTrue, fVector Y, fVector X, ui size );
overror_t  __vcuf OVCUAPI   cudaVF_cmp_le0( ui *h_nTrue, fVector Y, fVector X, ui size );
overror_t  __vcuf OVCUAPI   cudaVF_cmp_lt0( ui *h_nTrue, fVector Y, fVector X, ui size );
overror_t  __vcuf OVCUAPI   cudaVF_cmp_ge0( ui *h_nTrue, fVector Y, fVector X, ui size );
overror_t  __vcuf OVCUAPI   cudaVF_cmp_gt0( ui *h_nTrue, fVector Y, fVector X, ui size );

overror_t  __vcuf OVCUAPI   cudaVF_cmpC(    fVector Y, fVector X, ui size, float C );
overror_t  __vcuf OVCUAPI   cudaVF_cmp_eqC( ui *h_nTrue, fVector Y, fVector X, ui size, float C );
overror_t  __vcuf OVCUAPI   cudaVF_cmp_neC( ui *h_nTrue, fVector Y, fVector X, ui size, float C );
overror_t  __vcuf OVCUAPI   cudaVF_cmp_leC( ui *h_nTrue, fVector Y, fVector X, ui size, float C );
overror_t  __vcuf OVCUAPI   cudaVF_cmp_ltC( ui *h_nTrue, fVector Y, fVector X, ui size, float C );
overror_t  __vcuf OVCUAPI   cudaVF_cmp_geC( ui *h_nTrue, fVector Y, fVector X, ui size, float C );
overror_t  __vcuf OVCUAPI   cudaVF_cmp_gtC( ui *h_nTrue, fVector Y, fVector X, ui size, float C );
overror_t  __vcuf OVCUAPI   cusdVF_cmpC(    fVector Y, fVector X, ui size, float *d_C );
overror_t  __vcuf OVCUAPI   cusdVF_cmp_eqC( ui *h_nTrue, fVector Y, fVector X, ui size, float *d_C );
overror_t  __vcuf OVCUAPI   cusdVF_cmp_neC( ui *h_nTrue, fVector Y, fVector X, ui size, float *d_C );
overror_t  __vcuf OVCUAPI   cusdVF_cmp_leC( ui *h_nTrue, fVector Y, fVector X, ui size, float *d_C );
overror_t  __vcuf OVCUAPI   cusdVF_cmp_ltC( ui *h_nTrue, fVector Y, fVector X, ui size, float *d_C );
overror_t  __vcuf OVCUAPI   cusdVF_cmp_geC( ui *h_nTrue, fVector Y, fVector X, ui size, float *d_C );
overror_t  __vcuf OVCUAPI   cusdVF_cmp_gtC( ui *h_nTrue, fVector Y, fVector X, ui size, float *d_C );

overror_t  __vcuf OVCUAPI   cudaVF_cmpV(    fVector Z, fVector X, fVector Y, ui size );
overror_t  __vcuf OVCUAPI   cudaVF_cmp_eqV( ui *h_nTrue, fVector Z, fVector X, fVector Y, ui size );
overror_t  __vcuf OVCUAPI   cudaVF_cmp_neV( ui *h_nTrue, fVector Z, fVector X, fVector Y, ui size );
overror_t  __vcuf OVCUAPI   cudaVF_cmp_leV( ui *h_nTrue, fVector Z, fVector X, fVector Y, ui size );
overror_t  __vcuf OVCUAPI   cudaVF_cmp_ltV( ui *h_nTrue, fVector Z, fVector X, fVector Y, ui size );
overror_t  __vcuf OVCUAPI   cudaVF_cmp_geV( ui *h_nTrue, fVector Z, fVector X, fVector Y, ui size );
overror_t  __vcuf OVCUAPI   cudaVF_cmp_gtV( ui *h_nTrue, fVector Z, fVector X, fVector Y, ui size );

overror_t  __vcuf OVCUAPI   cudaVF_cmp_inclrange0C( ui *h_nTrue, fVector Y, fVector X, ui size, float C );
overror_t  __vcuf OVCUAPI   cudaVF_cmp_exclrange0C( ui *h_nTrue, fVector Y, fVector X, ui size, float C );
overror_t  __vcuf OVCUAPI   cudaVF_cmp_inclrangeCC( ui *h_nTrue, fVector Y, fVector X, ui size, float CLo, float CHi );
overror_t  __vcuf OVCUAPI   cudaVF_cmp_exclrangeCC( ui *h_nTrue, fVector Y, fVector X, ui size, float CLo, float CHi );
overror_t  __vcuf OVCUAPI   cusdVF_cmp_inclrange0C( ui *h_nTrue, fVector Y, fVector X, ui size, float *d_C );
overror_t  __vcuf OVCUAPI   cusdVF_cmp_exclrange0C( ui *h_nTrue, fVector Y, fVector X, ui size, float *d_C );
overror_t  __vcuf OVCUAPI   cusdVF_cmp_inclrangeCC( ui *h_nTrue, fVector Y, fVector X, ui size, float *d_CLo, float *d_CHi );
overror_t  __vcuf OVCUAPI   cusdVF_cmp_exclrangeCC( ui *h_nTrue, fVector Y, fVector X, ui size, float *d_CLo, float *d_CHi );

overror_t  __vcuf OVCUAPI   cudaVF_cnt_eq0( ui *h_nTrue, fVector X, ui size );
overror_t  __vcuf OVCUAPI   cudaVF_cnt_ne0( ui *h_nTrue, fVector X, ui size );
overror_t  __vcuf OVCUAPI   cudaVF_cnt_le0( ui *h_nTrue, fVector X, ui size );
overror_t  __vcuf OVCUAPI   cudaVF_cnt_lt0( ui *h_nTrue, fVector X, ui size );
overror_t  __vcuf OVCUAPI   cudaVF_cnt_ge0( ui *h_nTrue, fVector X, ui size );
overror_t  __vcuf OVCUAPI   cudaVF_cnt_gt0( ui *h_nTrue, fVector X, ui size );

overror_t  __vcuf OVCUAPI   cudaVF_cnt_eqC( ui *h_nTrue, fVector X, ui size, float C );
overror_t  __vcuf OVCUAPI   cudaVF_cnt_neC( ui *h_nTrue, fVector X, ui size, float C );
overror_t  __vcuf OVCUAPI   cudaVF_cnt_leC( ui *h_nTrue, fVector X, ui size, float C );
overror_t  __vcuf OVCUAPI   cudaVF_cnt_ltC( ui *h_nTrue, fVector X, ui size, float C );
overror_t  __vcuf OVCUAPI   cudaVF_cnt_geC( ui *h_nTrue, fVector X, ui size, float C );
overror_t  __vcuf OVCUAPI   cudaVF_cnt_gtC( ui *h_nTrue, fVector X, ui size, float C );
overror_t  __vcuf OVCUAPI   cusdVF_cnt_eqC( ui *h_nTrue, fVector X, ui size, float *d_C );
overror_t  __vcuf OVCUAPI   cusdVF_cnt_neC( ui *h_nTrue, fVector X, ui size, float *d_C );
overror_t  __vcuf OVCUAPI   cusdVF_cnt_leC( ui *h_nTrue, fVector X, ui size, float *d_C );
overror_t  __vcuf OVCUAPI   cusdVF_cnt_ltC( ui *h_nTrue, fVector X, ui size, float *d_C );
overror_t  __vcuf OVCUAPI   cusdVF_cnt_geC( ui *h_nTrue, fVector X, ui size, float *d_C );
overror_t  __vcuf OVCUAPI   cusdVF_cnt_gtC( ui *h_nTrue, fVector X, ui size, float *d_C );

overror_t  __vcuf OVCUAPI   cudaVF_cnt_eqV( ui *h_nTrue, fVector X, fVector Y, ui size );
overror_t  __vcuf OVCUAPI   cudaVF_cnt_neV( ui *h_nTrue, fVector X, fVector Y, ui size );
overror_t  __vcuf OVCUAPI   cudaVF_cnt_leV( ui *h_nTrue, fVector X, fVector Y, ui size );
overror_t  __vcuf OVCUAPI   cudaVF_cnt_ltV( ui *h_nTrue, fVector X, fVector Y, ui size );
overror_t  __vcuf OVCUAPI   cudaVF_cnt_geV( ui *h_nTrue, fVector X, fVector Y, ui size );
overror_t  __vcuf OVCUAPI   cudaVF_cnt_gtV( ui *h_nTrue, fVector X, fVector Y, ui size );

overror_t  __vcuf OVCUAPI   cudaVF_cnt_inclrange0C( ui *h_nTrue, fVector X, ui size, float C );
overror_t  __vcuf OVCUAPI   cudaVF_cnt_exclrange0C( ui *h_nTrue, fVector X, ui size, float C );
overror_t  __vcuf OVCUAPI   cudaVF_cnt_inclrangeCC( ui *h_nTrue, fVector X, ui size, float CLo, float CHi );
overror_t  __vcuf OVCUAPI   cudaVF_cnt_exclrangeCC( ui *h_nTrue, fVector X, ui size, float CLo, float CHi );
overror_t  __vcuf OVCUAPI   cusdVF_cnt_inclrange0C( ui *h_nTrue, fVector X, ui size, float *d_C );
overror_t  __vcuf OVCUAPI   cusdVF_cnt_exclrange0C( ui *h_nTrue, fVector X, ui size, float *d_C );
overror_t  __vcuf OVCUAPI   cusdVF_cnt_inclrangeCC( ui *h_nTrue, fVector X, ui size, float *d_CLo, float *d_CHi );
overror_t  __vcuf OVCUAPI   cusdVF_cnt_exclrangeCC( ui *h_nTrue, fVector X, ui size, float *d_CLo, float *d_CHi );

/*
overror_t  __vcuf OVCUAPI   cudaVF_cmp_eq0ind( ui *h_nTrue, uiVector Ind, fVector X, ui size );
overror_t  __vcuf OVCUAPI   cudaVF_cmp_ne0ind( ui *h_nTrue, uiVector Ind, fVector X, ui size );
overror_t  __vcuf OVCUAPI   cudaVF_cmp_le0ind( ui *h_nTrue, uiVector Ind, fVector X, ui size );
overror_t  __vcuf OVCUAPI   cudaVF_cmp_lt0ind( ui *h_nTrue, uiVector Ind, fVector X, ui size );
overror_t  __vcuf OVCUAPI   cudaVF_cmp_ge0ind( ui *h_nTrue, uiVector Ind, fVector X, ui size );
overror_t  __vcuf OVCUAPI   cudaVF_cmp_gt0ind( ui *h_nTrue, uiVector Ind, fVector X, ui size );

overror_t  __vcuf OVCUAPI   cudaVF_cmp_eqCind( ui *h_nTrue, uiVector Ind, fVector X, ui size, float C );
overror_t  __vcuf OVCUAPI   cudaVF_cmp_neCind( ui *h_nTrue, uiVector Ind, fVector X, ui size, float C );
overror_t  __vcuf OVCUAPI   cudaVF_cmp_leCind( ui *h_nTrue, uiVector Ind, fVector X, ui size, float C );
overror_t  __vcuf OVCUAPI   cudaVF_cmp_ltCind( ui *h_nTrue, uiVector Ind, fVector X, ui size, float C );
overror_t  __vcuf OVCUAPI   cudaVF_cmp_geCind( ui *h_nTrue, uiVector Ind, fVector X, ui size, float C );
overror_t  __vcuf OVCUAPI   cudaVF_cmp_gtCind( ui *h_nTrue, uiVector Ind, fVector X, ui size, float C );
overror_t  __vcuf OVCUAPI   cusdVF_cmp_eqCind( ui *h_nTrue, uiVector Ind, fVector X, ui size, float *d_C );
overror_t  __vcuf OVCUAPI   cusdVF_cmp_neCind( ui *h_nTrue, uiVector Ind, fVector X, ui size, float *d_C );
overror_t  __vcuf OVCUAPI   cusdVF_cmp_leCind( ui *h_nTrue, uiVector Ind, fVector X, ui size, float *d_C );
overror_t  __vcuf OVCUAPI   cusdVF_cmp_ltCind( ui *h_nTrue, uiVector Ind, fVector X, ui size, float *d_C );
overror_t  __vcuf OVCUAPI   cusdVF_cmp_geCind( ui *h_nTrue, uiVector Ind, fVector X, ui size, float *d_C );
overror_t  __vcuf OVCUAPI   cusdVF_cmp_gtCind( ui *h_nTrue, uiVector Ind, fVector X, ui size, float *d_C );

overror_t  __vcuf OVCUAPI   cudaVF_cmp_eqVind( ui *h_nTrue, uiVector Ind, fVector X, fVector Y, ui size );
overror_t  __vcuf OVCUAPI   cudaVF_cmp_neVind( ui *h_nTrue, uiVector Ind, fVector X, fVector Y, ui size );
overror_t  __vcuf OVCUAPI   cudaVF_cmp_leVind( ui *h_nTrue, uiVector Ind, fVector X, fVector Y, ui size );
overror_t  __vcuf OVCUAPI   cudaVF_cmp_ltVind( ui *h_nTrue, uiVector Ind, fVector X, fVector Y, ui size );
overror_t  __vcuf OVCUAPI   cudaVF_cmp_geVind( ui *h_nTrue, uiVector Ind, fVector X, fVector Y, ui size );
overror_t  __vcuf OVCUAPI   cudaVF_cmp_gtVind( ui *h_nTrue, uiVector Ind, fVector X, fVector Y, ui size );

overror_t  __vcuf OVCUAPI   cudaVF_cmp_inclrange0Cind( ui *h_nTrue, uiVector Ind, fVector X, ui size, float C );
overror_t  __vcuf OVCUAPI   cudaVF_cmp_exclrange0Cind( ui *h_nTrue, uiVector Ind, fVector X, ui size, float C );
overror_t  __vcuf OVCUAPI   cudaVF_cmp_inclrangeCCind( ui *h_nTrue, uiVector Ind, fVector X, ui size, float CLo, float CHi );
overror_t  __vcuf OVCUAPI   cudaVF_cmp_exclrangeCCind( ui *h_nTrue, uiVector Ind, fVector X, ui size, float CLo, float CHi );
overror_t  __vcuf OVCUAPI   cusdVF_cmp_inclrange0Cind( ui *h_nTrue, uiVector Ind, fVector X, ui size, float *d_C );
overror_t  __vcuf OVCUAPI   cusdVF_cmp_exclrange0Cind( ui *h_nTrue, uiVector Ind, fVector X, ui size, float *d_C );
overror_t  __vcuf OVCUAPI   cusdVF_cmp_inclrangeCCind( ui *h_nTrue, uiVector Ind, fVector X, ui size, float *d_CLo, float *d_CHi );
overror_t  __vcuf OVCUAPI   cusdVF_cmp_exclrangeCCind( ui *h_nTrue, uiVector Ind, fVector X, ui size, float *d_CLo, float *d_CHi );
*/

/********************  Standard Arithmetics   ***************************/

overror_t  __vcuf OVCUAPI   cudaVF_equC( fVector X, ui size, float C );
overror_t  __vcuf OVCUAPI   cusdVF_equC( fVector X, ui size, float *d_C );
overror_t  __vcuf OVCUAPI   cudaVF_equV( fVector Y, fVector X, ui size );
overror_t  __vcuf OVCUAPI   cudaVFx_equV( fVector Y, fVector X, ui size, float A, float B );
overror_t  __vcuf OVCUAPI   cusdVFx_equV( fVector Y, fVector X, ui size, float *d_A, float *d_B );

overror_t  __vcuf OVCUAPI   cudaVF_addC(  fVector Y, fVector X, ui size, float C );
overror_t  __vcuf OVCUAPI   cudaVF_subC(  fVector Y, fVector X, ui size, float C );
overror_t  __vcuf OVCUAPI   cudaVF_subrC( fVector Y, fVector X, ui size, float C );
overror_t  __vcuf OVCUAPI   cudaVF_mulC(  fVector Y, fVector X, ui size, float C );
overror_t  __vcuf OVCUAPI   cudaVF_divC(  fVector Y, fVector X, ui size, float C );
overror_t  __vcuf OVCUAPI   cudaVF_divrC( fVector Y, fVector X, ui size, float C );
overror_t  __vcuf OVCUAPI   cudaVFx_divrC( fVector Y, fVector X, ui size, float A, float B, float C );

overror_t  __vcuf OVCUAPI   cusdVF_addC(  fVector Y, fVector X, ui size, float *d_C );
overror_t  __vcuf OVCUAPI   cusdVF_subC(  fVector Y, fVector X, ui size, float *d_C );
overror_t  __vcuf OVCUAPI   cusdVF_subrC( fVector Y, fVector X, ui size, float *d_C );
overror_t  __vcuf OVCUAPI   cusdVF_mulC(  fVector Y, fVector X, ui size, float *d_C );
overror_t  __vcuf OVCUAPI   cusdVF_divC(  fVector Y, fVector X, ui size, float *d_C );
overror_t  __vcuf OVCUAPI   cusdVF_divrC( fVector Y, fVector X, ui size, float *d_C );
overror_t  __vcuf OVCUAPI   cusdVFx_divrC( fVector Y, fVector X, ui size, float *d_A, float *d_B, float *d_C );

overror_t  __vcuf OVCUAPI   cudaVF_addV(  fVector Z, fVector X, fVector Y, ui size );
overror_t  __vcuf OVCUAPI   cudaVF_subV(  fVector Z, fVector X, fVector Y, ui size );
overror_t  __vcuf OVCUAPI   cudaVF_subrV( fVector Z, fVector X, fVector Y, ui size );
overror_t  __vcuf OVCUAPI   cudaVF_mulV(  fVector Z, fVector X, fVector Y, ui size );
overror_t  __vcuf OVCUAPI   cudaVF_divV(  fVector Z, fVector X, fVector Y, ui size );
overror_t  __vcuf OVCUAPI   cudaVF_divrV(  fVector Z, fVector X, fVector Y, ui size );
overror_t  __vcuf OVCUAPI   cudaVF_add2V(  fVector Z, fVector X, fVector Y1, fVector Y2, ui size );
overror_t  __vcuf OVCUAPI   cudaVF_sub2V(  fVector Z, fVector X, fVector Y1, fVector Y2, ui size );

overror_t  __vcuf OVCUAPI   cudaVF_CaddV( fVector Z, fVector X, fVector Y, ui siz, float C );
overror_t  __vcuf OVCUAPI   cusdVF_CaddV( fVector Z, fVector X, fVector Y, ui siz, float *d_C );
                              /* Z = X + C*Y  */

overror_t  __vcuf OVCUAPI   cudaVFx_addV(  fVector Z, fVector X, fVector Y, ui size, float A, float B );
                              /* Z = (A*X+B) + Y  */
overror_t  __vcuf OVCUAPI   cudaVFx_subV(  fVector Z, fVector X, fVector Y, ui size, float A, float B );
overror_t  __vcuf OVCUAPI   cudaVFx_subrV( fVector Z, fVector X, fVector Y, ui size, float A, float B );
overror_t  __vcuf OVCUAPI   cudaVFx_mulV(  fVector Z, fVector X, fVector Y, ui size, float A, float B );
overror_t  __vcuf OVCUAPI   cudaVFx_divV(  fVector Z, fVector X, fVector Y, ui size, float A, float B );
overror_t  __vcuf OVCUAPI   cudaVFx_divrV( fVector Z, fVector X, fVector Y, ui size, float A, float B );

overror_t  __vcuf OVCUAPI   cusdVFx_addV(  fVector Z, fVector X, fVector Y, ui size, float *d_A, float *d_B );
overror_t  __vcuf OVCUAPI   cusdVFx_subV(  fVector Z, fVector X, fVector Y, ui size, float *d_A, float *d_B );
overror_t  __vcuf OVCUAPI   cusdVFx_subrV( fVector Z, fVector X, fVector Y, ui size, float *d_A, float *d_B );
overror_t  __vcuf OVCUAPI   cusdVFx_mulV(  fVector Z, fVector X, fVector Y, ui size, float *d_A, float *d_B );
overror_t  __vcuf OVCUAPI   cusdVFx_divV(  fVector Z, fVector X, fVector Y, ui size, float *d_A, float *d_B );
overror_t  __vcuf OVCUAPI   cusdVFx_divrV( fVector Z, fVector X, fVector Y, ui size, float *d_A, float *d_B );

overror_t  __vcuf OVCUAPI   cudaVFs_addV(  fVector Z, fVector X, fVector Y, ui size, float C ); /* Z=C*(X+Y) */
overror_t  __vcuf OVCUAPI   cudaVFs_subV(  fVector Z, fVector X, fVector Y, ui size, float C );
overror_t  __vcuf OVCUAPI   cudaVFs_subrV( fVector Z, fVector X, fVector Y, ui size, float C );
overror_t  __vcuf OVCUAPI   cudaVFs_mulV(  fVector Z, fVector X, fVector Y, ui size, float C );
overror_t  __vcuf OVCUAPI   cudaVFs_divV(  fVector Z, fVector X, fVector Y, ui size, float C );
overror_t  __vcuf OVCUAPI   cudaVFs_divrV( fVector Z, fVector X, fVector Y, ui size, float C );

overror_t  __vcuf OVCUAPI   cusdVFs_addV(  fVector Z, fVector X, fVector Y, ui size, float *d_C ); /* Z=C*(X+Y) */
overror_t  __vcuf OVCUAPI   cusdVFs_subV(  fVector Z, fVector X, fVector Y, ui size, float *d_C );
overror_t  __vcuf OVCUAPI   cusdVFs_subrV( fVector Z, fVector X, fVector Y, ui size, float *d_C );
overror_t  __vcuf OVCUAPI   cusdVFs_mulV(  fVector Z, fVector X, fVector Y, ui size, float *d_C );
overror_t  __vcuf OVCUAPI   cusdVFs_divV(  fVector Z, fVector X, fVector Y, ui size, float *d_C );
overror_t  __vcuf OVCUAPI   cusdVFs_divrV( fVector Z, fVector X, fVector Y, ui size, float *d_C );

overror_t  __vcuf OVCUAPI   cudaVF_maxC(   fVector Y, fVector X, ui size, float C );
overror_t  __vcuf OVCUAPI   cudaVF_minC(   fVector Y, fVector X, ui size, float C );
overror_t  __vcuf OVCUAPI   cudaVF_limit(  fVector Y, fVector X, ui size, float Min, float Max );
overror_t  __vcuf OVCUAPI   cudaVF_flush0( fVector Y, fVector X, ui size, float AbsMin );
overror_t  __vcuf OVCUAPI   cudaVF_flushInv( fVector Y, fVector X, ui size, float AbsMin );
overror_t  __vcuf OVCUAPI   cudaVF_replaceNAN( fVector Y, fVector X, ui size, float C );
overror_t  __vcuf OVCUAPI   cudaVF_maxV(   fVector Z, fVector X, fVector Y, ui size );
overror_t  __vcuf OVCUAPI   cudaVF_minV(   fVector Z, fVector X, fVector Y, ui size );
overror_t  __vcuf OVCUAPI   cudaVF_modC(   fVector Y, fVector X, ui size, float C );
overror_t  __vcuf OVCUAPI   cudaVF_modV(   fVector Z, fVector X, fVector Y, ui size );
overror_t  __vcuf OVCUAPI   cudaVFx_modV(  fVector Z, fVector X, fVector Y, ui size, float A, float B );
#define     cudaVF_fmodC    cudaVF_modC
#define     cudaVF_fmodV    cudaVF_modV
#define     cudaVFx_fmodV   cudaVFx_modV

overror_t  __vcuf OVCUAPI   cudaVF_redC(  fVector Y, fVector X, ui size, float C );
overror_t  __vcuf OVCUAPI   cudaVF_redV(  fVector Z, fVector X, fVector Y, ui size );
overror_t  __vcuf OVCUAPI   cudaVFx_redV( fVector Z, fVector X, fVector Y, ui size, float A, float B );
overror_t  __vcuf OVCUAPI   cudaVF_visC(  fVector Y, fVector X, ui size, float C );
overror_t  __vcuf OVCUAPI   cudaVF_visV(  fVector Z, fVector X, fVector Y, ui size );
overror_t  __vcuf OVCUAPI   cudaVFx_visV( fVector Z, fVector X, fVector Y, ui size, float A, float B );
overror_t  __vcuf OVCUAPI   cudaVF_hypC(  fVector Y, fVector X, ui size, float C );
overror_t  __vcuf OVCUAPI   cudaVF_hypV(  fVector Z, fVector X, fVector Y, ui size );
overror_t  __vcuf OVCUAPI   cudaVFx_hypV( fVector Z, fVector X, fVector Y, ui size, float A, float B );

overror_t  __vcuf OVCUAPI  cudaVF_lincomb( fVector Z, fVector X, fVector Y, ui size,
                      float CX, float CY );  /* Z=CX*X+CY*Y */

overror_t  __vcuf OVCUAPI  cudaVF_rotateCoordinates( fVector Xnew, fVector Ynew, fVector Xold, fVector Yold,
                      ui size, float costheta, float sintheta );
#define cudaVF_sgn    cudaVF_cmp0

overror_t  __vcuf OVCUAPI   cusdVF_maxC(   fVector Y, fVector X, ui size, float *d_C );
overror_t  __vcuf OVCUAPI   cusdVF_minC(   fVector Y, fVector X, ui size, float *d_C );
overror_t  __vcuf OVCUAPI   cusdVF_limit(  fVector Y, fVector X, ui size, float *d_Min, float *d_Max );
overror_t  __vcuf OVCUAPI   cusdVF_flush0( fVector Y, fVector X, ui size, float *d_AbsMin );
overror_t  __vcuf OVCUAPI   cusdVF_flushInv( fVector Y, fVector X, ui size, float *d_AbsMin );
overror_t  __vcuf OVCUAPI   cusdVF_replaceNAN( fVector Y, fVector X, ui size, float *d_C );
overror_t  __vcuf OVCUAPI   cusdVF_modC(   fVector Y, fVector X, ui size, float *d_C );
overror_t  __vcuf OVCUAPI   cusdVFx_modV(  fVector Z, fVector X, fVector Y, ui size, float *d_A, float *d_B );
#define     cusdVF_fmodC    cusdVF_modC
#define     cusdVFx_fmodV   cusdVFx_modV
overror_t  __vcuf OVCUAPI   cusdVF_redC(  fVector Y, fVector X, ui size, float *d_C );
overror_t  __vcuf OVCUAPI   cusdVFx_redV( fVector Z, fVector X, fVector Y, ui size, float *d_A, float *d_B );
overror_t  __vcuf OVCUAPI   cusdVF_visC(  fVector Y, fVector X, ui size, float *d_C );
overror_t  __vcuf OVCUAPI   cusdVFx_visV( fVector Z, fVector X, fVector Y, ui size, float *d_A, float *d_B );
overror_t  __vcuf OVCUAPI   cusdVF_hypC(  fVector Y, fVector X, ui size, float *d_C );
overror_t  __vcuf OVCUAPI   cusdVFx_hypV( fVector Z, fVector X, fVector Y, ui size, float *d_A, float *d_B );
overror_t  __vcuf OVCUAPI  cusdVF_lincomb( fVector Z, fVector X, fVector Y, ui size,  float *d_CX, float *d_CY );  /* Z=CX*X+CY*Y */
overror_t  __vcuf OVCUAPI  cusdVF_rotateCoordinates( fVector Xnew, fVector Ynew, fVector Xold, fVector Yold,
                      ui size, float *d_costheta, float *d_sintheta );

/******************* Mixed-type arithmetic Functions **********************/

overror_t  __vcuf OVCUAPI   cudaVF_addVBI(  fVector Z, fVector X, biVector Y, ui size );
overror_t  __vcuf OVCUAPI   cudaVF_subVBI(  fVector Z, fVector X, biVector Y, ui size );
overror_t  __vcuf OVCUAPI   cudaVF_subrVBI( fVector Z, fVector X, biVector Y, ui size );
overror_t  __vcuf OVCUAPI   cudaVF_mulVBI(  fVector Z, fVector X, biVector Y, ui size );
overror_t  __vcuf OVCUAPI   cudaVF_divVBI(  fVector Z, fVector X, biVector Y, ui size );
overror_t  __vcuf OVCUAPI   cudaVF_divrVBI( fVector Z, fVector X, biVector Y, ui size );
overror_t  __vcuf OVCUAPI   cudaVF_addVSI(  fVector Z, fVector X, siVector Y, ui size );
overror_t  __vcuf OVCUAPI   cudaVF_subVSI(  fVector Z, fVector X, siVector Y, ui size );
overror_t  __vcuf OVCUAPI   cudaVF_subrVSI( fVector Z, fVector X, siVector Y, ui size );
overror_t  __vcuf OVCUAPI   cudaVF_mulVSI(  fVector Z, fVector X, siVector Y, ui size );
overror_t  __vcuf OVCUAPI   cudaVF_divVSI(  fVector Z, fVector X, siVector Y, ui size );
overror_t  __vcuf OVCUAPI   cudaVF_divrVSI( fVector Z, fVector X, siVector Y, ui size );
overror_t  __vcuf OVCUAPI   cudaVF_addVI(  fVector Z, fVector X, iVector Y, ui size );
overror_t  __vcuf OVCUAPI   cudaVF_subVI(  fVector Z, fVector X, iVector Y, ui size );
overror_t  __vcuf OVCUAPI   cudaVF_subrVI( fVector Z, fVector X, iVector Y, ui size );
overror_t  __vcuf OVCUAPI   cudaVF_mulVI(  fVector Z, fVector X, iVector Y, ui size );
overror_t  __vcuf OVCUAPI   cudaVF_divVI(  fVector Z, fVector X, iVector Y, ui size );
overror_t  __vcuf OVCUAPI   cudaVF_divrVI( fVector Z, fVector X, iVector Y, ui size );
overror_t  __vcuf OVCUAPI   cudaVF_addVLI(  fVector Z, fVector X, liVector Y, ui size );
overror_t  __vcuf OVCUAPI   cudaVF_subVLI(  fVector Z, fVector X, liVector Y, ui size );
overror_t  __vcuf OVCUAPI   cudaVF_subrVLI( fVector Z, fVector X, liVector Y, ui size );
overror_t  __vcuf OVCUAPI   cudaVF_mulVLI(  fVector Z, fVector X, liVector Y, ui size );
overror_t  __vcuf OVCUAPI   cudaVF_divVLI(  fVector Z, fVector X, liVector Y, ui size );
overror_t  __vcuf OVCUAPI   cudaVF_divrVLI( fVector Z, fVector X, liVector Y, ui size );
overror_t  __vcuf OVCUAPI   cudaVF_addVQI(  fVector Z, fVector X, qiVector Y, ui size );
overror_t  __vcuf OVCUAPI   cudaVF_subVQI(  fVector Z, fVector X, qiVector Y, ui size );
overror_t  __vcuf OVCUAPI   cudaVF_subrVQI( fVector Z, fVector X, qiVector Y, ui size );
overror_t  __vcuf OVCUAPI   cudaVF_mulVQI(  fVector Z, fVector X, qiVector Y, ui size );
overror_t  __vcuf OVCUAPI   cudaVF_divVQI(  fVector Z, fVector X, qiVector Y, ui size );
overror_t  __vcuf OVCUAPI   cudaVF_divrVQI( fVector Z, fVector X, qiVector Y, ui size );
overror_t  __vcuf OVCUAPI   cudaVF_addVUB(  fVector Z, fVector X, ubVector Y, ui size );
overror_t  __vcuf OVCUAPI   cudaVF_subVUB(  fVector Z, fVector X, ubVector Y, ui size );
overror_t  __vcuf OVCUAPI   cudaVF_subrVUB( fVector Z, fVector X, ubVector Y, ui size );
overror_t  __vcuf OVCUAPI   cudaVF_mulVUB(  fVector Z, fVector X, ubVector Y, ui size );
overror_t  __vcuf OVCUAPI   cudaVF_divVUB(  fVector Z, fVector X, ubVector Y, ui size );
overror_t  __vcuf OVCUAPI   cudaVF_divrVUB( fVector Z, fVector X, ubVector Y, ui size );
overror_t  __vcuf OVCUAPI   cudaVF_addVUS(  fVector Z, fVector X, usVector Y, ui size );
overror_t  __vcuf OVCUAPI   cudaVF_subVUS(  fVector Z, fVector X, usVector Y, ui size );
overror_t  __vcuf OVCUAPI   cudaVF_subrVUS( fVector Z, fVector X, usVector Y, ui size );
overror_t  __vcuf OVCUAPI   cudaVF_mulVUS(  fVector Z, fVector X, usVector Y, ui size );
overror_t  __vcuf OVCUAPI   cudaVF_divVUS(  fVector Z, fVector X, usVector Y, ui size );
overror_t  __vcuf OVCUAPI   cudaVF_divrVUS( fVector Z, fVector X, usVector Y, ui size );
overror_t  __vcuf OVCUAPI   cudaVF_addVU(   fVector Z, fVector X, uVector Y,  ui size );
overror_t  __vcuf OVCUAPI   cudaVF_subVU(   fVector Z, fVector X, uVector Y,  ui size );
overror_t  __vcuf OVCUAPI   cudaVF_subrVU(  fVector Z, fVector X, uVector Y,  ui size );
overror_t  __vcuf OVCUAPI   cudaVF_mulVU(   fVector Z, fVector X, uVector Y,  ui size );
overror_t  __vcuf OVCUAPI   cudaVF_divVU(   fVector Z, fVector X, uVector Y,  ui size );
overror_t  __vcuf OVCUAPI   cudaVF_divrVU(  fVector Z, fVector X, uVector Y,  ui size );
overror_t  __vcuf OVCUAPI   cudaVF_addVUL(  fVector Z, fVector X, ulVector Y, ui size );
overror_t  __vcuf OVCUAPI   cudaVF_subVUL(  fVector Z, fVector X, ulVector Y, ui size );
overror_t  __vcuf OVCUAPI   cudaVF_subrVUL( fVector Z, fVector X, ulVector Y, ui size );
overror_t  __vcuf OVCUAPI   cudaVF_mulVUL(  fVector Z, fVector X, ulVector Y, ui size );
overror_t  __vcuf OVCUAPI   cudaVF_divVUL(  fVector Z, fVector X, ulVector Y, ui size );
overror_t  __vcuf OVCUAPI   cudaVF_divrVUL( fVector Z, fVector X, ulVector Y, ui size );
#ifdef _WIN64
    overror_t  __vcuf OVCUAPI   cudaVF_addVUQ(  fVector Z, fVector X, uqVector Y, ui size );
    overror_t  __vcuf OVCUAPI   cudaVF_subVUQ(  fVector Z, fVector X, uqVector Y, ui size );
    overror_t  __vcuf OVCUAPI   cudaVF_subrVUQ( fVector Z, fVector X, uqVector Y, ui size );
    overror_t  __vcuf OVCUAPI   cudaVF_mulVUQ(  fVector Z, fVector X, uqVector Y, ui size );
    overror_t  __vcuf OVCUAPI   cudaVF_divVUQ(  fVector Z, fVector X, uqVector Y, ui size );
    overror_t  __vcuf OVCUAPI   cudaVF_divrVUQ( fVector Z, fVector X, uqVector Y, ui size );
    #define cudaVF_addVUI  cudaVF_addVUQ
    #define cudaVF_subVUI  cudaVF_subVUQ
    #define cudaVF_subrVUI cudaVF_subrVUQ
    #define cudaVF_mulVUI  cudaVF_mulVUQ
    #define cudaVF_divVUI  cudaVF_divVUQ
    #define cudaVF_divrVUI cudaVF_divrVUQ
#else
    #define cudaVF_addVUI  cudaVF_addVU
    #define cudaVF_subVUI  cudaVF_subVU
    #define cudaVF_subrVUI cudaVF_subrVU
    #define cudaVF_mulVUI  cudaVF_mulVU
    #define cudaVF_divVUI  cudaVF_divVU
    #define cudaVF_divrVUI cudaVF_divrVU
#endif

/******************** Accumulation (Y += X) ******************************/

overror_t  __vcuf OVCUAPI  cudaVF_accV(   fVector Y, fVector  X, ui size );
overror_t  __vcuf OVCUAPI  cudaVF_acc2V(  fVector Y, fVector  X1, fVector  X2, ui size );
overror_t  __vcuf OVCUAPI  cudaVF_accVBI( fVector Y, biVector X, ui size );
overror_t  __vcuf OVCUAPI  cudaVF_accVSI( fVector Y, siVector X, ui size );
overror_t  __vcuf OVCUAPI  cudaVF_accVI(  fVector Y, iVector  X, ui size );
overror_t  __vcuf OVCUAPI  cudaVF_accVLI( fVector Y, liVector X, ui size );
overror_t  __vcuf OVCUAPI  cudaVF_accVQI( fVector Y, qiVector X, ui size );
overror_t  __vcuf OVCUAPI  cudaVF_accVUB( fVector Y, ubVector X, ui size );
overror_t  __vcuf OVCUAPI  cudaVF_accVUS( fVector Y, usVector X, ui size );
overror_t  __vcuf OVCUAPI  cudaVF_accVU(  fVector Y, uVector  X, ui size );
overror_t  __vcuf OVCUAPI  cudaVF_accVUL( fVector Y, ulVector X, ui size );
#if defined _WIN64
    overror_t  __vcuf OVCUAPI  cudaVF_accVUQ( fVector Y, uqVector X, ui size );
    #define cudaVF_accVUI   cudaVF_accVUQ
#else
    #define cudaVF_accVUI   cudaVF_accVU
#endif

/***************** Functions of a sub-set of elements  ********************/

overror_t  __vcuf OVCUAPI   cudaVF_subvector_equC(  fVector Y, ui subsiz, ui samp, float C );
overror_t  __vcuf OVCUAPI   cusdVF_subvector_equC(  fVector Y, ui subsiz, ui samp, float *d_C );
overror_t  __vcuf OVCUAPI   cudaVF_subvector_equV(  fVector Y, ui subsiz, ui samp, fVector X );

overror_t  __vcuf OVCUAPI   cudaVF_subvector_addC(  fVector Y, ui subsiz, ui samp, float C );
overror_t  __vcuf OVCUAPI   cudaVF_subvector_subC(  fVector Y, ui subsiz, ui samp, float C );
overror_t  __vcuf OVCUAPI   cudaVF_subvector_subrC( fVector Y, ui subsiz, ui samp, float C );
overror_t  __vcuf OVCUAPI   cudaVF_subvector_mulC(  fVector Y, ui subsiz, ui samp, float C );
overror_t  __vcuf OVCUAPI   cudaVF_subvector_divC(  fVector Y, ui subsiz, ui samp, float C );
overror_t  __vcuf OVCUAPI   cudaVF_subvector_divrC( fVector Y, ui subsiz, ui samp, float C );

overror_t  __vcuf OVCUAPI   cusdVF_subvector_addC(  fVector Y, ui subsiz, ui samp, float *d_C );
overror_t  __vcuf OVCUAPI   cusdVF_subvector_subC(  fVector Y, ui subsiz, ui samp, float *d_C );
overror_t  __vcuf OVCUAPI   cusdVF_subvector_subrC( fVector Y, ui subsiz, ui samp, float *d_C );
overror_t  __vcuf OVCUAPI   cusdVF_subvector_mulC(  fVector Y, ui subsiz, ui samp, float *d_C );
overror_t  __vcuf OVCUAPI   cusdVF_subvector_divC(  fVector Y, ui subsiz, ui samp, float *d_C );
overror_t  __vcuf OVCUAPI   cusdVF_subvector_divrC( fVector Y, ui subsiz, ui samp, float *d_C );

overror_t  __vcuf OVCUAPI   cudaVF_subvector_addV(  fVector Y, ui subsiz, ui samp, fVector X );
overror_t  __vcuf OVCUAPI   cudaVF_subvector_subV(  fVector Y, ui subsiz, ui samp, fVector X );
overror_t  __vcuf OVCUAPI   cudaVF_subvector_subrV( fVector Y, ui subsiz, ui samp, fVector X );
overror_t  __vcuf OVCUAPI   cudaVF_subvector_mulV(  fVector Y, ui subsiz, ui samp, fVector X );
overror_t  __vcuf OVCUAPI   cudaVF_subvector_divV(  fVector Y, ui subsiz, ui samp, fVector X );
overror_t  __vcuf OVCUAPI   cudaVF_subvector_divrV( fVector Y, ui subsiz, ui samp, fVector X );


/*********************  Mathematical Functions ***********************/

overror_t  __vcuf OVCUAPI   cudaVF_abs( fVector Y, fVector X, ui size );
overror_t  __vcuf OVCUAPI   cudaVF_neg( fVector Y, fVector X, ui size );
overror_t  __vcuf OVCUAPI   cudaVF_inv( fVector Y, fVector X, ui size );
overror_t  __vcuf OVCUAPI   cudaVFx_inv( fVector Y, fVector X, ui size, float A, float B );
overror_t  __vcuf OVCUAPI   cusdVFx_inv( fVector Y, fVector X, ui size, float *d_A, float *d_B );
overror_t  __vcuf OVCUAPI   cudaVF_intfrac( fVector Int, fVector Frac, fVector X, ui size );
#define      cudaVF_modf    cudaVF_intfrac
overror_t  __vcuf OVCUAPI   cudaVF_mantexp( fVector Mant, iVector Exp, fVector X, ui size );
#define      cudaVF_frexp   cudaVF_mantexp

overror_t  __vcuf OVCUAPI   cudaVF_hypotC( fVector Y, fVector X, ui size, float C );
overror_t  __vcuf OVCUAPI   cusdVF_hypotC( fVector Y, fVector X, ui size, float *d_C );
overror_t  __vcuf OVCUAPI   cudaVF_hypotV( fVector Z, fVector X, fVector Y, ui size );
overror_t  __vcuf OVCUAPI   cudaVFx_hypotV( fVector Z, fVector X, fVector Y, ui size, float A, float B );
overror_t  __vcuf OVCUAPI   cusdVFx_hypotV( fVector Z, fVector X, fVector Y, ui size, float *d_A, float *d_B );

overror_t  __vcuf OVCUAPI   cudaVF_scale2( fVector Y, fVector X, ui size, int expo );
overror_t  __vcuf OVCUAPI   cudaVF_scale10( fVector Y, fVector X, ui size, int expo );
#define       cudaVF_ldexp    cudaVF_scale2

overror_t  __vcuf OVCUAPI   cudaVF_square( fVector Y, fVector X, ui size );
overror_t  __vcuf OVCUAPI   cudaVFx_square( fVector Y, fVector X, ui size, float A, float B );
overror_t  __vcuf OVCUAPI   cudaVF_cubic( fVector Y, fVector X, ui size );
overror_t  __vcuf OVCUAPI   cudaVFx_cubic( fVector Y, fVector X, ui size, float A, float B );
overror_t  __vcuf OVCUAPI   cudaVF_quartic( fVector Y, fVector X, ui size );
overror_t  __vcuf OVCUAPI   cudaVFx_quartic( fVector Y, fVector X, ui size, float A, float B );
overror_t  __vcuf OVCUAPI   cudaVF_poly( fVector Y, fVector X, ui size, fVector h_Coeff, unsigned deg );
overror_t  __vcuf OVCUAPI   cudaVFx_poly( fVector Y, fVector X, ui size, fVector h_Coeff, unsigned deg, float A, float B );
overror_t  __vcuf OVCUAPI   cudaVF_ipow( fVector Y, fVector X, ui size, int ipow );
overror_t  __vcuf OVCUAPI   cudaVFx_ipow( fVector Y, fVector X, ui size, int ipow, float A, float B, float C );
                           /*  ipow = integer power of x */
overror_t  __vcuf OVCUAPI   cusdVFx_square( fVector Y, fVector X, ui size, float *d_A, float *d_B );
overror_t  __vcuf OVCUAPI   cusdVFx_cubic( fVector Y, fVector X, ui size, float *d_A, float *d_B );
overror_t  __vcuf OVCUAPI   cusdVFx_quartic( fVector Y, fVector X, ui size, float *d_A, float *d_B );
overror_t  __vcuf OVCUAPI   cusdVF_poly( fVector Y, fVector X, ui size, fVector d_Coeff, unsigned deg );
overror_t  __vcuf OVCUAPI   cusdVFx_poly( fVector Y, fVector X, ui size, fVector d_Coeff, unsigned deg, float *d_A, float *d_B );
overror_t  __vcuf OVCUAPI   cusdVFx_ipow( fVector Y, fVector X, ui size, int ipow, float *d_A, float *d_B, float *d_C );

       /* extra fast integer powers: "unprotected", without error handling: */
overror_t  __vcuf OVCUAPI   cudaVFu_square( fVector Y, fVector X, ui size );
overror_t  __vcuf OVCUAPI   cudaVFux_square( fVector Y, fVector X, ui size, float A, float B );
overror_t  __vcuf OVCUAPI   cudaVFu_cubic( fVector Y, fVector X, ui size );
overror_t  __vcuf OVCUAPI   cudaVFux_cubic( fVector Y, fVector X, ui size, float A, float B );
overror_t  __vcuf OVCUAPI   cudaVFu_quartic( fVector Y, fVector X, ui size );
overror_t  __vcuf OVCUAPI   cudaVFux_quartic( fVector Y, fVector X, ui size, float A, float B );
overror_t  __vcuf OVCUAPI   cudaVFu_poly( fVector Y, fVector X, ui size, fVector h_Coeff, unsigned deg );
overror_t  __vcuf OVCUAPI   cudaVFux_poly( fVector Y, fVector X, ui size, fVector h_Coeff, unsigned deg, float A, float B );
overror_t  __vcuf OVCUAPI   cudaVFu_ipow( fVector Y, fVector X, ui size, int ipow );
overror_t  __vcuf OVCUAPI   cudaVFux_ipow( fVector Y, fVector X, ui size, int ipow, float A, float B, float C );

overror_t  __vcuf OVCUAPI   cusdVFux_square( fVector Y, fVector X, ui size, float *d_A, float *d_B );
overror_t  __vcuf OVCUAPI   cusdVFux_cubic( fVector Y, fVector X, ui size, float *d_A, float *d_B );
overror_t  __vcuf OVCUAPI   cusdVFux_quartic( fVector Y, fVector X, ui size, float *d_A, float *d_B );
overror_t  __vcuf OVCUAPI   cusdVFu_poly( fVector Y, fVector X, ui size, fVector d_Coeff, unsigned deg );
overror_t  __vcuf OVCUAPI   cusdVFux_poly( fVector Y, fVector X, ui size, fVector d_Coeff, unsigned deg, float *d_A, float *d_B );
overror_t  __vcuf OVCUAPI   cusdVFux_ipow( fVector Y, fVector X, ui size, int ipow, float *d_A, float *d_B, float *d_C );

overror_t  __vcuf OVCUAPI   cudaVF_ipow2(  fVector Y, iVector X, ui size );
overror_t  __vcuf OVCUAPI   cudaVF_ipow10( fVector Y, iVector X, ui size );
                          /* ipow2 and ipow10: integer powers of 2 and 10 */

overror_t  __vcuf OVCUAPI   cudaVF_pow(    fVector Y, fVector X, ui size, float expo );
overror_t  __vcuf OVCUAPI   cudaVFx_pow(   fVector Y, fVector X, ui size, float expo, float A, float B, float C );

overror_t  __vcuf OVCUAPI   cudaVF_pow2(   fVector Y, fVector X, ui size );
overror_t  __vcuf OVCUAPI   cudaVFx_pow2(  fVector Y, fVector X, ui size, float A, float B, float C );
overror_t  __vcuf OVCUAPI   cudaVF_pow10(  fVector Y, fVector X, ui size );
overror_t  __vcuf OVCUAPI   cudaVFx_pow10( fVector Y, fVector X, ui size, float A, float B, float C );
            /* pow2 and pow10: basis 2 or 10 raised to power x */

overror_t  __vcuf OVCUAPI   cudaVF_sqrt(  fVector Y, fVector X, ui size );
overror_t  __vcuf OVCUAPI   cudaVFx_sqrt( fVector Y, fVector X, ui size, float A, float B, float C );

overror_t  __vcuf OVCUAPI   cudaVF_log(    fVector Y, fVector X, ui size );
overror_t  __vcuf OVCUAPI   cudaVF_log2(   fVector Y, fVector X, ui size );
overror_t  __vcuf OVCUAPI   cudaVF_log10(  fVector Y, fVector X, ui size );
#define     cudaVF_ln      cudaVF_log
overror_t  __vcuf OVCUAPI   cudaVFx_log(   fVector Y, fVector X, ui size, float A, float B, float C );
overror_t  __vcuf OVCUAPI   cudaVFx_log2(  fVector Y, fVector X, ui size, float A, float B, float C );
overror_t  __vcuf OVCUAPI   cudaVFx_log10( fVector Y, fVector X, ui size, float A, float B, float C );
#define     cudaVFx_ln     cudaVFx_log

overror_t  __vcuf OVCUAPI   cudaVF_OD( fVector OD, fVector X, fVector X0, ui size );  /* OD = log10( X0/X ) */
overror_t  __vcuf OVCUAPI   cudaVF_ODwDark( fVector OD, fVector X, fVector XDark, fVector X0, fVector X0Dark, ui size );
void __vcuf OVCUAPI   cudaVF_setODThresh( float minX, float minX0 );

overror_t  __vcuf OVCUAPI   cudaVF_exp(   fVector Y, fVector X, ui size );
overror_t  __vcuf OVCUAPI   cudaVFx_exp(  fVector Y, fVector X, ui size, float A, float B, float C );
overror_t  __vcuf OVCUAPI   cudaVF_expArbBase(  fVector Y, fVector X, ui size, float Base );
overror_t  __vcuf OVCUAPI   cudaVFx_expArbBase( fVector Y, fVector X, ui size, float Base,
                            float A, float B, float C );
overror_t  __vcuf OVCUAPI   cudaVF_expc(  fVector Y, fVector X, ui size );
overror_t  __vcuf OVCUAPI   cudaVFx_expc( fVector Y, fVector X, ui size, float A, float B, float C );
                /* expc(x) = 1 - exp(x)  */
overror_t  __vcuf OVCUAPI   cudaVF_expmx2(  fVector Y, fVector X, ui size );
overror_t  __vcuf OVCUAPI   cudaVFx_expmx2( fVector Y, fVector X, ui size, float A, float B, float C );
                /* expmx2(x) = exp( -x**2 )  */
#define cudaVF_exp2   cudaVF_pow2
#define cudaVFx_exp2  cudaVFx_pow2
#define cudaVF_exp10   cudaVF_pow10
#define cudaVFx_exp10  cudaVFx_pow10
overror_t  __vcuf OVCUAPI   cudaVF_powexp( fVector Y, fVector X, ui size, float expo );
overror_t  __vcuf OVCUAPI   cudaVFx_powexp( fVector Y, fVector X, ui size, float expo, float A, float B, float C );

overror_t  __vcuf OVCUAPI   cudaVF_erf(     fVector Y, fVector X, ui size );
overror_t  __vcuf OVCUAPI   cudaVFx_erf(    fVector Y, fVector X, ui size, float A, float B, float C );
overror_t  __vcuf OVCUAPI   cudaVF_erfc(    fVector Y, fVector X, ui size );
overror_t  __vcuf OVCUAPI   cudaVFx_erfc(   fVector Y, fVector X, ui size, float A, float B, float C );
overror_t  __vcuf OVCUAPI   cudaVF_Gauss(   fVector Y, fVector X, ui size, float Wid, float Cent, float C );
#define cudaVF_gauss cudaVF_Gauss
overror_t  __vcuf OVCUAPI   cudaVF_Lorentz( fVector Y, fVector X, ui size, float Wid, float Cent, float C );
#define cudaVF_lorentz cudaVF_Lorentz

void  __vcuf OVCUAPI   cusdVF_setODThresh( float *d_minX, float *d_minX0 );
overror_t  __vcuf OVCUAPI   cusdVFx_pow(   fVector Y, fVector X, ui size, float expo, float *d_A, float *d_B, float *d_C );
overror_t  __vcuf OVCUAPI   cusdVFx_pow2(  fVector Y, fVector X, ui size, float *d_A, float *d_B, float *d_C );
overror_t  __vcuf OVCUAPI   cusdVFx_pow10( fVector Y, fVector X, ui size, float *d_A, float *d_B, float *d_C );
overror_t  __vcuf OVCUAPI   cusdVFx_sqrt( fVector Y, fVector X, ui size, float *d_A, float *d_B, float *d_C );
overror_t  __vcuf OVCUAPI   cusdVFx_exp(  fVector Y, fVector X, ui size, float *d_A, float *d_B, float *d_C );
overror_t  __vcuf OVCUAPI   cusdVFx_expArbBase( fVector Y, fVector X, ui size, float Base, float *d_A, float *d_B, float *d_C );
overror_t  __vcuf OVCUAPI   cusdVFx_expc( fVector Y, fVector X, ui size, float *d_A, float *d_B, float *d_C );
overror_t  __vcuf OVCUAPI   cusdVFx_expmx2( fVector Y, fVector X, ui size, float *d_A, float *d_B, float *d_C );
#define cusdVFx_exp2  cusdVFx_pow2;
#define cusdVFx_exp10  cusdVFx_pow10;
overror_t  __vcuf OVCUAPI   cusdVFx_powexp( fVector Y, fVector X, ui size, float expo, float *d_A, float *d_B, float *d_C );
overror_t  __vcuf OVCUAPI   cusdVFx_erf(    fVector Y, fVector X, ui size, float *d_A, float *d_B, float *d_C );
overror_t  __vcuf OVCUAPI   cusdVFx_erfc(   fVector Y, fVector X, ui size, float *d_A, float *d_B, float *d_C );
overror_t  __vcuf OVCUAPI   cusdVF_Gauss(   fVector Y, fVector X, ui size, float *d_Wid, float *d_Cent, float *d_C );
#define cusdVF_gauss cusdVF_Gauss
overror_t  __vcuf OVCUAPI   cusdVF_Lorentz( fVector Y, fVector X, ui size, float *d_Wid, float *d_Cent, float *d_C );
#define cusdVF_lorentz cusdVF_Lorentz

overror_t  __vcuf OVCUAPI   cudaVF_sin(     fVector Y, fVector X, ui size );
overror_t  __vcuf OVCUAPI   cudaVFx_sin(    fVector Y, fVector X, ui size, float A, float B, float C );
overror_t  __vcuf OVCUAPI   cudaVF_cos(     fVector Y, fVector X, ui size );
overror_t  __vcuf OVCUAPI   cudaVFx_cos(    fVector Y, fVector X, ui size, float A, float B, float C );
overror_t  __vcuf OVCUAPI   cudaVF_sincos(  fVector Sin, fVector Cos, fVector X, ui size );
overror_t  __vcuf OVCUAPI   cudaVFx_sincos( fVector Sin, fVector Cos, fVector X, ui size, float A, float B, float C );

overror_t  __vcuf OVCUAPI   cudaVF_tan(     fVector Y, fVector X, ui size );
overror_t  __vcuf OVCUAPI   cudaVFx_tan(    fVector Y, fVector X, ui size, float A, float B, float C );
overror_t  __vcuf OVCUAPI   cudaVF_cot(     fVector Y, fVector X, ui size );
overror_t  __vcuf OVCUAPI   cudaVFx_cot(    fVector Y, fVector X, ui size, float A, float B, float C );

overror_t  __vcuf OVCUAPI   cudaVF_sec(     fVector Y, fVector X, ui size );
overror_t  __vcuf OVCUAPI   cudaVFx_sec(    fVector Y, fVector X, ui size, float A, float B, float C );
overror_t  __vcuf OVCUAPI   cudaVF_cosec(   fVector Y, fVector X, ui size );
overror_t  __vcuf OVCUAPI   cudaVFx_cosec(  fVector Y, fVector X, ui size, float A, float B, float C );

overror_t  __vcuf OVCUAPI   cudaVF_sin2(    fVector Y, fVector X, ui size );
overror_t  __vcuf OVCUAPI   cudaVFx_sin2(   fVector Y, fVector X, ui size, float A, float B, float C );
overror_t  __vcuf OVCUAPI   cudaVF_cos2(    fVector Y, fVector X, ui size );
overror_t  __vcuf OVCUAPI   cudaVFx_cos2(   fVector Y, fVector X, ui size, float A, float B, float C );
overror_t  __vcuf OVCUAPI   cudaVF_sincos2( fVector Sin, fVector Cos, fVector X, ui size );
overror_t  __vcuf OVCUAPI   cudaVFx_sincos2( fVector Sin, fVector Cos, fVector X, ui size, float A, float B, float C );

overror_t  __vcuf OVCUAPI   cudaVF_tan2(     fVector Y, fVector X, ui size );
overror_t  __vcuf OVCUAPI   cudaVFx_tan2(    fVector Y, fVector X, ui size, float A, float B, float C );
overror_t  __vcuf OVCUAPI   cudaVF_cot2(     fVector Y, fVector X, ui size );
overror_t  __vcuf OVCUAPI   cudaVFx_cot2(    fVector Y, fVector X, ui size, float A, float B, float C );
overror_t  __vcuf OVCUAPI   cudaVF_sec2(     fVector Y, fVector X, ui size );
overror_t  __vcuf OVCUAPI   cudaVFx_sec2(    fVector Y, fVector X, ui size, float A, float B, float C );
overror_t  __vcuf OVCUAPI   cudaVF_cosec2(   fVector Y, fVector X, ui size );
overror_t  __vcuf OVCUAPI   cudaVFx_cosec2(  fVector Y, fVector X, ui size, float A, float B, float C );

 /*  reduced-range sine and cosine for -2Pi <= x <= +2Pi */
/*
overror_t  __vcuf OVCUAPI   cudaVFr_sin(     fVector Y, fVector X, ui size );
overror_t  __vcuf OVCUAPI   cudaVFrx_sin(    fVector Y, fVector X, ui size, float A, float B, float C );
overror_t  __vcuf OVCUAPI   cudaVFr_cos(     fVector Y, fVector X, ui size );
overror_t  __vcuf OVCUAPI   cudaVFrx_cos(    fVector Y, fVector X, ui size, float A, float B, float C );
overror_t  __vcuf OVCUAPI   cudaVFr_sincos(  fVector YSin, fVector YCos, fVector X, ui size );
overror_t  __vcuf OVCUAPI   cudaVFrx_sincos( fVector YSin, fVector YCos, fVector X, ui size, float A, float B, float C );
overror_t  __vcuf OVCUAPI   cudaVFr_sin2(     fVector Y, fVector X, ui size );
overror_t  __vcuf OVCUAPI   cudaVFrx_sin2(    fVector Y, fVector X, ui size, float A, float B, float C );
overror_t  __vcuf OVCUAPI   cudaVFr_cos2(     fVector Y, fVector X, ui size );
overror_t  __vcuf OVCUAPI   cudaVFrx_cos2(    fVector Y, fVector X, ui size, float A, float B, float C );
overror_t  __vcuf OVCUAPI   cudaVFr_sincos2(  fVector YSin, fVector YCos, fVector X, ui size );
overror_t  __vcuf OVCUAPI   cudaVFrx_sincos2( fVector YSin, fVector YCos, fVector X, ui size, float A, float B, float C );
*/

/* trigonometric functions of rational multiples of Pi: x = p/q * Pi */
overror_t  __vcuf OVCUAPI   cudaVF_sinrpi(   fVector Y, iVector P, ui size, int q );
overror_t  __vcuf OVCUAPI   cudaVF_cosrpi(   fVector Y, iVector P, ui size, int q );
overror_t  __vcuf OVCUAPI   cudaVF_sincosrpi( fVector YSin, fVector YCos, iVector P, ui size, int q );
overror_t  __vcuf OVCUAPI   cudaVF_tanrpi(   fVector Y, iVector P, ui size, int q );
overror_t  __vcuf OVCUAPI   cudaVF_cotrpi(   fVector Y, iVector P, ui size, int q );
overror_t  __vcuf OVCUAPI   cudaVF_secrpi(   fVector Y, iVector P, ui size, int q );
overror_t  __vcuf OVCUAPI   cudaVF_cosecrpi( fVector Y, iVector P, ui size, int q );

overror_t  __vcuf OVCUAPI   cudaVF_sinrpi2(  fVector Y, iVector P, ui size, int q );
overror_t  __vcuf OVCUAPI   cudaVF_cosrpi2(  fVector Y, iVector P, ui size, int q );
overror_t  __vcuf OVCUAPI   cudaVF_sincosrpi2( fVector YSin, fVector YCos, iVector P, ui size, int q );
overror_t  __vcuf OVCUAPI   cudaVF_tanrpi2(  fVector Y, iVector P, ui size, int q );
overror_t  __vcuf OVCUAPI   cudaVF_cotrpi2(  fVector Y, iVector P, ui size, int q );
overror_t  __vcuf OVCUAPI   cudaVF_secrpi2(  fVector Y, iVector P, ui size, int q );
overror_t  __vcuf OVCUAPI   cudaVF_cosecrpi2( fVector Y, iVector P, ui size, int q );

overror_t  __vcuf OVCUAPI   cudaVF_sinrpi3(  fVector Y, iVector P, ui size, int q );
overror_t  __vcuf OVCUAPI   cudaVF_cosrpi3(  fVector Y, iVector P, ui size, int q );
overror_t  __vcuf OVCUAPI   cudaVF_sincosrpi3( fVector YSin, fVector YCos, iVector P, ui size, int q );
overror_t  __vcuf OVCUAPI   cudaVF_tanrpi3(  fVector Y, iVector P, ui size, int q );
overror_t  __vcuf OVCUAPI   cudaVF_cotrpi3(  fVector Y, iVector P, ui size, int q );
overror_t  __vcuf OVCUAPI   cudaVF_secrpi3(  fVector Y, iVector P, ui size, int q );
overror_t  __vcuf OVCUAPI   cudaVF_cosecrpi3( fVector Y, iVector P, ui size, int q );


overror_t  __vcuf OVCUAPI   cudaVF_sinc(     fVector Y, fVector X, ui size );
overror_t  __vcuf OVCUAPI   cudaVFx_sinc(    fVector Y, fVector X, ui size, float A, float B, float C );
overror_t  __vcuf OVCUAPI   cudaVF_Kepler(   fVector Y, fVector X, ui size, float T, float e );
overror_t  __vcuf OVCUAPI   cudaVFx_Kepler(  fVector Y, fVector X, ui size, float T, float e, float A, float B );
#define cudaVF_kepler  cudaVF_Kepler
#define cudaVFx_kepler cudaVFx_Kepler

overror_t  __vcuf OVCUAPI   cudaVF_asin(    fVector Y, fVector X, ui size );
overror_t  __vcuf OVCUAPI   cudaVFx_asin(   fVector Y, fVector X, ui size, float A, float B, float C );
overror_t  __vcuf OVCUAPI   cudaVF_acos(    fVector Y, fVector X, ui size );
overror_t  __vcuf OVCUAPI   cudaVFx_acos(   fVector Y, fVector X, ui size, float A, float B, float C );
overror_t  __vcuf OVCUAPI   cudaVF_atan(    fVector Y, fVector X, ui size );
overror_t  __vcuf OVCUAPI   cudaVFx_atan(   fVector Y, fVector X, ui size, float A, float B, float C );
overror_t  __vcuf OVCUAPI   cudaVF_atan2(   fVector Z, fVector X, fVector Y, ui size );
overror_t  __vcuf OVCUAPI   cudaVFx_atan2(  fVector Z, fVector X, fVector Y, ui size, float A, float B, float C );

overror_t  __vcuf OVCUAPI   cudaVF_sinh(    fVector Y, fVector X, ui size );
overror_t  __vcuf OVCUAPI   cudaVFx_sinh(   fVector Y, fVector X, ui size, float A, float B, float C );
overror_t  __vcuf OVCUAPI   cudaVF_cosh(    fVector Y, fVector X, ui size );
overror_t  __vcuf OVCUAPI   cudaVFx_cosh(   fVector Y, fVector X, ui size, float A, float B, float C );
overror_t  __vcuf OVCUAPI   cudaVF_tanh(    fVector Y, fVector X, ui size );
overror_t  __vcuf OVCUAPI   cudaVFx_tanh(   fVector Y, fVector X, ui size, float A, float B, float C );
overror_t  __vcuf OVCUAPI   cudaVF_coth(    fVector Y, fVector X, ui size );
overror_t  __vcuf OVCUAPI   cudaVFx_coth(   fVector Y, fVector X, ui size, float A, float B, float C );
overror_t  __vcuf OVCUAPI   cudaVF_sech(    fVector Y, fVector X, ui size );
overror_t  __vcuf OVCUAPI   cudaVFx_sech(   fVector Y, fVector X, ui size, float A, float B, float C );
overror_t  __vcuf OVCUAPI   cudaVF_cosech(  fVector Y, fVector X, ui size );
overror_t  __vcuf OVCUAPI   cudaVFx_cosech( fVector Y, fVector X, ui size, float A, float B, float C );
overror_t  __vcuf OVCUAPI   cudaVF_sech2(   fVector Y, fVector X, ui size );
overror_t  __vcuf OVCUAPI   cudaVFx_sech2(  fVector Y, fVector X, ui size, float A, float B, float C );
overror_t  __vcuf OVCUAPI   cudaVF_Langevin( fVector Y, fVector X, ui size ); /* coth(x)-1/x */
overror_t  __vcuf OVCUAPI   cudaVFx_Langevin(fVector Y, fVector X, ui size, float A, float B, float C );
#define cudaVF_langevin  cudaVF_Langevin
#define cudaVFx_langevin cudaVFx_Langevin


overror_t  __vcuf OVCUAPI   cusdVFx_sin(    fVector Y, fVector X, ui size, float *d_A, float *d_B, float *d_C );
overror_t  __vcuf OVCUAPI   cusdVFx_cos(    fVector Y, fVector X, ui size, float *d_A, float *d_B, float *d_C );
overror_t  __vcuf OVCUAPI   cusdVFx_sincos( fVector Sin, fVector Cos, fVector X, ui size, float *d_A, float *d_B, float *d_C );
overror_t  __vcuf OVCUAPI   cusdVFx_tan(    fVector Y, fVector X, ui size, float *d_A, float *d_B, float *d_C );
overror_t  __vcuf OVCUAPI   cusdVFx_cot(    fVector Y, fVector X, ui size, float *d_A, float *d_B, float *d_C );
overror_t  __vcuf OVCUAPI   cusdVFx_sec(    fVector Y, fVector X, ui size, float *d_A, float *d_B, float *d_C );
overror_t  __vcuf OVCUAPI   cusdVFx_cosec(  fVector Y, fVector X, ui size, float *d_A, float *d_B, float *d_C );
overror_t  __vcuf OVCUAPI   cusdVFx_sin2(   fVector Y, fVector X, ui size, float *d_A, float *d_B, float *d_C );
overror_t  __vcuf OVCUAPI   cusdVFx_cos2(   fVector Y, fVector X, ui size, float *d_A, float *d_B, float *d_C );
overror_t  __vcuf OVCUAPI   cusdVFx_sincos2( fVector Sin, fVector Cos, fVector X, ui size, float *d_A, float *d_B, float *d_C );
overror_t  __vcuf OVCUAPI   cusdVFx_tan2(    fVector Y, fVector X, ui size, float *d_A, float *d_B, float *d_C );
overror_t  __vcuf OVCUAPI   cusdVFx_cot2(    fVector Y, fVector X, ui size, float *d_A, float *d_B, float *d_C );
overror_t  __vcuf OVCUAPI   cusdVFx_sec2(    fVector Y, fVector X, ui size, float *d_A, float *d_B, float *d_C );
overror_t  __vcuf OVCUAPI   cusdVFx_cosec2(  fVector Y, fVector X, ui size, float *d_A, float *d_B, float *d_C );
overror_t  __vcuf OVCUAPI   cusdVFx_sinc(    fVector Y, fVector X, ui size, float *d_A, float *d_B, float *d_C );
overror_t  __vcuf OVCUAPI   cusdVF_Kepler(   fVector Y, fVector X, ui size, float *T, float *e );
overror_t  __vcuf OVCUAPI   cusdVFx_Kepler(  fVector Y, fVector X, ui size, float *T, float *e, float *d_A, float *d_B );
#define cusdVF_kepler  cusdVF_Kepler
#define cusdVFx_kepler cusdVFx_Kepler
overror_t  __vcuf OVCUAPI   cusdVFx_asin(   fVector Y, fVector X, ui size, float *d_A, float *d_B, float *d_C );
overror_t  __vcuf OVCUAPI   cusdVFx_acos(   fVector Y, fVector X, ui size, float *d_A, float *d_B, float *d_C );
overror_t  __vcuf OVCUAPI   cusdVFx_atan(   fVector Y, fVector X, ui size, float *d_A, float *d_B, float *d_C );
overror_t  __vcuf OVCUAPI   cusdVFx_atan2(  fVector Z, fVector X, fVector Y, ui size, float *d_A, float *d_B, float *d_C );
overror_t  __vcuf OVCUAPI   cusdVFx_sinh(   fVector Y, fVector X, ui size, float *d_A, float *d_B, float *d_C );
overror_t  __vcuf OVCUAPI   cusdVFx_cosh(   fVector Y, fVector X, ui size, float *d_A, float *d_B, float *d_C );
overror_t  __vcuf OVCUAPI   cusdVFx_tanh(   fVector Y, fVector X, ui size, float *d_A, float *d_B, float *d_C );
overror_t  __vcuf OVCUAPI   cusdVFx_coth(   fVector Y, fVector X, ui size, float *d_A, float *d_B, float *d_C );
overror_t  __vcuf OVCUAPI   cusdVFx_sech(   fVector Y, fVector X, ui size, float *d_A, float *d_B, float *d_C );
overror_t  __vcuf OVCUAPI   cusdVFx_cosech( fVector Y, fVector X, ui size, float *d_A, float *d_B, float *d_C );
overror_t  __vcuf OVCUAPI   cusdVFx_sech2(  fVector Y, fVector X, ui size, float *d_A, float *d_B, float *d_C );
overror_t  __vcuf OVCUAPI   cusdVFx_Langevin(fVector Y, fVector X, ui size, float *d_A, float *d_B, float *d_C );
#define cusdVFx_langevin cusdVFx_Langevin


#ifdef __cplusplus
}  // end of extern "C"
#endif


/******************  VFcu_ functions: **********************************
	act on host memory, using the CUDA device for processing
************************************************************************/

#ifdef __cplusplus
extern "C" {
#endif

/**************************  Rounding **********************************/

int  __vf OVCUAPI   VFcu_round(  fVector  Y, fVector X, ui size );
int  __vf OVCUAPI   VFcu_roundtoBI( biVector Y, fVector X, ui size );
int  __vf OVCUAPI   VFcu_roundtoSI( siVector Y, fVector X, ui size );
int  __vf OVCUAPI   VFcu_roundtoI(  iVector  Y, fVector X, ui size );
int  __vf OVCUAPI   VFcu_roundtoLI( liVector Y, fVector X, ui size );
int  __vf OVCUAPI   VFcu_roundtoQI( qiVector Y, fVector X, ui size );
int  __vf OVCUAPI   VFcu_roundtoUB( ubVector Y, fVector X, ui size );
int  __vf OVCUAPI   VFcu_roundtoUS( usVector Y, fVector X, ui size );
int  __vf OVCUAPI   VFcu_roundtoU(  uVector  Y, fVector X, ui size );
int  __vf OVCUAPI   VFcu_roundtoUL( ulVector Y, fVector X, ui size );
#ifdef _WIN64
    int  __vf OVCUAPI   VFcu_roundtoUQ( uqVector Y, fVector X, ui size );
#endif

int  __vf OVCUAPI   VFcu_floor(  fVector  Y, fVector X, ui size );
int  __vf OVCUAPI   VFcu_floortoBI( biVector Y, fVector X, ui size );
int  __vf OVCUAPI   VFcu_floortoSI( siVector Y, fVector X, ui size );
int  __vf OVCUAPI   VFcu_floortoI(  iVector  Y, fVector X, ui size );
int  __vf OVCUAPI   VFcu_floortoLI( liVector Y, fVector X, ui size );
int  __vf OVCUAPI   VFcu_floortoQI( qiVector Y, fVector X, ui size );
int  __vf OVCUAPI   VFcu_floortoUB( ubVector Y, fVector X, ui size );
int  __vf OVCUAPI   VFcu_floortoUS( usVector Y, fVector X, ui size );
int  __vf OVCUAPI   VFcu_floortoU(  uVector  Y, fVector X, ui size );
int  __vf OVCUAPI   VFcu_floortoUL( ulVector Y, fVector X, ui size );
#ifdef _WIN64
    int  __vf OVCUAPI   VFcu_floortoUQ( uqVector Y, fVector X, ui size );
#endif

int  __vf OVCUAPI   VFcu_ceil(  fVector  Y, fVector X, ui size );
int  __vf OVCUAPI   VFcu_ceiltoBI( biVector Y, fVector X, ui size );
int  __vf OVCUAPI   VFcu_ceiltoSI( siVector Y, fVector X, ui size );
int  __vf OVCUAPI   VFcu_ceiltoI(  iVector  Y, fVector X, ui size );
int  __vf OVCUAPI   VFcu_ceiltoLI( liVector Y, fVector X, ui size );
int  __vf OVCUAPI   VFcu_ceiltoQI( qiVector Y, fVector X, ui size );
int  __vf OVCUAPI   VFcu_ceiltoUB( ubVector Y, fVector X, ui size );
int  __vf OVCUAPI   VFcu_ceiltoUS( usVector Y, fVector X, ui size );
int  __vf OVCUAPI   VFcu_ceiltoU(  uVector  Y, fVector X, ui size );
int  __vf OVCUAPI   VFcu_ceiltoUL( ulVector Y, fVector X, ui size );
#ifdef _WIN64
    int  __vf OVCUAPI   VFcu_ceiltoUQ( uqVector Y, fVector X, ui size );
#endif

int  __vf OVCUAPI   VFcu_chop(  fVector  Y, fVector X, ui size );
int  __vf OVCUAPI   VFcu_choptoBI( biVector Y, fVector X, ui size );
int  __vf OVCUAPI   VFcu_choptoSI( siVector Y, fVector X, ui size );
int  __vf OVCUAPI   VFcu_choptoI(  iVector  Y, fVector X, ui size );
int  __vf OVCUAPI   VFcu_choptoLI( liVector Y, fVector X, ui size );
int  __vf OVCUAPI   VFcu_choptoQI( qiVector Y, fVector X, ui size );
int  __vf OVCUAPI   VFcu_choptoUB( ubVector Y, fVector X, ui size );
int  __vf OVCUAPI   VFcu_choptoUS( usVector Y, fVector X, ui size );
int  __vf OVCUAPI   VFcu_choptoU(  uVector  Y, fVector X, ui size );
int  __vf OVCUAPI   VFcu_choptoUL( ulVector Y, fVector X, ui size );
#ifdef _WIN64
    int  __vf OVCUAPI   VFcu_choptoUQ( uqVector Y, fVector X, ui size );
#endif

#define VFcu_trunc      VFcu_chop
#define VFcu_trunctoBI  VFcu_choptoBI
#define VFcu_trunctoSI  VFcu_choptoSI
#define VFcu_trunctoI   VFcu_choptoI
#define VFcu_trunctoLI  VFcu_choptoLI
#define VFcu_trunctoQI  VFcu_choptoQI
#define VFcu_trunctoUB  VFcu_choptoUB
#define VFcu_trunctoUS  VFcu_choptoUS
#define VFcu_trunctoU   VFcu_choptoU
#define VFcu_trunctoUL  VFcu_choptoUL
#define VFcu_trunctoUQ  VFcu_choptoUQ

#if defined _WIN64
      #define   VFcu_roundtoUI    VFcu_roundtoUQ
      #define   VFcu_floortoUI    VFcu_floortoUQ
      #define   VFcu_ceiltoUI     VFcu_ceiltoUQ
      #define   VFcu_choptoUI     VFcu_choptoUQ
      #define   VFcu_trunctoUI    VFcu_trunctoUQ
#else
      #define   VFcu_roundtoUI    VFcu_roundtoU
      #define   VFcu_floortoUI    VFcu_floortoU
      #define   VFcu_ceiltoUI     VFcu_ceiltoU
      #define   VFcu_choptoUI     VFcu_choptoU
      #define   VFcu_trunctoUI    VFcu_trunctoU
#endif

/********************  Comparisons ********************************/

void __vf OVCUAPI   VFcu_cmp0(    fVector Y, fVector X, ui size );
ui   __vf OVCUAPI   VFcu_cmp_eq0( fVector Y, fVector X, ui size );
ui   __vf OVCUAPI   VFcu_cmp_ne0( fVector Y, fVector X, ui size );
ui   __vf OVCUAPI   VFcu_cmp_le0( fVector Y, fVector X, ui size );
ui   __vf OVCUAPI   VFcu_cmp_lt0( fVector Y, fVector X, ui size );
ui   __vf OVCUAPI   VFcu_cmp_ge0( fVector Y, fVector X, ui size );
ui   __vf OVCUAPI   VFcu_cmp_gt0( fVector Y, fVector X, ui size );

ui   __vf OVCUAPI   VFcu_cnt_eq0( fVector X, ui size );
ui   __vf OVCUAPI   VFcu_cnt_ne0( fVector X, ui size );
ui   __vf OVCUAPI   VFcu_cnt_le0( fVector X, ui size );
ui   __vf OVCUAPI   VFcu_cnt_lt0( fVector X, ui size );
ui   __vf OVCUAPI   VFcu_cnt_ge0( fVector X, ui size );
ui   __vf OVCUAPI   VFcu_cnt_gt0( fVector X, ui size );

/*
ui   __vf OVCUAPI   VFcu_cmp_eq0ind( uiVector Ind, fVector X, ui size );
ui   __vf OVCUAPI   VFcu_cmp_ne0ind( uiVector Ind, fVector X, ui size );
ui   __vf OVCUAPI   VFcu_cmp_le0ind( uiVector Ind, fVector X, ui size );
ui   __vf OVCUAPI   VFcu_cmp_lt0ind( uiVector Ind, fVector X, ui size );
ui   __vf OVCUAPI   VFcu_cmp_ge0ind( uiVector Ind, fVector X, ui size );
ui   __vf OVCUAPI   VFcu_cmp_gt0ind( uiVector Ind, fVector X, ui size );
*/

void __vf OVCUAPI   VFcu_cmpC(    fVector Y, fVector X, ui size, float C );
ui   __vf OVCUAPI   VFcu_cmp_eqC( fVector Y, fVector X, ui size, float C );
ui   __vf OVCUAPI   VFcu_cmp_neC( fVector Y, fVector X, ui size, float C );
ui   __vf OVCUAPI   VFcu_cmp_leC( fVector Y, fVector X, ui size, float C );
ui   __vf OVCUAPI   VFcu_cmp_ltC( fVector Y, fVector X, ui size, float C );
ui   __vf OVCUAPI   VFcu_cmp_geC( fVector Y, fVector X, ui size, float C );
ui   __vf OVCUAPI   VFcu_cmp_gtC( fVector Y, fVector X, ui size, float C );

ui   __vf OVCUAPI   VFcu_cnt_eqC( fVector X, ui size, float C );
ui   __vf OVCUAPI   VFcu_cnt_neC( fVector X, ui size, float C );
ui   __vf OVCUAPI   VFcu_cnt_leC( fVector X, ui size, float C );
ui   __vf OVCUAPI   VFcu_cnt_ltC( fVector X, ui size, float C );
ui   __vf OVCUAPI   VFcu_cnt_geC( fVector X, ui size, float C );
ui   __vf OVCUAPI   VFcu_cnt_gtC( fVector X, ui size, float C );

/*
ui   __vf OVCUAPI   VFcu_cmp_eqCind( uiVector Ind, fVector X, ui size, float C );
ui   __vf OVCUAPI   VFcu_cmp_neCind( uiVector Ind, fVector X, ui size, float C );
ui   __vf OVCUAPI   VFcu_cmp_leCind( uiVector Ind, fVector X, ui size, float C );
ui   __vf OVCUAPI   VFcu_cmp_ltCind( uiVector Ind, fVector X, ui size, float C );
ui   __vf OVCUAPI   VFcu_cmp_geCind( uiVector Ind, fVector X, ui size, float C );
ui   __vf OVCUAPI   VFcu_cmp_gtCind( uiVector Ind, fVector X, ui size, float C );
*/
void __vf OVCUAPI   VFcu_cmpV(    fVector Z, fVector X, fVector Y, ui size );
ui   __vf OVCUAPI   VFcu_cmp_eqV( fVector Z, fVector X, fVector Y, ui size );
ui   __vf OVCUAPI   VFcu_cmp_neV( fVector Z, fVector X, fVector Y, ui size );
ui   __vf OVCUAPI   VFcu_cmp_leV( fVector Z, fVector X, fVector Y, ui size );
ui   __vf OVCUAPI   VFcu_cmp_ltV( fVector Z, fVector X, fVector Y, ui size );
ui   __vf OVCUAPI   VFcu_cmp_geV( fVector Z, fVector X, fVector Y, ui size );
ui   __vf OVCUAPI   VFcu_cmp_gtV( fVector Z, fVector X, fVector Y, ui size );

ui   __vf OVCUAPI   VFcu_cnt_eqV( fVector X, fVector Y, ui size );
ui   __vf OVCUAPI   VFcu_cnt_neV( fVector X, fVector Y, ui size );
ui   __vf OVCUAPI   VFcu_cnt_leV( fVector X, fVector Y, ui size );
ui   __vf OVCUAPI   VFcu_cnt_ltV( fVector X, fVector Y, ui size );
ui   __vf OVCUAPI   VFcu_cnt_geV( fVector X, fVector Y, ui size );
ui   __vf OVCUAPI   VFcu_cnt_gtV( fVector X, fVector Y, ui size );

/*
ui   __vf OVCUAPI   VFcu_cmp_eqVind( uiVector Ind, fVector X, fVector Y, ui size );
ui   __vf OVCUAPI   VFcu_cmp_neVind( uiVector Ind, fVector X, fVector Y, ui size );
ui   __vf OVCUAPI   VFcu_cmp_leVind( uiVector Ind, fVector X, fVector Y, ui size );
ui   __vf OVCUAPI   VFcu_cmp_ltVind( uiVector Ind, fVector X, fVector Y, ui size );
ui   __vf OVCUAPI   VFcu_cmp_geVind( uiVector Ind, fVector X, fVector Y, ui size );
ui   __vf OVCUAPI   VFcu_cmp_gtVind( uiVector Ind, fVector X, fVector Y, ui size );
*/
ui   __vf OVCUAPI   VFcu_cmp_inclrange0C( fVector Y, fVector X, ui size, float C );
ui   __vf OVCUAPI   VFcu_cmp_exclrange0C( fVector Y, fVector X, ui size, float C );
ui   __vf OVCUAPI   VFcu_cmp_inclrangeCC( fVector Y, fVector X, ui size, float CLo, float CHi );
ui   __vf OVCUAPI   VFcu_cmp_exclrangeCC( fVector Y, fVector X, ui size, float CLo, float CHi );

ui   __vf OVCUAPI   VFcu_cnt_inclrange0C( fVector X, ui size, float C );
ui   __vf OVCUAPI   VFcu_cnt_exclrange0C( fVector X, ui size, float C );
ui   __vf OVCUAPI   VFcu_cnt_inclrangeCC( fVector X, ui size, float CLo, float CHi );
ui   __vf OVCUAPI   VFcu_cnt_exclrangeCC( fVector X, ui size, float CLo, float CHi );

/*
ui   __vf OVCUAPI   VFcu_cmp_inclrange0Cind( uiVector Ind, fVector X, ui size, float C );
ui   __vf OVCUAPI   VFcu_cmp_exclrange0Cind( uiVector Ind, fVector X, ui size, float C );
ui   __vf OVCUAPI   VFcu_cmp_inclrangeCCind( uiVector Ind, fVector X, ui size, float CLo, float CHi );
ui   __vf OVCUAPI   VFcu_cmp_exclrangeCCind( uiVector Ind, fVector X, ui size, float CLo, float CHi );
*/

/********************  Standard Arithmetics   ***************************/

void  __vf OVCUAPI   VFcu_equC( fVector X, ui size, float C );
void  __vf OVCUAPI   VFcu_equV( fVector Y, fVector X, ui size );
void  __vf OVCUAPI   VFxcu_equV( fVector Y, fVector X, ui size, float A, float B );

void  __vf OVCUAPI   VFcu_addC(  fVector Y, fVector X, ui size, float C );
void  __vf OVCUAPI   VFcu_subC(  fVector Y, fVector X, ui size, float C );
void  __vf OVCUAPI   VFcu_subrC( fVector Y, fVector X, ui size, float C );
void  __vf OVCUAPI   VFcu_mulC(  fVector Y, fVector X, ui size, float C );
void  __vf OVCUAPI   VFcu_divC(  fVector Y, fVector X, ui size, float C );
void  __vf OVCUAPI   VFcu_divrC( fVector Y, fVector X, ui size, float C );
void  __vf OVCUAPI   VFxcu_divrC( fVector Y, fVector X, ui size, float A, float B, float C );

void  __vf OVCUAPI   VFcu_addV(  fVector Z, fVector X, fVector Y, ui size );
void  __vf OVCUAPI   VFcu_subV(  fVector Z, fVector X, fVector Y, ui size );
void  __vf OVCUAPI   VFcu_subrV( fVector Z, fVector X, fVector Y, ui size );
void  __vf OVCUAPI   VFcu_mulV(  fVector Z, fVector X, fVector Y, ui size );
void  __vf OVCUAPI   VFcu_divV(  fVector Z, fVector X, fVector Y, ui size );
void  __vf OVCUAPI   VFcu_divrV(  fVector Z, fVector X, fVector Y, ui size );
void  __vf OVCUAPI   VFcu_add2V(  fVector Z, fVector X, fVector Y1, fVector Y2, ui size );
void  __vf OVCUAPI   VFcu_sub2V(  fVector Z, fVector X, fVector Y1, fVector Y2, ui size );

void  __vf OVCUAPI   VFcu_CaddV( fVector Z, fVector X, fVector Y, ui siz, float C );
                              /* Z = X + C*Y  */

void  __vf OVCUAPI   VFxcu_addV(  fVector Z, fVector X, fVector Y, ui size, float A, float B );
                              /* Z = (A*X+B) + Y  */
void  __vf OVCUAPI   VFxcu_subV(  fVector Z, fVector X, fVector Y, ui size, float A, float B );
void  __vf OVCUAPI   VFxcu_subrV( fVector Z, fVector X, fVector Y, ui size, float A, float B );
void  __vf OVCUAPI   VFxcu_mulV(  fVector Z, fVector X, fVector Y, ui size, float A, float B );
void  __vf OVCUAPI   VFxcu_divV(  fVector Z, fVector X, fVector Y, ui size, float A, float B );
void  __vf OVCUAPI   VFxcu_divrV( fVector Z, fVector X, fVector Y, ui size, float A, float B );

void  __vf OVCUAPI   VFscu_addV(  fVector Z, fVector X, fVector Y, ui size, float C ); /* Z=C*(X+Y) */
void  __vf OVCUAPI   VFscu_subV(  fVector Z, fVector X, fVector Y, ui size, float C );
void  __vf OVCUAPI   VFscu_subrV( fVector Z, fVector X, fVector Y, ui size, float C );
void  __vf OVCUAPI   VFscu_mulV(  fVector Z, fVector X, fVector Y, ui size, float C );
void  __vf OVCUAPI   VFscu_divV(  fVector Z, fVector X, fVector Y, ui size, float C );
void  __vf OVCUAPI   VFscu_divrV( fVector Z, fVector X, fVector Y, ui size, float C );

void  __vf OVCUAPI   VFcu_maxC(   fVector Y, fVector X, ui size, float C );
void  __vf OVCUAPI   VFcu_minC(   fVector Y, fVector X, ui size, float C );
void  __vf OVCUAPI   VFcu_limit(  fVector Y, fVector X, ui size, float Min, float Max );
void  __vf OVCUAPI   VFcu_flush0( fVector Y, fVector X, ui size, float AbsMin );
void  __vf OVCUAPI   VFcu_flushInv( fVector Y, fVector X, ui size, float AbsMin );
void  __vf OVCUAPI   VFcu_replaceNAN( fVector Y, fVector X, ui size, float C );
void  __vf OVCUAPI   VFcu_maxV(   fVector Z, fVector X, fVector Y, ui size );
void  __vf OVCUAPI   VFcu_minV(   fVector Z, fVector X, fVector Y, ui size );
void  __vf OVCUAPI   VFcu_modC(   fVector Y, fVector X, ui size, float C );
void  __vf OVCUAPI   VFcu_modV(   fVector Z, fVector X, fVector Y, ui size );
void  __vf OVCUAPI   VFxcu_modV(  fVector Z, fVector X, fVector Y, ui size, float A, float B );
#define     VFcu_fmodC    VFcu_modC
#define     VFcu_fmodV    VFcu_modV
#define     VFxcu_fmodV   VFxcu_modV

void __vf OVCUAPI   VFcu_redC(  fVector Y, fVector X, ui size, float C );
void __vf OVCUAPI   VFcu_redV(  fVector Z, fVector X, fVector Y, ui size );
void __vf OVCUAPI   VFxcu_redV( fVector Z, fVector X, fVector Y, ui size, float A, float B );
void __vf OVCUAPI   VFcu_visC(  fVector Y, fVector X, ui size, float C );
void __vf OVCUAPI   VFcu_visV(  fVector Z, fVector X, fVector Y, ui size );
void __vf OVCUAPI   VFxcu_visV( fVector Z, fVector X, fVector Y, ui size, float A, float B );
void __vf OVCUAPI   VFcu_hypC(  fVector Y, fVector X, ui size, float C );
void __vf OVCUAPI   VFcu_hypV(  fVector Z, fVector X, fVector Y, ui size );
void __vf OVCUAPI   VFxcu_hypV( fVector Z, fVector X, fVector Y, ui size, float A, float B );

void __vf OVCUAPI  VFcu_lincomb( fVector Z, fVector X, fVector Y, ui size,
                      float CX, float CY );  /* Z=CX*X+CY*Y */

void __vf OVCUAPI  VFcu_rotateCoordinates( fVector Xnew, fVector Ynew, fVector Xold, fVector Yold,
                      ui size, float costheta, float sintheta );
#define VFcu_sgn    VFcu_cmp0

/******************* Mixed-type arithmetic Functions **********************/

void  __vf OVCUAPI   VFcu_addVBI(  fVector Z, fVector X, biVector Y, ui size );
void  __vf OVCUAPI   VFcu_subVBI(  fVector Z, fVector X, biVector Y, ui size );
void  __vf OVCUAPI   VFcu_subrVBI( fVector Z, fVector X, biVector Y, ui size );
void  __vf OVCUAPI   VFcu_mulVBI(  fVector Z, fVector X, biVector Y, ui size );
void  __vf OVCUAPI   VFcu_divVBI(  fVector Z, fVector X, biVector Y, ui size );
void  __vf OVCUAPI   VFcu_divrVBI( fVector Z, fVector X, biVector Y, ui size );
void  __vf OVCUAPI   VFcu_addVSI(  fVector Z, fVector X, siVector Y, ui size );
void  __vf OVCUAPI   VFcu_subVSI(  fVector Z, fVector X, siVector Y, ui size );
void  __vf OVCUAPI   VFcu_subrVSI( fVector Z, fVector X, siVector Y, ui size );
void  __vf OVCUAPI   VFcu_mulVSI(  fVector Z, fVector X, siVector Y, ui size );
void  __vf OVCUAPI   VFcu_divVSI(  fVector Z, fVector X, siVector Y, ui size );
void  __vf OVCUAPI   VFcu_divrVSI( fVector Z, fVector X, siVector Y, ui size );
void  __vf OVCUAPI   VFcu_addVI(  fVector Z, fVector X, iVector Y, ui size );
void  __vf OVCUAPI   VFcu_subVI(  fVector Z, fVector X, iVector Y, ui size );
void  __vf OVCUAPI   VFcu_subrVI( fVector Z, fVector X, iVector Y, ui size );
void  __vf OVCUAPI   VFcu_mulVI(  fVector Z, fVector X, iVector Y, ui size );
void  __vf OVCUAPI   VFcu_divVI(  fVector Z, fVector X, iVector Y, ui size );
void  __vf OVCUAPI   VFcu_divrVI( fVector Z, fVector X, iVector Y, ui size );
void  __vf OVCUAPI   VFcu_addVLI(  fVector Z, fVector X, liVector Y, ui size );
void  __vf OVCUAPI   VFcu_subVLI(  fVector Z, fVector X, liVector Y, ui size );
void  __vf OVCUAPI   VFcu_subrVLI( fVector Z, fVector X, liVector Y, ui size );
void  __vf OVCUAPI   VFcu_mulVLI(  fVector Z, fVector X, liVector Y, ui size );
void  __vf OVCUAPI   VFcu_divVLI(  fVector Z, fVector X, liVector Y, ui size );
void  __vf OVCUAPI   VFcu_divrVLI( fVector Z, fVector X, liVector Y, ui size );
void  __vf OVCUAPI   VFcu_addVQI(  fVector Z, fVector X, qiVector Y, ui size );
void  __vf OVCUAPI   VFcu_subVQI(  fVector Z, fVector X, qiVector Y, ui size );
void  __vf OVCUAPI   VFcu_subrVQI( fVector Z, fVector X, qiVector Y, ui size );
void  __vf OVCUAPI   VFcu_mulVQI(  fVector Z, fVector X, qiVector Y, ui size );
void  __vf OVCUAPI   VFcu_divVQI(  fVector Z, fVector X, qiVector Y, ui size );
void  __vf OVCUAPI   VFcu_divrVQI( fVector Z, fVector X, qiVector Y, ui size );
void  __vf OVCUAPI   VFcu_addVUB(  fVector Z, fVector X, ubVector Y, ui size );
void  __vf OVCUAPI   VFcu_subVUB(  fVector Z, fVector X, ubVector Y, ui size );
void  __vf OVCUAPI   VFcu_subrVUB( fVector Z, fVector X, ubVector Y, ui size );
void  __vf OVCUAPI   VFcu_mulVUB(  fVector Z, fVector X, ubVector Y, ui size );
void  __vf OVCUAPI   VFcu_divVUB(  fVector Z, fVector X, ubVector Y, ui size );
void  __vf OVCUAPI   VFcu_divrVUB( fVector Z, fVector X, ubVector Y, ui size );
void  __vf OVCUAPI   VFcu_addVUS(  fVector Z, fVector X, usVector Y, ui size );
void  __vf OVCUAPI   VFcu_subVUS(  fVector Z, fVector X, usVector Y, ui size );
void  __vf OVCUAPI   VFcu_subrVUS( fVector Z, fVector X, usVector Y, ui size );
void  __vf OVCUAPI   VFcu_mulVUS(  fVector Z, fVector X, usVector Y, ui size );
void  __vf OVCUAPI   VFcu_divVUS(  fVector Z, fVector X, usVector Y, ui size );
void  __vf OVCUAPI   VFcu_divrVUS( fVector Z, fVector X, usVector Y, ui size );
void  __vf OVCUAPI   VFcu_addVU(   fVector Z, fVector X, uVector Y,  ui size );
void  __vf OVCUAPI   VFcu_subVU(   fVector Z, fVector X, uVector Y,  ui size );
void  __vf OVCUAPI   VFcu_subrVU(  fVector Z, fVector X, uVector Y,  ui size );
void  __vf OVCUAPI   VFcu_mulVU(   fVector Z, fVector X, uVector Y,  ui size );
void  __vf OVCUAPI   VFcu_divVU(   fVector Z, fVector X, uVector Y,  ui size );
void  __vf OVCUAPI   VFcu_divrVU(  fVector Z, fVector X, uVector Y,  ui size );
void  __vf OVCUAPI   VFcu_addVUL(  fVector Z, fVector X, ulVector Y, ui size );
void  __vf OVCUAPI   VFcu_subVUL(  fVector Z, fVector X, ulVector Y, ui size );
void  __vf OVCUAPI   VFcu_subrVUL( fVector Z, fVector X, ulVector Y, ui size );
void  __vf OVCUAPI   VFcu_mulVUL(  fVector Z, fVector X, ulVector Y, ui size );
void  __vf OVCUAPI   VFcu_divVUL(  fVector Z, fVector X, ulVector Y, ui size );
void  __vf OVCUAPI   VFcu_divrVUL( fVector Z, fVector X, ulVector Y, ui size );
#ifdef _WIN64
    void  __vf OVCUAPI   VFcu_addVUQ(  fVector Z, fVector X, uqVector Y, ui size );
    void  __vf OVCUAPI   VFcu_subVUQ(  fVector Z, fVector X, uqVector Y, ui size );
    void  __vf OVCUAPI   VFcu_subrVUQ( fVector Z, fVector X, uqVector Y, ui size );
    void  __vf OVCUAPI   VFcu_mulVUQ(  fVector Z, fVector X, uqVector Y, ui size );
    void  __vf OVCUAPI   VFcu_divVUQ(  fVector Z, fVector X, uqVector Y, ui size );
    void  __vf OVCUAPI   VFcu_divrVUQ( fVector Z, fVector X, uqVector Y, ui size );
    #define VFcu_addVUI  VFcu_addVUQ
    #define VFcu_subVUI  VFcu_subVUQ
    #define VFcu_subrVUI VFcu_subrVUQ
    #define VFcu_mulVUI  VFcu_mulVUQ
    #define VFcu_divVUI  VFcu_divVUQ
    #define VFcu_divrVUI VFcu_divrVUQ
#else
    #define VFcu_addVUI  VFcu_addVU
    #define VFcu_subVUI  VFcu_subVU
    #define VFcu_subrVUI VFcu_subrVU
    #define VFcu_mulVUI  VFcu_mulVU
    #define VFcu_divVUI  VFcu_divVU
    #define VFcu_divrVUI VFcu_divrVU
#endif

/******************** Accumulation (Y += X) ******************************/

void __vf OVCUAPI  VFcu_accV(   fVector Y, fVector  X, ui size );
void __vf OVCUAPI  VFcu_acc2V(  fVector Y, fVector  X1, fVector  X2, ui size );
void __vf OVCUAPI  VFcu_accVBI( fVector Y, biVector X, ui size );
void __vf OVCUAPI  VFcu_accVSI( fVector Y, siVector X, ui size );
void __vf OVCUAPI  VFcu_accVI(  fVector Y, iVector  X, ui size );
void __vf OVCUAPI  VFcu_accVLI( fVector Y, liVector X, ui size );
void __vf OVCUAPI  VFcu_accVQI( fVector Y, qiVector X, ui size );
void __vf OVCUAPI  VFcu_accVUB( fVector Y, ubVector X, ui size );
void __vf OVCUAPI  VFcu_accVUS( fVector Y, usVector X, ui size );
void __vf OVCUAPI  VFcu_accVU(  fVector Y, uVector  X, ui size );
void __vf OVCUAPI  VFcu_accVUL( fVector Y, ulVector X, ui size );
#if defined _WIN64
    void __vf OVCUAPI  VFcu_accVUQ( fVector Y, uqVector X, ui size );
    #define VFcu_accVUI   VFcu_accVUQ
#else
    #define VFcu_accVUI   VFcu_accVU
#endif

/***************** Functions of a sub-set of elements  ********************/

void  __vf OVCUAPI   VFcu_subvector_equC(  fVector Y, ui subsiz, ui samp, float C );
void  __vf OVCUAPI   VFcu_subvector_equV(  fVector Y, ui subsiz, ui samp, fVector X );

void  __vf OVCUAPI   VFcu_subvector_addC(  fVector Y, ui subsiz, ui samp, float C );
void  __vf OVCUAPI   VFcu_subvector_subC(  fVector Y, ui subsiz, ui samp, float C );
void  __vf OVCUAPI   VFcu_subvector_subrC( fVector Y, ui subsiz, ui samp, float C );
void  __vf OVCUAPI   VFcu_subvector_mulC(  fVector Y, ui subsiz, ui samp, float C );
void  __vf OVCUAPI   VFcu_subvector_divC(  fVector Y, ui subsiz, ui samp, float C );
void  __vf OVCUAPI   VFcu_subvector_divrC( fVector Y, ui subsiz, ui samp, float C );

void  __vf OVCUAPI   VFcu_subvector_addV(  fVector Y, ui subsiz, ui samp, fVector X );
void  __vf OVCUAPI   VFcu_subvector_subV(  fVector Y, ui subsiz, ui samp, fVector X );
void  __vf OVCUAPI   VFcu_subvector_subrV( fVector Y, ui subsiz, ui samp, fVector X );
void  __vf OVCUAPI   VFcu_subvector_mulV(  fVector Y, ui subsiz, ui samp, fVector X );
void  __vf OVCUAPI   VFcu_subvector_divV(  fVector Y, ui subsiz, ui samp, fVector X );
void  __vf OVCUAPI   VFcu_subvector_divrV( fVector Y, ui subsiz, ui samp, fVector X );


/*********************  Mathematical Functions ***********************/

int   __vf OVCUAPI   VFcu_abs( fVector Y, fVector X, ui size );
int   __vf OVCUAPI   VFcu_neg( fVector Y, fVector X, ui size );
int   __vf OVCUAPI   VFcu_inv( fVector Y, fVector X, ui size );
int   __vf OVCUAPI   VFxcu_inv( fVector Y, fVector X, ui size, float A, float B );
int   __vf OVCUAPI   VFcu_intfrac( fVector Int, fVector Frac, fVector X, ui size );
#define      VFcu_modf    VFcu_intfrac
int   __vf OVCUAPI   VFcu_mantexp( fVector Mant, iVector Exp, fVector X, ui size );
#define      VFcu_frexp   VFcu_mantexp

int  __vf OVCUAPI   VFcu_hypotC( fVector Y, fVector X, ui size, float C );
int  __vf OVCUAPI   VFcu_hypotV( fVector Z, fVector X, fVector Y, ui size );
int  __vf OVCUAPI   VFxcu_hypotV( fVector Z, fVector X, fVector Y, ui size, float A, float B );

int  __vf OVCUAPI   VFcu_scale2( fVector Y, fVector X, ui size, int expo );
int  __vf OVCUAPI   VFcu_scale10( fVector Y, fVector X, ui size, int expo );
#define       VFcu_ldexp    VFcu_scale2

int  __vf OVCUAPI   VFcu_square( fVector Y, fVector X, ui size );
int  __vf OVCUAPI   VFxcu_square( fVector Y, fVector X, ui size, float A, float B );
int  __vf OVCUAPI   VFcu_cubic( fVector Y, fVector X, ui size );
int  __vf OVCUAPI   VFxcu_cubic( fVector Y, fVector X, ui size, float A, float B );
int  __vf OVCUAPI   VFcu_quartic( fVector Y, fVector X, ui size );
int  __vf OVCUAPI   VFxcu_quartic( fVector Y, fVector X, ui size, float A, float B );
int  __vf OVCUAPI   VFcu_poly( fVector Y, fVector X, ui size, fVector d_Coeff, unsigned deg );
int  __vf OVCUAPI   VFxcu_poly( fVector Y, fVector X, ui size, fVector d_Coeff, unsigned deg, float A, float B );
int  __vf OVCUAPI   VFcu_ipow( fVector Y, fVector X, ui size, int ipow );
int  __vf OVCUAPI   VFxcu_ipow( fVector Y, fVector X, ui size, int ipow, float A, float B, float C );
                           /*  ipow = integer power of x */

	/* unprotected integer powers:  */
int  __vf OVCUAPI   VFucu_square( fVector Y, fVector X, ui size );
int  __vf OVCUAPI   VFuxcu_square( fVector Y, fVector X, ui size, float A, float B );
int  __vf OVCUAPI   VFucu_cubic( fVector Y, fVector X, ui size );
int  __vf OVCUAPI   VFuxcu_cubic( fVector Y, fVector X, ui size, float A, float B );
int  __vf OVCUAPI   VFucu_quartic( fVector Y, fVector X, ui size );
int  __vf OVCUAPI   VFuxcu_quartic( fVector Y, fVector X, ui size, float A, float B );
int  __vf OVCUAPI   VFucu_poly( fVector Y, fVector X, ui size, fVector Coeff, unsigned deg );
int  __vf OVCUAPI   VFuxcu_poly( fVector Y, fVector X, ui size, fVector Coeff, unsigned deg, float A, float B );
int  __vf OVCUAPI   VFucu_ipow( fVector Y, fVector X, ui size, int ipow );
int  __vf OVCUAPI   VFuxcu_ipow( fVector Y, fVector X, ui size, int ipow, float A, float B, float C );

int  __vf OVCUAPI   VFcu_ipow2(  fVector Y, iVector X, ui size );
int  __vf OVCUAPI   VFcu_ipow10( fVector Y, iVector X, ui size );
                          /* ipow2 and ipow10: integer powers of 2 and 10 */

int  __vf OVCUAPI   VFcu_pow(    fVector Y, fVector X, ui size, float expo );
int  __vf OVCUAPI   VFxcu_pow(   fVector Y, fVector X, ui size, float expo, float A, float B, float C );

int  __vf OVCUAPI   VFcu_pow2(   fVector Y, fVector X, ui size );
int  __vf OVCUAPI   VFxcu_pow2(  fVector Y, fVector X, ui size, float A, float B, float C );
int  __vf OVCUAPI   VFcu_pow10(  fVector Y, fVector X, ui size );
int  __vf OVCUAPI   VFxcu_pow10( fVector Y, fVector X, ui size, float A, float B, float C );
            /* pow2 and pow10: basis 2 or 10 raised to power x */

int  __vf OVCUAPI   VFcu_sqrt(  fVector Y, fVector X, ui size );
int  __vf OVCUAPI   VFxcu_sqrt( fVector Y, fVector X, ui size, float A, float B, float C );

int  __vf OVCUAPI   VFcu_log(    fVector Y, fVector X, ui size );
int  __vf OVCUAPI   VFcu_log2(   fVector Y, fVector X, ui size );
int  __vf OVCUAPI   VFcu_log10(  fVector Y, fVector X, ui size );
#define     VFcu_ln      VFcu_log
int  __vf OVCUAPI   VFxcu_log(   fVector Y, fVector X, ui size, float A, float B, float C );
int  __vf OVCUAPI   VFxcu_log2(  fVector Y, fVector X, ui size, float A, float B, float C );
int  __vf OVCUAPI   VFxcu_log10( fVector Y, fVector X, ui size, float A, float B, float C );
#define     VFxcu_ln     VFxcu_log

int  __vf OVCUAPI   VFcu_OD( fVector OD, fVector X, fVector X0, ui size );  /* OD = log10( X0/X ) */
int  __vf OVCUAPI   VFcu_ODwDark( fVector OD, fVector X, fVector XDark, fVector X0, fVector X0Dark, ui size );
void __vf OVCUAPI   VFcu_setODThresh( float minX, float minX0 );

int  __vf OVCUAPI   VFcu_exp(   fVector Y, fVector X, ui size );
int  __vf OVCUAPI   VFxcu_exp(  fVector Y, fVector X, ui size, float A, float B, float C );
int  __vf OVCUAPI   VFcu_expArbBase(  fVector Y, fVector X, ui size, float Base );
int  __vf OVCUAPI   VFxcu_expArbBase( fVector Y, fVector X, ui size, float Base,
                            float A, float B, float C );
int  __vf OVCUAPI   VFcu_expc(  fVector Y, fVector X, ui size );
int  __vf OVCUAPI   VFxcu_expc( fVector Y, fVector X, ui size, float A, float B, float C );
                /* expc(x) = 1 - exp(x)  */
int  __vf OVCUAPI   VFcu_expmx2(  fVector Y, fVector X, ui size );
int  __vf OVCUAPI   VFxcu_expmx2( fVector Y, fVector X, ui size, float A, float B, float C );
                /* expmx2(x) = exp( -x**2 )  */
#define VFcu_exp2   VFcu_pow2
#define VFxcu_exp2  VFxcu_pow2
#define VFcu_exp10   VFcu_pow10
#define VFxcu_exp10  VFxcu_pow10
int  __vf OVCUAPI   VFcu_powexp( fVector Y, fVector X, ui size, float expo );
int  __vf OVCUAPI   VFxcu_powexp( fVector Y, fVector X, ui size, float expo, float A, float B, float C );

int  __vf OVCUAPI   VFcu_erf(     fVector Y, fVector X, ui size );
int  __vf OVCUAPI   VFxcu_erf(    fVector Y, fVector X, ui size, float A, float B, float C );
int  __vf OVCUAPI   VFcu_erfc(    fVector Y, fVector X, ui size );
int  __vf OVCUAPI   VFxcu_erfc(   fVector Y, fVector X, ui size, float A, float B, float C );
int  __vf OVCUAPI   VFcu_Gauss(   fVector Y, fVector X, ui size, float Wid, float Cent, float C );
#define VFcu_gauss VFcu_Gauss
int  __vf OVCUAPI   VFcu_Lorentz( fVector Y, fVector X, ui size, float Wid, float Cent, float C );
#define VFcu_lorentz VFcu_Lorentz

int  __vf OVCUAPI   VFcu_sin(     fVector Y, fVector X, ui size );
int  __vf OVCUAPI   VFxcu_sin(    fVector Y, fVector X, ui size, float A, float B, float C );
int  __vf OVCUAPI   VFcu_cos(     fVector Y, fVector X, ui size );
int  __vf OVCUAPI   VFxcu_cos(    fVector Y, fVector X, ui size, float A, float B, float C );
int  __vf OVCUAPI   VFcu_sincos(  fVector Sin, fVector Cos, fVector X, ui size );
int  __vf OVCUAPI   VFxcu_sincos( fVector Sin, fVector Cos, fVector X, ui size, float A, float B, float C );

int  __vf OVCUAPI   VFcu_tan(     fVector Y, fVector X, ui size );
int  __vf OVCUAPI   VFxcu_tan(    fVector Y, fVector X, ui size, float A, float B, float C );
int  __vf OVCUAPI   VFcu_cot(     fVector Y, fVector X, ui size );
int  __vf OVCUAPI   VFxcu_cot(    fVector Y, fVector X, ui size, float A, float B, float C );

int  __vf OVCUAPI   VFcu_sec(     fVector Y, fVector X, ui size );
int  __vf OVCUAPI   VFxcu_sec(    fVector Y, fVector X, ui size, float A, float B, float C );
int  __vf OVCUAPI   VFcu_cosec(   fVector Y, fVector X, ui size );
int  __vf OVCUAPI   VFxcu_cosec(  fVector Y, fVector X, ui size, float A, float B, float C );

int  __vf OVCUAPI   VFcu_sin2(    fVector Y, fVector X, ui size );
int  __vf OVCUAPI   VFxcu_sin2(   fVector Y, fVector X, ui size, float A, float B, float C );
int  __vf OVCUAPI   VFcu_cos2(    fVector Y, fVector X, ui size );
int  __vf OVCUAPI   VFxcu_cos2(   fVector Y, fVector X, ui size, float A, float B, float C );
int  __vf OVCUAPI   VFcu_sincos2( fVector Sin, fVector Cos, fVector X, ui size );
int  __vf OVCUAPI   VFxcu_sincos2( fVector Sin, fVector Cos, fVector X, ui size, float A, float B, float C );

int  __vf OVCUAPI   VFcu_tan2(     fVector Y, fVector X, ui size );
int  __vf OVCUAPI   VFxcu_tan2(    fVector Y, fVector X, ui size, float A, float B, float C );
int  __vf OVCUAPI   VFcu_cot2(     fVector Y, fVector X, ui size );
int  __vf OVCUAPI   VFxcu_cot2(    fVector Y, fVector X, ui size, float A, float B, float C );
int  __vf OVCUAPI   VFcu_sec2(     fVector Y, fVector X, ui size );
int  __vf OVCUAPI   VFxcu_sec2(    fVector Y, fVector X, ui size, float A, float B, float C );
int  __vf OVCUAPI   VFcu_cosec2(   fVector Y, fVector X, ui size );
int  __vf OVCUAPI   VFxcu_cosec2(  fVector Y, fVector X, ui size, float A, float B, float C );

 /*  reduced-range sine and cosine for -2Pi <= x <= +2Pi */
/*
int  __vf OVCUAPI   VFrcu_sin(     fVector Y, fVector X, ui size );
int  __vf OVCUAPI   VFrxcu_sin(    fVector Y, fVector X, ui size, float A, float B, float C );
int  __vf OVCUAPI   VFrcu_cos(     fVector Y, fVector X, ui size );
int  __vf OVCUAPI   VFrxcu_cos(    fVector Y, fVector X, ui size, float A, float B, float C );
int  __vf OVCUAPI   VFrcu_sincos(  fVector YSin, fVector YCos, fVector X, ui size );
int  __vf OVCUAPI   VFrxcu_sincos( fVector YSin, fVector YCos, fVector X, ui size, float A, float B, float C );
int  __vf OVCUAPI   VFrcu_sin2(     fVector Y, fVector X, ui size );
int  __vf OVCUAPI   VFrxcu_sin2(    fVector Y, fVector X, ui size, float A, float B, float C );
int  __vf OVCUAPI   VFrcu_cos2(     fVector Y, fVector X, ui size );
int  __vf OVCUAPI   VFrxcu_cos2(    fVector Y, fVector X, ui size, float A, float B, float C );
int  __vf OVCUAPI   VFrcu_sincos2(  fVector YSin, fVector YCos, fVector X, ui size );
int  __vf OVCUAPI   VFrxcu_sincos2( fVector YSin, fVector YCos, fVector X, ui size, float A, float B, float C );
*/

/* trigonometric functions of rational multiples of Pi: x = p/q * Pi */
int  __vf OVCUAPI   VFcu_sinrpi(   fVector Y, iVector P, ui size, int q );
int  __vf OVCUAPI   VFcu_cosrpi(   fVector Y, iVector P, ui size, int q );
int  __vf OVCUAPI   VFcu_sincosrpi( fVector YSin, fVector YCos, iVector P, ui size, int q );
int  __vf OVCUAPI   VFcu_tanrpi(   fVector Y, iVector P, ui size, int q );
int  __vf OVCUAPI   VFcu_cotrpi(   fVector Y, iVector P, ui size, int q );
int  __vf OVCUAPI   VFcu_secrpi(   fVector Y, iVector P, ui size, int q );
int  __vf OVCUAPI   VFcu_cosecrpi( fVector Y, iVector P, ui size, int q );

int  __vf OVCUAPI   VFcu_sinrpi2(  fVector Y, iVector P, ui size, int q );
int  __vf OVCUAPI   VFcu_cosrpi2(  fVector Y, iVector P, ui size, int q );
int  __vf OVCUAPI   VFcu_sincosrpi2( fVector YSin, fVector YCos, iVector P, ui size, int q );
int  __vf OVCUAPI   VFcu_tanrpi2(  fVector Y, iVector P, ui size, int q );
int  __vf OVCUAPI   VFcu_cotrpi2(  fVector Y, iVector P, ui size, int q );
int  __vf OVCUAPI   VFcu_secrpi2(  fVector Y, iVector P, ui size, int q );
int  __vf OVCUAPI   VFcu_cosecrpi2( fVector Y, iVector P, ui size, int q );

int  __vf OVCUAPI   VFcu_sinrpi3(  fVector Y, iVector P, ui size, int q );
int  __vf OVCUAPI   VFcu_cosrpi3(  fVector Y, iVector P, ui size, int q );
int  __vf OVCUAPI   VFcu_sincosrpi3( fVector YSin, fVector YCos, iVector P, ui size, int q );
int  __vf OVCUAPI   VFcu_tanrpi3(  fVector Y, iVector P, ui size, int q );
int  __vf OVCUAPI   VFcu_cotrpi3(  fVector Y, iVector P, ui size, int q );
int  __vf OVCUAPI   VFcu_secrpi3(  fVector Y, iVector P, ui size, int q );
int  __vf OVCUAPI   VFcu_cosecrpi3( fVector Y, iVector P, ui size, int q );


int  __vf OVCUAPI   VFcu_sinc(     fVector Y, fVector X, ui size );
int  __vf OVCUAPI   VFxcu_sinc(    fVector Y, fVector X, ui size, float A, float B, float C );
int  __vf OVCUAPI   VFcu_Kepler(   fVector Y, fVector X, ui size, float T, float e );
int  __vf OVCUAPI   VFxcu_Kepler(  fVector Y, fVector X, ui size, float T, float e, float A, float B );
#define VFcu_kepler  VFcu_Kepler
#define VFxcu_kepler VFxcu_Kepler

int  __vf OVCUAPI   VFcu_asin(    fVector Y, fVector X, ui size );
int  __vf OVCUAPI   VFxcu_asin(   fVector Y, fVector X, ui size, float A, float B, float C );
int  __vf OVCUAPI   VFcu_acos(    fVector Y, fVector X, ui size );
int  __vf OVCUAPI   VFxcu_acos(   fVector Y, fVector X, ui size, float A, float B, float C );
int  __vf OVCUAPI   VFcu_atan(    fVector Y, fVector X, ui size );
int  __vf OVCUAPI   VFxcu_atan(   fVector Y, fVector X, ui size, float A, float B, float C );
int  __vf OVCUAPI   VFcu_atan2(   fVector Z, fVector X, fVector Y, ui size );
int  __vf OVCUAPI   VFxcu_atan2(  fVector Z, fVector X, fVector Y, ui size, float A, float B, float C );

int  __vf OVCUAPI   VFcu_sinh(    fVector Y, fVector X, ui size );
int  __vf OVCUAPI   VFxcu_sinh(   fVector Y, fVector X, ui size, float A, float B, float C );
int  __vf OVCUAPI   VFcu_cosh(    fVector Y, fVector X, ui size );
int  __vf OVCUAPI   VFxcu_cosh(   fVector Y, fVector X, ui size, float A, float B, float C );
int  __vf OVCUAPI   VFcu_tanh(    fVector Y, fVector X, ui size );
int  __vf OVCUAPI   VFxcu_tanh(   fVector Y, fVector X, ui size, float A, float B, float C );
int  __vf OVCUAPI   VFcu_coth(    fVector Y, fVector X, ui size );
int  __vf OVCUAPI   VFxcu_coth(   fVector Y, fVector X, ui size, float A, float B, float C );
int  __vf OVCUAPI   VFcu_sech(    fVector Y, fVector X, ui size );
int  __vf OVCUAPI   VFxcu_sech(   fVector Y, fVector X, ui size, float A, float B, float C );
int  __vf OVCUAPI   VFcu_cosech(  fVector Y, fVector X, ui size );
int  __vf OVCUAPI   VFxcu_cosech( fVector Y, fVector X, ui size, float A, float B, float C );
int  __vf OVCUAPI   VFcu_sech2(   fVector Y, fVector X, ui size );
int  __vf OVCUAPI   VFxcu_sech2(  fVector Y, fVector X, ui size, float A, float B, float C );
int  __vf OVCUAPI   VFcu_Langevin( fVector Y, fVector X, ui size ); /* coth(x)-1/x */
int  __vf OVCUAPI   VFxcu_Langevin(fVector Y, fVector X, ui size, float A, float B, float C );
#define VFcu_langevin  VFcu_Langevin
#define VFxcu_langevin VFxcu_Langevin

#ifdef __cplusplus
}  // end of extern "C"
#endif

#endif /* __cudaVFMATH_H */
