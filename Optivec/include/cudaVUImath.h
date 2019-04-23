/*  cudaVUImath.h

  vector management functions for data type "ui"
  ("unsigned index" = size_t, the data type for indexing and addressing):
  integer arithmetics and mathematics.

  Copyright (c) 1996-2017 by OptiCode - Dr. Martin Sander Software Dev.
  All Rights Reserved.
*/

#ifndef __CUDAVUIMATH_H
#define __CUDAVUIMATH_H

#if defined _WIN64
   #if !defined( __CUDAVUQMATH_H )
       #include <cudaVUQmath.h>
   #endif
   #define cudaVUI_cmp_eq0 cudaVUQ_cmp_eq0
   #define cudaVUI_cmp_ne0 cudaVUQ_cmp_ne0
   #define cudaVUI_cmp_gt0 cudaVUQ_cmp_gt0
   #define cudaVUI_cmpC    cudaVUQ_cmpC
   #define cudaVUI_cmp_eqC cudaVUQ_cmp_eqC
   #define cudaVUI_cmp_neC cudaVUQ_cmp_neC
   #define cudaVUI_cmp_gtC cudaVUQ_cmp_gtC
   #define cudaVUI_cmp_geC cudaVUQ_cmp_geC
   #define cudaVUI_cmp_leC cudaVUQ_cmp_leC
   #define cudaVUI_cmp_ltC cudaVUQ_cmp_ltC
   #define cudaVUI_cmp_exclrange0C cudaVUQ_cmp_exclrange0C
   #define cudaVUI_cmp_inclrangeCC cudaVUQ_cmp_inclrangeCC
   #define cudaVUI_cmp_exclrangeCC cudaVUQ_cmp_exclrangeCC
   #define cusdVUI_cmpC    cusdVUQ_cmpC
   #define cusdVUI_cmp_eqC cusdVUQ_cmp_eqC
   #define cusdVUI_cmp_neC cusdVUQ_cmp_neC
   #define cusdVUI_cmp_gtC cusdVUQ_cmp_gtC
   #define cusdVUI_cmp_geC cusdVUQ_cmp_geC
   #define cusdVUI_cmp_leC cusdVUQ_cmp_leC
   #define cusdVUI_cmp_ltC cusdVUQ_cmp_ltC
   #define cusdVUI_cmp_exclrange0C cusdVUQ_cmp_exclrange0C
   #define cusdVUI_cmp_inclrangeCC cusdVUQ_cmp_inclrangeCC
   #define cusdVUI_cmp_exclrangeCC cusdVUQ_cmp_exclrangeCC
   #define cudaVUI_cmpV    cudaVUQ_cmpV
   #define cudaVUI_cmp_eqV cudaVUQ_cmp_eqV
   #define cudaVUI_cmp_neV cudaVUQ_cmp_neV
   #define cudaVUI_cmp_gtV cudaVUQ_cmp_gtV
   #define cudaVUI_cmp_geV cudaVUQ_cmp_geV
   #define cudaVUI_cmp_leV cudaVUQ_cmp_leV
   #define cudaVUI_cmp_ltV cudaVUQ_cmp_ltV

   #define cudaVUI_cnt_eq0 cudaVUQ_cnt_eq0
   #define cudaVUI_cnt_ne0 cudaVUQ_cnt_ne0
   #define cudaVUI_cnt_gt0 cudaVUQ_cnt_gt0
   #define cudaVUI_cnt_eqC cudaVUQ_cnt_eqC
   #define cudaVUI_cnt_neC cudaVUQ_cnt_neC
   #define cudaVUI_cnt_gtC cudaVUQ_cnt_gtC
   #define cudaVUI_cnt_geC cudaVUQ_cnt_geC
   #define cudaVUI_cnt_leC cudaVUQ_cnt_leC
   #define cudaVUI_cnt_ltC cudaVUQ_cnt_ltC
   #define cudaVUI_cnt_exclrange0C cudaVUQ_cnt_exclrange0C
   #define cudaVUI_cnt_inclrangeCC cudaVUQ_cnt_inclrangeCC
   #define cudaVUI_cnt_exclrangeCC cudaVUQ_cnt_exclrangeCC
   #define cusdVUI_cnt_eqC cusdVUQ_cnt_eqC
   #define cusdVUI_cnt_neC cusdVUQ_cnt_neC
   #define cusdVUI_cnt_gtC cusdVUQ_cnt_gtC
   #define cusdVUI_cnt_geC cusdVUQ_cnt_geC
   #define cusdVUI_cnt_leC cusdVUQ_cnt_leC
   #define cusdVUI_cnt_ltC cusdVUQ_cnt_ltC
   #define cusdVUI_cnt_exclrange0C cusdVUQ_cnt_exclrange0C
   #define cusdVUI_cnt_inclrangeCC cusdVUQ_cnt_inclrangeCC
   #define cusdVUI_cnt_exclrangeCC cusdVUQ_cnt_exclrangeCC
   #define cudaVUI_cnt_eqV cudaVUQ_cnt_eqV
   #define cudaVUI_cnt_neV cudaVUQ_cnt_neV
   #define cudaVUI_cnt_gtV cudaVUQ_cnt_gtV
   #define cudaVUI_cnt_geV cudaVUQ_cnt_geV
   #define cudaVUI_cnt_leV cudaVUQ_cnt_leV
   #define cudaVUI_cnt_ltV cudaVUQ_cnt_ltV

   #define cudaVUI_addC    cudaVUQ_addC
   #define cudaVUI_subC    cudaVUQ_subC
   #define cudaVUI_subrC   cudaVUQ_subrC
   #define cudaVUI_mulC    cudaVUQ_mulC
   #define cudaVUIo_addC   cudaVUQ_addC
   #define cudaVUIo_subC   cudaVUQ_subC
   #define cudaVUIo_subrC  cudaVUQ_subrC
   #define cudaVUIo_mulC   cudaVUQ_mulC
   #define cudaVUI_divC    cudaVUQ_divC
   #define cudaVUI_divrC   cudaVUQ_divrC
   #define cudaVUI_modC    cudaVUQ_modC
   #define cudaVUI_maxC    cudaVUQ_maxC
   #define cudaVUI_minC    cudaVUQ_minC
   #define cudaVUI_addV    cudaVUQ_addV
   #define cudaVUI_subV    cudaVUQ_subV
   #define cudaVUI_subrV   cudaVUQ_subrV
   #define cudaVUI_mulV    cudaVUQ_mulV
   #define cudaVUIo_addV   cudaVUQ_addV
   #define cudaVUIo_subV   cudaVUQ_subV
   #define cudaVUIo_subrV  cudaVUQ_subrV
   #define cudaVUIo_mulV   cudaVUQ_mulV
   #define cudaVUI_divV    cudaVUQ_divV
   #define cudaVUI_divrV   cudaVUQ_divrV
   #define cudaVUI_modV    cudaVUQ_modV
   #define cudaVUI_maxV    cudaVUQ_maxV
   #define cudaVUI_minV    cudaVUQ_minV
   #define cudaVUI_accV    cudaVUQ_accV
   #define cudaVUI_accVUB  cudaVUQ_accVUB
   #define cudaVUI_accVUS  cudaVUQ_accVUS
   #define cudaVUI_accVU   cudaVUQ_accVU
   #define cudaVUI_shl     cudaVUQ_shl
   #define cudaVUI_shr     cudaVUQ_shr
   #define cudaVUI_and     cudaVUQ_and
   #define cudaVUI_or      cudaVUQ_or
   #define cudaVUI_xor     cudaVUQ_xor
   #define cudaVUI_not     cudaVUQ_not
   #define cudaVUI_ODtoF   cudaVUQ_ODtoF
   #define cudaVUI_ODtoD   cudaVUQ_ODtoD
   #define cudaVUI_ODtoFwDark   cudaVUQ_ODtoFwDark
   #define cudaVUI_ODtoDwDark   cudaVUQ_ODtoDwDark
   #define cudaVUI_setODThresh  cudaVUQ_setODThresh
