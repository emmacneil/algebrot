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
  return true;
}



void app::quit()
{
}



void app::render()
{
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
