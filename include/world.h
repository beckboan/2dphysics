#ifndef WORLD
#define WORLD

#include <vector>
#include "mathfuncs.h"
#include "rigidbody.h"

struct World 
{
    


    bool addCircle (float radius, vec2d position, float density);
    bool addRect(float width, float height, vec2d position, float density);
    void addObject (RigidBody* object);
    const std::vector<std::shared_ptr<RigidBody>>& getBodies() const {return world_objects;}

    bool isValidArea(float& area);
    bool isValidDensity(float& density);

    void removePhysicsObject (std::shared_ptr<RigidBody>);
    void printPhysicsObjects();

    void worldStep();
    void checkCollisions();

    private:
    std::vector<std::shared_ptr<RigidBody>> world_objects;
};

struct WorldParams
{
    static constexpr float min_body_area = 0.01; // m^2
    static constexpr float max_body_area = 100*100; // m^2
    static constexpr float min_body_density = 200; // kg/m^3
    static constexpr float max_body_density = 25000; // kg/m^3
    const vec2d origin = vec2d(0,0);
    const vec2d world_gravity = vec2d(0,-9.81);
    const vec2d viewport = vec2d(1200,800);
};

#endif