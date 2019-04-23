/*  VUQstd.h

  vector management functions for data type "uquad".

  Copyright (c) 1996-2017 by OptiCode - Dr. Martin Sander Software Dev.
  All Rights Reserved.
*/

#if defined _WIN64
#ifndef __VUQSTD_H
#define __VUQSTD_H

#if !defined( __VECLIB_H )
   #include <VecLib.h>
#endif

#ifdef __cplusplus
    extern "C" {
#endif

/*****************************  Generation ******************************/

uqVector  __vf  VUQ_vector( ui size );
uqVector  __vf  VUQ_vector0( ui size );
#if defined (_MSC_VER) && defined (_DEBUG)
    uqVector  __vf  VUQ_vector_dbg( ui size );
    uqVector  __vf  VUQ_vector0_dbg( ui size );
    #if defined (_INC_CRTDBG) && defined (_CRTDBG_MAP_ALLOC) 
	    /* Automatic mapping for memory-leak detection by CRT debugging switched on? */ 
        #define VUQ_vector  VUQ_vector_dbg
        #define VUQ_vector0 VUQ_vector0_dbg
    #endif
#else
    #define VUQ_vector_dbg  VUQ_vector
    #define VUQ_vector0_dbg VUQ_vector0
#endif

/***************  Addressing single vector elements ******************/

uquad _VFAR * __vf VUQ_Pelement( uqVector X, ui n );
      /* returns a pointer to the n'th element of X. For the memory model
         HUGE, the pointer is normalized. */
#define VUQ_element( X, n ) (*VUQ_Pelement( X, n ))
void  __vf VUQ_getElement( uquad *y, uqVector X, ui n );
void  __vf VUQ_setElement( uqVector X, ui n, uquad C );

/****************** Initialization  ******************************/

void  __vf  VUQ_equ0( uqVector X, ui size );
void  __vf  VUQ_equC( uqVector X, ui size, uquad C );
void  __vf  VUQ_equV( uqVector Y, uqVector X, ui size );
void  __vf  VUQ_ramp( uqVector X, ui size, uquad Start, quad Rise );

/******  Linear Congruential random generator with Bays-Durham shuffle:  ***********
  seed!=0 --> initialization of state. seed==0 --> continue series from previous call with the same state. */
void  __vf  VUQ_randomLC( uqVector X, ui size, long seed, uquad MinVal, uquad MaxVal, V_RANDOMLCSTATE *state );
/**  simplified version: returns new seed. Series not continuous across calls due to new state initialization: */
long  __vf  VUQ_random( uqVector X, ui size, long seed, uquad MinVal, uquad MaxVal );

/**************  Data-type interconversions  **************************/

void __vf  V_QItoUQ( uqVector Y, qiVector X, ui size );  /* signed-unsigned */
void __vf  V_UQtoQI( qiVector Y, uqVector X, ui size );

void __vf  V_UBtoUQ( uqVector Y, ubVector X, ui size );  /* up-conversion */
void __vf  V_UStoUQ( uqVector Y, usVector X, ui size );
void __vf  V_UtoUQ(  uqVector Y, uVector  X, ui size );
void __vf  V_ULtoUQ( uqVector Y, ulVector X, ui size );

void __vf  V_UQtoUB( ubVector Y, uqVector X, ui size ); /* down-conversion */
void __vf  V_UQtoUS( usVector Y, uqVector X, ui size );
void __vf  V_UQtoU(  uVector  Y, uqVector X, ui size );
void __vf  V_UQtoUL( ulVector Y, uqVector X, ui size );

void  __vf   V_UQtoF(  fVector Y, uqVector X, ui size );
void  __vf   V_UQtoD(  dVector Y, uqVector X, ui size );
#if (defined __BORLANDC__) && !(defined _WIN64)
    void  __vf   V_UQtoE(  eVector Y, uqVector X, ui size );
#else  /* no 80-bit IEEE reals with Visual C++ */
    #define V_UQtoE V_UQtoD
#endif


/************** Index-oriented manipulations ***************************/

void  __vf  VUQ_reflect( uqVector X, ui size );
void  __vf  VUQ_rev( uqVector Y, uqVector X, ui size );
void  __vf  VUQ_rotate( uqVector Y, uqVector X, ui size, ssize_t pos );
void  __vf  VUQ_rotate_buf( uqVector Y, uqVector X, ui size, ssize_t pos, uqVector Buf );

void  __vf  VUQ_delete( uqVector X, ui size, ui pos );
void  __vf  VUQ_insert( uqVector X, ui size, ui pos, uquad C );

void  __vf  VUQ_sort( uqVector Y, uqVector X, ui size, int dir );
void  __vf  VUQ_sortind( uiVector Ind, uqVector X, ui size, int dir );

void  __vf  VUQ_subvector( uqVector Y, ui sizey, uqVector X, ssize_t samp );
void  __vf  VUQ_subvector_equC( uqVector Y, ui subsz, ui samp, uquad C );
void  __vf  VUQ_subvector_equV( uqVector Y, ui subsz, ui samp, uqVector X );

void  __vf  VUQ_indpick( uqVector Y, uiVector Ind, ui sizey, uqVector X );
void  __vf  VUQ_indput(  uqVector Y, uqVector X, uiVector Ind, ui sizex );

ui    __vf  VUQ_searchC( uqVector XTab, ui size, uquad C, int mode );
void  __vf  VUQ_searchV( uiVector Ind, uqVector X, ui sizex,
                         uqVector Tab, ui sizetab, int mode );

/********************   One-dimensional Vector Operations  ********/

uquad  __vf  VUQ_sum( uqVector X, ui size );
void   __vf  VUQ_runsum( uqVector Y, uqVector X, ui size );
uquad  __vf  VUQ_max( uqVector X, ui size );
uquad  __vf  VUQ_min( uqVector X, ui size );
uquad  __vf  VUQ_maxind( ui _VFAR *Ind, uqVector X, ui size );
uquad  __vf  VUQ_minind( ui _VFAR *Ind, uqVector X, ui size );
extended __vf  VUQ_fsum( uqVector X, ui size );
extended __vf  VUQ_mean( uqVector X, ui size );
void   __vf  VUQ_runmax( uqVector Y, uqVector X, ui size );
void   __vf  VUQ_runmin( uqVector Y, uqVector X, ui size );

int    __vf  VUQ_iselementC( uqVector Tab, ui size, uquad  C );
ui     __vf  VUQ_iselementV( uqVector Y, uqVector X, ui sizex,
                             uqVector Tab, ui sizetab );
ui     __vf  VUQ_distribution( uiVector Abund, uqVector Limits, ui nbins,
                               uqVector X, ui sizex, int mode );


/************************ Input / Output ******************************/

void  __vf   V_ifprint(  FILE _VFAR *stream, void _VFAR *X, ui size,
                  unsigned nperline, unsigned linewidth, unsigned vers );
#define VUQ_fprint( st, x, sz, npl, lw ) \
	         V_ifprint(  st, (void _VFAR *)(x), sz, npl, lw, 9 )
#define VUQ_cprint( x, sz, npl ) \
	         V_icprint( (void _VFAR *)(x), sz, npl, 9 )
#define VUQ_print( x, sz, npl ) VUQ_fprint( stdout, x, sz, npl, 80 )

/* note that V_setRadix does not act on VUQ_read. Here, the radix is always 10 */
void  __vf   VUQ_read( uqVector X, ui size, FILE _VFAR *stream );
void  __vf   VUQ_write( FILE _VFAR *stream, uqVector X, ui size );
void  __vf   VUQ_nread( unsigned n, ui size, FILE _VFAR *stream, ... );
void  __vf   VUQ_nwrite( FILE _VFAR *stream, unsigned n, ui size, ... );
void  __vf   VUQ_setWriteFormat( char _VFAR *FormatString );
void  __vf   VUQ_setWriteSeparate( char _VFAR *SepString ); /* for VUQ_write */
void  __vf   VUQ_setNWriteSeparate( char _VFAR *SepString ); /* for VUQ_nwrite */
#ifdef __cplusplus
         void  inline VUQ_store( FILE _VFAR *stream, uqVector X, ui size )
         {    fwrite( X, sizeof(uquad), size, stream ); 
         }
         void  inline VUQ_recall( uqVector X, ui size, FILE _VFAR *stream )
         {    fread(  X, sizeof(uquad), size, stream );
         }
#else
        #define VUQ_store( str, X, sz )  \
                     fwrite( X, sizeof(uquad), sz, str )
        #define VUQ_recall( X, sz, str ) \
                     fread(  X, sizeof(uquad), sz, str )
#endif    /* VUQ_store, VUQ_recall in binary format */

#ifdef __cplusplus
}  // end of extern "C"
#endif

#endif   /*  __VUQSTD_H    */
#endif   /*  _WIN64 */