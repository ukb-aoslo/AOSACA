/*  MDstd.h

  matrix management functions:
  manipulations on matrices of data type "double"
  (double-precision real numbers)

  Copyright (c) 1996-2017 by OptiCode - Dr. Martin Sander Software Dev.
  All Rights Reserved.
*/

#if !defined( __MDSTD_H )
#define __MDSTD_H
#if !defined( __MATLIB_H )
#include <MatLib.h>
#endif
#if !defined( __VDSTD_H )
#include <VDstd.h>
#endif
#if !defined( __VDMATH_H )
#include <VDmath.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif

/*************   Dynamic Generation of Matrices   ************************/

dMatrix __vf  MD_matrix(  ui ht, ui len );
dMatrix __vf  MD_matrix0( ui ht, ui len );
#if defined (_MSC_VER) && defined (_DEBUG)
    dMatrix __vf  MD_matrix_dbg(  ui ht, ui len );
    dMatrix __vf  MD_matrix0_dbg( ui ht, ui len );
    #if defined (_INC_CRTDBG) && defined (_CRTDBG_MAP_ALLOC) 
	    /* Automatic mapping for memory-leak detection by CRT debugging switched on? */ 
        #define MD_matrix  MD_matrix_dbg
        #define MD_matrix0 MD_matrix0_dbg
    #endif
#else
    #define MD_matrix_dbg  MD_matrix
    #define MD_matrix0_dbg MD_matrix0
#endif
    /*  notice that, in the memory model HUGE,
        neither len nor ht may exceed 4095            */

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

#define MD_getElement( y, MA, ht, len, m, n ) MDgetElement( y, (MA)[0], ht, len, m, n )
#define MD_setElement( MA, ht, len, m, n, C ) MDsetElement( (MA)[0], ht, len, m, n, C )
#define MD_Pelement( MA, ht, len, m, n ) MDPelement( (MA)[0], ht, len, m, n )
                     /* returns a pointer to MA[m][n]. */
#define MD_element( MA, ht, len, m, n ) *MDPelement( (MA)[0], ht, len, m, n )
                     /* dereferenced pointer */

 /****************  Initialization  ***************************************

    To initialize all elements of a matrix with the same value,
    or to perform arithmetic operations on all elements simultaneously,
    refer to the functions of VectorLib, declared in <VDstd.h>, <VDmath.h>.
    In order to use the VectorLib functions, utilize the feature that
    the whole matrix occupies one contiguous area in memory: pass the
    address of the first row to the desired vector function, the size
    of the "vector" being ht * len.
    For example, initialize all elements of the matrix MA with 1.0
    (this is *NOT* the identity matrix)  by calling
        VD_equ1( (MA)[0], ht * len );
*/

#define MD_equ0( MA, ht, len )            VD_equ0( (MA)[0], (ht)*(len) )
#define MD_equ1( MA, len )                MDequ1( (MA)[0], len ) /* identity matrix */
#define MD_equm1( MA, len )               MDequm1( (MA)[0], len ) /* neg. identity matrix */
#define MD_randomLC( MA, ht, len, seed, Min, Max, state ) \
                                          VD_randomLC( (MA)[0], (ht)*(len), seed, Min, Max, state )
#define MD_random( MA, ht, len, seed, Min, Max ) \
                                          VD_random( (MA)[0], (ht)*(len), seed, Min, Max )
#define MD_outerprod( MA, X, Y, ht, len ) MDouterprod( (MA)[0], X, Y, ht, len )
                       /* sizX=ht, sizY=len */
#define MD_Row_equ0( MA, ht, len, iRow )  MDRow_equ0( (MA)[0], ht, len, iRow )
#define MD_Col_equ0( MA, ht, len, iCol )  MDCol_equ0( (MA)[0], ht, len, iCol )
#define MD_Dia_equ0( MA, len )            MDDia_equ0( (MA)[0], len )
#define MD_Row_equC( MA, ht, len, iRow, C ) \
                                        MDRow_equC( (MA)[0], ht, len, iRow, C )
#define MD_Col_equC( MA, ht, len, iCol, C ) \
                                        MDCol_equC( (MA)[0], ht, len, iCol, C )
#define MD_Dia_equC( MA, len, C )       MDDia_equC( (MA)[0], len, C )

#define MD_Row_equV( MA, ht, len, iRow, X ) \
                                        MDRow_equV( (MA)[0], ht, len, iRow, X )
#define MD_Col_equV( MA, ht, len, iCol, X ) \
                                        MDCol_equV( (MA)[0], ht, len, iCol, X )
#define MD_Dia_equV( MA, len, X )       MDDia_equV( (MA)[0], len, X )

#define MD_Trd_equM( MA, MTrd, len )    MDTrd_equM( (MA)[0], (MTrd)[0], len )
#define MD_Trd_extract( MTrd, MA, len ) MDTrd_extract( (MTrd)[0], (MA)[0], len )

#define MD_equM( MB, MA, ht, len )  VD_equV( (MB)[0], (MA)[0], (ht)*(len) )
#define MD_neg( MB, MA, ht, len )   VD_neg( (MB)[0], (MA)[0], (ht)*(len) )

#define MD_UequL( MA, len ) MDUequL( (MA)[0], len )
#define MD_LequU( MA, len ) MDLequU( (MA)[0], len )
         /* copy lower-diagonal elements into upper-diagonal
           (or vice versa) by index-reflection, so as to
           get a symmetric matrix    */

            /* data-type conversions:  */
#define M_DtoF( MF, MD, ht, len ) V_DtoF( (MF)[0], (MD)[0], (ht)*(len) )
#define M_FtoD( MD, MF, ht, len ) V_FtoD( (MD)[0], (MF)[0], (ht)*(len) )
#define M_EtoD( MD, ME, ht, len ) V_EtoD( (MD)[0], (ME)[0], (ht)*(len) )
#define M_DtoE( ME, MD, ht, len ) V_DtoE( (ME)[0], (MD)[0], (ht)*(len) )

            /* suitable windows for MF_spectrum: */
#define MD_Hann( MA, ht, len )  MDHann( (MA)[0], ht, len )
#define MD_Hanning( MA, ht, len )  MDHann( (MA)[0], ht, len )  /* erroneous name for Hann */
#define MD_Parzen( MA, ht, len )   MDParzen( (MA)[0], ht, len )
#define MD_Welch( MA, ht, len )    MDWelch( (MA)[0], ht, len )

/********  Extracting a submatrix and copying a submatrix back  *********/

#define MD_submatrix( MSub, subHt, subLen, \
                      MSrce, srceHt, srceLen, \
                      firstRowInCol, sampInCol, firstColInRow, sampInRow ) \
               MDsubmatrix(  (MSub)[0], subHt, subLen, \
                             (MSrce)[0], srceHt, srceLen, \
                             firstRowInCol, sampInCol, firstColInRow, sampInRow )

#define MD_submatrix_equM( MDest, destHt, destLen, \
                           firstRowInCol, sampInCol, firstColInRow, sampInRow, \
                           MSrce, srceHt, srceLen ) \
               MDsubmatrix_equM(  (MDest)[0], destHt, destLen, \
                             firstRowInCol, sampInCol, firstColInRow, sampInRow, \
                             (MSrce)[0], srceHt, srceLen )

#define MD_equMblock( MSub, subHt, subLen, \
                      MSrce, srceHt, srceLen, \
                      firstRowInCol, firstColInRow ) \
               MDequMblock(  (MSub)[0], subHt, subLen, \
                             (MSrce)[0], srceHt, srceLen, \
                             firstRowInCol, firstColInRow )

#define MD_block_equM( MDest, destHt, destLen, \
                       firstRowInCol, firstColInRow, \
                       MSrce, srceHt, srceLen ) \
               MDblock_equM( (MDest)[0], destHt, destLen, \
                             firstRowInCol, firstColInRow, \
                             (MSrce)[0], srceHt, srceLen )

#define MD_equMblockT( MSub, subHt, subLen, \
                      MSrce, srceHt, srceLen, \
                      firstRowInCol, firstColInRow ) \
               MDequMblockT(  (MSub)[0], subHt, subLen, \
                             (MSrce)[0], srceHt, srceLen, \
                             firstRowInCol, firstColInRow )

#define MD_block_equMT( MDest, destHt, destLen, \
                       firstRowInCol, firstColInRow, \
                       MSrce, srceHt, srceLen ) \
               MDblock_equMT( (MDest)[0], destHt, destLen, \
                             firstRowInCol, firstColInRow, \
                             (MSrce)[0], srceHt, srceLen )

/*****   Extracting a single row or a single column or the diagonal  ******
 *       and storing it into a vector                                     */

#define MD_Row_extract( Y, MA, ht, len, iRow ) \
                                     MDRow_extract( Y, (MA)[0], ht, len, iRow )
#define MD_Col_extract( Y, MA, ht, len, iCol ) \
                                     MDCol_extract( Y, (MA)[0], ht, len, iCol )
#define MD_Dia_extract( Y, MA, len ) MDDia_extract( Y, (MA)[0], len )

/**************  Deleting or inserting a row or a column   ***************/

#define MD_Row_delete( MB, MA, htA, lenA, iRow ) \
                           MDRow_delete( (MB)[0], (MA)[0], htA, lenA, iRow )
#define MD_Col_delete( MB, MA, htA, lenA, iCol ) \
                           MDCol_delete( (MB)[0], (MA)[0], htA, lenA, iCol )
#define MD_Row_insert( MB, MA, htB, lenB, iRow, X ) \
                           MDRow_insert( (MB)[0], (MA)[0], htB, lenB, iRow, X )
#define MD_Col_insert( MB, MA, htB, lenB, iCol, X ) \
                           MDCol_insert( (MB)[0], (MA)[0], htB, lenB, iCol, X )


/*****************    Basic arithmetic operations *********************
                      performed on one single row,
                      or one single column of any matrix,
                      or on the diagonal of a square matrix

    Note: In contrast to the analogous VectorLib functions, the operations
    are performed in-place, i.e. the input matrix itself is changed  */

#define MD_Row_neg( MA, ht, len, iRow ) MDRow_neg( (MA)[0], ht, len, iRow )
#define MD_Col_neg( MA, ht, len, iCol ) MDCol_neg( (MA)[0], ht, len, iCol )

#define MD_Row_addC( MA, ht, len, iRow, C ) \
                                     MDRow_addC( (MA)[0], ht, len, iRow, C )
#define MD_Col_addC( MA, ht, len, iCol, C ) \
                                     MDCol_addC( (MA)[0], ht, len, iCol, C )
#define MD_Dia_addC( MA, len, C )    MDDia_addC( (MA)[0], len, C )

#define MD_Row_addV( MA, ht, len, iRow, X ) \
                                     MDRow_addV( (MA)[0], ht, len, iRow, X )
#define MD_Col_addV( MA, ht, len, iCol, X ) \
                                     MDCol_addV( (MA)[0], ht, len, iCol, X )
#define MD_Dia_addV( MA, len, X )    MDDia_addV( (MA)[0], len, X )

#define MD_Row_subC( MA, ht, len, iRow, C ) \
                                     MDRow_subC( (MA)[0], ht, len, iRow, C )
#define MD_Col_subC( MA, ht, len, iCol, C ) \
                                     MDCol_subC( (MA)[0], ht, len, iCol, C )
#define MD_Dia_subC( MA, len, C )    MDDia_subC( (MA)[0], len, C )

#define MD_Row_subV( MA, ht, len, iRow, X ) \
                                     MDRow_subV( (MA)[0], ht, len, iRow, X )
#define MD_Col_subV( MA, ht, len, iCol, X ) \
                                     MDCol_subV( (MA)[0], ht, len, iCol, X )
#define MD_Dia_subV( MA, len, X )    MDDia_subV( (MA)[0], len, X )

#define MD_Row_subrC( MA, ht, len, iRow, C ) \
                                     MDRow_subrC( (MA)[0], ht, len, iRow, C )
#define MD_Col_subrC( MA, ht, len, iCol, C ) \
                                     MDCol_subrC( (MA)[0], ht, len, iCol, C )
#define MD_Dia_subrC( MA, len, C )   MDDia_subrC( (MA)[0], len, C )

#define MD_Row_subrV( MA, ht, len, iRow, X ) \
                                     MDRow_subrV( (MA)[0], ht, len, iRow, X )
#define MD_Col_subrV( MA, ht, len, iCol, X ) \
                                     MDCol_subrV( (MA)[0], ht, len, iCol, X )
#define MD_Dia_subrV( MA, len, X )   MDDia_subrV( (MA)[0], len, X )

#define MD_Row_mulC( MA, ht, len, iRow, C ) \
                                     MDRow_mulC( (MA)[0], ht, len, iRow, C )
#define MD_Col_mulC( MA, ht, len, iCol, C ) \
                                     MDCol_mulC( (MA)[0], ht, len, iCol, C )
#define MD_Dia_mulC( MA, len, C )    MDDia_mulC( (MA)[0], len, C )

#define MD_Row_mulV( MA, ht, len, iRow, X ) \
                                     MDRow_mulV( (MA)[0], ht, len, iRow, X )
#define MD_Col_mulV( MA, ht, len, iCol, X ) \
                                     MDCol_mulV( (MA)[0], ht, len, iCol, X )
#define MD_Dia_mulV( MA, len, X )    MDDia_mulV( (MA)[0], len, X )

#define MD_Row_divC( MA, ht, len, iRow, C ) \
                                     MDRow_divC( (MA)[0], ht, len, iRow, C )
#define MD_Col_divC( MA, ht, len, iCol, C ) \
                                     MDCol_divC( (MA)[0], ht, len, iCol, C )
#define MD_Dia_divC( MA, len, C )    MDDia_divC( (MA)[0], len, C )

#define MD_Row_divV( MA, ht, len, iRow, X ) \
                                      MDRow_divV( (MA)[0], ht, len, iRow, X )
#define MD_Col_divV( MA, ht, len, iCol, X ) \
                                      MDCol_divV( (MA)[0], ht, len, iCol, X )
