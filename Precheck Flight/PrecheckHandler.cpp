#include "PrecheckHandler.h"

PrecheckHandler::PrecheckHandler()
{

}

bool PrecheckHandler::checkFrame(PrecheckStateMachine::State state, char* frame)
{
	return true;
}

void PrecheckHandler::generateFrame(PrecheckStateMachine::State state, char* frame)
{
	for (int i = 0; i < 64; i++)
		frame[i] = 'a';
}