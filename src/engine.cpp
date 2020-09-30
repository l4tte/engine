// Copyright (c) 2020, Ari Eythorsson
// See LICENSE.txt for more information

#include "engine.hpp"

#include <stdlib.h> // For malloc
#include <iostream>

#include <SDL2/SDL.h>

#include "font.hpp"

// Initialize RLESCreen::Root with garbage data
// Will be set properly in RLEScreen::CreateScreen
RLEConsole* RLE::Screen::Root = (RLEConsole*)malloc(sizeof(RLEConsole));

// Initialize RLE::Screen::IsOpen bool to false
// Because the window is closed until initialized in
// RLE::Screen::CreateScreen
bool RLE::Screen::IsOpen = false;

int main()
{
  SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "0");
  RLE::Init(); // Initial setup, defined by user
  while (RLEScreen::IsOpen) // While the screen is open
  {
   RLEEngine::Update();
   RLE::Update(); // Game loop, defined by user
   RLEScreen::Render();
   RLEEngine::FPS(120); // 120 FPS
  }
  RLEEngine::Exit();
	return 0;
}


void RLE::Screen::CreateScreen(int tilesize, int width, int height, char const* title)
{
  // TODO: Dynamic tilesize
  RLE::Screen::Root = new RLEConsole(width, height, tilesize);
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
  RLE::Screen::Root->KeyboardStateUpdate();
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
        break;

      case SDL_KEYDOWN:
        if (!event.key.repeat)
        {
          Screen::Root->KeyPressed_(event.key.keysym.scancode, true);
          std::cout << Screen::Root->IsKeyDown('d') << "\n";
        }
        break;
    }
  }
}

void RLE::Engine::Exit()
{
  RLE::Screen::FreeScreen();
  SDL_Quit();
}
