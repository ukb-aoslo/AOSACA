/*  MFstd.h

  matrix management functions:
  manipulations on matrices of data type "float"
  (single-precision real numbers)

  Copyright (c) 1996-2017 by OptiCode - Dr. Martin Sander Software Dev.
  All Rights Reserved.
*/

#if !defined( __MFSTD_H )
#define __MFSTD_H
#if !defined( __MATLIB_H )
#include <MatLib.h>
#endif
#if !defined( __VFSTD_H )
#include <VFstd.h>
#endif
#if !defined( __VFMATH_H )
#include <VFmath.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif

/*************   Dynamic Generation of Matrices   ************************/

fMatrix __vf  MF_matrix(  ui ht, ui len );
fMatrix __vf  MF_matrix0( ui ht, ui len );
#if defined (_MSC_VER) && defined (_DEBUG)
    fMatrix __vf  MF_matrix_dbg(  ui ht, ui len );
    fMatrix __vf  MF_matrix0_dbg( ui ht, ui len );
    #if defined (_INC_CRTDBG) && defined (_CRTDBG_MAP_ALLOC) 
	    /* Automatic mapping for memory-leak detection by CRT debugging switched on? */ 
        #define MF_matrix  MF_matrix_dbg
        #define MF_matrix0 MF_matrix0_dbg
    #endif
#else
    #define MF_matrix_dbg  MF_matrix
    #define MF_matrix0_dbg MF_matrix0
#endif
    /*  notice that, in the memory model HUGE,
        neither len nor ht may exceed 8191            */

/***************************************************************************
 *  The following definitions ensure compatibility between dynamically     *
 *  and statically allocated matrices. The definitions are somewhat        *
 *  cumbersome, but the result for you is that you need not care about     *
 *  the differences between the two types.                                 *
 *  (Internally, the address of the first element of any matrix is needed; *
 *  the expression "(MA)[0]" is evaluated in a different way for both types, *
 *  but yields in either case the correct address to be passed to the      *
 *  function you wish to call.)                                            *
 *  Only in the rare case that you need to pass the address of one of      *
 *  these functions as an argument to another function, you have to use    *
 *  the actual run-time functions defined further below. Be careful with   *
 *  this: future development of compilers may allow us to avoid this un-   *
 *  handy scheme of macros. So future versions of MatrixLib may no longer  *
 *  use these run-time names.                                              *
 ***************************************************************************/


/***  Addressing single elements of dynamically allocated matrices: ******
     These functions are for compatibility with Pascal/Delphi
	 and for range-checking in the debug libraries                         */

#define MF_getElement( y, MA, ht, len, m, n ) MFgetElement( y, (MA)[0], ht, len, m, n )
#define MF_setElement( MA, ht, len, m, n, C ) MFsetElement( (MA)[0], ht, len, m, n, C )
#define MF_Pelement( MA, ht, len, m, n ) MFPelement( (MA)[0], ht, len, m, n )
                     /* returns a pointer to MA[m][n]. */
#define MF_element( MA, ht, len, m, n ) (*MFPelement( (MA)[0], ht, len, m, n ))
                     /* dereferenced pointer */

 /****************  Initialization  ***************************************

    To initialize all elements of a matrix with the same value,
    or to perform arithmetic operations on all elements simultaneously,
    refer to the functions of VectorLib, declared in <VFstd.h>, <VFmath.h>.
    In order to use the VectorLib functions, utilize the feature that
    the whole matrix occupies one contiguous area in memory: pass the
    address of the first row to the desired vector function, the size
    of the "vector" being ht * len.
    For example, initialize all elements of the matrix MA with 1.0
    (this is *NOT* the identity matrix)  by calling
        VF_equ1( (MA)[0], ht * len );
*/

#define MF_equ0( MA, ht, len )            VF_equ0( (MA)[0], (ht)*(len) )
#define MF_equ1( MA, len )                MFequ1( (MA)[0], len ) /* identity matrix */
#define MF_equm1( MA, len )               MFequm1( (MA)[0], len ) /* neg. identity matrix */
#define MF_randomLC( MA, ht, len, seed, Min, Max, state ) \
                                          VF_randomLC( (MA)[0], (ht)*(len), seed, Min, Max, state )
#define MF_random( MA, ht, len, seed, Min, Max ) \
                                          VF_random( (MA)[0], (ht)*(len), seed, Min, Max )
#define MF_outerprod( MA, X, Y, ht, len ) MFouterprod( (MA)[0], X, Y, ht, len )
                       /* sizX=ht, sizY=len */
#define MF_Row_equ0( MA, ht, len, iRow )  MFRow_equ0( (MA)[0], ht, len, iRow )
#define MF_Col_equ0( MA, ht, len, iCol )  MFCol_equ0( (MA)[0], ht, len, iCol )
#define MF_Dia_equ0( MA, len )            MFDia_equ0( (MA)[0], len )
#define MF_Row_equC( MA, ht, len, iRow, C ) \
                                        MFRow_equC( (MA)[0], ht, len, iRow, C )
#define MF_Col_equC( MA, ht, len, iCol, C ) \
                                        MFCol_equC( (MA)[0], ht, len, iCol, C )
#define MF_Dia_equC( MA, len, C )       MFDia_equC( (MA)[0], len, C )

#define MF_Row_equV( MA, ht, len, iRow, X ) \
                                        MFRow_equV( (MA)[0], ht, len, iRow, X )
#define MF_Col_equV( MA, ht, len, iCol, X ) \
                                        MFCol_equV( (MA)[0], ht, len, iCol, X )
#define MF_Dia_equV( MA, len, X )       MFDia_equV( (MA)[0], len, X )

#define MF_Trd_equM( MA, MTrd, len )    MFTrd_equM( (MA)[0], (MTrd)[0], len )
#define MF_Trd_extract( MTrd, MA, len ) MFTrd_extract( (MTrd)[0], (MA)[0], len )

#define MF_equM( MB, MA, ht, len )  VF_equV( (MB)[0], (MA)[0], (ht)*(len) )
#define MF_neg( MB, MA, ht, len )   VF_neg( (MB)[0], (MA)[0], (ht)*(len) )

#define MF_UequL( MA, len ) MFUequL( (MA)[0], len )
#define MF_LequU( MA, len ) MFLequU( (MA)[0], len )
         /* copy lower-diagonal elements into upper-diagonal
           (or vice versa) by index-reflection, so as to
           get a symmetric matrix    */

            /* data-type conversions:  */
#define M_DtoF( MF, MD, ht, len ) V_DtoF( (MF)[0], (MD)[0], (ht)*(len) )
#define M_EtoF( MF, ME, ht, len ) V_EtoF( (MF)[0], (ME)[0], (ht)*(len) )
#define M_FtoD( MD, MF, ht, len ) V_FtoD( (MD)[0], (MF)[0], (ht)*(len) )
#define M_FtoE( ME, MF, ht, len ) V_FtoE( (ME)[0], (MF)[0], (ht)*(len) )

            /* suitable windows for MF_spectrum: */
#define MF_Hann( MA, ht, len )     MFHann( (MA)[0], ht, len )
#define MF_Hanning( MA, ht, len )  MFHann( (MA)[0], ht, len )  /* erronous name for Hann */
#define MF_Parzen( MA, ht, len )   MFParzen( (MA)[0], ht, len )
#define MF_Welch( MA, ht, len )    MFWelch( (MA)[0], ht, len )

/********  Extracting a submatrix and copying a submatrix back  *********/

#define MF_submatrix( MSub, subHt, subLen, \
                      MSrce, srceHt, srceLen, \
                      firstRowInCol, sampInCol, firstColInRow, sampInRow ) \
               MFsubmatrix(  (MSub)[0], subHt, subLen, \
                             (MSrce)[0], srceHt, srceLen, \
                             firstRowInCol, sampInCol, firstColInRow, sampInRow )

#define MF_submatrix_equM( MDest, destHt, destLen, \
                           firstRowInCol, sampInCol, firstColInRow, sampInRow, \
                           MSrce, srceHt, srceLen ) \
               MFsubmatrix_equM(  (MDest)[0], destHt, destLen, \
                             firstRowInCol, sampInCol, firstColInRow, sampInRow, \
                             (MSrce)[0], srceHt, srceLen )

#define MF_equMblock( MSub, subHt, subLen, \
                      MSrce, srceHt, srceLen, \
                      firstRowInCol, firstColInRow ) \
               MFequMblock(  (MSub)[0], subHt, subLen, \
                             (MSrce)[0], srceHt, srceLen, \
                             firstRowInCol, firstColInRow )

#define MF_block_equM( MDest, destHt, destLen, \
                       firstRowInCol, firstColInRow, \
                       MSrce, srceHt, srceLen ) \
               MFblock_equM( (MDest)[0], destHt, destLen, \
                             firstRowInCol, firstColInRow, \
                             (MSrce)[0], srceHt, srceLen )

#define MF_equMblockT( MSub, subHt, subLen, \
                      MSrce, srceHt, srceLen, \
                      firstRowInCol, firstColInRow ) \
               MFequMblockT(  (MSub)[0], subHt, subLen, \
                             (MSrce)[0], srceHt, srceLen, \
                             firstRowInCol, firstColInRow )

#define MF_block_equMT( MDest, destHt, destLen, \
                       firstRowInCol, firstColInRow, \
                       MSrce, srceHt, srceLen ) \
               MFblock_equMT( (MDest)[0], destHt, destLen, \
                             firstRowInCol, firstColInRow, \
                             (MSrce)[0], srceHt, srceLen )

/*****   Extracting a single row or a single column or the diagonal  ******
 *       and storing it into a vector                                     */

#define MF_Row_extract( Y, MA, ht, len, iRow ) \
                                     MFRow_extract( Y, (MA)[0], ht, len, iRow )
#define MF_Col_extract( Y, MA, ht, len, iCol ) \
                                     MFCol_extract( Y, (MA)[0], ht, len, iCol )
#define MF_Dia_extract( Y, MA, len ) MFDia_extract( Y, (MA)[0], len )


/**************  Deleting or inserting a row or a column   ***************/

#define MF_Row_delete( MB, MA, htA, lenA, iRow ) \
                           MFRow_delete( (MB)[0], (MA)[0], htA, lenA, iRow )
#define MF_Col_delete( MB, MA, htA, lenA, iCol ) \
                           MFCol_delete( (MB)[0], (MA)[0], htA, lenA, iCol )
#define MF_Row_insert( MB, MA, htB, lenB, iRow, X ) \
                           MFRow_insert( (MB)[0], (MA)[0], htB, lenB, iRow, X )
#define MF_Col_insert( MB, MA, htB, lenB, iCol, X ) \
                           MFCol_insert( (MB)[0], (MA)[0], htB, lenB, iCol, X )

/*****************    Basic arithmetic operations *********************
                      performed on one single row,
                      or one single column of any matrix,
                      or on the diagonal of a square matrix

    Note: In contrast to the analogous VectorLib functions, the operations
    are performed in-place, i.e. the input matrix itself is changed  */

#define MF_Row_neg( MA, ht, len, iRow ) MFRow_neg( (MA)[0], ht, len, iRow )
#define MF_Col_neg( MA, ht, len, iCol ) MFCol_neg( (MA)[0], ht, len, iCol )

#define MF_Row_addC( MA, ht, len, iRow, C ) \
                                     MFRow_addC( (MA)[0], ht, len, iRow, C )
#define MF_Col_addC( MA, ht, len, iCol, C ) \
                                     MFCol_addC( (MA)[0], ht, len, iCol, C )
#define MF_Dia_addC( MA, len, C )    MFDia_addC( (MA)[0], len, C )

#define MF_Row_addV( MA, ht, len, iRow, X ) \
                                     MFRow_addV( (MA)[0], ht, len, iRow, X )
#define MF_Col_addV( MA, ht, len, iCol, X ) \
                                     MFCol_addV( (MA)[0], ht, len, iCol, X )
#define MF_Dia_addV( MA, len, X )    MFDia_addV( (MA)[0], len, X )

#define MF_Row_subC( MA, ht, len, iRow, C ) \
                                     MFRow_subC( (MA)[0], ht, len, iRow, C )
#define MF_Col_subC( MA, ht, len, iCol, C ) \
                                     MFCol_subC( (MA)[0], ht, len, iCol, C )
#define MF_Dia_subC( MA, len, C )    MFDia_subC( (MA)[0], len, C )

#define MF_Row_subV( MA, ht, len, iRow, X ) \
                                     MFRow_subV( (MA)[0], ht, len, iRow, X )
#define MF_Col_subV( MA, ht, len, iCol, X ) \
                                     MFCol_subV( (MA)[0], ht, len, iCol, X )
#define MF_Dia_subV( MA, len, X )    MFDia_subV( (MA)[0], len, X )

#define MF_Row_subrC( MA, ht, len, iRow, C ) \
                                     MFRow_subrC( (MA)[0], ht, len, iRow, C )
#define MF_Col_subrC( MA, ht, len, iCol, C ) \
                                     MFCol_subrC( (MA)[0], ht, len, iCol, C )
#define MF_Dia_subrC( MA, len, C )   MFDia_subrC( (MA)[0], len, C )

#define MF_Row_subrV( MA, ht, len, iRow, X ) \
                                     MFRow_subrV( (MA)[0], ht, len, iRow, X )
#define MF_Col_subrV( MA, ht, len, iCol, X ) \
                                     MFCol_subrV( (MA)[0], ht, len, iCol, X )
#define MF_Dia_subrV( MA, len, X )   MFDia_subrV( (MA)[0], len, X )

#define MF_Row_mulC( MA, ht, len, iRow, C ) \
                                     MFRow_mulC( (MA)[0], ht, len, iRow, C )
#define MF_Col_mulC( MA, ht, len, iCol, C ) \
                                     MFCol_mulC( (MA)[0], ht, len, iCol, C )
#define MF_Dia_mulC( MA, len, C )    MFDia_mulC( (MA)[0], len, C )

#define MF_Row_mulV( MA, ht, len, iRow, X ) \
                                     MFRow_mulV( (MA)[0], ht, len, iRow, X )
#define MF_Col_mulV( MA, ht, len, iCol, X ) \
                                     MFCol_mulV( (MA)[0], ht, len, iCol, X )
#define MF_Dia_mulV( MA, len, X )    MFDia_mulV( (MA)[0], len, X )

