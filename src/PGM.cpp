#ifndef __PGM_CPP
#define __PGM_CPP

#include "Constants.h"
#include "PGM.h"
#include <fstream>

void PGM::open() 
{
    // std::ifstream file(this->filename);
    // if (!file)
    // {
    //     std::cout << "Problem while opening file " << this->filename << " !" << std::endl; 
    //     return;
    // }

    // std::string magicNumber;
    // file >> magicNumber;
    // if (magicNumber != PGM_FILE_SIGNATURE_TEXT) {
    //     file.close();
    //     std::cout << "File is not PGM !" << std::endl;
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

    // std::string grey;

    // for (unsigned int i = 0; i < width * height; i++) 
    // {
    //     PixelPGM* pixel = new PixelPGM();
    //     file >> grey;
    //     pixel->greyscale = std::stoi(grey);

    //     this->pixels.push_back(pixel);
    // }

    // file.close();

    if (this->type == "text" && (!this->openTextType()))
        std::cout << "Cannot open text PGM file !" << std::endl;
    else if (this->type == "binary" && (!this->openBinaryType()))
        std::cout << "Cannot open binary PGM file !" << std::endl;
}

bool PGM::openTextType()
{
    std::ifstream file(this->filename);
    if (!file)
    {
        std::cout << "Problem while opening file " << this->filename << " !" << std::endl; 
        return false;
    }

    std::string magicNumber;
    file >> magicNumber;
    if (magicNumber != PGM_FILE_SIGNATURE_TEXT) {
        file.close();
        std::cout << "File is not PGM !" << std::endl;
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

    std::string grey;

    for (unsigned int i = 0; i < width * height; ++i) 
    {
        PixelPGM* pixel = new PixelPGM();
        file >> grey;
        pixel->greyscale = std::stoi(grey);

        this->pixels.push_back(pixel);
    }

    file.close();
    return true; // Think of better work-around
}

bool PGM::openBinaryType()
{
    std::ifstream file(this->filename, std::ios::binary);
    if (!file)
    {
        std::cout << "Problem while opening file " << this->filename << " !" << std::endl; 
        return false;
    }

    std::string magicNumber;
    file >> magicNumber;
    if (magicNumber != PGM_FILE_SIGNATURE_BINARY) {
        file.close();
        std::cout << "File is not PGM !" << std::endl;
        return false;
    }

    file >> this->width >> this->height >> this->colorRange;
    file.get(); // skip the trailing white space

    size_t size = (this->width) * (this->height);
    char* pointer = new char[size];
    file.read(pointer, size);
    
    for (int i = 0; i < size; ++i)
    {
        PixelPGM* pixel = new PixelPGM();

        pixel->greyscale = pointer[i] - '0';

        this->pixels.push_back(pixel);
    }

    file.close();
    return true;
}

#endif