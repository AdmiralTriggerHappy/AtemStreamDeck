#include "include\BMDSwitcherAPI.h"
#include <cstdio>
#include <map>
#include <string>
#include <utility>
#include <vector>

#include <conio.h>
#include <comutil.h>
#include <atlbase.h>
#include <windows.h>

#pragma comment(lib, "comsuppw.lib")


static const std::map<BMDSwitcherConnectToFailure, std::string> kConnectFailReasonCodes =
{
	{ bmdSwitcherConnectToFailureNoResponse,			"No response" },
	{ bmdSwitcherConnectToFailureIncompatibleFirmware,	"Incompatible firmware" },
	{ bmdSwitcherConnectToFailureCorruptData,			"Corrupt data" },
	{ bmdSwitcherConnectToFailureStateSync,				"State synchronisation failed" },
	{ bmdSwitcherConnectToFailureStateSyncTimedOut,		"State synchronisation timed-out" },
};

static const std::map<BMDSwitcherVideoMode, std::string> kSwitcherVideoModes =
{
	{ bmdSwitcherVideoMode525i5994NTSC,			"525i59.94 NTSC"},
	{ bmdSwitcherVideoMode625i50PAL,			"625i50 PAL"},
	{ bmdSwitcherVideoMode525i5994Anamorphic,	"525i59.94 Anamorphic"},
	{ bmdSwitcherVideoMode625i50Anamorphic,		"625i50 Anamorphic"},
	{ bmdSwitcherVideoMode720p50,				"HD 720p50"},
	{ bmdSwitcherVideoMode720p5994,				"HD 720p59.94"},
	{ bmdSwitcherVideoMode1080i50,				"HD 1080i50"},
	{ bmdSwitcherVideoMode1080i5994,			"HD 1080i59.94"},
	{ bmdSwitcherVideoMode1080i60,				"HD 1080i60"},
	{ bmdSwitcherVideoMode1080p2398,			"HD 1080p23.98"},
	{ bmdSwitcherVideoMode1080p24,				"HD 1080p24"},
	{ bmdSwitcherVideoMode1080p25,				"HD 1080p25"},
	{ bmdSwitcherVideoMode1080p2997,			"HD 1080p29.97"},
	{ bmdSwitcherVideoMode1080p30,				"HD 1080p30"},
	{ bmdSwitcherVideoMode1080p50,				"HD 1080p50"},
	{ bmdSwitcherVideoMode1080p5994,			"HD 1080p59.94"},
	{ bmdSwitcherVideoMode1080p60,				"HD 1080p60"},
	{ bmdSwitcherVideoMode4KHDp2398,			"UHD 2160p23.98"},
	{ bmdSwitcherVideoMode4KHDp24,				"UHD 2160p24"},
	{ bmdSwitcherVideoMode4KHDp25,				"UHD 2160p25"},
	{ bmdSwitcherVideoMode4KHDp2997,			"UHD 2160p29.97"},
	{ bmdSwitcherVideoMode4KHDp50,				"UHD 2160p50"},
	{ bmdSwitcherVideoMode4KHDp5994,			"UHD 2160p59.94"},
	{ bmdSwitcherVideoMode8KHDp2398,			"UHD 4320p23.98"},
	{ bmdSwitcherVideoMode8KHDp24,				"UHD 4320p24"},
	{ bmdSwitcherVideoMode8KHDp25,				"UHD 4320p25"},
	{ bmdSwitcherVideoMode8KHDp2997,			"UHD 4320p29.97"},
	{ bmdSwitcherVideoMode8KHDp50,				"UHD 4320p50"},
	{ bmdSwitcherVideoMode8KHDp5994,			"UHD 4320p59.94"},
};

static const std::map<BMDSwitcherPortType, std::string> kSwitcherPortTypes =
{
	{ bmdSwitcherPortTypeExternal,				"External" },
	{ bmdSwitcherPortTypeBlack,					"Black Video" },
	{ bmdSwitcherPortTypeColorBars,				"Color-Bars" },
	{ bmdSwitcherPortTypeColorGenerator,		"Color Generator" },
	{ bmdSwitcherPortTypeMediaPlayerFill,		"Media-Player Fill" },
	{ bmdSwitcherPortTypeMediaPlayerCut,		"Media-Player Cut" },
	{ bmdSwitcherPortTypeSuperSource,			"Super-Source" },
	{ bmdSwitcherPortTypeMixEffectBlockOutput,	"Mix-Effect Block Output" },
	{ bmdSwitcherPortTypeAuxOutput,				"Auxiliary Output" },
	{ bmdSwitcherPortTypeKeyCutOutput,			"Key Cut Output" },
};

static const std::vector<std::pair<GUID, std::string>> kSwitcherTransitionStyles =
{
	std::make_pair(__uuidof(IBMDSwitcherTransitionMixParameters),		"Mix"),
	std::make_pair(__uuidof(IBMDSwitcherTransitionDipParameters),		"Dip"),
	std::make_pair(__uuidof(IBMDSwitcherTransitionWipeParameters),		"Wipe"),
	std::make_pair(__uuidof(IBMDSwitcherTransitionDVEParameters),		"DVE"),
	std::make_pair(__uuidof(IBMDSwitcherTransitionStingerParameters),	"Stinger"),
};

