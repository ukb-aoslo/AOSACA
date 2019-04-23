/*  MIstd.h

  matrix management functions:
  manipulations on matrices of data type "int"

  Copyright (c) 1996-2017 by OptiCode - Dr. Martin Sander Software Dev.
  All Rights Reserved.
*/

#if !defined( __MISTD_H )
#define __MISTD_H
#if !defined( __MATLIB_H )
#include <MatLib.h>
#endif
#if !defined( __VISTD_H )
#include <VIstd.h>
#endif
#if !defined( __VIMATH_H )
#include <VImath.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif

/*************   Dynamic Generation of Matrices   ************************/

iMatrix __vf  MI_matrix(  ui ht, ui len );
iMatrix __vf  MI_matrix0( ui ht, ui len );
#if defined (_MSC_VER) && defined (_DEBUG)
    iMatrix __vf  MI_matrix_dbg(  ui ht, ui len );
    iMatrix __vf  MI_matrix0_dbg( ui ht, ui len );
    #if defined (_INC_CRTDBG) && defined (_CRTDBG_MAP_ALLOC) 
	    /* Automatic mapping for memory-leak detection by CRT debugging switched on? */ 
        #define MI_matrix  MI_matrix_dbg
        #define MI_matrix0 MI_matrix0_dbg
    #endif
#else
    #define MI_matrix_dbg  MI_matrix
    #define MI_matrix0_dbg MI_matrix0
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

#define MI_getElement( y, MA, ht, len, m, n ) MIgetElement( y, (MA)[0], ht, len, m, n )
#define MI_setElement( MA, ht, len, m, n, C ) MIsetElement( (MA)[0], ht, len, m, n, C )
#define MI_Pelement( MA, ht, len, m, n ) MIPelement( (MA)[0], ht, len, m, n )
                     /* returns a pointer to MA[m][n]. */
#define MI_element( MA, ht, len, m, n ) (*MIPelement( (MA)[0], ht, len, m, n ))
                     /* dereferenced pointer */

 /****************  Initialization  ***************************************

    To initialize all elements of a matrix with the same value,
    or to perform arithmetic operations on all elements simultaneously,
    refer to the functions of VectorLib, declared in <VIstd.h>, <VImath.h>.
    In order to use the VectorLib functions, utilize the feature that
    the whole matrix occupies one contiguous area in memory: pass the
    address of the first row to the desired vector function, the size
    of the "vector" being ht * len.
    For example, initialize all elements of the matrix MA with 1.0
    (this is *NOT* the identity matrix)  by calling
        VI_equ1( (MA)[0], ht * len );
*/

#define MI_equ0( MA, ht, len )            VI_equ0( (MA)[0], (ht)*(len) )
#define MI_equ1( MA, len )                MIequ1( (MA)[0], len ) /* identity matrix */
#define MI_equm1( MA, len )               MIequm1( (MA)[0], len ) /* neg. identity matrix */
#define MI_random( MA, ht, len, seed, Min, Max ) \
                                          VI_random( (MA)[0], (ht)*(len), seed, Min, Max )
#define MI_outerprod( MA, X, Y, ht, len ) MIouterprod( (MA)[0], X, Y, ht, len )
                       /* sizX=ht, sizY=len */
#define MI_Row_equ0( MA, ht, len, iRow )  MIRow_equ0( (MA)[0], ht, len, iRow )
#define MI_Col_equ0( MA, ht, len, iCol )  MICol_equ0( (MA)[0], ht, len, iCol )
#define MI_Dia_equ0( MA, len )            MIDia_equ0( (MA)[0], len )
#define MI_Row_equC( MA, ht, len, iRow, C ) \
                                        MIRow_equC( (MA)[0], ht, len, iRow, C )
#define MI_Col_equC( MA, ht, len, iCol, C ) \
                                        MICol_equC( (MA)[0], ht, len, iCol, C )
#define MI_Dia_equC( MA, len, C )       MIDia_equC( (MA)[0], len, C )

