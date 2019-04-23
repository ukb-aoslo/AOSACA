/*  VPEstd.h

  vector management functions:
  manipulations on whole arrays or vectors of data type ePolar
  (extended-precision polar complex)

  Copyright (c) 1996-2017 by OptiCode - Dr. Martin Sander Software Dev.
  All Rights Reserved.
*/

#ifndef __VPESTD_H
#define __VPESTD_H
#if !defined( __VECLIB_H )
#include <VecLib.h>
#endif

#if (defined __BORLANDC__) && !(defined _WIN64)   /* 80-bit IEEE numbers supported.
                         The following  130 lines apply only to Borland C++ 32-bit  */

#ifdef __cplusplus
extern "C" {
#endif

/*************************  Generation  **************************/

peVector  __vf  VPE_vector( ui size );
peVector  __vf  VPE_vector0( ui size );
#if defined (_MSC_VER) && defined (_DEBUG)
    peVector  __vf  VPE_vector_dbg( ui size );
    peVector  __vf  VPE_vector0_dbg( ui size );
    #if defined (_INC_CRTDBG) && defined (_CRTDBG_MAP_ALLOC) 
	    /* Automatic mapping for memory-leak detection by CRT debugging switched on? */ 
        #define VPE_vector  VPE_vector_dbg
        #define VPE_vector0 VPE_vector0_dbg
    #endif
#else
    #define VPE_vector_dbg  VPE_vector
    #define VPE_vector0_dbg VPE_vector0
#endif

/***************  Addressing single vector elements ******************/

ePolar _VFAR * __vf VPE_Pelement( peVector X, ui n );
      /* returns a pointer to the n'th element of X. For the memory model
         HUGE, the pointer is normalized. */
#define VPE_element( X, n )  (*VPE_Pelement( X, n ))
void  __vf VPE_getElement( ePolar *y, peVector X, ui n );
void  __vf VPE_setElement( peVector X, ui n, ePolar C );

/*******************  Initialization **********************************/

void  __vf  VPE_equ0( peVector X, ui size );
void  __vf  VPE_equ1( peVector X, ui size );
void  __vf  VPE_equm1( peVector X, ui size );
void  __vf  VPE_equC( peVector X, ui size, ePolar C );
void  __vf  VPE_equV( peVector Y, peVector X, ui size );
void  __vf  VPE_principal( peVector Y, peVector X, ui size );

void  __vf  VE_PtoMagArg( eVector Mag, eVector Arg, peVector X, ui size );
void  __vf  VE_MagArgtoP( peVector Y, eVector Mag, eVector Arg, ui size );
void  __vf  VE_MagArgtoPrincipal( peVector Y,
                                  eVector Mag, eVector Arg, ui size );
void  __vf  VE_PtoMag( eVector Mag, peVector X, ui size );
void  __vf  VE_MagtoP( peVector Y, eVector Mag, ui size );
void  __vf  VE_PtoArg( eVector Arg, peVector X, ui size );
void  __vf  VE_ArgtoP( peVector Y, eVector Arg, ui size );
void  __vf  VE_CtoP( peVector YP, ceVector XC, ui size );
void  __vf  VE_PtoC( ceVector YC, peVector XP, ui size );
void  __vf  VE_PtoNorm( eVector Norm, peVector X, ui size );
void  __vf  VE_PtoReIm( eVector Re, eVector Im, peVector X, ui size );
void  __vf  VE_ReImtoP( peVector Y, eVector Re, eVector Im, ui size );
void  __vf  VE_PtoRe( eVector Re, peVector X, ui size );
void  __vf  VE_PtoIm( eVector Im, peVector X, ui size );
int   __vf  VPE_abs(  eVector Y, peVector X, ui size );

#define     VPE_real         VE_PtoRe
#define     VPE_imag         VE_PtoIm
#define     VPE_arg          VE_PtoArg
#define     VPE_norm         VE_PtoNorm

/****************  Data-type interconversions  ***************************/

void  __vf   V_PFtoPE( peVector Y, pfVector X, ui size );
void  __vf   V_PEtoPF( pfVector Y, peVector X, ui size );
void  __vf   V_PDtoPE( peVector Y, pdVector X, ui size );
void  __vf   V_PEtoPD( pdVector Y, peVector X, ui size );


/****************  Index-oriented manipulations ***********************/

void  __vf  VPE_reflect( peVector X, ui size );
void  __vf  VPE_delete( peVector X, ui size, ui pos );
void  __vf  VPE_insert( peVector X, ui size, ui pos, ePolar C );
void  __vf  VPE_rev( peVector Y, peVector X, ui size );
void  __vf  VPE_rotate( peVector Y, peVector X, ui size, ssize_t pos );
void  __vf  VPE_rotate_buf( peVector Y, peVector X, ui size, ssize_t pos, peVector Buf );

void  __vf  VPE_indpick( peVector Y, uiVector Ind, ui sizey, peVector X );
void  __vf  VPE_indput(  peVector Y, peVector X, uiVector Ind, ui sizex );
void  __vf  VPE_subvector( peVector Y, ui sizey, peVector X, ssize_t samp );


/***************** Functions of a sub-set of elements  ********************/

void  __vf  VPE_subvector_equC(  peVector Y, ui subsiz, ui samp,
                                 ePolar C );
void  __vf  VPE_subvector_equV(  peVector Y, ui subsiz, ui samp,
                                 peVector X );
    /*   for arithmetic functions of subsets, see <VPEmath.h>  */


/**************** One-Dimensional Vector Operations ***********************/

extended  __vf  VPE_absmax(  peVector X, ui size );
extended  __vf  VPE_absmin(  peVector X, ui size );
extended  __vf  VPE_absmaxind( ui _VFAR *pos, peVector X, ui size );
extended  __vf  VPE_absminind( ui _VFAR *pos, peVector X, ui size );
#if defined __cplusplus && defined _CMATH_CLASSDEFS
} // the following functions cannot be extern "C", if ePolar is a class
#endif
ePolar  __vf  VPE_prod(    peVector X, ui size );
#if defined __cplusplus && defined _CMATH_CLASSDEFS
extern "C" {
#endif
void      __vf  VPE_runprod( peVector Y, peVector X, ui size );
int       __vf  VPE_iselementC( peVector Tab, ui size, ePolar C );
ui        __vf  VPE_iselementV( peVector Y, peVector X, ui sizex,
                                peVector Tab, ui sizetab );

/***************************  Input and Output *****************************/

void  __vf  VPE_fprint( FILE _VFAR *stream, peVector X, ui size,
                                 unsigned nperline, unsigned linewidth );
void  __vf  VPE_cprint( peVector X, ui size, unsigned nperline );
#define     VPE_print( X, sz, npl ) VPE_fprint( stdout, X, sz, npl, 80 )\
  /*  VPE_print, VPE_cprint usable only for console applications! */
void  __vf  VPE_write( FILE _VFAR *stream, peVector X, ui size );
void  __vf  VPE_nwrite( FILE _VFAR *stream, unsigned n, ui size, ... );
void  __vf  VPE_setWriteFormat( char _VFAR *FormatString );
                                 /* for VPE_write and VPE_nwrite */
void  __vf  VPE_setWriteSeparate( char _VFAR *SepString ); /* for VPE_write */
void  __vf  VPE_setNWriteSeparate( char _VFAR *SepString ); /* for VPE_nwrite */
#if !((defined __BORLANDC__) && (__BORLANDC__ < 0x710))
		/* modern compiler versions:  */
	void  __vf    VPE_read( peVector X, ui size, FILE _VFAR *stream );
	void  __vf    VPE_nread( unsigned n, ui size, FILE _VFAR *stream, ... );
#else /* older Borland compiler versions need separate implementation */
	void  __vf    VPE_read1( peVector X, ui size, FILE _VFAR *stream );
	void  __vf    VPE_nread1( unsigned n, ui size, FILE _VFAR *stream, ... );
	#define VPE_read  VPE_read1
	#define VPE_nread VPE_nread1
#endif
#ifdef V_HUGE
    void  __vf  VPE_store( FILE _VFAR *stream, peVector X, ui size );
    void  __vf  VPE_recall( peVector X, ui size, FILE _VFAR *stream  );
#else
    #ifdef __cplusplus
         void  inline VPE_store( FILE _VFAR *stream, peVector X, ui size )
         {    fwrite( X, sizeof(ePolar), size, stream );
         }
         void  inline VPE_recall( peVector X, ui size, FILE _VFAR *stream )
         {    fread(  X, sizeof(ePolar), size, stream );
         }
    #else
        #define VPE_store( str, X, sz )  \
                     fwrite( X, sizeof(ePolar), sz, str )
        #define VPE_recall( X, sz, str ) \
                     fread(  X, sizeof(ePolar), sz, str )
    #endif
#endif      /* VPE_store, VPE_recall in binary format */

#ifdef __cplusplus
}    /* end of extern "C"  */
#endif