static const std::map<BMDSwitcherExternalPortType, std::string> kSwitcherExternalPortTypes =
{
	{ bmdSwitcherExternalPortTypeSDI,			"SDI" },
	{ bmdSwitcherExternalPortTypeHDMI,			"HDMI" },
	{ bmdSwitcherExternalPortTypeComponent,		"Component" },
	{ bmdSwitcherExternalPortTypeComposite,		"Composite" },
	{ bmdSwitcherExternalPortTypeSVideo,		"S-Video" },
	{ bmdSwitcherExternalPortTypeXLR,			"XLR Audio" },
	{ bmdSwitcherExternalPortTypeAESEBU,		"AES EBU Audio" },
	{ bmdSwitcherExternalPortTypeRCA,			"RCA Audio" },
	{ bmdSwitcherExternalPortTypeInternal,		"Internal" },
	{ bmdSwitcherExternalPortTypeTSJack,		"TS Jack" },
	{ bmdSwitcherExternalPortTypeMADI,			"MADI" },
	{ bmdSwitcherExternalPortTypeTRS,			"TRS" },
};

static const std::map<BMDSwitcherAudioInputType, std::string> kSwitcherAudioInputTypes =
{
	{ bmdSwitcherAudioInputTypeEmbeddedWithVideo,	"Embedded with Video" },
	{ bmdSwitcherAudioInputTypeMediaPlayer,			"Media Player" },
	{ bmdSwitcherAudioInputTypeAudioIn,				"Audio input" },
};

static const std::map<BMDSwitcherFairlightAudioInputType, std::string> kSwitcherFairlightAudioInputTypes =
{
	{ bmdSwitcherFairlightAudioInputTypeEmbeddedWithVideo,	"Embedded with Video" },
	{ bmdSwitcherFairlightAudioInputTypeMediaPlayer,		"Media Player" },
	{ bmdSwitcherFairlightAudioInputTypeAudioIn,			"Audio input" },
	{ bmdSwitcherFairlightAudioInputTypeMADI,				"MADI input" },
};

static const std::vector<BMDSwitcherInputAvailability> kSwitcherInputAvailabilty =
{
	bmdSwitcherInputAvailabilityMixEffectBlock0,
	bmdSwitcherInputAvailabilityMixEffectBlock1,
	bmdSwitcherInputAvailabilityMixEffectBlock2,
	bmdSwitcherInputAvailabilityMixEffectBlock3,
	bmdSwitcherInputAvailabilityAuxOutputs,
	bmdSwitcherInputAvailabilityMultiView,
	bmdSwitcherInputAvailabilitySuperSourceArt,
	bmdSwitcherInputAvailabilitySuperSourceBox,
	bmdSwitcherInputAvailabilityInputCut,
};

void						get_switcher_inputs(const CComPtr<IBMDSwitcher>& switcher, std::vector<CComPtr<IBMDSwitcherInput>>& switcherInputs);
void						get_switcher_mix_effect_blocks(const CComPtr<IBMDSwitcher>& switcher, std::vector<CComPtr<IBMDSwitcherMixEffectBlock>>& mixEffectBlocks);

std::string					get_product_name(const CComPtr<IBMDSwitcher>& switcher);
int							get_usk_count_for_meb(const CComPtr<IBMDSwitcherMixEffectBlock>& mixEffectBlock);
std::vector<std::string>	get_transition_styles_for_meb(const CComPtr<IBMDSwitcherMixEffectBlock>& mixEffectBlock);
int							get_downstream_keyer_count(const CComPtr<IBMDSwitcher>& switcher);
int							get_input_type_count(const std::vector<CComPtr<IBMDSwitcherInput>>& switcherInputs, BMDSwitcherPortType portType);
int							get_media_pool_clip_count(const CComPtr<IBMDSwitcherMediaPool>& mediaPool);
int							get_media_pool_stills_count(const CComPtr<IBMDSwitcherStills>& stills);

bool						does_support_advanced_chroma_keyers(const std::vector<CComPtr<IBMDSwitcherMixEffectBlock>>& mixEffectBlocks);

void						print_supported_video_modes(const CComPtr<IBMDSwitcher>& switcher);
void						print_switcher_inputs(const std::vector<CComPtr<IBMDSwitcherInput>>& switcherInputs);
void						print_input_availability_matrix(const std::vector<CComPtr<IBMDSwitcherInput>>& switcherInputs, int mixEffectCount);
void						print_fairlight_audio_inputs(const CComPtr<IBMDSwitcherFairlightAudioMixer>& fairlightAudioMixer, std::vector<CComPtr<IBMDSwitcherInput>>& switcherInputs);
void						print_audio_inputs(const CComPtr<IBMDSwitcherAudioMixer>& audioMixer, std::vector<CComPtr<IBMDSwitcherInput>>& switcherInputs);
void						print_media_pool_stills(const CComPtr<IBMDSwitcherStills>& stills);
void						print_media_pool_clips(const CComPtr<IBMDSwitcherMediaPool>& mediaPool);
void						print_recording_drives(const CComPtr<IBMDSwitcherRecordAV>& switcherRecord);
void						print_hyperdecks(const CComPtr<IBMDSwitcher>& switcher);


const char* BSTRToCString(const CComBSTR& str)
{
	_bstr_t bstr(str);
	const size_t newSize = (bstr.length() + 1) * 2;
	char *retString = new char[newSize];

	strcpy_s(retString, newSize, (char *)bstr);

	return retString;
}

template<typename T>
std::string LookupString(const std::map<T, std::string>& stringMap, T index)
{
	std::string connectFailReasonStr;
	auto iter = stringMap.find(index);
	
	if (iter != stringMap.end())
		return iter->second;
	else
		return "Unknown";
}