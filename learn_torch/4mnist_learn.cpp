//
//cloned from pytorch/cpp/example/mnist on git
//
#include <torch/torch.h>

#include <cstddef>
#include <cstdio>
#include <iostream>
#include <string>
#include <vector>

#include "utils.h"


// Where to find the MNIST dataset.
const char* kDataRoot = "./data";

// The batch size for training.
const int64_t kTrainBatchSize = 64;

// The batch size for testing.
const int64_t kTestBatchSize = 1000;

// The number of epochs to train.
const int64_t kNumberOfEpochs = 10;

// After how many batches to log a new update with the loss value.
const int64_t kLogInterval = 10;

struct Net : torch::nn::Module {
    Net()
            : conv1(torch::nn::Conv2dOptions(1, 10, /*kernel_size=*/5)),
              conv2(torch::nn::Conv2dOptions(10, 20, /*kernel_size=*/5)),
              fc1(320, 50),
              fc2(50, 10) {
        register_module("conv1", conv1);
        register_module("conv2", conv2);
        register_module("conv2_drop", conv2_drop);
        register_module("fc1", fc1);
        register_module("fc2", fc2);
    }

    torch::Tensor forward(torch::Tensor x) {
        x = torch::relu(torch::max_pool2d(conv1->forward(x), 2));
        x = torch::relu(
                torch::max_pool2d(conv2_drop->forward(conv2->forward(x)), 2));
        x = x.view({-1, 320});
        x = torch::relu(fc1->forward(x));
        x = torch::dropout(x, /*p=*/0.5, /*training=*/is_training());
        x = fc2->forward(x);
        return torch::log_softmax(x, /*dim=*/1);
    }

    torch::nn::Conv2d conv1;
    torch::nn::Conv2d conv2;
    torch::nn::Dropout2d conv2_drop;
    torch::nn::Linear fc1;
    torch::nn::Linear fc2;
};


// 训练函数，模板函数，其中将Dataloader定义为模板类
template <typename DataLoader>
void train(
        size_t epoch,
        Net& model,
        torch::Device device,
        DataLoader& data_loader,
        torch::optim::Optimizer& optimizer,
        size_t dataset_size) {
    model.train();  // 修改模型的模式，训练模式
    size_t batch_idx = 0;
    for (auto& batch : data_loader) {
        // 采用引用调用data_loader中的data
        auto data = batch.data.to(device), targets = batch.target.to(device);
        optimizer.zero_grad();
        auto output = model.forward(data);
        auto loss = torch::nll_loss(output, targets);
        AT_ASSERT(!std::isnan(loss.template item<float>()));
        loss.backward();
        optimizer.step();

        if (batch_idx++ % kLogInterval == 0) {
            std::printf(
                    "\rTrain Epoch: %ld [%5ld/%5ld] Loss: %.4f", // 字符串前用 "\r"，输出的时候只会更新 不会反复打印
                    epoch,
                    batch_idx * batch.data.size(0),
                    dataset_size,
                    loss.template item<float>());
        }
    }
}


// 测试 验证训练的精度
template <typename DataLoader>
void test(
        Net& model,
        torch::Device device,
        DataLoader& data_loader,
        size_t dataset_size) {
    torch::NoGradGuard no_grad;
    model.eval(); // 修改模型的模式，测试模式 （不需要求导）
    double test_loss = 0;
    int32_t correct = 0;
    for (const auto& batch : data_loader) {
        auto data = batch.data.to(device), targets = batch.target.to(device);
        auto output = model.forward(data);
        test_loss += torch::nll_loss(
                output,
                targets,
                /*weight=*/{},
                torch::Reduction::Sum)
                .template item<float>();
        auto pred = output.argmax(1);
        correct += pred.eq(targets).sum().template item<int64_t>();
    }

    test_loss /= dataset_size;
    std::printf(
            "\nTest set: Average loss: %.4f | Accuracy: %.3f\n",
            test_loss,
            static_cast<double>(correct) / dataset_size);
}

auto main(int argc, char ** argv) -> int {

    std::cout << "\n==========================\n" ;
    std::cout << "Program: " << argv[0] << std::endl;
    std::cout << "CWD: " << get_cwd() << std::endl;
    std::cout << "==========================\n" ;


    torch::manual_seed(1);

    // 设定训练的设备，首先采用类 torch::DeciveType 初始化一个类
    // 然后采用torch::Device 创建一个device
    torch::DeviceType device_type;
    if (torch::cuda::is_available()) {
        std::cout << "CUDA available! Training on GPU." << std::endl;
        device_type = torch::kCUDA;
    } else {
        std::cout << "Training on CPU." << std::endl;
        device_type = torch::kCPU;
    }
    torch::Device device(device_type);

    // 创建模型，将模型转移到定义的device上
    Net model;
    model.to(device);

    // 读取数据集 train
    auto train_dataset = torch::data::datasets::MNIST(kDataRoot)
            .map(torch::data::transforms::Normalize<>(0.1307, 0.3081))  //数据集处理
            .map(torch::data::transforms::Stack<>()); // 数据集转化为stack
    const size_t train_dataset_size = train_dataset.size().value();  // 获取数据集的大小
    auto train_loader =  // 建立train_loader
            torch::data::make_data_loader<torch::data::samplers::SequentialSampler>(
                    std::move(train_dataset), kTrainBatchSize);

    //读取数据集 test
    auto test_dataset = torch::data::datasets::MNIST(
            kDataRoot, torch::data::datasets::MNIST::Mode::kTest)
            .map(torch::data::transforms::Normalize<>(0.1307, 0.3081))
            .map(torch::data::transforms::Stack<>());
    const size_t test_dataset_size = test_dataset.size().value();
    auto test_loader =
            torch::data::make_data_loader(std::move(test_dataset), kTestBatchSize);

    // 创建优化器
    torch::optim::SGD optimizer(
            model.parameters(), torch::optim::SGDOptions(0.01).momentum(0.5));

    for (size_t epoch = 1; epoch <= kNumberOfEpochs; ++epoch) {
        train(epoch, model, device, *train_loader, optimizer, train_dataset_size);
        test(model, device, *test_loader, test_dataset_size);
    }
}
