/*  cudaVSIstd.h

  vector management functions for data type "short int".

  Copyright (c) 1996-2017 by OptiCode - Dr. Martin Sander Software Dev.
  All Rights Reserved.
*/

#ifndef __CUDAVSISTD_H
#define __CUDAVSISTD_H

#if !defined( __CUDAVECLIB_H )
   #include <cudaVecLib.h>
#endif

/******************  cudaVSI_ functions: **********************************
	 act on vectors in CUDA device memory; 
	 scalar parameters and return values on host
******************  cusdVSI_ functions: **********************************
	 also act on vectors in CUDA device memory; 
	 scalar parameters and return values by address on device memory
************************************************************************/

#ifdef __cplusplus
   extern "C" {
#endif

/*************************  Generation ***************************/

siVector  __vf  cudaVSI_vector( ui size );   /* allocates a vector on device memory */
siVector  __vf  cudaVSI_vector0( ui size );
 /* The following functions allocate device-accessible, "pinned" memory on the host.
	This memory is mapped onto the device memory space. The resulting device address is returned.
	The vector can be accessed either by its host address "hostPtr" e.g., VSI_ramp( hostPtr, size, 0, 1 );
	or by its device address , e.g., cudaVSI_ramp( devicePtr, size, 0, 1 );     */
siVector  __vf  cudaVSI_pinnedVector(  siVector *hostPtr, ui size ); 
siVector  __vf  cudaVSI_pinnedVector0( siVector *hostPtr, ui size );


/***************  Addressing single vector elements ******************/

short * __vcuf OVCUAPI cudaVSI_Pelement( siVector X, ui n );
short   __vcuf OVCUAPI cudaVSI_element( siVector X, ui n );
void    __vcuf OVCUAPI cudaVSI_getElement( short *y, siVector X, ui n );
void    __vcuf OVCUAPI cusdVSI_getElement( short *d_y, siVector X, ui n );
void    __vcuf OVCUAPI cudaVSI_setElement( siVector X, ui n, short C );
void    __vcuf OVCUAPI cusdVSI_setElement( siVector X, ui n, short *C );

/****************** Initialization  ******************************/

overror_t  __vcuf OVCUAPI   cudaVSI_equ0( siVector X, ui size );
overror_t  __vcuf OVCUAPI   cudaVSI_equC( siVector X, ui size, short C );
overror_t  __vcuf OVCUAPI   cusdVSI_equC( siVector X, ui size, short *C );
overror_t  __vcuf OVCUAPI   cudaVSI_equV( siVector Y, siVector X, ui size ); /* copies from device to device */
overror_t  __vcuf OVCUAPI   cudaVSI_equVhost( siVector Y, siVector X, ui size );  /* copies from host to device */
overror_t  __vcuf OVCUAPI   VSI_equVdevice( siVector Y, siVector X, ui size );  /* copies from device to host */
overror_t  __vcuf OVCUAPI   cudaVSI_ramp( siVector X, ui size, short Start, short Rise );
overror_t  __vcuf OVCUAPI   cusdVSI_ramp( siVector X, ui size, short *Start, short *Rise );

/******  Linear Congruential random generator with Bays-Durham shuffle:  ***********
  Random series is generated on the CPU. State must be stored in host memory!
  seed!=0 --> initialization of state. seed==0 --> continue series from previous call with the same state. */
overror_t  __vcuf OVCUAPI  cudaVSI_randomLC( siVector X, ui size, long seed, short MinVal, short MaxVal, V_RANDOMLCSTATE *state );
overror_t  __vcuf OVCUAPI  cusdVSI_randomLC( siVector X, ui size, long seed, short *MinVal, short *MaxVal, V_RANDOMLCSTATE *state );
/**  simplified version: Series cannot be made continuous across calls: */
overror_t  __vcuf OVCUAPI  cudaVSI_random( siVector X, ui size, long seed, short MinVal, short MaxVal );
overror_t  __vcuf OVCUAPI  cusdVSI_random( siVector X, ui size, long seed, short *MinVal, short *MaxVal );



/************** Data-type overror_terconversions  ****************************/

overror_t  __vcuf OVCUAPI   cudaV_BItoSI( siVector Y, biVector X, ui size );  /* up-conversion */
overror_t  __vcuf OVCUAPI   cudaV_SItoI(  iVector  Y, siVector X, ui size );
overror_t  __vcuf OVCUAPI   cudaV_SItoLI( liVector Y, siVector X, ui size );
overror_t  __vcuf OVCUAPI   cudaV_SItoQI( qiVector Y, siVector X, ui size );

overror_t  __vcuf OVCUAPI   cudaV_SItoBI(  biVector Y, siVector X, ui size ); /* down-conversion */
overror_t  __vcuf OVCUAPI   cudaV_SItoUS( usVector Y, siVector X, ui size );
overror_t  __vcuf OVCUAPI   cudaV_UStoSI( siVector Y, usVector X, ui size );
overror_t  __vcuf OVCUAPI   cudaV_ItoSI(  siVector Y, iVector  X, ui size );
overror_t  __vcuf OVCUAPI   cudaV_LItoSI( siVector Y, liVector X, ui size );
overror_t  __vcuf OVCUAPI   cudaV_QItoSI( siVector Y, qiVector X, ui size );

overror_t  __vcuf OVCUAPI   cudaV_SItoF(  fVector Y, siVector X, ui size );
overror_t  __vcuf OVCUAPI   cudaV_SItoD(  dVector Y, siVector X, ui size );

/************** Index-oriented manipulations ***************************/

overror_t  __vcuf OVCUAPI   cudaVSI_reflect( siVector X, ui size );
overror_t  __vcuf OVCUAPI   cudaVSI_rev( siVector Y, siVector X, ui size );
overror_t  __vcuf OVCUAPI   cudaVSI_rotate( siVector Y, siVector X, ui size, ssize_t pos );
overror_t  __vcuf OVCUAPI   cudaVSI_rotate_buf( siVector Y, siVector X, ui size, ssize_t pos, siVector Buf );
overror_t  __vcuf OVCUAPI   cudaVSI_delete( siVector X, ui size, ui pos );
overror_t  __vcuf OVCUAPI   cudaVSI_insert( siVector X, ui size, ui pos, short C );
overror_t  __vcuf OVCUAPI   cusdVSI_insert( siVector X, ui size, ui pos, short *C );
overror_t  __vcuf OVCUAPI   cudaVSI_sort( siVector Y, siVector X, ui size, int dir );
overror_t  __vcuf OVCUAPI   cudaVSI_sortind( uiVector Ind, siVector X, ui size, int dir );
overror_t  __vcuf OVCUAPI   cudaVSI_subvector( siVector Y, ui sizey, siVector X, ssize_t samp );
overror_t  __vcuf OVCUAPI   cudaVSI_subvector_equC( siVector Y, ui subsz, ui samp, short C );
overror_t  __vcuf OVCUAPI   cusdVSI_subvector_equC( siVector Y, ui subsz, ui samp, short *C );
overror_t  __vcuf OVCUAPI   cudaVSI_subvector_equV( siVector Y, ui subsz, ui samp, siVector X );
overror_t  __vcuf OVCUAPI   cudaVSI_indpick( siVector Y, uiVector Ind, ui sizey, siVector X );
overror_t  __vcuf OVCUAPI   cudaVSI_indput(  siVector Y, siVector X, uiVector Ind, ui sizex );
overror_t  __vcuf OVCUAPI   cudaVSI_searchC( ui *h_Ind, siVector XTab, ui size, short C, int mode );
overror_t  __vcuf OVCUAPI   cusdVSI_searchC( ui *d_Ind, siVector XTab, ui size, short *C, int mode );
overror_t  __vcuf OVCUAPI   cudaVSI_searchV( uiVector Ind, siVector X, ui sizex, siVector Tab, ui sizetab, int mode );


/********************   One-dimensional Vector Operations  ********/

overror_t __vcuf OVCUAPI   cudaVSI_sum( short *h_retVal, siVector X, ui size );
overror_t  __vcuf OVCUAPI   cudaVSI_max( short *h_retVal, siVector X, ui size );
overror_t  __vcuf OVCUAPI   cudaVSI_min( short *h_retVal, siVector X, ui size );
overror_t  __vcuf OVCUAPI   cudaVSI_maxind( short *h_retVal, ui *Ind, siVector X, ui size );
overror_t  __vcuf OVCUAPI   cudaVSI_minind( short *h_retVal, ui *Ind, siVector X, ui size );
overror_t  __vcuf OVCUAPI   cudaVSI_fsum( double *h_retVal, siVector X, ui size );
overror_t  __vcuf OVCUAPI   cudaVSI_mean( double *h_retVal, siVector X, ui size );
overror_t   __vcuf OVCUAPI   cudaVSI_runsum( siVector Y, siVector X, ui size );
overror_t   __vcuf OVCUAPI   cudaVSI_runmax( siVector Y, siVector X, ui size );
overror_t   __vcuf OVCUAPI   cudaVSI_runmin( siVector Y, siVector X, ui size );

overror_t  __vcuf OVCUAPI   cusdVSI_sum( short *d_RetVal, siVector X, ui size );
overror_t  __vcuf OVCUAPI   cusdVSI_max( short *d_RetVal, siVector X, ui size );
overror_t  __vcuf OVCUAPI   cusdVSI_min( short *d_RetVal, siVector X, ui size );
overror_t  __vcuf OVCUAPI   cusdVSI_maxind( short *d_RetVal, ui *Ind, siVector X, ui size );
overror_t  __vcuf OVCUAPI   cusdVSI_minind( short *d_RetVal, ui *Ind, siVector X, ui size );
overror_t  __vcuf OVCUAPI   cusdVSI_fsum( double *d_RetVal, siVector X, ui size );
overror_t  __vcuf OVCUAPI   cusdVSI_mean( double *d_RetVal, siVector X, ui size );

int       __vcuf OVCUAPI   cudaVSI_iselementC( siVector Tab, ui size, short C );
int       __vcuf OVCUAPI   cusdVSI_iselementC( siVector Tab, ui size, short *C );
overror_t __vcuf OVCUAPI   cudaVSI_iselementV( ui *h_nFound, siVector Y, siVector X, ui sizex, siVector Tab, ui sizetab );

overror_t  __vcuf OVCUAPI   cudaVSI_distribution( ui *h_nOutside, uiVector Abund, siVector Limits, ui nbins, siVector X, ui sizex, int mode );
overror_t  __vcuf OVCUAPI   cusdVSI_distribution( ui *d_nOutside, uiVector Abund, siVector Limits, ui nbins, siVector X, ui sizex, int mode );

/***************************  Input and Output *****************************
	The input/output functions involve memory transfers from device
	to host memory or vice versa. The generic cudaVSI_input/output functions
	allocate their own host buffers, whereas the cudaVSI_xxx_buf functions
	take a user-supplied buffer h_Wk and are much more efficient.          */

overror_t  __vf    cudaVSI_fprint( FILE *stream, siVector X, ui size, unsigned nperline, unsigned linewidth );
overror_t  __vf    cudaVSI_cprint( siVector X, ui size, unsigned nperline );
#define       cudaVSI_print( x, sz, npl )  cudaVSI_fprint( stdout, x, sz, npl, 80 )
overror_t  __vf    cudaVSI_fprint_buf( FILE *stream, siVector d_X, ui size, unsigned nperline, unsigned linewidth, siVector h_Wk );
overror_t  __vf    cudaVSI_cprint_buf( siVector d_X, ui size, unsigned nperline, siVector h_Wk );
#define       cudaVSI_print_buf( d_x, sz, npl, h_Wk )  cudaVSI_fprint_buf( stdout, d_x, sz, npl, 80, h_Wk )
 /*  cudaVSI_print, cudaVSI_cprint are usable only for console applications!  */
overror_t  __vf    cudaVSI_write( FILE *stream, siVector X, ui size  );
overror_t  __vf    cudaVSI_read( siVector X, ui size, FILE *stream );
overror_t  __vf    cudaVSI_write_buf( FILE *stream, siVector d_X, ui size, siVector h_Wk );
overror_t  __vf    cudaVSI_read_buf( siVector d_X, ui size, FILE *stream, siVector h_Wk );
                     /* cudaVSI_write, cudaVSI_read in ascii format */
overror_t  __vf     cudaVSI_store( FILE *stream, siVector X, ui size );
overror_t  __vf     cudaVSI_recall( siVector X, ui size, FILE *stream );
overror_t  __vf     cudaVSI_store_buf( FILE *stream, siVector d_X, ui size, siVector h_Wk );
overror_t  __vf     cudaVSI_recall_buf( siVector d_X, ui size, FILE *stream, siVector h_Wk );
                     /* cudaVSI_store, cudaVSI_recall in binary format */


#ifdef __cplusplus
}  // end of extern "C"
#endif

