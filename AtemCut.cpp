#pragma once

//#include "BMDSwitcherAPI.idl"
#include "AtemCut.h"

//private TSettings MySettings;
//IBMDSwitcherMixEffectBlock* mMixEffectBlock;

//class AtemCut final: public ESDActionWithExternalState(){


  void AtemCut::KeyDown(const nlohmann::json& settings)  {
    ESDLog("KeyDown");
  }

  void AtemCut::KeyUp(const nlohmann::json& settings)  {
    // Log in release and debug builds
    ESDLog("KeyUp");

    MixerHW->Cut();
    //mMixEffectBlock->PerformCut();

    ShowOK();
    // Only log in debug builds (C++20-style format strings):
    ESDDebug("Settings: {}", settings.dump());
  }

  void AtemCut::WillAppear(const nlohmann::json& settings)  {
    ESDLog("WillAppear");

  }

  void AtemCut::SendToPlugin(const nlohmann::json& message)  {
    ESDLog("Received message from property inspector: {}", message.dump());
  }




