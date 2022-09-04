#pragma once
#include <iostream>
#include "Image.h"
typedef std::string string;
class Image;

class Manipulator {
    double* data;
    int w, h, channels;

public:
    Manipulator(Image& image, short mode);
    Manipulator(int w, int h, int channels, uint8_t* data);
    ~Manipulator();

    void normalize();
    double min() const;
    double max() const;
    std::pair<double, double> min_max() const;
    void remove_low(double threshold);
    bool write(string filename) const;

    int height()     const;
    int width()      const;
    int n_channels() const;

    double& operator[](size_t i) const;

    static const short default_mode   = 0;
    static const short normalize_mode = 1;
    static const short contrast_mode  = 2;
    static const short direct_mode    = 3;
};