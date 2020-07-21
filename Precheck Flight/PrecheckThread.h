#pragma once

#include <QThread>
#include "PrecheckStateMachine.h"
#include "PrecheckHandler.h"
#include "serial_port.h"

class PrecheckThread : public QThread
{
	Q_OBJECT

public:
	PrecheckThread(PrecheckStateMachine* state, CSerialPort* port, int num);
	void closeThread();
	PrecheckStateMachine* machine;
	CSerialPort* portCommunicator;


public slots:
	void receiveFromPort(QString content);

signals:
	void sendToWindow(QString count, PrecheckStateMachine::State state, PrecheckStateMachine::Status status, QString message);

protected:
	virtual void run();

private:
	QString PrecheckThread::trailBuilder(int i, int total);
	volatile bool stopThread;
	char frames[256];
	int position = 0;
	int trail = 1;

};
