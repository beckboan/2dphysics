#ifndef RIGIDBODY_H
#define RIGIDBODY_H

#include "mathfuncs.h"
#include <memory>

struct Shape;

struct RigidBody {
    RigidBody(std::unique_ptr<Shape> &shape_, vec2d &position_, float density_);

    RigidBody(const RigidBody &) = delete;

    RigidBody &operator=(const RigidBody &) = delete;

    ~RigidBody() = default;

    vec2d position;
    vec2d velocity{0.0, 0.0};
    vec2d force{0.0, 0.0};

    float rotation = 0.0;
    float angular_velocity = 0.0f;
    float torque = 0.0;

    // Shape Features
    float I{};
    float inv_I = 0.0;
    float m = 0.0;
    float inv_m{};
    float area{};
    float density;

    // Friction and Rest
    float static_friction;
    float dynamic_friction;
    float restitution;
    [[maybe_unused]] bool hasProperties = false;
    [[maybe_unused]] bool isStatic = false;

    // Shape Reference
    std::unique_ptr<Shape> shape;

    // Body Color
    [[maybe_unused]] int r, g, b;

    // Property Functions
    void rigidIni();

    void setBodyStatic();

    void setRGB(int red, int green, int blue);

    // Getters
    [[nodiscard]] const vec2d &getPosition() const { return position; };

    std::array<int, 3> getRGB() const;

    // Physics Functions
    [[maybe_unused]] void move(const vec2d &amount);

    [[maybe_unused]] void moveto(const vec2d &position_new);

    void setRotation(float radians);

    [[maybe_unused]] void applyForce(vec2d &force, vec2d &point);

    [[maybe_unused]] void applyCenterForce(vec2d &force);

    void applyLinearImpulse(vec2d &impulse, vec2d &point);

    [[maybe_unused]] void applyCenterLinearImpulse(vec2d &impulse);
};

#endif
