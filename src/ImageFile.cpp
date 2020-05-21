#ifndef __IMAGE_FILE_CPP
#define __IMAGE_FILE_CPP

#include "ImageFile.h"
#include "ImageFileFactory.h"
#include <stdexcept>

const std::map<std::string, ImageFile::Transformation> ImageFile::TRANSFORMATIONS = {
    {"grayscale", &ImageFile::grayscale},
    {"monochrome", &ImageFile::monochrome},
    {"negative", &ImageFile::negative},
    {"redscale", &ImageFile::redscale},
    {"greenscale", &ImageFile::greenscale},
    {"bluescale", &ImageFile::bluescale}
};

bool ImageFile::isThereSuchTransformation(std::string transformation)
{
    std::map<std::string, ImageFile::Transformation>::const_iterator it = TRANSFORMATIONS.find(transformation);
    return (it != TRANSFORMATIONS.end());
}

ImageFile* ImageFile::collage(std::string direction, std::string image1Filename, std::string image2Filename, std::string outimageFilename)
{
    ImageFile* image1 = ImageFileFactory::generate(image1Filename);
    ImageFile* image2 = ImageFileFactory::generate(image2Filename);
    if (image1 == nullptr || image2 == nullptr)
    {
        throw std::invalid_argument("Invalid images !");

    } else if (image1->type != image2->type)
    {
        throw std::invalid_argument("Images must be from the same type !");
    }

    image1->open();
    image2->open();

    if (image1->width != image2->width || image1->height != image2->height) // dimension can be different depending on direction
        throw std::invalid_argument("Images must be from the same dimensions !");

    unsigned int collageHeight;
    unsigned int collageWidth;

    if (direction == "horizontal")
    {
        collageHeight = image1->height;
        collageWidth = image1->width + image2->width;

    } else if (direction == "vertical")
    {
        collageHeight = image1->height + image2->height;
        collageWidth = image1->width;
    }

    std::vector<Pixel*> newPixels(image1->pixels.size() + image2->pixels.size());
    // std::cout << collageWidth << " " << collageHeight << std::endl;
    // std::cout << newPixels.size() << std::endl;

    for (unsigned int i = 0; i < collageHeight; ++i) 
    {
        for (unsigned int j = 0; j < collageWidth; ++j) 
        {
            if (direction == "horizontal")
            {
                newPixels[(i * collageWidth) + j] = (j < image1->width) ? image1->getPixel(j, i) : image2->getPixel(j - image1->width, i);
            } else
            {
                newPixels[(i * collageWidth) + j] = (i < image1->height) ? image1->getPixel(j, i) : image2->getPixel(j, i- image1->height);
            }
        }
    }

    ImageFile* newFile = ImageFileFactory::generate(image1Filename); // The new file will be in the format of the format of first image
    newFile->setFilename(outimageFilename);
    newFile->width = collageWidth;
    newFile->height = collageHeight;
    newFile->setPixels(newPixels);

    return newFile;
}

void ImageFile::setPixels(const std::vector<Pixel*>& _pixels)
{
    this->pixels.empty();
    this->pixels.resize(_pixels.size());

    int index = 0;
    for (Pixel* pixel : _pixels)
    {
        this->pixels[index] = pixel->clone();
        ++index;
    }
}

void ImageFile::executeTransformation(const std::string& transformation)
{
    std::map<std::string, ImageFile::Transformation>::const_iterator it = TRANSFORMATIONS.find(transformation);
    if (it == TRANSFORMATIONS.end())
    {
        std::cout << "Invalid transformation given ! " << std::endl;
        return;
    }

    Transformation function = it->second;
    (this->*function)();
}

#endif