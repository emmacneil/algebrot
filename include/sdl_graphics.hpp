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
    int window_width();
    int window_height();
    void clear();
    void present();
    void draw_line(int x1, int y1, int x2, int y2, int r, int g, int b, int a = 255);
    void draw_point(int x, int y, int r, int g, int b, int a = 255);
  private:
    SDL_Window * window;
    SDL_Renderer * renderer;
};
