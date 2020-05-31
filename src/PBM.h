/**
 * \class PBM
 *
 * \brief PBM images files class
 *
 * Class, representing the PBM image files format. All public methods
 * overrides the base class methods.
 *
 * \author $Author: Boyan Dafov $
 * 
 * Contact: boyandafov123@gmail.com
 *
 */

/**
 * \struct PixelPBM
 *
 * \brief PBM files pixels struct
 *
 * Used to represent the pixels of PBM files format. Extends the
 * Pixel base struct.
 *
 * \author $Author: Boyan Dafov $
 * 
 * Contact: boyandafov123@gmail.com
 *
 */
#ifndef __PBM_H
#define __PBM_H

#include <iostream>
#include <vector>
#include <string>

#include "ImageFile.h"

/**
 * @param isBlack the only filed for the struct, showing if the pixel is black.
 */
struct PixelPBM : public Pixel
{
    unsigned char isBlack; // using unsigned char instead of bool for less memory

    PixelPBM() : isBlack(0) {};

    virtual Pixel* clone() const
    {
        return new PixelPBM(*this);
    }
};

class PBM : public ImageFile
{
private:
    /**
     * Opens PBM ASCII file format
     * 
     * @return bool, representing the success
     */
    bool openTextType();

    /**
     * Opens PBM binary file format
     * 
     * @return bool, representing the success
     */
    bool openBinaryType();

    /**
     * Writes in PBM ASCII file format
     * 
     * @return bool, representing the success
     */
    bool writeBinary();

    /**
     * Writes to PBM ASCII file format
     * 
     * @return bool, representing the success
     */
    bool writeText();
public:
    PBM() : ImageFile("", "") {};
    PBM(const std::string& _filepath, const std::string& _type) : ImageFile(_filepath, _type) {};

    void open() override;
    void write() override;
    void grayscale() override {}
    void print() override;
    void monochrome() override {}
    void negative() override;
    virtual void redscale() override {};
    virtual void greenscale() override {};
    virtual void bluescale() override {};

    std::string getType() const override;

    virtual ImageFile* clone() const override
    {
        return new PBM(*this);
    }
};

#endif