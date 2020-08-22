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
list<T>::list()
{
 head = new node;
    z = new node;
 head->next = z;
 z->next = z;
 numNodes = 0;
}

template <class T>
T list<T>::at(int x)
{
  bool found = false;
  struct node *t = head;
  while (t != z)
  {
    if (t->id == x)
    {
      found = true;
      break;
    } else {
      t = t->next;
    }
  }
  if (found == true)
  {
    return t->key;
  }
  return z->key;
}

template <class T>
T list<T>::end()
{
  return z->key;
}

template <class T>
void list<T>::clear()
{
  struct node *t;
  while (!empty()) pop();
  t = new node;
  t->next = z;
  head = t;
}

template <class T>
void list<T>::push(T v)
{
 struct node *x;
 x = new node;
 x->key = v;
 x->next = head->next;
 head->next = x;
 numNodes++;
 x->id = numNodes;
}

template <class T>
T list<T>::pop()
{
 T v;
 struct node *x, *t = head;
  x = head->next; t->next = x->next;
  v = x->key;
 if (x != z)
   delete x;
 numNodes--;
 return v;
}

template <class T>
T list<T>::get(T v)
{
 struct node *t = head;
 while (t->key != v)
 { t = t->next; }
 return t->key;
}

template <class T>
void list<T>::remove(T v)
{
 struct node *x, *t = head;
 while (t->next->key != v)
 { t = t->next; }
 x = t->next;
 t->next = x->next;
 if (t != z)
   delete x;
 numNodes--;
}

template <class T>
T list<T>::front()
{
  return head->next->key;
}

template <class T>
T list<T>::back()
{
  struct node *t = head;
  T v;
  while (t->next != z)
  {
    v = t->next->key;
    t = t->next;
  }
  return v;
}

template <class T>
bool list<T>::empty()
{
 return head->next == z;
}


template <class T>
void list<T>::insert(T v, T p)
{
  struct node *x, *t = head;
  x = new node;
  x->key = v;
  while (t->next->next->key != p)
  {
    t = t->next;
  }
  x->next = t->next->next;
  t->next->next = x;
  x->id = x->next->id;
  numNodes++;
  while (t != z)
  {
    t = t->next;
    t->id++;
  }
}

template <class T>
bool list<T>::find(T v)
{
  struct node *t = head;
  while (t != z)
  {
    if (t->key == v)
      return true;
    t = t->next;
  }
  return false;
}

template <class T>
int list<T>::size()
{
 return numNodes;
}

}