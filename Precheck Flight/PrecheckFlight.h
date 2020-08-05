#pragma once

#include <QtWidgets/QMainWindow>
#include <QtXml/QDomDocument>
#include <QMessageBox>
#include <QScrollBar>
#include <QFileDialog>
#include <QTextStream>
#include <QDateTime>
#include <QAxObject>
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
	PrecheckThread* worker = 0;
	Ui::PrecheckFlightClass ui;
	QMetaObject::Connection sender;
	QMetaObject::Connection receiver;
	QMetaObject::Connection printer;
	void initCommPort();
	

public slots:
	void testComm();
	void sendMessage();
	void beginTest();
	void endTest();
	void openPort();
	void exportReport();
	void receiveFromWorker(QString trail, PrecheckStateMachine::State state, PrecheckStateMachine::Status status, QString message);
	void printToConsole(QString content);
	void printToOutput(uint8_t content, size_t size);
	void receiveDetailsFromWorker(PrecheckStateMachine::State state, PrecheckStateMachine::Status status, QString function, QString message);

signals:
	void sendToWorker(uint8_t content, size_t size);
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
		{
			emit(printToConsole(data[i], 1));
		}
		
		return;
	}

	
signals:
	void printToConsole(uint8_t content, size_t size);
};