#ifndef POLYGON
#define POLYGON

#include "../common/common.h"
#include "../common/mathfuncs.h"
#include "shape.h"
#include <vector>

struct Poly : public Shape {
    explicit Poly(std::vector<vec2d> &verticies);// Normal Poly
    Poly(float width, float height);             // Rectangle Poly
    // Poly(float radius, int side_number); //Regular Polygon (think stop sign)

    [[nodiscard]] ShapeType getType() const override;

    [[nodiscard]] std::string getName() const override;

    void calculateMassProperties(float density) override;

    void createAABB() override;

    // Getters/Setters
    [[nodiscard]] const unsigned int &getVertexCount() const { return vertex_count; }

    [[nodiscard]] const std::vector<vec2d> &getVertexList() const { return vertex_list; }

    [[nodiscard]] const std::vector<vec2d> &getNormals() const { return normals; }

    const float poly_radius = polygonRadius;

private:
    unsigned int vertex_count = 0;
    std::vector<vec2d> vertex_list;
    std::vector<vec2d> normals;
    vec2d centroid;

    void calculatePolyNormals();
};

#endif
