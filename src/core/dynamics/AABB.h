#ifndef AABB_H
#define AABB_H

#include "mathfuncs.h"

struct AABB {
    AABB() = default;

    [[nodiscard]] vec2d getMin() const { return min; }

    [[nodiscard]] vec2d getMax() const { return max; }

    [[maybe_unused]] void setAABB(const vec2d &min_, const vec2d &max_);

    [[maybe_unused]] void setMin(const vec2d &min_);

    [[maybe_unused]] void setMax(const vec2d &max_);

    void setMin(float min_x, float min_y);

    void setMax(float max_x, float max_y);

    [[maybe_unused]] void move(const vec2d &vec);

private:
    vec2d min;// Bottom Left
    vec2d max;// Top Right
};

inline bool checkAABBOverlap(const AABB &box1, const AABB &box2) {
    return box1.getMin().x <= box2.getMax().x && box1.getMax().x >= box2.getMin().x &&
           box1.getMin().y <= box2.getMax().y && box1.getMax().y >= box2.getMin().y;
}

#endif
