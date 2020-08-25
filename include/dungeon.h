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



namespace mctk {

class Room {
public:
 Point uL;
 Point lR;
 Point cent;
 int x, y, w, h;
 int id;
 bool collision(Room other); 
 Room* childA = NULL;
 Room* childB = NULL;
 bool splitRoom();
 Room* makeRoom();
 Room* getRoom();
 Room(int x, int y, int w, int h, int ID);
 Room() = default;
};

class dungeon {
public:
bool hasmaze;
int mapW;
int mapH;
Point spos;
Point stairsDown;
Point fovPoint;
field layout;
std::deque<Room*> halls;
std::vector<Room*> rooms;
std::vector<Room*> cells;
std::queue<Room*> nodes;
std::array<Room, 7> scrSect;
bool passCheck(Room*);
void render(dungeon*);
void dig(Room*);
void outLine();
void basic(int, int);
bool inbounds(Point p);
zone getZone();
void placeStairs(Point);
void BSP();
void conRoomStyle1(std::vector<Room*>);
void conRoomStyle2(std::vector<Room*>);
void crNB1(std::vector<Room*>);
void crNB2(std::vector<Room*>);
dungeon(mctk::zone outline);
~dungeon();
};

}