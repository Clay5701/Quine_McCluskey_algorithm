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

    void simplify(MinimizedTerms& history, MintermCollection& minterms);
    std::vector<int> find_prime_terms(std::vector<int> history_terms);
    std::vector<int> find_history_terms(std::vector<BinaryMinterm>& history, std::vector<int>& found_terms);
    void process_prime_terms(
        std::vector<BinaryMinterm>& history,
        std::vector<int>& prime_terms,
        std::unordered_set<std::string>& found_binary,
        std::vector<int>& minterms,
        std::vector<int>& found_terms,
        std::vector<int>& history_terms
    );
    void process_non_prime_terms(
        std::vector<BinaryMinterm>& history,
        std::vector<int>& history_terms,
        std::vector<int>& minterms,
        std::unordered_set<std::string>& found_binary
    );
    std::vector<BinaryMinterm> gather_matching_terms(
        BinaryMinterm& item,
        std::vector<BinaryMinterm>& history,
        int max_terms,
        std::unordered_set<std::string>& found_binary
    );
    std::vector<std::string> extract_binary(
        std::vector<BinaryMinterm>& temp_v,
        std::unordered_set<std::string>& found_binary,
        std::vector<int>& minterms
    );
public:
    Solution(MinimizedTerms& history, MintermCollection& minterms);
    void set_essential(const std::vector<std::string>& essential);
    void append_non_essential(std::vector<std::string>& terms);
    void print();
};