#define MF_Row_divC( MA, ht, len, iRow, C ) \
                                     MFRow_divC( (MA)[0], ht, len, iRow, C )
#define MF_Col_divC( MA, ht, len, iCol, C ) \
                                     MFCol_divC( (MA)[0], ht, len, iCol, C )
#define MF_Dia_divC( MA, len, C )    MFDia_divC( (MA)[0], len, C )

#define MF_Row_divV( MA, ht, len, iRow, X ) \
                                      MFRow_divV( (MA)[0], ht, len, iRow, X )
#define MF_Col_divV( MA, ht, len, iCol, X ) \
                                      MFCol_divV( (MA)[0], ht, len, iCol, X )
#define MF_Dia_divV( MA, len, X )     MFDia_divV( (MA)[0], len, X )

#define MF_Row_divrC( MA, ht, len, iRow, C ) \
                                      MFRow_divrC( (MA)[0], ht, len, iRow, C )
#define MF_Col_divrC( MA, ht, len, iCol, C ) \
                                      MFCol_divrC( (MA)[0], ht, len, iCol, C )
#define MF_Dia_divrC( MA, len, C )    MFDia_divrC( (MA)[0], len, C )

#define MF_Row_divrV( MA, ht, len, iRow, X ) \
                                      MFRow_divrV( (MA)[0], ht, len, iRow, X )
#define MF_Col_divrV( MA, ht, len, iCol, X ) \
                                      MFCol_divrV( (MA)[0], ht, len, iCol, X )
#define MF_Dia_divrV( MA, len, X )    MFDia_divrV( (MA)[0], len, X )


/******  One-dimensional vector operations **********************
         performed along all rows or all columns simultaneously,
         or along the diagonal of a square matrix                */

#define MF_Rows_max( Y, MA, ht, len )     MFRows_max( Y, (MA)[0], ht, len )
#define MF_Cols_max( Y, MA, ht, len )     MFCols_max( Y, (MA)[0], ht, len )
#define MF_Dia_max(  MA, len )            MFDia_max(  (MA)[0], len )
#define MF_Rows_min( Y, MA, ht, len )     MFRows_min( Y, (MA)[0], ht, len )
#define MF_Cols_min( Y, MA, ht, len )     MFCols_min( Y, (MA)[0], ht, len )
#define MF_Dia_min(  MA, len )            MFDia_min(  (MA)[0], len )

#define MF_Rows_absmax( Y, MA, ht, len )  MFRows_absmax( Y, (MA)[0], ht, len )
#define MF_Cols_absmax( Y, MA, ht, len )  MFCols_absmax( Y, (MA)[0], ht, len )
#define MF_Dia_absmax(  MA, len )         MFDia_absmax(  (MA)[0], len )
#define MF_Rows_absmin( Y, MA, ht, len )  MFRows_absmin( Y, (MA)[0], ht, len )
#define MF_Cols_absmin( Y, MA, ht, len )  MFCols_absmin( Y, (MA)[0], ht, len )
#define MF_Dia_absmin(  MA, len )         MFDia_absmin(  (MA)[0], len )

#define MF_Rows_sum( Y, MA, ht, len )     MFRows_sum( Y, (MA)[0], ht, len )
#define MF_Cols_sum( Y, MA, ht, len )     MFCols_sum( Y, (MA)[0], ht, len )
#define MF_Dia_sum(  MA, len )            MFDia_sum(  (MA)[0], len )
#define MF_Rows_ssq( Y, MA, ht, len )     MFRows_ssq( Y, (MA)[0], ht, len )
#define MF_Cols_ssq( Y, MA, ht, len )     MFCols_ssq( Y, (MA)[0], ht, len )
#define MF_Dia_ssq(  MA, len )            MFDia_ssq(  (MA)[0], len )
#define MF_Rows_prod( Y, MA, ht, len )    MFRows_prod( Y, (MA)[0], ht, len )
#define MF_Cols_prod( Y, MA, ht, len )    MFCols_prod( Y, (MA)[0], ht, len )
#define MF_Dia_prod(  MA, len )           MFDia_prod( (MA)[0], len )

#define MF_Rows_runsum( MA, ht, len )     MFRows_runsum( (MA)[0], ht, len )
#define MF_Cols_runsum( MA, ht, len )     MFCols_runsum( (MA)[0], ht, len )
#define MF_Rows_runprod( MA, ht, len )    MFRows_runprod( (MA)[0], ht, len )
#define MF_Cols_runprod( MA, ht, len )    MFCols_runprod( (MA)[0], ht, len )

#define MF_Rows_rotate( MA, ht, len, pos) MFRows_rotate( (MA)[0], ht, len, pos )
#define MF_Cols_rotate( MA, ht, len, pos) MFCols_rotate( (MA)[0], ht, len, pos )
#define MF_Rows_rotate_buf( MA, ht, len, pos, MBuf) MFRows_rotate_buf( (MA)[0], ht, len, pos, (MBuf)[0] )
#define MF_Cols_rotate_buf( MA, ht, len, pos, MBuf) MFCols_rotate_buf( (MA)[0], ht, len, pos, (MBuf)[0] )
#define MF_Rows_reflect( MA, ht, len)     MFRows_reflect( (MA)[0], ht, len )
#define MF_Cols_reflect( MA, ht, len)     MFCols_reflect( (MA)[0], ht, len )
#define MF_Rows_rev( MA, ht, len)         MFRows_rev( (MA)[0], ht, len )
#define MF_Cols_rev( MA, ht, len)         MFCols_rev( (MA)[0], ht, len )

#define MF_Rows_distribution( MAbund, Limits, nBins, MX, htX, lenX, mode ) MFRows_distribution( (MAbund)[0], Limits, nBins, (MX)[0], htX, lenX, mode )
#define MF_Cols_distribution( MAbund, Limits, nBins, MX, htX, lenX, mode ) MFCols_distribution( (MAbund)[0], Limits, nBins, (MX)[0], htX, lenX, mode )

/********  Operations involving two rows or two colums of one matrix  *****/

#define MF_Rows_exchange( MA, ht, len, row1, row2 ) \
                             MFRows_exchange( (MA)[0], ht, len, row1, row2 )
#define MF_Cols_exchange( MA, ht, len, col1, col2 ) \
                             MFCols_exchange( (MA)[0], ht, len, col1, col2 )

#define MF_Rows_add( MA, ht, len, destRow, srceRow ) \
                             MFRows_add( (MA)[0], ht, len, destRow, srceRow )
#define MF_Cols_add( MA, ht, len, destCol, srceCol ) \
                             MFCols_add( (MA)[0], ht, len, destCol, srceCol )
                         /* dest[i] += source[i]  */

#define MF_Rows_sub( MA, ht, len, destRow, srceRow ) \
                             MFRows_sub( (MA)[0], ht, len, destRow, srceRow )
#define MF_Cols_sub( MA, ht, len, destCol, srceCol ) \
                             MFCols_sub( (MA)[0], ht, len, destCol, srceCol )
                         /* dest[i] -= source[i]  */

#define MF_Rows_Cadd( MA, ht, len, destRow, srceRow, C ) \
                          MFRows_Cadd( (MA)[0], ht, len, destRow, srceRow, C )
#define MF_Cols_Cadd( MA, ht, len, destCol, srceCol, C ) \
                          MFCols_Cadd( (MA)[0], ht, len, destCol, srceCol, C )
                         /* dest[i] += C * source[i]  */

#define MF_Rows_lincomb( MA, ht, len, destRow, destC, srceRow, srceC ) \
            MFRows_lincomb( (MA)[0], ht, len, destRow, destC, srceRow, srceC )
#define MF_Cols_lincomb( MA, ht, len, destCol, destC, srceCol, srceC ) \
            MFCols_lincomb( (MA)[0], ht, len, destCol, destC, srceCol, srceC )
  /*  linear combination: dest[i] = destC * dest[i] + sourceC * source[i] */

/*********************  Center of gravity *****************************/
#define MF_centerOfGravityInd( MA, ht, len ) \
            MFcenterOfGravityInd( (MA)[0], ht, len )
#define MF_centerOfGravityV( X, Y, MA, ht, len ) \
            MFcenterOfGravityV( X, Y, (MA)[0], ht, len )

/***************  Transposing and rotating a matrix **********************/

#define MF_transpose( MTr, MA, htTr, lenTr ) \
             MFtranspose( (MTr)[0], (MA)[0], htTr, lenTr )
       /*  dimensions htTr, lenTr are those of the transposed matrix,
           not of the original!                */
#define MF_rotate90( MRot, MA, htRot, lenRot ) \
             MFrotate90( (MRot)[0], (MA)[0], htRot, lenRot )
#define MF_rotate180( MRot, MA, htRot, lenRot ) \
             VF_rev( (MRot)[0], (MA)[0], (htRot)*(lenRot) )
#define MF_rotate270( MRot, MA, htRot, lenRot ) \
             MFrotate270( (MRot)[0], (MA)[0], htRot, lenRot )

/********************** Interpolation of Matrix elements **************/

#define MF_polyinterpol( MZ, X, Y, ht, len, XTab, YTab, MZTab, httab, lentab, degX, degY ) \
             MFpolyinterpol( (MZ)[0], X, Y, ht, len, XTab, YTab, (MZTab)[0], \
                             httab, lentab, degX, degY )
#define MF_ratinterpol( MZ, X, Y, ht, len, XTab, YTab, MZTab, httab, lentab, degX, degY ) \
             MFratinterpol( (MZ)[0], X, Y, ht, len, XTab, YTab, (MZTab)[0], \
                             httab, lentab, degX, degY )
#define MF_natCubSplineInterpol( MZ, X, Y, ht, len, XTab, YTab, MZTab, httab, lentab ) \
             MFnatCubSplineInterpol( (MZ)[0], X, Y, ht, len, XTab, YTab, (MZTab)[0], \
                             httab, lentab )

/************************ Matrix Arithmetics *************************/

#define MF_addM( MC, MA, MB, htA, lenA ) \
                 VF_addV( (MC)[0], (MA)[0], (MB)[0], (htA)*(lenA) )
#define MF_addMT( MC, MA, MB, htA, lenA ) \
                 MFaddMT( (MC)[0], (MA)[0], (MB)[0], htA, lenA )
#define MF_subM( MC, MA, MB, htA, lenA ) \
                 VF_subV( (MC)[0], (MA)[0], (MB)[0], (htA)*(lenA) )
#define MF_subMT( MC, MA, MB, htA, lenA ) \
                 MFsubMT( (MC)[0], (MA)[0], (MB)[0], htA, lenA )
#define MF_subrMT( MC, MA, MB, htA, lenA ) \
                 MFsubrMT( (MC)[0], (MA)[0], (MB)[0], htA, lenA )
#define MF_mulC( MB, MA, htA, lenA, C ) \
                 VF_mulC( (MB)[0], (MA)[0], (htA)*(lenA), C )
#define MF_divC( MB, MA, htA, lenA, C ) \
                 VF_divC( (MB)[0], (MA)[0], (htA)*(lenA), C )
#define MFs_addM( MC, MA, MB, htA, lenA, C ) \
                 VFs_addV( (MC)[0], (MA)[0], (MB)[0], (htA)*(lenA), C )
#define MFs_addMT( MC, MA, MB, htA, lenA, C ) \
                 MFsaddMT( (MC)[0], (MA)[0], (MB)[0], htA, lenA, C )
#define MFs_subM( MC, MA, MB, htA, lenA, C ) \
                 VFs_subV( (MC)[0], (MA)[0], (MB)[0], (htA)*(lenA), C )
#define MFs_subMT( MC, MA, MB, htA, lenA, C ) \
                 MFssubMT( (MC)[0], (MA)[0], (MB)[0], htA, lenA, C )
#define MFs_subrMT( MC, MA, MB, htA, lenA, C ) \
                 MFssubrMT( (MC)[0], (MA)[0], (MB)[0], htA, lenA, C )
#define MF_lincomb( MC, MA, MB, htA, lenA, CA, CB ) \
                 VF_lincomb( (MC)[0], (MA)[0], (MB)[0], (htA)*(lenA), CA, CB )

#define MF_mulV( Y, MA, X, htA, lenA )    MFmulV( Y, (MA)[0], X, htA, lenA )
                          /*  Y = MA * X.  sizX=lenA, sizY=htA
                              both X and Y are column-vectors    */
#define MF_TmulV( Y, MA, X, htA, lenA )   MFTmulV( Y, (MA)[0], X, htA, lenA )
                          /*  Y = MAT * X.  sizX=htA, sizY=lenA
                              both X and Y are column-vectors    */
#define VF_mulM( Y, X, MA, htA, lenA )    VFmulM( Y, X, (MA)[0], htA, lenA )
                         /*  Y = X * MA.  sizX=htA, sizY=lenA
                             both X and Y are row-vectors.
                             Mind the prefix: VF_ (not MF_)    */
#define VF_mulMT( Y, X, MA, htA, lenA )  VFmulMT( Y, X, (MA)[0], htA, lenA )
                         /*  Y = X * MAT.  sizX=lenA, sizY=htA
                             both X and Y are row-vectors.   */
#define MF_mulM( MC, MA, MB, htA, lenA, lenB ) \
                    MFmulM( (MC)[0], (MA)[0], (MB)[0], htA, lenA, lenB )
                         /*  MC = MA * MB.  htB=lenA, htC=htA, lenC=lenB */
#define MF_mulMT( MC, MA, MB, htA, lenA, htB ) \
                    MFmulMT( (MC)[0], (MA)[0], (MB)[0], htA, lenA, htB )
                         /*  MC = MA * MBT.  lenB=lenA, htC=htA, lenC=htB */
#define MF_TmulM( MC, MA, MB, htA, lenA, lenB ) \
                    MFTmulM( (MC)[0], (MA)[0], (MB)[0], htA, lenA, lenB )
                         /*  MC = MAT * MB.  htB=htA, htC=lenA, lenC=lenB */
#define MF_TmulMT( MC, MA, MB, htA, lenA, htB ) \
                    MFTmulMT( (MC)[0], (MA)[0], (MB)[0], htA, lenA, htB )
                         /*  MC = MAT * MBT.  lenB=htA, htC=lenA, lenC=htB */
