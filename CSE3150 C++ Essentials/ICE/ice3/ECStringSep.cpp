// Starter code
#include <iostream>

using namespace std;

string ECStringSep(const string &str)
{
  string res;

  // checks if string is empty, returns if true 
  if (str.length() == 0)
  {
    return res;
  }

  res += str[0];
  for (int i = 1; i < str.length(); ++i)
  {
    res += ',';
    res += str[i];
  }

  return res;
}
