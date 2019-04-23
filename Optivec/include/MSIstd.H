/*  MSIstd.h

  matrix management functions:
  manipulations on matrices of data type "short"

  Copyright (c) 1996-2017 by OptiCode - Dr. Martin Sander Software Dev.
  All Rights Reserved.
*/

#if !defined( __MSISTD_H )
#define __MSISTD_H
#if !defined( __MATLIB_H )
#include <MatLib.h>
#endif
#if !defined( __VSISTD_H )
#include <VSIstd.h>
#endif
#if !defined( __VSIMATH_H )
#include <VSImath.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif

/*************   Dynamic Generation of Matrices   ************************/

siMatrix __vf  MSI_matrix(  ui ht, ui len );
siMatrix __vf  MSI_matrix0( ui ht, ui len );
#if defined (_MSC_VER) && defined (_DEBUG)
    siMatrix __vf  MSI_matrix_dbg(  ui ht, ui len );
    siMatrix __vf  MSI_matrix0_dbg( ui ht, ui len );
    #if defined (_INC_CRTDBG) && defined (_CRTDBG_MAP_ALLOC) 
	    /* Automatic mapping for memory-leak detection by CRT debugging switched on? */ 
        #define MSI_matrix  MSI_matrix_dbg
        #define MSI_matrix0 MSI_matrix0_dbg
    #endif
#else
    #define MSI_matrix_dbg  MSI_matrix
    #define MSI_matrix0_dbg MSI_matrix0
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

#define MSI_getElement( y, MA, ht, len, m, n ) MSIgetElement( y, (MA)[0], ht, len, m, n )
#define MSI_setElement( MA, ht, len, m, n, C ) MSIsetElement( (MA)[0], ht, len, m, n, C )
#define MSI_Pelement( MA, ht, len, m, n ) MSIPelement( (MA)[0], ht, len, m, n )
                     /* returns a pointer to MA[m][n]. */
#define MSI_element( MA, ht, len, m, n ) (*MSIPelement( (MA)[0], ht, len, m, n ))
                     /* dereferenced pointer */

 /****************  Initialization  ***************************************

    To initialize all elements of a matrix with the same value,
    or to perform arithmetic operations on all elements simultaneously,
    refer to the functions of VectorLib, declared in <VSIstd.h>, <VSImath.h>.
    In order to use the VectorLib functions, utilize the feature that
    the whole matrix occupies one contiguous area in memory: pass the
    address of the first row to the desired vector function, the size
    of the "vector" being ht * len.
    For example, initialize all elements of the matrix MA with 1.0
    (this is *NOT* the identity matrix)  by calling
        VSI_equ1( (MA)[0], ht * len );
*/

#define MSI_equ0( MA, ht, len )            VSI_equ0( (MA)[0], (ht)*(len) )
#define MSI_equ1( MA, len )                MSIequ1( (MA)[0], len ) /* identity matrix */
#define MSI_equm1( MA, len )               MSIequm1( (MA)[0], len ) /* neg. identity matrix */
#define MSI_random( MA, ht, len, seed, Min, Max ) \
                                          VSI_random( (MA)[0], (ht)*(len), seed, Min, Max )
#define MSI_outerprod( MA, X, Y, ht, len ) MSIouterprod( (MA)[0], X, Y, ht, len )
                       /* sizX=ht, sizY=len */
#define MSI_Row_equ0( MA, ht, len, iRow )  MSIRow_equ0( (MA)[0], ht, len, iRow )
#define MSI_Col_equ0( MA, ht, len, iCol )  MSICol_equ0( (MA)[0], ht, len, iCol )
#define MSI_Dia_equ0( MA, len )            MSIDia_equ0( (MA)[0], len )
#define MSI_Row_equC( MA, ht, len, iRow, C ) \
                                        MSIRow_equC( (MA)[0], ht, len, iRow, C )
#define MSI_Col_equC( MA, ht, len, iCol, C ) \
                                        MSICol_equC( (MA)[0], ht, len, iCol, C )
#define MSI_Dia_equC( MA, len, C )       MSIDia_equC( (MA)[0], len, C )

