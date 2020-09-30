// Copyright (c) 2020, Ari Eythorsson
// See LICENSE.txt for more information

#include "screen.hpp"

#include <cstdint>
#include <iostream>

#include <SDL2/SDL.h>

#include "font.hpp"
#include "error.hpp"

using RLEFont = RLE::Screen::Font;

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
  Pixels        = (int32_t*)calloc(heightpx * widthpx, sizeof(int32_t));
  Tiles         = (Tile*)calloc(height * width, sizeof(Tile));
  CurrentFont   = (RLEFont*)malloc(sizeof(RLEFont));
  for (int i = 0; i < 256; i++)
  {
    KeyboardState[i] = false;
  }
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

// Internal function for rendering characters
void RLEConsole::RenderTile(int x, int y, Tile tile)
{
  SDL_Surface* CS = CurrentFont->GetChar(tile.Ch); // Charachter Surface
  SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "0");
  SDL_Texture* CT = SDL_CreateTextureFromSurface(Renderer, CS);
  SDL_Rect dst;
  dst.x = x * (widthpx/width);    
  dst.y = y * (heightpx/height);  
  dst.w = (widthpx/width);   
  dst.h = (heightpx/height); 

  SDL_SetTextureColorMod(CT, tile.Col.r, tile.Col.g, tile.Col.b);
  SDL_RenderCopy(Renderer, CT, NULL, &dst);

  SDL_FreeSurface(CS);
  SDL_DestroyTexture(CT);
}

void RLEConsole::Render()
{
  // Copy the pixel array to the Texture
  SDL_UpdateTexture(Texture, NULL, Pixels, heightpx * sizeof(int32_t));
  SDL_RenderCopy(Renderer, Texture, NULL, NULL);
  // Loop through tiles and draw each one
  for (int x = 0; x < width; x++)
  {
    for (int y = 0; y < height; y++)
    {
      RenderTile(x, y, Tiles[x * width + y]);
      Tiles[x * width + y] = {0};
    }
  }
  // Finally, render everything
  // Copy the texture and present the renderer
  SDL_RenderPresent(Renderer);
}

void RLEConsole::SetPixel(int x, int y, int32_t px)
{
  Pixels[y * widthpx + x] = px;
}

void RLEConsole::SetFont(char* Path, int Rows, int Cols, int* Letters)
{
  CurrentFont = new RLEFont(Path, Rows, Cols, Letters);
}

void RLEConsole::SetChar(int x, int y, Tile T)
{  
  Tiles[x * width + y] = T; 
}

bool RLEConsole::IsKeyDown(int keycode)
{
  int key = SDL_GetScancodeFromKey(keycode);
  return KeyboardState[key];
}

void RLEConsole::KeyboardStateUpdate()
{
  //KeyboardStateOld = KeyboardState;
  for (int i = 0; i < 256; i++)
  {
    KeyboardState[i] = false;
  }
  //KeyboardState    = (uint8_t*)SDL_GetKeyboardState(NULL);
}

void RLEConsole::KeyPressed_(int key, bool val)
{
  if (key > 256 || key < 0)
  {
    Error("screen.cpp, keypressed_", "Key value is invalid");
  }
  KeyboardState[key] = val;
}
