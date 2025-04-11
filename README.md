# **Cub3D**

Cub3D is a 3D raycasting engine that renders a basic 3D environment from a 2D map, inspired by early 3D games. This project was created as part of the [42 School](https://www.42.fr/en/) curriculum and aims to demonstrate understanding of 3D rendering, raycasting, and basic game engine mechanics.

---

## **Table of Contents**

- [Introduction](#introduction)
- [Features](#features)
- [Requirements](#requirements)
- [Installation](#installation)
- [Usage](#usage)
- [Controls](#controls)
- [How It Works](#how-it-works)
- [Contributing](#contributing)
- [License](#license)

---

## **Introduction**

Cub3D is a 3D raycasting engine that simulates a first-person view of a 3D world based on a 2D grid map. The project utilizes raycasting, a technique commonly used in early 3D games like *Wolfenstein 3D*. It is an excellent exercise in learning how graphics, rendering, and input handling work under the hood of a game engine.

---

## **Features**

- **Raycasting Engine:** Render 3D world from a 2D map using raycasting.
- **Simple Graphics:** Walls and floor are drawn using basic textures.
- **First-Person View:** Navigate the world in first-person with keyboard and mouse controls.
- **Minimap:** A mini overview of the world as a 2D map.
- **FPS Display:** Display the frame rate for optimization and performance analysis.

---

## **Requirements**

Before you can run the project, make sure you have the following installed:

- **OS:** Linux, macOS, or Windows (via WSL)
- **Compiler:** GCC or Clang
- **Libraries:**
  - [MinilibX](https://github.com/42Paris/minilibx) (for graphics rendering)
  - [X11](https://www.x.org/wiki/) (Linux only)
  - [Make](https://www.gnu.org/software/make/)
  
You can check your installation using the following commands:
```bash
gcc --version
make --version
