#ifndef __PGM_H
#define __PGM_H

#include <iostream>
#include <vector>
#include <string>

#include "ImageFile.h"

struct PixelPGM : public Pixel
{
    unsigned char greyscale;

    PixelPGM() : greyscale(0) {};
};

class PGM : public ImageFile
{
private:
    unsigned int colorRange;

    bool openTextType();
    bool openBinaryType();
public:
    PGM() : ImageFile("", ""), colorRange(255) {};
    PGM(const std::string& _filepath, const std::string& _type) : ImageFile(_filepath, _type), colorRange(255) {};

    void open();

    void print()
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
};

#endif