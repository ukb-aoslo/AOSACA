/*  MUstd.h

  matrix management functions:
  manipulations on matrices of data type "unsigned"

  Copyright (c) 1996-2017 by OptiCode - Dr. Martin Sander Software Dev.
  All Rights Reserved.
*/

#if !defined( __MUSTD_H )
#define __MUSTD_H
#if !defined( __MATLIB_H )
#include <MatLib.h>
#endif
#if !defined( __VUSTD_H )
#include <VUstd.h>
#endif
#if !defined( __VUMATH_H )
#include <VUmath.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif

/*************   Dynamic Generation of Matrices   ************************/

uMatrix __vf  MU_matrix(  ui ht, ui len );
uMatrix __vf  MU_matrix0( ui ht, ui len );
#if defined (_MSC_VER) && defined (_DEBUG)
    uMatrix __vf  MU_matrix_dbg(  ui ht, ui len );
    uMatrix __vf  MU_matrix0_dbg( ui ht, ui len );
    #if defined (_INC_CRTDBG) && defined (_CRTDBG_MAP_ALLOC)
	    /* Automatic mapping for memory-leak detection by CRT debugging switched on? */
        #define MU_matrix  MU_matrix_dbg
        #define MU_matrix0 MU_matrix0_dbg
    #endif
#else
    #define MU_matrix_dbg  MU_matrix
    #define MU_matrix0_dbg MU_matrix0
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

#define MU_getElement( y, MA, ht, len, m, n ) MUgetElement( y, (MA)[0], ht, len, m, n )
#define MU_setElement( MA, ht, len, m, n, C ) MUsetElement( (MA)[0], ht, len, m, n, C )
#define MU_Pelement( MA, ht, len, m, n ) MUPelement( (MA)[0], ht, len, m, n )
                     /* returns a pointer to MA[m][n]. */
#define MU_element( MA, ht, len, m, n ) (*MUPelement( (MA)[0], ht, len, m, n ))
                     /* dereferenced pointer */

 /****************  Initialization  ***************************************

    To initialize all elements of a matrix with the same value,
    or to perform arithmetic operations on all elements simultaneously,
    refer to the functions of VectorLib, declared in <VUstd.h>, <VUmath.h>.
    In order to use the VectorLib functions, utilize the feature that
    the whole matrix occupies one contiguous area in memory: pass the
    address of the first row to the desired vector function, the size
    of the "vector" being ht * len.
    For example, initialize all elements of the matrix MA with 1.0
    (this is *NOT* the identity matrix)  by calling
        VU_equ1( (MA)[0], ht * len );
*/

#define MU_equ0( MA, ht, len )            VU_equ0( (MA)[0], (ht)*(len) )
#define MU_equ1( MA, len )                MUequ1( (MA)[0], len ) /* identity matrix */
#define MU_random( MA, ht, len, seed, Min, Max ) \
                                          VU_random( (MA)[0], (ht)*(len), seed, Min, Max )
#define MU_outerprod( MA, X, Y, ht, len ) MUouterprod( (MA)[0], X, Y, ht, len )
                       /* sizX=ht, sizY=len */
#define MU_Row_equ0( MA, ht, len, iRow )  MURow_equ0( (MA)[0], ht, len, iRow )
#define MU_Col_equ0( MA, ht, len, iCol )  MUCol_equ0( (MA)[0], ht, len, iCol )
#define MU_Dia_equ0( MA, len )            MUDia_equ0( (MA)[0], len )
#define MU_Row_equC( MA, ht, len, iRow, C ) \
                                        MURow_equC( (MA)[0], ht, len, iRow, C )
#define MU_Col_equC( MA, ht, len, iCol, C ) \
                                        MUCol_equC( (MA)[0], ht, len, iCol, C )
#define MU_Dia_equC( MA, len, C )       MUDia_equC( (MA)[0], len, C )

#define MU_Row_equV( MA, ht, len, iRow, X ) \
                                        MURow_equV( (MA)[0], ht, len, iRow, X )
