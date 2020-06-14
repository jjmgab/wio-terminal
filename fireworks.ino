#include "lib/programExt.hpp"
#include "lib/fireworks.hpp"

ProgramExt p = ProgramExt();

void setup()
{
  randomSeed(analogRead(0));

  p.init();
  p.setTftBrightness(50);

  p.startFireworks(5);
}

void loop()
{
  p.loop();
}
