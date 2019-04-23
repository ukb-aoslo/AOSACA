/*  cudaVUQstd.h

  vector management functions for data type "uquad".

  Copyright (c) 1996-2017 by OptiCode - Dr. Martin Sander Software Dev.
  All Rights Reserved.
*/

#if defined _WIN64
#ifndef __CUDAVUQSTD_H
#define __CUDAVUQSTD_H

#if !defined( __CUDAVECLIB_H )
   #include <cudaVecLib.h>
#endif

/******************  cudaVUQ_ functions: **********************************
	 act on vectors in CUDA device memory; 
	 scalar parameters and return values on host
******************  cusdVUQ_ functions: **********************************
	 also act on vectors in CUDA device memory; 
	 scalar parameters and return values by address on device memory
************************************************************************/

#ifdef __cplusplus
    extern "C" {
#endif

/*****************************  Generation ******************************/

uqVector  __vf  cudaVUQ_vector( ui size );   /* allocates a vector on device memory */
uqVector  __vf  cudaVUQ_vector0( ui size );
 /* The following functions allocate device-accessible, "pinned" memory on the host.
	This memory is mapped onto the device memory space. The resulting device address is returned.
	The vector can be accessed either by its host address "hostPtr" e.g., VUQ_ramp( hostPtr, size, 0, 1 );
	or by its device address , e.g., cudaVUQ_ramp( devicePtr, size, 0, 1 );     */
uqVector  __vf  cudaVUQ_pinnedVector(  uqVector *hostPtr, ui size ); 
uqVector  __vf  cudaVUQ_pinnedVector0( uqVector *hostPtr, ui size );

/***************  Addressing single vector elements ******************/

uquad * __vcuf OVCUAPI cudaVUQ_Pelement( uqVector X, ui n );
uquad   __vcuf OVCUAPI cudaVUQ_element( uqVector X, ui n );
void    __vcuf OVCUAPI cudaVUQ_getElement( uquad *y, uqVector X, ui n );
void    __vcuf OVCUAPI cusdVUQ_getElement( uquad *d_y, uqVector X, ui n );
void    __vcuf OVCUAPI cudaVUQ_setElement( uqVector X, ui n, uquad C );
void    __vcuf OVCUAPI cusdVUQ_setElement( uqVector X, ui n, uquad *C );

/****************** Initialization  ******************************/

overror_t  __vcuf OVCUAPI   cudaVUQ_equ0( uqVector X, ui size );
overror_t  __vcuf OVCUAPI   cudaVUQ_equC( uqVector X, ui size, uquad C );
overror_t  __vcuf OVCUAPI   cusdVUQ_equC( uqVector X, ui size, uquad *C );
overror_t  __vcuf OVCUAPI   cudaVUQ_equV( uqVector Y, uqVector X, ui size ); /* copies from device to device */
overror_t  __vcuf OVCUAPI   cudaVUQ_equVhost( uqVector Y, uqVector X, ui size );  /* copies from host to device */
overror_t  __vcuf OVCUAPI   VUQ_equVdevice( uqVector Y, uqVector X, ui size );  /* copies from device to host */
overror_t  __vcuf OVCUAPI   cudaVUQ_ramp( uqVector X, ui size, uquad Start, quad Rise );
overror_t  __vcuf OVCUAPI   cusdVUQ_ramp( uqVector X, ui size, uquad *Start, quad *Rise );

/******  Linear Congruential random generator with Bays-Durham shuffle:  ***********
  Random series is generated on the CPU. State must be stored in host memory!
  seed!=0 --> initialization of state. seed==0 --> continue series from previous call with the same state. */
overror_t  __vcuf OVCUAPI  cudaVUQ_randomLC( uqVector X, ui size, long seed, uquad MinVal, uquad MaxVal, V_RANDOMLCSTATE *state );
overror_t  __vcuf OVCUAPI  cusdVUQ_randomLC( uqVector X, ui size, long seed, uquad *MinVal, uquad *MaxVal, V_RANDOMLCSTATE *state );
/**  simplified version: Series cannot be made continuous across calls: */
overror_t  __vcuf OVCUAPI  cudaVUQ_random( uqVector X, ui size, long seed, uquad MinVal, uquad MaxVal );
overror_t  __vcuf OVCUAPI  cusdVUQ_random( uqVector X, ui size, long seed, uquad *MinVal, uquad *MaxVal );

/**************  Data-type interconversions  **************************/

overror_t __vcuf OVCUAPI   cudaV_QItoUQ( uqVector Y, qiVector X, ui size );  /* signed-unsigned */
overror_t __vcuf OVCUAPI   cudaV_UQtoQI( qiVector Y, uqVector X, ui size );

overror_t __vcuf OVCUAPI   cudaV_UBtoUQ( uqVector Y, ubVector X, ui size );  /* up-conversion */
overror_t __vcuf OVCUAPI   cudaV_UStoUQ( uqVector Y, usVector X, ui size );
overror_t __vcuf OVCUAPI   cudaV_UtoUQ(  uqVector Y, uVector  X, ui size );
overror_t __vcuf OVCUAPI   cudaV_ULtoUQ( uqVector Y, ulVector X, ui size );

overror_t __vcuf OVCUAPI   cudaV_UQtoUB( ubVector Y, uqVector X, ui size ); /* down-conversion */
overror_t __vcuf OVCUAPI   cudaV_UQtoUS( usVector Y, uqVector X, ui size );
overror_t __vcuf OVCUAPI   cudaV_UQtoU(  uVector  Y, uqVector X, ui size );
overror_t __vcuf OVCUAPI   cudaV_UQtoUL( ulVector Y, uqVector X, ui size );

overror_t  __vcuf OVCUAPI   cudaV_UQtoF(  fVector Y, uqVector X, ui size );
overror_t  __vcuf OVCUAPI   cudaV_UQtoD(  dVector Y, uqVector X, ui size );


/************** Index-oriented manipulations ***************************/

overror_t  __vcuf OVCUAPI   cudaVUQ_reflect( uqVector X, ui size );
overror_t  __vcuf OVCUAPI   cudaVUQ_rev( uqVector Y, uqVector X, ui size );
overror_t  __vcuf OVCUAPI   cudaVUQ_rotate( uqVector Y, uqVector X, ui size, ssize_t pos );
overror_t  __vcuf OVCUAPI   cudaVUQ_rotate_buf( uqVector Y, uqVector X, ui size, ssize_t pos, uqVector Buf );
overror_t  __vcuf OVCUAPI   cudaVUQ_delete( uqVector X, ui size, ui pos );
overror_t  __vcuf OVCUAPI   cudaVUQ_insert( uqVector X, ui size, ui pos, uquad C );
overror_t  __vcuf OVCUAPI   cusdVUQ_insert( uqVector X, ui size, ui pos, uquad *C );
overror_t  __vcuf OVCUAPI   cudaVUQ_sort( uqVector Y, uqVector X, ui size, int dir );
overror_t  __vcuf OVCUAPI   cudaVUQ_sortind( uiVector Ind, uqVector X, ui size, int dir );

overror_t  __vcuf OVCUAPI   cudaVUQ_subvector( uqVector Y, ui sizey, uqVector X, ssize_t samp );
overror_t  __vcuf OVCUAPI   cudaVUQ_subvector_equC( uqVector Y, ui subsz, ui samp, uquad C );
overror_t  __vcuf OVCUAPI   cusdVUQ_subvector_equC( uqVector Y, ui subsz, ui samp, uquad *C );
overror_t  __vcuf OVCUAPI   cudaVUQ_subvector_equV( uqVector Y, ui subsz, ui samp, uqVector X );

overror_t  __vcuf OVCUAPI   cudaVUQ_indpick( uqVector Y, uiVector Ind, ui sizey, uqVector X );
overror_t  __vcuf OVCUAPI   cudaVUQ_indput(  uqVector Y, uqVector X, uiVector Ind, ui sizex );
overror_t  __vcuf OVCUAPI   cudaVUQ_searchC( ui *h_Ind, uqVector XTab, ui size, uquad C, int mode );
overror_t  __vcuf OVCUAPI   cusdVUQ_searchC( ui *d_Ind, uqVector XTab, ui size, uquad *C, int mode );
overror_t  __vcuf OVCUAPI   cudaVUQ_searchV( uiVector Ind, uqVector X, ui sizex, uqVector Tab, ui sizetab, int mode );

/********************   One-dimensional Vector Operations  ********/

overror_t  __vcuf OVCUAPI   cudaVUQ_sum( uquad *h_RetVal, uqVector X, ui size );
overror_t  __vcuf OVCUAPI   cudaVUQ_max( uquad *h_RetVal, uqVector X, ui size );
overror_t  __vcuf OVCUAPI   cudaVUQ_min( uquad *h_RetVal, uqVector X, ui size );
overror_t  __vcuf OVCUAPI   cudaVUQ_maxind( uquad *h_RetVal, ui *Ind, uqVector X, ui size );
overror_t  __vcuf OVCUAPI   cudaVUQ_minind( uquad *h_RetVal, ui *Ind, uqVector X, ui size );
overror_t  __vcuf OVCUAPI   cudaVUQ_fsum( double *h_RetVal, uqVector X, ui size );
overror_t  __vcuf OVCUAPI   cudaVUQ_mean( double *h_RetVal, uqVector X, ui size );
overror_t   __vcuf OVCUAPI   cudaVUQ_runsum( uqVector Y, uqVector X, ui size );
overror_t   __vcuf OVCUAPI   cudaVUQ_runmax( uqVector Y, uqVector X, ui size );
overror_t   __vcuf OVCUAPI   cudaVUQ_runmin( uqVector Y, uqVector X, ui size );

overror_t  __vcuf OVCUAPI   cusdVUQ_sum( uquad *d_RetVal, uqVector X, ui size );
overror_t  __vcuf OVCUAPI   cusdVUQ_max( uquad *d_RetVal, uqVector X, ui size );
overror_t  __vcuf OVCUAPI   cusdVUQ_min( uquad *d_RetVal, uqVector X, ui size );
overror_t  __vcuf OVCUAPI   cusdVUQ_maxind( uquad *d_RetVal, ui *Ind, uqVector X, ui size );
overror_t  __vcuf OVCUAPI   cusdVUQ_minind( uquad *d_RetVal, ui *Ind, uqVector X, ui size );
overror_t  __vcuf OVCUAPI   cusdVUQ_fsum( double *d_RetVal, uqVector X, ui size );
overror_t  __vcuf OVCUAPI   cusdVUQ_mean( double *d_RetVal, uqVector X, ui size );

int        __vcuf OVCUAPI   cudaVUQ_iselementC( uqVector Tab, ui size, uquad  C );
int        __vcuf OVCUAPI   cusdVUQ_iselementC( uqVector Tab, ui size, uquad  *C );
overror_t  __vcuf OVCUAPI   cudaVUQ_iselementV( ui *h_nFound, uqVector Y, uqVector X, ui sizex, uqVector Tab, ui sizetab );

overror_t  __vcuf OVCUAPI   cudaVUQ_distribution( ui *h_nOutside, uiVector Abund, uqVector Limits, ui nbins, uqVector X, ui sizex, int mode );
overror_t  __vcuf OVCUAPI   cusdVUQ_distribution( ui *d_nOutside, uiVector Abund, uqVector Limits, ui nbins, uqVector X, ui sizex, int mode );

/***************************  Input and Output *****************************
	The input/output functions involve memory transfers from device
	to host memory or vice versa. The generic cudaVUQ_input/output functions
	allocate their own host buffers, whereas the cudaVUQ_xxx_buf functions
	take a user-supplied buffer h_Wk and are much more efficient.          */

overror_t  __vf    cudaVUQ_fprint( FILE *stream, uqVector X, ui size, unsigned nperline, unsigned linewidth );
overror_t  __vf    cudaVUQ_cprint( uqVector X, ui size, unsigned nperline );
#define       cudaVUQ_print( x, sz, npl )  cudaVUQ_fprint( stdout, x, sz, npl, 80 )
overror_t  __vf    cudaVUQ_fprint_buf( FILE *stream, uqVector d_X, ui size, unsigned nperline, unsigned linewidth, uqVector h_Wk );
overror_t  __vf    cudaVUQ_cprint_buf( uqVector d_X, ui size, unsigned nperline, uqVector h_Wk );
#define       cudaVUQ_print_buf( d_x, sz, npl, h_Wk )  cudaVUQ_fprint_buf( stdout, d_x, sz, npl, 80, h_Wk )
 /*  cudaVUQ_print, cudaVUQ_cprint are usable only for console applications!  */
overror_t  __vf    cudaVUQ_write( FILE *stream, uqVector X, ui size  );
overror_t  __vf    cudaVUQ_read( uqVector X, ui size, FILE *stream );
overror_t  __vf    cudaVUQ_write_buf( FILE *stream, uqVector d_X, ui size, uqVector h_Wk );
overror_t  __vf    cudaVUQ_read_buf( uqVector d_X, ui size, FILE *stream, uqVector h_Wk );
                     /* cudaVUQ_write, cudaVUQ_read in ascii format */
overror_t  __vf     cudaVUQ_store( FILE *stream, uqVector X, ui size );
overror_t  __vf     cudaVUQ_recall( uqVector X, ui size, FILE *stream );
overror_t  __vf     cudaVUQ_store_buf( FILE *stream, uqVector d_X, ui size, uqVector h_Wk );
overror_t  __vf     cudaVUQ_recall_buf( uqVector d_X, ui size, FILE *stream, uqVector h_Wk );
                     /* cudaVUQ_store, cudaVUQ_recall in binary format */


#ifdef __cplusplus
}  // end of extern "C"
#endif

