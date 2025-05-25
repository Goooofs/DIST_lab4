cmake_minimum_required(VERSION 3.10)
project(Lab4Encryption)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(OpenSSL REQUIRED)

include_directories(includes)

add_executable(main
    src/main.cpp
    src/singleton.cpp
    src/aes_encrypt.cpp
)

target_link_libraries(main OpenSSL::Crypto)