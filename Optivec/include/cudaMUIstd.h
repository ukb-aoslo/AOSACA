/*  cudaMUIstd.h

  matrix management functions:
  manipulations on matrices of data type "ui"

  Copyright (c) 1996-2017 by OptiCode - Dr. Martin Sander Software Dev.
  All Rights Reserved.
*/

#if !defined( __CUDAMUISTD_H )
#define __CUDAMUISTD_H

#if defined( _WIN64 )
   #if !defined( __CUDAMUQSTD_H )
      #include <cudaMUQstd.h>
   #endif
   #define cudaMUI_matrix          cudaMUQ_matrix
   #define cudaMUI_matrix0         cudaMUQ_matrix0
   #define cudaMUI_Pelement        cudaMUQ_Pelement
   #define cudaMUI_setElement      cudaMUQ_setElement
   #define cudaMUI_getElement      cudaMUQ_getElement
   #define cusdMUI_setElement      cusdMUQ_setElement
   #define cusdMUI_getElement      cusdMUQ_getElement
   #define cudaMUI_element         cudaMUQ_element
   #define cudaMUI_equ0            cudaMUQ_equ0
   #define cudaMUI_equ1            cudaMUQ_equ1
   #define cudaMUI_random          cudaMUQ_random
   #define cudaMUI_outerprod       cudaMUQ_outerprod
   #define cudaMUI_Row_equ0        cudaMUQ_Row_equ0
   #define cudaMUI_Col_equ0        cudaMUQ_Col_equ0
   #define cudaMUI_Dia_equ0        cudaMUQ_Dia_equ0
   #define cudaMUI_Row_equC        cudaMUQ_Row_equC
   #define cudaMUI_Col_equC        cudaMUQ_Col_equC
   #define cudaMUI_Dia_equC        cudaMUQ_Dia_equC
   #define cudaMUI_Row_equV        cudaMUQ_Row_equV
   #define cudaMUI_Col_equV        cudaMUQ_Col_equV
   #define cudaMUI_Dia_equV        cudaMUQ_Dia_equV
   #define cudaMUI_Trd_equM        cudaMUQ_Trd_equM
   #define cudaMUI_Trd_extract     cudaMUQ_Trd_extract
   #define cudaMUI_equM            cudaMUQ_equM
   #define cudaMUI_equMhost        cudaMUQ_equMhost
   #define MUI_equMdevice          MUQ_equMdevice
   #define cudaMUI_UequL           cudaMUQ_UequL
   #define cudaMUI_LequU           cudaMUQ_LequU
   #define cudaM_UBtoUI            cudaM_UBtoUQ
   #define cudaM_UStoUI            cudaM_UStoUQ
   #define cudaM_UtoUI             cudaM_UtoUQ
   #define cudaM_ULtoUI            cudaM_ULtoUQ
   #define cudaM_UQtoUI            cudaMUQ_equM
   #define cudaM_UItoUB            cudaM_UQtoUB
   #define cudaM_UItoUS            cudaM_UQtoUS
   #define cudaM_UItoU             cudaM_UQtoU
   #define cudaM_UItoUL            cudaM_UQtoUL
   #define cudaM_UItoUQ            cudaMUQ_equM
   #define cudaM_UItoF             cudaM_UQtoF
   #define cudaM_UItoD             cudaM_UQtoD
   #define cudaM_UItoE             cudaM_UQtoE
   #define cudaMUI_submatrix       cudaMUQ_submatrix
   #define cudaMUI_submatrix_equM  cudaMUQ_submatrix_equM
   #define cudaMUI_equMblock       cudaMUQ_equMblock
   #define cudaMUI_block_equM      cudaMUQ_block_equM
   #define cudaMUI_equMblockT      cudaMUQ_equMblockT
   #define cudaMUI_block_equMT     cudaMUQ_block_equMT
   #define cudaMUI_Row_extract     cudaMUQ_Row_extract
   #define cudaMUI_Col_extract     cudaMUQ_Col_extract
   #define cudaMUI_Dia_extract     cudaMUQ_Dia_extract
   #define cudaMUI_Row_delete      cudaMUQ_Row_delete
   #define cudaMUI_Col_delete      cudaMUQ_Col_delete
   #define cudaMUI_Row_insert      cudaMUQ_Row_insert
   #define cudaMUI_Col_insert      cudaMUQ_Col_insert
   #define cudaMUI_Rows_max        cudaMUQ_Rows_max
   #define cudaMUI_Cols_max        cudaMUQ_Cols_max
   #define cudaMUI_Dia_max         cudaMUQ_Dia_max
   #define cudaMUI_Rows_min        cudaMUQ_Rows_min
   #define cudaMUI_Cols_min        cudaMUQ_Cols_min
   #define cudaMUI_Dia_min         cudaMUQ_Dia_min
   #define cudaMUI_Rows_rotate     cudaMUQ_Rows_rotate
   #define cudaMUI_Cols_rotate     cudaMUQ_Cols_rotate
   #define cudaMUI_Rows_rotate_buf cudaMUQ_Rows_rotate_buf
   #define cudaMUI_Cols_rotate_buf cudaMUQ_Cols_rotate_buf
   #define cudaMUI_Rows_reflect    cudaMUQ_Rows_reflect
   #define cudaMUI_Cols_reflect    cudaMUQ_Cols_reflect
   #define cudaMUI_Rows_rev        cudaMUQ_Rows_rev
   #define cudaMUI_Cols_rev        cudaMUQ_Cols_rev
   #define cudaMUI_Rows_exchange   cudaMUQ_Rows_exchange
   #define cudaMUI_Cols_exchange   cudaMUQ_Cols_exchange
   #define cudaMUI_transpose       cudaMUQ_transpose
   #define cudaMUI_transpose_buf   cudaMUQ_transpose_buf
   #define cudaMUI_rotate90        cudaMUQ_rotate90
   #define cudaMUI_rotate180       cudaMUQ_rotate180
   #define cudaMUI_rotate270       cudaMUQ_rotate270
   #define cudaMUI_fprint          cudaMUQ_fprint
   #define cudaMUI_print           cudaMUQ_print
   #define cudaMUI_cprint          cudaMUQ_cprint
   #define cudaMUI_read            cudaMUQ_read
   #define cudaMUI_write           cudaMUQ_write
   #define cudaMUI_store           cudaMUQ_store
   #define cudaMUI_recall          cudaMUQ_recall
   #define cudaMUI_fprint_buf      cudaMUQ_fprint_buf
   #define cudaMUI_print_buf       cudaMUQ_print_buf
   #define cudaMUI_cprint_buf      cudaMUQ_cprint_buf
   #define cudaMUI_read_buf        cudaMUQ_read_buf
   #define cudaMUI_write_buf       cudaMUQ_write_buf
   #define cudaMUI_store_buf       cudaMUQ_store_buf
   #define cudaMUI_recall_buf      cudaMUQ_recall_buf
