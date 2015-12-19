/* class fin_data:
   Data wrapper for information related to a single expense/earning entry.
*/
#ifndef FIN_DATA_H
#def FIN_DATA_H

class fin_data {
private:
  Date date;
  double amount;
  string medium;
  string tagList;

public:
  /* fin_data():


     @params
     const Date &idate
     const double &iamount
     const string &imedium
     const string &itagList

     @return
     const 
  */
 fin_data(const Date &idate, const double &iamount, const string &imedium,
	  const string &itagList)
   : date(idate), amount(iamount), medium(imedium), tagList(itagList) {}
  

  bool setData(string idate = date, double iamount = amount, string imedium = medium, string itagList = tagList);
  
  
  string getDate(){ return date; }
  double getAmount(){ return amount; }
  string getMedium(){ return medium; }
  string getTagList(){ return tagList; }
}

#endif
