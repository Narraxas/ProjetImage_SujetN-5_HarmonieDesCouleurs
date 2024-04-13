#include <QFileDialog>
#include <QMessageBox>
#include <QLabel>
#include <QtWidgets>
#include <QProcess>
#include <QColorDialog>

#include <iostream>
#include <vector>

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "image_ppm.h"
#include "Color.hpp"
#include "harmonie.hpp"

QString originalFrameFilePath;
QString modifiedFrameFilePath = "ImgOut.ppm";
QString selectedHarmony;
QColor color(255, 255, 255);

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

int writeMonochromatique(double color, double saturation)
{
    int nH, nW, nTaille;
    OCTET *ImgIn, *ImgOut;
    char cNomImgLue[originalFrameFilePath.length() + 1];
    strcpy(cNomImgLue, originalFrameFilePath.toUtf8().constData());
    char cNomImgEcrite[modifiedFrameFilePath.length() + 1];
    strcpy(cNomImgEcrite, modifiedFrameFilePath.toUtf8().constData());

    lire_nb_lignes_colonnes_image_ppm(cNomImgLue, &nH, &nW);
    nTaille = nH * nW;

    int nTaille3 = nTaille * 3;
    allocation_tableau(ImgIn, OCTET, nTaille3);
    lire_image_ppm(cNomImgLue, ImgIn, nH * nW);
    allocation_tableau(ImgOut, OCTET, nTaille3);

    std::vector<Color> ImgHSL;
    octetToColorVec(ImgIn, ImgHSL, nTaille3);
    std::cout << ImgHSL.size() << std::endl;
    monoChromatique(ImgOut, ImgHSL, nH, nW, color, saturation);

    ecrire_image_ppm(cNomImgEcrite, ImgOut,  nH, nW);
    free(ImgIn);
    return 1;
}

int writeComplementaire(double color, double saturation)
{
    int nH, nW, nTaille;
    OCTET *ImgIn, *ImgOut;
    char cNomImgLue[originalFrameFilePath.length() + 1];
    strcpy(cNomImgLue, originalFrameFilePath.toUtf8().constData());
    char cNomImgEcrite[modifiedFrameFilePath.length() + 1];
    strcpy(cNomImgEcrite, modifiedFrameFilePath.toUtf8().constData());

    lire_nb_lignes_colonnes_image_ppm(cNomImgLue, &nH, &nW);
    nTaille = nH * nW;

    int nTaille3 = nTaille * 3;
    allocation_tableau(ImgIn, OCTET, nTaille3);
    lire_image_ppm(cNomImgLue, ImgIn, nH * nW);
    allocation_tableau(ImgOut, OCTET, nTaille3);

    std::vector<Color> ImgHSL;
    octetToColorVec(ImgIn, ImgHSL, nTaille3);
    std::cout << ImgHSL.size() << std::endl;
    Complementaire(ImgOut, ImgHSL, nH, nW, color,saturation);

    ecrire_image_ppm(cNomImgEcrite, ImgOut,  nH, nW);
    free(ImgIn);
    return 1;
}

int writeComplementaire_B(double color, double saturation)
{
    int nH, nW, nTaille;
    OCTET *ImgIn, *ImgOut;
    char cNomImgLue[originalFrameFilePath.length() + 1];
    strcpy(cNomImgLue, originalFrameFilePath.toUtf8().constData());
    char cNomImgEcrite[modifiedFrameFilePath.length() + 1];
    strcpy(cNomImgEcrite, modifiedFrameFilePath.toUtf8().constData());

    lire_nb_lignes_colonnes_image_ppm(cNomImgLue, &nH, &nW);
    nTaille = nH * nW;

    int nTaille3 = nTaille * 3;
    allocation_tableau(ImgIn, OCTET, nTaille3);
    lire_image_ppm(cNomImgLue, ImgIn, nH * nW);
    allocation_tableau(ImgOut, OCTET, nTaille3);

    std::vector<Color> ImgHSL;
    octetToColorVec(ImgIn, ImgHSL, nTaille3);
    std::cout << ImgHSL.size() << std::endl;
    Complementaire_B(ImgOut, ImgHSL, nH, nW, color);

    ecrire_image_ppm(cNomImgEcrite, ImgOut,  nH, nW);
    free(ImgIn);
    return 1;
}

