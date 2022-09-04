#pragma once
#include <iostream>
#include <cstdint>
#include "Manipulator.h"
class Manipulator;
typedef std::string string;
class Image {

    uint8_t* data;
    int w;
    int h;
    int channels;
    bool manual;
public:

    Image(string filename, int n = 0);
    Image(const Manipulator& manipulator);
    Image(int w, int h, int channels);

    ~Image();

    uint8_t& operator[](size_t index);

    int width();
    int height();
    int n_channels();
    uint8_t max();
    uint8_t min();
    std::pair<uint8_t, uint8_t> min_max();
    void contrast();

    bool write(string filename);
};
