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
Random integer and float generators, Perlin noise, and a maze generator, and an 
extended feature set for BLT's color_t type, just to name a few. A full list of 
what is implemented is below. This is a work in progress, so not all of the bugs
have been shaken out. More features will be added regularly.

##How it works
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
    Once you have generated your fields of desired size you can pass it through the maze generator, the dungeon
  generator, or implement something yourself through the shape classes.
    With your field setup you can use the Dijkstra Map generator and the accompanying dijkMove function
 for implementing NPC movement on the field. A basice entity class is included for creaing both
 NPC's or player characters.

# Feature set
--------------

##Path finding:
------------

Breadth First Search & A* based path finding


##Data structures:
----------------
Point - more than just x/y, the features of this library are all developed
       around the idea of using a point based grid system not just for making
       maps but also to facilitate character movement, path finding, FOV, etc.
       
line - a continuous segment of Points along a vertical or horizontal plane
       this is used to make more complex shapes.
       
Rectangle - see above.

Circle - see above.


##Containers:
-----------

linked list - dynamically allocated to be able to grow and shrink in size.

Queue - FIFO stack used in many algorithms

Stack - classic LIFO stack, see above.


##Generators:
-----------

Random Number - integer and float

Dungeon - "spray and pray" room and tunnel, bsp, and maze based dungeons.

Perlin Noise - noise generator, many uses.

Colors - easy interface to BLT's color_t type, as well as a gradients and fades.

Dijkstra Map - creation of single focus and multi point focus Dijkstra maps of levels
	       and functions for NPC interaction with Dijkstra Maps

Name Generator - [color] [texture] [item] format, i.e. a [purple] [forthing] [potion]
		or [red] [hairy] [troll]



