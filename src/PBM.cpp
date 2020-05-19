#ifndef __PBM_CPP
#define __PBM_CPP

#include "Constants.h"
#include "PBM.h"
#include <fstream>

void PBM::open() 
{
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

        pixel->isBlack = pointer[i]; // - '0'

        this->pixels.push_back(pixel);
    }

    file.close();
    return true;
}

void PBM::print()
{
    unsigned int size = width * width;

    std::cout << "File size : " << size << std::endl;
    std::cout << "Width : " << width << std::endl;
    std::cout << "Height : " << height << std::endl;

    for (unsigned int j = 0; j < height; ++j) 
    {
        for (unsigned int i = 0; i < width; ++i) 
        {
            PixelPBM* pixel = dynamic_cast<PixelPBM*>(getPixel(i, j));
            std::cout << (int)pixel->isBlack << " " ;
        }
        std::cout << std::endl;
    }
}

void PBM::write()
{
    if (this->type == "text" && (!this->writeText()))
        std::cout << "Cannot write text PBM file !" << std::endl;
    else if (this->type == "binary" && (!this->writeBinary()))
        std::cout << "Cannot write binary PBM file !" << std::endl;
}

bool PBM::writeBinary()
{
    std::ofstream out(this->filename, std::ios::binary);
    if (!out)
    {
        std::cout << "Problem while opening file " << this->filename << " !" << std::endl; 
        return false;
    }

    out << PBM_FILE_SIGNATURE_BINARY << '\n';
    out << this->width << ' ' << this->height << '\n';

    size_t size = (this->width) * (this->height);
    char* pointer = new char[size];
    
    for (int i = 0; i < size; ++i)
    {
        PixelPBM* pixel = dynamic_cast<PixelPBM*>(this->pixels[i]);

        pointer[i] = pixel->isBlack; // + '0'
    }
    out.write(pointer, size);

    out.close();
    return true;
}

bool PBM::writeText()
{
    std::ofstream out(this->filename);
    if(!out)
        return false;
    
    out << PGM_FILE_SIGNATURE_TEXT << '\n' << this->width << ' ' << this->height << '\n';
    if(!out)
        return false;
    
    for (unsigned int j = 0; j < height; ++j) 
    {
        for (unsigned int i = 0; i < width; ++i) 
        {
            PixelPBM* pixel = dynamic_cast<PixelPBM*>(getPixel(i, j));
            out << (int)pixel->isBlack << ' ';
        }
        out  << '\n';
    }

    out.close();
    return true;
}

void PBM::negative()
{
    for (Pixel* pixel : this->pixels)
    {
        PixelPBM* pixelPBM = dynamic_cast<PixelPBM*>(pixel);

        pixelPBM->isBlack = (255 - pixelPBM->isBlack);
    }
}

std::string PBM::getType() const
{
    return "PBM";
}

#endif