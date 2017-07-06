/******************************************************************************
*
* Copyright (C) 2017 Allegro DVT2.  All rights reserved.
*
* Permission is hereby granted, free of charge, to any person obtaining a copy
* of this software and associated documentation files (the "Software"), to deal
* in the Software without restriction, including without limitation the rights
* to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
* copies of the Software, and to permit persons to whom the Software is
* furnished to do so, subject to the following conditions:
*
* The above copyright notice and this permission notice shall be included in
* all copies or substantial portions of the Software.
*
* Use of the Software is limited solely to applications:
* (a) running on a Xilinx device, or
* (b) that interact with a Xilinx device through a bus or interconnect.
*
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
* XILINX OR ALLEGRO DVT2 BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
* WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF
* OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
* SOFTWARE.
*
* Except as contained in this notice, the name of  Xilinx shall not be used
* in advertising or otherwise to promote the sale, use or other dealings in
* this Software without prior written authorization from Xilinx.
*
*
* Except as contained in this notice, the name of Allegro DVT2 shall not be used
* in advertising or otherwise to promote the sale, use or other dealings in
* this Software without prior written authorization from Allegro DVT2.
*
******************************************************************************/

/****************************************************************************
   -----------------------------------------------------------------------------
 **************************************************************************//*!
   \addtogroup lib_common
   @{
   \file
 *****************************************************************************/
#pragma once

#include "lib_common/HwScalingList.h"

/****************************************************************************/
static const int AL_AVC_ENC_SCL_ORDER_8x8[64] =
{
  0, 8, 16, 24,
  32, 40, 48, 56,
  1, 9, 17, 25,
  33, 41, 49, 57,
  2, 10, 18, 26,
  34, 42, 50, 58,
  3, 11, 19, 27,
  35, 43, 51, 59,
  4, 12, 20, 28,
  36, 44, 52, 60,
  5, 13, 21, 29,
  37, 45, 53, 61,
  6, 14, 22, 30,
  38, 46, 54, 62,
  7, 15, 23, 31,
  39, 47, 55, 63
};

/****************************************************************************/
static const int AL_HEVC_ENC_SCL_ORDER_8x8[64] =
{
  0, 8, 16, 24,
  32, 40, 48, 56,
  1, 9, 17, 25,
  33, 41, 49, 57,
  2, 10, 18, 26,
  34, 42, 50, 58,
  3, 11, 19, 27,
  35, 43, 51, 59,
  4, 12, 20, 28,
  36, 44, 52, 60,
  5, 13, 21, 29,
  37, 45, 53, 61,
  6, 14, 22, 30,
  38, 46, 54, 62,
  7, 15, 23, 31,
  39, 47, 55, 63
};

/****************************************************************************/
static const int AL_AVC_ENC_SCL_ORDER_4x4[16] =
{
  0, 4, 8, 12,
  1, 5, 9, 13,
  2, 6, 10, 14,
  3, 7, 11, 15
};

/****************************************************************************/
static const int AL_HEVC_ENC_SCL_ORDER_4x4[16] =
{
  0, 4, 8, 12,
  1, 5, 9, 13,
  2, 6, 10, 14,
  3, 7, 11, 15
};

/*************************************************************************//*!
   \brief Dump Hardware formated encoder scaling list into buffer of bytes
   \param[in]  pSclLst Pointer to the inverse scaling list coefficients
   \param[in]  pHwSclLst Pointer to the forward scaling list coefficients
   \param[out] pBuf Pointer to buffer that receives the scaling list
   matrices data
*****************************************************************************/
extern void AL_HEVC_WriteEncHwScalingList(AL_TSCLParam const* pSclLst, AL_THwScalingList* pHwSclLst, uint8_t* pBuf);
extern void AL_AVC_WriteEncHwScalingList(AL_TSCLParam const* pSclLst, AL_THwScalingList const* pHwSclLst, uint8_t* pBuf);

/*@}*/

