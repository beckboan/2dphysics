#include <vector>
#include "mathfuncs.h"
#include "rigidbody.h"

#ifndef PHYSICSWORLD_H
#define PHYSICSWORLD_H

struct PhysicsWorld {
    
    std::vector<std::shared_ptr<RigidBody>> world_objects;

    bool addCircle (float radius, vec2d position, float density);
    bool addRect(float width, float height, vec2d position, float density);
    void addObject (RigidBody* object);

    bool isValidArea(float& area);
    bool isValidDensity(float& density);

    void removePhysicsObject (std::shared_ptr<RigidBody>);
    void printPhysicsObjects();

    void worldStep();
};

struct WorldParams{
    static constexpr float min_body_area = 0.01; // m^2
    static constexpr float max_body_area = 100*100; // m^2
    static constexpr float min_body_density = 200; // kg/m^3
    static constexpr float max_body_density = 25000; // kg/m^3
    const vec2d origin = vec2d(0,0);
    const vec2d world_gravity = vec2d(0,-9.81);
    const vec2d viewport = vec2d(1200,800);
};


#endif