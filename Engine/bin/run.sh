#!/bin/bash

cp ../lib/libaxion-core.so ./
cp ../lib/libaxion-glfw.so ./
cp ../extlibs/GLFW/lib-linux/libglfw.so ./
cp ../extlibs/GLFW/lib-linux/libglfw.so.3.2 ./
cp ../extlibs/GLFW/lib-linux/libglfw.so.3 ./
LD_LIBRARY_PATH=. ./RuntimeTest
