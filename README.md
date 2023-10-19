# onnxruntime
A simple, cross-plaform onnx runtime for cpu inference

在Debian Linux中编译此工程：
1. 安装CMake：sudo apt install cmake
2. 安装libprotobuf-dev: sudo apt install libprotobuf-dev

可能出现的问题：
安装protoc编译工具：sudo apt install protobuf-compiler
对工程文件中的protos/onnx.proto3文件进行编译：protoc --cpp_out=. onnx.proto3