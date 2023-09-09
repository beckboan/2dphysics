#include <vector>
#include "physicsobject.h"
#include "mathfuncs.h"

#ifndef PHYSICSWORLD_H
#define PHYSICSWORLD_H

class PhysicsWorld {
    private:
    
    std::vector<PhysicsObject*> world_objects;
    const vec2d world_gravity = vec2d(0,-9.81);

    public:

    void addPhysicsObject (PhysicsObject* object);
    void removePhysicsObject (PhysicsObject* object);

    void worldStep();

};

struct WorldParams{
    static constexpr float min_body_area = 0.01; // m^2
    static constexpr float max_body_area = 100*100; // m^2
    static constexpr float min_body_density = 200; // kg/m^3
    static constexpr float max_body_density = 25000; // kg/m^3
};


#endif