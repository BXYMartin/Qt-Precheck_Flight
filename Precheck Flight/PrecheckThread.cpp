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

void PrecheckThread::receiveFromPort(uint8_t* content, size_t size)
{
	mutex.lock();
	for (size_t i = 0; i < size; i++)
	{
		frames[position + i] = content[i];
	}
	position += size;
	mutex.unlock();
}

QString PrecheckThread::trailBuilder(int i, int total)
{
	return QString::number(i) + QString("/") + QString::number(total);
}



void PrecheckThread::run()
{
	PrecheckHandler* handler = new PrecheckHandler(this);
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
		bool elapsed = false;
		emit(sendToWindow(trailBuilder(0, total), machine->currentState(), PrecheckStateMachine::BEGIN, QString("开始检查...")));
		
		for (int i = 0; i < total; i++)
		{
			if (stopThread)
				break;
			position = 0;
			uint8_t message[64];
			handler->generateFrame(machine->currentState(), message);
			if (portCommunicator->Write((uint8_t*)message, 64))
			{
				emit(sendToWindow(trailBuilder(i, total), machine->currentState(), PrecheckStateMachine::FAILED, QString("发送帧出错")));
				passed = false;
				break;
			}
			if (machine->currentState() == PrecheckStateMachine::GND_INIT)
			{
				for (int timer = 10; timer >= 0; timer--)
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
				int timeout = 15;
				mutex.lock();
				int current_position = position;
				mutex.unlock();
				while (current_position < 64 && timeout > 0) { sleep(1); timeout--; mutex.lock(); current_position = position; mutex.unlock(); }
				if (timeout < 0)
				{
					passed = false;
					elapsed = true;
					break;
				}
				else
				{
					emit(sendToWindow(trailBuilder(i, total), machine->currentState(), PrecheckStateMachine::PROCESSING, QString("接收到返回帧 ") + QString((char*)frames)));
					if (!handler->checkFrame(machine->currentState(), frames))
					{
						//emit(sendDetailsToWindow(machine->currentState(), PrecheckStateMachine::FAILED, function, message));
						passed = false;
					}
					emit(sendToWindow(trailBuilder(i, total), machine->currentState(), PrecheckStateMachine::PROCESSING, QString("处理完成")));
				}
				
			}
			
		}
		if (passed)
		{
			emit(sendToWindow(trailBuilder(total, total), machine->currentState(), PrecheckStateMachine::FINISH, QString("测试通过")));
		}
		else
		{
			if (elapsed)
				emit(sendToWindow(trailBuilder(total, total), machine->currentState(), PrecheckStateMachine::FAILED, QString("等待返回超时")));
			else
				emit(sendToWindow(trailBuilder(total, total), machine->currentState(), PrecheckStateMachine::FAILED, QString("检查出错")));
		}
	}
	delete handler;
	emit(sendToWindow(trailBuilder(0, 0), machine->currentState(), PrecheckStateMachine::FINISH, ""));
}