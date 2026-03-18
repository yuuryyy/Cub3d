# 🐺 cub3D

*My first RayCaster with miniLibX.* **cub3D** is a graphics project at 1337 (42 Network) inspired by the world-famous 90s game, Wolfenstein 3D. The objective is to create a dynamic view inside a maze, exploring the fascinating mathematical technique of **Raycasting**.

---

## 📖 About The Project

Before the era of true 3D hardware acceleration, games relied on clever math to simulate three-dimensional environments on 2D screens. `cub3D` challenges you to build a similar graphics engine from scratch in C, using only the barebones **MiniLibX** library.

This project is a rigorous test of algorithm optimization, vector mathematics (trigonometry), and deep structural organization, requiring you to render a realistic perspective, apply wall textures, and handle fluid user movements without frame drops.

### 🎯 Core Objectives
* Implement a robust **Raycasting engine** (typically using the DDA - Digital Differential Analysis algorithm).
* Master window and event management (keyboard inputs, window destruction).
* Perform complex string manipulation and rigorous validation of configuration files (`.cub` maps).
* Handle pixel-perfect texture mapping and color rendering.

---

## ✨ Features & Gameplay

### The Graphics Engine
* **True Raycasting:** Calculates the distance to walls for every vertical stripe of the screen to render depth.
* **Directional Texturing:** Distinct textures are applied to walls depending on which compass direction they face (North, South, East, West).
* **Floor & Ceiling Rendering:** Customizable RGB colors for the floor and ceiling.
* **Smooth Rendering:** Optimized frame buffering to prevent screen tearing and ensure smooth movement.

### Controls
| Key | Action |
| :---: | :--- |
| `W` | Move Forward |
| `S` | Move Backward |
| `A` | Strafe Left |
| `D` | Strafe Right |
| `←` / `→` (Arrows) | Rotate Camera Left / Right |
| `ESC` | Close the game and exit cleanly |

---

## 🗺️ Map Configuration (`.cub` files)

The engine reads a specific `.cub` configuration file that defines the environment. The parser strictly validates this file before rendering.

**Configuration Requirements:**
1. **Textures:** Paths to the `xpm` texture files for the North, South, West, and East walls.
2. **Colors:** RGB values `(0-255)` for the Floor (`F`) and Ceiling (`C`).
3. **The Map:** * `0`: Empty space
   * `1`: Wall
   * `N`, `S`, `E`, or `W`: The player's spawn position and initial facing direction.
   * *The map must be completely enclosed by walls.*

**Example (`map.cub`):**
```text
NO ./textures/north_wall.xpm
SO ./textures/south_wall.xpm
WE ./textures/west_wall.xpm
EA ./textures/east_wall.xpm

F 220,100,0
C 225,30,0

111111
100001
101001
100N01
111111
```

---

## 🛠️ Getting Started

### Prerequisites
* A standard C compiler (`cc`, `gcc`, or `clang`)
* `make` utility
* **MiniLibX** dependencies (Linux: `X11`, `Xext`, `lm` / macOS: OpenGL and AppKit)

### Installation & Compilation

1. Clone the repository:
   ```bash
   git clone [https://github.com/yuuryyy/Cub3d.git](https://github.com/yuuryyy/Cub3d.git)
   cd Cub3d
   ```

2. Compile the engine:
   ```bash
   make
   ```
   This compiles the source code, links the MiniLibX library, and generates the `cub3D` executable.

### Makefile Rules
* `make` / `make all`: Compiles the game.
* `make clean`: Removes the compiled `.o` object files.
* `make fclean`: Removes the object files and the `cub3D` executable.
* `make re`: Runs `fclean` followed by `all`.

---

## 💻 Usage

To launch the game, run the executable followed by the path to a valid `.cub` scene description file.

```bash
./cub3D maps/default.cub
```

*(Note: If the map is invalid, unclosed, or missing textures, the program will gracefully exit with an explicit `Error` message).*

---
*Developed by Youssra Chagri at 1337 (UM6P).*
