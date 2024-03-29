//
// Created by beckm on 1/29/2024.
//

#include "scene.h"
#include "circle.h"
#include "edge.h"
#include "imgui.h"
#include "mathfuncs.h"
#include "polygon.h"
#include "shape.h"
#include <SDL.h>
#include <backends/imgui_impl_sdl2.h>
#include <backends/imgui_impl_sdlrenderer2.h>
#include <iostream>

void Scene::drawBody(const std::shared_ptr<RigidBody> &body) const {
    auto colors = body->getRGB();
    auto body_color = IM_COL32(colors[0], colors[1], colors[2], 255);
    switch (body->shape->getType()) {
        case Shape::ShapeType::Circle: {
            auto *c = dynamic_cast<Circle *>(body->shape.get());
            auto radius_int = c->radius;

            // Convert the position to screen space
            ImVec2 pos = ImVec2(renderXTransfer(body->position.x), renderYTransfer(body->position.y));

            // Render a circle using ImGui
            ImGui::GetWindowDrawList()->AddCircle(pos, radius_int, body_color, 0, 1.0f);
            break;
        }
        case Shape::ShapeType::Poly: {
            Poly *p = dynamic_cast<Poly *>(body->shape.get());
            std::vector<vec2d> v_list_temp = p->getVertexList();
            vec2d position = body->position;

            unsigned int v_c = v_list_temp.size();

            // Convert vertices to screen space
            for (unsigned int i = 0; i < v_c; i++) {
                v_list_temp[i] = p->rotation->mul(v_list_temp[i]) + position;
            }

            // Render a polygon using ImGui
            for (unsigned int i = 0; i < v_c; i++) {
                ImVec2 p1 = ImVec2(renderXTransfer(v_list_temp[i].x), renderYTransfer(v_list_temp[i].y));
                ImVec2 p2 = ImVec2(renderXTransfer(v_list_temp[(i + 1) % v_c].x),
                                   renderYTransfer(v_list_temp[(i + 1) % v_c].y));
                ImGui::GetWindowDrawList()->AddLine(p1, p2, body_color, 1.0f);
            }
            break;
        }
        case Shape::ShapeType::Edge: {
            Edge *e = dynamic_cast<Edge *>(body->shape.get());

            // Convert vertices to screen space
            ImVec2 start = ImVec2(renderXTransfer(e->start_vertex.x), renderYTransfer(e->start_vertex.y));
            ImVec2 end = ImVec2(renderXTransfer(e->end_vertex.x), renderYTransfer(e->end_vertex.y));

            // Render an edge using ImGui
            ImGui::GetWindowDrawList()->AddLine(start, end, body_color, 1.0f);
            break;
        }
        default:
            break;
    }
}


int Scene::renderYTransfer(int y) const { return int(scene_hw_y) + -1 * y; }

int Scene::renderXTransfer(int x) const { return int(scene_hw_x) + x; }

int Scene::renderYTransfer(float y) const { return int(scene_hw_y) + -1 * int(y); }

int Scene::renderXTransfer(float x) const { return int(scene_hw_x) + int(x); }

void Scene::drawBodies(const std::vector<std::shared_ptr<RigidBody>> &bodies) const {
    for (const auto &body: bodies) {
        drawBody(body);
    }
}

void Scene::setHalfWidths(float hw_x, float hw_y) {
    scene_hw_x = hw_x;
    scene_hw_y = hw_y;
}
