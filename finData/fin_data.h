/* class fin_data:
   Data wrapper for information related to a single expense/earning entry.
*/
#ifndef FIN_DATA_H
#define FIN_DATA_H

#include <string>
#include <unordered_set>
#include "Date.h"

class fin_data {
public:
  fin_data(const Date &idate, const double &iamount, const std::string &imedium,
	   const std::string &itagList, const std::string &inote);

  bool addTag(std::string tag){ return tagList.insert(tag).second; }
  
  void                             setDate    (Date d)           { date = d;   }
  void                             setMedium  (std::string m)    { medium = m; }
  void                             setAmount  (double a)         { amount = a; }
  void                             setNote    (std::string n)    { note = n;   }
  void                             setTagList (std::string tags);
  
  Date                             getDate    ()            { return date;    }
  double                           getAmount  ()            { return amount;  }
  std::string                      getMedium  ()            { return medium;  }
  std::unordered_set<std::string>  getTagList ()            { return tagList; }
  std::string                      getNote    ()            { return note;    }
  
private:
  Date                             date;
  double                           amount; // + = earning, - = expense
  std::string                      medium;
  std::string                      note;
  std::unordered_set<std::string>  tagList;
};

#endif
