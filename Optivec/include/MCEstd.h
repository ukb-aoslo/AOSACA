/*  MCEstd.h

  matrix management functions:
  manipulations on matrices of data type "eComplex"
  (extended-precision complex numbers)

  Copyright (c) 1996-2017 by OptiCode - Dr. Martin Sander Software Dev.
  All Rights Reserved.
*/

#if !defined( __MCESTD_H )
#define __MCESTD_H
#if !defined( __MATLIB_H )
   #include <MatLib.h>
#endif
#if !defined( __VCESTD_H )
   #include <VCEstd.h>
#endif
#if !defined( __VCEMATH_H )
   #include <VCEmath.h>
#endif

#if (defined __BORLANDC__) && !(defined _WIN64)
       /* the following ca. 550 lines are only for Borland C++ 32-bit,
		  as 80-bit reals are not available on Win64 and not in Visual C++ */
#ifdef __cplusplus
extern "C" {
#endif

/*************   Dynamic Generation of Matrices   ************************/

ceMatrix __vf  MCE_matrix(  ui ht, ui len );
ceMatrix __vf  MCE_matrix0( ui ht, ui len );
#if defined (_MSC_VER) && defined (_DEBUG)
    ceMatrix __vf  MCE_matrix_dbg(  ui ht, ui len );
    ceMatrix __vf  MCE_matrix0_dbg( ui ht, ui len );
    #if defined (_INC_CRTDBG) && defined (_CRTDBG_MAP_ALLOC) 
	    /* Automatic mapping for memory-leak detection by CRT debugging switched on? */ 
        #define MCE_matrix  MCE_matrix_dbg
        #define MCE_matrix0 MCE_matrix0_dbg
    #endif
#else
    #define MCE_matrix_dbg  MCE_matrix
    #define MCE_matrix0_dbg MCE_matrix0
#endif
    /*  Notice that, in the memory model HUGE,
        neither len nor ht may exceed 1637            */

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

#define MCE_getElement( y, MA, ht, len, m, n ) MCEgetElement( y, (MA)[0], ht, len, m, n )
#define MCE_setElement( MA, ht, len, m, n, C ) MCEsetElement( (MA)[0], ht, len, m, n, C )
#define MCE_Pelement( MA, ht, len, m, n ) MCEPelement( (MA)[0], ht, len, m, n )
                     /* returns a pointer to MA[m][n]. */
#define MCE_element( MA, ht, len, m, n ) *MCEPelement( (MA)[0], ht, len, m, n )
                     /* dereferenced pointer */

 /****************  Initialization  ***************************************

    To initialize all elements of a matrix with the same value,
    or to perform arithmetic operations on all elements simultaneously,
    refer to the functions of VectorLib, declared in <VCEstd.h>, <VCEmath.h>.
    In order to use the VectorLib functions, utilize the feature that
    the whole matrix occupies one contiguous area in memory: pass the
    address of the first row to the desired vector function, the size
    of the "vector" being len * ht.
    For example, initialize all elements of the matrix MA with {1.0, 0.0}
    (this is *NOT* the identity matrix)  by calling
        VCE_equ1( (MA)[0], len * ht );
*/

#define MCE_equ0( MA, ht, len )            VCE_equ0( (MA)[0], (ht)*(len) )
#define MCE_equ1( MA, len )                MCEequ1( (MA)[0], len ) /* identity matrix */
#define MCE_equm1( MA, len )               MCEequm1( (MA)[0], len ) /* neg. identity matrix */
#define MCE_randomLC( MA, ht, len, seed, Min, Max, state ) \
                                           VCE_randomLC( (MA)[0], (ht)*(len), seed, Min, Max, state )
#define MCE_random( MA, ht, len, seed, Min, Max ) \
                                           VCE_random( (MA)[0], (ht)*(len), seed, Min, Max )
#define MCE_outerprod( MA, X, Y, ht, len ) MCEouterprod( (MA)[0], X, Y, ht, len )
                       /* sizX=ht, sizY=len */
#define MCE_Row_equ0( MA, ht, len, iRow ) MCERow_equ0( (MA)[0], ht, len, iRow )
#define MCE_Col_equ0( MA, ht, len, iCol ) MCECol_equ0( (MA)[0], ht, len, iCol )
#define MCE_Dia_equ0( MA, len )           MCEDia_equ0( (MA)[0], len )
#define MCE_Row_equC( MA, ht, len, iRow, C ) \
                                        MCERow_equC( (MA)[0], ht, len, iRow, C )
#define MCE_Col_equC( MA, ht, len, iCol, C ) \
                                        MCECol_equC( (MA)[0], ht, len, iCol, C )
#define MCE_Dia_equC( MA, len, C )      MCEDia_equC( (MA)[0], len, C )

#define MCE_Row_equV( MA, ht, len, iRow, X ) \
                                        MCERow_equV( (MA)[0], ht, len, iRow, X )
#define MCE_Col_equV( MA, ht, len, iCol, X ) \
                                        MCECol_equV( (MA)[0], ht, len, iCol, X )
#define MCE_Dia_equV( MA, len, X )      MCEDia_equV( (MA)[0], len, X )

#define MCE_Trd_equM( MA, MTrd, len )    MCETrd_equM( (MA)[0], (MTrd)[0], len )
#define MCE_Trd_extract( MTrd, MA, len ) MCETrd_extract( (MTrd)[0], (MA)[0], len )

#define MCE_equM( MB, MA, ht, len )  VCE_equV( (MB)[0], (MA)[0], ((ui)(len))*(ht) )
#define MCE_neg( MB, MA, ht, len )   VCE_neg( (MB)[0], (MA)[0], ((ui)(len))*(ht) )
#define MCE_conj( MB, MA, ht, len )  VCE_conj( (MB)[0], (MA)[0], ((ui)(len))*(ht) )

#define MCE_UequL( MA, len ) MCEUequL( (MA)[0], len )
#define MCE_LequU( MA, len ) MCELequU( (MA)[0], len )
         /* copy lower-diagonal elements into upper-diagonal
           (or vice versa) by index-reflection, so as to
           get a symmetric matrix    */

            /* data-type conversions:  */
#define M_CEtoCF( MCF, MCE, ht, len ) V_CEtoCF( (MCF)[0], (MCE)[0], (ht)*(len) )
#define M_CFtoCE( MCE, MCF, ht, len ) V_CFtoCE( (MCE)[0], (MCF)[0], (ht)*(len) )
#define M_CEtoCD( MCD, MCE, ht, len ) V_CEtoCD( (MCD)[0], (MCE)[0], (ht)*(len) )
#define M_CDtoCE( MCE, MCD, ht, len ) V_CDtoCE( (MCE)[0], (MCD)[0], (ht)*(len) )

#define ME_CtoRe( MY, MCX, ht, len )  VE_CtoRe( (MY)[0],  (MCX)[0], (ht)*(len) )
#define ME_CtoIm( MY, MCX, ht, len )  VE_CtoIm( (MY)[0],  (MCX)[0], (ht)*(len) )
#define ME_CtoReIm( MYRe, MYIm, MCX, ht, len )  VE_CtoReIm( (MYRe)[0], (MYIm)[0], (MCX)[0], (ht)*(len) )
#define ME_RetoC( MCY, MX, ht, len )  VE_RetoC( (MCY)[0], (MX)[0],  (ht)*(len) )
#define ME_ImtoC( MCY, MX, ht, len )  VE_ImtoC( (MCY)[0], (MX)[0],  (ht)*(len) )
#define ME_ReImtoC( MCY, MXRe, MXIm, ht, len )  VE_ReImtoC( (MCY)[0], (MXRe)[0], (MXIm)[0], (ht)*(len) )

/********  Extracting a submatrix and copying a submatrix back  *********/

#define MCE_submatrix( MSub, subHt, subLen, \
                       MSrce, srceHt, srceLen, \
                       firstRowInCol, sampInCol, firstColInRow, sampInRow ) \
               MCEsubmatrix(  (MSub)[0], subHt, subLen, \
                              (MSrce)[0], srceHt, srceLen, \
                              firstRowInCol, sampInCol, firstColInRow, sampInRow )

#define MCE_submatrix_equM( MDest, destHt, destLen, \
                            firstRowInCol, sampInCol, firstColInRow, sampInRow, \
                            MSrce, srceHt, srceLen ) \
               MCEsubmatrix_equM(  (MDest)[0], destHt, destLen, \
                             firstRowInCol, sampInCol, firstColInRow, sampInRow, \
                             (MSrce)[0], srceHt, srceLen )

#define MCE_equMblock( MSub, subHt, subLen, \
                      MSrce, srceHt, srceLen, \
                      firstRowInCol, firstColInRow ) \
              MCEequMblock(  (MSub)[0], subHt, subLen, \
                             (MSrce)[0], srceHt, srceLen, \
                             firstRowInCol, firstColInRow )

#define MCE_block_equM( MDest, destHt, destLen, \
                       firstRowInCol, firstColInRow, \
                       MSrce, srceHt, srceLen ) \
              MCEblock_equM( (MDest)[0], destHt, destLen, \
                             firstRowInCol, firstColInRow, \
                             (MSrce)[0], srceHt, srceLen )

#define MCE_equMblockT( MSub, subHt, subLen, \
                      MSrce, srceHt, srceLen, \
                      firstRowInCol, firstColInRow ) \
              MCEequMblockT( (MSub)[0], subHt, subLen, \
                             (MSrce)[0], srceHt, srceLen, \
                             firstRowInCol, firstColInRow )

#define MCE_block_equMT( MDest, destHt, destLen, \
                       firstRowInCol, firstColInRow, \
                       MSrce, srceHt, srceLen ) \
              MCEblock_equMT( (MDest)[0], destHt, destLen, \
                             firstRowInCol, firstColInRow, \
                             (MSrce)[0], srceHt, srceLen )

/*****   Extracting a single row or a single column or the diagonal  ******
 *       and storing it into a vector                                     */

#define MCE_Row_extract( Y, MA, ht, len, iRow ) \
                                     MCERow_extract( Y, (MA)[0], ht, len, iRow )
#define MCE_Col_extract( Y, MA, ht, len, iCol ) \
                                     MCECol_extract( Y, (MA)[0], ht, len, iCol )
#define MCE_Dia_extract( Y, MA, len ) MCEDia_extract( Y, (MA)[0], len )


/**************  Deleting or inserting a row or a column   ***************/

#define MCE_Row_delete( MB, MA, htA, lenA, iRow ) \
                           MCERow_delete( (MB)[0], (MA)[0], htA, lenA, iRow )
#define MCE_Col_delete( MB, MA, htA, lenA, iCol ) \
                           MCECol_delete( (MB)[0], (MA)[0], htA, lenA, iCol )
#define MCE_Row_insert( MB, MA, htB, lenB, iRow, X ) \
                           MCERow_insert( (MB)[0], (MA)[0], htB, lenB, iRow, X )
#define MCE_Col_insert( MB, MA, htB, lenB, iCol, X ) \
                           MCECol_insert( (MB)[0], (MA)[0], htB, lenB, iCol, X )


/*****************    Basic arithmetic operations *********************
                      performed on one single row,
                      or one single column of any matrix,
                      or on the diagonal of a square matrix

    Note: In contrast to the analogous VectorLib functions, the operations
    are performed in-place, i.e. the input matrix itself is changed  */

