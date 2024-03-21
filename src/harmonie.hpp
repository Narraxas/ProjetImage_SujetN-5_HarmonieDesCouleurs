#ifndef HARMONIE_HPP
#define HARMONIE_HPP

#include <vector>
#include <stdio.h>
#include <vector>
#include <cmath>
#include <iostream>
#include "image_ppm.h"
#include "Color.hpp"
#include "getDominantColor.hpp"

using namespace std;

void RGB_to_HSL(OCTET *ImgInRGB,vector<double> &ImgOutHSL, int nH, int nW);

void pixel_RGB_to_HSL(double R, double G,double B, double &H, double &S, double &L);

void HSL_to_RGB(OCTET *ImgOutRGB,vector<double> &ImgInHSL, int nH, int nW);

void pixel_HSL_to_RGB(double H, double S,double L, double &R, double &G, double &B, double &m);

void monoChromatique(OCTET *ImgOut, vector<Color> ImgIn, int nH, int nW, double color, double saturation);

void Complementaire(OCTET *ImgOut,vector<Color> ImgIn, int nH, int nW,double teinte);

void Triadique(OCTET *ImgOutRGB,vector<double> ImgInHSL, int nH, int nW,double teinte,int ecart);

void Analogue(OCTET *ImgOutRGB,vector<double> ImgInHSL, int nH, int nW,double teinte,int ecart, OCTET *segmentation,int* tabK);

void vector_to_OCTETtab(vector<double> vector,OCTET *octet_tab);
void octetToColorVec(OCTET *octetTab, vector<Color> &colorVec, int nTaille3);

double couleurComplementaire(double H);
void couleurTriadique(double H, double &H1, double &H2, int ecart);
void couleurQuadratique(double H, double &H1, double &H2,double &H3);


#endif