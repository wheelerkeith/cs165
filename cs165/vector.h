/***********************************************************************
* Header:
*    Vector
* Summary:
*    A Vector class to model how to make the projects for this semester
*
*    This will contain the class definition of:
*        Vector            : A class to hold the Vector
*        VectorIterator    : A class to go through the Vector class
* Author
*    Keith Wheeler
************************************************************************/

#ifndef CONTAINER_H
#define CONTAINER_H

#include <cassert>
#include <iostream>

// forward declaration for VectorIterator
template <class T>
class VectorIterator;

// forward declaration for VectorConstIterator
template <class T>
class VectorConstIterator;

/************************************************
 * Vector
 * A class that holds stuff
 ***********************************************/
template <class T>
class Vector
{
public:
   // default constructor : empty and kinda useless
   Vector() : numItems(0), cap(0), data(NULL) {}

   // copy constructor : copy it
   Vector(const Vector & rhs) throw (const char *);
   
   // non-default constructor : pre-allocate
   Vector(int cap) throw (const char *);
   
   // destructor : free everything
   ~Vector()        { if (cap) delete [] data; }
   
   // is the container currently empty
   bool empty() const  { return numItems == 0;         }

   // remove all the items from the container
   void clear()        { numItems = 0;                 }

   // how many items are currently in the container?
   int size() const    { return numItems;              }

   // add an item to the container
   void insert(const T & t) throw (const char *);

   // how many items can be put into container
   int capacity() const   { return cap;          }

   // push_back function
   void push_back(T item)
   {
      // creates a pointer template
      T* newT;
      // if numItems excedes capacity doubles space
      if (numItems >= cap)
      {
         if (cap == 0)
         {
            cap = 1;
         }
         else
         {
            cap *= 2;
         }
         newT = new T[cap];
         // copies old array to new array
         for(int x = 0; x < numItems; ++x)
         {
            newT[x] = data[x];
         }
         delete [] data;
         data = newT;
      }
      // puts item into array
      insert(item);
   }

   // square bracket operator returns what is in a certain spot of array
   T& operator[](int t) throw (const char *)
   {
      if (t < 0 || t >= numItems)
      {
         throw "ERROR: invalid index";
      }
      return data[t];
   }

   const T& operator[](int t) const throw (const char *)
   {
      if (t < 0 || t >= numItems)
      {
         throw "ERROR: invalid index";
      }
      return data[t];
   }

   Vector<T> & operator = (const Vector<T> & rhs) throw (const char *);
    
   // return an iterator to the beginning of the list
   VectorIterator <T> begin() { return VectorIterator<T>(data); }

   // return the constiterator to the beginning of the list
   VectorConstIterator <T> cbegin() const
      { return VectorConstIterator<T>(data); }

   // return the constiterator to the end of the list
   VectorConstIterator <T> cend() const
      { return VectorConstIterator<T>(data + numItems);}

   // return an iterator to the end of the list
   VectorIterator <T> end() { return VectorIterator<T>(data + numItems);}
   
private:
   T * data;          // dynamically allocated array of T
   int numItems;      // how many items are currently in the Container?
   int cap;      // how many items can I put on the Container before full?
};

/**************************************************
 * Vector ITERATOR
 * An iterator through Container
 *************************************************/
template <class T>
class VectorIterator
{
  public:
   // default constructor
   VectorIterator() : p(NULL) {}

   // initialize to direct p to some item
   VectorIterator(T * p) : p(p) {}

   // copy constructor
   VectorIterator(const VectorIterator & rhs) { *this = rhs; }

   // assignment operator
   VectorIterator & operator = (const VectorIterator & rhs)
   {
      this->p = rhs.p;
      return *this;
   }

   // not equals operator
   bool operator != (const VectorIterator & rhs) const
   {
      return rhs.p != this->p;
   }

   // dereference operator
   T & operator * ()
   {
      return *p;
   }

   // prefix increment
   VectorIterator <T> & operator ++ ()
   {
      p++;
      return *this;
   }

   // postfix increment
   VectorIterator <T> operator++(int postfix)
   {
      VectorIterator tmp(*this);
      p++;
      return tmp;
   }

   // added operators
   VectorIterator <T> & operator -- ()
   {
      p--;
      return *this;
   }

   VectorIterator <T> operator-- (int decrement)
   {
      VectorIterator tmp(*this);
      p--;
      return tmp;
   }   
   
  private:
   T * p;
};

