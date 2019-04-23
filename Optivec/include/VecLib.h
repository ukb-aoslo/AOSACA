/*  VecLib.h

  vector management functions.

  Contains the basic definitions for VectorLib.

  Copyright (c) 1996-2017 by OptiCode - Dr. Martin Sander Software Dev.
  All Rights Reserved.
*/

#ifndef __VECLIB_H
#define __VECLIB_H

/*    #define V_trapIntError 1   */
           /*  activate this line, if you wish to generate an error
               message and/or terminate program execution in case
               of INTEGER OVERFLOW or INTEGER DOMAIN errors!
               Additionally, you have to make one call to
               V_setIntErrorHandling with either ierrNote or
               ierrAbort as argument.    */

#include <stdio.h>
#if (defined __BORLANDC__) && !(defined _WIN64)
       /* the following statements apply to
          VectorLib for Embarcadero / Borland C++ 32-bit */
    #ifndef _WINDOWS
        #define _WINDOWS
    #endif
    #include <windows.h>

    #define  _VFAR
    #define  V_DATAPTR
    typedef   unsigned int    ui;
    #if !defined ssize_t
        typedef int ssize_t;
    #endif   /* signed size_t  */
    #if (__BORLANDC__ >= 0x450)
         #define __vf _RTLENTRY _EXPFUNC
    #else
         #define __vf  _Cdecl _FARFUNC
    #endif
    #pragma option -a-  /* avoid insertion of dummy bytes in eComplex */

	#if __BORLANDC__ >= 0x570  /* C++ Builder 2006 or higher */
		typedef __int64 quad; /* "quadruple int", 64 bit */
	#else   /* maintain compatibility with older BC versions which did not directly support 64-bit integers: */
		typedef  struct { long Lo, Hi; }  quad;  /* "quadruple int", 64 bit */
	#endif
    #if !defined( _CMATH_DEFS )
       typedef long double  extended; /* 32-bit Borland C supports IEEE 80-bit real numbers */
       typedef struct {float    Re,  Im;}  fComplex;
       typedef struct {double   Re,  Im;}  dComplex;
       typedef struct {extended Re,  Im;}  eComplex;
       typedef struct {float    Mag, Arg;} fPolar;
       typedef struct {double   Mag, Arg;} dPolar;
       typedef struct {extended Mag, Arg;} ePolar;
       typedef fComplex fcomplex;
       typedef dComplex dcomplex;
       typedef eComplex ecomplex;
       typedef fPolar fpolar;
       typedef dPolar dpolar;
       typedef ePolar epolar;  // tolerate all-lower case
       #define _CMATH_DEFS
    #endif
    #pragma option -a.   /* restore default data packing  */

#else  /* the following definitions apply to:
          OptiVec for Microsoft Visual C++,
		  OptiVec for 64-bit Embarcadero RAD Studio,
          OptiVec for Powersoft Optima++ */
    #if !defined(_WIN32)
        #error ERROR: Only Win32 and Win64 targets supported!
    #endif
    #if (defined _MSC_VER) || (defined __BORLANDC__)
        #include <windows.h>
    #endif
    #ifndef _WINDOWS
        #define _WINDOWS
    #endif
    #define __vf  __cdecl
    #define   _VFAR
    #define   V_DATAPTR
    typedef  size_t  ui;
    typedef __int64 quad; /* "quadruple int", 64 bit */
    #ifdef _WIN64
        typedef unsigned __int64 uquad;  /* unsigned "quadruple int", available only in Win64 version */
        #if !defined ssize_t
            typedef __int64 ssize_t;
        #endif   /* signed size_t  */
    #else
        #if !defined ssize_t
            typedef int ssize_t;
        #endif   /* signed size_t  */
    #endif
    #if !defined( _CMATH_DEFS )
       typedef  double extended; /* Visual C++, BCC64 and Optima++ do not
                                    support 80-bit IEEE numbers.
                                    So make extended equal to double. */
       typedef struct {float    Re,  Im;}  fComplex;
       typedef struct {float    Mag, Arg;} fPolar;
       typedef struct {double   Re,  Im;}  dComplex;
       typedef struct {double   Mag, Arg;} dPolar;
       typedef dComplex                    eComplex;
       typedef dPolar                      ePolar;
       typedef fComplex fcomplex;
       typedef dComplex dcomplex;
       typedef eComplex ecomplex;
       typedef fPolar   fpolar;
       typedef dPolar   dpolar;
       typedef ePolar   epolar;   // tolerate all-lower case
       #define _CMATH_DEFS
    #endif
#endif    /*  Borland C/C++, Visual C++, or Optima++ */

typedef   int   overror_t;

typedef   char           V_DATAPTR *    biVector;
typedef   short          V_DATAPTR *    siVector;
typedef   int            V_DATAPTR *    iVector;
typedef   long           V_DATAPTR *    liVector;
typedef   quad           V_DATAPTR *    qiVector;
typedef   unsigned char  V_DATAPTR *    ubVector;
typedef   unsigned short V_DATAPTR *    usVector;
typedef   unsigned int   V_DATAPTR *    uVector;
typedef   unsigned long  V_DATAPTR *    ulVector;
#ifdef _WIN64
    typedef   uquad      V_DATAPTR *    uqVector; 
