﻿# CMakeList.txt : Top-level CMake project file, do global configuration
# and include sub-projects here.
#
cmake_minimum_required (VERSION 3.8)

project ("MonsterMaker")

# Include sub-projects.
add_subdirectory ("MonsterMaker")
# add_executable(MonsterMaker MonsterMaker.cpp monster.cpp attack.cpp skill.cpp)
