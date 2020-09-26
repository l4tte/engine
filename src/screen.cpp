// Copyright (c) 2020, Ari Eythorsson
// See LICENSE.txt for more information

#include "screen.hpp"

#include <cstdint>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

RLEConsole::RLEConsole(int width, int height, int tilesize) :
  width(width), height(height), tilesize(tilesize)
{
  widthpx = tilesize * width;
  heightpx = tilesize * height;
  SDL_Init(SDL_INIT_EVERYTHING);
  Window = SDL_CreateWindow(
    "RL",  // Window title
    SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
    widthpx, heightpx,
    0
  );
  Renderer = SDL_CreateRenderer(
    Window,
    -1,
    SDL_RENDERER_ACCELERATED
  );
  Texture = SDL_CreateTexture(
    Renderer,
    SDL_PIXELFORMAT_RGB888,
    SDL_TEXTUREACCESS_STATIC,
    widthpx, heightpx
  );
  // Clear pixel buffer with garbage data
  Pixels = (int32_t*)calloc(heightpx * widthpx, sizeof(int32_t));
  Clear(); // And then clear the screen
}

RLEConsole::~RLEConsole()
{
  SDL_DestroyWindow(Window);
  SDL_DestroyRenderer(Renderer);
  SDL_DestroyTexture(Texture);
}

// Private function, will memset pixels to all white
void RLEConsole::Clear()
{
  memset(Pixels, 0xFFFFFF, heightpx * widthpx * sizeof(int32_t));
}

void RLEConsole::Render()
{
  // Clear the screen
  Clear();
  

  // Finally, render everything
  // Copy the pixel array to the Texture
  SDL_UpdateTexture(Texture, NULL, Pixels, heightpx * sizeof(int32_t));
  // Copy the texture and present the renderer
  SDL_RenderCopy(Renderer, Texture, NULL, NULL);
  SDL_RenderPresent(Renderer);
}

void RLEConsole::SetPixel(int x, int y, int32_t px)
{
  Pixels[y * widthpx + x] = px;
}
