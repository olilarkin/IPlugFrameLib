#pragma once

#include "IPlug_include_in_plug_hdr.h"
#include "FrameLibPatch.h"
#include "FrameLib_FromHost.h"

const int kNumPrograms = 1;

enum EParams
{
  kGain = 0,
  kNumParams
};

using namespace iplug;
using namespace igraphics;

class IPlugFrameLib : public Plugin
{
public:
  IPlugFrameLib(const InstanceInfo& info);

#if IPLUG_DSP // All DSP methods and member variables should be within an IPLUG_DSP guard, should you want distributed UI
  void ProcessBlock(sample** inputs, sample** outputs, int nFrames) override;
  void OnReset() override;
  void OnParamChange(int paramIdx, EParamSource src, int sampleOffset) override;
#endif
  
private:
  FrameLib_FromHost::Proxy* mProxy;
  FrameLibPatch mPatch;
};
