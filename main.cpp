#include "Image.h"
#include <algorithm>
#include <cstring>
const string filename = "../robot.png";


int main() {

    Image image(filename, 1); //We need it to be grey
    Manipulator mani(image, Manipulator::contrast_mode);
    mani.normalize();
    mani.remove_low(0.5);
    image.contrast();

    image.write("../image_contrast.png");
    mani.write("../manipulator_contrast.png");

    return 0;
}
