/*  VPFstd.h

  vector management functions:
  manipulations on whole arrays or vectors of data type "fPolar"
  (single-precision polar complex numbers)

  Copyright (c) 1996-2017 by OptiCode - Dr. Martin Sander Software Dev.
  All Rights Reserved.
*/

#ifndef __VPFSTD_H
#define __VPFSTD_H
#if !defined( __VECLIB_H )
#include <VecLib.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif

/*************************  Generation  **************************/

pfVector  __vf  VPF_vector( ui size );
pfVector  __vf  VPF_vector0( ui size );
#if defined (_MSC_VER) && defined (_DEBUG)
    pfVector  __vf  VPF_vector_dbg( ui size );
    pfVector  __vf  VPF_vector0_dbg( ui size );
    #if defined (_INC_CRTDBG) && defined (_CRTDBG_MAP_ALLOC) 
	    /* Automatic mapping for memory-leak detection by CRT debugging switched on? */ 
        #define VPF_vector  VPF_vector_dbg
        #define VPF_vector0 VPF_vector0_dbg
    #endif
#else
    #define VPF_vector_dbg  VPF_vector
    #define VPF_vector0_dbg VPF_vector0
#endif

/***************  Addressing single vector elements ******************/

fPolar _VFAR * __vf VPF_Pelement( pfVector X, ui n );
      /* returns a pointer to the n'th element of X. For the memory model
         HUGE, the pointer is normalized. */
#define VPF_element( X, n )  (*VPF_Pelement( X, n ))
#if defined __cplusplus && defined _CMATH_CLASSDEFS && defined __BORLANDC__ && defined _WIN64
} // for C++Builder on Win64, the following functions cannot be extern "C", if fComplex is a class
#endif
void  __vf VPF_getElement( fPolar *y, pfVector X, ui n );
void  __vf VPF_setElement( pfVector X, ui n, fPolar C );
#if defined __cplusplus && defined _CMATH_CLASSDEFS && defined __BORLANDC__ && defined _WIN64
extern "C" {
#endif

/*******************  Initialization **********************************/

void  __vf  VPF_equ0( pfVector X, ui size );
void  __vf  VPF_equ1( pfVector X, ui size );
void  __vf  VPF_equm1( pfVector X, ui size );
#if defined __cplusplus && defined _CMATH_CLASSDEFS && defined __BORLANDC__ && defined _WIN64
} // cannot be extern "C" for C++Builder on Win64, if fPolar is a class
#endif
void  __vf  VPF_equC( pfVector X, ui size, fPolar C );
#if defined __cplusplus && defined _CMATH_CLASSDEFS && defined __BORLANDC__ && defined _WIN64
extern "C" {
#endif
void  __vf  VPF_equV( pfVector Y, pfVector X, ui size );
void  __vf  VPF_principal( pfVector Y, pfVector X, ui size );

void  __vf  VF_PtoMagArg( fVector Mag, fVector Arg, pfVector X, ui size );
void  __vf  VF_MagArgtoP( pfVector Y, fVector Mag, fVector Arg, ui size );
void  __vf  VF_MagArgtoPrincipal( pfVector Y,
                                  fVector Mag, fVector Arg, ui size );
void  __vf  VF_PtoMag(  fVector Mag, pfVector X, ui size );
void  __vf  VF_MagtoP(  pfVector Y, fVector Mag, ui size );
void  __vf  VF_PtoArg(  fVector Arg, pfVector X, ui size );
void  __vf  VF_ArgtoP(  pfVector Y, fVector Arg, ui size );
void  __vf  VF_CtoP( pfVector YP, cfVector XC, ui size );
void  __vf  VF_PtoC( cfVector YC, pfVector XP, ui size );
void  __vf  VF_PtoNorm( fVector Norm, pfVector X, ui size );
void  __vf  VF_PtoReIm( fVector Re, fVector Im, pfVector X, ui size );
void  __vf  VF_ReImtoP( pfVector Y, fVector Re, fVector Im, ui size );
void  __vf  VF_PtoRe( fVector Re, pfVector X, ui size );
void  __vf  VF_PtoIm( fVector Im, pfVector X, ui size );
int   __vf  VPF_abs(   fVector Y, pfVector X, ui size );
#define     VPF_real       VF_PtoRe
#define     VPF_imag       VF_PtoIm
#define     VPF_arg        VF_PtoArg
#define     VPF_norm       VF_PtoNorm

/****************  Data-type interconversions  ***************************/

void  __vf   V_PFtoPD( pdVector Y, pfVector X, ui size );
void  __vf   V_PDtoPF( pfVector Y, pdVector X, ui size );
#if (defined __BORLANDC__) && !(defined _WIN64)   /* 80-bit IEEE numbers supported */
    void  __vf   V_PFtoPE( peVector Y, pfVector X, ui size );
    void  __vf   V_PEtoPF( pfVector Y, peVector X, ui size );
#else  /* no IEEE number support for other compilers */
    #define V_PFtoPE V_PFtoPD
    #define V_PEtoPF V_PDtoPF
#endif


/****************  Index-oriented manipulations ***********************/

void  __vf  VPF_reflect( pfVector X, ui size );
void  __vf  VPF_delete( pfVector X, ui size, ui pos );
#if defined __cplusplus && defined _CMATH_CLASSDEFS && defined __BORLANDC__ && defined _WIN64
} // cannot be extern "C" for C++Builder on Win64, if fPolar is a class
#endif
void  __vf  VPF_insert( pfVector X, ui size, ui pos, fPolar C );
#if defined __cplusplus && defined _CMATH_CLASSDEFS && defined __BORLANDC__ && defined _WIN64
extern "C" {
#endif
void  __vf  VPF_rev( pfVector Y, pfVector X, ui size );
void  __vf  VPF_rotate( pfVector Y, pfVector X, ui size, ssize_t pos );
void  __vf  VPF_rotate_buf( pfVector Y, pfVector X, ui size, ssize_t pos, pfVector Buf );

void  __vf  VPF_indpick( pfVector Y, uiVector Ind, ui sizey, pfVector X );
void  __vf  VPF_indput(  pfVector Y, pfVector X, uiVector Ind, ui sizex );
void  __vf  VPF_subvector( pfVector Y, ui sizey, pfVector X, ssize_t samp );


/*************** Functions of a sub-set of elements  ********************/

#if defined __cplusplus && defined _CMATH_CLASSDEFS && defined __BORLANDC__ && defined _WIN64
} // cannot be extern "C" for C++Builder on Win64, if fPolar is a class
#endif
void  __vf  VPF_subvector_equC(  pfVector Y, ui subsiz, ui samp,
                                 fPolar C );
