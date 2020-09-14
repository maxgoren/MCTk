#include "landscape.h"

landscape::landscape()
{

}

field landscape::make_it(field layout, int mapW, int mapH)
{
    this->mapW = mapW;
    this->mapH = mapH;
    int x, y;
    for (x = 0; x < mapW; x++)
    {
        for (y = 0; y < mapH; y++)
        {
            layout[x][y] = {x,y,'#', 0, 1};
            layout[x][y].blocks = true;
            layout[x][y].populated = false;
            layout[x][y].color = 0xFFFF0000;
        }
    }
    std::cout<<"calling walk.\n";
    layout = biased_walk(layout, .53);
    return layout;
}



inline bool landscape::onmap(Point curr)
{
 return curr.x > 1 && curr.x < mapW && curr.y > 1 && curr.y < mapH; 
}

field landscape::biased_walk(field layout, float percent_clear)
{
  std::cout<<"Waling\n";
  std::array<Point, 4> cd;
  Point dxdy;
  Point current;
  Point next;
  int x;
  int y;
  int selector;
  int stepped = 0;
  double area = ((double)mapW * (double)mapH) / 4;
  double to_clear = area * percent_clear;
  cd[0] = {0, -1}; cd[3] = {0, 1};
  cd[1] = {-1, 0}; cd[2] = {1, 0};
  x = aux.getrand(20, mapW-20);
  y = aux.getrand(10, mapH-10);
  current = {x,y};
  layout[x][y].blocks = false;
  stepped++;
  while (stepped < to_clear)
  {
    selector = aux.getrand(0,3);
    if (current.x > (mapW-mapW/6))
    {
      if (aux.getrand(1,100) < 10)
        dxdy = {-1,0};
      else
        dxdy = cd[selector];
    } else if (current.x < mapW/6) {
      if (aux.getrand(1,100) < 10)
       dxdy = {1,0};
      else
       dxdy = cd[selector];
    } else if (current.y < 10) {
      if (aux.getrand(1,100)< 20)
       dxdy = {0,1};
      else
       dxdy = cd[selector];
    } else if (current.y > mapH-10) {
      if (aux.getrand(1,100) < 20)
       dxdy = {0,-1};
      else
       dxdy = cd[selector];
    } else {
       dxdy = cd[selector];
    }
    std::cout<<"Current: "<<current.x<<"/"<<current.y<<" dxdy: "<<dxdy.x<<"/"<<dxdy.y<<"\n";
    next = {current.x + dxdy.x, current.y + dxdy.y};
    if (onmap(next)) 
    { 
      std::cout<<"Trying: "<<next.x<<"/"<<next.y<<"...";
     if (layout[next.x][next.y].blocks == true)
     {
       layout[next.x][next.y].blocks = false;
       layout[next.x][next.y].color = 0xFFFF4400;
       layout[next.x][next.y].s = '-';
       stepped++;
       std::cout<<"accepted\n";
     }
    }
    std::cout<<"rejected\n";
    current = next;
  }
 return layout;
}


field landscape::play(field layout)
{
  int x, y;
  for (x = 0; x < 160; x++)
  {
    for (y = 0; y < 40; y++)
    {
       layout[x][y]={x,y,'#',0,1};
       layout[x][y].blocks = true;
       layout[x][y].color = 0xFFCECECE;
    }
  }
  for (x = 2; x < 15; x++)
  {
    for (y = 3; y < 15; y++)
    {
       layout[x][y].s = '.';
       layout[x][y].blocks = false;
       layout[x][y].color = 0xFFCEFFCE;
    }
  }
  for (x = 14; x < 55; x++)
  {
    for (y = 7; y < 15; y++)
    {
       layout[x][y].s = '.';
       layout[x][y].blocks = false;
       layout[x][y].color = 0xFFCEFFCE;
    }
  }
  for (x = 20; x < 70; x++)
  {
    for (y = 2; y < 6; y++)
    {
      layout[x][y].s = '.';
       layout[x][y].blocks = false;
       layout[x][y].color = 0xFFCEFFCE;
    }
  }
  for (x = 50; x < 80; x++)
  {
    for (y = 10; y < 15; y++)
    {
      layout[x][y].s = '.';
       layout[x][y].blocks = false;
       layout[x][y].color = 0xFFCEFFCE;
    }
  }
  for (x = 56; x < 64; x++)
  {
    for (y = 3; y < 15; y++)
    {
      layout[x][y].s = '.';
       layout[x][y].blocks = false;
       layout[x][y].color = 0xFFCEFFCE;
    }
  }
  return layout;
}