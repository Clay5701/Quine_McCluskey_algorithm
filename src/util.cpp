#include <algorithm>
#include <set>
#include <unordered_set>
#include "../include/util.h"

void StringUtil::rm_string_dup(std::vector<std::string>& input) {
    std::sort(input.begin(), input.end(), [](const std::string& a, std::string& b) {
        return a > b;
    });

    auto it = std::unique(input.begin(), input.end(), [](const std::string& a, std::string& b){
        return a == b;
    });

    input.erase(it, input.end());
}

std::string StringUtil::convert_single(std::string& input) {
    std::string temp = "";
    int count = 0;
    for(char ch : input) {
        if(ch == '1') {
            temp = temp + (char)('A' + count);
        }
        else if(ch == '0') {
            temp = temp + (char)('A' + count) + '\'';
        }

        count++;
    }

    return temp;
}

std::vector<std::string> StringUtil::convert(std::vector<std::string>& input) {
    std::vector<std::string> output;

    for(std::string& item : input) {
        output.push_back(StringUtil::convert_single(item));
    }

    return output;
}

void VectorUtil::rm_vector(std::vector<int>& v1, const std::vector<int>& v2) {
    std::unordered_set<int> v2_set(v2.begin(), v2.end());

     v1.erase(std::remove_if(v1.begin(), v1.end(), [&](int x) {
        return v2_set.count(x);
    }), v1.end());
}

int VectorUtil::common_terms(const std::vector<int>& v1, const std::vector<int>& v2) {
    std::set<int> s1(v1.begin(), v1.end());
    std::set<int> s2(v2.begin(), v2.end());

    std::set<int> common;
    for(const int& item : s1) {
        if(s2.find(item) != s2.end()) {
            common.insert(item);
        }
    }

    return static_cast<int>(common.size());
}

int VectorUtil::max_common_terms(const std::vector<int>& v1, const std::vector<BinaryMinterm>& v2) {
    int term_count = 0;
    for(auto item : v2) {
        int new_term_count = common_terms(item.terms, v1);

        if(new_term_count > term_count) {
            term_count = new_term_count;
        }
    }

    return term_count;
}