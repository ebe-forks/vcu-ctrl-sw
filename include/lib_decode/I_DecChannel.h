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
   \addtogroup lib_decode_hls
   @{
   \file
 *****************************************************************************/

#pragma once

#include "lib_rtos/types.h"

#include "lib_common/MemDesc.h"

#include "lib_common_dec/StartCodeParam.h"
#include "lib_common_dec/DecChanParam.h"
#include "lib_common_dec/DecSliceParam.h"
#include "lib_common_dec/DecPicParam.h"

#define AL_INVALID_CHANNEL (AL_HANDLE)0xff
#define AL_UNINITIALIZED_CHANNEL (AL_HANDLE)0xfe

/****************************************************************************/
typedef struct
{
  void (* func)(void* pUserParam, AL_TDecPicStatus* pPicStatus);
  void* userParam;
}AL_CB_EndFrameDecoding;

typedef struct
{
  void (* func)(void* pUserParam, AL_TScStatus* pScdStatus);
  void* userParam;
}AL_CB_EndStartCode;

typedef struct
{
  void (* func)(void* pUserParam);
  void* userParam;
}AL_CB_DestroyChannel;


typedef struct AL_t_IDecChannelCallbacks
{
  AL_CB_EndFrameDecoding endFrameDecodingCB;
  AL_CB_DestroyChannel destroyChannelCB;
}AL_TIDecChannelCallbacks;

/****************************************************************************/
typedef struct AL_t_IDecChannelVtable AL_TIDecChannelVtable;

typedef struct AL_t_IDecChannel
{
  const AL_TIDecChannelVtable* vtable;
}AL_TIDecChannel;

typedef struct AL_t_IDecChannelVtable
{
  void (* Destroy)(AL_TIDecChannel* pDecChannel);
  bool (* Configure)(AL_TIDecChannel* pDecChannel, AL_TDecChanParam* pChParam, AL_TIDecChannelCallbacks* pCBs);
  void (* SearchSC)(AL_TIDecChannel* pDecChannel, AL_TScParam* pScParam, AL_TScBufferAddrs* pBufferAddrs, AL_CB_EndStartCode callback);
  void (* DecodeOneFrame)(AL_TIDecChannel* pDecChannel, AL_TDecPicParam* pPictParam, AL_TDecPicBufferAddrs* pPictAddrs, TMemDesc* pSliceParams);
  void (* DecodeOneSlice)(AL_TIDecChannel* pDecChannel, AL_TDecPicParam* pPictParam, AL_TDecPicBufferAddrs* pPictAddrs, TMemDesc* pSliceParams);

}AL_TIDecChannelVtable;

/*************************************************************************//*!
   \brief De-initializes the scheduler
   \return return true
*****************************************************************************/
static inline
void AL_IDecChannel_Destroy(AL_TIDecChannel* pThis)
{
  return pThis->vtable->Destroy(pThis);
}

/*************************************************************************//*!
   \brief Channel creation
   \param[in] pChParam       Pointer to the channel parameter
   \param[in] pfnDecCallBack User CallBack which will be called after each frame decoding
   \param[in] pUserParam     User CallBack parameter
   \return return the channel ID if the creation is successfull
              255 otherwise(invalide channel ID)
*****************************************************************************/
static inline
bool AL_IDecChannel_Configure(AL_TIDecChannel* pThis, AL_TDecChanParam* pChParam, AL_TIDecChannelCallbacks* pCBs)
{
  return pThis->vtable->Configure(pThis, pChParam, pCBs);
}

/*************************************************************************//*!
   \brief Asks the scheduler to process a start code detection
   \param[in]  pScParam     Pointer to the start code detector parameters
   \param[in]  pBufferAddrs Pointer to the start code detectors buffers
   \param[in] pfnScdCallBack User CallBack which will be called after each start code searching
   \param[in] pUserParam     User CallBack parameter
   \return return true
*****************************************************************************/
static inline
void AL_IDecChannel_SearchSC(AL_TIDecChannel* pThis, AL_TScParam* pScParam, AL_TScBufferAddrs* pBufferAddrs, AL_CB_EndStartCode callback)
{
  return pThis->vtable->SearchSC(pThis, pScParam, pBufferAddrs, callback);
}

/*************************************************************************//*!
   \brief Asks the scheduler to process a frame decoding
   \param[in] hChannel    Channel identifier
   \param[in] pPictParam  Pointer to the picture parameters structure
   \param[in] pSliceParam Pointer to the slice parameters list structure
   \return return true if the decoding launch is successfull
              false otherwise
*****************************************************************************/
static inline
void AL_IDecChannel_DecodeOneFrame(AL_TIDecChannel* pThis, AL_TDecPicParam* pPictParam, AL_TDecPicBufferAddrs* pPictAddrs, TMemDesc* pSliceParams)
{
  return pThis->vtable->DecodeOneFrame(pThis, pPictParam, pPictAddrs, pSliceParams);
}

/*************************************************************************//*!
   \brief Asks the scheduler to process a frame decoding
   \param[in] hChannel    Channel identifier
   \param[in] pPictParam  Pointer to the picture parameters structure
   \param[in] pSliceParam Pointer to the slice parameters list structure
   \return return true if the decoding launch is successfull
              false otherwise
*****************************************************************************/
static inline
void AL_IDecChannel_DecodeOneSlice(AL_TIDecChannel* pThis, AL_TDecPicParam* pPictParam, AL_TDecPicBufferAddrs* pPictAddrs, TMemDesc* pSliceParams)
{
  return pThis->vtable->DecodeOneSlice(pThis, pPictParam, pPictAddrs, pSliceParams);
}

/*@}*/

