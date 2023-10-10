#include "shape.h"
#include <iostream>

//Shape
Shape::~Shape() {};

void Shape::setBody(const std::shared_ptr<RigidBody>& body_) 
{
    body = body_;
    std::shared_ptr<RigidBody> body_ref = body.lock();
    body_ref->rigidIni();
}

std::tuple<int,int,int,int> Shape::getAABB()
{
    return std::tuple<float, float, float, float>(aabb.getMin().x,aabb.getMin().y,aabb.getMax().x,aabb.getMax().y);
}

void Shape::setSpaceOrientation(float radians)
{
    rotation->setMatrixRotation(radians);
}





