/*	CFMATH.H

	Complex library for the languages C and C++.

	This header file contains all definitions for
	single-precision complex numbers (complex float).

	Copyright (c) 1996-2017 by OptiCode - Dr. Martin Sander Software Dev.
	Address of the author:
			OptiCode - Dr. Martin Sander Software Dev.
			Brahmsstr. 6
			D-32756 Detmold
			Germany
			optivec@gmx.de
			http://www.optivec.com
*/


#ifndef __CFMATH_H
#define __CFMATH_H

#if !defined( _CMATH_DEFS )
	#ifdef __BORLANDC__
		#pragma option -a- /* avoid insertion of dummy bytes in eComplex */
	#else /* Visual C++ */
	//	#pragma pack( push,1 )
	#endif 
	typedef struct {float	Re,  Im;}  fComplex;
	typedef struct {double	Re,  Im;}  dComplex;
	typedef struct {float	Mag, Arg;} fPolar;
	typedef struct {double	Mag, Arg;} dPolar;
	#if (defined __BORLANDC__) && !(defined _WIN64)
		typedef long double	extended;
		typedef struct {extended Re,  Im;}  eComplex;
		typedef struct {extended Mag, Arg;} ePolar;
		#pragma option -a.
	#else /* Visual C++ */
		typedef  double extended; /* Visual C++ does not support
								 80-bit IEEE numbers. So make
								 extended equal to double	*/
		typedef dComplex  eComplex;
		typedef dPolar	ePolar;
		#ifdef _MSC_VER
		//	#pragma pack( pop )
		#else
			#ifdef __BORLANDC__
				#pragma option -a.
			#endif
		#endif
	#endif	/* restore default data packing  */
	typedef fComplex fcomplex;
	typedef dComplex dcomplex;
	typedef eComplex ecomplex;
	typedef fPolar fpolar;
	typedef dPolar dpolar;
	typedef ePolar epolar;  // tolerate all-lower case
	#define _CMATH_DEFS
#endif
#ifdef __BORLANDC__
	#include <_defs.h>
	#define  _VFAR
	#if (__BORLANDC__ >= 0x450)
		 #define __cmf _RTLENTRY _EXPFUNC
	#else
		 #define __cmf  _Cdecl _FARFUNC
	#endif
	#if __BORLANDC__ < 0x500
		#define VBOOL int
	#else
		#define VBOOL bool
	#endif
#else  /* Visual C++, Optima++ */
	#define _VFAR
	#define __cmf __cdecl
	#define VBOOL int
#endif
#define _VFARC const _VFAR

/*  first the constructors:  */
#ifdef __cplusplus
	/* since fComplex and fPolar are declared as structs instead of classes,
	the constructors cannot get the names "fComplex" and "fPolar" here.	*/
  #ifndef _FCPLX_DEFINED
  inline fComplex __cmf fcplx( float __ReVal )
  {	fComplex Result;
	Result.Re = __ReVal;
	Result.Im = 0.0f;
	return Result;
  }

  inline fPolar __cmf fpolr( float __MagVal )
  {	fPolar Result;
	Result.Mag = __MagVal;
	Result.Arg = 0.0f;
	return Result;
  }

	// down-conversions from double and extended precision
	// (with OVERFLOW error handling):
  fComplex __cmf fcplx( dComplex __zd );
  #if defined __COMPLEX_H
	fComplex __cmf fcplx( complex __z );
  #endif
  fPolar __cmf fpolr( dPolar __pd );
  #if (defined __BORLANDC__) && !(defined _WIN64)
	fComplex __cmf fcplx( eComplex __ze );
	fPolar __cmf fpolr( ePolar __pe );
  #else
	#ifdef _CMATH_CLASSDEFS
		fComplex __cmf fcplx( complex<long double> __ze );
		fPolar __cmf fpolr( polar<long double> __pe );
	#endif
  #endif
	//  identity:
  inline fComplex __cmf fcplx( fComplex __zf )
  {	return __zf;  } 
  inline fPolar	__cmf fpolr( fPolar __pf )
  {	return __pf;  }

	// interconversions of Cartesian and polar
  fComplex __cmf fcplx( fPolar	__pf );
  fComplex __cmf fcplx( dPolar	__pd );
  fPolar	__cmf fpolr( fComplex __zf );
  fPolar	__cmf fpolr( dComplex __zd );
  #if (defined __BORLANDC__) && !(defined _WIN64)
	fComplex __cmf fcplx( ePolar	__pe );
	fPolar	__cmf fpolr( eComplex __ze );
  #else
	#ifdef _CMATH_CLASSDEFS
		fComplex __cmf fcplx( polar<long double> __pe );
		fPolar __cmf fpolr( complex<long double> __ze );
	#endif
  #endif
  #define _FCPLX_DEFINED
  #endif  // _FCPLX_DEFINED
