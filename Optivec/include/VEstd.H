/*  VEstd.h

  vector management functions:
  manipulations on whole arrays or vectors of data type "extended"
  (real numbers: long double)

  Copyright (c) 1996-2017 by OptiCode - Dr. Martin Sander Software Dev.
  All Rights Reserved.
*/

#ifndef __VESTD_H
#define __VESTD_H
#if !defined( __VECLIB_H )
#include <VecLib.h>
#endif


#if (defined __BORLANDC__) && !(defined _WIN64)   /* 80-bit IEEE supported:
                 the following 350 lines apply only to Borland C++ 32-bit */

#ifdef __cplusplus
extern "C" {
#endif

/*************************  Generation  **************************/

eVector  __vf  VE_vector( ui size );
eVector  __vf  VE_vector0( ui size );
#if defined (_MSC_VER) && defined (_DEBUG)
    eVector  __vf  VE_vector_dbg( ui size );
    eVector  __vf  VE_vector0_dbg( ui size );
    #if defined (_INC_CRTDBG) && defined (_CRTDBG_MAP_ALLOC) 
	    /* Automatic mapping for memory-leak detection by CRT debugging switched on? */ 
        #define VE_vector  VE_vector_dbg
        #define VE_vector0 VE_vector0_dbg
    #endif
#else
    #define VE_vector_dbg  VE_vector
    #define VE_vector0_dbg VE_vector0
#endif

/***************  Addressing single vector elements ******************/

extended _VFAR * __vf VE_Pelement( eVector X, ui n );
      /* returns a pointer to the n'th element of X. For the memory model
         HUGE, the pointer is normalized. */
#define VE_element( X, n )  (*VE_Pelement( X, n ))
void  __vf VE_getElement( extended *y, eVector X, ui n );
void  __vf VE_setElement( eVector X, ui n, extended C );

/*******************  Initialization **********************************/

void  __vf  VE_equ0( eVector X, ui size );
void  __vf  VE_equ1( eVector X, ui size );
void  __vf  VE_equm1( eVector X, ui size );
void  __vf  VE_equC( eVector X, ui size, extended C );
void  __vf  VE_equV( eVector Y, eVector X, ui size );
void  __vf  VEx_equV( eVector Y, eVector X, ui size,
                                       extended A, extended B );
void  __vf  VE_ramp( eVector X, ui size,
                                    extended Start, extended Rise );
void  __vf  VE_Parzen( eVector X, ui size );
void  __vf  VE_Welch( eVector X, ui size );
void  __vf  VE_Hann( eVector X, ui size );
#define VE_Hanning VE_Hann
void  __vf  VE_comb( eVector X, ui size, ui step, extended C );

/******  Linear Congruential random generator with Bays-Durham shuffle:  ***********
   seed!=0 --> initialization of state. seed==0 --> continue series from previous call with the same state.
   Random quality of VE_randomLC is much better than of VE_noiseLC                                         */
void  __vf  VE_randomLC( eVector X, ui size, long seed, extended MinVal, extended MaxVal, V_RANDOMLCSTATE *state );
void  __vf  VE_noiseLC( eVector X, ui size, long seed, extended Amp, V_RANDOMLCSTATE *state );
/**  simplified version: returns new seed. Series not continuous across calls due to new state initialization: */
long  __vf  VE_random( eVector X, ui size, long seed, extended MinVal, extended MaxVal );
long  __vf  VE_noise( eVector X, ui size, long seed, extended Amp );

/***************  Data-type interconversions  *************************/
       /* for rounding functions, see VEmath.h ! */

void  __vf   V_BItoE(  eVector Y, biVector X, ui size );
void  __vf   V_SItoE(  eVector Y, siVector X, ui size );
void  __vf   V_ItoE(   eVector Y, iVector  X, ui size );
void  __vf   V_LItoE(  eVector Y, liVector X, ui size );
void  __vf   V_QItoE(  eVector Y, qiVector X, ui size );

void  __vf   V_UBtoE(  eVector Y, ubVector X, ui size );
void  __vf   V_UStoE(  eVector Y, usVector X, ui size );
void  __vf   V_UtoE(   eVector Y, uVector  X, ui size );
void  __vf   V_ULtoE(  eVector Y, ulVector X, ui size );

void  __vf   V_FtoE( eVector Y, fVector X, ui size );
void  __vf   V_EtoF( fVector Y, eVector X, ui size );
void  __vf   V_DtoE( eVector Y, dVector X, ui size );
void  __vf   V_EtoD( dVector Y, eVector X, ui size );


/****************  Index-oriented manipulations ***********************/


void  __vf  VE_reflect( eVector X, ui size );
void  __vf  VE_rev( eVector Y, eVector X, ui size );
void  __vf  VE_rotate( eVector Y, eVector X, ui size, ssize_t pos );
void  __vf  VE_rotate_buf( eVector Y, eVector X, ui size, ssize_t pos, eVector Buf );
void  __vf  VE_delete( eVector X, ui size, ui pos );
void  __vf  VE_insert( eVector X, ui size, ui pos, extended C );
void  __vf  VE_sort( eVector Y, eVector X, ui size, int dir );
void  __vf  VE_sortind( uiVector Ind, eVector X, ui size, int dir );
void  __vf  VE_subvector( eVector Y, ui sizey, eVector X, ssize_t samp );
void  __vf  VE_indpick( eVector Y, uiVector Ind, ui sizey, eVector X );
void  __vf  VE_indput(  eVector Y, eVector X, uiVector Ind, ui sizex );
ui    __vf  VE_searchC( eVector X, ui size, extended C, int mode );
void  __vf  VE_searchV( uiVector Ind, eVector X, ui sizex,
                                     eVector Tab, ui sizetab, int mode );

void  __vf  VE_polyinterpol( eVector Y, eVector X, ui sizex,
                   eVector XTab, eVector YTab, ui sizetab, unsigned deg );
void  __vf  VE_ratinterpol( eVector Y, eVector X, ui sizex,
                   eVector XTab, eVector YTab, ui sizetab, unsigned deg );
void  __vf  VE_natCubSplineInterpol( eVector Y, eVector X, ui sizex,
                   eVector XTab, eVector YTab, ui sizetab );
void  __vf  VE_splinederiv2( eVector Y2, eVector XTab, eVector YTab,
                   ui size, int specify, extended Yp0, extended Ypn );
void  __vf  VE_splineinterpol( eVector Y, eVector X, ui sizex,
                   eVector XTab, eVector YTab, eVector Y2Tab, ui sizetab );


/***************** Functions of a sub-set of elements  ********************/

void  __vf  VE_subvector_equC(  eVector Y, ui subsiz, ui samp, extended C );
void  __vf  VE_subvector_equV(  eVector Y, ui subsiz, ui samp, eVector X );
    /*   for arithmetic functions of subsets, see <VEmath.h>  */


/**************** One-Dimensional Vector Operations ***********************/

extended  __vf  VE_max( eVector X, ui size );
extended  __vf  VE_min( eVector X, ui size );
extended  __vf  VE_absmax( eVector X, ui size );
extended  __vf  VE_absmin( eVector X, ui size );
int       __vf  VE_maxexp( eVector X, ui size );
int       __vf  VE_minexp( eVector X, ui size );
extended  __vf  VE_maxind( ui _VFAR *Ind, eVector X, ui size );
extended  __vf  VE_minind( ui _VFAR *Ind, eVector X, ui size );
extended  __vf  VE_absmaxind( ui _VFAR *Ind, eVector X, ui size );
extended  __vf  VE_absminind( ui _VFAR *Ind, eVector X, ui size );
ui        __vf  VE_localmaxima( uiVector Ind, eVector X, ui size );
ui        __vf  VE_localminima( uiVector Ind, eVector X, ui size );
void      __vf  VE_runmax( eVector Y, eVector X, ui size );
void      __vf  VE_runmin( eVector Y, eVector X, ui size );
extended  __vf  VE_sum( eVector X, ui size );
extended  __vf  VE_prod( eVector X, ui size );
void      __vf  VE_runsum( eVector Y, eVector X, ui size );
void      __vf  VE_runprod( eVector Y, eVector X, ui size );
int       __vf  VE_iselementC( eVector Tab, ui size, extended C );
ui        __vf  VE_iselementV( eVector Y, eVector X, ui sizex,
                               eVector Tab, ui sizetab );
extended  __vf  VE_centerOfGravityInd( eVector X, ui size );
extended  __vf  VE_centerOfGravityV( eVector X, eVector Y, ui size );

/**************** Statistical Functions and Building Blocks *************/

extended __vf  VE_sumabs( eVector X, ui size );
extended __vf  VE_mean( eVector X, ui size );
extended __vf  VE_meanwW( eVector X, eVector Wt, ui size );
extended __vf  VE_meanabs( eVector X, ui size );
extended __vf  VE_selected_mean( ui _VFAR *nsel, eVector X, ui size,
                extended XMin, extended XMax ); /* takes only x with Min<=x<=Max */
extended __vf  VE_median( eVector X, ui size );
extended __vf  VE_sumdevC( eVector X, ui size, extended C );
extended __vf  VE_sumdevV( eVector X, eVector Y, ui size );
extended __vf  VE_avdevC( eVector X, ui size, extended C );
extended __vf  VE_avdevV( eVector X, eVector Y, ui size );
extended __vf  VE_ssq( eVector X, ui size );
extended __vf  VE_rms( eVector X, ui size );
extended __vf  VE_ssqdevC( eVector X, ui size, extended C );
extended __vf  VE_ssqdevV( eVector X, eVector Y, ui size );
extended __vf  VE_meanvar(  extended _VFAR *Var, eVector X, ui size );
extended __vf  VE_meanvarwW(  extended _VFAR *Var, eVector X, eVector Wt, ui size );
extended __vf  VE_varianceC( eVector X, ui size, extended C );
extended __vf  VE_varianceV( eVector X, eVector Y, ui size );
extended __vf  VE_varianceCwW( eVector X, eVector Wt, ui size, extended C );
extended __vf  VE_varianceVwW( eVector X, eVector Y, eVector Wt, ui size );
extended __vf  VE_chi2( eVector X, eVector Y, eVector InvVar, ui size );
extended __vf  VE_chiabs( eVector X, eVector Y, eVector Wt, ui size );
extended __vf  VE_corrcoeff( eVector X, eVector Y, ui size,
                             extended Xmean, extended Ymean );
ui       __vf  VE_distribution( uiVector Abund, eVector Limits, ui nbins,
                             eVector X, ui sizex, int mode );
void     __vf  VE_min_max_mean_stddev( eVector Stats, eVector X, ui siz );

void  __vf  VE_linregress( eVector Param, eVector X, eVector Y, ui size );
void  __vf  VE_linregresswW( eVector Param, eVector X, eVector Y,
                             eVector InvVar, ui size );
     /* more (linear and nonlinear) data fitting routines need MatrixLib
        and are declared in <MEstd.h> !                                */


/*********  Fourier Transforms, Convolutions, Filtering  ****************/

#if defined __cplusplus && defined _CMATH_CLASSDEFS
} // following function cannot be extern "C"
#endif
eComplex  __vf   VE_getRspEdit( void );
#if defined __cplusplus && defined _CMATH_CLASSDEFS
extern "C" {
#endif
void     __vf VE_setRspEdit( eComplex Trunc );

void     __vf VEp_FFT( eVector Y, eVector X, ui size, int dir );
void     __vf VEp_FFTtoC( ceVector Y, eVector X, ui size );
void     __vf VEp_filter( eVector Y, eVector X, eVector Flt, ui size );
void     __vf VEp_autocorr( eVector Y, eVector X, ui size );
void     __vf VEp_xcorr( eVector Z, eVector X, eVector Y, ui size );
extended __vf VEp_spectrum( eVector Spc, ui specsiz, eVector X, ui xsiz, eVector Win );
                              /* xsiz >= n*specsiz,  Winsiz = 2*specsiz ! */
void     __vf VEp_convolve( eVector Y, eVector Flt, eVector X,
                               eVector Rsp, ui size );
void     __vf VEp_deconvolve( eVector Y, eVector Flt, eVector X,
                            eVector Rsp, ui size );
void     __vf VEb_FFT( eVector Y, eVector X, ui size, int dir, eVector Buf );
void     __vf VEb_FFTtoC( ceVector Y, eVector X, ui size, ceVector Buf );
#define VE_FFT         VEp_FFT
#define VE_FFTtoC      VEp_FFTtoC
#define VE_convolve    VEp_convolve
#define VE_deconvolve  VEp_deconvolve
#define VE_filter      VEp_filter
#define VE_autocorr    VEp_autocorr
#define VE_xcorr       VEp_xcorr
#define VE_spectrum    VEp_spectrum

void     __vf VEl_FFT( eVector Y, eVector X, ui size, int dir );
void     __vf VEl_FFTtoC( ceVector Y, eVector X, ui size );
void     __vf VEl_filter( eVector Y, eVector X, eVector Flt, ui size );
void     __vf VEl_autocorr( eVector Y, eVector X, ui size );
void     __vf VEl_xcorr( eVector Z, eVector X, eVector Y, ui size );
extended __vf VEl_spectrum( eVector Spc, ui specsiz, eVector X, ui xsiz,
                            eVector Win );
                           /* xsiz >= n*specsiz,  Winsiz = 2*specsiz ! */
void     __vf VEl_convolve( eVector Y, eVector Flt, eVector X,
                            eVector Rsp, ui size );
void     __vf VEl_deconvolve( eVector Y, eVector Flt, eVector X,
                            eVector Rsp, ui size );

void     __vf VEs_FFT( eVector Y, eVector X, ui size, int dir );
void     __vf VEs_FFTtoC( ceVector Y, eVector X, ui size );
void     __vf VEs_filter( eVector Y, eVector X, eVector Flt, ui size );
void     __vf VEs_autocorr( eVector Y, eVector X, ui size );
void     __vf VEs_xcorr( eVector Z, eVector X, eVector Y, ui size );
extended __vf VEs_spectrum( eVector Spc, ui specsiz, eVector X, ui xsiz,
                            eVector Win );
void     __vf VEs_convolve( eVector Y, eVector Flt, eVector X,
                            eVector Rsp, ui size );
void     __vf VEs_deconvolve( eVector Y, eVector Flt, eVector X,
                            eVector Rsp, ui size );


/********************** Analysis ****************************************/

void     __vf  VE_derivC( eVector Y, eVector X, ui size, extended Deltat );
void     __vf  VE_derivV( eVector Z, eVector X, eVector Y, ui size );
extended __vf  VE_integralC( eVector X, ui size, extended Deltat );
void     __vf  VE_runintegralC( eVector Y, eVector X, ui size, extended Deltat );
extended __vf  VE_integralV( eVector X, eVector Y, ui size );
void     __vf  VE_runintegralV( eVector Z, eVector X, eVector Y, ui size );
void     __vf  VE_smooth( eVector Y, eVector X, ui size, unsigned deg );
void     __vf  VE_biquad( eVector Y, eVector X, ui siz, eVector Param );
/* Param[0]=a0, [1]=a1, [2]=a2, [3]=b1, [4]=b2, [5]=x(-1), [6]=x(-2), [7]=y(-1), [8]=y(-2) */
int      __vf  VE_ismonoton( eVector X, ui size );
	/* returns 1 for ascending or flat, -1 for descending, 0 for non-sorted */


/****************** Geometrical Vector Arithmetics **************************/

extended  __vf  VE_scalprod( eVector X, eVector Y, ui size );
void      __vf  VE_xprod( eVector Z, eVector X, eVector Y );
extended  __vf  VE_Euclid( eVector X, ui size );


/***************************  Input and Output *****************************/

void  __vf    VE_fprint( FILE _VFAR *stream, eVector X, ui size,
                                    unsigned nperline, unsigned linewidth );
void  __vf VE_cprint( eVector X, ui size, unsigned nperline );
#define       VE_print( x, sz, npl )  VE_fprint( stdout, x, sz, npl, 80 )
  /*  VE_print, VE_cprint usable only for console applications! */
void  __vf  VE_write( FILE _VFAR *stream, eVector X, ui size  ); /* in ascii */
void  __vf  VE_nwrite( FILE _VFAR *stream, unsigned n, ui size, ... );
void  __vf  VE_setWriteFormat( char _VFAR *FormatString );
                                            /* for VE_write and VE_nwrite */
void  __vf  VE_setWriteSeparate( char _VFAR *SepString ); /* for VE_write */
void  __vf  VE_setNWriteSeparate( char _VFAR *SepString ); /* for VE_nwrite */
#if !((defined __BORLANDC__) && (__BORLANDC__ < 0x710))
		/* modern compiler versions:  */
	void  __vf    VE_read( eVector X, ui size, FILE _VFAR *stream );
	void  __vf    VE_nread( unsigned n, ui size, FILE _VFAR *stream, ... );
#else /* older Borland compiler versions need separate implementation */
	void  __vf    VE_read1( eVector X, ui size, FILE _VFAR *stream );
	void  __vf    VE_nread1( unsigned n, ui size, FILE _VFAR *stream, ... );
	#define VE_read  VE_read1
	#define VE_nread VE_nread1
#endif
#ifdef V_HUGE
    void  __vf  VE_store( FILE _VFAR *stream, eVector X, ui size );
    void  __vf  VE_recall( eVector X, ui size, FILE _VFAR *stream  );
#else
    #ifdef __cplusplus
         void  inline VE_store( FILE _VFAR *stream, eVector X, ui size )
         {    fwrite( X, sizeof(extended), size, stream );
         }
         void  inline VE_recall( eVector X, ui size, FILE _VFAR *stream )
         {    fread(  X, sizeof(extended), size, stream );
         }
    #else
        #define VE_store( str, X, sz )  \
                     fwrite( X, sizeof(extended), sz, str )
        #define VE_recall( X, sz, str ) \
                     fread(  X, sizeof(extended), sz, str )
    #endif
#endif      /* VE_store, VE_recall in binary format */

#ifdef __cplusplus
}  //  end of extern "C"
        // alternative syntax of convolution and deconvolution
    #if defined (__FLAT__)
    inline void  VEp_convolve( eVector Y, eVector Flt, eVector X, eVector Rsp,
                           ui size, extended TruncRe, extended TruncIm )
    {   VE_setRspEdit( ecplx( TruncRe, TruncIm ) );
        VEp_convolve( Y, Flt, X, Rsp, size );
    }
    inline void  VEp_deconvolve( eVector Y, eVector Flt, eVector X, eVector Rsp,
                           ui size, extended TruncRe, extended TruncIm )
    {   VE_setRspEdit( ecplx( TruncRe, TruncIm ) );
        VEp_deconvolve( Y, Flt, X, Rsp, size );
    }
    #endif
    inline void  VEl_convolve( eVector Y, eVector Flt, eVector X, eVector Rsp,
                           ui size, extended TruncRe, extended TruncIm )
    {   VE_setRspEdit( ecplx( TruncRe, TruncIm ) );
        VEl_convolve( Y, Flt, X, Rsp, size );
    }
    inline void  VEl_deconvolve( eVector Y, eVector Flt, eVector X, eVector Rsp,
                           ui size, extended TruncRe, extended TruncIm )
    {   VE_setRspEdit( ecplx( TruncRe, TruncIm ) );
        VEl_deconvolve( Y, Flt, X, Rsp, size );
    }
    inline void  VEs_convolve( eVector Y, eVector Flt, eVector X, eVector Rsp,
                           ui size, extended TruncRe, extended TruncIm )
    {   VE_setRspEdit( ecplx( TruncRe, TruncIm ) );
        VEs_convolve( Y, Flt, X, Rsp, size );
    }
    inline void  VEs_deconvolve( eVector Y, eVector Flt, eVector X, eVector Rsp,
                           ui size, extended TruncRe, extended TruncIm )
    {   VE_setRspEdit( ecplx( TruncRe, TruncIm ) );
        VEs_deconvolve( Y, Flt, X, Rsp, size );
    }
