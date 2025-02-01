#include <iostream>
#include "../include/binary_minterm.h"
#include "../include/solution.h"
#include "../include/minterm_collection.h"
#include "../include/minimized_terms.h"

int main() {
    MintermCollection minterm_collection;

    minterm_collection.input_to_minterms();
    minterm_collection.decimal_to_binary_conv();
    MintermCollection::print_minterms(minterm_collection.get_binary_minterms());

    MinimizedTerms history(minterm_collection.get_binary_minterms());

    Solution solution(history, minterm_collection);
    solution.print();

    std::cin.get();
    return 0;
}