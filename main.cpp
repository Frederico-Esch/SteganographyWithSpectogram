#include "Image.h"
#include <algorithm>
#include <cstring>
const string filename = "./robot.png";

uint8_t min_pixel(Image& image){
    int size = image.height() * image.width() * image.n_channels();

    uint8_t min = image[0];
    for (int i = 0; i < size; i++){
        if (image[i] < min)
            min = image[i];
    }

    return min;
}

uint8_t max_pixel(Image& image){
    int size = image.height() * image.width() * image.n_channels();

    uint8_t max = image[0];
    for (int i = 0; i < size; i++){
        if (image[i] > max){
            max = image[i];
        }
    }

    return max;
}

int main() {

    Image image(filename, 1); //We need it to be grey

    //Increase contrast
    //I need to streach the distance between colors
    //Make a look up table (LUT)
    uint8_t LUT[256];
    uint8_t max = max_pixel(image);
    uint8_t min = min_pixel(image);


    int step =  255 / (max - min);
    for(int i = min; i <= max; i++){
        LUT[i] = (i-min)*step;
        if(i*step > 255){
            std::cout << "SOMETHING WRONG" << std::endl;
        }
    }

    //Change values from image based on LUT
    for (int i = 0; i < image.width()*image.height()*image.n_channels(); i++) {
        image[i] = LUT[image[i]];
    }

    image.write("contraste.png");
    return 0;
}
