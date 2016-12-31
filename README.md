# Wangscape
Converts terrain tiles to procedural corner Wang tilesets.

Procjam 2016 project (in progress)

# What is Wangscape for?
Let's say you've drawn or procedurally generated a set of beautiful square terrain tiles to use in a game. But you don't have any nice-looking borders between them, or the borders you do have are all straight and boring, or the borders are all on the same side of the line dividing the in-game tiles.

Wangscape is intended to convert your tiles into a set of corner Wang tiles that solve all those problems.

# What are corner Wang tiles?
A good explanation of the corner Wang tiles (and the related Wang tiles) can be found at [cr31.co.uk](http://cr31.co.uk/stagecast/wang/2corn.html). Examples of the natural boundary lines that can be produced with corner Wang tiles in an isometric display can be seen by searching for screenshots of [Civilization 3 terrain](https://www.google.co.uk/search?q=civilization+3+terrain&tbm=isch).

Rather than matching graphical tiles with the representation of logical tiles on screen, corner Wang tiles should be displayed offset by half a tile in both axes. Thus each logical tile is represented by the matching corners of four graphical tiles, and the logical boundary between tiles will pass through the central axes of the graphical tiles. Thus the graphical boundary between tiles can intrude on both sides of the logical boundary, simply by being drawn on one side or the other of the graphical tile.

# How does Wangscape make corner Wang tiles?
* A set of cliques each with up to 4 members is defined on the terrain types. Each clique produces a separate tileset to avoid making excessively large textures.
* For each valid combination of terrain types in the corners:
    * An alpha mask is generated for each corner (currently it's just a smooth gradient with no randomness).
    * These alpha masks are used to combine each corner's terrain texture into a single tile.
* In future this will be much more customisable, using Perlin noise to generate noisy gradients and boundaries betwen corners.
* Currently all tile generation is done through a command-line application configured using a JSON file. In the future, this should be migrated to a GUI interface which allows the user to alter tile generation parameters and immediately see the range of possible results.

# How can I build Wangscape?

First of all, you need to clone all needed submodules. To get them, execute
this command in Wangscape's root directory:

```bash
git submodule update --init
```

Wangscape depends on these libraries:
* **Boost**
  - system
  - filesystem
* **SFML 2**
  - system
  - graphics
* **spotify-json** (submodule)

After installing them, you can compile Wangscape using either of the methods
below.

## CMake (Linux)

#### 1. Create `build` directory in **Wangscape** project root and move into it:

```shell
mkdir build
cd build
```

#### 2. Execute `cmake` with path to root `CMakeLists.txt`:

```shell
cmake ..
```

It will check for required libraries and prepare files for the next step.

#### 3. Execute `make` to generate `Wangscape` executable under `bin/` subdirectory:

```shell
make
```

#### 4. To run **unit tests** just execute:

```shell
./bin/WangscapeTest
```

# Example

To check how it works for provided examples, call it with the path to one of JSONs
under `Wangscape` dir, e.g. (in `build` directory):

```shell
./bin/Wangscape ../Wangscape/example/example_options.json
```

After that the result image can be found in the `output` directory under
`Wangscape/example`.

Alternatively, you can use the `Wangview` Python script to see example landscapes
using the output tilesets.
Wangview requires Python 3 and the [`bearlibterminal`](https://pypi.python.org/pypi/bearlibterminal) package.

Example usage (in `Wangview` directory):

```shell
python Wangview.py ../Wangscape/example3/output
```

Press `space` to regenerate the landscape, or `esc` to quit.
