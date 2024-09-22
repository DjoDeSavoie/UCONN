#include <string>
#include <gtest/gtest.h> // Include Google Test header
using namespace std;

void foo(int n)
{
  if (n < 0)
  {
    throw string("NEGATIVE");
  }
  else if (n == 0)
  {
    throw string("ZERO");
  }
}

string bar(int n)
{
  try
  {
    foo(n);
  }
  catch (const string& ex)
  {
    return ex;
  }
  return "OK";
}

TEST(ECExceptionTest, TestCases)
{
  EXPECT_EQ(bar(-1), "NEGATIVE");
  EXPECT_EQ(bar(3), "OK");
  EXPECT_EQ(bar(0), "ZERO");
}

int main(int argc, char **argv)
{
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