#else   /* the following 130 lines apply only to compilers without
           support for 80-bit IEEE numbers.  */
#include <VPDstd.h>
#define VPE_vector      VPD_vector
#define VPE_vector0     VPD_vector0
#define VPE_vector_dbg  VPD_vector
#define VPE_vector0_dbg VPD_vector0_dbg
#define VPE_Pelement    VPD_Pelement
#define VPE_element( X, n )  (*VPE_Pelement( X, n ))
#define VPE_setElement  VPD_setElement

#define VPE_equ0        VPD_equ0
#define VPE_equ1        VPD_equ1
#define VPE_equm1       VPD_equm1
#define VPE_equC        VPD_equC
#define VPE_equV        VPD_equV
#define VPE_principal   VPD_principal
#define VE_MagArgtoPrincipal VD_MagArgtoPrincipal
#define VE_PtoMagArg    VD_PtoMagArg
#define VE_MagArgtoP    VD_MagArgtoP
#define VE_PtoMag       VD_PtoMag
#define VE_MagtoP       VD_MagtoP
#define VE_PtoArg       VD_PtoArg
#define VE_ArgtoP       VD_ArgtoP
#define VE_PtoC         VD_PtoC
#define VE_CtoP         VD_CtoP
#define VE_PtoNorm      VD_PtoNorm
#define VE_PtoReIm      VD_PtoReIm
#define VE_ReImtoP      VD_ReImtoP
#define VE_PtoRe        VD_PtoRe
#define VE_PtoIm        VD_PtoIm
#define VPE_abs         VPD_abs

