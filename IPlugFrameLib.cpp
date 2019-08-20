#include "IPlugFrameLib.h"
#include "IPlug_include_in_plug_src.h"
#include "IControls.h"

IPlugFrameLib::IPlugFrameLib(const InstanceInfo& info)
: Plugin(info, MakeConfig(kNumParams, kNumPrograms))
, mPatch(mProxy = new FrameLib_FromHost::Proxy(false))
{
  GetParam(kGain)->InitDouble("Gain", 0., 0., 100.0, 0.01, "%");

#if IPLUG_EDITOR // All UI methods and member variables should be within an IPLUG_EDITOR guard, should you want distributed UI
  mMakeGraphicsFunc = [&]() {
    return MakeGraphics(*this, PLUG_WIDTH, PLUG_HEIGHT, PLUG_FPS, 1.);
  };
  
  mLayoutFunc = [&](IGraphics* pGraphics) {
    pGraphics->AttachCornerResizer(EUIResizerMode::Scale, false);
    pGraphics->AttachPanelBackground(COLOR_GRAY);
    pGraphics->LoadFont("Roboto-Regular", ROBOTO_FN);
    const IRECT b = pGraphics->GetBounds();

  };
#endif
}

#if IPLUG_DSP
void IPlugFrameLib::ProcessBlock(sample** inputs, sample** outputs, int nFrames)
{
  mPatch.process(inputs, outputs, nFrames);
}

void IPlugFrameLib::OnReset()
{
  mPatch.reset(GetSampleRate(), GetBlockSize());
}

void IPlugFrameLib::OnParamChange(int paramIdx, EParamSource src, int sampleOffset)
{
  double value = GetParam(0)->Value();
  //mProxy->sendFromHost(5, &value, 1);
}
#endif
