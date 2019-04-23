/*  VUImath.h

  vector management functions for data type "ui"
  ("unsigned index" = size_t, the data type for indexing and addressing):
  integer arithmetics and mathematics.

  Copyright (c) 1996-2017 by OptiCode - Dr. Martin Sander Software Dev.
  All Rights Reserved.
*/

#ifndef __VUIMATH_H
#define __VUIMATH_H

#if defined _WIN64
		#if !defined( __VUQMATH_H )
		 #include <VUQmath.h>
	#endif
	#define VUI_cmp_eq0		VUQ_cmp_eq0
	#define VUI_cmp_ne0		VUQ_cmp_ne0
	#define VUI_cmp_gt0		VUQ_cmp_gt0
	#define VUI_cmp_eq0ind	VUQ_cmp_eq0ind
	#define VUI_cmp_ne0ind	VUQ_cmp_ne0ind
	#define VUI_cmp_gt0ind	VUQ_cmp_gt0ind
	#define VUI_cnt_eq0		VUQ_cnt_eq0
	#define VUI_cnt_ne0		VUQ_cnt_ne0
	#define VUI_cnt_gt0		VUQ_cnt_gt0
	#define VUI_cmpC		VUQ_cmpC
	#define VUI_cmp_eqC		VUQ_cmp_eqC
	#define VUI_cmp_neC		VUQ_cmp_neC
	#define VUI_cmp_leC		VUQ_cmp_leC
	#define VUI_cmp_ltC		VUQ_cmp_ltC
	#define VUI_cmp_geC		VUQ_cmp_geC
	#define VUI_cmp_gtC		VUQ_cmp_gtC
	#define VUI_cmp_eqCind	VUQ_cmp_eqCind
	#define VUI_cmp_neCind	VUQ_cmp_neCind
	#define VUI_cmp_leCind	VUQ_cmp_leCind
	#define VUI_cmp_ltCind	VUQ_cmp_ltCind
	#define VUI_cmp_geCind	VUQ_cmp_geCind
	#define VUI_cmp_gtCind	VUQ_cmp_gtCind
	#define VUI_cnt_eqC		VUQ_cnt_eqC
	#define VUI_cnt_neC		VUQ_cnt_neC
	#define VUI_cnt_leC		VUQ_cnt_leC
	#define VUI_cnt_ltC		VUQ_cnt_ltC
	#define VUI_cnt_geC		VUQ_cnt_geC
	#define VUI_cnt_gtC		VUQ_cnt_gtC
	#define VUI_cmpV		VUQ_cmpV
	#define VUI_cmp_eqV		VUQ_cmp_eqV
	#define VUI_cmp_neV		VUQ_cmp_neV
	#define VUI_cmp_leV		VUQ_cmp_leV
	#define VUI_cmp_ltV		VUQ_cmp_ltV
	#define VUI_cmp_geV		VUQ_cmp_geV
	#define VUI_cmp_gtV		VUQ_cmp_gtV
	#define VUI_cmp_eqVind	VUQ_cmp_eqVind
	#define VUI_cmp_neVind	VUQ_cmp_neVind
	#define VUI_cmp_leVind	VUQ_cmp_leVind
	#define VUI_cmp_ltVind	VUQ_cmp_ltVind
	#define VUI_cmp_geVind	VUQ_cmp_geVind
	#define VUI_cmp_gtVind	VUQ_cmp_gtVind
	#define VUI_cnt_eqV		VUQ_cnt_eqV
	#define VUI_cnt_neV		VUQ_cnt_neV
	#define VUI_cnt_leV		VUQ_cnt_leV
	#define VUI_cnt_ltV		VUQ_cnt_ltV
	#define VUI_cnt_geV		VUQ_cnt_geV
	#define VUI_cnt_gtV		VUQ_cnt_gtV
	#define VUI_cmp_exclrange0C	 VUQ_cmp_exclrange0C
	#define VUI_cmp_inclrangeCC	 VUQ_cmp_inclrangeCC
	#define VUI_cmp_exclrangeCC	 VUQ_cmp_exclrangeCC
	#define VUI_cmp_exclrange0Cind VUQ_cmp_exclrange0Cind
	#define VUI_cmp_inclrangeCCind VUQ_cmp_inclrangeCCind
	#define VUI_cmp_exclrangeCCind VUQ_cmp_exclrangeCCind
	#define VUI_cnt_exclrange0C	 VUQ_cnt_exclrange0C
	#define VUI_cnt_inclrangeCC	 VUQ_cnt_inclrangeCC
	#define VUI_cnt_exclrangeCC	 VUQ_cnt_exclrangeCC

	#define VUI_addC	VUQ_addC
	#define VUI_subC	VUQ_subC
	#define VUI_subrC	VUQ_subrC
	#define VUI_mulC	VUQ_mulC
	#define VUIo_addC	VUQ_addC
	#define VUIo_subC	VUQ_subC
	#define VUIo_subrC  VUQ_subrC
	#define VUIo_mulC	VUQ_mulC
	#define VUI_divC	VUQ_divC
	#define VUI_divrC	VUQ_divrC
	#define VUI_modC	VUQ_modC
	#define VUI_maxC	VUQ_maxC
	#define VUI_minC	VUQ_minC
	#define VUI_addV	VUQ_addV
	#define VUI_subV	VUQ_subV
	#define VUI_subrV	VUQ_subrV
	#define VUI_mulV	VUQ_mulV
	#define VUIo_addV	VUQ_addV
	#define VUIo_subV	VUQ_subV
	#define VUIo_subrV  VUQ_subrV
	#define VUIo_mulV	VUQ_mulV
	#define VUI_divV	VUQ_divV
	#define VUI_divrV	VUQ_divrV
	#define VUI_modV	VUQ_modV
	#define VUI_maxV	VUQ_maxV
	#define VUI_minV	VUQ_minV
	#define VUI_accV	VUQ_accV
	#define VUI_accVUB  VUQ_accVUB
	#define VUI_accVUS  VUQ_accVUS
	#define VUI_accVU	VUQ_accVU
	#define VUI_shl		VUQ_shl
	#define VUI_shr		VUQ_shr
	#define VUI_and		VUQ_and
	#define VUI_or		VUQ_or
	#define VUI_xor		VUQ_xor
	#define VUI_not		VUQ_not
	#define VUI_ODtoF	VUQ_ODtoF
	#define VUI_ODtoD	VUQ_ODtoD
	#define VUI_ODtoE	VUQ_ODtoE
	#define VUI_ODtoFwDark	VUQ_ODtoFwDark
	#define VUI_ODtoDwDark	VUQ_ODtoDwDark
	#define VUI_ODtoEwDark	VUQ_ODtoEwDark
	#define VUI_setODThresh VUQ_setODThresh