#endif    /*  __cplusplus  */



#else  /* no IEEE number support with all 64-bit compilers
		  and with the 32-bit compilers Visual C++, Watcom C, and Optima++:
		  Redirect to the corresponding VD_ functions */

#include <VDstd.h>
#define VE_vector      VD_vector
#define VE_vector0     VD_vector0
#define VE_vector_dbg  VD_vector_dbg
#define VE_vector0_dbg VD_vector0_dbg
#define VE_Pelement    VD_Pelement
#define VE_element( X, n )  (*VD_Pelement( X, n ))
#define VE_setElement  VD_setElement

#define VE_equ0         VD_equ0
#define VE_equ1         VD_equ1
#define VE_equm1        VD_equm1
#define VE_equC         VD_equC
#define VE_equV         VD_equV
#define VEx_equV        VDx_equV
#define VE_ramp         VD_ramp
#define VE_Parzen       VD_Parzen
#define VE_Welch        VD_Welch
#define VE_Hann         VD_Hann
#define VE_Hanning      VD_Hann
#define VE_comb         VD_comb
#define VE_randomLC     VD_randomLC
#define VE_noiseLC      VD_noiseLC
#define VE_random       VD_random
#define VE_noise        VD_noise
#define V_BItoE         V_BItoD
#define V_SItoE         V_SItoD
#define V_ItoE          V_ItoD
#define V_LItoE         V_LItoD
#define V_QItoE         V_QItoD
#define V_UBtoE         V_UBtoD
#define V_UStoE         V_UStoD
#define V_UtoE          V_UtoD
#define V_ULtoE         V_ULtoD

