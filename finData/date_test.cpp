/* Test Date class functionality */
#include <iostream>
#include "Date.h"

void testDate();

int main(){
  testDate();
}

void testDate(){
  std::string str = "02/10/2015";
  Date d1(str);
  Date d2(8, 25, 2015);
  Date d3(0, 45, -1); // d3 is wrong

  std::cout << "d1: " << d1 << std::endl;
  std::cout << "d2: " << d2 << std::endl;
  std::cout << "d3: " << d3 << std::endl;

  Date d4(12, 2, 1995);
  Date d5(8, 17, 2003);
  std::cout << d4 << "\t-\t" << d5 << "\t = " << Date::daysBetween(d4, d5) << std::endl;
}

