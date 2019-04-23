/*  MCFstd.h

  matrix management functions:
  manipulations on matrices of data type "fComplex"
  (single-precision complex numbers)

  Copyright (c) 1996-2017 by OptiCode - Dr. Martin Sander Software Dev.
  All Rights Reserved.
*/

#if !defined( __MCFSTD_H )
#define __MCFSTD_H
#if !defined( __MATLIB_H )
   #include <MatLib.h>
#endif
#if !defined( __VCFSTD_H )
   #include <VCFstd.h>
#endif
#if !defined( __VCFMATH_H )
   #include <VCFmath.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif

/*************   Dynamic Generation of Matrices   ************************/

cfMatrix __vf  MCF_matrix(  ui ht, ui len );
cfMatrix __vf  MCF_matrix0( ui ht, ui len );
#if defined (_MSC_VER) && defined (_DEBUG)
    cfMatrix __vf  MCF_matrix_dbg(  ui ht, ui len );
    cfMatrix __vf  MCF_matrix0_dbg( ui ht, ui len );
    #if defined (_INC_CRTDBG) && defined (_CRTDBG_MAP_ALLOC) 
	    /* Automatic mapping for memory-leak detection by CRT debugging switched on? */ 
        #define MCF_matrix  MCF_matrix_dbg
        #define MCF_matrix0 MCF_matrix0_dbg
    #endif
#else
    #define MCF_matrix_dbg  MCF_matrix
    #define MCF_matrix0_dbg MCF_matrix0
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

#define MCF_getElement( y, MA, ht, len, m, n ) MCFgetElement( y, (MA)[0], ht, len, m, n )
#define MCF_setElement( MA, ht, len, m, n, C ) MCFsetElement( (MA)[0], ht, len, m, n, C )
#define MCF_Pelement( MA, ht, len, m, n ) MCFPelement( (MA)[0], ht, len, m, n )
                     /* returns a pointer to MA[m][n]. */
#define MCF_element( MA, ht, len, m, n ) *MCFPelement( (MA)[0], ht, len, m, n )
                     /* dereferenced pointer */

 /****************  Initialization  ***************************************

    To initialize all elements of a matrix with the same value,
    or to perform arithmetic operations on all elements simultaneously,
    refer to the functions of VectorLib, declared in <VCFstd.h>, <VCFmath.h>.
    In order to use the VectorLib functions, utilize the feature that
    the whole matrix occupies one contiguous area in memory: pass the
    address of the first row to the desired vector function, the size
    of the "vector" being len * ht.
    For example, initialize all elements of the matrix MA with {1.0, 0.0}
    (this is *NOT* the identity matrix)  by calling
        VCF_equ1( (MA)[0], len * ht );
*/

#define MCF_equ0( MA, ht, len )            VCF_equ0( (MA)[0], (ht)*(len) )
#define MCF_equ1( MA, len )                MCFequ1( (MA)[0], len )  /* identity matrix */
#define MCF_equm1( MA, len )               MCFequm1( (MA)[0], len )  /* neg. identity matrix */
#define MCF_randomLC( MA, ht, len, seed, Min, Max, state ) \
                                           VCF_randomLC( (MA)[0], (ht)*(len), seed, Min, Max, state )
#define MCF_random( MA, ht, len, seed, Min, Max ) \
                                           VCF_random( (MA)[0], (ht)*(len), seed, Min, Max )
#define MCF_outerprod( MA, X, Y, ht, len ) MCFouterprod( (MA)[0], X, Y, ht, len )
                       /* sizX=ht, sizY=len */
#define MCF_Row_equ0( MA, ht, len, iRow ) MCFRow_equ0( (MA)[0], ht, len, iRow )
#define MCF_Col_equ0( MA, ht, len, iCol ) MCFCol_equ0( (MA)[0], ht, len, iCol )
#define MCF_Dia_equ0( MA, len )           MCFDia_equ0( (MA)[0], len )
#define MCF_Row_equC( MA, ht, len, iRow, C ) \
                                        MCFRow_equC( (MA)[0], ht, len, iRow, C )
#define MCF_Col_equC( MA, ht, len, iCol, C ) \
                                        MCFCol_equC( (MA)[0], ht, len, iCol, C )
#define MCF_Dia_equC( MA, len, C )       MCFDia_equC( (MA)[0], len, C )

#define MCF_Row_equV( MA, ht, len, iRow, X ) \
                                        MCFRow_equV( (MA)[0], ht, len, iRow, X )
#define MCF_Col_equV( MA, ht, len, iCol, X ) \
                                        MCFCol_equV( (MA)[0], ht, len, iCol, X )
#define MCF_Dia_equV( MA, len, X )       MCFDia_equV( (MA)[0], len, X )

#define MCF_Trd_equM( MA, MTrd, len )    MCFTrd_equM( (MA)[0], (MTrd)[0], len )
#define MCF_Trd_extract( MTrd, MA, len ) MCFTrd_extract( (MTrd)[0], (MA)[0], len )

#define MCF_equM( MB, MA, ht, len )  VCF_equV( (MB)[0], (MA)[0], ((ui)(len))*(ht) )
#define MCF_neg( MB, MA, ht, len )   VCF_neg( (MB)[0], (MA)[0], ((ui)(len))*(ht) )
#define MCF_conj( MB, MA, ht, len )  VCF_conj( (MB)[0], (MA)[0], ((ui)(len))*(ht) )

#define MCF_UequL( MA, len ) MCFUequL( (MA)[0], len )
#define MCF_LequU( MA, len ) MCFLequU( (MA)[0], len )
         /* copy lower-diagonal elements into upper-diagonal
           (or vice versa) by index-reflection, so as to
           get a symmetric matrix    */

            /* data-type conversions:  */
#define M_CEtoCF( MCF, MCE, ht, len ) V_CEtoCF( (MCF)[0], (MCE)[0], (ht)*(len) )
#define M_CFtoCE( MCE, MCF, ht, len ) V_CFtoCE( (MCE)[0], (MCF)[0], (ht)*(len) )
#define M_CDtoCF( MCF, MCD, ht, len ) V_CDtoCF( (MCF)[0], (MCD)[0], (ht)*(len) )
#define M_CFtoCD( MCD, MCF, ht, len ) V_CFtoCD( (MCD)[0], (MCF)[0], (ht)*(len) )
#define MF_CtoRe( MY, MCX, ht, len )  VF_CtoRe( (MY)[0],  (MCX)[0], (ht)*(len) )
#define MF_CtoIm( MY, MCX, ht, len )  VF_CtoIm( (MY)[0],  (MCX)[0], (ht)*(len) )
#define MF_CtoReIm( MYRe, MYIm, MCX, ht, len )  VF_CtoReIm( (MYRe)[0], (MYIm)[0], (MCX)[0], (ht)*(len) )
#define MF_RetoC( MCY, MX, ht, len )  VF_RetoC( (MCY)[0], (MX)[0],  (ht)*(len) )
#define MF_ImtoC( MCY, MX, ht, len )  VF_ImtoC( (MCY)[0], (MX)[0],  (ht)*(len) )
#define MF_ReImtoC( MCY, MXRe, MXIm, ht, len )  VF_ReImtoC( (MCY)[0], (MXRe)[0], (MXIm)[0], (ht)*(len) )

/********  Extracting a submatrix and copying a submatrix back  *********/

#define MCF_submatrix( MSub, subHt, subLen, \
                       MSrce, srceHt, srceLen, \
                       firstRowInCol, sampInCol, firstColInRow, sampInRow ) \
               MCFsubmatrix(  (MSub)[0], subHt, subLen, \
                              (MSrce)[0], srceHt, srceLen, \
                              firstRowInCol, sampInCol, firstColInRow, sampInRow )

#define MCF_submatrix_equM( MDest, destHt, destLen, \
                            firstRowInCol, sampInCol, firstColInRow, sampInRow, \
                            MSrce, srceHt, srceLen ) \
               MCFsubmatrix_equM(  (MDest)[0], destHt, destLen, \
                             firstRowInCol, sampInCol, firstColInRow, sampInRow, \
                             (MSrce)[0], srceHt, srceLen )

#define MCF_equMblock( MSub, subHt, subLen, \
                      MSrce, srceHt, srceLen, \
                      firstRowInCol, firstColInRow ) \
               MCFequMblock(  (MSub)[0], subHt, subLen, \
                             (MSrce)[0], srceHt, srceLen, \
                             firstRowInCol, firstColInRow )

