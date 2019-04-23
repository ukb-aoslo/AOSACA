/*  MLIstd.h

  matrix management functions:
  manipulations on matrices of data type "long"

  Copyright (c) 1996-2017 by OptiCode - Dr. Martin Sander Software Dev.
  All Rights Reserved.
*/

#if !defined( __MLISTD_H )
#define __MLISTD_H
#if !defined( __MATLIB_H )
#include <MatLib.h>
#endif
#if !defined( __VLISTD_H )
#include <VLIstd.h>
#endif
#if !defined( __VLIMATH_H )
#include <VLImath.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif

/*************   Dynamic Generation of Matrices   ************************/

liMatrix __vf  MLI_matrix(  ui ht, ui len );
liMatrix __vf  MLI_matrix0( ui ht, ui len );
#if defined (_MSC_VER) && defined (_DEBUG)
    liMatrix __vf  MLI_matrix_dbg(  ui ht, ui len );
    liMatrix __vf  MLI_matrix0_dbg( ui ht, ui len );
    #if defined (_INC_CRTDBG) && defined (_CRTDBG_MAP_ALLOC) 
	    /* Automatic mapping for memory-leak detection by CRT debugging switched on? */ 
        #define MLI_matrix  MLI_matrix_dbg
        #define MLI_matrix0 MLI_matrix0_dbg
    #endif
#else
    #define MLI_matrix_dbg  MLI_matrix
    #define MLI_matrix0_dbg MLI_matrix0
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

#define MLI_getElement( y, MA, ht, len, m, n ) MLIgetElement( y, (MA)[0], ht, len, m, n )
#define MLI_setElement( MA, ht, len, m, n, C ) MLIsetElement( (MA)[0], ht, len, m, n, C )
#define MLI_Pelement( MA, ht, len, m, n ) MLIPelement( (MA)[0], ht, len, m, n )
                     /* returns a pointer to MA[m][n]. */
#define MLI_element( MA, ht, len, m, n ) (*MLIPelement( (MA)[0], ht, len, m, n ))
                     /* dereferenced pointer */

 /****************  Initialization  ***************************************

    To initialize all elements of a matrix with the same value,
    or to perform arithmetic operations on all elements simultaneously,
    refer to the functions of VectorLib, declared in <VLIstd.h>, <VLImath.h>.
    In order to use the VectorLib functions, utilize the feature that
    the whole matrix occupies one contiguous area in memory: pass the
    address of the first row to the desired vector function, the size
    of the "vector" being ht * len.
    For example, initialize all elements of the matrix MA with 1.0
    (this is *NOT* the identity matrix)  by calling
        VLI_equ1( (MA)[0], ht * len );
*/

#define MLI_equ0( MA, ht, len )            VLI_equ0( (MA)[0], (ht)*(len) )
#define MLI_equ1( MA, len )                MLIequ1( (MA)[0], len ) /* identity matrix */
#define MLI_equm1( MA, len )               MLIequm1( (MA)[0], len ) /* neg. identity matrix */
#define MLI_random( MA, ht, len, seed, Min, Max ) \
                                          VLI_random( (MA)[0], (ht)*(len), seed, Min, Max )
#define MLI_outerprod( MA, X, Y, ht, len ) MLIouterprod( (MA)[0], X, Y, ht, len )
                       /* sizX=ht, sizY=len */
#define MLI_Row_equ0( MA, ht, len, iRow )  MLIRow_equ0( (MA)[0], ht, len, iRow )
#define MLI_Col_equ0( MA, ht, len, iCol )  MLICol_equ0( (MA)[0], ht, len, iCol )
#define MLI_Dia_equ0( MA, len )            MLIDia_equ0( (MA)[0], len )
#define MLI_Row_equC( MA, ht, len, iRow, C ) \
                                        MLIRow_equC( (MA)[0], ht, len, iRow, C )
#define MLI_Col_equC( MA, ht, len, iCol, C ) \
                                        MLICol_equC( (MA)[0], ht, len, iCol, C )
#define MLI_Dia_equC( MA, len, C )       MLIDia_equC( (MA)[0], len, C )

