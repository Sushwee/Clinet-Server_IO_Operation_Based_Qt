/********************************************************************************
** Form generated from reading UI file 'dialog.ui'
**
** Created by: Qt User Interface Compiler version 6.8.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DIALOG_H
#define UI_DIALOG_H

#include <QtCore/QVariant>
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

class Ui_Dialog
{
public:
    QLabel *label;
    QLabel *label_2;
    QSpinBox *spinBox;
    QPlainTextEdit *plainTextEdit;
    QPushButton *pushButton;
    QPushButton *pushButton_2;
    QPlainTextEdit *plainTextEdit_2;
    QPushButton *pushButton_3;
    QPushButton *pushButton_4;
    QPushButton *pushButton_5;
    QLabel *label_5;
    QProgressBar *progressBar;
    QComboBox *comboBox;
    QGroupBox *groupBox;
    QGroupBox *groupBox_2;
    QGroupBox *groupBox_3;

    void setupUi(QDialog *Dialog)
    {
        if (Dialog->objectName().isEmpty())
            Dialog->setObjectName("Dialog");
        Dialog->resize(910, 710);
        label = new QLabel(Dialog);
        label->setObjectName("label");
        label->setGeometry(QRect(30, 30, 131, 19));
        QFont font;
        font.setPointSize(11);
        label->setFont(font);
        label_2 = new QLabel(Dialog);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(310, 30, 131, 21));
        label_2->setFont(font);
        spinBox = new QSpinBox(Dialog);
        spinBox->setObjectName("spinBox");
        spinBox->setGeometry(QRect(450, 30, 91, 25));
        plainTextEdit = new QPlainTextEdit(Dialog);
        plainTextEdit->setObjectName("plainTextEdit");
        plainTextEdit->setGeometry(QRect(30, 140, 841, 281));
        pushButton = new QPushButton(Dialog);
        pushButton->setObjectName("pushButton");
        pushButton->setGeometry(QRect(600, 30, 121, 31));
        pushButton_2 = new QPushButton(Dialog);
        pushButton_2->setObjectName("pushButton_2");
        pushButton_2->setGeometry(QRect(750, 30, 121, 31));
        plainTextEdit_2 = new QPlainTextEdit(Dialog);
        plainTextEdit_2->setObjectName("plainTextEdit_2");
        plainTextEdit_2->setGeometry(QRect(30, 490, 841, 111));
        pushButton_3 = new QPushButton(Dialog);
        pushButton_3->setObjectName("pushButton_3");
        pushButton_3->setGeometry(QRect(600, 620, 121, 31));
        pushButton_4 = new QPushButton(Dialog);
        pushButton_4->setObjectName("pushButton_4");
        pushButton_4->setGeometry(QRect(750, 620, 121, 31));
        pushButton_5 = new QPushButton(Dialog);
        pushButton_5->setObjectName("pushButton_5");
        pushButton_5->setGeometry(QRect(450, 620, 121, 31));
        label_5 = new QLabel(Dialog);
        label_5->setObjectName("label_5");
        label_5->setGeometry(QRect(30, 680, 131, 21));
        label_5->setFont(font);
        progressBar = new QProgressBar(Dialog);
        progressBar->setObjectName("progressBar");
        progressBar->setGeometry(QRect(170, 680, 391, 23));
        progressBar->setValue(0);
        comboBox = new QComboBox(Dialog);
        comboBox->setObjectName("comboBox");
        comboBox->setGeometry(QRect(160, 30, 101, 25));
        groupBox = new QGroupBox(Dialog);
        groupBox->setObjectName("groupBox");
        groupBox->setGeometry(QRect(20, 0, 861, 81));
        groupBox_2 = new QGroupBox(Dialog);
        groupBox_2->setObjectName("groupBox_2");
        groupBox_2->setGeometry(QRect(20, 100, 861, 331));
        QFont font1;
        font1.setPointSize(12);
        groupBox_2->setFont(font1);
        groupBox_3 = new QGroupBox(Dialog);
        groupBox_3->setObjectName("groupBox_3");
        groupBox_3->setGeometry(QRect(20, 460, 861, 201));
        groupBox_3->setFont(font1);
        groupBox_3->raise();
        groupBox_2->raise();
        groupBox->raise();
        label->raise();
        label_2->raise();
        spinBox->raise();
        plainTextEdit->raise();
        pushButton->raise();
        pushButton_2->raise();
        plainTextEdit_2->raise();
        pushButton_3->raise();
        pushButton_4->raise();
        pushButton_5->raise();
        label_5->raise();
        progressBar->raise();
        comboBox->raise();

        retranslateUi(Dialog);

        QMetaObject::connectSlotsByName(Dialog);
    } // setupUi

    void retranslateUi(QDialog *Dialog)
    {
        Dialog->setWindowTitle(QCoreApplication::translate("Dialog", "Dialog", nullptr));
        label->setText(QCoreApplication::translate("Dialog", "\346\234\215\345\212\241\345\231\250\347\233\221\345\220\254\345\234\260\345\235\200", nullptr));
        label_2->setText(QCoreApplication::translate("Dialog", "\346\234\215\345\212\241\345\231\250\347\233\221\345\220\254\347\253\257\345\217\243", nullptr));
        pushButton->setText(QCoreApplication::translate("Dialog", "\345\220\257\345\212\250\347\233\221\345\220\254", nullptr));
        pushButton_2->setText(QCoreApplication::translate("Dialog", "\345\201\234\346\255\242\347\233\221\345\220\254", nullptr));
        pushButton_3->setText(QCoreApplication::translate("Dialog", "\346\270\205\347\251\272\346\266\210\346\201\257", nullptr));
        pushButton_4->setText(QCoreApplication::translate("Dialog", "\345\217\221\351\200\201\346\266\210\346\201\257", nullptr));
        pushButton_5->setText(QCoreApplication::translate("Dialog", "\351\200\200\345\207\272\347\263\273\347\273\237", nullptr));
        label_5->setText(QCoreApplication::translate("Dialog", "\346\216\245\345\217\227\346\226\207\344\273\266\350\277\233\345\272\246", nullptr));
        groupBox->setTitle(QCoreApplication::translate("Dialog", "GroupBox", nullptr));
        groupBox_2->setTitle(QCoreApplication::translate("Dialog", "\346\266\210\346\201\257\345\210\227\350\241\250", nullptr));
        groupBox_3->setTitle(QCoreApplication::translate("Dialog", "\345\217\221\351\200\201\346\266\210\346\201\257\346\241\206", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Dialog: public Ui_Dialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DIALOG_H
