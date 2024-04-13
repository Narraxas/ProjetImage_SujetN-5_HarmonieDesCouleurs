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
#include <QtWidgets/QAction>
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
    QMenuBar *menubar;
    QMenu *menuHarmony_Application;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(800, 600);
        MainWindow->setStyleSheet(QString::fromUtf8("background-color: rgb(243, 238, 234);\n"
"border-top-color: rgb(182, 182, 182);"));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        pushButton = new QPushButton(centralwidget);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setGeometry(QRect(20, 420, 151, 24));
        pushButton->setStyleSheet(QString::fromUtf8("background-color: rgb(190, 183, 183);"));
        originalFrame = new QFrame(centralwidget);
        originalFrame->setObjectName(QString::fromUtf8("originalFrame"));
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
        harmonyComboBox->setObjectName(QString::fromUtf8("harmonyComboBox"));
        harmonyComboBox->setGeometry(QRect(180, 420, 171, 24));
        harmonyComboBox->setStyleSheet(QString::fromUtf8("background-color: rgb(190, 183, 183);"));
        modifiedFrame = new QFrame(centralwidget);
        modifiedFrame->setObjectName(QString::fromUtf8("modifiedFrame"));
        modifiedFrame->setGeometry(QRect(440, 20, 331, 391));
        modifiedFrame->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));
        modifiedFrame->setFrameShape(QFrame::StyledPanel);
        modifiedFrame->setFrameShadow(QFrame::Raised);
        colorBtn = new QPushButton(centralwidget);
        colorBtn->setObjectName(QString::fromUtf8("colorBtn"));
        colorBtn->setGeometry(QRect(180, 450, 171, 24));
        colorBtn->setStyleSheet(QString::fromUtf8("background-color: rgb(190, 183, 183);"));
        pushButton_2 = new QPushButton(centralwidget);
        pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));
        pushButton_2->setGeometry(QRect(20, 490, 331, 51));
        isBlurred = new QCheckBox(centralwidget);
        isBlurred->setObjectName(QString::fromUtf8("isBlurred"));
        isBlurred->setGeometry(QRect(440, 420, 181, 23));
        isOpenedClosed = new QCheckBox(centralwidget);
        isOpenedClosed->setObjectName(QString::fromUtf8("isOpenedClosed"));
        isOpenedClosed->setGeometry(QRect(440, 460, 181, 23));
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
        seuilDistance->setGeometry(QRect(440, 500, 160, 16));
        seuilDistance->setOrientation(Qt::Horizontal);
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 800, 22));
        menuHarmony_Application = new QMenu(menubar);
        menuHarmony_Application->setObjectName(QString::fromUtf8("menuHarmony_Application"));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
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
        harmonyComboBox->setItemText(4, QCoreApplication::translate("MainWindow", "Compl\303\251mentaireB", nullptr));
        harmonyComboBox->setItemText(5, QCoreApplication::translate("MainWindow", "Analogue", nullptr));
        harmonyComboBox->setItemText(6, QCoreApplication::translate("MainWindow", "Triadique", nullptr));
        harmonyComboBox->setItemText(7, QCoreApplication::translate("MainWindow", "TriadiqueB", nullptr));
        harmonyComboBox->setItemText(8, QCoreApplication::translate("MainWindow", "Quadratique", nullptr));

        colorBtn->setText(QCoreApplication::translate("MainWindow", "Choose a color", nullptr));
        pushButton_2->setText(QCoreApplication::translate("MainWindow", "Generate the image", nullptr));
        isBlurred->setText(QCoreApplication::translate("MainWindow", "Flou Gaussien", nullptr));
        isOpenedClosed->setText(QCoreApplication::translate("MainWindow", "Ouverture/Fermeture", nullptr));
        valueIntensiteFlou->setText(QCoreApplication::translate("MainWindow", "Valeur du flou", nullptr));
        menuHarmony_Application->setTitle(QCoreApplication::translate("MainWindow", "Harmony Application", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
