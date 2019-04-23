/*  VFmath.h

  vector management functions:
  math functions performed on each individual element of an
  array or vector of the data type "float"

  Copyright (c) 1996-2017 by OptiCode - Dr. Martin Sander Software Dev.
  All Rights Reserved.
*/

#ifndef __VFMATH_H
#define __VFMATH_H

#ifndef __VFSTD_H 
#include <VFstd.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif



/**************************  Rounding **********************************/

int  __vf   VF_round(  fVector  Y, fVector X, ui size );
int  __vf   VF_roundtoBI( biVector Y, fVector X, ui size );
int  __vf   VF_roundtoSI( siVector Y, fVector X, ui size );
int  __vf   VF_roundtoI(  iVector  Y, fVector X, ui size );
int  __vf   VF_roundtoLI( liVector Y, fVector X, ui size );
int  __vf   VF_roundtoQI( qiVector Y, fVector X, ui size );
int  __vf   VF_roundtoUB( ubVector Y, fVector X, ui size );
int  __vf   VF_roundtoUS( usVector Y, fVector X, ui size );
int  __vf   VF_roundtoU(  uVector  Y, fVector X, ui size );
int  __vf   VF_roundtoUL( ulVector Y, fVector X, ui size );
#ifdef _WIN64
    int  __vf   VF_roundtoUQ( uqVector Y, fVector X, ui size );
#endif

int  __vf   VF_floor(  fVector  Y, fVector X, ui size );
int  __vf   VF_floortoBI( biVector Y, fVector X, ui size );
int  __vf   VF_floortoSI( siVector Y, fVector X, ui size );
int  __vf   VF_floortoI(  iVector  Y, fVector X, ui size );
int  __vf   VF_floortoLI( liVector Y, fVector X, ui size );
int  __vf   VF_floortoQI( qiVector Y, fVector X, ui size );
int  __vf   VF_floortoUB( ubVector Y, fVector X, ui size );
int  __vf   VF_floortoUS( usVector Y, fVector X, ui size );
int  __vf   VF_floortoU(  uVector  Y, fVector X, ui size );
int  __vf   VF_floortoUL( ulVector Y, fVector X, ui size );
#ifdef _WIN64
    int  __vf   VF_floortoUQ( uqVector Y, fVector X, ui size );
#endif

int  __vf   VF_ceil(  fVector  Y, fVector X, ui size );
int  __vf   VF_ceiltoBI( biVector Y, fVector X, ui size );
int  __vf   VF_ceiltoSI( siVector Y, fVector X, ui size );
int  __vf   VF_ceiltoI(  iVector  Y, fVector X, ui size );
int  __vf   VF_ceiltoLI( liVector Y, fVector X, ui size );
int  __vf   VF_ceiltoQI( qiVector Y, fVector X, ui size );
int  __vf   VF_ceiltoUB( ubVector Y, fVector X, ui size );
int  __vf   VF_ceiltoUS( usVector Y, fVector X, ui size );
int  __vf   VF_ceiltoU(  uVector  Y, fVector X, ui size );
int  __vf   VF_ceiltoUL( ulVector Y, fVector X, ui size );
#ifdef _WIN64
    int  __vf   VF_ceiltoUQ( uqVector Y, fVector X, ui size );
#endif

int  __vf   VF_chop(  fVector  Y, fVector X, ui size );
int  __vf   VF_choptoBI( biVector Y, fVector X, ui size );
int  __vf   VF_choptoSI( siVector Y, fVector X, ui size );
int  __vf   VF_choptoI(  iVector  Y, fVector X, ui size );
int  __vf   VF_choptoLI( liVector Y, fVector X, ui size );
int  __vf   VF_choptoQI( qiVector Y, fVector X, ui size );
int  __vf   VF_choptoUB( ubVector Y, fVector X, ui size );
int  __vf   VF_choptoUS( usVector Y, fVector X, ui size );
int  __vf   VF_choptoU(  uVector  Y, fVector X, ui size );
int  __vf   VF_choptoUL( ulVector Y, fVector X, ui size );
#ifdef _WIN64
    int  __vf   VF_choptoUQ( uqVector Y, fVector X, ui size );
#endif

#define VF_trunc      VF_chop
#define VF_trunctoBI  VF_choptoBI
#define VF_trunctoSI  VF_choptoSI
#define VF_trunctoI   VF_choptoI
#define VF_trunctoLI  VF_choptoLI
#define VF_trunctoQI  VF_choptoQI
#define VF_trunctoUB  VF_choptoUB
#define VF_trunctoUS  VF_choptoUS
#define VF_trunctoU   VF_choptoU
#define VF_trunctoUL  VF_choptoUL
#define VF_trunctoUQ  VF_choptoUQ

#if defined V_HUGE
      #define   VF_roundtoUI    VF_roundtoUL
      #define   VF_floortoUI    VF_floortoUL
      #define   VF_ceiltoUI     VF_ceiltoUL
      #define   VF_choptoUI     VF_choptoUL
      #define   VF_trunctoUI    VF_trunctoUL
#elif defined _WIN64
      #define   VF_roundtoUI    VF_roundtoUQ
      #define   VF_floortoUI    VF_floortoUQ
      #define   VF_ceiltoUI     VF_ceiltoUQ
      #define   VF_choptoUI     VF_choptoUQ
      #define   VF_trunctoUI    VF_trunctoUQ
