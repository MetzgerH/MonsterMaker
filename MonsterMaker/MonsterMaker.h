#pragma once

#include <iostream>
#include <fstream>
#include <filesystem>

#include "monster.h"
#include "strManip.h"

Monster importMonster(std::fstream* input);
void exportToCSV(std::fstream* output, Monster* monster);
Monster importFromCSV(std::fstream* intput);
