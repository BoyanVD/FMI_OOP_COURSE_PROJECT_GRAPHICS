#ifndef __IMAGE_FILE_FACTORY_CPP
#define __IMAGE_FILE_FACTORY_CPP

#include "ImageFileFactory.h"
#include "ImageFile.h"
#include "Constants.h"
#include "PPM.h"
#include "PBM.h"
#include "PGM.h"

#include <fstream>

// Find the file type from the signature. Must implement constructor only by field filename for Image File.
ImageFile* ImageFileFactory::generate(const std::string& filepath)
{
    std::ifstream file(filepath);
    if (!file)
    {
        std::cout << "Problem while opening file " << filepath << " !" << std::endl; 
        return nullptr;
    }

    std::string magicNumber;
    file >> magicNumber;

    file.close();

    ImageFile* item;
    if (magicNumber == PPM_FILE_SIGNATURE)
        item = new PPM(filepath);
    else if (magicNumber == PGM_FILE_SIGNATURE)
        item = new PGM(filepath);
    else if (magicNumber == PBM_FILE_SIGNATURE)
        item = new PBM(filepath);
    
    return item;
}

#endif