#ifndef SHAPE_H
#define SHAPE_H

#include "mathfuncs.h"
#include "rigidbody.h"
#include "SDL2/SDL.h"
#include <vector>
#include <memory>
#include "AABB.h"

#define max_poly_count 32

struct Shape 
{

    enum ShapeType {
        Circle, Poly
    };

    Shape() {};
    ~Shape() {}
    virtual ShapeType getType() const = 0;
    virtual std::string getName() const = 0;
    virtual void createAABB() = 0;
    virtual void calculateMassProperties(float density) = 0;  

    std::weak_ptr<RigidBody> body;
    void setBody(const std::shared_ptr<RigidBody>& body_);

    std::unique_ptr<AABB> aabb = std::make_unique<AABB>();
    std::tuple<int, int, int, int> getAABB();

    std::unique_ptr<mat2d> rotation = std::make_unique<mat2d>();
    void setSpaceOrientation(float radians);
    
};




#endif