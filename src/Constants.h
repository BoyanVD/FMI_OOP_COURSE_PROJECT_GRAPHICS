#ifndef __CONSTANTS_H
#define __CONSTANTS_H

#include <iostream>
#include <string>

const std::string PPM_FILE_SIGNATURE_TEXT = "P3";
const std::string PGM_FILE_SIGNATURE_TEXT = "P2";
const std::string PBM_FILE_SIGNATURE_TEXT = "P1";

const std::string PPM_FILE_SIGNATURE_BINARY = "P6";
const std::string PGM_FILE_SIGNATURE_BINARY = "P5";
const std::string PBM_FILE_SIGNATURE_BINARY = "P4";

const std::string INPUT_COMMAND_DELIMETER = " ";
const unsigned INITIAL_SESSION_ID = 1;

const float GRAYSCALE_RED_COEFF = 0.299f;
const float GRAYSCALE_GREEN_COEFF = 0.587f;
const float GRAYSCALE_BLUE_COEFF = 0.114f;

#endif