#define MI_Row_equV( MA, ht, len, iRow, X ) \
                                        MIRow_equV( (MA)[0], ht, len, iRow, X )
#define MI_Col_equV( MA, ht, len, iCol, X ) \
                                        MICol_equV( (MA)[0], ht, len, iCol, X )
#define MI_Dia_equV( MA, len, X )       MIDia_equV( (MA)[0], len, X )

#define MI_Trd_equM( MA, MTrd, len )    MITrd_equM( (MA)[0], (MTrd)[0], len )
#define MI_Trd_extract( MTrd, MA, len ) MITrd_extract( (MTrd)[0], (MA)[0], len )

#define MI_equM( MB, MA, ht, len )  VI_equV( (MB)[0], (MA)[0], (ht)*(len) )
#define MI_neg( MB, MA, ht, len )   VI_neg( (MB)[0], (MA)[0], (ht)*(len) )

#define MI_UequL( MA, len ) MIUequL( (MA)[0], len )
#define MI_LequU( MA, len ) MILequU( (MA)[0], len )
         /* copy lower-diagonal elements into upper-diagonal
           (or vice versa) by index-reflection, so as to
           get a symmetric matrix    */

            /* data-type conversions:  */
/************** Data-type interconversions  ****************************/

#define M_ItoU( MU, MI, ht, len ) V_ItoU( (MU)[0], (MI)[0], (ht)*(len) )
#define M_UtoI( MI, MU, ht, len ) V_UtoI( (MI)[0], (MU)[0], (ht)*(len) )
#define M_ItoBI( MBI, MI, ht, len ) V_ItoBI( (MBI)[0], (MI)[0], (ht)*(len) )
#define M_ItoSI( MSI, MI, ht, len ) V_ItoSI( (MSI)[0], (MI)[0], (ht)*(len) )
#define M_ItoLI( MLI, MI, ht, len ) V_ItoLI( (MLI)[0], (MI)[0], (ht)*(len) )
#define M_ItoQI( MQI, MI, ht, len ) V_ItoQI( (MQI)[0], (MI)[0], (ht)*(len) )
#define M_BItoI( MI, MBI, ht, len ) V_BItoI( (MI)[0], (MBI)[0], (ht)*(len) )
#define M_SItoI( MI, MSI, ht, len ) V_SItoI( (MI)[0], (MSI)[0], (ht)*(len) )
#define M_LItoI( MI, MLI, ht, len ) V_LItoI( (MI)[0], (MLI)[0], (ht)*(len) )
#define M_QItoI( MI, MQI, ht, len ) V_QItoI( (MI)[0], (MQI)[0], (ht)*(len) )
#define M_ItoF(  MF,  MI, ht, len ) V_ItoF(  (MF)[0],  (MI)[0], (ht)*(len) )
#define M_ItoD(  MD,  MI, ht, len ) V_ItoD(  (MD)[0],  (MI)[0], (ht)*(len) )
#if (defined __BORLANDC__) && !(defined _WIN64)
    #define M_ItoE( ME, MI, ht, len ) V_ItoE( (ME)[0], (MI)[0], (ht)*(len) )
#else
    #define M_ItoE M_ItoD
#endif

/********  Extracting a submatrix and copying a submatrix back  *********/

#define MI_submatrix( MSub, subHt, subLen, \
                      MSrce, srceHt, srceLen, \
                      firstRowInCol, sampInCol, firstColInRow, sampInRow ) \
               MIsubmatrix(  (MSub)[0], subHt, subLen, \
                             (MSrce)[0], srceHt, srceLen, \
                             firstRowInCol, sampInCol, firstColInRow, sampInRow )

#define MI_submatrix_equM( MDest, destHt, destLen, \
                           firstRowInCol, sampInCol, firstColInRow, sampInRow, \
                           MSrce, srceHt, srceLen ) \
               MIsubmatrix_equM(  (MDest)[0], destHt, destLen, \
                             firstRowInCol, sampInCol, firstColInRow, sampInRow, \
                             (MSrce)[0], srceHt, srceLen )