#define MCE_Row_neg( MA, ht, len, iRow ) MCERow_neg( (MA)[0], ht, len, iRow )
#define MCE_Col_neg( MA, ht, len, iCol ) MCECol_neg( (MA)[0], ht, len, iCol )

#define MCE_Row_conj( MA, ht, len, iRow ) MCERow_conj( (MA)[0], ht, len, iRow )
#define MCE_Col_conj( MA, ht, len, iCol ) MCECol_conj( (MA)[0], ht, len, iCol )

#define MCE_Row_addC( MA, ht, len, iRow, C ) \
                                     MCERow_addC( (MA)[0], ht, len, iRow, C )
#define MCE_Col_addC( MA, ht, len, iCol, C ) \
                                     MCECol_addC( (MA)[0], ht, len, iCol, C )
#define MCE_Dia_addC( MA, len, C )   MCEDia_addC( (MA)[0], len, C )

#define MCE_Row_addV( MA, ht, len, iRow, X ) \
                                     MCERow_addV( (MA)[0], ht, len, iRow, X )
#define MCE_Col_addV( MA, ht, len, iCol, X ) \
                                     MCECol_addV( (MA)[0], ht, len, iCol, X )
#define MCE_Dia_addV( MA, len, X )   MCEDia_addV( (MA)[0], len, X )

#define MCE_Row_subC( MA, ht, len, iRow, C ) \
                                     MCERow_subC( (MA)[0], ht, len, iRow, C )
#define MCE_Col_subC( MA, ht, len, iCol, C ) \
                                     MCECol_subC( (MA)[0], ht, len, iCol, C )
#define MCE_Dia_subC( MA, len, C )   MCEDia_subC( (MA)[0], len, C )

#define MCE_Row_subV( MA, ht, len, iRow, X ) \
                                     MCERow_subV( (MA)[0], ht, len, iRow, X )
#define MCE_Col_subV( MA, ht, len, iCol, X ) \
                                     MCECol_subV( (MA)[0], ht, len, iCol, X )
#define MCE_Dia_subV( MA, len, X )   MCEDia_subV( (MA)[0], len, X )

#define MCE_Row_subrC( MA, ht, len, iRow, C ) \
                                     MCERow_subrC( (MA)[0], ht, len, iRow, C )
#define MCE_Col_subrC( MA, ht, len, iCol, C ) \
                                     MCECol_subrC( (MA)[0], ht, len, iCol, C )
#define MCE_Dia_subrC( MA, len, C )  MCEDia_subrC( (MA)[0], len, C )

#define MCE_Row_subrV( MA, ht, len, iRow, X ) \
                                     MCERow_subrV( (MA)[0], ht, len, iRow, X )
#define MCE_Col_subrV( MA, ht, len, iCol, X ) \
                                     MCECol_subrV( (MA)[0], ht, len, iCol, X )
#define MCE_Dia_subrV( MA, len, X )  MCEDia_subrV( (MA)[0], len, X )

#define MCE_Row_mulC( MA, ht, len, iRow, C ) \
                                     MCERow_mulC( (MA)[0], ht, len, iRow, C )
#define MCE_Col_mulC( MA, ht, len, iCol, C ) \
                                     MCECol_mulC( (MA)[0], ht, len, iCol, C )
#define MCE_Dia_mulC( MA, len, C )   MCEDia_mulC( (MA)[0], len, C )

#define MCE_Row_mulV( MA, ht, len, iRow, X ) \
                                     MCERow_mulV( (MA)[0], ht, len, iRow, X )
#define MCE_Col_mulV( MA, ht, len, iCol, X ) \
                                     MCECol_mulV( (MA)[0], ht, len, iCol, X )
#define MCE_Dia_mulV( MA, len, X )   MCEDia_mulV( (MA)[0], len, X )

#define MCE_Row_divC( MA, ht, len, iRow, C ) \
                                     MCERow_divC( (MA)[0], ht, len, iRow, C )
#define MCE_Col_divC( MA, ht, len, iCol, C ) \
                                     MCECol_divC( (MA)[0], ht, len, iCol, C )
#define MCE_Dia_divC( MA, len, C )   MCEDia_divC( (MA)[0], len, C )

#define MCE_Row_divV( MA, ht, len, iRow, X ) \
                                      MCERow_divV( (MA)[0], ht, len, iRow, X )
#define MCE_Col_divV( MA, ht, len, iCol, X ) \
                                      MCECol_divV( (MA)[0], ht, len, iCol, X )
#define MCE_Dia_divV( MA, len, X )    MCEDia_divV( (MA)[0], len, X )

#define MCE_Row_divrC( MA, ht, len, iRow, C ) \
                                      MCERow_divrC( (MA)[0], ht, len, iRow, C )
#define MCE_Col_divrC( MA, ht, len, iCol, C ) \
                                      MCECol_divrC( (MA)[0], ht, len, iCol, C )
#define MCE_Dia_divrC( MA, len, C )   MCEDia_divrC( (MA)[0], len, C )

#define MCE_Row_divrV( MA, ht, len, iRow, X ) \
                                      MCERow_divrV( (MA)[0], ht, len, iRow, X )
#define MCE_Col_divrV( MA, ht, len, iCol, X ) \
                                      MCECol_divrV( (MA)[0], ht, len, iCol, X )
#define MCE_Dia_divrV( MA, len, X )   MCEDia_divrV( (MA)[0], len, X )


/******  One-dimensional vector operations **********************
         performed along all rows or all columns simultaneously,
         or along the diagonal of a square matrix                */

#define MCE_Rows_absmax( Y, MA, ht, len )  MCERows_absmax( Y, (MA)[0], ht, len )
#define MCE_Cols_absmax( Y, MA, ht, len )  MCECols_absmax( Y, (MA)[0], ht, len )
#define MCE_Dia_absmax( MA, len )          MCEDia_absmax( (MA)[0], len )
#define MCE_Rows_absmin( Y, MA, ht, len )  MCERows_absmin( Y, (MA)[0], ht, len )
#define MCE_Cols_absmin( Y, MA, ht, len )  MCECols_absmin( Y, (MA)[0], ht, len )
#define MCE_Dia_absmin( MA, len )          MCEDia_absmin( (MA)[0], len )

#define MCE_Rows_maxReIm( Y, MA, ht, len ) MCERows_maxReIm( Y, (MA)[0], ht, len )
#define MCE_Cols_maxReIm( Y, MA, ht, len ) MCECols_maxReIm( Y, (MA)[0], ht, len )
#define MCE_Dia_maxReIm( MA, len )         MCEDia_maxReIm( (MA)[0], len )
#define MCE_Rows_minReIm( Y, MA, ht, len ) MCERows_minReIm( Y, (MA)[0], ht, len )
#define MCE_Cols_minReIm( Y, MA, ht, len ) MCECols_minReIm( Y, (MA)[0], ht, len )
#define MCE_Dia_minReIm( MA, len )         MCEDia_minReIm( (MA)[0], len )

#define MCE_Rows_absmaxReIm( Y, MA, ht, len ) MCERows_absmaxReIm( Y, (MA)[0], ht, len )
#define MCE_Cols_absmaxReIm( Y, MA, ht, len ) MCECols_absmaxReIm( Y, (MA)[0], ht, len )
#define MCE_Dia_absmaxReIm( MA, len )         MCEDia_absmaxReIm( (MA)[0], len )
#define MCE_Rows_absminReIm( Y, MA, ht, len ) MCERows_absminReIm( Y, (MA)[0], ht, len )
#define MCE_Cols_absminReIm( Y, MA, ht, len ) MCECols_absminReIm( Y, (MA)[0], ht, len )
#define MCE_Dia_absminReIm( MA, len )         MCEDia_absminReIm( (MA)[0], len )

#define MCE_Rows_cabsmax( Y, MA, ht, len ) MCERows_cabsmax( Y, (MA)[0], ht, len )
#define MCE_Cols_cabsmax( Y, MA, ht, len ) MCECols_cabsmax( Y, (MA)[0], ht, len )
#define MCE_Dia_cabsmax( MA, len )         MCEDia_cabsmax( (MA)[0], len )
#define MCE_Rows_cabsmin( Y, MA, ht, len ) MCERows_cabsmin( Y, (MA)[0], ht, len )
#define MCE_Cols_cabsmin( Y, MA, ht, len ) MCECols_cabsmin( Y, (MA)[0], ht, len )
#define MCE_Dia_cabsmin( MA, len )         MCEDia_cabsmin( (MA)[0], len )

#define MCE_Rows_sabsmax( Y, MA, ht, len ) MCERows_sabsmax( Y, (MA)[0], ht, len )
#define MCE_Cols_sabsmax( Y, MA, ht, len ) MCECols_sabsmax( Y, (MA)[0], ht, len )
#define MCE_Dia_sabsmax( MA, len )         MCEDia_sabsmax( (MA)[0], len )
#define MCE_Rows_sabsmin( Y, MA, ht, len ) MCERows_sabsmin( Y, (MA)[0], ht, len )
#define MCE_Cols_sabsmin( Y, MA, ht, len ) MCECols_sabsmin( Y, (MA)[0], ht, len )
#define MCE_Dia_sabsmin( MA, len )         MCEDia_sabsmin( (MA)[0], len )

#define MCE_Rows_sum( Y, MA, ht, len )     MCERows_sum( Y, (MA)[0], ht, len )
#define MCE_Cols_sum( Y, MA, ht, len )     MCECols_sum( Y, (MA)[0], ht, len )
#define MCE_Dia_sum(  MA, len )            MCEDia_sum( (MA)[0], len )
#define MCE_Rows_prod( Y, MA, ht, len )    MCERows_prod( Y, (MA)[0], ht, len )
#define MCE_Cols_prod( Y, MA, ht, len )    MCECols_prod( Y, (MA)[0], ht, len )
#define MCE_Dia_prod(  MA, len )           MCEDia_prod( (MA)[0], len )

#define MCE_Rows_runsum( MA, ht, len )     MCERows_runsum( (MA)[0], ht, len )
#define MCE_Cols_runsum( MA, ht, len )     MCECols_runsum( (MA)[0], ht, len )
#define MCE_Rows_runprod( MA, ht, len )    MCERows_runprod( (MA)[0], ht, len )
#define MCE_Cols_runprod( MA, ht, len )    MCECols_runprod( (MA)[0], ht, len )

#define MCE_Rows_rotate( MA, ht, len, pos) MCERows_rotate( (MA)[0], ht, len, pos )
#define MCE_Cols_rotate( MA, ht, len, pos) MCECols_rotate( (MA)[0], ht, len, pos )
#define MCE_Rows_rotate_buf( MA, ht, len, pos, MBuf) MCERows_rotate_buf( (MA)[0], ht, len, pos, (MBuf)[0] )
#define MCE_Cols_rotate_buf( MA, ht, len, pos, MBuf) MCECols_rotate_buf( (MA)[0], ht, len, pos, (MBuf)[0] )
#define MCE_Rows_reflect( MA, ht, len)     MCERows_reflect( (MA)[0], ht, len )
#define MCE_Cols_reflect( MA, ht, len)     MCECols_reflect( (MA)[0], ht, len )
#define MCE_Rows_rev( MA, ht, len)         MCERows_rev( (MA)[0], ht, len )
#define MCE_Cols_rev( MA, ht, len)         MCECols_rev( (MA)[0], ht, len )

/********  Operations involving two rows or two colums of one matrix  *****/

