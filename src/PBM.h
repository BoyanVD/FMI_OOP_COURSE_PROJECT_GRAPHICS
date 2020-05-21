#ifndef __PBM_H
#define __PBM_H

#include <iostream>
#include <vector>
#include <string>

#include "ImageFile.h"

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
    bool openTextType();
    bool openBinaryType();

    bool writeBinary();
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

    virtual ImageFile* clone() const
    {
        return new PBM(*this);
    }
};

#endif