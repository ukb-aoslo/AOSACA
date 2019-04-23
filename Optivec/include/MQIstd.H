/*  MQIstd.h

  matrix management functions:
  manipulations on matrices of data type "quad"

  Copyright (c) 1996-2017 by OptiCode - Dr. Martin Sander Software Dev.
  All Rights Reserved.
*/

#if !defined( __MQISTD_H )
#define __MQISTD_H
#if !defined( __MATLIB_H )
#include <MatLib.h>
#endif
#if !defined( __VQISTD_H )
#include <VQIstd.h>
#endif
#if !defined( __VQIMATH_H )
#include <VQImath.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif

/*************   Dynamic Generation of Matrices   ************************/

qiMatrix __vf  MQI_matrix(  ui ht, ui len );
qiMatrix __vf  MQI_matrix0( ui ht, ui len );
#if defined (_MSC_VER) && defined (_DEBUG)
    qiMatrix __vf  MQI_matrix_dbg(  ui ht, ui len );
    qiMatrix __vf  MQI_matrix0_dbg( ui ht, ui len );
    #if defined (_INC_CRTDBG) && defined (_CRTDBG_MAP_ALLOC) 
	    /* Automatic mapping for memory-leak detection by CRT debugging switched on? */ 
        #define MQI_matrix  MQI_matrix_dbg
        #define MQI_matrix0 MQI_matrix0_dbg
    #endif
#else
    #define MQI_matrix_dbg  MQI_matrix
    #define MQI_matrix0_dbg MQI_matrix0
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

#define MQI_getElement( y, MA, ht, len, m, n ) MQIgetElement( y, (MA)[0], ht, len, m, n )
#define MQI_setElement( MA, ht, len, m, n, C ) MQIsetElement( (MA)[0], ht, len, m, n, C )
#define MQI_Pelement( MA, ht, len, m, n ) MQIPelement( (MA)[0], ht, len, m, n )
                     /* returns a pointer to MA[m][n]. */
#define MQI_element( MA, ht, len, m, n ) (*MQIPelement( (MA)[0], ht, len, m, n ))
                     /* dereferenced pointer */

 /****************  Initialization  ***************************************

    To initialize all elements of a matrix with the same value,
    or to perform arithmetic operations on all elements simultaneously,
    refer to the functions of VectorLib, declared in <VQIstd.h>, <VQImath.h>.
    In order to use the VectorLib functions, utilize the feature that
    the whole matrix occupies one contiguous area in memory: pass the
    address of the first row to the desired vector function, the size
    of the "vector" being ht * len.
    For example, initialize all elements of the matrix MA with 1.0
    (this is *NOT* the identity matrix)  by calling
        VQI_equ1( (MA)[0], ht * len );
*/

#define MQI_equ0( MA, ht, len )            VQI_equ0( (MA)[0], (ht)*(len) )
#define MQI_equ1( MA, len )                MQIequ1( (MA)[0], len ) /* identity matrix */
#define MQI_equm1( MA, len )               MQIequm1( (MA)[0], len ) /* neg. identity matrix */
#define MQI_random( MA, ht, len, seed, Min, Max ) \
                                          VQI_random( (MA)[0], (ht)*(len), seed, Min, Max )
#define MQI_outerprod( MA, X, Y, ht, len ) MQIouterprod( (MA)[0], X, Y, ht, len )
                       /* sizX=ht, sizY=len */
#define MQI_Row_equ0( MA, ht, len, iRow )  MQIRow_equ0( (MA)[0], ht, len, iRow )
#define MQI_Col_equ0( MA, ht, len, iCol )  MQICol_equ0( (MA)[0], ht, len, iCol )
#define MQI_Dia_equ0( MA, len )            MQIDia_equ0( (MA)[0], len )
#define MQI_Row_equC( MA, ht, len, iRow, C ) \
                                        MQIRow_equC( (MA)[0], ht, len, iRow, C )
#define MQI_Col_equC( MA, ht, len, iCol, C ) \
                                        MQICol_equC( (MA)[0], ht, len, iCol, C )
#define MQI_Dia_equC( MA, len, C )       MQIDia_equC( (MA)[0], len, C )

#define MQI_Row_equV( MA, ht, len, iRow, X ) \
                                        MQIRow_equV( (MA)[0], ht, len, iRow, X )
