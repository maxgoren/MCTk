/****************************************************************
*  MIT License
* 
*  Copyright (c) 2020 Max Goren
*
* Permission is hereby granted, free of charge, to any person obtaining a copy
* of this software and associated documentation files (the "Software"), to deal
* in the Software without restriction, including without limitation the rights
* to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
* copies of the Software, and to permit persons to whom the Software is
* furnished to do so, subject to the following conditions:
*
* The above copyright notice and this permission notice shall be included in all
* copies or substantial portions of the Software.
*
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
* AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
* LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
* OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
* SOFTWARE.
***************************************************/
using namespace mctk;
dungeon::dungeon(zone outline)
{
    this->mapW = outline.mapW;
    this->mapH = outline.mapH;
    this->layout = outline.layout;
    this->hasmaze = outline.ismaze;
}
dungeon::~dungeon()
{
    for (auto r : rooms)
    {
        delete r;
    }
    for (auto c : cells)
    {
        delete c;
    }
}


void dungeon::dig(Room* current)
{
     int x, y;
  for (x = current->uL.x; x <= current->lR.x; x++)
  {
    for (y = current->uL.y; y <= current->lR.y; y++)
    {

        layout[x][y].blocks = false;
        layout[x][y].s = '-';
        layout[x][y].costm = 1;
        if (current->id == 77)
        {
            layout[x][y].s = '.';
            layout[x][y].costm = 2;
        }
    }
  }
}


bool dungeon::passCheck(Room* r)
{
if  (r->uL.x > mapW || r->uL.x <= 0 || r->uL.y > mapH || r->uL.y <= 0
    || r->lR.x > mapW || r->lR.x <= 0 || r->lR.y > mapH || r->lR.y <= 0 
    || r->w <= 0 || r->h <= 0) {
        return false;
    }
    r->uL.x = r->x; r->uL.y = r->y;
    r->lR.x = r->x + r->w; r->lR.y = r->y + r->h;
    r->cent.x = (r->uL.x + r->lR.x) / 2;
    r->cent.y = (r->uL.y + r->lR.y) / 2;
    return true;
}


Room::Room(int X, int Y, int W, int H, int ID)
{
 
  this->uL.x = X;
  this->uL.y = Y;
  this->lR.x = X + W;
  this->lR.y = Y + H;
  this->x = X;
  this->y = Y;
  this->w = W;
  this->h = H;
  this->cent.x = (this->uL.x + this->lR.x) / 2;
  this->cent.y = (this->uL.x + this->lR.y) / 2;
  this->id = ID;
 }

void dungeon::BSP()
{
    int level = 0;
    int MAX_SIZE = 12;
    Room* root;
    Room* toSplit;
    std::vector<Room*> A;
    std::vector<Room*> B;
    root = new Room(1,1,mapW-1,mapH-5, level);
    nodes.push(root);
    cells.push_back(root);
    while (!nodes.empty())
    {
       toSplit = nodes.front();
       nodes.pop();
     
        if ((toSplit->childA == NULL && toSplit->childB == NULL))
        {
          if ((toSplit->w < MAX_SIZE && toSplit->h < MAX_SIZE) || getrand(1,20) < 15)
          {
              if (toSplit->splitRoom())
              {
                nodes.push(toSplit->childA);
                nodes.push(toSplit->childB);
                cells.push_back(toSplit->childA);
                cells.push_back(toSplit->childB);
                level++;
              } 
            }
          }
      }
    Room* r;
    int rc = 0;
    for (auto h : cells)
    {
        r = h->makeRoom();
        if (passCheck(r))
        {
            rooms.push_back(r);
        } 
    } 
    if (rooms.size() < 13)
    {
      cells.clear();
      rooms.clear();
      halls.clear();
      BSP();
    } else {
    }
    for (auto r: rooms)
    {
        dig(r);
        if (getrand(1,50)>25)
         {
             A.push_back(r);
         } else {
             B.push_back(r);
         }
           rc++;
        if (rc == 2)
            spos = r->cent;
    }

    if (getrand(1,100) > 100)
    {
        conRoomStyle1(A);
        conRoomStyle2(B);
    } else {
        conRoomStyle1(B);
        conRoomStyle2(A);
    }
    for (auto j : halls)
    {
        dig(j);
    }
    outLine();
}