int writeAnalogue(double color, double saturation)
{
    int nH, nW, nTaille;
    OCTET *ImgIn, *ImgOut;
    char cNomImgLue[originalFrameFilePath.length() + 1];
    strcpy(cNomImgLue, originalFrameFilePath.toUtf8().constData());
    char cNomImgEcrite[modifiedFrameFilePath.length() + 1];
    strcpy(cNomImgEcrite, modifiedFrameFilePath.toUtf8().constData());

    lire_nb_lignes_colonnes_image_ppm(cNomImgLue, &nH, &nW);
    nTaille = nH * nW;

    int nTaille3 = nTaille * 3;
    allocation_tableau(ImgIn, OCTET, nTaille3);
    lire_image_ppm(cNomImgLue, ImgIn, nH * nW);
    allocation_tableau(ImgOut, OCTET, nTaille3);

    int ecart=90;//A MODIFIER

    std::vector<Color> ImgHSL;
    octetToColorVec(ImgIn, ImgHSL, nTaille3);
    std::cout << ImgHSL.size() << std::endl;
    Analogue(ImgOut, ImgHSL, nH, nW, color,ecart,saturation);

    ecrire_image_ppm(cNomImgEcrite, ImgOut,  nH, nW);
    free(ImgIn);
    return 1;
}

int writeTriadique(double color, double saturation)
{
    int nH, nW, nTaille;
    OCTET *ImgIn, *ImgOut;
    char cNomImgLue[originalFrameFilePath.length() + 1];
    strcpy(cNomImgLue, originalFrameFilePath.toUtf8().constData());
    char cNomImgEcrite[modifiedFrameFilePath.length() + 1];
    strcpy(cNomImgEcrite, modifiedFrameFilePath.toUtf8().constData());

    lire_nb_lignes_colonnes_image_ppm(cNomImgLue, &nH, &nW);
    nTaille = nH * nW;

    int nTaille3 = nTaille * 3;
    allocation_tableau(ImgIn, OCTET, nTaille3);
    lire_image_ppm(cNomImgLue, ImgIn, nH * nW);
    allocation_tableau(ImgOut, OCTET, nTaille3);

    int ecart=120;

    std::vector<Color> ImgHSL;
    octetToColorVec(ImgIn, ImgHSL, nTaille3);
    std::cout << ImgHSL.size() << std::endl;
    Triadique(ImgOut, ImgHSL, nH, nW, color,ecart,saturation);

    ecrire_image_ppm(cNomImgEcrite, ImgOut,  nH, nW);
    free(ImgIn);
    return 1;
}

int writeTriadique_B(double color, double saturation)
{
    int nH, nW, nTaille;
    OCTET *ImgIn, *ImgOut;
    char cNomImgLue[originalFrameFilePath.length() + 1];
    strcpy(cNomImgLue, originalFrameFilePath.toUtf8().constData());
    char cNomImgEcrite[modifiedFrameFilePath.length() + 1];
    strcpy(cNomImgEcrite, modifiedFrameFilePath.toUtf8().constData());

    lire_nb_lignes_colonnes_image_ppm(cNomImgLue, &nH, &nW);
    nTaille = nH * nW;

    int nTaille3 = nTaille * 3;
    allocation_tableau(ImgIn, OCTET, nTaille3);
    lire_image_ppm(cNomImgLue, ImgIn, nH * nW);
    allocation_tableau(ImgOut, OCTET, nTaille3);

    int ecart=120;

    std::vector<Color> ImgHSL;
    octetToColorVec(ImgIn, ImgHSL, nTaille3);
    std::cout << ImgHSL.size() << std::endl;
    Triadique_B(ImgOut, ImgHSL, nH, nW, color);

    ecrire_image_ppm(cNomImgEcrite, ImgOut,  nH, nW);
    free(ImgIn);
    return 1;
}

