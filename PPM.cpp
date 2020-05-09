#ifndef __PPM_CPP
#define __PPM_CPP

#include "Constants.h"
#include "PPM.h"
#include <fstream>

void PPM::open(const std::string& path) 
{
    std::ifstream file(path);
    if (!file)
    {
        std::cout << "Problem while opening file " << path << " !" << std::endl; 
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
    this->pixelsTable.clear();

    RGB pixel;
    std::string red;
    std::string green;
    std::string blue;

    for (unsigned int i = 0; i < width * height; i++) 
    {
        file >> red;
        pixel.red = std::stoi(red);
        file >> green;
        pixel.green = std::stoi(green);
        file >> blue;
        pixel.blue = std::stoi(blue);

        this->pixelsTable.push_back(pixel);
    }

    file.close();
}

#endif