#endif  // __cplusplus

#if defined __cplusplus && !defined _CMATH_CLASSDEFS
extern "C" {  // the following functions cannot be "extern C",
#endif		// if fComplex is a class

	/* basic form of constructor for C and C++ : */
fComplex __cmf fcplx( float __ReVal,  float __ImVal );
fPolar	__cmf fpolr( float __MagVal, float __ArgVal );

	/* plain-C version of conversions: */

#if !defined _CMATH_CLASSDEFS /* declared in <newcplx.h> */
	fComplex __cmf cdtocf( dComplex __zd );
	fPolar	__cmf pdtopf( dPolar	__pd );
	fComplex __cmf pftocf( fPolar	__pf );
	fComplex __cmf pdtocf( dPolar	__pd );
	fPolar	__cmf cftopf( fComplex __zf );
	fPolar	__cmf cdtopf( dComplex __zd );
	#if (defined __BORLANDC__) && !(defined _WIN64)
		fComplex __cmf cetocf( eComplex __ze );
		fPolar	__cmf petopf( ePolar	__pe );
		fComplex __cmf petocf( ePolar	__pe );
		fPolar	__cmf cetopf( eComplex __ze );
	#else	/* extended = double */
		#define cetocf cdtocf
		#define petopf pdtopf
		#define petocf pdtocf
		#define cetopf cdtopf
	#endif
#endif

	/* Basic complex operations. They are defined both
	for C and C++. However, for C++ you may as well use the
	overloaded operators and functions defined further below. */
#define		 cf_real( z )  (z).Re
#define		 cf_imag( z )  (z).Im
#define		 pf_abs(  p )  (p).Mag
#define		 pf_arg(  p )  (p).Arg

fComplex __cmf  cf_neg(  fComplex __z );
fComplex __cmf  cf_conj( fComplex __z );
fPolar	__cmf  pf_neg(  fPolar	__p );
fPolar	__cmf  pf_conj( fPolar	__p );
fPolar	__cmf  pf_principal( fPolar __p );
#if defined __cplusplus && !defined _CMATH_CLASSDEFS
}
#endif
#ifdef __cplusplus  // even if _CMATH_CLASSDEFS
	extern "C" {
#endif
float __cmf  cf_norm( fComplex __z );
float __cmf  cf_arg(  fComplex __z );
float __cmf  pf_norm( fPolar __p );
float __cmf  pf_real( fPolar __p );
float __cmf  pf_imag( fPolar __p );
#ifdef __cplusplus
	}
