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

breadthFirst::breadthFirst(zone outline)
{
 this->layout = outline.layout;
 this->mapW = outline.mapW;
 this->mapH = outline.mapH;
  visited.resize(mapW, std::vector<bool>(mapH));
  distance.resize(mapW, std::vector<int>(mapH));
 int x, y;
 for (x = 0; x < this->mapW; x++)
 {
   for (y = 0; y < this->mapH; y++)
   {
     visited[x][y] = false;
     distance[x][y] = 0;
   }
 }
 
}

bool breadthFirst::inbounds(Point p)
{
  return p.x > 0 && p.x < mapW && p.y > 0 && p.y < mapH;
}

bool breadthFirst::bfs(Point start, Point fin)
{
 int i;
 int level = 0;
 Point current, next, mark={INF, INF};
 struct Edge node;
 node = {start, start};
 visited[start.x][start.y] = true;
 queue.push(start);
 camefrom.push(node);
 queue.push(mark);
 while (!queue.empty())
 {
  current = queue.pop();
  if (current == mark)
  {
    level++;
    queue.push(mark);
    current = queue.pop();
    if (current == mark) return false; 
  }
  if (current == fin) return true;
  for (auto dir : cmp.dir)
  {
   next = {current.x + dir.x, current.y + dir.y};
   if (visited[next.x][next.y] == false && inbounds(next))
   {
      std::cout<<next.x<<"/"<<next.y<<"\n";
      if (this->layout[next.x][next.y].blocks == false)
      {
    	  queue.push(next);
        node = {next,current};
        camefrom.push(node);
        distance[next.x][next.y] = level;
        visited[next.x][next.y] = true;
      }
   }
  }
 }
 return false;
}

std::vector<Point> breadthFirst::pathFind(Point start, Point fin)
{
  std::vector<Point> retpath;
  int i, p;
  bool yaynay = bfs(start, fin);
  if (yaynay == false)
  {
    retpath.push_back(start);
    return retpath;
  }
  Point current = fin, repeat;
  int list_size = camefrom.size();
  while (current != start)
  {
   for (i = 0; i < list_size; i++)
   {
     if (camefrom.at(i).at == current)
     {
	     current=camefrom.at(i).from;
       if (current == repeat)
         break;
       retpath.push_back(current);
       repeat = current;
     }
   }
  }
  retpath.push_back(start);
  std::reverse(retpath.begin(), retpath.end());
  return retpath;
}

void breadthFirst::reset()
{
  int x, y;
  for (x = 0; x < 80; x++)
  {
    for (y = 0; y < 40; y++)
    {
      visited[x][y] = false;
      distance[x][y] = 0;
    }
  }
}


}