#else
      #define   VF_roundtoUI    VF_roundtoU
      #define   VF_floortoUI    VF_floortoU
      #define   VF_ceiltoUI     VF_ceiltoU
      #define   VF_choptoUI     VF_choptoU
      #define   VF_trunctoUI    VF_trunctoU
#endif

/********************  Comparisons ********************************/

void __vf   VF_cmp0(    fVector Y, fVector X, ui size );
ui   __vf   VF_cmp_eq0( fVector Y, fVector X, ui size );
ui   __vf   VF_cmp_ne0( fVector Y, fVector X, ui size );
ui   __vf   VF_cmp_le0( fVector Y, fVector X, ui size );
ui   __vf   VF_cmp_lt0( fVector Y, fVector X, ui size );
ui   __vf   VF_cmp_ge0( fVector Y, fVector X, ui size );
ui   __vf   VF_cmp_gt0( fVector Y, fVector X, ui size );

ui   __vf   VF_cmp_eq0ind( uiVector Ind, fVector X, ui size );
ui   __vf   VF_cmp_ne0ind( uiVector Ind, fVector X, ui size );
ui   __vf   VF_cmp_le0ind( uiVector Ind, fVector X, ui size );
ui   __vf   VF_cmp_lt0ind( uiVector Ind, fVector X, ui size );
ui   __vf   VF_cmp_ge0ind( uiVector Ind, fVector X, ui size );
ui   __vf   VF_cmp_gt0ind( uiVector Ind, fVector X, ui size );

ui   __vf   VF_cnt_eq0( fVector X, ui size );
ui   __vf   VF_cnt_ne0( fVector X, ui size );
ui   __vf   VF_cnt_le0( fVector X, ui size );
ui   __vf   VF_cnt_lt0( fVector X, ui size );
ui   __vf   VF_cnt_ge0( fVector X, ui size );
ui   __vf   VF_cnt_gt0( fVector X, ui size );

void __vf   VF_cmpC(    fVector Y, fVector X, ui size, float C );
ui   __vf   VF_cmp_eqC( fVector Y, fVector X, ui size, float C );
ui   __vf   VF_cmp_neC( fVector Y, fVector X, ui size, float C );
ui   __vf   VF_cmp_leC( fVector Y, fVector X, ui size, float C );
ui   __vf   VF_cmp_ltC( fVector Y, fVector X, ui size, float C );
ui   __vf   VF_cmp_geC( fVector Y, fVector X, ui size, float C );
ui   __vf   VF_cmp_gtC( fVector Y, fVector X, ui size, float C );

ui   __vf   VF_cmp_eqCind( uiVector Ind, fVector X, ui size, float C );
ui   __vf   VF_cmp_neCind( uiVector Ind, fVector X, ui size, float C );
ui   __vf   VF_cmp_leCind( uiVector Ind, fVector X, ui size, float C );
ui   __vf   VF_cmp_ltCind( uiVector Ind, fVector X, ui size, float C );
ui   __vf   VF_cmp_geCind( uiVector Ind, fVector X, ui size, float C );
ui   __vf   VF_cmp_gtCind( uiVector Ind, fVector X, ui size, float C );

ui   __vf   VF_cnt_eqC( fVector X, ui size, float C );
ui   __vf   VF_cnt_neC( fVector X, ui size, float C );
ui   __vf   VF_cnt_leC( fVector X, ui size, float C );
ui   __vf   VF_cnt_ltC( fVector X, ui size, float C );
ui   __vf   VF_cnt_geC( fVector X, ui size, float C );
ui   __vf   VF_cnt_gtC( fVector X, ui size, float C );

void __vf   VF_cmpV(    fVector Z, fVector X, fVector Y, ui size );
ui   __vf   VF_cmp_eqV( fVector Z, fVector X, fVector Y, ui size );
ui   __vf   VF_cmp_neV( fVector Z, fVector X, fVector Y, ui size );
ui   __vf   VF_cmp_leV( fVector Z, fVector X, fVector Y, ui size );
ui   __vf   VF_cmp_ltV( fVector Z, fVector X, fVector Y, ui size );
ui   __vf   VF_cmp_geV( fVector Z, fVector X, fVector Y, ui size );
ui   __vf   VF_cmp_gtV( fVector Z, fVector X, fVector Y, ui size );

ui   __vf   VF_cmp_eqVind( uiVector Ind, fVector X, fVector Y, ui size );
ui   __vf   VF_cmp_neVind( uiVector Ind, fVector X, fVector Y, ui size );
ui   __vf   VF_cmp_leVind( uiVector Ind, fVector X, fVector Y, ui size );
ui   __vf   VF_cmp_ltVind( uiVector Ind, fVector X, fVector Y, ui size );
ui   __vf   VF_cmp_geVind( uiVector Ind, fVector X, fVector Y, ui size );
ui   __vf   VF_cmp_gtVind( uiVector Ind, fVector X, fVector Y, ui size );

ui   __vf   VF_cnt_eqV( fVector X, fVector Y, ui size );
ui   __vf   VF_cnt_neV( fVector X, fVector Y, ui size );
ui   __vf   VF_cnt_leV( fVector X, fVector Y, ui size );
ui   __vf   VF_cnt_ltV( fVector X, fVector Y, ui size );
ui   __vf   VF_cnt_geV( fVector X, fVector Y, ui size );
ui   __vf   VF_cnt_gtV( fVector X, fVector Y, ui size );

