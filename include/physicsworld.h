#include <vector>
#include "physicsobject.h"
#include "vec2d.h"

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

#endif