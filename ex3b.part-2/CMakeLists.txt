cmake_minimum_required(VERSION 3.22)

project(ex3C)

set(CMAKE_C_STANDARD 11)

include_directories(.)

add_executable(ex3
       # _new_generic_type.c
        tweets_generator.c
        #snakes_and_ladders.c
        linked_list.c
        linked_list.h
        markov_chain.c
        markov_chain.h
        oh_tests_helpers.c
        oh_tests_helpers.h)