ui   __vf   VF_cmp_inclrange0C( fVector Y, fVector X, ui size, float C );
ui   __vf   VF_cmp_exclrange0C( fVector Y, fVector X, ui size, float C );
ui   __vf   VF_cmp_inclrangeCC( fVector Y, fVector X, ui size, float CLo, float CHi );
ui   __vf   VF_cmp_exclrangeCC( fVector Y, fVector X, ui size, float CLo, float CHi );

ui   __vf   VF_cmp_inclrange0Cind( uiVector Ind, fVector X, ui size, float C );
ui   __vf   VF_cmp_exclrange0Cind( uiVector Ind, fVector X, ui size, float C );
ui   __vf   VF_cmp_inclrangeCCind( uiVector Ind, fVector X, ui size, float CLo, float CHi );
ui   __vf   VF_cmp_exclrangeCCind( uiVector Ind, fVector X, ui size, float CLo, float CHi );

ui   __vf   VF_cnt_inclrange0C( fVector X, ui size, float C );
ui   __vf   VF_cnt_exclrange0C( fVector X, ui size, float C );
ui   __vf   VF_cnt_inclrangeCC( fVector X, ui size, float CLo, float CHi );
ui   __vf   VF_cnt_exclrangeCC( fVector X, ui size, float CLo, float CHi );


/********************  Standard Arithmetics   ***************************/

void  __vf  VF_equC( fVector X, ui size, float C );
void  __vf  VF_equV( fVector Y, fVector X, ui size );
void  __vf  VFx_equV( fVector Y, fVector X, ui size, float A, float B );

void  __vf  VF_addC(  fVector Y, fVector X, ui size, float C );
void  __vf  VF_subC(  fVector Y, fVector X, ui size, float C );
void  __vf  VF_subrC( fVector Y, fVector X, ui size, float C );
void  __vf  VF_mulC(  fVector Y, fVector X, ui size, float C );
void  __vf  VF_divC(  fVector Y, fVector X, ui size, float C );
void  __vf  VF_divrC( fVector Y, fVector X, ui size, float C );
void  __vf  VFx_divrC( fVector Y, fVector X, ui size, float A, float B, float C );

void  __vf  VF_addV(  fVector Z, fVector X, fVector Y, ui size );
void  __vf  VF_subV(  fVector Z, fVector X, fVector Y, ui size );
void  __vf  VF_subrV( fVector Z, fVector X, fVector Y, ui size );
void  __vf  VF_mulV(  fVector Z, fVector X, fVector Y, ui size );
void  __vf  VF_divV(  fVector Z, fVector X, fVector Y, ui size );
void  __vf  VF_divrV(  fVector Z, fVector X, fVector Y, ui size );
void  __vf  VF_add2V(  fVector Z, fVector X, fVector Y1, fVector Y2, ui size );
void  __vf  VF_sub2V(  fVector Z, fVector X, fVector Y1, fVector Y2, ui size );

void  __vf   VF_CaddV( fVector Z, fVector X, fVector Y, ui siz, float C );
                              /* Z = X + C*Y  */

void  __vf  VFx_addV(  fVector Z, fVector X, fVector Y, ui size, float A, float B );
                              /* Z = (A*X+B) + Y  */
void  __vf  VFx_subV(  fVector Z, fVector X, fVector Y, ui size, float A, float B );
void  __vf  VFx_subrV( fVector Z, fVector X, fVector Y, ui size, float A, float B );
void  __vf  VFx_mulV(  fVector Z, fVector X, fVector Y, ui size, float A, float B );
void  __vf  VFx_divV(  fVector Z, fVector X, fVector Y, ui size, float A, float B );
void  __vf  VFx_divrV( fVector Z, fVector X, fVector Y, ui size, float A, float B );

void  __vf  VFs_addV(  fVector Z, fVector X, fVector Y, ui size, float C ); /* Z=C*(X+Y) */
void  __vf  VFs_subV(  fVector Z, fVector X, fVector Y, ui size, float C );
void  __vf  VFs_subrV( fVector Z, fVector X, fVector Y, ui size, float C );
void  __vf  VFs_mulV(  fVector Z, fVector X, fVector Y, ui size, float C );
void  __vf  VFs_divV(  fVector Z, fVector X, fVector Y, ui size, float C );
void  __vf  VFs_divrV( fVector Z, fVector X, fVector Y, ui size, float C );

void  __vf  VF_maxC(   fVector Y, fVector X, ui size, float C );
void  __vf  VF_minC(   fVector Y, fVector X, ui size, float C );
void  __vf  VF_limit(  fVector Y, fVector X, ui size, float Min, float Max );
void  __vf  VF_flush0( fVector Y, fVector X, ui size, float AbsMin );
void  __vf  VF_flushInv( fVector Y, fVector X, ui size, float AbsMin );
void  __vf  VF_replaceNAN( fVector Y, fVector X, ui siz, float C );
void  __vf  VF_maxV(   fVector Z, fVector X, fVector Y, ui size );
void  __vf  VF_minV(   fVector Z, fVector X, fVector Y, ui size );
void  __vf  VF_modC(   fVector Y, fVector X, ui size, float C );
void  __vf  VF_modV(   fVector Z, fVector X, fVector Y, ui size );
void  __vf  VFx_modV(  fVector Z, fVector X, fVector Y, ui size, float A, float B );
#define     VF_fmodC    VF_modC
#define     VF_fmodV    VF_modV
#define     VFx_fmodV   VFx_modV

