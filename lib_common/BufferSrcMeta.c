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

#include "lib_rtos/lib_rtos.h"
#include "lib_common/BufferSrcMeta.h"
#include <assert.h>

static bool SrcMeta_Destroy(AL_TMetaData* pMeta)
{
  Rtos_Free(pMeta);
  return true;
}

AL_TSrcMetaData* AL_SrcMetaData_Create(int iWidth, int iHeight, AL_TPitches tPitches, AL_TOffsetYC tOffsetYC, TFourCC tFourCC)
{
  AL_TSrcMetaData* pMeta = Rtos_Malloc(sizeof(*pMeta));

  if(!pMeta)
    return NULL;

  pMeta->tMeta.eType = AL_META_TYPE_SOURCE;
  pMeta->tMeta.MetaDestroy = SrcMeta_Destroy;

  pMeta->iWidth = iWidth;
  pMeta->iHeight = iHeight;

  pMeta->tPitches.iLuma = tPitches.iLuma;
  pMeta->tPitches.iChroma = tPitches.iChroma;

  pMeta->tOffsetYC.iLuma = tOffsetYC.iLuma;
  pMeta->tOffsetYC.iChroma = tOffsetYC.iChroma;

  pMeta->tFourCC = tFourCC;

  return pMeta;
}

AL_TSrcMetaData* AL_SrcMetaData_Clone(AL_TSrcMetaData* pMeta)
{
  return AL_SrcMetaData_Create(pMeta->iWidth, pMeta->iHeight, pMeta->tPitches, pMeta->tOffsetYC, pMeta->tFourCC);
}

int AL_SrcMetaData_GetOffsetC(AL_TSrcMetaData* pMeta)
{
  assert(pMeta->tPitches.iLuma * pMeta->iHeight <= pMeta->tOffsetYC.iChroma);
  return pMeta->tOffsetYC.iChroma;
}

