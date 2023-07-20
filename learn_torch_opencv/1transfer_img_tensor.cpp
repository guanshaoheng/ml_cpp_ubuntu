//
// Created by shguan on 7/20/23.
//
#include <torch/torch.h>
#include <opencv4/opencv2/opencv.hpp>
#include "../utils/utils.h"
#include "../learn_torch/network.hpp"

using namespace cv;

std::string get_image_type(const Mat& img, bool more_info=true)
{
    std::string r;
    int type = img.type();
    uchar depth = type & CV_MAT_DEPTH_MASK;
    uchar chans = 1 + (type >> CV_CN_SHIFT);

    switch (depth) {
        case CV_8U:  r = "8U"; break;
        case CV_8S:  r = "8S"; break;
        case CV_16U: r = "16U"; break;
        case CV_16S: r = "16S"; break;
        case CV_32S: r = "32S"; break;
        case CV_32F: r = "32F"; break;
        case CV_64F: r = "64F"; break;
        default:     r = "User"; break;
    }

    r += "C";
    r += (chans + '0');

    if (more_info)
        std::cout << "depth: " << img.depth() << " channels: " << img.channels() << std::endl;

    return r;
}

void show_image(Mat& img, std::string title)
{
    std::string image_type = get_image_type(img);
//    namedWindow(title + " type:" + image_type, WINDOW_AUTOSIZE); // Create a window for display.
    imshow(title + " type:" + image_type, img);
    waitKey(0);
}

auto transpose(at::Tensor tensor, c10::IntArrayRef dims = { 0, 3, 1, 2 })
{
    std::cout << "############### transpose ############" << std::endl;
    std::cout << "shape before : " << tensor.sizes() << std::endl;
    tensor = tensor.permute(dims);
    std::cout << "shape after : " << tensor.sizes() << std::endl;
    std::cout << "######################################" << std::endl;
    return tensor;
}

auto ToTensor(Mat img, bool show_output = false, bool unsqueeze=false, int unsqueeze_dim = 0)
{
    std::cout << "image shape: " << img.size() << std::endl;
    at::Tensor tensor_image = torch::from_blob(img.data, { img.rows, img.cols, 3 }, at::kByte);

    if (unsqueeze)
    {
        tensor_image.unsqueeze_(unsqueeze_dim);
        std::cout << "tensors new shape: " << tensor_image.sizes() << std::endl;
    }

    if (show_output)
    {
        std::cout << tensor_image.slice(2, 0, 1) << std::endl;
    }
    std::cout << "tenor shape: " << tensor_image.sizes() << std::endl;
    return tensor_image;
}

auto ToInput(at::Tensor tensor_image)
{
    // Create a vector of inputs.
    return std::vector<torch::jit::IValue>{tensor_image};
}

auto ToCvImage(at::Tensor tensor, bool show_img=false)
{
    int width = tensor.sizes()[0];
    int height = tensor.sizes()[1];
    try
    {
        Mat output_mat(Size{ height, width }, CV_8UC3, tensor.data_ptr<uchar>());

        if (show_img){
            show_image(output_mat, "converted image from tensor");
        }
        return output_mat.clone();
    }
    catch (const c10::Error& e)
    {
        std::cout << "an error has occured : " << e.msg() << std::endl;
    }
    return Mat(height, width, CV_8UC3);
}

int main(int argc, const char* argv[])
{

    std::cout << "\n==========================\n" ;
    std::cout << "Program: " << argv[0] << std::endl;
    std::cout << "CWD: " << get_cwd() << std::endl;
    if (argc != 2){
        std::cout << "Please specify the path of the img!" << std::endl;
        return -1;
    }
    std::cout << "Fig path: " << argv[1] << std::endl;
    std::cout << "==========================\n" ;


    std::string msg = "sample image";
    auto img = imread(argv[1]);
    show_image(img, msg);

    // convert the cvimage into tensor
    auto tensor = ToTensor(img);

    // 处理图片，通过改变图片对应像素点的大小
    auto cv_img = ToCvImage(tensor.clamp_min(100), true);

    for (int i: {10, 20, 30, 50, 100, 200}){
        cv_img = ToCvImage(tensor.clamp_min(i));
        show_image(cv_img, "min " + std::to_string(i));
    }
    for (int i :  {20, 30, 50, 100, 200, 255}){
        cv_img = ToCvImage(tensor.clamp_max(i));
        show_image(cv_img, "max " + std::to_string(i));
    }

    // convert the tensor into float and scale it
    tensor = tensor.toType(c10::kFloat).div(255);
    // swap axis
    tensor = transpose(tensor, { (2),(0),(1) });
    //add batch dim (an inplace operation just like in pytorch)
    tensor.unsqueeze_(0);

    auto input_to_net = ToInput(tensor);


    torch::jit::script::Module r18;

    try
    {
        std::string save_path = "../learn_torch/net.pt";

        Net net;
        // Deserialize the ScriptModule from a file using torch::jit::load().
        load_model(net, save_path);

        // Execute the model and turn its output into a tensor.
        at::Tensor output = r18.forward(input_to_net).toTensor();

        //sizes() gives shape.
        std::cout << output.sizes() << std::endl;
        std::cout << "output: " << output[0] << std::endl;
        //std::cout << output.slice(/*dim=*/1, /*start=*/0, /*end=*/5) << '\n';

    }
    catch (const c10::Error& e)
    {
        std::cerr << "error loading the model\n" <<e.msg();
        return -1;
    }

    std::cout << "ok\n";
    std::system("pause");
    return 0;
}