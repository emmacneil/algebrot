// number.cpp

#include "number.hpp"

std::ostream& operator<< (std::ostream& os, const number& n)
{
  os << n.r0 << " + " << n.r1 << "*a + " << n.r2 << "*a^2";
  return os;
}

number number::operator+ (const number & n)
{
  // Assumes number share the same parent
  number m = *this;
  return m.parent(m.r0 + n.r0, m.r1 + n.r1, m.r2 + n.r2);
}

number number::operator* (const number & n)
{
  number m = *this;
  double a = m.parent.a;
  double b = m.parent.b;
  double c = m.parent.c;
  double z = m.r1*n.r2 + m.r2*(n.r1 - a*n.r2);
  double t0 = m.r0*n.r0 - c*z;
  double t1 = m.r1*n.r0 + m.r0*n.r1 - c*m.r2*n.r2 - b*z;
  double t2 = m.r2*(n.r0 - b*n.r2) + m.r1*n.r1 + m.r0*n.r2 - a*z;
  return m.parent(t0, t1, t2);
}



void number::operator= (const number & n)
{
  r0 = n.r0;
  r1 = n.r1;
  r2 = n.r2;
}



double number::norm()
{
  // TODO : Compute the actual norm
  return std::max(std::max(std::abs(r0), std::abs(r1)), std::abs(r2));
}
