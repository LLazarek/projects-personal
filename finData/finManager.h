#ifndef FINMANAGER_H
#define FINMANAGER_H

#include <vector>
#include "fin_data.h"
#include "Date.h"

class finManager{
private:
  std::vector<fin_data> entryList;
  
public:
  finManager();

  // Read information from dateStart to dateEnd from data files
  bool read(Date start, Date end);
  void genReport();
  bool saveEntry(const fin_data &entry);
  
};

#endif
