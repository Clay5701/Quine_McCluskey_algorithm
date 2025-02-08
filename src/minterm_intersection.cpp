#include <vector>
#include "../include/binary_minterm.h"
#include "../include/minterm_intersection.h"
#include "../include/util.h"

MintermIntersect::MintermIntersect(BinaryMinterm& history_term, const std::vector<int>& minterms) {
    intersection = VectorUtil::intersection(history_term.terms, minterms);
    minterm_reference = history_term;
}