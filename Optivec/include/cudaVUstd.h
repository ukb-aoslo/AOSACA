/*  cudaVUstd.h

  vector management functions for data type "unsigned".

  Copyright (c) 1996-2017 by OptiCode - Dr. Martin Sander Software Dev.
  All Rights Reserved.
*/

#ifndef __CUDAVUSTD_H
#define __CUDAVUSTD_H

#if !defined( __CUDAVECLIB_H )
   #include <cudaVecLib.h>
#endif

/******************  cudaVU_ functions: **********************************
	 act on vectors in CUDA device memory; 
	 scalar parameters and return values on host
******************  cusdVU_ functions: **********************************
	 also act on vectors in CUDA device memory; 
	 scalar parameters and return values by address on device memory
************************************************************************/

#ifdef __cplusplus
    extern "C" {
#endif

/*********************  Generation ***********************************/

uVector  __vf  cudaVU_vector( ui size );   /* allocates a vector on device memory */
uVector  __vf  cudaVU_vector0( ui size );
 /* The following functions allocate device-accessible, "pinned" memory on the host.
	This memory is mapped onto the device memory space. The resulting device address is returned.
	The vector can be accessed either by its host address "hostPtr" e.g., VU_ramp( hostPtr, size, 0, 1 );
	or by its device address , e.g., cudaVU_ramp( devicePtr, size, 0, 1 );     */
uVector  __vf  cudaVU_pinnedVector(  uVector *hostPtr, ui size ); 
uVector  __vf  cudaVU_pinnedVector0( uVector *hostPtr, ui size );

/***************  Addressing single vector elements ******************/

unsigned * __vcuf OVCUAPI cudaVU_Pelement( uVector X, ui n );
unsigned   __vcuf OVCUAPI cudaVU_element( uVector X, ui n );
void       __vcuf OVCUAPI cudaVU_getElement( unsigned *y, uVector X, ui n );
void       __vcuf OVCUAPI cusdVU_getElement( unsigned *d_y, uVector X, ui n );
void       __vcuf OVCUAPI cudaVU_setElement( uVector X, ui n, unsigned C );
void       __vcuf OVCUAPI cusdVU_setElement( uVector X, ui n, unsigned *C );

/****************** Initialization  ******************************/

overror_t  __vcuf OVCUAPI   cudaVU_equ0( uVector X, ui size );
overror_t  __vcuf OVCUAPI   cudaVU_equC( uVector X, ui size, unsigned C );
overror_t  __vcuf OVCUAPI   cusdVU_equC( uVector X, ui size, unsigned *C );
overror_t  __vcuf OVCUAPI   cudaVU_equV( uVector Y, uVector X, ui size ); /* copies from device to device */
overror_t  __vcuf OVCUAPI   cudaVU_equVhost( uVector Y, uVector X, ui size );  /* copies from host to device */
overror_t  __vcuf OVCUAPI   VU_equVdevice( uVector Y, uVector X, ui size );  /* copies from device to host */
overror_t  __vcuf OVCUAPI   cudaVU_ramp( uVector X, ui size, unsigned Start, int Rise );
overror_t  __vcuf OVCUAPI   cusdVU_ramp( uVector X, ui size, unsigned *Start, int *Rise );

/******  Linear Congruential random generator with Bays-Durham shuffle:  ***********
  Random series is generated on the CPU. State must be stored in host memory!
  seed!=0 --> initialization of state. seed==0 --> continue series from previous call with the same state. */
overror_t  __vcuf OVCUAPI  cudaVU_randomLC( uVector X, ui size, long seed, unsigned MinVal, unsigned MaxVal, V_RANDOMLCSTATE *state );
overror_t  __vcuf OVCUAPI  cusdVU_randomLC( uVector X, ui size, long seed, unsigned *MinVal, unsigned *MaxVal, V_RANDOMLCSTATE *state );
/**  simplified version: Series cannot be made continuous across calls: */
overror_t  __vcuf OVCUAPI  cudaVU_random( uVector X, ui size, long seed, unsigned MinVal, unsigned MaxVal );
overror_t  __vcuf OVCUAPI  cusdVU_random( uVector X, ui size, long seed, unsigned *MinVal, unsigned *MaxVal );


/************** Data-type interconversions  ***************************/

overror_t  __vcuf OVCUAPI   cudaV_UBtoU(  uVector  Y, ubVector X, ui size );  /* up-conversion */
overror_t  __vcuf OVCUAPI   cudaV_UStoU(  uVector  Y, usVector X, ui size );
overror_t  __vcuf OVCUAPI   cudaV_UtoUL(  ulVector Y, uVector  X, ui size );

overror_t  __vcuf OVCUAPI   cudaV_UtoUB( ubVector Y, uVector  X, ui size ); /* down-conversion */
overror_t  __vcuf OVCUAPI   cudaV_ItoU( uVector Y, iVector X, ui size );
overror_t  __vcuf OVCUAPI   cudaV_UtoI( iVector Y, uVector X, ui size );
overror_t  __vcuf OVCUAPI   cudaV_UtoUS( usVector Y, uVector  X, ui size );
overror_t  __vcuf OVCUAPI   cudaV_ULtoU( uVector  Y, ulVector X, ui size );
#if defined _WIN64
    overror_t __vcuf OVCUAPI   cudaV_UtoUQ( uqVector Y, uVector  X, ui size );
    overror_t __vcuf OVCUAPI   cudaV_UQtoU( uVector Y, uqVector X, ui size );
#endif

overror_t  __vcuf OVCUAPI   cudaV_UtoF(   fVector Y, uVector  X, ui size );
overror_t  __vcuf OVCUAPI   cudaV_UtoD(   dVector Y, uVector  X, ui size );


/************** Index-oriented manipulations ***************************/

overror_t  __vcuf OVCUAPI   cudaVU_reflect( uVector X, ui size );
overror_t  __vcuf OVCUAPI   cudaVU_rev( uVector Y, uVector X, ui size );
overror_t  __vcuf OVCUAPI   cudaVU_rotate( uVector Y, uVector X, ui size, ssize_t pos );
overror_t  __vcuf OVCUAPI   cudaVU_rotate_buf( uVector Y, uVector X, ui size, ssize_t pos, uVector Buf );
overror_t  __vcuf OVCUAPI   cudaVU_delete( uVector X, ui size, ui pos );
overror_t  __vcuf OVCUAPI   cudaVU_insert( uVector X, ui size, ui pos, unsigned C );
overror_t  __vcuf OVCUAPI   cusdVU_insert( uVector X, ui size, ui pos, unsigned *C );
overror_t  __vcuf OVCUAPI   cudaVU_sort( uVector Y, uVector X, ui size, int dir );
overror_t  __vcuf OVCUAPI   cudaVU_sortind( uiVector Ind, uVector X, ui size, int dir );

overror_t  __vcuf OVCUAPI   cudaVU_subvector( uVector Y, ui sizey, uVector X, ssize_t samp );
overror_t  __vcuf OVCUAPI   cudaVU_subvector_equC( uVector Y, ui subsz, ui samp, unsigned C );
overror_t  __vcuf OVCUAPI   cusdVU_subvector_equC( uVector Y, ui subsz, ui samp, unsigned *C );
overror_t  __vcuf OVCUAPI   cudaVU_subvector_equV( uVector Y, ui subsz, ui samp, uVector X );
overror_t  __vcuf OVCUAPI   cudaVU_indpick( uVector Y, uiVector Ind, ui sizey, uVector X );
overror_t  __vcuf OVCUAPI   cudaVU_indput(  uVector Y, uVector X, uiVector Ind, ui sizex );
overror_t  __vcuf OVCUAPI   cudaVU_searchC( ui *h_Ind, uVector XTab, ui size, unsigned C, int mode );
overror_t  __vcuf OVCUAPI   cusdVU_searchC( ui *d_Ind, uVector XTab, ui size, unsigned *C, int mode );
overror_t  __vcuf OVCUAPI   cudaVU_searchV( uiVector Ind, uVector X, ui sizex, uVector Tab, ui sizetab, int mode );

/********************   One-dimensional Vector Operations  ********/

overror_t  __vcuf OVCUAPI   cudaVU_sum( unsigned *h_RetVal, uVector X, ui size );
overror_t  __vcuf OVCUAPI   cudaVU_max( unsigned *h_RetVal, uVector X, ui size );
overror_t  __vcuf OVCUAPI   cudaVU_min( unsigned *h_RetVal, uVector X, ui size );
overror_t  __vcuf OVCUAPI   cudaVU_maxind( unsigned *h_RetVal, ui *Ind, uVector X, ui size );
overror_t  __vcuf OVCUAPI   cudaVU_minind( unsigned *h_RetVal, ui *Ind, uVector X, ui size );
overror_t  __vcuf OVCUAPI   cudaVU_fsum( double *h_RetVal, uVector X, ui size );
overror_t  __vcuf OVCUAPI   cudaVU_mean( double *h_RetVal, uVector X, ui size );
overror_t  __vcuf OVCUAPI   cudaVU_runsum( uVector Y, uVector X, ui size );
overror_t  __vcuf OVCUAPI   cudaVU_runmax( uVector Y, uVector X, ui size );
overror_t  __vcuf OVCUAPI   cudaVU_runmin( uVector Y, uVector X, ui size );

overror_t  __vcuf OVCUAPI   cusdVU_sum( unsigned *d_RetVal, uVector X, ui size );
overror_t  __vcuf OVCUAPI   cusdVU_max( unsigned *d_RetVal, uVector X, ui size );
overror_t  __vcuf OVCUAPI   cusdVU_min( unsigned *d_RetVal, uVector X, ui size );
overror_t  __vcuf OVCUAPI   cusdVU_maxind( unsigned *d_RetVal, ui *Ind, uVector X, ui size );
overror_t  __vcuf OVCUAPI   cusdVU_minind( unsigned *d_RetVal, ui *Ind, uVector X, ui size );
overror_t  __vcuf OVCUAPI   cusdVU_fsum( double *d_RetVal, uVector X, ui size );
overror_t  __vcuf OVCUAPI   cusdVU_mean( double *d_RetVal, uVector X, ui size );

int        __vcuf OVCUAPI   cudaVU_iselementC( uVector Tab, ui size, unsigned  C );
int        __vcuf OVCUAPI   cusdVU_iselementC( uVector Tab, ui size, unsigned  *C );
overror_t  __vcuf OVCUAPI   cudaVU_iselementV( ui *h_nFound, uVector Y, uVector X, ui sizex, uVector Tab, ui sizetab );

overror_t  __vcuf OVCUAPI   cudaVU_distribution( ui *h_nOutside, uiVector Abund, uVector Limits, ui nbins, uVector X, ui sizex, int mode );
overror_t  __vcuf OVCUAPI   cusdVU_distribution( ui *d_nOutside, uiVector Abund, uVector Limits, ui nbins, uVector X, ui sizex, int mode );

/***************************  Input and Output *****************************
	The input/output functions involve memory transfers from device
	to host memory or vice versa. The generic cudaVF_input/output functions
	allocate their own host buffers, whereas the cudaVU_xxx_buf functions
	take a user-supplied buffer h_Wk and are much more efficient.          */

overror_t  __vf    cudaVU_fprint( FILE *stream, uVector X, ui size, unsigned nperline, unsigned linewidth );
overror_t  __vf    cudaVU_cprint( uVector X, ui size, unsigned nperline );
#define       cudaVU_print( x, sz, npl )  cudaVU_fprint( stdout, x, sz, npl, 80 )
overror_t  __vf    cudaVU_fprint_buf( FILE *stream, uVector d_X, ui size, unsigned nperline, unsigned linewidth, uVector h_Wk );
overror_t  __vf    cudaVU_cprint_buf( uVector d_X, ui size, unsigned nperline, uVector h_Wk );
#define       cudaVU_print_buf( d_x, sz, npl, h_Wk )  cudaVU_fprint_buf( stdout, d_x, sz, npl, 80, h_Wk )
 /*  cudaVU_print, cudaVU_cprint are usable only for console applications!  */
overror_t  __vf    cudaVU_write( FILE *stream, uVector X, ui size  );
overror_t  __vf    cudaVU_read( uVector X, ui size, FILE *stream );
overror_t  __vf    cudaVU_write_buf( FILE *stream, uVector d_X, ui size, uVector h_Wk );
overror_t  __vf    cudaVU_read_buf( uVector d_X, ui size, FILE *stream, uVector h_Wk );
                     /* cudaVU_write, cudaVU_read in ascii format */
overror_t  __vf     cudaVU_store( FILE *stream, uVector X, ui size );
overror_t  __vf     cudaVU_recall( uVector X, ui size, FILE *stream );
overror_t  __vf     cudaVU_store_buf( FILE *stream, uVector d_X, ui size, uVector h_Wk );
overror_t  __vf     cudaVU_recall_buf( uVector d_X, ui size, FILE *stream, uVector h_Wk );
                     /* cudaVU_store, cudaVU_recall in binary format */


#ifdef __cplusplus
}  // end of extern "C"
#endif

