#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>

#define CONTRAST_SCALE_MAX 5e7

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
    image.convertTo(image, CV_64FC1);

    //cv::invert()
    double max, min;
    cv::minMaxLoc(image, &min, &max);
    std::cout << min << " " << max << std::endl;

    //cv::normalize(image, image, 1, 0, cv::NORM_MINMAX);
    //image = 1/(image + CONTRAST_SCALE_MAX); //make
    image.forEach<double>([&](double& p, const int * pos) -> void {
        p = p/max;
        p = 1/(p + CONTRAST_SCALE_MAX); // TODO UNDERSTAND  WHY IT  ISN'T WORKING LIKE A DOUBLE WOULD
    });
    cv::normalize(image, image, 1, 0, cv::NORM_MINMAX);

    image.forEach<double>([](auto& p, const int * pos) -> void {
        if(p < .5) p = 0;
    });

    cv::resize(image, image, cv::Size(1000, 1000));

    cv::namedWindow("IDK", 0);
    cv::imshow("IDK", image);
    cv::waitKey(0);

    cv::normalize(image, image, 255, 0, cv::NORM_MINMAX);
    cv::imwrite("../result.png", image);

    return 0;
}
