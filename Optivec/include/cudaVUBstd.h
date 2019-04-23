/*  cudaVUBstd.h

  vector management functions for data type "unsigned char".

  Copyright (c) 1996-2017 by OptiCode - Dr. Martin Sander Software Dev.
  All Rights Reserved.
*/

#ifndef __CUDAVUBSTD_H
#define __CUDAVUBSTD_H

#if !defined( __CUDAVECLIB_H )
   #include <cudaVecLib.h>
#endif

/******************  cudaVUB_ functions: **********************************
	 act on vectors in CUDA device memory; 
	 scalar parameters and return values on host
******************  cusdVUB_ functions: **********************************
	 also act on vectors in CUDA device memory; 
	 scalar parameters and return values by address on device memory
************************************************************************/

#ifdef __cplusplus
   extern "C" {
#endif

/**********************  Generation *************************************/

ubVector  __vf  cudaVUB_vector( ui size );   /* allocates a vector on device memory */
ubVector  __vf  cudaVUB_vector0( ui size );
 /* The following functions allocate device-accessible, "pinned" memory on the host.
	This memory is mapped onto the device memory space. The resulting device address is returned.
	The vector can be accessed either by its host address "hostPtr" e.g., VUB_ramp( hostPtr, size, 0, 1 );
	or by its device address , e.g., cudaVUB_ramp( devicePtr, size, 0, 1 );     */
ubVector  __vf  cudaVUB_pinnedVector(  ubVector *hostPtr, ui size ); 
ubVector  __vf  cudaVUB_pinnedVector0( ubVector *hostPtr, ui size );

/***************  Addressing single vector elements ******************/

unsigned char * __vcuf OVCUAPI cudaVUB_Pelement( ubVector X, ui n );
unsigned char   __vcuf OVCUAPI cudaVUB_element( ubVector X, ui n );
void            __vcuf  OVCUAPI cudaVUB_getElement( unsigned char *y, ubVector X, ui n );
void            __vcuf  OVCUAPI cusdVUB_getElement( unsigned char *d_y, ubVector X, ui n );
void            __vcuf OVCUAPI cudaVUB_setElement( ubVector X, ui n, unsigned char C );
void            __vcuf OVCUAPI cusdVUB_setElement( ubVector X, ui n, unsigned char *d_C );

/****************** Initialization  ******************************/

overror_t  __vcuf OVCUAPI   cudaVUB_equ0( ubVector X, ui size );
overror_t  __vcuf OVCUAPI   cudaVUB_equC( ubVector X, ui size, unsigned char C );
overror_t  __vcuf OVCUAPI   cusdVUB_equC( ubVector X, ui size, unsigned char *d_C );
overror_t  __vcuf OVCUAPI   cudaVUB_equV( ubVector Y, ubVector X, ui size ); /* copies from device to device */
overror_t  __vcuf OVCUAPI   cudaVUB_equVhost( ubVector Y, ubVector X, ui size );  /* copies from host to device */
overror_t  __vcuf OVCUAPI   VUB_equVdevice( ubVector Y, ubVector X, ui size );  /* copies from device to host */
overror_t  __vcuf OVCUAPI   cudaVUB_ramp( ubVector X, ui size, unsigned char Start, char Rise );
overror_t  __vcuf OVCUAPI   cusdVUB_ramp( ubVector X, ui size, unsigned char *d_Start, char *d_Rise );

/******  Linear Congruential random generator with Bays-Durham shuffle:  ***********
  Random series is generated on the CPU. State must be stored in host memory!
  seed!=0 --> initialization of state. seed==0 --> continue series from previous call with the same state. */
overror_t  __vcuf OVCUAPI  cudaVUB_randomLC( ubVector X, ui size, long seed, unsigned char MinVal, unsigned char MaxVal, V_RANDOMLCSTATE *state );
overror_t  __vcuf OVCUAPI  cusdVUB_randomLC( ubVector X, ui size, long seed, unsigned char *MinVal, unsigned char *MaxVal, V_RANDOMLCSTATE *state );
/**  simplified version: Series cannot be made continuous across calls: */
overror_t  __vcuf OVCUAPI  cudaVUB_random( ubVector X, ui size, long seed, unsigned char MinVal, unsigned char MaxVal );
overror_t  __vcuf OVCUAPI  cusdVUB_random( ubVector X, ui size, long seed, unsigned char *MinVal, unsigned char *MaxVal );



/**************  Data-type overror_terconversions  **************************/

overror_t __vcuf OVCUAPI   cudaV_BItoUB( ubVector Y, biVector X, ui size );  /* signed-unsigned */
overror_t __vcuf OVCUAPI   cudaV_UBtoBI( biVector Y, ubVector X, ui size );

overror_t __vcuf OVCUAPI   cudaV_UBtoU(  uVector  Y, ubVector X, ui size );  /* up-conversion */
overror_t __vcuf OVCUAPI   cudaV_UBtoUS( usVector Y, ubVector X, ui size );
overror_t __vcuf OVCUAPI   cudaV_UBtoUL( ulVector Y, ubVector X, ui size );

overror_t  __vcuf OVCUAPI   cudaV_UStoUB( ubVector Y, usVector X, ui size );/* down-conversion */
overror_t  __vcuf OVCUAPI   cudaV_UtoUB(  ubVector Y, uVector  X, ui size );
overror_t  __vcuf OVCUAPI   cudaV_ULtoUB( ubVector Y, ulVector X, ui size );

#if defined _WIN64
    overror_t __vcuf OVCUAPI   cudaV_UBtoUQ( uqVector Y, ubVector  X, ui size );
    overror_t __vcuf OVCUAPI   cudaV_UQtoUB( ubVector Y, uqVector X, ui size );
#endif

overror_t  __vcuf OVCUAPI   cudaV_UBtoF(  fVector Y, ubVector X, ui size );
overror_t  __vcuf OVCUAPI   cudaV_UBtoD(  dVector Y, ubVector X, ui size );


/************** Index-oriented manipulations ***************************/

overror_t  __vcuf OVCUAPI   cudaVUB_reflect( ubVector X, ui size );
overror_t  __vcuf OVCUAPI   cudaVUB_rev( ubVector Y, ubVector X, ui size );
overror_t  __vcuf OVCUAPI   cudaVUB_rotate( ubVector Y, ubVector X, ui size, ssize_t pos );
overror_t  __vcuf OVCUAPI   cudaVUB_rotate_buf( ubVector Y, ubVector X, ui size, ssize_t pos, ubVector Buf );
overror_t  __vcuf OVCUAPI   cudaVUB_delete( ubVector X, ui size, ui pos );
overror_t  __vcuf OVCUAPI   cudaVUB_insert( ubVector X, ui size, ui pos, unsigned char C );
overror_t  __vcuf OVCUAPI   cusdVUB_insert( ubVector X, ui size, ui pos, unsigned char *C );
overror_t  __vcuf OVCUAPI   cudaVUB_sort( ubVector Y, ubVector X, ui size, int dir );
overror_t  __vcuf OVCUAPI   cudaVUB_sortind( uiVector Ind, ubVector X, ui size, int dir );

overror_t  __vcuf OVCUAPI   cudaVUB_subvector( ubVector Y, ui sizey, ubVector X, ssize_t samp );
overror_t  __vcuf OVCUAPI   cudaVUB_subvector_equC( ubVector Y, ui subsz, ui samp, unsigned char C );
overror_t  __vcuf OVCUAPI   cusdVUB_subvector_equC( ubVector Y, ui subsz, ui samp, unsigned char *C );
overror_t  __vcuf OVCUAPI   cudaVUB_subvector_equV( ubVector Y, ui subsz, ui samp, ubVector X );

overror_t  __vcuf OVCUAPI   cudaVUB_indpick( ubVector Y, uiVector Ind, ui sizey, ubVector X );
overror_t  __vcuf OVCUAPI   cudaVUB_indput(  ubVector Y, ubVector X, uiVector Ind, ui sizex );
overror_t  __vcuf OVCUAPI   cudaVUB_searchC( ui *h_Ind, ubVector XTab, ui size, unsigned char C, int mode );
overror_t  __vcuf OVCUAPI   cusdVUB_searchC( ui *d_Ind, ubVector XTab, ui size, unsigned char *C, int mode );
overror_t  __vcuf OVCUAPI   cudaVUB_searchV( uiVector Ind, ubVector X, ui sizex, ubVector Tab, ui sizetab, int mode );

/********************   One-dimensional Vector Operations  ********/

overror_t  __vcuf OVCUAPI   cudaVUB_sum( unsigned char *h_RetVal, ubVector X, ui size );
overror_t  __vcuf OVCUAPI   cudaVUB_max( unsigned char *h_RetVal, ubVector X, ui size );
overror_t  __vcuf OVCUAPI   cudaVUB_min( unsigned char *h_RetVal, ubVector X, ui size );
overror_t  __vcuf OVCUAPI   cudaVUB_maxind( unsigned char *h_RetVal, ui *Ind, ubVector X, ui size );
overror_t  __vcuf OVCUAPI   cudaVUB_minind( unsigned char *h_RetVal, ui *Ind, ubVector X, ui size );
overror_t  __vcuf OVCUAPI   cudaVUB_fsum( double *h_retVal, ubVector X, ui size );
overror_t  __vcuf OVCUAPI   cudaVUB_mean( double *h_retVal, ubVector X, ui size );
overror_t  __vcuf OVCUAPI   cudaVUB_runsum( ubVector Y, ubVector X, ui size );
overror_t  __vcuf OVCUAPI   cudaVUB_runmax( ubVector Y, ubVector X, ui size );
overror_t  __vcuf OVCUAPI   cudaVUB_runmin( ubVector Y, ubVector X, ui size );

overror_t  __vcuf OVCUAPI   cusdVUB_sum( unsigned char *d_RetVal, ubVector X, ui size );
overror_t  __vcuf OVCUAPI   cusdVUB_max( unsigned char *d_RetVal, ubVector X, ui size );
overror_t  __vcuf OVCUAPI   cusdVUB_min( unsigned char *d_RetVal, ubVector X, ui size );
overror_t  __vcuf OVCUAPI   cusdVUB_maxind( unsigned char *d_RetVal, ui *Ind, ubVector X, ui size );
overror_t  __vcuf OVCUAPI   cusdVUB_minind( unsigned char *d_RetVal, ui *Ind, ubVector X, ui size );
overror_t  __vcuf OVCUAPI   cusdVUB_fsum( double *d_RetVal, ubVector X, ui size );
overror_t  __vcuf OVCUAPI   cusdVUB_mean( double *d_RetVal, ubVector X, ui size );

int        __vcuf OVCUAPI   cudaVUB_iselementC( ubVector Tab, ui size, unsigned char C );
int        __vcuf OVCUAPI   cusdVUB_iselementC( ubVector Tab, ui size, unsigned char *C );
overror_t  __vcuf OVCUAPI   cudaVUB_iselementV( ui *h_nFound, ubVector Y, ubVector X, ui sizex, ubVector Tab, ui sizetab );

overror_t  __vcuf OVCUAPI   cudaVUB_distribution( ui *h_nOutside, uiVector Abund, ubVector Limits, ui nbins, ubVector X, ui sizex, int mode );
overror_t  __vcuf OVCUAPI   cusdVUB_distribution( ui *d_nOutside, uiVector Abund, ubVector Limits, ui nbins, ubVector X, ui sizex, int mode );

/***************************  Input and Output *****************************
	The input/output functions involve memory transfers from device
	to host memory or vice versa. The generic cudaVF_input/output functions
	allocate their own host buffers, whereas the cudaVUB_xxx_buf functions
	take a user-supplied buffer h_Wk and are much more efficient.          */

overror_t  __vf    cudaVUB_fprint( FILE *stream, ubVector X, ui size, unsigned nperline, unsigned linewidth );
overror_t  __vf    cudaVUB_cprint( ubVector X, ui size, unsigned nperline );
#define       cudaVUB_print( x, sz, npl )  cudaVUB_fprint( stdout, x, sz, npl, 80 )
overror_t  __vf    cudaVUB_fprint_buf( FILE *stream, ubVector d_X, ui size, unsigned nperline, unsigned linewidth, ubVector h_Wk );
overror_t  __vf    cudaVUB_cprint_buf( ubVector d_X, ui size, unsigned nperline, ubVector h_Wk );
#define       cudaVUB_print_buf( d_x, sz, npl, h_Wk )  cudaVUB_fprint_buf( stdout, d_x, sz, npl, 80, h_Wk )
 /*  cudaVUB_print, cudaVUB_cprint are usable only for console applications!  */
overror_t  __vf    cudaVUB_write( FILE *stream, ubVector X, ui size  );
overror_t  __vf    cudaVUB_read( ubVector X, ui size, FILE *stream );
overror_t  __vf    cudaVUB_write_buf( FILE *stream, ubVector d_X, ui size, ubVector h_Wk );
overror_t  __vf    cudaVUB_read_buf( ubVector d_X, ui size, FILE *stream, ubVector h_Wk );
                     /* cudaVUB_write, cudaVUB_read in ascii format */
overror_t  __vf     cudaVUB_store( FILE *stream, ubVector X, ui size );
overror_t  __vf     cudaVUB_recall( ubVector X, ui size, FILE *stream );
overror_t  __vf     cudaVUB_store_buf( FILE *stream, ubVector d_X, ui size, ubVector h_Wk );
overror_t  __vf     cudaVUB_recall_buf( ubVector d_X, ui size, FILE *stream, ubVector h_Wk );
                     /* cudaVUB_store, cudaVUB_recall in binary format */


#ifdef __cplusplus
}  // end of extern "C"
#endif

