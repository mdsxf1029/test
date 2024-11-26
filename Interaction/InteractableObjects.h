#pragma once
#ifndef INTERACTABLE_OBJECTS_H
#define INTERACTABLE_OBJECTS_H

#include "Interaction.h"

// 物品交互类
class InteractableObjects : public Interactable 
{
private:
    string type;
    string name;
public:
    InteractableObjects(const string& name) : name(name) {}
    void Interact() override;                   // 实现交互逻辑
    bool IsInteractable() const override { return true; }
    string GetType() const override { return "Object"; }
    string GetName() const override { return name; }
};

#endif // INTERACTABLE_OBJECTS_H
