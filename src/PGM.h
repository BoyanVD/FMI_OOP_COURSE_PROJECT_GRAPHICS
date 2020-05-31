/**
 * \class PGM
 *
 * \brief PGM images files class
 *
 * Class, representing the PGM image files format. All public methods
 * overrides the base class methods.
 *
 * \author $Author: Boyan Dafov $
 * 
 * Contact: boyandafov123@gmail.com
 *
 */

/**
 * \struct PixelPGM
 *
 * \brief PGM files pixels struct
 *
 * Used to represent the pixels of PGM files format. Extends the
 * Pixel base struct.
 *
 * \author $Author: Boyan Dafov $
 * 
 * Contact: boyandafov123@gmail.com
 *
 */
#ifndef __PGM_H
#define __PGM_H

#include <iostream>
#include <vector>
#include <string>

#include "ImageFile.h"

/**
 * @param greyscale showing pixel greyscale value
 */
struct PixelPGM : public Pixel
{
    unsigned char greyscale;

    PixelPGM() : greyscale(0) {};

    virtual Pixel* clone() const
    {
        return new PixelPGM(*this);
    }

    /**
     * Checks if pixel is monochrome.
     * 
     * @param colorRange the max value for grey pixel
     * @return bool
     */
    bool isMonochrome(unsigned int colorRange)
    {
        return ((greyscale == 0) || (greyscale == colorRange));
    }
};

class PGM : public ImageFile
{
private:
    unsigned int colorRange;

    /**
     * Opens PGM ASCII file format
     * 
     * @return bool, representing the success
     */
    bool openTextType();

    /**
     * Opens PGM binary file format
     * 
     * @return bool, representing the success
     */
    bool openBinaryType();

    /**
     * Writes in PGM ASCII file format
     * 
     * @return bool, representing the success
     */
    bool writeBinary();

    /**
     * Writes to PGM ASCII file format
     * 
     * @return bool, representing the success
     */
    bool writeText();

    /**
     * Checks if all image pixels are monochrome.
     * 
     * @return bool
     */
    bool isMonochrome() const;
public:
    PGM() : ImageFile("", ""), colorRange(255) {};
    PGM(const std::string& _filepath, const std::string& _type) : ImageFile(_filepath, _type), colorRange(255) {};

    void open() override;
    void write() override;
    void grayscale() override {}
    void print() override;
    void monochrome() override;
    void negative() override;
    virtual void redscale() override {};
    virtual void greenscale() override {};
    virtual void bluescale() override {};

    std::string getType() const override;

    virtual ImageFile* clone() const override
    {
        return new PGM(*this);
    }
};

#endif