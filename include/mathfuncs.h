#ifndef mathfuncs_H
#define mathfuncs_H

#include <array>

class vec2d {
public:
  float x;
  float y;

  vec2d();
  vec2d(float x, float y);
  vec2d(const vec2d &vector);
  vec2d(vec2d &&other) = default;
  vec2d &operator=(vec2d &&other) = default;

  vec2d &operator=(const vec2d &vec);
  vec2d &operator+=(const vec2d &vec);
  vec2d &operator-=(const vec2d &vec);
  vec2d &operator+=(const float val);
  vec2d &operator-=(const float val);
  vec2d &operator*=(const float val);
  vec2d &operator/=(const float val);
  vec2d operator+(const vec2d &vec) const;
  vec2d operator-(const vec2d &vec) const;
  vec2d operator+(const float val) const;
  vec2d operator-(const float val) const;
  vec2d operator*(const float val) const;
  vec2d operator/(const float val) const;

  void assign(float x, float y);
  float length() const;
  vec2d normalize();
  vec2d negY();
  vec2d negate();
};

// Dot Product
inline float dp(vec2d &vec1, vec2d &vec2) {
  return (vec1.x * vec2.x) + (vec1.y * vec2.y);
}

inline float dp(vec2d vec1, vec2d vec2) {
  return (vec1.x * vec2.x) + (vec1.y * vec2.y);
}
// Cross Product (In 2D Space)
inline float cp(vec2d &vec1, vec2d &vec2) {
  return (vec1.x * vec2.y) - (vec1.y * vec2.x);
}

inline vec2d cp(vec2d &vec, float n) { return {n * vec.y, -n * vec.x}; }

inline vec2d cp(float n, vec2d &vec) { return {-n * vec.y, n * vec.x}; }

// Distance between
inline float dist(vec2d &vec1, vec2d &vec2) {
  vec2d d(vec1.x - vec2.x, vec1.y - vec2.y);
  return d.length();
}

// Distance between squared for reduced sqrt ops
inline float distSquared(vec2d &vec1, vec2d &vec2) {
  vec2d d(vec1.x - vec2.x, vec1.y - vec2.y);
  return (d.x * d.x) + (d.y * d.y);
}

inline float minval(float a, float b) { return a < b ? a : b; }

inline float maxval(float a, float b) { return a > b ? a : b; }

inline void clamp(float &val, float min, float max) {
  val = maxval(min, minval(val, max));
}

inline float findOrientation(const vec2d &p1, const vec2d &p2, const vec2d &p) {
  const float val = (p2.y - p1.y) * (p.x - p2.x) - (p2.x - p1.x) * (p.y - p2.y);
  if (val > 0) {
    return 1;
  } // CW
  else if (val < 0) {
    return -1;
  } // CCW
  else
    return 0; // Collinear
}

inline float findOrientation(vec2d &p1, vec2d &p2, vec2d &p) {
  const float val = (p2.y - p1.y) * (p.x - p2.x) - (p2.x - p1.x) * (p.y - p2.y);
  if (val > 0) {
    return 1;
  } // CW
  else if (val < 0) {
    return -1;
  } // CCW
  else
    return 0; // Collinear
}

inline bool isLeftOf(const vec2d &p1, const vec2d &p2) {
  return p1.x < p2.x || (p1.x == p2.x && p1.y < p2.y);
}

// Rotation matrix for 2D Vectors [2x2]
struct mat2d {
  mat2d();
  mat2d(float radians);
  mat2d(float v_00, float v_01, float v_10, float v_11);

  void setMatrixRotation(float radians);

  std::array<float, 2> row_1{0};
  std::array<float, 2> row_2{0};

  const vec2d mul(vec2d &vec) const;
  mat2d transpose();
};

#endif