#endif
typedef   ui             V_DATAPTR *    uiVector;
typedef   float          V_DATAPTR *    fVector;
typedef   double         V_DATAPTR *    dVector;
typedef   extended       V_DATAPTR *    eVector;
typedef   fComplex       V_DATAPTR *    cfVector;
typedef   dComplex       V_DATAPTR *    cdVector;
typedef   eComplex       V_DATAPTR *    ceVector;
typedef   fPolar         V_DATAPTR *    pfVector;
typedef   dPolar         V_DATAPTR *    pdVector;
typedef   ePolar         V_DATAPTR *    peVector;
#undef V_DATAPTR

#ifdef __cplusplus
extern "C" {
#endif

/** Allocation of memory is specific for the respective data type and
    is consequently included in VFstd.h etc.                            */

/*    Freeing memory is the same for all data types: */

void  __vf  V_free( void _VFAR *X );
void  __vf  V_freeAll( void );  /* frees all vectors allocated by V.._vector */
void  __vf  V_nfree( unsigned numfree,...); /* e.g., V_nfree( 2, X, Y ); */
#if defined (_MSC_VER) && defined (_DEBUG)
    void  __vf  V_free_dbg( void _VFAR *X );
    void  __vf  V_freeAll_dbg( void );
    void  __vf  V_nfree_dbg( unsigned numfree,...); 
    #if defined (_INC_CRTDBG) && defined (_CRTDBG_MAP_ALLOC) 
	    /* Automatic mapping for memory-leak detection by CRT debugging switched on? */ 
        #define V_free     V_free_dbg
        #define V_freeAll  V_freeAll_dbg
        #define V_nfree    V_nfree_dbg
    #endif
#else
    #define V_free_dbg     V_free
    #define V_freeAll_dbg  V_freeAll
    #define V_nfree_dbg    V_nfree
#endif

/************  Controlling FPU accuracy (does not affect SIMD) ***************/
void     __vf V_setFPAccuracy(unsigned level);/*1:float, 2:double, 3:extended*/
unsigned __vf V_getFPAccuracy(void);

/************ State used in random functions *********************************/
typedef struct V_RANDOMLCSTATE
{	unsigned long v[35];
	long          seed;
} V_RANDOMLCSTATE;

/********  user-accessible error handling functions ***************/

void  __vf  V_noteError( char _VFAR *fname, unsigned why );
void  __vf  V_printErrorMsg( char _VFAR *ErrMsg );
void  __vf  V_setErrorEventFile( char _VFAR *filename,  unsigned ScreenAndFile );
void  __vf  V_closeErrorEventFile( void );
#ifdef _WIN64
	void  __vf  V_checkBoundaries( void _VFAR *X, ui size, int FlagRW, 
									char _VFAR *funcname, char _VFAR *parname );
#else
	void  __vf  V_checkBoundaries( void _VFAR *X, ui size, int FlagRW, char _VFAR *funcname );
#endif
/*  X: vector of any type;  size: size in bytes;  FlagRW: 0=read, 1=write; 
	funcname: name of calling function;  parname (WIN64 only): name of offending vector */

	void  __vf  V_setBoundaryCheckWarn( int WarnLevel );
/* WarnLevel=0: tolerate static and other non-OptiVec vectors; 1: warn */ 

/* disable obsolete macro: */
#define NEWMATHERR

/***********  Multi-Processor Optimization  ***********************/

int   __vf  V_initMT( unsigned nProcessorCores );
int   __vf  V_closeMT( void );

/************ Integer OVERFLOW handling **************************/

typedef enum
{
         ierrIgnore = 0,
         ierrNote,
         ierrAbort
}   V_ihand;

void __vf  V_setIntErrorHandling( V_ihand a );

#if defined __cplusplus && defined _CMATH_CLASSDEFS
}   // the following functions cannot be "extern C",
	// if fComplex, fPolar etc. are classes
#endif

        /*  constructors of complex data types:   */
fComplex __vf fcplx( float    __ReVal,  float    __ImVal );
dComplex __vf dcplx( double   __ReVal,  double   __ImVal );
fPolar   __vf fpolr( float    __MagVal, float    __ArgVal );
dPolar   __vf dpolr( double   __MagVal, double   __ArgVal );
#if (defined __BORLANDC__) && !(defined _WIN64)
   eComplex __vf ecplx( extended __ReVal,  extended __ImVal);
   ePolar   __vf epolr( extended __MagVal, extended __ArgVal );
#else  /* Visual C++, Optima++, BCC64 */
   #define ecplx dcplx
   #define epolr dpolr
#endif

#if defined __cplusplus && !defined _CMATH_CLASSDEFS
}   // end of "extern C",
#endif

	/*  for overloaded constructors and for all scalar (i.e., "non-vector")
         operations on complex numbers, see CMATH with the include-files 
		 <newcplx.h> and <cmath.h> !                                        */

#endif  /*  __VECLIB_H  */
