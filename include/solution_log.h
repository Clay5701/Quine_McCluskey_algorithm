#pragma once
#include <vector>
#include <string>

class SolutionLog {
private:
    
public:
    static void solution_log(
        std::vector<std::string>& essential_pi,
        std::vector<std::vector<std::string>>& non_essential_pi
    );
    static void print_non_essential(
        std::vector<std::string>& essential,
        std::vector<std::vector<std::string>> non_essential_pi
    );
};