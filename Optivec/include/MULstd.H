/*  MULstd.h

  matrix management functions:
  manipulations on matrices of data type "unsigned long"

  Copyright (c) 1996-2017 by OptiCode - Dr. Martin Sander Software Dev.
  All Rights Reserved.
*/

#if !defined( __MULSTD_H )
#define __MULSTD_H
#if !defined( __MATLIB_H )
#include <MatLib.h>
#endif
#if !defined( __VULSTD_H )
#include <VULstd.h>
#endif
#if !defined( __VULMATH_H )
#include <VULmath.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif

/*************   Dynamic Generation of Matrices   ************************/

ulMatrix __vf  MUL_matrix(  ui ht, ui len );
ulMatrix __vf  MUL_matrix0( ui ht, ui len );
#if defined (_MSC_VER) && defined (_DEBUG)
    ulMatrix __vf  MUL_matrix_dbg(  ui ht, ui len );
    ulMatrix __vf  MUL_matrix0_dbg( ui ht, ui len );
    #if defined (_INC_CRTDBG) && defined (_CRTDBG_MAP_ALLOC)
	    /* Automatic mapping for memory-leak detection by CRT debugging switched on? */
        #define MUL_matrix  MUL_matrix_dbg
        #define MUL_matrix0 MUL_matrix0_dbg
    #endif
#else
    #define MUL_matrix_dbg  MUL_matrix
    #define MUL_matrix0_dbg MUL_matrix0
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

#define MUL_getElement( y, MA, ht, len, m, n ) MULgetElement( y, (MA)[0], ht, len, m, n )
#define MUL_setElement( MA, ht, len, m, n, C ) MULsetElement( (MA)[0], ht, len, m, n, C )
#define MUL_Pelement( MA, ht, len, m, n ) MULPelement( (MA)[0], ht, len, m, n )
                     /* returns a pointer to MA[m][n]. */
#define MUL_element( MA, ht, len, m, n ) (*MULPelement( (MA)[0], ht, len, m, n ))
                     /* dereferenced pointer */

 /****************  Initialization  ***************************************

    To initialize all elements of a matrix with the same value,
    or to perform arithmetic operations on all elements simultaneously,
    refer to the functions of VectorLib, declared in <VULstd.h>, <VULmath.h>.
    In order to use the VectorLib functions, utilize the feature that
    the whole matrix occupies one contiguous area in memory: pass the
    address of the first row to the desired vector function, the size
    of the "vector" being ht * len.
    For example, initialize all elements of the matrix MA with 1.0
    (this is *NOT* the identity matrix)  by calling
        VUL_equ1( (MA)[0], ht * len );
*/

#define MUL_equ0( MA, ht, len )            VUL_equ0( (MA)[0], (ht)*(len) )
#define MUL_equ1( MA, len )                MULequ1( (MA)[0], len ) /* identity matrix */
#define MUL_random( MA, ht, len, seed, Min, Max ) \
                                          VUL_random( (MA)[0], (ht)*(len), seed, Min, Max )
#define MUL_outerprod( MA, X, Y, ht, len ) MULouterprod( (MA)[0], X, Y, ht, len )
                       /* sizX=ht, sizY=len */
#define MUL_Row_equ0( MA, ht, len, iRow )  MULRow_equ0( (MA)[0], ht, len, iRow )
#define MUL_Col_equ0( MA, ht, len, iCol )  MULCol_equ0( (MA)[0], ht, len, iCol )
#define MUL_Dia_equ0( MA, len )            MULDia_equ0( (MA)[0], len )
#define MUL_Row_equC( MA, ht, len, iRow, C ) \
                                        MULRow_equC( (MA)[0], ht, len, iRow, C )
#define MUL_Col_equC( MA, ht, len, iCol, C ) \
                                        MULCol_equC( (MA)[0], ht, len, iCol, C )
#define MUL_Dia_equC( MA, len, C )       MULDia_equC( (MA)[0], len, C )

#define MUL_Row_equV( MA, ht, len, iRow, X ) \
                                        MULRow_equV( (MA)[0], ht, len, iRow, X )
