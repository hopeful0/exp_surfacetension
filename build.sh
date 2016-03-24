#!/bin/sh

#进入源代码环境
cd source/
#编译源代码
g++ -std=c++11 surfacetension.cpp -o main
#移动可执行文件
mv main ../main
