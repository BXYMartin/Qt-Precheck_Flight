#include "PrecheckFlight.h"
#include "PrecheckThread.h"
#include "serial_port.h"


#pragma execution_character_set("utf-8")

PrecheckFlight::PrecheckFlight(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	portHandler = new PortHandler(this);
	portCommunicator = new CSerialPort(portHandler);
	machine = new PrecheckStateMachine();
	connect(ui.testButton, SIGNAL(clicked()), this, SLOT(testComm()));
	connect(ui.sendButton, SIGNAL(clicked()), this, SLOT(sendMessage()));
	connect(ui.beginButton, SIGNAL(clicked()), this, SLOT(beginTest()));
	connect(portHandler, SIGNAL(printToConsole(QString)), this, SLOT(printToOutput(QString)));
	testComm();
}

void PrecheckFlight::receiveFromWorker(QString trail, PrecheckStateMachine::State state, PrecheckStateMachine::Status status, QString message)
{
	switch (state)
	{
	case PrecheckStateMachine::GND_IDLE:
		endTest();
		break;
	default:
		int count = ui.tableWidget->rowCount();
		while (count < state)
		{
			ui.tableWidget->insertRow(count);
			count = ui.tableWidget->rowCount();
		}
		QTableWidgetItem* status_item = new QTableWidgetItem;
		switch (status) 
		{
		case PrecheckStateMachine::BEGIN:
			status_item->setIcon(QApplication::style()->standardIcon((QStyle::StandardPixmap) ICON_BEGIN));
			break;
		case PrecheckStateMachine::FAILED:
			status_item->setIcon(QApplication::style()->standardIcon((QStyle::StandardPixmap) ICON_FAILED)); 
			break;
		case PrecheckStateMachine::FINISH:
			status_item->setIcon(QApplication::style()->standardIcon((QStyle::StandardPixmap) ICON_FINISH)); 
			break;
		case PrecheckStateMachine::PROCESSING:
			status_item->setIcon(QApplication::style()->standardIcon((QStyle::StandardPixmap) ICON_PROCESSING));
			break;
		default:
			status_item->setIcon(QApplication::style()->standardIcon((QStyle::StandardPixmap) ICON_BEGIN));
			break;
		}
		ui.tableWidget->setItem(state - 1, 0, new QTableWidgetItem(PrecheckStateMachine::getStateText(state))); // 项目
		ui.tableWidget->setItem(state - 1, 1, status_item); // 状态
		ui.tableWidget->setItem(state - 1, 2, new QTableWidgetItem(trail)); // 计数
		ui.tableWidget->setItem(state - 1, 3, new QTableWidgetItem(message)); // 信息
		
		break;
	}
}

void PrecheckFlight::beginTest()
{
	machine = new PrecheckStateMachine();
	if (portCommunicator->Open(ui.commBox->currentData().toInt(), ui.bitBox->currentData().toInt()))
	{
		printToConsole("端口" + ui.commBox->currentData().toString() + ", 波特率" + ui.bitBox->currentData().toString() + ", 连接成功~");
		ui.sendButton->setEnabled(false);
		ui.testButton->setEnabled(false);
		ui.beginButton->setEnabled(false);
		worker = new PrecheckThread(machine, portCommunicator, 5);
		qRegisterMetaType<PrecheckStateMachine::Status>("PrecheckStateMachine::Status");
		qRegisterMetaType<PrecheckStateMachine::State>("PrecheckStateMachine::State");
		sender = connect(this, SIGNAL(sendToWorker(QString)), worker, SLOT(receiveFromPort(QString)));
		receiver = connect(worker, SIGNAL(sendToWindow(QString, PrecheckStateMachine::State, PrecheckStateMachine::Status, QString)), this, SLOT(receiveFromWorker(QString, PrecheckStateMachine::State, PrecheckStateMachine::Status, QString)));
		worker->start();
	}
	else
	{
		printToConsole("端口打开失败, 请重试!");
		portCommunicator->Close();
	}
	
}

