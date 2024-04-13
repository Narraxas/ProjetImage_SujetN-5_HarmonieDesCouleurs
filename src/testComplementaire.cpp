#include <limits.h>
#include <stdio.h>
#include "image_ppm.h"
#include <stdlib.h>
#include <time.h>
#include <cmath>
#include <iostream>
#include "harmonie.cpp"

int main(int argc, char* argv[])
{
  char cNomImgLue[250], cNomImgEcrite[250],cNomImgEcriteMoy[250],cNomImgEcriteConv[250];
  int nH, nW, nTaille, nbK;
  double teinte;
  if (argc != 4) 
     {
       printf("Usage: ImageIn.ppm ImageOut.ppm teinte \n"); 
       exit (1) ;
     }
   
   sscanf (argv[1],"%s",cNomImgLue) ;
   sscanf (argv[2],"%s",cNomImgEcrite);
   sscanf (argv[3],"%lf",&teinte);
   nbK=2;

   OCTET *ImgIn, *ImgOut,*ImgSegm;
   
   lire_nb_lignes_colonnes_image_ppm(cNomImgLue, &nH, &nW);
   nTaille = nH * nW;
  
   int nTaille3 = nTaille * 3;
   allocation_tableau(ImgIn, OCTET, nTaille3);
   lire_image_ppm(cNomImgLue, ImgIn, nH * nW);
   allocation_tableau(ImgOut, OCTET, nTaille3);

  std::vector<Color> ImgHSL;
  octetToColorVec(ImgIn, ImgHSL, nTaille3);
  Complementaire(ImgOut, ImgHSL, nH, nW, teinte);

   ecrire_image_ppm(cNomImgEcrite, ImgOut,  nH, nW);
   free(ImgIn);
   return 1;
}