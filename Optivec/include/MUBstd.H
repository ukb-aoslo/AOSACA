/*  MUBstd.h

  matrix management functions:
  manipulations on matrices of data type "unsigned char"

  Copyright (c) 1996-2017 by OptiCode - Dr. Martin Sander Software Dev.
  All Rights Reserved.
*/

#if !defined( __MUBSTD_H )
#define __MUBSTD_H
#if !defined( __MATLIB_H )
#include <MatLib.h>
#endif
#if !defined( __VUBSTD_H )
#include <VUBstd.h>
#endif
#if !defined( __VUBMATH_H )
#include <VUBmath.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif

/*************   Dynamic Generation of Matrices   ************************/

ubMatrix __vf  MUB_matrix(  ui ht, ui len );
ubMatrix __vf  MUB_matrix0( ui ht, ui len );
#if defined (_MSC_VER) && defined (_DEBUG)
    ubMatrix __vf  MUB_matrix_dbg(  ui ht, ui len );
    ubMatrix __vf  MUB_matrix0_dbg( ui ht, ui len );
    #if defined (_INC_CRTDBG) && defined (_CRTDBG_MAP_ALLOC) 
	    /* Automatic mapping for memory-leak detection by CRT debugging switched on? */
        #define MUB_matrix  MUB_matrix_dbg
        #define MUB_matrix0 MUB_matrix0_dbg
    #endif
#else
    #define MUB_matrix_dbg  MUB_matrix
    #define MUB_matrix0_dbg MUB_matrix0
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

#define MUB_getElement( y, MA, ht, len, m, n ) MUBgetElement( y, (MA)[0], ht, len, m, n )
#define MUB_setElement( MA, ht, len, m, n, C ) MUBsetElement( (MA)[0], ht, len, m, n, C )
#define MUB_Pelement( MA, ht, len, m, n ) MUBPelement( (MA)[0], ht, len, m, n )
                     /* returns a pointer to MA[m][n]. */
#define MUB_element( MA, ht, len, m, n ) (*MUBPelement( (MA)[0], ht, len, m, n ))
                     /* dereferenced pointer */

 /****************  Initialization  ***************************************

    To initialize all elements of a matrix with the same value,
    or to perform arithmetic operations on all elements simultaneously,
    refer to the functions of VectorLib, declared in <VUBstd.h>, <VUBmath.h>.
    In order to use the VectorLib functions, utilize the feature that
    the whole matrix occupies one contiguous area in memory: pass the
    address of the first row to the desired vector function, the size
    of the "vector" being ht * len.
    For example, initialize all elements of the matrix MA with 1
    (this is *NOT* the identity matrix)  by calling
        VUB_equ1( (MA)[0], ht * len );
*/

#define MUB_equ0( MA, ht, len )            VUB_equ0( (MA)[0], (ht)*(len) )
#define MUB_equ1( MA, len )                MUBequ1( (MA)[0], len ) /* identity matrix */
#define MUB_random( MA, ht, len, seed, Min, Max ) \
                                          VUB_random( (MA)[0], (ht)*(len), seed, Min, Max )
#define MUB_outerprod( MA, X, Y, ht, len ) MUBouterprod( (MA)[0], X, Y, ht, len )
                       /* sizX=ht, sizY=len */
#define MUB_Row_equ0( MA, ht, len, iRow )  MUBRow_equ0( (MA)[0], ht, len, iRow )
#define MUB_Col_equ0( MA, ht, len, iCol )  MUBCol_equ0( (MA)[0], ht, len, iCol )
#define MUB_Dia_equ0( MA, len )            MUBDia_equ0( (MA)[0], len )
#define MUB_Row_equC( MA, ht, len, iRow, C ) \
                                        MUBRow_equC( (MA)[0], ht, len, iRow, C )
#define MUB_Col_equC( MA, ht, len, iCol, C ) \
                                        MUBCol_equC( (MA)[0], ht, len, iCol, C )
#define MUB_Dia_equC( MA, len, C )       MUBDia_equC( (MA)[0], len, C )

#define MUB_Row_equV( MA, ht, len, iRow, X ) \
                                        MUBRow_equV( (MA)[0], ht, len, iRow, X )
