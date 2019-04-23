/*  MUQstd.h

  matrix management functions:
  manipulations on matrices of data type "uquad"

  Copyright (c) 1996-2017 by OptiCode - Dr. Martin Sander Software Dev.
  All Rights Reserved.
*/

#if defined _WIN64

#if !defined( __MUQSTD_H )
#define __MUQSTD_H
#if !defined( __MATLIB_H )
#include <MatLib.h>
#endif
#if !defined( __VUQSTD_H )
#include <VUQstd.h>
#endif
#if !defined( __VUQMATH_H )
#include <VUQmath.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif

/*************   Dynamic Generation of Matrices   ************************/

uqMatrix __vf  MUQ_matrix(  ui ht, ui len );
uqMatrix __vf  MUQ_matrix0( ui ht, ui len );
#if defined (_MSC_VER) && defined (_DEBUG)
    uqMatrix __vf  MUQ_matrix_dbg(  ui ht, ui len );
    uqMatrix __vf  MUQ_matrix0_dbg( ui ht, ui len );
    #if defined (_INC_CRTDBG) && defined (_CRTDBG_MAP_ALLOC)
	    /* Automatic mapping for memory-leak detection by CRT debugging switched on? */
        #define MUQ_matrix  MUQ_matrix_dbg
        #define MUQ_matrix0 MUQ_matrix0_dbg
    #endif
#else
    #define MUQ_matrix_dbg  MUQ_matrix
    #define MUQ_matrix0_dbg MUQ_matrix0
#endif

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

#define MUQ_getElement( y, MA, ht, len, m, n ) MUQgetElement( y, (MA)[0], ht, len, m, n )
#define MUQ_setElement( MA, ht, len, m, n, C ) MUQsetElement( (MA)[0], ht, len, m, n, C )
#define MUQ_Pelement( MA, ht, len, m, n ) MUQPelement( (MA)[0], ht, len, m, n )
                     /* returns a pointer to MA[m][n]. */
#define MUQ_element( MA, ht, len, m, n ) (*MUQPelement( (MA)[0], ht, len, m, n ))
                     /* dereferenced pointer */

 /****************  Initialization  ***************************************

    To initialize all elements of a matrix with the same value,
    or to perform arithmetic operations on all elements simultaneously,
    refer to the functions of VectorLib, declared in <VUQstd.h>, <VUQmath.h>.
    In order to use the VectorLib functions, utilize the feature that
    the whole matrix occupies one contiguous area in memory: pass the
    address of the first row to the desired vector function, the size
    of the "vector" being ht * len.
    For example, initialize all elements of the matrix MA with 1.0
    (this is *NOT* the identity matrix)  by calling
        VUQ_equ1( (MA)[0], ht * len );
*/

#define MUQ_equ0( MA, ht, len )            VUQ_equ0( (MA)[0], (ht)*(len) )
#define MUQ_equ1( MA, len )                MUQequ1( (MA)[0], len ) /* identity matrix */
#define MUQ_random( MA, ht, len, seed, Min, Max ) \
                                          VUQ_random( (MA)[0], (ht)*(len), seed, Min, Max )
#define MUQ_outerprod( MA, X, Y, ht, len ) MUQouterprod( (MA)[0], X, Y, ht, len )
                       /* sizX=ht, sizY=len */
#define MUQ_Row_equ0( MA, ht, len, iRow )  MUQRow_equ0( (MA)[0], ht, len, iRow )
#define MUQ_Col_equ0( MA, ht, len, iCol )  MUQCol_equ0( (MA)[0], ht, len, iCol )
#define MUQ_Dia_equ0( MA, len )            MUQDia_equ0( (MA)[0], len )
#define MUQ_Row_equC( MA, ht, len, iRow, C ) \
                                        MUQRow_equC( (MA)[0], ht, len, iRow, C )
#define MUQ_Col_equC( MA, ht, len, iCol, C ) \
                                        MUQCol_equC( (MA)[0], ht, len, iCol, C )
#define MUQ_Dia_equC( MA, len, C )       MUQDia_equC( (MA)[0], len, C )

#define MUQ_Row_equV( MA, ht, len, iRow, X ) \
                                        MUQRow_equV( (MA)[0], ht, len, iRow, X )
