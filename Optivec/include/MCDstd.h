/*  MCDstd.h

  matrix management functions:
  manipulations on matrices of data type "dComplex"
  (double-precision complex numbers)

  Copyright (c) 1996-2017 by OptiCode - Dr. Martin Sander Software Dev.
  All Rights Reserved.
*/

#if !defined( __MCDSTD_H )
#define __MCDSTD_H
#if !defined( __MATLIB_H )
   #include <MatLib.h>
#endif
#if !defined( __VCDSTD_H )
   #include <VCDstd.h>
#endif
#if !defined( __VCDMATH_H )
   #include <VCDmath.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif

/*************   Dynamic Generation of Matrices   ************************/

cdMatrix __vf  MCD_matrix(  ui ht, ui len );
cdMatrix __vf  MCD_matrix0( ui ht, ui len );
#if defined (_MSC_VER) && defined (_DEBUG)
    cdMatrix __vf  MCD_matrix_dbg(  ui ht, ui len );
    cdMatrix __vf  MCD_matrix0_dbg( ui ht, ui len );
    #if defined (_INC_CRTDBG) && defined (_CRTDBG_MAP_ALLOC) 
	    /* Automatic mapping for memory-leak detection by CRT debugging switched on? */ 
        #define MCD_matrix  MCD_matrix_dbg
        #define MCD_matrix0 MCD_matrix0_dbg
    #endif
#else
    #define MCD_matrix_dbg  MCD_matrix
    #define MCD_matrix0_dbg MCD_matrix0
#endif
    /*  notice that, in the memory model HUGE,
        neither len nor ht may exceed 2047                */

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

#define MCD_getElement( y, MA, ht, len, m, n ) MCDgetElement( y, (MA)[0], ht, len, m, n )
#define MCD_setElement( MA, ht, len, m, n, C ) MCDsetElement( (MA)[0], ht, len, m, n, C )
#define MCD_Pelement( MA, ht, len, m, n ) MCDPelement( (MA)[0], ht, len, m, n )
                     /* returns a pointer to MA[m][n]. */
#define MCD_element( MA, ht, len, m, n ) *MCDPelement( (MA)[0], ht, len, m, n )
                     /* dereferenced pointer */

 /****************  Initialization  ***************************************

    To initialize all elements of a matrix with the same value,
    or to perform arithmetic operations on all elements simultaneously,
    refer to the functions of VectorLib, declared in <VCDstd.h>, <VCDmath.h>.
    In order to use the VectorLib functions, utilize the feature that
    the whole matrix occupies one contiguous area in memory: pass the
    address of the first row to the desired vector function, the size
    of the "vector" being len * ht.
    For example, initialize all elements of the matrix MA with {1.0, 0.0}
    (this is *NOT* the identity matrix)  by calling
        VCD_equ1( (MA)[0], len * ht );
*/

#define MCD_equ0( MA, ht, len )            VCD_equ0( (MA)[0], (ht)*(len) )
#define MCD_equ1( MA, len )                MCDequ1( (MA)[0], len )  /* identity matrix */
#define MCD_equm1( MA, len )               MCDequm1( (MA)[0], len )  /* neg. identity matrix */
#define MCD_randomLC( MA, ht, len, seed, Min, Max, state ) \
                                           VCD_randomLC( (MA)[0], (ht)*(len), seed, Min, Max, state )
#define MCD_random( MA, ht, len, seed, Min, Max ) \
                                           VCD_random( (MA)[0], (ht)*(len), seed, Min, Max )
#define MCD_outerprod( MA, X, Y, ht, len ) MCDouterprod( (MA)[0], X, Y, ht, len )
                       /* sizX=ht, sizY=len */
#define MCD_Row_equ0( MA, ht, len, iRow ) MCDRow_equ0( (MA)[0], ht, len, iRow )
#define MCD_Col_equ0( MA, ht, len, iCol ) MCDCol_equ0( (MA)[0], ht, len, iCol )
#define MCD_Dia_equ0( MA, len )           MCDDia_equ0( (MA)[0], len )
#define MCD_Row_equC( MA, ht, len, iRow, C ) \
                                        MCDRow_equC( (MA)[0], ht, len, iRow, C )
#define MCD_Col_equC( MA, ht, len, iCol, C ) \
                                        MCDCol_equC( (MA)[0], ht, len, iCol, C )
#define MCD_Dia_equC( MA, len, C )       MCDDia_equC( (MA)[0], len, C )

#define MCD_Row_equV( MA, ht, len, iRow, X ) \
                                        MCDRow_equV( (MA)[0], ht, len, iRow, X )
#define MCD_Col_equV( MA, ht, len, iCol, X ) \
                                        MCDCol_equV( (MA)[0], ht, len, iCol, X )
#define MCD_Dia_equV( MA, len, X )      MCDDia_equV( (MA)[0], len, X )

#define MCD_Trd_equM( MA, MTrd, len )    MCDTrd_equM( (MA)[0], (MTrd)[0], len )
#define MCD_Trd_extract( MTrd, MA, len ) MCDTrd_extract( (MTrd)[0], (MA)[0], len )

#define MCD_equM( MB, MA, ht, len )  VCD_equV( (MB)[0], (MA)[0], ((ui)(len))*(ht) )
#define MCD_neg( MB, MA, ht, len )   VCD_neg( (MB)[0], (MA)[0], ((ui)(len))*(ht) )
#define MCD_conj( MB, MA, ht, len )  VCD_conj( (MB)[0], (MA)[0], ((ui)(len))*(ht) )

#define MCD_UequL( MA, len ) MCDUequL( (MA)[0], len )
#define MCD_LequU( MA, len ) MCDLequU( (MA)[0], len )
         /* copy lower-diagonal elements into upper-diagonal
           (or vice versa) by index-reflection, so as to
           get a symmetric matrix    */

            /* data-type conversions:  */
#define M_CDtoCF( MCF, MCD, ht, len ) V_CDtoCF( (MCF)[0], (MCD)[0], (ht)*(len) )
#define M_CFtoCD( MCD, MCF, ht, len ) V_CFtoCD( (MCD)[0], (MCF)[0], (ht)*(len) )
#define M_CEtoCD( MCD, MCE, ht, len ) V_CEtoCD( (MCD)[0], (MCE)[0], (ht)*(len) )
#define M_CDtoCE( MCE, MCD, ht, len ) V_CDtoCE( (MCE)[0], (MCD)[0], (ht)*(len) )

#define MD_CtoRe( MY, MCX, ht, len )  VD_CtoRe( (MY)[0],  (MCX)[0], (ht)*(len) )
#define MD_CtoIm( MY, MCX, ht, len )  VD_CtoIm( (MY)[0],  (MCX)[0], (ht)*(len) )
#define MD_CtoReIm( MYRe, MYIm, MCX, ht, len )  VD_CtoReIm( (MYRe)[0], (MYIm)[0], (MCX)[0], (ht)*(len) )
#define MD_RetoC( MCY, MX, ht, len )  VD_RetoC( (MCY)[0], (MX)[0],  (ht)*(len) )
#define MD_ImtoC( MCY, MX, ht, len )  VD_ImtoC( (MCY)[0], (MX)[0],  (ht)*(len) )
#define MD_ReImtoC( MCY, MXRe, MXIm, ht, len )  VD_ReImtoC( (MCY)[0], (MXRe)[0], (MXIm)[0], (ht)*(len) )

/********  Extracting a submatrix and copying a submatrix back  *********/

#define MCD_submatrix( MSub, subHt, subLen, \
                       MSrce, srceHt, srceLen, \
                       firstRowInCol, sampInCol, firstColInRow, sampInRow ) \
               MCDsubmatrix(  (MSub)[0], subHt, subLen, \
                              (MSrce)[0], srceHt, srceLen, \
                              firstRowInCol, sampInCol, firstColInRow, sampInRow )

#define MCD_submatrix_equM( MDest, destHt, destLen, \
                            firstRowInCol, sampInCol, firstColInRow, sampInRow, \
                            MSrce, srceHt, srceLen ) \
               MCDsubmatrix_equM(  (MDest)[0], destHt, destLen, \
                             firstRowInCol, sampInCol, firstColInRow, sampInRow, \
                             (MSrce)[0], srceHt, srceLen )

