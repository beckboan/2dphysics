#include "mathfuncs.h"
#include <iostream>
#include "rigidbody.h"
#include <cmath>

#ifndef COLLIDERS_H
#define COLLIDERS_H



struct Shape {

    enum ShapeType {
        Circle, Rect
    };

    Shape() {};
    ~Shape() {}
    virtual ShapeType getType() const = 0;
    virtual std::string getName() const = 0;
    virtual float calculateArea() const = 0;
    virtual float calculateInertia(float& mass)const = 0;

    std::shared_ptr<RigidBody> body;
};

struct Circle: public Shape {
    Circle(float radius);

    const float radius;

    float calculateInertia(float& mass) const;
    float calculateArea() const;
    ShapeType getType() const;
    std::string getName() const;

};

struct Rect: public Shape {
    Rect(float width, float height);

    const float width;
    const float height;

    float calculateInertia(float& mass) const;
    float calculateArea() const;
    ShapeType getType() const;
    std::string getName() const;

};

#endif