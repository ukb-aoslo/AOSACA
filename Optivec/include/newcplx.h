/* newcmplx.h

    Include-File for the CMATH Complex Number Library
    replaces <complex.h>.

    Copyright (c) 1996-2017 by OptiCode - Dr. Martin Sander Software Dev.
    Address of the author:
           OptiCode - Dr. Martin Sander Software Dev.
           Brahmsstr. 6
           D-32756 Detmold
           Germany
           optivec@gmx.de
           http://www.optivec.com

    for C++, the following cartesian-complex classes are defined:
    a) if you choose the "classic" Borland C++ style:  class complex;
    b) otherwise:
	   classes complex<float>, complex<double>, and complex<long double>.
    fComplex, dComplex, and eComplex are defined as synonyms for these classes.
    The polar-complex classes are:
       polar<float>, polar<double>, and polar<long double>
    with the synonyms  fPolar, dPolar, and ePolar.

	Fo plain C, use <cmath.h> instead, which declares fComplex, dComplex,
    eComplex, fPolar, dPolar, and ePolar as structs, along with the same
	range of functions as present in the complex C++ classes.

    The classes complex and complex<double> are binary compatible with
    the C struct dComplex. Similarly, complex<float> and struct fComplex
    as well as class complex<long double> and struct eComplex are mutually
    compatible. This is important if one has programs with some modules
    written in C, others in C++.

    All mathematical complex functions are implemented as a library
	written in machine code. In comparison to C++ inline functions,
	this leads to greater precision, greater speed and best security due
	to complete error handling via the standard C error handling functions
	_matherr() (for complex<float>, complex<double>, polar<float>, and
	polar<double>), and _matherrl() (for complex<long double> and
	polar<long double>).

	Note the following important differences between this implementation
	and the one contained in the file <complex.h> delivered with most
	implementations of the Standard C++ Library, coming with the
	Borland and Microsoft C++ compilers:
	-  The real and imaginary parts are declared as public and are referred
	   to as  Re and Im, so that you may always access them as z.Re and z.Im
	   in addition to the member functions real(z) and imag(z);
	-  The argument of all mathematical functions is a value, not a reference.
	-  The following functions and operators have been added to the cartesian
	   complex classes:
	   friend complex  cubic(complex);  //   third power
	   friend complex  inv(complex);    //   1.0 / z
	   friend complex  ipow(complex __base, int __expo);  // integer power
	   friend complex  log2(complex);
	   friend complex  powReExpo(complex __base, double __expoRe);
									   // explicit power with real exponent
	   friend complex  powReBase(double __baseRe, complex __expo);
									   // explicit power of real base
	   friend complex  quartic(complex);  // fourth power
	   friend complex  square(complex);
	   friend int      operator==(complex &, double);
	   friend int      operator!=(complex &, double);
	-  The polar complex classes and all their functions are new.
	   Also new are many of the mixed-accuracy level binary operators.
*/

#ifndef __cplusplus
   #error Must use C++ for complex classes. Include <cmath.h> for the plain-C version
#endif
#if !defined(__NEWCPLX_H)
#define __NEWCPLX_H
#if (defined _COMPLEX_) || (defined _XCOMPLEX_) || (defined __COMPLEX_H) || (defined __STD_COMPLEX) || (defined _STLP_template_complex)
   #error Cannot simultaneously include STL's complex classes and <newcplx.h> !
#endif
#if defined( _CMATH_DEFS )
   #error If you want to include both <cmath.h> and <newcplx.h>, <newcplx.h> must come first !
#endif
#ifdef complex
#undef complex
#endif

#if (!defined _MSC_VER || _MSC_VER <= 1200) && !defined _WIN64 && !defined __clang__
	#if !defined(__IOSTREAM_H) && !defined (_INC_IOSTREAM)
		#include <iostream.h>
	#endif
	#define __cmios ios
	#define __cmistream istream
	#define __cmostream ostream
#else // in 64-bit and in 32-bit MSVC above version 6 as well as BCC32C, use new iostream
	#include <iostream>
	#define __cmios std::ios
	#define __cmistream std::istream
	#define __cmostream std::ostream
#endif
#define  _VFAR  // legacy
#ifdef __BORLANDC__
	 #pragma option -a-
	#if __BORLANDC__ >= 0x550
		#pragma warn -8026
	#endif
	#if (__BORLANDC__ >= 0x450)
		 #define __cmf _RTLENTRY _EXPFUNC
		 #define __cmo _RTLENTRY
	#else
		 #define __cmf  _Cdecl _FARFUNC
		 #define __cmo  _Cdecl
	#endif
	#if __BORLANDC__ < 0x500
		#define VBOOL int
	#else
		#define VBOOL bool
	#endif
#else /* Visual C++ */
	#pragma pack( push,1 )
	#define VBOOL int
	#define __cmf _cdecl
	#define __cmo _cdecl
#endif /* avoid insertion of dummy bytes  */

#define _VFARC const _VFAR

#if defined _MSC_VER || (defined __BORLANDC__ && __BORLANDC__ >= 0x540)
			// explicit specialization of templates
	#define CMATH_NEW_TEMPLATE template<>
#else
	#define CMATH_NEW_TEMPLATE
#endif

#if defined( CMATH_CLASSIC_COMPLEX )
	// Classic Borland C++ class complex only. This has double precision.
	// Complex numbers of float and of long double precision are
	// implemented as structs. So there is no constructor! Moreover, there
	// are no functions defined for float and long double complex numbers
	// or for complex numbers in polar coordinates.

#if !defined(RC_INVOKED)
	#pragma option -Vo-
	#if defined(__STDC__)
		#pragma warn -nak
	#endif
#endif  /* !RC_INVOKED */

