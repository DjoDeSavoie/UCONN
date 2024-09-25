// test out adapater functionalities: back_inserter vs inserter
#include <vector>
#include <unordered_set>
#include <set>
#include <iostream>
#include <chrono>

void Test1()
{
  // add some number of items
  const int NUM = 10000000;
  std::vector<int> vec;
  for(int i=0; i<NUM; ++i)
  {
    vec.push_back(i);
  }
  // now copy to a vector
  std::vector<int> vec2;
  std::chrono::steady_clock::time_point bt1 = std::chrono::steady_clock::now();

  // copy...

  std::chrono::steady_clock::time_point et1 = std::chrono::steady_clock::now();
  std::cout << "Num of items in copy: " << vec2.size() << std::endl;
  std::cout << "Elapsed time for copy1: " << std::chrono::duration_cast<std::chrono::microseconds>(et1 - bt1).count() << "[µs]" << std::endl;
  
  // now copy to an unordered set
  std::unordered_set<int> os1;
...
}

int main()
{
  Test1();
}
