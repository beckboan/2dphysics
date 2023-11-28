# 2D Physics Engine Project

A simple rigid-body physics simulator written in C++.

## Introduction

This Physics Engine is a C++ project designed to simulate physical interactions in a 2D environment. It serves as a simple foundation/blueprint that other developers can use to run simulations or build their own physics engine. This project may serve as a helpful project for someone learning C++, as I used it to learn C++ features such as smart pointers, function overrides, virtual inheritance, and polymorphism.

## Credit

Majority of credit for this project can go to Randy Gaul's Impulse Engine (https://github.com/RandyGaul/ImpulseEngine) and Erin Catto's Box2d (https://github.com/erincatto/box2d). Many times I found myself using their projects as templates/tutorials on engine setup/ primitive shape creation/ collision detection and resolution.

## Features

- **Rigid Body Dynamics**
- **Collision Detection**
- **Broad Phase and Narrow Phase**

## Getting Started

### Prerequisites 
- C++ compiler (C++11 or higher)
- CMake (for building the project)
- SDL2
- OpenGL

### Building

1. Clone the repository: 
```
https://github.com/beckboan/2dphysics.git
```

2.  Navigate to the project directory
```
cd 2dphysics
```

3. Build with cmake
```
cmake --build build 
```

4. Run the output file
```
build/2dphysics
```





