# Wangscape algorithms

This file contains detailed information about the algorithms and dataflow used in Wangscape.
Understanding them may help you to configure Wangscape to make the tilesets you want.

## Table of contents

0. [Tiles and tilesets](#tiles-and-tilesets)
0. [Rearranging source tiles](#rearranging-source-tiles)
0. [Terrain hyperraph](#terrain-hypergraph)
0. [Combining terrains](#combining-terrains)
0. [Generating corner masks](#generating-corner-masks)

## Tiles and tilesets

Wangscape's input is:
* A set of image files containing your source terrain tiles.
* A set of configurations files describing the locations of the source terrain tiles and how to combine them into tilesets. This includes:
  * The resolution (in pixels) of tiles used.
  * The image file and offset within the image of each terrain.
  * A set of terrain cliques (see [Terrain hypergraph](#terrain-hypergraph)).
  * Filenames of noise module groups used for [generating corner masks](#generating-corner-masks).
  * Which method is used to convert noise values into corner masks ([generating corner masks](#generating-corner-masks)).

Wangscape's output is:
* A set of image files, each one containing a full corner Wang tileset for a subset of the input terrain types,
all of them with compatible borders (if configured correctly).
* A set of JSON files describing the tilesets generated, and where to find a specific tile within them.

## Rearranging source tiles

Wangscape's output tiles are designed to be displayed offset by a quarter tile.
In order for the display tiles to match the source tiles,
the source images must be chopped into quarters and reassembled in this arrangement:
```
12 -> 43
34    21
```
When the resolution is an odd number in the x or y dimension,
the pixel at `(0,0)` is translated right and down by `(floor(rx/2), floor(ry/2))`.
So, to correctly display output tiles, they should be translated left and up by the same amount.

## Terrain hypergraph

###Adjacency restrictions

In a display map built strictly from square tiles, there are no restrictions on which terrain types can border each other.
In a display map built from corner Wang tiles, there are restrictions on which terrain types can meet at a single corner.
For instance, you could generate tilesets where desert and tundra can never be adjacent.
However, some restrictions can be more subtle than that.
For instance, you could generate tilesets with this situation :
```
G: grass
C: sea
P: plains
D: desert

GC    GC    GP    CP    GC
PP    DD    DD    DD    PD
Legal Legal Legal Legal Illegal
```
In theory, the algorithms described below allow you to generate any individual corner Wang tile you want,
with as many different versions as you want.
However, manually listing each individual tile and the number of spares would be impractical
when configuring Wangscape to generate a set of tiles usable for map displays.

It is also possible to simply generate one tile for every combination of terrain types in the game.
If you have a lot of terrain types, this will produce a large number of tiles (`N^4`), which has many disadvantages:
* In a single tileset, the size of the tileset may exceed the maximum texture size of low-end or legacy graphics cards.
* In individual files, the number of tiles may affect performance when browsing the output files.
* The large number of tiles will take a long time to generate, slowing down the configuration process.
* A large number of generated tiles may never be used, for instance all tiles containing deep water and land.

A sensible compromise between texture size and folder size,
and between simple and complex configuration,
is to define a [hypergraph](https://en.wikipedia.org/wiki/Hypergraph) on the set of terrains.

### Hypergraph

The terrain hypergraph, for the purposes of Wangscape, is a list of lists of terrains.
For each list of terrains (which we call cliques), one tileset is generated,
with a single tile for each combination of four terrains in the clique.

Subject to the restriction that each clique must be unique (ignoring order of terrains),
the terrain hypergraph can configure the legal terrain combinations as follows:
* If a set of 2, 3 or 4 terrains is not found in any of the cliques,
those terrains cannot appear around a common corner.
In the case of two terrains, this means they cannot be adjacent (even diagonally).
* If a set of terrains appears in more than one (different) clique,
extra tiles will be generated for each combination of those tiles.
The extra tiles will have different borders (except for the single-terrain tiles),
and can be used to add variety to output displays.

Make sure your hypergraph, where appropriate.
If your hypergraph is (for instance) `[["a","b"],["c","d"]]`,
then it will be impossible for terrains `a` and `b` to be on the same map as terrains `c` and `d`.

If have a set of `N` terrains in which all combinations must be allowed,
you have a few different options:
* Put them all in one clique. This will generate the smallest number of tiles,
but the largest texture size.
* Choose a clique size `4 <= C < N`, and make one clique for each combination of `C` terrains.
That's `N!/(C!(N-C)!)` cliques, each with texture size `(rx*C^2, ry*C^2)`.
Your choice of `C` will depend on your requirements for texture size, folder size, and computation time.
If `N` is so large that no `C` satisfies your requirements,
you will need to introduce more adjacency constraints.

## Combining terrains

Each tile has corner terrains `t1, ..., t4`, and is generated as follows:

0. Generate a [corner mask](#generating-corner-masks) for each corner.
They are essentially 8-bit greyscale images with the same resolution as a tile,
and should satisfy these constraints:
    0. The total of the corner masks in each pixel is 255.
    0. Each one has value 255 at the corresponding corner (hence each one has value 0 at all other corners).
    0. Along the horizontal border (transitioning from `t1` to `t2` or from `t3` to `t4`) incident on the corresponding corner,
    each one has values similar to those generated for all other corner masks with a similar horizontal border.
    0. Equivalent constraints for vertical borders.
0. Initialise the output tile to opaque black `(0,0,0,255)`.
0. For each corner mask and corresponding ([rearranged](#rearranging-source-tiles)) terrain texture:
    0. Add the terrain texture, multiplied by the corner mask and scaled, to the output tile.

Note that this is not the standard alpha blending algorithm.
However, it is easy to configure OpenGL's blending equation and parameters to perform this operation.

## Generating corner masks

Corner masks (effectively 8-bit greyscale images) are generated in two stages:

0. A raster of floating-point noise values is calculated for each corner. They should satisfy these constraints:
    0. Each one has value 1 or greater at the corresponding corner.
    0. Each one has value 0 at all other corners.
    0. Along the horizontal border (transitioning from `t1` to `t2` or from `t3` to `t4`) incident on the corresponding corner,
each one has values similar to those generated for all other corner masks with a similar horizontal border.
    0. Equivalent constraints for vertical borders.
0. For each pixel, an alpha calculator converts the four floating-point values at that pixel into four 8-bit unsigned integer values,
such that the above constraints on corner mask values are satisfied.

### Generating noise values

The generation of noise values is quite delicate, mostly because of the border constraints.

TODO: detailed explanation with diagrams.

### Alpha calculation

TODO: Description of existing alpha calculators.
