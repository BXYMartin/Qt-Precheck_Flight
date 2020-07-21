#pragma once
#include "PrecheckStateMachine.h"

class PrecheckHandler
{
public:
	PrecheckHandler();

	void generateFrame(PrecheckStateMachine::State, uint8_t* frames);
	bool checkFrame(PrecheckStateMachine::State, uint8_t* frames);

private:
	void fillInstruction(PrecheckStateMachine::State, uint8_t* frames);
	void fillHeader(uint8_t* frames);
	void fillType(uint8_t* frames);
};