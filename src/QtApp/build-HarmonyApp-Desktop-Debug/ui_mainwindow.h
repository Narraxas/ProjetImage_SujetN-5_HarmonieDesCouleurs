/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.9.7
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHeaderView>
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
    QPushButton *colorBtn;
    QPushButton *pushButton_2;
    QMenuBar *menubar;
    QMenu *menuHarmony_Application;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(800, 600);
        MainWindow->setStyleSheet(QLatin1String("background-color: rgb(243, 238, 234);\n"
"border-top-color: rgb(182, 182, 182);"));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        pushButton = new QPushButton(centralwidget);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setGeometry(QRect(20, 420, 151, 24));
        pushButton->setStyleSheet(QStringLiteral("background-color: rgb(190, 183, 183);"));
        originalFrame = new QFrame(centralwidget);
        originalFrame->setObjectName(QStringLiteral("originalFrame"));
        originalFrame->setGeometry(QRect(20, 20, 331, 391));
        originalFrame->setStyleSheet(QStringLiteral("background-color: rgb(255, 255, 255);"));
        originalFrame->setFrameShape(QFrame::StyledPanel);
        originalFrame->setFrameShadow(QFrame::Raised);
        harmonyComboBox = new QComboBox(centralwidget);
        harmonyComboBox->setObjectName(QStringLiteral("harmonyComboBox"));
        harmonyComboBox->setGeometry(QRect(180, 420, 171, 24));
        harmonyComboBox->setStyleSheet(QStringLiteral("background-color: rgb(190, 183, 183);"));
        modifiedFrame = new QFrame(centralwidget);
        modifiedFrame->setObjectName(QStringLiteral("modifiedFrame"));
        modifiedFrame->setGeometry(QRect(440, 20, 331, 391));
        modifiedFrame->setStyleSheet(QStringLiteral("background-color: rgb(255, 255, 255);"));
        modifiedFrame->setFrameShape(QFrame::StyledPanel);
        modifiedFrame->setFrameShadow(QFrame::Raised);
        colorBtn = new QPushButton(centralwidget);
        colorBtn->setObjectName(QStringLiteral("colorBtn"));
        colorBtn->setGeometry(QRect(180, 450, 171, 24));
        colorBtn->setStyleSheet(QStringLiteral("background-color: rgb(190, 183, 183);"));
        pushButton_2 = new QPushButton(centralwidget);
        pushButton_2->setObjectName(QStringLiteral("pushButton_2"));
        pushButton_2->setGeometry(QRect(20, 490, 331, 51));
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QStringLiteral("menubar"));
        menubar->setGeometry(QRect(0, 0, 800, 22));
        menuHarmony_Application = new QMenu(menubar);
        menuHarmony_Application->setObjectName(QStringLiteral("menuHarmony_Application"));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QStringLiteral("statusbar"));
        MainWindow->setStatusBar(statusbar);

        menubar->addAction(menuHarmony_Application->menuAction());

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", Q_NULLPTR));
        pushButton->setText(QApplication::translate("MainWindow", "Open file", Q_NULLPTR));
        harmonyComboBox->clear();
        harmonyComboBox->insertItems(0, QStringList()
         << QApplication::translate("MainWindow", "S\303\251lectionnez une harmonie", Q_NULLPTR)
         << QApplication::translate("MainWindow", "getDominantColors", Q_NULLPTR)
         << QApplication::translate("MainWindow", "Monochromatique", Q_NULLPTR)
         << QApplication::translate("MainWindow", "Compl\303\251mentaire", Q_NULLPTR)
         << QApplication::translate("MainWindow", "Compl\303\251mentaireB", Q_NULLPTR)
         << QApplication::translate("MainWindow", "Analogue", Q_NULLPTR)
         << QApplication::translate("MainWindow", "Triadique", Q_NULLPTR)
         << QApplication::translate("MainWindow", "TriadiqueB", Q_NULLPTR)
         << QApplication::translate("MainWindow", "Quadratique", Q_NULLPTR)
        );
        colorBtn->setText(QApplication::translate("MainWindow", "Choose a color", Q_NULLPTR));
        pushButton_2->setText(QApplication::translate("MainWindow", "Generate the image", Q_NULLPTR));
        menuHarmony_Application->setTitle(QApplication::translate("MainWindow", "Harmony Application", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
