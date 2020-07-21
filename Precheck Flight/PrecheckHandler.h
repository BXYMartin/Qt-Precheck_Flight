#pragma once
#include "PrecheckStateMachine.h"

class PrecheckHandler
{
public:
	PrecheckHandler();

	void generateFrame(PrecheckStateMachine::State, char* frames);
	bool checkFrame(PrecheckStateMachine::State, char* frames);

private:
	void fillInstruction(PrecheckStateMachine::State, char* frames);
	void fillHeader(char* frames);
	void fillType(char* frames);
};