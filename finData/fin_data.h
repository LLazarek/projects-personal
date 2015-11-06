/* class fin_data:
   Data wrapper for information related to a single expense/earning entry.
*/
#ifndef FIN_DATA_H
#def FIN_DATA_H

class fin_data {
 private:
  string date;
  double amount;
  string medium;
  string tagList;

 public:
 fin_data(string idate, double iamount, string imedium, string itagList)
   : date(idate), amount(iamount), string medium(imedium), string tagList(itagList) {}
  bool setData(string idate = date, double iamount = amount, string imedium = medium,
	       string itagList = tagList);
  string getDate(){ return date; }
  double getAmount(){ return amount; }
  string getMedium(){ return medium; }
  string getTagList(){ return tagList; }
}

#endif