#define MFdia_mulM(  MC, MADia, MB, htB, lenB )  MFdiamulM(  (MC)[0], MADia, (MB)[0], htB, lenB )
#define MFdia_mulMT( MC, MADia, MB, htB, lenB )  MFdiamulMT( (MC)[0], MADia, (MB)[0], htB, lenB )
#define MF_mulMdia(  MC, MA, MBDia, htA, lenA )  MFmulMdia(  (MC)[0], (MA)[0], MBDia, htA, lenA )
#define MF_TmulMdia( MC, MA, MBDia, htA, lenA )  MFTmulMdia( (MC)[0], (MA)[0], MBDia, htA, lenA )


/*************************  Linear Algebra    *****************************/

   /*  The standard treatment of linear systems is based
       on LUD (matrix decomposition into Upper-triangular
       and Lower-triangular components). The result of the
       decomposition step is used for further operations.  */

#define MF_LUdecompose( MLU, Ind, MA, len ) MFLUdecompose( (MLU)[0], Ind, (MA)[0], len )
            /* returns "permut" = +-1 which is needed for MF_LUdet.
               for singularities not cured by editing, permut is 0  */
int     __vf MF_LUDresult( void );
    /* returns 0, if MF_LUdecompose was successful;
       returns 1, if MA was (nearly) singular in MF_LUdecompose.   */
void    __vf MF_LUDsetEdit( float Thresh );
float   __vf MF_LUDgetEdit( void );
     /*  Editing threshold valid for MF_LUdecompose;
         may be used to cure singularities           */

#define MF_LUsolve( X, MLU, B, Ind, len )  MFLUsolve( X, (MLU)[0], B, Ind, len )
#define MF_LUinv( MInv, MLU, Ind, len )    MFLUinv( (MInv)[0], (MLU)[0], Ind, len )
#define MF_LUdet( MLU, len, permut )       MFLUdet( (MLU)[0], len, permut )
#define MF_LUimprove( X, B, MA, MLU, Ind, len ) \
                      MFLUimprove( X, B, (MA)[0], (MLU)[0], Ind, len )

	/****	Special treatment for symmetric, positive definite linear
			systems: Use Cholesky decomposition.
			"CholeskyL" functions use lower (left) triangular storage,
			"CholeskyR" functions use upper (right) triangular storage   ******/
#define MF_CholeskyLdecompose( ML, MA, len )		MFCholeskyLdecompose( (ML)[0], (MA)[0], len )
#define MF_CholeskyLsolve( X, ML, B, len )			MFCholeskyLsolve( X, (ML)[0], B, len )
#define MF_CholeskyLimprove( X, B, MA, ML, len )	MFCholeskyLimprove( X, B, (MA)[0], (ML)[0], len )
#define MF_CholeskyLinv( MInv, ML, len )			MFCholeskyLinv( (MInv)[0], (ML)[0], len )
#define MF_CholeskyRdecompose( MR, MA, len )		MFCholeskyRdecompose( (MR)[0], (MA)[0], len )
#define MF_CholeskyRsolve( X, MR, B, len )			MFCholeskyRsolve( X, (MR)[0], B, len )
#define MF_CholeskyRimprove( X, B, MA, MR, len )	MFCholeskyRimprove( X, B, (MA)[0], (MR)[0], len )
#define MF_CholeskyRinv( MInv, MR, len )			MFCholeskyRinv( (MInv)[0], (MR)[0], len )
#define MF_CholeskyDet( MLR, len )					MFCholeskyDet( (MLR)[0], len )
	/* takes either L or R input matrix to calculate determinant */
			
    /****  Special treatment of over- or under-determined
           linear systems, i.e. of matrices with len != ht
           and of singular matrices:
           SVD (Singular Value Decomposition)       ****/

#define MF_SVdecompose( MU, MV, W, MA, htA, lenA ) \
                    MFSVdecompose( (MU)[0], (MV)[0], W, (MA)[0], htA, lenA )
#define MF_SVsort( MUout, MVout, Wout, MUraw, MVraw, Wraw, htU, lenU ) \
					MFSVsort( (MUout)[0], (MVout)[0], Wout, (MUraw)[0], (MVraw)[0], Wraw, htU, lenU )
#define MF_SVsolve( X, MU, MV, W, B, htA, lenA ) \
                    MFSVsolve( X, (MU)[0], (MV)[0], W, B, htA, lenA )
            /*  lenU = lenA,  htA = sizeB, htU = max( lenA, htA ) as fed into
                MF_SVdecompose   */
void    __vf MF_SVDsetEdit( float Thresh );
float   __vf MF_SVDgetEdit( void );
    /* Override of the standard values for editing threshholds
       in MF_SVsolve. Calling MF_setEdit with Thresh=0.0 means
       that you do the necessary editing of W yourself
       before calling MD_SVsolve                           */

 /*****  "Easy-to-use" versions of the matrix functions
          using LUD, Cholesky, or SVD.
          They allocate their own working space and rely
          on your setting of the editing threshold. 
		  For optimal performance and in case of memory 
		  stress, you should better use the two-step methods 
		  declared above.            ***/
#define MF_solve( X, MA, B, len ) MFsolve( X, (MA)[0], B, len )
#define MF_inv( MInv, MA, len )  MFinv( (MInv)[0], (MA)[0], len )
#define MF_det(  MA, len )       MFdet( (MA)[0], len )
#define MF_solveBySVD( X, MA, B, ht, len ) \
                    MFsolveBySVD( X, (MA)[0], B, ht, len )
         /*  sizX = len,  sizB = ht  */
#define MF_safeSolve( X, MA, B, len ) MFsafeSolve( X, (MA)[0], B, len )
        /* MF_safeSolve tries first LUD. If that fails, SVD is done.
           X[i] will be 0.0 instead of INF for those i corresponding
           to singularities. If even SVD fails, all X[i] are set to 0.0.
           return value 0: success via LUD; 1: success via SVD; -1: failure */

		/* functions for symmetric matrices which may or may not be 
		   positive definite: */
#define MFsym_solve( X, MA, B, len )	MFsymsolve( X, (MA)[0], B, len )
#define MFsym_inv( MInv, MA, len )		MFsyminv( (MInv)[0], (MA)[0], len )
#define MFsym_det(  MA, len )			MFsymdet( (MA)[0], len )

      /*********  Eigenvalues and Eigenvectors  ********/
      /*** only the most frequent case of symmetric real matrices
           is covered here! *********/

#define MFsym_eigenvalues( EigV, EigM, MA, len, CalcEigenVec ) \
                    MFs_eigenvalues( EigV, (EigM)[0], (MA)[0], len, CalcEigenVec )
                        /*  Eigenvalues are returned in EigV.
                            CalcEigenVec = 0 means that only eigenvalues
                            are needed; CalcEigenVec != 0 means that
                            also eigenvectors are calculated. If so,
                            eigenvectors are returned as the columns of EigM.
                            Even if eigenvectors are not desired, EigM is
                            needed by the function as working-space. Then, on
                            output, it will contain just rubbish.
                            MA may be overwritten by EigM. */
#define MFsym_sqrt( MY, MX, len )   MFs_sqrt( (MY)[0], (MX)[0], len )
             /* square root of symmetric, positive definite matrix */

/***************** Two-Dimensional Fourier-Transform Methods ************/

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
           /* these are the same functions as used
              in the one-dimensional case */

#define MFp_FFT( MY, MX, ht, len, dir )     MFpFFT( (MY)[0], (MX)[0], ht, len, dir )
#define MFb_FFT( MY, MX, ht, len, dir, Buf) MFbFFT( (MY)[0], (MX)[0], ht, len, dir, Buf )
#define MFp_Rows_FFT( MY, MX, ht, len, dir) MFpRows_FFT( (MY)[0], (MX)[0], ht, len, dir )
#define MFp_Cols_FFT( MY, MX, ht, len, dir) MFpCols_FFT( (MY)[0], (MX)[0], ht, len, dir )
#define MFb_Rows_FFT( MY, MX, ht, len, dir, Buf) MFbRows_FFT( (MY)[0], (MX)[0], ht, len, dir, Buf )
#define MFb_Cols_FFT( MY, MX, ht, len, dir, Buf) MFbCols_FFT( (MY)[0], (MX)[0], ht, len, dir, Buf )
#define MFp_FFTtoC( MY, MX, ht, len )       MFpFFTtoC( (MY)[0], (MX)[0], ht, len )
#define MFb_FFTtoC( MY, MX, ht, len, Buf )  MFbFFTtoC( (MY)[0], (MX)[0], ht, len, Buf )
#define MFp_Rows_FFTtoC( MY, MX, ht, len )  MFpRows_FFTtoC( (MY)[0], (MX)[0], ht, len )
#define MFp_Cols_FFTtoC( MY, MX, ht, len )  MFpCols_FFTtoC( (MY)[0], (MX)[0], ht, len )
#define MFb_Rows_FFTtoC( MY, MX, ht, len, Buf )  MFbRows_FFTtoC( (MY)[0], (MX)[0], ht, len, Buf )
#define MFb_Cols_FFTtoC( MY, MX, ht, len, Buf )  MFbCols_FFTtoC( (MY)[0], (MX)[0], ht, len, Buf )
#define MFp_convolve( MY, MFlt, MX, MRsp, ht, len ) \
                  MFpconvolve( (MY)[0], (MFlt)[0], (MX)[0], (MRsp)[0], ht, len )
#define MFp_deconvolve( MY, MFlt, MX, MRsp, ht, len ) \
                  MFpdeconvolve( (MY)[0], (MFlt)[0], (MX)[0], (MRsp)[0], ht, len )
#define MFp_filter( MY, MX, MFlt, ht, len ) MFpfilter( (MY)[0], (MX)[0], (MFlt)[0], ht, len )
#define MFp_autocorr( MACorr, MX, ht, len ) MFpautocorr( (MACorr)[0], (MX)[0], ht, len )
#define MFp_xcorr( MXCorr, MX, MY, ht, len) MFpxcorr( (MXCorr)[0], (MX)[0], (MY)[0], ht, len )
#define MFp_spectrum( MSpec, htSpec, lenSpec, MX, htX, lenX, MWin ) \
              MFpspectrum( (MSpec)[0], htSpec, lenSpec, (MX)[0], htX, lenX, (MWin)[0] )
                  /* htSpec, lenSpec must be 2**n,
                     MSpec must be a (htSpec+1)*(lenSpec+1) matrix!!
                     htX >= n*htSpec,  lenX >= n*lenSpec,
                     htWin = 2*htSpec, lenWin = 2*lenSpec */

#define MF_FFT         MFp_FFT
#define MF_Rows_FFT    MFp_Rows_FFT
#define MF_Cols_FFT    MFp_Cols_FFT
#define MF_FFTtoC      MFp_FFTtoC
#define MF_Rows_FFTtoC MFp_Rows_FFTtoC
#define MF_Cols_FFTtoC MFp_Cols_FFTtoC
#define MF_convolve    MFp_convolve
#define MF_deconvolve  MFp_deconvolve
#define MF_filter      MFp_filter
#define MF_autocorr    MFp_autocorr
#define MF_xcorr       MFp_xcorr
#define MF_spectrum    MFp_spectrum
#define MFFFT          MFpFFT
#define MFRows_FFT     MFpRows_FFT
#define MFCols_FFT     MFpCols_FFT
#define MFFFTtoC       MFpFFTtoC
#define MFRows_FFTtoC  MFpRows_FFTtoC
#define MFCols_FFTtoC  MFpCols_FFTtoC
#define MFconvolve     MFpconvolve
#define MFdeconvolve   MFpdeconvolve
#define MFfilter       MFpfilter
#define MFautocorr     MFpautocorr
#define MFxcorr        MFpxcorr
#define MFspectrum     MFpspectrum

#define MFl_FFT( MY, MX, ht, len, dir )     MFlFFT( (MY)[0], (MX)[0], ht, len, dir )
#define MFl_Rows_FFT( MY, MX, ht, len, dir) MFlRows_FFT( (MY)[0], (MX)[0], ht, len, dir )
#define MFl_Cols_FFT( MY, MX, ht, len, dir) MFlCols_FFT( (MY)[0], (MX)[0], ht, len, dir )
#define MFl_FFTtoC( MY, MX, ht, len )       MFlFFTtoC( (MY)[0], (MX)[0], ht, len )
#define MFl_Rows_FFTtoC( MY, MX, ht, len )  MFlRows_FFTtoC( (MY)[0], (MX)[0], ht, len )
#define MFl_Cols_FFTtoC( MY, MX, ht, len )  MFlCols_FFTtoC( (MY)[0], (MX)[0], ht, len )
#define MFl_convolve( MY, MFlt, MX, MRsp, ht, len ) \
                  MFlconvolve( (MY)[0], (MFlt)[0], (MX)[0], (MRsp)[0], ht, len )
#define MFl_deconvolve( MY, MFlt, MX, MRsp, ht, len ) \
                  MFldeconvolve( (MY)[0], (MFlt)[0], (MX)[0], (MRsp)[0], ht, len )
#define MFl_filter( MY, MX, MFlt, ht, len ) MFlfilter( (MY)[0], (MX)[0], (MFlt)[0], ht, len )
#define MFl_autocorr( MACorr, MX, ht, len ) MFlautocorr( (MACorr)[0], (MX)[0], ht, len )
#define MFl_xcorr( MXCorr, MX, MY, ht, len) MFlxcorr( (MXCorr)[0], (MX)[0], (MY)[0], ht, len )
#define MFl_spectrum( MSpec, htSpec, lenSpec, MX, htX, lenX, MWin ) \
              MFlspectrum( (MSpec)[0], htSpec, lenSpec, (MX)[0], htX, lenX, (MWin)[0] )
                  /* htSpec, lenSpec must be 2**n,
                     MSpec must be a (htSpec+1)*(lenSpec+1) matrix!!
                     htX >= n*htSpec,  lenX >= n*lenSpec,
                     htWin = 2*htSpec, lenWin = 2*lenSpec */

