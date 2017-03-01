# Wangscape

Converts terrain tiles to procedural corner Wang tilesets.

[![Gitter chat](https://badges.gitter.im/Wangscape.png)](https://gitter.im/Wangscape/Lobby)

Procjam 2016 project (in progress)

# What is Wangscape for?
Does your game have nice square terrain tiles like these ones by David Gervais? ([CC BY 3.0](creativecommons.org/licenses/by/3.0/))

![gervais-terrain-3](https://cloud.githubusercontent.com/assets/15715657/23166703/8cfa561c-f839-11e6-8c43-bdd54cd9a4f7.png)

Do they make sharp borders and ugly right angles like these when you combine them into a map?

![wangscape-squares-sample-fixed](https://cloud.githubusercontent.com/assets/15715657/23484807/7660d0a0-fed0-11e6-892d-2346da221ac9.png)

Would you prefer to have smooth transitions and curved boundaries like these in your map display?

![wangscape-natural-sample](https://cloud.githubusercontent.com/assets/15715657/23166724/a3d6dbb2-f839-11e6-8e1c-4654cb2a11f6.png)

Do you want meandering borders that affect both sides of the logical tile boundaries?

![wangscape-natural-sample-grid](https://cloud.githubusercontent.com/assets/15715657/23166727/a5bf4f86-f839-11e6-84f7-2530d5fcbfa7.png)

Do you think the above tiles need some adjustment before they look right?

![wangscape-options-sample](https://cloud.githubusercontent.com/assets/15715657/23166825/0720fbb2-f83a-11e6-8f48-7a2345dc2444.PNG)
![wangscape-module-sample](https://cloud.githubusercontent.com/assets/15715657/23166827/08b9c30a-f83a-11e6-9e47-d4fe31dea779.PNG)

Do you want to reduce visual repetition by making duplicate border tiles that still tessellate seamlessly? Do you want to do all of this automatically using just the base tile images and a few JSON configuration files?

Then Wangscape can help.

# What are corner Wang tiles?

A good explanation of the corner Wang tiles (and the related Wang tiles) can be found at [cr31.co.uk](http://cr31.co.uk/stagecast/wang/2corn.html). Examples of the natural boundary lines that can be produced with corner Wang tiles in an isometric display can be seen by searching for screenshots of [Civilization 3 terrain](https://www.google.co.uk/search?q=civilization+3+terrain&tbm=isch).

In corner Wang tiles, each corner corresponds to the centre of a logical terrain tile. In the middle of a corner Wang tile, anything can happen, provided the borders match.

![corner-wang-tiles-separate](https://cloud.githubusercontent.com/assets/15715657/23168061/b4a264b6-f83e-11e6-9cb9-2eba145532d6.png)

When you place four corner Wang tiles together, the four quarter-tiles around the joining point combine to form a display tile.

![corner-wang-tiles-together](https://cloud.githubusercontent.com/assets/15715657/23168059/b49ea510-f83e-11e6-8117-4d521d6fdadf.png)

Different combinations of the 8 surrounding terrains can produce different display tiles. If you generate redundant tilesets, there can be even more options.

# How does Wangscape make corner Wang tiles?
* A set of cliques is defined on the terrain types. Each clique produces a separate tileset to avoid making excessively large textures.
* For each valid combination of terrain types in the corners:
    * An alpha mask is generated for each corner.
    * These alpha masks are used to combine each corner's terrain texture into a single tile.
* Currently all tile generation is done through a command-line application configured using a JSON file. In the future, this should be migrated to a GUI interface which allows the user to alter tile generation parameters and immediately see the range of possible results.

# How can I use corner Wang tilesets in my project?
Wangscape's sibling project, [Wangview](https://github.com/Wangscape/Wangview/tree/documentation), demonstrates how to use tilesets produced by Wangscape. Wangview provides a set of well-commented IPython notebooks and Python scripts to enable easy porting to the platform used by your project.

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
* **libnoise**

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
