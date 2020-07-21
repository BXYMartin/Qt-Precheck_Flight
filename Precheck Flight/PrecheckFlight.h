#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_PrecheckFlight.h"
#include "serial_port.h"
#include "PrecheckStateMachine.h"
#include "PrecheckThread.h"

class PortHandler;

class PrecheckFlight : public QMainWindow
{
	Q_OBJECT

public:
	~PrecheckFlight();
	PrecheckFlight(QWidget *parent = Q_NULLPTR);
	void clearConsole();

private:
	CSerialPort* portCommunicator;
	PortHandler* portHandler;
	PrecheckStateMachine* machine;
	PrecheckThread* worker;
	Ui::PrecheckFlightClass ui;
	QMetaObject::Connection sender;
	QMetaObject::Connection receiver;
	void initCommPort();
	

public slots:
	void testComm();
	void sendMessage();
	void beginTest();
	void endTest();
	void receiveFromWorker(QString trail, PrecheckStateMachine::State state, PrecheckStateMachine::Status status, QString message);
	void printToConsole(QString content);
	void printToOutput(QString content);

signals:
	void sendToWorker(QString content);
};


class PortHandler : public QObject, public CSerialPortHandle
{
	Q_OBJECT

public:
	PrecheckFlight * window;
	PortHandler(PrecheckFlight* obj)
	{
		window = obj;
	}

	void DataHandle(uint8_t* data, size_t size)
	{
		for (int i = 0; i < size; i++)
			emit(printToConsole(QString((char)data[i])));
		return;
	}

	
signals:
	void printToConsole(QString content);
};