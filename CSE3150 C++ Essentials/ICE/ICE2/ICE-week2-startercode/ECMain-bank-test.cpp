#include "ECBank1.h"
#include "ECBank2.h"
#include <iostream>

int main()
{
  using namespace BankofAmerica;
  //using namespace CitiBank;
  std::cout << "balance: " << balance << std::endl;
  if( BankofAmerica::IsLucky(balance) )
  {
    std::cout << "Lucky!\n";
  }
}

