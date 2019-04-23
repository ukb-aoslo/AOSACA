/*  cudaVUSstd.h

  vector management functions for data type "unsigned short".

  Copyright (c) 1996-2017 by OptiCode - Dr. Martin Sander Software Dev.
  All Rights Reserved.
*/

#ifndef __CUDAVUSSTD_H
#define __CUDAVUSSTD_H

#if !defined( __CUDAVECLIB_H )
   #include <cudaVecLib.h>
#endif

/******************  cudaVUS_ functions: **********************************
	 act on vectors in CUDA device memory; 
	 scalar parameters and return values on host
******************  cusdVUS_ functions: **********************************
	 also act on vectors in CUDA device memory; 
	 scalar parameters and return values by address on device memory
************************************************************************/

#ifdef __cplusplus
   extern "C" {
#endif

/**********************  Generation *************************************/

usVector  __vf  cudaVUS_vector( ui size );   /* allocates a vector on device memory */
usVector  __vf  cudaVUS_vector0( ui size );
 /* The following functions allocate device-accessible, "pinned" memory on the host.
	This memory is mapped onto the device memory space. The resulting device address is returned.
	The vector can be accessed either by its host address "hostPtr" e.g., VUS_ramp( hostPtr, size, 0, 1 );
	or by its device address , e.g., cudaVUS_ramp( devicePtr, size, 0, 1 );     */
usVector  __vf  cudaVUS_pinnedVector(  usVector *hostPtr, ui size ); 
usVector  __vf  cudaVUS_pinnedVector0( usVector *hostPtr, ui size );

/***************  Addressing single vector elements ******************/

unsigned short * __vcuf OVCUAPI cudaVUS_Pelement( usVector X, ui n );
unsigned short   __vcuf OVCUAPI cudaVUS_element( usVector X, ui n );
void             __vcuf OVCUAPI cudaVUS_getElement( unsigned short *y, usVector X, ui n );
void             __vcuf OVCUAPI cusdVUS_getElement( unsigned short *d_y, usVector X, ui n );
void             __vcuf OVCUAPI cudaVUS_setElement( usVector X, ui n, unsigned short C );
void             __vcuf OVCUAPI cusdVUS_setElement( usVector X, ui n, unsigned short *C );

/****************** Initialization  ******************************/

overror_t  __vcuf OVCUAPI   cudaVUS_equ0( usVector X, ui size );
overror_t  __vcuf OVCUAPI   cudaVUS_equC( usVector X, ui size, unsigned short C );
overror_t  __vcuf OVCUAPI   cusdVUS_equC( usVector X, ui size, unsigned short *C );
overror_t  __vcuf OVCUAPI   cudaVUS_equV( usVector Y, usVector X, ui size ); /* copies from device to device */
overror_t  __vcuf OVCUAPI   cudaVUS_equVhost( usVector Y, usVector X, ui size );  /* copies from host to device */
overror_t  __vcuf OVCUAPI   VUS_equVdevice( usVector Y, usVector X, ui size );  /* copies from device to host */
overror_t  __vcuf OVCUAPI   cudaVUS_ramp( usVector X, ui size, unsigned short Start, short Rise );
overror_t  __vcuf OVCUAPI   cusdVUS_ramp( usVector X, ui size, unsigned short *Start, short *Rise );

/******  Linear Congruential random generator with Bays-Durham shuffle:  ***********
  Random series is generated on the CPU. State must be stored in host memory!
  seed!=0 --> initialization of state. seed==0 --> continue series from previous call with the same state. */
overror_t  __vcuf OVCUAPI  cudaVUS_randomLC( usVector X, ui size, long seed, unsigned short MinVal, unsigned short MaxVal, V_RANDOMLCSTATE *state );
overror_t  __vcuf OVCUAPI  cusdVUS_randomLC( usVector X, ui size, long seed, unsigned short *MinVal, unsigned short *MaxVal, V_RANDOMLCSTATE *state );
/**  simplified version: Series cannot be made continuous across calls: */
overror_t  __vcuf OVCUAPI  cudaVUS_random( usVector X, ui size, long seed, unsigned short MinVal, unsigned short MaxVal );
overror_t  __vcuf OVCUAPI  cusdVUS_random( usVector X, ui size, long seed, unsigned short *MinVal, unsigned short *MaxVal );


/**************  Data-type overror_terconversions  **************************/

overror_t __vcuf OVCUAPI   cudaV_UBtoUS( usVector Y, ubVector X, ui size );  /* up-conversion */
overror_t __vcuf OVCUAPI   cudaV_UStoU(  uVector  Y, usVector  X, ui size );
overror_t __vcuf OVCUAPI   cudaV_UStoUL( ulVector Y, usVector  X, ui size );

overror_t __vcuf OVCUAPI   cudaV_UStoUB(  ubVector Y, usVector X, ui size ); /* down-conversion */
overror_t  __vcuf OVCUAPI   cudaV_SItoUS( usVector Y, siVector X, ui size );
overror_t  __vcuf OVCUAPI   cudaV_UStoSI( siVector Y, usVector X, ui size );
overror_t  __vcuf OVCUAPI   cudaV_UtoUS(  usVector Y, uVector  X, ui size );
overror_t  __vcuf OVCUAPI   cudaV_ULtoUS( usVector Y, ulVector X, ui size );
#if defined _WIN64
    overror_t __vcuf OVCUAPI   cudaV_UStoUQ( uqVector Y, usVector  X, ui size );
    overror_t __vcuf OVCUAPI   cudaV_UQtoUS( usVector Y, uqVector X, ui size );
#endif

overror_t  __vcuf OVCUAPI   cudaV_UStoF(  fVector Y, usVector X, ui size );
overror_t  __vcuf OVCUAPI   cudaV_UStoD(  dVector Y, usVector X, ui size );


/************** Index-oriented manipulations ***************************/

overror_t  __vcuf OVCUAPI   cudaVUS_reflect( usVector X, ui size );
overror_t  __vcuf OVCUAPI   cudaVUS_rev( usVector Y, usVector X, ui size );
overror_t  __vcuf OVCUAPI   cudaVUS_rotate( usVector Y, usVector X, ui size, ssize_t pos );
overror_t  __vcuf OVCUAPI   cudaVUS_rotate_buf( usVector Y, usVector X, ui size, ssize_t pos, usVector Buf );
overror_t  __vcuf OVCUAPI   cudaVUS_delete( usVector X, ui size, ui pos );
overror_t  __vcuf OVCUAPI   cudaVUS_insert( usVector X, ui size, ui pos, unsigned short C );
overror_t  __vcuf OVCUAPI   cusdVUS_insert( usVector X, ui size, ui pos, unsigned short *C );
overror_t  __vcuf OVCUAPI   cudaVUS_sort( usVector Y, usVector X, ui size, int dir );
overror_t  __vcuf OVCUAPI   cudaVUS_sortind( uiVector Ind, usVector X, ui size, int dir );

overror_t  __vcuf OVCUAPI   cudaVUS_subvector( usVector Y, ui sizey, usVector X, ssize_t samp );
overror_t  __vcuf OVCUAPI   cudaVUS_subvector_equC( usVector Y, ui subsz, ui samp, unsigned short C );
overror_t  __vcuf OVCUAPI   cusdVUS_subvector_equC( usVector Y, ui subsz, ui samp, unsigned short *C );
overror_t  __vcuf OVCUAPI   cudaVUS_subvector_equV( usVector Y, ui subsz, ui samp, usVector X );

overror_t  __vcuf OVCUAPI   cudaVUS_indpick( usVector Y, uiVector Ind, ui sizey, usVector X );
overror_t  __vcuf OVCUAPI   cudaVUS_indput(  usVector Y, usVector X, uiVector Ind, ui sizex );
overror_t  __vcuf OVCUAPI   cudaVUS_searchC( ui *h_Ind, usVector XTab, ui size, unsigned short C, int mode );
overror_t  __vcuf OVCUAPI   cusdVUS_searchC( ui *d_Ind, usVector XTab, ui size, unsigned short *C, int mode );
overror_t  __vcuf OVCUAPI   cudaVUS_searchV( uiVector Ind, usVector X, ui sizex, usVector Tab, ui sizetab, int mode );

/********************   One-dimensional Vector Operations  ********/

overror_t  __vcuf OVCUAPI   cudaVUS_sum( unsigned short *h_RetVal, usVector X, ui size );
overror_t  __vcuf OVCUAPI   cudaVUS_max( unsigned short *h_RetVal, usVector X, ui size );
overror_t  __vcuf OVCUAPI   cudaVUS_min( unsigned short *h_RetVal, usVector X, ui size );
overror_t  __vcuf OVCUAPI   cudaVUS_maxind( unsigned short *h_RetVal, ui *Ind, usVector X, ui size );
overror_t  __vcuf OVCUAPI   cudaVUS_minind( unsigned short *h_RetVal, ui *Ind, usVector X, ui size );
overror_t  __vcuf OVCUAPI   cudaVUS_fsum( double *h_RetVal, usVector X, ui size );
overror_t  __vcuf OVCUAPI   cudaVUS_mean( double *h_RetVal, usVector X, ui size );
overror_t  __vcuf OVCUAPI   cudaVUS_runsum( usVector Y, usVector X, ui size );
overror_t  __vcuf OVCUAPI   cudaVUS_runmax( usVector Y, usVector X, ui size );
overror_t  __vcuf OVCUAPI   cudaVUS_runmin( usVector Y, usVector X, ui size );

overror_t  __vcuf OVCUAPI   cusdVUS_sum( unsigned short *d_RetVal, usVector X, ui size );
overror_t  __vcuf OVCUAPI   cusdVUS_max( unsigned short *d_RetVal, usVector X, ui size );
overror_t  __vcuf OVCUAPI   cusdVUS_min( unsigned short *d_RetVal, usVector X, ui size );
overror_t  __vcuf OVCUAPI   cusdVUS_maxind( unsigned short *d_RetVal, ui *Ind, usVector X, ui size );
overror_t  __vcuf OVCUAPI   cusdVUS_minind( unsigned short *d_RetVal, ui *Ind, usVector X, ui size );
overror_t  __vcuf OVCUAPI   cusdVUS_fsum( double *d_RetVal, usVector X, ui size );
overror_t  __vcuf OVCUAPI   cusdVUS_mean( double *d_RetVal, usVector X, ui size );

int        __vcuf OVCUAPI   cudaVUS_iselementC( usVector Tab, ui size, unsigned short C );
int        __vcuf OVCUAPI   cusdVUS_iselementC( usVector Tab, ui size, unsigned short *C );
overror_t  __vcuf OVCUAPI   cudaVUS_iselementV( ui *h_nFound, usVector Y, usVector X, ui sizex, usVector Tab, ui sizetab );

overror_t  __vcuf OVCUAPI   cudaVUS_distribution( ui *h_nOutside, uiVector Abund, usVector Limits, ui nbins, usVector X, ui sizex, int mode );
overror_t  __vcuf OVCUAPI   cusdVUS_distribution( ui *d_nOutside, uiVector Abund, usVector Limits, ui nbins, usVector X, ui sizex, int mode );


/***************************  Input and Output *****************************
	The input/output functions involve memory transfers from device
	to host memory or vice versa. The generic cudaVUS_input/output functions
	allocate their own host buffers, whereas the cudaVUS_xxx_buf functions
	take a user-supplied buffer h_Wk and are much more efficient.          */

overror_t  __vf    cudaVUS_fprint( FILE *stream, usVector X, ui size, unsigned nperline, unsigned linewidth );
overror_t  __vf    cudaVUS_cprint( usVector X, ui size, unsigned nperline );
#define       cudaVUS_print( x, sz, npl )  cudaVUS_fprint( stdout, x, sz, npl, 80 )
overror_t  __vf    cudaVUS_fprint_buf( FILE *stream, usVector d_X, ui size, unsigned nperline, unsigned linewidth, usVector h_Wk );
overror_t  __vf    cudaVUS_cprint_buf( usVector d_X, ui size, unsigned nperline, usVector h_Wk );
#define       cudaVUS_print_buf( d_x, sz, npl, h_Wk )  cudaVUS_fprint_buf( stdout, d_x, sz, npl, 80, h_Wk )
 /*  cudaVUS_print, cudaVUS_cprint are usable only for console applications!  */
overror_t  __vf    cudaVUS_write( FILE *stream, usVector X, ui size  );
overror_t  __vf    cudaVUS_read( usVector X, ui size, FILE *stream );
overror_t  __vf    cudaVUS_write_buf( FILE *stream, usVector d_X, ui size, usVector h_Wk );
overror_t  __vf    cudaVUS_read_buf( usVector d_X, ui size, FILE *stream, usVector h_Wk );
                     /* cudaVUS_write, cudaVUS_read in ascii format */
overror_t  __vf     cudaVUS_store( FILE *stream, usVector X, ui size );
overror_t  __vf     cudaVUS_recall( usVector X, ui size, FILE *stream );
overror_t  __vf     cudaVUS_store_buf( FILE *stream, usVector d_X, ui size, usVector h_Wk );
overror_t  __vf     cudaVUS_recall_buf( usVector d_X, ui size, FILE *stream, usVector h_Wk );
                     /* cudaVUS_store, cudaVUS_recall in binary format */


#ifdef __cplusplus
}  // end of extern "C"
#endif