#define MU_Col_equV( MA, ht, len, iCol, X ) \
                                        MUCol_equV( (MA)[0], ht, len, iCol, X )
#define MU_Dia_equV( MA, len, X )       MUDia_equV( (MA)[0], len, X )

#define MU_Trd_equM( MA, MTrd, len )    MUTrd_equM( (MA)[0], (MTrd)[0], len )
#define MU_Trd_extract( MTrd, MA, len ) MUTrd_extract( (MTrd)[0], (MA)[0], len )

#define MU_equM( MB, MA, ht, len )  VU_equV( (MB)[0], (MA)[0], (ht)*(len) )

#define MU_UequL( MA, len ) MUUequL( (MA)[0], len )
#define MU_LequU( MA, len ) MULequU( (MA)[0], len )
         /* copy lower-diagonal elements into upper-diagonal
           (or vice versa) by index-reflection, so as to
           get a symmetric matrix    */

            /* data-type conversions:  */
/************** Data-type interconversions  ****************************/

#define M_ItoU( MU, MI, ht, len ) V_ItoU( (MU)[0], (MI)[0], (ht)*(len) )
#define M_UtoI( MI, MU, ht, len ) V_UtoI( (MI)[0], (MU)[0], (ht)*(len) )
#define M_UtoUB( MUB, MU, ht, len ) V_UtoUB( (MUB)[0], (MU)[0], (ht)*(len) )
#define M_UtoUS( MUS, MU, ht, len ) V_UtoUS( (MUS)[0], (MU)[0], (ht)*(len) )
#define M_UtoUL( MUL, MU, ht, len ) V_UtoUL( (MUL)[0], (MU)[0], (ht)*(len) )
#define M_UBtoU( MU, MUB, ht, len ) V_UBtoU( (MU)[0], (MUB)[0], (ht)*(len) )
#define M_UStoU( MU, MUS, ht, len ) V_UStoU( (MU)[0], (MUS)[0], (ht)*(len) )
#define M_ULtoU( MU, MUL, ht, len ) V_ULtoU( (MU)[0], (MUL)[0], (ht)*(len) )
#define M_UtoF(  MF,  MU, ht, len ) V_UtoF(  (MF)[0],  (MU)[0], (ht)*(len) )
#define M_UtoD(  MD,  MU, ht, len ) V_UtoD(  (MD)[0],  (MU)[0], (ht)*(len) )
#ifdef _WIN64
	#define M_UtoUQ( MUQ, MU, ht, len ) V_UtoUQ( (MUQ)[0], (MU)[0], (ht)*(len) )
	#define M_UQtoU( MU, MUQ, ht, len ) V_UQtoU( (MU)[0], (MUQ)[0], (ht)*(len) )
#endif
#if (defined __BORLANDC__) && !(defined _WIN64)
    #define M_UtoE( ME, MU, ht, len ) V_UtoE( (ME)[0], (MU)[0], (ht)*(len) )
#else
    #define M_UtoE M_UtoD
#endif

/********  Extracting a submatrix and copying a submatrix back  *********/

#define MU_submatrix( MSub, subHt, subLen, \
                      MSrce, srceHt, srceLen, \
                      firstRowInCol, sampInCol, firstColInRow, sampInRow ) \
               MUsubmatrix(  (MSub)[0], subHt, subLen, \
                             (MSrce)[0], srceHt, srceLen, \
                             firstRowInCol, sampInCol, firstColInRow, sampInRow )

#define MU_submatrix_equM( MDest, destHt, destLen, \
                           firstRowInCol, sampInCol, firstColInRow, sampInRow, \
                           MSrce, srceHt, srceLen ) \
               MUsubmatrix_equM(  (MDest)[0], destHt, destLen, \
                             firstRowInCol, sampInCol, firstColInRow, sampInRow, \
                             (MSrce)[0], srceHt, srceLen )

