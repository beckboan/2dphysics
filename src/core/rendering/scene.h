//
// Created by beckm on 1/29/2024.
//

#ifndef IMGUI_SCENE_H
#define IMGUI_SCENE_H

#include "rigidbody.h"
#include <memory>
#include <vector>

class Scene {
public:

    void drawBody(const std::shared_ptr<RigidBody> &body) const;

    [[nodiscard]] int renderYTransfer(int y) const;

    [[nodiscard]] int renderXTransfer(int x) const;

    [[nodiscard]] int renderYTransfer(float y) const;

    [[nodiscard]] int renderXTransfer(float x) const;

    void drawBodies(const std::vector<std::shared_ptr<RigidBody>> &bodies) const;

    void setHalfWidths(float hw_x, float hw_y);

    float scene_hw_x;
    float scene_hw_y;
    vec2d m_zoom{1.0, 1.0};

};


#endif //IMGUI_SCENE_H
