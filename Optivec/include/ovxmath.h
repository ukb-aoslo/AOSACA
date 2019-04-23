/*  ovxmath.h

  extended math library  belonging to OptiVec.

  may contain more functions in future releases.

  Copyright (c) 1996-2017 by OptiCode - Dr. Martin Sander Software Dev.
  All Rights Reserved.
*/

#if !defined( __OVXMATH_H )
#define __OVXMATH_H
#if !defined( __VECLIB_H )
   #include <VecLib.h>
#endif

#define VF_tabsz2 4096
#define VD_tabsz2 4096
#define VE_tabsz2 4096
#define VF_log2tabsz2 12
#define VD_log2tabsz2 12
#define VE_log2tabsz2 12
#if defined _WIN64
    #define VF_tabsz3   2880
    #define VD_tabsz3   2880
    #define VE_tabsz3   2880
#else /* 32-bit only */
    #define VF_tabsz3   720
    #define VD_tabsz3   720
    #define VE_tabsz3   720
#endif
#ifdef __BORLANDC__
    #define _VCDAT _cdecl
#else
    #define _VCDAT
#endif

#ifdef __cplusplus
extern "C" {
#endif

extern float    _VCDAT  VF_sintab2[ VF_tabsz2+1 ];
extern float    _VCDAT  VF_sintab3[ VF_tabsz3+1 ];
extern float    _VCDAT  VF_tantab2[ VF_tabsz2+1 ];
extern float    _VCDAT  VF_tantab3[ VF_tabsz3+1 ];
extern float    _VCDAT  VF_cosectab2[ VF_tabsz2+1 ];
extern float    _VCDAT  VF_cosectab3[ VF_tabsz3+1 ];
extern double   _VCDAT  VD_sintab2[ VD_tabsz2+1 ];
extern double   _VCDAT  VD_sintab3[ VD_tabsz3+1 ];
extern double   _VCDAT  VD_tantab2[ VD_tabsz2+1 ];
extern double   _VCDAT  VD_tantab3[ VD_tabsz3+1 ];
extern double   _VCDAT  VD_cosectab2[ VD_tabsz2+1 ];
extern double   _VCDAT  VD_cosectab3[ VD_tabsz3+1 ];
#if (defined __BORLANDC__) && !(defined _WIN64)  /* only Borland C++ support 80-bit reals */
	extern extended _VCDAT  VE_sintab2[ VE_tabsz2+1 ];
	extern extended _VCDAT  VE_sintab3[ VE_tabsz3+1 ];
	extern extended _VCDAT  VE_tantab2[ VE_tabsz2+1 ];
	extern extended _VCDAT  VE_tantab3[ VE_tabsz3+1 ];
	extern extended _VCDAT  VE_cosectab2[ VE_tabsz2+1 ];
	extern extended _VCDAT  VE_cosectab3[ VE_tabsz3+1 ];
#endif

int         __vf  isint( double x );
int         __vf  isintl( extended x );
#define           iseven( x )  !(x & 1)    /* for all integer types */
#define           sispositive( x )  !(x & HIBITS)  /* for short int */
#define           ispositive( x )   !(x & HIBITI)  /* for int */
#define           lispositive( x )  !(x & HIBITL)  /* for long int */
int         __vf  sisipow2( unsigned short x );
int         __vf  lisipow2( unsigned long x );
int         __vf  ui_isipow2( ui x );
unsigned	__vf  u_ceil2n( unsigned x );
ui			__vf  ui_ceil2n( ui x );
unsigned    __vf  ui_ceil_log2( ui x );
#ifdef _WIN64
	typedef struct qdiv_t {
		size_t quot;
		size_t rem;
	} qdiv_t;
	qdiv_t __vf qdiv( size_t _Numerator, size_t _Denominator);
#endif
#ifdef __cplusplus
}  // end of extern "C"
#endif
#undef _VCDAT
#endif /* __OVXMATH_H */