#define MU_equMblock( MSub, subHt, subLen, \
                      MSrce, srceHt, srceLen, \
                      firstRowInCol, firstColInRow ) \
               MUequMblock(  (MSub)[0], subHt, subLen, \
                             (MSrce)[0], srceHt, srceLen, \
                             firstRowInCol, firstColInRow )

#define MU_block_equM( MDest, destHt, destLen, \
                       firstRowInCol, firstColInRow, \
                       MSrce, srceHt, srceLen ) \
               MUblock_equM( (MDest)[0], destHt, destLen, \
                             firstRowInCol, firstColInRow, \
                             (MSrce)[0], srceHt, srceLen )

#define MU_equMblockT( MSub, subHt, subLen, \
                      MSrce, srceHt, srceLen, \
                      firstRowInCol, firstColInRow ) \
               MUequMblockT(  (MSub)[0], subHt, subLen, \
                             (MSrce)[0], srceHt, srceLen, \
                             firstRowInCol, firstColInRow )

#define MU_block_equMT( MDest, destHt, destLen, \
                       firstRowInCol, firstColInRow, \
                       MSrce, srceHt, srceLen ) \
               MUblock_equMT( (MDest)[0], destHt, destLen, \
                             firstRowInCol, firstColInRow, \
                             (MSrce)[0], srceHt, srceLen )

/*****   Extracting a single row or a single column or the diagonal  ******
 *       and storing it into a vector                                     */

#define MU_Row_extract( Y, MA, ht, len, iRow ) \
                                     MURow_extract( Y, (MA)[0], ht, len, iRow )
#define MU_Col_extract( Y, MA, ht, len, iCol ) \
                                     MUCol_extract( Y, (MA)[0], ht, len, iCol )
#define MU_Dia_extract( Y, MA, len ) MUDia_extract( Y, (MA)[0], len )


/**************  Deleting or inserting a row or a column   ***************/

#define MU_Row_delete( MB, MA, htA, lenA, iRow ) \
                           MURow_delete( (MB)[0], (MA)[0], htA, lenA, iRow )
#define MU_Col_delete( MB, MA, htA, lenA, iCol ) \
                           MUCol_delete( (MB)[0], (MA)[0], htA, lenA, iCol )
#define MU_Row_insert( MB, MA, htB, lenB, iRow, X ) \
                           MURow_insert( (MB)[0], (MA)[0], htB, lenB, iRow, X )
#define MU_Col_insert( MB, MA, htB, lenB, iCol, X ) \
                           MUCol_insert( (MB)[0], (MA)[0], htB, lenB, iCol, X )

/******  One-dimensional vector operations **********************
         performed along all rows or all columns simultaneously,
         or along the diagonal of a square matrix                */

#define MU_Rows_max( Y, MA, ht, len )     MURows_max( Y, (MA)[0], ht, len )
#define MU_Cols_max( Y, MA, ht, len )     MUCols_max( Y, (MA)[0], ht, len )
#define MU_Dia_max(  MA, len )            MUDia_max(  (MA)[0], len )
#define MU_Rows_min( Y, MA, ht, len )     MURows_min( Y, (MA)[0], ht, len )
#define MU_Cols_min( Y, MA, ht, len )     MUCols_min( Y, (MA)[0], ht, len )
#define MU_Dia_min(  MA, len )            MUDia_min(  (MA)[0], len )

#define MU_Rows_rotate( MA, ht, len, pos) MURows_rotate( (MA)[0], ht, len, pos )
#define MU_Cols_rotate( MA, ht, len, pos) MUCols_rotate( (MA)[0], ht, len, pos )
#define MU_Rows_rotate_buf( MA, ht, len, pos, MBuf) MURows_rotate_buf( (MA)[0], ht, len, pos, (MBuf)[0] )
#define MU_Cols_rotate_buf( MA, ht, len, pos, MBuf) MUCols_rotate_buf( (MA)[0], ht, len, pos, (MBuf)[0] )
#define MU_Rows_reflect( MA, ht, len)     MURows_reflect( (MA)[0], ht, len )
#define MU_Cols_reflect( MA, ht, len)     MUCols_reflect( (MA)[0], ht, len )
#define MU_Rows_rev( MA, ht, len)         MURows_rev( (MA)[0], ht, len )
#define MU_Cols_rev( MA, ht, len)         MUCols_rev( (MA)[0], ht, len )