#if (__BORLANDC__ >= 0x450)
	class _EXPCLASS complex {
#else
	_CLASSDEF(complex)
	class _CLASSTYPE complex {
#endif
  public:
	// constructors
	complex( double Re_part, double Im_part ) {Re=Re_part; Im=Im_part;}
	complex( double Re_part )  {Re=Re_part; Im=0;}
	complex() {}; // more efficient to have these three separate variants
	// Cartesian complex from polar coordinates; this functions replaces "polar":
	friend complex __cmf magargtoc(double _mag, double _angle=0);
	// basic operations:
	double real() { return Re; }                     // real part
	friend double  __cmf real(complex _VFARC &_z);
	double imag() { return Im; }                     // imaginary part
	friend complex __cmf neg(complex _VFARC &);   // same as unary operator -
	friend complex __cmf conj(complex _VFARC &);  // complex conjugate
    friend double  __cmf norm(complex);          // square of the magnitude
    friend double  __cmf arg(complex);           // angle in the plane

	 // Unary operators
    complex _VFAR & __cmo operator+();
    friend complex __cmf operator-( complex _VFARC &);

    // Binary operators
	friend complex __cmf operator+(complex _VFARC &, complex _VFARC &);
    friend complex __cmf operator+(double, complex _VFARC &);
    friend complex __cmf operator+(complex _VFARC &, double);
	friend complex __cmf operator-(complex _VFARC &, complex _VFARC &);
    friend complex __cmf operator-(double, complex _VFARC &);
	friend complex __cmf operator-(complex _VFARC &, double);
    friend complex __cmf operator*(complex _VFARC &, complex _VFARC &);
    friend complex __cmf operator*(complex _VFARC &, double);
    friend complex __cmf operator*(double, complex _VFARC &);
	friend complex __cmf operator/(complex _VFARC &, complex _VFARC &);
    friend complex __cmf operator/(complex _VFARC &, double);
    friend complex __cmf operator/(double, complex _VFARC &);

    friend VBOOL __cmf operator==(complex _VFARC &, complex _VFARC &);
    friend VBOOL __cmf operator==(complex _VFARC &, double);
    friend VBOOL __cmf operator!=(complex _VFARC &, complex _VFARC &);
    friend VBOOL __cmf operator!=(complex _VFARC &, double);

    complex _VFAR & __cmo operator+=(complex _VFARC &);
    complex _VFAR & __cmo operator+=(double);
	complex _VFAR & __cmo operator-=(complex _VFARC &);
    complex _VFAR & __cmo operator-=(double);
    complex _VFAR & __cmo operator*=(complex _VFARC &);
    complex _VFAR & __cmo operator*=(double);
    complex _VFAR & __cmo operator/=(complex _VFARC &);
	complex _VFAR & __cmo operator/=(double);

    // Overloaded ANSI C math functions with error handling via matherr():
	friend double  __cmf abs(complex);    // complex pointer magnitude
    friend complex __cmf acos(complex);
	friend complex __cmf asin(complex);
    friend complex __cmf atan(complex);
    friend complex __cmf cos(complex);
    friend complex __cmf cosh(complex);
	friend complex __cmf cubic(complex);  // raise to the third power
    friend complex __cmf exp(complex);
    friend complex __cmf inv(complex);    //   1.0 / z
    friend complex __cmf ipow(complex _base, int _IntExpo);  // integer power
    friend complex __cmf ln(complex);
    friend complex __cmf log(complex); // same as ln
    friend complex __cmf log2(complex);
    friend complex __cmf log10(complex);
    friend complex __cmf pow(complex _base, double _expoRe);
    friend complex __cmf powReExpo(complex _base, double _expoRe);
    friend complex __cmf pow(double _baseRe, complex _expo);
	friend complex __cmf powReBase(double _baseRe, complex _expo);
    friend complex __cmf pow(complex _base, complex _expo);
    friend complex __cmf quartic(complex);  // raise to the fourth power
    friend complex __cmf sin(complex);
    friend complex __cmf sinh(complex);
	friend complex __cmf sqrt(complex);
    friend complex __cmf square(complex);
    friend complex __cmf tan(complex);
	friend complex __cmf tanh(complex);

	friend ostream _VFAR & __cmf operator<<(ostream _VFAR &, complex _VFAR &);
    friend istream _VFAR & __cmf operator>>(istream _VFAR &, complex _VFARC &);

// Implementation
	double Re, Im;   // still public!
};
#if !defined( _CMATH_DEFS )
   #define _CMATH_DEFS
   typedef struct {float  Re, Im;} fComplex;
   typedef complex  dComplex;
   #if (defined __BORLANDC__) && !(defined _WIN64)
       typedef long double  extended;
       typedef struct {extended Re, Im;} eComplex;
   #else /* Visual C++, all 64-bit */
       typedef  double extended; /* Win64 and Visual C++ do not support
								 80-bit IEEE numbers. So make
                                 extended equal to double    */
       typedef dComplex  eComplex;
   #endif    /* restore default data packing  */
#endif

// Inline implementation of the simplest functions and operators
// basic operations:
inline double __cmf real( complex _VFARC & __z)
{ return __z.Re; }

inline double __cmf imag( complex _VFARC & __z)
{ return __z.Im; }

inline complex __cmo conj(complex _VFARC & __z)
{    return complex(__z.Re, -__z.Im); }

inline complex __cmo neg(complex _VFARC & __z)
{    return complex(-__z.Re, -__z.Im); }

// unary operators:
inline complex _VFAR & __cmo complex::operator+()
{    return *this; }

inline complex __cmf operator-( complex _VFARC & __z)
{    return complex(-__z.Re, -__z.Im); }


// binary operators:
inline complex __cmo operator+(complex _VFARC & __z1, complex _VFARC & __z2)
{    return complex(__z1.Re + __z2.Re, __z1.Im + __z2.Im); }

inline complex __cmo operator+(double __z1Re, complex _VFARC & __z2)
{    return complex(__z1Re + __z2.Re, __z2.Im); }

inline complex __cmo operator+(complex _VFARC & __z1, double __z2Re)
{    return complex(__z1.Re + __z2Re, __z1.Im); }

inline complex __cmo operator-(complex _VFARC & __z1, complex _VFARC & __z2)
{    return complex(__z1.Re - __z2.Re, __z1.Im - __z2.Im); }

inline complex __cmo operator-(double __z1Re, complex _VFARC & __z2)
{    return complex(__z1Re - __z2.Re, -__z2.Im); }

inline complex __cmo operator-(complex _VFARC & __z1, double __z2Re)
{    return complex(__z1.Re - __z2Re, __z1.Im); }

inline complex __cmo operator*(complex _VFARC & __z1, complex _VFARC & __z2)
{   return complex( __z1.Re * __z2.Re - __z1.Im * __z2.Im,
                    __z1.Re * __z2.Im + __z1.Im * __z2.Re );
}

inline complex __cmo operator*(complex _VFARC & __z1, double __z2Re)
{    return complex(__z1.Re*__z2Re, __z1.Im*__z2Re); }

inline complex __cmo operator*(double __z1Re, complex _VFARC & __z2)
{    return complex(__z2.Re*__z1Re, __z2.Im*__z1Re); }

inline complex __cmo operator /(complex _VFARC & __dividend,
                                complex _VFARC & __divisor )
{     complex     Result;
      long double denom;
      Result.Re = (double)((__dividend.Re *__divisor.Re +
                            __dividend.Im *__divisor.Im) /
		 (denom = (long double)(__divisor.Re) * __divisor.Re +
                  (long double)(__divisor.Im) * __divisor.Im));
      Result.Im = (double)((__dividend.Im * __divisor.Re -
                            __dividend.Re * __divisor.Im ) / denom);
      return Result;
}

inline complex __cmo operator/(complex _VFARC & __dividend, double __divisorRe)
{    return complex(__dividend.Re/__divisorRe, __dividend.Im/__divisorRe); }

inline complex __cmo operator /( double __dividendRe, complex _VFARC & __divisor )
{     complex     Result;
      long double denom;
	  Result.Re = (double)((__dividendRe * __divisor.Re) /
         (denom = (long double)(__divisor.Re) * __divisor.Re +
                  (long double)(__divisor.Im) * __divisor.Im));
	  Result.Im = -(double)((__dividendRe * __divisor.Im ) / denom);
      return Result;
}

inline complex _VFAR & __cmo complex::operator+=(complex _VFARC & __z2)
{   Re += __z2.Re;
    Im += __z2.Im;
    return *this;
}

inline complex _VFAR & __cmo complex::operator+=(double __z2Re)
{   Re += __z2Re;
    return *this;
}

inline complex _VFAR & __cmo complex::operator-=(complex _VFARC & __z2)
{   Re -= __z2.Re;
    Im -= __z2.Im;
    return *this;
}

inline complex _VFAR & __cmo complex::operator-=(double __z2Re)
{   Re -= __z2Re;
    return *this;
}

inline complex _VFAR & __cmo complex::operator*=(double __z2Re)
{   Re *= __z2Re;
	Im *= __z2Re;
    return *this;
}

inline complex _VFAR & __cmo complex::operator *=(complex _VFARC & __z2)
{     double tmpRe = Re * __z2.Re - Im * __z2.Im;
			 Im    = Re * __z2.Im + Im * __z2.Re;
      Re = tmpRe;
      return *this;
}

inline complex _VFAR & __cmo complex::operator /=( complex _VFARC & __divisor )
{     long double denom;
      double tmpRe = (double)((Re * __divisor.Re + Im * __divisor.Im) /
        (denom = (long double)(__divisor.Re) * __divisor.Re +
                 (long double)(__divisor.Im) * __divisor.Im));
      Im = (Im * __divisor.Re - Re * __divisor.Im ) / denom;
	  Re = tmpRe;
      return *this;
}

inline complex _VFAR & __cmo complex::operator/=(double __z2Re)
{   Re /= __z2Re;
    Im /= __z2Re;
    return *this;
}

inline VBOOL __cmo operator==(complex _VFARC & __z1, complex _VFARC & __z2)
{   return __z1.Re == __z2.Re && __z1.Im == __z2.Im; }

inline VBOOL __cmo operator==(complex _VFARC & __z1, double __z2Re)
{   return __z1.Re == __z2Re && __z1.Im == 0.0; }

inline VBOOL __cmo operator!=(complex _VFARC & __z1, complex _VFARC & __z2)
{   return __z1.Re != __z2.Re || __z1.Im != __z2.Im; }

inline VBOOL __cmo operator!=(complex _VFARC & __z1, double __z2Re)
{   return __z1.Re != __z2Re || __z1.Im != 0.0; }


#if !defined(RC_INVOKED)
	#if defined(__STDC__)
		#pragma warn .nak
	#endif
	#pragma option -Vo.
#endif  /* !RC_INVOKED */

#else   // not defined( CMATH_CLASSIC_COMPLEX )
		// declare the complex classes for all three levels of precision
		// Although these classes are fully compatible to the complex
		// classes of the Standard C++ Library, keep them out of the
        // standard namespace.
		// Additionally define polar classes and their functions.

template <class T>
class complex;
CMATH_NEW_TEMPLATE class complex<float>;
CMATH_NEW_TEMPLATE class complex<double>;
CMATH_NEW_TEMPLATE class complex<long double>;

template <class T>
class polar;
CMATH_NEW_TEMPLATE class polar<float>;
CMATH_NEW_TEMPLATE class polar<double>;
CMATH_NEW_TEMPLATE class polar<long double>;

#ifdef _MSC_VER
	#pragma warning(disable: 4244)
	// don't complain about conversion of double into float!
#endif

	/* order of declarations and definitions :
		1. overloaded functions which are not members of the classes
		2. actual class definitions
		3. implementation of inline functions

	1. declaration of overloaded functions which are not members of the classes:  */

inline complex<float> __cmf fcplx( float Re_part, float Im_part );
complex<float> __cmf cdtocf( complex<double> cd );
complex<float> __cmf cetocf( complex<long double> ce );
complex<float> __cmf pftocf( polar<float> pf );
complex<float> __cmf pdtocf( polar<double> pd );
complex<float> __cmf petocf( polar<long double> pe );
complex<float> __cmf magargtoc( float __Mag, float __Arg );

inline float __cmf real(complex<float> _VFARC &_z);
inline float __cmf imag(complex<float> _VFARC &_z);
inline complex<float> __cmf neg(complex<float> _VFARC &); // same as unary operator -
inline complex<float> __cmf conj(complex<float> _VFARC &);// complex conjugate
float  __cmf norm(complex<float>);          // square of the magnitude
float  __cmf arg(complex<float>);           // angle in the plane
	 // Unary minus operator:
inline complex<float> __cmf operator-( complex<float> _VFARC &);

	// Binary operators:
inline complex<float> __cmf operator+(complex<float> _VFARC &, complex<float> _VFARC &);
inline complex<float> __cmf operator+(float, complex<float> _VFARC &);
inline complex<float> __cmf operator+(complex<float> _VFARC &, float);
inline complex<float> __cmf operator-(complex<float> _VFARC &, complex<float> _VFARC &);
inline complex<float> __cmf operator-(float, complex<float> _VFARC &);
inline complex<float> __cmf operator-(complex<float> _VFARC &, float);
inline complex<float> __cmf operator*(complex<float> _VFARC &, complex<float> _VFARC &);
inline complex<float> __cmf operator*(complex<float> _VFARC &, float);
inline complex<float> __cmf operator*(float, complex<float> _VFARC &);
inline complex<float> __cmf operator/(complex<float> _VFARC &, complex<float> _VFARC &);
inline complex<float> __cmf operator/(complex<float> _VFARC &, float);
inline complex<float> __cmf operator/(float, complex<float> _VFARC &);
	   // mixed-accuracy binary operators are declared at the higher-accuracy classes
inline VBOOL __cmf operator==(complex<float> _VFARC &, complex<float> _VFARC &);
inline VBOOL __cmf operator==(complex<float> _VFARC &, float);
inline VBOOL __cmf operator!=(complex<float> _VFARC &, complex<float> _VFARC &);
inline VBOOL __cmf operator!=(complex<float> _VFARC &, float);
		// stream operators:
inline __cmistream _VFAR & __cmf operator>>(__cmistream _VFAR &, complex<float> _VFAR &);
inline __cmostream _VFAR & __cmf operator<<(__cmostream _VFAR &, complex<float> _VFARC &);
		// math functions:
float          __cmf abs(complex<float>);
complex<float> __cmf acos(complex<float>);
complex<float> __cmf asin(complex<float>);
complex<float> __cmf atan(complex<float>);
complex<float> __cmf cos(complex<float>);
complex<float> __cmf cosh(complex<float>);
complex<float> __cmf cubic(complex<float>);  // raise to the third power
complex<float> __cmf exp(complex<float>);
complex<float> __cmf inv(complex<float>);    //   1.0 / z
complex<float> __cmf ipow(complex<float> __base, int __expon);  // integer power
complex<float> __cmf ln(complex<float>);
complex<float> __cmf log(complex<float>); // same as ln
complex<float> __cmf log2(complex<float>);
complex<float> __cmf log10(complex<float>);
complex<float> __cmf ln(polar<float>);
complex<float> __cmf log(polar<float>); // same as ln
complex<float> __cmf log2(polar<float>);
complex<float> __cmf log10(polar<float>);
complex<float> __cmf pow(complex<float> __base, float __expon);
complex<float> __cmf powReExpo(complex<float> __base, float __expon);
complex<float> __cmf pow(float __base, complex<float> __expon);
complex<float> __cmf powReBase(float __base, complex<float> __expon);
complex<float> __cmf pow(complex<float> __base, complex<float> __expon);
complex<float> __cmf quartic(complex<float>);  // raise to the fourth power
complex<float> __cmf sin(complex<float>);
complex<float> __cmf sinh(complex<float>);
complex<float> __cmf sqrt(complex<float>);
complex<float> __cmf square(complex<float>);
complex<float> __cmf tan(complex<float>);
complex<float> __cmf tanh(complex<float>);

		// complex<long double>:
		// constructor, conversions:
inline complex<double> __cmf dcplx( double Re_part, double Im_part );
inline complex<double> __cmf cftocd( complex<float> _VFARC &zf );
complex<double> __cmf cetocd( complex<long double> ze );
complex<double> __cmf pftocd( polar<float> pf );
complex<double> __cmf pdtocd( polar<double> pd );
complex<double> __cmf petocd( polar<long double> pe );
complex<double> __cmf magargtoc( double __Mag, double __Arg );
    // basic operations:
inline double __cmf real(complex<double> _VFARC &_z);
inline double __cmf imag(complex<double> _VFARC &_z);
inline complex<double> __cmf neg(complex<double> _VFARC &); // same as unary operator -
inline complex<double> __cmf conj(complex<double> _VFARC &);// complex conjugate
double  __cmf norm(complex<double>);         // square of the magnitude
double  __cmf arg(complex<double>);          // the angle in the plane
		// Unary - operator:
inline complex<double>  __cmf operator-( complex<double> _VFARC &);
        // Binary operators:
inline complex<double> __cmf operator+(complex<double> _VFARC &, complex<double> _VFARC &);
inline complex<double> __cmf operator+(double, complex<double> _VFARC &);
inline complex<double> __cmf operator+(complex<double> _VFARC &, double);
inline complex<double> __cmf operator-(complex<double> _VFARC &, complex<double> _VFARC &);
inline complex<double> __cmf operator-(double, complex<double> _VFARC &);
inline complex<double> __cmf operator-(complex<double> _VFARC &, double);
inline complex<double> __cmf operator*(complex<double> _VFARC &, complex<double> _VFARC &);
inline complex<double> __cmf operator*(complex<double> _VFARC &, double);
inline complex<double> __cmf operator*(double, complex<double> _VFARC &);
complex<double> __cmf operator/(complex<double> _VFARC &, complex<double> _VFARC &);
inline complex<double> __cmf operator/(complex<double> _VFARC &, double);
complex<double> __cmf operator/(double, complex<double> _VFARC &);
        // float-double mixed-accuracy versions:
inline complex<double> __cmf operator+(complex<float> _VFARC &, complex<double> _VFARC &);
inline complex<double> __cmf operator+(complex<double> _VFARC &, complex<float> _VFARC &);
inline complex<double> __cmf operator-(complex<float> _VFARC &, complex<double> _VFARC &);
inline complex<double> __cmf operator-(complex<double> _VFARC &, complex<float> _VFARC &);
inline complex<double> __cmf operator*(complex<float> _VFARC &, complex<double> _VFARC &);
inline complex<double> __cmf operator*(complex<double> _VFARC &, complex<float> _VFARC &);
complex<double> __cmf operator/(complex<float> _VFARC &, complex<double> _VFARC &);
inline complex<double> __cmf operator/(complex<double> _VFARC &, complex<float> _VFARC &);

inline VBOOL __cmf operator==(complex<double> _VFARC &, complex<double> _VFARC &);
inline VBOOL __cmf operator==(complex<double> _VFARC &, double);
inline VBOOL __cmf operator!=(complex<double> _VFARC &, complex<double> _VFARC &);
inline VBOOL __cmf operator!=(complex<double> _VFARC &, double);
			// stream operators:
inline __cmistream _VFAR & __cmf operator>>(__cmistream _VFAR &, complex<double> _VFAR &);
inline __cmostream _VFAR & __cmf operator<<(__cmostream _VFAR &, complex<double> _VFARC &);
		// overloaded math functions:
double          __cmf abs(complex<double>);
complex<double> __cmf acos(complex<double>);
complex<double> __cmf asin(complex<double>);
complex<double> __cmf atan(complex<double>);
complex<double> __cmf cos(complex<double>);
complex<double> __cmf cosh(complex<double>);
complex<double> __cmf cubic(complex<double>);  // raise to the third power
complex<double> __cmf exp(complex<double>);
complex<double> __cmf inv(complex<double>);    //   1.0 / z
complex<double> __cmf ipow(complex<double> __base, int __expon);  // integer power
complex<double> __cmf ln(complex<double>);
complex<double> __cmf log(complex<double>); // same as ln
complex<double> __cmf log2(complex<double>);
complex<double> __cmf log10(complex<double>);
complex<double> __cmf ln(polar<double>);
complex<double> __cmf log(polar<double>); // same as ln
complex<double> __cmf log2(polar<double>);
complex<double> __cmf log10(polar<double>);
complex<double> __cmf pow(complex<double> __base, double __expon);
complex<double> __cmf powReExpo(complex<double> __base, double __expon);
complex<double> __cmf pow(double __base, complex<double> __expon);
complex<double> __cmf powReBase(double __base, complex<double> __expon);
complex<double> __cmf pow(complex<double> __base, complex<double> __expon);
complex<double> __cmf quartic(complex<double>);  // raise to the fourth power
complex<double> __cmf sin(complex<double>);
complex<double> __cmf sinh(complex<double>);
complex<double> __cmf sqrt(complex<double>);
complex<double> __cmf square(complex<double>);
complex<double> __cmf tan(complex<double>);
complex<double> __cmf tanh(complex<double>);

		// complex<long double>:
		// constructor, conversions:
inline complex<long double> __cmf ecplx( long double Re_part, long double Im_part );
inline complex<long double> __cmf cftoce( complex<float> _VFARC &cf );
inline complex<long double> __cmf cdtoce( complex<double> _VFARC &cd );
complex<long double> __cmf pftoce( polar<float> pf );
complex<long double> __cmf pdtoce( polar<double> pd );
complex<long double> __cmf petoce( polar<long double> pe );
complex<long double> __cmf magargtoc( long double __Mag, long double __Arg );
        // basic operations:
inline long double __cmf real(complex<long double> _VFARC &_z);
inline long double __cmf imag(complex<long double> _VFARC &_z);
inline complex<long double> __cmf neg(complex<long double> _VFARC &); // same as unary operator -
inline complex<long double> __cmf conj(complex<long double> _VFARC &);// complex conjugate
long double  __cmf norm(complex<long double>);         // square of the magnitude
long double  __cmf arg(complex<long double>);          // the angle in the plane
		// Unary - operator:
inline complex<long double>  __cmf operator-( complex<long double> _VFARC &);

        // Binary operators:
inline complex<long double> __cmf operator+(complex<long double> _VFARC &, complex<long double> _VFARC &);
inline complex<long double> __cmf operator+(long double, complex<long double> _VFARC &);
inline complex<long double> __cmf operator+(complex<long double> _VFARC &, long double);
inline complex<long double> __cmf operator-(complex<long double> _VFARC &, complex<long double> _VFARC &);
inline complex<long double> __cmf operator-(long double, complex<long double> _VFARC &);
inline complex<long double> __cmf operator-(complex<long double> _VFARC &, long double);
inline complex<long double> __cmf operator*(complex<long double> _VFARC &, complex<long double> _VFARC &);
inline complex<long double> __cmf operator*(complex<long double> _VFARC &, long double);
inline complex<long double> __cmf operator*(long double, complex<long double> _VFARC &);
complex<long double> __cmf operator/(complex<long double> _VFARC & __dividend,
                                                complex<long double> _VFARC & __divisor);
inline complex<long double> __cmf operator/(complex<long double> _VFARC &, long double );
complex<long double> __cmf operator/(long double __dividend,
												complex<long double> _VFARC &__divisor);
        // mixed-accuracy versions:
inline complex<long double> __cmf operator+(complex<float> _VFARC &, complex<long double> _VFARC &);
inline complex<long double> __cmf operator+(complex<long double> _VFARC &, complex<float> _VFARC &);
inline complex<long double> __cmf operator+(complex<double> _VFARC &, complex<long double> _VFARC &);
inline complex<long double> __cmf operator+(complex<long double> _VFARC &, complex<double> _VFARC &);
inline complex<long double> __cmf operator-(complex<float> _VFARC &, complex<long double> _VFARC &);
inline complex<long double> __cmf operator-(complex<long double> _VFARC &, complex<float> _VFARC &);
inline complex<long double> __cmf operator-(complex<double> _VFARC &, complex<long double> _VFARC &);
inline complex<long double> __cmf operator-(complex<long double> _VFARC &, complex<double> _VFARC &);
inline complex<long double> __cmf operator*(complex<float> _VFARC &, complex<long double> _VFARC &);
inline complex<long double> __cmf operator*(complex<long double> _VFARC &, complex<float> _VFARC &);
inline complex<long double> __cmf operator*(complex<double> _VFARC &, complex<long double> _VFARC &);
inline complex<long double> __cmf operator*(complex<long double> _VFARC &, complex<double> _VFARC &);
inline complex<long double> __cmf operator/(complex<long double> _VFARC & __dividend,
                                                complex<float> _VFARC & __divisor);
complex<long double> __cmf operator/(complex<long double> _VFARC & __dividend,
                                                complex<double> _VFARC & __divisor);
complex<long double> __cmf operator/(complex<float> _VFARC & __dividend,
                                                complex<long double> _VFARC & __divisor);
complex<long double> __cmf operator/(complex<double> _VFARC & __dividend,
												complex<long double> _VFARC & __divisor);

inline VBOOL __cmf operator==(complex<long double> _VFARC &, complex<long double> _VFARC &);
inline VBOOL __cmf operator==(complex<long double> _VFARC &, long double);
inline VBOOL __cmf operator!=(complex<long double> _VFARC &, complex<long double> _VFARC &);
inline VBOOL __cmf operator!=(complex<long double> _VFARC &, long double);

		// Stream operators:
inline __cmistream _VFAR & __cmf operator>>(__cmistream _VFAR &,
										complex<long double> _VFAR &);
inline __cmostream _VFAR & __cmf operator<<(__cmostream _VFAR &,
										complex<long double> _VFARC &);
		// Overloaded ANSI C math functions:
long double          __cmf abs(complex<long double>);
complex<long double> __cmf acos(complex<long double>);
complex<long double> __cmf asin(complex<long double>);
complex<long double> __cmf atan(complex<long double>);
complex<long double> __cmf cos(complex<long double>);
complex<long double> __cmf cosh(complex<long double>);
complex<long double> __cmf cubic(complex<long double>);  // raise to the third power
complex<long double> __cmf exp(complex<long double>);
complex<long double> __cmf inv(complex<long double>);    //   1.0 / z
complex<long double> __cmf ipow(complex<long double> __base, int __expon);  // integer power
complex<long double> __cmf ln(complex<long double>);
complex<long double> __cmf log(complex<long double>); // same as ln
complex<long double> __cmf log2(complex<long double>);
complex<long double> __cmf log10(complex<long double>);
complex<long double> __cmf ln(polar<long double>);
complex<long double> __cmf log(polar<long double>); // same as ln
complex<long double> __cmf log2(polar<long double>);
complex<long double> __cmf log10(polar<long double>);
complex<long double> __cmf pow(complex<long double> __base, long double __expon);
complex<long double> __cmf powReExpo(complex<long double> __base, long double __expon);
complex<long double> __cmf pow(long double __base, complex<long double> __expon);
complex<long double> __cmf powReBase(long double __base, complex<long double> __expon);
complex<long double> __cmf pow(complex<long double> __base, complex<long double> __expon);
complex<long double> __cmf quartic(complex<long double>);  // raise to the fourth power
complex<long double> __cmf sin(complex<long double>);
complex<long double> __cmf sinh(complex<long double>);
complex<long double> __cmf sqrt(complex<long double>);
complex<long double> __cmf square(complex<long double>);
complex<long double> __cmf tan(complex<long double>);
complex<long double> __cmf tanh(complex<long double>);

		// polar<float>:
		// constructor, conversions:
inline polar<float> __cmf fpolr( float Mag_part, float Arg_part );
polar<float> __cmf pdtopf( polar<double> pd );
polar<float> __cmf petopf( polar<long double> pe );
polar<float> __cmf cftopf( complex<float> zf );
polar<float> __cmf cdtopf( complex<double> zd );
polar<float> __cmf cetopf( complex<long double> ze );
polar<float> __cmf reimtop( float __Re, float __Im );
	// basic operations:
float __cmf real(polar<float>);
float __cmf imag(polar<float>);
polar<float> __cmf neg(polar<float>); // same as unary operator -
inline polar<float> __cmf conj(polar<float> _VFARC &);// complex conjugate
float  __cmf norm(polar<float>);          // square of the magnitude
inline float  __cmf arg(polar<float> _VFARC &);
		// Unary -operator:
polar<float> __cmf operator-( polar<float> );

    // Binary operators: only * and /, not + and - !
polar<float> __cmf operator*(polar<float> _VFARC &, polar<float> _VFARC &);
polar<float> __cmf operator*(polar<float> _VFARC &, float);
polar<float> __cmf operator*(float, polar<float> _VFARC &);
polar<float> __cmf operator/(polar<float> _VFARC &, polar<float> _VFARC &);
polar<float> __cmf operator/(polar<float> _VFARC &, float);
polar<float> __cmf operator/(float, polar<float> _VFARC &);
       // mixed-accuracy binary operators are declared at the higher-accuracy classes

inline VBOOL __cmf operator==(polar<float> _VFARC &, polar<float> _VFARC &);
inline VBOOL __cmf operator==(polar<float> _VFARC &, float);
inline VBOOL __cmf operator!=(polar<float> _VFARC &, polar<float> _VFARC &);
inline VBOOL __cmf operator!=(polar<float> _VFARC &, float);
		// Stream operators:
inline __cmistream _VFAR & __cmf operator>>(__cmistream _VFAR &, polar<float> _VFAR &);
inline __cmostream _VFAR & __cmf operator<<(__cmostream _VFAR &, polar<float> _VFARC &);

    // Overloaded ANSI C math functions
inline float __cmf abs(polar<float> _VFARC &);
polar<float> __cmf cubic(polar<float>);  // raise to the third power
polar<float> __cmf exptop(complex<float>);
polar<float> __cmf inv(polar<float>);    //   1.0 / z
polar<float> __cmf ipow(polar<float> __base, int __expon);  // integer power
complex<float> __cmf lntoc(polar<float>);
complex<float> __cmf logtoc(polar<float>); // same as lntocomplex
complex<float> __cmf log2toc(polar<float>);
complex<float> __cmf log10toc(polar<float>);
polar<float> __cmf pow(polar<float> __base, float __expon);
polar<float> __cmf powReExpo(polar<float> __base, float __expon);
polar<float> __cmf quartic(polar<float>);  // raise to the fourth power
polar<float> __cmf sqrt(polar<float>);
polar<float> __cmf square(polar<float>);

		// polar<double>:
		// constructor, conversions:
inline polar<double> __cmf dpolr( double Mag_part, double Arg_part );
inline polar<double> __cmf pftopd( polar<float> _VFARC &pf );
polar<double> __cmf petopd( polar<long double> pe );
polar<double> __cmf cftopd( complex<float> zf );
polar<double> __cmf cdtopd( complex<double> zd );
polar<double> __cmf cetopd( complex<long double> ze );
polar<double> __cmf reimtop( double __Re, double __Im );

    // basic operations:
double __cmf real(polar<double>);
double __cmf imag(polar<double>);
polar<double> __cmf neg(polar<double>); // same as unary operator -
inline polar<double> __cmf conj(polar<double> _VFARC &);// complex conjugate
double  __cmf norm(polar<double>);          // square of the magnitude
inline double  __cmf arg(polar<double> _VFARC &);
	// Unary -operator:
polar<double> __cmf operator-( polar<double> );

    // Binary operators: only * and /, not + and - !
polar<double> __cmf operator*(polar<double> _VFARC &, polar<double> _VFARC &);
polar<double> __cmf operator*(polar<double> _VFARC &, double);
polar<double> __cmf operator*(double, polar<double> _VFARC &);
polar<double> __cmf operator/(polar<double> _VFARC &, polar<double> _VFARC &);
polar<double> __cmf operator/(polar<double> _VFARC &, double);
polar<double> __cmf operator/(double, polar<double> _VFARC &);

        // float-double mixed-accuracy versions:
polar<double> __cmf operator*(polar<float> _VFARC &, polar<double> _VFARC &);
polar<double> __cmf operator*(polar<double> _VFARC &, polar<float> _VFARC &);
polar<double> __cmf operator/(polar<float> _VFARC &, polar<double> _VFARC &);
polar<double> __cmf operator/(polar<double> _VFARC &, polar<float> _VFARC &);
       // mixed-accuracy binary operators are declared at the higher-accuracy classes

inline VBOOL __cmf operator==(polar<double> _VFARC &, polar<double> _VFARC &);
inline VBOOL __cmf operator==(polar<double> _VFARC &, double);
inline VBOOL __cmf operator!=(polar<double> _VFARC &, polar<double> _VFARC &);
inline VBOOL __cmf operator!=(polar<double> _VFARC &, double);
	// Stream operators:
inline __cmistream _VFAR & __cmf operator>>(__cmistream _VFAR &, polar<double> _VFAR &);
inline __cmostream _VFAR & __cmf operator<<(__cmostream _VFAR &, polar<double> _VFARC &);
    // Overloaded ANSI C math functions
inline double          __cmf abs(polar<double> _VFARC &);
polar<double>   __cmf cubic(polar<double>);  // raise to the third power
polar<double>   __cmf exptop(complex<double>);
polar<double>   __cmf inv(polar<double>);    //   1.0 / z
polar<double>   __cmf ipow(polar<double> __base, int __expon);  // integer power
complex<double> __cmf lntoc(polar<double>);
complex<double> __cmf logtoc(polar<double>); // same as lntocomplex
complex<double> __cmf log2toc(polar<double>);
complex<double> __cmf log10toc(polar<double>);
polar<double>   __cmf pow(polar<double> __base, double __expon);
polar<double>   __cmf powReExpo(polar<double> __base, double __expon);
polar<double>   __cmf quartic(polar<double>);  // raise to the fourth power
polar<double>   __cmf sqrt(polar<double>);
polar<double>   __cmf square(polar<double>);

		// polar<long double>:
		// constructor, conversions:
inline polar<long double> __cmf epolr( long double Mag_part, long double Arg_part );
inline polar<long double> __cmf pftope( polar<float> _VFARC &pf );
inline polar<long double> __cmf pdtope( polar<double> _VFARC &pd );
polar<long double> __cmf cftope( complex<float> zf );
polar<long double> __cmf cdtope( complex<double> zd );
polar<long double> __cmf cetope( complex<long double> ze );
polar<long double> __cmf reimtop( long double __Re, long double __Im );

    // basic operations:
long double __cmf real(polar<long double>);
long double __cmf imag(polar<long double>);
polar<long double> __cmf neg(polar<long double>); // same as unary operator -
inline polar<long double> __cmf conj(polar<long double> _VFARC &);// complex conjugate
long double  __cmf norm(polar<long double>);          // square of the magnitude
inline long double  __cmf arg(polar<long double> _VFARC &);
		// Unary -operator:
polar<long double> __cmf operator-( polar<long double> );

    // Binary operators: only * and /, not + and - !
polar<long double> __cmf operator*(polar<long double> _VFARC &, polar<long double> _VFARC &);
polar<long double> __cmf operator*(polar<long double> _VFARC &, long double);
polar<long double> __cmf operator*(long double, polar<long double> _VFARC &);
polar<long double> __cmf operator/(polar<long double> _VFARC &, polar<long double> _VFARC &);
polar<long double> __cmf operator/(polar<long double> _VFARC &, long double);
polar<long double> __cmf operator/(long double, polar<long double> _VFARC &);

        // float-long double mixed-accuracy versions:
polar<long double> __cmf operator*(polar<float> _VFARC &, polar<long double> _VFARC &);
polar<long double> __cmf operator*(polar<long double> _VFARC &, polar<float> _VFARC &);
polar<long double> __cmf operator/(polar<float> _VFARC &, polar<long double> _VFARC &);
polar<long double> __cmf operator/(polar<long double> _VFARC &, polar<float> _VFARC &);

	   // mixed-accuracy binary operators are declared at the higher-accuracy classes

inline VBOOL __cmf operator==(polar<long double> _VFARC &, polar<long double> _VFARC &);
inline VBOOL __cmf operator==(polar<long double> _VFARC &, long double);
inline VBOOL __cmf operator!=(polar<long double> _VFARC &, polar<long double> _VFARC &);
inline VBOOL __cmf operator!=(polar<long double> _VFARC &, long double);
		// Stream operators:
inline __cmistream _VFAR & __cmf operator>>(__cmistream _VFAR &, polar<long double> _VFAR &);
inline __cmostream _VFAR & __cmf operator<<(__cmostream _VFAR &, polar<long double> _VFARC &);
    // Overloaded ANSI C math functions
inline long double   __cmf abs(polar<long double> _VFARC &);
polar<long double>   __cmf cubic(polar<long double>);  // raise to the third power
polar<long double>   __cmf exptop(complex<long double>);
polar<long double>   __cmf inv(polar<long double>);    //   1.0 / z
polar<long double>   __cmf ipow(polar<long double> __base, int __expon);  // integer power
complex<long double> __cmf lntoc(polar<long double>);
complex<long double> __cmf logtoc(polar<long double>); // same as lntocomplex
complex<long double> __cmf log2toc(polar<long double>);
complex<long double> __cmf log10toc(polar<long double>);
polar<long double>   __cmf pow(polar<long double> __base, long double __expon);
polar<long double>   __cmf powReExpo(polar<long double> __base, long double __expon);
polar<long double>   __cmf quartic(polar<long double>);  // raise to the fourth power
polar<long double>   __cmf sqrt(polar<long double>);
polar<long double>   __cmf square(polar<long double>);

		/* now the actual class definitions:  */

CMATH_NEW_TEMPLATE class complex<float>
{
  public:
		 // constructors:
	complex( float Re_part, float Im_part ) {Re=Re_part; Im=Im_part;}
	complex( float Re_part )  {Re=Re_part; Im=0;}
	complex() {}; // most efficient to have these as three different constructors!
	complex (polar<float> _VFARC &);
	complex (polar<double> _VFARC &);
	complex (polar<long double> _VFARC &);
	#if !defined _MSC_VER && (!defined __BORLANDC__ || __BORLANDC__ > 0x500)
		complex (complex<float> _VFARC &);
	#endif
	explicit complex (complex<double> _VFARC &);
	explicit complex (complex<long double> _VFARC &);
	   // simple assignments: no OVERFLOW error handling
	complex<float> _VFAR & __cmo  operator=(complex<float> _VFARC &);
    complex<float> _VFAR & __cmo  operator=(complex<double> _VFARC &);
    complex<float> _VFAR & __cmo  operator=(complex<long double> _VFARC &);
	complex<float> _VFAR & __cmo  operator=(float);
    complex<float> _VFAR & __cmo  operator=(double);
    complex<float> _VFAR & __cmo  operator=(long double);
	complex<float> _VFAR & __cmo  operator=(polar<float> _VFARC &);
	complex<float> _VFAR & __cmo  operator=(polar<double> _VFARC &);
    complex<float> _VFAR & __cmo  operator=(polar<long double> _VFARC &);

	// basic operations:
	float real() { return Re; }                              // real part
    float imag() { return Im; }                              // imaginary part

	 // Unary + operator
    complex<float> _VFAR & __cmo operator+();

       //  Compound-assignment operators:
	complex<float> _VFAR & __cmo  operator+=(complex<float> _VFARC &);
    complex<float> _VFAR & __cmo  operator-=(complex<float> _VFARC &);
	complex<float> _VFAR & __cmo  operator*=(complex<float> _VFARC &);
    complex<float> _VFAR & __cmo  operator/=(complex<float> _VFARC &);

	complex<float> _VFAR & __cmo  operator+=(complex<double> _VFARC &);
    complex<float> _VFAR & __cmo  operator-=(complex<double> _VFARC &);
    complex<float> _VFAR & __cmo  operator*=(complex<double> _VFARC &);
	complex<float> _VFAR & __cmo  operator/=(complex<double> _VFARC &);

    complex<float> _VFAR & __cmo  operator+=(complex<long double> _VFARC &);
	complex<float> _VFAR & __cmo  operator-=(complex<long double> _VFARC &);
	complex<float> _VFAR & __cmo  operator*=(complex<long double> _VFARC &);
    complex<float> _VFAR & __cmo  operator/=(complex<long double> _VFARC &);

	complex<float> _VFAR & __cmo  operator+=(float);
	complex<float> _VFAR & __cmo  operator-=(float);
	complex<float> _VFAR & __cmo  operator*=(float);
    complex<float> _VFAR & __cmo  operator/=(float);

	float Re, Im;  // still public!
};

CMATH_NEW_TEMPLATE class  complex<double>
{
  public:
		 // constructors:
	#if !defined __BORLANDC__ || __BORLANDC__ >= 0x450
		complex( double Re_part, double Im_part ) {Re=Re_part; Im=Im_part;}
		complex( double Re_part )  {Re=Re_part; Im=0;}
		complex() {};
			// interconversions between the three levels of accuracy:
			// with OVERFLOW error handling for the down-conversions
		complex (complex<float> _VFARC &);
		complex (polar<float> _VFARC &);
		complex (polar<double> _VFARC &);
		complex (polar<long double> _VFARC &);
	#else // problems with the template definitions in older BC versions
        complex<double>( double Re_part, double Im_part ) {Re=Re_part; Im=Im_part;}
		complex<double>( double Re_part )  {Re=Re_part; Im=0;}
		complex<double>() {};
		complex<double> (complex<float> _VFARC & zf) {Re = zf.Re; Im = zf.Im;}
        complex<double> (polar<float> _VFARC & __p) {*this = pftocd(__p);}
		complex<double> (polar<double> _VFARC & __p) {*this = pdtocd(__p);}
        complex<double> (polar<long double> _VFARC & __p) {*this = petocd(__p);}
	#endif
    #if !defined _MSC_VER && (!defined __BORLANDC__ || __BORLANDC__ > 0x500)
            complex (complex<double> _VFARC &);
    #endif
	#if defined _MSC_VER || (defined __BORLANDC__ && __BORLANDC__ >= 0x500)
        explicit complex (complex<long double> _VFARC &);
    #else
		#ifdef __BORLANDC__  // prior to v5.0
			complex<double> (complex<long double> _VFARC & ze) {*this = cetocd( ze );}
		#else  // Optima++ doesn't like "explicit"
			complex (complex<long double> _VFARC & ze);
        #endif
    #endif
		  // simple assignments: no OVERFLOW error handling
	complex<double> _VFAR & __cmo  operator=(complex<float> _VFARC &);
	complex<double> _VFAR & __cmo  operator=(complex<double> _VFARC &);
    complex<double> _VFAR & __cmo  operator=(complex<long double> _VFARC &);
    complex<double> _VFAR & __cmo  operator=(float);
    complex<double> _VFAR & __cmo  operator=(double);
	complex<double> _VFAR & __cmo  operator=(long double);
	complex<double> _VFAR & __cmo  operator=(polar<float> _VFARC &);
	complex<double> _VFAR & __cmo  operator=(polar<double> _VFARC &);
    complex<double> _VFAR & __cmo  operator=(polar<long double> _VFARC &);

    // basic operations:
	double real() { return Re; }                              // real part
    double imag() { return Im; }                              // imaginary part

	 // Unary + operator
	complex<double> _VFAR & __cmo operator+();

       //  Compound-assignment operators:
    complex<double> _VFAR & __cmo  operator+=(complex<float> _VFARC &);
    complex<double> _VFAR & __cmo  operator-=(complex<float> _VFARC &);
	complex<double> _VFAR & __cmo  operator*=(complex<float> _VFARC &);
	complex<double> _VFAR & __cmo  operator/=(complex<float> _VFARC &);

    complex<double> _VFAR & __cmo  operator+=(complex<double> _VFARC &);
	complex<double> _VFAR & __cmo  operator-=(complex<double> _VFARC &);
    complex<double> _VFAR & __cmo  operator*=(complex<double> _VFARC &);
	complex<double> _VFAR & __cmo  operator/=(complex<double> _VFARC &);

    complex<double> _VFAR & __cmo  operator+=(complex<long double> _VFARC &);
    complex<double> _VFAR & __cmo  operator-=(complex<long double> _VFARC &);
	complex<double> _VFAR & __cmo  operator*=(complex<long double> _VFARC &);
    complex<double> _VFAR & __cmo  operator/=(complex<long double> _VFARC &);

	complex<double> _VFAR & __cmo  operator+=(double);
	complex<double> _VFAR & __cmo  operator-=(double);
	complex<double> _VFAR & __cmo  operator*=(double);
	complex<double> _VFAR & __cmo  operator/=(double);

	double Re, Im;  // still public!
};

CMATH_NEW_TEMPLATE class complex<long double>
{
  public:
		 // constructors:
	#if !defined __BORLANDC__ || __BORLANDC__ >= 0x450
		complex( long double Re_part, long double Im_part ) {Re=Re_part; Im=Im_part;}
		complex( long double Re_part )  {Re=Re_part; Im=0;}
		complex() {};
			// interconversions:
		complex (complex<float> _VFARC &);
		complex (complex<double> _VFARC &);
		complex (polar<float> _VFARC &);
		complex (polar<double> _VFARC &);
        complex (polar<long double> _VFARC &);
	#else // problems with the template definitions in older BC versions
        complex<long double>( long double Re_part, long double Im_part ) {Re=Re_part; Im=Im_part;}
        complex<long double>( long double Re_part )  {Re=Re_part; Im=0;}
		complex<long double>() {};
				// interconversions between the three levels of accuracy:
        complex<long double> (complex<float> _VFARC & zf) {Re = zf.Re; Im = zf.Im;}
		complex<long double> (complex<double> _VFARC & zd) {Re = zd.Re; Im = zd.Im;}
        complex<long double> (polar<float> _VFARC & __p) {*this = pftoce(__p);}
        complex<long double> (polar<double> _VFARC & __p) {*this = pdtoce(__p);}
        complex<long double> (polar<long double> _VFARC & __p) {*this = petoce(__p);}
    #endif
	#if !defined _MSC_VER && (!defined __BORLANDC__ || __BORLANDC__ > 0x500)
        complex (complex<long double> _VFARC &);
	#endif

		  // simple assignments do the same:
	complex<long double> _VFAR & __cmo  operator=(complex<float> _VFARC &);
    complex<long double> _VFAR & __cmo  operator=(complex<double> _VFARC &);
	complex<long double> _VFAR & __cmo  operator=(complex<long double> _VFARC &);
    complex<long double> _VFAR & __cmo  operator=(float);
    complex<long double> _VFAR & __cmo  operator=(double);
    complex<long double> _VFAR & __cmo  operator=(long double);
	complex<long double> _VFAR & __cmo  operator=(polar<float> _VFARC &);
    complex<long double> _VFAR & __cmo  operator=(polar<double> _VFARC &);
    complex<long double> _VFAR & __cmo  operator=(polar<long double> _VFARC &);

        // basic operations:
    long double real() { return Re; }                              // real part
	long double imag() { return Im; }                              // imaginary part

	 // Unary + operator
    complex<long double> _VFAR & __cmo operator+();

       //  Compound-assignment operators:
    complex<long double> _VFAR & __cmo  operator+=(complex<float> _VFARC &);
    complex<long double> _VFAR & __cmo  operator-=(complex<float> _VFARC &);
    complex<long double> _VFAR & __cmo  operator*=(complex<float> _VFARC &);
	complex<long double> _VFAR & __cmo  operator/=(complex<float> _VFARC &);

	complex<long double> _VFAR & __cmo  operator+=(complex<double> _VFARC &);
    complex<long double> _VFAR & __cmo  operator-=(complex<double> _VFARC &);
    complex<long double> _VFAR & __cmo  operator*=(complex<double> _VFARC &);
	complex<long double> _VFAR & __cmo  operator/=(complex<double> _VFARC &);

	complex<long double> _VFAR & __cmo  operator+=(complex<long double> _VFARC &);
    complex<long double> _VFAR & __cmo  operator-=(complex<long double> _VFARC &);
    complex<long double> _VFAR & __cmo  operator*=(complex<long double> _VFARC &);
    complex<long double> _VFAR & __cmo  operator/=(complex<long double> _VFARC &);

    complex<long double> _VFAR & __cmo  operator+=(long double);
    complex<long double> _VFAR & __cmo  operator-=(long double);
	complex<long double> _VFAR & __cmo  operator*=(long double);
    complex<long double> _VFAR & __cmo  operator/=(long double);

    long double Re, Im; // still public!
};


	  //  now the classes for complex numbers in polar representation:

CMATH_NEW_TEMPLATE class polar<float>
{
  public:
		 // constructors:
	#if !defined __BORLANDC__ || __BORLANDC__ >= 0x450
		polar( float Mag_part, float Arg_part ) {Mag=Mag_part; Arg=Arg_part;}
		polar( float Mag_part )  {Mag=Mag_part; Arg=0;}
		polar() {}; // most efficient to have these as three different constructors!
		polar (complex<float> _VFARC &);
		polar (complex<double> _VFARC &);
		polar (complex<long double> _VFARC &);
	#else // problems with the template definitions in older BC versions
        polar<float>( float Mag_part, float Arg_part ) {Mag=Mag_part; Arg=Arg_part;}
        polar<float>( float Mag_part )  {Mag=Mag_part; Arg=0;}
        polar<float>() {};
		polar<float> (complex<float> _VFARC & __z) {*this = cftopf(__z);}
        polar<float> (complex<double> _VFARC & __z) {*this = cdtopf(__z);}
		polar<float> (complex<long double> _VFARC & __z) {*this = cetopf(__z);}
    #endif
    #if !defined _MSC_VER && (!defined __BORLANDC__ || __BORLANDC__ > 0x500)
		polar (polar<float> _VFARC &);
    #endif
	#if defined _MSC_VER || (defined __BORLANDC__ && __BORLANDC__ >= 0x500)
        explicit polar (polar<double> _VFARC &);
        explicit polar (polar<long double> _VFARC &);
	#else
		#ifdef __BORLANDC__   // prior to v5.0
            polar<float> (polar<double> _VFARC & pd) {*this = pdtopf( pd );}
            polar<float> (polar<long double> _VFARC & pe) {*this = petopf( pe );}
        #else // Optima++ doesn't like "explicit"
            polar (polar<double> _VFARC & pd);
            polar (polar<long double> _VFARC & pe);
        #endif
	#endif
       // simple assignments: no OVERFLOW error handling
	polar<float> _VFAR & __cmo  operator=(polar<float> _VFARC &);
    polar<float> _VFAR & __cmo  operator=(polar<double> _VFARC &);
    polar<float> _VFAR & __cmo  operator=(polar<long double> _VFARC &);
    polar<float> _VFAR & __cmo  operator=(float);
    polar<float> _VFAR & __cmo  operator=(double);
	polar<float> _VFAR & __cmo  operator=(long double);
    polar<float> _VFAR & __cmo  operator=(complex<float> _VFARC &);
	polar<float> _VFAR & __cmo  operator=(complex<double> _VFARC &);
    polar<float> _VFAR & __cmo  operator=(complex<long double> _VFARC &);

        // basic operations:
    float mag() { return Mag; }          // magnitude
	float arg() { return Arg; }         // angle, argument

     // Unary +operator
    polar<float> _VFAR & __cmo operator+();

       //  Compound-assignment operators:
	polar<float> _VFAR & __cmo  operator*=(polar<float> _VFARC &);
    polar<float> _VFAR & __cmo  operator/=(polar<float> _VFARC &);

    polar<float> _VFAR & __cmo  operator*=(polar<double> _VFARC &);
	polar<float> _VFAR & __cmo  operator/=(polar<double> _VFARC &);

    polar<float> _VFAR & __cmo  operator*=(polar<long double> _VFARC &);
    polar<float> _VFAR & __cmo  operator/=(polar<long double> _VFARC &);

    polar<float> _VFAR & __cmo  operator*=(float);
    polar<float> _VFAR & __cmo  operator/=(float);
	float Mag, Arg;  // still public!
};

CMATH_NEW_TEMPLATE class polar<double>
{
  public:
		 // constructors:
    #if !defined __BORLANDC__ || __BORLANDC__ >= 0x450
		polar( double Mag_part, double Arg_part ) {Mag=Mag_part; Arg=Arg_part;}
        polar( double Mag_part )  {Mag=Mag_part; Arg=0;}
        polar() {}; // most efficient to have these as three different constructors!
        polar (polar<float> _VFARC &);
		polar (complex<float> _VFARC &);
        polar (complex<double> _VFARC &);
        polar (complex<long double> _VFARC &);
    #else // problems with the template definitions in older BC versions
        polar<double>( double Mag_part, double Arg_part ) {Mag=Mag_part; Arg=Arg_part;}
        polar<double>( double Mag_part )  {Mag=Mag_part; Arg=0;}
        polar<double>() {};
		polar<double> (polar<float> _VFARC & pf) {Mag = pf.Mag; Arg = pf.Arg;}
        polar<double> (complex<float> _VFARC & __z) {*this = cftopd(__z);}
		polar<double> (complex<double> _VFARC & __z) {*this = cdtopd(__z);}
        polar<double> (complex<long double> _VFARC & __z) {*this = cetopd(__z);}
    #endif
    #if !defined _MSC_VER && (!defined __BORLANDC__ || __BORLANDC__ > 0x500)
        polar (polar<double> _VFARC &);
	#endif
	#if defined _MSC_VER || (defined __BORLANDC__ && __BORLANDC__ >= 0x500)
        explicit polar (polar<long double> _VFARC &);
	#else
        #ifdef __BORLANDC__   // prior to v5.0
			polar<double> (polar<long double> _VFARC & pe) {*this = petopd( pe );}
        #else // Optima++ doesn't like "explicit"
			polar (polar<long double> _VFARC & pe);
        #endif
    #endif

	   // simple assignments: no OVERFLOW error handling
    polar<double> _VFAR & __cmo  operator=(polar<float> _VFARC &);
    polar<double> _VFAR & __cmo  operator=(polar<double> _VFARC &);
    polar<double> _VFAR & __cmo  operator=(polar<long double> _VFARC &);
    polar<double> _VFAR & __cmo  operator=(float);
    polar<double> _VFAR & __cmo  operator=(double);
    polar<double> _VFAR & __cmo  operator=(long double);
	polar<double> _VFAR & __cmo  operator=(complex<float> _VFARC &);
    polar<double> _VFAR & __cmo  operator=(complex<double> _VFARC &);
	polar<double> _VFAR & __cmo  operator=(complex<long double> _VFARC &);

        // basic operations:
    double mag() { return Mag; }          // magnitude
	double arg() { return Arg; }         // angle, argument

     // Unary +operator
    polar<double> _VFAR & __cmo operator+();

       //  Compound-assignment operators:
    polar<double> _VFAR & __cmo  operator*=(polar<float> _VFARC &);
	polar<double> _VFAR & __cmo  operator/=(polar<float> _VFARC &);

    polar<double> _VFAR & __cmo  operator*=(polar<double> _VFARC &);
    polar<double> _VFAR & __cmo  operator/=(polar<double> _VFARC &);

    polar<double> _VFAR & __cmo  operator*=(polar<long double> _VFARC &);
    polar<double> _VFAR & __cmo  operator/=(polar<long double> _VFARC &);

    polar<double> _VFAR & __cmo  operator*=(double);
    polar<double> _VFAR & __cmo  operator/=(double);

	double Mag, Arg;  // still public!
};

CMATH_NEW_TEMPLATE class polar<long double>
{
  public:
		 // constructors:
    #if !defined __BORLANDC__ || __BORLANDC__ >= 0x450
        polar( long double Mag_part, long double Arg_part ) {Mag=Mag_part; Arg=Arg_part;}
		polar( long double Mag_part )  {Mag=Mag_part; Arg=0;}
        polar() {}; // most efficient to have these as three different constructors!
            // interconversions between the three levels of accuracy:
        polar (polar<float> _VFARC &);
		polar (polar<double> _VFARC &);
        polar (complex<float> _VFARC &);
        polar (complex<double> _VFARC &);
        polar (complex<long double> _VFARC &);
	#else // problems with the template definitions in older BC versions
        polar<long double>( long double Mag_part, long double Arg_part ) {Mag=Mag_part; Arg=Arg_part;}
        polar<long double>( long double Mag_part )  {Mag=Mag_part; Arg=0;}
        polar<long double>() {};
            // interconversions between the three levels of accuracy:
        polar<long double> (polar<float>  _VFARC & pf) {Mag = pf.Mag; Arg = pf.Arg;}
        polar<long double> (polar<double> _VFARC & pd) {Mag = pd.Mag; Arg = pd.Arg;}
        polar<long double> (complex<float> _VFARC & __z) {*this = cftope(__z);}
        polar<long double> (complex<double> _VFARC & __z) {*this = cdtope(__z);}
		polar<long double> (complex<long double> _VFARC & __z) {*this = cetope(__z);}
    #endif
    #if !defined _MSC_VER && (!defined __BORLANDC__ || __BORLANDC__ > 0x500)
        polar (polar<long double> _VFARC &);
    #endif
	polar<long double> _VFAR & __cmo  operator=(polar<float> _VFARC &);
    polar<long double> _VFAR & __cmo  operator=(polar<double> _VFARC &);
    polar<long double> _VFAR & __cmo  operator=(polar<long double> _VFARC &);
    polar<long double> _VFAR & __cmo  operator=(float);
    polar<long double> _VFAR & __cmo  operator=(double);
    polar<long double> _VFAR & __cmo  operator=(long double);
    polar<long double> _VFAR & __cmo  operator=(complex<float> _VFARC &);
	polar<long double> _VFAR & __cmo  operator=(complex<double> _VFARC &);
    polar<long double> _VFAR & __cmo  operator=(complex<long double> _VFARC &);

        // basic operations:
    long double mag() { return Mag; }          // magnitude
	long double arg() { return Arg; }         // angle, argument

     // Unary +operator
    polar<long double> _VFAR & __cmo operator+();

       //  Compound-assignment operators:
    polar<long double> _VFAR & __cmo  operator*=(polar<float> _VFARC &);
	polar<long double> _VFAR & __cmo  operator/=(polar<float> _VFARC &);

    polar<long double> _VFAR & __cmo  operator*=(polar<double> _VFARC &);
    polar<long double> _VFAR & __cmo  operator/=(polar<double> _VFARC &);

	polar<long double> _VFAR & __cmo  operator*=(polar<long double> _VFARC &);
    polar<long double> _VFAR & __cmo  operator/=(polar<long double> _VFARC &);

    polar<long double> _VFAR & __cmo  operator*=(long double);
    polar<long double> _VFAR & __cmo  operator/=(long double);

    long double Mag, Arg;  // still public!
};

// implementation: first the functions for cartesian complex classes
// inline-implementation of the simple functions and operators
// cannot use templates here, as several compilers do not allow template
// implementations of functions already declared specialized

//  constructors with function names as in <cmath.h>
inline complex<float> __cmf fcplx( float Re_part, float Im_part )
{return( complex<float>(Re_part,Im_part));}
inline complex<double> __cmf dcplx( double Re_part, double Im_part )
{return( complex<double>(Re_part,Im_part));}
inline complex<long double> __cmf ecplx( long double Re_part, long double Im_part )
{return( complex<long double>(Re_part,Im_part));}
inline polar<float> __cmf fpolr( float Mag_part, float Arg_part )
{return( polar<float>(Mag_part,Arg_part));}
inline polar<double> __cmf dpolr( double Mag_part, double Arg_part )
{return( polar<double>(Mag_part,Arg_part));}
inline polar<long double> __cmf epolr( long double Mag_part, long double Arg_part )
{return( polar<long double>(Mag_part,Arg_part));}

//  data-type interconverting constructors:
//  in the down-conversions, OVERFLOW errors are handled via _matherr
inline complex<double> __cmf cftocd( complex<float> _VFARC &zf )
{  return( complex<double>(zf.Re, zf.Im) ); }
inline complex<long double> __cmf cftoce( complex<float> _VFARC &zf )
{  return( complex<long double>(zf.Re, zf.Im) ); }
inline complex<long double> __cmf  cdtoce( complex<double> _VFARC &zd )
{  return( complex<long double>(zd.Re, zd.Im) ); }
#if !(defined __BORLANDC__) || (defined _WIN64)
    inline complex<double> __cmf  cetocd( complex<long double> ze )
	{  return( complex<double>(ze.Re, ze.Im) ); }
#endif
#if !defined __BORLANDC__ || __BORLANDC__ >= 0x450
	inline complex<float>::complex(complex<double> _VFARC & zd){ *this = cdtocf( zd ); }
    inline complex<float>::complex(complex<long double> _VFARC & ze){*this = cetocf( ze );}
	inline complex<double>::complex(complex<float> _VFARC & zf){Re = zf.Re; Im = zf.Im; }
  #if (defined __BORLANDC__) && !(defined _WIN64)
	inline complex<double>::complex(complex<long double> _VFARC & ze){*this = cetocd( ze );}
  #else
    inline complex<double>::complex(complex<long double> _VFARC & ze){Re=ze.Re; Im=ze.Im;}
  #endif
    inline complex<long double>::complex(complex<float> _VFARC & zf){Re=zf.Re; Im=zf.Im;}
    inline complex<long double>::complex(complex<double> _VFARC & zd){Re=zd.Re; Im=zd.Im;}
    inline complex<float>::complex(polar<float> _VFARC & pf){ *this = pftocf( pf ); }
	inline complex<float>::complex(polar<double> _VFARC & pd){ *this = pdtocf( pd ); }
	inline complex<float>::complex(polar<long double> _VFARC & pe){ *this = petocf( pe ); }
	inline complex<double>::complex(polar<float> _VFARC & pf){ *this = pftocd( pf ); }
	inline complex<double>::complex(polar<double> _VFARC & pd){ *this = pdtocd( pd ); }
	inline complex<double>::complex(polar<long double> _VFARC & pe){ *this = petocd( pe ); }
	inline complex<long double>::complex(polar<float> _VFARC & pf){ *this = pftoce( pf ); }
	inline complex<long double>::complex(polar<double> _VFARC & pd){ *this = pdtoce( pd ); }
	inline complex<long double>::complex(polar<long double> _VFARC & pe){ *this = petoce( pe ); }
#endif
#if !defined _MSC_VER && (!defined __BORLANDC__ || __BORLANDC__ > 0x500)
	inline complex<float>::complex(complex<float> _VFARC & zf){ Re = zf.Re; Im = zf.Im;}
	inline complex<double>::complex(complex<double> _VFARC & zd){Re = zd.Re; Im = zd.Im; }
	inline complex<long double>::complex(complex<long double> _VFARC & ze){Re=ze.Re; Im=ze.Im;}
#endif

//  simple assignments:
inline complex<float> _VFAR & __cmo complex<float>::operator=(complex<float> _VFARC & __z)
{   Re = __z.Re; Im = __z.Im; return *this; }
inline complex<float> _VFAR & __cmo complex<float>::operator=(complex<double> _VFARC & __z)
{   Re = (float) __z.Re; Im = (float) __z.Im; return *this; }
inline complex<float> _VFAR & __cmo complex<float>::operator=(complex<long double> _VFARC & __z)
{   Re = (float) __z.Re; Im = (float) __z.Im; return *this; }
inline complex<float> _VFAR & __cmo complex<float>::operator=(float __zRe)
{   Re = __zRe; Im = 0; return *this; }
inline complex<float> _VFAR & __cmo complex<float>::operator=(double __zRe)
{   Re = (float) __zRe; Im = 0; return *this; }
inline complex<float> _VFAR & __cmo complex<float>::operator=(long double __zRe)
{   Re = (float) __zRe; Im = 0; return *this; }
inline complex<double> _VFAR & __cmo complex<double>::operator=(complex<float> _VFARC & __z)
{   Re = __z.Re; Im = __z.Im; return *this; }
inline complex<double> _VFAR & __cmo complex<double>::operator=(complex<double> _VFARC & __z)
{   Re = __z.Re; Im = __z.Im; return *this; }
inline complex<double> _VFAR & __cmo complex<double>::operator=(complex<long double> _VFARC & __z)
{   Re = (double) __z.Re; Im = (double) __z.Im; return *this; }
inline complex<double> _VFAR & __cmo complex<double>::operator=(float __zRe)
{   Re = __zRe; Im = 0; return *this; }
inline complex<double> _VFAR & __cmo complex<double>::operator=(double __zRe)
{   Re = __zRe; Im = 0; return *this; }
inline complex<double> _VFAR & __cmo complex<double>::operator=(long double __zRe)
{   Re = (double) __zRe; Im = 0; return *this; }
inline complex<long double> _VFAR & __cmo complex<long double>::operator=(complex<float> _VFARC & __z)
{   Re = __z.Re; Im = __z.Im; return *this; }
inline complex<long double> _VFAR & __cmo complex<long double>::operator=(complex<double> _VFARC & __z)
{   Re = __z.Re; Im = __z.Im; return *this; }
inline complex<long double> _VFAR & __cmo complex<long double>::operator=(complex<long double> _VFARC & __z)
{   Re = __z.Re; Im = __z.Im; return *this; }
inline complex<long double> _VFAR & __cmo complex<long double>::operator=(float __zRe)
{   Re = __zRe; Im = 0; return *this; }
inline complex<long double> _VFAR & __cmo complex<long double>::operator=(double __zRe)
{   Re = __zRe; Im = 0; return *this; }
inline complex<long double> _VFAR & __cmo complex<long double>::operator=(long double __zRe)
{   Re = __zRe; Im = 0; return *this; }
inline complex<float> _VFAR & __cmo complex<float>::operator=(polar<float> _VFARC & __p)
{  *this = pftocf( __p ); return *this; }
inline complex<float> _VFAR & __cmo complex<float>::operator=(polar<double> _VFARC & __p)
{  *this = pdtocf( __p ); return *this; }
inline complex<float> _VFAR & __cmo complex<float>::operator=(polar<long double> _VFARC & __p)
{  *this = petocf( __p ); return *this; }
inline complex<double> _VFAR & __cmo complex<double>::operator=(polar<float> _VFARC & __p)
{  *this = pftocd( __p ); return *this; }
inline complex<double> _VFAR & __cmo complex<double>::operator=(polar<double> _VFARC & __p)
{  *this = pdtocd( __p ); return *this; }
inline complex<double> _VFAR & __cmo complex<double>::operator=(polar<long double> _VFARC & __p)
{  *this = petocd( __p ); return *this; }
inline complex<long double> _VFAR & __cmo complex<long double>::operator=(polar<float> _VFARC & __p)
{  *this = pftoce( __p ); return *this; }
inline complex<long double> _VFAR & __cmo complex<long double>::operator=(polar<double> _VFARC & __p)
{  *this = pdtoce( __p ); return *this; }
inline complex<long double> _VFAR & __cmo complex<long double>::operator=(polar<long double> _VFARC & __p)
{  *this = petoce( __p ); return *this; }

// basic operations:
inline float       __cmf real( complex<float> _VFARC & __z) { return __z.Re; }
inline double      __cmf real( complex<double> _VFARC & __z) { return __z.Re; }
inline long double __cmf real( complex<long double> _VFARC & __z) { return __z.Re; }
inline float       __cmf imag( complex<float> _VFARC & __z) { return __z.Im; }
inline double      __cmf imag( complex<double> _VFARC & __z) { return __z.Im; }
inline long double __cmf imag( complex<long double> _VFARC & __z) { return __z.Im; }

inline complex<float>     __cmf neg( complex<float> _VFARC & __z )
{   return complex<float>(-__z.Re, -__z.Im); }

inline complex<double>     __cmf neg( complex<double> _VFARC & __z )
{   return complex<double>(-__z.Re, -__z.Im); }

inline complex<long double> __cmf neg( complex<long double> _VFARC & __z )
{   return complex<long double>(-__z.Re, -__z.Im); }

inline complex<float>     __cmf conj( complex<float> _VFARC & __z )
{   return complex<float>(__z.Re, -__z.Im); }

inline complex<double>     __cmf conj( complex<double> _VFARC & __z )
{   return complex<double>(__z.Re, -__z.Im); }

inline complex<long double> __cmf conj( complex<long double> _VFARC & __z )
{   return complex<long double>(__z.Re, -__z.Im); }

         // Unary operators:
inline complex<float> _VFAR & __cmo complex<float>::operator+()
{   return (*this); }

inline complex<double> _VFAR & __cmo complex<double>::operator+()
{   return (*this); }

inline complex<long double> _VFAR & __cmo complex<long double>::operator+()
{   return (*this); }

inline complex<float> __cmf operator-( complex<float> _VFARC & __z)
{   return complex<float>(-__z.Re, -__z.Im); }

inline complex<double> __cmf operator-( complex<double> _VFARC & __z)
{   return complex<double>(-__z.Re, -__z.Im); }

inline complex<long double> __cmf operator-( complex<long double> _VFARC & __z)
{   return complex<long double>(-__z.Re, -__z.Im); }

				// Binary operators:
inline complex<float> __cmf operator+( complex<float> _VFARC & __z1, complex<float> _VFARC & __z2)
{   return complex<float>(__z1.Re + __z2.Re, __z1.Im + __z2.Im); }

inline complex<float> __cmf operator+( complex<float> _VFARC & __z1, float __z2Re )
{   return complex<float>(__z1.Re+__z2Re, __z1.Im); }

inline complex<float> __cmf operator+( float __z1Re, complex<float> _VFARC & __z2 )
{   return complex<float>(__z1Re + __z2.Re, __z2.Im); }

inline complex<float> __cmf operator-( complex<float> _VFARC & __z1, complex<float> _VFARC & __z2)
{   return complex<float>(__z1.Re - __z2.Re, __z1.Im - __z2.Im); }

inline complex<float> __cmf operator-( complex<float> _VFARC & __z1, float __z2Re )
{   return complex<float>(__z1.Re - __z2Re, __z1.Im); }

inline complex<float> __cmf operator-( float __z1Re, complex<float> _VFARC & __z2 )
{   return complex<float>(__z1Re - __z2.Re, -__z2.Im); }

inline complex<float> __cmf operator*( complex<float> _VFARC & __z1, complex<float> _VFARC & __z2)
{   return complex<float>( __z1.Re * __z2.Re - __z1.Im * __z2.Im,
						   __z1.Re * __z2.Im + __z1.Im * __z2.Re );
}
inline complex<float> __cmf operator*( complex<float> _VFARC & __z1, float __z2Re )
{   return complex<float>( __z1.Re * __z2Re, __z1.Im * __z2Re ); }

inline complex<float> __cmf operator*( float __z1Re, complex<float> _VFARC & __z2 )
{   return complex<float>( __z1Re * __z2.Re, __z1Re * __z2.Im ); }

inline complex<float> __cmf operator/( complex<float> _VFARC & __dividend,
                                       complex<float> _VFARC & __divisor )
{     complex<float> Result;
      double denom;
      Result.Re = (float)(((double)(__dividend.Re) *__divisor.Re +
						   (double)(__dividend.Im) *__divisor.Im) /
         (denom = (double)(__divisor.Re) * __divisor.Re +
                  (double)(__divisor.Im) * __divisor.Im));
      Result.Im = (float)(((double)(__dividend.Im) * __divisor.Re -
                           (double)(__dividend.Re) * __divisor.Im ) / denom);
	  return Result;
}
inline complex<float> __cmf operator/( complex<float> _VFARC & __dividend, float __divisorRe)
{   return complex<float>( __dividend.Re / __divisorRe, __dividend.Im / __divisorRe ); }

inline complex<float> __cmf operator /( float __dividendRe,
                                        complex<float> _VFARC & __divisor )
{     complex<float> Result;
      double         denom;
      Result.Re = (float)(((double)(__dividendRe) * __divisor.Re) /
        (denom = (double)(__divisor.Re) * __divisor.Re +
				 (double)(__divisor.Im) * __divisor.Im));
      Result.Im = -(float)(((double)(__dividendRe) * __divisor.Im ) / denom);
      return Result;
}

inline complex<double> __cmf operator+( complex<double> _VFARC & __z1, complex<double> _VFARC & __z2)
{   return complex<double>(__z1.Re + __z2.Re, __z1.Im + __z2.Im); }

inline complex<double> __cmf operator+( complex<double> _VFARC & __z1, double __z2Re )
{   return complex<double>(__z1.Re+__z2Re, __z1.Im); }

inline complex<double> __cmf operator+( double __z1Re, complex<double> _VFARC & __z2 )
{   return complex<double>(__z1Re + __z2.Re, __z2.Im); }

inline complex<double> __cmf operator-( complex<double> _VFARC & __z1, complex<double> _VFARC & __z2)
{   return complex<double>(__z1.Re - __z2.Re, __z1.Im - __z2.Im); }

inline complex<double> __cmf operator-( complex<double> _VFARC & __z1, double __z2Re )
{   return complex<double>(__z1.Re - __z2Re, __z1.Im); }

inline complex<double> __cmf operator-( double __z1Re, complex<double> _VFARC & __z2 )
{   return complex<double>(__z1Re - __z2.Re, -__z2.Im); }

inline complex<double> __cmf operator*( complex<double> _VFARC & __z1, complex<double> _VFARC & __z2)
{   return complex<double>( __z1.Re * __z2.Re - __z1.Im * __z2.Im,
						   __z1.Re * __z2.Im + __z1.Im * __z2.Re );
}
inline complex<double> __cmf operator*( complex<double> _VFARC & __z1, double __z2Re )
{   return complex<double>( __z1.Re * __z2Re, __z1.Im * __z2Re ); }

inline complex<double> __cmf operator*( double __z1Re, complex<double> _VFARC & __z2 )
{   return complex<double>( __z1Re * __z2.Re, __z1Re * __z2.Im ); }

inline complex<double> __cmf operator/( complex<double> _VFARC & __dividend, double __divisorRe)
{   return complex<double>( __dividend.Re / __divisorRe, __dividend.Im / __divisorRe ); }

inline complex<long double> __cmf operator+( complex<long double> _VFARC & __z1, complex<long double> _VFARC & __z2)
{   return complex<long double>(__z1.Re + __z2.Re, __z1.Im + __z2.Im); }

inline complex<long double> __cmf operator+( complex<long double> _VFARC & __z1, long double __z2Re )
{   return complex<long double>(__z1.Re+__z2Re, __z1.Im); }

inline complex<long double> __cmf operator+( long double __z1Re, complex<long double> _VFARC & __z2 )
{   return complex<long double>(__z1Re + __z2.Re, __z2.Im); }

inline complex<long double> __cmf operator-( complex<long double> _VFARC & __z1, complex<long double> _VFARC & __z2)
{   return complex<long double>(__z1.Re - __z2.Re, __z1.Im - __z2.Im); }

inline complex<long double> __cmf operator-( complex<long double> _VFARC & __z1, long double __z2Re )
{   return complex<long double>(__z1.Re - __z2Re, __z1.Im); }

inline complex<long double> __cmf operator-( long double __z1Re, complex<long double> _VFARC & __z2 )
{   return complex<long double>(__z1Re - __z2.Re, -__z2.Im); }

inline complex<long double> __cmf operator*( complex<long double> _VFARC & __z1, complex<long double> _VFARC & __z2)
{   return complex<long double>( __z1.Re * __z2.Re - __z1.Im * __z2.Im,
                           __z1.Re * __z2.Im + __z1.Im * __z2.Re );
}
inline complex<long double> __cmf operator*( complex<long double> _VFARC & __z1, long double __z2Re )
{   return complex<long double>( __z1.Re * __z2Re, __z1.Im * __z2Re ); }

inline complex<long double> __cmf operator*( long double __z1Re, complex<long double> _VFARC & __z2 )
{   return complex<long double>( __z1Re * __z2.Re, __z1Re * __z2.Im ); }

inline complex<long double> __cmf operator/( complex<long double> _VFARC & __dividend, long double __divisorRe)
{   return complex<long double>( __dividend.Re / __divisorRe, __dividend.Im / __divisorRe ); }
    //  operator / (complex<double>, complex<double> ) and
    //  operator / (complex<long double>, complex<long double> )
    //  cannot safely be inlined

    // Mixed-accuracy level binary operators:
inline complex<double> __cmf operator+( complex<float> _VFARC & __z1, complex<double> _VFARC & __z2)
{   return complex<double>(__z1.Re + __z2.Re, __z1.Im + __z2.Im); }

inline complex<double> __cmf operator+( complex<double> _VFARC & __z1, complex<float> _VFARC & __z2)
{   return complex<double>(__z1.Re + __z2.Re, __z1.Im + __z2.Im); }

inline complex<long double> __cmf operator+( complex<float> _VFARC & __z1, complex<long double> _VFARC & __z2)
{   return complex<long double>(__z1.Re + __z2.Re, __z1.Im + __z2.Im); }

inline complex<long double> __cmf operator+( complex<long double> _VFARC & __z1, complex<float> _VFARC & __z2)
{   return complex<long double>(__z1.Re + __z2.Re, __z1.Im + __z2.Im); }

inline complex<long double> __cmf operator+( complex<double> _VFARC & __z1, complex<long double> _VFARC & __z2)
{   return complex<long double>(__z1.Re + __z2.Re, __z1.Im + __z2.Im); }

inline complex<long double> __cmf operator+( complex<long double> _VFARC & __z1, complex<double> _VFARC & __z2)
{   return complex<long double>(__z1.Re + __z2.Re, __z1.Im + __z2.Im); }

inline complex<double> __cmf operator-( complex<float> _VFARC & __z1, complex<double> _VFARC & __z2)
{   return complex<double>(__z1.Re - __z2.Re, __z1.Im - __z2.Im); }

inline complex<double> __cmf operator-( complex<double> _VFARC & __z1, complex<float> _VFARC & __z2)
{   return complex<double>(__z1.Re - __z2.Re, __z1.Im - __z2.Im); }

inline complex<long double> __cmf operator-( complex<float> _VFARC & __z1, complex<long double> _VFARC & __z2)
{   return complex<long double>(__z1.Re - __z2.Re, __z1.Im - __z2.Im); }

inline complex<long double> __cmf operator-( complex<long double> _VFARC & __z1, complex<float> _VFARC & __z2)
{   return complex<long double>(__z1.Re - __z2.Re, __z1.Im - __z2.Im); }

inline complex<long double> __cmf operator-( complex<double> _VFARC & __z1, complex<long double> _VFARC & __z2)
{   return complex<long double>(__z1.Re - __z2.Re, __z1.Im - __z2.Im); }

inline complex<long double> __cmf operator-( complex<long double> _VFARC & __z1, complex<double> _VFARC & __z2)
{   return complex<long double>(__z1.Re - __z2.Re, __z1.Im - __z2.Im); }

inline complex<double> __cmf operator*( complex<float> _VFARC & __z1, complex<double> _VFARC & __z2 )
{   return complex<double>( __z1.Re * __z2.Re - __z1.Im * __z2.Im,
							__z1.Re * __z2.Im + __z1.Im * __z2.Re );
}
inline complex<double> __cmf operator*( complex<double> _VFARC & __z1, complex<float> _VFARC & __z2 )
{   return complex<double>( __z1.Re * __z2.Re - __z1.Im * __z2.Im,
                            __z1.Re * __z2.Im + __z1.Im * __z2.Re );
}
inline complex<long double> __cmf operator*( complex<float> _VFARC & __z1, complex<long double> _VFARC & __z2 )
{   return complex<long double>( __z1.Re * __z2.Re - __z1.Im * __z2.Im,
                                 __z1.Re * __z2.Im + __z1.Im * __z2.Re );
}
inline complex<long double> __cmf operator*( complex<long double> _VFARC & __z1, complex<float> _VFARC & __z2 )
{   return complex<long double>( __z1.Re * __z2.Re - __z1.Im * __z2.Im,
								 __z1.Re * __z2.Im + __z1.Im * __z2.Re );
}
inline complex<long double> __cmf operator*( complex<double> _VFARC & __z1, complex<long double> _VFARC & __z2 )
{   return complex<long double>( __z1.Re * __z2.Re - __z1.Im * __z2.Im,
								 __z1.Re * __z2.Im + __z1.Im * __z2.Re );
}
inline complex<long double> __cmf operator*( complex<long double> _VFARC & __z1, complex<double> _VFARC & __z2 )
{   return complex<long double>( __z1.Re * __z2.Re - __z1.Im * __z2.Im,
                                 __z1.Re * __z2.Im + __z1.Im * __z2.Re );
}

inline complex<double> __cmf operator/( complex<double> _VFARC & __dividend,
										complex<float>  _VFARC & __divisor )
{     complex<double> Result;
	  double          denom;
	  Result.Re = (__dividend.Re *__divisor.Re +
				   __dividend.Im *__divisor.Im) /
		 (denom = (double)(__divisor.Re) * __divisor.Re +
				  (double)(__divisor.Im) * __divisor.Im);
	  Result.Im = (__dividend.Im * __divisor.Re -
				   __dividend.Re * __divisor.Im ) / denom;
	  return Result;
}

inline complex<long double> __cmf operator/( complex<long double> _VFARC & __dividend,
											 complex<float>  _VFARC & __divisor )
{     complex<long double> Result;
	  double               denom;
	  Result.Re = (__dividend.Re *__divisor.Re +
				   __dividend.Im *__divisor.Im) /
         (denom = (double)(__divisor.Re) * __divisor.Re +
                  (double)(__divisor.Im) * __divisor.Im);
      Result.Im = (__dividend.Im * __divisor.Re -
                   __dividend.Re * __divisor.Im ) / denom;
      return Result;
}

inline VBOOL __cmf operator==(complex<float> _VFARC & __z1, complex<float> _VFARC & __z2)
{   return __z1.Re == __z2.Re && __z1.Im == __z2.Im; }

inline VBOOL __cmf operator==(float __z1Re, complex<float> _VFARC & __z2)
{   return __z1Re == __z2.Re && __z2.Im == 0; }

inline VBOOL __cmf operator==(complex<float> _VFARC & __z1, float __z2Re)
{   return __z1.Re == __z2Re && __z1.Im == 0; }

inline VBOOL __cmf operator!=(complex<float> _VFARC & __z1, complex<float> _VFARC & __z2)
{   return __z1.Re != __z2.Re || __z1.Im != __z2.Im; }

inline VBOOL __cmf operator!=(float __z1Re, complex<float> _VFARC & __z2)
{   return __z1Re != __z2.Re || __z2.Im != 0; }

inline VBOOL __cmf operator!=(complex<float> _VFARC & __z1, float __z2Re)
{   return __z1.Re != __z2Re || __z1.Im != 0; }

inline VBOOL __cmf operator==(complex<double> _VFARC & __z1, complex<double> _VFARC & __z2)
{   return __z1.Re == __z2.Re && __z1.Im == __z2.Im; }

inline VBOOL __cmf operator==(double __z1Re, complex<double> _VFARC & __z2)
{   return __z1Re == __z2.Re && __z2.Im == 0; }

inline VBOOL __cmf operator==(complex<double> _VFARC & __z1, double __z2Re)
{   return __z1.Re == __z2Re && __z1.Im == 0; }

inline VBOOL __cmf operator!=(complex<double> _VFARC & __z1, complex<double> _VFARC & __z2)
{   return __z1.Re != __z2.Re || __z1.Im != __z2.Im; }

inline VBOOL __cmf operator!=(double __z1Re, complex<double> _VFARC & __z2)
{   return __z1Re != __z2.Re || __z2.Im != 0; }

inline VBOOL __cmf operator!=(complex<double> _VFARC & __z1, double __z2Re)
{   return __z1.Re != __z2Re || __z1.Im != 0; }

inline VBOOL __cmf operator==(complex<long double> _VFARC & __z1, complex<long double> _VFARC & __z2)
{   return __z1.Re == __z2.Re && __z1.Im == __z2.Im; }

inline VBOOL __cmf operator==(long double __z1Re, complex<long double> _VFARC & __z2)
{   return __z1Re == __z2.Re && __z2.Im == 0; }

inline VBOOL __cmf operator==(complex<long double> _VFARC & __z1, long double __z2Re)
{   return __z1.Re == __z2Re && __z1.Im == 0; }

inline VBOOL __cmf operator!=(complex<long double> _VFARC & __z1, complex<long double> _VFARC & __z2)
{   return __z1.Re != __z2.Re || __z1.Im != __z2.Im; }

inline VBOOL __cmf operator!=(long double __z1Re, complex<long double> _VFARC & __z2)
{   return __z1Re != __z2.Re || __z2.Im != 0; }

inline VBOOL __cmf operator!=(complex<long double> _VFARC & __z1, long double __z2Re)
{   return __z1.Re != __z2Re || __z1.Im != 0; }

      // Compound-assignment operators:
inline complex<float> _VFAR & __cmo complex<float>::operator+=(complex<float> _VFARC & __s2)
{   Re += __s2.Re; Im += __s2.Im; return *this; }

inline complex<float> _VFAR & __cmo complex<float>::operator+=(complex<double> _VFARC & __s2)
{   Re = (float)(Re + __s2.Re); Im = (float) (Im + __s2.Im); return *this; }

inline complex<float> _VFAR & __cmo complex<float>::operator+=(complex<long double> _VFARC & __s2)
{   Re = (float)(Re + __s2.Re); Im = (float) (Im + __s2.Im); return *this; }

inline complex<float> _VFAR & __cmo complex<float>::operator+=(float __s2Re)
{   Re += __s2Re; return *this; }

inline complex<double> _VFAR & __cmo complex<double>::operator+=(complex<float> _VFARC & __s2)
{   Re += __s2.Re; Im += __s2.Im; return *this; }

inline complex<double> _VFAR & __cmo complex<double>::operator+=(complex<double> _VFARC & __s2)
{   Re += __s2.Re; Im += __s2.Im; return *this; }

inline complex<double> _VFAR & __cmo complex<double>::operator+=(complex<long double> _VFARC & __s2)
{   Re = (double)(Re + __s2.Re); Im = (double) (Im + __s2.Im); return *this; }

inline complex<double> _VFAR & __cmo complex<double>::operator+=(double __s2Re)
{   Re += __s2Re; return *this; }

inline complex<long double> _VFAR & __cmo complex<long double>::operator+=(complex<float> _VFARC & __s2)
{   Re += __s2.Re; Im += __s2.Im; return *this; }

inline complex<long double> _VFAR & __cmo complex<long double>::operator+=(complex<double> _VFARC & __s2)
{   Re += __s2.Re; Im += __s2.Im; return *this; }

inline complex<long double> _VFAR & __cmo complex<long double>::operator+=(complex<long double> _VFARC & __s2)
{   Re += __s2.Re; Im += __s2.Im; return *this; }

inline complex<long double> _VFAR & __cmo complex<long double>::operator+=(long double __s2Re)
{   Re += __s2Re; return *this; }

inline complex<float> _VFAR & __cmo complex<float>::operator-=(complex<float> _VFARC & __s2)
{   Re -= __s2.Re; Im -= __s2.Im; return *this; }

inline complex<float> _VFAR & __cmo complex<float>::operator-=(complex<double> _VFARC & __s2)
{   Re = (float)(Re - __s2.Re); Im = (float) (Im - __s2.Im); return *this; }

inline complex<float> _VFAR & __cmo complex<float>::operator-=(complex<long double> _VFARC & __s2)
{   Re = (float)(Re - __s2.Re); Im = (float) (Im - __s2.Im); return *this; }

inline complex<float> _VFAR & __cmo complex<float>::operator-=(float __s2Re)
{   Re -= __s2Re; return *this; }

inline complex<double> _VFAR & __cmo complex<double>::operator-=(complex<float> _VFARC & __s2)
{   Re -= __s2.Re; Im -= __s2.Im; return *this; }

inline complex<double> _VFAR & __cmo complex<double>::operator-=(complex<double> _VFARC & __s2)
{   Re -= __s2.Re; Im -= __s2.Im; return *this; }

inline complex<double> _VFAR & __cmo complex<double>::operator-=(complex<long double> _VFARC & __s2)
{   Re = (double)(Re - __s2.Re); Im = (double) (Im - __s2.Im); return *this; }

inline complex<double> _VFAR & __cmo complex<double>::operator-=(double __s2Re)
{   Re -= __s2Re; return *this; }

inline complex<long double> _VFAR & __cmo complex<long double>::operator-=(complex<float> _VFARC & __s2)
{    Re -= __s2.Re; Im -= __s2.Im; return *this; }

inline complex<long double> _VFAR & __cmo complex<long double>::operator-=(complex<double> _VFARC & __s2)
{   Re -= __s2.Re; Im -= __s2.Im; return *this; }

inline complex<long double> _VFAR & __cmo complex<long double>::operator-=(complex<long double> _VFARC & __s2)
{   Re -= __s2.Re; Im -= __s2.Im; return *this; }

inline complex<long double> _VFAR & __cmo complex<long double>::operator-=(long double __s2Re)
{   Re -= __s2Re; return *this; }

inline complex<float> _VFAR & __cmo complex<float>::operator*=(complex<float> _VFARC & __fac2)
{   float tmpRe = Re * __fac2.Re - Im * __fac2.Im;
    Im          = Im * __fac2.Re + Re * __fac2.Im;
    Re          = tmpRe;
	return *this;
}

inline complex<float> _VFAR & __cmo complex<float>::operator*=(complex<double> _VFARC & __fac2)
{   float tmpRe = (float) (Re * __fac2.Re - Im * __fac2.Im);
    Im          = (float) (Im * __fac2.Re + Re * __fac2.Im);
    Re          = tmpRe;
	return *this;
}

inline complex<float> _VFAR & __cmo complex<float>::operator*=(complex<long double> _VFARC & __fac2)
{   float tmpRe = (float) (Re * __fac2.Re - Im * __fac2.Im);
    Im          = (float) (Im * __fac2.Re + Re * __fac2.Im);
    Re          = tmpRe;
    return *this;
}

inline complex<float> _VFAR & __cmo complex<float>::operator*=(float __fac2Re)
{
    Re *= __fac2Re;
	Im *= __fac2Re;
    return *this;
}

inline complex<double> _VFAR & __cmo complex<double>::operator*=(complex<float> _VFARC & __fac2)
{   double tmpRe = Re * __fac2.Re - Im * __fac2.Im;
    Im           = Im * __fac2.Re + Re * __fac2.Im;
    Re           = tmpRe;
    return *this;
}

inline complex<double> _VFAR & __cmo complex<double>::operator*=(complex<double> _VFARC & __fac2)
{   double tmpRe = Re * __fac2.Re - Im * __fac2.Im;
    Im           = Im * __fac2.Re + Re * __fac2.Im;
    Re           = tmpRe;
    return *this;
}

inline complex<double> _VFAR & __cmo complex<double>::operator*=(complex<long double> _VFARC & __fac2)
{   double tmpRe = (double) (Re * __fac2.Re - Im * __fac2.Im);
    Im           = (double) (Im * __fac2.Re + Re * __fac2.Im);
    Re           = tmpRe;
    return *this;
}

inline complex<double> _VFAR & __cmo complex<double>::operator*=(double __fac2Re)
{
    Re *= __fac2Re;
    Im *= __fac2Re;
    return *this;
}

inline complex<long double> _VFAR & __cmo complex<long double>::operator*=(complex<float> _VFARC & __fac2)
{   long double tmpRe = Re * __fac2.Re - Im * __fac2.Im;
    Im                = Im * __fac2.Re + Re * __fac2.Im;
    Re                = tmpRe;
    return *this;
}

inline complex<long double> _VFAR & __cmo complex<long double>::operator*=(complex<double> _VFARC & __fac2)
{   long double tmpRe = Re * __fac2.Re - Im * __fac2.Im;
    Im                = Im * __fac2.Re + Re * __fac2.Im;
    Re                = tmpRe;
    return *this;
}

inline complex<long double> _VFAR & __cmo complex<long double>::operator*=(complex<long double> _VFARC & __fac2)
{   long double tmpRe = Re * __fac2.Re - Im * __fac2.Im;
	Im                = Im * __fac2.Re + Re * __fac2.Im;
    Re                = tmpRe;
	return *this;
}

inline complex<long double> _VFAR & __cmo complex<long double>::operator*=(long double __fac2Re)
{
	Re *= __fac2Re;
    Im *= __fac2Re;
    return *this;
}

inline complex<float> _VFAR & __cmo complex<float>::operator/=(complex<float> _VFARC & __divisor)
{     double denom;
	  float  tmpRe = (float)((Re * __divisor.Re + Im * __divisor.Im) /
            (denom = (double)(__divisor.Re) * __divisor.Re +
                     (double)(__divisor.Im) * __divisor.Im));
      Im = (float)((Im * __divisor.Re - Re * __divisor.Im ) / denom);
      Re = tmpRe;
      return *this;
}

inline complex<float> _VFAR & __cmo complex<float>::operator/=(float __divisor)
{
    Re /= __divisor;
	Im /= __divisor;
    return *this;
}

inline complex<double> _VFAR & __cmo complex<double>::operator/=(complex<float> _VFARC & __divisor)
{     double denom;
      double tmpRe = (double)((Re * __divisor.Re + Im * __divisor.Im) /
			(denom = (double)(__divisor.Re) * __divisor.Re +
                     (double)(__divisor.Im) * __divisor.Im));
      Im = (Im * __divisor.Re - Re * __divisor.Im ) / denom;
      Re = tmpRe;
      return *this;
}

inline complex<double> _VFAR & __cmo complex<double>::operator/=(double __divisor)
{
    Re /= __divisor;
    Im /= __divisor;
    return *this;
}

inline complex<long double> _VFAR & __cmo complex<long double>::operator/=(complex<float> _VFARC & __divisor)
{     double denom;
      long double tmpRe = (Re * __divisor.Re + Im * __divisor.Im) /
                 (denom = (double)(__divisor.Re) * __divisor.Re +
						  (double)(__divisor.Im) * __divisor.Im);
      Im = (Im * __divisor.Re - Re * __divisor.Im ) / denom;
	  Re = tmpRe;
      return *this;
}

inline complex<long double> _VFAR & __cmo complex<long double>::operator/=(long double __divisor)
{
    Re /= __divisor;
    Im /= __divisor;
    return *this;
}

inline __cmistream _VFAR &  __cmf operator>>(__cmistream _VFAR & is, complex<float> _VFAR & __z)
{   // read a complex number __z in the form r or (r) or {r, i} or (r, i)
    float     r = 0, i = 0;
    char  c;

    is >> c;
    if (c == '(' || c == '{')  // notations (r), (r,i), or {r,i}
    {
        is >> r >> c;
        if (c == ',') { is >> i  >> c;}
        if (c != ')' && c != '}')   is.clear(__cmios::failbit);
    }
	else  // only real part
    {
		is.putback(c);
        is >> r;
    }
    if (is) { __z.Re = r; __z.Im = i; }
    return is;
}

inline __cmostream _VFAR &  __cmf operator<<(__cmostream _VFAR & os, complex<float> _VFARC & __z)
{   return (os << "{" << __z.Re << "," << __z.Im << "}"); }

inline __cmistream _VFAR &  __cmf operator>>(__cmistream _VFAR & is, complex<double> _VFAR & __z)
{   // read a complex number __z in the form r or (r) or {r, i} or (r, i)
	double     r = 0, i = 0;
    char  c;

    is >> c;
    if (c == '(' || c == '{')  // notations (r), (r,i), or {r,i}
    {
        is >> r >> c;
        if (c == ',') { is >> i  >> c;}
        if (c != ')' && c != '}')   is.clear(__cmios::failbit);
    }
    else  // only real part
	{
        is.putback(c);
		is >> r;
    }
    if (is) { __z.Re = r; __z.Im = i; }
    return is;
}

inline __cmostream _VFAR &  __cmf operator<<(__cmostream _VFAR & os, complex<double> _VFARC & __z)
{   return (os << "{" << __z.Re << "," << __z.Im << "}"); }

inline __cmistream _VFAR &  __cmf operator>>(__cmistream _VFAR & is, complex<long double> _VFAR & __z)
{   // read a complex number __z in the form r or (r) or {r, i} or (r, i)
    long double     r = 0, i = 0;
	char  c;

    is >> c;
    if (c == '(' || c == '{')  // notations (r), (r,i), or {r,i}
    {
        is >> r >> c;
        if (c == ',') { is >> i  >> c;}
        if (c != ')' && c != '}')   is.clear(__cmios::failbit);
    }
    else  // only real part
    {
		is.putback(c);
		is >> r;
	}
	if (is) { __z.Re = r; __z.Im = i; }
	return is;
}

inline __cmostream _VFAR &  __cmf operator<<(__cmostream _VFAR & os, complex<long double> _VFARC & __z)
{   return (os << "{" << __z.Re << "," << __z.Im << "}"); }


//  now the functions for polar-complex classes:
//  data-type interconverting constructors:
//  in the down-conversions, OVERFLOW errors are handled via _matherr
inline polar<double> __cmf  pftopd( polar<float> _VFARC &pf )
{  return( polar<double>(pf.Mag, pf.Arg) ); }
inline polar<long double> __cmf  pftope( polar<float> _VFARC &pf )
{  return( polar<long double>(pf.Mag, pf.Arg) ); }
inline polar<long double> __cmf  pdtope( polar<double> _VFARC &pd )
{  return( polar<long double>(pd.Mag, pd.Arg) ); }
#if !(defined __BORLANDC__) || (defined _WIN64)
    inline polar<double> __cmf  petopd( polar<long double> pe )
	{  return( polar<double>(pe.Mag, pe.Arg) ); }
#endif
#if !defined __BORLANDC__ || __BORLANDC__ >= 0x450
    inline polar<float>::polar(polar<double> _VFARC & pd){ *this = pdtopf( pd ); }
    inline polar<float>::polar(polar<long double> _VFARC & pe){*this = petopf( pe );}
	inline polar<double>::polar(polar<float> _VFARC & pf){Mag = pf.Mag; Arg = pf.Arg; }
  #if (defined __BORLANDC__) && !(defined _WIN64)
    inline polar<double>::polar(polar<long double> _VFARC &pe){*this = petopd( pe );}
  #else
    inline polar<double>::polar(polar<long double> _VFARC & pe){Mag=pe.Mag; Arg=pe.Arg;}
  #endif
    inline polar<long double>::polar(polar<float> _VFARC & pf){Mag=pf.Mag; Arg=pf.Arg;}
    inline polar<long double>::polar(polar<double> _VFARC & pd){Mag=pd.Mag; Arg=pd.Arg;}
    inline polar<float>::polar(complex<float> _VFARC & zf){ *this = cftopf( zf ); }
	inline polar<float>::polar(complex<double> _VFARC & zd){ *this = cdtopf( zd ); }
    inline polar<float>::polar(complex<long double> _VFARC & ze){ *this = cetopf( ze ); }
    inline polar<double>::polar(complex<float> _VFARC & zf){ *this = cftopd( zf ); }
	inline polar<double>::polar(complex<double> _VFARC & zd){ *this = cdtopd( zd ); }
    inline polar<double>::polar(complex<long double> _VFARC & ze){ *this = cetopd( ze ); }
    inline polar<long double>::polar(complex<float> _VFARC & zf){ *this = cftope( zf ); }
    inline polar<long double>::polar(complex<double> _VFARC & zd){ *this = cdtope( zd ); }
    inline polar<long double>::polar(complex<long double> _VFARC & ze){ *this = cetope( ze ); }
#endif
#if !defined _MSC_VER && (!defined __BORLANDC__ || __BORLANDC__ > 0x500)
    inline polar<float>::polar(polar<float> _VFARC & pf){Mag=pf.Mag; Arg=pf.Arg;}
    inline polar<double>::polar(polar<double> _VFARC & pd){Mag=pd.Mag; Arg=pd.Arg;}
    inline polar<long double>::polar(polar<long double> _VFARC & pe){Mag=pe.Mag; Arg=pe.Arg;}
#endif

//  simple assignments:
inline polar<float> _VFAR & __cmo polar<float>::operator=(polar<float> _VFARC & __p)
{   Mag = __p.Mag; Arg = __p.Arg; return *this; }
inline polar<float> _VFAR & __cmo polar<float>::operator=(polar<double> _VFARC & __p)
{   Mag = (float)__p.Mag; Arg = (float)__p.Arg; return *this; }
inline polar<float> _VFAR & __cmo polar<float>::operator=(polar<long double> _VFARC & __p)
{   Mag = (float)__p.Mag; Arg = (float)__p.Arg; return *this; }
inline polar<float> _VFAR & __cmo polar<float>::operator=(float __zRe)
{   Mag = __zRe; Arg = 0; return *this; }
inline polar<float> _VFAR & __cmo polar<float>::operator=(double __zRe)
{   Mag = (float) __zRe; Arg = 0; return *this; }
inline polar<float> _VFAR & __cmo polar<float>::operator=(long double __zRe)
{   Mag = (float) __zRe; Arg = 0; return *this; }
inline polar<double> _VFAR & __cmo polar<double>::operator=(polar<float> _VFARC & __p)
{   Mag = __p.Mag; Arg = __p.Arg; return *this; }
inline polar<double> _VFAR & __cmo polar<double>::operator=(polar<double> _VFARC & __p)
{   Mag = __p.Mag; Arg = __p.Arg; return *this; }
inline polar<double> _VFAR & __cmo polar<double>::operator=(polar<long double> _VFARC & __p)
{   Mag = (double)__p.Mag; Arg = (double)__p.Arg; return *this; }
inline polar<double> _VFAR & __cmo polar<double>::operator=(float __zRe)
{   Mag = __zRe; Arg = 0; return *this; }
inline polar<double> _VFAR & __cmo polar<double>::operator=(double __zRe)
{   Mag = __zRe; Arg = 0; return *this; }
inline polar<double> _VFAR & __cmo polar<double>::operator=(long double __zRe)
{   Mag = (double) __zRe; Arg = 0; return *this; }
inline polar<long double> _VFAR & __cmo polar<long double>::operator=(polar<float> _VFARC & __p)
{   Mag = __p.Mag; Arg = __p.Arg; return *this; }
inline polar<long double> _VFAR & __cmo polar<long double>::operator=(polar<double> _VFARC & __p)
{   Mag = __p.Mag; Arg = __p.Arg; return *this; }
inline polar<long double> _VFAR & __cmo polar<long double>::operator=(polar<long double> _VFARC & __p)
{   Mag = __p.Mag; Arg = __p.Arg; return *this; }
inline polar<long double> _VFAR & __cmo polar<long double>::operator=(float __zRe)
{   Mag = __zRe; Arg = 0; return *this; }
inline polar<long double> _VFAR & __cmo polar<long double>::operator=(double __zRe)
{   Mag = __zRe; Arg = 0; return *this; }
inline polar<long double> _VFAR & __cmo polar<long double>::operator=(long double __zRe)
{   Mag = __zRe; Arg = 0; return *this; }
inline polar<float> _VFAR & __cmo polar<float>::operator=(complex<float> _VFARC & __p)
{  *this = cftopf( __p ); return *this; }
inline polar<float> _VFAR & __cmo polar<float>::operator=(complex<double> _VFARC & __p)
{  *this = cdtopf( __p ); return *this; }
inline polar<float> _VFAR & __cmo polar<float>::operator=(complex<long double> _VFARC & __p)
{  *this = cetopf( __p ); return *this; }
inline polar<double> _VFAR & __cmo polar<double>::operator=(complex<float> _VFARC & __p)
{  *this = cftopd( __p ); return *this; }
inline polar<double> _VFAR & __cmo polar<double>::operator=(complex<double> _VFARC & __p)
{  *this = cdtopd( __p ); return *this; }
inline polar<double> _VFAR & __cmo polar<double>::operator=(complex<long double> _VFARC & __p)
{  *this = cetopd( __p ); return *this; }
inline polar<long double> _VFAR & __cmo polar<long double>::operator=(complex<float> _VFARC & __p)
{  *this = cftope( __p ); return *this; }
inline polar<long double> _VFAR & __cmo polar<long double>::operator=(complex<double> _VFARC & __p)
{  *this = cdtope( __p ); return *this; }
inline polar<long double> _VFAR & __cmo polar<long double>::operator=(complex<long double> _VFARC & __p)
{  *this = cetope( __p ); return *this; }

// basic operations:
inline float       __cmf abs( polar<float> _VFARC & __p) { return __p.Mag; }
inline double      __cmf abs( polar<double> _VFARC & __p) { return __p.Mag; }
inline long double __cmf abs( polar<long double> _VFARC & __p) { return __p.Mag; }
inline float       __cmf arg( polar<float> _VFARC & __p) { return __p.Arg; }
inline double      __cmf arg( polar<double> _VFARC & __p) { return __p.Arg; }
inline long double __cmf arg( polar<long double> _VFARC & __p) { return __p.Arg; }

inline polar<float>     __cmf conj( polar<float> _VFARC & __p )
{   return polar<float>(__p.Mag, -__p.Arg); }

inline polar<double>     __cmf conj( polar<double> _VFARC & __p )
{   return polar<double>(__p.Mag, -__p.Arg); }

inline polar<long double> __cmf conj( polar<long double> _VFARC & __p )
{   return polar<long double>(__p.Mag, -__p.Arg); }


				// Binary operators:
inline polar<float> __cmf operator*( polar<float> _VFARC & __p1, polar<float> _VFARC & __p2)
{   return polar<float>( __p1.Mag * __p2.Mag, __p1.Arg + __p2.Arg );
}

inline polar<float> __cmf operator/( polar<float> _VFARC & __dividend,
									 polar<float> _VFARC & __divisor )
{   return polar<float>( __dividend.Mag / __divisor.Mag,
                         __dividend.Arg - __divisor.Arg );
}

inline polar<double> __cmf operator*( polar<double> _VFARC & __p1, polar<double> _VFARC & __p2)
{   return polar<double>( __p1.Mag * __p2.Mag, __p1.Arg + __p2.Arg );
}

inline polar<double> __cmf operator/( polar<double> _VFARC & __dividend,
                                      polar<double> _VFARC & __divisor )
{   return polar<double>( __dividend.Mag / __divisor.Mag,
                          __dividend.Arg - __divisor.Arg );
}

inline polar<long double> __cmf operator*( polar<long double> _VFARC & __p1, polar<long double> _VFARC & __p2)
{   return polar<long double>( __p1.Mag * __p2.Mag, __p1.Arg + __p2.Arg );
}

inline polar<long double> __cmf operator/( polar<long double> _VFARC & __dividend,
									   polar<long double> _VFARC & __divisor )
{   return polar<long double>( __dividend.Mag / __divisor.Mag,
							   __dividend.Arg - __divisor.Arg );
}

inline polar<float> __cmf operator*( polar<float> _VFARC & __p1, float __p2Re)
{   return polar<float>( __p1.Mag * __p2Re, __p1.Arg );
}

inline polar<double> __cmf operator*( polar<double> _VFARC & __p1, double __p2Re)
{   return polar<double>( __p1.Mag * __p2Re, __p1.Arg );
}

inline polar<long double> __cmf operator*( polar<long double> _VFARC & __p1, long double __p2Re)
{   return polar<long double>( __p1.Mag * __p2Re, __p1.Arg );
}

inline polar<float> __cmf operator*( float __p2Re, polar<float> _VFARC & __p1 )
{   return polar<float>( __p1.Mag * __p2Re, __p1.Arg );
}

inline polar<double> __cmf operator*( double __p2Re, polar<double> _VFARC & __p1 )
{   return polar<double>( __p1.Mag * __p2Re, __p1.Arg );
}

inline polar<long double> __cmf operator*( long double __p2Re, polar<long double> _VFARC & __p1 )
{   return polar<long double>( __p1.Mag * __p2Re, __p1.Arg );
}

inline polar<float> __cmf operator/( polar<float> _VFARC & __p1, float __p2Re)
{   return polar<float>( __p1.Mag / __p2Re, __p1.Arg );
}

inline polar<double> __cmf operator/( polar<double> _VFARC & __p1, double __p2Re)
{   return polar<double>( __p1.Mag / __p2Re, __p1.Arg );
}

inline polar<long double> __cmf operator/( polar<long double> _VFARC & __p1, long double __p2Re)
{   return polar<long double>( __p1.Mag / __p2Re, __p1.Arg );
}

	// Mixed-accuracy level binary operators:
inline polar<double> __cmf operator*( polar<float> _VFARC & __p1, polar<double> _VFARC & __p2 )
{   return polar<double>( __p1.Mag * __p2.Mag, __p1.Arg + __p2.Arg );
}
inline polar<double> __cmf operator*( polar<double> _VFARC & __p1, polar<float> _VFARC & __p2 )
{   return polar<double>( __p1.Mag * __p2.Mag, __p1.Arg + __p2.Arg );
}
inline polar<long double> __cmf operator*( polar<float> _VFARC & __p1, polar<long double> _VFARC & __p2 )
{   return polar<long double>( __p1.Mag * __p2.Mag, __p1.Arg + __p2.Arg );
}
inline polar<long double> __cmf operator*( polar<long double> _VFARC & __p1, polar<float> _VFARC & __p2 )
{   return polar<long double>( __p1.Mag * __p2.Mag, __p1.Arg + __p2.Arg );
}
inline polar<long double> __cmf operator*( polar<double> _VFARC & __p1, polar<long double> _VFARC & __p2 )
{   return polar<long double>( __p1.Mag * __p2.Mag, __p1.Arg + __p2.Arg );
}
inline polar<long double> __cmf operator*( polar<long double> _VFARC & __p1, polar<double> _VFARC & __p2 )
{   return polar<long double>( __p1.Mag * __p2.Mag, __p1.Arg + __p2.Arg );
}

inline polar<double> __cmf operator/( polar<double> _VFARC & __dividend,
									  polar<float>  _VFARC & __divisor )
{   return polar<double>( __dividend.Mag / __divisor.Mag,
                          __dividend.Arg - __divisor.Arg );
}

inline polar<double> __cmf operator/( polar<float> _VFARC & __dividend,
                                      polar<double>  _VFARC & __divisor )
{   return polar<double>( __dividend.Mag / __divisor.Mag,
                          __dividend.Arg - __divisor.Arg );
}

inline polar<long double> __cmf operator/( polar<long double> _VFARC & __dividend,
										   polar<float>  _VFARC & __divisor )
{   return polar<long double>( __dividend.Mag / __divisor.Mag,
                               __dividend.Arg - __divisor.Arg );
}

inline polar<long double> __cmf operator/( polar<float> _VFARC & __dividend,
                                           polar<long double>  _VFARC & __divisor )
{   return polar<long double>( __dividend.Mag / __divisor.Mag,
                               __dividend.Arg - __divisor.Arg );
}

inline polar<long double> __cmf operator/( polar<long double> _VFARC & __dividend,
                                           polar<double>  _VFARC & __divisor )
{   return polar<long double>( __dividend.Mag / __divisor.Mag,
                               __dividend.Arg - __divisor.Arg );
}

inline polar<long double> __cmf operator/( polar<double> _VFARC & __dividend,
										   polar<long double>  _VFARC & __divisor )
{   return polar<long double>( __dividend.Mag / __divisor.Mag,
							   __dividend.Arg - __divisor.Arg );
}

inline VBOOL __cmf operator==(polar<float> _VFARC & __p1, polar<float> _VFARC & __p2)
{   return __p1.Mag == __p2.Mag && __p1.Arg == __p2.Arg; }

inline VBOOL __cmf operator==(float __z1Re, polar<float> _VFARC & __p2)
{   return __z1Re == __p2.Mag && __p2.Arg == 0; }

inline VBOOL __cmf operator==(polar<float> _VFARC & __p1, float __z2Re)
{   return __p1.Mag == __z2Re && __p1.Arg == 0; }

inline VBOOL __cmf operator!=(polar<float> _VFARC & __p1, polar<float> _VFARC & __p2)
{   return __p1.Mag != __p2.Mag || __p1.Arg != __p2.Arg; }

inline VBOOL __cmf operator!=(float __z1Re, polar<float> _VFARC & __p2)
{   return __z1Re != __p2.Mag || __p2.Arg != 0; }

inline VBOOL __cmf operator!=(polar<float> _VFARC & __p1, float __z2Re)
{   return __p1.Mag != __z2Re || __p1.Arg != 0; }

inline VBOOL __cmf operator==(polar<double> _VFARC & __p1, polar<double> _VFARC & __p2)
{   return __p1.Mag == __p2.Mag && __p1.Arg == __p2.Arg; }

inline VBOOL __cmf operator==(double __z1Re, polar<double> _VFARC & __p2)
{   return __z1Re == __p2.Mag && __p2.Arg == 0; }

inline VBOOL __cmf operator==(polar<double> _VFARC & __p1, double __z2Re)
{   return __p1.Mag == __z2Re && __p1.Arg == 0; }

inline VBOOL __cmf operator!=(polar<double> _VFARC & __p1, polar<double> _VFARC & __p2)
{   return __p1.Mag != __p2.Mag || __p1.Arg != __p2.Arg; }

inline VBOOL __cmf operator!=(double __z1Re, polar<double> _VFARC & __p2)
{   return __z1Re != __p2.Mag || __p2.Arg != 0; }

inline VBOOL __cmf operator!=(polar<double> _VFARC & __p1, double __z2Re)
{   return __p1.Mag != __z2Re || __p1.Arg != 0; }

inline VBOOL __cmf operator==(polar<long double> _VFARC & __p1, polar<long double> _VFARC & __p2)
{   return __p1.Mag == __p2.Mag && __p1.Arg == __p2.Arg; }

inline VBOOL __cmf operator==(long double __z1Re, polar<long double> _VFARC & __p2)
{   return __z1Re == __p2.Mag && __p2.Arg == 0; }

inline VBOOL __cmf operator==(polar<long double> _VFARC & __p1, long double __z2Re)
{   return __p1.Mag == __z2Re && __p1.Arg == 0; }

inline VBOOL __cmf operator!=(polar<long double> _VFARC & __p1, polar<long double> _VFARC & __p2)
{   return __p1.Mag != __p2.Mag || __p1.Arg != __p2.Arg; }

inline VBOOL __cmf operator!=(long double __z1Re, polar<long double> _VFARC & __p2)
{   return __z1Re != __p2.Mag || __p2.Arg != 0; }

inline VBOOL __cmf operator!=(polar<long double> _VFARC & __p1, long double __z2Re)
{   return __p1.Mag != __z2Re || __p1.Arg != 0; }

	 // Compound-assignment operators:
inline polar<float> _VFAR & __cmo polar<float>::operator*=(polar<float> _VFARC & __fac2)
{   Mag *= __fac2.Mag;
    Arg += __fac2.Arg;
    return *this;
}

inline polar<float> _VFAR & __cmo polar<float>::operator*=(polar<double> _VFARC & __fac2)
{   Mag = (float)(Mag * __fac2.Mag);
    Arg = (float)(Arg + __fac2.Arg);
    return *this;
}

inline polar<float> _VFAR & __cmo polar<float>::operator*=(polar<long double> _VFARC & __fac2)
{   Mag = (float)(Mag * __fac2.Mag);
    Arg = (float)(Arg + __fac2.Arg);
	return *this;
}

inline polar<double> _VFAR & __cmo polar<double>::operator*=(polar<float> _VFARC & __fac2)
{   Mag *= __fac2.Mag;
    Arg += __fac2.Arg;
    return *this;
}

inline polar<double> _VFAR & __cmo polar<double>::operator*=(polar<double> _VFARC & __fac2)
{   Mag *= __fac2.Mag;
    Arg += __fac2.Arg;
    return *this;
}

inline polar<double> _VFAR & __cmo polar<double>::operator*=(polar<long double> _VFARC & __fac2)
{   Mag = (double)(Mag * __fac2.Mag);
    Arg = (double)(Arg + __fac2.Arg);
    return *this;
}

inline polar<long double> _VFAR & __cmo polar<long double>::operator*=(polar<float> _VFARC & __fac2)
{   Mag *= __fac2.Mag;
    Arg += __fac2.Arg;
    return *this;
}

inline polar<long double> _VFAR & __cmo polar<long double>::operator*=(polar<double> _VFARC & __fac2)
{   Mag *= __fac2.Mag;
    Arg += __fac2.Arg;
    return *this;
}

inline polar<long double> _VFAR & __cmo polar<long double>::operator*=(polar<long double> _VFARC & __fac2)
{   Mag *= __fac2.Mag;
    Arg += __fac2.Arg;
    return *this;
}

inline polar<float> _VFAR & __cmo polar<float>::operator/=(polar<float> _VFARC & __divisor)
{   Mag /= __divisor.Mag;
    Arg -= __divisor.Arg;
    return *this;
}

inline polar<float> _VFAR & __cmo polar<float>::operator/=(polar<double> _VFARC & __divisor)
{   Mag = (float)(Mag / __divisor.Mag);
    Arg = (float)(Arg - __divisor.Arg);
    return *this;
}

inline polar<float> _VFAR & __cmo polar<float>::operator/=(polar<long double> _VFARC & __divisor)
{   Mag = (float)(Mag / __divisor.Mag);
    Arg = (float)(Arg - __divisor.Arg);
    return *this;
}

inline polar<double> _VFAR & __cmo polar<double>::operator/=(polar<float> _VFARC & __divisor)
{   Mag /= __divisor.Mag;
	Arg -= __divisor.Arg;
	return *this;
}

inline polar<double> _VFAR & __cmo polar<double>::operator/=(polar<double> _VFARC & __divisor)
{   Mag /= __divisor.Mag;
    Arg -= __divisor.Arg;
    return *this;
}

inline polar<double> _VFAR & __cmo polar<double>::operator/=(polar<long double> _VFARC & __divisor)
{   Mag = (double)(Mag / __divisor.Mag);
    Arg = (double)(Arg - __divisor.Arg);
    return *this;
}

inline polar<long double> _VFAR & __cmo polar<long double>::operator/=(polar<float> _VFARC & __divisor)
{   Mag /= __divisor.Mag;
    Arg -= __divisor.Arg;
    return *this;
}

inline polar<long double> _VFAR & __cmo polar<long double>::operator/=(polar<double> _VFARC & __divisor)
{   Mag /= __divisor.Mag;
    Arg -= __divisor.Arg;
    return *this;
}

inline polar<long double> _VFAR & __cmo polar<long double>::operator/=(polar<long double> _VFARC & __divisor)
{   Mag /= __divisor.Mag;
    Arg -= __divisor.Arg;
    return *this;
}

inline polar<float> _VFAR & __cmo polar<float>::operator*=(float __fac2)
{   Mag *= __fac2;
    return *this;
}

inline polar<double> _VFAR & __cmo polar<double>::operator*=(double __fac2)
{   Mag *= __fac2;
	return *this;
}

inline polar<long double> _VFAR & __cmo polar<long double>::operator*=(long double __fac2)
{   Mag *= __fac2;
    return *this;
}

inline polar<float> _VFAR & __cmo polar<float>::operator/=(float __fac2)
{   Mag /= __fac2;
    return *this;
}

inline polar<double> _VFAR & __cmo polar<double>::operator/=(double __fac2)
{   Mag /= __fac2;
	return *this;
}

inline polar<long double> _VFAR & __cmo polar<long double>::operator/=(long double __fac2)
{   Mag /= __fac2;
    return *this;
}

inline __cmistream _VFAR &  __cmf operator>>(__cmistream _VFAR & is, polar<float> _VFAR & __p)
{   // read a polar number __p in the form r or (r) or {m, a} or (m, a)
	//                                       or (m@a) or {m@a}
	float  m = 0, a = 0;
	char  c;

	is >> c;
	if (c == '(' || c == '{')  // notations (r), (m,a), {m,a}, (m@a), {mQa}
	{
		is >> m >> c;
		if (c == ',' || c == '@') { is >> a  >> c;}
		if (c != ')' && c != '}')   is.clear(__cmios::failbit);
	}
	else  // only real part
	{
		is.putback(c);
		is >> m;
	}
	if (is) { __p.Mag = m; __p.Arg = a; }
	return is;
}

inline __cmostream _VFAR &  __cmf operator<<(__cmostream _VFAR & os, polar<float> _VFARC & __p)
{   return (os << "{" << __p.Mag << "@" << __p.Arg << "}"); }

inline __cmistream _VFAR &  __cmf operator>>(__cmistream _VFAR & is, polar<double> _VFAR & __p)
{   // read a polar number __p in the form r or (r) or {m, a} or (m, a)
	//                                       or (m@a) or {m@a}
    double  m = 0, a = 0;
    char    c;

    is >> c;
	if (c == '(' || c == '{')  // notations (r), (m,a), {m,a}, (m@a), {mQa}
    {
        is >> m >> c;
        if (c == ',' || c == '@') { is >> a  >> c;}
        if (c != ')' && c != '}')   is.clear(__cmios::failbit);
    }
    else  // only real part
	{
        is.putback(c);
        is >> m;
    }
    if (is) { __p.Mag = m; __p.Arg = a; }
    return is;
}

inline __cmostream _VFAR &  __cmf operator<<(__cmostream _VFAR & os, polar<double> _VFARC & __p)
{   return (os << "{" << __p.Mag << "@" << __p.Arg << "}"); }

inline __cmistream _VFAR &  __cmf operator>>(__cmistream _VFAR & is, polar<long double> _VFAR & __p)
{   // read a polar number __p in the form r or (r) or {m, a} or (m, a)
	//                                       or (m@a) or {m@a}
    float  m = 0, a = 0;
    char  c;

    is >> c;
	if (c == '(' || c == '{')  // notations (r), (m,a), {m,a}, (m@a), {mQa}
    {
        is >> m >> c;
        if (c == ',' || c == '@') { is >> a  >> c;}
        if (c != ')' && c != '}')   is.clear(__cmios::failbit);
    }
    else  // only real part
	{
		is.putback(c);
		is >> m;
	}
	if (is) { __p.Mag = m; __p.Arg = a; }
	return is;
}

inline __cmostream _VFAR &  __cmf operator<<(__cmostream _VFAR & os, polar<long double> _VFARC & __p)
{   return (os << "{" << __p.Mag << "@" << __p.Arg << "}"); }

#endif // CMATH_CLASSIC_COMPLEX


#if (defined __BORLANDC__) && !(defined _WIN64)
	typedef long double extended;
#else
	typedef double extended; /* Win64 and Visual C++ do not support 80-bit IEEE numbers. 
							 So make extended equal to double    */
#endif
#if defined( CMATH_CLASSIC_COMPLEX )
	typedef struct {float  Re, Im;} fComplex;
	typedef complex  dComplex;
	#if (defined __BORLANDC__) && !(defined _WIN64)
		typedef struct {extended Re, Im;} eComplex;
	#else /* Watcom, Visual C++ */
		typedef dComplex  eComplex;
	#endif
#else  // not defined( CMATH_CLASSIC_COMPLEX )
	typedef complex<float>      fComplex;
	typedef complex<double>     dComplex;
	typedef complex<extended>   eComplex; // for MSVC and BCC64, this will be complex<double>, not complex<long double> !
	#define _CMATH_CLASSDEFS
#endif
typedef polar<float>    fPolar;
typedef polar<double>   dPolar;
typedef polar<extended> ePolar; // for MSVCand BCC64, this will be polar<double>
#define _POLAR_CLASSDEFS
#define _CMATH_DEFS
	
#ifdef __BORLANDC__
	  #pragma option -a.
#else /* Visual C++ */
	  #pragma pack( pop )
#endif    /* restore default data packing  */

       /* error handling functions, borrowed from VectorLib:  */
extern "C" {
void  __cmf  V_noteError( char _VFAR *fname, unsigned why );
void  __cmf  V_printErrorMsg( char _VFAR *ErrMsg );
void  __cmf  V_setErrorEventFile( char _VFAR *filename,  unsigned ScreenAndFile );
void  __cmf  V_closeErrorEventFile( void );

}  // end of extern "C" statement

#undef VBOOL
#undef CMATH_NEW_TEMPLATE
#undef __cmf
#undef __cmo
#undef __cmios
#undef __cmistream
#undef __cmostream
typedef fComplex fcomplex;
typedef dComplex dcomplex;
typedef eComplex ecomplex;
typedef fPolar   fpolar;
typedef dPolar   dpolar;
typedef ePolar   epolar;  // tolerate all-lower case
#ifdef _MSC_VER
    #pragma warning(default: 4244)
#endif
#if defined (__BORLANDC__) && (__BORLANDC__ >= 0x550)
    #pragma warn .8026
#endif
#endif  // __NEWCPLX_H