/**************************************************
 * Vector Const ITERATOR
 * An iterator through Container
 *************************************************/
template <class T>
class VectorConstIterator
{
  public:
   // default constructor
   VectorConstIterator() : p(NULL) {}

   // initialize to direct p to some item
   VectorConstIterator(T * p) : p(p) {}

   // copy constructor
   VectorConstIterator(const VectorConstIterator & rhs) { *this = rhs; }

   // assignment operator
   VectorConstIterator & operator = (const VectorConstIterator & rhs)
   {
      this->p = rhs.p;
      return *this;
   }

   // not equals operator
   bool operator != (const VectorConstIterator & rhs) const
   {
      return rhs.p != this->p;
   }

   // dereference operator
   T & operator * ()
   {
      return *p;
   }

   // prefix increment
   VectorConstIterator <T> & operator ++ ()
   {
      p++;
      return *this;
   }

   // postfix increment
   VectorConstIterator <T> operator++(int postfix)
   {
      VectorConstIterator tmp(*this);
      p++;
      return tmp;
   }

   // added operators
   VectorConstIterator <T> & operator -- ()
   {
      p--;
      return *this;
   }

   VectorConstIterator <T> operator-- (int decrement)
   {
      VectorConstIterator tmp(*this);
      p--;
      return tmp;
   }

   
   
  private:
   T * p;
};


/*******************************************
 * CONTAINER :: COPY CONSTRUCTOR
 *******************************************/
template <class T>
Vector <T> :: Vector(const Vector <T> & rhs) throw (const char *)
{
   assert(rhs.cap >= 0);
      
   // do nothing if there is nothing to do
   if (rhs.cap == 0)
   {
      cap = numItems = 0;
      data = NULL;
      return;
   }

   // attempt to allocate
   try
   {
      data = new T[rhs.cap];
   }
   catch (std::bad_alloc)
   {
      throw "ERROR: Unable to allocate buffer for Vector";
   }
   
   // copy over the capacity and size
   assert(rhs.numItems >= 0 && rhs.numItems <= rhs.cap);
   cap = rhs.cap;
   numItems = rhs.numItems;

   // copy the items over one at a time using the assignment operator
   for (int i = 0; i < numItems; i++)
      data[i] = rhs.data[i];

   // the rest needs to be filled with the default value for T
   for (int i = numItems; i < cap; i++)
      data[i] = T();
}

/**********************************************
 * CONTAINER : NON-DEFAULT CONSTRUCTOR
 * Preallocate the container to "capacity"
 **********************************************/
template <class T>
Vector<T> :: Vector(int cap) throw (const char *)
{
   assert(cap >= 0);
   
   // do nothing if there is nothing to do
   if (cap == 0)
   {
      this->cap = this->numItems = 0;
      this->data = NULL;
      return;
   }

   // attempt to allocate
   try
   {
      data = new T[cap];
   }
   catch (std::bad_alloc)
   {
      throw "ERROR: Unable to allocate buffer";
   }

      
   // copy over the stuff
   this->cap = cap;
   this->numItems = 0;

   // initialize the container by calling the default constructor
   for (int i = 0; i < cap; i++)
      data[i] = T();
}

/***************************************************
 * CONTAINER :: INSERT
 * Insert an item on the end of the container
 **************************************************/
template <class T>
void Vector <T> :: insert(const T & t) throw (const char *)
{
   // do we have space?
   if (cap == 0 || cap == numItems)
      throw "ERROR: Insufficient space";
   
   // add an item to the end
   data[numItems++] = t;
}

/****************************************
 * Vector : ASSIGNMENT
 ****************************************/
template <class T>
Vector<T> & Vector<T> :: operator = (const Vector<T> & rhs) throw (const char *)
{
   assert(rhs.cap >=0);

   if (rhs.cap == 0)
   {
      this->cap = this->numItems = 0;
      this->data = NULL;
      return *this;
   }

   try
   {
      this->data = new T[rhs.cap];
   }
   catch (std::bad_alloc)
   {
      throw "ERROR: Unable to allocate a new buffer for Vector";
   }

   assert(rhs.numItems >= 0 && rhs.numItems <= rhs.cap);
   this->numItems = rhs.numItems;
   this->cap = rhs.cap;

   for(int i = 0; i < this->numItems; i++)
      this->data[i] = rhs.data[i];

   for (int i = this->numItems; i < this->cap; i++)
      this->data[i] = T();

   return *this;
}

#endif // Vector_H

