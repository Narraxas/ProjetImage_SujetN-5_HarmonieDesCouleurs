#include "harmonie.cpp"
#include <stdio.h>
#include "image_ppm.h"
#include <vector>
#include <cmath>
#include <iostream>

int main(int argc, char* argv[])
{
  char cNomImgLue[250], cNomImgEcrite[250], cNomImgEcrite2[250];
  int nH, nW, nTaille;
  double color,saturation;
  if (argc != 5) 
    {
      printf("Usage: ImageIn.ppm couleur(entre 0. et 1) saturation ImageOutRGB.ppm \n"); 
      exit (1) ;
    }
  
  sscanf (argv[1],"%s",cNomImgLue) ;
  sscanf (argv[2],"%lf",&color);
  sscanf (argv[3],"%lf",&saturation);
  sscanf (argv[4],"%s",cNomImgEcrite2);

  OCTET *ImgIn, *ImgOut, *ImgOut2;
  
  lire_nb_lignes_colonnes_image_ppm(cNomImgLue, &nH, &nW);
  nTaille = nH * nW;
  
  int nTaille3 = nTaille * 3;
  allocation_tableau(ImgIn, OCTET, nTaille3);
  lire_image_ppm(cNomImgLue, ImgIn, nH * nW);
  allocation_tableau(ImgOut, OCTET, nTaille3);


  allocation_tableau(ImgOut2, OCTET, nTaille3);

  std::vector<Color> ImgHSL;
  octetToColorVec(ImgIn, ImgHSL, nTaille3);
  std::cout << ImgHSL.size() << std::endl;
  monoChromatique(ImgOut, ImgHSL, nH, nW, color, saturation);

  // ecrire_image_ppm(cNomImgEcrite, ImgOut2,  nH, nW);
  ecrire_image_ppm(cNomImgEcrite2, ImgOut,  nH, nW);
  free(ImgIn);
  return 1;
}
