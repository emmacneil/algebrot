// sdl_graphics.cpp

#include <iostream>

#include "sdl_graphics.hpp"



sdl_graphics::sdl_graphics()
  : window(nullptr), renderer(nullptr)
{
  //...
}



sdl_graphics::~sdl_graphics()
{
  quit();
}



void sdl_graphics::clear()
{
  SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
  SDL_RenderClear(renderer);
}



void sdl_graphics::draw_line(int x1, int y1, int x2, int y2, int r, int g, int b, int a)
{
  SDL_SetRenderDrawColor(renderer, r, g, b, a);
  SDL_RenderDrawLine(renderer, x1, y1, x2, y2);
}



void sdl_graphics::draw_point(int x, int y, int r, int g, int b, int a)
{
  SDL_SetRenderDrawColor(renderer, r, g, b, a);
  SDL_RenderDrawPoint(renderer, x, y);
}



bool sdl_graphics::init()
{
  std::cout << "Initializing SDL library." << std::endl;
  SDL_version v;
  SDL_GetVersion(&v);
  std::cout << "SDL version " << (int)v.major << "." << (int)v.minor << "." << (int)v.patch << std::endl;
  if (SDL_Init(SDL_INIT_VIDEO) < 0)
  {
    std::cout << "Failed to initialize SDL." << std::endl;
    std::cout << "SDL error: " << SDL_GetError() << std::endl;
    return false;
  }

  std::cout << "Creating window." << std::endl;
  window = SDL_CreateWindow("Algebrot", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 960, 540, 0);
  if (window == nullptr)
  {
    std::cout << "Failed to create window." << std::endl;
    std::cout << "SDL error: " << SDL_GetError() << std::endl;
    return false;
  }

  std::cout << "Creating a 2D rendering context for window." << std::endl;
  renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
  if (renderer == nullptr)
  {
    std::cout << "Failed to create rendering context." << std::endl;
    std::cout << "SDL error: " << SDL_GetError() << std::endl;
    return false;
  }

  return true;
}



void sdl_graphics::quit()
{
  if (renderer != nullptr)
    SDL_DestroyRenderer(renderer);
  if (window != nullptr)
    SDL_DestroyWindow(window);
  SDL_Quit();
}



void sdl_graphics::present()
{
  SDL_RenderPresent(renderer);
}



int sdl_graphics::window_width()
{
  int ret;
  SDL_GetWindowSize(window, &ret, nullptr);
  return ret;
}



int sdl_graphics::window_height()
{
  int ret;
  SDL_GetWindowSize(window, nullptr, &ret);
  return ret;
}
