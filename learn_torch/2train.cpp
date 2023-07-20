#include <iostream>
#include "network.hpp"

using namespace std;

int main(int argc, char ** argv){
    
    cout << argv[0] << endl;

    Net net(1, 1, 100);

    torch::Tensor x = torch::linspace(0, 3.14, 20).view({20, 1});
    torch::Tensor y = torch::sin(3. * x + 0.15);
    
    torch::optim::Adam op_adam(net->parameters());


    for (int epoch = 0; epoch< 10000; epoch++){ 
        torch::Tensor y_pre = net(x);
        torch::Tensor mse = torch::mse_loss(y_pre, y);

        op_adam.zero_grad();
        mse.backward();
        op_adam.step();

        if (epoch % 100 ==0){
            cout<< "Epoch " << epoch << "\tloss " << mse.cpu().item()<< endl;
        }
    }

    std::string  net_save_name = "net.pt";
    std::string  optim_save_name = "optim_state.pt";
    save_model(net, net_save_name);
    save_optimizer_state(& op_adam, optim_save_name);

    return 0;
}