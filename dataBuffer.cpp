#include "dataBuffer.h"
using namespace std;

//default constructor
dataBuffer::dataBuffer()
{
    //Initialize variables 0
    numElement = 0;
    numSample = 0;
    scanline = 0;
    //Initialize variables to NULL
    dataMatrix = NULL;
    next = NULL;
}

//parameterized constructor
dataBuffer::dataBuffer( std::ifstream *imagFile, std::ifstream *realFile, int inputNumElement, int inputNumSample, int inputScanline)
{
    //variables assigned to the corresponding counterpart of the class component variable 
    numElement = inputNumElement;
    numSample = inputNumSample;

    //inputScanline determines which scanline the current dataBuffer belongs to and is be assigned to scanline
    scanline = inputScanline;
    dataMatrix = createDataMatrix();//allocate a 2D complex array and assign it to dataMatrix
    loadRFData(dataMatrix, imagFile, realFile);//call loadRFData in order to populate dataMatrix
} 

//destructor
dataBuffer::~dataBuffer()
{
    deleteDataMatrix();//call deleteDataMatrix to release the 2D array dynamically allocated for dataMatrix
}


complex **dataBuffer::createDataMatrix()
{
    complex **dataMatrix;
    //Allocate a 2D array based on the component variables numElement and numSample and return that array
    //Iterate throught to 
    dataMatrix = new complex*[numElement];
    for (int h = 0; h < numElement; h++){
        dataMatrix[h] = new complex[numSample];
    }

    return dataMatrix;//return dataMatrix

}

int dataBuffer::loadRFData(complex **RFData, std::ifstream *imagFile, std::ifstream *realFile) 
{ 
    int count = 0;//create counter
    const int MAXIMUM_LINE_SIZE = 20;
    char line [MAXIMUM_LINE_SIZE];//set length of the array to const int MAXIMUM_LINE_SIZE value

    for(int h = 0; h < numElement; h++){
        for(int i = 0; i < numSample; i++){
            count++;//increment counter by 1
            imagFile->getline(line, MAXIMUM_LINE_SIZE);//obtains each line from imaginary file 
            RFData[h][i].imag = atof(line);//converts the char array to float and then it store it in the imaginary part of the RFData array
            realFile->getline(line, MAXIMUM_LINE_SIZE);//obtains each line from real file 
            RFData[h][i].real = atof(line);//converts the char array to float and then it store it in the real part of the RFData array
        }
    }

    return 0;

}

float dataBuffer::getRealRFData(int element,int sample)//takes element and sample as input arguments 
{
    return dataMatrix[element][sample].real;//Returns the real component of the complex data stored in dataMatrix[element][sample]
}
float dataBuffer::getImagRFData(int element,int sample)//takes element and sample as input arguments 
{
    return dataMatrix[element][sample].imag;//Returns the imaginary component of the complex data stored in dataMatrix[element][sample]
}

void dataBuffer::deleteDataMatrix()
{
    //Release the 2D array dataMatrix using a for loop
    for(int y = 0; y < numElement; y++){
        delete dataMatrix[y];
    }
}