#define MCE_Rows_exchange( MA, ht, len, row1, row2 ) \
                             MCERows_exchange( (MA)[0], ht, len, row1, row2 )
#define MCE_Cols_exchange( MA, ht, len, col1, col2 ) \
                             MCECols_exchange( (MA)[0], ht, len, col1, col2 )

#define MCE_Rows_add( MA, ht, len, destRow, srceRow ) \
                             MCERows_add( (MA)[0], ht, len, destRow, srceRow )
#define MCE_Cols_add( MA, ht, len, destCol, srceCol ) \
                             MCECols_add( (MA)[0], ht, len, destCol, srceCol )
                         /* dest[i] += source[i]  */

#define MCE_Rows_sub( MA, ht, len, destRow, srceRow ) \
                             MCERows_sub( (MA)[0], ht, len, destRow, srceRow )
#define MCE_Cols_sub( MA, ht, len, destCol, srceCol ) \
                             MCECols_sub( (MA)[0], ht, len, destCol, srceCol )
                         /* dest[i] -= source[i]  */

#define MCE_Rows_Cadd( MA, ht, len, destRow, srceRow, C ) \
                          MCERows_Cadd( (MA)[0], ht, len, destRow, srceRow, C )
#define MCE_Cols_Cadd( MA, ht, len, destCol, srceCol, C ) \
                          MCECols_Cadd( (MA)[0], ht, len, destCol, srceCol, C )
                         /* dest[i] += C * source[i]  */

#define MCE_Rows_lincomb( MA, ht, len, destRow, destC, srceRow, srceC ) \
            MCERows_lincomb( (MA)[0], ht, len, destRow, destC, srceRow, srceC )
#define MCE_Cols_lincomb( MA, ht, len, destCol, destC, srceCol, srceC ) \
            MCECols_lincomb( (MA)[0], ht, len, destCol, destC, srceCol, srceC )
  /*  linear combination: dest[i] = destC * dest[i] + sourceC * source[i] */


/*************  Transposing and rotating a matrix **********************/

#define MCE_transpose( MTr, MA, htTr, lenTr ) \
             MCEtranspose( (MTr)[0], (MA)[0], htTr, lenTr )
       /*  the dimensions htTr, lenTr are those of the transposed matrix,
           not of the original!                */
#define MCE_hermconj( MHConj, MA, htTr, lenTr ) \
             MCEhermconj( (MHConj)[0], (MA)[0], htTr, lenTr )
#define MCE_rotate90( MRot, MA, htRot, lenRot ) \
             MCErotate90( (MRot)[0], (MA)[0], htRot, lenRot )
#define MCE_rotate180( MRot, MA, htRot, lenRot ) \
             VCE_rev( (MRot)[0], (MA)[0], (htRot)*(lenRot) )
#define MCE_rotate270( MRot, MA, htRot, lenRot ) \
             MCErotate270( (MRot)[0], (MA)[0], htRot, lenRot )


/************************ Matrix Arithmetics *************************/

#define MCE_addM( MC, MA, MB, htA, lenA ) \
                 VCE_addV( (MC)[0], (MA)[0], (MB)[0], (htA)*(lenA) )
#define MCE_addMT( MC, MA, MB, htA, lenA ) \
                 MCEaddMT( (MC)[0], (MA)[0], (MB)[0], htA, lenA )
#define MCE_subM( MC, MA, MB, htA, lenA ) \
                 VCE_subV( (MC)[0], (MA)[0], (MB)[0], (htA)*(lenA) )
#define MCE_subMT( MC, MA, MB, htA, lenA ) \
                 MCEsubMT( (MC)[0], (MA)[0], (MB)[0], htA, lenA )
#define MCE_subrMT( MC, MA, MB, htA, lenA ) \
                 MCEsubrMT( (MC)[0], (MA)[0], (MB)[0], htA, lenA )
#define MCE_mulC( MB, MA, htA, lenA, C ) \
                 VCE_mulC( (MB)[0], (MA)[0], (htA)*(lenA), C )
#define MCE_divC( MB, MA, htA, lenA, C ) \
                 VCE_divC( (MB)[0], (MA)[0], (htA)*(lenA), C )
#define MCE_mulReC( MB, MA, htA, lenA, CRe ) \
                 VCE_mulReC( (MB)[0], (MA)[0], (htA)*(lenA), CRe )
#define MCE_divReC( MB, MA, htA, lenA, CRe ) \
                 VCE_divReC( (MB)[0], (MA)[0], (htA)*(lenA), CRe )
#define MCE_lincomb( MC, MA, MB, htA, lenA, CA, CB ) \
                 VCE_lincomb( (MC)[0], (MA)[0], (MB)[0], (htA)*(lenA), CA, CB )

#define MCE_mulV( Y, MA, X, htA, lenA ) \
                    MCEmulV( Y, (MA)[0], X, htA, lenA )
                          /*  Y = MA * X.  sizX=lenA, sizY=htA
                              both X and Y are column-vectors    */
#define MCE_TmulV( Y, MA, X, htA, lenA ) \
                    MCETmulV( Y, (MA)[0], X, htA, lenA )
                          /*  Y = MAT * X.  sizX=htA, sizY=lenA
                              both X and Y are column-vectors    */
#define VCE_mulM( Y, X, MA, htA, lenA ) \
                    VCEmulM( Y, X, (MA)[0], htA, lenA )
                         /*  Y = X * MA.  sizX=htA, sizY=lenA
                             both X and Y are row-vectors.
                             Mind the prefix: VCE_ (not MCE_)    */
#define VCE_mulMT( Y, X, MA, htA, lenA ) \
                    VCEmulMT( Y, X, (MA)[0], htA, lenA )
                         /*  Y = X * MAT.  sizX=lenA, sizY=htA
                             both X and Y are row-vectors.   */
#define MCE_mulM( MC, MA, MB, htA, lenA, lenB ) \
                    MCEmulM( (MC)[0], (MA)[0], (MB)[0], htA, lenA, lenB )
                         /*  MC = MA * MB.  htB=lenA, htC=htA, lenC=lenB */
#define MCE_mulMT( MC, MA, MB, htA, lenA, htB ) \
                    MCEmulMT( (MC)[0], (MA)[0], (MB)[0], htA, lenA, htB )
                         /*  MC = MA * MBT.  lenB=lenA, htC=htA, lenC=htB */
#define MCE_mulMH( MC, MA, MB, htA, lenA, htB ) \
                    MCEmulMH( (MC)[0], (MA)[0], (MB)[0], htA, lenA, htB )
                         /*  MC = MA * MBH.  lenB=lenA, htC=htA, lenC=htB */
#define MCE_TmulM( MC, MA, MB, htA, lenA, lenB ) \
                    MCETmulM( (MC)[0], (MA)[0], (MB)[0], htA, lenA, lenB )
                         /*  MC = MAT * MB.  htB=htA, htC=lenA, lenC=lenB */
#define MCE_HmulM( MC, MA, MB, htA, lenA, lenB ) \
                    MCEHmulM( (MC)[0], (MA)[0], (MB)[0], htA, lenA, lenB )
                         /*  MC = MAH * MB.  htB=htA, htC=lenA, lenC=lenB */
#define MCE_TmulMT( MC, MA, MB, htA, lenA, htB ) \
                    MCETmulMT( (MC)[0], (MA)[0], (MB)[0], htA, lenA, htB )
                         /*  MC = MAT * MBT.  lenB=htA, htC=lenA, lenC=htB */
#define MCE_TmulMH( MC, MA, MB, htA, lenA, htB ) \
                    MCETmulMH( (MC)[0], (MA)[0], (MB)[0], htA, lenA, htB )
                         /*  MC = MAT * MBH.  lenB=htA, htC=lenA, lenC=htB */
#define MCEdia_mulM(  MC, MADia, MB, htB, lenB )  MCEdiamulM(  (MC)[0], MADia, (MB)[0], htB, lenB )
#define MCEdia_mulMT( MC, MADia, MB, htB, lenB )  MCEdiamulMT( (MC)[0], MADia, (MB)[0], htB, lenB )
#define MCE_mulMdia(  MC, MA, MBDia, htA, lenA )  MCEmulMdia(  (MC)[0], (MA)[0], MBDia, htA, lenA )
#define MCE_TmulMdia( MC, MA, MBDia, htA, lenA )  MCETmulMdia( (MC)[0], (MA)[0], MBDia, htA, lenA )

/*************************  Linear Algebra    *****************************/

   /*  The standard treatMCEnt of linear systems is based
       on LUD (matrix decomposition into Upper-triangular
       and Lower-triangular components). The result of the
       decomposition step is used for further operations.  */

#define MCE_LUdecompose( MLU, Ind, MA, len ) \
                    MCELUdecompose( (MLU)[0], Ind, (MA)[0], len )
            /* returns "permut" = ñ1 which is needed for MCE_LUdet.
               for singularities not cured by editing, permut is 0  */
int     __vf MCE_LUDresult( void );
    /* returns 0, if MCE_LUdecompose was successful;
       returns 1, if MA was (nearly) singular in MCE_LUdecompose.   */
void       __vf MCE_LUDsetEdit( extended Thresh );
extended   __vf MCE_LUDgetEdit( void );
     /*  Editing threshold valid for MCE_LUdecompose;
         may be used to cure singularities           */

#define MCE_LUsolve( X, MLU, B, Ind, len ) \
                    MCELUsolve( X, (MLU)[0], B, Ind, len )
#define MCE_LUinv( MInv, MLU, Ind, len ) \
                    MCELUinv( (MInv)[0], (MLU)[0], Ind, len )
#define MCE_LUdet( MLU, len, permut )  MCELUdet( (MLU)[0], len, permut )
#define MCE_LUimprove( X, B, MA, MLU, Ind, len ) \
                      MCELUimprove( X, B, (MA)[0], (MLU)[0], Ind, len )

    /****  Special treatment of over- or under-determined
           linear systems, i.e. of matrices with len != ht
           and of singular matrices:
           SVD (Singular Value Decomposition)       ****

#define MCE_SVdecompose( MU, MV, W, MA, htA, lenA ) \
                    MCESVdecompose( (MU)[0], (MV)[0], W, (MA)[0], htA, lenA )
            *  sizB = htA,  sizX = sizW = htV = lenV = lenA  *
#define MCE_SVsolve( X, MU, MV, W, B, htU, lenU ) \
                    MCESVsolve( X, (MU)[0], (MV)[0], W, B, htU, lenU )
            *  lenU = lenA,  htU = max( lenA, htA ) as fed into
                MD_SVdecompose   *
void    __vf MCE_SVDsetEdit( extended Thresh );
extended   __vf MCE_SVDgetEdit( void );
    * Override of the standard values for editing threshholds
       in MCE_SVsolve. Calling MCE_setEdit with Thresh=0.0 MCEans
       that you do the necessary editing of W yourself
       before calling MD_SVsolve                           */

 /*****  "Easy-to-use" versions of the matrix functions
          using LUD or SVD.
          They allocate their own working space and rely
          on your setting of the editing threshold. In
          case of MCEmory stress, you might better use the
          two-step MCEthods declared above.            ***/
#define MCE_solve( X, MA, B, len ) \
                    MCEsolve( X, (MA)[0], B, len )
#define MCE_inv( MInv, MA, len ) \
                    MCEinv( (MInv)[0], (MA)[0], len )
#define MCE_det(  MA, len ) \
                    MCEdet( (MA)[0], len )
