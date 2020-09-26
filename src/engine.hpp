// Copyright (c) 2020, Ari Eythorsson
// See LICENSE.txt for more information

#ifndef ENGINE_HPP_
#define ENGINE_HPP_

class RLEConsole;

namespace RLE 
{
  namespace Screen 
  {
    extern RLEConsole *Root;
    // TODO: make CreateScreen a bool that can fail
	  // Create the screen of the game at RLEScreen::Root. 
    // Will be of type RLEConsole
    // as defined in screen.hpp/cpp
    // Usage:
	  //   RLE::CreateScreen(80, 50, "MyGame");
	  extern void CreateScreen(int width, int height, char const* title);
    // Frees the memory of the root screen created by CreateScreen
    // Should be called on exit
    extern void FreeScreen();
    // Returns true if the window (RLEScreen::Root) is still open
    // Used for game loop
    extern bool IsOpen;
  }  // Screen
  namespace Engine
  {
    // Used at the end of every loop by calling
    // SDL_Delay for a length of time that if called every frame
    // will make the game run at int fps frames per second
    // Basically, call at the end of every frame with your 
    // Preferred FPS
    extern void Delay(int fps);
    // Update the game, and handle SDL_Poll events
    // Should be called once per frame, before render
    extern void Update();
    // Render the screen, should be called once per frame
    // Called inside game loop, after update
    //extern void Render();
  }
}  // RLE 

// Alias namespaces
namespace RLEScreen = RLE::Screen; 
namespace RLEEngine = RLE::Engine;

#endif  // ENGINE_HPP_
