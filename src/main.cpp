#include <iostream>
#include "vec2d.h"

int main(int, char**){
    vec2d vector1(2.00,2.00);
    vec2d vector2(2.00, 1.00);
    auto product = dp(vector1, vector2);
    std::cout << product << std::endl;
    
    //std::cout << vector1.x << ", " << vector1.y << std::endl;
}
