//
// Created by shguan on 7/20/23.
//
#include "network.hpp"
#include "../utils/utils.h"
using namespace std;

int main(int argc, char ** argv){
    cout<< "\n======================\n";
    cout << argv[0] << endl;

    cout << get_cwd() << endl;
    cout<< "\n======================\n";

    // 初始化模型
    Net net(1, 1, 100 );
    string net_save_path = "./net.pt";
    load_model(net, net_save_path);

    //初始化优化器
    torch::optim::Adam op_adam(net->parameters());
    string optim_state_save_path = "./optim_state.pt";
    load_optimizer_state(& op_adam, optim_state_save_path);

    // 数据集
    torch::Tensor x = torch::linspace(0, 3.14, 20).view({20, 1});
    torch::Tensor y = torch::sin(3. * x + 0.15);

    // 继续训练
    for (int epoch =0; epoch < 10000; epoch ++ ){
        torch::Tensor y_pre = net(x);
        torch::Tensor mse = torch::mse_loss(y_pre, y);

        op_adam.zero_grad();
        mse.backward();
        op_adam.step();

        if (epoch % 100 == 0){
            cout<< "Epoch " << epoch << "\tloss "<< mse.cpu().item());
        }
    }

    // 保存模型
    save_model(net, net_save_path);
    save_optimizer_state(& op_adam, optim_state_save_path);


    return 0;
}