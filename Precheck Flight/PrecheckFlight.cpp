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
		printToConsole("关闭串口");
		if (worker && !worker->stopThread)
		{
			worker->closeThread();
		}
		portCommunicator->Close();
		ui.openButton->setText(tr("打开串口"));
		ui.statusLabel->setText(tr("端口未打开"));
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
			printToConsole("打开串口成功");
			printToConsole("端口" + ui.commBox->currentData().toString() + ", 波特率" + ui.bitBox->currentData().toString() + ", 连接成功~");
			ui.openButton->setText(tr("关闭串口"));
			ui.statusLabel->setText(tr("未检测到飞控"));
			ui.beginButton->setEnabled(true);
			ui.sendButton->setEnabled(true);
			ui.commBox->setEnabled(false);
			ui.bitBox->setEnabled(false);
			ui.testButton->setEnabled(false);
		}
		else
		{
			ui.exportButton->setEnabled(false);
			ui.statusLabel->setText(tr("端口未打开"));
			printToConsole("端口打开失败, 请重试!");
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
		ui.tableWidget->setItem(state - 1, 0, new QTableWidgetItem(PrecheckStateMachine::getStateText(state))); // 项目
		ui.tableWidget->setItem(state - 1, 1, status_item); // 状态
		ui.tableWidget->setItem(state - 1, 2, new QTableWidgetItem(trail)); // 计数
		ui.tableWidget->setItem(state - 1, 3, new QTableWidgetItem(message)); // 信息
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
		printToConsole("开始测试");
		ui.sendButton->setEnabled(false);
		ui.testButton->setEnabled(false);
		ui.beginButton->setText(tr("取消"));
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
			result = "开始";
			status_item->setIcon(QApplication::style()->standardIcon((QStyle::StandardPixmap) ICON_BEGIN));
			break;
		case PrecheckStateMachine::FAILED:
			result = "失败";
			status_item->setIcon(QApplication::style()->standardIcon((QStyle::StandardPixmap) ICON_FAILED));
			break;
		case PrecheckStateMachine::FINISH:
			result = "通过";
			status_item->setIcon(QApplication::style()->standardIcon((QStyle::StandardPixmap) ICON_FINISH));
			break;
		case PrecheckStateMachine::PROCESSING:
			result = "等待";
			status_item->setIcon(QApplication::style()->standardIcon((QStyle::StandardPixmap) ICON_PROCESSING));
			break;
		default:
			result = "未知";
			status_item->setIcon(QApplication::style()->standardIcon((QStyle::StandardPixmap) ICON_BEGIN));
			break;
		}
		ui.detailWidget->setItem(count, 0, new QTableWidgetItem(PrecheckStateMachine::getStateText(state))); // 项目
		ui.detailWidget->setItem(count, 1, new QTableWidgetItem(function)); // 功能
		ui.detailWidget->setItem(count, 3, new QTableWidgetItem(message)); // 信息
		ui.detailWidget->setItem(count, 4, new QTableWidgetItem(result)); // 信息
		ui.detailWidget->setItem(count, 2, status_item); // 状态
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
	ui.beginButton->setText(tr("开始"));
	QMessageBox::information(this, "检测完成", "装前检测已完成",
		QMessageBox::Ok, QMessageBox::Ok);
	printToConsole("测试完成 = =");
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
			ui.statusLabel->setText(tr("飞控已连接"));
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
	//获取保存路径
	/*
	QString filepath = QFileDialog::getSaveFileName(this, tr("Save"), ".", tr(" (*.xlsx)"));
	printToConsole("开始导出...");
	if (!filepath.isEmpty()) {
		QAxObject *excel = new QAxObject(this);
		//连接Excel控件
		excel->setControl("Excel.Application");
		//不显示窗体
		excel->dynamicCall("SetVisible (bool Visible)", "false");
		//不显示任何警告信息。如果为true那么在关闭是会出现类似“文件已修改，是否保存”的提示
		excel->setProperty("DisplayAlerts", false);
		//获取工作簿集合
		QApplication::processEvents();
		QAxObject *workbooks = excel->querySubObject("WorkBooks");
		//新建一个工作簿
		workbooks->dynamicCall("Add");
		//获取当前工作簿
		QAxObject *workbook = excel->querySubObject("ActiveWorkBook");
		//获取工作表集合
		QAxObject *worksheets = workbook->querySubObject("Sheets");
		//获取工作表集合的工作表1，即sheet1
		QAxObject *worksheet = worksheets->querySubObject("Item(int)", 1);
		QApplication::processEvents();
		QAxObject *cellA, *cellB, *cellC, *cellD;
		//设置标题
		int cellrow = 1;
		//设置要操作的单元格，如A1
		QString A = "A" + QString::number(cellrow);
		QString B = "B" + QString::number(cellrow);
		QString C = "C" + QString::number(cellrow);
		QString D = "D" + QString::number(cellrow);
		//获取单元格
		cellA = worksheet->querySubObject("Range(QVariant, QVariant)", A);
		cellB = worksheet->querySubObject("Range(QVariant, QVariant)", B);
		cellC = worksheet->querySubObject("Range(QVariant, QVariant)", C);
		cellD = worksheet->querySubObject("Range(QVariant, QVariant)", D);
		QApplication::processEvents();
		//设置单元格的表头值
		cellA->dynamicCall("SetValue(const QVariant&)", QVariant(ui.detailWidget->horizontalHeaderItem(0)->text()));
		cellB->dynamicCall("SetValue(const QVariant&)", QVariant(ui.detailWidget->horizontalHeaderItem(1)->text()));
		cellC->dynamicCall("SetValue(const QVariant&)", QVariant(ui.detailWidget->horizontalHeaderItem(4)->text()));
		cellD->dynamicCall("SetValue(const QVariant&)", QVariant(ui.detailWidget->horizontalHeaderItem(3)->text()));
		cellrow++;
		QApplication::processEvents();
		int rows = ui.detailWidget->rowCount();
		//设置表格数据
		for (int i = 0; i<rows; i++) {
			//设置要操作的单元格，如A1，A2，A3，A4
			QString A = "A" + QString::number(cellrow);
			QString B = "B" + QString::number(cellrow);
			QString C = "C" + QString::number(cellrow);
			QString D = "D" + QString::number(cellrow);
			QApplication::processEvents();
			//获取单元格
			cellA = worksheet->querySubObject("Range(QVariant, QVariant)", A);
			cellB = worksheet->querySubObject("Range(QVariant, QVariant)", B);
			cellC = worksheet->querySubObject("Range(QVariant, QVariant)", C);
			cellD = worksheet->querySubObject("Range(QVariant, QVariant)", D);
			//设置单元格的值
			cellA->dynamicCall("SetValue(const QVariant&)", QVariant(ui.detailWidget->item(i, 0)->data(Qt::DisplayRole).toString()));
			cellB->dynamicCall("SetValue(const QVariant&)", QVariant(ui.detailWidget->item(i, 1)->data(Qt::DisplayRole).toString()));
			cellC->dynamicCall("SetValue(const QVariant&)", QVariant(ui.detailWidget->item(i, 4)->data(Qt::DisplayRole).toString()));
			cellD->dynamicCall("SetValue(const QVariant&)", QVariant(ui.detailWidget->item(i, 3)->data(Qt::DisplayRole).toString()));
			cellrow++;
			QApplication::processEvents();
		}

		workbook->dynamicCall("SaveAs(const QString&)", QDir::toNativeSeparators(filepath));//保存至filepath，注意一定要用QDir::toNativeSeparators将路径中的"/"转换为"\"，不然一定保存不了。
		workbook->dynamicCall("Close()");//关闭工作簿
		excel->dynamicCall("Quit()");//关闭excel
		delete excel;
		excel = NULL;
		printToConsole("导出成功啦！！！");
	}
	*/
	QString fileName = QFileDialog::getSaveFileName(this, tr("保存检测结果"), QString(), tr("Rich Text Files (*.rtf);;"));
	if (fileName.isEmpty())
	{
		printToConsole("文件名为空!");
		QMessageBox::critical(this, "导出错误", "文件名为空!", QMessageBox::Ok, QMessageBox::Ok);
		ui.exportButton->setEnabled(true);
		return;
	}
	if (!fileName.endsWith(QLatin1String(".rtf")))
		fileName += QLatin1String(".rtf");

	// 上面那块代码，用于用户手动选择保存路径， 以及输入文件名后， 如果用户没有加上后缀，自动加上文件后缀。
	QFile file(fileName);
	if (!file.open(QIODevice::ReadWrite | QIODevice::Text)) {
		ui.exportButton->setEnabled(true);
		printToConsole("文件打开失败!");
		QMessageBox::critical(this, "导出错误", "文件打开失败!", QMessageBox::Ok, QMessageBox::Ok);
		return;
	}
	// 上面这一小段，以文本的方式，打开并读写文件。

	QDomDocument doc;  //xml，rtf 等多种文本格式生成所需要的类。
	doc.setContent(&file);
	QDomElement root = doc.documentElement();
	QDomElement body;
	if (!root.isNull()) {
		body = root.firstChildElement(QLatin1String("body"));  //如果用户保存的文件里面有内容， 查找是否是rtf格式的相关元素。
	}
	if (body.isNull()) {
		root = doc.createElement(QLatin1String("html"));
		QDomElement head = doc.createElement(QLatin1String("head"));
		QDomElement meta = doc.createElement(QLatin1String("meta"));
		meta.setAttribute(QLatin1String("http-equiv"), QLatin1String("Content-Type"));
		meta.setAttribute(QLatin1String("content"), QLatin1String("text/html; charset=utf-8"));
		//rtf格式就是一个html格式文件， 一样的结构， 需要文件头， body内容。
		head.appendChild(meta);
		root.appendChild(head);
		body = doc.createElement(QLatin1String("body"));
		root.appendChild(body);
		doc.appendChild(root);
	}
	// 上面这一小块主要写文件的文件头部内容。
	if (body.isNull())
	{
		QMessageBox::critical(this, "导出错误", "RTF 文件无法覆盖!", QMessageBox::Ok, QMessageBox::Ok);
		printToConsole("RTF 文件头为空!");
		return;
	}
	body.setAttribute(QLatin1String("style"), QLatin1String("font-family: 'Arial', 'Microsoft YaHei', '黑体', '宋体', 'sans-serif'"));
	QDomElement title = doc.createElement(QLatin1String("h1"));
	QDomText titleText = doc.createTextNode(tr("飞控装前检测报告\n"));
	title.setAttribute(QLatin1String("style"), QLatin1String("text-align: center;font-weight: bold"));
	title.appendChild(titleText);
	body.appendChild(title);
	QDomElement time = doc.createElement(QLatin1String("h2"));
	QDomText timeText = doc.createTextNode(QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss"));
	time.setAttribute(QLatin1String("style"), QLatin1String("text-align: right"));
	time.appendChild(timeText);
	body.appendChild(time);
	// 创建表
	QDomElement table = doc.createElement(QLatin1String("table"));
	table.setAttribute(QLatin1String("style"), QLatin1String("border: 1px solid black;text-align: center;"));
	QDomElement table_header = doc.createElement(QLatin1String("tr"));
	//设置单元格的表头值
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
	//设置表格数据
	for (int i = 0; i < rows; i++) {
		QDomElement row = doc.createElement(QLatin1String("tr"));
		
		
		//设置单元格的值
		for (int j = 0; j < 4; j++)
		{
			QDomElement row_element = doc.createElement(QLatin1String("td"));
			row_element.setAttribute(QLatin1String("style"), QLatin1String("border: 1px solid black;"));
			QDomText content = doc.createTextNode(ui.detailWidget->item(i, column_map[j])->text());

			if (j == 2)
			{
				if (QString::compare(ui.detailWidget->item(i, column_map[j])->text(), QString("通过")))
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
	printToConsole("导出成功啦！！！");
	QMessageBox::information(this, "导出成功", "RTF 文件成功导出!",
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
		printToConsole("发送完成!");
}

void PrecheckFlight::testComm()
{
	if (portCommunicator->IsOpen()) 
	{
		openPort();
	}
	ui.openButton->setEnabled(false);
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
		// ui.bitBox->addItem("38400", 38400);
		// ui.bitBox->addItem("57600", 57600);
		ui.bitBox->addItem("115200", 115200);
		//	ui.bitBox->addItem("230400", 230400);
		//	ui.bitBox->addItem("460800", 460800);
		printToConsole("发现可用端口~!");
		ui.openButton->setEnabled(true);
	}
	else
	{
		ui.beginButton->setEnabled(false);
		ui.sendButton->setEnabled(false);
		ui.openButton->setEnabled(false);
		printToConsole("暂无可用端口 QAQ");
	}
}