#define MFs_FFT( MY, MX, ht, len, dir )     MFsFFT( (MY)[0], (MX)[0], ht, len, dir )
#define MFs_Rows_FFT( MY, MX, ht, len, dir) MFsRows_FFT( (MY)[0], (MX)[0], ht, len, dir )
#define MFs_Cols_FFT( MY, MX, ht, len, dir) MFsCols_FFT( (MY)[0], (MX)[0], ht, len, dir )
#define MFs_FFTtoC( MY, MX, ht, len )       MFsFFTtoC( (MY)[0], (MX)[0], ht, len )
#define MFs_Rows_FFTtoC( MY, MX, ht, len )  MFsRows_FFTtoC( (MY)[0], (MX)[0], ht, len )
#define MFs_Cols_FFTtoC( MY, MX, ht, len )  MFsCols_FFTtoC( (MY)[0], (MX)[0], ht, len )
#define MFs_convolve( MY, MFlt, MX, MRsp, ht, len ) \
                  MFsconvolve( (MY)[0], (MFlt)[0], (MX)[0], (MRsp)[0], ht, len )
#define MFs_deconvolve( MY, MFlt, MX, MRsp, ht, len ) \
                  MFsdeconvolve( (MY)[0], (MFlt)[0], (MX)[0], (MRsp)[0], ht, len )
#define MFs_filter( MY, MX, MFlt, ht, len ) MFsfilter( (MY)[0], (MX)[0], (MFlt)[0], ht, len )
#define MFs_autocorr( MACorr, MX, ht, len ) MFsautocorr( (MACorr)[0], (MX)[0], ht, len )
#define MFs_xcorr( MXCorr, MX, MY, ht, len) MFsxcorr( (MXCorr)[0], (MX)[0], (MY)[0], ht, len )
#define MFs_spectrum( MSpec, htSpec, lenSpec, MX, htX, lenX, MWin ) \
              MFsspectrum( (MSpec)[0], htSpec, lenSpec, (MX)[0], htX, lenX, (MWin)[0] )
                /*   htSpec, lenSpec must be 2**n,
                     MSpec has [htSpec+1][lenSpec+1] elements (!)
                     htX >= n*htSpec,  lenX >= n*lenSpec,
                     htWin = 2*htSpec, lenWin = 2*lenSpec     */


/************************** Data Fitting *********************************

  Note that some of these functions have the prefix VF_, others MF_.
  This depends on the form in which the data to be fitted are recorded:
  vectors are fitted by the VF_ functions, matrices by the MF_ functions.
  All of these functions employ matrix methods internally. The weighted
  versions return covariances in a matrix "Covar". So they are all
  contained in MatrixLib and declared here.
*/

#ifndef V_NONONLINFITWORKSPACE
#ifdef __BORLANDC__
    #pragma option -a-  /* avoid insertion of dummy bytes */
#else   /* MS Visual C++ */
    #pragma pack(push,1)
#endif    /*  Borland or Microsoft */
typedef struct VF_NONLINFITOPTIONS
{
      int        FigureOfMerit;  /*  0:least squares, 1:robust */
             /* Convergence conditions: if the changes achieved
                in successive iterations are lower than any of the
                following values, this signals convergence. Set
                criteria to 0.0, if not applicable              */
      float      AbsTolChi,  /* absolute change of chi */
                 FracTolChi, /* fractional change of chi */
                 AbsTolPar,  /* absolute change of all parameters */
                 FracTolPar; /* fractional change of all parameters */
      unsigned   HowOftenFulfill; /* how often fulfill the above conditions? */
      unsigned   LevelOfMethod;  /* 1: Levenberg-Marquardt method,
                                    2: Downhill Simplex (Nelder and Mead) method,
                                    3: both methods alternating;
                                       add 4 to this in order to try
                                       breaking out of local minima;
                                    0: no fit, calculate only chi2 (and Covar) */
      unsigned   LevMarIterations; /* max.number of successful iterations of LevMar */
      unsigned   LevMarStarts; /* number of starts per LevMar run */
      float      LambdaStart,
                 LambdaMin, LambdaMax,
                 LambdaDiv, LambdaMul;    /* LevMar parameter lambda */
      unsigned   DownhillIterations; /* max.number of successful iterations in Downhill */
      float      DownhillReflection,  /* re-shaping of the simplex */
                 DownhillContraction,
                 DownhillExpansion;
      unsigned   TotalStarts;  /* max. number of LevMar/Downhill pairs */
      fVector    UpperLimits;  /* impose upper limits on parameters */
      fVector    LowerLimits;  /* impose lower limits on parameters */
      void       (*Restrictions)(void);  /* user-defined editing of parameters */
}  VF_NONLINFITOPTIONS;

typedef struct VF_EXPERIMENT
{
    fVector X, Y, InvVar;
    ui      size;
    float   WeightOfExperiment;
     /* InvVar and WeightOfExperiment are needed only for the
        weighted variants of the multifit functions */
} VF_EXPERIMENT;

typedef struct MF_EXPERIMENT
{
    fVector   X, Y;
    fMatrix   MZ, MInvVar;  /* here no compatibility with static matrices! */
    ui        htZ, lenZ;
    float     WeightOfExperiment;
     /* MInvVar and WeightOfExperiment are needed only for the
        weighted variants of the multifit functions */
} MF_EXPERIMENT;

typedef struct VF_NONLINFITWORKSPACE
{
	float	chi2, fIntern1, fIntern2, fIntern3, fIntern4,
			fIntern5, fIntern6, fIntern7, fIntern8, fIntern9, fIntern10;
	fVector	Chi2Detail, 
			vfIntern1, vfIntern2, vfIntern3, vfIntern4, vfIntern5,
			vfIntern6, vfIntern7, vfIntern8, vfIntern9, vfIntern10,
			vfIntern11, vfIntern12, vfIntern13, vfIntern14, vfIntern15, 
			vfIntern16, vfIntern17, vfIntern18, vfIntern19, vfIntern20,
			vfIntern21, *vfIntern22;
	fMatrix	mfIntern1, mfIntern2, mfIntern3, mfIntern4, 
			mfIntern5, mfIntern6, mfIntern7, mfIntern8;
	uVector	vuIntern1, vuIntern2, vuIntern3, vuIntern4;
	uiVector vuiIntern1;
	uiMatrix	muiIntern1;
	ui		uiIntern1;
	int		testDir, stop,
			iIntern1, iIntern2,iIntern3, iIntern4, iIntern5;
	unsigned	testRun, testPar, 
			uIntern1, uIntern2, uIntern3, uIntern4, uIntern5, uIntern6,
			uIntern7, uIntern8, uIntern9, uIntern10, uIntern11;
	void	(*funcIntern1)(void), (*funcIntern2)(void);
	VF_NONLINFITOPTIONS  foptIntern1;
	VF_EXPERIMENT *vfeIntern1;
}  VF_NONLINFITWORKSPACE;

typedef struct MF_NONLINFITWORKSPACE
{
	float	chi2, fIntern1, fIntern2, fIntern3, fIntern4,
			fIntern5, fIntern6, fIntern7, fIntern8, fIntern9, fIntern10;
	fVector	Chi2Detail, 
			vfIntern1, vfIntern2, vfIntern3, vfIntern4, vfIntern5,
			vfIntern6, vfIntern7, vfIntern8, vfIntern9, vfIntern10,
			vfIntern11, vfIntern12, vfIntern13, vfIntern14, vfIntern15, 
			vfIntern16, vfIntern17, vfIntern18, vfIntern19, vfIntern20,
			vfIntern21, *vfIntern22;
	fMatrix	mfIntern1, mfIntern2, mfIntern3, mfIntern4, 
			mfIntern5, *mfIntern6, mfIntern7, mfIntern8;
	uVector	vuIntern1, vuIntern2, vuIntern3, vuIntern4;
	uiVector vuiIntern1;
	uiMatrix	muiIntern1;
	ui		uiIntern1;
	int		testDir, stop,
			iIntern1, iIntern2,iIntern3, iIntern4, iIntern5;
	unsigned	testRun, testPar, 
			uIntern1, uIntern2, uIntern3, uIntern4, uIntern5, uIntern6,
			uIntern7, uIntern8, uIntern9, uIntern10, uIntern11;
	void	(*funcIntern1)(void), (*funcIntern2)(void);
	VF_NONLINFITOPTIONS  foptIntern1;
	MF_EXPERIMENT *mfeIntern1;
	fVector vfIntern23;
	fMatrix mfIntern9, mfIntern10, mfIntern11;
	ui		uiIntern2, uiIntern3, uiIntern4;
}  MF_NONLINFITWORKSPACE;

#ifdef __BORLANDC__
    #pragma option -a.   /* restore default data packing  */
#else   /* MS Visual C++ */
    #pragma pack(pop)
#endif
#endif  /* exclusion of NONLINFITWORKSPACE etc. */

void __vf VF_setNonlinfitOptions( VF_NONLINFITOPTIONS _VFAR *Options );
void __vf VF_getNonlinfitOptions( VF_NONLINFITOPTIONS _VFAR *Options );

int  __vf VF_polyfit( fVector A, unsigned deg, fVector X, fVector Y, ui sizex );
#define   VF_polyfitwW( A, Covar, deg, X, Y, InvVar, sizex ) \
          VFpolyfitwW( A, (Covar)[0], deg, X, Y, InvVar, sizex )
       /* the size of A is deg+1 and Covar has [deg+1][deg+1] elements! */

int  __vf VF_linfit( fVector A, iVector AStatus, unsigned npars,
                     fVector X, fVector Y, ui sizex,
                     void __vf funcs(fVector BasFuncs, float x, unsigned nfuncs) );
#define   VF_linfitwW( A, Covar, AStatus, npars, X, Y, InvVar, sizex, funcs ) \
          VFlinfitwW( A, (Covar)[0], AStatus, npars, X, Y, InvVar, sizex, funcs )
#define   MF_linfit( A, AStatus, npars, X, Y, MZ, htZ, lenZ, funcs ) \
          MFlinfit( A, AStatus, npars, X, Y, (MZ)[0], htZ, lenZ, funcs )
#define   MF_linfitwW( A, Covar, AStatus, npars, X, Y, MZ, MInvVar, htZ, lenZ, funcs ) \
          MFlinfitwW( A, (Covar)[0], AStatus, npars, X, Y, (MZ)[0], (MInvVar)[0], htZ, lenZ, funcs )

void  __vf VF_setLinfitNeglect( float Thresh );
                   /* neglect A[i]=0, if significance smaller than Thresh */
float __vf VF_getLinfitNeglect( void );

float __vf VF_nonlinfit( fVector A, iVector AStatus, unsigned npars,
                    fVector X, fVector Y, ui sizex,
                    void __vf modelfunc(fVector YModel, fVector XModel, ui size),
                    void __vf derivatives(fVector dYdAi,fVector X, ui size, unsigned iPar),
					VF_NONLINFITWORKSPACE *FitWorkSpace, VF_NONLINFITOPTIONS *FitOpts );
            /* returns figure-of-merit of best A. If you don't know the partial
               derivatives with respect to A, call with derivatives=NULL */
#ifndef __cplusplus  /* following macros only for plain-C. Overloaded C++ functions see below */
#define   VF_nonlinfitwW( A, Covar, AStatus, npars, X, Y, InvVar, sizex, modelfunc, deriv, fitworksp, fitopts ) \
          VFnonlinfitwW( A, (Covar)[0], AStatus, npars, X, Y, InvVar, sizex, modelfunc, deriv, fitworksp, fitopts )
#define   MF_nonlinfit( A, AStatus, npars, X, Y, MZ, htZ, lenZ, modelfunc, deriv, fitworksp, fitopts ) \
          MFnonlinfit( A, AStatus, npars, X, Y, (MZ)[0], htZ, lenZ, modelfunc, deriv, fitworksp, fitopts )
#define   MF_nonlinfitwW( A, Covar, AStatus, npars, X, Y, MZ, MInvVar, htZ, lenZ, modelfunc, deriv, fitworksp, fitopts ) \
          MFnonlinfitwW( A, (Covar)[0], AStatus, npars, X, Y, (MZ)[0], (MInvVar)[0], htZ, lenZ, modelfunc, deriv, fitworksp, fitopts )
#endif  /* plain-C macros */

        /* If you know some partial derivatives, you may call these functions
           for those parameters for which you do not know them:           */
void     __vf VF_nonlinfit_autoDeriv( fVector dYdAi, fVector X, ui size, unsigned ipar, VF_NONLINFITWORKSPACE *FitWorkSpace );
void     __vf VF_nonlinfitwW_autoDeriv( fVector dYdAi, fVector X, ui size, unsigned ipar, VF_NONLINFITWORKSPACE *FitWorkSpace );
void     __vf MF_nonlinfit_autoDeriv( fMatrix dZdAi, ui htZ, ui lenZ, fVector X, fVector Y, unsigned ipar, MF_NONLINFITWORKSPACE *FitWorkSpace );
void     __vf MF_nonlinfitwW_autoDeriv( fMatrix dZdAi, ui htZ, ui lenZ, fVector X, fVector Y, unsigned ipar, MF_NONLINFITWORKSPACE *FitWorkSpace );
       /* The following functions allow to monitor the progress of
          a nonlinear fitting procedure or to manually stop it:     */
