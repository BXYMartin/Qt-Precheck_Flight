#pragma once

#define ICON_PROCESSING	59
#define ICON_FINISH		48
#define ICON_FAILED		49
#define ICON_BEGIN		7

#include <QtWidgets/QMainWindow>
#pragma execution_character_set("utf-8")

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
	enum Receive {
		HEADER_0,
		HEADER_1,
		READY,
		IDLE
	};

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

	static QString getStateText(State state)
	{
		switch (state)
		{
		case GND_IDLE:
			return QString("����");
		case GND_INIT:
			return QString("����ȴ�");
		case GND_TEST:
			return QString("������");
		case PUBIT_RESULT:
			return QString("PUBIT���");
		case PUBIT_CONNECT:
			return QString("PUBIT�ӿ�");
		case CHANNEL_LOGIC:
			return QString("ͨ�����Ͻ��");
		default:
			return QString("����");
		}
	}

private:
	State current;
};