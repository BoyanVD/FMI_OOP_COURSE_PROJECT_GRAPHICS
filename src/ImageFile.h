#ifndef __IMAGE_FILE_H
#define __IMAGE_FILE_H

#include <string>
#include <vector>
#include <iostream>

struct Pixel 
{
    virtual ~Pixel() {};
};

class ImageFile
{
protected:
    std::string filename;
    std::vector<Pixel*> pixels;
    unsigned int width;
    unsigned int height;

public:
    ImageFile(std::string _filename) : filename(_filename), width(0), height(0) {};

    virtual void open() = 0;

    Pixel* getPixel(unsigned int i, unsigned int j) 
    {
        return pixels[(j * width) + i];
    }

    unsigned int getWidth() 
    {
        return width;
    }

    unsigned int getHeight() 
    {
        return height;
    }

    virtual void print() {std::cout << filename << std::endl;}; // must make virtual !!!!!!!!!!!!!!!!!!!

    virtual ~ImageFile()
    {
        for (Pixel* pixel : pixels)
        {
            delete pixel;
        }
    };
};


#endif