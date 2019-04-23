/*   cudaVFuncs.h 

  OptiVec functions using CUDA:
  host functions, operating on device memory
  For the host functions, operating on host memory,
  see VcudaFuncs.h 

  These are the OptiVec functions present for data in CUDA device
  memory. They can be used only if you are developing CUDA code with
  NVIDIA's CUDA SDK.
  
  All these functions are contained in the libraries
  OVCUMTD.LIB   (working with the multi-thread debug runtime of Visual C++),
  OVCUMTR.LIB   (multi-thread release),
  OVCUMDD.LIB   (multi-thread debug DLL),
  OVCUMDR.LIB   (multi-thread release DLL)
  
  Copyright (c) 1996-2017 by OptiCode - Dr. Martin Sander Software Dev.
  All Rights Reserved.

  Please note:
  The OVCUxyz.LIB ibraries were created with NVIDA's CUDA SDK. 
  They include code which is copyrighted by NVIDIA Corporation.
  As far as NVIDIA's code is concerned, the following notices apply:

 *
 * Copyright 1993-2010 NVIDIA Corporation.  All rights reserved.
 *
 * NVIDIA MAKES NO REPRESENTATION ABOUT THE SUITABILITY OF THIS SOURCE 
 * CODE FOR ANY PURPOSE.  IT IS PROVIDED "AS IS" WITHOUT EXPRESS OR 
 * IMPLIED WARRANTY OF ANY KIND.  NVIDIA DISCLAIMS ALL WARRANTIES WITH 
 * REGARD TO THIS SOURCE CODE, INCLUDING ALL IMPLIED WARRANTIES OF 
 * MERCHANTABILITY, NONINFRINGEMENT, AND FITNESS FOR A PARTICULAR PURPOSE.
 * IN NO EVENT SHALL NVIDIA BE LIABLE FOR ANY SPECIAL, INDIRECT, INCIDENTAL, 
 * OR CONSEQUENTIAL DAMAGES, OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS 
 * OF USE, DATA OR PROFITS,  WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE 
 * OR OTHER TORTIOUS ACTION,  ARISING OUT OF OR IN CONNECTION WITH THE USE 
 * OR PERFORMANCE OF THIS SOURCE CODE.  
 *
 * U.S. Government End Users.   This source code is a "commercial item" as 
 * that term is defined at  48 C.F.R. 2.101 (OCT 1995), consisting  of 
 * "commercial computer  software"  and "commercial computer software 
 * documentation" as such terms are  used in 48 C.F.R. 12.212 (SEPT 1995) 
 * and is provided to the U.S. Government only as a commercial end item.  
 * Consistent with 48 C.F.R.12.212 and 48 C.F.R. 227.7202-1 through 
 * 227.7202-4 (JUNE 1995), all U.S. Government End Users acquire the 
 * source code with only those rights set forth herein. 
 *
 * Any use of this source code in individual and commercial software must 
 * include, in the user documentation and internal comments to the code,
 * the above Disclaimer and U.S. Government End Users Notice.

 */

#if !defined( __CUDAVECLIB_H )
#include <cudaVecLib.h>
#endif
#if !defined( __CUDAMATLIB_H )
#include <cudaMatLib.h>
#endif

 // make sure your include path contains the CUDA SDK include directories!
#include <cutil_inline.h>   

/******************  general definitions  *******************************/
#define __vcuf OVCUAPI __vf OVCUAPI  // CUDA API works with __stdcall, but name-mangling makes float2 and fComplex distinct;
                     // therefore use standard as for other OptiVec functions

#define fComplexAsfloat2( _cfx_ ) (*(float2 *)(&_cfx_))
#define float2AsfComplex( _cfx_ ) (*(fComplex *)(&_cfx_))

