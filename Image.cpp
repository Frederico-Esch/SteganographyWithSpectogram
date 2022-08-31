#include "Image.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"


Image::Image(string filename) {
    const char* _filename = filename.c_str();
    data = stbi_load(_filename, &w, &h, &channels, 0);
}

Image::~Image(){
    stbi_image_free(data);
}

uint8_t& Image::operator[](size_t index){
    return data[index];
}

bool Image::write(string filename){
    return (bool)stbi_write_png(filename.c_str(), w, h, channels, (void*)data, w*channels);
}

int Image::n_channels(){
    return channels;
}

int Image::width(){
    return w;
}

int Image::height(){
    return h;
}
