#include "scene.h"
#define GL_GLEXT_PROTOTYPES
#include "rigidbody.h"
#include "shape.h"
#include "circle.h"
#include "polygon.h"

Scene::Scene() {
    SDL_Init(SDL_INIT_EVERYTHING);

    window = SDL_CreateWindow("OpenGL Test",
    SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1200, 800, SDL_WINDOW_OPENGL);
    
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);   
    SDL_RenderPresent(renderer);
}

void Scene::drawBody(const std::shared_ptr<RigidBody> body) {
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

        while (x >= y) {
            SDL_RenderDrawPoint(renderer, body->position.x + x, body->position.y - y);
            SDL_RenderDrawPoint(renderer, body->position.x + x, body->position.y + y);
            SDL_RenderDrawPoint(renderer, body->position.x - x, body->position.y - y);
            SDL_RenderDrawPoint(renderer, body->position.x - x, body->position.y + y);
            SDL_RenderDrawPoint(renderer, body->position.x + y, body->position.y - x);
            SDL_RenderDrawPoint(renderer, body->position.x + y, body->position.y + x);
            SDL_RenderDrawPoint(renderer, body->position.x - y, body->position.y - x);
            SDL_RenderDrawPoint(renderer, body->position.x - y, body->position.y + x);

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
        for (unsigned int i = 0; i < p->vertex_count; i ++) {
            int x1 = body->position.x + p->vertex_list[i].x;
            int y1 = body->position.y + p->vertex_list[i].y;
            int x2= body->position.x + p->vertex_list[(i+1) % p->vertex_count].x;
            int y2 = body->position.y + p->vertex_list[(i+1) % p->vertex_count].y;
            SDL_RenderDrawLine(renderer, x1, y1, x2, y2);
        }
        SDL_RenderPresent(renderer);
        break;
    }
    default:
        break;
    }
}



// inline void windowTranslate(SDL_Renderer * renderer) {
//     vec2d winSize;
//     SDL_GetRendererOutputSize(renderer, &int(winSize.x), &int(winSize.y));
// };