#else  /* Win32 */
	#if !defined( __VUMATH_H )
		 #include <VUmath.h>
	#endif
	#define VUI_cmp_eq0		VU_cmp_eq0
	#define VUI_cmp_ne0		VU_cmp_ne0
	#define VUI_cmp_gt0		VU_cmp_gt0
	#define VUI_cmp_eq0ind	VU_cmp_eq0ind
	#define VUI_cmp_ne0ind	VU_cmp_ne0ind
	#define VUI_cmp_gt0ind	VU_cmp_gt0ind
	#define VUI_cnt_eq0		VU_cnt_eq0
	#define VUI_cnt_ne0		VU_cnt_ne0
	#define VUI_cnt_gt0		VU_cnt_gt0
	#define VUI_cmpC		VU_cmpC
	#define VUI_cmp_eqC		VU_cmp_eqC
	#define VUI_cmp_neC		VU_cmp_neC
	#define VUI_cmp_leC		VU_cmp_leC
	#define VUI_cmp_ltC		VU_cmp_ltC
	#define VUI_cmp_geC		VU_cmp_geC
	#define VUI_cmp_gtC		VU_cmp_gtC
	#define VUI_cmp_eqCind	VU_cmp_eqCind
	#define VUI_cmp_neCind	VU_cmp_neCind
	#define VUI_cmp_leCind	VU_cmp_leCind
	#define VUI_cmp_ltCind	VU_cmp_ltCind
	#define VUI_cmp_geCind	VU_cmp_geCind
	#define VUI_cmp_gtCind	VU_cmp_gtCind
	#define VUI_cnt_eqC		VU_cnt_eqC
	#define VUI_cnt_neC		VU_cnt_neC
	#define VUI_cnt_leC		VU_cnt_leC
	#define VUI_cnt_ltC		VU_cnt_ltC
	#define VUI_cnt_geC		VU_cnt_geC
	#define VUI_cnt_gtC		VU_cnt_gtC
	#define VUI_cmpV		VU_cmpV
	#define VUI_cmp_eqV		VU_cmp_eqV
	#define VUI_cmp_neV		VU_cmp_neV
	#define VUI_cmp_leV		VU_cmp_leV
	#define VUI_cmp_ltV		VU_cmp_ltV
	#define VUI_cmp_geV		VU_cmp_geV
	#define VUI_cmp_gtV		VU_cmp_gtV
	#define VUI_cmp_eqVind	VU_cmp_eqVind
	#define VUI_cmp_neVind	VU_cmp_neVind
	#define VUI_cmp_leVind	VU_cmp_leVind
	#define VUI_cmp_ltVind	VU_cmp_ltVind
	#define VUI_cmp_geVind	VU_cmp_geVind
	#define VUI_cmp_gtVind	VU_cmp_gtVind
	#define VUI_cnt_eqV		VU_cnt_eqV
	#define VUI_cnt_neV		VU_cnt_neV
	#define VUI_cnt_leV		VU_cnt_leV
	#define VUI_cnt_ltV		VU_cnt_ltV
	#define VUI_cnt_geV		VU_cnt_geV
	#define VUI_cnt_gtV		VU_cnt_gtV
	#define VUI_cmp_exclrange0C	 VU_cmp_exclrange0C
	#define VUI_cmp_inclrangeCC	 VU_cmp_inclrangeCC
	#define VUI_cmp_exclrangeCC	 VU_cmp_exclrangeCC
	#define VUI_cmp_exclrange0Cind VU_cmp_exclrange0Cind
	#define VUI_cmp_inclrangeCCind VU_cmp_inclrangeCCind
	#define VUI_cmp_exclrangeCCind VU_cmp_exclrangeCCind
	#define VUI_cnt_exclrange0C	 VU_cnt_exclrange0C
	#define VUI_cnt_inclrangeCC	 VU_cnt_inclrangeCC
	#define VUI_cnt_exclrangeCC	 VU_cnt_exclrangeCC

	#define VUI_addC	VU_addC
	#define VUI_subC	VU_subC
	#define VUI_subrC	VU_subrC
	#define VUI_mulC	VU_mulC
	#define VUIo_addC	VUo_addC
	#define VUIo_subC	VUo_subC
	#define VUIo_subrC  VUo_subrC
	#define VUIo_mulC	VUo_mulC
	#define VUI_divC	VU_divC
	#define VUI_divrC	VU_divrC
	#define VUI_modC	VU_modC
	#define VUI_maxC	VU_maxC
	#define VUI_minC	VU_minC
	#define VUI_addV	VU_addV
	#define VUI_subV	VU_subV
	#define VUI_subrV	VU_subrV
	#define VUI_mulV	VU_mulV
	#define VUIo_addV	VUo_addV
	#define VUIo_subV	VUo_subV
	#define VUIo_subrV  VUo_subrV
	#define VUIo_mulV	VUo_mulV
	#define VUI_divV	VU_divV
	#define VUI_divrV	VU_divrV
	#define VUI_modV	VU_modV
	#define VUI_maxV	VU_maxV
	#define VUI_minV	VU_minV
	#define VUI_accV	VU_accV
	#define VUI_accVUB  VU_accVUB
	#define VUI_accVUS  VU_accVUS
	#define VUI_accVU	VU_accV
	#define VUI_shl		VU_shl
	#define VUI_shr		VU_shr
	#define VUI_and		VU_and
	#define VUI_or		VU_or
	#define VUI_xor		VU_xor
	#define VUI_not		VU_not
	#define VUI_ODtoF	VU_ODtoF
	#define VUI_ODtoD	VU_ODtoD
	#define VUI_ODtoE	VU_ODtoE
	#define VUI_ODtoFwDark	VU_ODtoFwDark
	#define VUI_ODtoDwDark	VU_ODtoDwDark
	#define VUI_ODtoEwDark	VU_ODtoEwDark
	#define VUI_setODThresh VU_setODThresh
#endif /* Win64 or Win32 */
#endif  /* __VUIMATH_H */


