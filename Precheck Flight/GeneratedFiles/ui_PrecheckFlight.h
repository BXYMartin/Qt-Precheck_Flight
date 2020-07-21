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
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_PrecheckFlightClass
{
public:
    QWidget *centralWidget;
    QGroupBox *groupBox;
    QWidget *formLayoutWidget;
    QFormLayout *formLayout;
    QLabel *label;
    QLabel *label_2;
    QComboBox *bitBox;
    QComboBox *commBox;
    QPushButton *testButton;
    QGroupBox *groupBox_2;
    QPlainTextEdit *consoleWindow;
    QGroupBox *groupBox_3;
    QPlainTextEdit *sendComm;
    QPlainTextEdit *receiveComm;
    QPushButton *sendButton;
    QPushButton *pushButton_2;
    QGroupBox *groupBox_4;
    QPushButton *beginButton;
    QTableWidget *tableWidget;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *PrecheckFlightClass)
    {
        if (PrecheckFlightClass->objectName().isEmpty())
            PrecheckFlightClass->setObjectName(QString::fromUtf8("PrecheckFlightClass"));
        PrecheckFlightClass->resize(600, 400);
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(PrecheckFlightClass->sizePolicy().hasHeightForWidth());
        PrecheckFlightClass->setSizePolicy(sizePolicy);
        PrecheckFlightClass->setUnifiedTitleAndToolBarOnMac(true);
        centralWidget = new QWidget(PrecheckFlightClass);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        groupBox = new QGroupBox(centralWidget);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        groupBox->setGeometry(QRect(10, 10, 161, 111));
        QFont font;
        font.setFamily(QString::fromUtf8("\351\273\221\344\275\223"));
        font.setPointSize(10);
        groupBox->setFont(font);
        formLayoutWidget = new QWidget(groupBox);
        formLayoutWidget->setObjectName(QString::fromUtf8("formLayoutWidget"));
        formLayoutWidget->setGeometry(QRect(10, 20, 141, 51));
        formLayout = new QFormLayout(formLayoutWidget);
        formLayout->setSpacing(6);
        formLayout->setContentsMargins(11, 11, 11, 11);
        formLayout->setObjectName(QString::fromUtf8("formLayout"));
        formLayout->setFieldGrowthPolicy(QFormLayout::ExpandingFieldsGrow);
        formLayout->setLabelAlignment(Qt::AlignCenter);
        formLayout->setFormAlignment(Qt::AlignCenter);
        formLayout->setContentsMargins(0, 0, 0, 0);
        label = new QLabel(formLayoutWidget);
        label->setObjectName(QString::fromUtf8("label"));
        QFont font1;
        font1.setFamily(QString::fromUtf8("\345\256\213\344\275\223"));
        label->setFont(font1);

        formLayout->setWidget(0, QFormLayout::LabelRole, label);

        label_2 = new QLabel(formLayoutWidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setFont(font1);

        formLayout->setWidget(1, QFormLayout::LabelRole, label_2);

        bitBox = new QComboBox(formLayoutWidget);
        bitBox->setObjectName(QString::fromUtf8("bitBox"));
        sizePolicy.setHeightForWidth(bitBox->sizePolicy().hasHeightForWidth());
        bitBox->setSizePolicy(sizePolicy);
        QFont font2;
        font2.setFamily(QString::fromUtf8("Courier New"));
        bitBox->setFont(font2);

        formLayout->setWidget(1, QFormLayout::FieldRole, bitBox);

        commBox = new QComboBox(formLayoutWidget);
        commBox->setObjectName(QString::fromUtf8("commBox"));
        sizePolicy.setHeightForWidth(commBox->sizePolicy().hasHeightForWidth());
        commBox->setSizePolicy(sizePolicy);
        commBox->setFont(font2);

        formLayout->setWidget(0, QFormLayout::FieldRole, commBox);

        testButton = new QPushButton(groupBox);
        testButton->setObjectName(QString::fromUtf8("testButton"));
        testButton->setGeometry(QRect(40, 80, 75, 23));
        groupBox_2 = new QGroupBox(centralWidget);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        groupBox_2->setGeometry(QRect(10, 130, 161, 211));
        groupBox_2->setFont(font);
        consoleWindow = new QPlainTextEdit(groupBox_2);
        consoleWindow->setObjectName(QString::fromUtf8("consoleWindow"));
        consoleWindow->setGeometry(QRect(10, 20, 141, 181));
        QFont font3;
        font3.setFamily(QString::fromUtf8("Courier New"));
        font3.setPointSize(10);
        consoleWindow->setFont(font3);
        consoleWindow->viewport()->setProperty("cursor", QVariant(QCursor(Qt::PointingHandCursor)));
        consoleWindow->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        consoleWindow->setReadOnly(true);
        groupBox_3 = new QGroupBox(centralWidget);
        groupBox_3->setObjectName(QString::fromUtf8("groupBox_3"));
        groupBox_3->setGeometry(QRect(180, 10, 401, 111));
        groupBox_3->setFont(font);
        sendComm = new QPlainTextEdit(groupBox_3);
        sendComm->setObjectName(QString::fromUtf8("sendComm"));
        sendComm->setGeometry(QRect(40, 20, 151, 81));
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
        groupBox_4 = new QGroupBox(centralWidget);
        groupBox_4->setObjectName(QString::fromUtf8("groupBox_4"));
        groupBox_4->setGeometry(QRect(180, 130, 401, 211));
        groupBox_4->setFont(font);
        beginButton = new QPushButton(groupBox_4);
        beginButton->setObjectName(QString::fromUtf8("beginButton"));
        beginButton->setGeometry(QRect(10, 170, 121, 23));
        tableWidget = new QTableWidget(groupBox_4);
        if (tableWidget->columnCount() < 3)
            tableWidget->setColumnCount(3);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        tableWidget->setObjectName(QString::fromUtf8("tableWidget"));
        tableWidget->setGeometry(QRect(140, 10, 251, 181));
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
        PrecheckFlightClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(PrecheckFlightClass);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 600, 22));
        PrecheckFlightClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(PrecheckFlightClass);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        PrecheckFlightClass->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(PrecheckFlightClass);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        PrecheckFlightClass->setStatusBar(statusBar);

        retranslateUi(PrecheckFlightClass);

        QMetaObject::connectSlotsByName(PrecheckFlightClass);
    } // setupUi

    void retranslateUi(QMainWindow *PrecheckFlightClass)
    {
        PrecheckFlightClass->setWindowTitle(QApplication::translate("PrecheckFlightClass", "PrecheckFlight", nullptr));
        groupBox->setTitle(QApplication::translate("PrecheckFlightClass", "\344\270\262\345\217\243\351\205\215\347\275\256", nullptr));
        label->setText(QApplication::translate("PrecheckFlightClass", "\344\270\262\345\217\243", nullptr));
        label_2->setText(QApplication::translate("PrecheckFlightClass", "\346\263\242\347\211\271\347\216\207", nullptr));
        testButton->setText(QApplication::translate("PrecheckFlightClass", "\351\207\215\346\226\260\346\243\200\346\265\213", nullptr));
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
        ___qtablewidgetitem2->setText(QApplication::translate("PrecheckFlightClass", "\344\277\241\346\201\257", nullptr));
    } // retranslateUi

};

namespace Ui {
    class PrecheckFlightClass: public Ui_PrecheckFlightClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PRECHECKFLIGHT_H
