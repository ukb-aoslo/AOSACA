/*  MBIstd.h

  matrix management functions:
  manipulations on matrices of data type "char"

  Copyright (c) 1996-2017 by OptiCode - Dr. Martin Sander Software Dev.
  All Rights Reserved.
*/

#if !defined( __MBISTD_H )
#define __MBISTD_H
#if !defined( __MATLIB_H )
#include <MatLib.h>
#endif
#if !defined( __VBISTD_H )
#include <VBIstd.h>
#endif
#if !defined( __VBIMATH_H )
#include <VBImath.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif

/*************   Dynamic Generation of Matrices   ************************/

biMatrix __vf  MBI_matrix(  ui ht, ui len );
biMatrix __vf  MBI_matrix0( ui ht, ui len );
#if defined (_MSC_VER) && defined (_DEBUG)
    biMatrix __vf  MBI_matrix_dbg(  ui ht, ui len );
    biMatrix __vf  MBI_matrix0_dbg( ui ht, ui len );
    #if defined (_INC_CRTDBG) && defined (_CRTDBG_MAP_ALLOC) 
	    /* Automatic mapping for memory-leak detection by CRT debugging switched on? */ 
        #define MBI_matrix  MBI_matrix_dbg
        #define MBI_matrix0 MBI_matrix0_dbg
    #endif
#else
    #define MBI_matrix_dbg  MBI_matrix
    #define MBI_matrix0_dbg MBI_matrix0
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

#define MBI_getElement( y, MA, ht, len, m, n ) MBIgetElement( y, (MA)[0], ht, len, m, n )
#define MBI_setElement( MA, ht, len, m, n, C ) MBIsetElement( (MA)[0], ht, len, m, n, C )
#define MBI_Pelement( MA, ht, len, m, n ) MBIPelement( (MA)[0], ht, len, m, n )
                     /* returns a pointer to MA[m][n]. */
#define MBI_element( MA, ht, len, m, n ) (*MBIPelement( (MA)[0], ht, len, m, n ))
                     /* dereferenced pointer */

 /****************  Initialization  ***************************************

    To initialize all elements of a matrix with the same value,
    or to perform arithmetic operations on all elements simultaneously,
    refer to the functions of VectorLib, declared in <VBIstd.h>, <VBImath.h>.
    In order to use the VectorLib functions, utilize the feature that
    the whole matrix occupies one contiguous area in memory: pass the
    address of the first row to the desired vector function, the size
    of the "vector" being ht * len.
    For example, initialize all elements of the matrix MA with 1.0
    (this is *NOT* the identity matrix)  by calling
        VBI_equ1( (MA)[0], ht * len );
*/

#define MBI_equ0( MA, ht, len )            VBI_equ0( (MA)[0], (ht)*(len) )
#define MBI_equ1( MA, len )                MBIequ1( (MA)[0], len ) /* identity matrix */
#define MBI_equm1( MA, len )               MBIequm1( (MA)[0], len ) /* neg. identity matrix */
#define MBI_random( MA, ht, len, seed, Min, Max ) \
                                          VBI_random( (MA)[0], (ht)*(len), seed, Min, Max )
#define MBI_outerprod( MA, X, Y, ht, len ) MBIouterprod( (MA)[0], X, Y, ht, len )
                       /* sizX=ht, sizY=len */
#define MBI_Row_equ0( MA, ht, len, iRow )  MBIRow_equ0( (MA)[0], ht, len, iRow )
#define MBI_Col_equ0( MA, ht, len, iCol )  MBICol_equ0( (MA)[0], ht, len, iCol )
#define MBI_Dia_equ0( MA, len )            MBIDia_equ0( (MA)[0], len )
#define MBI_Row_equC( MA, ht, len, iRow, C ) \
                                        MBIRow_equC( (MA)[0], ht, len, iRow, C )
#define MBI_Col_equC( MA, ht, len, iCol, C ) \
                                        MBICol_equC( (MA)[0], ht, len, iCol, C )
#define MBI_Dia_equC( MA, len, C )       MBIDia_equC( (MA)[0], len, C )