#endif
#if defined __cplusplus && !defined _CMATH_CLASSDEFS
extern "C" {  // the following functions cannot be "extern C",
#endif		// if fComplex identical with complex<float>
fComplex __cmf  cf_polar(	float __mag, float __angle );
fComplex __cmf  cf_magargtoc(float __mag, float __angle); /* same as cf_polar */
fPolar	__cmf  pf_complex( float __re,  float __im );
fPolar	__cmf  pf_reimtop( float __re,  float __im ); /* same as pf_complex */

fComplex __cmf  cf_add(	fComplex __x, fComplex __y );
fComplex __cmf  cf_addRe( fComplex __x, float __yRe );
fComplex __cmf  cf_sub(	fComplex __x, fComplex __y );
fComplex __cmf  cf_subRe( fComplex __x, float __yRe );  /* x - yRe */
fComplex __cmf  cf_subrRe( fComplex __x, float __yRe ); /* yRe - x */
fComplex __cmf  cf_mul(	fComplex __x, fComplex __y );
fComplex __cmf  cf_mulRe( fComplex __x, float __yRe );
fComplex __cmf  cf_div(	fComplex __x, fComplex __y );
fComplex __cmf  cf_divRe( fComplex __x, float __yRe );	/*  x / yRe  */
fComplex __cmf  cf_divrRe( fComplex __x, float __yRe );  /*  yRe / x  */

fPolar	__cmf  pf_mul(	fPolar	__x, fPolar	__y );
fPolar	__cmf  pf_mulRe(  fPolar	__x, float __yRe );
fPolar	__cmf  pf_div(	fPolar	__x, fPolar	__y );
fPolar	__cmf  pf_divRe(  fPolar	__x, float __yRe );	/*  x / yRe  */
fPolar	__cmf  pf_divrRe( fPolar	__x, float __yRe );  /*  yRe / x  */

/*  mathematical functions with error handling through _matherr: */
#ifdef __cplusplus  // even if _CMATH_CLASSDEFS
	extern "C" float  __cmf  cf_abs(  fComplex __z );
#else
	float  __cmf  cf_abs(  fComplex __z );
#endif
fComplex __cmf  cf_acos( fComplex __z );
fComplex __cmf  cf_asin( fComplex __z );
fComplex __cmf  cf_atan( fComplex __z );
fComplex __cmf  cf_cos(  fComplex __z );
fComplex __cmf  cf_cosh( fComplex __z );
fComplex __cmf  cf_cubic( fComplex __z );  /* raise to the third power */
fComplex __cmf  cf_exp(  fComplex __z );
fPolar	__cmf  cf_exptop(  fComplex __z ); /* exp with result as fPolar */
fComplex __cmf  cf_inv(  fComplex __z );	/*	1.0 / z	*/
fComplex __cmf  cf_ipow( fComplex __z, int __exponent );
											 /* raise z to integer power */
fComplex __cmf  cf_ln(	fComplex __z );
fComplex __cmf  cf_log(	fComplex __z ); /* same as cf_ln */
fComplex __cmf  cf_log2(  fComplex __z );
fComplex __cmf  cf_log10( fComplex __z );
fComplex __cmf  cf_pow( fComplex __base, fComplex __exponent );
fComplex __cmf  cf_powReBase( float __base, fComplex __exponent ); /* power of real base */
fComplex __cmf  cf_powReExpo( fComplex __base, float __exponent ); /* raise z to real power */
						 /* for integer exponents, use cf_ipow ! */
fComplex __cmf  cf_quartic( fComplex __z );  /* raise to the fourth power */
fComplex __cmf  cf_sin(  fComplex __z );
fComplex __cmf  cf_sinh( fComplex __z );
fComplex __cmf  cf_square( fComplex __z );
fComplex __cmf  cf_sqrt( fComplex __z );
fComplex __cmf  cf_tan(  fComplex __z );
fComplex __cmf  cf_tanh( fComplex __z );

		/* some of the mathematical functions also for polar: */
fPolar	__cmf  pf_cubic( fPolar	__p );  /* raise to the third power */
fPolar	__cmf  pf_inv(  fPolar	__p );	/*	1.0 / z	*/
fPolar	__cmf  pf_ipow( fPolar	__p, int __exponent );
											 /* raise z to integer power */
fComplex __cmf  pf_lntoc(	fPolar	__p );
fComplex __cmf  pf_logtoc(	fPolar	__p ); /* same as pf_lntocf */
fComplex __cmf  pf_log2toc(  fPolar	__p );
fComplex __cmf  pf_log10toc( fPolar	__p );
fPolar	__cmf  pf_powReExpo( fPolar	__base, float __exponent ); /* raise z to real power */
						 /* for integer exponents, use pf_ipow ! */
fPolar	__cmf  pf_quartic( fPolar	__p );  /* raise to the fourth power */
fPolar	__cmf  pf_square( fPolar	__p );
fPolar	__cmf  pf_sqrt( fPolar	__p );

#if defined __cplusplus && !defined _CMATH_CLASSDEFS
}	//  end of the extern "C" statement
fPolar	__cmf  pf_principal( float __mag, float __angle );
		// this overload cannot be extern C
