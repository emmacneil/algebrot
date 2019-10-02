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



void app::quit()
{
  if (fractal != nullptr)
    delete fractal;
}



void app::render()
{
  renderer.clear();
  int w = renderer.window_width();
  int h = renderer.window_height();
  for (int i = 0; i < w; i++)
  {
    for (int j = 0; j < h; j++)
    {
      int shade = fractal->data_at(i,j);
      renderer.draw_point(i, j, shade, shade, shade);
    }
  }
  renderer.present();
}



void app::run()
{
  bool quit = false;
  while (!quit)
  {
    quit = handle_input();
    render();
  }
}