#define MQI_Col_equV( MA, ht, len, iCol, X ) \
                                        MQICol_equV( (MA)[0], ht, len, iCol, X )
#define MQI_Dia_equV( MA, len, X )       MQIDia_equV( (MA)[0], len, X )

#define MQI_Trd_equM( MA, MTrd, len )    MQITrd_equM( (MA)[0], (MTrd)[0], len )
#define MQI_Trd_extract( MTrd, MA, len ) MQITrd_extract( (MTrd)[0], (MA)[0], len )

#define MQI_equM( MB, MA, ht, len )  VQI_equV( (MB)[0], (MA)[0], (ht)*(len) )
#define MQI_neg( MB, MA, ht, len )   VQI_neg( (MB)[0], (MA)[0], (ht)*(len) )

#define MQI_UequL( MA, len ) MQIUequL( (MA)[0], len )
#define MQI_LequU( MA, len ) MQILequU( (MA)[0], len )
         /* copy lower-diagonal elements into upper-diagonal
           (or vice versa) by index-reflection, so as to
           get a symmetric matrix    */

            /* data-type conversions:  */
/************** Data-type interconversions  ****************************/

#define M_QItoBI( MBI, MQI, ht, len ) V_QItoBI( (MBI)[0], (MQI)[0], (ht)*(len) )
#define M_QItoSI( MSI, MQI, ht, len ) V_QItoSI( (MSI)[0], (MQI)[0], (ht)*(len) )
#define M_QItoI(  MI,  MQI, ht, len ) V_QItoI(  (MI)[0],  (MQI)[0], (ht)*(len) )
#define M_QItoLI( MLI, MQI, ht, len ) V_QItoLI( (MLI)[0], (MQI)[0], (ht)*(len) )
#define M_BItoQI( MQI, MBI, ht, len ) V_BItoQI( (MQI)[0], (MBI)[0], (ht)*(len) )
#define M_SItoQI( MQI, MSI, ht, len ) V_SItoQI( (MQI)[0], (MSI)[0], (ht)*(len) )
#define M_ItoQI(  MQI, MI,  ht, len ) V_ItoQI(  (MQI)[0], (MI)[0],  (ht)*(len) )
#define M_LItoQI( MQI, MLI, ht, len ) V_LItoQI( (MQI)[0], (MLI)[0], (ht)*(len) )
#define M_QItoF(  MF,  MQI, ht, len ) V_QItoF(  (MF)[0],  (MQI)[0], (ht)*(len) )
#define M_QItoD(  MD,  MQI, ht, len ) V_QItoD(  (MD)[0],  (MQI)[0], (ht)*(len) )
#if (defined __BORLANDC__) && !(defined _WIN64)
    #define M_QItoE( ME, MQI, ht, len ) V_QItoE( (ME)[0], (MQI)[0], (ht)*(len) )
#else
    #define M_QItoE M_QItoD
#endif

/********  Extracting a submatrix and copying a submatrix back  *********/

#define MQI_submatrix( MSub, subHt, subLen, \
                      MSrce, srceHt, srceLen, \
                      firstRowInCol, sampInCol, firstColInRow, sampInRow ) \
               MQIsubmatrix(  (MSub)[0], subHt, subLen, \
                             (MSrce)[0], srceHt, srceLen, \
                             firstRowInCol, sampInCol, firstColInRow, sampInRow )

#define MQI_submatrix_equM( MDest, destHt, destLen, \
                           firstRowInCol, sampInCol, firstColInRow, sampInRow, \
                           MSrce, srceHt, srceLen ) \
               MQIsubmatrix_equM(  (MDest)[0], destHt, destLen, \
                             firstRowInCol, sampInCol, firstColInRow, sampInRow, \
                             (MSrce)[0], srceHt, srceLen )

#define MQI_equMblock( MSub, subHt, subLen, \
                      MSrce, srceHt, srceLen, \
                      firstRowInCol, firstColInRow ) \
               MQIequMblock(  (MSub)[0], subHt, subLen, \
                             (MSrce)[0], srceHt, srceLen, \
                             firstRowInCol, firstColInRow )

#define MQI_block_equM( MDest, destHt, destLen, \
                       firstRowInCol, firstColInRow, \
                       MSrce, srceHt, srceLen ) \
               MQIblock_equM( (MDest)[0], destHt, destLen, \
                             firstRowInCol, firstColInRow, \
                             (MSrce)[0], srceHt, srceLen )