int writeQuadratique(double color, double saturation)
{
    int nH, nW, nTaille;
    OCTET *ImgIn, *ImgOut;
    char cNomImgLue[originalFrameFilePath.length() + 1];
    strcpy(cNomImgLue, originalFrameFilePath.toUtf8().constData());
    char cNomImgEcrite[modifiedFrameFilePath.length() + 1];
    strcpy(cNomImgEcrite, modifiedFrameFilePath.toUtf8().constData());

    lire_nb_lignes_colonnes_image_ppm(cNomImgLue, &nH, &nW);
    nTaille = nH * nW;

    int nTaille3 = nTaille * 3;
    allocation_tableau(ImgIn, OCTET, nTaille3);
    lire_image_ppm(cNomImgLue, ImgIn, nH * nW);
    allocation_tableau(ImgOut, OCTET, nTaille3);

    std::vector<Color> ImgHSL;
    octetToColorVec(ImgIn, ImgHSL, nTaille3);
    std::cout << ImgHSL.size() << std::endl;
    Quadratique(ImgOut, ImgHSL, nH, nW, color,saturation);

    ecrire_image_ppm(cNomImgEcrite, ImgOut,  nH, nW);
    free(ImgIn);
    return 1;
}
int writeAnalogue_B(double color,double saturation){
    int nH, nW, nTaille;
    OCTET *ImgIn, *ImgOut;
    char cNomImgLue[originalFrameFilePath.length() + 1];
    strcpy(cNomImgLue, originalFrameFilePath.toUtf8().constData());
    char cNomImgEcrite[modifiedFrameFilePath.length() + 1];
    strcpy(cNomImgEcrite, modifiedFrameFilePath.toUtf8().constData());

    lire_nb_lignes_colonnes_image_ppm(cNomImgLue, &nH, &nW);
    nTaille = nH * nW;

    int nTaille3 = nTaille * 3;
    allocation_tableau(ImgIn, OCTET, nTaille3);
    lire_image_ppm(cNomImgLue, ImgIn, nH * nW);
    allocation_tableau(ImgOut, OCTET, nTaille3);

    int ecart=90;//A MODIFIER

    std::vector<Color> ImgHSL;
    octetToColorVec(ImgIn, ImgHSL, nTaille3);
    std::cout << ImgHSL.size() << std::endl;
    Analogue_B(ImgOut, ImgHSL, nH, nW, color);

    ecrire_image_ppm(cNomImgEcrite, ImgOut,  nH, nW);
    free(ImgIn);
    return 1;
}

void MainWindow::on_harmonyComboBox_currentTextChanged(const QString &arg1)
{
    selectedHarmony = arg1;
}

void MainWindow::on_colorBtn_clicked()
{
    color = QColorDialog::getColor(color, this, "Choose a color");
    // std::cout << (int)color.hue() << std::endl;

    // Print the hue value
    // qDebug() << "Hue value of the color:" << hue;

}

void MainWindow::on_pushButton_2_clicked()
{
    if (selectedHarmony == "Monochromatique") {
        writeMonochromatique(color.hue()/360.0f, color.saturation()/255.0f);
    }

    if (selectedHarmony == "Complémentaire") {
        writeComplementaire(color.hue()/360.0f, color.saturation()/255.0f);
    }

    if (selectedHarmony == "ComplémentaireB") {
        writeComplementaire_B(color.hue()/360.0f, color.saturation()/255.0f);
    }

    if (selectedHarmony == "Triadique") {
        writeTriadique(color.hue()/360.0f, color.saturation()/255.0f);
    }

    if (selectedHarmony == "TriadiqueB") {
        writeTriadique_B(color.hue()/360.0f, color.saturation()/255.0f);
    }

    if (selectedHarmony == "Quadratique") {
        writeQuadratique(color.hue()/360.0f, color.saturation()/255.0f);
    }
    if (selectedHarmony == "Analogue") {
        writeAnalogue(color.hue()/360.0f, color.saturation()/255.0f);
    }
    if (selectedHarmony == "Analogue_dist") {
        writeAnalogue_B(color.hue()/360.0f, color.saturation()/255.0f);
    }
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