/******************  VUQcu_ functions: **********************************
	act on host memory, using the CUDA device for processing
************************************************************************/


#ifdef __cplusplus
    extern "C" {
#endif

/****************** Initialization  ******************************/

void  __vcuf OVCUAPI   VUQcu_equ0( uqVector X, ui size );
void  __vcuf OVCUAPI   VUQcu_equC( uqVector X, ui size, uquad C );
void  __vcuf OVCUAPI   VUQcu_equV( uqVector Y, uqVector X, ui size ); /* copies from device to device */
void  __vcuf OVCUAPI   VUQcu_ramp( uqVector X, ui size, uquad Start, quad Rise );
/* no Vcu_random functions: random generation runs on CPU anyway */


/**************  Data-type interconversions  **************************/

void __vcuf OVCUAPI   Vcu_QItoUQ( uqVector Y, qiVector X, ui size );  /* signed-unsigned */
void __vcuf OVCUAPI   Vcu_UQtoQI( qiVector Y, uqVector X, ui size );

void __vcuf OVCUAPI   Vcu_UBtoUQ( uqVector Y, ubVector X, ui size );  /* up-conversion */
void __vcuf OVCUAPI   Vcu_UStoUQ( uqVector Y, usVector X, ui size );
void __vcuf OVCUAPI   Vcu_UtoUQ(  uqVector Y, uVector  X, ui size );
void __vcuf OVCUAPI   Vcu_ULtoUQ( uqVector Y, ulVector X, ui size );

void __vcuf OVCUAPI   Vcu_UQtoUB( ubVector Y, uqVector X, ui size ); /* down-conversion */
void __vcuf OVCUAPI   Vcu_UQtoUS( usVector Y, uqVector X, ui size );
void __vcuf OVCUAPI   Vcu_UQtoU(  uVector  Y, uqVector X, ui size );
void __vcuf OVCUAPI   Vcu_UQtoUL( ulVector Y, uqVector X, ui size );

void  __vcuf OVCUAPI   Vcu_UQtoF(  fVector Y, uqVector X, ui size );
void  __vcuf OVCUAPI   Vcu_UQtoD(  dVector Y, uqVector X, ui size );


/************** Index-oriented manipulations ***************************/

void  __vcuf OVCUAPI   VUQcu_reflect( uqVector X, ui size );
void  __vcuf OVCUAPI   VUQcu_rev( uqVector Y, uqVector X, ui size );
void  __vcuf OVCUAPI   VUQcu_rotate( uqVector Y, uqVector X, ui size, ssize_t pos );
void  __vcuf OVCUAPI   VUQcu_rotate_buf( uqVector Y, uqVector X, ui size, ssize_t pos, uqVector Buf );
void  __vcuf OVCUAPI   VUQcu_delete( uqVector X, ui size, ui pos );
void  __vcuf OVCUAPI   VUQcu_insert( uqVector X, ui size, ui pos, uquad C );
void  __vcuf OVCUAPI   VUQcu_sort( uqVector Y, uqVector X, ui size, int dir );
void  __vcuf OVCUAPI   VUQcu_sortind( uiVector Ind, uqVector X, ui size, int dir );

void  __vcuf OVCUAPI   VUQcu_subvector( uqVector Y, ui sizey, uqVector X, ssize_t samp );
void  __vcuf OVCUAPI   VUQcu_subvector_equC( uqVector Y, ui subsz, ui samp, uquad C );
void  __vcuf OVCUAPI   VUQcu_subvector_equV( uqVector Y, ui subsz, ui samp, uqVector X );

  /* no V?cu_indpick, V?cu_indput possible! */
ui    __vcuf OVCUAPI   VUQcu_searchC( uqVector XTab, ui size, uquad C, int mode );
void  __vcuf OVCUAPI   VUQcu_searchV( uiVector Ind, uqVector X, ui sizex, uqVector Tab, ui sizetab, int mode );

/********************   One-dimensional Vector Operations  ********/

uquad  __vcuf OVCUAPI   VUQcu_sum( uqVector X, ui size );
uquad  __vcuf OVCUAPI   VUQcu_max( uqVector X, ui size );
uquad  __vcuf OVCUAPI   VUQcu_min( uqVector X, ui size );
uquad  __vcuf OVCUAPI   VUQcu_maxind( ui *Ind, uqVector X, ui size );
uquad  __vcuf OVCUAPI   VUQcu_minind( ui *Ind, uqVector X, ui size );
double __vcuf OVCUAPI   VUQcu_fsum( uqVector X, ui size );
double __vcuf OVCUAPI   VUQcu_mean( uqVector X, ui size );
void   __vcuf OVCUAPI   VUQcu_runsum( uqVector Y, uqVector X, ui size );
void   __vcuf OVCUAPI   VUQcu_runmax( uqVector Y, uqVector X, ui size );
void   __vcuf OVCUAPI   VUQcu_runmin( uqVector Y, uqVector X, ui size );

int    __vcuf OVCUAPI   VUQcu_iselementC( uqVector Tab, ui size, uquad  C );
ui     __vcuf OVCUAPI   VUQcu_iselementV( uqVector Y, uqVector X, ui sizex, uqVector Tab, ui sizetab );

ui     __vcuf OVCUAPI   VUQcu_distribution( uiVector Abund, uqVector Limits, ui nbins, uqVector X, ui sizex, int mode );

#ifdef __cplusplus
}  // end of extern "C"
#endif

#endif   /*  __CUDAVUQSTD_H    */
#endif   /*  _WIN64 */