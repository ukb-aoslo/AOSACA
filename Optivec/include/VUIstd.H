/*  VUIstd.h

  vector management functions for data type "ui"
  ("unsigned index" = size_t, the data type for indexing and addressing).

  Copyright (c) 1996-2017 by OptiCode - Dr. Martin Sander Software Dev.
  All Rights Reserved.
*/

#ifndef __VUISTD_H
#define __VUISTD_H

#if defined _WIN64
   #if !defined( __VUQSTD_H )
      #include <VUQstd.h>
   #endif
   #define VUI_vector            VUQ_vector
   #define VUI_vector0           VUQ_vector0
   #define VUI_vector_dbg        VUQ_vector_dbg
   #define VUI_vector0_dbg       VUQ_vector0_dbg
   #define VUI_Pelement          VUQ_Pelement
   #define VUI_element           VUQ_element
   #define VUI_getElement        VUQ_getElement
   #define VUI_setElement        VUQ_setElement
   #define VUI_equ0              VUQ_equ0
   #define VUI_equC              VUQ_equC
   #define VUI_equV              VUQ_equV
   #define VUI_ramp              VUQ_ramp
   #define VUI_randomLC          VUQ_randomLC
   #define VUI_random            VUQ_random
   #define V_UItoU               V_UQtoU
   #define V_UtoUI               V_UtoUQ
   #define V_UItoUB              V_UQtoUB
   #define V_UBtoUI              V_UBtoUQ
   #define V_UItoUS              V_UQtoUS
   #define V_UStoUI              V_UStoUQ
   #define V_ULtoUI              V_ULtoUQ
   #define V_UItoUL              V_UQtoUL
   #define V_UQtoUI              VUQ_equV
   #define V_UItoUQ              VUQ_equV
   #define V_UItoF               V_UQtoF
   #define V_UItoD               V_UQtoD
   #define V_UItoE               V_UQtoE
   #define VUI_reflect           VUQ_reflect
   #define VUI_rev               VUQ_rev
   #define VUI_rotate            VUQ_rotate
   #define VUI_delete            VUQ_delete
   #define VUI_insert            VUQ_insert
   #define VUI_sort              VUQ_sort
   #define VUI_sortind           VUQ_sortind
   #define VUI_subvector         VUQ_subvector
   #define VUI_subvector_equC    VUQ_subvector_equC
   #define VUI_subvector_equV    VUQ_subvector_equV
   #define VUI_indpick           VUQ_indpick
   #define VUI_indput            VUQ_indput
   #define VUI_searchC           VUQ_searchC
   #define VUI_searchV           VUQ_searchV
   #define VUI_sum               VUQ_sum
   #define VUI_runsum            VUQ_runsum
   #define VUI_fsum              VUQ_fsum
   #define VUI_mean              VUQ_mean
   #define VUI_max               VUQ_max
   #define VUI_min               VUQ_min
   #define VUI_maxind            VUQ_maxind
   #define VUI_minind            VUQ_minind
   #define VUI_runmax            VUQ_runmax
   #define VUI_runmin            VUQ_runmin
   #define VUI_iselementC        VUQ_iselementC
   #define VUI_iselementV        VUQ_iselementV
   #define VUI_distribution      VUQ_distribution
   #define VUI_fprint            VUQ_fprint
   #define VUI_cprint            VUQ_cprint
   #define VUI_print             VUQ_print
   #define VUI_setRadix          VUQ_setRadix
   #define VUI_read              VUQ_read
   #define VUI_write             VUQ_write
   #define VUI_nread             VUQ_nread
   #define VUI_nwrite            VUQ_nwrite
   #define VUI_setWriteFormat    VUQ_setWriteFormat
   #define VUI_setWriteSeparate  VUQ_setWriteSeparate
   #define VUI_setNWriteSeparate VUQ_setNWriteSeparate
   #define VUI_store             VUQ_store
   #define VUI_recall            VUQ_recall
#else   /* Win32  */
   #if !defined( __VUSTD_H )
      #include <VUstd.h>
   #endif
   #define VUI_vector            VU_vector
   #define VUI_vector0           VU_vector0
   #define VUI_vector_dbg        VU_vector_dbg
   #define VUI_vector0_dbg       VU_vector0_dbg
   #define VUI_Pelement          VU_Pelement
   #define VUI_element           VU_element
   #define VUI_getElement        VU_getElement
   #define VUI_setElement        VU_setElement
   #define VUI_equ0              VU_equ0
   #define VUI_equC              VU_equC
   #define VUI_equV              VU_equV
   #define VUI_ramp              VU_ramp
   #define VUI_randomLC          VU_randomLC
   #define VUI_random            VU_random
   #define V_UItoU               VU_equV
   #define V_UtoUI               VU_equV
   #define V_UItoUB              V_UtoUB
   #define V_UBtoUI              V_UBtoU
   #define V_UItoUS              V_UtoUS
   #define V_UStoUI              V_UStoU
   #define V_ULtoUI              V_ULtoU
   #define V_UItoUL              V_UtoUL
   #define V_UItoF               V_UtoF
   #define V_UItoD               V_UtoD
   #define V_UItoE               V_UtoE
   #define VUI_reflect           VU_reflect
   #define VUI_rev               VU_rev
   #define VUI_rotate            VU_rotate
   #define VUI_delete            VU_delete
   #define VUI_insert            VU_insert
   #define VUI_sort              VU_sort
   #define VUI_sortind           VU_sortind
   #define VUI_subvector         VU_subvector
   #define VUI_subvector_equC    VU_subvector_equC
   #define VUI_subvector_equV    VU_subvector_equV
   #define VUI_indpick           VU_indpick
   #define VUI_indput            VU_indput
   #define VUI_searchC           VU_searchC
   #define VUI_searchV           VU_searchV
   #define VUI_sum               VU_sum
   #define VUI_runsum            VU_runsum
   #define VUI_fsum              VU_fsum
   #define VUI_mean              VU_mean
   #define VUI_max               VU_max
   #define VUI_min               VU_min
   #define VUI_maxind            VU_maxind
   #define VUI_minind            VU_minind
   #define VUI_runmax            VU_runmax
   #define VUI_runmin            VU_runmin
   #define VUI_iselementC        VU_iselementC
   #define VUI_iselementV        VU_iselementV
   #define VUI_distribution      VU_distribution
   #define VUI_ifprint           VU_ifprint
   #define VUI_fprint            VU_fprint
   #define VUI_cprint            VU_cprint
   #define VUI_print             VU_print
   #define VUI_setRadix          VU_setRadix
   #define VUI_read              VU_read
   #define VUI_write             VU_write
   #define VUI_nread             VU_nread
   #define VUI_nwrite            VU_nwrite
   #define VUI_setWriteFormat    VU_setWriteFormat
   #define VUI_setWriteSeparate  VU_setWriteSeparate
   #define VUI_setNWriteSeparate VU_setNWriteSeparate
   #define VUI_store             VU_store
   #define VUI_recall            VU_recall
#endif

#endif /* __VUISTD_H  */

