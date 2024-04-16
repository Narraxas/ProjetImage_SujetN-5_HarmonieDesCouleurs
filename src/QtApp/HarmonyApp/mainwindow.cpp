#include <QFileDialog>
#include <QMessageBox>
#include <QLabel>
#include <QtWidgets>
#include <QProcess>
#include <QColorDialog>
#include <QFile>
#include <QtConcurrent/QtConcurrent>

#include <iostream>
#include <vector>

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "image_ppm.h"
#include "Color.hpp"
#include "harmonie.hpp"

QString originalFrameFilePath;
QString saveFrameFilePath;
QString modifiedFrameFilePath = "ImgOut.ppm";
QString selectedHarmony;
QColor color(255, 255, 255);
bool isBlurred = false;
bool isOpenedClosed = false;
bool colorChoosed = false;
unsigned int intensite_flou=1;
float seuil_distance =0.25;
QTimer timer;
QLabel *labelIn;
QLabel *labelOut;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , futureWatcher(this)
{

    ui->setupUi(this);

    ui->intensiteFlou->setMinimum(1);
    ui->intensiteFlou->setMaximum(10);
    ui->intensiteFlou->setSingleStep(1);
    ui->valueIntensiteFlou->setText(QString::number(intensite_flou));
    connect(ui->intensiteFlou, SIGNAL(valueChanged(int)), this, SLOT(updateIntensiteFlou(int)));
    ui->valueIntensiteFlou->setVisible(false);
    ui->isBlurred->setVisible(false);
    ui->isOpenedClosed->setVisible(false);
    ui->intensiteFlou->setVisible(false);

    ui->seuilDistance->setVisible(false);

    ui->seuilDistance->setMinimum(0.0);
    ui->seuilDistance->setMaximum(10.0);
    ui->seuilDistance->setSingleStep(1);
    connect(ui->seuilDistance, SIGNAL(valueChanged(int)), this, SLOT(updateSeuilDistance(int)));

    ui->saveBtn->setVisible(false);

    // Barre de progression
    ui->progressBarImgOut->setRange(0, 100); // Set the range of the progress bar
    ui->progressBarImgOut->setValue(0);      // Set initial value
    ui->progressBarImgOut->setVisible(false);

    timer.setInterval(100); // Set interval to update progress (in milliseconds)

    // Connect the timer's timeout signal to update the progress bar
    QObject::connect(&timer, &QTimer::timeout, [&]() {
        int value = ui->progressBarImgOut->value();
        if (value < 150) {
            ui->progressBarImgOut->setValue(value + 10); // Increase the value of the progress bar
        } else {
            timer.stop(); // Stop the timer when progress reaches 100%
            ui->progressBarImgOut->setVisible(false);
            ui->progressBarImgOut->setValue(0);      // Set initial value
        }
    });
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
        // Récupérer le layout actuel
        QLayout *existingLayout = ui->originalFrame->layout();

        // Si un layout existe déjà, le supprimer et supprimer les widgets enfants
        if (existingLayout) {
            QLayoutItem *child;
            while ((child = existingLayout->takeAt(0)) != nullptr) {
                if (QWidget *widget = child->widget()) {
                    widget->deleteLater();
                }
                delete child;
            }
            delete existingLayout;
        }

        // Charger l'image
        QPixmap originalImage(originalFrameFilePath);
        if (!originalImage.isNull()) {
            delete labelIn;
            // Redimensionner l'image pour s'adapter à la taille de la frame
            originalImage = originalImage.scaled(ui->originalFrame->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation);

            // Créer un QLabel et afficher l'originalImage dans la frame
            labelIn = new QLabel(ui->originalFrame);
            labelIn->setPixmap(originalImage);
            labelIn->setScaledContents(true); // Redimensionner l'image pour s'adapter à la taille du QLabel
            labelIn->show();

            // Créer un layout pour la frame et ajouter le label
            existingLayout = new QVBoxLayout(ui->originalFrame);
            existingLayout->addWidget(labelIn);

            // Centrer le label dans la frame
            existingLayout->setAlignment(Qt::AlignCenter);
            // Ajuster la marge et l'espacement pour centrer le label
            existingLayout->setContentsMargins(0, 0, 0, 0);
            existingLayout->setSpacing(0);

            // Appliquer le layout à la frame
            ui->originalFrame->setLayout(existingLayout);
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
    Complementaire(ImgOut, ImgHSL, nH, nW, color,saturation, isBlurred, isOpenedClosed, intensite_flou);

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
    Complementaire_B(ImgOut, ImgHSL, nH, nW, color,saturation, seuil_distance);

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
    Analogue(ImgOut, ImgHSL, nH, nW, color,ecart,saturation, isBlurred, isOpenedClosed, intensite_flou);

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
    Triadique(ImgOut, ImgHSL, nH, nW, color,ecart,saturation, isBlurred, isOpenedClosed, intensite_flou);

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
    Triadique_B(ImgOut, ImgHSL, nH, nW, color,ecart,saturation,seuil_distance);

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
    Quadratique(ImgOut, ImgHSL, nH, nW, color,saturation, isBlurred, isOpenedClosed, intensite_flou);

    ecrire_image_ppm(cNomImgEcrite, ImgOut,  nH, nW);
    free(ImgIn);
    return 1;
}

//////////////////////////HARMONIE PAR DISTANCE//////////////////////

int writeComplementaire_dist(double color, double saturation)
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
    Complementaire_dist(ImgOut, ImgHSL, nH, nW, color, saturation);

    ecrire_image_ppm(cNomImgEcrite, ImgOut,  nH, nW);
    free(ImgIn);
    return 1;
}