#define MQI_equMblockT( MSub, subHt, subLen, \
                      MSrce, srceHt, srceLen, \
                      firstRowInCol, firstColInRow ) \
               MQIequMblockT(  (MSub)[0], subHt, subLen, \
                             (MSrce)[0], srceHt, srceLen, \
                             firstRowInCol, firstColInRow )

#define MQI_block_equMT( MDest, destHt, destLen, \
                       firstRowInCol, firstColInRow, \
                       MSrce, srceHt, srceLen ) \
               MQIblock_equMT( (MDest)[0], destHt, destLen, \
                             firstRowInCol, firstColInRow, \
                             (MSrce)[0], srceHt, srceLen )

/*****   Extracting a single row or a single column or the diagonal  ******
 *       and storing it into a vector                                     */

#define MQI_Row_extract( Y, MA, ht, len, iRow ) \
                                     MQIRow_extract( Y, (MA)[0], ht, len, iRow )
#define MQI_Col_extract( Y, MA, ht, len, iCol ) \
                                     MQICol_extract( Y, (MA)[0], ht, len, iCol )
#define MQI_Dia_extract( Y, MA, len ) MQIDia_extract( Y, (MA)[0], len )


/**************  Deleting or inserting a row or a column   ***************/

#define MQI_Row_delete( MB, MA, htA, lenA, iRow ) \
                           MQIRow_delete( (MB)[0], (MA)[0], htA, lenA, iRow )
#define MQI_Col_delete( MB, MA, htA, lenA, iCol ) \
                           MQICol_delete( (MB)[0], (MA)[0], htA, lenA, iCol )
#define MQI_Row_insert( MB, MA, htB, lenB, iRow, X ) \
                           MQIRow_insert( (MB)[0], (MA)[0], htB, lenB, iRow, X )
#define MQI_Col_insert( MB, MA, htB, lenB, iCol, X ) \
                           MQICol_insert( (MB)[0], (MA)[0], htB, lenB, iCol, X )

/******  One-dimensional vector operations **********************
         performed along all rows or all columns simultaneously,
         or along the diagonal of a square matrix                */

#define MQI_Rows_max( Y, MA, ht, len )     MQIRows_max( Y, (MA)[0], ht, len )
#define MQI_Cols_max( Y, MA, ht, len )     MQICols_max( Y, (MA)[0], ht, len )
#define MQI_Dia_max(  MA, len )            MQIDia_max(  (MA)[0], len )
#define MQI_Rows_min( Y, MA, ht, len )     MQIRows_min( Y, (MA)[0], ht, len )
#define MQI_Cols_min( Y, MA, ht, len )     MQICols_min( Y, (MA)[0], ht, len )
#define MQI_Dia_min(  MA, len )            MQIDia_min(  (MA)[0], len )

#define MQI_Rows_rotate( MA, ht, len, pos) MQIRows_rotate( (MA)[0], ht, len, pos )
#define MQI_Cols_rotate( MA, ht, len, pos) MQICols_rotate( (MA)[0], ht, len, pos )
#define MQI_Rows_rotate_buf( MA, ht, len, pos, MBuf) MQIRows_rotate_buf( (MA)[0], ht, len, pos, (MBuf)[0] )
#define MQI_Cols_rotate_buf( MA, ht, len, pos, MBuf) MQICols_rotate_buf( (MA)[0], ht, len, pos, (MBuf)[0] )
#define MQI_Rows_reflect( MA, ht, len)     MQIRows_reflect( (MA)[0], ht, len )
#define MQI_Cols_reflect( MA, ht, len)     MQICols_reflect( (MA)[0], ht, len )
#define MQI_Rows_rev( MA, ht, len)         MQIRows_rev( (MA)[0], ht, len )
#define MQI_Cols_rev( MA, ht, len)         MQICols_rev( (MA)[0], ht, len )

#define MQI_Rows_distribution( MAbund, Limits, nBins, MX, htX, lenX, mode ) MQIRows_distribution( (MAbund)[0], Limits, nBins, (MX)[0], htX, lenX, mode )
#define MQI_Cols_distribution( MAbund, Limits, nBins, MX, htX, lenX, mode ) MQICols_distribution( (MAbund)[0], Limits, nBins, (MX)[0], htX, lenX, mode )

