// Created by Y. Wu, Feb 16, 2023
// You are given two containers, src and dest (with the same data type); you want to copy all items in src to dest (in the order of their appearance in src; of course, if dest has its own ordering like a set, you would just go with that container's ordering). After copying, dest should contain exactly the same list of items in src. You need to support all kinds of containers and data types.

#include <algorithm>

template <class T1, class T2>
void ECCopy(const T1 &src, T2 &dest)
{
    dest.clear();
    std::copy(src.begin(), src.end(), std::inserter(dest, dest.end()));
}
