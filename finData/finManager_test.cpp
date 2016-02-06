#include "finManager.h"

int main(){
  finManager fm;
  std::string str("");
  std::cout << "Welcome to finAid. Today's date is " << Date::today().toStr()
	    << '\n' << std::endl;
  Date test = Date::today();
  test.incrDay(1);
  std::cout << test << '\n' << std::endl;
  
  do{
    std::cout << "Enter a new data entry:" << std::endl;
    std::cout << "Date: (. = today)\t";
    getline(std::cin, str);
    Date d;
    if(str.compare(".") == 0)  d = Date::today();
    else                       d = Date(str);
    
    std::cout << "Amount: (- = earning)\t";
    getline(std::cin, str);
    double amt = atof(str.c_str());
    
    std::cout << "Medium:\t\t\t";
    getline(std::cin, str);
    std::string med = str;
    
    std::cout << "Note:\t\t\t";
    getline(std::cin, str);
    std::string note = str;
    
    std::cout << "Tags:\t\t\t";// Tags seperated by '`'
    getline(std::cin, str);
    fm.saveEntry(fin_data(d, amt, med, note, str));

    std::cout << "Save another? ([y]/n)" << std::endl;
    getline(std::cin, str);
  }while(str.size() == 0 || str.c_str()[0] == 'y'); // matches "y" & "yes"
}
