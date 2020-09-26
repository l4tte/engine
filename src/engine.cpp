// Copyright (c) 2020, Ari Eythorsson
// See LICENSE.txt for more information

#include "engine.hpp"

#include <stdlib.h> // For malloc

#include <SDL2/SDL.h>

#include "screen.hpp"

// Initialize RLESCreen::Root with garbage data
// Will be set properly in RLEScreen::CreateScreen
RLEConsole* RLEScreen::Root = (RLEConsole*)malloc(sizeof(RLEConsole));
// Initialize RLEScreen::IsOpen bool to false
// Because the window is closed until initialized in
// RLEScreen::CreateScreen
bool RLEScreen::IsOpen = false;

void RLEScreen::CreateScreen(int width, int height, char const* title)
{
  // TODO: Dynamic tilesize
  RLEScreen::Root = new RLEConsole(width, height, 16);
  RLEScreen::IsOpen = true;
}

void RLEScreen::FreeScreen()
{
  delete RLEScreen::Root;
}

void RLEEngine::Delay(int fps)
{
  SDL_Delay(1000 / fps);
}

void RLEEngine::Update()
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

