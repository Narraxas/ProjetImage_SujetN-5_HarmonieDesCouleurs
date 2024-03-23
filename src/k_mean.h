#ifndef K_MEAN_H_
#define K_MEAN_H_

#include <iostream>
#include <vector>
#include <algorithm>
#include <limits>
#include <random>
#include "Color.hpp"


int findClass(Color &c, std::vector<Color> classes) {
    int cIdx = 0;
    float minDist = std::numeric_limits<float>::max();

    for (int i = 0; i < classes.size(); i++) {
        float tmpDist = c.dist(classes[i]);
        if (tmpDist < minDist) {
            minDist = tmpDist;
            cIdx = i;
        }
    }

    return cIdx;
}

void setDistantColor(Color &c1, Color &c2, OCTET* ImgIn, int n) {
    float maxDist = 0;
    int accuracy = 100;

    for (int i = 0; i < n; i += accuracy * 3)
    {
        Color tmpC1(ImgIn[i], ImgIn[i+1], ImgIn[i+2]);
        for (int j = 0; j < n; j += accuracy * 3)
        {
            Color tmpC2(ImgIn[j], ImgIn[j+1], ImgIn[j+2]);
            float dist = tmpC1.dist(tmpC2);

            if(dist > maxDist)
            {
                maxDist = dist;
                c1 = tmpC1;
                c2 = tmpC2;
            }
        }
    }
}

std::vector<Color> findRandomColors(const std::vector<Color> &ImgIn, int number, int width, int height)
{
    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> distWidth(0,width);
    std::uniform_int_distribution<std::mt19937::result_type> distHeight(0,height);

    std::vector<Color> tab;

    for(int i = 0; i < number; i++)
    {
        int randWidth = distWidth(rng);
        int randHeight = distHeight(rng);

        int index = randWidth + width*randHeight;

        if (std::find(tab.begin(), tab.end(), ImgIn[index]) != tab.end()) // tab contient déjà c
            i--;
        else
            tab.push_back(ImgIn[index]);
    }
    return tab;
}

void k_mean(std::vector<Color> &ImgIn, std::vector<Color> &classes, int nTaille3, int repMax){
    int convergence = 0;
    int rep = 0;
    while (convergence == 0 && rep < repMax) {
        std::cout << "repMax: " << (repMax == 1 ? 0 : (rep * 100 / repMax + 1)) << "/100" << std::endl;
        std::vector<Color_float> avgColorPerClasses = std::vector<Color_float>(classes.size());
        std::vector<int> countForAvgClasses = std::vector<int>(classes.size());

        for (int i = 0; i < nTaille3; i += 3) {
            float distanceMin = std::numeric_limits<float>::max();
            int index;

            for(int colorIndex = 0; colorIndex < classes.size(); colorIndex++) {
                float d = ImgIn[i/3].dist(classes[colorIndex]);
                if(d < distanceMin) {
                    // std::cout << d << " < " << distanceMin << std::endl;
                    distanceMin = d;
                    index = colorIndex;
                }
            }
            avgColorPerClasses[index] = avgColorPerClasses[index] + ImgIn[i/3];
            countForAvgClasses[index]++;
        }
        convergence = classes.size();
        // std::cout << "\nrep: " << rep << std::endl;
        // for (Color c : classes)
        //     std::cout << c.toString() << std::endl;
        // std::cout << std::endl;
        for(int i = 0; i < avgColorPerClasses.size(); i++)
        {
            Color tmpAvg = (avgColorPerClasses[i] / countForAvgClasses[i]).convertToInt();
            // std::cout << "Moyenne cluster: "<<  tmpAvg.toString() << std::endl;
            if (!(classes[i] == tmpAvg)) {
                classes[i] = tmpAvg;
                convergence--;
            }
        }
        rep++;
    }
}

float psnr(OCTET* ImgIn, OCTET* ImgOut, int maxSignal, int nTaille3)
{
    float eqm; // erreur quadratique
    for(int i = 0; i < nTaille3; i++)
    {
        eqm += pow(ImgIn[i] - ImgOut[i] , 2);
    }
    eqm /= nTaille3;

    float a = 10 * log10(static_cast<float>(pow(maxSignal,2)) / eqm );
    return a;
}

std::vector<Color> createColorPalette(OCTET* Img, int nTaille3)
{
    std::vector<Color> tab;
    bool isIn;

    for(int i = 0; i < nTaille3; i = i +3)
    {
        Color c(Img[i], Img[i+1],Img[i+2]);

        isIn = false;

        for(Color &c2 : tab){
            if(c == c2){
                isIn = true;
            }
        }

        if(!isIn){
            tab.push_back(c);
        }
    }
    return tab;
}

// void createPaletteImage(OCTET* &PaletteImg, std::vector<Color> &palette, int nTaille3, int &nW, int &nH)
// {
//     int tailleImg_x = ceil(sqrt(palette.size()));
//     int tailleImg = tailleImg_x*tailleImg_x;
//     int tailleImg3 = tailleImg*3;
//     nW = tailleImg_x;
//     nH = tailleImg_x;

//     allocation_tableau(PaletteImg, OCTET, tailleImg3);

//     int index = 0;
//     for(int i = 0; i < palette.size(); i++)
//     {
//         PaletteImg[index] = palette[i].r;
//         PaletteImg[index+1] = palette[i].g;
//         PaletteImg[index+2] = palette[i].b;
//         index = index + 3;
//     }
// }

void convertColorToIndexedGrey(OCTET* ImgIn, OCTET* ImgOut, std::vector<Color> &palette, int nTaille3)
{
    for(int i = 0; i < nTaille3; i = i +3)
    {
        Color c(ImgIn[i], ImgIn[i+1],ImgIn[i+2]);
        int index = 0;

        for(int ind = 0; ind < palette.size(); ind++)
        {
            if(palette[ind] == c){
                index = ind;
                break;
            }
        }

        ImgOut[i/3] = index;
        //std::cout << index << std::endl;
    }
}

#endif //K_MEAN_H_