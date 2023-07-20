//
// Created by shguan on 7/20/23.
//
#include <opencv4/opencv2/opencv.hpp>
#include <iostream>
#include <torch/torch.h>
#include "../utils/utils.h"

using namespace cv;
using namespace std;

int main(int argc, char** argv)
{
    cout << "\n==========================\n" ;
    cout << "Program: " << argv[0] << endl;
    cout << "CWD: " << get_cwd() << endl;
    if (argc != 2){
        cout << "Please specify the path of the img!" << endl;
        return -1;
    }
    cout << "Fig path: " << argv[1] << endl;
    cout << "==========================\n" ;

    cout<< torch::rand({3, 3}).unsqueeze(0).to(torch::kCUDA)<< endl;

    Mat image;
    image = imread(argv[1], 1);
    if (!image.data) {
        cout<< "No image data\n" << endl;
        return -1;
    }
    namedWindow("Display Image", WINDOW_AUTOSIZE);
    imshow("Display Image", image);
    waitKey(0);
    return 0;
}