/*  MUSstd.h

  matrix management functions:
  manipulations on matrices of data type "unsigned short"

  Copyright (c) 1996-2017 by OptiCode - Dr. Martin Sander Software Dev.
  All Rights Reserved.
*/

#if !defined( __MUSSTD_H )
#define __MUSSTD_H
#if !defined( __MATLIB_H )
#include <MatLib.h>
#endif
#if !defined( __VUSSTD_H )
#include <VUSstd.h>
#endif
#if !defined( __VUSMATH_H )
#include <VUSmath.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif

/*************   Dynamic Generation of Matrices   ************************/

usMatrix __vf  MUS_matrix(  ui ht, ui len );
usMatrix __vf  MUS_matrix0( ui ht, ui len );
#if defined (_MSC_VER) && defined (_DEBUG)
    usMatrix __vf  MUS_matrix_dbg(  ui ht, ui len );
    usMatrix __vf  MUS_matrix0_dbg( ui ht, ui len );
    #if defined (_INC_CRTDBG) && defined (_CRTDBG_MAP_ALLOC) 
	    /* Automatic mapping for memory-leak detection by CRT debugging switched on? */
        #define MUS_matrix  MUS_matrix_dbg
        #define MUS_matrix0 MUS_matrix0_dbg
    #endif
#else
    #define MUS_matrix_dbg  MUS_matrix
    #define MUS_matrix0_dbg MUS_matrix0
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

#define MUS_getElement( y, MA, ht, len, m, n ) MUSgetElement( y, (MA)[0], ht, len, m, n )
#define MUS_setElement( MA, ht, len, m, n, C ) MUSsetElement( (MA)[0], ht, len, m, n, C )
#define MUS_Pelement( MA, ht, len, m, n ) MUSPelement( (MA)[0], ht, len, m, n )
                     /* returns a pointer to MA[m][n]. */
#define MUS_element( MA, ht, len, m, n ) (*MUSPelement( (MA)[0], ht, len, m, n ))
                     /* dereferenced pointer */

 /****************  Initialization  ***************************************

    To initialize all elements of a matrix with the same value,
    or to perform arithmetic operations on all elements simultaneously,
    refer to the functions of VectorLib, declared in <VUSstd.h>, <VUSmath.h>.
    In order to use the VectorLib functions, utilize the feature that
    the whole matrix occupies one contiguous area in memory: pass the
    address of the first row to the desired vector function, the size
    of the "vector" being ht * len.
    For example, initialize all elements of the matrix MA with 1.0
    (this is *NOT* the identity matrix)  by calling
        VUS_equ1( (MA)[0], ht * len );
*/

#define MUS_equ0( MA, ht, len )            VUS_equ0( (MA)[0], (ht)*(len) )
#define MUS_equ1( MA, len )                MUSequ1( (MA)[0], len ) /* identity matrix */
#define MUS_random( MA, ht, len, seed, Min, Max ) \
                                          VUS_random( (MA)[0], (ht)*(len), seed, Min, Max )
#define MUS_outerprod( MA, X, Y, ht, len ) MUSouterprod( (MA)[0], X, Y, ht, len )
                       /* sizX=ht, sizY=len */
#define MUS_Row_equ0( MA, ht, len, iRow )  MUSRow_equ0( (MA)[0], ht, len, iRow )
#define MUS_Col_equ0( MA, ht, len, iCol )  MUSCol_equ0( (MA)[0], ht, len, iCol )
#define MUS_Dia_equ0( MA, len )            MUSDia_equ0( (MA)[0], len )
#define MUS_Row_equC( MA, ht, len, iRow, C ) \
                                        MUSRow_equC( (MA)[0], ht, len, iRow, C )
#define MUS_Col_equC( MA, ht, len, iCol, C ) \
                                        MUSCol_equC( (MA)[0], ht, len, iCol, C )
#define MUS_Dia_equC( MA, len, C )       MUSDia_equC( (MA)[0], len, C )

#define MUS_Row_equV( MA, ht, len, iRow, X ) \
                                        MUSRow_equV( (MA)[0], ht, len, iRow, X )
