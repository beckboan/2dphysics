#ifndef WORLD
#define WORLD

#include <vector>
#include "mathfuncs.h"
#include "rigidbody.h"
#include "collisions.h"
#include "scene.h"

struct World 
{
    World();
    World(const float g);

    bool addCircle (float radius, vec2d position, float density);
    bool addRect(float width, float height, vec2d position, float density);
    bool addPoly(std::vector<vec2d> verticies, vec2d position, float density);

    const std::vector<std::shared_ptr<RigidBody>>& getBodies() const {return world_objects;}

    void removePhysicsObject (std::shared_ptr<RigidBody>);
    void printPhysicsObjects();

    void worldStep(float dt);
    void checkCollisions();

    void renderObjects();

    private:
    std::vector<std::shared_ptr<RigidBody>> world_objects;
    std::vector<std::shared_ptr<Manifold>> contact_list;
    vec2d gravity;
    const vec2d origin = vec2d(0,0);
    std::unique_ptr<Scene> scene;
    void integrateForces(float dt);
    void integrateVelocities(float dt);

    public:
    static constexpr float min_body_area = 0.01; // m^2
    static constexpr float max_body_area = 100*100; // m^2
    static constexpr float min_body_density = 200; // kg/m^3
    static constexpr float max_body_density = 25000; // kg/m^3
    
};


// Physics Validation

inline bool isValidArea(float area) {
    if(area < World::min_body_area || area > World::max_body_area) 
    {
        std::cout << "Area outside of world parameters" << std::endl;
        return false;
    }
    return true;
}

inline bool isValidDensity(float density) {
    if(density < World::min_body_density || density > World::max_body_density) 
    {
        std::cout << "Density outside of world parameters" << std::endl;
        return false;
    }
    return true;
}

#endif