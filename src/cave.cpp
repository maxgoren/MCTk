namespace mctk {

Cave::Cave(zone outline)
{
    int x,y;
    this->mapW = outline.mapW;
    this->mapH = outline.mapH;
    this->temp = outline.layout;
    this->hasmaze = outline.ismaze;
    layout.resize(mapW, std::vector<Point>(mapH));
    temp.resize(mapW, std::vector<Point>(mapH));

  cdir[0] = {0,-1}; cdir[1] = {0,1};
  cdir[2] ={-1,1}; cdir[3] = {1,-1};
  cdir[4] = {1,0}; cdir[5] = {-1,0};
  cdir[6] = {-1,-1}; cdir[7] = {1,1};
}

field Cave::place_seed(field seed)
{
    std::list<Point> automaton;
    int minX = 3;
    int maxX = mapW - 2;
    int minY = 3;
    int maxY = mapH-2;
    double area = ((mapW -2) - 4) * ((mapH-2) - 3);
    double to_fill = area * .45;
    int accepted = 0;
    int x, y;
    Point perhaps;
    while (accepted < to_fill)
    {
        x = getrand(minX, maxX);
        y = getrand(minY, maxY);
        perhaps = {x,y};
        if (automaton.size() < 1)
        {
            automaton.push_back(perhaps);
            accepted++;
            seed[x][y].blocks = true;
        } else if (std::find(automaton.begin(), automaton.end(), perhaps) == automaton.end()) {
            automaton.push_back(perhaps);
            accepted++;
            seed[x][y].blocks = true;
        } else {
            do
            {
                x = getrand(minX, maxX);
                y = getrand(minY, maxY);
                perhaps = {x,y};  
            } while (std::find(automaton.begin(), automaton.end(), perhaps) != automaton.end());
            automaton.push_back(perhaps);
            seed[x][y].blocks = true;
            accepted++;   
        }
    }
    return seed;
}

field Cave::four_five(field working)
{
   int p;
   color_t dirt;
   color_t stone;
  int x, y, t;
  Point current;
  std::unordered_map<Point, bool, hashZ> wall;
  terminal_layer(0);
  terminal_bkcolor("black");
  for (x = 3; x < mapW-2; x++)
  {
      for (y = 3; y < mapH - 2; y++)
      {
          t = count_neightbors(working[x][y], working);
          if (working[x][y].blocks && t >= 4)
          {
              wall[working[x][y]] = true;
              terminal_print(x,y, "#");
          } else if (!working[x][y].blocks && t >= 5) {
              wall[working[x][y]] = true;
              terminal_print(x,y, "#");
          } else {
              wall[working[x][y]] = false;
                terminal_print(x,y, " ");
          }
      }
  }
  for (auto cell : wall)
  {
      if (cell.second == true)
      {
          
          working[cell.first.x][cell.first.y].blocks = true;

      } else {
          
          working[cell.first.x][cell.first.y].blocks = false;
      }
  }
  terminal_refresh();
  return working;
}

//This function returns the number of cells which
//are blocking, for use in the four_five() function 
int Cave::count_neightbors(Point p, field working)
{
    int neighbors = 0;
    Point test;
    for (auto d : cdir)
    {
        test = {p.x + d.x, p.y + d.y};
        if (working[test.x][test.y].blocks)
        {
            neighbors++;
        }
    }
    return neighbors;
}

//this isnt neccessary, it just makes a nice border
//around the caves.
void Cave::prep_fields()
{
    int x, y, i;
    
    for (x = 0; x < mapW; x++)
    {
        for (y = 0; y < mapH; y++)
        {
            
            temp[x][y].blocks = true;
            temp[x][y].populated = false;
            temp[x][y].x = x;
            temp[x][y].y = y;
            temp[x][y].color=0xAACECECE;
        }
    }
    for (x = 3; x < mapW-2; x++)
    {
        for (y = 2; y < mapH - 2; y++)
        {
            temp[x][y].blocks = false;
            temp[x][y].x = x;
            temp[x][y].y = y;
        }
    }
    
}


zone Cave::getZone()
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
//This function controls the whole show

void Cave::make_cave()
{
    int i, x, y, p;
    color_t stone;
    color_t dirt;
    std::cout<<"Prepping Fields\n";
    prep_fields();
    std::cout<<"Setting Seed\n";
    temp = place_seed(temp);
    std::cout<<"Automaton: ";
    
    for (i = 0; i < 5; i++)
    {
        std::cout<<i<<" ";
        temp = four_five(temp);
    }
    std::cout<<"\n Automota Done. Beginning flood fill...\n";
    temp = flood_fill(temp);
    std::cout<<"Flood Fill Done, Beginning colorizing...\n";
    for (x = 0; x < mapW; x++)
    {
        for (y = 0; y < mapH; y++)
        {
            layout[x][y] = temp[x][y];
          
          if (layout[x][y].blocks)
          {
            p = getrand(1,4);
            switch (p)
            {
                case 1: stone = 0xFF60676b; break;
                case 2: stone = 0xFF888CAD; break;
                case 3: stone = 0xFFA9A9A9; break;
                case 4: stone = 0xFFAC7954; break;
            }
            layout[x][y].blocks = stone;
          } else {
             p = getrand(1,4);
             switch (p)
             {
                case 1: dirt = 0xFFDEB887; break;
                case 2: dirt = 0xFFF4A460; break;
                case 3: dirt = 0xFFA0522D; break;
                case 4: dirt = 0xFFF4A460; break;
             }
             layout[x][y].color = dirt;
          }

        }
    }
    std::cout<<"Map Ready.\n";
}


//This a a Basic Beadth first search flood fill
//which starts from multiple points. This ensures
//that there are no unreachable areas of the Cave.
field Cave::flood_fill(field working)
{
  Point current, next, visiting;
  std::queue<Point> frontier;
  std::vector<std::vector<bool>> seen;
  seen.resize(mapW, std::vector<bool>(mapH));
  for (auto sb : seen)
    for (auto bs : sb)
      bs = false;
  for (auto i = 0; i <5 ; i++)
  {
  do
  {
    current = {getrand(3,mapW-3), getrand(4,mapH-4)};
  } while (working[current.x][current.y].blocks);
  frontier.push(current);
  seen[current.x][current.y] = true;
  }
  while (!frontier.empty())
  {
      visiting = frontier.front();
      frontier.pop();
      for (auto d : cdir)
      {
          next = {d.x + visiting.x, d.y + visiting.y};
          if (seen[next.x][next.y] == false && working[next.x][next.y].blocks == false)
          {
            frontier.push(next);
            seen[next.x][next.y] = true;
          }
      }
  }
  int x,y;
  for (x = 0; x < mapW; x++)
  {
      for (y = 0; y < mapH; y++)
      {
          if (!seen[x][y] && !working[x][y].blocks)
             working[x][y].blocks = true;
      }
  }
    return working;
}

}