void __vf  VF_redC(  fVector Y, fVector X, ui size, float C );
void __vf  VF_redV(  fVector Z, fVector X, fVector Y, ui size );
void __vf  VFx_redV( fVector Z, fVector X, fVector Y, ui size, float A, float B );
void __vf  VF_visC(  fVector Y, fVector X, ui size, float C );
void __vf  VF_visV(  fVector Z, fVector X, fVector Y, ui size );
void __vf  VFx_visV( fVector Z, fVector X, fVector Y, ui size, float A, float B );
void __vf  VF_hypC(  fVector Y, fVector X, ui size, float C );
void __vf  VF_hypV(  fVector Z, fVector X, fVector Y, ui size );
void __vf  VFx_hypV( fVector Z, fVector X, fVector Y, ui size, float A, float B );

void __vf VF_lincomb( fVector Z, fVector X, fVector Y, ui size,
                      float CX, float CY );  /* Z=CX*X+CY*Y */

void __vf VF_rotateCoordinates( fVector Xnew, fVector Ynew, fVector Xold, fVector Yold,
                      ui size, float costheta, float sintheta );
#define VF_sgn    VF_cmp0

/******************* Mixed-type arithmetic Functions **********************/

void  __vf  VF_addVBI(  fVector Z, fVector X, biVector Y, ui size );
void  __vf  VF_subVBI(  fVector Z, fVector X, biVector Y, ui size );
void  __vf  VF_subrVBI( fVector Z, fVector X, biVector Y, ui size );
void  __vf  VF_mulVBI(  fVector Z, fVector X, biVector Y, ui size );
void  __vf  VF_divVBI(  fVector Z, fVector X, biVector Y, ui size );
void  __vf  VF_divrVBI( fVector Z, fVector X, biVector Y, ui size );
void  __vf  VF_addVSI(  fVector Z, fVector X, siVector Y, ui size );
void  __vf  VF_subVSI(  fVector Z, fVector X, siVector Y, ui size );
void  __vf  VF_subrVSI( fVector Z, fVector X, siVector Y, ui size );
void  __vf  VF_mulVSI(  fVector Z, fVector X, siVector Y, ui size );
void  __vf  VF_divVSI(  fVector Z, fVector X, siVector Y, ui size );
void  __vf  VF_divrVSI( fVector Z, fVector X, siVector Y, ui size );
void  __vf  VF_addVI(  fVector Z, fVector X, iVector Y, ui size );
void  __vf  VF_subVI(  fVector Z, fVector X, iVector Y, ui size );
void  __vf  VF_subrVI( fVector Z, fVector X, iVector Y, ui size );
void  __vf  VF_mulVI(  fVector Z, fVector X, iVector Y, ui size );
void  __vf  VF_divVI(  fVector Z, fVector X, iVector Y, ui size );
void  __vf  VF_divrVI( fVector Z, fVector X, iVector Y, ui size );
void  __vf  VF_addVLI(  fVector Z, fVector X, liVector Y, ui size );
void  __vf  VF_subVLI(  fVector Z, fVector X, liVector Y, ui size );
void  __vf  VF_subrVLI( fVector Z, fVector X, liVector Y, ui size );
void  __vf  VF_mulVLI(  fVector Z, fVector X, liVector Y, ui size );
void  __vf  VF_divVLI(  fVector Z, fVector X, liVector Y, ui size );
void  __vf  VF_divrVLI( fVector Z, fVector X, liVector Y, ui size );
void  __vf  VF_addVQI(  fVector Z, fVector X, qiVector Y, ui size );
void  __vf  VF_subVQI(  fVector Z, fVector X, qiVector Y, ui size );
void  __vf  VF_subrVQI( fVector Z, fVector X, qiVector Y, ui size );
void  __vf  VF_mulVQI(  fVector Z, fVector X, qiVector Y, ui size );
void  __vf  VF_divVQI(  fVector Z, fVector X, qiVector Y, ui size );
void  __vf  VF_divrVQI( fVector Z, fVector X, qiVector Y, ui size );
void  __vf  VF_addVUB(  fVector Z, fVector X, ubVector Y, ui size );
void  __vf  VF_subVUB(  fVector Z, fVector X, ubVector Y, ui size );
void  __vf  VF_subrVUB( fVector Z, fVector X, ubVector Y, ui size );
void  __vf  VF_mulVUB(  fVector Z, fVector X, ubVector Y, ui size );
void  __vf  VF_divVUB(  fVector Z, fVector X, ubVector Y, ui size );
void  __vf  VF_divrVUB( fVector Z, fVector X, ubVector Y, ui size );
void  __vf  VF_addVUS(  fVector Z, fVector X, usVector Y, ui size );
void  __vf  VF_subVUS(  fVector Z, fVector X, usVector Y, ui size );
void  __vf  VF_subrVUS( fVector Z, fVector X, usVector Y, ui size );
void  __vf  VF_mulVUS(  fVector Z, fVector X, usVector Y, ui size );
void  __vf  VF_divVUS(  fVector Z, fVector X, usVector Y, ui size );
void  __vf  VF_divrVUS( fVector Z, fVector X, usVector Y, ui size );
void  __vf  VF_addVU(   fVector Z, fVector X, uVector Y,  ui size );
void  __vf  VF_subVU(   fVector Z, fVector X, uVector Y,  ui size );
void  __vf  VF_subrVU(  fVector Z, fVector X, uVector Y,  ui size );
void  __vf  VF_mulVU(   fVector Z, fVector X, uVector Y,  ui size );
void  __vf  VF_divVU(   fVector Z, fVector X, uVector Y,  ui size );
void  __vf  VF_divrVU(  fVector Z, fVector X, uVector Y,  ui size );
void  __vf  VF_addVUL(  fVector Z, fVector X, ulVector Y, ui size );
void  __vf  VF_subVUL(  fVector Z, fVector X, ulVector Y, ui size );
void  __vf  VF_subrVUL( fVector Z, fVector X, ulVector Y, ui size );
void  __vf  VF_mulVUL(  fVector Z, fVector X, ulVector Y, ui size );
void  __vf  VF_divVUL(  fVector Z, fVector X, ulVector Y, ui size );
void  __vf  VF_divrVUL( fVector Z, fVector X, ulVector Y, ui size );
#ifdef _WIN64
    void  __vf  VF_addVUQ(  fVector Z, fVector X, uqVector Y, ui size );
    void  __vf  VF_subVUQ(  fVector Z, fVector X, uqVector Y, ui size );
    void  __vf  VF_subrVUQ( fVector Z, fVector X, uqVector Y, ui size );
    void  __vf  VF_mulVUQ(  fVector Z, fVector X, uqVector Y, ui size );
    void  __vf  VF_divVUQ(  fVector Z, fVector X, uqVector Y, ui size );
    void  __vf  VF_divrVUQ( fVector Z, fVector X, uqVector Y, ui size );
    #define VF_addVUI  VF_addVUQ
    #define VF_subVUI  VF_subVUQ
    #define VF_subrVUI VF_subrVUQ
    #define VF_mulVUI  VF_mulVUQ
    #define VF_divVUI  VF_divVUQ
    #define VF_divrVUI VF_divrVUQ
