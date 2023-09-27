#ifndef CIRCLE_H
#define CIRCLE_H

#include "shape.h"
#include <iostream>
#include <vector>
#include "mathfuncs.h"

struct Circle: public Shape 
{
    Circle(float radius);

    const float radius;

    ShapeType getType() const;
    std::string getName() const;
    void calculateMassProperties(float density);
    void createAABB();

};

#endif