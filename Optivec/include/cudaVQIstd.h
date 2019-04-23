/*  cudaVQIstd.h

  vector management functions for data type "quad".

  Copyright (c) 1996-2017 by OptiCode - Dr. Martin Sander Software Dev.
  All Rights Reserved.
*/

#ifndef __CUDAVQISTD_H
#define __CUDAVQISTD_H

#if !defined( __CUDAVECLIB_H )
   #include <cudaVecLib.h>
#endif

/******************  cudaVQI_ functions: **********************************
	 act on vectors in CUDA device memory; 
	 scalar parameters and return values on host
******************  cusdVQI_ functions: **********************************
	 also act on vectors in CUDA device memory; 
	 scalar parameters and return values by address on device memory
************************************************************************/

#ifdef __cplusplus
   extern "C" {
#endif

/************************  Generation ******************************/

qiVector  __vf  cudaVQI_vector( ui size );   /* allocates a vector on device memory */
qiVector  __vf  cudaVQI_vector0( ui size );
 /* The following functions allocate device-accessible, "pinned" memory on the host.
	This memory is mapped onto the device memory space. The resulting device address is returned.
	The vector can be accessed either by its host address "hostPtr" e.g., VQI_ramp( hostPtr, size, 0, 1 );
	or by its device address , e.g., cudaVQI_ramp( devicePtr, size, 0, 1 );     */
qiVector  __vf  cudaVQI_pinnedVector(  qiVector *hostPtr, ui size ); 
qiVector  __vf  cudaVQI_pinnedVector0( qiVector *hostPtr, ui size );

/***************  Addressing single vector elements ******************/

quad * __vcuf OVCUAPI cudaVQI_Pelement( qiVector X, ui n );
quad   __vcuf OVCUAPI cudaVQI_element( qiVector X, ui n );
void   __vcuf OVCUAPI cudaVQI_getElement( quad *y, qiVector X, ui n );
void   __vcuf OVCUAPI cusdVQI_getElement( quad *d_y, qiVector X, ui n );
void   __vcuf OVCUAPI cudaVQI_setElement( qiVector X, ui n, quad C );
void   __vcuf OVCUAPI cusdVQI_setElement( qiVector X, ui n, quad *C );

/****************** Initialization  ******************************/

overror_t  __vcuf OVCUAPI   cudaVQI_equ0( qiVector X, ui size );
overror_t  __vcuf OVCUAPI   cudaVQI_equC( qiVector X, ui size, quad C );
overror_t  __vcuf OVCUAPI   cusdVQI_equC( qiVector X, ui size, quad *C );
overror_t  __vcuf OVCUAPI   cudaVQI_equV( qiVector Y, qiVector X, ui size ); /* copies from device to device */
overror_t  __vcuf OVCUAPI   cudaVQI_equVhost( qiVector Y, qiVector X, ui size );  /* copies from host to device */
overror_t  __vcuf OVCUAPI   VQI_equVdevice( qiVector Y, qiVector X, ui size );  /* copies from device to host */
overror_t  __vcuf OVCUAPI   cudaVQI_ramp( qiVector X, ui size, quad Start, quad Rise );
overror_t  __vcuf OVCUAPI   cusdVQI_ramp( qiVector X, ui size, quad *Start, quad *Rise );

/******  Linear Congruential random generator with Bays-Durham shuffle:  ***********
  Random series is generated on the CPU. State must be stored in host memory!
  seed!=0 --> initialization of state. seed==0 --> continue series from previous call with the same state. */
overror_t  __vcuf OVCUAPI  cudaVQI_randomLC( qiVector X, ui size, long seed, quad MinVal, quad MaxVal, V_RANDOMLCSTATE *state );
overror_t  __vcuf OVCUAPI  cusdVQI_randomLC( qiVector X, ui size, long seed, quad *MinVal, quad *MaxVal, V_RANDOMLCSTATE *state );
/**  simplified version: Series cannot be made continuous across calls: */
overror_t  __vcuf OVCUAPI  cudaVQI_random( qiVector X, ui size, long seed, quad MinVal, quad MaxVal );
overror_t  __vcuf OVCUAPI  cusdVQI_random( qiVector X, ui size, long seed, quad *MinVal, quad *MaxVal );


/************** Data-type interconversions  ***************************/

#if defined _WIN64  /* signed - unsigned conversion available only for Win64 */
    overror_t __vcuf OVCUAPI   cudaV_UQtoQI( qiVector Y, uqVector  X, ui size );
    overror_t __vcuf OVCUAPI   cudaV_QItoUQ( uqVector Y, qiVector X, ui size );
#endif

overror_t  __vcuf OVCUAPI   cudaV_BItoQI( qiVector Y, biVector X, ui size );  /* up-conversion */
overror_t  __vcuf OVCUAPI   cudaV_SItoQI( qiVector Y, siVector X, ui size );
overror_t  __vcuf OVCUAPI   cudaV_ItoQI(  qiVector Y, iVector  X, ui size );
overror_t  __vcuf OVCUAPI   cudaV_LItoQI( qiVector Y, liVector X, ui size );

overror_t  __vcuf OVCUAPI   cudaV_QItoBI(  biVector Y, qiVector X, ui size ); /* down-conversion */
overror_t  __vcuf OVCUAPI   cudaV_QItoSI( siVector Y, qiVector X, ui size );
overror_t  __vcuf OVCUAPI   cudaV_QItoI(  iVector  Y, qiVector X, ui size );
overror_t  __vcuf OVCUAPI   cudaV_QItoLI( liVector Y, qiVector X, ui size );

overror_t  __vcuf OVCUAPI   cudaV_QItoF(  fVector Y, qiVector X, ui size );
overror_t  __vcuf OVCUAPI   cudaV_QItoD(  dVector Y, qiVector X, ui size );


/************** Index-oriented manipqiations ***************************/

overror_t  __vcuf OVCUAPI   cudaVQI_reflect( qiVector X, ui size );
overror_t  __vcuf OVCUAPI   cudaVQI_rev( qiVector Y, qiVector X, ui size );
overror_t  __vcuf OVCUAPI   cudaVQI_rotate( qiVector Y, qiVector X, ui size, ssize_t pos );
overror_t  __vcuf OVCUAPI   cudaVQI_rotate_buf( qiVector Y, qiVector X, ui size, ssize_t pos, qiVector Buf );
overror_t  __vcuf OVCUAPI   cudaVQI_delete( qiVector X, ui size, ui pos );
overror_t  __vcuf OVCUAPI   cudaVQI_insert( qiVector X, ui size, ui pos, quad C );
overror_t  __vcuf OVCUAPI   cusdVQI_insert( qiVector X, ui size, ui pos, quad *C );
overror_t  __vcuf OVCUAPI   cudaVQI_sort( qiVector Y, qiVector X, ui size, int dir );
overror_t  __vcuf OVCUAPI   cudaVQI_sortind( uiVector Ind, qiVector X, ui size, int dir );

overror_t  __vcuf OVCUAPI   cudaVQI_subvector( qiVector Y, ui sizey, qiVector X, ssize_t samp );
overror_t  __vcuf OVCUAPI   cudaVQI_subvector_equC( qiVector Y, ui subsz, ui samp, quad C );
overror_t  __vcuf OVCUAPI   cusdVQI_subvector_equC( qiVector Y, ui subsz, ui samp, quad *C );
overror_t  __vcuf OVCUAPI   cudaVQI_subvector_equV( qiVector Y, ui subsz, ui samp, qiVector X );
overror_t  __vcuf OVCUAPI   cudaVQI_indpick( qiVector Y, uiVector Ind, ui sizey, qiVector X );
overror_t  __vcuf OVCUAPI   cudaVQI_indput(  qiVector Y, qiVector X, uiVector Ind, ui sizex );
overror_t  __vcuf OVCUAPI   cudaVQI_searchC( ui *h_Ind, qiVector XTab, ui size, quad C, int mode );
overror_t  __vcuf OVCUAPI   cusdVQI_searchC( ui *d_Ind, qiVector XTab, ui size, quad *C, int mode );
overror_t  __vcuf OVCUAPI   cudaVQI_searchV( uiVector Ind, qiVector X, ui sizex, qiVector Tab, ui sizetab, int mode );


/********************   One-dimensional Vector Operations  ********/

overror_t  __vcuf OVCUAPI   cudaVQI_sum( quad *h_RetVal, qiVector X, ui size );
overror_t  __vcuf OVCUAPI   cudaVQI_max( quad *h_RetVal, qiVector X, ui size );
overror_t  __vcuf OVCUAPI   cudaVQI_min( quad *h_RetVal, qiVector X, ui size );
overror_t  __vcuf OVCUAPI   cudaVQI_maxind( quad *h_RetVal, ui *Ind, qiVector X, ui size );
overror_t  __vcuf OVCUAPI   cudaVQI_minind( quad *h_RetVal, ui *Ind, qiVector X, ui size );
overror_t  __vcuf OVCUAPI   cudaVQI_fsum( double *h_RetVal, qiVector X, ui size );
overror_t  __vcuf OVCUAPI   cudaVQI_mean( double *h_RetVal, qiVector X, ui size );
overror_t   __vcuf OVCUAPI   cudaVQI_runsum( qiVector Y, qiVector X, ui size );
overror_t   __vcuf OVCUAPI   cudaVQI_runmax( qiVector Y, qiVector X, ui size );
overror_t   __vcuf OVCUAPI   cudaVQI_runmin( qiVector Y, qiVector X, ui size );

overror_t  __vcuf OVCUAPI   cusdVQI_sum( quad *d_RetVal, qiVector X, ui size );
overror_t  __vcuf OVCUAPI   cusdVQI_max( quad *d_RetVal, qiVector X, ui size );
overror_t  __vcuf OVCUAPI   cusdVQI_min( quad *d_RetVal, qiVector X, ui size );
overror_t  __vcuf OVCUAPI   cusdVQI_maxind( quad *d_RetVal, ui *Ind, qiVector X, ui size );
overror_t  __vcuf OVCUAPI   cusdVQI_minind( quad *d_RetVal, ui *Ind, qiVector X, ui size );
overror_t  __vcuf OVCUAPI   cusdVQI_fsum( double *d_RetVal, qiVector X, ui size );
overror_t  __vcuf OVCUAPI   cusdVQI_mean( double *d_RetVal, qiVector X, ui size );


int        __vcuf OVCUAPI   cudaVQI_iselementC( qiVector Tab, ui size, quad C );
int        __vcuf OVCUAPI   cusdVQI_iselementC( qiVector Tab, ui size, quad *C );
overror_t  __vcuf OVCUAPI   cudaVQI_iselementV( ui *h_nFound, qiVector Y, qiVector X, ui sizex, qiVector Tab, ui sizetab );

overror_t  __vcuf OVCUAPI   cudaVQI_distribution( ui *h_nOutside, uiVector Abund, qiVector Limits, ui nbins, qiVector X, ui sizex, int mode );
overror_t  __vcuf OVCUAPI   cusdVQI_distribution( ui *d_nOutside, uiVector Abund, qiVector Limits, ui nbins, qiVector X, ui sizex, int mode );

/***************************  Input and Output *****************************
	The input/output functions involve memory transfers from device
	to host memory or vice versa. The generic cudaVF_input/output functions
	allocate their own host buffers, whereas the cudaVQI_xxx_buf functions
	take a user-supplied buffer h_Wk and are much more efficient.          */

#if ((defined __BORLANDC__) && (__BORLANDC__ >= 0x570)) || ((defined _MSC_VER) && (_MSC_VER >= 1400))
		/* modern compiler versions:  */
	overror_t  __vf    cudaVQI_fprint( FILE *stream, qiVector X, ui size, unsigned nperline, unsigned linewidth );
	overror_t  __vf    cudaVQI_cprint( qiVector X, ui size, unsigned nperline );
	#define       cudaVQI_print( x, sz, npl )  cudaVQI_fprint( stdout, x, sz, npl, 80 )
	overror_t  __vf    cudaVQI_fprint_buf( FILE *stream, qiVector d_X, ui size, unsigned nperline, unsigned linewidth, qiVector h_Wk );
	overror_t  __vf    cudaVQI_cprint_buf( qiVector d_X, ui size, unsigned nperline, qiVector h_Wk );
	#define       cudaVQI_print_buf( d_x, sz, npl, h_Wk )  cudaVQI_fprint_buf( stdout, d_x, sz, npl, 80, h_Wk )
	/*  cudaVQI_print, cudaVQI_cprint are usable only for console applications!  */
	overror_t  __vf    cudaVQI_write( FILE *stream, qiVector X, ui size  );
	overror_t  __vf    cudaVQI_write_buf( FILE *stream, qiVector d_X, ui size, qiVector h_Wk );
                     /* cudaVQI_write, cudaVQI_read in ascii format */
#else /* older compiler versions need separate implementation */
	overror_t  __vf    cudaVQI_fprint1( FILE *stream, qiVector X, ui size, unsigned nperline, unsigned linewidth );
	#define cudaVQI_fprint cudaVQI_fprint1
	overror_t  __vf    cudaVQI_cprint1( qiVector X, ui size, unsigned nperline );
	#define cudaVQI_cprint cudaVQI_cprint1
	#define       cudaVQI_print( x, sz, npl )  cudaVQI_fprint1( stdout, x, sz, npl, 80 )
	overror_t  __vf    cudaVQI_fprint1_buf( FILE *stream, qiVector d_X, ui size, unsigned nperline, unsigned linewidth, qiVector h_Wk );
	#define cudaVQI_fprint_buf cudaVQI_fprint1_buf
	overror_t  __vf    cudaVQI_cprint1_buf( qiVector d_X, ui size, unsigned nperline, qiVector h_Wk );
	#define cudaVQI_cprint_buf cudaVQI_cprint1_buf
	#define       cudaVQI_print_buf( d_x, sz, npl, h_Wk )  cudaVQI_fprint1_buf( stdout, d_x, sz, npl, 80, h_Wk )
	/*  cudaVQI_print, cudaVQI_cprint are usable only for console applications!  */
	overror_t  __vf    cudaVQI_write1( FILE *stream, qiVector X, ui size  );
	#define cudaVQI_write cudaVQI_write1
	overror_t  __vf    cudaVQI_write_buf( FILE *stream, qiVector d_X, ui size, qiVector h_Wk );
	#define cudaVQI_write_buf cudaVQI_write1_buf
#endif
#if !(((defined __BORLANDC__) && (__BORLANDC__ < 0x600)))
	overror_t  __vf    cudaVQI_read( qiVector X, ui size, FILE *stream );
	overror_t  __vf    cudaVQI_read_buf( qiVector d_X, ui size, FILE *stream, qiVector h_Wk );
#else  /* old versions of Borland C need different implementation: */
	overror_t  __vf    cudaVQI_read1( qiVector X, ui size, FILE *stream );
	overror_t  __vf    cudaVQI_read1_buf( qiVector d_X, ui size, FILE *stream, qiVector h_Wk );
	#define cudaVQI_read     cudaVQI_read1
	#define cudaVQI_read_buf cudaVQI_read1_buf
#endif

overror_t  __vf     cudaVQI_store( FILE *stream, qiVector X, ui size );
overror_t  __vf     cudaVQI_recall( qiVector X, ui size, FILE *stream );
overror_t  __vf     cudaVQI_store_buf( FILE *stream, qiVector d_X, ui size, qiVector h_Wk );
overror_t  __vf     cudaVQI_recall_buf( qiVector d_X, ui size, FILE *stream, qiVector h_Wk );
                     /* cudaVQI_store, cudaVQI_recall in binary format */


#ifdef __cplusplus
}  // end of extern "C"
#endif

