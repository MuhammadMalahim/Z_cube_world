# Z Cube World

**Z Cube World** is a real-time 3D computer graphics application that visualizes and animates multiple Z-shaped cube formations using OpenGL and ImGui. The project features interactive controls, physics-based animation along a parabolic path, and dynamic creation/removal of object groups.

---

## Project Overview

At the core of this project is the construction and animation of a **Z-shaped structure**, composed of **five identical unit cubes**:

- Each cube has an edge length of 1 unit.
- The five cubes are connected in a Z-like formation.

Once the Z-shape is created:

- It is **replicated** and placed at the **vertices of a larger cube** (edge length: 5 units), centered at the origin.
- The entire formation moves along a **parabolic path** defined by the equation `y = 0.05 × x²` in the XY plane.
- The movement oscillates back and forth between `x = -10` and `x = 10`, completing one full traversal (forward and back) in **10 seconds**.

---

## Interactive Features

- **User Controls** (via ImGui):
  - Pressing the `+` button adds a new copy of the formation along the circumference of a circle with a radius of 15 units. Each new formation is evenly spaced along the circle.
  - Pressing the `-` button removes the most recently added formation.

---

## Rendering and Geometry

- **Back-face culling** is enabled to ensure correct visual appearance.
- **Each vertex** is assigned a distinct color.
- **All geometries are closed**, with no missing faces or holes.

---

## Technologies and Libraries

- **C++** – Core implementation language
- **OpenGL** – For 3D rendering
- **GLM** – Matrix and vector mathematics
- **GLEW** – OpenGL extension loader
- **SDL2** – Window and input management
- **ImGui** – Real-time graphical user interface
- **Visual Studio** – Development environment

---

## Key Features

- Real-time rendering of custom Z-shaped cube structures
- Smooth animation along a parabolic curve
- Dynamic addition and removal of object groups
- Interactive controls with an intuitive GUI
- Correct visual output using face culling
- Per-vertex coloring for visual clarity
- Adaptive camera system for optimal viewing

