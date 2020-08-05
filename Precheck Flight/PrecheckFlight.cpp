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
	connect(ui.openButton, SIGNAL(clicked()), this, SLOT(openPort()));
	connect(ui.exportButton, SIGNAL(clicked()), this, SLOT(exportReport()));
	qRegisterMetaType<size_t>("size_t");
	qRegisterMetaType<uint8_t*>("uint8_t");
	connect(portHandler, SIGNAL(printToConsole(uint8_t, size_t)), this, SLOT(printToOutput(uint8_t, size_t)));
	testComm();
	ui.tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
	ui.digitBox->addItem("ASCII", 0);
	ui.beginButton->setEnabled(false);
	ui.sendButton->setEnabled(false);
	ui.exportButton->setEnabled(false);
	ui.detailWidget->setColumnHidden(4, true);
	ui.consoleWindow->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
}

void PrecheckFlight::openPort()
{
	if (portCommunicator->IsOpen())
	{
		printToConsole("�رմ���");
		if (worker && !worker->stopThread)
		{
			worker->closeThread();
		}
		portCommunicator->Close();
		ui.openButton->setText(tr("�򿪴���"));
		ui.statusLabel->setText(tr("�˿�δ��"));
		ui.exportButton->setEnabled(false);
		ui.sendButton->setEnabled(false);
		ui.beginButton->setEnabled(false);
		ui.testButton->setEnabled(true);
		ui.commBox->setEnabled(true);
		ui.bitBox->setEnabled(true);
	}
	else
	{
		
		if (portCommunicator->Open(ui.commBox->currentData().toInt(), ui.bitBox->currentData().toInt()))
		{
			printToConsole("�򿪴��ڳɹ�");
			printToConsole("�˿�" + ui.commBox->currentData().toString() + ", ������" + ui.bitBox->currentData().toString() + ", ���ӳɹ�~");
			ui.openButton->setText(tr("�رմ���"));
			ui.statusLabel->setText(tr("δ��⵽�ɿ�"));
			ui.beginButton->setEnabled(true);
			ui.sendButton->setEnabled(true);
			ui.commBox->setEnabled(false);
			ui.bitBox->setEnabled(false);
			ui.testButton->setEnabled(false);
		}
		else
		{
			ui.exportButton->setEnabled(false);
			ui.statusLabel->setText(tr("�˿�δ��"));
			printToConsole("�˿ڴ�ʧ��, ������!");
			portCommunicator->Close();
		}
	}
}

