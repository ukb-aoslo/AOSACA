/*  cudaVBIstd.h

  vector management functions for byte-size integers.

  Copyright (c) 1996-2017 by OptiCode - Dr. Martin Sander Software Dev.
  All Rights Reserved.
*/

#ifndef __CUDAVBISTD_H
#define __CUDAVBISTD_H  

#if !defined( __CUDAVECLIB_H )
   #include <cudaVecLib.h>
#endif

/******************  cudaVBI_ functions: **********************************
	 act on vectors in CUDA device memory; 
	 scalar parameters and return values on host
******************  cusdVBI_ functions: **********************************
	 also act on vectors in CUDA device memory; 
	 scalar parameters and return values by address on device memory
************************************************************************/

#ifdef __cplusplus
   extern "C" {
#endif

/*************************  Generation ***************************/

biVector  __vf  cudaVBI_vector( ui size );   /* allocates a vector on device memory */
biVector  __vf  cudaVBI_vector0( ui size );
 /* The following functions allocate device-accessible, "pinned" memory on the host.
	This memory is mapped onto the device memory space. The resulting device address is returned.
	The vector can be accessed either by its host address "hostPtr" e.g., VBI_ramp( hostPtr, size, 0, 1 );
	or by its device address , e.g., cudaVBI_ramp( devicePtr, size, 0, 1 );     */
biVector  __vf  cudaVBI_pinnedVector(  biVector *hostPtr, ui size ); 
biVector  __vf  cudaVBI_pinnedVector0( biVector *hostPtr, ui size );


/***************  Addressing single vector elements ******************/

char * __vcuf OVCUAPI cudaVBI_Pelement( biVector X, ui n );
char   __vcuf OVCUAPI cudaVBI_element( biVector X, ui n );
void __vcuf OVCUAPI cudaVBI_getElement( char *y, biVector X, ui n );
void __vcuf OVCUAPI cusdVBI_getElement( char *d_y, biVector X, ui n );
void __vcuf OVCUAPI cudaVBI_setElement( biVector X, ui n, char C );
void __vcuf OVCUAPI cusdVBI_setElement( biVector X, ui n, char *d_C );

/****************** Initialization  ******************************/

overror_t  __vcuf OVCUAPI   cudaVBI_equ0( biVector X, ui size );
overror_t  __vcuf OVCUAPI   cudaVBI_equC( biVector X, ui size, char C );
overror_t  __vcuf OVCUAPI   cusdVBI_equC( biVector X, ui size, char *C );
overror_t  __vcuf OVCUAPI   cudaVBI_equV( biVector Y, biVector X, ui size ); /* copies from device to device */
overror_t  __vcuf OVCUAPI   cudaVBI_equVhost( biVector Y, biVector X, ui size );  /* copies from host to device */
overror_t  __vcuf OVCUAPI   VBI_equVdevice( biVector Y, biVector X, ui size );  /* copies from device to host */
overror_t  __vcuf OVCUAPI   cudaVBI_ramp( biVector X, ui size, char Start, char Rise );
overror_t  __vcuf OVCUAPI   cusdVBI_ramp( biVector X, ui size, char *Start, char *Rise );

/******  Linear Congruential random generator with Bays-Durham shuffle:  ***********
  Random series is generated on the CPU. State must be stored in host memory!
  seed!=0 --> initialization of state. seed==0 --> continue series from previous call with the same state. */
overror_t  __vcuf OVCUAPI  cudaVBI_randomLC( biVector X, ui size, long seed, char MinVal, char MaxVal, V_RANDOMLCSTATE *state );
overror_t  __vcuf OVCUAPI  cusdVBI_randomLC( biVector X, ui size, long seed, char *MinVal, char *MaxVal, V_RANDOMLCSTATE *state );
/**  simplified version: Series cannot be made continuous across calls: */
overror_t  __vcuf OVCUAPI  cudaVBI_random( biVector X, ui size, long seed, char MinVal, char MaxVal );
overror_t  __vcuf OVCUAPI  cusdVBI_random( biVector X, ui size, long seed, char *MinVal, char *MaxVal );


/************** Data-type overror_terconversions  ****************************/

overror_t  __vcuf OVCUAPI   cudaV_BItoUB( ubVector Y, biVector X, ui size ); /* signed-unsigned */
overror_t  __vcuf OVCUAPI   cudaV_UBtoBI( biVector Y, ubVector X, ui size );

overror_t  __vcuf OVCUAPI   cudaV_BItoI(  iVector  Y, biVector X, ui size );  /* up-conversion */
overror_t  __vcuf OVCUAPI   cudaV_BItoSI( siVector Y, biVector X, ui size );
overror_t  __vcuf OVCUAPI   cudaV_BItoLI( liVector Y, biVector X, ui size );
overror_t  __vcuf OVCUAPI   cudaV_BItoQI( qiVector Y, biVector X, ui size );

overror_t  __vcuf OVCUAPI   cudaV_SItoBI( biVector Y, siVector  X, ui size );/* down-conversion */
overror_t  __vcuf OVCUAPI   cudaV_ItoBI(  biVector Y, iVector  X, ui size );
overror_t  __vcuf OVCUAPI   cudaV_LItoBI( biVector Y, liVector X, ui size );
overror_t  __vcuf OVCUAPI   cudaV_QItoBI( biVector Y, qiVector X, ui size );

overror_t  __vcuf OVCUAPI   cudaV_BItoF(  fVector Y, biVector X, ui size );
overror_t  __vcuf OVCUAPI   cudaV_BItoD(  dVector Y, biVector X, ui size );

/************** Index-oriented manipulations ***************************/

overror_t  __vcuf OVCUAPI   cudaVBI_reflect( biVector X, ui size );
overror_t  __vcuf OVCUAPI   cudaVBI_rev( biVector Y, biVector X, ui size );
overror_t  __vcuf OVCUAPI   cudaVBI_rotate( biVector Y, biVector X, ui size, ssize_t pos );
overror_t  __vcuf OVCUAPI   cudaVBI_rotate_buf( biVector Y, biVector X, ui size, ssize_t pos, biVector Buf );

overror_t  __vcuf OVCUAPI   cudaVBI_delete( biVector X, ui size, ui pos );
overror_t  __vcuf OVCUAPI   cudaVBI_insert( biVector X, ui size, ui pos, char C );
overror_t  __vcuf OVCUAPI   cusdVBI_insert( biVector X, ui size, ui pos, char *C );
overror_t  __vcuf OVCUAPI   cudaVBI_sort( biVector Y, biVector X, ui size, int dir );
overror_t  __vcuf OVCUAPI   cudaVBI_sortind( uiVector Ind, biVector X, ui size, int dir );

overror_t  __vcuf OVCUAPI   cudaVBI_subvector( biVector Y, ui sizey, biVector X, ssize_t samp );
overror_t  __vcuf OVCUAPI   cudaVBI_subvector_equC( biVector Y, ui subsz, ui samp, char C );
overror_t  __vcuf OVCUAPI   cusdVBI_subvector_equC( biVector Y, ui subsz, ui samp, char *C );
overror_t  __vcuf OVCUAPI   cudaVBI_subvector_equV( biVector Y, ui subsz, ui samp, biVector X );

overror_t  __vcuf OVCUAPI   cudaVBI_indpick( biVector Y, uiVector Ind, ui sizey, biVector X );
overror_t  __vcuf OVCUAPI   cudaVBI_indput(  biVector Y, biVector X, uiVector Ind, ui sizex );
overror_t  __vcuf OVCUAPI   cudaVBI_searchC( ui *h_Ind, biVector XTab, ui size, char C, int mode );
overror_t  __vcuf OVCUAPI   cusdVBI_searchC( ui *d_Ind, biVector XTab, ui size, char *C, int mode );
overror_t  __vcuf OVCUAPI   cudaVBI_searchV( uiVector Ind, biVector X, ui sizex, biVector Tab, ui sizetab, int mode );


/********************   One-dimensional Vector Operations  ********/

overror_t  __vcuf OVCUAPI   cudaVBI_sum( char *h_RetVal, biVector X, ui size );
overror_t  __vcuf OVCUAPI   cudaVBI_max( char *h_RetVal, biVector X, ui size );
overror_t  __vcuf OVCUAPI   cudaVBI_min( char *h_RetVal, biVector X, ui size );
overror_t  __vcuf OVCUAPI   cudaVBI_maxind( char *h_RetVal, ui *Ind, biVector X, ui size );
overror_t  __vcuf OVCUAPI   cudaVBI_minind( char *h_RetVal, ui *Ind, biVector X, ui size );
overror_t  __vcuf OVCUAPI   cudaVBI_fsum( double *h_RetVal, biVector X, ui size );
overror_t  __vcuf OVCUAPI   cudaVBI_mean( double *h_RetVal, biVector X, ui size );
overror_t   __vcuf OVCUAPI   cudaVBI_runsum( biVector Y, biVector X, ui size );
overror_t   __vcuf OVCUAPI   cudaVBI_runmax( biVector Y, biVector X, ui size );
overror_t   __vcuf OVCUAPI   cudaVBI_runmin( biVector Y, biVector X, ui size );

overror_t  __vcuf OVCUAPI   cusdVBI_sum( char *d_RetVal, biVector X, ui size );
overror_t  __vcuf OVCUAPI   cusdVBI_max( char *d_RetVal, biVector X, ui size );
overror_t  __vcuf OVCUAPI   cusdVBI_min( char *d_RetVal, biVector X, ui size );
overror_t  __vcuf OVCUAPI   cusdVBI_maxind( char *d_RetVal, ui *Ind, biVector X, ui size );
overror_t  __vcuf OVCUAPI   cusdVBI_minind( char *d_RetVal, ui *Ind, biVector X, ui size );
overror_t  __vcuf OVCUAPI   cusdVBI_fsum( double *d_RetVal, biVector X, ui size );
overror_t  __vcuf OVCUAPI   cusdVBI_mean( double *d_RetVal, biVector X, ui size );

int       __vcuf OVCUAPI   cudaVBI_iselementC( biVector Tab, ui size, char C );
int       __vcuf OVCUAPI   cusdVBI_iselementC( biVector Tab, ui size, char *C );
overror_t __vcuf OVCUAPI   cudaVBI_iselementV( ui *h_nFound, biVector Y, biVector X, ui sizex, biVector Tab, ui sizetab );

overror_t  __vcuf OVCUAPI   cudaVBI_distribution( ui *h_nOutside, uiVector Abund, biVector Limits, ui nbins, biVector X, ui sizex, int mode );
overror_t  __vcuf OVCUAPI   cusdVBI_distribution( ui *d_nOutside, uiVector Abund, biVector Limits, ui nbins, biVector X, ui sizex, int mode );

/***************************  Input and Output *****************************
	The input/output functions involve memory transfers from device
	to host memory or vice versa. The generic cudaVBI_input/output functions
	allocate their own host buffers, whereas the cudaVBI_xxx_buf functions
	take a user-supplied buffer h_Wk and are much more efficient.          */

overror_t  __vf    cudaVBI_fprint( FILE *stream, biVector X, ui size, unsigned nperline, unsigned linewidth );
overror_t  __vf    cudaVBI_cprint( biVector X, ui size, unsigned nperline );
#define       cudaVBI_print( x, sz, npl )  cudaVBI_fprint( stdout, x, sz, npl, 80 )
overror_t  __vf    cudaVBI_fprint_buf( FILE *stream, biVector d_X, ui size, unsigned nperline, unsigned linewidth, biVector h_Wk );
overror_t  __vf    cudaVBI_cprint_buf( biVector d_X, ui size, unsigned nperline, biVector h_Wk );
#define       cudaVBI_print_buf( d_x, sz, npl, h_Wk )  cudaVBI_fprint_buf( stdout, d_x, sz, npl, 80, h_Wk )
 /*  cudaVBI_print, cudaVBI_cprint are usable only for console applications!  */
overror_t  __vf    cudaVBI_write( FILE *stream, biVector X, ui size  );
overror_t  __vf    cudaVBI_read( biVector X, ui size, FILE *stream );
overror_t  __vf    cudaVBI_write_buf( FILE *stream, biVector d_X, ui size, biVector h_Wk );
overror_t  __vf    cudaVBI_read_buf( biVector d_X, ui size, FILE *stream, biVector h_Wk );
                     /* cudaVBI_write, cudaVBI_read in ascii format */
overror_t  __vf    cudaVBI_store( FILE *stream, biVector X, ui size );
overror_t  __vf    cudaVBI_recall( biVector X, ui size, FILE *stream );
overror_t  __vf    cudaVBI_store_buf( FILE *stream, biVector d_X, ui size, biVector h_Wk );
overror_t  __vf    cudaVBI_recall_buf( biVector d_X, ui size, FILE *stream, biVector h_Wk );
                     /* cudaVBI_store, cudaVBI_recall in binary format */


#ifdef __cplusplus
}  // end of extern "C"
#endif

