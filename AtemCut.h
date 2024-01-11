#pragma once

//#include "BMDSwitcherAPI.idl"
#include "MySettings.h"
#include "include\AtemControl.h"
#include <StreamDeckSDK/ESDAction.h>
#include <StreamDeckSDK/ESDLogger.h>
#include <StreamDeckSDK/ESDActionWithExternalState.h>
#include "include\BMDSwitcherAPI.h"

//private TSettings MySettings;
//IBMDSwitcherMixEffectBlock* mMixEffectBlock;

//class AtemCut final: public ESDActionWithExternalState(){

class AtemCut final : public ESDAction {
using ESDAction::ESDAction;
//Constrcution
public:
  AtemCut (AtemControl* _MixerHW,ESDConnectionManager* esd_connection,const std::string& action,  const std::string& context) : ESDAction(esd_connection, action, context)
  {
    MixerHW = _MixerHW;
  }
  //~AtemCut();
protected:

public:

  virtual void KeyDown(const nlohmann::json& settings);
  virtual void KeyUp(const nlohmann::json& settings);
  virtual void WillAppear(const nlohmann::json& settings);
  virtual void SendToPlugin(const nlohmann::json& message);

private:
AtemControl* MixerHW;


};
