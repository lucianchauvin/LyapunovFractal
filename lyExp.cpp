#include "EasyBMP.hpp"
#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;
using namespace EasyBMP;

double ly(double a, double b){
    double r   =  a;
    double sum =  0;
    double xn  = .5;

    for(int i = 1; i < 750; i++){
        if (xn != .5){
            sum += log(abs(r*(1-(2*xn))));
        }
        xn = r*xn*(1-xn);
        if (r == a){
            r = b;
        }else{
            r = a;
        }
    }

    return (1/750.0) * sum;
}

RGBColor getC(double n){
    if (n < 0){
        return RGBColor(0, 0, (int)((n*100+255)));
    }
    if (n > 0){
        return RGBColor((int)((n*300*1.225+255)), 0, 0);
    }
    return RGBColor(0, 0, 0);
}


int main(){

    int width  = 1170;
    int height = 2532;

    vector<double> aR = {3.4,4};
    vector<double> bR = {3.3,4};

    vector<double> all;

    Image i(width, height, "sample.bmp", RGBColor (0, 0, 0));
    for(int y = 0; y < height; y++){
        for(int x = 0; x < width; x++){
            double a = ((y/(double) height) * (aR[1] - aR[0])) + aR[0];
            double b = ((x/(double) width)  * (bR[1] - bR[0])) + bR[0];
            double lyExp = ly(a,b);
            // cout << lyExp << endl;
            i.SetPixel(x, y, getC(lyExp)); 
        }
    }
    i.Write();
    return 0;
}