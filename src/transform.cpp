#include "transform.h"

Transform::Transform(vec2d& position, float angle) {
    transform_position = position;
    sin_theta = sin(angle);
    cos_theta = cos(angle);
}

Transform::Transform(float x, float y, float angle) {
    transform_position.assign(x,y);
    sin_theta = sin(angle);
    cos_theta = cos(angle);   
}