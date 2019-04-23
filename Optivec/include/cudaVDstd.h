/*  cudaVDstd.h

  vector management functions:
  manipulations on whole arrays or vectors of data type "double"
  (real numbers)

  Copyright (c) 1996-2017 by OptiCode - Dr. Martin Sander Software Dev.
  All Rights Reserved.
*/

#ifndef __CUDAVDSTD_H
#define __CUDAVDSTD_H
#if !defined( __CUDAVECLIB_H )
#include <cudaVecLib.h>
#endif
#if !defined( __VDSTD_H )
#include <VDstd.h>
#endif


/******************  cudaVD_ functions: **********************************
	 act on vectors in CUDA device memory; 
	 scalar parameters and return values on host
******************  cusdVD_ functions: **********************************
	 also act on vectors in CUDA device memory; 
	 scalar parameters and return values by address on device memory
************************************************************************/

#ifdef __cplusplus
extern "C" {
#endif

/*************************  Generation  **************************/

dVector  __vf cudaVD_vector( ui size );    /* allocates a vector on device memory  */
dVector  __vf cudaVD_vector0( ui size );
/* The following functions allocate device-accessible, "pinned" memory on the host.
	This memory is mapped onto the device memory space. The resulting device address is returned.
	The vector can be accessed either by its host address "hostPtr" e.g., VD_ramp( hostPtr, size, 0, 1 );
	or by its device address , e.g., cudaVD_ramp( devicePtr, size, 0, 1 );     */
dVector  __vf cudaVD_pinnedVector(  dVector *hostPtr, ui size ); 
dVector  __vf cudaVD_pinnedVector0( dVector *hostPtr, ui size );

/***************  Addressing single vector elements ******************
*  Please note that you cannot use the X[n] syntax on device memory! */

double * __vcuf OVCUAPI cudaVD_Pelement( dVector X, ui n );
double   __vcuf OVCUAPI cudaVD_element( dVector X, ui n );
void     __vcuf OVCUAPI cudaVD_getElement( double *y, dVector X, ui n );
void     __vcuf OVCUAPI cusdVD_getElement( double *d_y, dVector X, ui n );
void     __vcuf OVCUAPI cudaVD_setElement( dVector X, ui n, double C );
void     __vcuf OVCUAPI cusdVD_setElement( dVector X, ui n, double *d_C );

/*******************  Initialization **********************************/

overror_t  __vcuf OVCUAPI   cudaVD_equ0( dVector X, ui size );
overror_t  __vcuf OVCUAPI   cudaVD_equ1( dVector X, ui size );
overror_t  __vcuf OVCUAPI   cudaVD_equm1( dVector X, ui size );
overror_t  __vcuf OVCUAPI   cudaVD_equC( dVector X, ui size, double C );
overror_t  __vcuf OVCUAPI   cusdVD_equC( dVector X, ui size, double *C );
overror_t  __vcuf OVCUAPI   cudaVD_equV( dVector Y, dVector X, ui size );  /* copies from device to device */
overror_t  __vcuf OVCUAPI   cudaVD_equVhost( dVector Y, dVector X, ui size );  /* copies from host to device */
overror_t  __vcuf OVCUAPI   VD_equVdevice( dVector Y, dVector X, ui size );  /* copies from device to host */
overror_t  __vcuf OVCUAPI   cudaVDx_equV( dVector Y, dVector X, ui size, double A, double B );
overror_t  __vcuf OVCUAPI   cusdVDx_equV( dVector Y, dVector X, ui size, double *A, double *B );
overror_t  __vcuf OVCUAPI   cudaVD_ramp( dVector X, ui size, double Start, double Rise );
overror_t  __vcuf OVCUAPI   cusdVD_ramp( dVector X, ui size, double *Start, double *Rise );
overror_t  __vcuf OVCUAPI   cudaVD_Parzen( dVector X, ui size );
overror_t  __vcuf OVCUAPI   cudaVD_Welch( dVector X, ui size );
overror_t  __vcuf OVCUAPI   cudaVD_Hann( dVector X, ui size );
#define cudaVD_Hanning cudaVD_Hann
overror_t  __vcuf OVCUAPI   cudaVD_comb( dVector X, ui size, ui step, double C );
overror_t  __vcuf OVCUAPI   cusdVD_comb( dVector X, ui size, ui step, double *C );

/******  Linear Congruential random generator with Bays-Durham shuffle:  ***********
  Random series is generated on the CPU.
  seed!=0 --> initialization of state. seed==0 --> continue series from previous call with the same state. 
  State must be stored in host memory!
  Random quality of VD_randomLC is much better than of VD_noiseLC                                         */
overror_t  __vcuf OVCUAPI  cudaVD_randomLC( dVector X, ui size, long seed, double MinVal, double MaxVal, V_RANDOMLCSTATE *state );
overror_t  __vcuf OVCUAPI  cusdVD_randomLC( dVector X, ui size, long seed, double *MinVal, double *MaxVal, V_RANDOMLCSTATE *state );
overror_t  __vcuf OVCUAPI  cudaVD_noiseLC( dVector X, ui size, long seed, double Amp, V_RANDOMLCSTATE *state );
overror_t  __vcuf OVCUAPI  cusdVD_noiseLC( dVector X, ui size, long seed, double *Amp, V_RANDOMLCSTATE *state );
/**  simplified version: Series cannot be made continuous across calls: */
overror_t  __vcuf OVCUAPI  cudaVD_random( dVector X, ui size, long seed, double MinVal, double MaxVal );
overror_t  __vcuf OVCUAPI  cusdVD_random( dVector X, ui size, long seed, double *MinVal, double *MaxVal );
overror_t  __vcuf OVCUAPI  cudaVD_noise( dVector X, ui size, long seed, double Amp );
overror_t  __vcuf OVCUAPI  cusdVD_noise( dVector X, ui size, long seed, double *Amp );


/***************  Data-type overror_terconversions  *************************/
       /* for rounding functions, see VDmath.h ! */

overror_t  __vcuf OVCUAPI   cudaV_BItoD(  dVector Y, biVector X, ui size );
overror_t  __vcuf OVCUAPI   cudaV_SItoD(  dVector Y, siVector X, ui size );
overror_t  __vcuf OVCUAPI   cudaV_ItoD(   dVector Y, iVector  X, ui size );
overror_t  __vcuf OVCUAPI   cudaV_LItoD(  dVector Y, liVector X, ui size );
overror_t  __vcuf OVCUAPI   cudaV_QItoD(  dVector Y, qiVector X, ui size );

overror_t  __vcuf OVCUAPI   cudaV_UBtoD(  dVector Y, ubVector X, ui size );
overror_t  __vcuf OVCUAPI   cudaV_UStoD(  dVector Y, usVector X, ui size );
overror_t  __vcuf OVCUAPI   cudaV_UtoD(   dVector Y, uVector  X, ui size );
overror_t  __vcuf OVCUAPI   cudaV_ULtoD(  dVector Y, ulVector X, ui size );
#ifdef _WIN64
overror_t  __vcuf OVCUAPI   cudaV_UQtoD(  dVector Y, uqVector X, ui size );
#endif

overror_t  __vcuf OVCUAPI   cudaV_FtoD( dVector Y, fVector X, ui size );
overror_t  __vcuf OVCUAPI   cudaV_DtoF( fVector Y, dVector X, ui size );


/****************  Index-oriented manipulations ***********************/

overror_t  __vcuf OVCUAPI   cudaVD_reflect( dVector X, ui size );
overror_t  __vcuf OVCUAPI   cudaVD_rev( dVector Y, dVector X, ui size );
overror_t  __vcuf OVCUAPI   cudaVD_rotate( dVector Y, dVector X, ui size, ssize_t pos );
overror_t  __vcuf OVCUAPI   cudaVD_rotate_buf( dVector Y, dVector X, ui size, ssize_t pos, dVector Buf );
overror_t  __vcuf OVCUAPI   cudaVD_delete( dVector X, ui size, ui pos );
overror_t  __vcuf OVCUAPI   cudaVD_insert( dVector X, ui size, ui pos, double C );
overror_t  __vcuf OVCUAPI   cusdVD_insert( dVector X, ui size, ui pos, double *d_C );
overror_t  __vcuf OVCUAPI   cudaVD_sort( dVector Y, dVector X, ui size, int dir );
overror_t  __vcuf OVCUAPI   cudaVD_sortind( uiVector Ind, dVector X, ui size, int dir );
overror_t  __vcuf OVCUAPI   cudaVD_subvector( dVector Y, ui sizey, dVector X, ssize_t samp );
overror_t  __vcuf OVCUAPI   cudaVD_indpick( dVector Y, uiVector Ind, ui sizey, dVector X );
overror_t  __vcuf OVCUAPI   cudaVD_indput(  dVector Y, dVector X, uiVector Ind, ui sizex );
overror_t  __vcuf OVCUAPI   cudaVD_searchC( ui *h_Ind, dVector XTab, ui size, double C, int mode );
overror_t  __vcuf OVCUAPI   cusdVD_searchC( ui *d_Ind, dVector XTab, ui size, double *d_C, int mode );
overror_t  __vcuf OVCUAPI   cudaVD_searchV( uiVector Ind, dVector X, ui sizex, dVector Tab, ui sizetab, int mode );

overror_t  __vcuf OVCUAPI   cudaVD_polyinterpol( dVector Y, dVector X, ui sizex,
                        dVector XTab, dVector YTab, ui sizetab, unsigned deg );
overror_t  __vcuf OVCUAPI   cudaVD_ratinterpol( dVector Y, dVector X, ui sizex,
                        dVector XTab, dVector YTab, ui sizetab, unsigned deg );
overror_t  __vcuf OVCUAPI   cudaVD_natCubSplineInterpol( dVector Y, dVector X, ui sizex,
                    dVector XTab, dVector YTab, ui sizetab );
overror_t  __vcuf OVCUAPI   cudaVD_splinederiv2( dVector Y2, dVector XTab, dVector YTab,
                            ui size, int specify, double Yp0, double Ypn );
overror_t  __vcuf OVCUAPI   cusdVD_splinederiv2( dVector Y2, dVector XTab, dVector YTab,
                            ui size, int specify, double *d_Yp0, double *d_Ypn );
overror_t  __vcuf OVCUAPI   cudaVD_splineinterpol( dVector Y, dVector X, ui sizex,
                    dVector XTab, dVector YTab, dVector Y2Tab, ui sizetab );


/***************** Functions of a sub-set of elements  ********************/

overror_t  __vcuf OVCUAPI   cudaVD_subvector_equC(  dVector Y, ui subsiz, ui samp, double C );
overror_t  __vcuf OVCUAPI   cusdVD_subvector_equC(  dVector Y, ui subsiz, ui samp, double *d_C );
overror_t  __vcuf OVCUAPI   cudaVD_subvector_equV(  dVector Y, ui subsiz, ui samp, dVector X );
    /*   for arithmetic functions of subsets, see <VDmath.h>  */

/**************** One-Dimensional Vector Operations ***********************/

overror_t     __vcuf OVCUAPI   cudaVD_max( double *h_RetVal, dVector X, ui size );
overror_t     __vcuf OVCUAPI   cudaVD_min( double *h_RetVal, dVector X, ui size );
overror_t     __vcuf OVCUAPI   cudaVD_minmax( double *h_Min, double *h_Max, dVector X, ui size );
overror_t     __vcuf OVCUAPI   cudaVD_absmax( double *h_RetVal, dVector X, ui size );
overror_t     __vcuf OVCUAPI   cudaVD_absmin( double *h_RetVal, dVector X, ui size );
overror_t     __vcuf OVCUAPI   cudaVD_maxexp( int *h_RetVal, dVector X, ui size );
overror_t     __vcuf OVCUAPI   cudaVD_minexp( int *h_RetVal, dVector X, ui size );
overror_t     __vcuf OVCUAPI   cudaVD_maxind( double *h_RetVal, ui *Ind, dVector X, ui size );
overror_t     __vcuf OVCUAPI   cudaVD_minind( double *h_RetVal, ui *Ind, dVector X, ui size );
overror_t     __vcuf OVCUAPI   cudaVD_absmaxind( double *h_RetVal, ui *Ind, dVector X, ui size );
overror_t     __vcuf OVCUAPI   cudaVD_absminind( double *h_RetVal, ui *Ind, dVector X, ui size );
overror_t     __vcuf OVCUAPI   cudaVD_localmaxima( ui *h_nFound, uiVector Ind, dVector X, ui size );
overror_t     __vcuf OVCUAPI   cudaVD_localminima( ui *h_nFound, uiVector Ind, dVector X, ui size );
overror_t     __vcuf OVCUAPI   cudaVD_runmax( dVector Y, dVector X, ui size );
overror_t     __vcuf OVCUAPI   cudaVD_runmin( dVector Y, dVector X, ui size );
overror_t     __vcuf OVCUAPI   cudaVD_sum( double *h_RetVal, dVector X, ui size );
overror_t     __vcuf OVCUAPI   cudaVD_prod( double *h_RetVal, dVector X, ui size );
overror_t     __vcuf OVCUAPI   cudaVD_runsum( dVector Y, dVector X, ui size );
overror_t     __vcuf OVCUAPI   cudaVD_runprod( dVector Y, dVector X, ui size );
int           __vcuf OVCUAPI   cudaVD_iselementC( dVector Tab, ui size, double C );   // returns 1, if C is found in Tab, otherwise 0
overror_t     __vcuf OVCUAPI   cudaVD_iselementV( ui *h_nFound, dVector Y, dVector X, ui sizex, dVector Tab, ui sizetab );
overror_t     __vcuf OVCUAPI   cudaVD_centerOfGravityInd( double *h_RetVal,  dVector X, ui size );
overror_t     __vcuf OVCUAPI   cudaVD_centerOfGravityV( double *h_RetVal, dVector X, dVector Y, ui size );

   /*  cusdVD_ variant: return value stored on device:  */
overror_t    __vcuf OVCUAPI   cusdVD_max( double *d_RetVal, dVector X, ui size );
overror_t    __vcuf OVCUAPI   cusdVD_min( double *d_RetVal, dVector X, ui size );
overror_t    __vcuf OVCUAPI   cusdVD_minmax( double *d_Min, double *d_Max, dVector X, ui size );
overror_t    __vcuf OVCUAPI   cusdVD_absmax( double *d_RetVal, dVector X, ui size );
overror_t    __vcuf OVCUAPI   cusdVD_absmin( double *d_RetVal, dVector X, ui size );
overror_t    __vcuf OVCUAPI   cusdVD_maxexp( int *d_RetVal, dVector X, ui size );
overror_t    __vcuf OVCUAPI   cusdVD_minexp( int *d_RetVal, dVector X, ui size );
overror_t    __vcuf OVCUAPI   cusdVD_maxind( double *d_RetVal, ui *h_Ind, dVector X, ui size );
overror_t    __vcuf OVCUAPI   cusdVD_minind( double *d_RetVal, ui *h_Ind, dVector X, ui size );
overror_t    __vcuf OVCUAPI   cusdVD_absmaxind( double *d_RetVal, ui *Ind, dVector X, ui size );
overror_t    __vcuf OVCUAPI   cusdVD_absminind( double *d_RetVal, ui *Ind, dVector X, ui size );
overror_t    __vcuf OVCUAPI   cusdVD_sum( double *d_RetVal, dVector X, ui size );
overror_t    __vcuf OVCUAPI   cusdVD_prod( double *d_RetVal, dVector X, ui size );
int          __vcuf OVCUAPI   cusdVD_iselementC( dVector Tab, ui size, double *d_C );
overror_t    __vcuf OVCUAPI   cusdVD_centerOfGravityInd( double *d_RetVal, dVector X, ui size );
overror_t    __vcuf OVCUAPI   cusdVD_centerOfGravityV( double *d_RetVal, dVector X, dVector Y, ui size );


/**************** Statistical Functions and Building Blocks *************/

overror_t  __vcuf OVCUAPI   cudaVD_sumabs( double *h_RetVal, dVector X, ui size );
overror_t  __vcuf OVCUAPI   cudaVD_mean( double *h_RetVal, dVector X, ui size );
overror_t  __vcuf OVCUAPI   cudaVD_meanwW( double *h_RetVal, dVector X, dVector Wt, ui size );
overror_t  __vcuf OVCUAPI   cudaVD_meanabs( double *h_RetVal, dVector X, ui size );
overror_t  __vcuf OVCUAPI   cudaVD_selected_mean( double *h_RetVal, ui *nsel, dVector X, ui size, double XMin, double XMax ); 
overror_t  __vcuf OVCUAPI   cudaVD_median( double *h_RetVal, dVector X, ui size );
overror_t  __vcuf OVCUAPI   cudaVD_sumdevC( double *h_RetVal, dVector X, ui size, double C );
overror_t  __vcuf OVCUAPI   cudaVD_sumdevV( double *h_RetVal, dVector X, dVector Y, ui size );
overror_t  __vcuf OVCUAPI   cudaVD_avdevC( double *h_RetVal, dVector X, ui size, double C );
overror_t  __vcuf OVCUAPI   cudaVD_avdevV( double *h_RetVal, dVector X, dVector Y, ui size );
overror_t  __vcuf OVCUAPI   cudaVD_ssq( double *h_RetVal, dVector X, ui size );  /* sum-of-squares */
overror_t  __vcuf OVCUAPI   cudaVD_rms( double *h_RetVal, dVector X, ui size );  /* root of the mean square */
overror_t  __vcuf OVCUAPI   cudaVD_ssqdevC( double *h_RetVal, dVector X, ui size, double C );
overror_t  __vcuf OVCUAPI   cudaVD_ssqdevV( double *h_RetVal, dVector X, dVector Y, ui size );
overror_t  __vcuf OVCUAPI   cudaVD_meanvar( double *h_RetMean, double *h_RetVar, dVector X, ui size );
overror_t  __vcuf OVCUAPI   cudaVD_meanvarwW( double *h_RetMean, double *h_RetVar, dVector X, dVector Wt, ui size );
overror_t  __vcuf OVCUAPI   cudaVD_varianceC( double *h_RetVal, dVector X, ui size, double C );
overror_t  __vcuf OVCUAPI   cudaVD_varianceV( double *h_RetVal, dVector X, dVector Y, ui size );
overror_t  __vcuf OVCUAPI   cudaVD_varianceCwW( double *h_RetVal, dVector X, dVector Wt, ui size, double C );
overror_t  __vcuf OVCUAPI   cudaVD_varianceVwW( double *h_RetVal, dVector X, dVector Y, dVector Wt, ui size );
overror_t  __vcuf OVCUAPI   cudaVD_chi2( double *h_RetVal, dVector X, dVector Y, dVector InvVar, ui size );
overror_t  __vcuf OVCUAPI   cudaVD_chiabs( double *h_RetVal, dVector X, dVector Y, dVector Wt, ui size );
overror_t  __vcuf OVCUAPI   cudaVD_corrcoeff( double *h_RetVal, dVector X, dVector Y, ui size, double Xmean, double Ymean );
overror_t  __vcuf OVCUAPI   cudaVD_linregress( dVector h_Param, dVector X, dVector Y, ui size );
overror_t  __vcuf OVCUAPI   cudaVD_linregresswW( dVector h_Param, dVector X, dVector Y, dVector InvVar, ui size );
overror_t  __vcuf OVCUAPI   cudaVD_distribution( ui *h_nOutside, uiVector Abund, dVector Limits, ui nbins, dVector X, ui sizex, int mode );
overror_t  __vcuf OVCUAPI   cudaVD_min_max_mean_stddev( dVector h_Stats, dVector X, ui siz );

	/*  cusdV_ variant: return value stored on device: */
overror_t  __vcuf OVCUAPI   cusdVD_sumabs( double *d_RetVal, dVector X, ui size );
overror_t  __vcuf OVCUAPI   cusdVD_mean( double *d_RetVal, dVector X, ui size );
overror_t  __vcuf OVCUAPI   cusdVD_meanwW( double *d_RetVal, dVector X, dVector Wt, ui size );
overror_t  __vcuf OVCUAPI   cusdVD_meanabs( double *d_RetVal, dVector X, ui size );
overror_t  __vcuf OVCUAPI   cusdVD_selected_mean( double *d_RetVal, ui *nsel, dVector X, ui size, double *d_XMin, double *d_XMax ); 
overror_t  __vcuf OVCUAPI   cusdVD_median( double *d_RetVal, dVector X, ui size );
overror_t  __vcuf OVCUAPI   cusdVD_sumdevC( double *d_RetVal, dVector X, ui size, double *d_C );
overror_t  __vcuf OVCUAPI   cusdVD_sumdevV( double *d_RetVal, dVector X, dVector Y, ui size );
overror_t  __vcuf OVCUAPI   cusdVD_avdevC( double *d_RetVal, dVector X, ui size, double *d_C );
overror_t  __vcuf OVCUAPI   cusdVD_avdevV( double *d_RetVal, dVector X, dVector Y, ui size );
overror_t  __vcuf OVCUAPI   cusdVD_ssq( double *d_RetVal, dVector X, ui size );  /* sum-of-squares */
overror_t  __vcuf OVCUAPI   cusdVD_rms( double *d_RetVal, dVector X, ui size );  /* root of the mean square */
overror_t  __vcuf OVCUAPI   cusdVD_ssqdevC( double *d_RetVal, dVector X, ui size, double *d_C );
overror_t  __vcuf OVCUAPI   cusdVD_ssqdevV( double *d_RetVal, dVector X, dVector Y, ui size );
overror_t  __vcuf OVCUAPI   cusdVD_meanvar( double *d_RetVal, double *Var, dVector X, ui size );
overror_t  __vcuf OVCUAPI   cusdVD_meanvarwW( double *d_RetVal, double *Var, dVector X, dVector Wt, ui size );
overror_t  __vcuf OVCUAPI   cusdVD_varianceC( double *d_RetVal, dVector X, ui size, double *d_C );
overror_t  __vcuf OVCUAPI   cusdVD_varianceV( double *d_RetVal, dVector X, dVector Y, ui size );
overror_t  __vcuf OVCUAPI   cusdVD_varianceCwW( double *d_RetVal, dVector X, dVector Wt, ui size, double *d_C );
overror_t  __vcuf OVCUAPI   cusdVD_varianceVwW( double *d_RetVal, dVector X, dVector Y, dVector Wt, ui size );
overror_t  __vcuf OVCUAPI   cusdVD_chi2( double *d_RetVal, dVector X, dVector Y, dVector InvVar, ui size );
overror_t  __vcuf OVCUAPI   cusdVD_chiabs( double *d_RetVal, dVector X, dVector Y, dVector Wt, ui size );
overror_t  __vcuf OVCUAPI   cusdVD_corrcoeff( double *d_RetVal, dVector X, dVector Y, ui size, double *d_Xmean, double *d_Ymean );
overror_t  __vcuf OVCUAPI   cusdVD_linregress( dVector d_Param, dVector X, dVector Y, ui size );
overror_t  __vcuf OVCUAPI   cusdVD_linregresswW( dVector d_Param, dVector X, dVector Y, dVector InvVar, ui size );
overror_t  __vcuf OVCUAPI   cusdVD_distribution( ui *d_nOutside, uiVector Abund, dVector Limits, ui nbins, dVector X, ui sizex, int mode );
overror_t  __vcuf OVCUAPI   cusdVD_min_max_mean_stddev( dVector d_Stats, dVector X, ui siz );

/*********  Fourier Transforms, Convolutions, Filtering  ****************/

#if defined __cplusplus && defined _CMATH_CLASSDEFS
} // following function cannot be extern "C"
#endif
dComplex  __vf   cudaVD_getRspEdit( void );
#if defined __cplusplus && defined _CMATH_CLASSDEFS
extern "C" {
#endif
void      __vf   cudaVD_setRspEdit( dComplex Trunc );
overror_t   __vcuf OVCUAPI   cudaVD_FFT( dVector Y, dVector X, ui size, int dir );
overror_t   __vcuf OVCUAPI   cudaVD_2FFT( dVector Y1, dVector Y2, dVector X1, dVector X2, ui size, int dir );
overror_t   __vcuf OVCUAPI   cudaVD_FFTtoC( cdVector Y, dVector X, ui size );
overror_t   __vcuf OVCUAPI   cudaVD_filter( dVector Y, dVector X, dVector Flt, ui size );
overror_t   __vcuf OVCUAPI   cudaVD_autocorr( dVector Y, dVector X, ui size );
overror_t  __vcuf OVCUAPI    cudaVD_xcorr( dVector Z, dVector X, dVector Y, ui size );
overror_t   __vcuf OVCUAPI   cudaVD_spectrum( double *h_pfc, dVector Spc, ui specsiz, dVector X, ui xsiz, dVector Win );
overror_t   __vcuf OVCUAPI   cusdVD_spectrum( double *d_pfc, dVector Spc, ui specsiz, dVector X, ui xsiz, dVector Win );
                /* xsiz >= n*specsiz,  Winsiz = 2*specsiz ! returns psd at Nyquist frequ. */
overror_t  __vcuf OVCUAPI   cudaVD_convolve( dVector Y, dVector Flt, dVector X, dVector Rsp, ui size );
overror_t  __vcuf OVCUAPI   cudaVD_deconvolve( dVector Y, dVector Flt, dVector X, dVector Rsp, ui size );


/********************** Analysis ****************************************/

overror_t    __vcuf OVCUAPI   cudaVD_derivC( dVector Y, dVector X, ui size, double Deltat );
overror_t    __vcuf OVCUAPI   cusdVD_derivC( dVector Y, dVector X, ui size, double *d_Deltat );
overror_t    __vcuf OVCUAPI   cudaVD_derivV( dVector Z, dVector X, dVector Y, ui size );
overror_t    __vcuf OVCUAPI   cudaVD_integralC( double *h_RetVal, dVector X, ui size, double Deltat );
overror_t    __vcuf OVCUAPI   cudaVD_integralV( double *h_RetVal, dVector X, dVector Y, ui size );
overror_t    __vcuf OVCUAPI   cusdVD_integralC( double *d_RetVal, dVector X, ui size, double *d_Deltat );
overror_t    __vcuf OVCUAPI   cusdVD_integralV( double *d_RetVal, dVector X, dVector Y, ui size );
overror_t    __vcuf OVCUAPI   cudaVD_runintegralC( dVector Y, dVector X, ui size, double Deltat );
overror_t    __vcuf OVCUAPI   cudaVD_runintegralV( dVector Z, dVector X, dVector Y, ui size );
overror_t    __vcuf OVCUAPI   cudaVD_smooth( dVector Y, dVector X, ui size, unsigned deg );
overror_t    __vcuf OVCUAPI   cudaVD_biquad( dVector Y, dVector X, ui siz, dVector h_Param );
overror_t    __vcuf OVCUAPI   cusdVD_biquad( dVector Y, dVector X, ui siz, dVector d_Param );
overror_t    __vcuf OVCUAPI   cudaVD_ismonoton( int *h_isSorted, dVector X, ui size );
overror_t    __vcuf OVCUAPI   cusdVD_ismonoton( int *d_isSorted, dVector X, ui size );
	/* isSorted = 1 for ascending or flat, -1 for descending, 0 for non-sorted */

/****************** Geometrical Vector Arithmetics **************************/

overror_t    __vcuf OVCUAPI   cudaVD_scalprod( double *h_RetVal, dVector X, dVector Y, ui size );
overror_t    __vcuf OVCUAPI   cudaVD_Euclid( double *h_RetVal, dVector X, ui size );
#define cudaVD_euclid cudaVD_Euclid
overror_t    __vcuf OVCUAPI   cusdVD_scalprod( double *d_RetVal, dVector X, dVector Y, ui size );
overror_t    __vcuf OVCUAPI   cusdVD_Euclid( double *d_RetVal, dVector X, ui size );
#define cusdVD_euclid cusdVD_Euclid
overror_t      __vcuf OVCUAPI   cudaVD_xprod( dVector Z, dVector X, dVector Y );


/***************************  Input and Output *****************************
	The input/output functions involve memory transfers from device
	to host memory or vice versa. The generic cudaVD_input/output functions
	allocate their own host buffers, whereas the cudaVD_xxx_buf functions
	take a user-supplied buffer h_Wk and are much more efficient.          */

overror_t  __vf    cudaVD_fprint( FILE *stream, dVector X, ui size, unsigned nperline, unsigned linewidth );
overror_t  __vf    cudaVD_cprint( dVector X, ui size, unsigned nperline );
#define       cudaVD_print( x, sz, npl )  cudaVD_fprint( stdout, x, sz, npl, 80 )
overror_t  __vf    cudaVD_fprint_buf( FILE *stream, dVector d_X, ui size, unsigned nperline, unsigned linewidth, dVector h_Wk );
overror_t  __vf    cudaVD_cprint_buf( dVector d_X, ui size, unsigned nperline, dVector h_Wk );
#define       cudaVD_print_buf( d_x, sz, npl, h_Wk )  cudaVD_fprint_buf( stdout, d_x, sz, npl, 80, h_Wk )
 /*  cudaVD_print, cudaVD_cprint are usable only for console applications!  */
overror_t  __vf    cudaVD_write( FILE *stream, dVector X, ui size  );
overror_t  __vf    cudaVD_write_buf( FILE *stream, dVector d_X, ui size, dVector h_Wk );
                     /* cudaVD_write, cudaVD_read in ascii format */
#if !((defined __BORLANDC__) && (__BORLANDC__ < 0x710))
		/* modern compiler versions:  */
	overror_t  __vf    cudaVD_read( dVector X, ui size, FILE *stream );
	overror_t  __vf    cudaVD_read_buf( dVector d_X, ui size, FILE *stream, dVector h_Wk );
#else /* older Borland compiler versions need separate implementation */
	overror_t  __vf    cudaVD_read1( dVector X, ui size, FILE *stream );
	overror_t  __vf    cudaVD_read1_buf( dVector d_X, ui size, FILE *stream, dVector h_Wk );
	#define cudaVD_read     cudaVD_read1
	#define cudaVD_read_buf cudaVD_read1_buf
#endif
overror_t  __vf cudaVD_store( FILE *stream, dVector X, ui size );
overror_t  __vf cudaVD_recall( dVector X, ui size, FILE *stream );
overror_t  __vf cudaVD_store_buf( FILE *stream, dVector d_X, ui size, dVector h_Wk );
overror_t  __vf cudaVD_recall_buf( dVector d_X, ui size, FILE *stream, dVector h_Wk );
                     /* cudaVD_store, cudaVD_recall in binary format */


#ifdef __cplusplus
}    //  end of extern "C"
         // alternative syntax of convolution and deconvolution:
    inline overror_t cudaVD_convolve( dVector Y, dVector Flt, dVector X, dVector Rsp,
                              ui size, double TruncRe, double TruncIm )
    {   cudaVD_setRspEdit( dcplx( TruncRe, TruncIm ) );
        return( cudaVD_convolve( Y, Flt, X, Rsp, size ));
    }
    inline overror_t cudaVD_deconvolve( dVector Y, dVector Flt, dVector X, dVector Rsp,
                                ui size, double TruncRe, double TruncIm )
    {   cudaVD_setRspEdit( dcplx( TruncRe, TruncIm ) );
        return( cudaVD_deconvolve( Y, Flt, X, Rsp, size ));
    }