#define MBI_Row_equV( MA, ht, len, iRow, X ) \
                                        MBIRow_equV( (MA)[0], ht, len, iRow, X )
#define MBI_Col_equV( MA, ht, len, iCol, X ) \
                                        MBICol_equV( (MA)[0], ht, len, iCol, X )
#define MBI_Dia_equV( MA, len, X )       MBIDia_equV( (MA)[0], len, X )

#define MBI_Trd_equM( MA, MTrd, len )    MBITrd_equM( (MA)[0], (MTrd)[0], len )
#define MBI_Trd_extract( MTrd, MA, len ) MBITrd_extract( (MTrd)[0], (MA)[0], len )

#define MBI_equM( MB, MA, ht, len )  VBI_equV( (MB)[0], (MA)[0], (ht)*(len) )
#define MBI_neg( MB, MA, ht, len )   VBI_neg( (MB)[0], (MA)[0], (ht)*(len) )

#define MBI_UequL( MA, len ) MBIUequL( (MA)[0], len )
#define MBI_LequU( MA, len ) MBILequU( (MA)[0], len )
         /* copy lower-diagonal elements into upper-diagonal
           (or vice versa) by index-reflection, so as to
           get a symmetric matrix    */

            /* data-type conversions:  */
/************** Data-type interconversions  ****************************/

#define M_BItoUB( MUB, MBI, ht, len ) V_BItoUB( (MUB)[0], (MBI)[0], (ht)*(len) )
#define M_UBtoBI( MBI, MUB, ht, len ) V_UBtoBI( (MBI)[0], (MUB)[0], (ht)*(len) )
#define M_BItoI(  MI,  MBI, ht, len ) V_BItoI(  (MI)[0],  (MBI)[0], (ht)*(len) )
#define M_BItoSI( MSI, MBI, ht, len ) V_BItoSI( (MSI)[0], (MBI)[0], (ht)*(len) )
#define M_BItoLI( MLI, MBI, ht, len ) V_BItoLI( (MLI)[0], (MBI)[0], (ht)*(len) )
#define M_BItoQI( MQI, MBI, ht, len ) V_BItoQI( (MQI)[0], (MBI)[0], (ht)*(len) )
#define M_SItoBI( MBI, MSI, ht, len ) V_SItoBI( (MBI)[0], (MSI)[0], (ht)*(len) )
#define M_ItoBI(  MBI, MI,  ht, len ) V_ItoBI(  (MBI)[0], (MI)[0],  (ht)*(len) )
#define M_LItoBI( MBI, MLI, ht, len ) V_LItoBI( (MBI)[0], (MLI)[0], (ht)*(len) )
#define M_QItoBI( MBI, MQI, ht, len ) V_QItoBI( (MBI)[0], (MQI)[0], (ht)*(len) )
#define M_BItoF(  MF,  MBI, ht, len ) V_BItoF(  (MF)[0],  (MBI)[0], (ht)*(len) )
#define M_BItoD(  MD,  MBI, ht, len ) V_BItoD(  (MD)[0],  (MBI)[0], (ht)*(len) )
#if (defined __BORLANDC__) && !(defined _WIN64)
    #define M_BItoE( ME, MBI, ht, len ) V_BItoE( (ME)[0], (MBI)[0], (ht)*(len) )
#else
    #define M_BItoE M_BItoD
#endif

/********  Extracting a submatrix and copying a submatrix back  *********/

#define MBI_submatrix( MSub, subHt, subLen, \
                      MSrce, srceHt, srceLen, \
                      firstRowInCol, sampInCol, firstColInRow, sampInRow ) \
               MBIsubmatrix(  (MSub)[0], subHt, subLen, \
                             (MSrce)[0], srceHt, srceLen, \
                             firstRowInCol, sampInCol, firstColInRow, sampInRow )

#define MBI_submatrix_equM( MDest, destHt, destLen, \
                           firstRowInCol, sampInCol, firstColInRow, sampInRow, \
                           MSrce, srceHt, srceLen ) \
               MBIsubmatrix_equM(  (MDest)[0], destHt, destLen, \
                             firstRowInCol, sampInCol, firstColInRow, sampInRow, \
                             (MSrce)[0], srceHt, srceLen )