#elif defined V_HUGE
    #define VF_addVUI  VF_addVUL
    #define VF_subVUI  VF_subVUL
    #define VF_subrVUI VF_subrVUL
    #define VF_mulVUI  VF_mulVUL
    #define VF_divVUI  VF_divVUL
    #define VF_divrVUI VF_divrVUL
#else
    #define VF_addVUI  VF_addVU
    #define VF_subVUI  VF_subVU
    #define VF_subrVUI VF_subrVU
    #define VF_mulVUI  VF_mulVU
    #define VF_divVUI  VF_divVU
    #define VF_divrVUI VF_divrVU
#endif

/******************** Accumulation (Y += X) ******************************/

void __vf VF_accV(   fVector Y, fVector  X, ui size );
void __vf VF_accVBI( fVector Y, biVector X, ui size );
void __vf VF_accVSI( fVector Y, siVector X, ui size );
void __vf VF_accVI(  fVector Y, iVector  X, ui size );
void __vf VF_accVLI( fVector Y, liVector X, ui size );
void __vf VF_accVQI( fVector Y, qiVector X, ui size );
void __vf VF_accVUB( fVector Y, ubVector X, ui size );
void __vf VF_accVUS( fVector Y, usVector X, ui size );
void __vf VF_accVU(  fVector Y, uVector  X, ui size );
void __vf VF_accVUL( fVector Y, ulVector X, ui size );
void __vf VF_acc2V(  fVector Y, fVector  X1, fVector  X2, ui size );
#if defined _WIN64
    void __vf VF_accVUQ( fVector Y, uqVector X, ui size );
    #define VF_accVUI   VF_accVUQ
#elif defined V_HUGE
    #define VF_accVUI   VF_accVUL
#else
    #define VF_accVUI   VF_accVU
#endif

/***************** Functions of a sub-set of elements  ********************/

void  __vf  VF_subvector_equC(  fVector Y, ui subsiz, ui samp, float C );
void  __vf  VF_subvector_equV(  fVector Y, ui subsiz, ui samp, fVector X );

void  __vf  VF_subvector_addC(  fVector Y, ui subsiz, ui samp, float C );
void  __vf  VF_subvector_subC(  fVector Y, ui subsiz, ui samp, float C );
void  __vf  VF_subvector_subrC( fVector Y, ui subsiz, ui samp, float C );
void  __vf  VF_subvector_mulC(  fVector Y, ui subsiz, ui samp, float C );
void  __vf  VF_subvector_divC(  fVector Y, ui subsiz, ui samp, float C );
void  __vf  VF_subvector_divrC( fVector Y, ui subsiz, ui samp, float C );

void  __vf  VF_subvector_addV(  fVector Y, ui subsiz, ui samp, fVector X );
void  __vf  VF_subvector_subV(  fVector Y, ui subsiz, ui samp, fVector X );
void  __vf  VF_subvector_subrV( fVector Y, ui subsiz, ui samp, fVector X );
void  __vf  VF_subvector_mulV(  fVector Y, ui subsiz, ui samp, fVector X );
void  __vf  VF_subvector_divV(  fVector Y, ui subsiz, ui samp, fVector X );
void  __vf  VF_subvector_divrV( fVector Y, ui subsiz, ui samp, fVector X );