#define MI_equMblock( MSub, subHt, subLen, \
                      MSrce, srceHt, srceLen, \
                      firstRowInCol, firstColInRow ) \
               MIequMblock(  (MSub)[0], subHt, subLen, \
                             (MSrce)[0], srceHt, srceLen, \
                             firstRowInCol, firstColInRow )

#define MI_block_equM( MDest, destHt, destLen, \
                       firstRowInCol, firstColInRow, \
                       MSrce, srceHt, srceLen ) \
               MIblock_equM( (MDest)[0], destHt, destLen, \
                             firstRowInCol, firstColInRow, \
                             (MSrce)[0], srceHt, srceLen )

#define MI_equMblockT( MSub, subHt, subLen, \
                      MSrce, srceHt, srceLen, \
                      firstRowInCol, firstColInRow ) \
               MIequMblockT(  (MSub)[0], subHt, subLen, \
                             (MSrce)[0], srceHt, srceLen, \
                             firstRowInCol, firstColInRow )

#define MI_block_equMT( MDest, destHt, destLen, \
                       firstRowInCol, firstColInRow, \
                       MSrce, srceHt, srceLen ) \
               MIblock_equMT( (MDest)[0], destHt, destLen, \
                             firstRowInCol, firstColInRow, \
                             (MSrce)[0], srceHt, srceLen )

/*****   Extracting a single row or a single column or the diagonal  ******
 *       and storing it into a vector                                     */

#define MI_Row_extract( Y, MA, ht, len, iRow ) \
                                     MIRow_extract( Y, (MA)[0], ht, len, iRow )
#define MI_Col_extract( Y, MA, ht, len, iCol ) \
                                     MICol_extract( Y, (MA)[0], ht, len, iCol )
#define MI_Dia_extract( Y, MA, len ) MIDia_extract( Y, (MA)[0], len )


/**************  Deleting or inserting a row or a column   ***************/

#define MI_Row_delete( MB, MA, htA, lenA, iRow ) \
                           MIRow_delete( (MB)[0], (MA)[0], htA, lenA, iRow )
#define MI_Col_delete( MB, MA, htA, lenA, iCol ) \
                           MICol_delete( (MB)[0], (MA)[0], htA, lenA, iCol )
#define MI_Row_insert( MB, MA, htB, lenB, iRow, X ) \
                           MIRow_insert( (MB)[0], (MA)[0], htB, lenB, iRow, X )
#define MI_Col_insert( MB, MA, htB, lenB, iCol, X ) \
                           MICol_insert( (MB)[0], (MA)[0], htB, lenB, iCol, X )

/******  One-dimensional vector operations **********************
         performed along all rows or all columns simultaneously,
         or along the diagonal of a square matrix                */

#define MI_Rows_max( Y, MA, ht, len )     MIRows_max( Y, (MA)[0], ht, len )
#define MI_Cols_max( Y, MA, ht, len )     MICols_max( Y, (MA)[0], ht, len )
#define MI_Dia_max(  MA, len )            MIDia_max(  (MA)[0], len )
#define MI_Rows_min( Y, MA, ht, len )     MIRows_min( Y, (MA)[0], ht, len )
#define MI_Cols_min( Y, MA, ht, len )     MICols_min( Y, (MA)[0], ht, len )
#define MI_Dia_min(  MA, len )            MIDia_min(  (MA)[0], len )

#define MI_Rows_rotate( MA, ht, len, pos) MIRows_rotate( (MA)[0], ht, len, pos )
#define MI_Cols_rotate( MA, ht, len, pos) MICols_rotate( (MA)[0], ht, len, pos )
#define MI_Rows_rotate_buf( MA, ht, len, pos, MBuf) MIRows_rotate_buf( (MA)[0], ht, len, pos, (MBuf)[0] )
#define MI_Cols_rotate_buf( MA, ht, len, pos, MBuf) MICols_rotate_buf( (MA)[0], ht, len, pos, (MBuf)[0] )
#define MI_Rows_reflect( MA, ht, len)     MIRows_reflect( (MA)[0], ht, len )
#define MI_Cols_reflect( MA, ht, len)     MICols_reflect( (MA)[0], ht, len )
#define MI_Rows_rev( MA, ht, len)         MIRows_rev( (MA)[0], ht, len )
#define MI_Cols_rev( MA, ht, len)         MICols_rev( (MA)[0], ht, len )

