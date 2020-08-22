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

struct colors {
  float a = 255;
  int r = 0;
  int g = 0;
  int b = 0;
  color_t final = color_from_argb(a, r, g, b);
  colors(int q, int c, int d, int l) : a(q), r(c), g(d), b(l) { }
  colors(int c, int d, int l) : r(c), g(d), b(l) { }
  colors() { }
};
/***************************************/
const colors red = { 0xff, 0x00,0x00 };
const colors green = { 0x00, 0xff, 0x00 };
const colors blue = { 0x00, 0x00, 0xff }; 
const colors yellow = { 0xFF, 0xFF, 0x00 };
const colors cyan = { 0x00, 0xFF, 0xFF };
const colors white = { 0xFF, 0xFF, 0xFF };
const colors black = {0x00, 0x00, 0x00};
const colors grey = {0xce, 0xce,0xce};
/***************************************/


color_t fadeColors(colors c1, colors c2, float mix)
{
 
  colors result;
  color_t ret = color_from_argb(
    255,
    (int)c1.r*(1-mix) + c2.r*(mix),
    (int)c1.g*(1-mix) + c2.g*(mix),
    (int)c1.b*(1-mix) + c2.b*(mix));
  return ret;
}