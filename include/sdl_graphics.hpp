// sdl_graphics.hpp

#include <SDL2/SDL.h>

#include "graphics.hpp"


class sdl_graphics : public graphics
{
  public:
    sdl_graphics();
    ~sdl_graphics();
    bool init();
    void quit();
  private:
    SDL_Window * window;
    SDL_Surface * surface;
};