#define MUB_Col_equV( MA, ht, len, iCol, X ) \
                                        MUBCol_equV( (MA)[0], ht, len, iCol, X )
#define MUB_Dia_equV( MA, len, X )       MUBDia_equV( (MA)[0], len, X )

#define MUB_Trd_equM( MA, MTrd, len )    MUBTrd_equM( (MA)[0], (MTrd)[0], len )
#define MUB_Trd_extract( MTrd, MA, len ) MUBTrd_extract( (MTrd)[0], (MA)[0], len )

#define MUB_equM( MB, MA, ht, len )  VUB_equV( (MB)[0], (MA)[0], (ht)*(len) )

#define MUB_UequL( MA, len ) MUBUequL( (MA)[0], len )
#define MUB_LequU( MA, len ) MUBLequU( (MA)[0], len )
         /* copy lower-diagonal elements into upper-diagonal
           (or vice versa) by index-reflection, so as to
           get a symmetric matrix    */

            /* data-type conversions:  */
/************** Data-type interconversions  ****************************/

#define M_BItoUB( MUB, MBI, ht, len ) V_BItoUB( (MUB)[0], (MBI)[0], (ht)*(len) )
#define M_UBtoBI( MBI, MUB, ht, len ) V_UBtoBI( (MBI)[0], (MUB)[0], (ht)*(len) )
#define M_UBtoU(  MU,  MUB, ht, len ) V_UBtoU(  (MU)[0],  (MUB)[0], (ht)*(len) )
#define M_UBtoUS( MUS, MUB, ht, len ) V_UBtoUS( (MUS)[0], (MUB)[0], (ht)*(len) )
#define M_UBtoUL( MUL, MUB, ht, len ) V_UBtoUL( (MUL)[0], (MUB)[0], (ht)*(len) )
#define M_UStoUB( MUB, MUS, ht, len ) V_UStoUB( (MUB)[0], (MUS)[0], (ht)*(len) )
#define M_UtoUB(  MUB, MU,  ht, len ) V_UtoUB(  (MUB)[0], (MU)[0],  (ht)*(len) )
#define M_ULtoUB( MUB, MUL, ht, len ) V_ULtoUB( (MUB)[0], (MUL)[0], (ht)*(len) )
#define M_UBtoF(  MF,  MUB, ht, len ) V_UBtoF(  (MF)[0],  (MUB)[0], (ht)*(len) )
#define M_UBtoD(  MD,  MUB, ht, len ) V_UBtoD(  (MD)[0],  (MUB)[0], (ht)*(len) )
#ifdef _WIN64
	#define M_UBtoUQ( MUQ, MUB, ht, len ) V_UBtoUQ( (MUQ)[0], (MUB)[0], (ht)*(len) )
	#define M_UQtoUB( MUB, MUQ, ht, len ) V_UQtoUB( (MUB)[0], (MUQ)[0], (ht)*(len) )
#endif
#if (defined __BORLANDC__) && !(defined _WIN64)
    #define M_UBtoE( ME, MUB, ht, len ) V_UBtoE( (ME)[0], (MUB)[0], (ht)*(len) )
#else
    #define M_UBtoE M_UBtoD
#endif

/********  Extracting a submatrix and copying a submatrix back  *********/

#define MUB_submatrix( MSub, subHt, subLen, \
                      MSrce, srceHt, srceLen, \
                      firstRowInCol, sampInCol, firstColInRow, sampInRow ) \
               MUBsubmatrix(  (MSub)[0], subHt, subLen, \
                             (MSrce)[0], srceHt, srceLen, \
                             firstRowInCol, sampInCol, firstColInRow, sampInRow )

#define MUB_submatrix_equM( MDest, destHt, destLen, \
                           firstRowInCol, sampInCol, firstColInRow, sampInRow, \
                           MSrce, srceHt, srceLen ) \
               MUBsubmatrix_equM(  (MDest)[0], destHt, destLen, \
                             firstRowInCol, sampInCol, firstColInRow, sampInRow, \
                             (MSrce)[0], srceHt, srceLen )

