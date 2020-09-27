// Copyright (c) 2020, Ari Eythorsson
// See LICENSE.txt for more information

#include "engine.hpp"

#include <stdlib.h> // For malloc

#include <SDL2/SDL.h>

// Initialize RLESCreen::Root with garbage data
// Will be set properly in RLEScreen::CreateScreen
RLEConsole* RLE::Screen::Root = (RLEConsole*)malloc(sizeof(RLEConsole));
// Initialize RLE::Screen::IsOpen bool to false
// Because the window is closed until initialized in
// RLE::Screen::CreateScreen
bool RLE::Screen::IsOpen = false;

void RLE::Screen::CreateScreen(int width, int height, char const* title)
{
  // TODO: Dynamic tilesize
  RLE::Screen::Root = new RLEConsole(width, height, 16);
  RLE::Screen::IsOpen = true;
}

void RLE::Screen::Render()
{
  RLE::Screen::Root->Render();
}

void RLE::Screen::FreeScreen()
{
  RLE::Screen::Root->~RLEConsole();
  delete RLE::Screen::Root;
}

void RLE::Engine::FPS(int fps)
{
  SDL_Delay(1000 / fps);
}

void RLE::Engine::Update()
{
  // Handle events
  SDL_Event event;
  while(SDL_PollEvent(&event))
  {
    switch (event.type)
    {
      // The game has recieved a quit signal
      // Change IsOpen bool 
      case SDL_QUIT:
        Screen::IsOpen = false;
    }
  }
}

void RLE::Engine::Exit()
{
  RLE::Screen::FreeScreen();
  SDL_Quit();
}
