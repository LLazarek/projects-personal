/* Test Date class functionality */
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
  
}