/*********************  Mathematical Functions ***********************/

int   __vf   VF_abs( fVector Y, fVector X, ui size );
int   __vf   VF_neg( fVector Y, fVector X, ui size );
int   __vf   VF_inv( fVector Y, fVector X, ui size );
int   __vf   VFx_inv( fVector Y, fVector X, ui size, float A, float B );
int   __vf   VF_intfrac( fVector Int, fVector Frac, fVector X, ui size );
#define      VF_modf    VF_intfrac
int   __vf   VF_mantexp( fVector Mant, iVector Exp, fVector X, ui size );
#define      VF_frexp   VF_mantexp

int  __vf    VF_hypotC( fVector Y, fVector X, ui size, float C );
int  __vf    VF_hypotV( fVector Z, fVector X, fVector Y, ui size );
int  __vf    VFx_hypotV( fVector Z, fVector X, fVector Y, ui size, float A, float B );

int  __vf    VF_scale2( fVector Y, fVector X, ui size, int expo );
int  __vf    VF_scale10( fVector Y, fVector X, ui size, int expo );
#define      VF_ldexp    VF_scale2

int  __vf    VF_square( fVector Y, fVector X, ui size );
int  __vf    VFx_square( fVector Y, fVector X, ui size, float A, float B );
int  __vf    VF_cubic( fVector Y, fVector X, ui size );
int  __vf    VFx_cubic( fVector Y, fVector X, ui size, float A, float B );
int  __vf    VF_quartic( fVector Y, fVector X, ui size );
int  __vf    VFx_quartic( fVector Y, fVector X, ui size, float A, float B );
int  __vf    VF_poly( fVector Y, fVector X, ui size, fVector Coeff, unsigned deg );
int  __vf    VFx_poly( fVector Y, fVector X, ui size, fVector Coeff, unsigned deg, float A, float B );
int  __vf    VF_ipow( fVector Y, fVector X, ui size, int ipow );
int  __vf    VFx_ipow( fVector Y, fVector X, ui size, int ipow, float A, float B, float C );
                           /*  ipow = integer power of x */

       /* extra fast integer powers: "unprotected", without error handling: */
int  __vf    VFu_square( fVector Y, fVector X, ui size );
int  __vf    VFux_square( fVector Y, fVector X, ui size, float A, float B );
int  __vf    VFu_cubic( fVector Y, fVector X, ui size );
int  __vf    VFux_cubic( fVector Y, fVector X, ui size, float A, float B );
int  __vf    VFu_quartic( fVector Y, fVector X, ui size );
int  __vf    VFux_quartic( fVector Y, fVector X, ui size, float A, float B );
int  __vf    VFu_poly( fVector Y, fVector X, ui size, fVector Coeff, unsigned deg );
int  __vf    VFux_poly( fVector Y, fVector X, ui size, fVector Coeff, unsigned deg, float A, float B );
int  __vf    VFu_ipow( fVector Y, fVector X, ui size, int ipow );
int  __vf    VFux_ipow( fVector Y, fVector X, ui size, int ipow, float A, float B, float C );

int  __vf    VF_ipow2(  fVector Y, iVector X, ui size );
int  __vf    VF_ipow10( fVector Y, iVector X, ui size );
                          /* ipow2 and ipow10: integer powers of 2 and 10 */

int  __vf   VF_pow(    fVector Y, fVector X, ui size, float expo );
int  __vf   VFx_pow(   fVector Y, fVector X, ui size, float expo, float A, float B, float C );

int  __vf   VF_pow2(   fVector Y, fVector X, ui size );
int  __vf   VFx_pow2(  fVector Y, fVector X, ui size, float A, float B, float C );
int  __vf   VF_pow10(  fVector Y, fVector X, ui size );
int  __vf   VFx_pow10( fVector Y, fVector X, ui size, float A, float B, float C );
            /* pow2 and pow10: basis 2 or 10 raised to power x */

int  __vf   VF_sqrt(  fVector Y, fVector X, ui size );
int  __vf   VFx_sqrt( fVector Y, fVector X, ui size, float A, float B, float C );
int  __vf   VFu_sqrt(  fVector Y, fVector X, ui size );
int  __vf   VFux_sqrt( fVector Y, fVector X, ui size, float A, float B, float C );

int  __vf   VF_log(    fVector Y, fVector X, ui size );
int  __vf   VF_log2(   fVector Y, fVector X, ui size );
int  __vf   VF_log10(  fVector Y, fVector X, ui size );
#define     VF_ln      VF_log
int  __vf   VFx_log(   fVector Y, fVector X, ui size, float A, float B, float C );
int  __vf   VFx_log2(  fVector Y, fVector X, ui size, float A, float B, float C );
int  __vf   VFx_log10( fVector Y, fVector X, ui size, float A, float B, float C );
#define     VFx_ln     VFx_log

int  __vf   VF_OD( fVector OD, fVector X, fVector X0, ui size );  /* OD = log10( X0/X ) */
int  __vf   VF_ODwDark( fVector OD, fVector X, fVector XDark,
                        fVector X0, fVector X0Dark, ui size );
void __vf   VF_setODThresh( float minX, float minX0 );