#define MCD_equMblock( MSub, subHt, subLen, \
                      MSrce, srceHt, srceLen, \
                      firstRowInCol, firstColInRow ) \
              MCDequMblock(  (MSub)[0], subHt, subLen, \
                             (MSrce)[0], srceHt, srceLen, \
                             firstRowInCol, firstColInRow )

#define MCD_block_equM( MDest, destHt, destLen, \
                       firstRowInCol, firstColInRow, \
                       MSrce, srceHt, srceLen ) \
              MCDblock_equM( (MDest)[0], destHt, destLen, \
                             firstRowInCol, firstColInRow, \
                             (MSrce)[0], srceHt, srceLen )

#define MCD_equMblockT( MSub, subHt, subLen, \
                      MSrce, srceHt, srceLen, \
                      firstRowInCol, firstColInRow ) \
              MCDequMblockT( (MSub)[0], subHt, subLen, \
                             (MSrce)[0], srceHt, srceLen, \
                             firstRowInCol, firstColInRow )

#define MCD_block_equMT( MDest, destHt, destLen, \
                       firstRowInCol, firstColInRow, \
                       MSrce, srceHt, srceLen ) \
              MCDblock_equMT( (MDest)[0], destHt, destLen, \
                             firstRowInCol, firstColInRow, \
                             (MSrce)[0], srceHt, srceLen )

/*****   Extracting a single row or a single column or the diagonal  ******
 *       and storing it into a vector                                     */

#define MCD_Row_extract( Y, MA, ht, len, iRow ) \
                                     MCDRow_extract( Y, (MA)[0], ht, len, iRow )
#define MCD_Col_extract( Y, MA, ht, len, iCol ) \
                                     MCDCol_extract( Y, (MA)[0], ht, len, iCol )
#define MCD_Dia_extract( Y, MA, len ) MCDDia_extract( Y, (MA)[0], len )


/**************  Deleting or inserting a row or a column   ***************/

#define MCD_Row_delete( MB, MA, htA, lenA, iRow ) \
                           MCDRow_delete( (MB)[0], (MA)[0], htA, lenA, iRow )
#define MCD_Col_delete( MB, MA, htA, lenA, iCol ) \
                           MCDCol_delete( (MB)[0], (MA)[0], htA, lenA, iCol )
#define MCD_Row_insert( MB, MA, htB, lenB, iRow, X ) \
                           MCDRow_insert( (MB)[0], (MA)[0], htB, lenB, iRow, X )
#define MCD_Col_insert( MB, MA, htB, lenB, iCol, X ) \
                           MCDCol_insert( (MB)[0], (MA)[0], htB, lenB, iCol, X )


/*****************    Basic arithmetic operations *********************
                      performed on one single row,
                      or one single column of any matrix,
                      or on the diagonal of a square matrix

    Note: In contrast to the analogous VectorLib functions, the operations
    are performed in-place, i.e. the input matrix itself is changed  */

#define MCD_Row_neg( MA, ht, len, iRow ) MCDRow_neg( (MA)[0], ht, len, iRow )
#define MCD_Col_neg( MA, ht, len, iCol ) MCDCol_neg( (MA)[0], ht, len, iCol )

#define MCD_Row_conj( MA, ht, len, iRow ) MCDRow_conj( (MA)[0], ht, len, iRow )
#define MCD_Col_conj( MA, ht, len, iCol ) MCDCol_conj( (MA)[0], ht, len, iCol )

#define MCD_Row_addC( MA, ht, len, iRow, C ) \
                                     MCDRow_addC( (MA)[0], ht, len, iRow, C )
#define MCD_Col_addC( MA, ht, len, iCol, C ) \
                                     MCDCol_addC( (MA)[0], ht, len, iCol, C )
#define MCD_Dia_addC( MA, len, C )   MCDDia_addC( (MA)[0], len, C )

#define MCD_Row_addV( MA, ht, len, iRow, X ) \
                                     MCDRow_addV( (MA)[0], ht, len, iRow, X )
#define MCD_Col_addV( MA, ht, len, iCol, X ) \
                                     MCDCol_addV( (MA)[0], ht, len, iCol, X )
#define MCD_Dia_addV( MA, len, X )   MCDDia_addV( (MA)[0], len, X )

#define MCD_Row_subC( MA, ht, len, iRow, C ) \
                                     MCDRow_subC( (MA)[0], ht, len, iRow, C )
#define MCD_Col_subC( MA, ht, len, iCol, C ) \
                                     MCDCol_subC( (MA)[0], ht, len, iCol, C )
#define MCD_Dia_subC( MA, len, C )   MCDDia_subC( (MA)[0], len, C )

#define MCD_Row_subV( MA, ht, len, iRow, X ) \
                                     MCDRow_subV( (MA)[0], ht, len, iRow, X )
#define MCD_Col_subV( MA, ht, len, iCol, X ) \
                                     MCDCol_subV( (MA)[0], ht, len, iCol, X )
#define MCD_Dia_subV( MA, len, X )   MCDDia_subV( (MA)[0], len, X )

#define MCD_Row_subrC( MA, ht, len, iRow, C ) \
                                     MCDRow_subrC( (MA)[0], ht, len, iRow, C )
#define MCD_Col_subrC( MA, ht, len, iCol, C ) \
                                     MCDCol_subrC( (MA)[0], ht, len, iCol, C )
#define MCD_Dia_subrC( MA, len, C )  MCDDia_subrC( (MA)[0], len, C )

#define MCD_Row_subrV( MA, ht, len, iRow, X ) \
                                     MCDRow_subrV( (MA)[0], ht, len, iRow, X )
#define MCD_Col_subrV( MA, ht, len, iCol, X ) \
                                     MCDCol_subrV( (MA)[0], ht, len, iCol, X )
#define MCD_Dia_subrV( MA, len, X )  MCDDia_subrV( (MA)[0], len, X )

#define MCD_Row_mulC( MA, ht, len, iRow, C ) \
                                     MCDRow_mulC( (MA)[0], ht, len, iRow, C )
#define MCD_Col_mulC( MA, ht, len, iCol, C ) \
                                     MCDCol_mulC( (MA)[0], ht, len, iCol, C )
#define MCD_Dia_mulC( MA, len, C )   MCDDia_mulC( (MA)[0], len, C )

#define MCD_Row_mulV( MA, ht, len, iRow, X ) \
                                     MCDRow_mulV( (MA)[0], ht, len, iRow, X )
#define MCD_Col_mulV( MA, ht, len, iCol, X ) \
                                     MCDCol_mulV( (MA)[0], ht, len, iCol, X )
#define MCD_Dia_mulV( MA, len, X )   MCDDia_mulV( (MA)[0], len, X )

#define MCD_Row_divC( MA, ht, len, iRow, C ) \
                                     MCDRow_divC( (MA)[0], ht, len, iRow, C )
#define MCD_Col_divC( MA, ht, len, iCol, C ) \
                                     MCDCol_divC( (MA)[0], ht, len, iCol, C )
#define MCD_Dia_divC( MA, len, C )   MCDDia_divC( (MA)[0], len, C )

#define MCD_Row_divV( MA, ht, len, iRow, X ) \
                                      MCDRow_divV( (MA)[0], ht, len, iRow, X )
#define MCD_Col_divV( MA, ht, len, iCol, X ) \
                                      MCDCol_divV( (MA)[0], ht, len, iCol, X )
#define MCD_Dia_divV( MA, len, X )    MCDDia_divV( (MA)[0], len, X )

#define MCD_Row_divrC( MA, ht, len, iRow, C ) \
                                      MCDRow_divrC( (MA)[0], ht, len, iRow, C )
#define MCD_Col_divrC( MA, ht, len, iCol, C ) \
                                      MCDCol_divrC( (MA)[0], ht, len, iCol, C )
#define MCD_Dia_divrC( MA, len, C )   MCDDia_divrC( (MA)[0], len, C )

#define MCD_Row_divrV( MA, ht, len, iRow, X ) \
                                      MCDRow_divrV( (MA)[0], ht, len, iRow, X )
#define MCD_Col_divrV( MA, ht, len, iCol, X ) \
                                      MCDCol_divrV( (MA)[0], ht, len, iCol, X )
