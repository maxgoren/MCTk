/****************************************************************************
 * MIT License

Copyright (c) 2020 Max Goren - maxgoren@icloud.com, https://www.maxcodes.info

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
******************************************************************************/
namespace mctk {
typedef std::vector<std::vector<Point>> field;
ent::ent(int x, int y, int id, char ch)
{
 this->pos.x = x;
 this->pos.y = y;
 this->ch[0] = ch;
 this->ch[1] = '\0';
 this->id = id;
   Point N({0,-1,'^'});
   Point S({0,1,'v'});
   Point E({1,0,'>'});
   Point W({-1,0,'<'});
   Point NW({-1,1});
   Point NE({1,1});
   Point SW({-1,-1});
   Point SE({1,-1});
   compass[0]=E; compass[1]=N; compass[2]=W; compass[3]=S;
   compass[4]=NW; compass[5]=SE; compass[6]=SW; compass[7]=NE;
}

bool ent::canMove(field layout, int x, int y)
{
 if (layout[x][y].blocks == true) {
    return true;
 } else {
   return false;
 }
}



void ent::move(field layout, int dx, int dy)
{
 if (canMove(layout, this->pos.x + dx,this->pos.y + dy))
 {
 this->pos.x += dx;
 this->pos.y += dy;
 }
}

void ent::render()
{
  terminal_layer(2);
  terminal_color("magenta");
  terminal_print(pos.x, pos.y, "G");
}



void ent::automove(field layout)
{
  int i;
  int bestValue = 1000; //dummy value arbitrarilly high to gaurentee first comparison sets a proper value.
  int distance;
  Point dir;
  Point best;   //the point chosen to move to.
  Point checking; //the point being analyzed
  //this is essentially Dijkstra's algorithm performed on an adjacency matrix.
  //we dont need a priority queue, because were simply picking the 
  //best priority out of four choices.
  for (i = 0; i < 4; i++)
  {                      
    dir = compass[i];          //loop through checking all the directions
    checking.x = pos.x + dir.x;
    checking.y = pos.y + dir.y;
    checking.level = layout[checking.x][checking.y].level;
    if (checking.level < bestValue && layout[checking.x][checking.y].blocks == true 
    && layout[checking.x][checking.y].populated == false)
    {                                   //If the value being checked is lower than the current lowest &&
      bestValue = checking.level;       // the point is one that can be walked on && theres not another 
      best = checking;                  //goblin/NPC already occupying the tile.
    }
  }
  
  layout[pos.x][pos.y].blocks = true;       //set the currently occupied point to
  layout[pos.x][pos.y].populated = false;    // make it unoccupied
  pos = best;                                        //set the goblins position as the one we chose as best
  layout[pos.x][pos.y].blocks = true;        //set the newly occupied current point to occupied. 
  layout[pos.x][pos.y].populated = false;
}
}