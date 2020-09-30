#include "error.hpp"

#include <iostream>

void Error(char* src, char* msg)
{
  std::cout << "Error in " << src << ": " << msg << "\n";
  // Maybe print out stacktrace/other useful info?
}
