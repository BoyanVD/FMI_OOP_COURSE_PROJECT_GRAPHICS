#ifndef __PPM_H
#define __PPM_H

#include <iostream>
#include <vector>
#include <string>

#include "ImageFile.h"

struct PixelPPM : public Pixel
{
    unsigned char red;
    unsigned char green;
    unsigned char blue;

    PixelPPM() : red(0), green(0), blue(0) {};
};

class PPM : public ImageFile
{
private:
    unsigned int colorRange;

    bool openTextType();
    bool openBinaryType();
public:
    PPM() : ImageFile("", ""), colorRange(255) {};
    PPM(const std::string& _filepath, const std::string& _type) : ImageFile(_filepath, _type), colorRange(255) {};

    void open() override;

    void print() override
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
};

#endif