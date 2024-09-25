#include <vector>
#include <iostream>
using namespace std;

// hack!
#include "ECMergeSimilarItems.cpp"

template<class T>
void ASSERT_EQ(T x, T y)
{
  if( x == y )
  {
    cout << "Test passed: equal: " << x << "  " << y << endl;
  }
  else
  {
    cout << "Test FAILED: equal: " << x << "  " << y << endl;
  }
}

// tests
void Test1()
{
  vector<pair<int,int> > items1, items2, ret;
  items1.push_back(make_pair(1,1));
  items1.push_back(make_pair(4,5));
  items1.push_back(make_pair(3,8));
  items2.push_back(make_pair(3,1));
  items2.push_back(make_pair(1,5));
  ECMergeSimilarItems(items1, items2, ret);
  ASSERT_EQ( (int)ret.size(), 3 );
  ASSERT_EQ( ret[0].first, 1);
  ASSERT_EQ( ret[0].second, 6);
  ASSERT_EQ( ret[1].first, 3);
  ASSERT_EQ( ret[1].second, 9);
  ASSERT_EQ( ret[2].first, 4);
  ASSERT_EQ( ret[2].second, 5);
}

void Test2()
{
  vector<pair<char,double> > items1, items2, ret;
  items1.push_back(make_pair('c',1));
  items1.push_back(make_pair('a',5));
  items1.push_back(make_pair('d',8));
  items2.push_back(make_pair('c',1));
  items2.push_back(make_pair('b',4));
  ECMergeSimilarItems(items1, items2, ret);
  ASSERT_EQ( (int)ret.size(), 4 );
  ASSERT_EQ( ret[0].first, 'a');
  ASSERT_EQ( ret[0].second, 5.0);
  ASSERT_EQ( ret[1].first, 'b');
  ASSERT_EQ( ret[1].second, 4.0);
  ASSERT_EQ( ret[2].first, 'c');
  ASSERT_EQ( ret[2].second, 2.0);
  ASSERT_EQ( ret[3].first, 'd');
  ASSERT_EQ( ret[3].second, 8.0);
}
int main()
{
  Test1();
  Test2();
}
