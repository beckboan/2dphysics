# 2D Physics Engine Project

A simple rigid-body physics simulator written in C++.

## Introduction

This Physics Engine is a C++ project designed to simulate physical interactions in a 2D environment. It serves as a
simple foundation/blueprint that other developers can use to run simulations or build their own physics engine. This
project may serve as a helpful project to learn features such as smart pointers, function overrides, virtual
inheritance, and polymorphism.

## Demo


https://github.com/user-attachments/assets/52c71139-ec8a-4390-b553-f66d25263544



## Credit

Serious help/inspiration for this project can go to Randy Gaul's Impulse Engine that can be found [here](https://github.com/RandyGaul/ImpulseEngine) and
Erin Catto's Box2d [here](https://github.com/erincatto/box2d). Many times I found myself using their projects as
templates/tutorials on engine setup/ primitive shape creation/ collision detection and resolution.

## Features

- **Rigid Body Dynamics**
- **Collision Detection**
- **Collision Resolution**
- **Level Loading**
- **Shape Rendering**

## To Do

- **Add Logging in UI**
- **Add AABB Visualization**
- **Add Menu for Placing Shapes**
- **Add Edge Drawing on Main Screen**
- **Add Shape Drawing on Main Screen**
- **Move Shapes on Screen**

## Getting Started

### Prerequisites

- C++ compiler (C++11 or higher)
- CMake (for building the project)
- SDL and OpenGL will be installed by CMake

### Building

1. Clone the repository:

```
https://github.com/beckboan/2dphysics.git
```

2. Navigate to the project directory

```
cd 2dphysics
```

3. Build with cmake

```
cmake --build build 
```

4. Run the output file

```
./build/src/app/app
```

## Level Loading
Levels are loaded in from the **scenes/** directory. The level file is a simple .yaml file that contains two three main sections:
- **Scene**: Contains the scene name
- **Bodies**: Contains the bodies that will be loaded into the scene
- **Boundaries**: Contains the boundaries of the scene

### Example Level File
```yaml
scene_info:
  name: "Test Scene"

bodies:
  - name: "Polygon Shape"
    shape: "polygon"
    color: [0, 0, 255]
    points: [[0, 0], [0, 10], [10, 10], [0, 10], [15,20], [-10,15]]
    position: [0, 50]
    rotation: 15
    density: 500
    static: false  
  - name: "Circle Shape"
    shape: "circle"
    radius: 20
    position: [0, 50]
    rotation: [0, 0]
    density: 500
    static: false



boundaries:
  - name: "Boundary1"
    start: [-200, -50]
    end: [500, -50]
  - name: "Boundary1"
    start: [-200, -50]
    end: [-200, 500]
  - name: "Boundary1"
    start: [500, -50]
    end: [500, 500]
```
There are two types of shapes that can be loaded into the scene:
- **Polygon**: A polygon shape that is defined by a list of points. 
- **Circle**: A circle shape that is defined by a radius

**Note**: Only convex polygons are supported.

Other properties that can be set for the shapes are:
- **Color**: The color of the shape
- **Position**: The position of the shape
- **Rotation**: The rotation of the shape
- **Density**: The density of the shape
- **Static**: Whether the shape reacts to forces or not

All boundaries are static and defined by a start and end point. Boundaries simply act as static bodies that shapes can collide with.

## Detection Algorithm
The collision detection algorithm used in this project is the Separating Axis Theorem (SAT). The SAT algorithm is a simple and efficient algorithm that can be used to detect collisions between convex shapes. The algorithm works by projecting the shapes onto a set of axes and checking for overlap. If there is no overlap on any axis, then the shapes are not colliding.

Here are good resources to learn more about the SAT algorithm:
- [2D Collision Detection: The Separating Axis Theorem](https://www.codeproject.com/Articles/15573/2D-Polygon-Collision-Detection)
- [How To Create a Custom 2D Physics Engine](https://code.tutsplus.com/how-to-create-a-custom-2d-physics-engine-the-basics-and-impulse-resolution--gamedev-6331t)
- [Collision Detection Using the Separating Axis Theorem](https://code.tutsplus.com/collision-detection-using-the-separating-axis-theorem--gamedev-169t)
- [Separating Axis Theorem](https://en.wikipedia.org/wiki/Hyperplane_sepaation_theorem)