#define MU_Rows_distribution( MAbund, Limits, nBins, MX, htX, lenX, mode ) MURows_distribution( (MAbund)[0], Limits, nBins, (MX)[0], htX, lenX, mode )
#define MU_Cols_distribution( MAbund, Limits, nBins, MX, htX, lenX, mode ) MUCols_distribution( (MAbund)[0], Limits, nBins, (MX)[0], htX, lenX, mode )

/********  Operations involving two rows or two colums of one matrix  *****/

#define MU_Rows_exchange( MA, ht, len, row1, row2 ) \
                             MURows_exchange( (MA)[0], ht, len, row1, row2 )
#define MU_Cols_exchange( MA, ht, len, col1, col2 ) \
                             MUCols_exchange( (MA)[0], ht, len, col1, col2 )

/****************  Transposing and rotating a matrix **********************/

#define MU_transpose( MTr, MA, htTr, lenTr ) \
             MUtranspose( (MTr)[0], (MA)[0], htTr, lenTr )
       /*  dimensions htTr, lenTr are those of the transposed matrix,
           not of the original!                */
#define MU_rotate90( MRot, MA, htRot, lenRot ) \
             MUrotate90( (MRot)[0], (MA)[0], htRot, lenRot )
#define MU_rotate180( MRot, MA, htRot, lenRot ) \
             VU_rev( (MRot)[0], (MA)[0], (htRot)*(lenRot) )
#define MU_rotate270( MRot, MA, htRot, lenRot ) \
             MUrotate270( (MRot)[0], (MA)[0], htRot, lenRot )

/**************************  Input and Output  **************************/

#define MU_write( str, MA, ht, len )   MUwrite( str, (MA)[0], ht, len )
#define MU_read( MA, ht, len, str )    MUread( (MA)[0], ht, len, str )
#define MU_setWriteFormat              VU_setWriteFormat
#define MU_setWriteSeparate            VU_setNWriteSeparate
                                   /* write and read in ascii format */
#define MU_store( str, MA, ht, len )   VU_store( str, (MA)[0], (len)*(ht) )
#define MU_recall( MA, ht, len, str)   VU_recall( (MA)[0], (len)*(ht), str)
                                  /* store and recall in binary format */


/*************************************************************************
 * Here are now the actual declarations of the functions used internally.*
 * These declarations may change in future versions of MatrixLib!        *
 * You should not care too much about them, except in the case you need  *
 * the actual address of a run-time function (see above). Under all      *
 * "normal" circumstances, use only the names defined above in the       *
 * macro section!                                                        *
 *************************************************************************/

void  __vf MUgetElement( unsigned *y, uPMatrix X, ui ht, ui len, ui m, ui n );
void  __vf MUsetElement( uPMatrix X, ui ht, ui len, ui m, ui n, unsigned C );
unsigned _VFAR * __vf MUPelement( uPMatrix X, ui ht, ui len, ui m, ui n );
                  /* pointer is normalized in memory model HUGE */
#define MUelement( MA, ht, len, m, n ) (*MUPelement( MA, ht, len, m, n ))

#define MUequ0( MA, ht, len )            VU_equ0( MA, (ht)*(len) )
void   __vf  MUequ1( uPMatrix MA, ui len );  /* identity matrix */
void   __vf  MUouterprod( uPMatrix MA, uVector X,  uVector Y, ui ht, ui len );

void   __vf  MURow_equ0( uPMatrix MA, ui ht, ui len, ui iRow );
void   __vf  MUCol_equ0( uPMatrix MA, ui ht, ui len, ui iCol );
void   __vf  MUDia_equ0( uPMatrix MA, ui len );

