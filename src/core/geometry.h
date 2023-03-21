#pragma once

using namespace std;


// -- Vector Declarations -- 
template <typename T>
class Vector2 {
public:
  // Vector2 Public Methods
  Vector2() { x = y = 0; }
  Vector2(T xx, T yy) : x(xx), y(yy) { DCHECK(!HasNaNs()); }
  bool HasNaNs() const { return isNaN(x) || isNaN(y); }
  explicit Vector2(const Point2<T>& p);
  explicit Vector2(const Point3<T>& p);
#ifndef NDEBUG
  // The default versions of these are fine for release builds; for debug
  // we define them so that we can add the Assert checks.
  Vector2(const Vector2<T>& v) {
    DCHECK(!v.HasNaNs());
    x = v.x;
    y = v.y;
  }
  Vector2<T>& operator=(const Vector2<T>& v) {
    DCHECK(!v.HasNaNs());
    x = v.x;
    y = v.y;
    return *this;
  }
#endif  // !NDEBUG

  Vector2<T> operator+(const Vector2<T>& v) const {
    DCHECK(!v.HasNaNs());
    return Vector2(x + v.x, y + v.y);
  }

  Vector2<T>& operator+=(const Vector2<T>& v) {
    DCHECK(!v.HasNaNs());
    x += v.x;
    y += v.y;
    return *this;
  }
  Vector2<T> operator-(const Vector2<T>& v) const {
    DCHECK(!v.HasNaNs());
    return Vector2(x - v.x, y - v.y);
  }

  Vector2<T>& operator-=(const Vector2<T>& v) {
    DCHECK(!v.HasNaNs());
    x -= v.x;
    y -= v.y;
    return *this;
  }
  bool operator==(const Vector2<T>& v) const { return x == v.x && y == v.y; }
  bool operator!=(const Vector2<T>& v) const { return x != v.x || y != v.y; }
  template <typename U>
  Vector2<T> operator*(U f) const {
    return Vector2<T>(f * x, f * y);
  }

  template <typename U>
  Vector2<T>& operator*=(U f) {
    DCHECK(!isNaN(f));
    x *= f;
    y *= f;
    return *this;
  }
  template <typename U>
  Vector2<T> operator/(U f) const {
    CHECK_NE(f, 0);
    Float inv = (Float)1 / f;
    return Vector2<T>(x * inv, y * inv);
  }

  template <typename U>
  Vector2<T>& operator/=(U f) {
    CHECK_NE(f, 0);
    Float inv = (Float)1 / f;
    x *= inv;
    y *= inv;
    return *this;
  }
  Vector2<T> operator-() const { return Vector2<T>(-x, -y); }
  T operator[](int i) const {
    DCHECK(i >= 0 && i <= 1);
    if (i == 0) return x;
    return y;
  }

  T& operator[](int i) {
    DCHECK(i >= 0 && i <= 1);
    if (i == 0) return x;
    return y;
  }
  Float LengthSquared() const { return x * x + y * y; }
  Float Length() const { return std::sqrt(LengthSquared()); }

  // Vector2 Public Data
  T x, y;
};

template <typename T>
class Vector3 {
public:
  // Vector3 Public Methods
  T operator[](int i) const {
    DCHECK(i >= 0 && i <= 2);
    if (i == 0) return x;
    if (i == 1) return y;
    return z;
  }
  T& operator[](int i) {
    DCHECK(i >= 0 && i <= 2);
    if (i == 0) return x;
    if (i == 1) return y;
    return z;
  }
  Vector3() { x = y = z = 0; }
  Vector3(T x, T y, T z) : x(x), y(y), z(z) { DCHECK(!HasNaNs()); }
  bool HasNaNs() const { return isNaN(x) || isNaN(y) || isNaN(z); }
  explicit Vector3(const Point3<T>& p);
#ifndef NDEBUG
  // The default versions of these are fine for release builds; for debug
  // we define them so that we can add the Assert checks.
  Vector3(const Vector3<T>& v) {
    DCHECK(!v.HasNaNs());
    x = v.x;
    y = v.y;
    z = v.z;
  }

