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

Noise::Noise()
{

}

float Noise::linearConvert(float value, float OldMin, float OldMax, float NewMin, float NewMax)
{
  float OldRange = OldMax - OldMin;
  float NewRange = NewMax - NewMin;
  return (((value - OldMin) * NewRange)/ OldRange) + NewMin;
}


float Noise::lerp(float a0, float a1, float w)
{
    return (1.0f - w)*a0+w*a1;
}

float Noise::dotGridGradient(int ix, int iy, float x, float y)
{
    float dx = x - (float)ix;
    float dy = y - (float)iy;
    float xgrad = getrandfloat(0.0f, 1.0f);
    float ygrad = getrandfloat(0.0f, 1.0f);
    return (dx*xgrad + dy*ygrad);
}

float Noise::perlin(float x, float y)
{
    int x0 = int(x);
    int x1 = x0 + 1;
    int y0 = int(y);
    int y1 = y0 + 1;

    float sx = x- (float)x0;
    float sy = y - (float)y0;
    float n0,n1,ix0,ix1,value;

    n0 = dotGridGradient(x0,y0,x,y);
    n1 = dotGridGradient(x1,y0,x,y);
    ix0 = lerp(n0,n1,sx);
  
    n0 = dotGridGradient(x0,y1,x,y);
    n1 = dotGridGradient(x1,y1,x,y);
    ix1 = lerp(n0,n1,sx); 
    value = lerp(ix0,ix1,sy);
    return linearConvert(value, -2.5, 2.3, 0.0, 1.0);
}

}