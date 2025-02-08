/**
 * @author Clayton Scharf
 * @brief Main entry point for the Quine-McCluskey minimization program.
 *
 * This program performs Boolean function minimization using the 
 * Quine-McCluskey algorithm. It takes user-inputted minterms, converts them 
 * to binary, groups them, and then simplifies the function.
 *
 * ## Execution Flow:
 * 1. The user enters minterms in decimal format.
 * 2. The program converts them to binary and groups them accordingly.
 * 3. The solution is computed using the Quine-McCluskey method.
 * 4. The minimized terms are printed.
 *
 * @note This program requires proper input formatting (space-separated integers).
 * @see MintermCollection, Solution, MinimizedTerms for implementation details.
 */

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

    Solution solution(history.get_history(), minterm_collection.get_minterms());
    solution.print();

    std::cin.get();
    return 0;
}