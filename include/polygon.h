#ifndef POLYGON
#define POLYGON

#include "shape.h"
#include <iostream>
#include <vector>
#include "mathfuncs.h"


struct Poly: public Shape {
    Poly(std::vector<vec2d>& verticies); //Normal Poly
    Poly(float width, float height); //Rectangle Poly

    unsigned int vertex_count = 0;
    std::vector<vec2d> vertex_list;
    std::vector<vec2d> normals;
    vec2d centroid;

    ShapeType getType() const;
    std::string getName() const;
    void draw(SDL_Renderer * renderer, vec2d& position);
    void calculateMassProperties(float& density);
    void createAABB();   
    void setSpaceOrientation(float radians);
    void calculatePolyNormals();
};

#endif