#define MUL_Col_equV( MA, ht, len, iCol, X ) \
                                        MULCol_equV( (MA)[0], ht, len, iCol, X )
#define MUL_Dia_equV( MA, len, X )       MULDia_equV( (MA)[0], len, X )

#define MUL_Trd_equM( MA, MTrd, len )    MULTrd_equM( (MA)[0], (MTrd)[0], len )
#define MUL_Trd_extract( MTrd, MA, len ) MULTrd_extract( (MTrd)[0], (MA)[0], len )

#define MUL_equM( MB, MA, ht, len )  VUL_equV( (MB)[0], (MA)[0], (ht)*(len) )

#define MUL_UequL( MA, len ) MULUequL( (MA)[0], len )
#define MUL_LequU( MA, len ) MULLequU( (MA)[0], len )
         /* copy lower-diagonal elements into upper-diagonal
           (or vice versa) by index-reflection, so as to
           get a symmetric matrix    */

            /* data-type conversions:  */
/************** Data-type interconversions  ****************************/

#define M_LItoUL( MUL, MLI, ht, len ) V_LItoUL( (MUL)[0], (MLI)[0], (ht)*(len) )
#define M_ULtoLI( MLI, MUL, ht, len ) V_ULtoLI( (MLI)[0], (MUL)[0], (ht)*(len) )
#define M_ULtoUB( MUB, MUL, ht, len ) V_ULtoUB( (MUB)[0], (MUL)[0], (ht)*(len) )
#define M_ULtoUS( MUS, MUL, ht, len ) V_ULtoUS( (MUS)[0], (MUL)[0], (ht)*(len) )
#define M_ULtoU(  MU,  MUL, ht, len ) V_ULtoU(  (MU)[0],  (MUL)[0], (ht)*(len) )
#define M_UBtoUL( MUL, MUB, ht, len ) V_UBtoUL( (MUL)[0], (MUB)[0], (ht)*(len) )
#define M_UStoUL( MUL, MUS, ht, len ) V_UStoUL( (MUL)[0], (MUS)[0], (ht)*(len) )
#define M_UtoUL(  MUL, MU,  ht, len ) V_UtoUL(  (MUL)[0], (MU)[0],  (ht)*(len) )
#define M_ULtoF(  MF,  MUL, ht, len ) V_ULtoF(  (MF)[0],  (MUL)[0], (ht)*(len) )
#define M_ULtoD(  MD,  MUL, ht, len ) V_ULtoD(  (MD)[0],  (MUL)[0], (ht)*(len) )
#ifdef _WIN64
	#define M_ULtoUQ( MUQ, MUL, ht, len ) V_ULtoUQ( (MUQ)[0], (MUL)[0], (ht)*(len) )
	#define M_UQtoUL( MUL, MUQ, ht, len ) V_UQtoUL( (MUL)[0], (MUQ)[0], (ht)*(len) )
#endif
#if (defined __BORLANDC__) && !(defined _WIN64)
    #define M_ULtoE( ME, MUL, ht, len ) V_ULtoE( (ME)[0], (MUL)[0], (ht)*(len) )
#else
    #define M_ULtoE M_ULtoD
#endif

/********  Extracting a submatrix and copying a submatrix back  *********/

#define MUL_submatrix( MSub, subHt, subLen, \
                      MSrce, srceHt, srceLen, \
                      firstRowInCol, sampInCol, firstColInRow, sampInRow ) \
               MULsubmatrix(  (MSub)[0], subHt, subLen, \
                             (MSrce)[0], srceHt, srceLen, \
                             firstRowInCol, sampInCol, firstColInRow, sampInRow )

#define MUL_submatrix_equM( MDest, destHt, destLen, \
                           firstRowInCol, sampInCol, firstColInRow, sampInRow, \
                           MSrce, srceHt, srceLen ) \
               MULsubmatrix_equM(  (MDest)[0], destHt, destLen, \
                             firstRowInCol, sampInCol, firstColInRow, sampInRow, \
                             (MSrce)[0], srceHt, srceLen )

