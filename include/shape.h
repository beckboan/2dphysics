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
    virtual void initializeBody() = 0;
    void setShapeRef(std::shared_ptr<RigidBody>& body_);

    std::weak_ptr<RigidBody> body;
};

struct Circle: public Shape {
    Circle(float radius);

    const float radius;

    float calculateArea();
    ShapeType getType() const;
    std::string getName() const;
    void initializeBody();
    //void iniShape();
};

struct Rect: public Shape {
    Rect(float width, float height);

    const float width;
    const float height;

    float calculateArea();
    ShapeType getType() const;
    std::string getName() const;
    void initializeBody();
    //void iniShape();

};

#endif