#define MUQ_Col_equV( MA, ht, len, iCol, X ) \
                                        MUQCol_equV( (MA)[0], ht, len, iCol, X )
#define MUQ_Dia_equV( MA, len, X )       MUQDia_equV( (MA)[0], len, X )

#define MUQ_Trd_equM( MA, MTrd, len )    MUQTrd_equM( (MA)[0], (MTrd)[0], len )
#define MUQ_Trd_extract( MTrd, MA, len ) MUQTrd_extract( (MTrd)[0], (MA)[0], len )

#define MUQ_equM( MB, MA, ht, len )  VUQ_equV( (MB)[0], (MA)[0], (ht)*(len) )

#define MUQ_UequL( MA, len ) MUQUequL( (MA)[0], len )
#define MUQ_LequU( MA, len ) MUQLequU( (MA)[0], len )
         /* copy lower-diagonal elements into upper-diagonal
           (or vice versa) by index-reflection, so as to
           get a symmetric matrix    */

            /* data-type conversions:  */
/************** Data-type interconversions  ****************************/

#define M_QItoUQ( MUQ, MQI, ht, len ) V_QItoUQ( (MUQ)[0], (MQI)[0], (ht)*(len) )
#define M_UQtoQI( MQI, MUQ, ht, len ) V_UQtoqI( (MQI)[0], (MUQ)[0], (ht)*(len) )
#define M_UQtoUB( MUB, MUQ, ht, len ) V_UQtoUB( (MUB)[0], (MUQ)[0], (ht)*(len) )
#define M_UQtoUS( MUS, MUQ, ht, len ) V_UQtoUS( (MUS)[0], (MUQ)[0], (ht)*(len) )
#define M_UQtoU(  MU,  MUQ, ht, len ) V_UQtoU(  (MU)[0],  (MUQ)[0], (ht)*(len) )
#define M_UQtoUL( MUL, MUQ, ht, len ) V_UQtoUL( (MUL)[0], (MUQ)[0], (ht)*(len) )
#define M_UBtoUQ( MUQ, MUB, ht, len ) V_UBtoUQ( (MUQ)[0], (MUB)[0], (ht)*(len) )
#define M_UStoUQ( MUQ, MUS, ht, len ) V_UStoUQ( (MUQ)[0], (MUS)[0], (ht)*(len) )
#define M_UtoUQ(  MUQ, MU,  ht, len ) V_UtoUQ(  (MUQ)[0], (MU)[0],  (ht)*(len) )
#define M_ULtoUQ( MUQ, MUL, ht, len ) V_ULtoUQ( (MUQ)[0], (MUL)[0], (ht)*(len) )
#define M_UQtoF(  MF,  MUQ, ht, len ) V_UQtoF(  (MF)[0],  (MUQ)[0], (ht)*(len) )
#define M_UQtoD(  MD,  MUQ, ht, len ) V_UQtoD(  (MD)[0],  (MUQ)[0], (ht)*(len) )
#if (defined __BORLANDC__) && !(defined _WIN64)
    #define M_UQtoE( ME, MUQ, ht, len ) V_UQtoE( (ME)[0], (MUQ)[0], (ht)*(len) )
#else
    #define M_UQtoE M_UQtoD
#endif

/********  Extracting a submatrix and copying a submatrix back  *********/

#define MUQ_submatrix( MSub, subHt, subLen, \
                      MSrce, srceHt, srceLen, \
                      firstRowInCol, sampInCol, firstColInRow, sampInRow ) \
               MUQsubmatrix(  (MSub)[0], subHt, subLen, \
                             (MSrce)[0], srceHt, srceLen, \
                             firstRowInCol, sampInCol, firstColInRow, sampInRow )

#define MUQ_submatrix_equM( MDest, destHt, destLen, \
                           firstRowInCol, sampInCol, firstColInRow, sampInRow, \
                           MSrce, srceHt, srceLen ) \
               MUQsubmatrix_equM(  (MDest)[0], destHt, destLen, \
                             firstRowInCol, sampInCol, firstColInRow, sampInRow, \
                             (MSrce)[0], srceHt, srceLen )

