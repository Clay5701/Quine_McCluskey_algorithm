/**
 * @brief Defines the `MintermCollection` class, which manages user-inputted minterms
 *        and converts them to binary representations.
 *
 * The `MintermCollection` class stores user-entered minterms in a vector and processes 
 * them into `BinaryMinterm` representations. It provides methods for input, conversion, retrieval, 
 * and formatted output of minterms.
 *
 * @note See minterm_collection.cpp for implementation.
 */

#pragma once
#include <vector>
#include "./binary_minterm.h"

/**
 * @class MintermCollection
 * @brief Manages the collection of minterms and their `BinaryMinterm` representations.
 */
class MintermCollection {
private:
    std::vector<int> minterms;                  ///< Stores user-inputted decimal minterms.
    std::vector<BinaryMinterm> binary_minterms; ///< Stores converted binary representations.
public:
    /**
     * @brief Accepts user input and stores it in the `minterms` vector.
     */
    void input_to_minterms();

    /**
     * @brief Converts decimal minterms to `BinaryMinterm` representation and groups them accordingly.
     * 
     * Each converted minterm is stored in the `binary_minterms` vector.
     */
    void decimal_to_binary_conv();

    /**
     * @brief Retrieves the binary minterms.
     * @return A vector of `BinaryMinterm` objects representing the binary minterms.
     */
    std::vector<BinaryMinterm> get_binary_minterms();

    /**
     * @brief Retrieves the decimal minterms.
     * @return A vector of integers representing the original user-inputted minterms.
     */
    std::vector<int> get_minterms();

    /**
     * @brief Prints a formatted representation of the binary minterms.
     * 
     * This method is static because it is used outside `MintermCollection` in minimized_terms.cpp.
     * 
     * @param binary_minterms: A vector of `BinaryMinterm` objects to be printed.
     */
    static void print_minterms(const std::vector<BinaryMinterm>& binary_minterms);

    static void calculate_cost(std::vector<BinaryMinterm>& binary_minterms, int max_length);
};