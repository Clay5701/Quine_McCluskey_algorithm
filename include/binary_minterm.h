/**
 * @brief Defines the `BinaryMinterm` struct for representing minterms in the Quine-McCluskey method.
 *
 * The `BinaryMinterm` struct stores a minterm’s binary representation, the decimal terms it represents,
 * and its corresponding group.
 */

#pragma once
#include <vector>
#include <string>

/**
 * @struct BinaryMinterm
 * @brief Represents a minterm with its binary form, associated decimal values, and grouping information.
 *
 * The `BinaryMinterm` struct is used to store and manipulate minterms in the Quine-McCluskey method.
 * - `binary`: A string representing the minterm in binary form (e.g., `"01-1"`). Dashes (`-`) are allowed
 *   to indicate "don't-care" bits.
 * - `terms`: A vector containing the decimal values represented by the binary string. 
 *   For example, `"01-1"` corresponds to `{5, 7}`.
 * - `group`: Initially set to the number of `1`s in the `binary` string, but as minterms are combined,
 *   it takes the smallest group number of the combined terms.
 */
struct BinaryMinterm {
    std::vector<int> terms; ///< The possible decimal values represented by the binary stored in `binary`.
    std::string binary;     ///< The binary representation of the minterm.
    int group;              ///< The QM group this minterm belongs to.
    int cost;
};