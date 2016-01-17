// Create test code for fin_data class
#include "fin_data.h"


int main(){
  fin_data fd1("4/25/2013|-25.33|CA|Test note.|food`living costs");
  fin_data fd(Date(4, 25, 2013), 25.33, "CA", "Test note.", "food`living costs");
  std::cout << fd.getDate() << '\n' << fd.getAmount() << '\n' << fd.getMedium() << '\n' << fd.getNote() << std::endl;
  auto list = fd.getTagList();
  for(auto it = list.begin(); it != list.end(); ++it){
    std::cout << *it << ", ";
  }
  std::cout << std::endl;
  
}
