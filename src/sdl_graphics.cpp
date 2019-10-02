// sdl_graphics.cpp

#include <iostream>

#include "sdl_graphics.hpp"



sdl_graphics::sdl_graphics()
  : window(nullptr), surface(nullptr)
{
  //...
}



sdl_graphics::~sdl_graphics()
{
  quit();
}



bool sdl_graphics::init()
{
  std::cout << "Initializing SDL library." << std::endl;
  if (SDL_Init(SDL_INIT_VIDEO) < 0)
  {
    std::cout << "Failed to initialize SDL." << std::endl;
    std::cout << "SDL error: " << SDL_GetError() << std::endl;
    return false;
  }

  std::cout << "Creating window." << std::endl;
  window = SDL_CreateWindow("Algebrot", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 640, 480, 0);
  if (window == nullptr)
  {
    std::cout << "Failed to create window." << std::endl;
    std::cout << "SDL error: " << SDL_GetError() << std::endl;
    return false;
  }

  return true;
}



void sdl_graphics::quit()
{
  if (surface != nullptr)
    SDL_FreeSurface(surface);
  if (window != nullptr)
    SDL_DestroyWindow(window);
  SDL_Quit();
}