#define V_FtoE          V_FtoD
#define V_EtoF          V_DtoF
#define V_DtoE          VD_equV
#define V_EtoD          VD_equV

#define VE_reflect      VD_reflect
#define VE_rev          VD_rev
#define VE_rotate       VD_rotate
#define VE_rotate_buf   VD_rotate_buf
#define VE_delete       VD_delete
#define VE_insert       VD_insert
#define VE_sort         VD_sort
#define VE_sortind      VD_sortind
#define VE_subvector    VD_subvector
#define VE_indpick      VD_indpick
#define VE_indput       VD_indput

#define VE_searchC      VD_searchC
#define VE_searchV      VD_searchV
#define VE_polyinterpol VD_polyinterpol
#define VE_ratinterpol  VD_ratinterpol
#define VE_natCubSplineInterpol VD_natCubSplineInterpol
#define VE_splinederiv2 VD_splinederiv2
#define VE_splineinterpol VD_splineinterpol

#define VE_subvector_equC  VD_subvector_equC
#define VE_subvector_equV  VD_subvector_equV

#define VE_max          VD_max
#define VE_min          VD_min
#define VE_absmax       VD_absmax
#define VE_absmin       VD_absmin
#define VE_maxexp       VD_maxexp
#define VE_minexp       VD_minexp
#define VE_maxind       VD_maxind
#define VE_minind       VD_minind
#define VE_absmaxind    VD_absmaxind
#define VE_absminind    VD_absminind

