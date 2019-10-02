// main.cpp

#include <iostream>
#include "app.hpp"

using namespace std;



bool handle_input();
bool handle_key_event(SDL_KeyboardEvent & e);
bool handle_window_event(SDL_WindowEvent & e);
void render();
void run();



int main(int argc, char * argv[])
{
  app algebrot;

  cout << "Initializing app." << endl;
  if (algebrot.init())
    algebrot.run();
  else
    cout << "Could not initialize app." << endl;

  cout << "Exiting." << endl;
  
  return 0;
}


