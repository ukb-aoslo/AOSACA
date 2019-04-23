/*  VCDstd.h

  vector management functions:
  manipulations on whole arrays or vectors of data type dComplex
  (double-precision complex numbers)

  Copyright (c) 1996-2017 by OptiCode - Dr. Martin Sander Software Dev.
  All Rights Reserved.
*/

#ifndef __VCDSTD_H
#define __VCDSTD_H
#if !defined( __VECLIB_H )
#include <VecLib.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif

/*************************  Generation  **************************/

cdVector  __vf  VCD_vector( ui size );
cdVector  __vf  VCD_vector0( ui size );
#if defined (_MSC_VER) && defined (_DEBUG)
    cdVector  __vf  VCD_vector_dbg( ui size );
    cdVector  __vf  VCD_vector0_dbg( ui size );
    #if defined (_INC_CRTDBG) && defined (_CRTDBG_MAP_ALLOC) 
	    /* Automatic mapping for memory-leak detection by CRT debugging switched on? */ 
        #define VCD_vector  VCD_vector_dbg
        #define VCD_vector0 VCD_vector0_dbg
    #endif
#else
    #define VCD_vector_dbg  VCD_vector
    #define VCD_vector0_dbg VCD_vector0
#endif

/***************  Addressing single vector elements ******************/

dComplex _VFAR * __vf VCD_Pelement( cdVector X, ui n );
      /* returns a pointer to the n'th element of X. For the memory model
         HUGE, the pointer is normalized. */
#define VCD_element( X, n )  (*VCD_Pelement( X, n ))
void __vf VCD_getElement( dComplex *y, cdVector X, ui n );
void __vf VCD_setElement( cdVector X, ui n, dComplex C );

/*******************  Initialization **********************************/

void  __vf  VCD_equ0( cdVector X, ui size );
void  __vf  VCD_equ1( cdVector X, ui size );
void  __vf  VCD_equm1( cdVector X, ui size );
void  __vf  VCD_equC( cdVector X, ui size, dComplex C );
void  __vf  VCD_equV( cdVector Y, cdVector X, ui size );
void  __vf  VCDx_equV( cdVector Y, cdVector X, ui size,
                       dComplex A, dComplex B );
void  __vf  VCD_ramp( cdVector X, ui size, dComplex Start, dComplex Rise );
/******  Linear Congruential random generator with Bays-Durham shuffle:  ***********
  seed!=0 --> initialization of state. seed==0 --> continue series from previous call with the same state. */
void  __vf  VCD_randomLC( cdVector X, ui size, long seed, dComplex MinVal, dComplex MaxVal, V_RANDOMLCSTATE *state );
/**  simplified version: returns new seed. Series not continuous across calls due to new state initialization: */
long  __vf  VCD_random( cdVector X, ui size, long seed, dComplex MinVal, dComplex MaxVal );

void  __vf  VD_CtoReIm( dVector Re, dVector Im, cdVector X, ui size );
void  __vf  VD_ReImtoC( cdVector Y, dVector Re, dVector Im, ui size );
void  __vf  VD_CtoRe( dVector Re, cdVector X, ui size );
void  __vf  VD_RetoC( cdVector Y, dVector Re, ui size );
void  __vf  VD_CtoIm( dVector Im, cdVector X, ui size );
void  __vf  VD_ImtoC( cdVector Y, dVector Im, ui size );
void  __vf  VD_CtoPolar( dVector Mag, dVector Arg, cdVector X, ui size );
void  __vf  VD_PolartoC( cdVector Y, dVector Mag, dVector Arg, ui size );
void  __vf  VD_CtoNorm( dVector Norm, cdVector X, ui size );
void  __vf  VD_CtoAbs( dVector Abs, cdVector X, ui size );
void  __vf  VD_CtoArg( dVector Arg, cdVector X, ui size );
int   __vf  VCD_abs(   dVector Y, cdVector X, ui size );
void  __vf  VCD_normtoC( cdVector Norm, cdVector X, ui size );
#define     VCD_real( Y, X, sz )         VD_CtoRe( Y, X, sz )
#define     VCD_imag( Y, X, sz )         VD_CtoIm( Y, X, sz )
#define     VCD_arg( Y, X, sz )          VD_CtoArg( Y, X, sz )
#define     VCD_norm( Y, X, sz )         VD_CtoNorm( Y, X, sz )
#define     VCD_polar( Y, Mag, Arg, sz ) VD_PolartoC( Y, Mag, Arg, sz )
#define     VCD_complex( Y, Re, Im, sz ) VD_ReImtoC( Y, Re, Im, sz )