#define MCD_Dia_divrV( MA, len, X )   MCDDia_divrV( (MA)[0], len, X )


/******  One-dimensional vector operations **********************
         performed along all rows or all columns simultaneously,
         or along the diagonal of a square matrix                */

#define MCD_Rows_absmax( Y, MA, ht, len )  MCDRows_absmax( Y, (MA)[0], ht, len )
#define MCD_Cols_absmax( Y, MA, ht, len )  MCDCols_absmax( Y, (MA)[0], ht, len )
#define MCD_Dia_absmax( MA, len )          MCDDia_absmax( (MA)[0], len )
#define MCD_Rows_absmin( Y, MA, ht, len )  MCDRows_absmin( Y, (MA)[0], ht, len )
#define MCD_Cols_absmin( Y, MA, ht, len )  MCDCols_absmin( Y, (MA)[0], ht, len )
#define MCD_Dia_absmin( MA, len )          MCDDia_absmin( (MA)[0], len )

#define MCD_Rows_maxReIm( Y, MA, ht, len ) MCDRows_maxReIm( Y, (MA)[0], ht, len )
#define MCD_Cols_maxReIm( Y, MA, ht, len ) MCDCols_maxReIm( Y, (MA)[0], ht, len )
#define MCD_Dia_maxReIm( MA, len )         MCDDia_maxReIm( (MA)[0], len )
#define MCD_Rows_minReIm( Y, MA, ht, len ) MCDRows_minReIm( Y, (MA)[0], ht, len )
#define MCD_Cols_minReIm( Y, MA, ht, len ) MCDCols_minReIm( Y, (MA)[0], ht, len )
#define MCD_Dia_minReIm( MA, len )         MCDDia_minReIm( (MA)[0], len )

#define MCD_Rows_absmaxReIm( Y, MA, ht, len ) MCDRows_absmaxReIm( Y, (MA)[0], ht, len )
#define MCD_Cols_absmaxReIm( Y, MA, ht, len ) MCDCols_absmaxReIm( Y, (MA)[0], ht, len )
#define MCD_Dia_absmaxReIm( MA, len )         MCDDia_absmaxReIm( (MA)[0], len )
#define MCD_Rows_absminReIm( Y, MA, ht, len ) MCDRows_absminReIm( Y, (MA)[0], ht, len )
#define MCD_Cols_absminReIm( Y, MA, ht, len ) MCDCols_absminReIm( Y, (MA)[0], ht, len )
#define MCD_Dia_absminReIm( MA, len )         MCDDia_absminReIm( (MA)[0], len )

#define MCD_Rows_cabsmax( Y, MA, ht, len ) MCDRows_cabsmax( Y, (MA)[0], ht, len )
#define MCD_Cols_cabsmax( Y, MA, ht, len ) MCDCols_cabsmax( Y, (MA)[0], ht, len )
#define MCD_Dia_cabsmax( MA, len )         MCDDia_cabsmax( (MA)[0], len )
#define MCD_Rows_cabsmin( Y, MA, ht, len ) MCDRows_cabsmin( Y, (MA)[0], ht, len )
#define MCD_Cols_cabsmin( Y, MA, ht, len ) MCDCols_cabsmin( Y, (MA)[0], ht, len )
#define MCD_Dia_cabsmin( MA, len )         MCDDia_cabsmin( (MA)[0], len )

#define MCD_Rows_sabsmax( Y, MA, ht, len ) MCDRows_sabsmax( Y, (MA)[0], ht, len )
#define MCD_Cols_sabsmax( Y, MA, ht, len ) MCDCols_sabsmax( Y, (MA)[0], ht, len )
#define MCD_Dia_sabsmax( MA, len )         MCDDia_sabsmax( (MA)[0], len )
#define MCD_Rows_sabsmin( Y, MA, ht, len ) MCDRows_sabsmin( Y, (MA)[0], ht, len )
#define MCD_Cols_sabsmin( Y, MA, ht, len ) MCDCols_sabsmin( Y, (MA)[0], ht, len )
#define MCD_Dia_sabsmin( MA, len )         MCDDia_sabsmin( (MA)[0], len )

#define MCD_Rows_sum( Y, MA, ht, len )     MCDRows_sum( Y, (MA)[0], ht, len )
#define MCD_Cols_sum( Y, MA, ht, len )     MCDCols_sum( Y, (MA)[0], ht, len )
#define MCD_Dia_sum(  MA, len )            MCDDia_sum( (MA)[0], len )
#define MCD_Rows_prod( Y, MA, ht, len )    MCDRows_prod( Y, (MA)[0], ht, len )
#define MCD_Cols_prod( Y, MA, ht, len )    MCDCols_prod( Y, (MA)[0], ht, len )
#define MCD_Dia_prod(  MA, len )           MCDDia_prod( (MA)[0], len )

#define MCD_Rows_runsum( MA, ht, len )     MCDRows_runsum( (MA)[0], ht, len )
#define MCD_Cols_runsum( MA, ht, len )     MCDCols_runsum( (MA)[0], ht, len )
#define MCD_Rows_runprod( MA, ht, len )    MCDRows_runprod( (MA)[0], ht, len )
#define MCD_Cols_runprod( MA, ht, len )    MCDCols_runprod( (MA)[0], ht, len )

#define MCD_Rows_rotate( MA, ht, len, pos) MCDRows_rotate( (MA)[0], ht, len, pos )
#define MCD_Cols_rotate( MA, ht, len, pos) MCDCols_rotate( (MA)[0], ht, len, pos )
#define MCD_Rows_rotate_buf( MA, ht, len, pos, MBuf) MCDRows_rotate_buf( (MA)[0], ht, len, pos, (MBuf)[0] )
#define MCD_Cols_rotate_buf( MA, ht, len, pos, MBuf) MCDCols_rotate_buf( (MA)[0], ht, len, pos, (MBuf)[0] )
#define MCD_Rows_reflect( MA, ht, len)     MCDRows_reflect( (MA)[0], ht, len )
#define MCD_Cols_reflect( MA, ht, len)     MCDCols_reflect( (MA)[0], ht, len )
#define MCD_Rows_rev( MA, ht, len)         MCDRows_rev( (MA)[0], ht, len )
#define MCD_Cols_rev( MA, ht, len)         MCDCols_rev( (MA)[0], ht, len )

/********  Operations involving two rows or two colums of one matrix  *****/

#define MCD_Rows_exchange( MA, ht, len, row1, row2 ) \
                             MCDRows_exchange( (MA)[0], ht, len, row1, row2 )
#define MCD_Cols_exchange( MA, ht, len, col1, col2 ) \
                             MCDCols_exchange( (MA)[0], ht, len, col1, col2 )

#define MCD_Rows_add( MA, ht, len, destRow, srceRow ) \
                             MCDRows_add( (MA)[0], ht, len, destRow, srceRow )
#define MCD_Cols_add( MA, ht, len, destCol, srceCol ) \
                             MCDCols_add( (MA)[0], ht, len, destCol, srceCol )
                         /* dest[i] += source[i]  */

#define MCD_Rows_sub( MA, ht, len, destRow, srceRow ) \
                             MCDRows_sub( (MA)[0], ht, len, destRow, srceRow )
#define MCD_Cols_sub( MA, ht, len, destCol, srceCol ) \
                             MCDCols_sub( (MA)[0], ht, len, destCol, srceCol )
                         /* dest[i] -= source[i]  */

#define MCD_Rows_Cadd( MA, ht, len, destRow, srceRow, C ) \
                          MCDRows_Cadd( (MA)[0], ht, len, destRow, srceRow, C )
#define MCD_Cols_Cadd( MA, ht, len, destCol, srceCol, C ) \
                          MCDCols_Cadd( (MA)[0], ht, len, destCol, srceCol, C )
                         /* dest[i] += C * source[i]  */

#define MCD_Rows_lincomb( MA, ht, len, destRow, destC, srceRow, srceC ) \
            MCDRows_lincomb( (MA)[0], ht, len, destRow, destC, srceRow, srceC )
#define MCD_Cols_lincomb( MA, ht, len, destCol, destC, srceCol, srceC ) \
            MCDCols_lincomb( (MA)[0], ht, len, destCol, destC, srceCol, srceC )
  /*  linear combination: dest[i] = destC * dest[i] + sourceC * source[i] */


