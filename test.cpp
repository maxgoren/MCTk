#include "BearLibTerminal.h"
#include "mctk.h"


void BLT_init()
{
  terminal_open();                     
  terminal_set("window: size=80x40");
  terminal_refresh();
}

void BLT_cleanup()
{
  terminal_close();
}
int main()
{
  BLT_init();
  mctk::GameEngine* engine;
  engine = new GameEngine();
  engine->mainLoop();
  BLT_cleanup();
  return 0;
}