#define MSI_Row_equV( MA, ht, len, iRow, X ) \
                                        MSIRow_equV( (MA)[0], ht, len, iRow, X )
#define MSI_Col_equV( MA, ht, len, iCol, X ) \
                                        MSICol_equV( (MA)[0], ht, len, iCol, X )
#define MSI_Dia_equV( MA, len, X )       MSIDia_equV( (MA)[0], len, X )

#define MSI_Trd_equM( MA, MTrd, len )    MSITrd_equM( (MA)[0], (MTrd)[0], len )
#define MSI_Trd_extract( MTrd, MA, len ) MSITrd_extract( (MTrd)[0], (MA)[0], len )

#define MSI_equM( MB, MA, ht, len )  VSI_equV( (MB)[0], (MA)[0], (ht)*(len) )
#define MSI_neg( MB, MA, ht, len )   VSI_neg( (MB)[0], (MA)[0], (ht)*(len) )

#define MSI_UequL( MA, len ) MSIUequL( (MA)[0], len )
#define MSI_LequU( MA, len ) MSILequU( (MA)[0], len )
         /* copy lower-diagonal elements into upper-diagonal
           (or vice versa) by index-reflection, so as to
           get a symmetric matrix    */

            /* data-type conversions:  */
/************** Data-type interconversions  ****************************/

#define M_SItoUS( MUS, MSI, ht, len ) V_SItoUS( (MUS)[0], (MSI)[0], (ht)*(len) )
#define M_UStoSI( MSI, MUS, ht, len ) V_UStoSI( (MSI)[0], (MUS)[0], (ht)*(len) )
#define M_SItoBI( MBI, MSI, ht, len ) V_SItoBI( (MBI)[0], (MSI)[0], (ht)*(len) )
#define M_SItoI(  MI,  MSI, ht, len ) V_SItoI(  (MI)[0],  (MSI)[0], (ht)*(len) )
#define M_SItoLI( MLI, MSI, ht, len ) V_SItoLI( (MLI)[0], (MSI)[0], (ht)*(len) )
#define M_SItoQI( MQI, MSI, ht, len ) V_SItoQI( (MQI)[0], (MSI)[0], (ht)*(len) )
#define M_BItoSI( MSI, MBI, ht, len ) V_BItoSI( (MSI)[0], (MBI)[0], (ht)*(len) )
#define M_ItoSI(  MSI, MI,  ht, len ) V_ItoSI(  (MSI)[0], (MI)[0],  (ht)*(len) )
#define M_LItoSI( MSI, MLI, ht, len ) V_LItoSI( (MSI)[0], (MLI)[0], (ht)*(len) )
#define M_QItoSI( MSI, MQI, ht, len ) V_QItoSI( (MSI)[0], (MQI)[0], (ht)*(len) )
#define M_SItoF(  MF,  MSI, ht, len ) V_SItoF(  (MF)[0],  (MSI)[0], (ht)*(len) )
#define M_SItoD(  MD,  MSI, ht, len ) V_SItoD(  (MD)[0],  (MSI)[0], (ht)*(len) )
#if (defined __BORLANDC__) && !(defined _WIN64)
    #define M_SItoE( ME, MSI, ht, len ) V_SItoE( (ME)[0], (MSI)[0], (ht)*(len) )
#else
    #define M_SItoE M_SItoD
#endif

/********  Extracting a submatrix and copying a submatrix back  *********/

#define MSI_submatrix( MSub, subHt, subLen, \
                      MSrce, srceHt, srceLen, \
                      firstRowInCol, sampInCol, firstColInRow, sampInRow ) \
               MSIsubmatrix(  (MSub)[0], subHt, subLen, \
                             (MSrce)[0], srceHt, srceLen, \
                             firstRowInCol, sampInCol, firstColInRow, sampInRow )

#define MSI_submatrix_equM( MDest, destHt, destLen, \
                           firstRowInCol, sampInCol, firstColInRow, sampInRow, \
                           MSrce, srceHt, srceLen ) \
               MSIsubmatrix_equM(  (MDest)[0], destHt, destLen, \
                             firstRowInCol, sampInCol, firstColInRow, sampInRow, \
                             (MSrce)[0], srceHt, srceLen )