#define MUS_Col_equV( MA, ht, len, iCol, X ) \
                                        MUSCol_equV( (MA)[0], ht, len, iCol, X )
#define MUS_Dia_equV( MA, len, X )       MUSDia_equV( (MA)[0], len, X )

#define MUS_Trd_equM( MA, MTrd, len )    MUSTrd_equM( (MA)[0], (MTrd)[0], len )
#define MUS_Trd_extract( MTrd, MA, len ) MUSTrd_extract( (MTrd)[0], (MA)[0], len )

#define MUS_equM( MB, MA, ht, len )  VUS_equV( (MB)[0], (MA)[0], (ht)*(len) )

#define MUS_UequL( MA, len ) MUSUequL( (MA)[0], len )
#define MUS_LequU( MA, len ) MUSLequU( (MA)[0], len )
         /* copy lower-diagonal elements into upper-diagonal
           (or vice versa) by index-reflection, so as to
           get a symmetric matrix    */

            /* data-type conversions:  */
/************** Data-type interconversions  ****************************/

#define M_SItoUS( MUS, MSI, ht, len ) V_SItoUS( (MUS)[0], (MSI)[0], (ht)*(len) )
#define M_UStoSI( MSI, MUS, ht, len ) V_UStoSI( (MSI)[0], (MUS)[0], (ht)*(len) )
#define M_UStoUB( MUB, MUS, ht, len ) V_UStoUB( (MUB)[0], (MUS)[0], (ht)*(len) )
#define M_UStoU(  MU,  MUS, ht, len ) V_UStoU(  (MU)[0],  (MUS)[0], (ht)*(len) )
#define M_UStoUL( MUL, MUS, ht, len ) V_UStoUL( (MUL)[0], (MUS)[0], (ht)*(len) )
#define M_UBtoUS( MUS, MUB, ht, len ) V_UBtoUS( (MUS)[0], (MUB)[0], (ht)*(len) )
#define M_UtoUS(  MUS, MU,  ht, len ) V_UtoUS(  (MUS)[0], (MU)[0],  (ht)*(len) )
#define M_ULtoUS( MUS, MUL, ht, len ) V_ULtoUS( (MUS)[0], (MUL)[0], (ht)*(len) )
#define M_UStoF(  MF,  MUS, ht, len ) V_UStoF(  (MF)[0],  (MUS)[0], (ht)*(len) )
#define M_UStoD(  MD,  MUS, ht, len ) V_UStoD(  (MD)[0],  (MUS)[0], (ht)*(len) )
#ifdef _WIN64
	#define M_UStoUQ( MUQ, MUS, ht, len ) V_UStoUQ( (MUQ)[0], (MUS)[0], (ht)*(len) )
	#define M_UQtoUS( MUS, MUQ, ht, len ) V_UQtoUS( (MUS)[0], (MUQ)[0], (ht)*(len) )
#endif
#if (defined __BORLANDC__) && !(defined _WIN64)
    #define M_UStoE( ME, MUS, ht, len ) V_UStoE( (ME)[0], (MUS)[0], (ht)*(len) )
#else
    #define M_UStoE M_UStoD
#endif

/********  Extracting a submatrix and copying a submatrix back  *********/

#define MUS_submatrix( MSub, subHt, subLen, \
                      MSrce, srceHt, srceLen, \
                      firstRowInCol, sampInCol, firstColInRow, sampInRow ) \
               MUSsubmatrix(  (MSub)[0], subHt, subLen, \
                             (MSrce)[0], srceHt, srceLen, \
                             firstRowInCol, sampInCol, firstColInRow, sampInRow )

#define MUS_submatrix_equM( MDest, destHt, destLen, \
                           firstRowInCol, sampInCol, firstColInRow, sampInRow, \
                           MSrce, srceHt, srceLen ) \
               MUSsubmatrix_equM(  (MDest)[0], destHt, destLen, \
                             firstRowInCol, sampInCol, firstColInRow, sampInRow, \
                             (MSrce)[0], srceHt, srceLen )

