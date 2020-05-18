#ifndef __IMAGE_FILE_H
#define __IMAGE_FILE_H

#include <string>
#include <vector>
#include <iostream>

struct Pixel 
{
    virtual ~Pixel() {};
    virtual Pixel* clone() const = 0;
};

class ImageFile
{
protected:
    std::string filename;
    std::string type; // consider enum type
    std::vector<Pixel*> pixels;
    unsigned int width;
    unsigned int height;

public:
    ImageFile(const std::string& _filename, const std::string& _type) : filename(_filename), type(_type), width(0), height(0) {};

    virtual void open() = 0;
    virtual void write() = 0;
    virtual void grayscale() = 0;
    virtual void monochrome() = 0;
    virtual void negative() = 0;

    Pixel* getPixel(unsigned int i, unsigned int j)
    {
        return pixels[(j * width) + i];
    }

    void setPixel(unsigned int i, unsigned int j, const Pixel* _pixel)
    {
        Pixel* pixel = this->getPixel(i, j);
        pixel = _pixel->clone();
    }

    unsigned int getWidth() 
    {
        return width;
    }

    unsigned int getHeight() 
    {
        return height;
    }

    void setFilename(std::string newFilename)
    {
        this->filename = newFilename;
    }

    virtual void print() 
    {
        std::cout << filename << std::endl;
    }

    void rotate(std::string direction)
    {
        std::vector<Pixel*> rotatedPixels(this->pixels.size());
        for (unsigned int i = 0; i < height; ++i) 
        {
            for (unsigned int j = 0; j < width; ++j) 
            {
                if (direction == "right")
                    rotatedPixels[j * height + (height - i - 1)] = pixels[i * width + j];
                else if (direction == "left")
                    rotatedPixels[j * height + (height - i - 1)] = pixels[(height - i - 1) * width + (width - j - 1)];
            }
        }

        this->pixels = rotatedPixels;
        
        unsigned int tmp = this->height;
        this->height = this->width;
        this->width = tmp;
    }

    virtual ~ImageFile()
    {
        for (Pixel* pixel : pixels)
        {
            delete pixel;
        }
    };
};


#endif