float    __vf VF_nonlinfit_getChi2( VF_NONLINFITWORKSPACE *FitWorkSpace );
float    __vf VF_nonlinfitwW_getChi2( VF_NONLINFITWORKSPACE *FitWorkSpace );
float    __vf MF_nonlinfit_getChi2( MF_NONLINFITWORKSPACE *FitWorkSpace );
float    __vf MF_nonlinfitwW_getChi2( MF_NONLINFITWORKSPACE *FitWorkSpace );
void     __vf VF_nonlinfit_getBestValues( fVector ABest, VF_NONLINFITWORKSPACE *FitWorkSpace );
void     __vf VF_nonlinfitwW_getBestValues( fVector ABest, VF_NONLINFITWORKSPACE *FitWorkSpace );
void     __vf MF_nonlinfit_getBestValues( fVector ABest, MF_NONLINFITWORKSPACE *FitWorkSpace );
void     __vf MF_nonlinfitwW_getBestValues( fVector ABest, MF_NONLINFITWORKSPACE *FitWorkSpace );
unsigned __vf VF_nonlinfit_getTestRun( VF_NONLINFITWORKSPACE *FitWorkSpace );
unsigned __vf VF_nonlinfitwW_getTestRun( VF_NONLINFITWORKSPACE *FitWorkSpace );
unsigned __vf MF_nonlinfit_getTestRun( MF_NONLINFITWORKSPACE *FitWorkSpace );
unsigned __vf MF_nonlinfitwW_getTestRun( MF_NONLINFITWORKSPACE *FitWorkSpace );
unsigned __vf VF_nonlinfit_getTestPar( VF_NONLINFITWORKSPACE *FitWorkSpace );
unsigned __vf VF_nonlinfitwW_getTestPar( VF_NONLINFITWORKSPACE *FitWorkSpace );
unsigned __vf MF_nonlinfit_getTestPar( MF_NONLINFITWORKSPACE *FitWorkSpace );
unsigned __vf MF_nonlinfitwW_getTestPar( MF_NONLINFITWORKSPACE *FitWorkSpace );
int      __vf VF_nonlinfit_getTestDir( VF_NONLINFITWORKSPACE *FitWorkSpace );
int      __vf VF_nonlinfitwW_getTestDir( VF_NONLINFITWORKSPACE *FitWorkSpace );
int      __vf MF_nonlinfit_getTestDir( MF_NONLINFITWORKSPACE *FitWorkSpace );
int      __vf MF_nonlinfitwW_getTestDir( MF_NONLINFITWORKSPACE *FitWorkSpace );
void     __vf VF_nonlinfit_stop( VF_NONLINFITWORKSPACE *FitWorkSpace );
void     __vf VF_nonlinfitwW_stop( VF_NONLINFITWORKSPACE *FitWorkSpace );
void     __vf MF_nonlinfit_stop( MF_NONLINFITWORKSPACE *FitWorkSpace );
void     __vf MF_nonlinfitwW_stop( MF_NONLINFITWORKSPACE *FitWorkSpace );

int  __vf VF_multiLinfit( fVector A, iVector AStatus, unsigned ma,
                VF_EXPERIMENT _VFAR *ListOfExperiments, unsigned nexperiments,
                void __vf funcs(fVector BasFuncs, float x,
                              unsigned nfuncs, unsigned iexperiment) );
#define   VF_multiLinfitwW( A, Covar, AStatus, npars, ListOfEx, nexp, funcs ) \
          VFmultiLinfitwW( A, (Covar)[0], AStatus, npars, ListOfEx, nexp, funcs )
int  __vf MF_multiLinfit( fVector A, iVector AStatus, unsigned ma,
                MF_EXPERIMENT _VFAR *ListOfExperiments, unsigned nexperiments,
                void __vf funcs(fVector BasFuncs, float x, float y,
                              unsigned nfuncs, unsigned iexperiment) );
#define   MF_multiLinfitwW( A, Covar, AStatus, npars, ListOfEx, nexp, funcs ) \
          MFmultiLinfitwW( A, (Covar)[0], AStatus, npars, ListOfEx, nexp, funcs )
float __vf VF_multiNonlinfit( fVector A, iVector AStatus, unsigned npars,
                VF_EXPERIMENT _VFAR *ListOfExperiments, unsigned nexperiments,
                void __vf modelfunc(fVector YModel, fVector XModel,
                                  ui size, unsigned iexperiment),
                void __vf derivatives(fVector dYdAi,fVector X, ui size,
                                  unsigned ipar, unsigned iexperiment),
				VF_NONLINFITWORKSPACE *FitWorkSpace, VF_NONLINFITOPTIONS *FitOpts );
            /* returns figure-of-merit of best A. If you don't know the
               partial derivatives, set derivatives=NULL */
float __vf MF_multiNonlinfit( fVector A, iVector AStatus, unsigned npars,
                MF_EXPERIMENT _VFAR *ListOfExperiments, unsigned nexperiments,
                void __vf modelfunc(fMatrix MZModel, ui htZ, ui lenZ,
                                  fVector X, fVector Y, unsigned iexperiment),
                void __vf derivatives(fMatrix dZdAi, ui htZ, ui lenZ,
                                    fVector X, fVector Y, unsigned ipar,
                                    unsigned iexperiment),
				MF_NONLINFITWORKSPACE *FitWorkSpace, VF_NONLINFITOPTIONS *FitOpts );
#ifndef __cplusplus  /* following macros only for plain-C. Overloaded C++ functions see below */
#define   VF_multiNonlinfitwW( A, Covar, AStatus, npars, ListOfEx, nexp, modfunc, deriv, fitworksp, fitopts ) \
          VFmultiNonlinfitwW( A, (Covar)[0], AStatus, npars, ListOfEx, nexp, modfunc, deriv, fitworksp, fitopts )
#define   MF_multiNonlinfitwW( A, Covar, AStatus, npars, ListOfEx, nexp, modfunc, deriv, fitworksp, fitopts ) \
          MFmultiNonlinfitwW( A, (Covar)[0], AStatus, npars, ListOfEx, nexp, modfunc, deriv, fitworksp, fitopts )
#endif  /* plain-C macros */

void  __vf VF_multiNonlinfit_autoDeriv( fVector dYdAi, fVector X, ui size,
                                       unsigned ipar, unsigned iexperiment, VF_NONLINFITWORKSPACE *FitWorkSpace );
void  __vf VF_multiNonlinfitwW_autoDeriv( fVector dYdAi, fVector X, ui size,
                                        unsigned ipar, unsigned iexperiment, VF_NONLINFITWORKSPACE *FitWorkSpace );
void  __vf MF_multiNonlinfit_autoDeriv( fMatrix dZdAi, ui htZ, ui lenZ,
                                    fVector X, fVector Y,
                                    unsigned ipar, unsigned iexperiment, MF_NONLINFITWORKSPACE *FitWorkSpace );
void  __vf MF_multiNonlinfitwW_autoDeriv( fMatrix dZdAi, ui htZ, ui lenZ,
                                    fVector X, fVector Y,
                                    unsigned ipar, unsigned iexperiment, MF_NONLINFITWORKSPACE *FitWorkSpace );
float    __vf VF_multiNonlinfit_getChi2( VF_NONLINFITWORKSPACE *FitWorkSpace );
float    __vf VF_multiNonlinfitwW_getChi2( VF_NONLINFITWORKSPACE *FitWorkSpace );
float    __vf MF_multiNonlinfit_getChi2( MF_NONLINFITWORKSPACE *FitWorkSpace );
float    __vf MF_multiNonlinfitwW_getChi2( MF_NONLINFITWORKSPACE *FitWorkSpace );
void     __vf VF_multiNonlinfit_getChi2Detail( fVector Chi2Detail, VF_NONLINFITWORKSPACE *FitWorkSpace );
void     __vf VF_multiNonlinfitwW_getChi2Detail( fVector Chi2Detail, VF_NONLINFITWORKSPACE *FitWorkSpace );
void     __vf MF_multiNonlinfit_getChi2Detail( fVector Chi2Detail, MF_NONLINFITWORKSPACE *FitWorkSpace );
void     __vf MF_multiNonlinfitwW_getChi2Detail( fVector Chi2Detail, MF_NONLINFITWORKSPACE *FitWorkSpace );
void     __vf VF_multiNonlinfit_getBestValues( fVector ABest, VF_NONLINFITWORKSPACE *FitWorkSpace );
void     __vf VF_multiNonlinfitwW_getBestValues( fVector ABest, VF_NONLINFITWORKSPACE *FitWorkSpace );
void     __vf MF_multiNonlinfit_getBestValues( fVector ABest, MF_NONLINFITWORKSPACE *FitWorkSpace );
void     __vf MF_multiNonlinfitwW_getBestValues( fVector ABest, MF_NONLINFITWORKSPACE *FitWorkSpace );
unsigned __vf VF_multiNonlinfit_getTestRun( VF_NONLINFITWORKSPACE *FitWorkSpace );
unsigned __vf VF_multiNonlinfitwW_getTestRun( VF_NONLINFITWORKSPACE *FitWorkSpace );
unsigned __vf MF_multiNonlinfit_getTestRun( MF_NONLINFITWORKSPACE *FitWorkSpace );
unsigned __vf MF_multiNonlinfitwW_getTestRun( MF_NONLINFITWORKSPACE *FitWorkSpace );
unsigned __vf VF_multiNonlinfit_getTestPar( VF_NONLINFITWORKSPACE *FitWorkSpace );
unsigned __vf VF_multiNonlinfitwW_getTestPar( VF_NONLINFITWORKSPACE *FitWorkSpace );
unsigned __vf MF_multiNonlinfit_getTestPar( MF_NONLINFITWORKSPACE *FitWorkSpace );
unsigned __vf MF_multiNonlinfitwW_getTestPar( MF_NONLINFITWORKSPACE *FitWorkSpace );
int      __vf VF_multiNonlinfit_getTestDir( VF_NONLINFITWORKSPACE *FitWorkSpace );
int      __vf VF_multiNonlinfitwW_getTestDir( VF_NONLINFITWORKSPACE *FitWorkSpace );
int      __vf MF_multiNonlinfit_getTestDir( MF_NONLINFITWORKSPACE *FitWorkSpace );
int      __vf MF_multiNonlinfitwW_getTestDir( MF_NONLINFITWORKSPACE *FitWorkSpace );
void     __vf VF_multiNonlinfit_stop( VF_NONLINFITWORKSPACE *FitWorkSpace );
void     __vf VF_multiNonlinfitwW_stop( VF_NONLINFITWORKSPACE *FitWorkSpace );
void     __vf MF_multiNonlinfit_stop( MF_NONLINFITWORKSPACE *FitWorkSpace );
void     __vf MF_multiNonlinfitwW_stop( MF_NONLINFITWORKSPACE *FitWorkSpace );

/**************************  Input and Output  **************************/

#define MF_fprint( stream, MA, ht, len, linewidth ) \
                    MFfprint( stream, (MA)[0], ht, len, linewidth )
#define MF_print( MA, ht, len )  MFfprint( stdout, (MA)[0], ht, len, 80 )
#define MF_cprint( MA, ht, len ) MFcprint( (MA)[0], ht, len )
  /*  MF_print, MF_cprint usable only for console applications! */

#define MF_write( str, MA, ht, len )   MFwrite( str, (MA)[0], ht, len )
#define MF_read( MA, ht, len, str )    MFread( (MA)[0], ht, len, str )
#define MF_setWriteFormat              VF_setWriteFormat
#define MF_setWriteSeparate            VF_setNWriteSeparate
                                   /* write and read in ascii format */
#define MF_store( str, MA, ht, len ) \
                           VF_store( str, (MA)[0], (len)*(ht) )
#define MF_recall( MA, ht, len, str) \
                           VF_recall( (MA)[0], (len)*(ht), str)
                                  /* store and recall in binary format */


/*************************************************************************
 * Here are now the actual declarations of the functions used internally.*
 * These declarations may change in future versions of MatrixLib!        *
 * You should not care too much about them, except in the case you need  *
 * the actual address of a run-time function (see above). Under all      *
 * "normal" circumstances, use only the names defined above in the       *
 * macro section!                                                        *
 *************************************************************************/

void  __vf MFgetElement( float *y, fPMatrix X, ui ht, ui len, ui m, ui n );
void  __vf MFsetElement( fPMatrix X, ui ht, ui len, ui m, ui n, float C );
float _VFAR * __vf MFPelement( fPMatrix X, ui ht, ui len,  ui m, ui n );
                  /* pointer is normalized in memory model HUGE */
#define MFelement( MA, ht, len, m, n ) (*MFPelement( MA, ht, len, m, n ))

#define MFequ0( MA, ht, len )            VF_equ0( MA, (ht)*(len) )
void   __vf  MFequ1( fPMatrix MA, ui len );  /* identity matrix */
void   __vf  MFequm1( fPMatrix MA, ui len );  /* neg. identity matrix */
void   __vf  MFouterprod( fPMatrix MA, fVector X,  fVector Y,
                          ui ht, ui len );

void   __vf  MFRow_equ0( fPMatrix MA, ui ht, ui len,
                         ui iRow );
void   __vf  MFCol_equ0( fPMatrix MA, ui ht, ui len,
                         ui iCol );
void   __vf  MFDia_equ0( fPMatrix MA, ui len );

void   __vf  MFRow_equC( fPMatrix MA, ui ht, ui len,
                         ui iRow, float C );
void   __vf  MFCol_equC( fPMatrix MA, ui ht, ui len,
                         ui iCol, float C );
void   __vf  MFDia_equC( fPMatrix MA, ui len, float C );

void   __vf  MFRow_equV( fPMatrix MA, ui ht, ui len,
                         ui iRow, fVector X );
void   __vf  MFCol_equV( fPMatrix MA, ui ht, ui len,
                         ui iCol, fVector X );
void   __vf  MFDia_equV( fPMatrix MA, ui len, fVector X );

void   __vf  MFTrd_equM( fPMatrix MA, fPMatrix MTrd, ui len );
void   __vf  MFTrd_extract( fPMatrix MTrd, fPMatrix MA, ui len );

#define MFequM( MB, MA, ht, len )  VF_equV( MB, MA, (ht)*(len) )
#define MFneg( MB, MA, ht, len )   VF_neg( MB, MA, (ht)*(len) )
void   __vf  MFUequL( fPMatrix MA, ui len );
void   __vf  MFLequU( fPMatrix MA, ui len );

void   __vf  MFHann( fPMatrix MA, ui ht, ui len );
#define MFHanning MFHann
void   __vf  MFParzen(  fPMatrix MA, ui ht, ui len );
void   __vf  MFWelch(   fPMatrix MA, ui ht, ui len );

/********  Extracting a submatrix and copying a submatrix back  *********/

void  __vf  MFsubmatrix( fPMatrix MSub,
                          ui subHt,  ui subLen,
                          fPMatrix MSrce,
                          ui srceHt,  ui srceLen,
                          ui firstRowInCol,  ui sampInCol,
                          ui firstColInRow,  ui sampInRow );

void  __vf  MFsubmatrix_equM( fPMatrix MDest,
                               ui destHt,     ui destLen,
                               ui firstRowInCol,  ui sampInCol,
                               ui firstColInRow,  ui sampInRow,
                               fPMatrix MSrce,
                               ui srceHt,     ui srceLen );

void  __vf  MFequMblock(  fPMatrix MSub,
                          ui subHt,  ui subLen,
                          fPMatrix MSrce,
                          ui srceHt,  ui srceLen,
                          ui firstRowInCol,  ui firstColInRow );

