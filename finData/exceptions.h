#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H

#include <stdexcept>

class bad_data : public std::runtime_error {
public:
  virtual char const* what() const { return "The data string used to initialize a fin_data object is incomplete. This may be due to a corrupt data file."; }
};

#endif
