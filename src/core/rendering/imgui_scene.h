//
// Created by beckm on 1/29/2024.
//

#ifndef IMGUI_SCENE_H
#define IMGUI_SCENE_H

#include "rigidbody.h"
#include <memory>
#include <vector>

class ImGuiScene {
public:

    void drawImGuiBody(const std::shared_ptr<RigidBody> &body) const;

    [[nodiscard]] int renderYTransfer(int y) const;

    [[nodiscard]] int renderXTransfer(int x) const;

    [[nodiscard]] int renderYTransfer(float y) const;

    [[nodiscard]] int renderXTransfer(float x) const;

    void drawImGuiObjects(const std::vector<std::shared_ptr<RigidBody>> &bodies) const;

    void setHalfWidths(float hw_x, float hw_y);

    float m_hw_x;
    float m_hw_y;
    vec2d m_zoom{1.0, 1.0};

};


#endif //INC_2DPHYSICS_IMGUI_SCENE_H
