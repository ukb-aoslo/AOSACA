/*  cudaVIstd.h

  vector management functions for data type "int".

  Copyright (c) 1996-2017 by OptiCode - Dr. Martin Sander Software Dev.
  All Rights Reserved.
*/

#ifndef __CUDAVISTD_H
#define __CUDAVISTD_H

#if !defined( __CUDAVECLIB_H )
   #include <cudaVecLib.h>
#endif

/******************  cudaVI_ functions: **********************************
	 act on vectors in CUDA device memory; 
	 scalar parameters and return values on host
******************  cusdVI_ functions: **********************************
	 also act on vectors in CUDA device memory; 
	 scalar parameters and return values by address on device memory
************************************************************************/

#ifdef __cplusplus
   extern "C" {
#endif

/***********  Generation of Arrays and Vectors  *************************/

iVector  __vf  cudaVI_vector( ui size );   /* allocates a vector on device memory */
iVector  __vf  cudaVI_vector0( ui size );
 /* The following functions allocate device-accessible, "pinned" memory on the host.
	This memory is mapped onto the device memory space. The resulting device address is returned.
	The vector can be accessed either by its host address "hostPtr" e.g., VI_ramp( hostPtr, size, 0, 1 );
	or by its device address , e.g., cudaVI_ramp( devicePtr, size, 0, 1 );     */
iVector  __vf  cudaVI_pinnedVector(  iVector *hostPtr, ui size ); 
iVector  __vf  cudaVI_pinnedVector0( iVector *hostPtr, ui size );

/***************  Addressing single vector elements ******************/

int * __vcuf OVCUAPI cudaVI_Pelement( iVector X, ui n );
int   __vcuf OVCUAPI cudaVI_element( iVector X, ui n );
void  __vcuf OVCUAPI cudaVI_getElement( int *y, iVector X, ui n );
void  __vcuf OVCUAPI cusdVI_getElement( int *d_y, iVector X, ui n );
void  __vcuf OVCUAPI cudaVI_setElement( iVector X, ui n, int C );
void  __vcuf OVCUAPI cusdVI_setElement( iVector X, ui n, int *C );

/****************** Initialization  ******************************/

overror_t  __vcuf OVCUAPI   cudaVI_equ0( iVector X, ui size );
overror_t  __vcuf OVCUAPI   cudaVI_equC( iVector X, ui size, int C );
overror_t  __vcuf OVCUAPI   cusdVI_equC( iVector X, ui size, int *C );
overror_t  __vcuf OVCUAPI   cudaVI_equV( iVector Y, iVector X, ui size ); /* copies from device to device */
overror_t  __vcuf OVCUAPI   cudaVI_equVhost( iVector Y, iVector X, ui size );  /* copies from host to device */
overror_t  __vcuf OVCUAPI   VI_equVdevice( iVector Y, iVector X, ui size );  /* copies from device to host */
overror_t  __vcuf OVCUAPI   cudaVI_ramp( iVector X, ui size, int Start, int Rise );
overror_t  __vcuf OVCUAPI   cusdVI_ramp( iVector X, ui size, int *Start, int *Rise );

/******  Linear Congruential random generator with Bays-Durham shuffle:  ***********
  Random series is generated on the CPU. State must be stored in host memory!
  seed!=0 --> initialization of state. seed==0 --> continue series from previous call with the same state. */
overror_t  __vcuf OVCUAPI  cudaVI_randomLC( iVector X, ui size, long seed, int MinVal, int MaxVal, V_RANDOMLCSTATE *state );
overror_t  __vcuf OVCUAPI  cusdVI_randomLC( iVector X, ui size, long seed, int *MinVal, int *MaxVal, V_RANDOMLCSTATE *state );
/**  simplified version: Series cannot be made continuous across calls: */
overror_t  __vcuf OVCUAPI  cudaVI_random( iVector X, ui size, long seed, int MinVal, int MaxVal );
overror_t  __vcuf OVCUAPI  cusdVI_random( iVector X, ui size, long seed, int *MinVal, int *MaxVal );


/************** Data-type interconversions  ***************************/

overror_t  __vcuf OVCUAPI   cudaV_BItoI(  iVector  Y, biVector X, ui size );  /* up-conversion */
overror_t  __vcuf OVCUAPI   cudaV_SItoI(  iVector  Y, siVector X, ui size );
overror_t  __vcuf OVCUAPI   cudaV_ItoLI(  liVector Y, iVector  X, ui size );
overror_t  __vcuf OVCUAPI   cudaV_ItoQI(  qiVector Y, iVector  X, ui size );

overror_t  __vcuf OVCUAPI   cudaV_ItoBI(  biVector Y, iVector  X, ui size ); /* down-conversion */
overror_t  __vcuf OVCUAPI   cudaV_ItoU( uVector Y, iVector X, ui size );
overror_t  __vcuf OVCUAPI   cudaV_UtoI( iVector Y, uVector X, ui size );
overror_t  __vcuf OVCUAPI   cudaV_ItoSI( siVector Y, iVector  X, ui size );
overror_t  __vcuf OVCUAPI   cudaV_LItoI( iVector  Y, liVector X, ui size );
overror_t  __vcuf OVCUAPI   cudaV_QItoI( iVector  Y, qiVector X, ui size );

overror_t  __vcuf OVCUAPI   cudaV_ItoF(   fVector Y, iVector  X, ui size );
overror_t  __vcuf OVCUAPI   cudaV_ItoD(   dVector Y, iVector  X, ui size );

/************** Index-oriented manipulations ***************************/

overror_t  __vcuf OVCUAPI   cudaVI_reflect( iVector X, ui size );
overror_t  __vcuf OVCUAPI   cudaVI_rev( iVector Y, iVector X, ui size );
overror_t  __vcuf OVCUAPI   cudaVI_rotate( iVector Y, iVector X, ui size, ssize_t pos );
overror_t  __vcuf OVCUAPI   cudaVI_rotate_buf( iVector Y, iVector X, ui size, ssize_t pos, iVector Buf );

overror_t  __vcuf OVCUAPI   cudaVI_delete( iVector X, ui size, ui pos );
overror_t  __vcuf OVCUAPI   cudaVI_insert( iVector X, ui size, ui pos, int C );
overror_t  __vcuf OVCUAPI   cusdVI_insert( iVector X, ui size, ui pos, int *C );
overror_t  __vcuf OVCUAPI   cudaVI_sort( iVector Y, iVector X, ui size, int dir );
overror_t  __vcuf OVCUAPI   cudaVI_sortind( uiVector Ind, iVector X, ui size, int dir );

overror_t  __vcuf OVCUAPI   cudaVI_subvector( iVector Y, ui sizey, iVector X, ssize_t samp );
overror_t  __vcuf OVCUAPI   cudaVI_subvector_equC( iVector Y, ui subsz, ui samp, int C );
overror_t  __vcuf OVCUAPI   cusdVI_subvector_equC( iVector Y, ui subsz, ui samp, int *C );
overror_t  __vcuf OVCUAPI   cudaVI_subvector_equV( iVector Y, ui subsz, ui samp, iVector X );
overror_t  __vcuf OVCUAPI   cudaVI_indpick( iVector Y, uiVector Ind, ui sizey, iVector X );
overror_t  __vcuf OVCUAPI   cudaVI_indput(  iVector Y, iVector X, uiVector Ind, ui sizex );
overror_t  __vcuf OVCUAPI   cudaVI_searchC( ui *h_Ind, iVector XTab, ui size, int C, int mode );
overror_t  __vcuf OVCUAPI   cusdVI_searchC( ui *d_Ind, iVector XTab, ui size, int *C, int mode );
overror_t  __vcuf OVCUAPI   cudaVI_searchV( uiVector Ind, iVector X, ui sizex, iVector Tab, ui sizetab, int mode );

/********************   One-dimensional Vector Operations  ********/

overror_t  __vcuf OVCUAPI   cudaVI_sum( int *h_RetVal, iVector X, ui size );
overror_t  __vcuf OVCUAPI   cudaVI_max( int *h_RetVal, iVector X, ui size );
overror_t  __vcuf OVCUAPI   cudaVI_min( int *h_RetVal, iVector X, ui size );
overror_t  __vcuf OVCUAPI   cudaVI_maxind( int *h_RetVal, ui *Ind, iVector X, ui size );
overror_t  __vcuf OVCUAPI   cudaVI_minind( int *h_RetVal, ui *Ind, iVector X, ui size );
overror_t  __vcuf OVCUAPI   cudaVI_fsum( double *h_RetVal, iVector X, ui size );
overror_t  __vcuf OVCUAPI   cudaVI_mean( double *h_RetVal, iVector X, ui size );

overror_t  __vcuf OVCUAPI   cusdVI_sum( int *d_RetVal, iVector X, ui size );
overror_t  __vcuf OVCUAPI   cusdVI_max( int *d_RetVal, iVector X, ui size );
overror_t  __vcuf OVCUAPI   cusdVI_min( int *d_RetVal, iVector X, ui size );
overror_t  __vcuf OVCUAPI   cusdVI_maxind( int *d_RetVal, ui *Ind, iVector X, ui size );
overror_t  __vcuf OVCUAPI   cusdVI_minind( int *d_RetVal, ui *Ind, iVector X, ui size );
overror_t  __vcuf OVCUAPI   cusdVI_fsum( double *d_RetVal, iVector X, ui size );
overror_t  __vcuf OVCUAPI   cusdVI_mean( double *d_RetVal, iVector X, ui size );

overror_t   __vcuf OVCUAPI   cudaVI_runsum( iVector Y, iVector X, ui size );
overror_t   __vcuf OVCUAPI   cudaVI_runmax( iVector Y, iVector X, ui size );
overror_t   __vcuf OVCUAPI   cudaVI_runmin( iVector Y, iVector X, ui size );

int       __vcuf OVCUAPI   cudaVI_iselementC( iVector Tab, ui size, int  C );
int       __vcuf OVCUAPI   cusdVI_iselementC( iVector Tab, ui size, int  *C );
overror_t __vcuf OVCUAPI   cudaVI_iselementV( ui *h_nFound, iVector Y, iVector X, ui sizex, iVector Tab, ui sizetab );

overror_t  __vcuf OVCUAPI   cudaVI_distribution( ui *h_nOutside, uiVector Abund, iVector Limits, ui nbins, iVector X, ui sizex, int mode );
overror_t  __vcuf OVCUAPI   cusdVI_distribution( ui *d_nOutside, uiVector Abund, iVector Limits, ui nbins, iVector X, ui sizex, int mode );

/***************************  Input and Output *****************************
	The input/output functions involve memory transfers from device
	to host memory or vice versa. The generic cudaVF_input/output functions
	allocate their own host buffers, whereas the cudaVI_xxx_buf functions
	take a user-supplied buffer h_Wk and are much more efficient.          */

overror_t  __vf    cudaVI_fprint( FILE *stream, iVector X, ui size, unsigned nperline, unsigned linewidth );
overror_t  __vf    cudaVI_cprint( iVector X, ui size, unsigned nperline );
#define       cudaVI_print( x, sz, npl )  cudaVI_fprint( stdout, x, sz, npl, 80 )
overror_t  __vf    cudaVI_fprint_buf( FILE *stream, iVector d_X, ui size, unsigned nperline, unsigned linewidth, iVector h_Wk );
overror_t  __vf    cudaVI_cprint_buf( iVector d_X, ui size, unsigned nperline, iVector h_Wk );
#define       cudaVI_print_buf( d_x, sz, npl, h_Wk )  cudaVI_fprint_buf( stdout, d_x, sz, npl, 80, h_Wk )
 /*  cudaVI_print, cudaVI_cprint are usable only for console applications!  */
overror_t  __vf    cudaVI_write( FILE *stream, iVector X, ui size  );
overror_t  __vf    cudaVI_read( iVector X, ui size, FILE *stream );
overror_t  __vf    cudaVI_write_buf( FILE *stream, iVector d_X, ui size, iVector h_Wk );
overror_t  __vf    cudaVI_read_buf( iVector d_X, ui size, FILE *stream, iVector h_Wk );
                     /* cudaVI_write, cudaVI_read in ascii format */
overror_t  __vf     cudaVI_store( FILE *stream, iVector X, ui size );
overror_t  __vf     cudaVI_recall( iVector X, ui size, FILE *stream );
overror_t  __vf     cudaVI_store_buf( FILE *stream, iVector d_X, ui size, iVector h_Wk );
overror_t  __vf     cudaVI_recall_buf( iVector d_X, ui size, FILE *stream, iVector h_Wk );
                     /* cudaVI_store, cudaVI_recall in binary format */


#ifdef __cplusplus
}  // end of extern "C"
#endif


