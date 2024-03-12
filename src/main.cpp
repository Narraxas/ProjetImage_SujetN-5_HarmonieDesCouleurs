
#include <iostream>
#include <ostream>
#include "getDominantColors.hpp"

int main(int argc, char* argv[]) {
    char cNomImgLue[250], cNomImgEcrite[250];
    int nH, nW, nTaille, number_of_dominant_color;

    int taille_palette = 512;

    if (argc != 3) {
        printf("Usage: ImageIn.ppm nbrCouleursDominantes\n");
        exit(1);
    }

    sscanf(argv[1], "%s", cNomImgLue);
    sscanf(argv[2], "%d", &number_of_dominant_color);

    OCTET *ImgIn, *Palette, *ImgOut;

    lire_nb_lignes_colonnes_image_ppm(cNomImgLue, &nH, &nW);
    nTaille = nH * nW;
    int nTaille3 = nTaille * 3;
    allocation_tableau(ImgIn, OCTET, nTaille3);
    allocation_tableau(Palette, OCTET, (taille_palette * taille_palette) * 3);
    lire_image_ppm(cNomImgLue, ImgIn, nH * nW);

    vector<Color> listeColors;
    for (int i = 0; i < nTaille3; i += 3) {
        Color c = {ImgIn[i], ImgIn[i + 1], ImgIn[i + 2]};
        listeColors.push_back(c);
    }

    vector<Color> dominantColors = get_dominant_colors(listeColors, number_of_dominant_color, nH, nW);

    createPaletteImage(Palette, dominantColors, nTaille3, nW, nH);
    ecrire_image_ppm((char *)"out/Palette.ppm", Palette, nH, nW);

    // for (Color c : dominantColors) {
    //     std::cout << (int)c.r << std::endl;
    // }
}