#include "finManager.h"

int main(){
  finManager fm;
  fm.saveEntry(fin_data("01/15/2015|22.30|CA|Test note.|food`disc"));
  std::string str("");
  
  do{
    std::cout << "Enter a new data entry:" << std::endl;
    std::cout << "Date:\t";
    getline(std::cin, str);
    Date d(str);
    
    std::cout << "Amount:\t";
    getline(std::cin, str);
    double amt = atof(str.c_str());
    
    std::cout << "Medium:\t";
    getline(std::cin, str);
    std::string med = str;
    
    std::cout << "Note:\t";
    getline(std::cin, str);
    std::string note = str;
    
    std::cout << "Tags:\t";
    getline(std::cin, str);
    fm.saveEntry(fin_data(d, amt, med, note, str));

    std::cout << "Save another?" << std::endl;
    getline(std::cin, str);
  }while(str.c_str()[0] == 'y'); // matches "y" & "yes"
}