#define MUS_equMblock( MSub, subHt, subLen, \
                      MSrce, srceHt, srceLen, \
                      firstRowInCol, firstColInRow ) \
               MUSequMblock(  (MSub)[0], subHt, subLen, \
                             (MSrce)[0], srceHt, srceLen, \
                             firstRowInCol, firstColInRow )

#define MUS_block_equM( MDest, destHt, destLen, \
                       firstRowInCol, firstColInRow, \
                       MSrce, srceHt, srceLen ) \
               MUSblock_equM( (MDest)[0], destHt, destLen, \
                             firstRowInCol, firstColInRow, \
                             (MSrce)[0], srceHt, srceLen )

#define MUS_equMblockT( MSub, subHt, subLen, \
                      MSrce, srceHt, srceLen, \
                      firstRowInCol, firstColInRow ) \
               MUSequMblockT(  (MSub)[0], subHt, subLen, \
                             (MSrce)[0], srceHt, srceLen, \
                             firstRowInCol, firstColInRow )

#define MUS_block_equMT( MDest, destHt, destLen, \
                       firstRowInCol, firstColInRow, \
                       MSrce, srceHt, srceLen ) \
               MUSblock_equMT( (MDest)[0], destHt, destLen, \
                             firstRowInCol, firstColInRow, \
                             (MSrce)[0], srceHt, srceLen )

/*****   Extracting a single row or a single column or the diagonal  ******
 *       and storing it into a vector                                     */

#define MUS_Row_extract( Y, MA, ht, len, iRow ) \
                                     MUSRow_extract( Y, (MA)[0], ht, len, iRow )
#define MUS_Col_extract( Y, MA, ht, len, iCol ) \
                                     MUSCol_extract( Y, (MA)[0], ht, len, iCol )
#define MUS_Dia_extract( Y, MA, len ) MUSDia_extract( Y, (MA)[0], len )


/**************  Deleting or inserting a row or a column   ***************/

#define MUS_Row_delete( MB, MA, htA, lenA, iRow ) \
                           MUSRow_delete( (MB)[0], (MA)[0], htA, lenA, iRow )
#define MUS_Col_delete( MB, MA, htA, lenA, iCol ) \
                           MUSCol_delete( (MB)[0], (MA)[0], htA, lenA, iCol )
#define MUS_Row_insert( MB, MA, htB, lenB, iRow, X ) \
                           MUSRow_insert( (MB)[0], (MA)[0], htB, lenB, iRow, X )
#define MUS_Col_insert( MB, MA, htB, lenB, iCol, X ) \
                           MUSCol_insert( (MB)[0], (MA)[0], htB, lenB, iCol, X )

/******  One-dimensional vector operations **********************
         performed along all rows or all columns simultaneously,
         or along the diagonal of a square matrix                */

#define MUS_Rows_max( Y, MA, ht, len )     MUSRows_max( Y, (MA)[0], ht, len )
#define MUS_Cols_max( Y, MA, ht, len )     MUSCols_max( Y, (MA)[0], ht, len )
#define MUS_Dia_max(  MA, len )            MUSDia_max(  (MA)[0], len )
#define MUS_Rows_min( Y, MA, ht, len )     MUSRows_min( Y, (MA)[0], ht, len )
#define MUS_Cols_min( Y, MA, ht, len )     MUSCols_min( Y, (MA)[0], ht, len )
#define MUS_Dia_min(  MA, len )            MUSDia_min(  (MA)[0], len )

#define MUS_Rows_rotate( MA, ht, len, pos) MUSRows_rotate( (MA)[0], ht, len, pos )
#define MUS_Cols_rotate( MA, ht, len, pos) MUSCols_rotate( (MA)[0], ht, len, pos )
#define MUS_Rows_rotate_buf( MA, ht, len, pos, MBuf) MUSRows_rotate_buf( (MA)[0], ht, len, pos, (MBuf)[0] )
#define MUS_Cols_rotate_buf( MA, ht, len, pos, MBuf) MUSCols_rotate_buf( (MA)[0], ht, len, pos, (MBuf)[0] )
#define MUS_Rows_reflect( MA, ht, len)     MUSRows_reflect( (MA)[0], ht, len )
#define MUS_Cols_reflect( MA, ht, len)     MUSCols_reflect( (MA)[0], ht, len )
#define MUS_Rows_rev( MA, ht, len)         MUSRows_rev( (MA)[0], ht, len )
#define MUS_Cols_rev( MA, ht, len)         MUSCols_rev( (MA)[0], ht, len )

