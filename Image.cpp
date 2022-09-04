#include "Image.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"


//Constructors
Image::Image(string filename, int n) : manual(false) {
    const char* _filename = filename.c_str();
    data = stbi_load(_filename, &w, &h, &channels, n);
    if(n){
        channels = n;
    }
}

Image::Image(int w, int h, int channels):w(w), h(h), channels(channels), manual(true){
    data = new uint8_t[w*channels*h];
}

//Destructors
Image::~Image(){
    if(manual) {
        delete [] data;
    }
    else{
        stbi_image_free(data);
    }
}

//Operator Overload
uint8_t& Image::operator[](size_t index){
    return data[index];
}

//Save File
bool Image::write(string filename){
    return (bool)stbi_write_png(filename.c_str(), w, h, channels, (void*)data, w*channels);
}

//Getters
int Image::n_channels(){
    return channels;
}

int Image::width(){
    return w;
}

int Image::height(){
    return h;
}
