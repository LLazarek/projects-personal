#ifndef FINMANAGER_H
#define FINMANAGER_H

#include "fin_data.h"
#include "Date.h"

class finManager{
private:
  std::vector<fin_data> entryList;
  
public:
  finManager();

  // Read information from dateStart to dateEnd from data files
  bool read(std::string path, Date start, Date end);
  void genReport();
  bool saveEntry(const fin_data &entry);
  
};

#endif
