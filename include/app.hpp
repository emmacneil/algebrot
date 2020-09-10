// app.hpp

#ifndef APP_HPP
#define APP_HPP

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
    void pick_color(const unsigned short i, int * r, int * g, int * b);
    bool handle_input();
    bool handle_key_event(SDL_KeyboardEvent & e);
    bool handle_mouse_event(SDL_MouseButtonEvent & e);
    bool handle_mouse_wheel_event(SDL_MouseWheelEvent & e);
    bool handle_window_event(SDL_WindowEvent & e);
    void render();
    void update();

    sdl_graphics renderer;
    fractal2d * fractal;
};

#endif // APP_HPP
