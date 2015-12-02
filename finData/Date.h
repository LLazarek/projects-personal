/* Date:
   Class for working with and comparing dates.
*/
#ifndef DATE_H
#define DATE_H

#include <string>
#include <iostream>

class Date{
  friend std::ostream& operator<<(std::ostream &out, const Date &rhs);
 public:
  Date(std::string in);
  Date(int mo, int d, int y);
  Date(Date &rhs) = default; // Shallow copy OK
  Date& operator=(Date &rhs);
  bool operator<(Date &rhs);
  bool operator>(Date &rhs);
  bool operator<=(Date &rhs);
  bool operator>=(Date &rhs);
  bool operator==(Date &rhs);
  int getMonth() { return month; }
  int getDay() { return day; }
  int getYear() { return year; }
  std::string toStr();

private:
  int month;
  int day;
  int year;
  bool lessThan(Date &rhs, bool orEqual);
};

#endif
