#pragma once
#ifndef NPC_H
#define NPC_H

#include <string>
#include <string.h>


const string PRINCESS = "PRINCESS";//公主
const string KING = "KING";//国王
const string MINISTER = "MINISTER";//大臣

const stirng HIGH_LEVEL_MONSTER = "HIGH_LEVEL_MONSTER";
const stirng LOW_LEVEL_MONSTER = "LOW_LEVEL_MONSTER";

class NPC
{
public:
	NPC(const string& name) :name{ name } {};
	virtual ~NPC() {};

protected:

private:
	string name;

};

#endif