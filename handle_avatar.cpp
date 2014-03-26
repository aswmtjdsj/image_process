#include "common.h"
#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

void showImage(const char * window_name, const cv::Mat &img) {
    cv::namedWindow(window_name, cv::WINDOW_AUTOSIZE);
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
    cv::cvtColor(avatar, grey_ava, cv::COLOR_BGR2GRAY);
    cv::imwrite(avatar_name_mod, grey_ava);

    char * ava_bi_name = new char[100];
    sprintf(ava_bi_name, "%s/avatar_bi.jpg", output_dir); 
    cv::Mat bi_ava;
    cv::bilateralFilter(avatar, bi_ava, 10, 100, 100); 
    cv::imwrite(ava_bi_name, bi_ava);

    char * ava_edge_name = new char[100];
    sprintf(ava_edge_name, "%s/avatar_edge.jpg", output_dir); 
    cv::Mat edge_ava;
    cv::Canny(bi_ava, edge_ava, 50, 100);
    std::cout << edge_ava.rows << ' ' << edge_ava.cols << '\n';

    /*cv::MatConstIterator_<CvScalar> it = edge_ava.begin<CvScalar>(), it_end = edge_ava.end<CvScalar>();
      int cnt = 0;
      for(; it != it_end; ++it) {
      cnt ++;
      std::cout << cnt << ' ' << cnt / edge_ava.rows << ' ' << cnt % edge_ava.rows << ": ";
      CvScalar a = *it;
      std::cout << a.val[0] << ' ' << a.val[1] << ' ' << a.val[2] << '\n';
      }*/

    //std::cout << "R (python)  = " << std::endl << cv::format(edge_ava,"python") << std::endl << std::endl;
    cv::imwrite(ava_edge_name, edge_ava);

    char * ava_edge_mod_name = new char[100];
    sprintf(ava_edge_mod_name, "%s/avatar_edge_mod.jpg", output_dir); 
    cv::Mat edge_mod(edge_ava.rows, edge_ava.cols, CV_8UC3);
    for(int i = 0; i < edge_ava.rows; i++) {
        for(int j = 0; j < edge_ava.cols; j++) {
            // std::cout << i << ' ' << j << '\n';
            //edge_ava.at<CvScalar>(i, j) = cvScalar(255, 0, 0);
            CvPoint a = cvPoint(j, i);
            if(edge_ava.at<uchar>(i, j) == 255) {
                //edge_mod.at<CvScalar>(i, j) = 0;
                CvScalar biu = cvScalar(0);
                //CvScalar biu = cvScalar(random()%256, random()%256, random()%256);
                cv::circle(edge_mod, a, 5, biu);
            }
            else if(edge_ava.at<uchar>(i, j) == 0) {
                //edge_mod.at<CvScalar>(i, j) = 255;
                CvScalar biu = cvScalar(random()%256, random()%256, random()%256);
                //CvScalar biu = cvScalar(255, 255, 255);
                cv::circle(edge_mod, a, 1, biu);
            }
        }
    }
    cv::imwrite(ava_edge_mod_name, edge_mod);

    char * ava_scaled_mod_name = new char[100];
    sprintf(ava_scaled_mod_name, "%s/avatar_scaled_mod.jpg", output_dir); 
    double scale = 0.25;
    cv::Size dsize = cv::Size(edge_mod.cols*scale, edge_mod.rows*scale);
    cv::Mat scaled_mod = cv::Mat(dsize, CV_8UC3);
    cv::resize(edge_mod, scaled_mod, dsize);
    cv::imwrite(ava_scaled_mod_name, scaled_mod);

    return 0;
}