#define MD_Dia_divV( MA, len, X )     MDDia_divV( (MA)[0], len, X )

#define MD_Row_divrC( MA, ht, len, iRow, C ) \
                                      MDRow_divrC( (MA)[0], ht, len, iRow, C )
#define MD_Col_divrC( MA, ht, len, iCol, C ) \
                                      MDCol_divrC( (MA)[0], ht, len, iCol, C )
#define MD_Dia_divrC( MA, len, C )    MDDia_divrC( (MA)[0], len, C )

#define MD_Row_divrV( MA, ht, len, iRow, X ) \
                                      MDRow_divrV( (MA)[0], ht, len, iRow, X )
#define MD_Col_divrV( MA, ht, len, iCol, X ) \
                                      MDCol_divrV( (MA)[0], ht, len, iCol, X )
#define MD_Dia_divrV( MA, len, X )    MDDia_divrV( (MA)[0], len, X )


/******  One-dimensional vector operations **********************
         performed along all rows or all columns simultaneously,
         or along the diagonal of a square matrix                */

#define MD_Rows_max( Y, MA, ht, len )     MDRows_max( Y, (MA)[0], ht, len )
#define MD_Cols_max( Y, MA, ht, len )     MDCols_max( Y, (MA)[0], ht, len )
#define MD_Dia_max(  MA, len )            MDDia_max(  (MA)[0], len )
#define MD_Rows_min( Y, MA, ht, len )     MDRows_min( Y, (MA)[0], ht, len )
#define MD_Cols_min( Y, MA, ht, len )     MDCols_min( Y, (MA)[0], ht, len )
#define MD_Dia_min(  MA, len )            MDDia_min(  (MA)[0], len )

#define MD_Rows_absmax( Y, MA, ht, len )  MDRows_absmax( Y, (MA)[0], ht, len )
#define MD_Cols_absmax( Y, MA, ht, len )  MDCols_absmax( Y, (MA)[0], ht, len )
#define MD_Dia_absmax(  MA, len )         MDDia_absmax(  (MA)[0], len )
#define MD_Rows_absmin( Y, MA, ht, len )  MDRows_absmin( Y, (MA)[0], ht, len )
#define MD_Cols_absmin( Y, MA, ht, len )  MDCols_absmin( Y, (MA)[0], ht, len )
#define MD_Dia_absmin(  MA, len )         MDDia_absmin(  (MA)[0], len )

#define MD_Rows_sum( Y, MA, ht, len )     MDRows_sum( Y, (MA)[0], ht, len )
#define MD_Cols_sum( Y, MA, ht, len )     MDCols_sum( Y, (MA)[0], ht, len )
#define MD_Dia_sum(  MA, len )            MDDia_sum(  (MA)[0], len )
#define MD_Rows_ssq( Y, MA, ht, len )     MDRows_ssq( Y, (MA)[0], ht, len )
#define MD_Cols_ssq( Y, MA, ht, len )     MDCols_ssq( Y, (MA)[0], ht, len )
#define MD_Dia_ssq(  MA, len )            MDDia_ssq(  (MA)[0], len )
#define MD_Rows_prod( Y, MA, ht, len )    MDRows_prod( Y, (MA)[0], ht, len )
#define MD_Cols_prod( Y, MA, ht, len )    MDCols_prod( Y, (MA)[0], ht, len )
#define MD_Dia_prod(  MA, len )           MDDia_prod(  (MA)[0], len )

#define MD_Rows_runsum( MA, ht, len )     MDRows_runsum( (MA)[0], ht, len )
#define MD_Cols_runsum( MA, ht, len )     MDCols_runsum( (MA)[0], ht, len )
#define MD_Rows_runprod( MA, ht, len )    MDRows_runprod( (MA)[0], ht, len )
#define MD_Cols_runprod( MA, ht, len )    MDCols_runprod( (MA)[0], ht, len )

#define MD_Rows_rotate( MA, ht, len, pos) MDRows_rotate( (MA)[0], ht, len, pos )
#define MD_Cols_rotate( MA, ht, len, pos) MDCols_rotate( (MA)[0], ht, len, pos )
#define MD_Rows_rotate_buf( MA, ht, len, pos, MBuf) MDRows_rotate_buf( (MA)[0], ht, len, pos, (MBuf)[0] )
#define MD_Cols_rotate_buf( MA, ht, len, pos, MBuf) MDCols_rotate_buf( (MA)[0], ht, len, pos, (MBuf)[0] )
#define MD_Rows_reflect( MA, ht, len )    MDRows_reflect( (MA)[0], ht, len )
#define MD_Cols_reflect( MA, ht, len )    MDCols_reflect( (MA)[0], ht, len )
#define MD_Rows_rev( MA, ht, len)         MDRows_rev( (MA)[0], ht, len )
#define MD_Cols_rev( MA, ht, len)         MDCols_rev( (MA)[0], ht, len )

#define MD_Rows_distribution( MAbund, Limits, nBins, MX, htX, lenX, mode ) MDRows_distribution( (MAbund)[0], Limits, nBins, (MX)[0], htX, lenX, mode )
#define MD_Cols_distribution( MAbund, Limits, nBins, MX, htX, lenX, mode ) MDCols_distribution( (MAbund)[0], Limits, nBins, (MX)[0], htX, lenX, mode )

/********  Operations involving two rows or two colums of one matrix  *****/

#define MD_Rows_exchange( MA, ht, len, row1, row2 ) \
                             MDRows_exchange( (MA)[0], ht, len, row1, row2 )
#define MD_Cols_exchange( MA, ht, len, col1, col2 ) \
                             MDCols_exchange( (MA)[0], ht, len, col1, col2 )

#define MD_Rows_add( MA, ht, len, destRow, srceRow ) \
                             MDRows_add( (MA)[0], ht, len, destRow, srceRow )
#define MD_Cols_add( MA, ht, len, destCol, srceCol ) \
                             MDCols_add( (MA)[0], ht, len, destCol, srceCol )
                         /* dest[i] += source[i]  */

#define MD_Rows_sub( MA, ht, len, destRow, srceRow ) \
                             MDRows_sub( (MA)[0], ht, len, destRow, srceRow )
#define MD_Cols_sub( MA, ht, len, destCol, srceCol ) \
                             MDCols_sub( (MA)[0], ht, len, destCol, srceCol )
                         /* dest[i] -= source[i]  */

#define MD_Rows_Cadd( MA, ht, len, destRow, srceRow, C ) \
                          MDRows_Cadd( (MA)[0], ht, len, destRow, srceRow, C )
#define MD_Cols_Cadd( MA, ht, len, destCol, srceCol, C ) \
                          MDCols_Cadd( (MA)[0], ht, len, destCol, srceCol, C )
                         /* dest[i] += C * source[i]  */

#define MD_Rows_lincomb( MA, ht, len, destRow, destC, srceRow, srceC ) \
            MDRows_lincomb( (MA)[0], ht, len, destRow, destC, srceRow, srceC )
#define MD_Cols_lincomb( MA, ht, len, destCol, destC, srceCol, srceC ) \
            MDCols_lincomb( (MA)[0], ht, len, destCol, destC, srceCol, srceC )
  /*  linear combination: dest[i] = destC * dest[i] + sourceC * source[i] */


/*********************  Center of gravity *****************************/
#define MD_centerOfGravityInd( MA, ht, len ) \
            MDcenterOfGravityInd( (MA)[0], ht, len )
#define MD_centerOfGravityV( X, Y, MA, ht, len ) \
            MDcenterOfGravityV( X, Y, (MA)[0], ht, len )

/*************** Transposing and rotating a matrix **********************/

#define MD_transpose( MTr, MA, htTr, lenTr ) \
             MDtranspose( (MTr)[0], (MA)[0], htTr, lenTr )
       /*  dimensions htTr, lenTr are those of the transposed matrix,
           not of the original!                */
#define MD_rotate90( MRot, MA, htRot, lenRot ) \
             MDrotate90( (MRot)[0], (MA)[0], htRot, lenRot )
#define MD_rotate180( MRot, MA, htRot, lenRot ) \
             VD_rev( (MRot)[0], (MA)[0], (htRot)*(lenRot) )
#define MD_rotate270( MRot, MA, htRot, lenRot ) \
             MDrotate270( (MRot)[0], (MA)[0], htRot, lenRot )

/********************** Interpolation of Matrix elements **************/

#define MD_polyinterpol( MZ, X, Y, ht, len, XTab, YTab, MZTab, httab, lentab, degX, degY ) \
             MDpolyinterpol( (MZ)[0], X, Y, ht, len, XTab, YTab, (MZTab)[0], \
                             httab, lentab, degX, degY )
#define MD_ratinterpol( MZ, X, Y, ht, len, XTab, YTab, MZTab, httab, lentab, degX, degY ) \
             MDratinterpol( (MZ)[0], X, Y, ht, len, XTab, YTab, (MZTab)[0], \
                             httab, lentab, degX, degY )
#define MD_natCubSplineInterpol( MZ, X, Y, ht, len, XTab, YTab, MZTab, httab, lentab ) \
             MDnatCubSplineInterpol( (MZ)[0], X, Y, ht, len, XTab, YTab, (MZTab)[0], \
                             httab, lentab )


/************************ Matrix Arithmetics *************************/

#define MD_addM( MC, MA, MB, htA, lenA ) \
                 VD_addV( (MC)[0], (MA)[0], (MB)[0], (htA)*(lenA) )
#define MD_addMT( MC, MA, MB, htA, lenA ) \
                 MDaddMT( (MC)[0], (MA)[0], (MB)[0], htA, lenA )
#define MD_subM( MC, MA, MB, htA, lenA ) \
                 VD_subV( (MC)[0], (MA)[0], (MB)[0], (htA)*(lenA) )
#define MD_subMT( MC, MA, MB, htA, lenA ) \
                 MDsubMT( (MC)[0], (MA)[0], (MB)[0], htA, lenA )
#define MD_subrMT( MC, MA, MB, htA, lenA ) \
                 MDsubrMT( (MC)[0], (MA)[0], (MB)[0], htA, lenA )
#define MD_mulC( MB, MA, htA, lenA, C ) \
                 VD_mulC( (MB)[0], (MA)[0], (htA)*(lenA), C )
#define MD_divC( MB, MA, htA, lenA, C ) \
                 VD_divC( (MB)[0], (MA)[0], (htA)*(lenA), C )
#define MDs_addM( MC, MA, MB, htA, lenA, C ) \
                 VDs_addV( (MC)[0], (MA)[0], (MB)[0], (htA)*(lenA), C )
#define MDs_addMT( MC, MA, MB, htA, lenA, C ) \
                 MDsaddMT( (MC)[0], (MA)[0], (MB)[0], htA, lenA, C )
#define MDs_subM( MC, MA, MB, htA, lenA, C ) \
                 VDs_subV( (MC)[0], (MA)[0], (MB)[0], (htA)*(lenA), C )
#define MDs_subMT( MC, MA, MB, htA, lenA, C ) \
                 MDssubMT( (MC)[0], (MA)[0], (MB)[0], htA, lenA, C )
#define MDs_subrMT( MC, MA, MB, htA, lenA, C ) \
                 MDssubrMT( (MC)[0], (MA)[0], (MB)[0], htA, lenA, C )
#define MD_lincomb( MC, MA, MB, htA, lenA, CA, CB ) \
                 VD_lincomb( (MC)[0], (MA)[0], (MB)[0], (htA)*(lenA), CA, CB )

#define MD_mulV( Y, MA, X, htA, lenA ) \
                    MDmulV( Y, (MA)[0], X, htA, lenA )
                          /*  Y = MA * X.  sizX=lenA, sizY=htA
                              both X and Y are column-vectors    */
#define MD_TmulV( Y, MA, X, htA, lenA ) \
                    MDTmulV( Y, (MA)[0], X, htA, lenA )
                          /*  Y = MAT * X.  sizX=htA, sizY=lenA
                              both X and Y are column-vectors    */
#define VD_mulM( Y, X, MA, htA, lenA ) \
                    VDmulM( Y, X, (MA)[0], htA, lenA )
                         /*  Y = X * MA.  sizX=htA, sizY=lenA
                             both X and Y are row-vectors.
                             Mind the prefix: VD_ (not MD_)    */
#define VD_mulMT( Y, X, MA, htA, lenA ) \
                    VDmulMT( Y, X, (MA)[0], htA, lenA )
                         /*  Y = X * MAT.  sizX=lenA, sizY=htA
                             both X and Y are row-vectors.   */
#define MD_mulM( MC, MA, MB, htA, lenA, lenB ) \
                    MDmulM( (MC)[0], (MA)[0], (MB)[0], htA, lenA, lenB )
                         /*  MC = MA * MB.  htB=lenA, htC=htA, lenC=lenB */
#define MD_mulMT( MC, MA, MB, htA, lenA, htB ) \
                    MDmulMT( (MC)[0], (MA)[0], (MB)[0], htA, lenA, htB )
                         /*  MC = MA * MBT.  lenB=lenA, htC=htA, lenC=htB */
#define MD_TmulM( MC, MA, MB, htA, lenA, lenB ) \
                    MDTmulM( (MC)[0], (MA)[0], (MB)[0], htA, lenA, lenB )
                         /*  MC = MAT * MB.  htB=htA, htC=lenA, lenC=lenB */
#define MD_TmulMT( MC, MA, MB, htA, lenA, htB ) \
                    MDTmulMT( (MC)[0], (MA)[0], (MB)[0], htA, lenA, htB )
                         /*  MC = MAT * MBT.  lenB=htA, htC=lenA, lenC=htB */
#define MDdia_mulM(  MC, MADia, MB, htB, lenB )  MDdiamulM(  (MC)[0], MADia, (MB)[0], htB, lenB )
#define MDdia_mulMT( MC, MADia, MB, htB, lenB )  MDdiamulMT( (MC)[0], MADia, (MB)[0], htB, lenB )
#define MD_mulMdia(  MC, MA, MBDia, htA, lenA )  MDmulMdia(  (MC)[0], (MA)[0], MBDia, htA, lenA )
#define MD_TmulMdia( MC, MA, MBDia, htA, lenA )  MDTmulMdia( (MC)[0], (MA)[0], MBDia, htA, lenA )


