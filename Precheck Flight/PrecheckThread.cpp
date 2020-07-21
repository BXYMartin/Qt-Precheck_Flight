#include <QDebug>
#include <QMutex>
#include "PrecheckThread.h"
#pragma execution_character_set("utf-8")

PrecheckThread::PrecheckThread(PrecheckStateMachine* state, CSerialPort* port, int num)
{
	machine = state;
	portCommunicator = port;
	stopThread = false;
	trail = num;
}

void PrecheckThread::closeThread()
{
	stopThread = true;
}

void PrecheckThread::receiveFromPort(QString content)
{
	frames[position++] = *content.toUtf8().data();
}

QString PrecheckThread::trailBuilder(int i, int total)
{
	return QString::number(i) + QString("/") + QString::number(total);
}

void PrecheckThread::run()
{
	PrecheckHandler* handler = new PrecheckHandler();
	while (machine->nextState())
	{
		int total = trail;
		switch (machine->currentState())
		{
		case PrecheckStateMachine::GND_IDLE:
		case PrecheckStateMachine::GND_INIT:
		case PrecheckStateMachine::GND_TEST:
			total = 1; // 初始化过程执行一次
			break;
		default:
			break;
		}
		if (stopThread)
		{
			emit(sendToWindow(trailBuilder(0, total), machine->currentState(), PrecheckStateMachine::FAILED, QString("检查被跳过")));
			continue;
		}
		bool passed = true;
		emit(sendToWindow(trailBuilder(0, total), machine->currentState(), PrecheckStateMachine::BEGIN, QString("开始检查...")));
		
		for (int i = 0; i < total; i++)
		{
			if (stopThread)
				break;
			position = 0;
			char message[64];
			handler->generateFrame(machine->currentState(), message);
			if (portCommunicator->Write((uint8_t*)message, 64))
			{
				emit(sendToWindow(trailBuilder(i, total), machine->currentState(), PrecheckStateMachine::FAILED, QString("发送帧出错")));
				passed = false;
				break;
			}
			if (machine->currentState() == PrecheckStateMachine::GND_INIT)
			{
				for (int timer = 60; timer >= 0; timer--)
				{
					if (stopThread)
						break;
					emit(sendToWindow(trailBuilder(i, total), machine->currentState(), PrecheckStateMachine::PROCESSING, QString("等待 ") + QString::number(timer) + QString(" 秒")));
					sleep(1);
				}
				emit(sendToWindow(trailBuilder(i, total), machine->currentState(), PrecheckStateMachine::PROCESSING, QString("等待完成")));
			}
			else
			{
				emit(sendToWindow(trailBuilder(i, total), machine->currentState(), PrecheckStateMachine::PROCESSING, QString("等待返回帧中")));
				// 临时使用输入帧大小替代，真实情况为 256
				while (position < 64) { sleep(1); }
				emit(sendToWindow(trailBuilder(i, total), machine->currentState(), PrecheckStateMachine::PROCESSING, QString("接收到返回帧 ") + QString(frames)));
				if (!handler->checkFrame(machine->currentState(), frames))
				{
					passed = false;
				}
				emit(sendToWindow(trailBuilder(i, total), machine->currentState(), PrecheckStateMachine::PROCESSING, QString("处理完成")));
			}
			
		}
		if (passed)
		{
			emit(sendToWindow(trailBuilder(total, total), machine->currentState(), PrecheckStateMachine::FINISH, QString("测试通过")));
		}
		else
		{
			emit(sendToWindow(trailBuilder(total, total), machine->currentState(), PrecheckStateMachine::FAILED, QString("检查出错")));
		}
	}
	delete handler;
	emit(sendToWindow(trailBuilder(0, 0), machine->currentState(), PrecheckStateMachine::FINISH, ""));
}