#define MCF_block_equM( MDest, destHt, destLen, \
                       firstRowInCol, firstColInRow, \
                       MSrce, srceHt, srceLen ) \
               MCFblock_equM( (MDest)[0], destHt, destLen, \
                             firstRowInCol, firstColInRow, \
                             (MSrce)[0], srceHt, srceLen )

#define MCF_equMblockT( MSub, subHt, subLen, \
                      MSrce, srceHt, srceLen, \
                      firstRowInCol, firstColInRow ) \
               MCFequMblockT( (MSub)[0], subHt, subLen, \
                             (MSrce)[0], srceHt, srceLen, \
                             firstRowInCol, firstColInRow )

#define MCF_block_equMT( MDest, destHt, destLen, \
                       firstRowInCol, firstColInRow, \
                       MSrce, srceHt, srceLen ) \
               MCFblock_equMT( (MDest)[0], destHt, destLen, \
                             firstRowInCol, firstColInRow, \
                             (MSrce)[0], srceHt, srceLen )

/*****   Extracting a single row or a single column or the diagonal  ******
 *       and storing it into a vector                                     */

#define MCF_Row_extract( Y, MA, ht, len, iRow ) \
                                     MCFRow_extract( Y, (MA)[0], ht, len, iRow )
#define MCF_Col_extract( Y, MA, ht, len, iCol ) \
                                     MCFCol_extract( Y, (MA)[0], ht, len, iCol )
#define MCF_Dia_extract( Y, MA, len ) MCFDia_extract( Y, (MA)[0], len )


/**************  Deleting or inserting a row or a column   ***************/

#define MCF_Row_delete( MB, MA, htA, lenA, iRow ) \
                           MCFRow_delete( (MB)[0], (MA)[0], htA, lenA, iRow )
#define MCF_Col_delete( MB, MA, htA, lenA, iCol ) \
                           MCFCol_delete( (MB)[0], (MA)[0], htA, lenA, iCol )
#define MCF_Row_insert( MB, MA, htB, lenB, iRow, X ) \
                           MCFRow_insert( (MB)[0], (MA)[0], htB, lenB, iRow, X )
#define MCF_Col_insert( MB, MA, htB, lenB, iCol, X ) \
                           MCFCol_insert( (MB)[0], (MA)[0], htB, lenB, iCol, X )


/*****************    Basic arithmetic operations *********************
                      performed on one single row,
                      or one single column of any matrix,
                      or on the diagonal of a square matrix

    Note: In contrast to the analogous VectorLib functions, the operations
    are performed in-place, i.e. the input matrix itself is changed  */

#define MCF_Row_neg( MA, ht, len, iRow ) MCFRow_neg( (MA)[0], ht, len, iRow )
#define MCF_Col_neg( MA, ht, len, iCol ) MCFCol_neg( (MA)[0], ht, len, iCol )

#define MCF_Row_conj( MA, ht, len, iRow ) MCFRow_conj( (MA)[0], ht, len, iRow )
#define MCF_Col_conj( MA, ht, len, iCol ) MCFCol_conj( (MA)[0], ht, len, iCol )

#define MCF_Row_addC( MA, ht, len, iRow, C ) \
                                     MCFRow_addC( (MA)[0], ht, len, iRow, C )
#define MCF_Col_addC( MA, ht, len, iCol, C ) \
                                     MCFCol_addC( (MA)[0], ht, len, iCol, C )
#define MCF_Dia_addC( MA, len, C )   MCFDia_addC( (MA)[0], len, C )

#define MCF_Row_addV( MA, ht, len, iRow, X ) \
                                     MCFRow_addV( (MA)[0], ht, len, iRow, X )
#define MCF_Col_addV( MA, ht, len, iCol, X ) \
                                     MCFCol_addV( (MA)[0], ht, len, iCol, X )
#define MCF_Dia_addV( MA, len, X )   MCFDia_addV( (MA)[0], len, X )

#define MCF_Row_subC( MA, ht, len, iRow, C ) \
                                     MCFRow_subC( (MA)[0], ht, len, iRow, C )
#define MCF_Col_subC( MA, ht, len, iCol, C ) \
                                     MCFCol_subC( (MA)[0], ht, len, iCol, C )
#define MCF_Dia_subC( MA, len, C )   MCFDia_subC( (MA)[0], len, C )

#define MCF_Row_subV( MA, ht, len, iRow, X ) \
                                     MCFRow_subV( (MA)[0], ht, len, iRow, X )
#define MCF_Col_subV( MA, ht, len, iCol, X ) \
                                     MCFCol_subV( (MA)[0], ht, len, iCol, X )
#define MCF_Dia_subV( MA, len, X )   MCFDia_subV( (MA)[0], len, X )

#define MCF_Row_subrC( MA, ht, len, iRow, C ) \
                                     MCFRow_subrC( (MA)[0], ht, len, iRow, C )
#define MCF_Col_subrC( MA, ht, len, iCol, C ) \
                                     MCFCol_subrC( (MA)[0], ht, len, iCol, C )
#define MCF_Dia_subrC( MA, len, C )  MCFDia_subrC( (MA)[0], len, C )

#define MCF_Row_subrV( MA, ht, len, iRow, X ) \
                                     MCFRow_subrV( (MA)[0], ht, len, iRow, X )
#define MCF_Col_subrV( MA, ht, len, iCol, X ) \
                                     MCFCol_subrV( (MA)[0], ht, len, iCol, X )
#define MCF_Dia_subrV( MA, len, X )  MCFDia_subrV( (MA)[0], len, X )

#define MCF_Row_mulC( MA, ht, len, iRow, C ) \
                                     MCFRow_mulC( (MA)[0], ht, len, iRow, C )
#define MCF_Col_mulC( MA, ht, len, iCol, C ) \
                                     MCFCol_mulC( (MA)[0], ht, len, iCol, C )
#define MCF_Dia_mulC( MA, len, C )   MCFDia_mulC( (MA)[0], len, C )

#define MCF_Row_mulV( MA, ht, len, iRow, X ) \
                                     MCFRow_mulV( (MA)[0], ht, len, iRow, X )
#define MCF_Col_mulV( MA, ht, len, iCol, X ) \
                                     MCFCol_mulV( (MA)[0], ht, len, iCol, X )
#define MCF_Dia_mulV( MA, len, X )   MCFDia_mulV( (MA)[0], len, X )

#define MCF_Row_divC( MA, ht, len, iRow, C ) \
                                     MCFRow_divC( (MA)[0], ht, len, iRow, C )
#define MCF_Col_divC( MA, ht, len, iCol, C ) \
                                     MCFCol_divC( (MA)[0], ht, len, iCol, C )
#define MCF_Dia_divC( MA, len, C )   MCFDia_divC( (MA)[0], len, C )

#define MCF_Row_divV( MA, ht, len, iRow, X ) \
                                      MCFRow_divV( (MA)[0], ht, len, iRow, X )
#define MCF_Col_divV( MA, ht, len, iCol, X ) \
                                      MCFCol_divV( (MA)[0], ht, len, iCol, X )
#define MCF_Dia_divV( MA, len, X )    MCFDia_divV( (MA)[0], len, X )

#define MCF_Row_divrC( MA, ht, len, iRow, C ) \
                                      MCFRow_divrC( (MA)[0], ht, len, iRow, C )
#define MCF_Col_divrC( MA, ht, len, iCol, C ) \
                                      MCFCol_divrC( (MA)[0], ht, len, iCol, C )
#define MCF_Dia_divrC( MA, len, C )   MCFDia_divrC( (MA)[0], len, C )

#define MCF_Row_divrV( MA, ht, len, iRow, X ) \
                                      MCFRow_divrV( (MA)[0], ht, len, iRow, X )
#define MCF_Col_divrV( MA, ht, len, iCol, X ) \
                                      MCFCol_divrV( (MA)[0], ht, len, iCol, X )
#define MCF_Dia_divrV( MA, len, X )   MCFDia_divrV( (MA)[0], len, X )


/******  One-dimensional vector operations **********************
         performed along all rows or all columns simultaneously,
         or along the diagonal of a square matrix                */