/*****************  Transposing and rotating a matrix **********************/

#define MCD_transpose( MTr, MA, htTr, lenTr ) \
             MCDtranspose( (MTr)[0], (MA)[0], htTr, lenTr )
       /*  the dimensions htTr, lenTr are those of the transposed matrix,
           not of the original!                */
#define MCD_hermconj( MHConj, MA, htTr, lenTr ) \
             MCDhermconj( (MHConj)[0], (MA)[0], htTr, lenTr )
#define MCD_rotate90( MRot, MA, htRot, lenRot ) \
             MCDrotate90( (MRot)[0], (MA)[0], htRot, lenRot )
#define MCD_rotate180( MRot, MA, htRot, lenRot ) \
             VCD_rev( (MRot)[0], (MA)[0], (htRot)*(lenRot) )
#define MCD_rotate270( MRot, MA, htRot, lenRot ) \
             MCDrotate270( (MRot)[0], (MA)[0], htRot, lenRot )


/************************ Matrix Arithmetics *************************/

#define MCD_addM( MC, MA, MB, htA, lenA ) \
                 VCD_addV( (MC)[0], (MA)[0], (MB)[0], (htA)*(lenA) )
#define MCD_addMT( MC, MA, MB, htA, lenA ) \
                 MCDaddMT( (MC)[0], (MA)[0], (MB)[0], htA, lenA )
#define MCD_subM( MC, MA, MB, htA, lenA ) \
                 VCD_subV( (MC)[0], (MA)[0], (MB)[0], (htA)*(lenA) )
#define MCD_subMT( MC, MA, MB, htA, lenA ) \
                 MCDsubMT( (MC)[0], (MA)[0], (MB)[0], htA, lenA )
#define MCD_subrMT( MC, MA, MB, htA, lenA ) \
                 MCDsubrMT( (MC)[0], (MA)[0], (MB)[0], htA, lenA )
#define MCD_mulC( MB, MA, htA, lenA, C ) \
                 VCD_mulC( (MB)[0], (MA)[0], (htA)*(lenA), C )
#define MCD_divC( MB, MA, htA, lenA, C ) \
                 VCD_divC( (MB)[0], (MA)[0], (htA)*(lenA), C )
#define MCD_mulReC( MB, MA, htA, lenA, CRe ) \
                 VCD_mulReC( (MB)[0], (MA)[0], (htA)*(lenA), CRe )
#define MCD_divReC( MB, MA, htA, lenA, CRe ) \
                 VCD_divReC( (MB)[0], (MA)[0], (htA)*(lenA), CRe )
#define MCD_lincomb( MC, MA, MB, htA, lenA, CA, CB ) \
                 VCD_lincomb( (MC)[0], (MA)[0], (MB)[0], (htA)*(lenA), CA, CB )

#define MCD_mulV( Y, MA, X, htA, lenA ) \
                    MCDmulV( Y, (MA)[0], X, htA, lenA )
                          /*  Y = MA * X.  sizX=lenA, sizY=htA
                              both X and Y are column-vectors    */
#define MCD_TmulV( Y, MA, X, htA, lenA ) \
                    MCDTmulV( Y, (MA)[0], X, htA, lenA )
                          /*  Y = MAT * X.  sizX=htA, sizY=lenA
                              both X and Y are column-vectors    */
#define VCD_mulM( Y, X, MA, htA, lenA ) \
                    VCDmulM( Y, X, (MA)[0], htA, lenA )
                         /*  Y = X * MA.  sizX=htA, sizY=lenA
                             both X and Y are row-vectors.
                             Mind the prefix: VCD_ (not MCD_)    */
#define VCD_mulMT( Y, X, MA, htA, lenA ) \
                    VCDmulMT( Y, X, (MA)[0], htA, lenA )
                         /*  Y = X * MAT.  sizX=lenA, sizY=htA
                             both X and Y are row-vectors.   */
#define MCD_mulM( MC, MA, MB, htA, lenA, lenB ) \
                    MCDmulM( (MC)[0], (MA)[0], (MB)[0], htA, lenA, lenB )
                         /*  MC = MA * MB.  htB=lenA, htC=htA, lenC=lenB */
#define MCD_mulMT( MC, MA, MB, htA, lenA, htB ) \
                    MCDmulMT( (MC)[0], (MA)[0], (MB)[0], htA, lenA, htB )
                         /*  MC = MA * MBT.  lenB=lenA, htC=htA, lenC=htB */
#define MCD_mulMH( MC, MA, MB, htA, lenA, htB ) \
                    MCDmulMH( (MC)[0], (MA)[0], (MB)[0], htA, lenA, htB )
                         /*  MC = MA * MBH.  lenB=lenA, htC=htA, lenC=htB */
#define MCD_TmulM( MC, MA, MB, htA, lenA, lenB ) \
                    MCDTmulM( (MC)[0], (MA)[0], (MB)[0], htA, lenA, lenB )
                         /*  MC = MAT * MB.  htB=htA, htC=lenA, lenC=lenB */
#define MCD_HmulM( MC, MA, MB, htA, lenA, lenB ) \
                    MCDHmulM( (MC)[0], (MA)[0], (MB)[0], htA, lenA, lenB )
                         /*  MC = MAH * MB.  htB=htA, htC=lenA, lenC=lenB */
#define MCD_TmulMT( MC, MA, MB, htA, lenA, htB ) \
                    MCDTmulMT( (MC)[0], (MA)[0], (MB)[0], htA, lenA, htB )
                         /*  MC = MAT * MBT.  lenB=htA, htC=lenA, lenC=htB */
#define MCD_TmulMH( MC, MA, MB, htA, lenA, htB ) \
                    MCDTmulMH( (MC)[0], (MA)[0], (MB)[0], htA, lenA, htB )
                         /*  MC = MAT * MBH.  lenB=htA, htC=lenA, lenC=htB */
#define MCDdia_mulM(  MC, MADia, MB, htB, lenB )  MCDdiamulM(  (MC)[0], MADia, (MB)[0], htB, lenB )
#define MCDdia_mulMT( MC, MADia, MB, htB, lenB )  MCDdiamulMT( (MC)[0], MADia, (MB)[0], htB, lenB )
#define MCD_mulMdia(  MC, MA, MBDia, htA, lenA )  MCDmulMdia(  (MC)[0], (MA)[0], MBDia, htA, lenA )
#define MCD_TmulMdia( MC, MA, MBDia, htA, lenA )  MCDTmulMdia( (MC)[0], (MA)[0], MBDia, htA, lenA )

/*************************  Linear Algebra    *****************************/

   /*  The standard treatment of linear systems is based
       on LUD (matrix decomposition into Upper-triangular
       and Lower-triangular components). The result of the
       decomposition step is used for further operations.  */

#define MCD_LUdecompose( MLU, Ind, MA, len ) \
                    MCDLUdecompose( (MLU)[0], Ind, (MA)[0], len )
            /* returns "permut" = ñ1 which is needed for MCD_LUdet.
               for singularities not cured by editing, permut is 0  */
int     __vf MCD_LUDresult( void );
    /* returns 0, if MCD_LUdecompose was successful;
       returns 1, if MA was (nearly) singular in MCD_LUdecompose.   */
void    __vf MCD_LUDsetEdit( double Thresh );
double  __vf MCD_LUDgetEdit( void );
     /*  Editing threshold valid for MCD_LUdecompose;
         may be used to cure singularities           */

#define MCD_LUsolve( X, MLU, B, Ind, len ) \
                    MCDLUsolve( X, (MLU)[0], B, Ind, len )
#define MCD_LUinv( MInv, MLU, Ind, len ) \
                    MCDLUinv( (MInv)[0], (MLU)[0], Ind, len )
