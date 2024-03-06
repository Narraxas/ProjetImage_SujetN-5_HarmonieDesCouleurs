#include <stdio.h>
#include "image_ppm.h"
#include <vector>

using namespace std;

void RGB_to_HSL(OCTET *ImgInRGB,vector<int> &ImgOutHSL, int nH, int nW);

void HSL_to_RGB(OCTET *ImgOutRGB,vector<int> &ImgInHSL, int nH, int nW);