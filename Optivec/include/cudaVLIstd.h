/*  cudaVLIstd.h

  vector management functions for data type "long".

  Copyright (c) 1996-2017 by OptiCode - Dr. Martin Sander Software Dev.
  All Rights Reserved.
*/

#ifndef __CUDAVLISTD_H
#define __CUDAVLISTD_H

#if !defined( __CUDAVECLIB_H )
   #include <cudaVecLib.h>
#endif

/******************  cudaVLI_ functions: **********************************
	 act on vectors in CUDA device memory; 
	 scalar parameters and return values on host
******************  cusdVLI_ functions: **********************************
	 also act on vectors in CUDA device memory; 
	 scalar parameters and return values by address on device memory
************************************************************************/

#ifdef __cplusplus
   extern "C" {
#endif

/**********************  Generation  ************************************/

liVector  __vf   cudaVLI_vector( ui size );   /* allocates a vector on device memory */
liVector  __vf   cudaVLI_vector0( ui size );
 /* The following functions allocate device-accessible, "pinned" memory on the host.
	This memory is mapped onto the device memory space. The resulting device address is returned.
	The vector can be accessed either by its host address "hostPtr" e.g., VLI_ramp( hostPtr, size, 0, 1 );
	or by its device address , e.g., cudaVLI_ramp( devicePtr, size, 0, 1 );     */
liVector  __vf   cudaVLI_pinnedVector(  liVector *hostPtr, ui size ); 
liVector  __vf   cudaVLI_pinnedVector0( liVector *hostPtr, ui size );

/***************  Addressing single vector elements ******************/

long * __vcuf  OVCUAPI cudaVLI_Pelement( liVector X, ui n );
long   __vcuf  OVCUAPI cudaVLI_element( liVector X, ui n );
void   __vcuf  OVCUAPI cudaVLI_getElement( long *y, liVector X, ui n );
void   __vcuf  OVCUAPI cusdVLI_getElement( long *d_y, liVector X, ui n );
void   __vcuf  OVCUAPI cudaVLI_setElement( liVector X, ui n, long C );
void   __vcuf  OVCUAPI cusdVLI_setElement( liVector X, ui n, long *C );

/*********************** Initialization  ******************************/

overror_t  __vcuf OVCUAPI   cudaVLI_equ0( liVector X, ui size );
overror_t  __vcuf OVCUAPI   cudaVLI_equC( liVector X, ui size, long C );
overror_t  __vcuf OVCUAPI   cusdVLI_equC( liVector X, ui size, long *C );
overror_t  __vcuf OVCUAPI   cudaVLI_equV( liVector Y, liVector X, ui size ); /* copies from device to device */
overror_t  __vcuf           cudaVLI_equVhost( liVector Y, liVector X, ui size );  /* copies from host to device */
overror_t  __vcuf           VLI_equVdevice( liVector Y, liVector X, ui size );  /* copies from device to host */
overror_t  __vcuf OVCUAPI   cudaVLI_ramp( liVector X, ui size, long Start, long Rise );
overror_t  __vcuf OVCUAPI   cusdVLI_ramp( liVector X, ui size, long *Start, long *Rise );

/******  Linear Congruential random generator with Bays-Durham shuffle:  ***********
  Random series is generated on the CPU. State must be stored in host memory!
  seed!=0 --> initialization of state. seed==0 --> continue series from previous call with the same state. */
overror_t  __vcuf OVCUAPI  cudaVLI_randomLC( liVector X, ui size, long seed, long MinVal, long MaxVal, V_RANDOMLCSTATE *state );
overror_t  __vcuf OVCUAPI  cusdVLI_randomLC( liVector X, ui size, long seed, long *MinVal, long *MaxVal, V_RANDOMLCSTATE *state );
/**  simplified version: Series cannot be made continuous across calls: */
overror_t  __vcuf OVCUAPI  cudaVLI_random( liVector X, ui size, long seed, long MinVal, long MaxVal );
overror_t  __vcuf OVCUAPI  cusdVLI_random( liVector X, ui size, long seed, long *MinVal, long *MaxVal );


/************** Data-type interconversions  ***************************/

overror_t  __vcuf OVCUAPI   cudaV_BItoLI( liVector Y, biVector X, ui size );  /* up-conversion */
overror_t  __vcuf OVCUAPI   cudaV_SItoLI( liVector Y, siVector X, ui size );
overror_t  __vcuf OVCUAPI   cudaV_ItoLI(  liVector Y, iVector  X, ui size );
overror_t  __vcuf OVCUAPI   cudaV_LItoQI( qiVector Y, liVector X, ui size );

overror_t  __vcuf OVCUAPI   cudaV_LItoBI(  biVector Y, liVector X, ui size ); /* down-conversion */
overror_t  __vcuf OVCUAPI   cudaV_LItoUL( ulVector Y, liVector X, ui size );
overror_t  __vcuf OVCUAPI   cudaV_ULtoLI( liVector Y, ulVector X, ui size );
overror_t  __vcuf OVCUAPI   cudaV_LItoSI( siVector Y, liVector X, ui size );
overror_t  __vcuf OVCUAPI   cudaV_LItoI(  iVector  Y, liVector X, ui size );
overror_t  __vcuf OVCUAPI   cudaV_QItoLI( liVector Y, qiVector X, ui size );

overror_t  __vcuf OVCUAPI   cudaV_LItoF(  fVector Y, liVector X, ui size );
overror_t  __vcuf OVCUAPI   cudaV_LItoD(  dVector Y, liVector X, ui size );


/************** Index-oriented manipulations ***************************/

overror_t  __vcuf OVCUAPI   cudaVLI_reflect( liVector X, ui size );
overror_t  __vcuf OVCUAPI   cudaVLI_rev( liVector Y, liVector X, ui size );
overror_t  __vcuf OVCUAPI   cudaVLI_rotate( liVector Y, liVector X, ui size, ssize_t pos );
overror_t  __vcuf OVCUAPI   cudaVLI_rotate_buf( liVector Y, liVector X, ui size, ssize_t pos, liVector Buf );
overror_t  __vcuf OVCUAPI   cudaVLI_delete( liVector X, ui size, ui pos );
overror_t  __vcuf OVCUAPI   cudaVLI_insert( liVector X, ui size, ui pos, long C );
overror_t  __vcuf OVCUAPI   cusdVLI_insert( liVector X, ui size, ui pos, long *C );
overror_t  __vcuf OVCUAPI   cudaVLI_sort( liVector Y, liVector X, ui size, int dir );
overror_t  __vcuf OVCUAPI   cudaVLI_sortind( uiVector Ind, liVector X, ui size, int dir );

overror_t  __vcuf OVCUAPI   cudaVLI_subvector( liVector Y, ui sizey, liVector X, ssize_t samp );
overror_t  __vcuf OVCUAPI   cudaVLI_subvector_equC( liVector Y, ui subsz, ui samp, long C );
overror_t  __vcuf OVCUAPI   cusdVLI_subvector_equC( liVector Y, ui subsz, ui samp, long *C );
overror_t  __vcuf OVCUAPI   cudaVLI_subvector_equV( liVector Y, ui subsz, ui samp, liVector X );
overror_t  __vcuf OVCUAPI   cudaVLI_indpick( liVector Y, uiVector Ind, ui sizey, liVector X );
overror_t  __vcuf OVCUAPI   cudaVLI_indput(  liVector Y, liVector X, uiVector Ind, ui sizex );
overror_t  __vcuf OVCUAPI   cudaVLI_searchC( ui *h_Ind, liVector XTab, ui size, long C, int mode );
overror_t  __vcuf OVCUAPI   cusdVLI_searchC( ui *d_Ind, liVector XTab, ui size, long *C, int mode );
overror_t  __vcuf OVCUAPI   cudaVLI_searchV( uiVector Ind, liVector X, ui sizex, liVector Tab, ui sizetab, int mode );

/********************   One-dimensional Vector Operations  ********/

overror_t  __vcuf OVCUAPI   cudaVLI_sum( long *h_RetVal, liVector X, ui size );
overror_t  __vcuf OVCUAPI   cudaVLI_max( long *h_RetVal, liVector X, ui size );
overror_t  __vcuf OVCUAPI   cudaVLI_min( long *h_RetVal, liVector X, ui size );
overror_t  __vcuf OVCUAPI   cudaVLI_maxind( long *h_RetVal, ui *Ind, liVector X, ui size );
overror_t  __vcuf OVCUAPI   cudaVLI_minind( long *h_RetVal, ui *Ind, liVector X, ui size );
overror_t  __vcuf OVCUAPI   cudaVLI_fsum( double *h_RetVal, liVector X, ui size );
overror_t  __vcuf OVCUAPI   cudaVLI_mean( double *h_RetVal, liVector X, ui size );
overror_t   __vcuf OVCUAPI   cudaVLI_runsum( liVector Y, liVector X, ui size );
overror_t   __vcuf OVCUAPI   cudaVLI_runmax( liVector Y, liVector X, ui size );
overror_t   __vcuf OVCUAPI   cudaVLI_runmin( liVector Y, liVector X, ui size );

overror_t  __vcuf OVCUAPI   cusdVLI_sum( long *d_RetVal, liVector X, ui size );
overror_t  __vcuf OVCUAPI   cusdVLI_max( long *d_RetVal, liVector X, ui size );
overror_t  __vcuf OVCUAPI   cusdVLI_min( long *d_RetVal, liVector X, ui size );
overror_t  __vcuf OVCUAPI   cusdVLI_maxind( long *d_RetVal, ui *Ind, liVector X, ui size );
overror_t  __vcuf OVCUAPI   cusdVLI_minind( long *d_RetVal, ui *Ind, liVector X, ui size );
overror_t  __vcuf OVCUAPI   cusdVLI_fsum( double *d_RetVal, liVector X, ui size );
overror_t  __vcuf OVCUAPI   cusdVLI_mean( double *d_RetVal, liVector X, ui size );

int        __vcuf OVCUAPI   cudaVLI_iselementC( liVector Tab, ui size, long C );
int        __vcuf OVCUAPI   cusdVLI_iselementC( liVector Tab, ui size, long *C );
overror_t  __vcuf OVCUAPI   cudaVLI_iselementV( ui *h_nFound, liVector Y, liVector X, ui sizex, liVector Tab, ui sizetab );

overror_t  __vcuf OVCUAPI   cudaVLI_distribution( ui *h_nOutside, uiVector Abund, liVector Limits, ui nbins, liVector X, ui sizex, int mode );
overror_t  __vcuf OVCUAPI   cusdVLI_distribution( ui *d_nOutside, uiVector Abund, liVector Limits, ui nbins, liVector X, ui sizex, int mode );

/***************************  Input and Output *****************************
	The input/output functions involve memory transfers from device
	to host memory or vice versa. The generic cudaVLI_input/output functions
	allocate their own host buffers, whereas the cudaVLI_xxx_buf functions
	take a user-supplied buffer h_Wk and are much more efficient.          */

overror_t  __vf    cudaVLI_fprint( FILE *stream, liVector X, ui size, unsigned nperline, unsigned linewidth );
overror_t  __vf    cudaVLI_cprint( liVector X, ui size, unsigned nperline );
#define       cudaVLI_print( x, sz, npl )  cudaVLI_fprint( stdout, x, sz, npl, 80 )
overror_t  __vf    cudaVLI_fprint_buf( FILE *stream, liVector d_X, ui size, unsigned nperline, unsigned linewidth, liVector h_Wk );
overror_t  __vf    cudaVLI_cprint_buf( liVector d_X, ui size, unsigned nperline, liVector h_Wk );
#define       cudaVLI_print_buf( d_x, sz, npl, h_Wk )  cudaVLI_fprint_buf( stdout, d_x, sz, npl, 80, h_Wk )
 /*  cudaVLI_print, cudaVLI_cprint are usable only for console applications!  */
overror_t  __vf    cudaVLI_write( FILE *stream, liVector X, ui size  );
overror_t  __vf    cudaVLI_read( liVector X, ui size, FILE *stream );
overror_t  __vf    cudaVLI_write_buf( FILE *stream, liVector d_X, ui size, liVector h_Wk );
overror_t  __vf    cudaVLI_read_buf( liVector d_X, ui size, FILE *stream, liVector h_Wk );
                     /* cudaVLI_write, cudaVLI_read in ascii format */
overror_t  __vf     cudaVLI_store( FILE *stream, liVector X, ui size );
overror_t  __vf     cudaVLI_recall( liVector X, ui size, FILE *stream );
overror_t  __vf     cudaVLI_store_buf( FILE *stream, liVector d_X, ui size, liVector h_Wk );
overror_t  __vf     cudaVLI_recall_buf( liVector d_X, ui size, FILE *stream, liVector h_Wk );
                     /* cudaVLI_store, cudaVLI_recall in binary format */


#ifdef __cplusplus
}  // end of extern "C"
#endif