/******************  VUBcu_ functions: **********************************
	act on host memory, using the CUDA device for processing
************************************************************************/


#ifdef __cplusplus
   extern "C" {
#endif

/****************** Initialization  ******************************/

void  __vcuf OVCUAPI   VUBcu_equ0( ubVector X, ui size );
void  __vcuf OVCUAPI   VUBcu_equC( ubVector X, ui size, unsigned char C );
void  __vcuf OVCUAPI   VUBcu_equV( ubVector Y, ubVector X, ui size ); /* copies from device to device */
void  __vcuf OVCUAPI   VUBcu_ramp( ubVector X, ui size, unsigned char Start, char Rise );
/* no Vcu_random functions: random generation runs on CPU anyway */


/**************  Data-type interconversions  **************************/

void __vcuf OVCUAPI   Vcu_BItoUB( ubVector Y, biVector X, ui size );  /* signed-unsigned */
void __vcuf OVCUAPI   Vcu_UBtoBI( biVector Y, ubVector X, ui size );

void __vcuf OVCUAPI   Vcu_UBtoU(  uVector  Y, ubVector X, ui size );  /* up-conversion */
void __vcuf OVCUAPI   Vcu_UBtoUS( usVector Y, ubVector X, ui size );
void __vcuf OVCUAPI   Vcu_UBtoUL( ulVector Y, ubVector X, ui size );

void  __vcuf OVCUAPI   Vcu_UStoUB( ubVector Y, usVector X, ui size );/* down-conversion */
void  __vcuf OVCUAPI   Vcu_UtoUB(  ubVector Y, uVector  X, ui size );
void  __vcuf OVCUAPI   Vcu_ULtoUB( ubVector Y, ulVector X, ui size );

#if defined _WIN64
    void __vcuf OVCUAPI   Vcu_UBtoUQ( uqVector Y, ubVector  X, ui size );
    void __vcuf OVCUAPI   Vcu_UQtoUB( ubVector Y, uqVector X, ui size );
#endif

void  __vcuf OVCUAPI   Vcu_UBtoF(  fVector Y, ubVector X, ui size );
void  __vcuf OVCUAPI   Vcu_UBtoD(  dVector Y, ubVector X, ui size );


/************** Index-oriented manipulations ***************************/

void  __vcuf OVCUAPI   VUBcu_reflect( ubVector X, ui size );
void  __vcuf OVCUAPI   VUBcu_rev( ubVector Y, ubVector X, ui size );
void  __vcuf OVCUAPI   VUBcu_rotate( ubVector Y, ubVector X, ui size, ssize_t pos );
void  __vcuf OVCUAPI   VUBcu_rotate_buf( ubVector Y, ubVector X, ui size, ssize_t pos, ubVector Buf );
void  __vcuf OVCUAPI   VUBcu_delete( ubVector X, ui size, ui pos );
void  __vcuf OVCUAPI   VUBcu_insert( ubVector X, ui size, ui pos, unsigned char C );
void  __vcuf OVCUAPI   VUBcu_sort( ubVector Y, ubVector X, ui size, int dir );
void  __vcuf OVCUAPI   VUBcu_sortind( uiVector Ind, ubVector X, ui size, int dir );

void  __vcuf OVCUAPI   VUBcu_subvector( ubVector Y, ui sizey, ubVector X, ssize_t samp );
void  __vcuf OVCUAPI   VUBcu_subvector_equC( ubVector Y, ui subsz, ui samp, unsigned char C );
void  __vcuf OVCUAPI   VUBcu_subvector_equV( ubVector Y, ui subsz, ui samp, ubVector X );

  /* no V?cu_indpick, V?cu_indput possible! */
ui    __vcuf OVCUAPI   VUBcu_searchC( ubVector XTab, ui size, unsigned char C, int mode );
void  __vcuf OVCUAPI   VUBcu_searchV( uiVector Ind, ubVector X, ui sizex, ubVector Tab, ui sizetab, int mode );

/********************   One-dimensional Vector Operations  ********/

unsigned char  __vcuf OVCUAPI   VUBcu_sum( ubVector X, ui size );
unsigned char  __vcuf OVCUAPI   VUBcu_max( ubVector X, ui size );
unsigned char  __vcuf OVCUAPI   VUBcu_min( ubVector X, ui size );
unsigned char  __vcuf OVCUAPI   VUBcu_maxind( ui *Ind, ubVector X, ui size );
unsigned char  __vcuf OVCUAPI   VUBcu_minind( ui *Ind, ubVector X, ui size );
double         __vcuf OVCUAPI   VUBcu_fsum( ubVector X, ui size );
double         __vcuf OVCUAPI   VUBcu_mean( ubVector X, ui size );
void           __vcuf OVCUAPI   VUBcu_runsum( ubVector Y, ubVector X, ui size );
void           __vcuf OVCUAPI   VUBcu_runmax( ubVector Y, ubVector X, ui size );
void           __vcuf OVCUAPI   VUBcu_runmin( ubVector Y, ubVector X, ui size );

int    __vcuf OVCUAPI   VUBcu_iselementC( ubVector Tab, ui size, unsigned char C );
ui     __vcuf OVCUAPI   VUBcu_iselementV( ubVector Y, ubVector X, ui sizex, ubVector Tab, ui sizetab );
ui     __vcuf OVCUAPI   VUBcu_distribution( uiVector Abund, ubVector Limits, ui nbins, ubVector X, ui sizex, int mode );

#ifdef __cplusplus
}  // end of extern "C"
#endif

#endif   /*  __CUDAVUBSTD_H    */