#define MUS_Rows_distribution( MAbund, Limits, nBins, MX, htX, lenX, mode ) MUSRows_distribution( (MAbund)[0], Limits, nBins, (MX)[0], htX, lenX, mode )
#define MUS_Cols_distribution( MAbund, Limits, nBins, MX, htX, lenX, mode ) MUSCols_distribution( (MAbund)[0], Limits, nBins, (MX)[0], htX, lenX, mode )

/********  Operations involving two rows or two colums of one matrix  *****/

#define MUS_Rows_exchange( MA, ht, len, row1, row2 ) \
                             MUSRows_exchange( (MA)[0], ht, len, row1, row2 )
#define MUS_Cols_exchange( MA, ht, len, col1, col2 ) \
                             MUSCols_exchange( (MA)[0], ht, len, col1, col2 )

/***************  Transposing and rotating a matrix **********************/

#define MUS_transpose( MTr, MA, htTr, lenTr ) \
             MUStranspose( (MTr)[0], (MA)[0], htTr, lenTr )
       /*  dimensions htTr, lenTr are those of the transposed matrix,
           not of the original!                */
#define MUS_rotate90( MRot, MA, htRot, lenRot ) \
             MUSrotate90( (MRot)[0], (MA)[0], htRot, lenRot )
#define MUS_rotate180( MRot, MA, htRot, lenRot ) \
             VUS_rev( (MRot)[0], (MA)[0], (htRot)*(lenRot) )
#define MUS_rotate270( MRot, MA, htRot, lenRot ) \
             MUSrotate270( (MRot)[0], (MA)[0], htRot, lenRot )

/**************************  Input and Output  **************************/

#define MUS_write( str, MA, ht, len )   MUSwrite( str, (MA)[0], ht, len )
#define MUS_read( MA, ht, len, str )    MUSread( (MA)[0], ht, len, str )
#define MUS_setWriteFormat              VUS_setWriteFormat
#define MUS_setWriteSeparate            VUS_setNWriteSeparate
                                   /* write and read in ascii format */
#define MUS_store( str, MA, ht, len )   VUS_store( str, (MA)[0], (len)*(ht) )
#define MUS_recall( MA, ht, len, str)   VUS_recall( (MA)[0], (len)*(ht), str)
                                  /* store and recall in binary format */


/*************************************************************************
 * Here are now the actual declarations of the functions used internally.*
 * These declarations may change in future versions of MatrixLib!        *
 * You should not care too much about them, except in the case you need  *
 * the actual address of a run-time function (see above). Under all      *
 * "normal" circumstances, use only the names defined above in the       *
 * macro section!                                                        *
 *************************************************************************/

void  __vf MUSgetElement( unsigned short *y, usPMatrix X, ui ht, ui len, ui m, ui n );
void  __vf MUSsetElement( usPMatrix X, ui ht, ui len, ui m, ui n, unsigned short C );
unsigned short _VFAR * __vf MUSPelement( usPMatrix X, ui ht, ui len, ui m, ui n );
                  /* pointer is normalized in memory model HUGE */
#define MUSelement( MA, ht, len, m, n ) (*MUSPelement( MA, ht, len, m, n ))

#define MUSequ0( MA, ht, len )            VUS_equ0( MA, (ht)*(len) )
void   __vf  MUSequ1( usPMatrix MA, ui len );  /* identity matrix */
void   __vf  MUSouterprod( usPMatrix MA, usVector X,  usVector Y,
                          ui ht, ui len );

void   __vf  MUSRow_equ0( usPMatrix MA, ui ht, ui len,
                         ui iRow );
void   __vf  MUSCol_equ0( usPMatrix MA, ui ht, ui len,
                         ui iCol );
void   __vf  MUSDia_equ0( usPMatrix MA, ui len );

