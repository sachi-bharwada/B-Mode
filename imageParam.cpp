#include "imageParam.h"

imageParam::imageParam()
{
    //set variables to given numbers 
    numElement = 128;
    numSample = 3338;
    numScanline = 127;
    elementPosition = genElementPosition();//Call genElementPosition and assign the returned 1D array to elementPosition
    scanlinePosition = genScanlinePosition(numScanline, PITCH, elementPosition);//Call genScanlinePosition and assign the returned 2D array to scanlinePosition
}

imageParam::~imageParam()
{
    deletePositionArray();//release the arrays dynamically allocated for different variables, elementPosition and scanlinePosition
}

// Create an array containing the element location (in x-direction) of the ultrasound transducer
float *imageParam::genElementPosition()
{
    //Allocate a 1D array for elementPosition based on numElement 
    float *elementLocation;
    elementLocation = new float[numElement];

    //use for loop and use the component variable PITCH to deduce the position of each element
    for (int y = 0; y < numElement; ++y){
        elementLocation[y] = ((y - ((float)numElement - 1.0)/2.0)*PITCH);
    }

    return elementLocation;//return elementLocation
}

//float2 created in order to store the lateral position and depth of each pixel
float2 **imageParam::genScanlinePosition(int numScanline, const float PITCH, float* elementLocation)
{
    std::cout<<"Input desired depth: ";//prompt user for depth 
    std::cin>>desiredDepth;//store the input value to data component desiredDepth 
    std::cout<<"Input desired number of pixels: ";//prompt user for number of pixels 
    std::cin>>numPixel;//store the input value to data component numPixel 
    float2 **scanlinePosition;

    //allocate a 2D array of struct float2 type for scanlinePosition based on the 
    //component variables numScanline and numPixel
    scanlinePosition = new float2*[numScanline];
    for(int h = 0; h < numScanline; h++){
        scanlinePosition[h] = new float2[numPixel];
        //use for loop to determine the data compoents lateral position and depth 
        for(int i = 0; i < numPixel; i++){
            scanlinePosition[h][i].x = ((h - (((float)numScanline - 1.0)/2.0))*PITCH);
            scanlinePosition[h][i].y = (i*(desiredDepth/(numPixel - 1)));
        }
    }

    return scanlinePosition;//Return scanlinePosition

}

//
float imageParam::getXPosition(int scanline, int pixel)
{
    //Return the x component of the data stored in scanlinePosition at scanline (first
    //dimension) and pixel (second dimension)
    return scanlinePosition[scanline][pixel].x;
}

float imageParam::getYPosition(int scanline, int pixel)
{
    //Return the y component of the data stored in scanlinePosition at scanline (first
    //dimension) and pixel (second dimension)
    return scanlinePosition[scanline][pixel].y;
}

float imageParam::getElementPosition(int element)
{
    //Return the position of the element stored in elementPosition at element
    return elementPosition[element];
}

int imageParam::getNumElement()
{
    //return numElement
    return numElement;
}

int imageParam::getNumSample()
{
    //return numSample
    return numSample;
}

int imageParam::getNumScanline() 
{
    ////return numScanline
    return numScanline;
}

int imageParam::getNumPixel() 
{
    ////return numPixel
    return numPixel;
}

void imageParam::deletePositionArray()
{
    //Release the memory allocated for elementPosition
    delete elementPosition;
    //Release the memory allocated for scanlinePosition
    for(int y = 0; y < numScanline; y++){
        delete scanlinePosition[y];
    }
}









