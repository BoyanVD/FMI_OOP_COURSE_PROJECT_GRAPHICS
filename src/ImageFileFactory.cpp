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
    std::ifstream file(filepath, std::ios::binary);
    if (!file)
    {
        std::cout << "Problem while opening file " << filepath << " !" << std::endl; 
        return nullptr;
    }

    std::string magicNumber;
    file >> magicNumber;
    // std::cout << magicNumber << "----------------------------" << std::endl;

    file.close();

    ImageFile* item = nullptr;

    if (magicNumber == PPM_FILE_SIGNATURE_TEXT)
        item = new PPM(filepath, "text");
    else if (magicNumber == PPM_FILE_SIGNATURE_BINARY)
        item = new PPM(filepath, "binary");
    if (magicNumber == PGM_FILE_SIGNATURE_TEXT)
        item = new PGM(filepath, "text");
    else if (magicNumber == PGM_FILE_SIGNATURE_BINARY)
        item = new PGM(filepath, "binary");
    if (magicNumber == PBM_FILE_SIGNATURE_TEXT)
        item = new PBM(filepath, "text");
    else if (magicNumber == PBM_FILE_SIGNATURE_BINARY)
        item = new PBM(filepath, "binary");
    
    return item;
}

#endif