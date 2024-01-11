#pragma once

#include "BMDSwitcherAPI.h"
#include "stdafx.h"
//#include "afx.h"
#include <comutil.h>
#include <windows.h>
//#include <atlbase.h>
#include <atlstr.h>
#include <cstring>
#include <list>
#include <string>
#include <locale>
#include <atlconv.h>

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

	struct inputDetails {
		BMDSwitcherInputId inputID;
		wstring shortName;
		wstring LongName;
		BMDSwitcherPortType portType;
		wstring HRPortType;

	};
	// Implementation
protected:
	void OnClose();

private:

	HRESULT switcherConnected();
	void switcherDisconnected();
	BOOL						mMixerConnected = FALSE;
	CString						mProductName;
	IBMDSwitcherDiscovery* mSwitcherDiscovery;
	IBMDSwitcher* mSwitcher;
	IBMDSwitcherMixEffectBlock* mMixEffectBlock;
	MixEffectBlockMonitor* mMixEffectBlockMonitor;
	SwitcherMonitor* mSwitcherMonitor;
	std::list<InputMonitor*>	mInputMonitors;
	BOOL						mMoveSliderDownwards;
	BOOL						mCurrentTransitionReachedHalfway;
	std::list<inputDetails>  inputList;

public:


	HRESULT Connect(CString _address);
	std::list<inputDetails> getListInputList();
	HRESULT Auto();
	HRESULT Cut();
	HRESULT FTB();
	HRESULT SetPreview(BMDSwitcherInputId _inputID);
	wstring GetProductName();
	HRESULT SetProgram(BMDSwitcherInputId _inputID);
};
