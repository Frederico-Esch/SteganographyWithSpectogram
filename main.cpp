#include "Image.h"
const string filename = "./robot.png";

int main() {

    Image image(filename);
    std::cout << image.height() << std::endl;
    std::cout << image.width() << std::endl;
    std::cout << image.n_channels() << std::endl;
    int count = 0;
    for (int i = 0; i < image.width()*image.n_channels(); i++) {
        if(count == 2)
            image[i] = 255;
        else
            image[i] = 0;

        count = count == 2 ? 0 : count + 1;
    }

    bool result = image.write("white_line.png");
    std::cout << "RESULT: " << result << std::endl;
    return 0;
}
