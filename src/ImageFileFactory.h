#ifndef __IMAGE_FILE_FACTORY_H
#define __IMAGE_FILE_FACTORY_H

#include "ImageFile.h"
#include <string>
#include <iostream>

class ImageFileFactory
{
public:
    static ImageFile* generate(const std::string& filepath);
};

#endif