#define MUB_equMblock( MSub, subHt, subLen, \
                      MSrce, srceHt, srceLen, \
                      firstRowInCol, firstColInRow ) \
               MUBequMblock(  (MSub)[0], subHt, subLen, \
                             (MSrce)[0], srceHt, srceLen, \
                             firstRowInCol, firstColInRow )

#define MUB_block_equM( MDest, destHt, destLen, \
                       firstRowInCol, firstColInRow, \
                       MSrce, srceHt, srceLen ) \
               MUBblock_equM( (MDest)[0], destHt, destLen, \
                             firstRowInCol, firstColInRow, \
                             (MSrce)[0], srceHt, srceLen )

#define MUB_equMblockT( MSub, subHt, subLen, \
                      MSrce, srceHt, srceLen, \
                      firstRowInCol, firstColInRow ) \
               MUBequMblockT(  (MSub)[0], subHt, subLen, \
                             (MSrce)[0], srceHt, srceLen, \
                             firstRowInCol, firstColInRow )

#define MUB_block_equMT( MDest, destHt, destLen, \
                       firstRowInCol, firstColInRow, \
                       MSrce, srceHt, srceLen ) \
               MUBblock_equMT( (MDest)[0], destHt, destLen, \
                             firstRowInCol, firstColInRow, \
                             (MSrce)[0], srceHt, srceLen )

/*****   Extracting a single row or a single column or the diagonal  ******
 *       and storing it into a vector                                     */

#define MUB_Row_extract( Y, MA, ht, len, iRow ) \
                                     MUBRow_extract( Y, (MA)[0], ht, len, iRow )
#define MUB_Col_extract( Y, MA, ht, len, iCol ) \
                                     MUBCol_extract( Y, (MA)[0], ht, len, iCol )
#define MUB_Dia_extract( Y, MA, len ) MUBDia_extract( Y, (MA)[0], len )


/**************  Deleting or inserting a row or a column   ***************/

#define MUB_Row_delete( MB, MA, htA, lenA, iRow ) \
                           MUBRow_delete( (MB)[0], (MA)[0], htA, lenA, iRow )
#define MUB_Col_delete( MB, MA, htA, lenA, iCol ) \
                           MUBCol_delete( (MB)[0], (MA)[0], htA, lenA, iCol )
#define MUB_Row_insert( MB, MA, htB, lenB, iRow, X ) \
                           MUBRow_insert( (MB)[0], (MA)[0], htB, lenB, iRow, X )
#define MUB_Col_insert( MB, MA, htB, lenB, iCol, X ) \
                           MUBCol_insert( (MB)[0], (MA)[0], htB, lenB, iCol, X )

/******  One-dimensional vector operations **********************
         performed along all rows or all columns simultaneously,
         or along the diagonal of a square matrix                */

#define MUB_Rows_max( Y, MA, ht, len )     MUBRows_max( Y, (MA)[0], ht, len )
#define MUB_Cols_max( Y, MA, ht, len )     MUBCols_max( Y, (MA)[0], ht, len )
#define MUB_Dia_max(  MA, len )            MUBDia_max(  (MA)[0], len )
#define MUB_Rows_min( Y, MA, ht, len )     MUBRows_min( Y, (MA)[0], ht, len )
#define MUB_Cols_min( Y, MA, ht, len )     MUBCols_min( Y, (MA)[0], ht, len )
#define MUB_Dia_min(  MA, len )            MUBDia_min(  (MA)[0], len )

#define MUB_Rows_rotate( MA, ht, len, pos) MUBRows_rotate( (MA)[0], ht, len, pos )
#define MUB_Cols_rotate( MA, ht, len, pos) MUBCols_rotate( (MA)[0], ht, len, pos )
#define MUB_Rows_rotate_buf( MA, ht, len, pos, MBuf) MUBRows_rotate_buf( (MA)[0], ht, len, pos, (MBuf)[0] )
#define MUB_Cols_rotate_buf( MA, ht, len, pos, MBuf) MUBCols_rotate_buf( (MA)[0], ht, len, pos, (MBuf)[0] )
#define MUB_Rows_reflect( MA, ht, len)     MUBRows_reflect( (MA)[0], ht, len )
#define MUB_Cols_reflect( MA, ht, len)     MUBCols_reflect( (MA)[0], ht, len )
#define MUB_Rows_rev( MA, ht, len)         MUBRows_rev( (MA)[0], ht, len )
#define MUB_Cols_rev( MA, ht, len)         MUBCols_rev( (MA)[0], ht, len )