void  __vf  MFblock_equM( fPMatrix MDest,
                          ui destHt,     ui destLen,
                          ui firstRowInCol,  ui firstColInRow,
                          fPMatrix MSrce,
                          ui srceHt,     ui srceLen );

void  __vf  MFequMblockT( fPMatrix MSub,
                          ui subHt,  ui subLen,
                          fPMatrix MSrce,
                          ui srceHt,  ui srceLen,
                          ui firstRowInCol,  ui firstColInRow );

void  __vf  MFblock_equMT( fPMatrix MDest,
                          ui destHt,     ui destLen,
                          ui firstRowInCol,  ui firstColInRow,
                          fPMatrix MSrce,
                          ui srceHt,     ui srceLen );


/*****   Extracting a single row or a single column or the diagonal  *****
 *       and storing it into a vector                                    */

void __vf MFRow_extract( fVector Y, fPMatrix MA, ui ht, ui len, ui iRow );
void __vf MFCol_extract( fVector Y, fPMatrix MA, ui ht, ui len, ui iCol );
void __vf MFDia_extract( fVector Y, fPMatrix MA, ui len );


/**********  Deleting or inserting a row or a column *****************/

void __vf MFRow_delete( fPMatrix MB, fPMatrix MA,
                        ui htA, ui lenA, ui iRow );
void __vf MFCol_delete( fPMatrix MB, fPMatrix MA,
                        ui htA, ui lenA, ui iCol );
void __vf MFRow_insert( fPMatrix MB, fPMatrix MA, ui htB,
                        ui lenB, ui iRow, fVector X );
void __vf MFCol_insert( fPMatrix MB, fPMatrix MA, ui htB,
                        ui lenB, ui iCol, fVector X );


/*****************    Basic arithmetic operations ***********************
     performed on one single row,  or one single column of any matrix,
     or on the diagonal of a square matrix                              */

void   __vf  MFRow_neg( fPMatrix MX, ui ht, ui len, ui iRow );
void   __vf  MFCol_neg( fPMatrix MX, ui ht, ui len, ui iCol );

void   __vf  MFRow_addC( fPMatrix MA, ui ht, ui len,
                         ui iRow, float C );
void   __vf  MFCol_addC( fPMatrix MA, ui ht, ui len,
                         ui iCol, float C );
void   __vf  MFDia_addC( fPMatrix MA, ui len, float C );

void   __vf  MFRow_subC( fPMatrix MA, ui ht, ui len,
                         ui iRow, float C );
void   __vf  MFCol_subC( fPMatrix MA, ui ht, ui len,
                         ui iCol, float C );
void   __vf  MFDia_subC( fPMatrix MA, ui len, float C );

void   __vf  MFRow_addV( fPMatrix MA, ui ht, ui len,
                         ui iRow, fVector X );
void   __vf  MFCol_addV( fPMatrix MA, ui ht, ui len,
                         ui iCol, fVector X );
void   __vf  MFDia_addV( fPMatrix MA, ui len, fVector X );

void   __vf  MFRow_subV( fPMatrix MA, ui ht, ui len,
                         ui iRow, fVector X );
void   __vf  MFCol_subV( fPMatrix MA, ui ht, ui len,
                         ui iCol, fVector X );
void   __vf  MFDia_subV( fPMatrix MA, ui len, fVector X );

void   __vf  MFRow_subrC( fPMatrix MA, ui ht, ui len,
                         ui iRow, float C );
void   __vf  MFCol_subrC( fPMatrix MA, ui ht, ui len,
                         ui iCol, float C );
void   __vf  MFDia_subrC( fPMatrix MA, ui len, float C );

void   __vf  MFRow_subrV( fPMatrix MA, ui ht, ui len,
                         ui iRow, fVector X );
void   __vf  MFCol_subrV( fPMatrix MA, ui ht, ui len,
                         ui iCol, fVector X );
void   __vf  MFDia_subrV( fPMatrix MA, ui len, fVector X );

void   __vf  MFRow_mulC( fPMatrix MA, ui ht, ui len,
                         ui iRow, float C );
void   __vf  MFCol_mulC( fPMatrix MA, ui ht, ui len,
                         ui iCol, float C );
void   __vf  MFDia_mulC( fPMatrix MA, ui len, float C );

void   __vf  MFRow_mulV( fPMatrix MA, ui ht, ui len,
                         ui iRow, fVector X );
void   __vf  MFCol_mulV( fPMatrix MA, ui ht, ui len,
                         ui iCol, fVector X );
void   __vf  MFDia_mulV( fPMatrix MA, ui len, fVector X );

void   __vf  MFRow_divC( fPMatrix MA, ui ht, ui len,
                         ui iRow, float C );
void   __vf  MFCol_divC( fPMatrix MA, ui ht, ui len,
                         ui iCol, float C );
void   __vf  MFDia_divC( fPMatrix MA, ui len, float C );

void   __vf  MFRow_divV( fPMatrix MA, ui ht, ui len,
                         ui iRow, fVector X );
void   __vf  MFCol_divV( fPMatrix MA, ui ht, ui len,
                         ui iCol, fVector X );
void   __vf  MFDia_divV( fPMatrix MA, ui len, fVector X );

void   __vf  MFRow_divrC( fPMatrix MA, ui ht, ui len,
                         ui iRow, float C );
void   __vf  MFCol_divrC( fPMatrix MA, ui ht, ui len,
                         ui iCol, float C );
void   __vf  MFDia_divrC( fPMatrix MA, ui len, float C );

void   __vf  MFRow_divrV( fPMatrix MA, ui ht, ui len,
                         ui iRow, fVector X );
void   __vf  MFCol_divrV( fPMatrix MA, ui ht, ui len,
                         ui iCol, fVector X );
void   __vf  MFDia_divrV( fPMatrix MA, ui len, fVector X );


/******  One-dimensional vector operations **********************
         performed along all rows or all columns simultaneously,
         or along the diagonal of a square matrix                */

void  __vf  MFRows_max( fVector Y, fPMatrix MA, ui ht, ui len );
void  __vf  MFCols_max( fVector Y, fPMatrix MA, ui ht, ui len );
float __vf  MFDia_max(  fPMatrix MA, ui len );
void  __vf  MFRows_min( fVector Y, fPMatrix MA, ui ht, ui len );
void  __vf  MFCols_min( fVector Y, fPMatrix MA, ui ht, ui len );
float __vf  MFDia_min(  fPMatrix MA, ui len );

void  __vf  MFRows_absmax( fVector Y, fPMatrix MA, ui ht, ui len );
void  __vf  MFCols_absmax( fVector Y, fPMatrix MA, ui ht, ui len );
float __vf  MFDia_absmax(  fPMatrix MA, ui len );
void  __vf  MFRows_absmin( fVector Y, fPMatrix MA, ui ht, ui len );
void  __vf  MFCols_absmin( fVector Y, fPMatrix MA, ui ht, ui len );
float __vf  MFDia_absmin(  fPMatrix MA, ui len );

void  __vf  MFRows_sum( fVector Y, fPMatrix MA, ui ht, ui len );
void  __vf  MFCols_sum( fVector Y, fPMatrix MA, ui ht, ui len );
float __vf  MFDia_sum(  fPMatrix MA, ui len );
void  __vf  MFRows_ssq( fVector Y, fPMatrix MA, ui ht, ui len );
void  __vf  MFCols_ssq( fVector Y, fPMatrix MA, ui ht, ui len );
float __vf  MFDia_ssq(  fPMatrix MA, ui len );
void  __vf  MFRows_prod(fVector Y, fPMatrix MA, ui ht, ui len );
void  __vf  MFCols_prod(fVector Y, fPMatrix MA, ui ht, ui len );
float __vf  MFDia_prod( fPMatrix MA, ui len );

void  __vf  MFRows_runsum( fPMatrix MA, ui ht, ui len );
void  __vf  MFCols_runsum( fPMatrix MA, ui ht, ui len );
void  __vf  MFRows_runprod( fPMatrix MA, ui ht, ui len );
void  __vf  MFCols_runprod( fPMatrix MA, ui ht, ui len );

void  __vf  MFRows_rotate( fPMatrix MA, ui ht, ui len, ssize_t pos );
void  __vf  MFCols_rotate( fPMatrix MA, ui ht, ui len, ssize_t pos );
void  __vf  MFRows_rotate_buf( fPMatrix MA, ui ht, ui len, ssize_t pos, fPMatrix MBuf );
void  __vf  MFCols_rotate_buf( fPMatrix MA, ui ht, ui len, ssize_t pos, fPMatrix MBuf );
void  __vf  MFRows_reflect( fPMatrix MA, ui ht, ui len );
void  __vf  MFCols_reflect( fPMatrix MA, ui ht, ui len );
void  __vf  MFRows_rev( fPMatrix MA, ui ht, ui len );
void  __vf  MFCols_rev( fPMatrix MA, ui ht, ui len );

void  __vf  MFRows_distribution( uiPMatrix MAbund, fVector Limits, ui nBins, fPMatrix MX, ui ht, ui len, int mode );
void  __vf  MFCols_distribution( uiPMatrix MAbund, fVector Limits, ui nBins, fPMatrix MX, ui ht, ui len, int mode );

/********  Operations involving two rows or two colums of one matrix  *****/

void   __vf  MFRows_exchange( fPMatrix MA, ui ht, ui len, ui i1, ui i2 );
void   __vf  MFCols_exchange( fPMatrix MA, ui ht, ui len, ui i1, ui i2 );

void   __vf  MFRows_add( fPMatrix MA, ui ht, ui len, ui destRow, ui sourceRow );
void   __vf  MFCols_add( fPMatrix MA, ui ht, ui len, ui destCol, ui sourceCol );

void   __vf  MFRows_sub( fPMatrix MA, ui ht, ui len, ui destRow, ui sourceRow );
void   __vf  MFCols_sub( fPMatrix MA, ui ht, ui len, ui destCol, ui sourceCol );

void   __vf  MFRows_Cadd( fPMatrix MA, ui ht, ui len, ui destRow, ui sourceRow, float C );
void   __vf  MFCols_Cadd( fPMatrix MA, ui ht, ui len, ui destCol, ui sourceCol, float C );

void   __vf  MFRows_lincomb( fPMatrix MA, ui ht, ui len,
                              ui destRow,  float  destC,
                              ui srceRow,  float  srceC );
void   __vf  MFCols_lincomb( fPMatrix MA, ui ht, ui len,
                              ui destCol,  float  destC,
                              ui srceCol,  float  srceC );

/*********************  Center of gravity *****************************/

#if defined __cplusplus && defined _CMATH_CLASSDEFS
} // the following functions cannot be extern "C", if fComplex is a class
#endif
fComplex   __vf  MFcenterOfGravityInd( fPMatrix MA, ui ht, ui len );
fComplex   __vf  MFcenterOfGravityV( fVector X, fVector Y, fPMatrix MA,
                                     ui ht, ui len );
