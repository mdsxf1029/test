#include "TriggerCondition.h"

bool SpecialTrigger::CheckTrigger(const Interactable& interactable) const 
{
	return interactable.IsInteractable();
}
