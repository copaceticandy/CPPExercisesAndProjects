#include <iostream>
#include <cmath>
#include "pbPlots.hpp"
#include "supportLib.hpp"

using namespace std;

//d^2theta/dt^2 + g/l*sin(theta) = 0
int main(){
double g = 9.8;
double length = 10;
double initAngle = M_PI*60/180;
double initSpeed = 0;

double t0 = 0;
double tFinal = 20;
double stepSize = 0.01;
int numOfSteps = tFinal/stepSize+1;
double firstAngle = initAngle;
double firstSpeed = initSpeed;
double midAngle = 0.5*firstSpeed*stepSize + initAngle;
double finalAngle = 0.5*firstSpeed*stepSize - 0.5*(g/length)*pow(stepSize,2)*sin(midAngle) + midAngle;
double finalSpeed = (finalAngle-midAngle)/(0.5*stepSize);
double tf = t0 + stepSize;

vector<double> angles;
vector<double> times;
angles.push_back(firstAngle);
angles.push_back(finalAngle);
times.push_back(t0);
times.push_back(tf);

for (int i=0;i<numOfSteps-1;i++){
    tf += stepSize;
    firstAngle = finalAngle;
    firstSpeed = finalSpeed;
    midAngle = 0.5*firstSpeed*stepSize + firstAngle;
    finalAngle = 0.5*firstSpeed*stepSize - 0.5*(g/length)*pow(stepSize,2)*sin(midAngle) + midAngle;
    finalSpeed = (finalAngle-midAngle)/(0.5*stepSize);
    angles.push_back(finalAngle);
    times.push_back(tf);
}

RGBABitmapImageReference *imageRef = CreateRGBABitmapImageReference();

DrawScatterPlot(imageRef,600,400,&times,&angles);

vector<double> *pngData = ConvertToPNG(imageRef->image);
WriteToFile(pngData,"firstPlot.png");
DeleteImage(imageRef->image);


return 0;
 
}