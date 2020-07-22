#pragma once
#include "PrecheckStateMachine.h"
#include "PrecheckThread.h"

class PrecheckThread;

class PrecheckHandler
{
public:
	PrecheckHandler(PrecheckThread* callback);

	void generateFrame(PrecheckStateMachine::State, uint8_t* frames);
	bool checkFrame(PrecheckStateMachine::State, uint8_t* frames);

private:
	void genReport(bool accord, PrecheckStateMachine::State state, char* function, char* message, bool* passed);
	void fillInstruction(PrecheckStateMachine::State, uint8_t* frames);
	void fillHeader(uint8_t* frames);
	void fillType(uint8_t* frames);
	PrecheckThread* response;
};