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
      case SDL_MOUSEBUTTONDOWN:
        return handle_mouse_event(e.button);
      case SDL_MOUSEWHEEL:
        return handle_mouse_wheel_event(e.wheel);
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
  switch (e.keysym.sym)
  {
    case SDLK_ESCAPE:
    case SDLK_q:
      return true;
    case SDLK_r:
      fractal->reset();
      break;
    default:
      break;
  }
  return false;
}



bool app::handle_mouse_event(SDL_MouseButtonEvent & e)
{
  switch (e.button)
  {
    case SDL_BUTTON_LEFT:
      if (e.clicks == 1)
      {
        fractal->recenter(e.x, e.y);
      }
      else
      {
        fractal->zoom(2.0);
      }
      break;
    case SDL_BUTTON_MIDDLE:
        fractal->reset();
        break;
    case SDL_BUTTON_RIGHT:
      // Zoom out
        fractal->zoom(0.5);
      break;
    default:
      break;
  }
  return false;
}



bool app::handle_mouse_wheel_event(SDL_MouseWheelEvent & e)
{
  if (e.y > 0)
    fractal->zoom(2.0);
  else
    fractal->zoom(0.5);
  return false;
}



bool app::handle_window_event(SDL_WindowEvent & e)
{
  int w, h;
  switch (e.event)
  {
    case SDL_WINDOWEVENT_CLOSE :
      return true;
    case SDL_WINDOWEVENT_RESIZED :
    {
      w = renderer.window_width();
      h = renderer.window_height();
      //fractal->resize(w, h);
      break;
    } 
    default :
      break;
  }
  return false;
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

  bool show_center = false; // Show two red lines intersecting at center of window.
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
    quit = handle_input();
    //update();
    render();
  }
}



void app::update()
{
  static float sign = 1.0f;
  if (fractal->w > 2.0)
    sign = -1.0f;
  else if (fractal->w < -2.0)
    sign = 1.0f;
  fractal->w += 0.025f*sign;
  fractal->fill_data();
}
