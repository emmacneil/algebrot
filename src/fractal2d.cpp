// fractal2d.cpp

#include <iostream>

#include "fractal2d.hpp"



fractal2d::fractal2d(int w, int h)
  : K(1, -2, -1), width(w), height(h)
{
  // Allocate enough memory for fractal
  data = (unsigned char *)malloc(w*h);
  if (data == nullptr)
    std::cout << "Could not allocated enough memory for fractal data." << std::endl;

  reset();
}



fractal2d::~fractal2d()
{
  if (data != nullptr)
    free(data);
}



unsigned char fractal2d::data_at(int i, int j)
{
  int k = i*width + j;
  if (k >= i*j) return 0;
  return data[k];
}

number fractal2d::f(number z, number c)
{
  return z*z + c;
}



void fractal2d::fill_data()
{
  if (data == nullptr)
  {
    std::cout << "No memory allocated for fractal data." << std::endl;
    return;
  }
  int k = 0;
  for (int i = 0; i < width; i++)
  {
    for (int j = 0; j < height; j++)
    {
      double x = u + (double)i * step;
      double y = v + (double)j * step;
      data[k++] = iterate(K(x,y,0.0)); // TODO: Account for different slices.
    }
  }
}



unsigned char fractal2d::iterate(number c)
{
  const int BOUND = 200;
  
  number z = K(0, 0, 0);
  for (int i = 0; i < BOUND; i++)
  {
    z = f(z, c);
    if (z.norm() > 2)
      return (unsigned char)i;
  }
  return (unsigned char)BOUND;
}



void fractal2d::reset()
{
  // Choose a new upper-left corner and step based on current width and height
  // We want to center the fractal so that the origin (0, 0) is at the center of the screen
  // and we want at least the circle of radius 2 to be visible.
  step = 4.0/(height < width ? (double)height : (double)width);
  u = 2.0*step*((double)width/2.0);
  v = 2.0*step*((double)height/2.0);
  fill_data();
}



void fractal2d::resize(int w, int h)
{
  width = w;
  height = h;
  if (data != nullptr)
    free(data);
  data = (unsigned char *)malloc(w*h);
  if (data == nullptr)
    std::cout << "Could not allocated enough memory for fractal data." << std::endl;
  fill_data();
}
