#include "PrecheckFlight.h"
#include "serial_port.h"

#pragma execution_character_set("utf-8")

PrecheckFlight::PrecheckFlight(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	portHandler = new PortHandler(this);
	portCommunicator = new CSerialPort(portHandler);
	connect(ui.testButton, SIGNAL(clicked()), this, SLOT(testComm()));
	connect(ui.sendButton, SIGNAL(clicked()), this, SLOT(sendMessage()));
	connect(portHandler, SIGNAL(printToConsole(QString)), this, SLOT(printToOutput(QString)));
	testComm();
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
	ui.receiveComm->setPlainText(current + content);
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
