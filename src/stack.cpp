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
template <class T>
Stack<T>::Stack()
{
  head = new node;
  z = new node;
  head->next = z;
  z->next = z;
}

template <class T>
Stack<T>::~Stack()
{
 struct node *t = head;
 while (t != z)
 {
  head = t;
  t= t->next;
  delete head;
 }
}

template <class T>
void Stack<T>::push(T v)
{
 struct node *t = new node;
 t->key = v;
 t->next = head->next;
 head->next = t;
}

template <class T>
T Stack<T>::pop()
{
 T x;
 struct node *t = head->next;
 head->next = t->next; x = t->key;
 delete t;
 return x;
}

template <class T>
int Stack<T>::empty()
{
 return head->next == z;
}

}