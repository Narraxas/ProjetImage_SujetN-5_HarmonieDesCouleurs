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

void pixel_RGB_to_HSL(double R, double G,double B, double &H, double &S, double &L){
    double maxVal=max(R,max(G,B));
    double minVal=min(min(R,G),B);
    //Lightness  : The "brightness relative to the brightness of a similarly illuminated white".
    L=(maxVal+minVal)/2.0;

    //Saturation : The "colorfulness of a stimulus relative to its own brightness".
    //Hue :
/*        The "attribute of a visual sensation according to which an area appears to be similar to one of the perceived colors:
            red, yellow, green, and blue, or to a combination of two of them"*/
    if(maxVal==minVal){
        S=0;
        H=0;
    }
    else{
        S=(L<0.5)?((maxVal-minVal)/(maxVal+minVal)):((maxVal-minVal)/(2.0-maxVal-minVal));
        if(maxVal==R){
            H=(G-B)/(maxVal-minVal)+((G<B)?6.0:0.0);
        }
        else if(maxVal==G){
            H=2.0+(B-R)/(maxVal-minVal);
        }
        else{
            H=4.0+(R-G)/(maxVal-minVal);
        }
        H/=6;
    }

};

void RGB_to_HSL(OCTET *ImgInRGB,vector<double> &ImgOutHSL, int nH, int nW){
    ImgOutHSL.resize(nH*nW*3);
    for (int i=0;i<nH*nW*3;i+=3){
        double R=ImgInRGB[i]/255.0;//on veut entre [0:1]
        double G=ImgInRGB[i+1]/255.0;
        double B=ImgInRGB[i+2]/255.0;


        double H,S,L;

        pixel_RGB_to_HSL(R,G,B,H,S,L);

        //Entre 0 et 255 mais ca se trouve c est mieux de garder entre 0 et 1 avant de reconvertir vers rgb
        /*
        ImgOutHSL[i]=(H*255.0);
        ImgOutHSL[i+1]=(S*255.0);
        ImgOutHSL[i+2]=(L*255.0);
        */
        //H!=0&&cout<<H<<" "<<S<<" "<<L<<endl;
        ImgOutHSL[i]=H;
        ImgOutHSL[i+1]=S;
        ImgOutHSL[i+2]=L;
    }
};

void pixel_HSL_to_RGB(double H, double S,double L, double &R, double &G, double &B, double &m){
    double X,C;
    C=(1-fabs(2*L-1))*S;
    H=H*360/60.0;
    //X=C*(1-abs(H%2.0-1));
    X=C*(1-fabs(fmod(H,2.0)-1));//fmod=% sur double
    if(H>=0&&H<1){R=C;G=X;B=0;}
    if(H>=1&&H<2){R=X;G=C;B=0;}
    if(H>=2&&H<3){R=0;G=C;B=X;}
    if(H>=3&&H<4){R=0;G=X;B=C;}
    if(H>=4&&H<5){R=X;G=0;B=C;}
    if(H>=5&&H<6){R=C;G=0;B=X;}
    m=L-C/2;
};

void HSL_to_RGB(OCTET *ImgOutRGB,vector<double> ImgInHSL, int nH, int nW){
    double R,G,B,m;
    for (int i=0;i<nH*nW*3;i+=3){
        double H=ImgInHSL[i];
        double S=ImgInHSL[i+1];
        double L=ImgInHSL[i+2];

        pixel_HSL_to_RGB(H,S,L,R,G,B,m);

        ImgOutRGB[i]=R+m>1?255:(R+m)*255.0;
        ImgOutRGB[i+1]=G+m>1?255:(G+m)*255.0;
        ImgOutRGB[i+2]=B+m>1?255:(B+m)*255.0;
    }
};

