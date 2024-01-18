
#include "mathfuncs.h"
#include <cmath>

// Vector Methods//

vec2d::vec2d() : x(0), y(0) {}
vec2d::vec2d(float x, float y) : x(x), y(y) {}
vec2d::vec2d(const vec2d &vector) : x(vector.x), y(vector.y) {}

// Assignment Operators
// Vector Input
vec2d &vec2d::operator=(const vec2d &vec) {
    x = vec.x;
    y = vec.y;
    return *this;
}

vec2d &vec2d::operator+=(const vec2d &vec) {
    x += vec.x;
    y += vec.y;
    return *this;
}
vec2d &vec2d::operator-=(const vec2d &vec) {
    x -= vec.x;
    y -= vec.y;
    return *this;
}

// Float Input
vec2d &vec2d::operator+=(const float val) {
    x += val;
    y += val;
    return *this;
}
vec2d &vec2d::operator-=(const float val) {
    x -= val;
    y -= val;
    return *this;
}
vec2d &vec2d::operator*=(const float val) {
    x *= val;
    y *= val;
    return *this;
}
vec2d &vec2d::operator/=(const float val) {
    x /= val;
    y /= val;
    return *this;
}

vec2d vec2d::operator-() const { return {-x, -y}; }
// Arithmetic Operators
// Vector Input
vec2d vec2d::operator+(const vec2d &vec) const { return {x + vec.x, y + vec.y}; }
vec2d vec2d::operator-(const vec2d &vec) const { return {x - vec.x, y - vec.y}; }

// Float Input
vec2d vec2d::operator+(const float val) const { return {x + val, y + val}; }
vec2d vec2d::operator-(const float val) const { return {x - val, y - val}; }
vec2d vec2d::operator*(const float val) const { return {x * val, y * val}; }
vec2d vec2d::operator/(const float val) const { return {x / val, y / val}; }

float vec2d::length() const { return std::sqrt((x * x) + (y * y)); }

vec2d vec2d::normalize() const {
    float len = length();
    // std::cout << len << std::endl;
    // std::cout << x << std::endl;
    return {x / len, y / len};
}

void vec2d::assign(float x_, float y_) {
    this->x = x_;
    this->y = y_;
}

// Rotation Matrix

mat2d::mat2d() { this->setMatrixRotation(0); }

mat2d::mat2d(float radians) { this->setMatrixRotation(radians); }

mat2d::mat2d(float v_00, float v_01, float v_10, float v_11) {
    row_1[0] = v_00;
    row_1[1] = v_01;
    row_2[0] = v_10;
    row_2[1] = v_11;
}

void mat2d::setMatrixRotation(float radians) {
    float c_val = std::cos(radians);
    float s_val = std::sin(radians);

    row_1[0] = c_val;
    row_1[1] = -s_val;
    row_2[0] = s_val;
    row_2[1] = c_val;
}

mat2d mat2d::transpose() { return {row_1[0], row_2[0], row_1[1], row_2[1]}; }

vec2d mat2d::mul(vec2d &vec) { return {row_1[0] * vec.x + row_1[1] * vec.y, row_2[0] * vec.x + row_2[1] * vec.y}; }
vec2d mat2d::operator*(const vec2d &vec) { return {row_1[0] * vec.x + row_1[1] * vec.y, row_2[0] * vec.x + row_2[1] * vec.y}; }
