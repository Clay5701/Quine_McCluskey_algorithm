#pragma once
#include <vector>
#include <string>
#include <unordered_set>
#include "./minterm_collection.h"
#include "./minimized_terms.h"

class Solution {
private:
    std::vector<std::string> essential_pi;
    std::vector<std::vector<std::string>> non_essential_pi;

    void process_history(std::vector<BinaryMinterm>& history,  std::vector<int>& minterms);
    void extract_essential_prime(std::vector<BinaryMinterm>& history, std::vector<int>& minterms);
    void populate_non_essential(std::vector<BinaryMinterm>& history, std::vector<int>& minterms);
    bool row_dominance(std::vector<BinaryMinterm>& history, std::vector<int>& minterms);
public:
    Solution(std::vector<BinaryMinterm>& history,  std::vector<int>& minterms);
    void print();
};