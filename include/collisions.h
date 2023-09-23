#include "rigidbody.h"
#include "shape.h"
#include <memory>
#include <iostream>

#ifndef COLLISIONS_H
#define COLLISIONS_H

bool CirclevsCircle(std::shared_ptr<RigidBody> A, std::shared_ptr<RigidBody> B);
bool CirclevsRect(std::shared_ptr<RigidBody> A, std::shared_ptr<RigidBody> B);
bool RectvsRect(std::shared_ptr<RigidBody> A, std::shared_ptr<RigidBody> B);

#endif