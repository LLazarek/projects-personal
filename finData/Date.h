/* Date:
   Class for working with and comparing dates.
*/
#ifndef DATE_H
#DEF DATE_H
#include <string>

class Date{
 private:
  int month;
  int day;
  int year;

 public:
  Date(string in);
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
  string toStr();
}

#endif
