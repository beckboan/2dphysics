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
    virtual ShapeType getType() const = 0;
    virtual float calculateArea() = 0;
   // virtual void iniShape() = 0;

};

struct Circle: public Shape {
    Circle(float radius);
    float calculateArea();
    ShapeType getType() const;
    //void iniShape();
    float radius;

};

struct Rect: public Shape {
    Rect(float width, float height);
    float calculateArea();
    ShapeType getType() const;
    //void iniShape();

    float width;
    float height;
};

#endif