void ero_dilat_nonBinary(OCTET *ImgIn, OCTET *ImgOut, int nH, int nW, bool color, bool whiteObject, bool erosion){

    //Check si on est sur tu greyscale ou pas
    int facteur = color ? 3 : 1;
    int boucle = color ? 3 : 1;
    //Boucle sur chaque pixel de l'image
    for (int i = 0; i < nH; i++)
    {
        for (int j = 0; j < nW; j++)
        {
            for (int k = 0; k < boucle; k++)
            {
                int M;
                if((whiteObject && erosion) || (!whiteObject && !erosion)){
                    M = 255;
                } else if((whiteObject && !erosion) || (!whiteObject && erosion)){
                    M = 0;
                }
                //boucle sur tout le voisinage de i-1 j -1 a i+1 j+1 en skippant les bords de l'image
                for (int y = max(i - 1, 0); y <= min(i + 1, nH - 1); y++)
                {
                    for (int x = max(j - 1, 0); x <= min(j + 1, nW - 1); x++)
                    {
                        if((whiteObject && erosion) || (!whiteObject && !erosion)){
                            M = min(M, (int)ImgIn[facteur * (y * nW + x) + k]);
                        } else if((whiteObject && !erosion) || (!whiteObject && erosion)){
                            M = max(M, (int)ImgIn[facteur * (y * nW + x) + k]);
                        }

                    }
                }
                ImgOut[facteur * (i * nW + j) + k] = M;
            }
        }
    }
}

// color : 0 = greyScale, 1 = RGB
// whiteObject : 0 = black object, 1 = white object
void erosion_nonBinary(OCTET *ImgIn, OCTET *ImgOut, int nH, int nW, bool color, bool whiteObject)
{
    ero_dilat_nonBinary(ImgIn, ImgOut, nH, nW, color, whiteObject, true);
}

// color : 0 = greyScale, 1 = RGB
// whiteObject : 0 = black object, 1 = white object
void dilation_nonBinary(OCTET *ImgIn, OCTET *ImgOut, int nH, int nW, bool color, bool whiteObject)
{
    ero_dilat_nonBinary(ImgIn, ImgOut, nH, nW, color, whiteObject, false);
}

// color : 0 = greyScale, 1 = RGB
// whiteObject : 0 = black object, 1 = white object
void closing_nonBinary(OCTET *ImgIn, OCTET *ImgOut, int nH, int nW, bool color, bool whiteObject)
{
    OCTET *ImgTemp;
    allocation_tableau(ImgTemp, OCTET, nW * nH * (color ? 3 : 1));

    dilation_nonBinary(ImgIn, ImgTemp, nH, nW, color, whiteObject);
    erosion_nonBinary(ImgTemp, ImgOut, nH, nW, color, whiteObject);

    free(ImgTemp);
}

// color : 0 = greyScale, 1 = RGB
// whiteObject : 0 = black object, 1 = white object
void opening_nonBinary(OCTET *ImgIn, OCTET *ImgOut, int nH, int nW, bool color, bool whiteObject)
{
    OCTET *ImgTemp;
    allocation_tableau(ImgTemp, OCTET, nW * nH * (color ? 3 : 1));

    erosion_nonBinary(ImgIn, ImgTemp, nH, nW, color, whiteObject);
    dilation_nonBinary(ImgTemp, ImgOut, nH, nW, color, whiteObject);

    free(ImgTemp);
}

void copyOctet(OCTET *ImgIn, OCTET *ImgCopy,int taille){
    for(int i=0; i<taille ;i++){
        ImgCopy[i]=ImgIn[i];
    }
}

void monoChromatique(OCTET *ImgOut,vector<Color> ImgIn, int nH, int nW, double color, double saturation){
    Color outColor;

    for (int i=0; i < nH*nW; i++){
        outColor.h = color;
        outColor.s = (saturation+ImgIn[i].s)/2;
        outColor.l = ImgIn[i].l;

        outColor.HSL_to_RGB();

        ImgOut[i*3] = outColor.r;
        ImgOut[i*3+1] = outColor.g;
        ImgOut[i*3+2] = outColor.b;
    }
};

void vector_to_OCTETtab(vector<double> vec, OCTET *octet_tab){
    int n= vec.size();
    for(int i=0;i<n;i++){
        octet_tab[i]=vec[i]*255;
    }
};