#define MCF_Rows_absmax( Y, MA, ht, len )  MCFRows_absmax( Y, (MA)[0], ht, len )
#define MCF_Cols_absmax( Y, MA, ht, len )  MCFCols_absmax( Y, (MA)[0], ht, len )
#define MCF_Dia_absmax( MA, len )          MCFDia_absmax( (MA)[0], len )
#define MCF_Rows_absmin( Y, MA, ht, len )  MCFRows_absmin( Y, (MA)[0], ht, len )
#define MCF_Cols_absmin( Y, MA, ht, len )  MCFCols_absmin( Y, (MA)[0], ht, len )
#define MCF_Dia_absmin( MA, len )          MCFDia_absmin( (MA)[0], len )

#define MCF_Rows_maxReIm( Y, MA, ht, len ) MCFRows_maxReIm( Y, (MA)[0], ht, len )
#define MCF_Cols_maxReIm( Y, MA, ht, len ) MCFCols_maxReIm( Y, (MA)[0], ht, len )
#define MCF_Dia_maxReIm( MA, len )         MCFDia_maxReIm( (MA)[0], len )
#define MCF_Rows_minReIm( Y, MA, ht, len ) MCFRows_minReIm( Y, (MA)[0], ht, len )
#define MCF_Cols_minReIm( Y, MA, ht, len ) MCFCols_minReIm( Y, (MA)[0], ht, len )
#define MCF_Dia_minReIm( MA, len )         MCFDia_minReIm( (MA)[0], len )

#define MCF_Rows_absmaxReIm( Y, MA, ht, len ) MCFRows_absmaxReIm( Y, (MA)[0], ht, len )
#define MCF_Cols_absmaxReIm( Y, MA, ht, len ) MCFCols_absmaxReIm( Y, (MA)[0], ht, len )
#define MCF_Dia_absmaxReIm( MA, len )         MCFDia_absmaxReIm( (MA)[0], len )
#define MCF_Rows_absminReIm( Y, MA, ht, len ) MCFRows_absminReIm( Y, (MA)[0], ht, len )
#define MCF_Cols_absminReIm( Y, MA, ht, len ) MCFCols_absminReIm( Y, (MA)[0], ht, len )
#define MCF_Dia_absminReIm( MA, len )         MCFDia_absminReIm( (MA)[0], len )

#define MCF_Rows_cabsmax( Y, MA, ht, len ) MCFRows_cabsmax( Y, (MA)[0], ht, len )
#define MCF_Cols_cabsmax( Y, MA, ht, len ) MCFCols_cabsmax( Y, (MA)[0], ht, len )
#define MCF_Dia_cabsmax( MA, len )         MCFDia_cabsmax( (MA)[0], len )
#define MCF_Rows_cabsmin( Y, MA, ht, len ) MCFRows_cabsmin( Y, (MA)[0], ht, len )
#define MCF_Cols_cabsmin( Y, MA, ht, len ) MCFCols_cabsmin( Y, (MA)[0], ht, len )
#define MCF_Dia_cabsmin( MA, len )         MCFDia_cabsmin( (MA)[0], len )

#define MCF_Rows_sabsmax( Y, MA, ht, len ) MCFRows_sabsmax( Y, (MA)[0], ht, len )
#define MCF_Cols_sabsmax( Y, MA, ht, len ) MCFCols_sabsmax( Y, (MA)[0], ht, len )
#define MCF_Dia_sabsmax( MA, len )         MCFDia_sabsmax( (MA)[0], len )
#define MCF_Rows_sabsmin( Y, MA, ht, len ) MCFRows_sabsmin( Y, (MA)[0], ht, len )
#define MCF_Cols_sabsmin( Y, MA, ht, len ) MCFCols_sabsmin( Y, (MA)[0], ht, len )
#define MCF_Dia_sabsmin( MA, len )         MCFDia_sabsmin( (MA)[0], len )

#define MCF_Rows_sum( Y, MA, ht, len )     MCFRows_sum( Y, (MA)[0], ht, len )
#define MCF_Cols_sum( Y, MA, ht, len )     MCFCols_sum( Y, (MA)[0], ht, len )
#define MCF_Dia_sum(  MA, len )            MCFDia_sum( (MA)[0], len )
#define MCF_Rows_prod( Y, MA, ht, len )    MCFRows_prod( Y, (MA)[0], ht, len )
#define MCF_Cols_prod( Y, MA, ht, len )    MCFCols_prod( Y, (MA)[0], ht, len )
#define MCF_Dia_prod(  MA, len )           MCFDia_prod( (MA)[0], len )

#define MCF_Rows_runsum( MA, ht, len )     MCFRows_runsum( (MA)[0], ht, len )
#define MCF_Cols_runsum( MA, ht, len )     MCFCols_runsum( (MA)[0], ht, len )
#define MCF_Rows_runprod( MA, ht, len )    MCFRows_runprod( (MA)[0], ht, len )
#define MCF_Cols_runprod( MA, ht, len )    MCFCols_runprod( (MA)[0], ht, len )

#define MCF_Rows_rotate( MA, ht, len, pos) MCFRows_rotate( (MA)[0], ht, len, pos )
#define MCF_Cols_rotate( MA, ht, len, pos) MCFCols_rotate( (MA)[0], ht, len, pos )
#define MCF_Rows_rotate_buf( MA, ht, len, pos, MBuf) MCFRows_rotate_buf( (MA)[0], ht, len, pos, (MBuf)[0] )
#define MCF_Cols_rotate_buf( MA, ht, len, pos, MBuf) MCFCols_rotate_buf( (MA)[0], ht, len, pos, (MBuf)[0] )
#define MCF_Rows_reflect( MA, ht, len)     MCFRows_reflect( (MA)[0], ht, len )
#define MCF_Cols_reflect( MA, ht, len)     MCFCols_reflect( (MA)[0], ht, len )
#define MCF_Rows_rev( MA, ht, len)         MCFRows_rev( (MA)[0], ht, len )
#define MCF_Cols_rev( MA, ht, len)         MCFCols_rev( (MA)[0], ht, len )

/********  Operations involving two rows or two colums of one matrix  *****/

#define MCF_Rows_exchange( MA, ht, len, row1, row2 ) \
                             MCFRows_exchange( (MA)[0], ht, len, row1, row2 )
#define MCF_Cols_exchange( MA, ht, len, col1, col2 ) \
                             MCFCols_exchange( (MA)[0], ht, len, col1, col2 )

#define MCF_Rows_add( MA, ht, len, destRow, srceRow ) \
                             MCFRows_add( (MA)[0], ht, len, destRow, srceRow )
#define MCF_Cols_add( MA, ht, len, destCol, srceCol ) \
                             MCFCols_add( (MA)[0], ht, len, destCol, srceCol )
                         /* dest[i] += source[i]  */

#define MCF_Rows_sub( MA, ht, len, destRow, srceRow ) \
                             MCFRows_sub( (MA)[0], ht, len, destRow, srceRow )
#define MCF_Cols_sub( MA, ht, len, destCol, srceCol ) \
                             MCFCols_sub( (MA)[0], ht, len, destCol, srceCol )
                         /* dest[i] -= source[i]  */

#define MCF_Rows_Cadd( MA, ht, len, destRow, srceRow, C ) \
                          MCFRows_Cadd( (MA)[0], ht, len, destRow, srceRow, C )
#define MCF_Cols_Cadd( MA, ht, len, destCol, srceCol, C ) \
                          MCFCols_Cadd( (MA)[0], ht, len, destCol, srceCol, C )
                         /* dest[i] += C * source[i]  */

#define MCF_Rows_lincomb( MA, ht, len, destRow, destC, srceRow, srceC ) \
            MCFRows_lincomb( (MA)[0], ht, len, destRow, destC, srceRow, srceC )
#define MCF_Cols_lincomb( MA, ht, len, destCol, destC, srceCol, srceC ) \
            MCFCols_lincomb( (MA)[0], ht, len, destCol, destC, srceCol, srceC )
  /*  linear combination: dest[i] = destC * dest[i] + sourceC * source[i] */


/*****************  Transposing and rotating a matrix ********************/

#define MCF_transpose( MTr, MA, htTr, lenTr ) \
             MCFtranspose( (MTr)[0], (MA)[0], htTr, lenTr )
       /*  the dimensions htTr, lenTr are those of the transposed matrix,
           not of the original!                */
#define MCF_hermconj( MHConj, MA, htTr, lenTr ) \
             MCFhermconj( (MHConj)[0], (MA)[0], htTr, lenTr )
