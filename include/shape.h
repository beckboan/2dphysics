#include "mathfuncs.h"
#include <iostream>
#include "rigidbody.h"
#include <cmath>
#include "SDL2/SDL.h"
#include "physicsworld.h"

#ifndef SHAPE_H
#define SHAPE_H



struct Shape {

    enum ShapeType {
        Circle, Poly
    };

    Shape() {};
    ~Shape() {}
    virtual ShapeType getType() const = 0;
    virtual std::string getName() const = 0;
    virtual void draw(SDL_Renderer * renderer, vec2d& position) = 0;
    virtual float calculateArea() const = 0;
    virtual float calculateInertia(float& mass)const = 0;
    virtual void createAABB() = 0;

};

struct Circle: public Shape {
    Circle(float radius);

    const float radius;

    ShapeType getType() const;
    std::string getName() const;
    void draw(SDL_Renderer * renderer, vec2d& position);
    float calculateArea() const;
    float calculateInertia(float& mass) const;
    void createAABB();

};

struct Poly: public Shape {
    Poly(const std::vector<vec2d>& vertecies); //Normal Poly
    Poly(float width, float height); //Rectangle Poly

    const int vertexCount = 0;
    std::vector<vec2d> vertex_list;
    std::vector<vec2d> normals;

    ShapeType getType() const;
    std::string getName() const;
    void draw(SDL_Renderer * renderer, vec2d& position);
    float calculateArea() const;
    float calculateInertia(float& mass) const;
    void createAABB();   
    void calculatePolyNormals();
};

#endif