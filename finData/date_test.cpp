/* Test Date class functionality */
#include <iostream>
#include "Date.h"

void testDate();

int main(){
  testDate();
}

void testDate(){
  string str = "08/22/2015";
  Date d1(str);
  Date d2(8, 25, 2015);
  Date d3(0, 45, -1); // d3 is wrong

  std::cout << "d1: " << d1.getMonth() << "/" << d1.getDay() << d1.getYear() << std::endl;
  std::cout << "d2: " << d2.getMonth() << "/" << d2.getDay() << d2.getYear() << std::endl;
  std::cout << "d3: " << d3.getMonth() << "/" << d3.getDay() << d3.getYear() << std::endl;
}
