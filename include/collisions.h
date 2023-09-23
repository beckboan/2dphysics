#include "rigidbody.h"
#include "shape.h"
#include <memory>
#include <iostream>

#ifndef COLLISIONS_H
#define COLLISIONS_H

void collisionCaller(std::shared_ptr<RigidBody> body1, std::shared_ptr<RigidBody> body2) {}

bool CirclevsCircle(std::shared_ptr<RigidBody> A, std::shared_ptr<RigidBody> B) {
    //std::unique_ptr<Circle> circle1 = dynamic_cast<std::unique_ptr<Circle>>(body1->shape);
    Circle* C1 = (Circle*)A->shape.get();
    Circle* C2 = (Circle*)B->shape.get();

    vec2d norm = B->position - A->position;
    
    float dist = norm.length();
    float radius = C1->radius + C2->radius;


    return true;
}

bool RectvsCircle(std::shared_ptr<RigidBody> A, std::shared_ptr<RigidBody> B) {
    Rect* R1 = (Rect*)A->shape.get();
    Circle* C2 = (Circle*)B->shape.get();
    return true;
}

bool CirclevsRect(std::shared_ptr<RigidBody> A, std::shared_ptr<RigidBody> B) {
    Circle* C1 = (Circle*)A->shape.get();   
    Rect* R2 = (Rect*)B->shape.get();
    return true;

}

bool RectvsRect(std::shared_ptr<RigidBody> A, std::shared_ptr<RigidBody> B) {
    Rect* R1 = (Rect*)A->shape.get();    
    Rect* R2 = (Rect*)B->shape.get();
    return true;
}

#endif