void octetToColorVec(OCTET *octetTab, vector<Color> &colorVec, int nTaille3) {
    for (int i = 0; i < nTaille3; i+=3)
        colorVec.push_back(Color(octetTab[i], octetTab[i + 1], octetTab[i + 2]));
};

void colorVecToOctet(OCTET *octetTab, vector<Color> &colorVec, int nTaille) {
    for (int i = 0; i < nTaille; i++){
        octetTab[i*3]=colorVec[i].r;
        octetTab[i*3]=colorVec[i].g;
        octetTab[i*3]=colorVec[i].b;
    }

};
void flouGaussRGB(OCTET* ImgIn, OCTET *ImgOut, int nH, int nW) {
    int hg_r, hh_r, hd_r, mg_r, md_r, bg_r, bm_r, bd_r;
    int hg_g, hh_g, hd_g, mg_g, md_g, bg_g, bm_g, bd_g;
    int hg_b, hh_b, hd_b, mg_b, md_b, bg_b, bm_b, bd_b;

    for (int i = 0; i < nH; i++) {
        for (int j = 0; j < nW; j++) {
            if (i == 0 || i == nH - 1 || j == 0 || j == nW - 1) {
                // Copy pixel values as is for border pixels
                ImgOut[3 * (i * nW + j)] = ImgIn[3 * (i * nW + j)]; // Red channel
                ImgOut[3 * (i * nW + j) + 1] = ImgIn[3 * (i * nW + j) + 1]; // Green channel
                ImgOut[3 * (i * nW + j) + 2] = ImgIn[3 * (i * nW + j) + 2]; // Blue channel
            } else {
                // Red channel
                hg_r = ImgIn[3 * ((i - 1) * nW + (j - 1))];
                hh_r = ImgIn[3 * ((i - 1) * nW + j)];
                hd_r = ImgIn[3 * ((i - 1) * nW + (j + 1))];
                mg_r = ImgIn[3 * (i * nW + (j - 1))];
                md_r = ImgIn[3 * (i * nW + (j + 1))];
                bg_r = ImgIn[3 * ((i + 1) * nW + (j - 1))];
                bm_r = ImgIn[3 * ((i + 1) * nW + j)];
                bd_r = ImgIn[3 * ((i + 1) * nW + (j + 1))];
                ImgOut[3 * (i * nW + j)] = (ImgIn[3 * (i * nW + j)] * 4 + hg_r + hh_r * 2 + hd_r + mg_r * 2 + md_r * 2 + bg_r + bm_r * 2 + bd_r) / 16;

                // Green channel
                hg_g = ImgIn[3 * ((i - 1) * nW + (j - 1)) + 1];
                hh_g = ImgIn[3 * ((i - 1) * nW + j) + 1];
                hd_g = ImgIn[3 * ((i - 1) * nW + (j + 1)) + 1];
                mg_g = ImgIn[3 * (i * nW + (j - 1)) + 1];
                md_g = ImgIn[3 * (i * nW + (j + 1)) + 1];
                bg_g = ImgIn[3 * ((i + 1) * nW + (j - 1)) + 1];
                bm_g = ImgIn[3 * ((i + 1) * nW + j) + 1];
                bd_g = ImgIn[3 * ((i + 1) * nW + (j + 1)) + 1];
                ImgOut[3 * (i * nW + j) + 1] = (ImgIn[3 * (i * nW + j) + 1] * 4 + hg_g + hh_g * 2 + hd_g + mg_g * 2 + md_g * 2 + bg_g + bm_g * 2 + bd_g) / 16;

                // Blue channel
                hg_b = ImgIn[3 * ((i - 1) * nW + (j - 1)) + 2];
                hh_b = ImgIn[3 * ((i - 1) * nW + j) + 2];
                hd_b = ImgIn[3 * ((i - 1) * nW + (j + 1)) + 2];
                mg_b = ImgIn[3 * (i * nW + (j - 1)) + 2];
                md_b = ImgIn[3 * (i * nW + (j + 1)) + 2];
                bg_b = ImgIn[3 * ((i + 1) * nW + (j - 1)) + 2];
                bm_b = ImgIn[3 * ((i + 1) * nW + j) + 2];
                bd_b = ImgIn[3 * ((i + 1) * nW + (j + 1)) + 2];
                ImgOut[3 * (i * nW + j) + 2] = (ImgIn[3 * (i * nW + j) + 2] * 4 + hg_b + hh_b * 2 + hd_b + mg_b * 2 + md_b * 2 + bg_b + bm_b * 2 + bd_b) / 16;
            }
        }
    }
}


