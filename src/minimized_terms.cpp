#include <algorithm>
#include "../include/minimized_terms.h"
#include "../include/minterm_collection.h"

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

    return combined;
}

std::vector<std::vector<BinaryMinterm>*> MinimizedTerms::calculate_minimized(std::vector<BinaryMinterm> minterms) {
    std::vector<BinaryMinterm>* new_minterms = new std::vector<BinaryMinterm>{combine_minterms(minterms)};
    std::vector<std::vector<BinaryMinterm>*> history;

    while(!new_minterms->empty()) {
        MintermCollection::print_minterms(*new_minterms);

        history.push_back(new_minterms);
        std::vector<BinaryMinterm>* next_minterms = new std::vector<BinaryMinterm>{combine_minterms(*new_minterms)};

        new_minterms = next_minterms;
    }

    rm_history_dup(history);
    std::reverse(history.begin(), history.end());

    return history;
}

void MinimizedTerms::rm_history_dup(std::vector<std::vector<BinaryMinterm>*>& history) {
    for(auto* v : history) {
        std::sort(v->begin(), v->end(), [](const BinaryMinterm& a, const BinaryMinterm& b) {
            return a.binary > b.binary;
        });

        auto it = std::unique(v->begin(), v->end(), [](const BinaryMinterm& a, const BinaryMinterm& b){
            return a.binary == b.binary;
        });

        v->erase(it, v->end());
    }
}

std::vector<std::vector<BinaryMinterm>*> MinimizedTerms::get_history() {
    return history;
}

MinimizedTerms::MinimizedTerms(std::vector<BinaryMinterm> minterms) {
    history = calculate_minimized(minterms);
}

MinimizedTerms::~MinimizedTerms() {
    for(auto* it : history) {
        delete it;
    }
}