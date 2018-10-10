#!/bin/bash

cp ../../lib/libaxion-core.so ./
cp ../../lib/libaxion-glfw.so ./
cp ../../lib/libaxion-opengl.so ./

LD_LIBRARY_PATH=. ./RuntimeTest