#define MUB_Rows_distribution( MAbund, Limits, nBins, MX, htX, lenX, mode ) MUBRows_distribution( (MAbund)[0], Limits, nBins, (MX)[0], htX, lenX, mode )
#define MUB_Cols_distribution( MAbund, Limits, nBins, MX, htX, lenX, mode ) MUBCols_distribution( (MAbund)[0], Limits, nBins, (MX)[0], htX, lenX, mode )

/********  Operations involving two rows or two colums of one matrix  *****/

#define MUB_Rows_exchange( MA, ht, len, row1, row2 ) \
                             MUBRows_exchange( (MA)[0], ht, len, row1, row2 )
#define MUB_Cols_exchange( MA, ht, len, col1, col2 ) \
                             MUBCols_exchange( (MA)[0], ht, len, col1, col2 )

/****************  Transposing and rotating a matrix **********************/

#define MUB_transpose( MTr, MA, htTr, lenTr ) \
             MUBtranspose( (MTr)[0], (MA)[0], htTr, lenTr )
       /*  dimensions htTr, lenTr are those of the transposed matrix,
           not of the original!                */
#define MUB_rotate90( MRot, MA, htRot, lenRot ) \
             MUBrotate90( (MRot)[0], (MA)[0], htRot, lenRot )
#define MUB_rotate180( MRot, MA, htRot, lenRot ) \
             VUB_rev( (MRot)[0], (MA)[0], (htRot)*(lenRot) )
#define MUB_rotate270( MRot, MA, htRot, lenRot ) \
             MUBrotate270( (MRot)[0], (MA)[0], htRot, lenRot )


/**************************  Input and Output  **************************/

#define MUB_write( str, MA, ht, len )   MUBwrite( str, (MA)[0], ht, len )
#define MUB_read( MA, ht, len, str )    MUBread( (MA)[0], ht, len, str )
#define MUB_setWriteFormat              VUB_setWriteFormat
#define MUB_setWriteSeparate            VUB_setNWriteSeparate
                                   /* write and read in ascii format */
#define MUB_store( str, MA, ht, len )   VUB_store( str, (MA)[0], (len)*(ht) )
#define MUB_recall( MA, ht, len, str)   VUB_recall( (MA)[0], (len)*(ht), str)
                                  /* store and recall in binary format */


/*************************************************************************
 * Here are now the actual declarations of the functions used internally.*
 * These declarations may change in future versions of MatrixLib!        *
 * You should not care too much about them, except in the case you need  *
 * the actual address of a run-time function (see above). Under all      *
 * "normal" circumstances, use only the names defined above in the       *
 * macro section!                                                        *
 *************************************************************************/

void  __vf MUBgetElement( unsigned char *y, ubPMatrix X, ui ht, ui len, ui m, ui n );
void  __vf MUBsetElement( ubPMatrix X, ui ht, ui len, ui m, ui n, unsigned char C );
unsigned char _VFAR * __vf MUBPelement( ubPMatrix X, ui ht, ui len, ui m, ui n );
                  /* pointer is normalized in memory model HUGE */
#define MUBelement( MA, ht, len, m, n ) (*MUBPelement( MA, ht, len, m, n ))

#define MUBequ0( MA, ht, len )            VUB_equ0( MA, (ht)*(len) )
void   __vf  MUBequ1( ubPMatrix MA, ui len );  /* identity matrix */
void   __vf  MUBouterprod( ubPMatrix MA, ubVector X,  ubVector Y,
                          ui ht, ui len );

void   __vf  MUBRow_equ0( ubPMatrix MA, ui ht, ui len,
                         ui iRow );
void   __vf  MUBCol_equ0( ubPMatrix MA, ui ht, ui len,
                         ui iCol );
void   __vf  MUBDia_equ0( ubPMatrix MA, ui len );

