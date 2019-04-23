/*  cudaVFstd.h

  vector management functions:
  manipulations on whole arrays or vectors of data type "float"
  (real numbers)

  Copyright (c) 1996-2017 by OptiCode - Dr. Martin Sander Software Dev.
  All Rights Reserved.
*/

#ifndef __CUDAVFSTD_H
#define __CUDAVFSTD_H
#if !defined( __CUDAVECLIB_H )
#include <cudaVecLib.h>
#endif
#if !defined( __VFSTD_H )
#include <VFstd.h>
#endif


/******************  cudaVF_ functions: **********************************
	 act on vectors in CUDA device memory; 
	 scalar parameters and return values on host
******************  cusdVF_ functions: **********************************
	 also act on vectors in CUDA device memory; 
	 scalar parameters and return values by address on device memory
************************************************************************/

#ifdef __cplusplus
extern "C" {
#endif

/*************************  Generation  **************************/

fVector  __vf cudaVF_vector( ui size );    /* allocates a vector on device memory */
fVector  __vf cudaVF_vector0( ui size );
 /* The following functions allocate device-accessible, "pinned" memory on the host.
	This memory is mapped onto the device memory space. The resulting device address is returned.
	The vector can be accessed either by its host address "hostPtr" e.g., VF_ramp( hostPtr, size, 0, 1 );
	or by its device address , e.g., cudaVF_ramp( devicePtr, size, 0, 1 );     */
fVector  __vf cudaVF_pinnedVector(  fVector *hostPtr, ui size ); 
fVector  __vf cudaVF_pinnedVector0( fVector *hostPtr, ui size );

/***************  Addressing single vector elements ******************
*  Please note that you cannot use the X[n] syntax on device memory! */

float * __vcuf OVCUAPI cudaVF_Pelement( fVector X, ui n );
float   __vcuf OVCUAPI cudaVF_element( fVector X, ui n );
void    __vcuf OVCUAPI cudaVF_getElement( float *y, fVector X, ui n );
void    __vcuf OVCUAPI cusdVF_getElement( float *d_y, fVector X, ui n );
void    __vcuf OVCUAPI cudaVF_setElement( fVector X, ui n, float C );
void    __vcuf OVCUAPI cusdVF_setElement( fVector X, ui n, float *d_C );

/*******************  Initialization **********************************/

overror_t  __vcuf OVCUAPI   cudaVF_equ0( fVector X, ui size );
overror_t  __vcuf OVCUAPI   cudaVF_equ1( fVector X, ui size );
overror_t  __vcuf OVCUAPI   cudaVF_equm1( fVector X, ui size );
overror_t  __vcuf OVCUAPI   cudaVF_equC( fVector X, ui size, float C );
overror_t  __vcuf OVCUAPI   cusdVF_equC( fVector X, ui size, float *d_C );
overror_t  __vcuf OVCUAPI   cudaVF_equV( fVector Y, fVector X, ui size );  /* copies from device to device */
overror_t  __vcuf OVCUAPI   cudaVF_equVhost( fVector Y, fVector X, ui size );  /* copies from host to device */
overror_t  __vcuf OVCUAPI   VF_equVdevice( fVector Y, fVector X, ui size );  /* copies from device to host */
overror_t  __vcuf OVCUAPI   cudaVFx_equV( fVector Y, fVector X, ui size, float A, float B );
overror_t  __vcuf OVCUAPI   cusdVFx_equV( fVector Y, fVector X, ui size, float *d_A, float *d_B );
overror_t  __vcuf OVCUAPI   cudaVF_ramp( fVector X, ui size, float Start, float Rise );
overror_t  __vcuf OVCUAPI   cusdVF_ramp( fVector X, ui size, float *d_Start, float *d_Rise );
overror_t  __vcuf OVCUAPI   cudaVF_Parzen( fVector X, ui size );
overror_t  __vcuf OVCUAPI   cudaVF_Welch( fVector X, ui size );
overror_t  __vcuf OVCUAPI   cudaVF_Hann( fVector X, ui size );
#define cudaVF_Hanning cudaVF_Hann
overror_t  __vcuf OVCUAPI   cudaVF_comb( fVector X, ui size, ui step, float C );
overror_t  __vcuf OVCUAPI   cusdVF_comb( fVector X, ui size, ui step, float *d_C );

/******  Linear Congruential random generator with Bays-Durham shuffle:  ***********
  Random series is generated on the CPU.
  seed!=0 --> initialization of state. seed==0 --> continue series from previous call with the same state. 
  State must be stored in host memory!
  Random quality of VF_randomLC is much better than of VF_noiseLC                                         */
overror_t  __vcuf OVCUAPI  cudaVF_randomLC( fVector X, ui size, long seed, float MinVal, float MaxVal, V_RANDOMLCSTATE *h_state );
overror_t  __vcuf OVCUAPI  cusdVF_randomLC( fVector X, ui size, long seed, float *d_MinVal, float *d_MaxVal, V_RANDOMLCSTATE *h_state );
overror_t  __vcuf OVCUAPI  cudaVF_noiseLC( fVector X, ui size, long seed, float Amp, V_RANDOMLCSTATE *h_state );
overror_t  __vcuf OVCUAPI  cusdVF_noiseLC( fVector X, ui size, long seed, float *d_Amp, V_RANDOMLCSTATE *h_state );
/**  simplified version: Series cannot be made not continuous across calls: */
overror_t  __vcuf OVCUAPI  cudaVF_random( fVector X, ui size, long seed, float MinVal, float MaxVal );
overror_t  __vcuf OVCUAPI  cusdVF_random( fVector X, ui size, long seed, float *d_MinVal, float *d_MaxVal );
overror_t  __vcuf OVCUAPI  cudaVF_noise( fVector X, ui size, long seed, float Amp );
overror_t  __vcuf OVCUAPI  cusdVF_noise( fVector X, ui size, long seed, float *d_Amp );


/***************  Data-type overror_terconversions  *************************/
       /* for rounding functions, see cudaVFmath.h ! */

overror_t  __vcuf OVCUAPI   cudaV_BItoF(  fVector Y, biVector X, ui size );
overror_t  __vcuf OVCUAPI   cudaV_SItoF(  fVector Y, siVector X, ui size );
overror_t  __vcuf OVCUAPI   cudaV_ItoF(   fVector Y, iVector  X, ui size );
overror_t  __vcuf OVCUAPI   cudaV_LItoF(  fVector Y, liVector X, ui size );
overror_t  __vcuf OVCUAPI   cudaV_QItoF(  fVector Y, qiVector X, ui size );

overror_t  __vcuf OVCUAPI   cudaV_UBtoF(  fVector Y, ubVector X, ui size );
overror_t  __vcuf OVCUAPI   cudaV_UStoF(  fVector Y, usVector X, ui size );
overror_t  __vcuf OVCUAPI   cudaV_UtoF(   fVector Y, uVector  X, ui size );
overror_t  __vcuf OVCUAPI   cudaV_ULtoF(  fVector Y, ulVector X, ui size );
#ifdef _WIN64
overror_t  __vcuf OVCUAPI   cudaV_UQtoF(  fVector Y, uqVector X, ui size );
#endif

overror_t  __vcuf OVCUAPI   cudaV_FtoD( dVector Y, fVector X, ui size );
overror_t  __vcuf OVCUAPI   cudaV_DtoF( fVector Y, dVector X, ui size );


/****************  Index-oriented manipulations ***********************/

overror_t  __vcuf OVCUAPI   cudaVF_reflect( fVector X, ui size );
overror_t  __vcuf OVCUAPI   cudaVF_rev( fVector Y, fVector X, ui size );
overror_t  __vcuf OVCUAPI   cudaVF_rotate( fVector Y, fVector X, ui size, ssize_t pos );
overror_t  __vcuf OVCUAPI   cudaVF_rotate_buf( fVector Y, fVector X, ui size, ssize_t pos, fVector Buf );

overror_t  __vcuf OVCUAPI   cudaVF_delete( fVector X, ui size, ui pos );
overror_t  __vcuf OVCUAPI   cudaVF_insert( fVector X, ui size, ui pos, float C );
overror_t  __vcuf OVCUAPI   cusdVF_insert( fVector X, ui size, ui pos, float *d_C );
overror_t  __vcuf OVCUAPI   cudaVF_sort( fVector Y, fVector X, ui size, int dir );
overror_t  __vcuf OVCUAPI   cudaVF_sortind( uiVector Ind, fVector X, ui size, int dir );
overror_t  __vcuf OVCUAPI   cudaVF_subvector( fVector Y, ui sizey, fVector X, ssize_t samp );
overror_t  __vcuf OVCUAPI   cudaVF_indpick( fVector Y, uiVector Ind, ui sizey, fVector X );
overror_t  __vcuf OVCUAPI   cudaVF_indput(  fVector Y, fVector X, uiVector Ind, ui sizex );
overror_t  __vcuf OVCUAPI   cudaVF_searchC( ui *h_Ind, fVector XTab, ui size, float C, int mode );
overror_t  __vcuf OVCUAPI   cusdVF_searchC( ui *d_Ind, fVector XTab, ui size, float *d_C, int mode );
overror_t  __vcuf OVCUAPI   cudaVF_searchV( uiVector Ind, fVector X, ui sizex, fVector Tab, ui sizetab, int mode );

overror_t  __vcuf OVCUAPI   cudaVF_polyinterpol( fVector Y, fVector X, ui sizex,
                        fVector XTab, fVector YTab, ui sizetab, unsigned deg );
overror_t  __vcuf OVCUAPI   cudaVF_ratinterpol( fVector Y, fVector X, ui sizex,
                        fVector XTab, fVector YTab, ui sizetab, unsigned deg );
overror_t  __vcuf OVCUAPI   cudaVF_natCubSplineInterpol( fVector Y, fVector X, ui sizex,
                    fVector XTab, fVector YTab, ui sizetab );
overror_t  __vcuf OVCUAPI   cudaVF_splinederiv2( fVector Y2, fVector XTab, fVector YTab,
                            ui size, int specify, float Yp0, float Ypn );
overror_t  __vcuf OVCUAPI   cusdVF_splinederiv2( fVector Y2, fVector XTab, fVector YTab,
                            ui size, int specify, float *d_Yp0, float *d_Ypn );
overror_t  __vcuf OVCUAPI   cudaVF_splineinterpol( fVector Y, fVector X, ui sizex,
                    fVector XTab, fVector YTab, fVector Y2Tab, ui sizetab );


/***************** Functions of a sub-set of elements  ********************/

overror_t  __vcuf OVCUAPI   cudaVF_subvector_equC(  fVector Y, ui subsiz, ui samp, float C );
overror_t  __vcuf OVCUAPI   cusdVF_subvector_equC(  fVector Y, ui subsiz, ui samp, float *d_C );
overror_t  __vcuf OVCUAPI   cudaVF_subvector_equV(  fVector Y, ui subsiz, ui samp, fVector X );
    /*   for arithmetic functions of subsets, see <VFmath.h>  */

/**************** One-Dimensional Vector Operations ***********************/

overror_t     __vcuf OVCUAPI   cudaVF_max( float *h_RetVal, fVector X, ui size );
overror_t     __vcuf OVCUAPI   cudaVF_min( float *h_RetVal, fVector X, ui size );
overror_t     __vcuf OVCUAPI   cudaVF_minmax( float *h_Min, float *h_Max, fVector X, ui size );
overror_t     __vcuf OVCUAPI   cudaVF_absmax( float *h_RetVal, fVector X, ui size );
overror_t     __vcuf OVCUAPI   cudaVF_absmin( float *h_RetVal, fVector X, ui size );
overror_t     __vcuf OVCUAPI   cudaVF_maxexp( int *h_RetVal, fVector X, ui size );
overror_t     __vcuf OVCUAPI   cudaVF_minexp( int *h_RetVal, fVector X, ui size );
overror_t     __vcuf OVCUAPI   cudaVF_maxind( float *h_RetVal, ui *Ind, fVector X, ui size );
overror_t     __vcuf OVCUAPI   cudaVF_minind( float *h_RetVal, ui *Ind, fVector X, ui size );
overror_t     __vcuf OVCUAPI   cudaVF_absmaxind( float *h_RetVal, ui *Ind, fVector X, ui size );
overror_t     __vcuf OVCUAPI   cudaVF_absminind( float *h_RetVal, ui *Ind, fVector X, ui size );
overror_t     __vcuf OVCUAPI   cudaVF_localmaxima( ui *h_nFound, uiVector Ind, fVector X, ui size );
overror_t     __vcuf OVCUAPI   cudaVF_localminima( ui *h_nFound, uiVector Ind, fVector X, ui size );
overror_t     __vcuf OVCUAPI   cudaVF_runmax( fVector Y, fVector X, ui size );
overror_t     __vcuf OVCUAPI   cudaVF_runmin( fVector Y, fVector X, ui size );
overror_t     __vcuf OVCUAPI   cudaVF_sum( float *h_RetVal, fVector X, ui size );
overror_t     __vcuf OVCUAPI   cudaVF_prod( float *h_RetVal, fVector X, ui size );
overror_t     __vcuf OVCUAPI   cudaVF_runsum( fVector Y, fVector X, ui size );
overror_t     __vcuf OVCUAPI   cudaVF_runprod( fVector Y, fVector X, ui size );
int           __vcuf OVCUAPI   cudaVF_iselementC( fVector Tab, ui size, float C );   // returns 1, if C is found in Tab, otherwise 0
overror_t     __vcuf OVCUAPI   cudaVF_iselementV( ui *h_nFound, fVector Y, fVector X, ui sizex, fVector Tab, ui sizetab );
overror_t     __vcuf OVCUAPI   cudaVF_centerOfGravityInd( float *h_RetVal,  fVector X, ui size );
overror_t     __vcuf OVCUAPI   cudaVF_centerOfGravityV( float *h_RetVal, fVector X, fVector Y, ui size );

   /*  cusdVF_ variant: return value stored on device:  */
overror_t    __vcuf OVCUAPI   cusdVF_max( float *d_RetVal, fVector X, ui size );
overror_t    __vcuf OVCUAPI   cusdVF_min( float *d_RetVal, fVector X, ui size );
overror_t    __vcuf OVCUAPI   cusdVF_minmax( float *d_Min, float *d_Max, fVector X, ui size );
overror_t    __vcuf OVCUAPI   cusdVF_absmax( float *d_RetVal, fVector X, ui size );
overror_t    __vcuf OVCUAPI   cusdVF_absmin( float *d_RetVal, fVector X, ui size );
overror_t    __vcuf OVCUAPI   cusdVF_maxexp( int *d_RetVal, fVector X, ui size );
overror_t    __vcuf OVCUAPI   cusdVF_minexp( int *d_RetVal, fVector X, ui size );
overror_t    __vcuf OVCUAPI   cusdVF_maxind( float *d_RetVal, ui *h_Ind, fVector X, ui size );
overror_t    __vcuf OVCUAPI   cusdVF_minind( float *d_RetVal, ui *h_Ind, fVector X, ui size );
overror_t    __vcuf OVCUAPI   cusdVF_absmaxind( float *d_RetVal, ui *h_Ind, fVector X, ui size );
overror_t    __vcuf OVCUAPI   cusdVF_absminind( float *d_RetVal, ui *h_Ind, fVector X, ui size );
overror_t    __vcuf OVCUAPI   cusdVF_sum( float *d_RetVal, fVector X, ui size );
overror_t    __vcuf OVCUAPI   cusdVF_prod( float *d_RetVal, fVector X, ui size );
int          __vcuf OVCUAPI   cusdVF_iselementC( fVector Tab, ui size, float *C );
overror_t    __vcuf OVCUAPI   cusdVF_centerOfGravityInd( float *d_RetVal, fVector X, ui size );
overror_t    __vcuf OVCUAPI   cusdVF_centerOfGravityV( float *d_RetVal, fVector X, fVector Y, ui size );


/**************** Statistical Functions and Building Blocks *************/

overror_t  __vcuf OVCUAPI   cudaVF_sumabs( float *h_RetVal, fVector X, ui size );
overror_t  __vcuf OVCUAPI   cudaVF_mean( float *h_RetVal, fVector X, ui size );
overror_t  __vcuf OVCUAPI   cudaVF_meanwW( float *h_RetVal, fVector X, fVector Wt, ui size );
overror_t  __vcuf OVCUAPI   cudaVF_meanabs( float *h_RetVal, fVector X, ui size );
overror_t  __vcuf OVCUAPI   cudaVF_selected_mean( float *h_RetVal, ui *nsel, fVector X, ui size, float XMin, float XMax ); 
overror_t  __vcuf OVCUAPI   cudaVF_median( float *h_RetVal, fVector X, ui size );
overror_t  __vcuf OVCUAPI   cudaVF_sumdevC( float *h_RetVal, fVector X, ui size, float C );
overror_t  __vcuf OVCUAPI   cudaVF_sumdevV( float *h_RetVal, fVector X, fVector Y, ui size );
overror_t  __vcuf OVCUAPI   cudaVF_avdevC( float *h_RetVal, fVector X, ui size, float C );
overror_t  __vcuf OVCUAPI   cudaVF_avdevV( float *h_RetVal, fVector X, fVector Y, ui size );
overror_t  __vcuf OVCUAPI   cudaVF_ssq( float *h_RetVal, fVector X, ui size );  /* sum-of-squares */
overror_t  __vcuf OVCUAPI   cudaVF_rms( float *h_RetVal, fVector X, ui size );  /* root of the mean square */
overror_t  __vcuf OVCUAPI   cudaVF_ssqdevC( float *h_RetVal, fVector X, ui size, float C );
overror_t  __vcuf OVCUAPI   cudaVF_ssqdevV( float *h_RetVal, fVector X, fVector Y, ui size );
overror_t  __vcuf OVCUAPI   cudaVF_meanvar( float *h_RetMean, float *h_RetVar, fVector X, ui size );
overror_t  __vcuf OVCUAPI   cudaVF_meanvarwW( float *h_RetMean, float *h_RetVar, fVector X, fVector Wt, ui size );
overror_t  __vcuf OVCUAPI   cudaVF_varianceC( float *h_RetVal, fVector X, ui size, float C );
overror_t  __vcuf OVCUAPI   cudaVF_varianceV( float *h_RetVal, fVector X, fVector Y, ui size );
overror_t  __vcuf OVCUAPI   cudaVF_varianceCwW( float *h_RetVal, fVector X, fVector Wt, ui size, float C );
overror_t  __vcuf OVCUAPI   cudaVF_varianceVwW( float *h_RetVal, fVector X, fVector Y, fVector Wt, ui size );
overror_t  __vcuf OVCUAPI   cudaVF_chi2( float *h_RetVal, fVector X, fVector Y, fVector InvVar, ui size );
overror_t  __vcuf OVCUAPI   cudaVF_chiabs( float *h_RetVal, fVector X, fVector Y, fVector Wt, ui size );
overror_t  __vcuf OVCUAPI   cudaVF_corrcoeff( float *h_RetVal, fVector X, fVector Y, ui size, float Xmean, float Ymean );
overror_t  __vcuf OVCUAPI   cudaVF_linregress( fVector h_Param, fVector X, fVector Y, ui size );
overror_t  __vcuf OVCUAPI   cudaVF_linregresswW( fVector h_Param, fVector X, fVector Y, fVector InvVar, ui size );
overror_t  __vcuf OVCUAPI   cudaVF_distribution( ui *h_nOutside, uiVector Abund, fVector Limits, ui nbins, fVector X, ui sizex, int mode );
overror_t  __vcuf OVCUAPI   cudaVF_min_max_mean_stddev( fVector h_Stats, fVector X, ui siz );

	/*  cusdV_ variant: return value stored on device: */
overror_t  __vcuf OVCUAPI   cusdVF_sumabs( float *d_RetVal, fVector X, ui size );
overror_t  __vcuf OVCUAPI   cusdVF_mean( float *d_RetVal, fVector X, ui size );
overror_t  __vcuf OVCUAPI   cusdVF_meanwW( float *d_RetVal, fVector X, fVector Wt, ui size );
overror_t  __vcuf OVCUAPI   cusdVF_meanabs( float *d_RetVal, fVector X, ui size );
overror_t  __vcuf OVCUAPI   cusdVF_selected_mean( float *d_RetVal, ui *d_nsel, fVector X, ui size, float *d_XMin, float *d_XMax ); 
overror_t  __vcuf OVCUAPI   cusdVF_median( float *d_RetVal, fVector X, ui size );
overror_t  __vcuf OVCUAPI   cusdVF_sumdevC( float *d_RetVal, fVector X, ui size, float *d_C );
overror_t  __vcuf OVCUAPI   cusdVF_sumdevV( float *d_RetVal, fVector X, fVector Y, ui size );
overror_t  __vcuf OVCUAPI   cusdVF_avdevC( float *d_RetVal, fVector X, ui size, float *d_C );
overror_t  __vcuf OVCUAPI   cusdVF_avdevV( float *d_RetVal, fVector X, fVector Y, ui size );
overror_t  __vcuf OVCUAPI   cusdVF_ssq( float *d_RetVal, fVector X, ui size );  /* sum-of-squares */
overror_t  __vcuf OVCUAPI   cusdVF_rms( float *d_RetVal, fVector X, ui size );  /* root of the mean square */
overror_t  __vcuf OVCUAPI   cusdVF_ssqdevC( float *d_RetVal, fVector X, ui size, float *d_C );
overror_t  __vcuf OVCUAPI   cusdVF_ssqdevV( float *d_RetVal, fVector X, fVector Y, ui size );
overror_t  __vcuf OVCUAPI   cusdVF_meanvar( float *d_RetVal, float *Var, fVector X, ui size );
overror_t  __vcuf OVCUAPI   cusdVF_meanvarwW( float *d_RetVal, float *Var, fVector X, fVector Wt, ui size );
overror_t  __vcuf OVCUAPI   cusdVF_varianceC( float *d_RetVal, fVector X, ui size, float *d_C );
overror_t  __vcuf OVCUAPI   cusdVF_varianceV( float *d_RetVal, fVector X, fVector Y, ui size );
overror_t  __vcuf OVCUAPI   cusdVF_varianceCwW( float *d_RetVal, fVector X, fVector Wt, ui size, float *d_C );
overror_t  __vcuf OVCUAPI   cusdVF_varianceVwW( float *d_RetVal, fVector X, fVector Y, fVector Wt, ui size );
overror_t  __vcuf OVCUAPI   cusdVF_chi2( float *d_RetVal, fVector X, fVector Y, fVector InvVar, ui size );
overror_t  __vcuf OVCUAPI   cusdVF_chiabs( float *d_RetVal, fVector X, fVector Y, fVector Wt, ui size );
overror_t  __vcuf OVCUAPI   cusdVF_corrcoeff( float *d_RetVal, fVector X, fVector Y, ui size, float *d_Xmean, float *d_Ymean );
overror_t  __vcuf OVCUAPI   cusdVF_linregress( fVector d_Param, fVector X, fVector Y, ui size );
overror_t  __vcuf OVCUAPI   cusdVF_linregresswW( fVector d_Param, fVector X, fVector Y, fVector InvVar, ui size );
overror_t  __vcuf OVCUAPI   cusdVF_distribution( ui *d_nOutside, uiVector Abund, fVector Limits, ui nbins, fVector X, ui sizex, int mode );
overror_t  __vcuf OVCUAPI   cusdVF_min_max_mean_stddev( fVector d_Stats, fVector X, ui siz );


/*********  Fourier Transforms, Convolutions, Filtering  ****************/

#if defined __cplusplus && defined _CMATH_CLASSDEFS
} // following function cannot be extern "C"
#endif
fComplex  __vf   cudaVF_getRspEdit( void );
#if defined __cplusplus && defined _CMATH_CLASSDEFS
extern "C" {
#endif
#if defined __cplusplus && defined _CMATH_CLASSDEFS && defined __BORLANDC__ && defined _WIN64
} // cannot be extern "C" for C++Builder on Win64, if fComplex is a class
#endif
void  __vf  cudaVF_setRspEdit( fComplex Trunc );
#if defined __cplusplus && defined _CMATH_CLASSDEFS && defined __BORLANDC__ && defined _WIN64
extern "C" {
#endif
overror_t   __vcuf OVCUAPI   cudaVF_FFT( fVector Y, fVector X, ui size, int dir );
overror_t   __vcuf OVCUAPI   cudaVF_2FFT( fVector Y1, fVector Y2, fVector X1, fVector X2, ui size, int dir );
overror_t   __vcuf OVCUAPI   cudaVF_FFTtoC( cfVector Y, fVector X, ui size );
overror_t   __vcuf OVCUAPI   cudaVF_filter( fVector Y, fVector X, fVector Flt, ui size );
overror_t   __vcuf OVCUAPI   cudaVF_autocorr( fVector Y, fVector X, ui size );
overror_t   __vcuf OVCUAPI   cudaVF_xcorr( fVector Z, fVector X, fVector Y, ui size );
overror_t   __vcuf OVCUAPI   cudaVF_spectrum( float *h_pfc, fVector Spc, ui specsiz, fVector X, ui xsiz, fVector Win );
overror_t   __vcuf OVCUAPI   cusdVF_spectrum( float *d_pfc, fVector Spc, ui specsiz, fVector X, ui xsiz, fVector Win );
                /* xsiz >= n*specsiz,  Winsiz = 2*specsiz ! returns psd at Nyquist frequ. */
overror_t  __vcuf OVCUAPI   cudaVF_convolve( fVector Y, fVector Flt, fVector X, fVector Rsp, ui size );
overror_t  __vcuf OVCUAPI   cudaVF_deconvolve( fVector Y, fVector Flt, fVector X, fVector Rsp, ui size );


/********************** Analysis ****************************************/

overror_t    __vcuf OVCUAPI   cudaVF_derivC( fVector Y, fVector X, ui size, float Deltat );
overror_t    __vcuf OVCUAPI   cusdVF_derivC( fVector Y, fVector X, ui size, float *d_Deltat );
overror_t    __vcuf OVCUAPI   cudaVF_derivV( fVector Z, fVector X, fVector Y, ui size );
overror_t    __vcuf OVCUAPI   cudaVF_integralC( float *h_RetVal, fVector X, ui size, float Deltat );
overror_t    __vcuf OVCUAPI   cudaVF_integralV( float *h_RetVal, fVector X, fVector Y, ui size );
overror_t    __vcuf OVCUAPI   cusdVF_integralC( float *d_RetVal, fVector X, ui size, float *d_Deltat );
overror_t    __vcuf OVCUAPI   cusdVF_integralV( float *d_RetVal, fVector X, fVector Y, ui size );
overror_t    __vcuf OVCUAPI   cudaVF_runintegralC( fVector Y, fVector X, ui size, float Deltat );
overror_t    __vcuf OVCUAPI   cusdVF_runintegralC( fVector Y, fVector X, ui size, float *d_Deltat );
overror_t    __vcuf OVCUAPI   cudaVF_runintegralV( fVector Z, fVector X, fVector Y, ui size );
overror_t    __vcuf OVCUAPI   cudaVF_smooth( fVector Y, fVector X, ui size, unsigned deg );
overror_t    __vcuf OVCUAPI   cudaVF_biquad( fVector Y, fVector X, ui siz, fVector h_Param );
overror_t    __vcuf OVCUAPI   cusdVF_biquad( fVector Y, fVector X, ui siz, fVector d_Param );
overror_t    __vcuf OVCUAPI   cudaVF_ismonoton( int *h_isSorted, fVector X, ui size ); 
overror_t    __vcuf OVCUAPI   cusdVF_ismonoton( int *d_isSorted, fVector X, ui size ); 
	/* isSorted = 1 for ascending or flat, -1 for descending, 0 for non-sorted */

/****************** Geometrical Vector Arithmetics **************************/

overror_t    __vcuf OVCUAPI   cudaVF_scalprod( float *h_RetVal, fVector X, fVector Y, ui size );
overror_t    __vcuf OVCUAPI   cudaVF_Euclid( float *h_RetVal, fVector X, ui size );
#define cudaVF_euclid cudaVF_Euclid
overror_t  __vcuf OVCUAPI   cusdVF_scalprod( float *retval, fVector X, fVector Y, ui size );
overror_t  __vcuf OVCUAPI   cusdVF_Euclid( float *retval, fVector X, ui size );
#define cusdVF_euclid cusdVF_Euclid
overror_t      __vcuf OVCUAPI   cudaVF_xprod( fVector Z, fVector X, fVector Y );


/***************************  Input and Output *****************************
	The input/output functions involve memory transfers from device
	to host memory or vice versa. The generic cudaVF_input/output functions
	allocate their own host buffers, whereas the cudaVF_xxx_buf functions
	take a user-supplied buffer h_Wk and are much more efficient.          */

overror_t  __vf    cudaVF_fprint( FILE *stream, fVector X, ui size, unsigned nperline, unsigned linewidth );
overror_t  __vf    cudaVF_cprint( fVector X, ui size, unsigned nperline );
#define       cudaVF_print( x, sz, npl )  cudaVF_fprint( stdout, x, sz, npl, 80 )
overror_t  __vf    cudaVF_fprint_buf( FILE *stream, fVector d_X, ui size, unsigned nperline, unsigned linewidth, fVector h_Wk );
overror_t  __vf    cudaVF_cprint_buf( fVector d_X, ui size, unsigned nperline, fVector h_Wk );
#define       cudaVF_print_buf( d_x, sz, npl, h_Wk )  cudaVF_fprint_buf( stdout, d_x, sz, npl, 80, h_Wk )
 /*  cudaVF_print, cudaVF_cprint are usable only for console applications!  */
overror_t  __vf    cudaVF_write( FILE *stream, fVector X, ui size  );
overror_t  __vf    cudaVF_write_buf( FILE *stream, fVector d_X, ui size, fVector h_Wk );
                     /* cudaVF_write, cudaVF_read in ascii format */
#if !((defined __BORLANDC__) && (__BORLANDC__ < 0x710))
		/* modern compiler versions:  */
	overror_t  __vf    cudaVF_read( fVector X, ui size, FILE *stream );
	overror_t  __vf    cudaVF_read_buf( fVector d_X, ui size, FILE *stream, fVector h_Wk );
#else /* older Borland compiler versions need separate implementation */
	overror_t  __vf    cudaVF_read1( fVector X, ui size, FILE *stream );
	overror_t  __vf    cudaVF_read1_buf( fVector d_X, ui size, FILE *stream, fVector h_Wk );
	#define cudaVF_read     cudaVF_read1
	#define cudaVF_read_buf cudaVF_read1_buf
#endif
overror_t  __vf cudaVF_store( FILE *stream, fVector X, ui size );
overror_t  __vf cudaVF_recall( fVector X, ui size, FILE *stream );
overror_t  __vf cudaVF_store_buf( FILE *stream, fVector d_X, ui size, fVector h_Wk );
overror_t  __vf cudaVF_recall_buf( fVector d_X, ui size, FILE *stream, fVector h_Wk );
                     /* cudaVF_store, cudaVF_recall in binary format */

#ifdef __cplusplus
}    //  end of extern "C"
         // alternative syntax of convolution and deconvolution:
    inline overror_t cudaVF_convolve( fVector Y, fVector Flt, fVector X, fVector Rsp,
                              ui size, float TruncRe, float TruncIm )
    {   cudaVF_setRspEdit( fcplx( TruncRe, TruncIm ) );
        return( cudaVF_convolve( Y, Flt, X, Rsp, size ));
    }
    inline overror_t cudaVF_deconvolve( fVector Y, fVector Flt, fVector X, fVector Rsp,
                                ui size, float TruncRe, float TruncIm )
    {   cudaVF_setRspEdit( fcplx( TruncRe, TruncIm ) );
        return( cudaVF_deconvolve( Y, Flt, X, Rsp, size ));
    }
