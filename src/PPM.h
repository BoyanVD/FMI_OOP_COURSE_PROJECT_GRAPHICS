/**
 * \class PPM
 *
 * \brief PPM images files class
 *
 * Class, representing the PPM image files format. All public methods
 * overrides the base class methods.
 *
 * \author $Author: Boyan Dafov $
 * 
 * Contact: boyandafov123@gmail.com
 *
 */

/**
 * \struct PixelPPM
 *
 * \brief PPM files pixels struct
 *
 * Used to represent the pixels of PPM files format. Extends the
 * Pixel base struct.
 *
 * \author $Author: Boyan Dafov $
 * 
 * Contact: boyandafov123@gmail.com
 *
 */
#ifndef __PPM_H
#define __PPM_H

#include <iostream>
#include <vector>
#include <string>

#include "ImageFile.h"

/**
 * @param red pixel red value
 * @param green pixel green value
 * @param blue pixel blue value
 */
struct PixelPPM : public Pixel
{
    unsigned char red;
    unsigned char green;
    unsigned char blue;

    PixelPPM() : red(0), green(0), blue(0) {};

    virtual Pixel* clone() const
    {
        return new PixelPPM(*this);
    }

    /**
     * Checks if pixel is gray
     * 
     * @return bool
     */
    bool isGray() const
    {
        return ((red == green) && (green == blue));
    }

    /**
     * Checks if pixel is monochrome
     * 
     * @return bool
     */
    bool isMonochrome(unsigned int colorRange) const
    {
        return (red == 0 && green == 0 && blue == 0) || (red == colorRange && green == colorRange && blue == colorRange);
    }
};

class PPM : public ImageFile
{
private:
    unsigned int colorRange;

    /**
     * Opens PPM ASCII file format
     * 
     * @return bool, representing the success
     */
    bool openTextType();

    /**
     * Opens PPM binary file format
     * 
     * @return bool, representing the success
     */
    bool openBinaryType();

    /**
     * Writes in PPM ASCII file format
     * 
     * @return bool, representing the success
     */
    bool writeBinary();

    /**
     * Writes to PPM ASCII file format
     * 
     * @return bool, representing the success
     */
    bool writeText();

    /**
     * Checks if all image pixels are in grayscale already
     * 
     * @return bool
     */
    bool isGrayscale() const;

    /**
     * Checks if all image pixels are monochrome already
     * 
     * @return bool
     */
    bool isMonochrome() const;

public:
    PPM() : ImageFile("", ""), colorRange(255) {};
    PPM(const std::string& _filepath, const std::string& _type) : ImageFile(_filepath, _type), colorRange(255) {};

    void open() override;
    void write() override;
    void grayscale() override;
    void print() override;
    void monochrome() override;
    void negative() override;
    virtual void redscale() override;
    virtual void greenscale() override;
    virtual void bluescale() override;

    std::string getType() const override;

    virtual ImageFile* clone() const
    {
        return new PPM(*this);
    }
};

#endif