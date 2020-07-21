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
		emit(sendToWindow(machine->currentState(), PrecheckStateMachine::BEGIN, QString("开始检查...")));
		char message[64];
		handler->generateFrame(machine->currentState(), message);
		if (portCommunicator->Write((uint8_t*)message, 64))
		{
			emit(sendToWindow(machine->currentState(), PrecheckStateMachine::FAILED, QString("发送帧出错")));
			continue;
		}
		emit(sendToWindow(machine->currentState(), PrecheckStateMachine::PROCESSING, QString("等待返回帧中")));
		// 临时使用输入帧大小替代，真实情况为 256
		while (position < 64) { sleep(1); }
		emit(sendToWindow(machine->currentState(), PrecheckStateMachine::PROCESSING, QString("接收到返回帧 ") + QString(frames)));
		if (handler->checkFrame(machine->currentState(), frames))
		{
			emit(sendToWindow(machine->currentState(), PrecheckStateMachine::FINISH, QString("检查结束")));
		}
		else
		{
			emit(sendToWindow(machine->currentState(), PrecheckStateMachine::FAILED, QString("检查出错")));
		}
	}
	delete handler;
	emit(sendToWindow(machine->currentState(), PrecheckStateMachine::FINISH, ""));
}