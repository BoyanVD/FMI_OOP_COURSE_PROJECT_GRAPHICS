#ifndef __IMAGE_FILE_H
#define __IMAGE_FILE_H

#include <string>
#include <vector>
#include <iostream>
#include <map>

struct Pixel 
{
    virtual ~Pixel() {};
    virtual Pixel* clone() const = 0;
};

// using ImageFileTransformation = void (ImageFile::*)();
// typedef void (ImageFile::*Transformation)();

class ImageFile
{
protected:
    // typedef void (ImageFile::*Transformation)();
    typedef void (ImageFile::*Transformation)();
    static const std::map<std::string, Transformation> TRANSFORMATIONS;

    std::string filename;
    std::string type; // consider enum type
    std::vector<Pixel*> pixels;
    unsigned int width;
    unsigned int height;

    void setPixels(const std::vector<Pixel*>& _pixels);
public:
    ImageFile(const std::string& _filename, const std::string& _type) : filename(_filename), type(_type), width(0), height(0) {};

    virtual void open() = 0;
    virtual void write() = 0;
    virtual void grayscale() = 0;
    virtual void monochrome() = 0;
    virtual void negative() = 0;
    virtual void redscale() = 0;
    virtual void greenscale() = 0;
    virtual void bluescale() = 0;

    void executeTransformation(const std::string& transformation);

    virtual std::string getType() const = 0;
    virtual ImageFile* clone() const = 0;

    static ImageFile* collage(std::string direction, std::string image1Filename, std::string image2Filename, std::string outimageFilename);

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

    std::string getFilename()
    {
        return this->filename;
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

    static bool isThereSuchTransformation(std::string transformation);

    virtual ~ImageFile()
    {
        for (Pixel* pixel : pixels)
        {
            delete pixel;
        }
    };
};


#endif