#define MSI_equMblock( MSub, subHt, subLen, \
                      MSrce, srceHt, srceLen, \
                      firstRowInCol, firstColInRow ) \
               MSIequMblock(  (MSub)[0], subHt, subLen, \
                             (MSrce)[0], srceHt, srceLen, \
                             firstRowInCol, firstColInRow )

#define MSI_block_equM( MDest, destHt, destLen, \
                       firstRowInCol, firstColInRow, \
                       MSrce, srceHt, srceLen ) \
               MSIblock_equM( (MDest)[0], destHt, destLen, \
                             firstRowInCol, firstColInRow, \
                             (MSrce)[0], srceHt, srceLen )

#define MSI_equMblockT( MSub, subHt, subLen, \
                      MSrce, srceHt, srceLen, \
                      firstRowInCol, firstColInRow ) \
               MSIequMblockT(  (MSub)[0], subHt, subLen, \
                             (MSrce)[0], srceHt, srceLen, \
                             firstRowInCol, firstColInRow )

#define MSI_block_equMT( MDest, destHt, destLen, \
                       firstRowInCol, firstColInRow, \
                       MSrce, srceHt, srceLen ) \
               MSIblock_equMT( (MDest)[0], destHt, destLen, \
                             firstRowInCol, firstColInRow, \
                             (MSrce)[0], srceHt, srceLen )

/*****   Extracting a single row or a single column or the diagonal  ******
 *       and storing it into a vector                                     */

#define MSI_Row_extract( Y, MA, ht, len, iRow ) \
                                     MSIRow_extract( Y, (MA)[0], ht, len, iRow )
#define MSI_Col_extract( Y, MA, ht, len, iCol ) \
                                     MSICol_extract( Y, (MA)[0], ht, len, iCol )
#define MSI_Dia_extract( Y, MA, len ) MSIDia_extract( Y, (MA)[0], len )


/**************  Deleting or inserting a row or a column   ***************/

#define MSI_Row_delete( MB, MA, htA, lenA, iRow ) \
                           MSIRow_delete( (MB)[0], (MA)[0], htA, lenA, iRow )
#define MSI_Col_delete( MB, MA, htA, lenA, iCol ) \
                           MSICol_delete( (MB)[0], (MA)[0], htA, lenA, iCol )
#define MSI_Row_insert( MB, MA, htB, lenB, iRow, X ) \
                           MSIRow_insert( (MB)[0], (MA)[0], htB, lenB, iRow, X )
#define MSI_Col_insert( MB, MA, htB, lenB, iCol, X ) \
                           MSICol_insert( (MB)[0], (MA)[0], htB, lenB, iCol, X )

/******  One-dimensional vector operations **********************
         performed along all rows or all columns simultaneously,
         or along the diagonal of a square matrix                */

#define MSI_Rows_max( Y, MA, ht, len )     MSIRows_max( Y, (MA)[0], ht, len )
#define MSI_Cols_max( Y, MA, ht, len )     MSICols_max( Y, (MA)[0], ht, len )
#define MSI_Dia_max(  MA, len )            MSIDia_max(  (MA)[0], len )
#define MSI_Rows_min( Y, MA, ht, len )     MSIRows_min( Y, (MA)[0], ht, len )
#define MSI_Cols_min( Y, MA, ht, len )     MSICols_min( Y, (MA)[0], ht, len )
#define MSI_Dia_min(  MA, len )            MSIDia_min(  (MA)[0], len )

#define MSI_Rows_rotate( MA, ht, len, pos) MSIRows_rotate( (MA)[0], ht, len, pos )
#define MSI_Cols_rotate( MA, ht, len, pos) MSICols_rotate( (MA)[0], ht, len, pos )
#define MSI_Rows_rotate_buf( MA, ht, len, pos, MBuf) MSIRows_rotate_buf( (MA)[0], ht, len, pos, (MBuf)[0] )
#define MSI_Cols_rotate_buf( MA, ht, len, pos, MBuf) MSICols_rotate_buf( (MA)[0], ht, len, pos, (MBuf)[0] )
#define MSI_Rows_reflect( MA, ht, len)     MSIRows_reflect( (MA)[0], ht, len )
#define MSI_Cols_reflect( MA, ht, len)     MSICols_reflect( (MA)[0], ht, len )
#define MSI_Rows_rev( MA, ht, len)         MSIRows_rev( (MA)[0], ht, len )
#define MSI_Cols_rev( MA, ht, len)         MSICols_rev( (MA)[0], ht, len )

