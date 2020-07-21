#pragma once

#include <QThread>
#include "PrecheckStateMachine.h"
#include "PrecheckHandler.h"
#include "serial_port.h"

class PrecheckThread : public QThread
{
	Q_OBJECT

public:
	PrecheckThread(PrecheckStateMachine* state, CSerialPort* port);
	void closeThread();
	PrecheckStateMachine* machine;
	CSerialPort* portCommunicator;


public slots:
	void receiveFromPort(QString content);

signals:
	void sendToWindow(PrecheckStateMachine::State state, PrecheckStateMachine::Status status, QString message);

protected:
	virtual void run();

private:
	volatile bool stopThread;
	char frames[256];
	int position = 0;

};