#if defined __cplusplus && defined _CMATH_CLASSDEFS
extern "C" {
#endif


/****************  Transposing and rotating a matrix **********************/

void  __vf  MFtranspose( fPMatrix MTr, fPMatrix MA,
                          ui htTr, ui lenTr );
void  __vf  MFrotate90(  fPMatrix MRot, fPMatrix MA, ui htRot, ui lenRot );
#define     MFrotate180( MRot, MA, htRot, lenRot ) \
                VF_rev( MRot, MA, (htRot)*(lenRot) )
void  __vf  MFrotate270( fPMatrix MRot, fPMatrix MA, ui htRot, ui lenRot );

/********************** Interpolation of Matrix elements **************/

void __vf  MFpolyinterpol( fPMatrix MZ, fVector X, fVector Y, ui ht, ui len,
       fVector XTab, fVector YTab, fPMatrix MZTab, ui httab, ui lentab,
       unsigned degX, unsigned degY );
void __vf  MFratinterpol( fPMatrix MZ, fVector X, fVector Y, ui ht, ui len,
       fVector XTab, fVector YTab, fPMatrix MZTab, ui httab, ui lentab,
       unsigned degX, unsigned degY );
void __vf  MFnatCubSplineInterpol( fPMatrix MZ, fVector X, fVector Y, ui ht, ui len,
       fVector XTab, fVector YTab, fPMatrix MZTab, ui httab, ui lentab );

/************************ Matrix Arithmetics *************************/

#define MFaddM( MC, MA, MB, htA, lenA ) \
                 VF_addV( MC, MA, MB, (htA)*(lenA) )
void __vf  MFaddMT( fPMatrix MC, fPMatrix MA, fPMatrix MB,
                    ui htA, ui lenA );
#define MFsubM( MC, MA, MB, htA, lenA ) \
                 VF_subV( MC, MA, MB, (htA)*(lenA) )
void __vf  MFsubMT( fPMatrix MC, fPMatrix MA, fPMatrix MB,
                    ui htA, ui lenA );
void __vf  MFsubrMT( fPMatrix MC, fPMatrix MA, fPMatrix MB,
                    ui htA, ui lenA );
#define MFmulC( MB, MA, htA, lenA, C ) \
                 VF_mulC( MB, MA, (htA)*(lenA), C )
#define MFdivC( MB, MA, htA, lenA, C ) \
                 VF_divC( MB, MA, (htA)*(lenA), C )
#define MFsaddM( MC, MA, MB, htA, lenA, C ) \
                 VFs_addV( MC, MA, MB, (htA)*(lenA), C )
void __vf  MFsaddMT( fPMatrix MC, fPMatrix MA, fPMatrix MB,
                    ui htA, ui lenA, float C );
#define MFssubM( MC, MA, MB, htA, lenA, C ) \
                 VFs_subV( MC, MA, MB, (htA)*(lenA), C )
void __vf  MFssubMT( fPMatrix MC, fPMatrix MA, fPMatrix MB,
                    ui htA, ui lenA, float C );
void __vf  MFssubrMT( fPMatrix MC, fPMatrix MA, fPMatrix MB,
                    ui htA, ui lenA, float C );
#define MFlincomb( MC, MA, MB, htA, lenA, CA, CB ) \
                 VF_lincomb( MC, MA, MB, (htA)*(lenA), CA, CB )
void  __vf  MFmulV( fVector Y, fPMatrix MA, fVector X,
                    ui htA, ui lenA );
void  __vf  MFTmulV( fVector Y, fPMatrix MA, fVector X,
                     ui htA, ui lenA );
void  __vf  VFmulM( fVector Y, fVector X, fPMatrix MA,
                    ui htA, ui lenA );
void  __vf  VFmulMT( fVector Y, fVector X, fPMatrix MA,
                     ui htA, ui lenA );
void  __vf  MFmulM( fPMatrix MC, fPMatrix MA, fPMatrix MB,
                    ui htA, ui lenA, ui lenB );
void  __vf  MFmulMT( fPMatrix MC, fPMatrix MA, fPMatrix MB,
                    ui htA, ui lenA, ui htB );
void  __vf  MFTmulM( fPMatrix MC, fPMatrix MA, fPMatrix MB,
                    ui htA, ui lenA, ui lenB );
void  __vf  MFTmulMT( fPMatrix MC, fPMatrix MA, fPMatrix MB,
                    ui htA, ui lenA, ui htB );
void  __vf  MFdiamulM( fPMatrix MC, fPMatrix MADia, fPMatrix MB,
                    ui htB, ui lenB );
void  __vf  MFdiamulMT( fPMatrix MC, fPMatrix MADia, fPMatrix MB,
                    ui htB, ui lenB );
void  __vf  MFmulMdia( fPMatrix MC, fPMatrix MA, fPMatrix MBDia,
                    ui htA, ui lenA );
void  __vf  MFTmulMdia( fPMatrix MC, fPMatrix MA, fPMatrix MBDia,
                    ui htA, ui lenA );


/*************************  Linear Algebra    *****************************/

int    __vf  MFLUdecompose( fPMatrix MLU,  uiVector Ind, fPMatrix MA, ui len );

void   __vf  MFLUsolve( fVector X, fPMatrix MLU, fVector B, uiVector Ind, ui len );
void   __vf  MFLUinv( fPMatrix MInv, fPMatrix MLU, uiVector Ind, ui len );
float  __vf  MFLUdet( fPMatrix MLU, ui len, int permut );
void   __vf  MFLUimprove( fVector X, fVector B, fPMatrix MA, fPMatrix MLU,
                          uiVector Ind, ui len );

int    __vf  MFCholeskyLdecompose( fPMatrix ML,  fPMatrix MA, ui len ); /* returns 0 for success, 1 for non-positive definite matrix */
void   __vf  MFCholeskyLsolve( fVector X, fPMatrix ML, fVector B, ui len );
void   __vf  MFCholeskyLimprove( fVector X, fVector B, fPMatrix MA, fPMatrix ML, ui len );
void   __vf  MFCholeskyLinv( fPMatrix MInv, fPMatrix ML, ui len );
int    __vf  MFCholeskyRdecompose( fPMatrix MR,  fPMatrix MA, ui len ); /* returns 0 for success, 1 for non-positive definite matrix */
void   __vf  MFCholeskyRsolve( fVector X, fPMatrix MR, fVector B, ui len );
void   __vf  MFCholeskyRimprove( fVector X, fVector B, fPMatrix MA, fPMatrix MR, ui len );
void   __vf  MFCholeskyRinv( fPMatrix MInv, fPMatrix MR, ui len );
float  __vf  MFCholeskyDet( fPMatrix MLU, ui len );

int   __vf  MFSVdecompose( fPMatrix MU, fPMatrix MV, fVector W, fPMatrix MA, ui htA, ui lenA );
void  __vf  MFSVsort( fPMatrix MUout, fPMatrix MVout, fVector Wout, 
					  fPMatrix MUraw, fPMatrix MVraw, fVector Wraw, ui htU, ui lenU );
void  __vf  MFSVsolve( fVector X, fPMatrix MU, fPMatrix MV, fVector W,
                       fVector B, ui htA, ui lenA );

          /*  functions using LUD or SVD     */
int    __vf  MFsolve( fVector X, fPMatrix MA, fVector B, ui len );
                  /* ret.value != 0 signals error */
int    __vf  MFinv( fPMatrix MInv, fPMatrix MA, ui len );
                 /* ret.value != 0 signals error */
float  __vf  MFdet( fPMatrix MA, ui len );

int    __vf  MFsolveBySVD( fVector X, fPMatrix MA, fVector B,
                           ui htA, ui lenA );
              /*  sizX = lenA,  sizB = htA.  ret.value != 0 signals failure */
int    __vf  MFsafeSolve( fVector X, fPMatrix MA, fVector B, ui len );
              /* ret.value 0: success via LUD; 1: success via SVD; -1: error */

/* functions for symmetric matrices which may or may not be positive definite: */
int    __vf  MFsymsolve( fVector X, fPMatrix MA, fVector B, ui len );
                  /* ret.value != 0 signals error */
int    __vf  MFsyminv( fPMatrix MInv, fPMatrix MA, ui len );
                 /* ret.value != 0 signals error */
float  __vf  MFsymdet( fPMatrix MA, ui len );


	/*********  Eigenvalues and Eigenvectors  ********/

int  __vf MFs_eigenvalues( fVector EigV, fPMatrix EigM, fPMatrix MA, ui len,
                        int CalcEigenVec );
int  __vf MFs_sqrt( fPMatrix MY, fPMatrix MX, ui len );
              /* ret. value 0: success; 1: failure */

/*************  Two-Dimensional Fourier-Transform Methods *****************/

void  __vf   MFpFFT( fPMatrix MY, fPMatrix MX, ui ht, ui len, int dir );
void  __vf   MFbFFT( fPMatrix MY, fPMatrix MX, ui ht, ui len, int dir, fVector Buf );
void  __vf   MFpFFTtoC( cfPMatrix MY, fPMatrix MX, ui ht, ui len );
void  __vf   MFbFFTtoC( cfPMatrix MY, fPMatrix MX, ui ht, ui len, cfVector Buf );
void  __vf   MFpconvolve( fPMatrix MY, fPMatrix MFlt, fPMatrix MX,
                          fPMatrix MRsp, ui ht, ui len );
void  __vf   MFpdeconvolve( fPMatrix MY, fPMatrix MFlt, fPMatrix MX,
                            fPMatrix MRsp, ui ht, ui len );
void  __vf   MFpfilter( fPMatrix MY, fPMatrix MX, fPMatrix MFlt,
                        ui ht, ui len );
void  __vf   MFpautocorr( fPMatrix MACorr, fPMatrix MX,
                          ui ht, ui len );
void  __vf   MFpxcorr( fPMatrix MXCorr, fPMatrix MX, fPMatrix MY,
                          ui ht, ui len );
void  __vf   MFpspectrum( fPMatrix MSpec, ui htSpec, ui lenSpec,
                          fPMatrix MX, ui htX, ui lenX,
                          fPMatrix MWin );
void  __vf   MFpRows_FFT( fPMatrix MY, fPMatrix MX, ui ht, ui len, int dir );
void  __vf   MFpCols_FFT( fPMatrix MY, fPMatrix MX, ui ht, ui len, int dir );
void  __vf   MFbRows_FFT( fPMatrix MY, fPMatrix MX, ui ht, ui len, int dir, fVector Buf );
void  __vf   MFbCols_FFT( fPMatrix MY, fPMatrix MX, ui ht, ui len, int dir, fVector Buf );
void  __vf   MFpRows_FFTtoC( cfPMatrix MY, fPMatrix MX, ui ht, ui len );
void  __vf   MFpCols_FFTtoC( cfPMatrix MY, fPMatrix MX, ui ht, ui len );
void  __vf   MFbRows_FFTtoC( cfPMatrix MY, fPMatrix MX, ui ht, ui len, cfVector Buf );
void  __vf   MFbCols_FFTtoC( cfPMatrix MY, fPMatrix MX, ui ht, ui len, cfVector Buf );

void  __vf   MFlFFT( fPMatrix MY, fPMatrix MX, ui ht, ui len, int dir );
void  __vf   MFlFFTtoC( cfPMatrix MY, fPMatrix MX, ui ht, ui len );
void  __vf   MFlconvolve( fPMatrix MY, fPMatrix MFlt, fPMatrix MX,
                          fPMatrix MRsp, ui ht, ui len );
void  __vf   MFldeconvolve( fPMatrix MY, fPMatrix MFlt, fPMatrix MX,
                            fPMatrix MRsp, ui ht, ui len );
void  __vf   MFlfilter( fPMatrix MY, fPMatrix MX, fPMatrix MFlt,
                        ui ht, ui len );
void  __vf   MFlautocorr( fPMatrix MACorr, fPMatrix MX,
                          ui ht, ui len );
void  __vf   MFlxcorr( fPMatrix MXCorr, fPMatrix MX, fPMatrix MY,
                       ui ht, ui len );
void  __vf   MFlspectrum( fPMatrix MSpec, ui htSpec, ui lenSpec,
                          fPMatrix MX, ui htX, ui lenX,
                          fPMatrix MWin );
void  __vf   MFlRows_FFT( fPMatrix MY, fPMatrix MX, ui ht, ui len, int dir );
void  __vf   MFlCols_FFT( fPMatrix MY, fPMatrix MX, ui ht, ui len, int dir );
void  __vf   MFlRows_FFTtoC( cfPMatrix MY, fPMatrix MX, ui ht, ui len );
void  __vf   MFlCols_FFTtoC( cfPMatrix MY, fPMatrix MX, ui ht, ui len );

void  __vf   MFsFFT( fPMatrix MY, fPMatrix MX, ui ht, ui len, int dir );
void  __vf   MFsFFTtoC( cfPMatrix MY, fPMatrix MX, ui ht, ui len );
void  __vf   MFsconvolve( fPMatrix MY, fPMatrix MFlt, fPMatrix MX,
                          fPMatrix MRsp, ui ht, ui len );
void  __vf   MFsdeconvolve( fPMatrix MY, fPMatrix MFlt, fPMatrix MX,
                            fPMatrix MRsp, ui ht, ui len );
void  __vf   MFsfilter( fPMatrix MY, fPMatrix MX, fPMatrix MFlt,
                        ui ht, ui len );
void  __vf   MFsautocorr( fPMatrix MACorr, fPMatrix MX,
                          ui ht, ui len );
void  __vf   MFsxcorr( fPMatrix MXCorr, fPMatrix MX, fPMatrix MY,
                       ui ht, ui len );
void  __vf   MFsspectrum( fPMatrix MSpec, ui htSpec, ui lenSpec,
                          fPMatrix MX, ui htX, ui lenX,
                          fPMatrix MWin );
void  __vf   MFsRows_FFT( fPMatrix MY, fPMatrix MX, ui ht, ui len, int dir );
void  __vf   MFsCols_FFT( fPMatrix MY, fPMatrix MX, ui ht, ui len, int dir );
void  __vf   MFsRows_FFTtoC( cfPMatrix MY, fPMatrix MX, ui ht, ui len );
void  __vf   MFsCols_FFTtoC( cfPMatrix MY, fPMatrix MX, ui ht, ui len );

/*************************  Data Fitting    *******************************/

int  __vf VFpolyfitwW( fVector A, fPMatrix Covar, unsigned deg,
                        fVector X, fVector Y, fVector InvVar, ui sizex );
int  __vf VFlinfitwW( fVector A, fPMatrix Covar, iVector AStatus, unsigned npars,
                    fVector X, fVector Y, fVector InvVar, ui sizex,
                    void __vf funcs(fVector BasFuncs, float x, unsigned nfuncs) );
float __vf VFnonlinfitwW( fVector A, fPMatrix Covar, iVector AStatus, unsigned npars,
                    fVector X, fVector Y, fVector InvVar, ui sizex,
                    void __vf modelfunc(fVector YModel, fVector X, ui size),
                    void __vf derivatives(fVector dYdAi, fVector X, ui size, unsigned i),
					VF_NONLINFITWORKSPACE *FitWorkSpace, VF_NONLINFITOPTIONS *FitOpts );
int   __vf MFlinfit( fVector A, iVector AStatus, unsigned npars,
                    fVector X, fVector Y, fPMatrix MZ, ui htZ, ui lenZ,
                    void __vf funcs(fVector BasFuncs, float x, float y, unsigned nfuncs) );
float __vf MFnonlinfit( fVector A, iVector AStatus, unsigned npars,
                    fVector X, fVector Y, fPMatrix MZ, ui htZ, ui lenZ,
                    void __vf modelfunc(fMatrix MZModel, ui htZ, ui lenZ, fVector X, fVector Y ),
                    void __vf derivatives(fMatrix dZdAi, ui htZ, ui lenZ, fVector X, fVector Y, unsigned ipar),
					MF_NONLINFITWORKSPACE *FitWorkSpace, VF_NONLINFITOPTIONS *FitOpts );
int   __vf MFlinfitwW( fVector A, fPMatrix Covar, iVector AStatus, unsigned npars,
                      fVector X, fVector Y, fPMatrix MZ, fPMatrix MInvVar, ui htZ, ui lenZ,
                      void __vf funcs(fVector BasFuncs, float x, float y, unsigned nfuncs) );
float __vf MFnonlinfitwW( fVector A, fPMatrix Covar, iVector AStatus, unsigned npars,
                    fVector X, fVector Y, fPMatrix MZ, fPMatrix MInvVar, ui htZ, ui lenZ,
                    void __vf modelfunc(fMatrix MZModel, ui htZ, ui lenZ, fVector X, fVector Y ),
                    void __vf derivatives(fMatrix dZdAi, ui htZ, ui lenZ, fVector X, fVector Y, unsigned ipar),
					MF_NONLINFITWORKSPACE *FitWorkSpace, VF_NONLINFITOPTIONS *FitOpts );

int   __vf VFmultiLinfitwW( fVector A, fPMatrix Covar, iVector AStatus, unsigned ma,
                VF_EXPERIMENT _VFAR *ListOfExperiments, unsigned nexperiments,
                void __vf funcs(fVector BasFuncs, float x,
                              unsigned nfuncs, unsigned nexperiment) );
int   __vf MFmultiLinfitwW( fVector A, fPMatrix Covar,
                iVector AStatus, unsigned npars,
                MF_EXPERIMENT _VFAR *ListOfExperiments, unsigned nexperiments,
                void __vf funcs(fVector BasFuncs, float x, float y,
                              unsigned nfuncs, unsigned nexperiment) );
float __vf VFmultiNonlinfitwW( fVector A, fPMatrix Covar,
                iVector AStatus, unsigned npars,
                VF_EXPERIMENT _VFAR *ListOfExperiments, unsigned nexperiments,
                void __vf modelfunc(fVector YModel, fVector X, ui size, unsigned iexperiment),
                void __vf derivatives(fVector dYdAi, fVector X, ui size,
                                  unsigned ipar, unsigned iexperiment),
				VF_NONLINFITWORKSPACE *FitWorkSpace, VF_NONLINFITOPTIONS *FitOpts );
float __vf MFmultiNonlinfitwW( fVector A, fPMatrix Covar,
                iVector AStatus, unsigned npars,
                MF_EXPERIMENT _VFAR *ListOfExperiments, unsigned nexperiments,
                void __vf modelfunc(fMatrix MZModel, ui htZ, ui lenZ,
                                  fVector X, fVector Y, unsigned iexperiment ),
                void __vf derivatives(fMatrix dZdAi, ui htZ, ui lenZ,
                                    fVector X, fVector Y,
                                    unsigned ipar, unsigned iexperiment),
				MF_NONLINFITWORKSPACE *FitWorkSpace, VF_NONLINFITOPTIONS *FitOpts );

      /*************  Input and Output  ****************/

#define MFprint( MA, ht, len )  MFfprint( stdout, MA, ht, len, 80 )
void __vf MFfprint( FILE _VFAR *stream, fPMatrix MA, ui ht, ui len, unsigned linewidth );
void __vf MFcprint( fPMatrix MA, ui ht, ui len );
void __vf MFwrite( FILE _VFAR *stream, fPMatrix X, ui ht, ui len  );
#if !((defined __BORLANDC__) && (__BORLANDC__ < 0x710))
		/* modern compiler versions:  */
	void __vf MFread( fPMatrix X, ui ht, ui len, FILE _VFAR *stream );
#else /* older Borland compiler versions need separate implementation */
	void __vf MFread1( fPMatrix X, ui ht, ui len, FILE _VFAR *stream );
	#define MFread  MFread1
#endif
#define MFstore( str, MA, ht, len ) VF_store( str, MA, (len)*(ht) )
#define MFrecall( MA, ht, len, str) VF_recall( MA, (len)*(ht), str)

#ifdef __cplusplus
} // end of extern "C"

