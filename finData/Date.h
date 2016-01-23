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
  // Default Constructor: creates a Date with date "1/1/2000"
  Date() : month(1), day(1), year(2000) {}
  
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
  static int daysBetween(const Date &start, const Date &end);
  static bool isLeapYear(int yr) { return !( (yr - 1804)%4 ); }
  void  incrDay(const int days);
  bool  incrMonth(const int mos);
  void  incrYear(const int yrs);

  static std::string intToStr_2d(const int n);
  
private:
  int month;
  int day;
  int year;
  static int daysInMonth[12]; // Contains the number of days in each month
  bool lessThan(const Date &rhs, bool orEqual) const;
};

#endif