/*************************  Linear Algebra    *****************************/

   /*  The standard treatment of linear systems is based
       on LUD (matrix decomposition into Upper-triangular
       and Lower-triangular components). The result of the
       decomposition step is used for further operations.  */

#define MD_LUdecompose( MLU, Ind, MA, len ) \
                    MDLUdecompose( (MLU)[0], Ind, (MA)[0], len )
            /* returns "permut" = ñ1 which is needed for MD_LUdet.
               for singularities not cured by editing, permut is 0  */
int     __vf MD_LUDresult( void );
    /* returns 0, if MD_LUdecompose was successful;
       returns 1, if MA was (nearly) singular in MD_LUdecompose.   */
void    __vf MD_LUDsetEdit( double Thresh );
double  __vf MD_LUDgetEdit( void );
     /*  Editing threshold valid for MD_LUdecompose;
         may be used to cure singularities           */

#define MD_LUsolve( X, MLU, B, Ind, len ) \
                    MDLUsolve( X, (MLU)[0], B, Ind, len )
#define MD_LUinv( MInv, MLU, Ind, len ) \
                    MDLUinv( (MInv)[0], (MLU)[0], Ind, len )
#define MD_LUdet( MLU, len, permut )  MDLUdet( (MLU)[0], len, permut )
#define MD_LUimprove( X, B, MA, MLU, Ind, len ) \
                      MDLUimprove( X, B, (MA)[0], (MLU)[0], Ind, len )

	/****	Special treatment for symmetric, positive definite linear
			systems: Use Cholesky decomposition.
			"CholeskyL" functions use lower (left) triangular storage,
			"CholeskyR" functions use upper (right) triangular storage   ******/
#define MD_CholeskyLdecompose( ML, MA, len )		MDCholeskyLdecompose( (ML)[0], (MA)[0], len )
#define MD_CholeskyLsolve( X, ML, B, len )			MDCholeskyLsolve( X, (ML)[0], B, len )
#define MD_CholeskyLimprove( X, B, MA, ML, len )	MDCholeskyLimprove( X, B, (MA)[0], (ML)[0], len )
#define MD_CholeskyLinv( MInv, ML, len )			MDCholeskyLinv( (MInv)[0], (ML)[0], len )
#define MD_CholeskyRdecompose( MR, MA, len )		MDCholeskyRdecompose( (MR)[0], (MA)[0], len )
#define MD_CholeskyRsolve( X, MR, B, len )			MDCholeskyRsolve( X, (MR)[0], B, len )
#define MD_CholeskyRimprove( X, B, MA, MR, len )	MDCholeskyRimprove( X, B, (MA)[0], (MR)[0], len )
#define MD_CholeskyRinv( MInv, MR, len )			MDCholeskyRinv( (MInv)[0], (MR)[0], len )
#define MD_CholeskyDet( MLR, len )					MDCholeskyDet( (MLR)[0], len )
	/* takes either L or R input matrix to calculate determinant */
			
    /****  Special treatment of over- or under-determined
           linear systems, i.e. of matrices with len != ht
           and of singular matrices:
           SVD (Singular Value Decomposition)       ****/

#define MD_SVdecompose( MU, MV, W, MA, htA, lenA ) \
                    MDSVdecompose( (MU)[0], (MV)[0], W, (MA)[0], htA, lenA )
            /*  sizB = htA,  sizX = sizW = htV = lenV = lenA  */
#define MD_SVsort( MUout, MVout, Wout, MUraw, MVraw, Wraw, htU, lenU ) \
					MDSVsort( (MUout)[0], (MVout)[0], Wout, (MUraw)[0], (MVraw)[0], Wraw, htU, lenU )
#define MD_SVsolve( X, MU, MV, W, B, htA, lenA ) \
                    MDSVsolve( X, (MU)[0], (MV)[0], W, B, htA, lenA )
            /*  lenU = lenA,  htA = sizeB, htU = max( lenA, htA ) as fed into
                MD_SVdecompose   */
void    __vf MD_SVDsetEdit( double Thresh );
double  __vf MD_SVDgetEdit( void );
    /* Override of the standard values for editing threshholds
       in MD_SVsolve. Calling MD_setEdit with Thresh=0.0 means
       that you do the necessary editing of W yourself
       before calling MD_SVsolve                           */

 /*****  "Easy-to-use" versions of the matrix functions
          using LUD, Cholesky, or SVD.
          They allocate their own working space and rely
          on your setting of the editing threshold. In
          case of memory stress, you might better use the
          two-step methods declared above.            ***/
#define MD_solve( X, MA, B, len ) \
                    MDsolve( X, (MA)[0], B, len )
#define MD_inv( MInv, MA, len ) \
                    MDinv( (MInv)[0], (MA)[0], len )
#define MD_det(  MA, len ) \
                    MDdet( (MA)[0], len )
#define MD_solveBySVD( X, MA, B, ht, len ) \
                    MDsolveBySVD( X, (MA)[0], B, ht, len )
         /*  sizX = len,  sizB = ht  */
#define MD_safeSolve( X, MA, B, len ) \
                    MDsafeSolve( X, (MA)[0], B, len )
        /* MD_safeSolve tries first LUD. If that fails, SVD is done.
           X[i] will be 0.0 instead of INF for those i corresponding
           to singularities. If even SVD fails, all X[i] are set to 0.0.
           return value 0: success via LUD; 1: success via SVD; -1: failure */

 		/* functions for symmetric matrices which may or may not be 
		   positive definite: */
#define MDsym_solve( X, MA, B, len )	MDsymsolve( X, (MA)[0], B, len )
#define MDsym_inv( MInv, MA, len )		MDsyminv( (MInv)[0], (MA)[0], len )
#define MDsym_det(  MA, len )			MDsymdet( (MA)[0], len )

     /*********  Eigenvalues and Eigenvectors  ********/
      /*** only the most frequent case of symmetric real matrices
           is covered here! *********/

#define MDsym_eigenvalues( EigV, EigM, MA, len, CalcEigenVec ) \
                    MDs_eigenvalues( EigV, (EigM)[0], (MA)[0], len, CalcEigenVec )
                        /*  Eigenvalues are returned in EigV,
                            Eigenvectors are returned as the columns of EigM.
                            CalcEigenVec = 0 means that only eigenvalues
                            are needed; CalcEigenVec != 0 means that
                            also eigenvectors are calculated.
                            Even if eigenvectors are not desired, EigM is
                            needed by the function as working-space. Then, on
                            output, it will contain just rubbish.
                            MA may be overwritten by EigM. */
#define MDsym_sqrt( MY, MX, len )   MDs_sqrt( (MY)[0], (MX)[0], len )
             /* square root of symmetric, positive definite matrix */

/***************** Two-Dimensional Fourier-Transform Methods ************/

#if defined __cplusplus && defined _CMATH_CLASSDEFS
} // following function cannot be extern "C"
#endif
dComplex  __vf   VD_getRspEdit( void );
#if defined __cplusplus && defined _CMATH_CLASSDEFS
extern "C" {
#endif
void      __vf   VD_setRspEdit( dComplex Trunc );
           /* these are the same functions as used
              in the one-dimensional case */

#define MDp_FFT( MY, MX, ht, len, dir )     MDpFFT( (MY)[0], (MX)[0], ht, len, dir )
#define MDb_FFT( MY, MX, ht, len, dir, Buf) MDbFFT( (MY)[0], (MX)[0], ht, len, dir, Buf )
#define MDp_Rows_FFT( MY, MX, ht, len, dir) MDpRows_FFT( (MY)[0], (MX)[0], ht, len, dir )
#define MDp_Cols_FFT( MY, MX, ht, len, dir) MDpCols_FFT( (MY)[0], (MX)[0], ht, len, dir )
#define MDb_Rows_FFT( MY, MX, ht, len, dir, Buf) MDbRows_FFT( (MY)[0], (MX)[0], ht, len, dir, Buf )
#define MDb_Cols_FFT( MY, MX, ht, len, dir, Buf) MDbCols_FFT( (MY)[0], (MX)[0], ht, len, dir, Buf )
#define MDp_FFTtoC( MY, MX, ht, len )       MDpFFTtoC( (MY)[0], (MX)[0], ht, len )
#define MDb_FFTtoC( MY, MX, ht, len, Buf )  MDbFFTtoC( (MY)[0], (MX)[0], ht, len, Buf )
#define MDp_Rows_FFTtoC( MY, MX, ht, len )  MDpRows_FFTtoC( (MY)[0], (MX)[0], ht, len )
#define MDp_Cols_FFTtoC( MY, MX, ht, len )  MDpCols_FFTtoC( (MY)[0], (MX)[0], ht, len )
#define MDb_Rows_FFTtoC( MY, MX, ht, len, Buf )  MDpRows_FFTtoC( (MY)[0], (MX)[0], ht, len, Buf )
#define MDb_Cols_FFTtoC( MY, MX, ht, len, Buf )  MDpCols_FFTtoC( (MY)[0], (MX)[0], ht, len, Buf )
#define MDp_convolve( MY, MFlt, MX, MRsp, ht, len ) \
                  MDpconvolve( (MY)[0], (MFlt)[0], (MX)[0], (MRsp)[0], ht, len )
#define MDp_deconvolve( MY, MFlt, MX, MRsp, ht, len ) \
                  MDpdeconvolve( (MY)[0], (MFlt)[0], (MX)[0], (MRsp)[0], ht, len )
#define MDp_filter( MY, MX, MFlt, ht, len ) MDpfilter( (MY)[0], (MX)[0], (MFlt)[0], ht, len )
#define MDp_autocorr( MACorr, MX, ht, len ) MDpautocorr( (MACorr)[0], (MX)[0], ht, len )
#define MDp_xcorr( MXCorr, MX, MY, ht, len) MDpxcorr( (MXCorr)[0], (MX)[0], (MY)[0], ht, len )
#define MDp_spectrum( MSpec, htSpec, lenSpec, MX, htX, lenX, MWin ) \
              MDpspectrum( (MSpec)[0], htSpec, lenSpec, (MX)[0], htX, lenX, (MWin)[0] )
              /*   htSpec, lenSpec must be 2**n,
                   MSpec must be a (htSpec+1)*(lenSpec+1) matrix!!
                   htX >= n*htSpec,  lenX >= n*lenSpec,
                   htWin = 2*htSpec, lenWin = 2*lenSpec */

#define MD_FFT         MDp_FFT
#define MD_Rows_FFT    MDp_Rows_FFT
#define MD_Cols_FFT    MDp_Cols_FFT
#define MD_FFTtoC      MDp_FFTtoC
#define MD_Rows_FFTtoC MDp_Rows_FFTtoC
#define MD_Cols_FFTtoC MDp_Cols_FFTtoC
#define MD_convolve    MDp_convolve
#define MD_deconvolve  MDp_deconvolve
#define MD_filter      MDp_filter
#define MD_autocorr    MDp_autocorr
#define MD_xcorr       MDp_xcorr
#define MD_spectrum    MDp_spectrum
#define MDFFT          MDpFFT
#define MDRows_FFT     MDpRows_FFT
#define MDCols_FFT     MDpCols_FFT
#define MDFFTtoC       MDpFFTtoC
#define MDRows_FFTtoC  MDpRows_FFTtoC
#define MDCols_FFTtoC  MDpCols_FFTtoC
#define MDconvolve     MDpconvolve
#define MDdeconvolve   MDpdeconvolve
#define MDfilter       MDpfilter
#define MDautocorr     MDpautocorr
#define MDxcorr        MDpxcorr
#define MDspectrum     MDpspectrum

#define MDl_FFT( MY, MX, ht, len, dir )     MDlFFT( (MY)[0], (MX)[0], ht, len, dir )
#define MDl_Rows_FFT( MY, MX, ht, len, dir) MDlRows_FFT( (MY)[0], (MX)[0], ht, len, dir )
#define MDl_Cols_FFT( MY, MX, ht, len, dir) MDlCols_FFT( (MY)[0], (MX)[0], ht, len, dir )
#define MDl_FFTtoC( MY, MX, ht, len )       MDlFFTtoC( (MY)[0], (MX)[0], ht, len )
#define MDl_Rows_FFTtoC( MY, MX, ht, len )  MDlRows_FFTtoC( (MY)[0], (MX)[0], ht, len )
#define MDl_Cols_FFTtoC( MY, MX, ht, len )  MDlCols_FFTtoC( (MY)[0], (MX)[0], ht, len )
#define MDl_convolve( MY, MFlt, MX, MRsp, ht, len ) \
                  MDlconvolve( (MY)[0], (MFlt)[0], (MX)[0], (MRsp)[0], ht, len )
#define MDl_deconvolve( MY, MFlt, MX, MRsp, ht, len ) \
                  MDldeconvolve( (MY)[0], (MFlt)[0], (MX)[0], (MRsp)[0], ht, len )
#define MDl_filter( MY, MX, MFlt, ht, len ) MDlfilter( (MY)[0], (MX)[0], (MFlt)[0], ht, len )
#define MDl_autocorr( MACorr, MX, ht, len ) MDlautocorr( (MACorr)[0], (MX)[0], ht, len )
#define MDl_xcorr( MXCorr, MX, MY, ht, len) MDlxcorr( (MXCorr)[0], (MX)[0], (MY)[0], ht, len )
#define MDl_spectrum( MSpec, htSpec, lenSpec, MX, htX, lenX, MWin ) \
              MDlspectrum( (MSpec)[0], htSpec, lenSpec, (MX)[0], htX, lenX, (MWin)[0] )
              /*   htSpec, lenSpec must be 2**n,
                   MSpec must be a (htSpec+1)*(lenSpec+1) matrix!!
                   htX >= n*htSpec,  lenX >= n*lenSpec,
                   htWin = 2*htSpec, lenWin = 2*lenSpec */

#define MDs_FFT( MY, MX, ht, len, dir )     MDsFFT( (MY)[0], (MX)[0], ht, len, dir )
#define MDs_Rows_FFT( MY, MX, ht, len, dir) MDsRows_FFT( (MY)[0], (MX)[0], ht, len, dir )
#define MDs_Cols_FFT( MY, MX, ht, len, dir) MDsCols_FFT( (MY)[0], (MX)[0], ht, len, dir )
#define MDs_FFTtoC( MY, MX, ht, len )       MDsFFTtoC( (MY)[0], (MX)[0], ht, len )
#define MDs_Rows_FFTtoC( MY, MX, ht, len )  MDsRows_FFTtoC( (MY)[0], (MX)[0], ht, len )
#define MDs_Cols_FFTtoC( MY, MX, ht, len )  MDsCols_FFTtoC( (MY)[0], (MX)[0], ht, len )
#define MDs_convolve( MY, MFlt, MX, MRsp, ht, len ) \
                  MDsconvolve( (MY)[0], (MFlt)[0], (MX)[0], (MRsp)[0], ht, len )
#define MDs_deconvolve( MY, MFlt, MX, MRsp, ht, len ) \
                  MDsdeconvolve( (MY)[0], (MFlt)[0], (MX)[0], (MRsp)[0], ht, len )
#define MDs_filter( MY, MX, MFlt, ht, len ) MDsfilter( (MY)[0], (MX)[0], (MFlt)[0], ht, len )
#define MDs_autocorr( MACorr, MX, ht, len ) MDsautocorr( (MACorr)[0], (MX)[0], ht, len )
#define MDs_xcorr( MXCorr, MX, MY, ht, len) MDsxcorr( (MXCorr)[0], (MX)[0], (MY)[0], ht, len )
#define MDs_spectrum( MSpec, htSpec, lenSpec, MX, htX, lenX, MWin ) \
              MDsspectrum( (MSpec)[0], htSpec, lenSpec, (MX)[0], htX, lenX, (MWin)[0] )
               /*  htSpec, lenSpec must be 2**n,
                   MSpec has [htSpec+1][lenSpec+1] elements (!)
                   htX >= n*htSpec,  lenX >= n*lenSpec,
                   htWin = 2*htSpec, lenWin = 2*lenSpec     */

/************************** Data Fitting *********************************

  Notice that some of these functions have the prefix VD_, others MD_.
  This depends on the form in which the data to be fitted are recorded:
  vectors are fitted by the VD_ functions, matrices by the MD_ functions.
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

typedef struct VD_NONLINFITOPTIONS
{
      int        FigureOfMerit;  /*  0:least squares, 1:robust */
             /* Convergence conditions: if the changes achieved
                in successive iterations are lower than any of the
                following values, this signals convergence. Set
                criteria to 0.0, if not applicable              */
      double     AbsTolChi,  /* absolute change of chi */
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
      double     LambdaStart,
                 LambdaMin, LambdaMax,
                 LambdaDiv, LambdaMul;    /* LevMar parameter lambda */
      unsigned   DownhillIterations; /* max.number of successful iterations in Downhill */
      double     DownhillReflection,  /* re-shaping of the simplex */
                 DownhillContraction,
                 DownhillExpansion;
      unsigned   TotalStarts;  /* max. number of LevMar/Downhill pairs */
      dVector    UpperLimits;  /* impose upper limits on parameters */
      dVector    LowerLimits;  /* impose lower limits on parameters */
      void       (*Restrictions)(void);  /* user-defined editing of parameters */
}  VD_NONLINFITOPTIONS;

