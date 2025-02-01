#pragma once
#include <vector>
#include <string>

struct BinaryMinterm {
    std::vector<int> terms;
    std::string binary;
    int group;
};