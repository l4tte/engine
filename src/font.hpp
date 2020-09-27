#ifndef FONT_HPP_
#define FONT_HPP_

namespace RLE
{
  namespace Screen
  {
    class Font
    {
      public:
        Font(char* path, char* letters);
      private:
        char* path;
        char* letters;
    };  // Font
  }  // Screen
}  // RLE

#endif
