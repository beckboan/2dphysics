#include "polygon.h"
#include <cassert>
#include <algorithm>

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