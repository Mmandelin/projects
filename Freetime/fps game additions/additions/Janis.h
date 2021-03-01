#pragma once
#include "Windows.h"
#include "Offsets.h"

struct world {

	DWORD GameModule = (DWORD)GetModuleHandle("client.dll");
};

struct entity {
public:
	int health;
	int flags;

	DWORD EntityPtr;

	void ForceJump(DWORD GameModule) {

		*(int*)(GameModule + hazedumper::signatures::dwForceJump) = 2;
	}
};