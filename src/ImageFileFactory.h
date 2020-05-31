/**
 * \class ImageFileFactory
 *
 * \brief ImageFileFactory class
 *
 * The class, implementing factory pattern for image files.
 *
 * \author $Author: Boyan Dafov $
 * 
 * Contact: boyandafov123@gmail.com
 *
 */

/**
 * \class InvalidImageFileSignatureException
 *
 * \brief Exception, used to by ImageFileFictory generate() function
 *
 * Used to signalize when image file given is not supprted by our Application.
 *
 * \author $Author: Boyan Dafov $
 * 
 * Contact: boyandafov123@gmail.com
 *
 */
#ifndef __IMAGE_FILE_FACTORY_H
#define __IMAGE_FILE_FACTORY_H

#include "ImageFile.h"
#include <string>
#include <iostream>
#include <stdexcept>

/**
 * @param message exception message
 */
class InvalidImageFileSignatureException : public std::exception
{
private:
    std::string message;
public:
    InvalidImageFileSignatureException(const std::string& _message) : std::exception(), message(_message) {}
    const char* what() const noexcept;
};

class ImageFileFactory
{
public:
    /**
     * Generates empty ImageFile object from file given, checking the file signature
     * from so called 'magic bytes'.
     * 
     * @return pointer to the generated object.
     */
    static ImageFile* generate(const std::string& filepath);
};

#endif