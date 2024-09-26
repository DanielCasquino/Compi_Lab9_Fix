cmake_minimum_required(VERSION 3.5.0)
project(lab9_fix VERSION 0.1.0 LANGUAGES C CXX)

set(CXX_STANDARD 23)

add_executable(lab9_fix exp.cpp main.cpp parser.cpp scanner.cpp token.cpp visitor.cpp)