/******************  VLIcu_ functions: **********************************
	act on host memory, using the CUDA device for processing
************************************************************************/


#ifdef __cplusplus
   extern "C" {
#endif
/*********************** Initialization  ******************************/

void  __vcuf OVCUAPI   VLIcu_equ0( liVector X, ui size );
void  __vcuf OVCUAPI   VLIcu_equC( liVector X, ui size, long C );
void  __vcuf OVCUAPI   VLIcu_equV( liVector Y, liVector X, ui size ); /* copies from device to device */
void  __vcuf OVCUAPI   VLIcu_ramp( liVector X, ui size, long Start, long Rise );
/* no Vcu_random functions: random generation runs on CPU anyway */


/************** Data-type interconversions  ***************************/

void  __vcuf OVCUAPI   Vcu_BItoLI( liVector Y, biVector X, ui size );  /* up-conversion */
void  __vcuf OVCUAPI   Vcu_SItoLI( liVector Y, siVector X, ui size );
void  __vcuf OVCUAPI   Vcu_ItoLI(  liVector Y, iVector  X, ui size );
void  __vcuf OVCUAPI   Vcu_LItoQI( qiVector Y, liVector X, ui size );

void  __vcuf OVCUAPI   Vcu_LItoBI(  biVector Y, liVector X, ui size ); /* down-conversion */
void  __vcuf OVCUAPI   Vcu_LItoUL( ulVector Y, liVector X, ui size );
void  __vcuf OVCUAPI   Vcu_ULtoLI( liVector Y, ulVector X, ui size );
void  __vcuf OVCUAPI   Vcu_LItoSI( siVector Y, liVector X, ui size );
void  __vcuf OVCUAPI   Vcu_LItoI(  iVector  Y, liVector X, ui size );
void  __vcuf OVCUAPI   Vcu_QItoLI( liVector Y, qiVector X, ui size );

void  __vcuf OVCUAPI   Vcu_LItoF(  fVector Y, liVector X, ui size );
void  __vcuf OVCUAPI   Vcu_LItoD(  dVector Y, liVector X, ui size );


/************** Index-oriented manipulations ***************************/

void  __vcuf OVCUAPI   VLIcu_reflect( liVector X, ui size );
void  __vcuf OVCUAPI   VLIcu_rev( liVector Y, liVector X, ui size );
void  __vcuf OVCUAPI   VLIcu_rotate( liVector Y, liVector X, ui size, ssize_t pos );
void  __vcuf OVCUAPI   VLIcu_rotate_buf( liVector Y, liVector X, ui size, ssize_t pos, liVector Buf );
void  __vcuf OVCUAPI   VLIcu_delete( liVector X, ui size, ui pos );
void  __vcuf OVCUAPI   VLIcu_insert( liVector X, ui size, ui pos, long C );
void  __vcuf OVCUAPI   VLIcu_sort( liVector Y, liVector X, ui size, int dir );
void  __vcuf OVCUAPI   VLIcu_sortind( uiVector Ind, liVector X, ui size, int dir );

void  __vcuf OVCUAPI   VLIcu_subvector( liVector Y, ui sizey, liVector X, ssize_t samp );
void  __vcuf OVCUAPI   VLIcu_subvector_equC( liVector Y, ui subsz, ui samp, long C );
void  __vcuf OVCUAPI   VLIcu_subvector_equV( liVector Y, ui subsz, ui samp, liVector X );
  /* no V?cu_indpick, V?cu_indput possible! */
ui    __vcuf OVCUAPI   VLIcu_searchC( liVector XTab, ui size, long C, int mode );
void  __vcuf OVCUAPI   VLIcu_searchV( uiVector Ind, liVector X, ui sizex, liVector Tab, ui sizetab, int mode );

/********************   One-dimensional Vector Operations  ********/

long   __vcuf OVCUAPI   VLIcu_sum( liVector X, ui size );
long   __vcuf OVCUAPI   VLIcu_max( liVector X, ui size );
long   __vcuf OVCUAPI   VLIcu_min( liVector X, ui size );
long   __vcuf OVCUAPI   VLIcu_maxind( ui *Ind, liVector X, ui size );
long   __vcuf OVCUAPI   VLIcu_minind( ui *Ind, liVector X, ui size );
double __vcuf OVCUAPI   VLIcu_fsum( liVector X, ui size );
double __vcuf OVCUAPI   VLIcu_mean( liVector X, ui size );
void   __vcuf OVCUAPI   VLIcu_runsum( liVector Y, liVector X, ui size );
void   __vcuf OVCUAPI   VLIcu_runmax( liVector Y, liVector X, ui size );
void   __vcuf OVCUAPI   VLIcu_runmin( liVector Y, liVector X, ui size );

int    __vcuf OVCUAPI   VLIcu_iselementC( liVector Tab, ui size, long C );
ui     __vcuf OVCUAPI   VLIcu_iselementV( liVector Y, liVector X, ui sizex, liVector Tab, ui sizetab );

ui     __vcuf OVCUAPI   VLIcu_distribution( uiVector Abund, liVector Limits, ui nbins, liVector X, ui sizex, int mode );

#ifdef __cplusplus
}  // end of extern "C"
#endif

#endif   /*  __CUDAVLISTD_H    */
