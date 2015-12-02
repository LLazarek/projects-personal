#include <cstdlib>
#include <string>
#include "Date.h"

Date::Date(std::string in){
  // Extract data from string, format mm/dd/yyyy
  const char *c = in.c_str();
  char m[2] = {*c, *(c + 1)};
  char d[2] = {*(c + 3), *(c + 4)};
  char y[4] = {*(c + 6), *(c + 7), *(c + 8), *(c + 9)};
  month = atoi(m);
  day = atoi(d);
  year = atoi(y);
}

Date::Date(int mo, int d, int y) : month(mo), day(d), year(y) {
  // Ensure valid inputs
  if(month < 1 || mo > 12) month = 1;
  if(day < 1 || day > 31) day = 1;
  if(year < 1) year = 1;
}

Date& Date::operator=(Date &rhs){
  // Shallow copy
  day = rhs.getDay();
  month = rhs.getMonth();
  year = rhs.getYear();
  return *this;
}

/* lessThan:
   Private utility function. Determines if another Date object
   is less than this one.

   @params
   Date& rhs               A reference to the other Date object
   bool orEqual            Act as <=?
                           true:   returns this <= rhs
			   false:  returns this <  rhs

   @params
   bool                    The result of the comparison.
                           (See parameter orEqual)
*/
bool Date::lessThan(Date &rhs, bool orEqual){
  int yearDiff = year - rhs.getYear();
  if(yearDiff < 0){              // this.year < rhs.year
    return true;
  }else if(yearDiff == 0){       // Same year
    int monthDiff = month - rhs.getMonth();
    if(monthDiff < 0){           // this.month < rhs.month
      return true;
    }else if(monthDiff == 0){    // Same month
      int dayDiff = day - rhs.getDay();
      if(dayDiff < 0)            // this.day < rhs.day
	return true;
      else if(dayDiff == 0)      // Same day
	return orEqual;
    }
  }
  // else
  return false;
}

bool Date::operator<(Date &rhs){
  return lessThan(rhs, false);
}

bool Date::operator>(Date &rhs){
  return !lessThan(rhs, true);
}

bool Date::operator<=(Date &rhs){
  return lessThan(rhs, true);
}

bool Date::operator>=(Date &rhs){
  return !lessThan(rhs, true);
}

bool Date::operator==(Date &rhs){
  return ((year == rhs.getYear()) &&
	  (month == rhs.getMonth()) &&
	  (day == rhs.getDay()));
}

bool Date:operator!=(Date &rhs){
  return !operator==(rhs);
}

std::string std::toStr(){ // Using c++11 (c++0x)
  return (std::to_string(month) + "/" + std::to_string(day) +
          "/" + std::to_string(year));
}

std::ostream& std::operator<<(std::ostream &out, const Date &rhs){
  out << rhs.month << "/" << rhs.day << "/" << rhs.year;
}
