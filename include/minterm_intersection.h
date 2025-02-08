#pragma once
#include <vector>
#include "./binary_minterm.h"

class MintermIntersect {
public:
    std::vector<int> intersection;
    BinaryMinterm minterm_reference;

    MintermIntersect(BinaryMinterm& history_term, const std::vector<int>& minterms);
};