int  __vf   VF_exp(   fVector Y, fVector X, ui size );
int  __vf   VFx_exp(  fVector Y, fVector X, ui size, float A, float B, float C );
int  __vf   VF_expArbBase(  fVector Y, fVector X, ui size, float Base );
int  __vf   VFx_expArbBase( fVector Y, fVector X, ui size, float Base,
                            float A, float B, float C );
int  __vf   VF_expc(  fVector Y, fVector X, ui size );
int  __vf   VFx_expc( fVector Y, fVector X, ui size, float A, float B, float C );
                /* expc(x) = 1 - exp(x)  */
int  __vf   VF_expmx2(  fVector Y, fVector X, ui size );
int  __vf   VFx_expmx2( fVector Y, fVector X, ui size, float A, float B, float C );
                /* expmx2(x) = exp( -x**2 )  */
int  __vf   VF_exp2(  fVector Y, fVector X, ui size );
int  __vf   VFx_exp2( fVector Y, fVector X, ui size, float A, float B, float C );
int  __vf   VF_exp10(  fVector Y, fVector X, ui size );
int  __vf   VFx_exp10( fVector Y, fVector X, ui size, float A, float B, float C );
                /*  exp2 and exp10 used as synonyms for pow2 and pow10 */
int  __vf  VF_powexp( fVector Y, fVector X, ui size, float expo );
int  __vf  VFx_powexp( fVector Y, fVector X, ui size, float expo, float A, float B, float C );

int  __vf   VF_erf(     fVector Y, fVector X, ui size );
int  __vf   VFx_erf(    fVector Y, fVector X, ui size, float A, float B, float C );
int  __vf   VF_erfc(    fVector Y, fVector X, ui size );
int  __vf   VFx_erfc(   fVector Y, fVector X, ui size, float A, float B, float C );
int  __vf   VF_Gauss(   fVector Y, fVector X, ui size, float Wid, float Cent, float C );
#define VF_gauss VF_Gauss
int  __vf   VF_Lorentz( fVector Y, fVector X, ui size, float Wid, float Cent, float C );
#define VF_lorentz VF_Lorentz

int  __vf   VF_sin(     fVector Y, fVector X, ui size );
int  __vf   VFx_sin(    fVector Y, fVector X, ui size, float A, float B, float C );
int  __vf   VF_cos(     fVector Y, fVector X, ui size );
int  __vf   VFx_cos(    fVector Y, fVector X, ui size, float A, float B, float C );
int  __vf   VF_sincos(  fVector Sin, fVector Cos, fVector X, ui size );
int  __vf   VFx_sincos( fVector Sin, fVector Cos, fVector X, ui size, float A, float B, float C );

int  __vf   VF_tan(     fVector Y, fVector X, ui size );
int  __vf   VFx_tan(    fVector Y, fVector X, ui size, float A, float B, float C );
int  __vf   VF_cot(     fVector Y, fVector X, ui size );
int  __vf   VFx_cot(    fVector Y, fVector X, ui size, float A, float B, float C );

int  __vf   VF_sec(     fVector Y, fVector X, ui size );
int  __vf   VFx_sec(    fVector Y, fVector X, ui size, float A, float B, float C );
int  __vf   VF_cosec(   fVector Y, fVector X, ui size );
int  __vf   VFx_cosec(  fVector Y, fVector X, ui size, float A, float B, float C );

int  __vf   VF_sin2(    fVector Y, fVector X, ui size );
int  __vf   VFx_sin2(   fVector Y, fVector X, ui size, float A, float B, float C );
int  __vf   VF_cos2(    fVector Y, fVector X, ui size );
int  __vf   VFx_cos2(   fVector Y, fVector X, ui size, float A, float B, float C );
int  __vf   VF_sincos2( fVector Sin, fVector Cos, fVector X, ui size );
int  __vf   VFx_sincos2( fVector Sin, fVector Cos, fVector X, ui size, float A, float B, float C );

int  __vf   VF_tan2(     fVector Y, fVector X, ui size );
int  __vf   VFx_tan2(    fVector Y, fVector X, ui size, float A, float B, float C );
int  __vf   VF_cot2(     fVector Y, fVector X, ui size );
int  __vf   VFx_cot2(    fVector Y, fVector X, ui size, float A, float B, float C );
int  __vf   VF_sec2(     fVector Y, fVector X, ui size );
int  __vf   VFx_sec2(    fVector Y, fVector X, ui size, float A, float B, float C );
int  __vf   VF_cosec2(   fVector Y, fVector X, ui size );
int  __vf   VFx_cosec2(  fVector Y, fVector X, ui size, float A, float B, float C );

 /*  reduced-range sine and cosine for -2Pi <= x <= +2Pi */
int  __vf   VFr_sin(     fVector Y, fVector X, ui size );
int  __vf   VFrx_sin(    fVector Y, fVector X, ui size, float A, float B, float C );
int  __vf   VFr_cos(     fVector Y, fVector X, ui size );
int  __vf   VFrx_cos(    fVector Y, fVector X, ui size, float A, float B, float C );
int  __vf   VFr_sincos(  fVector YSin, fVector YCos, fVector X, ui size );
int  __vf   VFrx_sincos( fVector YSin, fVector YCos, fVector X, ui size, float A, float B, float C );
int  __vf   VFr_sin2(     fVector Y, fVector X, ui size );
int  __vf   VFrx_sin2(    fVector Y, fVector X, ui size, float A, float B, float C );
int  __vf   VFr_cos2(     fVector Y, fVector X, ui size );
int  __vf   VFrx_cos2(    fVector Y, fVector X, ui size, float A, float B, float C );
int  __vf   VFr_sincos2(  fVector YSin, fVector YCos, fVector X, ui size );
int  __vf   VFrx_sincos2( fVector YSin, fVector YCos, fVector X, ui size, float A, float B, float C );

