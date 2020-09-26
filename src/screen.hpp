// Copyright (c) 2020, Ari Eythorsson
// See LICENSE.txt for more information

#ifndef SCREEN_HPP_
#define SCREEN_HPP_

struct SDL_Window;
struct SDL_Renderer;
struct SDL_Surface;

class RLEConsole
{
  public:
    // RLEConsole initializer, create new console
    // Width: Width of screen in pixels
    // Height: Height of screen in pixels
    RLEConsole(int width, int height, int tilesize);
    // Free Window, Renderer, and Texture. Should be called only
    // Once in the internal function RLEEngine::Exit
    ~RLEConsole();
    void Render();
  private:
    SDL_Window   *Window;
    SDL_Renderer *Renderer;
    int width, height, tilesize;
};  // RLEConsole

#endif  // SCREEN_HPP_
