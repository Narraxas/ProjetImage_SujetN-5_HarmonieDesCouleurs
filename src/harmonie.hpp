#ifndef HARMONIE_HPP
#define HARMONIE_HPP

#include <vector>
#include "image_ppm.h"

using namespace std;

void RGB_to_HSL(OCTET *ImgInRGB,vector<double> &ImgOutHSL, int nH, int nW);

void pixel_RGB_to_HSL(double R, double G,double B, double &H, double &S, double &L);

void HSL_to_RGB(OCTET *ImgOutRGB,vector<int> &ImgInHSL, int nH, int nW);

void pixel_HSL_to_RGB(double H, double S,double L, double &R, double &G, double &B, double &m);

void monoChromatique(OCTET *ImgOutRGB,vector<double> ImgInHSL, int nH, int nW,double color, double saturation);

void vector_to_OCTETtab(vector<double> vector,OCTET *octet_tab);

#endif