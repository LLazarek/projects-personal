#include "fin_data.h"
#include <sstream>

#define TAG_DELIM '`'
#define DATA_DELIM '|'


fin_data::fin_data(const Date        &idate,   const double &iamount,
		   const std::string &imedium, const std::string &inote,
		   const std::string &itagList)
                   : date(idate), amount(iamount), medium(imedium){
  setTagList(itagList);
}

std::string getNextData(std::stringstream *stream){
  std::string str;
  if(!std::getline(*stream, str, DATA_DELIM)){
    // TMP TODO: throw exception
  }
  return str;
}

fin_data::fin_data(string data_entry){
  std::stringstream stream(data_entry);
  std::string str;
  date = Date(getNextData(&stream));
  amount = std::stod(getNextData(&stream));
  medium = getNextData(&stream);
  note = getNextData(&stream);
  setTagList(getNextData(&stream);
}

void fin_data::setTagList(std::string tags){
  // Extract each token (tag) and insert into tagList
  std::stringstream stream(tags);
  std::string str;
  while(std::getline(stream, str, TAG_DELIM))
    tagList.insert(str);
}
