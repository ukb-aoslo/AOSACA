/*  cudaVULstd.h

  vector management functions for data type "unsigned long".

  Copyright (c) 1996-2017 by OptiCode - Dr. Martin Sander Software Dev.
  All Rights Reserved.
*/

#ifndef __CUDAVULSTD_H
#define __CUDAVULSTD_H

#if !defined( __CUDAVECLIB_H )
   #include <cudaVecLib.h>
#endif

/******************  cudaVUL_ functions: **********************************
	 act on vectors in CUDA device memory; 
	 scalar parameters and return values on host
******************  cusdVUL_ functions: **********************************
	 also act on vectors in CUDA device memory; 
	 scalar parameters and return values by address on device memory
************************************************************************/

#ifdef __cplusplus
    extern "C" {
#endif

/*****************************  Generation ******************************/

ulVector  __vcuf   cudaVUL_vector( ui size );   /* allocates a vector on device memory */
ulVector  __vcuf   cudaVUL_vector0( ui size );
 /* The following functions allocate device-accessible, "pinned" memory on the host.
	This memory is mapped onto the device memory space. The resulting device address is returned.
	The vector can be accessed either by its host address "hostPtr" e.g., VUL_ramp( hostPtr, size, 0, 1 );
	or by its device address , e.g., cudaVUL_ramp( devicePtr, size, 0, 1 );     */
ulVector  __vcuf   cudaVUL_pinnedVector(  ulVector *hostPtr, ui size ); 
ulVector  __vcuf   cudaVUL_pinnedVector0( ulVector *hostPtr, ui size );

/***************  Addressing single vector elements ******************/

unsigned long * __vcuf OVCUAPI cudaVUL_Pelement( ulVector X, ui n );
unsigned long   __vcuf OVCUAPI cudaVUL_element( ulVector X, ui n );
void            __vcuf OVCUAPI cudaVUL_getElement( unsigned long *y, ulVector X, ui n );
void            __vcuf OVCUAPI cusdVUL_getElement( unsigned long *d_y, ulVector X, ui n );
void            __vcuf OVCUAPI cudaVUL_setElement( ulVector X, ui n, unsigned long C );
void            __vcuf OVCUAPI cusdVUL_setElement( ulVector X, ui n, unsigned long *C );

/****************** Initialization  ******************************/

overror_t  __vcuf OVCUAPI   cudaVUL_equ0( ulVector X, ui size );
overror_t  __vcuf OVCUAPI   cudaVUL_equC( ulVector X, ui size, unsigned long C );
overror_t  __vcuf OVCUAPI   cusdVUL_equC( ulVector X, ui size, unsigned long *C );
overror_t  __vcuf OVCUAPI   cudaVUL_equV( ulVector Y, ulVector X, ui size ); /* copies from device to device */
overror_t  __vcuf           cudaVUL_equVhost( ulVector Y, ulVector X, ui size );  /* copies from host to device */
overror_t  __vcuf           VUL_equVdevice( ulVector Y, ulVector X, ui size );  /* copies from device to host */
overror_t  __vcuf OVCUAPI   cudaVUL_ramp( ulVector X, ui size, unsigned long Start, long Rise );
overror_t  __vcuf OVCUAPI   cusdVUL_ramp( ulVector X, ui size, unsigned long *Start, long *Rise );

/******  Linear Congruential random generator with Bays-Durham shuffle:  ***********
  Random series is generated on the CPU. State must be stored in host memory!
  seed!=0 --> initialization of state. seed==0 --> continue series from previous call with the same state. */
overror_t  __vcuf OVCUAPI  cudaVUL_randomLC( ulVector X, ui size, long seed, unsigned long MinVal, unsigned long MaxVal, V_RANDOMLCSTATE *state );
overror_t  __vcuf OVCUAPI  cusdVUL_randomLC( ulVector X, ui size, long seed, unsigned long *MinVal, unsigned long *MaxVal, V_RANDOMLCSTATE *state );
/**  simplified version: Series cannot be made continuous across calls: */
overror_t  __vcuf OVCUAPI  cudaVUL_random( ulVector X, ui size, long seed, unsigned long MinVal, unsigned long MaxVal );
overror_t  __vcuf OVCUAPI  cusdVUL_random( ulVector X, ui size, long seed, unsigned long *MinVal, unsigned long *MaxVal );


/**************  Data-type interconversions  **************************/

overror_t __vcuf OVCUAPI   cudaV_UBtoUL( ulVector Y, ubVector X, ui size );  /* up-conversion */
overror_t __vcuf OVCUAPI   cudaV_UStoUL( ulVector Y, usVector X, ui size );
overror_t __vcuf OVCUAPI   cudaV_UtoUL(  ulVector Y, uVector  X, ui size );

overror_t __vcuf OVCUAPI   cudaV_ULtoUB(  ubVector Y, ulVector X, ui size ); /* down-conversion */
overror_t  __vcuf OVCUAPI   cudaV_LItoUL( ulVector Y, liVector X, ui size );
overror_t  __vcuf OVCUAPI   cudaV_ULtoLI( liVector Y, ulVector X, ui size );
overror_t  __vcuf OVCUAPI   cudaV_ULtoUS( usVector Y, ulVector X, ui size );
overror_t  __vcuf OVCUAPI   cudaV_ULtoU(  uVector  Y, ulVector X, ui size );
#if defined _WIN64
    overror_t __vcuf OVCUAPI   cudaV_ULtoUQ( uqVector Y, ulVector  X, ui size );
    overror_t __vcuf OVCUAPI   cudaV_UQtoUL( ulVector Y, uqVector X, ui size );
#endif

overror_t  __vcuf OVCUAPI   cudaV_ULtoF(  fVector Y, ulVector X, ui size );
overror_t  __vcuf OVCUAPI   cudaV_ULtoD(  dVector Y, ulVector X, ui size );


/************** Index-oriented manipulations ***************************/

overror_t  __vcuf OVCUAPI   cudaVUL_reflect( ulVector X, ui size );
overror_t  __vcuf OVCUAPI   cudaVUL_rev( ulVector Y, ulVector X, ui size );
overror_t  __vcuf OVCUAPI   cudaVUL_rotate( ulVector Y, ulVector X, ui size, ssize_t pos );
overror_t  __vcuf OVCUAPI   cudaVUL_rotate_buf( ulVector Y, ulVector X, ui size, ssize_t pos, ulVector Buf );
overror_t  __vcuf OVCUAPI   cudaVUL_delete( ulVector X, ui size, ui pos );
overror_t  __vcuf OVCUAPI   cudaVUL_insert( ulVector X, ui size, ui pos, unsigned long C );
overror_t  __vcuf OVCUAPI   cusdVUL_insert( ulVector X, ui size, ui pos, unsigned long *C );
overror_t  __vcuf OVCUAPI   cudaVUL_sort( ulVector Y, ulVector X, ui size, int dir );
overror_t  __vcuf OVCUAPI   cudaVUL_sortind( uiVector Ind, ulVector X, ui size, int dir );

overror_t  __vcuf OVCUAPI   cudaVUL_subvector( ulVector Y, ui sizey, ulVector X, ssize_t samp );
overror_t  __vcuf OVCUAPI   cudaVUL_subvector_equC( ulVector Y, ui subsz, ui samp, unsigned long C );
overror_t  __vcuf OVCUAPI   cusdVUL_subvector_equC( ulVector Y, ui subsz, ui samp, unsigned long *C );
overror_t  __vcuf OVCUAPI   cudaVUL_subvector_equV( ulVector Y, ui subsz, ui samp, ulVector X );

overror_t  __vcuf OVCUAPI   cudaVUL_indpick( ulVector Y, uiVector Ind, ui sizey, ulVector X );
overror_t  __vcuf OVCUAPI   cudaVUL_indput(  ulVector Y, ulVector X, uiVector Ind, ui sizex );
overror_t  __vcuf OVCUAPI   cudaVUL_searchC( ui *h_Ind, ulVector XTab, ui size, unsigned long C, int mode );
overror_t  __vcuf OVCUAPI   cusdVUL_searchC( ui *d_Ind, ulVector XTab, ui size, unsigned long *C, int mode );
overror_t  __vcuf OVCUAPI   cudaVUL_searchV( uiVector Ind, ulVector X, ui sizex, ulVector Tab, ui sizetab, int mode );

/********************   One-dimensional Vector Operations  ********/

overror_t  __vcuf OVCUAPI   cudaVUL_sum( unsigned long *h_RetVal, ulVector X, ui size );
overror_t  __vcuf OVCUAPI   cudaVUL_max( unsigned long *h_RetVal, ulVector X, ui size );
overror_t  __vcuf OVCUAPI   cudaVUL_min( unsigned long *h_RetVal, ulVector X, ui size );
overror_t  __vcuf OVCUAPI   cudaVUL_maxind( unsigned long *h_RetVal, ui *Ind, ulVector X, ui size );
overror_t  __vcuf OVCUAPI   cudaVUL_minind( unsigned long *h_RetVal, ui *Ind, ulVector X, ui size );
overror_t  __vcuf OVCUAPI   cudaVUL_fsum( double *h_RetVal, ulVector X, ui size );
overror_t  __vcuf OVCUAPI   cudaVUL_mean( double *h_RetVal, ulVector X, ui size );
overror_t  __vcuf OVCUAPI   cudaVUL_runsum( ulVector Y, ulVector X, ui size );
overror_t  __vcuf OVCUAPI   cudaVUL_runmax( ulVector Y, ulVector X, ui size );
overror_t  __vcuf OVCUAPI   cudaVUL_runmin( ulVector Y, ulVector X, ui size );

overror_t  __vcuf OVCUAPI   cusdVUL_sum( unsigned long *d_RetVal, ulVector X, ui size );
overror_t  __vcuf OVCUAPI   cusdVUL_max( unsigned long *d_RetVal, ulVector X, ui size );
overror_t  __vcuf OVCUAPI   cusdVUL_min( unsigned long *d_RetVal, ulVector X, ui size );
overror_t  __vcuf OVCUAPI   cusdVUL_maxind( unsigned long *d_RetVal, ui *Ind, ulVector X, ui size );
overror_t  __vcuf OVCUAPI   cusdVUL_minind( unsigned long *d_RetVal, ui *Ind, ulVector X, ui size );
overror_t  __vcuf OVCUAPI   cusdVUL_fsum( double *d_RetVal, ulVector X, ui size );
overror_t  __vcuf OVCUAPI   cusdVUL_mean( double *d_RetVal, ulVector X, ui size );

int        __vcuf OVCUAPI   cudaVUL_iselementC( ulVector Tab, ui size, unsigned long  C );
int        __vcuf OVCUAPI   cusdVUL_iselementC( ulVector Tab, ui size, unsigned long  *C );
overror_t  __vcuf OVCUAPI   cudaVUL_iselementV( ui *h_nFound, ulVector Y, ulVector X, ui sizex, ulVector Tab, ui sizetab );

overror_t  __vcuf OVCUAPI   cudaVUL_distribution( ui *h_nOutside, uiVector Abund, ulVector Limits, ui nbins, ulVector X, ui sizex, int mode );
overror_t  __vcuf OVCUAPI   cusdVUL_distribution( ui *d_nOutside, uiVector Abund, ulVector Limits, ui nbins, ulVector X, ui sizex, int mode );

/***************************  Input and Output *****************************
	The input/output functions involve memory transfers from device
	to host memory or vice versa. The generic cudaVUL_input/output functions
	allocate their own host buffers, whereas the cudaVUL_xxx_buf functions
	take a user-supplied buffer h_Wk and are much more efficient.          */

overror_t  __vf    cudaVUL_fprint( FILE *stream, ulVector X, ui size, unsigned nperline, unsigned linewidth );
overror_t  __vf    cudaVUL_cprint( ulVector X, ui size, unsigned nperline );
#define       cudaVUL_print( x, sz, npl )  cudaVUL_fprint( stdout, x, sz, npl, 80 )
overror_t  __vf    cudaVUL_fprint_buf( FILE *stream, ulVector d_X, ui size, unsigned nperline, unsigned linewidth, ulVector h_Wk );
overror_t  __vf    cudaVUL_cprint_buf( ulVector d_X, ui size, unsigned nperline, ulVector h_Wk );
#define       cudaVUL_print_buf( d_x, sz, npl, h_Wk )  cudaVUL_fprint_buf( stdout, d_x, sz, npl, 80, h_Wk )
 /*  cudaVUL_print, cudaVUL_cprint are usable only for console applications!  */
overror_t  __vf    cudaVUL_write( FILE *stream, ulVector X, ui size  );
overror_t  __vf    cudaVUL_read( ulVector X, ui size, FILE *stream );
overror_t  __vf    cudaVUL_write_buf( FILE *stream, ulVector d_X, ui size, ulVector h_Wk );
overror_t  __vf    cudaVUL_read_buf( ulVector d_X, ui size, FILE *stream, ulVector h_Wk );
                     /* cudaVUL_write, cudaVUL_read in ascii format */
overror_t  __vf     cudaVUL_store( FILE *stream, ulVector X, ui size );
overror_t  __vf     cudaVUL_recall( ulVector X, ui size, FILE *stream );
overror_t  __vf     cudaVUL_store_buf( FILE *stream, ulVector d_X, ui size, ulVector h_Wk );
overror_t  __vf     cudaVUL_recall_buf( ulVector d_X, ui size, FILE *stream, ulVector h_Wk );
                     /* cudaVUL_store, cudaVUL_recall in binary format */


#ifdef __cplusplus
}  // end of extern "C"
#endif

