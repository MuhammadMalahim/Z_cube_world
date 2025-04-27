# Z Cube World

This project is a real-time 3D computer graphics program that visualizes and animates multiple Z-shaped cube formations using OpenGL and ImGui. It features interactive controls, physics-based animation along a parabolic path, and dynamic creation/removal of object groups.

## Project Overview

The core of this project is the construction and animation of a **Z-shaped structure**, composed of **five identical unit cubes**:

- Each cube has an **edge length of 1 unit**.
- Five cubes are connected to form a **Z-shape**.

Once the Z-shape is created:

- It is **replicated** and placed at the **vertices of a larger cube** (edge length **5 units**), centered at the **origin**.
- The entire formation **moves along a parabolic path** defined by **y = 0.05 × x²** in the XY plane, back and forth between **x = -10** and **x = 10**.
- One full back-and-forth traversal along the parabola is completed in **10 seconds**.

Additional features include:

- **User Interaction**: Using **ImGui** buttons:
  - Pressing the **"+"** button adds a new copy of the formation along the circumference of a **circle with a radius of 15 units**.
  - Formations are **evenly spaced** along the circumference.
  - Pressing the **"-"** button removes the latest added formation.
- **Camera Configuration**: Automatically adjusted to ensure **all formations are visible** at any time.

Rendering and geometry details:

- **Back-face culling** is enabled for proper visual appearance.
- **All vertices** have **distinct colors**.
- **Geometries are closed**; no missing faces.

## Technologies & Libraries Used

- **C++** - Core programming language.
- **OpenGL** - 3D rendering.
- **GLM** - Mathematics library for matrix and vector operations.
- **GLEW** - Extension wrangler for OpenGL.
- **SDL2** - Window management and event handling.
- **ImGui** - Immediate Mode GUI for real-time UI components.
- **Visual Studio** - Used for project structure and development.

## Features

- ✨ Real-time rendering of custom Z-shaped geometries.
- 🚀 Smooth animation along a defined parabolic curve.
- 🧹 Dynamic addition and removal of formations.
- 🖛 User control with intuitive ImGui interface.
- 🛡️ Correct visual output using back-face culling.
- 🎨 Unique per-vertex coloring.
- 📷 Dynamic camera to handle scene scaling.

---

Thank you for exploring Z Cube World! 🚀 Feel free to clone, build, and experiment with the project!

Remark: Description is written with chatGPT

