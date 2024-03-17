#include <limits.h>
#include <stdio.h>
#include "image_ppm.h"
#include <stdlib.h>
#include <time.h>
#include <cmath>
#include <iostream>
#include "harmonie.hpp"

void tabCouleur(OCTET *ImgIn,OCTET *ImgOutConv, int *tabK,int nbK, int nTaille){
  OCTET *ImgOut,*ImgOutMoy;
    int nTaille3=nTaille*3;
  allocation_tableau(ImgOut, OCTET, nTaille3);
  allocation_tableau(ImgOutMoy, OCTET, nTaille3);
  srand(time(NULL)); 
  for(int i=0; i<nbK*3;i+=3){
    
    int v=rand()%nTaille;
    for(int j=0;j<i;j+=3){
      if(abs(tabK[j]-(int)ImgIn[v*3])<8&&
      abs(tabK[j+1]-(int)ImgIn[v*3+1])<8&&
      abs(tabK[j+2]-(int)ImgIn[v*3+2])<8){
        v=rand()%nTaille;j=0;std::cout<<"couleur trop proche "<<i<<std::endl;
      }
    }
    tabK[i]=(int)ImgIn[v*3];
    tabK[i+1]=(int)ImgIn[v*3+1];
    tabK[i+2]=(int)ImgIn[v*3+2];
  }
  int tabKbis[nbK*3];
//  for(int i=0;i<nbK*3;i+=3){
//    std::cout<<tabK[i]<<" "<<tabK[i+1]<<" "<<tabK[i+2]<<std::endl;
//  }
  int nbOcc[nbK*3];
  int tabKmoy[nbK*3];
  bool not_converge=true;
  int max_passage=400;
  int passage=0;
  std::cout<<"in "<<std::endl;
  while(not_converge&&passage<max_passage){
    passage++;
    for(int i=0; i<nbK*3;i+=3){
      tabKmoy[i]=0;
      tabKmoy[i+1]=0;
      tabKmoy[i+2]=0;
    }
    for(int i=0; i<nbK*3;i+=1){
      nbOcc[i]=0;
    }
    for (int i=0; i < nTaille3; i+=3)
      {
        int dist=INT_MAX;
        int tab_i=INT_MAX;
        for(int j=0;j<nbK*3;j+=3){
          int dist_temp=sqrt(
            (tabK[j  ]-(int)ImgIn[i  ])*(tabK[j  ]-(int)ImgIn[i  ])+
            (tabK[j+1]-(int)ImgIn[i+1])*(tabK[j+1]-(int)ImgIn[i+1])+
            (tabK[j+2]-(int)ImgIn[i+2])*(tabK[j+2]-(int)ImgIn[i+2]));
          if(dist>dist_temp){dist=dist_temp;tab_i=j;}
        }
        nbOcc[tab_i]++;

        tabKmoy[tab_i]+=(int)ImgIn[i];
        tabKmoy[tab_i+1]+=(int)ImgIn[i+1];
        tabKmoy[tab_i+2]+=(int)ImgIn[i+2];

        if(passage==1){
          ImgOut[i]=(char)tabK[tab_i];
          ImgOut[i+1]=(char)tabK[tab_i+1]; 
          ImgOut[i+2]=(char)tabK[tab_i+2];
          }
      }
    not_converge=false;
    for(int j=0;j<nbK*3;j+=3){
      if(nbOcc[j]==0){nbOcc[j]=1;tabKmoy[j]=tabK[j];tabKmoy[j+1]=tabK[j+1];tabKmoy[j+2]=tabK[j+2];}
      tabKbis[j]=tabKmoy[j]/nbOcc[j];
      tabKbis[j+1]=tabKmoy[j+1]/nbOcc[j];
      tabKbis[j+2]=tabKmoy[j+2]/nbOcc[j];
      //std::cout<<tabKbis[j]<<"  "<<tabKbis[j+1]<<"  "<<tabKbis[j+2]<<"  "<<nbOcc[j]<<"  "<<tabKmoy[j]<<"  "<<tabKmoy[j+1]<<"  "<<tabKmoy[j+2]<<"  "<<std::endl;
      //if(abs(tabKbis[j]-tabK[j])<2||abs(tabKbis[j+1]-tabK[j+1])<2||abs(tabKbis[j+2]-tabK[j+2])<2){not_converge=true;}
      if(tabKbis[j]!=tabK[j]||tabKbis[j+1]!=tabK[j+1]||tabKbis[j+2]!=tabK[j+2]){not_converge=true;}
      tabK[j]=tabKbis[j];tabK[j+1]=tabKbis[j+1];tabK[j+2]=tabKbis[j+2];
    }
    //std::cout<<" tour"<<std::endl;
    if(passage==1){
      for (int i=0; i < nTaille3; i+=3)
      {
        int dist=INT_MAX;
        for(int j=0;j<nbK*3;j+=3){
          int dist_temp=sqrt((tabK[j]-ImgIn[i])*(tabK[j]-ImgIn[i])+(tabK[j+1]-ImgIn[i+1])*(tabK[j+1]-ImgIn[i+1])+(tabK[j+2]-ImgIn[i+2])*(tabK[j+2]-ImgIn[i+2]));
          if(dist>dist_temp){
            dist=dist_temp;
            ImgOutMoy[i]=(char)tabK[j];
            ImgOutMoy[i+1]=(char)tabK[j+1]; 
            ImgOutMoy[i+2]=(char)tabK[j+2];
          }
        }
      }
    }
    if(not_converge==false||passage==max_passage){
      std::cout<<passage<<std::endl;
      for(int i=0; i < nTaille3; i+=3){
        int dist=INT_MAX;
        for(int j=0;j<nbK*3;j+=3){
          int dist_temp=sqrt((tabK[j]-ImgIn[i])*(tabK[j]-ImgIn[i])+(tabK[j+1]-ImgIn[i+1])*(tabK[j+1]-ImgIn[i+1])+(tabK[j+2]-ImgIn[i+2])*(tabK[j+2]-ImgIn[i+2]));
          if(dist>dist_temp){
            dist=dist_temp;
            ImgOutConv[i]=(char)tabK[j];
            ImgOutConv[i+1]=(char)tabK[j+1]; 
            ImgOutConv[i+2]=(char)tabK[j+2];
            }
        }
      }

    }
    
}
}

