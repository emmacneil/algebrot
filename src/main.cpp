// main.cpp

#include <iostream>
#include "number_field.hpp"
#include "number.hpp"

using namespace std;

int main(int argc, char * argv[])
{
  number_field K(1, -2, -1);
  number z = K(0, 0, 0);
  number c = K(0.1, 0.1, 0.01);

  cout << z << endl;
  for (int i = 0; i < 100; i++)
  {
    z = z*z + c;
    cout << z << endl;
  }

  return 0;
}
