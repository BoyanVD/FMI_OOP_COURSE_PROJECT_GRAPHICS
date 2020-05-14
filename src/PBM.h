#ifndef __PBM_H
#define __PBM_H

#include <iostream>
#include <vector>
#include <string>

#include "ImageFile.h"

struct PixelPBM : public Pixel
{
    unsigned char isBlack; // using unsigned char instead of bool for less memory

    PixelPBM() : isBlack(0) {};
};

class PBM : public ImageFile
{
private:
    bool openTextType();
    bool openBinaryType();
public:
    PBM() : ImageFile("", "") {};
    PBM(const std::string& _filepath, const std::string& _type) : ImageFile(_filepath, _type) {};

    void open();

    void print()
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
};

#endif