#define MSI_Rows_distribution( MAbund, Limits, nBins, MX, htX, lenX, mode ) MSIRows_distribution( (MAbund)[0], Limits, nBins, (MX)[0], htX, lenX, mode )
#define MSI_Cols_distribution( MAbund, Limits, nBins, MX, htX, lenX, mode ) MSICols_distribution( (MAbund)[0], Limits, nBins, (MX)[0], htX, lenX, mode )

/********  Operations involving two rows or two colums of one matrix  *****/

#define MSI_Rows_exchange( MA, ht, len, row1, row2 ) \
                             MSIRows_exchange( (MA)[0], ht, len, row1, row2 )
#define MSI_Cols_exchange( MA, ht, len, col1, col2 ) \
                             MSICols_exchange( (MA)[0], ht, len, col1, col2 )

/****************  Transposing and rotating a matrix **********************/

#define MSI_transpose( MTr, MA, htTr, lenTr ) \
             MSItranspose( (MTr)[0], (MA)[0], htTr, lenTr )
       /*  dimensions htTr, lenTr are those of the transposed matrix,
           not of the original!                */
#define MSI_rotate90( MRot, MA, htRot, lenRot ) \
             MSIrotate90( (MRot)[0], (MA)[0], htRot, lenRot )
#define MSI_rotate180( MRot, MA, htRot, lenRot ) \
             VSI_rev( (MRot)[0], (MA)[0], (htRot)*(lenRot) )
#define MSI_rotate270( MRot, MA, htRot, lenRot ) \
             MSIrotate270( (MRot)[0], (MA)[0], htRot, lenRot )

/**************************  Input and Output  **************************/

#define MSI_write( str, MA, ht, len )   MSIwrite( str, (MA)[0], ht, len )
#define MSI_read( MA, ht, len, str )    MSIread( (MA)[0], ht, len, str )
#define MSI_setWriteFormat              VSI_setWriteFormat
#define MSI_setWriteSeparate            VSI_setNWriteSeparate
                                   /* write and read in ascii format */
#define MSI_store( str, MA, ht, len )   VSI_store( str, (MA)[0], (len)*(ht) )
#define MSI_recall( MA, ht, len, str)   VSI_recall( (MA)[0], (len)*(ht), str)
                                  /* store and recall in binary format */


/*************************************************************************
 * Here are now the actual declarations of the functions used internally.*
 * These declarations may change in future versions of MatrixLib!        *
 * You should not care too much about them, except in the case you need  *
 * the actual address of a run-time function (see above). Under all      *
 * "normal" circumstances, use only the names defined above in the       *
 * macro section!                                                        *
 *************************************************************************/

void  __vf MSIgetElement( short *y, siPMatrix X, ui ht, ui len, ui m, ui n );
void  __vf MSIsetElement( siPMatrix X, ui ht, ui len, ui m, ui n, short C );
short _VFAR * __vf MSIPelement( siPMatrix X, ui ht, ui len, ui m, ui n );
                  /* pointer is normalized in memory model HUGE */
#define MSIelement( MA, ht, len, m, n ) (*MSIPelement( MA, ht, len, m, n ))

#define MSIequ0( MA, ht, len )            VSI_equ0( MA, (ht)*(len) )
void   __vf  MSIequ1( siPMatrix MA, ui len );  /* identity matrix */
void   __vf  MSIequm1( siPMatrix MA, ui len );  /* neg. identity matrix */
void   __vf  MSIouterprod( siPMatrix MA, siVector X,  siVector Y,
                          ui ht, ui len );

void   __vf  MSIRow_equ0( siPMatrix MA, ui ht, ui len,
                         ui iRow );
void   __vf  MSICol_equ0( siPMatrix MA, ui ht, ui len,
                         ui iCol );
