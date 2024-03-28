#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QMessageBox>
#include <QLabel>
#include <QtWidgets>
#include <QProcess>

QString originalFrameFilePath;
QString modifiedFrameFilePath;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    originalFrameFilePath = QFileDialog::getOpenFileName(this, "Choose an image to apply harmony on", "../../../in");
    // QMessageBox::information(this, "FilePath of the image", filePath);

    if (ui->originalFrame) {
        // Charger l'image
        QPixmap originalImage(originalFrameFilePath);
        if (!originalImage.isNull()) {
            // Redimensionner l'image pour s'adapter à la taille de la frame
            originalImage = originalImage.scaled(ui->originalFrame->size(), Qt::KeepAspectRatioByExpanding, Qt::SmoothTransformation);

            // Créer un QLabel et afficher l'originalImage dans la frame
            QLabel *label = new QLabel(ui->originalFrame);
            label->setPixmap(originalImage);
            label->setScaledContents(true); // Redimensionner l'image pour s'adapter à la taille du QLabel
            label->show();
        }
    }
}


void MainWindow::on_harmonyComboBox_currentTextChanged(const QString &arg1)
{
    // QMessageBox::information(this, "Selected harmony", arg1);

    // Spécifier le chemin de l'exécutable à appeler
    // if (arg1 == "monochromatique")
    // QString outputName = "../../../out/Palette.ppm";
    // QString command = arg1 + ".sh " + originalFrameFilePath + " 4";

    // Vérifier si le fichier existe
    /*if (!QFile::exists(command)) {
        qDebug() << "Le fichier n'existe pas à l'emplacement spécifié.";
        return;
    }*/

    // Exécuter la commande
    // int result = system(command.toUtf8().constData());

    // // Vérifier le résultat
    // if (result == -1) {
    //     qDebug() << "Failed to execute the command.";
    //     return;
    // } else {
    //     qDebug() << "Command executed successfully.";
    // }

    // QMessageBox::information(this, "Process fnished sucessfully", "OK");
    modifiedFrameFilePath = QFileDialog::getOpenFileName(this, "Choose an image to display", "../../../in");
    // QMessageBox::information(this, "FilePath of the image", filePath);

    if (ui->modifiedFrame) {
        // Charger l'image
        QPixmap modifiedImage(modifiedFrameFilePath);
        if (!modifiedImage.isNull()) {
            // Redimensionner l'image pour s'adapter à la taille de la frame
            modifiedImage = modifiedImage.scaled(ui->modifiedFrame->size(), Qt::KeepAspectRatioByExpanding, Qt::SmoothTransformation);

            // Créer un QLabel et afficher l'modifiedImage dans la frame
            QLabel *label = new QLabel(ui->modifiedFrame);
            label->setPixmap(modifiedImage);
            label->setScaledContents(true); // Redimensionner l'image pour s'adapter à la taille du QLabel
            label->show();
        }
    }
}

