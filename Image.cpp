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

uint8_t Image::max() {
    int size = h * w * channels;

    uint8_t max = data[0];
    for (int i = 0; i < size; i++){
        if (data[i] > max){
            max = data[i];
        }
    }

    return max;
}

uint8_t Image::min() {
    int size = h * w * channels;

    uint8_t min = data[0];
    for (int i = 0; i < size; i++){
        if (data[i] < min)
            min = data[i];
    }

    return min;
}

void Image::contrast() {
    //Increase contrast
    //I need to stretch the distance between colors
    //Make a look-up table (LUT)
    if(channels > 1) throw new std::exception("Only works with B&W");
    uint8_t LUT[256];
    //uint8_t max = this->max();
    //uint8_t min = this->min();

    auto [min, max] = this->min_max();


    int step =  255 / (max - min);
    for(int i = min; i <= max; i++){
        LUT[i] = (i-min)*step;
        if(i*step > 255){
            //std::cout << "SOMETHING WRONG" << std::endl;
            throw std::exception("Something went wrong when adjusting the contrast");
        }
    }

    //Change values from image based on LUT
    for (int i = 0; i < w*h*channels; i++) {
        data[i] = LUT[data[i]];
    }
}

std::pair<uint8_t, uint8_t> Image::min_max() {
    int size = h * w * channels;
    uint8_t min = data[0];
    uint8_t max = data[0];
    for (int i = 0; i < size; i++){
        if (data[i] < min)
            min = data[i];
        if (data[i] > max)
            max = data[i];
    }
    return {min, max};
}

Image::Image(const Manipulator &manipulator): w(manipulator.height()), channels(manipulator.n_channels()), h(manipulator.height()), manual(true) {
    size_t size = w*h*channels;
    data = new uint8_t [size];
    for(size_t i = 0; i < size; i++ ){
        data[i] = static_cast<uint8_t>(std::ceil(manipulator[i]*255));
    }
}