#define MUQ_equMblock( MSub, subHt, subLen, \
                      MSrce, srceHt, srceLen, \
                      firstRowInCol, firstColInRow ) \
               MUQequMblock(  (MSub)[0], subHt, subLen, \
                             (MSrce)[0], srceHt, srceLen, \
                             firstRowInCol, firstColInRow )

#define MUQ_block_equM( MDest, destHt, destLen, \
                       firstRowInCol, firstColInRow, \
                       MSrce, srceHt, srceLen ) \
               MUQblock_equM( (MDest)[0], destHt, destLen, \
                             firstRowInCol, firstColInRow, \
                             (MSrce)[0], srceHt, srceLen )

#define MUQ_equMblockT( MSub, subHt, subLen, \
                      MSrce, srceHt, srceLen, \
                      firstRowInCol, firstColInRow ) \
               MUQequMblockT(  (MSub)[0], subHt, subLen, \
                             (MSrce)[0], srceHt, srceLen, \
                             firstRowInCol, firstColInRow )

#define MUQ_block_equMT( MDest, destHt, destLen, \
                       firstRowInCol, firstColInRow, \
                       MSrce, srceHt, srceLen ) \
               MUQblock_equMT( (MDest)[0], destHt, destLen, \
                             firstRowInCol, firstColInRow, \
                             (MSrce)[0], srceHt, srceLen )

/*****   Extracting a single row or a single column or the diagonal  ******
 *       and storing it into a vector                                     */

#define MUQ_Row_extract( Y, MA, ht, len, iRow ) \
                                     MUQRow_extract( Y, (MA)[0], ht, len, iRow )
#define MUQ_Col_extract( Y, MA, ht, len, iCol ) \
                                     MUQCol_extract( Y, (MA)[0], ht, len, iCol )
#define MUQ_Dia_extract( Y, MA, len ) MUQDia_extract( Y, (MA)[0], len )


/**************  Deleting or inserting a row or a column   ***************/

#define MUQ_Row_delete( MB, MA, htA, lenA, iRow ) \
                           MUQRow_delete( (MB)[0], (MA)[0], htA, lenA, iRow )
#define MUQ_Col_delete( MB, MA, htA, lenA, iCol ) \
                           MUQCol_delete( (MB)[0], (MA)[0], htA, lenA, iCol )
#define MUQ_Row_insert( MB, MA, htB, lenB, iRow, X ) \
                           MUQRow_insert( (MB)[0], (MA)[0], htB, lenB, iRow, X )
#define MUQ_Col_insert( MB, MA, htB, lenB, iCol, X ) \
                           MUQCol_insert( (MB)[0], (MA)[0], htB, lenB, iCol, X )

/******  One-dimensional vector operations **********************
         performed along all rows or all columns simultaneously,
         or along the diagonal of a square matrix                */

#define MUQ_Rows_max( Y, MA, ht, len )     MUQRows_max( Y, (MA)[0], ht, len )
#define MUQ_Cols_max( Y, MA, ht, len )     MUQCols_max( Y, (MA)[0], ht, len )
#define MUQ_Dia_max(  MA, len )            MUQDia_max(  (MA)[0], len )
#define MUQ_Rows_min( Y, MA, ht, len )     MUQRows_min( Y, (MA)[0], ht, len )
#define MUQ_Cols_min( Y, MA, ht, len )     MUQCols_min( Y, (MA)[0], ht, len )
#define MUQ_Dia_min(  MA, len )            MUQDia_min(  (MA)[0], len )

#define MUQ_Rows_rotate( MA, ht, len, pos) MUQRows_rotate( (MA)[0], ht, len, pos )
#define MUQ_Cols_rotate( MA, ht, len, pos) MUQCols_rotate( (MA)[0], ht, len, pos )
#define MUQ_Rows_rotate_buf( MA, ht, len, pos, MBuf) MUQRows_rotate_buf( (MA)[0], ht, len, pos, (MBuf)[0] )
#define MUQ_Cols_rotate_buf( MA, ht, len, pos, MBuf) MUQCols_rotate_buf( (MA)[0], ht, len, pos, (MBuf)[0] )
#define MUQ_Rows_reflect( MA, ht, len)     MUQRows_reflect( (MA)[0], ht, len )
#define MUQ_Cols_reflect( MA, ht, len)     MUQCols_reflect( (MA)[0], ht, len )
#define MUQ_Rows_rev( MA, ht, len)         MUQRows_rev( (MA)[0], ht, len )
#define MUQ_Cols_rev( MA, ht, len)         MUQCols_rev( (MA)[0], ht, len )