/******************  VQIcu_ functions: **********************************
	act on host memory, using the CUDA device for processing
************************************************************************/


#ifdef __cplusplus
   extern "C" {
#endif

/****************** Initialization  ******************************/

void  __vcuf OVCUAPI   VQIcu_equ0( qiVector X, ui size );
void  __vcuf OVCUAPI   VQIcu_equC( qiVector X, ui size, quad C );
void  __vcuf OVCUAPI   VQIcu_equV( qiVector Y, qiVector X, ui size ); /* copies from device to device */
void  __vcuf OVCUAPI   VQIcu_ramp( qiVector X, ui size, quad Start, quad Rise );
/* no Vcu_random functions: random generation runs on CPU anyway */


/************** Data-type interconversions  ***************************/

#if defined _WIN64  /* signed - unsigned conversion available only for Win64 */
    void __vcuf OVCUAPI   Vcu_UQtoQI( qiVector Y, uqVector  X, ui size );
    void __vcuf OVCUAPI   Vcu_QItoUQ( uqVector Y, qiVector X, ui size );
#endif

void  __vcuf OVCUAPI   Vcu_BItoQI( qiVector Y, biVector X, ui size );  /* up-conversion */
void  __vcuf OVCUAPI   Vcu_SItoQI( qiVector Y, siVector X, ui size );
void  __vcuf OVCUAPI   Vcu_ItoQI(  qiVector Y, iVector  X, ui size );
void  __vcuf OVCUAPI   Vcu_LItoQI( qiVector Y, liVector X, ui size );

void  __vcuf OVCUAPI   Vcu_QItoBI(  biVector Y, qiVector X, ui size ); /* down-conversion */
void  __vcuf OVCUAPI   Vcu_QItoSI( siVector Y, qiVector X, ui size );
void  __vcuf OVCUAPI   Vcu_QItoI(  iVector  Y, qiVector X, ui size );
void  __vcuf OVCUAPI   Vcu_QItoLI( liVector Y, qiVector X, ui size );

void  __vcuf OVCUAPI   Vcu_QItoF(  fVector Y, qiVector X, ui size );
void  __vcuf OVCUAPI   Vcu_QItoD(  dVector Y, qiVector X, ui size );


/************** Index-oriented manipqiations ***************************/

void  __vcuf OVCUAPI   VQIcu_reflect( qiVector X, ui size );
void  __vcuf OVCUAPI   VQIcu_rev( qiVector Y, qiVector X, ui size );
void  __vcuf OVCUAPI   VQIcu_rotate( qiVector Y, qiVector X, ui size, ssize_t pos );
void  __vcuf OVCUAPI   VQIcu_rotate_buf( qiVector Y, qiVector X, ui size, ssize_t pos, qiVector Buf );
void  __vcuf OVCUAPI   VQIcu_delete( qiVector X, ui size, ui pos );
void  __vcuf OVCUAPI   VQIcu_insert( qiVector X, ui size, ui pos, quad C );
void  __vcuf OVCUAPI   VQIcu_sort( qiVector Y, qiVector X, ui size, int dir );
void  __vcuf OVCUAPI   VQIcu_sortind( uiVector Ind, qiVector X, ui size, int dir );

void  __vcuf OVCUAPI   VQIcu_subvector( qiVector Y, ui sizey, qiVector X, ssize_t samp );
void  __vcuf OVCUAPI   VQIcu_subvector_equC( qiVector Y, ui subsz, ui samp, quad C );
void  __vcuf OVCUAPI   VQIcu_subvector_equV( qiVector Y, ui subsz, ui samp, qiVector X );
  /* no V?cu_indpick, V?cu_indput possible! */
ui    __vcuf OVCUAPI   VQIcu_searchC( qiVector XTab, ui size, quad C, int mode );
void  __vcuf OVCUAPI   VQIcu_searchV( uiVector Ind, qiVector X, ui sizex, qiVector Tab, ui sizetab, int mode );


/********************   One-dimensional Vector Operations  ********/

quad   __vcuf OVCUAPI   VQIcu_sum( qiVector X, ui size );
quad   __vcuf OVCUAPI   VQIcu_max( qiVector X, ui size );
quad   __vcuf OVCUAPI   VQIcu_min( qiVector X, ui size );
quad   __vcuf OVCUAPI   VQIcu_maxind( ui *Ind, qiVector X, ui size );
quad   __vcuf OVCUAPI   VQIcu_minind( ui *Ind, qiVector X, ui size );
double __vcuf OVCUAPI   VQIcu_fsum( qiVector X, ui size );
double __vcuf OVCUAPI   VQIcu_mean( qiVector X, ui size );
void   __vcuf OVCUAPI   VQIcu_runsum( qiVector Y, qiVector X, ui size );
void   __vcuf OVCUAPI   VQIcu_runmax( qiVector Y, qiVector X, ui size );
void   __vcuf OVCUAPI   VQIcu_runmin( qiVector Y, qiVector X, ui size );

int    __vcuf OVCUAPI   VQIcu_iselementC( qiVector Tab, ui size, quad C );
ui     __vcuf OVCUAPI   VQIcu_iselementV( qiVector Y, qiVector X, ui sizex, qiVector Tab, ui sizetab );

ui     __vcuf OVCUAPI   VQIcu_distribution( uiVector Abund, qiVector Limits, ui nbins, qiVector X, ui sizex, int mode );

#ifdef __cplusplus
}  // end of extern "C"
#endif

#endif   /*  __CUDAVQISTD_H    */