#define MLI_Row_equV( MA, ht, len, iRow, X ) \
                                        MLIRow_equV( (MA)[0], ht, len, iRow, X )
#define MLI_Col_equV( MA, ht, len, iCol, X ) \
                                        MLICol_equV( (MA)[0], ht, len, iCol, X )
#define MLI_Dia_equV( MA, len, X )       MLIDia_equV( (MA)[0], len, X )

#define MLI_Trd_equM( MA, MTrd, len )    MLITrd_equM( (MA)[0], (MTrd)[0], len )
#define MLI_Trd_extract( MTrd, MA, len ) MLITrd_extract( (MTrd)[0], (MA)[0], len )

#define MLI_equM( MB, MA, ht, len )  VLI_equV( (MB)[0], (MA)[0], (ht)*(len) )
#define MLI_neg( MB, MA, ht, len )   VLI_neg( (MB)[0], (MA)[0], (ht)*(len) )

#define MLI_UequL( MA, len ) MLIUequL( (MA)[0], len )
#define MLI_LequU( MA, len ) MLILequU( (MA)[0], len )
         /* copy lower-diagonal elements into upper-diagonal
           (or vice versa) by index-reflection, so as to
           get a symmetric matrix    */

            /* data-type conversions:  */
/************** Data-type interconversions  ****************************/

#define M_LItoUL( MUL, MLI, ht, len ) V_LItoUL( (MUL)[0], (MLI)[0], (ht)*(len) )
#define M_ULtoLI( MLI, MUL, ht, len ) V_ULtoLI( (MLI)[0], (MUL)[0], (ht)*(len) )
#define M_LItoBI( MBI, MLI, ht, len ) V_LItoBI( (MBI)[0], (MLI)[0], (ht)*(len) )
#define M_LItoSI( MSI, MLI, ht, len ) V_LItoSI( (MSI)[0], (MLI)[0], (ht)*(len) )
#define M_LItoI(  MI,  MLI, ht, len ) V_LItoI(  (MI)[0],  (MLI)[0], (ht)*(len) )
#define M_LItoQI( MQI, MLI, ht, len ) V_LItoQI( (MQI)[0], (MLI)[0], (ht)*(len) )
#define M_BItoLI( MLI, MBI, ht, len ) V_BItoLI( (MLI)[0], (MBI)[0], (ht)*(len) )
#define M_SItoLI( MLI, MSI, ht, len ) V_SItoLI( (MLI)[0], (MSI)[0], (ht)*(len) )
#define M_ItoLI(  MLI, MI,  ht, len ) V_ItoLI(  (MLI)[0], (MI)[0],  (ht)*(len) )
#define M_QItoLI( MLI, MQI, ht, len ) V_QItoLI( (MLI)[0], (MQI)[0], (ht)*(len) )
#define M_LItoF(  MF,  MLI, ht, len ) V_LItoF(  (MF)[0],  (MLI)[0], (ht)*(len) )
#define M_LItoD(  MD,  MLI, ht, len ) V_LItoD(  (MD)[0],  (MLI)[0], (ht)*(len) )
#if (defined __BORLANDC__) && !(defined _WIN64)
    #define M_LItoE( ME, MLI, ht, len ) V_LItoE( (ME)[0], (MLI)[0], (ht)*(len) )
#else
    #define M_LItoE M_LItoD
#endif

/********  Extracting a submatrix and copying a submatrix back  *********/

#define MLI_submatrix( MSub, subHt, subLen, \
                      MSrce, srceHt, srceLen, \
                      firstRowInCol, sampInCol, firstColInRow, sampInRow ) \
               MLIsubmatrix(  (MSub)[0], subHt, subLen, \
                             (MSrce)[0], srceHt, srceLen, \
                             firstRowInCol, sampInCol, firstColInRow, sampInRow )

#define MLI_submatrix_equM( MDest, destHt, destLen, \
                           firstRowInCol, sampInCol, firstColInRow, sampInRow, \
                           MSrce, srceHt, srceLen ) \
               MLIsubmatrix_equM(  (MDest)[0], destHt, destLen, \
                             firstRowInCol, sampInCol, firstColInRow, sampInRow, \
                             (MSrce)[0], srceHt, srceLen )