/******************  VBIcu_ functions: **********************************
	act on host memory, using the CUDA device for processing
************************************************************************/

#ifdef __cplusplus
   extern "C" {
#endif

/****************** Initialization  ******************************/

void  __vcuf OVCUAPI   VBIcu_equ0( biVector X, ui size );
void  __vcuf OVCUAPI   VBIcu_equC( biVector X, ui size, char C );
void  __vcuf OVCUAPI   VBIcu_equV( biVector Y, biVector X, ui size ); /* copies from device to device */
void  __vcuf OVCUAPI   VBIcu_ramp( biVector X, ui size, char Start, char Rise );
/* no Vcu_random functions: random generation runs on CPU anyway */


/************** Data-type interconversions  ****************************/

void  __vcuf OVCUAPI   Vcu_BItoUB( ubVector Y, biVector X, ui size ); /* signed-unsigned */
void  __vcuf OVCUAPI   Vcu_UBtoBI( biVector Y, ubVector X, ui size );

void  __vcuf OVCUAPI   Vcu_BItoI(  iVector  Y, biVector X, ui size );  /* up-conversion */
void  __vcuf OVCUAPI   Vcu_BItoSI( siVector Y, biVector X, ui size );
void  __vcuf OVCUAPI   Vcu_BItoLI( liVector Y, biVector X, ui size );
void  __vcuf OVCUAPI   Vcu_BItoQI( qiVector Y, biVector X, ui size );

void  __vcuf OVCUAPI   Vcu_SItoBI( biVector Y, siVector  X, ui size );/* down-conversion */
void  __vcuf OVCUAPI   Vcu_ItoBI(  biVector Y, iVector  X, ui size );
void  __vcuf OVCUAPI   Vcu_LItoBI( biVector Y, liVector X, ui size );
void  __vcuf OVCUAPI   Vcu_QItoBI( biVector Y, qiVector X, ui size );

void  __vcuf OVCUAPI   Vcu_BItoF(  fVector Y, biVector X, ui size );
void  __vcuf OVCUAPI   Vcu_BItoD(  dVector Y, biVector X, ui size );

/************** Index-oriented manipulations ***************************/

void  __vcuf OVCUAPI   VBIcu_reflect( biVector X, ui size );
void  __vcuf OVCUAPI   VBIcu_rev( biVector Y, biVector X, ui size );
void  __vcuf OVCUAPI   VBIcu_rotate( biVector Y, biVector X, ui size, ssize_t pos );
void  __vcuf OVCUAPI   VBIcu_rotate_buf( biVector Y, biVector X, ui size, ssize_t pos, biVector Buf );

void  __vcuf OVCUAPI   VBIcu_delete( biVector X, ui size, ui pos );
void  __vcuf OVCUAPI   VBIcu_insert( biVector X, ui size, ui pos, char C );
void  __vcuf OVCUAPI   VBIcu_sort( biVector Y, biVector X, ui size, int dir );
void  __vcuf OVCUAPI   VBIcu_sortind( uiVector Ind, biVector X, ui size, int dir );

void  __vcuf OVCUAPI   VBIcu_subvector( biVector Y, ui sizey, biVector X, ssize_t samp );
void  __vcuf OVCUAPI   VBIcu_subvector_equC( biVector Y, ui subsz, ui samp, char C );
void  __vcuf OVCUAPI   VBIcu_subvector_equV( biVector Y, ui subsz, ui samp, biVector X );

  /* no V?cu_indpick, V?cu_indput possible! */
ui    __vcuf OVCUAPI   VBIcu_searchC( biVector XTab, ui size, char C, int mode );
void  __vcuf OVCUAPI   VBIcu_searchV( uiVector Ind, biVector X, ui sizex, biVector Tab, ui sizetab, int mode );


/********************   One-dimensional Vector Operations  ********/

char  __vcuf OVCUAPI   VBIcu_sum( biVector X, ui size );
char  __vcuf OVCUAPI   VBIcu_max( biVector X, ui size );
char  __vcuf OVCUAPI   VBIcu_min( biVector X, ui size );
char  __vcuf OVCUAPI   VBIcu_maxind( ui *Ind, biVector X, ui size );
char  __vcuf OVCUAPI   VBIcu_minind( ui *Ind, biVector X, ui size );
double __vcuf OVCUAPI   VBIcu_fsum( biVector X, ui size );
double __vcuf OVCUAPI   VBIcu_mean( biVector X, ui size );
void   __vcuf OVCUAPI   VBIcu_runsum( biVector Y, biVector X, ui size );
void   __vcuf OVCUAPI   VBIcu_runmax( biVector Y, biVector X, ui size );
void   __vcuf OVCUAPI   VBIcu_runmin( biVector Y, biVector X, ui size );

int    __vcuf OVCUAPI   VBIcu_iselementC( biVector Tab, ui size, char C );
ui     __vcuf OVCUAPI   VBIcu_iselementV( biVector Y, biVector X, ui sizex, biVector Tab, ui sizetab );
ui     __vcuf OVCUAPI   VBIcu_distribution( uiVector Abund, biVector Limits, ui nbins, biVector X, ui sizex, int mode );

#ifdef __cplusplus
}  // end of extern "C"
#endif

#endif   /*  __CUDAVBISTD_H    */