void PrecheckFlight::receiveFromWorker(QString trail, PrecheckStateMachine::State state, PrecheckStateMachine::Status status, QString message)
{
	switch (state)
	{
	case -1:
		printToConsole(message);
		break;
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
		QScrollBar *scrollbar = ui.tableWidget->verticalScrollBar();
		if (scrollbar)
			scrollbar->setSliderPosition(scrollbar->maximum());
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
	ui.exportButton->setEnabled(false);
		printToConsole("��ʼ����");
		ui.sendButton->setEnabled(false);
		ui.testButton->setEnabled(false);
		ui.beginButton->setText(tr("ȡ��"));
		ui.detailWidget->setRowCount(0);
		ui.detailWidget->clearContents();
		worker = new PrecheckThread(machine, portCommunicator, 1);
		qRegisterMetaType<PrecheckStateMachine::Status>("PrecheckStateMachine::Status");
		qRegisterMetaType<PrecheckStateMachine::State>("PrecheckStateMachine::State");
		qRegisterMetaType<size_t>("size_t");
		qRegisterMetaType<uint8_t*>("uint8_t");
		// sender = connect(portHandler, SIGNAL(printToConsole(uint8_t, size_t)), worker, SLOT(receiveFromPort(uint8_t, size_t)), Qt::QueuedConnection);
		sender = connect(this, SIGNAL(sendToWorker(uint8_t, size_t)), worker, SLOT(receiveFromPort(uint8_t, size_t)));
		receiver = connect(worker, SIGNAL(sendToWindow(QString, PrecheckStateMachine::State, PrecheckStateMachine::Status, QString)), this, SLOT(receiveFromWorker(QString, PrecheckStateMachine::State, PrecheckStateMachine::Status, QString)));
		printer = connect(worker, SIGNAL(sendDetailsToWindow(PrecheckStateMachine::State, PrecheckStateMachine::Status, QString, QString)), this, SLOT(receiveDetailsFromWorker(PrecheckStateMachine::State, PrecheckStateMachine::Status, QString, QString)));
		worker->start();
}

void PrecheckFlight::receiveDetailsFromWorker(PrecheckStateMachine::State state, PrecheckStateMachine::Status status, QString function, QString message)
{
		int count = ui.detailWidget->rowCount();
		ui.detailWidget->insertRow(count);
		QTableWidgetItem* status_item = new QTableWidgetItem;
		QString result;
		switch (status)
		{
		case PrecheckStateMachine::BEGIN:
			result = "��ʼ";
			status_item->setIcon(QApplication::style()->standardIcon((QStyle::StandardPixmap) ICON_BEGIN));
			break;
		case PrecheckStateMachine::FAILED:
			result = "ʧ��";
			status_item->setIcon(QApplication::style()->standardIcon((QStyle::StandardPixmap) ICON_FAILED));
			break;
		case PrecheckStateMachine::FINISH:
			result = "ͨ��";
			status_item->setIcon(QApplication::style()->standardIcon((QStyle::StandardPixmap) ICON_FINISH));
			break;
		case PrecheckStateMachine::PROCESSING:
			result = "�ȴ�";
			status_item->setIcon(QApplication::style()->standardIcon((QStyle::StandardPixmap) ICON_PROCESSING));
			break;
		default:
			result = "δ֪";
			status_item->setIcon(QApplication::style()->standardIcon((QStyle::StandardPixmap) ICON_BEGIN));
			break;
		}
		ui.detailWidget->setItem(count, 0, new QTableWidgetItem(PrecheckStateMachine::getStateText(state))); // ��Ŀ
		ui.detailWidget->setItem(count, 1, new QTableWidgetItem(function)); // ����
		ui.detailWidget->setItem(count, 3, new QTableWidgetItem(message)); // ��Ϣ
		ui.detailWidget->setItem(count, 4, new QTableWidgetItem(result)); // ��Ϣ
		ui.detailWidget->setItem(count, 2, status_item); // ״̬
		ui.detailWidget->horizontalHeader()->setSectionResizeMode(2, QHeaderView::ResizeToContents);
		QScrollBar *scrollbar = ui.detailWidget->verticalScrollBar();
		if (scrollbar)
			scrollbar->setSliderPosition(scrollbar->maximum());
}

void PrecheckFlight::endTest()
{
	disconnect(sender);
	disconnect(receiver);
	disconnect(printer);
	delete worker;
	ui.testButton->setEnabled(true);
	if (portCommunicator->IsOpen())
	{
		ui.sendButton->setEnabled(true);
		ui.beginButton->setEnabled(true);
	}
	ui.exportButton->setEnabled(true);
	ui.beginButton->setText(tr("��ʼ"));
	QMessageBox::information(this, "������", "װǰ��������",
		QMessageBox::Ok, QMessageBox::Ok);
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
	QScrollBar *scrollbar = ui.consoleWindow->verticalScrollBar();
	if (scrollbar)
		scrollbar->setSliderPosition(scrollbar->maximum());
}

void PrecheckFlight::printToOutput(uint8_t content, size_t size)
{
	//QString current = ui.receiveComm->toPlainText();
	//QString console = ui.consoleWindow->toPlainText();
	//static int position = 0;
	//QString disp = QString("%1").arg(content, 2, 16, QLatin1Char('0'));
	switch (machine->currentState()) {
	case PrecheckStateMachine::GND_IDLE:
		if (content == 0x81)
		{
			ui.statusLabel->setText(tr("�ɿ�������"));
		}
		return;
		break;
	default:
		emit(sendToWorker(content, size));
		break;
	}
}

void PrecheckFlight::exportReport()
{
	ui.exportButton->setEnabled(false);
	//��ȡ����·��
	/*
	QString filepath = QFileDialog::getSaveFileName(this, tr("Save"), ".", tr(" (*.xlsx)"));
	printToConsole("��ʼ����...");
	if (!filepath.isEmpty()) {
		QAxObject *excel = new QAxObject(this);
		//����Excel�ؼ�
		excel->setControl("Excel.Application");
		//����ʾ����
		excel->dynamicCall("SetVisible (bool Visible)", "false");
		//����ʾ�κξ�����Ϣ�����Ϊtrue��ô�ڹر��ǻ�������ơ��ļ����޸ģ��Ƿ񱣴桱����ʾ
		excel->setProperty("DisplayAlerts", false);
		//��ȡ����������
		QApplication::processEvents();
		QAxObject *workbooks = excel->querySubObject("WorkBooks");
		//�½�һ��������
		workbooks->dynamicCall("Add");
		//��ȡ��ǰ������
		QAxObject *workbook = excel->querySubObject("ActiveWorkBook");
		//��ȡ��������
		QAxObject *worksheets = workbook->querySubObject("Sheets");
		//��ȡ�������ϵĹ�����1����sheet1
		QAxObject *worksheet = worksheets->querySubObject("Item(int)", 1);
		QApplication::processEvents();
		QAxObject *cellA, *cellB, *cellC, *cellD;
		//���ñ���
		int cellrow = 1;
		//����Ҫ�����ĵ�Ԫ����A1
		QString A = "A" + QString::number(cellrow);
		QString B = "B" + QString::number(cellrow);
		QString C = "C" + QString::number(cellrow);
		QString D = "D" + QString::number(cellrow);
		//��ȡ��Ԫ��
		cellA = worksheet->querySubObject("Range(QVariant, QVariant)", A);
		cellB = worksheet->querySubObject("Range(QVariant, QVariant)", B);
		cellC = worksheet->querySubObject("Range(QVariant, QVariant)", C);
		cellD = worksheet->querySubObject("Range(QVariant, QVariant)", D);
		QApplication::processEvents();
		//���õ�Ԫ��ı�ͷֵ
		cellA->dynamicCall("SetValue(const QVariant&)", QVariant(ui.detailWidget->horizontalHeaderItem(0)->text()));
		cellB->dynamicCall("SetValue(const QVariant&)", QVariant(ui.detailWidget->horizontalHeaderItem(1)->text()));
		cellC->dynamicCall("SetValue(const QVariant&)", QVariant(ui.detailWidget->horizontalHeaderItem(4)->text()));
		cellD->dynamicCall("SetValue(const QVariant&)", QVariant(ui.detailWidget->horizontalHeaderItem(3)->text()));
		cellrow++;
		QApplication::processEvents();
		int rows = ui.detailWidget->rowCount();
		//���ñ������
		for (int i = 0; i<rows; i++) {
			//����Ҫ�����ĵ�Ԫ����A1��A2��A3��A4
			QString A = "A" + QString::number(cellrow);
			QString B = "B" + QString::number(cellrow);
			QString C = "C" + QString::number(cellrow);
			QString D = "D" + QString::number(cellrow);
			QApplication::processEvents();
			//��ȡ��Ԫ��
			cellA = worksheet->querySubObject("Range(QVariant, QVariant)", A);
			cellB = worksheet->querySubObject("Range(QVariant, QVariant)", B);
			cellC = worksheet->querySubObject("Range(QVariant, QVariant)", C);
			cellD = worksheet->querySubObject("Range(QVariant, QVariant)", D);
			//���õ�Ԫ���ֵ
			cellA->dynamicCall("SetValue(const QVariant&)", QVariant(ui.detailWidget->item(i, 0)->data(Qt::DisplayRole).toString()));
			cellB->dynamicCall("SetValue(const QVariant&)", QVariant(ui.detailWidget->item(i, 1)->data(Qt::DisplayRole).toString()));
			cellC->dynamicCall("SetValue(const QVariant&)", QVariant(ui.detailWidget->item(i, 4)->data(Qt::DisplayRole).toString()));
			cellD->dynamicCall("SetValue(const QVariant&)", QVariant(ui.detailWidget->item(i, 3)->data(Qt::DisplayRole).toString()));
			cellrow++;
			QApplication::processEvents();
		}

		workbook->dynamicCall("SaveAs(const QString&)", QDir::toNativeSeparators(filepath));//������filepath��ע��һ��Ҫ��QDir::toNativeSeparators��·���е�"/"ת��Ϊ"\"����Ȼһ�����治�ˡ�
		workbook->dynamicCall("Close()");//�رչ�����
		excel->dynamicCall("Quit()");//�ر�excel
		delete excel;
		excel = NULL;
		printToConsole("�����ɹ���������");
	}
	*/
	QString fileName = QFileDialog::getSaveFileName(this, tr("��������"), QString(), tr("Rich Text Files (*.rtf);;"));
	if (fileName.isEmpty())
	{
		printToConsole("�ļ���Ϊ��!");
		QMessageBox::critical(this, "��������", "�ļ���Ϊ��!", QMessageBox::Ok, QMessageBox::Ok);
		ui.exportButton->setEnabled(true);
		return;
	}
	if (!fileName.endsWith(QLatin1String(".rtf")))
		fileName += QLatin1String(".rtf");

	// �����ǿ���룬�����û��ֶ�ѡ�񱣴�·���� �Լ������ļ����� ����û�û�м��Ϻ�׺���Զ������ļ���׺��
	QFile file(fileName);
	if (!file.open(QIODevice::ReadWrite | QIODevice::Text)) {
		ui.exportButton->setEnabled(true);
		printToConsole("�ļ���ʧ��!");
		QMessageBox::critical(this, "��������", "�ļ���ʧ��!", QMessageBox::Ok, QMessageBox::Ok);
		return;
	}
	// ������һС�Σ����ı��ķ�ʽ���򿪲���д�ļ���

	QDomDocument doc;  //xml��rtf �ȶ����ı���ʽ��������Ҫ���ࡣ
	doc.setContent(&file);
	QDomElement root = doc.documentElement();
	QDomElement body;
	if (!root.isNull()) {
		body = root.firstChildElement(QLatin1String("body"));  //����û�������ļ����������ݣ� �����Ƿ���rtf��ʽ�����Ԫ�ء�
	}
	if (body.isNull()) {
		root = doc.createElement(QLatin1String("html"));
		QDomElement head = doc.createElement(QLatin1String("head"));
		QDomElement meta = doc.createElement(QLatin1String("meta"));
		meta.setAttribute(QLatin1String("http-equiv"), QLatin1String("Content-Type"));
		meta.setAttribute(QLatin1String("content"), QLatin1String("text/html; charset=utf-8"));
		//rtf��ʽ����һ��html��ʽ�ļ��� һ���Ľṹ�� ��Ҫ�ļ�ͷ�� body���ݡ�
		head.appendChild(meta);
		root.appendChild(head);
		body = doc.createElement(QLatin1String("body"));
		root.appendChild(body);
		doc.appendChild(root);
	}
	// ������һС����Ҫд�ļ����ļ�ͷ�����ݡ�
	if (body.isNull())
	{
		QMessageBox::critical(this, "��������", "RTF �ļ��޷�����!", QMessageBox::Ok, QMessageBox::Ok);
		printToConsole("RTF �ļ�ͷΪ��!");
		return;
	}
	body.setAttribute(QLatin1String("style"), QLatin1String("font-family: 'Arial', 'Microsoft YaHei', '����', '����', 'sans-serif'"));
	QDomElement title = doc.createElement(QLatin1String("h1"));
	QDomText titleText = doc.createTextNode(tr("�ɿ�װǰ��ⱨ��\n"));
	title.setAttribute(QLatin1String("style"), QLatin1String("text-align: center;font-weight: bold"));
	title.appendChild(titleText);
	body.appendChild(title);
	QDomElement time = doc.createElement(QLatin1String("h2"));
	QDomText timeText = doc.createTextNode(QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss"));
	time.setAttribute(QLatin1String("style"), QLatin1String("text-align: right"));
	time.appendChild(timeText);
	body.appendChild(time);
	// ������
	QDomElement table = doc.createElement(QLatin1String("table"));
	table.setAttribute(QLatin1String("style"), QLatin1String("border: 1px solid black;text-align: center;"));
	QDomElement table_header = doc.createElement(QLatin1String("tr"));
	//���õ�Ԫ��ı�ͷֵ
	int column_map[] = { 0, 1, 4, 3 };
	for (int i = 0; i < 4; i++)
	{
		QDomElement table_header_element = doc.createElement(QLatin1String("th"));
		QDomText content = doc.createTextNode(ui.detailWidget->horizontalHeaderItem(column_map[i])->text());
		table_header_element.setAttribute(QLatin1String("style"), QLatin1String("border: 1px solid black;"));
		table_header_element.appendChild(content);
		table_header.appendChild(table_header_element);
	}
	table.appendChild(table_header);
	QApplication::processEvents();
	int rows = ui.detailWidget->rowCount();
	//���ñ������
	for (int i = 0; i < rows; i++) {
		QDomElement row = doc.createElement(QLatin1String("tr"));
		
		
		//���õ�Ԫ���ֵ
		for (int j = 0; j < 4; j++)
		{
			QDomElement row_element = doc.createElement(QLatin1String("td"));
			row_element.setAttribute(QLatin1String("style"), QLatin1String("border: 1px solid black;"));
			QDomText content = doc.createTextNode(ui.detailWidget->item(i, column_map[j])->text());

			if (j == 2)
			{
				if (QString::compare(ui.detailWidget->item(i, column_map[j])->text(), QString("ͨ��")))
				{
					row_element.setAttribute(QLatin1String("style"), QLatin1String("border: 1px solid black;color: red;width: 50px;font-weight: bold"));
				}
				else
				{
					row_element.setAttribute(QLatin1String("style"), QLatin1String("border: 1px solid black;color: green;width: 50px;font-weight: bold"));
				}
			}

			row_element.appendChild(content);
			row.appendChild(row_element);
		}
		table.appendChild(row);
		QApplication::processEvents();
	}
	body.appendChild(table);
	QTextStream out(&file);
	doc.save(out, 4);
	file.close();
	printToConsole("�����ɹ���������");
	QMessageBox::information(this, "�����ɹ�", "RTF �ļ��ɹ�����!",
		QMessageBox::Ok, QMessageBox::Ok);
	ui.exportButton->setEnabled(true);
}

void PrecheckFlight::clearConsole()
{
	ui.consoleWindow->setPlainText("");
}

void PrecheckFlight::sendMessage()
{
		portCommunicator->Write((uint8_t*)ui.sendComm->toPlainText().toUtf8().data(), strlen(ui.sendComm->toPlainText().toUtf8().data()), false);
		ui.sendComm->clear();
		//portHandler->DataHandle((uint8_t*)ui.sendComm->toPlainText().toUtf8().data(), strlen(ui.sendComm->toPlainText().toUtf8().data()));
		//
		printToConsole("�������!");
}

void PrecheckFlight::testComm()
{
	if (portCommunicator->IsOpen()) 
	{
		openPort();
	}
	ui.openButton->setEnabled(false);
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
		// ui.bitBox->addItem("38400", 38400);
		// ui.bitBox->addItem("57600", 57600);
		ui.bitBox->addItem("115200", 115200);
		//	ui.bitBox->addItem("230400", 230400);
		//	ui.bitBox->addItem("460800", 460800);
		printToConsole("���ֿ��ö˿�~!");
		ui.openButton->setEnabled(true);
	}
	else
	{
		ui.beginButton->setEnabled(false);
		ui.sendButton->setEnabled(false);
		ui.openButton->setEnabled(false);
		printToConsole("���޿��ö˿� QAQ");
	}
}