int writeTriadique_dist(double color, double saturation)
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
    Triadique_dist(ImgOut, ImgHSL, nH, nW, color, saturation ,ecart);

    ecrire_image_ppm(cNomImgEcrite, ImgOut,  nH, nW);
    free(ImgIn);
    return 1;
}

int writeQuadratique_dist(double color, double saturation)
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
    Quadratique_dist(ImgOut, ImgHSL, nH, nW, color,saturation);

    ecrire_image_ppm(cNomImgEcrite, ImgOut,  nH, nW);
    free(ImgIn);
    return 1;
}

int writeAnalogue_dist(double color,double saturation){
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
    Analogue_dist(ImgOut, ImgHSL, nH, nW, color, saturation);

    ecrire_image_ppm(cNomImgEcrite, ImgOut,  nH, nW);
    free(ImgIn);
    return 1;
}

////////////////////////////////////////////////////////////////////
void MainWindow::on_harmonyComboBox_currentTextChanged(const QString &arg1)
{
    selectedHarmony = arg1;
    if (selectedHarmony == "Complémentaire" || selectedHarmony == "Triadique"
        || selectedHarmony == "Quadratique" || selectedHarmony == "Analogue") { // Remplacez "Mode 1" et "Mode 2" par vos options de liste déroulante
        // Affichez le slider et le bouton
        ui->valueIntensiteFlou->setVisible(true);
        ui->isBlurred->setVisible(true);
        ui->isOpenedClosed->setVisible(true);
        ui->intensiteFlou->setVisible(true);
    } else {
        // Cachez le slider et le bouton
        ui->valueIntensiteFlou->setVisible(false);
        ui->isBlurred->setVisible(false);
        ui->isOpenedClosed->setVisible(false);
        ui->intensiteFlou->setVisible(false);
    }
    if(selectedHarmony == "ComplémentaireB" || selectedHarmony == "TriadiqueB"){
        ui->seuilDistance->setVisible(true);
    } else {
        ui->seuilDistance->setVisible(false);
    }
}

void MainWindow::on_colorBtn_clicked()
{
    color = QColorDialog::getColor(color, this, "Choose a color");
    colorChoosed = true;
    // std::cout << (int)color.hue() << std::endl;

    // Print the hue value
    // qDebug() << "Hue value of the color:" << hue;

}

