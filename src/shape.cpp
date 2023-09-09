#include "shape.h"

Circle::Circle(float radius): radius(radius) {
        std::cout << "Circle" << std::endl;
    }
Shape::ShapeType Circle::getType() const {return ShapeType::Circle;}
float Circle::calculateArea() {
    return radius * radius * M_PI;
}
//void Circle::iniShape() {calculateMass(0.5f);}


Rect::Rect(float width, float height) : width(width), height(height){
        std::cout << "Rectangle" << std::endl;
    }
Shape::ShapeType Rect::getType() const {return ShapeType::Rect;}
float Rect::calculateArea() {
    return width*height;
}

//void Rect::iniShape() {calculateMass(0.5f);}