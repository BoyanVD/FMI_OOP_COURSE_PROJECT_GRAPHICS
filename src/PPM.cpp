#ifndef __PPM_CPP
#define __PPM_CPP

#include "Constants.h"
#include "PPM.h"
#include <fstream>

void PPM::open() 
{
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

void PPM::print()
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
            PixelPPM* pixel = dynamic_cast<PixelPPM*>(getPixel(i, j));
            std::cout << (int)pixel->red << " " << (int)pixel->green << " " << (int)pixel->blue << std::endl;
        }
    }
}

void PPM::write()
{
    if (this->type == "text" && (!this->writeText()))
        std::cout << "Cannot write text PPM file !" << std::endl;
    else if (this->type == "binary" && (!this->writeBinary()))
        std::cout << "Cannot write binary PPM file !" << std::endl;
}

bool PPM::writeBinary()
{
    std::ofstream out(this->filename, std::ios::binary);
    if (!out)
    {
        std::cout << "Problem while opening file " << this->filename << " !" << std::endl; 
        return false;
    }

    out << PPM_FILE_SIGNATURE_BINARY << '\n';
    out << this->width << ' ' << this->height << '\n' << this->colorRange << '\n';

    size_t size = (this->width) * (this->height) * 3;
    char* pointer = new char[size];
    
    for (int i = 0; i < size; i += 3)
    {
        PixelPPM* pixel = dynamic_cast<PixelPPM*>(this->pixels[i / 3]);
        pointer[i] = '0' + pixel->red;
        pointer[i + 1] = '0' + pixel->green;
        pointer[i + 2] = '0' + pixel->blue;   
    }
    out.write(pointer, size);

    out.close();
    return true;
}

bool PPM::writeText()
{
    std::ofstream out(this->filename);
    if(!out)
        return false;
    
    out << PPM_FILE_SIGNATURE_TEXT << '\n' << this->width << ' ' << this->height << '\n' << this->colorRange << '\n';
    if(!out)
        return false;
    
    for (unsigned int j = 0; j < height; ++j) 
    {
        for (unsigned int i = 0; i < width; ++i) 
        {
            PixelPPM* pixel = dynamic_cast<PixelPPM*>(getPixel(i, j));
            out << (int)pixel->red << ' ' << (int)pixel->green << ' ' << (int)pixel->blue << '\n';
        }
    }

    out.close();
    return true;
}

bool PPM::isMonochrome() const
{
    for (Pixel* pixel : this->pixels)
    {
        PixelPPM* pixelPPM = dynamic_cast<PixelPPM*>(pixel);
        if (!pixelPPM->isMonochrome(this->colorRange))
            return false;
    }

    return true;
}

bool PPM::isGrayscale() const
{
    for (Pixel* pixel : this->pixels)
    {
        PixelPPM* pixelPPM = dynamic_cast<PixelPPM*>(pixel);
        if (!pixelPPM->isGray())
            return false;
    }

    return true;
}

void PPM::grayscale()
{
    if (this->isGrayscale())
    {
        std::cout << "Image already greyscale !" << std::endl;
        return;
    }

    for (Pixel* pixel : this->pixels)
    {
        PixelPPM* pixelPPM = dynamic_cast<PixelPPM*>(pixel);

        float greyscaleValue = (pixelPPM->red * GRAYSCALE_RED_COEFF) + (pixelPPM->green * GRAYSCALE_GREEN_COEFF) + (pixelPPM->blue * GRAYSCALE_BLUE_COEFF);
        pixelPPM->red = greyscaleValue;
        pixelPPM->green = greyscaleValue;
        pixelPPM->blue = greyscaleValue;
    }
}

void PPM::monochrome()
{
    if (this->isMonochrome())
    {
        std::cout << "Image already monochrome !" << std::endl;
        return;
    }

    for (Pixel* pixel : this->pixels)
    {
        PixelPPM* pixelPPM = dynamic_cast<PixelPPM*>(pixel);

        float monochromeValue = (pixelPPM->red + pixelPPM->green + pixelPPM->blue) / 3; // Logic may not be like that
        pixelPPM->red = monochromeValue;
        pixelPPM->green = monochromeValue;
        pixelPPM->blue = monochromeValue;
    }
}

void PPM::negative()
{
    for (Pixel* pixel : this->pixels)
    {
        PixelPPM* pixelPPM = dynamic_cast<PixelPPM*>(pixel);

        pixelPPM->red = (this->colorRange - pixelPPM->red);
        pixelPPM->green = (this->colorRange - pixelPPM->green);
        pixelPPM->blue = (this->colorRange - pixelPPM->blue);
    }
}

void PPM::redscale()
{
    for (Pixel* pixel : this->pixels)
    {
        PixelPPM* pixelPPM = dynamic_cast<PixelPPM*>(pixel);

        pixelPPM->green = 0;
        pixelPPM->blue = 0;
    }
}

void PPM::greenscale()
{
    for (Pixel* pixel : this->pixels)
    {
        PixelPPM* pixelPPM = dynamic_cast<PixelPPM*>(pixel);

        pixelPPM->red = 0;
        pixelPPM->blue = 0;
    }
}

void PPM::bluescale()
{
    for (Pixel* pixel : this->pixels)
    {
        PixelPPM* pixelPPM = dynamic_cast<PixelPPM*>(pixel);

        pixelPPM->green = 0;
        pixelPPM->red = 0;
    }
}

std::string PPM::getType() const
{
    return "PPM";
}

#endif