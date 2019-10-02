// app.cpp

#include <iostream>

#include "app.hpp"



app::app()
{
}



// Handles mouse and keyboard events.
// Returns true if an event suggests the program should terminate.
bool app::handle_input()
{
  SDL_Event e;
  while (SDL_PollEvent(&e)) // While there are events in the queue
  {
    switch (e.type) 
    {
      case SDL_KEYDOWN:
        return handle_key_event(e.key);
      case SDL_WINDOWEVENT:
        return handle_window_event(e.window);
      default:
        break;
    }
  }

  return false;
}



bool app::handle_key_event(SDL_KeyboardEvent & e)
{
  return true;
}



bool app::handle_window_event(SDL_WindowEvent & e)
{
  switch (e.event)
  {
    case SDL_WINDOWEVENT_CLOSE :
      return true;
    default :
      return false;
  }
}



bool app::init()
{
  std::cout << "Initializing renderer." << std::endl;
  if (!renderer.init())
  {
    std::cout << "Failed to initialize renderer." << std::endl;
    return false;
  }

  std::cout << "Constructing fractal." << std::endl;
  int width = renderer.window_width();
  int height = renderer.window_height();
  fractal = new fractal2d(width, height);
  if (fractal == nullptr)
  {
    std::cout << "Failed to construct fractal." << std::endl;
    return false;
  }

  return true;
}



void app::pick_color(const unsigned short i, int * r, int * g, int * b)
{
  if (i == fractal->BOUND)
  {
    (*r) = 0;
    (*g) = 0;
    (*b) = 0;
    return;
  }

  float pi = 3.1415927;
  float f_i = (float)i;
  float f_B = (float)fractal->BOUND;
  float f_rshift = 2.0;
  float f_gshift = 1.0;
  float f_bshift = -1.0;
  float f_r = 127.0f*(std::sin(pi * f_i / f_B - f_rshift) + 1.0f);
  float f_g = 127.0f*(std::sin(pi * f_i / f_B - f_gshift) + 1.0f);
  float f_b = 127.0f*(std::sin(pi * f_i / f_B - f_bshift) + 1.0f);
  (*r) = (int)f_r;
  (*g) = (int)f_g;
  (*b) = (int)f_b;
}



void app::quit()
{
  if (fractal != nullptr)
    delete fractal;
}



void app::render()
{
  renderer.clear();

  bool show_center = true; // Show two red lines intersecting at center of window.
  int w = renderer.window_width();
  int h = renderer.window_height();
  for (int row = 0; row < h; row++)
  {
    for (int col = 0; col < w; col++)
    {
      int r, g, b;
      pick_color(fractal->data_at(row, col), &r, &g, &b);
      renderer.draw_point(col, row, r, g, b);
    }
  }

  if (show_center)
  {
    renderer.draw_line(0, 0, w, h, 255, 0, 0);
    renderer.draw_line(w, 0, 0, h, 255, 0, 0);
  }
  renderer.present();
}



void app::run()
{
  bool quit = false;
  while (!quit)
  {
    render();
    quit = handle_input();
  }
}
