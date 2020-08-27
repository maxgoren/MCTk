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
SOFTWARE.b
******************************************************************************/
#define INF -666
namespace mctk {

bfDungeon::bfDungeon(zone outline)
{
 this->layout = outline.layout;
 this->mapW = outline.mapW;
 this->mapH = outline.mapH;
 this->hasmaze = outline.ismaze;
 seen.resize(mapW+2, std::vector<bool>(mapH+2));
 distance.resize(mapW+2, std::vector<int>(mapH+2));
 int x, y;
 for (x = 0; x < this->mapW; x++)
 {
   for (y = 0; y < this->mapH; y++)
   {
     seen[x][y] = false;
     distance[x][y] = INF;
     layout[x][y].x = x;
     layout[x][y].y = y;
   }
 }
 
}

bool bfDungeon::inbounds(Point p)
{
  return p.x > 0 && p.x < mapW-1 && p.y > 0 && p.y < mapH-1;
}


int bfDungeon::dist(Point a, Point b)
{
  int dx = a.x - b.x;
  int dy = a.y - b.y;
  float d = sqrtf(dx*dx+dy*dy);
  return (int)d; 
}

   
zone bfDungeon::getZone()
{
  zone retzone;
  retzone.mapW = mapW;
  retzone.mapH = mapH;
  retzone.layout = layout;
  retzone.ismaze = hasmaze;
  int x, y;
  for (x = 0; x < mapW; x++)
    for (y = 0; y < mapH; y++)
      if (!layout[x][y].blocks)
        retzone.openSpace.push_back(layout[x][y]);
  return retzone;
}
void bfDungeon::reset()
{
  int x, y;
  for (x = 0; x < 80; x++)
  {
    for (y = 0; y < 40; y++)
    {
      seen[x][y] = false;
      distance[x][y] = 0;
    }
  }
}

void bfDungeon::putWalls()
{
  int x, y;
  for (x = 0; x < mapW-1; x++)
  {
    for (y = 0; y < mapH - 1; y++)
    {
      if (distance[x][y] > 9)
        layout[x][y].blocks = true;
    }
  }
}

void bfDungeon::putDoors(std::vector<std::vector<Point>> wallvec)
{
  std::vector<Point> possiblesX;
  std::vector<Point> possiblesY;
  Point nd,nd2, nd3;
  for (auto vec : wallvec)
  {
    for (auto p : vec)
    {
      if (layout[p.x][p.y].blocks && !layout[p.x-1][p.y].blocks && !layout[p.x+1][p.y].blocks)
          possiblesX.push_back(p);
      if (layout[p.x][p.y].blocks && !layout[p.x][p.y-1].blocks && !layout[p.x][p.y+1].blocks)
          possiblesY.push_back(p); 
    }
    if (possiblesX.size() > 0)
    {
    nd = possiblesX.at(getrand(0,possiblesX.size()-1));
    layout[nd.x][nd.y].blocks = false;
    }
    if (possiblesY.size() > 0)
    {
    nd = possiblesY.at(getrand(0,possiblesY.size()-1));
    layout[nd.x][nd.y].blocks = false;
    }
    possiblesX.clear();
    possiblesY.clear();
  }

}

void bfDungeon::plantSeeds()
{
  int x[5], y[5];
  int i, numSeeds = 0;
  bool cont = false;
  std::vector<Point> seeds;
  Point next;

  while (numSeeds < 40)
  {
    x[0] = getrand(5, mapW/2);
    y[0] = getrand(5, mapH/2);
    x[1] = getrand(mapW/2, mapW-5);
    y[1] = getrand(5, mapW/2);
    x[2] = getrand(mapW/3, mapW - mapW/3);
    y[2] = getrand(8, mapH - 8);
    x[3] = getrand(5, mapW/2);
    y[3] = getrand(mapH/2, mapH-5);
    x[4] = getrand(mapW/2, mapW -5);
    y[4] = getrand(mapH/2, mapH - 5);
    i = getrand(0, 4); 
    next = {x[i],y[i]};
    if (seeds.size() < 1)
    {
        seeds.push_back(next);
    } else {
      for (auto s : seeds)
      {
        if (dist(next, s) > 25)
        {
          cont = true;
        }
        
      }
      if (cont)
      {
        seeds.push_back(next);
        numSeeds++;
        cont = false;
      }
    }
  }
  makeRooms(seeds);
}

void bfDungeon::makeRooms(std::vector<Point> seeds)
{
  bool makingRoom = true;
  int roomNum = 1;
  std::unordered_map<Point, int, hashkey> dist_now;
  std::vector<Point> walls;
  std::vector<std::vector<Point>> wallvec;
  Point current, next;
  std::array<Point, 8> cdir; 
  cdir[0]={-1, -1};  //NW
  cdir[7]={0, -1};   //N      Not using compass class so order of visit can be tweaked.
  cdir[3]={1, -1};   //NE  The order in which these are visited effects
  cdir[5]={1, 0};    //E    how we grow outwards.     8
  cdir[1]={1, 1};   //SE                         1  N 4
  cdir[6]={0, 1};    //S                        5  W    E  6
  cdir[2]={-1, 1};   //SW                         3  S 2
  cdir[4]={-1, 0};   //W                             7
  for (auto sd : seeds)
  {
   queue.push(sd);
   dist_now[sd] = 0;
   while (!queue.empty())
   {
    current = queue.front();
    queue.pop();
    if (dist_now[current] > 9)
      makingRoom = false;
    if (makingRoom)
    {
      for (auto dir : cdir)
      {
      next = {current.x + dir.x, current.y + dir.y};
      if (inbounds(next) && !seen[next.x][next.y])
        if (layout[next.x][next.y].blocks)
        {
          queue.push(next);
          seen[next.x][next.y] = true;
          if (dist_now.find(next) == dist_now.end())
          {
            dist_now[next] = dist_now[current] + 1;
            distance[next.x][next.y] = dist_now[current] + 1;
          }
          layout[next.x][next.y].blocks = false;
          if (dist_now[next] > 9)
            walls.push_back(layout[next.x][next.y]);
        }
      }
    } else {
      while (!queue.empty()) queue.pop();
      makingRoom = true;
      roomNum++;
      wallvec.push_back(walls);
      walls.clear();
    }
  }
  }
  putWalls();
  putDoors(wallvec);
}


}