#define VPE_real        VE_PtoRe
#define VPE_imag        VE_PtoIm
#define VPE_arg         VE_PtoArg
#define VPE_norm        VE_PtoNorm

#define V_PFtoPE        V_PFtoPD
#define V_PEtoPF        V_PDtoPF
#define V_PDtoPE        VPD_equV
#define V_PEtoPD        VPD_equV

#define VPE_reflect     VPD_reflect
#define VPE_delete      VPD_delete
#define VPE_insert      VPD_insert
#define VPE_rev         VPD_rev
#define VPE_rotate      VPD_rotate
#define VPE_rotate_buf  VPD_rotate_buf
#define VPE_indpick     VPD_indpick
#define VPE_indput      VPD_indput
#define VPE_subvector   VPD_subvector
#define VPE_subvector_equC  VPD_subvector_equC
#define VPE_subvector_equV  VPD_subvector_equV

#define VPE_absmax      VPD_absmax
#define VPE_absmin      VPD_absmin
#define VPE_absmaxind   VPD_absmaxind
#define VPE_absminind   VPD_absminind
#define VPE_prod        VPD_prod
#define VPE_runprod     VPD_runprod
#define VPE_iselementC  VPD_iselementC
#define VPE_iselementV  VPD_iselementV

#define VPE_fprint      VPD_fprint
#define VPE_cprint      VPD_cprint
#define VPE_print       VPD_print
#define VPE_write       VPD_write
#define VPE_read        VPD_read
#define VPE_nwrite      VPD_nwrite
#define VPE_nread       VPD_nread
#define VPE_setWriteFormat      VPD_setWriteFormat
#define VPE_setWriteSeparate    VPD_setWriteSeparate
#define VPE_setNWriteSeparate   VPD_setNWriteSeparate
#define VPE_store       VPD_store
#define VPE_recall      VPD_recall

#endif   /* IEEE number support */

#endif /*  __VPESTD_H */
