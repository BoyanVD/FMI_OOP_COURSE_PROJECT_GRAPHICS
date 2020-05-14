#ifndef __PBM_CPP
#define __PBM_CPP

#include "Constants.h"
#include "PBM.h"
#include <fstream>

void PBM::open() 
{
    // std::ifstream file(this->filename);
    // if (!file)
    // {
    //     std::cout << "Problem while opening file " << this->filename << " !" << std::endl; 
    //     return;
    // }

    // std::string magicNumber;
    // file >> magicNumber;
    // if (magicNumber != PBM_FILE_SIGNATURE_TEXT) {
    //     file.close();
    //     std::cout << "File is not PBM !" << std::endl;
    //     return;
    // }

    // std::string widthString;
    // std::string heightString;

    // file >> widthString;
    // this->width  = std::stoi(widthString);
    // file >> heightString;
    // this->height = std::stoi(heightString);
    
    // this->pixels.clear();

    // std::string isPixelBlack;

    // for (unsigned int i = 0; i < width * height; i++) 
    // {
    //     PixelPBM* pixel = new PixelPBM();

    //     file >> isPixelBlack;
    //     pixel->isBlack = std::stoi(isPixelBlack);

    //     this->pixels.push_back(pixel);
    // }

    // file.close();

    if (this->type == "text" && (!this->openTextType()))
        std::cout << "Cannot open text PBM file !" << std::endl;
    else if (this->type == "binary" && (!this->openBinaryType()))
        std::cout << "Cannot open binary PBM file !" << std::endl;
}

bool PBM::openTextType()
{
    std::ifstream file(this->filename);
    if (!file)
    {
        std::cout << "Problem while opening file " << this->filename << " !" << std::endl; 
        return false;
    }

    std::string magicNumber;
    file >> magicNumber;
    
    if (magicNumber != PBM_FILE_SIGNATURE_TEXT) {
        file.close();
        std::cout << "File is not PBM !" << std::endl;
        return false;
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
    return true; // Think of better work-around
}

// @TODO - think of either fixing the format expected or reading them dynamically
//-------------------------------------------------------------------------------
//-------------------------------------------------------------------------------
//-------------------------------------------------------------------------------
//-------------------------------------------------------------------------------
//-------------------------------------------------------------------------------
bool PBM::openBinaryType()
{
    std::ifstream file(this->filename, std::ios::binary);
    if (!file)
    {
        std::cout << "Problem while opening file " << this->filename << " !" << std::endl; 
        return false;
    }

    std::string magicNumber;
    file >> magicNumber;

    if (magicNumber != PBM_FILE_SIGNATURE_BINARY) {
        file.close();
        std::cout << "File is not PBM !" << std::endl;

        return false;
    }

    file >> this->width;
    file >> this->height;

    file.get(); // skip the trailing white space

    size_t size = (this->width) * (this->height);
    char* pointer = new char[size];
    file.read(pointer, size);
    
    for (int i = 0; i < size; ++i)
    {
        PixelPBM* pixel = new PixelPBM();

        pixel->isBlack = pointer[i];

        this->pixels.push_back(pixel);
    }

    file.close();
    return true;
}

#endif