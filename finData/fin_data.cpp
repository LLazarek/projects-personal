#include "fin_data.h"

bool fin_data::setData(string idate = date, double iamount = amount, string imedium = medium,
		       string itags = tags){
  date = idate;
  amount = iamount;
  medium = imedium;
  tags = itags;
}
