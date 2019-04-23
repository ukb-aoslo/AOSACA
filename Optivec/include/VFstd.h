/*  VFstd.h

  vector management functions:
  manipulations on whole arrays or vectors of data type "float"
  (real numbers)

  Copyright (c) 1996-2017 by OptiCode - Dr. Martin Sander Software Dev.
  All Rights Reserved.
*/

#ifndef __VFSTD_H
#define __VFSTD_H
#if !defined( __VECLIB_H )
#include <VecLib.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif

/*************************  Generation  **************************/

fVector  __vf  VF_vector( ui size );
fVector  __vf  VF_vector0( ui size );
#if defined (_MSC_VER) && defined (_DEBUG)
    fVector  __vf  VF_vector_dbg( ui size );
    fVector  __vf  VF_vector0_dbg( ui size );
    #if defined (_INC_CRTDBG) && defined (_CRTDBG_MAP_ALLOC) 
	    /* Automatic mapping for memory-leak detection by CRT debugging switched on? */ 
        #define VF_vector  VF_vector_dbg
        #define VF_vector0 VF_vector0_dbg
    #endif
#else
    #define VF_vector_dbg  VF_vector
    #define VF_vector0_dbg VF_vector0
#endif

/***************  Addressing single vector elements ******************/

float _VFAR * __vf VF_Pelement( fVector X, ui n );
      /* returns a pointer to the n'th element of X. For the memory model
         HUGE, the pointer is normalized. */
#define VF_element( X, n )  (*VF_Pelement( X, n ))
void  __vf VF_getElement( float *y, fVector X, ui n );
void  __vf VF_setElement( fVector X, ui n, float C );

/*******************  Initialization **********************************/

void  __vf  VF_equ0( fVector X, ui size );
void  __vf  VF_equ1( fVector X, ui size );
void  __vf  VF_equm1( fVector X, ui size );
void  __vf  VF_equC( fVector X, ui size, float C );
void  __vf  VF_equV( fVector Y, fVector X, ui size );
void  __vf  VFx_equV( fVector Y, fVector X, ui size, float A, float B );
void  __vf  VF_ramp( fVector X, ui size, float Start, float Rise );
void  __vf  VF_Parzen( fVector X, ui size );
void  __vf  VF_Welch( fVector X, ui size );
void  __vf  VF_Hann( fVector X, ui size );
#define VF_Hanning VF_Hann
void  __vf  VF_comb( fVector X, ui size, ui step, float C );

/******  Linear Congruential random generator with Bays-Durham shuffle:  ***********
   seed!=0 --> initialization of state. seed==0 --> continue series from previous call with the same state.
   Random quality of VF_randomLC is much better than of VF_noiseLC                                         */
void  __vf  VF_randomLC( fVector X, ui size, long seed, float MinVal, float MaxVal, V_RANDOMLCSTATE *state );
void  __vf  VF_noiseLC( fVector X, ui size, long seed, float Amp, V_RANDOMLCSTATE *state );
/**  simplified version: returns new seed. Series not continuous across calls due to new state initialization: */
long  __vf  VF_random( fVector X, ui size, long seed, float MinVal, float MaxVal );
long  __vf  VF_noise( fVector X, ui size, long seed, float Amp );

/***************  Data-type interconversions  *************************/
       /* for rounding functions, see VFmath.h ! */

void  __vf   V_BItoF(  fVector Y, biVector X, ui size );
void  __vf   V_SItoF(  fVector Y, siVector X, ui size );
void  __vf   V_ItoF(   fVector Y, iVector  X, ui size );
void  __vf   V_LItoF(  fVector Y, liVector X, ui size );
void  __vf   V_QItoF(  fVector Y, qiVector X, ui size );

void  __vf   V_UBtoF(  fVector Y, ubVector X, ui size );
void  __vf   V_UStoF(  fVector Y, usVector X, ui size );
void  __vf   V_UtoF(   fVector Y, uVector  X, ui size );
void  __vf   V_ULtoF(  fVector Y, ulVector X, ui size );
#ifdef _WIN64
void  __vf   V_UQtoF(  fVector Y, uqVector X, ui size );
#endif

