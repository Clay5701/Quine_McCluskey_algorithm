#include <iostream>
#include <unordered_set>
#include "../include/solution.h"
#include "../include/solution_log.h"
#include "../include/util.h"
#include "../include/minterm_intersection.h"

Solution::Solution(std::vector<BinaryMinterm>& history,  std::vector<int>& minterms) {
    process_history(history, minterms);
}

void Solution::process_history(std::vector<BinaryMinterm>& history, std::vector<int>& minterms) {
    while(true) {
        extract_essential_prime(history, minterms);

        bool check = row_dominance(history, minterms);
        if(!check) break;
    }

    extract_essential_prime(history, minterms);

    if(!minterms.empty()) {
        populate_non_essential(history, minterms);
    }
}

void Solution::extract_essential_prime(std::vector<BinaryMinterm>& history, std::vector<int>& minterms) {
    std::vector<MintermIntersect> intersect_vector;

    for(auto& term : history) {
        MintermIntersect new_intersect(term, minterms);
        intersect_vector.push_back(new_intersect);
    }

    std::vector<int> found_terms;
    for(int x : minterms) {
        if(std::find(found_terms.begin(), found_terms.end(), x) != found_terms.end()) {
            continue;
        }

        int terms_found = 0;
        int idx = 0;
        for(int i = 0; i < intersect_vector.size(); i++) {
            std::vector<int> temp_v = intersect_vector[i].intersection;
            if(std::find(temp_v.begin(), temp_v.end(), x) != temp_v.end()) {
                terms_found++;
                idx = i;
            }
        }
        if(terms_found == 1) {
            MintermIntersect temp = intersect_vector[idx];
            found_terms.insert(found_terms.end(), temp.minterm_reference.terms.begin(), temp.minterm_reference.terms.end());
            essential_pi.push_back(temp.minterm_reference.binary);
            history.erase(std::remove_if(history.begin(), history.end(), [&](const BinaryMinterm& term) {
                return term.binary == temp.minterm_reference.binary;
            }), history.end());
        }
    }
    VectorUtil::rm_vector(minterms, found_terms);
}

bool Solution::row_dominance(std::vector<BinaryMinterm>& history, std::vector<int>& minterms) {
    bool success = false;

    for(auto it = history.begin(); it != history.end(); ) {
        bool erased = false;
        std::vector<int> outer_common = VectorUtil::intersection(it->terms, minterms);

        for(auto& term : history) {
            if(it->binary == term.binary) continue;

            std::vector<int> inner_common = VectorUtil::intersection(term.terms, minterms);
            int common_between = VectorUtil::common_terms(outer_common, inner_common);
            bool cost_check = (it->cost >= term.cost);

            if((outer_common.size() < inner_common.size() && common_between == outer_common.size() && cost_check)) {
                it = history.erase(it);
                erased = true;
                success = true;
                break;
            }
        }
        if(!erased) {
            it++;
        }
    }
    return success;
}

void Solution::populate_non_essential(std::vector<BinaryMinterm>& history, std::vector<int>& minterms) {
    for(int i : minterms) {
        std::vector<std::string> n_essential;
        for(auto it = history.begin(); it != history.end(); ) {
            if(std::find(it->terms.begin(), it->terms.end(), i) != it->terms.end()) {
                n_essential.push_back(it->binary);
                it = history.erase(it);
            }
            else {
                it++;
            }
        }
        non_essential_pi.push_back(n_essential);
    }
}

void Solution::print() {
    SolutionLog::solution_log(essential_pi, non_essential_pi);
}