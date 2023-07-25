# 采用c++ libtorch进行机器学习的操作
## 安装
推荐在ubuntu下调用libtorch，在windows中会碰到各种各样的问题。

## 生成tensor
在生成`Tensor`类之前，需要明确的是，在`torch`对应的`namespace`下生成的tensor是可以采用`torch::requires_grad()`关键字将其调整为可对其
求导数的性质。例如一下代码：
```c++
#include <torch/torch.h>

int main(int argc, char ** argv){
    torch::Tensor tensor = torch::rand({2, 3}, torch::requires_grad())
}
```
在另外一个命名空间`namespace`中也有`at::Tensor`，ATen 本质上是一个张量库，PyTorch 中几乎所有其他 Python 和 C++ 接口都是在其之上构建的。
但是采用`at::Tensor`定义的张量不可定义`torch::requires_grad()`,
```c++
#include <ATen/ATen.h>

at::Tensor a = at::ones({2, 2}, at::kInt);
at::Tensor b = at::randn({2, 2});
auto c = a + b.to(at::kInt);
```
