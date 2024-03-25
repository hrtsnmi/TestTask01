#pragma once

//class APawn*;

namespace QuestFlowDelegates
{

DECLARE_DELEGATE_TwoParams(OnQuestStartSignature, AController*, AController*);
DECLARE_DELEGATE_TwoParams(OnQuestEndSignature, AController*, AController*);

// Delegates forPlayerState
DECLARE_DELEGATE_RetVal(const FQuestData&, OnGetQuestDataSignature);
DECLARE_MULTICAST_DELEGATE_ThreeParams(OnSetQuestDataSignature, const FQuestData&, EQuestProgress , AActor*);


DECLARE_DELEGATE_RetVal(EQuestProgress, OnGetQuestProgressSignature);

}  // namespace QuestFlowDelegates
