#include "collisions.h"
#include "shape.h"
#include "polygon.h"
#include "circle.h"

void collisionCaller(std::shared_ptr<RigidBody> body1, std::shared_ptr<RigidBody> body2) {}

bool CirclevsCircle(std::shared_ptr<RigidBody> A, std::shared_ptr<RigidBody> B) {
    Circle* C1 = dynamic_cast<Circle*>(A->shape.get());
    Circle* C2 = dynamic_cast<Circle*>(B->shape.get());

    float distance = dist(A->position,B->position);
    
    float radii = C1->radius + C2->radius;

    if (distance >= radii) {return false;}

    vec2d normal = (B->position - A->position).normalize();
    float depth = radii - distance;

    A->move(normal*depth/-2);
    B->move(normal*depth/2);

    return true;
}

bool CirclevsRect(std::shared_ptr<RigidBody> A, std::shared_ptr<RigidBody> B) {
    Poly* R1 = dynamic_cast<Poly*>(A->shape.get());
    Circle* C2 = dynamic_cast<Circle*>(B->shape.get());
    return true;
}

bool RectvsRect(std::shared_ptr<RigidBody> A, std::shared_ptr<RigidBody> B) {
    Poly* R1 = dynamic_cast<Poly*>(A->shape.get());    
    Poly* R2 = dynamic_cast<Poly*>(B->shape.get());
    return true;
}