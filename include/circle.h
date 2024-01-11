#ifndef CIRCLE_H
#define CIRCLE_H

#include "shape.h"

struct Circle : public Shape {
    explicit Circle(float radius);

    const float radius;

    [[nodiscard]] ShapeType getType() const override;
    [[nodiscard]] std::string getName() const override;
    void calculateMassProperties(float density) override;
    void createAABB() override;
};

#endif
