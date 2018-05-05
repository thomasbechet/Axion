#!/bin/bash

cp ../lib/libaxion-core.so ./
LD_LIBRARY_PATH=. ./RuntimeTest
