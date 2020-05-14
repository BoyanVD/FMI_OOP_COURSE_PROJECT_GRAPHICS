#ifndef __PPM_CPP
#define __PPM_CPP

#include "Constants.h"
#include "PPM.h"
#include <fstream>

void PPM::open() 
{
    // std::ifstream file(this->filename, std::ios::binary);
    // if (!file)
    // {
    //     std::cout << "Problem while opening file " << this->filename << " !" << std::endl; 
    //     return;
    // }

    // std::string magicNumber;
    // file >> magicNumber;
    // if (magicNumber != PPM_FILE_SIGNATURE_TEXT) {
    //     file.close();
    //     std::cout << "File is not PPM !" << std::endl;
    //     return;
    // }

    // std::string widthString;
    // std::string heightString;
    // std::string rangeString;

    // file >> widthString;
    // this->width  = std::stoi(widthString);
    // file >> heightString;
    // this->height = std::stoi(heightString);
    // file >> rangeString;
    // this->colorRange = std::stoi(rangeString);

    // this->pixels.clear();

    // std::string red;
    // std::string green;
    // std::string blue;

    // for (unsigned int i = 0; i < width * height; i++) 
    // {
    //     PixelPPM* pixel = new PixelPPM();

    //     file >> red;
    //     pixel->red = std::stoi(red);
    //     file >> green;
    //     pixel->green = std::stoi(green);
    //     file >> blue;
    //     pixel->blue = std::stoi(blue);

    //     this->pixels.push_back(pixel);
    // }

    // file.close();

    if (this->type == "text" && (!this->openTextType()))
        std::cout << "Cannot open text PPM file !" << std::endl;
    else if (this->type == "binary" && (!this->openBinaryType()))
        std::cout << "Cannot open binary PPM file !" << std::endl;
}

bool PPM::openTextType()
{
    std::ifstream file(this->filename);
    if (!file)
    {
        std::cout << "Problem while opening file " << this->filename << " !" << std::endl; 
        return false;
    }

    std::string magicNumber;
    file >> magicNumber;
    if (magicNumber != PPM_FILE_SIGNATURE_TEXT) {
        file.close();
        std::cout << "File is not PPM !" << std::endl;
        return false;
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
    return true; // Think of better work-around
}

bool PPM::openBinaryType()
{
    std::ifstream file(this->filename, std::ios::binary);
    if (!file)
    {
        std::cout << "Problem while opening file " << this->filename << " !" << std::endl; 
        return false;
    }

    std::string magicNumber;
    file >> magicNumber;
    if (magicNumber != PPM_FILE_SIGNATURE_BINARY) {
        file.close();
        std::cout << "File is not PPM !" << std::endl;
        return false;
    }

    file >> this->width >> this->height >> this->colorRange;
    file.get(); // skip the trailing white space

    size_t size = (this->width) * (this->height) * 3;
    char* pointer = new char[size];
    file.read(pointer, size);
    
    for (int i = 0; i < size; i += 3)
    {
        PixelPPM* pixel = new PixelPPM();

        pixel->red = pointer[i] - '0';
        pixel->green = pointer[i + 1] - '0';
        pixel->blue = pointer[i + 2] - '0';

        this->pixels.push_back(pixel);
    }

    file.close();
    return true;
}

#endif