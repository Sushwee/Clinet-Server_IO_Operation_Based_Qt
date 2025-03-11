/********************************************************************************
** Form generated from reading UI file 'maindialog.ui'
**
** Created by: Qt User Interface Compiler version 6.8.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINDIALOG_H
#define UI_MAINDIALOG_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>

QT_BEGIN_NAMESPACE

class Ui_MainDialog
{
public:
    QLabel *label;
    QLabel *label_2;
    QComboBox *comboBox_ServerIP;
    QSpinBox *spinBox_ServerPort;
    QPushButton *pushButton_ConnectServer;
    QPushButton *pushButton_Disconnect;
    QPlainTextEdit *plainTextEdit_MsgList;
    QPlainTextEdit *plainTextEdit_SendMsg;
    QProgressBar *progressBar;
    QPushButton *pushButton_SelectFile;
    QPushButton *pushButton_SendFile;
    QGroupBox *groupBox;
    QGroupBox *groupBox_2;
    QGroupBox *groupBox_3;
    QPushButton *pushButton_Exit;
    QPushButton *pushButton_Clear;
    QPushButton *pushButton_SendMsg;
    QGroupBox *groupBox_4;

    void setupUi(QDialog *MainDialog)
    {
        if (MainDialog->objectName().isEmpty())
            MainDialog->setObjectName("MainDialog");
        MainDialog->resize(813, 608);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/new/prefix1/image/logo.jpg"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        MainDialog->setWindowIcon(icon);
        label = new QLabel(MainDialog);
        label->setObjectName("label");
        label->setGeometry(QRect(50, 20, 101, 19));
        QFont font;
        font.setFamilies({QString::fromUtf8("\345\276\256\350\275\257\351\233\205\351\273\221")});
        font.setPointSize(10);
        label->setFont(font);
        label_2 = new QLabel(MainDialog);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(320, 20, 101, 21));
        label_2->setFont(font);
        comboBox_ServerIP = new QComboBox(MainDialog);
        comboBox_ServerIP->addItem(QString());
        comboBox_ServerIP->setObjectName("comboBox_ServerIP");
        comboBox_ServerIP->setGeometry(QRect(160, 20, 121, 25));
        comboBox_ServerIP->setFont(font);
        comboBox_ServerIP->setEditable(true);
        spinBox_ServerPort = new QSpinBox(MainDialog);
        spinBox_ServerPort->setObjectName("spinBox_ServerPort");
        spinBox_ServerPort->setGeometry(QRect(420, 20, 81, 25));
        spinBox_ServerPort->setFont(font);
        spinBox_ServerPort->setMaximum(65535);
        spinBox_ServerPort->setValue(6688);
        pushButton_ConnectServer = new QPushButton(MainDialog);
        pushButton_ConnectServer->setObjectName("pushButton_ConnectServer");
        pushButton_ConnectServer->setGeometry(QRect(530, 20, 121, 31));
        pushButton_ConnectServer->setFont(font);
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/new/prefix1/image/connect.jpg"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButton_ConnectServer->setIcon(icon1);
        pushButton_Disconnect = new QPushButton(MainDialog);
        pushButton_Disconnect->setObjectName("pushButton_Disconnect");
        pushButton_Disconnect->setGeometry(QRect(660, 20, 121, 31));
        pushButton_Disconnect->setFont(font);
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/new/prefix1/image/disconnect.jpg"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButton_Disconnect->setIcon(icon2);
        plainTextEdit_MsgList = new QPlainTextEdit(MainDialog);
        plainTextEdit_MsgList->setObjectName("plainTextEdit_MsgList");
        plainTextEdit_MsgList->setGeometry(QRect(50, 90, 731, 281));
        plainTextEdit_MsgList->setFont(font);
        plainTextEdit_SendMsg = new QPlainTextEdit(MainDialog);
        plainTextEdit_SendMsg->setObjectName("plainTextEdit_SendMsg");
        plainTextEdit_SendMsg->setGeometry(QRect(50, 410, 731, 81));
        plainTextEdit_SendMsg->setFont(font);
        progressBar = new QProgressBar(MainDialog);
        progressBar->setObjectName("progressBar");
        progressBar->setGeometry(QRect(50, 560, 331, 23));
        progressBar->setFont(font);
        progressBar->setValue(0);
        pushButton_SelectFile = new QPushButton(MainDialog);
        pushButton_SelectFile->setObjectName("pushButton_SelectFile");
        pushButton_SelectFile->setGeometry(QRect(440, 560, 101, 28));
        pushButton_SelectFile->setFont(font);
        QIcon icon3;
        icon3.addFile(QString::fromUtf8(":/new/prefix1/image/openfile.jpg"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButton_SelectFile->setIcon(icon3);
        pushButton_SendFile = new QPushButton(MainDialog);
        pushButton_SendFile->setObjectName("pushButton_SendFile");
        pushButton_SendFile->setGeometry(QRect(560, 560, 101, 28));
        pushButton_SendFile->setFont(font);
        QIcon icon4;
        icon4.addFile(QString::fromUtf8(":/new/prefix1/image/sendfile.jpg"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButton_SendFile->setIcon(icon4);
        groupBox = new QGroupBox(MainDialog);
        groupBox->setObjectName("groupBox");
        groupBox->setGeometry(QRect(40, 10, 751, 51));
        groupBox_2 = new QGroupBox(MainDialog);
        groupBox_2->setObjectName("groupBox_2");
        groupBox_2->setGeometry(QRect(40, 70, 751, 311));
        QFont font1;
        font1.setFamilies({QString::fromUtf8("\345\276\256\350\275\257\351\233\205\351\273\221")});
        groupBox_2->setFont(font1);
        groupBox_3 = new QGroupBox(MainDialog);
        groupBox_3->setObjectName("groupBox_3");
        groupBox_3->setGeometry(QRect(40, 390, 751, 141));
        groupBox_3->setFont(font1);
        pushButton_Exit = new QPushButton(groupBox_3);
        pushButton_Exit->setObjectName("pushButton_Exit");
        pushButton_Exit->setGeometry(QRect(400, 110, 101, 28));
        pushButton_Exit->setFont(font);
        QIcon icon5;
        icon5.addFile(QString::fromUtf8(":/new/prefix1/image/exit.jpg"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButton_Exit->setIcon(icon5);
        pushButton_Clear = new QPushButton(groupBox_3);
        pushButton_Clear->setObjectName("pushButton_Clear");
        pushButton_Clear->setGeometry(QRect(520, 110, 101, 28));
        pushButton_Clear->setFont(font);
        QIcon icon6;
        icon6.addFile(QString::fromUtf8(":/new/prefix1/image/clear.jpg"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButton_Clear->setIcon(icon6);
        pushButton_SendMsg = new QPushButton(groupBox_3);
        pushButton_SendMsg->setObjectName("pushButton_SendMsg");
        pushButton_SendMsg->setGeometry(QRect(640, 110, 93, 28));
        pushButton_SendMsg->setFont(font);
        QIcon icon7;
        icon7.addFile(QString::fromUtf8(":/new/prefix1/image/sendmsg.jpg"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButton_SendMsg->setIcon(icon7);
        groupBox_4 = new QGroupBox(MainDialog);
        groupBox_4->setObjectName("groupBox_4");
        groupBox_4->setGeometry(QRect(40, 530, 751, 71));
        groupBox_4->raise();
        groupBox_3->raise();
        groupBox_2->raise();
        groupBox->raise();
        label->raise();
        label_2->raise();
        comboBox_ServerIP->raise();
        spinBox_ServerPort->raise();
        pushButton_ConnectServer->raise();
        pushButton_Disconnect->raise();
        plainTextEdit_MsgList->raise();
        plainTextEdit_SendMsg->raise();
        progressBar->raise();
        pushButton_SelectFile->raise();
        pushButton_SendFile->raise();

        retranslateUi(MainDialog);

        QMetaObject::connectSlotsByName(MainDialog);
    } // setupUi

    void retranslateUi(QDialog *MainDialog)
    {
        MainDialog->setWindowTitle(QCoreApplication::translate("MainDialog", "\345\256\242\346\210\267\347\253\257\344\270\216\346\234\215\345\212\241\345\231\250\346\236\266\346\236\204\347\263\273\347\273\237-TCP\345\256\242\346\210\267\347\253\257", nullptr));
        label->setText(QCoreApplication::translate("MainDialog", "\346\234\215\345\212\241\345\231\250IP\345\234\260\345\235\200", nullptr));
        label_2->setText(QCoreApplication::translate("MainDialog", "\346\234\215\345\212\241\345\231\250\347\253\257\345\217\243", nullptr));
        comboBox_ServerIP->setItemText(0, QCoreApplication::translate("MainDialog", "127.0.0.1", nullptr));

        pushButton_ConnectServer->setText(QCoreApplication::translate("MainDialog", "\350\277\236\346\216\245\346\234\215\345\212\241\345\231\250", nullptr));
        pushButton_Disconnect->setText(QCoreApplication::translate("MainDialog", "\346\226\255\345\274\200\346\234\215\345\212\241\345\231\250", nullptr));
        pushButton_SelectFile->setText(QCoreApplication::translate("MainDialog", "\351\200\211\346\213\251\346\226\207\344\273\266", nullptr));
        pushButton_SendFile->setText(QCoreApplication::translate("MainDialog", "\345\217\221\351\200\201\346\226\207\344\273\266", nullptr));
        groupBox->setTitle(QString());
        groupBox_2->setTitle(QCoreApplication::translate("MainDialog", "\346\266\210\346\201\257\345\210\227\350\241\250", nullptr));
        groupBox_3->setTitle(QCoreApplication::translate("MainDialog", "\345\217\221\351\200\201\346\266\210\346\201\257\346\241\206", nullptr));
        pushButton_Exit->setText(QCoreApplication::translate("MainDialog", "\351\200\200\345\207\272\347\263\273\347\273\237", nullptr));
        pushButton_Clear->setText(QCoreApplication::translate("MainDialog", "\346\270\205\351\231\244\346\266\210\346\201\257", nullptr));
        pushButton_SendMsg->setText(QCoreApplication::translate("MainDialog", "\345\217\221\351\200\201", nullptr));
        groupBox_4->setTitle(QCoreApplication::translate("MainDialog", "\344\274\240\350\276\223\346\226\207\344\273\266\350\207\263\346\234\215\345\212\241\345\231\250", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainDialog: public Ui_MainDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINDIALOG_H
