#include "shape.h"
#include <iostream>

//Shape

void Shape::setBody(const std::shared_ptr<RigidBody>& body_) {
    body = body_;
    std::shared_ptr<RigidBody> temp = body.lock();
    temp->rigidIni();
}