/********  Operations involving two rows or two colums of one matrix  *****/

#define MQI_Rows_exchange( MA, ht, len, row1, row2 ) \
                             MQIRows_exchange( (MA)[0], ht, len, row1, row2 )
#define MQI_Cols_exchange( MA, ht, len, col1, col2 ) \
                             MQICols_exchange( (MA)[0], ht, len, col1, col2 )

/***********  Transposing and rotating a matrix **********************/

#define MQI_transpose( MTr, MA, htTr, lenTr ) \
             MQItranspose( (MTr)[0], (MA)[0], htTr, lenTr )
       /*  dimensions htTr, lenTr are those of the transposed matrix,
           not of the original!                */
#define MQI_rotate90( MRot, MA, htRot, lenRot ) \
             MQIrotate90( (MRot)[0], (MA)[0], htRot, lenRot )
#define MQI_rotate180( MRot, MA, htRot, lenRot ) \
             VQI_rev( (MRot)[0], (MA)[0], (htRot)*(lenRot) )
#define MQI_rotate270( MRot, MA, htRot, lenRot ) \
             MQIrotate270( (MRot)[0], (MA)[0], htRot, lenRot )

/**************************  Input and Output  **************************/

void  __vf M_ifprint( FILE _VFAR *stream, void _VFAR *X, ui ht, ui len, unsigned linewidth, unsigned vers );
#define MQI_fprint( stream, MA, ht, len, linewidth ) \
                    MQIfprint( stream, (MA)[0], ht, len, linewidth )
#define MQI_print( MA, ht, len )  MQIfprint( stdout, (MA)[0], ht, len, 80 )
#define MQI_cprint( MA, ht, len ) MQIcprint( (MA)[0], ht, len )
  /*  MQI_print, MQI_cprint usable only for console applications! */
#define MQI_write( str, MA, ht, len )   MQIwrite( str, (MA)[0], ht, len )
#define MQI_read( MA, ht, len, str )    MQIread( (MA)[0], ht, len, str )
#define MQI_setWriteFormat              VQI_setWriteFormat
#define MQI_setWriteSeparate            VQI_setNWriteSeparate
                                   /* write and read in ascii format */
#define MQI_store( str, MA, ht, len )   VQI_store( str, (MA)[0], (len)*(ht) )
#define MQI_recall( MA, ht, len, str)   VQI_recall( (MA)[0], (len)*(ht), str)
                                  /* store and recall in binary format */


/*************************************************************************
 * Here are now the actual declarations of the functions used internally.*
 * These declarations may change in future versions of MatrixLib!        *
 * You should not care too much about them, except in the case you need  *
 * the actual address of a run-time function (see above). Under all      *
 * "normal" circumstances, use only the names defined above in the       *
 * macro section!                                                        *
 *************************************************************************/

void  __vf MQIgetElement( quad *y, qiPMatrix X, ui ht, ui len, ui m, ui n );
void  __vf MQIsetElement( qiPMatrix X, ui ht, ui len, ui m, ui n, quad C );
quad _VFAR * __vf MQIPelement( qiPMatrix X, ui ht, ui len, ui m, ui n );
                  /* pointer is normalized in memory model HUGE */
#define MQIelement( MA, ht, len, m, n ) (*MQIPelement( MA, ht, len, m, n ))

#define MQIequ0( MA, ht, len )            VQI_equ0( MA, (ht)*(len) )
void   __vf  MQIequ1( qiPMatrix MA, ui len );  /* identity matrix */
void   __vf  MQIequm1( qiPMatrix MA, ui len );  /* neg. identity matrix */
void   __vf  MQIouterprod( qiPMatrix MA, qiVector X,  qiVector Y,
                          ui ht, ui len );

void   __vf  MQIRow_equ0( qiPMatrix MA, ui ht, ui len,
                         ui iRow );
void   __vf  MQICol_equ0( qiPMatrix MA, ui ht, ui len,
                         ui iCol );
void   __vf  MQIDia_equ0( qiPMatrix MA, ui len );

void   __vf  MQIRow_equC( qiPMatrix MA, ui ht, ui len,
                         ui iRow, quad C );
void   __vf  MQICol_equC( qiPMatrix MA, ui ht, ui len,
                         ui iCol, quad C );
void   __vf  MQIDia_equC( qiPMatrix MA, ui len, quad C );

