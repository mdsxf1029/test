#pragma once
#ifndef TRIGGER_H
#define TRIGGER_H

#include "Interaction.h"

// 普通触发
class BasicTrigger 
{
public:
	virtual bool CheckTrigger(const Interactable& interactable) const = 0;
};

// 特殊触发
class SpecialTrigger : public BasicTrigger 
{
public:
	bool CheckTrigger(const Interactable& interactable) const override;
};

#endif // TRIGGER_H
