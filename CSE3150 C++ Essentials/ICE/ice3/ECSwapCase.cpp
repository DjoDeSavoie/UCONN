// Starter code
#include <string>
#include <iostream>
using namespace std;

std::string ECSwapCase(const std::string str)
{
  std::string res; // res is empty string. std can be removing by initializing namespace
  for (int i = 0; i < str.length(); ++i)
  {
    char ch = str[i];

    // change ch to proper case
    if (std::islower(ch))
    {
      ch = std::toupper(ch);
    }
    else
    {
      ch = std::tolower(ch);
    }

    res += ch;
  }
  return res;
}