void   __vf  MQIRow_equV( qiPMatrix MA, ui ht, ui len,
                         ui iRow, qiVector X );
void   __vf  MQICol_equV( qiPMatrix MA, ui ht, ui len,
                         ui iCol, qiVector X );
void   __vf  MQIDia_equV( qiPMatrix MA, ui len, qiVector X );

void   __vf  MQITrd_equM( qiPMatrix MA, qiPMatrix MTrd, ui len );
void   __vf  MQITrd_extract( qiPMatrix MTrd, qiPMatrix MA, ui len );

#define MQIequM( MB, MA, ht, len )  VQI_equV( MB, MA, (ht)*(len) )
#define MQIneg( MB, MA, ht, len )   VQI_neg( MB, MA, (ht)*(len) )
void   __vf  MQIUequL( qiPMatrix MA, ui len );
void   __vf  MQILequU( qiPMatrix MA, ui len );

/********  Extracting a submatrix and copying a submatrix back  *********/

void  __vf  MQIsubmatrix( qiPMatrix MSub,
                          ui subHt,  ui subLen,
                          qiPMatrix MSrce,
                          ui srceHt,  ui srceLen,
                          ui firstRowInCol,  ui sampInCol,
                          ui firstColInRow,  ui sampInRow );

void  __vf  MQIsubmatrix_equM( qiPMatrix MDest,
                               ui destHt,     ui destLen,
                               ui firstRowInCol,  ui sampInCol,
                               ui firstColInRow,  ui sampInRow,
                               qiPMatrix MSrce,
                               ui srceHt,     ui srceLen );

void  __vf  MQIequMblock(  qiPMatrix MSub,
                          ui subHt,  ui subLen,
                          qiPMatrix MSrce,
                          ui srceHt,  ui srceLen,
                          ui firstRowInCol,  ui firstColInRow );

void  __vf  MQIblock_equM( qiPMatrix MDest,
                          ui destHt,     ui destLen,
                          ui firstRowInCol,  ui firstColInRow,
                          qiPMatrix MSrce,
                          ui srceHt,     ui srceLen );

void  __vf  MQIequMblockT( qiPMatrix MSub,
                          ui subHt,  ui subLen,
                          qiPMatrix MSrce,
                          ui srceHt,  ui srceLen,
                          ui firstRowInCol,  ui firstColInRow );

void  __vf  MQIblock_equMT( qiPMatrix MDest,
                          ui destHt,     ui destLen,
                          ui firstRowInCol,  ui firstColInRow,
                          qiPMatrix MSrce,
                          ui srceHt,     ui srceLen );


/*****   Extracting a single row or a single column or the diagonal  *****
 *       and storing it into a vector                                    */

void __vf MQIRow_extract( qiVector Y, qiPMatrix MA, ui ht, ui len,
                           ui iRow );
void __vf MQICol_extract( qiVector Y, qiPMatrix MA, ui ht, ui len,
                           ui iCol );
void __vf MQIDia_extract( qiVector Y, qiPMatrix MA, ui len );


/**********  Deleting or inserting a row or a column *****************/

void __vf MQIRow_delete( qiPMatrix MB, qiPMatrix MA,
                        ui htA, ui lenA, ui iRow );
void __vf MQICol_delete( qiPMatrix MB, qiPMatrix MA,
                        ui htA, ui lenA, ui iCol );
void __vf MQIRow_insert( qiPMatrix MB, qiPMatrix MA, ui htB,
                        ui lenB, ui iRow, qiVector X );
void __vf MQICol_insert( qiPMatrix MB, qiPMatrix MA, ui htB,
                        ui lenB, ui iCol, qiVector X );


/******  One-dimensional vector operations **********************
         performed along all rows or all columns simultaneously,
         or along the diagonal of a square matrix                */

void  __vf  MQIRows_max( qiVector Y, qiPMatrix MA, ui ht, ui len );
void  __vf  MQICols_max( qiVector Y, qiPMatrix MA, ui ht, ui len );
void  __vf  MQIRows_min( qiVector Y, qiPMatrix MA, ui ht, ui len );
void  __vf  MQICols_min( qiVector Y, qiPMatrix MA, ui ht, ui len );

#if !((defined __BORLANDC__) && (__BORLANDC__ < 0x570))
	quad  __vf  MQIDia_max(  qiPMatrix MA, ui len );
	quad  __vf  MQIDia_min(  qiPMatrix MA, ui len );