#define MUL_equMblock( MSub, subHt, subLen, \
                      MSrce, srceHt, srceLen, \
                      firstRowInCol, firstColInRow ) \
               MULequMblock(  (MSub)[0], subHt, subLen, \
                             (MSrce)[0], srceHt, srceLen, \
                             firstRowInCol, firstColInRow )

#define MUL_block_equM( MDest, destHt, destLen, \
                       firstRowInCol, firstColInRow, \
                       MSrce, srceHt, srceLen ) \
               MULblock_equM( (MDest)[0], destHt, destLen, \
                             firstRowInCol, firstColInRow, \
                             (MSrce)[0], srceHt, srceLen )

#define MUL_equMblockT( MSub, subHt, subLen, \
                      MSrce, srceHt, srceLen, \
                      firstRowInCol, firstColInRow ) \
               MULequMblockT(  (MSub)[0], subHt, subLen, \
                             (MSrce)[0], srceHt, srceLen, \
                             firstRowInCol, firstColInRow )

#define MUL_block_equMT( MDest, destHt, destLen, \
                       firstRowInCol, firstColInRow, \
                       MSrce, srceHt, srceLen ) \
               MULblock_equMT( (MDest)[0], destHt, destLen, \
                             firstRowInCol, firstColInRow, \
                             (MSrce)[0], srceHt, srceLen )

/*****   Extracting a single row or a single column or the diagonal  ******
 *       and storing it into a vector                                     */

#define MUL_Row_extract( Y, MA, ht, len, iRow ) \
                                     MULRow_extract( Y, (MA)[0], ht, len, iRow )
#define MUL_Col_extract( Y, MA, ht, len, iCol ) \
                                     MULCol_extract( Y, (MA)[0], ht, len, iCol )
#define MUL_Dia_extract( Y, MA, len ) MULDia_extract( Y, (MA)[0], len )


/**************  Deleting or inserting a row or a column   ***************/

#define MUL_Row_delete( MB, MA, htA, lenA, iRow ) \
                           MULRow_delete( (MB)[0], (MA)[0], htA, lenA, iRow )
#define MUL_Col_delete( MB, MA, htA, lenA, iCol ) \
                           MULCol_delete( (MB)[0], (MA)[0], htA, lenA, iCol )
#define MUL_Row_insert( MB, MA, htB, lenB, iRow, X ) \
                           MULRow_insert( (MB)[0], (MA)[0], htB, lenB, iRow, X )
#define MUL_Col_insert( MB, MA, htB, lenB, iCol, X ) \
                           MULCol_insert( (MB)[0], (MA)[0], htB, lenB, iCol, X )

/******  One-dimensional vector operations **********************
         performed along all rows or all columns simultaneously,
         or along the diagonal of a square matrix                */

#define MUL_Rows_max( Y, MA, ht, len )     MULRows_max( Y, (MA)[0], ht, len )
#define MUL_Cols_max( Y, MA, ht, len )     MULCols_max( Y, (MA)[0], ht, len )
#define MUL_Dia_max(  MA, len )            MULDia_max(  (MA)[0], len )
#define MUL_Rows_min( Y, MA, ht, len )     MULRows_min( Y, (MA)[0], ht, len )
#define MUL_Cols_min( Y, MA, ht, len )     MULCols_min( Y, (MA)[0], ht, len )
#define MUL_Dia_min(  MA, len )            MULDia_min(  (MA)[0], len )

#define MUL_Rows_rotate( MA, ht, len, pos) MULRows_rotate( (MA)[0], ht, len, pos )
#define MUL_Cols_rotate( MA, ht, len, pos) MULCols_rotate( (MA)[0], ht, len, pos )
#define MUL_Rows_rotate_buf( MA, ht, len, pos, MBuf) MULRows_rotate_buf( (MA)[0], ht, len, pos, (MBuf)[0] )
#define MUL_Cols_rotate_buf( MA, ht, len, pos, MBuf) MULCols_rotate_buf( (MA)[0], ht, len, pos, (MBuf)[0] )
#define MUL_Rows_reflect( MA, ht, len)     MULRows_reflect( (MA)[0], ht, len )
#define MUL_Cols_reflect( MA, ht, len)     MULCols_reflect( (MA)[0], ht, len )
#define MUL_Rows_rev( MA, ht, len)         MULRows_rev( (MA)[0], ht, len )
#define MUL_Cols_rev( MA, ht, len)         MULCols_rev( (MA)[0], ht, len )

