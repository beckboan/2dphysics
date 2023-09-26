#include "shape.h"
#include <iostream>

//Shape

void Shape::setBody(const std::shared_ptr<RigidBody>& body_) 
{
    body = body_;
    std::shared_ptr<RigidBody> body_ref = body.lock();
    body_ref->rigidIni();
}







