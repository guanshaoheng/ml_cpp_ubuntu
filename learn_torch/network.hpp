#include <torch/torch.h>

struct  NetImpl : torch::nn::Module
{
    NetImpl(int in_features, int out_features, int node_num)
        : l1(register_module("l1", torch::nn::Linear(in_features, node_num))),
        l2(register_module("l2", torch::nn::Linear(node_num, node_num))),
        l3(register_module("l3", torch::nn::Linear(node_num, out_features)))
        {}

    torch::Tensor forward(torch::Tensor x){
        x = torch::tanh(l1(x));
        x = torch::tanh(l2(x));
        x = l3(x);
        return x;
    }

    torch::nn::Linear l1, l2, l3;
};
TORCH_MODULE(Net);


void save_model(Net & net, const std::string & save_name){
    torch::serialize::OutputArchive out_archive;
    net->to(torch::kCPU);
    net->save(out_archive);
    out_archive.save_to(save_name);

    std::cout << "\n================================\n"
              << "    model saved as:\n   "
              << save_name << "\n\n";
};

void load_model(Net & net, const std::string & saved_path) {
    // Load model state

    torch::serialize::InputArchive input_archive;
    input_archive.load_from(saved_path);
    net->load(input_archive);
    std::cout << "\n================================\n"
              << "    model loaded from:\n   "
              << saved_path << "\n\n";
}

void save_optimizer_state(torch::optim::Adam * myOptimizer, const std::string & optim_state_dict_path ) {
    // Save optim state
    torch::save(*myOptimizer, optim_state_dict_path);
    /*torch::serialize::OutputArchive output_optim_archive;
    myOptimizer->save(output_optim_archive);
    output_optim_archive.save_to(optim_state_dict_path);*/
    std::cout << "\n================================\n"
              << "    optimizer saved as:\n   "
              << optim_state_dict_path << "\n\n";
}

void load_optimizer_state(torch::optim::Adam* myOptimizer, const std::string & optim_state_dict_path) {
    // Load optim state

    torch::load(*myOptimizer, optim_state_dict_path);
    /*torch::serialize::InputArchive input_archive;
    input_archive.load_from(optim_state_dict_path);
    myOptimizer->load(input_archive);*/
    std::cout << "\n================================\n"
              << "    optimizer loaded from:\n   "
              << optim_state_dict_path << "\n\n";
}