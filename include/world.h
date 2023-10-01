#ifndef WORLD
#define WORLD

#include <vector>
#include "mathfuncs.h"
#include "rigidbody.h"

struct World 
{
    
    bool addCircle (float radius, vec2d position, float density);
    bool addRect(float width, float height, vec2d position, float density);
    bool addPoly(std::vector<vec2d> verticies, vec2d position, float density);

    const std::vector<std::shared_ptr<RigidBody>>& getBodies() const {return world_objects;}

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
};

// Physics Validation

inline bool isValidArea(float area) {
    if(area < WorldParams::min_body_area || area > WorldParams::max_body_area) 
    {
        std::cout << "Area outside of world parameters" << std::endl;
        return false;
    }
    return true;
}

inline bool isValidDensity(float density) {
    if(density < WorldParams::min_body_density || density > WorldParams::max_body_density) 
    {
        std::cout << "Density outside of world parameters" << std::endl;
        return false;
    }
    return true;
}

#endif