#endif   /*  __cplusplus   */


/******************  VDcu_ functions: **********************************
	act on host memory, using the CUDA device for processing
************************************************************************/


#ifdef __cplusplus
extern "C" {
#endif

/*******************  Initialization **********************************/

void  __vcuf OVCUAPI   VDcu_equ0( dVector X, ui size );
void  __vcuf OVCUAPI   VDcu_equ1( dVector X, ui size );
void  __vcuf OVCUAPI   VDcu_equm1( dVector X, ui size );
void  __vcuf OVCUAPI   VDcu_equC( dVector X, ui size, double C );
void  __vcuf OVCUAPI   VDcu_equV( dVector Y, dVector X, ui size );  /* copies from device to device */
void  __vcuf OVCUAPI   VDxcu_equV( dVector Y, dVector X, ui size, double A, double B );
void  __vcuf OVCUAPI   VDcu_ramp( dVector X, ui size, double Start, double Rise );
void  __vcuf OVCUAPI   VDcu_Parzen( dVector X, ui size );
void  __vcuf OVCUAPI   VDcu_Welch( dVector X, ui size );
void  __vcuf OVCUAPI   VDcu_Hann( dVector X, ui size );
#define VDcu_Hanning VDcu_Hann
void  __vcuf OVCUAPI   VDcu_comb( dVector X, ui size, ui step, double C );
/* no Vcu_random functions: random generation runs on CPU anyway */


/***************  Data-type interconversions  *************************/
       /* for rounding functions, see VDmath.h ! */

void  __vcuf OVCUAPI   Vcu_BItoD(  dVector Y, biVector X, ui size );
void  __vcuf OVCUAPI   Vcu_SItoD(  dVector Y, siVector X, ui size );
void  __vcuf OVCUAPI   Vcu_ItoD(   dVector Y, iVector  X, ui size );
void  __vcuf OVCUAPI   Vcu_LItoD(  dVector Y, liVector X, ui size );
void  __vcuf OVCUAPI   Vcu_QItoD(  dVector Y, qiVector X, ui size );

void  __vcuf OVCUAPI   Vcu_UBtoD(  dVector Y, ubVector X, ui size );
void  __vcuf OVCUAPI   Vcu_UStoD(  dVector Y, usVector X, ui size );
void  __vcuf OVCUAPI   Vcu_UtoD(   dVector Y, uVector  X, ui size );
void  __vcuf OVCUAPI   Vcu_ULtoD(  dVector Y, ulVector X, ui size );
#ifdef _WIN64
void  __vcuf OVCUAPI   Vcu_UQtoD(  dVector Y, uqVector X, ui size );
#endif

void  __vcuf OVCUAPI   Vcu_FtoD( dVector Y, fVector X, ui size );
void  __vcuf OVCUAPI   Vcu_DtoF( fVector Y, dVector X, ui size );


/****************  Index-oriented manipulations ***********************/

void  __vcuf OVCUAPI   VDcu_reflect( dVector X, ui size );
void  __vcuf OVCUAPI   VDcu_rev( dVector Y, dVector X, ui size );
void  __vcuf OVCUAPI   VDcu_rotate( dVector Y, dVector X, ui size, ssize_t pos );
void  __vcuf OVCUAPI   VDcu_rotate_buf( dVector Y, dVector X, ui size, ssize_t pos, dVector Buf );
void  __vcuf OVCUAPI   VDcu_delete( dVector X, ui size, ui pos );
void  __vcuf OVCUAPI   VDcu_insert( dVector X, ui size, ui pos, double C );
void  __vcuf OVCUAPI   VDcu_sort( dVector Y, dVector X, ui size, int dir );
void  __vcuf OVCUAPI   VDcu_sortind( uiVector Ind, dVector X, ui size, int dir );
void  __vcuf OVCUAPI   VDcu_subvector( dVector Y, ui sizey, dVector X, ssize_t samp );
  /* no VDcu_indpick, VDcu_indput possible! */
ui    __vcuf OVCUAPI   VDcu_searchC( dVector X, ui size, double C, int mode );
void  __vcuf OVCUAPI   VDcu_searchV( uiVector Ind, dVector X, ui sizex, dVector Tab, ui sizetab, int mode );

void  __vcuf OVCUAPI   VDcu_polyinterpol( dVector Y, dVector X, ui sizex,
                        dVector XTab, dVector YTab, ui sizetab, unsigned deg );
void  __vcuf OVCUAPI   VDcu_ratinterpol( dVector Y, dVector X, ui sizex,
                        dVector XTab, dVector YTab, ui sizetab, unsigned deg );
void  __vcuf OVCUAPI   VDcu_natCubSplineInterpol( dVector Y, dVector X, ui sizex,
                    dVector XTab, dVector YTab, ui sizetab );
	/* no VDcu_splinederiv2! must be executed on host anyway */
void  __vcuf OVCUAPI   VDcu_splineinterpol( dVector Y, dVector X, ui sizex,
                    dVector XTab, dVector YTab, dVector Y2Tab, ui sizetab );


/***************** Functions of a sub-set of elements  ********************/

void  __vcuf OVCUAPI   VDcu_subvector_equC(  dVector Y, ui subsiz, ui samp, double C );
void  __vcuf OVCUAPI   VDcu_subvector_equV(  dVector Y, ui subsiz, ui samp, dVector X );
    /*   for arithmetic functions of subsets, see <VDmath.h>  */

/**************** One-Dimensional Vector Operations ***********************/

double     __vcuf OVCUAPI   VDcu_max( dVector X, ui size );
double     __vcuf OVCUAPI   VDcu_min( dVector X, ui size );
double     __vcuf OVCUAPI   VDcu_minmax( double *RetMax, dVector X, ui size );
double     __vcuf OVCUAPI   VDcu_absmax( dVector X, ui size );
double     __vcuf OVCUAPI   VDcu_absmin( dVector X, ui size );
int        __vcuf OVCUAPI   VDcu_maxexp( dVector X, ui size );
int        __vcuf OVCUAPI   VDcu_minexp( dVector X, ui size );
double     __vcuf OVCUAPI   VDcu_maxind( ui *Ind, dVector X, ui size );
double     __vcuf OVCUAPI   VDcu_minind( ui *Ind, dVector X, ui size );
double     __vcuf OVCUAPI   VDcu_absmaxind( ui *Ind, dVector X, ui size );
double     __vcuf OVCUAPI   VDcu_absminind( ui *Ind, dVector X, ui size );
ui         __vcuf OVCUAPI   VDcu_localmaxima( uiVector Ind, dVector X, ui size );
ui         __vcuf OVCUAPI   VDcu_localminima( uiVector Ind, dVector X, ui size );
void       __vcuf OVCUAPI   VDcu_runmax( dVector Y, dVector X, ui size );
void       __vcuf OVCUAPI   VDcu_runmin( dVector Y, dVector X, ui size );
double     __vcuf OVCUAPI   VDcu_sum( dVector X, ui size );
double     __vcuf OVCUAPI   VDcu_prod( dVector X, ui size );
void       __vcuf OVCUAPI   VDcu_runsum( dVector Y, dVector X, ui size );
void       __vcuf OVCUAPI   VDcu_runprod( dVector Y, dVector X, ui size );
int        __vcuf OVCUAPI   VDcu_iselementC( dVector Tab, ui size, double C );
ui         __vcuf OVCUAPI   VDcu_iselementV( dVector Y, dVector X, ui sizex, dVector Tab, ui sizetab );

double     __vcuf OVCUAPI   VDcu_centerOfGravityInd( dVector X, ui size );
double     __vcuf OVCUAPI   VDcu_centerOfGravityV( dVector X, dVector Y, ui size );

/**************** Statistical Functions and Building Blocks *************/

double  __vcuf OVCUAPI   VDcu_sumabs( dVector X, ui size );
double  __vcuf OVCUAPI   VDcu_mean( dVector X, ui size );
double  __vcuf OVCUAPI   VDcu_meanwW( dVector X, dVector Wt, ui size );
double  __vcuf OVCUAPI   VDcu_meanabs( dVector X, ui size );
double  __vcuf OVCUAPI   VDcu_selected_mean( ui *nsel, dVector X, ui size, double XMin, double XMax ); 
double  __vcuf OVCUAPI   VDcu_median( dVector X, ui size );
double  __vcuf OVCUAPI   VDcu_sumdevC( dVector X, ui size, double C );
double  __vcuf OVCUAPI   VDcu_sumdevV( dVector X, dVector Y, ui size );
double  __vcuf OVCUAPI   VDcu_avdevC( dVector X, ui size, double C );
double  __vcuf OVCUAPI   VDcu_avdevV( dVector X, dVector Y, ui size );
double  __vcuf OVCUAPI   VDcu_ssq( dVector X, ui size );  /* sum-of-squares */
double  __vcuf OVCUAPI   VDcu_rms( dVector X, ui size );  /* root of the mean square */
double  __vcuf OVCUAPI   VDcu_ssqdevC( dVector X, ui size, double C );
double  __vcuf OVCUAPI   VDcu_ssqdevV( dVector X, dVector Y, ui size );
double  __vcuf OVCUAPI   VDcu_meanvar( double *Var, dVector X, ui size );
double  __vcuf OVCUAPI   VDcu_meanvarwW( double *Var, dVector X, dVector Wt, ui size );
double  __vcuf OVCUAPI   VDcu_varianceC( dVector X, ui size, double C );
double  __vcuf OVCUAPI   VDcu_varianceV( dVector X, dVector Y, ui size );
double  __vcuf OVCUAPI   VDcu_varianceCwW( dVector X, dVector Wt, ui size, double C );
double  __vcuf OVCUAPI   VDcu_varianceVwW( dVector X, dVector Y, dVector Wt, ui size );
double  __vcuf OVCUAPI   VDcu_chi2( dVector X, dVector Y, dVector InvVar, ui size );
double  __vcuf OVCUAPI   VDcu_chiabs( dVector X, dVector Y, dVector Wt, ui size );
double  __vcuf OVCUAPI   VDcu_corrcoeff( dVector X, dVector Y, ui size, double Xmean, double Ymean );
void    __vcuf OVCUAPI   VDcu_linregress( dVector h_Param, dVector X, dVector Y, ui size );
void    __vcuf OVCUAPI   VDcu_linregresswW( dVector h_Param, dVector X, dVector Y, dVector InvVar, ui size );
ui      __vcuf OVCUAPI   VDcu_distribution( uiVector Abund, dVector Limits, ui nbins, dVector X, ui sizex, int mode );
void    __vcuf OVCUAPI   VDcu_min_max_mean_stddev( dVector Stats, dVector X, ui siz );


/*********  Fourier Transforms, Convolutions, Filtering  ****************/

void   __vcuf OVCUAPI   VDcu_FFT( dVector Y, dVector X, ui size, int dir );
void   __vcuf OVCUAPI   VDcu_2FFT( dVector Y1, dVector Y2, dVector X1, dVector X2, ui size, int dir );
void   __vcuf OVCUAPI   VDcu_FFTtoC( cdVector Y, dVector X, ui size );
void   __vcuf OVCUAPI   VDcu_filter( dVector Y, dVector X, dVector Flt, ui size );
void   __vcuf OVCUAPI   VDcu_autocorr( dVector Y, dVector X, ui size );
void   __vcuf OVCUAPI   VDcu_xcorr( dVector Z, dVector X, dVector Y, ui size );
double __vcuf OVCUAPI   VDcu_spectrum( dVector Spc, ui specsiz, dVector X, ui xsiz, dVector Win );
                /* xsiz >= n*specsiz,  Winsiz = 2*specsiz ! returns psd at Nyquist frequ. */
void  __vcuf OVCUAPI   VDcu_convolve( dVector Y, dVector Flt, dVector X, dVector Rsp, ui size );
void  __vcuf OVCUAPI   VDcu_deconvolve( dVector Y, dVector Flt, dVector X, dVector Rsp, ui size );


/********************** Analysis ****************************************/

void    __vcuf OVCUAPI   VDcu_derivC( dVector Y, dVector X, ui size, double Deltat );
void    __vcuf OVCUAPI   VDcu_derivV( dVector Z, dVector X, dVector Y, ui size );
double  __vcuf OVCUAPI   VDcu_integralC( dVector X, ui size, double Deltat );
void    __vcuf OVCUAPI   VDcu_runintegralC( dVector Y, dVector X, ui size, double Deltat );
double  __vcuf OVCUAPI   VDcu_integralV( dVector X, dVector Y, ui size );
void    __vcuf OVCUAPI   VDcu_runintegralV( dVector Z, dVector X, dVector Y, ui size );
void    __vcuf OVCUAPI   VDcu_smooth( dVector Y, dVector X, ui size, unsigned deg );
void    __vcuf OVCUAPI   VDcu_biquad( dVector Y, dVector X, ui siz, dVector Param );
	/* Param[0]=a0, [1]=a1, [2]=a2, [3]=b1, [4]=b2, [5]=x(-1), [6]=x(-2), [7]=y(-1), [8]=y(-2) */
int     __vcuf OVCUAPI   VDcu_ismonoton( dVector X, ui size );

/****************** Geometrical Vector Arithmetics **************************/

double    __vcuf OVCUAPI   VDcu_scalprod( dVector X, dVector Y, ui size );
double    __vcuf OVCUAPI   VDcu_Euclid( dVector X, ui size );
#define VDcu_euclid VDcu_Euclid
/* void      __vcuf OVCUAPI   VDcu_xprod( dVector Z, dVector X, dVector Y );
*/


#ifdef __cplusplus
}    //  end of extern "C"
         // alternative syntax of convolution and deconvolution:
    inline void VDcu_convolve( dVector Y, dVector Flt, dVector X, dVector Rsp,
                              ui size, double TruncRe, double TruncIm )
    {   dComplex OldEdit = cudaVD_getRspEdit();
		cudaVD_setRspEdit( dcplx( TruncRe, TruncIm ) );
        VDcu_convolve( Y, Flt, X, Rsp, size );
		cudaVD_setRspEdit( OldEdit );
    }
    inline void VDcu_deconvolve( dVector Y, dVector Flt, dVector X, dVector Rsp,
                                ui size, double TruncRe, double TruncIm )
    {   dComplex OldEdit = cudaVD_getRspEdit();
		cudaVD_setRspEdit( dcplx( TruncRe, TruncIm ) );
        VDcu_deconvolve( Y, Flt, X, Rsp, size );
		cudaVD_setRspEdit( OldEdit );
    }
#endif   /*  __cplusplus   */


#endif   /*  __CUDAVDSTD_H  */
