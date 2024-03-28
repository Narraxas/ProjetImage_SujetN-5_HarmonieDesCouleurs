/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.6.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
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
    QMenuBar *menubar;
    QMenu *menuHarmony_Application;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(800, 600);
        MainWindow->setStyleSheet(QString::fromUtf8("background-color: rgb(243, 238, 234);\n"
"border-top-color: rgb(182, 182, 182);"));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        pushButton = new QPushButton(centralwidget);
        pushButton->setObjectName("pushButton");
        pushButton->setGeometry(QRect(20, 420, 151, 24));
        pushButton->setStyleSheet(QString::fromUtf8("background-color: rgb(190, 183, 183);"));
        originalFrame = new QFrame(centralwidget);
        originalFrame->setObjectName("originalFrame");
        originalFrame->setGeometry(QRect(20, 20, 331, 391));
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
        harmonyComboBox->setObjectName("harmonyComboBox");
        harmonyComboBox->setGeometry(QRect(180, 420, 171, 24));
        harmonyComboBox->setStyleSheet(QString::fromUtf8("background-color: rgb(190, 183, 183);"));
        modifiedFrame = new QFrame(centralwidget);
        modifiedFrame->setObjectName("modifiedFrame");
        modifiedFrame->setGeometry(QRect(440, 20, 331, 391));
        modifiedFrame->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));
        modifiedFrame->setFrameShape(QFrame::StyledPanel);
        modifiedFrame->setFrameShadow(QFrame::Raised);
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 800, 21));
        menuHarmony_Application = new QMenu(menubar);
        menuHarmony_Application->setObjectName("menuHarmony_Application");
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        menubar->addAction(menuHarmony_Application->menuAction());

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        pushButton->setText(QCoreApplication::translate("MainWindow", "Open file", nullptr));
        harmonyComboBox->setItemText(0, QCoreApplication::translate("MainWindow", "S\303\251lectionnez une harmonie", nullptr));
        harmonyComboBox->setItemText(1, QCoreApplication::translate("MainWindow", "getDominantColors", nullptr));
        harmonyComboBox->setItemText(2, QCoreApplication::translate("MainWindow", "Monochromatique", nullptr));
        harmonyComboBox->setItemText(3, QCoreApplication::translate("MainWindow", "Compl\303\251mentaire", nullptr));
        harmonyComboBox->setItemText(4, QCoreApplication::translate("MainWindow", "Triadique", nullptr));
        harmonyComboBox->setItemText(5, QCoreApplication::translate("MainWindow", "Quadratique", nullptr));

        menuHarmony_Application->setTitle(QCoreApplication::translate("MainWindow", "Harmony Application", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