#define MCF_rotate90( MRot, MA, htRot, lenRot ) \
             MCFrotate90( (MRot)[0], (MA)[0], htRot, lenRot )
#define MCF_rotate180( MRot, MA, htRot, lenRot ) \
             VCF_rev( (MRot)[0], (MA)[0], (htRot)*(lenRot) )
#define MCF_rotate270( MRot, MA, htRot, lenRot ) \
             MCFrotate270( (MRot)[0], (MA)[0], htRot, lenRot )

/************************ Matrix Arithmetics *************************/

#define MCF_addM( MC, MA, MB, htA, lenA ) \
                 VCF_addV( (MC)[0], (MA)[0], (MB)[0], (htA)*(lenA) )
#define MCF_addMT( MC, MA, MB, htA, lenA ) \
                 MCFaddMT( (MC)[0], (MA)[0], (MB)[0], htA, lenA )
#define MCF_subM( MC, MA, MB, htA, lenA ) \
                 VCF_subV( (MC)[0], (MA)[0], (MB)[0], (htA)*(lenA) )
#define MCF_subMT( MC, MA, MB, htA, lenA ) \
                 MCFsubMT( (MC)[0], (MA)[0], (MB)[0], htA, lenA )
#define MCF_subrMT( MC, MA, MB, htA, lenA ) \
                 MCFsubrMT( (MC)[0], (MA)[0], (MB)[0], htA, lenA )
#define MCF_mulC( MB, MA, htA, lenA, C ) \
                 VCF_mulC( (MB)[0], (MA)[0], (htA)*(lenA), C )
#define MCF_divC( MB, MA, htA, lenA, C ) \
                 VCF_divC( (MB)[0], (MA)[0], (htA)*(lenA), C )
#define MCF_mulReC( MB, MA, htA, lenA, CRe ) \
                 VCF_mulReC( (MB)[0], (MA)[0], (htA)*(lenA), CRe )
#define MCF_divReC( MB, MA, htA, lenA, CRe ) \
                 VCF_divReC( (MB)[0], (MA)[0], (htA)*(lenA), CRe )
#define MCF_lincomb( MC, MA, MB, htA, lenA, CA, CB ) \
                 VCF_lincomb( (MC)[0], (MA)[0], (MB)[0], (htA)*(lenA), CA, CB )

#define MCF_mulV( Y, MA, X, htA, lenA ) \
                    MCFmulV( Y, (MA)[0], X, htA, lenA )
                          /*  Y = MA * X.  sizX=lenA, sizY=htA
                              both X and Y are column-vectors    */
#define MCF_TmulV( Y, MA, X, htA, lenA ) \
                    MCFTmulV( Y, (MA)[0], X, htA, lenA )
                          /*  Y = MAT * X.  sizX=htA, sizY=lenA
                              both X and Y are column-vectors    */
#define VCF_mulM( Y, X, MA, htA, lenA ) \
                    VCFmulM( Y, X, (MA)[0], htA, lenA )
                         /*  Y = X * MA.  sizX=htA, sizY=lenA
                             both X and Y are row-vectors.
                             Mind the prefix: VCF_ (not MCF_)    */
#define VCF_mulMT( Y, X, MA, htA, lenA ) \
                    VCFmulMT( Y, X, (MA)[0], htA, lenA )
                         /*  Y = X * MAT.  sizX=lenA, sizY=htA
                             both X and Y are row-vectors.   */
#define MCF_mulM( MC, MA, MB, htA, lenA, lenB ) \
                    MCFmulM( (MC)[0], (MA)[0], (MB)[0], htA, lenA, lenB )
                         /*  MC = MA * MB.  htB=lenA, htC=htA, lenC=lenB */
#define MCF_mulMT( MC, MA, MB, htA, lenA, htB ) \
                    MCFmulMT( (MC)[0], (MA)[0], (MB)[0], htA, lenA, htB )
                         /*  MC = MA * MBT.  lenB=lenA, htC=htA, lenC=htB */
#define MCF_mulMH( MC, MA, MB, htA, lenA, htB ) \
                    MCFmulMH( (MC)[0], (MA)[0], (MB)[0], htA, lenA, htB )
                         /*  MC = MA * MBH.  lenB=lenA, htC=htA, lenC=htB */
#define MCF_TmulM( MC, MA, MB, htA, lenA, lenB ) \
                    MCFTmulM( (MC)[0], (MA)[0], (MB)[0], htA, lenA, lenB )
                         /*  MC = MAT * MB.  htB=htA, htC=lenA, lenC=lenB */
#define MCF_HmulM( MC, MA, MB, htA, lenA, lenB ) \
                    MCFHmulM( (MC)[0], (MA)[0], (MB)[0], htA, lenA, lenB )
                         /*  MC = MAH * MB.  htB=htA, htC=lenA, lenC=lenB */
#define MCF_TmulMT( MC, MA, MB, htA, lenA, htB ) \
                    MCFTmulMT( (MC)[0], (MA)[0], (MB)[0], htA, lenA, htB )
                         /*  MC = MAT * MBT.  lenB=htA, htC=lenA, lenC=htB */
#define MCF_TmulMH( MC, MA, MB, htA, lenA, htB ) \
                    MCFTmulMH( (MC)[0], (MA)[0], (MB)[0], htA, lenA, htB )
                         /*  MC = MAT * MBH.  lenB=htA, htC=lenA, lenC=htB */
#define MCFdia_mulM(  MC, MADia, MB, htB, lenB )  MCFdiamulM(  (MC)[0], MADia, (MB)[0], htB, lenB )
#define MCFdia_mulMT( MC, MADia, MB, htB, lenB )  MCFdiamulMT( (MC)[0], MADia, (MB)[0], htB, lenB )
#define MCF_mulMdia(  MC, MA, MBDia, htA, lenA )  MCFmulMdia(  (MC)[0], (MA)[0], MBDia, htA, lenA )
#define MCF_TmulMdia( MC, MA, MBDia, htA, lenA )  MCFTmulMdia( (MC)[0], (MA)[0], MBDia, htA, lenA )

/*************************  Linear Algebra    *****************************/

   /*  The standard treatment of linear systems is based
       on LUD (matrix decomposition into Upper-triangular
       and Lower-triangular components). The result of the
       decomposition step is used for further operations.  */

#define MCF_LUdecompose( MLU, Ind, MA, len ) \
                    MCFLUdecompose( (MLU)[0], Ind, (MA)[0], len )
            /* returns "permut" = +-1 which is needed for MCF_LUdet.
               for singularities not cured by editing, permut is 0  */
int     __vf MCF_LUDresult( void );
    /* returns 0, if MCF_LUdecompose was successful;
       returns 1, if MA was (nearly) singular in MCF_LUdecompose.   */
void   __vf MCF_LUDsetEdit( float Thresh );
float  __vf MCF_LUDgetEdit( void );
     /*  Editing threshold valid for MCF_LUdecompose;
         may be used to work around singularities           */

#define MCF_LUsolve( X, MLU, B, Ind, len ) \
                    MCFLUsolve( X, (MLU)[0], B, Ind, len )
#define MCF_LUinv( MInv, MLU, Ind, len ) \
                    MCFLUinv( (MInv)[0], (MLU)[0], Ind, len )
#define MCF_LUdet( MLU, len, permut ) MCFLUdet( (MLU)[0], len, permut )
#define MCF_LUimprove( X, B, MA, MLU, Ind, len ) \
                      MCFLUimprove( X, B, (MA)[0], (MLU)[0], Ind, len )

    /****  Special treatment of over- or under-determined
           linear systems, i.e. of matrices with len != ht
           and of singular matrices:
           SVD (Singular Value Decomposition)       ****

#define MCF_SVdecompose( MU, MV, W, MA, htA, lenA ) \
                    MCFSVdecompose( (MU)[0], (MV)[0], W, (MA)[0], htA, lenA )
            *  sizB = htA,  sizX = sizW = htV = lenV = lenA *
#define MCF_SVsolve( X, MU, MV, W, B, htU, lenU ) \
                    MCFSVsolve( X, (MU)[0], (MV)[0], W, B, htU, lenU )
            *  lenU = lenA,  htU = max( lenA, htA ) as fed into
                MD_SVdecompose   *
void    __vf MCF_SVDsetEdit( float Thresh );
float   __vf MCF_SVDgetEdit( void );
   *  Override of the standard values for editing threshholds
       in MCF_SVsolve. Calling MCF_setEdit with Thresh=0.0 means
       that you do the necessary editing of W yourself
       before calling MD_SVsolve                           */

 /*****  "Easy-to-use" versions of the matrix functions
          using LUD or SVD.
          They allocate their own working space and rely
          on your setting of the editing threshold. In
          case of memory stress, you should better use the
          two-step methods declared above.            ***/
