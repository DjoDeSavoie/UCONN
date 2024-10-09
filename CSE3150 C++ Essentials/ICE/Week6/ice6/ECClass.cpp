#include "ECClass.h"
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

// Class for class
ECClass ::ECClass()
{
}

void ECClass ::AddStudent(const ECStudent &s)
{
  listStu.push_back(s);
}

double ECClass::GetAveMedian() const
{
  vector<double> scores;
  for (auto &x : listStu)
  {
    scores.push_back(x.GetAve());
  }
  std::sort(scores.begin(), scores.end());

  int n = scores.size();
  if (n % 2 == 0)
  {
    return (scores[n / 2 - 1] + scores[n / 2]) / 2.0;
  }
  else
  {
    return scores[n / 2];
  }
}

std::string ECClass ::GetRankedStudentName(int n) const
{
  vector<pair<double, string>> scoreNamess;
  for (auto &x : listStu)
  {
    scoreNamess.push_back(std::make_pair(-1.0 * x.GetAve(), x.GetName()));
  }
  std::sort(scoreNamess.begin(), scoreNamess.end());
  return scoreNamess[n].second;
}