#define MI_Rows_distribution( MAbund, Limits, nBins, MX, htX, lenX, mode ) MIRows_distribution( (MAbund)[0], Limits, nBins, (MX)[0], htX, lenX, mode )
#define MI_Cols_distribution( MAbund, Limits, nBins, MX, htX, lenX, mode ) MICols_distribution( (MAbund)[0], Limits, nBins, (MX)[0], htX, lenX, mode )

/********  Operations involving two rows or two colums of one matrix  *****/

#define MI_Rows_exchange( MA, ht, len, row1, row2 ) \
                             MIRows_exchange( (MA)[0], ht, len, row1, row2 )
#define MI_Cols_exchange( MA, ht, len, col1, col2 ) \
                             MICols_exchange( (MA)[0], ht, len, col1, col2 )

/**************  Transposing and rotating a matrix **********************/

#define MI_transpose( MTr, MA, htTr, lenTr ) \
             MItranspose( (MTr)[0], (MA)[0], htTr, lenTr )
       /*  dimensions htTr, lenTr are those of the transposed matrix,
           not of the original!                */
#define MI_rotate90( MRot, MA, htRot, lenRot ) \
             MIrotate90( (MRot)[0], (MA)[0], htRot, lenRot )
#define MI_rotate180( MRot, MA, htRot, lenRot ) \
             VI_rev( (MRot)[0], (MA)[0], (htRot)*(lenRot) )
#define MI_rotate270( MRot, MA, htRot, lenRot ) \
             MIrotate270( (MRot)[0], (MA)[0], htRot, lenRot )

/**************************  Input and Output  **************************/

#define MI_write( str, MA, ht, len )   MIwrite( str, (MA)[0], ht, len )
#define MI_read( MA, ht, len, str )    MIread( (MA)[0], ht, len, str )
#define MI_setWriteFormat              VI_setWriteFormat
#define MI_setWriteSeparate            VI_setNWriteSeparate
                                   /* write and read in ascii format */
#define MI_store( str, MA, ht, len )   VI_store( str, (MA)[0], (len)*(ht) )
#define MI_recall( MA, ht, len, str)   VI_recall( (MA)[0], (len)*(ht), str)
                                  /* store and recall in binary format */


/*************************************************************************
 * Here are now the actual declarations of the functions used internally.*
 * These declarations may change in future versions of MatrixLib!        *
 * You should not care too much about them, except in the case you need  *
 * the actual address of a run-time function (see above). Under all      *
 * "normal" circumstances, use only the names defined above in the       *
 * macro section!                                                        *
 *************************************************************************/

void  __vf MIgetElement( int *y, iPMatrix X, ui ht, ui len, ui m, ui n );
void  __vf MIsetElement( iPMatrix X, ui ht, ui len, ui m, ui n, int C );
int _VFAR * __vf MIPelement( iPMatrix X, ui ht, ui len, ui m, ui n );
                  /* pointer is normalized in memory model HUGE */
#define MIelement( MA, ht, len, m, n ) (*MIPelement( MA, ht, len, m, n ))

#define MIequ0( MA, ht, len )            VI_equ0( MA, (ht)*(len) )
void   __vf  MIequ1( iPMatrix MA, ui len );  /* identity matrix */
void   __vf  MIequm1( iPMatrix MA, ui len );  /* neg. identity matrix */
void   __vf  MIouterprod( iPMatrix MA, iVector X,  iVector Y,
                          ui ht, ui len );

void   __vf  MIRow_equ0( iPMatrix MA, ui ht, ui len,
                         ui iRow );
void   __vf  MICol_equ0( iPMatrix MA, ui ht, ui len,
                         ui iCol );
void   __vf  MIDia_equ0( iPMatrix MA, ui len );

