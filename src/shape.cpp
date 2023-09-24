#include "shape.h"
#include <cassert>

struct GrahamCCWSorter {
    const vec2d& pivot;

    GrahamCCWSorter(const vec2d& pivot_): pivot(pivot_) {}

    bool operator()(const vec2d& a, const vec2d& b) {
        return findOrientation(a, b, pivot) < 0;
    }
};

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
Poly::Poly(std::vector<vec2d>& v) {
    
    std::vector<vec2d> hull;

    //Establish min_x and move to front of verticies
    vec2d min_x = *std::min_element(v.begin(), v.end(), isLeftOf);

    std::swap(v[0], min_x);

    //Sort point ccw around min_x
    std::sort(v.begin() + 1, v.end(), GrahamCCWSorter(v[0]));

    auto it = v.begin();

    hull.push_back(*it++);
    hull.push_back(*it++);
    hull.push_back(*it++);

    while (it != v.end()) {
        while (findOrientation(*(hull.rbegin() + 1), *(hull.rbegin()), *it) >= 0) {
            hull.pop_back();
        }
        hull.push_back(*it++);
        vertex_count ++;
        
    }

    assert(vertex_count > 2 && vertex_count <= max_poly_count && "Vertex list size out of bounds");

    for (auto i: hull)
    {
        vertex_list.push_back(i);
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



