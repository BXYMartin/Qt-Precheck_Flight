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
	void printToOutput(uint8_t* content, size_t size);

signals:
	void sendToWorker(uint8_t* content, size_t size);
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
		emit(printToConsole(data, size));
		return;
	}

	
signals:
	void printToConsole(uint8_t* content, size_t size);
};