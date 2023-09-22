#include "shape.h"


//Shape

//Circle
Circle::Circle(float radius): radius(radius) {
        std::cout << "Circle" << std::endl;
    }

Shape::ShapeType Circle::getType() const {return ShapeType::Circle;}

std::string Circle::getName() const {return "Circle";}

void Circle::draw(SDL_Renderer * renderer, vec2d& position) { 
    int32_t radius_int = int(radius);
    int32_t position_x = int(position.x);
    int32_t position_y = int(position.y);
    const int32_t diameter = radius*2;
    int32_t x = (radius - 1);
    int32_t y = 0;
    int32_t dx = 1;
    int32_t dy = 1;
    int32_t err = dx - diameter;

    while (x >= y) {
        SDL_RenderDrawPoint(renderer, position.x + x, position.y - y);
        SDL_RenderDrawPoint(renderer, position.x + x, position.y + y);
        SDL_RenderDrawPoint(renderer, position.x - x, position.y - y);
        SDL_RenderDrawPoint(renderer, position.x - x, position.y + y);
        SDL_RenderDrawPoint(renderer, position.x + y, position.y - x);
        SDL_RenderDrawPoint(renderer, position.x + y, position.y + x);
        SDL_RenderDrawPoint(renderer, position.x - y, position.y - x);
        SDL_RenderDrawPoint(renderer, position.x - y, position.y + x);

        if (err <= 0) {
            ++y;
            err += dy;
            dy +=2 ;
        }

        if (err > 0) {
            --x;
            dx += 2;
            err += (dx-diameter);
        }
    }

    
}
// Drawing circle with midpoint circle algorithm 

float Circle::calculateArea() const {return radius * radius * M_PI;}

float Circle::calculateInertia(float& mass) const {
    return mass * radius * radius /2;
}

float Circle::getVar(char dataname) const {
    switch (dataname)
    {
    case 'r':
        return radius;
        break;   
    default: break;
    }
}


//Rect
Rect::Rect(float width, float height) : width(width), height(height){
        std::cout << "Rectangle" << std::endl;
    }

Shape::ShapeType Rect::getType() const {return ShapeType::Rect;}

std::string Rect::getName() const {return "Rectangle";}

void Rect::draw(SDL_Renderer * renderer, vec2d& position) {
    int32_t w_int = int(width);
    int32_t h_int = int(height);
    int32_t position_x = int(position.x);
    int32_t position_y = int(position.y);
    int32_t x = (0 - 1);
    int32_t y = 0;
    int32_t dx = 1;
    int32_t dy = 1;
    int32_t err = 0;

    while (x >= y) {
        SDL_RenderDrawPoint(renderer, position.x + x, position.y - y);
        SDL_RenderDrawPoint(renderer, position.x + x, position.y + y);
        SDL_RenderDrawPoint(renderer, position.x - x, position.y - y);
        SDL_RenderDrawPoint(renderer, position.x - x, position.y + y);
        SDL_RenderDrawPoint(renderer, position.x + y, position.y - x);
        SDL_RenderDrawPoint(renderer, position.x + y, position.y + x);
        SDL_RenderDrawPoint(renderer, position.x - y, position.y - x);
        SDL_RenderDrawPoint(renderer, position.x - y, position.y + x);

        if (err <= 0) {
            ++y;
            err += dy;
            dy +=2 ;
        }

        if (err > 0) {
            --x;
            dx += 2;
            err += (dx-0);
        }
    }
// Drawing circle with midpoint circle algorithm 
}

float Rect::calculateArea() const {return width*height;}

float Rect::calculateInertia(float& mass) const {
    return mass*((height*height)+(width*width))/12;
}

float Rect::getVar(char dataname) const {
    switch (dataname)
    {
    case 'h':
        return height;
        break;
    
    case 'w':
        return width;
        break;

    default: break;
    }
}