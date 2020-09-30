// Copyright (c) 2020, Ari Eythorsson
// See LICENSE.txt for more information

#include <iostream>
#include "engine.hpp"

void RLE::Init()
{
  RLEScreen::CreateScreen(15, 20, 20, "RL");
  RLEScreen::Root->SetFont("terminal.bmp", 16, 16);
}

int px = 0;
int py = 0;

void RLE::Update()
{
  if (RLEScreen::Root->IsKeyDown('d'))
  {
    px++;
  } else if (RLEScreen::Root->IsKeyDown('a'))
  {
    px--;
  }

  if (RLEScreen::Root->IsKeyDown('s'))
  {
    py++;
  } else if (RLEScreen::Root->IsKeyDown('w'))
  {
    py--;
  }
  

  RLEScreen::Root->SetChar(px, py, {'@'});
}
