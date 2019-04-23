/* uiMatObj.H

  object-oriented interface for OptiVec matrix functions
  of type "ui"

  This file is based on work done by Brian Dale, Case Western Reserve Univ.

  Copyright (c) 1996-2017 by OptiCode
  All Rights Reserved.
*/

#ifndef UIMATOBJ_H

#include <VecObj.h>

#if defined _WIN64
   #include <uqMatObj.h>
#else
   #include <uMatObj.h>
#endif

#define UIMATOBJ_H
#endif //UIMATOBJ_H
