
#include "harmonie.hpp"

using namespace std;

//https://en.wikipedia.org/wiki/HSL_and_HSV
//https://gist.github.com/ciembor/1494530

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

void monoChromatique(OCTET *ImgOut,vector<Color> ImgIn, int nH, int nW, double color, double saturation){
    double R,G,B,m;
    Color outColor;

    for (int i=0; i < nH*nW; i++){
        outColor.h = color;
        outColor.s = saturation;
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
}

double couleurComplementaire(double H){
    return fmod((H + 0.5), 1.0);//entre 0 et 1
    //return (int)(H * 360 + 180) % 360; entre 0 et 360
};

void couleurTriadique(double H, double &H1, double &H2, int ecart){//ecart en degre entre 0 et <180
    //entre 0 et 1
    H1 = fmod((H + ecart/360.0), 1.0);
    H2 = fmod((H - ecart/360.0 + 1.0), 1.0);
    //entre 0 et 360
    //H1 = (int)(H * 360 + ecart) % 360;
    //H2 = (int)(H * 360 - ecart + 360) % 360;
};

void couleurQuadratique(double H, double &H1, double &H2, double &H3){
    //entre 0 et 1
    H1 = fmod((H + 90/360.0), 1.0);
    H2 = fmod((H - 90/360.0 + 1.0), 1.0);
    H3 = fmod((H - 180/360.0 + 1.0), 1.0);
    //entre 0 et 360
    //H1 = (int)(H * 360 + ecart) % 360;
    //H2 = (int)(H * 360 - ecart + 360) % 360;
};

void Complementaire(OCTET *ImgOut,vector<Color> ImgIn, int nH, int nW,double teinte){
    double complementaire=couleurComplementaire(teinte);
    double R,G,B,m;
    Color outColor;
    OCTET *segmentation;
    std::vector<Color> tabK = get_dominant_colors(segmentation, ImgIn, 2, nH, nW);

    for (int i=0; i<nH*nW; i++){
        outColor.h = (segmentation[i]==tabK[0].r && segmentation[i+1]==tabK[0].g && segmentation[i+2]==tabK[0].b) ? teinte : complementaire;
        outColor.s=ImgIn[i].s;
        outColor.l=ImgIn[i].l;
        outColor.HSL_to_RGB();

        ImgOut[i*3]= outColor.r;
        ImgOut[i*3+1]= outColor.g;
        ImgOut[i*3+2]= outColor.b;
    }
}

void Triadique(OCTET *ImgOutRGB,vector<double> ImgInHSL, int nH, int nW,double teinte,int ecart, OCTET *segmentation,int* tabK){
    double teinte2, teinte3;    
    couleurTriadique(teinte,teinte2,teinte3,ecart);
    int red= tabK[0];int blue= tabK[1];int green= tabK[2];    
    int red2= tabK[3];int blue2= tabK[4];int green2= tabK[5];    
    double R,G,B,m;
    for (int i=0;i<nH*nW*3;i+=3){
        double S=ImgInHSL[i+1];
        double L=ImgInHSL[i+2];
        if(segmentation[i]==red&&segmentation[i+1]==blue&&segmentation[i+2]==green){

            pixel_HSL_to_RGB(teinte,S,L,R,G,B,m);
            
            ImgOutRGB[i]=R+m>1?255:(R+m)*255.0;
            ImgOutRGB[i+1]=G+m>1?255:(G+m)*255.0;
            ImgOutRGB[i+2]=B+m>1?255:(B+m)*255.0;
        }
        else if(segmentation[i]==red2&&segmentation[i+1]==blue2&&segmentation[i+2]==green2){

            pixel_HSL_to_RGB(teinte2,S,L,R,G,B,m);
            
            ImgOutRGB[i]=R+m>1?255:(R+m)*255.0;
            ImgOutRGB[i+1]=G+m>1?255:(G+m)*255.0;
            ImgOutRGB[i+2]=B+m>1?255:(B+m)*255.0;
        }
        else{
            pixel_HSL_to_RGB(teinte3,S,L,R,G,B,m);
            
            ImgOutRGB[i]=R+m>1?255:(R+m)*255.0;
            ImgOutRGB[i+1]=G+m>1?255:(G+m)*255.0;
            ImgOutRGB[i+2]=B+m>1?255:(B+m)*255.0;
        }
    }
}

