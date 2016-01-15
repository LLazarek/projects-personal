#include "fin_data.h"
#include <sstream>

#define TAG_DELIM '`'

fin_data::fin_data(const Date        &idate,   const double &iamount,
		   const std::string &imedium, const std::string &itagList,
		   const std::string &inote)
                   : date(idate), amount(iamount), medium(imedium){
  setTagList(itagList);
}

void fin_data::setTagList(std::string tags){
  // Extract each token (tag) and insert into tagList
  std::stringstream stream(tags);
  std::string str;
  while(std::getline(stream, str, TAG_DELIM))
    tagList.insert(str);
}
