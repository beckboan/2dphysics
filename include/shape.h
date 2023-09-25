#ifndef SHAPE_H
#define SHAPE_H

#include "mathfuncs.h"
#include "rigidbody.h"
#include "SDL2/SDL.h"
#include <vector>
#include <memory>

#define max_poly_count 32

struct Shape {

    enum ShapeType {
        Circle, Poly
    };

    Shape() {};
    ~Shape() {}
    virtual ShapeType getType() const = 0;
    virtual std::string getName() const = 0;
    virtual void draw(SDL_Renderer * renderer, vec2d& position) = 0;
    virtual void createAABB() = 0;
    virtual void calculateMassProperties(float& density) = 0;

    std::weak_ptr<RigidBody> body;
    void setBody(const std::shared_ptr<RigidBody>& body_);

};

#endif