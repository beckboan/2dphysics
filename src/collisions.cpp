#include "collisions.h"
#include "shape.h"
#include "polygon.h"
#include "circle.h"


Manifold::Manifold(std::shared_ptr<RigidBody> A_, std::shared_ptr<RigidBody> B_): A(A_), B(B_) 
{
    std::cout << "Manifold Created" << std::endl;
    e = std::min(A->restitution, B->restitution);
    df = std::sqrt(A->dynamic_friction * B->dynamic_friction);
    sf = std::sqrt(A->static_friction * B->dynamic_friction);
}

void Manifold::collisionCaller() {
    Shape::ShapeType A_type = A->shape->getType();
    Shape::ShapeType B_type = B->shape->getType();

    if (A_type == Shape::ShapeType::Poly && B_type == Shape::ShapeType::Poly) 
    {
        PolyvsPoly();
    }
    else if (A_type == Shape::ShapeType::Poly && B_type == Shape::ShapeType::Circle) {
        PolyvsCircle();
    }
    else if (A_type == Shape::ShapeType::Circle && B_type == Shape::ShapeType::Poly) {
        CirclevsPoly();
    }
    else if (A_type == Shape::ShapeType::Circle && B_type == Shape::ShapeType::Circle) {
        CirclevsCircle();
    }
}

void Manifold::CirclevsCircle() 
{
    std:: cout << "Circle Collision" << std::endl;
    Circle* C1 = dynamic_cast<Circle*>(A->shape.get());
    Circle* C2 = dynamic_cast<Circle*>(B->shape.get());

    float distSq = distSquared(A->position, B->position);
    
    float radii = C1->radius + C2->radius;

    if (distSq > (radii*radii)) 
    {
        contact_count = 0;
        return;
    }

    float distance = dist(A->position,B->position);

    contact_count = 1;

    // If distance is 0, the circles are directly overlapping and their
    // contact is at the center of A or B (same thing)

    if (distance == 0.0f) 
    {
        penetration = C1->radius;
        contacts[0] = A->position;
        normal.assign(1, 0);
    }

    else 
    {
        normal = (B->position - A->position).normalize();
        penetration = radii - distance;
        contacts[0] = normal * C1->radius + A->position;
    }
}

void Manifold::CirclevsPoly() 
{
    std:: cout << "Circle/Polygon Collision" << std::endl;
    Poly* R2 = dynamic_cast<Poly*>(A->shape.get());
    Circle* C1 = dynamic_cast<Circle*>(B->shape.get());
}

void Manifold::PolyvsCircle() 
{
    CirclevsPoly();
    //rememebr to reverse the normal
}

void Manifold::PolyvsPoly() 
{
    std:: cout << "Polygon Collision" << std::endl;
    Poly* R1 = dynamic_cast<Poly*>(A->shape.get());    
    Poly* R2 = dynamic_cast<Poly*>(B->shape.get());
}

void Manifold::solve() 
{
    for (auto c : contacts)
    {
        vec2d A_c = c - A->position;
        vec2d B_c = c - B->position;

        vec2d r_vel = B->velocity + cp(B->angular_velocity, A_c) - A->velocity - cp(A->angular_velocity, B_c);

        float r_speed = dp(r_vel, normal);

        if (r_speed >= 0) return;

    }
}
