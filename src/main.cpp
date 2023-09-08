#include <iostream>
#include "vec2d.h"

int main(int, char**){
    vec2d vector1(3.12,4.12);
    vec2d vector2(2.00, 1.00);
    
    std::cout << vector1.x << ", " << vector1.y << std::endl;
}
