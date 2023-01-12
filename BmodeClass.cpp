#include "BmodeClass.h"

BmodeClass::BmodeClass()
{
    imparams = NULL;//initialize imparams to NULL
    RFData = NULL;//initialize RFData to NULL
    next = NULL;//initialize next to NULL
    line = 0;//set line to 0
}

BmodeClass::BmodeClass(imageParam *params,dataBuffer *data,int numline)
{
    imparams = params;//Set imparams to params
    RFData = data;//Set RFData to data
    line = numline;//Set line to numline
    scanline = createScanline(imparams->getNumPixel());//Invoke createScanline to allocate memory for scanline
    beamform();//Invoke beamform to beamform the scanline
}

BmodeClass::~BmodeClass()
{
    deleteScanline();//release the arrays dynamically allocated for scanline
}

float *BmodeClass::createScanline(int numPixel)
{
    //allocate a 1D float array of size numPixel as mem
    float *mem;
    mem = new float[numPixel];
    return mem;//return mem
}

void BmodeClass::beamform()
{
    //set variables to 0
    float totalTime = 0;
    int s = 0;
    float pImag = 0;
    float pReal = 0;

    for(int h = 0; h < imparams->getNumPixel(); h++){
        pImag = 0;//intiialize to 0
        pReal = 0;//intiialize to 0
        for(int i = 0; i < imparams->getNumElement(); ++i){
            //determine totaltime using equation given
            totalTime = ((imparams->getYPosition(line,h) + sqrt(pow(imparams->getYPosition(line,h),2) 
            + pow(imparams->getXPosition(line, h) - imparams->getElementPosition(i),2)))/imparams->SOS);
            //determine s using equation given 
            s = floor(totalTime*imparams->FS);
            if(s < imparams->getNumSample()){
                pImag += RFData->getImagRFData(i,s);//icrement part imaginary
                pReal += RFData->getRealRFData(i,s);//icrement part real
            }
            scanline[h] = (sqrt(pow(pReal,2) + pow(pImag,2)));//calculate echo magnitude 
        }
    }
}

void BmodeClass::getScanline(float *data)
{
    //Copy the content inside scanline to data element-by-element
    for(int h = 0; h < imparams->getNumPixel(); h++){
        data[h] = scanline[h];
    }
}

void BmodeClass::deleteScanline()
{
    delete scanline;//Release the memory allocated for scanline
}