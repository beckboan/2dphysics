#include "mathfuncs.h"
#include <iostream>
#include "rigidbody.h"
#include <cmath>
#include "SDL2/SDL.h"

#ifndef SHAPE_H
#define SHAPE_H



struct Shape {

    enum ShapeType {
        Circle, Rect
    };

    Shape() {};
    ~Shape() {}
    virtual ShapeType getType() const = 0;
    virtual std::string getName() const = 0;
    virtual void draw(SDL_Renderer * renderer, vec2d& position) = 0;
    virtual float calculateArea() const = 0;
    virtual float calculateInertia(float& mass)const = 0;

    std::shared_ptr<RigidBody> body;
};

struct Circle: public Shape {
    Circle(float radius);

    const float radius;

    ShapeType getType() const;
    std::string getName() const;
    void draw(SDL_Renderer * renderer, vec2d& position);
    float calculateArea() const;
    float calculateInertia(float& mass) const;

};

struct Rect: public Shape {
    Rect(float width, float height);

    const float width;
    const float height;


    ShapeType getType() const;
    std::string getName() const;
    void draw(SDL_Renderer * renderer, vec2d& position);
    float calculateArea() const;
    float calculateInertia(float& mass) const;



};

#endif