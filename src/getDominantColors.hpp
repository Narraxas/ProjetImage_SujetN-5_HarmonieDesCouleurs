#ifndef GET_DOMINANT_COLOR_H__
#define GET_DOMINANT_COLOR_H__

#include <iostream>
#include <vector>
#include <random>
#include <cmath>
#include <algorithm>
#include <queue>
#include "image_ppm.h"
#include "color.h"

using namespace std;

// Calculate the Euclidean distance between two pixels
float euclidean_distance(const Color& p1, const Color& p2) {
    float dr = p1.r - p2.r;
    float dg = p1.g - p2.g;
    float db = p1.b - p2.b;
    return sqrt(dr*dr + dg*dg + db*db);
}

// Assign each pixel to the closest cluster centroid
void assign_clusters(const vector<Color>& pixels, const vector<Color>& centroids, vector<int>& labels) {
    for (int i = 0; i < pixels.size(); i++) {
        int min_label = -1;
        float min_distance = numeric_limits<float>::max();

        for (int j = 0; j < centroids.size(); j++) {
            float distance = euclidean_distance(pixels[i], centroids[j]);

            if (distance < min_distance) {
                min_label = j;
                min_distance = distance;
            }
        }

        labels[i] = min_label;
    }
}

// Calculate the mean color of each cluster
void update_centroids(const vector<Color>& pixels, const vector<int>& labels, vector<Color>& centroids) {
    vector<int> counts(centroids.size(), 0);
    vector<int> r_sums(centroids.size(), 0);
    vector<int> g_sums(centroids.size(), 0);
    vector<int> b_sums(centroids.size(), 0);

    for (int i = 0; i < pixels.size(); i++) {
        int label = labels[i];
        counts[label]++;
        r_sums[label] += pixels[i].r;
        g_sums[label] += pixels[i].g;
        b_sums[label] += pixels[i].b;
    }

    for (int j = 0; j < centroids.size(); j++) {
        if (counts[j] == 0) {
            continue;
        }

        centroids[j].r = static_cast<OCTET>(r_sums[j] / counts[j]);
        centroids[j].g = static_cast<OCTET>(g_sums[j] / counts[j]);
        centroids[j].b = static_cast<OCTET>(b_sums[j] / counts[j]);
    }
}

// Run k-means algorithm
void kmeans(const vector<Color>& pixels, vector<Color>& centroids, int k, int max_iter) {
    vector<int> labels(pixels.size(), -1);

    // Randomly initialize cluster centroids
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<int> dist(0, pixels.size()-1);
    for (int i = 0; i < k; i++) {
        centroids.push_back(pixels[dist(gen)]);
    }

    // Run k-means iterations
    for (int i = 0; i < max_iter; i++) {
        assign_clusters(pixels, centroids, labels);
        update_centroids(pixels, labels, centroids);
    }
}

// colors using number_of_dominant_colors-means algorithm
vector<Color> get_dominant_colors(const vector<Color>& pixels, int number_of_dominant_colors, int nH, int nW) {
    std::vector<Color> ImgKmean;
    OCTET * ImgOut;
    int nTaille3 = (nH * nW) * 3;
    allocation_tableau(ImgOut, OCTET, nTaille3);

    vector<Color> centroids;
    kmeans(pixels, centroids, number_of_dominant_colors, 30);
    // Run k-means algorithm
    // Count the number of pixels in each cluster
    vector<int> counts(centroids.size(), 0);
    for (int i = 0; i < pixels.size(); i++) {
        int label = -1;
        float min_distance = numeric_limits<float>::max();
        for (int j = 0; j < centroids.size(); j++) {
            float distance = euclidean_distance(pixels[i], centroids[j]);
            if (distance < min_distance) {
                label = j;
                min_distance = distance;
            }
        }
        ImgKmean.emplace_back(centroids[label]);
        counts[label]++;
    }

    // Sort the clusters by the number of pixels in each cluster
    vector<pair<int, int>> cluster_counts;
    for (int i = 0; i < centroids.size(); i++) {
        cluster_counts.push_back(make_pair(counts[i], i));
    }
    sort(cluster_counts.begin(), cluster_counts.end(), greater<pair<int, int>>());

    // Get the most dominant colors
    vector<Color> dominant_colors;
    for (int i = 0; i < min(number_of_dominant_colors, static_cast<int>(centroids.size())); i++) {
        dominant_colors.push_back(centroids[cluster_counts[i].second]);
    }

    for (int z=0; z < nTaille3; z+=3)
    {
        ImgOut[z] = ImgKmean[z/3].r;
        ImgOut[z+1] = ImgKmean[z/3].g;
        ImgOut[z+2] = ImgKmean[z/3].b;
    }
    ecrire_image_ppm((char *)"out/Image_Kmean.ppm", ImgOut, nH, nW);

    return dominant_colors;
}

void createPaletteImage(OCTET* &PaletteImg, std::vector<Color> &palette, int nTaille3, int &nW, int &nH)
{
    int tailleImg = nW*nH;
    int tailleImg3 = tailleImg*3;
    int paletteSize = palette.size();
    int numCols = std::ceil(std::sqrt(paletteSize)); // Nombre de colonnes dans l'image de la palette
    int numRows = (paletteSize + numCols - 1) / numCols; // Nombre de lignes

    int cW = nW / numCols;
    int cH = nH / numRows;
    allocation_tableau(PaletteImg, OCTET, tailleImg3);

    // std::cout << cW << "x" << cH << std::endl;
    // Parcourir la palette et placer chaque couleur dans l'image de la palette
    for(int i = 0; i < paletteSize; i++)
    {
        int row = i / numCols; // Ligne actuelle
        int col = i % numCols; // Colonne actuelle

        // Position de départ de la couleur dans l'image
        int startX = col * cW;
        int startY = row * cH;

        // Copier la couleur dans l'image de la palette
        for (int y = 0; y < cH; y++) {
            for (int x = 0; x < cW; x++) {
                int destIndex = ((startY + y) * nW + (startX + x)) * 3;
                PaletteImg[destIndex] = palette[i].r;
                PaletteImg[destIndex + 1] = palette[i].g;
                PaletteImg[destIndex + 2] = palette[i].b;
            }
        }
    }
}

#endif