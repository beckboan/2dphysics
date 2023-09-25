#ifndef CIRCLE_H
#define CIRCLE_H

#include "shape.h"
#include <iostream>

struct Circle: public Shape {
    Circle(float radius);

    const float radius;

    ShapeType getType() const;
    std::string getName() const;
    void draw(SDL_Renderer * renderer, vec2d& position);
    void calculateMassProperties(float& density);
    void createAABB();

};

#endif