/* #define MCE_solveBySVD( X, MA, B, ht, len ) \
                    MCEsolveBySVD( X, (MA)[0], B, ht, len )
         *  sizX = len,  sizB = ht  *
#define MCE_safeSolve( X, MA, B, len ) \
                    MCEsafeSolve( X, (MA)[0], B, len )
        * MCE_safeSolve tries first LUD. If that fails, SVD is done.
           X[i] will be 0.0 instead of INF for those i corresponding
           to singularities. If even SVD fails, all X[i] are set to 0.0.
           return value 0: success via LUD; 1: success via SVD; -1: failure */

/***************** Two-Dimensional Fourier-Transform Methods ************/

#define MCEp_FFT( MY, MX, ht, len, dir )      MCEpFFT( (MY)[0], (MX)[0], ht, len, dir )
#define MCEb_FFT( MY, MX, ht, len, dir, Buf ) MCEbFFT( (MY)[0], (MX)[0], ht, len, dir, Buf )
#define MCEp_Rows_FFT( MY, MX, ht, len, dir) MCEpRows_FFT( (MY)[0], (MX)[0], ht, len, dir )
#define MCEp_Cols_FFT( MY, MX, ht, len, dir) MCEpCols_FFT( (MY)[0], (MX)[0], ht, len, dir )
#define MCEb_Rows_FFT( MY, MX, ht, len, dir, Buf) MCEbRows_FFT( (MY)[0], (MX)[0], ht, len, dir, Buf )
#define MCEb_Cols_FFT( MY, MX, ht, len, dir, Buf) MCEbCols_FFT( (MY)[0], (MX)[0], ht, len, dir, Buf )
#define MCEp_filter( MY, MX, MFlt, ht, len ) MCEpfilter( (MY)[0], (MX)[0], (MFlt)[0], ht, len )

#define MCE_FFT         MCEp_FFT
#define MCE_Rows_FFT    MCEp_Rows_FFT
#define MCE_Cols_FFT    MCEp_Cols_FFT
#define MCE_filter      MCEp_filter
#define MCEFFT          MCEpFFT
#define MCERows_FFT     MCEpRows_FFT
#define MCECols_FFT     MCEpCols_FFT
#define MCEfilter       MCEpfilter

#define MCEl_FFT( MY, MX, ht, len, dir )     MCElFFT( (MY)[0], (MX)[0], ht, len, dir )
#define MCEl_Rows_FFT( MY, MX, ht, len, dir) MCElRows_FFT( (MY)[0], (MX)[0], ht, len, dir )
#define MCEl_Cols_FFT( MY, MX, ht, len, dir) MCElCols_FFT( (MY)[0], (MX)[0], ht, len, dir )
#define MCEl_filter( MY, MX, MFlt, ht, len ) MCElfilter( (MY)[0], (MX)[0], (MFlt)[0], ht, len )

#define MCEs_FFT( MY, MX, ht, len, dir )     MCEsFFT( (MY)[0], (MX)[0], ht, len, dir )
#define MCEs_Rows_FFT( MY, MX, ht, len, dir) MCEsRows_FFT( (MY)[0], (MX)[0], ht, len, dir )
#define MCEs_Cols_FFT( MY, MX, ht, len, dir) MCEsCols_FFT( (MY)[0], (MX)[0], ht, len, dir )
#define MCEs_filter( MY, MX, MFlt, ht, len ) MCEsfilter( (MY)[0], (MX)[0], (MFlt)[0], ht, len )

/**************************  Input and Output  **************************/

#define MCE_fprint( stream, MA, ht, len, linewidth ) \
                    MCEfprint( stream, (MA)[0], ht, len, linewidth )
#define MCE_print( MA, ht, len )  MCEfprint( stdout, (MA)[0], ht, len, 80 )
#define MCE_cprint( MA, ht, len ) MCEcprint( (MA)[0], ht, len )
  /*  MCE_print, MCE_cprint usable only for console applications! */

#define MCE_write( str, MA, ht, len )   MCEwrite( str, (MA)[0], ht, len )
#define MCE_read( MA, ht, len, str )    MCEread( (MA)[0], ht, len, str )
#define MCE_setWriteFormat              VCE_setWriteFormat
#define MCE_setWriteSeparate            VCE_setNWriteSeparate
                                   /* write and read in ascii format */
#define MCE_store( str, MA, ht, len )   VCE_store( str, (MA)[0], ((ui)(len))*(ht) )
#define MCE_recall( MA, ht, len, str)   VCE_recall( (MA)[0], ((ui)(len))*(ht), str)
                                  /* store and recall in binary format */


/*************************************************************************
 * Here are now the actual declarations of the functions used internally.*
 * These declarations may change in future versions of MatrixLib!        *
 * You should not care too much about them, except in the case you need  *
 * the actual address of a run-time function (see above). Under all      *
 * "normal" circumstances, use only the names defined above in the       *
 * macro section!                                                        *
 *************************************************************************/

void  __vf MCEgetElement( eComplex *y, cePMatrix X, ui ht, ui len, ui m, ui n );
void  __vf MCEsetElement( cePMatrix X, ui ht, ui len, ui m, ui n, eComplex C );
eComplex _VFAR * __vf MCEPelement( cePMatrix X, ui ht, ui len, ui m, ui n );
                  /* pointer is normalized in memory model HUGE */
#define MCEelement( MA, ht, len, m, n ) (*MCEPelement( MA, ht, len, m, n ))

#define MCEequ0( MA, ht, len )    VCE_equ0( MA, (ht)*(len) )
void   __vf  MCEequ1( cePMatrix MA, ui len );  /* identity matrix */
void   __vf  MCEequm1( cePMatrix MA, ui len );  /* neg. identity matrix */
void   __vf  MCEouterprod( cePMatrix MA, ceVector X,  ceVector Y,
                           ui ht, ui len );

void   __vf  MCERow_equ0( cePMatrix MA, ui ht, ui len,
                         ui iRow );
void   __vf  MCECol_equ0( cePMatrix MA, ui ht, ui len,
                         ui iCol );
void   __vf  MCEDia_equ0( cePMatrix MA, ui len );

void   __vf  MCERow_equC( cePMatrix MA, ui ht, ui len,
                         ui iRow, eComplex C );
void   __vf  MCECol_equC( cePMatrix MA, ui ht, ui len,
                         ui iCol, eComplex C );
void   __vf  MCEDia_equC( cePMatrix MA, ui len, eComplex C );

void   __vf  MCERow_equV( cePMatrix MA, ui ht, ui len,
                         ui iRow, ceVector X );
void   __vf  MCECol_equV( cePMatrix MA, ui ht, ui len,
                         ui iCol, ceVector X );
void   __vf  MCEDia_equV( cePMatrix MA, ui len, ceVector X );

void   __vf  MCETrd_equM( cePMatrix MA, cePMatrix MTrd, ui len );
void   __vf  MCETrd_extract( cePMatrix MTrd, cePMatrix MA, ui len );

#define MCEequM( MB, MA, ht, len )  VCE_equV( MB, MA, (ht)*(len) )
#define MCEneg( MB, MA, ht, len )   VCE_neg( MB, MA, (ht)*(len) )
#define MCEconj( MB, MA, ht, len )  VCE_conj( MB, MA, (ht)*(len) )

void   __vf  MCEUequL( cePMatrix MA, ui len );
void   __vf  MCELequU( cePMatrix MA, ui len );

/********  Extracting a submatrix and copying a submatrix back  *********/

void  __vf  MCEsubmatrix( cePMatrix MSub,
                          ui subHt,  ui subLen,
                          cePMatrix MSrce,
                          ui srceHt,  ui srceLen,
                          ui firstRowInCol,  ui sampInCol,
                          ui firstColInRow,  ui sampInRow );

void  __vf  MCEsubmatrix_equM( cePMatrix MDest,
                               ui destHt,     ui destLen,
                               ui firstRowInCol,  ui sampInCol,
                               ui firstColInRow,  ui sampInRow,
                               cePMatrix MSrce,
                               ui srceHt,     ui srceLen );

void  __vf  MCEequMblock( cePMatrix MSub,
                          ui subHt,  ui subLen,
                          cePMatrix MSrce,
                          ui srceHt,  ui srceLen,
                          ui firstRowInCol,  ui firstColInRow );

void  __vf  MCEblock_equM( cePMatrix MDest,
                           ui destHt,     ui destLen,
                           ui firstRowInCol,  ui firstColInRow,
                           cePMatrix MSrce,
                           ui srceHt,     ui srceLen );

void  __vf  MCEequMblockT( cePMatrix MSub,
                          ui subHt,  ui subLen,
                          cePMatrix MSrce,
                          ui srceHt,  ui srceLen,
                          ui firstRowInCol,  ui firstColInRow );

void  __vf  MCEblock_equMT( cePMatrix MDest,
                           ui destHt,     ui destLen,
                           ui firstRowInCol,  ui firstColInRow,
                           cePMatrix MSrce,
                           ui srceHt,     ui srceLen );


/*****   Extracting a single row or a single column or the diagonal  *****
 *       and storing it into a vector                                    */

void __vf MCERow_extract( ceVector Y, cePMatrix MA, ui ht, ui len,
                           ui iRow );
void __vf MCECol_extract( ceVector Y, cePMatrix MA, ui ht, ui len,
                           ui iCol );
void __vf MCEDia_extract( ceVector Y, cePMatrix MA, ui len );


/**********  Deleting or inserting a row or a column *****************/

void __vf MCERow_delete( cePMatrix MB, cePMatrix MA,
                         ui htA, ui lenA, ui iRow );
void __vf MCECol_delete( cePMatrix MB, cePMatrix MA,
                         ui htA, ui lenA, ui iCol );
void __vf MCERow_insert( cePMatrix MB, cePMatrix MA, ui htB,
                         ui lenB, ui iRow, ceVector X );
void __vf MCECol_insert( cePMatrix MB, cePMatrix MA, ui htB,
                         ui lenB, ui iCol, ceVector X );


/*****************    Basic arithmetic operations ***********************
     performed on one single row,  or one single column of any matrix,
     or on the diagonal of a square matrix                              */

void   __vf  MCERow_neg( cePMatrix MX, ui ht, ui len, ui iRow );
void   __vf  MCECol_neg( cePMatrix MX, ui ht, ui len, ui iCol );

void   __vf  MCERow_conj( cePMatrix MX, ui ht, ui len, ui iRow );
void   __vf  MCECol_conj( cePMatrix MX, ui ht, ui len, ui iCol );

void   __vf  MCERow_addC( cePMatrix MA, ui ht, ui len,
                         ui iRow, eComplex C );
void   __vf  MCECol_addC( cePMatrix MA, ui ht, ui len,
                         ui iCol, eComplex C );
void   __vf  MCEDia_addC( cePMatrix MA, ui len, eComplex C );

void   __vf  MCERow_subC( cePMatrix MA, ui ht, ui len,
                         ui iRow, eComplex C );
void   __vf  MCECol_subC( cePMatrix MA, ui ht, ui len,
                         ui iCol, eComplex C );
void   __vf  MCEDia_subC( cePMatrix MA, ui len, eComplex C );

void   __vf  MCERow_addV( cePMatrix MA, ui ht, ui len,
                         ui iRow, ceVector X );
void   __vf  MCECol_addV( cePMatrix MA, ui ht, ui len,
                         ui iCol, ceVector X );