zone dungeon::getZone()
{
    int x, y;
    zone retzone;
    retzone.mapW = this->mapW;
    retzone.mapH = this->mapH;
    retzone.layout = this->layout;
    retzone.ismaze = this->hasmaze;
    for (x = 0; x < mapW; x++)
    {
     for (y = 0; y < mapH; y++)
     {
       if (layout[x][y].blocks == false)
       {
         retzone.openSpace.push_back(layout[x][y]);
       }
     }
    }
    return retzone;
}


bool Room::splitRoom()
{
    bool splitH;
    const unsigned int childMin = 16;
    int childMax;
    int split;
    if (this->childA != NULL && this->childB != NULL)
    {
        return false;
    }
    splitH = getrand(1,10) > 5;
    if (this->w > this->h && this->w / this->h >= 1.25)
    {
        splitH = false;
    } else if (this->h > this->w && this->h / this->w >= 1.25) {
        splitH = true;
    }

    childMax = (splitH ? this->h : this->w) - childMin;
    if (childMax < childMin)
    {
        return false; //too small to split.
    }
    split = getrand(childMin, childMax);
    if (splitH)
    {
        //horiz
        childA = new Room(this->uL.x, this->uL.y, this->w, split, this->id + 1);
        childB = new Room(this->uL.x, this->uL.y + split, this->w, this->h - split, this->id + 1);
    } else {
       //vert
       childA = new Room(this->uL.x, this->uL.y, split, this->h, this->id + 1);
       childB = new Room(this->uL.x + split, this->uL.y, this->w - split, this->h, this-> id + 1);
    }
   return true;
}



Room* Room::makeRoom()
{
    if (childA != NULL || childB != NULL)
    {
        if (childA != NULL)
        {
            childA->makeRoom(); //roomception
        }
        if (childB != NULL) 
        {
            childB->makeRoom();
        }
    } else {
             Point* roomSize;
             Point* roomPos;
             Room* room;
             roomSize = new Point();
		     roomPos = new Point();
             roomSize->x = getrand(6, this->w - 1); 
             roomSize->y = getrand(3, this->h - 1);
             roomPos->x = getrand(1, this->w - roomSize->x - 1);
             roomPos->y = getrand(1, this->h - roomSize->y - 1);
		     room = new Room(this->x + roomPos->x, this->y + roomPos->y, roomSize->x, roomSize->y, 0);
             return room;
    }
    return new Room(1,1,1,1,00);
}


Room* Room::getRoom()
{
    //Wow.
    return this;
}

bool Room::collision(Room other)
{
 if ((uL.x < other.lR.x) && (lR.x > other.uL.x) &&
     (uL.y < other.lR.y) && (lR.y > other.uL.y)) {
     return true; 
  } else {
  return false;
 }
}



