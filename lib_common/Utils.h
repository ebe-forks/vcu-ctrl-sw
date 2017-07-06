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
   \addtogroup lib_base
   @{
   \file


 *****************************************************************************/
#pragma once

#include "lib_rtos/types.h"
#include "lib_common/SliceConsts.h"
#include "lib_common/BufCommon.h"

#define NUMCORE_AUTO 0xff

/***************************************************************************/
static AL_INLINE int Clip3(int iVal, int iMin, int iMax)
{
  return ((iVal) < (iMin)) ? (iMin) : ((iVal) > (iMax)) ? (iMax) : (iVal);
}

/***************************************************************************/
static AL_INLINE uint32_t UMax(uint32_t uVal1, uint32_t uVal2)
{
  return ((uVal1) < (uVal2)) ? (uVal2) : (uVal1);
}

/***************************************************************************/
static AL_INLINE int Max(int iVal1, int iVal2)
{
  return ((iVal1) < (iVal2)) ? (iVal2) : (iVal1);
}

/***************************************************************************/
static AL_INLINE uint32_t UnsignedMax(uint32_t iVal1, uint32_t iVal2)
{
  return ((iVal1) < (iVal2)) ? (iVal2) : (iVal1);
}

/***************************************************************************/
static AL_INLINE size_t UnsignedMin(size_t iVal1, size_t iVal2)
{
  return ((iVal1) > (iVal2)) ? (iVal2) : (iVal1);
}

/***************************************************************************/
static AL_INLINE int Min(int iVal1, int iVal2)
{
  return ((iVal1) > (iVal2)) ? (iVal2) : (iVal1);
}

/***************************************************************************/
static AL_INLINE int Abs(int iVal)
{
  return ((iVal) > 0) ? (iVal) : (-(iVal));
}

/***************************************************************************/
static AL_INLINE int Sign(int iVal)
{
  return ((iVal) > 0) ? (1) : (((iVal) < 0) ? (-1) : (0));
}

/***************************************************************************/
static AL_INLINE int AbsDiff(int iVal1, int iVal2)
{
  return ((iVal1) > (iVal2)) ? ((iVal1) - (iVal2)) : ((iVal2) - (iVal1));
}

/***************************************************************************/
static AL_INLINE int RoundUp(int iVal, int iRnd)
{
  return (iVal + iRnd - 1) & (~(iRnd - 1));
}

AL_INLINE static AL_ECodec AL_GetCodec(AL_EProfile eProf)
{

  if(AL_IS_AVC(eProf))
    return AL_CODEC_AVC;
  return AL_CODEC_HEVC;
}

/*************************************************************************//*!
   \brief The GetMaxDPBSize function retrieves the maximum DBP size respect to the
   level constraint
   \param[in] iLevel Level of the current H264 stream
   \param[in] bConstrSet3 Used for the special level value 11
   \return return the maximum size of the DBP allowed by the specified level
*****************************************************************************/
uint32_t AL_AVC_GetMaxDPBSize(int iLevel, bool bConstrSet3);

/*************************************************************************//*!
   \brief This function retrieves the maximum DBP size respect to the
   level constraint
   \param[in] level_idc  Level of the current HEVC stream
   \param[in] uPictSizeY Size of picture luma component
   \return return the maximum size of the DBP allowed by the specified level
 ***************************************************************************/
uint8_t AL_HEVC_GetMaxDPBSize(uint8_t level_idc, uint32_t uPictSizeY);

/*************************************************************************//*!
   \brief This function checks if the current Nal Unit Type corresponds to an IDR
   picture respect to the AVC specification
   \param[in] eNUT Nal Unit Type
   \return true if it's an IDR nal unit type
   false otherwise
 ***************************************************************************/
bool AL_AVC_IsIDR(AL_ENut eNUT);

/*************************************************************************//*!
   \brief This function checks if the current Nal Unit Type corresponds to a Vcl NAL
   respect to the AVC specification
   \param[in] eNUT Nal Unit Type
   \return true if it's a VCL nal unit type
   false otherwise
 ***************************************************************************/
bool AL_AVC_IsVcl(AL_ENut eNUT);
/*************************************************************************//*!
    \brief This function checks if the current Nal Unit Type corresponds to an
           SLNR picture respect to the HEVC specification
    \param[in] eNUT Nal Unit Type
    \return true if it's an SLNR nal unit type
    false otherwise
 ***************************************************************************/
bool AL_HEVC_IsSLNR(AL_ENut eNUT);
/*************************************************************************//*!
   \brief This function checks if the current Nal Unit Type corresponds to an RADL,
   RASL or SLNR picture respect to the HEVC specification
   \param[in] eNUT Nal Unit Type
   \return true if it's an RASL, RADL or SLNR nal unit type
   false otherwise
 ***************************************************************************/
bool AL_HEVC_IsRASL_RADL_SLNR(AL_ENut eNUT);
/*************************************************************************//*!
   \brief This function checks if the current Nal Unit Type corresponds to a BLA
   picture respect to the HEVC specification
   \param[in] eNUT Nal Unit Type
   \return true if it's a BLA nal unit type
   false otherwise
 ***************************************************************************/
bool AL_HEVC_IsBLA(AL_ENut eNUT);

/*************************************************************************//*!
   \brief This function checks if the current Nal Unit Type corresponds to a CRA
   picture respect to the HEVC specification
   \param[in] eNUT Nal Unit Type
   \return true if it's a CRA nal unit type
   false otherwise
 ***************************************************************************/
bool AL_HEVC_IsCRA(AL_ENut eNUT);

/*************************************************************************//*!
   \brief This function checks if the current Nal Unit Type corresponds to an IDR
   picture respect to the HEVC specification
   \param[in] eNUT Nal Unit Type
   \return true if it's an IDR nal unit type
   false otherwise
 ***************************************************************************/
bool AL_HEVC_IsIDR(AL_ENut eNUT);

/*************************************************************************//*!
   \brief This function checks if the current Nal Unit Type corresponds to an RASL
   picture respect to the HEVC specification
   \param[in] eNUT Nal Unit Type
   \return true if it's an RASL nal unit type
   false otherwise
 ***************************************************************************/
bool AL_HEVC_IsRASL(AL_ENut eNUT);

/*************************************************************************//*!
   \brief This function checks if the current Nal Unit Type corresponds to a Vcl NAL
   respect to the HEVC specification
   \param[in] eNUT Nal Unit Type
   \return true if it's a VCL nal unit type
   false otherwise
 ***************************************************************************/
bool AL_HEVC_IsVcl(AL_ENut eNUT);

/***************************************************************************/
int ceil_log2(uint16_t n);

/***************************************************************************/
#define ROUND_POWER_OF_TWO(value, n) (((value) + (1 << ((n) - 1))) >> (n))

/***************************************************************************/
/*@}*/