void   __vf  MCEDia_addV( cePMatrix MA, ui len, ceVector X );

void   __vf  MCERow_subV( cePMatrix MA, ui ht, ui len,
                         ui iRow, ceVector X );
void   __vf  MCECol_subV( cePMatrix MA, ui ht, ui len,
                         ui iCol, ceVector X );
void   __vf  MCEDia_subV( cePMatrix MA, ui len, ceVector X );

void   __vf  MCERow_subrC( cePMatrix MA, ui ht, ui len,
                         ui iRow, eComplex C );
void   __vf  MCECol_subrC( cePMatrix MA, ui ht, ui len,
                         ui iCol, eComplex C );
void   __vf  MCEDia_subrC( cePMatrix MA, ui len, eComplex C );

void   __vf  MCERow_subrV( cePMatrix MA, ui ht, ui len,
                         ui iRow, ceVector X );
void   __vf  MCECol_subrV( cePMatrix MA, ui ht, ui len,
                         ui iCol, ceVector X );
void   __vf  MCEDia_subrV( cePMatrix MA, ui len, ceVector X );

void   __vf  MCERow_mulC( cePMatrix MA, ui ht, ui len,
                         ui iRow, eComplex C );
void   __vf  MCECol_mulC( cePMatrix MA, ui ht, ui len,
                         ui iCol, eComplex C );
void   __vf  MCEDia_mulC( cePMatrix MA, ui len, eComplex C );

void   __vf  MCERow_mulV( cePMatrix MA, ui ht, ui len,
                         ui iRow, ceVector X );
void   __vf  MCECol_mulV( cePMatrix MA, ui ht, ui len,
                         ui iCol, ceVector X );
void   __vf  MCEDia_mulV( cePMatrix MA, ui len, ceVector X );

void   __vf  MCERow_divC( cePMatrix MA, ui ht, ui len,
                         ui iRow, eComplex C );
void   __vf  MCECol_divC( cePMatrix MA, ui ht, ui len,
                         ui iCol, eComplex C );
void   __vf  MCEDia_divC( cePMatrix MA, ui len, eComplex C );

void   __vf  MCERow_divV( cePMatrix MA, ui ht, ui len,
                         ui iRow, ceVector X );
void   __vf  MCECol_divV( cePMatrix MA, ui ht, ui len,
                         ui iCol, ceVector X );
void   __vf  MCEDia_divV( cePMatrix MA, ui len, ceVector X );

void   __vf  MCERow_divrC( cePMatrix MA, ui ht, ui len,
                         ui iRow, eComplex C );
void   __vf  MCECol_divrC( cePMatrix MA, ui ht, ui len,
                         ui iCol, eComplex C );
void   __vf  MCEDia_divrC( cePMatrix MA, ui len, eComplex C );

void   __vf  MCERow_divrV( cePMatrix MA, ui ht, ui len,
                         ui iRow, ceVector X );
void   __vf  MCECol_divrV( cePMatrix MA, ui ht, ui len,
                         ui iCol, ceVector X );
void   __vf  MCEDia_divrV( cePMatrix MA, ui len, ceVector X );


/******  One-dimensional vector operations **********************
         performed along all rows or all columns simultaneously,
         or along the diagonal of a square matrix                */

void     __vf  MCERows_absmax( eVector Y, cePMatrix MA, ui ht, ui len );
void     __vf  MCECols_absmax( eVector Y, cePMatrix MA, ui ht, ui len );
extended __vf  MCEDia_absmax(  cePMatrix MA, ui len );
void     __vf  MCERows_absmin( eVector Y, cePMatrix MA, ui ht, ui len );
void     __vf  MCECols_absmin( eVector Y, cePMatrix MA, ui ht, ui len );
extended __vf  MCEDia_absmin(  cePMatrix MA, ui len );

void     __vf  MCERows_maxReIm( ceVector Y, cePMatrix MA, ui ht, ui len );
void     __vf  MCECols_maxReIm( ceVector Y, cePMatrix MA, ui ht, ui len );
void     __vf  MCERows_minReIm( ceVector Y, cePMatrix MA, ui ht, ui len );
void     __vf  MCECols_minReIm( ceVector Y, cePMatrix MA, ui ht, ui len );

void     __vf  MCERows_absmaxReIm( ceVector Y, cePMatrix MA, ui ht, ui len );
void     __vf  MCECols_absmaxReIm( ceVector Y, cePMatrix MA, ui ht, ui len );
void     __vf  MCERows_absminReIm( ceVector Y, cePMatrix MA, ui ht, ui len );
void     __vf  MCECols_absminReIm( ceVector Y, cePMatrix MA, ui ht, ui len );

void     __vf  MCERows_cabsmax( ceVector Y, cePMatrix MA, ui ht, ui len );
void     __vf  MCECols_cabsmax( ceVector Y, cePMatrix MA, ui ht, ui len );
void     __vf  MCERows_cabsmin( ceVector Y, cePMatrix MA, ui ht, ui len );
void     __vf  MCECols_cabsmin( ceVector Y, cePMatrix MA, ui ht, ui len );

void     __vf  MCERows_sabsmax( ceVector Y, cePMatrix MA, ui ht, ui len );
void     __vf  MCECols_sabsmax( ceVector Y, cePMatrix MA, ui ht, ui len );
void     __vf  MCERows_sabsmin( ceVector Y, cePMatrix MA, ui ht, ui len );
void     __vf  MCECols_sabsmin( ceVector Y, cePMatrix MA, ui ht, ui len );

