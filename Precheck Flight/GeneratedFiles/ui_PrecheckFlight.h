/********************************************************************************
** Form generated from reading UI file 'PrecheckFlight.ui'
**
** Created by: Qt User Interface Compiler version 5.12.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PRECHECKFLIGHT_H
#define UI_PRECHECKFLIGHT_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_PrecheckFlightClass
{
public:
    QWidget *centralWidget;
    QGroupBox *groupBox;
    QPushButton *testButton;
    QPushButton *openButton;
    QLabel *label;
    QLabel *label_2;
    QComboBox *commBox;
    QComboBox *bitBox;
    QLabel *statusLabel;
    QGroupBox *groupBox_2;
    QPlainTextEdit *consoleWindow;
    QGroupBox *groupBox_3;
    QPlainTextEdit *sendComm;
    QPlainTextEdit *receiveComm;
    QPushButton *sendButton;
    QPushButton *pushButton_2;
    QComboBox *digitBox;
    QGroupBox *groupBox_4;
    QPushButton *beginButton;
    QTableWidget *tableWidget;
    QTableWidget *detailWidget;
    QPushButton *exportButton;

    void setupUi(QMainWindow *PrecheckFlightClass)
    {
        if (PrecheckFlightClass->objectName().isEmpty())
            PrecheckFlightClass->setObjectName(QString::fromUtf8("PrecheckFlightClass"));
        PrecheckFlightClass->resize(760, 499);
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(PrecheckFlightClass->sizePolicy().hasHeightForWidth());
        PrecheckFlightClass->setSizePolicy(sizePolicy);
        PrecheckFlightClass->setMinimumSize(QSize(0, 0));
        PrecheckFlightClass->setUnifiedTitleAndToolBarOnMac(true);
        centralWidget = new QWidget(PrecheckFlightClass);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        groupBox = new QGroupBox(centralWidget);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        groupBox->setGeometry(QRect(10, 10, 571, 51));
        QFont font;
        font.setFamily(QString::fromUtf8("\351\273\221\344\275\223"));
        font.setPointSize(10);
        groupBox->setFont(font);
        testButton = new QPushButton(groupBox);
        testButton->setObjectName(QString::fromUtf8("testButton"));
        testButton->setGeometry(QRect(420, 18, 61, 23));
        openButton = new QPushButton(groupBox);
        openButton->setObjectName(QString::fromUtf8("openButton"));
        openButton->setGeometry(QRect(500, 18, 61, 23));
        label = new QLabel(groupBox);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(20, 20, 31, 17));
        QFont font1;
        font1.setFamily(QString::fromUtf8("\351\273\221\344\275\223"));
        label->setFont(font1);
        label_2 = new QLabel(groupBox);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(150, 20, 30, 17));
        label_2->setFont(font1);
        commBox = new QComboBox(groupBox);
        commBox->setObjectName(QString::fromUtf8("commBox"));
        commBox->setGeometry(QRect(60, 20, 67, 19));
        sizePolicy.setHeightForWidth(commBox->sizePolicy().hasHeightForWidth());
        commBox->setSizePolicy(sizePolicy);
        QFont font2;
        font2.setFamily(QString::fromUtf8("Courier New"));
        commBox->setFont(font2);
        bitBox = new QComboBox(groupBox);
        bitBox->setObjectName(QString::fromUtf8("bitBox"));
        bitBox->setGeometry(QRect(190, 20, 67, 19));
        sizePolicy.setHeightForWidth(bitBox->sizePolicy().hasHeightForWidth());
        bitBox->setSizePolicy(sizePolicy);
        bitBox->setFont(font2);
        statusLabel = new QLabel(groupBox);
        statusLabel->setObjectName(QString::fromUtf8("statusLabel"));
        statusLabel->setGeometry(QRect(300, 20, 71, 17));
        QFont font3;
        font3.setFamily(QString::fromUtf8("\351\273\221\344\275\223"));
        font3.setPointSize(12);
        statusLabel->setFont(font3);
        statusLabel->setStyleSheet(QString::fromUtf8("color: rgb(138, 138, 138)"));
        statusLabel->setAlignment(Qt::AlignCenter);
        groupBox_2 = new QGroupBox(centralWidget);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        groupBox_2->setGeometry(QRect(590, 10, 161, 481));
        groupBox_2->setFont(font);
        consoleWindow = new QPlainTextEdit(groupBox_2);
        consoleWindow->setObjectName(QString::fromUtf8("consoleWindow"));
        consoleWindow->setGeometry(QRect(10, 20, 141, 451));
        QFont font4;
        font4.setFamily(QString::fromUtf8("Courier New"));
        font4.setPointSize(10);
        consoleWindow->setFont(font4);
        consoleWindow->viewport()->setProperty("cursor", QVariant(QCursor(Qt::PointingHandCursor)));
        consoleWindow->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        consoleWindow->setReadOnly(true);
        groupBox_3 = new QGroupBox(centralWidget);
        groupBox_3->setObjectName(QString::fromUtf8("groupBox_3"));
        groupBox_3->setGeometry(QRect(770, 10, 401, 111));
        groupBox_3->setFont(font);
        sendComm = new QPlainTextEdit(groupBox_3);
        sendComm->setObjectName(QString::fromUtf8("sendComm"));
        sendComm->setGeometry(QRect(40, 20, 151, 61));
        receiveComm = new QPlainTextEdit(groupBox_3);
        receiveComm->setObjectName(QString::fromUtf8("receiveComm"));
        receiveComm->setGeometry(QRect(240, 20, 151, 81));
        receiveComm->setReadOnly(true);
        sendButton = new QPushButton(groupBox_3);
        sendButton->setObjectName(QString::fromUtf8("sendButton"));
        sendButton->setGeometry(QRect(10, 20, 21, 81));
        sendButton->setAcceptDrops(false);
        sendButton->setFlat(false);
        pushButton_2 = new QPushButton(groupBox_3);
        pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));
        pushButton_2->setEnabled(false);
        pushButton_2->setGeometry(QRect(210, 20, 21, 81));
        pushButton_2->setAcceptDrops(false);
        pushButton_2->setFlat(false);
        digitBox = new QComboBox(groupBox_3);
        digitBox->setObjectName(QString::fromUtf8("digitBox"));
        digitBox->setGeometry(QRect(40, 80, 151, 22));
        digitBox->setFont(font2);
        groupBox_4 = new QGroupBox(centralWidget);
        groupBox_4->setObjectName(QString::fromUtf8("groupBox_4"));
        groupBox_4->setGeometry(QRect(10, 70, 571, 421));
        groupBox_4->setFont(font);
        beginButton = new QPushButton(groupBox_4);
        beginButton->setObjectName(QString::fromUtf8("beginButton"));
        beginButton->setGeometry(QRect(10, 20, 271, 21));
        tableWidget = new QTableWidget(groupBox_4);
        if (tableWidget->columnCount() < 4)
            tableWidget->setColumnCount(4);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        __qtablewidgetitem->setTextAlignment(Qt::AlignCenter);
        tableWidget->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        __qtablewidgetitem1->setTextAlignment(Qt::AlignCenter);
        tableWidget->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        __qtablewidgetitem2->setTextAlignment(Qt::AlignCenter);
        tableWidget->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        __qtablewidgetitem3->setTextAlignment(Qt::AlignCenter);
        tableWidget->setHorizontalHeaderItem(3, __qtablewidgetitem3);
        tableWidget->setObjectName(QString::fromUtf8("tableWidget"));
        tableWidget->setGeometry(QRect(10, 50, 551, 91));
        QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(tableWidget->sizePolicy().hasHeightForWidth());
        tableWidget->setSizePolicy(sizePolicy1);
        tableWidget->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
        tableWidget->setSizeAdjustPolicy(QAbstractScrollArea::AdjustIgnored);
        tableWidget->setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);
        tableWidget->setHorizontalScrollMode(QAbstractItemView::ScrollPerPixel);
        tableWidget->horizontalHeader()->setMinimumSectionSize(12);
        tableWidget->horizontalHeader()->setDefaultSectionSize(50);
        tableWidget->horizontalHeader()->setStretchLastSection(true);
        tableWidget->verticalHeader()->setMinimumSectionSize(15);
        tableWidget->verticalHeader()->setDefaultSectionSize(20);
        detailWidget = new QTableWidget(groupBox_4);
        if (detailWidget->columnCount() < 5)
            detailWidget->setColumnCount(5);
        QTableWidgetItem *__qtablewidgetitem4 = new QTableWidgetItem();
        __qtablewidgetitem4->setTextAlignment(Qt::AlignCenter);
        detailWidget->setHorizontalHeaderItem(0, __qtablewidgetitem4);
        QTableWidgetItem *__qtablewidgetitem5 = new QTableWidgetItem();
        __qtablewidgetitem5->setTextAlignment(Qt::AlignCenter);
        detailWidget->setHorizontalHeaderItem(1, __qtablewidgetitem5);
        QTableWidgetItem *__qtablewidgetitem6 = new QTableWidgetItem();
        __qtablewidgetitem6->setTextAlignment(Qt::AlignCenter);
        detailWidget->setHorizontalHeaderItem(2, __qtablewidgetitem6);
        QTableWidgetItem *__qtablewidgetitem7 = new QTableWidgetItem();
        __qtablewidgetitem7->setTextAlignment(Qt::AlignCenter);
        detailWidget->setHorizontalHeaderItem(3, __qtablewidgetitem7);
        QTableWidgetItem *__qtablewidgetitem8 = new QTableWidgetItem();
        __qtablewidgetitem8->setTextAlignment(Qt::AlignCenter);
        detailWidget->setHorizontalHeaderItem(4, __qtablewidgetitem8);
        detailWidget->setObjectName(QString::fromUtf8("detailWidget"));
        detailWidget->setGeometry(QRect(10, 150, 551, 261));
        detailWidget->horizontalHeader()->setMinimumSectionSize(10);
        detailWidget->horizontalHeader()->setDefaultSectionSize(120);
        detailWidget->horizontalHeader()->setStretchLastSection(true);
        detailWidget->verticalHeader()->setMinimumSectionSize(15);
        detailWidget->verticalHeader()->setDefaultSectionSize(20);
        exportButton = new QPushButton(groupBox_4);
        exportButton->setObjectName(QString::fromUtf8("exportButton"));
        exportButton->setGeometry(QRect(290, 20, 271, 21));
        PrecheckFlightClass->setCentralWidget(centralWidget);

        retranslateUi(PrecheckFlightClass);

        QMetaObject::connectSlotsByName(PrecheckFlightClass);
    } // setupUi

    void retranslateUi(QMainWindow *PrecheckFlightClass)
    {
        PrecheckFlightClass->setWindowTitle(QApplication::translate("PrecheckFlightClass", "PrecheckFlight", nullptr));
        groupBox->setTitle(QApplication::translate("PrecheckFlightClass", "\344\270\262\345\217\243\351\205\215\347\275\256", nullptr));
        testButton->setText(QApplication::translate("PrecheckFlightClass", "\351\207\215\346\226\260\346\243\200\346\265\213", nullptr));
        openButton->setText(QApplication::translate("PrecheckFlightClass", "\346\211\223\345\274\200\344\270\262\345\217\243", nullptr));
        label->setText(QApplication::translate("PrecheckFlightClass", "\344\270\262\345\217\243\345\217\267", nullptr));
        label_2->setText(QApplication::translate("PrecheckFlightClass", "\346\263\242\347\211\271\347\216\207", nullptr));
        statusLabel->setText(QApplication::translate("PrecheckFlightClass", "\346\234\252\346\211\223\345\274\200\347\253\257\345\217\243", nullptr));
        groupBox_2->setTitle(QApplication::translate("PrecheckFlightClass", "\344\277\241\346\201\257", nullptr));
        groupBox_3->setTitle(QApplication::translate("PrecheckFlightClass", "\344\270\262\345\217\243\351\200\232\344\277\241", nullptr));
        sendButton->setText(QApplication::translate("PrecheckFlightClass", "\345\217\221\n"
"\351\200\201", nullptr));
        pushButton_2->setText(QApplication::translate("PrecheckFlightClass", "\346\216\245\n"
"\346\224\266", nullptr));
        groupBox_4->setTitle(QApplication::translate("PrecheckFlightClass", "\350\243\205\345\211\215\346\243\200\346\265\213", nullptr));
        beginButton->setText(QApplication::translate("PrecheckFlightClass", "\345\274\200\345\247\213", nullptr));
        QTableWidgetItem *___qtablewidgetitem = tableWidget->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QApplication::translate("PrecheckFlightClass", "\351\241\271\347\233\256", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidget->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QApplication::translate("PrecheckFlightClass", "\347\212\266\346\200\201", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = tableWidget->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QApplication::translate("PrecheckFlightClass", "\350\256\241\346\225\260", nullptr));
        QTableWidgetItem *___qtablewidgetitem3 = tableWidget->horizontalHeaderItem(3);
        ___qtablewidgetitem3->setText(QApplication::translate("PrecheckFlightClass", "\344\277\241\346\201\257", nullptr));
        QTableWidgetItem *___qtablewidgetitem4 = detailWidget->horizontalHeaderItem(0);
        ___qtablewidgetitem4->setText(QApplication::translate("PrecheckFlightClass", "\351\241\271\347\233\256", nullptr));
        QTableWidgetItem *___qtablewidgetitem5 = detailWidget->horizontalHeaderItem(1);
        ___qtablewidgetitem5->setText(QApplication::translate("PrecheckFlightClass", "\345\212\237\350\203\275", nullptr));
        QTableWidgetItem *___qtablewidgetitem6 = detailWidget->horizontalHeaderItem(2);
        ___qtablewidgetitem6->setText(QApplication::translate("PrecheckFlightClass", "\347\212\266\346\200\201", nullptr));
        QTableWidgetItem *___qtablewidgetitem7 = detailWidget->horizontalHeaderItem(3);
        ___qtablewidgetitem7->setText(QApplication::translate("PrecheckFlightClass", "\350\257\246\347\273\206\344\277\241\346\201\257", nullptr));
        QTableWidgetItem *___qtablewidgetitem8 = detailWidget->horizontalHeaderItem(4);
        ___qtablewidgetitem8->setText(QApplication::translate("PrecheckFlightClass", "\347\273\223\346\236\234", nullptr));
        exportButton->setText(QApplication::translate("PrecheckFlightClass", "\345\257\274\345\207\272\346\212\245\345\221\212", nullptr));
    } // retranslateUi

};

namespace Ui {
    class PrecheckFlightClass: public Ui_PrecheckFlightClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PRECHECKFLIGHT_H
