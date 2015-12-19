#include "fin_data.h"

bool fin_data::setData(string idate, double iamount, string imedium,
		       string itags){
  date = idate;
  amount = iamount;
  medium = imedium;
  tags = itags;
}
