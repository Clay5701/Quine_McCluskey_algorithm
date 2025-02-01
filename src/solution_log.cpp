#include <iostream>
#include <vector>
#include <string>
#include "../include/solution_log.h"
#include "../include/util.h"

void SolutionLog::solution_log(
    std::vector<std::string>& essential_pi,
    std::vector<std::vector<std::string>>& non_essential_pi
) {
    std::vector<std::string> final_expression = StringUtil::convert(essential_pi);
    
    if(non_essential_pi.empty()) {
        for(int i = 0; i < final_expression.size(); i++) {
        std::cout << final_expression[i];

            if(i != final_expression.size() - 1) {
                std::cout << " + ";
            }
        }
    }
    
    else {
        print_non_essential(final_expression, non_essential_pi);
    }
}

void SolutionLog::print_non_essential(
        std::vector<std::string>& essential,
        std::vector<std::vector<std::string>> non_essential_pi
) {
    std::vector<int> idx(non_essential_pi.size(), 0);

    while(true) {
        for(size_t i = 0; i < essential.size(); i++) {
            std::cout << essential[i] << " + ";
        }
        for(size_t i = 0; i < non_essential_pi.size(); i++) {
            std::cout << StringUtil::convert_single(non_essential_pi[i][idx[i]]);
            if (i != non_essential_pi.size() - 1) {
                std::cout << " + ";
            }
        }
        std::cout << std::endl;

        size_t next = non_essential_pi.size();
        while(next > 0) {
            --next;
            idx[next]++;

            if(idx[next] < non_essential_pi[next].size()) {
                break;
            }

            idx[next] = 0;
            if(next == 0) return;
        }
    }
}