void  __vf   V_FtoD( dVector Y, fVector X, ui size );
void  __vf   V_DtoF( fVector Y, dVector X, ui size );
#if (defined __BORLANDC__) && !(defined _WIN64)   /* 80-bit IEEE numbers supported */
    void  __vf   V_FtoE( eVector Y, fVector X, ui size );
    void  __vf   V_EtoF( fVector Y, eVector X, ui size );
#else  /* no IEEE number support with Visual C++ */
    #define V_FtoE V_FtoD
    #define V_EtoF V_DtoF
#endif


/****************  Index-oriented manipulations ***********************/

void  __vf  VF_reflect( fVector X, ui size );
void  __vf  VF_rev( fVector Y, fVector X, ui size );
void  __vf  VF_rotate( fVector Y, fVector X, ui size, ssize_t pos );
void  __vf  VF_rotate_buf( fVector Y, fVector X, ui size, ssize_t pos, fVector Buf );
void  __vf  VF_delete( fVector X, ui size, ui pos );
void  __vf  VF_insert( fVector X, ui size, ui pos, float C );
void  __vf  VF_sort( fVector Y, fVector X, ui size, int dir );
void  __vf  VF_sortind( uiVector Ind, fVector X, ui size, int dir );
void  __vf  VF_subvector( fVector Y, ui sizey, fVector X, ssize_t samp );
void  __vf  VF_indpick( fVector Y, uiVector Ind, ui sizey, fVector X );
void  __vf  VF_indput(  fVector Y, fVector X, uiVector Ind, ui sizex );
ui    __vf  VF_searchC( fVector X, ui size, float C, int mode );
void  __vf  VF_searchV( uiVector Ind, fVector X, ui sizex,
                                     fVector Tab, ui sizetab, int mode );

void  __vf  VF_polyinterpol( fVector Y, fVector X, ui sizex,
                        fVector XTab, fVector YTab, ui sizetab, unsigned deg );
void  __vf  VF_ratinterpol( fVector Y, fVector X, ui sizex,
                        fVector XTab, fVector YTab, ui sizetab, unsigned deg );
void  __vf  VF_natCubSplineInterpol( fVector Y, fVector X, ui sizex,
                    fVector XTab, fVector YTab, ui sizetab );
void  __vf  VF_splinederiv2( fVector Y2, fVector XTab, fVector YTab,
                            ui tabsize, int specify, float Yp0, float Ypn );
void  __vf  VF_splineinterpol( fVector Y, fVector X, ui sizex,
                    fVector XTab, fVector YTab, fVector Y2Tab, ui sizetab );


/***************** Functions of a sub-set of elements  ********************/

void  __vf  VF_subvector_equC(  fVector Y, ui subsiz, ui samp, float C );
void  __vf  VF_subvector_equV(  fVector Y, ui subsiz, ui samp, fVector X );
     /*  for arithmetic functions performed on subvectors, see <VFmath.h> */


/**************** One-Dimensional Vector Operations ***********************/

float      __vf  VF_max( fVector X, ui size );
float      __vf  VF_min( fVector X, ui size );
float      __vf  VF_absmax( fVector X, ui size );
float      __vf  VF_absmin( fVector X, ui size );
int        __vf  VF_maxexp( fVector X, ui size );
int        __vf  VF_minexp( fVector X, ui size );
float      __vf  VF_maxind( ui _VFAR *Ind, fVector X, ui size );
float      __vf  VF_minind( ui _VFAR *Ind, fVector X, ui size );
float      __vf  VF_absmaxind( ui _VFAR *Ind, fVector X, ui size );
float      __vf  VF_absminind( ui _VFAR *Ind, fVector X, ui size );
ui         __vf  VF_localmaxima( uiVector Ind, fVector X, ui size );
ui         __vf  VF_localminima( uiVector Ind, fVector X, ui size );
void       __vf  VF_runmax( fVector Y, fVector X, ui size );
void       __vf  VF_runmin( fVector Y, fVector X, ui size );
float      __vf  VF_sum( fVector X, ui size );
float      __vf  VF_prod( fVector X, ui size );
void       __vf  VF_runsum( fVector Y, fVector X, ui size );
void       __vf  VF_runprod( fVector Y, fVector X, ui size );
int        __vf  VF_iselementC( fVector Tab, ui size, float C );
ui         __vf  VF_iselementV( fVector Y, fVector X, ui sizex,
                                fVector Tab, ui sizetab );
