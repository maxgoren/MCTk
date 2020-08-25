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

dfMaze::dfMaze(zone outline)
{
 int x, y;
 this->mapW = outline.mapW;
 this->mapH = outline.mapH;
 this->layout = outline.layout;
 seen.resize(outline.mapW, std::vector<bool>(outline.mapH));
 for (x = 0; x < mapW; x++)
    {
      for (y = 0; y < mapH; y++)
      {
        seen[x][y] = false;
      }
    }
}

bool dfMaze::OOB(Point p)
{
  return p.x > 0 && p.x < mapW-1 && p.y > 0 && p.y < mapH-1; 
}

zone dfMaze::getZone()
{
  zone retmaze;
  retmaze.ismaze = true;
  retmaze.layout = this->layout;
  retmaze.mapH = this->mapH;
  retmaze.mapW = this->mapW;
  int x,y;
  for (x = 0; x < mapW; x++)
   {
     for (y = 0; y < mapH; y++)
     {
       if (layout[x][y].blocks == false)
       {
         retmaze.openSpace.push_back(layout[x][y]);
       }
     }
   }
  return retmaze;
}


void dfMaze::makeMaze()
{
 int i;
 Point start = {mapW/2, mapH/2};
 Point current, next, rdir;
 staq.push(start);
 while (!staq.empty())
 {
  current = staq.top();
  staq.pop();
   for (i = 0; i < 4; i++)
   {
     next = {current.x + cmp.dir[i].x, current.y + cmp.dir[i].y};
     if (seen[next.x][next.y] == false)
     {
        if (OOB(next))
        {
	        staq.push(next);
          mbe.push_back(next);
          seen[next.x][next.y] = true;
          layout[next.x][next.y].ismaze = true;
        }
     }
    }
   if (!mbe.empty()) {
      rdir = mbe.at(getrand(0,mbe.size()-1));
      layout[rdir.x][rdir.y].blocks = false;
      layout[rdir.x][rdir.y].ismaze = true;
      mbe.clear();
    }

 }
}

compMaze::compMaze(mctk::zone outline)
{
    seen.resize(outline.mapW, std::vector<bool>(outline.mapH));
    this->mapW = outline.mapW;
    this->mapH = outline.mapH;
    this->layout = outline.layout;
    this->width = mapW;
    this->height= mapH;
    int x, y;
    for (x = 0; x < mapW; x++)
    {
      for (y = 0; y < mapH; y++)
      {
        seen[x][y] = false;
      }
    }
}

zone compMaze::getZone()
{
   int x,y;
   zone retzone;
   retzone.ismaze = true;
   retzone.mapH = this->mapH;
   retzone.mapW = this->mapW;
   retzone.layout = this->layout;
   for (x = 2; x < mapW; x++)
   {
     for (y = 2; y < mapH; y++)
     {
       if (layout[x][y].blocks == false)
       {
         retzone.openSpace.push_back(layout[x][y]);
       }
     }
   }
   std::cout<<retzone.openSpace.size();
   return retzone;
}


bool compMaze::OOB(Point n)
{
    return n.x > 0 && n.y > 0 && n.x < width - 1 && n.y < height - 1;
}

std::vector<std::tuple<int, Point>> compMaze::checkAdj(Point n)
{
    std::vector<std::tuple<int, Point>> mbe;
    int i;
    Point test, dir;
    for (i = 0; i < 4; i++)
    {
        dir = cmp.dir[i];
        test = {n.x + dir.x, n.y + dir.y};
        if (OOB(test)) {
            if (seen[test.x][test.y] == false)
            {
                seen[test.x][test.y] = true;
                mbe.push_back(std::make_tuple(i, test));
                backtrack.push(test);
            }
        } 
    }
  return mbe;
} 

void compMaze::removeEdge(std::tuple<int, Point> t)
{
    Point n; int d;
    std::tie(d, n) = t;
    switch (d)
    {
        case 0: layout[n.x][n.y].bottom = false; break;
        case 1: layout[n.x][n.y].top = false; break;       //removing the inverse
        case 2: layout[n.x][n.y].right = false; break;     //of came from;
        case 3: layout[n.x][n.y].left = false; break;
    }
    seen[n.x][n.y] = true;
    layout[n.x][n.y].blocks = false;
    layout[n.x][n.y].ismaze = true;
}



void compMaze::start()
{
    int i;
    std::vector<std::tuple<int, Point>> mbe;
    totalCells = this->mapW * this->mapH;
    visited = 0;
    Point current = {getrand(0,4),getrand(1,7)};
    Point fin = {getrand(62,79),getrand(35, 39)};
    Point test;
    std::tuple<int,Point> cm;
    seen[current.x][current.y] = true;
    layout[current.x][current.y].blocks = false;
    layout[current.x][current.y].ismaze = true;
    visited++;
    while (visited < totalCells)
    {
        mbe = checkAdj(current);
        if (!mbe.empty())
        {
            std::random_shuffle(mbe.begin(), mbe.end());
            cm = mbe.at(getrand(0,mbe.size() - 1));
            removeEdge(cm);
            std::tie(i, test) = cm;
            switch(i)
            {   
                case 0:  layout[current.x][current.y].top = false; break;
                case 1:  layout[current.x][current.y].bottom = false; break;
                case 2:  layout[current.x][current.y].left = false; break;
                case 3:  layout[current.x][current.y].right = false; break;
            }
             seen[current.x][current.y]= true;
             layout[current.x][current.y].blocks = false;
             layout[current.x][current.y].ismaze = true;
            backtrack.push(current);
            current = test;
            visited++;
        } else {
            if (!backtrack.empty())
            {
                current = backtrack.top();
                backtrack.pop();
            } else {
                break;
            }
        }
    }
}


}