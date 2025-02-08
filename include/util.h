#pragma once
#include <vector>
#include <string>
#include <unordered_set>
#include "./binary_minterm.h"

namespace StringUtil {
    void rm_string_dup(std::vector<std::string>& input);
    std::string convert_single(std::string& input);
    std::vector<std::string> convert(std::vector<std::string>& input);
}

namespace VectorUtil {
    void rm_vector(std::vector<int>& v1, const std::vector<int>& v2);
    int common_terms(const std::vector<int>& v1, const std::vector<int>& v2);
    std::vector<int> intersection(const std::vector<int>& v1, const std::vector<int>& v2);
    int max_common_terms(const std::vector<int>& v1, const std::vector<BinaryMinterm>& v2);
}