void MainWindow::on_pushButton_2_clicked()
{
    if (!originalFrameFilePath.isEmpty()) {
        if (selectedHarmony != "Sélectionnez une harmonie" && !selectedHarmony.isEmpty()) {
            if (colorChoosed) {
                // On lance la progress bar
                timer.start();
                ui->progressBarImgOut->setValue(0);
                ui->progressBarImgOut->setVisible(true);
                ui->progressBarImgOut->raise();
                qApp->processEvents();

                // Exécute le traitement dans un thread séparé
                QFuture<void> future = QtConcurrent::run([=]() {
                    //harmonie segmentation kmean
                    if (selectedHarmony == "Monochromatique") {
                        writeMonochromatique(color.hue()/360.0f, color.saturation()/255.0f);
                    }
                    if (selectedHarmony == "Complémentaire") {
                        writeComplementaire(color.hue()/360.0f, color.saturation()/255.0f);
                    }
                    if (selectedHarmony == "Triadique") {
                        writeTriadique(color.hue()/360.0f, color.saturation()/255.0f);
                    }
                    if (selectedHarmony == "Quadratique") {
                        writeQuadratique(color.hue()/360.0f, color.saturation()/255.0f);
                    }
                    if (selectedHarmony == "Analogue") {
                        writeAnalogue(color.hue()/360.0f, color.saturation()/255.0f);
                    }
                    //////test
                    if (selectedHarmony == "TriadiqueB") {
                        writeTriadique_B(color.hue()/360.0f, color.saturation()/255.0f);
                    }
                    if (selectedHarmony == "ComplémentaireB") {
                        writeComplementaire_B(color.hue()/360.0f, color.saturation()/255.0f);
                    }
                    //////harmonie par distance
                    if (selectedHarmony == "Complémentaire par distance") {
                        writeComplementaire_dist(color.hue()/360.0f, color.saturation()/255.0f);
                    }
                    if (selectedHarmony == "Triadique par distance") {
                        writeTriadique_dist(color.hue()/360.0f, color.saturation()/255.0f);
                    }
                    if (selectedHarmony == "Quadratique par distance") {
                        writeQuadratique_dist(color.hue()/360.0f, color.saturation()/255.0f);
                    }
                    if (selectedHarmony == "Analogue par distance") {
                        writeAnalogue_dist(color.hue()/360.0f, color.saturation()/255.0f);
                    }
                });

                // Connectez le signal de progression au slot de mise à jour de la barre de progression
                connect(&futureWatcher, &QFutureWatcher<void>::progressValueChanged, this, &MainWindow::updateProgressBar);

                // Connectez le signal de fin au slot de traitement terminé
                connect(&futureWatcher, &QFutureWatcher<void>::finished, this, &MainWindow::processingFinished);

                // Démarrez la surveillance de l'avenir
                futureWatcher.setFuture(future);

            } else
                QMessageBox::critical(this, "Erreur", "You must choose a color first", QMessageBox::Ok);
        } else
            QMessageBox::critical(this, "Erreur", "You must choose an harmony first", QMessageBox::Ok);
    } else
        QMessageBox::critical(this, "Erreur", "You must load a file first.", QMessageBox::Ok);
}

void MainWindow::updateProgressBar(int value) {
    ui->progressBarImgOut->setValue(value);
}

void MainWindow::processingFinished() {
    // Affichez le résultat du traitement ou effectuez toute autre opération nécessaire
    // par exemple, afficher l'image modifiée dans un QLabel
    if (ui->modifiedFrame) {
        // Récupérer le layout actuel
        QLayout *existingLayout = ui->modifiedFrame->layout();

        // Si un layout existe déjà, le supprimer et supprimer les widgets enfants
        if (existingLayout) {
            QLayoutItem *child;
            while ((child = existingLayout->takeAt(0)) != nullptr) {
                if (QWidget *widget = child->widget()) {
                    widget->deleteLater();
                }
                delete child;
            }
            delete existingLayout;
        }

        delete labelOut;
        QPixmap modifiedImage(modifiedFrameFilePath);
        if (!modifiedImage.isNull()) {
            modifiedImage = modifiedImage.scaled(ui->modifiedFrame->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation);
            labelOut = new QLabel(ui->modifiedFrame);
            labelOut->setPixmap(modifiedImage);
            labelOut->setScaledContents(true);
            labelOut->show();

            // Créer un layout pour la frame et ajouter le label
            existingLayout = new QVBoxLayout(ui->modifiedFrame);
            existingLayout->addWidget(labelOut);

            // Centrer le label dans la frame
            existingLayout->setAlignment(Qt::AlignCenter);
            // Ajuster la marge et l'espacement pour centrer le label
            existingLayout->setContentsMargins(0, 0, 0, 0);
            existingLayout->setSpacing(0);

            // Appliquer le layout à la frame
            ui->modifiedFrame->setLayout(existingLayout);
        }
    }

    ui->saveBtn->setVisible(true);
    ui->progressBarImgOut->setVisible(false);
    timer.stop();
}