#endif   /*  __cplusplus   */


	
/******************  VFcu_ functions: **********************************
	act on host memory, using the CUDA device for processing
************************************************************************/


#ifdef __cplusplus
extern "C" {
#endif

/*******************  Initialization **********************************/

void  __vcuf OVCUAPI   VFcu_equ0( fVector X, ui size );
void  __vcuf OVCUAPI   VFcu_equ1( fVector X, ui size );
void  __vcuf OVCUAPI   VFcu_equm1( fVector X, ui size );
void  __vcuf OVCUAPI   VFcu_equC( fVector X, ui size, float C );
void  __vcuf OVCUAPI   VFcu_equV( fVector Y, fVector X, ui size );  /* copies from device to device */
void  __vcuf OVCUAPI   VFxcu_equV( fVector Y, fVector X, ui size, float A, float B );
void  __vcuf OVCUAPI   VFcu_ramp( fVector X, ui size, float Start, float Rise );
void  __vcuf OVCUAPI   VFcu_Parzen( fVector X, ui size );
void  __vcuf OVCUAPI   VFcu_Welch( fVector X, ui size );
void  __vcuf OVCUAPI   VFcu_Hann( fVector X, ui size );
#define VFcu_Hanning VFcu_Hann
void  __vcuf OVCUAPI   VFcu_comb( fVector X, ui size, ui step, float C );
/* no V?cu_random, V?cu_noise functions: random generation runs on CPU anyway */


/***************  Data-type interconversions  *************************/
       /* for rounding functions, see VFmath.h ! */

void  __vcuf OVCUAPI   Vcu_BItoF(  fVector Y, biVector X, ui size );
void  __vcuf OVCUAPI   Vcu_SItoF(  fVector Y, siVector X, ui size );
void  __vcuf OVCUAPI   Vcu_ItoF(   fVector Y, iVector  X, ui size );
void  __vcuf OVCUAPI   Vcu_LItoF(  fVector Y, liVector X, ui size );
void  __vcuf OVCUAPI   Vcu_QItoF(  fVector Y, qiVector X, ui size );

void  __vcuf OVCUAPI   Vcu_UBtoF(  fVector Y, ubVector X, ui size );
void  __vcuf OVCUAPI   Vcu_UStoF(  fVector Y, usVector X, ui size );
void  __vcuf OVCUAPI   Vcu_UtoF(   fVector Y, uVector  X, ui size );
void  __vcuf OVCUAPI   Vcu_ULtoF(  fVector Y, ulVector X, ui size );
#ifdef _WIN64
void  __vcuf OVCUAPI   Vcu_UQtoF(  fVector Y, uqVector X, ui size );
#endif

void  __vcuf OVCUAPI   Vcu_FtoD( dVector Y, fVector X, ui size );
void  __vcuf OVCUAPI   Vcu_DtoF( fVector Y, dVector X, ui size );


/****************  Index-oriented manipulations ***********************/

void  __vcuf OVCUAPI   VFcu_reflect( fVector X, ui size );
void  __vcuf OVCUAPI   VFcu_rev( fVector Y, fVector X, ui size );
void  __vcuf OVCUAPI   VFcu_rotate( fVector Y, fVector X, ui size, ssize_t pos );
void  __vcuf OVCUAPI   VFcu_rotate_buf( fVector Y, fVector X, ui size, ssize_t pos, fVector Buf );
void  __vcuf OVCUAPI   VFcu_delete( fVector X, ui size, ui pos );
void  __vcuf OVCUAPI   VFcu_insert( fVector X, ui size, ui pos, float C );
void  __vcuf OVCUAPI   VFcu_sort( fVector Y, fVector X, ui size, int dir );
void  __vcuf OVCUAPI   VFcu_sortind( uiVector Ind, fVector X, ui size, int dir );
void  __vcuf OVCUAPI   VFcu_subvector( fVector Y, ui sizey, fVector X, ssize_t samp );
  /* no VFcu_indpick, VFcu_indput possible! */
ui    __vcuf OVCUAPI   VFcu_searchC( fVector XTab, ui size, float C, int mode );
void  __vcuf OVCUAPI   VFcu_searchV( uiVector Ind, fVector X, ui sizex, fVector Tab, ui sizetab, int mode );

void  __vcuf OVCUAPI   VFcu_polyinterpol( fVector Y, fVector X, ui sizex,
                        fVector XTab, fVector YTab, ui sizetab, unsigned deg );
void  __vcuf OVCUAPI   VFcu_ratinterpol( fVector Y, fVector X, ui sizex,
                        fVector XTab, fVector YTab, ui sizetab, unsigned deg );
void  __vcuf OVCUAPI   VFcu_natCubSplineInterpol( fVector Y, fVector X, ui sizex,
                    fVector XTab, fVector YTab, ui sizetab );
	/* no VFcu_splinederiv2! must be executed on host anyway */
void  __vcuf OVCUAPI   VFcu_splineinterpol( fVector Y, fVector X, ui sizex,
                    fVector XTab, fVector YTab, fVector Y2Tab, ui sizetab );


/***************** Functions of a sub-set of elements  ********************/

void  __vcuf OVCUAPI   VFcu_subvector_equC(  fVector Y, ui subsiz, ui samp, float C );
void  __vcuf OVCUAPI   VFcu_subvector_equV(  fVector Y, ui subsiz, ui samp, fVector X );
    /*   for arithmetic functions of subsets, see <VFmath.h>  */

/**************** One-Dimensional Vector Operations ***********************/

float     __vcuf OVCUAPI   VFcu_max( fVector X, ui size );
float     __vcuf OVCUAPI   VFcu_min( fVector X, ui size );
float     __vcuf OVCUAPI   VFcu_minmax( float *RetMax, fVector X, ui size );
float     __vcuf OVCUAPI   VFcu_absmax( fVector X, ui size );
float     __vcuf OVCUAPI   VFcu_absmin( fVector X, ui size );
int       __vcuf OVCUAPI   VFcu_maxexp( fVector X, ui size );
int       __vcuf OVCUAPI   VFcu_minexp( fVector X, ui size );
float     __vcuf OVCUAPI   VFcu_maxind( ui *Ind, fVector X, ui size );
float     __vcuf OVCUAPI   VFcu_minind( ui *Ind, fVector X, ui size );
float     __vcuf OVCUAPI   VFcu_absmaxind( ui *Ind, fVector X, ui size );
float     __vcuf OVCUAPI   VFcu_absminind( ui *Ind, fVector X, ui size );
ui         __vcuf OVCUAPI   VFcu_localmaxima( uiVector Ind, fVector X, ui size );
ui         __vcuf OVCUAPI   VFcu_localminima( uiVector Ind, fVector X, ui size );
void       __vcuf OVCUAPI   VFcu_runmax( fVector Y, fVector X, ui size );
void       __vcuf OVCUAPI   VFcu_runmin( fVector Y, fVector X, ui size );
float      __vcuf OVCUAPI   VFcu_sum( fVector X, ui size );
float      __vcuf OVCUAPI   VFcu_prod( fVector X, ui size );
void       __vcuf OVCUAPI   VFcu_runsum( fVector Y, fVector X, ui size );
void       __vcuf OVCUAPI   VFcu_runprod( fVector Y, fVector X, ui size );
int        __vcuf OVCUAPI   VFcu_iselementC( fVector Tab, ui size, float C );
ui         __vcuf OVCUAPI   VFcu_iselementV( fVector Y, fVector X, ui sizex, fVector Tab, ui sizetab );

float     __vcuf OVCUAPI   VFcu_centerOfGravityInd( fVector X, ui size );
float     __vcuf OVCUAPI   VFcu_centerOfGravityV( fVector X, fVector Y, ui size );


/**************** Statistical Functions and Building Blocks *************/

float  __vcuf OVCUAPI   VFcu_sumabs( fVector X, ui size );
float  __vcuf OVCUAPI   VFcu_mean( fVector X, ui size );
float  __vcuf OVCUAPI   VFcu_meanwW( fVector X, fVector Wt, ui size );
float  __vcuf OVCUAPI   VFcu_meanabs( fVector X, ui size );
float  __vcuf OVCUAPI   VFcu_selected_mean( ui *nsel, fVector X, ui size, float XMin, float XMax ); 
float  __vcuf OVCUAPI   VFcu_median( fVector X, ui size );
float  __vcuf OVCUAPI   VFcu_sumdevC( fVector X, ui size, float C );
float  __vcuf OVCUAPI   VFcu_sumdevV( fVector X, fVector Y, ui size );
float  __vcuf OVCUAPI   VFcu_avdevC( fVector X, ui size, float C );
float  __vcuf OVCUAPI   VFcu_avdevV( fVector X, fVector Y, ui size );
float  __vcuf OVCUAPI   VFcu_ssq( fVector X, ui size );  /* sum-of-squares */
float  __vcuf OVCUAPI   VFcu_rms( fVector X, ui size );  /* root of the mean square */
float  __vcuf OVCUAPI   VFcu_ssqdevC( fVector X, ui size, float C );
float  __vcuf OVCUAPI   VFcu_ssqdevV( fVector X, fVector Y, ui size );
float  __vcuf OVCUAPI   VFcu_meanvar( float *Var, fVector X, ui size );
float  __vcuf OVCUAPI   VFcu_meanvarwW( float *Var, fVector X, fVector Wt, ui size );
float  __vcuf OVCUAPI   VFcu_varianceC( fVector X, ui size, float C );
float  __vcuf OVCUAPI   VFcu_varianceV( fVector X, fVector Y, ui size );
float  __vcuf OVCUAPI   VFcu_varianceCwW( fVector X, fVector Wt, ui size, float C );
float  __vcuf OVCUAPI   VFcu_varianceVwW( fVector X, fVector Y, fVector Wt, ui size );
float  __vcuf OVCUAPI   VFcu_chi2( fVector X, fVector Y, fVector InvVar, ui size );
float  __vcuf OVCUAPI   VFcu_chiabs( fVector X, fVector Y, fVector Wt, ui size );
float  __vcuf OVCUAPI   VFcu_corrcoeff( fVector X, fVector Y, ui size, float Xmean, float Ymean );
void   __vcuf OVCUAPI   VFcu_linregress( fVector h_Param, fVector X, fVector Y, ui size );
void   __vcuf OVCUAPI   VFcu_linregresswW( fVector h_Param, fVector X, fVector Y, fVector InvVar, ui size );
ui     __vcuf OVCUAPI   VFcu_distribution( uiVector Abund, fVector Limits, ui nbins, fVector X, ui sizex, int mode );
void   __vcuf OVCUAPI   VFcu_min_max_mean_stddev( fVector Stats, fVector X, ui siz );


/*********  Fourier Transforms, Convolutions, Filtering  ****************/

void   __vcuf OVCUAPI   VFcu_FFT( fVector Y, fVector X, ui size, int dir );
void   __vcuf OVCUAPI   VFcu_2FFT( fVector Y1, fVector Y2, fVector X1, fVector X2, ui size, int dir );
void   __vcuf OVCUAPI   VFcu_FFTtoC( cfVector Y, fVector X, ui size );
void   __vcuf OVCUAPI   VFcu_filter( fVector Y, fVector X, fVector Flt, ui size );
void   __vcuf OVCUAPI   VFcu_autocorr( fVector Y, fVector X, ui size );
void   __vcuf OVCUAPI   VFcu_xcorr( fVector Z, fVector X, fVector Y, ui size );
float  __vcuf OVCUAPI   VFcu_spectrum( fVector Spc, ui specsiz, fVector X, ui xsiz, fVector Win );
                /* xsiz >= n*specsiz,  Winsiz = 2*specsiz ! returns psd at Nyquist frequ. */
void  __vcuf OVCUAPI   VFcu_convolve( fVector Y, fVector Flt, fVector X, fVector Rsp, ui size );
void  __vcuf OVCUAPI   VFcu_deconvolve( fVector Y, fVector Flt, fVector X, fVector Rsp, ui size );


/********************** Analysis ****************************************/

void    __vcuf OVCUAPI   VFcu_derivC( fVector Y, fVector X, ui size, float Deltat );
void    __vcuf OVCUAPI   VFcu_derivV( fVector Z, fVector X, fVector Y, ui size );
float   __vcuf OVCUAPI   VFcu_integralC( fVector X, ui size, float Deltat );
void    __vcuf OVCUAPI   VFcu_runintegralC( fVector Y, fVector X, ui size, float Deltat );
float   __vcuf OVCUAPI   VFcu_integralV( fVector X, fVector Y, ui size );
void    __vcuf OVCUAPI   VFcu_runintegralV( fVector Z, fVector X, fVector Y, ui size );
void    __vcuf OVCUAPI   VFcu_smooth( fVector Y, fVector X, ui size, unsigned deg );
void    __vcuf OVCUAPI   VFcu_biquad( fVector Y, fVector X, ui siz, fVector Param );
/* Param[0]=a0, [1]=a1, [2]=a2, [3]=b1, [4]=b2, [5]=x(-1), [6]=x(-2), [7]=y(-1), [8]=y(-2) */
int     __vcuf OVCUAPI   VFcu_ismonoton( fVector X, ui size );

/****************** Geometrical Vector Arithmetics **************************/

float    __vcuf OVCUAPI   VFcu_scalprod( fVector X, fVector Y, ui size );
float    __vcuf OVCUAPI   VFcu_Euclid( fVector X, ui size );
#define VFcu_euclid VFcu_Euclid
void      __vcuf OVCUAPI   VFcu_xprod( fVector Z, fVector X, fVector Y );


#ifdef __cplusplus
}    //  end of extern "C"
         // alternative syntax of convolution and deconvolution:
    inline void VFcu_convolve( fVector Y, fVector Flt, fVector X, fVector Rsp,
                              ui size, float TruncRe, float TruncIm )
    {   fComplex OldEdit = cudaVF_getRspEdit();
		cudaVF_setRspEdit( fcplx( TruncRe, TruncIm ) );
        VFcu_convolve( Y, Flt, X, Rsp, size );
		cudaVF_setRspEdit( OldEdit );
    }
    inline void VFcu_deconvolve( fVector Y, fVector Flt, fVector X, fVector Rsp,
                                ui size, float TruncRe, float TruncIm )
    {   fComplex OldEdit = cudaVF_getRspEdit();
		cudaVF_setRspEdit( fcplx( TruncRe, TruncIm ) );
        VFcu_deconvolve( Y, Flt, X, Rsp, size );
		cudaVF_setRspEdit( OldEdit );
    }
#endif   /*  __cplusplus   */


#endif   /*  __CUDAVFSTD_H  */
