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
			total = 1; // ��ʼ������ִ��һ��
			break;
		default:
			break;
		}
		if (stopThread)
		{
			emit(sendToWindow(trailBuilder(0, total), machine->currentState(), PrecheckStateMachine::FAILED, QString("��鱻����")));
			continue;
		}
		bool passed = true;
		bool elapsed = false;
		emit(sendToWindow(trailBuilder(0, total), machine->currentState(), PrecheckStateMachine::BEGIN, QString("��ʼ���...")));
		
		for (int i = 0; i < total; i++)
		{
			if (stopThread)
				break;
			position = 0;
			uint8_t message[64];
			handler->generateFrame(machine->currentState(), message);
			if (portCommunicator->Write((uint8_t*)message, 64))
			{
				emit(sendToWindow(trailBuilder(i, total), machine->currentState(), PrecheckStateMachine::FAILED, QString("����֡����")));
				passed = false;
				break;
			}
			if (machine->currentState() == PrecheckStateMachine::GND_INIT)
			{
				for (int timer = 10; timer >= 0; timer--)
				{
					if (stopThread)
						break;
					emit(sendToWindow(trailBuilder(i, total), machine->currentState(), PrecheckStateMachine::PROCESSING, QString("�ȴ� ") + QString::number(timer) + QString(" ��")));
					sleep(1);
				}
				emit(sendToWindow(trailBuilder(i, total), machine->currentState(), PrecheckStateMachine::PROCESSING, QString("�ȴ����")));
			}
			else
			{
				emit(sendToWindow(trailBuilder(i, total), machine->currentState(), PrecheckStateMachine::PROCESSING, QString("�ȴ�����֡��")));
				// ��ʱʹ������֡��С�������ʵ���Ϊ 256
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
					emit(sendToWindow(trailBuilder(i, total), machine->currentState(), PrecheckStateMachine::PROCESSING, QString("���յ�����֡ ") + QString((char*)frames)));
					if (!handler->checkFrame(machine->currentState(), frames))
					{
						//emit(sendDetailsToWindow(machine->currentState(), PrecheckStateMachine::FAILED, function, message));
						passed = false;
					}
					emit(sendToWindow(trailBuilder(i, total), machine->currentState(), PrecheckStateMachine::PROCESSING, QString("�������")));
				}
				
			}
			
		}
		if (passed)
		{
			emit(sendToWindow(trailBuilder(total, total), machine->currentState(), PrecheckStateMachine::FINISH, QString("����ͨ��")));
		}
		else
		{
			if (elapsed)
				emit(sendToWindow(trailBuilder(total, total), machine->currentState(), PrecheckStateMachine::FAILED, QString("�ȴ����س�ʱ")));
			else
				emit(sendToWindow(trailBuilder(total, total), machine->currentState(), PrecheckStateMachine::FAILED, QString("������")));
		}
	}
	delete handler;
	emit(sendToWindow(trailBuilder(0, 0), machine->currentState(), PrecheckStateMachine::FINISH, ""));
}