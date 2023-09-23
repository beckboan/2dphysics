#include "shape.h"
#include <cassert>


//Shape

//Circle
Circle::Circle(float radius): radius(radius) {
        std::cout << "Circle" << std::endl;
    }

Shape::ShapeType Circle::getType() const {return ShapeType::Circle;}

std::string Circle::getName() const {return "Circle";}

void Circle::draw(SDL_Renderer * renderer, vec2d& position) { 
    int32_t radius_int = int(radius);
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


float Circle::calculateArea() const {return radius * radius * M_PI;}

float Circle::calculateInertia(float& mass) const {
    return mass * radius * radius /2;
}

void Circle::createAABB() {}

//Polygon
Poly::Poly(const std::vector<vec2d>& verticies) {
    vertex_count = verticies.size();
    assert(vertex_count > 2 && vertex_count <= max_poly_count && "Vertex list size out of bounds");

    std::vector<vec2d> hull;

    //Establish min x point
    unsigned int first_point = 0;
    float minimum_x = FLT_MAX;
    for (unsigned int i = 0; i < vertex_count; i++) {
        float x_val = verticies[i].x;
        if (x_val < minimum_x) {
            first_point = i;
            minimum_x = x_val;
        }
    }

}

Poly::Poly(float width, float height) : vertex_count(4) {
    vertex_list.emplace_back(-width/2, -height/2);
    vertex_list.emplace_back(width/2, -height/2);
    vertex_list.emplace_back(width/2, height/2);
    vertex_list.emplace_back(-width/2, -height/2);
    normals.emplace_back(0, -1); // v
    normals.emplace_back(1, 0);  // ->
    normals.emplace_back(0, 1);  // ^
    normals.emplace_back(-1, 0); // <-
}

Shape::ShapeType Poly::getType() const {return ShapeType::Poly;}

std::string Poly::getName() const {return "Poylgon";}

void Poly::draw(SDL_Renderer * renderer, vec2d& position) { }

float Poly::calculateArea() const {return 0;}

float Poly::calculateInertia(float& mass) const {return 0;}

void Poly::createAABB() {}