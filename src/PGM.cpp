#ifndef __PGM_CPP
#define __PGM_CPP

#include "Constants.h"
#include "PGM.h"
#include <fstream>

void PGM::open() 
{
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
    return true;
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

void PGM::print()
{
    unsigned int size = width * width;

    std::cout << "File size : " << size << std::endl;
    std::cout << "Width : " << width << std::endl;
    std::cout << "Height : " << height << std::endl;
    std::cout << "Color range : " << colorRange << std::endl;

    for (unsigned int j = 0; j < height; ++j) 
    {
        for (unsigned int i = 0; i < width; ++i) 
        {
            PixelPGM* pixel = dynamic_cast<PixelPGM*>(getPixel(i, j));
            std::cout << (int)pixel->greyscale << " ";
        }
        std::cout << std::endl;
    }
}

void PGM::write()
{
    if (this->type == "text" && (!this->writeText()))
        std::cout << "Cannot write text PGM file !" << std::endl;
    else if (this->type == "binary" && (!this->writeBinary()))
        std::cout << "Cannot write binary PGM file !" << std::endl;
}

bool PGM::writeBinary()
{
    std::ofstream out(this->filename, std::ios::binary);
    if (!out)
    {
        std::cout << "Problem while opening file " << this->filename << " !" << std::endl; 
        return false;
    }

    out << PGM_FILE_SIGNATURE_BINARY << '\n';
    out << this->width << ' ' << this->height << '\n' << this->colorRange << '\n';

    size_t size = (this->width) * (this->height);
    char* pointer = new char[size];
    
    for (int i = 0; i < size; ++i)
    {
        PixelPGM* pixel = dynamic_cast<PixelPGM*>(this->pixels[i]);

        pointer[i] = pixel->greyscale + '0';
    }
    out.write(pointer, size);

    out.close();
    return true;
}

bool PGM::writeText()
{
    std::ofstream out(this->filename);
    if(!out)
        return false;
    
    out << PGM_FILE_SIGNATURE_TEXT << '\n' << this->width << ' ' << this->height << '\n' << this->colorRange << '\n';
    if(!out)
        return false;
    
    for (unsigned int j = 0; j < height; ++j) 
    {
        for (unsigned int i = 0; i < width; ++i) 
        {
            PixelPGM* pixel = dynamic_cast<PixelPGM*>(getPixel(i, j));
            out << (int)pixel->greyscale << ' ';
        }
        out  << '\n';
    }

    out.close();
    return true;
}

bool PGM::isMonochrome() const
{
    for (Pixel* pixel : this->pixels)
    {
        PixelPGM* pixelPGM = dynamic_cast<PixelPGM*>(pixel);
        if (!pixelPGM->isMonochrome(this->colorRange))
            return false;
    }
    return true;
}

void PGM::monochrome()
{
    if (this->isMonochrome())
    {
        std::cout << "Image already monochrome !" << std::endl;
        return;
    }

    for (Pixel* pixel : this->pixels)
    {
        PixelPGM* pixelPGM = dynamic_cast<PixelPGM*>(pixel);
        pixelPGM->greyscale = (pixelPGM->greyscale > (this->colorRange / 2)) ? this->colorRange : 0;
    }
}

void PGM::negative()
{
    for (Pixel* pixel : this->pixels)
    {
        PixelPGM* pixelPGM = dynamic_cast<PixelPGM*>(pixel);

        pixelPGM->greyscale = (this->colorRange - pixelPGM->greyscale);
    }
}

std::string PGM::getType() const
{
    return "PGM";
}

#endif