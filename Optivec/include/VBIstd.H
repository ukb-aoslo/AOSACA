/*  VBIstd.h

  vector management functions for byte-size integers.

  Copyright (c) 1996-2017 by OptiCode - Dr. Martin Sander Software Dev.
  All Rights Reserved.
*/

#ifndef __VBISTD_H
#define __VBISTD_H

#if !defined( __VECLIB_H )
   #include <VecLib.h>
#endif

#ifdef __cplusplus
   extern "C" {
#endif

/*************************  Generation ***************************/

biVector  __vf  VBI_vector( ui size );
biVector  __vf  VBI_vector0( ui size );
#if defined (_MSC_VER) && defined (_DEBUG)
    biVector  __vf  VBI_vector_dbg( ui size );
    biVector  __vf  VBI_vector0_dbg( ui size );
    #if defined (_INC_CRTDBG) && defined (_CRTDBG_MAP_ALLOC) 
	    /* Automatic mapping for memory-leak detection by CRT debugging switched on? */ 
        #define VBI_vector  VBI_vector_dbg
        #define VBI_vector0 VBI_vector0_dbg
    #endif
#else
    #define VBI_vector_dbg  VBI_vector
    #define VBI_vector0_dbg VBI_vector0
#endif


/***************  Addressing single vector elements ******************/

char _VFAR * __vf VBI_Pelement( biVector X, ui n );
      /* returns a pointer to the n'th element of X. For the memory model
         HUGE, the pointer is normalized. */
#define VBI_element( X, n )  (*VBI_Pelement( X, n ))
void __vf VBI_getElement( char *y, biVector X, ui n );
void __vf VBI_setElement( biVector X, ui n, char C );

/****************** Initialization  ******************************/

void  __vf  VBI_equ0( biVector X, ui size );
void  __vf  VBI_equC( biVector X, ui size, char C );
void  __vf  VBI_equV( biVector Y, biVector X, ui size );
void  __vf  VBI_ramp( biVector X, ui size, char Start, char Rise );

/******  Linear Congruential random generator with Bays-Durham shuffle:  ***********
  seed!=0 --> initialization of state. seed==0 --> continue series from previous call with the same state. */
void  __vf  VBI_randomLC( biVector X, ui size, long seed, char MinVal, char MaxVal, V_RANDOMLCSTATE *state );
/**  simplified version: returns new seed. Series not continuous across calls due to new state initialization: */
long  __vf  VBI_random( biVector X, ui size, long seed, char MinVal, char MaxVal );


/************** Data-type interconversions  ****************************/

void  __vf  V_BItoUB( ubVector Y, biVector X, ui size ); /* signed-unsigned */
void  __vf  V_UBtoBI( biVector Y, ubVector X, ui size );

void  __vf  V_BItoI(  iVector  Y, biVector X, ui size );  /* up-conversion */
void  __vf  V_BItoSI( siVector Y, biVector X, ui size );
void  __vf  V_BItoLI( liVector Y, biVector X, ui size );
void  __vf  V_BItoQI( qiVector Y, biVector X, ui size );

void  __vf   V_SItoBI( biVector Y, siVector  X, ui size );/* down-conversion */
void  __vf   V_ItoBI(  biVector Y, iVector  X, ui size );
void  __vf   V_LItoBI( biVector Y, liVector X, ui size );
void  __vf   V_QItoBI( biVector Y, qiVector X, ui size );

void  __vf   V_BItoF(  fVector Y, biVector X, ui size );
void  __vf   V_BItoD(  dVector Y, biVector X, ui size );
#if (defined __BORLANDC__) && !(defined _WIN64)
    void  __vf   V_BItoE(  eVector Y, biVector X, ui size );
#else  /* no 80-bit IEEE reals with Visual C++ and Optima++ */
    #define V_BItoE V_BItoD
#endif

/************** Index-oriented manipulations ***************************/

void  __vf  VBI_reflect( biVector X, ui size );
void  __vf  VBI_rev( biVector Y, biVector X, ui size );
void  __vf  VBI_rotate( biVector Y, biVector X, ui size, ssize_t pos );
void  __vf  VBI_rotate_buf( biVector Y, biVector X, ui size, ssize_t pos, biVector Buf );

void  __vf  VBI_delete( biVector X, ui size, ui pos );
void  __vf  VBI_insert( biVector X, ui size, ui pos, char C );

void  __vf  VBI_sort( biVector Y, biVector X, ui size, int dir );
void  __vf  VBI_sortind( uiVector Ind, biVector X, ui size, int dir );

void  __vf  VBI_subvector( biVector Y, ui sizey, biVector X, ssize_t samp );
void  __vf  VBI_subvector_equC( biVector Y, ui subsz, ui samp, char C );
void  __vf  VBI_subvector_equV( biVector Y, ui subsz, ui samp,
                                biVector X );

void  __vf  VBI_indpick( biVector Y, uiVector Ind, ui sizey, biVector X );
void  __vf  VBI_indput(  biVector Y, biVector X, uiVector Ind, ui sizex );

ui    __vf  VBI_searchC( biVector XTab, ui size, char C, int mode );
void  __vf  VBI_searchV( uiVector Ind, biVector X, ui sizex,
                         biVector Tab, ui sizetab, int mode );

/********************   One-dimensional Vector Operations  ********/

char  __vf  VBI_sum( biVector X, ui size );
void  __vf  VBI_runsum( biVector Y, biVector X, ui size );
char  __vf  VBI_max( biVector X, ui size );
char  __vf  VBI_min( biVector X, ui size );
char  __vf  VBI_maxind( ui _VFAR *Ind, biVector X, ui size );
char  __vf  VBI_minind( ui _VFAR *Ind, biVector X, ui size );
void   __vf  VBI_runmax( biVector Y, biVector X, ui size );
void   __vf  VBI_runmin( biVector Y, biVector X, ui size );
double __vf  VBI_fsum( biVector X, ui size );
double __vf  VBI_mean( biVector X, ui size );

int    __vf  VBI_iselementC( biVector Tab, ui size, char C );
ui     __vf  VBI_iselementV( biVector Y, biVector X, ui sizex,
                             biVector Tab, ui sizetab );
ui     __vf  VBI_distribution( uiVector Abund, biVector Limits, ui nbins,
                               biVector X, ui sizex, int mode );


/************************ Input / Output ******************************/

void  __vf   V_ifprint(  FILE _VFAR *stream, void _VFAR *X, ui size,
                  unsigned nperline, unsigned linewidth, unsigned vers );
#define VBI_fprint( st, x, sz, npl, lw ) \
             V_ifprint(  st, (void _VFAR *)(x), sz, npl, lw, 0 )

void __vf  V_icprint(  void _VFAR *X, ui size, unsigned nperline, unsigned vers );
#define VBI_cprint( x, sz, npl ) V_icprint( (void _VFAR *) (x), sz, npl, 0 )
#define VBI_print(  x, sz, npl ) \
             V_ifprint(  stdout, (void _VFAR *)(x), sz, npl, 80, 0 )

void  __vf   V_setRadix( int radix );
           /* radix to be assumed by all whole-number read functions V??_read */
void  __vf   VBI_read( biVector X, ui size, FILE _VFAR *stream );
void  __vf   VBI_write( FILE _VFAR *stream, biVector X, ui size );
void  __vf   VBI_nread( unsigned n, ui size, FILE _VFAR *stream, ... );
void  __vf   VBI_nwrite( FILE _VFAR *stream, unsigned n, ui size, ... );
void  __vf   VBI_setWriteFormat( char _VFAR *FormatString );
        /* for VBI_write and VBI_nwrite. The format must be a format for short int ! */
void  __vf   VBI_setWriteSeparate( char _VFAR *SepString ); /* for VBI_write */
void  __vf   VBI_setNWriteSeparate( char _VFAR *SepString ); /* for VBI_nwrite */
#ifdef V_HUGE
    void  __vf   VBI_store(  FILE _VFAR *stream, biVector X, ui size );
    void  __vf   VBI_recall( biVector X, ui size, FILE _VFAR *stream );
#else
    #ifdef __cplusplus
         void  inline VBI_store( FILE _VFAR *stream, biVector X, ui size )
         {    fwrite( X, sizeof(char), size, stream );
         }
         void  inline VBI_recall( biVector X, ui size, FILE _VFAR *stream )
         {    fread(  X, sizeof(char), size, stream );
         }
    #else
        #define VBI_store( str, X, sz )  \
                     fwrite( X, sizeof(char), sz, str )
        #define VBI_recall( X, sz, str ) \
                     fread(  X, sizeof(char), sz, str )
    #endif
#endif      /* VBI_store, VBI_recall in binary format */

#ifdef __cplusplus
}  // end of extern "C"
#endif

#endif   /*  __VBISTD_H    */
