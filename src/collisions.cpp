#include "collisions.h"

void collisionCaller(std::shared_ptr<RigidBody> body1, std::shared_ptr<RigidBody> body2) {}

bool CirclevsCircle(std::shared_ptr<RigidBody> A, std::shared_ptr<RigidBody> B) {
    Circle* C1 = dynamic_cast<Circle*>(A->shape.get());;
    Circle* C2 = dynamic_cast<Circle*>(B->shape.get());

    vec2d norm = B->position - A->position;
    
    float dist = norm.length();
    float radii = C1->radius + C2->radius;

    if (dist > radii) {return false;}

    if (dist == 0) {
    }


    return true;
}

bool CirclevsRect(std::shared_ptr<RigidBody> A, std::shared_ptr<RigidBody> B) {
    Rect* R1 = dynamic_cast<Rect*>(A->shape.get());
    Circle* C2 = dynamic_cast<Circle*>(B->shape.get());
    return true;
}

bool RectvsRect(std::shared_ptr<RigidBody> A, std::shared_ptr<RigidBody> B) {
    Rect* R1 = dynamic_cast<Rect*>(A->shape.get());    
    Rect* R2 = dynamic_cast<Rect*>(B->shape.get());
    return true;
}