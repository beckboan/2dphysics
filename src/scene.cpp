#include "scene.h"
#define GL_GLEXT_PROTOTYPES
#include "rigidbody.h"
#include "shape.h"
#include "circle.h"
#include "polygon.h"
#include "mathfuncs.h"
#include <vector>

Scene::Scene(int screen_x_, int screen_y_) : screen_x(screen_x_), screen_y(screen_y_), hw_x(screen_x_/2), hw_y(screen_y_/2) {}

void Scene::init()
{
    SDL_Init(SDL_INIT_EVERYTHING);

    window = SDL_CreateWindow("OpenGL Test",
    SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, screen_x, screen_y, SDL_WINDOW_OPENGL);
    
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);   
    SDL_RenderPresent(renderer);
}

void Scene::drawBody(const std::shared_ptr<RigidBody> body) 
{
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    switch (body->shape->getType())
    {
    case Shape::ShapeType::Circle: 
    {
        Circle* c = dynamic_cast<Circle*>(body->shape.get());
        int32_t radius_int = int(c->radius);
        const int32_t diameter = radius_int*2;
        int32_t x = (radius_int - 1);
        int32_t y = 0;
        int32_t dx = 1;
        int32_t dy = 1;
        int32_t err = dx - diameter;
        int32_t bod_x_hw = renderXTransfer(body->position.x);
        int32_t bod_y_hw = renderYTransfer(body->position.y);

        while (x >= y) 
        {
            SDL_RenderDrawPoint(renderer, bod_x_hw + x, bod_y_hw - y);
            SDL_RenderDrawPoint(renderer, bod_x_hw + x, bod_y_hw + y);
            SDL_RenderDrawPoint(renderer, bod_x_hw - x, bod_y_hw - y);
            SDL_RenderDrawPoint(renderer, bod_x_hw - x, bod_y_hw + y);
            SDL_RenderDrawPoint(renderer, bod_x_hw + y, bod_y_hw - x);
            SDL_RenderDrawPoint(renderer, bod_x_hw + y, bod_y_hw + x);
            SDL_RenderDrawPoint(renderer, bod_x_hw - y, bod_y_hw - x);
            SDL_RenderDrawPoint(renderer, bod_x_hw - y, bod_y_hw + x);

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
        SDL_RenderPresent(renderer);
        break; 
    }
    case Shape::ShapeType::Poly:
    {
        Poly* p = dynamic_cast<Poly*>(body->shape.get());
        std::vector<vec2d> v_list_temp = p->getVertexList();
        int32_t body_pos_x = body->position.x;
        int32_t body_pos_y = body->position.y;
        vec2d position = body->position;

        unsigned int v_c = p->getVertexCount();

        for (unsigned int i = 0; i < v_c; i ++)
        {
            v_list_temp[i] = p->rotation->mul(v_list_temp[i]) + position;
        }

        for (unsigned int i = 0; i < v_c; i ++) 
        {
            int x1 = renderXTransfer(v_list_temp[i].x);
            int y1 = renderYTransfer(v_list_temp[i].y);
            int x2= renderXTransfer(v_list_temp[(i+1) % v_c].x);
            int y2 = renderYTransfer(v_list_temp[(i+1) % v_c].y);
            SDL_RenderDrawLine(renderer, x1, y1, x2, y2);
        }
        SDL_RenderPresent(renderer);
        break;
    }
    default:
        break;
    }
}


void Scene::drawAABB(const std::shared_ptr<RigidBody> body) 
{
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    auto [min_x, min_y, max_x, max_y] = body->shape->getAABB();
    // std::cout << min_x << min_y << max_x << max_y <<std::endl;
    float adjust_min_y = renderYTransfer(min_y);
    float adjust_max_y = renderYTransfer(max_y);
    float adjust_max_x = renderXTransfer(max_x);
    float adjust_min_x = renderXTransfer(min_x);
    SDL_RenderDrawLine(renderer, adjust_min_x, adjust_min_y, adjust_max_x, adjust_min_y);
    SDL_RenderDrawLine(renderer, adjust_max_x, adjust_min_y, adjust_max_x, adjust_max_y);
    SDL_RenderDrawLine(renderer, adjust_max_x, adjust_max_y, adjust_min_x, adjust_max_y);
    SDL_RenderDrawLine(renderer, adjust_min_x, adjust_max_y, adjust_min_x, adjust_min_y);
    SDL_RenderPresent(renderer);
}


int Scene::renderYTransfer(int y) {return hw_y + -1*y;}
int Scene::renderXTransfer(int x) {return hw_x + x;}