void   __vf  MUBRow_equC( ubPMatrix MA, ui ht, ui len,
                         ui iRow, unsigned char C );
void   __vf  MUBCol_equC( ubPMatrix MA, ui ht, ui len,
                         ui iCol, unsigned char C );
void   __vf  MUBDia_equC( ubPMatrix MA, ui len, unsigned char C );

void   __vf  MUBRow_equV( ubPMatrix MA, ui ht, ui len,
                         ui iRow, ubVector X );
void   __vf  MUBCol_equV( ubPMatrix MA, ui ht, ui len,
                         ui iCol, ubVector X );
void   __vf  MUBDia_equV( ubPMatrix MA, ui len, ubVector X );

void   __vf  MUBTrd_equM( ubPMatrix MA, ubPMatrix MTrd, ui len );
void   __vf  MUBTrd_extract( ubPMatrix MTrd, ubPMatrix MA, ui len );

#define MUBequM( MB, MA, ht, len )  VUB_equV( MB, MA, (ht)*(len) )
void   __vf  MUBUequL( ubPMatrix MA, ui len );
void   __vf  MUBLequU( ubPMatrix MA, ui len );

/********  Extracting a submatrix and copying a submatrix back  *********/

void  __vf  MUBsubmatrix( ubPMatrix MSub,
                          ui subHt,  ui subLen,
                          ubPMatrix MSrce,
                          ui srceHt,  ui srceLen,
                          ui firstRowInCol,  ui sampInCol,
                          ui firstColInRow,  ui sampInRow );

void  __vf  MUBsubmatrix_equM( ubPMatrix MDest,
                               ui destHt,     ui destLen,
                               ui firstRowInCol,  ui sampInCol,
                               ui firstColInRow,  ui sampInRow,
                               ubPMatrix MSrce,
                               ui srceHt,     ui srceLen );

void  __vf  MUBequMblock(  ubPMatrix MSub,
                          ui subHt,  ui subLen,
                          ubPMatrix MSrce,
                          ui srceHt,  ui srceLen,
                          ui firstRowInCol,  ui firstColInRow );

void  __vf  MUBblock_equM( ubPMatrix MDest,
                          ui destHt,     ui destLen,
                          ui firstRowInCol,  ui firstColInRow,
                          ubPMatrix MSrce,
                          ui srceHt,     ui srceLen );

void  __vf  MUBequMblockT( ubPMatrix MSub,
                          ui subHt,  ui subLen,
                          ubPMatrix MSrce,
                          ui srceHt,  ui srceLen,
                          ui firstRowInCol,  ui firstColInRow );

void  __vf  MUBblock_equMT( ubPMatrix MDest,
                          ui destHt,     ui destLen,
                          ui firstRowInCol,  ui firstColInRow,
                          ubPMatrix MSrce,
                          ui srceHt,     ui srceLen );


/*****   Extracting a single row or a single column or the diagonal  *****
 *       and storing it into a vector                                    */

void __vf MUBRow_extract( ubVector Y, ubPMatrix MA, ui ht, ui len,
                           ui iRow );
void __vf MUBCol_extract( ubVector Y, ubPMatrix MA, ui ht, ui len,
                           ui iCol );
void __vf MUBDia_extract( ubVector Y, ubPMatrix MA, ui len );


/**********  Deleting or inserting a row or a column *****************/

void __vf MUBRow_delete( ubPMatrix MB, ubPMatrix MA,
                        ui htA, ui lenA, ui iRow );
void __vf MUBCol_delete( ubPMatrix MB, ubPMatrix MA,
                        ui htA, ui lenA, ui iCol );
void __vf MUBRow_insert( ubPMatrix MB, ubPMatrix MA, ui htB,
                        ui lenB, ui iRow, ubVector X );
void __vf MUBCol_insert( ubPMatrix MB, ubPMatrix MA, ui htB,
                        ui lenB, ui iCol, ubVector X );


/******  One-dimensional vector operations **********************
         performed along all rows or all columns simultaneously,
         or along the diagonal of a square matrix                */