#define MCD_LUdet( MLU, len, permut )  MCDLUdet( (MLU)[0], len, permut )
#define MCD_LUimprove( X, B, MA, MLU, Ind, len ) \
                      MCDLUimprove( X, B, (MA)[0], (MLU)[0], Ind, len )

    /****  Special treatment of over- or under-determined
           linear systems, i.e. of matrices with len != ht
           and of singular matrices:
           SVD (Singular Value Decomposition)       ****

#define MCD_SVdecompose( MU, MV, W, MA, htA, lenA ) \
                    MCDSVdecompose( (MU)[0], (MV)[0], W, (MA)[0], htA, lenA )
            *  sizB = htA,  sizX = sizW = htV = lenV = lenA  *
#define MCD_SVsolve( X, MU, MV, W, B, htU, lenU ) \
                    MCDSVsolve( X, (MU)[0], (MV)[0], W, B, htU, lenU )
            *  lenU = lenA,  htU = max( lenA, htA ) as fed into
                MCD_SVdecompose   *
void    __vf MCD_SVDsetEdit( double Thresh );
double  __vf MCD_SVDgetEdit( void );
    * Override of the standard values for editing threshholds
       in MCD_SVsolve. Calling MCD_setEdit with Thresh=0.0 means
       that you do the necessary editing of W yourself
       before calling MCD_SVsolve                           */

 /*****  "Easy-to-use" versions of the matrix functions
          using LUD or SVD.
          They allocate their own working space and rely
          on your setting of the editing threshold. In
          case of memory stress, you might better use the
          two-step methods declared above.            ***/
#define MCD_solve( X, MA, B, len ) \
                    MCDsolve( X, (MA)[0], B, len )
#define MCD_inv( MInv, MA, len ) \
                    MCDinv( (MInv)[0], (MA)[0], len )
#define MCD_det(  MA, len ) \
                    MCDdet( (MA)[0], len )
/* #define MCD_solveBySVD( X, MA, B, ht, len ) \
                    MCDsolveBySVD( X, (MA)[0], B, ht, len )
         *  sizX = len,  sizB = ht  *
#define MCD_safeSolve( X, MA, B, len ) \
                    MCDsafeSolve( X, (MA)[0], B, len )
        * MCD_safeSolve tries first LUD. If that fails, SVD is done.
           X[i] will be 0.0 instead of INF for those i corresponding
           to singularities. If even SVD fails, all X[i] are set to 0.0.
           return value 0: success via LUD; 1: success via SVD; -1: failure */

/***************** Two-Dimensional Fourier-Transform Methods ************/

#define MCDp_FFT( MY, MX, ht, len, dir )      MCDpFFT( (MY)[0], (MX)[0], ht, len, dir )
#define MCDb_FFT( MY, MX, ht, len, dir, Buf ) MCDbFFT( (MY)[0], (MX)[0], ht, len, dir, Buf )
#define MCDp_Rows_FFT( MY, MX, ht, len, dir) MCDpRows_FFT( (MY)[0], (MX)[0], ht, len, dir )
#define MCDp_Cols_FFT( MY, MX, ht, len, dir) MCDpCols_FFT( (MY)[0], (MX)[0], ht, len, dir )
#define MCDb_Rows_FFT( MY, MX, ht, len, dir, Buf) MCDbRows_FFT( (MY)[0], (MX)[0], ht, len, dir, Buf )
#define MCDb_Cols_FFT( MY, MX, ht, len, dir, Buf) MCDbCols_FFT( (MY)[0], (MX)[0], ht, len, dir, Buf )
#define MCDp_filter( MY, MX, MFlt, ht, len ) MCDpfilter( (MY)[0], (MX)[0], (MFlt)[0], ht, len )

#define MCD_FFT         MCDp_FFT
#define MCD_Rows_FFT    MCDp_Rows_FFT
#define MCD_Cols_FFT    MCDp_Cols_FFT
#define MCD_filter      MCDp_filter
#define MCDFFT          MCDpFFT
#define MCDRows_FFT     MCDpRows_FFT
#define MCDCols_FFT     MCDpCols_FFT
#define MCDfilter       MCDpfilter

#define MCDl_FFT( MY, MX, ht, len, dir )     MCDlFFT( (MY)[0], (MX)[0], ht, len, dir )
#define MCDl_Rows_FFT( MY, MX, ht, len, dir) MCDlRows_FFT( (MY)[0], (MX)[0], ht, len, dir )
#define MCDl_Cols_FFT( MY, MX, ht, len, dir) MCDlCols_FFT( (MY)[0], (MX)[0], ht, len, dir )
#define MCDl_filter( MY, MX, MFlt, ht, len ) MCDlfilter( (MY)[0], (MX)[0], (MFlt)[0], ht, len )

#define MCDs_FFT( MY, MX, ht, len, dir )     MCDsFFT( (MY)[0], (MX)[0], ht, len, dir )
#define MCDs_Rows_FFT( MY, MX, ht, len, dir) MCDsRows_FFT( (MY)[0], (MX)[0], ht, len, dir )
#define MCDs_Cols_FFT( MY, MX, ht, len, dir) MCDsCols_FFT( (MY)[0], (MX)[0], ht, len, dir )
#define MCDs_filter( MY, MX, MFlt, ht, len ) MCDsfilter( (MY)[0], (MX)[0], (MFlt)[0], ht, len )

/**************************  Input and Output  **************************/

#define MCD_fprint( stream, MA, ht, len, linewidth ) \
                    MCDfprint( stream, (MA)[0], ht, len, linewidth )
#define MCD_print( MA, ht, len )  MCDfprint( stdout, (MA)[0], ht, len, 80 )
#define MCD_cprint( MA, ht, len ) MCDcprint( (MA)[0], ht, len )
  /*  MCD_print, MCD_cprint usable only for console applications! */

#define MCD_write( str, MA, ht, len )   MCDwrite( str, (MA)[0], ht, len )
#define MCD_read( MA, ht, len, str )    MCDread( (MA)[0], ht, len, str )
#define MCD_setWriteFormat              VCD_setWriteFormat
#define MCD_setWriteSeparate            VCD_setNWriteSeparate
                                   /* write and read in ascii format */
#define MCD_store( str, MA, ht, len )   VCD_store( str, (MA)[0], ((ui)(len))*(ht) )
#define MCD_recall( MA, ht, len, str)   VCD_recall( (MA)[0], ((ui)(len))*(ht), str)
                                  /* store and recall in binary format */


/*************************************************************************
 * Here are now the actual declarations of the functions used internally.*
 * These declarations may change in future versions of MatrixLib!        *
 * You should not care too much about them, except in the case you need  *
 * the actual address of a run-time function (see above). Under all      *
 * "normal" circumstances, use only the names defined above in the       *
 * macro section!                                                        *
 *************************************************************************/

void  __vf MCDgetElement( dComplex *y, cdPMatrix X, ui ht, ui len, ui m, ui n );
void  __vf MCDsetElement( cdPMatrix X, ui ht, ui len, ui m, ui n, dComplex C );
dComplex _VFAR * __vf MCDPelement( cdPMatrix X, ui ht, ui len, ui m, ui n );
                  /* pointer is normalized in memory model HUGE */
#define MCDelement( MA, ht, len, m, n ) (*MCDPelement( MA, ht, len, m, n ))

#define MCDequ0( MA, ht, len )    VCD_equ0( MA, (ht)*(len) )
void   __vf  MCDequ1( cdPMatrix MA, ui len );  /* identity matrix */
void   __vf  MCDequm1( cdPMatrix MA, ui len );  /* neg. identity matrix */
void   __vf  MCDouterprod( cdPMatrix MA, cdVector X,  cdVector Y,
                           ui ht, ui len );

void   __vf  MCDRow_equ0( cdPMatrix MA, ui ht, ui len,
                         ui iRow );
void   __vf  MCDCol_equ0( cdPMatrix MA, ui ht, ui len,
                         ui iCol );
void   __vf  MCDDia_equ0( cdPMatrix MA, ui len );

void   __vf  MCDRow_equC( cdPMatrix MA, ui ht, ui len,
                         ui iRow, dComplex C );
void   __vf  MCDCol_equC( cdPMatrix MA, ui ht, ui len,
                         ui iCol, dComplex C );
void   __vf  MCDDia_equC( cdPMatrix MA, ui len, dComplex C );

void   __vf  MCDRow_equV( cdPMatrix MA, ui ht, ui len,
                         ui iRow, cdVector X );
void   __vf  MCDCol_equV( cdPMatrix MA, ui ht, ui len,
                         ui iCol, cdVector X );
void   __vf  MCDDia_equV( cdPMatrix MA, ui len, cdVector X );

