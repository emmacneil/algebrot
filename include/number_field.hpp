#ifndef __NUMBER_FIELD_HPP__
#define __NUMBER_FIELD_HPP__

class number;

class number_field
{
  friend class number;
  public:
    /* Constructs the number field
     *   Q[x]/p(x)
     * where p(x) = x^3 + ax^2 + bx + c
     */
    number_field(const double a, const double b, const double c)
      : a(a), b(b), c(c) {}

    /* Construct the number field element
     *   r2*alpha^2 + r1*alpha + r0
     * where alpha is a primitive generator of this number field.
     */
    number operator()(const double r2, const double r1, const double r0) const;
  private:
    const double a, b, c;
};

#endif
