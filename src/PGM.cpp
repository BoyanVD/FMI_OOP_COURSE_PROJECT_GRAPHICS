#ifndef __PGM_CPP
#define __PGM_CPP

#include "Constants.h"
#include "PGM.h"
#include <fstream>

void PGM::open() 
{
    std::ifstream file(this->filename);
    if (!file)
    {
        std::cout << "Problem while opening file " << this->filename << " !" << std::endl; 
        return;
    }

    std::string magicNumber;
    file >> magicNumber;
    if (magicNumber != PGM_FILE_SIGNATURE) {
        file.close();
        std::cout << "File is not PGM !" << std::endl;
        return;
    }

    std::string widthString;
    std::string heightString;
    std::string rangeString;

    file >> widthString;
    this->width  = std::stoi(widthString);
    file >> heightString;
    this->height = std::stoi(heightString);
    file >> rangeString;
    this->colorRange = std::stoi(rangeString);
    
    this->pixels.clear();

    std::string grey;

    for (unsigned int i = 0; i < width * height; i++) 
    {
        PixelPGM* pixel = new PixelPGM();
        file >> grey;
        pixel->greyscale = std::stoi(grey);

        this->pixels.push_back(pixel);
    }

    file.close();
}

#endif