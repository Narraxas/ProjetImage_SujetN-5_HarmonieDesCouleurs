#ifndef GET_DOMINANT_COLOR_H__
#define GET_DOMINANT_COLOR_H__

#include <iostream>
#include <vector>
#include <random>
#include <cmath>
#include <algorithm>
#include <queue>
#include "image_ppm.h"
#include "k_mean.h"
#include "Color.hpp"

using namespace std;

// colors using number_of_dominant_colors-means algorithm
vector<Color> get_dominant_colors(OCTET *ImgOut, vector<Color>& ImgIn, int number_of_dominant_colors, int nH, int nW) {
    vector<Color> ImgKmean;
    int nTaille3 = (nH * nW) * 3;

    vector<Color> classes = findRandomColors(ImgIn, number_of_dominant_colors, nW, nH);
    // for (Color c : classes) {
    //     cout << c.toString() << std::endl;
    // }
    k_mean(ImgIn, classes, nTaille3, 100);
    // cout << "After Kmean: " << std::endl;

    // for (Color c : classes) {
    //     cout << c.toString() << std::endl;
    // }

    //ecrire_image_ppm((char *)"out/Image_Kmean.ppm", ImgOut, nH, nW);
    for (int i = 0; i < nTaille3; i += 3)
    {
        int iClass = findClass(ImgIn[i/3], classes);
        // std::cout << ImgIn[i/3].toString() << " - Class " << iClass <<std::endl;

        ImgOut[i] = classes[iClass].r;
        ImgOut[i+1] = classes[iClass].g;
        ImgOut[i+2] = classes[iClass].b;
    }
    ecrire_image_ppm((char *)"out/Image_Kmean.ppm", ImgOut, nH, nW);
    return classes;
}

#endif