/*************  OptiVec CUDA API functions ****************************
*************  called from host, operating on device memory: *********/
extern "C" {
void __vcuf OVCUAPI cudaVF_equ0( fVector X, ui siz );
void __vcuf OVCUAPI cudaVF_equ1( fVector X, ui siz );
void __vcuf OVCUAPI cudaVF_equC( fVector X, ui siz, float C );

int __vcuf OVCUAPI cudaVF_acos( fVector Y, fVector X, ui siz );
int __vcuf OVCUAPI cudaVF_asin( fVector Y, fVector X, ui siz );
int __vcuf OVCUAPI cudaVF_atan( fVector Y, fVector X, ui siz );
int __vcuf OVCUAPI cudaVF_cos( fVector Y, fVector X, ui siz );
int __vcuf OVCUAPI cudaVF_cos2( fVector Y, fVector X, ui siz );
int __vcuf OVCUAPI cudaVF_cosh( fVector Y, fVector X, ui siz );
int __vcuf OVCUAPI cudaVF_cosec( fVector Y, fVector X, ui siz );
int __vcuf OVCUAPI cudaVF_cosec2( fVector Y, fVector X, ui siz );
int __vcuf OVCUAPI cudaVF_cosech( fVector Y, fVector X, ui siz );
int __vcuf OVCUAPI cudaVF_cot( fVector Y, fVector X, ui siz );
int __vcuf OVCUAPI cudaVF_cot2( fVector Y, fVector X, ui siz );
int __vcuf OVCUAPI cudaVF_coth( fVector Y, fVector X, ui siz );
int __vcuf OVCUAPI cudaVF_erf( fVector Y, fVector X, ui siz );
int __vcuf OVCUAPI cudaVF_erfc( fVector Y, fVector X, ui siz );
int __vcuf OVCUAPI cudaVF_exp( fVector Y, fVector X, ui siz );
int __vcuf OVCUAPI cudaVF_expc( fVector Y, fVector X, ui siz );
int __vcuf OVCUAPI cudaVF_expmx2( fVector Y, fVector X, ui siz );
int __vcuf OVCUAPI cudaVF_Kepler( fVector Y, fVector X, ui siz, float T, float e );
int __vcuf OVCUAPI cudaVF_Langevin( fVector Y, fVector X, ui siz );
int __vcuf OVCUAPI cudaVF_log( fVector Y, fVector X, ui siz );
int __vcuf OVCUAPI cudaVF_log2( fVector Y, fVector X, ui siz );
int __vcuf OVCUAPI cudaVF_log10( fVector Y, fVector X, ui siz );
int __vcuf OVCUAPI cudaVF_pow( fVector Y, fVector X, ui siz, float Expo );
int __vcuf OVCUAPI cudaVF_pow2( fVector Y, fVector X, ui siz );
int __vcuf OVCUAPI cudaVF_pow10( fVector Y, fVector X, ui siz );
int __vcuf OVCUAPI cudaVF_sec( fVector Y, fVector X, ui siz );
int __vcuf OVCUAPI cudaVF_sec2( fVector Y, fVector X, ui siz );
int __vcuf OVCUAPI cudaVF_sech( fVector Y, fVector X, ui siz );
int __vcuf OVCUAPI cudaVF_sech2( fVector Y, fVector X, ui siz );
int __vcuf OVCUAPI cudaVF_sin( fVector Y, fVector X, ui siz );
int __vcuf OVCUAPI cudaVF_sin2( fVector Y, fVector X, ui siz );
int __vcuf OVCUAPI cudaVF_sinc( fVector Y, fVector X, ui siz );
int __vcuf OVCUAPI cudaVF_sincos( fVector YSin, fVector YCos, fVector X, ui siz );
int __vcuf OVCUAPI cudaVF_sincos2( fVector YSin, fVector YCos, fVector X, ui siz );
int __vcuf OVCUAPI cudaVF_sinh( fVector Y, fVector X, ui siz );
int __vcuf OVCUAPI cudaVF_tan( fVector Y, fVector X, ui siz );
int __vcuf OVCUAPI cudaVF_tan2( fVector Y, fVector X, ui siz );
int __vcuf OVCUAPI cudaVF_tanh( fVector Y, fVector X, ui siz );
#define cudaVF_exp2   cudaVF_pow2
#define cudaVF_exp10  cudaVF_pow10

int __vcuf OVCUAPI cudaVFx_acos( fVector Y, fVector X, ui siz, float A, float B, float C );
int __vcuf OVCUAPI cudaVFx_asin( fVector Y, fVector X, ui siz, float A, float B, float C );
int __vcuf OVCUAPI cudaVFx_atan( fVector Y, fVector X, ui siz, float A, float B, float C );
int __vcuf OVCUAPI cudaVFx_cos( fVector Y, fVector X, ui siz, float A, float B, float C );
int __vcuf OVCUAPI cudaVFx_cos2( fVector Y, fVector X, ui siz, float A, float B, float C );
int __vcuf OVCUAPI cudaVFx_cosh( fVector Y, fVector X, ui siz, float A, float B, float C );
int __vcuf OVCUAPI cudaVFx_cosec( fVector Y, fVector X, ui siz, float A, float B, float C );
int __vcuf OVCUAPI cudaVFx_cosec2( fVector Y, fVector X, ui siz, float A, float B, float C );
int __vcuf OVCUAPI cudaVFx_cosech( fVector Y, fVector X, ui siz, float A, float B, float C );
int __vcuf OVCUAPI cudaVFx_cot( fVector Y, fVector X, ui siz, float A, float B, float C );
int __vcuf OVCUAPI cudaVFx_cot2( fVector Y, fVector X, ui siz, float A, float B, float C );
int __vcuf OVCUAPI cudaVFx_coth( fVector Y, fVector X, ui siz, float A, float B, float C );
int __vcuf OVCUAPI cudaVFx_erf( fVector Y, fVector X, ui siz, float A, float B, float C );
int __vcuf OVCUAPI cudaVFx_erfc( fVector Y, fVector X, ui siz, float A, float B, float C );
int __vcuf OVCUAPI cudaVFx_exp( fVector Y, fVector X, ui siz, float A, float B, float C );
int __vcuf OVCUAPI cudaVFx_expc( fVector Y, fVector X, ui siz, float A, float B, float C );
int __vcuf OVCUAPI cudaVFx_expmx2( fVector Y, fVector X, ui siz, float A, float B, float C );
int __vcuf OVCUAPI cudaVFx_Kepler( fVector Y, fVector X, ui siz, float T, float e, float A, float B );
int __vcuf OVCUAPI cudaVFx_Langevin( fVector Y, fVector X, ui siz, float A, float B, float C );
int __vcuf OVCUAPI cudaVFx_log( fVector Y, fVector X, ui siz, float A, float B, float C );
int __vcuf OVCUAPI cudaVFx_log2( fVector Y, fVector X, ui siz, float A, float B, float C );
int __vcuf OVCUAPI cudaVFx_log10( fVector Y, fVector X, ui siz, float A, float B, float C );
int __vcuf OVCUAPI cudaVFx_pow( fVector Y, fVector X, ui siz, float Expo, float A, float B, float C );
int __vcuf OVCUAPI cudaVFx_pow2( fVector Y, fVector X, ui siz, float A, float B, float C );
int __vcuf OVCUAPI cudaVFx_pow10( fVector Y, fVector X, ui siz, float A, float B, float C );
int __vcuf OVCUAPI cudaVFx_sec( fVector Y, fVector X, ui siz, float A, float B, float C );
int __vcuf OVCUAPI cudaVFx_sec2( fVector Y, fVector X, ui siz, float A, float B, float C );
int __vcuf OVCUAPI cudaVFx_sech( fVector Y, fVector X, ui siz, float A, float B, float C );
int __vcuf OVCUAPI cudaVFx_sech2( fVector Y, fVector X, ui siz, float A, float B, float C );
int __vcuf OVCUAPI cudaVFx_sin( fVector Y, fVector X, ui siz, float A, float B, float C );
int __vcuf OVCUAPI cudaVFx_sin2( fVector Y, fVector X, ui siz, float A, float B, float C );
int __vcuf OVCUAPI cudaVFx_sinc( fVector Y, fVector X, ui siz, float A, float B, float C );
int __vcuf OVCUAPI cudaVFx_sincos( fVector YSin, fVector YCos, fVector X, ui siz, float A, float B, float C );
int __vcuf OVCUAPI cudaVFx_sincos2( fVector YSin, fVector YCos, fVector X, ui siz, float A, float B, float C );
int __vcuf OVCUAPI cudaVFx_sinh( fVector Y, fVector X, ui siz, float A, float B, float C );
int __vcuf OVCUAPI cudaVFx_sqrt( fVector Y, fVector X, ui siz, float A, float B, float C );
int __vcuf OVCUAPI cudaVFx_tan( fVector Y, fVector X, ui siz, float A, float B, float C );
int __vcuf OVCUAPI cudaVFx_tan2( fVector Y, fVector X, ui siz, float A, float B, float C );
int __vcuf OVCUAPI cudaVFx_tanh( fVector Y, fVector X, ui siz, float A, float B, float C );
#define cudaVFx_exp2   cudaVFx_pow2
#define cudaVFx_exp10  cudaVFx_pow10

float __vcuf OVCUAPI cudaVF_scalprod( fVector X, fVector Y, ui siz );
float __vcuf OVCUAPI cudaVF_Euclid( fVector X, ui size );
float __vcuf OVCUAPI cudaVF_max( fVector X, ui size );
float __vcuf OVCUAPI cudaVF_min( fVector X, ui size );
float __vcuf OVCUAPI cudaVF_absmax( fVector X, ui size );
float __vcuf OVCUAPI cudaVF_absmin( fVector X, ui size );
int   __vcuf OVCUAPI cudaVF_maxexp( fVector X, ui size );
int   __vcuf OVCUAPI cudaVF_minexp( fVector X, ui size );
float __vcuf OVCUAPI cudaVF_maxind( ui *Ind, fVector X, ui size );
float __vcuf OVCUAPI cudaVF_minind( ui *Ind, fVector X, ui size );
float __vcuf OVCUAPI cudaVF_absmaxind( ui *Ind, fVector X, ui size );
float __vcuf OVCUAPI cudaVF_absminind( ui *Ind, fVector X, ui size );
float __vcuf OVCUAPI cudaVF_sum( fVector X, ui size );
float __vcuf OVCUAPI cudaVF_prod( fVector X, ui size );
// int   __vcuf OVCUAPI cudaVF_iselementC( fVector Tab, ui size, float C );
// ui    __vcuf OVCUAPI cudaVF_iselementV( fVector Y, fVector X, ui sizex, fVector Tab, ui sizetab );
float __vcuf OVCUAPI cudaVF_centerOfGravityInd( fVector X, ui size );
float __vcuf OVCUAPI cudaVF_centerOfGravityV( fVector X, fVector Y, ui size );
float __vcuf OVCUAPI cudaVF_mean( fVector X, ui size );
float __vcuf OVCUAPI cudaVF_meanwW( fVector X, fVector Wt, ui size );
float __vcuf OVCUAPI cudaVF_sumabs( fVector X, ui size );
float __vcuf OVCUAPI cudaVF_meanabs( fVector X, ui size );
// float __vcuf OVCUAPI cudaVF_selected_mean( ui *nsel, fVector X, ui size, float XMin, float XMax );
// float __vcuf OVCUAPI cudaVF_median( fVector X, ui size );
float __vcuf OVCUAPI cudaVF_sumdevC( fVector X, ui size, float C );
float __vcuf OVCUAPI cudaVF_sumdevV( fVector X, fVector Y, ui size );
float __vcuf OVCUAPI cudaVF_avdevC( fVector X, ui size, float C );
float __vcuf OVCUAPI cudaVF_avdevV( fVector X, fVector Y, ui size );
float __vcuf OVCUAPI cudaVF_ssq( fVector X, ui size );  /* sum-of-squares */
float __vcuf OVCUAPI cudaVF_rms( fVector X, ui size );  /* root of the mean square */
float __vcuf OVCUAPI cudaVF_ssqdevC( fVector X, ui size, float C );
float __vcuf OVCUAPI cudaVF_ssqdevV( fVector X, fVector Y, ui size );
float __vcuf OVCUAPI cudaVF_meanvar(  float  *Var, fVector X, ui size );
float __vcuf OVCUAPI cudaVF_meanvarwW(  float  *Var, fVector X, fVector Wt, ui size );
#define cudaVF_varianceC  cudaVF_ssqdevC
#define cudaVF_varianceV  cudaVF_ssqdevV
float __vcuf OVCUAPI cudaVF_varianceV( fVector X, fVector Y, ui size );
float __vcuf OVCUAPI cudaVF_varianceCwW( fVector X, fVector Wt, ui size, float C );
float __vcuf OVCUAPI cudaVF_varianceVwW( fVector X, fVector Y, fVector Wt, ui size );
float __vcuf OVCUAPI cudaVF_chi2( fVector X, fVector Y, fVector InvVar, ui size );
float __vcuf OVCUAPI cudaVF_chiabs( fVector X, fVector Y, fVector Wt, ui size );
float __vcuf OVCUAPI cudaVF_corrcoeff( fVector X, fVector Y, ui size, float Xmean, float Ymean );
// ui    __vcuf OVCUAPI cudaVF_distribution( uiVector Abund, fVector Limits, ui nbins, fVector X, ui sizex, int mode );
void  __vcuf OVCUAPI cudaVF_linregress( fVector Param, fVector X, fVector Y, ui size );
void  __vcuf OVCUAPI cudaVF_linregresswW( fVector Param, fVector X, fVector Y, fVector InvVar, ui size );

void __vcuf OVCUAPI cudaVCF_equ0( cfVector X, ui siz );
void __vcuf OVCUAPI cudaVCF_equ1( cfVector X, ui siz );
void __vcuf OVCUAPI cudaVCF_equC( cfVector X, ui siz, fComplex C );
void __vcuf OVCUAPI cudaVCF_equV( cfVector Y, cfVector X, ui siz );

int __vcuf OVCUAPI cudaVCF_inv( cfVector Y, cfVector X, ui siz );
int __vcuf OVCUAPI cudaVCF_square( cfVector Y, cfVector X, ui siz );
int __vcuf OVCUAPI cudaVCF_cubic( cfVector Y, cfVector X, ui siz );
int __vcuf OVCUAPI cudaVCF_quartic( cfVector Y, cfVector X, ui siz );
int __vcuf OVCUAPI cudaVCFu_square( cfVector Y, cfVector X, ui siz );
int __vcuf OVCUAPI cudaVCFu_cubic( cfVector Y, cfVector X, ui siz );
int __vcuf OVCUAPI cudaVCFu_quartic( cfVector Y, cfVector X, ui siz );

int __vcuf OVCUAPI cudaVCF_acos( cfVector Y, cfVector X, ui siz );
int __vcuf OVCUAPI cudaVCF_asin( cfVector Y, cfVector X, ui siz );
int __vcuf OVCUAPI cudaVCF_atan( cfVector Y, cfVector X, ui siz );
int __vcuf OVCUAPI cudaVCF_cos( cfVector Y, cfVector X, ui siz );
int __vcuf OVCUAPI cudaVCF_cosh( cfVector Y, cfVector X, ui siz );
int __vcuf OVCUAPI cudaVCF_exp( cfVector Y, cfVector X, ui siz );
int __vcuf OVCUAPI cudaVCF_expArbBase( cfVector Y, cfVector X, ui siz, fComplex Base );
int __vcuf OVCUAPI cudaVCF_ipow( cfVector Y, cfVector X, ui siz, int Expo );
int __vcuf OVCUAPI cudaVCFu_ipow( cfVector Y, cfVector X, ui siz, int Expo );
int __vcuf OVCUAPI cudaVCF_log( cfVector Y, cfVector X, ui siz );
int __vcuf OVCUAPI cudaVCF_log2( cfVector Y, cfVector X, ui siz );
int __vcuf OVCUAPI cudaVCF_log10( cfVector Y, cfVector X, ui siz );
int __vcuf OVCUAPI cudaVCF_pow( cfVector Y, cfVector X, ui siz, fComplex Expo );
int __vcuf OVCUAPI cudaVCF_powReExpo( cfVector Y, cfVector X, ui siz, float Expo );
int __vcuf OVCUAPI cudaVCF_sin( cfVector Y, cfVector X, ui siz );
int __vcuf OVCUAPI cudaVCF_sinh( cfVector Y, cfVector X, ui siz );
int __vcuf OVCUAPI cudaVCF_sqrt( cfVector Y, cfVector X, ui siz );
int __vcuf OVCUAPI cudaVCF_tan( cfVector Y, cfVector X, ui siz );
int __vcuf OVCUAPI cudaVCF_tanh( cfVector Y, cfVector X, ui siz );

int __vcuf OVCUAPI cudaVCFx_inv( cfVector Y, cfVector X, ui siz, fComplex A, fComplex B );
int __vcuf OVCUAPI cudaVCFx_square( cfVector Y, cfVector X, ui siz, fComplex A, fComplex B );
int __vcuf OVCUAPI cudaVCFx_cubic( cfVector Y, cfVector X, ui siz, fComplex A, fComplex B );
int __vcuf OVCUAPI cudaVCFx_quartic( cfVector Y, cfVector X, ui siz, fComplex A, fComplex B );
int __vcuf OVCUAPI cudaVCFux_square( cfVector Y, cfVector X, ui siz, fComplex A, fComplex B );
int __vcuf OVCUAPI cudaVCFux_cubic( cfVector Y, cfVector X, ui siz, fComplex A, fComplex B );
int __vcuf OVCUAPI cudaVCFux_quartic( cfVector Y, cfVector X, ui siz, fComplex A, fComplex B );

int __vcuf OVCUAPI cudaVCFx_acos( cfVector Y, cfVector X, ui siz, fComplex A, fComplex B, fComplex C );
int __vcuf OVCUAPI cudaVCFx_asin( cfVector Y, cfVector X, ui siz, fComplex A, fComplex B, fComplex C );
int __vcuf OVCUAPI cudaVCFx_atan( cfVector Y, cfVector X, ui siz, fComplex A, fComplex B, fComplex C );
int __vcuf OVCUAPI cudaVCFx_cos( cfVector Y, cfVector X, ui siz, fComplex A, fComplex B, fComplex C );
int __vcuf OVCUAPI cudaVCFx_cosh( cfVector Y, cfVector X, ui siz, fComplex A, fComplex B, fComplex C );
int __vcuf OVCUAPI cudaVCFx_exp( cfVector Y, cfVector X, ui siz, fComplex A, fComplex B, fComplex C );
int __vcuf OVCUAPI cudaVCFx_expArbBase( cfVector Y, cfVector X, ui siz, fComplex Base, fComplex A, fComplex B, fComplex C );
int __vcuf OVCUAPI cudaVCFx_ipow( cfVector Y, cfVector X, ui siz, int Expo, fComplex A, fComplex B, fComplex C );
int __vcuf OVCUAPI cudaVCFux_ipow( cfVector Y, cfVector X, ui siz, int Expo, fComplex A, fComplex B, fComplex C );
int __vcuf OVCUAPI cudaVCFx_log( cfVector Y, cfVector X, ui siz, fComplex A, fComplex B, fComplex C );
int __vcuf OVCUAPI cudaVCFx_log2( cfVector Y, cfVector X, ui siz, fComplex A, fComplex B, fComplex C );
int __vcuf OVCUAPI cudaVCFx_log10( cfVector Y, cfVector X, ui siz, fComplex A, fComplex B, fComplex C );
int __vcuf OVCUAPI cudaVCFx_pow( cfVector Y, cfVector X, ui siz, fComplex Expo, fComplex A, fComplex B, fComplex C );
int __vcuf OVCUAPI cudaVCFx_powReExpo( cfVector Y, cfVector X, ui siz, float Expo, fComplex A, fComplex B, fComplex C );
int __vcuf OVCUAPI cudaVCFx_sin( cfVector Y, cfVector X, ui siz, fComplex A, fComplex B, fComplex C );
int __vcuf OVCUAPI cudaVCFx_sinh( cfVector Y, cfVector X, ui siz, fComplex A, fComplex B, fComplex C );
int __vcuf OVCUAPI cudaVCFx_sqrt( cfVector Y, cfVector X, ui siz, fComplex A, fComplex B, fComplex C );
int __vcuf OVCUAPI cudaVCFx_tan( cfVector Y, cfVector X, ui siz, fComplex A, fComplex B, fComplex C );
int __vcuf OVCUAPI cudaVCFx_tanh( cfVector Y, cfVector X, ui siz, fComplex A, fComplex B, fComplex C );

void  __vcuf OVCUAPI cudaVCF_FFT( cfVector Y, cfVector X, ui size, int dir );
void  __vcuf OVCUAPI cudaVF_FFT( fVector Y, fVector X, ui size, int dir );
void  __vcuf OVCUAPI cudaVF_FFTtoC( cfVector Y, fVector X, ui size );
void  __vcuf OVCUAPI cudaVF_filter( fVector Y, fVector X, fVector Flt, ui size );
void  __vcuf OVCUAPI cudaVF_autocorr( fVector Y, fVector X, ui size );
void  __vcuf OVCUAPI cudaVF_xcorr( fVector Z, fVector X, fVector Y, ui size );
float __vcuf OVCUAPI cudaVF_spectrum( fVector Spc, ui specsiz, fVector X, ui xsiz, fVector Win );
                           /* xsiz >= n*specsiz,  Winsiz = 2*specsiz ! */
void  __vcuf OVCUAPI cudaVF_convolve( fVector Y, fVector Flt, fVector X, fVector Rsp, ui size );
void  __vcuf OVCUAPI cudaVF_deconvolve( fVector Y, fVector Flt, fVector X, fVector Rsp, ui size );

#define cudaMF_Row_scalprodV( MA, X, htA, lenA, iRowA )  cudaVF_scalprod( MA[iRowA], X, lenA )
#define cudaMFRow_scalprodV( MA0, X, htA, lenA, iRowA )  cudaVF_scalprod( MA0+((ui)(iRowA))*(lenA), X, lenA )
#define cudaMF_Row_scalprodMRow( MA, MB, htA, lenA, iRowA, htB, lenB, iRowB )   cudaVF_scalprod( MA[iRowA], MB[iRowB], lenA )
#define cudaMFRow_scalprodMRow( MA0, MB0, htA, lenA, iRowA, htB, lenB, iRowB )  cudaVF_scalprod( MA0+((ui)(lenA))*(iRowA), MB0+((ui)(lenB))*(iRowB), lenA )
        /*  lenB >= lenA;  scalprod is taken over lenA elements */
#define cudaMF_Row_scalprodMCol( MA, MB, htA, lenA, iRowA, htB, lenB, iColB )  cudaMFCol_scalprodV( MB[0], MA[iRowA], lenA, lenB, iColB )
#define cudaMFRow_scalprodMCol( MA0, MB0, htA, lenA, iRowA, htB, lenB, iColB ) cudaMFCol_scalprodV( MB0, MA0+((ui)(iRowA))*(lenA), lenA, lenB, iColB )
        /* htB >= lenA; scalprod is taken over lenA elements */
#define cudaMF_Col_scalprodV( MA, X, htA, lenA, iColA )  cudaMFCol_scalprodV( MA[0], X, htA, lenA, iColA )
#define cudaMF_Col_scalprodMRow( MA, MB, htA, lenA, iColA, htB, lenB, iRowB )  cudaMFCol_scalprodV( MA[0], MB[iRowB], htA, lenA, iColA )
#define cudaMFCol_scalprodMRow( MA0, MB0, htA, lenA, iColA, htB, lenB, iRowB ) cudaMFCol_scalprodV( MA[0], MB0+((ui)(lenB))*(iRowB), htA, lenA, iColA )
#define cudaMF_Col_scalprodMCol( MA, MB, htA, lenA, iColA, htB, lenB, iColB )  cudaMFCol_scalprodMCol( MA[0], MB[0], htA, lenA, iColA, htB, lenB, iColB )
float __vcuf OVCUAPI cudaMFCol_scalprodV( fPMatrix MA, fVector X, ui htA, ui lenA, ui iColA );
float __vcuf OVCUAPI cudaMFCol_scalprodMCol( fPMatrix MA, fPMatrix MB, ui htA, ui lenA, ui iColA, 
	       						                             ui htB, ui lenB, ui iColB );
        /* htB >= htA; scalprod is taken over htA elements */

#define cudaMF_Rows_max( Y, MA, ht, len )     cudaMFRows_max( Y, MA[0], ht, len )
#define cudaMF_Cols_max( Y, MA, ht, len )     cudaMFCols_max( Y, MA[0], ht, len )
#define cudaMF_Rows_min( Y, MA, ht, len )     cudaMFRows_min( Y, MA[0], ht, len )
#define cudaMF_Cols_min( Y, MA, ht, len )     cudaMFCols_min( Y, MA[0], ht, len )
#define cudaMF_Rows_absmax( Y, MA, ht, len )  cudaMFRows_absmax( Y, MA[0], ht, len )
#define cudaMF_Cols_absmax( Y, MA, ht, len )  cudaMFCols_absmax( Y, MA[0], ht, len )
#define cudaMF_Rows_absmin( Y, MA, ht, len )  cudaMFRows_absmin( Y, MA[0], ht, len )
#define cudaMF_Cols_absmin( Y, MA, ht, len )  cudaMFCols_absmin( Y, MA[0], ht, len )
#define cudaMF_Rows_sum( Y, MA, ht, len )     cudaMFRows_sum( Y, MA[0], ht, len )
#define cudaMF_Cols_sum( Y, MA, ht, len )     cudaMFCols_sum( Y, MA[0], ht, len )
#define cudaMF_Rows_ssq( Y, MA, ht, len )     cudaMFRows_ssq( Y, MA[0], ht, len )
#define cudaMF_Cols_ssq( Y, MA, ht, len )     cudaMFCols_ssq( Y, MA[0], ht, len )
#define cudaMF_Rows_prod( Y, MA, ht, len )    cudaMFRows_prod( Y, MA[0], ht, len )
#define cudaMF_Cols_prod( Y, MA, ht, len )    cudaMFCols_prod( Y, MA[0], ht, len )
void  __vcuf OVCUAPI cudaMFRows_max( fVector Y, fPMatrix MA, ui ht, ui len );
void  __vcuf OVCUAPI cudaMFCols_max( fVector Y, fPMatrix MA, ui ht, ui len );
void  __vcuf OVCUAPI cudaMFRows_min( fVector Y, fPMatrix MA, ui ht, ui len );
void  __vcuf OVCUAPI cudaMFCols_min( fVector Y, fPMatrix MA, ui ht, ui len );
void  __vcuf OVCUAPI cudaMFRows_absmax( fVector Y, fPMatrix MA, ui ht, ui len );
void  __vcuf OVCUAPI cudaMFCols_absmax( fVector Y, fPMatrix MA, ui ht, ui len );
void  __vcuf OVCUAPI cudaMFRows_absmin( fVector Y, fPMatrix MA, ui ht, ui len );
void  __vcuf OVCUAPI cudaMFCols_absmin( fVector Y, fPMatrix MA, ui ht, ui len );
void  __vcuf OVCUAPI cudaMFRows_sum( fVector Y, fPMatrix MA, ui ht, ui len );
void  __vcuf OVCUAPI cudaMFCols_sum( fVector Y, fPMatrix MA, ui ht, ui len );
void  __vcuf OVCUAPI cudaMFRows_ssq( fVector Y, fPMatrix MA, ui ht, ui len );
void  __vcuf OVCUAPI cudaMFCols_ssq( fVector Y, fPMatrix MA, ui ht, ui len );
void  __vcuf OVCUAPI cudaMFRows_prod(fVector Y, fPMatrix MA, ui ht, ui len );
void  __vcuf OVCUAPI cudaMFCols_prod(fVector Y, fPMatrix MA, ui ht, ui len );
void  __vcuf OVCUAPI cudaMFRows_exchange( fPMatrix d_X, ui ht, ui len, ui i1, ui i2 );


#define cudaMF_mulV( Y, MA, X, htA, lenA )  cudaMFmulV( Y, MA[0], X, htA, lenA )
    /*  Y = MA * X.  sizX=lenA, sizY=htA.  both X and Y are column-vectors    */
#define cudaMF_TmulV( Y, MA, X, htA, lenA ) cudaMFTmulV( Y, MA[0], X, htA, lenA )
    /*  Y = MAT * X.  sizX=htA, sizY=lenA.  both X and Y are column-vectors    */
#define VFc_mulM( Y, X, MA, htA, lenA )  VFcmulM( Y, X, MA[0], htA, lenA )
    /*  Y = X * MA.  sizX=htA, sizY=lenA. both X and Y are row-vectors.
                             Mind the prefix: VF_ (not MF_)    */
#define VFc_mulMT( Y, X, MA, htA, lenA ) VFcmulMT( Y, X, MA[0], htA, lenA )
    /*  Y = X * MAT.  sizX=lenA, sizY=htA. both X and Y are row-vectors.   */
#define cudaMF_mulM( MC, MA, MB, htA, lenA, lenB ) cudaMFmulM( MC[0], MA[0], MB[0], htA, lenA, lenB )
    /*  MC = MA * MB.  htB=lenA, htC=htA, lenC=lenB */
#define cudaMF_mulMT( MC, MA, MB, htA, lenA, htB ) cudaMFmulMT( MC[0], MA[0], MB[0], htA, lenA, htB )
    /*  MC = MA * MBT.  lenB=lenA, htC=htA, lenC=htB */
#define cudaMF_TmulM( MC, MA, MB, htA, lenA, lenB ) cudaMFTmulM( MC[0], MA[0], MB[0], htA, lenA, lenB )
    /*  MC = MAT * MB.  htB=htA, htC=lenA, lenC=lenB */
#define cudaMF_TmulMT( MC, MA, MB, htA, lenA, htB ) cudaMFTmulMT( MC[0], MA[0], MB[0], htA, lenA, htB )

void  __vcuf OVCUAPI cudaMFmulV( fVector Y, fPMatrix MA, fVector X, ui htA, ui lenA );
void  __vcuf OVCUAPI cudaMFTmulV( fVector Y, fPMatrix MA, fVector X, ui htA, ui lenA );
void  __vcuf OVCUAPI cudaVFmulM( fVector Y, fVector X, fPMatrix MA, ui htA, ui lenA );
void  __vcuf OVCUAPI cudaVFmulMT( fVector Y, fVector X, fPMatrix MA, ui htA, ui lenA );
void  __vcuf OVCUAPI cudaMFmulM( fPMatrix MC, fPMatrix MA, fPMatrix MB, ui htA, ui lenA, ui lenB );
void  __vcuf OVCUAPI cudaMFmulMT( fPMatrix MC, fPMatrix MA, fPMatrix MB, ui htA, ui lenA, ui htB );
void  __vcuf OVCUAPI cudaMFTmulM( fPMatrix MC, fPMatrix MA, fPMatrix MB, ui htA, ui lenA, ui lenB );
void  __vcuf OVCUAPI cudaMFTmulMT( fPMatrix MC, fPMatrix MA, fPMatrix MB, ui htA, ui lenA, ui htB );

#define cudaMCF_mulV( Y, MA, X, htA, lenA )  cudaMCFmulV( Y, MA[0], X, htA, lenA )
    /*  Y = MA * X.  sizX=lenA, sizY=htA.  both X and Y are column-vectors    */
#define cudaMCF_TmulV( Y, MA, X, htA, lenA ) cudaMCFTmulV( Y, MA[0], X, htA, lenA )
    /*  Y = MAT * X.  sizX=htA, sizY=lenA.  both X and Y are column-vectors    */
#define VCFc_mulM( Y, X, MA, htA, lenA )  VCFcmulM( Y, X, MA[0], htA, lenA )
    /*  Y = X * MA.  sizX=htA, sizY=lenA. both X and Y are row-vectors.
                             Mind the prefix: VCF_ (not MCF_)    */
#define VCFc_mulMT( Y, X, MA, htA, lenA ) VCFcmulMT( Y, X, MA[0], htA, lenA )
    /*  Y = X * MAT.  sizX=lenA, sizY=htA. both X and Y are row-vectors.   */
#define cudaMCF_mulM( MC, MA, MB, htA, lenA, lenB ) cudaMCFmulM( MC[0], MA[0], MB[0], htA, lenA, lenB )
    /*  MC = MA * MB.  htB=lenA, htC=htA, lenC=lenB */
#define cudaMCF_mulMT( MC, MA, MB, htA, lenA, htB ) cudaMCFmulMT( MC[0], MA[0], MB[0], htA, lenA, htB )
    /*  MC = MA * MBT.  lenB=lenA, htC=htA, lenC=htB */
#define cudaMCF_TmulM( MC, MA, MB, htA, lenA, lenB ) cudaMCFTmulM( MC[0], MA[0], MB[0], htA, lenA, lenB )
    /*  MC = MAT * MB.  htB=htA, htC=lenA, lenC=lenB */
#define cudaMCF_TmulMT( MC, MA, MB, htA, lenA, htB ) cudaMCFTmulMT( MC[0], MA[0], MB[0], htA, lenA, htB )

void  __vcuf OVCUAPI cudaMCFmulV( cfVector Y, cfPMatrix MA, cfVector X, ui htA, ui lenA );
void  __vcuf OVCUAPI cudaMCFTmulV( cfVector Y, cfPMatrix MA, cfVector X, ui htA, ui lenA );
void  __vcuf OVCUAPI cudaVCFmulM( cfVector Y, cfVector X, cfPMatrix MA, ui htA, ui lenA );
void  __vcuf OVCUAPI cudaVCFmulMT( cfVector Y, cfVector X, cfPMatrix MA, ui htA, ui lenA );
void  __vcuf OVCUAPI cudaMCFmulM( cfPMatrix MC, cfPMatrix MA, cfPMatrix MB, ui htA, ui lenA, ui lenB );
void  __vcuf OVCUAPI cudaMCFmulMT( cfPMatrix MC, cfPMatrix MA, cfPMatrix MB, ui htA, ui lenA, ui htB );
void  __vcuf OVCUAPI cudaMCFTmulM( cfPMatrix MC, cfPMatrix MA, cfPMatrix MB, ui htA, ui lenA, ui lenB );
void  __vcuf OVCUAPI cudaMCFTmulMT( cfPMatrix MC, cfPMatrix MA, cfPMatrix MB, ui htA, ui lenA, ui htB );


#define cudaMF_transpose( MTr, MA, htTr, lenTr ) cudaMFtranspose( MTr[0], MA[0], htTr, lenTr )
void  __vcuf OVCUAPI cudaMFtranspose( fPMatrix MTr, fPMatrix MA, ui htTr, ui lenTr );
#define cudaMCF_transpose( MTr, MA, htTr, lenTr ) cudaMCFtranspose( MTr[0], MA[0], htTr, lenTr )
void __vcuf OVCUAPI cudaMCFtranspose( cfPMatrix MTr, cfPMatrix MA, ui htTr, ui lenTr );

}   /* end of extern "C" */

