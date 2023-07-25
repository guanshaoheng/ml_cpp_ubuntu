import sys

# add the path to the exmaple file
sys.path.append("/home/shguan/ml_cpp/cmake-build-debug/learn_pybind")

# import the compiled file   example.cpython-310-x86_64-linux-gnu.so
import example


print(example.add(1, 1))
print(example.add(5.3, 5.2))
print(example.add('beautiful   ', "Graz!!!"))

example.print_something()