/******************  VUScu_ functions: **********************************
	act on host memory, using the CUDA device for processing
************************************************************************/


#ifdef __cplusplus
   extern "C" {
#endif

/****************** Initialization  ******************************/

void  __vcuf OVCUAPI   VUScu_equ0( usVector X, ui size );
void  __vcuf OVCUAPI   VUScu_equC( usVector X, ui size, unsigned short C );
void  __vcuf OVCUAPI   VUScu_equV( usVector Y, usVector X, ui size ); /* copies from device to device */
void  __vcuf OVCUAPI   VUScu_ramp( usVector X, ui size, unsigned short Start, short Rise );
/* no Vcu_random functions: random generation runs on CPU anyway */


/**************  Data-type interconversions  **************************/

void __vcuf OVCUAPI   Vcu_UBtoUS( usVector Y, ubVector X, ui size );  /* up-conversion */
void __vcuf OVCUAPI   Vcu_UStoU(  uVector  Y, usVector  X, ui size );
void __vcuf OVCUAPI   Vcu_UStoUL( ulVector Y, usVector  X, ui size );

void  __vcuf OVCUAPI   Vcu_UStoUB(  ubVector Y, usVector X, ui size ); /* down-conversion */
void  __vcuf OVCUAPI   Vcu_SItoUS( usVector Y, siVector X, ui size );
void  __vcuf OVCUAPI   Vcu_UStoSI( siVector Y, usVector X, ui size );
void  __vcuf OVCUAPI   Vcu_UtoUS(  usVector Y, uVector  X, ui size );
void  __vcuf OVCUAPI   Vcu_ULtoUS( usVector Y, ulVector X, ui size );
#if defined _WIN64
    void __vcuf OVCUAPI   Vcu_UStoUQ( uqVector Y, usVector  X, ui size );
    void __vcuf OVCUAPI   Vcu_UQtoUS( usVector Y, uqVector X, ui size );
#endif

void  __vcuf OVCUAPI   Vcu_UStoF(  fVector Y, usVector X, ui size );
void  __vcuf OVCUAPI   Vcu_UStoD(  dVector Y, usVector X, ui size );


/************** Index-oriented manipulations ***************************/

void  __vcuf OVCUAPI   VUScu_reflect( usVector X, ui size );
void  __vcuf OVCUAPI   VUScu_rev( usVector Y, usVector X, ui size );
void  __vcuf OVCUAPI   VUScu_rotate( usVector Y, usVector X, ui size, ssize_t pos );
void  __vcuf OVCUAPI   VUScu_rotate_buf( usVector Y, usVector X, ui size, ssize_t pos, usVector Buf );
void  __vcuf OVCUAPI   VUScu_delete( usVector X, ui size, ui pos );
void  __vcuf OVCUAPI   VUScu_insert( usVector X, ui size, ui pos, unsigned short C );
void  __vcuf OVCUAPI   VUScu_sort( usVector Y, usVector X, ui size, int dir );
void  __vcuf OVCUAPI   VUScu_sortind( uiVector Ind, usVector X, ui size, int dir );

void  __vcuf OVCUAPI   VUScu_subvector( usVector Y, ui sizey, usVector X, ssize_t samp );
void  __vcuf OVCUAPI   VUScu_subvector_equC( usVector Y, ui subsz, ui samp, unsigned short C );
void  __vcuf OVCUAPI   VUScu_subvector_equV( usVector Y, ui subsz, ui samp, usVector X );

  /* no V?cu_indpick, V?cu_indput possible! */
ui    __vcuf OVCUAPI   VUScu_searchC( usVector XTab, ui size, unsigned short C, int mode );
void  __vcuf OVCUAPI   VUScu_searchV( uiVector Ind, usVector X, ui sizex, usVector Tab, ui sizetab, int mode );

/********************   One-dimensional Vector Operations  ********/

unsigned short __vcuf OVCUAPI   VUScu_sum( usVector X, ui size );
unsigned short  __vcuf OVCUAPI   VUScu_max( usVector X, ui size );
unsigned short  __vcuf OVCUAPI   VUScu_min( usVector X, ui size );
unsigned short  __vcuf OVCUAPI   VUScu_maxind( ui *Ind, usVector X, ui size );
unsigned short  __vcuf OVCUAPI   VUScu_minind( ui *Ind, usVector X, ui size );
double          __vcuf OVCUAPI   VUScu_fsum( usVector X, ui size );
double          __vcuf OVCUAPI   VUScu_mean( usVector X, ui size );
void            __vcuf OVCUAPI   VUScu_runsum( usVector Y, usVector X, ui size );
void            __vcuf OVCUAPI   VUScu_runmax( usVector Y, usVector X, ui size );
void            __vcuf OVCUAPI   VUScu_runmin( usVector Y, usVector X, ui size );

int    __vcuf OVCUAPI   VUScu_iselementC( usVector Tab, ui size, unsigned short C );
ui     __vcuf OVCUAPI   VUScu_iselementV( usVector Y, usVector X, ui sizex, usVector Tab, ui sizetab );

ui     __vcuf OVCUAPI   VUScu_distribution( uiVector Abund, usVector Limits, ui nbins, usVector X, ui sizex, int mode );

#ifdef __cplusplus
}  // end of extern "C"
#endif

#endif   /*  __CUDAVUSSTD_H    */