/* trigonometric functions of rational multiples of Pi: x = p/q * Pi */
int  __vf   VF_sinrpi(   fVector Y, iVector P, ui size, int q );
int  __vf   VF_cosrpi(   fVector Y, iVector P, ui size, int q );
int  __vf   VF_sincosrpi( fVector YSin, fVector YCos, iVector P, ui size, int q );
int  __vf   VF_tanrpi(   fVector Y, iVector P, ui size, int q );
int  __vf   VF_cotrpi(   fVector Y, iVector P, ui size, int q );
int  __vf   VF_secrpi(   fVector Y, iVector P, ui size, int q );
int  __vf   VF_cosecrpi( fVector Y, iVector P, ui size, int q );

int  __vf   VF_sinrpi2(  fVector Y, iVector P, ui size, int q );
int  __vf   VF_cosrpi2(  fVector Y, iVector P, ui size, int q );
int  __vf   VF_sincosrpi2( fVector YSin, fVector YCos, iVector P, ui size, int q );
int  __vf   VF_tanrpi2(  fVector Y, iVector P, ui size, int q );
int  __vf   VF_cotrpi2(  fVector Y, iVector P, ui size, int q );
int  __vf   VF_secrpi2(  fVector Y, iVector P, ui size, int q );
int  __vf   VF_cosecrpi2( fVector Y, iVector P, ui size, int q );

int  __vf   VF_sinrpi3(  fVector Y, iVector P, ui size, int q );
int  __vf   VF_cosrpi3(  fVector Y, iVector P, ui size, int q );
int  __vf   VF_sincosrpi3( fVector YSin, fVector YCos, iVector P, ui size, int q );
int  __vf   VF_tanrpi3(  fVector Y, iVector P, ui size, int q );
int  __vf   VF_cotrpi3(  fVector Y, iVector P, ui size, int q );
int  __vf   VF_secrpi3(  fVector Y, iVector P, ui size, int q );
int  __vf   VF_cosecrpi3( fVector Y, iVector P, ui size, int q );

int  __vf   VF_sinc(     fVector Y, fVector X, ui size );
int  __vf   VFx_sinc(    fVector Y, fVector X, ui size, float A, float B, float C );
int  __vf   VF_Kepler(   fVector Y, fVector X, ui size, float T, float e );
int  __vf   VFx_Kepler(  fVector Y, fVector X, ui size, float T, float e,
                         float A, float B );
#define VF_kepler  VF_Kepler
#define VFx_kepler VFx_Kepler

int  __vf   VF_asin(    fVector Y, fVector X, ui size );
int  __vf   VFx_asin(   fVector Y, fVector X, ui size, float A, float B, float C );
int  __vf   VF_acos(    fVector Y, fVector X, ui size );
int  __vf   VFx_acos(   fVector Y, fVector X, ui size, float A, float B, float C );
int  __vf   VF_atan(    fVector Y, fVector X, ui size );
int  __vf   VFx_atan(   fVector Y, fVector X, ui size, float A, float B, float C );
int  __vf   VF_atan2(   fVector Z, fVector X, fVector Y, ui size );
int  __vf   VFx_atan2(  fVector Z, fVector X, fVector Y, ui size, float A, float B, float C );

int  __vf   VF_sinh(    fVector Y, fVector X, ui size );
int  __vf   VFx_sinh(   fVector Y, fVector X, ui size, float A, float B, float C );
int  __vf   VF_cosh(    fVector Y, fVector X, ui size );
int  __vf   VFx_cosh(   fVector Y, fVector X, ui size, float A, float B, float C );
int  __vf   VF_tanh(    fVector Y, fVector X, ui size );
int  __vf   VFx_tanh(   fVector Y, fVector X, ui size, float A, float B, float C );
int  __vf   VF_coth(    fVector Y, fVector X, ui size );
int  __vf   VFx_coth(   fVector Y, fVector X, ui size, float A, float B, float C );
int  __vf   VF_sech(    fVector Y, fVector X, ui size );
int  __vf   VFx_sech(   fVector Y, fVector X, ui size, float A, float B, float C );
int  __vf   VF_cosech(  fVector Y, fVector X, ui size );
int  __vf   VFx_cosech( fVector Y, fVector X, ui size, float A, float B, float C );
int  __vf   VF_sech2(   fVector Y, fVector X, ui size );
int  __vf   VFx_sech2(  fVector Y, fVector X, ui size, float A, float B, float C );
int  __vf   VF_Langevin( fVector Y, fVector X, ui size ); /* coth(x)-1/x */
int  __vf   VFx_Langevin(fVector Y, fVector X, ui size, float A, float B, float C );
#define VF_langevin  VF_Langevin
#define VFx_langevin VFx_Langevin

#ifdef __cplusplus
}  // end of extern "C"
#endif


#endif /* __VFMATH_H */