void   __vf  MCDTrd_equM( cdPMatrix MA, cdPMatrix MTrd, ui len );
void   __vf  MCDTrd_extract( cdPMatrix MTrd, cdPMatrix MA, ui len );

#define MCDequM( MB, MA, ht, len )  VCD_equV( MB, MA, (ht)*(len) )
#define MCDneg( MB, MA, ht, len )   VCD_neg( MB, MA, (ht)*(len) )
#define MCDconj( MB, MA, ht, len )  VCD_conj( MB, MA, (ht)*(len) )

void   __vf  MCDUequL( cdPMatrix MA, ui len );
void   __vf  MCDLequU( cdPMatrix MA, ui len );

/********  Extracting a submatrix and copying a submatrix back  *********/

void  __vf  MCDsubmatrix( cdPMatrix MSub,
                          ui subHt,  ui subLen,
                          cdPMatrix MSrce,
                          ui srceHt,  ui srceLen,
                          ui firstRowInCol,  ui sampInCol,
                          ui firstColInRow,  ui sampInRow );

void  __vf  MCDsubmatrix_equM( cdPMatrix MDest,
                               ui destHt,     ui destLen,
                               ui firstRowInCol,  ui sampInCol,
                               ui firstColInRow,  ui sampInRow,
                               cdPMatrix MSrce,
                               ui srceHt,     ui srceLen );

void  __vf  MCDequMblock( cdPMatrix MSub,
                          ui subHt,  ui subLen,
                          cdPMatrix MSrce,
                          ui srceHt,  ui srceLen,
                          ui firstRowInCol,  ui firstColInRow );

void  __vf  MCDblock_equM( cdPMatrix MDest,
                           ui destHt,     ui destLen,
                           ui firstRowInCol,  ui firstColInRow,
                           cdPMatrix MSrce,
                           ui srceHt,     ui srceLen );

void  __vf  MCDequMblockT( cdPMatrix MSub,
                          ui subHt,  ui subLen,
                          cdPMatrix MSrce,
                          ui srceHt,  ui srceLen,
                          ui firstRowInCol,  ui firstColInRow );

void  __vf  MCDblock_equMT( cdPMatrix MDest,
                           ui destHt,     ui destLen,
                           ui firstRowInCol,  ui firstColInRow,
                           cdPMatrix MSrce,
                           ui srceHt,     ui srceLen );


/*****   Extracting a single row or a single column or the diagonal  *****
 *       and storing it into a vector                                    */

void __vf MCDRow_extract( cdVector Y, cdPMatrix MA, ui ht, ui len,
                           ui iRow );
void __vf MCDCol_extract( cdVector Y, cdPMatrix MA, ui ht, ui len,
                           ui iCol );
void __vf MCDDia_extract( cdVector Y, cdPMatrix MA, ui len );

/**********  Deleting or inserting a row or a column *****************/

void __vf MCDRow_delete( cdPMatrix MB, cdPMatrix MA,
                         ui htA, ui lenA, ui iRow );
void __vf MCDCol_delete( cdPMatrix MB, cdPMatrix MA,
                         ui htA, ui lenA, ui iCol );
void __vf MCDRow_insert( cdPMatrix MB, cdPMatrix MA, ui htB,
                         ui lenB, ui iRow, cdVector X );
void __vf MCDCol_insert( cdPMatrix MB, cdPMatrix MA, ui htB,
                         ui lenB, ui iCol, cdVector X );


/*****************    Basic arithmetic operations ***********************
     performed on one single row,  or one single column of any matrix,
     or on the diagonal of a square matrix                              */

void   __vf  MCDRow_neg( cdPMatrix MX, ui ht, ui len, ui iRow );
void   __vf  MCDCol_neg( cdPMatrix MX, ui ht, ui len, ui iCol );

void   __vf  MCDRow_conj( cdPMatrix MX, ui ht, ui len, ui iRow );
void   __vf  MCDCol_conj( cdPMatrix MX, ui ht, ui len, ui iCol );

void   __vf  MCDRow_addC( cdPMatrix MA, ui ht, ui len,
                         ui iRow, dComplex C );
void   __vf  MCDCol_addC( cdPMatrix MA, ui ht, ui len,
                         ui iCol, dComplex C );
void   __vf  MCDDia_addC( cdPMatrix MA, ui len, dComplex C );

void   __vf  MCDRow_subC( cdPMatrix MA, ui ht, ui len,
                         ui iRow, dComplex C );
void   __vf  MCDCol_subC( cdPMatrix MA, ui ht, ui len,
                         ui iCol, dComplex C );
void   __vf  MCDDia_subC( cdPMatrix MA, ui len, dComplex C );

void   __vf  MCDRow_addV( cdPMatrix MA, ui ht, ui len,
                         ui iRow, cdVector X );
void   __vf  MCDCol_addV( cdPMatrix MA, ui ht, ui len,
                         ui iCol, cdVector X );
void   __vf  MCDDia_addV( cdPMatrix MA, ui len, cdVector X );

void   __vf  MCDRow_subV( cdPMatrix MA, ui ht, ui len,
                         ui iRow, cdVector X );
void   __vf  MCDCol_subV( cdPMatrix MA, ui ht, ui len,
                         ui iCol, cdVector X );
void   __vf  MCDDia_subV( cdPMatrix MA, ui len, cdVector X );

void   __vf  MCDRow_subrC( cdPMatrix MA, ui ht, ui len,
                         ui iRow, dComplex C );
void   __vf  MCDCol_subrC( cdPMatrix MA, ui ht, ui len,
                         ui iCol, dComplex C );
void   __vf  MCDDia_subrC( cdPMatrix MA, ui len, dComplex C );

void   __vf  MCDRow_subrV( cdPMatrix MA, ui ht, ui len,
                         ui iRow, cdVector X );
void   __vf  MCDCol_subrV( cdPMatrix MA, ui ht, ui len,
                         ui iCol, cdVector X );
void   __vf  MCDDia_subrV( cdPMatrix MA, ui len, cdVector X );

void   __vf  MCDRow_mulC( cdPMatrix MA, ui ht, ui len,
                         ui iRow, dComplex C );
void   __vf  MCDCol_mulC( cdPMatrix MA, ui ht, ui len,
                         ui iCol, dComplex C );
void   __vf  MCDDia_mulC( cdPMatrix MA, ui len, dComplex C );

void   __vf  MCDRow_mulV( cdPMatrix MA, ui ht, ui len,
                         ui iRow, cdVector X );
void   __vf  MCDCol_mulV( cdPMatrix MA, ui ht, ui len,
                         ui iCol, cdVector X );
void   __vf  MCDDia_mulV( cdPMatrix MA, ui len, cdVector X );

void   __vf  MCDRow_divC( cdPMatrix MA, ui ht, ui len,
                         ui iRow, dComplex C );
void   __vf  MCDCol_divC( cdPMatrix MA, ui ht, ui len,
                         ui iCol, dComplex C );
void   __vf  MCDDia_divC( cdPMatrix MA, ui len, dComplex C );

void   __vf  MCDRow_divV( cdPMatrix MA, ui ht, ui len,
                         ui iRow, cdVector X );
void   __vf  MCDCol_divV( cdPMatrix MA, ui ht, ui len,
                         ui iCol, cdVector X );
void   __vf  MCDDia_divV( cdPMatrix MA, ui len, cdVector X );

void   __vf  MCDRow_divrC( cdPMatrix MA, ui ht, ui len,
                         ui iRow, dComplex C );
void   __vf  MCDCol_divrC( cdPMatrix MA, ui ht, ui len,
                         ui iCol, dComplex C );
void   __vf  MCDDia_divrC( cdPMatrix MA, ui len, dComplex C );

void   __vf  MCDRow_divrV( cdPMatrix MA, ui ht, ui len,
                         ui iRow, cdVector X );
void   __vf  MCDCol_divrV( cdPMatrix MA, ui ht, ui len,
                         ui iCol, cdVector X );
void   __vf  MCDDia_divrV( cdPMatrix MA, ui len, cdVector X );


/******  One-dimensional vector operations **********************
         performed along all rows or all columns simultaneously,
         or along the diagonal of a square matrix                */

