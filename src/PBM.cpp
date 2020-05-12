#ifndef __PBM_CPP
#define __PBM_CPP

#include "Constants.h"
#include "PBM.h"
#include <fstream>

void PBM::open() 
{
    std::ifstream file(this->filename);
    if (!file)
    {
        std::cout << "Problem while opening file " << this->filename << " !" << std::endl; 
        return;
    }

    std::string magicNumber;
    file >> magicNumber;
    if (magicNumber != PBM_FILE_SIGNATURE) {
        file.close();
        std::cout << "File is not PBM !" << std::endl;
        return;
    }

    std::string widthString;
    std::string heightString;

    file >> widthString;
    this->width  = std::stoi(widthString);
    file >> heightString;
    this->height = std::stoi(heightString);
    
    this->pixels.clear();

    std::string isPixelBlack;

    for (unsigned int i = 0; i < width * height; i++) 
    {
        PixelPBM* pixel = new PixelPBM();

        file >> isPixelBlack;
        pixel->isBlack = std::stoi(isPixelBlack);

        this->pixels.push_back(pixel);
    }

    file.close();
}

#endif