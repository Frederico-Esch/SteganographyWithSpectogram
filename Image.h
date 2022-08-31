#include <iostream>
#include <stdint.h>
typedef std::string string;

class Image {

    uint8_t* data;
    int w;
    int h;
    int channels;
public:

    Image(string filename);

    ~Image();

    uint8_t& operator[](size_t index);

    int width();
    int height();
    int n_channels();

    bool write(string filename);
};
