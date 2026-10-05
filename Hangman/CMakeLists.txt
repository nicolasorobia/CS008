cmake_minimum_required(VERSION 3.28)
project(BTSHangman)
set(CMALE_CXX_STANDARD 17)

add_executable(main main.cpp gamelogic.cpp board.cpp player.cpp)