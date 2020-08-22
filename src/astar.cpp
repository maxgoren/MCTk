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
    
astar::astar(zone outline)
{
   this->layout = outline.layout;
   this->mapW = outline.mapW;
   this->mapH = outline.mapH;
   cdir[0]={0,1}; 
   cdir[2]={0,-1};         
   cdir[4]={-1,0};          
   cdir[6]={1,0};  

   cdir[1]={1,-1};       
   cdir[3]={-1,-1};     
   cdir[5]={-1,1};     
   cdir[7]={1,1};
}
int astar::heuristic(Point A, Point B)
{
   return std::abs(A.x - B.x) + std::abs(A.y - B.y);
}

bool astar::inBounds(Point p)
{
     return  p.x > 0 && p.x < mapW &&  p.y > 0 && p.y < mapH;
}

int astar::effort_now(Point A) const
{
   return A.costm;
}


void astar::addNeighbors(Point current, Point target)
{

int thiscost = 0;
for (auto dir : cdir)
{
   Point next= {current.x + dir.x, current.y + dir.y}; // dir.s );
   next.costm = layout[next.x][next.y].costm;
   if (inBounds(next) && layout[next.x][next.y].blocks == false)
   {
     for (auto all : effort)
     {
        thiscost = effort_now(next) + effort[current]; 
        if (effort.find(next) == effort.end() || thiscost < next.costm + effort[current]) 
        {
            effort[next] = thiscost;
            camefrom[next] = current;
            visited[next.x][next.y] = true;
            pque.emplace(next, thiscost + heuristic(next, target));
         }  
        }
      }
     }
}

bool astar::search(Point start, Point target)
{
   Point current;
   int level = 0;
   visited[start.x][start.y] = true;
   pque.emplace(start, start.costm);
   camefrom[start] = start;
   effort[start] = 0;
   while (!pque.empty())
   {
      current = pque.top().value;
      pque.pop();
      if (current == target)
          return true;
      addNeighbors(current, target);
   }
  return false;
}

std::vector<Point> astar::pathFind(Point start, Point target)
{
   this->reset();
   bool success = false;
   std::vector<Point> path;
   success = search(start, target);
   if (success == false)
   {
      path.push_back(start);
      return path;
   } else {
   Point current = target;
    while (current != start) 
    {
      path.push_back(current);
      current = camefrom[current];
      layout[current.x][current.y].s = '+';
    }
     path.push_back(start);
     std::reverse(path.begin(),path.end());
   }
   return path;
}


void astar::reset()
{
 while (!pque.empty())
 {
  pque.pop();
 }
 camefrom.clear();
 effort.clear();
}

}