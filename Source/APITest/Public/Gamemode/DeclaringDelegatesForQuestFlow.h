#pragma once

namespace QuestFlowDelegates
{

DECLARE_DELEGATE_TwoParams(OnQuestStartSignature, UTAQuestComponent*, UTAQuestComponent*);
DECLARE_DELEGATE_TwoParams(OnQuestEndSignature, UTAQuestComponent*, UTAQuestComponent*);

}  // namespace QuestFlowDelegates
