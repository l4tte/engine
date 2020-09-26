// Copyright (c) 2020, Ari Eythorsson
// See LICENSE.txt for more information

#include "screen.hpp"

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

RLEConsole::RLEConsole(int width, int height, int tilesize)
{
  int widthpx = tilesize * width;
  int heightpx = tilesize * height;
  SDL_Init(SDL_INIT_EVERYTHING);
  Window = SDL_CreateWindow(
    "RL",  // Window title
    SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
    widthpx, heightpx,
    0
  );
}
