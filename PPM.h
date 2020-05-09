#ifndef __PPM_H
#define __PPM_H

#include <iostream>
#include <vector>
#include <string>

struct RGB 
{
    unsigned char red;
    unsigned char green;
    unsigned char blue;

    RGB() : red(0), green(0), blue(0) {};
};

class PPM
{
private:
    unsigned int width;
    unsigned int height;
    std::vector<RGB> pixelsTable;
public:
    PPM() : width(0), height(0) {};

    void open(const std::string& path);

    RGB& getPixel(unsigned int i, unsigned int j) 
    {
        return pixelsTable[(j * width) + i];
    }

    unsigned int getWidth() 
    {
        return width;
    }

    unsigned int getHeight() 
    {
        return height;
    }

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
                RGB& pixel = getPixel(i, j);
                std::cout << (int)pixel.red << " " << (int)pixel.green << " " << (int)pixel.blue << std::endl;
            }
        }
    }
};

#endif