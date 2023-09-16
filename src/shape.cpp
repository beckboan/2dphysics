#include "shape.h"

//Shape
void Shape::setShapeRef(std::shared_ptr<RigidBody>& body_) {
        std::cout << body_.use_count() << std::endl;
        body = body_;
    }

//Circle
Circle::Circle(float radius): radius(radius) {
        std::cout << "Circle" << std::endl;
    }

void Circle::initializeBody() {
    std::cout << "Circle Initialized" << std::endl;
}

Shape::ShapeType Circle::getType() const {return ShapeType::Circle;}

float Circle::calculateArea() {return radius * radius * M_PI;}

std::string Circle::getName() const {return "Circle";}

//Rect
Rect::Rect(float width, float height) : width(width), height(height){
        std::cout << "Rectangle" << std::endl;
    }

void Rect::initializeBody() {
    std::cout << "Rectangle Initialized" << std::endl;
}

Shape::ShapeType Rect::getType() const {return ShapeType::Rect;}

float Rect::calculateArea() {return width*height;}

std::string Rect::getName() const {return "Rectangle";}

