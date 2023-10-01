#include <iostream>
#include "world.h"
#include "mathfuncs.h"
#include "shape.h"
#include "circle.h"
#include "polygon.h"
#include "collisions.h"

#define DBG(msg) std::cout << msg <<std::endl;

//Creating World

World::World() {gravity.assign(0,0);}

World::World(float g) {gravity.assign(0, -g);}

//Creating and Destroying Rigid Bodies

bool World::addCircle (float radius, vec2d position, float density)
{

    float area =  radius * radius * M_PI;
    if (!isValidArea(area)) return false;
    if (!isValidDensity(density)) return false;

    std::unique_ptr<Shape> shp = std::make_unique<Circle>(radius);
    std::shared_ptr<RigidBody> bod = std::make_shared<RigidBody>(shp,position,density);
    bod->shape->setBody(bod);

    world_objects.emplace_back(bod);
    std::cout << "Circle Added" << std::endl;
    return true;
};

bool World::addRect(float width, float height, vec2d position, float density) 
{

    float area =  width * height;

    if (!isValidArea(area)) return false;
    if (!isValidDensity(density)) return false;

    std::unique_ptr<Shape> shp = std::make_unique<Poly>(width, height);
    std::shared_ptr<RigidBody> bod = std::make_shared<RigidBody>(shp,position,density);
    bod->shape->setBody(bod);
    
    world_objects.emplace_back(bod);
    std::cout << "Rectangle Added" << std::endl;
    return true;

}

bool World::addPoly(std::vector<vec2d> verticies, vec2d position, float density)
{
    if (!isValidDensity(density)) return false;

    std::unique_ptr<Shape> shp = std::make_unique<Poly>(verticies);
    std::shared_ptr<RigidBody> bod = std::make_shared<RigidBody>(shp,position,density);
    bod->shape->setBody(bod);

    std::cout << bod->area << std::endl;
    if (!isValidArea(bod->area)) return false;

    world_objects.emplace_back(bod);
    std::cout << "Poly Added" << std::endl;
    return true;
}

void World::removePhysicsObject (std::shared_ptr<RigidBody>) 
{

};

void World::checkCollisions() {
    //Brute Force for now, want to optimize in future
    unsigned int size = world_objects.size();
    for (unsigned int i = 0; i < size; i ++) 
    {
        std::shared_ptr<RigidBody> A = world_objects[i];
        for (unsigned int j = i + 1; j < size; j ++)
        {
            std::shared_ptr<RigidBody> B = world_objects[j];

            if (checkAABBOverlap(A->shape->aabb, B->shape->aabb)) {
                std::shared_ptr<Manifold> collision = std::make_shared<Manifold>(A, B);
                collision->collisionCaller();
            }
        }
    }
}

void World::worldStep() {
    checkCollisions();

}


