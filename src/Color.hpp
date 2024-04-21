#ifndef COLOR_HPP__
#define COLOR_HPP__

#include <iostream>
#include "image_ppm.h"

class Color{
	public:
		OCTET r,g,b;
		double h,s,l;

        // CONSTRUCTOR

        Color(){}

		Color(int r, int g, int b)
		{
			this->r = r;
			this->g = g;
			this->b = b;
            this->RGB_to_HSL();
		}

		Color(double r, double g, double b)
		{
			this->r = r;
			this->g = g;
			this->b = b;
            this->RGB_to_HSL();
		}

        Color(OCTET r, OCTET g, OCTET b){
            this->r = r;
            this->g = g;
            this->b = b;
            this->RGB_to_HSL();
        }

        // METHODS
        void RGB_to_HSL(){
            double R = this->r / 255.0;
            double G = this->g / 255.0;
            double B = this->b / 255.0;
            double maxVal = std::max(R, std::max(G, B));
            double minVal = std::min(std::min(R, G), B);

            // Lightness  : The "brightness relative to the brightness of a similarly illuminated white".
            this->l = (maxVal+minVal)/2.0;

            // Saturation : The "colorfulness of a stimulus relative to its own brightness".
            // Hue :
            // The "attribute of a visual sensation according to which an area appears to be similar to one of the perceived colors:
            //     red, yellow, green, and blue, or to a combination of two of them"
            if(maxVal == minVal){
                this->s = 0;
                this->h = 0;
            }
            else {
                this->s = (this->l<0.5) ? ((maxVal-minVal)/(maxVal+minVal)):((maxVal-minVal)/(2.0-maxVal-minVal));
                if(maxVal == R){
                    this->h=(G-B)/(maxVal-minVal)+((G<B)?6.0:0.0);
                }
                else if(maxVal == G){
                    this->h = 2.0 + (B-R) / (maxVal - minVal);
                }
                else{
                    this->h = 4.0 + (R-G) / (maxVal - minVal);
                }
                this->h/= 6.0;
            }

        };

        void HSL_to_RGB(){
            double X, C;
            double R,G,B,m;
            double H = this->h;
            double S = this->s;
            double L = this->l;

            C=(1-fabs(2 * L - 1)) * S;
            H = H * 360/60.0;
            X=C*(1-fabs(fmod(H ,2.0)-1)); //fmod=% sur double

            if(H >= 0&&H <1) {R = C; G = X; B = 0;}
            if(H >= 1&&H <2) {R = X; G = C; B = 0;}
            if(H >= 2&&H <3) {R = 0; G = C; B = X;}
            if(H >= 3&&H <4) {R = 0; G = X; B = C;}
            if(H >= 4&&H <5) {R = X; G = 0; B = C;}
            if(H >= 5&&H <6) {R = C; G = 0; B = X;}
            m = L - C / 2;

            this->r = (R + m) > 1 ? 255 : (R + m) * 255.0;
            this->g = (G + m) > 1 ? 255 : (G + m) * 255.0;
            this->b = (B + m) > 1 ? 255 : (B + m) * 255.0;
        };

        // COMPARATOR

        Color& operator = (Color &c){
            r = c.r;
            g = c.g;
            b = c.b;
            return *this;
        }
        Color& operator = (const Color &c){
            r = c.r;
            g = c.g;
            b = c.b;
            return *this;
        }

        Color& operator + (Color &c){
            r = r + c.r;
            g = g + c.g;
            b = b + c.b;
            return *this;
        }

        Color& operator / (int i)
        {
            r /= i;
            g /= i;
            b /= i;
            return *this;
        }

        bool operator == (const Color &c)
        {
            if( r == c.r &&
                g == c.g &&
                b == c.b )
                return true;
            return false;
        }

		float dist(Color c)
		{
			return sqrt(pow(r - c.r,2) + pow(g - c.g,2) + pow(b - c.b,2));
		}

        std::string toString()
        {
            return std::to_string(r) + " " + std::to_string(g) + " " + std::to_string(b);
        }
};

class Color_float{

public:
    float r,g,b;

    Color_float(float r, float g, float b)
    {
        this->r = r;
        this->g = g;
        this->b = b;
    }

    Color_float(){
        r = 0.f;
        g = 0.f;
        b = 0.f;
    }

    Color_float& operator = (Color_float &c){
        r = c.r;
        g = c.g;
        b = c.b;
        return *this;
    }
    Color_float& operator = (Color &c){
        r = c.r;
        g = c.g;
        b = c.b;
        return *this;
    }

    Color_float& operator + (Color_float &c){
        r = r + c.r;
        g = g + c.g;
        b = b + c.b;
        return *this;
    }
    Color_float& operator + (Color &c){
        r = r + c.r;
        g = g + c.g;
        b = b + c.b;
        return *this;
    }

    Color_float& operator / (int i)
    {
        r /= static_cast<float>(i);
        g /= static_cast<float>(i);
        b /= static_cast<float>(i);
        return *this;
    }

    Color convertToInt() const{
        Color c((int)r,(int)g,(int)b);
        return c;
    }

    float dist(Color_float c)
    {
        return sqrt(pow(r - c.r,2) + pow(g - c.g,2) + pow(b - c.b,2));
    }
    float dist(Color c)
    {
        return sqrt(pow(r - c.r,2) + pow(g - c.g,2) + pow(b - c.b,2));
    }

    std::string toString()
    {
        return std::to_string(r) + " " + std::to_string(g) + " " + std::to_string(b);
    }
};

#endif