#define MUQ_Rows_distribution( MAbund, Limits, nBins, MX, htX, lenX, mode ) MUQRows_distribution( (MAbund)[0], Limits, nBins, (MX)[0], htX, lenX, mode )
#define MUQ_Cols_distribution( MAbund, Limits, nBins, MX, htX, lenX, mode ) MUQCols_distribution( (MAbund)[0], Limits, nBins, (MX)[0], htX, lenX, mode )

/********  Operations involving two rows or two colums of one matrix  *****/

#define MUQ_Rows_exchange( MA, ht, len, row1, row2 ) \
                             MUQRows_exchange( (MA)[0], ht, len, row1, row2 )
#define MUQ_Cols_exchange( MA, ht, len, col1, col2 ) \
                             MUQCols_exchange( (MA)[0], ht, len, col1, col2 )

/*****************  Transposing and rotating a matrix **********************/

#define MUQ_transpose( MTr, MA, htTr, lenTr ) \
             MUQtranspose( (MTr)[0], (MA)[0], htTr, lenTr )
       /*  dimensions htTr, lenTr are those of the transposed matrix,
           not of the original!                */
#define MUQ_rotate90( MRot, MA, htRot, lenRot ) \
             MUQrotate90( (MRot)[0], (MA)[0], htRot, lenRot )
#define MUQ_rotate180( MRot, MA, htRot, lenRot ) \
             VUQ_rev( (MRot)[0], (MA)[0], (htRot)*(lenRot) )
#define MUQ_rotate270( MRot, MA, htRot, lenRot ) \
             MUQrotate270( (MRot)[0], (MA)[0], htRot, lenRot )

/**************************  Input and Output  **************************/

void  __vf M_ifprint( FILE _VFAR *stream, void _VFAR *X, ui ht, ui len, unsigned linewidth, unsigned vers );
#define MUQ_fprint( stream, MA, ht, len, linewidth ) \
                    MUQfprint( stream, (MA)[0], ht, len, linewidth )
#define MUQ_print( MA, ht, len )  MUQfprint( stdout, (MA)[0], ht, len, 80 )
#define MUQ_cprint( MA, ht, len ) MUQcprint( (MA)[0], ht, len )
  /*  MUQ_print, MUQ_cprint usable only for console applications! */
#define MUQ_write( str, MA, ht, len )   MUQwrite( str, (MA)[0], ht, len )
#define MUQ_read( MA, ht, len, str )    MUQread( (MA)[0], ht, len, str )
#define MUQ_setWriteFormat              VUQ_setWriteFormat
#define MUQ_setWriteSeparate            VUQ_setNWriteSeparate
                                   /* write and read in ascii format */
#define MUQ_store( str, MA, ht, len )   VUQ_store( str, (MA)[0], (len)*(ht) )
#define MUQ_recall( MA, ht, len, str)   VUQ_recall( (MA)[0], (len)*(ht), str)
                                  /* store and recall in binary format */


/*************************************************************************
 * Here are now the actual declarations of the functions used internally.*
 * These declarations may change in future versions of MatrixLib!        *
 * You should not care too much about them, except in the case you need  *
 * the actual address of a run-time function (see above). Under all      *
 * "normal" circumstances, use only the names defined above in the       *
 * macro section!                                                        *
 *************************************************************************/

void  __vf MUQgetElement( uquad *y, uqPMatrix X, ui ht, ui len, ui m, ui n );
void  __vf MUQsetElement( uqPMatrix X, ui ht, ui len, ui m, ui n, uquad C );
uquad _VFAR * __vf MUQPelement( uqPMatrix X, ui ht, ui len, ui m, ui n );
                  /* pointer is normalized in memory model HUGE */
