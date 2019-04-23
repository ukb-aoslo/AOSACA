/*  VUSmath.h

  vector management functions for data type "unsigned short":
  integer arithmetics and mathematics.

  Copyright (c) 1996-2017 by OptiCode - Dr. Martin Sander Software Dev.
  All Rights Reserved.
*/

#ifndef __VUSMATH_H
#define __VUSMATH_H

#if !defined( __VECLIB_H )
   #include <VecLib.h>
#endif

#ifdef __cplusplus
   extern "C" {
#endif

/********************  Comparisons ********************************/

ui   __vf   VUS_cmp_eq0( usVector Y, usVector X, ui size );
ui   __vf   VUS_cmp_ne0( usVector Y, usVector X, ui size );
ui   __vf   VUS_cmp_gt0( usVector Y, usVector X, ui size );

ui   __vf   VUS_cmp_eq0ind( uiVector Ind, usVector X, ui size );
ui   __vf   VUS_cmp_ne0ind( uiVector Ind, usVector X, ui size );
ui   __vf   VUS_cmp_gt0ind( uiVector Ind, usVector X, ui size );

ui   __vf   VUS_cnt_eq0( usVector X, ui size );
ui   __vf   VUS_cnt_ne0( usVector X, ui size );
ui   __vf   VUS_cnt_gt0( usVector X, ui size );

void __vf   VUS_cmpC(    siVector Y, usVector X, ui size, unsigned short C );
ui   __vf   VUS_cmp_eqC( usVector Y, usVector X, ui size, unsigned short C );
ui   __vf   VUS_cmp_neC( usVector Y, usVector X, ui size, unsigned short C );
ui   __vf   VUS_cmp_leC( usVector Y, usVector X, ui size, unsigned short C );
ui   __vf   VUS_cmp_ltC( usVector Y, usVector X, ui size, unsigned short C );
ui   __vf   VUS_cmp_geC( usVector Y, usVector X, ui size, unsigned short C );
ui   __vf   VUS_cmp_gtC( usVector Y, usVector X, ui size, unsigned short C );

ui   __vf   VUS_cmp_eqCind( uiVector Ind, usVector X, ui size, unsigned short C );
ui   __vf   VUS_cmp_neCind( uiVector Ind, usVector X, ui size, unsigned short C );
ui   __vf   VUS_cmp_leCind( uiVector Ind, usVector X, ui size, unsigned short C );
ui   __vf   VUS_cmp_ltCind( uiVector Ind, usVector X, ui size, unsigned short C );
ui   __vf   VUS_cmp_geCind( uiVector Ind, usVector X, ui size, unsigned short C );
ui   __vf   VUS_cmp_gtCind( uiVector Ind, usVector X, ui size, unsigned short C );

ui   __vf   VUS_cnt_eqC( usVector X, ui size, unsigned short C );
ui   __vf   VUS_cnt_neC( usVector X, ui size, unsigned short C );
ui   __vf   VUS_cnt_leC( usVector X, ui size, unsigned short C );
ui   __vf   VUS_cnt_ltC( usVector X, ui size, unsigned short C );
ui   __vf   VUS_cnt_geC( usVector X, ui size, unsigned short C );
ui   __vf   VUS_cnt_gtC( usVector X, ui size, unsigned short C );

void __vf   VUS_cmpV(    siVector Z, usVector X, usVector Y, ui size );
ui   __vf   VUS_cmp_eqV( usVector Z, usVector X, usVector Y, ui size );
ui   __vf   VUS_cmp_neV( usVector Z, usVector X, usVector Y, ui size );
ui   __vf   VUS_cmp_leV( usVector Z, usVector X, usVector Y, ui size );
ui   __vf   VUS_cmp_ltV( usVector Z, usVector X, usVector Y, ui size );
ui   __vf   VUS_cmp_geV( usVector Z, usVector X, usVector Y, ui size );
ui   __vf   VUS_cmp_gtV( usVector Z, usVector X, usVector Y, ui size );

ui   __vf   VUS_cmp_eqVind( uiVector Ind, usVector X, usVector Y, ui size );
ui   __vf   VUS_cmp_neVind( uiVector Ind, usVector X, usVector Y, ui size );
ui   __vf   VUS_cmp_leVind( uiVector Ind, usVector X, usVector Y, ui size );
ui   __vf   VUS_cmp_ltVind( uiVector Ind, usVector X, usVector Y, ui size );
ui   __vf   VUS_cmp_geVind( uiVector Ind, usVector X, usVector Y, ui size );
ui   __vf   VUS_cmp_gtVind( uiVector Ind, usVector X, usVector Y, ui size );

ui   __vf   VUS_cnt_eqV( usVector X, usVector Y, ui size );
ui   __vf   VUS_cnt_neV( usVector X, usVector Y, ui size );
ui   __vf   VUS_cnt_leV( usVector X, usVector Y, ui size );
ui   __vf   VUS_cnt_ltV( usVector X, usVector Y, ui size );
ui   __vf   VUS_cnt_geV( usVector X, usVector Y, ui size );
ui   __vf   VUS_cnt_gtV( usVector X, usVector Y, ui size );

ui   __vf   VUS_cmp_exclrange0C( usVector Y, usVector X, ui size, unsigned short C );
ui   __vf   VUS_cmp_inclrangeCC( usVector Y, usVector X, ui size, unsigned short CLo, unsigned short CHi );
ui   __vf   VUS_cmp_exclrangeCC( usVector Y, usVector X, ui size, unsigned short CLo, unsigned short CHi );

ui   __vf   VUS_cmp_exclrange0Cind( uiVector Ind, usVector X, ui size, unsigned short C );
ui   __vf   VUS_cmp_inclrangeCCind( uiVector Ind, usVector X, ui size, unsigned short CLo, unsigned short CHi );
ui   __vf   VUS_cmp_exclrangeCCind( uiVector Ind, usVector X, ui size, unsigned short CLo, unsigned short CHi );

ui   __vf   VUS_cnt_exclrange0C( usVector X, ui size, unsigned short C );
ui   __vf   VUS_cnt_inclrangeCC( usVector X, ui size, unsigned short CLo, unsigned short CHi );
ui   __vf   VUS_cnt_exclrangeCC( usVector X, ui size, unsigned short CLo, unsigned short CHi );

/******************   Basic  Arithmetics   *************************/

#if (!defined _WIN64)
	void  __vf  VUSo_addC(  usVector Y, usVector X, ui size, unsigned short C );
	void  __vf  VUSo_subC(  usVector Y, usVector X, ui size, unsigned short C );
	void  __vf  VUSo_subrC( usVector Y, usVector X, ui size, unsigned short C );
	void  __vf  VUSo_mulC(  usVector Y, usVector X, ui size, unsigned short C );
#endif
#if defined (V_trapIntError) && (!defined _WIN64)
    #define VUS_addC     VUSo_addC
    #define VUS_subC     VUSo_subC
    #define VUS_subrC    VUSo_subrC
    #define VUS_mulC     VUSo_mulC
#else
    void  __vf  VUS_addC(  usVector Y, usVector X, ui size, unsigned short C );
    void  __vf  VUS_subC(  usVector Y, usVector X, ui size, unsigned short C );
    void  __vf  VUS_subrC( usVector Y, usVector X, ui size, unsigned short C );
    void  __vf  VUS_mulC(  usVector Y, usVector X, ui size, unsigned short C );
#endif

void  __vf  VUS_divC(  usVector Y, usVector X, ui size, unsigned short C );
void  __vf  VUS_divrC( usVector Y, usVector X, ui size, unsigned short C );
void  __vf  VUS_modC(  usVector Y, usVector X, ui size, unsigned short C );
void  __vf  VUS_maxC(  usVector Y, usVector X, ui size, unsigned short C );
void  __vf  VUS_minC(  usVector Y, usVector X, ui size, unsigned short C );
void  __vf  VUS_limit( usVector Y, usVector X, ui size, unsigned short Min, unsigned short Max );

#if (!defined _WIN64)
	void  __vf  VUSo_addV(  usVector Z, usVector X, usVector Y, ui size );
	void  __vf  VUSo_subV(  usVector Z, usVector X, usVector Y, ui size );
	void  __vf  VUSo_subrV( usVector Z, usVector X, usVector Y, ui size );
	void  __vf  VUSo_mulV(  usVector Z, usVector X, usVector Y, ui size );
#endif
#if defined (V_trapIntError) && (!defined _WIN64)
    #define VUS_addV    VUSo_addV
    #define VUS_subV    VUSo_subV
    #define VUS_subrV   VUSo_subrV
    #define VUS_mulV    VUSo_mulV
#else
    void __vf  VUS_addV(  usVector Z, usVector X, usVector Y, ui size );
    void __vf  VUS_subV(  usVector Z, usVector X, usVector Y, ui size );
    void __vf  VUS_subrV( usVector Z, usVector X, usVector Y, ui size );
    void __vf  VUS_mulV(  usVector Z, usVector X, usVector Y, ui size );
#endif
void  __vf  VUS_divV(  usVector Z, usVector X, usVector Y, ui size );
void  __vf  VUS_divrV( usVector Z, usVector X, usVector Y, ui size );
void  __vf  VUS_modV(  usVector Z, usVector X, usVector Y, ui size );
void  __vf  VUS_maxV(  usVector Z, usVector X, usVector Y, ui size );
void  __vf  VUS_minV(  usVector Z, usVector X, usVector Y, ui size );


/******************** Accumulation (Y += X) ******************************/

void __vf VUS_accV(   usVector Y, usVector  X, ui size );
void __vf VUS_accVUB( usVector Y, ubVector  X, ui size );


/*****************   Bit-wise operations  *********************/

void    __vf  VUS_shl( usVector Y, usVector X, ui size, unsigned C );
void    __vf  VUS_shr( usVector Y, usVector X, ui size, unsigned C );

void    __vf  VUS_and( usVector Y, usVector X, ui size, unsigned short C );
void    __vf  VUS_or(  usVector Y, usVector X, ui size, unsigned short C );
void    __vf  VUS_xor( usVector Y, usVector X, ui size, unsigned short C );
void    __vf  VUS_not( usVector Y, usVector X, ui size );

/************  Optical Density Y = log10( X0 / X ) *********************/

int  __vf VUS_ODtoF( fVector OD, usVector X, usVector X0, ui size );
int  __vf VUS_ODtoD( dVector OD, usVector X, usVector X0, ui size );
int  __vf VUS_ODtoFwDark( fVector OD, usVector X, usVector XDark,
                          usVector X0, usVector X0Dark, ui size );
int  __vf VUS_ODtoDwDark( dVector OD, usVector X, usVector XDark,
                          usVector X0, usVector X0Dark, ui size );
void __vf VUS_setODThresh( unsigned short minX, unsigned short minX0 );
#if (defined __BORLANDC__) && !(defined _WIN64)   /* 80-bit reals supported ? */
	int  __vf VUS_ODtoE( eVector OD, usVector X, usVector X0, ui size );
	int  __vf VUS_ODtoEwDark( eVector OD, usVector X, usVector XDark,
                          usVector X0, usVector X0Dark, ui size );
#else
	#define VUS_ODtoE      VUS_ODtoD
	#define VUS_ODtoEwDark VUS_ODtoDwDark
#endif

#ifdef __cplusplus
}  // end of extern "C"
#endif

#endif   /*  __VUSMATH_H    */
