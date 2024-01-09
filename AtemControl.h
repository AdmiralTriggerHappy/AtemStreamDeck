#pragma once

#include "include/BMDSwitcherAPI.h"
#include "stdafx.h"
#include <comutil.h>
#include <windows.h>
//#include <atlbase.h>
#include <atlstr.h>
#include <cstring>
#include <list>
#include <string>
#include <locale>

using namespace std;

class MixEffectBlockMonitor;
class SwitcherMonitor;
class InputMonitor;

// Atem Control Class
class AtemControl
{
	// Construction
public:
	AtemControl();	// standard constructor
	~AtemControl();
	// Implementation
protected:
	void OnClose();

public:
	HRESULT Connect(CString _address);
	HRESULT Auto();
	HRESULT Cut();
	HRESULT FTB();
	string GetProductName();

private:
	HRESULT switcherConnected();
	void switcherDisconnected();
	BOOL						mMixerConnected = FALSE;
	CString						mProductName;
	IBMDSwitcherDiscovery*		mSwitcherDiscovery;
	IBMDSwitcher*				mSwitcher;
	IBMDSwitcherMixEffectBlock*	mMixEffectBlock;
	MixEffectBlockMonitor*		mMixEffectBlockMonitor;
	SwitcherMonitor*			mSwitcherMonitor;
	std::list<InputMonitor*>	mInputMonitors;
	BOOL						mMoveSliderDownwards;
	BOOL						mCurrentTransitionReachedHalfway;
};
