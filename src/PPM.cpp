#ifndef __PPM_CPP
#define __PPM_CPP

#include "Constants.h"
#include "PPM.h"
#include <fstream>

void PPM::open() 
{
    std::ifstream file(this->filename);
    if (!file)
    {
        std::cout << "Problem while opening file " << this->filename << " !" << std::endl; 
        return;
    }

    std::string magicNumber;
    file >> magicNumber;
    if (magicNumber != PPM_FILE_SIGNATURE) {
        file.close();
        std::cout << "File is not PPM !" << std::endl;
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

    std::string red;
    std::string green;
    std::string blue;

    for (unsigned int i = 0; i < width * height; i++) 
    {
        PixelPPM* pixel = new PixelPPM();

        file >> red;
        pixel->red = std::stoi(red);
        file >> green;
        pixel->green = std::stoi(green);
        file >> blue;
        pixel->blue = std::stoi(blue);

        this->pixels.push_back(pixel);
    }

    file.close();
}

#endif