void   __vf  MSIDia_equ0( siPMatrix MA, ui len );

void   __vf  MSIRow_equC( siPMatrix MA, ui ht, ui len,
                         ui iRow, short C );
void   __vf  MSICol_equC( siPMatrix MA, ui ht, ui len,
                         ui iCol, short C );
void   __vf  MSIDia_equC( siPMatrix MA, ui len, short C );

void   __vf  MSIRow_equV( siPMatrix MA, ui ht, ui len,
                         ui iRow, siVector X );
void   __vf  MSICol_equV( siPMatrix MA, ui ht, ui len,
                         ui iCol, siVector X );
void   __vf  MSIDia_equV( siPMatrix MA, ui len, siVector X );

void   __vf  MSITrd_equM( siPMatrix MA, siPMatrix MTrd, ui len );
void   __vf  MSITrd_extract( siPMatrix MTrd, siPMatrix MA, ui len );

#define MSIequM( MB, MA, ht, len )  VSI_equV( MB, MA, (ht)*(len) )
#define MSIneg( MB, MA, ht, len )   VSI_neg( MB, MA, (ht)*(len) )
void   __vf  MSIUequL( siPMatrix MA, ui len );
void   __vf  MSILequU( siPMatrix MA, ui len );

/********  Extracting a submatrix and copying a submatrix back  *********/

void  __vf  MSIsubmatrix( siPMatrix MSub,
                          ui subHt,  ui subLen,
                          siPMatrix MSrce,
                          ui srceHt,  ui srceLen,
                          ui firstRowInCol,  ui sampInCol,
                          ui firstColInRow,  ui sampInRow );

void  __vf  MSIsubmatrix_equM( siPMatrix MDest,
                               ui destHt,     ui destLen,
                               ui firstRowInCol,  ui sampInCol,
                               ui firstColInRow,  ui sampInRow,
                               siPMatrix MSrce,
                               ui srceHt,     ui srceLen );

void  __vf  MSIequMblock(  siPMatrix MSub,
                          ui subHt,  ui subLen,
                          siPMatrix MSrce,
                          ui srceHt,  ui srceLen,
                          ui firstRowInCol,  ui firstColInRow );

void  __vf  MSIblock_equM( siPMatrix MDest,
                          ui destHt,     ui destLen,
                          ui firstRowInCol,  ui firstColInRow,
                          siPMatrix MSrce,
                          ui srceHt,     ui srceLen );

void  __vf  MSIequMblockT( siPMatrix MSub,
                          ui subHt,  ui subLen,
                          siPMatrix MSrce,
                          ui srceHt,  ui srceLen,
                          ui firstRowInCol,  ui firstColInRow );

void  __vf  MSIblock_equMT( siPMatrix MDest,
                          ui destHt,     ui destLen,
                          ui firstRowInCol,  ui firstColInRow,
                          siPMatrix MSrce,
                          ui srceHt,     ui srceLen );


/*****   Extracting a single row or a single column or the diagonal  *****
 *       and storing it into a vector                                    */

void __vf MSIRow_extract( siVector Y, siPMatrix MA, ui ht, ui len,
                           ui iRow );
void __vf MSICol_extract( siVector Y, siPMatrix MA, ui ht, ui len,
                           ui iCol );
void __vf MSIDia_extract( siVector Y, siPMatrix MA, ui len );


/**********  Deleting or inserting a row or a column *****************/

void __vf MSIRow_delete( siPMatrix MB, siPMatrix MA,
                        ui htA, ui lenA, ui iRow );
void __vf MSICol_delete( siPMatrix MB, siPMatrix MA,
                        ui htA, ui lenA, ui iCol );
void __vf MSIRow_insert( siPMatrix MB, siPMatrix MA, ui htB,
                        ui lenB, ui iRow, siVector X );
void __vf MSICol_insert( siPMatrix MB, siPMatrix MA, ui htB,
                        ui lenB, ui iCol, siVector X );


/******  One-dimensional vector operations **********************
         performed along all rows or all columns simultaneously,
         or along the diagonal of a square matrix                */

