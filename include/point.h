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
#include <tuple>

struct Point {
  int x;
  int y;
  int costm;
  int level;
  int id;
  char s;
  color_t color;
  bool blocks;
  bool populated;
  bool border;
  bool ismaze;
  bool operator==(const Point& other) const {
    return x == other.x && y == other.y;
  }

  bool operator!=(const Point& other) const {
    return x != other.x || y != other.y;
  }

  bool operator < (const Point& other) const {
    return std::tie(x,y) < std::tie(other.x,other.y);
  }

  bool operator > (const Point& other) const {
    return std::tie(x,y) > std::tie(other.x, other.y);
  }

Point operator=(Point other) {
  x = other.x;
  y = other.y;
  s = other.s;
  blocks = other.blocks;
  return other;
}
Point(int x, int y) : x(x), y(y) { }
Point(int x, int y, char s) : x(x), y(y), s(s) { }
Point() = default;
};