void   __vf  MUSRow_equC( usPMatrix MA, ui ht, ui len,
                         ui iRow, unsigned short C );
void   __vf  MUSCol_equC( usPMatrix MA, ui ht, ui len,
                         ui iCol, unsigned short C );
void   __vf  MUSDia_equC( usPMatrix MA, ui len, unsigned short C );

void   __vf  MUSRow_equV( usPMatrix MA, ui ht, ui len,
                         ui iRow, usVector X );
void   __vf  MUSCol_equV( usPMatrix MA, ui ht, ui len,
                         ui iCol, usVector X );
void   __vf  MUSDia_equV( usPMatrix MA, ui len, usVector X );

void   __vf  MUSTrd_equM( usPMatrix MA, usPMatrix MTrd, ui len );
void   __vf  MUSTrd_extract( usPMatrix MTrd, usPMatrix MA, ui len );

#define MUSequM( MB, MA, ht, len )  VUS_equV( MB, MA, (ht)*(len) )
void   __vf  MUSUequL( usPMatrix MA, ui len );
void   __vf  MUSLequU( usPMatrix MA, ui len );

/********  Extracting a submatrix and copying a submatrix back  *********/

void  __vf  MUSsubmatrix( usPMatrix MSub,
                          ui subHt,  ui subLen,
                          usPMatrix MSrce,
                          ui srceHt,  ui srceLen,
                          ui firstRowInCol,  ui sampInCol,
                          ui firstColInRow,  ui sampInRow );

void  __vf  MUSsubmatrix_equM( usPMatrix MDest,
                               ui destHt,     ui destLen,
                               ui firstRowInCol,  ui sampInCol,
                               ui firstColInRow,  ui sampInRow,
                               usPMatrix MSrce,
                               ui srceHt,     ui srceLen );

void  __vf  MUSequMblock(  usPMatrix MSub,
                          ui subHt,  ui subLen,
                          usPMatrix MSrce,
                          ui srceHt,  ui srceLen,
                          ui firstRowInCol,  ui firstColInRow );

void  __vf  MUSblock_equM( usPMatrix MDest,
                          ui destHt,     ui destLen,
                          ui firstRowInCol,  ui firstColInRow,
                          usPMatrix MSrce,
                          ui srceHt,     ui srceLen );

void  __vf  MUSequMblockT( usPMatrix MSub,
                          ui subHt,  ui subLen,
                          usPMatrix MSrce,
                          ui srceHt,  ui srceLen,
                          ui firstRowInCol,  ui firstColInRow );

void  __vf  MUSblock_equMT( usPMatrix MDest,
                          ui destHt,     ui destLen,
                          ui firstRowInCol,  ui firstColInRow,
                          usPMatrix MSrce,
                          ui srceHt,     ui srceLen );


/*****   Extracting a single row or a single column or the diagonal  *****
 *       and storing it into a vector                                    */

void __vf MUSRow_extract( usVector Y, usPMatrix MA, ui ht, ui len, ui iRow );
void __vf MUSCol_extract( usVector Y, usPMatrix MA, ui ht, ui len, ui iCol );
void __vf MUSDia_extract( usVector Y, usPMatrix MA, ui len );


/**********  Deleting or inserting a row or a column *****************/

void __vf MUSRow_delete( usPMatrix MB, usPMatrix MA,
                        ui htA, ui lenA, ui iRow );
void __vf MUSCol_delete( usPMatrix MB, usPMatrix MA,
                        ui htA, ui lenA, ui iCol );
void __vf MUSRow_insert( usPMatrix MB, usPMatrix MA, ui htB,
                        ui lenB, ui iRow, usVector X );
void __vf MUSCol_insert( usPMatrix MB, usPMatrix MA, ui htB,
                        ui lenB, ui iCol, usVector X );


/******  One-dimensional vector operations **********************
         performed along all rows or all columns simultaneously,
         or along the diagonal of a square matrix                */