void     __vf  MCERows_sum( ceVector Y, cePMatrix MA, ui ht, ui len );
void     __vf  MCECols_sum( ceVector Y, cePMatrix MA, ui ht, ui len );
void     __vf  MCERows_prod(ceVector Y, cePMatrix MA, ui ht, ui len );
void     __vf  MCECols_prod(ceVector Y, cePMatrix MA, ui ht, ui len );
#if defined __cplusplus && defined _CMATH_CLASSDEFS
} // the following functions cannot be extern "C", if eComplex is a class
#endif
eComplex __vf  MCEDia_maxReIm(  cePMatrix MA, ui len );
eComplex __vf  MCEDia_minReIm(  cePMatrix MA, ui len );
eComplex __vf  MCEDia_absmaxReIm(  cePMatrix MA, ui len );
eComplex __vf  MCEDia_absminReIm(  cePMatrix MA, ui len );
eComplex __vf  MCEDia_cabsmax(  cePMatrix MA, ui len );
eComplex __vf  MCEDia_cabsmin(  cePMatrix MA, ui len );
eComplex __vf  MCEDia_sabsmax(  cePMatrix MA, ui len );
eComplex __vf  MCEDia_sabsmin(  cePMatrix MA, ui len );
eComplex __vf  MCEDia_sum(  cePMatrix MA, ui len );
eComplex __vf  MCEDia_prod( cePMatrix MA, ui len );
#if defined __cplusplus && defined _CMATH_CLASSDEFS
extern "C" {
#endif
void  __vf  MCERows_runsum( cePMatrix MA, ui ht, ui len );
void  __vf  MCECols_runsum( cePMatrix MA, ui ht, ui len );
void  __vf  MCERows_runprod( cePMatrix MA, ui ht, ui len );
void  __vf  MCECols_runprod( cePMatrix MA, ui ht, ui len );

void  __vf  MCERows_rotate( cePMatrix MA, ui ht, ui len, ssize_t pos );
void  __vf  MCECols_rotate( cePMatrix MA, ui ht, ui len, ssize_t pos );
void  __vf  MCERows_rotate_buf( cePMatrix MA, ui ht, ui len, ssize_t pos, cePMatrix MBuf );
void  __vf  MCECols_rotate_buf( cePMatrix MA, ui ht, ui len, ssize_t pos, cePMatrix MBuf );
void  __vf  MCERows_reflect( cePMatrix MA, ui ht, ui len );
void  __vf  MCECols_reflect( cePMatrix MA, ui ht, ui len );
void  __vf  MCERows_rev( cePMatrix MA, ui ht, ui len );
void  __vf  MCECols_rev( cePMatrix MA, ui ht, ui len );

/********  Operations involving two rows or two colums of one matrix  *****/

void   __vf  MCERows_exchange( cePMatrix MA, ui ht, ui len,
                              ui i1, ui i2 );
void   __vf  MCECols_exchange( cePMatrix MA, ui ht, ui len,
                              ui i1, ui i2 );

void   __vf  MCERows_add( cePMatrix MA, ui ht, ui len,
                          ui destRow, ui sourceRow );
void   __vf  MCECols_add( cePMatrix MA, ui ht, ui len,
                          ui destCol, ui sourceCol );

void   __vf  MCERows_sub( cePMatrix MA, ui ht, ui len,
                          ui destRow, ui sourceRow );
void   __vf  MCECols_sub( cePMatrix MA, ui ht, ui len,
                          ui destCol, ui sourceCol );

void   __vf  MCERows_Cadd( cePMatrix MA, ui ht, ui len,
                           ui destRow, ui sourceRow, eComplex C );
void   __vf  MCECols_Cadd( cePMatrix MA, ui ht, ui len,
                           ui destCol, ui sourceCol, eComplex C );

void   __vf  MCERows_lincomb( cePMatrix MA, ui ht, ui len,
                              ui destRow,  eComplex  destC,
                              ui srceRow,  eComplex  srceC );
void   __vf  MCECols_lincomb( cePMatrix MA, ui ht, ui len,
                              ui destCol,  eComplex  destC,
                              ui srceCol,  eComplex  srceC );


/*************  Transposing and rotating a matrix **********************/

void  __vf  MCEtranspose( cePMatrix MTr, cePMatrix MA,
                          ui htTr, ui lenTr );
void  __vf  MCEhermconj( cePMatrix MHConj, cePMatrix MA,
                          ui htTr, ui lenTr );
void  __vf  MCErotate90(  cePMatrix MRot, cePMatrix MA, ui htRot, ui lenRot );
#define     MCErotate180( MRot, MA, htRot, lenRot ) \
                VCE_rev( MRot, MA, (htRot)*(lenRot) )
void  __vf  MCErotate270( cePMatrix MRot, cePMatrix MA, ui htRot, ui lenRot );


/************************ Matrix Arithmetics *************************/

#define MCEaddM( MC, MA, MB, htA, lenA ) \
                 VCE_addV( MC, MA, MB, (htA)*(lenA) )
void __vf  MCEaddMT( cePMatrix MC, cePMatrix MA, cePMatrix MB,
                     ui htA, ui lenA );
#define MCEsubM( MC, MA, MB, htA, lenA ) \
                 VCE_subV( MC, MA, MB, (htA)*(lenA) )
void __vf  MCEsubMT( cePMatrix MC, cePMatrix MA, cePMatrix MB,
                     ui htA, ui lenA );
void __vf  MCEsubrMT( cePMatrix MC, cePMatrix MA, cePMatrix MB,
                     ui htA, ui lenA );
#define MCEmulC( MB, MA, htA, lenA, C ) \
                 VCE_mulC( MB, MA, (htA)*(lenA), C )
#define MCEdivC( MB, MA, htA, lenA, C ) \
                 VCE_divC( MB, MA, (htA)*(lenA), C )
#define MCEmulReC( MB, MA, htA, lenA, CRe ) \
                 VCE_mulReC( MB, MA, (htA)*(lenA), CRe )
#define MCEdivReC( MB, MA, htA, lenA, CRe ) \
                 VCE_divReC( MB, MA, (htA)*(lenA), CRe )
#define MCElincomb( MC, MA, MB, htA, lenA, CA, CB ) \
                 VCE_lincomb( MC, MA, MB, (htA)*(lenA), CA, CB )
void  __vf  MCEmulV( ceVector Y, cePMatrix MA, ceVector X,
                    ui htA, ui lenA );
void  __vf  MCETmulV( ceVector Y, cePMatrix MA, ceVector X,
                     ui htA, ui lenA );
void  __vf  VCEmulM( ceVector Y, ceVector X, cePMatrix MA,
                    ui htA, ui lenA );
void  __vf  VCEmulMT( ceVector Y, ceVector X, cePMatrix MA,
                     ui htA, ui lenA );
void  __vf  MCEmulM( cePMatrix MC, cePMatrix MA, cePMatrix MB,
                    ui htA, ui lenA, ui lenB );
void  __vf  MCEmulMT( cePMatrix MC, cePMatrix MA, cePMatrix MB,
                    ui htA, ui lenA, ui htB );
void  __vf  MCEmulMH( cePMatrix MC, cePMatrix MA, cePMatrix MB,
                    ui htA, ui lenA, ui htB );
void  __vf  MCETmulM( cePMatrix MC, cePMatrix MA, cePMatrix MB,
                    ui htA, ui lenA, ui lenB );
void  __vf  MCEHmulM( cePMatrix MC, cePMatrix MA, cePMatrix MB,
                    ui htA, ui lenA, ui lenB );
void  __vf  MCETmulMT( cePMatrix MC, cePMatrix MA, cePMatrix MB,
                    ui htA, ui lenA, ui htB );
void  __vf  MCETmulMH( cePMatrix MC, cePMatrix MA, cePMatrix MB,
                    ui htA, ui lenA, ui htB );
void  __vf  MCEdiamulM( cePMatrix MC, cePMatrix MADia, cePMatrix MB,
                    ui htB, ui lenB );
void  __vf  MCEdiamulMT( cePMatrix MC, cePMatrix MADia, cePMatrix MB,
                    ui htB, ui lenB );
void  __vf  MCEmulMdia( cePMatrix MC, cePMatrix MA, cePMatrix MBDia,
                    ui htA, ui lenA );
void  __vf  MCETmulMdia( cePMatrix MC, cePMatrix MA, cePMatrix MBDia,
                    ui htA, ui lenA );

/*************************  Linear Algebra    *****************************/

int    __vf  MCELUdecompose( cePMatrix MLU,  uiVector Ind, cePMatrix MA,
                            ui len );

void     __vf  MCELUsolve( ceVector X, cePMatrix MLU, ceVector B, uiVector Ind,
                          ui len );
void     __vf  MCELUinv( cePMatrix MInv, cePMatrix MLU, uiVector Ind,
                        ui len );
#if defined __cplusplus && defined _CMATH_CLASSDEFS
} // the following functions cannot be extern "C", if fComplex is a class
#endif
eComplex __vf  MCELUdet( cePMatrix MLU, ui len, int permut );
#if defined __cplusplus && defined _CMATH_CLASSDEFS
extern "C" {
#endif
void     __vf  MCELUimprove( ceVector X, ceVector B, cePMatrix MA, cePMatrix MLU,
                            uiVector Ind, ui len );
/*
int   __vf  MCESVdecompose( cePMatrix MU, cePMatrix MV, ceVector W, cePMatrix MA,
                           ui htA, ui lenA );
void  __vf  MCESVsolve( ceVector X, cePMatrix MU, cePMatrix MV, ceVector W,
                       ceVector B, ui htU, ui lenU ); */

          /*  functions using LUD or SVD     */
int    __vf  MCEsolve( ceVector X, cePMatrix MA, ceVector B, ui len );
                  /* ret.value != 0 signals error */
int    __vf  MCEinv( cePMatrix MInv, cePMatrix MA, ui len );
                 /* ret.value != 0 signals error */
#if defined __cplusplus && defined _CMATH_CLASSDEFS
} // the following functions cannot be extern "C", if fComplex is a class
#endif
eComplex  __vf  MCEdet( cePMatrix MA, ui len );
#if defined __cplusplus && defined _CMATH_CLASSDEFS
extern "C" {
#endif

/* int    __vf  MCEsolveBySVD( ceVector X, cePMatrix MA, ceVector B,
                           ui ht, ui len );
                 *  ret.value != 0 signals failure *
int    __vf  MCEsafeSolve( ceVector X, cePMatrix MA, ceVector B, ui len );
              * ret.value 0: success via LUD; 1: success via SVD; -1: error */


/*************  Two-Dimensional Fourier-Transform Methods *****************/

void  __vf  MCEpFFT( cePMatrix MY, cePMatrix MX, ui ht, ui len, int dir );
void  __vf  MCEpfilter( cePMatrix MY, cePMatrix MX, cePMatrix MFlt, ui ht, ui len );
void  __vf  MCEpRows_FFT( cePMatrix MY, cePMatrix MX, ui ht, ui len, int dir );
void  __vf  MCEpCols_FFT( cePMatrix MY, cePMatrix MX, ui ht, ui len, int dir );
void  __vf  MCEbFFT( cePMatrix MY, cePMatrix MX, ui ht, ui len, int dir, ceVector Buf );
void  __vf  MCEbRows_FFT( cePMatrix MY, cePMatrix MX, ui ht, ui len, int dir, ceVector Buf );
void  __vf  MCEbCols_FFT( cePMatrix MY, cePMatrix MX, ui ht, ui len, int dir, ceVector Buf );

void  __vf  MCElFFT( cePMatrix MY, cePMatrix MX, ui ht, ui len, int dir );
void  __vf  MCElfilter( cePMatrix MY, cePMatrix MX, cePMatrix MFlt, ui ht, ui len );
void  __vf  MCElRows_FFT( cePMatrix MY, cePMatrix MX, ui ht, ui len, int dir );
void  __vf  MCElCols_FFT( cePMatrix MY, cePMatrix MX, ui ht, ui len, int dir );
void  __vf  MCEsFFT( cePMatrix MY, cePMatrix MX, ui ht, ui len, int dir );
void  __vf  MCEsfilter( cePMatrix MY, cePMatrix MX, cePMatrix MFlt, ui ht, ui len );
void  __vf  MCEsRows_FFT( cePMatrix MY, cePMatrix MX, ui ht, ui len, int dir );
void  __vf  MCEsCols_FFT( cePMatrix MY, cePMatrix MX, ui ht, ui len, int dir );

      /*************  Input and Output  ****************/

#define MCEprint( MA, ht, len )  MCEfprint( stdout, MA, ht, len, 80 )
void __vf  MCEfprint( FILE _VFAR *stream, cePMatrix MA, ui ht,
                     ui len, unsigned linewidth );
void __vf  MCEcprint( cePMatrix MA, ui ht, ui len );
void __vf  MCEwrite( FILE _VFAR *stream, cePMatrix X, ui ht, ui len  );
#if !((defined __BORLANDC__) && (__BORLANDC__ < 0x710))
		/* modern compiler versions:  */
	void __vf MCEread( cePMatrix X, ui ht, ui len, FILE _VFAR *stream );
#else /* older Borland compiler versions need separate implementation */
	void __vf MCEread1( cePMatrix X, ui ht, ui len, FILE _VFAR *stream );
	#define MCEread  MCEread1
#endif
#define MCEstore( str, MA, ht, len ) VCE_store( str, MA, (len)*(ht) )
#define MCErecall( MA, ht, len, str) VCE_recall( MA, (len)*(ht), str)

#ifdef __cplusplus
}   // end of extern "C"
#endif

#else  /*  MSVC, Optima++:  MCE_ functions are identical to MCD_ */
#include <MCDstd.h>
#define MCE_matrix       MCD_matrix
#define MCE_matrix0      MCD_matrix0
#define MCE_matrix_dbg   MCD_matrix_dbg
#define MCE_matrix0_dbg  MCD_matrix0_dbg
#define MCE_Pelement   MCD_Pelement
#define MCE_element    MCD_element
#define MCE_getElement MCD_getElement
#define MCE_setElement MCD_setElement
#define MCE_equ0       MCD_equ0
#define MCE_equ1       MCD_equ1
#define MCE_equm1      MCD_equm1
#define MCE_randomLC( MA, ht, len, seed, Min, Max, state ) \
                       VCD_randomLC( (MA)[0], (ht)*(len), seed, Min, Max, state )
#define MCE_random( MA, ht, len, seed, Min, Max ) \
                       VCD_random( (MA)[0], (ht)*(len), seed, Min, Max )
