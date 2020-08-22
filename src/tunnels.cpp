
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
void dungeon::conRoomStyle1(std::vector<Room*> path)
{
  int ax,bx;
  int ay,by;
  int x, y, w , h;
  Room* start;
  Room* fin;
  Room* tunnelA;
  Room* tunnelB;
  int i = 0;
  int r;
  
 
  for ( r = 0; r < path.size() - 1; r++)
  {
   start = path[i]->getRoom();
   fin = path[i+1]->getRoom();
   if (start->cent.x <= fin->cent.x)
   {
      x = start->cent.x;
      y = start->cent.y;
      w = (fin->cent.x + start->cent.x) / 2;
      tunnelA = new Room(x, y, w, 1, 77);
      if (passCheck(tunnelA))
        halls.push_back(tunnelA);

      x = fin->cent.x;
      y = fin->cent.y;
      w = (fin->cent.x + start->cent.x) / 2;
      tunnelB = new Room(x, y, w, 1, 77);
      if (passCheck(tunnelB))
        halls.push_back(tunnelB);

   }

      x = (fin->cent.x + start->cent.x) / 2;
      y = start->cent.y;
      h = fin->cent.y - start->cent.y;
      tunnelA = new Room(x,y,2,h,77);
      if (passCheck(tunnelA))
         halls.push_back(tunnelA);
      
    i++;
  }
  

}

void dungeon::conRoomStyle2(std::vector<Room*> path)
{
 int x, y;
 int w, h;
 int ax, ay;
 int bx, by;
 Room* start;
 Room* fin;
 Room* tunnelA;
 Room* tunnelB;
 int r, i=0;
 for (r = 0; r < path.size() - 1; r++)
 {
    start = path[i]->getRoom();
    fin   = path[i + 1]->getRoom();

    x = start->cent.x;
    y = start->cent.y;
    h = (start->cent.y + fin->cent.y)/2;

    tunnelA = new Room(x, y, 1, h, 77);
    x = fin->cent.x;
    y = fin->cent.y;
    h = (start->cent.y + fin->cent.y) / 2;

    tunnelB = new Room(x,y,1,h, 77);
   if (passCheck(tunnelA))
   {     
        halls.push_back(tunnelA);
    }
    if (passCheck(tunnelB))
    {
        halls.push_back(tunnelB);
    }


   x = start->cent.x;
   y = start->cent.y;
   w = (fin->cent.x + start->cent.x)/2;
   tunnelA = new Room(x,y,w,1, 77);

   x = fin->cent.x;
   y = fin->cent.y;
   w = (start->cent.x + fin->cent.x) /2;
   tunnelB = new Room(x,y,w,1, 77);
   
   if (passCheck(tunnelA))
   {
        halls.push_back(tunnelA);
   }

   if (passCheck(tunnelB))
   {
        halls.push_back(tunnelB);
   }
  

  i++;
 }
}

void dungeon::crNB1(std::vector<Room*> rooms)
{
  int ax,bx;
  int ay,by;
  Room* start;
  Room* fin;
  int i = 0;
  int r;
  for ( r = 0; r < rooms.size() - 1; r++)
  {
   start = rooms[i];
   fin = rooms[i+1];
   if (start->cent.x <= fin->cent.x)
   {
      for (ax = start->cent.x; ax <= (fin->cent.x + start->cent.x) / 2; ax++)
      {
	      layout[ax][start->cent.y].blocks = false;
      }
      for (bx = fin->cent.x; bx >= (fin->cent.x + start->cent.x) / 2; bx--)
      {
        layout[bx][fin->cent.y].blocks = false;
      }
   } else {
      for (ax = start->cent.x; ax >= (fin->cent.x + start->cent.x) / 2; ax--)
      {
        layout[ax][start->cent.y].blocks = false;
      }
      for (bx = fin->cent.x; bx <= (fin->cent.x + start->cent.x) / 2; bx++)
      {
        layout[bx][fin->cent.y].blocks = false;
      }
   }
   if (start->cent.y <= fin->cent.y)
   {
      for (ay = start->cent.y; ay <  fin->cent.y; ay++)
      {
         layout[ax][ay].blocks = false;
         layout[ax+1][ay].blocks = false;
      }
   } else {
      for (by = fin->cent.y; by <= start->cent.y; by++)
      {
        layout[bx][by].blocks = false;
        layout[bx-1][by].blocks = false;
        layout[bx][by].level = 77;
      }   
   }
  i++;
  }

}

void dungeon::crNB2(std::vector<Room*> rooms)
{
 int x, y;
 int ax, ay;
 int bx, by;
 Room* start;
 Room* fin;
 int r, i=0;
 for (r = 0; r < rooms.size() - 1; r++)
 {
  start = rooms[i];
  fin = rooms[i + 1];
  if (start->cent.y <= fin->cent.y)
  {
    for (ay = start->cent.y; ay <= (start->cent.y + fin->cent.y) / 2; ay++)
    {
   	layout[start->cent.x][ay].blocks = false;
     layout[start->cent.x+1][ay].blocks=false;
    }
    for (by = fin->cent.y; by >= (start->cent.y + fin->cent.y) / 2; by--)
    {
        layout[fin->cent.x][by].blocks = false;
        layout[fin->cent.x-1][by].blocks=false;
    }
  } else {
    for (ay = start->cent.y; ay >= (start->cent.y + fin->cent.y) / 2; ay--)
    {
      layout[start->cent.x][ay].blocks = false;
      layout[start->cent.x-1][ay].blocks = false;
    }
    for (by = fin->cent.y; by <= (start->cent.y + fin->cent.y) / 2; by++)
    {
     layout[fin->cent.x][by].blocks = false;
     layout[fin->cent.x+1][by].blocks=false;
    }
  }
  if (start->cent.x <= fin->cent.x)
  {
   for (ax = start->cent.x; ax <= fin->cent.x; ax++)
   {
     layout[ax][ay].blocks = false;
   }
  } else {
   for (bx = fin->cent.x; bx <= start->cent.x; bx++)
   {
     layout[bx][by].blocks = false;
   }
  }
  i++;
 }
}

}