/****************  Data-type interconversions  ***************************/

void  __vf   V_CFtoCD( cdVector Y, cfVector X, ui size );
void  __vf   V_CDtoCF( cfVector Y, cdVector X, ui size );
#if (defined __BORLANDC__) && !(defined _WIN64)   /* 80-bit IEEE numbers supported */
    void  __vf   V_CDtoCE( ceVector Y, cdVector X, ui size );
    void  __vf   V_CEtoCD( cdVector Y, ceVector X, ui size );
#else  /* no IEEE number support with other compilers */
    #define V_CDtoCE VCD_equV
    #define V_CEtoCD VCD_equV
#endif


/****************  Index-oriented manipulations ***********************/

void  __vf  VCD_reflect( cdVector X, ui size );
void  __vf  VCD_delete( cdVector X, ui size, ui pos );
void  __vf  VCD_insert( cdVector X, ui size, ui pos, dComplex C );
void  __vf  VCD_rev( cdVector Y, cdVector X, ui size );
void  __vf  VCD_rotate( cdVector Y, cdVector X, ui size, ssize_t pos );
void  __vf  VCD_rotate_buf( cdVector Y, cdVector X, ui size, ssize_t pos, cdVector Buf );

void  __vf  VCD_indpick( cdVector Y, uiVector Ind, ui sizey, cdVector X );
void  __vf  VCD_indput(  cdVector Y, cdVector X, uiVector Ind, ui sizex );
void  __vf  VCD_subvector( cdVector Y, ui sizey, cdVector X, ssize_t samp );


/***************** Functions of a sub-set of elements  ********************/

void  __vf  VCD_subvector_equC(  cdVector Y, ui subsiz, ui samp,
                                 dComplex C );
void  __vf  VCD_subvector_equV(  cdVector Y, ui subsiz, ui samp,
                                 cdVector X );
    /*   for arithmetic functions of subsets, see <VCDmath.h>  */


/**************** One-Dimensional Vector Operations ***********************/