#define MUQelement( MA, ht, len, m, n ) (*MUQPelement( MA, ht, len, m, n ))

#define MUQequ0( MA, ht, len )            VUQ_equ0( MA, (ht)*(len) )
void   __vf  MUQequ1( uqPMatrix MA, ui len );  /* identity matrix */
void   __vf  MUQouterprod( uqPMatrix MA, uqVector X,  uqVector Y,
                          ui ht, ui len );

void   __vf  MUQRow_equ0( uqPMatrix MA, ui ht, ui len,
                         ui iRow );
void   __vf  MUQCol_equ0( uqPMatrix MA, ui ht, ui len,
                         ui iCol );
void   __vf  MUQDia_equ0( uqPMatrix MA, ui len );

void   __vf  MUQRow_equC( uqPMatrix MA, ui ht, ui len,
                         ui iRow, uquad C );
void   __vf  MUQCol_equC( uqPMatrix MA, ui ht, ui len,
                         ui iCol, uquad C );
void   __vf  MUQDia_equC( uqPMatrix MA, ui len, uquad C );

void   __vf  MUQRow_equV( uqPMatrix MA, ui ht, ui len,
                         ui iRow, uqVector X );
void   __vf  MUQCol_equV( uqPMatrix MA, ui ht, ui len,
                         ui iCol, uqVector X );
void   __vf  MUQDia_equV( uqPMatrix MA, ui len, uqVector X );

void   __vf  MUQTrd_equM( uqPMatrix MA, uqPMatrix MTrd, ui len );
void   __vf  MUQTrd_extract( uqPMatrix MTrd, uqPMatrix MA, ui len );

#define MUQequM( MB, MA, ht, len )  VUQ_equV( MB, MA, (ht)*(len) )
void   __vf  MUQUequL( uqPMatrix MA, ui len );
void   __vf  MUQLequU( uqPMatrix MA, ui len );

/********  Extracting a submatrix and copying a submatrix back  *********/

void  __vf  MUQsubmatrix( uqPMatrix MSub,
                          ui subHt,  ui subLen,
                          uqPMatrix MSrce,
                          ui srceHt,  ui srceLen,
                          ui firstRowInCol,  ui sampInCol,
                          ui firstColInRow,  ui sampInRow );

void  __vf  MUQsubmatrix_equM( uqPMatrix MDest,
                               ui destHt,     ui destLen,
                               ui firstRowInCol,  ui sampInCol,
                               ui firstColInRow,  ui sampInRow,
                               uqPMatrix MSrce,
                               ui srceHt,     ui srceLen );

void  __vf  MUQequMblock(  uqPMatrix MSub,
                          ui subHt,  ui subLen,
                          uqPMatrix MSrce,
                          ui srceHt,  ui srceLen,
                          ui firstRowInCol,  ui firstColInRow );

void  __vf  MUQblock_equM( uqPMatrix MDest,
                          ui destHt,     ui destLen,
                          ui firstRowInCol,  ui firstColInRow,
                          uqPMatrix MSrce,
                          ui srceHt,     ui srceLen );

void  __vf  MUQequMblockT( uqPMatrix MSub,
                          ui subHt,  ui subLen,
                          uqPMatrix MSrce,
                          ui srceHt,  ui srceLen,
                          ui firstRowInCol,  ui firstColInRow );

void  __vf  MUQblock_equMT( uqPMatrix MDest,
                          ui destHt,     ui destLen,
                          ui firstRowInCol,  ui firstColInRow,
                          uqPMatrix MSrce,
                          ui srceHt,     ui srceLen );


/*****   Extracting a single row or a single column or the diagonal  *****
 *       and storing it into a vector                                    */

void __vf MUQRow_extract( uqVector Y, uqPMatrix MA, ui ht, ui len,
                           ui iRow );
void __vf MUQCol_extract( uqVector Y, uqPMatrix MA, ui ht, ui len,
                           ui iCol );
void __vf MUQDia_extract( uqVector Y, uqPMatrix MA, ui len );


/**********  Deleting or inserting a row or a column *****************/

void __vf MUQRow_delete( uqPMatrix MB, uqPMatrix MA,
                        ui htA, ui lenA, ui iRow );
