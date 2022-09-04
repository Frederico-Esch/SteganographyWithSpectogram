#include <iostream>
#include <stdint.h>
typedef std::string string;
class Image {

    uint8_t* data;
    int w;
    int h;
    int channels;
    bool manual;
public:

    Image(string filename, int n = 0);
    Image(int w, int h, int channels);

    ~Image();

    uint8_t& operator[](size_t index);

    int width();
    int height();
    int n_channels();

    bool write(string filename);
};

class Manipulator {

    float* data;
    int w, h, channels;

public:
    Manipulator(Image& image);
    Manipulator(int w, int h, int channels, uint8_t* data);
    void normalize();
    void remove_low(float threshold);
};