void   __vf  MIRow_equC( iPMatrix MA, ui ht, ui len,
                         ui iRow, int C );
void   __vf  MICol_equC( iPMatrix MA, ui ht, ui len,
                         ui iCol, int C );
void   __vf  MIDia_equC( iPMatrix MA, ui len, int C );

void   __vf  MIRow_equV( iPMatrix MA, ui ht, ui len,
                         ui iRow, iVector X );
void   __vf  MICol_equV( iPMatrix MA, ui ht, ui len,
                         ui iCol, iVector X );
void   __vf  MIDia_equV( iPMatrix MA, ui len, iVector X );

void   __vf  MITrd_equM( iPMatrix MA, iPMatrix MTrd, ui len );
void   __vf  MITrd_extract( iPMatrix MTrd, iPMatrix MA, ui len );

#define MIequM( MB, MA, ht, len )  VI_equV( MB, MA, (ht)*(len) )
#define MIneg( MB, MA, ht, len )   VI_neg( MB, MA, (ht)*(len) )
void   __vf  MIUequL( iPMatrix MA, ui len );
void   __vf  MILequU( iPMatrix MA, ui len );

/********  Extracting a submatrix and copying a submatrix back  *********/

void  __vf  MIsubmatrix( iPMatrix MSub,
                          ui subHt,  ui subLen,
                          iPMatrix MSrce,
                          ui srceHt,  ui srceLen,
                          ui firstRowInCol,  ui sampInCol,
                          ui firstColInRow,  ui sampInRow );

void  __vf  MIsubmatrix_equM( iPMatrix MDest,
                               ui destHt,     ui destLen,
                               ui firstRowInCol,  ui sampInCol,
                               ui firstColInRow,  ui sampInRow,
                               iPMatrix MSrce,
                               ui srceHt,     ui srceLen );

void  __vf  MIequMblock(  iPMatrix MSub,
                          ui subHt,  ui subLen,
                          iPMatrix MSrce,
                          ui srceHt,  ui srceLen,
                          ui firstRowInCol,  ui firstColInRow );

void  __vf  MIblock_equM( iPMatrix MDest,
                          ui destHt,     ui destLen,
                          ui firstRowInCol,  ui firstColInRow,
                          iPMatrix MSrce,
                          ui srceHt,     ui srceLen );

void  __vf  MIequMblockT( iPMatrix MSub,
                          ui subHt,  ui subLen,
                          iPMatrix MSrce,
                          ui srceHt,  ui srceLen,
                          ui firstRowInCol,  ui firstColInRow );

void  __vf  MIblock_equMT( iPMatrix MDest,
                          ui destHt,     ui destLen,
                          ui firstRowInCol,  ui firstColInRow,
                          iPMatrix MSrce,
                          ui srceHt,     ui srceLen );


/*****   Extracting a single row or a single column or the diagonal  *****
 *       and storing it into a vector                                    */

void __vf MIRow_extract( iVector Y, iPMatrix MA, ui ht, ui len,
                           ui iRow );
void __vf MICol_extract( iVector Y, iPMatrix MA, ui ht, ui len,
                           ui iCol );
void __vf MIDia_extract( iVector Y, iPMatrix MA, ui len );


/**********  Deleting or inserting a row or a column *****************/

void __vf MIRow_delete( iPMatrix MB, iPMatrix MA,
                        ui htA, ui lenA, ui iRow );
void __vf MICol_delete( iPMatrix MB, iPMatrix MA,
                        ui htA, ui lenA, ui iCol );
void __vf MIRow_insert( iPMatrix MB, iPMatrix MA, ui htB,
                        ui lenB, ui iRow, iVector X );
void __vf MICol_insert( iPMatrix MB, iPMatrix MA, ui htB,
                        ui lenB, ui iCol, iVector X );


/******  One-dimensional vector operations **********************
         performed along all rows or all columns simultaneously,
         or along the diagonal of a square matrix                */

