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
  Date(const Date &rhs) = default; // Shallow copy OK
  Date& operator= (const Date &rhs);
  bool  operator< (const Date &rhs) const;
  bool  operator> (const Date &rhs) const;
  bool  operator<=(const Date &rhs) const;
  bool  operator>=(const Date &rhs) const;
  bool  operator==(const Date &rhs) const;
  bool  operator!=(const Date &rhs) const;
  int   getMonth() const   { return month; }
  int   getDay() const     { return day; }
  int   getYear() const    { return year; }
  bool  isLeapYear() const { return !( (year - 1804)%4 ); }
  std::string toStr() const;
  // Determines the number of days between the two given dates, accounting for leap years etc
  static int daysBetween(const Date &start, const Date &end);
  static bool isLeapYear(int yr) { return !( (yr - 1804)%4 ); }
  
private:
  int month;
  int day;
  int year;
  static int daysInMonth[12];
  bool lessThan(const Date &rhs, bool orEqual) const;
};

#endif