void __vf MUQCol_delete( uqPMatrix MB, uqPMatrix MA,
                        ui htA, ui lenA, ui iCol );
void __vf MUQRow_insert( uqPMatrix MB, uqPMatrix MA, ui htB,
                        ui lenB, ui iRow, uqVector X );
void __vf MUQCol_insert( uqPMatrix MB, uqPMatrix MA, ui htB,
                        ui lenB, ui iCol, uqVector X );


/******  One-dimensional vector operations **********************
         performed along all rows or all columns simultaneously,
         or along the diagonal of a square matrix                */

void  __vf  MUQRows_max( uqVector Y, uqPMatrix MA, ui ht, ui len );
void  __vf  MUQCols_max( uqVector Y, uqPMatrix MA, ui ht, ui len );
uquad __vf  MUQDia_max(  uqPMatrix MA, ui len );
void  __vf  MUQRows_min( uqVector Y, uqPMatrix MA, ui ht, ui len );
void  __vf  MUQCols_min( uqVector Y, uqPMatrix MA, ui ht, ui len );
uquad __vf  MUQDia_min(  uqPMatrix MA, ui len );

void  __vf  MUQRows_rotate( uqPMatrix MA, ui ht, ui len, ssize_t pos );
void  __vf  MUQCols_rotate( uqPMatrix MA, ui ht, ui len, ssize_t pos );
void  __vf  MUQRows_rotate_buf( uqPMatrix MA, ui ht, ui len, ssize_t pos, uqPMatrix MBuf );
void  __vf  MUQCols_rotate_buf( uqPMatrix MA, ui ht, ui len, ssize_t pos, uqPMatrix MBuf );
void  __vf  MUQRows_reflect( uqPMatrix MA, ui ht, ui len );
void  __vf  MUQCols_reflect( uqPMatrix MA, ui ht, ui len );
void  __vf  MUQRows_rev( uqPMatrix MA, ui ht, ui len );
void  __vf  MUQCols_rev( uqPMatrix MA, ui ht, ui len );

void  __vf  MUQRows_distribution( uiPMatrix MAbund, uqVector Limits, ui nBins, uqPMatrix MX, ui ht, ui len, int mode );
void  __vf  MUQCols_distribution( uiPMatrix MAbund, uqVector Limits, ui nBins, uqPMatrix MX, ui ht, ui len, int mode );

/********  Operations involving two rows or two colums of one matrix  *****/

void   __vf  MUQRows_exchange( uqPMatrix MA, ui ht, ui len,
                              ui i1, ui i2 );
void   __vf  MUQCols_exchange( uqPMatrix MA, ui ht, ui len,
                              ui i1, ui i2 );

/*************  Transposing and rotating a matrix **********************/

void  __vf  MUQtranspose( uqPMatrix MTr, uqPMatrix MA,
                          ui htTr, ui lenTr );
void  __vf  MUQrotate90(  uqPMatrix MRot, uqPMatrix MA, ui htRot, ui lenRot );
#define     MUQrotate180( MRot, MA, htRot, lenRot ) \
                VUQ_rev( MRot, MA, (htRot)*(lenRot) )
void  __vf  MUQrotate270( uqPMatrix MRot, uqPMatrix MA, ui htRot, ui lenRot );

      /*************  Input and Output  ****************/

#define MUQfprint( stream, MA0, ht, len, linewidth ) \
                    M_ifprint( stream, (void _VFAR *) (MA0), ht, len, linewidth, 9 )
#define MUQcprint( MA0, ht, len ) \
	                M_icprint( (void _VFAR *) (MA0), ht, len, 9 )

void __vf MUQwrite( FILE _VFAR *stream, uqPMatrix X, ui ht, ui len  );
void __vf MUQread( uqPMatrix X, ui ht, ui len, FILE _VFAR *stream );
#define MUQstore( str, MA, ht, len ) VUQ_store( str, MA, (len)*(ht) )
#define MUQrecall( MA, ht, len, str) VUQ_recall( MA, (len)*(ht), str)

#ifdef __cplusplus
} // end of extern "C"
#endif
#endif  /*  __MUQSTD_H  */
#endif  /*  _WIN64  */