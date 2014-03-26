#include "common.h"
#include <opencv2/opencv.hpp>

void showImage(const char * window_name, const cv::Mat &img) {
    cv::namedWindow(window_name, CV_WINDOW_AUTOSIZE);
    cv::imshow(window_name, img);
    cv::waitKey();
}

int main() {
    char * input_dir = new char[100],
         * output_dir = new char[100];
    sprintf(input_dir, "./input_images"); 
    sprintf(output_dir, "./output_images"); 

    char * avatar_name = new char[100];
    sprintf(avatar_name, "%s/avatar.jpg", input_dir); 
    cv::Mat avatar = cv::imread(avatar_name);

    //showImage("avatar", avatar);

    char * avatar_name_mod = new char[100];
    sprintf(avatar_name_mod, "%s/avatar_mod.jpg", output_dir); 
    cv::Mat grey_ava;
    cv::cvtColor(avatar, grey_ava, CV_BGR2GRAY);
    cv::imwrite(avatar_name_mod, grey_ava);

    char * ava_bi_name = new char[100];
    sprintf(ava_bi_name, "%s/avatar_bi.jpg", output_dir); 
    cv::Mat bi_ava;
    cv::bilateralFilter(avatar, bi_ava, 10, 150, 150); 
    cv::imwrite(ava_bi_name, bi_ava);

    return 0;
}
