#pragma once
#include "PrecheckStateMachine.h"

class PrecheckHandler
{
public:
	PrecheckHandler();

	void generateFrame(PrecheckStateMachine::State, char* frames);
	bool checkFrame(PrecheckStateMachine::State, char* frames);
};