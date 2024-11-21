//
//  ECVirtualMemory.h
//  
//
//  Created by Yufeng Wu on 8/30/23.
//  Port the page replacement code to the ECVirtualMemory class 

#ifndef ECVirtualMemory_h
#define ECVirtualMemory_h

#include <iostream>
#include <set>
#include <vector>
#include <map>
#include <string>
#include <list>
#include <unordered_map>
#include <unordered_set>

//*****************************************************************************
// Virtual memory: consists of memory pages and a main memory with limited capacity
// Page: represented by an integer; main memory can hold up to K pages
// Page replacement: when the main memory reaches its limit (i.e., having K pages) 
// and a new page (not currently in memory) is to be add, 
// then need to swap out one current page to make room for this new page
// This class: use LRU algorithm

class ECVirtualMemory
{
public:
    // Constructor: Initialize with the maximum number of pages in main memory
    ECVirtualMemory(int capacity);

    // Access a page in memory using the LRU algorithm
    void AccessPage(int page);

    // Run the Optimal (OPT) page replacement algorithm and return the number of page faults
    int RunOpt();

    // Return the number of pages currently in main memory
    int GetNumPagesInMainMemory() const;

    // Return the number of page faults so far (for LRU algorithm)
    int GetNumPageFaults() const;

private:
    int capacity; // Maximum number of pages in main memory
    int page_faults_lru; // Number of page faults using LRU

    std::list<int> lru_cache; // List to maintain LRU order (front = most recently used)
    std::unordered_map<int, std::list<int>::iterator> page_map; // Map from page to its iterator in lru_cache

    std::vector<int> accessed_pages; // All accessed pages for the OPT algorithm
};

#endif /* ECVirtualMemory_h */
