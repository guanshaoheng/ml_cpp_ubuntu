#include <iostream>
#include <torch/torch.h>

int main(int argc, char **argv)
{

    torch::Tensor x = torch::linspace(0, 3.14, 20).view({20, 1});
    
    torch::Tensor one = torch::ones({3,3});
    std::cout<< one << std::endl;

    std::cout << x << std::endl;

    if (torch::cuda::is_available())
    {
        std::cout << "CUDA is available! " << std::endl;
        x = x.to(torch::kCUDA);
    }
    std::cout << x << std::endl;

    return 0;
}