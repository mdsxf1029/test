#include "TriggerCondition.h"

bool BasicTrigger::CheckTrigger(const Interactable& interactable) const
{
	return interactable.IsInteractable();
}

bool SpecialTrigger::CheckTrigger(const Interactable& interactable) const 
{
	return interactable.IsInteractable();
}
