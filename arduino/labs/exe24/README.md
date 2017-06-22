# Algo
a bit of everything
    
  
### Drawing primitives 3.5 Breakout TFT (Arduino)

> fritzing diagram for standard design
> or image

Basic program flow is:
+ `setup()` runs some color/geometry tests (standard tests provided by Adafruit) - `testFilledCircles()`, `testCircles()`
+ `loop()` opens serial console and waits for a command - once a command routine starts, it will block the flow till it's finished - commands from the following:
  + `circle` | `rectangle` | `line` | `triangle` - geometric primitives - wrappers over the `Adafruit GFX` library.
  + `car` | `house` - some basic geometry stuff
  + `clear` - resets content on screen `tft.fillScreen(BLACK);`

Obs: Some additional utility functions are available: `readInput()`, `readString()`, `readColor()`