#define MUL_Rows_distribution( MAbund, Limits, nBins, MX, htX, lenX, mode ) MULRows_distribution( (MAbund)[0], Limits, nBins, (MX)[0], htX, lenX, mode )
#define MUL_Cols_distribution( MAbund, Limits, nBins, MX, htX, lenX, mode ) MULCols_distribution( (MAbund)[0], Limits, nBins, (MX)[0], htX, lenX, mode )

/********  Operations involving two rows or two colums of one matrix  *****/

#define MUL_Rows_exchange( MA, ht, len, row1, row2 ) \
                             MULRows_exchange( (MA)[0], ht, len, row1, row2 )
#define MUL_Cols_exchange( MA, ht, len, col1, col2 ) \
                             MULCols_exchange( (MA)[0], ht, len, col1, col2 )

/*****************  Transposing and rotating a matrix **********************/

#define MUL_transpose( MTr, MA, htTr, lenTr ) \
             MULtranspose( (MTr)[0], (MA)[0], htTr, lenTr )
       /*  dimensions htTr, lenTr are those of the transposed matrix,
           not of the original!                */
#define MUL_rotate90( MRot, MA, htRot, lenRot ) \
             MULrotate90( (MRot)[0], (MA)[0], htRot, lenRot )
#define MUL_rotate180( MRot, MA, htRot, lenRot ) \
             VUL_rev( (MRot)[0], (MA)[0], (htRot)*(lenRot) )
#define MUL_rotate270( MRot, MA, htRot, lenRot ) \
             MULrotate270( (MRot)[0], (MA)[0], htRot, lenRot )

/**************************  Input and Output  **************************/

#define MUL_write( str, MA, ht, len )   MULwrite( str, (MA)[0], ht, len )
#define MUL_read( MA, ht, len, str )    MULread( (MA)[0], ht, len, str )
#define MUL_setWriteFormat              VUL_setWriteFormat
#define MUL_setWriteSeparate            VUL_setNWriteSeparate
                                   /* write and read in ascii format */
#define MUL_store( str, MA, ht, len )   VUL_store( str, (MA)[0], (len)*(ht) )
#define MUL_recall( MA, ht, len, str)   VUL_recall( (MA)[0], (len)*(ht), str)
                                  /* store and recall in binary format */


/*************************************************************************
 * Here are now the actual declarations of the functions used internally.*
 * These declarations may change in future versions of MatrixLib!        *
 * You should not care too much about them, except in the case you need  *
 * the actual address of a run-time function (see above). Under all      *
 * "normal" circumstances, use only the names defined above in the       *
 * macro section!                                                        *
 *************************************************************************/

void  __vf MULgetElement( unsigned long *y, ulPMatrix X, ui ht, ui len, ui m, ui n );
void  __vf MULsetElement( ulPMatrix X, ui ht, ui len, ui m, ui n, unsigned long C );
unsigned long _VFAR * __vf MULPelement( ulPMatrix X, ui ht, ui len, ui m, ui n );
                  /* pointer is normalized in memory model HUGE */
#define MULelement( MA, ht, len, m, n ) (*MULPelement( MA, ht, len, m, n ))

#define MULequ0( MA, ht, len )            VUL_equ0( MA, (ht)*(len) )
void   __vf  MULequ1( ulPMatrix MA, ui len );  /* identity matrix */
void   __vf  MULouterprod( ulPMatrix MA, ulVector X,  ulVector Y,
                          ui ht, ui len );

void   __vf  MULRow_equ0( ulPMatrix MA, ui ht, ui len,
                         ui iRow );
void   __vf  MULCol_equ0( ulPMatrix MA, ui ht, ui len,
                         ui iCol );
void   __vf  MULDia_equ0( ulPMatrix MA, ui len );

