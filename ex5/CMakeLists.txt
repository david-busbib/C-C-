cmake_minimum_required(VERSION 3.23)
project(ex5-dbusbib123_1)

set(CMAKE_CXX_STANDARD 14)

add_executable(ex5-dbusbib123_1 presubmit.cpp Movie.h
        Movie.cpp
        RecommenderSystem.h
        RecommenderSystemLoader.cpp
        RecommenderSystem.h
        RecommenderSystemLoader.h
        RecommenderSystem.cpp
        RSUser.cpp
        RSUsersLoader.cpp )

