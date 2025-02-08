/**
 * @brief Implements the MintermCollection class, which manages user-inputted minterms
 *        and converts them to binary representations.
 *
 * The `MintermCollection` class stores user-entered minterms in a vector and processes 
 * them into binary representations. It provides methods for input, conversion, retrieval, 
 * and formatted output of minterms.
 *
 * @see minterm_collection.h for class definitions.
 */

#include <iostream>
#include <sstream>
#include <algorithm>
#include <iomanip>
#include "../include/minterm_collection.h"

void MintermCollection::input_to_minterms() {
    std::string input;

    std::cout << "Enter SOP minterms in decimal (Enter each term followed by a space. Only press ENTER once all terms are typed): " << std::endl;
    std::getline(std::cin, input);

    std::istringstream iss(input);
    int number;

    while(iss >> number) {
        minterms.push_back(number);
    }

    std::sort(minterms.begin(), minterms.end());
}

void MintermCollection::decimal_to_binary_conv() {
    int max_len = 0;

    for(int value : minterms) {
        struct BinaryMinterm temp;
        temp.terms.push_back(value);
        int group = 0;

        if(value == 0) {
            temp.binary = "0";
            temp.group = group;
            binary_minterms.push_back(temp);
            continue;
        }

        std::string binary = "";

        while(value > 0) {
            int remainder = value % 2;
            if(remainder == 1) {
                group++;
            }

            binary = std::to_string(remainder) + binary;
            value /= 2;
        }
        temp.group = group;

        temp.binary = binary;

        max_len = std::max(max_len, (int)binary.length());

        binary_minterms.push_back(temp);
    }

    for(auto& b : binary_minterms) {
        while(b.binary.length() != max_len) {
            b.binary = "0" + b.binary;
        }
    }

    std::sort(binary_minterms.begin(), binary_minterms.end(), [](const BinaryMinterm& a, const BinaryMinterm& b) {
        return a.group < b.group;
    });

    calculate_cost(binary_minterms, max_len);
}

void MintermCollection::calculate_cost(std::vector<BinaryMinterm>& binary_minterms, int max_length) {
    for(auto& term : binary_minterms) {
        int dash_count = 0;
        int zero_count = 0;
        for(char ch : term.binary) {
            if(ch == '-') dash_count++;
            if(ch == '0') zero_count++;
        }
        term.dash_count = dash_count;
        term.cost = max_length + 1 + zero_count - dash_count;
    }
}

std::vector<BinaryMinterm> MintermCollection::get_binary_minterms() {
    return binary_minterms;
}

std::vector<int> MintermCollection::get_minterms() {
    return minterms;
}

void MintermCollection::print_minterms(const std::vector<BinaryMinterm>& binary_minterms) {
    std::cout   << "|--------------|------------------------|------------------|" << std::endl
	            << "| Group        | Decimal                | Binary           |" << std::endl
	            << "|--------------|------------------------|------------------|" << std::endl;

    for(auto& minterm : binary_minterms) {
        std::cout   << "| " << std::left << std::setw(12) << minterm.group
                    << " | ";

        size_t width = 0;     
        for (const auto& term : minterm.terms) {
            std::cout << term << " ";
            width += std::to_string(term).length() + 1;
        }

        std::cout << std::setw(22 - width) << " ";
        std::cout   << " | " << std::left << std::setw(16) << minterm.binary
                    << " |" << std::endl;
    }
    std::cout << "|--------------|------------------------|------------------|" << std::endl;
}