/******************  VSIcu_ functions: **********************************
	act on host memory, using the CUDA device for processing
************************************************************************/


#ifdef __cplusplus
   extern "C" {
#endif

/****************** Initialization  ******************************/

void  __vcuf OVCUAPI   VSIcu_equ0( siVector X, ui size );
void  __vcuf OVCUAPI   VSIcu_equC( siVector X, ui size, short C );
void  __vcuf OVCUAPI   VSIcu_equV( siVector Y, siVector X, ui size ); /* copies from device to device */
void  __vcuf OVCUAPI   VSIcu_ramp( siVector X, ui size, short Start, short Rise );
/* no Vcu_random functions: random generation runs on CPU anyway */


/************** Data-type interconversions  ****************************/

void  __vcuf OVCUAPI   Vcu_BItoSI( siVector Y, biVector X, ui size );  /* up-conversion */
void  __vcuf OVCUAPI   Vcu_SItoI(  iVector  Y, siVector X, ui size );
void  __vcuf OVCUAPI   Vcu_SItoLI( liVector Y, siVector X, ui size );
void  __vcuf OVCUAPI   Vcu_SItoQI( qiVector Y, siVector X, ui size );

void  __vcuf OVCUAPI   Vcu_SItoBI(  biVector Y, siVector X, ui size ); /* down-conversion */
void  __vcuf OVCUAPI   Vcu_SItoUS( usVector Y, siVector X, ui size );
void  __vcuf OVCUAPI   Vcu_UStoSI( siVector Y, usVector X, ui size );
void  __vcuf OVCUAPI   Vcu_ItoSI(  siVector Y, iVector  X, ui size );
void  __vcuf OVCUAPI   Vcu_LItoSI( siVector Y, liVector X, ui size );
void  __vcuf OVCUAPI   Vcu_QItoSI( siVector Y, qiVector X, ui size );

void  __vcuf OVCUAPI   Vcu_SItoF(  fVector Y, siVector X, ui size );
void  __vcuf OVCUAPI   Vcu_SItoD(  dVector Y, siVector X, ui size );

/************** Index-oriented manipulations ***************************/

void  __vcuf OVCUAPI   VSIcu_reflect( siVector X, ui size );
void  __vcuf OVCUAPI   VSIcu_rev( siVector Y, siVector X, ui size );
void  __vcuf OVCUAPI   VSIcu_rotate( siVector Y, siVector X, ui size, ssize_t pos );
void  __vcuf OVCUAPI   VSIcu_rotate_buf( siVector Y, siVector X, ui size, ssize_t pos, siVector Buf );
void  __vcuf OVCUAPI   VSIcu_delete( siVector X, ui size, ui pos );
void  __vcuf OVCUAPI   VSIcu_insert( siVector X, ui size, ui pos, short C );
void  __vcuf OVCUAPI   VSIcu_sort( siVector Y, siVector X, ui size, int dir );
void  __vcuf OVCUAPI   VSIcu_sortind( uiVector Ind, siVector X, ui size, int dir );
void  __vcuf OVCUAPI   VSIcu_subvector( siVector Y, ui sizey, siVector X, ssize_t samp );
void  __vcuf OVCUAPI   VSIcu_subvector_equC( siVector Y, ui subsz, ui samp, short C );
void  __vcuf OVCUAPI   VSIcu_subvector_equV( siVector Y, ui subsz, ui samp, siVector X );
  /* no V?cu_indpick, V?cu_indput possible! */
ui    __vcuf OVCUAPI   VSIcu_searchC( siVector XTab, ui size, short C, int mode );
void  __vcuf OVCUAPI   VSIcu_searchV( uiVector Ind, siVector X, ui sizex, siVector Tab, ui sizetab, int mode );


/********************   One-dimensional Vector Operations  ********/

short  __vcuf OVCUAPI   VSIcu_sum( siVector X, ui size );
short  __vcuf OVCUAPI   VSIcu_max( siVector X, ui size );
short  __vcuf OVCUAPI   VSIcu_min( siVector X, ui size );
short  __vcuf OVCUAPI   VSIcu_maxind( ui *Ind, siVector X, ui size );
short  __vcuf OVCUAPI   VSIcu_minind( ui *Ind, siVector X, ui size );
double __vcuf OVCUAPI   VSIcu_fsum( siVector X, ui size );
double __vcuf OVCUAPI   VSIcu_mean( siVector X, ui size );
void   __vcuf OVCUAPI   VSIcu_runsum( siVector Y, siVector X, ui size );
void   __vcuf OVCUAPI   VSIcu_runmax( siVector Y, siVector X, ui size );
void   __vcuf OVCUAPI   VSIcu_runmin( siVector Y, siVector X, ui size );

int    __vcuf OVCUAPI   VSIcu_iselementC( siVector Tab, ui size, short C );
ui     __vcuf OVCUAPI   VSIcu_iselementV( siVector Y, siVector X, ui sizex, siVector Tab, ui sizetab );
ui     __vcuf OVCUAPI   VSIcu_distribution( uiVector Abund, siVector Limits, ui nbins, siVector X, ui sizex, int mode );

#ifdef __cplusplus
}  // end of extern "C"
#endif

#endif   /*  __CUDAVSISTD_H    */
