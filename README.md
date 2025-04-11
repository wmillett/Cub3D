Cub3D
Cub3D is a 3D raycasting engine that renders a basic 3D environment from a 2D map, inspired by early 3D games. This project was created as part of the 42 School curriculum and aims to demonstrate understanding of 3D rendering, raycasting, and basic game engine mechanics.

Table of Contents
Introduction

Features

Requirements

Installation

Usage

Controls

How It Works

Contributing

License

Introduction
Cub3D is a 3D raycasting engine that simulates a first-person view of a 3D world based on a 2D grid map. The project utilizes raycasting, a technique commonly used in early 3D games like Wolfenstein 3D. It is an excellent exercise in learning how graphics, rendering, and input handling work under the hood of a game engine.

Features
Raycasting Engine: Render 3D world from a 2D map using raycasting.

Simple Graphics: Walls and floor are drawn using basic textures.

First-Person View: Navigate the world in first-person with keyboard and mouse controls.

Minimap: A mini overview of the world as a 2D map.

FPS Display: Display the frame rate for optimization and performance analysis.

Requirements
Before you can run the project, make sure you have the following installed:

OS: Linux, macOS, or Windows (via WSL)

Compiler: GCC or Clang

Libraries:

MinilibX (for graphics rendering)

X11 (Linux only)

Make

You can check your installation using the following commands:

bash
Copy
Edit
gcc --version
make --version
Installation
To set up the project on your local machine, follow these steps:

Clone the Repository:

bash
Copy
Edit
git clone https://github.com/yourusername/cub3d.git
cd cub3d
Install Dependencies:

On Linux (Debian-based systems):

bash
Copy
Edit
sudo apt-get update
sudo apt-get install libx11-dev libbsd-dev
For macOS, you’ll need to install X11 and MinilibX.

Compile the Project: Run make in the project folder:

bash
Copy
Edit
make
Run the Program: After compiling, you can run the program using:

bash
Copy
Edit
./cub3d map/cub3d_map.cub
Usage
After following the installation steps, you can use Cub3D in the following ways:

Launch the Game: Run the program with a map file as an argument:

bash
Copy
Edit
./cub3d <path_to_map_file>
Example:

bash
Copy
Edit
./cub3d maps/level1.cub
Edit the Map:
The map files are simple .cub files that you can edit with any text editor. A basic map layout consists of walls (represented by 1), open spaces (0), and player starting position (P).

Controls
Navigate through the 3D world using the following controls:

W: Move forward

S: Move backward

A: Strafe left

D: Strafe right

Arrow keys or Mouse: Look around

Esc: Exit the game

How It Works
Cub3D uses the raycasting algorithm to simulate the rendering of a 3D world on a 2D plane. Here's a quick overview of the process:

Raycasting:
The engine casts rays from the player's position, checking for intersections with walls. The distance to the wall is calculated, and based on the distance, the engine draws the appropriate vertical line in the 3D view.

Texture Mapping:
Walls are textured based on the ray’s intersection point. The engine calculates which part of the texture should be drawn to simulate depth.

Rendering:
The engine then renders the view by drawing the floor and ceiling in a fixed color, and using the raycasted wall distances to create the illusion of depth.

Contributing
If you'd like to contribute to this project, feel free to fork the repository and submit pull requests. Here’s how you can contribute:

Fork the repository to your GitHub account.

Clone your fork to your local machine:

bash
Copy
Edit
git clone https://github.com/yourusername/cub3d.git
Make your changes to the code.

Submit a pull request with a description of your changes.

License
This project is licensed under the MIT License - see the LICENSE file for details.
