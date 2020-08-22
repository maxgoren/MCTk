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

djMapper::djMapper(zone outline)
{
   this->mapH = outline.mapH;
   this->mapW = outline.mapW;
   int x, y;
   for (x = 0; x < mapW;x++)
   {
     for (y = 0; y < mapH; y++)
     {
       seen[x][y] = false;
       distance[x][y] = INF;
     }
   }
 cdir[0]={0,1}; //N
 cdir[1]={0,-1}; //NE        
 cdir[2]={-1,0}; //E         
 cdir[3]={1,0}; //SE     
 cdir[4]={1,-1}; //S       
 cdir[5]={-1,-1}; //SW     
 cdir[6]={-1,1}; //W     
 cdir[7]={1,1}; //NW*/

}

bool djMapper::inBounds(Point p)
{
     return 0 <= p.x && p.x < this->mapW && 0 <= p.y && p.y < this->mapH;
}


field djMapper::setMapValue(field layout, Point start, int cut)
{
   reset();
   Point current, next, marker = {INF, INF}; 
   int level = 1;      
   distance[start.x][start.y] = level;
   seen[start.x][start.y] = true;
   que.push(start);   
   que.push(marker);   
   while (!que.empty())
   {
     current = que.pop();    
      if (current == marker) 
      { 
        level++; que.push(marker); 
        if (que.front() == marker) 
          break;                   
      } 
      if (level == cut)     
        break;
      for (auto dir : cdir) 
      {
        next = {current.x + dir.x, current.y + dir.y}; 
        if (inBounds(next) && layout[next.x][next.y].blocks == true)
        {
          if (seen[next.x][next.y] == false) 
          {
            que.push(next);         
            seen[next.x][next.y]=true;
            distance[next.x][next.y] = level;
            layout[next.x][next.y].level = level;
          }
        }
      }
   }
   que.clear();
   return layout;
}


field djMapper::inverseField(field layout, Point start, int cut)
{
    reset();
    Point current, next, marker = {INF, INF}; 
   int level = 100;
   cut = level - cut;      
   distance[start.x][start.y] = level;
   seen[start.x][start.y] = true;
   que.push(start);   
   que.push(marker);   
   while (!que.empty())
   {
     current = que.pop();    
      if (current == marker) 
      { 
        level--; que.push(marker); 
        if (que.front() == marker) 
          break;                   
      } 
      if (level == cut)     
        break;
      for (auto dir : cdir) 
      {
        next = {current.x + dir.x, current.y + dir.y}; 
        if (inBounds(next) && layout[next.x][next.y].blocks == true)
        {
          if (seen[next.x][next.y] == false) 
          {
            que.push(next);         
            seen[next.x][next.y]=true;
            distance[next.x][next.y] = level;
            layout[next.x][next.y].level = level;
          }
        }
      }
   }
   que.clear();
   return layout;
}

void djMapper::reset()
{
  int x, y;
   for (x = 0; x < mapW;x++)
   {
     for (y = 0; y < mapH; y++)
     {
       seen[x][y] = false;
       distance[x][y] = INF;
     }
   }
}

}