#define VE_localmaxima  VD_localmaxima
#define VE_localminima  VD_localminima
#define VE_runmax       VD_runmax
#define VE_runmin       VD_runmin
#define VE_sum          VD_sum
#define VE_prod         VD_prod
#define VE_runsum       VD_runsum
#define VE_runprod      VD_runprod
#define VE_iselementC   VD_iselementC
#define VE_iselementV   VD_iselementV

#define VE_sumabs       VD_sumabs
#define VE_mean         VD_mean
#define VE_meanwW       VD_meanwW
#define VE_meanabs      VD_meanabs
#define VE_selected_mean VD_selected_mean
#define VE_median       VD_median
#define VE_sumdevC      VD_sumdevC
#define VE_sumdevV      VD_sumdevV
#define VE_avdevC       VD_avdevC
#define VE_avdevV       VD_avdevV
#define VE_ssq          VD_ssq
#define VE_rms          VD_rms
#define VE_ssqdevC      VD_ssqdevC
#define VE_ssqdevV      VD_ssqdevV
#define VE_meanvar      VD_meanvar
#define VE_meanvarwW    VD_meanvarwW
#define VE_varianceC    VD_varianceC
#define VE_varianceV    VD_varianceV
#define VE_varianceCwW  VD_varianceCwW
#define VE_varianceVwW  VD_varianceVwW
#define VE_chi2         VD_chi2
#define VE_chiabs       VD_chiabs
#define VE_corrcoeff    VD_corrcoeff
#define VE_distribution VD_distribution
#define VE_min_max_mean_stddev VD_min_max_mean_stddev
#define VE_linregress   VD_linregress
#define VE_linregresswW VD_linregresswW
#define VE_centerOfGravityInd VD_centerOfGravityInd
#define VE_centerOfGravityV   VD_centerOfGravityV