typedef struct VD_EXPERIMENT
{
    dVector  X, Y, InvVar;
    ui       size;
    double   WeightOfExperiment;
     /* InvVar and WeightOfExperiment are needed only for the
        weighted variants of the multifit functions */
} VD_EXPERIMENT;

typedef struct MD_EXPERIMENT
{
    dVector    X, Y;
    dMatrix    MZ, MInvVar;  /* here no compatibility with static matrices! */
    ui         htZ, lenZ;
    double     WeightOfExperiment;
     /* MInvVar and WeightOfExperiment are needed only for the
        weighted variants of the multifit functions */
} MD_EXPERIMENT;

typedef struct VD_NONLINFITWORKSPACE
{
	double	chi2, dIntern1, dIntern2, dIntern3, dIntern4,
			dIntern5, dIntern6, dIntern7, dIntern8, dIntern9, dIntern10;
	dVector	Chi2Detail, 
			vdIntern1, vdIntern2, vdIntern3, vdIntern4, vdIntern5,
			vdIntern6, vdIntern7, vdIntern8, vdIntern9, vdIntern10,
			vdIntern11, vdIntern12, vdIntern13, vdIntern14, vdIntern15, 
			vdIntern16, vdIntern17, vdIntern18, vdIntern19, vdIntern20,
			vdIntern21, *vdIntern22;
	dMatrix	mdIntern1, mdIntern2, mdIntern3, mdIntern4, 
			mdIntern5, *mdIntern6, mdIntern7, mdIntern8;
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
	VD_NONLINFITOPTIONS  foptIntern1;
	VD_EXPERIMENT *vdeIntern1;
}  VD_NONLINFITWORKSPACE;

typedef struct MD_NONLINFITWORKSPACE
{
	double	chi2, dIntern1, dIntern2, dIntern3, dIntern4,
			dIntern5, dIntern6, dIntern7, dIntern8, dIntern9, dIntern10;
	dVector	Chi2Detail, 
			vdIntern1, vdIntern2, vdIntern3, vdIntern4, vdIntern5,
			vdIntern6, vdIntern7, vdIntern8, vdIntern9, vdIntern10,
			vdIntern11, vdIntern12, vdIntern13, vdIntern14, vdIntern15, 
			vdIntern16, vdIntern17, vdIntern18, vdIntern19, vdIntern20,
			vdIntern21, *vdIntern22;
	dMatrix	mdIntern1, mdIntern2, mdIntern3, mdIntern4, 
			mdIntern5, mdIntern6, mdIntern7, mdIntern8;
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
	VD_NONLINFITOPTIONS  foptIntern1;
	MD_EXPERIMENT *mdeIntern1;
	dVector vdIntern23;
	dMatrix mdIntern9, mdIntern10, mdIntern11;
	ui		uiIntern2, uiIntern3, uiIntern4;
}  MD_NONLINFITWORKSPACE;

#ifdef __BORLANDC__
    #pragma option -a.   /* restore default data packing  */
#else   /* MS Visual C++ */
    #pragma pack(pop)
#endif
#endif  /* exclusion of NONLINFITWORKSPACE etc. */

void __vf VD_setNonlinfitOptions( VD_NONLINFITOPTIONS *Options );
void __vf VD_getNonlinfitOptions( VD_NONLINFITOPTIONS *Options );

int __vf VD_polyfit( dVector ParValues, unsigned deg, dVector X, dVector Y, ui sizex );
#define   VD_polyfitwW( ParValues, Covar, deg, X, Y, InvVar, sizex ) \
          VDpolyfitwW( ParValues, (Covar)[0], deg, X, Y, InvVar, sizex )
       /* the size of A is deg+1 and Covar has [deg+1][deg+1] elements! */

int __vf VD_linfit( dVector ParValues, iVector ParStatus, unsigned npars,
                     dVector X, dVector Y, ui sizex,
                     void __vf funcs(dVector BasFuncs, double x, unsigned nfuncs) );
#define   VD_linfitwW( ParValues, Covar, ParStatus, npars, X, Y, InvVar, sizex, funcs ) \
          VDlinfitwW( ParValues, (Covar)[0], ParStatus, npars, X, Y, InvVar, sizex, funcs )
#define   MD_linfit( ParValues, ParStatus, npars, X, Y, MZ, htZ, lenZ, funcs ) \
          MDlinfit( ParValues, ParStatus, npars, X, Y, (MZ)[0], htZ, lenZ, funcs )
#define   MD_linfitwW( ParValues, Covar, ParStatus, npars, X, Y, MZ, MInvVar, htZ, lenZ, funcs ) \
          MDlinfitwW( ParValues, (Covar)[0], ParStatus, npars, X, Y, (MZ)[0], (MInvVar)[0], htZ, lenZ, funcs )

void  __vf VD_setLinfitNeglect( double Thresh );
                   /* neglect A[i]=0, if significance smaller than Thresh */
double __vf VD_getLinfitNeglect( void );

double __vf VD_nonlinfit( dVector ParValues, iVector ParStatus, unsigned npars,
                    dVector X, dVector Y, ui sizex,
                    void __vf modelfunc(dVector YModel, dVector XModel, ui size),
                    void __vf derivatives(dVector dYdPari,dVector X, ui size, unsigned i),
					VD_NONLINFITWORKSPACE *FitWorkSpace, VD_NONLINFITOPTIONS *FitOpts );
            /* returns figure-of-merit of best A. If you don't know the partial
               derivatives with respect to ParValues, call with derivatives=NULL */
#ifndef __cplusplus  /* following macros only for plain-C. Overloaded C++ functions see below */
#define   VD_nonlinfitwW( ParValues, Covar, ParStatus, npars, X, Y, InvVar, sizex, modelfunc, deriv, fitworksp, fitopts ) \
          VDnonlinfitwW( ParValues, (Covar)[0], ParStatus, npars, X, Y, InvVar, sizex, modelfunc, deriv, fitworksp, fitopts )
#define   MD_nonlinfit( ParValues, ParStatus, npars, X, Y, MZ, htZ, lenZ, modelfunc, deriv, fitworksp, fitopts ) \
          MDnonlinfit( ParValues, ParStatus, npars, X, Y, (MZ)[0], htZ, lenZ, modelfunc, deriv, fitworksp, fitopts )
#define   MD_nonlinfitwW( ParValues, Covar, ParStatus, npars, X, Y, MZ, MInvVar, htZ, lenZ, modelfunc, deriv, fitworksp, fitopts ) \
          MDnonlinfitwW( ParValues, (Covar)[0], ParStatus, npars, X, Y, (MZ)[0], (MInvVar)[0], htZ, lenZ, modelfunc, deriv, fitworksp, fitopts )
#endif  /* plain-C macros */

        /* If you know some partial derivatives, you may call these functions
           for those parameters for which you do not know them:           */
void   __vf VD_nonlinfit_autoDeriv( dVector dYdPari, dVector X, ui size, unsigned ipar, VD_NONLINFITWORKSPACE *FitWorkSpace );
void   __vf VD_nonlinfitwW_autoDeriv( dVector dYdPari, dVector X, ui size, unsigned ipar, VD_NONLINFITWORKSPACE *FitWorkSpace );
void   __vf MD_nonlinfitwW_autoDeriv( dMatrix dZdAi, ui htZ, ui lenZ, dVector X, dVector Y, unsigned ipar, MD_NONLINFITWORKSPACE *FitWorkSpace );
void   __vf MD_nonlinfit_autoDeriv( dMatrix dZdAi, ui htZ, ui lenZ, dVector X, dVector Y, unsigned ipar, MD_NONLINFITWORKSPACE *FitWorkSpace );
       /* The following functions allow to monitor the progress of
          a nonlinear fitting procedure or to manually stop it:     */
double   __vf VD_nonlinfit_getChi2( VD_NONLINFITWORKSPACE *FitWorkSpace );
double   __vf VD_nonlinfitwW_getChi2( VD_NONLINFITWORKSPACE *FitWorkSpace );
double   __vf MD_nonlinfit_getChi2( MD_NONLINFITWORKSPACE *FitWorkSpace );
double   __vf MD_nonlinfitwW_getChi2( MD_NONLINFITWORKSPACE *FitWorkSpace );
void     __vf VD_nonlinfit_getBestValues( dVector BestValues, VD_NONLINFITWORKSPACE *FitWorkSpace );
void     __vf VD_nonlinfitwW_getBestValues( dVector BestValues, VD_NONLINFITWORKSPACE *FitWorkSpace );
void     __vf MD_nonlinfit_getBestValues( dVector BestValues, MD_NONLINFITWORKSPACE *FitWorkSpace );
void     __vf MD_nonlinfitwW_getBestValues( dVector BestValues, MD_NONLINFITWORKSPACE *FitWorkSpace );
unsigned __vf VD_nonlinfit_getTestRun( VD_NONLINFITWORKSPACE *FitWorkSpace );
unsigned __vf VD_nonlinfitwW_getTestRun( VD_NONLINFITWORKSPACE *FitWorkSpace );
unsigned __vf MD_nonlinfit_getTestRun( MD_NONLINFITWORKSPACE *FitWorkSpace );
unsigned __vf MD_nonlinfitwW_getTestRun( MD_NONLINFITWORKSPACE *FitWorkSpace );
unsigned __vf VD_nonlinfit_getTestPar( VD_NONLINFITWORKSPACE *FitWorkSpace );
unsigned __vf VD_nonlinfitwW_getTestPar( VD_NONLINFITWORKSPACE *FitWorkSpace );
unsigned __vf MD_nonlinfit_getTestPar( MD_NONLINFITWORKSPACE *FitWorkSpace );
unsigned __vf MD_nonlinfitwW_getTestPar( MD_NONLINFITWORKSPACE *FitWorkSpace );
int      __vf VD_nonlinfit_getTestDir( VD_NONLINFITWORKSPACE *FitWorkSpace );
int      __vf VD_nonlinfitwW_getTestDir( VD_NONLINFITWORKSPACE *FitWorkSpace );
int      __vf MD_nonlinfit_getTestDir( MD_NONLINFITWORKSPACE *FitWorkSpace );
int      __vf MD_nonlinfitwW_getTestDir( MD_NONLINFITWORKSPACE *FitWorkSpace );
void     __vf VD_nonlinfit_stop( VD_NONLINFITWORKSPACE *FitWorkSpace );
void     __vf VD_nonlinfitwW_stop( VD_NONLINFITWORKSPACE *FitWorkSpace );
void     __vf MD_nonlinfit_stop( MD_NONLINFITWORKSPACE *FitWorkSpace );
void     __vf MD_nonlinfitwW_stop( MD_NONLINFITWORKSPACE *FitWorkSpace );

