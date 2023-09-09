#include "shape.h"

Circle::Circle(float radius): radius(radius) {std::cout << "Circle" << std::endl;}
Shape* Circle::Clone() const {
    return new Circle(radius);
}
void Circle::calculateMass(float density) {
    body->area = radius*radius*M_PI;
    body->m = density*body->area;
    body->inv_M = (body->m) ? 1/body->m : 0.0f;
    body->I = body->area*radius*radius/4;
    body->inv_I = (body->I) ? 1/body->I : 0.0f;
}
Shape::ShapeType Circle::getType() const {return ShapeType::Circle;}
void Circle::iniShape() {calculateMass(0.5f);}


Rect::Rect(float width, float height) : width(width), height(height) {std::cout << "Rectangle" << std::endl;}
Shape* Rect::Clone() const {
    return new Rect(width, height);
}
void Rect::calculateMass(float density) {
    body->area = width*height;
    body->m = density*body->area;
    body->inv_M = (body->m) ? 1/body->m : 0.0f;
    // ADD RECT I AND INV I
}
Shape::ShapeType Rect::getType() const {return ShapeType::Rect;}
void Rect::iniShape() {calculateMass(0.5f);}