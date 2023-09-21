#include "shape.h"


//Shape

//Circle
Circle::Circle(int radius): radius(radius) {
        std::cout << "Circle" << std::endl;
    }

Shape::ShapeType Circle::getType() const {return ShapeType::Circle;}

std::string Circle::getName() const {return "Circle";}

void Circle::draw(SDL_Renderer * renderer, vec2d& position) { 
    float diameter = radius*2;
    float x = (radius - 1);

}
// Drawing circle with midpoint circle algorithm 

float Circle::calculateArea() const {return radius * radius * M_PI;}

float Circle::calculateInertia(float& mass) const {
    return mass * radius * radius /2;
}



//Rect
Rect::Rect(int width, int height) : width(width), height(height){
        std::cout << "Rectangle" << std::endl;
    }

Shape::ShapeType Rect::getType() const {return ShapeType::Rect;}

std::string Rect::getName() const {return "Rectangle";}

void Rect::draw(SDL_Renderer * renderer, vec2d& position) {}

float Rect::calculateArea() const {return width*height;}

float Rect::calculateInertia(float& mass) const {
    return mass*((height*height)+(width*width))/12;
}