#define MBI_equMblock( MSub, subHt, subLen, \
                      MSrce, srceHt, srceLen, \
                      firstRowInCol, firstColInRow ) \
               MBIequMblock(  (MSub)[0], subHt, subLen, \
                             (MSrce)[0], srceHt, srceLen, \
                             firstRowInCol, firstColInRow )

#define MBI_block_equM( MDest, destHt, destLen, \
                       firstRowInCol, firstColInRow, \
                       MSrce, srceHt, srceLen ) \
               MBIblock_equM( (MDest)[0], destHt, destLen, \
                             firstRowInCol, firstColInRow, \
                             (MSrce)[0], srceHt, srceLen )

#define MBI_equMblockT( MSub, subHt, subLen, \
                      MSrce, srceHt, srceLen, \
                      firstRowInCol, firstColInRow ) \
               MBIequMblockT(  (MSub)[0], subHt, subLen, \
                             (MSrce)[0], srceHt, srceLen, \
                             firstRowInCol, firstColInRow )

#define MBI_block_equMT( MDest, destHt, destLen, \
                       firstRowInCol, firstColInRow, \
                       MSrce, srceHt, srceLen ) \
               MBIblock_equMT( (MDest)[0], destHt, destLen, \
                             firstRowInCol, firstColInRow, \
                             (MSrce)[0], srceHt, srceLen )

/*****   Extracting a single row or a single column or the diagonal  ******
 *       and storing it into a vector                                     */

#define MBI_Row_extract( Y, MA, ht, len, iRow ) \
                                     MBIRow_extract( Y, (MA)[0], ht, len, iRow )
#define MBI_Col_extract( Y, MA, ht, len, iCol ) \
                                     MBICol_extract( Y, (MA)[0], ht, len, iCol )
#define MBI_Dia_extract( Y, MA, len ) MBIDia_extract( Y, (MA)[0], len )


/**************  Deleting or inserting a row or a column   ***************/

#define MBI_Row_delete( MB, MA, htA, lenA, iRow ) \
                           MBIRow_delete( (MB)[0], (MA)[0], htA, lenA, iRow )
#define MBI_Col_delete( MB, MA, htA, lenA, iCol ) \
                           MBICol_delete( (MB)[0], (MA)[0], htA, lenA, iCol )
#define MBI_Row_insert( MB, MA, htB, lenB, iRow, X ) \
                           MBIRow_insert( (MB)[0], (MA)[0], htB, lenB, iRow, X )
#define MBI_Col_insert( MB, MA, htB, lenB, iCol, X ) \
                           MBICol_insert( (MB)[0], (MA)[0], htB, lenB, iCol, X )

/******  One-dimensional vector operations **********************
         performed along all rows or all columns simultaneously,
         or along the diagonal of a square matrix                */

#define MBI_Rows_max( Y, MA, ht, len )     MBIRows_max( Y, (MA)[0], ht, len )
#define MBI_Cols_max( Y, MA, ht, len )     MBICols_max( Y, (MA)[0], ht, len )
#define MBI_Dia_max(  MA, len )            MBIDia_max(  (MA)[0], len )
#define MBI_Rows_min( Y, MA, ht, len )     MBIRows_min( Y, (MA)[0], ht, len )
#define MBI_Cols_min( Y, MA, ht, len )     MBICols_min( Y, (MA)[0], ht, len )
#define MBI_Dia_min(  MA, len )            MBIDia_min(  (MA)[0], len )

#define MBI_Rows_rotate( MA, ht, len, pos) MBIRows_rotate( (MA)[0], ht, len, pos )
#define MBI_Cols_rotate( MA, ht, len, pos) MBICols_rotate( (MA)[0], ht, len, pos )
#define MBI_Rows_rotate_buf( MA, ht, len, pos, MBuf) MBIRows_rotate_buf( (MA)[0], ht, len, pos, (MBuf)[0] )
#define MBI_Cols_rotate_buf( MA, ht, len, pos, MBuf) MBICols_rotate_buf( (MA)[0], ht, len, pos, (MBuf)[0] )
#define MBI_Rows_reflect( MA, ht, len)     MBIRows_reflect( (MA)[0], ht, len )
#define MBI_Cols_reflect( MA, ht, len)     MBICols_reflect( (MA)[0], ht, len )
#define MBI_Rows_rev( MA, ht, len)         MBIRows_rev( (MA)[0], ht, len )
#define MBI_Cols_rev( MA, ht, len)         MBICols_rev( (MA)[0], ht, len )

