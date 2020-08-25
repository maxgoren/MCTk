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

class dfMaze {
private:
 Point dir[8];
 std::vector<std::vector<bool>> seen;
 std::vector<Point> mbe;
 std::stack<Point> staq;
public:
 int mapH, mapW;
 field layout;
 zone getZone();
 void makeMaze();
 bool OOB(Point);
 dfMaze(mctk::zone outline);
};

class compMaze {
    public:
    std::stack<Point> backtrack;
    std::array<Point, 4> dir;
    int width;
    int height;
    int mapW, mapH;
    int visited;
    int totalCells;
    std::vector<std::vector<bool>> seen;
    field layout;
    zone getZone();
    void removeEdge(std::tuple<int, Point>);
    std::vector<std::tuple<int, Point>> checkAdj(Point n);
    bool OOB(Point n);
    void start();
    compMaze(mctk::zone outline);
};


}