void  __vf  MSIRows_max( siVector Y, siPMatrix MA, ui ht, ui len );
void  __vf  MSICols_max( siVector Y, siPMatrix MA, ui ht, ui len );
short __vf  MSIDia_max(  siPMatrix MA, ui len );
void  __vf  MSIRows_min( siVector Y, siPMatrix MA, ui ht, ui len );
void  __vf  MSICols_min( siVector Y, siPMatrix MA, ui ht, ui len );
short __vf  MSIDia_min(  siPMatrix MA, ui len );

void  __vf  MSIRows_rotate( siPMatrix MA, ui ht, ui len, ssize_t pos );
void  __vf  MSICols_rotate( siPMatrix MA, ui ht, ui len, ssize_t pos );
void  __vf  MSIRows_rotate_buf( siPMatrix MA, ui ht, ui len, ssize_t pos, siPMatrix MBuf );
void  __vf  MSICols_rotate_buf( siPMatrix MA, ui ht, ui len, ssize_t pos, siPMatrix MBuf );
void  __vf  MSIRows_reflect( siPMatrix MA, ui ht, ui len );
void  __vf  MSICols_reflect( siPMatrix MA, ui ht, ui len );
void  __vf  MSIRows_rev( siPMatrix MA, ui ht, ui len );
void  __vf  MSICols_rev( siPMatrix MA, ui ht, ui len );

void  __vf  MSIRows_distribution( uiPMatrix MAbund, siVector Limits, ui nBins, siPMatrix MX, ui ht, ui len, int mode );
void  __vf  MSICols_distribution( uiPMatrix MAbund, siVector Limits, ui nBins, siPMatrix MX, ui ht, ui len, int mode );

/********  Operations involving two rows or two colums of one matrix  *****/

void   __vf  MSIRows_exchange( siPMatrix MA, ui ht, ui len,
                              ui i1, ui i2 );
void   __vf  MSICols_exchange( siPMatrix MA, ui ht, ui len,
                              ui i1, ui i2 );

/*****************  Transposing and rotating a matrix **********************/

void  __vf  MSItranspose( siPMatrix MTr, siPMatrix MA,
                          ui htTr, ui lenTr );
void  __vf  MSIrotate90(  siPMatrix MRot, siPMatrix MA, ui htRot, ui lenRot );
#define     MSIrotate180( MRot, MA, htRot, lenRot ) \
                VSI_rev( MRot, MA, (htRot)*(lenRot) )
void  __vf  MSIrotate270( siPMatrix MRot, siPMatrix MA, ui htRot, ui lenRot );

      /*************  Input and Output  ****************/

void  __vf M_ifprint( FILE _VFAR *stream, void _VFAR *X, ui ht, ui len, unsigned linewidth, unsigned vers );
#define MSIfprint( stream, MA0, ht, len, linewidth ) \
                    M_ifprint( stream, (void _VFAR *) (MA0), ht, len, linewidth, 2 )
#define MSI_fprint( stream, MA, ht, len, linewidth ) \
                    MSIfprint( stream, (MA)[0], ht, len, linewidth )
void  __vf M_icprint( void _VFAR *X, ui ht, ui len, unsigned vers );
#define MSIcprint( MA0, ht, len ) M_icprint( (void _VFAR *) (MA0), ht, len, 2 )
#define MSI_cprint( MA, ht, len ) MSIcprint( (MA)[0], ht, len )
#define MSIprint( MA0, ht, len )  M_ifprint( stdout, (void _VFAR *) (MA0), ht, len, 80, 2 )
#define MSI_print( MA, ht, len )  MSIprint( (MA)[0], ht, len )
  /*  MSI_print, MSI_cprint usable only for console applications! */

void __vf MSIwrite( FILE _VFAR *stream, siPMatrix X, ui ht, ui len  );
void __vf MSIread( siPMatrix X, ui ht, ui len, FILE _VFAR *stream );
#define MSIstore( str, MA, ht, len ) VSI_store( str, MA, (len)*(ht) )
#define MSIrecall( MA, ht, len, str) VSI_recall( MA, (len)*(ht), str)

#ifdef __cplusplus
} // end of extern "C"
#endif
#endif  /*  __MSISTD_H  */
