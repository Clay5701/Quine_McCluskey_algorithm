#pragma once
#include <vector>
#include "./binary_minterm.h"

class MintermCollection {
private:
    std::vector<int> minterms;
    std::vector<BinaryMinterm> binary_minterms;
public:
    void input_to_minterms();
    void decimal_to_binary_conv();
    std::vector<BinaryMinterm> get_binary_minterms();
    std::vector<int> get_minterms();
    static void print_minterms(const std::vector<BinaryMinterm>& binary_minterms);
};