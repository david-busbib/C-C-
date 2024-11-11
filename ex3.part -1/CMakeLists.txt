cmake_minimum_required(VERSION 3.22)
project(untitled5 C)

set(CMAKE_C_STANDARD 99)

add_executable(untitled5 markov_chain.c markov_chain.h tweets_generator.c linked_list.c linked_list.h markov_chain.h)
