#include "shape.h"
#include <cassert>
#include <cmath>
#include <algorithm>
#include "physicsworld.h"
#include <iostream>

//Shape



void Shape::setBody(const std::shared_ptr<RigidBody>& body_) {
    body = body_;
}

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


void Circle::calculateMassProperties(float& density) {
        std::shared_ptr<RigidBody> body_ref = body.lock();
        body_ref->area = radius * radius * M_PI;
        body_ref->m = body_ref->area *density;
        body_ref->I = body_ref->m * radius * radius /2;
        body_ref->inv_m = (body_ref->m) ? 1.0f / body_ref -> I : 0;
        body_ref->inv_I = (body_ref->I) ? 1.0f / body_ref -> I : 0;

    }

//Inertia return mass * radius * radius /2;

void Circle::createAABB() {}

//Polygon

//Polygon Sorter
struct GrahamCCWSorter {
    const vec2d& pivot;

    GrahamCCWSorter(const vec2d& pivot_): pivot(pivot_) {}

    bool operator()(const vec2d& a, const vec2d& b) {
        return findOrientation(a, b, pivot) < 0;
    }
};


Poly::Poly(std::vector<vec2d>& v) {
    //Hull Creation
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
    vertex_count++;
    while (it != v.end()) {
        while (findOrientation(*(hull.rbegin() + 1), *(hull.rbegin()), *it) >= 0) {
            hull.pop_back();
        }
        hull.push_back(*it++);
        vertex_count++;
    }

    assert(vertex_count > 2 && vertex_count <= max_poly_count && "Vertex list size out of bounds");

    for (unsigned int i = 0; i < vertex_count; i++)
    {
        vertex_list.push_back(hull[i]);
    }

    calculatePolyNormals();

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

void Poly::draw(SDL_Renderer * renderer, vec2d& position) {
    for (unsigned int i = 0; i < vertex_count; i ++) {
        int x1 = vertex_list[i].x;
        int y1 = vertex_list[i].y;
        int x2= vertex_list[(i+1) % vertex_count].x;
        int y2 = vertex_list[(i+1) % vertex_count].y;
        SDL_RenderDrawLine(renderer, x1, y1, x2, y2);
    }
}

void Poly::calculateMassProperties(float& density) {


};

void Poly::createAABB() {}

void Poly::calculatePolyNormals() {
    normals.clear();
    assert (vertex_count > 2 && vertex_count < max_poly_count && "Vertex count out of bounds");
    for (unsigned int i =0; i < vertex_count; i ++) {
        vec2d face = vertex_list[(i+1) % vertex_count] - vertex_list[i];
        normals.push_back(vec2d(face.y, -face.x).normalize());
    }

}



