#define _USE_MATH_DEFINES

#include "world.h"
#include "circle.h"
#include "collisions.h"
#include "edge.h"
#include "mathfuncs.h"
#include "polygon.h"
#include "shape.h"
#include "rigidbody.h"
#include <stdexcept>

#include <cmath>
#include <iostream>
#include <memory>

#define DBG(msg) std::cout << msg << std::endl;

// Creating World

World::World() { gravity.assign(0, 0); }

World::World(float g) { gravity.assign(0, -g); }

[[maybe_unused]] void World::setGravity(float g) { gravity.assign(0, -g); }

void World::addCircle(float radius, vec2d position, float density, bool is_static) {
    float area = radius * radius * float(M_PI);
    if (!isValidArea(area))
        throw std::invalid_argument("Invalid Radius");
    if (!isValidDensity(density))
        throw std::invalid_argument("Invalid Density");

    std::unique_ptr<Shape> shp = std::make_unique<Circle>(radius);
    std::shared_ptr<RigidBody> bod = std::make_shared<RigidBody>(shp, position, density);
    bod->shape->setBody(bod);

    world_objects.emplace_back(bod);
    std::cout << "Circle Added" << std::endl;
    if (is_static) {
        bod->setBodyStatic();
    }
}

void World::addRect(float width, float height, vec2d position, float density, bool is_static) {

    float area = width * height;

    if (!isValidArea(area))
        throw std::invalid_argument("Invalid Area");
    if (!isValidDensity(density))
        throw std::invalid_argument("Invalid Density");

    std::unique_ptr<Shape> shp = std::make_unique<Poly>(width, height);
    std::shared_ptr<RigidBody> bod = std::make_shared<RigidBody>(shp, position, density);
    bod->shape->setBody(bod);

    world_objects.push_back(bod);
    std::cout << "Rectangle Added" << std::endl;
    if (is_static) {
        bod->setBodyStatic();
    }
}

void World::addPoly(std::vector<vec2d> verticies, vec2d position, float density, bool is_static) {
    try {
        if (!isValidDensity(density))
            throw std::invalid_argument("Invalid Density");

        std::unique_ptr<Shape> shp = std::make_unique<Poly>(verticies);
        std::shared_ptr<RigidBody> bod = std::make_shared<RigidBody>(shp, position, density);
        bod->shape->setBody(bod);

        if (!isValidArea(bod->area))
            throw std::invalid_argument("Invalid Area");

        world_objects.push_back(bod);
        std::cout << "Poly Added" << std::endl;
        if (is_static) {
            bod->setBodyStatic();
        }
    }
    catch (const std::invalid_argument &e) {
        throw;
    }
}

void World::addEdge(const vec2d &s, const vec2d &e) {
    if (s.x == e.x && s.y == e.y){
        throw std::invalid_argument("Invalid Edge");
    }
    vec2d position = (s + e) * 0.5;
    std::unique_ptr<Shape> shp = std::make_unique<Edge>(s, e);
    std::shared_ptr<RigidBody> bod = std::make_shared<RigidBody>(shp, position, 1);
    bod->shape->setBody(bod);
    world_objects.push_back(bod);
    std::cout << "Edge Added" << std::endl;
    bod->setBodyStatic();
}

void World::removePhysicsObject(const std::shared_ptr<RigidBody> &) {}

void World::checkCollisions() {
    // Brute Force for now, want to optimize in future

    unsigned int size = world_objects.size();
    for (unsigned int i = 0; i < size; i++) {
        std::shared_ptr<RigidBody> A = world_objects[i];
        for (unsigned int j = i + 1; j < size; j++) {
            std::shared_ptr<RigidBody> B = world_objects[j];

            if (checkAABBOverlap(A->shape->aabb, B->shape->aabb)) {
                std::shared_ptr<Manifold> collision = std::make_shared<Manifold>(A, B);
                // std::cout << "Collision Detected" << std::endl;
                collision->collisionCaller();
                if (collision->getContactCount() > 0) {
                    contact_list.push_back(collision);
                }
            }
        }
    }
}

void World::worldStep(float dt) {

    contact_list.clear();
    checkCollisions();

    integrateForces(dt);

    for (const auto &c: contact_list) {
        c->solve();
    }

    integrateVelocities(dt);
    for (const auto &c: contact_list) {
        c->correctPositions();
    }
    updateAABB();
}

void World::integrateForces(float dt) {
    for (const auto &bod: world_objects) {
        if (bod->inv_m == 0.0)
            continue;
        bod->velocity += (bod->force * bod->inv_m + gravity) * dt;
        bod->angular_velocity += (bod->torque * bod->inv_I) * dt;
        bod->force.assign(0, 0);
        bod->torque = 0;
    }
}

void World::integrateVelocities(float dt) {
    for (const auto &bod: world_objects) {
        if (bod->inv_m == 0.0)
            continue;
        bod->position += bod->velocity * dt;
        bod->rotation += bod->angular_velocity * dt;
        bod->setRotation(bod->rotation);
    }
}

void World::updateAABB() {
    for (const auto &bod: world_objects) {
        bod->shape->createAABB();
    }
}

void World::clearBodies() { world_objects.clear(); }

float * World::getGravity() {
    return &gravity.y;
}