void   __vf  MULRow_equC( ulPMatrix MA, ui ht, ui len,
                         ui iRow, unsigned long C );
void   __vf  MULCol_equC( ulPMatrix MA, ui ht, ui len,
                         ui iCol, unsigned long C );
void   __vf  MULDia_equC( ulPMatrix MA, ui len, unsigned long C );

void   __vf  MULRow_equV( ulPMatrix MA, ui ht, ui len,
                         ui iRow, ulVector X );
void   __vf  MULCol_equV( ulPMatrix MA, ui ht, ui len,
                         ui iCol, ulVector X );
void   __vf  MULDia_equV( ulPMatrix MA, ui len, ulVector X );

void   __vf  MULTrd_equM( ulPMatrix MA, ulPMatrix MTrd, ui len );
void   __vf  MULTrd_extract( ulPMatrix MTrd, ulPMatrix MA, ui len );

#define MULequM( MB, MA, ht, len )  VUL_equV( MB, MA, (ht)*(len) )
void   __vf  MULUequL( ulPMatrix MA, ui len );
void   __vf  MULLequU( ulPMatrix MA, ui len );

/********  Extracting a submatrix and copying a submatrix back  *********/

void  __vf  MULsubmatrix( ulPMatrix MSub,
                          ui subHt,  ui subLen,
                          ulPMatrix MSrce,
                          ui srceHt,  ui srceLen,
                          ui firstRowInCol,  ui sampInCol,
                          ui firstColInRow,  ui sampInRow );

void  __vf  MULsubmatrix_equM( ulPMatrix MDest,
                               ui destHt,     ui destLen,
                               ui firstRowInCol,  ui sampInCol,
                               ui firstColInRow,  ui sampInRow,
                               ulPMatrix MSrce,
                               ui srceHt,     ui srceLen );

void  __vf  MULequMblock(  ulPMatrix MSub,
                          ui subHt,  ui subLen,
                          ulPMatrix MSrce,
                          ui srceHt,  ui srceLen,
                          ui firstRowInCol,  ui firstColInRow );

void  __vf  MULblock_equM( ulPMatrix MDest,
                          ui destHt,     ui destLen,
                          ui firstRowInCol,  ui firstColInRow,
                          ulPMatrix MSrce,
                          ui srceHt,     ui srceLen );

void  __vf  MULequMblockT( ulPMatrix MSub,
                          ui subHt,  ui subLen,
                          ulPMatrix MSrce,
                          ui srceHt,  ui srceLen,
                          ui firstRowInCol,  ui firstColInRow );

void  __vf  MULblock_equMT( ulPMatrix MDest,
                          ui destHt,     ui destLen,
                          ui firstRowInCol,  ui firstColInRow,
                          ulPMatrix MSrce,
                          ui srceHt,     ui srceLen );


/*****   Extracting a single row or a single column or the diagonal  *****
 *       and storing it into a vector                                    */

void __vf MULRow_extract( ulVector Y, ulPMatrix MA, ui ht, ui len,
                           ui iRow );
void __vf MULCol_extract( ulVector Y, ulPMatrix MA, ui ht, ui len,
                           ui iCol );
void __vf MULDia_extract( ulVector Y, ulPMatrix MA, ui len );


/**********  Deleting or inserting a row or a column *****************/

void __vf MULRow_delete( ulPMatrix MB, ulPMatrix MA,
                        ui htA, ui lenA, ui iRow );
void __vf MULCol_delete( ulPMatrix MB, ulPMatrix MA,
                        ui htA, ui lenA, ui iCol );
void __vf MULRow_insert( ulPMatrix MB, ulPMatrix MA, ui htB,
                        ui lenB, ui iRow, ulVector X );
void __vf MULCol_insert( ulPMatrix MB, ulPMatrix MA, ui htB,
                        ui lenB, ui iCol, ulVector X );


/******  One-dimensional vector operations **********************
         performed along all rows or all columns simultaneously,
         or along the diagonal of a square matrix                */