#else  /* old BC versions need separate implementation */
	quad  __vf  MQIDia_max1(  qiPMatrix MA, ui len );
	quad  __vf  MQIDia_min1(  qiPMatrix MA, ui len );
	#define MQIDia_max MQIDia_max1
	#define MQIDia_min MQIDia_min1
#endif
void  __vf  MQIRows_rotate( qiPMatrix MA, ui ht, ui len, ssize_t pos );
void  __vf  MQICols_rotate( qiPMatrix MA, ui ht, ui len, ssize_t pos );
void  __vf  MQIRows_rotate_buf( qiPMatrix MA, ui ht, ui len, ssize_t pos, qiPMatrix MBuf );
void  __vf  MQICols_rotate_buf( qiPMatrix MA, ui ht, ui len, ssize_t pos, qiPMatrix MBuf );
void  __vf  MQIRows_reflect( qiPMatrix MA, ui ht, ui len );
void  __vf  MQICols_reflect( qiPMatrix MA, ui ht, ui len );
void  __vf  MQIRows_rev( qiPMatrix MA, ui ht, ui len );
void  __vf  MQICols_rev( qiPMatrix MA, ui ht, ui len );

void  __vf  MQIRows_distribution( uiPMatrix MAbund, qiVector Limits, ui nBins, qiPMatrix MX, ui ht, ui len, int mode );
void  __vf  MQICols_distribution( uiPMatrix MAbund, qiVector Limits, ui nBins, qiPMatrix MX, ui ht, ui len, int mode );

/********  Operations involving two rows or two colums of one matrix  *****/

void   __vf  MQIRows_exchange( qiPMatrix MA, ui ht, ui len,
                              ui i1, ui i2 );
void   __vf  MQICols_exchange( qiPMatrix MA, ui ht, ui len,
                              ui i1, ui i2 );

/***************  Transposing and rotating a matrix **********************/

void  __vf  MQItranspose( qiPMatrix MTr, qiPMatrix MA,
                          ui htTr, ui lenTr );
void  __vf  MQIrotate90(  qiPMatrix MRot, qiPMatrix MA, ui htRot, ui lenRot );
#define     MQIrotate180( MRot, MA, htRot, lenRot ) \
                VQI_rev( MRot, MA, (htRot)*(lenRot) )
void  __vf  MQIrotate270( qiPMatrix MRot, qiPMatrix MA, ui htRot, ui lenRot );

      /*************  Input and Output  ****************/

#if !(((defined __BORLANDC__) && (__BORLANDC__ < 0x570)) || ((defined _MSC_VER) && (_MSC_VER < 1400)))
		/* modern compiler versions:  */
	#define MQIfprint( stream, MA0, ht, len, linewidth ) \
                    M_ifprint( stream, (void _VFAR *) (MA0), ht, len, linewidth, 8 )
	#define MQIcprint( MA0, ht, len ) \
	                M_icprint( (void _VFAR *) (MA0), ht, len, 8 )
	void __vf MQIwrite( FILE _VFAR *stream, qiPMatrix X, ui ht, ui len  );
#else /* older compiler versions need separate implementation */
	void __vf MQIfprint1( FILE _VFAR *stream, qiPMatrix MA, ui ht,  ui len, unsigned linewidth );
	#define MQIfprint MQIfprint1
    void __vf MQIcprint1( qiPMatrix MA, ui ht, ui len );
	#define MQIcprint MQIcprint1
	void __vf MQIwrite1( FILE _VFAR *stream, qiPMatrix X, ui ht, ui len  );
	#define MQIwrite MQIwrite1
#endif
#if !(((defined __BORLANDC__) && (__BORLANDC__ < 0x600)))
	void __vf MQIread( qiPMatrix X, ui ht, ui len, FILE _VFAR *stream );
#else
	void __vf MQIread1( qiPMatrix X, ui ht, ui len, FILE _VFAR *stream );
	#define MQIread MQIread1
#endif
#define MQIstore( str, MA, ht, len ) VQI_store( str, MA, (len)*(ht) )
#define MQIrecall( MA, ht, len, str) VQI_recall( MA, (len)*(ht), str)

#ifdef __cplusplus
} // end of extern "C"
#endif
#endif  /*  __MQISTD_H  */
