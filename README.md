# MCTk
---------------
An adjunct Library designed to work with BearLibTerminal for Roguelike and other 2D game development.

  BearLibTerminal is a popular choice amongst people interested in developing Roguelike and other 2D games.
What it lacks in features compared to other libraries such as the venerable libTCOD (The Doryen library)
it more than makes up for with its light implementation, easy syntax, and lightweight performance.
  MCTk is a collection of algorithms, containers, datastructes and functions  written in modern
C++ to address some of the features that are present in other libraries but lacking out of the box
with BearLibTerminal. 
A few examples of whats offered: is A* path finding, a Dijkstra Map generator,
Random integer and float generators, Perlin noise, and a maze generator, BSP dungeon generator,
and an interface for BLT's color_t type, just to name a few. A full list of 
what is implemented is below. This is a work in progress, so not all of the bugs
have been shaken out. More features will be added regularly.
As of now mctk is a header based library. when a -STABLE version is reached a dynamic library
versison will also be made available.

## How it works
--------------


	Once bearlibterminal launches the console window, aside from basic input and out put pretty much
everything else is up to the programmer as far as features go. The apex data structure for creating
something useful with BLT is the 'Point' (see point.h)
	The BLT console is grid based, so naturally the point makes an excellent choice to start with, and as
such most of whats here is focues around manipulating points on the grid. From pathfinding to dungeon generation
The abality to address and influence each spot on the grid is paramount.
	The other important structure is the 'field'. The field is an N x M grid of Point's that makes up
the current scene/dungeon/&c. The board class (see blank_layout.h) creates an empty grid of a supplied
size to be used for the layout. The Point structure has a .blocks value to indicate whether the current
Point is a wall/obstacle or an open area.
    'zones' are used to hold the field and other relative data about the map being created, for example,
    if it is a maze or not. it also contains the height and width dimensions.
    Once you have generated your fields of desired size you can pass it through the maze generator, the dungeon
  generator, or implement something yourself through the shape classes, you may also combine options, such as 
  generating a maze field and passing the maze field to one of the dungeon generators to build on top of.
    With your field setup you can use the Dijkstra Map generator and the accompanying dijkMove function
 for implementing NPC movement on the field. A basice entity class is included for creaing both
 NPC's or player characters. 
 
 ## Example Usage
 
 MCTk is meant to be used in conjunction with BearLibTerminal. BearLibTerminal must be installed on your
 system inorder to build a project with MCTk.
 To use MCTk, you must include the header mctk.h in your project, and the include/ and src/ folders MUST 
 be in the same folder as mctk.h
 
 A minimum of C++11 is required to compile MCTk, with the code below saved as mctkexample.cpp:
 ```
 compile:
 g++ --std=c++11 mctkexample.cpp -o mctkexample -L. libBearTerminal.dylib
 
 run
 ./mctkexample
 ```
 
 ```cpp
#include "BearLibTerminal.h"
#include "mctk.h"

int main()
{

  terminal_open();                     //settin up a bearlibterminal console window
  terminal_set("window: size=80x40");

  mctk::board blanklayout(80, 40);          //create a blank zone with the supplied dimensions
  mctk::zone base = blanklayout.getZone();  //retrieve the zone for usage
  mctk::dfMaze maze(base);                  //initialize the maze generator without blank zone
  
  maze.makeMaze();                          //create a maze
  base = maze.getMaze();                    //retrieve our zone which no contains a maze
  
  mctk::dungeon dg(base);                   //initialize the dungeon generator with our maze
  dg.basic(8, 8);                           //use the basic dungeon generator, max # of rooms = 8, max room size = 8x8 
  base.layout = dg.getField();              //retrieve our updated zone
  
  terminal_refresh();
  while (int k = terminal_read() != TK_Q)
  {
    terminal_clear();
    mctk::render(base);                           //render our generated maze dungeon zone on the bearlibterminal
    terminal_refresh();                     //console window.
  }
  terminal_close();
  return 0;
}
```
Without a maze:

![No maze](https://www.maxcodes.info/~maxgoren/nomaze.png)

composite dungeon and maze:

![With maze](https://www.maxcodes.info/~maxgoren/withmaze.png)


basic dungeon set to maxrooms = 10 and maxsize = 9.
Dijkstra mapping on and render() set to showingDmap = true

![dmap colored](https://www.maxcodes.info/~maxgoren/dmapcolorized.png)

 Feature set
--------------

Path finding:
------------

- Breadth First Search & A* based path finding
- Dijkstra Map automated pathing for NPC's


Generators:
-----------

Random Number - integer and float

Dungeon - There is 2 dungeon generating algorithms available for use at those moment:
	- Basic Map generator - uses random place ment and collision detection to build a dungeon layout
	- BSP Map generator - this uses Binary Space Partition to create a zero overlapping, or minor overlapping room
				layout depending on your desired tolerance constraints.

Maze generator - input a field and this outputs a maze! can be used standalone or combined with one of the above dungeon generators
		to make more complex maps.

Perlin Noise Generator - many, many uses from placing items to making landscapes Perlin noise is used for all sorts of
			procedural generation. Outputs valuse between 0.0 and 1.0.

Colors - easy interface to BLT's color_t type, as well as a gradients and fades.

Dijkstra Map - creation of single focus and multi point focus Dijkstra maps of levels
	       and functions for NPC interaction with Dijkstra Maps

Name Generator - [color] [texture] [item] format, i.e. a [purple] [forthing] [potion]
		or [red] [hairy] [troll]


Data structures:
----------------
Point - more than just x/y, the features of this library are all developed
       around the idea of using a point based grid system not just for making
       maps but also to facilitate character movement, path finding, FOV, etc.
       
line - a continuous segment of Points along a vertical or horizontal plane
       this is used to make more complex shapes.
       
Rectangle - see above.

Circle - see above.


Containers:
-----------

linked list - dynamically allocated to be able to grow and shrink in size.

Queue - FIFO stack used in many algorithms

Stack - classic LIFO stack, see above.