#define MBI_Rows_distribution( MAbund, Limits, nBins, MX, htX, lenX, mode ) MBIRows_distribution( (MAbund)[0], Limits, nBins, (MX)[0], htX, lenX, mode )
#define MBI_Cols_distribution( MAbund, Limits, nBins, MX, htX, lenX, mode ) MBICols_distribution( (MAbund)[0], Limits, nBins, (MX)[0], htX, lenX, mode )

/********  Operations involving two rows or two colums of one matrix  *****/

#define MBI_Rows_exchange( MA, ht, len, row1, row2 ) \
                             MBIRows_exchange( (MA)[0], ht, len, row1, row2 )
#define MBI_Cols_exchange( MA, ht, len, col1, col2 ) \
                             MBICols_exchange( (MA)[0], ht, len, col1, col2 )

/*************  Transposing and rotating a matrix **********************/

#define MBI_transpose( MTr, MA, htTr, lenTr ) \
             MBItranspose( (MTr)[0], (MA)[0], htTr, lenTr )
       /*  dimensions htTr, lenTr are those of the transposed matrix,
           not of the original!                */
#define MBI_rotate90( MRot, MA, htRot, lenRot ) \
             MBIrotate90( (MRot)[0], (MA)[0], htRot, lenRot )
#define MBI_rotate180( MRot, MA, htRot, lenRot ) \
             VBI_rev( (MRot)[0], (MA)[0], (htRot)*(lenRot) )
#define MBI_rotate270( MRot, MA, htRot, lenRot ) \
             MBIrotate270( (MRot)[0], (MA)[0], htRot, lenRot )


/**************************  Input and Output  **************************/

#define MBI_write( str, MA, ht, len )   MBIwrite( str, (MA)[0], ht, len )
#define MBI_read( MA, ht, len, str )    MBIread( (MA)[0], ht, len, str )
#define MBI_setWriteFormat              VBI_setWriteFormat
#define MBI_setWriteSeparate            VBI_setNWriteSeparate
                                   /* write and read in ascii format */
#define MBI_store( str, MA, ht, len )   VBI_store( str, (MA)[0], (len)*(ht) )
#define MBI_recall( MA, ht, len, str)   VBI_recall( (MA)[0], (len)*(ht), str)
                                  /* store and recall in binary format */


/*************************************************************************
 * Here are now the actual declarations of the functions used internally.*
 * These declarations may change in future versions of MatrixLib!        *
 * You should not care too much about them, except in the case you need  *
 * the actual address of a run-time function (see above). Under all      *
 * "normal" circumstances, use only the names defined above in the       *
 * macro section!                                                        *
 *************************************************************************/

void  __vf MBIgetElement( char *y, biPMatrix X, ui ht, ui len, ui m, ui n );
void  __vf MBIsetElement( biPMatrix X, ui ht, ui len, ui m, ui n, char C );
char _VFAR * __vf MBIPelement( biPMatrix X, ui ht, ui len, ui m, ui n );
                  /* pointer is normalized in memory model HUGE */
#define MBIelement( MA, ht, len, m, n ) (*MBIPelement( MA, ht, len, m, n ))

#define MBIequ0( MA, ht, len )            VBI_equ0( MA, (ht)*(len) )
void   __vf  MBIequ1( biPMatrix MA, ui len );  /* identity matrix */
void   __vf  MBIequm1( biPMatrix MA, ui len );  /* neg. identity matrix */
void   __vf  MBIouterprod( biPMatrix MA, biVector X,  biVector Y,
                          ui ht, ui len );

void   __vf  MBIRow_equ0( biPMatrix MA, ui ht, ui len,
                         ui iRow );
void   __vf  MBICol_equ0( biPMatrix MA, ui ht, ui len,
                         ui iCol );