void     __vf  MCDRows_absmax( dVector Y, cdPMatrix MA, ui ht, ui len );
void     __vf  MCDCols_absmax( dVector Y, cdPMatrix MA, ui ht, ui len );
double   __vf  MCDDia_absmax(  cdPMatrix MA, ui len );
void     __vf  MCDRows_absmin( dVector Y, cdPMatrix MA, ui ht, ui len );
void     __vf  MCDCols_absmin( dVector Y, cdPMatrix MA, ui ht, ui len );
double   __vf  MCDDia_absmin(  cdPMatrix MA, ui len );

void     __vf  MCDRows_maxReIm( cdVector Y, cdPMatrix MA, ui ht, ui len );
void     __vf  MCDCols_maxReIm( cdVector Y, cdPMatrix MA, ui ht, ui len );
void     __vf  MCDRows_minReIm( cdVector Y, cdPMatrix MA, ui ht, ui len );
void     __vf  MCDCols_minReIm( cdVector Y, cdPMatrix MA, ui ht, ui len );

void     __vf  MCDRows_absmaxReIm( cdVector Y, cdPMatrix MA, ui ht, ui len );
void     __vf  MCDCols_absmaxReIm( cdVector Y, cdPMatrix MA, ui ht, ui len );
void     __vf  MCDRows_absminReIm( cdVector Y, cdPMatrix MA, ui ht, ui len );
void     __vf  MCDCols_absminReIm( cdVector Y, cdPMatrix MA, ui ht, ui len );

void     __vf  MCDRows_cabsmax( cdVector Y, cdPMatrix MA, ui ht, ui len );
void     __vf  MCDCols_cabsmax( cdVector Y, cdPMatrix MA, ui ht, ui len );
void     __vf  MCDRows_cabsmin( cdVector Y, cdPMatrix MA, ui ht, ui len );
void     __vf  MCDCols_cabsmin( cdVector Y, cdPMatrix MA, ui ht, ui len );

void     __vf  MCDRows_sabsmax( cdVector Y, cdPMatrix MA, ui ht, ui len );
void     __vf  MCDCols_sabsmax( cdVector Y, cdPMatrix MA, ui ht, ui len );
void     __vf  MCDRows_sabsmin( cdVector Y, cdPMatrix MA, ui ht, ui len );
void     __vf  MCDCols_sabsmin( cdVector Y, cdPMatrix MA, ui ht, ui len );

