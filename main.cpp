#include <iostream>
#include <cstdint>
#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>

typedef std::string string;
const string filename = "../robot.png";

/* CONTRAST MODE
 * for(size_t i = 0; i < size; i++){
 *   data[i] = static_cast<double >(image[i])/max;
 *   data[i] = 1/(data[i] + CONTRAST_PRECISION);
 * }
 */

int main() {
    cv::Mat image = cv::imread(filename, cv::IMREAD_GRAYSCALE);
    image = 1/image;
    cv::imwrite("../result.png", image);
    return 0;
}