void   __vf  MBIDia_equ0( biPMatrix MA, ui len );

void   __vf  MBIRow_equC( biPMatrix MA, ui ht, ui len,
                         ui iRow, char C );
void   __vf  MBICol_equC( biPMatrix MA, ui ht, ui len,
                         ui iCol, char C );
void   __vf  MBIDia_equC( biPMatrix MA, ui len, char C );

void   __vf  MBIRow_equV( biPMatrix MA, ui ht, ui len,
                         ui iRow, biVector X );
void   __vf  MBICol_equV( biPMatrix MA, ui ht, ui len,
                         ui iCol, biVector X );
void   __vf  MBIDia_equV( biPMatrix MA, ui len, biVector X );

void   __vf  MBITrd_equM( biPMatrix MA, biPMatrix MTrd, ui len );
void   __vf  MBITrd_extract( biPMatrix MTrd, biPMatrix MA, ui len );

#define MBIequM( MB, MA, ht, len )  VBI_equV( MB, MA, (ht)*(len) )
#define MBIneg( MB, MA, ht, len )   VBI_neg( MB, MA, (ht)*(len) )
void   __vf  MBIUequL( biPMatrix MA, ui len );
void   __vf  MBILequU( biPMatrix MA, ui len );

/********  Extracting a submatrix and copying a submatrix back  *********/

void  __vf  MBIsubmatrix( biPMatrix MSub,
                          ui subHt,  ui subLen,
                          biPMatrix MSrce,
                          ui srceHt,  ui srceLen,
                          ui firstRowInCol,  ui sampInCol,
                          ui firstColInRow,  ui sampInRow );

void  __vf  MBIsubmatrix_equM( biPMatrix MDest,
                               ui destHt,     ui destLen,
                               ui firstRowInCol,  ui sampInCol,
                               ui firstColInRow,  ui sampInRow,
                               biPMatrix MSrce,
                               ui srceHt,     ui srceLen );

void  __vf  MBIequMblock(  biPMatrix MSub,
                          ui subHt,  ui subLen,
                          biPMatrix MSrce,
                          ui srceHt,  ui srceLen,
                          ui firstRowInCol,  ui firstColInRow );

void  __vf  MBIblock_equM( biPMatrix MDest,
                          ui destHt,     ui destLen,
                          ui firstRowInCol,  ui firstColInRow,
                          biPMatrix MSrce,
                          ui srceHt,     ui srceLen );

void  __vf  MBIequMblockT( biPMatrix MSub,
                          ui subHt,  ui subLen,
                          biPMatrix MSrce,
                          ui srceHt,  ui srceLen,
                          ui firstRowInCol,  ui firstColInRow );

void  __vf  MBIblock_equMT( biPMatrix MDest,
                          ui destHt,     ui destLen,
                          ui firstRowInCol,  ui firstColInRow,
                          biPMatrix MSrce,
                          ui srceHt,     ui srceLen );


/*****   Extracting a single row or a single column or the diagonal  *****
 *       and storing it into a vector                                    */

void __vf MBIRow_extract( biVector Y, biPMatrix MA, ui ht, ui len,
                           ui iRow );
void __vf MBICol_extract( biVector Y, biPMatrix MA, ui ht, ui len,
                           ui iCol );
void __vf MBIDia_extract( biVector Y, biPMatrix MA, ui len );


/**********  Deleting or inserting a row or a column *****************/

void __vf MBIRow_delete( biPMatrix MB, biPMatrix MA,
                        ui htA, ui lenA, ui iRow );
void __vf MBICol_delete( biPMatrix MB, biPMatrix MA,
                        ui htA, ui lenA, ui iCol );
void __vf MBIRow_insert( biPMatrix MB, biPMatrix MA, ui htB,
                        ui lenB, ui iRow, biVector X );
void __vf MBICol_insert( biPMatrix MB, biPMatrix MA, ui htB,
                        ui lenB, ui iCol, biVector X );


/******  One-dimensional vector operations **********************
         performed along all rows or all columns simultaneously,
         or along the diagonal of a square matrix                */