double    __vf  VCD_absmax(  cdVector X, ui size );
double    __vf  VCD_absmin(  cdVector X, ui size );
double    __vf  VCD_absmaxind( ui _VFAR *pos, cdVector X, ui size );
double    __vf  VCD_absminind( ui _VFAR *pos, cdVector X, ui size );
#if defined __cplusplus && defined _CMATH_CLASSDEFS
} // the following functions cannot be extern "C", if dComplex is a class
#endif
dComplex  __vf  VCD_maxReIm(     cdVector X, ui size );
dComplex  __vf  VCD_minReIm(     cdVector X, ui size );
dComplex  __vf  VCD_absmaxReIm(  cdVector X, ui size );
dComplex  __vf  VCD_absminReIm(  cdVector X, ui size );
dComplex  __vf  VCD_cabsmax(  cdVector X, ui size );
dComplex  __vf  VCD_cabsmin(  cdVector X, ui size );
dComplex  __vf  VCD_sabsmax(  cdVector X, ui size );
dComplex  __vf  VCD_sabsmin(  cdVector X, ui size );
dComplex  __vf  VCD_sum(     cdVector X, ui size );
dComplex  __vf  VCD_prod(    cdVector X, ui size );
dComplex  __vf  VCD_mean(   cdVector X, ui size );
dComplex  __vf  VCD_meanwW( cdVector X, dVector Wt, ui size );
dComplex  __vf  VCD_scalprod( cdVector X, cdVector Y, ui size );
#if defined __cplusplus && defined _CMATH_CLASSDEFS
extern "C" {
#endif
void      __vf  VCD_runsum(  cdVector Y, cdVector X, ui size );
void      __vf  VCD_runprod( cdVector Y, cdVector X, ui size );
int       __vf  VCD_iselementC( cdVector Tab, ui size, dComplex C );
ui        __vf  VCD_iselementV( cdVector Y, cdVector X, ui sizex,
                                cdVector Tab, ui sizetab );


/*********  Fourier Transforms, Convolutions, Filtering  ****************/

void  __vf   VCDl_FFT( cdVector Y, cdVector X, ui size, int dir );
void  __vf   VCDl_filter( cdVector Y, cdVector X, cdVector Flt, ui size );

void  __vf   VCDs_FFT( cdVector Y, cdVector X, ui size, int dir );
void  __vf   VCDs_filter( cdVector Y, cdVector X, cdVector Flt, ui size );

#if defined(__FLAT__) || defined(_WIN32)
   void  __vf   VCDp_FFT( cdVector Y, cdVector X, ui size, int dir );
   void  __vf   VCDp_filter( cdVector Y, cdVector X, cdVector Flt, ui size );
   void  __vf   VCDb_FFT( cdVector Y, cdVector X, ui size, int dir, cdVector Buf );
   #define VCD_FFT       VCDp_FFT
   #define VCD_filter    VCDp_filter
#elif defined(__LARGE__) || defined(__COMPACT__)
   #define VCD_FFT       VCDl_FFT
   #define VCD_filter    VCDl_filter
   #define VCDp_FFT      VCDl_FFT
   #define VCDp_filter   VCDl_filter
#else
   #define VCD_FFT       VCDs_FFT
   #define VCD_filter    VCDs_filter
   #define VCDp_FFT      VCDs_FFT
   #define VCDp_filter   VCDs_filter
#endif


/***************************  Input and Output *****************************/

void  __vf  VCD_fprint( FILE _VFAR *stream, cdVector X, ui size,
                                 unsigned nperline, unsigned linewidth );
void  __vf  VCD_cprint( cdVector X, ui size, unsigned nperline );
#define     VCD_print( X, sz, npl ) VCD_fprint( stdout, X, sz, npl, 80 )
  /*  VCD_print, VCD_cprint usable only for console applications! */
void  __vf  VCD_write( FILE _VFAR *stream, cdVector X, ui size );
void  __vf  VCD_nwrite( FILE _VFAR *stream, unsigned n, ui size, ... );
void  __vf  VCD_setWriteFormat( char _VFAR *FormatString );
                                            /* for VCD_write and VCD_nwrite */
void  __vf  VCD_setWriteSeparate( char _VFAR *SepString ); /* for VCD_write */
void  __vf  VCD_setNWriteSeparate( char _VFAR *SepString ); /* for VCD_nwrite */
#if !((defined __BORLANDC__) && (__BORLANDC__ < 0x710))
		/* modern compiler versions:  */
	void  __vf    VCD_read( cdVector X, ui size, FILE _VFAR *stream );
	void  __vf    VCD_nread( unsigned n, ui size, FILE _VFAR *stream, ... );
#else /* older Borland compiler versions need separate implementation */
	void  __vf    VCD_read1( cdVector X, ui size, FILE _VFAR *stream );
	void  __vf    VCD_nread1( unsigned n, ui size, FILE _VFAR *stream, ... );
	#define VCD_read  VCD_read1
	#define VCD_nread VCD_nread1
#endif
#ifdef V_HUGE
    void  __vf  VCD_store( FILE _VFAR *stream, cdVector X, ui size );
    void  __vf  VCD_recall( cdVector X, ui size, FILE _VFAR *stream  );
#else
    #ifdef __cplusplus
         void  inline VCD_store( FILE _VFAR *stream, cdVector X, ui size )
         {    fwrite( X, sizeof(dComplex), size, stream ); 
         }
         void  inline VCD_recall( cdVector X, ui size, FILE _VFAR *stream )
         {    fread(  X, sizeof(dComplex), size, stream );
         }
    #else
        #define VCD_store( str, X, sz )  \
                     fwrite( X, sizeof(dComplex), sz, str )
        #define VCD_recall( X, sz, str ) \
                     fread(  X, sizeof(dComplex), sz, str )
    #endif
#endif      /* VCD_store, VCD_recall in binary format */


#ifdef __cplusplus
}  // end of extern "C"
#endif


#endif /*  __VCDSTD_H */