  Vector3<T>& operator=(const Vector3<T>& v) {
    DCHECK(!v.HasNaNs());
    x = v.x;
    y = v.y;
    z = v.z;
    return *this;
  }
#endif  // !NDEBUG
  Vector3<T> operator+(const Vector3<T>& v) const {
    DCHECK(!v.HasNaNs());
    return Vector3(x + v.x, y + v.y, z + v.z);
  }
  Vector3<T>& operator+=(const Vector3<T>& v) {
    DCHECK(!v.HasNaNs());
    x += v.x;
    y += v.y;
    z += v.z;
    return *this;
  }
  Vector3<T> operator-(const Vector3<T>& v) const {
    DCHECK(!v.HasNaNs());
    return Vector3(x - v.x, y - v.y, z - v.z);
  }
  Vector3<T>& operator-=(const Vector3<T>& v) {
    DCHECK(!v.HasNaNs());
    x -= v.x;
    y -= v.y;
    z -= v.z;
    return *this;
  }
  bool operator==(const Vector3<T>& v) const {
    return x == v.x && y == v.y && z == v.z;
  }
  bool operator!=(const Vector3<T>& v) const {
    return x != v.x || y != v.y || z != v.z;
  }
  template <typename U>
  Vector3<T> operator*(U s) const {
    return Vector3<T>(s * x, s * y, s * z);
  }
  template <typename U>
  Vector3<T>& operator*=(U s) {
    DCHECK(!isNaN(s));
    x *= s;
    y *= s;
    z *= s;
    return *this;
  }
  template <typename U>
  Vector3<T> operator/(U f) const {
    CHECK_NE(f, 0);
    Float inv = (Float)1 / f;
    return Vector3<T>(x * inv, y * inv, z * inv);
  }

  template <typename U>
  Vector3<T>& operator/=(U f) {
    CHECK_NE(f, 0);
    Float inv = (Float)1 / f;
    x *= inv;
    y *= inv;
    z *= inv;
    return *this;
  }
  Vector3<T> operator-() const { return Vector3<T>(-x, -y, -z); }
  Float LengthSquared() const { return x * x + y * y + z * z; }
  Float Length() const { return std::sqrt(LengthSquared()); }
  explicit Vector3(const Normal3<T>& n);

  // Vector3 Public Data
  T x, y, z;
};

// TypeDef for common vectors
typedef Vector2<Float> Vector2f;
typedef Vector2<int> Vector2i;
typedef Vector3<Float> Vector3f;
typedef Vector3<int> Vector3i;

// Geometry Inline Functions
template <typename T> inline Vector3<T> operator*(T s, const Vector3<T>& v) { return v * s; }
template <typename T> inline Vector3<T> Abs(const Vector3<T>& v) {
  return Vector3<T>(std::abs(v.x), std::abs(v.y), std::abs(v.z));
}
template <typename T> inline T Dot(const Vector3<T>& v1, const Vector3<T>& v2) {
  return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
}
template <typename T> inline T AbsDot(const Vector3<T>& v1, const Vector3<T>& v2) {
  return std::abs(Dot(v1, v2));
}
template <typename T> inline Vector3<T> Cross(const Vector3<T>& v1, const Vector3<T>& v2) {
  double v1x = v1.x, v1y = v1.y, v1z = v1.z;
  double v2x = v2.x, v2y = v2.y, v2z = v2.z;
  return Vector3<T>((v1y * v2z) - (v1z * v2y),
    (v1z * v2x) - (v1x * v2z),
    (v1x * v2y) - (v1y * v2x));
}
template <typename T> inline Vector3<T> Normalize(const Vector3<T>& v) { return v / v.Length(); }

// -- Miscellaneous Operations
template <typename T> T MinComponent(const Vector3<T>& v) {
  return std::min(v.x, std::min(v.y, v.z));
}
template <typename T> T MaxComponent(const Vector3<T>& v) {
  return std::max(v.x, std::max(v.y, v.z));
}
template <typename T> int MaxDimension(const Vector3<T>& v) {
  return (v.x > v.y) ? ((v.x > v.z) ? 0 : 2) : ((v.y > v.z) ? 1 : 2);
}
template <typename T> Vector3<T> Min(const Vector3<T>& p1, const Vector3<T>& p2) {
  return Vector3<T>(std::min(p1.x, p2.x), std::min(p1.y, p2.y), std::min(p1.z, p2.z));
}
template <typename T> Vector3<T> Max(const Vector3<T>& p1, const Vector3<T>& p2) {
  return Vector3<T>(std::max(p1.x, p2.x), std::max(p1.y, p2.y), std::max(p1.z, p2.z));
}
template <typename T> Vector3<T> Permute(const Vector3<T>& v, int x, int y, int z) {
  return Vector3<T>(v[x], v[y], v[z]);
}
template <typename T> inline void CoordinateSystem(const Vector3<T>& v1, Vector3<T>* v2, Vector3<T>* v3) {
  if (std::abs(v1.x) > std::abs(v1.y))
    *v2 = Vector3<T>(-v1.z, 0, v1.x) /
    std::sqrt(v1.x * v1.x + v1.z * v1.z);
  else
    *v2 = Vector3<T>(0, v1.z, -v1.y) /
    std::sqrt(v1.y * v1.y + v1.z * v1.z);
  *v3 = Cross(v1, *v2);
}


// -- Points Declaration
// 2.3 here https://www.pbr-book.org/3ed-2018/Geometry_and_Transformations/Points
