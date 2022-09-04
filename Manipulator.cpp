//
// Created by Frederico on 04/09/2022.
//

#include "Manipulator.h"
#define CONTRAST_PRECISION 1e15

Manipulator::Manipulator(Image &image, short mode) : w(image.width()), h(image.height()), channels(image.n_channels()) {
    if(image.n_channels() > 1){
        throw std::exception("Only works with B&W");
    }

    size_t size = image.height() * image.width();
    data = new double[size];

    auto max = static_cast<double >(image.max());
    auto min = static_cast<double >(image.min());
    switch (mode) {
        case normalize_mode:
            for(size_t i = 0; i < size; i++){
                data[i] = (static_cast<double >(image[i]) - min);
            }
            max = this->max();
            for(size_t i = 0; i < size; i++){
                data[i] = data[i]/max;
            }
            break;
        case contrast_mode:
            for(size_t i = 0; i < size; i++){
                data[i] = static_cast<double >(image[i])/max;
                data[i] = 1/(data[i] + CONTRAST_PRECISION);
            }
            break;
        case direct_mode:
            for(size_t i = 0; i < size; i++){
                data[i] = static_cast<double >(image[i]);
            }
            break;
        case default_mode:
        default:
            for(size_t i = 0; i < size; i++){
                data[i] = static_cast<double >(image[i])/255.f;
            }
            break;
    }
}

Manipulator::Manipulator(int w, int h, int channels, uint8_t *data): w(w), h(h), channels(channels) {
    if(channels > 1){
        throw std::exception("Only works with B&W");
    }
    size_t size = w*h*channels;
    this->data = new double[size];
    for(int i = 0; i < size; i++){
        this->data[i] = static_cast<double >(data[i]);
    }
}

void Manipulator::normalize() {
    size_t size = w*h*channels;
    auto min = this->min();
    for(size_t i = 0; i < size; i++){
        data[i] = (data[i] - min);
    }
    auto max = this->max();
    for(size_t i = 0; i < size; i++){
        data[i] = (data[i])/max;
    }
}

double Manipulator::min() const {
    size_t size = w*h*channels;
    double min = data[0];
    for(size_t i = 0; i < size; i++) {
        if(data[i] < min)
            min = data[i];
    }
    return min;
}

double Manipulator::max() const {
    size_t size = w*h*channels;
    double max = data[0];
    for(size_t i = 0; i < size; i++) {
        if(data[i] > max)
            max = data[i];
    }
    return max;
}

std::pair<double, double> Manipulator::min_max() const {
    size_t size = w*h*channels;
    double max = data[0];
    double min = data[0];
    for(size_t i = 0; i < size; i++) {
        if(data[i] < min)
            min = data[i];
        if(data[i] > max)
            max = data[i];
    }
    return {min, max};
}

void Manipulator::remove_low(double threshold) {
    size_t size = w*h*channels;
    for(size_t i = 0; i < size; i++) {
        data[i] = data[i] > threshold ? data[i] : 0;
    }
}

Manipulator::~Manipulator() {
    delete[] data;
}

int Manipulator::height() const {
    return h;
}

int Manipulator::width() const {
    return w;
}
int Manipulator::n_channels() const {
    return channels;
}

double &Manipulator::operator[](size_t i) const {
    if(i > w*h*channels) throw std::exception("Out of range exception");
    return data[i];
}

bool Manipulator::write(string filename) const {
    const Manipulator& self = *this;
    Image image(self);
    return image.write(filename);
}