#define MCE_outerprod  MCD_outerprod
#define MCE_Row_equ0   MCD_Row_equ0
#define MCE_Col_equ0   MCD_Col_equ0
#define MCE_Dia_equ0   MCD_Dia_equ0
#define MCE_Row_equC   MCD_Row_equC
#define MCE_Col_equC   MCD_Col_equC
#define MCE_Dia_equC   MCD_Dia_equC
#define MCE_Row_equV   MCD_Row_equV
#define MCE_Col_equV   MCD_Col_equV
#define MCE_Dia_equV   MCD_Dia_equV
#define MCE_Trd_equM   MCD_Trd_equM
#define MCE_Trd_extract MCD_Trd_extract
#define MCE_equM       MCD_equM
#define MCE_neg        MCD_neg
#define MCE_conj       MCD_conj
#define MCE_UequL      MCD_UequL
#define MCE_LequU      MCD_LequU
#define M_CEtoCF( MCF, MCE, ht, len ) V_CEtoCF( (MCF)[0], (MCE)[0], (ht)*(len) )
#define M_CFtoCE( MCE, MCF, ht, len ) V_CFtoCE( (MCE)[0], (MCF)[0], (ht)*(len) )
#define M_CEtoCD( MCD, MCE, ht, len ) V_CEtoCD( (MCD)[0], (MCE)[0], (ht)*(len) )
#define M_CDtoCE( MCE, MCD, ht, len ) V_CDtoCE( (MCE)[0], (MCD)[0], (ht)*(len) )
#define ME_CtoRe( MY, MCX, ht, len )  VD_CtoRe( (MY)[0],  (MCX)[0], (ht)*(len) )
#define ME_CtoIm( MY, MCX, ht, len )  VD_CtoIm( (MY)[0],  (MCX)[0], (ht)*(len) )
#define ME_CtoReIm( MYRe, MYIm, MCX, ht, len )  VD_CtoReIm( (MYRe)[0], (MYIm)[0], (MCX)[0], (ht)*(len) )
#define ME_RetoC( MCY, MX, ht, len )  VD_RetoC( (MCY)[0], (MX)[0],  (ht)*(len) )
#define ME_ImtoC( MCY, MX, ht, len )  VD_ImtoC( (MCY)[0], (MX)[0],  (ht)*(len) )
#define ME_ReImtoC( MCY, MXRe, MXIm, ht, len )  VD_ReImtoC( (MCY)[0], (MXRe)[0], (MXIm)[0], (ht)*(len) )
#define MCE_submatrix           MCD_submatrix
#define MCE_submatrix_equM      MCD_submatrix_equM
#define MCE_equMblock           MCD_equMblock
#define MCE_block_equM          MCD_block_equM
#define MCE_equMblockT          MCD_equMblockT
#define MCE_block_equMT         MCD_block_equMT
#define MCE_Row_extract         MCD_Row_extract
#define MCE_Col_extract         MCD_Col_extract
#define MCE_Dia_extract         MCD_Dia_extract
#define MCE_Row_insert          MCD_Row_insert
#define MCE_Col_insert          MCD_Col_insert
#define MCE_Row_delete          MCD_Row_delete
#define MCE_Col_delete          MCD_Col_delete
#define MCE_Row_neg             MCD_Row_neg
#define MCE_Col_neg             MCD_Col_neg
#define MCE_Row_conj            MCD_Row_conj
#define MCE_Col_conj            MCD_Col_conj
#define MCE_Row_addC            MCD_Row_addC
#define MCE_Col_addC            MCD_Col_addC 
#define MCE_Dia_addC            MCD_Dia_addC 
#define MCE_Row_addV            MCD_Row_addV
#define MCE_Col_addV            MCD_Col_addV
#define MCE_Dia_addV            MCD_Dia_addV
#define MCE_Row_subC            MCD_Row_subC 
#define MCE_Col_subC            MCD_Col_subC
#define MCE_Dia_subC            MCD_Dia_subC
#define MCE_Row_subV            MCD_Row_subV
#define MCE_Col_subV            MCD_Col_subV
#define MCE_Dia_subV            MCD_Dia_subV
#define MCE_Row_subrC           MCD_Row_subrC
#define MCE_Col_subrC           MCD_Col_subrC
#define MCE_Dia_subrC           MCD_Dia_subrC 
#define MCE_Row_subrV           MCD_Row_subrV 
#define MCE_Col_subrV           MCD_Col_subrV
#define MCE_Dia_subrV           MCD_Dia_subrV
#define MCE_Row_mulC            MCD_Row_mulC
#define MCE_Col_mulC            MCD_Col_mulC
#define MCE_Dia_mulC            MCD_Dia_mulC 
#define MCE_Row_mulV            MCD_Row_mulV
#define MCE_Col_mulV            MCD_Col_mulV
#define MCE_Dia_mulV            MCD_Dia_mulV
#define MCE_Row_divC            MCD_Row_divC
#define MCE_Col_divC            MCD_Col_divC   
#define MCE_Dia_divC            MCD_Dia_divC
#define MCE_Row_divV            MCD_Row_divV
#define MCE_Col_divV            MCD_Col_divV
#define MCE_Dia_divV            MCD_Dia_divV
#define MCE_Row_divrC           MCD_Row_divrC
#define MCE_Col_divrC           MCD_Col_divrC
#define MCE_Dia_divrC           MCD_Dia_divrC 
#define MCE_Row_divrV           MCD_Row_divrV
#define MCE_Col_divrV           MCD_Col_divrV
#define MCE_Dia_divrV           MCD_Dia_divrV
#define MCE_Rows_absmax         MCD_Rows_absmax
#define MCE_Cols_absmax         MCD_Cols_absmax  
#define MCE_Dia_absmax          MCD_Dia_absmax
#define MCE_Rows_absmin         MCD_Rows_absmin
#define MCE_Cols_absmin         MCD_Cols_absmin
#define MCE_Dia_absmin          MCD_Dia_absmin
#define MCE_Rows_maxReIm        MCD_Rows_maxReIm
#define MCE_Cols_maxReIm        MCD_Cols_maxReIm
#define MCE_Dia_maxReIm         MCD_Dia_maxReIm
#define MCE_Rows_minReIm        MCD_Rows_minReIm
#define MCE_Cols_minReIm        MCD_Cols_minReIm
#define MCE_Dia_minReIm         MCD_Dia_minReIm
#define MCE_Rows_absmaxReIm     MCD_Rows_absmaxReIm
#define MCE_Cols_absmaxReIm     MCD_Cols_absmaxReIm
#define MCE_Dia_absmaxReIm      MCD_Dia_absmaxReIm
#define MCE_Rows_absminReIm     MCD_Rows_absminReIm
#define MCE_Cols_absminReIm     MCD_Cols_absminReIm
#define MCE_Dia_absminReIm      MCD_Dia_absminReIm
#define MCE_Rows_cabsmax        MCD_Rows_cabsmax
#define MCE_Cols_cabsmax        MCD_Cols_cabsmax
#define MCE_Dia_cabsmax         MCD_Dia_cabsmax
#define MCE_Rows_cabsmin        MCD_Rows_cabsmin
#define MCE_Cols_cabsmin        MCD_Cols_cabsmin
#define MCE_Dia_cabsmin         MCD_Dia_cabsmin
#define MCE_Rows_sabsmax        MCD_Rows_sabsmax
#define MCE_Cols_sabsmax        MCD_Cols_sabsmax
#define MCE_Dia_sabsmax         MCD_Dia_sabsmax
#define MCE_Rows_sabsmin        MCD_Rows_sabsmin
#define MCE_Cols_sabsmin        MCD_Cols_sabsmin
#define MCE_Dia_sabsmin         MCD_Dia_sabsmin
#define MCE_Rows_sum            MCD_Rows_sum
#define MCE_Cols_sum            MCD_Cols_sum
#define MCE_Dia_sum             MCD_Dia_sum
#define MCE_Rows_prod           MCD_Rows_prod
#define MCE_Cols_prod           MCD_Cols_prod
#define MCE_Dia_prod            MCD_Dia_prod
#define MCE_Rows_runsum         MCD_Rows_runsum
#define MCE_Cols_runsum         MCD_Cols_runsum
#define MCE_Rows_runprod        MCD_Rows_runprod
#define MCE_Cols_runprod        MCD_Cols_runprod
#define MCE_Rows_rotate         MCD_Rows_rotate
#define MCE_Cols_rotate         MCD_Cols_rotate
#define MCE_Rows_rotate_buf     MCD_Rows_rotate_buf
#define MCE_Cols_rotate_buf     MCD_Cols_rotate_buf
#define MCE_Rows_reflect        MCD_Rows_reflect
#define MCE_Cols_reflect        MCD_Cols_reflect
#define MCE_Rows_rev            MCD_Rows_rev
#define MCE_Cols_rev            MCD_Cols_rev
#define MCE_Rows_exchange       MCD_Rows_exchange
#define MCE_Cols_exchange       MCD_Cols_exchange
#define MCE_Rows_add            MCD_Rows_add
#define MCE_Cols_add            MCD_Cols_add
#define MCE_Rows_sub            MCD_Rows_sub
#define MCE_Cols_sub            MCD_Cols_sub
#define MCE_Rows_Cadd           MCD_Rows_Cadd
#define MCE_Cols_Cadd           MCD_Cols_Cadd
#define MCE_Rows_lincomb        MCD_Rows_lincomb
#define MCE_Cols_lincomb        MCD_Cols_lincomb
#define MCE_transpose           MCD_transpose
#define MCE_hermconj            MCD_hermconj
#define MCE_rotate90            MCD_rotate90
#define MCE_rotate180           MCD_rotate180
#define MCE_rotate270           MCD_rotate270
#define MCE_addM                MCD_addM
#define MCE_addMT               MCD_addMT
#define MCE_subM                MCD_subM
#define MCE_subMT               MCD_subMT
#define MCE_subrMT              MCD_subrMT
#define MCE_mulC                MCD_mulC
#define MCE_divC                MCD_divC
#define MCE_mulReC              MCD_mulReC
#define MCE_divReC              MCD_divReC
#define MCE_lincomb             MCD_lincomb
#define MCE_mulV                MCD_mulV
#define MCE_TmulV               MCD_TmulV
#define VCE_mulM                VCD_mulM
#define VCE_mulMT               VCD_mulMT
#define MCE_mulM                MCD_mulM
#define MCE_mulMT               MCD_mulMT
#define MCE_mulMH               MCD_mulMH
#define MCE_TmulM               MCD_TmulM
#define MCE_HmulM               MCD_HmulM
#define MCE_TmulMT              MCD_TmulMT
#define MCE_TmulMH              MCD_TmulMH
#define MCEdia_mulM             MCDdia_mulM
#define MCEdia_mulMT            MCDdia_mulMT
#define MCE_mulMdia             MCD_mulMdia
#define MCE_TmulMdia            MCD_TmulMdia
#define MCE_LUdecompose         MCD_LUdecompose
#define MCE_LUDresult           MCD_LUDresult
#define MCE_LUDsetEdit          MCD_LUDsetEdit
#define MCE_LUDgetEdit          MCD_LUDgetEdit
#define MCE_LUsolve             MCD_LUsolve
#define MCE_LUinv               MCD_LUinv
#define MCE_LUdet               MCD_LUdet
#define MCE_LUimprove           MCD_LUimprove
// #define MCE_SVdecompose         MCD_SVdecompose
// #define MCE_SVsolve             MCD_SVsolve
// #define MCE_SVimprove           MCD_SVimprove
// #define MCE_SVDsetEdit          MCD_SVDsetEdit
// #define MCE_SVDgetEdit          MCD_SVDgetEdit
#define MCE_solve               MCD_solve
#define MCE_inv                 MCD_inv
#define MCE_det                 MCD_det
// #define MCE_solveBySVD          MCD_solveBySVD
// #define MCE_safeSolve           MCD_safeSolve
#define MCEp_FFT                MCDp_FFT
#define MCEp_Rows_FFT           MCDp_Rows_FFT
#define MCEp_Cols_FFT           MCDp_Cols_FFT
#define MCEp_filter             MCDp_filter
#define MCEl_FFT                MCDl_FFT
#define MCEl_Rows_FFT           MCDl_Rows_FFT
#define MCEl_Cols_FFT           MCDl_Cols_FFT
#define MCEl_filter             MCDl_filter
#define MCEs_FFT                MCDs_FFT
#define MCEs_Rows_FFT           MCDs_Rows_FFT
#define MCEs_Cols_FFT           MCDs_Cols_FFT
#define MCEs_filter             MCDs_filter
#define MCE_FFT                 MCD_FFT
#define MCE_Rows_FFT            MCD_Rows_FFT
#define MCE_Cols_FFT            MCD_Cols_FFT
#define MCE_filter              MCD_filter
#define MCE_fprint              MCD_fprint
#define MCE_print               MCD_print
#define MCE_cprint              MCD_cprint
#define MCE_write               MCD_write
#define MCE_read                MCD_read
#define MCE_setWriteFormat      VCE_setWriteFormat
#define MCE_setWriteSeparate    VCE_setNWriteSeparate
#define MCE_store               MCD_store
#define MCE_recall              MCD_recall

#define MCEPelement   MCDPelement
#define MCEelement    MCDelement
#define MCEgetElement MCDgetElement
#define MCEsetElement MCDsetElement
#define MCEequ0       MCDequ0
#define MCEequ1       MCDequ1
#define MCEequm1      MCDequm1
#define MCErandomLC( MA, ht, len, seed, Min, Max, state ) \
                       VCD_randomLC( (MA), (ht)*(len), seed, Min, Max, state )
#define MCErandom( MA, ht, len, seed, Min, Max ) \
                       VCD_random( (MA), (ht)*(len), seed, Min, Max )
