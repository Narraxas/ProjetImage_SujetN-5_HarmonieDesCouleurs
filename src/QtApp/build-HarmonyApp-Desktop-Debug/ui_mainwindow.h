/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.15.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QPushButton *pushButton;
    QFrame *originalFrame;
    QComboBox *harmonyComboBox;
    QFrame *modifiedFrame;
    QProgressBar *progressBarImgOut;
    QPushButton *colorBtn;
    QPushButton *pushButton_2;
    QCheckBox *isBlurred;
    QCheckBox *isOpenedClosed;
    QSlider *intensiteFlou;
    QLabel *valueIntensiteFlou;
    QSlider *seuilDistance;
    QPushButton *saveBtn;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(799, 556);
        MainWindow->setStyleSheet(QString::fromUtf8("background-color: rgb(253, 205, 166);\n"
"color: rgb(27, 27, 27);"));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        pushButton = new QPushButton(centralwidget);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setGeometry(QRect(30, 420, 151, 24));
        pushButton->setStyleSheet(QString::fromUtf8(" QPushButton {\n"
"     border: 1px solid #2d2e32;\n"
"     border-radius: 6px;\n"
"	color: rgb(255, 255, 255);\n"
"	background-color: rgb(56, 58, 63);\n"
"     min-width: 80px;\n"
" }\n"
" \n"
" QPushButton:pressed {\n"
"     background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,\n"
"                                       stop: 0 #dadbde, stop: 1 #f6f7fa);\n"
" }\n"
" \n"
" QPushButton:flat {\n"
"     border: none; /* no border for a flat push button */\n"
" }\n"
" \n"
" QPushButton:default {\n"
"     border-color: navy; /* make the default button prominent */\n"
" }"));
        originalFrame = new QFrame(centralwidget);
        originalFrame->setObjectName(QString::fromUtf8("originalFrame"));
        originalFrame->setGeometry(QRect(20, 20, 361, 391));
        originalFrame->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));
        originalFrame->setFrameShape(QFrame::StyledPanel);
        originalFrame->setFrameShadow(QFrame::Raised);
        harmonyComboBox = new QComboBox(centralwidget);
        harmonyComboBox->addItem(QString());
        harmonyComboBox->addItem(QString());
        harmonyComboBox->addItem(QString());
        harmonyComboBox->addItem(QString());
        harmonyComboBox->addItem(QString());
        harmonyComboBox->addItem(QString());
        harmonyComboBox->addItem(QString());
        harmonyComboBox->addItem(QString());
        harmonyComboBox->addItem(QString());
        harmonyComboBox->addItem(QString());
        harmonyComboBox->addItem(QString());
        harmonyComboBox->addItem(QString());
        harmonyComboBox->addItem(QString());
        harmonyComboBox->setObjectName(QString::fromUtf8("harmonyComboBox"));
        harmonyComboBox->setGeometry(QRect(30, 450, 251, 24));
        harmonyComboBox->setStyleSheet(QString::fromUtf8(" QComboBox {\n"
"     border: 1px solid gray;\n"
"     border-radius: 3px;\n"
"     padding: 1px 18px 1px 3px;\n"
"     min-width: 6em;\n"
"	background-color: rgb(255, 255, 255);\n"
" }\n"
" \n"
" QComboBox:editable {\n"
"     background: white;\n"
" }\n"
" \n"
" QComboBox:!editable, QComboBox::drop-down:editable {\n"
"	background-color: rgb(255, 255, 255);\n"
" }\n"
" \n"
" /* QComboBox gets the \"on\" state when the popup is open */\n"
" QComboBox:!editable:on, QComboBox::drop-down:editable:on {\n"
"	background-color: rgb(255, 255, 255);\n"
" }\n"
" \n"
" QComboBox:on { /* shift the text when the popup opens */\n"
"     padding-top: 3px;\n"
"     padding-left: 4px;\n"
"	background-color: rgb(255, 255, 255);\n"
" }\n"
" \n"
" QComboBox::drop-down {\n"
"     subcontrol-origin: padding;\n"
"     subcontrol-position: top right;\n"
"     width: 15px;\n"
"	background-color: rgb(255, 255, 255);\n"
" \n"
"     border-left-width: 1px;\n"
"     border-left-color: darkgray;\n"
"     border-left-style: solid; /* just a "
                        "single line */\n"
"     border-top-right-radius: 3px; /* same radius as the QComboBox */\n"
"     border-bottom-right-radius: 3px;\n"
" }\n"
" "));
        modifiedFrame = new QFrame(centralwidget);
        modifiedFrame->setObjectName(QString::fromUtf8("modifiedFrame"));
        modifiedFrame->setGeometry(QRect(420, 20, 361, 391));
        modifiedFrame->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));
        modifiedFrame->setFrameShape(QFrame::StyledPanel);
        modifiedFrame->setFrameShadow(QFrame::Raised);
        progressBarImgOut = new QProgressBar(modifiedFrame);
        progressBarImgOut->setObjectName(QString::fromUtf8("progressBarImgOut"));
        progressBarImgOut->setGeometry(QRect(10, 360, 341, 23));
        progressBarImgOut->setStyleSheet(QString::fromUtf8("QProgressBar {\n"
"    border: 2px solid grey;\n"
"    border-radius: 5px;\n"
"    text-align: center;\n"
"}\n"
"\n"
"QProgressBar::chunk {\n"
"    background-color: #05B8CC;\n"
"    width: 20px;\n"
"}"));
        progressBarImgOut->setValue(24);
        colorBtn = new QPushButton(centralwidget);
        colorBtn->setObjectName(QString::fromUtf8("colorBtn"));
        colorBtn->setGeometry(QRect(190, 420, 171, 24));
        colorBtn->setStyleSheet(QString::fromUtf8(" QPushButton {\n"
"     border: 1px solid #2d2e32;\n"
"     border-radius: 6px;\n"
"	color: rgb(255, 255, 255);\n"
"	background-color: rgb(56, 58, 63);\n"
"     min-width: 80px;\n"
" }\n"
" \n"
" QPushButton:pressed {\n"
"     background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,\n"
"                                       stop: 0 #dadbde, stop: 1 #f6f7fa);\n"
" }\n"
" \n"
" QPushButton:flat {\n"
"     border: none; /* no border for a flat push button */\n"
" }\n"
" \n"
" QPushButton:default {\n"
"     border-color: navy; /* make the default button prominent */\n"
" }"));
        pushButton_2 = new QPushButton(centralwidget);
        pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));
        pushButton_2->setGeometry(QRect(30, 490, 341, 51));
        pushButton_2->setStyleSheet(QString::fromUtf8(" QPushButton {\n"
"     border: 2px solid #2d2e32;\n"
"     border-radius: 10px;\n"
"	color: rgb(255, 255, 255);\n"
"	background-color: rgb(56, 58, 63);\n"
"     min-width: 80px;\n"
" }\n"
" \n"
" QPushButton:pressed {\n"
"     background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,\n"
"                                       stop: 0 #dadbde, stop: 1 #f6f7fa);\n"
" }\n"
" \n"
" QPushButton:flat {\n"
"     border: none; /* no border for a flat push button */\n"
" }\n"
" \n"
" QPushButton:default {\n"
"     border-color: navy; /* make the default button prominent */\n"
" }"));
        isBlurred = new QCheckBox(centralwidget);
        isBlurred->setObjectName(QString::fromUtf8("isBlurred"));
        isBlurred->setGeometry(QRect(430, 420, 181, 23));
        isBlurred->setStyleSheet(QString::fromUtf8(" QCheckBox {\n"
"     spacing: 5px;\n"
" }\n"
" \n"
" QCheckBox::indicator {\n"
"     width: 13px;\n"
"     height: 13px;\n"
" }\n"
" "));
        isOpenedClosed = new QCheckBox(centralwidget);
        isOpenedClosed->setObjectName(QString::fromUtf8("isOpenedClosed"));
        isOpenedClosed->setGeometry(QRect(430, 460, 181, 23));
        isOpenedClosed->setStyleSheet(QString::fromUtf8(" QCheckBox {\n"
"     spacing: 5px;\n"
" }\n"
" \n"
" QCheckBox::indicator {\n"
"     width: 13px;\n"
"     height: 13px;\n"
" }\n"
" "));
        intensiteFlou = new QSlider(centralwidget);
        intensiteFlou->setObjectName(QString::fromUtf8("intensiteFlou"));
        intensiteFlou->setGeometry(QRect(440, 440, 160, 16));
        intensiteFlou->setMinimumSize(QSize(160, 0));
        intensiteFlou->setOrientation(Qt::Horizontal);
        valueIntensiteFlou = new QLabel(centralwidget);
        valueIntensiteFlou->setObjectName(QString::fromUtf8("valueIntensiteFlou"));
        valueIntensiteFlou->setGeometry(QRect(610, 440, 101, 17));
        seuilDistance = new QSlider(centralwidget);
        seuilDistance->setObjectName(QString::fromUtf8("seuilDistance"));
        seuilDistance->setGeometry(QRect(440, 480, 160, 16));
        seuilDistance->setOrientation(Qt::Horizontal);
        saveBtn = new QPushButton(centralwidget);
        saveBtn->setObjectName(QString::fromUtf8("saveBtn"));
        saveBtn->setGeometry(QRect(630, 480, 141, 61));
        saveBtn->setStyleSheet(QString::fromUtf8(" QPushButton {\n"
"     border: 2px solid #2d2e32;\n"
"     border-radius: 10px;\n"
"	color: rgb(255, 255, 255);\n"
"	background-color: rgb(56, 58, 63);\n"
"     min-width: 80px;\n"
" }\n"
" \n"
" QPushButton:pressed {\n"
"     background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,\n"
"                                       stop: 0 #dadbde, stop: 1 #f6f7fa);\n"
" }\n"
" \n"
" QPushButton:flat {\n"
"     border: none; /* no border for a flat push button */\n"
" }\n"
" \n"
" QPushButton:default {\n"
"     border-color: navy; /* make the default button prominent */\n"
" }"));
        MainWindow->setCentralWidget(centralwidget);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "HarmonyApp", nullptr));
        pushButton->setText(QCoreApplication::translate("MainWindow", "Open file", nullptr));
        harmonyComboBox->setItemText(0, QCoreApplication::translate("MainWindow", "S\303\251lectionnez une harmonie", nullptr));
        harmonyComboBox->setItemText(1, QCoreApplication::translate("MainWindow", "getDominantColors", nullptr));
        harmonyComboBox->setItemText(2, QCoreApplication::translate("MainWindow", "Monochromatique", nullptr));
        harmonyComboBox->setItemText(3, QCoreApplication::translate("MainWindow", "Analogue", nullptr));
        harmonyComboBox->setItemText(4, QCoreApplication::translate("MainWindow", "Compl\303\251mentaire", nullptr));
        harmonyComboBox->setItemText(5, QCoreApplication::translate("MainWindow", "Triadique", nullptr));
        harmonyComboBox->setItemText(6, QCoreApplication::translate("MainWindow", "Quadratique", nullptr));
        harmonyComboBox->setItemText(7, QCoreApplication::translate("MainWindow", "Compl\303\251mentaireB", nullptr));
        harmonyComboBox->setItemText(8, QCoreApplication::translate("MainWindow", "TriadiqueB", nullptr));
        harmonyComboBox->setItemText(9, QCoreApplication::translate("MainWindow", "Analogue par distance", nullptr));
        harmonyComboBox->setItemText(10, QCoreApplication::translate("MainWindow", "Compl\303\251mentaire par distance", nullptr));
        harmonyComboBox->setItemText(11, QCoreApplication::translate("MainWindow", "Triadique par distance", nullptr));
        harmonyComboBox->setItemText(12, QCoreApplication::translate("MainWindow", "Quadratique par distance", nullptr));

        colorBtn->setText(QCoreApplication::translate("MainWindow", "Choose a color", nullptr));
        pushButton_2->setText(QCoreApplication::translate("MainWindow", "Generate the image", nullptr));
        isBlurred->setText(QCoreApplication::translate("MainWindow", "Flou Gaussien", nullptr));
        isOpenedClosed->setText(QCoreApplication::translate("MainWindow", "Ouverture/Fermeture", nullptr));
        valueIntensiteFlou->setText(QCoreApplication::translate("MainWindow", "Valeur du flou", nullptr));
        saveBtn->setText(QCoreApplication::translate("MainWindow", "Save", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
