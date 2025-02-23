cmake_minimum_required(VERSION 3.14)
project(V2x)

# 設定 C++ 標準
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(
    "C:/Users/USER/Documents/C++lib/bls-signatures/src"
)

add_executable(V2x main.cpp)

target_link_libraries(V2x
    PRIVATE
    "C:/Users/USER/Documents/C++lib/bls-signatures/build/src/Release/bls.lib"
    "C:/Users/USER/Documents/C++lib/bls-signatures/build/_deps/sodium-build/Release/sodium.lib"
)
