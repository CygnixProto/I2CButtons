cmake_minimum_required(VERSION 3.6)
project(I2CButtons)

set(CMAKE_CXX_STANDARD 20)

add_executable(I2CButtons example.cpp I2CButtons.cpp)
target_link_libraries(I2CButtons i2c)
