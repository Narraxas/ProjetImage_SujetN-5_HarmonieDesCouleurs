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
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
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
    QCheckBox *isBlurred;
    QCheckBox *isOpenedClosed;
    QSlider *intensiteFlou;
    QLabel *valueIntensiteFlou;
    QSlider *seuilDistance;
    QPushButton *saveBtn;
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
        harmonyComboBox->addItem(QString());
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
        colorBtn = new QPushButton(centralwidget);
        colorBtn->setObjectName("colorBtn");
        colorBtn->setGeometry(QRect(180, 450, 171, 24));
        colorBtn->setStyleSheet(QString::fromUtf8("background-color: rgb(190, 183, 183);"));
        pushButton_2 = new QPushButton(centralwidget);
        pushButton_2->setObjectName("pushButton_2");
        pushButton_2->setGeometry(QRect(20, 490, 331, 51));
        isBlurred = new QCheckBox(centralwidget);
        isBlurred->setObjectName("isBlurred");
        isBlurred->setGeometry(QRect(440, 420, 181, 23));
        isOpenedClosed = new QCheckBox(centralwidget);
        isOpenedClosed->setObjectName("isOpenedClosed");
        isOpenedClosed->setGeometry(QRect(440, 460, 181, 23));
        intensiteFlou = new QSlider(centralwidget);
        intensiteFlou->setObjectName("intensiteFlou");
        intensiteFlou->setGeometry(QRect(440, 440, 160, 16));
        intensiteFlou->setMinimumSize(QSize(160, 0));
        intensiteFlou->setOrientation(Qt::Horizontal);
        valueIntensiteFlou = new QLabel(centralwidget);
        valueIntensiteFlou->setObjectName("valueIntensiteFlou");
        valueIntensiteFlou->setGeometry(QRect(610, 440, 101, 17));
        seuilDistance = new QSlider(centralwidget);
        seuilDistance->setObjectName("seuilDistance");
        seuilDistance->setGeometry(QRect(440, 490, 160, 16));
        seuilDistance->setOrientation(Qt::Horizontal);
        saveBtn = new QPushButton(centralwidget);
        saveBtn->setObjectName("saveBtn");
        saveBtn->setGeometry(QRect(650, 490, 121, 51));
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
        menuHarmony_Application->setTitle(QCoreApplication::translate("MainWindow", "Harmony Application", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
