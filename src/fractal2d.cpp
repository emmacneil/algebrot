// fractal2d.cpp

#include <iostream>

#include "fractal2d.hpp"



fractal2d::fractal2d(int w, int h)
  : K(1, -2, -1), width(w), height(h)
{
  // Allocate enough memory for fractal
  data = (unsigned short *)malloc(w*h*sizeof(unsigned short));
  if (data == nullptr)
    std::cout << "Could not allocated enough memory for fractal data." << std::endl;

  reset();

  // Dump some information about fractal
  std::cout << "Width:  " << width << std::endl;
  std::cout << "Height: " << height << std::endl;
  std::cout << "u:      " << u << std::endl;
  std::cout << "v:      " << v << std::endl;
  std::cout << "step:   " << step << std::endl;
}



fractal2d::~fractal2d()
{
  if (data != nullptr)
    free(data);
}



unsigned short fractal2d::data_at(int i, int j)
{
  if (data == nullptr)
  {
    std::cout << "No memory allocated for fractal data." << std::endl;
    return 0;
  }
  int k = j*width + i;
  if (k >= width*height)
    return 0;
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
  for (int row = 0; row < height; row++)
  {
    for (int col = 0; col < width; col++)
    {
      double x = u + (double)col * step;
      double y = v - (double)row * step;
      number n = K(x, y, 0.0);
      unsigned short tmp = iterate(n);
      data[k++] = tmp; // TODO: Account for different slices.
    }
  }
}



unsigned short fractal2d::iterate(number c)
{
  const int BOUND = 1000;
  
  number z = K(0, 0, 0);
  for (int i = 0; i < BOUND; i++)
  {
    z = f(z, c);
    if (z.norm() > 2.0)
      return (unsigned short)i;
  }
  return (unsigned short)BOUND;
}



void fractal2d::reset()
{
  // Choose a new upper-left corner and step based on current width and height
  // We want to center the fractal so that the origin (0, 0) is at the center of the screen
  // and we want at least the circle of radius 2 to be visible.
  step = 4.0/(height < width ? (double)height : (double)width);
  u = -step*((double)width/2.0);
  v =  step*((double)height/2.0);
  fill_data();
}



void fractal2d::resize(int w, int h)
{
  width = w;
  height = h;
  if (data != nullptr)
    free(data);
  data = (unsigned short *)malloc(w*h);
  if (data == nullptr)
    std::cout << "Could not allocated enough memory for fractal data." << std::endl;
  fill_data();
}