float      __vf  VF_centerOfGravityInd( fVector X, ui size );
float      __vf  VF_centerOfGravityV( fVector X, fVector Y, ui size );

/**************** Statistical Functions and Building Blocks *************/

float   __vf  VF_mean( fVector X, ui size );
float   __vf  VF_meanwW( fVector X, fVector Wt, ui size );
float   __vf  VF_sumabs( fVector X, ui size );
float   __vf  VF_meanabs( fVector X, ui size );
float   __vf  VF_selected_mean( ui _VFAR *nsel, fVector X, ui size,
                 float XMin, float XMax ); /* takes only x with Min<=x<=Max */
float   __vf  VF_median( fVector X, ui size );
float   __vf  VF_sumdevC( fVector X, ui size, float C );
float   __vf  VF_sumdevV( fVector X, fVector Y, ui size );
float   __vf  VF_avdevC( fVector X, ui size, float C );
float   __vf  VF_avdevV( fVector X, fVector Y, ui size );
float   __vf  VF_ssq( fVector X, ui size );  /* sum-of-squares */
float   __vf  VF_rms( fVector X, ui size );  /* root of the mean square */
float   __vf  VF_ssqdevC( fVector X, ui size, float C );
float   __vf  VF_ssqdevV( fVector X, fVector Y, ui size );
float   __vf  VF_meanvar(  float  _VFAR *Var, fVector X, ui size );
float   __vf  VF_meanvarwW(  float  _VFAR *Var, fVector X, fVector Wt, ui size );
float   __vf  VF_varianceC( fVector X, ui size, float C );
float   __vf  VF_varianceV( fVector X, fVector Y, ui size );
float   __vf  VF_varianceCwW( fVector X, fVector Wt, ui size, float C );
float   __vf  VF_varianceVwW( fVector X, fVector Y, fVector Wt, ui size );
float   __vf  VF_chi2( fVector X, fVector Y, fVector InvVar, ui size );
float   __vf  VF_chiabs( fVector X, fVector Y, fVector Wt, ui size );
float   __vf  VF_corrcoeff( fVector X, fVector Y, ui size,
                            float Xmean, float Ymean );
ui      __vf  VF_distribution( uiVector Abund, fVector Limits, ui nbins,
                               fVector X, ui sizex, int mode );
void    __vf  VF_min_max_mean_stddev( fVector Stats, fVector X, ui siz );


void  __vf  VF_linregress( fVector Param, fVector X, fVector Y, ui size );
void  __vf  VF_linregresswW( fVector Param, fVector X, fVector Y,
                             fVector InvVar, ui size );
     /* more linear and nonlinear data fitting routines need MatrixLib
        and are declared in <MFstd.h> !                                */


/*********  Fourier Transforms, Convolutions, Filtering  ****************/