void   __vf  MURow_equC( uPMatrix MA, ui ht, ui len,
                         ui iRow, unsigned C );
void   __vf  MUCol_equC( uPMatrix MA, ui ht, ui len,
                         ui iCol, unsigned C );
void   __vf  MUDia_equC( uPMatrix MA, ui len, unsigned C );

void   __vf  MURow_equV( uPMatrix MA, ui ht, ui len,
                         ui iRow, uVector X );
void   __vf  MUCol_equV( uPMatrix MA, ui ht, ui len,
                         ui iCol, uVector X );
void   __vf  MUDia_equV( uPMatrix MA, ui len, uVector X );

void   __vf  MUTrd_equM( uPMatrix MA, uPMatrix MTrd, ui len );
void   __vf  MUTrd_extract( uPMatrix MTrd, uPMatrix MA, ui len );

#define MUequM( MB, MA, ht, len )  VU_equV( MB, MA, (ht)*(len) )
void   __vf  MUUequL( uPMatrix MA, ui len );
void   __vf  MULequU( uPMatrix MA, ui len );

/********  Extracting a submatrix and copying a submatrix back  *********/

void  __vf  MUsubmatrix( uPMatrix MSub,
                          ui subHt,  ui subLen,
                          uPMatrix MSrce,
                          ui srceHt,  ui srceLen,
                          ui firstRowInCol,  ui sampInCol,
                          ui firstColInRow,  ui sampInRow );

void  __vf  MUsubmatrix_equM( uPMatrix MDest,
                               ui destHt,     ui destLen,
                               ui firstRowInCol,  ui sampInCol,
                               ui firstColInRow,  ui sampInRow,
                               uPMatrix MSrce,
                               ui srceHt,     ui srceLen );

void  __vf  MUequMblock(  uPMatrix MSub,
                          ui subHt,  ui subLen,
                          uPMatrix MSrce,
                          ui srceHt,  ui srceLen,
                          ui firstRowInCol,  ui firstColInRow );

void  __vf  MUblock_equM( uPMatrix MDest,
                          ui destHt,     ui destLen,
                          ui firstRowInCol,  ui firstColInRow,
                          uPMatrix MSrce,
                          ui srceHt,     ui srceLen );

void  __vf  MUequMblockT( uPMatrix MSub,
                          ui subHt,  ui subLen,
                          uPMatrix MSrce,
                          ui srceHt,  ui srceLen,
                          ui firstRowInCol,  ui firstColInRow );

void  __vf  MUblock_equMT( uPMatrix MDest,
                          ui destHt,     ui destLen,
                          ui firstRowInCol,  ui firstColInRow,
                          uPMatrix MSrce,
                          ui srceHt,     ui srceLen );


/*****   Extracting a single row or a single column or the diagonal  *****
 *       and storing it into a vector                                    */

void __vf MURow_extract( uVector Y, uPMatrix MA, ui ht, ui len,
                           ui iRow );
void __vf MUCol_extract( uVector Y, uPMatrix MA, ui ht, ui len,
                           ui iCol );
void __vf MUDia_extract( uVector Y, uPMatrix MA, ui len );


/**********  Deleting or inserting a row or a column *****************/

void __vf MURow_delete( uPMatrix MB, uPMatrix MA,
                        ui htA, ui lenA, ui iRow );
void __vf MUCol_delete( uPMatrix MB, uPMatrix MA,
                        ui htA, ui lenA, ui iCol );
void __vf MURow_insert( uPMatrix MB, uPMatrix MA, ui htB,
                        ui lenB, ui iRow, uVector X );
void __vf MUCol_insert( uPMatrix MB, uPMatrix MA, ui htB,
                        ui lenB, ui iCol, uVector X );


/******  One-dimensional vector operations **********************
         performed along all rows or all columns simultaneously,
         or along the diagonal of a square matrix                */

