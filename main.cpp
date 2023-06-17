// #include <fcntl.h>

#include <iostream>
#include <fstream>

#include "include/onnx.proto3.pb.h"

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

int main(int argc, char **argv)
{
    if(argc != 2)
    {
        std::cout << "parameter error!" << std::endl;
        exit(-1);
    }
    onnx::ModelProto model{};
    read_proto(std::string(argv[1]), model);
    int num_node = model.graph().node_size();
    std::cout << "graph node size: " << num_node << std::endl;

    for(int i=0; i<num_node; i++)
    {
        std::cout << "node: " << i << ", name: " << model.graph().node(i).name() << std::endl;
    }

}