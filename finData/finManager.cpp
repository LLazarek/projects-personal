#include "finManager.h"
#include <fstream>

finManager::finManager(){
  // Create missing files if necessary
  /*  if(!(/home/lukas/.finData exists)){
    mkdir /home/lukas/.finData;
    mkdir /home/lukas/.finData/data;
    if(!(/home/lukas/.finData/.conf exists)){
      touch /home/lukas/.finData/.conf;
    }
    }*/
}

bool finManager::read(const Date start, const Date end){
  entryList.clear();
  Date            Start = start, End = end;
  if(end < start) Start = end,   End = start; // Ensure dates in ascending order

  /* Begin reading in file for start.month
     Read all entries between start & end into entryList until either
     A. An entry is found that is > end --> done reading
     B. The end of file is reached --> continue reading from next month's file
  */
  bool stopFlag = false;
  while(!stopFlag){
    int mo = Start.getMonth(), yr = Start.getYear();
    std::string path = "/home/lukas/.finData/data/" + Date::intToStr_2d(mo) +
                       "." + Date::intToStr_2d(yr) + ".dat";
    std::string str;
    std::ifstream file(path);
    if(file.is_open()){
      while(getline(file, str, '\n')){
	if(str.size() < 3){
	  // Empty entry (eof), stop
	  stopFlag = true;
	  continue;
	}
	Date entryDate(str.substr(0, 10));
	if(entryDate < Start){
	  std::cout << "\tentryDate (" << entryDate.toStr() << ") < Start; skipping..." << std::endl;
	  // Skip
	}else if(entryDate >= Start && entryDate <= End){
	  entryList.push_back(fin_data(str));
	}else{ // entryDate > End
	  std::cout << "\tentryDate (" << entryDate.toStr() << ") > End; stopping..." << std::endl;
	  stopFlag = true;
	  break;
	}
      }
    }
    else return false;

    // File opened and read...
    file.close();

    ++mo;
    if(mo > 12){
      mo -= 12;
      ++yr;
    }
    Start = Date(mo, 1, yr); // Continue at start of next month
    if(Start > End){
      stopFlag = true;
    }
  }
  return true;
}

bool finManager::saveEntry(const fin_data &entry){  
  // read the file for entry's month
  read(Date(entry.getDate().getMonth(), 1, entry.getDate().getYear()), // start date
       Date(entry.getDate().getMonth(), 31, entry.getDate().getYear())); // end (day = last in mo)
  

  bool added = false; 
  // Find correct position to insert entry, then write changes to file
  for(auto it = entryList.begin(); !added && it != entryList.end(); ++it){
    if(entry.getDate() <= it -> getDate()){
      entryList.insert(it, entry);
      added = true;
    }else if(entry.getDate() > it -> getDate()){
      auto curr_it = it++;
      if(entry.getDate() <= it -> getDate()){
	entryList.insert(it, entry);
	added = true;
	break;
      }else it = curr_it;
    }
  }
  if(!added) entryList.push_back(entry); // Add entry if not added (list was empty)
  // Write new entry list to file
  std::string path = "/home/lukas/.finData/data/" +
                     Date::intToStr_2d(entry.getDate().getMonth()) + "." +
                     Date::intToStr_2d(entry.getDate().getYear()) + ".dat";
  std::ofstream file(path, std::ios::trunc);
  if(file.is_open()){
    for(auto it = entryList.begin(); it != entryList.end(); ++it){
      file << it -> toStr() << "\n";
    }
    file.close();
    return true;
  }else{
    // TMP TODO: Throw exception here
    std::cerr << "Error opening data file " << path << ", cannot save data."
	      << std::endl;
    return false;
  }
}
