#pragma once

class PrecheckStateMachine
{
public:
	enum Status {
		BEGIN,
		PROCESSING,
		FINISH,
		FAILED
	};
	enum State {
		GND_IDLE,
		GND_INIT,
		GND_TEST,
		PUBIT_RESULT,
		PUBIT_CONNECT,
		CHANNEL_LOGIC
	} state;

	PrecheckStateMachine(State init = GND_IDLE)
	{
		current = init;
	}

	State nextState()
	{
		switch (current)
		{
		case GND_IDLE:
			current = GND_INIT;
			break;
		case GND_INIT:
			current = GND_TEST;
			break;
		case GND_TEST:
			current = PUBIT_RESULT;
			break;
		case PUBIT_RESULT:
			current = PUBIT_CONNECT;
			break;
		case PUBIT_CONNECT:
			current = CHANNEL_LOGIC;
			break;
		case CHANNEL_LOGIC:
			current = GND_IDLE;
			break;
		}
		return current;
	}

	State currentState()
	{
		return current;
	}

private:
	State current;
};