#endif

#if defined __cplusplus && !defined __STD_COMPLEX && !defined __NEWCPLX_H
	/* in addition to the basic operations defined above for C,
	here is the same complete set of overloaded operators and
	functions as offered by <newcplx.h> for the complex classes.  */

	inline float real( fComplex _VFARC & __z )
	{
		return __z.Re;
	}

	inline float imag( fComplex _VFARC & __z )
	{
		return __z.Im;
	}

	inline fComplex neg( fComplex _VFARC & __z1 )
	{	fComplex Result;
		Result.Re = -__z1.Re;
		Result.Im = -__z1.Im;
		return Result;
	}

	inline fComplex conj( fComplex _VFARC & __z)
	{	fComplex Result;
		Result.Re =  __z.Re;
		Result.Im = -__z.Im;
		return Result;
	}

	float	__cmf norm( fComplex __z );
	float	__cmf arg(  fComplex __z );
	fComplex __cmf magargtoc( float Mag, float Angle );

  //  unary operators:

  inline fComplex _VFAR & operator +( fComplex _VFAR & __z1 )
  {
	return __z1;
  }

  inline fComplex operator -( fComplex _VFARC & __z1 )
  {	fComplex Result;
	Result.Re = -__z1.Re;
	Result.Im = -__z1.Im;
	return Result;
  }

  //  binary operators:

  inline fComplex operator +( fComplex _VFARC & __z1, fComplex _VFARC & __z2 )
  {	fComplex Result;
	Result.Re = __z1.Re + __z2.Re;
	Result.Im = __z1.Im + __z2.Im;
	return Result;
  }

  inline fComplex operator +( fComplex _VFARC & __z1, float __z2Re )
  {	fComplex Result;
	Result.Re = __z1.Re + __z2Re;
	Result.Im = __z1.Im;
	return Result;
  }

  inline fComplex operator +( float __z1Re, fComplex _VFARC & __z2 )
  {	fComplex Result;
	Result.Re = __z1Re + __z2.Re;
	Result.Im = __z2.Im;
	return Result;
  }

  inline fComplex operator -( fComplex _VFARC & __z1, fComplex _VFARC & __z2 )
  {	fComplex Result;
	Result.Re = __z1.Re - __z2.Re;
	Result.Im = __z1.Im - __z2.Im;
	return Result;
  }

  inline fComplex operator -( fComplex _VFARC & __z1, float __z2Re )
  {	fComplex Result;
	Result.Re = __z1.Re - __z2Re;
	Result.Im = __z1.Im;
	return Result;
  }

  inline fComplex operator -( float __z1Re, fComplex _VFARC & __z2 )
  {	fComplex Result;
	Result.Re = __z1Re - __z2.Re;
	Result.Im = -__z2.Im;
	return Result;
  }

  inline fComplex operator *( fComplex _VFARC & __z1, fComplex _VFARC & __z2 )
  {	fComplex Result;
	Result.Re  = __z1.Re * __z2.Re - __z1.Im * __z2.Im;
	Result.Im  = __z1.Re * __z2.Im + __z1.Im * __z2.Re;
	return Result;
  }

  inline fComplex operator *( fComplex _VFARC & __z1, float __z2Re )
  {	fComplex Result;
	Result.Re = __z1.Re * __z2Re;
	Result.Im = __z1.Im * __z2Re;
	return Result;
  }

  inline fComplex operator *( float __z1Re, fComplex _VFARC & __z2 )
  {	fComplex Result;
	Result.Re  = __z1Re * __z2.Re;
	Result.Im  = __z1Re * __z2.Im;
	return Result;
  }

  inline fComplex operator /( fComplex _VFARC & __z1, fComplex _VFARC & __z2 )
  {	fComplex Result;
	double denom;
	Result.Re = (float)(((double)(__z1.Re) * __z2.Re + (double)(__z1.Im) * __z2.Im) /
		(denom = (double)(__z2.Re) * __z2.Re + (double)(__z2.Im) * __z2.Im));
	Result.Im = (float)(((double)(__z1.Im) * __z2.Re - (double)(__z1.Re) * __z2.Im ) / denom);
	return Result;
  }

  inline fComplex operator /( fComplex _VFARC & __z1, float __z2Re )
  {	fComplex Result;
	Result.Re = __z1.Re / __z2Re;
	Result.Im = __z1.Im / __z2Re;
	return Result;
  }

  inline fComplex operator /( float __z1Re, fComplex _VFARC & __z2 )
  {	fComplex Result;
	double denom;
	Result.Re = (float)(((double)(__z1Re) * __z2.Re) /
		(denom = (double)(__z2.Re) * __z2.Re + (double)(__z2.Im) * __z2.Im));
	Result.Im = -(float)(((double)(__z1Re) * __z2.Im ) / denom);
	return Result;
  }

	/* compound-assignment operators:  */
  inline fComplex _VFAR & operator +=( fComplex _VFAR & __z1, fComplex _VFARC & __z2 )
  {
	__z1.Re += __z2.Re;
	__z1.Im += __z2.Im;
	return __z1;
  }

  inline fComplex _VFAR & operator +=( fComplex _VFAR & __z1, float __z2Re )
  {
	__z1.Re += __z2Re;
	return __z1;
  }

  inline fComplex _VFAR & operator -=( fComplex  _VFAR & __z1, fComplex _VFARC & __z2 )
  {
	__z1.Re -= __z2.Re;
	__z1.Im -= __z2.Im;
	return __z1;
  }

  inline fComplex _VFAR & operator -=( fComplex _VFAR & __z1, float __z2Re )
  {
	__z1.Re -= __z2Re;
	return __z1;
  }

  inline fComplex _VFAR & operator *=( fComplex _VFAR & __z1, fComplex _VFARC & __z2 )
  {
	float tmpRe;
	tmpRe	= __z1.Re * __z2.Re - __z1.Im * __z2.Im;
	__z1.Im = __z1.Re * __z2.Im + __z1.Im * __z2.Re;
	__z1.Re = tmpRe;
	return __z1;
  }

  inline fComplex _VFAR & operator *=( fComplex _VFAR & __z1, float __z2Re )
  {
	__z1.Re *= __z2Re;
	__z1.Im *= __z2Re;
	return __z1;
  }

  inline fComplex _VFAR & operator /=( fComplex _VFAR & __z1, fComplex _VFARC & __z2 )
  {	double denom;
	float  tmpRe;
	tmpRe = (float)(((double)(__z1.Re) * __z2.Re + (double)(__z1.Im) * __z2.Im) /
		(denom = (double)(__z2.Re) * __z2.Re + (double)(__z2.Im) * __z2.Im));
	__z1.Im = (float)(((double)(__z1.Im) * __z2.Re - (double)(__z1.Re) * __z2.Im ) / denom);
	__z1.Re = tmpRe;
	return __z1;
  }

  inline fComplex _VFAR & operator /=( fComplex _VFAR & __z1, float __z2Re )
  {
	__z1.Re /= __z2Re;
	__z1.Im /= __z2Re;
	return __z1;
  }

  inline VBOOL operator ==( fComplex _VFARC & __z1, fComplex _VFARC & __z2 )
  {
	return (__z1.Re == __z2.Re) && (__z1.Im == __z2.Im );
  }

  inline VBOOL operator ==( fComplex _VFARC & __z1, float __z2Re )
  {
	return (__z1.Re == __z2Re) && (__z1.Im == 0.0 );
  }

  inline VBOOL operator !=( fComplex _VFARC & __z1, fComplex _VFARC & __z2 )
  {
	return (__z1.Re != __z2.Re) || (__z1.Im != __z2.Im );
  }

  inline VBOOL operator !=( fComplex _VFARC & __z1, float __z2Re )
  {
	return (__z1.Im != 0.0 ) || (__z1.Re != __z2Re);
  }

  /* now the polar functions and operators: */

	float  __cmf real(  fPolar __p );
	float  __cmf imag(  fPolar __p );
	fPolar __cmf reimtop( float __Re, float __Im );
	inline float norm( fPolar _VFARC & __p )
	{
		return __p.Mag * __p.Mag;
	}

	inline float arg( fPolar _VFARC & __p )
	{
		return __p.Arg;
	}
	fPolar  __cmf neg( fPolar __p );

	inline fPolar conj( fPolar _VFARC & __p)
	{	fPolar Result;
		Result.Mag =  __p.Mag;
		Result.Arg = -__p.Arg;
		return Result;
	}


  //  unary operators:

  inline fPolar _VFAR & operator +( fPolar _VFAR & __p1 )
  {
	return __p1;
  }

  inline fPolar operator -( fPolar _VFARC & __p1 )
  {
	return neg( __p1 );
  }

  //  binary operators:

  inline fPolar operator *( fPolar _VFARC & __p1, fPolar _VFARC & __p2 )
  {	fPolar Result;
	Result.Mag  = __p1.Mag * __p2.Mag;
	Result.Arg  = __p1.Arg + __p2.Arg;
	return Result;
  }

  inline fPolar operator *( fPolar _VFARC & __p1, float __z2Re )
  {	fPolar Result;
	Result.Mag  = __p1.Mag * __z2Re;
	Result.Arg  = __p1.Arg;
	return Result;
  }

  inline fPolar operator *( float __z1Re, fPolar _VFARC & __p2 )
  {	fPolar Result;
	Result.Mag  = __p2.Mag * __z1Re;
	Result.Arg  = __p2.Arg;
	return Result;
  }

  inline fPolar operator /( fPolar _VFARC & __p1, fPolar _VFARC & __p2 )
  {	fPolar Result;
	Result.Mag  = __p1.Mag / __p2.Mag;
	Result.Arg  = __p1.Arg - __p2.Arg;
	return Result;
  }

  inline fPolar operator /( fPolar _VFARC & __p1, float __z2Re )
  {	fPolar Result;
	Result.Mag  = __p1.Mag / __z2Re;
	Result.Arg  = __p1.Arg;
	return Result;
  }

  fPolar __cmf operator /( float __z1Re, fPolar _VFARC & __p2 );

	/* compound-assignment operators:  */
  inline fPolar _VFAR & operator *=( fPolar _VFAR & __p1, fPolar _VFARC & __p2 )
  {
	__p1.Mag *= __p2.Mag;
	__p1.Arg += __p2.Arg;
	return __p1;
  }

  inline fPolar _VFAR & __cmf operator *=( fPolar _VFAR & __p1, float __z2Re )
  {
	__p1.Mag *= __z2Re;
	return __p1;
  }

  inline fPolar _VFAR & operator /=( fPolar _VFAR & __p1, fPolar _VFARC & __p2 )
  {
	__p1.Mag /= __p2.Mag;
	__p1.Arg -= __p2.Arg;
	return __p1;
  }

  inline fPolar _VFAR & __cmf operator /=( fPolar _VFAR & __p1, float __z2Re )
  {
	__p1.Mag /= __z2Re;
	return __p1;
  }

  inline VBOOL operator ==( fPolar _VFARC & __p1, fPolar _VFARC & __p2 )
  {
	return (__p1.Mag == __p2.Mag) &&
			 (pf_arg(__p1) == pf_arg(__p2) );
  }

  inline VBOOL operator ==( fPolar _VFARC & __p1, float __p2Re )
  {
	return (__p1.Mag == __p2Re) && (pf_arg(__p1) == 0.0 );
  }

  inline VBOOL operator !=( fPolar _VFARC & __p1, fPolar _VFARC & __p2 )
  {
	return (__p1.Mag != __p2.Mag) || (pf_arg(__p1) != pf_arg(__p2) );
  }

  inline VBOOL operator !=( fPolar _VFARC & __p1, float __p2Re )
  {
	return (__p1.Mag != __p2Re) || (pf_arg(__p1) != 0.0 );
  }


  /*  C++ version of the mathematical functions defined above.
	They use the same code as the C versions. In case of an error,
	you get a message in which the name of the C version is
	stated.
	Note that these functions require complex arguments to be
	passed by value, not by reference, as it is done in the member
	functions of the class complex. In terms of efficiency, this
	is about the same. (The math functions of the class complex
	store complex results at intermediate addresses and copy them
	to the desired address afterwards. This final copy is not
	necessary here.)											 */

  float	__cmf  abs(  fComplex __z );
  fComplex __cmf  acos( fComplex __z );
  fComplex __cmf  asin( fComplex __z );
  fComplex __cmf  atan( fComplex __z );
  fComplex __cmf  cos(  fComplex __z );
  fComplex __cmf  cosh( fComplex __z );
  fComplex __cmf  cubic( fComplex __z );  /* raise to the third power */
  fComplex __cmf  exp(  fComplex __z );
  fPolar	__cmf  exptop(  fComplex __z );
  fComplex __cmf  inv(  fComplex __z );	/*	1.0 / z	*/
  fComplex __cmf  ipow( fComplex __z, int __exponent );
											/* raise z to integer power */
  fComplex __cmf  ln(  fComplex __z );
  fComplex __cmf  log(  fComplex __z );  /* same as ln */
  fComplex __cmf  log2( fComplex __z );
  fComplex __cmf  log10( fComplex __z );
  fComplex __cmf  pow( fComplex __z, fComplex __exponent );
  fComplex __cmf  pow( fComplex __z,  float __exponent ); // identical to powReExpo
  fComplex __cmf  pow( float __base,  fComplex __exponent ); // identical to powReBase
  fComplex __cmf  powReBase( float __base, fComplex __exponent ); // power of real base
  fComplex __cmf  powReExpo( fComplex __z, float __exponent );	// raise z to real power
							// for integer exponents, use ipow !
  fComplex __cmf  quartic( fComplex __z );  // raise to the fourth power
  fComplex __cmf  sin(  fComplex __z );
  fComplex __cmf  sinh( fComplex __z );
  fComplex __cmf  square( fComplex __z );
  fComplex __cmf  sqrt( fComplex __z );
  fComplex __cmf  tan(  fComplex __z );
  fComplex __cmf  tanh( fComplex __z );

			/*  polar math functions:  */
  inline float abs( fPolar _VFARC & __p )
  {
	return __p.Mag;
  }
  fPolar	__cmf  cubic( fPolar	__p );  /* raise to the third power */
  fPolar	__cmf  inv(  fPolar	__p );	/*	1.0 / z	*/
  fPolar	__cmf  ipow( fPolar	__p, int __exponent );
											 /* raise z to integer power */
  fComplex __cmf  lntoc(	fPolar	__p );
  fComplex __cmf  logtoc(	fPolar	__p ); /* same as lntoc */
  fComplex __cmf  log2toc(  fPolar	__p );
  fComplex __cmf  log10toc( fPolar	__p );
  fPolar	__cmf  pow( fPolar	__base, float __exponent ); /* raise z to real power */
  fPolar	__cmf  powReExpo( fPolar	__base, float __exponent ); /* raise z to real power */
						 /* for integer exponents, use ipow ! */
  fPolar	__cmf  quartic( fPolar	__p );  /* raise to the fourth power */
  fPolar	__cmf  square( fPolar	__p );
  fPolar	__cmf  sqrt( fPolar	__p );
#endif //  __cplusplus, not __STD_COMPLEX , __NEWCPLX_H


/***  user-accessible error handling functions, borrowed from VectorLib  ****/

#ifdef __cplusplus
extern "C" {
#endif

void  __cmf  V_noteError( char _VFAR *fname, unsigned why );
void  __cmf  V_printErrorMsg( char _VFAR *ErrMsg );
void  __cmf  V_setErrorEventFile( char _VFAR *filename,  unsigned ScreenAndFile );
void  __cmf  V_closeErrorEventFile( void );

/*** translation of calls to matherr() into _matherr() for BorlandC 4.0+ ***/

#if defined __BORLANDC__ && (__BORLANDC__ >= 0x450) && !defined (__FLAT__)
	 #if !defined( __MATH_H )
			#include <math.h>
	 #endif
	 int  _Cdecl _FARFUNC matherr (struct exception _VFAR *__e);
	 #define NEWMATHERR  \
		 int matherr( struct exception _VFAR *__e ) \
		 {  return( _matherr( __e )); }
#else
	 #define NEWMATHERR
#endif

#ifdef __cplusplus
}	// end of extern "C"
#endif
#endif /*  __CFMATH_H  */