void MainWindow::on_isBlurred_stateChanged(int arg1)
{
    isBlurred=!isBlurred;
    std::cout << "Blurred " << isBlurred << std::endl;
}


void MainWindow::on_isOpenedClosed_stateChanged(int arg1)
{
    isOpenedClosed=!isOpenedClosed;
    std::cout << "OpenClose " << isOpenedClosed << std::endl;
}

void MainWindow::updateIntensiteFlou(int value) {
    intensite_flou = value;
    ui->valueIntensiteFlou->setText(QString::number(value));
    //std::cout << "nombre de floutage : " << intensite_flou << std::endl;
}

void MainWindow::updateSeuilDistance(int value) {
    seuil_distance = value/10.0;
    std::cout << "seuil distance: " << seuil_distance << std::endl;
    if (selectedHarmony == "ComplémentaireB") {
        writeComplementaire_B(color.hue()/360.0f, color.saturation()/255.0f);
    }
    if (selectedHarmony == "TriadiqueB") {
        writeTriadique_B(color.hue()/360.0f, color.saturation()/255.0f);
    }


    // Affichez le résultat du traitement ou effectuez toute autre opération nécessaire
    // par exemple, afficher l'image modifiée dans un QLabel
    if (ui->modifiedFrame) {
        // Récupérer le layout actuel
        QLayout *existingLayout = ui->modifiedFrame->layout();

        // Si un layout existe déjà, le supprimer et supprimer les widgets enfants
        if (existingLayout) {
            QLayoutItem *child;
            while ((child = existingLayout->takeAt(0)) != nullptr) {
                if (QWidget *widget = child->widget()) {
                    widget->deleteLater();
                }
                delete child;
            }
            delete existingLayout;
        }

        delete labelOut;
        QPixmap modifiedImage(modifiedFrameFilePath);
        if (!modifiedImage.isNull()) {
            modifiedImage = modifiedImage.scaled(ui->modifiedFrame->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation);
            labelOut = new QLabel(ui->modifiedFrame);
            labelOut->setPixmap(modifiedImage);
            labelOut->setScaledContents(true);
            labelOut->show();

            // Créer un layout pour la frame et ajouter le label
            existingLayout = new QVBoxLayout(ui->modifiedFrame);
            existingLayout->addWidget(labelOut);

            // Centrer le label dans la frame
            existingLayout->setAlignment(Qt::AlignCenter);
            // Ajuster la marge et l'espacement pour centrer le label
            existingLayout->setContentsMargins(0, 0, 0, 0);
            existingLayout->setSpacing(0);

            // Appliquer le layout à la frame
            ui->modifiedFrame->setLayout(existingLayout);
        }
    }


}



void MainWindow::on_saveBtn_clicked()
{
    QFile sourceFile(modifiedFrameFilePath);
    QString saveFrameFilePath = QFileDialog::getSaveFileName(this, "Select Folder to save the output Image", "../../../out", "Fichiers (*.ppm)");
    if (!saveFrameFilePath.isEmpty()) {
        if (sourceFile.copy(saveFrameFilePath)) {
            qDebug() << "File copied successfully to" << saveFrameFilePath;
        } else {
            qDebug() << "Failed to copy file";
        }
    } else {
        qDebug() << "Annulation de la sauvegarde du fichier.";
    }
}