void     __vf  MCDRows_sum( cdVector Y, cdPMatrix MA, ui ht, ui len );
void     __vf  MCDCols_sum( cdVector Y, cdPMatrix MA, ui ht, ui len );
void     __vf  MCDRows_prod(cdVector Y, cdPMatrix MA, ui ht, ui len );
void     __vf  MCDCols_prod(cdVector Y, cdPMatrix MA, ui ht, ui len );
#if defined __cplusplus && defined _CMATH_CLASSDEFS
} // the following functions cannot be extern "C", if dComplex is a class
#endif
dComplex __vf  MCDDia_maxReIm(  cdPMatrix MA, ui len );
dComplex __vf  MCDDia_minReIm(  cdPMatrix MA, ui len );
dComplex __vf  MCDDia_absmaxReIm(  cdPMatrix MA, ui len );
dComplex __vf  MCDDia_absminReIm(  cdPMatrix MA, ui len );
dComplex __vf  MCDDia_cabsmax(  cdPMatrix MA, ui len );
dComplex __vf  MCDDia_cabsmin(  cdPMatrix MA, ui len );
dComplex __vf  MCDDia_sabsmax(  cdPMatrix MA, ui len );
dComplex __vf  MCDDia_sabsmin(  cdPMatrix MA, ui len );
dComplex __vf  MCDDia_sum(  cdPMatrix MA, ui len );
dComplex __vf  MCDDia_prod( cdPMatrix MA, ui len );
#if defined __cplusplus && defined _CMATH_CLASSDEFS
extern "C" {
#endif

void  __vf  MCDRows_runsum( cdPMatrix MA, ui ht, ui len );
void  __vf  MCDCols_runsum( cdPMatrix MA, ui ht, ui len );
void  __vf  MCDRows_runprod( cdPMatrix MA, ui ht, ui len );
void  __vf  MCDCols_runprod( cdPMatrix MA, ui ht, ui len );

void  __vf  MCDRows_rotate( cdPMatrix MA, ui ht, ui len, ssize_t pos );
void  __vf  MCDCols_rotate( cdPMatrix MA, ui ht, ui len, ssize_t pos );
void  __vf  MCDRows_rotate_buf( cdPMatrix MA, ui ht, ui len, ssize_t pos, cdPMatrix MBuf );
void  __vf  MCDCols_rotate_buf( cdPMatrix MA, ui ht, ui len, ssize_t pos, cdPMatrix MBuf );
void  __vf  MCDRows_reflect( cdPMatrix MA, ui ht, ui len );
void  __vf  MCDCols_reflect( cdPMatrix MA, ui ht, ui len );
void  __vf  MCDRows_rev( cdPMatrix MA, ui ht, ui len );
void  __vf  MCDCols_rev( cdPMatrix MA, ui ht, ui len );

/********  Operations involving two rows or two colums of one matrix  *****/

void   __vf  MCDRows_exchange( cdPMatrix MA, ui ht, ui len,
                              ui i1, ui i2 );
void   __vf  MCDCols_exchange( cdPMatrix MA, ui ht, ui len,
                              ui i1, ui i2 );

void   __vf  MCDRows_add( cdPMatrix MA, ui ht, ui len,
                          ui destRow, ui sourceRow );
void   __vf  MCDCols_add( cdPMatrix MA, ui ht, ui len,
                          ui destCol, ui sourceCol );

void   __vf  MCDRows_sub( cdPMatrix MA, ui ht, ui len,
                          ui destRow, ui sourceRow );
void   __vf  MCDCols_sub( cdPMatrix MA, ui ht, ui len,
                          ui destCol, ui sourceCol );

void   __vf  MCDRows_Cadd( cdPMatrix MA, ui ht, ui len,
                           ui destRow, ui sourceRow, dComplex C );
void   __vf  MCDCols_Cadd( cdPMatrix MA, ui ht, ui len,
                           ui destCol, ui sourceCol, dComplex C );

void   __vf  MCDRows_lincomb( cdPMatrix MA, ui ht, ui len,
                              ui destRow,  dComplex  destC,
                              ui srceRow,  dComplex  srceC );
void   __vf  MCDCols_lincomb( cdPMatrix MA, ui ht, ui len,
                              ui destCol,  dComplex  destC,
                              ui srceCol,  dComplex  srceC );


/**************  Transposing and rotating a matrix **********************/

void  __vf  MCDtranspose( cdPMatrix MTr, cdPMatrix MA,
                          ui htTr, ui lenTr );
void  __vf  MCDhermconj( cdPMatrix MHConj, cdPMatrix MA,
                          ui htTr, ui lenTr );
void  __vf  MCDrotate90(  cdPMatrix MRot, cdPMatrix MA, ui htRot, ui lenRot );
#define     MCDrotate180( MRot, MA, htRot, lenRot ) \
                VCD_rev( MRot, MA, (htRot)*(lenRot) )
void  __vf  MCDrotate270( cdPMatrix MRot, cdPMatrix MA, ui htRot, ui lenRot );


/************************ Matrix Arithmetics *************************/

#define MCDaddM( MC, MA, MB, htA, lenA ) \
                 VCD_addV( MC, MA, MB, (htA)*(lenA) )
void __vf  MCDaddMT( cdPMatrix MC, cdPMatrix MA, cdPMatrix MB,
                     ui htA, ui lenA );
#define MCDsubM( MC, MA, MB, htA, lenA ) \
                 VCD_subV( MC, MA, MB, (htA)*(lenA) )
void __vf  MCDsubMT( cdPMatrix MC, cdPMatrix MA, cdPMatrix MB,
                     ui htA, ui lenA );
void __vf  MCDsubrMT( cdPMatrix MC, cdPMatrix MA, cdPMatrix MB,
                     ui htA, ui lenA );
#define MCDmulC( MB, MA, htA, lenA, C ) \
                 VCD_mulC( MB, MA, (htA)*(lenA), C )
#define MCDdivC( MB, MA, htA, lenA, C ) \
				 VCD_divC( MB, MA, (htA)*(lenA), C )
#define MCDmulReC( MB, MA, htA, lenA, CRe ) \
				 VCD_mulReC( MB, MA, (htA)*(lenA), CRe )
#define MCDdivReC( MB, MA, htA, lenA, CRe ) \
				 VCD_divReC( MB, MA, (htA)*(lenA), CRe )
#define MCDlincomb( MC, MA, MB, htA, lenA, CA, CB ) \
				 VCD_lincomb( MC, MA, MB, (htA)*(lenA), CA, CB )
void  __vf  MCDmulV( cdVector Y, cdPMatrix MA, cdVector X, ui htA, ui lenA );
void  __vf  MCDTmulV( cdVector Y, cdPMatrix MA, cdVector X, ui htA, ui lenA );
void  __vf  VCDmulM( cdVector Y, cdVector X, cdPMatrix MA, ui htA, ui lenA );
void  __vf  VCDmulMT( cdVector Y, cdVector X, cdPMatrix MA, ui htA, ui lenA );
void  __vf  MCDmulM( cdPMatrix MC, cdPMatrix MA, cdPMatrix MB,
					ui htA, ui lenA, ui lenB );
void  __vf  MCDmulMT( cdPMatrix MC, cdPMatrix MA, cdPMatrix MB,
					ui htA, ui lenA, ui htB );
void  __vf  MCDmulMH( cdPMatrix MC, cdPMatrix MA, cdPMatrix MB,
					ui htA, ui lenA, ui htB );
void  __vf  MCDTmulM( cdPMatrix MC, cdPMatrix MA, cdPMatrix MB,
					ui htA, ui lenA, ui lenB );
void  __vf  MCDHmulM( cdPMatrix MC, cdPMatrix MA, cdPMatrix MB,
					ui htA, ui lenA, ui lenB );
void  __vf  MCDTmulMT( cdPMatrix MC, cdPMatrix MA, cdPMatrix MB,
					ui htA, ui lenA, ui htB );
void  __vf  MCDTmulMH( cdPMatrix MC, cdPMatrix MA, cdPMatrix MB,
					ui htA, ui lenA, ui htB );
void  __vf  MCDdiamulM( cdPMatrix MC, cdPMatrix MADia, cdPMatrix MB,
					ui htB, ui lenB );
void  __vf  MCDdiamulMT( cdPMatrix MC, cdPMatrix MADia, cdPMatrix MB,
					ui htB, ui lenB );
void  __vf  MCDmulMdia( cdPMatrix MC, cdPMatrix MA, cdPMatrix MBDia,
					ui htA, ui lenA );
void  __vf  MCDTmulMdia( cdPMatrix MC, cdPMatrix MA, cdPMatrix MBDia,
					ui htA, ui lenA );

/*************************  Linear Algebra    *****************************/

int    __vf  MCDLUdecompose( cdPMatrix MLU,  uiVector Ind, cdPMatrix MA, ui len );

void   __vf  MCDLUsolve( cdVector X, cdPMatrix MLU, cdVector B, uiVector Ind,
						ui len );
void   __vf  MCDLUinv( cdPMatrix MInv, cdPMatrix MLU, uiVector Ind,
					  ui len );
#if defined __cplusplus && defined _CMATH_CLASSDEFS
} // the following functions cannot be extern "C", if fComplex is a class
#endif
dComplex __vf  MCDLUdet( cdPMatrix MLU, ui len, int permut );
#if defined __cplusplus && defined _CMATH_CLASSDEFS
extern "C" {
#endif
void   __vf  MCDLUimprove( cdVector X, cdVector B, cdPMatrix MA, cdPMatrix MLU,
                          uiVector Ind, ui len );

/* int    __vf  MCDSVdecompose( cdPMatrix MU, cdPMatrix MV, cdVector W, cdPMatrix MA,
                           ui htMA, ui lenA );
void   __vf  MCDSVsolve( cdVector X, cdPMatrix MU, cdPMatrix MV, cdVector W,
                       cdVector B, ui htU, ui lenU );  */

          /*  functions using LUD or SVD     */
int    __vf  MCDsolve( cdVector X, cdPMatrix MA, cdVector B, ui len );
                  /* ret.value != 0 signals error */
int    __vf  MCDinv( cdPMatrix MInv, cdPMatrix MA, ui len );
                 /* ret.value != 0 signals error */
#if defined __cplusplus && defined _CMATH_CLASSDEFS
} // the following functions cannot be extern "C", if fComplex is a class
#endif
dComplex __vf  MCDdet( cdPMatrix MA, ui len );
#if defined __cplusplus && defined _CMATH_CLASSDEFS
extern "C" {
#endif

/* int    __vf  MCDsolveBySVD( cdVector X, cdPMatrix MA, cdVector B,
                           ui ht, ui len );
              *  sizX = lenMA,  sizB = htA.  ret.value != 0 signals failure *
int    __vf  MCDsafeSolve( cdVector X, cdPMatrix MA, cdVector B, ui len );
              * ret.value 0: success via LUD; 1: success via SVD; -1: error */


/*************  Two-Dimensional Fourier-Transform Methods *****************/

void  __vf MCDpFFT( cdPMatrix MY, cdPMatrix MX, ui ht, ui len, int dir );
void  __vf MCDbFFT( cdPMatrix MY, cdPMatrix MX, ui ht, ui len, int dir, cdVector Buf );
void  __vf MCDpRows_FFT( cdPMatrix MY, cdPMatrix MX, ui ht, ui len, int dir );
void  __vf MCDpCols_FFT( cdPMatrix MY, cdPMatrix MX, ui ht, ui len, int dir );
void  __vf MCDbRows_FFT( cdPMatrix MY, cdPMatrix MX, ui ht, ui len, int dir, cdVector Buf );
void  __vf MCDbCols_FFT( cdPMatrix MY, cdPMatrix MX, ui ht, ui len, int dir, cdVector Buf );
void  __vf MCDpfilter( cdPMatrix MY, cdPMatrix MX, cdPMatrix MFlt, ui ht, ui len );

void  __vf MCDlFFT( cdPMatrix MY, cdPMatrix MX, ui ht, ui len, int dir );
void  __vf MCDlfilter( cdPMatrix MY, cdPMatrix MX, cdPMatrix MFlt,
					   ui ht, ui len );
void  __vf MCDlRows_FFT( cdPMatrix MY, cdPMatrix MX, ui ht, ui len, int dir );
void  __vf MCDlCols_FFT( cdPMatrix MY, cdPMatrix MX, ui ht, ui len, int dir );
void  __vf MCDsFFT( cdPMatrix MY, cdPMatrix MX, ui ht, ui len, int dir );
void  __vf MCDsfilter( cdPMatrix MY, cdPMatrix MX, cdPMatrix MFlt,
					   ui ht, ui len );
void  __vf MCDsRows_FFT( cdPMatrix MY, cdPMatrix MX, ui ht, ui len, int dir );
void  __vf MCDsCols_FFT( cdPMatrix MY, cdPMatrix MX, ui ht, ui len, int dir );

	  /*************  Input and Output  ****************/

#define MCDprint( MA, ht, len )  MCDfprint( stdout, MA, ht, len, 80 )
void __vf  MCDfprint( FILE _VFAR *stream, cdPMatrix MA, ui ht, ui len, unsigned linewidth );
void __vf  MCDcprint( cdPMatrix MA, ui ht, ui len );
void __vf  MCDwrite( FILE _VFAR *stream, cdPMatrix X, ui ht, ui len  );
#if !((defined __BORLANDC__) && (__BORLANDC__ < 0x710))
		/* modern compiler versions:  */
	void __vf MCDread( cdPMatrix X, ui ht, ui len, FILE _VFAR *stream );
#else /* older Borland compiler versions need separate implementation */
	void __vf MCDread1( cdPMatrix X, ui ht, ui len, FILE _VFAR *stream );
	#define MCDread  MCDread1
#endif
#define MCDstore( str, MA, ht, len ) VCD_store( str, MA, (len)*(ht) )
#define MCDrecall( MA, ht, len, str) VCD_recall( MA, (len)*(ht), str)

#ifdef __cplusplus
}  // end of extern "C"
#endif
#endif /* __MCDSTD_H */