/******************  VIcu_ functions: **********************************
	act on host memory, using the CUDA device for processing
************************************************************************/

#ifdef __cplusplus
   extern "C" {
#endif

	   /****************** Initialization  ******************************/

void  __vcuf OVCUAPI   VIcu_equ0( iVector X, ui size );
void  __vcuf OVCUAPI   VIcu_equC( iVector X, ui size, int C );
void  __vcuf OVCUAPI   VIcu_equV( iVector Y, iVector X, ui size ); /* copies from device to device */
void  __vcuf OVCUAPI   VIcu_ramp( iVector X, ui size, int Start, int Rise );
/* no Vcu_random functions: random generation runs on CPU anyway */


/************** Data-type interconversions  ***************************/

void  __vcuf OVCUAPI   Vcu_BItoI(  iVector  Y, biVector X, ui size );  /* up-conversion */
void  __vcuf OVCUAPI   Vcu_SItoI(  iVector  Y, siVector X, ui size );
void  __vcuf OVCUAPI   Vcu_ItoLI(  liVector Y, iVector  X, ui size );
void  __vcuf OVCUAPI   Vcu_ItoQI(  qiVector Y, iVector  X, ui size );

void  __vcuf OVCUAPI   Vcu_ItoBI(  biVector Y, iVector  X, ui size ); /* down-conversion */
void  __vcuf OVCUAPI   Vcu_ItoU( uVector Y, iVector X, ui size );
void  __vcuf OVCUAPI   Vcu_UtoI( iVector Y, uVector X, ui size );
void  __vcuf OVCUAPI   Vcu_ItoSI( siVector Y, iVector  X, ui size );
void  __vcuf OVCUAPI   Vcu_LItoI( iVector  Y, liVector X, ui size );
void  __vcuf OVCUAPI   Vcu_QItoI( iVector  Y, qiVector X, ui size );

void  __vcuf OVCUAPI   Vcu_ItoF(   fVector Y, iVector  X, ui size );
void  __vcuf OVCUAPI   Vcu_ItoD(   dVector Y, iVector  X, ui size );

/************** Index-oriented manipulations ***************************/

void  __vcuf OVCUAPI   VIcu_reflect( iVector X, ui size );
void  __vcuf OVCUAPI   VIcu_rev( iVector Y, iVector X, ui size );
void  __vcuf OVCUAPI   VIcu_rotate( iVector Y, iVector X, ui size, ssize_t pos );
void  __vcuf OVCUAPI   VIcu_rotate_buf( iVector Y, iVector X, ui size, ssize_t pos, iVector Buf );
void  __vcuf OVCUAPI   VIcu_delete( iVector X, ui size, ui pos );
void  __vcuf OVCUAPI   VIcu_insert( iVector X, ui size, ui pos, int C );
void  __vcuf OVCUAPI   VIcu_sort( iVector Y, iVector X, ui size, int dir );
void  __vcuf OVCUAPI   VIcu_sortind( uiVector Ind, iVector X, ui size, int dir );

void  __vcuf OVCUAPI   VIcu_subvector( iVector Y, ui sizey, iVector X, ssize_t samp );
void  __vcuf OVCUAPI   VIcu_subvector_equC( iVector Y, ui subsz, ui samp, int C );
void  __vcuf OVCUAPI   VIcu_subvector_equV( iVector Y, ui subsz, ui samp, iVector X );
  /* no V?cu_indpick, V?cu_indput possible! */
ui    __vcuf OVCUAPI   VIcu_searchC( iVector XTab, ui size, int C, int mode );
void  __vcuf OVCUAPI   VIcu_searchV( uiVector Ind, iVector X, ui sizex, iVector Tab, ui sizetab, int mode );

/********************   One-dimensional Vector Operations  ********/

int    __vcuf OVCUAPI   VIcu_sum( iVector X, ui size );
int    __vcuf OVCUAPI   VIcu_max( iVector X, ui size );
int    __vcuf OVCUAPI   VIcu_min( iVector X, ui size );
int    __vcuf OVCUAPI   VIcu_maxind( ui *Ind, iVector X, ui size );
int    __vcuf OVCUAPI   VIcu_minind( ui *Ind, iVector X, ui size );
double __vcuf OVCUAPI   VIcu_fsum( iVector X, ui size );
double __vcuf OVCUAPI   VIcu_mean( iVector X, ui size );
void   __vcuf OVCUAPI   VIcu_runsum( iVector Y, iVector X, ui size );
void   __vcuf OVCUAPI   VIcu_runmax( iVector Y, iVector X, ui size );
void   __vcuf OVCUAPI   VIcu_runmin( iVector Y, iVector X, ui size );

int    __vcuf OVCUAPI   VIcu_iselementC( iVector Tab, ui size, int  C );
ui     __vcuf OVCUAPI   VIcu_iselementV( iVector Y, iVector X, ui sizex, iVector Tab, ui sizetab );

ui     __vcuf OVCUAPI   VIcu_distribution( uiVector Abund, iVector Limits, ui nbins, iVector X, ui sizex, int mode );

#ifdef __cplusplus
}  // end of extern "C"
#endif

#endif   /*  __CUDAVISTD_H    */
