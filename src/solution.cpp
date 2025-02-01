#include <iostream>
#include <unordered_set>
#include "../include/solution.h"
#include "../include/solution_log.h"
#include "../include/util.h"

using namespace StringUtil;
using namespace VectorUtil;

void Solution::set_essential(const std::vector<std::string>& essential) {
    essential_pi = essential;
}
void Solution::append_non_essential(std::vector<std::string>& terms) {
    non_essential_pi.push_back(terms);
}
void Solution::print() {
    SolutionLog::solution_log(essential_pi, non_essential_pi);
}

void Solution::simplify(MinimizedTerms& minimized_terms, MintermCollection& minterm_collection) {
    auto history = minimized_terms.get_history();
    std::vector<BinaryMinterm> binary_minterms = minterm_collection.get_binary_minterms();
    std::vector<int> minterms = minterm_collection.get_minterms();

    std::vector<int> found_terms;
    std::unordered_set<std::string> found_binary;
    int history_idx = 0;

    if(history.empty()) {
        for(auto item : binary_minterms) {
            essential_pi.push_back(item.binary);
        }
        return;
    }

    while(!minterms.empty() && history_idx != history.size()) {
        std::vector<int> history_terms = find_history_terms(*history[history_idx], found_terms);

        std::vector<int> prime_terms = find_prime_terms(history_terms);

        process_prime_terms(*history[history_idx], prime_terms, found_binary, minterms, found_terms, history_terms);

        process_non_prime_terms(*history[history_idx], history_terms, minterms, found_binary);

        history_idx++;
    }

    if(!minterms.empty()) {
        for(auto item : binary_minterms) {
            if(common_terms(item.terms, minterms)) {
                essential_pi.push_back(item.binary);
                rm_vector(minterms, item.terms);
            }
        }
    }

    rm_string_dup(essential_pi);
}

std::vector<int> Solution::find_prime_terms(std::vector<int> history_terms) {
    std::vector<int> prime_terms;

    for(int i = 0; i < history_terms.size(); i++) {
        int count = 0;

        for(int j = 0; j < history_terms.size(); j++) {
            if(history_terms[i] == history_terms[j]) {
                count++;
            }
        }

        if(count == 1) {
            prime_terms.push_back(history_terms[i]);
        }
    }

    return prime_terms;
}

std::vector<int> Solution::find_history_terms(std::vector<BinaryMinterm>& history, std::vector<int>& found_terms) {
    std::vector<int> history_terms;

    for(const auto& item : history) {
        history_terms.insert(history_terms.end(), item.terms.begin(), item.terms.end());
    }

    rm_vector(history_terms, found_terms);

    return history_terms;
}

void Solution::process_prime_terms(
    std::vector<BinaryMinterm>& history,
    std::vector<int>& prime_terms,
    std::unordered_set<std::string>& found_binary,
    std::vector<int>& minterms,
    std::vector<int>& found_terms,
    std::vector<int>& history_terms
) {
    for(const auto& item : history) {
        if(common_terms(item.terms, prime_terms)) {
            essential_pi.push_back(item.binary);
            found_binary.insert(item.binary);
            found_terms.insert(found_terms.end(), item.terms.begin(), item.terms.end());
            rm_vector(minterms, item.terms);
        }

        if(prime_terms.empty()) {
            break;
        }
    }
    rm_vector(history_terms, found_terms);
}

void Solution::process_non_prime_terms(
    std::vector<BinaryMinterm>& history,
    std::vector<int>& history_terms,
    std::vector<int>& minterms,
    std::unordered_set<std::string>& found_binary
) {
    while(!history_terms.empty()) {
        int max_terms = max_common_terms(history_terms, history);

        for(auto item : history) {
            if(common_terms(item.terms, history_terms) != max_terms) {
                continue;
            }
            std::vector<BinaryMinterm> temp_v = gather_matching_terms(item, history, max_terms, found_binary);
            max_terms = max_common_terms(history_terms, history);

            std::vector<std::string> non_essential = extract_binary(temp_v, found_binary, minterms);

            if(non_essential.size() == 1) {
                essential_pi.push_back(non_essential[0]);
            }
            else {
                non_essential_pi.push_back(non_essential);;
            }

            rm_vector(history_terms, item.terms);
        }
    }
}

std::vector<BinaryMinterm> Solution::gather_matching_terms(
    BinaryMinterm& item,
    std::vector<BinaryMinterm>& history,
    int max_terms,
    std::unordered_set<std::string>& found_binary
) {
    std::vector<BinaryMinterm> temp_v;
    temp_v.push_back(item);

    for(auto item_2 : history) {
        if(common_terms(item_2.terms, item.terms) == max_terms && item_2.binary != item.binary) {
            if(found_binary.find(item_2.binary) == found_binary.end()) {
                temp_v.push_back(item_2);
            }
        }
    }

    return temp_v;
}

std::vector<std::string> Solution::extract_binary(
    std::vector<BinaryMinterm>& temp_v,
    std::unordered_set<std::string>& found_binary,
    std::vector<int>& minterms
) {
    std::vector<std::string> non_essential;
    for(BinaryMinterm& term : temp_v) {
        non_essential.push_back(term.binary);
        found_binary.insert(term.binary);
        rm_vector(minterms, term.terms);
    }
    return non_essential;
}

Solution::Solution(MinimizedTerms& history, MintermCollection& minterms) {
    simplify(history, minterms);
}