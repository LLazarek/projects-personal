#include <sstream>
#include "fin_data.h"
//#include "exceptions.h" // TODO: Exceptions

#define TAG_DELIM '`'
#define DATA_DELIM '|'


fin_data::fin_data(const Date        &idate,   const double &iamount,
		   const std::string &imedium, const std::string &inote,
		   const std::string &itagList)
          : date(idate), amount(iamount), medium(imedium), note(inote){
  setTagList(itagList);
}

std::string fin_data::getNextData(std::stringstream *stream){
  std::string str;
  if(!std::getline(*stream, str, DATA_DELIM)){
    // throw bad_data; // TODO: Exceptions
  }
  return str;
}

fin_data::fin_data(std::string data_entry){
  std::stringstream stream(data_entry);
  date = Date(getNextData(&stream));
  amount = std::stod(getNextData(&stream));
  medium = getNextData(&stream);
  note = getNextData(&stream);
  setTagList(getNextData(&stream));
}

void fin_data::setTagList(std::string tags){
  tagList.clear();
  // Extract each token (tag) and insert into tagList
  std::stringstream stream(tags);
  std::string str;
  while(std::getline(stream, str, TAG_DELIM)){
    tagList.insert(str);
  }
}

void fin_data::addTags(std::string tags){
  // Extract each token (tag) and insert into tagList
  std::stringstream stream(tags);
  std::string str;
  while(std::getline(stream, str, TAG_DELIM)){
    tagList.insert(str);
  }
}

std::string fin_data::toString() const {
  std::string str = "";
  str += date.toStr() + "|" + std::to_string(amount) + "|" + medium + "|"
         + note + "|";
  auto it = tagList.begin();
  if(it == tagList.end()) return str;
  str += *it;
  for(++it; it != tagList.end(); ++it){
    str += "`" + *it;
  }
  return str;
}
