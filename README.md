# Ecosystem simulation

This project aims to be a simulation of a basic ecosystem. This is inspired from Daniel Schiffman's simulation which can be found [here](http://natureofcode.com/book/chapter-9-the-evolution-of-code#913-ecosystem-simulation).

**Current version**: 1.0.0

## Building

This project uses a `CMakeLists.txt` file to build the project. The parameters for the cmake command are listed below.

### Parameters

| Option name      | Description                                                                                    |
| ---------------- | ---------------------------------------------------------------------------------------------- |
| OUTPUT_DIRECTORY | The output directory where the binary is gonna be located.                                     |
| SFML_ROOT        | The path to the SFML root location (in case Cmake can't find it properly with FindSFML.cmake). |

### Windows

#### Prerequisites for Windows

* Visual Studio 15 / 17
* CMake > 2.5

#### Instructions for Windows

Clone the repository, open a command prompt in it and type:

Example 1 (32 bits environnement):

```bash
mkdir build
cd build
cmake ..
cmake --build .
```

Example 2 (64 bits environnement):

```bash
mkdir build
cd build
cmake -G "Visual Studio 15 Win64" ..
cmake --build .
```

Example 3 (using CMake options):

```bash
mkdir build
cd build
cmake -DOUTPUT_DIRECTORY=..\bin -DSFML_ROOT=C:\path\to\your\SFML\location -G "Visual Studio 15 Win64" ..
cmake --build .
```

### Linux

#### Prerequisites for Linux

* g++
* CMake > 2.5

#### Instructions for Linux

Clone the repository, open a terminal in it, and type:

Example 1 (without CMake options):

```bash
mkdir build
cd build
cmake ..
make
```

Example 2 (with CMake options):

```bash
mkdir build
cd build
cmake -DOUTPUT_DIRECTORY=../bin -DSFML_ROOT=/path/to/your/SFML/location ..
make
```

## Running

### Running on Windows

Make sure the different `.dll` files are in the folder where the executable is. Those `.dll` files are needed:

* freetype.dll
* jpeg62.dll
* libbz2.dll
* libpng16.dll
* sfml-graphics-2.dll
* sfml-system-2.dll
* sfml-window-2.dll
* zlib1.dll

Then, you should be able to run the executable `Ecosystem_simulation.exe`.

### Running on Linux

You should be able to run the simulation by opening a terminal in the output directory and type:

```bash
./Ecosystem_simulation
```

### Keybindings

* `Enter`: Starts the simulation

* `Escape`: Ends the simulation

* `Space`: Pauses/Resumes the simulation

## Functionning

* There are `30` cells, spawning randomly on the window at the beginning of the simulation.

* A **cell** has a random radius value, from `5` pixels to `50`. The biggest the **cell** is, the slowest it is (from `10` pixels/second to `50`). At the beginning of the simulation, each **cell** has `100` HP. Each second, the **cell** loses `3` HP. When a **cell** has no longer HP, it disappears: the **cell** is *dead*. A full HP **cell** is `green`, while a *almost-dead* **cell** is `red`.

* Each `0.7` seconds, a **food** appears on the window. A **food** is represented by a `blue` octagon. When a **cell** comes into contact with a **food**, the **cell** *eats* it and regain `20` HP.

Here's a short video how this simulation looks like:

[![YouTube video](https://img.youtube.com/vi/J1tXWuG9WE0/0.jpg)](https://www.youtube.com/watch?v=J1tXWuG9WE0)

This simulation uses [SimplexNoise](https://github.com/SRombauts/SimplexNoise) to simulate a *natural* movement for the cells and [SFML](https://github.com/SFML/SFML) to render the graphics.

## Customizing

You can customize pretty much all the settings of the simulation, such as:

* The maximum HP of the cells

* The number of HP lost per second

* The minimum / maximum radius of the cells / food

* Cells / Food color

* The minimal / maximal speed of the cells

* The number of seconds between the spawn of two two piles of food

* The number of HP the cells regain by eating food

... and more.

You just need to change the constants values in the file `src/constants.hpp`.

## Possible improvments

* A more *random natural* movement for the cell. Currently, the movement is a bit *predictable* (the cells are more likely to move at the center of the window).

* Gather the info about the results of the simulation and write it down in a file. So, we could make statistics about the simulation.

* Speeding up / down the simulation.

* Save the animation in a `.mp4` file.

* Timer for the duration of the simulation.

## Contributing

If you want to improve this project, feel free to create a *pull request*. Make sure your code respects the settings of the `.clang-format` file.
