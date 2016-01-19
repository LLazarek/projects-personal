#include <fstream>
#include "Date.h"

finManager::finManager(){
  // Create missing files if necessary
  if(!(~/.finData exists)){
    mkdir ~/.finData;
    mkdir ~/.finData/data;
    if(!(~/.finData/.conf exists)){
      touch ~/.finData/.conf;
    }
  }
}

bool finManager::read(const Date start, const Date end){
  string path = "~/.finData/data/" + std::to_string(start.getMonth()) + "." +
                std::to_string(start.getYear()) + ".dat";
  Date Start = start, End = end;
  if(end < start) Start = end, End = start; // Ensure dates in ascending order
  // Loop and read each line from file, checking date of each entry
  // if an entry is found that is > end, set a flag and stop looping.
  // After loop, check for flag - if not set, increment start month and then
  // repeat, reading next month's file
}

bool finManager::saveEntry(const fin_data &entry){
  // Open/create necessary file
  string path = "~/.finData/data/" + std::to_string(entry.getMonth()) + "." +
                std::to_string(entry.getYear()) + ".dat";
  std::ifstream dataFile(path);
  if(dataFile.is_open()){
    read(Date(entry.getMonth(), 1, entry.getYear()), // start date
	 Date(entry.getMonth(), 50, entry.getYear())); // end (day = last in mo)
    // Find correct position to insert entry, then write changes to file
  }else{
    // TMP TODO: Throw exception here
    std::cerr << "Error opening data file " << path << ", cannot save data."
	      << std::endl;
  }
}
