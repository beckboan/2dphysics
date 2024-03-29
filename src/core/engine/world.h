#ifndef WORLD
#define WORLD

#include "collisions.h"
#include "mathfuncs.h"
#include "rigidbody.h"
#include "AABB.h"
#include <iostream>
#include <vector>

struct World {
    World();

    explicit World(float g);

    void addCircle(float radius, vec2d position, float density, bool is_static);

    void addRect(float width, float height, vec2d position, float density, bool is_static);

    void addPoly(std::vector<vec2d> verticies, vec2d position, float density, bool is_static);

    void addEdge(const vec2d &s, const vec2d &e);

    [[nodiscard]] const std::vector<std::shared_ptr<RigidBody>> &getBodies() const { return world_objects; }

    void setGravity(float g);

    float * getGravity();

    void removePhysicsObject(const std::shared_ptr<RigidBody> &);

    void clearBodies();

    void printPhysicsObjects();

    void worldStep(float dt);

    void checkCollisions();

    std::vector<std::shared_ptr<Manifold>> contact_list;

private:
    std::vector<std::shared_ptr<RigidBody>> world_objects;
    vec2d gravity;
    const vec2d origin = vec2d(0, 0);

    void integrateForces(float dt);

    void integrateVelocities(float dt);

    void updatePositions();

    void updateAABB();

    unsigned int iterations = 1;

public:
    static constexpr float min_body_area = 0.01;      // m^2
    static constexpr float max_body_area = 100 * 100; // m^2
    static constexpr float min_body_density = 500;    // kg/m^3
    static constexpr float max_body_density = 25000;  // kg/m^3
};

// Physics Validation

inline bool isValidArea(float area) {
    if (area < World::min_body_area || area > World::max_body_area) {
        return false;
    }
    return true;
}

inline bool isValidDensity(float density) {
    if (density < World::min_body_density || density > World::max_body_density) {
        return false;
    }
    return true;
}

#endif