#define MCF_solve( X, MA, B, len ) \
                    MCFsolve( X, (MA)[0], B, len )
#define MCF_inv( MInv, MA, len ) \
                    MCFinv( (MInv)[0], (MA)[0], len )
#define MCF_det(  MA, len ) \
                    MCFdet( (MA)[0], len )
/* #define MCF_solveBySVD( X, MA, B, ht, len ) \
                    MCFsolveBySVD( X, (MA)[0], B, ht, len )
         *  sizX = len,  sizB = ht   *
#define MCF_safeSolve( X, MA, B, len ) \
                    MCFsafeSolve( X, (MA)[0], B, len ) */

/***************** Two-Dimensional Fourier-Transform Methods ************/

#define MCFp_FFT( MY, MX, ht, len, dir )     MCFpFFT( (MY)[0], (MX)[0], ht, len, dir )
#define MCFb_FFT( MY, MX, ht, len, dir, Buf )     MCFbFFT( (MY)[0], (MX)[0], ht, len, dir, Buf )
#define MCFp_Rows_FFT( MY, MX, ht, len, dir) MCFpRows_FFT( (MY)[0], (MX)[0], ht, len, dir )
#define MCFp_Cols_FFT( MY, MX, ht, len, dir) MCFpCols_FFT( (MY)[0], (MX)[0], ht, len, dir )
#define MCFb_Rows_FFT( MY, MX, ht, len, dir, Buf) MCFbRows_FFT( (MY)[0], (MX)[0], ht, len, dir, Buf )
#define MCFb_Cols_FFT( MY, MX, ht, len, dir, Buf) MCFbCols_FFT( (MY)[0], (MX)[0], ht, len, dir, Buf )
#define MCFp_filter( MY, MX, MFlt, ht, len ) MCFpfilter( (MY)[0], (MX)[0], (MFlt)[0], ht, len )

#define MCF_FFT         MCFp_FFT
#define MCF_Rows_FFT    MCFp_Rows_FFT
#define MCF_Cols_FFT    MCFp_Cols_FFT
#define MCF_filter      MCFp_filter
#define MCFFFT          MCFpFFT
#define MCFRows_FFT     MCFpRows_FFT
#define MCFCols_FFT     MCFpCols_FFT
#define MCFfilter       MCFpfilter

#define MCFl_FFT( MY, MX, ht, len, dir )     MCFlFFT( (MY)[0], (MX)[0], ht, len, dir )
#define MCFl_Rows_FFT( MY, MX, ht, len, dir) MCFlRows_FFT( (MY)[0], (MX)[0], ht, len, dir )
#define MCFl_Cols_FFT( MY, MX, ht, len, dir) MCFlCols_FFT( (MY)[0], (MX)[0], ht, len, dir )
#define MCFl_filter( MY, MX, MFlt, ht, len ) MCFlfilter( (MY)[0], (MX)[0], (MFlt)[0], ht, len )

#define MCFs_FFT( MY, MX, ht, len, dir )     MCFsFFT( (MY)[0], (MX)[0], ht, len, dir )
#define MCFs_Rows_FFT( MY, MX, ht, len, dir) MCFsRows_FFT( (MY)[0], (MX)[0], ht, len, dir )
#define MCFs_Cols_FFT( MY, MX, ht, len, dir) MCFsCols_FFT( (MY)[0], (MX)[0], ht, len, dir )
#define MCFs_filter( MY, MX, MFlt, ht, len ) MCFsfilter( (MY)[0], (MX)[0], (MFlt)[0], ht, len )

/**************************  Input and Output  **************************/

#define MCF_fprint( stream, MA, ht, len, linewidth ) \
                    MCFfprint( stream, (MA)[0], ht, len, linewidth )
#define MCF_print( MA, ht, len )  MCFfprint( stdout, (MA)[0], ht, len, 80 )
#define MCF_cprint( MA, ht, len ) MCFcprint( (MA)[0], ht, len )
  /*  MCF_print, MCF_cprint usable only for console applications! */

#define MCF_write( str, MA, ht, len )   MCFwrite( str, (MA)[0], ht, len )
#define MCF_read( MA, ht, len, str )    MCFread( (MA)[0], ht, len, str )
#define MCF_setWriteFormat              VCF_setWriteFormat
#define MCF_setWriteSeparate            VCF_setNWriteSeparate
                                   /* write and read in ascii format */
#define MCF_store( str, MA, ht, len )   VCF_store( str, (MA)[0], ((ui)(len))*(ht) )
#define MCF_recall( MA, ht, len, str)   VCF_recall( (MA)[0], ((ui)(len))*(ht), str)
                                  /* store and recall in binary format */


/*************************************************************************
 * Here are now the actual declarations of the functions used internally.*
 * These declarations may change in future versions of MatrixLib!        *
 * You should not care too much about them, except in the case you need  *
 * the actual address of a run-time function (see above). Under all      *
 * "normal" circumstances, use only the names defined above in the       *
 * macro section!                                                        *
 *************************************************************************/