void  __vf  MBIRows_max( biVector Y, biPMatrix MA, ui ht, ui len );
void  __vf  MBICols_max( biVector Y, biPMatrix MA, ui ht, ui len );
char __vf  MBIDia_max(  biPMatrix MA, ui len );
void  __vf  MBIRows_min( biVector Y, biPMatrix MA, ui ht, ui len );
void  __vf  MBICols_min( biVector Y, biPMatrix MA, ui ht, ui len );
char __vf  MBIDia_min(  biPMatrix MA, ui len );

void  __vf  MBIRows_rotate( biPMatrix MA, ui ht, ui len, ssize_t pos );
void  __vf  MBICols_rotate( biPMatrix MA, ui ht, ui len, ssize_t pos );
void  __vf  MBIRows_rotate_buf( biPMatrix MA, ui ht, ui len, ssize_t pos, biPMatrix MBuf );
void  __vf  MBICols_rotate_buf( biPMatrix MA, ui ht, ui len, ssize_t pos, biPMatrix MBuf );
void  __vf  MBIRows_reflect( biPMatrix MA, ui ht, ui len );
void  __vf  MBICols_reflect( biPMatrix MA, ui ht, ui len );
void  __vf  MBIRows_rev( biPMatrix MA, ui ht, ui len );
void  __vf  MBICols_rev( biPMatrix MA, ui ht, ui len );

void  __vf  MBIRows_distribution( uiPMatrix MAbund, biVector Limits, ui nBins, biPMatrix MX, ui ht, ui len, int mode );
void  __vf  MBICols_distribution( uiPMatrix MAbund, biVector Limits, ui nBins, biPMatrix MX, ui ht, ui len, int mode );

/********  Operations involving two rows or two colums of one matrix  *****/

void   __vf  MBIRows_exchange( biPMatrix MA, ui ht, ui len,
                              ui i1, ui i2 );
void   __vf  MBICols_exchange( biPMatrix MA, ui ht, ui len,
                              ui i1, ui i2 );

/*****************  Transposing and rotating a matrix **********************/

void  __vf  MBItranspose( biPMatrix MTr, biPMatrix MA,
                          ui htTr, ui lenTr );
void  __vf  MBIrotate90(  biPMatrix MRot, biPMatrix MA, ui htRot, ui lenRot );
#define     MBIrotate180( MRot, MA, htRot, lenRot ) \
                VBI_rev( MRot, MA, (htRot)*(lenRot) )
void  __vf  MBIrotate270( biPMatrix MRot, biPMatrix MA, ui htRot, ui lenRot );

      /*************  Input and Output  ****************/

void  __vf M_ifprint( FILE _VFAR *stream, void _VFAR *X, ui ht, ui len, unsigned linewidth, unsigned vers );
#define MBIfprint( stream, MA0, ht, len, linewidth ) \
                    M_ifprint( stream, (void _VFAR *) (MA0), ht, len, linewidth, 0 )
#define MBI_fprint( stream, MA, ht, len, linewidth ) \
                    MBIfprint( stream, (MA)[0], ht, len, linewidth )
void  __vf M_icprint( void _VFAR *X, ui ht, ui len, unsigned vers );
#define MBIcprint( MA0, ht, len ) M_icprint( (void _VFAR *) (MA0), ht, len, 0 )
#define MBI_cprint( MA, ht, len ) MBIcprint( (MA)[0], ht, len )
#define MBIprint( MA0, ht, len )  M_ifprint( stdout, (void _VFAR *) (MA0), ht, len, 80, 0 )
#define MBI_print( MA, ht, len )  MBIprint( (MA)[0], ht, len )
  /*  MBI_print, MBI_cprint usable only for console applications! */

void __vf MBIwrite( FILE _VFAR *stream, biPMatrix X, ui ht, ui len  );
void __vf MBIread( biPMatrix X, ui ht, ui len, FILE _VFAR *stream );
#define MBIstore( str, MA, ht, len ) VBI_store( str, MA, (len)*(ht) )
#define MBIrecall( MA, ht, len, str) VBI_recall( MA, (len)*(ht), str)

#ifdef __cplusplus
} // end of extern "C"
#endif
#endif  /*  __MBISTD_H  */