void  __vf  MIRows_max( iVector Y, iPMatrix MA, ui ht, ui len );
void  __vf  MICols_max( iVector Y, iPMatrix MA, ui ht, ui len );
int __vf  MIDia_max(  iPMatrix MA, ui len );
void  __vf  MIRows_min( iVector Y, iPMatrix MA, ui ht, ui len );
void  __vf  MICols_min( iVector Y, iPMatrix MA, ui ht, ui len );
int __vf  MIDia_min(  iPMatrix MA, ui len );

void  __vf  MIRows_rotate( iPMatrix MA, ui ht, ui len, ssize_t pos );
void  __vf  MICols_rotate( iPMatrix MA, ui ht, ui len, ssize_t pos );
void  __vf  MIRows_rotate_buf( iPMatrix MA, ui ht, ui len, ssize_t pos, iPMatrix MBuf );
void  __vf  MICols_rotate_buf( iPMatrix MA, ui ht, ui len, ssize_t pos, iPMatrix MBuf );
void  __vf  MIRows_reflect( iPMatrix MA, ui ht, ui len );
void  __vf  MICols_reflect( iPMatrix MA, ui ht, ui len );
void  __vf  MIRows_rev( iPMatrix MA, ui ht, ui len );
void  __vf  MICols_rev( iPMatrix MA, ui ht, ui len );

void  __vf  MIRows_distribution( uiPMatrix MAbund, iVector Limits, ui nBins, iPMatrix MX, ui ht, ui len, int mode );
void  __vf  MICols_distribution( uiPMatrix MAbund, iVector Limits, ui nBins, iPMatrix MX, ui ht, ui len, int mode );

/********  Operations involving two rows or two colums of one matrix  *****/

void   __vf  MIRows_exchange( iPMatrix MA, ui ht, ui len,
                              ui i1, ui i2 );
void   __vf  MICols_exchange( iPMatrix MA, ui ht, ui len,
                              ui i1, ui i2 );

/***************  Transposing and rotating a matrix **********************/

void  __vf  MItranspose( iPMatrix MTr, iPMatrix MA,
                          ui htTr, ui lenTr );
void  __vf  MIrotate90(  iPMatrix MRot, iPMatrix MA, ui htRot, ui lenRot );
#define     MIrotate180( MRot, MA, htRot, lenRot ) \
                VI_rev( MRot, MA, (htRot)*(lenRot) )
void  __vf  MIrotate270( iPMatrix MRot, iPMatrix MA, ui htRot, ui lenRot );

      /*************  Input and Output  ****************/

void  __vf M_ifprint( FILE _VFAR *stream, void _VFAR *X, ui ht, ui len, unsigned linewidth, unsigned vers );
#define MIfprint( stream, MA0, ht, len, linewidth ) \
                    M_ifprint( stream, (void _VFAR *) (MA0), ht, len, linewidth, 4 )
#define MI_fprint( stream, MA, ht, len, linewidth ) \
                    MIfprint( stream, (MA)[0], ht, len, linewidth )
void  __vf M_icprint( void _VFAR *X, ui ht, ui len, unsigned vers );
#define MIcprint( MA0, ht, len ) M_icprint( (void _VFAR *) (MA0), ht, len, 4 )
#define MI_cprint( MA, ht, len ) MIcprint( (MA)[0], ht, len )
#define MIprint( MA0, ht, len )  M_ifprint( stdout, (void _VFAR *) (MA0), ht, len, 80, 4 )
#define MI_print( MA, ht, len )  MIprint( (MA)[0], ht, len )
  /*  MI_print, MI_cprint usable only for console applications! */

void __vf MIwrite( FILE _VFAR *stream, iPMatrix X, ui ht, ui len  );
void __vf MIread( iPMatrix X, ui ht, ui len, FILE _VFAR *stream );
#define MIstore( str, MA, ht, len ) VI_store( str, MA, (len)*(ht) )
#define MIrecall( MA, ht, len, str) VI_recall( MA, (len)*(ht), str)

#ifdef __cplusplus
} // end of extern "C"
#endif
#endif  /*  __MISTD_H  */
