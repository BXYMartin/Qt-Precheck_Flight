#include <QDebug>
#include <QMutex>
#include "PrecheckThread.h"
#pragma execution_character_set("utf-8")

PrecheckThread::PrecheckThread(PrecheckStateMachine* state, CSerialPort* port)
{
	machine = state;
	portCommunicator = port;
	stopThread = false;
}

void PrecheckThread::closeThread()
{
	stopThread = true;
}

void PrecheckThread::receiveFromPort(QString content)
{
	frames[position++] = *content.toUtf8().data();
}

void PrecheckThread::run()
{
	PrecheckHandler* handler = new PrecheckHandler();
	while (machine->nextState())
	{
		position = 0;
		emit(sendToWindow(machine->currentState(), PrecheckStateMachine::BEGIN, QString("��ʼ���...")));
		char message[64];
		handler->generateFrame(machine->currentState(), message);
		if (portCommunicator->Write((uint8_t*)message, 64))
		{
			emit(sendToWindow(machine->currentState(), PrecheckStateMachine::FAILED, QString("����֡����")));
			continue;
		}
		emit(sendToWindow(machine->currentState(), PrecheckStateMachine::PROCESSING, QString("�ȴ�����֡��")));
		// ��ʱʹ������֡��С�������ʵ���Ϊ 256
		while (position < 64) { sleep(1); }
		emit(sendToWindow(machine->currentState(), PrecheckStateMachine::PROCESSING, QString("���յ�����֡ ") + QString(frames)));
		if (handler->checkFrame(machine->currentState(), frames))
		{
			emit(sendToWindow(machine->currentState(), PrecheckStateMachine::FINISH, QString("������")));
		}
		else
		{
			emit(sendToWindow(machine->currentState(), PrecheckStateMachine::FAILED, QString("������")));
		}
	}
	delete handler;
	emit(sendToWindow(machine->currentState(), PrecheckStateMachine::FINISH, ""));
}