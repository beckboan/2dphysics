#include "world.h"
#include "circle.h"
#include "collisions.h"
#include "edge.h"
#include "math.h"
#include "mathfuncs.h"
#include "polygon.h"
#include "shape.h"
#include <iostream>
#include <memory>

#define DBG(msg) std::cout << msg << std::endl;

// Creating World

World::World() { gravity.assign(0, 0); }

World::World(float g) { gravity.assign(0, -g); }

void World::setGravity(float g) { gravity.assign(0, -g); }
// Creating and Destroying Rigid Bodies

bool World::addCircle(float radius, vec2d position, float density,
                      bool is_static) {

  float area = radius * radius * M_PI;
  if (!isValidArea(area))
    return false;
  if (!isValidDensity(density))
    return false;

  std::unique_ptr<Shape> shp = std::make_unique<Circle>(radius);
  std::shared_ptr<RigidBody> bod =
      std::make_shared<RigidBody>(shp, position, density);
  bod->shape->setBody(bod);

  world_objects.emplace_back(bod);
  std::cout << "Circle Added" << std::endl;
  if (is_static) {
    bod->setBodyStatic();
  }
  return true;
};

bool World::addRect(float width, float height, vec2d position, float density,
                    bool is_static) {

  float area = width * height;

  if (!isValidArea(area))
    return false;
  if (!isValidDensity(density))
    return false;

  std::unique_ptr<Shape> shp = std::make_unique<Poly>(width, height);
  std::shared_ptr<RigidBody> bod =
      std::make_shared<RigidBody>(shp, position, density);
  bod->shape->setBody(bod);

  world_objects.push_back(bod);
  std::cout << "Rectangle Added" << std::endl;
  if (is_static) {
    bod->setBodyStatic();
  }
  return true;
}

bool World::addPoly(std::vector<vec2d> verticies, vec2d position, float density,
                    bool is_static) {
  if (!isValidDensity(density))
    return false;

  std::unique_ptr<Shape> shp = std::make_unique<Poly>(verticies);
  std::shared_ptr<RigidBody> bod =
      std::make_shared<RigidBody>(shp, position, density);
  bod->shape->setBody(bod);

  if (!isValidArea(bod->area))
    return false;

  world_objects.push_back(bod);
  std::cout << "Poly Added" << std::endl;
  if (is_static) {
    bod->setBodyStatic();
  }
  return true;
}

bool World::addEdge(vec2d s, vec2d e, bool is_static) {
  vec2d position = (s + e) / 2;
  std::unique_ptr<Shape> shp = std::make_unique<Edge>(s, e);
  std::shared_ptr<RigidBody> bod =
      std::make_shared<RigidBody>(shp, position, 1);
  bod->shape->setBody(bod);
  world_objects.push_back(bod);
  // std::cout << "Edge Added" << std::endl;
  if (is_static) {
    bod->setBodyStatic();
  }
  return true;
}

void World::removePhysicsObject(std::shared_ptr<RigidBody>){

};

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
          // std::cout << collision->getContactCount() << std::endl;
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

  for (auto c : contact_list) {
    c->solve();
  }

  // std::cout << dt << std::endl;
  integrateVelocities(dt);
  updateAABB();
}

void World::integrateForces(float dt) {
  for (auto bod : world_objects) {
    if (bod->inv_m == 0.0)
      continue;
    bod->velocity += (bod->force * bod->inv_m + gravity) * dt;
    bod->angular_velocity += (bod->torque * bod->inv_I) * dt;
    bod->force.assign(0, 0);
    bod->torque = 0;
  }
}

void World::integrateVelocities(float dt) {
  for (auto bod : world_objects) {
    if (bod->inv_m == 0.0)
      continue;
    bod->position += bod->velocity * dt;
    bod->rotation += bod->angular_velocity * dt;
    bod->setRotation(bod->rotation);
    // std::cout << bod->rotation << std::endl;
  }
}

void World::updateAABB() {
  for (auto bod : world_objects) {
    bod->shape->createAABB();
  }
}
