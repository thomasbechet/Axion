cmake_minimum_required(VERSION 2.8)

#Core project
PROJECT(axion-core DESCRIPTION "Core library")
FILE(GLOB_RECURSE SRCS src/Core/*.cpp)


ADD_LIBRARY(axion-core SHARED
    
)