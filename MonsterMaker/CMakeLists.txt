# CMakeList.txt : CMake project for MonsterMaker, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

# Add source to this project's executable.
add_executable (MonsterMaker "MonsterMaker.cpp" "MonsterMaker.h" "monster.h"   "monster.cpp" "attack.h" "attack.cpp" "skill.h" "skill.cpp" "strManip.h" "strManip.cpp")


if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET MonsterMaker PROPERTY CXX_STANDARD 20)
endif()

# TODO: Add tests and install targets if needed.