void  __vf  MUSRows_max( usVector Y, usPMatrix MA, ui ht, ui len );
void  __vf  MUSCols_max( usVector Y, usPMatrix MA, ui ht, ui len );
unsigned short __vf  MUSDia_max(  usPMatrix MA, ui len );
void  __vf  MUSRows_min( usVector Y, usPMatrix MA, ui ht, ui len );
void  __vf  MUSCols_min( usVector Y, usPMatrix MA, ui ht, ui len );
unsigned short __vf  MUSDia_min(  usPMatrix MA, ui len );

void  __vf  MUSRows_rotate( usPMatrix MA, ui ht, ui len, ssize_t pos );
void  __vf  MUSCols_rotate( usPMatrix MA, ui ht, ui len, ssize_t pos );
void  __vf  MUSRows_rotate_buf( usPMatrix MA, ui ht, ui len, ssize_t pos, usPMatrix MBuf );
void  __vf  MUSCols_rotate_buf( usPMatrix MA, ui ht, ui len, ssize_t pos, usPMatrix MBuf );
void  __vf  MUSRows_reflect( usPMatrix MA, ui ht, ui len );
void  __vf  MUSCols_reflect( usPMatrix MA, ui ht, ui len );
void  __vf  MUSRows_rev( usPMatrix MA, ui ht, ui len );
void  __vf  MUSCols_rev( usPMatrix MA, ui ht, ui len );

void  __vf  MUSRows_distribution( uiPMatrix MAbund, usVector Limits, ui nBins, usPMatrix MX, ui ht, ui len, int mode );
void  __vf  MUSCols_distribution( uiPMatrix MAbund, usVector Limits, ui nBins, usPMatrix MX, ui ht, ui len, int mode );

/********  Operations involving two rows or two colums of one matrix  *****/

void   __vf  MUSRows_exchange( usPMatrix MA, ui ht, ui len,
                              ui i1, ui i2 );
void   __vf  MUSCols_exchange( usPMatrix MA, ui ht, ui len,
                              ui i1, ui i2 );

/****************  Transposing and rotating a matrix **********************/

void  __vf  MUStranspose( usPMatrix MTr, usPMatrix MA,
                          ui htTr, ui lenTr );
void  __vf  MUSrotate90(  usPMatrix MRot, usPMatrix MA, ui htRot, ui lenRot );
#define     MUSrotate180( MRot, MA, htRot, lenRot ) \
                VUS_rev( MRot, MA, (htRot)*(lenRot) )
void  __vf  MUSrotate270( usPMatrix MRot, usPMatrix MA, ui htRot, ui lenRot );

      /*************  Input and Output  ****************/

void  __vf M_ifprint( FILE _VFAR *stream, void _VFAR *X, ui ht, ui len, unsigned linewidth, unsigned vers );
#define MUSfprint( stream, MA0, ht, len, linewidth ) \
                    M_ifprint( stream, (void _VFAR *) (MA0), ht, len, linewidth, 3 )
#define MUS_fprint( stream, MA, ht, len, linewidth ) \
                    MUSfprint( stream, (MA)[0], ht, len, linewidth )
void  __vf M_icprint( void _VFAR *X, ui ht, ui len, unsigned vers );
#define MUScprint( MA0, ht, len ) M_icprint( (void _VFAR *) (MA0), ht, len, 3 )
#define MUS_cprint( MA, ht, len ) MUScprint( (MA)[0], ht, len )
#define MUSprint( MA0, ht, len )  M_ifprint( stdout, (void _VFAR *) (MA0), ht, len, 80, 3 )
#define MUS_print( MA, ht, len )  MUSprint( (MA)[0], ht, len )
  /*  MUS_print, MUS_cprint usable only for console applications! */

void __vf MUSwrite( FILE _VFAR *stream, usPMatrix X, ui ht, ui len  );
void __vf MUSread( usPMatrix X, ui ht, ui len, FILE _VFAR *stream );
#define MUSstore( str, MA, ht, len ) VUS_store( str, MA, (len)*(ht) )
#define MUSrecall( MA, ht, len, str) VUS_recall( MA, (len)*(ht), str)

#ifdef __cplusplus
} // end of extern "C"
#endif
#endif  /*  __MUSSTD_H  */