#define MLI_equMblock( MSub, subHt, subLen, \
                      MSrce, srceHt, srceLen, \
                      firstRowInCol, firstColInRow ) \
               MLIequMblock(  (MSub)[0], subHt, subLen, \
                             (MSrce)[0], srceHt, srceLen, \
                             firstRowInCol, firstColInRow )

#define MLI_block_equM( MDest, destHt, destLen, \
                       firstRowInCol, firstColInRow, \
                       MSrce, srceHt, srceLen ) \
               MLIblock_equM( (MDest)[0], destHt, destLen, \
                             firstRowInCol, firstColInRow, \
                             (MSrce)[0], srceHt, srceLen )

#define MLI_equMblockT( MSub, subHt, subLen, \
                      MSrce, srceHt, srceLen, \
                      firstRowInCol, firstColInRow ) \
               MLIequMblockT(  (MSub)[0], subHt, subLen, \
                             (MSrce)[0], srceHt, srceLen, \
                             firstRowInCol, firstColInRow )

#define MLI_block_equMT( MDest, destHt, destLen, \
                       firstRowInCol, firstColInRow, \
                       MSrce, srceHt, srceLen ) \
               MLIblock_equMT( (MDest)[0], destHt, destLen, \
                             firstRowInCol, firstColInRow, \
                             (MSrce)[0], srceHt, srceLen )

/*****   Extracting a single row or a single column or the diagonal  ******
 *       and storing it into a vector                                     */

#define MLI_Row_extract( Y, MA, ht, len, iRow ) \
                                     MLIRow_extract( Y, (MA)[0], ht, len, iRow )
#define MLI_Col_extract( Y, MA, ht, len, iCol ) \
                                     MLICol_extract( Y, (MA)[0], ht, len, iCol )
#define MLI_Dia_extract( Y, MA, len ) MLIDia_extract( Y, (MA)[0], len )


/**************  Deleting or inserting a row or a column   ***************/

#define MLI_Row_delete( MB, MA, htA, lenA, iRow ) \
                           MLIRow_delete( (MB)[0], (MA)[0], htA, lenA, iRow )
#define MLI_Col_delete( MB, MA, htA, lenA, iCol ) \
                           MLICol_delete( (MB)[0], (MA)[0], htA, lenA, iCol )
#define MLI_Row_insert( MB, MA, htB, lenB, iRow, X ) \
                           MLIRow_insert( (MB)[0], (MA)[0], htB, lenB, iRow, X )
#define MLI_Col_insert( MB, MA, htB, lenB, iCol, X ) \
                           MLICol_insert( (MB)[0], (MA)[0], htB, lenB, iCol, X )

/******  One-dimensional vector operations **********************
         performed along all rows or all columns simultaneously,
         or along the diagonal of a square matrix                */

#define MLI_Rows_max( Y, MA, ht, len )     MLIRows_max( Y, (MA)[0], ht, len )
#define MLI_Cols_max( Y, MA, ht, len )     MLICols_max( Y, (MA)[0], ht, len )
#define MLI_Dia_max(  MA, len )            MLIDia_max(  (MA)[0], len )
#define MLI_Rows_min( Y, MA, ht, len )     MLIRows_min( Y, (MA)[0], ht, len )
#define MLI_Cols_min( Y, MA, ht, len )     MLICols_min( Y, (MA)[0], ht, len )
#define MLI_Dia_min(  MA, len )            MLIDia_min(  (MA)[0], len )

#define MLI_Rows_rotate( MA, ht, len, pos) MLIRows_rotate( (MA)[0], ht, len, pos )
#define MLI_Cols_rotate( MA, ht, len, pos) MLICols_rotate( (MA)[0], ht, len, pos )
#define MLI_Rows_rotate_buf( MA, ht, len, pos, MBuf) MLIRows_rotate_buf( (MA)[0], ht, len, pos, (MBuf)[0] )
#define MLI_Cols_rotate_buf( MA, ht, len, pos, MBuf) MLICols_rotate_buf( (MA)[0], ht, len, pos, (MBuf)[0] )
#define MLI_Rows_reflect( MA, ht, len)     MLIRows_reflect( (MA)[0], ht, len )
#define MLI_Cols_reflect( MA, ht, len)     MLICols_reflect( (MA)[0], ht, len )
#define MLI_Rows_rev( MA, ht, len)         MLIRows_rev( (MA)[0], ht, len )
#define MLI_Cols_rev( MA, ht, len)         MLICols_rev( (MA)[0], ht, len )

