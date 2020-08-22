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
 this->mapW = outline.mapW;
 this->mapH = outline.mapH;
 this->layout = outline.layout;
 dir[0]={0,1}; //N
 dir[1]={0,-1}; //NE        
 dir[2]={-1,0}; //E         
 dir[3]={1,0}; //SE     
 dir[4]={1,-1}; //S       
 dir[5]={-1,-1}; //SW     
 dir[6]={-1,1}; //W     
 dir[7]={1,1}; //NW*/
 //yeah?
}

bool dfMaze::OOB(Point p)
{
  return p.x > 0 && p.x < mapW-1 && p.y > 0 && p.y < mapH-1; 
}

zone dfMaze::getMaze()
{
  zone retmaze;
  retmaze.ismaze = true;
  retmaze.layout = this->layout;
  retmaze.mapH = this->mapH;
  retmaze.mapW = this->mapW;
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
  current = staq.pop();
   for (i = 0; i < 4; i++)
   {
     next = {current.x + dir[i].x, current.y + dir[i].y};
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

}