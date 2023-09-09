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
    static constexpr float min_body_mass = 0.01; // kg
    static constexpr float max_body_mass = 1000000; //kg
};


#endif