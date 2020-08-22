
#include <BearLibTerminal.h>
namespace mctk {
void render(zone outline)
{
 std::string dist = "-1234567890ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
 int x, y;
 for (x = 0; x < outline.mapW; x++)
 {
  for (y = 0; y < outline.mapH; y++)
  {
    
      
    if (outline.layout[x][y].blocks == false)
    {
        terminal_bkcolor("black");
        terminal_print(x, y, " ");
    } else {
      if (outline.ismaze)
      {
          terminal_bkcolor("grey");
          terminal_print(x, y, " ");
      } else {
        terminal_color("grey");
        terminal_print(x, y, ".");
      }
    }
    /*terminal_layer(2);
    if (outline.layout[x][y].level < dist.length())
    {
        terminal_printf(x,y,"%d", dist.at(outline.layout[x][y].level));
    }
    */
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