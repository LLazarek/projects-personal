class finManager{
 private:
  fin_data* entryList;
  double avgIn_daily;
  double avgOut_daily;
  double avgIn_weekly;
  double avgOut_weekly;
  double avgIn_monthly;
  double avgOut_monthly;

 public:
  finManager();
  finManager(finManager &rhs);
  
  
  bool read(Date dateStart, Date dateEnd);
