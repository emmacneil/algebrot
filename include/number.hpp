#ifndef __NUMBER_HPP__
#define __NUMBER_HPP__

#include <ostream>

#include "number_field.hpp"

class number
{
  friend class number_field;
  public: 
    friend std::ostream& operator<< (std::ostream& os, const number & n);
    number operator+ (const number& n);
    number operator* (const number& n);
    void operator= (const number& n);
    double norm();
  private:
    number(const number_field & parent, const double r0, const double r1, const double r2)
      : parent(parent), r0(r0), r1(r1), r2(r2) {}
    const number_field & parent;
    double r0, r1, r2;
};

#endif
