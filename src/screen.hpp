// Copyright (c) 2020, Ari Eythorsson
// See LICENSE.txt for more information

#ifndef SCREEN_HPP_
#define SCREEN_HPP_

#include <cstdint>

struct SDL_Window;
struct SDL_Renderer;
struct SDL_Texture;

class RLEConsole
{
  public:
    // RLEConsole initializer, create new console
    // Width: Width of screen in pixels
    // Height: Height of screen in pixels
    RLEConsole(int width, int height, int tilesize);
    // Free Window, Renderer, and Texture. Should be called only
    // Once in the internal function RLEEngine::Exit
    ~RLEConsole();
    // Will render the screen by copying the internal array of 
    // pixels to texture, the texture to a renderer, and then
    // presenting the renderer. Called once per frame.
    void Render();
    // Sets the value of a pixel on the screen. 
    // Will edit the int32_t* pixel array which is updated
    // in Render(). Mostly used internally.
    // Usage (Sets a single red pixel at 10, 10):
    //   SetPixel(10, 10, 0x00FF0000);
    void SetPixel(int x, int y, int32_t px);
  private:
    SDL_Window   *Window;
    SDL_Renderer *Renderer;
    SDL_Texture  *Texture;
    int width, height, tilesize, widthpx, heightpx;
    // The pixel buffer. Can be accessed with RLEConsole::SetPixel
    // TODO: Implement RLEConsole::SetPixel
    int32_t* Pixels;
};  // RLEConsole

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
    // Render the screen, should be called once per frame
    // Called inside game loop, after update
    extern void Render();
  }  // Screen
}  // RLE

#endif  // SCREEN_HPP_
