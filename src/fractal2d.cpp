// fractal2d.cpp

#include <chrono>
#include <iostream>

#include "fractal2d.hpp"

fractal2d::fractal2d(int w, int h)
  : K(1.0, 1.0, 1.0), width(w), height(h), BOUND(300), w(0.0)
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



unsigned short fractal2d::data_at(int row, int col)
{
  if (data == nullptr)
  {
    std::cout << "No memory allocated for fractal data." << std::endl;
    return 0;
  }
  int k = row*width + col;
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
  using clock = std::chrono::high_resolution_clock;

  bool print_time = true;
  std::cout << "Computing fractal ..." << std::endl;
  auto t0 = clock::now();
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
      number n = K(x, y, w);
      unsigned short tmp = iterate(n);
      data[k++] = tmp; // TODO: Account for different slices.
    }
  }
  auto t1 = clock::now();
  std::chrono::milliseconds dt = std::chrono::duration_cast<std::chrono::milliseconds>(t1 - t0);
  if (print_time)
    std::cout << "Done (in " << dt.count() << " ms)" << std::endl;
  else
    std::cout << "Done)" << std::endl;
}



unsigned short fractal2d::iterate(number c)
{
  number z = K(0.0, 0.0, 0.0);
  for (int i = 0; i < BOUND; i++)
  {
    z = f(z, c);
    if (z.norm() > 2.0)
      return (unsigned short)i;
  }
  return (unsigned short)BOUND;
}



void fractal2d::recenter(int x, int y)
{
  int old_x = width/2;
  int old_y = height/2;
  double dx = x - old_x;
  double dy = y - old_y;
  u += dx*step;
  v -= dy*step;
  fill_data();
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



void fractal2d::zoom(double factor)
{
  double lf_w = width;
  double lf_h = height;

  if (factor < 0.0)
  {
    std::cout << "Cannot zoom by a negative factor." << std::endl;
    return;
  }
  else if (factor < 1.0)
  {
    u -= step*lf_w/(2.0*factor);
    v += step*lf_h/(2.0*factor);
  }
  else
  {
    u += step*lf_w/(2.0*factor);
    v -= step*lf_h/(2.0*factor);
  }
  step /= factor;
  fill_data();
}
