#pragma once

#include "AtemControl.h"
#include "AtemCut.h"

#include "include\BMDSwitcherAPI.h"

//#include <cstdio>
//#include <map>
//#include <string>
//#include <utility>
//#include <vector>

//#include <conio.h>
//#include <comutil.h>
//#include <atlbase.h>

//#pragma comment(lib, "comsuppw.lib")

#include <StreamDeckSDK/ESDPlugin.h>
#include <StreamDeckSDK/ESDLogger.h>
//#include <StreamDeckSDK/ESDConnectionManager.h>

class AtemStreamDeckPlugin final : public ESDPlugin
{
public:
  using ESDPlugin::ESDPlugin;

  virtual std::shared_ptr<ESDAction> GetOrCreateAction(
      const std::string &action,
      const std::string &context) override
  {
    auto it = mActions.find(context);
    if (it != mActions.end())
    {
      return it->second;
    }

    HRESULT result; 
  CString address("192.168.1.53");

  AtemControl* MixerHW = new AtemControl();
  result = MixerHW->Connect(address);
  if(result==S_OK)
  {
  string outputString = MixerHW->GetProductName();
  ESDLog("Connection to ATEM successful" + outputString);
  };
    ESDDebug("Loaded fine");

    if (action == "com.admiraltriggerhappy.atemcontrol.atemcut")
    {
      auto impl = std::make_shared<AtemCut>(MixerHW,
          mConnectionManager,
          action,
          context);
      mActions.emplace(context, impl);
      return impl;
    }

    ESDLog("Asked to get or create unknown action: {}", action);
    return nullptr;
  }

  // Overriding from ESDBasePlugin
  virtual void DidReceiveGlobalSettings(
      const nlohmann::json &payload) override
  {
    ESDLog("Received global settings");
    ESDDebug("Global settings: {}", payload.dump());

   
  


    for (const auto &action : mActions)
    {
      // ... then pass it on to each action, e.g.:
      // action->setApplicationConnection(myConnectionObject);
      //action.second->setMixBlock(MixerHW);
      
    }
  }

private:
  std::map<std::string, std::shared_ptr<AtemCut>> mActions;
};