int  __vf VD_multiLinfit( dVector ParValues, iVector ParStatus, unsigned nParameters,
                VD_EXPERIMENT _VFAR *ListOfExperiments, unsigned nExperiments,
                void __vf funcs(dVector BasFuncs, double x,
                              unsigned nfuncs, unsigned iexperiment) );
#define   VD_multiLinfitwW( ParValues, Covar, ParStatus, npars, ListOfEx, nexp, funcs ) \
          VDmultiLinfitwW( ParValues, (Covar)[0], ParStatus, npars, ListOfEx, nexp, funcs )
int  __vf MD_multiLinfit( dVector ParValues, iVector ParStatus, unsigned nParameters,
                MD_EXPERIMENT _VFAR *ListOfExperiments, unsigned nExperiments,
                void __vf funcs(dVector BasFuncs, double x, double y,
                              unsigned nfuncs, unsigned iexperiment) );
#define   MD_multiLinfitwW( ParValues, Covar, ParStatus, npars, ListOfEx, nexp, funcs ) \
          MDmultiLinfitwW( ParValues, (Covar)[0], ParStatus, npars, ListOfEx, nexp, funcs )
double __vf VD_multiNonlinfit( dVector ParValues,
                iVector ParStatus, unsigned npars,
                VD_EXPERIMENT _VFAR *ListOfExperiments, unsigned nExperiments,
                void __vf modelfunc(dVector YModel, dVector XModel,
                                  ui size, unsigned iexperiment),
                void __vf derivatives(dVector dYdPari,dVector X, ui size,
                                   unsigned ipar, unsigned iexperiment),
				VD_NONLINFITWORKSPACE *FitWorkSpace, VD_NONLINFITOPTIONS *FitOpts );
            /* returns figure-of-merit of best ParValues. Chi2Detail contains
               the chi2 contribution of each experiment.
               If you don't know the partial derivatives, set derivatives=NULL */
double __vf MD_multiNonlinfit( dVector ParValues, iVector ParStatus, unsigned npars,
                MD_EXPERIMENT _VFAR *ListOfExperiments, unsigned nexperiments,
                void __vf modelfunc(dMatrix MZModel, ui htZ, ui lenZ,
                                  dVector X, dVector Y, unsigned iexperiment),
                void __vf derivatives(dMatrix dZdAi, ui htZ, ui lenZ,
                                    dVector X, dVector Y, unsigned ipar, unsigned iexperiment),
				MD_NONLINFITWORKSPACE *FitWorkSpace, VD_NONLINFITOPTIONS *FitOpts );
#ifndef __cplusplus
#define   VD_multiNonlinfitwW( ParValues, Covar, ParStatus, npars, ListOfEx, nexp, modfunc, deriv, fitworksp, fitopts ) \
          VDmultiNonlinfitwW( ParValues, (Covar)[0], ParStatus, npars, ListOfEx, nexp, modfunc, deriv, fitworksp, fitopts )
#define   MD_multiNonlinfitwW( ParValues, Covar, ParStatus, npars, ListOfEx, nexp, modfunc, deriv, fitworksp, fitopts ) \
          MDmultiNonlinfitwW( ParValues, (Covar)[0], ParStatus, npars, ListOfEx, nexp, modfunc, deriv, fitworksp, fitopts )
#endif  /* plain-C macros */

void  __vf VD_multiNonlinfit_autoDeriv( dVector dYdPari, dVector X, ui size,
                                        unsigned ipar, unsigned iexperiment, VD_NONLINFITWORKSPACE *FitWorkSpace);
void  __vf VD_multiNonlinfitwW_autoDeriv( dVector dYdPari, dVector X, ui size,
                                        unsigned ipar, unsigned iexperiment, VD_NONLINFITWORKSPACE *FitWorkSpace );
void  __vf MD_multiNonlinfit_autoDeriv( dMatrix dZdAi, ui htZ, ui lenZ,
                                    dVector X, dVector Y,
                                    unsigned ipar, unsigned iexperiment, MD_NONLINFITWORKSPACE *FitWorkSpace );
void  __vf MD_multiNonlinfitwW_autoDeriv( dMatrix dZdAi, ui htZ, ui lenZ,
                                    dVector X, dVector Y,
                                    unsigned ipar, unsigned iexperiment, MD_NONLINFITWORKSPACE *FitWorkSpace );
double   __vf VD_multiNonlinfit_getChi2( VD_NONLINFITWORKSPACE *FitWorkSpace );
double   __vf VD_multiNonlinfitwW_getChi2( VD_NONLINFITWORKSPACE *FitWorkSpace );
double   __vf MD_multiNonlinfit_getChi2( MD_NONLINFITWORKSPACE *FitWorkSpace );
double   __vf MD_multiNonlinfitwW_getChi2( MD_NONLINFITWORKSPACE *FitWorkSpace );
void     __vf VD_multiNonlinfit_getChi2Detail( dVector Chi2Detail, VD_NONLINFITWORKSPACE *FitWorkSpace );
void     __vf VD_multiNonlinfitwW_getChi2Detail( dVector Chi2Detail, VD_NONLINFITWORKSPACE *FitWorkSpace );
void     __vf MD_multiNonlinfit_getChi2Detail( dVector Chi2Detail, MD_NONLINFITWORKSPACE *FitWorkSpace );
void     __vf MD_multiNonlinfitwW_getChi2Detail( dVector Chi2Detail, MD_NONLINFITWORKSPACE *FitWorkSpace );
void     __vf VD_multiNonlinfit_getBestValues( dVector BestValues, VD_NONLINFITWORKSPACE *FitWorkSpace );
void     __vf VD_multiNonlinfitwW_getBestValues( dVector BestValues, VD_NONLINFITWORKSPACE *FitWorkSpace );
void     __vf MD_multiNonlinfit_getBestValues( dVector BestValues, MD_NONLINFITWORKSPACE *FitWorkSpace );
void     __vf MD_multiNonlinfitwW_getBestValues( dVector BestValues, MD_NONLINFITWORKSPACE *FitWorkSpace );
unsigned __vf VD_multiNonlinfit_getTestRun( VD_NONLINFITWORKSPACE *FitWorkSpace );
unsigned __vf VD_multiNonlinfitwW_getTestRun( VD_NONLINFITWORKSPACE *FitWorkSpace );
unsigned __vf MD_multiNonlinfit_getTestRun( MD_NONLINFITWORKSPACE *FitWorkSpace );
unsigned __vf MD_multiNonlinfitwW_getTestRun( MD_NONLINFITWORKSPACE *FitWorkSpace );
unsigned __vf VD_multiNonlinfit_getTestPar( VD_NONLINFITWORKSPACE *FitWorkSpace );
unsigned __vf VD_multiNonlinfitwW_getTestPar( VD_NONLINFITWORKSPACE *FitWorkSpace );
unsigned __vf MD_multiNonlinfit_getTestPar( MD_NONLINFITWORKSPACE *FitWorkSpace );
unsigned __vf MD_multiNonlinfitwW_getTestPar( MD_NONLINFITWORKSPACE *FitWorkSpace );
int      __vf VD_multiNonlinfit_getTestDir( VD_NONLINFITWORKSPACE *FitWorkSpace );
int      __vf VD_multiNonlinfitwW_getTestDir( VD_NONLINFITWORKSPACE *FitWorkSpace );
int      __vf MD_multiNonlinfit_getTestDir( MD_NONLINFITWORKSPACE *FitWorkSpace );
int      __vf MD_multiNonlinfitwW_getTestDir( MD_NONLINFITWORKSPACE *FitWorkSpace );
void     __vf VD_multiNonlinfit_stop( VD_NONLINFITWORKSPACE *FitWorkSpace );
void     __vf VD_multiNonlinfitwW_stop( VD_NONLINFITWORKSPACE *FitWorkSpace );
void     __vf MD_multiNonlinfit_stop( MD_NONLINFITWORKSPACE *FitWorkSpace );
void     __vf MD_multiNonlinfitwW_stop( MD_NONLINFITWORKSPACE *FitWorkSpace );

/**************************  Input and Output  **************************/

#define MD_fprint( stream, MA, ht, len, linewidth ) \
                    MDfprint( stream, (MA)[0], ht, len, linewidth )
#define MD_print( MA, ht, len )  MDfprint( stdout, (MA)[0], ht, len, 80 )
#define MD_cprint( MA, ht, len ) MDcprint( (MA)[0], ht, len )
  /*  MD_print, MD_cprint usable only for console applications! */

#define MD_write( str, MA, ht, len )   MDwrite( str, (MA)[0], ht, len )
#define MD_read( MA, ht, len, str )    MDread( (MA)[0], ht, len, str )
#define MD_setWriteFormat              VD_setWriteFormat
#define MD_setWriteSeparate            VD_setNWriteSeparate
                                   /* write and read in ascii format */
#define MD_store( str, MA, ht, len )   VD_store( str, (MA)[0], ((ui)(len))*(ht) )
#define MD_recall( MA, ht, len, str)   VD_recall( (MA)[0], ((ui)(len))*(ht), str)
                                  /* store and recall in binary format */


/*************************************************************************
 * Here are now the actual declarations of the functions used internally.*
 * These declarations may change in future versions of MatrixLib!        *
 * You should not care too much about them, except in the case you need  *
 * the actual address of a run-time function (see above). Under all      *
 * "normal" circumstances, use only the names defined above in the       *
 * macro section!                                                        *
 *************************************************************************/

void  __vf MDgetElement( double *y, dPMatrix X, ui ht, ui len, ui m, ui n );
void  __vf MDsetElement( dPMatrix X, ui ht, ui len, ui m, ui n, double C );
double _VFAR * __vf MDPelement( dPMatrix X, ui ht, ui len, ui m, ui n );
                  /* pointer is normalized in memory model HUGE */
#define MDelement( MA, ht, len, m, n ) (*MDPelement( MA, ht, len, m, n ))

#define MDequ0( MA, ht, len )            VD_equ0( MA, (ht)*(len) )
void   __vf  MDequ1( dPMatrix MA, ui len );  /* identity matrix */
void   __vf  MDequm1( dPMatrix MA, ui len );  /* neg. identity matrix */
void   __vf  MDouterprod( dPMatrix MA, dVector X,  dVector Y,
                          ui ht, ui len );

void   __vf  MDRow_equ0( dPMatrix MA, ui ht, ui len,
                         ui iRow );
void   __vf  MDCol_equ0( dPMatrix MA, ui ht, ui len,
                         ui iCol );
void   __vf  MDDia_equ0( dPMatrix MA, ui len );

void   __vf  MDRow_equC( dPMatrix MA, ui ht, ui len,
                         ui iRow, double C );
void   __vf  MDCol_equC( dPMatrix MA, ui ht, ui len,
                         ui iCol, double C );
void   __vf  MDDia_equC( dPMatrix MA, ui len, double C );

void   __vf  MDRow_equV( dPMatrix MA, ui ht, ui len,
                         ui iRow, dVector X );
void   __vf  MDCol_equV( dPMatrix MA, ui ht, ui len,
                         ui iCol, dVector X );
void   __vf  MDDia_equV( dPMatrix MA, ui len, dVector X );

void   __vf  MDTrd_equM( dPMatrix MA, dPMatrix MTrd, ui len );
void   __vf  MDTrd_extract( dPMatrix MTrd, dPMatrix MA, ui len );

#define MDequM( MB, MA, ht, len )  VD_equV( MB, MA, (ht)*(len) )
#define MDneg( MB, MA, ht, len )   VD_neg( MB, MA, (ht)*(len) )
void   __vf  MDUequL( dPMatrix MA, ui len );
void   __vf  MDLequU( dPMatrix MA, ui len );

void   __vf  MDHann( dPMatrix MA, ui ht, ui len );
#define MDHanning MDHann
void   __vf  MDParzen(  dPMatrix MA, ui ht, ui len );
void   __vf  MDWelch(   dPMatrix MA, ui ht, ui len );

/********  Extracting a submatrix and copying a submatrix back  *********/

void  __vf  MDsubmatrix( dPMatrix MSub,
                          ui subHt,  ui subLen,
                          dPMatrix MSrce,
                          ui srceHt,  ui srceLen,
                          ui firstRowInCol,  ui sampInCol,
                          ui firstColInRow,  ui sampInRow );

void  __vf  MDsubmatrix_equM( dPMatrix MDest,
                               ui destHt,     ui destLen,
                               ui firstRowInCol,  ui sampInCol,
                               ui firstColInRow,  ui sampInRow,
                               dPMatrix MSrce,
                               ui srceHt,     ui srceLen );

void  __vf  MDequMblock(  dPMatrix MSub,
                          ui subHt,  ui subLen,
                          dPMatrix MSrce,
                          ui srceHt,  ui srceLen,
                          ui firstRowInCol,  ui firstColInRow );

void  __vf  MDblock_equM( dPMatrix MDest,
                          ui destHt,     ui destLen,
                          ui firstRowInCol,  ui firstColInRow,
                          dPMatrix MSrce,
                          ui srceHt,     ui srceLen );

void  __vf  MDequMblockT( dPMatrix MSub,
                          ui subHt,  ui subLen,
                          dPMatrix MSrce,
                          ui srceHt,  ui srceLen,
                          ui firstRowInCol,  ui firstColInRow );

void  __vf  MDblock_equMT( dPMatrix MDest,
                          ui destHt,     ui destLen,
                          ui firstRowInCol,  ui firstColInRow,
                          dPMatrix MSrce,
                          ui srceHt,     ui srceLen );


/*****   Extracting a single row or a single column or the diagonal  *****
 *       and storing it into a vector                                    */

void __vf MDRow_extract( dVector Y, dPMatrix MA, ui ht, ui len,
                           ui iRow );
void __vf MDCol_extract( dVector Y, dPMatrix MA, ui ht, ui len,
                           ui iCol );