#define MLI_Rows_distribution( MAbund, Limits, nBins, MX, htX, lenX, mode ) MLIRows_distribution( (MAbund)[0], Limits, nBins, (MX)[0], htX, lenX, mode )
#define MLI_Cols_distribution( MAbund, Limits, nBins, MX, htX, lenX, mode ) MLICols_distribution( (MAbund)[0], Limits, nBins, (MX)[0], htX, lenX, mode )

/********  Operations involving two rows or two colums of one matrix  *****/

#define MLI_Rows_exchange( MA, ht, len, row1, row2 ) \
                             MLIRows_exchange( (MA)[0], ht, len, row1, row2 )
#define MLI_Cols_exchange( MA, ht, len, col1, col2 ) \
                             MLICols_exchange( (MA)[0], ht, len, col1, col2 )

/************  Transposing and rotating a matrix **********************/

#define MLI_transpose( MTr, MA, htTr, lenTr ) \
             MLItranspose( (MTr)[0], (MA)[0], htTr, lenTr )
       /*  dimensions htTr, lenTr are those of the transposed matrix,
           not of the original!                */
#define MLI_rotate90( MRot, MA, htRot, lenRot ) \
             MLIrotate90( (MRot)[0], (MA)[0], htRot, lenRot )
#define MLI_rotate180( MRot, MA, htRot, lenRot ) \
             VLI_rev( (MRot)[0], (MA)[0], (htRot)*(lenRot) )
#define MLI_rotate270( MRot, MA, htRot, lenRot ) \
             MLIrotate270( (MRot)[0], (MA)[0], htRot, lenRot )

/**************************  Input and Output  **************************/

#define MLI_write( str, MA, ht, len )   MLIwrite( str, (MA)[0], ht, len )
#define MLI_read( MA, ht, len, str )    MLIread( (MA)[0], ht, len, str )
#define MLI_setWriteFormat              VLI_setWriteFormat
#define MLI_setWriteSeparate            VLI_setNWriteSeparate
                                   /* write and read in ascii format */
#define MLI_store( str, MA, ht, len )   VLI_store( str, (MA)[0], (len)*(ht) )
#define MLI_recall( MA, ht, len, str)   VLI_recall( (MA)[0], (len)*(ht), str)
                                  /* store and recall in binary format */


/*************************************************************************
 * Here are now the actual declarations of the functions used internally.*
 * These declarations may change in future versions of MatrixLib!        *
 * You should not care too much about them, except in the case you need  *
 * the actual address of a run-time function (see above). Under all      *
 * "normal" circumstances, use only the names defined above in the       *
 * macro section!                                                        *
 *************************************************************************/

void  __vf MLIgetElement( long *y, liPMatrix X, ui ht, ui len, ui m, ui n );
void  __vf MLIsetElement( liPMatrix X, ui ht, ui len, ui m, ui n, long C );
long _VFAR * __vf MLIPelement( liPMatrix X, ui ht, ui len, ui m, ui n );
                  /* pointer is normalized in memory model HUGE */
#define MLIelement( MA, ht, len, m, n ) (*MLIPelement( MA, ht, len, m, n ))

#define MLIequ0( MA, ht, len )            VLI_equ0( MA, (ht)*(len) )
void   __vf  MLIequ1( liPMatrix MA, ui len );  /* identity matrix */
void   __vf  MLIequm1( liPMatrix MA, ui len );  /* neg. identity matrix */
void   __vf  MLIouterprod( liPMatrix MA, liVector X,  liVector Y,
                          ui ht, ui len );

void   __vf  MLIRow_equ0( liPMatrix MA, ui ht, ui len,
                         ui iRow );
void   __vf  MLICol_equ0( liPMatrix MA, ui ht, ui len,
                         ui iCol );