vector<Color> Traitement(vector<Color> ImgIn,int nH, int nW){
    std::cout << "preTRAITEMENT : Erosion "<< std::endl;
    OCTET *pretraitementIN;
    allocation_tableau(pretraitementIN, OCTET, nH * nW * 3);
    OCTET *pretraitementOUT;
    allocation_tableau(pretraitementOUT, OCTET, nH * nW * 3);
    colorVecToOctet(pretraitementIN,ImgIn, nH * nW);
    dilation_nonBinary(pretraitementIN,pretraitementOUT,nH,nW,1,0);
        erosion_nonBinary(pretraitementOUT,pretraitementIN,nH,nW,1,0);
    dilation_nonBinary(pretraitementIN,pretraitementOUT,nH,nW,1,0);
        erosion_nonBinary(pretraitementOUT,pretraitementIN,nH,nW,1,0);
    dilation_nonBinary(pretraitementIN,pretraitementOUT,nH,nW,1,0);
        erosion_nonBinary(pretraitementOUT,pretraitementIN,nH,nW,1,0);
    vector<Color> pretraitement;
    octetToColorVec(pretraitementIN,pretraitement,nH*nW*3);

    std::cout<< "pretraitement fini" <<std::endl;
    free(pretraitementIN); free(pretraitementOUT);
    return pretraitement;
};

vector<Color> TraitementFlou(vector<Color> ImgIn,int nH, int nW){
    std::cout << "preTRAITEMENT : FLOU "<< std::endl;
    OCTET *pretraitementIN;
    allocation_tableau(pretraitementIN, OCTET, nH * nW * 3);
    OCTET *pretraitementOUT;
    allocation_tableau(pretraitementOUT, OCTET, nH * nW * 3);
    colorVecToOctet(pretraitementIN,ImgIn, nH * nW);
    flouGaussRGB(pretraitementIN,pretraitementOUT,nH,nW);
    flouGaussRGB(pretraitementOUT,pretraitementIN,nH,nW);
    flouGaussRGB(pretraitementIN,pretraitementOUT,nH,nW);


    vector<Color> pretraitement;
    octetToColorVec(pretraitementOUT,pretraitement,nH*nW*3);
    free(pretraitementIN); free(pretraitementOUT);
    return pretraitement;
};

double couleurComplementaire(double H){
    return fmod((H + 0.5), 1.0);//entre 0 et 1
    //return (int)(H * 360 + 180) % 360; entre 0 et 360
};

void couleurTriadique(double H, double &H1, double &H2, int ecart){//ecart en degre entre 0 et <180
    //entre 0 et 1
    H1 = fmod((H + ecart/360.0), 1.0);
    H2 = fmod((H - ecart/360.0 + 1.0), 1.0);
    //std::cout<<H<<std::endl;
    //std::cout<<H1<<std::endl;
    //std::cout<<H2<<std::endl;
    //entre 0 et 360
    //H1 = (int)(H * 360 + ecart) % 360;
    //H2 = (int)(H * 360 - ecart + 360) % 360;
};

void couleurQuadratique(double H, double &H1, double &H2, double &H3){
    //entre 0 et 1
    H1 = fmod((H + 90/360.0), 1.0);
    H2 = fmod((H + 180/360.0 ), 1.0);
    H3 = fmod((H + 270/360.0 ), 1.0);
    //entre 0 et 360
    //H1 = (int)(H * 360 + ecart) % 360;
    //H2 = (int)(H * 360 - ecart + 360) % 360;
};

