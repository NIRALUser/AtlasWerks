/* ================================================================
 *
 * AtlasWerks Project
 *
 * Copyright (c) Sarang C. Joshi, Bradley C. Davis, J. Samuel Preston,
 * Linh K. Ha. All rights reserved.  See Copyright.txt or for details.
 *
 * This software is distributed WITHOUT ANY WARRANTY; without even the
 * implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
 * PURPOSE.  See the above copyright notice for more information.
 *
 * ================================================================ */

#ifndef __VECTOR3D_H
#define __VECTOR3D_H

#include "AtlasWerksException.h"

#ifndef SWIG

#include <iosfwd>
#include <iostream>

#endif // SWIG

//
// This struct is meant to be a fast 3D vector class.
// It is intended for use with built-in types (int, float, etc.)
// 
// Optimization is important for this struct
// - almost everything is inlined
// - readability and maintainability tradeoffs have been made 
//   for speed gains
//
// bcd 2003
//

template <class T>
class Vector3D 
{
public:
  //
  // IMPORTANT: DO NOT change the order of x, y, and z.  
  // DO NOT add other data members between x, y, and z.
  // Array style access depends on these being adjacent
  // in memory.  This is guarenteed for standards compliant
  // compilers only if they are declared as they are here.
  // DO NOT TOUCH THIS LINE
  //
  T x, y, z;
  // IMPORTANT DO NOT TOUCH THE ABOVE LINE //

  // 
  // constructors
  //

  Vector3D();
  Vector3D(const T& xIn, const T& yIn, const T& zIn);

  template <class U>
  Vector3D(const Vector3D<U>& rhs)
    :x((T)rhs.x), y((T)rhs.y), z((T)rhs.z)
  {}

  Vector3D(const T& v)
    :x(v), y(v), z(v)
  {}

  const T& get(unsigned int index);
  void set(unsigned int index, const T& val);

#ifndef SWIG
  //
  // Don't wrap these operators, they don't map to python.
  //

  template <class U>
  Vector3D<T>& operator=(const Vector3D<U>& rhs)
  {
    x = rhs.x;
    y = rhs.y;
    z = rhs.z;
    return *this;
  }
  
  Vector3D<T>& operator=(const T& v)
  {
    x = v;
    y = v;
    z = v;
    return *this;
  }
  
  //
  // array style coordinate access
  //
  // with optomization turned on, this is just as fast
  // as .x, .y, .z access
  //
  T& operator[](unsigned int index);
  const T& operator[](unsigned int index) const;

#endif // SWIG

  //
  // the euclidean length of this vector
  //
  double length() const;
  double lengthSquared() const;

  //
  // L1 and L2 norms, normL2 is the same as length()
  //
  double normL1() const;
  double normL2() const;

  //
  // element accumulation
  //
  T productOfElements() const;
  T sumOfElements() const;

  //
  // min and max coordinate values
  //
  T maxElement() const;
  T minElement() const;

  //
  // manipulation methods
  // 
  void set(const T& x, const T& y, const T& z);
  void scale(const T& sx, const T& sy, const T& sz);
  void translate(const T& tx, const T& ty, const T& tz);
  void invert();
  void normalize();

  //
  // the distance between the tip of this and the tip of rhs
  //
  double distance(const Vector3D<T>& rhs) const;
  double distanceSquared(const Vector3D<T>& rhs) const;

  //
  // inner (dot) product
  //
  double dot(const Vector3D<T>& rhs) const;

  //
  // vector (cross) product
  //
  Vector3D<T> cross(const Vector3D<T>& rhs) const;

  //
  // output
  //
  std::ostream& writeASCII(std::ostream& output = std::cerr) const;
  std::istream& readASCII(std::istream& input = std::cin);
  std::ostream& writeBinary(std::ostream& output = std::cerr) const;
  std::istream& readBinary(std::istream& input = std::cin);

};

//
// comparison operators
//
template <class T> 
bool operator<(const Vector3D<T>& lhs, const Vector3D<T>& rhs);
template <class T>
bool operator==(const Vector3D<T>& lhs, const Vector3D<T>& rhs);
template <class T>
bool operator!=(const Vector3D<T>& lhs, const Vector3D<T>& rhs);

//
// invert operator (unary minus)
//
template <class T>
Vector3D<T> operator-(const Vector3D<T>& rhs);

//
// elementwise operators with Vector3D
//
template <class T, class U>
Vector3D<T>& operator+=(Vector3D<T>& lhs, const Vector3D<U>& rhs);
template <class T, class U>
Vector3D<T>& operator-=(Vector3D<T>& lhs, const Vector3D<U>& rhs);
template <class T, class U>
Vector3D<T>& operator*=(Vector3D<T>& lhs, const Vector3D<U>& rhs);
template <class T, class U>
Vector3D<T>& operator/=(Vector3D<T>& lhs, const Vector3D<U>& rhs);
template <class T, class U>
Vector3D<T> operator+(const Vector3D<T>& lhs, const Vector3D<U>& rhs);
template <class T, class U>
Vector3D<T> operator-(const Vector3D<T>& lhs, const Vector3D<U>& rhs);
template <class T, class U>
Vector3D<T> operator*(const Vector3D<T>& lhs, const Vector3D<U>& rhs);
template <class T, class U>
Vector3D<T> operator/(const Vector3D<T>& lhs, const Vector3D<U>& rhs);

//
// element-wise operators with a double
//
template <class T, class U>
Vector3D<T>& operator+=(Vector3D<T>& v, const U &u);
template <class T, class U>
Vector3D<T>& operator-=(Vector3D<T>& v, const U &u);
template <class T, class U>
Vector3D<T>& operator*=(Vector3D<T>& v, const U &u);
template <class T, class U>
Vector3D<T>& operator/=(Vector3D<T>& v, const U &u);
template <class T, class U>
Vector3D<T> operator+(const Vector3D<T>& v, const U &u);
template <class T, class U>
Vector3D<T> operator+(const U &u, const Vector3D<T>& v);
template <class T, class U>
Vector3D<T> operator-(const Vector3D<T>& v, const U &u);
template <class T, class U>
Vector3D<T> operator-(const U &u, const Vector3D<T>& v);
template <class T, class U>
Vector3D<T> operator*(const Vector3D<T>& v, const U &u);
template <class T, class U>
Vector3D<T> operator*(const U &u, const Vector3D<T>& v);
template <class T, class U>
Vector3D<T> operator/(const Vector3D<T>& v, const U &u);
template <class T, class U>
Vector3D<T> operator/(const U &u, const Vector3D<T>& v);

//
// input/output
//
template <class T>
std::ostream& operator<<(std::ostream& output, const Vector3D<T>& v);
template <class T>
std::istream& operator>>(std::istream& input, Vector3D<T>& v);

#define Vector3Di Vector3D<int>
#define Vector3Du Vector3D<unsigned int>
#define Vector3Df Vector3D<float>
#define Vector3Dd Vector3D<double>

#ifndef SWIG
#include "Vector3D.txx"
#endif // SWIG

#endif