void __vf MDDia_extract( dVector Y, dPMatrix MA, ui len );

/**********  Deleting or inserting a row or a column *****************/

void __vf MDRow_delete( dPMatrix MB, dPMatrix MA,
                        ui htA, ui lenA, ui iRow );
void __vf MDCol_delete( dPMatrix MB, dPMatrix MA,
                        ui htA, ui lenA, ui iCol );
void __vf MDRow_insert( dPMatrix MB, dPMatrix MA, ui htB,
                        ui lenB, ui iRow, dVector X );
void __vf MDCol_insert( dPMatrix MB, dPMatrix MA, ui htB,
                        ui lenB, ui iCol, dVector X );


/*****************    Basic arithmetic operations ***********************
     performed on one single row,  or one single column of any matrix,
     or on the diagonal of a square matrix                              */

void   __vf  MDRow_neg( dPMatrix MX, ui ht, ui len, ui iRow );
void   __vf  MDCol_neg( dPMatrix MX, ui ht, ui len, ui iCol );

void   __vf  MDRow_addC( dPMatrix MA, ui ht, ui len,
                         ui iRow, double C );
void   __vf  MDCol_addC( dPMatrix MA, ui ht, ui len,
                         ui iCol, double C );
void   __vf  MDDia_addC( dPMatrix MA, ui len, double C );

void   __vf  MDRow_subC( dPMatrix MA, ui ht, ui len,
                         ui iRow, double C );
void   __vf  MDCol_subC( dPMatrix MA, ui ht, ui len,
                         ui iCol, double C );
void   __vf  MDDia_subC( dPMatrix MA, ui len, double C );

void   __vf  MDRow_addV( dPMatrix MA, ui ht, ui len,
                         ui iRow, dVector X );
void   __vf  MDCol_addV( dPMatrix MA, ui ht, ui len,
                         ui iCol, dVector X );
void   __vf  MDDia_addV( dPMatrix MA, ui len, dVector X );

void   __vf  MDRow_subV( dPMatrix MA, ui ht, ui len,
                         ui iRow, dVector X );
void   __vf  MDCol_subV( dPMatrix MA, ui ht, ui len,
                         ui iCol, dVector X );
void   __vf  MDDia_subV( dPMatrix MA, ui len, dVector X );

void   __vf  MDRow_subrC( dPMatrix MA, ui ht, ui len,
                         ui iRow, double C );
void   __vf  MDCol_subrC( dPMatrix MA, ui ht, ui len,
                         ui iCol, double C );
void   __vf  MDDia_subrC( dPMatrix MA, ui len, double C );

void   __vf  MDRow_subrV( dPMatrix MA, ui ht, ui len,
                         ui iRow, dVector X );
void   __vf  MDCol_subrV( dPMatrix MA, ui ht, ui len,
                         ui iCol, dVector X );
void   __vf  MDDia_subrV( dPMatrix MA, ui len, dVector X );

void   __vf  MDRow_mulC( dPMatrix MA, ui ht, ui len,
                         ui iRow, double C );
void   __vf  MDCol_mulC( dPMatrix MA, ui ht, ui len,
                         ui iCol, double C );
void   __vf  MDDia_mulC( dPMatrix MA, ui len, double C );

void   __vf  MDRow_mulV( dPMatrix MA, ui ht, ui len,
                         ui iRow, dVector X );
void   __vf  MDCol_mulV( dPMatrix MA, ui ht, ui len,
                         ui iCol, dVector X );
void   __vf  MDDia_mulV( dPMatrix MA, ui len, dVector X );

void   __vf  MDRow_divC( dPMatrix MA, ui ht, ui len,
                         ui iRow, double C );
void   __vf  MDCol_divC( dPMatrix MA, ui ht, ui len,
                         ui iCol, double C );
void   __vf  MDDia_divC( dPMatrix MA, ui len, double C );

void   __vf  MDRow_divV( dPMatrix MA, ui ht, ui len,
                         ui iRow, dVector X );
void   __vf  MDCol_divV( dPMatrix MA, ui ht, ui len,
                         ui iCol, dVector X );
void   __vf  MDDia_divV( dPMatrix MA, ui len, dVector X );

void   __vf  MDRow_divrC( dPMatrix MA, ui ht, ui len,
                         ui iRow, double C );
void   __vf  MDCol_divrC( dPMatrix MA, ui ht, ui len,
                         ui iCol, double C );
void   __vf  MDDia_divrC( dPMatrix MA, ui len, double C );

void   __vf  MDRow_divrV( dPMatrix MA, ui ht, ui len,
                         ui iRow, dVector X );
void   __vf  MDCol_divrV( dPMatrix MA, ui ht, ui len,
                         ui iCol, dVector X );
void   __vf  MDDia_divrV( dPMatrix MA, ui len, dVector X );


/******  One-dimensional vector operations **********************
         performed along all rows or all columns simultaneously,
         or along the diagonal of a square matrix                */

void   __vf  MDRows_max( dVector Y, dPMatrix MA, ui ht, ui len );
void   __vf  MDCols_max( dVector Y, dPMatrix MA, ui ht, ui len );
double __vf  MDDia_max(  dPMatrix MA, ui len );
void   __vf  MDRows_min( dVector Y, dPMatrix MA, ui ht, ui len );
void   __vf  MDCols_min( dVector Y, dPMatrix MA, ui ht, ui len );
double __vf  MDDia_min(  dPMatrix MA, ui len );

void   __vf  MDRows_absmax( dVector Y, dPMatrix MA, ui ht, ui len );
void   __vf  MDCols_absmax( dVector Y, dPMatrix MA, ui ht, ui len );
double __vf  MDDia_absmax(  dPMatrix MA, ui len );
void   __vf  MDRows_absmin( dVector Y, dPMatrix MA, ui ht, ui len );
void   __vf  MDCols_absmin( dVector Y, dPMatrix MA, ui ht, ui len );
double __vf  MDDia_absmin(  dPMatrix MA, ui len );

void   __vf  MDRows_sum( dVector Y, dPMatrix MA, ui ht, ui len );
void   __vf  MDCols_sum( dVector Y, dPMatrix MA, ui ht, ui len );
double __vf  MDDia_sum(  dPMatrix MA, ui len );
void   __vf  MDRows_ssq( dVector Y, dPMatrix MA, ui ht, ui len );
void   __vf  MDCols_ssq( dVector Y, dPMatrix MA, ui ht, ui len );
double __vf  MDDia_ssq(  dPMatrix MA, ui len );
void   __vf  MDRows_prod(dVector Y, dPMatrix MA, ui ht, ui len );
void   __vf  MDCols_prod(dVector Y, dPMatrix MA, ui ht, ui len );
double __vf  MDDia_prod( dPMatrix MA, ui len );

void  __vf  MDRows_runsum( dPMatrix MA, ui ht, ui len );
void  __vf  MDCols_runsum( dPMatrix MA, ui ht, ui len );
void  __vf  MDRows_runprod( dPMatrix MA, ui ht, ui len );
void  __vf  MDCols_runprod( dPMatrix MA, ui ht, ui len );

void  __vf  MDRows_rotate( dPMatrix MA, ui ht, ui len, ssize_t pos );
void  __vf  MDCols_rotate( dPMatrix MA, ui ht, ui len, ssize_t pos );
void  __vf  MDRows_rotate_buf( dPMatrix MA, ui ht, ui len, ssize_t pos, dPMatrix MBuf );
void  __vf  MDCols_rotate_buf( dPMatrix MA, ui ht, ui len, ssize_t pos, dPMatrix MBuf );
void  __vf  MDRows_reflect( dPMatrix MA, ui ht, ui len );
void  __vf  MDCols_reflect( dPMatrix MA, ui ht, ui len );
void  __vf  MDRows_rev( dPMatrix MA, ui ht, ui len );
void  __vf  MDCols_rev( dPMatrix MA, ui ht, ui len );

void  __vf  MDRows_distribution( uiPMatrix MAbund, dVector Limits, ui nBins, dPMatrix MX, ui ht, ui len, int mode );
void  __vf  MDCols_distribution( uiPMatrix MAbund, dVector Limits, ui nBins, dPMatrix MX, ui ht, ui len, int mode );

/********  Operations involving two rows or two colums of one matrix  *****/

void   __vf  MDRows_exchange( dPMatrix MA, ui ht, ui len,
                              ui i1, ui i2 );
void   __vf  MDCols_exchange( dPMatrix MA, ui ht, ui len,
                              ui i1, ui i2 );

void   __vf  MDRows_add( dPMatrix MA, ui ht, ui len,
                          ui destRow, ui sourceRow );
void   __vf  MDCols_add( dPMatrix MA, ui ht, ui len,
                          ui destCol, ui sourceCol );

void   __vf  MDRows_sub( dPMatrix MA, ui ht, ui len,
                          ui destRow, ui sourceRow );
void   __vf  MDCols_sub( dPMatrix MA, ui ht, ui len,
                          ui destCol, ui sourceCol );

void   __vf  MDRows_Cadd( dPMatrix MA, ui ht, ui len,
                           ui destRow, ui sourceRow, double C );
void   __vf  MDCols_Cadd( dPMatrix MA, ui ht, ui len,
                           ui destCol, ui sourceCol, double C );

void   __vf  MDRows_lincomb( dPMatrix MA, ui ht, ui len,
                              ui destRow,  double  destC,
                              ui srceRow,  double  srceC );
void   __vf  MDCols_lincomb( dPMatrix MA, ui ht, ui len,
                              ui destCol,  double  destC,
                              ui srceCol,  double  srceC );