/******************  VUcu_ functions: **********************************
	act on host memory, using the CUDA device for processing
************************************************************************/


#ifdef __cplusplus
    extern "C" {
#endif

/****************** Initialization  ******************************/

void  __vcuf OVCUAPI   VUcu_equ0( uVector X, ui size );
void  __vcuf OVCUAPI   VUcu_equC( uVector X, ui size, unsigned C );
void  __vcuf OVCUAPI   VUcu_equV( uVector Y, uVector X, ui size ); /* copies from device to device */
void  __vcuf OVCUAPI   VUcu_ramp( uVector X, ui size, unsigned Start, int Rise );
/* no Vcu_random functions: random generation runs on CPU anyway */


/************** Data-type interconversions  ***************************/

void  __vcuf OVCUAPI   Vcu_UBtoU(  uVector  Y, ubVector X, ui size );  /* up-conversion */
void  __vcuf OVCUAPI   Vcu_UStoU(  uVector  Y, usVector X, ui size );
void  __vcuf OVCUAPI   Vcu_UtoUL(  ulVector Y, uVector  X, ui size );

void  __vcuf OVCUAPI   Vcu_UtoUB( ubVector Y, uVector  X, ui size ); /* down-conversion */
void  __vcuf OVCUAPI   Vcu_ItoU( uVector Y, iVector X, ui size );
void  __vcuf OVCUAPI   Vcu_UtoI( iVector Y, uVector X, ui size );
void  __vcuf OVCUAPI   Vcu_UtoUS( usVector Y, uVector  X, ui size );
void  __vcuf OVCUAPI   Vcu_ULtoU( uVector  Y, ulVector X, ui size );
#if defined _WIN64
    void __vcuf OVCUAPI   Vcu_UtoUQ( uqVector Y, uVector  X, ui size );
    void __vcuf OVCUAPI   Vcu_UQtoU( uVector Y, uqVector X, ui size );
#endif

void  __vcuf OVCUAPI   Vcu_UtoF(   fVector Y, uVector  X, ui size );
void  __vcuf OVCUAPI   Vcu_UtoD(   dVector Y, uVector  X, ui size );


/************** Index-oriented manipulations ***************************/

void  __vcuf OVCUAPI   VUcu_reflect( uVector X, ui size );
void  __vcuf OVCUAPI   VUcu_rev( uVector Y, uVector X, ui size );
void  __vcuf OVCUAPI   VUcu_rotate( uVector Y, uVector X, ui size, ssize_t pos );
void  __vcuf OVCUAPI   VUcu_rotate_buf( uVector Y, uVector X, ui size, ssize_t pos, uVector Buf );
void  __vcuf OVCUAPI   VUcu_delete( uVector X, ui size, ui pos );
void  __vcuf OVCUAPI   VUcu_insert( uVector X, ui size, ui pos, unsigned C );
void  __vcuf OVCUAPI   VUcu_sort( uVector Y, uVector X, ui size, int dir );
void  __vcuf OVCUAPI   VUcu_sortind( uiVector Ind, uVector X, ui size, int dir );

void  __vcuf OVCUAPI   VUcu_subvector( uVector Y, ui sizey, uVector X, ssize_t samp );
void  __vcuf OVCUAPI   VUcu_subvector_equC( uVector Y, ui subsz, ui samp, unsigned C );
void  __vcuf OVCUAPI   VUcu_subvector_equV( uVector Y, ui subsz, ui samp, uVector X );
  /* no V?cu_indpick, V?cu_indput possible! */
ui    __vcuf OVCUAPI   VUcu_searchC( uVector XTab, ui size, unsigned C, int mode );
void  __vcuf OVCUAPI   VUcu_searchV( uiVector Ind, uVector X, ui sizex, uVector Tab, ui sizetab, int mode );

/********************   One-dimensional Vector Operations  ********/

unsigned  __vcuf OVCUAPI   VUcu_sum( uVector X, ui size );
unsigned  __vcuf OVCUAPI   VUcu_max( uVector X, ui size );
unsigned  __vcuf OVCUAPI   VUcu_min( uVector X, ui size );
unsigned  __vcuf OVCUAPI   VUcu_maxind( ui *Ind, uVector X, ui size );
unsigned  __vcuf OVCUAPI   VUcu_minind( ui *Ind, uVector X, ui size );
double    __vcuf OVCUAPI   VUcu_fsum( uVector X, ui size );
double    __vcuf OVCUAPI   VUcu_mean( uVector X, ui size );
void      __vcuf OVCUAPI   VUcu_runsum( uVector Y, uVector X, ui size );
void      __vcuf OVCUAPI   VUcu_runmax( uVector Y, uVector X, ui size );
void      __vcuf OVCUAPI   VUcu_runmin( uVector Y, uVector X, ui size );

int       __vcuf OVCUAPI   VUcu_iselementC( uVector Tab, ui size, unsigned  C );
ui        __vcuf OVCUAPI   VUcu_iselementV( uVector Y, uVector X, ui sizex, uVector Tab, ui sizetab );

ui        __vcuf OVCUAPI   VUcu_distribution( uiVector Abund, uVector Limits, ui nbins, uVector X, ui sizex, int mode );

#ifdef __cplusplus
}  // end of extern "C"
#endif

#endif   /*  __CUDAVUSTD_H    */