#define VE_setRspEdit   VD_setRspEdit
#define VE_getRspEdit   VD_getRspEdit
#define VEp_FFT         VDp_FFT
#define VEp_FFTtoC      VDp_FFTtoC
#define VEp_filter      VDp_filter
#define VEp_autocorr    VDp_autocorr
#define VEp_xcorr       VDp_xcorr
#define VEp_spectrum    VDp_spectrum
#define VEp_convolve    VDp_convolve
#define VEp_deconvolve  VDp_deconvolve
#define VEb_FFT         VDb_FFT
#define VEb_FFTtoC      VDb_FFTtoC
#define VEl_FFT         VDl_FFT
#define VEl_FFTtoC      VDl_FFTtoC
#define VEl_filter      VDl_filter
#define VEl_autocorr    VDl_autocorr
#define VEl_xcorr       VDl_xcorr
#define VEl_spectrum    VDl_spectrum
#define VEl_convolve    VDl_convolve
#define VEl_deconvolve  VDl_deconvolve
#define VEs_FFT         VDs_FFT
#define VEs_FFTtoC      VDs_FFTtoC
#define VEs_filter      VDs_filter
#define VEs_autocorr    VDs_autocorr
#define VEs_xcorr       VDs_xcorr
#define VEs_spectrum    VDs_spectrum
#define VEs_convolve    VDs_convolve
#define VEs_deconvolve  VDs_deconvolve
#define VE_FFT          VD_FFT
#define VE_FFTtoC       VD_FFTtoC
#define VE_filter       VD_filter
#define VE_autocorr     VD_autocorr
#define VE_xcorr        VD_xcorr
#define VE_spectrum     VD_spectrum
#define VE_convolve     VD_convolve
#define VE_deconvolve   VD_deconvolve

#define VE_derivC       VD_derivC
#define VE_derivV       VD_derivV
#define VE_integralC    VD_integralC
#define VE_runintegralC VD_runintegralC
#define VE_integralV    VD_integralV
#define VE_runintegralV VD_runintegralV
#define VE_smooth       VD_smooth
#define VE_biquad       VD_biquad
#define VE_ismonoton    VD_ismonoton

#define VE_scalprod     VD_scalprod
#define VE_xprod        VD_xprod
#define VE_Euclid       VD_Euclid

#define VE_fprint       VD_fprint
#define VE_cprint       VD_cprint
#define VE_print        VD_print
#define VE_write        VD_write
#define VE_read         VD_read
#define VE_nwrite       VD_nwrite
#define VE_nread        VD_nread
#define VE_setWriteFormat   VD_setWriteFormat
#define VE_setWriteSeparate VD_setWriteSeparate
#define VE_store        VD_store
#define VE_recall       VD_recall

#endif   /*  80-bit real support or not  */

#define VE_euclid VE_Euclid

#endif   /*  __VESTD_H  */