/*********************  Center of gravity *****************************/
#if defined __cplusplus && defined _CMATH_CLASSDEFS
} // the following functions cannot be extern "C", if dComplex is a class
#endif
dComplex   __vf  MDcenterOfGravityInd( dPMatrix MA, ui ht, ui len );
dComplex   __vf  MDcenterOfGravityV( dVector X, dVector Y, dPMatrix MA, ui ht, ui len );
#if defined __cplusplus && defined _CMATH_CLASSDEFS
extern "C" {
#endif

/***************  Transposing and rotating a matrix **********************/

void  __vf  MDtranspose( dPMatrix MTr, dPMatrix MA,
                          ui htTr, ui lenTr );
void  __vf  MDrotate90(  dPMatrix MRot, dPMatrix MA, ui htRot, ui lenRot );
#define     MDrotate180( MRot, MA, htRot, lenRot ) \
                VD_rev( MRot, MA, (htRot)*(lenRot) )
void  __vf  MDrotate270( dPMatrix MRot, dPMatrix MA, ui htRot, ui lenRot );


/********************** Interpolation of Matrix elements **************/

void __vf  MDpolyinterpol( dPMatrix MZ, dVector X, dVector Y, ui ht, ui len,
       dVector XTab, dVector YTab, dPMatrix MZTab, ui httab, ui lentab,
       unsigned degX, unsigned degY );
void __vf  MDratinterpol( dPMatrix MZ, dVector X, dVector Y, ui ht, ui len,
       dVector XTab, dVector YTab, dPMatrix MZTab, ui httab, ui lentab,
       unsigned degX, unsigned degY );
void __vf  MDnatCubSplineInterpol( dPMatrix MZ, dVector X, dVector Y, ui ht, ui len,
       dVector XTab, dVector YTab, dPMatrix MZTab, ui httab, ui lentab );


/************************ Matrix Arithmetics *************************/

#define MDaddM( MC, MA, MB, htA, lenA ) \
                 VD_addV( MC, MA, MB, (htA)*(lenA) )
void __vf  MDaddMT( dPMatrix MC, dPMatrix MA, dPMatrix MB,
                    ui htA, ui lenA );
#define MDsubM( MC, MA, MB, htA, lenA ) \
                 VD_subV( MC, MA, MB, (htA)*(lenA) )
void __vf  MDsubMT( dPMatrix MC, dPMatrix MA, dPMatrix MB,
                    ui htA, ui lenA );
void __vf  MDsubrMT( dPMatrix MC, dPMatrix MA, dPMatrix MB,
                    ui htA, ui lenA );
#define MDmulC( MB, MA, htA, lenA, C ) \
                 VD_mulC( MB, MA, (htA)*(lenA), C )
#define MDdivC( MB, MA, htA, lenA, C ) \
                 VD_divC( MB, MA, (htA)*(lenA), C )
#define MDsaddM( MC, MA, MB, htA, lenA, C ) \
                 VDs_addV( MC, MA, MB, (htA)*(lenA), C )
void __vf  MDsaddMT( dPMatrix MC, dPMatrix MA, dPMatrix MB,
                    ui htA, ui lenA, double C );
#define MDssubM( MC, MA, MB, htA, lenA, C ) \
                 VDs_subV( MC, MA, MB, (htA)*(lenA), C )
void __vf  MDssubMT( dPMatrix MC, dPMatrix MA, dPMatrix MB,
                    ui htA, ui lenA, double C );
void __vf  MDssubrMT( dPMatrix MC, dPMatrix MA, dPMatrix MB,
                    ui htA, ui lenA, double C );
#define MDlincomb( MC, MA, MB, htA, lenA, CA, CB ) \
                 VD_lincomb( MC, MA, MB, (htA)*(lenA), CA, CB )
void  __vf  MDmulV( dVector Y, dPMatrix MA, dVector X,
                    ui htA, ui lenA );
void  __vf  MDTmulV( dVector Y, dPMatrix MA, dVector X,
                     ui htA, ui lenA );
void  __vf  VDmulM( dVector Y, dVector X, dPMatrix MA,
                    ui htA, ui lenA );
void  __vf  VDmulMT( dVector Y, dVector X, dPMatrix MA,
                     ui htA, ui lenA );
void  __vf  MDmulM( dPMatrix MC, dPMatrix MA, dPMatrix MB,
                    ui htA, ui lenA, ui lenB );
void  __vf  MDmulMT( dPMatrix MC, dPMatrix MA, dPMatrix MB,
                    ui htA, ui lenA, ui htB );
void  __vf  MDTmulM( dPMatrix MC, dPMatrix MA, dPMatrix MB,
                    ui htA, ui lenA, ui lenB );
void  __vf  MDTmulMT( dPMatrix MC, dPMatrix MA, dPMatrix MB,
                    ui htA, ui lenA, ui htB );
void  __vf  MDdiamulM( dPMatrix MC, dPMatrix MADia, dPMatrix MB,
                    ui htB, ui lenB );
void  __vf  MDdiamulMT( dPMatrix MC, dPMatrix MADia, dPMatrix MB,
                    ui htB, ui lenB );
void  __vf  MDmulMdia( dPMatrix MC, dPMatrix MA, dPMatrix MBDia,
                    ui htA, ui lenA );
void  __vf  MDTmulMdia( dPMatrix MC, dPMatrix MA, dPMatrix MBDia,
                    ui htA, ui lenA );


/*************************  Linear Algebra    *****************************/

int    __vf  MDLUdecompose( dPMatrix MLU,  uiVector Ind, dPMatrix MA,
                            ui len );

void   __vf  MDLUsolve( dVector X, dPMatrix MLU, dVector B, uiVector Ind,
                        ui len );
void   __vf  MDLUinv( dPMatrix MInv, dPMatrix MLU, uiVector Ind,
                      ui len );
double __vf  MDLUdet( dPMatrix MLU, ui len, int permut );
void   __vf  MDLUimprove( dVector X, dVector B, dPMatrix MA, dPMatrix MLU,
                          uiVector Ind, ui len );

int    __vf  MDCholeskyLdecompose( dPMatrix ML,  dPMatrix MA, ui len ); /* returns 0 for success, 1 for non-positive definite matrix */
void   __vf  MDCholeskyLsolve( dVector X, dPMatrix ML, dVector B, ui len );
void   __vf  MDCholeskyLimprove( dVector X, dVector B, dPMatrix MA, dPMatrix ML, ui len );
void   __vf  MDCholeskyLinv( dPMatrix MInv, dPMatrix ML, ui len );
int    __vf  MDCholeskyRdecompose( dPMatrix MR,  dPMatrix MA, ui len ); /* returns 0 for success, 1 for non-positive definite matrix */
void   __vf  MDCholeskyRsolve( dVector X, dPMatrix MR, dVector B, ui len );
void   __vf  MDCholeskyRimprove( dVector X, dVector B, dPMatrix MA, dPMatrix MR, ui len );
void   __vf  MDCholeskyRinv( dPMatrix MInv, dPMatrix MR, ui len );
double  __vf  MDCholeskyDet( dPMatrix MLU, ui len );

int    __vf  MDSVdecompose( dPMatrix MU, dPMatrix MV, dVector W, dPMatrix MA,
                           ui htMA, ui lenA );
void   __vf  MDSVsort( dPMatrix MUout, dPMatrix MVout, dVector Wout, 
			 		   dPMatrix MUraw, dPMatrix MVraw, dVector Wraw, ui htU, ui lenU );
void   __vf  MDSVsolve( dVector X, dPMatrix MU, dPMatrix MV, dVector W,
                       dVector B, ui htA, ui lenA );

          /*  functions using LUD or SVD     */
int    __vf  MDsolve( dVector X, dPMatrix MA, dVector B, ui len );
                  /* ret.value != 0 signals error */
int    __vf  MDinv( dPMatrix MInv, dPMatrix MA, ui len );
                 /* ret.value != 0 signals error */
double __vf  MDdet( dPMatrix MA, ui len );

int    __vf  MDsolveBySVD( dVector X, dPMatrix MA, dVector B,
                           ui ht, ui len );
              /*  sizX = lenMA,  sizB = htA.  ret.value != 0 signals failure */
int    __vf  MDsafeSolve( dVector X, dPMatrix MA, dVector B, ui len );
              /* ret.value 0: success via LUD; 1: success via SVD; -1: error */

 /* functions for symmetric matrices which may or may not be positive definite: */
int    __vf  MDsymsolve( dVector X, dPMatrix MA, dVector B, ui len );
                  /* ret.value != 0 signals error */
int    __vf  MDsyminv( dPMatrix MInv, dPMatrix MA, ui len );
                 /* ret.value != 0 signals error */
double  __vf  MDsymdet( dPMatrix MA, ui len );

      /*********  Eigenvalues and Eigenvectors  ********/

int  __vf MDs_eigenvalues( dVector EigV, dPMatrix EigM, dPMatrix MA, ui len,
						int CalcEigenVec );
int  __vf MDs_sqrt( dPMatrix MY, dPMatrix MX, ui len );
              /* ret. value 0: success; 1: failure */

/*************  Matrix Fourier-Transform Methods *****************/

void  __vf   MDpFFT( dPMatrix MY, dPMatrix MX, ui ht, ui len, int dir );
void  __vf   MDbFFT( dPMatrix MY, dPMatrix MX, ui ht, ui len, int dir, dVector Buf );
void  __vf   MDpFFTtoC( cdPMatrix MY, dPMatrix MX, ui ht, ui len );
void  __vf   MDbFFTtoC( cdPMatrix MY, dPMatrix MX, ui ht, ui len, cdVector Buf );
void  __vf   MDpconvolve( dPMatrix MY, dPMatrix MFlt, dPMatrix MX,
                          dPMatrix MRsp, ui ht, ui len );
void  __vf   MDpdeconvolve( dPMatrix MY, dPMatrix MFlt, dPMatrix MX,
                            dPMatrix MRsp, ui ht, ui len );
void  __vf   MDpfilter( dPMatrix MY, dPMatrix MX, dPMatrix MFlt,
                        ui ht, ui len );
void  __vf   MDpautocorr( dPMatrix MACorr, dPMatrix MX,
                          ui ht, ui len );
void  __vf   MDpxcorr( dPMatrix MXCorr, dPMatrix MX, dPMatrix MY,
                       ui ht, ui len );
void  __vf   MDpspectrum( dPMatrix MSpec, ui htSpec, ui lenSpec,
                          dPMatrix MX, ui htX, ui lenX,
                          dPMatrix MWin );
void  __vf   MDpRows_FFT( dPMatrix MY, dPMatrix MX, ui ht, ui len, int dir );
void  __vf   MDpCols_FFT( dPMatrix MY, dPMatrix MX, ui ht, ui len, int dir );
void  __vf   MDbRows_FFT( dPMatrix MY, dPMatrix MX, ui ht, ui len, int dir, dVector Buf );
void  __vf   MDbCols_FFT( dPMatrix MY, dPMatrix MX, ui ht, ui len, int dir, dVector Buf );
void  __vf   MDpRows_FFTtoC( cdPMatrix MY, dPMatrix MX, ui ht, ui len );
void  __vf   MDpCols_FFTtoC( cdPMatrix MY, dPMatrix MX, ui ht, ui len );
void  __vf   MDbRows_FFTtoC( cdPMatrix MY, dPMatrix MX, ui ht, ui len, cdVector Buf );
void  __vf   MDbCols_FFTtoC( cdPMatrix MY, dPMatrix MX, ui ht, ui len, cdVector Buf );

void  __vf   MDlFFT( dPMatrix MY, dPMatrix MX, ui ht, ui len, int dir );
void  __vf   MDlFFTtoC( cdPMatrix MY, dPMatrix MX, ui ht, ui len );
void  __vf   MDlconvolve( dPMatrix MY, dPMatrix MFlt, dPMatrix MX,
                          dPMatrix MRsp, ui ht, ui len );
void  __vf   MDldeconvolve( dPMatrix MY, dPMatrix MFlt, dPMatrix MX,
                            dPMatrix MRsp, ui ht, ui len );
void  __vf   MDlfilter( dPMatrix MY, dPMatrix MX, dPMatrix MFlt,
                        ui ht, ui len );
void  __vf   MDlautocorr( dPMatrix MACorr, dPMatrix MX,
                          ui ht, ui len );
void  __vf   MDlxcorr( dPMatrix MXCorr, dPMatrix MX, dPMatrix MY,
                       ui ht, ui len );
void  __vf   MDlspectrum( dPMatrix MSpec, ui htSpec, ui lenSpec,
                          dPMatrix MX, ui htX, ui lenX,
                          dPMatrix MWin );
void  __vf   MDlRows_FFT( dPMatrix MY, dPMatrix MX, ui ht, ui len, int dir );
void  __vf   MDlCols_FFT( dPMatrix MY, dPMatrix MX, ui ht, ui len, int dir );
void  __vf   MDlRows_FFTtoC( cdPMatrix MY, dPMatrix MX, ui ht, ui len );
void  __vf   MDlCols_FFTtoC( cdPMatrix MY, dPMatrix MX, ui ht, ui len );

void  __vf   MDsFFT( dPMatrix MY, dPMatrix MX, ui ht, ui len, int dir );
void  __vf   MDsFFTtoC( cdPMatrix MY, dPMatrix MX, ui ht, ui len );
void  __vf   MDsconvolve( dPMatrix MY, dPMatrix MFlt, dPMatrix MX,
                          dPMatrix MRsp, ui ht, ui len );
void  __vf   MDsdeconvolve( dPMatrix MY, dPMatrix MFlt, dPMatrix MX,
                            dPMatrix MRsp, ui ht, ui len );
void  __vf   MDsfilter( dPMatrix MY, dPMatrix MX, dPMatrix MFlt,
                        ui ht, ui len );
void  __vf   MDsautocorr( dPMatrix MACorr, dPMatrix MX,
                          ui ht, ui len );
void  __vf   MDsxcorr( dPMatrix MXCorr, dPMatrix MX, dPMatrix MY,
                       ui ht, ui len );
void  __vf   MDsspectrum( dPMatrix MSpec, ui htSpec, ui lenSpec,
                          dPMatrix MX, ui htX, ui lenX,
                          dPMatrix MWin );
void  __vf   MDsRows_FFT( dPMatrix MY, dPMatrix MX, ui ht, ui len, int dir );
void  __vf   MDsCols_FFT( dPMatrix MY, dPMatrix MX, ui ht, ui len, int dir );
void  __vf   MDsRows_FFTtoC( cdPMatrix MY, dPMatrix MX, ui ht, ui len );
void  __vf   MDsCols_FFTtoC( cdPMatrix MY, dPMatrix MX, ui ht, ui len );

      /***************  Data Fitting    ******************/

int  __vf VDpolyfitwW( dVector ParValues, dPMatrix Covar, unsigned deg,
                        dVector X, dVector Y, dVector InvVar, ui sizex );
int  __vf VDlinfitwW( dVector ParValues, dPMatrix Covar, iVector ParStatus, unsigned npars,
                    dVector X, dVector Y, dVector InvVar, ui sizex,
                    void __vf funcs(dVector BasFuncs, double x, unsigned nfuncs) );
double __vf VDnonlinfitwW( dVector ParValues, dPMatrix Covar, iVector ParStatus, unsigned npars,
                    dVector X, dVector Y, dVector InvVar, ui sizex,
                    void __vf modelfunc(dVector YModel, dVector X, ui size),
                    void __vf derivatives(dVector dYdPari, dVector X, ui size, unsigned i),
					VD_NONLINFITWORKSPACE *FitWorkSpace, VD_NONLINFITOPTIONS *FitOpts);
int  __vf MDlinfit( dVector ParValues, iVector ParStatus, unsigned npars,
                    dVector X, dVector Y, dPMatrix MZ, ui htZ, ui lenZ,
                    void __vf funcs(dVector BasFuncs, double x, double y, unsigned nfuncs) );
double __vf MDnonlinfit( dVector ParValues, iVector ParStatus, unsigned npars,
                    dVector X, dVector Y, dPMatrix MZ, ui htZ, ui lenZ,
                    void __vf modelfunc(dMatrix MZModel, ui htZ, ui lenZ, dVector X, dVector Y ),
                    void __vf derivatives(dMatrix dZdAi, ui htZ, ui lenZ, dVector X, dVector Y, unsigned i),
					MD_NONLINFITWORKSPACE *FitWorkSpace, VD_NONLINFITOPTIONS *FitOpts);
int  __vf MDlinfitwW( dVector ParValues, dPMatrix Covar, iVector ParStatus, unsigned npars,
                      dVector X, dVector Y, dPMatrix MZ, dPMatrix MInvVar, ui htZ, ui lenZ,
                      void __vf funcs(dVector BasFuncs, double x, double y, unsigned nfuncs) );
double __vf MDnonlinfitwW( dVector ParValues, dPMatrix Covar, iVector ParStatus, unsigned npars,
                    dVector X, dVector Y, dPMatrix MZ, dPMatrix MInvVar, ui htZ, ui lenZ,
                    void __vf modelfunc(dMatrix MZModel, ui htZ, ui lenZ, dVector X, dVector Y ),
                    void __vf derivatives(dMatrix dZdAi, ui htZ, ui lenZ, dVector X, dVector Y, unsigned i),
					MD_NONLINFITWORKSPACE *FitWorkSpace, VD_NONLINFITOPTIONS *FitOpts);

int  __vf VDmultiLinfitwW( dVector ParValues, dPMatrix Covar, iVector ParStatus, unsigned npars,
                VD_EXPERIMENT _VFAR *ListOfExperiments, unsigned nexperiments,
                void __vf funcs(dVector BasFuncs, double x,
                              unsigned nfuncs, unsigned nexperiment) );
int  __vf MDmultiLinfitwW( dVector ParValues, dPMatrix Covar,
                iVector ParStatus, unsigned npars,
                MD_EXPERIMENT _VFAR *ListOfExperiments, unsigned nexperiments,
                void __vf funcs(dVector BasFuncs, double x, double y,
                              unsigned nfuncs, unsigned nexperiment) );
double __vf VDmultiNonlinfitwW( dVector ParValues, dPMatrix Covar,
                iVector ParStatus, unsigned npars,
                VD_EXPERIMENT _VFAR *ListOfExperiments, unsigned nexperiments,
                void __vf modelfunc(dVector YModel, dVector X, ui size, unsigned iexperiment),
                void __vf derivatives(dVector dYdPari, dVector X, ui size,
                                  unsigned ipar, unsigned iexperiment),
				VD_NONLINFITWORKSPACE *FitWorkSpace, VD_NONLINFITOPTIONS *FitOpts);
double __vf MDmultiNonlinfitwW( dVector ParValues, dPMatrix Covar,
                iVector ParStatus, unsigned npars,
                MD_EXPERIMENT _VFAR *ListOfExperiments, unsigned nexperiments,
                void __vf modelfunc(dMatrix MZModel, ui htZ, ui lenZ,
                                  dVector X, dVector Y, unsigned iexperiment ),
                void __vf derivatives(dMatrix dZdAi, ui htZ, ui lenZ,
                                    dVector X, dVector Y,
                                    unsigned ipar, unsigned iexperiment),
				MD_NONLINFITWORKSPACE *FitWorkSpace, VD_NONLINFITOPTIONS *FitOpts);

      /*************  Input and Output  ****************/

#define MDprint( MA, ht, len )  MDfprint( stdout, MA, ht, len, 80 )
void __vf MDfprint( FILE _VFAR *stream, dPMatrix MA, ui ht,
                     ui len, unsigned linewidth );
void __vf MDcprint( dPMatrix MA, ui ht, ui len );
void __vf MDwrite( FILE _VFAR *stream, dPMatrix X, ui ht, ui len  );
#if !((defined __BORLANDC__) && (__BORLANDC__ < 0x710))
		/* modern compiler versions:  */
	void __vf MDread( dPMatrix X, ui ht, ui len, FILE _VFAR *stream );
#else /* older Borland compiler versions need separate implementation */
	void __vf MDread1( dPMatrix X, ui ht, ui len, FILE _VFAR *stream );
	#define MDread  MDread1
#endif
#define MDstore( str, MA, ht, len ) VD_store( str, MA, (len)*(ht) )
#define MDrecall( MA, ht, len, str) VD_recall( MA, (len)*(ht), str)

#ifdef __cplusplus
}  // end of extern "C"

