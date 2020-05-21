#ifndef __PPM_H
#define __PPM_H

#include <iostream>
#include <vector>
#include <string>

#include "ImageFile.h"

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

    bool isGray() const
    {
        return ((red == green) && (green == blue));
    }

    bool isMonochrome(unsigned int colorRange) const
    {
        return (red == 0 && green == 0 && blue == 0) || (red == colorRange && green == colorRange && blue == colorRange);
    }
};

class PPM : public ImageFile
{
private:
    unsigned int colorRange;

    bool openTextType();
    bool openBinaryType();

    bool writeBinary();
    bool writeText();

    bool isGrayscale() const;
    bool isMonochrome() const;

    // float meanGreyscaleValue() const;
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