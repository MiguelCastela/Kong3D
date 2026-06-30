# Kong3D

A playable 3D reimagining of the original Donkey Kong (NES, 1981), built in C++
with the openFrameworks toolkit and fixed-function OpenGL. The game keeps the
classic climb-the-girders gameplay while adding switchable camera perspectives
(first person, 2D third person, and 3D third person) and a real-time lighting
sandbox.

## Overview

You play as Mario, climbing platforms and ladders to reach Pauline at the top
while avoiding the barrels that Donkey Kong rolls down. The project was developed
as a Computer Graphics assignment and demonstrates 3D modelling from primitives,
texturing, hierarchical animation, particle effects, collision detection, and
the three classic OpenGL light types (directional, point, and spot).

## Features

- Three camera modes that can be switched at any time: first person, 2D third
  person, and 3D third person.
- Four game modes: Easy, Medium, Hard (night), and Sandbox.
- A lighting Sandbox where ambient, directional, point, and spot lights can be
  toggled and tuned independently.
- Procedurally built characters (Mario, Donkey Kong, Pauline) and scene objects
  (platforms, ladders, barrels) assembled from OpenGL primitives.
- Textured platforms and ladders, plus a particle based explosion effect.
- Barrel spawning, collision detection, death and respawn, and a win condition.
- On-screen overlays for object stats, gameplay stats, and a controls help panel.

## Controls

| Action | Key |
| --- | --- |
| Cycle camera mode | T |
| Move (third person) | Left / Right / Up / Down arrows |
| Move (first person) | Left / Right arrows, W, S |
| Jump | Space |
| Easy mode | 1 |
| Medium mode | 2 |
| Hard / Night mode | 3 |
| Sandbox mode | 4 |
| Toggle object overlay | G |
| Toggle stats overlay | H |
| Toggle controls help panel | F |
| Quit | Esc |

Sandbox mode only (game mode 4):

| Action | Key |
| --- | --- |
| Ambient light on/off | Z |
| Directional light on/off | X (properties: I, O, P) |
| Point light, attached to Mario, on/off | C (properties: J, K, L) |
| Spot light, attached to Donkey Kong, on/off | V (properties: B, N, M) |

## Project structure

```
.
├── src/                  Application source
│   ├── main.cpp          Entry point, creates the window and runs the app
│   ├── app/              ofApp, the game manager, and shared global state
│   ├── camera/           Camera modes and view setup
│   ├── entities/         Game objects (Mario, Kong, Pauline, barrels,
│   │                     platforms, ladders, background, particles)
│   └── graphics/         Rendering helpers and material definitions
│                         (cg_extras, cg_cam_extras, cg_drawing_extras, materials)
├── bin/
│   └── data/             Runtime assets (textures and font) loaded by the game
├── docs/
│   └── tutorials/        Course materials and reference notes (PL9, PL10)
├── .gitattributes
├── .gitignore
└── README.md
```

## Requirements

- openFrameworks 0.11 or newer (https://openframeworks.cc/download/).
- A C++ compiler toolchain supported by openFrameworks (g++, Clang, or MSVC).
- A GPU and drivers supporting legacy fixed-function OpenGL.

The project uses only the openFrameworks core. No addons are required.

## Building and running

This repository contains source and assets only, not a generated
openFrameworks project. The recommended way to build is to drop these files into
a fresh openFrameworks project:

1. Install openFrameworks and confirm the bundled examples compile on your
   platform.
2. Create a new empty project with the openFrameworks project generator, for
   example under `openFrameworks/apps/myApps/Kong3D`.
3. Replace the generated `src/` folder with the `src/` folder from this
   repository.
4. Copy this repository's `bin/data/` into the project's `bin/data/`.
5. Build and run:
   - Linux and macOS (from the project folder): `make && make run`
   - Visual Studio: open the generated solution and build, or
   - Xcode: open the generated project and run.

The project generator adds every subfolder of `src/` to the include path, which
is why the source files use flat includes (for example `#include "mario.h"`)
even though they live in different folders. Keep all sources under `src/` so this
continues to work.

The application starts in fullscreen. To run in a window instead, edit
`src/main.cpp` and change the window mode from `OF_FULLSCREEN` to `OF_WINDOW`.

## Assets

All runtime assets live in `bin/data/` and are loaded by file name relative to
that folder:

- `platform_texture.png`, `ladder.png`, `ladder_side.png`, `ladder_fake.png`:
  textures for platforms and ladders.
- `font_stats.ttf`: font used for on-screen text and overlays.

## Documentation

`docs/tutorials/` holds the Computer Graphics course materials (lighting,
texturing, and final operations) that this project was based on, along with the
lighting calculator scripts (`calc_lights.py`, `calc_lights.m`).

## Authors

- Miguel Castela