void   __vf  MLIDia_equ0( liPMatrix MA, ui len );

void   __vf  MLIRow_equC( liPMatrix MA, ui ht, ui len,
                         ui iRow, long C );
void   __vf  MLICol_equC( liPMatrix MA, ui ht, ui len,
                         ui iCol, long C );
void   __vf  MLIDia_equC( liPMatrix MA, ui len, long C );

void   __vf  MLIRow_equV( liPMatrix MA, ui ht, ui len,
                         ui iRow, liVector X );
void   __vf  MLICol_equV( liPMatrix MA, ui ht, ui len,
                         ui iCol, liVector X );
void   __vf  MLIDia_equV( liPMatrix MA, ui len, liVector X );

void   __vf  MLITrd_equM( liPMatrix MA, liPMatrix MTrd, ui len );
void   __vf  MLITrd_extract( liPMatrix MTrd, liPMatrix MA, ui len );

#define MLIequM( MB, MA, ht, len )  VLI_equV( MB, MA, (ht)*(len) )
#define MLIneg( MB, MA, ht, len )   VLI_neg( MB, MA, (ht)*(len) )
void   __vf  MLIUequL( liPMatrix MA, ui len );
void   __vf  MLILequU( liPMatrix MA, ui len );

/********  Extracting a submatrix and copying a submatrix back  *********/

void  __vf  MLIsubmatrix( liPMatrix MSub,
                          ui subHt,  ui subLen,
                          liPMatrix MSrce,
                          ui srceHt,  ui srceLen,
                          ui firstRowInCol,  ui sampInCol,
                          ui firstColInRow,  ui sampInRow );

void  __vf  MLIsubmatrix_equM( liPMatrix MDest,
                               ui destHt,     ui destLen,
                               ui firstRowInCol,  ui sampInCol,
                               ui firstColInRow,  ui sampInRow,
                               liPMatrix MSrce,
                               ui srceHt,     ui srceLen );

void  __vf  MLIequMblock(  liPMatrix MSub,
                          ui subHt,  ui subLen,
                          liPMatrix MSrce,
                          ui srceHt,  ui srceLen,
                          ui firstRowInCol,  ui firstColInRow );

void  __vf  MLIblock_equM( liPMatrix MDest,
                          ui destHt,     ui destLen,
                          ui firstRowInCol,  ui firstColInRow,
                          liPMatrix MSrce,
                          ui srceHt,     ui srceLen );

void  __vf  MLIequMblockT( liPMatrix MSub,
                          ui subHt,  ui subLen,
                          liPMatrix MSrce,
                          ui srceHt,  ui srceLen,
                          ui firstRowInCol,  ui firstColInRow );

void  __vf  MLIblock_equMT( liPMatrix MDest,
                          ui destHt,     ui destLen,
                          ui firstRowInCol,  ui firstColInRow,
                          liPMatrix MSrce,
                          ui srceHt,     ui srceLen );


/*****   Extracting a single row or a single column or the diagonal  *****
 *       and storing it into a vector                                    */

void __vf MLIRow_extract( liVector Y, liPMatrix MA, ui ht, ui len,
                           ui iRow );
void __vf MLICol_extract( liVector Y, liPMatrix MA, ui ht, ui len,
                           ui iCol );
void __vf MLIDia_extract( liVector Y, liPMatrix MA, ui len );


/**********  Deleting or inserting a row or a column *****************/

void __vf MLIRow_delete( liPMatrix MB, liPMatrix MA,
                        ui htA, ui lenA, ui iRow );
void __vf MLICol_delete( liPMatrix MB, liPMatrix MA,
                        ui htA, ui lenA, ui iCol );
void __vf MLIRow_insert( liPMatrix MB, liPMatrix MA, ui htB,
                        ui lenB, ui iRow, liVector X );
void __vf MLICol_insert( liPMatrix MB, liPMatrix MA, ui htB,
                        ui lenB, ui iCol, liVector X );


/******  One-dimensional vector operations **********************
         performed along all rows or all columns simultaneously,
         or along the diagonal of a square matrix                */

