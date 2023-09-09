#include <iostream>
#include "mathfuncs.h"
#include "shape.h"
#include <typeinfo>
#include "rigidbody.h"

int main(int, char**){
    Circle c(5.0f);
    RigidBody b = RigidBody(&c, vec2d(0.0,0.0));
    Rect r(10, 10);
    RigidBody z = RigidBody(&r, vec2d(0.0,0.0));

}
