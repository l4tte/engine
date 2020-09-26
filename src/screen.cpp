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
    SDL_PIXELFORMAT_ARGB8888,
    SDL_TEXTUREACCESS_STATIC,
    widthpx, heightpx
  );
  // Clear pixel buffer with empty pixels
  Pixels = (int32_t*)malloc(heightpx * widthpx * sizeof(int32_t));  // First, initailize the pixel array with empty garbage data
  memset(Pixels, 255, heightpx * widthpx * sizeof(int32_t)); // Next, replace every pixel with white in array
}  

RLEConsole::~RLEConsole()
{
  SDL_DestroyWindow(Window);
  SDL_DestroyRenderer(Renderer);
  SDL_DestroyTexture(Texture);
  delete[] Pixels;
}

void RLEConsole::Render()
{
  // Clear the renderer
  SDL_RenderClear(Renderer);
  Pixels[20 * widthpx + 20] = 0;
  // Copy the pixel array to the Texture
  SDL_UpdateTexture(Texture, NULL, Pixels, heightpx * sizeof(int32_t));
  // Present the renderer
  SDL_RenderCopy(Renderer, Texture, NULL, NULL);
  SDL_RenderPresent(Renderer);
}

void RLEConsole::SetPixel(int x, int y, int32_t px)
{
  Pixels[y * widthpx + x] = px;
}
