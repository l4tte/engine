#include "font.hpp"

#include <cmath> 

#include <iostream>

#include <SDL2/SDL.h>

#include "error.hpp"

RLE::Screen::Font::Font(char* Path, int Rows, int Cols, int* Letters) :
  Path(Path), Letters(Letters), Rows(Rows), Cols(Cols)
{
  FontSurface = SDL_LoadBMP(Path);

  if (FontSurface == NULL)
  {
    Error("font.cpp", "Could not init fontsurface");
  }
}

SDL_Surface* RLE::Screen::Font::GetChar(int ch)
{
  SDL_Rect src;
  
  // For each letter, currently only works with terminal.png
  /*for (int i = 0; i < 256; i++)
  {
    if (Letters[i] == ch)
    {
      int x = 256 / i;
      int y = 256 % i;
      std::cout << "x: " << x << "\n";
      std::cout << "y: " << y << "\n";
      src.x = x * (FontSurface->w/Rows);
      src.y = y * (FontSurface->h/Cols);
      src.w = (FontSurface->w/Rows);
      src.h = (FontSurface->h/Cols);
      SDL_Surface *ret = SDL_CreateRGBSurface(
        0,
        src.w,
        src.h,
        32,
        0,0,0,0
      );
      SDL_BlitSurface(FontSurface, &src, ret, NULL);
      SDL_SetColorKey(ret, SDL_TRUE, 0x000000);
      return ret;
    }
  }*/

  for (int y = 0; y < 16; y++)
  {
    for (int x = 0; x < 16; x++)
    {
      if (Letters[x * 16 + y] == ch)
      {
        src.x = x * (FontSurface->w/Rows);
        src.y = y * (FontSurface->h/Cols);
        src.w = (FontSurface->w/Rows);
        src.h = (FontSurface->h/Cols);
        SDL_Surface *ret = SDL_CreateRGBSurface(
          0,
          src.w,
          src.h,
          32,
          0,0,0,0
        );
        SDL_BlitSurface(FontSurface, &src, ret, NULL);
        SDL_SetColorKey(ret, SDL_TRUE, 0x000000);
        return ret;
      }
    }
  }

  // No letter was found, return empty surface
  return SDL_CreateRGBSurface(0, 0, 0, 32, 0, 0, 0, 0);
}
