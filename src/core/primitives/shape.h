#ifndef SHAPE_H
#define SHAPE_H

#include "AABB.h"
#include "mathfuncs.h"
#include "rigidbody.h"
#include <memory>
#include <iostream>

#define max_poly_count 32

struct Shape {

    enum ShapeType {
        Circle, Poly, Edge
    };

    Shape() = default;

    virtual ~Shape() = 0;

    virtual ShapeType getType() const = 0;

    virtual std::string getName() const = 0;

    virtual void createAABB() = 0;

    virtual void calculateMassProperties(float density) = 0;

    std::weak_ptr<RigidBody> body;

    void setBody(const std::shared_ptr<RigidBody> &body_);

    AABB aabb = AABB();

    std::tuple<int, int, int, int> getAABB() const;

    std::unique_ptr<mat2d> rotation = std::make_unique<mat2d>();

    void setSpaceOrientation(float radians) const;
};

#endif
