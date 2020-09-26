// Copyright (c) 2020, Ari Eythorsson
// See LICENSE.txt for more information

#include <iostream>
#include "engine.hpp"

int main()
{
  RLEScreen::CreateScreen(20, 20, "RL");
  while (RLEScreen::IsOpen) // While the screen is open
  {
   RLEEngine::Update();
   RLEEngine::Delay(60); // 60 FPS
  }
	return 0;
}
