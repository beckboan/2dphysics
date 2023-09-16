#include "shape.h"

//Shape

//Circle
Circle::Circle(float radius): radius(radius) {
        std::cout << "Circle" << std::endl;
    }

Shape::ShapeType Circle::getType() const {return ShapeType::Circle;}

float Circle::calculateArea() const {return radius * radius * M_PI;}

float Circle::calculateInertia(float& mass) const {
    return mass * radius * radius /2;
}

std::string Circle::getName() const {return "Circle";}

//Rect
Rect::Rect(float width, float height) : width(width), height(height){
        std::cout << "Rectangle" << std::endl;
    }

Shape::ShapeType Rect::getType() const {return ShapeType::Rect;}

float Rect::calculateArea() const {return width*height;}

std::string Rect::getName() const {return "Rectangle";}

float Rect::calculateInertia(float& mass) const {
    return mass*((height*height)+(width*width))/12;
}