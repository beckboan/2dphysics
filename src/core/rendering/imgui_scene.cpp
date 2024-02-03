//
// Created by beckm on 1/29/2024.
//

#include "imgui_scene.h"
#include <SDL.h>
#include "imgui.h"
#include "shape.h"
#include <backends/imgui_impl_sdl2.h>
#include <backends/imgui_impl_sdlrenderer2.h>
#include "polygon.h"
#include "circle.h"
#include "edge.h"
#include "mathfuncs.h"

void ImGuiScene::drawImGuiBody(const std::shared_ptr<RigidBody> &body) {
    switch (body->shape->getType()) {
        case Shape::ShapeType::Circle: {
            auto *c = dynamic_cast<Circle *>(body->shape.get());
            auto radius_int = int(c->radius);

            // Convert the position to screen space
            ImVec2 pos = ImVec2(renderXTransfer(body->position.x), renderYTransfer(body->position.y));

            // Render a circle using ImGui
            ImGui::GetWindowDrawList()->AddCircle(pos, radius_int, IM_COL32(255, 0, 0, 255), 0, 1.0f);
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
                ImGui::GetWindowDrawList()->AddLine(p1, p2, IM_COL32(255, 0, 0, 255), 1.0f);
            }
            break;
        }
        case Shape::ShapeType::Edge: {
            Edge *e = dynamic_cast<Edge *>(body->shape.get());

            // Convert vertices to screen space
            ImVec2 start = ImVec2(renderXTransfer(e->start_vertex.x), renderYTransfer(e->start_vertex.y));
            ImVec2 end = ImVec2(renderXTransfer(e->end_vertex.x), renderYTransfer(e->end_vertex.y));

            // Render an edge using ImGui
            ImGui::GetWindowDrawList()->AddLine(start, end, IM_COL32(255, 0, 0, 255), 1.0f);
            break;
        }
        default:
            break;
    }
}


int ImGuiScene::renderYTransfer(int y) const { return m_hw_y + -1 * y; }

int ImGuiScene::renderXTransfer(int x) const { return m_hw_x + x; }

int ImGuiScene::renderYTransfer(float y) const { return m_hw_y + -1 * int(y); }

int ImGuiScene::renderXTransfer(float x) const { return m_hw_x + int(x); }

void ImGuiScene::drawImGuiObjects(const std::vector<std::shared_ptr<RigidBody>> &bodies) {
    for (const auto &body: bodies) {
        drawImGuiBody(body);
    }
}

void ImGuiScene::setHalfWidths(float hw_x, float hw_y) {
    m_hw_x = hw_x;
    m_hw_y = hw_y;
}