#define MCEouterprod  MCDouterprod
#define MCERow_equ0   MCDRow_equ0
#define MCECol_equ0   MCDCol_equ0
#define MCEDia_equ0   MCDDia_equ0
#define MCERow_equC   MCDRow_equC
#define MCECol_equC   MCDCol_equC
#define MCEDia_equC   MCDDia_equC
#define MCERow_equV   MCDRow_equV
#define MCECol_equV   MCDCol_equV
#define MCEDia_equV   MCDDia_equV
#define MCETrd_equM   MCDTrd_equM
#define MCETrd_extract MCDTrd_extract
#define MCEequM       MCDequM
#define MCEneg        MCDneg
#define MCEconj       MCDconj
#define MCEUequL      MCDUequL
#define MCELequU      MCDLequU
#define MCEtoCF( MCF, MCE, ht, len ) V_CEtoCF( (MCF), (MCE), (ht)*(len) )
#define MCFtoCE( MCE, MCF, ht, len ) V_CFtoCE( (MCE), (MCF), (ht)*(len) )
#define MCEtoCD( MCD, MCE, ht, len ) V_CEtoCD( (MCD), (MCE), (ht)*(len) )
#define MCDtoCE( MCE, MCD, ht, len ) V_CDtoCE( (MCE), (MCD), (ht)*(len) )
#define MECtoRe( MY, MCX, ht, len )  VD_CtoRe( (MY),  (MCX), (ht)*(len) )
#define MECtoIm( MY, MCX, ht, len )  VD_CtoIm( (MY),  (MCX), (ht)*(len) )
#define MECtoReIm( MYRe, MYIm, MCX, ht, len )  VD_CtoReIm( (MYRe), (MYIm), (MCX), (ht)*(len) )
#define MERetoC( MCY, MX, ht, len )  VD_RetoC( (MCY), (MX),  (ht)*(len) )
#define MEImtoC( MCY, MX, ht, len )  VD_ImtoC( (MCY), (MX),  (ht)*(len) )
#define MEReImtoC( MCY, MXRe, MXIm, ht, len )  VD_ReImtoC( (MCY), (MXRe), (MXIm), (ht)*(len) )
#define MCEsubmatrix           MCDsubmatrix
#define MCEsubmatrix_equM      MCDsubmatrix_equM
#define MCEequMblock           MCDequMblock
#define MCEblock_equM          MCDblock_equM
#define MCEequMblockT          MCDequMblockT
#define MCEblock_equMT         MCDblock_equMT
#define MCERow_extract         MCDRow_extract
#define MCECol_extract         MCDCol_extract
#define MCEDia_extract         MCDDia_extract
#define MCERow_insert          MCDRow_insert
#define MCECol_insert          MCDCol_insert
#define MCERow_delete          MCDRow_delete
#define MCECol_delete          MCDCol_delete
#define MCERow_neg             MCDRow_neg
#define MCECol_neg             MCDCol_neg
#define MCERow_conj            MCDRow_conj
#define MCECol_conj            MCDCol_conj
#define MCERow_addC            MCDRow_addC
#define MCECol_addC            MCDCol_addC 
#define MCEDia_addC            MCDDia_addC 
#define MCERow_addV            MCDRow_addV
#define MCECol_addV            MCDCol_addV
#define MCEDia_addV            MCDDia_addV
#define MCERow_subC            MCDRow_subC 
#define MCECol_subC            MCDCol_subC
#define MCEDia_subC            MCDDia_subC
#define MCERow_subV            MCDRow_subV
#define MCECol_subV            MCDCol_subV
#define MCEDia_subV            MCDDia_subV
#define MCERow_subrC           MCDRow_subrC
#define MCECol_subrC           MCDCol_subrC
#define MCEDia_subrC           MCDDia_subrC 
#define MCERow_subrV           MCDRow_subrV 
#define MCECol_subrV           MCDCol_subrV
#define MCEDia_subrV           MCDDia_subrV
#define MCERow_mulC            MCDRow_mulC
#define MCECol_mulC            MCDCol_mulC
#define MCEDia_mulC            MCDDia_mulC 
#define MCERow_mulV            MCDRow_mulV
#define MCECol_mulV            MCDCol_mulV
#define MCEDia_mulV            MCDDia_mulV
#define MCERow_divC            MCDRow_divC
#define MCECol_divC            MCDCol_divC   
#define MCEDia_divC            MCDDia_divC
#define MCERow_divV            MCDRow_divV
#define MCECol_divV            MCDCol_divV
#define MCEDia_divV            MCDDia_divV
#define MCERow_divrC           MCDRow_divrC
#define MCECol_divrC           MCDCol_divrC
#define MCEDia_divrC           MCDDia_divrC 
#define MCERow_divrV           MCDRow_divrV
#define MCECol_divrV           MCDCol_divrV
#define MCEDia_divrV           MCDDia_divrV
#define MCERows_absmax         MCDRows_absmax
#define MCECols_absmax         MCDCols_absmax  
#define MCEDia_absmax          MCDDia_absmax
#define MCERows_absmin         MCDRows_absmin
#define MCECols_absmin         MCDCols_absmin
#define MCEDia_absmin          MCDDia_absmin
#define MCERows_maxReIm        MCDRows_maxReIm
#define MCECols_maxReIm        MCDCols_maxReIm
#define MCEDia_maxReIm         MCDDia_maxReIm
#define MCERows_minReIm        MCDRows_minReIm
#define MCECols_minReIm        MCDCols_minReIm
#define MCEDia_minReIm         MCDDia_minReIm
#define MCERows_absmaxReIm     MCDRows_absmaxReIm
#define MCECols_absmaxReIm     MCDCols_absmaxReIm
#define MCEDia_absmaxReIm      MCDDia_absmaxReIm
#define MCERows_absminReIm     MCDRows_absminReIm
#define MCECols_absminReIm     MCDCols_absminReIm
#define MCEDia_absminReIm      MCDDia_absminReIm
#define MCERows_cabsmax        MCDRows_cabsmax
#define MCECols_cabsmax        MCDCols_cabsmax
#define MCEDia_cabsmax         MCDDia_cabsmax
#define MCERows_cabsmin        MCDRows_cabsmin
#define MCECols_cabsmin        MCDCols_cabsmin
#define MCEDia_cabsmin         MCDDia_cabsmin
#define MCERows_sabsmax        MCDRows_sabsmax
#define MCECols_sabsmax        MCDCols_sabsmax
#define MCEDia_sabsmax         MCDDia_sabsmax
#define MCERows_sabsmin        MCDRows_sabsmin
#define MCECols_sabsmin        MCDCols_sabsmin
#define MCEDia_sabsmin         MCDDia_sabsmin
#define MCERows_sum            MCDRows_sum
#define MCECols_sum            MCDCols_sum
#define MCEDia_sum             MCDDia_sum
#define MCERows_prod           MCDRows_prod
#define MCECols_prod           MCDCols_prod
#define MCEDia_prod            MCDDia_prod
#define MCERows_runsum         MCDRows_runsum
#define MCECols_runsum         MCDCols_runsum
#define MCERows_runprod        MCDRows_runprod
#define MCECols_runprod        MCDCols_runprod
#define MCERows_rotate         MCDRows_rotate
#define MCECols_rotate         MCDCols_rotate
#define MCERows_rotate_buf     MCDRows_rotate_buf
#define MCECols_rotate_buf     MCDCols_rotate_buf
#define MCERows_reflect        MCDRows_reflect
#define MCECols_reflect        MCDCols_reflect
#define MCERows_rev            MCDRows_rev
#define MCECols_rev            MCDCols_rev
#define MCERows_exchange       MCDRows_exchange
#define MCECols_exchange       MCDCols_exchange
#define MCERows_add            MCDRows_add
#define MCECols_add            MCDCols_add
#define MCERows_sub            MCDRows_sub
#define MCECols_sub            MCDCols_sub
#define MCERows_Cadd           MCDRows_Cadd
#define MCECols_Cadd           MCDCols_Cadd
#define MCERows_lincomb        MCDRows_lincomb
#define MCECols_lincomb        MCDCols_lincomb
#define MCEtranspose           MCDtranspose
#define MCEhermconj            MCDhermconj
#define MCErotate90            MCDrotate90
#define MCErotate180           MCDrotate180
#define MCErotate270           MCDrotate270
#define MCEaddM                MCDaddM
#define MCEaddMT               MCDaddMT
#define MCEsubM                MCDsubM
#define MCEsubMT               MCDsubMT
#define MCEsubrMT              MCDsubrMT
#define MCEmulC                MCDmulC
#define MCEdivC                MCDdivC
#define MCEmulReC              MCDmulReC
#define MCEdivReC              MCDdivReC
#define MCElincomb             MCDlincomb
#define MCEmulV                MCDmulV
#define MCETmulV               MCDTmulV
#define VCEmulM                VCDmulM
#define VCEmulMT               VCDmulMT
#define MCEmulM                MCDmulM
#define MCEmulMT               MCDmulMT
#define MCEmulMH               MCDmulMH
#define MCETmulM               MCDTmulM
#define MCEHmulM               MCDHmulM
#define MCETmulMT              MCDTmulMT
#define MCETmulMH              MCDTmulMH
#define MCEdiamulM             MCDdiamulM
#define MCEdiamulMT            MCDdiamulMT
#define MCEmulMdia             MCDmulMdia
#define MCETmulMdia            MCDTmulMdia
#define MCELUdecompose         MCDLUdecompose
#define MCELUDresult           MCDLUDresult
#define MCELUDsetEdit          MCDLUDsetEdit
#define MCELUDgetEdit          MCDLUDgetEdit
#define MCELUsolve             MCDLUsolve
#define MCELUinv               MCDLUinv
#define MCELUdet               MCDLUdet
#define MCELUimprove           MCDLUimprove
// #define MCESVdecompose         MCDSVdecompose
// #define MCESVsolve             MCDSVsolve
// #define MCESVimprove           MCDSVimprove
// #define MCESVDsetEdit          MCDSVDsetEdit
// #define MCESVDgetEdit          MCDSVDgetEdit
#define MCEsolve               MCDsolve
#define MCEinv                 MCDinv
#define MCEdet                 MCDdet
// #define MCEsolveBySVD          MCDsolveBySVD
// #define MCEsafeSolve           MCDsafeSolve
#define MCEpFFT                MCDpFFT
#define MCEpRows_FFT           MCDpRows_FFT
#define MCEpCols_FFT           MCDpCols_FFT
#define MCEpfilter             MCDpfilter
#define MCElFFT                MCDlFFT
#define MCElRows_FFT           MCDlRows_FFT
#define MCElCols_FFT           MCDlCols_FFT
#define MCElfilter             MCDlfilter
#define MCEsFFT                MCDsFFT
#define MCEsRows_FFT           MCDsRows_FFT
#define MCEsCols_FFT           MCDsCols_FFT
#define MCEsfilter             MCDsfilter
#define MCEFFT                 MCDFFT
#define MCERows_FFT            MCDRows_FFT
#define MCECols_FFT            MCDCols_FFT
#define MCEfilter              MCDfilter
#define MCEFFT                  MCDFFT
#define MCERows_FFT             MCDRows_FFT
#define MCECols_FFT             MCDCols_FFT
#define MCEfilter               MCDfilter
#define MCEfprint              MCDfprint
#define MCEprint               MCDprint
#define MCEcprint              MCDcprint
#define MCEwrite               MCDwrite
#define MCEread                MCDread
#define MCEsetWriteFormat      VCE_setWriteFormat
#define MCEsetWriteSeparate    VCE_setNWriteSeparate
#define MCEstore               MCDstore
#define MCErecall              MCDrecall
#endif  /*  Borland, Microsoft, Powersoft */
#endif /* __MCESTD_H */
