#pragma once
#include "./binary_minterm.h"

class MinimizedTerms {
private:
    std::vector<std::vector<BinaryMinterm>*> history;

    std::vector<BinaryMinterm> combine_minterms(const std::vector<BinaryMinterm>& minterms);
    std::vector<std::vector<BinaryMinterm>*> calculate_minimized(std::vector<BinaryMinterm> minterms);
    void rm_history_dup(std::vector<std::vector<BinaryMinterm>*>& history);
public:
    MinimizedTerms(std::vector<BinaryMinterm> minterms);
    ~MinimizedTerms();

    std::vector<std::vector<BinaryMinterm>*> get_history();
};