#else   /* Win32 only  */
   #if !defined( __CUDAMUSTD_H )
      #include <cudaMUstd.h>
   #endif
   #define cudaMUI_matrix          cudaMU_matrix
   #define cudaMUI_matrix0         cudaMU_matrix0
   #define cudaMUI_Pelement        cudaMU_Pelement
   #define cudaMUI_element         cudaMU_element
   #define cudaMUI_setElement      cudaMU_setElement
   #define cudaMUI_getElement      cudaMU_getElement
   #define cusdMUI_setElement      cusdMU_setElement
   #define cusdMUI_getElement      cusdMU_getElement
   #define cudaMUI_equ0            cudaMU_equ0
   #define cudaMUI_equ1            cudaMU_equ1
   #define cudaMUI_random          cudaMU_random
   #define cudaMUI_outerprod       cudaMU_outerprod
   #define cudaMUI_Row_equ0        cudaMU_Row_equ0
   #define cudaMUI_Col_equ0        cudaMU_Col_equ0
   #define cudaMUI_Dia_equ0        cudaMU_Dia_equ0
   #define cudaMUI_Row_equC        cudaMU_Row_equC
   #define cudaMUI_Col_equC        cudaMU_Col_equC
   #define cudaMUI_Dia_equC        cudaMU_Dia_equC
   #define cudaMUI_Row_equV        cudaMU_Row_equV
   #define cudaMUI_Col_equV        cudaMU_Col_equV
   #define cudaMUI_Dia_equV        cudaMU_Dia_equV
   #define cudaMUI_Trd_equM        cudaMU_Trd_equM
   #define cudaMUI_Trd_extract     cudaMU_Trd_extract
   #define cudaMUI_equM            cudaMU_equM
   #define cudaMUI_equMhost        cudaMU_equMhost
   #define MUI_equMdevice          MU_equMdevice
   #define cudaMUI_UequL           cudaMU_UequL
   #define cudaMUI_LequU           cudaMU_LequU
   #define cudaM_UBtoUI            cudaM_UBtoU
   #define cudaM_UStoUI            cudaM_UStoU
   #define cudaM_UtoUI             cudaM_UtoU
   #define cudaM_ULtoUI            cudaM_ULtoU
   #define cudaM_UItoUB            cudaM_UtoUB
   #define cudaM_UItoUS            cudaM_UtoUS
   #define cudaM_UItoU             cudaM_UtoU
   #define cudaM_UItoUL            cudaM_UtoUL
   #define cudaM_UItoF             cudaM_UtoF
   #define cudaM_UItoD             cudaM_UtoD
   #define cudaM_UItoE             cudaM_UtoE
   #define cudaMUI_submatrix       cudaMU_submatrix
   #define cudaMUI_submatrix_equM  cudaMU_submatrix_equM
   #define cudaMUI_equMblock       cudaMU_equMblock
   #define cudaMUI_block_equM      cudaMU_block_equM
   #define cudaMUI_equMblockT      cudaMU_equMblockT
   #define cudaMUI_block_equMT     cudaMU_block_equMT
   #define cudaMUI_Row_extract     cudaMU_Row_extract
   #define cudaMUI_Col_extract     cudaMU_Col_extract
   #define cudaMUI_Dia_extract     cudaMU_Dia_extract
   #define cudaMUI_Row_delete      cudaMU_Row_delete
   #define cudaMUI_Col_delete      cudaMU_Col_delete
   #define cudaMUI_Row_insert      cudaMU_Row_insert
   #define cudaMUI_Col_insert      cudaMU_Col_insert
   #define cudaMUI_Rows_max        cudaMU_Rows_max
   #define cudaMUI_Cols_max        cudaMU_Cols_max
   #define cudaMUI_Dia_max         cudaMU_Dia_max
   #define cudaMUI_Rows_min        cudaMU_Rows_min
   #define cudaMUI_Cols_min        cudaMU_Cols_min
   #define cudaMUI_Dia_min         cudaMU_Dia_min
   #define cudaMUI_Rows_rotate     cudaMU_Rows_rotate
   #define cudaMUI_Cols_rotate     cudaMU_Cols_rotate
   #define cudaMUI_Rows_rotate_buf cudaMU_Rows_rotate_buf
   #define cudaMUI_Cols_rotate_buf cudaMU_Cols_rotate_buf
   #define cudaMUI_Rows_reflect    cudaMU_Rows_reflect
   #define cudaMUI_Cols_reflect    cudaMU_Cols_reflect
   #define cudaMUI_Rows_rev        cudaMU_Rows_rev
   #define cudaMUI_Cols_rev        cudaMU_Cols_rev
   #define cudaMUI_Rows_exchange   cudaMU_Rows_exchange
   #define cudaMUI_Cols_exchange   cudaMU_Cols_exchange
   #define cudaMUI_transpose       cudaMU_transpose
   #define cudaMUI_transpose_buf   cudaMU_transpose_buf
   #define cudaMUI_rotate90        cudaMU_rotate90
   #define cudaMUI_rotate180       cudaMU_rotate180
   #define cudaMUI_rotate270       cudaMU_rotate270
   #define cudaMUI_fprint          cudaMU_fprint
   #define cudaMUI_print           cudaMU_print
   #define cudaMUI_cprint          cudaMU_cprint
   #define cudaMUI_read            cudaMU_read
   #define cudaMUI_write           cudaMU_write
   #define cudaMUI_store           cudaMU_store
   #define cudaMUI_recall          cudaMU_recall
   #define cudaMUI_fprint_buf      cudaMU_fprint_buf
   #define cudaMUI_print_buf       cudaMU_print_buf
   #define cudaMUI_cprint_buf      cudaMU_cprint_buf
   #define cudaMUI_read_buf        cudaMU_read_buf
   #define cudaMUI_write_buf       cudaMU_write_buf
   #define cudaMUI_store_buf       cudaMU_store_buf
   #define cudaMUI_recall_buf      cudaMU_recall_buf
#endif  /* Win64 or Win32  */

#endif  /*  __CUDAMUISTD_H  */
