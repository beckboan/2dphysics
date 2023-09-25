#include "circle.h"
#include "iostream"

//Circle
Circle::Circle(float radius): radius(radius) {
        std::cout << "Circle" << std::endl;
    }

Shape::ShapeType Circle::getType() const {return ShapeType::Circle;}

std::string Circle::getName() const {return "Circle";}

void Circle::draw(SDL_Renderer * renderer, vec2d& position) { 
    int32_t radius_int = int(radius);
    const int32_t diameter = radius*2;
    int32_t x = (radius - 1);
    int32_t y = 0;
    int32_t dx = 1;
    int32_t dy = 1;
    int32_t err = dx - diameter;

    while (x >= y) {
        SDL_RenderDrawPoint(renderer, position.x + x, position.y - y);
        SDL_RenderDrawPoint(renderer, position.x + x, position.y + y);
        SDL_RenderDrawPoint(renderer, position.x - x, position.y - y);
        SDL_RenderDrawPoint(renderer, position.x - x, position.y + y);
        SDL_RenderDrawPoint(renderer, position.x + y, position.y - x);
        SDL_RenderDrawPoint(renderer, position.x + y, position.y + x);
        SDL_RenderDrawPoint(renderer, position.x - y, position.y - x);
        SDL_RenderDrawPoint(renderer, position.x - y, position.y + x);

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
}


void Circle::calculateMassProperties(float& density) {
        std::shared_ptr<RigidBody> body_ref = body.lock();
        body_ref->area = radius * radius * M_PI;
        body_ref->m = body_ref->area *density;
        body_ref->I = body_ref->m * radius * radius /2;
        body_ref->inv_m = (body_ref->m) ? 1.0f / body_ref -> I : 0;
        body_ref->inv_I = (body_ref->I) ? 1.0f / body_ref -> I : 0;

    }

//Inertia return mass * radius * radius /2;

void Circle::createAABB() {}
