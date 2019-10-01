// number_field.cpp

#include "number_field.hpp"
#include "number.hpp"

number number_field::operator() (const double r0, const double r1, const double r2) const
{
  return number(*this, r0, r1, r2);
}