void  __vf MCFgetElement( fComplex *y, cfPMatrix X, ui ht, ui len, ui m, ui n );
#if defined __cplusplus && defined _CMATH_CLASSDEFS && defined __BORLANDC__ && defined _WIN64
} // for C++Builder on Win64, the following function cannot be extern "C", if fComplex is a class
#endif
void  __vf MCFsetElement( cfPMatrix X, ui ht, ui len, ui m, ui n, fComplex C );
#if defined __cplusplus && defined _CMATH_CLASSDEFS && defined __BORLANDC__ && defined _WIN64
extern "C" { 
#endif
fComplex _VFAR * __vf MCFPelement( cfPMatrix X, ui ht, ui len, ui m, ui n );
                  /* pointer is normalized in memory model HUGE */
#define MCFelement( MA, ht, len, m, n ) (*MCFPelement( MA, ht, len, m, n ))

#define MCFequ0( MA, ht, len )    VCF_equ0( MA, (ht)*(len) )
void   __vf  MCFequ1( cfPMatrix MA, ui len );  /* identity matrix */
void   __vf  MCFequm1( cfPMatrix MA, ui len );  /* neg. identity matrix */
void   __vf  MCFouterprod( cfPMatrix MA, cfVector X,  cfVector Y,
                           ui ht, ui len );

void   __vf  MCFRow_equ0( cfPMatrix MA, ui ht, ui len,
                         ui iRow );
void   __vf  MCFCol_equ0( cfPMatrix MA, ui ht, ui len,
                         ui iCol );
void   __vf  MCFDia_equ0( cfPMatrix MA, ui len );

#if defined __cplusplus && defined _CMATH_CLASSDEFS && defined __BORLANDC__ && defined _WIN64
} // for C++Builder on Win64, the following functions cannot be extern "C", if fComplex is a class
#endif
void   __vf  MCFRow_equC( cfPMatrix MA, ui ht, ui len, ui iRow, fComplex C );
void   __vf  MCFCol_equC( cfPMatrix MA, ui ht, ui len, ui iCol, fComplex C );
void   __vf  MCFDia_equC( cfPMatrix MA, ui len, fComplex C );
#if defined __cplusplus && defined _CMATH_CLASSDEFS && defined __BORLANDC__ && defined _WIN64
extern "C" {
#endif

void   __vf  MCFRow_equV( cfPMatrix MA, ui ht, ui len,
                         ui iRow, cfVector X );
void   __vf  MCFCol_equV( cfPMatrix MA, ui ht, ui len,
                         ui iCol, cfVector X );
void   __vf  MCFDia_equV( cfPMatrix MA, ui len, cfVector X );

void   __vf  MCFTrd_equM( cfPMatrix MA, cfPMatrix MTrd, ui len );
void   __vf  MCFTrd_extract( cfPMatrix MTrd, cfPMatrix MA, ui len );

#define MCFequM( MB, MA, ht, len )  VCF_equV( MB, MA, (ht)*(len) )
#define MCFneg( MB, MA, ht, len )   VCF_neg( MB, MA, (ht)*(len) )
#define MCFconj( MB, MA, ht, len )  VCF_conj( MB, MA, (ht)*(len) )

void   __vf  MCFUequL( cfPMatrix MA, ui len );
void   __vf  MCFLequU( cfPMatrix MA, ui len );

/********  Extracting a submatrix and copying a submatrix back  *********/

void  __vf  MCFsubmatrix( cfPMatrix MSub,
                          ui subHt,  ui subLen,
                          cfPMatrix MSrce,
                          ui srceHt,  ui srceLen,
                          ui firstRowInCol,  ui sampInCol,
                          ui firstColInRow,  ui sampInRow );

void  __vf  MCFsubmatrix_equM( cfPMatrix MDest,
                               ui destHt,     ui destLen,
                               ui firstRowInCol,  ui sampInCol,
                               ui firstColInRow,  ui sampInRow,
                               cfPMatrix MSrce,
                               ui srceHt,     ui srceLen );

void  __vf  MCFequMblock( cfPMatrix MSub,
                          ui subHt,  ui subLen,
                          cfPMatrix MSrce,
                          ui srceHt,  ui srceLen,
                          ui firstRowInCol,  ui firstColInRow );

void  __vf  MCFblock_equM( cfPMatrix MDest,
                           ui destHt,     ui destLen,
                           ui firstRowInCol,  ui firstColInRow,
                           cfPMatrix MSrce,
                           ui srceHt,     ui srceLen );

void  __vf  MCFequMblockT( cfPMatrix MSub,
                          ui subHt,  ui subLen,
                          cfPMatrix MSrce,
                          ui srceHt,  ui srceLen,
                          ui firstRowInCol,  ui firstColInRow );

void  __vf  MCFblock_equMT( cfPMatrix MDest,
                           ui destHt,     ui destLen,
                           ui firstRowInCol,  ui firstColInRow,
                           cfPMatrix MSrce,
                           ui srceHt,     ui srceLen );


/*****   Extracting a single row or a single column or the diagonal  *****
 *       and storing it into a vector                                    */

void __vf MCFRow_extract( cfVector Y, cfPMatrix MA, ui ht, ui len,
                           ui iRow );
void __vf MCFCol_extract( cfVector Y, cfPMatrix MA, ui ht, ui len,
                           ui iCol );
void __vf MCFDia_extract( cfVector Y, cfPMatrix MA, ui len );

/**********  Deleting or inserting a row or a column *****************/

void __vf MCFRow_delete( cfPMatrix MB, cfPMatrix MA,
                         ui htA, ui lenA, ui iRow );
void __vf MCFCol_delete( cfPMatrix MB, cfPMatrix MA,
                         ui htA, ui lenA, ui iCol );
void __vf MCFRow_insert( cfPMatrix MB, cfPMatrix MA, ui htB,
                         ui lenB, ui iRow, cfVector X );
void __vf MCFCol_insert( cfPMatrix MB, cfPMatrix MA, ui htB,
                         ui lenB, ui iCol, cfVector X );


/*****************    Basic arithmetic operations ***********************
     performed on one single row,  or one single column of any matrix,
     or on the diagonal of a square matrix                              */

void   __vf  MCFRow_neg( cfPMatrix MX, ui ht, ui len, ui iRow );
void   __vf  MCFCol_neg( cfPMatrix MX, ui ht, ui len, ui iCol );

void   __vf  MCFRow_conj( cfPMatrix MX, ui ht, ui len, ui iRow );
void   __vf  MCFCol_conj( cfPMatrix MX, ui ht, ui len, ui iCol );

#if defined __cplusplus && defined _CMATH_CLASSDEFS && defined __BORLANDC__ && defined _WIN64
} // for C++Builder on Win64, the following functions cannot be extern "C", if fComplex is a class
#endif
void   __vf  MCFRow_addC( cfPMatrix MA, ui ht, ui len, ui iRow, fComplex C );
void   __vf  MCFCol_addC( cfPMatrix MA, ui ht, ui len, ui iCol, fComplex C );
void   __vf  MCFDia_addC( cfPMatrix MA, ui len, fComplex C );

void   __vf  MCFRow_subC( cfPMatrix MA, ui ht, ui len, ui iRow, fComplex C );
void   __vf  MCFCol_subC( cfPMatrix MA, ui ht, ui len, ui iCol, fComplex C );
void   __vf  MCFDia_subC( cfPMatrix MA, ui len, fComplex C );

void   __vf  MCFRow_subrC( cfPMatrix MA, ui ht, ui len, ui iRow, fComplex C );
void   __vf  MCFCol_subrC( cfPMatrix MA, ui ht, ui len, ui iCol, fComplex C );
void   __vf  MCFDia_subrC( cfPMatrix MA, ui len, fComplex C );

void   __vf  MCFRow_mulC( cfPMatrix MA, ui ht, ui len, ui iRow, fComplex C );
void   __vf  MCFCol_mulC( cfPMatrix MA, ui ht, ui len, ui iCol, fComplex C );
void   __vf  MCFDia_mulC( cfPMatrix MA, ui len, fComplex C );

void   __vf  MCFRow_divC( cfPMatrix MA, ui ht, ui len, ui iRow, fComplex C );
void   __vf  MCFCol_divC( cfPMatrix MA, ui ht, ui len, ui iCol, fComplex C );
void   __vf  MCFDia_divC( cfPMatrix MA, ui len, fComplex C );

void   __vf  MCFRow_divrC( cfPMatrix MA, ui ht, ui len, ui iRow, fComplex C );
void   __vf  MCFCol_divrC( cfPMatrix MA, ui ht, ui len, ui iCol, fComplex C );
void   __vf  MCFDia_divrC( cfPMatrix MA, ui len, fComplex C );