void dungeon::basic(int numRoom, int maxSize)
{
 int i;
 int posx, posy, possize;
 int roomsMade = 0;
 int collisions = 0;
 int width = this->mapW;
 int height = this->mapH - 3;
 Room* posroom;
 Room scrSec1(1,1,width/2, height/2 - 1,0);                     //
 scrSect[0] = scrSec1;                                    //         uLs[0][4][1]suR
 Room scrSec2(width/2, 1, width/2 - 1, height/2 - 1,0);        //    lLs[2][5][3]slR
 scrSect[1] = scrSec2;                                    //               
 Room scrSec3(1, height/2, width/2, height/2,0);                //
 scrSect[2] = scrSec3;
 Room scrSec4(width/2, height/2, width/2 - 1, height/2 - 1,0);
 scrSect[3] = scrSec4;
 Room scrSec5(scrSec1.uL.x+10, 1, width/2, height/2-1,0);
 scrSect[4] = scrSec5;
 Room scrSec6(scrSec1.uL.x + 7, height/2, width/2,height/2 - 1, 0);
 scrSect[5] = scrSec6;
 while (roomsMade < numRoom)
 {
  possize = getrand(5, maxSize);
  switch (getrand(1,6))
  {
      case 1:
   	posx = getrand(scrSect[0].uL.x + 2, scrSect[0].uL.x + 5);
   	posy = getrand(scrSect[0].uL.y, scrSect[0].uL.y + 3);
      break;
      case 2:
   	posx = getrand(scrSect[1].uL.x-5, scrSect[1].lR.x - (possize) -5);
   	posy = getrand(scrSect[1].uL.y, scrSect[1].uL.y + 3);
      break;
      case 3:
	posx = getrand(scrSect[2].uL.x + 2, scrSect[2].uL.x + 5);
	posy = getrand(scrSect[2].uL.y + 1, scrSect[2].lR.y - (possize + 1));
      break;
      case 4:
	posx = getrand(scrSect[3].uL.x - 10, scrSect[3].lR.x - (possize) -5);
  	posy = getrand(scrSect[3].uL.y + 1, scrSect[3].lR.y - (possize + 1));
      break;
      case 5:
    posx = getrand(scrSect[4].uL.x, scrSect[4].uL.x + 5);
   	posy = getrand(scrSect[4].uL.y+2, scrSect[4].uL.y + 3);
      break;
      case 6:
    posx = getrand(scrSect[5].uL.x, scrSect[5].lR.x - (possize) -5);
   	posy = getrand(scrSect[5].uL.y, scrSect[5].uL.y + 3);
      break;
  }
  posroom = new Room(posx, posy, possize + (possize/2) , possize, 0);
  posroom->cent.x = (posroom->uL.x + posroom->lR.x) / 2;
  posroom->cent.y = (posroom->uL.y + posroom->lR.y) / 2;
  if (roomsMade > 0)
  {
     for (auto R : rooms)
     { if (posroom->collision(*R)) { collisions++; } }


     if (collisions == 0)
     {
       dig(posroom);
       rooms.push_back(posroom);
       roomsMade++;
       collisions = 0;
     } else {
       collisions = 0;
     }
   } else {
     
     dig(posroom);
     rooms.push_back(posroom);
     roomsMade++;
  }
  if (roomsMade == 3)
  {
   spos.y = rooms.at(2)->cent.y;
   spos.x = rooms.at(2)->cent.x;
  }
 }

   int ranLayout = getrand(1, 100);
  if (ranLayout < 30)
   {
     crNB1(rooms);
   } else if (ranLayout > 30 && ranLayout < 70) {
     crNB2(rooms);
   } else if (ranLayout > 70) {
       crNB1(rooms);
       crNB2(rooms);
   }
 outLine();
}

bool dungeon::inbounds(Point p)
{
  return p.x > 0 && p.x < mapW && p.y > 0 && p.y < mapH;
}

void dungeon::outLine()
{
 /*int x, y;
 for (x = 0; x < mapW; x++)
 {
  for (y = 0; y < mapH; y++)
  {
   if (inbounds(layout[x][y]))
   { 
    if (layout[x][y].blocks == false && layout[x+1][y].blocks == true)
    {
     layout[x+1][y].border = true;
    }
    if (layout[x][y].blocks == false && layout[x][y+1].blocks == true)
    {
     layout[x][y+1].border = true;
    }
    if (layout[x][y].blocks == false && layout[x-1][y].blocks == true)
    {
     layout[x-1][y].border = true;
    }
    if (layout[x][y].blocks == false && layout[x][y-1].blocks == true)
    {
     layout[x][y-1].border = true;
    }
    if (layout[x][y].blocks == false && layout[x-1][y].border == true && layout[x][y+1].border==true)
    {
      layout[x-1][y+1].border=true;
    }
    if (layout[x][y].blocks == false && layout[x-1][y].border == true && layout[x][y-1].border==true)
    {
      layout[x-1][y-1].border=true;
    }
    if (layout[x][y].blocks == false && layout[x+1][y].border == true && layout[x][y-1].border==true)
    {
      layout[x+1][y-1].border=true;
    }
    if (layout[x][y].blocks == false && layout[x+1][y].border == true && layout[x][y+1].border==true)
    {
      layout[x+1][y+1].border=true;
    }
    if (layout[x][y].border==true)
    {
        layout[x][y].s = '#';
        layout[x][y].costm = 0;
    }
   }
  }
 }*/
}