#include "rigidbody.h"
#include "shape.h"

RigidBody::RigidBody(std::unique_ptr<Shape>& shape_, vec2d& position_, float density_) : shape(std::move(shape_)), density(density_){
    position = position_;
    velocity.assign(0,0);
    angular_velocity = 0;
    torque = 0;
    rotation = 0;
    force.assign(0,0);
    static_friction = 0.3f;
    dynamic_friction = 0.2f;
    restitution = 0.2f;
    r,g,b = 120; // TEMP COLORS 
}


void RigidBody::applyForce(const vec2d& other_force) {
    force += other_force;
}

void RigidBody::setBodyStatic() {
    m, I, inv_I, inv_m = 0.0f;
}

// void RigidBody::rigidIni() {
//     area = shape->calculateArea();
//     m = area*density;
//     inv_m = 1/m;
//     if (shape->getType() == 0) {
//         I = area*shape->inertiaCalcValue();
//         inv_I = 1/I;
//     }
//     else if (shape->getType() == 1) {
        
//     }

// }

//void RigidBody::applyImpulse(const vec2)

// Circle:
//     body->area = radius*radius*M_PI;
//     body->m = density*body->area;
//     body->inv_M = (body->m) ? 1/body->m : 0.0f;
//     body->I = body->area*radius*radius/4;
//     body->inv_I = (body->I) ? 1/body->I : 0.0f;

//     void Rect::calculateMass(float density) {
//     body->area = width*height;
//     body->m = density*body->area;
//     body->inv_M = (body->m) ? 1/body->m : 0.0f;
//     // ADD RECT I AND INV I