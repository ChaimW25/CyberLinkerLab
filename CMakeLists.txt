cmake_minimum_required(VERSION 3.20)
project(Linker C)

set(CMAKE_C_STANDARD 99)

add_executable(Linker secret.c server.c scanfAttack.c)