/* now C++ overloaded forms of nonlinfit functions both in complete and in simplified syntax: */
inline double __vf VD_nonlinfit( dVector A, iVector AStatus, unsigned npars,
                    dVector X, dVector Y, ui sizex,
                    void __vf modelfunc(dVector YModel, dVector XModel, ui size),
                    void __vf derivatives(dVector dYdAi,dVector X, ui size, unsigned iPar) )
{	return VD_nonlinfit( A, AStatus, npars, X, Y, sizex, modelfunc, derivatives, NULL, NULL );
}

inline double __vf VDnonlinfitwW( dVector A, dPMatrix Covar, iVector AStatus, unsigned npars,
                    dVector X, dVector Y, dVector InvVar, ui sizex,
                    void __vf modelfunc(dVector YModel, dVector X, ui size),
                    void __vf derivatives(dVector dYdAi, dVector X, ui size, unsigned i) )
{	return VDnonlinfitwW( A, Covar, AStatus, npars, X, Y, InvVar, sizex, 
						  modelfunc, derivatives, NULL, NULL );
}

inline double __vf VD_nonlinfitwW( dVector A, dMatrix Covar, iVector AStatus, unsigned npars,
                    dVector X, dVector Y, dVector InvVar, ui sizex,
                    void __vf modelfunc(dVector YModel, dVector X, ui size),
                    void __vf derivatives(dVector dYdAi, dVector X, ui size, unsigned i),
				VD_NONLINFITWORKSPACE *FitWorkSpace, VD_NONLINFITOPTIONS *FitOpts)
{	return VDnonlinfitwW( A, (Covar)[0], AStatus, npars, X, Y, InvVar, sizex, 
						  modelfunc, derivatives, FitWorkSpace, FitOpts );
}

inline double __vf VD_nonlinfitwW( dVector A, dMatrix Covar, iVector AStatus, unsigned npars,
                    dVector X, dVector Y, dVector InvVar, ui sizex,
                    void __vf modelfunc(dVector YModel, dVector X, ui size),
                    void __vf derivatives(dVector dYdAi, dVector X, ui size, unsigned i) )
{	return VDnonlinfitwW( A, (Covar)[0], AStatus, npars, X, Y, InvVar, sizex, 
						  modelfunc, derivatives, NULL, NULL );
}

inline double __vf MDnonlinfit( dVector A, iVector AStatus, unsigned npars,
                    dVector X, dVector Y, dPMatrix MZ, ui htZ, ui lenZ,
                    void __vf modelfunc(dMatrix MZModel, ui htZ, ui lenZ, dVector X, dVector Y ),
                    void __vf derivatives(dMatrix dZdAi, ui htZ, ui lenZ, dVector X, dVector Y, unsigned ipar) )
{	return MDnonlinfit( A, AStatus, npars, X, Y, MZ, htZ, lenZ, modelfunc, derivatives, NULL, NULL );
}

inline double __vf MD_nonlinfit( dVector A, iVector AStatus, unsigned npars,
                    dVector X, dVector Y, dMatrix MZ, ui htZ, ui lenZ,
                    void __vf modelfunc(dMatrix MZModel, ui htZ, ui lenZ, dVector X, dVector Y ),
                    void __vf derivatives(dMatrix dZdAi, ui htZ, ui lenZ, dVector X, dVector Y, unsigned ipar),
				MD_NONLINFITWORKSPACE *FitWorkSpace, VD_NONLINFITOPTIONS *FitOpts)
{	return MDnonlinfit( A, AStatus, npars, X, Y, (MZ)[0], htZ, lenZ, modelfunc, derivatives, FitWorkSpace, FitOpts );
}

inline double __vf MD_nonlinfit( dVector A, iVector AStatus, unsigned npars,
                    dVector X, dVector Y, dMatrix MZ, ui htZ, ui lenZ,
                    void __vf modelfunc(dMatrix MZModel, ui htZ, ui lenZ, dVector X, dVector Y ),
                    void __vf derivatives(dMatrix dZdAi, ui htZ, ui lenZ, dVector X, dVector Y, unsigned ipar) )
{	return MDnonlinfit( A, AStatus, npars, X, Y, (MZ)[0], htZ, lenZ, modelfunc, derivatives, NULL, NULL );
}

inline double __vf MDnonlinfitwW( dVector A, dPMatrix Covar, iVector AStatus, unsigned npars,
                    dVector X, dVector Y, dPMatrix MZ, dPMatrix MInvVar, ui htZ, ui lenZ,
                    void __vf modelfunc(dMatrix MZModel, ui htZ, ui lenZ, dVector X, dVector Y ),
                    void __vf derivatives(dMatrix dZdAi, ui htZ, ui lenZ, dVector X, dVector Y, unsigned ipar) )
{	return MDnonlinfitwW( A, Covar, AStatus, npars, X, Y, MZ, MInvVar, htZ, lenZ, 
						  modelfunc, derivatives, NULL, NULL );
}

inline double __vf MD_nonlinfitwW( dVector A, dMatrix Covar, iVector AStatus, unsigned npars,
                    dVector X, dVector Y, dMatrix MZ, dMatrix MInvVar, ui htZ, ui lenZ,
                    void __vf modelfunc(dMatrix MZModel, ui htZ, ui lenZ, dVector X, dVector Y ),
                    void __vf derivatives(dMatrix dZdAi, ui htZ, ui lenZ, dVector X, dVector Y, unsigned ipar),
				MD_NONLINFITWORKSPACE *FitWorkSpace, VD_NONLINFITOPTIONS *FitOpts)
{	return MDnonlinfitwW( A, (Covar)[0], AStatus, npars, X, Y, (MZ)[0], (MInvVar)[0], htZ, lenZ, 
						  modelfunc, derivatives, FitWorkSpace, FitOpts );
}

inline double __vf MD_nonlinfitwW( dVector A, dMatrix Covar, iVector AStatus, unsigned npars,
                    dVector X, dVector Y, dMatrix MZ, dMatrix MInvVar, ui htZ, ui lenZ,
                    void __vf modelfunc(dMatrix MZModel, ui htZ, ui lenZ, dVector X, dVector Y ),
                    void __vf derivatives(dMatrix dZdAi, ui htZ, ui lenZ, dVector X, dVector Y, unsigned ipar) )
{	return MDnonlinfitwW( A, (Covar)[0], AStatus, npars, X, Y, (MZ)[0], (MInvVar)[0], htZ, lenZ, 
						  modelfunc, derivatives, NULL, NULL );
}

inline double __vf VD_multiNonlinfit( dVector A, iVector AStatus, unsigned npars,
                VD_EXPERIMENT _VFAR *ListOfExperiments, unsigned nexperiments,
                void __vf modelfunc(dVector YModel, dVector XModel,
                                  ui size, unsigned iexperiment),
                void __vf derivatives(dVector dYdAi,dVector X, ui size,
                                  unsigned ipar, unsigned iexperiment) )
{	return VD_multiNonlinfit( A, AStatus, npars, ListOfExperiments, nexperiments,
							 modelfunc, derivatives, NULL, NULL );
}

inline double __vf VDmultiNonlinfitwW( dVector A, dPMatrix Covar,
                iVector AStatus, unsigned npars,
                VD_EXPERIMENT _VFAR *ListOfExperiments, unsigned nexperiments,
                void __vf modelfunc(dVector YModel, dVector X, ui size, unsigned iexperiment),
                void __vf derivatives(dVector dYdAi, dVector X, ui size,
                                  unsigned ipar, unsigned iexperiment) )
{	return VDmultiNonlinfitwW( A, Covar, AStatus, npars, ListOfExperiments, nexperiments,
							 modelfunc, derivatives, NULL, NULL );
}

inline double __vf VD_multiNonlinfitwW( dVector A, dMatrix Covar,
                iVector AStatus, unsigned npars,
                VD_EXPERIMENT _VFAR *ListOfExperiments, unsigned nexperiments,
                void __vf modelfunc(dVector YModel, dVector X, ui size, unsigned iexperiment),
                void __vf derivatives(dVector dYdAi, dVector X, ui size,
                                  unsigned ipar, unsigned iexperiment),
				VD_NONLINFITWORKSPACE *FitWorkSpace, VD_NONLINFITOPTIONS *FitOpts)
{	return VDmultiNonlinfitwW( A, (Covar)[0], AStatus, npars, ListOfExperiments, nexperiments,
							 modelfunc, derivatives, FitWorkSpace, FitOpts );
}

inline double __vf VD_multiNonlinfitwW( dVector A, dMatrix Covar,
                iVector AStatus, unsigned npars,
                VD_EXPERIMENT _VFAR *ListOfExperiments, unsigned nexperiments,
                void __vf modelfunc(dVector YModel, dVector X, ui size, unsigned iexperiment),
                void __vf derivatives(dVector dYdAi, dVector X, ui size,
                                  unsigned ipar, unsigned iexperiment) )
{	return VDmultiNonlinfitwW( A, (Covar)[0], AStatus, npars, ListOfExperiments, nexperiments,
							 modelfunc, derivatives, NULL, NULL );
}

inline double __vf MD_multiNonlinfit( dVector A, iVector AStatus, unsigned npars,
                MD_EXPERIMENT _VFAR *ListOfExperiments, unsigned nexperiments,
                void __vf modelfunc(dMatrix MZModel, ui htZ, ui lenZ,
                                  dVector X, dVector Y, unsigned iexperiment),
                void __vf derivatives(dMatrix dZdAi, ui htZ, ui lenZ,
                                    dVector X, dVector Y, unsigned ipar,
                                    unsigned iexperiment) )
{	return MD_multiNonlinfit( A, AStatus, npars, ListOfExperiments, nexperiments,
							 modelfunc, derivatives, NULL, NULL );
}

inline double __vf MDmultiNonlinfitwW( dVector A, dPMatrix Covar,
                iVector AStatus, unsigned npars,
                MD_EXPERIMENT _VFAR *ListOfExperiments, unsigned nexperiments,
                void __vf modelfunc(dMatrix MZModel, ui htZ, ui lenZ,
                                  dVector X, dVector Y, unsigned iexperiment ),
                void __vf derivatives(dMatrix dZdAi, ui htZ, ui lenZ,
                                    dVector X, dVector Y,
                                    unsigned ipar, unsigned iexperiment) )
{	return MDmultiNonlinfitwW( A, Covar, AStatus, npars, ListOfExperiments, nexperiments,
							 modelfunc, derivatives, NULL, NULL );
}

inline double __vf MD_multiNonlinfitwW( dVector A, dMatrix Covar,
                iVector AStatus, unsigned npars,
                MD_EXPERIMENT _VFAR *ListOfExperiments, unsigned nexperiments,
                void __vf modelfunc(dMatrix MZModel, ui htZ, ui lenZ,
                                  dVector X, dVector Y, unsigned iexperiment ),
                void __vf derivatives(dMatrix dZdAi, ui htZ, ui lenZ,
                                    dVector X, dVector Y,
                                    unsigned ipar, unsigned iexperiment),
				MD_NONLINFITWORKSPACE *FitWorkSpace, VD_NONLINFITOPTIONS *FitOpts)
{	return MDmultiNonlinfitwW( A, (Covar)[0], AStatus, npars, ListOfExperiments, nexperiments,
							 modelfunc, derivatives, FitWorkSpace, FitOpts );
}

inline double __vf MD_multiNonlinfitwW( dVector A, dMatrix Covar,
                iVector AStatus, unsigned npars,
                MD_EXPERIMENT _VFAR *ListOfExperiments, unsigned nexperiments,
                void __vf modelfunc(dMatrix MZModel, ui htZ, ui lenZ,
                                  dVector X, dVector Y, unsigned iexperiment ),
                void __vf derivatives(dMatrix dZdAi, ui htZ, ui lenZ,
                                    dVector X, dVector Y,
                                    unsigned ipar, unsigned iexperiment) )
{	return MDmultiNonlinfitwW( A, (Covar)[0], AStatus, npars, ListOfExperiments, nexperiments,
							 modelfunc, derivatives, NULL, NULL );
}
#endif
#endif /* __MDSTD_H */
