
#include <BearLibTerminal.h>
namespace mctk {
void render(zone outline)
{
 int x, y;
 for (x = 0; x < outline.mapW; x++)
 {
  for (y = 0; y < outline.mapH; y++)
  {
    if (outline.ismaze == true)
    {
       terminal_layer(0);
       if (outline.layout[x][y].blocks == true)
        {
        terminal_bkcolor("black");
        terminal_print(x, y, " ");
        } else {
        terminal_bkcolor("blue");
        terminal_print(x, y, " ");
        }
    } else {
        terminal_print(x,y, ".");
    }
    if (outline.layout[x][y].border == true)
    {
        terminal_layer(0);
        terminal_bkcolor("grey");
        terminal_print(x, y, " ");
    }
   }
  }
} 

}