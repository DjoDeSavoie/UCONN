// Created by Y. Wu, Jan 31, 2023
// Merge lists (of any STL container type) into a single sorted list (of any STL container type)
// Duplicates allowed unless the output doesn't take duplicates (e.g., a map)
// Note: you should make your code as flexible as possible: you should allow all kinds of outputs: vector, set, etc 
// Make your code short: at most 10 lines of code (LOC)

#include <algorithm> // For std::merge
#include <iterator>  // For std::back_inserter
#include <vector>

// Function template to merge two containers into a single sorted container
template <typename InputIt1, typename InputIt2, typename OutputIt>
OutputIt ECMergeContainers(InputIt1 first1, InputIt1 last1, InputIt2 first2, InputIt2 last2, OutputIt d_first) {
    return std::merge(first1, last1, first2, last2, d_first);
}

// Explicit template instantiation for common types
template std::vector<int>::iterator ECMergeContainers<std::vector<int>::iterator, std::vector<int>::iterator, std::vector<int>::iterator>(
    std::vector<int>::iterator, std::vector<int>::iterator, std::vector<int>::iterator, std::vector<int>::iterator, std::vector<int>::iterator
);