void  __vf  MLIRows_max( liVector Y, liPMatrix MA, ui ht, ui len );
void  __vf  MLICols_max( liVector Y, liPMatrix MA, ui ht, ui len );
long __vf  MLIDia_max(  liPMatrix MA, ui len );
void  __vf  MLIRows_min( liVector Y, liPMatrix MA, ui ht, ui len );
void  __vf  MLICols_min( liVector Y, liPMatrix MA, ui ht, ui len );
long __vf  MLIDia_min(  liPMatrix MA, ui len );

void  __vf  MLIRows_rotate( liPMatrix MA, ui ht, ui len, ssize_t pos );
void  __vf  MLICols_rotate( liPMatrix MA, ui ht, ui len, ssize_t pos );
void  __vf  MLIRows_rotate_buf( liPMatrix MA, ui ht, ui len, ssize_t pos, liPMatrix MBuf );
void  __vf  MLICols_rotate_buf( liPMatrix MA, ui ht, ui len, ssize_t pos, liPMatrix MBuf );
void  __vf  MLIRows_reflect( liPMatrix MA, ui ht, ui len );
void  __vf  MLICols_reflect( liPMatrix MA, ui ht, ui len );
void  __vf  MLIRows_rev( liPMatrix MA, ui ht, ui len );
void  __vf  MLICols_rev( liPMatrix MA, ui ht, ui len );

void  __vf  MLIRows_distribution( uiPMatrix MAbund, liVector Limits, ui nBins, liPMatrix MX, ui ht, ui len, int mode );
void  __vf  MLICols_distribution( uiPMatrix MAbund, liVector Limits, ui nBins, liPMatrix MX, ui ht, ui len, int mode );

/********  Operations involving two rows or two colums of one matrix  *****/

void   __vf  MLIRows_exchange( liPMatrix MA, ui ht, ui len,
                              ui i1, ui i2 );
void   __vf  MLICols_exchange( liPMatrix MA, ui ht, ui len,
                              ui i1, ui i2 );

/*****************  Transposing and rotating a matrix **********************/

void  __vf  MLItranspose( liPMatrix MTr, liPMatrix MA,
                          ui htTr, ui lenTr );
void  __vf  MLIrotate90(  liPMatrix MRot, liPMatrix MA, ui htRot, ui lenRot );
#define     MLIrotate180( MRot, MA, htRot, lenRot ) \
                VLI_rev( MRot, MA, (htRot)*(lenRot) )
void  __vf  MLIrotate270( liPMatrix MRot, liPMatrix MA, ui htRot, ui lenRot );

      /*************  Input and Output  ****************/

void  __vf M_ifprint( FILE _VFAR *stream, void _VFAR *X, ui ht, ui len, unsigned linewidth, unsigned vers );
#define MLIfprint( stream, MA0, ht, len, linewidth ) \
                    M_ifprint( stream, (void _VFAR *) (MA0), ht, len, linewidth, 6 )
#define MLI_fprint( stream, MA, ht, len, linewidth ) \
                    MLIfprint( stream, (MA)[0], ht, len, linewidth )
void  __vf M_icprint( void _VFAR *X, ui ht, ui len, unsigned vers );
#define MLIcprint( MA0, ht, len ) M_icprint( (void _VFAR *) (MA0), ht, len, 6 )
#define MLI_cprint( MA, ht, len ) MLIcprint( (MA)[0], ht, len )
#define MLIprint( MA0, ht, len )  M_ifprint( stdout, (void _VFAR *) (MA0), ht, len, 80, 6 )
#define MLI_print( MA, ht, len )  MLIprint( (MA)[0], ht, len )
  /*  MLI_print, MLI_cprint usable only for console applications! */

void __vf MLIwrite( FILE _VFAR *stream, liPMatrix X, ui ht, ui len  );
void __vf MLIread( liPMatrix X, ui ht, ui len, FILE _VFAR *stream );
#define MLIstore( str, MA, ht, len ) VLI_store( str, MA, (len)*(ht) )
#define MLIrecall( MA, ht, len, str) VLI_recall( MA, (len)*(ht), str)

#ifdef __cplusplus
} // end of extern "C"
#endif
#endif  /*  __MLISTD_H  */