void  __vf  MURows_max( uVector Y, uPMatrix MA, ui ht, ui len );
void  __vf  MUCols_max( uVector Y, uPMatrix MA, ui ht, ui len );
unsigned __vf  MUDia_max(  uPMatrix MA, ui len );
void  __vf  MURows_min( uVector Y, uPMatrix MA, ui ht, ui len );
void  __vf  MUCols_min( uVector Y, uPMatrix MA, ui ht, ui len );
unsigned __vf  MUDia_min(  uPMatrix MA, ui len );

void  __vf  MURows_rotate( uPMatrix MA, ui ht, ui len, ssize_t pos );
void  __vf  MUCols_rotate( uPMatrix MA, ui ht, ui len, ssize_t pos );
void  __vf  MURows_rotate_buf( uPMatrix MA, ui ht, ui len, ssize_t pos, uPMatrix MBuf );
void  __vf  MUCols_rotate_buf( uPMatrix MA, ui ht, ui len, ssize_t pos, uPMatrix MBuf );
void  __vf  MURows_reflect( uPMatrix MA, ui ht, ui len );
void  __vf  MUCols_reflect( uPMatrix MA, ui ht, ui len );
void  __vf  MURows_rev( uPMatrix MA, ui ht, ui len );
void  __vf  MUCols_rev( uPMatrix MA, ui ht, ui len );

void  __vf  MURows_distribution( uiPMatrix MAbund, uVector Limits, ui nBins, uPMatrix MX, ui ht, ui len, int mode );
void  __vf  MUCols_distribution( uiPMatrix MAbund, uVector Limits, ui nBins, uPMatrix MX, ui ht, ui len, int mode );

/********  Operations involving two rows or two colums of one matrix  *****/

void   __vf  MURows_exchange( uPMatrix MA, ui ht, ui len,
                              ui i1, ui i2 );
void   __vf  MUCols_exchange( uPMatrix MA, ui ht, ui len,
                              ui i1, ui i2 );

/***************  Transposing and rotating a matrix **********************/

void  __vf  MUtranspose( uPMatrix MTr, uPMatrix MA,
                          ui htTr, ui lenTr );
void  __vf  MUrotate90(  uPMatrix MRot, uPMatrix MA, ui htRot, ui lenRot );
#define     MUrotate180( MRot, MA, htRot, lenRot ) \
                VU_rev( MRot, MA, (htRot)*(lenRot) )
void  __vf  MUrotate270( uPMatrix MRot, uPMatrix MA, ui htRot, ui lenRot );

      /*************  Input and Output  ****************/

void  __vf M_ifprint( FILE _VFAR *stream, void _VFAR *X, ui ht, ui len, unsigned linewidth, unsigned vers );
#define MUfprint( stream, MA0, ht, len, linewidth ) \
                    M_ifprint( stream, (void _VFAR *) (MA0), ht, len, linewidth, 5 )
#define MU_fprint( stream, MA, ht, len, linewidth ) \
                    MUfprint( stream, (MA)[0], ht, len, linewidth )
void  __vf M_icprint( void _VFAR *X, ui ht, ui len, unsigned vers );
#define MUcprint( MA0, ht, len ) M_icprint( (void _VFAR *) (MA0), ht, len, 5 )
#define MU_cprint( MA, ht, len ) MUcprint( (MA)[0], ht, len )
#define MUprint( MA0, ht, len )  M_ifprint( stdout, (void _VFAR *) (MA0), ht, len, 80, 5 )
#define MU_print( MA, ht, len )  MUprint( (MA)[0], ht, len )
  /*  MU_print, MU_cprint usable only for console applications! */

void __vf MUwrite( FILE _VFAR *stream, uPMatrix X, ui ht, ui len  );
void __vf MUread( uPMatrix X, ui ht, ui len, FILE _VFAR *stream );
#define MUstore( str, MA, ht, len ) VU_store( str, MA, (len)*(ht) )
#define MUrecall( MA, ht, len, str) VU_recall( MA, (len)*(ht), str)

#ifdef __cplusplus
} // end of extern "C"
#endif
#endif  /*  __MUSTD_H  */
