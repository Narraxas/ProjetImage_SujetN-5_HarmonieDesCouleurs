#include <limits.h>
#include <stdio.h>
#include "image_ppm.h"
#include <stdlib.h>
#include <time.h>
#include <cmath>
#include <iostream>
#include "harmonie.cpp"
#include "segmentationKmean.cpp"


int main(int argc, char* argv[])
{
  char cNomImgLue[250], cNomImgEcrite[250],cNomImgEcriteMoy[250],cNomImgEcriteConv[250];
  int nH, nW, nTaille, nbK, angle;
  double teinte;
  if (argc != 5) 
     {
       printf("Usage: ImageIn.ppm ImageOut.ppm teinte \n"); 
       exit (1) ;
     }
   
   sscanf (argv[1],"%s",cNomImgLue) ;
   sscanf (argv[2],"%s",cNomImgEcrite);
   sscanf (argv[3],"%lf",&teinte);
   sscanf (argv[4],"%d",&angle);
   nbK=3;

   OCTET *ImgIn, *ImgOut,*ImgSegm;
   
   lire_nb_lignes_colonnes_image_ppm(cNomImgLue, &nH, &nW);
   nTaille = nH * nW;
  
   int nTaille3 = nTaille * 3;
   allocation_tableau(ImgIn, OCTET, nTaille3);
   lire_image_ppm(cNomImgLue, ImgIn, nH * nW);
   allocation_tableau(ImgOut, OCTET, nTaille3);
   allocation_tableau(ImgSegm, OCTET, nTaille3);


    int tabK[nbK*3];
  tabCouleur(ImgIn, ImgSegm,tabK,nbK,nTaille);
//  for(int i=0;i<nbK*3;i+=3){
//    std::cout<<tabK[i]<<" "<<tabK[i+1]<<" "<<tabK[i+2]<<std::endl;
//  }
    vector<double> ImgHSL;
    ImgHSL.resize(nTaille3);
    double H,S,L;
    pixel_RGB_to_HSL(tabK[0],tabK[1],tabK[2],H,S,L);
    RGB_to_HSL(ImgIn, ImgHSL, nH, nW);
   
    Analogue(ImgOut, ImgHSL, nH, nW, teinte, angle, ImgSegm,tabK);
   ecrire_image_ppm(cNomImgEcrite, ImgOut,  nH, nW);
   free(ImgIn);
   return 1;
}
