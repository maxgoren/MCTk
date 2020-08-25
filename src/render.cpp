
#include <BearLibTerminal.h>
namespace mctk {
void render(zone outline, bool showingDmap)
{
 float mix;
 std::string dist = "-1234567890ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
 int x, y;
 for (x = 0; x < outline.mapW; x++)
 {
  for (y = 0; y < outline.mapH; y++)
  {
    
      
    if (outline.layout[x][y].blocks == false)
    {
        terminal_color(fadeColors(red, yellow, .76));
        terminal_print(x, y, "-");
    } else {
        terminal_color("grey");
        terminal_print(x, y, "%s");
    }

    if (showingDmap == true)
    {
        terminal_layer(2);
        terminal_color(0x88FF0000 * .75);
        if (outline.layout[x][y].level < dist.length())
        {
            mix = outline.layout[x][y].level/2;
            terminal_color(fadeColors(red, blue, mix/10));
            if (mix*2 > 20)
                terminal_color(fadeColors(blue, green, mix/10));
            terminal_printf(x,y,"%c", dist.at(outline.layout[x][y].level));
        }
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