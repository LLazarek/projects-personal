#include <cstdlib>
#include <string>
#include "Date.h"

#define DEBUG

int Date::daysInMonth[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

/* Date::Constructor: creates a Date object from a string containing a date in
   the format "mm/dd/yyyy"
*/
Date::Date(std::string in){
  // Extract data from string, format mm/dd/yyyy
  std::string m = in.substr(0, 2);
  month = atoi(m.c_str());
  if(month < 1) month = 1;
  else if(month > 12) month = 12;
  
  std::string d = in.substr(3, 5);
  day = atoi(d.c_str());
  if(day < 1) day = 1;
  else if(day > daysInMonth[month - 1]) day = daysInMonth[month - 1];
  
  std::string y = in.substr(6, 10);
  year = atoi(y.c_str());
}


/* Date::Constructor: creates a Date object from integer values for month, day,
   and year (in that order)
*/
Date::Date(int mo, int d, int y) : month(mo), day(d), year(y) {
  // Ensure valid inputs
  if(month < 1 || mo > 12) month = 1;
  
  if(day < 1) day = 1;
  else if(day > daysInMonth[month - 1]){
    day = daysInMonth[month - 1]; // Coerce day to highest possible value in mo
  }
  
  if(year < 1) year = 1;
  if(day == 29 && month == 2 && !isLeapYear(year))
    throw "Invalid date";
}


Date& Date::operator=(const Date &rhs){
  // Shallow copy
  day = rhs.getDay();
  month = rhs.getMonth();
  year = rhs.getYear();
  return *this;
}

/* lessThan:
   Private utility function. Determines if another Date object represents a date
   before this one.

   @params
   Date& rhs               A reference to the other Date object
   bool orEqual            Act as <=?
                           true:   returns this <= rhs
			   false:  returns this <  rhs

   @params
   bool                    The result of the comparison.
                           (See parameter orEqual)
*/
bool Date::lessThan(const Date &rhs, bool orEqual) const{
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

bool Date::operator<(const Date &rhs) const{
  return lessThan(rhs, false);
}

bool Date::operator>(const Date &rhs) const{
  return !lessThan(rhs, true);
}

bool Date::operator<=(const Date &rhs) const{
  return lessThan(rhs, true);
}

bool Date::operator>=(const Date &rhs) const{
  return !lessThan(rhs, false);
}

bool Date::operator==(const Date &rhs) const{
  return ((year == rhs.getYear()) &&
	  (month == rhs.getMonth()) &&
	  (day == rhs.getDay()));
}

bool Date::operator!=(const Date &rhs) const{
  return !operator==(rhs);
}

/* Date::toStr():
   Creates a string representation of this Date object in the format
   "mm/dd/yyyy"

   @params
   void

   @return
   std::string 
*/
std::string Date::toStr() const{ // Using c++11 (c++0x)
  return (Date::intToStr_2d(month) + "/" + Date::intToStr_2d(day) +
          "/" + std::to_string(year));
}

std::ostream& operator<<(std::ostream &out, const Date &rhs){
  return out << rhs.month << "/" << rhs.day << "/" << rhs.year;
}

/* Date::daysBetween():
   Datermines the number of days between the two given Dates. The order of
   the arguments does not matter.
   Note that this function accounts for leap years.

   @params
   const Date &start
   const Date &end

   @return
   int 
*/
int Date::daysBetween(const Date &start, const Date &end){
  int days = 0;
  Date st = start;
  Date ed = end;
  if(st > ed){
    st = end;
    ed = start;
  }
  // Increment start day up until it is equal to end day
  for(int d = st.day; d != ed.day; ++d, ++days, ++(st.day)){
    // If day is at the end of the month, start next month
    if(d >= daysInMonth[st.month - 1]){
      // If it is NOT Feb 28 on a leap year
      if( !( d == 28  &&  st.isLeapYear()  &&  st.month == 2 ) ){
	d = 0; // Start next month (d will be incremented to 1)
	st.day = 0;
	if(st.month == 12){
	  st.month = 1;
	  ++(st.year);
	}
	else ++(st.month);
      }
      // Else (Feb 28 on leap year): continue to day 29
    }
  }

  // Increment start month up until it is equal to end month
  for(; st.month != ed.month; ++(st.month)){
    days += daysInMonth[st.month - 1];
    if(st.month == 2 && st.isLeapYear()) ++days;
    if(st.month == 12){ // If month is at end of year, start next year
      st.month = 0; // month will be incremented to 1
      ++(st.year);
    }
  }
  
  // Increment start year up until it is equal to end year
  for(int yr = st.year; yr < ed.year; ++yr){
    /* Account for leap years */
    if(Date::isLeapYear(yr)){
      if(st.month < 2   ||   (st.month == 2  &&  st.day <= 28)){
	++days;
      }
    }
    else if(Date::isLeapYear(yr + 1)){
      if(st.month > 2   ||   (st.month == 2  &&  st.day > 28)){
	++days;
      }
    }
    days += 365;
  }

  return days;
}

/*bool incrMonth(const int mos){
  int yr = year;
  mos += month;
  for(; mos > 12; mos -= 12){
    ++yr;
  }
  if(day > daysInMonth[mos]){
    if(!(mos == 2 && Date::isLeapYear(yr))){
      return false;
    }
  }
  month = mos;
  year = yr;
  return true;
}
*/

inline std::string Date::intToStr_2d(const int n){ // Requires C++11
  std::string str = std::to_string(n);
  if(n < 10) str = "0" + str;
  return str;
}