/* now C++ overloaded forms of nonlinfit functions both in complete and in simplified syntax: */
inline float __vf VF_nonlinfit( fVector A, iVector AStatus, unsigned npars,
                    fVector X, fVector Y, ui sizex,
                    void __vf modelfunc(fVector YModel, fVector XModel, ui size),
                    void __vf derivatives(fVector dYdAi,fVector X, ui size, unsigned iPar) )
{	return VF_nonlinfit( A, AStatus, npars, X, Y, sizex, modelfunc, derivatives, NULL, NULL );
}

inline float __vf VFnonlinfitwW( fVector A, fPMatrix Covar, iVector AStatus, unsigned npars,
                    fVector X, fVector Y, fVector InvVar, ui sizex,
                    void __vf modelfunc(fVector YModel, fVector X, ui size),
                    void __vf derivatives(fVector dYdAi, fVector X, ui size, unsigned i) )
{	return VFnonlinfitwW( A, Covar, AStatus, npars, X, Y, InvVar, sizex, 
						  modelfunc, derivatives, NULL, NULL );
}

inline float __vf VF_nonlinfitwW( fVector A, fMatrix Covar, iVector AStatus, unsigned npars,
                    fVector X, fVector Y, fVector InvVar, ui sizex,
                    void __vf modelfunc(fVector YModel, fVector X, ui size),
                    void __vf derivatives(fVector dYdAi, fVector X, ui size, unsigned i),
				VF_NONLINFITWORKSPACE *FitWorkSpace, VF_NONLINFITOPTIONS *FitOpts)
{	return VFnonlinfitwW( A, (Covar)[0], AStatus, npars, X, Y, InvVar, sizex, 
						  modelfunc, derivatives, FitWorkSpace, FitOpts );
}

inline float __vf VF_nonlinfitwW( fVector A, fMatrix Covar, iVector AStatus, unsigned npars,
                    fVector X, fVector Y, fVector InvVar, ui sizex,
                    void __vf modelfunc(fVector YModel, fVector X, ui size),
                    void __vf derivatives(fVector dYdAi, fVector X, ui size, unsigned i) )
{	return VFnonlinfitwW( A, (Covar)[0], AStatus, npars, X, Y, InvVar, sizex, 
						  modelfunc, derivatives, NULL, NULL );
}

inline float __vf MFnonlinfit( fVector A, iVector AStatus, unsigned npars,
                    fVector X, fVector Y, fPMatrix MZ, ui htZ, ui lenZ,
                    void __vf modelfunc(fMatrix MZModel, ui htZ, ui lenZ, fVector X, fVector Y ),
                    void __vf derivatives(fMatrix dZdAi, ui htZ, ui lenZ, fVector X, fVector Y, unsigned ipar) )
{	return MFnonlinfit( A, AStatus, npars, X, Y, MZ, htZ, lenZ, modelfunc, derivatives, NULL, NULL );
}

inline float __vf MF_nonlinfit( fVector A, iVector AStatus, unsigned npars,
                    fVector X, fVector Y, fMatrix MZ, ui htZ, ui lenZ,
                    void __vf modelfunc(fMatrix MZModel, ui htZ, ui lenZ, fVector X, fVector Y ),
                    void __vf derivatives(fMatrix dZdAi, ui htZ, ui lenZ, fVector X, fVector Y, unsigned ipar),
				MF_NONLINFITWORKSPACE *FitWorkSpace, VF_NONLINFITOPTIONS *FitOpts)
{	return MFnonlinfit( A, AStatus, npars, X, Y, (MZ)[0], htZ, lenZ, modelfunc, derivatives, FitWorkSpace, FitOpts );
}

inline float __vf MF_nonlinfit( fVector A, iVector AStatus, unsigned npars,
                    fVector X, fVector Y, fMatrix MZ, ui htZ, ui lenZ,
                    void __vf modelfunc(fMatrix MZModel, ui htZ, ui lenZ, fVector X, fVector Y ),
                    void __vf derivatives(fMatrix dZdAi, ui htZ, ui lenZ, fVector X, fVector Y, unsigned ipar) )
{	return MFnonlinfit( A, AStatus, npars, X, Y, (MZ)[0], htZ, lenZ, modelfunc, derivatives, NULL, NULL );
}

inline float __vf MFnonlinfitwW( fVector A, fPMatrix Covar, iVector AStatus, unsigned npars,
                    fVector X, fVector Y, fPMatrix MZ, fPMatrix MInvVar, ui htZ, ui lenZ,
                    void __vf modelfunc(fMatrix MZModel, ui htZ, ui lenZ, fVector X, fVector Y ),
                    void __vf derivatives(fMatrix dZdAi, ui htZ, ui lenZ, fVector X, fVector Y, unsigned ipar) )
{	return MFnonlinfitwW( A, Covar, AStatus, npars, X, Y, MZ, MInvVar, htZ, lenZ, 
						  modelfunc, derivatives, NULL, NULL );
}

inline float __vf MF_nonlinfitwW( fVector A, fMatrix Covar, iVector AStatus, unsigned npars,
                    fVector X, fVector Y, fMatrix MZ, fMatrix MInvVar, ui htZ, ui lenZ,
                    void __vf modelfunc(fMatrix MZModel, ui htZ, ui lenZ, fVector X, fVector Y ),
                    void __vf derivatives(fMatrix dZdAi, ui htZ, ui lenZ, fVector X, fVector Y, unsigned ipar),
				MF_NONLINFITWORKSPACE *FitWorkSpace, VF_NONLINFITOPTIONS *FitOpts)
{	return MFnonlinfitwW( A, (Covar)[0], AStatus, npars, X, Y, (MZ)[0], (MInvVar)[0], htZ, lenZ, 
						  modelfunc, derivatives, FitWorkSpace, FitOpts );
}

inline float __vf MF_nonlinfitwW( fVector A, fMatrix Covar, iVector AStatus, unsigned npars,
                    fVector X, fVector Y, fMatrix MZ, fMatrix MInvVar, ui htZ, ui lenZ,
                    void __vf modelfunc(fMatrix MZModel, ui htZ, ui lenZ, fVector X, fVector Y ),
                    void __vf derivatives(fMatrix dZdAi, ui htZ, ui lenZ, fVector X, fVector Y, unsigned ipar) )
{	return MFnonlinfitwW( A, (Covar)[0], AStatus, npars, X, Y, (MZ)[0], (MInvVar)[0], htZ, lenZ, 
						  modelfunc, derivatives, NULL, NULL );
}

inline float __vf VF_multiNonlinfit( fVector A, iVector AStatus, unsigned npars,
                VF_EXPERIMENT _VFAR *ListOfExperiments, unsigned nexperiments,
                void __vf modelfunc(fVector YModel, fVector XModel,
                                  ui size, unsigned iexperiment),
                void __vf derivatives(fVector dYdAi,fVector X, ui size,
                                  unsigned ipar, unsigned iexperiment) )
{	return VF_multiNonlinfit( A, AStatus, npars, ListOfExperiments, nexperiments,
							 modelfunc, derivatives, NULL, NULL );
}

inline float __vf VFmultiNonlinfitwW( fVector A, fPMatrix Covar,
                iVector AStatus, unsigned npars,
                VF_EXPERIMENT _VFAR *ListOfExperiments, unsigned nexperiments,
                void __vf modelfunc(fVector YModel, fVector X, ui size, unsigned iexperiment),
                void __vf derivatives(fVector dYdAi, fVector X, ui size,
                                  unsigned ipar, unsigned iexperiment) )
{	return VFmultiNonlinfitwW( A, Covar, AStatus, npars, ListOfExperiments, nexperiments,
							 modelfunc, derivatives, NULL, NULL );
}

inline float __vf VF_multiNonlinfitwW( fVector A, fMatrix Covar,
                iVector AStatus, unsigned npars,
                VF_EXPERIMENT _VFAR *ListOfExperiments, unsigned nexperiments,
                void __vf modelfunc(fVector YModel, fVector X, ui size, unsigned iexperiment),
                void __vf derivatives(fVector dYdAi, fVector X, ui size,
                                  unsigned ipar, unsigned iexperiment),
				VF_NONLINFITWORKSPACE *FitWorkSpace, VF_NONLINFITOPTIONS *FitOpts)
{	return VFmultiNonlinfitwW( A, (Covar)[0], AStatus, npars, ListOfExperiments, nexperiments,
							 modelfunc, derivatives, FitWorkSpace, FitOpts );
}

inline float __vf VF_multiNonlinfitwW( fVector A, fMatrix Covar,
                iVector AStatus, unsigned npars,
                VF_EXPERIMENT _VFAR *ListOfExperiments, unsigned nexperiments,
                void __vf modelfunc(fVector YModel, fVector X, ui size, unsigned iexperiment),
                void __vf derivatives(fVector dYdAi, fVector X, ui size,
                                  unsigned ipar, unsigned iexperiment) )
{	return VFmultiNonlinfitwW( A, (Covar)[0], AStatus, npars, ListOfExperiments, nexperiments,
							 modelfunc, derivatives, NULL, NULL );
}

inline float __vf MF_multiNonlinfit( fVector A, iVector AStatus, unsigned npars,
                MF_EXPERIMENT _VFAR *ListOfExperiments, unsigned nexperiments,
                void __vf modelfunc(fMatrix MZModel, ui htZ, ui lenZ,
                                  fVector X, fVector Y, unsigned iexperiment),
                void __vf derivatives(fMatrix dZdAi, ui htZ, ui lenZ,
                                    fVector X, fVector Y, unsigned ipar,
                                    unsigned iexperiment) )
{	return MF_multiNonlinfit( A, AStatus, npars, ListOfExperiments, nexperiments,
							 modelfunc, derivatives, NULL, NULL );
}

inline float __vf MFmultiNonlinfitwW( fVector A, fPMatrix Covar,
                iVector AStatus, unsigned npars,
                MF_EXPERIMENT _VFAR *ListOfExperiments, unsigned nexperiments,
                void __vf modelfunc(fMatrix MZModel, ui htZ, ui lenZ,
                                  fVector X, fVector Y, unsigned iexperiment ),
                void __vf derivatives(fMatrix dZdAi, ui htZ, ui lenZ,
                                    fVector X, fVector Y,
                                    unsigned ipar, unsigned iexperiment) )
{	return MFmultiNonlinfitwW( A, Covar, AStatus, npars, ListOfExperiments, nexperiments,
							 modelfunc, derivatives, NULL, NULL );
}

inline float __vf MF_multiNonlinfitwW( fVector A, fMatrix Covar,
                iVector AStatus, unsigned npars,
                MF_EXPERIMENT _VFAR *ListOfExperiments, unsigned nexperiments,
                void __vf modelfunc(fMatrix MZModel, ui htZ, ui lenZ,
                                  fVector X, fVector Y, unsigned iexperiment ),
                void __vf derivatives(fMatrix dZdAi, ui htZ, ui lenZ,
                                    fVector X, fVector Y,
                                    unsigned ipar, unsigned iexperiment),
				MF_NONLINFITWORKSPACE *FitWorkSpace, VF_NONLINFITOPTIONS *FitOpts)
{	return MFmultiNonlinfitwW( A, (Covar)[0], AStatus, npars, ListOfExperiments, nexperiments,
							 modelfunc, derivatives, FitWorkSpace, FitOpts );
}

inline float __vf MF_multiNonlinfitwW( fVector A, fMatrix Covar,
                iVector AStatus, unsigned npars,
                MF_EXPERIMENT _VFAR *ListOfExperiments, unsigned nexperiments,
                void __vf modelfunc(fMatrix MZModel, ui htZ, ui lenZ,
                                  fVector X, fVector Y, unsigned iexperiment ),
                void __vf derivatives(fMatrix dZdAi, ui htZ, ui lenZ,
                                    fVector X, fVector Y,
                                    unsigned ipar, unsigned iexperiment) )
{	return MFmultiNonlinfitwW( A, (Covar)[0], AStatus, npars, ListOfExperiments, nexperiments,
							 modelfunc, derivatives, NULL, NULL );
}
#endif  /* __cplusplus */

#endif  /*  __MFSTD_H  */