void  __vf  MUBRows_max( ubVector Y, ubPMatrix MA, ui ht, ui len );
void  __vf  MUBCols_max( ubVector Y, ubPMatrix MA, ui ht, ui len );
unsigned char __vf  MUBDia_max(  ubPMatrix MA, ui len );
void  __vf  MUBRows_min( ubVector Y, ubPMatrix MA, ui ht, ui len );
void  __vf  MUBCols_min( ubVector Y, ubPMatrix MA, ui ht, ui len );
unsigned char __vf  MUBDia_min(  ubPMatrix MA, ui len );

void  __vf  MUBRows_rotate( ubPMatrix MA, ui ht, ui len, ssize_t pos );
void  __vf  MUBCols_rotate( ubPMatrix MA, ui ht, ui len, ssize_t pos );
void  __vf  MUBRows_rotate_buf( ubPMatrix MA, ui ht, ui len, ssize_t pos, ubPMatrix MBuf );
void  __vf  MUBCols_rotate_buf( ubPMatrix MA, ui ht, ui len, ssize_t pos, ubPMatrix MBuf );
void  __vf  MUBRows_reflect( ubPMatrix MA, ui ht, ui len );
void  __vf  MUBCols_reflect( ubPMatrix MA, ui ht, ui len );
void  __vf  MUBRows_rev( ubPMatrix MA, ui ht, ui len );
void  __vf  MUBCols_rev( ubPMatrix MA, ui ht, ui len );

void  __vf  MUBRows_distribution( uiPMatrix MAbund, ubVector Limits, ui nBins, ubPMatrix MX, ui ht, ui len, int mode );
void  __vf  MUBCols_distribution( uiPMatrix MAbund, ubVector Limits, ui nBins, ubPMatrix MX, ui ht, ui len, int mode );

/********  Operations involving two rows or two colums of one matrix  *****/

void   __vf  MUBRows_exchange( ubPMatrix MA, ui ht, ui len,
                              ui i1, ui i2 );
void   __vf  MUBCols_exchange( ubPMatrix MA, ui ht, ui len,
                              ui i1, ui i2 );

/****************  Transposing and rotating a matrix **********************/

void  __vf  MUBtranspose( ubPMatrix MTr, ubPMatrix MA,
                          ui htTr, ui lenTr );
void  __vf  MUBrotate90(  ubPMatrix MRot, ubPMatrix MA, ui htRot, ui lenRot );
#define     MUBrotate180( MRot, MA, htRot, lenRot ) \
                VUB_rev( MRot, MA, (htRot)*(lenRot) )
void  __vf  MUBrotate270( ubPMatrix MRot, ubPMatrix MA, ui htRot, ui lenRot );

      /*************  Input and Output  ****************/

void  __vf M_ifprint( FILE _VFAR *stream, void _VFAR *X, ui ht, ui len, unsigned linewidth, unsigned vers );
#define MUBfprint( stream, MA0, ht, len, linewidth ) \
                    M_ifprint( stream, (void _VFAR *) (MA0), ht, len, linewidth, 1 )
#define MUB_fprint( stream, MA, ht, len, linewidth ) \
                    MUBfprint( stream, (MA)[0], ht, len, linewidth )
void  __vf M_icprint( void _VFAR *X, ui ht, ui len, unsigned vers );
#define MUBcprint( MA0, ht, len ) M_icprint( (void _VFAR *) (MA0), ht, len, 1 )
#define MUB_cprint( MA, ht, len ) MUBcprint( (MA)[0], ht, len )
#define MUBprint( MA0, ht, len )  M_ifprint( stdout, (void _VFAR *) (MA0), ht, len, 80, 1 )
#define MUB_print( MA, ht, len )  MUBprint( (MA)[0], ht, len )
  /*  MUB_print, MUB_cprint usable only for console applications! */

void __vf MUBwrite( FILE _VFAR *stream, ubPMatrix X, ui ht, ui len  );
void __vf MUBread( ubPMatrix X, ui ht, ui len, FILE _VFAR *stream );
#define MUBstore( str, MA, ht, len ) VUB_store( str, MA, (len)*(ht) )
#define MUBrecall( MA, ht, len, str) VUB_recall( MA, (len)*(ht), str)

#ifdef __cplusplus
} // end of extern "C"
#endif
#endif  /*  __MUBSTD_H  */
