#include "collisions.h"
#include "shape.h"
#include "polygon.h"
#include "circle.h"


Manifold::Manifold(std::shared_ptr<RigidBody> A_, std::shared_ptr<RigidBody> B_): A(A_), B(B_) 
{
    std::cout << "Manifold Created" << std::endl;
}

void Manifold::collisionCaller() {
    Shape::ShapeType A_type = A->shape->getType();
    Shape::ShapeType B_type = B->shape->getType();

    if (A_type == Shape::ShapeType::Poly && B_type == Shape::ShapeType::Poly) 
    {
        PolyvsPoly(A, B);
    }
    else if (A_type == Shape::ShapeType::Poly && B_type == Shape::ShapeType::Circle) {
        CirclevsPoly(B, A);
    }
    else if (A_type == Shape::ShapeType::Circle && B_type == Shape::ShapeType::Poly) {
        CirclevsPoly(A, B);
    }
    else if (A_type == Shape::ShapeType::Circle && B_type == Shape::ShapeType::Circle) {
        CirclevsCircle(B, A);
    }
}

bool CirclevsCircle(std::shared_ptr<RigidBody> A, std::shared_ptr<RigidBody> B) 
{
    std:: cout << "Circle Collision" << std::endl;
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

bool CirclevsPoly(std::shared_ptr<RigidBody> A, std::shared_ptr<RigidBody> B) 
{
    std:: cout << "Circle/Polygon Collision" << std::endl;
    Poly* R1 = dynamic_cast<Poly*>(A->shape.get());
    Circle* C2 = dynamic_cast<Circle*>(B->shape.get());
    return true;
}

bool PolyvsPoly(std::shared_ptr<RigidBody> A, std::shared_ptr<RigidBody> B) 
{
    std:: cout << "Polygon Collision" << std::endl;
    Poly* R1 = dynamic_cast<Poly*>(A->shape.get());    
    Poly* R2 = dynamic_cast<Poly*>(B->shape.get());
    return true;
}