#if defined __cplusplus && defined _CMATH_CLASSDEFS
} // following function cannot be extern "C"
#endif
fComplex  __vf   VF_getRspEdit( void );
#if defined __cplusplus && defined _CMATH_CLASSDEFS
extern "C" {
#endif
#if defined __cplusplus && defined _CMATH_CLASSDEFS && defined __BORLANDC__ && defined _WIN64
} // cannot be extern "C" for C++Builder on Win64, if fComplex is a class
#endif
void  __vf   VF_setRspEdit( fComplex Trunc );
#if defined __cplusplus && defined _CMATH_CLASSDEFS && defined __BORLANDC__ && defined _WIN64
extern "C" {
#endif

void  __vf   VFp_FFT( fVector Y, fVector X, ui size, int dir );
void  __vf   VFp_FFTtoC( cfVector Y, fVector X, ui size );
void  __vf   VFp_filter( fVector Y, fVector X, fVector Flt, ui size );
void  __vf   VFp_autocorr( fVector Y, fVector X, ui size );
void  __vf   VFp_xcorr( fVector Z, fVector X, fVector Y, ui size );
float __vf   VFp_spectrum( fVector Spc, ui specsiz, fVector X, ui xsiz, fVector Win );
                              /* xsiz >= n*specsiz,  Winsiz = 2*specsiz ! */
void  __vf   VFp_convolve( fVector Y, fVector Flt, fVector X, fVector Rsp, ui size );
void  __vf   VFp_deconvolve( fVector Y, fVector Flt, fVector X, fVector Rsp, ui size );
void  __vf   VFb_FFT( fVector Y, fVector X, ui size, int dir, fVector Buf );
void  __vf   VFb_FFTtoC( cfVector Y, fVector X, ui size, cfVector Buf );

#define VF_FFT         VFp_FFT
#define VF_FFTtoC      VFp_FFTtoC
#define VF_convolve    VFp_convolve
#define VF_deconvolve  VFp_deconvolve
#define VF_filter      VFp_filter
#define VF_autocorr    VFp_autocorr
#define VF_xcorr       VFp_xcorr
#define VF_spectrum    VFp_spectrum

void  __vf   VFl_FFT( fVector Y, fVector X, ui size, int dir );
void  __vf   VFl_FFTtoC( cfVector Y, fVector X, ui size );
void  __vf   VFl_filter( fVector Y, fVector X, fVector Flt, ui size );
void  __vf   VFl_autocorr( fVector Y, fVector X, ui size );
void  __vf   VFl_xcorr( fVector Z, fVector X, fVector Y, ui size );
float __vf   VFl_spectrum( fVector Spc, ui specsiz, fVector X, ui xsiz,
                           fVector Win );
                           /* xsiz >= n*specsiz,  Winsiz = 2*specsiz ! */
void  __vf   VFl_convolve( fVector Y, fVector Flt, fVector X,
                           fVector Rsp, ui size );
void  __vf   VFl_deconvolve( fVector Y, fVector Flt, fVector X,
                             fVector Rsp, ui size );
void  __vf   VFs_FFT( fVector Y, fVector X, ui size, int dir );
void  __vf   VFs_FFTtoC( cfVector Y, fVector X, ui size );
void  __vf   VFs_filter( fVector Y, fVector X, fVector Flt, ui size );
void  __vf   VFs_autocorr( fVector Y, fVector X, ui size );
void  __vf   VFs_xcorr( fVector Z, fVector X, fVector Y, ui size );
float __vf   VFs_spectrum( fVector Spc, ui specsiz, fVector X, ui xsiz,
                           fVector Win );
void  __vf   VFs_convolve( fVector Y, fVector Flt, fVector X,
                           fVector Rsp, ui size );
void  __vf   VFs_deconvolve( fVector Y, fVector Flt, fVector X,
                             fVector Rsp, ui size );

/********************** Analysis ****************************************/

void    __vf  VF_derivC( fVector Y, fVector X, ui size, float Deltat );
void    __vf  VF_derivV( fVector Z, fVector X, fVector Y, ui size );
float   __vf  VF_integralC( fVector X, ui size, float Deltat );
void    __vf  VF_runintegralC( fVector Y, fVector X, ui size, float Deltat );
float   __vf  VF_integralV( fVector X, fVector Y, ui size );
void    __vf  VF_runintegralV( fVector Z, fVector X, fVector Y, ui size );
void    __vf  VF_smooth( fVector Y, fVector X, ui size, unsigned deg );
void    __vf  VF_biquad( fVector Y, fVector X, ui siz, fVector Param );
/* Param[0]=a0, [1]=a1, [2]=a2, [3]=b1, [4]=b2, [5]=x(-1), [6]=x(-2), [7]=y(-1), [8]=y(-2) */
int     __vf  VF_ismonoton( fVector X, ui size );
	/* returns 1 for ascending or flat, -1 for descending, 0 for non-sorted */

/****************** Geometrical Vector Arithmetics **************************/

float     __vf  VF_scalprod( fVector X, fVector Y, ui size );
void      __vf  VF_xprod( fVector Z, fVector X, fVector Y );
float     __vf  VF_Euclid( fVector X, ui size );
#define VF_euclid VF_Euclid

/***************************  Input and Output *****************************/

void  __vf    VF_fprint( FILE _VFAR *stream, fVector X, ui size, unsigned nperline, unsigned linewidth );
void  __vf    VF_cprint( fVector X, ui size, unsigned nperline );
#define       VF_print( x, sz, npl )  VF_fprint( stdout, x, sz, npl, 80 )
 /*  VF_print, VF_cprint are usable only for console applications!  */
void  __vf    VF_write( FILE _VFAR *stream, fVector X, ui size  );
void  __vf    VF_nwrite( FILE _VFAR *stream, unsigned n, ui size, ... );
void  __vf    VF_setWriteFormat( char _VFAR *FormatString );
                                            /* for VF_write and VF_nwrite */
void  __vf    VF_setWriteSeparate( char _VFAR *SepString ); /* for VF_write */
void  __vf    VF_setNWriteSeparate( char _VFAR *SepString ); /* for VF_nwrite */
                     /* VF_write, VF_read in ascii format */
#if !((defined __BORLANDC__) && (__BORLANDC__ < 0x710))
		/* modern compiler versions:  */
	void  __vf    VF_read( fVector X, ui size, FILE _VFAR *stream );
	void  __vf    VF_nread( unsigned n, ui size, FILE _VFAR *stream, ... );
#else /* older Borland compiler versions need separate implementation */
	void  __vf    VF_read1( fVector X, ui size, FILE _VFAR *stream );
	void  __vf    VF_nread1( unsigned n, ui size, FILE _VFAR *stream, ... );
	#define VF_read  VF_read1
	#define VF_nread VF_nread1
#endif
#ifdef V_HUGE
    void  __vf    VF_store( FILE _VFAR *stream, fVector X, ui size );
    void  __vf    VF_recall( fVector X, ui size, FILE _VFAR *stream );
#else
    #ifdef __cplusplus
         void  inline VF_store( FILE _VFAR *stream, fVector X, ui size )
         {    fwrite( X, sizeof(float), size, stream );
         }
         void  inline VF_recall( fVector X, ui size, FILE _VFAR *stream )
         {    fread(  X, sizeof(float), size, stream );
         }
    #else
        #define VF_store( str, X, sz )  \
                     fwrite( X, sizeof(float), sz, str )
        #define VF_recall( X, sz, str ) \
                     fread(  X, sizeof(float), sz, str )
    #endif
#endif      /* VF_store, VF_recall in binary format */

#ifdef __cplusplus
}   // end of extern "C"
         // alternative syntax of convolution and deconvolution
    #if defined __FLAT__ || defined _WIN32
    inline void VFp_convolve( fVector Y, fVector Flt, fVector X, fVector Rsp,
                              ui size, float TruncRe, float TruncIm )
    {   VF_setRspEdit( fcplx( TruncRe, TruncIm ) );
        VFp_convolve( Y, Flt, X, Rsp, size );
    }
    inline void  VFp_deconvolve( fVector Y, fVector Flt, fVector X, fVector Rsp,
                                 ui size, float TruncRe, float TruncIm )
    {   VF_setRspEdit( fcplx( TruncRe, TruncIm ) );
        VFp_deconvolve( Y, Flt, X, Rsp, size );
    }
    #endif
    inline void VFl_convolve( fVector Y, fVector Flt, fVector X, fVector Rsp,
                              ui size, float TruncRe, float TruncIm )
    {   VF_setRspEdit( fcplx( TruncRe, TruncIm ) );
        VFl_convolve( Y, Flt, X, Rsp, size );
    }
    inline void  VFl_deconvolve( fVector Y, fVector Flt, fVector X, fVector Rsp,
                                 ui size, float TruncRe, float TruncIm )
    {   VF_setRspEdit( fcplx( TruncRe, TruncIm ) );
        VFl_deconvolve( Y, Flt, X, Rsp, size );
    }
    inline void VFs_convolve( fVector Y, fVector Flt, fVector X, fVector Rsp,
                              ui size, float TruncRe, float TruncIm )
    {   VF_setRspEdit( fcplx( TruncRe, TruncIm ) );
        VFs_convolve( Y, Flt, X, Rsp, size );
    }
    inline void  VFs_deconvolve( fVector Y, fVector Flt, fVector X, fVector Rsp,
                                 ui size, float TruncRe, float TruncIm )
    {   VF_setRspEdit( fcplx( TruncRe, TruncIm ) );
        VFs_deconvolve( Y, Flt, X, Rsp, size );
    }
#endif   /*  __cplusplus  */

#endif   /*  __VFSTD_H  */
