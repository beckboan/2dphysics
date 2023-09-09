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
    virtual void calculateMass(float density) = 0;
    virtual ShapeType getType() const = 0;
    virtual Shape *Clone() const = 0;
    virtual void iniShape() = 0;

    RigidBody *body;
};

struct Circle: Shape {
    Circle(float radius);
    Shape *Clone() const;
    void calculateMass(float density);
    ShapeType getType() const;
    void iniShape();
    float radius;

};

struct Rect: Shape {
    Rect(float width, float height);
    Shape *Clone() const;
    void calculateMass(float density);
    ShapeType getType() const;
    void iniShape();

    float width;
    float height;
};

#endif