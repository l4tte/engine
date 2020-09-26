# RogueLikeEngine : RLE

## FAQ

### What is it
RLE is an engine designed specifically for roguelikes that takes everything complicated a roguelike dev has to do and boils it down into simple library functions.

### Why is it a thing
A library like this is definetly needed. In making my own roguelikes, or even just basic text programs, drawing to the screen is always excessively complicated.
If you're using SDL, then you have to deal with the con
Its worth noting that this library and [libtcod](https://github.com/libtcod/libtcod) is different.
Libtcod is more focused on probiding a basic roguelike framework to work on and make your own game, whereas RLE is to handle things like drawing to the screen,
generating random numbers/noise, etc.

### Documentation
Documentation isn't yet available. The library will be fully documented by the time it reaches 1.0, but currently the library isn't in a fully finished state and because of that documentation might change a good deal.

## Whats left to do?
 - [ ] Documentation of public API functions
 - [ ] Finish font class and allow for rendering text
 - [x] Working screen of variable size
 - [ ] Add setoptions function

## Known bugs
  - [x] Malloc complains on exit
