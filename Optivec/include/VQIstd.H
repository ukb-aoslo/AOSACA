/*  VQIstd.h

  vector management functions for data type "quad".

  Copyright (c) 1996-2017 by OptiCode - Dr. Martin Sander Software Dev.
  All Rights Reserved.
*/

#ifndef __VQISTD_H
#define __VQISTD_H

#if !defined( __VECLIB_H )
   #include <VecLib.h>
#endif

#ifdef __cplusplus
   extern "C" {
#endif

/************  Making the data type quad available   *********************
 *        The following definitions are necessary only for               *
 *        older versions of Borland C++ which did not directly           *
 *        support 64 bit integers.                                       */
#if (defined __BORLANDC__) && (__BORLANDC__ < 0x570)  
	   /* quad = struct{Lo, Hi} --> need interface functions */
    quad        __vf  setquad( long double x );
    double      __vf  quadtod( quad x );
    long double __vf  _quadtold( quad x );
#else /* direct conversions */
    #define setquad(x) ((quad)(x))
    #define quadtod(x) ((double)(x))
    #define _quadtold(x) ((long double)(x))
#endif

/************************  Generation ******************************/

qiVector  __vf  VQI_vector( ui size );
qiVector  __vf  VQI_vector0( ui size );
#if defined (_MSC_VER) && defined (_DEBUG)
    qiVector  __vf  VQI_vector_dbg( ui size );
    qiVector  __vf  VQI_vector0_dbg( ui size );
    #if defined (_INC_CRTDBG) && defined (_CRTDBG_MAP_ALLOC) 
	    /* Automatic mapping for memory-leak detection by CRT debugging switched on? */ 
        #define VQI_vector  VQI_vector_dbg
        #define VQI_vector0 VQI_vector0_dbg
    #endif
#else
    #define VQI_vector_dbg  VQI_vector
    #define VQI_vector0_dbg VQI_vector0
#endif

/***************  Addressing single vector elements ******************/

quad _VFAR * __vf VQI_Pelement( qiVector X, ui n );
      /* returns a pointer to the n'th element of X. For the memory model
         HUGE, the pointer is normalized. */
#define VQI_element( X, n ) (*VQI_Pelement( X, n ))
void  __vf VQI_getElement( quad *y, qiVector X, ui n );
void  __vf VQI_setElement( qiVector X, ui n, quad C );

/****************** Initialization  ******************************/

void  __vf  VQI_equ0( qiVector X, ui size );
void  __vf  VQI_equC( qiVector X, ui size, quad C );
void  __vf  VQI_equV( qiVector Y, qiVector X, ui size );
void  __vf  VQI_ramp( qiVector X, ui size, quad Start, quad Rise );

/******  Linear Congruential random generator with Bays-Durham shuffle:  ***********
  seed!=0 --> initialization of state. seed==0 --> continue series from previous call with the same state. */
void  __vf  VQI_randomLC( qiVector X, ui size, long seed, quad MinVal, quad MaxVal, V_RANDOMLCSTATE *state );
/*  simplified version: returns new seed. Series not continuous across calls due to new state initialization: */
long  __vf  VQI_random( qiVector X, ui size, long seed, quad MinVal, quad MaxVal );


/************** Data-type interconversions  ***************************/

#if defined _WIN64  /* signed - unsigned conversion available only for Win64 */
    void __vf  V_UQtoQI( qiVector Y, uqVector  X, ui size );
    void __vf  V_QItoUQ( uqVector Y, qiVector X, ui size );
#endif

void  __vf  V_BItoQI( qiVector Y, biVector X, ui size );  /* up-conversion */
void  __vf  V_SItoQI( qiVector Y, siVector X, ui size );
void  __vf  V_ItoQI(  qiVector Y, iVector  X, ui size );
void  __vf  V_LItoQI( qiVector Y, liVector X, ui size );

void  __vf  V_QItoBI(  biVector Y, qiVector X, ui size ); /* down-conversion */
#if (!defined _WIN64)
	void  __vf  Vo_QItoSI( siVector Y, qiVector X, ui size );
	void  __vf  Vo_QItoI(  iVector  Y, qiVector X, ui size );
	void  __vf  Vo_QItoLI( liVector Y, qiVector X, ui size );
#endif
#if defined (V_trapIntError) && (!defined _WIN64)
    #define V_QItoSI   Vo_QItoSI
    #define V_QItoI    Vo_QItoI
    #define V_QItoLI   Vo_QItoLI
#else
    void  __vf   V_QItoSI( siVector Y, qiVector X, ui size );
    void  __vf   V_QItoI(  iVector  Y, qiVector X, ui size );
    void  __vf   V_QItoLI( liVector Y, qiVector X, ui size );
#endif

void  __vf   V_QItoF(  fVector Y, qiVector X, ui size );
void  __vf   V_QItoD(  dVector Y, qiVector X, ui size );
#if (defined __BORLANDC__) && !(defined _WIN64)
    void  __vf   V_QItoE(  eVector Y, qiVector X, ui size );
#else  /* no 80-bit IEEE reals with Visual C++ */
    #define V_QItoE V_QItoD
#endif



/************** Index-oriented manipqiations ***************************/

void  __vf  VQI_reflect( qiVector X, ui size );
void  __vf  VQI_rev( qiVector Y, qiVector X, ui size );
void  __vf  VQI_rotate( qiVector Y, qiVector X, ui size, ssize_t pos );
void  __vf  VQI_rotate_buf( qiVector Y, qiVector X, ui size, ssize_t pos, qiVector Buf );

void  __vf  VQI_delete( qiVector X, ui size, ui pos );
void  __vf  VQI_insert( qiVector X, ui size, ui pos, quad C );

void  __vf  VQI_sort( qiVector Y, qiVector X, ui size, int dir );
void  __vf  VQI_sortind( uiVector Ind, qiVector X, ui size, int dir );

void  __vf  VQI_subvector( qiVector Y, ui sizey, qiVector X, ssize_t samp );
void  __vf  VQI_subvector_equC( qiVector Y, ui subsz, ui samp, quad C );
void  __vf  VQI_subvector_equV( qiVector Y, ui subsz, ui samp,
                                qiVector X );

void  __vf  VQI_indpick( qiVector Y, uiVector Ind, ui sizey, qiVector X );
void  __vf  VQI_indput(  qiVector Y, qiVector X, uiVector Ind, ui sizex );

ui    __vf  VQI_searchC( qiVector XTab, ui size, quad C, int mode );
void  __vf  VQI_searchV( uiVector Ind, qiVector X, ui sizex,
                         qiVector Tab, ui sizetab, int mode );

/********************   One-dimensional Vector Operations  ********/

#if !((defined __BORLANDC__) && (__BORLANDC__ < 0x570))
	quad   __vf  VQI_sum( qiVector X, ui size );
	quad   __vf  VQI_max( qiVector X, ui size );
	quad   __vf  VQI_min( qiVector X, ui size );
	quad   __vf  VQI_maxind( ui _VFAR *Ind, qiVector X, ui size );
	quad   __vf  VQI_minind( ui _VFAR *Ind, qiVector X, ui size );
#else  /* old BC versions need separate implementation */
	quad   __vf  VQI_sum1( qiVector X, ui size );
	quad   __vf  VQI_max1( qiVector X, ui size );
	quad   __vf  VQI_min1( qiVector X, ui size );
	quad   __vf  VQI_maxind1( ui _VFAR *Ind, qiVector X, ui size );
	quad   __vf  VQI_minind1( ui _VFAR *Ind, qiVector X, ui size );
	#define VQI_sum		VQI_sum1
	#define VQI_max		VQI_max1
	#define VQI_min		VQI_min1
	#define VQI_maxind	VQI_maxind1
	#define VQI_minind	VQI_minind1
#endif
void   __vf  VQI_runsum( qiVector Y, qiVector X, ui size );
void   __vf  VQI_runmax( qiVector Y, qiVector X, ui size );
void   __vf  VQI_runmin( qiVector Y, qiVector X, ui size );
extended __vf  VQI_fsum( qiVector X, ui size );
extended __vf  VQI_mean( qiVector X, ui size );

int    __vf  VQI_iselementC( qiVector Tab, ui size, quad C );
ui     __vf  VQI_iselementV( qiVector Y, qiVector X, ui sizex,
                             qiVector Tab, ui sizetab );
ui     __vf  VQI_distribution( uiVector Abund, qiVector Limits, ui nbins,
                               qiVector X, ui sizex, int mode );


/************************ Input / Output ******************************/


void  __vf   VQI_setWriteFormat( char _VFAR *FormatString );
											/* for VQI_write and VQI_nwrite */

#if ((defined __BORLANDC__) && (__BORLANDC__ >= 0x570)) || ((defined _MSC_VER) && (_MSC_VER >= 1400))
		/* modern compiler versions:  */
	void  __vf   V_ifprint(  FILE _VFAR *stream, void _VFAR *X, ui size,
                  unsigned nperline, unsigned linewidth, unsigned vers );
	#define VQI_fprint( st, x, sz, npl, lw ) \
		         V_ifprint(  st, (void _VFAR *)(x), sz, npl, lw, 8 )
	#define VQI_cprint( x, sz, npl ) \
		         V_icprint( (void _VFAR *)(x), sz, npl, 8 )
	#define VQI_print( x, sz, npl ) VQI_fprint( stdout, x, sz, npl, 80 )

		/* note that V_setRadix does not act on VQI_read. Here, the radix is always 10 */
	void  __vf   VQI_write( FILE _VFAR *stream, qiVector X, ui size );
	void  __vf   VQI_nwrite( FILE _VFAR *stream, unsigned n, ui size, ... );
#else /* older compiler versions need separate implementation */
	void  __vf   VQI_fprint1(  FILE _VFAR *stream, qiVector X, ui size,
					unsigned nperline, unsigned linewidth );
	#define VQI_fprint VQI_fprint1
    void __vf  VQI_cprint1( qiVector X, ui size, unsigned nperline );
	#define VQI_cprint VQI_cprint1
	#define VQI_print( x, sz, npl ) VQI_fprint1( stdout, x, sz, npl, 80 )
	void  __vf   VQI_write1( FILE _VFAR *stream, qiVector X, ui size );
	#define VQI_write VQI_write1
	void  __vf   VQI_nwrite1( FILE _VFAR *stream, unsigned n, ui size, ... );
	#define VQI_nwrite VQI_nwrite1
#endif
#if !(((defined __BORLANDC__) && (__BORLANDC__ < 0x600)))
	void  __vf   VQI_read( qiVector X, ui size, FILE _VFAR *stream );
	void  __vf   VQI_nread( unsigned n, ui size, FILE _VFAR *stream, ... );
#else  /* old versions of Borland C need different implementation: */
	void  __vf   VQI_read1( qiVector X, ui size, FILE _VFAR *stream );
	#define VQI_read VQI_read1
	void  __vf   VQI_nread1( unsigned n, ui size, FILE _VFAR *stream, ... );
	#define VQI_nread VQI_nread1
#endif
void  __vf   VQI_setWriteSeparate( char _VFAR *SepString ); /* for VQI_write */
void  __vf   VQI_setNWriteSeparate( char _VFAR *SepString ); /* for VQI_nwrite */
#ifdef V_HUGE
    void  __vf   VQI_store(  FILE _VFAR *stream, qiVector X, ui size );
    void  __vf   VQI_recall( qiVector X, ui size, FILE _VFAR *stream );
#else
    #ifdef __cplusplus
         void  inline VQI_store( FILE _VFAR *stream, qiVector X, ui size )
         {    fwrite( X, sizeof(quad), size, stream ); 
         }
         void  inline VQI_recall( qiVector X, ui size, FILE _VFAR *stream )
         {    fread(  X, sizeof(quad), size, stream );
         }
    #else
        #define VQI_store( str, X, sz )  \
                     fwrite( X, sizeof(quad), sz, str )
        #define VQI_recall( X, sz, str ) \
                     fread(  X, sizeof(quad), sz, str )
    #endif
#endif      /* VQI_store, VQI_recall in binary format */

#ifdef __cplusplus
}  // end of extern "C"
#endif

#endif   /*  __VQISTD_H    */