void Complementaire(OCTET *ImgOut,vector<Color> ImgIn, int nH, int nW,double teinte, double saturation,bool flou, bool openclose){
    double complementaire=couleurComplementaire(teinte);
    Color outColor;
    OCTET *segmentation;
    vector<Color> preTraitement=ImgIn;
    if(openclose){preTraitement= Traitement(preTraitement,nH,nW);}
    if(flou){preTraitement= TraitementFlou(preTraitement,nH,nW);}
    allocation_tableau(segmentation, OCTET, nH  * nW * 3);
    std::vector<Color> tabK = get_dominant_colors(segmentation, preTraitement, 2, nH, nW);
    for (int i=0; i<nH*nW; i++){
        outColor.h = (segmentation[i*3]==tabK[0].r && segmentation[i*3+1]==tabK[0].g && segmentation[i*3+2]==tabK[0].b) ? teinte : complementaire;
        outColor.s=(saturation+ImgIn[i].s)/2;
        outColor.l=ImgIn[i].l;
        outColor.HSL_to_RGB();

        ImgOut[i*3]= outColor.r;
        ImgOut[i*3+1]= outColor.g;
        ImgOut[i*3+2]= outColor.b;
    }
    free(segmentation);
}

void Triadique(OCTET *ImgOut,vector<Color> ImgIn, int nH, int nW,double teinte,int ecart, double saturation,bool flou, bool openclose){
    double teinte2, teinte3;
    couleurTriadique(teinte,teinte2,teinte3,ecart);
    Color outColor;
    OCTET *segmentation;
    vector<Color> preTraitement=ImgIn;
    if(openclose){preTraitement= Traitement(preTraitement,nH,nW);}
    if(flou){preTraitement= TraitementFlou(preTraitement,nH,nW);}
    allocation_tableau(segmentation, OCTET, nH  * nW * 3);
    std::vector<Color> tabK = get_dominant_colors(segmentation, preTraitement, 3, nH, nW);

    for (int i=0;i<nH*nW;i++){
        if(segmentation[i*3] == tabK[0].r &&segmentation[i*3+1] == tabK[0].g && segmentation[i*3+2] == tabK[0].b ){
            outColor.h =teinte;
        }
        else if(segmentation[i*3] == tabK[1].r && segmentation[i*3+1] == tabK[1].g && segmentation[i*3+2] == tabK[1].b ){
            outColor.h =teinte2;
        }
        else{
            outColor.h =teinte3;
        }
        outColor.s=(saturation+ImgIn[i].s)/2;
        outColor.l=ImgIn[i].l;
        outColor.HSL_to_RGB();

        ImgOut[i*3]= outColor.r;
        ImgOut[i*3+1]= outColor.g;
        ImgOut[i*3+2]= outColor.b;
    }
    free(segmentation);
}

void Quadratique(OCTET *ImgOut,vector<Color> ImgIn, int nH, int nW,double teinte,double saturation,bool flou, bool openclose){
    Color outColor;
    OCTET *segmentation;
    vector<Color> preTraitement=ImgIn;
    if(openclose){preTraitement= Traitement(preTraitement,nH,nW);}
    if(flou){preTraitement= TraitementFlou(preTraitement,nH,nW);}
    allocation_tableau(segmentation, OCTET, nH  * nW * 3);
    std::vector<Color> tabK = get_dominant_colors(segmentation, preTraitement, 4, nH, nW);
    //teinte=tabK[0].h;
    double teinte2, teinte3, teinte4;
    couleurQuadratique(teinte,teinte2,teinte3,teinte4);
    //int u=0;int v=0;int g=0;int d=0;
    for (int i=0;i<nH*nW;i++){
        if(segmentation[i*3] == tabK[0].r &&segmentation[i*3+1] == tabK[0].g && segmentation[i*3+2] == tabK[0].b ){
            outColor.h =teinte;
            //u++;
        }
        else if(segmentation[i*3] == tabK[1].r && segmentation[i*3+1] == tabK[1].g && segmentation[i*3+2] == tabK[1].b ){
            outColor.h =teinte2;
            //v++;
        }
        else if(segmentation[i*3] == tabK[2].r && segmentation[i*3+1] == tabK[2].g && segmentation[i*3+2] == tabK[2].b ){
            outColor.h =teinte3;
            //g++;
        }
        else{
            outColor.h =teinte4;
            //d++;
        }
        outColor.s=(saturation+ImgIn[i].s)/2;
        outColor.l=ImgIn[i].l;
        outColor.HSL_to_RGB();

        ImgOut[i*3]= outColor.r;
        ImgOut[i*3+1]= outColor.g;
        ImgOut[i*3+2]= outColor.b;
    }
    //std::cout<<u<<" "<<v<<" "<<g<<" "<<d<<std::endl;
    //std::cout<<teinte<<" "<<teinte2<<" "<<teinte3<<" "<<teinte4<<std::endl;
    free(segmentation);
}