#if defined __cplusplus && defined _CMATH_CLASSDEFS && defined __BORLANDC__ && defined _WIN64
extern "C" {
#endif
void  __vf  VPF_subvector_equV(  pfVector Y, ui subsiz, ui samp,
                                 pfVector X );
    /*   for arithmetic functions of subsets, see <VPFmath.h>  */

/**************** One-Dimensional Vector Operations ***********************/

float     __vf  VPF_absmax(  pfVector X, ui size );
float     __vf  VPF_absmin(  pfVector X, ui size );
float     __vf  VPF_absmaxind( ui _VFAR *pos, pfVector X, ui size );
float     __vf  VPF_absminind( ui _VFAR *pos, pfVector X, ui size );
#if defined __cplusplus && defined _CMATH_CLASSDEFS
} // the following functions cannot be extern "C", if fPolar is a class
#endif
fPolar  __vf  VPF_prod(    pfVector X, ui size );
#if defined __cplusplus && defined _CMATH_CLASSDEFS
extern "C" {
#endif
void      __vf  VPF_runprod( pfVector Y, pfVector X, ui size );
#if defined __cplusplus && defined _CMATH_CLASSDEFS && defined __BORLANDC__ && defined _WIN64
} // cannot be extern "C" for C++Builder on Win64, if fPolar is a class
#endif
int       __vf  VPF_iselementC( pfVector Tab, ui size, fPolar C );
#if defined __cplusplus && defined _CMATH_CLASSDEFS && defined __BORLANDC__ && defined _WIN64
extern "C" {
#endif
ui        __vf  VPF_iselementV( pfVector Y, pfVector X, ui sizex,
                                pfVector Tab, ui sizetab );


/***************************  Input and Output *****************************/

void  __vf  VPF_fprint( FILE _VFAR *stream, pfVector X, ui size,
                         unsigned nperline, unsigned linewidth );
void  __vf  VPF_cprint( pfVector X, ui size, unsigned nperline );
#define     VPF_print( X, sz, npl ) VPF_fprint( stdout, X, sz, npl, 80 )
  /*  VPF_print, VPF_cprint usable only for console applications! */
void  __vf  VPF_write( FILE _VFAR *stream, pfVector X, ui size );
void  __vf  VPF_nwrite( FILE _VFAR *stream, unsigned n, ui size, ... );
void  __vf  VPF_setWriteFormat( char _VFAR *FormatString );
                                       /* for VPF_write and VPF_nwrite */
void  __vf  VPF_setWriteSeparate( char _VFAR *SepString ); /* for VPF_write */
void  __vf  VPF_setNWriteSeparate( char _VFAR *SepString ); /* for VPF_nwrite */
#if !((defined __BORLANDC__) && (__BORLANDC__ < 0x710))
		/* modern compiler versions:  */
	void  __vf    VPF_read( pfVector X, ui size, FILE _VFAR *stream );
	void  __vf    VPF_nread( unsigned n, ui size, FILE _VFAR *stream, ... );
#else /* older Borland compiler versions need separate implementation */
	void  __vf    VPF_read1( pfVector X, ui size, FILE _VFAR *stream );
	void  __vf    VPF_nread1( unsigned n, ui size, FILE _VFAR *stream, ... );
	#define VPF_read  VPF_read1
	#define VPF_nread VPF_nread1
#endif
#ifdef V_HUGE
    void  __vf  VPF_store( FILE *stream, pfVector X, ui size );
    void  __vf  VPF_recall( pfVector X, ui size, FILE _VFAR *stream  );
#else
    #ifdef __cplusplus
         void  inline VPF_store( FILE _VFAR *stream, pfVector X, ui size )
         {    fwrite( X, sizeof(fPolar), size, stream );
         }
         void  inline VPF_recall( pfVector X, ui size, FILE _VFAR *stream )
         {    fread(  X, sizeof(fPolar), size, stream );
         }
    #else
        #define VPF_store( str, X, sz )  \
                     fwrite( X, sizeof(fPolar), sz, str )
        #define VPF_recall( X, sz, str ) \
                     fread(  X, sizeof(fPolar), sz, str )
    #endif
#endif      /* VPF_store, VPF_recall in binary format */

#ifdef __cplusplus
}  // end of extern "C"
#endif

#endif /*  __VPFSTD_H */