/******************  VULcu_ functions: **********************************
	act on host memory, using the CUDA device for processing
************************************************************************/


#ifdef __cplusplus
    extern "C" {
#endif

/****************** Initialization  ******************************/

void  __vcuf OVCUAPI   VULcu_equ0( ulVector X, ui size );
void  __vcuf OVCUAPI   VULcu_equC( ulVector X, ui size, unsigned long C );
void  __vcuf OVCUAPI   VULcu_equV( ulVector Y, ulVector X, ui size ); /* copies from device to device */
void  __vcuf OVCUAPI   VULcu_equVhost( ulVector Y, ulVector X, ui size );  /* copies from host to device */
void  __vcuf OVCUAPI   VULcu_ramp( ulVector X, ui size, unsigned long Start, long Rise );
/* no Vcu_random functions: random generation runs on CPU anyway */


/**************  Data-type interconversions  **************************/

void __vcuf OVCUAPI   Vcu_UBtoUL( ulVector Y, ubVector X, ui size );  /* up-conversion */
void __vcuf OVCUAPI   Vcu_UStoUL( ulVector Y, usVector X, ui size );
void __vcuf OVCUAPI   Vcu_UtoUL(  ulVector Y, uVector  X, ui size );

void __vcuf OVCUAPI   Vcu_ULtoUB(  ubVector Y, ulVector X, ui size ); /* down-conversion */
void  __vcuf OVCUAPI   Vcu_LItoUL( ulVector Y, liVector X, ui size );
void  __vcuf OVCUAPI   Vcu_ULtoLI( liVector Y, ulVector X, ui size );
void  __vcuf OVCUAPI   Vcu_ULtoUS( usVector Y, ulVector X, ui size );
void  __vcuf OVCUAPI   Vcu_ULtoU(  uVector  Y, ulVector X, ui size );
#if defined _WIN64
    void __vcuf OVCUAPI   Vcu_ULtoUQ( uqVector Y, ulVector  X, ui size );
    void __vcuf OVCUAPI   Vcu_UQtoUL( ulVector Y, uqVector X, ui size );
#endif

void  __vcuf OVCUAPI   Vcu_ULtoF(  fVector Y, ulVector X, ui size );
void  __vcuf OVCUAPI   Vcu_ULtoD(  dVector Y, ulVector X, ui size );


/************** Index-oriented manipulations ***************************/

void  __vcuf OVCUAPI   VULcu_reflect( ulVector X, ui size );
void  __vcuf OVCUAPI   VULcu_rev( ulVector Y, ulVector X, ui size );
void  __vcuf OVCUAPI   VULcu_rotate( ulVector Y, ulVector X, ui size, ssize_t pos );
void  __vcuf OVCUAPI   VULcu_rotate_buf( ulVector Y, ulVector X, ui size, ssize_t pos, ulVector Buf );
void  __vcuf OVCUAPI   VULcu_delete( ulVector X, ui size, ui pos );
void  __vcuf OVCUAPI   VULcu_insert( ulVector X, ui size, ui pos, unsigned long C );
void  __vcuf OVCUAPI   VULcu_sort( ulVector Y, ulVector X, ui size, int dir );
void  __vcuf OVCUAPI   VULcu_sortind( uiVector Ind, ulVector X, ui size, int dir );

void  __vcuf OVCUAPI   VULcu_subvector( ulVector Y, ui sizey, ulVector X, ssize_t samp );
void  __vcuf OVCUAPI   VULcu_subvector_equC( ulVector Y, ui subsz, ui samp, unsigned long C );
void  __vcuf OVCUAPI   VULcu_subvector_equV( ulVector Y, ui subsz, ui samp, ulVector X );

  /* no V?cu_indpick, V?cu_indput possible! */
ui    __vcuf OVCUAPI   VULcu_searchC( ulVector XTab, ui size, unsigned long C, int mode );
void  __vcuf OVCUAPI   VULcu_searchV( uiVector Ind, ulVector X, ui sizex, ulVector Tab, ui sizetab, int mode );

/********************   One-dimensional Vector Operations  ********/

unsigned long  __vcuf OVCUAPI   VULcu_sum( ulVector X, ui size );
unsigned long  __vcuf OVCUAPI   VULcu_max( ulVector X, ui size );
unsigned long  __vcuf OVCUAPI   VULcu_min( ulVector X, ui size );
unsigned long  __vcuf OVCUAPI   VULcu_maxind( ui *Ind, ulVector X, ui size );
unsigned long  __vcuf OVCUAPI   VULcu_minind( ui *Ind, ulVector X, ui size );
double         __vcuf OVCUAPI   VULcu_fsum( ulVector X, ui size );
double         __vcuf OVCUAPI   VULcu_mean( ulVector X, ui size );
void           __vcuf OVCUAPI   VULcu_runsum( ulVector Y, ulVector X, ui size );
void           __vcuf OVCUAPI   VULcu_runmax( ulVector Y, ulVector X, ui size );
void           __vcuf OVCUAPI   VULcu_runmin( ulVector Y, ulVector X, ui size );

int    __vcuf OVCUAPI   VULcu_iselementC( ulVector Tab, ui size, unsigned long  C );
ui     __vcuf OVCUAPI   VULcu_iselementV( ulVector Y, ulVector X, ui sizex, ulVector Tab, ui sizetab );

ui     __vcuf OVCUAPI   VULcu_distribution( uiVector Abund, ulVector Limits, ui nbins, ulVector X, ui sizex, int mode );

#ifdef __cplusplus
}  // end of extern "C"
#endif

#endif   /*  __CUDAVULSTD_H    */
