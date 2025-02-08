#include <iostream>
#include <algorithm>
#include <unordered_set>
#include "../include/minimized_terms.h"
#include "../include/minterm_collection.h"
#include "../include/util.h"

std::vector<BinaryMinterm> MinimizedTerms::combine_minterms(const std::vector<BinaryMinterm>& minterms) {
    std::vector<BinaryMinterm> combined;

    for(int i = 0; i < minterms.size(); i++) {
        for(int j = i + 1; j < minterms.size(); j++) {
            if(minterms[i].group + 1 == minterms[j].group) {
                int diff = 0;
                std::string comb_binary;

                for(int k = 0; k < minterms[i].binary.length(); k++) {
                    if(minterms[i].binary[k] != minterms[j].binary[k]) {
                        diff++;
                        comb_binary += "-";
                    }
                    else {
                        comb_binary += minterms[i].binary[k];
                    }
                }

                if(diff == 1) {
                    BinaryMinterm new_minterm;
                    new_minterm.binary = comb_binary;
                    new_minterm.group = minterms[i].group;

                    std::vector<int> combined_terms(minterms[i].terms);  
                    combined_terms.insert(combined_terms.end(), minterms[j].terms.begin(), minterms[j].terms.end());
                    new_minterm.terms = combined_terms;

                    combined.push_back(new_minterm);
                }
            }
        }
    }

    if(!combined.empty()) {
        MintermCollection::calculate_cost(combined, static_cast<int>(combined[0].binary.size()));
    }

    return combined;
}

void MinimizedTerms::calculate_minimized(std::vector<BinaryMinterm> minterms) {
    std::vector<BinaryMinterm> new_minterms = std::vector<BinaryMinterm>{combine_minterms(minterms)};
    std::vector<std::vector<BinaryMinterm>> expanded_history;
    expanded_history.push_back(minterms);

    while(!new_minterms.empty()) {
        MintermCollection::print_minterms(new_minterms);

        expanded_history.push_back(new_minterms);
        new_minterms = std::vector<BinaryMinterm>{combine_minterms(new_minterms)};
    }

    rm_history_dup(expanded_history);
    std::reverse(expanded_history.begin(), expanded_history.end());
    rm_history_redundancies(expanded_history);

    for(const auto& v : expanded_history) {
        history.insert(history.end(), v.begin(), v.end());
    }
}

void MinimizedTerms::rm_history_dup(std::vector<std::vector<BinaryMinterm>>& expanded_history) {
    for(auto& v : expanded_history) {
        std::sort(v.begin(), v.end(), [](const BinaryMinterm& a, const BinaryMinterm& b) {
            return a.binary > b.binary;
        });

        auto it = std::unique(v.begin(), v.end(), [](const BinaryMinterm& a, const BinaryMinterm& b){
            return a.binary == b.binary;
        });

        v.erase(it, v.end());
    }
}

void MinimizedTerms::rm_history_redundancies(std::vector<std::vector<BinaryMinterm>>& expanded_history) {
    std::unordered_set<int> used_terms;

    for(auto& v : expanded_history) {
        std::unordered_set<int> temp_used;
        for(auto it = v.begin(); it != v.end(); ) {
            if(VectorUtil::common_terms(it->terms, std::vector<int>(used_terms.begin(), used_terms.end())) >= it->terms.size()) {
                it = v.erase(it);
            }
            else {
                temp_used.insert(it->terms.begin(), it->terms.end());
                it++;
            }
        }
        used_terms.insert(temp_used.begin(), temp_used.end());
    }
}

std::vector<BinaryMinterm> MinimizedTerms::get_history() {
    return history;
}

MinimizedTerms::MinimizedTerms(std::vector<BinaryMinterm> minterms) {
   calculate_minimized(minterms);
}