// app.hpp

#ifndef __APP_HPP__
#define __APP_HPP__

#include "sdl_graphics.hpp"
#include "fractal2d.hpp"



class app
{
  public:
    app();
    bool init();
    void quit();
    void run();
  private:
    bool handle_input();
    bool handle_key_event(SDL_KeyboardEvent & e);
    bool handle_window_event(SDL_WindowEvent & e);
    void render();

    sdl_graphics renderer;
    fractal2d * fractal;
};

#endif