#else
   #if !defined( __CUDAVUMATH_H )
       #include <cudaVUmath.h>
   #endif
   #define cudaVUI_cmp_eq0 cudaVU_cmp_eq0
   #define cudaVUI_cmp_ne0 cudaVU_cmp_ne0
   #define cudaVUI_cmp_gt0 cudaVU_cmp_gt0
   #define cudaVUI_cmpC    cudaVU_cmpC
   #define cudaVUI_cmp_eqC cudaVU_cmp_eqC
   #define cudaVUI_cmp_neC cudaVU_cmp_neC
   #define cudaVUI_cmp_gtC cudaVU_cmp_gtC
   #define cudaVUI_cmp_geC cudaVU_cmp_geC
   #define cudaVUI_cmp_leC cudaVU_cmp_leC
   #define cudaVUI_cmp_ltC cudaVU_cmp_ltC
   #define cudaVUI_cmp_exclrange0C cudaVU_cmp_exclrange0C
   #define cudaVUI_cmp_inclrangeCC cudaVU_cmp_inclrangeCC
   #define cudaVUI_cmp_exclrangeCC cudaVU_cmp_exclrangeCC
   #define cusdVUI_cmpC    cusdVU_cmpC
   #define cusdVUI_cmp_eqC cusdVU_cmp_eqC
   #define cusdVUI_cmp_neC cusdVU_cmp_neC
   #define cusdVUI_cmp_gtC cusdVU_cmp_gtC
   #define cusdVUI_cmp_geC cusdVU_cmp_geC
   #define cusdVUI_cmp_leC cusdVU_cmp_leC
   #define cusdVUI_cmp_ltC cusdVU_cmp_ltC
   #define cusdVUI_cmp_exclrange0C cusdVU_cmp_exclrange0C
   #define cusdVUI_cmp_inclrangeCC cusdVU_cmp_inclrangeCC
   #define cusdVUI_cmp_exclrangeCC cusdVU_cmp_exclrangeCC
   #define cudaVUI_cmpV    cudaVU_cmpV
   #define cudaVUI_cmp_eqV cudaVU_cmp_eqV
   #define cudaVUI_cmp_neV cudaVU_cmp_neV
   #define cudaVUI_cmp_gtV cudaVU_cmp_gtV
   #define cudaVUI_cmp_geV cudaVU_cmp_geV
   #define cudaVUI_cmp_leV cudaVU_cmp_leV
   #define cudaVUI_cmp_ltV cudaVU_cmp_ltV

   #define cudaVUI_cnt_eq0 cudaVU_cnt_eq0
   #define cudaVUI_cnt_ne0 cudaVU_cnt_ne0
   #define cudaVUI_cnt_gt0 cudaVU_cnt_gt0
   #define cudaVUI_cnt_eqC cudaVU_cnt_eqC
   #define cudaVUI_cnt_neC cudaVU_cnt_neC
   #define cudaVUI_cnt_gtC cudaVU_cnt_gtC
   #define cudaVUI_cnt_geC cudaVU_cnt_geC
   #define cudaVUI_cnt_leC cudaVU_cnt_leC
   #define cudaVUI_cnt_ltC cudaVU_cnt_ltC
   #define cudaVUI_cnt_exclrange0C cudaVU_cnt_exclrange0C
   #define cudaVUI_cnt_inclrangeCC cudaVU_cnt_inclrangeCC
   #define cudaVUI_cnt_exclrangeCC cudaVU_cnt_exclrangeCC
   #define cusdVUI_cnt_eqC cusdVU_cnt_eqC
   #define cusdVUI_cnt_neC cusdVU_cnt_neC
   #define cusdVUI_cnt_gtC cusdVU_cnt_gtC
   #define cusdVUI_cnt_geC cusdVU_cnt_geC
   #define cusdVUI_cnt_leC cusdVU_cnt_leC
   #define cusdVUI_cnt_ltC cusdVU_cnt_ltC
   #define cusdVUI_cnt_exclrange0C cusdVU_cnt_exclrange0C
   #define cusdVUI_cnt_inclrangeCC cusdVU_cnt_inclrangeCC
   #define cusdVUI_cnt_exclrangeCC cusdVU_cnt_exclrangeCC
   #define cudaVUI_cnt_eqV cudaVU_cnt_eqV
   #define cudaVUI_cnt_neV cudaVU_cnt_neV
   #define cudaVUI_cnt_gtV cudaVU_cnt_gtV
   #define cudaVUI_cnt_geV cudaVU_cnt_geV
   #define cudaVUI_cnt_leV cudaVU_cnt_leV
   #define cudaVUI_cnt_ltV cudaVU_cnt_ltV

   #define cudaVUI_addC    cudaVU_addC
   #define cudaVUI_subC    cudaVU_subC
   #define cudaVUI_subrC   cudaVU_subrC
   #define cudaVUI_mulC    cudaVU_mulC
   #define cudaVUIo_addC   cudaVUo_addC
   #define cudaVUIo_subC   cudaVUo_subC
   #define cudaVUIo_subrC  cudaVUo_subrC
   #define cudaVUIo_mulC   cudaVUo_mulC
   #define cudaVUI_divC    cudaVU_divC
   #define cudaVUI_divrC   cudaVU_divrC
   #define cudaVUI_modC    cudaVU_modC
   #define cudaVUI_maxC    cudaVU_maxC
   #define cudaVUI_minC    cudaVU_minC
   #define cudaVUI_addV    cudaVU_addV
   #define cudaVUI_subV    cudaVU_subV
   #define cudaVUI_subrV   cudaVU_subrV
   #define cudaVUI_mulV    cudaVU_mulV
   #define cudaVUIo_addV   cudaVUo_addV
   #define cudaVUIo_subV   cudaVUo_subV
   #define cudaVUIo_subrV  cudaVUo_subrV
   #define cudaVUIo_mulV   cudaVUo_mulV
   #define cudaVUI_divV    cudaVU_divV
   #define cudaVUI_divrV   cudaVU_divrV
   #define cudaVUI_modV    cudaVU_modV
   #define cudaVUI_maxV    cudaVU_maxV
   #define cudaVUI_minV    cudaVU_minV
   #define cudaVUI_accV    cudaVU_accV
   #define cudaVUI_accVUB  cudaVU_accVUB
   #define cudaVUI_accVUS  cudaVU_accVUS
   #define cudaVUI_accVU   cudaVU_accV
   #define cudaVUI_shl     cudaVU_shl
   #define cudaVUI_shr     cudaVU_shr
   #define cudaVUI_and     cudaVU_and
   #define cudaVUI_or      cudaVU_or
   #define cudaVUI_xor     cudaVU_xor
   #define cudaVUI_not     cudaVU_not
   #define cudaVUI_ODtoF   cudaVU_ODtoF
   #define cudaVUI_ODtoD   cudaVU_ODtoD
   #define cudaVUI_ODtoFwDark   cudaVU_ODtoFwDark
   #define cudaVUI_ODtoDwDark   cudaVU_ODtoDwDark
   #define cudaVUI_setODThresh  cudaVU_setODThresh
#endif  /* _WIN64 */
#endif  /* __VUIMATH_H */


