cmake_minimum_required(VERSION 3.25.0)

project(onnx_parser)

find_package(Protobuf REQUIRED)

add_executable(main
    main.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/include/onnx.proto3.pb.cc
)

target_include_directories(main PUBLIC
    ${Protobuf_INCLUDE_DIRS}
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_link_libraries(main PUBLIC
    ${Protobuf_LIBRARY}

)