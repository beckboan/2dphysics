#include "shape.h"
#include <iostream>

// Shape
Shape::~Shape(){};

void Shape::setBody(const std::shared_ptr<RigidBody> &body_) {
  body = body_;
  std::shared_ptr<RigidBody> body_ref = body.lock();
  body_ref->rigidIni();
}

std::tuple<int, int, int, int> Shape::getAABB() {
  // std::cout << aabb.getMin().x << aabb.getMin().y << aabb.getMax().x
  //           << aabb.getMax().y << std::endl;
  return std::tuple<int, int, int, int>(aabb.getMin().x, aabb.getMin().y,
                                        aabb.getMax().x, aabb.getMax().y);
}

void Shape::setSpaceOrientation(float radians) {
  rotation->setMatrixRotation(radians);
}