void Analogue(OCTET *ImgOut,vector<Color> ImgIn, int nH, int nW,double teinte,int ecart, double saturation,bool flou, bool openclose){
    Color outColor;
    OCTET *segmentation;
    vector<Color> preTraitement=ImgIn;
    if(openclose){preTraitement= Traitement(preTraitement,nH,nW);}
    if(flou){preTraitement= TraitementFlou(preTraitement,nH,nW);}
    allocation_tableau(segmentation, OCTET, nH  * nW * 3);
    std::vector<Color> tabK = get_dominant_colors(segmentation, preTraitement, 1, nH, nW);
    Color couleurDominante(tabK[0].r ,tabK[0].g ,tabK[0].b );
    for (int i=0;i<nH*nW;i++){
        double dist = couleurDominante.h*360 - ImgIn[i].h*360 ;
        double couleur=dist > 0 ? teinte*360 + (sqrt(dist*dist)*2*ecart)/360 : teinte*360 - (sqrt(dist*dist)*2*ecart)/360;
        outColor.h =couleur<0? fmod(couleur /360.0 +1,1.0) : fmod(couleur /360.0 ,1.0) ;
        outColor.s=(saturation+ImgIn[i].s)/2;
        outColor.l=ImgIn[i].l;
        outColor.HSL_to_RGB();

        ImgOut[i*3]= outColor.r;
        ImgOut[i*3+1]= outColor.g;
        ImgOut[i*3+2]= outColor.b;
    }
    free(segmentation);
}

void Complementaire_B(OCTET *ImgOut,vector<Color> ImgIn, int nH, int nW,double teinte, double saturation){
    double complementaire=couleurComplementaire(teinte);
    std::cout<<teinte<<" "<<complementaire<<std::endl;
    Color outColor;
    for (int i=0; i<nH*nW; i++){
        outColor.h = std::fabs(ImgIn[i].h-teinte)<0.25 ? teinte : complementaire;
        outColor.s=saturation;
        outColor.l=ImgIn[i].l;
        outColor.HSL_to_RGB();

        ImgOut[i*3]= outColor.r;
        ImgOut[i*3+1]= outColor.g;
        ImgOut[i*3+2]= outColor.b;
    }
}

void Triadique_B(OCTET *ImgOut,vector<Color> ImgIn, int nH, int nW,double teinte,int ecart, double saturation){
    double teinte2, teinte3;
    couleurTriadique(teinte,teinte2,teinte3,ecart);
    Color outColor;


    for (int i=0;i<nH*nW;i++){
        if( std::fabs(ImgIn[i].h-teinte)<0.16){
            outColor.h =teinte;
        }
        else if( std::fabs(ImgIn[i].h-teinte2)<0.16){
            outColor.h =teinte2;
        }
        else{
            outColor.h =teinte3;
        }
        outColor.s=saturation;
        outColor.l=ImgIn[i].l;
        outColor.HSL_to_RGB();

        ImgOut[i*3]= outColor.r;
        ImgOut[i*3+1]= outColor.g;
        ImgOut[i*3+2]= outColor.b;
    }
}
#endif
