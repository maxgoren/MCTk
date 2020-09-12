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

drunk_walk::drunk_walk(zone outline)
{
     this->mapW = outline.mapW;
     this->mapH = outline.mapH;
     this->map = outline.layout;
     this->hasmaze = outline.ismaze;
     cd[0] = {0, -1}; cd[3] = {0, 1};
     cd[1] = {-1, 0}; cd[2] = {1, 0};
     
}

inline bool drunk_walk::onmap(Point curr)
{
 return curr.x > 1 && curr.x < mapW && curr.y > 1 && curr.y < mapH; 
}

void drunk_walk::walk(double toclear)
{
  std::stack<Point> backtrack;
  int stepped = 0;
  int i;
  double area = (mapW-2)*(mapH-2);
  double goal = area * toclear;
  Point current = {getrand(2,mapW-2), getrand(2,mapH-2)};
  map[current.x][current.y].blocks = false;
  stepped++;
  std::cout<<"First: "<<current.x<<"/"<<current.y<<"\n";
  Point next;
  while (stepped < goal)
  {
    i = getrand(0,3);
    next = {current.x + cd[i].x, current.y+cd[i].y};
    if (onmap(next))
    {
           map[next.x][next.y].blocks = false;
           backtrack.push(next);
           stepped++;
           current = next;      
    } else {
      i = getrand(1,5);
      switch(i)
      {
        case 1: 
                current.x = mapW/2;
                current.y = mapH/2;
                break;
        case 2:
                current.x = mapW/4;
                current.x = mapH/4;
                break;
        case 3: 
                current.x = mapW/4;
                current.y = mapH - mapH/4;
                break;
        case 4:
                current.x = mapW - mapW/4;
                current.y = mapH/4;
                break;
        case 5:
                current.x = mapW - mapW/4;
                current.y = mapH - mapH/4;
      }
    }
  }
  while (!backtrack.empty())
  {
      //hit me baby one more time..
      next = backtrack.top();
      backtrack.pop();
      i = getrand(0,3);
      next = {current.x + cd[i].x, current.y+cd[i].y};
      if (onmap(next))
      {
           map[next.x][next.y].blocks = false;
           current = next;      
      }
  }
}

zone drunk_walk::getZone()
{
  zone retzone;
  retzone.mapW = mapW;
  retzone.mapH = mapH;
  retzone.layout = map;
  retzone.ismaze = hasmaze;
  int x, y;
  for (x = 0; x < mapW; x++)
    for (y = 0; y < mapH; y++)
      if (!map[x][y].blocks)
        retzone.openSpace.push_back(map[x][y]);
  return retzone;
}

}