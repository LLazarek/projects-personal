// Create test code for fin_data class
#include "fin_data.h"


int main(){
  fin_data fd("04/25/2013|-25.33|CA|Test note.|food`living costs");
  fin_data fd1(Date(4, 25, 2013), 25.33, "CA", "Test note.", "food`living costs");
  std::cout << fd.getDate() << '\n' << fd.getAmount() << '\n' << fd.getMedium() << '\n' << fd.getNote() << std::endl;
  auto list = fd.getTagList();
  for(auto it = list.begin(); it != list.end(); ++it){
    std::cout << *it << ", ";
  }
  std::cout << std::endl;

  std::cout << "-------------------------------" << std::endl;

  fd.setDate(Date(5, 24, 2010));
  fd.setMedium("CC");
  fd.setAmount(30);
  fd.setNote("No note.");
  fd.setTagList("other stuff");

    std::cout << fd.getDate() << '\n' << fd.getAmount() << '\n' << fd.getMedium() << '\n' << fd.getNote() << std::endl;
  list = fd.getTagList();
  for(auto it = list.begin(); it != list.end(); ++it){
    std::cout << *it << ", ";
  }
  std::cout << std::endl;
  fd.addTags("something else`monthly");
    list = fd.getTagList();
  for(auto it = list.begin(); it != list.end(); ++it){
    std::cout << *it << ", ";
  }
  std::cout << std::endl;
}
