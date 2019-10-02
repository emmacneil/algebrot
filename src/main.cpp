// main.cpp

#include <iostream>
#include "number_field.hpp"
#include "number.hpp"
#include "sdl_graphics.hpp"

using namespace std;



bool handle_input();
bool handle_key_event(SDL_KeyboardEvent & e);
bool handle_window_event(SDL_WindowEvent & e);
void render();
void run();



int main(int argc, char * argv[])
{
  sdl_graphics g;
  
  if (g.init())
  {
    run();
  }
  else
    cout << "Could not initialize graphics." << endl;

  cout << "Exiting." << endl;
  
  return 0;
}



// Handles mouse and keyboard events.
// Returns true if an event suggests the program should terminate.
bool handle_input()
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



bool handle_key_event(SDL_KeyboardEvent & e)
{
  return true;
}



bool handle_window_event(SDL_WindowEvent & e)
{
  switch (e.event)
  {
    case SDL_WINDOWEVENT_CLOSE :
      return true;
    default :
      return false;
  }
}



// Draws the fractal
void render()
{
}



// Runs the input-render loop
void run()
{
  bool quit = false;
  while (!quit)
  {
    quit = handle_input();
    render();
  }
}