#if defined __cplusplus && defined _CMATH_CLASSDEFS && defined __BORLANDC__ && defined _WIN64
extern "C" {
#endif
void   __vf  MCFRow_addV( cfPMatrix MA, ui ht, ui len, ui iRow, cfVector X );
void   __vf  MCFCol_addV( cfPMatrix MA, ui ht, ui len, ui iCol, cfVector X );
void   __vf  MCFDia_addV( cfPMatrix MA, ui len, cfVector X );

void   __vf  MCFRow_subV( cfPMatrix MA, ui ht, ui len, ui iRow, cfVector X );
void   __vf  MCFCol_subV( cfPMatrix MA, ui ht, ui len, ui iCol, cfVector X );
void   __vf  MCFDia_subV( cfPMatrix MA, ui len, cfVector X );

void   __vf  MCFRow_subrV( cfPMatrix MA, ui ht, ui len, ui iRow, cfVector X );
void   __vf  MCFCol_subrV( cfPMatrix MA, ui ht, ui len, ui iCol, cfVector X );
void   __vf  MCFDia_subrV( cfPMatrix MA, ui len, cfVector X );

void   __vf  MCFRow_mulV( cfPMatrix MA, ui ht, ui len, ui iRow, cfVector X );
void   __vf  MCFCol_mulV( cfPMatrix MA, ui ht, ui len, ui iCol, cfVector X );
void   __vf  MCFDia_mulV( cfPMatrix MA, ui len, cfVector X );

void   __vf  MCFRow_divV( cfPMatrix MA, ui ht, ui len, ui iRow, cfVector X );
void   __vf  MCFCol_divV( cfPMatrix MA, ui ht, ui len, ui iCol, cfVector X );
void   __vf  MCFDia_divV( cfPMatrix MA, ui len, cfVector X );

void   __vf  MCFRow_divrV( cfPMatrix MA, ui ht, ui len, ui iRow, cfVector X );
void   __vf  MCFCol_divrV( cfPMatrix MA, ui ht, ui len, ui iCol, cfVector X );
void   __vf  MCFDia_divrV( cfPMatrix MA, ui len, cfVector X );


/******  One-dimensional vector operations **********************
         performed along all rows or all columns simultaneously,
         or along the diagonal of a square matrix                */

void     __vf  MCFRows_absmax( fVector Y, cfPMatrix MA, ui ht, ui len );
void     __vf  MCFCols_absmax( fVector Y, cfPMatrix MA, ui ht, ui len );
float    __vf  MCFDia_absmax(  cfPMatrix MA, ui len );
void     __vf  MCFRows_absmin( fVector Y, cfPMatrix MA, ui ht, ui len );
void     __vf  MCFCols_absmin( fVector Y, cfPMatrix MA, ui ht, ui len );
float    __vf  MCFDia_absmin(  cfPMatrix MA, ui len );

void     __vf  MCFRows_maxReIm( cfVector Y, cfPMatrix MA, ui ht, ui len );
void     __vf  MCFCols_maxReIm( cfVector Y, cfPMatrix MA, ui ht, ui len );
void     __vf  MCFRows_minReIm( cfVector Y, cfPMatrix MA, ui ht, ui len );
void     __vf  MCFCols_minReIm( cfVector Y, cfPMatrix MA, ui ht, ui len );

void     __vf  MCFRows_absmaxReIm( cfVector Y, cfPMatrix MA, ui ht, ui len );
void     __vf  MCFCols_absmaxReIm( cfVector Y, cfPMatrix MA, ui ht, ui len );
void     __vf  MCFRows_absminReIm( cfVector Y, cfPMatrix MA, ui ht, ui len );
void     __vf  MCFCols_absminReIm( cfVector Y, cfPMatrix MA, ui ht, ui len );

void     __vf  MCFRows_cabsmax( cfVector Y, cfPMatrix MA, ui ht, ui len );
void     __vf  MCFCols_cabsmax( cfVector Y, cfPMatrix MA, ui ht, ui len );
void     __vf  MCFRows_cabsmin( cfVector Y, cfPMatrix MA, ui ht, ui len );
void     __vf  MCFCols_cabsmin( cfVector Y, cfPMatrix MA, ui ht, ui len );

void     __vf  MCFRows_sabsmax( cfVector Y, cfPMatrix MA, ui ht, ui len );
void     __vf  MCFCols_sabsmax( cfVector Y, cfPMatrix MA, ui ht, ui len );
void     __vf  MCFRows_sabsmin( cfVector Y, cfPMatrix MA, ui ht, ui len );
void     __vf  MCFCols_sabsmin( cfVector Y, cfPMatrix MA, ui ht, ui len );

void     __vf  MCFRows_sum( cfVector Y, cfPMatrix MA, ui ht, ui len );
void     __vf  MCFCols_sum( cfVector Y, cfPMatrix MA, ui ht, ui len );
void     __vf  MCFRows_prod(cfVector Y, cfPMatrix MA, ui ht, ui len );
void     __vf  MCFCols_prod(cfVector Y, cfPMatrix MA, ui ht, ui len );
#if defined __cplusplus && defined _CMATH_CLASSDEFS
} // the following functions cannot be extern "C", if fComplex is a class
#endif
fComplex __vf  MCFDia_maxReIm(  cfPMatrix MA, ui len );
fComplex __vf  MCFDia_minReIm(  cfPMatrix MA, ui len );
fComplex __vf  MCFDia_absmaxReIm(  cfPMatrix MA, ui len );
fComplex __vf  MCFDia_absminReIm(  cfPMatrix MA, ui len );
fComplex __vf  MCFDia_cabsmax(  cfPMatrix MA, ui len );
fComplex __vf  MCFDia_cabsmin(  cfPMatrix MA, ui len );
fComplex __vf  MCFDia_sabsmax(  cfPMatrix MA, ui len );
fComplex __vf  MCFDia_sabsmin(  cfPMatrix MA, ui len );
fComplex __vf  MCFDia_sum(  cfPMatrix MA, ui len );
fComplex __vf  MCFDia_prod( cfPMatrix MA, ui len );
#if defined __cplusplus && defined _CMATH_CLASSDEFS
extern "C" {
#endif

void  __vf  MCFRows_runsum( cfPMatrix MA, ui ht, ui len );
void  __vf  MCFCols_runsum( cfPMatrix MA, ui ht, ui len );
void  __vf  MCFRows_runprod( cfPMatrix MA, ui ht, ui len );
void  __vf  MCFCols_runprod( cfPMatrix MA, ui ht, ui len );

void  __vf  MCFRows_rotate( cfPMatrix MA, ui ht, ui len, ssize_t pos );
void  __vf  MCFCols_rotate( cfPMatrix MA, ui ht, ui len, ssize_t pos );
void  __vf  MCFRows_rotate_buf( cfPMatrix MA, ui ht, ui len, ssize_t pos, cfPMatrix MBuf );
void  __vf  MCFCols_rotate_buf( cfPMatrix MA, ui ht, ui len, ssize_t pos, cfPMatrix MBuf );
void  __vf  MCFRows_reflect( cfPMatrix MA, ui ht, ui len );
void  __vf  MCFCols_reflect( cfPMatrix MA, ui ht, ui len );
void  __vf  MCFRows_rev( cfPMatrix MA, ui ht, ui len );
void  __vf  MCFCols_rev( cfPMatrix MA, ui ht, ui len );

/********  Operations involving two rows or two colums of one matrix  *****/

void   __vf  MCFRows_exchange( cfPMatrix MA, ui ht, ui len,
                              ui i1, ui i2 );
void   __vf  MCFCols_exchange( cfPMatrix MA, ui ht, ui len,
                              ui i1, ui i2 );

void   __vf  MCFRows_add( cfPMatrix MA, ui ht, ui len,
                          ui destRow, ui sourceRow );
void   __vf  MCFCols_add( cfPMatrix MA, ui ht, ui len,
                          ui destCol, ui sourceCol );

void   __vf  MCFRows_sub( cfPMatrix MA, ui ht, ui len,
                          ui destRow, ui sourceRow );
void   __vf  MCFCols_sub( cfPMatrix MA, ui ht, ui len,
                          ui destCol, ui sourceCol );

#if defined __cplusplus && defined _CMATH_CLASSDEFS && defined __BORLANDC__ && defined _WIN64
} // for C++Builder on Win64, the following functions cannot be extern "C", if fComplex is a class
#endif
void   __vf  MCFRows_Cadd( cfPMatrix MA, ui ht, ui len,
                           ui destRow, ui sourceRow, fComplex C );
void   __vf  MCFCols_Cadd( cfPMatrix MA, ui ht, ui len,
                           ui destCol, ui sourceCol, fComplex C );

void   __vf  MCFRows_lincomb( cfPMatrix MA, ui ht, ui len,
                              ui destRow,  fComplex  destC,
                              ui srceRow,  fComplex  srceC );
void   __vf  MCFCols_lincomb( cfPMatrix MA, ui ht, ui len,
                              ui destCol,  fComplex  destC,
                              ui srceCol,  fComplex  srceC );


/***************  Transposing and rotating a matrix **********************/

