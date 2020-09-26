// Copyright (c) 2020, Ari Eythorsson
// See LICENSE.txt for more information

#ifndef ENGINE_HPP_
#define ENGINE_HPP_

// Include these files in .hpp for a couple reasons.
// Every file including "Engine.hpp" is including the entire
// Roguelike engine, including these files.
// Also, functions/namespaces in these files are referenced 
// Throughout this header file. So to save compile time, space,
// and simplify everything, these files are included in
// This header.
// Also it makes RLE a one-include library
#include "screen.hpp"
#include "font.hpp"

class RLEConsole;

namespace RLE 
{
  namespace Engine
  {
    // Used at the end of every loop by calling
    // SDL_Delay for a length of time that if called every frame
    // will make the game run at int fps frames per second
    // Basically, call at the end of every frame with your 
    // Preferred FPS
    extern void FPS(int fps);
    // Update the game, and handle SDL_Poll events
    // Should be called once per frame, before render
    extern void Update();
    // Quit, should be called once on exit.
    // Will call FreeScreen, SDL_Quit, and other functions
    // that need to be called on exit
    extern void Exit();
  }
}  // RLE 

// Alias namespaces
namespace RLEScreen = RLE::Screen; 
namespace RLEEngine = RLE::Engine;
// Alias classes
using RLEFont = RLE::Screen::Font;

#endif  // ENGINE_HPP_
