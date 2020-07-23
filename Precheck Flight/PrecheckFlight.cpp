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
	qRegisterMetaType<size_t>("size_t");
	qRegisterMetaType<uint8_t*>("uint8_t*");
	connect(portHandler, SIGNAL(printToConsole(uint8_t*, size_t)), this, SLOT(printToOutput(uint8_t*, size_t)));
	testComm();
	ui.tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
	ui.digitBox->addItem("ASCII", 0);
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
		ui.tableWidget->setItem(state - 1, 0, new QTableWidgetItem(PrecheckStateMachine::getStateText(state))); // ��Ŀ
		ui.tableWidget->setItem(state - 1, 1, status_item); // ״̬
		ui.tableWidget->setItem(state - 1, 2, new QTableWidgetItem(trail)); // ����
		ui.tableWidget->setItem(state - 1, 3, new QTableWidgetItem(message)); // ��Ϣ
		ui.tableWidget->horizontalHeader()->setSectionResizeMode(1, QHeaderView::ResizeToContents);
		break;
	}
}

void PrecheckFlight::beginTest()
{
	if (worker && !worker->stopThread) 
	{
		worker->closeThread();
		ui.beginButton->setEnabled(false);
		return;
	}
	machine = new PrecheckStateMachine();
	if (portCommunicator->Open(ui.commBox->currentData().toInt(), ui.bitBox->currentData().toInt()))
	{
		printToConsole("�˿�" + ui.commBox->currentData().toString() + ", ������" + ui.bitBox->currentData().toString() + ", ���ӳɹ�~");
		ui.sendButton->setEnabled(false);
		ui.testButton->setEnabled(false);
		ui.beginButton->setText(tr("ȡ\n��"));
		ui.detailWidget->setRowCount(0);
		ui.detailWidget->clearContents();
		worker = new PrecheckThread(machine, portCommunicator, 1);
		qRegisterMetaType<PrecheckStateMachine::Status>("PrecheckStateMachine::Status");
		qRegisterMetaType<PrecheckStateMachine::State>("PrecheckStateMachine::State");
		qRegisterMetaType<size_t>("size_t");
		qRegisterMetaType<uint8_t*>("uint8_t*");
		sender = connect(this, SIGNAL(sendToWorker(uint8_t*, size_t)), worker, SLOT(receiveFromPort(uint8_t*, size_t)));
		receiver = connect(worker, SIGNAL(sendToWindow(QString, PrecheckStateMachine::State, PrecheckStateMachine::Status, QString)), this, SLOT(receiveFromWorker(QString, PrecheckStateMachine::State, PrecheckStateMachine::Status, QString)));
		printer = connect(worker, SIGNAL(sendDetailsToWindow(PrecheckStateMachine::State, PrecheckStateMachine::Status, QString, QString)), this, SLOT(receiveDetailsFromWorker(PrecheckStateMachine::State, PrecheckStateMachine::Status, QString, QString)));
		worker->start();
	}
	else
	{
		printToConsole("�˿ڴ�ʧ��, ������!");
		portCommunicator->Close();
	}
	
}

void PrecheckFlight::receiveDetailsFromWorker(PrecheckStateMachine::State state, PrecheckStateMachine::Status status, QString function, QString message)
{
		int count = ui.detailWidget->rowCount();
		ui.detailWidget->insertRow(count);
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
		ui.detailWidget->setItem(count, 0, new QTableWidgetItem(PrecheckStateMachine::getStateText(state))); // ��Ŀ
		ui.detailWidget->setItem(count, 1, new QTableWidgetItem(function)); // ����
		ui.detailWidget->setItem(count, 3, new QTableWidgetItem(message)); // ��Ϣ
		ui.detailWidget->setItem(count, 2, status_item); // ״̬
		ui.detailWidget->horizontalHeader()->setSectionResizeMode(2, QHeaderView::ResizeToContents);
}

void PrecheckFlight::endTest()
{
	disconnect(sender);
	disconnect(receiver);
	disconnect(printer);
	ui.testButton->setEnabled(true);
	ui.sendButton->setEnabled(true);
	ui.beginButton->setEnabled(true);
	ui.beginButton->setText(tr("��\nʼ"));
	printToConsole("������� = =");
}

PrecheckFlight::~PrecheckFlight()
{
	printToConsole("�����˳�...");
	portCommunicator->Close();
}

void PrecheckFlight::printToConsole(QString content)
{
	QString current = ui.consoleWindow->toPlainText();
	ui.consoleWindow->setPlainText(current + content + '\n');
}

void PrecheckFlight::printToOutput(uint8_t* content, size_t size)
{
	QString current = ui.receiveComm->toPlainText();
	switch (machine->currentState()) {
	case PrecheckStateMachine::GND_IDLE:
		ui.receiveComm->setPlainText(current + QString((char*)content));
		break;
	default:
		emit(sendToWorker(content, size));
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
		printToConsole("�˿�" + ui.commBox->currentData().toString() + ", ������" + ui.bitBox->currentData().toString() + ", ���ӳɹ�~");
		portCommunicator->Write((uint8_t*)ui.sendComm->toPlainText().toUtf8().data(), strlen(ui.sendComm->toPlainText().toUtf8().data()), false);
		ui.sendComm->clear();
		//portHandler->DataHandle((uint8_t*)ui.sendComm->toPlainText().toUtf8().data(), strlen(ui.sendComm->toPlainText().toUtf8().data()));
		//
		printToConsole("�������!");
	}
	else
	{
		printToConsole("�˿ڴ�ʧ��, ������!");
		portCommunicator->Close();
	}
}

void PrecheckFlight::testComm()
{
	ui.testButton->setEnabled(false);
	ui.testButton->setText(tr("�����"));
	printToConsole("��ʼ���");
	initCommPort();
	printToConsole("��ɼ��");
	ui.testButton->setText(tr("���¼��"));
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
	{// ֧��16������
		char name[MAX_PATH];
		WCHAR wname[MAX_PATH];
		sprintf(name, "\\\\.\\COM%d", i);
		MultiByteToWideChar(CP_ACP, 0, name, strlen(name) + 1, wname,
			sizeof(wname) / sizeof(wname[0]));
		hCom = CreateFile(wname, 0, 0, 0,
			OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);
		if (INVALID_HANDLE_VALUE != hCom)
		{// ��Ӵ���
			
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
		printToConsole("���ֿ��ö˿�~!");
	}
	else
		printToConsole("���޿��ö˿� QAQ");
}