#if defined __cplusplus && defined _CMATH_CLASSDEFS && defined __BORLANDC__ && defined _WIN64
extern "C" {
#endif
void  __vf  MCFtranspose( cfPMatrix MTr, cfPMatrix MA,
                          ui htTr, ui lenTr );
void  __vf  MCFhermconj( cfPMatrix MHConj, cfPMatrix MA,
                          ui htTr, ui lenTr );
void  __vf  MCFrotate90(  cfPMatrix MRot, cfPMatrix MA, ui htRot, ui lenRot );
#define     MCFrotate180( MRot, MA, htRot, lenRot ) \
                VCF_rev( MRot, MA, (htRot)*(lenRot) )
void  __vf  MCFrotate270( cfPMatrix MRot, cfPMatrix MA, ui htRot, ui lenRot );

/************************ Matrix Arithmetics *************************/

#define MCFaddM( MC, MA, MB, htA, lenA ) \
                 VCF_addV( MC, MA, MB, (htA)*(lenA) )
void __vf  MCFaddMT( cfPMatrix MC, cfPMatrix MA, cfPMatrix MB,
                     ui htA, ui lenA );
#define MCFsubM( MC, MA, MB, htA, lenA ) \
                 VCF_subV( MC, MA, MB, (htA)*(lenA) )
void __vf  MCFsubMT( cfPMatrix MC, cfPMatrix MA, cfPMatrix MB,
                     ui htA, ui lenA );
void __vf  MCFsubrMT( cfPMatrix MC, cfPMatrix MA, cfPMatrix MB,
                     ui htA, ui lenA );
#define MCFmulC( MB, MA, htA, lenA, C ) \
                 VCF_mulC( MB, MA, (htA)*(lenA), C )
#define MCFdivC( MB, MA, htA, lenA, C ) \
                 VCF_divC( MB, MA, (htA)*(lenA), C )
#define MCFmulReC( MB, MA, htA, lenA, CRe ) \
                 VCF_mulReC( MB, MA, (htA)*(lenA), CRe )
#define MCFdivReC( MB, MA, htA, lenA, CRe ) \
                 VCF_divReC( MB, MA, (htA)*(lenA), CRe )
#define MCFlincomb( MC, MA, MB, htA, lenA, CA, CB ) \
                 VCF_lincomb( MC, MA, MB, (htA)*(lenA), CA, CB )
void  __vf  MCFmulV( cfVector Y, cfPMatrix MA, cfVector X,
                    ui htA, ui lenA );
void  __vf  MCFTmulV( cfVector Y, cfPMatrix MA, cfVector X,
                     ui htA, ui lenA );
void  __vf  VCFmulM( cfVector Y, cfVector X, cfPMatrix MA,
                    ui htA, ui lenA );
void  __vf  VCFmulMT( cfVector Y, cfVector X, cfPMatrix MA,
                     ui htA, ui lenA );
void  __vf  MCFmulM( cfPMatrix MC, cfPMatrix MA, cfPMatrix MB,
                    ui htA, ui lenA, ui lenB );
void  __vf  MCFmulMT( cfPMatrix MC, cfPMatrix MA, cfPMatrix MB,
                    ui htA, ui lenA, ui htB );
void  __vf  MCFmulMH( cfPMatrix MC, cfPMatrix MA, cfPMatrix MB,
                    ui htA, ui lenA, ui htB );
void  __vf  MCFTmulM( cfPMatrix MC, cfPMatrix MA, cfPMatrix MB,
                    ui htA, ui lenA, ui lenB );
void  __vf  MCFHmulM( cfPMatrix MC, cfPMatrix MA, cfPMatrix MB,
                    ui htA, ui lenA, ui lenB );
void  __vf  MCFTmulMT( cfPMatrix MC, cfPMatrix MA, cfPMatrix MB,
                    ui htA, ui lenA, ui htB );
void  __vf  MCFTmulMH( cfPMatrix MC, cfPMatrix MA, cfPMatrix MB,
                    ui htA, ui lenA, ui htB );
void  __vf  MCFdiamulM( cfPMatrix MC, cfPMatrix MADia, cfPMatrix MB,
                    ui htB, ui lenB );
void  __vf  MCFdiamulMT( cfPMatrix MC, cfPMatrix MADia, cfPMatrix MB,
                    ui htB, ui lenB );
void  __vf  MCFmulMdia( cfPMatrix MC, cfPMatrix MA, cfPMatrix MBDia,
                    ui htA, ui lenA );
void  __vf  MCFTmulMdia( cfPMatrix MC, cfPMatrix MA, cfPMatrix MBDia,
                    ui htA, ui lenA );

/*************************  Linear Algebra    *****************************/

int    __vf  MCFLUdecompose( cfPMatrix MLU,  uiVector Ind, cfPMatrix MA,
                            ui len );

void   __vf  MCFLUsolve( cfVector X, cfPMatrix MLU, cfVector B, uiVector Ind,
                        ui len );
void   __vf  MCFLUinv( cfPMatrix MInv, cfPMatrix MLU, uiVector Ind,
                      ui len );
#if defined __cplusplus && defined _CMATH_CLASSDEFS
} // the following functions cannot be extern "C", if fComplex is a class
#endif
fComplex  __vf  MCFLUdet( cfPMatrix MLU, ui len, int permut );
#if defined __cplusplus && defined _CMATH_CLASSDEFS
extern "C" {
#endif
void   __vf  MCFLUimprove( cfVector X, cfVector B, cfPMatrix MA, cfPMatrix MLU,
                          uiVector Ind, ui len );

/* int   __vf  MCFSVdecompose( cfPMatrix MU, cfPMatrix MV, cfVector W, cfPMatrix MA,
                           ui htA, ui lenA );
void  __vf  MCFSVsolve( cfVector X, cfPMatrix MU, cfPMatrix MV, cfVector W,
                       cfVector B, ui htU, ui lenU ); */

          /*  functions using LUD or SVD     */
int    __vf  MCFsolve( cfVector X, cfPMatrix MA, cfVector B, ui len );
                  /* ret.value != 0 signals error */
int    __vf  MCFinv( cfPMatrix MInv, cfPMatrix MA, ui len );
                 /* ret.value != 0 signals error */
#if defined __cplusplus && defined _CMATH_CLASSDEFS
} // the following functions cannot be extern "C", if fComplex is a class
#endif
fComplex  __vf  MCFdet( cfPMatrix MA, ui len );
#if defined __cplusplus && defined _CMATH_CLASSDEFS
extern "C" {
#endif

/* int    __vf  MCFsolveBySVD( cfVector X, cfPMatrix MA, cfVector B,
                           ui htA, ui lenA );
              *  sizX = lenA,  sizB = htA.  ret.value != 0 signals failure *
int    __vf  MCFsafeSolve( cfVector X, cfPMatrix MA, cfVector B, ui len );
              * ret.value 0: success via LUD; 1: success via SVD; -1: error */


/*************  Two-Dimensional Fourier-Transform Methods *****************/

void  __vf   MCFpFFT( cfPMatrix MY, cfPMatrix MX, ui ht, ui len, int dir );
void  __vf   MCFbFFT( cfPMatrix MY, cfPMatrix MX, ui ht, ui len, int dir, cfVector Buf );
void  __vf   MCFpRows_FFT( cfPMatrix MY, cfPMatrix MX, ui ht, ui len, int dir );
void  __vf   MCFpCols_FFT( cfPMatrix MY, cfPMatrix MX, ui ht, ui len, int dir );
void  __vf   MCFbRows_FFT( cfPMatrix MY, cfPMatrix MX, ui ht, ui len, int dir, cfVector Buf );
void  __vf   MCFbCols_FFT( cfPMatrix MY, cfPMatrix MX, ui ht, ui len, int dir, cfVector Buf );
void  __vf   MCFpfilter( cfPMatrix MY, cfPMatrix MX, cfPMatrix MFlt, ui ht, ui len );

void  __vf   MCFlFFT( cfPMatrix MY, cfPMatrix MX, ui ht, ui len, int dir );
void  __vf   MCFlRows_FFT( cfPMatrix MY, cfPMatrix MX, ui ht, ui len, int dir );
void  __vf   MCFlCols_FFT( cfPMatrix MY, cfPMatrix MX, ui ht, ui len, int dir );
void  __vf   MCFlfilter( cfPMatrix MY, cfPMatrix MX, cfPMatrix MFlt, ui ht, ui len );

void  __vf   MCFsFFT( cfPMatrix MY, cfPMatrix MX, ui ht, ui len, int dir );
void  __vf   MCFsRows_FFT( cfPMatrix MY, cfPMatrix MX, ui ht, ui len, int dir );
void  __vf   MCFsCols_FFT( cfPMatrix MY, cfPMatrix MX, ui ht, ui len, int dir );
void  __vf   MCFsfilter( cfPMatrix MY, cfPMatrix MX, cfPMatrix MFlt,
                         ui ht, ui len );

      /*************  Input and Output  ****************/

#define MCFprint( MA, ht, len )  MCFfprint( stdout, MA, ht, len, 80 )
void __vf  MCFfprint( FILE _VFAR *stream, cfPMatrix MA, ui ht,
                      ui len, unsigned linewidth );
void __vf  MCFcprint( cfPMatrix MA, ui ht, ui len );
void __vf  MCFwrite( FILE _VFAR *stream, cfPMatrix X, ui ht, ui len  );
#if !((defined __BORLANDC__) && (__BORLANDC__ < 0x710))
		/* modern compiler versions:  */
	void __vf MCFread( cfPMatrix X, ui ht, ui len, FILE _VFAR *stream );
#else /* older Borland compiler versions need separate implementation */
	void __vf MCFread1( cfPMatrix X, ui ht, ui len, FILE _VFAR *stream );
	#define MCFread  MCFread1
#endif
#define MCFstore( str, MA, ht, len ) VCF_store( str, MA, (len)*(ht) )
#define MCFrecall( MA, ht, len, str) VCF_recall( MA, (len)*(ht), str)

#ifdef __cplusplus
}  // end of extern "C"
#endif
#endif /* __MCFSTD_H */
