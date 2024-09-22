// Can you change the code to use buffer overflow to
// change the flow control of the code?
#include <iostream>
#include <chrono>
#include <thread>
using namespace std;

int main();

void foo()
{
  cout << "Enter foo\n";
  long arr[10];
  int i = 5;
  arr[i + 3] = 12345;

#if 0
  cout << "Mem right abobe arr: is:\n";
  for (int j = 0; j < 6; ++j)
  {
    cout << arr[10 + j] << endl;
  }
  cout << "address of main: " << (long)main << endl;
#endif
  // hack:
  arr[10 + 2] = (long)main;

  // sleep for a while
  std::chrono::milliseconds timespan(1000); // or whatever
  std::this_thread::sleep_for(timespan);
  cout << "Exit foo\n";
}

int main()
{
  foo();
  return 0;
}
