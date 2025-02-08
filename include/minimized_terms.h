/**
 * @brief Defines the `MinimizedTerms` class, which minimizes a `BinaryMinterm` vector following the
 * Quine McCluskey method.
 *
 * The `MinimizedTerms` class stores a vector that follows the history of `BinarMinterm` minimization.
 * Each cycle of minimization is stored on the heap and a pointer to its location is stored in `history`.
 * This class provides various methods to manipulate `BinaryMinterm` vectors and the `history` member variable.
 * See method definitions below for more information.
 *
 * @note See minimized_terms.cpp for implementation.
 */

#pragma once
#include "./binary_minterm.h"

class MinimizedTerms {
private:
    std::vector<BinaryMinterm> history;

    /**
     * @brief Combines a `BinaryMinterm` vector following the Quine McCluskey method.
     * 
     * Compares each `BinaryMinterm` with each `BinaryMinterm` exactly one group higher than it.
     * If they differ by only one bit, they are combined. This combined term is pushed to a new vector. 
     * 
     * @param minterms: A const reference to a `BinaryMinterm` vector.
     * 
     * @return A new combined `BinaryMinterm` vector.
     */
    std::vector<BinaryMinterm> combine_minterms(const std::vector<BinaryMinterm>& minterms);

    /**
     * @brief Combines a `BinaryMinterm` vector terms MinimizedTerms::using combine_minterms until no futher combinations can
     * be made.
     * 
     * Each time MinimizedTerms::combine_minterms is called, the resulting `BinaryMinterm` vector is stored on the heap. 
     * A pointer to this new vector is stored in the `history` member. Subsequent calls of MinimizedTerms::combine_minterms() use
     * the previous combined result.
     * 
     * @param minterms: A `BinaryMinterm` vector.
     * 
     * @return A vector holding pointers to other `BinaryMinterm` vectors.
     */
    void calculate_minimized(std::vector<BinaryMinterm> minterms);

    /**
     * @brief Removes duplicate `BinaryMinterm` elements from each `BinaryMinterm` vector stored in `history`.
     * 
     * Iterates through `history` to access each stored `BinaryMinterm` vector. Each of these vectors is subsequently
     * sorted by `binary` and elements with duplicate `binary` are eliminated. Removing duplicat elements allows for
     * much easier processing later.
     * 
     * @param history: A vector holding pointers to other `BinaryMinterm` vectors.
     * 
     * @return A vector holding pointers to other `BinaryMinterm` vectors.
     */
    void rm_history_dup(std::vector<std::vector<BinaryMinterm>>& expanded_history);
    void rm_history_redundancies(std::vector<std::vector<BinaryMinterm>>& expanded_history);
public:
    MinimizedTerms(std::vector<BinaryMinterm> minterms);

    std::vector<BinaryMinterm> get_history();
};