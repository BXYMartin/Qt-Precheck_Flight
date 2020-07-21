#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_PrecheckFlight.h"
#include "serial_port.h"

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
	Ui::PrecheckFlightClass ui;
	void initCommPort();
	

public slots:
	void testComm();
	void sendMessage();
	void printToConsole(QString content);
	void printToOutput(QString content);
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