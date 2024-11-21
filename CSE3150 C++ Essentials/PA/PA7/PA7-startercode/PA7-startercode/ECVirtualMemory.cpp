//
//  ECVirtualMemory.cpp
//  
//
//  Created by Yufeng Wu on 8/30/23.
//  Implement popular page replacement algorithms

#include "ECVirtualMemory.h"
#include <algorithm>
#include <list>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <iostream>
using namespace std;


//*****************************************************************************
// Virtual memory: consists of memory pages and a main memory with limited capacity
// Page: represented by an integer; main memory can hold up to K pages
// Page replacement: when the main memory reaches its limit (i.e., having K pages) 
// and a new page (not currently in memory) is to be add, 
// then need to swap out one current page to make room for this new page
// This class: use OPT or LRU algorithm

// Your code here

// Constructor: Initialize with the maximum number of pages in main memory
ECVirtualMemory::ECVirtualMemory(int K) : capacity(K), page_faults_lru(0) {
    // Initialize any additional members if necessary
}

// Access a page in memory using the LRU algorithm
void ECVirtualMemory::AccessPage(int page) {
    accessed_pages.push_back(page); // Record the access for OPT

    // Check if the page is already in main memory
    auto it = page_map.find(page);
    if (it != page_map.end()) {
        // Page hit: Move the page to the front of the LRU cache
        lru_cache.erase(it->second);
        lru_cache.push_front(page);
        page_map[page] = lru_cache.begin();
    } else {
        // Page fault occurs
        page_faults_lru++;

        if (lru_cache.size() == capacity) {
            // Main memory is full: Evict the least recently used page (back of the list)
            int lru_page = lru_cache.back();
            lru_cache.pop_back();
            page_map.erase(lru_page);
        }

        // Insert the new page at the front of the LRU cache
        lru_cache.push_front(page);
        page_map[page] = lru_cache.begin();
    }
}

// Run the Optimal (OPT) page replacement algorithm and return the number of page faults
int ECVirtualMemory::RunOpt() {
    int page_faults_opt = 0;
    unordered_set<int> current_pages; // Pages currently in main memory
    unordered_map<int, vector<int>> future_uses_map; // Future access positions for each page

    // Preprocess: Map each page to all its future access positions
    for (int i = 0; i < accessed_pages.size(); ++i) {
        future_uses_map[accessed_pages[i]].push_back(i);
    }

    // Iterate through each page access
    for (int i = 0; i < accessed_pages.size(); ++i) {
        int page = accessed_pages[i];

        // Remove the current access position from future uses
        future_uses_map[page].erase(future_uses_map[page].begin());

        if (current_pages.find(page) != current_pages.end()) {
            // Page is already in main memory: No action needed
            continue;
        }

        // Page fault occurs
        page_faults_opt++;

        if (current_pages.size() < capacity) {
            // There is space in main memory: Insert the page
            current_pages.insert(page);
        } else {
            // Need to evict a page using the OPT strategy
            int page_to_evict = -1;
            int farthest_use = -1;

            for (const auto& current_page : current_pages) {
                if (future_uses_map[current_page].empty()) {
                    // This page is not used again: Best candidate for eviction
                    page_to_evict = current_page;
                    break;
                } else {
                    // Get the next use position
                    int next_use = future_uses_map[current_page].front();
                    if (next_use > farthest_use) {
                        farthest_use = next_use;
                        page_to_evict = current_page;
                    }
                }
            }

            // Evict the selected page
            if (page_to_evict != -1) {
                current_pages.erase(page_to_evict);
            }

            // Insert the new page
            current_pages.insert(page);
        }
    }

    return page_faults_opt;
}

// Return the number of pages currently in main memory
int ECVirtualMemory::GetNumPagesInMainMemory() const {
    return lru_cache.size();
}

// Return the number of page faults so far (for LRU algorithm)
int ECVirtualMemory::GetNumPageFaults() const {
    return page_faults_lru;
}