void  __vf  MULRows_max( ulVector Y, ulPMatrix MA, ui ht, ui len );
void  __vf  MULCols_max( ulVector Y, ulPMatrix MA, ui ht, ui len );
unsigned long __vf  MULDia_max(  ulPMatrix MA, ui len );
void  __vf  MULRows_min( ulVector Y, ulPMatrix MA, ui ht, ui len );
void  __vf  MULCols_min( ulVector Y, ulPMatrix MA, ui ht, ui len );
unsigned long __vf  MULDia_min(  ulPMatrix MA, ui len );

void  __vf  MULRows_rotate( ulPMatrix MA, ui ht, ui len, ssize_t pos );
void  __vf  MULCols_rotate( ulPMatrix MA, ui ht, ui len, ssize_t pos );
void  __vf  MULRows_rotate_buf( ulPMatrix MA, ui ht, ui len, ssize_t pos, ulPMatrix MBuf );
void  __vf  MULCols_rotate_buf( ulPMatrix MA, ui ht, ui len, ssize_t pos, ulPMatrix MBuf );
void  __vf  MULRows_reflect( ulPMatrix MA, ui ht, ui len );
void  __vf  MULCols_reflect( ulPMatrix MA, ui ht, ui len );
void  __vf  MULRows_rev( ulPMatrix MA, ui ht, ui len );
void  __vf  MULCols_rev( ulPMatrix MA, ui ht, ui len );

void  __vf  MULRows_distribution( uiPMatrix MAbund, ulVector Limits, ui nBins, ulPMatrix MX, ui ht, ui len, int mode );
void  __vf  MULCols_distribution( uiPMatrix MAbund, ulVector Limits, ui nBins, ulPMatrix MX, ui ht, ui len, int mode );

/********  Operations involving two rows or two colums of one matrix  *****/

void   __vf  MULRows_exchange( ulPMatrix MA, ui ht, ui len,
                              ui i1, ui i2 );
void   __vf  MULCols_exchange( ulPMatrix MA, ui ht, ui len,
                              ui i1, ui i2 );

/*************  Transposing and rotating a matrix **********************/

void  __vf  MULtranspose( ulPMatrix MTr, ulPMatrix MA,
                          ui htTr, ui lenTr );
void  __vf  MULrotate90(  ulPMatrix MRot, ulPMatrix MA, ui htRot, ui lenRot );
#define     MULrotate180( MRot, MA, htRot, lenRot ) \
                VUL_rev( MRot, MA, (htRot)*(lenRot) )
void  __vf  MULrotate270( ulPMatrix MRot, ulPMatrix MA, ui htRot, ui lenRot );

      /*************  Input and Output  ****************/

void  __vf M_ifprint( FILE _VFAR *stream, void _VFAR *X, ui ht, ui len, unsigned linewidth, unsigned vers );
#define MULfprint( stream, MA0, ht, len, linewidth ) \
                    M_ifprint( stream, (void _VFAR *) (MA0), ht, len, linewidth, 7 )
#define MUL_fprint( stream, MA, ht, len, linewidth ) \
                    MULfprint( stream, (MA)[0], ht, len, linewidth )
void  __vf M_icprint( void _VFAR *X, ui ht, ui len, unsigned vers );
#define MULcprint( MA0, ht, len ) M_icprint( (void _VFAR *) (MA0), ht, len, 7 )
#define MUL_cprint( MA, ht, len ) MULcprint( (MA)[0], ht, len )
#define MULprint( MA0, ht, len )  M_ifprint( stdout, (void _VFAR *) (MA0), ht, len, 80, 7 )
#define MUL_print( MA, ht, len )  MULprint( (MA)[0], ht, len )
  /*  MUL_print, MUL_cprint usable only for console applications! */

void __vf MULwrite( FILE _VFAR *stream, ulPMatrix X, ui ht, ui len  );
void __vf MULread( ulPMatrix X, ui ht, ui len, FILE _VFAR *stream );
#define MULstore( str, MA, ht, len ) VUL_store( str, MA, (len)*(ht) )
#define MULrecall( MA, ht, len, str) VUL_recall( MA, (len)*(ht), str)

#ifdef __cplusplus
} // end of extern "C"
#endif
#endif  /*  __MULSTD_H  */
