// Copyright (c) 2020, Ari Eythorsson
// See LICENSE.txt for more information

#ifndef SCREEN_HPP_
#define SCREEN_HPP_

#include <inttypes.h>

struct SDL_Window;
struct SDL_Renderer;
struct SDL_Texture;

#include "font.hpp"

struct Color {
  int r;
  int g;
  int b;
};

struct Tile {
  int Ch;
  Color Col = {0, 0, 0};
};

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

    // Clear the screen, mostly used internally in Render(),
    // Will memset the pixels to all white
    void Clear();

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

    // Will set the font of the terminal to a certain bmp font
    // Usage:
    //   SetFont("terminal.png", RLE_FONT_TERMINAL, 16, 16);
    void SetFont(char* Path, int Rows, int Cols, int* Letters=(int*)RLE_FONT_TERMINAL);
 
    // Set a char on an x and y position on screen
    // Usage:
    //   SetChar(15, 15, 'x');
    void SetChar(int x, int y, Tile tile);

    // Gets the status of a key/if its down
    // OR Gets the status of a key if first pressed this frame
    // Usage (See if 'c' key is down regardeless of repeat):
    //   IsKeyDown('c');
    // Usage (See if 'c' key was pressed this frame):
    //   IsKeyDown('c', true);
    bool IsKeyDown(int keycode);

    // Internal function.
    // Sets KeyboardStateOld to KeyboardState
    // Sets KeyboardState to current KeyboardState
    void KeyboardStateUpdate();

    // Used only internally
    // Will modify KeyboardState with given key
    // Will set KeyboardState[key] to val
    void KeyPressed_(int key, bool val);

private:
    SDL_Window   *Window;
    SDL_Renderer *Renderer;
    SDL_Texture  *Texture;
    Tile         *Tiles;
    RLE::Screen::Font *CurrentFont;
    int width, height, tilesize, widthpx, heightpx;
    int32_t* Pixels;
    int  KeyboardStateOld[256];
    int  KeyboardState[256];

    // Internal function to render tiles
    void RenderTile(int x, int y, Tile T);
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
	  //   RLE::CreateScreen(16, 80, 50, "MyGame");
	  extern void CreateScreen(int tilesize, int width, int height, char const* title);

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
