// #include <fcntl.h>

#include <iostream>
#include <fstream>
#include <vector>

#include "include/onnx.proto3.pb.h"

enum ErrorCode
{
    PASE_PROTO_FILE_ERROR,
};

const std::map<ErrorCode, std::string> ERROR_MESSAGE = {{ErrorCode::PASE_PROTO_FILE_ERROR, "parsing model failed!"}};

void read_proto(std::string model_path, onnx::ModelProto &model)
{
    std::ifstream model_file(model_path, std::ios::in | std::ios::binary);
    if(model.ParseFromIstream(&model_file) == false)
    {
        model_file.close();
        printf("error: parsing model failed! file: %s, line: %d\n", __FILE__, __LINE__);
        exit(-1);
    }
    model_file.close();
}

uint64_t get_tensor_size(const onnx::TensorProto &X)
{
    int dim_size = X.dims_size();
    uint64_t tensor_size = 1;
    for(int i=0; i<dim_size; i++)
        tensor_size *= X.dims(i);
    return tensor_size;
}

int main(int argc, char **argv)
{
    if(argc != 2)
    {
        std::cout << "parameter error!" << std::endl;
        exit(-1);
    }
    onnx::ModelProto model{};
    read_proto(std::string(argv[1]), model);

    int num_node = model.graph().node_size(); // 计算图中所包含的节点数量
    std::cout << "info: num nodes: " << num_node << std::endl;

    for(int i=0; i<num_node; i++)
    {
        std::cout << "info: " << "node: " << i << ", name: " << model.graph().node(i).name() << std::endl;
        int num_input = model.graph().node(i).input_size();
        for(int j=0; j<num_input; j++)
        {
            auto node_input = model.graph().node(i).input(j);
            std::cout << "input name: " << j << ", name: " << node_input << std::endl;
        }
    }

    int num_tensor = model.graph().initializer_size();
    for(int i=0; i<num_tensor; i++)
    {
        uint64_t tensor_size = get_tensor_size(model.graph().initializer(i));
        std::string tensor_name = model.graph().initializer(i).name();
        int32_t data_type = model.graph().initializer(i).data_type();
        std::cout << "tensor: " << i << ", tensor_name: " << tensor_name << ", tensor_size: " << tensor_size << ", data_type:" << data_type << std::endl;
    }
}