void PrecheckFlight::endTest()
{
	disconnect(sender);
	disconnect(receiver);
	ui.testButton->setEnabled(true);
	ui.sendButton->setEnabled(true);
	ui.beginButton->setEnabled(true);
}

PrecheckFlight::~PrecheckFlight()
{
	printToConsole("正在退出...");
	portCommunicator->Close();
}

void PrecheckFlight::printToConsole(QString content)
{
	QString current = ui.consoleWindow->toPlainText();
	ui.consoleWindow->setPlainText(current + content + '\n');
}

void PrecheckFlight::printToOutput(QString content)
{
	QString current = ui.receiveComm->toPlainText();
	switch (machine->currentState()) {
	case PrecheckStateMachine::GND_IDLE:
		ui.receiveComm->setPlainText(current + content);
		break;
	default:
		emit(sendToWorker(content));
		break;
	}
	
}

void PrecheckFlight::clearConsole()
{
	ui.consoleWindow->setPlainText("");
}

void PrecheckFlight::sendMessage()
{
	
	if (portCommunicator->Open(ui.commBox->currentData().toInt(), ui.bitBox->currentData().toInt()))
	{
		printToConsole("端口" + ui.commBox->currentData().toString() + ", 波特率" + ui.bitBox->currentData().toString() + ", 连接成功~");
		portCommunicator->Write((uint8_t*) ui.sendComm->toPlainText().toUtf8().data(), strlen(ui.sendComm->toPlainText().toUtf8().data()), false);
		ui.sendComm->clear();
		//portHandler->DataHandle((uint8_t*)ui.sendComm->toPlainText().toUtf8().data(), strlen(ui.sendComm->toPlainText().toUtf8().data()));
		//
		printToConsole("发送完成!");
	}
	else
	{
		printToConsole("端口打开失败, 请重试!");
		portCommunicator->Close();
	}
}

void PrecheckFlight::testComm()
{
	ui.testButton->setEnabled(false);
	ui.testButton->setText(tr("检测中"));
	printToConsole("开始检测");
	initCommPort();
	printToConsole("完成检测");
	ui.testButton->setText(tr("重新检测"));
	ui.testButton->setEnabled(true);
}

void PrecheckFlight::initCommPort()
{
	ui.bitBox->clear();
	ui.commBox->clear();
	HANDLE  hCom;
	int i, num, k;
	BOOL flag;
	flag = FALSE;
	num = 0;
	for (i = 1; i <= 16; i++)
	{// 支持16个串口
		char name[MAX_PATH];
		WCHAR wname[MAX_PATH];
		sprintf(name, "\\\\.\\COM%d", i);
		MultiByteToWideChar(CP_ACP, 0, name, strlen(name) + 1, wname,
			sizeof(wname) / sizeof(wname[0]));
		hCom = CreateFile(wname, 0, 0, 0,
			OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);
		if (INVALID_HANDLE_VALUE != hCom)
		{// 添加串口
			
			ui.commBox->addItem(&name[4], i);
			if (flag == FALSE)
			{
				flag = TRUE;
				num = i;
			}
		}
		CloseHandle(hCom);
	}
	if (flag)
	{
		ui.bitBox->addItem("600", 600);
		ui.bitBox->addItem("1200", 1200);
		ui.bitBox->addItem("2400", 2400);
		ui.bitBox->addItem("4800", 4800);
		ui.bitBox->addItem("9600", 9600);
		ui.bitBox->addItem("38400", 38400);
		ui.bitBox->addItem("57600", 57600);
		ui.bitBox->addItem("115200", 115200);
		//	ui.bitBox->addItem("230400", 230400);
		//	ui.bitBox->addItem("460800", 460800);
		printToConsole("发现可用端口~!");
	}
	else
		printToConsole("暂无可用端口 QAQ");
}
